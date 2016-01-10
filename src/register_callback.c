
#include "internal.h"
#include "ssix_interface.h"


#define REG_CALL_BACK(call_back, cmd) {												\
		struct disp_when data;															\
		memset(&data, 0, sizeof(data));													\
		data.app = ss_app;																\
		/* Rigister handler*/													\
		data.command = cmd;															\
		return fd_disp_register( call_back, DISP_HOW_CC, &data, NULL, NULL );		\
	}

/**Registers a callback function 'cb' that will be call when Update-Location-Request is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_cb_ulr(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_ulr);
}

/**Registers a callback function 'cb' that will be call when Cancel-Location-Request is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_cb_clr(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_clr);	
}

/**Registers a callback function 'cb' that will be call when Authentication-Information-Request is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_cb_air(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_air);	
}

/**Registers a callback function 'cb' that will be call when Insert-Subscriber-Data-Request is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_cb_idr(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_idr);	
}

/**Registers a callback function 'cb' that will be call when Delete-Subscriber-Data-Request  is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_cb_dsr(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_dsr);	
}

/**Registers a callback function 'cb' that will be call when  Purge-UE-Request is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_cb_pur(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_pur);	
}

/**Registers a callback function 'cb' that will be call when Reset-Request  is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_cb_rsr(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_rsr);	
}

/**Registers a callback function 'cb' that will be call when  Notify-Request is received. 
 Check Request callback function description for detail about the callback function.
*/
int ss_reg_cb_nor(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)){
	
	REG_CALL_BACK(cb, ss_cmd_nor);	
}
