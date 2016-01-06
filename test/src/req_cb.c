
#include <my_sys.h>
#include <mysql.h>

#include "ssix_interface.h"
#include "test.h"

#define CHECK_ULR_SKIP_SUBSC_DATA(x) 	 ((1U<<2) & x) 
#define CHECK_ULR_GPRS_DATA_IND(x) 		 ((1U<<3) & x) 
#define CHECK_SUPPORT_ODB_HPLMN_APN(x)   ((1U<<1) & x)
#define SET_ULA_MME_REG_SMS(x)			  x |= (1U<<1)
#define SET_ULA_SEPARATION_INDICATIN(x)   x |= 1U

/*
#define MYSQL_SERVER "localhost"
#define MYSQL_PASSWORD "1234"
#define MYSQL_USER "root"
#define MYSQL_DB "ss_hss"
*/
#define MYSQL_CONF_FILE_NAME "mysql.conf"

#define SET_ORIGIN_AND_EXPER_RESULT(result, msg)																	\
{																													\
	/* Add the Origin-Host and Origin-Realm AVP in the answer*/														\
	CHECK_FCT( fd_msg_add_origin ( *msg, 0 ) );																		\
	/*Set experimental result*/																						\
	SS_CHECK( ss_create_experimental_result(&tmp_gavp), "Experimental-Result AVP created.\n", "Failed to create Experimental-Result AVP.\n");																						\
	/*Vendor-id*/																									\
	SS_CHECK( ss_set_vendor_id(&tmp_gavp,(unsigned32)VENDOR_ID_3GPP), "vendor id set.\n", "Failed to set vendor id.\n");	   																										\
	/*experimental result code*/																					\
  	SS_CHECK(ss_set_experimental_result_code(&tmp_gavp, (unsigned32)result), "experimental result code set.\n", "Failed to set experimental result code.\n");																		\
	SS_CHECK( ss_add_avp( (msg_or_avp **) msg, tmp_gavp ), "experimental result added.\n", "Failed to add experimental result.\n");																							\
}

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

	if((!filename))
		return 1;

	if((!server) && (!db_name) && (!user_name) && (!password))
		return 1;

	/*read confile*/
	if((buff = test_parse_conf(filename)) == NULL)
		return 1;

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
static void connect_db(MYSQL **conn){

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
static int get_qry_res(MYSQL *conn, char * statement, MYSQL_RES **res){

	if((!conn) || (!statement) || (!res))
		return 1;

	if (mysql_query(conn, statement)) 
		fprintf(stderr, "%s\n", mysql_error(conn));      				
			
	if((*res = mysql_store_result(conn)) != NULL)
		return 0;
	else
		fprintf(stderr, "Error %s\n", mysql_error(conn));

	return 1;
}

/* Set AMBR AVP*/
static void set_ambr(struct avp **gavp, char * ul, char * dl){
	
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
		SS_SET_U32( ss_set_max_requested_bw_ul( &tmp_gavp, tmp_u), tmp_u, ul, "Max-Requested-Bandwidth-UL set.\n", "Failed to set Max-Requested-Bandwidth-UL.\n");
		
	/* Set Max-Requested-Bandwidth-DL*/	
	if(dl)
		SS_SET_U32( ss_set_max_requested_bw_dl( &tmp_gavp, tmp_u), tmp_u, dl, "Max-Requested-Bandwidth-DL set.\n", "Failed to set Max-Requested-Bandwidth-DL.\n");

	/*Add AMBR group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (msg_or_avp **) gavp, tmp_gavp), "AMBR AVP set.\n", "Failed to add AMBR.\n");
}

/* Set WLAN-offloadability*/
static void set_wlan_offload(struct avp **gavp, char * eutran, char * utran){
							
	struct avp * tmp_gavp;
	unsigned32 tmp_u;

	if(!gavp)
		return;
	if((!eutran) && (!utran))
		return;		
	
	/*Create WLAN-offloadability AVP*/
	SS_CHECK( ss_create_wlan_offloadability( &tmp_gavp), "WLAN-offloadability AVP created.\n", "Failed to create WLAN-offloadability.\n");

	/* Set WLAN-offloadability-EUTRAN */
	if(eutran)
		SS_SET_U32( ss_set_wlan_offloadability_eutran( &tmp_gavp, tmp_u), tmp_u, eutran, "WLAN-offloadability-EUTRAN set.\n", "Failed to set WLAN-offloadability-EUTRAN.\n");	
	
	/* Set WLAN-offloadability-UTRAN */	
	if(utran)
		SS_SET_U32( ss_set_wlan_offloadability_utran( &tmp_gavp, tmp_u), tmp_u, utran, "WLAN-offloadability-UTRAN set.\n", "Failed to set WLAN-offloadability-UTRAN.\n");		
		
	/*Add WLAN-offloadability group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (msg_or_avp **) gavp, tmp_gavp), "WLAN-offloadability AVP added.\n", "Failed to add WLAN-offloadability.\n");
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
	SS_CHECK( ss_add_avp( (msg_or_avp **)&gavp, tmp_gavp), "Allocation-Retention-Priority AVP added.\n", "Failed to add Allocation-Retention-Priority.\n");
}

/*** Set eps_qos_prof: EPS-Subscribed-QoS-Profile **************************/
static void eps_subsc_qos_prof(struct avp **gavp, char * qos, char * level, char * capab, char * vulner){

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
	SS_CHECK( ss_add_avp( (msg_or_avp **)&gavp, tmp_gavp), "EPS-Subscribed-QoS-Profile set.\n", "Failed to add EPS-Subscribed-QoS-Profile.\n");	
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
	connect_db(&conn);

	/*Prepare mysql statement to get area scope data*/	
	sprintf(buf,"select * from areaScope where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(get_qry_res(conn, buf, &res), "area scope data retrieved from db.\n", "Failed to store area scope data from database.\n");	

	/*Create Area-Scope AVP*/
	if(mysql_num_rows(res) != 0)
		SS_CHECK( ss_create_area_scope( &tmp_gavp), "Area-Scope AVP created.\n", "Failed to create Area-Scope.\n");

	/*Fetch row from mysql result for Area-Scope data */			
	while((row = mysql_fetch_row(res)) != NULL){
	
		/* Set Cell-Global-Identity*/
		if(row[1])
			SS_CHECK( ss_set_cell_global_identity(&tmp_gavp, (octetstring *)row[1]), "Cell-Global-Identity set.\n", "Failed to set Cell-Global-Identity.\n");

		/* Set E-UTRAN-Cell-Global-Identity*/
		if(row[2])
			SS_CHECK( ss_set_e_utran_cell_global_identity(&tmp_gavp, (octetstring *)row[2]), "E-UTRAN-Cell-Global-Identity set.\n", "Failed to set E-UTRAN-Cell-Global-Identity.\n");

		/* Set Routing-Area-Identity*/
		if(row[3])
			SS_CHECK( ss_set_routing_area_identity(&tmp_gavp, (octetstring *)row[3]), "Routing-Area-Identity set.\n", "Failed to set Routing-Area-Identity.\n");

		/* Set Location-Area-Identity*/
		if(row[4])
			SS_CHECK( ss_set_location_area_identity(&tmp_gavp, (octetstring *)row[4]), "Location-Area-Identity set.\n", "Failed to set Location-Area-Identity.\n");

		/* Set Tracking-Area-Identity*/
		if(row[5])
			SS_CHECK( ss_set_tracking_area_identity(&tmp_gavp, (octetstring *)row[5]), "Tracking-Area-Identity set.\n", "Failed to set Tracking-Area-Identity.\n");	
	}
		
	/*Add Area-Scope group AVP into the group AVP provided in parameter 'gavp'*/
	if(tmp_gavp)
		SS_CHECK( ss_add_avp( (msg_or_avp **) gavp, tmp_gavp), "Area-Scope AVP added.\n", "Failed to add Area-Scope group AVP.\n");

	mysql_free_result(res);
	mysql_close(conn);
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

	if((!gavp) || (!imsi))
		return;
	
	/*connect to database*/
	connect_db(&conn);

	/*Prepare mysql statement to get trace data*/	
	sprintf(buf,"select * from traceData where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(get_qry_res(conn, buf, &res), "Trace data retrieved from db.\n", "Failed to retrieve trace data from database.\n");
	
	/*if database query return empty set*/
	if((row = mysql_fetch_row(res)) == NULL)
		return;
		
	/*Create Trace-Data group AVP*/	
	SS_CHECK( ss_create_trace_data( &tmp_gavp), "Trace-Data AVP created.\n", "Failed to create Trace-Data group AVP.\n");
		
	/* Set Trace-Reference*/
	if(row[1])
		SS_CHECK( ss_set_trace_reference_gavp( &tmp_gavp, (octetstring *)row[1]), "Trace-Reference set.\n", "Failed to set Trace-Reference.\n");
	
	/* Set Trace-Depth*/
	if(row[2])
		SS_SET_I32( ss_set_trace_depth( &tmp_gavp, tmp_u), tmp_u, row[2], "Trace-Depth set.\n", "Failed to set Trace-Depth.\n");
	
	/* Set Trace-NE-Type-List*/
	if(row[3])
		SS_CHECK( ss_set_trace_ne_type_list( &tmp_gavp, (octetstring *)row[3]), "Trace-NE-Type-List set.\n", "Failed to set Trace-NE-Type-List.\n");
		
	/* Set Trace-Interface-List*/
	if(row[4])
		SS_CHECK( ss_set_trace_interface_list( &tmp_gavp, (octetstring *)row[4]), "Trace-Interface-List set.\n", "Failed to set Trace-Interface-List.\n");
	
	/* Set Trace-Event-List*/
	if(row[5])
		SS_CHECK( ss_set_trace_event_list( &tmp_gavp, (octetstring *)row[5]), "Trace-Event-List set.\n", "Failed to set Trace-Event-List.\n");
	
	/* Set OMC-Id*/
	if(row[6])
		SS_CHECK( ss_set_omc_id( &tmp_gavp, (octetstring *)row[6]), "OMC-Id set.\n", "Failed to set OMC-Id.\n");
		
	/* Set Trace-Collection-Entity*/
	if(row[7])
		SS_CHECK( ss_set_trace_collection_entity( &tmp_gavp, (address *)row[7]), "Trace-Collection-Entity set.\n", "Failed to set Trace-Collection-Entity.\n");
	
	/*** Set MDT-Configuration group AVP  ***/
	SS_CHECK( ss_create_mdt_configuration( &tmp_gavp2), "MDT-Configuration set.\n", "Failed to create MDT-Configuration.\n");	

	/** Set Job-Type **/
	if(row[8])
		SS_SET_I32( ss_set_job_type(&tmp_gavp2, tmp_i), tmp_i, row[8], "Job-Type set.\n", "Failed to set Job-Type.\n");	

	/* Set Area-Scope group AVP*/
	set_area_scope( &tmp_gavp2, imsi);	
		
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
		SS_CHECK( ss_set_positioning_method( &tmp_gavp2, (octetstring *)row[21]), "Positioning-Method set.\n", "Failed to set Positioning-Method.\n");

	/* Set Measurement-Quantity*/		
	if(row[22])
		SS_CHECK( ss_set_measurement_quantity( &tmp_gavp2, (octetstring *)row[22]), "Measurement-Quantity set.\n", "Failed to set Measurement-Quantity.\n");

	/* Set Event-Threshold-Event-1F*/		
	if(row[23])
		SS_SET_I32( ss_set_event_threshold_event_1f( &tmp_gavp2, tmp_i), tmp_i, row[23], "Event-Threshold-Event-1F set.\n", "Failed to set Event-Threshold-Event-1F.\n");

	/* Set Event-Threshold-Event-1I*/		
	if(row[24])
		SS_SET_I32( ss_set_event_threshold_event_1i( &tmp_gavp2, tmp_i), tmp_i, row[24], "Event-Threshold-Event-1I set.\n", "Failed to set Event-Threshold-Event-1I.\n");

	/* Set MDT-Allowed-PLMN-Id (only 3 AVPs set for testing)*/
	if(row[25])
		SS_CHECK( ss_set_mdt_allowed_plmn_id(&tmp_gavp2, (octetstring *)row[25]), "MDT-Allowed-PLMN-Id set.\n", "Failed to set MDT-Allowed-PLMN-Id.\n");
	if(row[26])
		SS_CHECK( ss_set_mdt_allowed_plmn_id(&tmp_gavp2, (octetstring *)row[26]), "MDT-Allowed-PLMN-Id 2 set.\n", "Failed to set MDT-Allowed-PLMN-Id 2.\n");
	if(row[27])
		SS_CHECK( ss_set_mdt_allowed_plmn_id(&tmp_gavp2, (octetstring *)row[27]), "MDT-Allowed-PLMN-Id 3 set.\n", "Failed to set MDT-Allowed-PLMN-Id.\n");	
	
	mysql_free_result(res);

	/*Add MDT-Configuration into Trace-Data*/
	SS_CHECK( ss_add_avp( (msg_or_avp **) &tmp_gavp, tmp_gavp2), "MDT-Configuration AVP added", "Failed to add MDT-Configuration.\n");
	
	/*Add Trace-Data group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (msg_or_avp **) gavp, tmp_gavp), "Trace-Data AVP added.\n", "Failed to add Trace-Data.\n");

}

/* Set GPRS-Subscription-Data*/
static void set_gprs_subsc_data(struct avp **gavp, char * imsi){

	struct avp * tmp_gavp;	
	struct avp * tmp_gavp2;	
	unsigned32 tmp_u;
	integer32 tmp_i;
	enum complete_data_list_included_indicator cmp_ind = All_PDP_CONTEXTS_INCLUDED;
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi))
		return;
	
	/*Create GPRS-Subscription-Data group AVP*/
	SS_CHECK( ss_create_gprs_subscription_data( &tmp_gavp), "GPRS-Subscription-Data AVP created.\n", "Failed to create GPRS-Subscription-Data.\n");

	/*Set Complete-Data-List-Included-Indicator*/
	SS_CHECK( ss_set_complete_data_list_included_indicator(&tmp_gavp, (int)cmp_ind), "Complete-Data-List-Included-Indicator set.\n", "Failed to set Complete-Data-List-Included-Indicator.\n");		
	
	/** Set PDP-Context	group AVP **/

	/*connect to database*/
	connect_db(&conn);

	/*Prepare mysql statement to get pdp context data*/	
	sprintf(buf,"select * from pdpContext where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(get_qry_res(conn, buf, &res), "pdp context data retrieved from db.\n", "Failed to retrieve pdp context data from database.\n");

	/*Check if the result is empty*/
	if(mysql_num_rows(res) == 0)
		return;	

	while((row = mysql_fetch_row(res)) != NULL){	
		
		/*Create PDP-Context AVP*/
		SS_CHECK( ss_create_pdp_context(&tmp_gavp2), "PDP-Context AVP created.\n", "Failed to create PDP-Context.\n");
	
		/* Set Context-Identifier */
		if(row[1])
			SS_SET_U32( ss_set_context_identifier_gavp( &tmp_gavp2, tmp_u), tmp_u, row[1], "context identifier set.\n", "Failed to set Context-Identifier.\n");

		/* Set PDP-Type */
		if(row[2])
			SS_CHECK( ss_set_pdp_type(&tmp_gavp2,(octetstring *)row[2]), "pdp type set.\n", "Failed to set PDP-Type.\n");

		/* Set PDP-Address */
		if(row[3])
			SS_CHECK( ss_set_pdp_address(&tmp_gavp2,(address *)row[3]), "pdp address set.\n", "Failed to set PDP-Address.\n");	
	
		/* Set QoS-Subscribed */
		if(row[4])
			SS_CHECK( ss_set_qos_subscribed(&tmp_gavp2,(octetstring *)row[4]), "qos subscribed set.\n", "Failed to set QoS-Subscribed.\n");

		/* Set VPLMN-Dynamic-Address-Allowed */
		if(row[5])
			SS_SET_I32( ss_set_vplmn_dynamic_address_allowed(&tmp_gavp2, tmp_i), tmp_i, row[5], "vplmn dynamic address allowed set.\n", "Failed to set VPLMN-Dynamic-Address-Allowed.\n");						

		/* Set Service-Selection*/
		if(row[6])
			SS_CHECK( ss_set_service_selection_gavp(&tmp_gavp2, (utf8string *)row[6]), " service selection set.\n", "Failed to set Service-Selection.\n");

		/* Set 3GPP-Charging-Characteristics */
		if(row[7])
			SS_CHECK( ss_set_3gpp_charging_characteristics(&tmp_gavp2, (utf8string *)row[7]), "3pp charging characteristics  set.\n", "Failed to set 3GPP-Charging-Characteristics.\n");					

		/* Set Ext-PDP-Type */
		if(row[8])
			SS_CHECK( ss_set_ext_pdp_type(&tmp_gavp2,(octetstring *)row[8]), "ext pdp type set.\n", "Failed to set Ext-PDP-Type.\n");		

		/* Set Ext-PDP-Address */
		if(row[9])
			SS_CHECK( ss_set_ext_pdp_address(&tmp_gavp2,(address *)row[9]), "ext pdp address set.\n", "Failed to set Ext-PDP-Address.\n");		

		/*** Set AMBR ***/
		set_ambr( &tmp_gavp2, row[10], row[11]);
	
		/* Set APN-OI-Replacement*/
		if(row[12])
			SS_CHECK( ss_set_apn_oi_replacement(&tmp_gavp2, (utf8string *)row[12]), "apn oi replacement set.\n", "Failed to set APN-OI-Replacement.\n");

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
		SS_CHECK( ss_add_avp( (msg_or_avp **) &tmp_gavp, tmp_gavp2), "PDP-Context added.\n", "Failed to add PDP-Context.\n");		
	} 

	mysql_free_result(res);	
	mysql_close(conn);

	/*Add GPRS-Subscription-Data group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (msg_or_avp **) gavp, tmp_gavp), "GPRS-Subscription-Data added.\n", "Failed to add GPRS-Subscription-Data.\n");			
}

/* Set CSG-Subscription-Data */
static void set_csg_subscription_data(struct avp **gavp, char * imsi, octetstring * vis_plmn_id){

	struct avp * tmp_gavp;
	unsigned32 tmp_u;
	char buf[110] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;
	
	if((!gavp) || (!imsi) || (!vis_plmn_id))
		return;

	/*connect to database*/
	connect_db(&conn);

	/*Prepare mysql statement to get csg data*/	
	sprintf(buf,"select * from csgData where imsi='%.15s' and visitPlmnId='%s'", imsi, vis_plmn_id);

	/*Query databse*/
	SS_CHECK(get_qry_res(conn, buf, &res), "csg data retrieved from db.\n", "Failed to retrieve csg data from database.\n");

	/*Check if the result is empty*/
	if((row = mysql_fetch_row(res)) == NULL)
		return;	
	
	/*Create CSG-Subscription-Data*/
	SS_CHECK( ss_create_csg_subscription_data( &tmp_gavp), "CSG-Subscription-Data AVP created.\n", "Failed to set CSG-Subscription-Data.\n");

	/* Set CSG-Id*/
	if(row[1])
		SS_SET_U32( ss_set_csg_id(&tmp_gavp, tmp_u), tmp_u, row[1], "CSG-Id set.\n", "Failed to set CSG-Id.\n");
	
	/* Set Expiration-Date*/
	if(row[2])
		SS_CHECK( ss_set_expiration_date( &tmp_gavp, (ss_time *)row[2]), "Expiration-Date set.\n", "Failed to set Expiration-Date.\n");
	
	/* Set Service-Selection (only 3 AVPs for testing)*/
	if(row[3])
		SS_CHECK( ss_set_service_selection_gavp( &tmp_gavp, (utf8string *)row[3]), "Service-Selection set.\n", "Failed to set Service-Selection.\n");
	if(row[4])
		SS_CHECK( ss_set_service_selection_gavp( &tmp_gavp, (utf8string *)row[4]), "Service-Selection 2 set.\n", "Failed to set Service-Selection 2.\n");
	if(row[5])
		SS_CHECK( ss_set_service_selection_gavp( &tmp_gavp, (utf8string *)row[5]), "Service-Selection 3 set.\n", "Failed to set Service-Selection 3.\n");	
		
	/* Set Visited-PLMN-Id*/
	if(row[6])
		SS_CHECK( ss_set_visited_plmn_id_gavp( &tmp_gavp, (octetstring *)row[6]), "Visited-PLMN-Id set.\n", "Failed to set Visited-PLMN-Id.\n");	

	mysql_free_result(res);
	mysql_close(conn);

	/*Add CSG-Subscription-Data group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (msg_or_avp **) gavp, tmp_gavp), "CSG-Subscription-Data added.\n", "Failed to add CSG-Subscription-Data.\n") ;	
}

/************ Set APN-Configuration-Profile ***************************************/
static void set_apn_conf_prof(struct avp **gavp, char * imsi, char * context_id){

	struct avp * tmp_gavp;	
	struct avp * tmp_gavp2;	
	unsigned32 tmp_u;
	integer32 tmp_i;
	enum all_apn_configuration_included_indicator apn_ind = All_APN_CONFIGURATIONS_INCLUDED;
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi) || (!context_id))
		return;
	
	/*Create APN-Configuration-Profile group AVP*/
	SS_CHECK( ss_create_apn_configuration_profile( &tmp_gavp), "APN-Configuration-Profile AVP created.\n", "Failed to create APN-Configuration-Profile.\n");

	/*Set Context-Identifier*/
	SS_SET_U32( ss_set_context_identifier_gavp(&tmp_gavp, tmp_u), tmp_u, context_id, "Context-Identifier set.\n", "Failed to set Context-Identifier.\n");
	
	/*Set All-APN-Configurations-Included-Indicator */
	SS_CHECK( ss_set_all_apn_configuration_included_indicator(&tmp_gavp, (int)apn_ind), "All-APN-Configurations-Included-Indicator set.\n", "Failed to set All-APN-Configurations-Included-Indicator.\n");

	/******Set APN-Configuration****************************************************/
	/*connect to database*/
	connect_db(&conn);

	/*Prepare mysql statement to get apn configuration data*/	
	sprintf(buf,"select * from apnConf where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(get_qry_res(conn, buf, &res), "APN config data retrieved from db.\n", "Failed to apn config data from database.\n");

	/*Check if the result is empty*/
	if(mysql_num_rows(res) == 0)
		return;								
				
	while((row = mysql_fetch_row(res)) != NULL){
		
		/*Create APN-Configuration group AVP*/
		SS_CHECK( ss_create_apn_configuration(&tmp_gavp2), "APN-Configuration AVP created.\n", "Failed to create APN-Configuration.\n");	

		/*Set Context-Identifier*/
		if(row[1])
			SS_SET_U32( ss_set_context_identifier_gavp(&tmp_gavp2, tmp_u), tmp_u, row[1], "Context-Identifier set.\n", "Failed to set Context-Identifier.\n");
	
		/* Set Served-Party-IP-Address (IPV4 and IPV6)*/	
		if(row[2])
			SS_CHECK( ss_set_served_party_ip_address(&tmp_gavp2, (address *)row[2]), "Served-Party-IP-Address set.\n", "Failed to set Served-Party-IP-Address.\n");
		if(row[3])
			SS_CHECK( ss_set_served_party_ip_address(&tmp_gavp2, (address *)row[3]), "Served-Party-IP-Address.\n", "Failed to set Served-Party-IP-Address.\n");					

		/*Set PDN-Type*/
		if(row[4])
			SS_SET_I32( ss_set_pdn_type(&tmp_gavp2, tmp_u), tmp_u, row[4], "PDN-Type set.\n", "Failed to set PDN-Type.\n");

		/* Set Service-Selection*/
		if(row[5])
			SS_CHECK( ss_set_service_selection_gavp(&tmp_gavp2, (utf8string *)row[5]), "Service-Selection set.\n", "Failed to set Service-Selection.\n");
	
		/*** Set eps_qos_prof: EPS-Subscribed-QoS-Profile **************************/
		eps_subsc_qos_prof(&tmp_gavp2, row[6], row[7], row[8], row[9]);							
							
		/* Set VPLMN-Dynamic-Address-Allowed*/
		if(row[10])
			SS_SET_I32( ss_set_vplmn_dynamic_address_allowed(&tmp_gavp2, tmp_i), tmp_i, row[10], "VPLMN-Dynamic-Address-Allowed set.\n", "Failed to set VPLMN-Dynamic-Address-Allowed.\n");

		/*** Set MIP6-Agent-Info AVP ******************************************/
		test_set_mip6( &tmp_gavp2, (address *) row[11], (address *) row[12], (diameterid *) row[13], (diameterid *) row[14]);
							
		/* Set Visited-Network-Identifier *********************/
		if(row[15])
			SS_CHECK( ss_set_visited_network_identifier_gavp( &tmp_gavp2, (octetstring *)row[15]), "Visited-Network-Identifier set.\n", "Failed to set Visited-Network-Identifier.\n");

		/* Set PDN-GW-Allocation-Type */
		if(row[16])
			SS_SET_I32( ss_set_pdn_gw_allocation_type( &tmp_gavp2, tmp_i), tmp_i, row[16], "PDN-GW-Allocation-Type set.\n", "Failed to set PDN-GW-Allocation-Type.\n");
									
		/* Set 3GPP-Charging-Characteristics*/
		if(row[17])
			SS_CHECK( ss_set_3gpp_charging_characteristics( &tmp_gavp2, (utf8string *)row[17]), "3GPP-Charging-Characteristics set.\n", "Failed to set 3GPP-Charging-Characteristics.\n");
	
		/* Set AMBR*/
		set_ambr( &tmp_gavp2, row[18], row[19]);

		/* Set APN-OI-Replacement*********/
		if(row[20])
			SS_CHECK( ss_set_apn_oi_replacement(&tmp_gavp2, (utf8string *)row[20]), "APN-OI-Replacement set.\n", "Failed to set APN-OI-Replacement.\n");

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
		SS_CHECK( ss_add_avp( (msg_or_avp **) &tmp_gavp, tmp_gavp2), "APN-Configuration added.\n", "Failed to add APN-Configuration.\n");			
	}
	
	mysql_free_result(res);
	mysql_close(conn);

	/*Add APN-Configuration-Profile group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (msg_or_avp **) &gavp, tmp_gavp), "APN-Configuration-Profile added.\n", "Failed to add APN-Configuration-Profile.\n");		
}

/* Set ProSe-Subscription-Data*/
static void set_prose_subsc(struct avp **gavp, char * prose_perm){
	
	struct avp * tmp_gavp;
	unsigned32 tmp_u;

	if((!gavp) || (!prose_perm))
		return;
	
	/*Create ProSe-Subscription-Data group AVP*/
	SS_CHECK( ss_create_prose_subscription_data( &tmp_gavp), "ProSe-Subscription-Data set.\n", "Failed to create ProSe-Subscription-Data.\n");

	/*Set ProSe-Permission*/	
	SS_SET_U32( ss_set_prose_permission( &tmp_gavp, tmp_u), tmp_u, prose_perm, "ProSe-Permission set.\n", "Failed to set ProSe-Permission.\n");	

	/*Add ProSe-Subscription-Data group AVP into the group AVP provided in parameter 'gavp'*/
	SS_CHECK( ss_add_avp( (msg_or_avp **) &gavp, tmp_gavp), "ProSe-Subscription-Data added.\n", "Failed to add ProSe-Subscription-Data.\n");
}

/*************** Set Call-Barring-Info ******************************************/
static void set_call_barring_info(struct avp **gavp, char * imsi){

	struct avp * tmp_gavp = NULL;	
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi))
		return;
	
	/*connect to database*/
	connect_db(&conn);

	/*Prepare mysql statement to get call barring info data*/	
	sprintf(buf,"select * from callBaringInfo where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(get_qry_res(conn, buf, &res), "Call barring info retrieved from db.\n", "Failed to retrieve callbarring info data from database.\n");

	while((row = mysql_fetch_row(res)) != NULL){

		/*Create Call-Barring-Info group AVP*/
		SS_CHECK( ss_create_call_barring_info( &tmp_gavp), "Call-Barring-Info AVP created.\n", "Failed to create Call-Barring-Info.\n");	
						
		/*Set SS-Code*/	
		if(row[1])
			SS_CHECK( ss_set_ss_code_gavp( &tmp_gavp, (octetstring *)row[1]), "SS-Code set.\n", "Failed to set SS-Code.\n");

		/*Set SS-Status*/	
		if(row[2])
			SS_CHECK( ss_set_ss_status( &tmp_gavp, (octetstring *)row[2]), "SS-Status set.\n", "Failed to set SS-Status.\n");

		/*Add Call-Barring-Info*/
		SS_CHECK( ss_add_avp( (msg_or_avp **) gavp, tmp_gavp), "Call-Barring-Info added.\n", "Failed to add Call-Barring-Info AVP.\n");		
	} 

	mysql_free_result(res);
	mysql_close(conn);
}

/* Create Teleservice-List*/
static void set_teleserv_list(struct avp **gavp, octetstring *ts_cd1, octetstring *ts_cd2, octetstring *ts_cd3){

	struct avp * tmp_gavp;

	if((!gavp))
		return;
	if((!ts_cd1) && (!ts_cd2) && (!ts_cd3))
		return;
	/*Create Teleservice-List group AVP*/
	SS_CHECK( ss_create_teleservice_list(&tmp_gavp), "Teleservice-List AVP created.\n", "Failed to create Teleservice-List.\n");

	/*Set TS-Code AVP(3 AVPs for test)*/
	if(ts_cd1)
		SS_CHECK( ss_set_ts_code_gavp(&tmp_gavp, ts_cd1), "TS-Code 1 set.\n", "Failed to set TS-Code 1.\n");
	if(ts_cd2)
		SS_CHECK( ss_set_ts_code_gavp(&tmp_gavp, ts_cd2), "TS-Code 2 set.\n", "Failed to set TS-Code 2.\n");
	if(ts_cd3)
		SS_CHECK( ss_set_ts_code_gavp(&tmp_gavp, ts_cd3), "TS-Code 3 set.\n", "Failed to set TS-Code 3.\n");
	
	/*Add Teleservice-List group AVP*/
	SS_CHECK( ss_add_avp( (msg_or_avp **)gavp, tmp_gavp), "Teleservice-List added.\n", "Failed to add Teleservice-List.\n");
}

/*Set MO-LR group AVP*/
static void set_mo_lr(struct avp **gavp, octetstring * ss_cd, octetstring * ss_sts){

	struct avp * tmp_gavp;

	if((!gavp) || (!ss_cd) || (!ss_sts))
		return;

	/*Create MO-LR group AVP*/
	SS_CHECK( ss_create_mo_lr( &tmp_gavp), "MO-LR AVP created.\n", "Failed to create MO-LR AVP.\n");		
	
	/*Set SS-Code AVP*/
	SS_CHECK( ss_set_ss_code_gavp(&tmp_gavp, ss_cd), "SS-Code set.\n", "Failed to Set SS-Code.\n");
	
	/*Set SS-Status AVP*/
	SS_CHECK( ss_set_ss_status(&tmp_gavp, ss_sts), "SS-Status set.\n", "Failed to Set SS-Status.\n");

	/*Add MO-LR group AVP*/
	SS_CHECK( ss_add_avp( (msg_or_avp **)gavp, tmp_gavp), "MO-LR added.\n", "Failed to add MO-LR.\n");
}

/*Set LCS-Info*/
static void set_lcs_info(struct avp **gavp, char * imsi){

	struct avp * tmp_gavp;	
	char buf[60] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!gavp) || (!imsi))
		return;
	
	/*connect to database*/
	connect_db(&conn);

	/*Prepare mysql statement to get LCS info data*/	
	sprintf(buf,"select * from lcsInfo where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(get_qry_res(conn, buf, &res), "LCS info data retrieved from db.\n", "Failed to retrieve LCS info data from database.\n");     				
			
	if((row = mysql_fetch_row(res))!= NULL){
	
		/* Create LCS-Info group AVP*/
		SS_CHECK( ss_create_lcs_info( &tmp_gavp), "LCS-Info AVP created.\n", "Failed to create LCS-Info AVP.\n");
		
		/* Set GMLC-Number AVPs (only 3 AVPs for testing purpose)*/
		if(row[1])
			SS_CHECK( ss_set_gmlc_number(&tmp_gavp, (octetstring *)row[1]), "GMLC-Number 1 set.\n", "Failed to Set GMLC-Number 1.\n");
		if(row[2])
			SS_CHECK( ss_set_gmlc_number(&tmp_gavp, (octetstring *)row[2]), "GMLC-Number 2 set.\n", "Failed to Set GMLC-Number 2.\n");
		if(row[3])
			SS_CHECK( ss_set_gmlc_number(&tmp_gavp, (octetstring *)row[3]), "GMLC-Number 3 set.\n", "Failed to Set GMLC-Number 3.\n");

		/* Set MO-LR group AVP (only 3 AVPs for testing purpose)*/
		set_mo_lr(&tmp_gavp, (octetstring *) row[4], (octetstring *) row[5]);
		set_mo_lr(&tmp_gavp, (octetstring *) row[6], (octetstring *) row[7]);
		set_mo_lr(&tmp_gavp, (octetstring *) row[8], (octetstring *) row[9]);

		SS_CHECK( ss_add_avp( (msg_or_avp **)&gavp, tmp_gavp), "LCS-Info added.\n", "Failed to add LCS-Info.\n");
	}

	mysql_free_result(res);
	mysql_close(conn);
}


/* Create Subscription-Data AVP*/
static void set_subsc_data(struct msg ** msg, char * imsi, unsigned32 ulr_flg, struct msg * req){

	struct avp * tmp_gavp;
	struct avp * tmp_gavp2;
	unsigned32 tmp_u;
	integer32 tmp_i;	
	octetstring ** visited_plmn_id = NULL;
	char buf[70] = {0};

	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if((!msg) || (!imsi))
		return;
	
	/*connect to database*/
	connect_db(&conn);

	/*Prepare mysql statement to subscription data*/	
	sprintf(buf,"select * from subscriptionData where imsi='%.15s'",imsi);

	/*Query databse*/
	SS_CHECK(get_qry_res(conn, buf, &res), "Subscription data retrieved from db.\n", "Failed to retrieve subscription data from database.\n"); 
	
	if((row = mysql_fetch_row(res))!= NULL){

		/*Create Subscription-Data group AVP*/
		SS_CHECK( ss_create_subscription_data(&tmp_gavp), "Subscription-Data AVP created.\n", "Failed to create Subscription-Data AVP.\n");
						
		/* Set Subscriber-Status*/
		if(row[1])
			SS_SET_I32( ss_set_subscriber_status(&tmp_gavp, tmp_i), tmp_i, row[1], "Subscriber-Status AVP.\n", "Failed to set Subscriber-Status AVP.\n");
		
		/* Set MSISDN*/
		if(row[2])
			SS_CHECK( ss_set_msisdn(&tmp_gavp, (octetstring *)row[2]), "MSISDN set.\n", "Failed to set MSISDN AVP.\n");

		/* Set A-MSISDN*/
		if(row[3])
			SS_CHECK( ss_set_msisdn(&tmp_gavp, (octetstring *)row[3]), "A_MSISDN set.\n", "Failed to set A_MSISDN AVP.\n");

		/* Set STN-SR*/
		if(row[4])
			SS_CHECK( ss_set_stn_sr(&tmp_gavp, (octetstring *)row[4]), "STN-SR set.\n", "Failed to set STN-SR AVP.\n");

		/* Set ICS-Indicator*/
		if(row[5])
			SS_SET_I32( ss_set_ics_indicator(&tmp_gavp, tmp_i), tmp_i, row[5], "ICS-Indicator set.\n", "Failed to set ICS-Indicator AVP.\n");
	
		/* Set Network-Access-Mode*/
		if(row[6])
			SS_SET_I32( ss_set_network_access_mode(&tmp_gavp, tmp_i), tmp_i, row[6], "Network-Access-Mode set.\n", "Failed to set Network-Access-Mode AVP.\n");
	
		/* Set Operator-Determined-Barring*/
		if(row[7])
			SS_SET_U32( ss_set_operator_determined_barring(&tmp_gavp, tmp_u), tmp_u, row[7], "Operator-Determined-Barring set.\n", "Failed to set Operator-Determined-Barring AVP.\n");

		/* Set HPLMN-ODB*/
		if(row[8])
			SS_SET_U32( ss_set_hplmn_odb(&tmp_gavp, tmp_u), tmp_u, row[8], "Operator-Determined-Barring set.\n", "Failed to set Operator-Determined-Barring AVP.\n");
	
		/* Set Regional-Subscription-Zone-Code*/
		if(row[9])
			SS_CHECK( ss_set_regional_subscription_zone_code(&tmp_gavp, (octetstring *)row[9]), "Regional-Subscription-Zone-Code set.\n", "Failed to set Regional-Subscription-Zone-Code AVP.\n");
		if(row[10])
			SS_CHECK( ss_set_regional_subscription_zone_code(&tmp_gavp, (octetstring *)row[10]), "Regional-Subscription-Zone-Code 2 set.\n", "Failed to set Regional-Subscription-Zone-Code 2 AVP.\n");
		if(row[11])
			SS_CHECK( ss_set_regional_subscription_zone_code(&tmp_gavp, (octetstring *)row[11]), "Regional-Subscription-Zone-Code 3 set.\n", "Failed to set Regional-Subscription-Zone-Code 3 AVP.\n");						

		/* Set Access-Restriction-Data*/
		if(row[12])
			SS_SET_U32( ss_set_access_restriction_data(&tmp_gavp, tmp_u), tmp_u, row[12], "Restriction-Data set.\n", "Failed to set Access-Restriction-Data AVP.\n");
		
		/* Set APN-OI-Replacement */
		if(row[13])
			SS_CHECK( ss_set_apn_oi_replacement(&tmp_gavp, (utf8string *)row[13]), "APN-OI-Replacement set.\n", "Failed to set APN-OI-Replacement AVP.\n");
	
		/*Set LCS-Info*/
		set_lcs_info(&tmp_gavp, imsi);
					
		/* Create Teleservice-List*/
		set_teleserv_list( &tmp_gavp, (octetstring *) row[14], (octetstring *) row[15], (octetstring *) row[16]);

		/* Set Call-Barring-Info group AVP*/
		set_call_barring_info( &tmp_gavp, imsi);
				
		/* Set 3GPP-Charging-Characteristics */
		if(row[17])
			SS_CHECK( ss_set_3gpp_charging_characteristics( &tmp_gavp, (utf8string *)row[17]), "3GPP-Charging-Characteristics set.\n", "Failed to set 3GPP-Charging-Characteristics.\n");
	
		/* Create AMBR	group AVP*/
		set_ambr( &tmp_gavp, row[18], row[19]);					
			
		/*Set APN-Configuration-Profile group AVP*/
		if(row[20])					
			set_apn_conf_prof(&tmp_gavp, imsi, row[20]);				
	
		/* Set RAT-Frequency-Selection-Priority-ID(u32)*/
		if(row[21])
			SS_SET_U32( ss_set_rat_frequency_selection_priority_id( &tmp_gavp, tmp_u), tmp_u, row[21], "RAT-Frequency-Selection-Priority-ID set.\n", "Failed to set RAT-Frequency-Selection-Priority-ID.\n");
	
		/*Set Trace-Data group Avp*/
		set_trace_data(&tmp_gavp, imsi);
	
		/* Set GPRS-Subscription-Data*/
		if(CHECK_ULR_GPRS_DATA_IND(ulr_flg))					
			set_gprs_subsc_data( &tmp_gavp, imsi);				
	
		/* Set CSG-Subscription-Data accoriding to Equivalent-PLMN-List if it exists in the request */	
		if(ss_get_gavp_equivalent_plmn_list( req, &tmp_gavp2)){

			size_t array_size = 0;
			size_t tmp_size;
			
			/*Get array of Visited-Plmn-Id values*/
			ss_get_visited_plmn_id_array(tmp_gavp2, &visited_plmn_id, &array_size);
			tmp_size = array_size;

			while(tmp_size > 0){

				/*Set CSG-Subscription-Data*/
				set_csg_subscription_data(&tmp_gavp2, imsi, visited_plmn_id[tmp_size-1]);
			
				tmp_size --;
			}

			/*free memory if allocated during ss_get_visited_plmn_id_array() function call*/
			if(array_size)
				free(visited_plmn_id);
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
			set_prose_subsc(&tmp_gavp, row[29]);
	
		/* Set Subscription-Data-Flags*/		
		if(row[30])
			SS_SET_U32( ss_set_subscription_data_flags(&tmp_gavp, tmp_u), tmp_u, row[30], "Subscription-Data-Flags set.\n", "Failed to set Subscription-Data-Flags.\n");
	
		SS_CHECK( ss_add_avp( (msg_or_avp **) msg, tmp_gavp), "Subscription-Data added to messge.\n", "Failed to add Subscription-Data.\n");
	}

	mysql_free_result(res);
	mysql_close(conn);
}

/*Insert/Update terminfo(Terminal-Information) table*/
static int get_terminal_info(struct msg * msg, utf8string **imei, utf8string **soft_ver, octetstring **meid){

	struct avp * tmp_gavp;
	int check = 3;

	if(!msg)
		return 1;
	if((!imei) && (!soft_ver) && (!meid))
		return 1;

	/*check terminal-info avp*/
	SS_WCHECK( ss_get_gavp_terminal_information( msg, &tmp_gavp), "Terminal-Information extracted.\n", "Failed to extract Terminal-Information\n", return 1;);

	/*Get IMIE*/
	if(imei)
		SS_WCHECK( ss_get_imei(tmp_gavp, imei), "IMEI extracted.\n", "Failed to retrieve IMEI.\n", check--);
				
	/*Get Software Version*/
	if(soft_ver)
		SS_WCHECK( ss_get_software_version(tmp_gavp, soft_ver), "Software Version extracted.\n", "Failed to retrieve Software Version.\n", check--);
		
	/*Get 3gpp2-MEID*/
	if(meid)
		SS_WCHECK( ss_get_3gpp2_meid(tmp_gavp, meid), "3GPP2 MEID extracted.\n", "Failed to retrieve Software 3GPP2 MEID.\n", check--);

	/*at least one of the avp is found*/
	if(check != 0)
		return 0;

	return 1;
}

/*Insert/Update database tables*/
static int insert_update_db(MYSQL * conn, char * table_name, char * column_name, char * value, char * imsi){

	char buf[500] = {0};

	if((!conn) || (!table_name) || (!column_name) || (!value) || (!imsi))
		return 1;

	/*Prepare insert/update mysql statement*/
	sprintf(buf, "insert into %s (imsi,%s) values('%s','%s') on duplicate key update %s='%s'", table_name, column_name, imsi, value, column_name, value);
	
	/*insert/update the table*/
	if(mysql_query(conn,buf)){
		fprintf(stderr, "Insert/Update %s table failed: %s\n", table_name, mysql_error(conn));
		return 1;
	}

	return 0;
}

/*Insert/Update terminal information into database*/
static int insert_update_db_terminfo(MYSQL *conn, char * imsi, char *imei, char *soft_ver, char *meid, integer32 ue_srv_capb){
	
	char tmp_str[2] = {0};	

	if((!conn) || (!imsi)){
		printf("ERROR : Terminal information insert/update failed. Given mysql connection is NULL.\n");
		return 1;
	}
	/*Insert/update IMEI into termInfor table*/
	if(imei)
		SS_WCHECK(insert_update_db(conn, "termInfo", "imei", imei, imsi), "IMIE iserted/updated.\n", "Insert/Update IMIE failed.\n", NULL);
	/*Insert/update software version into termInfor table*/
	if(soft_ver)
		SS_WCHECK(insert_update_db(conn, "termInfo", "softVersion", soft_ver, imsi), "software version iserted/updated.\n", "Insert/Update software version failed.\n", NULL);
	/*Insert/update 3GPP2 MEID into termInfor table*/
	if(meid)
		SS_WCHECK(insert_update_db(conn, "termInfo", "meid", meid, imsi), "MEID iserted/updated.\n", "Insert/Update MEID failed.\n", NULL);
	/*Insert/update UE SRVCC capability into termInfor table*/
	if(ue_srv_capb >= 0){
		sprintf( tmp_str, "%.1d", ue_srv_capb);
		SS_WCHECK(insert_update_db(conn, "termInfo", "ueSrvccCapab", tmp_str, imsi), "UE SRVCC capability iserted/updated.\n", "Insert/Update UE SRVCC capability failed.\n", NULL);
	}

	return 0;	
}	

/*Update the mme table with the new mme info*/
static int insert_update_mme(MYSQL *conn, char * imsi, char * origin_hst, char * origin_rlm, char * ueprg, char * mt_sms){

	if((!conn) || (!imsi)){
		printf("ERROR : mme table insert/update failed. 'mysql connection' or/and 'imsi' is NULL.\n");
		return 1;
	}

	/*Insert/update origin host into mme table*/
	if(origin_hst)
		SS_WCHECK( insert_update_db(conn, "mme", "mmeHost", origin_hst, imsi), "origin host inserted/updated into mme table.\n", "insert/update origin host into mme failed.\n", NULL);
	/*Insert/update origin realm into mme table*/
	if(origin_rlm)
		SS_WCHECK( insert_update_db(conn, "mme", "mmeRealm", origin_rlm, imsi), "mme realm inserted/updated into mme talbe.\n", "insert/update origin realm into mme failed.\n", NULL);
	/*Insert/update UE purged into mme table*/
	if(ueprg)
		SS_WCHECK( insert_update_db(conn, "mme", "uePurged", ueprg, imsi), "ue purged inserted/updated into mme table.\n", "isert/update UE purged into mme failed.\n", NULL);
	/*Insert/update MME-Number-for-MT-SMS into mme table*/
	if(mt_sms)
		SS_WCHECK( insert_update_db(conn, "mme", "mmeMtSmsNumb", mt_sms, imsi), "MME-Number-for-MT-SMS iserted/updated into mme table.\n", "isert/update MME-Number-for-MT-SMS into mme failed.\n", NULL);	

	return 0;
}
/*Get MIP-Home-Agent-Address*/
static inline int get_mip_addr(struct avp *gavp, address ** addr_1, address ** addr_2){

	address ** hm_agnt_addr = NULL;
	size_t array_size = 0;

	if(!gavp)
		return 1;
	
	if((!addr_1) && (!addr_2))
		return 1;

	/*Get MIP-Home-Agent-Address*/							
	SS_WCHECK( ss_get_mip_home_agent_address_array( gavp, &hm_agnt_addr, &array_size), "MIP-Home-Agent-Address array of values retrieved.\n", "Failed to retrieve MIP-Home-Agent-Address values.\n", NULL);

	if(array_size){
		
		if(addr_1){
			*addr_1 = hm_agnt_addr[array_size-1];
			array_size--;
		}
		else if(addr_2 && array_size)
			*addr_2 = hm_agnt_addr[array_size];
		
		free(hm_agnt_addr);

		return 0;
	}	

	return 1;
}

/*Get MIP-Home-Agent-Host child avp values*/
static inline int get_mip_home_agnt_hst(struct avp * gavp, diameterid ** dst_host, diameterid ** dst_realm){

	struct avp * tmp_gavp;

	if((!gavp) || (!dst_host) || (!dst_realm))
		return 1;

	/*Get MIP-Home-Agent-Host AVP*/
	SS_WCHECK( ss_get_gavp_mip_home_agent_host(gavp, &tmp_gavp), "MIP-Home-Agent-Host AVP retrieved,\n", "Failed to retrieve MIP-Home-Agent-Host.\n", return 1;);
	
	/*Get destination host value*/
	SS_CHECK(ss_get_destination_host_gavp(tmp_gavp, dst_host), "destination host retrieved.\n", "Failed to extract Destination-Host.\n");

	/*Get destination realm value*/
	SS_CHECK(ss_get_destination_realm_gavp(tmp_gavp, dst_realm), "destination host retrieved.\n", "Failed to extract Destination-Realm.\n");

	return 0;		
}

/*Get MIP6-Agent-Info child AVP values*/
static inline int get_mip6_values(struct avp *gavp, address ** addr_1, address ** addr_2, diameterid ** dst_host, diameterid ** dst_realm){

	struct avp * tmp_gavp;	
	int check = 1;

	if(!gavp)
		return 1;
	if((!addr_1) && (!addr_2) && (!dst_host) && (!dst_realm))
		return 1;

	/*check for  MIP6-Agent-Info avp*/
	SS_WCHECK( ss_get_gavp_mip6_agent_info(gavp, &tmp_gavp) , "MIP6-Agent-Info retrieved.\n", "Failed to retrieve MIP6-Agent-Info.\n", return 1;);
		
	/*check for the MIP-Home-Agent-Address*/	
	SS_WCHECK( get_mip_addr(tmp_gavp, addr_1, addr_2), "MIP-Home-Agent-Address retrieved.\n", "Failed to retrieve MIP-Home-Agent-Address.\n", check++);						
							
	/*check for  MIP-Home-Agent-Host */
	SS_WCHECK( get_mip_home_agnt_hst(tmp_gavp, dst_host, dst_realm), "MIP-Home-Agent-Host child AVP values retrieved.\n", "Failed to retrieve MIP-Home-Agent-Host child AVP values.\n", check++);	

	/*if both MIP-Home-Agent-Address and MIP-Home-Agent-Host fails to be retrieved*/
	if(check == 3)
		return 1;
	
	return 0;						
}

/*check for Active-Apn AVPs and update database*/
static void check_update_active_apn(struct msg *msg, char * imsi, MYSQL * conn){

	struct avp *tmp_gavp = NULL;
	struct avp *tmp_gavp2 = NULL;
	char buf[110] = {0};
	char buf2[550] = {0};
	unsigned32 context_id;
	address * hm_agnt_addr_1 = (address *)"";
	address * hm_agnt_addr_2 = (address *)"";
	diameterid * dst_hst = (diameterid *)"";
	diameterid * dst_rlm = (diameterid *)"";
	
	MYSQL_RES *res = NULL;
  	MYSQL_ROW row;
	
	if((!msg) || (!imsi) || (!conn))
		return;

	/*Get Active-Apn AVP from */
	SS_WCHECK( ss_get_gavp_active_apn( msg, &tmp_gavp), "Active-APN AVP retrieved from request.\n", "Failed to retrieve Active-APN AVP.\n", NULL);

	while(tmp_gavp){				
				
		/*Get context-id avp*/
		SS_CHECK( ss_get_context_identifier_gavp(tmp_gavp, &context_id), "Context id value retrieved.\n", "Failed to extract context-Id AVP\n.");

		/*mysql statement to fetch apn subscription data with context id and a 'dynamic' PDN-GW-Allocation-Type*/	
		snprintf(buf,110,"select imsi from apnConf where imsi='%.15s' and contextId='%u' and pdnGwAllocType='1'", imsi, context_id);

		/*Query database and store result*/
		SS_CHECK(get_qry_res(conn, buf, &res), "apn subscription data retrieved from db.\n", "Failed to store apn subscription data from database.\n");
					
		if((row = mysql_fetch_row(res))!= NULL){

			/*check for  MIP6-Agent-Info avp*/
			if(get_mip6_values(tmp_gavp, &hm_agnt_addr_1, &hm_agnt_addr_2, &dst_hst, &dst_rlm) == 0){
			
				/*mysqpl statement to update apnConf table with new MIP6-Agent-Info*/
				snprintf(buf2,550,"update apnConf set mipHomeAgntAddr0='%.16s', mipHomeAgntAddr1='%.16s', mipDestHost='%s', mipDestRealm='%s' where imsi='%.15s' and contextId='%u'",(char *)hm_agnt_addr_1, (char *)hm_agnt_addr_2, (char *)dst_hst, (char *)dst_rlm, imsi, context_id);
				
				/*Update apnConf table*/
				if (mysql_query(conn, buf2)) 
					fprintf(stderr, "Warning : apnConf table update failed: %s\n", mysql_error(conn));			
			}
		}

		mysql_free_result(res);				
		
		/*Get the next Active-Apn group AVP*/
		SS_WCHECK( ss_get_gavp_next_active_apn(tmp_gavp, &tmp_gavp2), "Next Active-Apn retrieved.\n", "Failed to retrieve Next Active-Apn.\n",NULL);
		tmp_gavp = tmp_gavp2;
	}
}



/*Callback function used when Update-Location-Request message is received*/
int test_req_cb_ulr(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){
	
	struct msg * req = NULL;	
	struct avp * tmp_gavp = NULL;	
    char buf[110] = {0};
	unsigned32 ulrflg;
	unsigned32 ulaflg = 0;
	char imsi[16] = {0};
	diameterid * origin_host = NULL;
	diameterid * origin_realm = NULL;
	octetstring * mme_nm_mt_sms = NULL;
	utf8string * imei = NULL;
	utf8string * soft_version = NULL;
	octetstring * meid = NULL;
	integer32 ue_srvcc_capability = -1;
	integer32 rat_type = -1;
	unsigned32 feature_list = 0;
	unsigned char * tmp_ustr = NULL;
	
	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if (msg == NULL)
		return EINVAL;	
	
	/* Message Received */
	SS_CHECK( ss_get_origin_host( *msg, &origin_host), "\n", "Failed to extract Origin-Host.\n");
	fprintf(stdout, COLOR_GREEN"MESSAGE RECEIVED : ULR message received from '%s'"ANSI_COLOR_RESET"\n", (char *)origin_host);	
	
	/* Create answer message header from the request */
	SS_CHECK( ss_create_answer( msg, &req), "Answer message header created from request.\n", "Failed to create answer message header.\n");	

	/* Extract imsi from request message*/
	SS_CHECK( ss_get_user_name(req, &tmp_ustr), "IMSI extracted from request.\n", "Failed to extract IMSI from request.\n");
	strncpy(imsi,(char *)tmp_ustr,15);

	/*Check user from the database and retrieve Rat Type info*/
	/* Connect to the mysql database*/
	connect_db(&conn);
	
	/*Prepare mysql statement to subscription data*/	
	sprintf(buf,"select ratType from subscriptionData where imsi='%.15s'",imsi);

	/*Query database and store result*/
	SS_CHECK(get_qry_res(conn, buf, &res), "RAT type data retrieved from db.\n", "Failed to retriev RAT type data from database.\n");

	/*fetch row*/
	if((row = mysql_fetch_row(res)) == NULL){
			
		/* User is unkown*/
		fprintf(stderr, COLOR_GREEN"OK : ERROR MESSAGE 'DIAMETER_ERROR_USER_UNKNOWN' to be sent."ANSI_COLOR_RESET"\n");

		/*Set origin host, origin realm and 'DIAMETER_ERROR_USER_UNKNOWN' experimental result code*/
		SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_USER_UNKNOWN, msg);

		mysql_free_result(res);
		mysql_close(conn);

		goto send;
	}

	/*Retrive Rat type value from request*/
	SS_CHECK( ss_get_rat_type(req, &rat_type), "Rat type extracted from request.\n", "Failed to extract Rat type from request.\n");

	/* Compare the subscribed RAT type with the recieved RAT type*/
	if(rat_type != atoi(row[0])){

		
		fprintf(stdout, COLOR_GREEN"OK : ERROR MESSAGE 'DIAMETER_ERROR_RAT_NOT_ALLOWED' to be sent. %d."ANSI_COLOR_RESET"\n", rat_type);

		/*Set origin host, origin realm and 'DIAMETER_ERROR_RAT_NOT_ALLOWED' experimental result code*/
		SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_RAT_NOT_ALLOWED, msg);

		mysql_free_result(res);
		mysql_close(conn);

		goto send;
	}

	/*free data from mysql query*/
	mysql_free_result(res);
		
	/*Retrieve supported feature group avp (only 1 avp is expected for testing) from request*/
	SS_CHECK( ss_get_gavp_supported_features(req, &tmp_gavp), "Supported feature AVP retrieved from request.\n", "Failed to retrieve supported feature from request.\n");

	/*Retrieve feature list from supported feature group AVP*/
	SS_CHECK( ss_get_feature_list(tmp_gavp, &feature_list), "feature list value retrieved.\n", "Failed to retrieve feature list.\n");

	/* Check if mme supports ODB_HPLMN_APN*/
	if(!CHECK_SUPPORT_ODB_HPLMN_APN(feature_list)){

		fprintf(stdout,COLOR_GREEN"OK : ERROR MESSAGE 'DIAMETER_ERROR_ROAMING_NOT_ALLOWED' with error diagnostic value 'ODB_HPLMN_APN' to be sent."ANSI_COLOR_RESET"\n");

		/*Set origin host, origin realm and 'DIAMETER_ERROR_ROAMING_NOT_ALLOWED' experimental result code*/
		SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_ROAMING_NOT_ALLOWED, msg);
		
		/*Set Error-Diagnostic AVP with 'ODB_HPLMN_APN' value*/
		SS_CHECK( ss_set_error_diagnostic(msg, (int32_t)ODB_HPLMN_APN), "Error diagnostic value set.\n", "Failed to set error diagnostic.\n");

		/*close mysql connection*/
		mysql_close(conn);
		
		goto send;
	}

	/* Set the Origin-Host, Origin-Realm and "DIAMETER_SUCCESS" Result-Code*/
	SS_CHECK( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1), "origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n", "Failed to set origin-host origin-realm and 'DIAMETER_SUCCESS' set in answer message.\n");

	/*check MME-Number-for-MT-SMS and Set ULA-Flags' MME Registered for SMS bit*/
	if((ss_get_mme_number_for_mt_sms(req, &mme_nm_mt_sms)) == 0){
		
		SET_ULA_MME_REG_SMS(ulaflg); 
		printf("ULA-Flags' MME Registered for SMS bit set.\n");
	}

	/*Retrieve origin realm from request*/
	SS_CHECK( ss_get_origin_realm(req, &origin_realm), "Origin realm retrieved from request.\n", "Failed to retrieve origin realm from request.\n");
		
	/*Prepare mysql statement to fetch mme data*/	
	sprintf(buf,"select * from mme where imsi='%.15s'",imsi);

	/*Query database and store result*/
	SS_CHECK(get_qry_res(conn, buf, &res), "mme data retrieved from db.\n", "Failed to store mme data from database.\n");
	
	if((row = mysql_fetch_row(res))!= NULL){

		/*if new mme is different from old mme*/
		if(strcmp(row[1],(char *)origin_host) != 0){
						
			/* Send cancel location to old mme*/
			printf("Sending CLR to old mme ...\n");
			test_send_clr((diameterid *)row[1], (diameterid *)row[2], (utf8string *)imsi, MME_UPDATE_PROCEDUR, 1); 
			
			/*Update the mme table with the new mme info*/
			SS_WCHECK( insert_update_mme(conn, imsi, (char *)origin_host, (char *)origin_realm, "", (char *)mme_nm_mt_sms), "insert/update mme table.\n", "insert/update mme table failed.\n", NULL);
		}
		else	
			SS_WCHECK( insert_update_mme(conn, imsi, NULL, NULL, "", (char *)mme_nm_mt_sms), "insert/update mme table.\n", "insert/update mme table failed.\n", NULL);
	}				
	else
		SS_WCHECK( insert_update_mme(conn, imsi, (char *)origin_host, (char *)origin_realm, "", (char *)mme_nm_mt_sms), "Insert mme table.\n", "Insert mme table failed.\n", NULL);
	
	/*free data from mysql query*/			
	mysql_free_result(res);
	
	
	/*Retrieve terminal information from request*/
	get_terminal_info(req, &imei, &soft_version, &meid);

	/*Retrieve ue-srvcc-capability from request*/
	SS_WCHECK( ss_get_ue_srvcc_capability(req, &ue_srvcc_capability), "UE-SRVCC-Capability value retrieved from request.\n", "Failed to retrieve UE-SRVCC-Capability value.\n", NULL);

	/*Insert/Update terminfo(Terminal-Information) table*/
	SS_WCHECK( insert_update_db_terminfo( conn, imsi, (char *)imei, (char *)soft_version, (char *)meid, ue_srvcc_capability), "terminfo inserted/updated.\n", "Insert/Update terminfo failed.\n", NULL);

	/*check for Active-Apn AVPs and update database*/
	check_update_active_apn( req, imsi, conn);

	/*close mysql connection*/
	mysql_close(conn);

	/****** Put subscription info into Answer message(ULA) ***************************************/			
	/* extract ulr flag from request*/
	SS_CHECK( ss_get_ulr_flags( req, &ulrflg), "ULR-Flags extracted from request.\n", "Failed to retrieve ulr flags value.\n");

	/*If skip subscriber data is not set in ulr flag then create and set Subscription-Data AVP*/
	if(CHECK_ULR_SKIP_SUBSC_DATA(ulrflg)){
		printf("Setting subscription data ...\n");
		set_subsc_data(msg, imsi, ulrflg, req);
	}

	/* Set Separation-Indication bit and Set ULA-Flags*/
	SET_ULA_SEPARATION_INDICATIN(ulaflg); 
	SS_CHECK( ss_set_ula_flags( msg, ulaflg), "ULA-Flags.\n", "Failed to set ULA-Flags.\n");		

	/* Send the answer */
send:
	/*SS_CHECK( fd_msg_send( msg, NULL, NULL ), "ULA Response sent\n", "Failed to set ULA Response");*/
	fprintf(stdout,"OK : Answer message passed to routing module.\n");
	*act == DISP_ACT_SEND;

	return 0;

/*error:
	return EINVAL;*/
}
