
#include "test.h"

#define CHECK_ULR_SKIP_SUBSC_DATA(x) 	 ((1U<<2) & x) 
#define CHECK_SUPPORT_ODB_HPLMN_APN(x)   ((1U<<1) & x)
#define SET_ULA_MME_REG_SMS(x)			  x |= (1U<<1)
#define SET_ULA_SEPARATION_INDICATIN(x)   x |= 1U


#define SET_ORIGIN_AND_EXPER_RESULT(result, msg)																	\
{																													\
	/* Add the Origin-Host and Origin-Realm AVP in the answer*/														\
	CHECK_FCT( fd_msg_add_origin ( *msg, 0 ) );																		\
	/*Set experimental result*/																						\
	SS_CHECK( ss_create_experimental_result(&tmp_gavp), "Experimental-Result AVP created.\n", "Failed to create Experimental-Result AVP.\n");																						\
	/*Vendor-id*/																									\
	SS_CHECK( ss_set_vendor_id( &tmp_gavp,(unsigned32)VENDOR_ID_3GPP), "vendor id set.\n", "Failed to set vendor id.\n");	   																										\
	/*experimental result code*/																					\
  	SS_CHECK(ss_set_experimental_result_code( &tmp_gavp, (unsigned32)result), "experimental result code set.\n", "Failed to set experimental result code.\n");																		\
	SS_CHECK( ss_add_avp(  (avp_or_msg **)msg, tmp_gavp ), "experimental result added.\n", "Failed to add experimental result.\n");																							\
}

/*Insert/Update terminfo(Terminal-Information) table*/
static int get_terminal_info(struct msg * msg, utf8string **imei, utf8string **soft_ver, octetstring **meid){

	struct avp * tmp_gavp;
	size_t len = 0;
	int check = 3;

	if(!msg)
		return 1;
	if((!imei) && (!soft_ver) && (!meid))
		return 1;

	/*check terminal-info avp*/
	SS_WCHECK( ss_get_gavp_terminal_information( msg, &tmp_gavp), "Terminal-Information extracted.\n", "Failed to extract Terminal-Information\n", return 1;);

	/*Get IMIE*/
	if(imei)
		SS_WCHECK( ss_get_imei(tmp_gavp, imei, &len), "IMEI extracted.\n", "Failed to retrieve IMEI.\n", check--);
				
	/*Get Software Version*/
	if(soft_ver)
		SS_WCHECK( ss_get_software_version(tmp_gavp, soft_ver, &len), "Software Version extracted.\n", "Failed to retrieve Software Version.\n", check--);
		
	/*Get 3gpp2-MEID*/
	if(meid)
		SS_WCHECK( ss_get_3gpp2_meid(tmp_gavp, meid, &len), "3GPP2 MEID extracted.\n", "Failed to retrieve Software 3GPP2 MEID.\n", check--);

	/*at least one of the avp is found*/
	if(check != 0)
		return 0;

	return 1;
}

/*Insert/Update database tables*/
static int insert_update_db(MYSQL * conn, char * table_name, char * column_name, char * value, char * imsi){

	char buf[500] = {0};

	if((!conn) || (!table_name) || (!column_name) || (!value) || (!imsi))
		return 1;

	/*Prepare insert/update mysql statement*/
	sprintf(buf, "insert into %s (imsi,%s) values('%s','%s') on duplicate key update %s='%s'", table_name, column_name, imsi, value, column_name, value);
	
	/*insert/update the table*/
	if(mysql_query(conn,buf)){
		fprintf(stderr, "Insert/Update %s table failed: %s\n", table_name, mysql_error(conn));
		return 1;
	}

	return 0;
}

/*Insert/Update terminal information into database*/
static int insert_update_db_terminfo(MYSQL *conn, char * imsi, char *imei, char *soft_ver, char *meid, integer32 ue_srv_capb){
	
	char tmp_str[2] = {0};	

	if((!conn) || (!imsi)){
		printf("ERROR : Terminal information insert/update failed. Given mysql connection is NULL.\n");
		return 1;
	}
	/*Insert/update IMEI into termInfor table*/
	if(imei)
		SS_WCHECK(insert_update_db(conn, "termInfo", "imei", imei, imsi), "IMIE iserted/updated.\n", "Insert/Update IMIE failed.\n", NULL);
	/*Insert/update software version into termInfor table*/
	if(soft_ver)
		SS_WCHECK(insert_update_db(conn, "termInfo", "softVersion", soft_ver, imsi), "software version iserted/updated.\n", "Insert/Update software version failed.\n", NULL);
	/*Insert/update 3GPP2 MEID into termInfor table*/
	if(meid)
		SS_WCHECK(insert_update_db(conn, "termInfo", "meid", meid, imsi), "MEID iserted/updated.\n", "Insert/Update MEID failed.\n", NULL);
	/*Insert/update UE SRVCC capability into termInfor table*/
	if(ue_srv_capb >= 0){
		sprintf( tmp_str, "%.1d", ue_srv_capb);
		SS_WCHECK(insert_update_db(conn, "termInfo", "ueSrvccCapab", tmp_str, imsi), "UE SRVCC capability iserted/updated.\n", "Insert/Update UE SRVCC capability failed.\n", NULL);
	}

	return 0;	
}	

/*Update the mme table with the new mme info*/
static int insert_update_mme(MYSQL *conn, char * imsi, char * origin_hst, char * origin_rlm, char * ueprg, char * mt_sms){

	if((!conn) || (!imsi)){
		printf("ERROR : mme table insert/update failed. 'mysql connection' or/and 'imsi' is NULL.\n");
		return 1;
	}

	/*Insert/update origin host into mme table*/
	if(origin_hst)
		SS_WCHECK( insert_update_db(conn, "mme", "mmeHost", origin_hst, imsi), "origin host inserted/updated into mme table.\n", "insert/update origin host into mme failed.\n", NULL);
	/*Insert/update origin realm into mme table*/
	if(origin_rlm)
		SS_WCHECK( insert_update_db(conn, "mme", "mmeRealm", origin_rlm, imsi), "mme realm inserted/updated into mme talbe.\n", "insert/update origin realm into mme failed.\n", NULL);
	/*Insert/update UE purged into mme table*/
	if(ueprg)
		SS_WCHECK( insert_update_db(conn, "mme", "uePurged", ueprg, imsi), "ue purged inserted/updated into mme table.\n", "isert/update UE purged into mme failed.\n", NULL);
	/*Insert/update MME-Number-for-MT-SMS into mme table*/
	if(mt_sms)
		SS_WCHECK( insert_update_db(conn, "mme", "mmeMtSmsNumb", mt_sms, imsi), "MME-Number-for-MT-SMS iserted/updated into mme table.\n", "isert/update MME-Number-for-MT-SMS into mme failed.\n", NULL);	

	return 0;
}
/*Get MIP-Home-Agent-Address*/
static inline int get_mip_addr(struct avp *gavp, address ** addr_1, address ** addr_2){

	address ** hm_agnt_addr = NULL;
	size_t array_size = 0;
	size_t *len = NULL;

	if(!gavp) return 1;
	
	if((!addr_1) && (!addr_2))	return 1;

	/*Get MIP-Home-Agent-Address*/							
	SS_WCHECK( ss_get_mip_home_agent_address_gavp_array( gavp, &hm_agnt_addr, &len,&array_size), "MIP-Home-Agent-Address array of values retrieved.\n", "Failed to retrieve MIP-Home-Agent-Address values.\n", return 1);

	if(array_size){
		
		if(addr_1){
			*addr_1 = hm_agnt_addr[array_size-1];
			array_size--;
		}
		else if(addr_2 && array_size)
			*addr_2 = hm_agnt_addr[array_size];
		
		free(hm_agnt_addr);
		free(len);

		return 0;
	}	

	return 1;
}

/*Get MIP-Home-Agent-Host child avp values*/
static inline int get_mip_home_agnt_hst(struct avp * gavp, diameterid ** dst_host, diameterid ** dst_realm){

	struct avp *tmp_gavp = NULL;
	size_t len = 0;

	if((!gavp) || (!dst_host) || (!dst_realm))
		return 1;

	/*Get MIP-Home-Agent-Host AVP*/
	SS_WCHECK( ss_get_gavp_mip_home_agent_host(gavp, &tmp_gavp), "MIP-Home-Agent-Host AVP retrieved,\n", "Failed to retrieve MIP-Home-Agent-Host.\n", return 1;);
	
	/*Get destination host value*/
	SS_CHECK(ss_get_destination_host(tmp_gavp, dst_host, &len), "destination host retrieved.\n", "Failed to extract Destination-Host.\n");

	/*Get destination realm value*/
	SS_CHECK(ss_get_destination_realm(tmp_gavp, dst_realm, &len), "destination host retrieved.\n", "Failed to extract Destination-Realm.\n");

	return 0;		
}

/*Get MIP6-Agent-Info child AVP values*/
static inline int get_mip6_values(struct avp *gavp, address ** addr_1, address ** addr_2, diameterid ** dst_host, diameterid ** dst_realm){

	struct avp * tmp_gavp;	
	int check = 1;

	if(!gavp)
		return 1;
	if((!addr_1) && (!addr_2) && (!dst_host) && (!dst_realm))
		return 1;

	/*check for  MIP6-Agent-Info avp*/
	SS_WCHECK( ss_get_gavp_mip6_agent_info(gavp, &tmp_gavp) , "MIP6-Agent-Info retrieved.\n", "Failed to retrieve MIP6-Agent-Info.\n", return 1;);
		
	/*check for the MIP-Home-Agent-Address*/	
	SS_WCHECK( get_mip_addr(tmp_gavp, addr_1, addr_2), "MIP-Home-Agent-Address retrieved.\n", "Failed to retrieve MIP-Home-Agent-Address.\n", check++);						
							
	/*check for  MIP-Home-Agent-Host */
	SS_WCHECK( get_mip_home_agnt_hst(tmp_gavp, dst_host, dst_realm), "MIP-Home-Agent-Host child AVP values retrieved.\n", "Failed to retrieve MIP-Home-Agent-Host child AVP values.\n", check++);	

	/*if both MIP-Home-Agent-Address and MIP-Home-Agent-Host fails to be retrieved*/
	if(check == 3)
		return 1;
	
	return 0;						
}

/*check for Active-Apn AVPs and update database*/
static void check_update_active_apn(struct msg *msg, char * imsi, MYSQL * conn){

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	char buf[110] = {0};
	char buf2[550] = {0};
	unsigned32 context_id;
	address * hm_agnt_addr_1 = (address *)"";
	address * hm_agnt_addr_2 = (address *)"";
	diameterid * dst_hst = (diameterid *)"";
	diameterid * dst_rlm = (diameterid *)"";	
	
	MYSQL_RES *res = NULL;
  	MYSQL_ROW row;
	
	if((!msg) || (!imsi) || (!conn))
		return;

	/*Get Active-Apn AVP from */
	SS_WCHECK( ss_get_gavp_active_apn( msg, &tmp_gavp), "Active-APN AVP retrieved from request.\n", "Failed to retrieve Active-APN AVP.\n", NULL);

	while(tmp_gavp){				
				
		/*Get context-id avp*/
		SS_CHECK( ss_get_context_identifier(tmp_gavp, &context_id), "Context id value retrieved.\n", "Failed to extract context-Id AVP\n.");

		/*mysql statement to fetch apn subscription data with context id and a 'dynamic' PDN-GW-Allocation-Type*/	
		snprintf(buf,110,"select imsi from apnConf where imsi='%.15s' and contextId='%u' and pdnGwAllocType='1'", imsi, context_id);

		/*Query database and store result*/
		SS_CHECK(test_get_qry_res(conn, buf, &res), "apn subscription data retrieved from db.\n", "Failed to store apn subscription data from database.\n");
					
		if((row = mysql_fetch_row(res))!= NULL){

			/*check for  MIP6-Agent-Info avp*/
			if(get_mip6_values(tmp_gavp, &hm_agnt_addr_1, &hm_agnt_addr_2, &dst_hst, &dst_rlm) == 0){
			
				/*mysqpl statement to update apnConf table with new MIP6-Agent-Info*/
				snprintf(buf2,550,"update apnConf set mipHomeAgntAddr0='%.16s', mipHomeAgntAddr1='%.16s', mipDestHost='%s', mipDestRealm='%s' where imsi='%.15s' and contextId='%u'",(char *)hm_agnt_addr_1, (char *)hm_agnt_addr_2, (char *)dst_hst, (char *)dst_rlm, imsi, context_id);
				
				/*Update apnConf table*/
				if (mysql_query(conn, buf2)) 
					fprintf(stderr, "Warning : apnConf table update failed: %s\n", mysql_error(conn));			
			}
		}

		mysql_free_result(res);				
		
		/*Get the next Active-Apn group AVP*/
		SS_WCHECK( ss_get_gavp_next_active_apn(tmp_gavp, &tmp_gavp2), "Next Active-Apn retrieved.\n", "Failed to retrieve Next Active-Apn.\n",NULL);
		tmp_gavp = tmp_gavp2;
	}
}

/*Set Request Authentication info values to their parent AVP*/
static int get_req_auth_info(struct avp *gavp, unsigned32 *num_req_vect, unsigned32 *immd_resp_pref, octetstring **re_sync_inf){
	
	size_t len = 0;

	if(!gavp) return EINVAL;

	if((!num_req_vect) && (!immd_resp_pref) && (!re_sync_inf)) return EINVAL;

	/*Set Number-Of-Requested-Vectors*/
	if(num_req_vect)
		SS_WCHECK( ss_get_number_of_requested_vectors(gavp, num_req_vect), "Number-Of-Requested-Vectors value retrieved.\n", "failed to retrieve Number-Of-Requested-Vectors.\n", NULL);

	/*Set Immediate-Response-Preferred*/
	if(immd_resp_pref)
		SS_WCHECK( ss_get_immediate_response_preferred(gavp, immd_resp_pref), "Immediate-Response-Preferred value retrieved.\n", "failed to retrieve Immediate-Response-Preferred.\n", NULL);

	/*Set Re-synchronization-Info*/
	if(re_sync_inf)
		SS_WCHECK( ss_get_re_synchronization_info(gavp, re_sync_inf, &len), "Re-synchronization-Info value retrieved.\n", "failed to retrieve Re-synchronization-Info.\n", NULL);

	return 0;
	
}

/*Get Requested-EUTRAN-Authentication-Info AVP */
static int get_req_eutran_auth_info(struct msg *msg, unsigned32 *num_req_vect, unsigned32 *immd_resp_pref, octetstring **re_sync_inf){

	struct avp *tmp_gavp = NULL;

	if(!msg) return EINVAL;

	/*Set Requested-EUTRAN-Authentication-Info AVP*/
	SS_WCHECK( ss_get_gavp_requested_eutran_authentication_info(msg, &tmp_gavp), "Requested-EUTRAN-Authentication-Info AVP retrieved.\n", "failed to retrieve Requested-EUTRAN-Authentication-Info AVP.\n", return 1;);

	/*Get Requested-EUTRAN-Authentication-Info AVP child AVP values and add it to Requested-EUTRAN-Authentication-Info AVP*/
	SS_WCHECK( get_req_auth_info(tmp_gavp, num_req_vect, immd_resp_pref, re_sync_inf), "Requested-EUTRAN-Authentication-Info AVP child AVP values retrieved.\n", "failed to retreive Requested-EUTRAN-Authentication-Info AVP child AVP values.\n", return 1;);

	return 0;
}

/*Get Requested-UTRAN-GERAN-Authentication-Info AVP */
static int get_req_utran_geran_auth_info(struct msg *msg, unsigned32 *num_req_vect, unsigned32 *immd_resp_pref, octetstring **re_sync_inf){

	struct avp *tmp_gavp = NULL;

	if(!msg) return EINVAL;

	/*Get Requested-UTRAN-GERAN-Authentication-Info AVP*/
	SS_WCHECK( ss_get_gavp_requested_utran_geran_authentication_info(msg, &tmp_gavp), "Requested-UTRAN-GERAN-Authentication-Info AVP retrieved.\n", "failed to get Requested-UTRAN-GERAN-Authentication-Info AVP.\n", return 1;);

	/*Get Requested-UTRAN-GERAN-Authentication-Info AVP child AVP values and add it to Requested-UTRAN-GERAN-Authentication-Info AVP*/
	SS_WCHECK( get_req_auth_info(tmp_gavp, num_req_vect, immd_resp_pref, re_sync_inf), "Requested-UTRAN-GERAN-Authentication-Info AVP child AVP values retrieved.\n", "failed to retrieve Requested-UTRAN-GERAN-Authentication-Info AVP child AVP values.\n", return 1;);

	return 0;
}

/*Get  UTRAN auth vector from db and set UTRAN-Vector*/
static int get_set_utran_vect(struct avp **gavp, char * imsi, unsigned32 num_req_vect_utran){

	struct avp *tmp_gavp = NULL;
	unsigned32 tmp_u = 0;
	char buf[70] = {0};
	int i = 0;
	MYSQL *conn = NULL;
	MYSQL_RES *res = NULL;
  	MYSQL_ROW row;

	if((!gavp) || (0 == num_req_vect_utran) || (!imsi))
		return EINVAL;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to subscription data*/	
	sprintf(buf,"select * from UTRANVector where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "UTRANVector data retrieved from db.\n", "Failed to retrieve UTRANVector data from database.\n"); 
	
	if((row = mysql_fetch_row(res))!= NULL){
	
		for(i = 0; i < num_req_vect_utran; i++){
		
		/*create UTRAN-Vector AVP*/
		SS_CHECK( ss_create_utran_vector(&tmp_gavp), "UTRAN-Vector created.\n", "Failed to create UTRAN-Vector.\n");

		/*Set Item-Number*/
			if(row[1])
				SS_SET_U32( ss_set_item_number( &tmp_gavp, tmp_u), tmp_u, row[1], "Item-Number set.\n", "failed to set Item-Number.\n");

			/*set RAND*/
			if(row[2])
				SS_CHECK( ss_set_rand( &tmp_gavp, (octetstring *)row[2], strlen(row[2])),"RAND set.\n", "failed to set RAND.\n");

			/*set XRES*/
			if(row[3])
				SS_CHECK( ss_set_xres( &tmp_gavp, (octetstring *)row[3], strlen(row[3])),"XRES set.\n", "failed to set XRES.\n");

			/*set AUTN*/
			if(row[4])
				SS_CHECK( ss_set_autn( &tmp_gavp, (octetstring *)row[4], strlen(row[4])),"AUTN set.\n", "failed to set AUTN.\n");

			/*set Confidentiality-Key*/
			if(row[5])
				SS_CHECK( ss_set_confidentiality_key( &tmp_gavp, (octetstring *)row[5], strlen(row[5])),"Confidentiality-Key set.\n", "failed to set Confidentiality-Key.\n");
	
			/*set Integrity-Key*/
			if(row[6])
				SS_CHECK( ss_set_integrity_key( &tmp_gavp, (octetstring *)row[6], strlen(row[6])),"Integrity-Key set.\n", "failed to set Integrity-Key.\n");	

			/*Add UTRAN-Vector AVP*/
			SS_CHECK( ss_add_avp((avp_or_msg **)gavp, tmp_gavp), "UTRAN-Vector added.\n", "Failed to add UTRAN-Vector.\n");	
		}

		mysql_free_result(res);
	}
	else{

		mysql_close(conn);
		return 1;	
	}
	
	return 0;
}
/*Get  GERAN auth vector from db set GERAN-Vector*/
static int get_set_geran_vect(struct avp **gavp, char * imsi, unsigned32 num_req_vect_geran){

	struct avp *tmp_gavp = NULL;
	unsigned32 tmp_u = 0;
	char buf[70] = {0};
	int i = 0;
	MYSQL *conn = NULL;
	MYSQL_RES *res = NULL;
  	MYSQL_ROW row;

	if((!gavp) || (0 == num_req_vect_geran) || (!imsi))
		return EINVAL;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to subscription data*/	
	sprintf(buf,"select * from GERANVector where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "GERANVector data retrieved from db.\n", "Failed to retrieve GERANVector data from database.\n"); 
	
	if((row = mysql_fetch_row(res))!= NULL){
	
		for(i = 0; i < num_req_vect_geran; i++){
		
			/*GERAN-Vector*/
			SS_CHECK( ss_create_geran_vector(&tmp_gavp), "GERAN-Vector AVP created.\n", "Failed to create GERAN-Vector.\n");

			/*Set Item-Number*/
			if(row[1])
				SS_SET_U32( ss_set_item_number( &tmp_gavp, tmp_u), tmp_u, row[1], "Item-Number set.\n", "failed to set Item-Number.\n");

			/*set RAND*/
			if(row[2])
				SS_CHECK( ss_set_rand( &tmp_gavp, (octetstring *)row[2], strlen(row[2])),"RAND set.\n", "failed to set RAND.\n");

			/*set SRES*/
			if(row[3])
				SS_CHECK( ss_set_sres( &tmp_gavp, (octetstring *)row[3], strlen(row[3])),"SRES set.\n", "failed to set SRES.\n");

			/*set Kc*/
			if(row[4])
				SS_CHECK( ss_set_kc( &tmp_gavp, (octetstring *)row[4], strlen(row[4])),"Kc set.\n", "failed to set Kc.\n");

			/*Add GERAN-Vector */
			SS_CHECK( ss_add_avp((avp_or_msg **)gavp, tmp_gavp), "GERAN-Vector added\n", "Fail to add GERAN-Vector.\n");
		}

		mysql_free_result(res);
	}
	else{

		mysql_close(conn);
		return 1;	
	}
	
	return 0;
}

/*Get  EUTRAN auth vector from db and set E-UTRAN-Vector*/
static int get_set_eutran_vect(struct avp **gavp, char * imsi, unsigned32 num_req_vect_eutran){

	struct avp *tmp_gavp = NULL;
	unsigned32 tmp_u = 0;
	char buf[70] = {0};
	int i = 0;
	MYSQL *conn = NULL;
	MYSQL_RES *res = NULL;
  	MYSQL_ROW row;

	if((!gavp) || (0 == num_req_vect_eutran) || (!imsi))
		return EINVAL;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to subscription data*/	
	sprintf(buf,"select * from EUTRANVector where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "EUTRANVector data retrieved from db.\n", "Failed to retrieve EUTRANVector data from database.\n"); 
	
	if((row = mysql_fetch_row(res))!= NULL){
	
		for(i = 0; i <num_req_vect_eutran; i++){
		
		/*Create E-UTRAN-Vector AVP*/
		SS_CHECK( ss_create_e_utran_vector(&tmp_gavp), "E-UTRAN-Vector created.\n", "Failed to create E-UTRAN-Vector AVP.\n");
		
		/*Set Item-Number*/
			if(row[1])
				SS_SET_U32( ss_set_item_number( &tmp_gavp, tmp_u), tmp_u, row[1], "Item-Number set.\n", "failed to set Item-Number.\n");

			/*set RAND*/
			if(row[2])
				SS_CHECK( ss_set_rand( &tmp_gavp, (octetstring *)row[2], strlen(row[2])),"RAND set.\n", "failed to set RAND.\n");

			/*set XRES*/
			if(row[3])
				SS_CHECK( ss_set_xres( &tmp_gavp, (octetstring *)row[3], strlen(row[3])),"XRES set.\n", "failed to set XRES.\n");

			/*set AUTN*/
			if(row[4])
				SS_CHECK( ss_set_autn( &tmp_gavp, (octetstring *)row[4], strlen(row[4])),"AUTN set.\n", "failed to set AUTN.\n");

			/*set KASME*/
			if(row[5])
				SS_CHECK( ss_set_kasme( &tmp_gavp, (octetstring *)row[5], strlen(row[5])),"KASME set.\n", "failed to set KASME.\n");

			/*Add E-UTRAN-Vector AVP*/
			SS_CHECK( ss_add_avp((avp_or_msg **)gavp, tmp_gavp), "E-UTRAN-Vector added.\n", "Failed to add E-UTRAN-Vector.\n");
		}

		mysql_free_result(res);
	}
	else{

		mysql_close(conn);
		return 1;	
	}
	
	return 0;
}

/*Set Authentication-Info*/
static void set_auth_info(struct msg **msg, char *imsi, unsigned32 num_req_vect_utran, unsigned32 num_req_vect_eutran){

	struct avp *tmp_gavp = NULL;
	
	if((!msg) || (!imsi)) return;	

	/*Create Authentication-Info AVP*/
	SS_CHECK( ss_create_authentication_info(&tmp_gavp), "Authentication-Info AVP created.\n", "failed to create Authentication-Info AVP.\n");

	/*Set UTRAN-GERAN auth-vectors requested*/
	if(0 != num_req_vect_utran){

		/*Set UTRAN auth vector*/
		SS_CHECK( get_set_utran_vect(&tmp_gavp, imsi, num_req_vect_utran), "UTRAN-Vector set.\n", "Failed to set UTRAN-Vector.\n");	

		/*Set  GERAN auth vector */
		SS_CHECK( get_set_geran_vect(&tmp_gavp, imsi, num_req_vect_utran), "GERAN-Vector set.\n", "Failed to set GERAN-Vector.\n");			
	}

	/*Set EUTRAN auth-vectors requested*/
	if(0 != num_req_vect_eutran)
		SS_CHECK( get_set_eutran_vect(&tmp_gavp, imsi, num_req_vect_eutran), "E-UTRAN-Vector set.\n", "Failed to set E-UTRAN-Vector.\n");	

	SS_CHECK( ss_add_avp((avp_or_msg *)msg, tmp_gavp), "Authentication-Info AVP added.\n", "faile to add Authentication-Info AVP.\n");	
	
}

/*Set EPS-User-State*/
static void set_eps_usr_state(struct msg **msg, enum user_state mme_usr_state){
	
	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;

	if(!msg) return;

	/*Create EPS-User-State AVP*/
	SS_CHECK( ss_create_eps_user_state(&tmp_gavp), "EPS-User-State created.\n", "Failed to create EPS-User-State.\n");

	/*Create MME-User-State AVP*/
	SS_CHECK( ss_create_mme_user_state(&tmp_gavp2), "MME-User-State created.\n", "Failed to create MME-User-State.\n");

	/*Set User-State*/
	SS_CHECK( ss_set_user_state(&tmp_gavp2, mme_usr_state), "User-State set.\n", "Failed to set User-State.\n");

	/*Add MME-User-State*/
	SS_CHECK( ss_add_avp((avp_or_msg **)&tmp_gavp, tmp_gavp2), " MME-User-State added.\n", "Failed to add  MME-User-State.\n");

	/*Add EPS-User-State*/
	SS_CHECK( ss_add_avp((avp_or_msg **)msg, tmp_gavp), " EPS-User-State added.\n", "Failed to add  EPS-User-State.\n");
}


/*Set Local-Time-Zone*/
static void set_local_time_zone(struct msg **msg, utf8string * time_zone, enum daylight_saving_time day_sv_tm){

	struct avp *tmp_gavp = NULL;
	
	if((!msg) || (!time_zone)) return;

	/*Create Local-Time-Zone*/ 
	SS_CHECK( ss_create_local_time_zone(&tmp_gavp), "Local-Time-Zone created.\n", "Failed to create Local-Time-Zone.\n");

	/*Set Time-Zone*/
	SS_CHECK( ss_set_time_zone(&tmp_gavp, time_zone, strlen((char *)time_zone)), "Time-Zone set.\n", "Failed to set Time-Zone.\n");

	/*Set Daylight-Saving-Time*/
	SS_CHECK( ss_set_daylight_saving_time(&tmp_gavp, day_sv_tm), "Daylight-Saving-Time set.\n", "Failed to set Daylight-Saving-Time.\n");

	/*Add Local-Time-Zone*/
	SS_CHECK( ss_add_avp((avp_or_msg **) msg, tmp_gavp), "Local-Time-Zone added.\n", "Failed to add Local-Time-Zone.\n");
}

/*Callback function used when Update-Location-Request message is received*/
int test_req_cb_ulr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){
	
	struct msg * req = NULL;	
	struct avp * tmp_gavp = NULL;	
    char buf[110] = {0};
	unsigned32 ulrflg;
	unsigned32 ulaflg = 0;
	char imsi[16] = {0};
	diameterid * origin_host = NULL;
	diameterid * origin_realm = NULL;
	octetstring * mme_nm_mt_sms = NULL;
	utf8string * imei = NULL;
	utf8string * soft_version = NULL;
	octetstring * meid = NULL;
	integer32 ue_srvcc_capability = -1;
	integer32 rat_type = -1;
	unsigned32 *feature_list = NULL;
	octetstring *reset_id[] = {(octetstring *)"244444", (octetstring *)"244445", (octetstring *)"244446"};
	size_t size = 0; /*used to store number of feature list values*/
	unsigned char * tmp_ustr = NULL;
	integer32 tmp_i = 0;
	size_t len = 0;
	
	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if (msg == NULL)
		return EINVAL;	
	
	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : ULR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);	
	
	/* Create answer message header from the request, copy the request before creating answer */
	req = *msg;
	SS_CHECK( ss_msg_create_answer( msg), "Answer message header created from request.\n", "Failed to create answer message header.\n");	

	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(req, &tmp_ustr, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");
	strncpy(imsi,(char *)tmp_ustr,15);

	/*Check user from the database and retrieve Rat Type info*/
	/* Connect to the mysql database*/
	test_connect_db(&conn);
	
	/*Prepare mysql statement to subscription data*/	
	sprintf(buf,"select ratType from subscriptionData where imsi='%.15s'",imsi);

	/*Query database and store result*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "RAT type data retrieved from db.\n", "Failed to retriev RAT type data from database.\n");

	/*fetch row*/
	if((row = mysql_fetch_row(res)) == NULL){
			
		/* User is unkown*/
		fprintf(stderr, COLOR_GREEN"OK : ERROR MESSAGE 'DIAMETER_ERROR_USER_UNKNOWN' to be sent."ANSI_COLOR_RESET"\n");

		/*Set origin host, origin realm and 'DIAMETER_ERROR_USER_UNKNOWN' experimental result code*/
		SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_USER_UNKNOWN, msg);

		mysql_free_result(res);
		mysql_close(conn);

		goto send;
	}

	/*Retrive Rat type value from request*/
	SS_CHECK( ss_get_rat_type_msg(req, &rat_type), "Rat type extracted from request.\n", "Failed to extract Rat type from request.\n");

	/* Compare the subscribed RAT type with the recieved RAT type*/
	if(rat_type != atoi(row[0])){

		
		fprintf(stdout, COLOR_GREEN"OK : ERROR MESSAGE 'DIAMETER_ERROR_RAT_NOT_ALLOWED' to be sent. %d."ANSI_COLOR_RESET"\n", rat_type);

		/*Set origin host, origin realm and 'DIAMETER_ERROR_RAT_NOT_ALLOWED' experimental result code*/
		SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_RAT_NOT_ALLOWED, msg);

		mysql_free_result(res);
		mysql_close(conn);

		goto send;
	}

	/*free data from mysql query*/
	mysql_free_result(res);
		
	/*Retrieve Feature-List AVP value (only 1 avp is expected for testing) from request*/
	test_get_supported_features(req, NULL, &feature_list, &size);

	/* Check if mme supports ODB_HPLMN_APN*/
	if((feature_list) && (!CHECK_SUPPORT_ODB_HPLMN_APN(*feature_list))){

		fprintf(stdout,COLOR_GREEN"OK : ERROR MESSAGE 'DIAMETER_ERROR_ROAMING_NOT_ALLOWED' with error diagnostic value 'ODB_HPLMN_APN' to be sent."ANSI_COLOR_RESET"\n");

		/*Set origin host, origin realm and 'DIAMETER_ERROR_ROAMING_NOT_ALLOWED' experimental result code*/
		SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_ROAMING_NOT_ALLOWED, msg);
		
		/*Set Error-Diagnostic AVP with 'ODB_HPLMN_APN' value*/
		SS_CHECK( ss_set_error_diagnostic(msg, (int32_t)ODB_HPLMN_APN), "Error diagnostic value set.\n", "Failed to set error diagnostic.\n");

		/*close mysql connection*/
		mysql_close(conn);
		
		goto send;
	}

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*check MME-Number-for-MT-SMS and Set ULA-Flags' MME Registered for SMS bit*/
	if(0 == (ss_get_mme_number_for_mt_sms_msg(req, &mme_nm_mt_sms, &len))){
		
		SET_ULA_MME_REG_SMS(ulaflg); 
		printf("OK : ULA-Flags' MME Registered for SMS bit set.\n");
	}

	/*Retrieve origin realm from request*/
	SS_CHECK( ss_get_origin_realm_msg(req, &origin_realm, &len), "Origin realm retrieved from request.\n", "Failed to retrieve origin realm from request.\n");
		
	/*Prepare mysql statement to fetch mme data*/	
	sprintf(buf,"select * from mme where imsi='%.15s'",imsi);

	/*Query database and store result*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "mme data retrieved from db.\n", "Failed to store mme data from database.\n");
	
	if((row = mysql_fetch_row(res))!= NULL){

		/*if new mme is different from old mme*/
		if(strcmp(row[1],(char *)origin_host) != 0){
						
			/* Send cancel location to old mme*/
			printf("Sending CLR to old mme ...\n");
			test_send_clr((diameterid *)row[1], (diameterid *)row[2], (utf8string *)imsi, MME_UPDATE_PROCEDUR, /*CLR msg sent on S6a*/1); 
			
			/*Update the mme table with the new mme info*/
			SS_WCHECK( insert_update_mme(conn, imsi, (char *)origin_host, (char *)origin_realm, "", (char *)mme_nm_mt_sms), "insert/update mme table.\n", "insert/update mme table failed.\n", NULL);
		}
		else	
			SS_WCHECK( insert_update_mme(conn, imsi, NULL, NULL, "", (char *)mme_nm_mt_sms), "insert/update mme table.\n", "insert/update mme table failed.\n", NULL);
	}				
	else
		SS_WCHECK( insert_update_mme(conn, imsi, (char *)origin_host, (char *)origin_realm, "", (char *)mme_nm_mt_sms), "Insert mme table.\n", "Insert mme table failed.\n", NULL);
	
	/*free data from mysql query*/			
	mysql_free_result(res);
	
	
	/*Retrieve terminal information from request*/
	get_terminal_info(req, &imei, &soft_version, &meid);

	/*Retrieve ue-srvcc-capability from request*/
	SS_WCHECK( ss_get_ue_srvcc_capability_msg(req, &ue_srvcc_capability), "UE-SRVCC-Capability value retrieved from request.\n", "Failed to retrieve UE-SRVCC-Capability value.\n", NULL);

	/*Insert/Update terminfo(Terminal-Information) table*/
	SS_WCHECK( insert_update_db_terminfo( conn, imsi, (char *)imei, (char *)soft_version, (char *)meid, ue_srvcc_capability), "terminfo inserted/updated.\n", "Insert/Update terminfo failed.\n", NULL);

	/*Get Visited-PLMN-Id AVP*/
	SS_CHECK( ss_get_visited_plmn_id_msg( req, &tmp_ustr, &len), "Visited-PLMN-Id AVP Retrieved.\n","Failed to Retrieve Visited-PLMN-Id AVP\n");

	/*Get SGSN-Number AVP*/
	SS_WCHECK( ss_get_sgsn_number_msg( req, &tmp_ustr, &len), "SGSN-Number AVP Retrieved.\n","Failed to Retrieve SGSN-Number AVP\n", NULL);
	
	/*Get Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP*/
	SS_CHECK( ss_get_homogeneous_support_of_ims_voice_over_ps_sessions_msg( req, &tmp_i), "Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP Retrieved.\n","Failed to Retrieve Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP\n");

	/*Get GMLC-Address AVP*/
	SS_CHECK( ss_get_gmlc_address_msg( req, &tmp_ustr, &len), "GMLC-Address AVP Retrieved.\n","Failed to Retrieve GMLC-Address AVP\n");

	/*check for Active-Apn AVPs and update database*/
	check_update_active_apn( req, imsi, conn);

	/*close mysql connection*/
	mysql_close(conn);

	/*Set supported feature*/
	test_set_supported_features(msg, (unsigned32) VENDOR_ID_3GPP, (unsigned32) 1, (unsigned32) 2);
	test_set_supported_features(msg, (unsigned32) VENDOR_ID_3GPP, (unsigned32) 2, (unsigned32) 5);

	/* Set Separation-Indication bit and Set ULA-Flags*/
	SET_ULA_SEPARATION_INDICATIN(ulaflg); 
	SS_CHECK( ss_set_ula_flags( msg, ulaflg), "ULA-Flags Set.\n", "Failed to set ULA-Flags.\n");

	/****** Put subscription info into Answer message(ULA) ***************************************/			
	/* extract ulr flag from request*/
	SS_CHECK( ss_get_ulr_flags_msg( req, &ulrflg), "ULR-Flags extracted from request.\n", "Failed to retrieve ulr flags value.\n");

	/*If skip subscriber data is not set in ulr flag then create and set Subscription-Data AVP*/
	if(!CHECK_ULR_SKIP_SUBSC_DATA(ulrflg)){
		fprintf(stdout, "ok : Setting subscription data ...\n");
		test_set_subsc_data(msg, imsi, ulrflg, req);
	}			

	/*Set Reset-Id, (only 3 AVPs set for testing)*/
	SS_CHECK( ss_set_reset_id(msg, reset_id[0], strlen((char *)reset_id[0])), "Reset-Id set.\n", "Failed to set Reset-Id.\n");
	SS_CHECK( ss_set_reset_id(msg, reset_id[1], strlen((char *)reset_id[1])), "Reset-Id 2 set.\n", "Failed to set Reset-Id 2.\n");
	SS_CHECK( ss_set_reset_id(msg, reset_id[2], strlen((char *)reset_id[2])), "Reset-Id 3 set.\n", "Failed to set Reset-Id 3.\n");

	/* Send the answer */
send:
	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "ULA Response sent\n", "Failed to set ULA Response");*/
	fprintf(stdout,"OK : Answer message passed to routing module.\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;

/*error:
	return EINVAL;*/
}

/*Callback function used when Update-Location-Request message is received*/
int test_req_cb_clr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	unsigned char *tmp_ustr = NULL;
	unsigned char *origin_host = NULL;
	char imsi[15] = {0};
	unsigned32 *feature_list_id = NULL;
	unsigned32 *feature_list = NULL;
	size_t size = 0;
	size_t len = 0;

	if(NULL == msg)
		return EINVAL;

	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : CLR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);	
	
	

	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(*msg, &tmp_ustr, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");
	strncpy(imsi,(char *)tmp_ustr,15);

	/*Extract Supported-Features child AVPs' values*/
	test_get_supported_features(*msg, &feature_list_id, &feature_list, &size);
	
	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "CLA Answer message header created from request.\n", "Failed to create CLA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);
	
	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "CLA Response sent\n", "Failed to set CLA Response");*/
	fprintf(stdout,"OK : CLA Answer message passed to routing module.\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}

/*Callback function used when Authentication-Information-Request message is received*/
int test_req_cb_air(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	unsigned char *tmp_ustr = NULL;
	unsigned char *origin_host = NULL;
	char imsi[15] = {0};
	unsigned32 *feature_list_id = NULL;
	unsigned32 *feature_list = NULL;
	size_t size = 0;
	unsigned32 num_req_vect_eutran = 0;
	unsigned32 num_req_vect_utran = 0;
	unsigned32 immd_resp_pref = 0;
	octetstring * re_sync_inf = NULL;
	octetstring * visited_plmn_id = NULL;
	size_t len = 0;
	

	if(NULL == msg)
		return EINVAL;

	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : AIR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);	
	
	

	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(*msg, &tmp_ustr, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");
	strncpy(imsi,(char *)tmp_ustr,15);

	/*Extract Supported-Features child AVPs' values*/
	test_get_supported_features(*msg, &feature_list_id, &feature_list, &size);
	
	/*Get Requested-EUTRAN-Authentication-Info */
	SS_WCHECK( get_req_eutran_auth_info(*msg, &num_req_vect_eutran, &immd_resp_pref,&re_sync_inf), "Requested-EUTRAN-Authentication-Info retrieved.\n","Failed to retrieve Requested-EUTRAN-Authentication-Info.\n", NULL);
	
	/*Get Requested-UTRAN-GERAN-Authentication-Info */
	SS_WCHECK(get_req_utran_geran_auth_info(*msg, &num_req_vect_utran, &immd_resp_pref,&re_sync_inf), "Requested-UTRAN-Authentication-Info retrieved.\n","Failed to retrieve Requested-UTRAN-Authentication-Info.\n", NULL);

	/*Get Visited-PLMN-Id*/
	SS_CHECK( ss_get_visited_plmn_id_msg(*msg, &visited_plmn_id, &len), "Visited-PLMN-Id retrieved.\n", "failed to retrieve Visited-PLMN-Id.\n");	

	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "AIA Answer message header created from request.\n", "Failed to create AIA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);

	/*Set Authentication-Info*/
	set_auth_info(msg, imsi, num_req_vect_utran, num_req_vect_eutran);

	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "CLA Response sent\n", "Failed to set CLA Response");*/
	fprintf(stdout,"OK : AIA Answer message passed to routing module.\n\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}

/*Callback function used when Insert-Subscriber-Data-Request message is received*/
int test_req_cb_idr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	unsigned char *tmp_ustr = NULL;
	unsigned char *origin_host = NULL;
	char imsi[15] = {0};
	unsigned32 *feature_list_id = NULL;
	unsigned32 *feature_list = NULL;
	size_t size = 0;
	unsigned32 idr_flgs = 0;
	octetstring **reset_ids = NULL;
	enum ims_voice_over_ps_sessions_supported ims_vop_supp = SUPPORTED;	
	ss_time last_ue_act_time[] = {0x01,0xff,0xff,0xff,'\0'}; 
	enum rat_type rat_type = UTRAN;
	unsigned32 ida_flgs = 1;
	enum user_state mme_usr_state = DETACHED;
	utf8string * time_zone = (utf8string *)"+8";
	enum daylight_saving_time day_sv_tm = NO_ADJUSTMENT;
	size_t len = 0;
	size_t *len_arr = NULL;

	if(NULL == msg) return EINVAL;

	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : IDR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);		

	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(*msg, &tmp_ustr, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");
	strncpy(imsi,(char *)tmp_ustr,15);

	/*Extract Supported-Features child AVPs' values*/
	test_get_supported_features(*msg, &feature_list_id, &feature_list, &size);
	
	/*Extract subscription data*/
	test_check_subsc_data(*msg);

	/*Extract IDR-Flags*/
	SS_WCHECK( ss_get_idr_flags_msg(*msg, &idr_flgs), "IDR-Flags retrieved.\n", "Failed to retrieve IDR-Flags.\n", NULL);
	
	/*Extract Reset-Id*/
	SS_WCHECK( ss_get_reset_id_array(*msg, &reset_ids, &len_arr, &size), "Reset-Id retrieved.\n", "Failed to retrieve Reset-Id.\n", NULL);
	if(reset_ids) free(reset_ids);
	if(len_arr) free(len_arr);

	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "AIA Answer message header created from request.\n", "Failed to create AIA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);

	/*Set IMS-Voice-Over-PS-Sessions-Supported*/
	SS_CHECK( ss_set_ims_voice_over_ps_sessions_supported( msg, ims_vop_supp), "IMS-Voice-Over-PS-Sessions-Supported set.\n", "Failed to set IMS-Voice-Over-PS-Sessions-Supported.\n");

	/*Set Last-UE-Activity-Time*/
	SS_CHECK( ss_set_last_ue_activity_time( msg, last_ue_act_time, strlen((char *)last_ue_act_time)), "Last-UE-Activity-Time set.\n", "Failed to set Last-UE-Activity-Time.\n");

	/*Set RAT-Type*/
	SS_CHECK( ss_set_rat_type(msg, rat_type), "RAT-Type set.\n", "Failed to set RAT-Type.\n");

	/*Set IDA-Flags*/
	SS_CHECK( ss_set_ida_flags( msg, ida_flgs), "IDA-Flags set.\n", "Failed to set IDA-Flags.\n");

	/*Set EPS-User-State*/
	set_eps_usr_state(msg, mme_usr_state);

	/*Set EPS-Location-Information*/
	test_set_eps_location_info(msg);

	/*Set Local-Time-Zone*/
	set_local_time_zone(msg, time_zone, day_sv_tm);

	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "IDA Response sent\n", "Failed to set IDA Response");*/
	fprintf(stdout,"OK : IDA Answer message passed to routing module.\n\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}

/*Callback function used when Delete-Subscriber-Data-Request message is received*/
int test_req_cb_dsr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	unsigned char *tmp_ustr = NULL;
	unsigned char *origin_host = NULL;
	char imsi[15] = {0};
	unsigned32 *feature_list_id = NULL;
	unsigned32 *feature_list = NULL;
	size_t size = 0;
	unsigned32 dsr_flgs = 0;
	unsigned32 *context_ids = NULL;
	octetstring *trace_ref = NULL;
	octetstring **ts_codes = NULL;
	octetstring **ss_codes = NULL;
	unsigned32 dsa_flgs = 1;
	size_t len = 0;
	size_t *len_arr = NULL;

	if(NULL == msg) return EINVAL;

	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : DSR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);		

	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(*msg, &tmp_ustr, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");
	strncpy(imsi,(char *)tmp_ustr,15);

	/*Extract Supported-Features child AVPs' values*/
	test_get_supported_features(*msg, &feature_list_id, &feature_list, &size);

	/*Extract DSR-Flags*/
	SS_CHECK( ss_get_dsr_flags_msg(*msg, &dsr_flgs), "DSR-Flags retrieved.\n", "Failed to retrieve DSR-Flags.\n");
	
	/*Extract Context-Identifier*/
	SS_WCHECK( ss_get_context_identifier_array(*msg, &context_ids, &size), "Context-Identifier retrieved.\n", "Failed to retrieve Context-Identifier.\n", NULL);
	if(context_ids) free(context_ids);

	/*Extract Trace-Reference*/
	SS_WCHECK( ss_get_trace_reference_msg( *msg, &trace_ref, &len), "Trace-Reference set.\n", "Failed to set Trace-Reference.\n", NULL);

	/*Extract TS-Code*/
	SS_WCHECK( ss_get_ts_code_array( *msg, &ts_codes, &len_arr, &size), "TS-Code set.\n","Failed to set TS-Code.\n", NULL);
	if(ts_codes) free(ts_codes);
	if(len_arr) free(len_arr);

	/*Extract SS-Code*/
	SS_WCHECK( ss_get_ts_code_array( *msg, &ss_codes, &len_arr, &size), "SS-Code set.\n","Failed to set SS-Code.\n", NULL);
	if(ss_codes) free(ss_codes);
	if(len_arr) free(len_arr);	

	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "DSA Answer message header created from request.\n", "Failed to create DSA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);

	/*Set DSA-flags*/
	SS_CHECK( ss_set_dsa_flags( msg, dsa_flgs), "DSA-flags set.\n", "Failed to set DSA-flags.\n");

	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "IDA Response sent\n", "Failed to set IDA Response");*/
	fprintf(stdout,"OK : DSA Answer message passed to routing module.\n\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}

/*Callback function used when Purge-UE-Request message is received*/
int test_req_cb_pur(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	unsigned char *tmp_ustr = NULL;
	unsigned char *origin_host = NULL;
	char imsi[15] = {0};
	unsigned32 *feature_list_id = NULL;
	unsigned32 *feature_list = NULL;
	unsigned32 pur_flgs = 0;
	unsigned32 pua_flgs = 1;
	size_t size = 0;
	size_t len = 0;

	if(NULL == msg) return EINVAL;

	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : PUR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);		

	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(*msg, &tmp_ustr, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");
	strncpy(imsi,(char *)tmp_ustr,15);

	/*Extract Supported-Features child AVPs' values*/
	test_get_supported_features(*msg, &feature_list_id, &feature_list, &size);

	/*Extract PUR-Flags*/
	SS_CHECK( ss_get_pur_flags_msg(*msg, &pur_flgs), "PUR-Flags retrieved.\n", "Failed to retrieve PUR-Flags.\n");

	/*check EPS-Location-Information*/
	test_check_eps_location_info(*msg);
	
	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "PUA Answer message header created from request.\n", "Failed to create PUA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);

	/*Set PUA-flags*/
	SS_CHECK( ss_set_pua_flags( msg, pua_flgs), "PUA-flags set.\n", "Failed to set PUA-flags.\n");

	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "PUA Response sent\n", "Failed to set PUA Response");*/
	fprintf(stdout,"OK : PUA Answer message passed to routing module.\n\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}

/*Callback function used when Reset-Request message is received*/
int test_req_cb_rsr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	unsigned char *origin_host = NULL;
	unsigned32 *feature_list_id = NULL;
	unsigned32 *feature_list = NULL;
	utf8string **user_id = NULL;
	octetstring **reset_id = NULL;
	size_t size = 0;
	size_t len = 0;
	size_t *len_arr = NULL;

	if(NULL == msg) return EINVAL;

	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : PUR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);		

	/*Extract Supported-Features child AVPs' values*/
	test_get_supported_features(*msg, &feature_list_id, &feature_list, &size);

	/*Extract User-Id*/
	SS_WCHECK( ss_get_user_id_array(*msg, &user_id, &len_arr, &len), "User-Id values retrieved.\n", "Failed to retrieve User-Id values.\n", NULL);
	if(user_id) free(user_id);
	if(len_arr) free(len_arr);

	/*Extract Reset-Id*/
	SS_WCHECK( ss_get_reset_id_array(*msg, &reset_id, &len_arr, &len), "Reset-Id values retrieved.\n", "Failed to retrieve Reset-Id values.\n", NULL);
	if(user_id) free(reset_id);
	if(len_arr) free(len_arr);

	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "RSA Answer message header created from request.\n", "Failed to create RSA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, 1, 2);

	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "RSA Response sent\n", "Failed to set RSA Response");*/
	fprintf(stdout,"OK : RSA Answer message passed to routing module.\n\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}

/*Callback function used when Notify-Request message is received*/
int test_req_cb_nor(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){
	
    char imsi[16] = {0};
	diameterid * origin_host = NULL;
	utf8string * imei = NULL;
	utf8string * soft_version = NULL;
	octetstring * meid = NULL;
	unsigned32 *feature_list = NULL;
	unsigned32 *feature_list_id = NULL;
	octetstring * visited_net_id = NULL;
	unsigned32 context_id = 0;
	utf8string * service_selection = NULL;
	enum alert_reason alert_reason;
	enum ue_srvcc_capability ue_srvcc_capability;
	unsigned32 nor_flgs = 0;
	enum homogeneous_support_of_ims_voice_over_ps_sessions hm_supp_ims_vop_sessions;
	unsigned char *tmp_ustr = NULL;
	size_t size = 0; /*used to store number of feature list values*/
	size_t len = 0;

	if (msg == NULL) return EINVAL;	
	
	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : NOR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);	
	
	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(*msg, &tmp_ustr, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");
	strncpy(imsi,(char *)tmp_ustr,15);

	/*Retrieve Feature-List AVP value (only 1 avp is expected for testing) from request*/
	test_get_supported_features(*msg, &feature_list_id, &feature_list, &size);

	/*Retrieve terminal information from request*/
	get_terminal_info(*msg, &imei, &soft_version, &meid);

	/*Get MIP6-Agent-Info*/
	test_check_mip6(*msg);

	/*Get Visited-Network-Identifier*/
	SS_CHECK( ss_get_visited_network_identifier_msg( *msg, &visited_net_id, &len), "Visited-Network-Identifier retrieved.\n", "Failed to retrieve Visited-Network-Identifier.\n");

	/*Get Context-Identifier*/
	SS_CHECK( ss_get_context_identifier_msg(*msg, &context_id), "Context-Identifier retrieved.\n", "Failed to retrieve Context-Identifier/\n");

	/*Get Service-Selection*/
	SS_CHECK( ss_get_service_selection_msg( *msg, &service_selection, &len), "Service-Selection retrieved.\n", "Failed to retrieve Service-Selection.\n");

	/*Get Alert-Reason*/
	SS_CHECK( ss_get_alert_reason_msg(*msg, (int32_t *)&alert_reason), "Alert-Reason retrieved.\n", "Failed to retrieve Alert-Reason.\n");

	/*Retrieve ue-srvcc-capability from request*/
	SS_WCHECK( ss_get_ue_srvcc_capability_msg(*msg, (int32_t *)&ue_srvcc_capability), "UE-SRVCC-Capability value retrieved from request.\n", "Failed to retrieve UE-SRVCC-Capability value.\n", NULL);
	
	/*Set NOR-Flags AVP*/
	SS_CHECK( ss_get_nor_flags_msg( *msg, &nor_flgs), "NOR-Flags AVP retrieved.\n","Failed to retrieve NOR-Flags AVP\n");
	
	/*Get Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP*/
	SS_CHECK( ss_get_homogeneous_support_of_ims_voice_over_ps_sessions_msg( *msg, (int32_t *)&hm_supp_ims_vop_sessions), "Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP Retrieved.\n","Failed to Retrieve Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP\n");

	/* Create answer message header from the request, copy the request before creating answer */
	SS_CHECK( ss_msg_create_answer( msg), "Answer message header created from request.\n", "Failed to create answer message header.\n");

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set supported feature*/
	test_set_supported_features(msg, (unsigned32) VENDOR_ID_3GPP, (unsigned32) 1, (unsigned32) 2);
	test_set_supported_features(msg, (unsigned32) VENDOR_ID_3GPP, (unsigned32) 2, (unsigned32) 5);

	/* Send the answer */
	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "NOA Response sent\n", "Failed to set NOA Response");*/
	fprintf(stdout,"OK : Answer message passed to routing module.\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}
