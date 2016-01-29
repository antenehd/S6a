
#include "test.h"

#define CHECK_ULR_SKIP_SUBSC_DATA(x) 	 ((1U<<2) & x) 
#define CHECK_SUPPORT_ODB_HPLMN_APN(x)   ((1U<<1) & x)
#define SET_ULA_MME_REG_SMS(x)			  x |= (1U<<1)
#define SET_ULA_SEPARATION_INDICATIN(x)   x |= 1U


#define SET_ORIGIN_AND_EXPER_RESULT(result, msg)																	\
{																													\
	/* Add the Origin-Host and Origin-Realm AVP in the answer*/														\
	CHECK_FCT( fd_msg_add_origin( *msg, 0 ) );																		\
	/*Set experimental result*/																						\
	SS_CHECK( ss_create_experimental_result(&tmp_gavp), "Experimental-Result AVP created.\n", "Failed to create Experimental-Result AVP.\n");																						\
	/*Vendor-id*/																									\
	SS_CHECK( ss_set_vendor_id( &tmp_gavp,(unsigned32)VENDOR_ID_3GPP), "vendor id set.\n", "Failed to set vendor id.\n");	   																										\
	/*experimental result code*/																					\
  	SS_CHECK(ss_set_experimental_result_code( &tmp_gavp, (unsigned32)result), "experimental result code set.\n", "Failed to set experimental result code.\n");																		\
	SS_CHECK( ss_add_avp(  (avp_or_msg **)msg, tmp_gavp ), "experimental result added.\n", "Failed to add experimental result.\n");																							\
}

/*converts unsigned char string to a string containing it's hexadecimal representation*/
/*buffer '*hex' should be at least 2*'ustr_size'+1 long, 'ustr_size' is size of 'ustr' in bytes*/
static void to_hex_str(unsigned char *ustr, char hex[], size_t ustr_size){
	
	int i;

	if((!ustr) || (!hex) || (0 == ustr_size)) return;

	for(i=0; i < ustr_size; i++)
		sprintf((hex + (2*i)), "%02x", ustr[i]);
	
	hex[2*ustr_size] = '\0';
}

/*Insert/Update terminfo(Terminal-Information) table*/
static int get_terminal_info(struct msg * msg, utf8string **imei, size_t *imei_len, utf8string **soft_ver, size_t *soft_len, octetstring **meid, size_t *meid_len){

	struct avp * tmp_gavp;
	size_t len = 0;
	int check = 3;

	if(!msg) return 1;

	if((!imei) && (!soft_ver) && (!meid)) return 1;

	/*check terminal-info avp*/
	SS_WCHECK( ss_get_gavp_terminal_information( msg, &tmp_gavp), "Terminal-Information extracted.\n", "Failed to extract Terminal-Information\n", return 1;);

	/*Get IMIE*/
	if(imei)
		SS_WCHECK( ss_get_imei(tmp_gavp, imei, &len), "IMEI extracted.\n", "Failed to retrieve IMEI.\n", check--);
	if(imei_len)
		*imei_len = len;
				
	/*Get Software Version*/
	if(soft_ver)
		SS_WCHECK( ss_get_software_version(tmp_gavp, soft_ver, &len), "Software Version extracted.\n", "Failed to retrieve Software Version.\n", check--);
	if(soft_len)
		*soft_len = len;
		
	/*Get 3gpp2-MEID*/
	if(meid)
		SS_WCHECK( ss_get_3gpp2_meid(tmp_gavp, meid, &len), "3GPP2 MEID extracted.\n", "Failed to retrieve Software 3GPP2 MEID.\n", check--);
	if(meid_len)
		*meid_len = len;

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

/*check for Active-Apn AVPs and update database*/
static void update_active_apn(struct msg *msg, char * imsi, MYSQL * conn){

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	char buf[110] = {0};
	char buf2[550] = {0};
	unsigned32 context_id;
	address * hm_agnt_addr_v4 = (address *)"";
	address * hm_agnt_addr_v6 = (address *)"";
	diameterid * dst_hst = (diameterid *)"";
	diameterid * dst_rlm = (diameterid *)"";	

	MYSQL_RES *res = NULL;
  	MYSQL_ROW row;
	
	if((!msg) || (!imsi) || (!conn)) return;

	/*Get Active-Apn AVP */
	SS_WCHECK( ss_get_gavp_active_apn( msg, &tmp_gavp), "Active-APN AVP retrieved from request.\n", "Failed to retrieve Active-APN AVP.\n", return);

	while(tmp_gavp){				
				
		/*Get context-id avp*/
		SS_CHECK( ss_get_context_identifier(tmp_gavp, &context_id), "Context id value retrieved.\n", "Failed to extract context-Id AVP\n.");
			
		/*mysql statement to fetch apn subscription data with context id and a 'dynamic' PDN-GW-Allocation-Type*/	
		snprintf(buf,110,"select imsi from apnConf where imsi='%.15s' and contextId='%u' and pdnGwAllocType='1'", imsi, context_id);

		/*Query database and store result*/
		SS_CHECK(test_get_qry_res(conn, buf, &res), "apn subscription data retrieved from db.\n", "Failed to store apn subscription data from database.\n");
					
		if((row = mysql_fetch_row(res))!= NULL){

			/*check for  MIP6-Agent-Info avp*/
			if(test_get_mip6_values(tmp_gavp, &hm_agnt_addr_v4, &hm_agnt_addr_v6, &dst_hst, &dst_rlm) == 0){
			
				char res4[13] = {0};
				char res6[37] = {0};

				/*convert received ipv4 address into hex string*/
				to_hex_str(hm_agnt_addr_v4, res4, 6);

				/*convert received ipv4 address into hex string*/
				to_hex_str(hm_agnt_addr_v6, res6, 18);

				/*mysqpl statement to update apnConf table with new MIP6-Agent-Info*/
				snprintf(buf2,550,"update apnConf set mipHomeAgntAddr0=x'%.12s', mipHomeAgntAddr1=x'%.36s', mipDestHost='%s', mipDestRealm='%s' where imsi='%.15s' and contextId='%u'",res4, res6, (char *)dst_hst, (char *)dst_rlm, imsi, context_id);
				
				/*Update apnConf table*/
				if (mysql_query(conn, buf2)) 
					fprintf(stderr, "Warning : apnConf table update failed: %s\n", mysql_error(conn));	
				else
					fprintf(stdout, COLOR_GREEN"OK : "COLOR_GREEN"apnConf table updated.\n");			
			}
		}

		mysql_free_result(res);		

		/*Get the next Active-Apn group AVP*/
		SS_WCHECK( ss_get_gavp_next_active_apn(tmp_gavp, &tmp_gavp2), "Next Active-Apn retrieved.\n", "Failed to retrieve Next Active-Apn.\n",NULL);
		tmp_gavp = tmp_gavp2;
	}
}

/*Compare for Active-Apn AVPs values*/
static void check_active_apn(struct msg *msg){

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	unsigned32 context_id;
	unsigned char *tmp_str = NULL;
	size_t len = 0;
	
	if(!msg) return;

	/*Get Active-Apn AVP from */
	SS_WCHECK( ss_get_gavp_active_apn( msg, &tmp_gavp), "Active-APN AVP retrieved from request.\n", "Failed to retrieve Active-APN AVP.\n", NULL);

	while(tmp_gavp){				
				
		/*Get context-id avp*/
		SS_CHECK( ss_get_context_identifier(tmp_gavp, &context_id), "Context id value retrieved.\n", "Failed to extract context-Id AVP\n.");
		/*compare context-id value*/
		test_comp_uint(context_id, gb_context_identifier[0], "Context-Id");

		/*Check Service-Selection values*/
		SS_WCHECK( ss_get_service_selection(tmp_gavp, &tmp_str, &len), "Service-Selection value retrieved.\n", "Failed to retrieve Service-Selection.\n", NULL);
		/*compare Service-Selection values*/
		if(tmp_str) test_comp_str(tmp_str, gb_service_selection, len, strlen((char*)gb_service_selection), "Service-Selection");		

		/*check for  MIP6-Agent-Info avp*/
		test_check_mip6_values((avp_or_msg *)tmp_gavp);
	
		/*Check Visited-Network-Identifier value*/
		tmp_str = NULL;
		SS_WCHECK( ss_get_visited_network_identifier(tmp_gavp, &tmp_str, &len), "Visited-Network-Identifier value retrieved.\n", "Failed to retrieve Visited-Network-Identifier.\n", NULL);
		/*Compare Visited-Network-Identifier values*/
		if(tmp_str) test_comp_str( tmp_str, gb_visited_network_identifier, len, strlen((char*)gb_visited_network_identifier), "Visited-Network-Identifier");

		/*check Specific-APN-Info*/
		test_check_spec_apn_info( tmp_gavp);		

		/*Get the next Active-Apn group AVP*/
		SS_WCHECK( ss_get_gavp_next_active_apn(tmp_gavp, &tmp_gavp2), "Next Active-Apn retrieved.\n", "Failed to retrieve Next Active-Apn.\n",NULL);
		tmp_gavp = tmp_gavp2;
	}
}


/*Set Request Authentication info values to their parent AVP*/
static int get_req_auth_info(struct avp *gavp, unsigned32 *num_req_vect, unsigned32 *immd_resp_pref, octetstring **re_sync_inf, size_t *len){
	
	size_t tmp_len = 0;

	if(!gavp) return EINVAL;

	if((!num_req_vect) && (!immd_resp_pref) && (!re_sync_inf)) return EINVAL;

	/*Set Number-Of-Requested-Vectors*/
	if(num_req_vect)
		SS_WCHECK( ss_get_number_of_requested_vectors(gavp, num_req_vect), "Number-Of-Requested-Vectors value retrieved.\n", "failed to retrieve Number-Of-Requested-Vectors.\n", NULL);

	/*Set Immediate-Response-Preferred*/
	if(immd_resp_pref)
		SS_WCHECK( ss_get_immediate_response_preferred(gavp, immd_resp_pref), "Immediate-Response-Preferred value retrieved.\n", "failed to retrieve Immediate-Response-Preferred.\n", NULL);

	/*Set Re-synchronization-Info*/
	if(re_sync_inf && len){

		SS_WCHECK( ss_get_re_synchronization_info(gavp, re_sync_inf, &tmp_len), "Re-synchronization-Info value retrieved.\n", "failed to retrieve Re-synchronization-Info.\n", NULL);
		
		*len = tmp_len;
	}

	return 0;
	
}

/*Get Requested-EUTRAN-Authentication-Info AVP */
static int get_req_eutran_auth_info(struct msg *msg, unsigned32 *num_req_vect, unsigned32 *immd_resp_pref, octetstring **re_sync_inf, size_t *len){

	struct avp *tmp_gavp = NULL;

	if(!msg) return EINVAL;

	/*Set Requested-EUTRAN-Authentication-Info AVP*/
	SS_WCHECK( ss_get_gavp_requested_eutran_authentication_info(msg, &tmp_gavp), "Requested-EUTRAN-Authentication-Info AVP retrieved.\n", "failed to retrieve Requested-EUTRAN-Authentication-Info AVP.\n", return 1;);

	/*Get Requested-EUTRAN-Authentication-Info AVP child AVP values and add it to Requested-EUTRAN-Authentication-Info AVP*/
	SS_WCHECK( get_req_auth_info(tmp_gavp, num_req_vect, immd_resp_pref, re_sync_inf, len), "Requested-EUTRAN-Authentication-Info AVP child AVP values retrieved.\n", "failed to retreive Requested-EUTRAN-Authentication-Info AVP child AVP values.\n", return 1;);

	return 0;
}

/*Get Requested-UTRAN-GERAN-Authentication-Info AVP */
static int get_req_utran_geran_auth_info(struct msg *msg, unsigned32 *num_req_vect, unsigned32 *immd_resp_pref, octetstring **re_sync_inf, size_t *len){

	struct avp *tmp_gavp = NULL;

	if(!msg) return EINVAL;

	/*Get Requested-UTRAN-GERAN-Authentication-Info AVP*/
	SS_WCHECK( ss_get_gavp_requested_utran_geran_authentication_info(msg, &tmp_gavp), "Requested-UTRAN-GERAN-Authentication-Info AVP retrieved.\n", "failed to get Requested-UTRAN-GERAN-Authentication-Info AVP.\n", return 1;);

	/*Get Requested-UTRAN-GERAN-Authentication-Info AVP child AVP values and add it to Requested-UTRAN-GERAN-Authentication-Info AVP*/
	SS_WCHECK( get_req_auth_info(tmp_gavp, num_req_vect, immd_resp_pref, re_sync_inf, len), "Requested-UTRAN-GERAN-Authentication-Info AVP child AVP values retrieved.\n", "failed to retrieve Requested-UTRAN-GERAN-Authentication-Info AVP child AVP values.\n", return 1;);

	return 0;
}

/*Get Requested Authentication Info AVP */
static void check_req_auth_info(unsigned32 *num_req_vect, unsigned32 *immd_resp_pref, octetstring *re_sync_inf, size_t len){

	if((!num_req_vect) && (!immd_resp_pref) && (!re_sync_inf)) return;

	/*compare Number-Of-Requested-Vectors value*/
	if(num_req_vect)
		test_comp_uint( *num_req_vect, gb_number_of_requested_vectors, "Number-Of-Requested-Vectors");

	/*compare Immediate-Response-Preferred value*/
	if(immd_resp_pref)
		test_comp_uint( *immd_resp_pref, gb_immediate_response_preferred, "Immediate-Response-Preferred");

	/*compare Re-synchronization-Info value*/
	if(re_sync_inf)
		test_comp_str( re_sync_inf, gb_re_synchronization_info, len, strlen((char*)gb_re_synchronization_info), "Re-synchronization-Info");	
}

/*Get  UTRAN auth vector from db and set UTRAN-Vector*/
static int get_set_utran_vect(struct avp **gavp, char * imsi, unsigned32 num_req_vect_utran){

	struct avp *tmp_gavp = NULL;
	unsigned32 tmp_u = 0;
	char buf[70] = {0};
	int i = 0;
	unsigned long *len = NULL;
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

		/*Get length of each element in array 'row'*/
		len = mysql_fetch_lengths(res);
	
		for(i = 0; i < num_req_vect_utran; i++){
		
			/*create UTRAN-Vector AVP*/
			SS_CHECK( ss_create_utran_vector(&tmp_gavp), "UTRAN-Vector created.\n", "Failed to create UTRAN-Vector.\n");

			/*Set Item-Number*/
			if(row[1])
				SS_SET_U32( ss_set_item_number( &tmp_gavp, tmp_u), tmp_u, row[1], "Item-Number set.\n", "failed to set Item-Number.\n");

			/*set RAND*/
			if(row[2])
				SS_CHECK( ss_set_rand( &tmp_gavp, (octetstring *)row[2], len[2]),"RAND set.\n", "failed to set RAND.\n");

			/*set XRES*/
			if(row[3])
				SS_CHECK( ss_set_xres( &tmp_gavp, (octetstring *)row[3], len[3]),"XRES set.\n", "failed to set XRES.\n");

			/*set AUTN*/
			if(row[4])
				SS_CHECK( ss_set_autn( &tmp_gavp, (octetstring *)row[4], len[4]),"AUTN set.\n", "failed to set AUTN.\n");

			/*set Confidentiality-Key*/
			if(row[5])
				SS_CHECK( ss_set_confidentiality_key( &tmp_gavp, (octetstring *)row[5], len[5]),"Confidentiality-Key set.\n", "failed to set Confidentiality-Key.\n");
	
			/*set Integrity-Key*/
			if(row[6])
				SS_CHECK( ss_set_integrity_key( &tmp_gavp, (octetstring *)row[6], len[6]),"Integrity-Key set.\n", "failed to set Integrity-Key.\n");	

			/*Add UTRAN-Vector AVP*/
			SS_CHECK( ss_add_avp((avp_or_msg **)gavp, tmp_gavp), "UTRAN-Vector added.\n", "Failed to add UTRAN-Vector.\n");	
		}

		mysql_free_result(res);
		mysql_close(conn);
		mysql_thread_end();
	}
	else{

		mysql_close(conn);
		mysql_thread_end();
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
	unsigned long *len = NULL;
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
	
		/*Get length of each element in array 'row'*/
		len = mysql_fetch_lengths(res);

		for(i = 0; i < num_req_vect_geran; i++){
		
			/*GERAN-Vector*/
			SS_CHECK( ss_create_geran_vector(&tmp_gavp), "GERAN-Vector AVP created.\n", "Failed to create GERAN-Vector.\n");

			/*Set Item-Number*/
			if(row[1])
				SS_SET_U32( ss_set_item_number( &tmp_gavp, tmp_u), tmp_u, row[1], "Item-Number set.\n", "failed to set Item-Number.\n");

			/*set RAND*/
			if(row[2])
				SS_CHECK( ss_set_rand( &tmp_gavp, (octetstring *)row[2], len[2]),"RAND set.\n", "failed to set RAND.\n");

			/*set SRES*/
			if(row[3])
				SS_CHECK( ss_set_sres( &tmp_gavp, (octetstring *)row[3], len[3]),"SRES set.\n", "failed to set SRES.\n");

			/*set Kc*/
			if(row[4])
				SS_CHECK( ss_set_kc( &tmp_gavp, (octetstring *)row[4], len[4]),"Kc set.\n", "failed to set Kc.\n");

			/*Add GERAN-Vector */
			SS_CHECK( ss_add_avp((avp_or_msg **)gavp, tmp_gavp), "GERAN-Vector added\n", "Fail to add GERAN-Vector.\n");
		}

		mysql_free_result(res);
		mysql_close(conn);
		mysql_thread_end();
	}
	else{

		mysql_close(conn);
		mysql_thread_end();
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
	unsigned long *len = NULL;
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
	
		/*Get length of each element in array 'row'*/
		len = mysql_fetch_lengths(res);
	
		for(i = 0; i < num_req_vect_eutran; i++){
		
			/*Create E-UTRAN-Vector AVP*/
			SS_CHECK( ss_create_e_utran_vector(&tmp_gavp), "E-UTRAN-Vector created.\n", "Failed to create E-UTRAN-Vector AVP.\n");
		
			/*Set Item-Number*/
			if(row[1])
				SS_SET_U32( ss_set_item_number( &tmp_gavp, tmp_u), tmp_u, row[1], "Item-Number set.\n", "failed to set Item-Number.\n");

			/*set RAND*/
			if(row[2])
				SS_CHECK( ss_set_rand( &tmp_gavp, (octetstring *)row[2], len[2]),"RAND set.\n", "failed to set RAND.\n");

			/*set XRES*/
			if(row[3])
				SS_CHECK( ss_set_xres( &tmp_gavp, (octetstring *)row[3], len[3]),"XRES set.\n", "failed to set XRES.\n");

			/*set AUTN*/
			if(row[4])
				SS_CHECK( ss_set_autn( &tmp_gavp, (octetstring *)row[4], len[4]),"AUTN set.\n", "failed to set AUTN.\n");

			/*set KASME*/
			if(row[5])
				SS_CHECK( ss_set_kasme( &tmp_gavp, (octetstring *)row[5], len[5]),"KASME set.\n", "failed to set KASME.\n");

			/*Add E-UTRAN-Vector AVP*/
			SS_CHECK( ss_add_avp((avp_or_msg **)gavp, tmp_gavp), "E-UTRAN-Vector added.\n", "Failed to add E-UTRAN-Vector.\n");
		}

		mysql_free_result(res);
		mysql_close(conn);
		mysql_thread_end();
	}
	else{

		fprintf(stdout, "INFO : No Auth-info for this subscriber.\n");
		mysql_close(conn);
		mysql_thread_end();
		return 1;	
	}
	
	return 0;
}

/*Set Authentication-Info*/
static void set_auth_info(struct msg **msg, char *imsi, unsigned32 num_req_vect_utran_geran, unsigned32 num_req_vect_eutran){

	struct avp *tmp_gavp = NULL;
	
	if((!msg) || (!imsi)) return;	

	/*Create Authentication-Info AVP*/
	SS_CHECK( ss_create_authentication_info(&tmp_gavp), "Authentication-Info AVP created.\n", "failed to create Authentication-Info AVP.\n");

	/*Set UTRAN-GERAN auth-vectors requested*/
	if(0 != num_req_vect_utran_geran){

		/*Set UTRAN auth vector*/
		SS_WCHECK( get_set_utran_vect(&tmp_gavp, imsi, num_req_vect_utran_geran), "UTRAN-Vector set.\n", "Failed to set UTRAN-Vector.\n", NULL);	

		/*Set  GERAN auth vector */
		SS_WCHECK( get_set_geran_vect(&tmp_gavp, imsi, num_req_vect_utran_geran), "GERAN-Vector set.\n", "Failed to set GERAN-Vector.\n", NULL);			
	}

	/*Set EUTRAN auth-vectors requested*/
	if(0 != num_req_vect_eutran)
		SS_WCHECK( get_set_eutran_vect(&tmp_gavp, imsi, num_req_vect_eutran), "E-UTRAN-Vector set.\n", "Failed to set E-UTRAN-Vector.\n", NULL);	

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

/*Check Terminal-Information group AVP child AVPs' values*/
void check_terminal_info(struct msg *msg){
	
	utf8string *imei = NULL;
	utf8string *soft_version = NULL;
	octetstring *meid = NULL;
	size_t imei_len = 0;
	size_t soft_len = 0;
	size_t meid_len = 0;

	get_terminal_info(msg, &imei, &imei_len, &soft_version, &soft_len, &meid, &meid_len);

	/*Check IMEI value*/
	test_comp_str( imei, gb_imei, imei_len, strlen((char*)gb_imei), "IMEI");

	/*Check Software-Version value*/
	test_comp_str( soft_version, gb_software_version, soft_len, strlen((char*)gb_software_version), "Software-Version");

	/*Check MEID value*/
	test_comp_str( meid, gb_meid, meid_len, strlen((char*)gb_meid), "MEID");
}

/*check Equivalent-PLMN-List child AVPs values*/
static void check_eqv_plmn_lst(struct msg *msg){

	struct avp *tmp_gavp = NULL;
	unsigned char **visited_plmn_id = NULL;
	size_t *len_arr = NULL;
	size_t array_size = 0;

	if(!msg) return;

	/*Get Equivalent-PLMN-List group AVP*/
	SS_WCHECK( ss_get_gavp_equivalent_plmn_list(msg, &tmp_gavp), "Equivalent-PLMN-List group AVP Retrieved.\n", "Failed to retrieve Equivalent-PLMN-List AVP\n", return);

	/*Get array of Visited-Plmn-Id values*/
	SS_CHECK(ss_get_visited_plmn_id_gavp_array(tmp_gavp, &visited_plmn_id, &len_arr, &array_size), "Visited-Plmn-Id retrieved from Equivalent-PLMN-List.\n", "Failed to retrieve Visited-Plmn-Id retrieved from Equivalent-PLMN-List.\n");

	while(array_size){

		/*compare Visited-Plmn-Id value*/
		test_comp_str( visited_plmn_id[array_size-1], gb_visited_plmn_id[array_size-1], len_arr[array_size-1], strlen((char*)gb_visited_plmn_id[array_size-1]), "Visited-Plmn-Id");

		array_size --;
	}
	
	/*free memory*/
	if(visited_plmn_id) free(visited_plmn_id);
	if(len_arr) free(len_arr);
}

/*Compare values received with values sent*/
static void check_ulr_val(struct msg *req){

	unsigned char *tmp_str = NULL;
	uint32_t tmp_u = 0;
	int32_t tmp_i = 0;
	size_t len = 0;

	if(!req) return;

	fprintf(stdout, COLOR_YELLOW"\nSTART : COMPARING VALUES RECEIVED IN ULR MESSAGE..."COLOR_YELLOW"\n");

	/*check User-Name*/
	SS_CHECK( ss_get_user_name_msg(req, &tmp_str, &len), "User-Name extracted from request.\n", "Failed to extract User-Name from request.\n");
	test_comp_str(tmp_str, gb_user_name, len, strlen((char*)gb_user_name), "User-Name");

	/*Check Supported-Features group AVP child AVPs' values*/
	test_check_support_feature( req);

	/*Check Terminal-Information group AVP child AVPs' values*/
	check_terminal_info(req);

	/*Check RAT-Type AVP*/
	SS_CHECK( ss_get_rat_type_msg( req, &tmp_i), "RAT-Type AVP extracted.\n","Failed to extracte RAT-Type AVP\n");
	test_comp_uint((uint32_t) tmp_i, (uint32_t) gb_rat_type, "RAT-Type");

	/*Check ULR-Flags AVP*/
	SS_CHECK( ss_get_ulr_flags_msg( req, &tmp_u), "ULR-Flags AVP extracted.\n","Failed to extracte ULR-Flags AVP\n");
	test_comp_uint(tmp_u, gb_ulr_flags, "ULR-Flags");

	/*Check UE-SRVCC-Capability AVP*/
	SS_WCHECK( ss_get_ue_srvcc_capability_msg( req, &tmp_i), "UE-SRVCC-Capability AVP extracted.\n","Failed to extracte UE-SRVCC-Capability AVP\n", NULL);
	test_comp_uint((uint32_t) tmp_i, (uint32_t) gb_ue_srvcc_capability, "UE-SRVCC-Capability");

	/*Check Visited-PLMN-Id AVP*/
	SS_CHECK( ss_get_visited_plmn_id_msg( req, &tmp_str, &len), "Visited-PLMN-Id AVP extracted.\n","Failed to extracte Visited-PLMN-Id AVP\n");
	test_comp_str(tmp_str, (unsigned char *)gb_visited_plmn_id[0], len, strlen((char*)gb_visited_plmn_id[0]),"Visited-PLMN-Id");

	/*Get SGSN-Number AVP*/
	SS_WCHECK( ss_get_sgsn_number_msg( req, &tmp_str, &len), "SGSN-Number AVP Retrieved.\n","Failed to Retrieve SGSN-Number AVP\n", NULL);
	test_comp_str(tmp_str, gb_sgsn_number, len, strlen((char*)gb_sgsn_number),"SGSN-Number");
	
	/*Get Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP*/
	SS_WCHECK( ss_get_homogeneous_support_of_ims_voice_over_ps_sessions_msg( req, &tmp_i), "Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP Retrieved.\n","Failed to Retrieve Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP\n", NULL);
	test_comp_uint((uint32_t) tmp_i, (uint32_t) gb_homogeneous_support_ims_voice_over_ps_sessions, "Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions");

	/*Get GMLC-Address AVP*/
	SS_WCHECK( ss_get_gmlc_address_msg( req, &tmp_str, &len), "GMLC-Address AVP Retrieved.\n","Failed to Retrieve GMLC-Address AVP\n", NULL);
	test_comp_str(tmp_str, gb_gmlc_address, len, strlen((char*)gb_gmlc_address), "GMLC-Address");

	/*check for Active-Apn AVPs and update database*/
	check_active_apn( req);

	/*check Equivalent-PLMN-List group AVP and its child AVPs*/
	check_eqv_plmn_lst(req);
	
	/*check MME-Number-for-MT-SMS AVP*/
	SS_WCHECK( ss_get_mme_number_for_mt_sms_msg( req, &tmp_str, &len), "MME-Number-for-MT-SMS AVP Retrieved.\n","Failed to Retrieve MME-Number-for-MT-SMS AVP.\n", NULL);
	/*compare MME-Number-for-MT-SMS values*/
	test_comp_str( tmp_str, gb_mme_number_for_mt_sms, len, strlen((char*)gb_mme_number_for_mt_sms),"MME-Number-for-MT-SMS");

	/*check SMS-Register-Request AVP*/
	SS_WCHECK( ss_get_sms_register_request_msg( req, &tmp_i), "SMS-Register-Request AVP Retrieved.\n","Failed to Retrieve SMS-Register-Request AVP.\n", NULL);
	/*compare SMS-Register-Request values*/
	test_comp_uint( (uint32_t)tmp_i, (uint32_t)gb_sms_register_request,"SMS-Register-Request");

	/*check Coupled-Node-Diameter-ID AVP*/
	SS_WCHECK( ss_get_coupled_node_diameter_id_msg( req, &tmp_str, &len), "Coupled-Node-Diameter-ID AVP Retrieved.\n","Failed to Retrieve Coupled-Node-Diameter-ID AVP.\n", NULL);
	/*compare Coupled-Node-Diameter-ID values*/
	test_comp_str( tmp_str, gb_coupled_node_diameter_id, len, strlen((char*)gb_coupled_node_diameter_id), "Coupled-Node-Diameter-ID");

	fprintf(stdout, COLOR_YELLOW"FINISHED : COMPARING VALUES RECEIVED IN ULR MESSAGE DONE."COLOR_YELLOW"\n\n");
}

/*Callback function used when Update-Location-Request message is received*/
int test_req_cb_ulr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){
	
	struct msg * req = NULL;	
	struct avp * tmp_gavp = NULL;	
    char buf[110] = {0};
	unsigned32 ulrflg;
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
	size_t size = 0; /*used to store number of feature list values*/
	unsigned char * tmp_ustr = NULL;
	size_t len = 0;
	
	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if (msg == NULL) return EINVAL;	
	
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
		mysql_thread_end();

		goto send;
	}

	/*Retrive Rat type value from request*/
	SS_CHECK( ss_get_rat_type_msg(req, &rat_type), "Rat type extracted from request.\n", "Failed to extract Rat type from request.\n");

	/* Compare the subscribed RAT type in database with the recieved RAT type*/
	if(rat_type != atoi(row[0])){
		
		fprintf(stdout, COLOR_GREEN"OK : ERROR MESSAGE 'DIAMETER_ERROR_RAT_NOT_ALLOWED' to be sent. %d."ANSI_COLOR_RESET"\n", rat_type);

		/*Set origin host, origin realm and 'DIAMETER_ERROR_RAT_NOT_ALLOWED' experimental result code*/
		SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_RAT_NOT_ALLOWED, msg);

		mysql_free_result(res);
		mysql_close(conn);
		mysql_thread_end();

		goto send;
	}

	/*free data from mysql query*/
	mysql_free_result(res);
		
	/*Retrieve Feature-List AVP value (only 1 avp is expected for testing) from request*/
	test_get_supported_features(req, NULL, &feature_list, &size);

	/* Check if mme supports ODB_HPLMN_APN*/
	if(NULL != feature_list){
		if(!CHECK_SUPPORT_ODB_HPLMN_APN(*feature_list)){

			fprintf(stdout,COLOR_GREEN"OK : ERROR MESSAGE 'DIAMETER_ERROR_ROAMING_NOT_ALLOWED' with error diagnostic value 'ODB_HPLMN_APN' to be sent."ANSI_COLOR_RESET"\n");

			/*Set origin host, origin realm and 'DIAMETER_ERROR_ROAMING_NOT_ALLOWED' experimental result code*/
			SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_ROAMING_NOT_ALLOWED, msg);
		
			/*Set Error-Diagnostic AVP with 'ODB_HPLMN_APN' value*/
			SS_CHECK( ss_set_error_diagnostic(msg, (int32_t)ODB_HPLMN_APN), "Error diagnostic value set.\n", "Failed to set error diagnostic.\n");

			/*close mysql connection*/
			mysql_close(conn);
			mysql_thread_end();

			free(feature_list);	

			/*Send answer message*/
			goto send;
		}

		free(feature_list);
	}


	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*check MME-Number-for-MT-SMS and Set ULA-Flags' MME Registered for SMS bit*/
	if(0 == (ss_get_mme_number_for_mt_sms_msg(req, &mme_nm_mt_sms, &len))){
		
		SET_ULA_MME_REG_SMS(gb_ula_flags); 
		printf("OK : ULA-Flags' MME Registered for SMS bit set.\n");
	}

	/*Retrieve origin realm from request*/
	SS_CHECK( ss_get_origin_realm_msg(req, &origin_realm, &len), "Origin realm retrieved from request.\n", "Failed to retrieve origin realm from request.\n");
		
	/*Prepare mysql statement to fetch mme data*/	
	sprintf(buf,"select * from mme where imsi='%.15s'",imsi);

	/*Query MME data from database and store result*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "mme data retrieved from db.\n", "Failed to store mme data from database.\n");
	
	if((row = mysql_fetch_row(res))!= NULL){

		/*if new mme is different from old mme*/
		if(strcmp(row[1],(char *)origin_host) != 0){
					
			/*// Send cancel location to old mme
			printf("Sending CLR to old mme ...\n");
			test_send_clr((diameterid *)row[1], (diameterid *)row[2], (utf8string *)imsi, MME_UPDATE_PROCEDUR, //CLR msg sent on S6a/ 1); */
			
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
	get_terminal_info(req, &imei, NULL, &soft_version, NULL, &meid, NULL);

	/*Retrieve ue-srvcc-capability from request*/
	SS_WCHECK( ss_get_ue_srvcc_capability_msg(req, &ue_srvcc_capability), "UE-SRVCC-Capability value retrieved from request.\n", "Failed to retrieve UE-SRVCC-Capability value.\n", NULL);

	/*Insert/Update terminfo(Terminal-Information) table*/
	insert_update_db_terminfo( conn, imsi, (char *)imei, (char *)soft_version, (char *)meid, ue_srvcc_capability);

	/* Update database with Active-Apn AVPs*/
	update_active_apn( req, imsi, conn);

	/*close mysql connection*/
	mysql_close(conn);
	mysql_thread_end();

	/*Compare values of received message with the values sent*/
	check_ulr_val(req);

	/*Set supported feature*/
	test_set_supported_features(msg, (unsigned32) VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(msg, (unsigned32) VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/* Set Separation-Indication bit and Set ULA-Flags*/
	SET_ULA_SEPARATION_INDICATIN(gb_ula_flags); 
	SS_CHECK( ss_set_ula_flags( msg, gb_ula_flags), "ULA-Flags Set.\n", "Failed to set ULA-Flags.\n");

	/* extract ulr flag from request*/
	SS_CHECK( ss_get_ulr_flags_msg( req, &ulrflg), "ULR-Flags extracted from request.\n", "Failed to retrieve ulr flags value.\n");

	/*If skip subscriber data is not set in ulr flag then create and set Subscription-Data AVP*/
	if(!CHECK_ULR_SKIP_SUBSC_DATA(ulrflg)){
		fprintf(stdout, "ok : Setting subscription data ...\n");
		test_set_subsc_data(msg, imsi, ulrflg, req);
	}			

	/*Set Reset-Id, (only 3 AVPs set for testing)*/
	SS_CHECK( ss_set_reset_id(msg, gb_reset_ids[0], strlen((char *)gb_reset_ids[0])), "Reset-Id set.\n", "Failed to set Reset-Id.\n");
	SS_CHECK( ss_set_reset_id(msg, gb_reset_ids[1], strlen((char *)gb_reset_ids[1])), "Reset-Id 2 set.\n", "Failed to set Reset-Id 2.\n");
	SS_CHECK( ss_set_reset_id(msg, gb_reset_ids[2], strlen((char *)gb_reset_ids[2])), "Reset-Id 3 set.\n", "Failed to set Reset-Id 3.\n");

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

	unsigned char *origin_host = NULL;
	unsigned char *tmp_str = NULL;
	uint32_t tmp_u = 0;
	int32_t tmp_i = 0;
	char imsi[15] = {0};
	size_t len = 0;

	if(NULL == msg)
		return EINVAL;

	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : CLR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);		

	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(*msg, &tmp_str, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");
	strncpy(imsi,(char *)tmp_str,15);

	/*check Supported-Features child AVPs' values*/
	test_check_support_feature(*msg);

	/*Extract Cancellation-Type AVP*/
	SS_CHECK( ss_get_cancellation_type_msg(*msg, &tmp_i), "Cancellation-Type AVP set.\n", "Failed to set Cancellation-Type AVP.\n");
	/*compare Cancellation-Type value*/
	test_comp_int( tmp_i, gb_cancellation_type, "Cancellation-Type");

	/*Extract CLR-Flags AVP*/
	SS_CHECK( ss_get_clr_flags_msg(*msg, &tmp_u), "CLR-Flags AVP set\n", "Failed to set CLR-Flags AVP.\n");
	/*compare CLR-Flags value*/
	test_comp_uint( tmp_u, gb_clr_flags, "CLR-Flags");

	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "CLA Answer message header created from request.\n", "Failed to create CLA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);
	
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

	/*check Supported-Features child AVPs' values*/
	test_check_support_feature(*msg);
	
	/*Get Requested-EUTRAN-Authentication-Info */
	SS_WCHECK( get_req_eutran_auth_info(*msg, &num_req_vect_eutran, &immd_resp_pref, &re_sync_inf, &len), "Requested-EUTRAN-Authentication-Info retrieved.\n","Failed to retrieve Requested-EUTRAN-Authentication-Info.\n", NULL);
	/*compare Requested-EUTRAN-Authentication-Info value*/
	check_req_auth_info(&num_req_vect_eutran, &immd_resp_pref, re_sync_inf, len);	
	
	/*Get Requested-UTRAN-GERAN-Authentication-Info */
	SS_WCHECK(get_req_utran_geran_auth_info(*msg, &num_req_vect_utran, &immd_resp_pref, &re_sync_inf, &len), "Requested-UTRAN-Authentication-Info retrieved.\n","Failed to retrieve Requested-UTRAN-Authentication-Info.\n", NULL);
	/*compare Requested-UTRAN-Authentication-Info value*/
	check_req_auth_info(&num_req_vect_eutran, &immd_resp_pref, re_sync_inf, len);

	/*Get Visited-PLMN-Id*/
	SS_CHECK( ss_get_visited_plmn_id_msg(*msg, &visited_plmn_id, &len), "Visited-PLMN-Id retrieved.\n", "failed to retrieve Visited-PLMN-Id.\n");	
	/*compare Visited-PLMN-Id value*/
	test_comp_str( visited_plmn_id, gb_visited_plmn_id[0], len, strlen((char*)gb_visited_plmn_id[0]), "Visited-PLMN-Id");

	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "AIA Answer message header created from request.\n", "Failed to create AIA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/*Set Authentication-Info*/
	set_auth_info(msg, imsi, num_req_vect_utran, num_req_vect_eutran);

	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "CLA Response sent\n", "Failed to set CLA Response");*/
	fprintf(stdout,"OK : AIA Answer message passed to routing module.\n\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}

/*Callback function used when Insert-Subscriber-Data-Request message is received*/
int test_req_cb_idr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	unsigned char *tmp_str = NULL;
	unsigned char *origin_host = NULL;
	char imsi[16] = {0};
	size_t size = 0;
	unsigned32 idr_flgs = 0;
	octetstring **reset_ids = NULL;	
	size_t len = 0;
	size_t *len_arr = NULL;

	if(NULL == msg) return EINVAL;

	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : IDR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);		

	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(*msg, &tmp_str, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");
	sprintf(imsi, "%.15s", (char *)tmp_str);

	/*Extract Supported-Features child AVPs' values*/
	test_check_support_feature(*msg);
	
	/*Check for subscription data*/
	test_check_subsc_data(*msg, imsi);

	/*Extract IDR-Flags*/
	SS_WCHECK( ss_get_idr_flags_msg(*msg, &idr_flgs), "IDR-Flags retrieved.\n", "Failed to retrieve IDR-Flags.\n", NULL);
	/*compare IDR-Flags value*/
	test_comp_uint( idr_flgs, gb_idr_flags, "IDR-Flags");
	
	/*Extract Reset-Id*/
	SS_WCHECK( ss_get_reset_id_array(*msg, &reset_ids, &len_arr, &size), "Reset-Id retrieved.\n", "Failed to retrieve Reset-Id.\n", NULL);
	/*compare value*/
	while(size){

		test_comp_str( reset_ids[size-1], gb_reset_ids[size-1], len_arr[size-1], strlen((char*)gb_reset_ids[size-1]), "Reset-Id");
		size--;
	}
	if(reset_ids) free(reset_ids);
	if(len_arr) free(len_arr);

	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "AIA Answer message header created from request.\n", "Failed to create AIA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/*Set IMS-Voice-Over-PS-Sessions-Supported*/
	SS_CHECK( ss_set_ims_voice_over_ps_sessions_supported( msg, gb_ims_vop_sessions_supported), "IMS-Voice-Over-PS-Sessions-Supported set.\n", "Failed to set IMS-Voice-Over-PS-Sessions-Supported.\n");

	/*Set Last-UE-Activity-Time*/
	SS_CHECK( ss_set_last_ue_activity_time( msg, gb_last_ue_activity_time, strlen((char *)gb_last_ue_activity_time)), "Last-UE-Activity-Time set.\n", "Failed to set Last-UE-Activity-Time.\n");

	/*Set RAT-Type*/
	SS_CHECK( ss_set_rat_type(msg, gb_rat_type), "RAT-Type set.\n", "Failed to set RAT-Type.\n");

	/*Set IDA-Flags*/
	SS_CHECK( ss_set_ida_flags( msg, gb_ida_flags), "IDA-Flags set.\n", "Failed to set IDA-Flags.\n");

	/*Set EPS-User-State*/
	set_eps_usr_state(msg, gb_mme_user_state);

	/*Set EPS-Location-Information*/
	test_set_eps_location_info(msg);

	/*Set Local-Time-Zone*/
	set_local_time_zone(msg, gb_time_zone, gb_daylight_saving_time);

	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "IDA Response sent\n", "Failed to set IDA Response");*/
	fprintf(stdout,"OK : IDA Answer message passed to routing module.\n\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}

/*Callback function used when Delete-Subscriber-Data-Request message is received*/
int test_req_cb_dsr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	unsigned char *tmp_ustr = NULL;
	unsigned char *origin_host = NULL;
	size_t size = 0;
	unsigned32 *context_ids = NULL;
	unsigned char *tmp_str = NULL;
	unsigned char **tmp_str_arr = NULL;
	uint32_t tmp_u = 0;
	size_t len = 0;
	size_t *len_arr = NULL;

	if(NULL == msg) return EINVAL;

	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : DSR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);		

	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(*msg, &tmp_ustr, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");

	/*Extract Supported-Features child AVPs' values*/
	test_check_support_feature(*msg);

	/*Extract DSR-Flags*/
	SS_CHECK( ss_get_dsr_flags_msg(*msg, &tmp_u), "DSR-Flags retrieved.\n", "Failed to retrieve DSR-Flags.\n");
	/*compare DSR-Flags values*/
	test_comp_uint( tmp_u, gb_dsr_flags, "DSR-Flags");
	
	/*Extract Context-Identifier*/
	SS_WCHECK( ss_get_context_identifier_array(*msg, &context_ids, &size), "Context-Identifier retrieved.\n", "Failed to retrieve Context-Identifier.\n", NULL);
	while(size){
	
		test_comp_uint( context_ids[size-1], gb_context_identifier[size-1], "Context-Id");
		size--;
	}
	if(context_ids) free(context_ids);

	/*Extract Trace-Reference*/
	SS_WCHECK( ss_get_trace_reference_msg( *msg, &tmp_str, &len), "Trace-Reference set.\n", "Failed to set Trace-Reference.\n", NULL);
	/*compare Trace-Reference value*/
	test_comp_str( tmp_str, gb_trace_reference, len, strlen((char*)gb_trace_reference), "Trace-Reference");

	/*Extract TS-Code*/
	SS_WCHECK( ss_get_ts_code_array( *msg, &tmp_str_arr, &len_arr, &size), "TS-Code set.\n","Failed to set TS-Code.\n", NULL);
	/*compare TS-Code value*/
	while(size){

		test_comp_str( tmp_str_arr[size-1], gb_ts_code[size-1], len_arr[size-1], strlen((char*)gb_ts_code[size-1]), "TS-Code");
		size--;
	}
	if(tmp_str_arr) free(tmp_str_arr);
	if(len_arr) free(len_arr);

	/*Extract SS-Code*/
	SS_WCHECK( ss_get_ts_code_array( *msg, &tmp_str_arr, &len_arr, &size), "SS-Code set.\n","Failed to set SS-Code.\n", NULL);
	/*compare SS-Code value*/
	while(size){

		test_comp_str( tmp_str_arr[size-1], gb_ss_code[size-1], len_arr[size-1], strlen((char*)gb_ss_code[size-1]), "SS-Code");
		size--;
	}
	if(tmp_str_arr) free(tmp_str_arr);
	if(len_arr) free(len_arr);	

	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "DSA Answer message header created from request.\n", "Failed to create DSA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/*Set DSA-flags*/
	SS_CHECK( ss_set_dsa_flags( msg, gb_dsa_flags), "DSA-flags set.\n", "Failed to set DSA-flags.\n");

	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "IDA Response sent\n", "Failed to set IDA Response");*/
	fprintf(stdout,"OK : DSA Answer message passed to routing module.\n\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}

/*Callback function used when Purge-UE-Request message is received*/
int test_req_cb_pur(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	unsigned char *tmp_str = NULL;
	unsigned char *origin_host = NULL;
	uint32_t tmp_u = 0;
	size_t len = 0;

	if(NULL == msg) return EINVAL;

	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : PUR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);		

	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(*msg, &tmp_str, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");

	/*Check Supported-Features child AVPs' values*/
	test_check_support_feature(*msg);

	/*Extract PUR-Flags*/
	SS_CHECK( ss_get_pur_flags_msg(*msg, &tmp_u), "PUR-Flags retrieved.\n", "Failed to retrieve PUR-Flags.\n");	
	/*compare PUR-Flags value*/
	test_comp_uint( tmp_u, gb_pur_flags, "PUR-Flags");

	/*check EPS-Location-Information*/
	test_check_eps_location_info(*msg);
	
	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "PUA Answer message header created from request.\n", "Failed to create PUA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/*Set PUA-flags*/
	SS_CHECK( ss_set_pua_flags( msg, gb_pua_flags), "PUA-flags set.\n", "Failed to set PUA-flags.\n");

	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "PUA Response sent\n", "Failed to set PUA Response");*/
	fprintf(stdout,"OK : PUA Answer message passed to routing module.\n\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}

/*Callback function used when Reset-Request message is received*/
int test_req_cb_rsr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	unsigned char *origin_host = NULL;
	utf8string **tmp_str_arr = NULL;
	size_t size = 0;
	size_t len = 0;
	size_t *len_arr = NULL;

	if(NULL == msg) return EINVAL;

	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : RSR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);		

	/*Extract Supported-Features child AVPs' values*/
	test_check_support_feature(*msg);

	/*Extract User-Id*/
	SS_WCHECK( ss_get_user_id_array(*msg, &tmp_str_arr, &len_arr, &size), "User-Id values retrieved.\n", "Failed to retrieve User-Id values.\n", NULL);
	/*compare User-Id value*/
	while(size){
	
		test_comp_str( tmp_str_arr[size-1], gb_user_id[size-1], len_arr[size-1], strlen((char*)gb_user_id[size-1]), "User-Id");
		size--;
	}
	if(tmp_str_arr) free(tmp_str_arr);
	if(len_arr) free(len_arr);

	/*Extract Reset-Id*/
	size = 0;
	SS_WCHECK( ss_get_reset_id_array(*msg, &tmp_str_arr, &len_arr, &size), "Reset-Id values retrieved.\n", "Failed to retrieve Reset-Id values.\n", NULL);
	/*compare Reset-Id value*/
	while(size){
	
		test_comp_str( tmp_str_arr[size-1], gb_reset_ids[size-1], len_arr[size-1], strlen((char*)gb_reset_ids[size-1]), "Reset-Id");
		size--;
	}
	if(tmp_str_arr) free(tmp_str_arr);
	if(len_arr) free(len_arr);

	/* Create answer message header from the request*/
	SS_CHECK( ss_msg_create_answer( msg), "RSA Answer message header created from request.\n", "Failed to create RSA answer message header.\n");	

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set two Supported-Freatures AVP*/
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(msg, (int)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "RSA Response sent\n", "Failed to set RSA Response");*/
	fprintf(stdout,"OK : RSA Answer message passed to routing module.\n\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}

/*Callback function used when Notify-Request message is received*/
int test_req_cb_nor(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){
	
	diameterid * origin_host = NULL;
	unsigned char *tmp_str = NULL;
	uint32_t tmp_u = 0;
	int32_t tmp_i = 0;
	size_t len = 0;

	if (msg == NULL) return EINVAL;	
	
	/* Message Received */
	SS_CHECK( ss_get_origin_host_msg( *msg, &origin_host, &len), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : NOR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);	
	
	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name_msg(*msg, &tmp_str, &len), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");

	/*Retrieve Feature-List AVP value from request*/
	test_check_support_feature(*msg);

	/*check terminal information from request*/
	check_terminal_info(*msg);

	/*check MIP6-Agent-Info*/
	test_check_mip6_values((avp_or_msg *)*msg);

	/*Get Visited-Network-Identifier*/
	SS_CHECK( ss_get_visited_network_identifier_msg( *msg, &tmp_str, &len), "Visited-Network-Identifier retrieved.\n", "Failed to retrieve Visited-Network-Identifier.\n");
	/*compare Visited-Network-Identifier value*/
	test_comp_str( tmp_str, gb_visited_network_identifier, len, strlen((char*)gb_visited_network_identifier), "Visited-Network-Identifier");

	/*Get Context-Identifier*/
	SS_CHECK( ss_get_context_identifier_msg(*msg, &tmp_u), "Context-Identifier retrieved.\n", "Failed to retrieve Context-Identifier/\n");
	/*compare Context-Identifier value*/	
	test_comp_uint( tmp_u, gb_context_identifier[0], "Context-Identifier");

	/*Get Service-Selection*/
	SS_CHECK( ss_get_service_selection_msg( *msg, &tmp_str, &len), "Service-Selection retrieved.\n", "Failed to retrieve Service-Selection.\n");
	/*compare Service-Selection value*/
	test_comp_str( tmp_str, gb_service_selection, len, strlen((char*)gb_service_selection), "Service-Selection");

	/*Get Alert-Reason*/
	SS_CHECK( ss_get_alert_reason_msg(*msg, &tmp_i), "Alert-Reason retrieved.\n", "Failed to retrieve Alert-Reason.\n");
	/*compare Alert-Reason value*/
	test_comp_int( tmp_i, (int32_t)gb_alert_reason, "Alert-Reason");

	/*Retrieve ue-srvcc-capability from request*/
	SS_WCHECK( ss_get_ue_srvcc_capability_msg(*msg, &tmp_i), "UE-SRVCC-Capability value retrieved from request.\n", "Failed to retrieve UE-SRVCC-Capability value.\n", NULL);
	/*compare ue-srvcc-capability value*/
	test_comp_int( tmp_i, (int32_t)gb_ue_srvcc_capability, "ue-srvcc-capability");
	
	/*Set NOR-Flags AVP*/
	SS_CHECK( ss_get_nor_flags_msg( *msg, &tmp_u), "NOR-Flags AVP retrieved.\n","Failed to retrieve NOR-Flags AVP\n");
	/*compare NOR-Flags value*/	
	test_comp_uint( tmp_u, gb_nor_flags, "NOR-Flags");
	
	/*Get Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP*/
	SS_CHECK( ss_get_homogeneous_support_of_ims_voice_over_ps_sessions_msg( *msg, &tmp_i), "Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP Retrieved.\n","Failed to Retrieve Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP\n");
	/*compare Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions value*/
	test_comp_int( tmp_i, (int32_t)gb_homogeneous_support_ims_voice_over_ps_sessions, "Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions");

	/* Create answer message header from the request, copy the request before creating answer */
	SS_CHECK( ss_msg_create_answer( msg), "Answer message header created from request.\n", "Failed to create answer message header.\n");

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*Set supported feature*/
	test_set_supported_features(msg, (unsigned32) VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(msg, (unsigned32) VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/* Send the answer */
	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "NOA Response sent\n", "Failed to set NOA Response");*/
	fprintf(stdout,"OK : Answer message passed to routing module.\n");
	*act == DISP_ACT_SEND; /*fd_msg_send(msg, NULL,NULL) can also be used here*/

	return 0;
}
