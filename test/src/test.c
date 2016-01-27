
#include "test.h"

#define CHECK_ULR_GPRS_DATA_IND(x)	((1U<<3) & x) 

#define MYSQL_CONF_FILE_NAME "mysql.conf"

/*macro to be used by function parse_db_conf only*/
#define PARSE_VALUE(value_name, value_variable) {					\
		if((value = test_parse_string(buff, value_name)) == NULL)		\
			goto error;												\
		*value_variable = value;									\
		value = NULL;												\
	}

/*values should be freed after use*/
static int parse_db_conf(char * filename, char ** server, char ** db_name, char ** user_name, char ** password){

	char * buff = NULL;	
	char * value = NULL;

	if((!filename))	return 1;

	if((!server) && (!db_name) && (!user_name) && (!password))	return 1;

	/*read confile*/
	if((buff = test_parse_conf(filename)) == NULL)	return 1;

	/*search for server*/
	if(server)
		PARSE_VALUE("server=", server)
	/*search for database name*/
	if(db_name)
		PARSE_VALUE("database=", db_name)
	/*search for user name*/
	if(user_name)
		PARSE_VALUE("username=", user_name)
	/*search for password*/
	if(password)
		PARSE_VALUE("password=", password)
	
	free(buff);
	return 0;

error:
	fprintf(stderr, "Error : Error parsing values in 'mysql.conf' file.\n");
	free(buff);
	return 1;
}

/*Connect to mysql database*/
void test_connect_db(MYSQL **conn){

	*conn = mysql_init(NULL);
	char * server = NULL;
	char * user_name = NULL;
	char * password = NULL;
	char * db_name = NULL;

	/*parse mysql server configuration*/
	SS_CHECK(parse_db_conf(MYSQL_CONF_FILE_NAME, &server, &db_name, &user_name, &password), "Mysql confile parsed.\n", "Failed to parse mysql confile.\n");	

	/* Connect to database */
	if (!mysql_real_connect(*conn, server, user_name, password, db_name, 0, NULL, 0)) {
		fprintf(stderr, "mysql db connection failed:%s\n", mysql_error(*conn));
		exit(1);
	}

	free(server); 
	free(user_name); 
	free(password);
	free(db_name);
}

/*Query database and get result*/
int test_get_qry_res(MYSQL *conn, char * statement, MYSQL_RES **res){

	if((!conn) || (!statement) || (!res))	return 1;

	if (mysql_query(conn, statement)) fprintf(stderr, "%s\n", mysql_error(conn));      				
			
	if((*res = mysql_store_result(conn)) != NULL)	return 0;
	else fprintf(stderr, "Error %s\n", mysql_error(conn));

	return 1;
}

/*Set Supported-Features group AVP*/
void test_set_supported_features(struct msg **msg, unsigned32 vnd_id, unsigned32 ftr_id, unsigned32 ftr_lst){

	struct avp * tmp_gavp;

	if(!msg) return;

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
	
	if(ftr_lst) *ftr_lst = lst;

	*size = sz;
}

/*Check Supported-Features group AVP child AVPs' values*/
void test_check_support_feature( struct msg *msg){

	unsigned32 *ftr_lst_id = NULL;	
	unsigned32 *ftr_lst = NULL;
	size_t size = 0;

	test_get_supported_features(msg, &ftr_lst_id, &ftr_lst, &size);


	while(size){

		/*Check Feature-List-Id values*/
		if(ftr_lst_id)
			test_comp_uint( gb_feature_list_id[size-1], ftr_lst_id[size-1], "Feature-List-Id");		

		/*Check Feature-List*/
		if(ftr_lst)
			test_comp_uint( gb_feature_list[size-1], ftr_lst[size-1], "Feature-List");		
	
		size --;
	}

	if(ftr_lst_id) free(ftr_lst_id);
	if(ftr_lst) free(ftr_lst);			
}

/* Sends cancel location request*/
int test_send_clr(diameterid *dst_host, diameterid *dst_rlm, utf8string * imsi, enum cancellation_type cncl_typ, unsigned32 clr_flg){
	
	struct msg * clr;
	
	if((!dst_host) || (!dst_rlm) || (!imsi)) return 1;

	/*Create Cancel-Location-Request message*/
	SS_CHECK( ss_msg_create_clr(&clr), "Cancel-Location-Request message Created.\n", "Error in creating Cancel-Location-Request message.\n");

	/*Set Destination-Host AVP*/	
	SS_CHECK( ss_set_destination_host( (avp_or_msg **)&clr, dst_host, strlen((char *)dst_host)), "Destination-Host AVP set.\n","Failed to set Destination-Host AVP\n");
	
	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( (avp_or_msg **)&clr, dst_rlm, strlen((char *)dst_rlm)), "Destination-Realm AVP set.\n","Failed to set Destination-Realm AVP\n");

	/*Set User-Name AVP*/
	SS_CHECK( ss_set_user_name( &clr, imsi, strlen((char *)imsi)), "User-Name AVP set.\n","Failed to set User-Name AVP\n");
	
	/*Set Supported-Features group AVP (Only 2 AVPs set for testing)*/
	test_set_supported_features(&clr, (int)VENDOR_ID_3GPP, gb_feature_list_id[0], gb_feature_list[0]);
	test_set_supported_features(&clr, (int)VENDOR_ID_3GPP, gb_feature_list_id[1], gb_feature_list[1]);

	/*Set Cancellation-Type AVP*/
	SS_CHECK( ss_set_cancellation_type(&clr, cncl_typ), "Cancellation-Type AVP set.\n", "Failed to set Cancellation-Type AVP.\n");
	
	/*Set CLR-Flags AVP*/
	SS_CHECK( ss_set_clr_flags(&clr, clr_flg), "CLR-Flags AVP set\n", "Failed to set CLR-Flags AVP.\n");

	/*Send Cancel-Location-Request message sent*/
	SS_CHECK( fd_msg_send( &clr, test_ans_cb_clr, NULL), "CLR request message sent.\n","Failed to send CLR request message.\n");
	
	return 0;
}

/*** Set MIP6-Agent-Info AVP ***/
void test_set_mip6(avp_or_msg **msg_gavp, address *ipv4, address *ipv6, char *host, char *realm){
	
	struct avp * tmp_gavp;
	struct avp * tmp_gavp2;
					
	if(!msg_gavp)	return;

	if( (!ipv4) && (!ipv6) && (!host) && (!realm))	return;

	/*Create MIP6-Agent-Info group AVP*/
	SS_CHECK( ss_create_mip6_agent_info(&tmp_gavp), "MIP6-Agent-Info Created.\n", "Failed to create MIP6-Agent-Info.\n");

	/* Set MIP-Home-Agent-Address avp (IPV4 and IPV6)*/
	if(ipv4)
		SS_CHECK( ss_set_mip_home_agent_address( &tmp_gavp, ipv4, 4), "MIP-Home-Agent-Address IPV4 set.\n", "Failed to set MIP-Home-Agent-Address IPV4.\n");	
	if(ipv6)
		SS_CHECK( ss_set_mip_home_agent_address( &tmp_gavp, ipv6, 16), "MIP-Home-Agent-Address IPV6 set.\n", "Failed to set MIP-Home-Agent-Address IPV6.\n");	

	/* Create MIP-Home-Agent-Host AVP*/
	SS_CHECK( ss_create_mip_home_agent_host( &tmp_gavp2), "MIP-Home-Agent-Host created.\n", "Failed to create MIP-Home-Agent-Host AVP.\n");
	
	/*Set Destination-Host avp*/
	if(host)
		SS_CHECK( ss_set_destination_host( (avp_or_msg **)&tmp_gavp2, (unsigned char *)host, strlen(host)), "Destination-Host set into MIP-Home-Agent-Host.\n", "Failed to set Destination-Host into MIP-Home-Agent-Host.\n");

	/* Set Destination-Realm avp*/
	if(realm)
		SS_CHECK( ss_set_destination_realm( (avp_or_msg **)&tmp_gavp2, (unsigned char *)realm, strlen(realm)), "Destination-Realm set into MIP-Home-Agent-Host.\n", "Failed to set Destination-Realm into MIP-Home-Agent-Host.\n");
	
	/*Add MIP-Home-Agent-Host AVP into MIP6-Agent-Info group AVP*/
	if((host) && (realm))
		SS_CHECK( ss_add_avp( (avp_or_msg **)&tmp_gavp, tmp_gavp2 ), "MIP-Home-Agent-Host added.\n", "Failed to add MIP-Home-Agent-Host.\n");
			
	/*Add MIP6-Agent-Info group AVP into the group AVP provided in parameter 'gavp'*/			
	SS_CHECK( ss_add_avp( (avp_or_msg **)msg_gavp, tmp_gavp), "MIP6-Agent-Info added.\n", "Failed to add MIP6-Agent-Info.\n");
}

/*Get MIP-Home-Agent-Address*/
static inline int get_mip_addr(struct avp *gavp, address ** addr_v4, address ** addr_v6){

	address ** hm_agnt_addr = NULL;
	size_t array_size = 0;
	size_t *len = NULL;
	int check = 0;

	if(!gavp) return 1;
	
	if((!addr_v4) && (!addr_v6))	return 1;

	/*Get MIP-Home-Agent-Address*/							
	SS_WCHECK( ss_get_mip_home_agent_address_gavp_array( gavp, &hm_agnt_addr, &len,&array_size), "MIP-Home-Agent-Address array of values retrieved.\n", "Failed to retrieve MIP-Home-Agent-Address values.\n", return 1);

	while(array_size){
		
		/*Get home-agent-address IPV6 address*/
		if( (16 == len[array_size-1]) && (addr_v6)){
			
		 	*addr_v6 = hm_agnt_addr[array_size-1];
			check++;
		}
		/*Get IPV4 address*/
		else if(4 == (len[array_size-1]) && (addr_v4)){
			
			*addr_v4 = hm_agnt_addr[array_size-1];
			check++;			
		}
		array_size--;
	}	

	if(hm_agnt_addr) free(hm_agnt_addr);
	if(len) free(len);

	/*if at least either IPV4 or IPV6 address is found return success*/
	if(check) return 0;

	return 1;
}

/*Check MIP-Home-Agent-Address*/
static inline void check_mip_addr(struct avp *gavp){

	unsigned char *addr_v4 = NULL;
	unsigned char *addr_v6 = NULL;	

	if(!gavp) return;

	/*Get IPV4 and IPV6 address*/	
	get_mip_addr( gavp, &addr_v4, &addr_v6);

	/*Compare IPV4 address*/
	if(addr_v4) test_comp_str( addr_v4, gb_home_agent_address_v4, 4, "Home-Agent-Address IPV4");

	/*Compare IPV6 address*/
	if(addr_v6) test_comp_str( addr_v6, gb_home_agent_address_v6, 16, "Home-Agent-Address IPV6");
}

/*Get MIP-Home-Agent-Host child avp values*/
static inline int get_mip_home_agnt_hst(struct avp * gavp, diameterid ** dst_host, size_t *len_host, diameterid ** dst_realm, size_t *len_realm){

	struct avp *tmp_gavp = NULL;
	size_t len = 0;

	if((!gavp) || (!dst_host) || (!dst_realm)) return 1;

	/*Get MIP-Home-Agent-Host AVP*/
	SS_WCHECK( ss_get_gavp_mip_home_agent_host(gavp, &tmp_gavp), "MIP-Home-Agent-Host AVP retrieved,\n", "Failed to retrieve MIP-Home-Agent-Host.\n", return 1;);
	
	/*Get Destination-Host value*/
	SS_CHECK(ss_get_destination_host(tmp_gavp, dst_host, &len), "Destination-Host retrieved.\n", "Failed to extract Destination-Host.\n");		
	if(len_host) *len_host = len;	

	/*Get Destination-Realm value*/
	SS_CHECK(ss_get_destination_realm(tmp_gavp, dst_realm, &len), "Destination-Realm retrieved.\n", "Failed to extract Destination-Realm.\n");
	if(len_realm) *len_realm = len;
	
	return 0;		
}

/*Check MIP-Home-Agent-Host child avp values*/
static inline void check_mip_home_agnt_hst(struct avp * gavp){

	unsigned char *dst_host = NULL;
	unsigned char *dst_realm = NULL;
	size_t len_host = 0;
	size_t len_realm = 0;

	if(!gavp) return;

	/*Get Destination-Host and Destination-Realm values*/
	get_mip_home_agnt_hst(gavp, &dst_host, &len_host, &dst_realm, &len_realm);	

	/*Compare Destination-Host*/
	test_comp_str( dst_host, gb_home_agent_host_host, len_host, "Destination-Host");

	/*Compare Destination-Realm*/
	test_comp_str( dst_realm, gb_home_agent_host_realm, len_realm, "Destination-Realm");
}

/*Get MIP6-Agent-Info child AVP values*/
int test_get_mip6_values(struct avp *gavp, address ** addr_v4, address ** addr_v6, diameterid ** dst_host, diameterid ** dst_realm){

	struct avp * tmp_gavp;	
	int check = 1;

	if(!gavp) return 1;

	if((!addr_v4) && (!addr_v6) && (!dst_host) && (!dst_realm)) return 1;

	/*check for  MIP6-Agent-Info avp*/
	SS_WCHECK( ss_get_gavp_mip6_agent_info(gavp, &tmp_gavp) , "MIP6-Agent-Info retrieved.\n", "Failed to retrieve MIP6-Agent-Info.\n", return 1;);
		
	/*check for the MIP-Home-Agent-Address*/	
	SS_WCHECK( get_mip_addr(tmp_gavp, addr_v4, addr_v6), "MIP-Home-Agent-Address retrieved.\n", "Failed to retrieve MIP-Home-Agent-Address.\n", check++);						
							
	/*check for  MIP-Home-Agent-Host */
	SS_WCHECK( get_mip_home_agnt_hst(tmp_gavp, dst_host, NULL, dst_realm, NULL), "MIP-Home-Agent-Host child AVP values retrieved.\n", "Failed to retrieve MIP-Home-Agent-Host child AVP values.\n", check++);	

	/*if both MIP-Home-Agent-Address and MIP-Home-Agent-Host fails to be retrieved*/
	if(check == 3)
		return 1;
	
	return 0;						
}

/*Get MIP6-Agent-Info child AVP values*/
void test_check_mip6_values(avp_or_msg *msg_gavp){

	struct avp *tmp_gavp = NULL;	

	if(!msg_gavp) return;

	/*Get for  MIP6-Agent-Info avp*/
	SS_WCHECK( ss_get_gavp_mip6_agent_info(msg_gavp, &tmp_gavp) , "MIP6-Agent-Info retrieved.\n", "Failed to retrieve MIP6-Agent-Info.\n", return);
		
	/*check for the MIP-Home-Agent-Address*/	
	check_mip_addr(tmp_gavp);	
							
	/*check for  MIP-Home-Agent-Host */
	check_mip_home_agnt_hst(tmp_gavp);
}

/*Get Specific-APN-Info child AVP values*/
void test_check_spec_apn_info(struct avp *gavp){

	struct avp *tmp_gavp = NULL;	
	struct avp *tmp_gavp2 = NULL;	
	unsigned char *tmp_str = NULL;
	size_t len = 0;

	if(!gavp) return;

	/*Get Specific-APN-Info AVP*/
	SS_WCHECK( ss_get_gavp_specific_apn_info(gavp, &tmp_gavp), "Specific-APN-Info retrieved.\n", "Failed to retrieve Specific-APN-Info.\n", return);

	while(tmp_gavp){

		/*Get Service-Selection value*/
		SS_CHECK( ss_get_service_selection(tmp_gavp, &tmp_str, &len), "Service-Selection retrieved.\n", "Failed to retrieve Service-Selection.\n");
		/*Check Service-Selection value*/
		test_comp_str( tmp_str, gb_service_selection, len, "Service-Selection");

		/*Check MIP6-Agent-Info child AVP values*/
		test_check_mip6_values(tmp_gavp);	

		/*Get Visited-Network-Identifier value*/
		SS_WCHECK( ss_get_visited_network_identifier(tmp_gavp, &tmp_str, &len), "Visited-Network-Identifier retrieved.\n", "Failed to retrieve Visited-Network-Identifier.\n", NULL);
		/*Check Visited-Network-Identifier value*/	
		test_comp_str( tmp_str, gb_visited_network_identifier, len, "Visited-Network-Identifier");

		/*Get next Specific-APN-Info*/
		SS_WCHECK( ss_get_gavp_next_specific_apn_info(tmp_gavp, &tmp_gavp2), "Next Specific-APN-Info retrieved.\n", "Failed to retrieve next Specific-APN-Info.\n", return);
		tmp_gavp = tmp_gavp2;
		tmp_gavp2 = NULL;		
	}
}

/*Set MO-LR group AVP*/
static void set_mo_lr(struct avp **gavp, octetstring * ss_cd, octetstring * ss_sts){

	struct avp *tmp_gavp = NULL;

	if((!gavp) || (!ss_cd) || (!ss_sts)) return;

	/*Create MO-LR group AVP*/
	SS_CHECK( ss_create_mo_lr( &tmp_gavp), "MO-LR AVP created.\n", "Failed to create MO-LR AVP.\n");		
	
	/*Set SS-Code AVP*/
	SS_CHECK( ss_set_ss_code( (avp_or_msg **)&tmp_gavp, ss_cd, strlen((char *)ss_cd)), "SS-Code set.\n", "Failed to Set SS-Code.\n");
	
	/*Set SS-Status AVP*/
	SS_CHECK( ss_set_ss_status( &tmp_gavp, ss_sts, strlen((char *)ss_sts)), "SS-Status set.\n", "Failed to Set SS-Status.\n");

	/*Add MO-LR group AVP*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "MO-LR added.\n", "Failed to add MO-LR.\n");
}

/*Check MO-LR group AVP*/
static void check_mo_lr(struct avp *avp, MYSQL_ROW row){

	struct avp * tmp_gavp = NULL;
	struct avp * tmp_gavp2 = NULL;
	octetstring * tmp_str = NULL;
	size_t len = 0;
	int indx = 4;

	if((!avp) || (!row)) return;

	/*Get MO-LR group AVP*/
	SS_WCHECK( ss_get_gavp_mo_lr( avp, &tmp_gavp), "MO-LR AVP retrieved.\n", "Failed to retrieve MO-LR AVP.\n", return);		
	while(tmp_gavp){
	
		/*Get SS-Code AVP*/
		SS_CHECK( ss_get_ss_code( tmp_gavp, &tmp_str, &len), "SS-Code retrieved.\n", "Failed to retrieve SS-Code.\n");
		/*compare SS-Code value*/
		test_comp_str( tmp_str, (unsigned char *)row[indx], len, "SS-Code");
	
		/*Get SS-Status AVP*/
		SS_CHECK( ss_get_ss_status( tmp_gavp, &tmp_str, &len), "SS-Status retrieved.\n", "Failed to retrieve SS-Status.\n");
		/*compare SS-Status value*/
		test_comp_str( tmp_str, (unsigned char *)row[indx+1], len, "SS-Status");

		/*Get next MO-LR group AVP*/
		SS_WCHECK( ss_get_gavp_next_mo_lr(tmp_gavp, &tmp_gavp2), "Next MO-LR AVP retrieved.\n", "Failed to retrieve next MO-LR AVP.\n", return);

		tmp_gavp = tmp_gavp2;
		tmp_gavp2 = NULL;

		indx += 2;
	}
}

/*Set LCS-Info*/
void test_set_lcs_info(struct avp **gavp, char * imsi){

	struct avp * tmp_gavp;	
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi)) return;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get LCS info data*/	
	sprintf(buf,"select * from lcsInfo where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "LCS info data retrieved from db.\n", "Failed to retrieve LCS info data from database.\n");     				
			
	if((row = mysql_fetch_row(res))!= NULL){
	
		/* Create LCS-Info group AVP*/
		SS_CHECK( ss_create_lcs_info( &tmp_gavp), "LCS-Info AVP created.\n", "Failed to create LCS-Info AVP.\n");
		
		/* Set GMLC-Number AVPs (only 3 AVPs for testing purpose)*/
		if(row[1])
			SS_CHECK( ss_set_gmlc_number( &tmp_gavp, (octetstring *)row[1], strlen((char *)row[1])), "GMLC-Number 1 set.\n", "Failed to Set GMLC-Number 1.\n");
		if(row[2])
			SS_CHECK( ss_set_gmlc_number( &tmp_gavp, (octetstring *)row[2], strlen((char *)row[2])), "GMLC-Number 2 set.\n", "Failed to Set GMLC-Number 2.\n");
		if(row[3])
			SS_CHECK( ss_set_gmlc_number( &tmp_gavp, (octetstring *)row[3], strlen((char *)row[3])), "GMLC-Number 3 set.\n", "Failed to Set GMLC-Number 3.\n");

		/* Set MO-LR group AVP (only 3 AVPs for testing purpose)*/
		set_mo_lr( &tmp_gavp, (octetstring *) row[4], (octetstring *) row[5]);
		set_mo_lr( &tmp_gavp, (octetstring *) row[6], (octetstring *) row[7]);
		set_mo_lr( &tmp_gavp, (octetstring *) row[8], (octetstring *) row[9]);

		SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "LCS-Info added.\n", "Failed to add LCS-Info.\n");
	}

	mysql_free_result(res);
	mysql_close(conn);
}

/*Check LCS-Info*/
void test_check_lcs_info(struct avp *gavp, char *imsi){

	struct avp *tmp_gavp = NULL;
	octetstring **tmp_str_arr = NULL;
	size_t size = 0;
	size_t *len = NULL;
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;
	
	if((!gavp) || (!imsi)) return;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get LCS info data*/	
	sprintf(buf,"select * from lcsInfo where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "LCS info data retrieved from db.\n", "Failed to retrieve LCS info data from database.\n");     				
			
	if(NULL == (row = mysql_fetch_row(res))) return;

	/* Get LCS-Info group AVP*/
	SS_WCHECK( ss_get_gavp_lcs_info( gavp, &tmp_gavp), "LCS-Info AVP retrieved.\n", "Failed to retrieve LCS-Info AVP.\n", return);
		
	/* check GMLC-Number AVPs (only 3 AVPs for testing purpose)*/
	SS_WCHECK( ss_get_gmlc_number_gavp_array( tmp_gavp, &tmp_str_arr, &len, &size), "GMLC-Number Retrieved.\n", "Failed to retrieve GMLC-Number.\n", NULL);
	while(size){
	
		test_comp_str( tmp_str_arr[size-1], (unsigned char *)row[size], len[size-1], "GMLC-Number");

		size--;
	}
	if(tmp_str_arr) free(tmp_str_arr);
	if(len) free(len);
	
	/* check MO-LR group AVP (only 3 AVPs for testing purpose)*/
	check_mo_lr( tmp_gavp, row);		

	mysql_free_result(res);
	mysql_close(conn);	
}

/* Create Teleservice-List*/
void test_set_teleserv_list(struct avp **gavp, octetstring *ts_cd1, octetstring *ts_cd2, octetstring *ts_cd3){

	struct avp * tmp_gavp;

	if((!gavp))
		return;
	if((!ts_cd1) && (!ts_cd2) && (!ts_cd3))
		return;
	/*Create Teleservice-List group AVP*/
	SS_CHECK( ss_create_teleservice_list(&tmp_gavp), "Teleservice-List AVP created.\n", "Failed to create Teleservice-List.\n");

	/*Set TS-Code AVP(3 AVPs for test)*/
	if(ts_cd1)
		SS_CHECK( ss_set_ts_code( (avp_or_msg **)&tmp_gavp, ts_cd1, strlen((char *)ts_cd1)), "TS-Code 1 set.\n", "Failed to set TS-Code 1.\n");
	if(ts_cd2)
		SS_CHECK( ss_set_ts_code( (avp_or_msg **)&tmp_gavp, ts_cd2, strlen((char *)ts_cd2)), "TS-Code 2 set.\n", "Failed to set TS-Code 2.\n");
	if(ts_cd3)
		SS_CHECK( ss_set_ts_code( (avp_or_msg **)&tmp_gavp, ts_cd3, strlen((char *)ts_cd3)), "TS-Code 3 set.\n", "Failed to set TS-Code 3.\n");
	
	/*Add Teleservice-List group AVP*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "Teleservice-List added.\n", "Failed to add Teleservice-List.\n");
}

/* Check Teleservice-List*/
static void check_teleserv_list(struct avp *avp, octetstring *ts_cd1, octetstring *ts_cd2, octetstring *ts_cd3){

	struct avp *tmp_gavp = NULL;
	octetstring *ts_cd_arr[3];
	octetstring **tmp_str_arr = NULL;
	size_t size = 0;
	size_t *len = NULL;

	if((!avp) || (!ts_cd1) || (!ts_cd2) || (!ts_cd3)) return;

	ts_cd_arr[0] = ts_cd1;
	ts_cd_arr[1] = ts_cd2;
	ts_cd_arr[2] = ts_cd3;
	
	/*Get Teleservice-List group AVP*/
	SS_WCHECK( ss_get_gavp_teleservice_list(avp, &tmp_gavp), "Teleservice-List AVP retrieved.\n", "Failed to retrieve Teleservice-List.\n",return);

	/*check TS-Code AVP*/
	SS_CHECK( ss_get_ts_code_gavp_array( tmp_gavp, &tmp_str_arr, &len, &size), "TS-Code retrieved.\n", "Failed to retrieve TS-Code.\n");
	while(size){
	
		test_comp_str( tmp_str_arr[size-1], ts_cd_arr[size-1], len[size-1], "TS-Code");

		size--;
	}
	if(tmp_str_arr) free(tmp_str_arr);
	if(len) free(len);
}

/*Set Call-Barring-Info */
void test_set_call_barring_info(struct avp **gavp, char * imsi){

	struct avp * tmp_gavp = NULL;	
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi)) return;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get call barring info data*/	
	sprintf(buf,"select * from callBaringInfo where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "Call barring info retrieved from db.\n", "Failed to retrieve callbarring info data from database.\n");

	while((row = mysql_fetch_row(res)) != NULL){

		/*Create Call-Barring-Info group AVP*/
		SS_CHECK( ss_create_call_barring_info( &tmp_gavp), "Call-Barring-Info AVP created.\n", "Failed to create Call-Barring-Info.\n");	
						
		/*Set SS-Code*/	
		if(row[1])
			SS_CHECK( ss_set_ss_code( (avp_or_msg **)&tmp_gavp, (octetstring *)row[1], strlen((char *)row[1])), "SS-Code set.\n", "Failed to set SS-Code.\n");

		/*Set SS-Status*/	
		if(row[2])
			SS_CHECK( ss_set_ss_status( &tmp_gavp, (octetstring *)row[2], strlen((char *)row[2])), "SS-Status set.\n", "Failed to set SS-Status.\n");

		/*Add Call-Barring-Info*/
		SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "Call-Barring-Info added.\n", "Failed to add Call-Barring-Info AVP.\n");		
	} 

	mysql_free_result(res);
	mysql_close(conn);
}

/*Check Call-Barring-Info */
static void check_call_barring_info(struct avp *gavp, char *imsi){

	struct avp * tmp_gavp = NULL;
	struct avp * tmp_gavp2 = NULL;
	octetstring * tmp_str = NULL;
	size_t len = 0;	
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;
	
	if((!gavp) || (!imsi)) return;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get call barring info data*/	
	sprintf(buf,"select * from callBaringInfo where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "Call barring info retrieved from db.\n", "Failed to retrieve callbarring info data from database.\n");

	/*Get Call-Barring-Info group AVP*/
	SS_WCHECK( ss_get_gavp_call_barring_info( gavp, &tmp_gavp), "Call-Barring-Info AVP retrieved.\n", "Failed to retrieve Call-Barring-Info.\n", return);

	while(((row = mysql_fetch_row(res)) != NULL) && (tmp_gavp)){			
						
		/*get SS-Code*/	
		SS_CHECK( ss_get_ss_code( tmp_gavp, &tmp_str, &len), "SS-Code retrieved.\n", "Failed to retrieve SS-Code.\n");
		/*compare SS-Code value*/
		test_comp_str( tmp_str, (unsigned char *)row[1], len, "SS-Code");

		/*get SS-Status*/	
		SS_CHECK( ss_get_ss_status( tmp_gavp, &tmp_str, &len), "SS-Status retrieved.\n", "Failed to retrieve SS-Status.\n");
		/*compare SS-Status value*/
		test_comp_str( tmp_str, (unsigned char *)row[2], len, "SS-Status");

		/*Get next Call-Barring-Info group AVP*/
		SS_WCHECK( ss_get_gavp_next_call_barring_info( tmp_gavp, &tmp_gavp2), "next Call-Barring-Info AVP retrieved.\n", "Failed to retrieve next Call-Barring-Info.\n", return);
		
		tmp_gavp = tmp_gavp2;
		tmp_gavp2 = NULL;
	}

	mysql_free_result(res);
	mysql_close(conn);
}

/* Set AMBR AVP*/
void test_set_ambr(struct avp **gavp, char * ul, char * dl){
	
	struct avp *tmp_gavp;
	unsigned32 tmp_u;

	if(!gavp)
		return;
	if((!ul) && (!dl))
		return;

	/*Create AMBR AVP*/
	SS_CHECK( ss_create_ambr(&tmp_gavp), "AMBR AVP created.\n", "Failed to create AMBR AVP.\n");

	/* Set Max-Requested-Bandwidth-UL */
	if(ul)
		SS_SET_U32( ss_set_max_requested_bandwidth_ul( &tmp_gavp, tmp_u), tmp_u, ul, "Max-Requested-Bandwidth-UL set.\n", "Failed to set Max-Requested-Bandwidth-UL.\n");
		
	/* Set Max-Requested-Bandwidth-DL*/	
	if(dl)
		SS_SET_U32( ss_set_max_requested_bandwidth_dl( &tmp_gavp, tmp_u), tmp_u, dl, "Max-Requested-Bandwidth-DL set.\n", "Failed to set Max-Requested-Bandwidth-DL.\n");

	/*Add AMBR group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "AMBR AVP set.\n", "Failed to add AMBR.\n");
}

/* check AMBR AVP*/
static void check_ambr(struct avp *gavp, char *ul, char *dl){
	
	struct avp *tmp_gavp = NULL;
	unsigned32 tmp_u = 0;

	if((!gavp) || (!ul) || (!dl)) return;
	
	/*Get AMBR AVP*/
	SS_WCHECK( ss_get_gavp_ambr( gavp, &tmp_gavp), "AMBR AVP retrieved.\n", "Failed to retrieve AMBR AVP.\n", return);

	/* Get Max-Requested-Bandwidth-UL */
	SS_CHECK( ss_get_max_requested_bandwidth_ul( tmp_gavp, &tmp_u), "Max-Requested-Bandwidth-UL retrieved.\n", "Failed to retrieve Max-Requested-Bandwidth-UL.\n");
	/*compare Max-Requested-Bandwidth-UL value*/
	test_comp_uint( tmp_u, (uint32_t)(strtoul(ul, NULL, 10)), "Max-Requested-Bandwidth-UL");
		
	/* Get Max-Requested-Bandwidth-DL*/	
	SS_CHECK( ss_get_max_requested_bandwidth_dl( tmp_gavp, &tmp_u), "Max-Requested-Bandwidth-DL retrieved.\n", "Failed to retrieve Max-Requested-Bandwidth-DL.\n");
	/*compare Max-Requested-Bandwidth-DL value*/
	test_comp_uint( tmp_u, (uint32_t)(strtoul(dl, NULL, 10)), "Max-Requested-Bandwidth-DL");
}

/* Set Allocation-Retention-Priority */
static void set_alloc_retention_prio(struct avp **gavp, char * level, char * capab, char * vulner){

	struct avp * tmp_gavp;
	unsigned32 tmp_u;
	integer32 tmp_i;
	
	if(!gavp)
		return;
	if((!level) && (!capab) && (!vulner))
		return;

	/* Create Allocation-Retention-Priority*/
	SS_CHECK( ss_create_allocation_retention_priority(&tmp_gavp), " Allocation-Retention-Priority AVP created.\n", "Failed to create Allocation-Retention-Priority.\n");

	/* Set Priority-Level */
	if(level)
		SS_SET_U32( ss_set_priority_level( &tmp_gavp, tmp_u), tmp_u, level, "Priority-Level set.\n", "Failed to set Priority-Level.\n");
		
	/* Set Pre-emption-Capability*/
	if(capab)
		SS_SET_I32( ss_set_pre_emption_capability( &tmp_gavp, tmp_i), tmp_i, capab, "Pre-emption-Capability set.\n", "Failed to set Pre-emption-Capability.\n");
		
	/* Set Pre-emption-Vulnerability*/
	if(vulner)
		SS_SET_I32( ss_set_pre_emption_vulnerability( &tmp_gavp, tmp_i), tmp_i, vulner, "Pre-emption-Vulnerability set.\n", "Failed to set Pre-emption-Vulnerability.\n");
		
	/*Add Allocation-Retention-Priority group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "Allocation-Retention-Priority AVP added.\n", "Failed to add Allocation-Retention-Priority.\n");
}

/* Set Allocation-Retention-Priority */
static void check_alloc_retention_prio(struct avp *gavp, uint32_t prio_lev, int32_t pre_emp_cp, int32_t pre_emp_vul){

	struct avp *tmp_gavp = NULL;
	unsigned32 tmp_u;
	integer32 tmp_i;
	
	if(!gavp) return;
		
	/* get Allocation-Retention-Priority*/
	SS_CHECK( ss_get_gavp_allocation_retention_priority(gavp, &tmp_gavp), " Allocation-Retention-Priority AVP retrieved.\n", "Failed to retrieve Allocation-Retention-Priority.\n");

	/* get Priority-Level */
	SS_CHECK( ss_get_priority_level( tmp_gavp, &tmp_u), "Priority-Level retrieved.\n", "Failed to retrieve Priority-Level.\n");
	/*compare Priority-Level value*/
	test_comp_uint( tmp_u, prio_lev, "Priority-Level");
		
	/* get Pre-emption-Capability*/
	SS_WCHECK( ss_get_pre_emption_capability( tmp_gavp, &tmp_i), "Pre-emption-Capability retrieved.\n", "Failed to retrieve Pre-emption-Capability.\n", NULL);
	/*compare Pre-emption-Capability value*/
	test_comp_int( tmp_i, pre_emp_cp, "Pre-emption-Capability");
		
	/* get Pre-emption-Vulnerability*/
	SS_WCHECK( ss_get_pre_emption_vulnerability( tmp_gavp, &tmp_i), "Pre-emption-Vulnerability retrieved.\n", "Failed to retrieve Pre-emption-Vulnerability.\n", NULL);
	/*compare Pre-emption-Vulnerability value*/
	test_comp_int( tmp_i, pre_emp_vul, "Pre-emption-Vulnerability");	
}

/* Set eps_qos_prof: EPS-Subscribed-QoS-Profile */
void test_set_eps_subsc_qos_prof(struct avp **gavp, char * qos, char * level, char * capab, char * vulner){

	struct avp * tmp_gavp;
	integer32 tmp_i;

	if(!gavp)
		return;
	if((!qos) && (!level) && (!capab) && (!vulner))
		return;

	/*Create EPS-Subscribed-QoS-Profile group AVP*/
	SS_CHECK( ss_create_eps_subscribed_qos_profile(&tmp_gavp), "EPS-Subscribed-QoS-Profile AVP created.\n", "Failed to create EPS-Subscribed-QoS-Profile.\n");

	/* Set QoS-Class-Identifier*/
	if(qos)
		SS_SET_I32( ss_set_qos_class_identifier( &tmp_gavp, tmp_i), tmp_i, qos, "QoS-Class-Identifier set.\n", "Failed to set QoS-Class-Identifier.\n");
	
	/* Set Allocation-Retention-Priority */
	set_alloc_retention_prio( &tmp_gavp, level, capab, vulner);		
	
	/*Add EPS-Subscribed-QoS-Profile group AVP into the group AVP provided in parameter 'gavp'*/			
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "EPS-Subscribed-QoS-Profile set.\n", "Failed to add EPS-Subscribed-QoS-Profile.\n");	
}

/* check eps_qos_prof: EPS-Subscribed-QoS-Profile */
static void check_eps_subsc_qos_prof(struct avp *avp, int32_t qos_cls_id, uint32_t prio_lev, int32_t pre_emp_cp, int32_t pre_emp_vul){

	struct avp *tmp_gavp = NULL;
	integer32 tmp_i;

	if(!avp) return;
	
	/*Get EPS-Subscribed-QoS-Profile group AVP*/
	SS_WCHECK( ss_get_gavp_eps_subscribed_qos_profile(avp, &tmp_gavp), "EPS-Subscribed-QoS-Profile AVP retrieved.\n", "Failed to retrieve EPS-Subscribed-QoS-Profile.\n", return);

	/* get QoS-Class-Identifier*/
	SS_CHECK( ss_get_qos_class_identifier( tmp_gavp, &tmp_i), "QoS-Class-Identifier retrieved.\n", "Failed to retrieve QoS-Class-Identifier.\n");
	/*compare QoS-Class-Identifier value*/
	test_comp_int( tmp_i, qos_cls_id, "QoS-Class-Identifier");
	
	/* check Allocation-Retention-Priority */
	check_alloc_retention_prio( tmp_gavp, prio_lev, pre_emp_cp, pre_emp_vul);			
}

/* Set WLAN-offloadability*/
static void set_wlan_offload(struct avp **gavp, char * eutran, char * utran){
							
	struct avp * tmp_gavp;
	unsigned32 tmp_u;

	if(!gavp)return;

	if((!eutran) && (!utran)) return;		
	
	/*Create WLAN-offloadability AVP*/
	SS_CHECK( ss_create_wlan_offloadability( &tmp_gavp), "WLAN-offloadability AVP created.\n", "Failed to create WLAN-offloadability.\n");

	/* Set WLAN-offloadability-EUTRAN */
	if(eutran)
		SS_SET_U32( ss_set_wlan_offloadability_eutran( &tmp_gavp, tmp_u), tmp_u, eutran, "WLAN-offloadability-EUTRAN set.\n", "Failed to set WLAN-offloadability-EUTRAN.\n");	
	
	/* Set WLAN-offloadability-UTRAN */	
	if(utran)
		SS_SET_U32( ss_set_wlan_offloadability_utran( &tmp_gavp, tmp_u), tmp_u, utran, "WLAN-offloadability-UTRAN set.\n", "Failed to set WLAN-offloadability-UTRAN.\n");		
		
	/*Add WLAN-offloadability group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "WLAN-offloadability AVP added.\n", "Failed to add WLAN-offloadability.\n");
}

/* check WLAN-offloadability*/
static void check_wlan_offload(struct avp *avp, uint32_t eutran, uint32_t utran){
							
	struct avp *tmp_gavp = NULL;
	unsigned32 tmp_u;

	if(!avp) return;
		
	/*get WLAN-offloadability AVP*/
	SS_WCHECK( ss_get_gavp_wlan_offloadability( avp, &tmp_gavp), "WLAN-offloadability AVP retrieved.\n", "Failed to retrieve WLAN-offloadability.\n", return);

	/* get WLAN-offloadability-EUTRAN */
	SS_WCHECK( ss_get_wlan_offloadability_eutran( tmp_gavp, &tmp_u), "WLAN-offloadability-EUTRAN retrieved.\n", "Failed to retrieve WLAN-offloadability-EUTRAN.\n", NULL);
	/*compare WLAN-offloadability-EUTRAN values*/
	test_comp_uint( tmp_u, eutran, "WLAN-offloadability-EUTRAN");	
	
	/* get WLAN-offloadability-UTRAN */	
	SS_WCHECK( ss_get_wlan_offloadability_utran( tmp_gavp, &tmp_u), "WLAN-offloadability-UTRAN retrieved.\n", "Failed to retrieve WLAN-offloadability-UTRAN.\n", return);	
	/*compare WLAN-offloadability-UTRAN values*/
	test_comp_uint( tmp_u, utran, "WLAN-offloadability-UTRAN");	
	
}



/*Set Specific-APN-Info group AVP (only 3 AVPs for testing) and its child AVPs*/
void test_set_spec_apn_info(struct avp **gavp, utf8string *serv_sel, address *ipv4, address *ipv6, diameterid *host, diameterid *realm, octetstring *vis_net_id){

	struct avp * tmp_gavp = NULL;

	if((!gavp) || (!serv_sel)) return;

	if((!ipv4) && (!ipv6) && (!host) && (!realm)) return;

	/*Create Specific-APN-Info group AVP*/
	SS_CHECK( ss_create_specific_apn_info(&tmp_gavp), "Specific-APN-Info group AVP created.\n", "Failed to create Specific-APN-Info AVP\n");
	
	/*Set Service-Selection AVP*/
	SS_CHECK( ss_set_service_selection( (avp_or_msg **)&tmp_gavp, serv_sel, strlen((char *)serv_sel)), "Service-Selection AVP set in Specific-APN-Info AVP.\n","Failed to set Service-Selection AVP in Specific-APN-Info AVP\n");

	/*Add MIP6-Agent-Info group AVP in to Specific-APN-Info*/ 	
	test_set_mip6( (avp_or_msg **)&tmp_gavp, ipv4, ipv6, (char *)host, (char *)realm);

	/*Set Visited-Network-Identifier AVP*/	
	SS_CHECK( ss_set_visited_network_identifier( (avp_or_msg **)&tmp_gavp, vis_net_id, strlen((char *) vis_net_id)), "Visited-Network-Identifier AVP set in Specific-APN-Info.\n","Failed to set Visited-Network-Identifier AVP in Specific-APN-Info.\n");

	/*Add Specific-APN-Info AVP*/ 	
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "Specific-APN-Info AVP added.\n", "Failed to add Specific-APN-Info AVP.\n");
}

/*Set APN-Configuration-Profile */
void test_set_apn_conf_prof(struct avp **gavp, char * imsi, char * context_id){

	struct avp * tmp_gavp;	
	struct avp * tmp_gavp2;	
	unsigned32 tmp_u;
	integer32 tmp_i;
	char buf[60] = {0};
	int i = 0;

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi) || (!context_id)) return;
	
	/*Create APN-Configuration-Profile group AVP*/
	SS_CHECK( ss_create_apn_configuration_profile( &tmp_gavp), "APN-Configuration-Profile AVP created.\n", "Failed to create APN-Configuration-Profile.\n");

	/*Set Context-Identifier*/
	SS_SET_U32( ss_set_context_identifier( (avp_or_msg **)&tmp_gavp, tmp_u), tmp_u, context_id, "Context-Identifier set.\n", "Failed to set Context-Identifier.\n");
	
	/*Set All-APN-Configurations-Included-Indicator */
	SS_CHECK( ss_set_all_apn_configuration_included_indicator( &tmp_gavp, (int)gb_all_apn_conf_included_indicator), "All-APN-Configurations-Included-Indicator set.\n", "Failed to set All-APN-Configurations-Included-Indicator.\n");

	/******Set APN-Configuration****************************************************/
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get apn configuration data*/	
	sprintf(buf,"select * from apnConf where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "APN config data retrieved from db.\n", "Failed to apn config data from database.\n");

	/*Check if the result is empty*/
	if(mysql_num_rows(res) == 0) return;								
				
	while((row = mysql_fetch_row(res)) != NULL){
		
		/*Create APN-Configuration group AVP*/
		SS_CHECK( ss_create_apn_configuration(&tmp_gavp2), "APN-Configuration AVP created.\n", "Failed to create APN-Configuration.\n");	

		/*Set Context-Identifier*/
		if(row[1])
			SS_SET_U32( ss_set_context_identifier((avp_or_msg **)&tmp_gavp2, tmp_u), tmp_u, row[1], "Context-Identifier set.\n", "Failed to set Context-Identifier.\n");
	
		/* Set Served-Party-IP-Address (IPV4 and IPV6)*/	
		if(row[2])
			SS_CHECK( ss_set_served_party_ip_address(&tmp_gavp2, (address *)row[2], strlen((char *)row[2])), "Served-Party-IP-Address set.\n", "Failed to set Served-Party-IP-Address.\n");
		if(row[3])
			SS_CHECK( ss_set_served_party_ip_address(&tmp_gavp2, (address *)row[3], strlen((char *)row[3])), "Served-Party-IP-Address.\n", "Failed to set Served-Party-IP-Address.\n");					

		/*Set PDN-Type*/
		if(row[4])
			SS_SET_I32( ss_set_pdn_type(&tmp_gavp2, tmp_u), tmp_u, row[4], "PDN-Type set.\n", "Failed to set PDN-Type.\n");

		/* Set Service-Selection*/
		if(row[5])
			SS_CHECK( ss_set_service_selection((avp_or_msg **)&tmp_gavp2, (utf8string *)row[5], strlen((char *)row[5])), "Service-Selection set.\n", "Failed to set Service-Selection.\n");
	
		/*** Set eps_qos_prof: EPS-Subscribed-QoS-Profile **************************/
		test_set_eps_subsc_qos_prof(&tmp_gavp2, row[6], row[7], row[8], row[9]);							
							
		/* Set VPLMN-Dynamic-Address-Allowed*/
		if(row[10])
			SS_SET_I32( ss_set_vplmn_dynamic_address_allowed(&tmp_gavp2, tmp_i), tmp_i, row[10], "VPLMN-Dynamic-Address-Allowed set.\n", "Failed to set VPLMN-Dynamic-Address-Allowed.\n");

		/*** Set MIP6-Agent-Info AVP ******************************************/
		test_set_mip6( (avp_or_msg **)&tmp_gavp2, (address *) row[11], (address *) row[12], row[13], row[14]);
							
		/* Set Visited-Network-Identifier *********************/
		if(row[15])
			SS_CHECK( ss_set_visited_network_identifier( (avp_or_msg **)&tmp_gavp2, (octetstring *)row[15], strlen((char *)row[15])), "Visited-Network-Identifier set.\n", "Failed to set Visited-Network-Identifier.\n");

		/* Set PDN-GW-Allocation-Type */
		if(row[16])
			SS_SET_I32( ss_set_pdn_gw_allocation_type( &tmp_gavp2, tmp_i), tmp_i, row[16], "PDN-GW-Allocation-Type set.\n", "Failed to set PDN-GW-Allocation-Type.\n");
									
		/* Set 3GPP-Charging-Characteristics*/
		if(row[17])
			SS_CHECK( ss_set_3gpp_charging_characteristics( &tmp_gavp2, (utf8string *)row[17], strlen((char *)row[17])), "3GPP-Charging-Characteristics set.\n", "Failed to set 3GPP-Charging-Characteristics.\n");
	
		/* Set AMBR*/
		test_set_ambr( &tmp_gavp2, row[18], row[19]);

		/*Set Specific-APN-Info group AVP (only 3 AVPs for testing) and its child AVPs*/
		for (i = 1 ; i<3 ; i++)		
			test_set_spec_apn_info( &tmp_gavp2, gb_service_selection, gb_home_agent_address_v4, gb_home_agent_address_v6, gb_home_agent_host_host, gb_home_agent_host_realm, gb_visited_network_identifier);

		/* Set APN-OI-Replacement*********/
		if(row[20])
			SS_CHECK( ss_set_apn_oi_replacement(&tmp_gavp2, (utf8string *)row[20], strlen((char *)row[20])), "APN-OI-Replacement set.\n", "Failed to set APN-OI-Replacement.\n");

		/* Set SIPTO-Permission*/
		if(row[21])
			SS_SET_I32( ss_set_sipto_permission(&tmp_gavp2, tmp_i), tmp_i, row[21], "SIPTO-Permission set.\n", "Failed to set SIPTO-Permission.\n");
	
		/* Set LIPA-Permission*/
		if(row[22])
			SS_SET_I32( ss_set_lipa_permission(&tmp_gavp2, tmp_i), tmp_i, row[22], "LIPA-Permission set.\n", "Failed to set LIPA-Permission.\n");

		/* Set Restoration-Priority*/
		if(row[23])
			SS_SET_U32( ss_set_restoration_priority(&tmp_gavp2, tmp_u), tmp_u, row[23], "Restoration-Priority set.\n", "Failed to set Restoration-Priority.\n");
	
		/* Set SIPTO-Local-Network-Permission*/
		if(row[24])
			SS_SET_I32( ss_set_sipto_local_network_permission(&tmp_gavp2, tmp_i), tmp_i, row[24], "SIPTO-Local-Network-Permission set.\n", "Failed to set SIPTO-Local-Network-Permission.\n");

		/* Set WLAN-offloadability*/
		set_wlan_offload( &tmp_gavp2, row[25], row[26]);
								
		/*Add APN-Configuration into APN-Configuration-Profile*/
		SS_CHECK( ss_add_avp( (avp_or_msg **)&tmp_gavp, tmp_gavp2), "APN-Configuration added.\n", "Failed to add APN-Configuration.\n");			
	}
	
	mysql_free_result(res);
	mysql_close(conn);

	/*Add APN-Configuration-Profile group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "APN-Configuration-Profile added.\n", "Failed to add APN-Configuration-Profile.\n");		
}

/*get Served-Party-IP-Address*/
static void get_serv_party(struct avp *gavp, unsigned char **ipv4, unsigned char **ipv6){

	unsigned char **tmp_str_arr = NULL;
	size_t *len_arr = NULL;
	size_t size = 0;

	if((!gavp)) return;

	if((!ipv4) && (!ipv6)) return;

	/*Get Served-Party-IP-Address values*/
	SS_CHECK( ss_get_served_party_ip_address_gavp_array(gavp, &tmp_str_arr, &len_arr, &size), "Served-Party-IP-Address retrieved.\n", "Failed to retrieve Served-Party-IP-Address.\n");
	while(size){
	
		if((4 == len_arr[size-1]) && (ipv4)) *ipv4 = tmp_str_arr[size-1];

		else if((6 == len_arr[size-1]) && (ipv6)) *ipv6 = tmp_str_arr[size-1];

		size--;
	}

	if(tmp_str_arr) free(tmp_str_arr);
	if(len_arr) free(len_arr);
}

/*Check Served-Party-IP-Address*/
static void check_serv_party(struct avp *gavp, unsigned char *addr_ipv4, unsigned char *addr_ipv6){

	unsigned char *ipv4 = NULL;
	unsigned char *ipv6 = NULL;

	if(!gavp) return;

	if((!addr_ipv4) || (!addr_ipv6)) return;

	/*Get IPV4 and IPV6 values*/
	get_serv_party(gavp, &ipv4, &ipv6);

	/*compare IPV4 address*/
	if(ipv4 && addr_ipv4) test_comp_str( ipv4, addr_ipv4, 4, "Served-Party-IP-Address IPV4");

	/*compare IPV6 address*/
	if(ipv6 && addr_ipv6) test_comp_str( ipv6, addr_ipv6, 16, "Served-Party-IP-Address IPV6");
}

/*check APN-Configuration-Profile */
static void check_apn_conf_prof(struct avp *gavp, char * imsi, char * context_id){

	struct avp *tmp_gavp = NULL;	
	struct avp *tmp_gavp2 = NULL;	
	struct avp *tmp_gavp3 = NULL;	
	unsigned32 tmp_u;
	integer32 tmp_i;
	octetstring *tmp_str = NULL;
	size_t len = 0;
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi) || (!context_id)) return;

	/*Get APN-Configuration-Profile group AVP*/
	SS_WCHECK( ss_get_gavp_apn_configuration_profile( gavp, &tmp_gavp), "APN-Configuration-Profile AVP retrieved.\n", "Failed to retrieve APN-Configuration-Profile.\n", return);	

	/*Get Context-Identifier*/
	SS_CHECK( ss_get_context_identifier( tmp_gavp, &tmp_u), "Context-Identifier retrieved.\n", "Failed to retrieve Context-Identifier.\n");
	/*compare Context-Identifier value*/
	test_comp_uint( tmp_u, (uint32_t)(strtoul(context_id, NULL, 10)), "Context-Identifier");
	
	/*Get All-APN-Configurations-Included-Indicator */
	SS_CHECK( ss_get_all_apn_configuration_included_indicator( tmp_gavp, &tmp_i), "All-APN-Configurations-Included-Indicator retrieved.\n", "Failed to retrieve All-APN-Configurations-Included-Indicator.\n");
	/*compare All-APN-Configurations-Included-Indicator value*/
	test_comp_int( tmp_i, (uint32_t)gb_all_apn_conf_included_indicator, "All-APN-Configurations-Included-Indicator");

	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get apn configuration data*/	
	sprintf(buf,"select * from apnConf where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "APN config data retrieved from db.\n", "Failed to apn config data from database.\n");

	/*Check if the result is empty*/
	if(mysql_num_rows(res) == 0) return;
	
	/*Get APN-Configuration group AVP*/
	SS_CHECK( ss_get_gavp_apn_configuration(tmp_gavp, &tmp_gavp2), "APN-Configuration AVP retrieved.\n", "Failed to retrieve APN-Configuration.\n");	

	while(((row = mysql_fetch_row(res)) != NULL) && (tmp_gavp2)){

		/*get Context-Identifier*/
		SS_CHECK( ss_get_context_identifier( tmp_gavp2, &tmp_u), "Context-Identifier retrieved.\n", "Failed to retrieve Context-Identifier.\n");
		/*compare Context-Identifier value*/
		test_comp_uint( tmp_u, (uint32_t)(strtoul(row[1], NULL, 10)), "Context-Identifier");
	
		/* chekc Served-Party-IP-Address (IPV4 and IPV6)*/	
		check_serv_party(tmp_gavp2, (unsigned char *)row[2], (unsigned char *)row[3]);
		
		/*get PDN-Type*/
		SS_CHECK( ss_get_pdn_type(tmp_gavp2, &tmp_i), "PDN-Type retrieved.\n", "Failed to retrieve PDN-Type.\n");
		/*compare PDN-Type value*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[4])), "PDN-Type");

		/* get Service-Selection*/
		SS_CHECK( ss_get_service_selection( tmp_gavp2, &tmp_str, &len), "Service-Selection retrieved.\n", "Failed to retrieve Service-Selection.\n");
		/*compare Service-Selection value*/
		test_comp_str( tmp_str, (unsigned char *)row[5], len, "Service-Selection");
	
		/*check eps_qos_prof: EPS-Subscribed-QoS-Profile */
		check_eps_subsc_qos_prof(tmp_gavp2, (int32_t)(atoi(row[6])), (uint32_t)(strtoul(row[7], NULL, 10)), (int32_t)(atoi(row[8])), (int32_t)(atoi(row[9])));							
							
		/* get VPLMN-Dynamic-Address-Allowed*/
		SS_WCHECK( ss_get_vplmn_dynamic_address_allowed(tmp_gavp2, &tmp_i), "VPLMN-Dynamic-Address-Allowed retrieved.\n", "Failed to retrieve VPLMN-Dynamic-Address-Allowed.\n", NULL);
		/*compare VPLMN-Dynamic-Address-Allowed values*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[10])), "VPLMN-Dynamic-Address-Allowed");

		/* check MIP6-Agent-Info AVP */
		test_check_mip6_values( (avp_or_msg *)tmp_gavp2);
							
		/* get Visited-Network-Identifier */
		SS_WCHECK( ss_get_visited_network_identifier( tmp_gavp2, &tmp_str, &len), "Visited-Network-Identifier retrieved.\n", "Failed to retrieve Visited-Network-Identifier.\n", NULL);
		/*compare Visited-Network-Identifier values*/
		test_comp_str( tmp_str, (unsigned char *)row[15], len, "Visited-Network-Identifier");

		/* get PDN-GW-Allocation-Type */
		SS_WCHECK( ss_get_pdn_gw_allocation_type( tmp_gavp2, &tmp_i), "PDN-GW-Allocation-Type retrieveD.\n", "Failed to retrieve PDN-GW-Allocation-Type.\n", NULL);
		/*compare PDN-GW-Allocation-Type values*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[16])), "PDN-GW-Allocation-Type");
									
		/* get 3GPP-Charging-Characteristics*/
		SS_CHECK( ss_get_3gpp_charging_characteristics( tmp_gavp2, &tmp_str, &len), "3GPP-Charging-Characteristics retrieved.\n", "Failed to retrieve 3GPP-Charging-Characteristics.\n");
		/*compare 3GPP-Charging-Characteristics values*/
		test_comp_str( tmp_str, (unsigned char *)row[17], len, "3GPP-Charging-Characteristics");
	
		/* check AMBR*/
		check_ambr( tmp_gavp2, row[18], row[19]);

		/*check Specific-APN-Info*/
		test_check_spec_apn_info( tmp_gavp2);

		/* get APN-OI-Replacement */
		SS_WCHECK( ss_get_apn_oi_replacement(tmp_gavp2, &tmp_str, &len), "APN-OI-Replacement retrieved.\n", "Failed to retrieve APN-OI-Replacement.\n", NULL);
		/*compare APN-OI-Replacement values*/
		test_comp_str( tmp_str, (unsigned char *)row[20], len, "APN-OI-Replacement");

		/* Get SIPTO-Permission*/
		SS_WCHECK( ss_get_sipto_permission(tmp_gavp2, &tmp_i), "SIPTO-Permission retrieved.\n", "Failed to retrieve SIPTO-Permission.\n", NULL);
		/*compare SIPTO-Permission values*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[21])), "SIPTO-Permission");
	
		/* get LIPA-Permission*/
		SS_WCHECK( ss_get_lipa_permission(tmp_gavp2, &tmp_i), "LIPA-Permission retrieved.\n", "Failed to retrieve LIPA-Permission.\n", NULL);
		/*compare LIPA-Permission values*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[22])), "LIPA-Permission");

		/* get Restoration-Priority*/
		SS_WCHECK( ss_get_restoration_priority(tmp_gavp2, &tmp_u), "Restoration-Priority retrieved.\n", "Failed to retrieve Restoration-Priority.\n", NULL);
		/*compare Restoration-Priority values*/
		test_comp_uint( tmp_u, (uint32_t)(strtoul(row[23], NULL, 10)), "Restoration-Priority");
	
		/* get SIPTO-Local-Network-Permission*/
		SS_WCHECK( ss_get_sipto_local_network_permission(tmp_gavp2, &tmp_i), "SIPTO-Local-Network-Permission retrieved.\n", "Failed to retrieve SIPTO-Local-Network-Permission.\n", NULL);
		/*compare SIPTO-Local-Network-Permission values*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[24])), "SIPTO-Local-Network-Permission");

		/* check WLAN-offloadability*/
		check_wlan_offload( tmp_gavp2, (uint32_t)(strtoul( row[25], NULL, 10)), (uint32_t)(strtoul( row[26], NULL, 10)));								
		
		/*Get next APN-Configuration group AVP*/
		SS_WCHECK( ss_get_gavp_next_apn_configuration(tmp_gavp2, &tmp_gavp3), "Next APN-Configuration AVP retrieved.\n", "Failed to retrieve next APN-Configuration.\n", return);

		tmp_gavp2 = tmp_gavp3;
		tmp_gavp3 = NULL;
	}

	mysql_free_result(res);
	mysql_close(conn);
}

/*Set Area-Scope AVP*/
static void set_area_scope(struct avp **gavp, const char * imsi){

	struct avp * tmp_gavp;
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi))
		return;

	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get area scope data*/	
	sprintf(buf,"select * from areaScope where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "area scope data retrieved from db.\n", "Failed to store area scope data from database.\n");	

	/*Create Area-Scope AVP*/
	if(mysql_num_rows(res) != 0)
		SS_CHECK( ss_create_area_scope(&tmp_gavp), "Area-Scope AVP created.\n", "Failed to create Area-Scope.\n");

	/*Fetch row from mysql result for Area-Scope data */			
	while((row = mysql_fetch_row(res)) != NULL){
	
		/* Set Cell-Global-Identity*/
		if(row[1])
			SS_CHECK( ss_set_cell_global_identity( &tmp_gavp, (octetstring *)row[1], strlen((char *)row[1])), "Cell-Global-Identity set.\n", "Failed to set Cell-Global-Identity.\n");

		/* Set E-UTRAN-Cell-Global-Identity*/
		if(row[2])
			SS_CHECK( ss_set_e_utran_cell_global_identity( &tmp_gavp, (octetstring *)row[2], strlen((char *)row[2])), "E-UTRAN-Cell-Global-Identity set.\n", "Failed to set E-UTRAN-Cell-Global-Identity.\n");

		/* Set Routing-Area-Identity*/
		if(row[3])
			SS_CHECK( ss_set_routing_area_identity( &tmp_gavp, (octetstring *)row[3], strlen((char *)row[3])), "Routing-Area-Identity set.\n", "Failed to set Routing-Area-Identity.\n");

		/* Set Location-Area-Identity*/
		if(row[4])
			SS_CHECK( ss_set_location_area_identity( &tmp_gavp, (octetstring *)row[4], strlen((char *)row[4])), "Location-Area-Identity set.\n", "Failed to set Location-Area-Identity.\n");

		/* Set Tracking-Area-Identity*/
		if(row[5])
			SS_CHECK( ss_set_tracking_area_identity( &tmp_gavp, (octetstring *)row[5], strlen((char *)row[5])), "Tracking-Area-Identity set.\n", "Failed to set Tracking-Area-Identity.\n");	
	}
		
	/*Add Area-Scope group AVP into the group AVP provided in parameter 'gavp'*/
	if(tmp_gavp)
		SS_CHECK( ss_add_avp(  (avp_or_msg **)gavp, tmp_gavp), "Area-Scope AVP added.\n", "Failed to add Area-Scope group AVP.\n");

	mysql_free_result(res);
	mysql_close(conn);
}

/*check Area-Scope AVP*/
static void check_area_scope(struct avp *gavp, char *imsi){

	struct avp *tmp_gavp = NULL;
	octetstring **cgi_arr = NULL;
	octetstring **ecgi_arr = NULL;
	octetstring **rai_arr = NULL;
	octetstring **lai_arr = NULL;
	octetstring **tai_arr = NULL;
	size_t cgi_size = 0;
	size_t ecgi_size = 0;
	size_t rai_size = 0;
	size_t lai_size = 0;
	size_t tai_size = 0;
	size_t *cgi_len = NULL;
	size_t *ecgi_len = NULL;
	size_t *rai_len = NULL;
	size_t *lai_len = NULL;
	size_t *tai_len = NULL;
	size_t tmp_cgi_size = 0;
	size_t tmp_ecgi_size = 0;
	size_t tmp_rai_size = 0;
	size_t tmp_lai_size = 0;
	size_t tmp_tai_size = 0;
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi)) return;

	/*Get Area-Scope AVP*/
	SS_WCHECK( ss_get_gavp_area_scope(gavp, &tmp_gavp), "Area-Scope AVP retrieved.\n", "Failed to retrieve Area-Scope.\n", return);

	/* Get Cell-Global-Identity*/
	SS_WCHECK( ss_get_cell_global_identity_gavp_array( tmp_gavp, &cgi_arr, &cgi_len, &cgi_size), "Cell-Global-Identity retrieved.\n", "Failed to retrieve Cell-Global-Identity.\n", NULL);

	/* Get E-UTRAN-Cell-Global-Identity*/
	SS_WCHECK( ss_get_e_utran_cell_global_identity_gavp_array( tmp_gavp, &ecgi_arr, &ecgi_len, &ecgi_size), "E-UTRAN-Cell-Global-Identity retrieved.\n", "Failed to retrieve E-UTRAN-Cell-Global-Identity.\n", NULL);
	
	/* Get Routing-Area-Identity*/
	SS_WCHECK( ss_get_routing_area_identity_gavp_array( tmp_gavp, &rai_arr, &rai_len, &rai_size), "Routing-Area-Identity retrieved.\n", "Failed to retrieve Routing-Area-Identity.\n", NULL);

	/* Get Location-Area-Identity*/
	SS_WCHECK( ss_get_location_area_identity_gavp_array( tmp_gavp, &lai_arr, &lai_len, &lai_size), "Location-Area-Identity retrieved.\n", "Failed to retrieve Location-Area-Identity.\n", NULL);

	/* Get Tracking-Area-Identity*/
	SS_WCHECK( ss_get_tracking_area_identity_gavp_array( tmp_gavp, &tai_arr, &tai_len, &tai_size), "Tracking-Area-Identity retrieved.\n", "Failed to retrieve Tracking-Area-Identity.\n", return);

	tmp_cgi_size = cgi_size;
	tmp_ecgi_size = ecgi_size;
	tmp_rai_size = rai_size;
	tmp_lai_size = lai_size;
	tmp_tai_size = tai_size;

	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get area scope data*/	
	sprintf(buf,"select * from areaScope where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "area scope data retrieved from db.\n", "Failed to store area scope data from database.\n");	

	/*Fetch row from mysql result for Area-Scope data */			
	while((row = mysql_fetch_row(res)) != NULL){

		/* compare Cell-Global-Identity value*/
		if(cgi_size){

			test_comp_str( cgi_arr[cgi_size-tmp_cgi_size], (unsigned char *)row[1], cgi_len[cgi_size-tmp_cgi_size], "Cell-Global-Identity");

			tmp_cgi_size--;
		}
		/* compare E-UTRAN-Cell-Global-Identity value*/
		if(ecgi_size){

			test_comp_str( ecgi_arr[ecgi_size-tmp_ecgi_size], (unsigned char *)row[2], ecgi_len[ecgi_size-tmp_ecgi_size], "E-UTRAN-Cell-Global-Identity");

			tmp_ecgi_size--;
		}	
		/* compare Routing-Area-Identity value*/
		if(rai_size){

			test_comp_str( rai_arr[rai_size-tmp_rai_size], (unsigned char *)row[3], rai_len[rai_size-tmp_rai_size], "Routing-Area-Identity");

			tmp_rai_size--;
		}
		/* compare Location-Area-Identity value*/
		if(lai_size){

			test_comp_str( lai_arr[lai_size-tmp_lai_size], (unsigned char *)row[4], lai_len[lai_size-tmp_lai_size], "Location-Area-Identity");

			tmp_lai_size--;
		}
		/* compare Tracking-Area-Identity value*/
		if(tai_size){

			test_comp_str( tai_arr[tai_size-tmp_tai_size], (unsigned char *)row[5], tai_len[tai_size-tmp_tai_size], "Cell-Global-Identity");

			tmp_tai_size--;
		}
	}

	/* free Cell-Global-Identity*/
	if(cgi_arr) free(cgi_arr);
	if(cgi_len) free(cgi_len);

	/* free E-UTRAN-Cell-Global-Identity*/
	if(ecgi_arr) free(ecgi_arr);
	if(ecgi_len) free(ecgi_len);

	/* free Routing-Area-Identity*/
	if(rai_arr) free(rai_arr);
	if(rai_len) free(rai_len);

	/* free Location-Area-Identity*/
	if(lai_arr) free(lai_arr);
	if(lai_len) free(lai_len);

	/* free Tracking-Area-Identity*/	
	if(tai_arr) free(tai_arr);	
	if(tai_len) free(tai_len);
}

/* Set Trace-Data group AVP*/
static void set_trace_data(struct avp **gavp, const char * imsi){	

	struct avp * tmp_gavp;
	struct avp * tmp_gavp2;
	unsigned32 tmp_u;
	integer32 tmp_i;
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi)) return;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get trace data*/	
	sprintf(buf,"select * from traceData where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "Trace data retrieved from db.\n", "Failed to retrieve trace data from database.\n");
	
	/*if database query return empty set*/
	if((row = mysql_fetch_row(res)) == NULL) return;
		
	/*Create Trace-Data group AVP*/	
	SS_CHECK( ss_create_trace_data( &tmp_gavp), "Trace-Data AVP created.\n", "Failed to create Trace-Data group AVP.\n");
		
	/* Set Trace-Reference*/
	if(row[1])
		SS_CHECK( ss_set_trace_reference( (avp_or_msg **)&tmp_gavp, (octetstring *)row[1], strlen((char *)row[1])), "Trace-Reference set.\n", "Failed to set Trace-Reference.\n");
	
	/* Set Trace-Depth*/
	if(row[2])
		SS_SET_I32( ss_set_trace_depth( &tmp_gavp, tmp_u), tmp_u, row[2], "Trace-Depth set.\n", "Failed to set Trace-Depth.\n");
	
	/* Set Trace-NE-Type-List*/
	if(row[3])
		SS_CHECK( ss_set_trace_ne_type_list( &tmp_gavp, (octetstring *)row[3], strlen((char *)row[3])), "Trace-NE-Type-List set.\n", "Failed to set Trace-NE-Type-List.\n");
		
	/* Set Trace-Interface-List*/
	if(row[4])
		SS_CHECK( ss_set_trace_interface_list( &tmp_gavp, (octetstring *)row[4], strlen((char *)row[4])), "Trace-Interface-List set.\n", "Failed to set Trace-Interface-List.\n");
	
	/* Set Trace-Event-List*/
	if(row[5])
		SS_CHECK( ss_set_trace_event_list( &tmp_gavp, (octetstring *)row[5], strlen((char *)row[5])), "Trace-Event-List set.\n", "Failed to set Trace-Event-List.\n");
	
	/* Set OMC-Id*/
	if(row[6])
		SS_CHECK( ss_set_omc_id( &tmp_gavp, (octetstring *)row[6], strlen((char *)row[6])), "OMC-Id set.\n", "Failed to set OMC-Id.\n");
		
	/* Set Trace-Collection-Entity*/
	if(row[7])
		SS_CHECK( ss_set_trace_collection_entity( &tmp_gavp, (address *)row[7], strlen((char *)row[7])), "Trace-Collection-Entity set.\n", "Failed to set Trace-Collection-Entity.\n");
	
	/*** Set MDT-Configuration group AVP  ***/
	SS_CHECK( ss_create_mdt_configuration(&tmp_gavp2), "MDT-Configuration set.\n", "Failed to create MDT-Configuration.\n");	

	/** Set Job-Type **/
	if(row[8])
		SS_SET_I32( ss_set_job_type(&tmp_gavp2, tmp_i), tmp_i, row[8], "Job-Type set.\n", "Failed to set Job-Type.\n");	

	/* Set Area-Scope group AVP*/
	set_area_scope(&tmp_gavp2, imsi);	
		
	/* Set List-Of-Measurements */		
	if(row[9])
		SS_SET_U32( ss_set_list_of_measurements( &tmp_gavp2, tmp_u), tmp_u, row[9], "List-Of-Measurements set.\n", "Failed to set List-Of-Measurements.\n");

	/* Set Reporting-Trigger */		
	if(row[10])
		SS_SET_U32( ss_set_reporting_trigger( &tmp_gavp2, tmp_u), tmp_u, row[10], "Reporting-Trigger set.\n", "Failed to set Reporting-Trigger.\n");

	/* Set Report-Interval */		
	if(row[11])
		SS_SET_I32( ss_set_report_interval( &tmp_gavp2, tmp_i), tmp_i, row[11], "Report-Interval set.\n", "Failed to set Report-Interval.\n");

	/* Set Report-Amount */		
	if(row[12])
		SS_SET_I32( ss_set_report_amount( &tmp_gavp2, tmp_i), tmp_i, row[12], "Report-Amount set.\n", "Failed to set Report-Amount.\n");
	
	/* Set Event-Threshold-RSRP */		
	if(row[13])
		SS_SET_U32( ss_set_event_threshold_rsrp( &tmp_gavp2, tmp_u), tmp_u, row[13], "Event-Threshold-RSRP set.\n", "Failed to set Event-Threshold-RSRP.\n");

	/* Set Event-Threshold-RSRQ */		
	if(row[14])
		SS_SET_U32( ss_set_event_threshold_rsrq( &tmp_gavp2, tmp_u), tmp_u, row[14], "Event-Threshold-RSRQ set.\n", "Failed to set Event-Threshold-RSRQ.\n");

	/* Set Logging-Interval*/	
	if(row[15])
		SS_SET_I32( ss_set_logging_interval( &tmp_gavp2, tmp_i), tmp_i, row[15], "Logging-Interval set.\n", "Failed to set Logging-Interval.\n");

	/* Set Logging-Duration */		
	if(row[16])
		SS_SET_I32( ss_set_logging_duration( &tmp_gavp2, tmp_i), tmp_i, row[16], "Logging-Duration set.\n", "Failed to set Logging-Duration.\n");

	/* Set Measurement-Period-LTE*/	
	if(row[17])
		SS_SET_I32( ss_set_measurement_period_lte( &tmp_gavp2, tmp_i), tmp_i, row[17], "Measurement-Period-LTE set.\n", "Failed to set Measurement-Period-LTE.\n");

	/* Set Measurement-Period-UMTS*/		
	if(row[18])
		SS_SET_I32( ss_set_measurement_period_umts( &tmp_gavp2, tmp_i), tmp_i, row[18], "Measurement-Period-UMTS set.\n", "Failed to set Measurement-Period-UMTS.\n");

	/* Set Collection-Period-RMM-LTE*/	
	if(row[19])
		SS_SET_I32( ss_set_collection_period_rmm_lte( &tmp_gavp2, tmp_i), tmp_i, row[19], "Collection-Period-RMM-LTE set.\n", "Failed to set Collection-Period-RMM-LTE.\n");

	/* Set Collection-Period-RRM-UMTS*/		
	if(row[20])
		SS_SET_I32( ss_set_collection_period_rmm_umts( &tmp_gavp2, tmp_i), tmp_i, row[20], "Collection-Period-RMM-UMTS set.\n", "Failed to set Collection-Period-RMM-UMTS.\n");

	/* Set Positioning-Method*/		
	if(row[21])
		SS_CHECK( ss_set_positioning_method( &tmp_gavp2, (octetstring *)row[21], strlen((char *)row[21])), "Positioning-Method set.\n", "Failed to set Positioning-Method.\n");

	/* Set Measurement-Quantity*/		
	if(row[22])
		SS_CHECK( ss_set_measurement_quantity( &tmp_gavp2, (octetstring *)row[22], strlen((char *)row[22])), "Measurement-Quantity set.\n", "Failed to set Measurement-Quantity.\n");

	/* Set Event-Threshold-Event-1F*/		
	if(row[23])
		SS_SET_I32( ss_set_event_threshold_event_1f( &tmp_gavp2, tmp_i), tmp_i, row[23], "Event-Threshold-Event-1F set.\n", "Failed to set Event-Threshold-Event-1F.\n");

	/* Set Event-Threshold-Event-1I*/		
	if(row[24])
		SS_SET_I32( ss_set_event_threshold_event_1i( &tmp_gavp2, tmp_i), tmp_i, row[24], "Event-Threshold-Event-1I set.\n", "Failed to set Event-Threshold-Event-1I.\n");

	/* Set MDT-Allowed-PLMN-Id (only 3 AVPs set for testing)*/
	if(row[25])
		SS_CHECK( ss_set_mdt_allowed_plmn_id(&tmp_gavp2, (octetstring *)row[25], strlen((char *)row[25])), "MDT-Allowed-PLMN-Id set.\n", "Failed to set MDT-Allowed-PLMN-Id.\n");
	if(row[26])
		SS_CHECK( ss_set_mdt_allowed_plmn_id(&tmp_gavp2, (octetstring *)row[26], strlen((char *)row[26])), "MDT-Allowed-PLMN-Id 2 set.\n", "Failed to set MDT-Allowed-PLMN-Id 2.\n");
	if(row[27])
		SS_CHECK( ss_set_mdt_allowed_plmn_id(&tmp_gavp2, (octetstring *)row[27], strlen((char *)row[27])), "MDT-Allowed-PLMN-Id 3 set.\n", "Failed to set MDT-Allowed-PLMN-Id.\n");	
	
	mysql_free_result(res);

	/*Add MDT-Configuration into Trace-Data*/
	SS_CHECK( ss_add_avp(  (avp_or_msg **)&tmp_gavp, tmp_gavp2), "MDT-Configuration AVP added.\n", "Failed to add MDT-Configuration.\n");
	
	/*Add Trace-Data group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp(  (avp_or_msg **)gavp, tmp_gavp), "Trace-Data AVP added.\n", "Failed to add Trace-Data.\n");

}

/* check Trace-Data group AVP*/
static void check_trace_data(struct avp *gavp, char *imsi){	

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	unsigned32 tmp_u;
	integer32 tmp_i;
	octetstring *tmp_str = NULL;
	octetstring **tmp_str_arr = NULL;
	size_t size = 0;
	size_t len = 0;
	size_t *len_arr = NULL;
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi)) return;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get trace data*/	
	sprintf(buf,"select * from traceData where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "Trace data retrieved from db.\n", "Failed to retrieve trace data from database.\n");
	
	/*if database query return empty set*/
	if((row = mysql_fetch_row(res)) == NULL) return;

	/*Get Trace-Data group AVP*/	
	SS_WCHECK( ss_get_gavp_trace_data( gavp, &tmp_gavp), "Trace-Data AVP retrieved.\n", "Failed to retrieve Trace-Data group AVP.\n", return);
		
	/* Get Trace-Reference*/
	SS_CHECK( ss_get_trace_reference( tmp_gavp, &tmp_str, &len), "Trace-Reference retrieved.\n", "Failed to retrieve Trace-Reference.\n");
	/*compare Trace-Reference values*/
	test_comp_str( tmp_str, (unsigned char *)row[1], len, "Trace-Reference");
	
	/* Get Trace-Depth*/
	SS_CHECK( ss_get_trace_depth( tmp_gavp, &tmp_i), "Trace-Depth retrieved.\n", "Failed to retrieve Trace-Depth.\n");
	/*compare Trace-Depth value*/
	test_comp_int( tmp_i, (int32_t)(atoi(row[2])), "Trace-Depth");
	
	/* Get Trace-NE-Type-List*/
	SS_CHECK( ss_get_trace_ne_type_list( tmp_gavp, &tmp_str, &len), "Trace-NE-Type-List retrieved.\n", "Failed to retrieve Trace-NE-Type-List.\n");
	/*compare Trace-NE-Type-List values*/
	test_comp_str( tmp_str, (unsigned char *)row[3], len, "Trace-NE-Type-List");
		
	/* Get Trace-Interface-List*/
	SS_WCHECK( ss_get_trace_interface_list( tmp_gavp, &tmp_str, &len), "Trace-Interface-List retrieved.\n", "Failed to retrieve Trace-Interface-List.\n", NULL);
	/*compare Trace-Interface-List values*/
	test_comp_str( tmp_str, (unsigned char *)row[4], len, "Trace-Interface-List");	

	/* Get Trace-Event-List*/
	SS_CHECK( ss_get_trace_event_list( tmp_gavp, &tmp_str, &len), "Trace-Event-List retrieved.\n", "Failed to retrieve Trace-Event-List.\n");
	/*compare Trace-Event-List values*/
	test_comp_str( tmp_str, (unsigned char *)row[5], len, "Trace-Event-List");
	
	/* Get OMC-Id*/
	SS_WCHECK( ss_get_omc_id( tmp_gavp, &tmp_str, &len), "OMC-Id retrieved.\n", "Failed to retrieve OMC-Id.\n", NULL);
	/*compare OMC-Id values*/
	test_comp_str( tmp_str, (unsigned char *)row[6], len, "OMC-Id");
		
	/* Get Trace-Collection-Entity*/
	SS_CHECK( ss_get_trace_collection_entity( tmp_gavp, &tmp_str, &len), "Trace-Collection-Entity retrieved.\n", "Failed to retrieve Trace-Collection-Entity.\n");
	/*compare Trace-Collection-Entity values*/
	test_comp_str( tmp_str, (unsigned char *)row[7], len, "Trace-Collection-Entity");
	
	/* Get MDT-Configuration group AVP  ***/
	SS_CHECK( ss_get_gavp_mdt_configuration(tmp_gavp, &tmp_gavp2), "MDT-Configuration retrieved.\n", "Failed to retrieve MDT-Configuration.\n");	

	/* Get Job-Type **/
	SS_CHECK( ss_get_job_type(tmp_gavp2, &tmp_i), "Job-Type retrieved.\n", "Failed to retrieve Job-Type.\n");	
	/*compare Job-Type value*/
	test_comp_int( tmp_i, (int32_t)(atoi(row[8])), "Job-Type");

	/* Get Area-Scope group AVP*/
	check_area_scope(tmp_gavp2, imsi);	
		
	/* Get List-Of-Measurements */		
	SS_WCHECK( ss_get_list_of_measurements( tmp_gavp2, &tmp_u), "List-Of-Measurements retrieved.\n", "Failed to retrieve List-Of-Measurements.\n", NULL);
	/*compare List-Of-Measurements value*/
	test_comp_uint( tmp_u, (uint32_t)(strtoul(row[9], NULL, 10)), "List-Of-Measurements");

	/* Get Reporting-Trigger */		
	SS_WCHECK( ss_get_reporting_trigger( tmp_gavp2, &tmp_u), "Reporting-Trigger retrieved.\n", "Failed to retrieve Reporting-Trigger.\n", NULL);
	/*compare Reporting-Trigger value*/
	test_comp_uint( tmp_u, (uint32_t)(strtoul(row[10], NULL, 10)), "Reporting-Trigger");

	/* Get Report-Interval */		
	SS_WCHECK( ss_get_report_interval( tmp_gavp2, &tmp_i), "Report-Interval retrieved.\n", "Failed to retrieve Report-Interval.\n", NULL);
	/*compare Reporting-Interval value*/
	test_comp_int( tmp_i, (int32_t)(atoi(row[11])), "Reporting-Interval");

	/* Get Report-Amount */		
	SS_WCHECK( ss_get_report_amount( tmp_gavp2, &tmp_i), "Report-Amount retrieved.\n", "Failed to retrieve Report-Amount.\n", NULL);
	/*compare Reporting-Amount value*/
	test_comp_int( tmp_i, (int32_t)(atoi(row[12])), "Reporting-Amount");
	
	/* Get Event-Threshold-RSRP */		
	SS_WCHECK( ss_get_event_threshold_rsrp( tmp_gavp2, &tmp_u), "Event-Threshold-RSRP retrieved.\n", "Failed to retrieve Event-Threshold-RSRP.\n", NULL);
	/*compare Event-Threshold-RSRP value*/
	test_comp_uint( tmp_u, (uint32_t)(strtoul(row[13], NULL, 10)), "Event-Threshold-RSRP");

	/* Get Event-Threshold-RSRQ */		
	SS_WCHECK( ss_get_event_threshold_rsrq( tmp_gavp2, &tmp_u), "Event-Threshold-RSRQ retrieved.\n", "Failed to retrieve Event-Threshold-RSRQ.\n", NULL);
	/*compare Event-Threshold-RSRQ value*/
	test_comp_uint( tmp_u, (uint32_t)(strtoul(row[14], NULL, 10)), "Event-Threshold-RSRQ");

	/* Get Logging-Interval*/	
	SS_WCHECK( ss_get_logging_interval( tmp_gavp2, &tmp_i), "Logging-Interval retrieved.\n", "Failed to retrieve Logging-Interval.\n", NULL);
	/*compare Logging-Interval value*/
	test_comp_int( tmp_i, (int32_t)(atoi(row[15])), "Logging-Interval");

	/* Get Logging-Duration */		
	SS_WCHECK( ss_get_logging_duration( tmp_gavp2, &tmp_i), "Logging-Duration retrieved.\n", "Failed to retrieve Logging-Duration.\n", NULL);
	/*compare Logging-Duration value*/
	test_comp_int( tmp_i, (int32_t)(atoi(row[16])), "Logging-Duration");

	/* Get Measurement-Period-LTE*/	
	SS_WCHECK( ss_get_measurement_period_lte( tmp_gavp2, &tmp_i), "Measurement-Period-LTE retrieved.\n", "Failed to retrieve Measurement-Period-LTE.\n", NULL);
	/*compare Measurement-Period-LTE value*/
	test_comp_int( tmp_i, (int32_t)(atoi(row[17])), "Measurement-Period-LTE");

	/* Get Measurement-Period-UMTS*/		
	SS_WCHECK( ss_get_measurement_period_umts( tmp_gavp2, &tmp_i), "Measurement-Period-UMTS retrieved.\n", "Failed to retrieve Measurement-Period-UMTS.\n", NULL);
	/*compare Measurement-Period-UMTS value*/
	test_comp_int( tmp_i, (int32_t)(atoi(row[18])), "Measurement-Period-UMTS");

	/* Get Collection-Period-RMM-LTE*/	
	SS_WCHECK( ss_get_collection_period_rmm_lte( tmp_gavp2, &tmp_i), "Collection-Period-RMM-LTE retrieved.\n", "Failed to retrieve Collection-Period-RMM-LTE.\n", NULL);
	/*compare Collection-Period-RMM-LTE value*/
	test_comp_int( tmp_i, (int32_t)(atoi(row[19])), "Collection-Period-RMM-LTE");

	/* Get Collection-Period-RRM-UMTS*/		
	SS_WCHECK( ss_get_collection_period_rmm_umts( tmp_gavp2, &tmp_i), "Collection-Period-RMM-UMTS retrieved.\n", "Failed to retrieve Collection-Period-RMM-UMTS.\n", NULL);
	/*compare Collection-Period-RRM-UMTS value*/
	test_comp_int( tmp_i, (int32_t)(atoi(row[20])), "Collection-Period-RRM-UMTS");

	/* Get Positioning-Method*/		
	SS_WCHECK( ss_get_positioning_method( tmp_gavp2, &tmp_str, &len), "Positioning-Method retrieved.\n", "Failed to retrieve Positioning-Method.\n", NULL);
	/*compare Positioning-Method value*/
	test_comp_str( tmp_str, (unsigned char *)row[21], len, "Positioning-Method");

	/* Get Measurement-Quantity*/		
	SS_WCHECK( ss_get_measurement_quantity( tmp_gavp2, &tmp_str, &len), "Measurement-Quantity retrieved.\n", "Failed to retrieve Measurement-Quantity.\n", NULL);
	/*compare Measurement-Quantity value*/
	test_comp_str( tmp_str, (unsigned char *)row[22], len, "Measurement-Quantity");

	/* Get Event-Threshold-Event-1F*/		
	SS_WCHECK( ss_get_event_threshold_event_1f( tmp_gavp2, &tmp_u), "Event-Threshold-Event-1F retrieved.\n", "Failed to retrieve Event-Threshold-Event-1F.\n", NULL);
	/*compare Event-Threshold-Event-1F value*/
	test_comp_uint( tmp_u, (uint32_t)(strtoul(row[23], NULL, 10)), "Event-Threshold-Event-1F");

	/* Get Event-Threshold-Event-1I*/		
	SS_WCHECK( ss_get_event_threshold_event_1i( tmp_gavp2, &tmp_u), "Event-Threshold-Event-1I retrieved.\n", "Failed to retrieve Event-Threshold-Event-1I.\n", NULL);
	/*compare Event-Threshold-Event-1I value*/
	test_comp_uint( tmp_u, (uint32_t)(strtoul(row[24], NULL, 10)), "Event-Threshold-Event-1I");

	/* Get MDT-Allowed-PLMN-Id (only 3 AVPs set for testing)*/
	SS_WCHECK( ss_get_mdt_allowed_plmn_id_gavp_array(tmp_gavp2, &tmp_str_arr, &len_arr, &size), "MDT-Allowed-PLMN-Id retrieved.\n", "Failed to retrieve MDT-Allowed-PLMN-Id.\n", NULL);
	while(size){
	
		test_comp_str( tmp_str_arr[size-1], (unsigned char *)row[24+size], len_arr[size-1],"MDT-Allowed-PLMN-Id");

		size--;
	}
	if(tmp_str_arr) free(tmp_str_arr);
	if(len_arr) free(len_arr);
}

/* Set GPRS-Subscription-Data*/
static void set_gprs_subsc_data(struct avp **gavp, char * imsi){

	struct avp * tmp_gavp;	
	struct avp * tmp_gavp2;	
	unsigned32 tmp_u;
	integer32 tmp_i;
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi)) return;
	
	/*Create GPRS-Subscription-Data group AVP*/
	SS_CHECK( ss_create_gprs_subscription_data(&tmp_gavp), "GPRS-Subscription-Data AVP created.\n", "Failed to create GPRS-Subscription-Data.\n");

	/*Set Complete-Data-List-Included-Indicator*/
	SS_CHECK( ss_set_complete_data_list_included_indicator( &tmp_gavp, (int)gb_comp_dt_lst_inc_ind), "Complete-Data-List-Included-Indicator set.\n", "Failed to set Complete-Data-List-Included-Indicator.\n");		
	
	/** Set PDP-Context	group AVP **/

	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get pdp context data*/	
	sprintf(buf,"select * from pdpContext where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "pdp context data retrieved from db.\n", "Failed to retrieve pdp context data from database.\n");

	/*Check if the result is empty*/
	if(mysql_num_rows(res) == 0) return;	

	while((row = mysql_fetch_row(res)) != NULL){	
		
		/*Create PDP-Context AVP*/
		SS_CHECK( ss_create_pdp_context(&tmp_gavp2), "PDP-Context AVP created.\n", "Failed to create PDP-Context.\n");
	
		/* Set Context-Identifier */
		if(row[1])
			SS_SET_U32( ss_set_context_identifier( (avp_or_msg **)&tmp_gavp2, tmp_u), tmp_u, row[1], "context identifier set.\n", "Failed to set Context-Identifier.\n");

		/* Set PDP-Type */
		if(row[2])
			SS_CHECK( ss_set_pdp_type(&tmp_gavp2,(octetstring *)row[2], strlen((char *)row[2])), "pdp type set.\n", "Failed to set PDP-Type.\n");

		/* Set PDP-Address */
		if(row[3])
			SS_CHECK( ss_set_pdp_address(&tmp_gavp2,(address *)row[3], strlen((char *)row[3])), "pdp address set.\n", "Failed to set PDP-Address.\n");	
	
		/* Set QoS-Subscribed */
		if(row[4])
			SS_CHECK( ss_set_qos_subscribed(&tmp_gavp2,(octetstring *)row[4], strlen((char *)row[4])), "qos subscribed set.\n", "Failed to set QoS-Subscribed.\n");

		/* Set VPLMN-Dynamic-Address-Allowed */
		if(row[5])
			SS_SET_I32( ss_set_vplmn_dynamic_address_allowed(&tmp_gavp2, tmp_i), tmp_i, row[5], "vplmn dynamic address allowed set.\n", "Failed to set VPLMN-Dynamic-Address-Allowed.\n");						

		/* Set Service-Selection*/
		if(row[6])
			SS_CHECK( ss_set_service_selection((avp_or_msg **)&tmp_gavp2, (utf8string *)row[6], strlen((char *)row[6])), " service selection set.\n", "Failed to set Service-Selection.\n");

		/* Set 3GPP-Charging-Characteristics */
		if(row[7])
			SS_CHECK( ss_set_3gpp_charging_characteristics(&tmp_gavp2, (utf8string *)row[7], strlen((char *)row[7])), "3pp charging characteristics  set.\n", "Failed to set 3GPP-Charging-Characteristics.\n");					

		/* Set Ext-PDP-Type */
		if(row[8])
			SS_CHECK( ss_set_ext_pdp_type(&tmp_gavp2,(octetstring *)row[8], strlen((char *)row[8])), "ext pdp type set.\n", "Failed to set Ext-PDP-Type.\n");		

		/* Set Ext-PDP-Address */
		if(row[9])
			SS_CHECK( ss_set_ext_pdp_address(&tmp_gavp2,(address *)row[9], strlen((char *)row[9])), "ext pdp address set.\n", "Failed to set Ext-PDP-Address.\n");		

		/*** Set AMBR ***/
		test_set_ambr( &tmp_gavp2, row[10], row[11]);
	
		/* Set APN-OI-Replacement*/
		if(row[12])
			SS_CHECK( ss_set_apn_oi_replacement(&tmp_gavp2, (utf8string *)row[12], strlen((char *)row[12])), "apn oi replacement set.\n", "Failed to set APN-OI-Replacement.\n");

		/* Set SIPTO-Permission */
		if(row[13])
			SS_SET_I32( ss_set_sipto_permission( &tmp_gavp2, tmp_i), tmp_i, row[13], "sipto permission set.\n", "Failed to set SIPTO-Permission.\n");					

		/* Set LIPA-Permission */
		if(row[14])
			SS_SET_I32( ss_set_lipa_permission( &tmp_gavp2, tmp_i), tmp_i, row[14], "lipa permission set.\n", "Failed to set LIPA-Permission.\n");		

		/* Set Restoration-Priority */
		if(row[15])
			SS_SET_U32( ss_set_restoration_priority( &tmp_gavp2, tmp_u), tmp_u, row[15], "restoration priority set.\n", "Failed to set Restoration-Priority.\n");

		/* Set SIPTO-Local-Network-Permission */
		if(row[16])
			SS_SET_U32( ss_set_sipto_local_network_permission( &tmp_gavp2, tmp_u), tmp_u, row[16], "sipto local network permission set.\n", "Fail to set SIPTO-Local-Network-Permission.\n");	

		/*Add PDP-Context into GPRS-Subscription-Data*/
		SS_CHECK( ss_add_avp( (avp_or_msg **)&tmp_gavp, tmp_gavp2), "PDP-Context added.\n", "Failed to add PDP-Context.\n");		
	} 

	mysql_free_result(res);	
	mysql_close(conn);

	/*Add GPRS-Subscription-Data group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "GPRS-Subscription-Data added.\n", "Failed to add GPRS-Subscription-Data.\n");			
}

/* Check GPRS-Subscription-Data*/
static void check_gprs_subsc_data(struct avp *gavp, char *imsi){

	struct avp *tmp_gavp = NULL;	
	struct avp *tmp_gavp2 = NULL;
	struct avp *tmp_gavp3 = NULL;
	unsigned32 tmp_u;
	integer32 tmp_i;
	octetstring *tmp_str = NULL;
	size_t len = 0;
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi)) return;

	/*Get GPRS-Subscription-Data group AVP*/
	SS_WCHECK( ss_get_gavp_gprs_subscription_data( gavp, &tmp_gavp), "GPRS-Subscription-Data AVP retrieved.\n", "Failed to retrieve GPRS-Subscription-Data.\n", return);

	/*Get Complete-Data-List-Included-Indicator*/
	SS_CHECK( ss_get_complete_data_list_included_indicator( tmp_gavp, &tmp_i), "Complete-Data-List-Included-Indicator retrieved.\n", "Failed to retrieve Complete-Data-List-Included-Indicator.\n");
	/*compare Complete-Data-List-Included-Indicator value*/
	test_comp_int( tmp_i, (uint32_t)gb_comp_dt_lst_inc_ind, "Complete-Data-List-Included-Indicator");

	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get pdp context data*/	
	sprintf(buf,"select * from pdpContext where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "pdp context data retrieved from db.\n", "Failed to retrieve pdp context data from database.\n");

	/*Check if the result is empty*/
	if(mysql_num_rows(res) == 0) return;	

	/*Get PDP-Context AVP*/
	SS_CHECK( ss_get_gavp_pdp_context(tmp_gavp, &tmp_gavp2), "PDP-Context AVP retrieved.\n", "Failed to retrieve PDP-Context.\n");

	while((NULL != (row = mysql_fetch_row(res))) && (tmp_gavp2)){
	
		/* Get Context-Identifier */
		SS_CHECK( ss_get_context_identifier( tmp_gavp2, &tmp_u), "context identifier retrieved.\n", "Failed to retrieve Context-Identifier.\n");
		/*compare Context-Identifier value*/
		test_comp_uint( tmp_u, (uint32_t)(strtoul(row[1], NULL, 10)), "Context-Identifier");

		/* Get PDP-Type */
		SS_CHECK( ss_get_pdp_type(tmp_gavp2, &tmp_str, &len), "pdp type retrieved.\n", "Failed to retrieve PDP-Type.\n");
		/*compare PDP-Type value*/
		test_comp_str( tmp_str, (unsigned char *)row[2], len, "PDP-Type");

		/* Get PDP-Address */
		SS_WCHECK( ss_get_pdp_address(tmp_gavp2, &tmp_str, &len), "pdp address retrieved.\n", "Failed to retrieve PDP-Address.\n", NULL);	
		/*compare PDP-Address value*/
		test_comp_str( tmp_str, (unsigned char *)row[3], len, "PDP-Address");
	
		/* Get QoS-Subscribed */
		SS_CHECK( ss_get_qos_subscribed(tmp_gavp2, &tmp_str, &len), "qos subscribed retrieved.\n", "Failed to retrieve QoS-Subscribed.\n");
		/*compare QoS-Subscribed value*/
		test_comp_str( tmp_str, (unsigned char *)row[4], len, "QoS-Subscribed");

		/* Get VPLMN-Dynamic-Address-Allowed */
		SS_WCHECK( ss_get_vplmn_dynamic_address_allowed(tmp_gavp2, &tmp_i), "vplmn dynamic address allowed retrieved.\n", "Failed to retrieve VPLMN-Dynamic-Address-Allowed.\n", NULL);	
		/*compare VPLMN-Dynamic-Address-Allowed value*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[5])), "VPLMN-Dynamic-Address-Allowed");					

		/* Get Service-Selection*/
		SS_WCHECK( ss_get_service_selection(tmp_gavp2,  &tmp_str, &len), " service selection retrieved.\n", "Failed to retrieve Service-Selection.\n", NULL);
		/*compare Service-Selection value*/
		test_comp_str( tmp_str, (unsigned char *)row[6], len, "Service-Selection");

		/* Get 3GPP-Charging-Characteristics */
		SS_WCHECK( ss_get_3gpp_charging_characteristics(tmp_gavp2,  &tmp_str, &len), "3pp charging characteristics  retrieved.\n", "Failed to retrieve 3GPP-Charging-Characteristics.\n", NULL);
		/*compare 3GPP-Charging-Characteristics value*/
		test_comp_str( tmp_str, (unsigned char *)row[7], len, "3GPP-Charging-Characteristics");					

		/* Get Ext-PDP-Type */
		SS_WCHECK( ss_get_ext_pdp_type(tmp_gavp2, &tmp_str, &len), "ext pdp type retrieved.\n", "Failed to retrieve Ext-PDP-Type.\n", NULL);
		/*compare Ext-PDP-Type value*/
		test_comp_str( tmp_str, (unsigned char *)row[8], len, "Ext-PDP-Type");		

		/* Get Ext-PDP-Address */
		SS_WCHECK( ss_get_ext_pdp_address(tmp_gavp2, &tmp_str, &len), "ext pdp address retrieved.\n", "Failed to retrieve Ext-PDP-Address.\n", NULL);	
		/*compare Ext-PDP-Address value*/
		test_comp_str( tmp_str, (unsigned char *)row[9], len, "Ext-PDP-Address");	

		/*check AMBR value*/
		check_ambr( tmp_gavp2, row[10], row[11]);
	
		/* Get APN-OI-Replacement*/
		SS_WCHECK( ss_get_apn_oi_replacement(tmp_gavp2, &tmp_str, &len), "apn oi replacement retrieved.\n", "Failed to retrieve APN-OI-Replacement.\n", NULL);
		/*compare APN-OI-Replacement value*/
		test_comp_str( tmp_str, (unsigned char *)row[12], len, "APN-OI-Replacement");

		/* Get SIPTO-Permission */
		SS_WCHECK( ss_get_sipto_permission( tmp_gavp2, &tmp_i), "sipto permission retrieved.\n", "Failed to retrieve SIPTO-Permission.\n", NULL);	
		/*compare SIPTO-Permission value*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[13])), "SIPTO-Permission");				

		/* Get LIPA-Permission */
		SS_WCHECK( ss_get_lipa_permission( tmp_gavp2, &tmp_i), "lipa permission retrieved.\n", "Failed to retrieve LIPA-Permission.\n", NULL);		
		/*compare LIPA-Permission value*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[14])), "LIPA-Permission");

		/* Get Restoration-Priority */
		SS_WCHECK( ss_get_restoration_priority( tmp_gavp2, &tmp_u), "restoration priority retrieved.\n", "Failed to retrieve Restoration-Priority.\n", NULL);
		/*compare Restoration-Priority value*/
		test_comp_uint( tmp_u, (int32_t)(strtoul(row[15], NULL, 10)), "Restoration-Priority");

		/* Get SIPTO-Local-Network-Permission */
		SS_WCHECK( ss_get_sipto_local_network_permission( tmp_gavp2, &tmp_i), "sipto local network permission retrieved.\n", "Fail to retrieve SIPTO-Local-Network-Permission.\n", NULL);
		/*compare SIPTO-Local-Network-Permission value*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[16])), "SIPTO-Local-Network-Permission");

		/*Get next PDP-Context AVP*/
		SS_WCHECK( ss_get_gavp_pdp_context(tmp_gavp2, &tmp_gavp3), "Next PDP-Context AVP retrieved.\n", "Failed to retrieve next PDP-Context.\n", return);
	
		tmp_gavp2 = tmp_gavp3;
		tmp_gavp3 = NULL;
	}		
}

/* Set CSG-Subscription-Data */
static void set_csg_subscription_data(struct avp **gavp, char *imsi, octetstring *vis_plmn_id){

	struct avp *tmp_gavp = NULL;
	unsigned32 tmp_u;
	char buf[110] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;
	
	if((!gavp) || (!imsi) || (!vis_plmn_id)) return;

	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get csg data*/	
	sprintf(buf,"select * from csgData where imsi='%.15s' and visitPlmnId=x'%02x%02x%02x'", imsi, vis_plmn_id[0],vis_plmn_id[1],vis_plmn_id[2]);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "csg data retrieved from db.\n", "Failed to retrieve csg data from database.\n");
	
	/*Check if the result is empty*/
	if(NULL == (row = mysql_fetch_row(res))) return;	
	
	/*Create CSG-Subscription-Data*/
	SS_CHECK( ss_create_csg_subscription_data( &tmp_gavp), "CSG-Subscription-Data AVP created.\n", "Failed to set CSG-Subscription-Data.\n");

	/* Set CSG-Id*/
	if(row[1])
		SS_SET_U32( ss_set_csg_id(&tmp_gavp, tmp_u), tmp_u, row[1], "CSG-Id set.\n", "Failed to set CSG-Id.\n");
	
	/* Set Expiration-Date*/
	if(row[2])
		SS_CHECK( ss_set_expiration_date( &tmp_gavp, (ss_time *)row[2], strlen((char *)row[2])), "Expiration-Date set.\n", "Failed to set Expiration-Date.\n");
	
	/* Set Service-Selection (only 3 AVPs for testing)*/
	if(row[3])
		SS_CHECK( ss_set_service_selection( (avp_or_msg **)&tmp_gavp, (utf8string *)row[3], strlen((char *)row[3])), "Service-Selection set.\n", "Failed to set Service-Selection.\n");
	if(row[4])
		SS_CHECK( ss_set_service_selection( (avp_or_msg **)&tmp_gavp, (utf8string *)row[4], strlen((char *)row[4])), "Service-Selection 2 set.\n", "Failed to set Service-Selection 2.\n");
	if(row[5])
		SS_CHECK( ss_set_service_selection( (avp_or_msg **)&tmp_gavp, (utf8string *)row[5], strlen((char *)row[5])), "Service-Selection 3 set.\n", "Failed to set Service-Selection 3.\n");	
		
	/* Set Visited-PLMN-Id*/
	if(row[6])
		SS_CHECK( ss_set_visited_plmn_id( (avp_or_msg **)&tmp_gavp, (octetstring *)row[6], strlen((char *)row[6])), "Visited-PLMN-Id set.\n", "Failed to set Visited-PLMN-Id.\n");	

	mysql_free_result(res);
	mysql_close(conn);

	/*Add CSG-Subscription-Data group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "CSG-Subscription-Data added.\n", "Failed to add CSG-Subscription-Data.\n") ;	
}

/* check CSG-Subscription-Data */
static void check_csg_subscription_data(struct avp *gavp, char *imsi){

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	unsigned32 tmp_u;
	octetstring *tmp_str = NULL; 
	octetstring **tmp_str_arr = NULL;
	size_t size = 0;
	size_t len = 0;
	size_t *len_arr = NULL;
	char buf[110] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;
	
	if((!gavp) || (!imsi)) return;

	/*Get CSG-Subscription-Data*/
	SS_WCHECK( ss_get_gavp_csg_subscription_data( gavp, &tmp_gavp), "CSG-Subscription-Data AVP retrieved.\n", "Failed to retrieve CSG-Subscription-Data.\n",return);

	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to get csg data*/	
	sprintf(buf,"select * from csgData where imsi='%.15s' and visitPlmnId=x'%02x%02x%02x'", imsi, gb_visited_plmn_id[0][0], gb_visited_plmn_id[0][1], gb_visited_plmn_id[0][2]);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "csg data retrieved from db.\n", "Failed to retrieve csg data from database.\n");	

	while((tmp_gavp) && (NULL == (row = mysql_fetch_row(res)))){

		/* Get CSG-Id*/
		SS_CHECK( ss_get_csg_id(tmp_gavp, &tmp_u), "CSG-Id retrieved.\n", "Failed to retrieve CSG-Id.\n");
		/*compare CSG-Id value*/
		test_comp_uint( tmp_u, (uint32_t)(strtoul( row[1], NULL, 10)), "CSG-Id");
	
		/* Get Expiration-Date*/
		SS_WCHECK( ss_get_expiration_date( tmp_gavp, &tmp_str, &len), "Expiration-Date retrieved.\n", "Failed to retrieve Expiration-Date.\n", NULL);
		/*compare Expiration-Date value*/
		test_comp_str( tmp_str, (unsigned char *)row[2], len, "Expiration-Date");
	
		/* Get Service-Selection */
		SS_WCHECK( ss_get_service_selection_gavp_array( tmp_gavp, &tmp_str_arr, &len_arr, &size), "Service-Selection retrieved.\n", "Failed to retrieve Service-Selection.\n", NULL);
		/*compare Service-Selection value*/
		while(size){

			test_comp_str( tmp_str_arr[size-1], (unsigned char *)row[2+size], len_arr[size-1], "Service-Selection");

			size--;
		}
		if(tmp_str_arr) free(tmp_str_arr);
		if(len_arr) free(len_arr);

		/* Get Visited-PLMN-Id*/
		SS_WCHECK( ss_get_visited_plmn_id( tmp_gavp, &tmp_str, &len), "Visited-PLMN-Id retrieved.\n", "Failed to retrieve Visited-PLMN-Id.\n", NULL);
		/* compare Visited-PLMN-Id value*/
		test_comp_str( tmp_str, (unsigned char *)row[6], len, "Visited-PLMN-Id");
	
		/*Get next CSG-Subscription-Data*/
		SS_WCHECK( ss_get_gavp_next_csg_subscription_data( tmp_gavp, &tmp_gavp2), "Next CSG-Subscription-Data AVP retrieved.\n", "Failed to retrieve next CSG-Subscription-Data.\n",return);
		tmp_gavp = tmp_gavp2;
		tmp_gavp2 = NULL;

		/*Prepare mysql statement to get next csg data*/	
		sprintf(buf,"select * from csgData where imsi='%.15s' and visitPlmnId=x'%02x%02x%02x'", imsi, gb_visited_plmn_id[1][0], gb_visited_plmn_id[1][1], gb_visited_plmn_id[1][2]);

		/*Query next database*/
		SS_CHECK(test_get_qry_res(conn, buf, &res), "csg data retrieved from db.\n", "Failed to retrieve csg data from database.\n");
	}
}

/* Set ProSe-Subscription-Data*/
static void set_prose_subsc(struct avp **gavp, char * prose_perm){
	
	struct avp * tmp_gavp;
	unsigned32 tmp_u;

	if((!gavp) || (!prose_perm)) return;
	
	/*Create ProSe-Subscription-Data group AVP*/
	SS_CHECK( ss_create_prose_subscription_data( &tmp_gavp), "ProSe-Subscription-Data set.\n", "Failed to create ProSe-Subscription-Data.\n");

	/*Set ProSe-Permission*/	
	SS_SET_U32( ss_set_prose_permission( &tmp_gavp, tmp_u), tmp_u, prose_perm, "ProSe-Permission set.\n", "Failed to set ProSe-Permission.\n");	

	/*Add ProSe-Subscription-Data group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)gavp, tmp_gavp), "ProSe-Subscription-Data added.\n", "Failed to add ProSe-Subscription-Data.\n");
}

/* Check ProSe-Subscription-Data*/
static void check_prose_subsc(struct avp *avp, uint32_t prose_perm){
	
	struct avp *tmp_gavp = NULL;
	unsigned32 tmp_u;

	if(!avp) return;
	
	/*Get ProSe-Subscription-Data group AVP*/
	SS_WCHECK( ss_get_gavp_prose_subscription_data( avp, &tmp_gavp), "ProSe-Subscription-Data retrieved.\n", "Failed to retrieve ProSe-Subscription-Data.\n",return);

	/*Get ProSe-Permission*/	
	SS_CHECK( ss_get_prose_permission( tmp_gavp, &tmp_u), "ProSe-Permission retrieved.\n", "Failed to retrieve ProSe-Permission.\n");	
	/*compare ProSe-Permission value*/
	test_comp_uint( tmp_u, prose_perm, "ProSe-Permission");
}

/* Create and set Subscription-Data AVP*/
void test_set_subsc_data(struct msg ** msg, char * imsi, unsigned32 flg, struct msg * req){

	struct avp * tmp_gavp;
	struct avp * tmp_gavp2;
	unsigned32 tmp_u;
	integer32 tmp_i;	
	octetstring ** visited_plmn_id = NULL;
	char buf[70] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!msg) || (!imsi)) return;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to subscription data*/	
	sprintf(buf,"select * from subscriptionData where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "Subscription data retrieved from db.\n", "Failed to retrieve subscription data from database.\n"); 
	
	if((row = mysql_fetch_row(res))!= NULL){

		/*Create Subscription-Data group AVP*/
		SS_CHECK( ss_create_subscription_data(&tmp_gavp), "Subscription-Data AVP created.\n", "Failed to create Subscription-Data AVP.\n");
						
		/* Set Subscriber-Status*/
		if(row[1])
			SS_SET_I32( ss_set_subscriber_status( &tmp_gavp, tmp_i), tmp_i, row[1], "Subscriber-Status AVP.\n", "Failed to set Subscriber-Status AVP.\n");
		
		/* Set MSISDN*/
		if(row[2])
			SS_CHECK( ss_set_msisdn( &tmp_gavp, (octetstring *)row[2], strlen((char *)row[2])), "MSISDN set.\n", "Failed to set MSISDN AVP.\n");

		/* Set A-MSISDN*/
		if(row[3])
			SS_CHECK( ss_set_a_msisdn( &tmp_gavp, (octetstring *)row[3], strlen((char *)row[3])), "A_MSISDN set.\n", "Failed to set A_MSISDN AVP.\n");

		/* Set STN-SR*/
		if(row[4])
			SS_CHECK( ss_set_stn_sr( &tmp_gavp, (octetstring *)row[4], strlen((char *)row[4])), "STN-SR set.\n", "Failed to set STN-SR AVP.\n");

		/* Set ICS-Indicator*/
		if(row[5])
			SS_SET_I32( ss_set_ics_indicator( &tmp_gavp, tmp_i), tmp_i, row[5], "ICS-Indicator set.\n", "Failed to set ICS-Indicator AVP.\n");
	
		/* Set Network-Access-Mode*/
		if(row[6])
			SS_SET_I32( ss_set_network_access_mode( &tmp_gavp, tmp_i), tmp_i, row[6], "Network-Access-Mode set.\n", "Failed to set Network-Access-Mode AVP.\n");
	
		/* Set Operator-Determined-Barring*/
		if(row[7])
			SS_SET_U32( ss_set_operator_determined_barring( &tmp_gavp, tmp_u), tmp_u, row[7], "Operator-Determined-Barring set.\n", "Failed to set Operator-Determined-Barring AVP.\n");

		/* Set HPLMN-ODB*/
		if(row[8])
			SS_SET_U32( ss_set_hplmn_odb( &tmp_gavp, tmp_u), tmp_u, row[8], "Operator-Determined-Barring set.\n", "Failed to set Operator-Determined-Barring AVP.\n");
	
		/* Set Regional-Subscription-Zone-Code*/
		if(row[9])
			SS_CHECK( ss_set_regional_subscription_zone_code( &tmp_gavp, (octetstring *)row[9], strlen((char *)row[9])), "Regional-Subscription-Zone-Code set.\n", "Failed to set Regional-Subscription-Zone-Code AVP.\n");
		if(row[10])
			SS_CHECK( ss_set_regional_subscription_zone_code( &tmp_gavp, (octetstring *)row[10], strlen((char *)row[10])), "Regional-Subscription-Zone-Code 2 set.\n", "Failed to set Regional-Subscription-Zone-Code 2 AVP.\n");
		if(row[11])
			SS_CHECK( ss_set_regional_subscription_zone_code( &tmp_gavp, (octetstring *)row[11], strlen((char *)row[11])), "Regional-Subscription-Zone-Code 3 set.\n", "Failed to set Regional-Subscription-Zone-Code 3 AVP.\n");						

		/* Set Access-Restriction-Data*/
		if(row[12])
			SS_SET_U32( ss_set_access_restriction_data( &tmp_gavp, tmp_u), tmp_u, row[12], "Restriction-Data set.\n", "Failed to set Access-Restriction-Data AVP.\n");
		
		/* Set APN-OI-Replacement */
		if(row[13])
			SS_CHECK( ss_set_apn_oi_replacement( &tmp_gavp, (utf8string *)row[13], strlen((char *)row[13])), "APN-OI-Replacement set.\n", "Failed to set APN-OI-Replacement AVP.\n");
	
		/*Set LCS-Info*/
		test_set_lcs_info( &tmp_gavp, imsi);
					
		/* Create Teleservice-List*/
		test_set_teleserv_list( &tmp_gavp, (octetstring *) row[14], (octetstring *) row[15], (octetstring *) row[16]);

		/* Set Call-Barring-Info group AVP*/
		test_set_call_barring_info( &tmp_gavp, imsi);
				
		/* Set 3GPP-Charging-Characteristics */
		if(row[17])
			SS_CHECK( ss_set_3gpp_charging_characteristics( &tmp_gavp, (utf8string *)row[17], strlen((char *)row[17])), "3GPP-Charging-Characteristics set.\n", "Failed to set 3GPP-Charging-Characteristics.\n");
	
		/* Create AMBR	group AVP*/
		test_set_ambr( &tmp_gavp, row[18], row[19]);					
			
		/*Set APN-Configuration-Profile group AVP*/
		if(row[20])					
			test_set_apn_conf_prof( &tmp_gavp, imsi, row[20]);				
	
		/* Set RAT-Frequency-Selection-Priority-ID(u32)*/
		if(row[21])
			SS_SET_U32( ss_set_rat_frequency_selection_priority_id( &tmp_gavp, tmp_u), tmp_u, row[21], "RAT-Frequency-Selection-Priority-ID set.\n", "Failed to set RAT-Frequency-Selection-Priority-ID.\n");
	
		/*Set Trace-Data group Avp*/
		set_trace_data( &tmp_gavp, imsi);
	
		/* Set GPRS-Subscription-Data*/
		if(CHECK_ULR_GPRS_DATA_IND(flg))					
			set_gprs_subsc_data( &tmp_gavp, imsi);				
	
		/* Set CSG-Subscription-Data accoriding to Equivalent-PLMN-List if it exists in the request */	
		if((req) && (0 == ss_get_gavp_equivalent_plmn_list( req, &tmp_gavp2))){

			size_t array_size = 0;	
			size_t tmp_size;
			size_t *len_arr = NULL;
			/*Get array of Visited-Plmn-Id values*/
			SS_CHECK(ss_get_visited_plmn_id_gavp_array(tmp_gavp2, &visited_plmn_id, &len_arr, &array_size), "Visited-Plmn-Id retrieved from Equivalent-PLMN-List.\n", "Failed to retrieve Visited-Plmn-Id retrieved from Equivalent-PLMN-List.\n");
			tmp_size = array_size;

			while(tmp_size > 0){

				/*Set CSG-Subscription-Data*/
				set_csg_subscription_data(&tmp_gavp, imsi, visited_plmn_id[tmp_size-1]);
			
				tmp_size --;
			}

			/*free memory if allocated during ss_get_visited_plmn_id_array() function call*/
			if(array_size)	free(visited_plmn_id);
			if(len_arr) free(len_arr);
		}
	
		/* Set Roaming-Restricted-Due-To-Unsupported-Feature*/		
		if(row[22])
			SS_SET_I32( ss_set_roaming_restricted_unsupported_feature( &tmp_gavp, tmp_i), tmp_i, row[22], "Roaming-Restricted-Due-To-Unsupported-Feature set.\n", "Failed to set Roaming-Restricted-Due-To-Unsupported-Feature.\n");

		/* Set Subscribed-Periodic-RAU-TAU-Timer*/		
		if(row[23])
			SS_SET_U32( ss_set_subscribed_periodic_rau_tau_timer( &tmp_gavp, tmp_u), tmp_u, row[23], "Subscribed-Periodic-RAU-TAU-Timer set.\n", "Failed to set Subscribed-Periodic-RAU-TAU-Timer.\n");

		/* Set MPS-Priority*/		
		if(row[24])
			SS_SET_U32( ss_set_mps_priority( &tmp_gavp, tmp_u), tmp_u, row[24], "MPS-Priority set.\n", "Failed to set MPS-Priority.\n");

		/* Set VPLMN-LIPA-Allowed*/		
		if(row[25])
			SS_SET_I32( ss_set_vplmn_lipa_allowed( &tmp_gavp, tmp_i), tmp_i, row[25], "VPLMN-LIPA-Allowed set.\n", "Failed to set VPLMN-LIPA-Allowed.\n");
	
		/* Set Relay-Node-Indicator*/		
		if(row[26])
			SS_SET_I32( ss_set_relay_node_indicator( &tmp_gavp, tmp_i), tmp_i, row[26], "Relay-Node-Indicator set.\n", "Failed to set Relay-Node-Indicator.\n");
	
		/* Set MDT-User-Consent*/		
		if(row[27])
			SS_SET_I32( ss_set_mdt_user_consent( &tmp_gavp, tmp_i), tmp_i, row[27], "MDT-User-Consent set.\n", "Failed to set MDT-User-Consent.\n");
	
		/* Set Subscribed-VSRVCC*/		
		if(row[28])
			SS_SET_I32( ss_set_subscribed_vsrvcc( &tmp_gavp, tmp_i), tmp_i, row[28], "Subscribed-VSRVCC set.\n", "Failed to set Subscribed-VSRVCC.\n");
	
		/* Set ProSe-Permission in ProSe-Subscription-Data*/
		if(row[29])
			set_prose_subsc( &tmp_gavp, row[29]);
	
		/* Set Subscription-Data-Flags*/		
		if(row[30])
			SS_SET_U32( ss_set_subscription_data_flags( &tmp_gavp, tmp_u), tmp_u, row[30], "Subscription-Data-Flags set.\n", "Failed to set Subscription-Data-Flags.\n");
	
		SS_CHECK( ss_add_avp( (avp_or_msg **)msg, tmp_gavp), "Subscription-Data added to messge.\n", "Failed to add Subscription-Data.\n");
	}

	mysql_free_result(res);
	mysql_close(conn);
}

/* Check Subscription-Data AVP*/
void test_check_subsc_data(struct msg *msg, char *imsi){

	struct avp *tmp_gavp = NULL;
	char buf[65] = {0};
	unsigned32 tmp_u;
	integer32 tmp_i;	
	octetstring *tmp_str = NULL;
	octetstring **tmp_str_arr = NULL;	
	size_t size = 0;
	size_t len = 0;
	size_t *len_arr = NULL;
	
	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!msg) || (!imsi)) return;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to subscription data*/	
	sprintf(buf,"select * from subscriptionData where imsi='%.15s'", imsi);

	/*Query database*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "Subscription data retrieved from db.\n", "Failed to retrieve subscription data from database.\n"); 
	
	if((row = mysql_fetch_row(res))!= NULL){

		/*Get Subscription-Data group AVP*/
		SS_WCHECK( ss_get_gavp_subscription_data(msg, &tmp_gavp), "Subscription-Data AVP retrieved.\n", "Failed to retrieve Subscription-Data AVP.\n", return);
						
		/* Get Subscriber-Status*/
		SS_WCHECK( ss_get_subscriber_status( tmp_gavp, &tmp_i), "Subscriber-Status AVP retrieved.\n", "Failed to retrieved Subscriber-Status AVP.\n", NULL);
		/*compare Subscriber-Status value*/
		test_comp_int( tmp_i, (uint32_t)(atoi(row[1])), "Subscriber-Status");
		
		/* Get MSISDN*/
		SS_WCHECK( ss_get_msisdn( tmp_gavp, &tmp_str, &len), "MSISDN value retrieved.\n", "Failed to retrieve MSISDN AVP value.\n", NULL);
		/*compare MSISDN value*/
		test_comp_str( tmp_str, (unsigned char*)row[2], len, "MSISDN");

		/* Get A-MSISDN*/
		SS_WCHECK( ss_get_a_msisdn( tmp_gavp, &tmp_str, &len), "A-MSISDN value retrieved.\n", "Failed to retrieve A-MSISDN AVP value.\n", NULL);
		/*compare A-MSISDN value*/
		test_comp_str( tmp_str, (unsigned char*)row[3], len, "A-MSISDN");

		/* Get STN-SR*/
		SS_WCHECK( ss_get_stn_sr( tmp_gavp, &tmp_str, &len), "STN-SR retrieved.\n", "Failed to retrieve STN-SR AVP value.\n", NULL);
		/*compare STN-SR value*/
		test_comp_str( tmp_str, (unsigned char*)row[4], len, "STN-SR");

		/* Get ICS-Indicator*/
		SS_WCHECK( ss_get_ics_indicator( tmp_gavp, &tmp_i), "ICS-Indicator retrieved.\n", "Failed to retrieve ICS-Indicator AVP.\n", NULL);
		/*compare ICS-Indicator value*/
		test_comp_int( tmp_i, (uint32_t)(atoi(row[5])), "ICS-Indicator");
	
		/* Get Network-Access-Mode*/
		SS_WCHECK( ss_get_network_access_mode( tmp_gavp, &tmp_i), "Network-Access-Mode retrieved.\n", "Failed to retrieve Network-Access-Mode AVP.\n", NULL);
		/*compare Network-Access-Mode value*/
		test_comp_int( tmp_i, (uint32_t)(atoi(row[6])), "Network-Access-Mode");

		/* Get Operator-Determined-Barring*/
		SS_WCHECK( ss_get_operator_determined_barring( tmp_gavp, &tmp_u), "Operator-Determined-Barring retrieved.\n", "Failed to retrieve Operator-Determined-Barring AVP.\n", NULL);
		/*compare Operator-Determined-Barring value*/
		test_comp_uint( tmp_u, (uint32_t)(strtoul(row[7], NULL, 10)), "Operator-Determined-Barring");

		/* Get HPLMN-ODB*/
		SS_WCHECK( ss_get_hplmn_odb( tmp_gavp, &tmp_u), "Operator-Determined-Barring retrieved.\n", "Failed to retrieve Operator-Determined-Barring AVP.\n", NULL);
		/*compare HPLMN-ODB value*/
		test_comp_uint( tmp_u, (uint32_t)(strtoul(row[8], NULL, 10)), "HPLMN-ODB");
	
		/* Get Regional-Subscription-Zone-Code*/
		SS_WCHECK( ss_get_regional_subscription_zone_code_gavp_array( tmp_gavp, &tmp_str_arr, &len_arr, &size), "Regional-Subscription-Zone-Code retrieved.\n", "Failed to retrieve Regional-Subscription-Zone-Code AVP.\n", NULL);			
		/*compare Regional-Subscription-Zone-Code values*/
		while(size){
		
			test_comp_str( tmp_str_arr[size-1], (unsigned char *)row[8 + size], len_arr[size-1], "Regional-Subscription-Zone-Code");

			size--;	
		}				
		if(tmp_str_arr) free(tmp_str_arr);
		if(len_arr) free(len_arr);	

		/* Get Access-Restriction-Data*/
		SS_WCHECK( ss_get_access_restriction_data( tmp_gavp, &tmp_u), "Restriction-Data retrieved.\n", "Failed to retrieve Access-Restriction-Data AVP.\n", NULL);
		/*compare Access-Restriction-Data values*/
		test_comp_uint( tmp_u, (uint32_t)(strtoul(row[12], NULL, 10)), "Access-Restriction-Data");
		
		/* Get APN-OI-Replacement */
		SS_WCHECK( ss_get_apn_oi_replacement( tmp_gavp, &tmp_str, &len), "APN-OI-Replacement retrieved.\n", "Failed to retrieve APN-OI-Replacement AVP.\n", NULL);
		/*compare APN-OI-Replacement value*/
		test_comp_str( tmp_str, (unsigned char *)row[13], len, "APN-OI-Replacement");
	
		/*Check LCS-Info*/
		test_check_lcs_info( tmp_gavp, imsi);
						
		/* Create Teleservice-List*/
		check_teleserv_list( tmp_gavp,(octetstring *) row[14], (octetstring *) row[15], (octetstring *) row[16]);

		/* Set Call-Barring-Info group AVP*/
		check_call_barring_info( tmp_gavp, imsi);
				
		/* Get 3GPP-Charging-Characteristics */
		SS_WCHECK( ss_get_3gpp_charging_characteristics( tmp_gavp, &tmp_str, &len), "3GPP-Charging-Characteristics retrieved.\n", "Failed to retrieve 3GPP-Charging-Characteristics.\n", NULL);
		/*compare 3GPP-Charging-Characteristics value*/
		test_comp_str( tmp_str, (unsigned char *)row[17], len, "3GPP-Charging-Characteristics");
	
		/* Get AMBR	group AVP*/
		check_ambr( tmp_gavp, row[18], row[19]);					
		
		/*Set APN-Configuration-Profile group AVP*/
		check_apn_conf_prof( tmp_gavp, imsi, row[20]);				
	
		/* Get RAT-Frequency-Selection-Priority-ID(u32)*/
		SS_WCHECK( ss_get_rat_frequency_selection_priority_id( tmp_gavp, &tmp_u), "RAT-Frequency-Selection-Priority-ID retrieved.\n", "Failed to retrieve RAT-Frequency-Selection-Priority-ID.\n", NULL);
		/* compare RAT-Frequency-Selection-Priority-ID values*/
		test_comp_uint( tmp_u, (uint32_t)(strtoul(row[21], NULL, 10)), "RAT-Frequency-Selection-Priority-ID");
	
		/*Get Trace-Data group Avp*/
		check_trace_data( tmp_gavp, imsi);

		/* Get GPRS-Subscription-Data*/
		check_gprs_subsc_data( tmp_gavp, imsi);				
	
		/*Get CSG-Subscription-Data*/
		check_csg_subscription_data(tmp_gavp, imsi);	
	
		/* Get Roaming-Restricted-Due-To-Unsupported-Feature*/		
		SS_WCHECK( ss_get_roaming_restricted_unsupported_feature( tmp_gavp, &tmp_i), "Roaming-Restricted-Due-To-Unsupported-Feature retrieved.\n", "Failed to retrieve Roaming-Restricted-Due-To-Unsupported-Feature.\n", NULL);
		/*compare Roaming-Restricted-Due-To-Unsupported-Feature value*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[22])),"Roaming-Restricted-Due-To-Unsupported-Feature");

		/* Get Subscribed-Periodic-RAU-TAU-Timer*/		
		SS_WCHECK( ss_get_subscribed_periodic_rau_tau_timer( tmp_gavp, &tmp_u), "Subscribed-Periodic-RAU-TAU-Timer retrieved.\n", "Failed to retrieve Subscribed-Periodic-RAU-TAU-Timer.\n", NULL);
		/*compare Subscribed-Periodic-RAU-TAU-Timer value*/
		test_comp_uint( tmp_u, (uint32_t)(strtoul(row[23], NULL, 10)),"Subscribed-Periodic-RAU-TAU-Timer");

		/* Get MPS-Priority*/		
		SS_WCHECK( ss_get_mps_priority( tmp_gavp, &tmp_u), "MPS-Priority retrieved.\n", "Failed to retrieve MPS-Priority.\n", NULL);
		/*compare MPS-Priority value*/
		test_comp_uint( tmp_u, (uint32_t)(strtoul(row[24], NULL, 10)),"MPS-Priority");

		/* Get VPLMN-LIPA-Allowed*/		
		SS_WCHECK( ss_get_vplmn_lipa_allowed( tmp_gavp, &tmp_i), "VPLMN-LIPA-Allowed retrieved.\n", "Failed to retrieve VPLMN-LIPA-Allowed.\n", NULL);
		/*compare VPLMN-LIPA-Allowed value*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[25])),"VPLMN-LIPA-Allowed");

		/* Get Relay-Node-Indicator*/		
		SS_WCHECK( ss_get_relay_node_indicator( tmp_gavp, &tmp_i), "Relay-Node-Indicator retrieved.\n", "Failed to retrieve Relay-Node-Indicator.\n", NULL);
		/*compare Relay-Node-Indicator value*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[26])),"Relay-Node-Indicator");

		/* Get MDT-User-Consent*/		
		SS_WCHECK( ss_get_mdt_user_consent( tmp_gavp, &tmp_i), "MDT-User-Consent retrieved.\n", "Failed to retrieve MDT-User-Consent.\n", NULL);
		/*compare MDT-User-Consent value*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[27])),"MDT-User-Consent");

		/* Get Subscribed-VSRVCC*/		
		SS_WCHECK( ss_get_subscribed_vsrvcc( tmp_gavp, &tmp_i), "Subscribed-VSRVCC retrieved.\n", "Failed to retrieve Subscribed-VSRVCC.\n", NULL);
		/*compare Subscribed-VSRVCC value*/
		test_comp_int( tmp_i, (int32_t)(atoi(row[28])),"Subscribed-VSRVCC");
	
		/* get ProSe-Permission in ProSe-Subscription-Data*/
		check_prose_subsc( tmp_gavp, (uint32_t)(strtoul( row[29], NULL, 10)));
	
		/* Get Subscription-Data-Flags*/		
		SS_WCHECK( ss_get_subscription_data_flags( tmp_gavp, &tmp_u), "Subscription-Data-Flags retrieved.\n", "Failed to retrieve Subscription-Data-Flags.\n", return);
		/*compare Subscription-Data-Flags value*/
		test_comp_uint( tmp_u, (uint32_t)(strtoul( row[30], NULL, 10)), "Subscription-Data-Flags");	
	}

	mysql_free_result(res);
	mysql_close(conn);
}

/*Set EPS-Location-Information*/
void test_set_eps_location_info(struct msg **msg){

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	struct avp *tmp_gavp3 = NULL;	

	if(!msg) return;

	/*Create EPS-Location-Information AVP*/
	SS_CHECK( ss_create_eps_location_information(&tmp_gavp), "EPS-Location-Information created.\n", "Failed to create EPS-Location-Information.\n");

	/*Create MME-Location-Information AVP*/
	SS_CHECK( ss_create_mme_location_information(&tmp_gavp2), "MME-Location-Information created.\n", "Failed to create MME-Location-Information.\n");

	/*Set E-UTRAN-Cell-Global-Identity*/
	SS_CHECK( ss_set_e_utran_cell_global_identity(&tmp_gavp2, gb_e_utran_cgi, strlen((char *)gb_e_utran_cgi)), "E-UTRAN-Cell-Global-Identity set.\n", "Failed to set E-UTRAN-Cell-Global-Identity.\n");

	/*Set Tracking-Area-Identity*/
	SS_CHECK( ss_set_tracking_area_identity(&tmp_gavp2, gb_tracking_area_id, strlen((char *)gb_tracking_area_id)), "Tracking-Area-Identity set.\n", "Failed to set Tracking-Area-Identity.\n");
	
	/*Set Geographical-Information*/
	SS_CHECK( ss_set_geographical_information(&tmp_gavp2, gb_geographical_info, strlen((char *) gb_geographical_info)), "Geographical-Information set.\n", "Failed to set Geographical-Information.\n");

	/*Set Geodetic-Information*/
	SS_CHECK( ss_set_geodetic_information(&tmp_gavp2, gb_geodetic_info, strlen((char *)gb_geodetic_info)), "Geodetic-Information set.\n", "Failed to set Geodetic-Information.\n");

	/*Set Current-Location-Retrieved*/
	SS_CHECK( ss_set_current_location_retrieved(&tmp_gavp2, gb_current_location_retrieved), "Current-Location-Retrieved set.\n", "Failed to set Current-Location-Retrieved.\n");

	/*Set Age-Of-Location-Information*/
	SS_CHECK( ss_set_age_of_location_information(&tmp_gavp2, gb_age_of_location_info), "Age-Of-Location-Information set.\n", "Failed to set Age-Of-Location-Information.\n");

	/*Create User-CSG-Information*/
	SS_CHECK( ss_create_user_csg_information(&tmp_gavp3), "User-CSG-Information created.\n", "Failed to create User-CSG-Information.\n");

	/*Set CSG-Id*/
	SS_CHECK( ss_set_csg_id(&tmp_gavp3, gb_csg_id), "CSG-Id set.\n", "Failed to set CSG-Id.\n");
	
	/*Set CSG-Access-Mode*/
	SS_CHECK( ss_set_csg_access_mode(&tmp_gavp3, gb_csg_access_mode), "CSG-Access-Mode set.\n", "Failed to set CSG-Access-Mode.\n");

	/*Set CSG-Membership-Indication*/
	SS_CHECK( ss_set_csg_membership_indication(&tmp_gavp3, gb_csg_membership_indication), "CSG-Membership-Indication set.\n", "Failed to set CSG-Membership-Indication.\n");

	/*Add User-CSG-Information*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)&tmp_gavp2, tmp_gavp3), "User-CSG-Information added.\n", "Failed to add User-CSG-Information.\n");

	/*Add MME-Location-Information*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)&tmp_gavp, tmp_gavp2), "MME-Location-Information added.\n", "Failed to add MME-Location-Information.\n");

	/*Add EPS-Location-Information*/
	SS_CHECK( ss_add_avp( (avp_or_msg **)msg, tmp_gavp), "EPS-Location-Information.\n", "Failed to add EPS-Location-Information.\n");

}

/*check EPS-Location-Information*/
void test_check_eps_location_info(struct msg *msg){

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	struct avp *tmp_gavp3 = NULL;
	unsigned char *tmp_str = NULL;
	int32_t tmp_i = 0;
	uint32_t tmp_u = 0;
	size_t len = 0;

	if(!msg) return;

	/*Get EPS-Location-Information AVP*/
	SS_WCHECK( ss_get_gavp_eps_location_information(msg, &tmp_gavp), "EPS-Location-Information retrieved.\n", "Failed to retrieve EPS-Location-Information.\n", return);

	/*Get MME-Location-Information AVP*/
	SS_WCHECK( ss_get_gavp_mme_location_information(tmp_gavp, &tmp_gavp2), "MME-Location-Information retrieved.\n", "Failed to retrieve MME-Location-Information.\n", return);

	/*Get E-UTRAN-Cell-Global-Identity*/
	SS_WCHECK( ss_get_e_utran_cell_global_identity(tmp_gavp2, &tmp_str, &len), "E-UTRAN-Cell-Global-Identity retrieved.\n", "Failed to retrieve E-UTRAN-Cell-Global-Identity.\n", NULL);
	/*compare E-UTRAN-Cell-Global-Identity*/
	test_comp_str( tmp_str, gb_e_utran_cgi, len, "E-UTRAN-Cell-Global-Identity");

	/*Get Tracking-Area-Identity*/
	SS_WCHECK( ss_get_tracking_area_identity(tmp_gavp2, &tmp_str, &len), "Tracking-Area-Identity retrieved.\n", "Failed to retrieve Tracking-Area-Identity.\n", NULL);
	/*compare Tracking-Area-Identity values*/
	test_comp_str( tmp_str, gb_tracking_area_id, len, "Tracking-Area-Identity");
	
	/*Get Geographical-Information*/
	SS_WCHECK( ss_get_geographical_information(tmp_gavp2, &tmp_str, &len), "Geographical-Information retrieved.\n", "Failed to retrieve Geographical-Information.\n", NULL);
	/*compare Geographical-Information value*/
	test_comp_str( tmp_str, gb_geographical_info, len, "Geographical-Information");

	/*Get Geodetic-Information*/
	SS_WCHECK( ss_get_geodetic_information(tmp_gavp2, &tmp_str, &len), "Geodetic-Information retrieved.\n", "Failed to retrieve Geodetic-Information.\n", NULL);
	/*compare Geodetic-Information value*/
	test_comp_str( tmp_str, gb_geodetic_info, len, "Geodetic-Information");

	/*Get Current-Location-Retrieved*/
	SS_WCHECK( ss_get_current_location_retrieved(tmp_gavp2, &tmp_i), "Current-Location-Retrieved retrieved.\n", "Failed to retrieve Current-Location-Retrieved.\n", NULL);
	/*compare Current-Location-Retrieved value*/
	test_comp_int( tmp_i, gb_current_location_retrieved, "Current-Location-Retrieved");

	/*Get Age-Of-Location-Information*/
	SS_WCHECK( ss_get_age_of_location_information(tmp_gavp2, &tmp_u), "Age-Of-Location-Information retrieved.\n", "Failed to retrieve Age-Of-Location-Information.\n", NULL);
	/*compare Age-Of-Location-Information value*/
	test_comp_uint( tmp_u, gb_age_of_location_info, "Age-Of-Location-Information");

	/*Get User-CSG-Information*/
	SS_WCHECK( ss_get_gavp_user_csg_information(tmp_gavp2, &tmp_gavp3), "User-CSG-Information retrieved.\n", "Failed to retrieve User-CSG-Information.\n", return);

	/*Get CSG-Id*/
	SS_CHECK( ss_get_csg_id(tmp_gavp3, &tmp_u), "CSG-Id retrieved.\n", "Failed to retrieve CSG-Id.\n");
	/*compare CSG-Id value*/
	test_comp_uint( tmp_u, gb_csg_id, "CSG-Id");
	
	/*Get CSG-Access-Mode*/
	SS_CHECK( ss_get_csg_access_mode(tmp_gavp3, &tmp_i), "CSG-Access-Mode retrieved.\n", "Failed to retrieve CSG-Access-Mode.\n");
	/*compare CSG-Access-Mode value*/
	test_comp_int( tmp_i, (int32_t)gb_csg_access_mode, "CSG-Access-Mode");

	/*Get CSG-Membership-Indication*/
	SS_WCHECK( ss_get_csg_membership_indication(tmp_gavp3, &tmp_i), "CSG-Membership-Indication retrieved.\n", "Failed to retrieve CSG-Membership-Indication.\n", return);
	/*compare CSG-Membership-Indication value*/
	test_comp_int( tmp_i, (int32_t)gb_csg_membership_indication, "CSG-Membership-Indication");
}

/*Compares two strings and their length*/
/*@name : is the name of the AVP whose recieved and sent values are compared*/
/*@str2 : should not contain 0x00 values in between and should terminate with '\0'*/
void test_comp_str(unsigned char *str1, unsigned char *str2, size_t str1_len, char *name){

	size_t str2_len = 0;

	if((!str1) || (!str2) || (!name)) return;

	/*compare length of strings*/
	str2_len = strlen((char *)str2);
	if(str1_len == str2_len)
		fprintf( stdout, "OK : Length of '%s' sent == received : (sent_len = %u) == (recv_len=%u).\n", name, str2_len, str1_len);

	else{

		fprintf( stdout, COLOR_YELLOW"Failed"ANSI_COLOR_RESET" : Length of '%s' sent != received : (sent_len = %u) != (recv_len=%u).\n", name, str2_len, str1_len);
		return;
	}

	/*compare strings*/
	if(0 == memcmp(str1,str2,str1_len))
		fprintf( stdout, "OK : Value of '%s' sent == received.\n", name);
	else
		fprintf( stdout, COLOR_YELLOW"Failed :"ANSI_COLOR_RESET" Value of '%s' sent != received.\n", name);
}

/*Compare two uint32_t values*/
/*@name : is the name of the AVP whose recieved and sent values are compared*/
void test_comp_int(int32_t int_1, int32_t int_2, char *name){

	if( int_1 == int_2)
		fprintf(stdout, "OK : Values of '%s' sent == received : (sent = %d) == (recv = %d).\n", name, int_1, int_2);

	else
		fprintf(stdout, COLOR_YELLOW"Failed :"ANSI_COLOR_RESET" Values of '%s' sent != received : (sent = %d) != (recv = %d).\n", name, int_2, int_1);	
}

/*Compare two uint32_t values*/
/*@name : is the name of the AVP whose recieved and sent values are compared*/
void test_comp_uint(uint32_t uint_1, uint32_t uint_2, char *name){

	if( uint_1 == uint_2)
		fprintf(stdout, "OK : Values of '%s' sent == received : (sent = %u) == (recv = %u).\n", name, uint_1, uint_2);

	else
		fprintf(stdout, COLOR_YELLOW"Failed :"ANSI_COLOR_RESET" Values of '%s' sent != received : (sent = %u) != (recv = %u).\n", name, uint_2, uint_1);	
}
