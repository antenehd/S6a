

#include "ssix_interface.h"
#include "test.h"


/*Set Supported-Features group AVP*/
void test_set_supported_features(struct msg **msg, unsigned32 vnd_id, unsigned32 ftr_id, unsigned32 ftr_lst){

	struct avp * tmp_gavp;

	if(!msg)	
		return;

	/*Create Supported-Features group AVP*/
	SS_CHECK( ss_create_supported_features(&tmp_gavp), "Supported-Features group AVP created.\n", "Failed to create Supported-Features group AVP\n");

	/*Set Vendor-Id*/
	SS_CHECK( ss_set_vendor_id( &tmp_gavp, (uint32_t)vnd_id), "Vendor-Id AVP is set.\n", "Failed to set Vendor-Id AVP.\n");

	/*Set Feature-List-ID AVP*/
	SS_CHECK( ss_set_feature_list_id( &tmp_gavp, ftr_id), "Feature-List-ID AVP set.\n","Failed to set Feature-List-ID AVP\n");

	/*Set Feature-List AVP*/
	SS_CHECK( ss_set_feature_list( &tmp_gavp, ftr_lst), "Feature-List AVP set.\n","Failed to set Feature-List AVP\n");	

	/*Add Supported-Features group AVP in to message*/ 	
	SS_CHECK( ss_add_avp( (avp_or_msg **)msg, tmp_gavp), "Supported-Features AVP added in to message\n", "Failed to add Supported-Features group AVP in to message\n");

}

/*Get Supported-Feature child AVPs' values*/
void test_get_supported_features(struct msg *msg, unsigned32 **ftr_lst_id, unsigned32 **ftr_lst, size_t *size){

	struct avp *tmp_gavp = NULL;
	unsigned32 *lst_id = NULL;
	unsigned32 *lst = NULL;	
	size_t sz = 0;	

	if((!msg) || (!size)) return;		

	if((!ftr_lst_id) && (!ftr_lst)) return;		

	/*Extract Supported-Feature AVP*/
	SS_WCHECK( ss_get_gavp_supported_features(msg, &tmp_gavp), "Supported-Features AVP extracted.\n", "failed to extract Supported-Features AVP.\n", NULL);

	while(tmp_gavp){

		if(ftr_lst_id){
			
			if(NULL == (lst_id = realloc(lst_id, sizeof(unsigned32))))	return;

			SS_CHECK( ss_get_feature_list_id( tmp_gavp, &lst_id[sz]), "Feature-List-Id extracted.\n", "Failed to extract Feature-List-Id.\n");			
		}

		if(ftr_lst){
			
			if(NULL == (lst = realloc(lst, sizeof(unsigned32))))	return;

			SS_CHECK( ss_get_feature_list( tmp_gavp, &lst[sz]), "Feature-List extracted.\n", "Failed to extract Feature-List.\n");			
		}
		
		sz ++;

		/*Extract Supported-Feature AVP*/
		SS_WCHECK( ss_get_gavp_next_supported_features(tmp_gavp, &tmp_gavp), "More Supported-Features AVP extracted.\n", "failed to extract more Supported-Features AVP.\n", NULL);		
	}	

	if(ftr_lst_id) *ftr_lst_id = lst_id;
	
	if(ftr_lst_id) *ftr_lst = lst;

	*size = sz;
}

/* Sends cancel location request*/
int test_util_send_clr(diameterid *dst_host, diameterid *dst_rlm, utf8string * imsi, enum cancellation_type cncl_typ, unsigned32 clr_flg){
	
	struct msg * clr;

	if((!dst_host) || (!dst_rlm) || (!imsi))
		return 1;

	/*Create Cancel-Location-Request message*/
	SS_CHECK( ss_msg_create_clr(&clr), "Cancel-Location-Request message Created.\n", "Error in creating Cancel-Location-Request message.\n");

	/*Set Destination-Host AVP*/	
	SS_CHECK( ss_set_destination_host( (avp_or_msg **)&clr, dst_host), "Destination-Host AVP set.\n","Failed to set Destination-Host AVP\n");
	
	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **)&clr, dst_rlm), "Destination-Realm AVP set.\n","Failed to set Destination-Realm AVP\n");

	/*Set User-Name AVP*/
	SS_CHECK( ss_set_user_name( &clr, imsi), "User-Name AVP set.\n","Failed to set User-Name AVP\n");
	
	/*Set Supported-Features group AVP (Only 2 AVPs set for testing)*/
	test_set_supported_features(&clr, (int)VENDOR_ID_3GPP, 1, 1);
	test_set_supported_features(&clr, (int)VENDOR_ID_3GPP, 2, 33);

	/*Set Cancellation-Type AVP*/
	SS_CHECK( ss_set_cancellation_type(&clr, cncl_typ), "Cancellation-Type AVP set.\n", "Failed to set Cancellation-Type AVP.\n");
	
	/*Set CLR-Flags AVP*/
	SS_CHECK( ss_set_clr_flags(&clr, clr_flg), "CLR-Flags AVP set\n", "Failed to set CLR-Flags AVP.\n");

	/*Send Cancel-Location-Request message sent*/
	SS_CHECK( fd_msg_send( &clr, test_ans_cb_clr, NULL), "CLR request message sent.\n","Failed to send CLR request message.\n");
	
	return 0;
}

/*** Set MIP6-Agent-Info AVP ***/
void test_set_mip6(struct avp **gavp, address * ipv4, address * ipv6, diameterid * host, diameterid * realm){
	
	struct avp * tmp_gavp;
	struct avp * tmp_gavp2;
					
	if(!gavp)
		return;
	if( (!ipv4) && (!ipv6) && (!host) && (!realm))
		return;

	/*Create MIP6-Agent-Info group AVP*/
	SS_CHECK( ss_create_mip6_agent_info(&tmp_gavp), "MIP6-Agent-Info Created.\n", "Failed to create MIP6-Agent-Info.\n");

	/* Set MIP-Home-Agent-Address avp (IPV4 and IPV6)*/
	if(ipv4)
		SS_CHECK( ss_set_mip_home_agent_address( &tmp_gavp, ipv4), "MIP-Home-Agent-Address IPV4 set.\n", "Failed to set MIP-Home-Agent-Address IPV4.\n");		
	if(ipv6)
		SS_CHECK( ss_set_mip_home_agent_address( &tmp_gavp, ipv6), "MIP-Home-Agent-Address IPV6 set.\n", "Failed to set MIP-Home-Agent-Address IPV6.\n");	

	/* Create MIP-Home-Agent-Host AVP*/
	SS_CHECK( ss_create_mip_home_agent_host( &tmp_gavp2), "MIP-Home-Agent-Host created.\n", "Failed to create MIP-Home-Agent-Host AVP.\n");
	
	/*Set Destination-Host avp*/
	if(host)
		SS_CHECK( ss_set_destination_host( (avp_or_msg **)&tmp_gavp2, host), "Destination-Host set into MIP-Home-Agent-Host.\n", "Failed to set Destination-Host into MIP-Home-Agent-Host.\n");

	/* Set Destination-Realm avp*/
	if(realm)
		SS_CHECK( ss_set_destination_realm( (avp_or_msg **)&tmp_gavp2, host), "Destination-Realm set into MIP-Home-Agent-Host.\n", "Failed to set Destination-Realm into MIP-Home-Agent-Host.\n");
	
	/*Add MIP-Home-Agent-Host AVP into MIP6-Agent-Info group AVP*/
	if((host) && (realm))
		SS_CHECK( ss_add_avp( (avp_or_msg **)&tmp_gavp, tmp_gavp2 ), "MIP-Home-Agent-Host added.\n", "Failed to add MIP-Home-Agent-Host.\n");
			
	/*Add MIP6-Agent-Info group AVP into the group AVP provided in parameter 'gavp'*/			
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "MIP6-Agent-Info added.\n", "Failed to add MIP6-Agent-Info.\n");
}



