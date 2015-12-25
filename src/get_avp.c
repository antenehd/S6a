#include "interf_ssix.h"

int get_gavp_msg(struct msg *msg, struct dict_object *dict, struct avp **res){

	if (!msg || !dict || !res)
		return 1;
	
	/*look in to the message structure for the avp of type 'dict'*/
	CHECK_FCT_DO( fd_msg_search_avp ( msg, dict, res), goto error );
	return 0;

	error:
		return 1;
}

int get_gavp(struct avp *gavp, struct dict_object *dict, struct avp **res){

	if (!gavp || !dict || !res)
		return 1;
	
	/*look in to the group avp for the group avp of type 'dict'*/
	ss_avp_search_avp ( gavp, dict, res, MSG_BRW_FIRST_CHILD )
	CHECK_FCT_DO( fd_msg_search_avp ( msg, dict, res), goto error );
	return 0;

	error:
		return 1;
}

int get_gavp_next(struct avp *gavp, struct dict_object *dict, struct avp **res){

	if (!gavp || !dict || !res)
		return 1;
	
	/*look in to the group avp for the group avp of type 'dict'*/
	ss_avp_search_avp ( gavp, dict, res, MSG_BRW_NEXT)
	CHECK_FCT_DO( fd_msg_search_avp ( msg, dict, res), goto error );
	return 0;

	error:
		return 1;
}

/*Retrievs Terminal-Information group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which Terminal-Information group is searched.
		gavp : a pointer to Terminal-Information group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_terminal_information(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_terminal_info, gavp);
}

/*Retrievs the first Active-APN group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which the Active-APN group avp is searched.
		gavp : a pointer to a Active-APN group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_active_apn(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_activ_apn, gavp);
}

/*Retrievs the next Active-APN group AVP 
	parameter:
		avp : a pointer to Active-APN group AVP pointer next to which the next Active-APN group avp is searched.
		gavp : a pointer to Active-APN group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_active_apn(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_activ_apn, gavp);
}

/*Retrievs Equivalent-PLMN-List group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which the Equivalent-PLMN-List group avp is searched.
		gavp : a pointer to Equivalent-PLMN-List group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_equivalent_plmn_list(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_eqv_plmn_list, gavp);
}

/*Retrievs MIP6-Agent-Info group AVP from group avp
	parameter:
		avp : a pointer to a group avp pointer in which MIP6-Agent-Info group avp is searched.
		gavp : a pointer to MIP6-Agent-Info group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_mip6_agent_info(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mip6_agent_info, gavp);
}

/*Retrievs MIP-Home-Agent-Host group AVP from group avp
	parameter:
		avp : a pointer to a group avp pointer in which MIP-Home-Agent-Host group avp is searched.
		gavp : a pointer to MIP-Home-Agent-Host group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_mip_home_agent_host(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mip_home_agen_host, gavp);
}

/*Retrievs the first Specific-APN-Info group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which Specific-APN-Info group avp is searched.
		gavp : a pointer to Specific-APN-Info group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_specific_apn_info(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mip6_agent_info, gavp);
}

/*Retrievs the next Specific-APN-Info group AVP 
	parameter:
		avp : a pointer to Specific-APN-Info group AVP pointer next to which the next Specific-APN-Info group avp is searched.
		gavp : a pointer to a Specific-APN-Info group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_specific_apn_info(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_activ_apn, gavp);
}

/*Retrievs Experimental-Result group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which the Experimental-Result group avp is searched.
		gavp : a pointer to Experimental-Result group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_experimental_result(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_exper_result, gavp);
}

/*Retrievs Subscription-Data group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which the Subscription-Data group avp is searched.
		gavp : a pointer to Subscription-Data group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_subscription_data(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_subsc_data, gavp);
}

/*Retrievs LCS-Info group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which LCS-Info group avp is searched.
		gavp : a pointer to Specific-APN-Info group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_lcs_info(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_lcs_info, gavp);
}

/*Retrievs the first LCS-PrivacyException group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which LCS-PrivacyException group avp is searched.
		gavp : a pointer to LCS-PrivacyException group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_lcs_privacyexception(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_lcs_privacyexception, gavp);
}

/*Retrievs the next LCS-PrivacyException group AVP 
	parameter:
		avp : a pointer to LCS-PrivacyException group AVP pointer next to which the next LCS-PrivacyException group avp is searched.
		gavp : a pointer to a LCS-PrivacyException group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_lcs_privacyexception(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_lcs_privacyexception, gavp);
}

/*Retrievs the first External-Client group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which External-Client group avp is searched.
		gavp : a pointer to External-Client group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_external_client(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_extr_cli, gavp);
}

/*Retrievs the next External-Client group AVP 
	parameter:
		avp : a pointer to External-Client group AVP pointer next to which the next External-Client group avp is searched.
		gavp : a pointer to a External-Client group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_external_client(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_extr_cli, gavp);
}

/*Retrievs the first Service-Type group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which Service-Type group avp is searched.
		gavp : a pointer to Service-Type group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_service_type(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_servc_type, gavp);
}

/*Retrievs the next Service-Type group AVP 
	parameter:
		avp : a pointer to Service-Type group AVP pointer next to which the next Service-Type group avp is searched.
		gavp : a pointer to a Service-Type group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_service_type(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_servc_type, gavp);
}

/*Retrievs the first MO-LR group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which MO-LR group avp is searched.
		gavp : a pointer to MO-LR group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_mo_lr(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mo_lr, gavp);
}

/*Retrievs the next MO-LR group AVP 
	parameter:
		avp : a pointer to MO-LR group AVP pointer next to which the next MO-LR group avp is searched.
		gavp : a pointer to a MO-LR group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_mo_lr(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_mo_lr, gavp);
}

/*Retrievs the first Teleservice-List group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which Teleservice-List group avp is searched.
		gavp : a pointer to Teleservice-List group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_teleservice_list(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_teleservice_list, gavp);
}

/*Retrievs the first Call-Barring-Info group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which Call-Barring-Info group avp is searched.
		gavp : a pointer to Call-Barring-Info group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_call_barring_info(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_call_barr_info, gavp);
}

/*Retrievs the next Call-Barring-Info group AVP 
	parameter:
		avp : a pointer to Call-Barring-Info group AVP pointer next to which the next Call-Barring-Info group avp is searched.
		gavp : a pointer to a Call-Barring-Info group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_call_barring_info(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_call_barr_info, gavp);
}

/*Retrievs AMBR group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which AMBR group avp is searched.
		gavp : a pointer to AMBR group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_ambr(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_ambr, gavp);
}

/*Retrievs APN-Configuration-Profile group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which APN-Configuration-Profile group avp is searched.
		gavp : a pointer to APN-Configuration-Profile group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_apn_configuration_profile(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_apn_conf_prof, gavp);
}

/*Retrievs the first APN-Configuration group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which APN-Configuration group avp is searched.
		gavp : a pointer to APN-Configuration group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_apn_configuration(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_apn_conf, gavp);
}

/*Retrievs the next APN-Configuration group AVP 
	parameter:
		avp : a pointer to APN-Configuration group AVP pointer next to which the next APN-Configuration group avp is searched.
		gavp : a pointer to a APN-Configuration group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_apn_configuration(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_apn_conf, gavp);
}

/*Retrievs the first EPS-Subscribed-QoS-Profile group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which EPS-Subscribed-QoS-Profile group avp is searched.
		gavp : a pointer to EPS-Subscribed-QoS-Profile group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_eps_subscribed_qos_profile(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_eps_subscd_qos_prof, gavp);
}

/*Retrievs the first Allocation-Retention-Priority group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which Allocation-Retention-Priority group avp is searched.
		gavp : a pointer to Allocation-Retention-Priority group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_allocation_retention_priority(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_alloc_retention_prio, gavp);
}

/*Retrievs the first WLAN-offloadability group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which WLAN-offloadability group avp is searched.
		gavp : a pointer to WLAN-offloadability group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_wlan_offloadability(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_wlan_offloadability, gavp);
}

/*Retrievs the first Trace-Data group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which Trace-Data group avp is searched.
		gavp : a pointer to Trace-Data group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_trace_data(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_trace_data, gavp);
}

/*Retrievs the first MDT-Configuration group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which MDT-Configuration group avp is searched.
		gavp : a pointer to MDT-Configuration group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_mdt_configuration(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mdt_conf, gavp);
}

/*Retrievs the first Area-Scope group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which Area-Scope group avp is searched.
		gavp : a pointer to Area-Scope group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_area_scope(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_area_scope, gavp);
}

/*Retrievs the first GPRS-Subscription-Data group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which GPRS-Subscription-Data group avp is searched.
		gavp : a pointer to GPRS-Subscription-Data group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_gprs_subscription_data(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_gprs_subsc_data, gavp);
}

/*Retrievs the first PDP-Context group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which PDP-Context group avp is searched.
		gavp : a pointer to PDP-Context group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_pdp_context(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_pdp_context, gavp);
}

/*Retrievs the next PDP-Context group AVP 
	parameter:
		avp : a pointer to PDP-Context group AVP pointer next to which the next PDP-Context group avp is searched.
		gavp : a pointer to a PDP-Context group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_pdp_context(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_pdp_context, gavp);
}

/*Retrievs the first CSG-Subscription-Data group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which CSG-Subscription-Data group avp is searched.
		gavp : a pointer to CSG-Subscription-Data group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_csg_subscription_data(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_csg_subsc_data, gavp);
}

/*Retrievs the next CSG-Subscription-Data group AVP 
	parameter:
		avp : a pointer to CSG-Subscription-Data group AVP pointer next to which the next CSG-Subscription-Data group avp is searched.
		gavp : a pointer to a CSG-Subscription-Data group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_csg_subscription_data(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_csg_subsc_data, gavp);
}

/*Retrievs ProSe-Subscription-Data group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which ProSe-Subscription-Data group avp is searched.
		gavp : a pointer to ProSe-Subscription-Data group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_prose_subscription_data(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_prose_subsc_data, gavp);
}

/*Retrievs Requested-EUTRAN-Authentication-Info group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which Requested-EUTRAN-Authentication-Info group avp is searched.
		gavp : a pointer to Requested-EUTRAN-Authentication-Info group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_requested_eutran_authentication_info(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_req_eutran_auth_info, gavp);
}

/*Retrievs Requested-UTRAN-GERAN-Authentication-Info group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which Requested-UTRAN-GERAN-Authentication-Info group avp is searched.
		gavp : a pointer to Requested-UTRAN-GERAN-Authentication-Info group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_requested_utran_geran_authentication_info(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_req_utran_geran_auth_info, gavp);
}

/*Retrievs Authentication-Info group AVP from message
	parameter:
		msg : a pointer to a message structure avp pointer in which Authentication-Info group avp is searched.
		gavp : a pointer to Authentication-Info group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_authentication_info(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_auth_info, gavp);
}

/*Retrievs the first E-UTRAN-Vector group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which E-UTRAN-Vector group avp is searched.
		gavp : a pointer to E-UTRAN-Vector group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_e_utran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_e_utran_vector, gavp);
}

/*Retrievs the next E-UTRAN-Vector group AVP 
	parameter:
		avp : a pointer to E-UTRAN-Vector group AVP pointer next to which the next E-UTRAN-Vector group avp is searched.
		gavp : a pointer to a E-UTRAN-Vector group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_e_utran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_e_utran_vector, gavp);
}

/*Retrievs the first UTRAN-Vector group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which UTRAN-Vector group avp is searched.
		gavp : a pointer to UTRAN-Vector group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_utran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_utran_vector, gavp);
}

/*Retrievs the next UTRAN-Vector group AVP 
	parameter:
		avp : a pointer to UTRAN-Vector group AVP pointer next to which the next UTRAN-Vector group avp is searched.
		gavp : a pointer to a UTRAN-Vector group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_utran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_utran_vector, gavp);
}

/*Retrievs the first GERAN-Vector group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which GERAN-Vector group avp is searched.
		gavp : a pointer to GERAN-Vector group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_geran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_geran_vector, gavp);
}

/*Retrievs the next GERAN-Vector group AVP 
	parameter:
		avp : a pointer to GERAN-Vector group AVP pointer next to which the next GERAN-Vector group avp is searched.
		gavp : a pointer to a GERAN-Vector group AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_next_geran_vector(struct avp *avp, struct avp **gavp){

	return get_gavp_next(avp, ss_geran_vector, gavp);
}

/*Retrievs the first EPS-User-State group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which EPS-User-State group avp is searched.
		gavp : a pointer to EPS-User-State group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_eps_user_state(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_eps_usr_state, gavp);
}

/*Retrievs the first MME-User-State group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which MME-User-State group avp is searched.
		gavp : a pointer to MME-User-State group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_mme_user_state(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mme_usr_state, gavp);
}

/*Retrievs the first EPS-Location-Information group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which EPS-Location-Information group avp is searched.
		gavp : a pointer to EPS-Location-Information group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_eps_location_information(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_eps_loc_info, gavp);
}

/*Retrievs the first MME-Location-Information group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which MME-Location-Information group avp is searched.
		gavp : a pointer to MME-Location-Information group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_mme_location_information(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_mme_loc_info, gavp);
}

/*Retrievs the first User-CSG-Information group AVP from group avp
	parameter:
		avp : a pointer to the group avp pointer in which User-CSG-Information group avp is searched.
		gavp : a pointer to User-CSG-Information group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_user_csg_information(struct avp *avp, struct avp **gavp){

	return get_gavp(avp, ss_usr_csg_info, gavp);
}

/*Retrievs the first Local-Time-Zone group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which Local-Time-Zone group avp is searched.
		gavp : a pointer to Local-Time-Zone group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_local_time_zone(struct msg *msg, struct avp **gavp){

	return get_gavp_msg(msg, ss_lcl_tm_zn, gavp);
}
