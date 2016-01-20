
#include "test.h"

diameterid * gb_destination_realm = (diameterid *)"localdomain";
utf8string *gb_user_name = (utf8string *)"244444123456789";
unsigned32 gb_feature_list_id[] = { 1, 2};
unsigned32 gb_feature_list[] = { 2, 3}; 
utf8string *gb_imei = (utf8string *)"2345";
utf8string *gb_software_version = (utf8string *)"22";
octetstring *gb_meid = (octetstring *)"2345";
enum rat_type gb_rat_type = UTRAN;	
unsigned32 gb_ulr_flags = 8;
unsigned32 gb_ula_flags = 0;
enum ue_srvcc_capability gb_ue_srvcc_capability = UE_SRVCC_SUPPORTED;
octetstring gb_visited_plmn_id[2][4]= {{0x01,0x10,0x01,'\0'},{0x01,0x10,0x02,'\0'}}; /*MCC = 011, MNC = 001*/	
octetstring  gb_sgsn_number [] = {0x25,0x14,0x56};
enum homogeneous_support_of_ims_voice_over_ps_sessions gb_homogeneous_support_ims_voice_over_ps_sessions = HOMO_IMS_VOICE_OVER_PS_NOT_SUPPORTED;
address *gb_gmlc_address = (address *)"gmlc.local";
unsigned32 gb_context_identifier[] = {1,2,3};
utf8string *gb_service_selection = (utf8string *)"serviceSelection";
address  gb_home_agent_address_v4 [] = {'a','b','c','d', '\0'};
address  gb_home_agent_address_v6 [] = {'a','b','c','d','a','b','c','d','a','b','c','d','a','b','c','d','\0'};
diameterid *gb_home_agent_host_host = (diameterid *) "pdngateway1";
diameterid *gb_home_agent_host_realm = (diameterid *) "epc.mnc001.mcc001.3gppnetwork.org";
octetstring *gb_visited_network_identifier = (octetstring *)"visited-net-id";
octetstring *gb_mme_number_for_mt_sms = (octetstring *)"mme-23";
enum sms_register_request gb_sms_register_request = SMS_REGISTRATION_REQUIRED;
diameterid *gb_coupled_node_diameter_id = (diameterid *)"coupl-node";
enum cancellation_type gb_cancellation_type = SUBCRIPTION_WITHDRAWAL;	
unsigned32 gb_clr_flags = 3;
octetstring *gb_reset_ids[] = {(octetstring *)"244444", (octetstring *)"244445", (octetstring *)"244446"};
enum all_apn_configuration_included_indicator gb_all_apn_conf_included_indicator = All_APN_CONFIGURATIONS_INCLUDED;
enum complete_data_list_included_indicator gb_comp_dt_lst_inc_ind = All_PDP_CONTEXTS_INCLUDED;

unsigned32 gb_number_of_requested_vectors = 2;
unsigned32 gb_immediate_response_preferred = 1;
octetstring gb_re_synchronization_info[] = {0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11, 0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11, '\0'};
unsigned32 gb_idr_flags = 1;
enum ims_voice_over_ps_sessions_supported gb_ims_vop_sessions_supported = SUPPORTED;
ss_time gb_last_ue_activity_time[] = {0x01,0xff,0xff,0xff,'\0'}; 
unsigned32 gb_ida_flags = 1;
enum user_state gb_mme_user_state = DETACHED;
octetstring gb_e_utran_cgi[] = {0x01,0x02,0x02,0x01,0x02,0x02,0x03,'\0'};
octetstring gb_tracking_area_id[] = {0x01,0x02,0x02,0x01,0x02,'\0'};
octetstring gb_geographical_info[] = {0x01,0x02,0x02,0x01,0x02,0x02,0x03, 0x04,'\0'};
octetstring gb_geodetic_info[] = {0x01,0x02,0x02,0x01,0x02,0x02,0x03,0x04,0x01,0x02,'\0'};
enum current_location_retrieved gb_current_location_retrieved = ACTIVE_LOCATION_RETRIEVAL;
unsigned32 gb_age_of_location_info = 10;
unsigned32 gb_csg_id = 1;
enum csg_access_mode gb_csg_access_mode = CLOSED;
enum csg_membership_indication gb_csg_membership_indication = Not_CSG_MEMBER;
utf8string * gb_time_zone = (utf8string *)"+8";
enum daylight_saving_time gb_daylight_saving_time = NO_ADJUSTMENT;

unsigned32 gb_dsr_flags = 64;
unsigned32 gb_dsa_flags = 1;
octetstring gb_trace_reference[] = {0x01,0x11,0x01,0x01,0x01,0x02,'\0'};
octetstring gb_ts_code[][2] = {{0x01,'\n'},{0x02,'\0'}};
octetstring gb_ss_code[][2] = {{0x01,'\n'},{0x02,'\0'}};
unsigned32 gb_pur_flags = 4;
unsigned32 gb_pua_flags = 1;
utf8string *gb_user_id[]= {(utf8string *)"24444412", (utf8string *)"24444412"};
unsigned32 gb_nor_flags = 8;
enum alert_reason gb_alert_reason = UE_PRESENT;
