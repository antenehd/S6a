
#include "ssix_interface.h"
#include "test.h"

static int get_experimental_result(struct msg * msg, unsigned32 * vend_id, unsigned32 * result_code){

	struct avp * tmp_gavp;

	if((!msg) || (!vend_id) || (!result_code))
		return 1;

	/*Extract experimental result AVP from message*/
	SS_WCHECK( ss_get_gavp_experimental_result(msg, &tmp_gavp), "Experimental result AVP extracted.\n", "Failed to extract experimental result.n", return 1;);

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
	else if(code == 5001)
		strcpy(*result, "DIAMETER_ERROR_USER_UNKNOWN");
	else if(code == 5421)
		strcpy(*result, "DIAMETER_ERROR_RAT_NOT_ALLOWED");	
	else if(code == 5004)
		strcpy(*result, "DIAMETER_ERROR_ROAMING_NOT_ALLOWED");
	else if(code == 3)
		strcpy(*result, "ODB_HPLMN_APN");
	else
		strcpy(*result, "UNKNOW or NOT PRESENT IN MESSAGE");	
}



/*This is register when request is send and when the corresponding anser is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb(void * data, struct msg ** msg){

	unsigned32  result_code = 0;
	unsigned32 exp_result_code = 0;
	integer32 err_diag = 0;
	unsigned32 vend_id = 0;
	diameterid * origin = NULL;
	char * code_str = NULL;
	int check_shut_down = 0;

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
	if(code_str){

		fprintf(stdout, "OK : Result code %s\n", code_str);

		/*this is used to check weather to wait or shutdown the diameter deamon*/
		if((strcmp(code_str, "DIAMETER_SUCCESS")) == 0)
			check_shut_down = 1;
		
		free(code_str);
		code_str = NULL;
	}

	/*extract experimental result child avp values*/
	if( get_experimental_result(*msg, &vend_id, &exp_result_code) == 0){
		
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

	/* Free the message */
	fd_msg_free(*msg);
	*msg = NULL;

	if(check_shut_down){
		fprintf(stdout,COLOR_GREEN"Sending core shutdown signal."ANSI_COLOR_RESET"\n");
		SS_CHECK(fd_core_shutdown(),"CORE SHUT DOWN\n", "FAILED TO SHUTDOWN CORE.\n");
	}
}
