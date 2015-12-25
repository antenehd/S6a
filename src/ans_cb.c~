
#include <my_sys.h>
#include <mysql.h>

#include "internal_ssix.h"


#define CHECK_SKIP_SUBSC_DATA(x) ((1U<<2) & x) 
#define CHECK_GPRS_DATA_IND(x) ((1U<<3) & x) 
#define DIAMETER_ERROR_UNKNOWN_EPS_SUBSCRIPTION  5420 
#define DIAMETER_ERROR_RAT_NOT_ALLOWED			 5421
#define DIAMETER_ERROR_USER_UNKNOWN 			 5001

#define MYSQL_SERVER "localhost"
#define MYSQL_PASSWORD "1234"
#define MYSQL_USER "root"
#define MYSQL_DB "ss_hss"

#define SS_SET_SI32( dict, value, parent, child)	{							 \
	CHECK_FCT_DO(fd_msg_avp_new(dict,0,&child),goto error);						 \
	val.i32=atoi(value);														 \
	CHECK_FCT_DO(fd_msg_avp_setvalue(child,&val),goto error);					 \
	CHECK_FCT_DO(fd_msg_avp_add(parent,MSG_BRW_LAST_CHILD,child),goto error);	 \
}

#define SS_SET_SU32( dict, value, parent, child)  {							 	 \
	CHECK_FCT_DO(fd_msg_avp_new(dict,0,&child),goto error);					     \
	val.u32=(unsigned32)(strtoul(value, NULL, 10));								 \
	CHECK_FCT_DO(fd_msg_avp_setvalue(child,&val),goto error);					 \
	CHECK_FCT_DO(fd_msg_avp_add(parent,MSG_BRW_LAST_CHILD,child),goto error);	 \
}

#define SET_ORIGIN_AND_EXPER_RESULT(result, msg)											\
	{																						\
		/* Add the Origin-Host and Origin-Realm AVP in the answer*/							\
		CHECK_FCT( fd_msg_add_origin ( msg, 0 ) );											\
		/*Set experimental result*/															\
		CHECK_FCT_DO( fd_msg_avp_new( ss_exper_result, 0, &gavp), goto error);				\
		/*Vendor-id*/																		\
		CHECK_FCT_DO(fd_msg_avp_new(ss_vendor_id,0,&avp),goto error);						\
		val.u32=(unsigned32) VENDOR_ID;														\
		CHECK_FCT_DO(fd_msg_avp_setvalue(avp,&val),goto error);								\
  		CHECK_FCT_DO(fd_msg_avp_add(gavp,MSG_BRW_LAST_CHILD,avp),goto error);				\
		/*experimental result code*/														\
		CHECK_FCT_DO( fd_msg_avp_new( ss_exper_res_code, 0, &avp), goto error);				\
		val.u32=(unsigned32) result;														\
		CHECK_FCT_DO(fd_msg_avp_setvalue(avp,&val),goto error);								\
  		CHECK_FCT_DO(fd_msg_avp_add(gavp,MSG_BRW_LAST_CHILD,avp),goto error);				\
		CHECK_FCT_DO( fd_msg_avp_add( msg, MSG_BRW_LAST_CHILD, gavp ), goto error  );		\
	}

/* same as 'enum msg_objtype' found in freadiameter*/
enum _msg_objtype {
	MSG_MSG = 1, 
	MSG_AVP
};
/* same as 'struct msg_avp_chain' found in freadiameter*/
struct _msg_avp_chain {
	struct fd_list		chaining;	/* Chaining information at this level. */
	struct fd_list		children;	/* sentinel for the children of this object */
	enum _msg_objtype 	type;		/* Type of this object, _MSG_MSG or _MSG_AVP */
};

/*Same as 'struct avp' found in freadiameter*/
/*Included here so that the compiler can see 'struct avp' internal stracture when compiling this file*/
struct _avp {
	struct _msg_avp_chain	 avp_chain;		
	int			 avp_eyec;		
	struct dict_object	*avp_model;		
	struct {
		avp_code_t	 mnf_code;		
		vendor_id_t	 mnf_vendor;		
	}  		avp_model_not_found;	
	struct avp_hdr		 avp_public;		
	uint8_t			*avp_source;		
	uint8_t			*avp_rawdata;		
	size_t			 avp_rawlen;		
	union avp_value		 avp_storage;		
	int			 avp_mustfreeos;	
};


/* Search a given AVP model in a AVP */
/* Modified from function  fd_msg_search_avp*/
static int ss_avp_search_avp ( struct avp * avp, struct dict_object * what, struct avp ** avp2, enum msg_brw_dir dir )
{
	struct _avp * nextavp;
	struct dict_avp_data 	dictdata;
	enum dict_object_type 	dicttype;
	
	if(!avp){
		*avp2 = NULL;
		return EINVAL;
	}
		
	CHECK_PARAMS( (fd_dict_gettype(what, &dicttype) == 0) && (dicttype == DICT_AVP) );
	CHECK_FCT(  fd_dict_getval(what, &dictdata)  );
	
	/* Search for AVPs */
	CHECK_FCT(  fd_msg_browse(avp, dir, (void *)&nextavp, NULL) );
	while (nextavp) {
		
		if ( (nextavp->avp_public.avp_code   == dictdata.avp_code)
		  && (nextavp->avp_public.avp_vendor == dictdata.avp_vendor) ) /* always 0 if no V flag */
			break;
		
		/* Otherwise move to next AVP in the message */
		CHECK_FCT( fd_msg_browse(nextavp, MSG_BRW_NEXT, (void *)&nextavp, NULL) );
	}
	
	if (avp2)
		*avp2 = (struct avp *)nextavp;
	
	if (avp2 && nextavp) {
		struct dictionary * dict;
		CHECK_FCT( fd_dict_getdict( what, &dict) );
		CHECK_FCT_DO( fd_msg_parse_dict( nextavp, dict, NULL ), /* nothing */ );
	}
	
	if (avp2 || nextavp)
		return 0;
	else
		return ENOENT;
}

/* Create answer message header from the request */
void create_answer(struct msg **msg, struct msg **ans, struct msg **req){

	
	*req = *msg;
	CHECK_FCT( fd_msg_new_answer_from_req ( fd_g_config->cnf_dict, msg, 0 ) );
	*ans = *msg;

	/* Vendor-Specific-Application-Id */
	SET_VENDOR_SPEC_APP_ID(ans);		

	/*Auth-Session-State*/
	SET_AUTH_SESSION_STATE(ans);
}

int ss_ulr_ans_cb(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){
	
	struct msg *ans, *req;	
	struct avp *avp, *avp1, *avp2 , *gavp, *gavp1, *gavp2, *gavp3, *gavp4;
	struct avp_hdr * hdr = NULL;
	struct avp_hdr * hdr2 = NULL;
	union avp_value val;
	unsigned32 ulrflg;
	unsigned32 ulaflg = 0;
	char imsi[16] = {0};
    char buf[110] = {0};
	char buf2[5] = {0};
	char buf3[550] = {0};
	char buf4[200] = {0};
	char buf5[60] = {0};
	unsigned char * c_temp = NULL;
	unsigned char * c_temp2 = NULL;
	unsigned char * c_temp3 = NULL;
	unsigned char * c_temp4 = NULL;
	int i_temp = -1;
	unsigned int u_temp = 0;

	struct clr_msg clr_req;
	enum cancel_typ  canc_typ;
	unsigned32  clr_flgs;

	MYSQL *conn = NULL;
	MYSQL_RES *res, *res2, *res3;
  	MYSQL_ROW row, row2, row3;


	if (msg == NULL)
		return EINVAL;	
	
	/* Value of Origin-Host */
	printf("ECHO ULR received from ");
	CHECK_FCT( fd_msg_search_avp ( *msg, ss_origin_host, &avp) );
	if (avp) {
		CHECK_FCT( fd_msg_avp_hdr( avp, &hdr ) );
		printf("'%.*s' \n", (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
	} 
	else 
		printf("no_Origin-Host\n");
	
	/* Create answer message header from the request */
	create_answer(msg, &ans, &req);	

	/*Check user from the database and retrieve subscription info*/
	/* Connect to the mysql database*/
	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, MYSQL_SERVER, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, 0, NULL, 0)) {
		fprintf(stderr, "mysql db connection failed:%s\n", mysql_error(conn));
		goto error;
	}
	
	/* Extract imsi from request message and query hss database for the user data*/
	CHECK_FCT_DO( fd_msg_search_avp ( req, ss_user_name, &avp), goto error );
	CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
	strncpy(imsi,(char *)hdr->avp_value->os.data,15);
	sprintf(buf,"select * from subscriptionData where imsi='%s'", imsi);
	if (mysql_query(conn, buf)) {
		fprintf(stderr, "subscription data query for imsi %s failed %s\n", imsi,mysql_error(conn));
    }

	/* Check the result of the query and process it*/
	if((res = mysql_store_result(conn))!=NULL){
		
		/*fetch row*/
		if((row = mysql_fetch_row(res))!= NULL){

			/*TODO:roaming not allowed*/

			/*check if APN-Configuration exists for this user*/
			if(row[19] == NULL){
				printf("SETTING EXP-RES-EPS\n");
				SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_UNKNOWN_EPS_SUBSCRIPTION, ans);
				mysql_free_result(res);
				goto send;
			}

			/* Compare the subscribed RAT type with the recieved RAT type*/
			CHECK_FCT_DO( fd_msg_search_avp ( req, ss_rat_type, &avp), goto error );
			CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
			snprintf(buf2, 4, "%d", hdr->avp_value->i32);
			
			if(strcmp(row[21], buf2) != 0){
				printf("SETTING EXP-RES-rat\n");
				SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_RAT_NOT_ALLOWED, ans);
				mysql_free_result(res);
				goto send;
				printf("after send\n");
			}
			

			/* Set the Origin-Host, Origin-Realm, Result-Code AVPs */
			CHECK_FCT( fd_msg_rescode_set( ans, "DIAMETER_SUCCESS", NULL, NULL, 1 ) );


			/*If the update is from new mme send cancel to old mme, also reset ue_purged if ue is purged*/
			fd_msg_search_avp ( req, ss_origin_host, &avp);
			CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
			memset(buf5,0,60);
			sprintf(buf,"select * from mme where imsi='%s'", imsi);
			if (mysql_query(conn, buf)) {
				fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
			}
			if((res2 = mysql_store_result(conn))!=NULL){
				
				/*check new mme realm*/
				fd_msg_search_avp ( req, ss_origin_realm, &avp2);	
				CHECK_FCT( fd_msg_avp_hdr( avp2, &hdr2));
				c_temp=hdr2->avp_value->os.data;

				/*check MME-Number-for-MT-SMS*/
				fd_msg_search_avp ( req, ss_mme_num_for_mt_sms, &avp2);
				if(avp2){
					CHECK_FCT( fd_msg_avp_hdr( avp2, &hdr2));
					c_temp2=hdr2->avp_value->os.data;

					/*Set ULA-Flags MME Registered for SMS bit*/
					ulaflg |= (1U << 1);					
				}

				/*if there is mme data in database*/
				if((row2 = mysql_fetch_row(res2))!= NULL){
					/*if new mme is different from old mme*/
					if(strcmp(row2[1],(char *)hdr->avp_value->os.data) != 0){
						
						/* Send cancel location to old mme*/
						canc_typ = MME_UPDATE_PROCEDUR;
						clr_flgs = 1; 
						clr_req.dst_host = (diameterid *)row2[1];
						clr_req.dst_realm = (diameterid *)row2[2];	
						clr_req.usr_name = (utf8string *)imsi;	 
						clr_req.suprt_ftr = NULL;
						clr_req.canc_typ = &canc_typ;	 
						clr_req.clr_flgs = &clr_flgs;	
						printf("SEND CLR to old mme\n");		
						ss_req(CLR, &clr_req);

						/*Update the mme table with the new mme info*/
						snprintf(buf3,550,"update mme set mmeHost='%s', mmeRealm='%s', uePurged=0, mmeMtSmsNumb='%.8s' where imsi='%.15s'", hdr->avp_value->os.data, c_temp, c_temp2, imsi);						
					}
					else				
						sprintf(buf3,"update mme set uePurged=0 where imsi='%.15s'",imsi);
				}				
				else
					snprintf(buf3,550,"insert into mme values('%s','%s','%s',0,'%s')",imsi,hdr->avp_value->os.data, c_temp, c_temp2);
				
				/*insert/update new mme data into mme table*/
				if(mysql_query(conn,buf3)){
					fprintf(stderr, "Insert/Update mme table failed: %s\n", mysql_error(conn));
				}

			}    
			else{
				/*TODO*/fprintf(stderr, "mysql_store_result mme table query:%s\n", mysql_error(conn));
			}

			/*Insert/Update terminfo(terminal information) table*/
			/*check terminal-info avp*/
			fd_msg_search_avp ( req, ss_terminal_info, &gavp);
			if(gavp){
				
				c_temp = NULL;
				c_temp2 = NULL;

				/*imei*/
				printf("SETTING imie\n");			
				ss_avp_search_avp ( gavp, ss_imei, &avp, MSG_BRW_FIRST_CHILD);
				if(avp){
					CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
					c_temp=hdr->avp_value->os.data;
				}
				/*Software Version*/
				ss_avp_search_avp ( gavp, ss_soft_version, &avp, MSG_BRW_FIRST_CHILD);
				if(avp){
					CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
					c_temp2= hdr->avp_value->os.data;
				}			
			}
			/*check ue-srvcc-capability avp*/
			fd_msg_search_avp ( req, ss_ue_srvcc_capab, &avp);
			if(avp){
				CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
				i_temp=hdr->avp_value->i32;
			}
			sprintf(buf4,"insert into termInfo values('%.15s','%.14s','%.2s','%d') on duplicate key update imei='%.14s', softVersion='%.2s', ueSrvccCapab='%d'",imsi,c_temp,c_temp2,i_temp,c_temp,c_temp2,i_temp);
			if(mysql_query(conn,buf4)){
				fprintf(stderr, "Insert/Update termInfo table failed: %s\n", mysql_error(conn));
			}


			/*check for active-apn avps*/
			fd_msg_search_avp( req, ss_activ_apn, &gavp);
			while(gavp){				
				
				/*check context-id avp*/
				ss_avp_search_avp( gavp, ss_context_id, &avp, MSG_BRW_FIRST_CHILD);
				CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
				
				/*check if apn subscription with this context id and dynamic pdp gateway*/
				memset(buf4,0,110);
				u_temp=hdr->avp_value->u32;
				snprintf(buf,110,"select imsi from apnConf where imsi='%.15s' and contextId='%u' and pdnGwAllocType='1'", imsi, u_temp);
				mysql_free_result(res2);				
				if (mysql_query(conn, buf)) {

					fprintf(stderr, "apnConf table query failed: %s\n", mysql_error(conn));
				}
				if((res2 = mysql_store_result(conn))!=NULL){
					
					if((row2 = mysql_fetch_row(res2))!= NULL){
						/*check for  MIP6-Agent-Info avp*/
						ss_avp_search_avp( gavp, ss_mip6_agent_info, &gavp2, MSG_BRW_FIRST_CHILD);
						if(gavp2){
							
							c_temp = NULL;
							c_temp2 = NULL;		
							c_temp3 = NULL;
							c_temp4 = NULL;				
	
							/*check for MIP-Home-Agent-Address*/
							ss_avp_search_avp( gavp2, ss_mip_home_agent_addr, &avp, MSG_BRW_FIRST_CHILD);
							if(avp){
								CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
								c_temp=hdr->avp_value->os.data;
							}
							ss_avp_search_avp( avp, ss_mip_home_agent_addr, &avp2, MSG_BRW_NEXT );
							if(avp2){
								CHECK_FCT( fd_msg_avp_hdr( avp2, &hdr));
								c_temp2=hdr->avp_value->os.data;
							}
	
							/*check for  MIP-Home-Agent-Host */
							ss_avp_search_avp( gavp2, ss_mip_home_agen_host, &gavp3, MSG_BRW_FIRST_CHILD);
							if(gavp3){
	
								ss_avp_search_avp( gavp3, ss_dest_host, &avp, MSG_BRW_FIRST_CHILD);
								CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
								c_temp3=hdr->avp_value->os.data;
	
								ss_avp_search_avp( gavp3, ss_dest_realm, &avp, MSG_BRW_FIRST_CHILD);
								CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
								c_temp4=hdr->avp_value->os.data;
							}
	
							/*update the apnConf table with new MIP6-Agent-Info*/
							memset(buf3,0,550);
							snprintf(buf3,550,"update apnConf set mipHomeAgntAddr0='%.16s', mipHomeAgntAddr1='%.16s', mipDestHost='%s', mipDestRealm='%s' where imsi='%.15s' and contextId='%u'",c_temp,c_temp2,c_temp3, c_temp4, imsi, u_temp);
							if (mysql_query(conn, buf3)) {

								fprintf(stderr, "apnConf table update failed: %s\n", mysql_error(conn));
							}
						}
					}

					mysql_free_result(res2);
				}
				else
					/*TODO*/fprintf(stderr, "mysql_store_result apnConf table query:%s\n", mysql_error(conn));

				ss_avp_search_avp( gavp,  ss_activ_apn, &gavp2, MSG_BRW_NEXT);
				gavp=gavp2;
			}



			/****** Put subscription info Answer message(ULA) ****************************************/			

			/* extract ulr flag from request*/
			fd_msg_search_avp ( req, ss_ulr_flgs, &avp);
			CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
			ulrflg = hdr->avp_value->u32;

			/*If skip subscriber data is not set in ulr flag*/
			if(CHECK_SKIP_SUBSC_DATA(ulrflg)){
				
				/* Set Subscription-Data*/
					
				CHECK_FCT_DO( fd_msg_avp_new( ss_subsc_data, 0, &gavp), goto error);

				/* Set Subscriber-Status*/
				if(row[1])
					SS_SET_SI32( ss_subscr_status, row[1], gavp, avp);
			
				/* Set MSISDN*/
				if(row[2])
					SS_SET_OCTET(  ss_msisdn, row[1], gavp, avp);

				/* Set A-MSISDN*/
				if(row[3])
					SS_SET_OCTET(  ss_a_msisdn, row[3], gavp, avp);
	
				/* Set STN-SR*/
				if(row[4])
					SS_SET_OCTET( ss_stn_sr, row[4], gavp, avp);
	
				/* Set ICS-Indicator*/
				if(row[5])
					SS_SET_SI32( ss_ics_indicator, row[5], gavp, avp);
	
				/* Set Network-Access-Mode*/
				if(row[6])
					SS_SET_SI32( ss_net_access_mode, row[6], gavp, avp);
	
				/* Set Operator-Determined-Barring*/
				if(row[7])
					SS_SET_SU32( ss_operator_det_barring, row[7], gavp, avp);
	
				/* Set Regional-Subscription-Zone-Code*/
				if(row[8])
					SS_SET_SU32( ss_regional_subscrip_zone_code, row[8], gavp, avp);
				if(row[9])
					SS_SET_SU32( ss_regional_subscrip_zone_code, row[9], gavp, avp);
				if(row[10])
					SS_SET_SU32( ss_regional_subscrip_zone_code, row[10], gavp, avp);						
	
				/* Set Access-Restriction-Data*/
				if(row[11])
					SS_SET_SU32( ss_access_restrict_data, row[11], gavp, avp);
		
				/* Set APN-OI-Replacement */
				if(row[12])
					SS_SET_OCTET( ss_apn_oi_replacement, row[12], gavp, avp);
	
				/*Set LCS-Info*/
				/*check lcsInfo table for data*/	
				memset(buf5,0,60);
				sprintf(buf5,"select * from lcsInfo where imsi='%.15s'",buf5);
				if (mysql_query(conn, buf5)) {
					fprintf(stderr, "%s\n", mysql_error(conn));      				
			    }		
				if((res2 = mysql_store_result(conn)) != NULL){
			
					if((row2 = mysql_fetch_row(res2))!= NULL){
						CHECK_FCT_DO( fd_msg_avp_new( ss_lcs_info, 0, &gavp1), goto error);
		
						/* Set GMLC-Number */
						if(row2[1])
							SS_SET_OCTET( ss_gmlc_num, row2[1], gavp1, avp);
						if(row2[2])
							SS_SET_OCTET( ss_gmlc_num, row2[2], gavp1, avp);
						if(row2[3])
							SS_SET_OCTET( ss_gmlc_num, row2[3], gavp1, avp);	

						/* Set MO-LR */
						CHECK_FCT_DO( fd_msg_avp_new( ss_mo_lr, 0, &gavp2), goto error);
						if(row2[4])
							SS_SET_OCTET( ss_ss_code, row2[4], gavp2, avp);
						if(row2[5])
							SS_SET_OCTET( ss_ss_status, row2[5], gavp2, avp);
						if(row2[6])
							SS_SET_OCTET( ss_ss_code, row2[6], gavp2, avp);
						if(row2[7])
							SS_SET_OCTET( ss_ss_status, row2[7], gavp2, avp);
						if(row2[8])
							SS_SET_OCTET( ss_ss_code, row2[8], gavp2, avp);
						if(row2[9])
							SS_SET_OCTET( ss_ss_status, row2[9], gavp2, avp);
						if(row2[4] || row2[6] || row2[8])	
							CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2), goto error);

						CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);
					}				
					mysql_free_result(res2);		
				}
					
				/* Set Teleservice-List & TS-Code*/
				CHECK_FCT_DO( fd_msg_avp_new( ss_teleservice_list, 0, &gavp1), goto error);
				if(row[13])
					SS_SET_OCTET( ss_ts_code, row[13], gavp1,avp);
				if(row[14])
					SS_SET_OCTET( ss_ts_code, row[14], gavp1,avp);
				if(row[15])
					SS_SET_OCTET( ss_ts_code, row[15], gavp1,avp);
				if(row[13] || row[14] || row[15])
					CHECK_FCT_DO( fd_msg_avp_add(gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);	

				/*************** Set Call-Barring-Info ******************************************/
				/*check callBaringInfo table for data*/	
				memset(buf,0,110);
				sprintf(buf,"select * from callBaringInfo where imsi='%.15s'",imsi);
				if (mysql_query(conn, buf)) {
					fprintf(stderr, "%s\n", mysql_error(conn));      				
			    }		
				if((res2 = mysql_store_result(conn)) != NULL){
				
					while((row2 = mysql_fetch_row(res2)) != NULL){
		
						CHECK_FCT_DO( fd_msg_avp_new( ss_call_barr_info, 0, &gavp1), goto error);	
						/*Set SS-Code*/	
						if(row2[1])
							SS_SET_OCTET( ss_ss_code, row2[1], gavp1, avp);	
						/*Set SS-Code*/	
						if(row2[2])
							SS_SET_OCTET( ss_ss_status, row2[2], gavp1, avp);
	
						CHECK_FCT_DO( fd_msg_avp_add(gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);		
					} 
				}
					
				/********** Set 3GPP-Charging-Characteristics ************************************/
				if(row[16])
					SS_SET_OCTET( ss_3gpp_charging_char, row[16], gavp, avp);
	
				/* Set AMBR*/
				CHECK_FCT_DO( fd_msg_avp_new( ss_ambr, 0, &gavp1), goto error);
				/* Set Max-Requested-Bandwidth-UL */
				if(row[17])
					SS_SET_SU32( ss_max_req_band_ul, row[17], gavp1, avp);	
				/* Set Max-Requested-Bandwidth-DL */
				if(row[18])
					SS_SET_SU32( ss_max_req_band_dl, row[18], gavp1, avp);
				if(row[17] || row[18])
					CHECK_FCT_DO( fd_msg_avp_add(gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);					
			
				/************ Set APN-Configuration-Profile ***************************************/
				if(row[19] && row [20]){

					/*check apnConf table for data*/	
					memset(buf,0,110);
					sprintf(buf,"select * from apnConf where imsi='%.15s' and contextId='%.10s'",imsi,row[19]);
					if (mysql_query(conn, buf)) {
						fprintf(stderr, "%s\n", mysql_error(conn));      				
				    }		
					if((res2 = mysql_store_result(conn)) != NULL){
				
						if((row2 = mysql_fetch_row(res2)) != NULL){

							CHECK_FCT_DO( fd_msg_avp_new( ss_apn_conf_prof, 0, &gavp1), goto error);
	
							/*Set Context-Identifier*/
							SS_SET_SU32( ss_context_id, row[19], gavp1, avp);
		
							/*Set All-APN-Configurations-Included-Indicator */
							SS_SET_SI32( ss_all_apn_config_incl_ind, row[20], gavp1, avp);
	
							/******Set APN-Configuration****************************************************/
							CHECK_FCT_DO( fd_msg_avp_new( ss_apn_conf, 0, &gavp2), goto error);	

							/*Set Context-Identifier*/
							if(row2[1])
								SS_SET_SU32( ss_context_id, row2[1], gavp2, avp);
	
							/* Set Served-Party-IP-Address*/	
							if(row2[2])
								SS_SET_OCTET( ss_servd_party_ip_addr, row2[2], gavp2, avp);
							if(row2[3])
								SS_SET_OCTET( ss_servd_party_ip_addr, row2[3], gavp2, avp);						

							/*Set PDN-Type*/
							if(row2[4])
								SS_SET_SI32( ss_pdn_type, row2[4], gavp2, avp);

							/* Set Service-Selection*/
							if(row2[5])
								SS_SET_OCTET( ss_service_selection, row2[5], gavp2, avp);
	
							/*** Set eps_qos_prof: EPS-Subscribed-QoS-Profile **************************/
							CHECK_FCT_DO( fd_msg_avp_new( ss_eps_subscd_qos_prof, 0, &gavp3), goto error);
							/* Set QoS-Class-Identifier*/
							if(row2[6])
								SS_SET_SI32( ss_qos_class_id, row2[6], gavp3, avp);

							/* Set Allocation-Retention-Priority**********/
							CHECK_FCT_DO( fd_msg_avp_new( ss_alloc_retention_prio, 0, &gavp4), goto error);
							/* Set Priority-Level */
							if(row2[7])
								SS_SET_SU32( ss_prio_level, row2[7], gavp4, avp);

							/* Set Pre-emption-Capability*/
							if(row2[8])		
								SS_SET_SI32( ss_pre_emp_capb, row2[8], gavp4, avp);

							/* Set Pre-emption-Vulnerability*/
							if(row2[9])	
								SS_SET_SI32( ss_pre_emp_vuln, row2[9], gavp4, avp);
							if(row2[7] || row2[8] || row[9])
								CHECK_FCT_DO( fd_msg_avp_add( gavp3, MSG_BRW_LAST_CHILD, gavp4), goto error);		
							
							CHECK_FCT_DO( fd_msg_avp_add( gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);
							
							
							/* Set VPLMN-Dynamic-Address-Allowed*/
							if(row[10])
								SS_SET_SI32( ss_vplmn_dyn_addr_allowed, row[10], gavp2, avp);

							/*** Set MIP6-Agent-Info AVP ******************************************/
							CHECK_FCT_DO( fd_msg_avp_new ( ss_mip6_agent_info, 0,&gavp3), goto error );
							/* Set MIP-Home-Agent-Address avp*/
							if(row2[11])
								SS_SET_OCTET( ss_mip_home_agent_addr, row2[11], gavp3, avp);						
							if(row2[12])
								SS_SET_OCTET( ss_mip_home_agent_addr, row2[11], gavp3, avp);
							/* Set MIP-Home-Agent-Host avp*/
							CHECK_FCT_DO( fd_msg_avp_new ( ss_mip_home_agen_host, 0,&gavp4), goto error );	
							/*Set Destination-Host avp*/
							if(row2[13])
								SS_SET_OCTET( ss_dest_host, row2[13], gavp4, avp);
							/* Set Destination-Realm avp*/
							if(row2[14])
								SS_SET_OCTET( ss_dest_realm, row2[14], gavp4, avp);
							if(row2[13] || row2[14])					
								CHECK_FCT_DO( fd_msg_avp_add( gavp3, MSG_BRW_LAST_CHILD, gavp4 ), goto error);
								
							CHECK_FCT_DO( fd_msg_avp_add( gavp2, MSG_BRW_LAST_CHILD, gavp3 ), goto error );
			

							/* Set Visited-Network-Identifier *********************/
							if(row2[15])
								SS_SET_OCTET( ss_vistd_net_id, row2[15], gavp2, avp);

							/* Set PDN-GW-Allocation-Type */
							if(row2[16])
								SS_SET_SI32( ss_pdn_gw_alloc_type, row2[16], gavp2, avp);
									
							/* Set 3GPP-Charging-Characteristics*/
							if(row2[17])
								SS_SET_OCTET( ss_3gpp_charging_char, row2[17], gavp2, avp);
	
							/* Set AMBR*/
							CHECK_FCT_DO( fd_msg_avp_new( ss_ambr, 0, &gavp3), goto error);
							/* Set Max-Requested-Bandwidth-UL */
							if(row2[18])								
	 							SS_SET_SU32( ss_max_req_band_ul, row2[18], gavp3, avp);
							/* Set Max-Requested-Bandwidth-DL*/			
							if(row2[19])
								SS_SET_SU32( ss_max_req_band_dl, row2[19], gavp3, avp);
							if(row2[18] || row2[19])
								CHECK_FCT_DO( fd_msg_avp_add(gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);	
															

							/* Set APN-OI-Replacement*********/
							if(row2[20])
								SS_SET_OCTET( ss_apn_oi_replacement, row2[20], gavp2, avp);

							/* Set SIPTO-Permission*/
							if(row2[21])
								SS_SET_I32( ss_sipto_permis, row2[21], gavp2, avp);
	
							/* Set LIPA-Permission*/
							if(row2[22])
								SS_SET_SI32( ss_lipa_permis, row2[22], gavp2, avp);

							/* Set Restoration-Priority*/
							if(row2[23])
								SS_SET_SU32( ss_restor_prio, row2[23], gavp2, avp);
	
							/* Set SIPTO-Local-Network-Permission*/
							if(row2[24])
								SS_SET_SU32( ss_sipto_local_net_permis, row2[24], gavp2, avp);

							/* Set WLAN-offloadability*/
							CHECK_FCT_DO( fd_msg_avp_new( ss_wlan_offloadability, 0, &gavp3), goto error);
							/* Set WLAN-offloadability-EUTRAN */							
							if(row2[25])
								SS_SET_SU32( ss_wlan_offloadability_eutran, row2[25], gavp3, avp);
							/* Set WLAN-offloadability-UTRAN */							
							if(row2[26])
								SS_SET_SU32( ss_wlan_offloadability_eutran, row2[26], gavp3, avp);
							if(row2[25] || row2[26])
								CHECK_FCT_DO( fd_msg_avp_add( gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);	
	
							CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2), goto error);
							CHECK_FCT_DO( fd_msg_avp_add(gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);	
						}
						mysql_free_result(res2);
					}
				}
	
				/* Set RAT-Frequency-Selection-Priority-ID*/
				if(row[21])
					SS_SET_U32( ss_rat_freq_sel_prior_id, row[21], gavp, avp);
	
				/* Set Trace-Data*/
				memset(buf5,0,60);
				sprintf(buf5,"select * from traceData where imsi='%.15s'",imsi);
				if (mysql_query(conn, buf5)) {
					fprintf(stderr, "%s\n", mysql_error(conn));      				
				}		
				if((res2 = mysql_store_result(conn)) != NULL){
				
					if((row2 = mysql_fetch_row(res2)) != NULL){
	
						CHECK_FCT_DO( fd_msg_avp_new( ss_trace_data, 0, &gavp1), goto error);
		
						/* Set Trace-Reference*/
						if(row2[1])
							SS_SET_OCTET( ss_trace_ref, row2[1], gavp1, avp);
	
						/* Set Trace-Depth*/
						if(row2[2])
							SS_SET_SI32( ss_trace_depth, row2[2], gavp1, avp);
	
						/* Set Trace-NE-Type-List*/
						if(row2[3])
							SS_SET_OCTET( ss_trace_ne_type_list, row2[3], gavp1, avp);
		
						/* Set Trace-Interface-List*/
						if(row2[4])
							SS_SET_OCTET( ss_trace_interf_list, row2[4], gavp1, avp);
	
						/* Set Trace-Event-List*/
						if(row2[5])
							SS_SET_OCTET( ss_trace_event_list, row2[5], gavp1, avp);
	
						/* Set OMC-Id*/
						if(row2[6])
							SS_SET_OCTET( ss_omc_id, row2[6], gavp1, avp);
		
						/* Set Trace-Collection-Entity*/
						if(row2[7])
							SS_SET_OCTET( ss_trace_coll_entity, row2[7], gavp1, avp);
	
						/* Set MDT-Configuration *******************************************/
						CHECK_FCT_DO( fd_msg_avp_new( ss_mdt_conf, 0, &gavp2), goto error);	
						/* Set Job-Type*/
						if(row2[8])
							SS_SET_SI32( ss_job_type, row2[8], gavp2, avp);	
						/* Set Area-Scope */		
						memset(buf5,0,60);
						sprintf(buf5,"select * from areaScope where imsi='%.15s'",imsi);
						if (mysql_query(conn, buf5)) {
							fprintf(stderr, "%s\n", mysql_error(conn));      				
						}		
						if((res3 = mysql_store_result(conn)) != NULL){
						
							while((row3 = mysql_fetch_row(res3)) != NULL){
	
								CHECK_FCT_DO( fd_msg_avp_new( ss_area_scope, 0, &gavp3), goto error);
	
								/* Set Cell-Global-Identity*/
								if(row3[1])
									SS_SET_OCTET( ss_cell_glb_id, row3[1], gavp3, avp);


								/* Set E-UTRAN-Cell-Global-Identity*/
								if(row3[2])
									SS_SET_OCTET( ss_e_utran_cell_glb_id, row3[2], gavp3, avp);

								/* Set Routing-Area-Identity*/
								if(row3[3])
									SS_SET_OCTET( ss_rout_area_id, row3[3], gavp3, avp);

								/* Set Location-Area-Identity*/
								if(row3[4])
									SS_SET_OCTET( ss_loc_area_id, row3[4], gavp3, avp);

								/* Set Tracking-Area-Identity*/
								if(row3[5])
									SS_SET_OCTET( ss_track_area_id, row3[5], gavp3, avp);

								CHECK_FCT_DO( fd_msg_avp_add( gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);
							}							
							mysql_free_result(res3);	
						}	

						/* Set List-Of-Measurements */		
						if(row2[9])
							SS_SET_U32( ss_list_of_measr, row2[9], gavp2, avp);

						/* Set Reporting-Trigger */		
						if(row2[10])
							SS_SET_SU32( ss_repor_trig, row2[10], gavp2, avp);

						/* Set Report-Interval */		
						if(row2[11])
							SS_SET_SI32( ss_repor_intrv, row2[11], gavp2, avp);

						/* Set Report-Amount */		
						if(row2[12])
							SS_SET_SI32( ss_repor_amount, row2[12], gavp2, avp);
	
						/* Set Event-Threshold-RSRP */		
						if(row2[13])
							SS_SET_SU32( ss_evt_thrsd_rsrp, row2[13], gavp2, avp);

						/* Set Event-Threshold-RSRQ */		
						if(row2[14])
							SS_SET_SU32( ss_evt_thrsd_rsrq, row2[14], gavp2, avp);

						/* Set Logging-Interval*/	
						if(row2[15])
							SS_SET_SI32( ss_log_intrv, row2[15], gavp2, avp);

						/* Set Logging-Duration */		
						if(row2[16])
							SS_SET_SI32( ss_log_dur, row2[16], gavp2, avp);

						/* Set Measurement-Period-LTE*/	
						if(row2[17])
							SS_SET_SI32( ss_measr_perd_lte, row2[17], gavp2, avp);

						/* Set Measurement-Period-UMTS*/		
						if(row2[18])
							SS_SET_SI32( ss_measr_perd_umts, row2[18], gavp2, avp);

						/* Set Collection-Period-RMM-LTE*/	
						if(row2[19])
							SS_SET_SI32( ss_coll_perd_rrm_lte, row2[19], gavp2, avp);

						/* Set Collection-Period-RRM-UMTS*/		
						if(row2[20])
							SS_SET_SI32( ss_coll_perd_rrm_umts, row2[20], gavp2, avp);

						/* Set Positioning-Method*/		
						if(row2[21])
							SS_SET_OCTET( ss_pos_meth, row2[21], gavp2, avp);

						/* Set Measurement-Quantity*/		
						if(row2[22])
							SS_SET_OCTET( ss_measr_quant, row2[22], gavp2, avp);

						/* Set Event-Threshold-Event-1F*/		
						if(row2[23])
							SS_SET_SI32( ss_evt_thrsd_evt_1f, row2[23], gavp2, avp);

						/* Set Event-Threshold-Event-1I*/		
						if(row2[24])
							SS_SET_SI32( ss_evt_thrsd_evt_1i, row2[24], gavp2, avp);

						/* Set MDT-Allowed-PLMN-Id*/
						if(row2[25])
							SS_SET_OCTET( ss_mdt_allow_plmn_id, row2[25], gavp2, avp);
						if(row2[26])
							SS_SET_OCTET( ss_mdt_allow_plmn_id, row2[26], gavp2, avp);
						if(row2[27])
							SS_SET_OCTET( ss_mdt_allow_plmn_id, row2[27], gavp2, avp);	
	
						CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2), goto error);

						CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);
					}
					mysql_free_result(res2);									
				}
	
				/* Set GPRS-Subscription-Data*/
				if(CHECK_GPRS_DATA_IND(ulrflg)){
	
					memset(buf5,0,60);
					sprintf(buf5,"select * from gprsData where imsi='%.15s'",imsi);
					if (mysql_query(conn, buf5)) {
						fprintf(stderr, "%s\n", mysql_error(conn));      				
					}		
					if((res2 = mysql_store_result(conn)) != NULL){
						
						i_temp = 1;
						CHECK_FCT_DO( fd_msg_avp_new( ss_gprs_subsc_data, 0, &gavp1), goto error);

						while((row2 = mysql_fetch_row(res2)) != NULL){
	
							/* Set Complete-Data-List-Included-Indicator*/
							if(row[22] && i_temp){
								SS_SET_SI32( ss_complete_data_list_incl_ind, row[22], gavp1, avp);
								i_temp = 0;
							}

							/* Set PDP-Context *****************************************************/
							CHECK_FCT_DO( fd_msg_avp_new( ss_pdp_context, 0, &gavp2), goto error);
	
							/* Set Context-Identifier */
							if(row2[1])
								SS_SET_SU32( ss_context_id, row2[1], gavp2, avp);

							/* Set PDP-Type */
							if(row2[2])
								SS_SET_OCTET( ss_pdp_type, row2[2], gavp2, avp);

							/* Set PDP-Address */
							if(row2[3])
								SS_SET_OCTET( ss_pdp_addr, row2[3], gavp2, avp);						
	
							/* Set QoS-Subscribed */
							if(row2[4])
								SS_SET_OCTET( ss_qos_subscr, row2[4], gavp2, avp);

							/* Set VPLMN-Dynamic-Address-Allowed */
							if(row2[5])
								SS_SET_SI32( ss_vplmn_dyn_addr_allowed, row2[5], gavp2, avp);						

							/* Set Service-Selection*/
							if(row2[6])
								SS_SET_OCTET( ss_service_selection, row2[6], gavp2, avp);

							/* Set 3GPP-Charging-Characteristics */
							if(row2[7])
								SS_SET_OCTET( ss_3gpp_charging_char, row2[7], gavp2, avp);					

							/* Set Ext-PDP-Type */
							if(row2[8])
								SS_SET_OCTET( ss_ext_pdp_type, row2[8], gavp2, avp);		

							/* Set Ext-PDP-Address */
							if(row2[9])
								SS_SET_OCTET( ss_ext_pdp_addr, row2[9], gavp2, avp);		

							/* Set AMBR *******************/
							CHECK_FCT_DO( fd_msg_avp_new( ss_ambr, 0, &gavp3), goto error);
							/* Set Max-Requested-Bandwidth-UL */
							if(row2[10])
								SS_SET_SU32( ss_max_req_band_ul, row2[10], gavp3, avp);
							/* Set Max-Requested-Bandwidth-DL */
							if(row2[11])
								SS_SET_U32( ss_max_req_band_dl, row2[11], gavp3, avp);		
							CHECK_FCT_DO( fd_msg_avp_add(gavp2, MSG_BRW_LAST_CHILD, gavp3), goto error);			
							
							/* Set APN-OI-Replacement*/
							if(row2[12])
								SS_SET_OCTET( ss_apn_oi_replacement, row2[12], gavp2, avp);

							/* Set SIPTO-Permission */
							if(row2[13])
								SS_SET_SI32( ss_sipto_permis, row2[13], gavp2, avp);					
	
							/* Set LIPA-Permission */
							if(row2[14])
								SS_SET_SI32( ss_lipa_permis, row2[14], gavp2, avp);		

							/* Set Restoration-Priority */
							if(row2[15])
								SS_SET_SU32( ss_restor_prio, row2[15], gavp2, avp);

							/* Set SIPTO-Local-Network-Permission */
							if(row2[16])
								SS_SET_SU32( ss_sipto_local_net_permis, row2[16], gavp2, avp);	

							CHECK_FCT_DO( fd_msg_avp_add( gavp1, MSG_BRW_LAST_CHILD, gavp2), goto error);			
						} 

						CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);
						mysql_free_result(res2);
					}	
				}
	
				/* Set CSG-Subscription-Data accoriding to equivalent PLMN if it exists in the request */
				CHECK_FCT_DO(fd_msg_search_avp(req, ss_eqv_plmn_list, &gavp1), goto error);
				if(gavp1){

					ss_avp_search_avp(gavp1, ss_visited_plmn_id, &avp1, MSG_BRW_FIRST_CHILD);

					while(avp1){

						CHECK_FCT( fd_msg_avp_hdr( avp1, &hdr));

						memset(buf,0,110);
						sprintf(buf5,"select * from csgData where imsi='%.15s' and visitPlmnId='%s'", imsi, hdr->avp_value->os.data);
						if (mysql_query(conn, buf)) {
							fprintf(stderr, "%s\n", mysql_error(conn));      				
						}		
						if((res2 = mysql_store_result(conn)) != NULL){							
		
							if((row2 = mysql_fetch_row(res2)) != NULL){
			
								CHECK_FCT_DO( fd_msg_avp_new( ss_csg_subsc_data, 0, &gavp1), goto error);

								/* Set CSG-Id*/
								if(row2[1])
									SS_SET_SU32( ss_csg_id, row2[1], gavp1, avp);
	
								/* Set Expiration-Date*/
								if(row2[2])
									SS_SET_OCTET( ss_expir_date, row2[2], gavp1, avp);
	
								/* Set Service-Selection*/
								if(row2[3])
									SS_SET_OCTET( ss_service_selection, row[3], gavp1, avp);
								if(row2[4])
									SS_SET_OCTET( ss_service_selection, row[4], gavp1, avp);
								if(row2[5])
									SS_SET_OCTET( ss_service_selection, row[5], gavp1, avp);		
		
								/* Set Visited-PLMN-Id*/
								if(row2[6])
									SS_SET_OCTET( ss_visited_plmn_id, row2[6], gavp1, avp);	

								CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);		
						
							} 
							
							mysql_free_result(res2);
						}

						/* Check next visited plmn id in equivalent plmn id, if it exists*/
						ss_avp_search_avp(avp1, ss_visited_plmn_id, &avp2, MSG_BRW_NEXT);
						avp1 = avp2;
					}
				}
	
				/* Set Roaming-Restricted-Due-To-Unsupported-Feature*/		
				if(row[23])
					SS_SET_SI32( ss_roam_restr_dueto_unsuppr_featr, row[23], gavp, avp);

				/* Set Subscribed-Periodic-RAU-TAU-Timer*/		
				if(row[24])
					SS_SET_SU32( ss_subscr_priod_rau_tau_timer, row[24], gavp, avp);

				/* Set MPS-Priority*/		
				if(row[25])
					SS_SET_SU32( ss_mps_prio, row[25], gavp, avp);	

				/* Set VPLMN-LIPA-Allowed*/		
				if(row[26])
					SS_SET_SI32( ss_vplmn_lipa_allow, row[26], gavp, avp);
	
				/* Set Relay-Node-Indicator*/		
				if(row[27])
					SS_SET_SI32( ss_rely_nod_ind, row[27], gavp, avp);
	
				/* Set MDT-User-Consent*/		
				if(row[28])
					SS_SET_SI32( ss_mdt_usr_consent, row[28], gavp, avp);	
	
				/* Set Subscribed-VSRVCC*/		
				if(row[29])
					SS_SET_SI32( ss_subscr_vsrvcc, row[29], gavp, avp);
	
				/* Set ProSe-Permission in ProSe-Subscription-Data*/
				if(row[30]){
					CHECK_FCT_DO( fd_msg_avp_new( ss_prose_subsc_data, 0, &gavp1), goto error);	
					SS_SET_SI32( ss_prose_permis, row[30], gavp1, avp);	
					CHECK_FCT_DO( fd_msg_avp_add( gavp, MSG_BRW_LAST_CHILD, gavp1), goto error);
				}
	
				/* Set Subscription-Data-Flags*/		
				if(row[31])
					SS_SET_SU32( ss_subsc_data_flgs, row[31], gavp, avp);
	
				CHECK_FCT_DO( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, gavp), goto error);
				
				/* Set ULA-Flags*/
				/* Set paration Indication bit*/
				ulaflg |= 1U;
				SS_SET_U32( ss_subsc_data_flgs, &ulaflg, ans, avp);
			}				
		}
		/* User is unkown*/
		else{
			
			SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_USER_UNKNOWN,ans);
		}

		mysql_free_result(res);		
	}
	else{
			/*TODO:QUERY ERROR  :DIAMETER_UNABLE_TO_COMPLY*/
		
		fprintf(stderr, " Query Error %s\n", mysql_error(conn));
		goto error; 
	}
	
	/* Send the answer */
	send:
		printf("ULA: Response sent\n");
		CHECK_FCT( fd_msg_send( msg, NULL, NULL ) );
		return 0;
	/*TODO:ERROR*/
	error:
		return EINVAL;
}

/*Call back to handle response when CLR is received*/
/*TODO: this is defined in way suitable for testing, change to practical usage, i.e like checking if the user(imsi)*/
/*belongs to this mme and respond accordingly*/
int ss_clr_ans_cb(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	struct avp *avp, *gavp;
	struct avp_hdr * hdr = NULL;
	union avp_value val;

	if (msg == NULL)
		return EINVAL;
	
	/* Value of Origin-Host */
	printf("ECHO CLR received from ");
	CHECK_FCT( fd_msg_search_avp ( *msg, ss_origin_host, &avp) );
	if (avp) {
		CHECK_FCT( fd_msg_avp_hdr( avp, &hdr ) );
		printf("'%.*s' \n", (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
	} 
	else 
		printf("no_Origin-Host\n");	
	
	/* Create answer message header from the request */	
	create_answer(msg, &ans, &req);

	/* Set the Origin-Host, Origin-Realm, Result-Code AVPs */
	CHECK_FCT( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1 ) );	

	/* */
	printf("CLA: Response sent\n");
	CHECK_FCT( fd_msg_send( msg, NULL, NULL ) );
	return 0;

	error:
		return EINVAL;
}

/*Call back to handle response when PUR is received*/
int ss_pur_ans_cb(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	struct msg *ans, *req;	
	struct avp *avp, gavp;
	struct avp_hdr * hdr = NULL;
	union avp_value val;
	unsigned32 puaflg = 0;
	char buf[60] = {0};
	char imsi[16] = {0};
	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if (msg == NULL)
		return EINVAL;
	
	/* Value of Origin-Host */
	printf("ECHO PUR received from ");
	CHECK_FCT( fd_msg_search_avp ( *msg, ss_origin_host, &avp) );
	if (avp) {
		CHECK_FCT( fd_msg_avp_hdr( avp, &hdr ) );
		printf("'%.*s' \n", (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
	} 
	else 
		printf("no_Origin-Host\n");

	/* Create answer message header from the request */
	create_answer(msg, &ans, &req);

	/* Connect to the mysql database*/
	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, MYSQL_SERVER, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, 0, NULL, 0)) {
		fprintf(stderr, "mysql db connection failed:%s\n", mysql_error(conn));
		goto error;
	}
	
	/* Extract imsi from request message and query hss database for the user data*/
	CHECK_FCT_DO( fd_msg_search_avp ( req, ss_user_name, &avp), goto error );
	CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
	strncpy(imsi,(char *)hdr->avp_value->os.data,15);
	sprintf(buf,"select * from mme where imsi='%s'", imsi);
	if (mysql_query(conn, buf)) {
		fprintf(stderr, "subscription data query for imsi %s failed %s\n", imsi,mysql_error(conn));
    }
	
	/* Check the result of the query and process it*/
	if((res = mysql_store_result(conn))!=NULL){
		
		/*fetch row*/
		if((row = mysql_fetch_row(res))!= NULL){

			/* Set the Origin-Host, Origin-Realm, Result-Code AVPs */
			CHECK_FCT( fd_msg_rescode_set( ans, "DIAMETER_SUCCESS", NULL, NULL, 1 ) );

			/*Extract the requesting mme host identity from request */
			fd_msg_search_avp ( req, ss_origin_host, avp);	
			CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));

			/*Check if requesing mme is same with registered mme*/
			if(strcmp(row[1],(char *)hdr->avp_value->os.data) == 0){
				
				/*Set UE purged flag in database*/
				memset(buf,0,60);
				sprintf(buf,"update mme set uePurged='UE_PURGED' where imsi='%.15s'",imsi);
				if(mysql_query(conn,buf)){
					fprintf(stderr, "Insert/Update UE_PURGED in mme table failed: %s\n", mysql_error(conn));
				}		
			
				/*Set freeze m-tsmi flag in PUA flags avp*/
				puaflg |= 1U ;
				SS_SET_U32( ss_subsc_data_flgs, &puaflg, ans, avp);
			}
			else
				SS_SET_U32( ss_subsc_data_flgs, &puaflg, ans, avp);
		}
		/* User is unkown*/
		else{
			/*Set 'DIAMETER_ERROR_USER_UNKNOWN' error in Experimental-Result-Code AVP*/
			SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_USER_UNKNOWN,ans);
		}
		
		mysql_free_result(res);
	}
	else{
			/*TODO:QUERY ERROR  :DIAMETER_UNABLE_TO_COMPLY*/
		
		fprintf(stderr, " Query Error %s\n", mysql_error(conn));
		goto error; 
	}

	/* Send the answer */	
	printf("PUA: Response sent\n");
	CHECK_FCT( fd_msg_send( msg, NULL, NULL ) );
	return 0;

	error:
		return EINVAL;
}

/*Call back to handle response when ISR is received*/
/*TODO: this works only for testing*/
int ss_isr_ans_cb(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	struct msg *ans, *req;	
	struct avp *avp, gavp;
	union avp_value val;
	
	if (msg == NULL)
		return EINVAL;
	
	/* Value of Origin-Host */
	printf("ECHO ISR received from ");
	CHECK_FCT( fd_msg_search_avp ( *msg, ss_origin_host, &avp) );
	if (avp) {
		CHECK_FCT( fd_msg_avp_hdr( avp, &hdr ) );
		printf("'%.*s' \n", (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
	} 
	else 
		printf("no_Origin-Host\n");

	/* Create answer message header from the request */
	create_answer(msg, &ans, &req);

	/* Set the Origin-Host, Origin-Realm, Result-Code AVPs */
	CHECK_FCT( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1 ) );	

	/*send isa message*/
	printf("ISA: Response sent\n");
	CHECK_FCT( fd_msg_send( msg, NULL, NULL ) );
	return 0;

	error:
		return EINVAL;
}

/*Call back to handle response when DSR is received*/
/*TODO: this works only for testing*/
int ss_dsr_ans_cb(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	struct msg *ans, *req;	
	struct avp *avp, gavp;
	union avp_value val;
	
	if (msg == NULL)
		return EINVAL;
	
	/* Value of Origin-Host */
	printf("ECHO DSR received from ");
	CHECK_FCT( fd_msg_search_avp ( *msg, ss_origin_host, &avp) );
	if (avp) {
		CHECK_FCT( fd_msg_avp_hdr( avp, &hdr ) );
		printf("'%.*s' \n", (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
	} 
	else 
		printf("no_Origin-Host\n");

	/* Create answer message header from the request */
	create_answer(msg, &ans, &req);

	/* Set the Origin-Host, Origin-Realm, Result-Code AVPs */
	CHECK_FCT( fd_msg_rescode_set( *msg, "DIAMETER_SUCCESS", NULL, NULL, 1 ) );	

	/*send dsa message*/
	printf("DSA: Response sent\n");
	CHECK_FCT( fd_msg_send( msg, NULL, NULL ) );
	return 0;

	error:
		return EINVAL;
}


/*TODO: this works only for testing*/
int ss_pur_ans_cb(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

	struct msg *ans, *req;	
	struct avp *avp, gavp;
	struct avp_hdr * hdr = NULL;
	union avp_value val;
	unsigned32 puaflg = 0;
	char buf[100] = {0};
	char imsi[16] = {0};
	MYSQL *conn = NULL;
	MYSQL_RES *res;
  	MYSQL_ROW row;

	if (msg == NULL)
		return EINVAL;
	
	/* Value of Origin-Host */
	printf("ECHO AIR received from ");
	CHECK_FCT( fd_msg_search_avp ( *msg, ss_origin_host, &avp) );
	if (avp) {
		CHECK_FCT( fd_msg_avp_hdr( avp, &hdr ) );
		printf("'%.*s' \n", (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
	} 
	else 
		printf("no_Origin-Host\n");

	/* Create answer message header from the request */
	create_answer(msg, &ans, &req);

	/* Connect to the mysql database*/
	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, MYSQL_SERVER, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, 0, NULL, 0)) {
		fprintf(stderr, "mysql db connection failed:%s\n", mysql_error(conn));
		goto error;
	}
	
	/* Extract imsi from request message and query hss database for the user data*/
	CHECK_FCT_DO( fd_msg_search_avp ( req, ss_user_name, &avp), goto error );
	CHECK_FCT( fd_msg_avp_hdr( avp, &hdr));
	strncpy(imsi,(char *)hdr->avp_value->os.data,15);
	sprintf(buf,"select * from subscriptionData where imsi='%s'", imsi);
	if (mysql_query(conn, buf)) {
		fprintf(stderr, "subscription data query for imsi %s failed %s\n", imsi,mysql_error(conn));
    }
	
	/* Check the result of the query and process it*/
	if((res = mysql_store_result(conn))!=NULL){
		
		/*fetch row*/
		if((row = mysql_fetch_row(res))!= NULL){
		}
		/* User is unkown*/
		else{
			/*Set 'DIAMETER_ERROR_USER_UNKNOWN' error in Experimental-Result-Code AVP*/
			SET_ORIGIN_AND_EXPER_RESULT(DIAMETER_ERROR_USER_UNKNOWN,ans);
		}
		
		mysql_free_result(res);
	}
	else{
			/*TODO:QUERY ERROR  :DIAMETER_UNABLE_TO_COMPLY*/
		
		fprintf(stderr, " Query Error %s\n", mysql_error(conn));
		goto error; 
	}

	/*send aia message*/
	printf("AIA: Response sent\n");
	CHECK_FCT( fd_msg_send( msg, NULL, NULL ) );
	return 0;

	error:
		return EINVAL;
}
