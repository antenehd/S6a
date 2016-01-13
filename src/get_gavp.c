
#include "ssix_interface.h"
#include "internal.h"

/*Get AVP of type 'dict' from message 'msg'*/
static inline int get_gavp_msg(struct msg *msg, struct dict_object *dict, struct avp **res){

	/*look in to the message structure for the AVP of type 'dict'*/
	return fd_msg_search_avp ( msg, dict, res);
}

/**get AVP of 'dict' type from group AVP 'gavp'*/
static inline int get_gavp(struct avp *gavp, struct dict_object *dict, struct avp **res){

	/*look in to the group avp for the group AVP of type 'dict'*/	
	return fd_avp_search_avp ( gavp, dict, res, MSG_BRW_FIRST_CHILD );
}

/**get AVP of 'dict' type next to another AVP 'gavp'*/
static inline int get_gavp_next(struct avp *gavp, struct dict_object *dict, struct avp **next_gavp){

	/*Search for AVP of type 'dict' next to AVP 'gavp'*/
	return fd_avp_search_avp ( gavp, dict, next_gavp, MSG_BRW_NEXT );
}

/*Retrievs Terminal-Information group AVP from message*/
int ss_get_gavp_terminal_information(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_terminal_information, gavp);
}

/*Retrievs the first Active-APN group AVP from message*/
int ss_get_gavp_active_apn(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_active_apn, gavp);
}

/*Retrievs the next Active-APN group AVP*/
int ss_get_gavp_next_active_apn(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_active_apn, gavp);
}

/*Retrievs Equivalent-PLMN-List group AVP from message*/
int ss_get_gavp_equivalent_plmn_list(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_equivalent_plmn_list, gavp);
}

/*Retrievs MIP6-Agent-Info group AVP from group avp*/
int ss_get_gavp_mip6_agent_info(avp_or_msg *msg_avp, struct avp **gavp){

	int ret = 1;

	/*Check if the search reference(container) is AVP of type group*/
	ret = get_gavp((struct avp *)msg_avp, ss_mip6_agent_info, gavp);
	if(0 == ret) return ret;
	
	/*Check if the search reference(container) is message structure*/
	ret = get_gavp_msg((struct msg *)msg_avp, ss_mip6_agent_info, gavp);
	if(0 == ret) return ret;

	return ret;
	
}

/*Retrievs MIP-Home-Agent-Host group AVP from group avp*/
int ss_get_gavp_mip_home_agent_host(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mip_home_agent_host, gavp);
}

/*Retrievs the first Specific-APN-Info group AVP from group avp*/
int ss_get_gavp_specific_apn_info(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_specific_apn_info, gavp);
}

/*Retrievs the next Specific-APN-Info group AVP*/
int ss_get_gavp_next_specific_apn_info(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_specific_apn_info, gavp);
}

/*Retrievs Experimental-Result group AVP from message*/
int ss_get_gavp_experimental_result(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_experimental_result, gavp);
}

/*Retrievs Subscription-Data group AVP from message*/
int ss_get_gavp_subscription_data(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_subscription_data, gavp);
}

/*Retrievs LCS-Info group AVP from group avp*/
int ss_get_gavp_lcs_info(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_lcs_info, gavp);
}

/*Retrievs the first LCS-PrivacyException group AVP from group avp*/
int ss_get_gavp_lcs_privacyexception(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_lcs_privacyexception, gavp);
}

/*Retrievs the next LCS-PrivacyException group AVP*/
int ss_get_gavp_next_lcs_privacyexception(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_lcs_privacyexception, gavp);
}

/*Retrievs the first External-Client group AVP from group avp*/
int ss_get_gavp_external_client(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_external_client, gavp);
}

/*Retrievs the next External-Client group AVP*/
int ss_get_gavp_next_external_client(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_external_client, gavp);
}

/*Retrievs the first Service-Type group AVP from group avp*/
int ss_get_gavp_service_type(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_service_type, gavp);
}

/*Retrievs the next Service-Type group AVP*/
int ss_get_gavp_next_service_type(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_service_type, gavp);
}

/*Retrievs the first MO-LR group AVP from group avp*/
int ss_get_gavp_mo_lr(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mo_lr, gavp);
}

/*Retrievs the next MO-LR group AVP*/
int ss_get_gavp_next_mo_lr(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_mo_lr, gavp);
}

/*Retrievs the first Teleservice-List group AVP from group avp*/
int ss_get_gavp_teleservice_list(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_teleservice_list, gavp);
}

/*Retrievs the first Call-Barring-Info group AVP from group avp*/
int ss_get_gavp_call_barring_info(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_call_barring_info, gavp);
}

/*Retrievs the next Call-Barring-Info group AVP*/
int ss_get_gavp_next_call_barring_info(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_call_barring_info, gavp);
}

/*Retrievs AMBR group AVP from group avp*/
int ss_get_gavp_ambr(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_ambr, gavp);
}

/*Retrievs APN-Configuration-Profile group AVP from group avp*/
int ss_get_gavp_apn_configuration_profile(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_apn_configuration_profile, gavp);
}

/*Retrievs the first APN-Configuration group AVP from group avp*/
int ss_get_gavp_apn_configuration(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_apn_configuration, gavp);
}

/*Retrievs the next APN-Configuration group AVP*/
int ss_get_gavp_next_apn_configuration(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_apn_configuration, gavp);
}

/*Retrievs the first EPS-Subscribed-QoS-Profile group AVP from group avp*/
int ss_get_gavp_eps_subscribed_qos_profile(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_eps_subscribed_qos_profile, gavp);
}

/*Retrievs the first Allocation-Retention-Priority group AVP from group avp*/
int ss_get_gavp_allocation_retention_priority(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_allocation_retention_priority, gavp);
}

/*Retrievs the first WLAN-offloadability group AVP from group avp*/
int ss_get_gavp_wlan_offloadability(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_wlan_offloadability, gavp);
}

/*Retrievs the first Trace-Data group AVP from group avp*/
int ss_get_gavp_trace_data(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_trace_data, gavp);
}

/*Retrievs the first MDT-Configuration group AVP from group avp*/
int ss_get_gavp_mdt_configuration(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mdt_configuration, gavp);
}

/*Retrievs the first Area-Scope group AVP from group avp*/
int ss_get_gavp_area_scope(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_area_scope, gavp);
}

/*Retrievs the first GPRS-Subscription-Data group AVP from group avp*/
int ss_get_gavp_gprs_subscription_data(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_gprs_subscription_data, gavp);
}

/*Retrievs the first PDP-Context group AVP from group avp*/
int ss_get_gavp_pdp_context(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_pdp_context, gavp);
}

/*Retrievs the next PDP-Context group AVP*/
int ss_get_gavp_next_pdp_context(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_pdp_context, gavp);
}

/*Retrievs the first CSG-Subscription-Data group AVP from group avp*/
int ss_get_gavp_csg_subscription_data(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_csg_subscription_data, gavp);
}

/*Retrievs the next CSG-Subscription-Data group AVP*/
int ss_get_gavp_next_csg_subscription_data(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_csg_subscription_data, gavp);
}

/*Retrievs ProSe-Subscription-Data group AVP from group avp*/
int ss_get_gavp_prose_subscription_data(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_prose_subscription_data, gavp);
}

/*Retrievs Requested-EUTRAN-Authentication-Info group AVP from group avp*/
int ss_get_gavp_requested_eutran_authentication_info(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_requested_eutran_authentication_info, gavp);
}

/*Retrievs Requested-UTRAN-GERAN-Authentication-Info group AVP from group avp*/
int ss_get_gavp_requested_utran_geran_authentication_info(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_requested_utran_geran_authentication_info, gavp);
}

/*Retrievs Authentication-Info group AVP from message*/
int ss_get_gavp_authentication_info(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_authentication_info, gavp);
}

/*Retrievs the first E-UTRAN-Vector group AVP from group avp*/
int ss_get_gavp_e_utran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_e_utran_vector, gavp);
}

/*Retrievs the next E-UTRAN-Vector group AVP*/
int ss_get_gavp_next_e_utran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_e_utran_vector, gavp);
}

/*Retrievs the first UTRAN-Vector group AVP from group avp*/
int ss_get_gavp_utran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_utran_vector, gavp);
}

/*Retrievs the next UTRAN-Vector group AVP*/
int ss_get_gavp_next_utran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_utran_vector, gavp);
}

/*Retrievs the first GERAN-Vector group AVP from group avp*/
int ss_get_gavp_geran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_geran_vector, gavp);
}

/*Retrievs the next GERAN-Vector group AVP*/
int ss_get_gavp_next_geran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_geran_vector, gavp);
}

/*Retrievs the first EPS-User-State group AVP from message*/
int ss_get_gavp_eps_user_state(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_eps_user_state, gavp);
}

/*Retrievs the first MME-User-State group AVP from group avp*/
int ss_get_gavp_mme_user_state(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mme_user_state, gavp);
}

/*Retrievs the first EPS-Location-Information group AVP from message*/
int ss_get_gavp_eps_location_information(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_eps_location_information, gavp);
}

/*Retrievs the first MME-Location-Information group AVP from group avp*/
int ss_get_gavp_mme_location_information(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mme_location_information, gavp);
}

/*Retrievs the first User-CSG-Information group AVP from group avp*/
int ss_get_gavp_user_csg_information(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_user_csg_information, gavp);
}

/*Retrievs the first Local-Time-Zone group AVP from message*/
int ss_get_gavp_local_time_zone(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_local_time_zone, gavp);
}

/*Retrievs the first Supported-Features group AVP from message*/
int ss_get_gavp_supported_features(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_supported_features, gavp);
}

/*Retrievs the next Supported-Features group AVP next to other Supported-Features AVP*/
int ss_get_gavp_next_supported_features(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_supported_features, gavp);
}
