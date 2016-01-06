
#include "ssix_interface.h"
#include "internal.h"

#define SET_VENDOR_SPEC_APP_ID(msg)																	\
	{																								\
		struct avp *avp, *gavp;																		\
		union avp_value val;																		\
		CHECK_FCT_DO( fd_msg_avp_new ( ss_vendor_specific_application_id, 0, &gavp), return 1; );	\
		CHECK_FCT_DO(fd_msg_avp_new(ss_vendor_id,0,&avp),return 1;);								\
		val.u32 = (uint32_t) VENDOR_ID_3GPP;																\
		CHECK_FCT_DO(fd_msg_avp_setvalue(avp,&val),return 1;);										\
  		CHECK_FCT_DO(fd_msg_avp_add(gavp,MSG_BRW_LAST_CHILD,avp),return 1;);						\
		CHECK_FCT_DO(fd_msg_avp_new(ss_auth_application_id,0,&avp),return 1;);						\
		val.u32 = (uint32_t) SSIX_APPLICATION_ID;														\
		CHECK_FCT_DO(fd_msg_avp_setvalue(avp,&val),return 1;);										\
		CHECK_FCT_DO(fd_msg_avp_add(gavp,MSG_BRW_LAST_CHILD,avp),return 1;);						\
		CHECK_FCT_DO( fd_msg_avp_add( msg, MSG_BRW_LAST_CHILD, gavp ), return 1;);					\
	}

#define SET_AUTH_SESSION_STATE(msg)															\
	{																						\
		struct avp *avp;																	\
		union avp_value val;																\
		CHECK_FCT_DO( fd_msg_avp_new ( ss_auth_session_state, 0, &avp), return 1; );		\
		val.i32 = NO_STATE_MAINTAINED;														\
		CHECK_FCT_DO(fd_msg_avp_setvalue(avp,&val), return 1;);								\
		CHECK_FCT_DO( fd_msg_avp_add( msg, MSG_BRW_LAST_CHILD, avp ), return 1; );			\
	}

#define CREATE_INIT_MSG(msg_type, msg)															\
	{																							\
		struct session *sess = NULL;															\
		/* Create a request message*/															\
		CHECK_FCT_DO( fd_msg_new( msg_type, MSGFL_ALLOC_ETEID, msg ), return 1; );				\
		/* Add a new session */																	\
		CHECK_FCT_DO( fd_msg_new_session( *msg, NULL, 0 ), return 1;);							\
		CHECK_FCT_DO( fd_msg_sess_get(fd_g_config->cnf_dict, *msg, &sess, NULL), return 1;);	\
		/*Add the Vendor-Specific-Application-Id*/												\
		SET_VENDOR_SPEC_APP_ID(*msg);															\
		/*Add the Auth-Session-State*/															\
		SET_AUTH_SESSION_STATE(*msg);															\
		/* Set Origin-Host & Origin-Realm AVP*/													\
		CHECK_FCT_DO( fd_msg_add_origin ( *msg, 0 ), return 1; );								\
	}

/* Create answer message from a request message. And set  Vendor-Specific-Application-Id and Auth-Session-State in to the message
	parameter:
		msg : a pointer to the request message pointer. it will point to the answer message upon function return.
		req : a pointer to a message structure pointer that will refere to the original request message upon function return
	return : 0 on success 1 on failure
*/
inline int ss_create_answer(struct msg **msg, struct msg **req){
	
	*req = *msg;
	CHECK_FCT( fd_msg_new_answer_from_req ( fd_g_config->cnf_dict, msg, 0 ) );

	/* Set Vendor-Specific-Application-Id */
	SET_VENDOR_SPEC_APP_ID(*msg);		

	/*Set Auth-Session-State*/
	SET_AUTH_SESSION_STATE(*msg);

	return 0;
}


/*Creates Update-Location-Request message and then creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success 1 on failure
*/
inline int ss_create_msg_ulr(struct msg ** req){

	CREATE_INIT_MSG(ss_cmd_ulr, req);	
	return 0;
}

/*Creates Authentication-Information-Request message and hen creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success 1 on failure
*/
inline int ss_create_msg_air(struct msg ** req){

	CREATE_INIT_MSG(ss_cmd_air, req);	
	return 0;
}

/*Creates Cancel-Location-Request message and then creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success 1 on failure
*/
inline int ss_create_msg_clr(struct msg ** req){

	CREATE_INIT_MSG(ss_cmd_clr, req);	
	return 0;
}

/*Creates Insert-Subscriber-Data-Request message and hen creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success 1 on failure
*/
inline int ss_create_msg_idr(struct msg ** req){

	CREATE_INIT_MSG(ss_cmd_idr, req);	
	return 0;
}

/*Creates Delete-Subscriber-Data-Request message and hen creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success 1 on failure
*/
inline int ss_create_msg_dsr(struct msg ** req){

	CREATE_INIT_MSG(ss_cmd_dsr, req);	
	return 0;
}

/*Creates Purge-UE-Request message and then creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success 1 on failure
*/
inline int ss_create_msg_pur(struct msg ** req){

	CREATE_INIT_MSG(ss_cmd_pur, req);	
	return 0;
}

/*Creates Reset-Request message and hen creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success 1 on failure
*/
inline int ss_create_msg_rsr(struct msg ** req){

	CREATE_INIT_MSG(ss_cmd_rsr, req);	
	return 0;
}

/*Creates Notify-Request message and hen creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success 1 on failure
*/
inline int ss_create_msg_nor(struct msg ** req){

	CREATE_INIT_MSG(ss_cmd_nor, req);	
	return 0;
}