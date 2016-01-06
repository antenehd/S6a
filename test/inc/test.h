
#ifndef SS_TEST_H
#define SS_TEST_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define SS_SET_I32( func_callbk, int_val, string_val, succ_string, err_string)	{		 \
	int_val=atoi(string_val);															 \
	SS_CHECK(func_callbk, succ_string, err_string);										 \
}

#define SS_SET_U32( func_callbk, uint_val, string_val, succ_string, err_string)  {		\
	uint_val = (unsigned32)(strtoul(string_val, NULL, 10));								\
	SS_CHECK(func_callbk, succ_string, err_string);							 			\
}

#define SS_CHECK( func_callback, succ_string, critical_error) {							\
		if(func_callback == 0)															\
			fprintf(stdout,COLOR_GREEN"OK : "ANSI_COLOR_RESET"%s",succ_string);			\
		else{																			\
			fprintf(stderr, COLOR_YELLOW"Error : "ANSI_COLOR_RESET"%s", critical_error);	\
			fd_core_shutdown();															\
			exit(1);																	\
		}																				\
	}

#define SS_WCHECK(func_callback, succ_string, warning, ret) {						\
		if(func_callback == 0)														\
			fprintf(stdout, COLOR_GREEN"OK : "ANSI_COLOR_RESET"%s", succ_string);		\
		else{																		\
			fprintf(stderr, COLOR_YELLOW"Warning : "ANSI_COLOR_RESET"%s", warning);	\
			ret;																	\
		}																			\
	}


typedef uint32_t unsigned32;
typedef int32_t integer32;
typedef unsigned char  utf8string;
typedef unsigned char  diameterid;
typedef unsigned char octetstring;
typedef unsigned char address;
typedef unsigned char ss_time;

/*Sets value of supported features and add it to message 'msg'*/
void test_set_supported_features(struct msg **msg, unsigned32 vendor_id, unsigned32 feature_id, unsigned32 feature_list);

/*Set MIP6-Agent-Info AVP */
void test_set_mip6(struct avp **gavp, address * ipv4, address * ipv6, diameterid * host, diameterid * realm);

/*Sends Cancel-Location-Request*/
int test_send_clr(diameterid *destination_host, diameterid *destination_rlm, utf8string * user_name, enum cancellation_type cancellation_type, unsigned32 clr_flags);

/*Prepares ULR message and send it to remote peer*/
/*'test_types = 0', response should be user unknow*/
/*'test_types = 1', response should be RAT not allowed, */
/*'test_types = 2', response should be roaming not allowed dueto odb feature not supported by MME*/
/*'test_types = any other number' , response should be filled with subscription data of user*/
int test_req_ulr(char * dest_host, int test_type);

/*Callback function to when any answer message is received*/
/*This is register when request is send and when the corresponding anser is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb(void * data, struct msg ** msg);

/*Callback function to when any ULR message is received*/
int test_req_cb_ulr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act);

/*finds a substring in a given string('parent_str') that immediatly follows another reference substring('ref_str') untill space charater or new line character or null character. if return is not NULL it should be freed after use*/
char * test_parse_string(char * parent_str, char * ref_str);

/*reads a file content into a buffer and returns a pointer to a buffer. file contetn size should be less 100.  if return is not NULL it should be freed after use*/
char * test_parse_conf(char * filename);

#endif
