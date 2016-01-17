
#include <unistd.h>

#include "test.h"

/*Set Terminal-Information group AVP and its child AVPs*/
static void set_terminal_info(struct msg ** msg, utf8string *imei, utf8string *soft_ver, octetstring *meid, size_t meid_len){

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

	if((!msg) || (!vis_plmn_id)) return;

	/*Create Equivalent-PLMN-List group AVP*/
	SS_CHECK( ss_create_equivalent_plmn_list(&tmp_gavp), "Equivalent-PLMN-List group AVP created.\n", "Failed to create Equivalent-PLMN-List AVP\n");

	/*Set Visited-PLMN-Id AVP*/
	while(arr_size){
	 
		SS_CHECK( ss_set_visited_plmn_id( (avp_or_msg **)&tmp_gavp, vis_plmn_id[arr_size-1], strlen((char *)vis_plmn_id[arr_size-1])), "Visited-PLMN-Id AVP set into Equivalent-PLMN-List.\n","Failed to set Visited-PLMN-Id AVP into Equivalent-PLMN-List\n");
	
		arr_size --;
	}

	/*Add Equivalent-PLMN-List into message*/ 	
	SS_CHECK( ss_add_avp(  (avp_or_msg **)msg, tmp_gavp), "Equivalent-PLMN-List AVP into into Update-Location-Request message\n", "Failed to add Equivalent-PLMN-List AVP into Update-Location-Request message\n");
}

/*Set Specific-APN-Info group AVP (only 3 AVPs for testing) and its child AVPs*/
static void set_spec_apn_info(struct avp **gavp, utf8string *serv_sel, address *ipv4, address *ipv6, diameterid *host, diameterid *realm, octetstring *vis_net_id){

	struct avp * tmp_gavp = NULL;

	if((!gavp) || (serv_sel)) return;

	if((!ipv4) && (!ipv6) && (!host) && (!realm)) return;

	/*Create Specific-APN-Info group AVP*/
	SS_CHECK( ss_create_specific_apn_info(&tmp_gavp), "Specific-APN-Info group AVP created.\n", "Failed to create Specific-APN-Info AVP\n");
	
	/*Set Service-Selection AVP*/
	SS_CHECK( ss_set_service_selection( (avp_or_msg **)&tmp_gavp, serv_sel, strlen((char *)serv_sel)), "Service-Selection AVP set in Specific-APN-Info AVP.\n","Failed to set Service-Selection AVP in Specific-APN-Info AVP\n");

	/*Add MIP6-Agent-Info group AVP in to Specific-APN-Info*/ 	
	test_set_mip6( (avp_or_msg **)&tmp_gavp, ipv4, ipv6, host, realm);

	/*Set Visited-Network-Identifier AVP*/	
	SS_CHECK( ss_set_visited_network_identifier( (avp_or_msg **)&tmp_gavp, vis_net_id, strlen((char *) vis_net_id)), "Visited-Network-Identifier AVP set in Specific-APN-Info.\n","Failed to set Visited-Network-Identifier AVP in Specific-APN-Info.\n");

	/*Add Specific-APN-Info into Active-APN AVP*/ 	
	SS_CHECK( ss_add_avp( (avp_or_msg **)&gavp, tmp_gavp), "Specific-APN-Info AVP added into Active-APN AVP\n", "Failed to add Specific-APN-Info AVP into Active-APN AVP\n");
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
	test_set_mip6( (avp_or_msg **)&tmp_gavp, ipv4, ipv6, host, realm);

	/*Set Visited-Network-Identifier AVP*/	
	SS_CHECK( ss_set_visited_network_identifier( (avp_or_msg **)&tmp_gavp, vis_net_id, strlen((char *)vis_net_id)), "Visited-Network-Identifier AVP set in Active-APN AVP.\n","Failed to set Visited-Network-Identifier AVP in Active-APN AVP.\n");

	/*Set Specific-APN-Info group AVP (only 3 AVPs for testing) and its child AVPs*/
	for (i = 1 ; i<3 ; i++)		
		set_spec_apn_info( &tmp_gavp, serv_sel, ipv4, ipv6, host, realm, vis_net_id);	

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
	int len = 0;
	
	if(!dest_host)
		return 1;

	diameterid * destination_host= (diameterid *) dest_host;
	diameterid * destination_realm = (diameterid *)"localdomain";
	utf8string * user_name = (utf8string *)"244444123456789";	
	unsigned32 feature_list_id = 1;
	unsigned32 feature_list = 2; 		
	utf8string * imei = (utf8string *)"2345";
	utf8string * software_version = (utf8string *)"22";
	octetstring * meid = (octetstring *)"2345";
	enum rat_type rat_type = UTRAN;	
	unsigned32 ulr_flags = 8;
	enum ue_srvcc_capability ue_srvcc_capability = UE_SRVCC_SUPPORTED;
	const size_t size = 2;
	octetstring visited_plmn_id[2][4]= {{0x01,0x10,0x01,'\0'},{0x01,0x10,0x01,'\0'}}; /*MCC = 011, MNC = 001*/	
	octetstring  sgsn_number [] = {0x25,0x14,0x56};
	enum homogeneous_support_of_ims_voice_over_ps_sessions homogeneous_support_ims_voice_over_ps_sessions = HOMO_IMS_VOICE_OVER_PS_NOT_SUPPORTED;
	address * gmlc_address = (address *)"gmlc.local";
	unsigned32 context_identifier = 1;
	utf8string * service_selection = (utf8string *)"serviceSelection";
	address  home_agent_address_v4 [] = {0xef,0x01,0x01,0x01, '\0'};
	address  home_agent_address_v6 [] = {0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, 0x01,0x01,0xff,0xff,0x7f, 0x01, 0x01, 0x01, '\0'};
	diameterid * home_agent_host_host = (diameterid *) "pdngateway1";
	diameterid * home_agent_host_realm = (diameterid *) "epc.mnc001.mcc001.3gppnetwork.org ";
	octetstring * visited_network_identifier = (octetstring *)"visited-net-id";
	octetstring * mme_number_for_mt_sms = (octetstring *)"mme-23";
	enum sms_register_request sms_register_request = SMS_REGISTRATION_REQUIRED;
	diameterid * coupled_node_diameter_id = (diameterid *)"coupl-node";


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
	else	
		fprintf(stdout, COLOR_GREEN"\nTest : Initializing ULR test that would result in DIAMER-SUCCESS. "ANSI_COLOR_RESET"\n");

		
	/*wait until remote peer connetion state is open*/
	len = strlen(dest_host);
	if(ss_peer_state( dest_host, len) != 1)
		fprintf(stdout, "Waiting until connection to remote peer is estabilished ...\n");	
	while(ss_peer_state( dest_host, len) != 1)
		sleep(2);
	
	/*Create Update-Location-Request message*/
	SS_CHECK( ss_msg_create_ulr(&ulr), "Update-Location-Request message Created.\n", "Error in creating Update-Location-Request message.\n");

	/*Set Destination-Host AVP*/	
	SS_CHECK( ss_set_destination_host( (avp_or_msg **)&ulr, destination_host,strlen((char *)destination_host)), "Destination-Host AVP set.\n","Failed to set Destination-Host AVP\n");
	
	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **)&ulr, destination_realm,strlen((char *)destination_realm)), "Destination-Realm AVP set.\n","Failed to set Destination-Realm AVP\n");

	/*Set User-Name AVP*/
	SS_CHECK( ss_set_user_name( &ulr, user_name, strlen((char *)user_name)), "User-Name AVP set.\n","Failed to set User-Name AVP\n");
	
	/*Set Supported-Features group AVP and its child AVPs*/
	test_set_supported_features(&ulr, (unsigned32)VENDOR_ID_3GPP, feature_list_id, feature_list);

	/*Set Terminal-Information group AVP and its child AVPs*/
	set_terminal_info( &ulr, imei, software_version, meid, strlen((char *)meid));
	
	/*Set RAT-Type AVP*/
	SS_CHECK( ss_set_rat_type( &ulr, rat_type), "RAT-Type AVP set.\n","Failed to set RAT-Type AVP\n");

	/*Set ULR-Flags AVP*/
	SS_CHECK( ss_set_ulr_flags( &ulr, ulr_flags), "ULR-Flags AVP set.\n","Failed to set ULR-Flags AVP\n");

	/*Set UE-SRVCC-Capability AVP*/
	SS_CHECK( ss_set_ue_srvcc_capability( &ulr, ue_srvcc_capability), "UE-SRVCC-Capability AVP set.\n","Failed to set UE-SRVCC-Capability AVP\n");

	/*Set Visited-PLMN-Id AVP*/
	SS_CHECK( ss_set_visited_plmn_id( (avp_or_msg **)&ulr, visited_plmn_id[0],3), "Visited-PLMN-Id AVP set.\n","Failed to set Visited-PLMN-Id AVP\n");

	/*Set SGSN-Number AVP*/
	SS_CHECK( ss_set_sgsn_number( &ulr, sgsn_number, strlen((char *)sgsn_number)), "SGSN-Number AVP set.\n","Failed to set SGSN-Number AVP\n");
	
	/*Set Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP*/
	SS_CHECK( ss_set_homogeneous_support_of_ims_voice_over_ps_sessions( &ulr, (int32_t)homogeneous_support_ims_voice_over_ps_sessions), "Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP set.\n","Failed to set Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP\n");

	/*Set GMLC-Address AVP*/
	SS_CHECK( ss_set_gmlc_address( &ulr, gmlc_address, strlen((char *)gmlc_address)), "GMLC-Address AVP set.\n","Failed to set GMLC-Address AVP\n");	

	/*Set Active-APN AVP*/
	for(i = 1; i<3 ; i++)
		set_active_apn(&ulr, context_identifier, service_selection, home_agent_address_v4, home_agent_address_v6, home_agent_host_host, home_agent_host_realm, visited_network_identifier);

	/*Set Equivalent-PLMN-List group AVP and its child AVPs*/
	set_eqv_plmn_lst(&ulr, visited_plmn_id, size);
	
	/*Set MME-Number-for-MT-SMS AVP*/
	SS_CHECK( ss_set_mme_number_for_mt_sms( &ulr, mme_number_for_mt_sms, strlen((char *)mme_number_for_mt_sms)), "MME-Number-for-MT-SMS AVP set.\n","Failed to set MME-Number-for-MT-SMS AVP.\n");

	/*Set SMS-Register-Request AVP*/
	SS_CHECK( ss_set_sms_register_request( &ulr, sms_register_request), "SMS-Register-Request AVP set.\n","Failed to set SMS-Register-Request AVP.\n");

	/*Set Coupled-Node-Diameter-ID AVP*/
	SS_CHECK( ss_set_coupled_node_diameter_id( &ulr, coupled_node_diameter_id, strlen((char*)coupled_node_diameter_id)), "Coupled-Node-Diameter-ID AVP set.\n","Failed to set Coupled-Node-Diameter-ID AVP.\n");

	/*send request*/
	SS_CHECK( fd_msg_send( &ulr, test_ans_cb_ulr, NULL), "ULR message sent.\n", "Failed to send ULR message.\n");

	return 0;
}

/*Sends Cancel-Location-Request message for testing*/
int test_req_clr(char * dest_host){
	
	int len = 0;	

	if(!dest_host)
		return EINVAL;

	diameterid * destination_host= (diameterid *) dest_host;
	diameterid * destination_realm = (diameterid *)"localdomain";
	utf8string * user_name = (utf8string *)"244444123456789";	
	enum cancellation_type cancel_type = SUBCRIPTION_WITHDRAWAL;	
	unsigned32 clr_flags = 3; /*CLR msg sent on S6a and reattach required*/
	
	/*waite until remote peer state is open*/
	len = strlen(dest_host);
	if(ss_peer_state( dest_host, len) != 1)
		fprintf(stdout, "Waiting until connection to remote peer is estabilished ...\n");	
	while(ss_peer_state( dest_host, len) != 1)
		sleep(2);

	/*Prepare the message and send CLR message, two Supported-Feature AVPs set inside this function*/
 	test_send_clr(destination_host, destination_realm, user_name, cancel_type, clr_flags);

	return 0;
}

/*Sends Authentication-Information-Request message for testing*/
int test_req_air(char * dest_host){
	
	int len = 0;
	struct msg *air = NULL;	

	if(!dest_host)
		return EINVAL;

	diameterid *destination_host= (diameterid *) dest_host;
	diameterid *destination_realm = (diameterid *)"localdomain";
	utf8string *user_name = (utf8string *)"244444123456789";	
	unsigned32 num_req_vect = 2;
	unsigned32 immd_resp_pref = 1;
	octetstring re_sync_inf[] = {0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11, 0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11, 0x00};
	unsigned32 feature_list_id[] = {1,2};
	unsigned32 feature_list[] = {3,2};
	octetstring visited_plmn_id[]= {0x00,0x10,0x01}; /*MCC = 001, MNC = 001*/

	/*waite until remote peer state is open*/
	len = strlen(dest_host);
	if(ss_peer_state( dest_host, len) != 1)
		fprintf(stdout, "Waiting until connection to remote peer is estabilished ...\n");	
	while(ss_peer_state( dest_host, len) != 1)
		sleep(2);

	/*Create AIR message*/
	SS_CHECK( ss_msg_create_air(&air), "Authentication-Information-Request message Created.\n", "Error in creating Authentication-Information-Request message.\n");

	/*Set Destination-Host AVP*/
	SS_CHECK( ss_set_destination_host((avp_or_msg **) &air, destination_host, strlen((char *)destination_host)), "Destination-Host AVP set.\n", "failed to set Destination-Host AVP.\n");

	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **) &air, destination_realm, strlen((char *)destination_realm)), "Destination-Realm AVP set.\n", "failed to set Destination-Realm AVP.\n");

	/* Set User-Name (imsi)*/
	SS_CHECK( ss_set_user_name(&air, user_name, strlen((char *)user_name)), "User-Name set.\n", "failed to set User-Name.\n");

	/* Set Supported-Features AVP (two AVPs will be set)*/
	test_set_supported_features(&air, (unsigned32)VENDOR_ID_3GPP, feature_list_id[0], feature_list[0]);
	test_set_supported_features(&air, (unsigned32)VENDOR_ID_3GPP, feature_list_id[1], feature_list[1]);

	/*Set Requested-EUTRAN-Authentication-Info */
	SS_WCHECK( set_req_eutran_auth_info(&air, &num_req_vect, &immd_resp_pref,re_sync_inf), "Requested-EUTRAN-Authentication-Info set.\n","Failed to set Requested-EUTRAN-Authentication-Info.\n", NULL);

	/*Set Requested-UTRAN-GERAN-Authentication-Info */
	SS_WCHECK(set_req_utran_geran_auth_info(&air, &num_req_vect, &immd_resp_pref,re_sync_inf), "Requested-UTRAN-Authentication-Info set.\n","Failed to set Requested-UTRAN-Authentication-Info.\n", NULL);

	/*Set Visited-PLMN-Id*/
	SS_CHECK( ss_set_visited_plmn_id((avp_or_msg **)&air, visited_plmn_id, strlen((char *)visited_plmn_id)), "Visited-PLMN-Id set.\n", "failed to set Visited-PLMN-Id.\n");

	/*Send AIR message*/
	SS_CHECK( fd_msg_send( &air, test_ans_cb_air, NULL), "AIR message sent.\n", "Failed to send AIR message.\n");

	return 0;
}

/*Sends Insert-Subscriber-Data-Request message for testing*/
int test_req_idr(char * dest_host){
	
	int len = 0;
	struct msg *idr = NULL;	

	if(!dest_host)
		return EINVAL;

	diameterid *destination_host= (diameterid *) dest_host;
	diameterid *destination_realm = (diameterid *)"localdomain";
	utf8string *user_name = (utf8string *)"244444123456789";	
	unsigned32 feature_list_id[] = {1,2};
	unsigned32 feature_list[] = {3,2};
	unsigned32 idr_flags = 1;
	octetstring *reset_id[] = {(octetstring *)"244444", (octetstring *)"244445", (octetstring *)"244446"}; 

	/*waite until remote peer state is open*/
	len = strlen(dest_host);
	if(ss_peer_state( dest_host, len) != 1)
		fprintf(stdout, "Waiting until connection to remote peer is estabilished ...\n");	
	while(ss_peer_state( dest_host, len) != 1)
		sleep(2);

	/*Create AIR message*/
	SS_CHECK( ss_msg_create_idr(&idr), "Insert-Subscriber-Data-Request message Created.\n", "Error in creating Insert-Subscriber-Data-Request message.\n");

	/*Set Destination-Host AVP*/
	SS_CHECK( ss_set_destination_host((avp_or_msg **) &idr, destination_host, strlen((char *)destination_host)), "Destination-Host AVP set.\n", "failed to set Destination-Host AVP.\n");

	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **) &idr, destination_realm, strlen((char *)destination_realm)), "Destination-Realm AVP set.\n", "failed to set Destination-Realm AVP.\n");

	/* Set User-Name (imsi)*/
	SS_CHECK( ss_set_user_name(&idr, user_name, strlen((char *)user_name)), "User-Name set.\n", "failed to set User-Name.\n");

	/* Set Supported-Features AVP (two AVPs will be set)*/
	test_set_supported_features(&idr, (unsigned32)VENDOR_ID_3GPP, feature_list_id[0], feature_list[0]);
	test_set_supported_features(&idr, (unsigned32)VENDOR_ID_3GPP, feature_list_id[1], feature_list[1]);

	/*Set Subscriber-Data*/
	test_set_subsc_data(&idr, (char *)user_name, /*Set GPRS-DATA*/8, NULL);

	/*Set IDR-Flags*/
	SS_CHECK( ss_set_idr_flags(&idr, idr_flags), "IDR-Flags set.\n", "Failed to set IDR-Flags.\n");
	
	/*Set Reset-Id, (only 3 AVPs set for testing)*/
	SS_CHECK( ss_set_reset_id(&idr, reset_id[0], strlen((char *)reset_id[0])), "Reset-Id set.\n", "Failed to set Reset-Id.\n");
	SS_CHECK( ss_set_reset_id(&idr, reset_id[1], strlen((char *)reset_id[1])), "Reset-Id 2 set.\n", "Failed to set Reset-Id 2.\n");
	SS_CHECK( ss_set_reset_id(&idr, reset_id[2], strlen((char *)reset_id[2])), "Reset-Id 3 set.\n", "Failed to set Reset-Id 3.\n");

	/*Send AIR message*/
	SS_CHECK( fd_msg_send( &idr, test_ans_cb_idr, NULL), "AIR message sent.\n", "Failed to send AIR message.\n");

	return 0;
}

/*Sends Delete-Subscriber-Data-Request message for testing*/
int test_req_dsr(char * dest_host){
	
	int len = 0;
	struct msg *dsr = NULL;	

	if(!dest_host)
		return EINVAL;

	diameterid *destination_host= (diameterid *) dest_host;
	diameterid *destination_realm = (diameterid *)"localdomain";
	utf8string *user_name = (utf8string *)"244444123456789";	
	unsigned32 feature_list_id[] = {1,2};
	unsigned32 feature_list[] = {3,2};
	unsigned32 dsr_flags = 64;
	unsigned32 context_id[] = {1,2,3};
	octetstring trace_ref[] = {0x01,0x11,0x01,0x01,0x01,0x02,'\0'};
	octetstring ts_code[][2] = {{0x01,'\n'},{0x02,'\0'}};
	octetstring ss_code[][2] = {{0x01,'\n'},{0x02,'\0'}};

	/*waite until remote peer state is open*/
	len = strlen(dest_host);
	if(ss_peer_state( dest_host, len) != 1)
		fprintf(stdout, "Waiting until connection to remote peer is estabilished ...\n");	
	while(ss_peer_state( dest_host, len) != 1)
		sleep(2);

	/*Create DSR message*/
	SS_CHECK( ss_msg_create_dsr(&dsr), "Delete-Subscriber-Data-Request message Created.\n", "Error in creating Delete-Subscriber-Data-Request message.\n");

	/*Set Destination-Host AVP*/
	SS_CHECK( ss_set_destination_host((avp_or_msg **) &dsr, destination_host, strlen((char *)destination_host)), "Destination-Host AVP set.\n", "failed to set Destination-Host AVP.\n");

	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **) &dsr, destination_realm, strlen((char *)destination_realm)), "Destination-Realm AVP set.\n", "failed to set Destination-Realm AVP.\n");

	/* Set User-Name (imsi)*/
	SS_CHECK( ss_set_user_name(&dsr, user_name, strlen((char *)user_name)), "User-Name set.\n", "failed to set User-Name.\n");

	/* Set Supported-Features AVP (two AVPs will be set)*/
	test_set_supported_features(&dsr, (unsigned32)VENDOR_ID_3GPP, feature_list_id[0], feature_list[0]);
	test_set_supported_features(&dsr, (unsigned32)VENDOR_ID_3GPP, feature_list_id[1], feature_list[1]);

	/*Set DSR-Flags*/
	SS_CHECK( ss_set_dsr_flags(&dsr, dsr_flags), "DSR-Flags set.\n", "Failed to set DSR-Flags.\n");

	/*Set Context-Identifier (3 AVPs for testing)*/
	SS_CHECK( ss_set_context_identifier((avp_or_msg **)&dsr, context_id[0]), "Context-Identifier set.\n","Failed to set Context-Identifier.\n");
	SS_CHECK( ss_set_context_identifier((avp_or_msg **)&dsr, context_id[1]), "Context-Identifier 2 set.\n","Failed to set Context-Identifier 2.\n");
	SS_CHECK( ss_set_context_identifier((avp_or_msg **)&dsr, context_id[2]), "Context-Identifier 3 set.\n","Failed to set Context-Identifier 3.\n");

	/*Set Trace-Reference*/
	SS_CHECK( ss_set_trace_reference((avp_or_msg **)&dsr, trace_ref, strlen((char *)trace_ref)), "Trace-Reference set.\n", "Failed to set Trace-Reference.\n");

	/*Set TS-Code (2 AVPs set for testing)*/
	SS_CHECK( ss_set_ts_code((avp_or_msg **)&dsr, ts_code[0], strlen((char *)ts_code[0])), "TS-Code set.\n", "Failed to set TS-Code.\n");
	SS_CHECK( ss_set_ts_code((avp_or_msg **)&dsr, ts_code[1], strlen((char *)ts_code[1])), "TS-Code set.\n", "Failed to set TS-Code.\n");

	/*Set SS-Code (2 AVPs set for testing)*/
	SS_CHECK( ss_set_ss_code((avp_or_msg **)&dsr, ss_code[0], strlen((char *)ss_code[0])), "SS-Code set.\n", "Failed to set SS-Code.\n");
	SS_CHECK( ss_set_ss_code((avp_or_msg **)&dsr, ss_code[1], strlen((char *)ss_code[1])), "SS-Code set.\n", "Failed to set SS-Code.\n");
	
	/*Send DSR message */
	SS_CHECK( fd_msg_send( &dsr, test_ans_cb_dsr, NULL), "DSR message sent.\n", "Failed to send DSR message.\n");

	return 0;
}

/*Sends Purge-UE-Request message for testing*/
int test_req_pur(char * dest_host){
	
	int len = 0;
	struct msg *pur = NULL;	

	if(!dest_host)
		return EINVAL;

	diameterid *destination_host= (diameterid *) dest_host;
	diameterid *destination_realm = (diameterid *)"localdomain";
	utf8string *user_name = (utf8string *)"244444123456789";	
	unsigned32 feature_list_id[] = {1,2};
	unsigned32 feature_list[] = {3,2};
	unsigned32 pur_flags = 4;
	

	/*waite until remote peer state is open*/
	len = strlen(dest_host);
	if(ss_peer_state( dest_host, len) != 1)
		fprintf(stdout, "Waiting until connection to remote peer is estabilished ...\n");	
	while(ss_peer_state( dest_host, len) != 1)
		sleep(2);

	/*Create PUR message*/
	SS_CHECK( ss_msg_create_pur(&pur), "Purge-UE-Request message Created.\n", "Error in creating Purge-UE-Request message.\n");

	/*Set Destination-Host AVP*/
	SS_CHECK( ss_set_destination_host((avp_or_msg **) &pur, destination_host, strlen((char *)destination_host)), "Destination-Host AVP set.\n", "failed to set Destination-Host AVP.\n");

	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **) &pur, destination_realm, strlen((char *)destination_realm)), "Destination-Realm AVP set.\n", "failed to set Destination-Realm AVP.\n");

	/* Set User-Name (imsi)*/
	SS_CHECK( ss_set_user_name(&pur, user_name, strlen((char *)user_name)), "User-Name set.\n", "failed to set User-Name.\n");

	/* Set Supported-Features AVP (two AVPs will be set)*/
	test_set_supported_features(&pur, (unsigned32)VENDOR_ID_3GPP, feature_list_id[0], feature_list[0]);
	test_set_supported_features(&pur, (unsigned32)VENDOR_ID_3GPP, feature_list_id[1], feature_list[1]);

	/*Set PUR-Flags*/
	SS_CHECK( ss_set_pur_flags(&pur, pur_flags), "PUR-Flags set.\n", "Failed to set PUR-Flags.\n");

	/*Set EPS-Location-Information*/
	test_set_eps_location_info(&pur);

	/*Send PUR message */
	SS_CHECK( fd_msg_send( &pur, test_ans_cb_pur, NULL), "PUR message sent.\n", "Failed to send PUR message.\n");

	return 0;
}

/*Sends Reset-Request message for testing*/
int test_req_rsr(char * dest_host){
	
	int len = 0;
	struct msg *rsr = NULL;	

	if(!dest_host)
		return EINVAL;

	diameterid *destination_host= (diameterid *) dest_host;
	diameterid *destination_realm = (diameterid *)"localdomain";
	unsigned32 feature_list_id[] = {1,2};
	unsigned32 feature_list[] = {3,2};
	utf8string *user_id[]= {(utf8string *)"24444412", (utf8string *)"24444412"};
	octetstring *reset_id[] = {(octetstring *)"244444", (octetstring *)"244445", (octetstring *)"244446"};
	

	/*waite until remote peer state is open*/
	len = strlen(dest_host);
	if(ss_peer_state( dest_host, len) != 1)
		fprintf(stdout, "Waiting until connection to remote peer is estabilished ...\n");	
	while(ss_peer_state( dest_host, len) != 1)
		sleep(2);

	/*Create RSR message*/
	SS_CHECK( ss_msg_create_rsr(&rsr), "Reset-Request message Created.\n", "Error in creating Reset-Request message.\n");

	/*Set Destination-Host AVP*/
	SS_CHECK( ss_set_destination_host((avp_or_msg **) &rsr, destination_host, strlen((char *)destination_host)), "Destination-Host AVP set.\n", "failed to set Destination-Host AVP.\n");

	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **) &rsr, destination_realm, strlen((char *)destination_realm)), "Destination-Realm AVP set.\n", "failed to set Destination-Realm AVP.\n");

	/* Set Supported-Features AVP (two AVPs will be set)*/
	test_set_supported_features(&rsr, (unsigned32)VENDOR_ID_3GPP, feature_list_id[0], feature_list[0]);
	test_set_supported_features(&rsr, (unsigned32)VENDOR_ID_3GPP, feature_list_id[1], feature_list[1]);

	/*Set User-Id (only 2 AVPs set for training)*/
	SS_CHECK( ss_set_user_id( &rsr, user_id[0], strlen((char *) user_id[0])), "User-Id set.\n", "Failed to set User-Id.\n");
	SS_CHECK( ss_set_user_id( &rsr, user_id[1], strlen((char *) user_id[1])), "User-Id 2 set.\n", "Failed to set User-Id 2.\n");	

	/*Set Reset-Id, (only 3 AVPs set for testing)*/
	SS_CHECK( ss_set_reset_id(&rsr, reset_id[0], strlen((char *)reset_id[0])), "Reset-Id set.\n", "Failed to set Reset-Id.\n");
	SS_CHECK( ss_set_reset_id(&rsr, reset_id[1], strlen((char *)reset_id[1])), "Reset-Id 2 set.\n", "Failed to set Reset-Id 2.\n");
	SS_CHECK( ss_set_reset_id(&rsr, reset_id[2], strlen((char *)reset_id[2])), "Reset-Id 3 set.\n", "Failed to set Reset-Id 3.\n");

	/*Send RSR message */
	SS_CHECK( fd_msg_send( &rsr, test_ans_cb_rsr, NULL), "RSR message sent.\n", "Failed to send RSR message.\n");

	return 0;
}

/*Sends Notify-Request message for testing*/
int test_req_nor(char * dest_host){
	
	struct msg * nor = NULL;
	int len = 0;
	
	if(!dest_host) return 1;

	diameterid * destination_host= (diameterid *) dest_host;
	diameterid * destination_realm = (diameterid *)"localdomain";
	utf8string * user_name = (utf8string *)"244444123456789";	
	unsigned32 feature_list_id = 1;
	unsigned32 feature_list = 2; 		
	utf8string * imei = (utf8string *)"2345";
	utf8string * software_version = (utf8string *)"22";
	octetstring * meid = (octetstring *)"2345";
	unsigned32 context_identifier = 1;
	unsigned32 nor_flags = 8;
	enum ue_srvcc_capability ue_srvcc_capability = UE_SRVCC_SUPPORTED;
	enum homogeneous_support_of_ims_voice_over_ps_sessions homogeneous_support_ims_voice_over_ps_sessions = HOMO_IMS_VOICE_OVER_PS_NOT_SUPPORTED;
	utf8string * service_selection = (utf8string *)"serviceSelection";
	address  home_agent_address_v4 [] = {0xef,0x00,0x00,0x01};
	address  home_agent_address_v6 [] = {0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, 0x01,0x01,0xff,0xff,0x7f, 0x01, 0x01, 0x01, '\0'};
	diameterid * home_agent_host_host = (diameterid *) "pdngateway1";
	diameterid * home_agent_host_realm = (diameterid *) "epc.mnc001.mcc001.3gppnetwork.org ";
	octetstring * visited_network_identifier = (octetstring *)"visited-net-id";	
	enum alert_reason alert_reason = UE_PRESENT;
		
	/*wait until remote peer connetion state is open*/
	len = strlen(dest_host);
	if(ss_peer_state( dest_host, len) != 1)
		fprintf(stdout, "Waiting until connection to remote peer is estabilished ...\n");	
	while(ss_peer_state( dest_host, len) != 1)
		sleep(2);
	
	/*Create Notify-Request message*/
	SS_CHECK( ss_msg_create_nor(&nor), "Notify-Request message Created.\n", "Error in creating Notify-Request message.\n");

	/*Set Destination-Host AVP*/	
	SS_CHECK( ss_set_destination_host( (avp_or_msg **)&nor, destination_host,strlen((char *)destination_host)), "Destination-Host AVP set.\n","Failed to set Destination-Host AVP\n");
	
	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **)&nor, destination_realm,strlen((char *)destination_realm)), "Destination-Realm AVP set.\n","Failed to set Destination-Realm AVP\n");

	/*Set User-Name AVP*/
	SS_CHECK( ss_set_user_name( &nor, user_name, strlen((char *)user_name)), "User-Name AVP set.\n","Failed to set User-Name AVP\n");
	
	/*Set Supported-Features group AVP and its child AVPs*/
	test_set_supported_features(&nor, (unsigned32)VENDOR_ID_3GPP, feature_list_id, feature_list);

	/*Set Terminal-Information group AVP and its child AVPs*/
	set_terminal_info( &nor, imei, software_version, meid, strlen((char *)meid));
	
	/*Set MIP6-Agent-Info*/
	test_set_mip6((avp_or_msg **)&nor, home_agent_address_v4, home_agent_address_v6, home_agent_host_host, home_agent_host_realm);

	/*Set Visited-Network-Identifier*/
	SS_CHECK( ss_set_visited_network_identifier( (avp_or_msg **)&nor, visited_network_identifier, strlen((char *)visited_network_identifier)), "Visited-Network-Identifier set.\n", "Failed to set Visited-Network-Identifier.\n");

	/*Set Context-Identifier*/
	SS_CHECK( ss_set_context_identifier((avp_or_msg **)&nor, context_identifier), "Context-Identifier set.\n", "Failed to set Context-Identifier/\n");

	/*Set Service-Selection*/
	SS_CHECK( ss_set_service_selection( (avp_or_msg **) &nor, service_selection, strlen((char *)service_selection)), "Service-Selection set.\n", "Failed to set Service-Selection.\n");

	/*Set Alert-Reason*/
	SS_CHECK( ss_set_alert_reason(&nor, alert_reason), "Alert-Reason set.\n", "Failed to set Alert-Reason.\n");
	
	/*Set UE-SRVCC-Capability AVP*/
	SS_CHECK( ss_set_ue_srvcc_capability( &nor, ue_srvcc_capability), "UE-SRVCC-Capability AVP set.\n","Failed to set UE-SRVCC-Capability AVP\n");

	/*Set NOR-Flags AVP*/
	SS_CHECK( ss_set_nor_flags( &nor, nor_flags), "NOR-Flags AVP set.\n","Failed to set NOR-Flags AVP\n");
	
	/*Set Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP*/
	SS_CHECK( ss_set_homogeneous_support_of_ims_voice_over_ps_sessions( &nor, (int32_t)homogeneous_support_ims_voice_over_ps_sessions), "Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP set.\n","Failed to set Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP\n");

	/*send request*/
	SS_CHECK( fd_msg_send( &nor, test_ans_cb_nor, NULL), "NOR message sent.\n", "Failed to send NOR message.\n");

	return 0;
}

