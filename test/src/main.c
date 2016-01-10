
#include <unistd.h>

#include "ssix_interface.h"
#include "test.h"

/*Initialize the configuratin file path to default path*/
char * diameter_conffile_name = NULL;

/*Value of 'argv' is the destination peer if this peer acts as a client otherwise 'argv' should be NULL(no argument)*/
int main(int argc, char **argv){
	
	char * mme = "mme";
	char * hss = "hss";
	char * ulr = "ulr";
	char * clr = "clr";
	char * air = "air";
	SS_CHECK( ss_init(),"Test application Initialized.\n", "Failed to initialize test application.\n"); ;

	if(argc == 3){
		
		/*Test Update-Location-Request message*/
		if( 0 == strncmp(argv[1], ulr, 3)){

			/*Send ULR message , response for this will be user unknown*/
			test_req_ulr(argv[2],0);
			sleep(3);
			
			/*Send ULR message , response for this will be rat not allowed*/
			test_req_ulr(argv[2],1);
			sleep(3);

			/*Send ULR message , response for this will be roaming not allowed with error diagnostic message*/
			test_req_ulr(argv[2],2);
			sleep(3);

			/*Send ULR message , response should be filled with subscription data of user*/
			test_req_ulr(argv[2],3);	
			
		}		
		/*Test Cancel-Location-Request message*/
		else if(  0 == strncmp(argv[1], clr, 3)){

			/*Prepare and send CLR message*/
			test_req_clr(argv[2]);
			sleep(3);
		}

		/*Test Authentication-Information-Request message*/
		else if(  0 == strncmp(argv[1], air, 3)){

			/*Prepare and send AIR message*/
			test_req_air(argv[2]);
			sleep(3);
		}

		else
			fprintf(stdout, "Invalid application type provided in argument.\nvalid app types are 'mme' and 'hss'.\n");
			
	}

	else if(argc == 2 ){

		/*if started as HSS*/
		if(strncmp(argv[1], hss, 3) == 0){

			/*Register callback for ULR*/
			SS_CHECK( ss_reg_cb_ulr(test_req_cb_ulr), "Call back for ULR registerd.\n", "Failed to register callback for ULR.\n");

			/*Register callback for AIR*/
			SS_CHECK( ss_reg_cb_air(test_req_cb_air), "Call back for AIR registerd.\n", "Failed to register callback for AIR.\n");
		}

		/*if started as MME*/
		else if(strncmp(argv[1], mme, 3) == 0){

			/*Register callback for CLR*/
			SS_CHECK( ss_reg_cb_clr(test_req_cb_clr), "Call back for CLR registerd.\n", "Failed to register callback for CLR.\n");
		}

		else
			fprintf(stdout, "Invalid number of input arguments provided.\n");
	}

	else
		fprintf(stdout, "Invalid number of input arguments provided.\n");
	
	/*waites untill the diameter application is down*/
	SS_CHECK(fd_core_wait_shutdown_complete(), "app shuts down gracefully.\n", "ungracefull app shutdown\n");
	
	return 1;	
}
