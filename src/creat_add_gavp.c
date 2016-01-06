
#include "ssix_interface.h"
#include "internal.h"

/*Add AVP to message structure or goup AVP
	parameter:
		parent: the message structure or group AVP in to which the AVP will be added
		avp: the AVP that to be added in to the message structure or group AVP.
	return: 0 on success or 1 on failure
*/
inline int ss_add_avp(msg_or_avp ** parent, struct avp * avp){
	CHECK_FCT_DO(fd_msg_avp_add(*parent,MSG_BRW_LAST_CHILD,avp),return 1;);
	return 0;
}

/*Creates Terminal-Information group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_terminal_information(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_terminal_information,0,gavp),return 1;);
	return 0;	
}

/*Creates  Active-APN group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_active_apn(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_active_apn,0,gavp),return 1;);
	return 0;
}

/*Creates Equivalent-PLMN-List group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_equivalent_plmn_list(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_equivalent_plmn_list,0,gavp),return 1;);
	return 0;
}

/*Creates MIP6-Agent-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_mip6_agent_info(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_mip6_agent_info,0,gavp),return 1;);
	return 0;
}

/*Creates MIP-Home-Agent-Host group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_mip_home_agent_host(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_mip_home_agent_host,0,gavp),return 1;);
	return 0;
}

/*Creates  Specific-APN-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_specific_apn_info(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_specific_apn_info,0,gavp),return 1;);
	return 0;
}

/*Creates Experimental-Result group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_experimental_result(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_experimental_result,0,gavp),return 1;);
	return 0;
}

/*Creates Subscription-Data group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_subscription_data(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_subscription_data,0,gavp),return 1;);
	return 0;
}

/*Creates LCS-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_lcs_info(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_lcs_info,0,gavp),return 1;);
	return 0;
}

/*Creates  LCS-PrivacyException group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_lcs_privacyexception(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_lcs_privacyexception,0,gavp),return 1;);
	return 0;
}

/*Creates  External-Client group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_external_client(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_external_client,0,gavp),return 1;);
	return 0;
}

/*Creates  Service-Type group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_service_type(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_service_type,0,gavp),return 1;);
	return 0;
}

/*Creates  MO-LR group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_mo_lr(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_mo_lr,0,gavp),return 1;);
	return 0;
}

/*Creates  Teleservice-List group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_teleservice_list(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_teleservice_list,0,gavp),return 1;);
	return 0;
}

/*Creates  Call-Barring-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_call_barring_info(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_call_barring_info,0,gavp),return 1;);
	return 0;
}

/*Creates AMBR group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_ambr(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_ambr,0,gavp),return 1;);
	return 0;
}

/*Creates APN-Configuration-Profile group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_apn_configuration_profile(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_apn_configuration_profile,0,gavp),return 1;);
	return 0;
}

/*Creates  APN-Configuration group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_apn_configuration(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_apn_configuration,0,gavp),return 1;);
	return 0;
}

/*Creates  EPS-Subscribed-QoS-Profile group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_eps_subscribed_qos_profile(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_eps_subscribed_qos_profile,0,gavp),return 1;);
	return 0;
}

/*Creates  Allocation-Retention-Priority group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_allocation_retention_priority(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_allocation_retention_priority,0,gavp),return 1;);
	return 0;
}

/*Creates  WLAN-offloadability group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_wlan_offloadability(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_wlan_offloadability,0,gavp),return 1;);
	return 0;
}

/*Creates  Trace-Data group AVP 
	parameter:
		gavp : a pointer to an pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_trace_data(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_trace_data,0,gavp),return 1;);
	return 0;
}

/*Creates  MDT-Configuration group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_mdt_configuration(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_mdt_configuration,0,gavp),return 1;);
	return 0;
}

/*Creates  Area-Scope group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_area_scope(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_area_scope,0,gavp),return 1;);
	return 0;
}

/*Creates  GPRS-Subscription-Data group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_gprs_subscription_data(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_gprs_subscription_data,0,gavp),return 1;);
	return 0;
}

/*Creates  PDP-Context group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_pdp_context(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_pdp_context,0,gavp),return 1;);
	return 0;
}

/*Creates  CSG-Subscription-Data group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_csg_subscription_data(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_csg_subscription_data,0,gavp),return 1;);
	return 0;
}

/*Creates ProSe-Subscription-Data group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_prose_subscription_data(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_prose_subscription_data,0,gavp),return 1;);
	return 0;
}

/*Creates Requested-EUTRAN-Authentication-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_requested_eutran_authentication_info(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_requested_eutran_authentication_info,0,gavp),return 1;);
	return 0;
}

/*Creates Requested-UTRAN-GERAN-Authentication-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_requested_utran_geran_authentication_info(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_requested_utran_geran_authentication_info,0,gavp),return 1;);
	return 0;
}

/*Creates Authentication-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_authentication_info(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_authentication_info,0,gavp),return 1;);
	return 0;
}



/*Creates  UTRAN-Vector group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_utran_vector(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_utran_vector,0,gavp),return 1;);
	return 0;
}


/*Creates  GERAN-Vector group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_geran_vector(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_geran_vector,0,gavp),return 1;);
	return 0;
}

/*Creates  EPS-User-State group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_eps_user_state(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_eps_user_state,0,gavp),return 1;);
	return 0;
}

/*Creates  MME-User-State group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_mme_user_state(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_mme_user_state,0,gavp),return 1;);
	return 0;
}

/*Creates  EPS-Location-Information group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_eps_location_information(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_eps_location_information,0,gavp),return 1;);
	return 0;
}

/*Creates  MME-Location-Information group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_mme_location_information(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_mme_location_information,0,gavp),return 1;);
	return 0;
}

/*Creates  User-CSG-Information group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_user_csg_information(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_user_csg_information,0,gavp),return 1;);
	return 0;
}

/*Creates  Local-Time-Zone group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_local_time_zone(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_local_time_zone,0,gavp),return 1;);
	return 0;
}

/*Creates Supported-Features group AVP
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_supported_features(struct avp **gavp){

	CHECK_FCT_DO(fd_msg_avp_new(ss_supported_features,0,gavp),return 1;);
	return 0;
}
