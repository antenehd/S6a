
#ifndef SS_TEST_H
#define SS_TEST_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define VENDOR_ID_3GPP 	10415		/*Vendor-Id AVP value for 3gpp*/

/*Define Diameter Error codes*/
#define DIAMETER_ERROR_USER_UNKNOWN          5001
#define DIAMETER_ERROR_RAT_NOT_ALLOWED       5421
#define DIAMETER_ERROR_ROAMING_NOT_ALLOWED   5004
#define DIAMETER_UNABLE_TO_DELIVER			 3002

/*Define print output colors*/
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

/*UE-SRVCC-Capability	AVP values*/
enum ue_srvcc_capability{
	UE_SRVCC_NOT_SUPPORTED = 0,
	UE_SRVCC_SUPPORTED

};

/*Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP values*/
enum homogeneous_support_ims_voice_over_ps_sessions{
	NOT_SUPPORTED = 0,
	SUPPORTED
};

/*Rat-Type AVP values*/
enum rat_type{
	WLAN = 0,
	VIRTUAL = 1,
	UTRAN = 1000,
	GERAN = 1001,
	GAN = 1002,
	HSPA_EVOLUTION = 1003,
	EUTRAN = 1004,
	CDMA2000_1X = 2000,
	HRPD = 2001,
	UMB = 2002,
	EHRPD = 2003
};

/*SMS-Register-Request AVP values*/
enum sms_register_request{
	SMS_REGISTRATION_REQUIRED = 0,  
	SMS_REGISTRATION_NOT_PREFERRED, 
	NO_PREFERENCE	
};

/*Error-Diagnosti AVP values*/
enum error_diagnostic{
	PRS_DATA_SUBSCRIBED = 0,
	NO_GPRS_DATA_SUBSCRIBED,
	ODB_ALL_APN,
	ODB_HPLMN_APN,
	ODB_VPLMN_APN
};

/*Subscriber Status AVP values*/
enum subscriber_status{
	SERVICE_GRANTED  = 0,
	OPERATOR_DETERMINED_BARRING 
};

/*ICS-Indicator AVP values*/
enum ics_indicator{
	False = 0,
	True
};

/*Network-Access-Mode  AVP values*/
enum network_access_mode{
	PACKET_AND_CIRCUIT = 0,
	Reserved,
	ONLY_PACKET 
};

/* Notification-To-UE-User AVP values*/
enum notification_to_ue_user{
	NOTIFY_LOCATION_ALLOWED = 0, 
	NOTIFYANDVERIFY_LOCATION_ALLOWED_IF_NO_RESPONSE, 
	NOTIFYANDVERIFY_LOCATION_NOT_ALLOWED_IF_NO_RESPONSE, 
	LOCATION_NOT_ALLOWED
};

/*GMLC-Restriction  AVP values*/
enum gmlc_restriction{
	GMLC_LIST = 0, 
	HOME_COUNTRY 
};

/*PLMN-Client  AVP values*/
enum plmn_client{
	BROADCAST_SERVICE = 0, 
	O_AND_M_HPLMN, 
	O_AND_M_VPLMN,
	ANONYMOUS_LOCATION, 
	TARGET_UE_SUBSCRIBED_SERVICE	 
};


/*All-APN-Configurations-Included-Indicator AVP values*/
enum all_apn_configuration_included_indicator{
	All_APN_CONFIGURATIONS_INCLUDED = 0, 
	MODIFIED_ADDED_APN_CONFIGURATIONS_INCLUDED
};

/*PDN-Type AVP values*/
enum pdn_type{
	IPv4 = 0,
	IPv6,
	IPv4v6,
	IPv4_OR_IPv6	 	
};

/*QoS-Class-Identifier AVP values*/
enum qos_class_identifier{
	QCI_1 = 1,
	QCI_2,
	QCI_3,
	QCI_4,
	QCI_5,
	QCI_6,
	QCI_7,
	QCI_8,
	QCI_9,
	QCI_65 = 65,
	QCI_66 = 66,
	QCI_69 = 69,
	QCI_70 = 70
};

/*Pre-emption-Capability AVP values*/
enum pre_emption_capability{
	PRE_EMPTION_CAPABILITY_ENABLED =0,
	PRE_EMPTION_CAPABILITY_DISABLED
};

/*Pre-emption-Vulnerability AVP values*/
enum pre_emption_vulnerability{
	PRE_EMPTION_VULNERABILITY_ENABLED = 0,
	PRE_EMPTION_VULNERABILITY_DISABLED
};

/*VPLMN-Dynamic-Address-Allowed AVP value*/
enum vplmn_dynamic_address_allowed{
	NOTALLOWED = 0,
	ALLOWED
};

/*PDN-GW-Allocation-Type AVP values*/
enum pdn_gw_allocation_type{
	STATIC = 0,
	DYNAMIC
};

/*SIPTO-Permission AVP values*/
enum sipto_permission{
	SIPTO_above_RAN_ALLOWED = 0, 
	SIPTO_above_RAN_NOTALLOWED
};

/*LIPA-Permission AVP value*/
enum lipa_permission{
	LIPA_PROHIBITED = 0,
	LIPA_ONLY,
	LIPA_CONDITIONAL,
	LIPA_NOT_PRESENT
};

/*Trace-Depth AVP value*/
enum trace_depth{
	Minimum = 0,  
	Medium,  
	Maximum, 
	MinimumWithoutVendorSpecificExtension,
	MediumWithoutVendorSpecificExtension, 
	MaximumWithoutVendorSpecificExtension
};

/*Job-Type  AVP value*/
enum job_type{
	Immediate_MDT_only = 0, 
	Logged_MDT_only, 
	Trace_only,
	Immediate_MDT_and_Trace, 
	RLF_reports_only, 
	RCEF_reports_only
};

/*Report-Interval  AVP value*/
enum report_interval{
	UMTS_250MS = 0,  
	UMTS_500MS,  
	UMTS_1000MS,  
	UMTS_2000MS,  
	UMTS_3000MS, 
	UMTS_4000MS,  
	UMTS_6000MS,  
	UMTS_8000MS,  
	UMTS_12000MS,  
	UMTS_16000MS,  
	UMTS_20000MS,  
	UMTS_24000MS,  
	UMTS_28000MS,  
	UMTS_32000MS,  
	UMTS_64000MS,
	LTE_120MS,
	LTE_240MS,
	LTE_480MS,  
	LTE_640MS,
	LTE_1024MS,  
	LTE_2048MS,  
	LTE_5120MS,  
	LTE_10240MS,  
	LTE_60000MS,  
	LTE_360000MS,  
	LTE_720000MS,  
	LTE_1800000MS,  
	LTE_3600000MS
};

/*Report-Amount AVP values*/
enum report_amount{
	ONE = 0,  
	TWO,
	FOUR,
	EIGHT, 
	SIXTEEN,  
	THIRTYTWO,
 	SIXTYFOUR,
	enum_INFINITY
};

/*Logging-Interval AVP values*/
enum logging_interval{
	LOG_1p28 = 0, 
	LOG_2p56,  
	LOG_5p12,  
	LOG_10p24, 
	LOG_20p48,  
	LOG_30p72, 
	LOG_40p96,  
	LOG_61p44
};

/*Logging-Duration AVP values*/
enum logging_duration{
	LOG_600SEC = 0,  
	LOG_1200SEC,  
	LOG_2400SEC,  
	LOG_3600SEC,  
	LOG_5400SEC,  
	LOG_7200SEC
};

/*Measurement-Period-LTE  AVP values*/
enum measurement_period_lte{
	D_1024MS = 0, 
	D_1280MS, 
	D_2048MS, 
	D_2560MS, 
	D_5120MS,
	D_10240MS,
	D_1MIN
};

/*Measurement-Period-UMTS  AVP values*/
enum measurement_period_umts{
	D_250MS = 0,  
	D_500MS,  
	D_1000MS,  
	D_2000MS,  
	D_3000MS, 
	D_4000MS,  
	D_6000MS,  
	D_8000MS,
	D_12000MS,  
	D_16000MS,  
	D_20000MS,  
	D_24000MS,  
	D_28000MS,  
	D_32000MS,  
	D_64000MS
};

/*Complete-Data-List-Included-Indicator AVP values*/
enum complete_data_list_included_indicator{
	All_PDP_CONTEXTS_INCLUDED = 0,
	MODIFIED_ADDED_PDP_CONTEXTS_INCLUDED
};

/*Roaming-Restricted-Due-To-Unsupported-Feature AVP values*/
enum roaming_restricted_due_to_unsupported_feature{
	Roaming_Restricted_Due_To_Unsupported_Feature = 0
};

/*VPLMN-LIPA-Allowed AVP values*/
enum vplmn_lipa_allowed{
	LIPA_NOTALLOWED = 0,
	LIPA_ALLOWED
};

/*Relay-Node-Indicator AVP values*/
enum relay_node_indicator{
	NOT_RELAY_NODE = 0,
	RELAY_NODE
};

/*MDT-User-Consent  AVP values*/
enum mdt_user_consent{
	CONSENT_NOT_GIVEN = 0,
	CONSENT_GIVEN
};

/*Subscribed-VSRVCC  AVP values*/
enum subscribed_vsrvcc{
	VSRVCC_SUBSCRIBED = 0
};

/*Cancellation-Type AVP values*/
enum cancellation_type{
	MME_UPDATE_PROCEDUR = 0,
	SGSN_UPDATE_PROCEDURE,
	SUBCRIPTION_WITHDRAWAL,
	UPDATE_PROCEDURE_IWF,
	INITIAL_ATTACH_PROCEDURE
};

/* Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions  AVP values*/
enum homogeneous_support_of_ims_voice_over_ps_sessions{
	HOMO_IMS_VOICE_OVER_PS_NOT_SUPPORTED = 0,
	HOMO_IMS_VOICE_OVER_PS_SUPPORTED
};

/*User-State AVP values*/
enum user_state{
	DETACHED = 0,
	ATTACHED_NOT_REACHABLE_FOR_PAGING,
	ATTACHED_REACHABLE_FOR_PAGING,
	CONNECTED_NOT_REACHABLE_FOR_PAGING,
	CONNECTED_REACHABLE_FOR_PAGING,
	RESERVED
};

/*Current-Location-Retrieved AVP values*/
enum current_location_retrieved{
	ACTIVE_LOCATION_RETRIEVAL = 0
};

/*CSG-Access-Mode AVP values*/
enum csg_access_mode{
	CLOSED = 0,
	HYBRIDE
};

/*CSG-Membership-Indication AVP values*/
enum csg_membership_indication{
	Not_CSG_MEMBER = 0,
	CSG_MEMBER
};

/*Daylight-Saving-Time AVP values*/
enum daylight_saving_time{
	NO_ADJUSTMENT = 0, 
	PLUS_ONE_HOUR_ADJUSTMENT,
	PLUS_TWO_HOURS_ADJUSTMENT
};

/*Alert-Reason AVP values*/
enum alert_reason{
	UE_PRESENT = 0, 
	UE_MEMORY_AVAILABLE
};

/*SIPTO-Local-Network-Permission AVP values*/
enum sipto_local_network_permisson{
     siptoAtLocalNetworkAllowed = 0, 
     siptoAtLocalNetworkNotAllowed 
};


typedef uint32_t unsigned32;
typedef int32_t integer32;
typedef unsigned char  utf8string;
typedef unsigned char  diameterid;
typedef unsigned char octetstring;
typedef unsigned char address;
typedef unsigned char ss_time;

/*Sets value of supported features and add it to message 'msg'*/
void test_set_supported_features(struct msg **msg, unsigned32 vendor_id, unsigned32 feature_id, unsigned32 feature_list);

/*Get Supported-Feature child AVPs' values*/
void test_get_supported_features(struct msg *msg, unsigned32 **ftr_lst_id, unsigned32 **ftr_lst, size_t *size);

/*Set MIP6-Agent-Info AVP */
void test_set_mip6(struct avp **gavp, address * ipv4, address * ipv6, diameterid * host, diameterid * realm);

/*helper function to sends Cancel-Location-Request*/
int test_util_send_clr(diameterid *destination_host, diameterid *destination_rlm, utf8string * user_name, enum cancellation_type cancellation_type, unsigned32 clr_flags);

/*Prepares ULR message and send it to remote peer*/
/*'test_types = 0', response should be user unknow*/
/*'test_types = 1', response should be RAT not allowed, */
/*'test_types = 2', response should be roaming not allowed dueto odb feature not supported by MME*/
/*'test_types = any other number' , response should be filled with subscription data of user*/
int test_req_ulr(char * dest_host, int test_type);

/*Sends Cancel-Location-Request message for testing*/
int test_req_clr(char * dst_host);

/*Sends Authentication-Information-Request message for testing*/
int test_req_air(char * dst_host);

/*Callback function to when any ULA answer message is received*/
/*This is register when request is send and when the corresponding anser is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_ulr(void * data, struct msg ** msg);

/*Callback function to when any CLA answer message is received*/
/*This is register when request is send and when the corresponding anser is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_clr(void * data, struct msg ** msg);

/*Callback function to when any AIA answer message is received*/
/*This is register when request is send and when the corresponding anser is received the deamon calls this function and passes the answer message 'msg' for this function to process. and it also passes the data 'data' which was registered when the request was sent.
*/
void test_ans_cb_air(void * data, struct msg ** msg);

/*Callback function to when any ULR message is received*/
int test_req_cb_ulr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act);

/*Callback function to when any ULR message is received*/
int test_req_cb_clr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act);

/*Callback function used when Authentication-Information-Request message is received*/
int test_req_cb_air(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act);

/*finds a substring in a given string('parent_str') that immediatly follows another reference substring('ref_str') untill space charater or new line character or null character. if return is not NULL it should be freed after use*/
char * test_parse_string(char * parent_str, char * ref_str);

/*reads a file content into a buffer and returns a pointer to a buffer. file contetn size should be less 100.  if return is not NULL it should be freed after use*/
char * test_parse_conf(char * filename);

#endif
