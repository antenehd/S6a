
#include "internal_ssix.h"
#include <string.h>
#include <unistd.h>

#include <signal.h>
#include <getopt.h>
#include <locale.h>

static char *conffile = NULL;
static void * catch_signals(void * arg);
static pthread_t signals_thr;

int ss_init(){
	int ret;
	sigset_t sig_all;
	
	/* Block all signals from the current thread and all its future children -- we will catch everything in catch_signals */
	sigfillset(&sig_all);
	ret = pthread_sigmask(SIG_BLOCK, &sig_all, NULL);
	ASSERT(ret == 0);

	/* Initialize the core library */
	ret = fd_core_initialize();
	if (ret != 0) {
		fprintf(stderr, "An error occurred during freeDiameter core library initialization.\n");
		return ret;
	}

	/* Parse the configuration file */
	CHECK_FCT_DO( fd_core_parseconf(conffile), goto error );

	/*Initialize the required avp dictionary*/
	ss_dict_init();

	/*dest_realm = (diameterid *)strdup(fd_g_config->cnf_diamrlm);*/

	/* Start the servers */
	CHECK_FCT_DO( fd_core_start(), goto error );

	/* Allow SIGINT and SIGTERM from this point to terminate the application */
	CHECK_POSIX_DO( pthread_create(&signals_thr, NULL, catch_signals, NULL), goto error );
	
	TRACE_DEBUG(INFO, FD_PROJECT_BINARY " daemon initialized.");

	/* Advertise the support for the s6 interface application in the peer */
	CHECK_FCT( fd_disp_app_support ( ss_app, ss_vendor, 1, 0 ) );	
	
	/*start the server*/
	ss_serv_init();	
	
	return 0;
error:	
	CHECK_FCT_DO( fd_core_shutdown(),  );
	CHECK_FCT( fd_core_wait_shutdown_complete() );
	fd_thr_term(&signals_thr);
	return -1;	

}

void  ss_wait_shutdown(){

	/* Now, just wait for termination */
	CHECK_FCT( fd_core_wait_shutdown_complete());

	/* Just in case it was not the result of a signal, we cancel signals_thr */
	fd_thr_term(&signals_thr);
}

/* Handle some signals */
static void * catch_signals(void * arg)
{
	sigset_t ss;
	fd_log_threadname ( "signals catcher" );
	
	sigemptyset(&ss);
	
	/* Signals that terminate the daemon */
	sigaddset(&ss, SIGTERM);
	sigaddset(&ss, SIGINT);
	
	/* Signals that send an event */
	sigaddset(&ss, SIGUSR1);
	sigaddset(&ss, SIGUSR2);
	
	/* We unblock all other signals, so that their default handler is used (such as SIGTSTP) */
	CHECK_SYS_DO( pthread_sigmask( SIG_SETMASK, &ss, NULL ), goto out );
	
	/* Now loop on the reception of the signal */
	while (1) {
		int sig;/**ps;*/
		
		/* Wait to receive the next signal */
		CHECK_POSIX_DO( sigwait(&ss, &sig), break );
		
		TRACE_DEBUG(FULL, "Signal %d caught", sig);
		
		switch (sig) {
			/*case SIGUSR1:
			case SIGUSR2:
				CHECK_MALLOC_DO( ps = malloc(sizeof(int)), goto out);
				*ps = sig;
				CHECK_FCT_DO( fd_event_send(fd_g_config->cnf_main_ev, FDEV_TRIGGER, sizeof(int), ps), goto out );
				break;*/
				
			case SIGINT:
			case SIGTERM:
				CHECK_FCT_DO( fd_core_shutdown(), goto out );

		}
	}
out:	
	/* Better way to handle this ? */
	ASSERT(0);
	return NULL;
}
