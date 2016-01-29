
#include "ssix_interface.h"
#include "internal.h"

/*Sets Vendor-Sepecific-Application-Id AVP in to message structure*/
static inline int set_vendor_specific_app_id(struct msg **msg){														
																									
	struct avp *avp = NULL;
	struct avp *gavp = NULL;																		
	union avp_value val;	

	/*Create Vendor-Sepecific-Application-Id AVP instance*/										
	SS_CHECK( fd_msg_avp_new( ss_vendor_specific_application_id, 0, &gavp));

	/*create Vendor-Id AVP instance and set its value*/	
	SS_CHECK(fd_msg_avp_new(ss_vendor_id,0,&avp));	

	/*set Vendor-Id AVP value and add it to Vendor-Sepecific-Application-Id AVP */							
	val.u32 = (uint32_t) VENDOR_ID_3GPP;														
	SS_CHECK(fd_msg_avp_setvalue(avp,&val));											
  	SS_CHECK(fd_msg_avp_add(gavp,MSG_BRW_LAST_CHILD,avp));	

	/*create Auth-Application-Id AVP instance*/					
	SS_CHECK(fd_msg_avp_new(ss_auth_application_id,0,&avp));

	/*set value of Auth-Application-Id AVP and add it to Vendor-Sepecific-Application-Id AVP*/						
	val.u32 = (uint32_t) SSIX_APPLICATION_ID;													
	SS_CHECK(fd_msg_avp_setvalue(avp,&val));										
	SS_CHECK(fd_msg_avp_add(gavp,MSG_BRW_LAST_CHILD,avp));	

	/*add Vendor-Sepecific-Application-Id AVP to message structure*/					
	SS_CHECK( fd_msg_avp_add( *msg, MSG_BRW_LAST_CHILD, gavp ));	

	return 0;				
}

/*set Auth-Session-State AVP into message structure*/
static inline int set_auth_session_state(struct msg **msg){
													
	struct avp *avp = NULL;																	
	union avp_value val;	
		
	/*create Auth-Session-State AVP instance*/													
	SS_CHECK( fd_msg_avp_new ( ss_auth_session_state, 0, &avp));

	/*set Auth-Session-State AVP value and add it into message structure*/		
	val.i32 = NO_STATE_MAINTAINED;														
	SS_CHECK(fd_msg_avp_setvalue(avp,&val));								
	SS_CHECK( fd_msg_avp_add( *msg, MSG_BRW_LAST_CHILD, avp ));		
	
	return 0;	
}

/*creates a message instance and add in it a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm*/
static inline int create_init_msg(struct dict_object *msg_type, struct msg **msg){								
																						
	/* Create a request message*/															
	SS_CHECK( fd_msg_new( msg_type, MSGFL_ALLOC_ETEID, msg ));	
			
	/* Add a new session */																	
	SS_CHECK( fd_msg_new_session( *msg, NULL, 0 ));							
	
	/*Add the Vendor-Specific-Application-Id*/												
	SS_CHECK( set_vendor_specific_app_id(msg));		
													
	/*Add the Auth-Session-State*/															
	SS_CHECK( set_auth_session_state(msg));	
														
	/* Set Origin-Host & Origin-Realm AVP*/													
	SS_CHECK( fd_msg_add_origin ( *msg, 0 ));	

	return 0;							
}

/* Create answer message from a request message. And set  Vendor-Specific-Application-Id and Auth-Session-State in to the message*/
int ss_msg_create_answer(struct msg **msg){
	
	if((!msg) || (!(*msg)))	return EINVAL;

	/*create answer message from request message, upon success msg will point to the answer message*/
	SS_CHECK( fd_msg_new_answer_from_req( fd_g_config->cnf_dict, msg, 0 ) );

	/* Set Vendor-Specific-Application-Id */
	SS_CHECK(set_vendor_specific_app_id(msg));		

	/*Set Auth-Session-State*/
	SS_CHECK(set_auth_session_state(msg));

	return 0;
}


/*Creates Update-Location-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.*/
int ss_msg_create_ulr(struct msg ** req){

	create_init_msg(ss_cmd_ulr, req);	
	return 0;
}

/*Creates Authentication-Information-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.*/
int ss_msg_create_air(struct msg ** req){

	create_init_msg(ss_cmd_air, req);	
	return 0;
}

/*Creates Cancel-Location-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.*/
int ss_msg_create_clr(struct msg ** req){

	create_init_msg(ss_cmd_clr, req);	
	return 0;
}

/*Creates Insert-Subscriber-Data-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.*/
int ss_msg_create_idr(struct msg ** req){

	create_init_msg(ss_cmd_idr, req);	
	return 0;
}

/*Creates Delete-Subscriber-Data-Request and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.*/
int ss_msg_create_dsr(struct msg ** req){

	create_init_msg(ss_cmd_dsr, req);	
	return 0;
}

/*Creates Purge-UE-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.*/
int ss_msg_create_pur(struct msg ** req){

	create_init_msg(ss_cmd_pur, req);	
	return 0;
}

/*Creates Reset-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.*/
int ss_msg_create_rsr(struct msg ** req){

	create_init_msg(ss_cmd_rsr, req);	
	return 0;
}

/*Creates Notify-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.*/
int ss_msg_create_nor(struct msg ** req){

	create_init_msg(ss_cmd_nor, req);	
	return 0;
}
