
#include "ssix_interface.h"
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

	if(!msg){
		
		fprintf(stderr,COLOR_YELLOW"\nError : Answer received with emtyp message."ANSI_COLOR_RESET"\n");
		return;
	}
		
	/*extract origin host name*/
	SS_CHECK( ss_get_origin_host(*msg, &origin), "", "Failed to extract origin host from answer message.\n");
	fprintf(stdout, COLOR_GREEN"\nOK : Answer received from %s"ANSI_COLOR_RESET"\n", (char *)origin);

	/*extract result-code*/
	SS_WCHECK( ss_get_result_code(*msg, &result_code), "", "Failed to extract result code from answer message.\n", NULL);

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
	SS_WCHECK( ss_get_error_diagnostic(*msg, &err_diag), "Error-Diagnostic value extracted.\n", "Failed to extract error diagnostic.\n", NULL);

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

	if(!msg) return;

	/*Get Authentication-Info AVP*/
	SS_WCHECK( ss_get_gavp_authentication_info(msg, &tmp_gavp), "Authentication-Info extracted.\n", "failed to extract Authentication-Info.\n", return;);

	/*Get E-UTRAN-Vector*/
	SS_WCHECK( ss_get_gavp_e_utran_vector(tmp_gavp, &tmp_gavp2), "E-UTRAN-Vector extracted.\n", "failed to extract E-UTRAN-Vector.\n", NULL);
	while(tmp_gavp2){

		/*Get Item-Number*/
		SS_WCHECK( ss_get_item_number(tmp_gavp2, &chk_u32), "Item-Number extracted.\n", "failed to extract Item-Number.\n", NULL);

		/*Get RAND*/
		SS_WCHECK( ss_get_rand(tmp_gavp2, &chk_oct), "RAND extracted.\n", "failed to extract RAND.\n", NULL);
		

		/*Get XRES*/
		SS_WCHECK( ss_get_xres(tmp_gavp2, &chk_oct), "XRES extracted.\n", "failed to extract XRES.\n", NULL);

		/*Get AUTN*/
		SS_WCHECK( ss_get_autn(tmp_gavp2, &chk_oct), "AUTN extracted.\n", "failed to extract AUTN.\n", NULL);

		/*Get KASME*/
		SS_WCHECK( ss_get_kasme(tmp_gavp2, &chk_oct), "KASME extracted.\n", "failed to extract KASME.\n", NULL);


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
		SS_WCHECK( ss_get_rand(tmp_gavp2, &chk_oct), "RAND extracted.\n", "failed to extract RAND.\n", NULL);

		/*Get XRES*/
		SS_WCHECK( ss_get_xres(tmp_gavp2, &chk_oct), "XRES extracted.\n", "failed to extract XRES.\n", NULL);

		/*Get AUTN*/
		SS_WCHECK( ss_get_autn(tmp_gavp2, &chk_oct), "AUTN extracted.\n", "failed to extract AUTN.\n", NULL);

		/*Get Confidentiality-Key*/
		SS_WCHECK( ss_get_confidentiality_key(tmp_gavp2, &chk_oct), "Confidentiality-Key extracted.\n", "failed to extract Confidentiality-Key.\n", NULL);

		/*Get Integrity-Key*/
		SS_WCHECK( ss_get_integrity_key(tmp_gavp2, &chk_oct), "Integrity-Key extracted.\n", "failed to extract Integrity-Key.\n", NULL);

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
		SS_WCHECK( ss_get_rand(tmp_gavp2, &chk_oct), "RAND extracted.\n", "failed to extract RAND.\n", NULL);

		/*Get SRES*/
		SS_WCHECK( ss_get_sres(tmp_gavp2, &chk_oct), "SRES extracted.\n", "failed to extract SRES.\n", NULL);

		/*Get Kc*/
		SS_WCHECK( ss_get_kc(tmp_gavp2, &chk_oct), "Kc extracted.\n", "failed to extract Kc.\n", NULL);

		/*Get the next GERAN-Vector*/
		SS_WCHECK( ss_get_gavp_next_geran_vector(tmp_gavp2, &tmp_gavp3), "next GERAN-Vector extracted.\n", "failed to extract next GERAN-Vector.\n", NULL);	
		
		tmp_gavp2 = tmp_gavp3;
		tmp_gavp3 = NULL;
	}
	
}

/*This is register when ULR request is send and when the corresponding ansWer is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_ulr(void * data, struct msg ** msg){

	static int check_shut_down = 0;

	/*check content of answer msg*/
	check_answer(msg);	

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

/*This is register when request is send and when the corresponding anser is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
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

/*This is register when request is send and when the corresponding anser is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
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
