
#include "ssix_interface.h"
#include "internal.h"

/*Add AVP to a given message structure or  AVP instance*/
int ss_add_avp(avp_or_msg **parent, struct avp *avp){
	return fd_msg_avp_add(*parent,MSG_BRW_LAST_CHILD,avp);
}

/*Creates a new Terminal-Information  AVP instance*/
int ss_create_terminal_information(struct avp **gavp){

	return fd_msg_avp_new(ss_terminal_information,0,gavp);
}

/*Creates a new  Active-APN  AVP instance*/
int ss_create_active_apn(struct avp **gavp){

	return fd_msg_avp_new(ss_active_apn,0,gavp);
}

/*Creates a new Equivalent-PLMN-List  AVP instance*/
int ss_create_equivalent_plmn_list(struct avp **gavp){

	return fd_msg_avp_new(ss_equivalent_plmn_list,0,gavp);
}

/*Creates a new MIP6-Agent-Info  AVP instance*/
int ss_create_mip6_agent_info(struct avp **gavp){

	return fd_msg_avp_new(ss_mip6_agent_info,0,gavp);
}

/*Creates a new MIP-Home-Agent-Host  AVP instance*/
int ss_create_mip_home_agent_host(struct avp **gavp){

	return fd_msg_avp_new(ss_mip_home_agent_host,0,gavp);
}

/*Creates a new  Specific-APN-Info  AVP instance*/
int ss_create_specific_apn_info(struct avp **gavp){

	return fd_msg_avp_new(ss_specific_apn_info,0,gavp);
}

/*Creates a new Experimental-Result  AVP instance*/
int ss_create_experimental_result(struct avp **gavp){

	return fd_msg_avp_new(ss_experimental_result,0,gavp);
}

/*Creates a new Subscription-Data  AVP instance*/
int ss_create_subscription_data(struct avp **gavp){

	return fd_msg_avp_new(ss_subscription_data,0,gavp);
}

/*Creates a new LCS-Info  AVP instance*/
int ss_create_lcs_info(struct avp **gavp){

	return fd_msg_avp_new(ss_lcs_info,0,gavp);
}

/*Creates a new  LCS-PrivacyException  AVP instance*/
int ss_create_lcs_privacyexception(struct avp **gavp){

	return fd_msg_avp_new(ss_lcs_privacyexception,0,gavp);
}

/*Creates a new  External-Client  AVP instance*/
int ss_create_external_client(struct avp **gavp){

	return fd_msg_avp_new(ss_external_client,0,gavp);
}

/*Creates a new  Service-Type  AVP instance*/
int ss_create_service_type(struct avp **gavp){

	return fd_msg_avp_new(ss_service_type,0,gavp);
}

/*Creates a new  MO-LR  AVP instance*/
int ss_create_mo_lr(struct avp **gavp){

	return fd_msg_avp_new(ss_mo_lr,0,gavp);
}

/*Creates a new  Teleservice-List  AVP instance*/
int ss_create_teleservice_list(struct avp **gavp){

	return fd_msg_avp_new(ss_teleservice_list,0,gavp);
}

/*Creates a new  Call-Barring-Info  AVP instance*/
int ss_create_call_barring_info(struct avp **gavp){

	return fd_msg_avp_new(ss_call_barring_info,0,gavp);
}

/*Creates a new AMBR  AVP instance*/
int ss_create_ambr(struct avp **gavp){

	return fd_msg_avp_new(ss_ambr,0,gavp);
}

/*Creates a new APN-Configuration-Profile  AVP instance*/
int ss_create_apn_configuration_profile(struct avp **gavp){

	return fd_msg_avp_new(ss_apn_configuration_profile,0,gavp);
}

/*Creates a new  APN-Configuration  AVP instance*/
int ss_create_apn_configuration(struct avp **gavp){

	return fd_msg_avp_new(ss_apn_configuration,0,gavp);
}

/*Creates a new  EPS-Subscribed-QoS-Profile  AVP instance*/
int ss_create_eps_subscribed_qos_profile(struct avp **gavp){

	return fd_msg_avp_new(ss_eps_subscribed_qos_profile,0,gavp);
}

/*Creates a new  Allocation-Retention-Priority  AVP instance*/
int ss_create_allocation_retention_priority(struct avp **gavp){

	return fd_msg_avp_new(ss_allocation_retention_priority,0,gavp);
}

/*Creates a new  WLAN-offloadability  AVP instance*/
int ss_create_wlan_offloadability(struct avp **gavp){

	return fd_msg_avp_new(ss_wlan_offloadability,0,gavp);
}

/*Creates a new  Trace-Data  AVP instance 
	parameter:
		gavp : a pointer to an pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
int ss_create_trace_data(struct avp **gavp){

	return fd_msg_avp_new(ss_trace_data,0,gavp);
}

/*Creates a new  MDT-Configuration  AVP instance*/
int ss_create_mdt_configuration(struct avp **gavp){

	return fd_msg_avp_new(ss_mdt_configuration,0,gavp);
}

/*Creates a new  Area-Scope  AVP instance*/
int ss_create_area_scope(struct avp **gavp){

	return fd_msg_avp_new(ss_area_scope,0,gavp);
}

/*Creates a new  GPRS-Subscription-Data  AVP instance*/
int ss_create_gprs_subscription_data(struct avp **gavp){

	return fd_msg_avp_new(ss_gprs_subscription_data,0,gavp);
}

/*Creates a new  PDP-Context  AVP instance*/
int ss_create_pdp_context(struct avp **gavp){

	return fd_msg_avp_new(ss_pdp_context,0,gavp);
}

/*Creates a new  CSG-Subscription-Data  AVP instance*/
int ss_create_csg_subscription_data(struct avp **gavp){

	return fd_msg_avp_new(ss_csg_subscription_data,0,gavp);
}

/*Creates a new ProSe-Subscription-Data  AVP instance*/
int ss_create_prose_subscription_data(struct avp **gavp){

	return fd_msg_avp_new(ss_prose_subscription_data,0,gavp);
}

/*Creates a new Requested-EUTRAN-Authentication-Info  AVP instance*/
int ss_create_requested_eutran_authentication_info(struct avp **gavp){

	return fd_msg_avp_new(ss_requested_eutran_authentication_info,0,gavp);
}

/*Creates a new Requested-UTRAN-GERAN-Authentication-Info  AVP instance*/
int ss_create_requested_utran_geran_authentication_info(struct avp **gavp){

	return fd_msg_avp_new(ss_requested_utran_geran_authentication_info,0,gavp);
}

/*Creates a new Authentication-Info  AVP instance*/
int ss_create_authentication_info(struct avp **gavp){

	return fd_msg_avp_new(ss_authentication_info,0,gavp);
}

/*Creates a new  UTRAN-Vector  AVP instance*/
int ss_create_e_utran_vector(struct avp **gavp){

	return fd_msg_avp_new(ss_e_utran_vector,0,gavp);
}

/*Creates a new  UTRAN-Vector  AVP instance*/
int ss_create_utran_vector(struct avp **gavp){

	return fd_msg_avp_new(ss_utran_vector,0,gavp);
}

/*Creates a new  GERAN-Vector  AVP instance*/
int ss_create_geran_vector(struct avp **gavp){

	return fd_msg_avp_new(ss_geran_vector,0,gavp);
}

/*Creates a new  EPS-User-State  AVP instance*/
int ss_create_eps_user_state(struct avp **gavp){

	return fd_msg_avp_new(ss_eps_user_state,0,gavp);
}

/*Creates a new  MME-User-State  AVP instance*/
int ss_create_mme_user_state(struct avp **gavp){

	return fd_msg_avp_new(ss_mme_user_state,0,gavp);
}

/*Creates a new  EPS-Location-Information  AVP instance*/
int ss_create_eps_location_information(struct avp **gavp){

	return fd_msg_avp_new(ss_eps_location_information,0,gavp);
}

/*Creates a new  MME-Location-Information  AVP instance*/
int ss_create_mme_location_information(struct avp **gavp){

	return fd_msg_avp_new(ss_mme_location_information,0,gavp);
}

/*Creates a new  User-CSG-Information  AVP instance*/
int ss_create_user_csg_information(struct avp **gavp){

	return fd_msg_avp_new(ss_user_csg_information,0,gavp);
}

/*Creates a new  Local-Time-Zone  AVP instance*/
int ss_create_local_time_zone(struct avp **gavp){

	return fd_msg_avp_new(ss_local_time_zone,0,gavp);
}

/*Creates a new Supported-Features  AVP instance*/
int ss_create_supported_features(struct avp **gavp){

	return fd_msg_avp_new(ss_supported_features,0,gavp);
}
