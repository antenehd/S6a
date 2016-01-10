
#include <stdlib.h>

#include "ssix_interface.h"
#include "internal.h"

/*Retrieve string value from AVP*/
static inline int avp_str_value(struct avp *avp, unsigned char **val){

	struct avp_hdr *hdr = NULL;
	
	if(!val) return EINVAL;

	/*extract value from AVP structure*/
	SS_CHECK( fd_msg_avp_hdr( avp, &hdr ));
    *val = hdr->avp_value->os.data;

	return 0;
}

/*Retrieve interger value from AVP*/
static inline int avp_int_value(struct avp *avp,  int32_t *val){

	struct avp_hdr *hdr = NULL;

	if(!val) return EINVAL;

	/*extract value from AVP structure*/
	SS_CHECK( fd_msg_avp_hdr( avp, &hdr ));
    *val = hdr->avp_value->i32;

	return 0;
}

/*Retrieve uint32_t value from avp*/
static inline int avp_uint_value(struct avp *avp, uint32_t *val){

	struct avp_hdr *hdr = NULL;

	if(!val) return EINVAL;

	/*extract value from AVP structure*/
	SS_CHECK( fd_msg_avp_hdr( avp, &hdr ));
    *val = hdr->avp_value->u32;

	return 0;
}

/*Retrieves string value of the first avp indicated by 'dict' with in  message 'msg' and store the resulting pointer to 'target'*/
static inline int get_str_value(struct msg *msg, struct dict_object *dict, unsigned char **val){

	struct avp *avp = NULL;	

	/*search for 'dict' type avp inside message 'msg'*/
	SS_CHECK( fd_msg_search_avp( msg, dict, &avp) );

	/*returns 0 if value is found otherwise EINVAL*/
	return avp_str_value(avp, val);	

}

/*Retrieves int value of the first avp indicated by 'dict' with in  message 'msg' and store the resulting pointer to 'target'*/
static inline int get_int_value(struct msg *msg, struct dict_object *dict,  int32_t *val){

	struct avp *avp = NULL;

	/*check for 'dict' type avp inside message 'msg'*/
	SS_CHECK( fd_msg_search_avp ( msg, dict, &avp) );

	/*returns 0 if value is found otherwise EINVAL*/
	return avp_int_value(avp, val);
}

/*Retrieves uint32_t value of the first avp indicated by 'dict' with in  message 'msg' and store the resulting pointer to 'target'*/
static inline int get_uint_value(struct msg *msg, struct dict_object *dict, uint32_t *val){

	struct avp *avp = NULL;

	/*check for 'dict' type avp inside message 'msg'*/
	SS_CHECK( fd_msg_search_avp ( msg, dict, &avp) );
	
	/*returns 0 if value is found otherwise EINVAL*/ 
	return avp_uint_value(avp, val);
}

/*Retrieves string value of the first avp indicated by 'dict' with in group avp 'gavp' and store the resulting pointer to 'target'*/
static inline int get_str_value_gavp(struct avp *gavp, struct dict_object *dict, unsigned char **val){

	struct avp *avp = NULL;

	/*check for 'dict' type avp inside message 'gavp'*/
	SS_CHECK(fd_avp_search_avp ( gavp, dict, &avp, MSG_BRW_FIRST_CHILD ));

	/*returns 0 if value is found otherwise EINVAL*/
	return avp_str_value(avp, val);
}

/*Retrieves string value of the first avp indicated by 'dict' with in group avp 'gavp' and store the resulting pointer to 'target'*/
static inline int get_uint_value_gavp(struct avp *gavp, struct dict_object *dict, uint32_t *val){

	struct avp *avp = NULL;

	/*check for 'dict' type avp inside message 'gavp'*/
	SS_CHECK(fd_avp_search_avp( gavp, dict, &avp, MSG_BRW_FIRST_CHILD));

	/*returns 0 if value is found otherwise EINVAL*/
	return avp_uint_value(avp, val);
}

/*Retrieves string value of the first avp indicated by 'dict' with in group avp 'gavp' and store the resulting pointer to 'target'*/
static inline int get_int_value_gavp(struct avp *gavp, struct dict_object *dict,  int32_t *val){

	struct avp *avp = NULL;

	/*check for 'dict' type avp inside message 'gavp'*/
	SS_CHECK(fd_avp_search_avp( gavp, dict, &avp, MSG_BRW_FIRST_CHILD));

	/*returns 0 if value is found written otherwise return EINVAL*/
	return avp_int_value(avp, val);
}

/*Retrieves multiple string values of multiple similar AVPs found in a message 'msg'. It retrieves those that are 
found on top level(i.e. direct children of 'msg')*/
static inline int get_str_array(struct msg * msg, struct dict_object * dict, unsigned char *** array_val, size_t *array_size){

	struct avp *avp = NULL;
	struct avp *avp2 = NULL;
	unsigned char **temp = NULL;
	size_t num = 0;

	if((!array_val) || (!array_size)) return EINVAL;
			

	*array_size = 0;

	/*search in to message the first AVP of type 'dict'*/
	SS_CHECK( fd_msg_search_avp( msg, dict, &avp));
	while(avp){

		/*allocate memory for the values*/
		if(NULL == (temp = realloc(temp, sizeof(char *) * (num + 1))))	return ENOMEM;
		
		/*retrieves value from AVP 'avp' and write it to location pointed by 'temp + num'*/
		if( avp_str_value(avp, temp + num) != 0){
			
			/*if value retrieval fails free memory*/
			free(temp);
			return EINVAL;
		}
			
		/*search for the first AVP of type 'dict' which is found after 'avp' at the same level (i.e no child or parent)*/
		SS_CHECK(fd_avp_search_avp ( avp, dict, &avp2, MSG_BRW_NEXT ));
		avp = avp2;

		num ++;
	}
		
	*array_size = num;
	*array_val = temp;

	return 0;
}

/*Retrieves multiple string values of multiple similar AVPs found in a group AVP 'gavp'*/
static inline int get_str_gavp_array(struct avp * gavp, struct dict_object * dict, unsigned char *** array_val, size_t *array_size){

	struct avp *avp = NULL;
	struct avp *avp2 = NULL;
	unsigned char **temp = NULL;
	size_t num = 0;

	if((!array_val) || (!array_size)) return EINVAL;

	*array_size = 0;

	/*search in to message for the first AVP of type 'dict'*/
	SS_CHECK(fd_avp_search_avp ( gavp, dict, &avp, MSG_BRW_FIRST_CHILD ));
	while(avp){
		
		/*allocate memory for the values*/
		if( NULL == (temp = realloc(temp, sizeof(char *) * (num + 1)))) return ENOMEM;

		/*retrieves value from AVP 'avp' and write it to location pointed by 'temp + num'*/
		if( 0 != avp_str_value(avp, temp + num)){

			free(temp);
			return EINVAL;
		}

		/*search for the first AVP of type 'dict' which is found after 'avp' at the same level (i.e no child or parent)*/
		SS_CHECK(fd_avp_search_avp ( avp, dict, &avp2, MSG_BRW_NEXT ));
		avp = avp2;

		num ++;
	}
		
	*array_size = num;
	*array_val = temp;

	return 0;
}

/*Retrieves multiple integer values of multiple similar AVPs found in a group AVP 'gavp'*/
static inline int get_int_gavp_array(struct avp * gavp, struct dict_object * dict, int32_t ** array_val, size_t *array_size){

	struct avp *avp = NULL;
	struct avp *avp2 = NULL;
	int32_t *temp = NULL;
	size_t num = 0;

	if((!array_val) || (!array_size)) return EINVAL;			

	*array_size = 0;

	/*search for the first child AVP of type 'dict' in message 'msg'*/
	SS_CHECK(fd_avp_search_avp ( gavp, dict, &avp, MSG_BRW_FIRST_CHILD ));
	while(avp){

		/*allocate memory for the values*/
		if( NULL == (temp = realloc(temp, sizeof(int32_t) * (num + 1)))) return ENOMEM;

		/*retrieves value from AVP 'avp' and write it to location pointed by 'temp + num'*/
		if( avp_int_value(avp, temp + num) != 0){

			free(temp);
			return EINVAL;
		}

		/*search for the first AVP of type 'dict' which is found after 'avp' at the same level (i.e no child or parent)*/		
		SS_CHECK(fd_avp_search_avp ( avp, dict, &avp2, MSG_BRW_NEXT ));
		avp = avp2;

		num ++;
	}

	*array_size = num;
	*array_val = temp;

	return 0;
}

/*Retrieves multiple uint32_t values of multiple similar AVPs found in message structure 'msg'*/
static inline int get_uint_array(struct msg * msg, struct dict_object * dict, uint32_t ** array_val, size_t *array_size){

	struct avp *avp = NULL;
	struct avp *avp2 = NULL;
	uint32_t *temp = NULL;
	size_t num = 0;
	
	if((!array_val) || (!array_size))
			return EINVAL;

	*array_size = 0;

	/*search for the first child AVP of type 'dict' in message 'msg'*/
	SS_CHECK(fd_msg_search_avp ( msg, dict, &avp));
	while(avp){

		if( NULL == (temp = realloc(temp, sizeof(uint32_t) * (num + 1)))) return ENOMEM;
		
		/*retrieves value from AVP 'avp' and write it to location pointed by 'temp + num'*/
		if( avp_uint_value(avp, temp + num) != 0){

			free(temp);
			return EINVAL;
		}
		
		/*search for the first AVP of type 'dict' which is found after 'avp' at the same level (i.e no child or parent)*/
		SS_CHECK(fd_avp_search_avp ( avp, dict, &avp2, MSG_BRW_NEXT ));
		avp = avp2;

		num ++;
	}
		
	*array_size = num;
	*array_val = temp;

	return 0;
}

/*Retrieves Destination-Host avp value from message */
int ss_get_destination_host(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_destination_host, ret);
}

/*Retrieves Destination-Host avp value from message */
int ss_get_destination_host_gavp(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_destination_host, ret);
}

/*Retrieves originating host avp value from message */
int ss_get_origin_host(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_origin_host, ret);
}

/*Retrieves Destination-Realm avp value from message*/
int ss_get_destination_realm(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_destination_realm, ret);
}

/*Retrieves Destination-Realm avp value from group AVP */
int ss_get_destination_realm_gavp(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_destination_realm, ret);
}

/*Retrieves originating realm avp value from message */
int ss_get_origin_realm(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_origin_realm, ret);
}

/*Retrieves User-Name (imsi) avp value from message*/
int ss_get_user_name(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_user_name, ret);
}

/*Retrieves RAT-Type avp value from message*/
int ss_get_rat_type(struct msg *msg, int32_t *ret){	

	return get_int_value(msg, ss_rat_type, ret);
}

/*Retrieves ULR-Flags avp value from message */
int ss_get_ulr_flags(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_ulr_flags, ret);
}

/*Retrieves UE-SRVCC-Capability avp value from message*/
int ss_get_ue_srvcc_capability(struct msg *msg, int32_t *ret){	

	return get_int_value(msg, ss_ue_srvcc_capability, ret);
}

/*Retrieves Visited-PLMN-Id avp value from message */
int ss_get_visited_plmn_id(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_visited_plmn_id, ret);
}

/*Retrieves SGSN-Number avp value from message */
int ss_get_sgsn_number(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_sgsn_number, ret);
}

/*Retrieves Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions avp value from message */
int ss_get_homogeneous_support_ims(struct msg *msg, int32_t *ret){	

	return get_int_value(msg, ss_homogeneous_support_of_ims_voice_over_ps_sessions, ret);
}

/*Retrieves GMLC-Address avp value from message*/
int ss_get_gmlc_address(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_gmlc_address, ret);
}

/*Retrieves MME-Number-for-MT-SMS avp value from message*/
int ss_get_mme_number_for_mt_sms(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_mme_number_for_mt_sms, ret);
}

/*Retrieves SMS-Register-Request avp value from message*/
int ss_get_sms_register_request(struct msg *msg, int32_t *ret){	

	return get_int_value(msg, ss_sms_register_request, ret);
}

/*Retrieves Coupled-Node-Diameter-ID avp value from message*/
int ss_get_coupled_node_diameter_id(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_coupled_node_diameter_id, ret);
}

/*Retrieves imei avp value from group avp*/
int ss_get_imei(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_imei, ret);
}

/*Retrieves Software-Version avp value from group avp */
int ss_get_software_version(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_software_version, ret);
}

/*Retrieves 3gpp2-meid avp value from group avp*/
int ss_get_3gpp2_meid(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_3gpp2_meid, ret);
}

/*Retrieves Context-Identifier avp value from group avp*/
int ss_get_context_identifier_gavp(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_context_identifier, ret);
}

/*Retrieves Service-Selection avp value from group avp */
int ss_get_service_selection_gavp(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_service_selection, ret);
}

/*Retrieves multiple Service-Selection AVPs' values from group avp*/
int ss_get_service_selection_array(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_service_selection, array_ret, array_size);		
}

/*Retrieves Visited-Network-Identifier avp value from group avp */
int ss_get_visited_network_identifier_gavp(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_visited_network_identifier, ret);
}

/*Retrieves multiple MIP-Home-Agent-Address AVPs' values from group avp */
int ss_get_mip_home_agent_address_array(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_mip_home_agent_address, array_ret, array_size);		
}

/*Retrieves Visited-PLMN-Id avp value from group avp */
int ss_get_visited_plmn_id_gavp(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_visited_plmn_id, ret);
}

/*Retrieves multiple Visited-PLMN-Id AVPs' values from group avp*/
int ss_get_visited_plmn_id_array(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_visited_plmn_id, array_ret, array_size);		
}

/*Retrieves Result-Code avp value from message*/
int ss_get_result_code(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_result_code, ret);
}

/*Retrieves Error-Diagnostic avp value from message */
int ss_get_error_diagnostic(struct msg *msg, int32_t *ret){	

	return get_int_value(msg, ss_error_diagnostic, ret);
}

/*Retrieves ULA-Flags avp value from message*/
int ss_get_ula_flags(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_ula_flags, ret);
}

/*Retrieves Vendor-Id avp value from group avp*/
int ss_get_vendor_id(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_vendor_id, ret);
}

/*Retrieves Experimental-Result-Code avp value from group avp*/
int ss_get_experimental_result_code(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_experimental_result_code, ret);
}

/*Retrieves Subscriber-Status avp value from group avp */
int ss_get_subscriber_status(struct avp *gavp, int32_t *ret){	

	return get_int_value_gavp(gavp, ss_subscriber_status, ret);
}

/*Retrieves MSISDN avp value from group avp*/
int ss_get_msisdn(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_msisdn, ret);
}

/*Retrieves A-MSISDN avp value from group avp*/
int ss_get_a_msisdn(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_a_msisdn, ret);
}

/*Retrieves STN-SR avp value from group avp*/
int ss_get_stn_sr(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_stn_sr, ret);
}

/*Retrieves ICS-Indicator avp value from group avp*/
int ss_get_ics_indicator(struct avp *gavp, int32_t *ret){	

	return get_int_value_gavp(gavp, ss_ics_indicator, ret);
}

/*Retrieves Network-Access-Mode avp value from group avp*/
int ss_get_network_access_mode(struct avp *gavp, int32_t *ret){	

	return get_int_value_gavp(gavp, ss_network_access_mode, ret);
}

/*Retrieves Operator-Determined-Barring avp value from group avp*/
int ss_get_operator_determined_barring(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_operator_determined_barring, ret);
}

/*Retrieves HPLMN-ODB avp value from group avp*/
int ss_get_hplmn_odb(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_hplmn_odb, ret);
}

/*Retrieves Regional-Subscription-Zone-Code avp value from group avp*/
int ss_get_regional_subscription_zone_code(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_regional_subscription_zone_code, ret);
}

/*Retrieves Access-Restriction-Data avp value from group avp */
int ss_get_access_restriction_data(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_access_restriction_data, ret);
}

/*Retrieves APN-OI-Replacement avp value from group avp*/
int ss_get_apn_oi_replacement(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_apn_oi_replacement, ret);
}

/*Retrieves 3GPP-Charging-Characteristics avp value from group avp*/
int ss_get_3gpp_charging_characteristics(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_3gpp_charging_characteristics, ret);
}

/*Retrieves RAT-Frequency-Selection-Priority-ID avp value from group avp*/
int ss_get_rat_frequency_selection_priority_id(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_rat_frequency_selection_priority_id, ret);
}

/*Retrieves Roaming-Restricted-Due-To-Unsupported-Feature avp value from group avp*/
int ss_get_roaming_restricted_unsupported_feature(struct avp *gavp, int32_t *ret){	

	return get_int_value_gavp(gavp, ss_roaming_restricted_due_to_unsupported_feature, ret);
}

/*Retrieves Subscribed-Periodic-RAU-TAU-Timer avp value from group avp*/
int ss_get_subscribed_periodic_rau_tau_timer(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_subscribed_priodic_rau_tau_timer, ret);
}

/*Retrieves MPS-Priority avp value from group avp */
int ss_get_mps_priority(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_mps_priority, ret);
}

/*Retrieves VPLMN-LIPA-Allowed avp value from group avp*/
int ss_get_vplmn_lipa_allowed(struct avp *gavp, int32_t *ret){	

	return get_int_value_gavp(gavp, ss_vplmn_lipa_allowed, ret);
}

/*Retrieves Relay-Node-Indicator avp value from group avp*/
int ss_get_relay_node_indicator(struct avp *gavp, int32_t *ret){	

	return get_int_value_gavp(gavp, ss_relay_node_indicator, ret);
}

/*Retrieves MDT-User-Consent avp value from group avp */
int ss_get_mdt_user_consent(struct avp *gavp, int32_t *ret){	

	return get_int_value_gavp(gavp, ss_mdt_user_consent, ret);
}

/*Retrieves Subscribed-VSRVCC avp value from group avp*/
int ss_get_subscribed_vsrvcc(struct avp *gavp, int32_t *ret){	

	return get_int_value_gavp(gavp, ss_subscribed_vsrvcc, ret);
}

/*Retrieves Subscription-Data-Flags avp value from group avp*/
int ss_get_subscription_data_flags(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_subscription_data_flags, ret);
}

/*Retrieves multiple GMLC-Number AVPs value from group avp */
int ss_get_gmlc_number(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_gmlc_number, array_ret, array_size);		
}

/*Retrieves SS-Code avp value from group avp*/
int ss_get_ss_code_gavp(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_ss_code, ret);
}

/*Retrieves SS-Status avp value from group avp*/
int ss_get_ss_status(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_ss_status, ret);
}

/*Retrieves Notification-To-UE-User avp value from group avp*/
int ss_get_notification_ue_user(struct avp *gavp, int32_t *ret){	

	return get_int_value_gavp(gavp, ss_notification_to_ue_user, ret);
}

/*Retrieves Client-Identity avp value from group avp*/
int ss_get_client_identity(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_client_identity, ret);
}

/*Retrieves GMLC-Restriction avp value from group avp*/
int ss_get_gmlc_restriction(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_gmlc_restriction, ret);
}

/*Retrieves multiple PLMN-Client AVPs value from group avp*/
int ss_get_plmn_client(struct avp *gavp, int32_t **array_ret, size_t *array_size){	
	
	return get_int_gavp_array(gavp, ss_plmn_client, array_ret, array_size);		
}

/*Retrieves ServiceTypeIdentity avp value from group avp*/
int ss_get_serviceTypeIdentity(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_servicetypeidentity, ret);
}

/*Retrieves multiple TS-Code AVPs value from group avp*/
int ss_get_ts_code_gavp(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_ts_code, array_ret, array_size);		
}

/*Retrieves Max-Requested-Bandwidth-UL avp value from group avp */
int ss_get_max_requested_bw_ul(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_max_requested_bandwidth_ul, ret);
}

/*Retrieves Max-Requested-Bandwidth-DL avp value from group avp*/
int ss_get_max_requested_bw_dl(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_max_requested_bandwidth_dl, ret);
}

/*Retrieves All-APN-Configurations-Included-Indicator avp value from group avp*/
int ss_get_all_apn_configuration_included_indicator(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_all_apn_configurations_included_indicator, ret);
}

/*Retrieves PDN-Type avp value from group avp */
int ss_get_pdn_type(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_pdn_type, ret);
}

/*Retrieves VPLMN-Dynamic-Address-Allowed avp value from group avp*/
int ss_get_vplmn_dynamic_address_allowed(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_vplmn_dynamic_address_allowed, ret);
}

/*Retrieves PDN-GW-Allocation-Type avp value from group avp */
int ss_get_pdn_gw_allocation_type(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_pdn_gw_allocation_type, ret);
}

/*Retrieves SIPTO-Permission avp value from group avp*/
int ss_get_sipto_permission(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_sipto_permission, ret);
}

/*Retrieves LIPA-Permission avp value from group avp*/
int ss_get_lipa_permission(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_lipa_permission, ret);
}

/*Retrieves Restoration-Priority avp value from group avp*/
int ss_get_restoration_priority(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_restoration_priority, ret);
}

/*Retrieves SIPTO-Local-Network-Permission avp value from group avp*/
int ss_get_sipto_local_network_permission(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_sipto_local_network_permission, ret);
}

/*Retrieves multiple Served-Party-IP-Address AVPs' values from group avp*/
int ss_get_served_party_ip_address(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_served_party_ip_address, array_ret, array_size);		
}

/*Retrieves QoS-Class-Identifier avp value from group avp*/
int ss_get_qos_class_identifier(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_qos_class_identifier, ret);
}

/*Retrieves Priority-Level avp value from group avp*/
int ss_get_priority_level(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_priority_level, ret);
}

/*Retrieves Pre-emption-Capability avp value from group avp*/
int ss_get_pre_emption_capability(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_pre_emption_capability, ret);
}

/*Retrieves Pre-emption-Vulnerability avp value from group avp*/
int ss_get_pre_emption_vulnerability(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_pre_emption_vulnerability, ret);
}

/*Retrieves WLAN-offloadability-EUTRAN avp value from group avp*/
int ss_get_wlan_offloadability_eutran(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_wlan_offloadability_eutran, ret);
}

/*Retrieves WLAN-offloadability-UTRAN avp value from group avp */
int ss_get_wlan_offloadability_utran(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_wlan_offloadability_utran, ret);
}

/*Retrieves Trace-Reference avp value from group avp*/
int ss_get_trace_reference_gavp(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_trace_reference, ret);
}

/*Retrieves Trace-Depth avp value from group avp */
int ss_get_trace_depth(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_trace_depth, ret);
}

/*Retrieves Trace-NE-Type-List avp value from group avp*/
int ss_get_trace_ne_type_list(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_trace_ne_type_list, ret);
}

/*Retrieves Trace-Interface-List avp value from group avp*/
int ss_get_trace_interface_list(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_trace_interface_list, ret);
}

/*Retrieves Trace-Event-List avp value from group avp*/
int ss_get_trace_event_list(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_trace_event_list, ret);
}

/*Retrieves OMC-Id avp value from group avp */
int ss_get_omc_id(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_omc_id, ret);
}

/*Retrieves Trace-Collection-Entity avp value from group avp*/
int ss_get_trace_collection_entity(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_trace_collection_entity, ret);
}

/*Retrieves Job-Type avp value from group avp*/
int ss_get_job_type(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_job_type, ret);
}

/*Retrieves multiple Cell-Global-Identity AVPs' values from group avp */
int ss_get_cell_global_identity(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_cell_global_identity, array_ret, array_size);		
}

/*Retrieves multiple E-UTRAN-Cell-Global-Identity AVPs' values from group avp */
int ss_get_e_utran_cell_global_identity(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_e_utran_cell_global_identity, array_ret, array_size);		
}

/*Retrieves multiple Routing-Area-Identity AVPs' values from group avp*/
int ss_get_routing_area_identity(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_routing_area_identity, array_ret, array_size);		
}

/*Retrieves multiple Location-Area-Identity AVPs' values from group avp*/
int ss_get_location_area_identity(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_location_area_identity, array_ret, array_size);		
}

/*Retrieves multiple Tracking-Area-Identity AVPs' values from group avp*/
int ss_get_tracking_area_identity(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_tracking_area_identity, array_ret, array_size);		
}

/*Retrieves List-Of-Measurements avp value from group avp*/
int ss_get_list_of_measurements(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_list_of_measurements, ret);
}

/*Retrieves Reporting-Trigger avp value from group avp */
int ss_get_reporting_trigger(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_reporting_trigger, ret);
}

/*Retrieves Report-Interval avp value from group avp */
int ss_get_report_interval(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_report_interval, ret);
}

/*Retrieves Report-Amount avp value from group avp*/
int ss_get_report_amount(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_report_amount, ret);
}

/*Retrieves Event-Threshold-RSRP avp value from group avp*/
int ss_get_event_threshold_rsrp(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_event_threshold_rsrp, ret);
}

/*Retrieves Event-Threshold-RSRQ avp value from group avp*/
int ss_get_event_threshold_rsrq(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_event_threshold_rsrq, ret);
}

/*Retrieves Logging-Interval avp value from group avp*/
int ss_get_logging_interval(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_logging_interval, ret);
}

/*Retrieves Logging-Duration avp value from group avp*/
int ss_get_logging_duration(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_logging_duration, ret);
}

/*Retrieves Measurement-Period-LTE avp value from group avp */
int ss_get_measurement_period_lte(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_measurement_period_lte, ret);
}

/*Retrieves Measurement-Period-UMTS avp value from group avp*/
int ss_get_measurement_period_umts(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_measurement_period_umts, ret);
}

/*Retrieves Collection-Period-RMM-LTE avp value from group avp*/
int ss_get_collection_period_rmm_lte(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_collection_period_rrm_lte, ret);
}

/*Retrieves Collection-Period-RRM-UMTS avp value from group avp */
int ss_get_collection_period_rmm_umts(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_collection_period_rrm_umts, ret);
}

/*Retrieves Positioning-Method avp value from group avp */
int ss_get_positioning_method(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_positioning_method, ret);
}

/*Retrieves Measurement-Quantity avp value from group avp*/
int ss_get_measurement_quantity(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_measurement_quantity, ret);
}

/*Retrieves Event-Threshold-Event-1F avp value from group avp*/
int ss_get_event_threshold_event_1f(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_event_threshold_event_1f, ret);
}

/*Retrieves Event-Threshold-Event-1I avp value from group avp*/
int ss_get_event_threshold_event_1i(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_event_threshold_event_1i, ret);
}	

/*Retrieves multiple MDT-Allowed-PLMN-Id AVPs' values from group avp*/
int ss_get_mdt_allowed_plmn_id(struct avp *gavp, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_gavp_array(gavp, ss_mdt_allowed_plmn_id, array_ret, array_size);		
}

/*Retrieves Complete-Data-List-Included-Indicator avp value from group avp*/
int ss_get_complete_data_list_included_indicator(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_complete_data_list_included_indicator, ret);
}

/*Retrieves PDP-Type avp value from group avp*/
int ss_get_pdp_type(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_pdp_type, ret);
}

/*Retrieves PDP-Address avp value from group avp*/
int ss_get_pdp_address(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_pdp_address, ret);
}

/*Retrieves QoS-Subscribed avp value from group avp */
int ss_get_qos_subscribed(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_qos_subscribed, ret);
}

/*Retrieves Ext-PDP-Type avp value from group avp*/
int ss_get_ext_pdp_type(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_ext_pdp_type, ret);
}

/*Retrieves Ext-PDP-Address avp value from group avp*/
int ss_get_ext_pdp_address(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_ext_pdp_address, ret);
}

/*Retrieves CSG-Id avp value from group avp */
int ss_get_csg_id(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_csg_id, ret);
}

/*Retrieves Expiration-Date avp value from group avp*/
int ss_get_expiration_date(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_expiration_date, ret);
}

/*Retrieves ProSe-Permission avp value from group avp*/
int ss_get_prose_permission(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_prose_permission, ret);
}

/*Retrieves multiple Reset-ID AVPs' values from group avp*/
int ss_get_reset_id(struct msg *msg, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_array(msg, ss_reset_id, array_ret, array_size);		
}

/*Retrieves Number-Of-Requested-Vectors avp value from group avp*/
int ss_get_number_of_requested_vectors(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_number_of_requested_vectors, ret);
}

/*Retrieves Immediate-Response-Preferred avp value from group avp*/
int ss_get_immediate_response_preferred(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_immediate_response_preferred, ret);
}

/*Retrieves Re-synchronization-Info avp value from group avp*/
int ss_get_re_synchronization_info(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_re_synchronization_info, ret);
}

/*Retrieves Item-Number avp value from group avp*/
int ss_get_item_number(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_item_number, ret);
}

/*Retrieves RAND avp value from group avp*/
int ss_get_rand(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_rand, ret);
}

/*Retrieves XRES avp value from group avp*/
int ss_get_xres(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_xres, ret);
}

/*Retrieves AUTN avp value from group avp*/
int ss_get_autn(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_autn, ret);
}

/*Retrieves KASME avp value from group avp*/
int ss_get_kasme(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_kasme, ret);
}

/*Retrieves Confidentiality-Key avp value from group avp*/
int ss_get_confidentiality_key(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_confidentiality_key, ret);
}

/*Retrieves Integrity-Key avp value from group avp*/
int ss_get_integrity_key(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_integrity_key, ret);
}

/*Retrieves Kc avp value from group avp*/
int ss_get_kc(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_kc, ret);
}

/*Retrieves SRES avp value from group avp*/
int ss_get_sres(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_sres, ret);
}

/*Retrieves Cancellation-Type avp value from message*/
int ss_get_cancellation_type(struct msg *msg, int32_t *ret){	

	return get_int_value(msg, ss_cancellation_type, ret);
}

/*Retrieves CLR-Flags avp value from message*/
int ss_get_clr_flags(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_clr_flags, ret);
}

/*Retrieves IDR- Flags avp value from message*/
int ss_get_idr_flags(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_idr_flags, ret);
}

/*Retrieves IMS-Voice-Over-PS-Sessions-Supported avp value from message*/
int ss_get_ims_voice_over_ps_sessions_supported(struct msg *msg, int32_t *ret){	

	return get_int_value(msg, ss_ims_voice_over_ps_sessions_supported, ret);
}

/*Retrieves Last-UE-Activity-Time avp value from message*/
int ss_get_last_ue_activity_time(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_last_ue_activity_time, ret);
}

/*Retrieves IDA- Flags avp value from message*/
int ss_get_ida_flags(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_ida_flags, ret);
}

/*Retrieves User-State avp value from group avp*/
int ss_get_user_state(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_user_state, ret);
}

/*Retrieves Geographical-Information avp value from group avp*/
int ss_get_geographical_information(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_geographical_information, ret);
}

/*Retrieves Geodetic-Information avp value from group avp*/
int ss_get_geodetic_information(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_geodetic_information, ret);
}

/*Retrieves Current-Location-Retrieved avp value from group avp*/
int ss_get_current_location_retrieved(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_current_location_retrieved, ret);
}

/*Retrieves Age-Of-Location-Information avp value from group avp*/
int ss_get_age_of_location_information(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_age_of_location_information, ret);
}

/*Retrieves CSG-Access-Mode avp value from group avp*/
int ss_get_csg_access_mode(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_csg_access_mode, ret);
}

/*Retrieves CSG-Membership-Indication avp value from group avp*/
int ss_get_csg_membership_indication(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_csg_membership_indication, ret);
}

/*Retrieves Time-Zone avp value from group avp*/
int ss_get_time_zone(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_time_zone, ret);
}

/*Retrieves Daylight-Saving-Time avp value from group avp*/
int ss_get_daylight_saving_time(struct avp *gavp, int32_t *ret){	
	return get_int_value_gavp(gavp, ss_daylight_saving_time, ret);
}

/*Retrieves DSR-Flags avp value from message*/
int ss_get_dsr_flags(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_dsr_flags, ret);
}

/*Retrieves Context-Identifier avp value from message*/
int ss_get_context_identifier(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_context_identifier, ret);
}

/*Retrieves multiple Context-Identifier AVPs' values from message*/
int ss_get_context_identifier_array(struct msg *msg, uint32_t **array_ret, size_t *array_size){	
	
	return get_uint_array(msg, ss_context_identifier, array_ret, array_size);		
}
/*Retrieves Trace-Reference avp value from from message*/
int ss_get_trace_reference(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_trace_reference, ret);
}

/*Retrieves multiple TS-Code AVPs value from message*/
int ss_get_ts_code(struct msg *msg, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_array(msg, ss_ts_code, array_ret, array_size);		
}

/*Retrieves multiple SS-Code AVPs value from message*/
int ss_get_ss_code(struct msg *msg, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_array(msg, ss_ss_code, array_ret, array_size);		
}

/*Retrieves DSA-Flags avp value from message*/
int ss_get_dsa_flags(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_dsa_flags, ret);
}

/*Retrieves PUR-Flags avp value from message*/
int ss_get_pur_flags(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_pur_flags, ret);
}

/*Retrieves PUA-Flags avp value from message*/
int ss_get_pua_flags(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_pua_flags, ret);
}

/*Retrieves multiple User-Id AVPs value from message*/
int ss_get_user_id(struct msg *msg, unsigned char ***array_ret, size_t *array_size){	
	
	return get_str_array(msg, ss_user_id, array_ret, array_size);		
}

/*Retrieves Visited-Network-Identifier avp value from message*/
int ss_get_visited_network_identifier(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_visited_network_identifier, ret);
}

/*Retrieves Service-Selection avp value from message*/
int ss_get_service_selection(struct msg *msg, unsigned char **ret){	

	return get_str_value(msg, ss_service_selection, ret);
}

/*Retrieves Alert-Reason avp value from message */
int ss_get_alert_reason(struct msg *msg, int32_t *ret){	

	return get_int_value(msg, ss_alert_reason, ret);
}

/*Retrieves NOR-Flags avp value from message*/
int ss_get_nor_flags(struct msg *msg, uint32_t *ret){	

	return get_uint_value(msg, ss_nor_flags, ret);
}

/*Retrieves Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions avp value from message*/
int ss_get_homogeneous_support_ims_vop_sessions(struct msg *msg, int32_t *ret){	

	return get_int_value(msg, ss_homogeneous_support_of_ims_voice_over_ps_sessions, ret);
}

/*Retrieves Feature-List-ID avp value from group avp*/
int ss_get_feature_list_id(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_feature_list_id, ret);
}

/*Retrieves Feature-List avp value from group avp*/
int ss_get_feature_list(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_feature_list, ret);
}
