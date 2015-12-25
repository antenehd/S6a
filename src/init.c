
#include "internal_ssix.h"
#include <string.h>
#include <unistd.h>

#include <signal.h>
#include <getopt.h>
#include <locale.h>

static char *conffile = NULL;

int ss_init(){

	int ret;
	

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
	TRACE_DEBUG(INFO, FD_PROJECT_BINARY " Diameter initialized.");

	/* Advertise the support for the s6 interface application in the peer */
	CHECK_FCT( fd_disp_app_support ( ss_app, ss_vendor, 1, 0 ) );	
	
	/*start the server*/
	ss_serv_init();	
	
	return 0;
error:	
	CHECK_FCT_DO( fd_core_shutdown(),  );
	CHECK_FCT( fd_core_wait_shutdown_complete() );
	return -1;	

}

void  ss_wait_shutdown(){

	/* Wait for termination */
	CHECK_FCT( fd_core_wait_shutdown_complete());

}


