
#include <unistd.h>

#include "test.h"


static void wait_till_state_open(char *dest_host, int len){
	
	
	if(ss_peer_state( dest_host, len) != 1)
		fprintf(stdout, "Waiting until connection to remote peer is estabilished ...\n");	

	while(ss_peer_state( dest_host, len) != 1)
		sleep(1);
}

/*Set Terminal-Information group AVP and its child AVPs*/
static void set_terminal_info(struct msg ** msg, utf8string *imei, utf8string *soft_ver, octetstring *meid){

	struct avp * tmp_gavp;
	
	if(!msg)
		return;

	if((!imei) && (!meid) && (!soft_ver))
		return;

	/*Create Terminal-Information group AVP*/
	SS_CHECK( ss_create_terminal_information(&tmp_gavp), "Terminal-Information group AVP created.\n", "Failed to create Terminal-Information group AVP\n");

	/*Set IMEI AVP*/
	if(imei)
		SS_CHECK( ss_set_imei( &tmp_gavp, imei, strlen((char *)imei)), "IMEI AVP set.\n","Failed to set IMEI AVP\n");

	/*Set Software-Version AVP*/
	if(soft_ver)
		SS_CHECK( ss_set_software_version( &tmp_gavp, soft_ver, strlen((char *)soft_ver)), "Software-Version AVP set.\n","Failed to set Software-Version AVP\n");

	/*Set 3GPP2-MEID AVP*/
	if(meid)
		SS_CHECK( ss_set_3gpp2_meid( &tmp_gavp, meid, strlen((char *)meid)), "3GPP2-MEID AVP set.\n","Failed to set 3GPP2-MEID AVP\n");	
	
	/*Add Terminal-Information group AVP in to message*/ 	
	SS_CHECK( ss_add_avp(  (avp_or_msg **)msg, tmp_gavp), "Terminal-Information group AVP added in to message\n", "Failed to add Terminal-Information group AVP in to message\n");
}

/*Set Equivalent-PLMN-List group AVP and its child AVPs*/
static void set_eqv_plmn_lst(struct msg ** msg, octetstring vis_plmn_id[][4], size_t arr_size){

	struct avp * tmp_gavp = NULL;
	size_t tmp_size = 0;

	if((!msg) || (!vis_plmn_id)) return;

	/*Create Equivalent-PLMN-List group AVP*/
	SS_CHECK( ss_create_equivalent_plmn_list(&tmp_gavp), "Equivalent-PLMN-List group AVP created.\n", "Failed to create Equivalent-PLMN-List AVP\n");

	/*Set Visited-PLMN-Id AVP*/
	tmp_size = arr_size;
	while(tmp_size){
	 
		SS_CHECK( ss_set_visited_plmn_id( (avp_or_msg **)&tmp_gavp, vis_plmn_id[arr_size - tmp_size], strlen((char *)vis_plmn_id[arr_size - tmp_size])), "Visited-PLMN-Id AVP set into Equivalent-PLMN-List.\n","Failed to set Visited-PLMN-Id AVP into Equivalent-PLMN-List\n");
	
		tmp_size --;
	}

	/*Add Equivalent-PLMN-List into message*/ 	
	SS_CHECK( ss_add_avp(  (avp_or_msg **)msg, tmp_gavp), "Equivalent-PLMN-List AVP into into Update-Location-Request message\n", "Failed to add Equivalent-PLMN-List AVP into Update-Location-Request message\n");
}

/*Set Active-APN group AVP and its child AVPs*/	
static void set_active_apn(struct msg **msg, unsigned32 context_id, utf8string * serv_sel, address * ipv4, address * ipv6, diameterid * host, diameterid * realm, octetstring * vis_net_id){

	struct avp * tmp_gavp = NULL;
	int i;

	if(!msg)
		return;
	if((!serv_sel) && (!ipv4) && (!ipv6) && (!host) && (!realm) && (!vis_net_id))
		return;
	/*Create Active-APN group AVP*/
	SS_CHECK( ss_create_active_apn(&tmp_gavp), "Active-APN group AVP created.\n", "Failed to create Active-APN group AVP\n");

	/*Set Context-Identifier AVP*/
	SS_CHECK( ss_set_context_identifier( (avp_or_msg **)&tmp_gavp, context_id), "context identifier set in Active-APN.\n", "Failed to set Context-Identifier in Active-APN.\n");

	/*Set Service-Selection AVP*/
	SS_CHECK( ss_set_service_selection( (avp_or_msg **)&tmp_gavp, serv_sel, strlen((char *)serv_sel)), "Service-Selection AVP set in Active-APN AVP.\n","Failed to set Service-Selection AVP in Active-APN AVP\n");

	/*Set MIP6-Agent-Info group AVP and its child AVPs*/
	test_set_mip6( (avp_or_msg **)&tmp_gavp, ipv4, ipv6, (char *)host, (char *)realm);

	/*Set Visited-Network-Identifier AVP*/	
	SS_CHECK( ss_set_visited_network_identifier( (avp_or_msg **)&tmp_gavp, vis_net_id, strlen((char *)vis_net_id)), "Visited-Network-Identifier AVP set in Active-APN AVP.\n","Failed to set Visited-Network-Identifier AVP in Active-APN AVP.\n");

	/*Set Specific-APN-Info group AVP (only 3 AVPs for testing) and its child AVPs*/
	for (i = 1 ; i<3 ; i++)		
		test_set_spec_apn_info( &tmp_gavp, serv_sel, ipv4, ipv6, host, realm, vis_net_id);	

	/*Add Specific-APN-Info into Active-APN AVP*/ 	
	SS_CHECK( ss_add_avp( (avp_or_msg **)msg, tmp_gavp), "Active-APN AVP added into Update-Location-Request message\n", "Failed to add Active-APN AVP into Update-Location-Request message\n"); 
}

/*Set Request Authentication info values to their parent AVP*/
static int set_req_auth_info(struct avp **gavp, unsigned32 *num_req_vect, unsigned32 *immd_resp_pref, octetstring *re_sync_inf){

	if(!gavp) return EINVAL;

	if((!num_req_vect) && (!immd_resp_pref) && (!re_sync_inf)) return EINVAL;

	/*Set Number-Of-Requested-Vectors*/
	if(num_req_vect)
		SS_WCHECK( ss_set_number_of_requested_vectors(gavp, *num_req_vect), "Number-Of-Requested-Vectors value set.\n", "failed to set Number-Of-Requested-Vectors.\n", NULL);

	/*Set Immediate-Response-Preferred*/
	if(immd_resp_pref)
		SS_WCHECK( ss_set_immediate_response_preferred(gavp, *immd_resp_pref), "Immediate-Response-Preferred value set.\n", "failed to set Immediate-Response-Preferred.\n", NULL);

	/*Set Re-synchronization-Info*/
	if(re_sync_inf)
		SS_WCHECK( ss_set_re_synchronization_info(gavp, re_sync_inf, strlen((char *)re_sync_inf)), "Re-synchronization-Info value set.\n", "failed to set Re-synchronization-Info.\n", NULL);

	return 0;
	
}

/*Set Requested-EUTRAN-Authentication-Info AVP */
static int set_req_eutran_auth_info(struct msg **msg, unsigned32 *num_req_vect, unsigned32 *immd_resp_pref, octetstring *re_sync_inf){

	struct avp *tmp_gavp = NULL;

	if(!msg) return EINVAL;

	/*Create Requested-EUTRAN-Authentication-Info AVP*/
	SS_CHECK( ss_create_requested_eutran_authentication_info(&tmp_gavp), "Requested-EUTRAN-Authentication-Info AVP created.\n", "failed to create Requested-EUTRAN-Authentication-Info AVP.\n");

	/*Set Requested-EUTRAN-Authentication-Info AVP child AVP values and add it to Requested-EUTRAN-Authentication-Info AVP*/
	SS_WCHECK( set_req_auth_info(&tmp_gavp, num_req_vect, immd_resp_pref, re_sync_inf), "Requested-EUTRAN-Authentication-Info AVP child AVP values set.\n", "failed to set Requested-EUTRAN-Authentication-Info AVP child AVP values.\n", return EINVAL;);

	/*Add to Requested-EUTRAN-Authentication-Info AVP child AVP values message*/
	SS_CHECK( ss_add_avp((avp_or_msg **)msg, tmp_gavp), "Requested-EUTRAN-Authentication-Info AVP child AVP values added.\n", "failed added Requested-EUTRAN-Authentication-Info AVP child AVP values.\n");
	

	return 0;
}

/*Set Requested-UTRAN-GERAN-Authentication-Info AVP */
static int set_req_utran_geran_auth_info(struct msg **msg, unsigned32 *num_req_vect, unsigned32 *immd_resp_pref, octetstring *re_sync_inf){

	struct avp *tmp_gavp = NULL;

	if(!msg) return EINVAL;

	/*Create Requested-UTRAN-Geran-Authentication-Info AVP*/
	SS_CHECK( ss_create_requested_utran_geran_authentication_info(&tmp_gavp), "Requested-UTRAN-GERAN-Authentication-Info AVP created.\n", "failed to create Requested-UTRAN-GERAN-Authentication-Info AVP.\n");

	/*Set Requested-UTRAN-Authentication-Info AVP child AVP values and add it to Requested-EUTRAN-Authentication-Info AVP*/
	SS_WCHECK( set_req_auth_info(&tmp_gavp, num_req_vect, immd_resp_pref, re_sync_inf), "Requested-UTRAN-GERAN-Authentication-Info AVP child AVP values set.\n", "failed to set Requested-UTRAN-GERAN-Authentication-Info AVP child AVP values.\n", return EINVAL;);

	/*Add to Requested-EUTRAN-Authentication-Info AVP child AVP values message*/
	SS_CHECK( ss_add_avp((avp_or_msg **)msg, tmp_gavp), "Requested-UTRAN-GERAN-Authentication-Info AVP child AVP values added.\n", "failed added Requested-UTRAN-GERAN-Authentication-Info AVP child AVP values.\n");
	

	return 0;
}



/*Sends Update-Location-Request message for testing*/
/*'test_types = 0', response should be user unknow*/
/*'test_types = 1', response should be RAT not allowed, */
/*'test_types = 2', response should be roaming not allowed dueto odb feature not supported by MME*/
/*'test_types = any other number' , response should be filled with subscription data of user*/
int test_req_ulr(char * dest_host, int test_type){

	struct msg * ulr = NULL;
	int i;
	
	if(!dest_host)
		return 1;

	diameterid * destination_host = (diameterid *) dest_host;
	utf8string * user_name = gb_user_name;
	unsigned32 feature_list = gb_feature_list[0];
	enum rat_type rat_type = gb_rat_type;
	const size_t size = 2;

	/*Initialize values of AVPs*/	
	if(test_type == 0){
		
		fprintf(stdout, COLOR_GREEN"\nTest : Initializing ULR test that would result in user unknown response."ANSI_COLOR_RESET"\n");
		user_name = (utf8string *)"244444123456788";
	}
	else if(test_type == 1){
		
		fprintf(stdout, COLOR_GREEN"\nTest : Initializing ULR test that would result in RAT not allowed response."ANSI_COLOR_RESET"\n");
		rat_type = VIRTUAL;
	}
	else if(test_type == 2){
		
		fprintf(stdout, COLOR_GREEN"\nTest : Initializing ULR test that would result in roaming not allowed with error diagnostic response."ANSI_COLOR_RESET"\n");
		feature_list = 1;
	}	
	else{

		fprintf(stdout, COLOR_GREEN"\nTest : Initializing ULR test that would result in DIAMER-SUCCESS. "ANSI_COLOR_RESET"\n");
		gb_ula_flags = 3;
	}
		
	/*wait until remote peer connetion state is open*/
	wait_till_state_open(dest_host, strlen(dest_host));
		
	/*Create Update-Location-Request message*/
	SS_CHECK( ss_msg_create_ulr(&ulr), "Update-Location-Request message Created.\n", "Error in creating Update-Location-Request message.\n");

	/*Set Destination-Host AVP*/	
	SS_CHECK( ss_set_destination_host( (avp_or_msg **)&ulr, destination_host,strlen((char *)destination_host)), "Destination-Host AVP set.\n","Failed to set Destination-Host AVP\n");
	
	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **)&ulr, gb_destination_realm,strlen((char *)gb_destination_realm)), "Destination-Realm AVP set.\n","Failed to set Destination-Realm AVP\n");

	/*Set User-Name AVP*/
	SS_CHECK( ss_set_user_name( &ulr, gb_user_name, strlen((char *)user_name)), "User-Name AVP set.\n","Failed to set User-Name AVP\n");
	
	/*Set Supported-Features group AVP and its child AVPs*/
	test_set_supported_features(&ulr, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[0], feature_list);

	/*Set Terminal-Information group AVP and its child AVPs*/
	set_terminal_info( &ulr, gb_imei, gb_software_version, gb_meid);
	
	/*Set RAT-Type AVP*/
	SS_CHECK( ss_set_rat_type( &ulr, rat_type), "RAT-Type AVP set.\n","Failed to set RAT-Type AVP\n");

	/*Set ULR-Flags AVP*/
	SS_CHECK( ss_set_ulr_flags( &ulr, gb_ulr_flags), "ULR-Flags AVP set.\n","Failed to set ULR-Flags AVP\n");

	/*Set UE-SRVCC-Capability AVP*/
	SS_CHECK( ss_set_ue_srvcc_capability( &ulr, gb_ue_srvcc_capability), "UE-SRVCC-Capability AVP set.\n","Failed to set UE-SRVCC-Capability AVP\n");

	/*Set Visited-PLMN-Id AVP*/
	SS_CHECK( ss_set_visited_plmn_id( (avp_or_msg **)&ulr, gb_visited_plmn_id[0], strlen((char *)gb_visited_plmn_id[0])), "Visited-PLMN-Id AVP set.\n","Failed to set Visited-PLMN-Id AVP\n");

	/*Set SGSN-Number AVP*/
	SS_CHECK( ss_set_sgsn_number( &ulr, gb_sgsn_number, strlen((char *)gb_sgsn_number)), "SGSN-Number AVP set.\n","Failed to set SGSN-Number AVP\n");
	
	/*Set Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP*/
	SS_CHECK( ss_set_homogeneous_support_of_ims_voice_over_ps_sessions( &ulr, (int32_t)gb_homogeneous_support_ims_voice_over_ps_sessions), "Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP set.\n","Failed to set Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP\n");

	/*Set GMLC-Address AVP*/
	SS_CHECK( ss_set_gmlc_address( &ulr, gb_gmlc_address, strlen((char *)gb_gmlc_address)), "GMLC-Address AVP set.\n","Failed to set GMLC-Address AVP\n");	

	/*Set Active-APN AVP*/
	for(i = 1; i<3 ; i++)
		set_active_apn(&ulr, gb_context_identifier[0], gb_service_selection, gb_home_agent_address_v4, gb_home_agent_address_v6, gb_home_agent_host_host, gb_home_agent_host_realm, gb_visited_network_identifier);

	/*Set Equivalent-PLMN-List group AVP and its child AVPs*/
	set_eqv_plmn_lst(&ulr, gb_visited_plmn_id, size);
	
	/*Set MME-Number-for-MT-SMS AVP*/
	SS_CHECK( ss_set_mme_number_for_mt_sms( &ulr, gb_mme_number_for_mt_sms, strlen((char *)gb_mme_number_for_mt_sms)), "MME-Number-for-MT-SMS AVP set.\n","Failed to set MME-Number-for-MT-SMS AVP.\n");

	/*Set SMS-Register-Request AVP*/
	SS_CHECK( ss_set_sms_register_request( &ulr, gb_sms_register_request), "SMS-Register-Request AVP set.\n","Failed to set SMS-Register-Request AVP.\n");

	/*Set Coupled-Node-Diameter-ID AVP*/
	SS_CHECK( ss_set_coupled_node_diameter_id( &ulr, gb_coupled_node_diameter_id, strlen((char*)gb_coupled_node_diameter_id)), "Coupled-Node-Diameter-ID AVP set.\n","Failed to set Coupled-Node-Diameter-ID AVP.\n");

	/*send request*/
	SS_CHECK( fd_msg_send( &ulr, test_ans_cb_ulr, (void *)gb_user_name), "ULR message sent.\n", "Failed to send ULR message.\n");

	return 0;
}

/*Sends Cancel-Location-Request message for testing*/
int test_req_clr(char * dest_host){
	
	if(!dest_host)
		return EINVAL;

	diameterid * destination_host= (diameterid *) dest_host;

	/*wait until remote peer connetion state is open*/
	wait_till_state_open(dest_host, strlen(dest_host));

	/*Prepare the message and send CLR message, two Supported-Feature AVPs set inside this function*/
 	test_send_clr(destination_host, gb_destination_realm, gb_user_name, gb_cancellation_type, gb_clr_flags);

	return 0;
}

/*Sends Authentication-Information-Request message for testing*/
int test_req_air(char * dest_host){
	
	struct msg *air = NULL;	

	if(!dest_host)
		return EINVAL;

	diameterid *destination_host= (diameterid *) dest_host;

	/*wait until remote peer connetion state is open*/
	wait_till_state_open(dest_host, strlen(dest_host));

	/*Create AIR message*/
	SS_CHECK( ss_msg_create_air(&air), "Authentication-Information-Request message Created.\n", "Error in creating Authentication-Information-Request message.\n");

	/*Set Destination-Host AVP*/
	SS_CHECK( ss_set_destination_host((avp_or_msg **) &air, destination_host, strlen((char *)destination_host)), "Destination-Host AVP set.\n", "failed to set Destination-Host AVP.\n");

	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **) &air, gb_destination_realm, strlen((char *)gb_destination_realm)), "Destination-Realm AVP set.\n", "failed to set Destination-Realm AVP.\n");

	/* Set User-Name (imsi)*/
	SS_CHECK( ss_set_user_name(&air, gb_user_name, strlen((char *)gb_user_name)), "User-Name set.\n", "failed to set User-Name.\n");

	/* Set Supported-Features AVP (two AVPs will be set)*/
	test_set_supported_features(&air, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(&air, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/*Set Requested-EUTRAN-Authentication-Info */
	SS_WCHECK( set_req_eutran_auth_info(&air, &gb_number_of_requested_vectors, &gb_immediate_response_preferred, gb_re_synchronization_info), "Requested-EUTRAN-Authentication-Info set.\n","Failed to set Requested-EUTRAN-Authentication-Info.\n", NULL);

	/*Set Requested-UTRAN-GERAN-Authentication-Info */
	SS_WCHECK(set_req_utran_geran_auth_info(&air, &gb_number_of_requested_vectors, &gb_immediate_response_preferred, gb_re_synchronization_info), "Requested-UTRAN-Authentication-Info set.\n","Failed to set Requested-UTRAN-Authentication-Info.\n", NULL);

	/*Set Visited-PLMN-Id*/
	SS_CHECK( ss_set_visited_plmn_id((avp_or_msg **)&air, gb_visited_plmn_id[0], strlen((char *)gb_visited_plmn_id[0])), "Visited-PLMN-Id set.\n", "failed to set Visited-PLMN-Id.\n");

	/*Send AIR message*/
	SS_CHECK( fd_msg_send( &air, test_ans_cb_air, (void *)gb_user_name), "AIR message sent.\n", "Failed to send AIR message.\n");

	return 0;
}

/*Sends Insert-Subscriber-Data-Request message for testing*/
int test_req_idr(char * dest_host){
	
	struct msg *idr = NULL;	

	if(!dest_host)
		return EINVAL;

	diameterid *destination_host= (diameterid *) dest_host;

	/*wait until remote peer connetion state is open*/
	wait_till_state_open(dest_host, strlen(dest_host));

	/*Create IDR message*/
	SS_CHECK( ss_msg_create_idr(&idr), "Insert-Subscriber-Data-Request message Created.\n", "Error in creating Insert-Subscriber-Data-Request message.\n");

	/*Set Destination-Host AVP*/
	SS_CHECK( ss_set_destination_host((avp_or_msg **) &idr, destination_host, strlen((char *)destination_host)), "Destination-Host AVP set.\n", "failed to set Destination-Host AVP.\n");

	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **) &idr, gb_destination_realm, strlen((char *)gb_destination_realm)), "Destination-Realm AVP set.\n", "failed to set Destination-Realm AVP.\n");

	/* Set User-Name (imsi)*/
	SS_CHECK( ss_set_user_name(&idr, gb_user_name, strlen((char *)gb_user_name)), "User-Name set.\n", "failed to set User-Name.\n");

	/* Set Supported-Features AVP (two AVPs will be set)*/
	test_set_supported_features(&idr, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(&idr, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/*Set Subscriber-Data*/
	test_set_subsc_data(&idr, (char *)gb_user_name, /*Set GPRS-DATA*/8, NULL);

	/*Set IDR-Flags*/
	SS_CHECK( ss_set_idr_flags(&idr, gb_idr_flags), "IDR-Flags set.\n", "Failed to set IDR-Flags.\n");
	
	/*Set Reset-Id, (only 3 AVPs set for testing)*/
	SS_CHECK( ss_set_reset_id(&idr, gb_reset_ids[0], strlen((char *)gb_reset_ids[0])), "Reset-Id set.\n", "Failed to set Reset-Id.\n");
	SS_CHECK( ss_set_reset_id(&idr, gb_reset_ids[1], strlen((char *)gb_reset_ids[1])), "Reset-Id 2 set.\n", "Failed to set Reset-Id 2.\n");
	SS_CHECK( ss_set_reset_id(&idr, gb_reset_ids[2], strlen((char *)gb_reset_ids[2])), "Reset-Id 3 set.\n", "Failed to set Reset-Id 3.\n");

	/*Send IDR message*/
	SS_CHECK( fd_msg_send( &idr, test_ans_cb_idr, NULL), "IDR message sent.\n", "Failed to send IDR message.\n");

	return 0;
}

/*Sends Delete-Subscriber-Data-Request message for testing*/
int test_req_dsr(char * dest_host){
	
	struct msg *dsr = NULL;	

	if(!dest_host)
		return EINVAL;

	diameterid *destination_host= (diameterid *) dest_host;	

	/*wait until remote peer connetion state is open*/
	wait_till_state_open(dest_host, strlen(dest_host));

	/*Create DSR message*/
	SS_CHECK( ss_msg_create_dsr(&dsr), "Delete-Subscriber-Data-Request message Created.\n", "Error in creating Delete-Subscriber-Data-Request message.\n");

	/*Set Destination-Host AVP*/
	SS_CHECK( ss_set_destination_host((avp_or_msg **) &dsr, destination_host, strlen((char *)destination_host)), "Destination-Host AVP set.\n", "failed to set Destination-Host AVP.\n");

	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **) &dsr, gb_destination_realm, strlen((char *)gb_destination_realm)), "Destination-Realm AVP set.\n", "failed to set Destination-Realm AVP.\n");

	/* Set User-Name (imsi)*/
	SS_CHECK( ss_set_user_name(&dsr, gb_user_name, strlen((char *)gb_user_name)), "User-Name set.\n", "failed to set User-Name.\n");

	/* Set Supported-Features AVP (two AVPs will be set)*/
	test_set_supported_features(&dsr, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(&dsr, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/*Set DSR-Flags*/
	SS_CHECK( ss_set_dsr_flags(&dsr, gb_dsr_flags), "DSR-Flags set.\n", "Failed to set DSR-Flags.\n");

	/*Set Context-Identifier (3 AVPs for testing)*/
	SS_CHECK( ss_set_context_identifier((avp_or_msg **)&dsr, gb_context_identifier[0]), "Context-Identifier set.\n","Failed to set Context-Identifier.\n");
	SS_CHECK( ss_set_context_identifier((avp_or_msg **)&dsr, gb_context_identifier[1]), "Context-Identifier 2 set.\n","Failed to set Context-Identifier 2.\n");
	SS_CHECK( ss_set_context_identifier((avp_or_msg **)&dsr, gb_context_identifier[2]), "Context-Identifier 3 set.\n","Failed to set Context-Identifier 3.\n");

	/*Set Trace-Reference*/
	SS_CHECK( ss_set_trace_reference((avp_or_msg **)&dsr, gb_trace_reference, strlen((char *)gb_trace_reference)), "Trace-Reference set.\n", "Failed to set Trace-Reference.\n");

	/*Set TS-Code (2 AVPs set for testing)*/
	SS_CHECK( ss_set_ts_code((avp_or_msg **)&dsr, gb_ts_code[0], strlen((char *)gb_ts_code[0])), "TS-Code set.\n", "Failed to set TS-Code.\n");
	SS_CHECK( ss_set_ts_code((avp_or_msg **)&dsr, gb_ts_code[1], strlen((char *)gb_ts_code[1])), "TS-Code set.\n", "Failed to set TS-Code.\n");

	/*Set SS-Code (2 AVPs set for testing)*/
	SS_CHECK( ss_set_ss_code((avp_or_msg **)&dsr, gb_ss_code[0], strlen((char *)gb_ss_code[0])), "SS-Code set.\n", "Failed to set SS-Code.\n");
	SS_CHECK( ss_set_ss_code((avp_or_msg **)&dsr, gb_ss_code[1], strlen((char *)gb_ss_code[1])), "SS-Code set.\n", "Failed to set SS-Code.\n");
	
	/*Send DSR message */
	SS_CHECK( fd_msg_send( &dsr, test_ans_cb_dsr, NULL), "DSR message sent.\n", "Failed to send DSR message.\n");

	return 0;
}

/*Sends Purge-UE-Request message for testing*/
int test_req_pur(char * dest_host){
	
	struct msg *pur = NULL;	

	if(!dest_host)
		return EINVAL;

	diameterid *destination_host= (diameterid *) dest_host;	

	/*wait until remote peer connetion state is open*/
	wait_till_state_open(dest_host, strlen(dest_host));

	/*Create PUR message*/
	SS_CHECK( ss_msg_create_pur(&pur), "Purge-UE-Request message Created.\n", "Error in creating Purge-UE-Request message.\n");

	/*Set Destination-Host AVP*/
	SS_CHECK( ss_set_destination_host((avp_or_msg **) &pur, destination_host, strlen((char *)destination_host)), "Destination-Host AVP set.\n", "failed to set Destination-Host AVP.\n");

	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **) &pur, gb_destination_realm, strlen((char *)gb_destination_realm)), "Destination-Realm AVP set.\n", "failed to set Destination-Realm AVP.\n");

	/* Set User-Name (imsi)*/
	SS_CHECK( ss_set_user_name(&pur, gb_user_name, strlen((char *)gb_user_name)), "User-Name set.\n", "failed to set User-Name.\n");

	/* Set Supported-Features AVP (two AVPs will be set)*/
	test_set_supported_features(&pur, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(&pur, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/*Set PUR-Flags*/
	SS_CHECK( ss_set_pur_flags(&pur, gb_pur_flags), "PUR-Flags set.\n", "Failed to set PUR-Flags.\n");

	/*Set EPS-Location-Information*/
	test_set_eps_location_info(&pur);

	/*Send PUR message */
	SS_CHECK( fd_msg_send( &pur, test_ans_cb_pur, NULL), "PUR message sent.\n", "Failed to send PUR message.\n");

	return 0;
}

/*Sends Reset-Request message for testing*/
int test_req_rsr(char * dest_host){
	
	struct msg *rsr = NULL;	

	if(!dest_host)
		return EINVAL;

	diameterid *destination_host= (diameterid *) dest_host;
	
	/*wait until remote peer connetion state is open*/
	wait_till_state_open(dest_host, strlen(dest_host));

	/*Create RSR message*/
	SS_CHECK( ss_msg_create_rsr(&rsr), "Reset-Request message Created.\n", "Error in creating Reset-Request message.\n");

	/*Set Destination-Host AVP*/
	SS_CHECK( ss_set_destination_host((avp_or_msg **) &rsr, destination_host, strlen((char *)destination_host)), "Destination-Host AVP set.\n", "failed to set Destination-Host AVP.\n");

	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **) &rsr, gb_destination_realm, strlen((char *)gb_destination_realm)), "Destination-Realm AVP set.\n", "failed to set Destination-Realm AVP.\n");

	/* Set Supported-Features AVP (two AVPs will be set)*/
	test_set_supported_features(&rsr, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(&rsr, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/*Set User-Id (only 2 AVPs set for training)*/
	SS_CHECK( ss_set_user_id( &rsr, gb_user_id[0], strlen((char *) gb_user_id[0])), "User-Id set.\n", "Failed to set User-Id.\n");
	SS_CHECK( ss_set_user_id( &rsr, gb_user_id[1], strlen((char *) gb_user_id[1])), "User-Id 2 set.\n", "Failed to set User-Id 2.\n");	

	/*Set Reset-Id, (only 3 AVPs set for testing)*/
	SS_CHECK( ss_set_reset_id(&rsr, gb_reset_ids[0], strlen((char *)gb_reset_ids[0])), "Reset-Id set.\n", "Failed to set Reset-Id.\n");
	SS_CHECK( ss_set_reset_id(&rsr, gb_reset_ids[1], strlen((char *)gb_reset_ids[1])), "Reset-Id 2 set.\n", "Failed to set Reset-Id 2.\n");
	SS_CHECK( ss_set_reset_id(&rsr, gb_reset_ids[2], strlen((char *)gb_reset_ids[2])), "Reset-Id 3 set.\n", "Failed to set Reset-Id 3.\n");

	/*Send RSR message */
	SS_CHECK( fd_msg_send( &rsr, test_ans_cb_rsr, NULL), "RSR message sent.\n", "Failed to send RSR message.\n");

	return 0;
}

/*Sends Notify-Request message for testing*/
int test_req_nor(char * dest_host){
	
	struct msg * nor = NULL;
	
	if(!dest_host) return 1;

	diameterid * destination_host= (diameterid *) dest_host;	
		
	/*wait until remote peer connetion state is open*/
	wait_till_state_open(dest_host, strlen(dest_host));
	
	/*Create Notify-Request message*/
	SS_CHECK( ss_msg_create_nor(&nor), "Notify-Request message Created.\n", "Error in creating Notify-Request message.\n");

	/*Set Destination-Host AVP*/	
	SS_CHECK( ss_set_destination_host( (avp_or_msg **)&nor, destination_host,strlen((char *)destination_host)), "Destination-Host AVP set.\n","Failed to set Destination-Host AVP\n");
	
	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **)&nor, gb_destination_realm,strlen((char *)gb_destination_realm)), "Destination-Realm AVP set.\n","Failed to set Destination-Realm AVP\n");

	/*Set User-Name AVP*/
	SS_CHECK( ss_set_user_name( &nor, gb_user_name, strlen((char *)gb_user_name)), "User-Name AVP set.\n","Failed to set User-Name AVP\n");
	
	/*Set Supported-Features group AVP and its child AVPs*/
	test_set_supported_features(&nor, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(&nor, (unsigned32)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);

	/*Set Terminal-Information group AVP and its child AVPs*/
	set_terminal_info( &nor, gb_imei, gb_software_version, gb_meid);
	
	/*Set MIP6-Agent-Info*/
	test_set_mip6((avp_or_msg **)&nor, gb_home_agent_address_v4, gb_home_agent_address_v6, (char *)gb_home_agent_host_host, (char *)gb_home_agent_host_realm);

	/*Set Visited-Network-Identifier*/
	SS_CHECK( ss_set_visited_network_identifier( (avp_or_msg **)&nor, gb_visited_network_identifier, strlen((char *)gb_visited_network_identifier)), "Visited-Network-Identifier set.\n", "Failed to set Visited-Network-Identifier.\n");

	/*Set Context-Identifier*/
	SS_CHECK( ss_set_context_identifier((avp_or_msg **)&nor, gb_context_identifier[0]), "Context-Identifier set.\n", "Failed to set Context-Identifier/\n");

	/*Set Service-Selection*/
	SS_CHECK( ss_set_service_selection( (avp_or_msg **) &nor, gb_service_selection, strlen((char *)gb_service_selection)), "Service-Selection set.\n", "Failed to set Service-Selection.\n");

	/*Set Alert-Reason*/
	SS_CHECK( ss_set_alert_reason(&nor, gb_alert_reason), "Alert-Reason set.\n", "Failed to set Alert-Reason.\n");
	
	/*Set UE-SRVCC-Capability AVP*/
	SS_CHECK( ss_set_ue_srvcc_capability( &nor, gb_ue_srvcc_capability), "UE-SRVCC-Capability AVP set.\n","Failed to set UE-SRVCC-Capability AVP\n");

	/*Set NOR-Flags AVP*/
	SS_CHECK( ss_set_nor_flags( &nor, gb_nor_flags), "NOR-Flags AVP set.\n","Failed to set NOR-Flags AVP\n");
	
	/*Set Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP*/
	SS_CHECK( ss_set_homogeneous_support_of_ims_voice_over_ps_sessions( &nor, (int32_t)gb_homogeneous_support_ims_voice_over_ps_sessions), "Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP set.\n","Failed to set Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP\n");

	/*send request*/
	SS_CHECK( fd_msg_send( &nor, test_ans_cb_nor, NULL), "NOR message sent.\n", "Failed to send NOR message.\n");

	return 0;
}

