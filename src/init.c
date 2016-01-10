
#include "ssix_interface.h"
#include "internal.h"

/*define the default path for the configuration file*/
char * ss_diameter_conffile_name = NULL;

/*Initailize diameter protocol application*/
int ss_init(){

	/* Initialize the core library */
	SS_CHECK( fd_core_initialize());

	/* Parse the configuration file */
	SS_CHECK( fd_core_parseconf(ss_diameter_conffile_name));

	/*Initialize the required avp dictionary*/
	SS_CHECK( ss_dict_init());

	/* Start the servers */
	SS_CHECK( fd_core_start());	

	/* Block until the framework has completed its initialization*/
	SS_CHECK(fd_core_waitstartcomplete());

	/* Advertise the support for the s6 interface application in the peer */
	SS_CHECK( fd_disp_app_support ( ss_app, ss_vendor, 1, 0 ));	
	
	return 0;
}
