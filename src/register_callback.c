
#include "internal.h"
#include "ssix_interface.h"


#define REG_CALL_BACK(call_back, cmd) {												\
		struct disp_when data;															\
		memset(&data, 0, sizeof(data));													\
		data.app = ss_app;																\
		/* Rigister handler for ULR */													\
		data.command = cmd;															\
		return fd_disp_register( call_back, DISP_HOW_CC, &data, NULL, NULL );		\
	}

/*Registers a callback function 'cb' that will be call when Update-Location-Request is received. 
 Check Request callback function description for detail about the callback function.

*/
int ss_reg_ulr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_ulr);
}

/*Registers a callback function 'cb' that will be call when Cancel-Location-Request is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_clr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_clr);	
}

/*Registers a callback function 'cb' that will be call when Authentication-Information-Request is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_air_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_air);	
}

/*Registers a callback function 'cb' that will be call when Insert-Subscriber-Data-Request is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_idr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_idr);	
}

/*Registers a callback function 'cb' that will be call when Delete-Subscriber-Data-Request  is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_dsr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_dsr);	
}

/*Registers a callback function 'cb' that will be call when  Purge-UE-Request is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_pur_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_pur);	
}

/*Registers a callback function 'cb' that will be call when Reset-Request  is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_rsr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_rsr);	
}

/*Registers a callback function 'cb' that will be call when  Notify-Request is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_nor_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_nor);	
}