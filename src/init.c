
#include "ssix_interface.h"
#include "internal.h"

/*Initailize diameter protocol*/
int ss_init(){

	int ret;	

	/* Initialize the core library */
	ret = fd_core_initialize();
	if (ret != 0) {
		fprintf(stderr, "Error occurred Diameter initialization.\n");
		return ret;
	}

	/* Parse the configuration file */
	CHECK_FCT_DO( fd_core_parseconf(diameter_conffile_name), return 1 );

	/*Initialize the required avp dictionary*/
	CHECK_FCT_DO( ss_dict_init(), return 1);

	/* Start the servers */
	CHECK_FCT_DO( fd_core_start(), return 1 );	

	/* Block until the framework has completed its initialization*/
	CHECK_FCT_DO(fd_core_waitstartcomplete(), return 1);

	/* Advertise the support for the s6 interface application in the peer */
	CHECK_FCT_DO( fd_disp_app_support ( ss_app, ss_vendor, 1, 0 ), return 1 );	
	
	return 0;
}

int  ss_wait_shutdown(){

	/* Wait for termination */
	CHECK_FCT_DO( fd_core_wait_shutdown_complete(), return 1);
	return 0;
}


