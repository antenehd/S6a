#ifndef INTERNAL_SSIX
#define INTERNAL_SSIX

#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdcore.h>

#include "interf_ssix.h"

#define NO_STATE_MAINTAINED 1
#define VENDOR_ID 10415
#define APPLICATION_ID 16777251

#define SS_SET_I32( dict, value, parent, child)	{								 \
	CHECK_FCT_DO(fd_msg_avp_new(dict,0,&child),goto error);						 \
	val.i32=*(value);															 \
	CHECK_FCT_DO(fd_msg_avp_setvalue(child,&val),goto error);					 \
	CHECK_FCT_DO(fd_msg_avp_add(parent,MSG_BRW_LAST_CHILD,child),goto error);	 \
}

#define SS_SET_U32( dict, value, parent, child)  {							 	 \
	CHECK_FCT_DO(fd_msg_avp_new(dict,0,&child),goto error);					     \
	val.u32=*(value);															 \
	CHECK_FCT_DO(fd_msg_avp_setvalue(child,&val),goto error);					 \
	CHECK_FCT_DO(fd_msg_avp_add(parent,MSG_BRW_LAST_CHILD,child),goto error);	 \
}

#define SS_SET_OCTET( dict, value, parent, child)  {							 \
	CHECK_FCT_DO(fd_msg_avp_new(dict,0,&child),goto error);					     \
	val.os.data = (unsigned char *)value;														 \
	val.os.len = strlen((char *)(value));										 \
	CHECK_FCT_DO(fd_msg_avp_setvalue(child,&val),goto error);					 \
	CHECK_FCT_DO(fd_msg_avp_add(parent,MSG_BRW_LAST_CHILD,child),goto error);	 \
}

#define SS_SET_COMMON	{																		\
	if(msg->dst_host)																			\
		SS_SET_OCTET( ss_dest_host, msg->dst_host, *req, avp);									\
	if(msg->dst_realm)																			\
		SS_SET_OCTET( ss_dest_realm, msg->dst_realm, *req, avp);									\
	if(msg->suprt_ftr){																			\
		do{																						\
			CHECK_FCT_DO( fd_msg_avp_new ( ss_supp_featr, 0,&gavp), goto error);				\
			if((msg->suprt_ftr)->vendor_id)														\
				SS_SET_U32( ss_vendor_id, (msg->suprt_ftr)->vendor_id, gavp, avp);				\
			if((msg->suprt_ftr)->feature_list_id)												\
				SS_SET_U32( ss_feature_list_id, (msg->suprt_ftr)->feature_list_id, gavp, avp);	\
			if((msg->suprt_ftr)->feature_list)													\
				SS_SET_U32( ss_feature_list, (msg->suprt_ftr)->feature_list, gavp, avp);		\
			CHECK_FCT_DO( fd_msg_avp_add( *req, MSG_BRW_LAST_CHILD, gavp ), goto error  );		\
		} while((msg->suprt_ftr =(msg->suprt_ftr)->next)!=NULL);								\
	}																							\
}

#define SET_VENDOR_SPEC_APP_ID(msg)															\
	{																						\
		CHECK_FCT_DO( fd_msg_avp_new ( ss_vendor_specific_app_id, 0, &gavp), goto error  );	\
		CHECK_FCT_DO(fd_msg_avp_new(ss_vendor_id,0,&avp),goto error);						\
		val.u32=(unsigned32) VENDOR_ID;														\
		CHECK_FCT_DO(fd_msg_avp_setvalue(avp,&val),goto error);								\
  		CHECK_FCT_DO(fd_msg_avp_add(gavp,MSG_BRW_LAST_CHILD,avp),goto error);				\
		CHECK_FCT_DO(fd_msg_avp_new(ss_auth_app_id,0,&avp),goto error);						\
		val.u32 = (unsigned32) APPLICATION_ID;												\
		CHECK_FCT_DO(fd_msg_avp_setvalue(avp,&val),goto error);								\
		CHECK_FCT_DO(fd_msg_avp_add(gavp,MSG_BRW_LAST_CHILD,avp),goto error);				\
		CHECK_FCT_DO( fd_msg_avp_add( msg, MSG_BRW_LAST_CHILD, gavp ), goto error);			\
	}
#define SET_AUTH_SESSION_STATE(msg)															\
	{																						\
		CHECK_FCT_DO( fd_msg_avp_new ( ss_auth_session_state, 0, &avp), goto error  );		\
		val.i32 = NO_STATE_MAINTAINED;														\
		CHECK_FCT_DO(fd_msg_avp_setvalue(avp,&val), goto error);							\
		CHECK_FCT_DO( fd_msg_avp_add( msg, MSG_BRW_LAST_CHILD, avp ), goto error  );		\
	}


/**/
extern struct dict_object * ss_origin_host;
extern struct dict_object * ss_origin_realm;
extern struct dict_object * ss_dest_host;
extern struct dict_object * ss_dest_realm;
extern struct dict_object * ss_sess_id;
extern struct dict_object * ss_vendor_specific_app_id;
extern struct dict_object * ss_auth_session_state;
extern struct dict_object * ss_user_name;
extern struct dict_object * ss_vendor_id;
extern struct dict_object * ss_supp_featr;
extern struct dict_object * ss_vplmn_csg_subsc_data;
extern struct dict_object * ss_usr_id;
extern struct dict_object * ss_feature_list_id;
extern struct dict_object * ss_feature_list;
extern struct dict_object * ss_terminal_info;
extern struct dict_object * ss_mip6_agent_info;
extern struct dict_object * ss_rat_type;
extern struct dict_object * ss_req_eutran_auth_info;
extern struct dict_object * ss_req_utran_geran_auth_info;
extern struct dict_object * ss_cancel_type;
extern struct dict_object * ss_ulr_flgs;
extern struct dict_object * ss_clr_flgs;
extern struct dict_object * ss_idr_flgs;
extern struct dict_object * ss_dsr_flgs;
extern struct dict_object * ss_pur_flgs;
extern struct dict_object * ss_ue_srvcc_capab;	
extern struct dict_object * ss_context_id;
extern struct dict_object * ss_service_selection;
extern struct dict_object * ss_alert_reason;
extern struct dict_object * ss_nor_flgs;
extern struct dict_object * ss_trace_ref;
extern struct dict_object * ss_ts_code;
extern struct dict_object * ss_ss_code;
extern struct dict_object * ss_visited_plmn_id;
extern struct dict_object * ss_sgsn_num;
extern struct dict_object * ss_homog_suppr_ims_vop_sess;
extern struct dict_object * ss_gmlc_addr;
extern struct dict_object * ss_activ_apn;
extern struct dict_object * ss_eqv_plmn_list;
extern struct dict_object * ss_mme_num_for_mt_sms;
extern struct dict_object * ss_sms_reg_req;
extern struct dict_object * ss_result_code; 
extern struct dict_object * ss_exper_result;
extern struct dict_object * ss_err_diagnostic;
extern struct dict_object * ss_ims_voice_ovr_ps_sess_suprt;
extern struct dict_object * ss_last_ue_actv_tm;
extern struct dict_object * ss_ula_flgs;
extern struct dict_object * ss_ida_flgs;
extern struct dict_object * ss_dsa_flgs;
extern struct dict_object * ss_pua_flgs;
extern struct dict_object * ss_eps_usr_state;
extern struct dict_object * ss_eps_loc_info;
extern struct dict_object * ss_lcl_tm_zn;
extern struct dict_object * ss_subsc_data;
extern struct dict_object * ss_rst_id;
extern struct dict_object * ss_auth_info;
extern struct dict_object * ss_failed_avp;
extern struct dict_object * ss_copl_nd_dia_id; 

/*Dictionary object for Vendor-Specific-Application-Id AVP child AVPs*/
extern struct dict_object * ss_auth_app_id;

/*Dictionary object for Authentication-Info AVP child AVPs*/
extern struct dict_object * ss_e_utran_vector;
extern struct dict_object * ss_utran_vector;
extern struct dict_object * ss_geran_vector; 

/*Dictionary object for E-UTRAN-Vector/UTRAN-Vector/GERAN-Vector AVP child AVPs*/
extern struct dict_object * ss_item_num;
extern struct dict_object * ss_rand; 
extern struct dict_object * ss_xres;
extern struct dict_object * ss_autn;
extern struct dict_object * ss_kasme; 		/*E-UTRAN-Vector only*/
extern struct dict_object * ss_confid_key; 	/*UTRAN-Vector only*/
extern struct dict_object * ss_integrity_key;	/*UTRAN-Vector only*/
extern struct dict_object * ss_sres; 			/*GERAN-Vector only*/
extern struct dict_object * ss_kc;			/*GERAN-Vector only*/
 
/*Dictionary object for Requested-EUTRAN-Authentication-Info/equested-UTRAN-GE
RAN-Authentication-Info  AVP child AVPs*/
extern struct dict_object * ss_num_of_req_vects;
extern struct dict_object * ss_immdt_res_prefrd; 
extern struct dict_object * ss_re_synch_info;  

/*Dictionary object for Terminal-Information AVP child AVPs*/
extern struct dict_object * ss_imei;
extern struct dict_object * ss_soft_version;
extern struct dict_object * ss_meid;

/*Dictionary object for Subscription-Data AVP child AVPs*/
extern struct dict_object * ss_subscr_status;
extern struct dict_object * ss_msisdn; 
extern struct dict_object * ss_a_msisdn;  
extern struct dict_object * ss_stn_sr; 
extern struct dict_object * ss_ics_indicator;
extern struct dict_object * ss_net_access_mode; 
extern struct dict_object * ss_operator_det_barring; 
extern struct dict_object * ss_hplmn_odb;
extern struct dict_object * ss_regional_subscrip_zone_code;
extern struct dict_object * ss_access_restrict_data;
extern struct dict_object * ss_apn_oi_replacement;
extern struct dict_object * ss_lcs_info;
extern struct dict_object * ss_teleservice_list;
extern struct dict_object * ss_call_barr_info;
extern struct dict_object * ss_3gpp_charging_char;  
extern struct dict_object * ss_ambr; 
extern struct dict_object * ss_apn_conf_prof;
extern struct dict_object * ss_rat_freq_sel_prior_id; 
extern struct dict_object * ss_trace_data;
extern struct dict_object * ss_gprs_subsc_data;
extern struct dict_object * ss_csg_subsc_data; 
extern struct dict_object * ss_roam_restr_dueto_unsuppr_featr;
extern struct dict_object * ss_subscr_priod_rau_tau_timer; 
extern struct dict_object * ss_mps_prio;
extern struct dict_object * ss_vplmn_lipa_allow;
extern struct dict_object * ss_rely_nod_ind; 
extern struct dict_object * ss_mdt_usr_consent;
extern struct dict_object * ss_subscr_vsrvcc; 
extern struct dict_object * ss_prose_subsc_data;
extern struct dict_object * ss_subsc_data_flgs;
	

/*Dictionary object for APN-Configuration-Profile AVP child AVPs*/
extern struct dict_object * ss_all_apn_config_incl_ind; 
extern struct dict_object * ss_apn_conf;

/*Dictionary object for APN-Configuration AVP child AVPs*/
extern struct dict_object * ss_servd_party_ip_addr; 
extern struct dict_object * ss_pdn_type;
extern struct dict_object * ss_eps_subscd_qos_prof; 
extern struct dict_object * ss_vplmn_dyn_addr_allowed;
extern struct dict_object * ss_vistd_net_id;
extern struct dict_object * ss_pdn_gw_alloc_type; 
extern struct dict_object * ss_specific_apn_info;	
extern struct dict_object * ss_sipto_permis;
extern struct dict_object * ss_lipa_permis;
extern struct dict_object * ss_restor_prio;
extern struct dict_object * ss_sipto_local_net_permis;
extern struct dict_object * ss_wlan_offloadability;

/*Dictionary object for EPS-Subscribed-QoS-Profile AVP child AVPs*/
extern struct dict_object * ss_qos_class_id; 
extern struct dict_object * ss_alloc_retention_prio;
	
/*Dictionary object for Allocation-Retention-Priority AVP child AVPs*/
extern struct dict_object * ss_prio_level;
extern struct dict_object * ss_pre_emp_capb;
extern struct dict_object * ss_pre_emp_vuln; 
 
/*Dictionary object for AMBR AVP child AVPs*/
extern struct dict_object * ss_max_req_band_ul;
extern struct dict_object * ss_max_req_band_dl;

/*Dictionary object for MIP6-Agent-In AVP child AVPs*/
extern struct dict_object * ss_mip_home_agent_addr;
extern struct dict_object * ss_mip_home_agen_host;

/*Dictionary object for Trace-Data AVP child AVPs*/
extern struct dict_object * ss_trace_depth; 
extern struct dict_object * ss_trace_ne_type_list;
extern struct dict_object * ss_trace_interf_list; 
extern struct dict_object * ss_trace_event_list;  
extern struct dict_object * ss_omc_id;  
extern struct dict_object * ss_trace_coll_entity;  
extern struct dict_object * ss_mdt_conf;

/*Dictionary object for GPRS-Subscription-Data  AVP child AVPs*/
extern struct dict_object * ss_complete_data_list_incl_ind;  
extern struct dict_object * ss_pdp_context;
	
/*Dictionary object for PDP-Context  AVP child AVPs*/
extern struct dict_object * ss_pdp_type; 
extern struct dict_object * ss_pdp_addr; 
extern struct dict_object * ss_qos_subscr;
extern struct dict_object * ss_ext_pdp_type;
extern struct dict_object * ss_ext_pdp_addr;  

/*Dictionary object for CSG-Subscription-Data  AVP child AVPs*/
extern struct dict_object * ss_csg_id;   
extern struct dict_object * ss_expir_date; 

/*Dictionary object for LCS-Info   AVP child AVPs*/
extern struct dict_object * ss_gmlc_num;   
extern struct dict_object * ss_lcs_privacyexception;
extern struct dict_object * ss_mo_lr; 

/*Dictionary object for LCS-PrivacyException AVP child AVPs*/
extern struct dict_object * ss_ss_status; 
extern struct dict_object * ss_notif_to_ue_user; 
extern struct dict_object * ss_extr_cli;
extern struct dict_object * ss_plmn_cli;
extern struct dict_object * ss_servc_type; 

/*Dictionary object for External-Client AVP child AVPs*/
extern struct dict_object * ss_cli_id;
extern struct dict_object * ss_gmlc_restr;
	
/*Dictionary object for Service-Type AVP child AVPs*/
extern struct dict_object * ss_servctypeid;

/*Dictionary object for EPS-User-State AVP child AVPs*/
extern struct dict_object * ss_mme_usr_state;
extern struct dict_object * ss_sgsn_usr_state;	

/*Dictionary object for EPS-Location-Information AVP child AVPs*/
extern struct dict_object * ss_mme_loc_info;
extern struct dict_object * ss_sgsn_loc_info;
	 
/*Dictionary object for MME-User-State  AVP child AVPs*/
extern struct dict_object * ss_usr_state;

/*Dictionary object for MME-Location-Information AVP child AVPs*/
extern struct dict_object * ss_e_utran_cell_glb_id;
extern struct dict_object * ss_track_area_id;
extern struct dict_object * ss_geo_info;
extern struct dict_object * ss_geodetic_info;
extern struct dict_object * ss_curr_loc_retrvd;
extern struct dict_object * ss_age_of_loc_info;
extern struct dict_object * ss_cmd_cla;
extern struct dict_object * ss_usr_csg_info;

/*Dictionary object for User-CSG-Information AVP child AVPs*/
extern struct dict_object * ss_csg_accss_mode;
extern struct dict_object * ss_csg_memb_ind;

/*Dictionary object for SGSN-Location-Information AVP child AVPs*/
extern struct dict_object * ss_cell_glb_id;
extern struct dict_object * ss_loc_area_id;
extern struct dict_object * ss_servc_area_id;
extern struct dict_object * ss_rout_area_id;

/*Dictionary object for MDT-Configuration AVP child AVPs*/
extern struct dict_object * ss_job_type;
extern struct dict_object * ss_area_scope;
extern struct dict_object * ss_list_of_measr;
extern struct dict_object * ss_repor_trig;
extern struct dict_object * ss_repor_intrv;
extern struct dict_object * ss_repor_amount;
extern struct dict_object * ss_evt_thrsd_rsrp;
extern struct dict_object * ss_evt_thrsd_rsrq;
extern struct dict_object * ss_log_intrv;
extern struct dict_object * ss_log_dur;
extern struct dict_object * ss_measr_perd_lte;
extern struct dict_object * ss_measr_perd_umts;
extern struct dict_object * ss_coll_perd_rrm_lte;
extern struct dict_object * ss_coll_perd_rrm_umts;
extern struct dict_object * ss_pos_meth;
extern struct dict_object * ss_measr_quant;
extern struct dict_object * ss_evt_thrsd_evt_1f;
extern struct dict_object * ss_evt_thrsd_evt_1i;
extern struct dict_object * ss_mdt_allow_plmn_id;

/*Dictionary object for Local-Time-Zone AVP child AVPs*/
extern struct dict_object * ss_tm_zn;
extern struct dict_object * ss_daylit_sv_tm;
	
/*Dictionary object for ProSe-Subscription-Data AVP child AVPs*/
extern struct dict_object * ss_prose_permis;

/*Dictionary object for WLAN-offloadability AVP child AVPs*/
extern struct dict_object * ss_wlan_offloadability_eutran;
extern struct dict_object * ss_wlan_offloadability_utran;

/*Dictionary object for Experimental-Result AVP child AVPs*/
extern struct dict_object * ss_exper_res_code;

/*Dictionary object for commands*/
extern struct dict_object * ss_vendor;
extern struct dict_object * ss_app;
extern struct dict_object * ss_cmd_ulr;
extern struct dict_object * ss_cmd_ula;
extern struct dict_object * ss_cmd_air;
extern struct dict_object * ss_cmd_aia;
extern struct dict_object * ss_cmd_clr;
extern struct dict_object * ss_cmd_cla;
extern struct dict_object * ss_cmd_idr;
extern struct dict_object * ss_cmd_ida;
extern struct dict_object * ss_cmd_dsr;
extern struct dict_object * ss_cmd_dsa;
extern struct dict_object * ss_cmd_pur;
extern struct dict_object * ss_cmd_pua;
extern struct dict_object * ss_cmd_rsr;
extern struct dict_object * ss_cmd_rsa;
extern struct dict_object * ss_cmd_nor;
extern struct dict_object * ss_cmd_noa;

/*Initialized the necessary dictionary objects*/
int ss_dict_init();

/*Functions that converts messages structures into AVPs */
int ss_msg_ulr_set(struct msg ** req, struct ulr_msg * msg);
int ss_msg_air_set(struct msg ** req, struct air_msg * msg);
int ss_msg_clr_set(struct msg ** req, struct clr_msg * msg);
int ss_msg_idr_set(struct msg ** req, struct idr_msg * msg);
int ss_msg_dsr_set(struct msg ** req, struct dsr_msg * msg);
int ss_msg_pur_set(struct msg ** req, struct pur_msg * msg);
int ss_msg_rsr_set(struct msg ** req, struct rsr_msg * msg);
int ss_msg_nor_set(struct msg ** req, struct nor_msg * msg);

/*Initializes the listening ssix server*/
int ss_serv_init();

/*Call back function that handle request messages and send answer*/
int ss_ulr_ans_cb(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act);
int ss_clr_ans_cb(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act);

#endif
