/*ETSI TS 129 272 V12.8.0 */
/*Avps not included:OC-Supported-Features (Reason: AVP code is not defined yet)
					SGs-MME-Identity (Reason: SGs interface is not required)
					Coupled-Node-Diameter-ID (Reason: sgsn is not part of requirment)
					
*/

/*Dictionary objects for parent AVP*/
struct dict_object * ss_origin_host=NULL;
struct dict_object * ss_origin_realm=NULL;
struct dict_object * ss_dest_host=NULL;
struct dict_object * ss_dest_realm=NULL;
struct dict_object * ss_sess_id=NULL;
struct dict_object * ss_vendor_specific_app_id=NULL;
struct dict_object * ss_auth_session_state=NULL;
struct dict_object * ss_uer_name=NULL;
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
struct dict_object * ss_homog_suppr_of_ims_voic_ovr_ps_sess=NULL;
struct dict_object * ss_gmlc_addr=NULL;
struct dict_object * ss_activ_apn=NULL;
struct dict_object * ss_eqv_plmn_list=NULL;
struct dict_object * ss_mme_num_for_mt_sms=NULL;
struct dict_object * ss_sms_reg_req=NULL;
struct dict_object * ss_result_code=NULL; 
struct dict_object * ss_exper_result=NULL;
struct dict_object * ss_err_diagnostic=NULL;
struct dict_object * ss_ims_voice_ovr_ps_sess_suprt=NULL;
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
struct dict_object * ss_eqp_status=NULL;
struct dict_object * ss_failed_avp=NULL;

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

/*Dictionary object for MME-Location-Information AVP child AVPs*/
struct dict_object * ss_e_utran_cell_glb_id = NULL;
struct dict_object * ss_track_area_id = NULL;
struct dict_object * ss_geo_info = NULL;
struct dict_object * ss_geodetic_info = NULL;
struct dict_object * ss_curr_loc_retrvd = NULL;
struct dict_object * ss_age_of_loc_info = NULL;
struct dict_object * ss_cmd_cla = NULL;

/*Dictionary object for SGSN-Location-Information AVP child AVPs*/
struct dict_object * ss_cell_glb_id = NULL;
struct dict_object * ss_loc_area_id = NULL;
struct dict_object * ss_servc_area_id = NULL;
struct dict_object * ss_rout_area_id = NULL;

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
struct dict_object * ss_cmd_ecr = NULL;
struct dict_object * ss_cmd_eca = NULL;

/*Create request and answer commands*/
inline void create_cmd(size_t cmd_code,char *cmd_name_r,char *cmd_name_a,struct dict_object **cmd_r,struct dict_object **cmd_a){
	struct dict_cmd_data data={cmd_code,cmd_name_r,CMD_FLAG_PROXIABLE | CMD_FLAG_REQUEST,CMD_FLAG_PROXIABLE | CMD_FLAG_REQUEST};
	CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_COMMAND, &data, ss_app, cmd_r));
	data.cmd_name = cmd_name_a;
	data.cmd_flag_val  = CMD_FLAG_PROXIABLE;
	CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_COMMAND, &data, ss_app, cmd_a));
}


struct ss_rule{
	char *name;
	struct dict_object *dict_obj;
	int min;/*min: Minimum number of occurences. -1 means "default": 0 for optional rules, 1 for other rules*/ 
		
	int max;/*max: Maximum number of occurences. -1 means no maximum. 0 means the AVP is forbidden*/
	enum rule_position pos; /*opt: The position in which the rule_avp must appear in the parent*/
}

/*sets rules for command struct dict_obj that need rules
  parameter:
		parent: pointer to 'struct dict_object'(command or AVP of type group)
		rules_arry: a pointer to 'struct ss_rule' array containing the rules
  Note:make sure to declare 'struct dict_rule_data data;' before using this macro
		
*/
#define	set_rule(parent,rules_arry) {											\
	int indx;																	\
	for(indx=0;indx<sizeof(rules_arry)/sizeof(rules_arry[0]);indx++){			\
		data.rule_min = rules_arry[indx].min;									\
		ata.rule_max = rules_arry[indx].max;									\
		data.rule_position = rules_arry[indx].pos;								\
		data.rule_avp = rules_arry[indx].dict_obj;								\
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, parent, NULL));	\
	}																			\
}	
							

int ss_dict_init(){

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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, UTF8String_type, NULL);
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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL);
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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL);
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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL);
	}

	/*Define 'SIPTO-Local-Network-Permission' AVP */
	{
		struct dict_avp_data data = {
			1665,	/* Code */
			10415,	/* Vendor */
			"SIPTO-Local-Network-Permission",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};		
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL);
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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL);
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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL);
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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL);
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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL);
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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL);
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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL);
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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, Address_type, NULL);
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
		CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, DICT_AVP, &data, NULL, NULL);
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
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Supported-Features", &ss_supp_featr, ENOENT));
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "VPLMN-CSG-Subscription-Data", &ss_vplmn_csg_subsc_data, ENOENT) );
	CHECK_FCT( fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "User-Id", &ss_usr_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Feature-List-ID", &ss_feature_list_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Feature-List", &ss_feature_list, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Terminal-Information", &ss_terminal_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MIP6-Agent-Info", &ss_mip6_agent_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Alert-Reason", &ss_alert_reason, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "3GPP-RAT-Type", &ss_rat_type, ENOENT) );
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "ULR-Flags", &ss_ulr_flgs, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "CLR-Flags", &ss_clr_flgs, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "IDR-Flags", &ss_idr_flgs, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "DSR-Flags", &ss_dsr_flgs, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "PUR-Flags", &ss_pur_flgs, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "NOR-Flags", &ss_nor_flgs, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "UE-SRVCC-Capability", &ss_ue_srvcc_capab, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Requested-EUTRAN-Authentication-Info", &ss_req_eutran_auth_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Requested-UTRAN-GERAN-Authentication-Info", &ss_req_utran_geran_auth_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Cancellation-Type", &ss_cancel_type, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Context-Identifier", &ss_context_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Service-Selection", &ss_service_selection, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Trace-Reference", &ss_trace_ref, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "TS-Code", &ss_ts_code, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "SS-Code", &ss_ss_code, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Visited-PLMN-Id", &ss_visited_plmn_id, ENOENT) );
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "SGSN-Number", &ss_sgsn_num, ENOENT) );
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions", &ss_homog_suppr_of_ims_voic_ovr_ps_sess, ENOENT) );
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "GMLC-Address", &ss_gmlc_addr, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Active-APN", &ss_activ_apn, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Equivalent-PLMN-List", &ss_eqv_plmn_list, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MME-Number-for-MT-SMS", &ss_mme_num_for_mt_sms, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "SMS-Register-Request", &ss_sms_reg_req, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Result-Code", &ss_result_code, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Experimental-Result", &ss_exper_result, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Error-Diagnostic", &ss_err_diagnostic, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "IMS-Voice-Over-PS-Sessions-Supported", &ss_ims_voice_ovr_ps_sess_suprt, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Last-UE-Activity-Time", &ss_last_ue_actv_tm, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "ULA-Flags", &ss_ula_flgs, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "IDA-Flags", &ss_ida_flgs, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "DSA-Flags", &ss_dsa_flgs, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "PUA-Flags", &ss_pua_flgs, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "EPS-User-State", &ss_eps_usr_state, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "EPS-Location-Information", &ss_eps_loc_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Local-Time-Zone", &ss_lcl_tm_zn, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Subscription-Data", &ss_subsc_data, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Reset-ID", &ss_rst_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Authentication-Info", &ss_auth_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Equipment-Status", &ss_eqp_status, ENOENT));
	
	/*Initialize Authentication-Info child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "E-UTRAN-Vector", &ss_e_utran_vector, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "UTRAN-Vector", &ss_utran_vector, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "GERAN-Vector", &ss_geran_vector, ENOENT));

	/*Initialize E-UTRAN-Vector/UTRAN-Vector/GERAN-Vector child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Item-Number", &ss_item_num, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "RAND", &ss_rand, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "XRES", &ss_xres, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "AUTN", &ss_autn, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "KASME", &ss_kasme, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Confidentiality-Key", &ss_confid_key, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Integrity-Key", &ss_integrity_key, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "SRES", &ss_sres, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Kc", &ss_kc, ENOENT));
	
	/*Initialize Requested-EUTRAN-Authentication-Info/Requested-UTRAN-GE
RAN-Authentication-Info  child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Number-Of-Requested-Vectors", &ss_num_of_req_vects, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Immediate-Response-Preferred", &ss_immdt_res_prefrd, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Re-synchronization-Info", &ss_re_synch_info, ENOENT));
	
	/*Initialize Terminal-Information child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "IMEI", &ss_imei, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Software-Version", &ss_soft_version, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "3GPP2-MEID", &ss_meid, ENOENT));

	/*Initialize Subscriber-Data child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Subscriber-Status", &ss_subscr_status, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MSISDN", &ss_msisdn, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "A-MSISDN", &ss_a_msisdn, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "STN-SR", &ss_stn_sr, ENOENT));
 	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "ICS-Indicator", &ss_ics_indicator, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Network-Access-Mode", &ss_net_access_mode, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Operator-Determined-Barring", &ss_operator_det_barring, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "HPLMN-ODB", &ss_hplmn_odb, ENOENT));
 	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Regional-Subscription-Zone-Code", &ss_regional_subscrip_zone_code, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Access-Restriction-Data", &ss_access_restrict_data, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "APN-OI-Replacement", &ss_apn_oi_replacement, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "LCS-Info", &ss_lcs_info, ENOENT));
 	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Teleservice-List", &ss_teleservice_list, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Call-Barring-Info", &ss_call_barr_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "3GPP-Charging-Characteristics", &ss_3gpp_charging_char, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "AMBR", &ss_ambr, ENOENT));
 	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "APN-Configuration-Profile", &ss_apn_conf_prof, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "RAT-Frequency-Selection-Priority-ID", &ss_rat_freq_sel_prior_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Trace-Data", &ss_trace_data, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "GPRS-Subscription-Data", &ss_ss_gprs_subsc_data, ENOENT));
 	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "CSG-Subscription-Data", &ss_csg_subsc_data, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Roaming-Restricted-Due-To-Unsupported-Feature", &ss_roam_restr_dueto_unsuppr_featr, ENOENT)); 
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Subscribed-Periodic-RAU-TAU-Timer", &ss_subscr_priod_rau_tau_timer), ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MPS-Priority", &ss_mps_prio), ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "VPLMN-LIPA-Allowed", &ss_vplmn_lipa_allow), ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Relay-Node-Indicator", &ss_rely_nod_ind), ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MDT-User-Consent", &ss_mdt_usr_consent), ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Subscribed-VSRVCC", &ss_subscr_vsrvcc), ENOENT));ss_prose_subsc_data=NULL;
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "ProSe-Subscription-Data", &ss_prose_subsc_data), ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Subscription-Data-Flags", &ss_subsc_data_flgs), ENOENT));	

	/*Initialize APN-Configuration-Profile child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "All-APN-Configurations-Included-Indicator", &ss_all_apn_config_incl_ind, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "APN-Configuration", &ss_apn_conf, ENOENT));
	
	/*Initialize APN-Configuration child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Served-Party-IP-Address", &ss_servd_party_ip_addr, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "PDN-Type", &ss_pdn_type, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "EPS-Subscribed-QoS-Profile", &ss_eps_subscd_qos_prof, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "VPLMN-Dynamic-Address-Allowed", &ss_vplmn_dyn_addr_allowed, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Visited-Network-Identifier", &ss_vistd_net_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "PDN-GW-Allocation-Type", &ss_pdn_gw_alloc_type, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Specific-APN-Info", &ss_specific_apn_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "SIPTO-Permission", &ss_sipto_permis, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "LIPA-Permission", &ss_lipa_permis, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Restoration-Priority", &ss_restor_prio, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "SIPTO-Local-Network-Permission", &ss_sipto_local_net_permis, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "WLAN-offloadability", &ss_wlan_offloadability, ENOENT));

	/*Initialize EPS-Subscribed-QoS-Profile child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "QoS-Class-Identifier", &ss_qos_class_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Allocation-Retention-Priority", &ss_alloc_retention_prio, ENOENT));

	/*Initialize Allocation-Retention-Priority AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Priority-Level", &ss_prio_level, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Pre-emption-Capability", &ss_pre_emp_capb, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Pre-emption-Vulnerability", &ss_pre_emp_vuln, ENOENT));

	/*Initialize  AMBR AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Max-Requested-Bandwidth-UL", &ss_max_req_band_ul, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Max-Requested-Bandwidth-DL", &ss_max_req_band_dl, ENOENT));

	/*Initialize MIP6-Agent-In AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MIP-Home-Agent-Address", &ss_mip_home_agent_addr, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MIP-Home-Agent-Host", &ss_mip_home_agen_host, ENOENT));
		
	/*Initialize Trace-Data AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Trace-Depth", &ss_trace_depth, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Trace-NE-Type-List", &ss_trace_ne_type_list, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Trace-Interface-List", &ss_trace_interf_list, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Trace-Event-List", &ss_trace_event_list, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "OMC-Id", &ss_omc_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Trace-Collection-Entity", &ss_trace_coll_entity, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MDT-Configuration", &ss_mdt_conf, ENOENT));
	
	/*Initialize GPRS-Subscription-Data  AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Complete-Data-List-Included-Indicator", &ss_complete_data_list_incl_ind, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "PDP-Context", &ss_pdp_context, ENOENT));

	/*Initialize PDP-Context  AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "PDP-Type", &ss_pdp_type, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "PDP-Address", &ss_pdp_addr, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "QoS-Subscribed", &ss_qos_subscr, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Ext-PDP-Type", &ss_ext_pdp_type, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Ext-PDP-Address", &ss_ext_pdp_addr, ENOENT));

	/*Initialize CSG-Subscription-Data AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "CSG-Id", &ss_csg_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Expiration-Date", &ss_expir_date, ENOENT));

	/*Initialize LCS-Info AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "GMLC-Number", &ss_gmlc_num, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "LCS-PrivacyException", &ss_lcs_privacyexception, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MO-LR", &ss_mo_lr, ENOENT));
 
	/*Initialize LCS-PrivacyException AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "SS-Status", &ss_ss_status, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Notification-To-UE-User", &ss_notif_to_ue_user, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "External-Client", &ss_extr_cli, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "PLMN-Client", &ss_plmn_cli, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Service-Type", &ss_servc_type, ENOENT));
 
	/*Initialize External-Client AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Client-Identity", &ss_cli_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "GMLC-Restriction", &ss_gmlc_restr, ENOENT));
	
	/*Initialize Service-Type AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "ServiceTypeIdentity", &ss_servctypeid, ENOENT));

	/*Initialize EPS-User-State AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MME-User-State", &ss_mme_usr_state, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "SGSN-User-State", &ss_sgsn_usr_state, ENOENT));

	/*Initialize EPS-Location-Information AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MME-Location-Information", &ss_mme_loc_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "SGSN-Location-Information", &ss_sgsn_loc_info, ENOENT));
	
	/*Initialize MME-User-State  AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "User-State", &ss_usr_state, ENOENT));

	/*Initialize MME-Location-Information AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "E-UTRAN-Cell-Global-Identity", &ss_e_utran_cell_glb_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Tracking-Area-Identity", &ss_track_area_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Geographical-Information", &ss_geo_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Geodetic-Information", &ss_geodetic_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Current-Location-Retrieved", &ss_curr_loc_retrvd, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Age-Of-Location-Information", &ss_age_of_loc_info, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "User-CSG-Information", &ss_usr_csg_info, ENOENT));

	/*Initialize SGSN-Location-Information AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Cell-Global-Identity", &ss_cell_glb_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Location-Area-Identity", &ss_loc_area_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Service-Area-Identity", &ss_servc_area_id, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Routing-Area-Identity", &ss_rout_area_id, ENOENT));

	/*Initialize MDT-Configuration AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Job-Type", &ss_job_type, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Area-Scope", &ss_area_scope, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "List-Of-Measurements", &ss_list_of_measr, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Reporting-Trigger", &ss_repor_trig, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Report-Interval", &ss_repor_intrv, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Report-Amount", &ss_repor_amount, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Event-Threshold-RSRP", &ss_evt_thrsd_rsrp, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Event-Threshold-RSRQ", &ss_evt_thrsd_rsrq, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Logging-Interval", &ss_log_intrv, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Logging-Duration", &ss_log_dur, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Measurement-Period-LTE", &ss_measr_perd_lte, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Measurement-Period-UMTS", &ss_measr_perd_umts, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Collection-Period-RRM-LTE", &ss_coll_perd_rrm_lte, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Collection-Period-RRM-UMTS", &ss_coll_perd_rrm_umts, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Positioning-Method", &ss_pos_meth, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Measurement-Quantity", &ss_measr_quant, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Event-Threshold-Event-1F", &ss_evt_thrsd_evt_1f, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Event-Threshold-Event-1I", &ss_evt_thrsd_evt_1i, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "MDT-Allowed-PLMN-Id", &ss_mdt_allow_plmn_id, ENOENT));

	/*Initialize Local-Time-Zone AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Time-Zone", &ss_tm_zn, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Daylight-Saving-Time", &ss_daylit_sv_tm, ENOENT));

	/*Initialize ProSe-Subscription-Data AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "ProSe-Permission", &ss_prose_permis, ENOENT));
			
	/*Initialize WLAN-offloadability AVP child AVPs*/
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "WLAN-offloadability-EUTRAN", &ss_wlan_offloadability_eutran, ENOENT));
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "WLAN-offloadability-UTRAN", &ss_wlan_offloadability_utran, ENOENT));

	/* Application Vendor */
	CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_VENDOR, VENDOR_BY_NAME, "3GPP",&ss_vendor, ENOENT) );
	
	
	/* S6a/S6d Application */Subscription-Data
	{
		struct dict_application_data data={16777251,"S6a/S6d"};
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_APPLICATION, &data, ss_vendor, &ss_app));
	}
	
	/* Create the  Update-Location-Request &  Update-Location-Answer commands */
	create_cmd(316,"Update-Location-Request","Update-Location-Answer",ss_cmd_ulr,ss_cmd_ula);

	/* Create the  Authentication-Information-Request &  Authentication-Information-Answer commands */
	create_cmd(318,"Authentication-Information-Request","Authentication-Information-Answer",ss_cmd_air,ss_cmd_aia);

	/* Create the  Cancel-Location-Request &  Cancel-Location-Answer commands */
	create_cmd(317,"Cancel-Location-Request","Cancel-Location-Answer",ss_cmd_clr,ss_cmd_cla);

	/* Create the  Insert-Subscriber-Data-Request &  Insert-Subscriber-Data-Request-Answer commands */
	create_cmd(319,"Insert-Subscriber-Data-Request","Insert-Subscriber-Data-Answer",ss_cmd_idr,ss_cmd_ida);

	/* Create the  Delete-Subscriber-Data-Request  &  Delete-Subscriber-Data-Answer commands */
	create_cmd(320,"Delete-Subscriber-Data-Request","Delete-Subscriber-Data-Answer",ss_cmd_dsr,ss_cmd_dsa);
	
	/* Create the   Purge-UE-Request &   Purge-UE-Answer commands */
	create_cmd(321,"Purge-UE-Request","Purge-UE-Answer",ss_cmd_pur,ss_cmd_pua);
	
	/* Create the   Reset-Request &   Reset-Answer commands */
	create_cmd(322,"Reset-Request","Reset-Request",ss_cmd_rsr,ss_cmd_rsa);
	
	/* Create the  Notify-Request &  Notify-Answer commands */
	create_cmd(323,"Notify-Request","Notify-Answer",ss_cmd_nor,ss_cmd_noa);
	
	/* Create the  E-Identity-Check-Request  &  E-Identity-Check-Answer commands */
	create_cmd(324,"E-Identity-Check-Request","E-Identity-Check-Answer",ss_cmd_ecr,ss_cmd_eca);

	/*Create rules for the commands*/
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
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ecr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_eca, NULL));

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
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ecr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_eca, NULL));

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
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ecr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_eca, NULL));

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
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ecr, NULL));
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_eca, NULL));

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
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ecr, NULL));

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

		/*Terminal-Information*/
		data.rule_avp = ss_terminal_info;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ecr, NULL));
		

		/*******************************************************/
		/*Rules for Optional avps with maximum occurance of 1*/
		/*******************************************************/
	
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
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ecr, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_eca, NULL));

		/*Destination-host*/
		data.rule_avp = ss_dst_host;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ulr, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_air, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_pur, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_nor, NULL));	
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ecr, NULL));	
		
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
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_eca, NULL));

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
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_eca, NULL));

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
		data.rule_avp = ss_ims_voice_ovr_ps_sess_suprt;
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
		data.rule_avp = ss_homog_suppr_of_ims_voic_ovr_ps_sess;
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

		/*User-Name*/
		data.rule_avp = ss_user_name;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_ecr, NULL));

		/*Equipment-Status*/
		data.rule_avp = ss_eqp_status;
		CHECK_FCT(fd_dict_new( fd_g_config->cnf_dict, DICT_RULE, &data, ss_cmd_eca, NULL));	


		/*********************************************************/
		/*Rules for Optional avps with unlimited maximum occurance*/
		/*********************************************************/	
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

	}

	/************************************/
	/******Create grouped AVP rules******/	
	/************************************/
	
	struct dict_rule_data data;
		
	/*Rules for Subscription-Data AVP*/
	{
		 struct ss_rule rules[]={
			{"Subscriber-Status",ss_subscr_status,0,1,RULE_OPTIONAL},
			{"MSISDN",ss_msisdn,0,1,RULE_OPTIONAL},
			{"A-MSISDN",ss_a_msisdn,0,1,RULE_OPTIONAL},
			{"STN-SR",ss_stn_sr,0,1,RULE_OPTIONAL},
			{"ICS-Indicator",ss_ics_indicator,0,1,RULE_OPTIONAL},
			{"Network-Access-Mode",ss_net_access_mode,0,1,RULE_OPTIONAL},
			{"Operator-Determined-Barring",ss_operator_det_barring,0,1,RULE_OPTIONAL},
			{"HPLMN-ODB",ss_hplmn_odb,0,1,RULE_OPTIONAL},
			{"Regional-Subscription-Zone-Code",ss_regional_subscrip_zone_code,0,10,RULE_OPTIONAL},
			{"Access-Restriction-Data",ss_access_restrict_data,0,1,RULE_OPTIONAL},
			{"APN-OI-Replacement",ss_apn_oi_replacement,0,1,RULE_OPTIONAL},
			{"LCS-Info",ss_lcs_info,0,1,RULE_OPTIONAL},
			{"Teleservice-List",ss_teleservice_list,0,1,RULE_OPTIONAL},
			{"Call-Barring-Info", &ss_call_barr_info,0,-1,RULE_OPTIONAL},
			{"3GPP-Charging-Characteristics",ss_3gpp_charging_char,0,1,RULE_OPTIONAL},
			{"AMBR",ss_ambr,0,1,RULE_OPTIONAL},
			{"APN-Configuration-Profile",ss_apn_conf_prof,0,1,RULE_OPTIONAL},
			{"RAT-Frequency-Selection-Priority-ID",ss_rat_freq_sel_prior_id,0,1,RULE_OPTIONAL},
			{"Trace-Data",ss_trace_data,0,1,RULE_OPTIONAL},
			{"GPRS-Subscription-Data",ss_ss_gprs_subsc_data,0,1,RULE_OPTIONAL},
			{"CSG-Subscription-Data",ss_csg_subsc_data,0,-1,RULE_OPTIONAL},
			{"Roaming-Restricted-Due-To-Unsupported-Feature",ss_roam_restr_dueto_unsuppr_featr,0,1,RULE_OPTIONAL},
			{"Subscribed-Periodic-RAU-TAU-Timer",ss_subscr_priod_rau_tau_timer,0,1,RULE_OPTIONAL},
			{"MPS-Priority",ss_mps_prio,0,1,RULE_OPTIONAL},
			{"VPLMN-LIPA-Allowed",ss_vplmn_lipa_allow,0,1,RULE_OPTIONAL},
			{"Relay-Node-Indicator",ss_rely_nod_ind,0,1,RULE_OPTIONAL},
			{"MDT-User-Consent",ss_mdt_usr_consent,0,1,RULE_OPTIONAL},
			{"Subscribed-VSRVCC",ss_subscr_vsrvcc,0,1,RULE_OPTIONAL},
			{"ProSe-Subscription-Data",ss_prose_subsc_data,0,1,RULE_OPTIONAL},
			{"Subscription-Data-Flags",ss_subsc_data_flgs,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_subsc_data,rules);
	}

	/*Rules for Terminal-Information AVP*/
	{
		struct ss_rule rules[]={
			{"IMEI",ss_imei,0,1,RULE_OPTIONAL},
			{"3GPP2-MEID",ss_meid,0,1,RULE_OPTIONAL},
			{"Software-Version",ss_soft_version,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_terminal_info,rules);
	}

	/*Rules for Requested-EUTRAN-Authentication-Info AVP*/
	{
		struct ss_rule rules[]={
			{"Number-Of-Requested-Vectors",ss_num_of_req_vects,0,1,RULE_OPTIONAL},
			{"Immediate-Response-Preferred",ss_immdt_res_prefrd,0,1,RULE_OPTIONAL},
			{"Re-synchronization-Info",ss_re_synch_info,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_req_eutran_auth_info,rules);
	}

	/*Rules for Requested-UTRAN-GERAN-Authentication-Info  AVP*/
	{
		struct ss_rule rules[]={
			{"Number-Of-Requested-Vectors",ss_num_of_req_vects,0,1,RULE_OPTIONAL},
			{"Immediate-Response-Preferred",ss_immdt_res_prefrd,0,1,RULE_OPTIONAL},
			{"Re-synchronization-Info",ss_re_synch_info,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_req_utran_geran_auth_info,rules);
	}

	/*Rules for Authentication-Info  AVP*/
	{
		struct ss_rule rules[]={
			{"E-UTRAN-Vector",ss_e_utran_vector,0,-1,RULE_OPTIONAL},
			{"UTRAN-Vector",ss_utran_vector,0,-1,RULE_OPTIONAL},
			{"GERAN-Vector",ss_geran_vector,0,-1,RULE_OPTIONAL}
		};
		set_rule(ss_auth_info,rules);
	}

	/*Rules for E-UTRAN-Vector  AVP*/
	{
		struct ss_rule rules[]={
			{"Item-Number",ss_item_num,0,1,RULE_OPTIONAL},
			{"RAND",ss_rand,1,1,RULE_REQUIRED},
			{"XRES",ss_xres,1,1,RULE_REQUIRED},
			{"AUTN",ss_autn,1,1,RULE_REQUIRED},
			{"KASME",ss_kasme,1,1,RULE_REQUIRED}
		};
		set_rule(ss_e_utran_vector,rules);
	}

	/*Rules for UTRAN-Vector AVP*/
	{
		struct ss_rule rules[]={
			{"Item-Number",ss_item_num,0,1,RULE_OPTIONAL},
			{"RAND",ss_rand,1,1,RULE_REQUIRED},
			{"XRES",ss_xres,1,1,RULE_REQUIRED},
			{"AUTN",ss_autn,1,1,RULE_REQUIRED},
			{"Confidentiality-Key",ss_confid_key,1,1,RULE_REQUIRED},
			{"Integrity-Key",ss_integrity_key,1,1,RULE_REQUIRED}
		};
		set_rule(ss_utran_vector,rules);
	}

	/*Rules for GERAN-Vector AVP*/
	{
		struct ss_rule rules[]={
			{"Item-Number",ss_item_num,0,1,RULE_OPTIONAL},
			{"RAND",ss_rand,1,1,RULE_REQUIRED},
			{"SRES",ss_sres,1,1,RULE_REQUIRED},
			{"Kc",ss_kc,1,1,RULE_REQUIRED}
		};
		set_rule(ss_geran_vector,rules);
	}

	/*Rules for APN-Configuration-Profile AVP*/
	{
		struct ss_rule rules[]={
			{"Context-Identifier",ss_context_id,1,1,RULE_REQUIRED},
			{"All-APN-Configurations-Included-Indicator",ss_all_apn_config_incl_ind,1,1,RULE_REQUIRED},
			{"APN-Configuration",ss_apn_conf,1,-1,RULE_REQUIRED}
		};
		set_rule(ss_apn_conf_prof,rules);
	}

	/*Rules for APN-Configuration AVP*/
	{
		struct ss_rule rules[]={
			{"Context-Identifier",ss_context_id,1,1,RULE_REQUIRED},
			{"Served-Party-IP-Address",ss_servd_party_ip_addr,0,2,RULE_OPTIONAL},
			{"PDN-Type",ss_pdn_type,1,1,RULE_REQUIRED},
			{"Service-Selection",ss_service_selection,1,1,RULE_REQUIRED},
			{"EPS-Subscribed-QoS-Profile",ss_eps_subscd_qos_prof,0,1,RULE_OPTIONAL},
			{"VPLMN-Dynamic-Address-Allowed",ss_vplmn_dyn_addr_allowed,0,1,RULE_OPTIONAL},
			{"MIP6-Agent-Info",ss_mip6_agent_info,0,1,RULE_OPTIONAL},
			{"Visited-Network-Identifier",ss_vistd_net_id,0,1,RULE_OPTIONAL},
			{"PDN-GW-Allocation-Type",ss_pdn_gw_alloc_type,0,1,RULE_OPTIONAL},
			{"3GPP-Charging-Characteristics",ss_3gpp_charging_char,0,1,RULE_OPTIONAL},
			{"AMBR",ss_ambr,0,1,RULE_OPTIONAL},
			{"Specific-APN-Info",ss_specific_apn_info,0,-1,RULE_OPTIONAL},
			{"APN-OI-Replacement",ss_apn_oi_replacement,0,1,RULE_OPTIONAL},
			{"SIPTO-Permission",ss_sipto_permis,0,1,RULE_OPTIONAL},
			{"LIPA-Permission",ss_lipa_permis,0,1,RULE_OPTIONAL},
			{"Restoration-Priority",ss_restor_prio,0,1,RULE_OPTIONAL}, 
			{"SIPTO-Local-Network-Permission",ss_sipto_local_net_permis,0,1,RULE_OPTIONAL},
			{"WLAN-offloadability",ss_lipa_permis,0,1,RULE_OPTIONAL} 
		
		};
		set_rule(ss_apn_conf,rules);
	}

	/*Rules for EPS-Subscribed-QoS-Profile AVP*/
	{
		struct ss_rule rules[]={
			{"QoS-Class-Identifier",ss_qos_class_id,1,1,RULE_REQUIRED},
			{"Allocation-Retention-Priority",ss_alloc_retention_prio,1,1,RULE_REQUIRED},
		};
		set_rule(ss_eps_subscd_qos_prof,rules);
	}

	/*Rules for Allocation-Retention-Priority AVP*/
	{
		struct ss_rule rules[]={
			{"Priority-Level",ss_prio_level,1,1,RULE_REQUIRED},
			{"Pre-emption-Capability",ss_pre_emp_capb,0,1,RULE_OPTIONAL},
			{"Pre-emption-Vulnerability",ss_pre_emp_vuln,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_alloc_retention_prio,rules);
	}

	/*Rules for AMBR AVP*/
	{
		struct ss_rule rules[]={
			{"Max-Requested-Bandwidth-UL",ss_max_req_band_ul,1,1,RULE_REQUIRED},
			{"Max-Requested-Bandwidth-DL",ss_max_req_band_dl,1,1,RULE_REQUIRED},
		};
		set_rule(ss_ambr,rules);
	}

	/*Rules for MIP6-Agent-Info AVP*/
	{
		struct ss_rule rules[]={
			{"MIP-Home-Agent-Address",ss_mip_home_agent_addr,0,2,RULE_OPTIONAL},
			{"MIP-Home-Agent-Host",ss_mip_home_agen_host,0,1,RULE_OPTIONAL}			
		};
		set_rule(ss_mip6_agent_info,rules);
	}

	/*Rules for MIP-Home-Agent-Host AVP*/
	{
		struct ss_rule rules[]={
			{"Destination-Realm",ss_dest_realm,1,1,RULE_REQUIRED},
			{"Destination-Host",ss_dest_host,1,1,RULE_REQUIRED},
		};
		set_rule(ss_mip_home_agen_host,rules);
	}
	
	/*Rules for Trace-Data AVP*/
	{
		struct ss_rule rules[]={
			{"Trace-Reference",ss_trace_ref,1,1,RULE_REQUIRED},
			{"Trace-Depth",ss_trace_depth,1,1,RULE_REQUIRED},
			{"Trace-NE-Type-List",ss_trace_ne_type_list,1,1,RULE_REQUIRED},
			{"Trace-Interface-List",ss_trace_interf_list,0,1,RULE_OPTIONAL},
			{"Trace-Event-List",ss_trace_event_list,1,1,RULE_REQUIRED},
			{"OMC-Id",ss_omc_id,0,1,RULE_OPTIONAL},
			{"Trace-Collection-Entity",ss_trace_coll_entity,1,1,RULE_REQUIRED},
			{"MDT-Configuration",ss_mdt_conf,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_trace_data,rules);
	}
	
	/*Rules for GPRS-Subscription-Data AVP*/
	{
		struct ss_rule rules[]={
			{"Complete-Data-List-Included-Indicator",ss_complete_data_list_incl_ind,1,1,RULE_REQUIRED},
			{"PDP-Context",ss_pdp_context,1,50,RULE_REQUIRED}			
		};
		set_rule(ss_ss_gprs_subsc_data,rules);
	}

	/*Rules for PDP-Context AVP*/
	{
		struct ss_rule rules[]={
			{"Context-Identifier",ss_context_id,1,1,RULE_REQUIRED},
			{"PDP-Type",ss_pdp_type,1,1,RULE_REQUIRED},
			{"PDP-Address",ss_pdp_addr,0,1,RULE_OPTIONAL},
			{"QoS-Subscribed",ss_qos_subscr,1,1,RULE_REQUIRED},
			{"VPLMN-Dynamic-Address-Allowed",ss_vplmn_dyn_addr_allowed,0,1,RULE_OPTIONAL},
			{"Service-Selection",ss_service_selection,1,1,RULE_REQUIRED},
			{"3GPP-Charging-Characteristics",ss_3gpp_charging_char,0,1,RULE_OPTIONAL},
			{"Ext-PDP-Type",ss_ext_pdp_type,0,1,RULE_OPTIONAL},
			{"Ext-PDP-Address",ss_ext_pdp_addr,0,1,RULE_OPTIONAL},
			{"AMBR",ss_ambr,0,1,RULE_OPTIONAL},
			{"APN-OI-Replacement",ss_apn_oi_replacement,0,1,RULE_OPTIONAL},
			{"SIPTO-Permission",ss_sipto_permis,0,1,RULE_OPTIONAL},
			{"LIPA-Permission",ss_lipa_permis,0,1,RULE_OPTIONAL},
			{"Restoration-Priority",ss_restor_prio,0,1,RULE_OPTIONAL},
			{"SIPTO-Local-Network-Permission",ss_sipto_local_net_permis,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_pdp_context,rules);
	}

	/*Rules for CSG-Subscription-Data AVP*/
	{
		struct ss_rule rules[]={
			{"CSG-Id",ss_csg_id,1,1,RULE_REQUIRED},
			{"Expiration-Date",ss_expir_date,0,1,RULE_OPTIONAL},
			{"Service-Selection",ss_service_selection,0,-1,RULE_OPTIONAL},
			{"Visited-PLMN-Id",ss_visited_plmn_id,0,1,RULE_OPTIONAL}			
		};
		set_rule(ss_csg_subsc_data,rules);
	}

	/*Rules for  Specific-APN-Info AVP*/
	{
		struct ss_rule rules[]={
			{"Service-Selection",ss_service_selection,1,1,RULE_REQUIRED},
			{"MIP6-Agent-Info",ss_mip6_agent_info,0,1,RULE_REQUIRED},
			{"Visited-Network-Identifier",ss_vistd_net_id,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_specific_apn_info,rules);
	}

	/*Rules for LCS-Info  AVP*/
	{
		struct ss_rule rules[]={
			{"GMLC-Number",ss_gmlc_num,0,-1,RULE_OPTIONAL},
			{"LCS-PrivacyException",ss_lcs_privacyexception,0,-1,RULE_OPTIONAL},
			{"MO-LR",ss_mo_lr,0,-1,RULE_OPTIONAL}			
		};
		set_rule(ss_lcs_info,rules);
	}

	/*Rules for LCS-PrivacyException AVP*/
	{
		struct ss_rule rules[]={
			{"SS-Code",ss_ss_code,1,1,RULE_REQUIRED},
			{"SS-Status",ss_ss_status,1,1,RULE_REQUIRED},
			{"Notification-To-UE-User",ss_notif_to_ue_user,0,1,RULE_OPTIONAL},
			{"External-Client",ss_extr_cli,0,-1,RULE_OPTIONAL},
			{"PLMN-Client",ss_plmn_cli,0,-1,RULE_OPTIONAL},
			{"Service-Type",ss_servc_type,0,-1,RULE_OPTIONAL}			
		};
		set_rule(ss_lcs_privacyexception,rules);
	}

	/*Rules for External-Client AVP*/
	{
		struct ss_rule rules[]={
			{"Client-Identity",ss_cli_id,1,1,RULE_REQUIRED},
			{"GMLC-Restriction",ss_gmlc_restr,0,1,RULE_OPTIONAL},
			{"Notification-To-UE-User",ss_notif_to_ue_user,0,1,RULE_OPTIONAL}			
		};
		set_rule(ss_extr_cli,rules);
	}

	/*Rules for Service-Type AVP*/
	{
		struct ss_rule rules[]={
			{"ServiceTypeIdentity",ss_servctypeid,1,1,RULE_REQUIRED},
			{"GMLC-Restriction",ss_gmlc_restr,0,1,RULE_OPTIONAL},
			{"Notification-To-UE-User",ss_notif_to_ue_user,0,1,RULE_OPTIONAL}			
		};
		set_rule(ss_servc_type,rules);
	}

	/*Rules for MO-LR AVP*/
	{
		struct ss_rule rules[]={
			{"SS-Code",ss_ss_code,1,1,RULE_REQUIRED},
			{"SS-Status",ss_ss_status,1,1,RULE_REQUIRED}
		};
		set_rule(ss_mo_lr,rules);
	}

	/*Rules for Teleservice-List AVP*/
	{
		struct ss_rule rules[]={
			{" TS-Code",ss_ts_code,1,-1,RULE_REQUIRED}
		};
		set_rule(ss_teleservice_list,rules);
	}

	/*Rules for Call-Barring-Info AVP*/
	{
		struct ss_rule rules[]={
			{"SS-Code",ss_ss_code,1,1,RULE_REQUIRED},
			{"SS-Status",ss_ss_status,1,1,RULE_REQUIRED}
		};
		set_rule(ss_call_barr_info,rules);
	}

	/*Rules for EPS-User-State AVP*/
	{
		struct ss_rule rules[]={
			{"MME-User-State",ss_mme_usr_state,0,1,RULE_OPTIONAL},
			{"SGSN-User-State",ss_sgsn_usr_state,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_eps_usr_state,rules);
	}

	/*Rules for EPS-Location-Information AVP*/
	{
		struct ss_rule rules[]={
			{"MME-Location-Information",ss_mme_loc_info,0,1,RULE_OPTIONAL},
			{"SGSN-Location-Information",ss_sgsn_loc_info,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_eps_loc_info,rules);
	}

	/*Rules for MME-User-State AVP*/
	{
		struct ss_rule rules[]={
			{"User-State",ss_usr_state,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_mme_usr_state,rules);
	}

	/*Rules for SGSN-User-State AVP*/
	{
		struct ss_rule rules[]={
			{"User-State",ss_usr_state,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_sgsn_usr_state,rules);
	}

	/*Rules for MME-Location-Information AVP*/
	{
		struct ss_rule rules[]={
			{"E-UTRAN-Cell-Global-Identity",ss_e_utran_cell_glb_id,0,1,RULE_OPTIONAL},
			{"Tracking-Area-Identity",ss_track_area_id,0,1,RULE_OPTIONAL},
			{"Geographical-Information",ss_geo_info,0,1,RULE_OPTIONAL},
			{"Geodetic-Information",ss_geodetic_info,0,1,RULE_OPTIONAL},
			{"Current-Location-Retrieved",ss_curr_loc_retrvd,0,1,RULE_OPTIONAL},
			{"Age-Of-Location-Information",ss_age_of_loc_info,0,1,RULE_OPTIONAL},
			{"User-CSG-Information",ss_usr_csg_info,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_mme_loc_info,rules);
	}

	/*Rules for SGSN-Location-Information AVP*/
	{
		struct ss_rule rules[]={
			{"Cell-Global-Identity",ss_cell_glb_id,0,1,RULE_OPTIONAL},
			{"Location-Area-Identity",ss_loc_area_id,0,1,RULE_OPTIONAL},
			{"Service-Area-Identity",ss_servc_area_id,0,1,RULE_OPTIONAL},
			{"Routing-Area-Identity",ss_rout_area_id,0,1,RULE_OPTIONAL},
			{"Geographical-Information",ss_geo_info,0,1,RULE_OPTIONAL},
			{"Geodetic-Information",ss_geodetic_info,0,1,RULE_OPTIONAL},
			{"Current-Location-Retrieved",ss_curr_loc_retrvd,0,1,RULE_OPTIONAL},
			{"Age-Of-Location-Information",ss_age_of_loc_info,0,1,RULE_OPTIONAL},
			{"User-CSG-Information",ss_usr_csg_info,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_sgsn_loc_info,rules);
	}

	/*Rules for Active-APN AVP*/
	{
		struct ss_rule rules[]={
			{"Context-Identifier",ss_context_id,1,1,RULE_REQUIRED},
			{"Service-Selection",ss_service_selection,0,1,RULE_OPTIONAL},
			{"MIP6-Agent-Info",ss_mip6_agent_info,0,1,RULE_OPTIONAL},
			{"Visited-Network-Identifier",ss_vistd_net_id,0,1,RULE_OPTIONAL},
			{"Specific-APN-Info",ss_specific_apn_info,0,-1,RULE_OPTIONAL}
		};
		set_rule(ss_activ_apn,rules);
	}

	/*Rules for  MDT-Configuration AVP*/
	{
		struct ss_rule rules[]={
			{"Job-Type",ss_job_type,1,1,RULE_REQUIRED},
			{"Area-Scope",ss_area_scope,0,1,RULE_OPTIONAL},
			{"List-Of-Measurements",ss_list_of_measr,0,1,RULE_OPTIONAL},
			{"Reporting-Trigger",ss_repor_trig,0,1,RULE_OPTIONAL},
			{"Report-Interval",ss_repor_intrv,0,1,RULE_OPTIONAL},
			{"Report-Amount",ss_repor_amount,0,1,RULE_OPTIONAL},
			{"Event-Threshold-RSRP",ss_evt_thrsd_rsrp,0,1,RULE_OPTIONAL},
			{"Event-Threshold-RSRQ",ss_evt_thrsd_rsrq,0,1,RULE_OPTIONAL},
			{"Logging-Interval",ss_log_intrv,0,1,RULE_OPTIONAL},
			{"Logging-Duration",ss_log_dur,0,1,RULE_OPTIONAL},
			{"Measurement-Period-LTE",ss_measr_perd_lte,0,1,RULE_OPTIONAL},
			{"Measurement-Period-UMTS",ss_measr_perd_umts,0,1,RULE_OPTIONAL},
			{"Collection-Period-RMM-LTE",ss_coll_perd_rrm_lte,0,1,RULE_OPTIONAL},
			{"Collection-Period-RRM-UMTS",ss_coll_perd_rrm_umts,0,1,RULE_OPTIONAL},
			{"Positioning-Method",ss_pos_meth,0,1,RULE_OPTIONAL},
			{"Measurement-Quantity",ss_measr_quant,0,1,RULE_OPTIONAL},
			{"Event-Threshold-Event-1F",ss_evt_thrsd_evt_1f,0,1,RULE_OPTIONAL},
			{"Event-Threshold-Event-1I",ss_evt_thrsd_evt_1i,0,1,RULE_OPTIONAL},
			{"MDT-Allowed-PLMN-Id",ss_mdt_allow_plmn_id,0,-1,RULE_OPTIONAL}
		};
		set_rule(ss_mdt_conf,rules);
	}	

	/*Rules for Area-Scope AVP*/
	{
		struct ss_rule rules[]={
			{"Cell-Global-Identity",ss_cell_glb_id,0,-1,RULE_OPTIONAL},
			{"E-UTRAN-Cell-Global-Identity",ss_e_utran_cell_glb_id,0,-1,RULE_OPTIONAL},
			{"Routing-Area-Identity",ss_rout_area_id,0,-1,RULE_OPTIONAL},
			{"Location-Area-Identity",ss_loc_area_id,0,-1,RULE_OPTIONAL},
			{"Tracking-Area-Identity",ss_track_area_id,0,-1,RULE_OPTIONAL}
		};
		set_rule(ss_area_scope,rules);
	}

	/*Rules for Equivalent-PLMN-List AVP*/
	{
		struct ss_rule rules[]={
			{"Visited-PLMN-Id",ss_visited_plmn_id,1,-1,RULE_REQUIRED},
		};
		set_rule(ss_eqv_plmn_list,rules);
	}

	/*Rules for VPLMN-CSG-Subscription-Data AVP*/
	{
		struct ss_rule rules[]={
			{"CSG-Id",ss_csg_id,1,1,RULE_REQUIRED},
			{"Expiration-Date",ss_expir_date,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_vplmn_csg_subsc_data,rules);
	}
 
	/*Rules for Local-Time-Zone AVP*/
	{
		struct ss_rule rules[]={
			{"Time-Zone",ss_tm_zn,1,1,RULE_REQUIRED},
			{"Daylight-Saving-Time",ss_daylit_sv_tm,1,1,RULE_REQUIRED}
		};
		set_rule(ss_lcl_tm_zn,rules);
	}

	/*Rules for ProSe-Subscription-Data AVP*/
	{
		struct ss_rule rules[]={
			{"ProSe-Permission",ss_prose_permis,1,1,RULE_REQUIRED}
		};
		set_rule(ss_prose_subsc_data,rules);
	}

	/*Rules for WLAN-offloadability AVP*/
	{
		struct ss_rule rules[]={
			{"WLAN-offloadability-EUTRAN",ss_wlan_offloadability_eutran,0,1,RULE_OPTIONAL},
			{"WLAN-offloadability-UTRAN",ss_wlan_offloadability_utran,0,1,RULE_OPTIONAL}
		};
		set_rule(ss_wlan_offloadability,rules);
	}

}	
	

