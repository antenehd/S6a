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

static void check_answer(struct msg **msg){

	unsigned32  result_code = 0;
	unsigned32 exp_result_code = 0;
	integer32 err_diag = 0;
	unsigned32 vend_id = 0;
	diameterid * origin = NULL;
	unsigned32 *feature_list_id = NULL;
	unsigned32 *feature_list = NULL;
	size_t size = 0;	
	char * code_str = NULL;
	size_t len = 0;

	if(!msg){
		
		fprintf(stderr,COLOR_YELLOW"\nError : Answer received with empty message."ANSI_COLOR_RESET"\n");
		return;
	}
		
	/*extract origin host name*/
	SS_CHECK( ss_get_origin_host_msg(*msg, &origin, &len), "", "Failed to extract origin host from answer message.\n");
	fprintf(stdout, COLOR_GREEN"\nOK : Answer received from %s"ANSI_COLOR_RESET"\n", (char *)origin);

	/*extract result-code*/
	SS_WCHECK( ss_get_result_code_msg(*msg, &result_code), "", "Failed to extract result code from answer message.\n", NULL);

	/*change result code to its string value*/
	code_2_str((int)result_code, &code_str);
	if(NULL != code_str){

		fprintf(stdout, "OK : Result code %s\n", code_str);

		free(code_str);
		code_str = NULL;
	}

	/*extract experimental result child avp values*/
	if( 0 == (get_experimental_result(*msg, &vend_id, &exp_result_code))){
		
		/*change result code to its string value*/
		code_2_str((int)exp_result_code, &code_str);

		if(code_str){

			fprintf(stdout, "OK : Experimetal Result:  exp-result-code - %s   vendor_id - %d\n", code_str, vend_id);
			free(code_str);
			code_str = NULL;
		}
	}

	/*extract Error diagnostic from message*/
	SS_WCHECK( ss_get_error_diagnostic_msg(*msg, &err_diag), "Error-Diagnostic value extracted.\n", "Failed to extract error diagnostic.\n", NULL);

	if(err_diag){

		/*change result code to its string value*/
	    code_2_str(err_diag, &code_str);

		if(code_str){
			fprintf(stdout, "OK : Error Diagnostic  %s\n", code_str);
			free(code_str);
			code_str = NULL;
		}
	}

	/*Extract Supported-Features AVP*/
	test_get_supported_features(*msg, &feature_list_id, &feature_list, &size);
	if(feature_list_id) free(feature_list_id);
	if(feature_list) free(feature_list);
} 

/*check Authentication-Info*/
static void check_auth_info(struct msg *msg){

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	struct avp *tmp_gavp3 = NULL;
	unsigned32 chk_u32 = 0;
	octetstring * chk_oct = NULL; 	
	size_t len = 0;

	if(!msg) return;

	/*Get Authentication-Info AVP*/
	SS_WCHECK( ss_get_gavp_authentication_info(msg, &tmp_gavp), "Authentication-Info extracted.\n", "failed to extract Authentication-Info.\n", return;);

	/*Get E-UTRAN-Vector*/
	SS_WCHECK( ss_get_gavp_e_utran_vector(tmp_gavp, &tmp_gavp2), "E-UTRAN-Vector extracted.\n", "failed to extract E-UTRAN-Vector.\n", NULL);
	while(tmp_gavp2){

		/*Get Item-Number*/
		SS_WCHECK( ss_get_item_number(tmp_gavp2, &chk_u32), "Item-Number extracted.\n", "failed to extract Item-Number.\n", NULL);

		/*Get RAND*/
		SS_WCHECK( ss_get_rand(tmp_gavp2, &chk_oct, &len), "RAND extracted.\n", "failed to extract RAND.\n", NULL);
		

		/*Get XRES*/
		SS_WCHECK( ss_get_xres(tmp_gavp2, &chk_oct, &len), "XRES extracted.\n", "failed to extract XRES.\n", NULL);

		/*Get AUTN*/
		SS_WCHECK( ss_get_autn(tmp_gavp2, &chk_oct, &len), "AUTN extracted.\n", "failed to extract AUTN.\n", NULL);

		/*Get KASME*/
		SS_WCHECK( ss_get_kasme(tmp_gavp2, &chk_oct, &len), "KASME extracted.\n", "failed to extract KASME.\n", NULL);


		/*Get the next E-UTRAN-Vector*/
		SS_WCHECK( ss_get_gavp_next_e_utran_vector(tmp_gavp2, &tmp_gavp3), "next E-UTRAN-Vector extracted.\n", "failed to extract next E-UTRAN-Vector.\n", NULL);

		tmp_gavp2 = tmp_gavp3;
		tmp_gavp3 = NULL;	
	}

	/*Get UTRAN-Vector*/
	SS_WCHECK( ss_get_gavp_utran_vector(tmp_gavp, &tmp_gavp2), "UTRAN-Vector extracted.\n", "failed to extract UTRAN-Vector.\n", NULL);
	while(tmp_gavp2){

		/*Get Item-Number*/
		SS_WCHECK( ss_get_item_number(tmp_gavp2, &chk_u32), "Item-Number extracted.\n", "failed to extract Item-Number.\n", NULL);

		/*Get RAND*/
		SS_WCHECK( ss_get_rand(tmp_gavp2, &chk_oct, &len), "RAND extracted.\n", "failed to extract RAND.\n", NULL);

		/*Get XRES*/
		SS_WCHECK( ss_get_xres(tmp_gavp2, &chk_oct, &len), "XRES extracted.\n", "failed to extract XRES.\n", NULL);

		/*Get AUTN*/
		SS_WCHECK( ss_get_autn(tmp_gavp2, &chk_oct, &len), "AUTN extracted.\n", "failed to extract AUTN.\n", NULL);

		/*Get Confidentiality-Key*/
		SS_WCHECK( ss_get_confidentiality_key(tmp_gavp2, &chk_oct, &len), "Confidentiality-Key extracted.\n", "failed to extract Confidentiality-Key.\n", NULL);

		/*Get Integrity-Key*/
		SS_WCHECK( ss_get_integrity_key(tmp_gavp2, &chk_oct, &len), "Integrity-Key extracted.\n", "failed to extract Integrity-Key.\n", NULL);

		/*Get the next UTRAN-Vector*/
		SS_WCHECK( ss_get_gavp_next_utran_vector(tmp_gavp2, &tmp_gavp3), "next UTRAN-Vector extracted.\n", "failed to extract next UTRAN-Vector.\n", NULL);	
		
		tmp_gavp2 = tmp_gavp3;
		tmp_gavp3 = NULL;
	}

	/*Get GERAN-Vector*/
	SS_WCHECK( ss_get_gavp_geran_vector(tmp_gavp, &tmp_gavp2), "GERAN-Vector extracted.\n", "failed to extract GERAN-Vector.\n", NULL);
	while(tmp_gavp2){

		/*Get Item-Number*/
		SS_WCHECK( ss_get_item_number(tmp_gavp2, &chk_u32), "Item-Number extracted.\n", "failed to extract Item-Number.\n", NULL);

		/*Get RAND*/
		SS_WCHECK( ss_get_rand(tmp_gavp2, &chk_oct, &len), "RAND extracted.\n", "failed to extract RAND.\n", NULL);

		/*Get SRES*/
		SS_WCHECK( ss_get_sres(tmp_gavp2, &chk_oct, &len), "SRES extracted.\n", "failed to extract SRES.\n", NULL);

		/*Get Kc*/
		SS_WCHECK( ss_get_kc(tmp_gavp2, &chk_oct, &len), "Kc extracted.\n", "failed to extract Kc.\n", NULL);

		/*Get the next GERAN-Vector*/
		SS_WCHECK( ss_get_gavp_next_geran_vector(tmp_gavp2, &tmp_gavp3), "next GERAN-Vector extracted.\n", "failed to extract next GERAN-Vector.\n", NULL);	
		
		tmp_gavp2 = tmp_gavp3;
		tmp_gavp3 = NULL;
	}
	
}

/*check EPS-User-State*/
static void check_eps_usr_state(struct msg *msg){
	
	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	enum user_state mme_user_state = 0;
	if(!msg) return;

	/*Get EPS-User-State AVP*/
	SS_CHECK( ss_get_gavp_eps_user_state(msg, &tmp_gavp), "EPS-User-State Retrieved.\n", "Failed to Retrieve EPS-User-State.\n");

	/*Get MME-User-State AVP*/
	SS_CHECK( ss_get_gavp_mme_user_state(tmp_gavp, &tmp_gavp2), "MME-User-State Retrieved.\n", "Failed to Retrieve MME-User-State.\n");

	/*Get User-State*/
	SS_CHECK( ss_get_user_state(tmp_gavp2, (int32_t *)&mme_user_state), "User-State Retrieved.\n", "Failed to Retrieve User-State.\n");
}


/*check Local-Time-Zone*/
static void check_local_time_zone(struct msg *msg){

	struct avp *tmp_gavp = NULL;
	utf8string *time_zone = NULL;
	enum daylight_saving_time day_sv_tm = 0;
	size_t len = 0;
	
	if(!msg) return;

	/*Get Local-Time-Zone*/ 
	SS_WCHECK( ss_get_gavp_local_time_zone(msg, &tmp_gavp), "Local-Time-Zone Retrieved.\n", "Failed to Retrieve Local-Time-Zone.\n", return);

	/*Get Time-Zone*/
	SS_CHECK( ss_get_time_zone(tmp_gavp, &time_zone, &len), "Time-Zone Retrieved.\n", "Failed to Retrieve Time-Zone.\n");

	/*Get Daylight-Saving-Time*/
	SS_CHECK( ss_get_daylight_saving_time(tmp_gavp, (int32_t *)&day_sv_tm), "Daylight-Saving-Time Retrieved.\n", "Failed to Retrieve Daylight-Saving-Time.\n");

}

/*This is register when ULR request is send and when the corresponding answer is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_ulr(void * data, struct msg ** msg){

	static int check_shut_down = 0;

	octetstring **reset_ids = NULL;
	unsigned32 ulaflg = 0;
	size_t size = 0;
	size_t *len_arr = NULL;

	/*check content of answer msg*/
	check_answer(msg);	

	/*Extract ULA-Flags*/
	SS_WCHECK( ss_get_ula_flags_msg( *msg, &ulaflg), "ULA-Flags retrieved.\n", "Failed to retrieve ULA-Flags.\n", NULL);

	/*Extract subscription data*/
	test_check_subsc_data(*msg);

	/*Extract Reset-Id*/
	SS_WCHECK( ss_get_reset_id_array(*msg, &reset_ids, &len_arr, &size), "Reset-Id retrieved.\n", "Failed to retrieve Reset-Id.\n", NULL);
	if(reset_ids) free(reset_ids);
	if(len_arr) free(len_arr);
	

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
	check_answer(msg);	

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
	check_answer(msg);	

	/*check Authentication-Info*/
	check_auth_info(*msg);

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
	enum ims_voice_over_ps_sessions_supported ims_vop_supp = 0;	
	ss_time * last_ue_act_time = NULL; 
	enum rat_type rat_type = 0;
	unsigned32 ida_flgs = 0;
	size_t len = 0;

	/*check common content of answer msg*/
	check_answer(msg);	

	/*check IMS-Voice-Over-PS-Sessions-Supported*/
	SS_WCHECK( ss_get_ims_voice_over_ps_sessions_supported_msg(*msg, (int32_t *)&ims_vop_supp), "IMS-Voice-Over-PS-Sessions-Supported retrieved.\n", "Failed to retrieve IMS-Voice-Over-PS-Sessions-Supported.\n", NULL);

	/*Get Last-UE-Activity-Time*/
	SS_WCHECK( ss_get_last_ue_activity_time_msg( *msg, &last_ue_act_time, &len), "Last-UE-Activity-Time retrieved.\n", "Failed to retrieve Last-UE-Activity-Time.\n", NULL);

	/*Get RAT-Type*/
	SS_WCHECK( ss_get_rat_type_msg(*msg, (int32_t *)&rat_type), "RAT-Type retrieved.\n", "Failed to retrieve RAT-Type.\n", NULL);

	/*Get IDA-Flags*/
	SS_WCHECK( ss_get_ida_flags_msg(*msg, &ida_flgs), "IDA-Flags retrieved.\n", "Failed to retrieve IDA-Flags.\n", NULL);

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
	check_answer(msg);	

	/*check DSA-Flags*/
	SS_WCHECK( ss_get_dsa_flags_msg( *msg, &dsa_flgs), "DSA-Flags retrieved.\n", "Failed to retrieve DSA-Flags.\n", NULL);

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
	check_answer(msg);	

	/*check PUA-Flags*/
	SS_WCHECK( ss_get_pua_flags_msg( *msg, &pua_flgs), "PUA-Flags retrieved.\n", "Failed to retrieve PUA-Flags.\n", NULL);

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
	check_answer(msg);	

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
	check_answer(msg);	

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
