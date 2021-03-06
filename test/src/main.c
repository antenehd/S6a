
#include <unistd.h>

#include "test.h"

/*Initialize the configuratin file path to default path*/
char * diameter_conffile_name = NULL;

/*Value of 'argv' is the destination peer if this peer acts as a client otherwise 'argv' should be NULL(no argument)*/
int main(int argc, char **argv){
	
	char *mme = "mme";
	char *hss = "hss";
	char *ulr = "ulr";
	char *clr = "clr";
	char *air = "air";
	char *idr = "idr";
	char *dsr = "dsr";
	char *pur = "pur";
	char *rsr = "rsr";
	char *nor = "nor";

	SS_CHECK( ss_init(),"Test application Initialized.\n", "Failed to initialize test application.\n"); ;

	if(argc == 3){
		
		/*Test Update-Location-Request message*/
		if( 0 == strncmp(argv[1], ulr, 3)){

			/*Send ULR message , response for this will be user unknown*/
			test_req_ulr(argv[2],0);
			sleep(1);
			
			/*Send ULR message , response for this will be rat not allowed*/
			test_req_ulr(argv[2],1);
			sleep(1);

			/*Send ULR message , response for this will be roaming not allowed with error diagnostic message*/
			test_req_ulr(argv[2],2);
			sleep(1);

			/*Send ULR message , response should be filled with subscription data of user*/
			test_req_ulr(argv[2],3);	
			
		}		
		/*Test Cancel-Location-Request message*/
		else if(  0 == strncmp(argv[1], clr, 3)){

			/*Prepare and send CLR message*/
			test_req_clr(argv[2]);
		}

		/*Test Authentication-Information-Request message*/
		else if(  0 == strncmp(argv[1], air, 3)){

			/*Prepare and send AIR message*/
			test_req_air(argv[2]);
		}

		/*Test Insert-Subscriber-Data-Request message*/
		else if(  0 == strncmp(argv[1], idr, 3)){

			/*Prepare and send IDR message*/
			test_req_idr(argv[2]);
		}

		/*Test Delete-Subscriber-Data-Request message*/
		else if(  0 == strncmp(argv[1], dsr, 3)){

			/*Prepare and send DSR message*/
			test_req_dsr(argv[2]);
		}

		/*Test Purge-UE-Request message*/
		else if(  0 == strncmp(argv[1], pur, 3)){

			/*Prepare and send PUR message*/
			test_req_pur(argv[2]);
		}

		/*Test Reset-Request message*/
		else if(  0 == strncmp(argv[1], rsr, 3)){

			/*Prepare and send PUR message*/
			test_req_rsr(argv[2]);
		}

		/*Test Notify-Request message*/
		else if(  0 == strncmp(argv[1], nor, 3)){

			/*Prepare and send PUR message*/
			test_req_nor(argv[2]);
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
	
			/*Register callback for PUR*/
			SS_CHECK( ss_reg_cb_pur(test_req_cb_pur), "Call back for PUR registerd.\n", "Failed to register callback for PUR.\n");

			/*Register callback for NOR*/
			SS_CHECK( ss_reg_cb_nor(test_req_cb_nor), "Call back for NOR registerd.\n", "Failed to register callback for NOR.\n");
		}

		/*if started as MME*/
		else if(strncmp(argv[1], mme, 3) == 0){

			/*Register callback for CLR*/
			SS_CHECK( ss_reg_cb_clr(test_req_cb_clr), "Call back for CLR registerd.\n", "Failed to register callback for CLR.\n");

			/*Register callback for IDR*/
			SS_CHECK( ss_reg_cb_idr(test_req_cb_idr), "Call back for IDR registerd.\n", "Failed to register callback for IDR.\n");

			/*Register callback for DSR*/
			SS_CHECK( ss_reg_cb_dsr(test_req_cb_dsr), "Call back for DSR registerd.\n", "Failed to register callback for DSR.\n");

			/*Register callback for RSR*/
			SS_CHECK( ss_reg_cb_rsr(test_req_cb_rsr), "Call back for RSR registerd.\n", "Failed to register callback for RSR.\n");
		}

		else
			fprintf(stdout, "Invalid number of input arguments provided.\n");
	}

	else
		fprintf(stdout, "Invalid number of input arguments provided.\n");
	
	/*waites untill the diameter application is down*/
	SS_CHECK(fd_core_wait_shutdown_complete(), "TEST app SHUTS DOWN gracefully.\n", "TEST APP SHUTS DOWN ungracefullY\n");
	
	return 1;	
}
