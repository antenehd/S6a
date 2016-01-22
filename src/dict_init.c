/*ETSI TS 129 272 V12.8.0 */
/*Avps not included:OC-Supported-Features & OC-OLR (Reason: AVP code is not defined yet)
					SGs-MME-Identity (Reason: SGs interface is not required)
					Coupled-Node-Diameter-ID (Reason: sgsn is not part of requirment)
					
*/

#include "internal.h"

/*Dictionary objects */
struct dict_object * ss_origin_host = NULL;
struct dict_object * ss_origin_realm = NULL;
struct dict_object * ss_destination_host = NULL;
struct dict_object * ss_destination_realm = NULL;
struct dict_object * ss_session_id = NULL;
struct dict_object * ss_vendor_specific_application_id = NULL;
struct dict_object * ss_auth_session_state = NULL;
struct dict_object * ss_user_name = NULL;
struct dict_object * ss_vendor_id = NULL;
struct dict_object * ss_supported_features = NULL;
struct dict_object * ss_vplmn_csg_subscription_data = NULL;
struct dict_object * ss_user_id = NULL;
struct dict_object * ss_feature_list_id = NULL;
struct dict_object * ss_feature_list = NULL;
struct dict_object * ss_terminal_information = NULL;
struct dict_object * ss_mip6_agent_info = NULL;
struct dict_object * ss_rat_type = NULL;
struct dict_object * ss_requested_eutran_authentication_info = NULL;
struct dict_object * ss_requested_utran_geran_authentication_info = NULL;
struct dict_object * ss_cancellation_type = NULL;
struct dict_object * ss_ulr_flags = NULL;
struct dict_object * ss_clr_flags = NULL;
struct dict_object * ss_idr_flags = NULL;
struct dict_object * ss_dsr_flags = NULL;
struct dict_object * ss_pur_flags = NULL;
struct dict_object * ss_ue_srvcc_capability = NULL;	
struct dict_object * ss_context_identifier = NULL;
struct dict_object * ss_service_selection = NULL;
struct dict_object * ss_alert_reason= NULL;
struct dict_object * ss_nor_flags = NULL;
struct dict_object * ss_trace_reference = NULL;
struct dict_object * ss_ts_code = NULL;
struct dict_object * ss_ss_code = NULL;
struct dict_object * ss_visited_plmn_id = NULL;
struct dict_object * ss_sgsn_number = NULL;
struct dict_object * ss_homogeneous_support_of_ims_voice_over_ps_sessions = NULL;
struct dict_object * ss_gmlc_address = NULL;
struct dict_object * ss_active_apn = NULL;
struct dict_object * ss_equivalent_plmn_list = NULL;
struct dict_object * ss_mme_number_for_mt_sms = NULL;
struct dict_object * ss_sms_register_request = NULL;
struct dict_object * ss_result_code = NULL; 
struct dict_object * ss_experimental_result = NULL;
struct dict_object * ss_error_diagnostic = NULL;
struct dict_object * ss_ims_voice_over_ps_sessions_supported = NULL;
struct dict_object * ss_last_ue_activity_time = NULL;
struct dict_object * ss_ula_flags = NULL;
struct dict_object * ss_ida_flags = NULL;
struct dict_object * ss_dsa_flags = NULL;
struct dict_object * ss_pua_flags = NULL;
struct dict_object * ss_eps_user_state = NULL;
struct dict_object * ss_eps_location_information = NULL;
struct dict_object * ss_local_time_zone = NULL;
struct dict_object * ss_subscription_data = NULL;
struct dict_object * ss_reset_id = NULL;
struct dict_object * ss_authentication_info = NULL;
struct dict_object * ss_coupled_node_diameter_id = NULL; 

/*Dictionary object for Vendor-Specific-Application-Id AVP child AVPs*/
struct dict_object * ss_auth_application_id = NULL;
/*Dictionary object for Authentication-Info AVP child AVPs*/
struct dict_object * ss_e_utran_vector = NULL;
struct dict_object * ss_utran_vector = NULL;
struct dict_object * ss_geran_vector = NULL; 

/*Dictionary object for E-UTRAN-Vector/UTRAN-Vector/GERAN-Vector AVP child AVPs*/
struct dict_object * ss_item_number = NULL;
struct dict_object * ss_rand = NULL; 
struct dict_object * ss_xres = NULL;
struct dict_object * ss_autn = NULL;
struct dict_object * ss_kasme = NULL; 		/*E-UTRAN-Vector only*/
struct dict_object * ss_confidentiality_key = NULL; 	/*UTRAN-Vector only*/
struct dict_object * ss_integrity_key = NULL;	/*UTRAN-Vector only*/
struct dict_object * ss_sres = NULL; 			/*GERAN-Vector only*/
struct dict_object * ss_kc = NULL;			/*GERAN-Vector only*/
 
/*Dictionary object for Requested-EUTRAN-Authentication-Info/equested-UTRAN-GE
RAN-Authentication-Info  AVP child AVPs*/
struct dict_object * ss_number_of_requested_vectors = NULL;
struct dict_object * ss_immediate_response_preferred = NULL; 
struct dict_object * ss_re_synchronization_info = NULL;  

/*Dictionary object for Terminal-Information AVP child AVPs*/
struct dict_object * ss_imei = NULL;
struct dict_object * ss_software_version = NULL;
struct dict_object * ss_3gpp2_meid = NULL;

/*Dictionary object for Subscription-Data AVP child AVPs*/
struct dict_object * ss_subscriber_status = NULL;
struct dict_object * ss_msisdn = NULL; 
struct dict_object * ss_a_msisdn = NULL;  
struct dict_object * ss_stn_sr = NULL; 
struct dict_object * ss_ics_indicator = NULL;
struct dict_object * ss_network_access_mode = NULL; 
struct dict_object * ss_operator_determined_barring = NULL; 
struct dict_object * ss_hplmn_odb = NULL;
struct dict_object * ss_regional_subscription_zone_code = NULL;
struct dict_object * ss_access_restriction_data = NULL;
struct dict_object * ss_apn_oi_replacement = NULL;
struct dict_object * ss_lcs_info = NULL;
struct dict_object * ss_teleservice_list = NULL;
struct dict_object * ss_call_barring_info = NULL;
struct dict_object * ss_3gpp_charging_characteristics = NULL;  
struct dict_object * ss_ambr = NULL; 
struct dict_object * ss_apn_configuration_profile = NULL;
struct dict_object * ss_rat_frequency_selection_priority_id = NULL; 
struct dict_object * ss_trace_data = NULL;
struct dict_object * ss_gprs_subscription_data = NULL;
struct dict_object * ss_csg_subscription_data = NULL; 
struct dict_object * ss_roaming_restricted_due_to_unsupported_feature = NULL;
struct dict_object * ss_subscribed_priodic_rau_tau_timer = NULL; 
struct dict_object * ss_mps_priority = NULL;
struct dict_object * ss_vplmn_lipa_allowed = NULL;
struct dict_object * ss_relay_node_indicator = NULL; 
struct dict_object * ss_mdt_user_consent = NULL;
struct dict_object * ss_subscribed_vsrvcc = NULL; 
struct dict_object * ss_prose_subscription_data = NULL;
struct dict_object * ss_subscription_data_flags = NULL;
	

/*Dictionary object for APN-Configuration-Profile AVP child AVPs*/
struct dict_object * ss_all_apn_configurations_included_indicator = NULL; 
struct dict_object * ss_apn_configuration = NULL;

/*Dictionary object for APN-Configuration AVP child AVPs*/
struct dict_object * ss_served_party_ip_address = NULL; 
struct dict_object * ss_pdn_type = NULL;
struct dict_object * ss_eps_subscribed_qos_profile = NULL; 
struct dict_object * ss_vplmn_dynamic_address_allowed = NULL;
struct dict_object * ss_visited_network_identifier = NULL;
struct dict_object * ss_pdn_gw_allocation_type = NULL; 
struct dict_object * ss_specific_apn_info = NULL;	
struct dict_object * ss_sipto_permission = NULL;
struct dict_object * ss_lipa_permission = NULL;
struct dict_object * ss_restoration_priority = NULL;
struct dict_object * ss_sipto_local_network_permission = NULL;
struct dict_object * ss_wlan_offloadability = NULL;

/*Dictionary object for EPS-Subscribed-QoS-Profile AVP child AVPs*/
struct dict_object * ss_qos_class_identifier = NULL; 
struct dict_object * ss_allocation_retention_priority = NULL;
	
/*Dictionary object for Allocation-Retention-Priority AVP child AVPs*/
struct dict_object * ss_priority_level = NULL;
struct dict_object * ss_pre_emption_capability = NULL;
struct dict_object * ss_pre_emption_vulnerability = NULL; 
 
/*Dictionary object for AMBR AVP child AVPs*/
struct dict_object * ss_max_requested_bandwidth_ul = NULL;
struct dict_object * ss_max_requested_bandwidth_dl = NULL;

/*Dictionary object for MIP6-Agent-In AVP child AVPs*/
struct dict_object * ss_mip_home_agent_address = NULL;
struct dict_object * ss_mip_home_agent_host = NULL;

/*Dictionary object for Trace-Data AVP child AVPs*/
struct dict_object * ss_trace_depth = NULL; 
struct dict_object * ss_trace_ne_type_list = NULL;
struct dict_object * ss_trace_interface_list = NULL; 
struct dict_object * ss_trace_event_list = NULL;  
struct dict_object * ss_omc_id = NULL;  
struct dict_object * ss_trace_collection_entity = NULL;  
struct dict_object * ss_mdt_configuration = NULL;

/*Dictionary object for GPRS-Subscription-Data  AVP child AVPs*/
struct dict_object * ss_complete_data_list_included_indicator = NULL;  
struct dict_object * ss_pdp_context = NULL;
	
/*Dictionary object for PDP-Context  AVP child AVPs*/
struct dict_object * ss_pdp_type = NULL; 
struct dict_object * ss_pdp_address = NULL; 
struct dict_object * ss_qos_subscribed = NULL;
struct dict_object * ss_ext_pdp_type = NULL;
struct dict_object * ss_ext_pdp_address = NULL;  

/*Dictionary object for CSG-Subscription-Data  AVP child AVPs*/
struct dict_object * ss_csg_id = NULL;   
struct dict_object * ss_expiration_date = NULL; 

/*Dictionary object for LCS-Info   AVP child AVPs*/
struct dict_object * ss_gmlc_number = NULL;   
struct dict_object * ss_lcs_privacyexception = NULL;
struct dict_object * ss_mo_lr = NULL; 

/*Dictionary object for LCS-PrivacyException AVP child AVPs*/
struct dict_object * ss_ss_status = NULL; 
struct dict_object * ss_notification_to_ue_user = NULL; 
struct dict_object * ss_external_client = NULL;
struct dict_object * ss_plmn_client = NULL;
struct dict_object * ss_service_type = NULL; 

/*Dictionary object for External-Client AVP child AVPs*/
struct dict_object * ss_client_identity = NULL;
struct dict_object * ss_gmlc_restriction = NULL;
	
/*Dictionary object for Service-Type AVP child AVPs*/
struct dict_object * ss_servicetypeidentity = NULL;

/*Dictionary object for EPS-User-State AVP child AVPs*/
struct dict_object * ss_mme_user_state = NULL;
struct dict_object * ss_sgsn_user_state = NULL;	

/*Dictionary object for EPS-Location-Information AVP child AVPs*/
struct dict_object * ss_mme_location_information = NULL;
struct dict_object * ss_sgsn_locationinformation = NULL;
	 
/*Dictionary object for MME-User-State  AVP child AVPs*/
struct dict_object * ss_user_state = NULL;

/*Dictionary object for MME-LocationInformation AVP child AVPs*/
struct dict_object * ss_e_utran_cell_global_identity = NULL;
struct dict_object * ss_tracking_area_identity = NULL;
struct dict_object * ss_geographical_information = NULL;
struct dict_object * ss_geodetic_information = NULL;
struct dict_object * ss_current_location_retrieved = NULL;
struct dict_object * ss_age_of_location_information = NULL;
struct dict_object * ss_user_csg_information = NULL;

/*Dictionary object for SGSN-Location-Information AVP child AVPs*/
struct dict_object * ss_cell_global_identity = NULL;
struct dict_object * ss_location_area_identity = NULL;
struct dict_object * ss_service_area_identity = NULL;
struct dict_object * ss_routing_area_identity = NULL;

/*Dictionary object for User-CSG-Information AVP child AVPs*/
struct dict_object * ss_csg_access_mode = NULL;
struct dict_object * ss_csg_membership_indication = NULL;


/*Dictionary object for MDT-Configuration AVP child AVPs*/
struct dict_object * ss_job_type = NULL;
struct dict_object * ss_area_scope = NULL;
struct dict_object * ss_list_of_measurements = NULL;
struct dict_object * ss_reporting_trigger = NULL;
struct dict_object * ss_report_interval = NULL;
struct dict_object * ss_report_amount = NULL;
struct dict_object * ss_event_threshold_rsrp = NULL;
struct dict_object * ss_event_threshold_rsrq = NULL;
struct dict_object * ss_logging_interval = NULL;
struct dict_object * ss_logging_duration = NULL;
struct dict_object * ss_measurement_period_lte = NULL;
struct dict_object * ss_measurement_period_umts = NULL;
struct dict_object * ss_collection_period_rrm_lte = NULL;
struct dict_object * ss_collection_period_rrm_umts = NULL;
struct dict_object * ss_positioning_method = NULL;
struct dict_object * ss_measurement_quantity = NULL;
struct dict_object * ss_event_threshold_event_1f = NULL;
struct dict_object * ss_event_threshold_event_1i = NULL;
struct dict_object * ss_mdt_allowed_plmn_id = NULL;

/*Dictionary object for Local-Time-Zone AVP child AVPs*/
struct dict_object * ss_time_zone = NULL;
struct dict_object * ss_daylight_saving_time = NULL;
	
/*Dictionary object for ProSe-Subscription-Data AVP child AVPs*/
struct dict_object * ss_prose_permission = NULL;

/*Dictionary object for WLAN-offloadability AVP child AVPs*/
struct dict_object * ss_wlan_offloadability_eutran = NULL;
struct dict_object * ss_wlan_offloadability_utran = NULL;

/*Dictionary object for  Experimental-Result AVP child AVPs*/
struct dict_object * ss_experimental_result_code = NULL;

/*Dictionary object for commands*/
struct dict_object * ss_vendor = NULL;
struct dict_object * ss_app = NULL;
struct dict_object * ss_cmd_ulr = NULL;
struct dict_object * ss_cmd_ula = NULL;
struct dict_object * ss_cmd_air = NULL;
struct dict_object * ss_cmd_aia = NULL;
struct dict_object * ss_cmd_clr = NULL;
struct dict_object * ss_cmd_cla = NULL;
struct dict_object * ss_cmd_idr = NULL;
struct dict_object * ss_cmd_ida = NULL;
struct dict_object * ss_cmd_dsr = NULL;
struct dict_object * ss_cmd_dsa = NULL;
struct dict_object * ss_cmd_pur = NULL;
struct dict_object * ss_cmd_pua = NULL;
struct dict_object * ss_cmd_rsr = NULL;
struct dict_object * ss_cmd_rsa = NULL;
struct dict_object * ss_cmd_nor = NULL;
struct dict_object * ss_cmd_noa = NULL;

/*Create request and answer commands*/
/* RETURN VALUE:
 *  0      	: successfuly created.
 *  EINVAL 	: A parameter is invalid.
 *  EEXIST 	: This object is already defined in the dictionary (with conflicting data). 
 *  (other standard freediameter errors may be returned, too, with their standard meaning. Example:
 *    ENOMEM 	: Memory allocation for the new object element failed.)
*/
inline static int create_cmd(size_t cmd_code,char *cmd_name_r,char *cmd_name_a,struct dict_object **cmd_r,struct dict_object **cmd_a){
	struct dict_cmd_data data={cmd_code,cmd_name_r,CMD_FLAG_PROXIABLE | CMD_FLAG_REQUEST,CMD_FLAG_PROXIABLE | CMD_FLAG_REQUEST};
	CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_COMMAND, &data, ss_app, cmd_r));
	data.cmd_name = cmd_name_a;
	data.cmd_flag_val  = CMD_FLAG_PROXIABLE;
	CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_COMMAND, &data, ss_app, cmd_a));

	return 0;
}

/*sets rules for command struct dict_obj that need rules
*  parameter:
*		parent: pointer to 'struct dict_object'(command or AVP of type group)
*		rules_arry: a pointer to 'struct dict_rule_data' array containing the rules
* Note:make sure to declare 'struct dict_rule_data data;' before using this macro		
*/
#define	set_rule(parent,rules_arry) {													\
	int indx;																			\
	for(indx=0;indx<sizeof(rules_arry)/sizeof(rules_arry[0]);indx++){					\
		data.rule_min = rules_arry[indx].rule_min;										\
		data.rule_max = rules_arry[indx].rule_max;										\
		data.rule_position = rules_arry[indx].rule_position;							\
		data.rule_avp = rules_arry[indx].rule_avp;										\
		data.rule_order = rules_arry[indx].rule_order;									\
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, parent, NULL));	\
	}																					\
}	

/*Create dictionary objects for S6a commands*/
static int create_cmd_dict(){
	/* Application Vendor */
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_VENDOR, VENDOR_BY_NAME, "3GPP",&ss_vendor, ENOENT) );
	
	
	/* S6a/S6d Application */
	{
		struct dict_application_data data={16777251,"S6a/S6d"};
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_APPLICATION, &data, ss_vendor, &ss_app));
	}
	
	/* Create the  Update-Location-Request &  Update-Location-Answer commands */
	CHECK_FCT(create_cmd(316,"Update-Location-Request","Update-Location-Answer",&ss_cmd_ulr,&ss_cmd_ula));

	/* Create the  Authentication-Information-Request &  Authentication-Information-Answer commands */
	CHECK_FCT(create_cmd(318,"Authentication-Information-Request","Authentication-Information-Answer",&ss_cmd_air,&ss_cmd_aia));

	/* Create the  Cancel-Location-Request &  Cancel-Location-Answer commands */
	CHECK_FCT(create_cmd(317,"Cancel-Location-Request","Cancel-Location-Answer",&ss_cmd_clr,&ss_cmd_cla));

	/* Create the  Insert-Subscriber-Data-Request &  Insert-Subscriber-Data-Request-Answer commands */
	CHECK_FCT(create_cmd(319,"Insert-Subscriber-Data-Request","Insert-Subscriber-Data-Answer",&ss_cmd_idr,&ss_cmd_ida));

	/* Create the  Delete-Subscriber-Data-Request  &  Delete-Subscriber-Data-Answer commands */
	CHECK_FCT(create_cmd(320,"Delete-Subscriber-Data-Request","Delete-Subscriber-Data-Answer",&ss_cmd_dsr,&ss_cmd_dsa));
	
	/* Create the   Purge-UE-Request &   Purge-UE-Answer commands */
	CHECK_FCT(create_cmd(321,"Purge-UE-Request","Purge-UE-Answer",&ss_cmd_pur,&ss_cmd_pua));
	
	/* Create the   Reset-Request &   Reset-Answer commands */
	CHECK_FCT(create_cmd(322,"Reset-Request","Reset-Answer",&ss_cmd_rsr,&ss_cmd_rsa));
	
	/* Create the  Notify-Request &  Notify-Answer commands */
	CHECK_FCT(create_cmd(323,"Notify-Request","Notify-Answer",&ss_cmd_nor,&ss_cmd_noa));

	return 0;
}

/*Creates rules S6a command objects.*/
static int create_cmd_rule(){
		struct dict_rule_data data;

		data.rule_min = 1;
		data.rule_max = 1;

		/* Session-Id is in first position */
		data.rule_avp = ss_session_id;
		data.rule_position = RULE_FIXED_HEAD;
		data.rule_order = 1;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_cla, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pua, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_noa, NULL));


		/***************************************/
		/*Rules for Mandatory avps*/
		/***************************************/

		data.rule_position = RULE_REQUIRED;

		/*Auth-Session-State*/
		data.rule_avp = ss_auth_session_state;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));
	
		/*Origin-Host*/
		data.rule_avp = ss_origin_host;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_cla, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pua, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_noa, NULL));

		/*Origin-Realm*/
		data.rule_avp = ss_origin_realm;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_cla, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pua, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_noa, NULL));
		
		/*Destination-host*/
		data.rule_avp = ss_destination_host;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));


		/*Destination-Realm*/
		data.rule_avp = ss_destination_realm;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));

		/*User-Name*/
		data.rule_avp = ss_user_name;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));

		/*RAT-type*/
		data.rule_avp = ss_rat_type;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));

		/*ULR-Flags*/
		data.rule_avp = ss_ulr_flags;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));

		/*DSR-Flags*/
		data.rule_avp = ss_dsr_flags;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));

		/*Visited-PLMN-Id*/
		data.rule_avp = ss_visited_plmn_id;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));

		/*Cancellation-Type*/
		data.rule_avp = ss_cancellation_type;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		
		/*Subscription-Data*/
		data.rule_avp = ss_subscription_data;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));

		
		/*****************************************************************************************/
		/*Rules for Optional avps with maximum occurance of 1*/
		/*****************************************************************************************/
	
		data.rule_position = RULE_OPTIONAL;
		data.rule_min = 0;

		/*Vendor-Specific-Application-Id*/
		data.rule_avp = ss_vendor_specific_application_id;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_cla, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pua, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_noa, NULL));
		
		/*Destination-host*/
		data.rule_avp = ss_destination_host;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));	
		
		/*Terminal-Information*/
		data.rule_avp = ss_terminal_information;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));	

		/*GMLC-Address*/
		data.rule_avp = ss_gmlc_address;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));

		/*Result-Code*/
		data.rule_avp = ss_result_code;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_cla, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pua, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_noa, NULL));

		/*Experimental-Result*/
		data.rule_avp = ss_experimental_result;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_cla, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pua, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_noa, NULL));

		/*Error-Diagnostic*/
		data.rule_avp = ss_error_diagnostic;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));


		/*ULA-Flags*/
		data.rule_avp = ss_ula_flags;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));

		/*Subscription-Data*/
		data.rule_avp = ss_subscription_data;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));

		/*Requested-EUTRAN-Authentication-Info*/
		data.rule_avp = ss_requested_eutran_authentication_info;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));
	
		/*Requested-UTRAN-GERAN-Authentication-Info*/
		data.rule_avp = ss_requested_utran_geran_authentication_info;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));

		/*Authentication-Info*/
		data.rule_avp = ss_authentication_info;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));

		/*CLR-Flags*/
		data.rule_avp = ss_clr_flags;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));

		/*IDR- Flags*/
		data.rule_avp = ss_idr_flags;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));

		/*IMS-Voice-Over-PS-Sessions-Supported*/
		data.rule_avp = ss_ims_voice_over_ps_sessions_supported;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));

		/*Last-UE-Activity-Time*/
		data.rule_avp = ss_last_ue_activity_time;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));	

		/* RAT-Type*/
		data.rule_avp = ss_rat_type;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));

		/*IDA-Flags */
		data.rule_avp = ss_ida_flags;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		
		/* EPS-User-State*/
		data.rule_avp = ss_eps_user_state;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));

		/* EPS-Location-Information*/
		data.rule_avp = ss_eps_location_information;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));

		/* Local-Time-Zone*/
		data.rule_avp = ss_local_time_zone;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
	
		/* Trace-Reference*/
		data.rule_avp = ss_trace_reference;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));		

		/*  DSA-Flags*/
		data.rule_avp = ss_dsa_flags;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsa, NULL));	

		/* PUR-Flags*/
		data.rule_avp = ss_pur_flags;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));		

		/*  PUA-Flags*/
		data.rule_avp = ss_pua_flags;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pua, NULL));	

		/* MIP6-Agent-Info*/
		data.rule_avp = ss_mip6_agent_info;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));
		
		/*UE-SRVCC-Capability*/	
		data.rule_avp = ss_ue_srvcc_capability;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));

		/*SGSN-Number*/
		data.rule_avp = ss_sgsn_number;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));

		/*Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions*/	
		data.rule_avp = ss_homogeneous_support_of_ims_voice_over_ps_sessions;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));

		/*Equivalent-PLMN-List*/
		data.rule_avp = ss_equivalent_plmn_list;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));

		/*MME-Number-for-MT-SMS*/
		data.rule_avp = ss_mme_number_for_mt_sms;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));

		/*SMS-Register-Request*/
		data.rule_avp = ss_sms_register_request;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
	
		/*  Visited-Network-Identifier*/
		data.rule_avp = ss_visited_network_identifier;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));

		/*Context-Identifier*/
		data.rule_avp = ss_context_identifier;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));		

		/*Service-Selection*/
		data.rule_avp = ss_service_selection;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));	
	
		/*Alert-Reason*/
		data.rule_avp = ss_alert_reason;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));

		/*NOR-Flags*/
		data.rule_avp = ss_nor_flags;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));		



		
		/***********************************************************************************************/
		/*Rules for Optional avps with unlimited maximum occurance*/
		/***********************************************************************************************/	
		data.rule_position = RULE_OPTIONAL;
		data.rule_max = -1;
		
		/*Supported-Features*/
		data.rule_avp = ss_supported_features;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_cla, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pua, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_noa, NULL));
	
		/*Active-APN*/
		data.rule_avp = ss_active_apn;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		
		/*Reset-ID*/
		data.rule_avp = ss_reset_id;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));

		/*Context-Identifier*/
		data.rule_avp = ss_context_identifier;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));	

		/*TS-Code*/
		data.rule_avp = ss_ts_code;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));	

		/*SS-Code*/
		data.rule_avp = ss_ss_code;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));	
			
		/*User-Id*/
		data.rule_avp = ss_user_id;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));	

	return 0;
}

/*Create rules for grouped AVPs*/
static int create_gavp_rule(){

	struct dict_rule_data data;

		/*Rules for Subscription-Data AVP*/
		{
			 struct dict_rule_data rules[]={
				{/*Subscriber-Status*/ ss_subscriber_status,RULE_OPTIONAL,0,0,1},
				{/*MSISDN*/ ss_msisdn,RULE_OPTIONAL,0,0,1},
				{/*A-MSISDN*/ ss_a_msisdn,RULE_OPTIONAL,0,0,1},
				{/*STN-SR*/ ss_stn_sr,RULE_OPTIONAL,0,0,1},
				{/*ICS-Indicator*/ ss_ics_indicator,RULE_OPTIONAL,0,0,1},
				{/*Network-Access-Mode*/ ss_network_access_mode,RULE_OPTIONAL,0,0,1},
				{/*Operator-Determined-Barring*/ ss_operator_determined_barring,RULE_OPTIONAL,0,0,1},
				{/*HPLMN-ODB*/ ss_hplmn_odb,RULE_OPTIONAL,0,0,1},
				{/*Regional-Subscription-Zone-Code*/ ss_regional_subscription_zone_code,RULE_OPTIONAL,0,0,10},
				{/*Access-Restriction-Data*/ ss_access_restriction_data,RULE_OPTIONAL,0,0,1},
				{/*APN-OI-Replacement*/ ss_apn_oi_replacement,RULE_OPTIONAL,0,0,1},
				{/*LCS-Info*/ ss_lcs_info,RULE_OPTIONAL,0,0,1},
				{/*Teleservice-List*/ ss_teleservice_list,RULE_OPTIONAL,0,0,1},
				{/*Call-Barring-Info*/  ss_call_barring_info,RULE_OPTIONAL,0,0,-1},
				{/*3GPP-Charging-Characteristics*/ ss_3gpp_charging_characteristics,RULE_OPTIONAL,0,0,1},
				{/*AMBR*/ ss_ambr,RULE_OPTIONAL,0,0,1},
				{/*APN-Configuration-Profile*/ ss_apn_configuration_profile,RULE_OPTIONAL,0,0,1},
				{/*RAT-Frequency-Selection-Priority-ID*/ ss_rat_frequency_selection_priority_id,RULE_OPTIONAL,0,0,1},
				{/*Trace-Data*/ ss_trace_data,RULE_OPTIONAL,0,0,1},
				{/*GPRS-Subscription-Data*/ ss_gprs_subscription_data,RULE_OPTIONAL,0,0,1},
				{/*CSG-Subscription-Data*/ ss_csg_subscription_data,RULE_OPTIONAL,0,0,-1},
				{/*Roaming-Restricted-Due-To-Unsupported-Feature*/ ss_roaming_restricted_due_to_unsupported_feature,RULE_OPTIONAL,0,0,1},
				{/*Subscribed-Periodic-RAU-TAU-Timer*/ ss_subscribed_priodic_rau_tau_timer,RULE_OPTIONAL,0,0,1},
				{/*MPS-Priority*/ ss_mps_priority,RULE_OPTIONAL,0,0,1},
				{/*VPLMN-LIPA-Allowed*/ ss_vplmn_lipa_allowed,RULE_OPTIONAL,0,0,1},
				{/*Relay-Node-Indicator*/ ss_relay_node_indicator,RULE_OPTIONAL,0,0,1},
				{/*MDT-User-Consent*/ ss_mdt_user_consent,RULE_OPTIONAL,0,0,1},
				{/*Subscribed-VSRVCC*/ ss_subscribed_vsrvcc,RULE_OPTIONAL,0,0,1},
				{/*ProSe-Subscription-Data*/ ss_prose_subscription_data,RULE_OPTIONAL,0,0,1},
				{/*Subscription-Data-Flags*/ ss_subscription_data_flags,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_subscription_data,rules);
		}
	
		/*Rules for Terminal-Information AVP*/
		{
			struct dict_rule_data rules[]={
				{/*IMEI*/ ss_imei,RULE_OPTIONAL,0,0,1},
				{/*3GPP2-MEID*/ ss_3gpp2_meid,RULE_OPTIONAL,0,0,1},
				{/*Software-Version*/ ss_software_version,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_terminal_information,rules);
		}
	
		/*Rules for Requested-EUTRAN-Authentication-Info AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Number-Of-Requested-Vectors*/ ss_number_of_requested_vectors,RULE_OPTIONAL,0,0,1},
				{/*Immediate-Response-Preferred*/ ss_immediate_response_preferred,RULE_OPTIONAL,0,0,1},
				{/*Re-synchronization-Info*/ ss_re_synchronization_info,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_requested_eutran_authentication_info,rules);
		}
		
		/*Rules for Requested-UTRAN-GERAN-Authentication-Info  AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Number-Of-Requested-Vectors*/ ss_number_of_requested_vectors,RULE_OPTIONAL,0,0,1},
				{/*Immediate-Response-Preferred*/ ss_immediate_response_preferred,RULE_OPTIONAL,0,0,1},
				{/*Re-synchronization-Info*/ ss_re_synchronization_info,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_requested_utran_geran_authentication_info,rules);
		}	

		/*Rules for Authentication-Info  AVP*/
		{
			struct dict_rule_data rules[]={
				{/*E-UTRAN-Vector*/ ss_e_utran_vector,RULE_OPTIONAL,0,0,-1},
				{/*UTRAN-Vector*/ ss_utran_vector,RULE_OPTIONAL,0,0,-1},
				{/*GERAN-Vector*/ ss_geran_vector,RULE_OPTIONAL,0,0,-1}
			};
			set_rule(ss_authentication_info,rules);
		}
	
		/*Rules for E-UTRAN-Vector  AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Item-Number*/ ss_item_number,RULE_OPTIONAL,0,0,1},
				{/*RAND*/ ss_rand,RULE_REQUIRED,0,1,1},
				{/*XRES*/ ss_xres,RULE_REQUIRED,0,1,1},
				{/*AUTN*/ ss_autn,RULE_REQUIRED,0,1,1},
				{/*KASME*/ ss_kasme,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_e_utran_vector,rules);
		}
	
		/*Rules for UTRAN-Vector AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Item-Number*/ ss_item_number,RULE_OPTIONAL,0,0,1},
				{/*RAND*/ ss_rand,RULE_REQUIRED,0,1,1},
				{/*XRES*/ ss_xres,RULE_REQUIRED,0,1,1},
				{/*AUTN*/ ss_autn,RULE_REQUIRED,0,1,1},
				{/*Confidentiality-Key*/ ss_confidentiality_key,RULE_REQUIRED,0,1,1},
				{/*Integrity-Key*/ ss_integrity_key,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_utran_vector,rules);
		}
	
		/*Rules for GERAN-Vector AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Item-Number*/ ss_item_number,RULE_OPTIONAL,0,0,1},
				{/*RAND*/ ss_rand,RULE_REQUIRED,0,1,1},
				{/*SRES*/ ss_sres,RULE_REQUIRED,0,1,1},
				{/*Kc*/ ss_kc,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_geran_vector,rules);
		}
	
		/*Rules for APN-Configuration-Profile AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Context-Identifier*/ ss_context_identifier,RULE_REQUIRED,0,1,1},
				{/*All-APN-Configurations-Included-Indicator*/ ss_all_apn_configurations_included_indicator,RULE_REQUIRED,0,1,1},
				{/*APN-Configuration*/ ss_apn_configuration,RULE_REQUIRED,0,1,-1}
			};
			set_rule(ss_apn_configuration_profile,rules);
		}
	
		/*Rules for APN-Configuration AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Context-Identifier*/ ss_context_identifier,RULE_REQUIRED,0,1,1},
				{/*Served-Party-IP-Address*/ ss_served_party_ip_address,RULE_OPTIONAL,0,0,2},
				{/*PDN-Type*/ ss_pdn_type,RULE_REQUIRED,0,1,1},
				{/*Service-Selection*/ ss_service_selection,RULE_REQUIRED,0,1,1},
				{/*EPS-Subscribed-QoS-Profile*/ ss_eps_subscribed_qos_profile,RULE_OPTIONAL,0,0,1},
				{/*VPLMN-Dynamic-Address-Allowed*/ ss_vplmn_dynamic_address_allowed,RULE_OPTIONAL,0,0,1},
				{/*MIP6-Agent-Info*/ ss_mip6_agent_info,RULE_OPTIONAL,0,0,1},
				{/*Visited-Network-Identifier*/ ss_visited_network_identifier,RULE_OPTIONAL,0,0,1},
				{/*PDN-GW-Allocation-Type*/ ss_pdn_gw_allocation_type,RULE_OPTIONAL,0,0,1},
				{/*3GPP-Charging-Characteristics*/ ss_3gpp_charging_characteristics,RULE_OPTIONAL,0,0,1},
				{/*AMBR*/ ss_ambr,RULE_OPTIONAL,0,0,1},
				{/*Specific-APN-Info*/ ss_specific_apn_info,RULE_OPTIONAL,0,0,-1},
				{/*APN-OI-Replacement*/ ss_apn_oi_replacement,RULE_OPTIONAL,0,0,1},
				{/*SIPTO-Permission*/ ss_sipto_permission,RULE_OPTIONAL,0,0,1},
				{/*LIPA-Permission*/ ss_lipa_permission,RULE_OPTIONAL,0,0,1},
				{/*Restoration-Priority*/ ss_restoration_priority,RULE_OPTIONAL,0,0,1}, 
				{/*SIPTO-Local-Network-Permission*/ ss_sipto_local_network_permission,RULE_OPTIONAL,0,0,1},
				{/*WLAN-offloadability*/ ss_wlan_offloadability,RULE_OPTIONAL,0,0,1} 
			
			};
			set_rule(ss_apn_configuration,rules);
		}
	
		/*Rules for EPS-Subscribed-QoS-Profile AVP*/
		{
			struct dict_rule_data rules[]={
				{/*QoS-Class-Identifier*/ ss_qos_class_identifier,RULE_REQUIRED,0,1,1},
				{/*Allocation-Retention-Priority*/ ss_allocation_retention_priority,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_eps_subscribed_qos_profile,rules);
		}
	
		/*Rules for Allocation-Retention-Priority AVP defined in dict_dcca_3gpp.fdx*/
		
	
		/*Rules for AMBR AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Max-Requested-Bandwidth-UL*/ ss_max_requested_bandwidth_ul,RULE_REQUIRED,0,1,1},
				{/*Max-Requested-Bandwidth-DL*/ ss_max_requested_bandwidth_dl,RULE_REQUIRED,0,1,1},
			};
			set_rule(ss_ambr,rules);
		}
	
		/*Rules for MIP6-Agent-Info AVP*/
		{
			struct dict_rule_data rules[]={
				{/*MIP-Home-Agent-Address*/ ss_mip_home_agent_address,RULE_OPTIONAL,0,0,2},
				{/*MIP-Home-Agent-Host*/ ss_mip_home_agent_host,RULE_OPTIONAL,0,0,1}			
			};
			set_rule(ss_mip6_agent_info,rules);
		}
	
		/*Rules for MIP-Home-Agent-Host AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Destination-Realm*/ ss_destination_realm,RULE_REQUIRED,0,1,1},
				{/*Destination-Host*/ ss_destination_host,RULE_REQUIRED,0,1,1},
			};
			set_rule(ss_mip_home_agent_host,rules);
		}
		
		/*Rules for Trace-Data AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Trace-Reference*/ ss_trace_reference,RULE_REQUIRED,0,1,1},
				{/*Trace-Depth*/ ss_trace_depth,RULE_REQUIRED,0,1,1},
				{/*Trace-NE-Type-List*/ ss_trace_ne_type_list,RULE_REQUIRED,0,1,1},
				{/*Trace-Interface-List*/ ss_trace_interface_list,RULE_OPTIONAL,0,0,1},
				{/*Trace-Event-List*/ ss_trace_event_list,RULE_REQUIRED,0,1,1},
				{/*OMC-Id*/ ss_omc_id,RULE_OPTIONAL,0,0,1},
				{/*Trace-Collection-Entity*/ ss_trace_collection_entity,RULE_REQUIRED,0,1,1},
				{/*MDT-Configuration*/ ss_mdt_configuration,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_trace_data,rules);
		}
		
		/*Rules for GPRS-Subscription-Data AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Complete-Data-List-Included-Indicator*/ ss_complete_data_list_included_indicator,RULE_REQUIRED,0,1,1},
				{/*PDP-Context*/ ss_pdp_context,RULE_REQUIRED,0,1,50}			
			};
			set_rule(ss_gprs_subscription_data,rules);
		}
	
		/*Rules for PDP-Context AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Context-Identifier*/ ss_context_identifier,RULE_REQUIRED,0,1,1},
				{/*PDP-Type*/ ss_pdp_type,RULE_REQUIRED,0,1,1},
				{/*PDP-Address*/ ss_pdp_address,RULE_OPTIONAL,0,0,1},
				{/*QoS-Subscribed*/ ss_qos_subscribed,RULE_REQUIRED,0,1,1},
				{/*VPLMN-Dynamic-Address-Allowed*/ ss_vplmn_dynamic_address_allowed,RULE_OPTIONAL,0,0,1},
				{/*Service-Selection*/ ss_service_selection,RULE_REQUIRED,0,1,1},
				{/*3GPP-Charging-Characteristics*/ ss_3gpp_charging_characteristics,RULE_OPTIONAL,0,0,1},
				{/*Ext-PDP-Type*/ ss_ext_pdp_type,RULE_OPTIONAL,0,0,1},
				{/*Ext-PDP-Address*/ ss_ext_pdp_address,RULE_OPTIONAL,0,0,1},
				{/*AMBR*/ ss_ambr,RULE_OPTIONAL,0,0,1},
				{/*APN-OI-Replacement*/ ss_apn_oi_replacement,RULE_OPTIONAL,0,0,1},
				{/*SIPTO-Permission*/ ss_sipto_permission,RULE_OPTIONAL,0,0,1},
				{/*LIPA-Permission*/ ss_lipa_permission,RULE_OPTIONAL,0,0,1},
				{/*Restoration-Priority*/ ss_restoration_priority,RULE_OPTIONAL,0,0,1},
				{/*SIPTO-Local-Network-Permission*/ ss_sipto_local_network_permission,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_pdp_context,rules);
		}
	
		/*Rules for CSG-Subscription-Data AVP*/
		{
			struct dict_rule_data rules[]={
				{/*CSG-Id*/ ss_csg_id,RULE_REQUIRED,0,1,1},
				{/*Expiration-Date*/ ss_expiration_date,RULE_OPTIONAL,0,0,1},
				{/*Service-Selection*/ ss_service_selection,RULE_OPTIONAL,0,0,-1},
				{/*Visited-PLMN-Id*/ ss_visited_plmn_id,RULE_OPTIONAL,0,0,1}			
			};
			set_rule(ss_csg_subscription_data,rules);
		}

		/*Rules for  Specific-APN-Info AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Service-Selection*/ ss_service_selection,RULE_REQUIRED,0,1,1},
				{/*MIP6-Agent-Info*/ ss_mip6_agent_info,RULE_REQUIRED,0,1,1},
				{/*Visited-Network-Identifier*/ ss_visited_network_identifier,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_specific_apn_info,rules);
		}
	
		/*Rules for LCS-Info  AVP*/
		{
			struct dict_rule_data rules[]={
				{/*GMLC-Number*/ ss_gmlc_number,RULE_OPTIONAL,0,0,-1},
				{/*LCS-PrivacyException*/ ss_lcs_privacyexception,RULE_OPTIONAL,0,0,-1},
				{/*MO-LR*/ ss_mo_lr,RULE_OPTIONAL,0,0,-1}			
			};
			set_rule(ss_lcs_info,rules);
		}
	
		/*Rules for LCS-PrivacyException AVP*/
		{
			struct dict_rule_data rules[]={
				{/*SS-Code*/ ss_ss_code,RULE_REQUIRED,0,1,1},
				{/*SS-Status*/ ss_ss_status,RULE_REQUIRED,0,1,1},
				{/*Notification-To-UE-User*/ ss_notification_to_ue_user,RULE_OPTIONAL,0,0,1},
				{/*External-Client*/ ss_external_client,RULE_OPTIONAL,0,0,-1},
				{/*PLMN-Client*/ ss_plmn_client,RULE_OPTIONAL,0,0,-1},
				{/*Service-Type*/ ss_service_type,RULE_OPTIONAL,0,0,-1}			
			};
			set_rule(ss_lcs_privacyexception,rules);
		}
	
		/*Rules for External-Client AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Client-Identity*/ ss_client_identity,RULE_REQUIRED,0,1,1},
				{/*GMLC-Restriction*/ ss_gmlc_restriction,RULE_OPTIONAL,0,0,1},
				{/*Notification-To-UE-User*/ ss_notification_to_ue_user,RULE_OPTIONAL,0,0,1}			
			};
			set_rule(ss_external_client,rules);
		}
	
		/*Rules for Service-Type AVP*/
		{
			struct dict_rule_data rules[]={
				{/*ServiceTypeIdentity*/ ss_servicetypeidentity,RULE_REQUIRED,0,1,1},
				{/*GMLC-Restriction*/ ss_gmlc_restriction,RULE_OPTIONAL,0,0,1},
				{/*Notification-To-UE-User*/ ss_notification_to_ue_user,RULE_OPTIONAL,0,0,1}			
			};
			set_rule(ss_service_type,rules);
		}
	
		/*Rules for MO-LR AVP*/
		{
			struct dict_rule_data rules[]={
				{/*SS-Code*/ ss_ss_code,RULE_REQUIRED,0,1,1},
				{/*SS-Status*/ ss_ss_status,RULE_REQUIRED,0,1,1}
			};
				set_rule(ss_mo_lr,rules);
		}
	
		/*Rules for Teleservice-List AVP*/
		{
			struct dict_rule_data rules[]={
				{/* TS-Code*/ ss_ts_code,RULE_REQUIRED,0,1,-1}
			};
			set_rule(ss_teleservice_list,rules);
		}
	
		/*Rules for Call-Barring-Info AVP*/
		{
			struct dict_rule_data rules[]={
				{/*SS-Code*/ ss_ss_code,RULE_REQUIRED,0,1,1},
				{/*SS-Status*/ ss_ss_status,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_call_barring_info,rules);
		}
	
		/*Rules for EPS-User-State AVP*/
		{
			struct dict_rule_data rules[]={
				{/*MME-User-State*/ ss_mme_user_state,RULE_OPTIONAL,0,0,1},
				{/*SGSN-User-State*/ ss_sgsn_user_state,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_eps_user_state,rules);
		}
	
		/*Rules for EPS-Location-Information AVP*/
		{
			struct dict_rule_data rules[]={
				{/*MME-LocationInformation*/ ss_mme_location_information,RULE_OPTIONAL,0,0,1},
				{/*SGSN-Location-Information*/ ss_sgsn_locationinformation,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_eps_location_information,rules);
		}

		/*Rules for MME-User-State AVP*/
		{
			struct dict_rule_data rules[]={
				{/*User-State*/ ss_user_state,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_mme_user_state,rules);
		}
	
		/*Rules for SGSN-User-State AVP*/
		{
			struct dict_rule_data rules[]={
				{/*User-State*/ ss_user_state,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_sgsn_user_state,rules);
		}
	
		/*Rules for MME-LocationInformation AVP*/
		{
			struct dict_rule_data rules[]={
				{/*E-UTRAN-Cell-Global-Identity*/ ss_e_utran_cell_global_identity, RULE_OPTIONAL,0,0,1},
				{/*Tracking-Area-Identity*/ ss_tracking_area_identity, RULE_OPTIONAL,0,0,1},
				{/*Geographical-Information*/ ss_geographical_information, RULE_OPTIONAL,0,0,1},
				{/*Geodetic-Information*/ ss_geodetic_information, RULE_OPTIONAL,0,0,1},
				{/*Current-Location-Retrieved*/ ss_current_location_retrieved, RULE_OPTIONAL,0,0,1},
				{/*Age-Of-Location-Information*/ ss_age_of_location_information, RULE_OPTIONAL,0,0,1},
				{/*User-CSG-Information*/ ss_user_csg_information, RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_mme_location_information,rules);
		} 

		/* Rules for User-CSG-Information AVP*/
		{
			struct dict_rule_data rules[]={
				{/*CSG-Id*/ ss_csg_id, RULE_REQUIRED, 0, 1, 1},
				{/*CSG-Access-Mode*/ ss_csg_access_mode, RULE_REQUIRED, 0, 1, 1},
				{/*CSG-Membership-Indication*/ ss_csg_membership_indication, RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_user_csg_information,rules);
		}

		/*Rules for SGSN-Location-Information AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Cell-Global-Identity*/ ss_cell_global_identity,RULE_OPTIONAL,0,0,1},
				{/*Location-Area-Identity*/ ss_location_area_identity,RULE_OPTIONAL,0,0,1},
				{/*Service-Area-Identity*/ ss_service_area_identity,RULE_OPTIONAL,0,0,1},
				{/*Routing-Area-Identity*/ ss_routing_area_identity,RULE_OPTIONAL,0,0,1},
				{/*Geographical-Information*/ ss_geographical_information,RULE_OPTIONAL,0,0,1},
				{/*Geodetic-Information*/ ss_geodetic_information,RULE_OPTIONAL,0,0,1},
				{/*Current-Location-Retrieved*/ ss_current_location_retrieved,RULE_OPTIONAL,0,0,1},
				{/*Age-Of-Location-Information*/ ss_age_of_location_information,RULE_OPTIONAL,0,0,1},
				{/*User-CSG-Information*/ ss_user_csg_information,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_sgsn_locationinformation,rules);
		}
	
		/*Rules for Active-APN AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Context-Identifier*/ ss_context_identifier,RULE_REQUIRED,0,1,1},
				{/*Service-Selection*/ ss_service_selection,RULE_OPTIONAL,0,0,1},
				{/*MIP6-Agent-Info*/ ss_mip6_agent_info,RULE_OPTIONAL,0,0,1},
				{/*Visited-Network-Identifier*/ ss_visited_network_identifier,RULE_OPTIONAL,0,0,1},
				{/*Specific-APN-Info*/ ss_specific_apn_info,RULE_OPTIONAL,0,0,-1}
			};
			set_rule(ss_active_apn,rules);
		}

		/*Rules for  MDT-Configuration AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Job-Type*/ ss_job_type,RULE_REQUIRED,0,1,1},
				{/*Area-Scope*/ ss_area_scope,RULE_OPTIONAL,0,0,1},
				{/*List-Of-Measurements*/ ss_list_of_measurements,RULE_OPTIONAL,0,0,1},
				{/*Reporting-Trigger*/ ss_reporting_trigger,RULE_OPTIONAL,0,0,1},
				{/*Report-Interval*/ ss_report_interval,RULE_OPTIONAL,0,0,1},
				{/*Report-Amount*/ ss_report_amount,RULE_OPTIONAL,0,0,1},
				{/*Event-Threshold-RSRP*/ ss_event_threshold_rsrp,RULE_OPTIONAL,0,0,1},
				{/*Event-Threshold-RSRQ*/ ss_event_threshold_rsrq,RULE_OPTIONAL,0,0,1},
				{/*Logging-Interval*/ ss_logging_interval,RULE_OPTIONAL,0,0,1},
				{/*Logging-Duration*/ ss_logging_duration,RULE_OPTIONAL,0,0,1},
				{/*Measurement-Period-LTE*/ ss_measurement_period_lte,RULE_OPTIONAL,0,0,1},
				{/*Measurement-Period-UMTS*/ ss_measurement_period_umts,RULE_OPTIONAL,0,0,1},
				{/*Collection-Period-RMM-LTE*/ ss_collection_period_rrm_lte,RULE_OPTIONAL,0,0,1},
				{/*Collection-Period-RRM-UMTS*/ ss_collection_period_rrm_umts,RULE_OPTIONAL,0,0,1},
				{/*Positioning-Method*/ ss_positioning_method,RULE_OPTIONAL,0,0,1},
				{/*Measurement-Quantity*/ ss_measurement_quantity,RULE_OPTIONAL,0,0,1},
				{/*Event-Threshold-Event-1F*/ ss_event_threshold_event_1f,RULE_OPTIONAL,0,0,1},
				{/*Event-Threshold-Event-1I*/ ss_event_threshold_event_1i,RULE_OPTIONAL,0,0,1},
				{/*MDT-Allowed-PLMN-Id*/ ss_mdt_allowed_plmn_id,RULE_OPTIONAL,0,0,-1}
			};
			set_rule(ss_mdt_configuration,rules);
		}	

		/*Rules for Area-Scope AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Cell-Global-Identity*/ ss_cell_global_identity,RULE_OPTIONAL,0,0,-1},
				{/*E-UTRAN-Cell-Global-Identity*/ ss_e_utran_cell_global_identity,RULE_OPTIONAL,0,0,-1},
				{/*Routing-Area-Identity*/ ss_routing_area_identity,RULE_OPTIONAL,0,0,-1},
				{/*Location-Area-Identity*/ ss_location_area_identity,RULE_OPTIONAL,0,0,-1},
				{/*Tracking-Area-Identity*/ ss_tracking_area_identity,RULE_OPTIONAL,0,0,-1}
			};
			set_rule(ss_area_scope,rules);
		}
	
		/*Rules for Equivalent-PLMN-List AVP*/
		{
			struct dict_rule_data rules[]={
			{/*Visited-PLMN-Id*/ ss_visited_plmn_id,RULE_REQUIRED,0,1,-1},
			};
			set_rule(ss_equivalent_plmn_list,rules);
		}
	
		/*Rules for VPLMN-CSG-Subscription-Data AVP*/
		{
			struct dict_rule_data rules[]={
				{/*CSG-Id*/ ss_csg_id,RULE_REQUIRED,0,1,1},
				{/*Expiration-Date*/ ss_expiration_date,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_vplmn_csg_subscription_data,rules);
		}
 	
		/*Rules for Local-Time-Zone AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Time-Zone*/ ss_time_zone,RULE_REQUIRED,0,1,1},
				{/*Daylight-Saving-Time*/ ss_daylight_saving_time,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_local_time_zone,rules);
		}
	
		/*Rules for ProSe-Subscription-Data AVP*/
		{
			struct dict_rule_data rules[]={
				{/*ProSe-Permission*/ ss_prose_permission,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_prose_subscription_data,rules);
		}
	
		/*Rules for WLAN-offloadability AVP*/
		{
			struct dict_rule_data rules[]={
				{/*WLAN-offloadability-EUTRAN*/ ss_wlan_offloadability_eutran,RULE_OPTIONAL,0,0,1},
				{/*WLAN-offloadability-UTRAN*/ ss_wlan_offloadability_utran,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_wlan_offloadability,rules);
		}

		/*Rules for Experimental-Result AVP*/			
		{
			struct dict_rule_data rules[]={
				{/*Vendor-Id*/ ss_vendor_id,RULE_REQUIRED,0,1,1},
				{/*Experimental-Result-Code*/ ss_experimental_result_code, RULE_REQUIRED, 0, 1, 1}
			};
			set_rule(ss_experimental_result,rules);
		}

		/*Rules for Supported-Features AVP*/			
		{
			struct dict_rule_data rules[]={
				{/*Vendor-Id*/ ss_vendor_id,RULE_REQUIRED,0,1,1},
				{/*"Feature-List-ID"*/ ss_feature_list_id, RULE_REQUIRED, 0, 1, 1},
				{/*"Feature-List"*/ ss_feature_list, RULE_REQUIRED, 0, 1, 1}
			};
			set_rule(ss_supported_features,rules);
		}	

	return 0;
}

/*Initializes command and AVP dictionary objects and set the rules*/
int ss_dict_init(){
	
	struct dict_avp_request vn;
	vn.avp_vendor = 10415;

	/*Load dictionary which contains the definition for the AVPs requered for S6a Interface*/
	if(ss_dict_load_dict()!= 0)
		fprintf(stderr, "ERROR : Error has occured in function 'ss_dict_load_dict()'\n");

	/*Create dictionary objects for S6a commands*/
	if(create_cmd_dict() != 0)
		fprintf(stderr, "ERROR : Error has occured in function 'create_cmd_dict()'\n");
		
	/*Initialize AVPs*/	
	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Origin-Host", &ss_origin_host, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Origin-Realm", &ss_origin_realm, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Destination-Host", &ss_destination_host, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Destination-Realm", &ss_destination_realm, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Session-Id", &ss_session_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Vendor-Specific-Application-Id", &ss_vendor_specific_application_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Auth-Session-State", &ss_auth_session_state, ENOENT));
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "User-Name", &ss_user_name, ENOENT) );
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Vendor-Id", &ss_vendor_id, ENOENT) );
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MIP6-Agent-Info", &ss_mip6_agent_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Result-Code", &ss_result_code, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Experimental-Result", &ss_experimental_result, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Service-Selection", &ss_service_selection, ENOENT));

	vn.avp_name = "Supported-Features";	
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_supported_features, ENOENT));
	vn.avp_name = "VPLMN-CSG-Subscription-Data";		
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_vplmn_csg_subscription_data, ENOENT) );
	vn.avp_name = "User-Id";		
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_user_id, ENOENT));
	vn.avp_name = "Feature-List-ID";			
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_feature_list_id, ENOENT));
	vn.avp_name = "Feature-List";				
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_feature_list, ENOENT));
	vn.avp_name = "Terminal-Information";				
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_terminal_information, ENOENT));
	vn.avp_name = "Alert-Reason";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_alert_reason, ENOENT));
	vn.avp_name = "RAT-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_rat_type, ENOENT));
	vn.avp_name = "ULR-Flags";			
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ulr_flags, ENOENT));
	vn.avp_name = "CLR-Flags";				
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_clr_flags, ENOENT));
	vn.avp_name = "IDR-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_idr_flags, ENOENT));
	vn.avp_name = "DSR-Flags";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_dsr_flags, ENOENT));
	vn.avp_name = "PUR-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pur_flags, ENOENT));
	vn.avp_name = "NOR-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_nor_flags, ENOENT));
	vn.avp_name = "UE-SRVCC-Capability";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ue_srvcc_capability, ENOENT));
	vn.avp_name = "Requested-EUTRAN-Authentication-Info";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_requested_eutran_authentication_info, ENOENT));
	vn.avp_name = "Requested-UTRAN-GERAN-Authentication-Info";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_requested_utran_geran_authentication_info, ENOENT));
	vn.avp_name = "Cancellation-Type"; 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_cancellation_type, ENOENT));
	vn.avp_name = "Context-Identifier"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_context_identifier, ENOENT));
	vn.avp_name = "Trace-Reference"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_reference, ENOENT));
	vn.avp_name = "TS-Code"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ts_code, ENOENT));
	vn.avp_name = "SS-Code"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ss_code, ENOENT));
	vn.avp_name = "Visited-PLMN-Id"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_visited_plmn_id, ENOENT) );
	vn.avp_name = "SGSN-Number"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sgsn_number, ENOENT) );
	vn.avp_name = "Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_homogeneous_support_of_ims_voice_over_ps_sessions, ENOENT) );
	vn.avp_name = "GMLC-Address"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_gmlc_address, ENOENT));
	vn.avp_name = "Active-APN"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_active_apn, ENOENT));
	vn.avp_name = "Equivalent-PLMN-List"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_equivalent_plmn_list, ENOENT));
	vn.avp_name = "MME-Number-for-MT-SMS";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mme_number_for_mt_sms, ENOENT));
	vn.avp_name = "SMS-Register-Request";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sms_register_request, ENOENT));
	vn.avp_name = "Error-Diagnostic";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_error_diagnostic, ENOENT));
	vn.avp_name = "IMS-Voice-Over-PS-Sessions-Supported";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ims_voice_over_ps_sessions_supported, ENOENT));
	vn.avp_name = "Last-UE-Activity-Time";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_last_ue_activity_time, ENOENT));
	vn.avp_name = "ULA-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ula_flags, ENOENT));
	vn.avp_name = "IDA-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ida_flags, ENOENT));
	vn.avp_name = "DSA-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_dsa_flags, ENOENT));
	vn.avp_name = "PUA-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pua_flags, ENOENT));
	vn.avp_name = "EPS-User-State";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_eps_user_state, ENOENT));
	vn.avp_name = "EPS-Location-Information";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_eps_location_information, ENOENT));
	vn.avp_name = "Local-Time-Zone";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_local_time_zone, ENOENT));
	vn.avp_name = "Subscription-Data";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_subscription_data, ENOENT));
	vn.avp_name = "Reset-ID";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_reset_id, ENOENT));
	vn.avp_name = "Authentication-Info";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_authentication_info, ENOENT));
	vn.avp_name = "Coupled-Node-Diameter-ID";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_coupled_node_diameter_id, ENOENT));

	/*Initialize Vendor-Specific-Application-Id child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Auth-Application-Id", &ss_auth_application_id, ENOENT));
	
	/*Initialize Authentication-Info child AVPs*/
	vn.avp_name = "E-UTRAN-Vector";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_e_utran_vector, ENOENT));
	vn.avp_name = "UTRAN-Vector";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_utran_vector, ENOENT));
	vn.avp_name = "GERAN-Vector";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_geran_vector, ENOENT));

	/*Initialize E-UTRAN-Vector/UTRAN-Vector/GERAN-Vector child AVPs*/
	vn.avp_name = "Item-Number";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_item_number, ENOENT));
	vn.avp_name = "RAND";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_rand, ENOENT));
	vn.avp_name = "XRES";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_xres, ENOENT));
	vn.avp_name = "AUTN";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_autn, ENOENT));
	vn.avp_name = "KASME";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_kasme, ENOENT));
	vn.avp_name = "Confidentiality-Key";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_confidentiality_key, ENOENT));
	vn.avp_name = "Integrity-Key";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_integrity_key, ENOENT));
	vn.avp_name = "SRES";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sres, ENOENT));
	vn.avp_name = "Kc";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_kc, ENOENT));
	
	/*Initialize Requested-EUTRAN-Authentication-Info/Requested-UTRAN-GE
RAN-Authentication-Info  child AVPs*/
	vn.avp_name = "Number-Of-Requested-Vectors";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_number_of_requested_vectors, ENOENT));
	vn.avp_name = "Immediate-Response-Preferred";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_immediate_response_preferred, ENOENT));
	vn.avp_name = "Re-Synchronization-Info";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_re_synchronization_info, ENOENT));
	
	/*Initialize Terminal-Information child AVPs*/
	vn.avp_name = "IMEI";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_imei, ENOENT));
	vn.avp_name = "Software-Version";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_software_version, ENOENT));
	vn.avp_name = "3GPP2-MEID";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_3gpp2_meid, ENOENT));

	/*Initialize Subscriber-Data child AVPs*/
	vn.avp_name = "Subscriber-Status";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_subscriber_status, ENOENT));
	vn.avp_name = "MSISDN";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_msisdn, ENOENT));
	vn.avp_name = "A-MSISDN";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_a_msisdn, ENOENT));
	vn.avp_name = "STN-SR";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_stn_sr, ENOENT));
	vn.avp_name = "ICS-Indicator";	 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ics_indicator, ENOENT));
	vn.avp_name = "Network-Access-Mode";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_network_access_mode, ENOENT));
	vn.avp_name = "Operator-Determined-Barring";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_operator_determined_barring, ENOENT));
	vn.avp_name = "HPLMN-ODB";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_hplmn_odb, ENOENT));
	vn.avp_name = "Regional-Subscription-Zone-Code";	 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_regional_subscription_zone_code, ENOENT));
	vn.avp_name = "Access-Restriction-Data";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_access_restriction_data, ENOENT));
	vn.avp_name = "APN-OI-Replacement";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_apn_oi_replacement, ENOENT));
	vn.avp_name = "LCS-Info";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_lcs_info, ENOENT));
	vn.avp_name = "Teleservice-List";	 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_teleservice_list, ENOENT));
	vn.avp_name = "Call-Barring-Info";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_call_barring_info, ENOENT));
	vn.avp_name = "3GPP-Charging-Characteristics";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_3gpp_charging_characteristics, ENOENT));
	vn.avp_name = "AMBR";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ambr, ENOENT));
	vn.avp_name = "APN-Configuration-Profile";	 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_apn_configuration_profile, ENOENT));
	vn.avp_name = "RAT-Frequency-Selection-Priority-ID";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_rat_frequency_selection_priority_id, ENOENT));
	vn.avp_name = "Trace-Data";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_data, ENOENT));
	vn.avp_name = "GPRS-Subscription-Data";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_gprs_subscription_data, ENOENT));
	vn.avp_name = "CSG-Subscription-Data";	 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_csg_subscription_data, ENOENT));
	vn.avp_name = "Roaming-Restricted-Due-To-Unsupported-Feature";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_roaming_restricted_due_to_unsupported_feature, ENOENT)); 
	vn.avp_name = "Subscribed-Periodic-RAU-TAU-Timer";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_subscribed_priodic_rau_tau_timer, ENOENT));
	vn.avp_name = "MPS-Priority";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mps_priority, ENOENT));
	vn.avp_name = "VPLMN-LIPA-Allowed";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_vplmn_lipa_allowed, ENOENT));
	vn.avp_name = "Relay-Node-Indicator";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_relay_node_indicator, ENOENT));
	vn.avp_name = "MDT-User-Consent";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mdt_user_consent, ENOENT));
	vn.avp_name = "Subscribed-VSRVCC";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_subscribed_vsrvcc, ENOENT));
	vn.avp_name = "ProSe-Subscription-Data";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_prose_subscription_data, ENOENT));
	vn.avp_name = "Subscription-Data-Flags";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_subscription_data_flags, ENOENT));	

	/*Initialize APN-Configuration-Profile child AVPs*/
	vn.avp_name = "All-APN-Configurations-Included-Indicator";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_all_apn_configurations_included_indicator, ENOENT));
	vn.avp_name = "APN-Configuration";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_apn_configuration, ENOENT));
	
	/*Initialize APN-Configuration child AVPs*/
	vn.avp_name = "Served-Party-IP-Address";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_served_party_ip_address, ENOENT));
	vn.avp_name = "PDN-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pdn_type, ENOENT));
	vn.avp_name = "EPS-Subscribed-QoS-Profile";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_eps_subscribed_qos_profile, ENOENT));
	vn.avp_name = "VPLMN-Dynamic-Address-Allowed";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_vplmn_dynamic_address_allowed, ENOENT));
	vn.avp_name = "Visited-Network-Identifier";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_visited_network_identifier, ENOENT));
	vn.avp_name = "PDN-GW-Allocation-Type";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pdn_gw_allocation_type, ENOENT));
	vn.avp_name = "Specific-APN-Info";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_specific_apn_info, ENOENT));
	vn.avp_name = "SIPTO-Permission";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sipto_permission, ENOENT));
	vn.avp_name = "LIPA-Permission";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_lipa_permission, ENOENT));
	vn.avp_name = "Restoration-Priority";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_restoration_priority, ENOENT));
	vn.avp_name = "SIPTO-Local-Network-Permission";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sipto_local_network_permission, ENOENT));
	vn.avp_name = "WLAN-offloadability";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_wlan_offloadability, ENOENT));

	/*Initialize EPS-Subscribed-QoS-Profile child AVPs*/
	vn.avp_name = "QoS-Class-Identifier";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_qos_class_identifier, ENOENT));
	vn.avp_name = "Allocation-Retention-Priority";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_allocation_retention_priority, ENOENT));

	/*Initialize Allocation-Retention-Priority AVP child AVPs*/
	vn.avp_name = "Priority-Level";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_priority_level, ENOENT));
	vn.avp_name = "Pre-emption-Capability";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pre_emption_capability, ENOENT));
	vn.avp_name = "Pre-emption-Vulnerability";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pre_emption_vulnerability, ENOENT));

	/*Initialize  AMBR AVP child AVPs*/
	vn.avp_name = "Max-Requested-Bandwidth-UL";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_max_requested_bandwidth_ul, ENOENT));
	vn.avp_name = "Max-Requested-Bandwidth-DL";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_max_requested_bandwidth_dl, ENOENT));

	/*Initialize MIP6-Agent-In AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MIP-Home-Agent-Address", &ss_mip_home_agent_address, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MIP-Home-Agent-Host", &ss_mip_home_agent_host, ENOENT));
		
	/*Initialize Trace-Data AVP child AVPs*/
	vn.avp_name = "Trace-Depth";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_depth, ENOENT));
	vn.avp_name = "Trace-NE-Type-List";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_ne_type_list, ENOENT));
	vn.avp_name = "Trace-Interface-List";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_interface_list, ENOENT));
	vn.avp_name = "Trace-Event-List";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_event_list, ENOENT));
	vn.avp_name = "OMC-Id";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_omc_id, ENOENT));
	vn.avp_name = "Trace-Collection-Entity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_collection_entity, ENOENT));
	vn.avp_name = "MDT-Configuration";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mdt_configuration, ENOENT));
	
	/*Initialize GPRS-Subscription-Data  AVP child AVPs*/
	vn.avp_name = "Complete-Data-List-Included-Indicator";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_complete_data_list_included_indicator, ENOENT));
	vn.avp_name = "PDP-Context";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pdp_context, ENOENT));

	/*Initialize PDP-Context  AVP child AVPs*/
	vn.avp_name = "PDP-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pdp_type, ENOENT));
	vn.avp_name = "PDP-Address";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pdp_address, ENOENT));
	vn.avp_name = "QoS-Subscribed";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_qos_subscribed, ENOENT));
	vn.avp_name = "Ext-PDP-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ext_pdp_type, ENOENT));
	vn.avp_name = "Ext-PDP-Address";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ext_pdp_address, ENOENT));

	/*Initialize CSG-Subscription-Data AVP child AVPs*/
	vn.avp_name = "CSG-Id";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_csg_id, ENOENT));
	vn.avp_name = "Expiration-Date";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_expiration_date, ENOENT));

	/*Initialize LCS-Info AVP child AVPs*/
	vn.avp_name = "GMLC-Number";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_gmlc_number, ENOENT));
	vn.avp_name = "LCS-PrivacyException";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_lcs_privacyexception, ENOENT));
	vn.avp_name = "MO-LR";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mo_lr, ENOENT));
 
	/*Initialize LCS-PrivacyException AVP child AVPs*/
	vn.avp_name = "SS-Status";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ss_status, ENOENT));
	vn.avp_name = "Notification-To-UE-User";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_notification_to_ue_user, ENOENT));
	vn.avp_name = "External-Client";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_external_client, ENOENT));
	vn.avp_name = "PLMN-Client";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_plmn_client, ENOENT));
	vn.avp_name = "Service-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_service_type, ENOENT));
 
	/*Initialize External-Client AVP child AVPs*/
	vn.avp_name = "Client-Identity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_client_identity, ENOENT));
	vn.avp_name = "GMLC-Restriction";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_gmlc_restriction, ENOENT));
	
	/*Initialize Service-Type AVP child AVPs*/
	vn.avp_name = "ServiceTypeIdentity";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_servicetypeidentity, ENOENT));

	/*Initialize EPS-User-State AVP child AVPs*/
	vn.avp_name = "MME-User-State";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mme_user_state, ENOENT));
	vn.avp_name = "SGSN-User-State";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sgsn_user_state, ENOENT));

	/*Initialize EPS-Location-Information AVP child AVPs*/
	vn.avp_name = "MME-Location-Information";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mme_location_information, ENOENT));
	vn.avp_name = "SGSN-Location-Information";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sgsn_locationinformation, ENOENT));
	
	/*Initialize MME-User-State  AVP child AVPs*/
	vn.avp_name = "User-State";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_user_state, ENOENT));

	/*Initialize MME-LocationInformation AVP child AVPs*/
	vn.avp_name = "E-UTRAN-Cell-Global-Identity";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_e_utran_cell_global_identity, ENOENT));
	vn.avp_name = "Tracking-Area-Identity";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_tracking_area_identity, ENOENT));
	vn.avp_name = "Geographical-Information";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_geographical_information, ENOENT));
	vn.avp_name = "Geodetic-Information";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_geodetic_information, ENOENT));
	vn.avp_name = "Current-Location-Retrieved";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_current_location_retrieved, ENOENT));
	vn.avp_name = "Age-Of-Location-Information";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_age_of_location_information, ENOENT));
	vn.avp_name = "User-CSG-Information";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_user_csg_information, ENOENT));

	/*Initialize SGSN-Location-Information AVP child AVPs*/
	vn.avp_name = "Cell-Global-Identity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_cell_global_identity, ENOENT));
	vn.avp_name = "Location-Area-Identity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_location_area_identity, ENOENT));
	vn.avp_name = "Service-Area-Identity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_service_area_identity, ENOENT));
	vn.avp_name = "Routing-Area-Identity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_routing_area_identity, ENOENT));

	/*Initialize User-CSG-Information AVP child AVPs*/
	vn.avp_name = "CSG-Access-Mode";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_csg_access_mode, ENOENT));
	vn.avp_name = "CSG-Membership-Indication";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_csg_membership_indication, ENOENT));

	/*Initialize MDT-Configuration AVP child AVPs*/
	vn.avp_name = "Job-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_job_type, ENOENT));
	vn.avp_name = "Area-Scope";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_area_scope, ENOENT));
	vn.avp_name = "List-Of-Measurements";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_list_of_measurements, ENOENT));
	vn.avp_name = "Reporting-Trigger";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_reporting_trigger, ENOENT));
	vn.avp_name = "Report-Interval";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_report_interval, ENOENT));
	vn.avp_name = "Report-Amount";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_report_amount, ENOENT));
	vn.avp_name = "Event-Threshold-RSRP";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_event_threshold_rsrp, ENOENT));
	vn.avp_name = "Event-Threshold-RSRQ";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_event_threshold_rsrq, ENOENT));
	vn.avp_name = "Logging-Interval";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_logging_interval, ENOENT));
	vn.avp_name = "Logging-Duration";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_logging_duration, ENOENT));
	vn.avp_name = "Measurement-Period-LTE";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_measurement_period_lte, ENOENT));
	vn.avp_name = "Measurement-Period-UMTS";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_measurement_period_umts, ENOENT));
	vn.avp_name = "Collection-Period-RRM-LTE";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_collection_period_rrm_lte, ENOENT));
	vn.avp_name = "Collection-Period-RRM-UMTS";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_collection_period_rrm_umts, ENOENT));
	vn.avp_name = "Positioning-Method";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_positioning_method, ENOENT));
	vn.avp_name = "Measurement-Quantity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_measurement_quantity, ENOENT));
	vn.avp_name = "Event-Threshold-Event-1F";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_event_threshold_event_1f, ENOENT));
	vn.avp_name = "Event-Threshold-Event-1I";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_event_threshold_event_1i, ENOENT));
	vn.avp_name = "MDT-Allowed-PLMN-Id";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mdt_allowed_plmn_id, ENOENT));

	/*Initialize Local-Time-Zone AVP child AVPs*/
	vn.avp_name = "Time-Zone";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_time_zone, ENOENT));
	vn.avp_name = "Daylight-Saving-Time";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_daylight_saving_time, ENOENT));

	/*Initialize ProSe-Subscription-Data AVP child AVPs*/
	vn.avp_name = "ProSe-Permission";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_prose_permission, ENOENT));
			
	/*Initialize WLAN-offloadability AVP child AVPs*/
	vn.avp_name = "WLAN-offloadability-EUTRAN";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_wlan_offloadability_eutran, ENOENT));
	vn.avp_name = "WLAN-offloadability-UTRAN";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_wlan_offloadability_utran, ENOENT));

	/*Initialize  Experimental-Result AVP child AVPs*/			
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Experimental-Result-Code", &ss_experimental_result_code, ENOENT));


	/*Creates rules for S6a command objects.*/
	if( 0 != create_cmd_rule()){

		fprintf(stderr, "ERROR : Error has occured in function 'create_cmd_rule'\n");
		return 1;
	}
	
	/*Create rules for grouped AVPs*/
	if( 0 != create_gavp_rule()){

		fprintf(stderr, "ERROR : Error has occured in function 'create_gavp_rule'\n");
		return 1;
	}

	return 0;

}	
