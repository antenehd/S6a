#include "test.h"

static int get_experimental_result(struct msg * msg, unsigned32 * vend_id, unsigned32 * result_code){

	struct avp * tmp_gavp;

	if((!msg) || (!vend_id) || (!result_code))
		return 1;

	/*Extract experimental result AVP from message*/
	SS_WCHECK( ss_get_gavp_experimental_result(msg, &tmp_gavp), "Experimental result AVP extracted.\n", "Failed to extract experimental result\n", return 1;);

	/*extract vendor id value*/
	SS_CHECK( ss_get_vendor_id(tmp_gavp, vend_id), "vendor id value extracted.\n", "Failed to extract vendor id value from experimental result.\n");

	/*extract vendor id value*/
	SS_CHECK( ss_get_experimental_result_code(tmp_gavp, result_code), "experimental result code value extracted.\n", "Failed to extract experimental result code value from experimental result.\n");

	return 0;
}

/*result should be freed after use*/
static void code_2_str(int code, char ** result){

	if(!result)
		return;
	
	*result = malloc(35);

	if(!(*result))
		return;

	memset(*result, '\0', 35); 

	if(code == 2001)
		strcpy(*result, "DIAMETER_SUCCESS");
	else if(code == (int)DIAMETER_ERROR_USER_UNKNOWN)
		strcpy(*result, "DIAMETER_ERROR_USER_UNKNOWN");
	else if(code == (int)DIAMETER_ERROR_RAT_NOT_ALLOWED)
		strcpy(*result, "DIAMETER_ERROR_RAT_NOT_ALLOWED");	
	else if(code == (int)DIAMETER_ERROR_ROAMING_NOT_ALLOWED)
		strcpy(*result, "DIAMETER_ERROR_ROAMING_NOT_ALLOWED");
	else if(code == (int)DIAMETER_UNABLE_TO_DELIVER)
		strcpy(*result, "DIAMETER_UNABLE_TO_DELIVER");         
	else if(code == 3)
		strcpy(*result, "ODB_HPLMN_APN");
	else
		strcpy(*result, "UNKNOW or NOT PRESENT IN MESSAGE");	
}

static void check_answer(struct msg *msg){

	unsigned32  result_code = 0;
	unsigned32 exp_result_code = 0;
	integer32 err_diag = 0;
	unsigned32 vend_id = 0;
	diameterid * origin = NULL;	
	char * code_str = NULL;
	size_t len = 0;

	if(!msg) return;
		
	/*extract origin host name*/
	SS_CHECK( ss_get_origin_host_msg(msg, &origin, &len), "Origin-Host extracted.\n", "Failed to extract origin host from answer message.\n");
	fprintf(stdout, COLOR_GREEN"\nOK : Answer received from %s"ANSI_COLOR_RESET"\n", (char *)origin);

	/*extract result-code*/
	SS_WCHECK( ss_get_result_code_msg(msg, &result_code), "Result-Code Extracted.\n", "Failed to extract result code from answer message.\n", NULL);

	/*change result code to its string value*/
	code_2_str((int)result_code, &code_str);
	if(NULL != code_str){

		fprintf(stdout, "OK : Result code %s\n", code_str);

		free(code_str);
		code_str = NULL;
	}

	/*extract experimental result child avp values*/
	if( 0 == (get_experimental_result(msg, &vend_id, &exp_result_code))){
		
		/*change result code to its string value*/
		code_2_str((int)exp_result_code, &code_str);

		if(code_str){

			fprintf(stdout, "OK : Experimetal Result:  exp-result-code - %s   vendor_id - %d\n", code_str, vend_id);
			free(code_str);
			code_str = NULL;
		}
	}

	/*extract Error diagnostic from message*/
	SS_WCHECK( ss_get_error_diagnostic_msg(msg, &err_diag), "Error-Diagnostic value extracted.\n", "Failed to extract error diagnostic.\n", NULL);

	if(err_diag){

		/*change error diagnostic to its string value*/
	    code_2_str(err_diag, &code_str);

		if(code_str){
			fprintf(stdout, "OK : Error Diagnostic  %s\n", code_str);
			free(code_str);
			code_str = NULL;
		}
	}

	/*Check Supported-Features AVP*/
	test_check_support_feature( msg);
} 

/*Get  UTRAN auth vector from db and compare it with received values*/
static void check_utran_vect(struct avp *gavp, char * imsi){

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	unsigned char *tmp_str = NULL;
	unsigned32 tmp_u = 0;
	size_t len = 0;
	char buf[70] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res = NULL;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi)) return;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to subscription data*/	
	sprintf(buf,"select * from UTRANVector where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "UTRANVector data retrieved from db.\n", "Failed to retrieve UTRANVector data from database.\n"); 
	
	if((row = mysql_fetch_row(res))!= NULL){

		/*Get UTRAN-Vector AVP*/
		SS_WCHECK( ss_get_gavp_utran_vector(gavp, &tmp_gavp), "UTRAN-Vector retrieved.\n", "Failed to retrieve UTRAN-Vector.\n", return);
		
		while(tmp_gavp){
		
			/*check Item-Number*/
			SS_WCHECK( ss_get_item_number( tmp_gavp, &tmp_u), "Item-Number retrieved.\n", "failed to retrieve Item-Number.\n", NULL);
			test_comp_uint( tmp_u, (uint32_t)(strtoul(row[1], NULL, 10)), "Item-Number");

			/*check RAND*/
			SS_CHECK( ss_get_rand( tmp_gavp, &tmp_str, &len), "RAND retrieved.\n", "failed to retrieve RAND.\n");
			test_comp_str( tmp_str, (unsigned char *)row[2], len, "RAND");

			/*check XRES*/
			SS_CHECK( ss_get_xres( tmp_gavp, &tmp_str, &len),"XRES retrieved.\n", "failed to retrieve XRES.\n");
			test_comp_str( tmp_str, (unsigned char *)row[3], len, "XRES");

			/*check AUTN*/
			SS_CHECK( ss_get_autn( tmp_gavp, &tmp_str, &len),"AUTN retrieved.\n", "failed to retrieve AUTN.\n");
			test_comp_str( tmp_str, (unsigned char *)row[4], len, "AUTN");

			/*check Confidentiality-Key*/
			SS_CHECK( ss_get_confidentiality_key( tmp_gavp, &tmp_str, &len), "Confidentiality-Key retrieved.\n", "failed to retrieve Confidentiality-Key.\n");
			test_comp_str( tmp_str, (unsigned char *)row[5], len, "Confidentiality-Key");
	
			/*check Integrity-Key*/
			SS_CHECK( ss_get_integrity_key( tmp_gavp, &tmp_str, &len), "Integrity-Key retrieved.\n", "failed to retrieve Integrity-Key.\n");	
			test_comp_str( tmp_str, (unsigned char *)row[6], len, "Integrity-Key");

			/*Get next UTRAN-Vector AVP*/
			SS_WCHECK( ss_get_gavp_next_utran_vector(tmp_gavp, &tmp_gavp2), "UTRAN-Vector next retrieved.\n", "Failed to retrieve next UTRAN-Vector.\n", goto end);
			tmp_gavp = tmp_gavp2;
		}		
	}

end:
	mysql_free_result(res);
	mysql_close(conn);		
}

/*Get E-UTRAN auth vector from db and compare it with received values*/
static void check_eutran_vect(struct avp *gavp, char * imsi){

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL; 
	unsigned char *tmp_str = NULL;
	unsigned32 tmp_u = 0;
	size_t len = 0;
	char buf[70] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res = NULL;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi)) return;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to subscription data*/	
	sprintf(buf,"select * from EUTRANVector where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "E-UTRANVector data retrieved from db.\n", "Failed to retrieve E-UTRANVector data from database.\n"); 
	
	if((row = mysql_fetch_row(res))!= NULL){

		/*Get E-UTRAN-Vector AVP*/
		SS_WCHECK( ss_get_gavp_e_utran_vector(gavp, &tmp_gavp), "E-UTRAN-Vector retrieved.\n", "Failed to retrieve E-UTRAN-Vector.\n", return);
		
		while(tmp_gavp){
		
			/*check Item-Number*/
			SS_WCHECK( ss_get_item_number( tmp_gavp, &tmp_u), "Item-Number retrieved.\n", "failed to retrieve Item-Number.\n", NULL);
			test_comp_uint( tmp_u, (uint32_t)(strtoul(row[1], NULL, 10)), "Item-Number");

			/*check RAND*/
			SS_CHECK( ss_get_rand( tmp_gavp, &tmp_str, &len), "RAND retrieved.\n", "failed to retrieve RAND.\n");
			test_comp_str( tmp_str, (unsigned char *)row[2], len, "RAND");

			/*check XRES*/
			SS_CHECK( ss_get_xres( tmp_gavp, &tmp_str, &len),"XRES retrieved.\n", "failed to retrieve XRES.\n");
			test_comp_str( tmp_str, (unsigned char *)row[3], len, "XRES");

			/*check AUTN*/
			SS_CHECK( ss_get_autn( tmp_gavp, &tmp_str, &len),"AUTN retrieved.\n", "failed to retrieve AUTN.\n");
			test_comp_str( tmp_str, (unsigned char *)row[4], len, "AUTN");

			/*check KASME*/
			SS_CHECK( ss_get_kasme( tmp_gavp, &tmp_str, &len), "KASME retrieved.\n", "failed to retrieve KASME.\n");
			test_comp_str( tmp_str, (unsigned char *)row[5], len, "KASME");
	
			/*Get next E-UTRAN-Vector AVP*/
			SS_WCHECK( ss_get_gavp_next_e_utran_vector(tmp_gavp, &tmp_gavp2), "E-UTRAN-Vector next retrieved.\n", "Failed to next retrieve E-UTRAN-Vector.\n", goto end);
			tmp_gavp = tmp_gavp2;
		}		
	}

end:
	mysql_free_result(res);
	mysql_close(conn);		
}

/*Get GERAN auth vector from db and compare it with received values*/
static void check_geran_vect(struct avp *gavp, char * imsi){

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL; 
	unsigned char *tmp_str = NULL;
	unsigned32 tmp_u = 0;
	size_t len = 0;
	char buf[70] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res = NULL;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi)) return;
	
	/*connect to database*/
	test_connect_db(&conn);

	/*Prepare mysql statement to subscription data*/	
	sprintf(buf,"select * from GERANVector where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(test_get_qry_res(conn, buf, &res), "GERANVector data retrieved from db.\n", "Failed to retrieve GERANVector data from database.\n"); 
	
	if((row = mysql_fetch_row(res))!= NULL){

		/*Get GERAN-Vector AVP*/
		SS_WCHECK( ss_get_gavp_geran_vector(gavp, &tmp_gavp), "GERAN-Vector retrieved.\n", "Failed to retrieve GERAN-Vector.\n", return);
		
		while(tmp_gavp){
		
			/*check Item-Number*/
			SS_WCHECK( ss_get_item_number( tmp_gavp, &tmp_u), "Item-Number retrieved.\n", "failed to retrieve Item-Number.\n", NULL);
			test_comp_uint( tmp_u, (uint32_t)(strtoul(row[1], NULL, 10)), "Item-Number");

			/*check RAND*/
			SS_CHECK( ss_get_rand( tmp_gavp, &tmp_str, &len), "RAND retrieved.\n", "failed to retrieve RAND.\n");
			test_comp_str( tmp_str, (unsigned char *)row[2], len, "RAND");

			/*check SRES*/
			SS_CHECK( ss_get_sres( tmp_gavp, &tmp_str, &len),"SRES retrieved.\n", "failed to retrieve SRES.\n");
			test_comp_str( tmp_str, (unsigned char *)row[3], len, "SRES");

			/*check Kc*/
			SS_CHECK( ss_get_kc( tmp_gavp, &tmp_str, &len),"Kc retrieved.\n", "failed to retrieve Kc.\n");
			test_comp_str( tmp_str, (unsigned char *)row[4], len, "Kc");
	
			/*Get next GERAN-Vector AVP*/
			SS_WCHECK( ss_get_gavp_next_geran_vector(tmp_gavp, &tmp_gavp2), "GERAN-Vector next retrieved.\n", "Failed to next retrieve GERAN-Vector.\n", goto end);
			tmp_gavp = tmp_gavp2;
		}		
	}

end:
	mysql_free_result(res);
	mysql_close(conn);		
}

/*check Authentication-Info*/
static void check_auth_info(struct msg *msg, char *imsi){

	struct avp *tmp_gavp = NULL;
	
	if((!msg) || (!imsi)) return;

	fprintf(stdout, COLOR_YELLOW"\nSTART : COMPARING VALUES RECEIVED IN AIA MESSAGE..."COLOR_YELLOW"\n");

	/*Get Authentication-Info AVP*/
	SS_WCHECK( ss_get_gavp_authentication_info(msg, &tmp_gavp), "Authentication-Info extracted.\n", "failed to extract Authentication-Info.\n", return;);

	/*Get E-UTRAN-Vector*/
	check_eutran_vect( tmp_gavp, imsi);	

	/*Get UTRAN-Vector*/
	check_utran_vect( tmp_gavp, imsi);

	/*Get GERAN-Vector*/
	check_geran_vect( tmp_gavp, imsi);

	fprintf(stdout, COLOR_YELLOW"FINISHED : COMPARING VALUES RECEIVED IN AIA MESSAGE DONE."COLOR_YELLOW"\n\n");
}

/*check EPS-User-State*/
static void check_eps_usr_state(struct msg *msg){
	
	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	int32_t tmp_i = 0;

	if(!msg) return;

	/*Get EPS-User-State AVP*/
	SS_CHECK( ss_get_gavp_eps_user_state(msg, &tmp_gavp), "EPS-User-State Retrieved.\n", "Failed to Retrieve EPS-User-State.\n");

	/*Get MME-User-State AVP*/
	SS_CHECK( ss_get_gavp_mme_user_state(tmp_gavp, &tmp_gavp2), "MME-User-State Retrieved.\n", "Failed to Retrieve MME-User-State.\n");
	
	/*Get User-State*/
	SS_CHECK( ss_get_user_state(tmp_gavp2, &tmp_i), "User-State Retrieved.\n", "Failed to Retrieve User-State.\n");
	/*compare User-State value*/
	test_comp_int( tmp_i, (int32_t)gb_mme_user_state, "User-State");
}


/*check Local-Time-Zone*/
static void check_local_time_zone(struct msg *msg){

	struct avp *tmp_gavp = NULL;
	unsigned char *tmp_str = NULL;
	int32_t tmp_i = 0;
	size_t len = 0;
	
	if(!msg) return;

	/*Get Local-Time-Zone*/ 
	SS_WCHECK( ss_get_gavp_local_time_zone(msg, &tmp_gavp), "Local-Time-Zone Retrieved.\n", "Failed to Retrieve Local-Time-Zone.\n", return);

	/*Get Time-Zone*/
	SS_CHECK( ss_get_time_zone(tmp_gavp, &tmp_str, &len), "Time-Zone Retrieved.\n", "Failed to Retrieve Time-Zone.\n");
	/*compare Time-Zone value*/
	test_comp_str( tmp_str, gb_time_zone, len,"Time-Zone");

	/*Get Daylight-Saving-Time*/
	SS_CHECK( ss_get_daylight_saving_time(tmp_gavp, &tmp_i), "Daylight-Saving-Time Retrieved.\n", "Failed to Retrieve Daylight-Saving-Time.\n");
	/*compare Daylight-Saving-Time value*/
	test_comp_int( tmp_i, (int32_t)gb_daylight_saving_time, "Daylight-Saving-Time");

}

/*Check ULA message values*/
static void check_ula(struct msg *msg, char *imsi){

	octetstring **reset_ids = NULL;
	unsigned32 ulaflg = 0;
	size_t size = 0;
	size_t *len_arr = NULL;

	if((!msg) || (!imsi)) return;

	fprintf(stdout, COLOR_YELLOW"\nSTART : COMPARING VALUES RECEIVED IN ULA MESSAGE..."COLOR_YELLOW"\n");

	/*check common content of answer msg*/
	check_answer(msg);	

	/*Extract ULA-Flags*/
	SS_WCHECK( ss_get_ula_flags_msg( msg, &ulaflg), "ULA-Flags retrieved.\n", "Failed to retrieve ULA-Flags.\n", NULL);

	/*compare ULA-Flags value*/
	test_comp_uint( ulaflg, gb_ula_flags, "ULA-Flags");

	/*Check subscription data*/
	test_check_subsc_data(msg, imsi);

	/*Extract Reset-Id*/
	SS_WCHECK( ss_get_reset_id_array(msg, &reset_ids, &len_arr, &size), "Reset-Id retrieved.\n", "Failed to retrieve Reset-Id.\n", NULL);	
	while(size){
		
		/*compare Reset-Id values*/
		test_comp_str( reset_ids[size-1], gb_reset_ids[size-1], len_arr[size-1], "Reset-Id");

		size --;
	}
	if(reset_ids) free(reset_ids);
	if(len_arr) free(len_arr);

	fprintf(stdout, COLOR_YELLOW"FINISHED : COMPARING VALUES RECEIVED IN ULA MESSAGE DONE."COLOR_YELLOW"\n\n");
}

/*This is register when ULR request is send and when the corresponding answer is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_ulr(void * data, struct msg ** msg){

	static int check_shut_down = 0;

	/*Check ULA message values*/
	check_ula( *msg, ((char *)data));

	/* Free the message */
	fd_msg_free(*msg);
	*msg = NULL;
	
	/*update cout of message received so far*/
	check_shut_down ++;

	if(4 == check_shut_down){
		fprintf(stdout,COLOR_GREEN"ULR/ULA MESSAGE TEST COMPLETED.\n.Sending core shutdown signal."ANSI_COLOR_RESET"\n");
		SS_CHECK(fd_core_shutdown(),"CORE SHUT DOWN\n", "FAILED TO SHUTDOWN CORE.\n");
	}
}

/*This is register when CLR request is send and when the corresponding answer is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_clr(void * data, struct msg ** msg){

	static int check_shut_down = 0;

	/*check content of answer msg*/
	check_answer(*msg);	

	/* Free the message */
	fd_msg_free(*msg);
	*msg = NULL;
	
	/*update cout of message received so far*/
	check_shut_down ++;

	if(1 == check_shut_down){
		fprintf(stdout,COLOR_GREEN"CLR/CLA MESSAGE TEST COMPLETED.\n.Sending core shutdown signal."ANSI_COLOR_RESET"\n");
		SS_CHECK(fd_core_shutdown(),"CORE SHUT DOWN\n", "FAILED TO SHUTDOWN CORE.\n");
	}
}

/*This is register when request is AIR send and when the corresponding answer is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_air(void * data, struct msg ** msg){

	static int check_shut_down = 0;

	/*check common content of answer msg*/
	check_answer(*msg);	

	/*check Authentication-Info*/
	check_auth_info(*msg, (char *)data);

	/* Free the message */
	fd_msg_free(*msg);
	*msg = NULL;
	
	/*update cout of message received so far*/
	check_shut_down ++;

	if(1 == check_shut_down){
		fprintf(stdout,COLOR_GREEN"AIR/AIA MESSAGE TEST COMPLETED.\n. Sending core shutdown signal."ANSI_COLOR_RESET"\n");
		SS_CHECK(fd_core_shutdown(),"CORE SHUT DOWN\n", "FAILED TO SHUTDOWN CORE.\n");
	}
}

/*This is register when IDR request is send and when the corresponding answer is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_idr(void * data, struct msg ** msg){

	static int check_shut_down = 0;
	int32_t tmp_i = 0;
	unsigned char *tmp_str = NULL;
	uint32_t tmp_u = 0;
	size_t len = 0;

	/*check common content of answer msg*/
	check_answer(*msg);	

	/*check IMS-Voice-Over-PS-Sessions-Supported*/
	SS_WCHECK( ss_get_ims_voice_over_ps_sessions_supported_msg(*msg, &tmp_i), "IMS-Voice-Over-PS-Sessions-Supported retrieved.\n", "Failed to retrieve IMS-Voice-Over-PS-Sessions-Supported.\n", NULL);
	/*compare IMS-Voice-Over-PS-Sessions-Supported values*/
	test_comp_int( tmp_i, (int32_t)gb_ims_vop_sessions_supported, "IMS-Voice-Over-PS-Sessions-Supported");

	/*Get Last-UE-Activity-Time*/
	SS_WCHECK( ss_get_last_ue_activity_time_msg( *msg, &tmp_str, &len), "Last-UE-Activity-Time retrieved.\n", "Failed to retrieve Last-UE-Activity-Time.\n", NULL);
	/*compare Last-UE-Activity-Time values*/
	test_comp_str( tmp_str, gb_last_ue_activity_time, len, "Last-UE-Activity-Time");

	/*Get RAT-Type*/
	SS_WCHECK( ss_get_rat_type_msg(*msg, (int32_t *)&tmp_i), "RAT-Type retrieved.\n", "Failed to retrieve RAT-Type.\n", NULL);
	/*compare RAT-Type value*/
	test_comp_int( tmp_i, gb_rat_type, "RAT-Type");

	/*Get IDA-Flags*/
	SS_WCHECK( ss_get_ida_flags_msg(*msg, &tmp_u), "IDA-Flags retrieved.\n", "Failed to retrieve IDA-Flags.\n", NULL);
	/*compare IDA-Flags value*/
	test_comp_uint( tmp_u, gb_ida_flags, "IDA-Flags");

	/*Get EPS-User-State*/
	check_eps_usr_state(*msg);

	/*Get EPS-Location-Information*/
	test_check_eps_location_info(*msg);

	/*Get Local-Time-Zone*/
	check_local_time_zone(*msg);

	/* Free the message */
	fd_msg_free(*msg);
	*msg = NULL;
	
	/*update cout of message received so far*/
	check_shut_down ++;

	if(1 == check_shut_down){
		fprintf(stdout,COLOR_GREEN"IDR/IDA MESSAGE TEST COMPLETED.\n. Sending core shutdown signal."ANSI_COLOR_RESET"\n");
		SS_CHECK(fd_core_shutdown(),"CORE SHUT DOWN\n", "FAILED TO SHUTDOWN CORE.\n");
	}
}

/*This is register when DSR request is send and when the corresponding answer is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_dsr(void * data, struct msg ** msg){

	static int check_shut_down = 0;
	unsigned32 dsa_flgs = 0;

	/*check common content of answer msg*/
	check_answer(*msg);	

	/*check DSA-Flags*/
	SS_WCHECK( ss_get_dsa_flags_msg( *msg, &dsa_flgs), "DSA-Flags retrieved.\n", "Failed to retrieve DSA-Flags.\n", NULL);
	/*compare DSA-Flags value*/
	test_comp_uint( dsa_flgs, gb_dsa_flags, "DSA-Flags");

	/* Free the message */
	fd_msg_free(*msg);
	*msg = NULL;
	
	/*update cout of message received so far*/
	check_shut_down ++;

	if(1 == check_shut_down){
		fprintf(stdout,COLOR_GREEN"DSR/DSA MESSAGE TEST COMPLETED.\n. Sending core shutdown signal."ANSI_COLOR_RESET"\n");
		SS_CHECK(fd_core_shutdown(),"CORE SHUT DOWN\n", "FAILED TO SHUTDOWN CORE.\n");
	}
}

/*This is register when PUR request is send and when the corresponding answer is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_pur(void * data, struct msg ** msg){

	static int check_shut_down = 0;
	unsigned32 pua_flgs = 0;

	/*check common content of answer msg*/
	check_answer(*msg);	

	/*check PUA-Flags*/
	SS_WCHECK( ss_get_pua_flags_msg( *msg, &pua_flgs), "PUA-Flags retrieved.\n", "Failed to retrieve PUA-Flags.\n", NULL);
	/*compare PUA-Flags value*/
	test_comp_uint( pua_flgs, gb_pua_flags, "PUA-Flags");

	/* Free the message */
	fd_msg_free(*msg);
	*msg = NULL;
	
	/*update cout of message received so far*/
	check_shut_down ++;

	if(1 == check_shut_down){
		fprintf(stdout,COLOR_GREEN"PUR/PUA MESSAGE TEST COMPLETED.\n. Sending core shutdown signal."ANSI_COLOR_RESET"\n");
		SS_CHECK(fd_core_shutdown(),"CORE SHUT DOWN\n", "FAILED TO SHUTDOWN CORE.\n");
	}
}

/*This is register when RSR request is send and when the corresponding answer is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_rsr(void * data, struct msg ** msg){

	static int check_shut_down = 0;

	/*check common content of answer msg*/
	check_answer(*msg);	

	/* Free the message */
	fd_msg_free(*msg);
	*msg = NULL;
	
	/*update cout of message received so far*/
	check_shut_down ++;

	if(1 == check_shut_down){
		fprintf(stdout,COLOR_GREEN"RSR/RSA MESSAGE TEST COMPLETED.\n. Sending core shutdown signal."ANSI_COLOR_RESET"\n");
		SS_CHECK(fd_core_shutdown(),"CORE SHUT DOWN\n", "FAILED TO SHUTDOWN CORE.\n");
	}
}

/*This is register when NOR request is send and when the corresponding answer is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_nor(void * data, struct msg ** msg){

	static int check_shut_down = 0;

	/*check common content of answer msg*/
	check_answer(*msg);	

	/* Free the message */
	fd_msg_free(*msg);
	*msg = NULL;
	
	/*update cout of message received so far*/
	check_shut_down ++;

	if(1 == check_shut_down){
		fprintf(stdout,COLOR_GREEN"NOR/NOA MESSAGE TEST COMPLETED.\n. Sending core shutdown signal."ANSI_COLOR_RESET"\n");
		SS_CHECK(fd_core_shutdown(),"CORE SHUT DOWN\n", "FAILED TO SHUTDOWN CORE.\n");
	}
}
