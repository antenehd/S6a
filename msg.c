/*msg.c*/
#include "interf_ssix.h"
#include "internal_ssix.h"


#define CREATE_INIT_MSG(msg_type)																		\
	{																							\
		/* Create a request message*/															\
		CHECK_FCT_DO( fd_msg_new( msg_type, MSGFL_ALLOC_ETEID, req ), goto error );			\
		/* Create a new session */																\
		CHECK_FCT_DO( fd_msg_new_session( *req, NULL, 0 ), goto error );							\
		CHECK_FCT_DO( fd_msg_sess_get(fd_g_config->cnf_dict, *req, &sess, NULL), goto error );	\
		/*Vendor-Specific-Application-Id*/														\
		SET_VENDOR_SPEC_APP_ID(*req);															\
		/*Auth-Session-State*/																	\
		SET_AUTH_SESSION_STATE(*req);															\
		/* Set Origin-Host & Origin-Realm AVP*/													\
		CHECK_FCT_DO( fd_msg_add_origin ( *req, 0 ), goto error  );								\
	}

/***********************************************************************************************/
/* Set  Update-Location-Request command														   */
/***********************************************************************************************/

int ss_msg_ulr_set(struct msg ** req, struct ulr_msg * msg){
	
	union avp_value val;
	struct avp *avp, *gavp, *gavp1, *gavp2, *gavp3;
	struct session *sess = NULL;

	if(req && msg){

		/*Create new ULR message, create a new sessiona, set vendor-spec-app-id and auth-sess-state*/
		CREATE_INIT_MSG(ss_cmd_ulr);

		/*set destinatin host,destination realm and supported features*/
		SS_SET_COMMON;
		
		/*Set User-Name AVP*/
		if(msg->usr_name)
			SS_SET_OCTET( ss_user_name, msg->usr_name, *req, avp);

		/*set Rat-Type avp from message*/
		if(msg->rat_type)
			SS_SET_I32( ss_rat_type, msg->rat_type, *req, avp);
	
		/*set Terminal-Information grouped avp from message*/
		if(msg->term_info){

			CHECK_FCT_DO( fd_msg_avp_new ( ss_terminal_info, 0, &gavp), goto error  );
	
			/*set IMEI avp and add it to Terminal-Information grouped avp as a child*/
			if((msg->term_info)->imei)
				SS_SET_OCTET( ss_imei, (msg->term_info)->imei, gavp, avp);

			/*set Software-Version avp and add it to Terminal-Information grouped avp as a child*/
			if((msg->term_info)->soft_vrs)
				SS_SET_OCTET( ss_soft_version, (msg->term_info)->soft_vrs, gavp, avp);

			/*set 3GPP2-MEID avp and add it to Terminal-Information grouped avp as a child*/
			if((msg->term_info)->meid)
				SS_SET_OCTET( ss_meid, (msg->term_info)->meid, gavp, avp);

			CHECK_FCT_DO( fd_msg_avp_add( *req, MSG_BRW_LAST_CHILD, gavp ), goto error  );	

		}	
			
		/*set Ulr-Flag avp from message*/
		if(msg->ulr_flg)
			SS_SET_U32( ss_ulr_flgs, msg->ulr_flg, *req, avp);

		/*Set UE-SRVCC-Capability	avp from message*/
		if(msg->ue_srvcc)
			SS_SET_I32( ss_ue_srvcc_capab, msg->ue_srvcc, *req, avp);

		/*Set Visted-Plmn-Id avp from message*/
		if(msg->vis_plmn_id)	
			SS_SET_OCTET( ss_visited_plmn_id, msg->vis_plmn_id, *req, avp);

		/*Set SGSN-Number avp from message*/
		if(msg->sgsn_num)
			SS_SET_OCTET( ss_sgsn_num, msg->sgsn_num, *req, avp);
	
		/*Set Homogeneous-Support-of-IMS-Voice-Over-PS-Session avp from message*/
		if(msg->hm_ims_vop)
			SS_SET_I32( ss_homog_suppr_ims_vop_sess, msg->hm_ims_vop, *req, avp);
		
		/*Set GMLC-Address avp from message*/
		if(msg->gmlc_addr)
			SS_SET_OCTET( ss_gmlc_addr, msg->gmlc_addr, *req, avp);	

		/*Set Active-APN  avp from message*/
		if(msg->act_apn){
		
			do{

				CHECK_FCT_DO( fd_msg_avp_new ( ss_activ_apn, 0,&gavp), goto error);	

				/*set Context-Identifier avp*/
				if((msg->act_apn)->contxt_id)
					SS_SET_U32( ss_context_id, (msg->act_apn)->contxt_id, gavp, avp);
	
				/*set Service-Selection avp*/
				if((msg->act_apn)->serv_sel)	
					SS_SET_OCTET( ss_service_selection, (msg->act_apn)->serv_sel, gavp, avp);
		
				/*set MIP6-Agent-Info avp*/
				if((msg->act_apn)->agt_inf){
					
					CHECK_FCT_DO( fd_msg_avp_new ( ss_mip6_agent_info, 0,&gavp1), goto error );
							
					/*set MIP-Home-Agent-Address 1 avp*/
					if(((msg->act_apn)->agt_inf)->hm_agt_addr1)
						SS_SET_OCTET( ss_mip_home_agent_addr, ((msg->act_apn)->agt_inf)->hm_agt_addr1, gavp1, avp);	

					/*set MIP-Home-Agent-Address 2 avp*/
					if(((msg->act_apn)->agt_inf)->hm_agt_addr2)
						SS_SET_OCTET( ss_mip_home_agent_addr, ((msg->act_apn)->agt_inf)->hm_agt_addr2, gavp1, avp);	
			
					/*set MIP-Home-Agent-Host avp*/
					if(((msg->act_apn)->agt_inf)->hm_agt_hst){
		
						CHECK_FCT_DO( fd_msg_avp_new ( ss_mip_home_agen_host, 0,&gavp2), goto error );
		
						/*set Destination-Realm avp*/
						if((((msg->act_apn)->agt_inf)->hm_agt_hst)->dst_rlm)
							SS_SET_OCTET( ss_dest_realm, (((msg->act_apn)->agt_inf)->hm_agt_hst)->dst_rlm, gavp2, avp);
			
						/*Set Destination-Host avp*/
						if((((msg->act_apn)->agt_inf)->hm_agt_hst)->dst_hst)
							SS_SET_OCTET( ss_dest_host, (((msg->act_apn)->agt_inf)->hm_agt_hst)->dst_hst, gavp2, avp);	

						CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2 ), goto error);
					}
					
					CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1 ), goto error );
				}
				
				/*Set Visited-Network-Identifier avp*/
				if((msg->act_apn)->vist_net_id)
					SS_SET_OCTET( ss_vistd_net_id, (msg->act_apn)->vist_net_id, gavp, avp);

				/*Set Specific-APN-Info avp*/
				if((msg->act_apn)->apn_inf){
		
					do{
	
						CHECK_FCT_DO( fd_msg_avp_new ( ss_specific_apn_info, 0,&gavp1), goto error );
	
						/* Set Service-Selection avp*/
						if(((msg->act_apn)->apn_inf)->serv_sel)
							SS_SET_OCTET( ss_service_selection, ((msg->act_apn)->apn_inf)->serv_sel, gavp1, avp);
						
						/* Set MIP6-Agent-Info avp*/
						if(((msg->act_apn)->apn_inf)->agt_inf){
							
							CHECK_FCT_DO( fd_msg_avp_new ( ss_mip6_agent_info, 0,&gavp2), goto error );
							
							/* Set MIP-Home-Agent-Address avp*/
							if((((msg->act_apn)->apn_inf)->agt_inf)->hm_agt_addr1)
								SS_SET_OCTET( ss_mip_home_agent_addr, (((msg->act_apn)->apn_inf)->agt_inf)->hm_agt_addr1, gavp2, avp);

							/* Set MIP-Home-Agent-Address avp*/
							if((((msg->act_apn)->apn_inf)->agt_inf)->hm_agt_addr2)
								SS_SET_OCTET( ss_mip_home_agent_addr, (((msg->act_apn)->apn_inf)->agt_inf)->hm_agt_addr2, gavp2, avp);				
					
							/* Set MIP-Home-Agent-Host avp*/
							if((((msg->act_apn)->apn_inf)->agt_inf)->hm_agt_hst){
		
								CHECK_FCT_DO( fd_msg_avp_new ( ss_mip_home_agen_host, 0,&gavp3), goto error );	

								/* Set Destination-Realm avp*/
								if(((((msg->act_apn)->apn_inf)->agt_inf)->hm_agt_hst)->dst_rlm)
									SS_SET_OCTET( ss_dest_realm, ((((msg->act_apn)->apn_inf)->agt_inf)->hm_agt_hst)->dst_rlm, gavp3, avp);
					
								/*Set Destination-Host avp*/
								if(((((msg->act_apn)->apn_inf)->agt_inf)->hm_agt_hst)->dst_hst)
									SS_SET_OCTET( ss_dest_host, ((((msg->act_apn)->apn_inf)->agt_inf)->hm_agt_hst)->dst_hst, gavp3, avp);	

								CHECK_FCT_DO( fd_msg_avp_add( gavp2, MSG_BRW_LAST_CHILD, gavp3 ), goto error);
							}
					
							CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2 ), goto error );
						}

						CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1 ), goto error );
	
					} while(((msg->act_apn)->apn_inf =((msg->act_apn)->apn_inf)->next) != NULL);				
				}

				CHECK_FCT_DO( fd_msg_avp_add( *req, MSG_BRW_LAST_CHILD, gavp ), goto error  );

			} while((msg->act_apn =(msg->act_apn)->next) != NULL);
			
		}

		/*Set Equivalent-PLMN-List avp*/
		if(msg->eqv_plmn_lst){

			CHECK_FCT_DO( fd_msg_avp_new ( ss_eqv_plmn_list, 0,&gavp), goto error);	

			/*Set Visited-PLMN-Id avp*/
			if((msg->eqv_plmn_lst)->vis_plmn_id){
				do{
							
					if(((msg->eqv_plmn_lst)->vis_plmn_id)->plmn_id)
						SS_SET_OCTET( ss_visited_plmn_id, ((msg->eqv_plmn_lst)->vis_plmn_id)->plmn_id, gavp, avp);
	
				} while(((msg->eqv_plmn_lst)->vis_plmn_id = ((msg->eqv_plmn_lst)->vis_plmn_id)->next));				
			}
			
			CHECK_FCT_DO( fd_msg_avp_add( *req, MSG_BRW_LAST_CHILD, gavp ), goto error  );		
		}

		/*Set MME-Number-for-MT-SMS avp*/
		if(msg->mme_num_mtsmsm)
			SS_SET_OCTET( ss_mme_num_for_mt_sms, msg->mme_num_mtsmsm, *req, avp);

		/*Set SMS-Register-Request avp*/
		if(msg->sms_reg)
			SS_SET_I32( ss_sms_reg_req, msg->sms_reg, *req, avp);		

		/*Set Coupled-Node-Diameter-ID avp*/
		if(msg->coupl_nd_dia_id)
			SS_SET_OCTET( ss_copl_nd_dia_id, msg->coupl_nd_dia_id, *req, avp);				
			
	}

	else
		return 0;
	
	return 1;

	error:
		return 0;
	
}


/***********************************************************************************************/
/* Set Authentication-Information-Request command											   */
/***********************************************************************************************/
int ss_msg_air_set(struct msg ** req, struct air_msg * msg){

	union avp_value val;
	struct avp *avp, *gavp;
	struct session *sess = NULL;

	if(req && msg){

		/*Create new AIR message, create a new sessiona, set vendor-spec-app-id and auth-sess-state*/
		CREATE_INIT_MSG(ss_cmd_air);

		/*set destinatin host,destination realm and supported features*/
		SS_SET_COMMON;
		
		/*Set User-Name AVP*/
		if(msg->usr_name)
			SS_SET_OCTET( ss_user_name, msg->usr_name, *req, avp);

		/* Set Requested-EUTRAN-Authentication-Info */
		if(msg->req_eutran_auth){
	
			CHECK_FCT_DO(fd_msg_avp_new(ss_req_eutran_auth_info, 0, &gavp),goto error);
			
			/*Set Number-Of-Requested-Vectors*/
			if((msg->req_eutran_auth)->num_req_vect)
				SS_SET_U32( ss_num_of_req_vects, (msg->req_eutran_auth)->num_req_vect, gavp, avp);

			/*Set Immediate-Response-Preferred*/
			if((msg->req_eutran_auth)->immd_resp_pref)
				SS_SET_U32( ss_immdt_res_prefrd, (msg->req_eutran_auth)->immd_resp_pref, gavp, avp);

			/*Set Re-synchronization-Info*/
			if((msg->req_eutran_auth)->re_sync_inf)
				SS_SET_OCTET( ss_re_synch_info, (msg->req_eutran_auth)->re_sync_inf, gavp, avp);
			
			CHECK_FCT_DO(fd_msg_avp_add(*req, MSG_BRW_LAST_CHILD, gavp), goto error);
		}

		/* Set Requested-UTRAN-GERAN-Authentication-Info */
		if(msg->req_utran_geran_auth){
	
			CHECK_FCT_DO(fd_msg_avp_new(ss_req_utran_geran_auth_info, 0, &gavp),goto error);
	
			/*Set Number-Of-Requested-Vectors*/
			if((msg->req_utran_geran_auth)->num_req_vect)
				SS_SET_U32( ss_num_of_req_vects, (msg->req_utran_geran_auth)->num_req_vect, gavp, avp);

			/*Set Immediate-Response-Preferred*/
			if((msg->req_utran_geran_auth)->immd_resp_pref)
				SS_SET_U32( ss_immdt_res_prefrd, (msg->req_utran_geran_auth)->immd_resp_pref, gavp, avp);

			/*Set Re-synchronization-Info*/
			if((msg->req_utran_geran_auth)->re_sync_inf)
				SS_SET_OCTET( ss_re_synch_info, (msg->req_utran_geran_auth)->re_sync_inf, gavp, avp);
			
			CHECK_FCT_DO(fd_msg_avp_add(*req, MSG_BRW_LAST_CHILD, gavp), goto error);
		}

		/*Set Visted-Plmn-Id avp from message*/
		if(msg->vis_plmn_id)
			SS_SET_OCTET( ss_visited_plmn_id, msg->vis_plmn_id, *req, avp);

	}

	else
		return 0;
	
	return 1;

	error:
		return 0;


}

/***********************************************************************************************/
/* Set  Cancel-Location-Request command														   */
/***********************************************************************************************/
int ss_msg_clr_set(struct msg ** req, struct clr_msg * msg){

	union avp_value val;
	struct avp *avp, *gavp;
	struct session *sess = NULL;	

	if(req && msg){

		/*Create new CLR message, create a new sessiona, set vendor-spec-app-id and auth-sess-state*/
		CREATE_INIT_MSG(ss_cmd_clr);

		/*set destinatin host,destination realm and supported features*/
		SS_SET_COMMON;
		
		/*Set User-Name AVP*/
		if(msg->usr_name)
			SS_SET_OCTET( ss_user_name, msg->usr_name, *req, avp);

		/* Set Cancellation-Type*/
		if(msg->canc_typ)
			SS_SET_I32( ss_cancel_type, msg->canc_typ, *req, avp);

		/* Set CLR-Flags*/
		if(msg->clr_flgs)
			SS_SET_U32( ss_clr_flgs, msg->clr_flgs, *req, avp);

	}

	else
		return 0;
	
	return 1;

	error:
		return 0;

}

/***********************************************************************************************/
/* Set  Insert-Subscriber-Data-Request command												   */
/***********************************************************************************************/

int ss_msg_idr_set(struct msg ** req, struct idr_msg * msg){

	union avp_value val;
	struct avp *avp, *gavp, *gavp1, *gavp2, *gavp3, *gavp4, *gavp5;
	struct session *sess = NULL;

	if(req && msg){

		/*Create new IDR message, create a new sessiona, set vendor-spec-app-id and auth-sess-state*/
		CREATE_INIT_MSG(ss_cmd_idr);

		/*set destinatin host,destination realm and supported features*/
		SS_SET_COMMON;
		
		/*Set User-Name AVP*/
		if(msg->usr_name)
			SS_SET_OCTET( ss_user_name, msg->usr_name, *req, avp);
	
		/* Set Subscription-Data*/
		if(msg->subc_dt){
					
			CHECK_FCT_DO( fd_msg_avp_new( ss_subsc_data, 0, &gavp), goto error);

			/* Set Subscriber-Status*/
			if((msg->subc_dt)->subc_st)
				SS_SET_I32( ss_subscr_status, (msg->subc_dt)->subc_st, gavp, avp);
		
			/* Set MSISDN*/
			if((msg->subc_dt)->msisdn)
				SS_SET_OCTET(  ss_msisdn, (msg->subc_dt)->msisdn, gavp, avp);

			/* Set A-MSISDN*/
			if((msg->subc_dt)->a_msisdn)
				SS_SET_OCTET(  ss_a_msisdn, (msg->subc_dt)->a_msisdn, gavp, avp);

			/* Set STN-SR*/
			if((msg->subc_dt)->stn_sr)
				SS_SET_OCTET( ss_stn_sr, (msg->subc_dt)->stn_sr, gavp, avp);

			/* Set ICS-Indicator*/
			if((msg->subc_dt)->ics_ind)
				SS_SET_I32( ss_ics_indicator, (msg->subc_dt)->ics_ind, gavp, avp);

			/* Set Network-Access-Mode*/
			if((msg->subc_dt)->net_acc_mod)
				SS_SET_I32( ss_net_access_mode, (msg->subc_dt)->net_acc_mod, gavp, avp);

			/* Set Operator-Determined-Barring*/
			if((msg->subc_dt)->odb)
				SS_SET_U32( ss_operator_det_barring, (msg->subc_dt)->odb, gavp, avp);

			/* Set Regional-Subscription-Zone-Code*/
			if((msg->subc_dt)->rg_zn_cd){
					
				do{

					if(((msg->subc_dt)->rg_zn_cd)->zn_cd)
						SS_SET_U32( ss_regional_subscrip_zone_code, (msg->subc_dt)->hplmn_odb, gavp, avp);

				} while( (((msg->subc_dt)->rg_zn_cd) = (((msg->subc_dt)->rg_zn_cd)->next)) != NULL);
			}

			/* Set Access-Restriction-Data*/
			if((msg->subc_dt)->acc_restr_dt)
				SS_SET_U32( ss_access_restrict_data, (msg->subc_dt)->acc_restr_dt, gavp, avp);
	
			/* Set APN-OI-Replacement */
			if((msg->subc_dt)->apn_oi_repl)
				SS_SET_OCTET( ss_apn_oi_replacement, (msg->subc_dt)->apn_oi_repl, gavp, avp);

			/*Set LCS-Info*/					
			if((msg->subc_dt)->lcs_inf){
		
				CHECK_FCT_DO( fd_msg_avp_new( ss_lcs_info, 0, &gavp1), goto error);
	
				/* Set GMLC-Number */
				if(((msg->subc_dt)->lcs_inf)->gmlc_nm){
						
					do{
						if((((msg->subc_dt)->lcs_inf)->gmlc_nm)->num)
							SS_SET_OCTET( ss_gmlc_num, (((msg->subc_dt)->lcs_inf)->gmlc_nm)->num, gavp1, avp);

					} while((((msg->subc_dt)->lcs_inf)->gmlc_nm = (((msg->subc_dt)->lcs_inf)->gmlc_nm)->next) != NULL);
				}

				/* Set LCS-PrivacyException */
				if(((msg->subc_dt)->lcs_inf)->prv_excp){
					
					do{
						CHECK_FCT_DO( fd_msg_avp_new( ss_lcs_privacyexception, 0, &gavp2), goto error);

						/* Set SS-Code*/
						if((((msg->subc_dt)->lcs_inf)->prv_excp)->ss_cd)
							SS_SET_OCTET( ss_ss_code, (((msg->subc_dt)->lcs_inf)->prv_excp)->ss_cd, gavp2, avp);

						/* Set SS-Status*/
						if((((msg->subc_dt)->lcs_inf)->prv_excp)->ss_sts)
							SS_SET_OCTET( ss_ss_status, (((msg->subc_dt)->lcs_inf)->prv_excp)->ss_sts, gavp2, avp);

						/* Set Notification-To-UE-User*/
						if((((msg->subc_dt)->lcs_inf)->prv_excp)->ntf_usr)
							SS_SET_I32( ss_notif_to_ue_user, (((msg->subc_dt)->lcs_inf)->prv_excp)->ntf_usr, gavp2, avp);

						/* Set External-Client*/
						if((((msg->subc_dt)->lcs_inf)->prv_excp)->extr_cln){

							CHECK_FCT_DO( fd_msg_avp_new( ss_extr_cli, 0, &gavp3), goto error);

							do{

								/* Set Client-Identity */
								if(((((msg->subc_dt)->lcs_inf)->prv_excp)->extr_cln)->cln_id)
									SS_SET_OCTET( ss_cli_id, ((((msg->subc_dt)->lcs_inf)->prv_excp)->extr_cln)->cln_id, gavp3, avp);

								/* Set GMLC-Restriction*/
								if(((((msg->subc_dt)->lcs_inf)->prv_excp)->extr_cln)->gmlc_rstr)
									SS_SET_I32( ss_gmlc_restr, ((((msg->subc_dt)->lcs_inf)->prv_excp)->extr_cln)->gmlc_rstr, gavp3, avp);

								/* Set Notification-To-UE-User */
								if(((((msg->subc_dt)->lcs_inf)->prv_excp)->extr_cln)->ntf_usr)
									SS_SET_I32( ss_notif_to_ue_user, ((((msg->subc_dt)->lcs_inf)->prv_excp)->extr_cln)->ntf_usr, gavp3, avp);

								CHECK_FCT_DO( fd_msg_avp_add(gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);

							} while(((((msg->subc_dt)->lcs_inf)->prv_excp)->extr_cln = ((((msg->subc_dt)->lcs_inf)->prv_excp)->extr_cln)->next) != NULL);

						}

						/* Set PLMN-Client*/
						if((((msg->subc_dt)->lcs_inf)->prv_excp)->plmn_cln){

							do{
								if(((((msg->subc_dt)->lcs_inf)->prv_excp)->plmn_cln)->cln)
									SS_SET_I32( ss_plmn_cli, ((((msg->subc_dt)->lcs_inf)->prv_excp)->plmn_cln)->cln, gavp2, avp);
							} while(((((msg->subc_dt)->lcs_inf)->prv_excp)->plmn_cln = ((((msg->subc_dt)->lcs_inf)->prv_excp)->plmn_cln)->next) != NULL);

						}

						/* Set Service-Type*/
						if((((msg->subc_dt)->lcs_inf)->prv_excp)->srv_typ){

							do{
								CHECK_FCT_DO( fd_msg_avp_new( ss_servc_type, 0, &gavp3), goto error);

								/* Set ServiceTypeIdentity*/
								if(((((msg->subc_dt)->lcs_inf)->prv_excp)->srv_typ)->servtyp_id)
									SS_SET_I32( ss_servctypeid, ((((msg->subc_dt)->lcs_inf)->prv_excp)->srv_typ)->servtyp_id, gavp3, avp);

								/* Set GMLC-Restriction*/
								if(((((msg->subc_dt)->lcs_inf)->prv_excp)->srv_typ)->gmlc_rstr)
									SS_SET_I32( ss_gmlc_restr, ((((msg->subc_dt)->lcs_inf)->prv_excp)->srv_typ)->gmlc_rstr, gavp3, avp);

								/* Set Notification-To-UE-User*/
								if(((((msg->subc_dt)->lcs_inf)->prv_excp)->srv_typ)->ntf_usr)
									SS_SET_I32( ss_notif_to_ue_user, ((((msg->subc_dt)->lcs_inf)->prv_excp)->srv_typ)->ntf_usr, gavp3, avp);
											
								CHECK_FCT_DO( fd_msg_avp_add( gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);

							} while(((((msg->subc_dt)->lcs_inf)->prv_excp)->srv_typ = ((((msg->subc_dt)->lcs_inf)->prv_excp)->srv_typ)->next) != NULL);

						}
							
						CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2), goto error);

					} while((((msg->subc_dt)->lcs_inf)->prv_excp = (((msg->subc_dt)->lcs_inf)->prv_excp)->next) != NULL);
				}

				/* Set MO-LR */
				if(((msg->subc_dt)->lcs_inf)->mo_lr){
	
					CHECK_FCT_DO( fd_msg_avp_new( ss_mo_lr, 0, &gavp2), goto error);
				
					do{
						/* Set SS-Code*/
						if((((msg->subc_dt)->lcs_inf)->mo_lr)->ss_cd)
							SS_SET_OCTET( ss_ss_code, (((msg->subc_dt)->lcs_inf)->mo_lr)->ss_cd, gavp2, avp);

						/* Set SS-Status*/
						if((((msg->subc_dt)->lcs_inf)->mo_lr)->ss_sts)
							SS_SET_OCTET( ss_ss_status, (((msg->subc_dt)->lcs_inf)->mo_lr)->ss_sts, gavp2, avp);

						CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2), goto error);
				
					} while((((msg->subc_dt)->lcs_inf)->mo_lr = (((msg->subc_dt)->lcs_inf)->mo_lr)->next) != NULL);
				}
						
				CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);
						
			}
					
			/* Set Teleservice-List & TS-Code*/
			if(((msg->subc_dt)->tele_srv) && (((msg->subc_dt)->tele_srv)->ts_cd)){
						
				CHECK_FCT_DO( fd_msg_avp_new( ss_teleservice_list, 0, &gavp1), goto error);
				do{
							
					if((((msg->subc_dt)->tele_srv)->ts_cd)->code)
						SS_SET_OCTET( ss_ts_code, (((msg->subc_dt)->tele_srv)->ts_cd)->code, gavp1,avp);
					
				} while((((msg->subc_dt)->tele_srv)->ts_cd = (((msg->subc_dt)->tele_srv)->ts_cd)->next) != NULL);						
				CHECK_FCT_DO( fd_msg_avp_add(gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);
			}

			/* Set Call-Barring-Info*/
			if((msg->subc_dt)->call_br_inf){

				do{
	
					CHECK_FCT_DO( fd_msg_avp_new( ss_call_barr_info, 0, &gavp1), goto error);

					/*Set SS-Code*/	
					if(((msg->subc_dt)->call_br_inf)->ss_cd)
						SS_SET_OCTET( ss_ss_code, ((msg->subc_dt)->call_br_inf)->ss_cd, gavp1, avp);

					/*Set SS-Code*/	
					if(((msg->subc_dt)->call_br_inf)->ss_cd)
						SS_SET_OCTET( ss_ss_status, ((msg->subc_dt)->call_br_inf)->ss_cd, gavp1, avp);

					CHECK_FCT_DO( fd_msg_avp_add(gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);	

				} while(((msg->subc_dt)->call_br_inf = ((msg->subc_dt)->call_br_inf)->next) != NULL);
			}
				
			/* Set 3GPP-Charging-Characteristics*/
			if((msg->subc_dt)->charg_char)
				SS_SET_OCTET( ss_3gpp_charging_char, (msg->subc_dt)->charg_char, gavp, avp);

			/* Set AMBR*/
			if((msg->subc_dt)->ambr){

				CHECK_FCT_DO( fd_msg_avp_new( ss_ambr, 0, &gavp1), goto error);

				/* Set Max-Requested-Bandwidth-UL */
				if(((msg->subc_dt)->ambr)->mx_req_bw_ul)
					SS_SET_U32( ss_max_req_band_ul, ((msg->subc_dt)->ambr)->mx_req_bw_ul, gavp1, avp);

				/* Set Max-Requested-Bandwidth-DL */
				if(((msg->subc_dt)->ambr)->mx_req_bw_dl)
					SS_SET_U32( ss_max_req_band_dl, ((msg->subc_dt)->ambr)->mx_req_bw_dl, gavp1, avp);

				CHECK_FCT_DO( fd_msg_avp_add(gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);	
			}
		
			/* Set APN-Configuration-Profile*/
			if((msg->subc_dt)->apn_cnf_prf){

				CHECK_FCT_DO( fd_msg_avp_new( ss_apn_conf_prof, 0, &gavp1), goto error);

				/*Set Context-Identifier*/
				if(((msg->subc_dt)->apn_cnf_prf)->contxt_id)
					SS_SET_U32( ss_context_id, ((msg->subc_dt)->apn_cnf_prf)->contxt_id, gavp1, avp);

				/*Set All-APN-Configurations-Included-Indicator */
				if(((msg->subc_dt)->apn_cnf_prf)->all_apn)
					SS_SET_I32( ss_all_apn_config_incl_ind, ((msg->subc_dt)->apn_cnf_prf)->all_apn, gavp1, avp);

				/*Set APN-Configuration*/
				if(((msg->subc_dt)->apn_cnf_prf)->apn_cnf){

					do{

						CHECK_FCT_DO( fd_msg_avp_new( ss_apn_conf, 0, &gavp2), goto error);

						/*Set Context-Identifier*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->contxt_id)
							SS_SET_U32( ss_context_id, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->contxt_id, gavp2, avp);

						/* Set Served-Party-IP-Address*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->srv_prty_addr){

							do{

								SS_SET_OCTET( ss_servd_party_ip_addr, ((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->srv_prty_addr)->addr, gavp2, avp);	
									
							} while(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->srv_prty_addr = ((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->srv_prty_addr)->next) != NULL);
						}

						/*Set PDN-Type*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->pdn_typ)
							SS_SET_I32( ss_pdn_type, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->pdn_typ, gavp2, avp);

						/* Set Service-Selection*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->srv_sel)
							SS_SET_OCTET( ss_service_selection, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->srv_sel, gavp2, avp);

						/* Set eps_qos_prof: EPS-Subscribed-QoS-Profile*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->eps_qos_prof){
								
							CHECK_FCT_DO( fd_msg_avp_new( ss_eps_subscd_qos_prof, 0, &gavp3), goto error);
								
							/* Set QoS-Class-Identifier*/
							if(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->eps_qos_prof)->cls_id)
								SS_SET_I32( ss_qos_class_id, ((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->eps_qos_prof)->cls_id, gavp3, avp);

							/* Set Allocation-Retention-Priority*/
							if(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->eps_qos_prof)->allc_ret_prio){

								CHECK_FCT_DO( fd_msg_avp_new( ss_alloc_retention_prio, 0, &gavp4), goto error);

								/* Set Priority-Level */
								if((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->eps_qos_prof)->allc_ret_prio)->prio_lev)
									SS_SET_U32( ss_prio_level, (((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->eps_qos_prof)->allc_ret_prio)->prio_lev, gavp4, avp);

								/* Set Pre-emption-Capability*/
								if((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->eps_qos_prof)->allc_ret_prio)->emp_cap)
									SS_SET_I32( ss_pre_emp_capb, (((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->eps_qos_prof)->allc_ret_prio)->emp_cap, gavp4, avp);

								/* Set Pre-emption-Vulnerability*/
								if((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->eps_qos_prof)->allc_ret_prio)->emp_vuln)
									SS_SET_I32( ss_pre_emp_vuln, (((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->eps_qos_prof)->allc_ret_prio)->emp_vuln, gavp4, avp);

								CHECK_FCT_DO( fd_msg_avp_add( gavp3, MSG_BRW_LAST_CHILD, gavp4), goto error);
							}

							CHECK_FCT_DO( fd_msg_avp_add( gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);
						}

						/* Set VPLMN-Dynamic-Address-Allowed*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->vplmn_dyn_allw)
							SS_SET_I32( ss_vplmn_dyn_addr_allowed, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->vplmn_dyn_allw, gavp2, avp);

						/* Set MIP6-Agent-Info AVP*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->mip6_agt_inf){
						
							CHECK_FCT_DO( fd_msg_avp_new ( ss_mip6_agent_info, 0,&gavp3), goto error );
							
							/* Set MIP-Home-Agent-Address 1 avp*/
							if(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->mip6_agt_inf)->hm_agt_addr1)
								SS_SET_OCTET( ss_mip_home_agent_addr, ((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->mip6_agt_inf)->hm_agt_addr1, gavp3, avp);
	
							/* Set MIP-Home-Agent-Address 2 avp*/
							if(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->mip6_agt_inf)->hm_agt_addr2)
								SS_SET_OCTET( ss_mip_home_agent_addr, ((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->mip6_agt_inf)->hm_agt_addr2, gavp3, avp);				
					
							/* Set MIP-Home-Agent-Host avp*/
							if(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->mip6_agt_inf)->hm_agt_hst){
		
								CHECK_FCT_DO( fd_msg_avp_new ( ss_mip_home_agen_host, 0,&gavp4), goto error );	

								/* Set Destination-Realm avp*/
								if((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->mip6_agt_inf)->hm_agt_hst)->dst_rlm)
									SS_SET_OCTET( ss_dest_realm, (((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->mip6_agt_inf)->hm_agt_hst)->dst_rlm, gavp4, avp);
				
								/*Set Destination-Host avp*/
								if((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->mip6_agt_inf)->hm_agt_hst)->dst_hst)
									SS_SET_OCTET( ss_dest_host, (((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->mip6_agt_inf)->hm_agt_hst)->dst_hst, gavp4, avp);	

								CHECK_FCT_DO( fd_msg_avp_add( gavp3, MSG_BRW_LAST_CHILD, gavp4 ), goto error);
							}
					
							CHECK_FCT_DO( fd_msg_avp_add( gavp2, MSG_BRW_LAST_CHILD, gavp3 ), goto error );
						}

						/* Set Visited-Network-Identifier */
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->vist_net_id)
							SS_SET_OCTET( ss_vistd_net_id, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->vist_net_id, gavp2, avp);

						/* Set PDN-GW-Allocation-Type */
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->pdn_alloc_typ)
							SS_SET_I32( ss_pdn_gw_alloc_type, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->pdn_alloc_typ, gavp2, avp);
									
						/* Set 3GPP-Charging-Characteristics*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->charg_char)
							SS_SET_OCTET( ss_3gpp_charging_char, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->charg_char, gavp2, avp);

						/* Set AMBR*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->ambr){

							CHECK_FCT_DO( fd_msg_avp_new( ss_ambr, 0, &gavp3), goto error);

 							/* Set Max-Requested-Bandwidth-UL */
							if(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->ambr)->mx_req_bw_ul)
								SS_SET_U32( ss_max_req_band_ul, ((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->ambr)->mx_req_bw_ul, gavp3, avp);

							/* Set Max-Requested-Bandwidth-DL */
							if(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->ambr)->mx_req_bw_dl)
								SS_SET_U32( ss_max_req_band_dl, ((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->ambr)->mx_req_bw_dl, gavp3, avp);

							CHECK_FCT_DO( fd_msg_avp_add(gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);	
						}

						/*Set Specific-APN-Info avp*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf){
				
							do{
			
								CHECK_FCT_DO( fd_msg_avp_new ( ss_specific_apn_info, 0,&gavp3), goto error );
				
								/* Set Service-Selection avp*/
								if(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->serv_sel)
									SS_SET_OCTET( ss_service_selection, ((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->serv_sel, gavp3, avp);
								
								/* Set MIP6-Agent-Info avp*/
								if(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->agt_inf){
									
									CHECK_FCT_DO( fd_msg_avp_new ( ss_mip6_agent_info, 0,&gavp4), goto error );
							
									/* Set MIP-Home-Agent-Address avp*/
									if((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->agt_inf)->hm_agt_addr1)
										SS_SET_OCTET( ss_mip_home_agent_addr, (((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->agt_inf)->hm_agt_addr1, gavp4, avp);	

									/* Set MIP-Home-Agent-Address avp*/
									if((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->agt_inf)->hm_agt_addr2)
										SS_SET_OCTET( ss_mip_home_agent_addr, (((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->agt_inf)->hm_agt_addr2, gavp4, avp);				
				
									/* Set MIP-Home-Agent-Host avp*/
									if((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->agt_inf)->hm_agt_hst){
			
										CHECK_FCT_DO( fd_msg_avp_new ( ss_mip_home_agen_host, 0,&gavp5), goto error );

										/* Set Destination-Realm avp*/
										if(((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->agt_inf)->hm_agt_hst)->dst_rlm)
											SS_SET_OCTET( ss_dest_realm, ((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->agt_inf)->hm_agt_hst)->dst_rlm, gavp5, avp);
					
										/*Set Destination-Host avp*/
										if(((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->agt_inf)->hm_agt_hst)->dst_hst)
											SS_SET_OCTET( ss_dest_host, ((((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->agt_inf)->hm_agt_hst)->dst_hst, gavp5, avp);	

										CHECK_FCT_DO( fd_msg_avp_add( gavp4, MSG_BRW_LAST_CHILD, gavp5 ), goto error);
									}
					
									CHECK_FCT_DO( fd_msg_avp_add( gavp3, MSG_BRW_LAST_CHILD, gavp4 ), goto error );
								}

								CHECK_FCT_DO( fd_msg_avp_add( gavp2, MSG_BRW_LAST_CHILD, gavp3 ), goto error );
	
							} while(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf =((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_inf)->next) != NULL);				
						}	

						/* Set APN-OI-Replacement*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_oi_repl)
							SS_SET_OCTET( ss_apn_oi_replacement, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->apn_oi_repl, gavp2, avp);

						/* Set SIPTO-Permission*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->sipto_perm)
							SS_SET_I32( ss_sipto_permis, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->sipto_perm, gavp2, avp);
	
						/* Set LIPA-Permission*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->lipa_perm)
							SS_SET_I32( ss_lipa_permis, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->lipa_perm, gavp2, avp);

						/* Set Restoration-Priority*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->res_prio)
							SS_SET_U32( ss_restor_prio, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->res_prio, gavp2, avp);
	
						/* Set SIPTO-Local-Network-Permission*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->sipto_lc_net_perm)
							SS_SET_U32( ss_sipto_local_net_permis, (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->sipto_lc_net_perm, gavp2, avp);

						/* Set WLAN-offloadability*/
						if((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->wln_offld){

							CHECK_FCT_DO( fd_msg_avp_new( ss_wlan_offloadability, 0, &gavp3), goto error);

							/* Set WLAN-offloadability-EUTRAN */							
							if(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->wln_offld)->eutran)
								SS_SET_U32( ss_wlan_offloadability_eutran, ((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->wln_offld)->eutran, gavp3, avp);

							/* Set WLAN-offloadability-UTRAN */							
							if(((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->wln_offld)->utran)
								SS_SET_U32( ss_wlan_offloadability_eutran, ((((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->wln_offld)->utran, gavp3, avp);

							CHECK_FCT_DO( fd_msg_avp_add( gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);
						}

						CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2), goto error);

					} while((((msg->subc_dt)->apn_cnf_prf)->apn_cnf = (((msg->subc_dt)->apn_cnf_prf)->apn_cnf)->next) != NULL);
				}

				CHECK_FCT_DO( fd_msg_avp_add(gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);					
			}
	
			/* Set RAT-Frequency-Selection-Priority-ID*/
			if((msg->subc_dt)->rat_frq_sel_pri_id)
				SS_SET_U32( ss_rat_freq_sel_prior_id, (msg->subc_dt)->rat_frq_sel_pri_id, gavp, avp);

			/* Set Trace-Data*/
			if((msg->subc_dt)->trc_dt){

				CHECK_FCT_DO( fd_msg_avp_new( ss_trace_data, 0, &gavp1), goto error);

				/* Set Trace-Reference*/
				if(((msg->subc_dt)->trc_dt)->trc_ref)
					SS_SET_OCTET( ss_trace_ref, ((msg->subc_dt)->trc_dt)->trc_ref, gavp1, avp);

				/* Set Trace-Depth*/
				if(((msg->subc_dt)->trc_dt)->trc_dpz)
					SS_SET_I32( ss_trace_depth, ((msg->subc_dt)->trc_dt)->trc_dpz, gavp1, avp);

				/* Set Trace-NE-Type-List*/
				if(((msg->subc_dt)->trc_dt)->trc_ne_typ_lst)
					SS_SET_OCTET( ss_trace_ne_type_list, ((msg->subc_dt)->trc_dt)->trc_ne_typ_lst, gavp1, avp);
	
				/* Set Trace-Interface-List*/
				if(((msg->subc_dt)->trc_dt)->trc_if_lst)
					SS_SET_OCTET( ss_trace_interf_list, ((msg->subc_dt)->trc_dt)->trc_if_lst, gavp1, avp);

				/* Set Trace-Event-List*/
				if(((msg->subc_dt)->trc_dt)->trc_evn_lst)
					SS_SET_OCTET( ss_trace_event_list, ((msg->subc_dt)->trc_dt)->trc_evn_lst, gavp1, avp);

				/* Set OMC-Id*/
				if(((msg->subc_dt)->trc_dt)->omc_id)
					SS_SET_OCTET( ss_omc_id, ((msg->subc_dt)->trc_dt)->omc_id, gavp1, avp);

				/* Set Trace-Collection-Entity*/
				if(((msg->subc_dt)->trc_dt)->trc_coll_enty)
					SS_SET_OCTET( ss_trace_coll_entity, ((msg->subc_dt)->trc_dt)->trc_coll_enty, gavp1, avp);

				/* Set MDT-Configuration*/
				if(((msg->subc_dt)->trc_dt)->mdt_cnf){

					CHECK_FCT_DO( fd_msg_avp_new( ss_mdt_conf, 0, &gavp2), goto error);

					/* Set Job-Type*/
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->jb_typ)
						SS_SET_I32( ss_job_type, (((msg->subc_dt)->trc_dt)->mdt_cnf)->jb_typ, gavp2, avp);

					/* Set Area-Scope */		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop){

						CHECK_FCT_DO( fd_msg_avp_new( ss_area_scope, 0, &gavp3), goto error);

						/* Set Cell-Global-Identity*/
						if(((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->cgi){
							
							do{
										
								if((((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->cgi)->id)
									SS_SET_OCTET( ss_cell_glb_id, (((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->cgi)->id, gavp3, avp);

							} while((((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->cgi = (((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->cgi)->next) != NULL);
									
						}

						/* Set E-UTRAN-Cell-Global-Identity*/
						if(((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->eu_cgi){
						
							do{
										
								if((((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->eu_cgi)->id)
									SS_SET_OCTET( ss_e_utran_cell_glb_id, (((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->eu_cgi)->id, gavp3, avp);

							} while((((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->eu_cgi = (((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->eu_cgi)->next) != NULL);
									
						}

						/* Set Routing-Area-Identity*/
						if(((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->rt_area_id){
							
							do{
										
								if((((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->rt_area_id)->id)
									SS_SET_OCTET( ss_rout_area_id, (((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->rt_area_id)->id, gavp3, avp);

							} while((((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->rt_area_id = (((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->rt_area_id)->next) != NULL);
							
						}

						/* Set Location-Area-Identity*/
						if(((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->lai){
							
							do{
										
								if((((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->lai)->id)
									SS_SET_OCTET( ss_loc_area_id, (((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->lai)->id, gavp3, avp);

							} while((((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->lai = (((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->lai)->next) != NULL);
									
						}

						/* Set Tracking-Area-Identity*/
						if(((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->tai){
							
							do{
										
								if((((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->tai)->id)
									SS_SET_OCTET( ss_track_area_id, (((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->tai)->id, gavp3, avp);

							} while((((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->tai = (((((msg->subc_dt)->trc_dt)->mdt_cnf)->area_scop)->tai)->next) != NULL);
									
						}

						CHECK_FCT_DO( fd_msg_avp_add( gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);

					}	

					/* Set List-Of-Measurements */		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->lst_of_measr)
						SS_SET_U32( ss_list_of_measr, (((msg->subc_dt)->trc_dt)->mdt_cnf)->lst_of_measr, gavp2, avp);

					/* Set Reporting-Trigger */		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->repr_trig)
						SS_SET_U32( ss_repor_trig, (((msg->subc_dt)->trc_dt)->mdt_cnf)->repr_trig, gavp2, avp);

					/* Set Report-Interval */		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->repr_interv)
						SS_SET_I32( ss_repor_intrv, (((msg->subc_dt)->trc_dt)->mdt_cnf)->repr_interv, gavp2, avp);

					/* Set Report-Amount */		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->repr_amnt)
						SS_SET_I32( ss_repor_amount, (((msg->subc_dt)->trc_dt)->mdt_cnf)->repr_amnt, gavp2, avp);
	
					/* Set Event-Threshold-RSRP */		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->evt_thrd_rsrp)
						SS_SET_U32( ss_evt_thrsd_rsrp, (((msg->subc_dt)->trc_dt)->mdt_cnf)->evt_thrd_rsrp, gavp2, avp);

					/* Set Event-Threshold-RSRQ */		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->evt_thrd_rsrq)
						SS_SET_U32( ss_evt_thrsd_rsrq, (((msg->subc_dt)->trc_dt)->mdt_cnf)->evt_thrd_rsrq, gavp2, avp);

					/* Set Logging-Interval*/	
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->lg_interv)
						SS_SET_I32( ss_log_intrv, (((msg->subc_dt)->trc_dt)->mdt_cnf)->lg_interv, gavp2, avp);

					/* Set Logging-Duration */		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->lg_dur)
						SS_SET_I32( ss_log_dur, (((msg->subc_dt)->trc_dt)->mdt_cnf)->lg_dur, gavp2, avp);

					/* Set Measurement-Period-LTE*/	
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->mst_prd_lte)
						SS_SET_I32( ss_measr_perd_lte, (((msg->subc_dt)->trc_dt)->mdt_cnf)->mst_prd_lte, gavp2, avp);

					/* Set Measurement-Period-UMTS*/		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->mst_prd_umts)
						SS_SET_I32( ss_measr_perd_umts, (((msg->subc_dt)->trc_dt)->mdt_cnf)->mst_prd_umts, gavp2, avp);

					/* Set Collection-Period-RMM-LTE*/	
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->cl_prd_rmm_lte)
						SS_SET_I32( ss_coll_perd_rrm_lte, (((msg->subc_dt)->trc_dt)->mdt_cnf)->cl_prd_rmm_lte, gavp2, avp);

					/* Set Collection-Period-RRM-UMTS*/		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->cl_prd_rmm_umts)
						SS_SET_I32( ss_coll_perd_rrm_umts, (((msg->subc_dt)->trc_dt)->mdt_cnf)->cl_prd_rmm_umts, gavp2, avp);

					/* Set Positioning-Method*/		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->pos_measr)
						SS_SET_OCTET( ss_pos_meth, (((msg->subc_dt)->trc_dt)->mdt_cnf)->pos_measr, gavp2, avp);

					/* Set Measurement-Quantity*/		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->measr_qnt)
						SS_SET_OCTET( ss_measr_quant, (((msg->subc_dt)->trc_dt)->mdt_cnf)->measr_qnt, gavp2, avp);

					/* Set Event-Threshold-Event-1F*/		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->evt_thrd_evt_1f)
						SS_SET_I32( ss_evt_thrsd_evt_1f, (((msg->subc_dt)->trc_dt)->mdt_cnf)->evt_thrd_evt_1f, gavp2, avp);

					/* Set Event-Threshold-Event-1I*/		
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->evt_thrd_evt_1i)
						SS_SET_I32( ss_evt_thrsd_evt_1i, (((msg->subc_dt)->trc_dt)->mdt_cnf)->evt_thrd_evt_1i, gavp2, avp);

					/* Set MDT-Allowed-PLMN-Id*/
					if((((msg->subc_dt)->trc_dt)->mdt_cnf)->allw_plmn_id){

						do{

							if(((((msg->subc_dt)->trc_dt)->mdt_cnf)->allw_plmn_id)->id)
								SS_SET_OCTET( ss_mdt_allow_plmn_id, ((((msg->subc_dt)->trc_dt)->mdt_cnf)->allw_plmn_id)->id, gavp2, avp);

						} while(((((msg->subc_dt)->trc_dt)->mdt_cnf)->allw_plmn_id = ((((msg->subc_dt)->trc_dt)->mdt_cnf)->allw_plmn_id)->next) != NULL);

					}

					CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2), goto error);
				}

				CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);				
			}

			/* Set GPRS-Subscription-Data*/
			if((msg->subc_dt)->gprs_sub_dt){

				CHECK_FCT_DO( fd_msg_avp_new( ss_gprs_subsc_data, 0, &gavp1), goto error);

				/* Set Complete-Data-List-Included-Indicator*/
				if(((msg->subc_dt)->gprs_sub_dt)->incl_ind)
					SS_SET_I32( ss_complete_data_list_incl_ind, ((msg->subc_dt)->gprs_sub_dt)->incl_ind, gavp1, avp);

				/* Set PDP-Context*/
				if(((msg->subc_dt)->gprs_sub_dt)->pdp_ctx){

					do{

						CHECK_FCT_DO( fd_msg_avp_new( ss_pdp_context, 0, &gavp2), goto error);

						/* Set Context-Identifier */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->contxt_id)
							SS_SET_U32( ss_context_id, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->contxt_id, gavp2, avp);

						/* Set PDP-Type */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->pdp_typ)
							SS_SET_OCTET( ss_pdp_type, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->pdp_typ, gavp2, avp);

						/* Set PDP-Address */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->pdp_addr)
							SS_SET_OCTET( ss_pdp_addr, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->pdp_addr, gavp2, avp);					

						/* Set QoS-Subscribed */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->qos_subcd)
							SS_SET_OCTET( ss_qos_subscr, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->qos_subcd, gavp2, avp);

						/* Set VPLMN-Dynamic-Address-Allowed */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->vplmn_dyn_allw)
							SS_SET_I32( ss_vplmn_dyn_addr_allowed, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->vplmn_dyn_allw, gavp2, avp);						

						/* Set Service-Selection*/
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->serv_sel)
							SS_SET_OCTET( ss_service_selection, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->serv_sel, gavp2, avp);

						/* Set 3GPP-Charging-Characteristics */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->charg_char)
							SS_SET_OCTET( ss_3gpp_charging_char, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->charg_char, gavp2, avp);					

						/* Set Ext-PDP-Type */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->ext_pdp_typ)
							SS_SET_OCTET( ss_ext_pdp_type, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->ext_pdp_typ, gavp2, avp);		

						/* Set Ext-PDP-Address */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->ext_pdp_addr)
							SS_SET_OCTET( ss_ext_pdp_addr, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->ext_pdp_addr, gavp2, avp);		

						/* Set AMBR*/
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->ambr){

							CHECK_FCT_DO( fd_msg_avp_new( ss_ambr, 0, &gavp3), goto error);

							/* Set Max-Requested-Bandwidth-UL */
							if(((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->ambr)->mx_req_bw_ul)
								SS_SET_U32( ss_max_req_band_ul, ((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->ambr)->mx_req_bw_ul, gavp3, avp);

							/* Set Max-Requested-Bandwidth-DL */
							if(((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->ambr)->mx_req_bw_dl)
								SS_SET_U32( ss_max_req_band_dl, ((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->ambr)->mx_req_bw_dl, gavp3, avp);
		
							CHECK_FCT_DO( fd_msg_avp_add(gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);	
						}
							
						/* Set APN-OI-Replacement*/
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->apn_oi_repl)
							SS_SET_OCTET( ss_apn_oi_replacement, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->apn_oi_repl, gavp2, avp);

						/* Set SIPTO-Permission */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->sipto_perm)
							SS_SET_I32( ss_sipto_permis, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->sipto_perm, gavp2, avp);					

						/* Set LIPA-Permission */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->lipa_perm)
							SS_SET_I32( ss_lipa_permis, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->lipa_perm, gavp2, avp);		

						/* Set Restoration-Priority */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->res_prio)
							SS_SET_U32( ss_restor_prio, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->res_prio, gavp2, avp);
						/* Set SIPTO-Local-Network-Permission */
						if((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->sipto_lc_net_perm)
							SS_SET_U32( ss_sipto_local_net_permis, (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->sipto_lc_net_perm, gavp2, avp);	

						CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2), goto error);
					
					} while((((msg->subc_dt)->gprs_sub_dt)->pdp_ctx = (((msg->subc_dt)->gprs_sub_dt)->pdp_ctx)->next) != NULL);
				}

				CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);

			}

			/* Set CSG-Subscription-Data */
			if((msg->subc_dt)->csg_sub_dt){

				do{

					CHECK_FCT_DO( fd_msg_avp_new( ss_csg_subsc_data, 0, &gavp1), goto error);

					/* Set CSG-Id*/
					if(((msg->subc_dt)->csg_sub_dt)->csg_id)
						SS_SET_U32( ss_csg_id, ((msg->subc_dt)->csg_sub_dt)->csg_id, gavp1, avp);

					/* Set Expiration-Date*/
					if(((msg->subc_dt)->csg_sub_dt)->expr_date)
						SS_SET_OCTET( ss_expir_date, ((msg->subc_dt)->csg_sub_dt)->expr_date, gavp1, avp);

					/* Set Service-Selection*/
					if(((msg->subc_dt)->csg_sub_dt)->serv_sel){

						do{

							if((((msg->subc_dt)->csg_sub_dt)->serv_sel)->serv_sel)
								SS_SET_OCTET( ss_service_selection, (((msg->subc_dt)->csg_sub_dt)->serv_sel)->serv_sel, gavp1, avp);						
	
						} while((((msg->subc_dt)->csg_sub_dt)->serv_sel = (((msg->subc_dt)->csg_sub_dt)->serv_sel)->next) != NULL);
					}

					/* Set Visited-PLMN-Id*/
					if(((msg->subc_dt)->csg_sub_dt)->vis_plmn_id)
						SS_SET_OCTET( ss_visited_plmn_id, ((msg->subc_dt)->csg_sub_dt)->vis_plmn_id, gavp1, avp);

					CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);							

				} while(((msg->subc_dt)->csg_sub_dt = ((msg->subc_dt)->csg_sub_dt)->next) != NULL);

			}
	
			/* Set Roaming-Restricted-Due-To-Unsupported-Feature*/		
			if((msg->subc_dt)->roam_restr)
				SS_SET_I32( ss_roam_restr_dueto_unsuppr_featr, (msg->subc_dt)->roam_restr, gavp, avp);

			/* Set Subscribed-Periodic-RAU-TAU-Timer*/		
			if((msg->subc_dt)->subcd_rau_tau_tmr)
				SS_SET_U32( ss_subscr_priod_rau_tau_timer, (msg->subc_dt)->subcd_rau_tau_tmr, gavp, avp);

			/* Set MPS-Priority*/		
			if((msg->subc_dt)->mps_prio)
				SS_SET_U32( ss_mps_prio, (msg->subc_dt)->mps_prio, gavp, avp);	

			/* Set VPLMN-LIPA-Allowed*/		
			if((msg->subc_dt)->vplmn_lipa_allw)
				SS_SET_I32( ss_vplmn_lipa_allow, (msg->subc_dt)->vplmn_lipa_allw, gavp, avp);

			/* Set Relay-Node-Indicator*/		
			if((msg->subc_dt)->rly_ind)
				SS_SET_I32( ss_rely_nod_ind, (msg->subc_dt)->rly_ind, gavp, avp);

			/* Set MDT-User-Consent*/		
			if((msg->subc_dt)->mdt_usr_cnst)
				SS_SET_I32( ss_mdt_usr_consent, (msg->subc_dt)->mdt_usr_cnst, gavp, avp);	

			/* Set Subscribed-VSRVCC*/		
			if((msg->subc_dt)->subsc_vsrvcc)
				SS_SET_I32( ss_subscr_vsrvcc, (msg->subc_dt)->subsc_vsrvcc, gavp, avp);

			/* Set ProSe-Subscription-Data*/
			if((msg->subc_dt)->prose_subsc_dt){

				CHECK_FCT_DO( fd_msg_avp_new( ss_prose_subsc_data, 0, &gavp1), goto error);

				/* Set ProSe-Permission*/
				if(((msg->subc_dt)->prose_subsc_dt)->prose_perm)
					SS_SET_I32( ss_prose_permis, ((msg->subc_dt)->prose_subsc_dt)->prose_perm, gavp1, avp);

				CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);
			}

			/* Set Subscription-Data-Flags*/		
			if((msg->subc_dt)->subsc_dt_flgs)
				SS_SET_U32( ss_subsc_data_flgs, (msg->subc_dt)->subsc_dt_flgs, gavp, avp);

			CHECK_FCT_DO( fd_msg_avp_add( *req, MSG_BRW_LAST_CHILD, gavp), goto error);
		}

		/* Set IDR- Flags*/
		if(msg->idr_flgs)
			SS_SET_U32( ss_idr_flgs, msg->idr_flgs, *req, avp);

		/* Set Reset-ID*/
		if(msg->rst_id){

			do{

				if((msg->rst_id)->id)
					SS_SET_OCTET( ss_rst_id, (msg->rst_id)->id, *req, avp);		

			} while((msg->rst_id = (msg->rst_id)->next) != NULL);
		}

	}

	else
		return 0;

	return 1;

	error:
		return 0;


}



/***********************************************************************************************/
/* Set  Delete-Subscriber-Data-Request command												   */
/***********************************************************************************************/

int ss_msg_dsr_set(struct msg ** req, struct dsr_msg * msg){

	union avp_value val;
	struct avp *avp, *gavp;
	struct session *sess = NULL;

	if(req && msg){

		/*Create new DSR message, create a new sessiona, set vendor-spec-app-id and auth-sess-state*/
		CREATE_INIT_MSG(ss_cmd_dsr);

		/*set destinatin host,destination realm and supported features*/
		SS_SET_COMMON;

		/*Set User-Name AVP*/
		if(msg->usr_name)
			SS_SET_OCTET( ss_user_name, msg->usr_name, req, avp);
		
		/* Set DSR-Flags*/
		if(msg->dsr_flgs)		
			SS_SET_U32( ss_dsr_flgs, msg->dsr_flgs, *req, avp);

		/* Set Context-Identifier */
		if(msg->cntx_id){

			do{
			
				if((msg->cntx_id)->id)
					SS_SET_U32( ss_context_id, (msg->cntx_id)->id, *req, avp);

			} while((msg->cntx_id = (msg->cntx_id)->next) != NULL);
		}

		/* Set Trace-Reference*/
		if(msg->trc_ref)		
			SS_SET_OCTET( ss_trace_ref, msg->trc_ref, *req, avp);

		/* Set TS-Code */
		if(msg->ts_cd){

			do{
			
				if((msg->ts_cd)->code)
					SS_SET_OCTET( ss_ts_code, (msg->ts_cd)->code, *req, avp);

			} while((msg->ts_cd = (msg->ts_cd)->next) != NULL);
		}

		/* Set SS-Code */
		if(msg->ss_cd){

			do{
			
				if((msg->ss_cd)->code)
					SS_SET_OCTET( ss_ss_code, (msg->ss_cd)->code, *req, avp);

			} while((msg->ss_cd = (msg->ss_cd)->next) != NULL);
		}

	}

	else
		return 0;

	return 1;

	error:
		return 0;
}


/***********************************************************************************************/
/* Set  Purge-UE-Request command															   */
/***********************************************************************************************/

int ss_msg_pur_set(struct msg ** req, struct pur_msg * msg){

	union avp_value val;
	struct avp *avp, *gavp, *gavp1, *gavp2;	
	struct session *sess = NULL;

	if(req && msg){

		/*Create new PUR message, create a new sessiona, set vendor-spec-app-id and auth-sess-state*/
		CREATE_INIT_MSG(ss_cmd_pur);

		/*set destinatin host,destination realm and supported features*/
		SS_SET_COMMON;
		
		/*Set User-Name AVP*/
		if(msg->usr_name)
			SS_SET_OCTET( ss_user_name, msg->usr_name, req, avp);

		/* Set PUR-Flags*/
		if(msg->pur_flgs)		
			SS_SET_U32( ss_pur_flgs, msg->pur_flgs, *req, avp);

		/* Set EPS-Location-Information */
		if(msg->eps_lc_inf){

			CHECK_FCT_DO( fd_msg_avp_new( ss_eps_loc_info, 0, &gavp), goto error);

			/* Set MME-Location-Information */
			if((msg->eps_lc_inf)->mme_loc_inf){

				CHECK_FCT_DO( fd_msg_avp_new( ss_mme_loc_info, 0, &gavp1), goto error);

				/* Set E-UTRAN-Cell-Global-Identity*/
				if(((msg->eps_lc_inf)->mme_loc_inf)->eutran_cgi)
					SS_SET_OCTET( ss_e_utran_cell_glb_id, ((msg->eps_lc_inf)->mme_loc_inf)->eutran_cgi, gavp1, avp);

				/* Set Tracking-Area-Identity*/
				if(((msg->eps_lc_inf)->mme_loc_inf)->trak_area_id)
					SS_SET_OCTET( ss_track_area_id, ((msg->eps_lc_inf)->mme_loc_inf)->trak_area_id, gavp1, avp);

				/* Set Geographical-Information	*/
				if(((msg->eps_lc_inf)->mme_loc_inf)->geog_inf)
					SS_SET_OCTET( ss_geo_info, ((msg->eps_lc_inf)->mme_loc_inf)->geog_inf, gavp1, avp);

				/* Set Geodetic-Information*/
				if(((msg->eps_lc_inf)->mme_loc_inf)->geod_inf)
					SS_SET_OCTET( ss_geodetic_info, ((msg->eps_lc_inf)->mme_loc_inf)->geod_inf, gavp1, avp);

				/* Set Current-Location-Retrieved*/
				if(((msg->eps_lc_inf)->mme_loc_inf)->curr_loc_ret)
					SS_SET_I32( ss_curr_loc_retrvd, ((msg->eps_lc_inf)->mme_loc_inf)->curr_loc_ret, gavp1, avp);

				/* Set Age-Of-Location-Information*/
				if(((msg->eps_lc_inf)->mme_loc_inf)->age_loc_inf)
					SS_SET_U32( ss_age_of_loc_info, ((msg->eps_lc_inf)->mme_loc_inf)->age_loc_inf, gavp1, avp);

				/* Set User-CSG-Information */
				if(((msg->eps_lc_inf)->mme_loc_inf)->ust_csg_inf){

					CHECK_FCT_DO( fd_msg_avp_new( ss_usr_csg_info, 0, &gavp2), goto error);

					/* Set CSG-Id*/
					if((((msg->eps_lc_inf)->mme_loc_inf)->ust_csg_inf)->csg_id)
						SS_SET_U32( ss_csg_id, (((msg->eps_lc_inf)->mme_loc_inf)->ust_csg_inf)->csg_id, gavp2, avp);

					/* Set CSG-Access-Mode*/
					if((((msg->eps_lc_inf)->mme_loc_inf)->ust_csg_inf)->accs_mod)
						SS_SET_I32( ss_csg_accss_mode, (((msg->eps_lc_inf)->mme_loc_inf)->ust_csg_inf)->accs_mod, gavp2, avp); 

					/* Set CSG-Membership-Indication*/
					if((((msg->eps_lc_inf)->mme_loc_inf)->ust_csg_inf)->memb_ind)
						SS_SET_I32( ss_csg_memb_ind, (((msg->eps_lc_inf)->mme_loc_inf)->ust_csg_inf)->memb_ind, gavp2, avp); 

					CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2), goto error);
				}
 
				CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);
			}

			/* Set SGSN-Location-Information */
			if((msg->eps_lc_inf)->sgns_loc_inf){

				CHECK_FCT_DO( fd_msg_avp_new( ss_sgsn_loc_info, 0, &gavp1), goto error);

				/* Set Cell-Global-Identity*/
				if(((msg->eps_lc_inf)->sgns_loc_inf)->cgi)
					SS_SET_OCTET( ss_cell_glb_id, ((msg->eps_lc_inf)->sgns_loc_inf)->cgi, gavp1, avp);

				/* Set Location-Area-Identity*/
				if(((msg->eps_lc_inf)->sgns_loc_inf)->lai)
					SS_SET_OCTET( ss_loc_area_id, ((msg->eps_lc_inf)->sgns_loc_inf)->lai, gavp1, avp);

				/* Set Service-Area-Identity*/
				if(((msg->eps_lc_inf)->sgns_loc_inf)->sai)
					SS_SET_OCTET( ss_servc_area_id, ((msg->eps_lc_inf)->sgns_loc_inf)->sai, gavp1, avp);

				/* Set Routing-Area-Identity*/
				if(((msg->eps_lc_inf)->sgns_loc_inf)->rai)
					SS_SET_OCTET( ss_rout_area_id, ((msg->eps_lc_inf)->sgns_loc_inf)->rai, gavp1, avp);

				/* Set Geographical-Information	*/
				if(((msg->eps_lc_inf)->sgns_loc_inf)->geog_inf)
					SS_SET_OCTET( ss_geo_info, ((msg->eps_lc_inf)->sgns_loc_inf)->geog_inf, gavp1, avp);

				/* Set Geodetic-Information*/
				if(((msg->eps_lc_inf)->sgns_loc_inf)->geod_inf)
					SS_SET_OCTET( ss_geodetic_info, ((msg->eps_lc_inf)->sgns_loc_inf)->geod_inf, gavp1, avp);

				/* Set Current-Location-Retrieved*/
				if(((msg->eps_lc_inf)->sgns_loc_inf)->curr_loc_ret)
					SS_SET_I32( ss_curr_loc_retrvd, ((msg->eps_lc_inf)->sgns_loc_inf)->curr_loc_ret, gavp1, avp);

				/* Set Age-Of-Location-Information*/
				if(((msg->eps_lc_inf)->sgns_loc_inf)->age_loc_inf)
					SS_SET_U32( ss_age_of_loc_info, ((msg->eps_lc_inf)->sgns_loc_inf)->age_loc_inf, gavp1, avp);

				/* Set User-CSG-Information */
				if(((msg->eps_lc_inf)->sgns_loc_inf)->ust_csg_inf){

					CHECK_FCT_DO( fd_msg_avp_new( ss_usr_csg_info, 0, &gavp2), goto error);

					/* Set CSG-Id*/
					if((((msg->eps_lc_inf)->sgns_loc_inf)->ust_csg_inf)->csg_id)
						SS_SET_U32( ss_csg_id, (((msg->eps_lc_inf)->sgns_loc_inf)->ust_csg_inf)->csg_id, gavp2, avp);

					/* Set CSG-Access-Mode*/
					if((((msg->eps_lc_inf)->sgns_loc_inf)->ust_csg_inf)->accs_mod)
						SS_SET_I32( ss_csg_accss_mode, (((msg->eps_lc_inf)->sgns_loc_inf)->ust_csg_inf)->accs_mod, gavp2, avp); 

					/* Set CSG-Membership-Indication*/
					if((((msg->eps_lc_inf)->sgns_loc_inf)->ust_csg_inf)->memb_ind)
						SS_SET_I32( ss_csg_memb_ind, (((msg->eps_lc_inf)->sgns_loc_inf)->ust_csg_inf)->memb_ind, gavp2, avp); 

					CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2), goto error);
				}
 
				CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);
			}

			CHECK_FCT_DO( fd_msg_avp_add( *req, MSG_BRW_LAST_CHILD, gavp), goto error);
		}		
	}

	else
		return 0;

	return 1;

	error:
		return 0;
}


/***********************************************************************************************/
/* Set  Reset-Request command																   */
/***********************************************************************************************/

int ss_msg_rsr_set(struct msg ** req, struct rsr_msg * msg){

	union avp_value val;
	struct avp *avp, *gavp;
	struct session *sess = NULL;	

	if(req && msg){

		/*Create new RSR message, create a new sessiona, set vendor-spec-app-id and auth-sess-state*/
		CREATE_INIT_MSG(ss_cmd_rsr);

		/*set destinatin host,destination realm and supported features*/
		SS_SET_COMMON;
		
		/* Set User-Id */
		if(msg->usr_id){

			do{

				if((msg->usr_id)->id)
					SS_SET_OCTET( ss_usr_id, (msg->usr_id)->id, *req, avp);
			} while((msg->usr_id = (msg->usr_id)->next) != NULL);
		}

		/* Set Reset-ID */
		if(msg->rst_id){

			do{

				if((msg->rst_id)->id)
					SS_SET_OCTET( ss_rst_id, (msg->rst_id)->id, *req, avp);		

			} while((msg->rst_id = (msg->rst_id)->next) != NULL);
		}

	}

	else
		return 0;

	return 1;

	error:
		return 0;
}



/***********************************************************************************************/
/* Set  Notify-Request command																   */
/***********************************************************************************************/

int ss_msg_nor_set(struct msg ** req, struct nor_msg * msg){

	union avp_value val;
	struct avp *avp, *gavp, *gavp1;
	struct session *sess = NULL;

	if(req && msg){

		/*Create new NOR message, create a new sessiona, set vendor-spec-app-id and auth-sess-state*/
		CREATE_INIT_MSG(ss_cmd_nor);

		/*set destinatin host,destination realm and supported features*/
		SS_SET_COMMON;
		
		/*Set User-Name AVP*/
		if(msg->usr_name)
			SS_SET_OCTET( ss_user_name, msg->usr_name, req, avp);
	
		/* Set Terminal-Information */
		if(msg->term_info){
			
			CHECK_FCT_DO( fd_msg_avp_new ( ss_terminal_info, 0, &gavp), goto error  );
			
			/*Set IMEI */
			if((msg->term_info)->imei)
				SS_SET_OCTET( ss_imei, (msg->term_info)->imei, gavp, avp);

			/*set Software-Version*/
			if((msg->term_info)->soft_vrs)
				SS_SET_OCTET( ss_soft_version, (msg->term_info)->soft_vrs, gavp, avp);

			/*set 3GPP2-MEID */
			if((msg->term_info)->meid)
				SS_SET_OCTET( ss_meid, (msg->term_info)->meid, gavp, avp);

			CHECK_FCT_DO( fd_msg_avp_add( *req, MSG_BRW_LAST_CHILD, gavp ), goto error  );	
		}

		/* Set MIP6-Agent-Info */
		if(msg->mip6_agt_inf){

			CHECK_FCT_DO( fd_msg_avp_new ( ss_mip6_agent_info, 0,&gavp), goto error );
							
			/*set MIP-Home-Agent-Address 1 avp*/
			if((msg->mip6_agt_inf)->hm_agt_addr1)
				SS_SET_OCTET( ss_mip_home_agent_addr, (msg->mip6_agt_inf)->hm_agt_addr1, gavp, avp);

			/*set MIP-Home-Agent-Address 2 avp*/
			if((msg->mip6_agt_inf)->hm_agt_addr2)
				SS_SET_OCTET( ss_mip_home_agent_addr, (msg->mip6_agt_inf)->hm_agt_addr2, gavp, avp);			
					
			/*set MIP-Home-Agent-Host avp*/
			if((msg->mip6_agt_inf)->hm_agt_hst){
		
				CHECK_FCT_DO( fd_msg_avp_new ( ss_mip_home_agen_host, 0,&gavp1), goto error );
		
				/*set Destination-Realm avp*/
				if(((msg->mip6_agt_inf)->hm_agt_hst)->dst_rlm)
					SS_SET_OCTET( ss_dest_realm, ((msg->mip6_agt_inf)->hm_agt_hst)->dst_rlm, gavp1, avp);
			
				/*Set Destination-Host avp*/
				if(((msg->mip6_agt_inf)->hm_agt_hst)->dst_hst)
					SS_SET_OCTET( ss_dest_host, ((msg->mip6_agt_inf)->hm_agt_hst)->dst_hst, gavp1, avp);	

				CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1 ), goto error);
			}
					
			CHECK_FCT_DO( fd_msg_avp_add( *req, MSG_BRW_LAST_CHILD, gavp ), goto error );
			
		}

		/* Set Visited-Network-Identifier*/
		if(msg->vist_net_id)
			SS_SET_OCTET( ss_vistd_net_id, msg->vist_net_id, *req, avp);		
	
		/* Set Context-Identifier avp*/
		if(msg->contxt_id)
			SS_SET_U32( ss_context_id, msg->contxt_id, *req, avp);
		
		/*set Service-Selection avp*/
		if(msg->serv_sel)	
			SS_SET_OCTET( ss_service_selection, msg->serv_sel, *req, avp);

		/* Set Alert-Reason avp*/
		if(msg->alrt_reasn)
			SS_SET_I32( ss_alert_reason, msg->alrt_reasn, *req, avp);


		/*Set UE-SRVCC-Capability AVP*/
		if(msg->ue_srvcc)
			SS_SET_I32( ss_ue_srvcc_capab, msg->ue_srvcc, *req, avp);

		/* Set NOR-Flags AVP */
		if(msg->nor_flgs)
			SS_SET_U32( ss_nor_flgs, msg->nor_flgs, *req, avp);

		/* Set Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP*/
		if(msg->hm_ims_vop)
			SS_SET_I32( ss_homog_suppr_ims_vop_sess, msg->hm_ims_vop, *req, avp);

	}

	else
		return 0;

	return 1;

	error:
		return 0;
}

