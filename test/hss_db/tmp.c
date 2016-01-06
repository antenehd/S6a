
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
int ss_air_ans_cb(struct msg ** msg, struct avp * av, struct session * sess, void * opaq, enum disp_action * act){

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
