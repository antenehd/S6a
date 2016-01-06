
#ifndef SS_INTERF_SSIX
#define SS_INTERF_SSIX

#include <stdlib.h>
#include <stdint.h>

#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdcore.h>

#define NO_STATE_MAINTAINED 1
#define VENDOR_ID_3GPP 		10415
#define SSIX_APPLICATION_ID 16777251

/*Define error codes*/
#define DIAMETER_ERROR_USER_UNKNOWN          5001
#define DIAMETER_ERROR_RAT_NOT_ALLOWED       5421
#define DIAMETER_ERROR_ROAMING_NOT_ALLOWED   5004


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
	UBSCRIPTION_WITHDRAWAL,
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

/*Global variable to store configuration file path including filename. It should be initialized before 'ss_init' function is called. If it is initialized to NULL the default file path is the the path where the application resides and the default file name is 'freeDiameter.conf'*/
extern char * diameter_conffile_name;

/*START of description directly copied from freediameter 'libfdproto.h' file
 * Call back functions:
 * PARAMETERS:
 *  msg 	: the received message on function entry. may be updated to answer on return (see description)
 *  avp  	: for callbacks registered with DISP_HOW_AVP or DISP_HOW_AVP_ENUMVAL, direct link to the triggering AVP.
 *  session	: if the message contains a Session-Id AVP, the corresponding session object, NULL otherwise.
 *  opaque  : An opaque pointer that is registered along the session handler.
 *  action	: upon return, this tells the daemon what to do next.
 *
 * DESCRIPTION: 
 *   Called when a received message matchs the condition for which the callback was registered.
 * This callback may do any kind of processing on the message, including:
 *  - create an answer for a request.
 *  - proxy a request or message, add / remove the Proxy-Info AVP, then forward the message.
 *  - update a routing table or start a connection with a new peer, then forward the message.
 *  - ...
 * 
 * When *action == DISP_ACT_SEND on callback return, the msg pointed by *msg is passed to the routing module for sending.
 * When *action == DISP_ACT_CONT, the next registered callback is called.
 *  When the last callback gives also DISP_ACT_CONT action value, a default handler is called. It's behavior is as follow:
 *   - if the message is an answer, it is discarded.
 *   - if the message is a request, it is passed again to the routing stack, and marked as non-local handling.
 *
 * RETURN VALUE:
 *  0      	: The callback executed successfully and updated *action appropriately.
 *  !0		: standard errors. In case of error, the message is discarded.
 *
 * END of description from freediameter 'libfdproto.h' file
 * 
 */


/*Registers a callback function 'cb' that will be call when Update-Location-Request is received. 
 Check the above Call back functions description for detail about the callback function. 	
	parameter :
 	  	cb : The callback function to register that is called when ULR message is received 
 	return: 
		0 : The callback is registered.
  		EINVAL : A parameter is invalid.
  		ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_ulr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/*Registers a callback function 'cb' that will be call when Cancel-Location-Request is received. 
 Check the above Call back functions description for detail about the callback function.
 	
	parameter :
 	  	cb : The callback function to register that is called when ULR message is received 
 	return: 
		0 : The callback is registered.
  		EINVAL : A parameter is invalid.
  		ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_clr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/*Registers a callback function 'cb' that will be call when Authentication-Information-Request is received. 
 Check the above Call back functions description for detail about the callback function.
 	
	parameter :
 	  	cb : The callback function to register that is called when ULR message is received 
 	return: 
		0 : The callback is registered.
  		EINVAL : A parameter is invalid.
  		ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_air_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/*Registers a callback function 'cb' that will be call when Insert-Subscriber-Data-Request is received. 
 Check the above Call back functions description for detail about the callback function.
 	
	parameter :
 	  	cb : The callback function to register that is called when ULR message is received 
 	return: 
		0 : The callback is registered.
  		EINVAL : A parameter is invalid.
  		ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_idr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/*Registers a callback function 'cb' that will be call when Delete-Subscriber-Data-Request  is received. 
 Check the above Call back functions description for detail about the callback function.
 	
	parameter :
 	  	cb : The callback function to register that is called when ULR message is received 
 	return: 
		0 : The callback is registered.
  		EINVAL : A parameter is invalid.
  		ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_dsr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/*Registers a callback function 'cb' that will be call when  Purge-UE-Request is received. 
 Check Request the above Call back functions description for detail about the callback function.
 	
	parameter :
 	  	cb : The callback function to register that is called when ULR message is received 
 	return: 
		0 : The callback is registered.
  		EINVAL : A parameter is invalid.
  		ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_pur_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/*Registers a callback function 'cb' that will be call when Reset-Request  is received. 
 Check the above Call back functions description for detail about the callback function.
 	
	parameter :
 	  	cb : The callback function to register that is called when ULR message is received 
 	return: 
		0 : The callback is registered.
  		EINVAL : A parameter is invalid.
  		ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_rsr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/*Registers a callback function 'cb' that will be call when  Notify-Request is received. 
 Check the above Call back functions description for detail about the callback function.
 	
	parameter :
 	  	cb : The callback function to register that is called when ULR message is received 
 	return: 
		0 : The callback is registered.
  		EINVAL : A parameter is invalid.
  		ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_nor_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/*	Initializes the diameter protocol.
	It parses the configuration file and initialize global variables based on
	the values in the configration file. It creates a connection with peers
	given in the confguration file.

		return: 0 on success, 1 on failure
*/
int ss_init();

/*Waites untill the diameter application gracefully shuts down. This function is called when the application
  is shuting down.
	
	return: 0 on success, 1 on failure
*/
int  ss_wait_shutdown();


/**************************************************************************************************/
/**				ADD AVPs TO MESSAGE OR GROUP AVP												 **/
/**************************************************************************************************/

/*Add AVP to message structure or goup AVP
	parameter:
		parent: the message structure or group AVP in to which the AVP will be added
		avp: the AVP that to be added in to the message structure or group AVP.
	return: 0 on success, or 1 on failure
*/
inline int ss_add_avp(msg_or_avp ** parent, struct avp * avp);


/**************************************************************************************************/
/**			 CREATE GROUP AVPs 																	 **/
/**************************************************************************************************/

/*Creates Terminal-Information group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_terminal_information(struct avp **gavp);

/*Creates  Active-APN group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_active_apn(struct avp **gavp);

/*Creates Equivalent-PLMN-List group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_equivalent_plmn_list(struct avp **gavp);

/*Creates MIP6-Agent-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_create_mip6_agent_info(struct avp **gavp);

/*Creates MIP-Home-Agent-Host group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_mip_home_agent_host(struct avp **gavp);

/*Creates  Specific-APN-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_specific_apn_info(struct avp **gavp);

/*Creates Experimental-Result group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_experimental_result(struct avp **gavp);

/*Creates Subscription-Data group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_subscription_data(struct avp **gavp);

/*Creates LCS-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_lcs_info(struct avp **gavp);

/*Creates  LCS-PrivacyException group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_lcs_privacyexception(struct avp **gavp);

/*Creates  External-Client group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_external_client(struct avp **gavp);

/*Creates  Service-Type group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_service_type(struct avp **gavp);

/*Creates  MO-LR group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_mo_lr(struct avp **gavp);

/*Creates  Teleservice-List group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_teleservice_list(struct avp **gavp);

/*Creates  Call-Barring-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_call_barring_info(struct avp **gavp);

/*Creates AMBR group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_ambr(struct avp **gavp);

/*Creates APN-Configuration-Profile group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_apn_configuration_profile(struct avp **gavp);

/*Creates  APN-Configuration group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_apn_configuration(struct avp **gavp);

/*Creates  EPS-Subscribed-QoS-Profile group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_eps_subscribed_qos_profile(struct avp **gavp);

/*Creates  Allocation-Retention-Priority group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_allocation_retention_priority(struct avp **gavp);

/*Creates  WLAN-offloadability group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_wlan_offloadability(struct avp **gavp);

/*Creates  Trace-Data group AVP 
	parameter:
		gavp : a pointer to an pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_trace_data(struct avp **gavp);

/*Creates  MDT-Configuration group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_mdt_configuration(struct avp **gavp);

/*Creates  Area-Scope group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_area_scope(struct avp **gavp);

/*Creates  GPRS-Subscription-Data group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_gprs_subscription_data(struct avp **gavp);

/*Creates  PDP-Context group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_pdp_context(struct avp **gavp);

/*Creates  CSG-Subscription-Data group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_csg_subscription_data(struct avp **gavp);

/*Creates ProSe-Subscription-Data group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_prose_subscription_data(struct avp **gavp);

/*Creates Requested-EUTRAN-Authentication-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_requested_eutran_authentication_info(struct avp **gavp);

/*Creates Requested-UTRAN-GERAN-Authentication-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_requested_utran_geran_authentication_info(struct avp **gavp);

/*Creates Authentication-Info group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_authentication_info(struct avp **gavp);

/*Creates  UTRAN-Vector group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_utran_vector(struct avp **gavp);

/*Creates  GERAN-Vector group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_geran_vector(struct avp **gavp);

/*Creates  EPS-User-State group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_eps_user_state(struct avp **gavp);

/*Creates  MME-User-State group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_mme_user_state(struct avp **gavp);

/*Creates  EPS-Location-Information group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_eps_location_information(struct avp **gavp);

/*Creates  MME-Location-Information group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_mme_location_information(struct avp **gavp);

/*Creates  User-CSG-Information group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_user_csg_information(struct avp **gavp);

/*Creates  Local-Time-Zone group AVP 
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_local_time_zone(struct avp **gavp);

/*Creates Supported-Features group AVP
	parameter:
		gavp : a pointer to an AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_create_supported_features(struct avp **gavp);


/******************************************************************************************************/
/**		GET GROUP AVPs FROM MESSAGE																	 **/	
/******************************************************************************************************/

/*Retrievs Terminal-Information group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which Terminal-Information group is searched.
		gavp : a pointer to Terminal-Information group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_terminal_information(struct msg *msg, struct avp **gavp);

/*Retrievs the first Active-APN group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which the Active-APN group avp is searched.
		gavp : a pointer to a Active-APN group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_active_apn(struct msg *msg, struct avp **gavp);

/*Retrievs the next Active-APN group AVP 
	parameter:
		avp : a pointer to Active-APN group AVP pointer next to which the next Active-APN group avp is searched.
		gavp : a pointer to Active-APN group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_active_apn(struct avp *avp, struct avp **gavp);

/*Retrievs Equivalent-PLMN-List group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which the Equivalent-PLMN-List group avp is searched.
		gavp : a pointer to Equivalent-PLMN-List group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_equivalent_plmn_list(struct msg *msg, struct avp **gavp);

/*Retrievs MIP6-Agent-Info group AVP from group avp
	parameter:
		avp : a pointer to a group avp pointer in which MIP6-Agent-Info group avp is searched.
		gavp : a pointer to MIP6-Agent-Info group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_mip6_agent_info(struct avp *avp, struct avp **gavp);

/*Retrievs MIP-Home-Agent-Host group AVP from group avp
	parameter:
		avp : a pointer to a group avp pointer in which MIP-Home-Agent-Host group avp is searched.
		gavp : a pointer to MIP-Home-Agent-Host group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_mip_home_agent_host(struct avp *avp, struct avp **gavp);

/*Retrievs the first Specific-APN-Info group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which Specific-APN-Info group avp is searched.
		gavp : a pointer to Specific-APN-Info group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_specific_apn_info(struct avp *avp, struct avp **gavp);

/*Retrievs the next Specific-APN-Info group AVP 
	parameter:
		avp : a pointer to Specific-APN-Info group AVP pointer next to which the next Specific-APN-Info group avp is searched.
		gavp : a pointer to a Specific-APN-Info group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_specific_apn_info(struct avp *avp, struct avp **gavp);

/*Retrievs Experimental-Result group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which the Experimental-Result group avp is searched.
		gavp : a pointer to Experimental-Result group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_experimental_result(struct msg *msg, struct avp **gavp);

/*Retrievs Subscription-Data group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which the Subscription-Data group avp is searched.
		gavp : a pointer to Subscription-Data group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_subscription_data(struct msg *msg, struct avp **gavp);

/*Retrievs LCS-Info group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which LCS-Info group avp is searched.
		gavp : a pointer to Specific-APN-Info group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_lcs_info(struct avp *avp, struct avp **gavp);

/*Retrievs the first LCS-PrivacyException group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which LCS-PrivacyException group avp is searched.
		gavp : a pointer to LCS-PrivacyException group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_lcs_privacyexception(struct avp *avp, struct avp **gavp);

/*Retrievs the next LCS-PrivacyException group AVP 
	parameter:
		avp : a pointer to LCS-PrivacyException group AVP pointer next to which the next LCS-PrivacyException group avp is searched.
		gavp : a pointer to a LCS-PrivacyException group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_lcs_privacyexception(struct avp *avp, struct avp **gavp);

/*Retrievs the first External-Client group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which External-Client group avp is searched.
		gavp : a pointer to External-Client group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_external_client(struct avp *avp, struct avp **gavp);

/*Retrievs the next External-Client group AVP 
	parameter:
		avp : a pointer to External-Client group AVP pointer next to which the next External-Client group avp is searched.
		gavp : a pointer to a External-Client group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_external_client(struct avp *avp, struct avp **gavp);

/*Retrievs the first Service-Type group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which Service-Type group avp is searched.
		gavp : a pointer to Service-Type group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_service_type(struct avp *avp, struct avp **gavp);

/*Retrievs the next Service-Type group AVP 
	parameter:
		avp : a pointer to Service-Type group AVP pointer next to which the next Service-Type group avp is searched.
		gavp : a pointer to a Service-Type group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_service_type(struct avp *avp, struct avp **gavp);

/*Retrievs the first MO-LR group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which MO-LR group avp is searched.
		gavp : a pointer to MO-LR group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_mo_lr(struct avp *avp, struct avp **gavp);

/*Retrievs the next MO-LR group AVP 
	parameter:
		avp : a pointer to MO-LR group AVP pointer next to which the next MO-LR group avp is searched.
		gavp : a pointer to a MO-LR group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_mo_lr(struct avp *avp, struct avp **gavp);

/*Retrievs the first Teleservice-List group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which Teleservice-List group avp is searched.
		gavp : a pointer to Teleservice-List group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_teleservice_list(struct avp *avp, struct avp **gavp);

/*Retrievs the first Call-Barring-Info group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which Call-Barring-Info group avp is searched.
		gavp : a pointer to Call-Barring-Info group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_call_barring_info(struct avp *avp, struct avp **gavp);

/*Retrievs the next Call-Barring-Info group AVP 
	parameter:
		avp : a pointer to Call-Barring-Info group AVP pointer next to which the next Call-Barring-Info group avp is searched.
		gavp : a pointer to a Call-Barring-Info group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_call_barring_info(struct avp *avp, struct avp **gavp);

/*Retrievs AMBR group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which AMBR group avp is searched.
		gavp : a pointer to AMBR group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_ambr(struct avp *avp, struct avp **gavp);

/*Retrievs APN-Configuration-Profile group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which APN-Configuration-Profile group avp is searched.
		gavp : a pointer to APN-Configuration-Profile group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_apn_configuration_profile(struct avp *avp, struct avp **gavp);

/*Retrievs the first APN-Configuration group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which APN-Configuration group avp is searched.
		gavp : a pointer to APN-Configuration group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_apn_configuration(struct avp *avp, struct avp **gavp);

/*Retrievs the next APN-Configuration group AVP 
	parameter:
		avp : a pointer to APN-Configuration group AVP pointer next to which the next APN-Configuration group avp is searched.
		gavp : a pointer to a APN-Configuration group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_apn_configuration(struct avp *avp, struct avp **gavp);

/*Retrievs the first EPS-Subscribed-QoS-Profile group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which EPS-Subscribed-QoS-Profile group avp is searched.
		gavp : a pointer to EPS-Subscribed-QoS-Profile group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_eps_subscribed_qos_profile(struct avp *avp, struct avp **gavp);

/*Retrievs the first Allocation-Retention-Priority group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which Allocation-Retention-Priority group avp is searched.
		gavp : a pointer to Allocation-Retention-Priority group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_allocation_retention_priority(struct avp *avp, struct avp **gavp);

/*Retrievs the first WLAN-offloadability group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which WLAN-offloadability group avp is searched.
		gavp : a pointer to WLAN-offloadability group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_wlan_offloadability(struct avp *avp, struct avp **gavp);

/*Retrievs the first Trace-Data group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which Trace-Data group avp is searched.
		gavp : a pointer to Trace-Data group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_trace_data(struct avp *avp, struct avp **gavp);

/*Retrievs the first MDT-Configuration group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which MDT-Configuration group avp is searched.
		gavp : a pointer to MDT-Configuration group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_mdt_configuration(struct avp *avp, struct avp **gavp);

/*Retrievs the first Area-Scope group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which Area-Scope group avp is searched.
		gavp : a pointer to Area-Scope group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_area_scope(struct avp *avp, struct avp **gavp);

/*Retrievs the first GPRS-Subscription-Data group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which GPRS-Subscription-Data group avp is searched.
		gavp : a pointer to GPRS-Subscription-Data group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_gprs_subscription_data(struct avp *avp, struct avp **gavp);

/*Retrievs the first PDP-Context group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which PDP-Context group avp is searched.
		gavp : a pointer to PDP-Context group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_pdp_context(struct avp *avp, struct avp **gavp);

/*Retrievs the next PDP-Context group AVP 
	parameter:
		avp : a pointer to PDP-Context group AVP pointer next to which the next PDP-Context group avp is searched.
		gavp : a pointer to a PDP-Context group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_pdp_context(struct avp *avp, struct avp **gavp);

/*Retrievs the first CSG-Subscription-Data group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which CSG-Subscription-Data group avp is searched.
		gavp : a pointer to CSG-Subscription-Data group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_csg_subscription_data(struct avp *avp, struct avp **gavp);

/*Retrievs the next CSG-Subscription-Data group AVP 
	parameter:
		avp : a pointer to CSG-Subscription-Data group AVP pointer next to which the next CSG-Subscription-Data group avp is searched.
		gavp : a pointer to a CSG-Subscription-Data group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_csg_subscription_data(struct avp *avp, struct avp **gavp);

/*Retrievs ProSe-Subscription-Data group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which ProSe-Subscription-Data group avp is searched.
		gavp : a pointer to ProSe-Subscription-Data group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_prose_subscription_data(struct avp *avp, struct avp **gavp);

/*Retrievs Requested-EUTRAN-Authentication-Info group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which Requested-EUTRAN-Authentication-Info group avp is searched.
		gavp : a pointer to Requested-EUTRAN-Authentication-Info group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_requested_eutran_authentication_info(struct avp *avp, struct avp **gavp);

/*Retrievs Requested-UTRAN-GERAN-Authentication-Info group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which Requested-UTRAN-GERAN-Authentication-Info group avp is searched.
		gavp : a pointer to Requested-UTRAN-GERAN-Authentication-Info group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_requested_utran_geran_authentication_info(struct avp *avp, struct avp **gavp);

/*Retrievs Authentication-Info group AVP from message
	parameter:
		msg : a pointer to a message structure avp pointer in which Authentication-Info group avp is searched.
		gavp : a pointer to Authentication-Info group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_authentication_info(struct msg *msg, struct avp **gavp);

/*Retrievs the first E-UTRAN-Vector group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which E-UTRAN-Vector group avp is searched.
		gavp : a pointer to E-UTRAN-Vector group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_e_utran_vector(struct avp *avp, struct avp **gavp);

/*Retrievs the next E-UTRAN-Vector group AVP 
	parameter:
		avp : a pointer to E-UTRAN-Vector group AVP pointer next to which the next E-UTRAN-Vector group avp is searched.
		gavp : a pointer to a E-UTRAN-Vector group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_e_utran_vector(struct avp *avp, struct avp **gavp);

/*Retrievs the first UTRAN-Vector group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which UTRAN-Vector group avp is searched.
		gavp : a pointer to UTRAN-Vector group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_utran_vector(struct avp *avp, struct avp **gavp);

/*Retrievs the next UTRAN-Vector group AVP 
	parameter:
		avp : a pointer to UTRAN-Vector group AVP pointer next to which the next UTRAN-Vector group avp is searched.
		gavp : a pointer to a UTRAN-Vector group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_utran_vector(struct avp *avp, struct avp **gavp);

/*Retrievs the first GERAN-Vector group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which GERAN-Vector group avp is searched.
		gavp : a pointer to GERAN-Vector group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_geran_vector(struct avp *avp, struct avp **gavp);

/*Retrievs the next GERAN-Vector group AVP 
	parameter:
		avp : a pointer to GERAN-Vector group AVP pointer next to which the next GERAN-Vector group avp is searched.
		gavp : a pointer to a GERAN-Vector group AVP pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_next_geran_vector(struct avp *avp, struct avp **gavp);

/*Retrievs the first EPS-User-State group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which EPS-User-State group avp is searched.
		gavp : a pointer to EPS-User-State group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_eps_user_state(struct msg *msg, struct avp **gavp);

/*Retrievs the first MME-User-State group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which MME-User-State group avp is searched.
		gavp : a pointer to MME-User-State group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_mme_user_state(struct avp *avp, struct avp **gavp);

/*Retrievs the first EPS-Location-Information group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which EPS-Location-Information group avp is searched.
		gavp : a pointer to EPS-Location-Information group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_eps_location_information(struct msg *msg, struct avp **gavp);

/*Retrievs the first MME-Location-Information group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which MME-Location-Information group avp is searched.
		gavp : a pointer to MME-Location-Information group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_mme_location_information(struct avp *avp, struct avp **gavp);

/*Retrievs the first User-CSG-Information group AVP from group avp
	parameter:
		avp : a goup avp in to which the avp will be added after its value is set pointer in which User-CSG-Information group avp is searched.
		gavp : a pointer to User-CSG-Information group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_user_csg_information(struct avp *avp, struct avp **gavp);

/*Retrievs the first Local-Time-Zone group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which Local-Time-Zone group avp is searched.
		gavp : a pointer to Local-Time-Zone group avp pointer where the result will be stored.
	return : 0 on success,, 1 on failure
*/
inline int ss_get_gavp_local_time_zone(struct msg *msg, struct avp **gavp);

/*Retrievs the first Supported-Features group AVP from message
	parameter:
		msg : a pointer to a message structure pointer in which Supported-Features group avp is searched.
		gavp : a pointer to Supported-Features group avp pointer where the result will be stored.
	return : 0 on success, 1 on failure
*/
inline int ss_get_gavp_supported_features(struct msg *msg, struct avp **gavp);


/***********************************************************************************************************/
/**			CREATE REQUEST AND ANSWER MESSAGE															  **/		
/***********************************************************************************************************/

/* Create answer message from a request message. And set  Vendor-Specific-Application-Id and Auth-Session-State in to the message
	parameter:
		msg : a pointer to the request message pointer. it will point to the answer message upon function return.
		req : a pointer to a message pointer that will point to the original request message upon function return
	return : 0 on success, 1 on failure
*/
inline int ss_create_answer(struct msg **msg, struct msg **req);

/*Creates Update-Location-Request message and then creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success, 1 on failure
*/
inline int ss_create_msg_ulr(struct msg ** req);

/*Creates Authentication-Information-Request message and then creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success, 1 on failure
*/
inline int ss_create_msg_air(struct msg ** req);

/*Creates Cancel-Location-Request message and then creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success, 1 on failure
*/
inline int ss_create_msg_clr(struct msg ** req);

/*Creates Insert-Subscriber-Data-Request message and hen creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success, 1 on failure
*/
inline int ss_create_msg_idr(struct msg ** req);
/*Creates Delete-Subscriber-Data-Request message and hen creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success, 1 on failure
*/
inline int ss_create_msg_dsr(struct msg ** req);

/*Creates Purge-UE-Request message and then creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success, 1 on failure
*/
inline int ss_create_msg_pur(struct msg ** req);

/*Creates Reset-Request message and then creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success, 1 on failure
*/
inline int ss_create_msg_rsr(struct msg ** req);

/*Creates Notify-Request message and hen creates new session, set Vendor-Specific-Application-Id, set Auth-Session-State and Origin-Host & Origin-Realm AVP in to the message.
	parameter req: a pointer to the message structure pointer where the result is saved.
	return : 0 on success, 1 on failure
*/
inline int ss_create_msg_nor(struct msg ** req);


/*****************************************************************************************************************/
/**					GET REMOTE PEER STATE																		**/
/*****************************************************************************************************************/

/* States of a peer 
enum peer_state {
	// Stable states 
	STATE_NEW = 0,		// The peer has been just been created, PSM thread not started yet 
	STATE_OPEN,		//Connexion established 
	
	// Peer state machine
	STATE_CLOSED,		// No connection established, will re-attempt after TcTimer. 
	STATE_CLOSING,		// the connection is being shutdown (DPR/DPA in progress) 
	STATE_WAITCNXACK,	// Attempting to establish transport-level connection 
	STATE_WAITCNXACK_ELEC,	// Received a CER from this same peer on an incoming connection (other peer object), while we were waiting for cnx ack 
	STATE_WAITCEA,		// Connection established, CER sent, waiting for CEA 
	
	STATE_OPEN_HANDSHAKE,	// TLS Handshake and validation are in progress in open state -- we use it only for debug purpose, it is never displayed 
	
	// Failover state machine 
	STATE_SUSPECT,		//A DWR was sent and not answered within TwTime. Failover in progress. 
	STATE_REOPEN,		// Connection has been re-established, waiting for 3 DWR/DWA exchanges before putting back to service 
	
	// Ordering issues with multistream & state machine. -- see top of p_psm.c for explanation 
	STATE_OPEN_NEW, 	// after CEA is sent, until a new message is received. Force ordering in this state 
	STATE_CLOSING_GRACE,	// after DPA is sent or received, give a short delay for messages in the pipe to be received. 
	
	// Error state
	STATE_ZOMBIE		//The PSM thread is not running anymore; it must be re-started or peer should be deleted. 
};
*/


/*Checks the connection state with remote peer. Only after the connection state is open that S6 messages may be sent to remote peer.
	parameter:
		diamid : diameter identity of remote peer
		diamidlen : length of diameter identity 
	returns :'enum peer_state' values as defined above. This values are defined in freediameter library. 
			 -1 if peer is invalid/notfound
			   

*/
inline int ss_peer_state(char * diamid, size_t diamid_len);



/******************************************************************************************************************/
/**				SET VALUE OF AVP AND ADD IT TO MESSAGE OR GROUP AVP												 **/
/******************************************************************************************************************/

/*Sets Destination-Host avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_destination_host(struct msg **msg, unsigned char *val);

/*Sets Destination-Host avp value and add it to group AVP 
	parameter:
		gavp: pointer to the group AVP pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_destination_host_gavp(struct avp **gavp, unsigned char *val);

/*Sets originating host avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_origin_host(struct msg **msg, unsigned char *val);

/*Sets Destination-Realm avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_destination_realm(struct msg **msg, unsigned char *val);

/*Sets Destination-Realm avp value and add it to group AVP 
	parameter:
		gavp: pointer to the group AVP pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_destination_realm_gavp(struct avp **gavp, unsigned char *val);

/*Sets originating realm avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: a pointer to the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_origin_realm(struct msg **msg, unsigned char *val);

/*Sets User-Name (imsi) avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_user_name(struct msg **msg, unsigned char *val);

/*Sets RAT-Type avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_rat_type(struct msg **msg, int32_t val);

/*Sets ULR-Flags avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ulr_flags(struct msg **msg, uint32_t val);

/*Sets UE-SRVCC-Capability avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ue_srvcc_capability(struct msg **msg, int32_t val);

/*Sets Visited-PLMN-Id avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: a a pointer to the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_visited_plmn_id(struct msg **msg, unsigned char *val);

/*Sets SGSN-Number avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_sgsn_number(struct msg **msg, unsigned char *val);

/*Sets Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_homogeneous_support_ims_vop_sessions(struct msg **msg, int32_t val);

/*Sets GMLC-Address avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_gmlc_address(struct msg **msg, unsigned char *val);

/*Sets MME-Number-for-MT-SMS avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_mme_number_for_mt_sms(struct msg **msg, unsigned char *val);

/*Sets SMS-Register-Request avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_sms_register_request(struct msg **msg, int32_t val);

/*Sets Coupled-Node-Diameter-ID avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_coupled_node_diameter_id(struct msg **msg, unsigned char *val);

/*Sets IMEI avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set . 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_imei(struct avp **gavp, unsigned char *val);

/*Sets Software-Version avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_software_version(struct avp **gavp, unsigned char *val);

/*Sets 3GPP2-MEID avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_3gpp2_meid(struct avp **gavp, unsigned char *val);

/*Sets Context-Identifier avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_context_identifier_gavp(struct avp **gavp, uint32_t val);

/*Sets Service-Selection avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_service_selection_gavp(struct avp **gavp, unsigned char *val);

/*Sets Visited-Network-Identifier avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set. 
		val: a pointer to the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_visited_network_identifier_gavp(struct avp **gavp, unsigned char *val);

/*Sets MIP-Home-Agent-Address avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set . 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_mip_home_agent_address(struct avp **gavp, unsigned char *val);

/*Sets MIP-Home-Agent-Host avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_mip_home_agent_host(struct avp **gavp, unsigned char *val);

/*Sets Visited-PLMN-Id avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set .  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_visited_plmn_id_gavp(struct avp **gavp, unsigned char *val);

/*Sets Result-Code avp value and add it to message 
	parameter:
		msg: pointer to the message pointer.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_result_code(struct msg **msg, uint32_t val);

/*Sets Error-Diagnostic avp value and add it to message 
	parameter:
		msg: pointer to the message pointer.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_error_diagnostic(struct msg **msg, int32_t val);

/*Sets ULA-Flags avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ula_flags(struct msg **msg, uint32_t val);

/*Sets Vendor-Id avp value and add it to group avp 
	parameter:
		gavp: a pointer to a group avp in to which the avp will be added after its value is set .
	returns: 0 on success, 1 on failure
*/
inline int ss_set_vendor_id(struct avp **gavp, uint32_t val);

/*Sets Auth-Application-Id avp value and add it to group avp 
	parameter:
		gavp: a pointer to a group avp in to which the avp will be added after its value is set .
	returns: 0 on success, 1 on failure
*/
inline int ss_set_auth_application_id(struct avp **gavp, uint32_t val);

/*Sets Experimental-Result-Code avp value and add it to group avp 
	parameter:
		gavp: a pointer to a group avp in to which the avp will be added after its value is set .
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_experimental_result_code(struct avp **gavp, uint32_t val);

/*Sets Subscriber-Status avp value and add it to group avp 
	parameter:
		gavp: a pointer to a group avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_subscriber_status(struct avp **gavp, int32_t val);

/*Sets MSISDN avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_msisdn(struct avp **gavp, unsigned char *val);

/*Sets A-MSISDN avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_a_msisdn(struct avp **gavp, unsigned char *val);

/*Sets STN-SR avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_stn_sr(struct avp **gavp, unsigned char *val);

/*Sets ICS-Indicator avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ics_indicator(struct avp **gavp, int32_t val);

/*Sets Network-Access-Mode avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		ret: a pointer to the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_network_access_mode(struct avp **gavp, int32_t val);

/*Sets Operator-Determined-Barring avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_operator_determined_barring(struct avp **gavp, uint32_t val);

/*Sets HPLMN-ODB avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_hplmn_odb(struct avp **gavp, uint32_t val);

/*Sets Regional-Subscription-Zone-Code avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_regional_subscription_zone_code(struct avp **gavp, unsigned char *val);

/*Sets Access-Restriction-Data avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_access_restriction_data(struct avp **gavp, uint32_t val);

/*Sets APN-OI-Replacement avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_apn_oi_replacement(struct avp **gavp, unsigned char *val);

/*Sets 3GPP-Charging-Characteristics avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_3gpp_charging_characteristics(struct avp **gavp, unsigned char *val);

/*Sets RAT-Frequency-Selection-Priority-ID avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_rat_frequency_selection_priority_id(struct avp **gavp, uint32_t val);

/*Sets Roaming-Restricted-Due-To-Unsupported-Feature avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_roaming_restricted_unsupported_feature(struct avp **gavp, int32_t val);

/*Sets Subscribed-Periodic-RAU-TAU-Timer avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_subscribed_periodic_rau_tau_timer(struct avp **gavp, uint32_t val);

/*Sets MPS-Priority avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_mps_priority(struct avp **gavp, uint32_t val);

/*Sets VPLMN-LIPA-Allowed avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_vplmn_lipa_allowed(struct avp **gavp, int32_t val);

/*Sets Relay-Node-Indicator avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_relay_node_indicator(struct avp **gavp, int32_t val);

/*Sets MDT-User-Consent avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_mdt_user_consent(struct avp **gavp, int32_t val);

/*Sets Subscribed-VSRVCC avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_subscribed_vsrvcc(struct avp **gavp, int32_t val);

/*Sets Subscription-Data-Flags avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_subscription_data_flags(struct avp **gavp, uint32_t val);

/*Sets multiple GMLC-Number AVPs value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_gmlc_number(struct avp **gavp, unsigned char *val);

/*Sets SS-Code avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ss_code_gavp(struct avp **gavp, unsigned char *val);

/*Sets SS-Status avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ss_status(struct avp **gavp, unsigned char *val);

/*Sets Notification-To-UE-User avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_notification_ue_user(struct avp **gavp, int32_t val);

/*Sets Client-Identity avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_client_identity(struct avp **gavp, unsigned char *val);

/*Sets GMLC-Restriction avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_gmlc_restriction(struct avp **gavp, int32_t val);

/*Sets multiple PLMN-Client AVPs value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_plmn_client(struct avp **gavp, int32_t val);

/*Sets ServiceTypeIdentity avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_serviceTypeIdentity(struct avp **gavp, uint32_t val);

/*Sets multiple TS-Code AVPs value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ts_code_gavp(struct avp **gavp, unsigned char *val);

/*Sets Max-Requested-Bandwidth-UL avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_max_requested_bw_ul(struct avp **gavp, uint32_t val);

/*Sets Max-Requested-Bandwidth-DL avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_max_requested_bw_dl(struct avp **gavp, uint32_t val);

/*Sets All-APN-Configurations-Included-Indicator avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_all_apn_configuration_included_indicator(struct avp **gavp, int32_t val);
/*Sets PDN-Type avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_pdn_type(struct avp **gavp, int32_t val);
/*Sets VPLMN-Dynamic-Address-Allowed avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_vplmn_dynamic_address_allowed(struct avp **gavp, int32_t val);

/*Sets PDN-GW-Allocation-Type avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_pdn_gw_allocation_type(struct avp **gavp, int32_t val);

/*Sets SIPTO-Permission avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_sipto_permission(struct avp **gavp, int32_t val);

/*Sets LIPA-Permission avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_lipa_permission(struct avp **gavp, int32_t val);

/*Sets Restoration-Priority avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_restoration_priority(struct avp **gavp, uint32_t val);

/*Sets SIPTO-Local-Network-Permission avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_sipto_local_network_permission(struct avp **gavp, int32_t val);

/*Sets multiple Served-Party-IP-Address AVPs' values to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_served_party_ip_address(struct avp **gavp, unsigned char *val);

/*Sets QoS-Class-Identifier avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set .
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_qos_class_identifier(struct avp **gavp, int32_t val);

/*Sets Priority-Level avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_priority_level(struct avp **gavp, uint32_t val);

/*Sets Pre-emption-Capability avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_pre_emption_capability(struct avp **gavp, int32_t val);

/*Sets Pre-emption-Vulnerability avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_pre_emption_vulnerability(struct avp **gavp, int32_t val);

/*Sets WLAN-offloadability-EUTRAN avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_wlan_offloadability_eutran(struct avp **gavp, uint32_t val);

/*Sets WLAN-offloadability-UTRAN avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_wlan_offloadability_utran(struct avp **gavp, uint32_t val);

/*Sets Trace-Reference avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set .  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_trace_reference_gavp(struct avp **gavp, unsigned char *val);

/*Sets Trace-Depth avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_trace_depth(struct avp **gavp, int32_t val);

/*Sets Trace-NE-Type-List avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_trace_ne_type_list(struct avp **gavp, unsigned char *val);

/*Sets Trace-Interface-List avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_trace_interface_list(struct avp **gavp, unsigned char *val);

/*Sets Trace-Event-List avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_trace_event_list(struct avp **gavp, unsigned char *val);

/*Sets OMC-Id avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_omc_id(struct avp **gavp, unsigned char *val);

/*Sets Trace-Collection-Entity avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_trace_collection_entity(struct avp **gavp, unsigned char *val);

/*Sets Job-Type avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_job_type(struct avp **gavp, int32_t val);

/*Sets multiple Cell-Global-Identity AVPs' values to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_cell_global_identity(struct avp **gavp, unsigned char *val);

/*Sets multiple E-UTRAN-Cell-Global-Identity AVPs' values to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_e_utran_cell_global_identity(struct avp **gavp, unsigned char *val);

/*Sets multiple Routing-Area-Identity AVPs' values to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_routing_area_identity(struct avp **gavp, unsigned char *val);

/*Sets multiple Location-Area-Identity AVPs' values to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_location_area_identity(struct avp **gavp, unsigned char *val);

/*Sets multiple Tracking-Area-Identity AVPs' values to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_tracking_area_identity(struct avp **gavp, unsigned char *val);

/*Sets List-Of-Measurements avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_list_of_measurements(struct avp **gavp, uint32_t val);

/*Sets Reporting-Trigger avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_reporting_trigger(struct avp **gavp, uint32_t val);

/*Sets Report-Interval avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_report_interval(struct avp **gavp, int32_t val);

/*Sets Report-Amount avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_report_amount(struct avp **gavp, int32_t val);

/*Sets Event-Threshold-RSRP avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_event_threshold_rsrp(struct avp **gavp, uint32_t val);

/*Sets Event-Threshold-RSRQ avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_event_threshold_rsrq(struct avp **gavp, uint32_t val);

/*Sets Logging-Interval avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_logging_interval(struct avp **gavp, int32_t val);

/*Sets Logging-Duration avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_logging_duration(struct avp **gavp, int32_t val);

/*Sets Measurement-Period-LTE avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set .
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_measurement_period_lte(struct avp **gavp, int32_t val);

/*Sets Measurement-Period-UMTS avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_measurement_period_umts(struct avp **gavp, int32_t val);

/*Sets Collection-Period-RMM-LTE avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_collection_period_rmm_lte(struct avp **gavp, int32_t val);

/*Sets Collection-Period-RRM-UMTS avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_collection_period_rmm_umts(struct avp **gavp, int32_t val);

/*Sets Positioning-Method avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_positioning_method(struct avp **gavp, unsigned char *val);

/*Sets Measurement-Quantity avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_measurement_quantity(struct avp **gavp, unsigned char *val);

/*Sets Event-Threshold-Event-1F avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_event_threshold_event_1f(struct avp **gavp, uint32_t val);

/*Sets Event-Threshold-Event-1I avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_event_threshold_event_1i(struct avp **gavp, uint32_t val);

/*Sets multiple MDT-Allowed-PLMN-Id AVPs' values to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_mdt_allowed_plmn_id(struct avp **gavp, unsigned char *val);

/*Sets Complete-Data-List-Included-Indicator avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_complete_data_list_included_indicator(struct avp **gavp, int32_t val);

/*Sets PDP-Type avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_pdp_type(struct avp **gavp, unsigned char *val);

/*Sets PDP-Address avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_pdp_address(struct avp **gavp, unsigned char *val);

/*Sets QoS-Subscribed avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_qos_subscribed(struct avp **gavp, unsigned char *val);

/*Sets Ext-PDP-Type avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ext_pdp_type(struct avp **gavp, unsigned char *val);

/*Sets Ext-PDP-Address avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ext_pdp_address(struct avp **gavp, unsigned char *val);

/*Sets CSG-Id avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_csg_id(struct avp **gavp, uint32_t val);

/*Sets Expiration-Date avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_expiration_date(struct avp **gavp, unsigned char *val);

/*Sets ProSe-Permission avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_prose_permission(struct avp **gavp, uint32_t val);

/*Sets multiple Reset-ID AVPs' values to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_reset_id(struct msg **msg, unsigned char *val);

/*Sets Number-Of-Requested-Vectors avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_number_of_requested_vectors(struct avp **gavp, uint32_t val);

/*Sets Immediate-Response-Preferred avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_immediate_response_preferred(struct avp **gavp, uint32_t val);

/*Sets Re-synchronization-Info avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_re_synchronization_info(struct avp **gavp, unsigned char *val);

/*Sets Item-Number avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_item_number(struct avp **gavp, uint32_t val);

/*Sets RAND avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_rand(struct avp **gavp, unsigned char *val);

/*Sets XRES avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_xres(struct avp **gavp, unsigned char *val);

/*Sets AUTN avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_autn(struct avp **gavp, unsigned char *val);

/*Sets KASME avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_kasme(struct avp **gavp, unsigned char *val);

/*Sets Confidentiality-Key avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_confidentiality_key(struct avp **gavp, unsigned char *val);

/*Sets Integrity-Key avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_integrity_key(struct avp **gavp, unsigned char *val);

/*Sets Kc avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_kc(struct avp **gavp, unsigned char *val);

/*Sets SRES avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_sres(struct avp **gavp, unsigned char *val);

/*Sets Cancellation-Type avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_cancellation_type(struct msg **msg, int32_t val);

/*Sets CLR-Flags avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_clr_flags(struct msg **msg, uint32_t val);

/*Sets IDR- Flags avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_idr_flags(struct msg **msg, uint32_t val);

/*Sets IMS-Voice-Over-PS-Sessions-Supported avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ims_voice_over_ps_sessions_supported(struct msg **msg, int32_t val);

/*Sets Last-UE-Activity-Time avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_last_ue_activity_time(struct msg **msg, unsigned char *val);

/*Sets IDA- Flags avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ida_flags(struct msg **msg, uint32_t val);

/*Sets User-State avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_user_state(struct avp **gavp, int32_t val);

/*Sets Geographical-Information avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		ret: a pointer to the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_geographical_information(struct avp **gavp, unsigned char *val);

/*Sets Geodetic-Information avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		ret: a a pointer to the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_geodetic_information(struct avp **gavp, unsigned char *val);

/*Sets Current-Location-Setd avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_current_location_Setd(struct avp **gavp, int32_t val);

/*Sets Age-Of-Location-Information avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_age_of_location_information(struct avp **gavp, uint32_t val);

/*Sets CSG-Access-Mode avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_csg_access_mode(struct avp **gavp, int32_t val);

/*Sets CSG-Membership-Indication avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_csg_membership_indication(struct avp **gavp, int32_t val);

/*Sets Time-Zone avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		ret: a pointer to the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_time_zone(struct avp **gavp, unsigned char *val);

/*Sets Daylight-Saving-Time avp value and add it to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_daylight_saving_time(struct avp **gavp, int32_t val);

/*Sets DSR-Flags avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_dsr_flags(struct msg **msg, uint32_t val);

/*Sets Context-Identifier avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_context_identifier(struct msg **msg, uint32_t val);

/*Sets Trace-Reference avp value to to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_trace_reference(struct msg **msg, unsigned char *val);

/*Sets multiple TS-Code AVPs value and add it to message
	parameter:
		msg: a pointer to the message pointer.  
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ts_code(struct msg **msg, unsigned char *val);

/*Sets multiple SS-Code AVPs value and add it to message
	parameter:
		msg: a pointer to the message pointer.  
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_ss_code(struct msg **msg, unsigned char *val);

/*Sets DSA-Flags avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_dsa_flags(struct msg **msg, uint32_t val);

/*Sets PUR-Flags avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_pur_flags(struct msg **msg, uint32_t val);

/*Sets PUA-Flags avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_pua_flags(struct msg **msg, uint32_t val);

/*Sets multiple User-Id AVPs value and add it to message
	parameter:
		msg: a pointer to the message pointer.  
		val : a pointer to the value to be  set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_user_id(struct msg **msg, unsigned char *val);

/*Sets Visited-Network-Identifier avp value and add it to message
	parameter:
		msg: a pointer to the message pointer.  
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_set_visited_network_identifier(struct msg **msg, unsigned char *val);

/*Sets Service-Selection avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_service_selection(struct msg **msg, unsigned char *val);

/*Sets Alert-Reason avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_alert_reason(struct msg **msg, int32_t val);

/*Sets NOR-Flags avp value and add it to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_nor_flags(struct msg **msg, uint32_t val);

/*Sets Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions avp value and add it to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_homogeneous_support_ims_vop_sessions(struct msg **msg, int32_t val);

/*Sets Feature-List-ID  avp value to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_feature_list_id(struct avp **gavp, uint32_t val);

/*Sets Feature-List  avp value to group avp 
	parameter:
		gavp: a pointer to a goup avp in to which the avp will be added after its value is set.  
		val: the value to be set
	returns: 0 on success, 1 on failure
*/
inline int ss_set_feature_list(struct avp **gavp, uint32_t val);



/*****************************************************************************************************************/
/**					RETRIEVE AVP VALUE																			**/
/*****************************************************************************************************************/

/*Retrieves Destination-Host avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_destination_host(struct msg *msg, unsigned char **ret);

/*Retrieves Destination-Host avp value from group AVP 
	parameter:
		gavp: a pointer the group AVP pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_destination_host_gavp(struct avp *gavp, unsigned char **ret);

/*Retrieves originating host avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_origin_host(struct msg *msg, unsigned char **ret);

/*Retrieves Destination-Realm avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_destination_realm(struct msg *msg, unsigned char **ret);

/*Retrieves originating realm avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_origin_realm(struct msg *msg, unsigned char **ret);

/*Retrieves originating realm avp value from group AVP 
	parameter:
		gavp: a pointer to the group AVP pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_destination_realm_gavp(struct avp *gavp, unsigned char **ret);

/*Retrieves User-Name (imsi) avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_user_name(struct msg *msg, unsigned char **ret);

/*Retrieves RAT-Type avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_rat_type(struct msg *msg, int32_t *ret);

/*Retrieves ULR-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ulr_flags(struct msg *msg, uint32_t *ret);

/*Retrieves UE-SRVCC-Capability avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ue_srvcc_capability(struct msg *msg, int32_t *ret);

/*Retrieves Visited-PLMN-Id avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_visited_plmn_id(struct msg *msg, unsigned char **ret);

/*Retrieves SGSN-Number avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_sgsn_number(struct msg *msg, unsigned char **ret);

/*Retrieves Homogeneous-Support-of-IMS-Voice-Over-PS-Session avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_homogeneous_support_ims(struct msg *msg, int32_t *ret);

/*Retrieves GMLC-Address avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_gmlc_address(struct msg *msg, unsigned char **ret);

/*Retrieves MME-Number-for-MT-SMS avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_mme_number_for_mt_sms(struct msg *msg, unsigned char **ret);

/*Retrieves SMS-Register-Request avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_sms_register_request(struct msg *msg, int32_t *ret);

/*Retrieves Coupled-Node-Diameter-ID avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_coupled_node_diameter_id(struct msg *msg, unsigned char **ret);

/*Retrieves IMEI avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains imei avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_imei(struct avp *gavp, unsigned char **ret);

/*Retrieves Software-Version avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Software-Version avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_software_version(struct avp *gavp, unsigned char **ret);

/*Retrieves 3gpp2-meid avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains meid avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_3gpp2_meid(struct avp *gavp, unsigned char **ret);

/*Retrieves Context-Identifier avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Context-Identifier avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_context_identifier_gavp(struct avp *gavp, uint32_t *ret);

/*Retrieves Service-Selection avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Service-Selection avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_service_selection_gavp(struct avp *gavp, unsigned char **ret);

/*Retrieves multiple Service-Selection AVPs' values from group avp 
	parameter:
		gavp: a pointer to the group avp that contains Service-Selection avps.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_service_selection_array(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves Visited-Network-Identifier avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Visited-Network-Identifier avp. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_visited_network_identifier_gavp(struct avp *gavp, unsigned char **ret);

/*Retrieves multiple MIP-Home-Agent-Address AVPs' values from group avp 
	parameter:
		gavp: a pointer to the group avp that contains MIP-Home-Agent-Address avps.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_mip_home_agent_address_array(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves Visited-PLMN-Id avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Visited-PLMN-Id avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_visited_plmn_id_gavp(struct avp *gavp, unsigned char **ret);

/*Retrieves multiple Visited-PLMN-Id AVPs' values from group avp 
	parameter:
		gavp: a pointer to the group avp that contains Visited-PLMN-Id avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_visited_plmn_id_array(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves Result-Code avp value from message
	parameter:
		msg: a pointer the message pointer.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_result_code(struct msg *msg, uint32_t *ret);

/*Retrieves Error-Diagnostic avp value from message 
	parameter:
		msg: a pointer the message pointer.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_error_diagnostic(struct msg *msg, int32_t *ret);

/*Retrieves ULA-Flags avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ula_flags(struct msg *msg, uint32_t *ret);

/*Retrieves Vendor-Id avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Vendor-Id avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_vendor_id(struct avp *gavp, uint32_t *ret);

/*Retrieves Experimental-Result-Code avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Experimental-Result-Code avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_experimental_result_code(struct avp *gavp, uint32_t *ret);

/*Retrieves Subscriber-Status avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Subscriber-Status avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_subscriber_status(struct avp *gavp, int32_t *ret);

/*Retrieves MSISDN avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains MSISDN avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_msisdn(struct avp *gavp, unsigned char **ret);

/*Retrieves A-MSISDN avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains A-MSISDN avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_a_msisdn(struct avp *gavp, unsigned char **ret);

/*Retrieves STN-SR avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains STN-SR avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_stn_sr(struct avp *gavp, unsigned char **ret);

/*Retrieves ICS-Indicator avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains ICS-Indicator avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ics_indicator(struct avp *gavp, int32_t *ret);

/*Retrieves Network-Access-Mode avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Network-Access-Mode avp.
		ret: a pointer to an uint variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_network_access_mode(struct avp *gavp, int32_t *ret);

/*Retrieves Operator-Determined-Barring avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Operator-Determined-Barring avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_operator_determined_barring(struct avp *gavp, uint32_t *ret);

/*Retrieves HPLMN-ODB avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains HPLMN-ODB avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_hplmn_odb(struct avp *gavp, uint32_t *ret);

/*Retrieves Regional-Subscription-Zone-Code avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Regional-Subscription-Zone-Code avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_regional_subscription_zone_code(struct avp *gavp, unsigned char **ret);

/*Retrieves Access-Restriction-Data avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Access-Restriction-Data avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_access_restriction_data(struct avp *gavp, uint32_t *ret);

/*Retrieves APN-OI-Replacement avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains APN-OI-Replacement avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_apn_oi_replacement(struct avp *gavp, unsigned char **ret);

/*Retrieves 3GPP-Charging-Characteristics avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains 3GPP-Charging-Characteristics avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_3gpp_charging_characteristics(struct avp *gavp, unsigned char **ret);

/*Retrieves RAT-Frequency-Selection-Priority-ID avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains RAT-Frequency-Selection-Priority-ID avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_rat_frequency_selection_priority_id(struct avp *gavp, uint32_t *ret);

/*Retrieves Roaming-Restricted-Due-To-Unsupported-Feature avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Roaming-Restricted-Due-To-Unsupported-Feature avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_roaming_restricted_unsupported_feature(struct avp *gavp, int32_t *ret);

/*Retrieves Subscribed-Periodic-RAU-TAU-Timer avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Subscribed-Periodic-RAU-TAU-Timer avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_subscribed_periodic_rau_tau_timer(struct avp *gavp, uint32_t *ret);

/*Retrieves MPS-Priority avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains MPS-Priority avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_mps_priority(struct avp *gavp, uint32_t *ret);

/*Retrieves VPLMN-LIPA-Allowed avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains VPLMN-LIPA-Allowed avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_vplmn_lipa_allowed(struct avp *gavp, int32_t *ret);

/*Retrieves Relay-Node-Indicator avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Relay-Node-Indicator avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_relay_node_indicator(struct avp *gavp, int32_t *ret);

/*Retrieves MDT-User-Consent avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains MDT-User-Consent avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_mdt_user_consent(struct avp *gavp, int32_t *ret);

/*Retrieves Subscribed-VSRVCC avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Subscribed-VSRVCC avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_subscribed_vsrvcc(struct avp *gavp, int32_t *ret);

/*Retrieves Subscription-Data-Flags avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Subscription-Data-Flags avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_subscription_data_flags(struct avp *gavp, uint32_t *ret);

/*Retrieves multiple GMLC-Number AVPs value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains GMLC-Number avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_gmlc_number(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves SS-Code avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains SS-Code avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ss_code_gavp(struct avp *gavp, unsigned char **ret);

/*Retrieves SS-Status avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains SS-Status avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ss_status(struct avp *gavp, unsigned char **ret);

/*Retrieves Notification-To-UE-User avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Notification-To-UE-User avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_notification_ue_user(struct avp *gavp, int32_t *ret);

/*Retrieves Client-Identity avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Client-Identity avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_client_identity(struct avp *gavp, unsigned char **ret);

/*Retrieves GMLC-Restriction avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains GMLC-Restriction avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_gmlc_restriction(struct avp *gavp, int32_t *ret);

/*Retrieves multiple PLMN-Client AVPs value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains PLMN-Client avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of int32_t values will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_plmn_client(struct avp *gavp, int32_t **array_ret, size_t *array_size);

/*Retrieves ServiceTypeIdentity avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains ServiceTypeIdentity avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_serviceTypeIdentity(struct avp *gavp, uint32_t *ret);

/*Retrieves multiple TS-Code AVPs value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains TS-Code avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ts_code_gavp(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves Max-Requested-Bandwidth-UL avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Max-Requested-Bandwidth-UL avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_max_requested_bw_ul(struct avp *gavp, uint32_t *ret);

/*Retrieves Max-Requested-Bandwidth-DL avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Max-Requested-Bandwidth-DL avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_max_requested_bw_dl(struct avp *gavp, uint32_t *ret);

/*Retrieves All-APN-Configurations-Included-Indicator avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains All-APN-Configurations-Included-Indicator avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_all_apn_configuration_included_indicator(struct avp *gavp, int32_t *ret);

/*Retrieves PDN-Type avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains PDN-Type avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_pdn_type(struct avp *gavp, int32_t *ret);

/*Retrieves VPLMN-Dynamic-Address-Allowed avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains VPLMN-Dynamic-Address-Allowed avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_vplmn_dynamic_address_allowed(struct avp *gavp, int32_t *ret);

/*Retrieves PDN-GW-Allocation-Type avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains PDN-GW-Allocation-Type avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_pdn_gw_allocation_type(struct avp *gavp, int32_t *ret);

/*Retrieves SIPTO-Permission avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains SIPTO-Permission avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_sipto_permission(struct avp *gavp, int32_t *ret);

/*Retrieves LIPA-Permission avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains LIPA-Permission avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_lipa_permission(struct avp *gavp, int32_t *ret);

/*Retrieves Restoration-Priority avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Restoration-Priority avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_restoration_priority(struct avp *gavp, uint32_t *ret);

/*Retrieves SIPTO-Local-Network-Permission avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains SIPTO-Local-Network-Permission avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_sipto_local_network_permission(struct avp *gavp, int32_t *ret);

/*Retrieves multiple Served-Party-IP-Address AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Served-Party-IP-Address avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_served_party_ip_address(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves QoS-Class-Identifier avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains QoS-Class-Identifier avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_qos_class_identifier(struct avp *gavp, int32_t *ret);

/*Retrieves Priority-Level avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Priority-Level avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_priority_level(struct avp *gavp, uint32_t *ret);

/*Retrieves Pre-emption-Capability avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Pre-emption-Capability avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_pre_emption_capability(struct avp *gavp, int32_t *ret);

/*Retrieves Pre-emption-Vulnerability avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Pre-emption-Vulnerability avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_pre_emption_vulnerability(struct avp *gavp, int32_t *ret);

/*Retrieves WLAN-offloadability-EUTRAN avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains WLAN-offloadability-EUTRAN avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_wlan_offloadability_eutran(struct avp *gavp, uint32_t *ret);

/*Retrieves WLAN-offloadability-UTRAN avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains WLAN-offloadability-UTRAN avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_wlan_offloadability_utran(struct avp *gavp, uint32_t *ret);

/*Retrieves Trace-Reference avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-Reference avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_trace_reference_gavp(struct avp *gavp, unsigned char **ret);

/*Retrieves Trace-Depth avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-Depth avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_trace_depth(struct avp *gavp, int32_t *ret);

/*Retrieves Trace-NE-Type-List avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-NE-Type-List avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_trace_ne_type_list(struct avp *gavp, unsigned char **ret);

/*Retrieves Trace-Interface-List avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-Interface-List avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_trace_interface_list(struct avp *gavp, unsigned char **ret);

/*Retrieves Trace-Event-List avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-Event-List avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_trace_event_list(struct avp *gavp, unsigned char **ret);

/*Retrieves OMC-Id avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains OMC-Id avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_omc_id(struct avp *gavp, unsigned char **ret);

/*Retrieves Trace-Collection-Entity avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-Collection-Entity avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_trace_collection_entity(struct avp *gavp, unsigned char **ret);

/*Retrieves Job-Type avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Job-Type avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_job_type(struct avp *gavp, int32_t *ret);

/*Retrieves multiple Cell-Global-Identity AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Cell-Global-Identity avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_cell_global_identity(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves multiple E-UTRAN-Cell-Global-Identity AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains E-UTRAN-Cell-Global-Identity avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_e_utran_cell_global_identity(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves multiple Routing-Area-Identity AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Routing-Area-Identity avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_routing_area_identity(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves multiple Location-Area-Identity AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Location-Area-Identity avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_location_area_identity(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves multiple Tracking-Area-Identity AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Tracking-Area-Identity avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_tracking_area_identity(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves List-Of-Measurements avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains List-Of-Measurements avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_list_of_measurements(struct avp *gavp, uint32_t *ret);

/*Retrieves Reporting-Trigger avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Reporting-Trigger avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_reporting_trigger(struct avp *gavp, uint32_t *ret);

/*Retrieves Report-Interval avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Report-Interval avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_report_interval(struct avp *gavp, int32_t *ret);

/*Retrieves Report-Amount avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Report-Amount avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_report_amount(struct avp *gavp, int32_t *ret);

/*Retrieves Event-Threshold-RSRP avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Event-Threshold-RSRP avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_event_threshold_rsrp(struct avp *gavp, uint32_t *ret);

/*Retrieves Event-Threshold-RSRQ avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Event-Threshold-RSRQ avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_event_threshold_rsrq(struct avp *gavp, uint32_t *ret);

/*Retrieves Logging-Interval avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Logging-Interval avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_logging_interval(struct avp *gavp, int32_t *ret);

/*Retrieves Logging-Duration avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Logging-Duration avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_logging_duration(struct avp *gavp, int32_t *ret);

/*Retrieves Measurement-Period-LTE avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Measurement-Period-LTE avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_measurement_period_lte(struct avp *gavp, int32_t *ret);

/*Retrieves Measurement-Period-UMTS avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Measurement-Period-UMTS avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_measurement_period_umts(struct avp *gavp, int32_t *ret);

/*Retrieves Collection-Period-RMM-LTE avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Collection-Period-RMM-LTE avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_collection_period_rmm_lte(struct avp *gavp, int32_t *ret);

/*Retrieves Collection-Period-RRM-UMTS avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Collection-Period-RRM-UMTS avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_collection_period_rmm_umts(struct avp *gavp, int32_t *ret);

/*Retrieves Positioning-Method avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Positioning-Method avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_positioning_method(struct avp *gavp, unsigned char **ret);

/*Retrieves Measurement-Quantity avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Measurement-Quantity avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_measurement_quantity(struct avp *gavp, unsigned char **ret);

/*Retrieves Event-Threshold-Event-1F avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Event-Threshold-Event-1F avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_event_threshold_event_1f(struct avp *gavp, uint32_t *ret);

/*Retrieves Event-Threshold-Event-1I avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Event-Threshold-Event-1I avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_event_threshold_event_1i(struct avp *gavp, uint32_t *ret);

/*Retrieves multiple MDT-Allowed-PLMN-Id AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains MDT-Allowed-PLMN-Id avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_mdt_allowed_plmn_id(struct avp *gavp, unsigned char ***array_ret, size_t *array_size);

/*Retrieves Complete-Data-List-Included-Indicator avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Complete-Data-List-Included-Indicator avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_complete_data_list_included_indicator(struct avp *gavp, int32_t *ret);

/*Retrieves PDP-Type avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains PDP-Type avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_pdp_type(struct avp *gavp, unsigned char **ret);

/*Retrieves PDP-Address avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains PDP-Address avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_pdp_address(struct avp *gavp, unsigned char **ret);

/*Retrieves QoS-Subscribed avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains QoS-Subscribed avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_qos_subscribed(struct avp *gavp, unsigned char **ret);

/*Retrieves Ext-PDP-Type avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Ext-PDP-Type avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ext_pdp_type(struct avp *gavp, unsigned char **ret);

/*Retrieves Ext-PDP-Address avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Ext-PDP-Address avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ext_pdp_address(struct avp *gavp, unsigned char **ret);

/*Retrieves CSG-Id avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains CSG-Id avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_csg_id(struct avp *gavp, uint32_t *ret);

/*Retrieves Expiration-Date avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Expiration-Date avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_expiration_date(struct avp *gavp, unsigned char **ret);

/*Retrieves ProSe-Permission avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains ProSe-Permission avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_prose_permission(struct avp *gavp, uint32_t *ret);

/*Retrieves multiple Reset-ID AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Reset-ID avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_reset_id(struct msg *msg, unsigned char ***array_ret, size_t *array_size);

/*Retrieves Number-Of-Requested-Vectors avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Number-Of-Requested-Vectors avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_number_of_requested_vectors(struct avp *gavp, uint32_t *ret);

/*Retrieves Immediate-Response-Preferred avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Immediate-Response-Preferred avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_immediate_response_preferred(struct avp *gavp, uint32_t *ret);

/*Retrieves Re-synchronization-Info avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Re-synchronization-Info avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_re_synchronization_info(struct avp *gavp, unsigned char **ret);

/*Retrieves Item-Number avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Item-Number avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_item_number(struct avp *gavp, uint32_t *ret);

/*Retrieves RAND avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains RAND avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_rand(struct avp *gavp, unsigned char **ret);

/*Retrieves XRES avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains XRES avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_xres(struct avp *gavp, unsigned char **ret);

/*Retrieves AUTN avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains AUTN avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_autn(struct avp *gavp, unsigned char **ret);

/*Retrieves KASME avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains KASME avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_kasme(struct avp *gavp, unsigned char **ret);

/*Retrieves Confidentiality-Key avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Confidentiality-Key avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_confidentiality_key(struct avp *gavp, unsigned char **ret);

/*Retrieves Integrity-Key avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Integrity-Key avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_integrity_key(struct avp *gavp, unsigned char **ret);

/*Retrieves Kc avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Kc avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_kc(struct avp *gavp, unsigned char **ret);

/*Retrieves SRES avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains SRES avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_sres(struct avp *gavp, unsigned char **ret);

/*Retrieves Cancellation-Type avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_cancellation_type(struct msg *msg, int32_t *ret);

/*Retrieves CLR-Flags avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_clr_flags(struct msg *msg, uint32_t *ret);

/*Retrieves IDR- Flags avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_idr_flags(struct msg *msg, uint32_t *ret);

/*Retrieves IMS-Voice-Over-PS-Sessions-Supported avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ims_voice_over_ps_sessions_supported(struct msg *msg, int32_t *ret);

/*Retrieves Last-UE-Activity-Time avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_last_ue_activity_time(struct msg *msg, unsigned char **ret);

/*Retrieves IDA- Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ida_flags(struct msg *msg, uint32_t *ret);

/*Retrieves User-State avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Complete-Data-List-Included-Indicator avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_user_state(struct avp *gavp, int32_t *ret);

/*Retrieves Geographical-Information avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Geographical-Information avp.  
		ret: a pointer to a pointer where the result will be stored.The value is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_geographical_information(struct avp *gavp, unsigned char **ret);

/*Retrieves Geodetic-Information avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Geodetic-Information avp.  
		ret: a pointer to a pointer where the result will be stored.The value is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_geodetic_information(struct avp *gavp, unsigned char **ret);

/*Retrieves Current-Location-Retrieved avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Current-Location-Retrieved avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_current_location_retrieved(struct avp *gavp, int32_t *ret);

/*Retrieves Age-Of-Location-Information avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Age-Of-Location-Information avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_age_of_location_information(struct avp *gavp, uint32_t *ret);

/*Retrieves CSG-Access-Mode avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains CSG-Access-Mode avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_csg_access_mode(struct avp *gavp, int32_t *ret);

/*Retrieves CSG-Membership-Indication avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains CSG-Membership-Indication avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_csg_membership_indication(struct avp *gavp, int32_t *ret);

/*Retrieves Time-Zone avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Time-Zone avp.  
		ret: a pointer to a pointer where the result will be stored.The value is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_time_zone(struct avp *gavp, unsigned char **ret);

/*Retrieves Daylight-Saving-Time avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Daylight-Saving-Time avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_daylight_saving_time(struct avp *gavp, int32_t *ret);

/*Retrieves DSR-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_dsr_flags(struct msg *msg, uint32_t *ret);

/*Retrieves Context-Identifier avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_context_identifier(struct msg *msg, uint32_t *ret);

/*Retrieves multiple Context-Identifier AVPs' values from group avp 
	parameter:
		msg: a pointer to a message structure(specifically DSR	message) that contains Context-Identifier avp.  
		ret: address of a pointer where a pointer to the resulting dynamic array of uint_32 values will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_context_identifier_array(struct msg *msg, uint32_t **array_ret, size_t *array_size);

/*Retrieves Trace-Reference avp value from from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_trace_reference(struct msg *msg, unsigned char **ret);

/*Retrieves multiple TS-Code AVPs value from message
	parameter:
		msg: a pointer to the message pointer.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ts_code(struct msg *msg, unsigned char ***array_ret, size_t *array_size);

/*Retrieves multiple SS-Code AVPs value from message
	parameter:
		msg: a pointer to the message pointer.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_ss_code(struct msg *msg, unsigned char ***array_ret, size_t *array_size);

/*Retrieves DSA-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_dsa_flags(struct msg *msg, uint32_t *ret);

/*Retrieves PUR-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_pur_flags(struct msg *msg, uint32_t *ret);

/*Retrieves PUA-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_pua_flags(struct msg *msg, uint32_t *ret);

/*Retrieves multiple User-Id AVPs value from message
	parameter:
		msg: a pointer to the message pointer.  
		ret: address of a pointer where a pointer to the resulting dynamic array of strings will be stored. The array should be freed unless the return value is 1(failure).
		array_size: the number of elements in the array. if return is 1(failure) array_size will be set to 0.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_user_id(struct msg *msg, unsigned char ***array_ret, size_t *array_size);

/*Retrieves Visited-Network-Identifier avp value from message
	parameter:
		msg: a pointer to the message pointer.  
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_visited_network_identifier(struct msg *msg, unsigned char **ret);

/*Retrieves Service-Selection avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_service_selection(struct msg *msg, unsigned char **ret);

/*Retrieves Alert-Reason avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_alert_reason(struct msg *msg, int32_t *ret);

/*Retrieves NOR-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_nor_flags(struct msg *msg, uint32_t *ret);

/*Retrieves Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_homogeneous_support_ims_vop_sessions(struct msg *msg, int32_t *ret);

/*Retrieves Feature-List-ID avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Feature-List-ID avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success, 1 on failure
*/
inline int ss_get_feature_list_id(struct avp *gavp, uint32_t *ret);

/*Retrieves Feature-List avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Feature-List avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success,  1 on failure
*/
inline int ss_get_feature_list(struct avp *gavp, uint32_t *ret);

#endif
