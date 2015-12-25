/*ETSI TS 129 272 V12.8.0 */
/*Avps not included:OC-Supported-Features (Reason: AVP code is not defined yet)
					SGs-MME-Identity (Reason: SGs interface is not required)
					Coupled-Node-Diameter-ID (Reason: sgsn is not part of requirment)
					
*/

/*Dictionary objects for parent AVP*/

#include "internal_ssix.h"

struct dict_object * ss_origin_host = NULL;
struct dict_object * ss_origin_realm = NULL;
struct dict_object * ss_dest_host = NULL;
struct dict_object * ss_dest_realm = NULL;
struct dict_object * ss_sess_id = NULL;
struct dict_object * ss_vendor_specific_app_id = NULL;
struct dict_object * ss_auth_session_state = NULL;
struct dict_object * ss_user_name = NULL;
struct dict_object * ss_vendor_id=NULL;
struct dict_object * ss_supp_featr=NULL;
struct dict_object * ss_vplmn_csg_subsc_data=NULL;
struct dict_object * ss_usr_id=NULL;
struct dict_object * ss_feature_list_id = NULL;
struct dict_object * ss_feature_list = NULL;
struct dict_object * ss_terminal_info = NULL;
struct dict_object * ss_mip6_agent_info = NULL;
struct dict_object * ss_rat_type=NULL;
struct dict_object * ss_req_eutran_auth_info=NULL;
struct dict_object * ss_req_utran_geran_auth_info=NULL;
struct dict_object * ss_cancel_type=NULL;
struct dict_object * ss_ulr_flgs=NULL;
struct dict_object * ss_clr_flgs=NULL;
struct dict_object * ss_idr_flgs=NULL;
struct dict_object * ss_dsr_flgs=NULL;
struct dict_object * ss_pur_flgs=NULL;
struct dict_object * ss_ue_srvcc_capab=NULL;	
struct dict_object * ss_context_id=NULL;
struct dict_object * ss_service_selection=NULL;
struct dict_object * ss_alert_reason= NULL;
struct dict_object * ss_nor_flgs=NULL;
struct dict_object * ss_trace_ref=NULL;
struct dict_object * ss_ts_code=NULL;
struct dict_object * ss_ss_code=NULL;
struct dict_object * ss_visited_plmn_id=NULL;
struct dict_object * ss_sgsn_num=NULL;
struct dict_object * ss_homog_suppr_ims_vop_sess=NULL;
struct dict_object * ss_gmlc_addr=NULL;
struct dict_object * ss_activ_apn=NULL;
struct dict_object * ss_eqv_plmn_list=NULL;
struct dict_object * ss_mme_num_for_mt_sms=NULL;
struct dict_object * ss_sms_reg_req=NULL;
struct dict_object * ss_result_code=NULL; 
struct dict_object * ss_exper_result=NULL;
struct dict_object * ss_err_diagnostic=NULL;
struct dict_object * ss_ims_vop_sess_suprt=NULL;
struct dict_object * ss_last_ue_actv_tm=NULL;
struct dict_object * ss_ula_flgs=NULL;
struct dict_object * ss_ida_flgs=NULL;
struct dict_object * ss_dsa_flgs=NULL;
struct dict_object * ss_pua_flgs=NULL;
struct dict_object * ss_eps_usr_state=NULL;
struct dict_object * ss_eps_loc_info=NULL;
struct dict_object * ss_lcl_tm_zn = NULL;
struct dict_object * ss_subsc_data=NULL;
struct dict_object * ss_rst_id=NULL;
struct dict_object * ss_auth_info=NULL;
struct dict_object * ss_failed_avp=NULL;
struct dict_object * ss_copl_nd_dia_id = NULL; 

/*Dictionary object for Vendor-Specific-Application-Id AVP child AVPs*/
struct dict_object * ss_auth_app_id=NULL;
/*Dictionary object for Authentication-Info AVP child AVPs*/
struct dict_object * ss_e_utran_vector=NULL;
struct dict_object * ss_utran_vector=NULL;
struct dict_object * ss_geran_vector=NULL; 

/*Dictionary object for E-UTRAN-Vector/UTRAN-Vector/GERAN-Vector AVP child AVPs*/
struct dict_object * ss_item_num=NULL;
struct dict_object * ss_rand=NULL; 
struct dict_object * ss_xres=NULL;
struct dict_object * ss_autn=NULL;
struct dict_object * ss_kasme=NULL; 		/*E-UTRAN-Vector only*/
struct dict_object * ss_confid_key=NULL; 	/*UTRAN-Vector only*/
struct dict_object * ss_integrity_key=NULL;	/*UTRAN-Vector only*/
struct dict_object * ss_sres=NULL; 			/*GERAN-Vector only*/
struct dict_object * ss_kc=NULL;			/*GERAN-Vector only*/
 
/*Dictionary object for Requested-EUTRAN-Authentication-Info/equested-UTRAN-GE
RAN-Authentication-Info  AVP child AVPs*/
struct dict_object * ss_num_of_req_vects=NULL;
struct dict_object * ss_immdt_res_prefrd=NULL; 
struct dict_object * ss_re_synch_info=NULL;  

/*Dictionary object for Terminal-Information AVP child AVPs*/
struct dict_object * ss_imei = NULL;
struct dict_object * ss_soft_version=NULL;
struct dict_object * ss_meid=NULL;

/*Dictionary object for Subscription-Data AVP child AVPs*/
struct dict_object * ss_subscr_status=NULL;
struct dict_object * ss_msisdn=NULL; 
struct dict_object * ss_a_msisdn=NULL;  
struct dict_object * ss_stn_sr=NULL; 
struct dict_object * ss_ics_indicator=NULL;
struct dict_object * ss_net_access_mode=NULL; 
struct dict_object * ss_operator_det_barring=NULL; 
struct dict_object * ss_hplmn_odb=NULL;
struct dict_object * ss_regional_subscrip_zone_code=NULL;
struct dict_object * ss_access_restrict_data=NULL;
struct dict_object * ss_apn_oi_replacement=NULL;
struct dict_object * ss_lcs_info=NULL;
struct dict_object * ss_teleservice_list=NULL;
struct dict_object * ss_call_barr_info=NULL;
struct dict_object * ss_3gpp_charging_char=NULL;  
struct dict_object * ss_ambr=NULL; 
struct dict_object * ss_apn_conf_prof=NULL;
struct dict_object * ss_rat_freq_sel_prior_id=NULL; 
struct dict_object * ss_trace_data=NULL;
struct dict_object * ss_gprs_subsc_data=NULL;
struct dict_object * ss_csg_subsc_data=NULL; 
struct dict_object * ss_roam_restr_dueto_unsuppr_featr=NULL;
struct dict_object * ss_subscr_priod_rau_tau_timer=NULL; 
struct dict_object * ss_mps_prio=NULL;
struct dict_object * ss_vplmn_lipa_allow=NULL;
struct dict_object * ss_rely_nod_ind=NULL; 
struct dict_object * ss_mdt_usr_consent=NULL;
struct dict_object * ss_subscr_vsrvcc=NULL; 
struct dict_object * ss_prose_subsc_data=NULL;
struct dict_object * ss_subsc_data_flgs=NULL;
	

/*Dictionary object for APN-Configuration-Profile AVP child AVPs*/
struct dict_object * ss_all_apn_config_incl_ind=NULL; 
struct dict_object * ss_apn_conf=NULL;

/*Dictionary object for APN-Configuration AVP child AVPs*/
struct dict_object * ss_servd_party_ip_addr=NULL; 
struct dict_object * ss_pdn_type=NULL;
struct dict_object * ss_eps_subscd_qos_prof=NULL; 
struct dict_object * ss_vplmn_dyn_addr_allowed=NULL;
struct dict_object * ss_vistd_net_id=NULL;
struct dict_object * ss_pdn_gw_alloc_type=NULL; 
struct dict_object * ss_specific_apn_info=NULL;	
struct dict_object * ss_sipto_permis=NULL;
struct dict_object * ss_lipa_permis=NULL;
struct dict_object * ss_restor_prio=NULL;
struct dict_object * ss_sipto_local_net_permis=NULL;
struct dict_object * ss_wlan_offloadability=NULL;

/*Dictionary object for EPS-Subscribed-QoS-Profile AVP child AVPs*/
struct dict_object * ss_qos_class_id=NULL; 
struct dict_object * ss_alloc_retention_prio=NULL;
	
/*Dictionary object for Allocation-Retention-Priority AVP child AVPs*/
struct dict_object * ss_prio_level=NULL;
struct dict_object * ss_pre_emp_capb=NULL;
struct dict_object * ss_pre_emp_vuln=NULL; 
 
/*Dictionary object for AMBR AVP child AVPs*/
struct dict_object * ss_max_req_band_ul=NULL;
struct dict_object * ss_max_req_band_dl=NULL;

/*Dictionary object for MIP6-Agent-In AVP child AVPs*/
struct dict_object * ss_mip_home_agent_addr=NULL;
struct dict_object * ss_mip_home_agen_host=NULL;

/*Dictionary object for Trace-Data AVP child AVPs*/
struct dict_object * ss_trace_depth=NULL; 
struct dict_object * ss_trace_ne_type_list=NULL;
struct dict_object * ss_trace_interf_list=NULL; 
struct dict_object * ss_trace_event_list=NULL;  
struct dict_object * ss_omc_id=NULL;  
struct dict_object * ss_trace_coll_entity=NULL;  
struct dict_object * ss_mdt_conf=NULL;

/*Dictionary object for GPRS-Subscription-Data  AVP child AVPs*/
struct dict_object * ss_complete_data_list_incl_ind=NULL;  
struct dict_object * ss_pdp_context=NULL;
	
/*Dictionary object for PDP-Context  AVP child AVPs*/
struct dict_object * ss_pdp_type=NULL; 
struct dict_object * ss_pdp_addr=NULL; 
struct dict_object * ss_qos_subscr=NULL;
struct dict_object * ss_ext_pdp_type=NULL;
struct dict_object * ss_ext_pdp_addr=NULL;  

/*Dictionary object for CSG-Subscription-Data  AVP child AVPs*/
struct dict_object * ss_csg_id=NULL;   
struct dict_object * ss_expir_date=NULL; 

/*Dictionary object for LCS-Info   AVP child AVPs*/
struct dict_object * ss_gmlc_num=NULL;   
struct dict_object * ss_lcs_privacyexception=NULL;
struct dict_object * ss_mo_lr=NULL; 

/*Dictionary object for LCS-PrivacyException AVP child AVPs*/
struct dict_object * ss_ss_status=NULL; 
struct dict_object * ss_notif_to_ue_user=NULL; 
struct dict_object * ss_extr_cli=NULL;
struct dict_object * ss_plmn_cli=NULL;
struct dict_object * ss_servc_type=NULL; 

/*Dictionary object for External-Client AVP child AVPs*/
struct dict_object * ss_cli_id=NULL;
struct dict_object * ss_gmlc_restr=NULL;
	
/*Dictionary object for Service-Type AVP child AVPs*/
struct dict_object * ss_servctypeid=NULL;

/*Dictionary object for EPS-User-State AVP child AVPs*/
struct dict_object * ss_mme_usr_state=NULL;
struct dict_object * ss_sgsn_usr_state=NULL;	

/*Dictionary object for EPS-Location-Information AVP child AVPs*/
struct dict_object * ss_mme_loc_info = NULL;
struct dict_object * ss_sgsn_loc_info = NULL;
	 
/*Dictionary object for MME-User-State  AVP child AVPs*/
struct dict_object * ss_usr_state=NULL;

/*Dictionary object for MME-LocationInformation AVP child AVPs*/
struct dict_object * ss_e_utran_cell_glb_id = NULL;
struct dict_object * ss_track_area_id = NULL;
struct dict_object * ss_geo_info = NULL;
struct dict_object * ss_geodetic_info = NULL;
struct dict_object * ss_curr_loc_retrvd = NULL;
struct dict_object * ss_age_of_loc_info = NULL;
struct dict_object * ss_usr_csg_info = NULL;

/*Dictionary object for SGSN-Location-Information AVP child AVPs*/
struct dict_object * ss_cell_glb_id = NULL;
struct dict_object * ss_loc_area_id = NULL;
struct dict_object * ss_servc_area_id = NULL;
struct dict_object * ss_rout_area_id = NULL;

/*Dictionary object for User-CSG-Information AVP child AVPs*/
struct dict_object * ss_csg_accss_mode = NULL;
struct dict_object * ss_csg_memb_ind = NULL;


/*Dictionary object for MDT-Configuration AVP child AVPs*/
struct dict_object * ss_job_type = NULL;
struct dict_object * ss_area_scope = NULL;
struct dict_object * ss_list_of_measr = NULL;
struct dict_object * ss_repor_trig = NULL;
struct dict_object * ss_repor_intrv = NULL;
struct dict_object * ss_repor_amount = NULL;
struct dict_object * ss_evt_thrsd_rsrp = NULL;
struct dict_object * ss_evt_thrsd_rsrq = NULL;
struct dict_object * ss_log_intrv = NULL;
struct dict_object * ss_log_dur = NULL;
struct dict_object * ss_measr_perd_lte = NULL;
struct dict_object * ss_measr_perd_umts = NULL;
struct dict_object * ss_coll_perd_rrm_lte = NULL;
struct dict_object * ss_coll_perd_rrm_umts = NULL;
struct dict_object * ss_pos_meth = NULL;
struct dict_object * ss_measr_quant = NULL;
struct dict_object * ss_evt_thrsd_evt_1f = NULL;
struct dict_object * ss_evt_thrsd_evt_1i = NULL;
struct dict_object * ss_mdt_allow_plmn_id = NULL;

/*Dictionary object for Local-Time-Zone AVP child AVPs*/
struct dict_object * ss_tm_zn = NULL;
struct dict_object * ss_daylit_sv_tm = NULL;
	
/*Dictionary object for ProSe-Subscription-Data AVP child AVPs*/
struct dict_object * ss_prose_permis = NULL;

/*Dictionary object for WLAN-offloadability AVP child AVPs*/
struct dict_object * ss_wlan_offloadability_eutran = NULL;
struct dict_object * ss_wlan_offloadability_utran = NULL;

/*Dictionary object for  Experimental-Result AVP child AVPs*/
struct dict_object * ss_exper_res_code = NULL;

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
 *  1      	: successfuly created.
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

	return 1;
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
							

int ss_dict_init(){
	
	struct dict_avp_request vn;
	vn.avp_vendor = 10415;
		
	/*Define 'Service-Selection' AVP, type is UTF8String */
	{
		struct dict_object * UTF8String_type;
		CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_TYPE, TYPE_BY_NAME,"UTF8String", &UTF8String_type, ENOENT));
		struct dict_avp_data data = {
			493,	/* Code */
			0,	/* Vendor */
			"Service-Selection",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			0 ,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};		
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, UTF8String_type, NULL));
	}	

	/*Define 'Reset-ID' AVP */
	{
		struct dict_avp_data data = {
			1670,	/* Code */
			10415,	/* Vendor */
			"Reset-ID",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};		
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL));
	}

	/*Define 'MDT-Allowed-PLMN-Id' AVP */
	{
		struct dict_avp_data data = {
			1671,	/* Code */
			10415,	/* Vendor */
			"MDT-Allowed-PLMN-Id",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};		
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL));
	}

	/*Define 'Restoration-Priority' AVP */
	{
		struct dict_avp_data data = {
			1663,	/* Code */
			10415,	/* Vendor */
			"Restoration-Priority",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};		
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL));
	}

	/* Define 'SIPTO-Local-Network-Permission' AVP */
	/* This AVP is defined in '3GPP TS 29.272 version 12.8.0 Release 12' as unsigned32, but is defined */
	/* as enumerated in '3GPP TS 29.002 version 12.7.0 Release 12' and based on the values it takes its */
	/* is defined here as enumerated*/
	{
		struct dict_avp_data data = {
			1665,	/* Code */
			10415,	/* Vendor */
			"SIPTO-Local-Network-Permission",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};		
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL));
	}

	/*Define 'WLAN-offloadability' AVP */
	{
		struct dict_avp_data data = {
			1667,	/* Code */
			10415,	/* Vendor */
			"WLAN-offloadability",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};		
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL));
	}

	/*Define 'WLAN-offloadability-EUTRAN' AVP */
	{
		struct dict_avp_data data = {
			1668,	/* Code */
			10415,	/* Vendor */
			"WLAN-offloadability-EUTRAN",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
			};		
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL));
	}

	/*Define 'WLAN-offloadability-UTRAN' AVP */
	{
		struct dict_avp_data data = {
			1669,	/* Code */
			10415,	/* Vendor */
			"WLAN-offloadability-UTRAN",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
			};		
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL));
	}

	/*Define 'ProSe-Subscription-Data' AVP */
	{
		struct dict_avp_data data = {
			3701,	/* Code */
			10415,	/* Vendor */
			"ProSe-Subscription-Data",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
			};		
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL));
	}
	
	/*Define 'ProSe-Permission' AVP */
	{
		struct dict_avp_data data = {
			3702,	/* Code */
			10415,	/* Vendor */
			"ProSe-Permission",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
			};		
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL));
	}

	/*Define 'MIP6-Agent-Info' AVP */
	{
		struct dict_avp_data data = {
			486,	/* Code */
			0,	/* Vendor */
			"MIP6-Agent-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			0,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
			};		
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL));
	}

	/*Define 'MIP-Home-Agent-Address' AVP, type is address */
	{
		struct dict_object * Address_type;
		CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_TYPE, TYPE_BY_NAME,"Address", &Address_type, ENOENT));
		struct dict_avp_data data = {
			334,	/* Code */
			0,	/* Vendor */
			"MIP-Home-Agent-Address",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			0,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
			};		
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, Address_type, NULL));
	}

	/*Define 'MIP-Home-Agent-Host' AVP */
	{
		struct dict_avp_data data = {
			348,	/* Code */
			0,	/* Vendor */
			"MIP-Home-Agent-Host",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			0,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
			};		
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL));
	}

	/*Coupled-Node-Diameter-ID*/
	{
		struct dict_object * DiameterIdentity_type;
		CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_TYPE, TYPE_BY_NAME, "DiameterIdentity", &DiameterIdentity_type, ENOENT));
		struct dict_avp_data data = { 
			1666, 					/* Code */
			10415, 					/* Vendor */
			"Coupled-Node-Diameter-ID", 			/* Name */
			AVP_FLAG_VENDOR | AVP_FLAG_MANDATORY, 	/* Fixed flags */
			AVP_FLAG_VENDOR,			/* Fixed flag values */
			AVP_TYPE_OCTETSTRING 			/* base type of data */
			};
		CHECK_FCT( fd_dict_new( fd_g_config->cnf_dict,DICT_AVP, &data , DiameterIdentity_type, NULL));	
	}


	/*Initialize parent AVPs*/	
	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Origin-Host", &ss_origin_host, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Origin-Realm", &ss_origin_realm, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Destination-Host", &ss_dest_host, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Destination-Realm", &ss_dest_realm, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Session-Id", &ss_sess_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Vendor-Specific-Application-Id", &ss_vendor_specific_app_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Auth-Session-State", &ss_auth_session_state, ENOENT));
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "User-Name", &ss_user_name, ENOENT) );
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Vendor-Id", &ss_vendor_id, ENOENT) );
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MIP6-Agent-Info", &ss_mip6_agent_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Result-Code", &ss_result_code, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Experimental-Result", &ss_exper_result, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Service-Selection", &ss_service_selection, ENOENT));

	vn.avp_name = "Supported-Features";	
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_supp_featr, ENOENT));
	vn.avp_name = "VPLMN-CSG-Subscription-Data";		
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_vplmn_csg_subsc_data, ENOENT) );
	vn.avp_name = "User-Id";		
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_usr_id, ENOENT));
	vn.avp_name = "Feature-List-ID";			
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_feature_list_id, ENOENT));
	vn.avp_name = "Feature-List";				
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_feature_list, ENOENT));
	vn.avp_name = "Terminal-Information";				
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_terminal_info, ENOENT));
	vn.avp_name = "Alert-Reason";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_alert_reason, ENOENT));
	vn.avp_name = "RAT-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_rat_type, ENOENT));
	vn.avp_name = "ULR-Flags";			
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ulr_flgs, ENOENT));
	vn.avp_name = "CLR-Flags";				
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_clr_flgs, ENOENT));
	vn.avp_name = "IDR-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_idr_flgs, ENOENT));
	vn.avp_name = "DSR-Flags";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_dsr_flgs, ENOENT));
	vn.avp_name = "PUR-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pur_flgs, ENOENT));
	vn.avp_name = "NOR-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_nor_flgs, ENOENT));
	vn.avp_name = "UE-SRVCC-Capability";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ue_srvcc_capab, ENOENT));
	vn.avp_name = "Requested-EUTRAN-Authentication-Info";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_req_eutran_auth_info, ENOENT));
	vn.avp_name = "Requested-UTRAN-GERAN-Authentication-Info";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_req_utran_geran_auth_info, ENOENT));
	vn.avp_name = "Cancellation-Type"; 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_cancel_type, ENOENT));
	vn.avp_name = "Context-Identifier"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_context_id, ENOENT));
	vn.avp_name = "Trace-Reference"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_ref, ENOENT));
	vn.avp_name = "TS-Code"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ts_code, ENOENT));
	vn.avp_name = "SS-Code"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ss_code, ENOENT));
	vn.avp_name = "Visited-PLMN-Id"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_visited_plmn_id, ENOENT) );
	vn.avp_name = "SGSN-Number"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sgsn_num, ENOENT) );
	vn.avp_name = "Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_homog_suppr_ims_vop_sess, ENOENT) );
	vn.avp_name = "GMLC-Address"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_gmlc_addr, ENOENT));
	vn.avp_name = "Active-APN"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_activ_apn, ENOENT));
	vn.avp_name = "Equivalent-PLMN-List"; 		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_eqv_plmn_list, ENOENT));
	vn.avp_name = "MME-Number-for-MT-SMS";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mme_num_for_mt_sms, ENOENT));
	vn.avp_name = "SMS-Register-Request";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sms_reg_req, ENOENT));
	vn.avp_name = "Error-Diagnostic";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_err_diagnostic, ENOENT));
	vn.avp_name = "IMS-Voice-Over-PS-Sessions-Supported";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ims_vop_sess_suprt, ENOENT));
	vn.avp_name = "Last-UE-Activity-Time";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_last_ue_actv_tm, ENOENT));
	vn.avp_name = "ULA-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ula_flgs, ENOENT));
	vn.avp_name = "IDA-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ida_flgs, ENOENT));
	vn.avp_name = "DSA-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_dsa_flgs, ENOENT));
	vn.avp_name = "PUA-Flags";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pua_flgs, ENOENT));
	vn.avp_name = "EPS-User-State";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_eps_usr_state, ENOENT));
	vn.avp_name = "EPS-Location-Information";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_eps_loc_info, ENOENT));
	vn.avp_name = "Local-Time-Zone";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_lcl_tm_zn, ENOENT));
	vn.avp_name = "Subscription-Data";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_subsc_data, ENOENT));
	vn.avp_name = "Reset-ID";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_rst_id, ENOENT));
	vn.avp_name = "Authentication-Info";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_auth_info, ENOENT));
	vn.avp_name = "Coupled-Node-Diameter-ID";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_copl_nd_dia_id, ENOENT));

	/*Initialize Vendor-Specific-Application-Id child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Auth-Application-Id", &ss_auth_app_id, ENOENT));
	
	/*Initialize Authentication-Info child AVPs*/
	vn.avp_name = "E-UTRAN-Vector";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_e_utran_vector, ENOENT));
	vn.avp_name = "UTRAN-Vector";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_utran_vector, ENOENT));
	vn.avp_name = "GERAN-Vector";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_geran_vector, ENOENT));

	/*Initialize E-UTRAN-Vector/UTRAN-Vector/GERAN-Vector child AVPs*/
	vn.avp_name = "Item-Number";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_item_num, ENOENT));
	vn.avp_name = "RAND";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_rand, ENOENT));
	vn.avp_name = "XRES";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_xres, ENOENT));
	vn.avp_name = "AUTN";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_autn, ENOENT));
	vn.avp_name = "KASME";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_kasme, ENOENT));
	vn.avp_name = "Confidentiality-Key";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_confid_key, ENOENT));
	vn.avp_name = "Integrity-Key";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_integrity_key, ENOENT));
	vn.avp_name = "SRES";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sres, ENOENT));
	vn.avp_name = "Kc";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_kc, ENOENT));
	
	/*Initialize Requested-EUTRAN-Authentication-Info/Requested-UTRAN-GE
RAN-Authentication-Info  child AVPs*/
	vn.avp_name = "Number-Of-Requested-Vectors";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_num_of_req_vects, ENOENT));
	vn.avp_name = "Immediate-Response-Preferred";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_immdt_res_prefrd, ENOENT));
	vn.avp_name = "Re-Synchronization-Info";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_re_synch_info, ENOENT));
	
	/*Initialize Terminal-Information child AVPs*/
	vn.avp_name = "IMEI";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_imei, ENOENT));
	vn.avp_name = "Software-Version";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_soft_version, ENOENT));
	vn.avp_name = "3GPP2-MEID";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_meid, ENOENT));

	/*Initialize Subscriber-Data child AVPs*/
	vn.avp_name = "Subscriber-Status";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_subscr_status, ENOENT));
	vn.avp_name = "MSISDN";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_msisdn, ENOENT));
	vn.avp_name = "A-MSISDN";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_a_msisdn, ENOENT));
	vn.avp_name = "STN-SR";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_stn_sr, ENOENT));
	vn.avp_name = "ICS-Indicator";	 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ics_indicator, ENOENT));
	vn.avp_name = "Network-Access-Mode";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_net_access_mode, ENOENT));
	vn.avp_name = "Operator-Determined-Barring";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_operator_det_barring, ENOENT));
	vn.avp_name = "HPLMN-ODB";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_hplmn_odb, ENOENT));
	vn.avp_name = "Regional-Subscription-Zone-Code";	 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_regional_subscrip_zone_code, ENOENT));
	vn.avp_name = "Access-Restriction-Data";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_access_restrict_data, ENOENT));
	vn.avp_name = "APN-OI-Replacement";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_apn_oi_replacement, ENOENT));
	vn.avp_name = "LCS-Info";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_lcs_info, ENOENT));
	vn.avp_name = "Teleservice-List";	 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_teleservice_list, ENOENT));
	vn.avp_name = "Call-Barring-Infor-List";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_call_barr_info, ENOENT));
	vn.avp_name = "3GPP-Charging-Characteristics";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_3gpp_charging_char, ENOENT));
	vn.avp_name = "AMBR";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ambr, ENOENT));
	vn.avp_name = "APN-Configuration-Profile";	 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_apn_conf_prof, ENOENT));
	vn.avp_name = "RAT-Frequency-Selection-Priority-ID";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_rat_freq_sel_prior_id, ENOENT));
	vn.avp_name = "Trace-Data";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_data, ENOENT));
	vn.avp_name = "GPRS-Subscription-Data";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_gprs_subsc_data, ENOENT));
	vn.avp_name = "CSG-Subscription-Data";	 	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_csg_subsc_data, ENOENT));
	vn.avp_name = "Roaming-Restricted-Due-To-Unsupported-Feature";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_roam_restr_dueto_unsuppr_featr, ENOENT)); 
	vn.avp_name = "Subscribed-Periodic-RAU-TAU-Timer";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_subscr_priod_rau_tau_timer, ENOENT));
	vn.avp_name = "MPS-Priority";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mps_prio, ENOENT));
	vn.avp_name = "VPLMN-LIPA-Allowed";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_vplmn_lipa_allow, ENOENT));
	vn.avp_name = "Relay-Node-Indicator";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_rely_nod_ind, ENOENT));
	vn.avp_name = "MDT-User-Consent";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mdt_usr_consent, ENOENT));
	vn.avp_name = "Subscribed-VSRVCC";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_subscr_vsrvcc, ENOENT));
	vn.avp_name = "ProSe-Subscription-Data";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_prose_subsc_data, ENOENT));
	vn.avp_name = "Subscription-Data-Flags";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_subsc_data_flgs, ENOENT));	

	/*Initialize APN-Configuration-Profile child AVPs*/
	vn.avp_name = "All-APN-Configurations-Included-Indicator";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_all_apn_config_incl_ind, ENOENT));
	vn.avp_name = "APN-Configuration";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_apn_conf, ENOENT));
	
	/*Initialize APN-Configuration child AVPs*/
	vn.avp_name = "Served-Party-IP-Address";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_servd_party_ip_addr, ENOENT));
	vn.avp_name = "PDN-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pdn_type, ENOENT));
	vn.avp_name = "EPS-Subscribed-QoS-Profile";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_eps_subscd_qos_prof, ENOENT));
	vn.avp_name = "VPLMN-Dynamic-Address-Allowed";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_vplmn_dyn_addr_allowed, ENOENT));
	vn.avp_name = "Visited-Network-Identifier";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_vistd_net_id, ENOENT));
	vn.avp_name = "PDN-GW-Allocation-Type";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pdn_gw_alloc_type, ENOENT));
	vn.avp_name = "Specific-APN-Info";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_specific_apn_info, ENOENT));
	vn.avp_name = "SIPTO-Permission";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sipto_permis, ENOENT));
	vn.avp_name = "LIPA-Permission";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_lipa_permis, ENOENT));
	vn.avp_name = "Restoration-Priority";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_restor_prio, ENOENT));
	vn.avp_name = "SIPTO-Local-Network-Permission";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sipto_local_net_permis, ENOENT));
	vn.avp_name = "WLAN-offloadability";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_wlan_offloadability, ENOENT));

	/*Initialize EPS-Subscribed-QoS-Profile child AVPs*/
	vn.avp_name = "QoS-Class-Identifier";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_qos_class_id, ENOENT));
	vn.avp_name = "Allocation-Retention-Priority";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_alloc_retention_prio, ENOENT));

	/*Initialize Allocation-Retention-Priority AVP child AVPs*/
	vn.avp_name = "Priority-Level";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_prio_level, ENOENT));
	vn.avp_name = "Pre-emption-Capability";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pre_emp_capb, ENOENT));
	vn.avp_name = "Pre-emption-Vulnerability";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pre_emp_vuln, ENOENT));

	/*Initialize  AMBR AVP child AVPs*/
	vn.avp_name = "Max-Requested-Bandwidth-UL";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_max_req_band_ul, ENOENT));
	vn.avp_name = "Max-Requested-Bandwidth-DL";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_max_req_band_dl, ENOENT));

	/*Initialize MIP6-Agent-In AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MIP-Home-Agent-Address", &ss_mip_home_agent_addr, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MIP-Home-Agent-Host", &ss_mip_home_agen_host, ENOENT));
		
	/*Initialize Trace-Data AVP child AVPs*/
	vn.avp_name = "Trace-Depth";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_depth, ENOENT));
	vn.avp_name = "Trace-NE-Type-List";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_ne_type_list, ENOENT));
	vn.avp_name = "Trace-Interface-List";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_interf_list, ENOENT));
	vn.avp_name = "Trace-Event-List";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_event_list, ENOENT));
	vn.avp_name = "OMC-Id";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_omc_id, ENOENT));
	vn.avp_name = "Trace-Collection-Entity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_trace_coll_entity, ENOENT));
	vn.avp_name = "MDT-Configuration";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mdt_conf, ENOENT));
	
	/*Initialize GPRS-Subscription-Data  AVP child AVPs*/
	vn.avp_name = "Complete-Data-List-Included-Indicator";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_complete_data_list_incl_ind, ENOENT));
	vn.avp_name = "PDP-Context";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pdp_context, ENOENT));

	/*Initialize PDP-Context  AVP child AVPs*/
	vn.avp_name = "PDP-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pdp_type, ENOENT));
	vn.avp_name = "PDP-Address";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pdp_addr, ENOENT));
	vn.avp_name = "QoS-Subscribed";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_qos_subscr, ENOENT));
	vn.avp_name = "Ext-PDP-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ext_pdp_type, ENOENT));
	vn.avp_name = "Ext-PDP-Address";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ext_pdp_addr, ENOENT));

	/*Initialize CSG-Subscription-Data AVP child AVPs*/
	vn.avp_name = "CSG-Id";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_csg_id, ENOENT));
	vn.avp_name = "Expiration-Date";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_expir_date, ENOENT));

	/*Initialize LCS-Info AVP child AVPs*/
	vn.avp_name = "GMLC-Number";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_gmlc_num, ENOENT));
	vn.avp_name = "LCS-PrivacyException";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_lcs_privacyexception, ENOENT));
	vn.avp_name = "MO-LR";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mo_lr, ENOENT));
 
	/*Initialize LCS-PrivacyException AVP child AVPs*/
	vn.avp_name = "SS-Status";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_ss_status, ENOENT));
	vn.avp_name = "Notification-To-UE-User";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_notif_to_ue_user, ENOENT));
	vn.avp_name = "External-Client";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_extr_cli, ENOENT));
	vn.avp_name = "PLMN-Client";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_plmn_cli, ENOENT));
	vn.avp_name = "Service-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_servc_type, ENOENT));
 
	/*Initialize External-Client AVP child AVPs*/
	vn.avp_name = "Client-Identity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_cli_id, ENOENT));
	vn.avp_name = "GMLC-Restriction";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_gmlc_restr, ENOENT));
	
	/*Initialize Service-Type AVP child AVPs*/
	vn.avp_name = "ServiceTypeIdentity";
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_servctypeid, ENOENT));

	/*Initialize EPS-User-State AVP child AVPs*/
	vn.avp_name = "MME-User-State";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mme_usr_state, ENOENT));
	vn.avp_name = "SGSN-User-State";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sgsn_usr_state, ENOENT));

	/*Initialize EPS-Location-Information AVP child AVPs*/
	vn.avp_name = "MME-LocationInformation";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mme_loc_info, ENOENT));
	vn.avp_name = "SGSN-Location-Information";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_sgsn_loc_info, ENOENT));
	
	/*Initialize MME-User-State  AVP child AVPs*/
	vn.avp_name = "User-State";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_usr_state, ENOENT));

	/*Initialize MME-LocationInformation AVP child AVPs*/
	vn.avp_name = "E-UTRAN-Cell-Global-Identity";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_e_utran_cell_glb_id, ENOENT));
	vn.avp_name = "Tracking-Area-Identity";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_track_area_id, ENOENT));
	vn.avp_name = "Geographical-Information";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_geo_info, ENOENT));
	vn.avp_name = "Geodetic-Information";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_geodetic_info, ENOENT));
	vn.avp_name = "Current-Location-Retrieved";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_curr_loc_retrvd, ENOENT));
	vn.avp_name = "Age-Of-Location-Information";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_age_of_loc_info, ENOENT));
	vn.avp_name = "User-CSG-Information";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_usr_csg_info, ENOENT));

	/*Initialize SGSN-Location-Information AVP child AVPs*/
	vn.avp_name = "Cell-Global-Identity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_cell_glb_id, ENOENT));
	vn.avp_name = "Location-Area-Identity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_loc_area_id, ENOENT));
	vn.avp_name = "Service-Area-Identity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_servc_area_id, ENOENT));
	vn.avp_name = "Routing-Area-Identity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_rout_area_id, ENOENT));

	/*Initialize User-CSG-Information AVP child AVPs*/
	vn.avp_name = "CSG-Access-Mode";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_csg_accss_mode, ENOENT));
	vn.avp_name = "CSG-Membership-Indication";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_csg_memb_ind, ENOENT));

	/*Initialize MDT-Configuration AVP child AVPs*/
	vn.avp_name = "Job-Type";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_job_type, ENOENT));
	vn.avp_name = "Area-Scope";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_area_scope, ENOENT));
	vn.avp_name = "List-Of-Measurements";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_list_of_measr, ENOENT));
	vn.avp_name = "Reporting-Trigger";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_repor_trig, ENOENT));
	vn.avp_name = "Report-Interval";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_repor_intrv, ENOENT));
	vn.avp_name = "Report-Amount";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_repor_amount, ENOENT));
	vn.avp_name = "Event-Threshold-RSRP";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_evt_thrsd_rsrp, ENOENT));
	vn.avp_name = "Event-Threshold-RSRQ";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_evt_thrsd_rsrq, ENOENT));
	vn.avp_name = "Logging-Interval";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_log_intrv, ENOENT));
	vn.avp_name = "Logging-Duration";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_log_dur, ENOENT));
	vn.avp_name = "Measurement-Period-LTE";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_measr_perd_lte, ENOENT));
	vn.avp_name = "Measurement-Period-UMTS";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_measr_perd_umts, ENOENT));
	vn.avp_name = "Collection-Period-RRM-LTE";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_coll_perd_rrm_lte, ENOENT));
	vn.avp_name = "Collection-Period-RRM-UMTS";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_coll_perd_rrm_umts, ENOENT));
	vn.avp_name = "Positioning-Method";	
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_pos_meth, ENOENT));
	vn.avp_name = "Measurement-Quantity";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_measr_quant, ENOENT));
	vn.avp_name = "Event-Threshold-Event-1F";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_evt_thrsd_evt_1f, ENOENT));
	vn.avp_name = "Event-Threshold-Event-1I";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_evt_thrsd_evt_1i, ENOENT));
	vn.avp_name = "MDT-Allowed-PLMN-Id";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_mdt_allow_plmn_id, ENOENT));

	/*Initialize Local-Time-Zone AVP child AVPs*/
	vn.avp_name = "Time-Zone";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_tm_zn, ENOENT));
	vn.avp_name = "Daylight-Saving-Time";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_daylit_sv_tm, ENOENT));

	/*Initialize ProSe-Subscription-Data AVP child AVPs*/
	vn.avp_name = "ProSe-Permission";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_prose_permis, ENOENT));
			
	/*Initialize WLAN-offloadability AVP child AVPs*/
	vn.avp_name = "WLAN-offloadability-EUTRAN";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_wlan_offloadability_eutran, ENOENT));
	vn.avp_name = "WLAN-offloadability-UTRAN";		
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &vn, &ss_wlan_offloadability_utran, ENOENT));

	/*Initialize  Experimental-Result AVP child AVPs*/			
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Experimental-Result-Code", &ss_exper_res_code, ENOENT));


	/***********************************************************************************************************/
	/* Create command dictionary                                                                               */
	/***********************************************************************************************************/

	/* Application Vendor */
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_VENDOR, VENDOR_BY_NAME, "3GPP",&ss_vendor, ENOENT) );
	
	
	/* S6a/S6d Application */
	{
		struct dict_application_data data={16777251,"S6a/S6d"};
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_APPLICATION, &data, ss_vendor, &ss_app));
	}
	
	/* Create the  Update-Location-Request &  Update-Location-Answer commands */
	create_cmd(316,"Update-Location-Request","Update-Location-Answer",&ss_cmd_ulr,&ss_cmd_ula);

	/* Create the  Authentication-Information-Request &  Authentication-Information-Answer commands */
	create_cmd(318,"Authentication-Information-Request","Authentication-Information-Answer",&ss_cmd_air,&ss_cmd_aia);

	/* Create the  Cancel-Location-Request &  Cancel-Location-Answer commands */
	create_cmd(317,"Cancel-Location-Request","Cancel-Location-Answer",&ss_cmd_clr,&ss_cmd_cla);

	/* Create the  Insert-Subscriber-Data-Request &  Insert-Subscriber-Data-Request-Answer commands */
	create_cmd(319,"Insert-Subscriber-Data-Request","Insert-Subscriber-Data-Answer",&ss_cmd_idr,&ss_cmd_ida);

	/* Create the  Delete-Subscriber-Data-Request  &  Delete-Subscriber-Data-Answer commands */
	create_cmd(320,"Delete-Subscriber-Data-Request","Delete-Subscriber-Data-Answer",&ss_cmd_dsr,&ss_cmd_dsa);
	
	/* Create the   Purge-UE-Request &   Purge-UE-Answer commands */
	create_cmd(321,"Purge-UE-Request","Purge-UE-Answer",&ss_cmd_pur,&ss_cmd_pua);
	
	/* Create the   Reset-Request &   Reset-Answer commands */
	create_cmd(322,"Reset-Request","Reset-Answer",&ss_cmd_rsr,&ss_cmd_rsa);
	
	/* Create the  Notify-Request &  Notify-Answer commands */
	create_cmd(323,"Notify-Request","Notify-Answer",&ss_cmd_nor,&ss_cmd_noa);





	
	/*********************************************************************************************/
	/*Create rules for the commands*/
	/*********************************************************************************************/
	{
		struct dict_rule_data data;

		data.rule_min = 1;
		data.rule_max = 1;

		/* Session-Id is in first position */
		data.rule_avp = ss_sess_id;
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
		data.rule_avp = ss_dest_host;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));


		/*Destination-Realm*/
		data.rule_avp = ss_dest_realm;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_noa, NULL));

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
		data.rule_avp = ss_ulr_flgs;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));

		/*DSR-Flags*/
		data.rule_avp = ss_dsr_flgs;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));

		/*Visited-PLMN-Id*/
		data.rule_avp = ss_visited_plmn_id;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));

		/*Cancellation-Type*/
		data.rule_avp = ss_cancel_type;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));
		
		/*Subscription-Data*/
		data.rule_avp = ss_subsc_data;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));

		
		/*****************************************************************************************/
		/*Rules for Optional avps with maximum occurance of 1*/
		/*****************************************************************************************/
	
		data.rule_position = RULE_OPTIONAL;
		data.rule_min = 0;

		/*Vendor-Specific-Application-Id*/
		data.rule_avp = ss_vendor_specific_app_id;
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
		data.rule_avp = ss_dest_host;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));	
		
		/*Terminal-Information*/
		data.rule_avp = ss_terminal_info;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));	

		/*GMLC-Address*/
		data.rule_avp = ss_gmlc_addr;
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
		data.rule_avp = ss_exper_result;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_cla, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pua, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsa, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_noa, NULL));

		/*Error-Diagnostic*/
		data.rule_avp = ss_err_diagnostic;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));


		/*ULA-Flags*/
		data.rule_avp = ss_ula_flgs;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));

		/*Subscription-Data*/
		data.rule_avp = ss_subsc_data;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));

		/*Requested-EUTRAN-Authentication-Info*/
		data.rule_avp = ss_req_eutran_auth_info;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));
	
		/*Requested-UTRAN-GERAN-Authentication-Info*/
		data.rule_avp = ss_req_utran_geran_auth_info;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));

		/*Authentication-Info*/
		data.rule_avp = ss_auth_info;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_aia, NULL));

		/*CLR-Flags*/
		data.rule_avp = ss_clr_flgs;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_clr, NULL));

		/*IDR- Flags*/
		data.rule_avp = ss_idr_flgs;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));

		/*IMS-Voice-Over-PS-Sessions-Supported*/
		data.rule_avp = ss_ims_vop_sess_suprt;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));

		/*Last-UE-Activity-Time*/
		data.rule_avp = ss_last_ue_actv_tm;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));	

		/* RAT-Type*/
		data.rule_avp = ss_rat_type;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));

		/*IDA-Flags */
		data.rule_avp = ss_ida_flgs;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		
		/* EPS-User-State*/
		data.rule_avp = ss_eps_usr_state;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));

		/* EPS-Location-Information*/
		data.rule_avp = ss_eps_loc_info;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));

		/* Local-Time-Zone*/
		data.rule_avp = ss_lcl_tm_zn;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ida, NULL));
	
		/* Trace-Reference*/
		data.rule_avp = ss_trace_ref;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));		

		/*  DSA-Flags*/
		data.rule_avp = ss_dsa_flgs;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsa, NULL));	

		/* PUR-Flags*/
		data.rule_avp = ss_pur_flgs;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));		

		/*  PUA-Flags*/
		data.rule_avp = ss_pua_flgs;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pua, NULL));	

		/* MIP6-Agent-Info*/
		data.rule_avp = ss_mip6_agent_info;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));
		
		/*UE-SRVCC-Capability*/	
		data.rule_avp = ss_ue_srvcc_capab;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));

		/*SGSN-Number*/
		data.rule_avp = ss_sgsn_num;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));

		/*Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions*/	
		data.rule_avp = ss_homog_suppr_ims_vop_sess;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));

		/*Equivalent-PLMN-List*/
		data.rule_avp = ss_eqv_plmn_list;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));

		/*MME-Number-for-MT-SMS*/
		data.rule_avp = ss_mme_num_for_mt_sms;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));

		/*SMS-Register-Request*/
		data.rule_avp = ss_sms_reg_req;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
	
		/*  Visited-Network-Identifier*/
		data.rule_avp = ss_vistd_net_id;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));

		/*Context-Identifier*/
		data.rule_avp = ss_context_id;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));		

		/*Service-Selection*/
		data.rule_avp = ss_service_selection;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));	
	
		/*Alert-Reason*/
		data.rule_avp = ss_alert_reason;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));

		/*NOR-Flags*/
		data.rule_avp = ss_nor_flgs;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));		



		
		/***********************************************************************************************/
		/*Rules for Optional avps with unlimited maximum occurance*/
		/***********************************************************************************************/	
		data.rule_position = RULE_OPTIONAL;
		data.rule_max = -1;
		
		/*Supported-Features*/
		data.rule_avp = ss_supp_featr;
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
		data.rule_avp = ss_activ_apn;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));
		
		/*Reset-ID*/
		data.rule_avp = ss_rst_id;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ula, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_idr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));

		/*Context-Identifier*/
		data.rule_avp = ss_context_id;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));	

		/*TS-Code*/
		data.rule_avp = ss_ts_code;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));	

		/*SS-Code*/
		data.rule_avp = ss_ss_code;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_dsr, NULL));	
			
		/*User-Id*/
		data.rule_avp = ss_usr_id;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_rsr, NULL));	



		


		/**************************************************************************************************/
		/*Create rules for grouped AVPs																	 **/	
		/**************************************************************************************************/
	
		

		/*Rules for Subscription-Data AVP*/
		{
			 struct dict_rule_data rules[]={
				{/*Subscriber-Status*/ ss_subscr_status,RULE_OPTIONAL,0,0,1},
				{/*MSISDN*/ ss_msisdn,RULE_OPTIONAL,0,0,1},
				{/*A-MSISDN*/ ss_a_msisdn,RULE_OPTIONAL,0,0,1},
				{/*STN-SR*/ ss_stn_sr,RULE_OPTIONAL,0,0,1},
				{/*ICS-Indicator*/ ss_ics_indicator,RULE_OPTIONAL,0,0,1},
				{/*Network-Access-Mode*/ ss_net_access_mode,RULE_OPTIONAL,0,0,1},
				{/*Operator-Determined-Barring*/ ss_operator_det_barring,RULE_OPTIONAL,0,0,1},
				{/*HPLMN-ODB*/ ss_hplmn_odb,0,1,RULE_OPTIONAL},
				{/*Regional-Subscription-Zone-Code*/ ss_regional_subscrip_zone_code,RULE_OPTIONAL,0,0,10},
				{/*Access-Restriction-Data*/ ss_access_restrict_data,RULE_OPTIONAL,0,0,1},
				{/*APN-OI-Replacement*/ ss_apn_oi_replacement,RULE_OPTIONAL,0,0,1},
				{/*LCS-Info*/ ss_lcs_info,RULE_OPTIONAL,0,0,1},
				{/*Teleservice-List*/ ss_teleservice_list,RULE_OPTIONAL,0,0,1},
				{/*Call-Barring-Infor-List*/  ss_call_barr_info,RULE_OPTIONAL,0,0,-1},
				{/*3GPP-Charging-Characteristics*/ ss_3gpp_charging_char,RULE_OPTIONAL,0,0,1},
				{/*AMBR*/ ss_ambr,RULE_OPTIONAL,0,0,1},
				{/*APN-Configuration-Profile*/ ss_apn_conf_prof,RULE_OPTIONAL,0,0,1},
				{/*RAT-Frequency-Selection-Priority-ID*/ ss_rat_freq_sel_prior_id,RULE_OPTIONAL,0,0,1},
				{/*Trace-Data*/ ss_trace_data,RULE_OPTIONAL,0,0,1},
				{/*GPRS-Subscription-Data*/ ss_gprs_subsc_data,RULE_OPTIONAL,0,0,1},
				{/*CSG-Subscription-Data*/ ss_csg_subsc_data,RULE_OPTIONAL,0,0,-1},
				{/*Roaming-Restricted-Due-To-Unsupported-Feature*/ ss_roam_restr_dueto_unsuppr_featr,RULE_OPTIONAL,0,0,1},
				{/*Subscribed-Periodic-RAU-TAU-Timer*/ ss_subscr_priod_rau_tau_timer,RULE_OPTIONAL,0,0,1},
				{/*MPS-Priority*/ ss_mps_prio,RULE_OPTIONAL,0,0,1},
				{/*VPLMN-LIPA-Allowed*/ ss_vplmn_lipa_allow,RULE_OPTIONAL,0,0,1},
				{/*Relay-Node-Indicator*/ ss_rely_nod_ind,RULE_OPTIONAL,0,0,1},
				{/*MDT-User-Consent*/ ss_mdt_usr_consent,RULE_OPTIONAL,0,0,1},
				{/*Subscribed-VSRVCC*/ ss_subscr_vsrvcc,RULE_OPTIONAL,0,0,1},
				{/*ProSe-Subscription-Data*/ ss_prose_subsc_data,RULE_OPTIONAL,0,0,1},
				{/*Subscription-Data-Flags*/ ss_subsc_data_flgs,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_subsc_data,rules);
		}
	
		/*Rules for Terminal-Information AVP*/
		{
			struct dict_rule_data rules[]={
				{/*IMEI*/ ss_imei,RULE_OPTIONAL,0,0,1},
				{/*3GPP2-MEID*/ ss_meid,RULE_OPTIONAL,0,0,1},
				{/*Software-Version*/ ss_soft_version,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_terminal_info,rules);
		}
	
		/*Rules for Requested-EUTRAN-Authentication-Info AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Number-Of-Requested-Vectors*/ ss_num_of_req_vects,RULE_OPTIONAL,0,0,1},
				{/*Immediate-Response-Preferred*/ ss_immdt_res_prefrd,RULE_OPTIONAL,0,0,1},
				{/*Re-synchronization-Info*/ ss_re_synch_info,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_req_eutran_auth_info,rules);
		}
		
		/*Rules for Requested-UTRAN-GERAN-Authentication-Info  AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Number-Of-Requested-Vectors*/ ss_num_of_req_vects,RULE_OPTIONAL,0,0,1},
				{/*Immediate-Response-Preferred*/ ss_immdt_res_prefrd,RULE_OPTIONAL,0,0,1},
				{/*Re-synchronization-Info*/ ss_re_synch_info,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_req_utran_geran_auth_info,rules);
		}	

		/*Rules for Authentication-Info  AVP*/
		{
			struct dict_rule_data rules[]={
				{/*E-UTRAN-Vector*/ ss_e_utran_vector,RULE_OPTIONAL,0,0,-1},
				{/*UTRAN-Vector*/ ss_utran_vector,RULE_OPTIONAL,0,0,-1},
				{/*GERAN-Vector*/ ss_geran_vector,RULE_OPTIONAL,0,0,-1}
			};
			set_rule(ss_auth_info,rules);
		}
	
		/*Rules for E-UTRAN-Vector  AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Item-Number*/ ss_item_num,RULE_OPTIONAL,0,0,1},
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
				{/*Item-Number*/ ss_item_num,RULE_OPTIONAL,0,0,1},
				{/*RAND*/ ss_rand,RULE_REQUIRED,0,1,1},
				{/*XRES*/ ss_xres,RULE_REQUIRED,0,1,1},
				{/*AUTN*/ ss_autn,RULE_REQUIRED,0,1,1},
				{/*Confidentiality-Key*/ ss_confid_key,RULE_REQUIRED,0,1,1},
				{/*Integrity-Key*/ ss_integrity_key,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_utran_vector,rules);
		}
	
		/*Rules for GERAN-Vector AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Item-Number*/ ss_item_num,RULE_OPTIONAL,0,0,1},
				{/*RAND*/ ss_rand,RULE_REQUIRED,0,1,1},
				{/*SRES*/ ss_sres,RULE_REQUIRED,0,1,1},
				{/*Kc*/ ss_kc,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_geran_vector,rules);
		}
	
		/*Rules for APN-Configuration-Profile AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Context-Identifier*/ ss_context_id,RULE_REQUIRED,0,1,1},
				{/*All-APN-Configurations-Included-Indicator*/ ss_all_apn_config_incl_ind,RULE_REQUIRED,0,1,1},
				{/*APN-Configuration*/ ss_apn_conf,RULE_REQUIRED,0,1,-1}
			};
			set_rule(ss_apn_conf_prof,rules);
		}
	
		/*Rules for APN-Configuration AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Context-Identifier*/ ss_context_id,RULE_REQUIRED,0,1,1},
				{/*Served-Party-IP-Address*/ ss_servd_party_ip_addr,RULE_OPTIONAL,0,0,2},
				{/*PDN-Type*/ ss_pdn_type,RULE_REQUIRED,0,1,1},
				{/*Service-Selection*/ ss_service_selection,RULE_REQUIRED,0,1,1},
				{/*EPS-Subscribed-QoS-Profile*/ ss_eps_subscd_qos_prof,RULE_OPTIONAL,0,0,1},
				{/*VPLMN-Dynamic-Address-Allowed*/ ss_vplmn_dyn_addr_allowed,RULE_OPTIONAL,0,0,1},
				{/*MIP6-Agent-Info*/ ss_mip6_agent_info,RULE_OPTIONAL,0,0,1},
				{/*Visited-Network-Identifier*/ ss_vistd_net_id,RULE_OPTIONAL,0,0,1},
				{/*PDN-GW-Allocation-Type*/ ss_pdn_gw_alloc_type,RULE_OPTIONAL,0,0,1},
				{/*3GPP-Charging-Characteristics*/ ss_3gpp_charging_char,RULE_OPTIONAL,0,0,1},
				{/*AMBR*/ ss_ambr,RULE_OPTIONAL,0,0,1},
				{/*Specific-APN-Info*/ ss_specific_apn_info,RULE_OPTIONAL,0,0,-1},
				{/*APN-OI-Replacement*/ ss_apn_oi_replacement,RULE_OPTIONAL,0,0,1},
				{/*SIPTO-Permission*/ ss_sipto_permis,RULE_OPTIONAL,0,0,1},
				{/*LIPA-Permission*/ ss_lipa_permis,RULE_OPTIONAL,0,0,1},
				{/*Restoration-Priority*/ ss_restor_prio,RULE_OPTIONAL,0,0,1}, 
				{/*SIPTO-Local-Network-Permission*/ ss_sipto_local_net_permis,RULE_OPTIONAL,0,0,1},
				{/*WLAN-offloadability*/ ss_wlan_offloadability,RULE_OPTIONAL,0,0,1} 
			
			};
			set_rule(ss_apn_conf,rules);
		}
	
		/*Rules for EPS-Subscribed-QoS-Profile AVP*/
		{
			struct dict_rule_data rules[]={
				{/*QoS-Class-Identifier*/ ss_qos_class_id,RULE_REQUIRED,0,1,1},
				{/*Allocation-Retention-Priority*/ ss_alloc_retention_prio,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_eps_subscd_qos_prof,rules);
		}
	
		/*Rules for Allocation-Retention-Priority AVP defined in dict_dcca_3gpp.fdx*/
		
	
		/*Rules for AMBR AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Max-Requested-Bandwidth-UL*/ ss_max_req_band_ul,RULE_REQUIRED,0,1,1},
				{/*Max-Requested-Bandwidth-DL*/ ss_max_req_band_dl,RULE_REQUIRED,0,1,1},
			};
			set_rule(ss_ambr,rules);
		}
	
		/*Rules for MIP6-Agent-Info AVP*/
		{
			struct dict_rule_data rules[]={
				{/*MIP-Home-Agent-Address*/ ss_mip_home_agent_addr,RULE_OPTIONAL,0,0,2},
				{/*MIP-Home-Agent-Host*/ ss_mip_home_agen_host,RULE_OPTIONAL,0,0,1}			
			};
			set_rule(ss_mip6_agent_info,rules);
		}
	
		/*Rules for MIP-Home-Agent-Host AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Destination-Realm*/ ss_dest_realm,RULE_REQUIRED,0,1,1},
				{/*Destination-Host*/ ss_dest_host,RULE_REQUIRED,0,1,1},
			};
			set_rule(ss_mip_home_agen_host,rules);
		}
		
		/*Rules for Trace-Data AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Trace-Reference*/ ss_trace_ref,RULE_REQUIRED,0,1,1},
				{/*Trace-Depth*/ ss_trace_depth,RULE_REQUIRED,0,1,1},
				{/*Trace-NE-Type-List*/ ss_trace_ne_type_list,RULE_REQUIRED,0,1,1},
				{/*Trace-Interface-List*/ ss_trace_interf_list,RULE_OPTIONAL,0,0,1},
				{/*Trace-Event-List*/ ss_trace_event_list,RULE_REQUIRED,0,1,1},
				{/*OMC-Id*/ ss_omc_id,RULE_OPTIONAL,0,0,1},
				{/*Trace-Collection-Entity*/ ss_trace_coll_entity,RULE_REQUIRED,0,1,1},
				{/*MDT-Configuration*/ ss_mdt_conf,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_trace_data,rules);
		}
		
		/*Rules for GPRS-Subscription-Data AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Complete-Data-List-Included-Indicator*/ ss_complete_data_list_incl_ind,RULE_REQUIRED,0,1,1},
				{/*PDP-Context*/ ss_pdp_context,RULE_REQUIRED,0,1,50}			
			};
			set_rule(ss_gprs_subsc_data,rules);
		}
	
		/*Rules for PDP-Context AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Context-Identifier*/ ss_context_id,RULE_REQUIRED,0,1,1},
				{/*PDP-Type*/ ss_pdp_type,RULE_REQUIRED,0,1,1},
				{/*PDP-Address*/ ss_pdp_addr,RULE_OPTIONAL,0,0,1},
				{/*QoS-Subscribed*/ ss_qos_subscr,RULE_REQUIRED,0,1,1},
				{/*VPLMN-Dynamic-Address-Allowed*/ ss_vplmn_dyn_addr_allowed,RULE_OPTIONAL,0,0,1},
				{/*Service-Selection*/ ss_service_selection,1,1,RULE_REQUIRED},
				{/*3GPP-Charging-Characteristics*/ ss_3gpp_charging_char,RULE_OPTIONAL,0,0,1},
				{/*Ext-PDP-Type*/ ss_ext_pdp_type,RULE_OPTIONAL,0,0,1},
				{/*Ext-PDP-Address*/ ss_ext_pdp_addr,RULE_OPTIONAL,0,0,1},
				{/*AMBR*/ ss_ambr,RULE_OPTIONAL,0,0,1},
				{/*APN-OI-Replacement*/ ss_apn_oi_replacement,RULE_OPTIONAL,0,0,1},
				{/*SIPTO-Permission*/ ss_sipto_permis,RULE_OPTIONAL,0,0,1},
				{/*LIPA-Permission*/ ss_lipa_permis,RULE_OPTIONAL,0,0,1},
				{/*Restoration-Priority*/ ss_restor_prio,RULE_OPTIONAL,0,0,1},
				{/*SIPTO-Local-Network-Permission*/ ss_sipto_local_net_permis,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_pdp_context,rules);
		}
	
		/*Rules for CSG-Subscription-Data AVP*/
		{
			struct dict_rule_data rules[]={
				{/*CSG-Id*/ ss_csg_id,RULE_REQUIRED,0,1,1},
				{/*Expiration-Date*/ ss_expir_date,RULE_OPTIONAL,0,0,1},
				{/*Service-Selection*/ ss_service_selection,RULE_OPTIONAL,0,0,-1},
				{/*Visited-PLMN-Id*/ ss_visited_plmn_id,RULE_OPTIONAL,0,0,1}			
			};
			set_rule(ss_csg_subsc_data,rules);
		}

		/*Rules for  Specific-APN-Info AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Service-Selection*/ ss_service_selection,RULE_REQUIRED,0,1,1},
				{/*MIP6-Agent-Info*/ ss_mip6_agent_info,RULE_REQUIRED,0,1,1},
				{/*Visited-Network-Identifier*/ ss_vistd_net_id,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_specific_apn_info,rules);
		}
	
		/*Rules for LCS-Info  AVP*/
		{
			struct dict_rule_data rules[]={
				{/*GMLC-Number*/ ss_gmlc_num,RULE_OPTIONAL,0,0,-1},
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
				{/*Notification-To-UE-User*/ ss_notif_to_ue_user,RULE_OPTIONAL,0,0,1},
				{/*External-Client*/ ss_extr_cli,RULE_OPTIONAL,0,0,-1},
				{/*PLMN-Client*/ ss_plmn_cli,RULE_OPTIONAL,0,0,-1},
				{/*Service-Type*/ ss_servc_type,RULE_OPTIONAL,0,0,-1}			
			};
			set_rule(ss_lcs_privacyexception,rules);
		}
	
		/*Rules for External-Client AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Client-Identity*/ ss_cli_id,RULE_REQUIRED,0,1,1},
				{/*GMLC-Restriction*/ ss_gmlc_restr,RULE_OPTIONAL,0,0,1},
				{/*Notification-To-UE-User*/ ss_notif_to_ue_user,RULE_OPTIONAL,0,0,1}			
			};
			set_rule(ss_extr_cli,rules);
		}
	
		/*Rules for Service-Type AVP*/
		{
			struct dict_rule_data rules[]={
				{/*ServiceTypeIdentity*/ ss_servctypeid,RULE_REQUIRED,0,1,1},
				{/*GMLC-Restriction*/ ss_gmlc_restr,RULE_OPTIONAL,0,0,1},
				{/*Notification-To-UE-User*/ ss_notif_to_ue_user,RULE_OPTIONAL,0,0,1}			
			};
			set_rule(ss_servc_type,rules);
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
	
		/*Rules for Call-Barring-Infor-list AVP*/
		{
			struct dict_rule_data rules[]={
				{/*SS-Code*/ ss_ss_code,RULE_REQUIRED,0,1,1},
				{/*SS-Status*/ ss_ss_status,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_call_barr_info,rules);
		}
	
		/*Rules for EPS-User-State AVP*/
		{
			struct dict_rule_data rules[]={
				{/*MME-User-State*/ ss_mme_usr_state,RULE_OPTIONAL,0,0,1},
				{/*SGSN-User-State*/ ss_sgsn_usr_state,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_eps_usr_state,rules);
		}
	
		/*Rules for EPS-Location-Information AVP*/
		{
			struct dict_rule_data rules[]={
				{/*MME-LocationInformation*/ ss_mme_loc_info,RULE_OPTIONAL,0,0,1},
				{/*SGSN-Location-Information*/ ss_sgsn_loc_info,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_eps_loc_info,rules);
		}

		/*Rules for MME-User-State AVP*/
		{
			struct dict_rule_data rules[]={
				{/*User-State*/ ss_usr_state,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_mme_usr_state,rules);
		}
	
		/*Rules for SGSN-User-State AVP*/
		{
			struct dict_rule_data rules[]={
				{/*User-State*/ ss_usr_state,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_sgsn_usr_state,rules);
		}
	
		/*Rules for MME-LocationInformation AVP*/
		{
			struct dict_rule_data rules[]={
				{/*E-UTRAN-Cell-Global-Identity*/ ss_e_utran_cell_glb_id, RULE_OPTIONAL,0,0,1},
				{/*Tracking-Area-Identity*/ ss_track_area_id, RULE_OPTIONAL,0,0,1},
				{/*Geographical-Information*/ ss_geo_info, RULE_OPTIONAL,0,0,1},
				{/*Geodetic-Information*/ ss_geodetic_info, RULE_OPTIONAL,0,0,1},
				{/*Current-Location-Retrieved*/ ss_curr_loc_retrvd, RULE_OPTIONAL,0,0,1},
				{/*Age-Of-Location-Information*/ ss_age_of_loc_info, RULE_OPTIONAL,0,0,1},
				{/*User-CSG-Information*/ ss_usr_csg_info, RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_mme_loc_info,rules);
		} 

		/* Rules for User-CSG-Information AVP*/
		{
			struct dict_rule_data rules[]={
				{/*CSG-Id*/ ss_csg_id, RULE_REQUIRED, 0, 1, 1},
				{/*CSG-Access-Mode*/ ss_csg_accss_mode, RULE_REQUIRED, 0, 1, 1},
				{/*CSG-Membership-Indication*/ ss_csg_memb_ind, RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_usr_csg_info,rules);
		}

		/*Rules for SGSN-Location-Information AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Cell-Global-Identity*/ ss_cell_glb_id,RULE_OPTIONAL,0,0,1},
				{/*Location-Area-Identity*/ ss_loc_area_id,RULE_OPTIONAL,0,0,1},
				{/*Service-Area-Identity*/ ss_servc_area_id,RULE_OPTIONAL,0,0,1},
				{/*Routing-Area-Identity*/ ss_rout_area_id,RULE_OPTIONAL,0,0,1},
				{/*Geographical-Information*/ ss_geo_info,RULE_OPTIONAL,0,0,1},
				{/*Geodetic-Information*/ ss_geodetic_info,RULE_OPTIONAL,0,0,1},
				{/*Current-Location-Retrieved*/ ss_curr_loc_retrvd,RULE_OPTIONAL,0,0,1},
				{/*Age-Of-Location-Information*/ ss_age_of_loc_info,RULE_OPTIONAL,0,0,1},
				{/*User-CSG-Information*/ ss_usr_csg_info,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_sgsn_loc_info,rules);
		}
	
		/*Rules for Active-APN AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Context-Identifier*/ ss_context_id,RULE_REQUIRED,0,1,1},
				{/*Service-Selection*/ ss_service_selection,RULE_OPTIONAL,0,0,1},
				{/*MIP6-Agent-Info*/ ss_mip6_agent_info,RULE_OPTIONAL,0,0,1},
				{/*Visited-Network-Identifier*/ ss_vistd_net_id,RULE_OPTIONAL,0,0,1},
				{/*Specific-APN-Info*/ ss_specific_apn_info,RULE_OPTIONAL,0,0,-1}
			};
			set_rule(ss_activ_apn,rules);
		}

		/*Rules for  MDT-Configuration AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Job-Type*/ ss_job_type,RULE_REQUIRED,0,1,1},
				{/*Area-Scope*/ ss_area_scope,RULE_OPTIONAL,0,0,1},
				{/*List-Of-Measurements*/ ss_list_of_measr,RULE_OPTIONAL,0,0,1},
				{/*Reporting-Trigger*/ ss_repor_trig,RULE_OPTIONAL,0,0,1},
				{/*Report-Interval*/ ss_repor_intrv,RULE_OPTIONAL,0,0,1},
				{/*Report-Amount*/ ss_repor_amount,RULE_OPTIONAL,0,0,1},
				{/*Event-Threshold-RSRP*/ ss_evt_thrsd_rsrp,RULE_OPTIONAL,0,0,1},
				{/*Event-Threshold-RSRQ*/ ss_evt_thrsd_rsrq,RULE_OPTIONAL,0,0,1},
				{/*Logging-Interval*/ ss_log_intrv,RULE_OPTIONAL,0,0,1},
				{/*Logging-Duration*/ ss_log_dur,RULE_OPTIONAL,0,0,1},
				{/*Measurement-Period-LTE*/ ss_measr_perd_lte,RULE_OPTIONAL,0,0,1},
				{/*Measurement-Period-UMTS*/ ss_measr_perd_umts,RULE_OPTIONAL,0,0,1},
				{/*Collection-Period-RMM-LTE*/ ss_coll_perd_rrm_lte,RULE_OPTIONAL,0,0,1},
				{/*Collection-Period-RRM-UMTS*/ ss_coll_perd_rrm_umts,RULE_OPTIONAL,0,0,1},
				{/*Positioning-Method*/ ss_pos_meth,RULE_OPTIONAL,0,0,1},
				{/*Measurement-Quantity*/ ss_measr_quant,RULE_OPTIONAL,0,0,1},
				{/*Event-Threshold-Event-1F*/ ss_evt_thrsd_evt_1f,RULE_OPTIONAL,0,0,1},
				{/*Event-Threshold-Event-1I*/ ss_evt_thrsd_evt_1i,RULE_OPTIONAL,0,0,1},
				{/*MDT-Allowed-PLMN-Id*/ ss_mdt_allow_plmn_id,RULE_OPTIONAL,0,0,-1}
			};
			set_rule(ss_mdt_conf,rules);
		}	

		/*Rules for Area-Scope AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Cell-Global-Identity*/ ss_cell_glb_id,RULE_OPTIONAL,0,0,-1},
				{/*E-UTRAN-Cell-Global-Identity*/ ss_e_utran_cell_glb_id,RULE_OPTIONAL,0,0,-1},
				{/*Routing-Area-Identity*/ ss_rout_area_id,RULE_OPTIONAL,0,0,-1},
				{/*Location-Area-Identity*/ ss_loc_area_id,RULE_OPTIONAL,0,0,-1},
				{/*Tracking-Area-Identity*/ ss_track_area_id,RULE_OPTIONAL,0,0,-1}
			};
			set_rule(ss_area_scope,rules);
		}
	
		/*Rules for Equivalent-PLMN-List AVP*/
		{
			struct dict_rule_data rules[]={
			{/*Visited-PLMN-Id*/ ss_visited_plmn_id,RULE_REQUIRED,0,1,-1},
			};
			set_rule(ss_eqv_plmn_list,rules);
		}
	
		/*Rules for VPLMN-CSG-Subscription-Data AVP*/
		{
			struct dict_rule_data rules[]={
				{/*CSG-Id*/ ss_csg_id,RULE_REQUIRED,0,1,1},
				{/*Expiration-Date*/ ss_expir_date,RULE_OPTIONAL,0,0,1}
			};
			set_rule(ss_vplmn_csg_subsc_data,rules);
		}
 	
		/*Rules for Local-Time-Zone AVP*/
		{
			struct dict_rule_data rules[]={
				{/*Time-Zone*/ ss_tm_zn,RULE_REQUIRED,0,1,1},
				{/*Daylight-Saving-Time*/ ss_daylit_sv_tm,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_lcl_tm_zn,rules);
		}
	
		/*Rules for ProSe-Subscription-Data AVP*/
		{
			struct dict_rule_data rules[]={
				{/*ProSe-Permission*/ ss_prose_permis,RULE_REQUIRED,0,1,1}
			};
			set_rule(ss_prose_subsc_data,rules);
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
				{/*Experimental-Result-Code*/ ss_exper_res_code, RULE_REQUIRED, 0, 1, 1}
			};
			set_rule(ss_exper_result,rules);
		}

	}
	
	return 1;
}	
