
#ifndef SS_INTERF_SSIX
#define SS_INTERF_SSIX

#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdcore.h>


/**
Global variable to store configuration file path including filename (eg. "./conf/freed.conf"). It should be set before 'ss_init' function is called. If it is initialized to NULL or not initialized at all the configuration file is should be located in same directory as the excutable code file name should be 'freeDiameter.conf'.
Note: This variable is already defined to a NULL value. 
*/
extern char *ss_diameter_conffile_name;

/** arguments of this typedef data type should be either 'struct avp *' or 'struct msg *' */
typedef void avp_or_msg; 


/**************************************************************************************************************/
/* REGISTER CALL BACK FUNCTIONS THAT WILL BE CALLED WHEN REQUEST MESSAGE IS RECEIVED	                      */
/**************************************************************************************************************/

/**
  (This description about callback funtiotion is directly copied from freediameter 'libfdproto.h' file)
 * Call back functions: 
 * PARAMETERS:
 *  msg 	: the received message on function entry. may be updated to answer on return (see description)
 *  AVP  	: for callbacks registered with DISP_HOW_AVP or DISP_HOW_AVP_ENUMVAL, direct link to the triggering AVP.
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
 *(Description about callback funtions ends here)
 * 
 *
 *Description: Registers a callback function 'cb' that will be call when Update-Location-Request is received. 
  Check the above Call back functions description for detail about the callback function. 	
	@param cb : The callback function to register that is called when ULR message is received 
 	@return 0 : The callback is registered.
  	@return EINVAL : A parameter is invalid.
  	@return ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_cb_ulr(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/**
  Check @see ss_reg_ulr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)) for details about the callback functions

  Registers a callback function 'cb' that will be call when Cancel-Location-Request is received. 
  Check the above Call back functions description for detail about the callback function.
 	
	@param cb : The callback function to register that is called when ULR message is received 
 	@return	0 : The callback is registered.
  	@return	EINVAL : A parameter is invalid.
  	@return	ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_cb_clr(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/**
  Check @see ss_reg_ulr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)) for details about the callback functions

 Registers a callback function 'cb' that will be called when Authentication-Information-Request is received. 
 Check the above Call back functions description for detail about the callback function.
 	
	@param 	cb : The callback function to register that is called when ULR message is received 
 	@return	0 : The callback is registered.
  	@return EINVAL : A parameter is invalid.
  	@return ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_cb_air(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/**
  Check @see ss_reg_ulr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)) for details about the callback functions

 Registers a callback function 'cb' that will be called when Insert-Subscriber-Data-Request is received. 
 Check the above Call back functions description for detail about the callback function.
 	
	@param cb : The callback function to register that is called when ULR message is received 
 	@return	0 : The callback is registered.
  	@return	EINVAL : A parameter is invalid.
  	@return ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_cb_idr(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/**
  Check @see ss_reg_ulr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)) for details about the callback functions

 Registers a callback function 'cb' that will be call when Delete-Subscriber-Data-Request  is received. 
 Check the above Call back functions description for detail about the callback function.
 	
	@param cb : The callback function to register that is called when ULR message is received 
 	@return	0 : The callback is registered.
  	@return EINVAL : A parameter is invalid.
  	@return ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_cb_dsr(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/**
  Check @see ss_reg_ulr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)) for details about the callback functions

 Registers a callback function 'cb' that will be call when  Purge-UE-Request is received. 
 Check Request the above Call back functions description for detail about the callback function.
 	
	@param cb : The callback function to register that is called when ULR message is received 
 	@return	0 : The callback is registered.
  	@return EINVAL : A parameter is invalid.
  	@return ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_cb_pur(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/**
  Check @see ss_reg_ulr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)) for details about the callback functions

 Registers a callback function 'cb' that will be call when Reset-Request  is received. 
 Check the above Call back functions description for detail about the callback function.
 	
	@param cb : The callback function to register that is called when ULR message is received 
 	@return	0 : The callback is registered.
  	@return EINVAL : A parameter is invalid.
  	@return ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_cb_rsr(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/**
  Check @see ss_reg_ulr_cb(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *)) for details about the callback functions

 Registers a callback function 'cb' that will be call when  Notify-Request is received. 
 Check the above Call back functions description for detail about the callback function.
 	
	@param cb : The callback function to register that is called when ULR message is received 
 	@return 0 : The callback is registered.
  	@return EINVAL : A parameter is invalid.
  	@return ENOMEM : Not enough memory to complete the operation
*/
int ss_reg_cb_nor(int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *));

/**	Initializes the diameter protocol.
	It parses the diameter configuration file and initialize global variables based on
	the values in the configration file. It creates a connection with peers
	given in the confguration file. It loads the dictionary that contains the command and AVP definations and rules

	@return 0 : initialized successfuly
    @return 1 (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_init();

/***************************************************************************************************************/
/*		SEND MESSAGE																						   */
/***************************************************************************************************************/

/**
    This functions are defined in freediameter 'libfdcore' and the following description is copied from 'libfdcore.h'
	file of freediamter implementation.

  FUNCTION:	fd_msg_send, fd_msg_send_timeout  
   

   @param pmsg : Location of the message to be sent on the network (set to NULL on function return to avoid double deletion).
   @param anscb	: A callback to be called when corresponding answer is received, when sending a request (not used with answers)
   @param data : opaque data to be passed back to the anscb (or expirecb) when it is called.
 * DESCRIPTION: 
 *   Sends a message on the network. (actually simply queues it in a global queue, to be picked by a daemon's thread)
 * For requests, the end-to-end id must be set (see fd_msg_get_eteid / MSGFL_ALLOC_ETEID).
 * For answers, the message must be created with function fd_msg_new_answer_from_req.
 *
 * The routing module will handle sending to the correct peer, usually based on the Destination-Realm / Destination-Host AVP.
 *
 * If the msg is a request, there are two ways of receiving the answer:
 *  - either having registered a callback in the dispatch module (see fd_disp_register)
 *  - or provide a anscb callback here. If such callback is provided, it is called before the dispatch callbacks.
 *    The prototype for this anscb callback function is:
 *     void anscb(void * data, struct msg ** answer)
 *	where:
 *		data   : opaque data that was registered along with the callback.
 *		answer : location of the pointer to the answer.
 *      note1: on function return, if *answer is not NULL, the message is passed to the dispatch module for regular callbacks.
 *	       otherwise, the callback must take care of freeing the message (fd_msg_free).
 *	note2: the opaque data is not freed by the daemon in any case, extensions should ensure clean handling in fd_ext_fini.
 * 
 * If no callback is registered to handle an answer, the message is discarded and an error is logged.
 *
 *  fd_msg_send_timeout is similar to fd_msg_send, except that it takes two additional arguments "expirecb" and "timeout". 
 * If the message parameter is an answer, there is no difference with fd_msg_send.
 * Otherwise, if the corresponding answer (or error) is received before the timeout date elapses, everything occurs as with fd_msg_send. 
 * Otherwise, the request is removed from the queue (meaning the matching answer will be discarded upon reception) and passed to the expirecb 
 * function. Upon return, if the *msg parameter is not NULL, it is freed (not passed to other callbacks). 
 * expirecb is called in a dedicated thread.
 * 
 *    The prototype for the expirecb callback function is:
 *     void expirecb(void * data, struct peer_hdr * sentto, struct msg ** request)
 *	where:
 *		data   : opaque data that was registered along with the callback.
 *      sentto : pointer to the peer to which the message was sent and no answer received within timeout.(check freediameter 'libfdcore.h' for detail about the structure of the 'struct peer_hdr')
 *		request: location of the pointer to the request that was not answered.
 *
 * RETURN VALUE:
 *  @return 0      	: The message has been queued for sending (sending may fail asynchronously).
 *  @return EINVAL 	: A parameter is invalid (ex: anscb provided but message is not a request).
 *  ...
 */
int fd_msg_send ( struct msg ** pmsg, void (*anscb)(void *, struct msg **), void * data );

/**
    This functions are defined in freediameter 'libfdcore' and the following description is copied from 'libfdcore.h'
	file of freediamter implementation.

  FUNCTION:	fd_msg_send_timeout  
   

   @param pmsg : Location of the message to be sent on the network (set to NULL on function return to avoid double deletion).
   @param anscb	: A callback to be called when corresponding answer is received, when sending a request (not used with answers)
   @param data : opaque data to be passed back to the anscb (or expirecb) when it is called.
   @param expirecb : (only for fd_msg_send_timeout) If the request did not get an answer before timeout, this callback is called.
   @param timeout : (only for fd_msg_send_timeout) sets the absolute time until when to wait for an answer. Past this time,
 *                the expirecb is called with the request and the answer will be discarded if received later.
 *
 * DESCRIPTION: 
 *   Sends a message on the network. (actually simply queues it in a global queue, to be picked by a daemon's thread)
 * For requests, the end-to-end id must be set (see fd_msg_get_eteid / MSGFL_ALLOC_ETEID).
 * For answers, the message must be created with function fd_msg_new_answer_from_req.
 *
 * The routing module will handle sending to the correct peer, usually based on the Destination-Realm / Destination-Host AVP.
 *
 * If the msg is a request, there are two ways of receiving the answer:
 *  - either having registered a callback in the dispatch module (see fd_disp_register)
 *  - or provide a anscb callback here. If such callback is provided, it is called before the dispatch callbacks.
 *    The prototype for this anscb callback function is:
 *     void anscb(void * data, struct msg ** answer)
 *	where:
 *		data   : opaque data that was registered along with the callback.
 *		answer : location of the pointer to the answer.
 *      note1: on function return, if *answer is not NULL, the message is passed to the dispatch module for regular callbacks.
 *	       otherwise, the callback must take care of freeing the message (fd_msg_free).
 *	note2: the opaque data is not freed by the daemon in any case, extensions should ensure clean handling in fd_ext_fini.
 * 
 * If no callback is registered to handle an answer, the message is discarded and an error is logged.
 *
 *  fd_msg_send_timeout is similar to fd_msg_send, except that it takes two additional arguments "expirecb" and "timeout". 
 * If the message parameter is an answer, there is no difference with fd_msg_send.
 * Otherwise, if the corresponding answer (or error) is received before the timeout date elapses, everything occurs as with fd_msg_send. 
 * Otherwise, the request is removed from the queue (meaning the matching answer will be discarded upon reception) and passed to the expirecb 
 * function. Upon return, if the *msg parameter is not NULL, it is freed (not passed to other callbacks). 
 * expirecb is called in a dedicated thread.
 * 
 *    The prototype for the expirecb callback function is:
 *     void expirecb(void * data, struct peer_hdr * sentto, struct msg ** request)
 *	where:
 *		data   : opaque data that was registered along with the callback.
 *      sentto : pointer to the peer to which the message was sent and no answer received within timeout.(check freediameter 'libfdcore.h' for detail about the structure of the 'struct peer_hdr')
 *		request: location of the pointer to the request that was not answered.
 *
 * RETURN VALUE:
 *  @return 0      	: The message has been queued for sending (sending may fail asynchronously).
 *  @return EINVAL 	: A parameter is invalid (ex: anscb provided but message is not a request).
 *  ...
 */
int fd_msg_send_timeout ( struct msg ** pmsg, void (*anscb)(void *, struct msg **), void * data, void (*expirecb)(void *, DiamId_t, size_t, struct msg **), const struct timespec *timeout );

/** Initialize shutdown of the diameter application. This is not blocking. This function is defined in
    freedimeter 'libfdcore' library.

	@return 0 : AVP instance is created (success)
	@return !0 : on failure
*/
int fd_core_shutdown(void);

/**Waites untill the diameter application gracefully shuts down. This function is should be called when the application is shuting down after function fd_core_shutdown is called to reclaim some resources. This function is defined in freedimeter 'libfdcore' library.
	
	@return 0 : AVP instance is created (success)
	@return !0 : on failure
*/
int fd_core_wait_shutdown_complete(void);

/**
   This function adds a Result-Code AVP to a message, and optionally
   - sets the 'E' error flag in the header,
   - adds Error-Message, Error-Reporting-Host and Failed-AVP AVPs.
 
   	 @param msg : A msg object -- it must be an answer.
   	 @param rescode : The name of the returned error code (ex: "DIAMETER_INVALID_AVP")
   	 @param errormsg : (optional) human-readable error message to put in Error-Message AVP
   	 @param optavp : (optional) If provided, the content will be put inside a Failed-AVP
     @param type_id : 0 => nothing; 1 => adds Origin-Host and Origin-Realm with local info. 2=> adds Error-Reporting-Host. 
     @return 0 : Operation complete.
     @return !0 : an error occurred.
*/
int fd_msg_rescode_set( struct msg * msg, char * rescode, char * errormsg, struct avp * optavp, int type_id );


/**************************************************************************************************/
/*			ADD AVPs TO MESSAGE OR GROUP AVP												      */
/**************************************************************************************************/

/**Add AVP to message structure or group AVP. The prupose of this function is to add an AVP of typed grouped to its parent which could be a message or an AVP of typed group. For AVP of type other than a group use the 'ss_set_*' functions to set the value and add it to its parent.

	@param parent: the message structure or group AVP in to which the AVP will be added
	@param	avp: the AVP that is to be added in to the message structure or group AVP.
	@return 0 on success
	@return 1 on failure
*/
int ss_add_avp(avp_or_msg ** parent, struct avp * avp);


/**************************************************************************************************/
/*			 CREATE GROUP AVPs 																	  */
/**************************************************************************************************/

/**Creates a new Terminal-Information AVP instance.

	@param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
	@return 0 on success
	@return 1 on failure
*/
int ss_create_terminal_information(struct avp **gavp);

/**Creates  a new Active-APN AVP instance. 

	@param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
	@return 0 : AVP instance is created (success)
	@return EINVAL 	: A parameter is invalid.
	@return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_active_apn(struct avp **gavp);

/**Creates a new Equivalent-PLMN-List AVP instance.
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return EINVAL 	: A parameter is invalid.
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_equivalent_plmn_list(struct avp **gavp);

/**Creates a new MIP6-Agent-Info AVP instance.
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return EINVAL 	: A parameter is invalid.
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_mip6_agent_info(struct avp **gavp);

/**Creates MIP-Home-Agent-Host AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @@return EINVAL 	: A parameter is invalid.
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_mip_home_agent_host(struct avp **gavp);

/**Creates a new Specific-APN-Info AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_specific_apn_info(struct avp **gavp);

/**Creates a new Experimental-Result AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_experimental_result(struct avp **gavp);

/**Creates a new Subscription-Data AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_subscription_data(struct avp **gavp);

/**Creates a new LCS-Info AVP  instance.
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_lcs_info(struct avp **gavp);

/**Creates a new LCS-PrivacyException AVP instance.
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_lcs_privacyexception(struct avp **gavp);

/**Creates  a new External-Client AVP instance.
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)  
*/
int ss_create_external_client(struct avp **gavp);

/**Creates  a new Service-Type AVP instance.
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_service_type(struct avp **gavp);

/**Creates  a new MO-LR AVP instance.
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_mo_lr(struct avp **gavp);

/**Creates  a new Teleservice-List AVP instance.
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_teleservice_list(struct avp **gavp);

/**Creates  a new Call-Barring-Info AVP instance. 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_call_barring_info(struct avp **gavp);

/**Creates a new AMBR AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_ambr(struct avp **gavp);

/**Creates a new APN-Configuration-Profile AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_apn_configuration_profile(struct avp **gavp);

/**Creates  a new APN-Configuration AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_apn_configuration(struct avp **gavp);

/**Creates  a new EPS-Subscribed-QoS-Profile AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_eps_subscribed_qos_profile(struct avp **gavp);

/**Creates  a new Allocation-Retention-Priority AVP instance  
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_allocation_retention_priority(struct avp **gavp);

/**Creates a new WLAN-offloadability AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_wlan_offloadability(struct avp **gavp);

/**Creates a new Trace-Data AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_trace_data(struct avp **gavp);

/**Creates  a new MDT-Configuration AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_mdt_configuration(struct avp **gavp);

/**Creates  a new Area-Scope AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_area_scope(struct avp **gavp);

/**Creates a new GPRS-Subscription-Data AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_gprs_subscription_data(struct avp **gavp);

/**Creates a new PDP-Context AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_pdp_context(struct avp **gavp);

/**Creates a new CSG-Subscription-Data AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_csg_subscription_data(struct avp **gavp);

/**Creates a new ProSe-Subscription-Data AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_prose_subscription_data(struct avp **gavp);

/**Creates a new Requested-EUTRAN-Authentication-Info AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_requested_eutran_authentication_info(struct avp **gavp);

/**Creates a new Requested-UTRAN-GERAN-Authentication-Info AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_requested_utran_geran_authentication_info(struct avp **gavp);

/**Creates a new Authentication-Info AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_authentication_info(struct avp **gavp);

/**Creates a new E-UTRAN-Vector AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_e_utran_vector(struct avp **gavp);

/**Creates a new UTRAN-Vector AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_utran_vector(struct avp **gavp);

/**Creates  a new GERAN-Vector AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_geran_vector(struct avp **gavp);

/**Creates  a new EPS-User-State AVP instance

  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_eps_user_state(struct avp **gavp);

/**Creates a new MME-User-State AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_mme_user_state(struct avp **gavp);

/**Creates a new EPS-Location-Information AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_eps_location_information(struct avp **gavp);

/**Creates a new MME-Location-Information AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_mme_location_information(struct avp **gavp);

/**Creates  a new User-CSG-Information AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_user_csg_information(struct avp **gavp);

/**Creates  a new Local-Time-Zone AVP instance 
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_local_time_zone(struct avp **gavp);

/**Creates a new Supported-Features AVP instance
	
  @param gavp : a pointer to an AVP structure pointer which will point to the new instance upon successful function return.
  @return 0 : AVP instance is created (success)
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_create_supported_features(struct avp **gavp);


/******************************************************************************************************/
/*		GET GROUP AVPs FROM MESSAGE																	  */	
/******************************************************************************************************/

/**Retrieves Terminal-Information AVP from message
	@param	msg : a pointer to a message structure in which Terminal-Information AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Terminal-Information AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_terminal_information(struct msg *msg, struct avp **gavp);

/**Retrieves the first Active-APN AVP from message
	@param	msg : a pointer to a message structure in which  Active-APN AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Active-APN AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_active_apn(struct msg *msg, struct avp **gavp);

/**Retrieves the next Active-APN AVP next to the given AVP 'avp'
	parameter:
		
	@param	avp : a pointer to Active-APN AVP next to which the next Active-APN AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Active-APN AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_active_apn(struct avp *avp, struct avp **gavp);

/**Retrieves Equivalent-PLMN-List AVP from message
	@param	msg : a pointer to a message structure in which  Equivalent-PLMN-List AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Equivalent-PLMN-List AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_equivalent_plmn_list(struct msg *msg, struct avp **gavp);

/**Retrieves MIP6-Agent-Info AVP from AVP of type grouped.
	@param	msg_avp : a pointer to an AVP of typed grouped in which MIP6-Agent-Info AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to MIP6-Agent-Info AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_mip6_agent_info(avp_or_msg *msg_avp, struct avp **gavp);

/**Retrieves MIP-Home-Agent-Host AVP from AVP of type grouped.
	@param	avp : a pointer to an AVP of typed grouped in which MIP-Home-Agent-Host AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to MIP-Home-Agent-Host AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_mip_home_agent_host(struct avp *avp, struct avp **gavp);

/**Retrieves the first Specific-APN-Info AVP from AVP of type grouped 'avp'
	@param	avp : a pointer to an AVP of typed grouped in which Specific-APN-Info AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Specific-APN-Info AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_specific_apn_info(struct avp *avp, struct avp **gavp);

/**Retrieves the next Specific-APN-Info AVP. 
	@param	avp : a pointer to Specific-APN-Info AVP next to which Specific-APN-Info AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to the next Specific-APN-Info AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_specific_apn_info(struct avp *avp, struct avp **gavp);

/**Retrieves Experimental-Result AVP from message
	@param	msg : a pointer to a message structure in which Experimental-Result AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Experimental-Result AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_experimental_result(struct msg *msg, struct avp **gavp);

/**Retrieves Subscription-Data AVP from message
	@param msg : a pointer to a message structure in which Subscription-Data AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Subscription-Data AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_subscription_data(struct msg *msg, struct avp **gavp);

/**Retrieves LCS-Info AVP from AVP of type grouped 'avp'
	@param avp : a pointer to an AVP of typed grouped in which LCS-Info AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to LCS-Info AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_lcs_info(struct avp *avp, struct avp **gavp);

/**Retrieves the first LCS-PrivacyException AVP from AVP of type grouped 'avp'
	@param avp : a pointer to an AVP of typed grouped in which LCS-PrivacyException AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to LCS-PrivacyException AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_lcs_privacyexception(struct avp *avp, struct avp **gavp);

/**Retrieves the next LCS-PrivacyException AVP.  
	@param avp : a pointer to LCS-PrivacyException AVP next to which LCS-PrivacyException AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to LCS-PrivacyException AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_lcs_privacyexception(struct avp *avp, struct avp **gavp);

/**Retrieves the first External-Client AVP from AVP of type grouped 'avp'
	@param avp : a pointer to an AVP of typed grouped in to which External-Client AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to External-Client AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_external_client(struct avp *avp, struct avp **gavp);

/**Retrieves the next External-Client group AVP 
	@param avp : a pointer to External-Client AVP next to which External-Client AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to External-Client AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_external_client(struct avp *avp, struct avp **gavp);

/**Retrieves the first Service-Type AVP from AVP of type grouped 'avp'
	@param avp : a pointer to an AVP of typed grouped in to which Service-Type AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Service-Type AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_service_type(struct avp *avp, struct avp **gavp);

/**Retrieves the next Service-Type AVP 
	@param avp : a pointer to Service-Type AVP next to which Service-Type AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Service-Type AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_service_type(struct avp *avp, struct avp **gavp);

/**Retrieves the first MO-LR AVP from AVP of type grouped 'avp'
	@param avp : a pointer to an AVP of typed grouped in to which MO-LR AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to MO-LR AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_mo_lr(struct avp *avp, struct avp **gavp);

/**Retrieves the next MO-LR group AVP 
	@param avp : a pointer to MO-LR AVP next to which Service-Type AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Service-Type AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_mo_lr(struct avp *avp, struct avp **gavp);

/**Retrieves the first Teleservice-List AVP from AVP of type grouped
	@param avp : a pointer to an AVP of typed grouped in to which Teleservice-List AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Teleservice-List AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_teleservice_list(struct avp *avp, struct avp **gavp);

/**Retrieves the first Call-Barring-Info AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which Call-Barring-Info AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Call-Barring-Info AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_call_barring_info(struct avp *avp, struct avp **gavp);

/**Retrieves the next Call-Barring-Info AVP 
	@param avp : a pointer to Call-Barring-Info AVP next to which Call-Barring-Info AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Call-Barring-Info AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_call_barring_info(struct avp *avp, struct avp **gavp);

/**Retrieves AMBR AVP from AVP of type grouped 'avp'
	@param avp : a pointer to an AVP of typed grouped in to which AMBR AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to AMBR AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_ambr(struct avp *avp, struct avp **gavp);

/**Retrieves APN-Configuration-Profile AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which APN-Configuration-Profile AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to APN-Configuration-Profile AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_apn_configuration_profile(struct avp *avp, struct avp **gavp);

/**Retrieves the first APN-Configuration AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which APN-Configuration AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to APN-Configuration AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_apn_configuration(struct avp *avp, struct avp **gavp);

/**Retrieves the next APN-Configuration AVP 
	@param avp : a pointer to APN-Configuration AVP next to which APN-Configuration AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to APN-Configuration AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_apn_configuration(struct avp *avp, struct avp **gavp);

/**Retrieves the EPS-Subscribed-QoS-Profile AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which EPS-Subscribed-QoS-Profile AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to EPS-Subscribed-QoS-Profile AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_eps_subscribed_qos_profile(struct avp *avp, struct avp **gavp);

/**Retrieves the Allocation-Retention-Priority AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which Allocation-Retention-Priority AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Allocation-Retention-Priority AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_allocation_retention_priority(struct avp *avp, struct avp **gavp);

/**Retrieves the WLAN-offloadability AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which  WLAN-offloadability AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to  WLAN-offloadability AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_wlan_offloadability(struct avp *avp, struct avp **gavp);

/**Retrieves the first Trace-Data AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which APN-Configuration AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to APN-Configuration AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_trace_data(struct avp *avp, struct avp **gavp);

/**Retrieves the MDT-Configuration AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which MDT-Configuration AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to MDT-Configuration AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_mdt_configuration(struct avp *avp, struct avp **gavp);

/**Retrieves the Area-Scope AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which Area-Scope AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Area-Scope AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_area_scope(struct avp *avp, struct avp **gavp);

/**Retrieves the GPRS-Subscription-Data AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which GPRS-Subscription-Data AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to GPRS-Subscription-Data AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_gprs_subscription_data(struct avp *avp, struct avp **gavp);

/**Retrieves the first PDP-Context AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which PDP-Context AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to PDP-Context AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_pdp_context(struct avp *avp, struct avp **gavp);

/**Retrieves the next PDP-Context group AVP 
	@param avp : a pointer to PDP-Context AVP next to which PDP-Context AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to PDP-Context AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_pdp_context(struct avp *avp, struct avp **gavp);

/**Retrieves the first CSG-Subscription-Data AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which CSG-Subscription-Data AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to CSG-Subscription-Data AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_csg_subscription_data(struct avp *avp, struct avp **gavp);

/**Retrieves the next CSG-Subscription-Data group AVP 
	@param avp : a pointer to CSG-Subscription-Data AVP next to which CSG-Subscription-Data AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to CSG-Subscription-Data AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_csg_subscription_data(struct avp *avp, struct avp **gavp);

/**Retrieves ProSe-Subscription-Data AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which ProSe-Subscription-Data AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to ProSe-Subscription-Data AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_prose_subscription_data(struct avp *avp, struct avp **gavp);

/**Retrieves Requested-EUTRAN-Authentication-Info AVP from a message
	@param msg : a pointer to a message structure in to which Requested-EUTRAN-Authentication-Info AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Requested-EUTRAN-Authentication-Info AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_requested_eutran_authentication_info(struct msg *msg, struct avp **gavp);

/**Retrieves Requested-UTRAN-GERAN-Authentication-Info AVP from a message.
	@param msg : a pointer to an AVP of typed grouped in to which Requested-UTRAN-GERAN-Authentication-Info AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Requested-UTRAN-GERAN-Authentication-Info AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_requested_utran_geran_authentication_info(struct msg *msg, struct avp **gavp);

/**Retrieves Authentication-Info group AVP from message
	@param msg : a pointer to a message structure in to which Authentication-Info AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Authentication-Info AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_authentication_info(struct msg *msg, struct avp **gavp);

/**Retrieves the first E-UTRAN-Vector AVP from AVP of type grouped.
	@param avp : a pointer to an AVP of typed grouped in to which E-UTRAN-Vector AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to E-UTRAN-Vector AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_e_utran_vector(struct avp *avp, struct avp **gavp);

/**Retrieves the next E-UTRAN-Vector group AVP 
	@param avp : a pointer to E-UTRAN-Vector AVP next to which E-UTRAN-Vector AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to E-UTRAN-Vector AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_e_utran_vector(struct avp *avp, struct avp **gavp);

/**Retrieves the first UTRAN-Vector AVP from AVP of type grouped.

	@param avp : a pointer to an AVP of typed grouped in to which UTRAN-Vector AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to UTRAN-Vector AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_utran_vector(struct avp *avp, struct avp **gavp);

/**Retrieves the next UTRAN-Vector group AVP.

	@param avp : a pointer to UTRAN-Vector AVP next to which UTRAN-Vector AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to UTRAN-Vector AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_utran_vector(struct avp *avp, struct avp **gavp);

/**Retrieves the first GERAN-Vector AVP from AVP of type grouped.

	@param avp : a pointer to an AVP of typed grouped in to which GERAN-Vector AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to GERAN-Vector AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_geran_vector(struct avp *avp, struct avp **gavp);

/**Retrieves the next GERAN-Vector AVP.

	@param avp : a pointer to GERAN-Vector AVP next to which GERAN-Vector AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to GERAN-Vector AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_geran_vector(struct avp *avp, struct avp **gavp);

/**Retrievs the EPS-User-State AVP from message.

	@param msg : a pointer to a message structure in to which EPS-User-State AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to EPS-User-State AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_eps_user_state(struct msg *msg, struct avp **gavp);

/**Retrievs the MME-User-State AVP from AVP of type grouped.

	@param avp : a pointer to an AVP of typed grouped in to which EPS-User-State AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to EPS-User-State AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_mme_user_state(struct avp *avp, struct avp **gavp);

/**Retrieves the first EPS-Location-Information AVP from message.

	@param msg : a pointer to a message structure in to which EPS-Location-Information AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to EPS-Location-Information AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_eps_location_information(struct msg *msg, struct avp **gavp);

/**Retrieves the first MME-Location-Information AVP from AVP of type grouped.

	@param avp : a pointer to an AVP of typed grouped in to which MME-Location-Information AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to MME-Location-Information AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_mme_location_information(struct avp *avp, struct avp **gavp);

/**Retrievs the first User-CSG-Information AVP from AVP of type grouped.

	@param avp : a pointer to an AVP of typed grouped in to which User-CSG-Information AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to User-CSG-Information AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_user_csg_information(struct avp *avp, struct avp **gavp);

/**Retrievs the first Local-Time-Zone AVP from message.

	@param msg : a pointer to a message structure in to which Local-Time-Zone AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Local-Time-Zone AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_local_time_zone(struct msg *msg, struct avp **gavp);

/**Retrieves the first Supported-Features AVP from message.

	@param msg : a pointer to a message structure in to which Supported-Features AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Supported-Features AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_supported_features(struct msg *msg, struct avp **gavp);

/**Retrieves the next Supported-Features group AVP next to other Supported-Features AVP.

    @param avp : a pointer to Supported-Features AVP next to which Supported-Features AVP is searched.
	@param gavp : a pointer to an instance of 'struct avp' pointer which will point to Supported-Features AVP upon successful function return.
	@return 0 : The AVP has been found (success)
    @return EINVAL : A parameter is invalid.
    @return ENOENT : No AVP has been found, and *gavp is set to NULL.
*/
int ss_get_gavp_next_supported_features(struct avp *avp, struct avp **gavp);

/***********************************************************************************************************/
/*			CREATE REQUEST AND ANSWER MESSAGE															   */		
/***********************************************************************************************************/

/**Create answer message from a request message and add Vendor-Specific-Application-Id and Auth-Session-State in to the message. It copies the Session-Id from the request. Up on successful function return *msg will point to the answer message. The request message could be accessed by setting *msg to other pointer variable before calling this function.  

	@param msg : a pointer to the request message pointer. it will point to the answer message upon successful function return.
	@return 0 : on success
    @return !0 : on failure
*/
int ss_msg_create_answer(struct msg **msg);

/**Creates Update-Location-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.

  @param req : a pointer to the message structure pointer which will point to the created message upon successful function return.
  @return 0 : message is created (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_msg_create_ulr(struct msg **req);

/**Creates Authentication-Information-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.

  @param req : a pointer to the message structure pointer which will point to the created message upon successful function return.
  @return 0 : message is created (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_msg_create_air(struct msg **req);

/**Creates Cancel-Location-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.

  @param req : a pointer to the message structure pointer which will point to the created message upon successful function return.
  @return 0 : message is created (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_msg_create_clr(struct msg **req);

/**Creates Insert-Subscriber-Data-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.

  @param req : a pointer to the message structure pointer which will point to the created message upon successful function return.
  @return 0 : message is created (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/

int ss_msg_create_idr(struct msg **req);
/**Creates Delete-Subscriber-Data-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.

  @param req : a pointer to the message structure pointer which will point to the created message upon successful function return.
  @return 0 : message is created (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_msg_create_dsr(struct msg **req);

/**Creates Purge-UE-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.

  @param req : a pointer to the message structure pointer which will point to the created message upon successful function return.
  @return 0 : message is created (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_msg_create_pur(struct msg **req);

/**Creates Reset-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.

  @param req : a pointer to the message structure pointer which will point to the created message upon successful function return.
  @return 0 : message is created (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_msg_create_rsr(struct msg **req);

/**Creates Notify-Request message and add a new Session-Id, Vendor-Specific-Application-Id, Auth-Session-State, Origin-Host and Origin-Realm AVP in to the message.

  @param req : a pointer to the message structure pointer which will point to the created message upon successful function return.
  @return 0 : message is created (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_msg_create_nor(struct msg **req);


/*****************************************************************************************************************/
/*					GET REMOTE PEER STATE																		 */
/*****************************************************************************************************************/

/** 
Checks the connection state with remote peer. Only after the connection state is open that S6a messages may be sent to remote peer.

	@param	diam_id : diameter identity of remote peer
	@param	diam_id_len : length of diameter identity

Possible states with remote peer are defined as enumeration:

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
	
  @return 'enum peer_state' values as defined above. This values are defined in freediameter library. 
		  -1 : if peer is invalid/notfound
*/
int ss_peer_state(char * diam_id, size_t diam_id_len);



/******************************************************************************************************************/
/**				SET VALUE OF AVP AND ADD IT TO MESSAGE OR GROUP AVP												 **/
/******************************************************************************************************************/

/**Sets Destination-Host AVP value and add it in to a message structure. This function creates an instance of
   Destination-Host AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg_avp : pointer to the message structure pointer or an AVP of type gruoped where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set 
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_destination_host(avp_or_msg **msg_avp, unsigned char *val, size_t len);

/**Sets Origin-Host AVP value and add it in to message structure. This function creates an instance of
   Origin-Host AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_origin_host(struct msg **msg, unsigned char *val, size_t len);

/**Sets Destination-Realm AVP value and add it in to messagestructure. This function creates an instance of
   Destination-Realm AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg_avp : pointer to the message structure pointer or an AVP of type gruoped where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_destination_realm(avp_or_msg **msg_avp, unsigned char *val, size_t len);

/**Sets Origin-Realm AVP value and add it in to message structure. This function creates an instance of
   Origin-Realm AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_origin_realm(struct msg **msg, unsigned char *val, size_t len);

/**Sets User-Name (imsi) AVP value and add it in to message structure. This function creates an instance of
   User-Name AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_user_name(struct msg **msg, unsigned char *val, size_t len);

/**Sets RAT-Type AVP value and add it in to message  structure. This function creates an instance of
   RAT-Type AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_rat_type(struct msg **msg, int32_t val);

/**Sets ULR-Flags AVP value and add it in to message structure. This function creates an instance of
   ULR-Flags AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ulr_flags(struct msg **msg, uint32_t val);

/**Sets UE-SRVCC-Capability AVP value and add it in to message structure. This function creates an instance of
   UE-SRVCC-Capability AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ue_srvcc_capability(struct msg **msg, int32_t val);

/**Sets Visited-PLMN-Id AVP value and add it in to message structure. This function creates an instance of
   Visited-PLMN-Id AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg_avp : pointer to the message structure pointer or an AVP of typed grouped where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_visited_plmn_id(avp_or_msg **msg_avp, unsigned char *val, size_t len);

/**Sets SGSN-Number AVP value and add it in to message structure. This function creates an instance of
   SGSN-Number AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_sgsn_number(struct msg **msg, unsigned char *val, size_t len);

/**Sets Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP value and add it in to message structure.
   This function creates an instance of Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_homogeneous_support_of_ims_voice_over_ps_sessions(struct msg **msg, int32_t val);

/**Sets GMLC-Address AVP value and add it in to message structure. This function creates an instance of
   GMLC-Address AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_gmlc_address(struct msg **msg, unsigned char *val, size_t len);

/**Sets MME-Number-for-MT-SMS AVP value and add it in to message structure. This function creates an instance of
   MME-Number-for-MT-SMS AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_mme_number_for_mt_sms(struct msg **msg, unsigned char *val, size_t len);

/**Sets SMS-Register-Request AVP value and add it in to message structure. This function creates an instance of
   SMS-Register-Request AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_sms_register_request(struct msg **msg, int32_t val);

/**Sets Coupled-Node-Diameter-ID AVP value and add it in to message structure. This function creates an instance of
   Coupled-Node-Diameter-ID AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_coupled_node_diameter_id(struct msg **msg, unsigned char *val, size_t len);

/**Sets IMEI AVP value and add it in to AVP structure that can contain it. This function creates an instance of IMEI AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_imei(struct avp **avp, unsigned char *val, size_t len);

/**Sets Software-Version AVP value and add it in to AVP structure that can contain it. This function creates an instance of Software-Version AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_software_version(struct avp **avp, unsigned char *val, size_t len);

/**Sets 3GPP2-MEID AVP value and add it in to AVP structure that can contain it. This function creates an instance of 3GPP2-MEID AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_3gpp2_meid(struct avp **avp, unsigned char *val, size_t len);

/**Sets MIP-Home-Agent-Address AVP value and add it in to AVP structure that can contain it. This function creates an instance of MIP-Home-Agent-Address AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_mip_home_agent_address(struct avp **avp, unsigned char *val, size_t len);

/**Sets MIP-Home-Agent-Host AVP value and add it in to AVP structure that can contain it. This function creates an instance of MIP-Home-Agent-Host AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_mip_home_agent_host(struct avp **avp, unsigned char *val, size_t len);

/**Sets Result-Code AVP value and add it to message structure. This function creates an instance of
   SMS-Register-Request AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_result_code(struct msg **msg, uint32_t val);

/**Sets Error-Diagnostic AVP value and add it to message structure. This function creates an instance of
   SMS-Register-Request AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_error_diagnostic(struct msg **msg, int32_t val);

/**Sets ULA-Flags AVP value and add it to message structure. This function creates an instance of
   SMS-Register-Request AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ula_flags(struct msg **msg, uint32_t val);

/**Sets Vendor-Id AVP value and add it in to AVP structure that can contain it. This function creates an instance of Vendor-Id AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_vendor_id(struct avp **avp, uint32_t val);

/**Sets Auth-Application-Id AVP value and add it in to AVP structure that can contain it. This function creates an instance of Auth-Application-Id AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_auth_application_id(struct avp **avp, uint32_t val);

/**Sets Experimental-Result-Code AVP value and add it in to AVP structure that can contain it. This function creates an instance of Experimental-Result-Code AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_experimental_result_code(struct avp **avp, uint32_t val);

/**Sets Subscriber-Status AVP value and add it in to AVP structure that can contain it. This function creates an instance of Subscriber-Status AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_subscriber_status(struct avp **avp, int32_t val);

/**Sets MSISDN AVP value and add it in to AVP structure that can contain it. This function creates an instance of MSISDN AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_msisdn(struct avp **avp, unsigned char *val, size_t len);

/**Sets A-MSISDN AVP value and add it in to AVP structure that can contain it. This function creates an instance of A-MSISDN AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_a_msisdn(struct avp **avp, unsigned char *val, size_t len);

/**Sets STN-SR AVP value and add it in to AVP structure that can contain it. This function creates an instance of STN-SR AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_stn_sr(struct avp **avp, unsigned char *val, size_t len);

/**Sets ICS-Indicator AVP value and add it in to AVP structure that can contain it. This function creates an instance of ICS-Indicator AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ics_indicator(struct avp **avp, int32_t val);

/**Sets Network-Access-Mode AVP value and add it in to AVP structure that can contain it. This function creates an instance of Network-Access-Mode AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_network_access_mode(struct avp **avp, int32_t val);

/**Sets Operator-Determined-Barring AVP value and add it in to AVP structure that can contain it. This function creates an instance of Operator-Determined-Barring AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_operator_determined_barring(struct avp **avp, uint32_t val);

/**Sets HPLMN-ODB AVP value and add it in to AVP structure that can contain it. This function creates an instance of HPLMN-ODB AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_hplmn_odb(struct avp **avp, uint32_t val);

/**Sets Regional-Subscription-Zone-Code AVP value and add it in to AVP structure that can contain it. This function creates an instance of Regional-Subscription-Zone-Code AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_regional_subscription_zone_code(struct avp **avp, unsigned char *val, size_t len);

/**Sets Access-Restriction-Data AVP value and add it in to AVP structure that can contain it. This function creates an instance of Access-Restriction-Data AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_access_restriction_data(struct avp **avp, uint32_t val);

/**Sets APN-OI-Replacement AVP value and add it in to AVP structure that can contain it. This function creates an instance of APN-OI-Replacement AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_apn_oi_replacement(struct avp **avp, unsigned char *val, size_t len);

/**Sets 3GPP-Charging-Characteristics AVP value and add it in to AVP structure that can contain it. This function creates an instance of 3GPP-Charging-Characteristics AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_3gpp_charging_characteristics(struct avp **avp, unsigned char *val, size_t len);

/**Sets RAT-Frequency-Selection-Priority-ID AVP value and add it in to AVP structure that can contain it. This function creates an instance of RAT-Frequency-Selection-Priority-ID AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_rat_frequency_selection_priority_id(struct avp **avp, uint32_t val);

/**Sets Roaming-Restricted-Due-To-Unsupported-Feature AVP value and add it in to AVP structure that can contain it. This function creates an instance of Roaming-Restricted-Due-To-Unsupported-Feature AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_roaming_restricted_unsupported_feature(struct avp **avp, int32_t val);

/**Sets Subscribed-Periodic-RAU-TAU-Timer AVP value and add it in to AVP structure that can contain it. This function creates an instance of Subscribed-Periodic-RAU-TAU-Timer AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_subscribed_periodic_rau_tau_timer(struct avp **avp, uint32_t val);

/**Sets MPS-Priority AVP value and add it in to AVP structure that can contain it. This function creates an instance of MPS-Priority AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_mps_priority(struct avp **avp, uint32_t val);

/**Sets VPLMN-LIPA-Allowed AVP value and add it in to AVP structure that can contain it. This function creates an instance of VPLMN-LIPA-Allowed AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_vplmn_lipa_allowed(struct avp **avp, int32_t val);

/**Sets Relay-Node-Indicator AVP value and add it in to AVP structure that can contain it. This function creates an instance of Relay-Node-Indicator AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_relay_node_indicator(struct avp **avp, int32_t val);

/**Sets MDT-User-Consent AVP value and add it in to AVP structure that can contain it. This function creates an instance of MDT-User-Consent AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_mdt_user_consent(struct avp **avp, int32_t val);

/**Sets Subscribed-VSRVCC AVP value and add it in to AVP structure that can contain it. This function creates an instance of Subscribed-VSRVCC AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_subscribed_vsrvcc(struct avp **avp, int32_t val);

/**Sets Subscription-Data-Flags AVP value and add it in to AVP structure that can contain it. This function creates an instance of Subscription-Data-Flags AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_subscription_data_flags(struct avp **avp, uint32_t val);

/**Sets Multiple GMLC-Number AVPs value and add it in to AVP structure that can contain it. This function creates an instance of Multiple GMLC-Number AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_gmlc_number(struct avp **avp, unsigned char *val, size_t len);

/**Sets SS-Code AVP value and add it in to AVP structure that can contain it. This function creates an instance of SS-Code AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg_avp : pointer to an AVP of type grouped pointer or pointer to a message structure pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ss_code(avp_or_msg **msg_avp, unsigned char *val, size_t len);

/**Sets SS-Status AVP value and add it in to AVP structure that can contain it. This function creates an instance of SS-Status AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ss_status(struct avp **avp, unsigned char *val, size_t len);

/**Sets Notification-To-UE-User AVP value and add it in to AVP structure that can contain it. This function creates an instance of Notification-To-UE-User AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_notification_ue_user(struct avp **avp, int32_t val);

/**Sets Client-Identity AVP value and add it in to AVP structure that can contain it. This function creates an instance of Client-Identity AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_client_identity(struct avp **avp, unsigned char *val, size_t len);

/**Sets GMLC-Restriction AVP value and add it in to AVP structure that can contain it. This function creates an instance of GMLC-Restriction AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_gmlc_restriction(struct avp **avp, int32_t val);

/**Sets PLMN-Client AVP value and add it in to AVP structure that can contain it. This function creates an instance of PLMN-Client AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_plmn_client(struct avp **avp, int32_t val);

/**Sets ServiceTypeIdentity AVP value and add it in to AVP structure that can contain it. This function creates an instance of ServiceTypeIdentity AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_serviceTypeIdentity(struct avp **avp, uint32_t val);

/**Sets TS-Code AVPs value and add it in to AVP structure or message sturcture that can contain it. This function creates an instance of TS-Code AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg_avp : pointer to an AVP of type grouped pointer message structure pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ts_code(avp_or_msg **msg_avp, unsigned char *val, size_t len);

/**Sets Max-Requested-Bandwidth-UL AVP value and add it in to AVP structure that can contain it. This function creates an instance of Max-Requested-Bandwidth-UL AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_max_requested_bandwidth_ul(struct avp **avp, uint32_t val);

/**Sets Max-Requested-Bandwidth-DL AVP value and add it in to AVP structure that can contain it. This function creates an instance of Max-Requested-Bandwidth-DL AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_max_requested_bandwidth_dl(struct avp **avp, uint32_t val);

/**Sets All-APN-Configurations-Included-Indicator AVP value and add it in to AVP structure that can contain it. This function creates an instance of All-APN-Configurations-Included-Indicator AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_all_apn_configuration_included_indicator(struct avp **avp, int32_t val);

/**Sets PDN-Type AVP value and add it in to AVP structure that can contain it. This function creates an instance of PDN-Type AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_pdn_type(struct avp **avp, int32_t val);

/**Sets VPLMN-Dynamic-Address-Allowed AVP value and add it in to AVP structure that can contain it. This function creates an instance of VPLMN-Dynamic-Address-Allowed AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_vplmn_dynamic_address_allowed(struct avp **avp, int32_t val);

/**Sets PDN-GW-Allocation-Type AVP value and add it in to AVP structure that can contain it. This function creates an instance of PDN-GW-Allocation-Type AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_pdn_gw_allocation_type(struct avp **avp, int32_t val);

/**Sets SIPTO-Permission AVP value and add it in to AVP structure that can contain it. This function creates an instance of SIPTO-Permission AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_sipto_permission(struct avp **avp, int32_t val);

/**Sets LIPA-Permission AVP value and add it in to AVP structure that can contain it. This function creates an instance of LIPA-Permission AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_lipa_permission(struct avp **avp, int32_t val);

/**Sets Restoration-Priority AVP value and add it in to AVP structure that can contain it. This function creates an instance of Restoration-Priority AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_restoration_priority(struct avp **avp, uint32_t val);

/**Sets SIPTO-Local-Network-Permission AVP value and add it in to AVP structure that can contain it. This function creates an instance of SIPTO-Local-Network-Permission AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_sipto_local_network_permission(struct avp **avp, int32_t val);

/**Sets Served-Party-IP-Address AVP values and add it in to AVP structure that can contain it. This function creates an instance of Served-Party-IP-Address AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_served_party_ip_address(struct avp **avp, unsigned char *val, size_t len);

/**Sets QoS-Class-Identifier AVP value and add it in to AVP structure that can contain it. This function creates an instance of QoS-Class-Identifier AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_qos_class_identifier(struct avp **avp, int32_t val);

/**Sets Priority-Level AVP value and add it in to AVP structure that can contain it. This function creates an instance of Priority-Level AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_priority_level(struct avp **avp, uint32_t val);

/**Sets Pre-emption-Capability AVP value and add it in to AVP structure that can contain it. This function creates an instance of Pre-emption-Capability AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_pre_emption_capability(struct avp **avp, int32_t val);

/**Sets Pre-emption-Vulnerability AVP value and add it in to AVP structure that can contain it. This function creates an instance of Pre-emption-Vulnerability AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_pre_emption_vulnerability(struct avp **avp, int32_t val);

/**Sets WLAN-offloadability-EUTRAN AVP value and add it in to AVP structure that can contain it. This function creates an instance of WLAN-offloadability-EUTRAN AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_wlan_offloadability_eutran(struct avp **avp, uint32_t val);

/**Sets WLAN-offloadability-UTRAN AVP value and add it in to AVP structure that can contain it. This function creates an instance of WLAN-offloadability-UTRAN AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_wlan_offloadability_utran(struct avp **avp, uint32_t val);

/**Sets Trace-Reference AVP value and add it in to AVP structure or message structure that can contain it. This function creates an instance of Trace-Reference AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg_avp : pointer to an AVP of type grouped pointer or message structure pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_trace_reference(avp_or_msg **msg_avp, unsigned char *val, size_t len);

/**Sets Trace-Depth AVP value and add it in to AVP structure that can contain it. This function creates an instance of Trace-Depth AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_trace_depth(struct avp **avp, int32_t val);

/**Sets Trace-NE-Type-List AVP value and add it in to AVP structure that can contain it. This function creates an instance of Trace-NE-Type-List AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_trace_ne_type_list(struct avp **avp, unsigned char *val, size_t len);

/**Sets Trace-Interface-List AVP value and add it in to AVP structure that can contain it. This function creates an instance of Trace-Interface-List AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_trace_interface_list(struct avp **avp, unsigned char *val, size_t len);

/**Sets Trace-Event-List AVP value and add it in to AVP structure that can contain it. This function creates an instance of Trace-Event-List AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_trace_event_list(struct avp **avp, unsigned char *val, size_t len);

/**Sets OMC-Id AVP value and add it in to AVP structure that can contain it. This function creates an instance of OMC-Id AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_omc_id(struct avp **avp, unsigned char *val, size_t len);

/**Sets Trace-Collection-Entity AVP value and add it in to AVP structure that can contain it. This function creates an instance of Trace-Collection-Entity AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_trace_collection_entity(struct avp **avp, unsigned char *val, size_t len);

/**Sets Job-Type AVP value and add it in to AVP structure that can contain it. This function creates an instance of Job-Type AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_job_type(struct avp **avp, int32_t val);

/**Sets Cell-Global-Identity AVP values and add it in to AVP structure that can contain it. This function creates an instance of Cell-Global-Identity AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_cell_global_identity(struct avp **avp, unsigned char *val, size_t len);

/**Sets E-UTRAN-Cell-Global-Identity AVP values and add it in to AVP structure that can contain it. This function creates an instance of E-UTRAN-Cell-Global-Identity AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_e_utran_cell_global_identity(struct avp **avp, unsigned char *val, size_t len);

/**Sets Routing-Area-Identity AVP values and add it in to AVP structure that can contain it. This function creates an instance of Routing-Area-Identity AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_routing_area_identity(struct avp **avp, unsigned char *val, size_t len);

/**Sets Location-Area-Identity AVP values add it in to AVP structure that can contain it. This function creates an instance of Location-Area-Identity AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_location_area_identity(struct avp **avp, unsigned char *val, size_t len);

/**Sets Tracking-Area-Identity AVP values and add it in to AVP structure that can contain it. This function creates an instance of Tracking-Area-Identity AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_tracking_area_identity(struct avp **avp, unsigned char *val, size_t len);

/**Sets List-Of-Measurements AVP value and add it in to AVP structure that can contain it. This function creates an instance of List-Of-Measurements AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_list_of_measurements(struct avp **avp, uint32_t val);

/**Sets Reporting-Trigger AVP value and add it in to AVP structure that can contain it. This function creates an instance of Reporting-Trigger AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_reporting_trigger(struct avp **avp, uint32_t val);

/**Sets Report-Interval AVP value and add it in to AVP structure that can contain it. This function creates an instance of Report-Interval AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_report_interval(struct avp **avp, int32_t val);

/**Sets Report-Amount AVP value and add it in to AVP structure that can contain it. This function creates an instance of Report-Amount AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_report_amount(struct avp **avp, int32_t val);

/**Sets Event-Threshold-RSRP AVP value and add it in to AVP structure that can contain it. This function creates an instance of Event-Threshold-RSRP AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_event_threshold_rsrp(struct avp **avp, uint32_t val);

/**Sets Event-Threshold-RSRQ AVP value and add it in to AVP structure that can contain it. This function creates an instance of Event-Threshold-RSRQ AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_event_threshold_rsrq(struct avp **avp, uint32_t val);

/**Sets Logging-Interval AVP value and add it in to AVP structure that can contain it. This function creates an instance of Logging-Interval AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_logging_interval(struct avp **avp, int32_t val);

/**Sets Logging-Duration AVP value and add it in to AVP structure that can contain it. This function creates an instance of Logging-Duration AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_logging_duration(struct avp **avp, int32_t val);

/**Sets Measurement-Period-LTE AVP value and add it in to AVP structure that can contain it. This function creates an instance of Measurement-Period-LTE AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_measurement_period_lte(struct avp **avp, int32_t val);

/**Sets Measurement-Period-UMTS AVP value and add it in to AVP structure that can contain it. This function creates an instance of Measurement-Period-UMTS AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_measurement_period_umts(struct avp **avp, int32_t val);

/**Sets Collection-Period-RRM-LTE AVP value and add it in to AVP structure that can contain it. This function creates an instance of Collection-Period-RRM-LTE AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_collection_period_rrm_lte(struct avp **avp, int32_t val);

/**Sets Collection-Period-RRM-UMTS AVP value and add it in to AVP structure that can contain it. This function creates an instance of Collection-Period-RRM-UMTS AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_collection_period_rrm_umts(struct avp **avp, int32_t val);

/**Sets Positioning-Method AVP value and add it in to AVP structure that can contain it. This function creates an instance of Positioning-Method AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_positioning_method(struct avp **avp, unsigned char *val, size_t len);

/**Sets Measurement-Quantity AVP value and add it in to AVP structure that can contain it. This function creates an instance of Measurement-Quantity AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_measurement_quantity(struct avp **avp, unsigned char *val, size_t len);

/**Sets Event-Threshold-Event-1F AVP value and add it in to AVP structure that can contain it. This function creates an instance of Event-Threshold-Event-1F AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_event_threshold_event_1f(struct avp **avp, int32_t val);

/**Sets Event-Threshold-Event-1I AVP value and add it in to AVP structure that can contain it. This function creates an instance of Event-Threshold-Event-1I AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_event_threshold_event_1i(struct avp **avp, int32_t val);

/**Sets MDT-Allowed-PLMN-Id AVP value and add it in to AVP structure that can contain it. This function creates an instance of MDT-Allowed-PLMN-Id AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_mdt_allowed_plmn_id(struct avp **avp, unsigned char *val, size_t len);

/**Sets Complete-Data-List-Included-Indicator AVP value and add it in to AVP structure that can contain it. This function creates an instance of Complete-Data-List-Included-Indicator AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_complete_data_list_included_indicator(struct avp **avp, int32_t val);

/**Sets PDP-Type AVP value and add it in to AVP structure that can contain it. This function creates an instance of PDP-Type AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_pdp_type(struct avp **avp, unsigned char *val, size_t len);

/**Sets PDP-Address AVP value and add it in to AVP structure that can contain it. This function creates an instance of PDP-Address AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_pdp_address(struct avp **avp, unsigned char *val, size_t len);

/**Sets QoS-Subscribed AVP value and add it in to AVP structure that can contain it. This function creates an instance of QoS-Subscribed AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_qos_subscribed(struct avp **avp, unsigned char *val, size_t len);

/**Sets Ext-PDP-Type AVP value and add it in to AVP structure that can contain it. This function creates an instance of Ext-PDP-Type AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ext_pdp_type(struct avp **avp, unsigned char *val, size_t len);

/**Sets Ext-PDP-Address AVP value and add it in to AVP structure that can contain it. This function creates an instance of Ext-PDP-Address AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ext_pdp_address(struct avp **avp, unsigned char *val, size_t len);

/**Sets CSG-Id AVP value and add it in to AVP structure that can contain it. This function creates an instance of Ext-CSG-Id AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_csg_id(struct avp **avp, uint32_t val);

/**Sets Expiration-Date AVP value and add it in to AVP structure that can contain it. This function creates an instance of Expiration-Date AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_expiration_date(struct avp **avp, unsigned char *val, size_t len);

/**Sets ProSe-Permission AVP value and add it in to AVP structure that can contain it. This function creates an instance of ProSe-Permission AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_prose_permission(struct avp **avp, uint32_t val);

/**Sets Reset-ID AVP value and add it in to AVP structure that can contain it. This function creates an instance of Reset-ID AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to a message structure pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_reset_id(struct msg **msg, unsigned char *val, size_t len);

/**Sets Number-Of-Requested-Vectors AVP value and add it in to AVP structure that can contain it. This function creates an instance of Number-Of-Requested-Vectors AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_number_of_requested_vectors(struct avp **avp, uint32_t val);

/**Sets Immediate-Response-Preferred AVP value and add it in to AVP structure that can contain it. This function creates an instance of Immediate-Response-Preferred AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_immediate_response_preferred(struct avp **avp, uint32_t val);

/**Sets Re-synchronization-Info AVP value and add it in to AVP structure that can contain it. This function creates an instance of Re-synchronization-Info AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_re_synchronization_info(struct avp **avp, unsigned char *val, size_t len);

/**Sets Item-Number AVP value and add it in to AVP structure that can contain it. This function creates an instance of Item-Number AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_item_number(struct avp **avp, uint32_t val);

/**Sets RAND AVP value and add it to in to AVP structure that can contain it. This function creates an instance of RAND AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_rand(struct avp **avp, unsigned char *val, size_t len);

/**Sets XRES AVP value and add it to in to AVP structure that can contain it. This function creates an instance of XRES AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_xres(struct avp **avp, unsigned char *val, size_t len);

/**Sets AUTN AVP value and add it in to AVP structure that can contain it. This function creates an instance of AUTN AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_autn(struct avp **avp, unsigned char *val, size_t len);

/**Sets KASME AVP value and add it in to AVP structure that can contain it. This function creates an instance of KASME AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_kasme(struct avp **avp, unsigned char *val, size_t len);

/**Sets Confidentiality-Key AVP value and add it in to AVP structure that can contain it. This function creates an instance of Confidentiality-Key AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_confidentiality_key(struct avp **avp, unsigned char *val, size_t len);

/**Sets Integrity-Key AVP value and add it in to AVP structure that can contain it. This function creates an instance of Integrity-Key AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_integrity_key(struct avp **avp, unsigned char *val, size_t len);

/**Sets Kc AVP value and add it in to AVP structure that can contain it. This function creates an instance of Kc AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_kc(struct avp **avp, unsigned char *val, size_t len);

/**Sets SRES AVP value and add it in to AVP structure that can contain it. This function creates an instance of SRES AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_sres(struct avp **avp, unsigned char *val, size_t len);

/**Sets Cancellation-Type AVP value and add it in to message structure. This function creates an instance of
   Cancellation-Type AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_cancellation_type(struct msg **msg, int32_t val);

/**Sets CLR-Flags AVP value and add it in to message structure. This function creates an instance of
   CLR-Flags AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_clr_flags(struct msg **msg, uint32_t val);

/**Sets IDR-Flags AVP value and add it in to message structure. This function creates an instance of
   IDR-Flags AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_idr_flags(struct msg **msg, uint32_t val);

/**Sets IMS-Voice-Over-PS-Sessions-Supported AVP value and add it in to message structure. This function creates an instance of IMS-Voice-Over-PS-Sessions-Supported AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ims_voice_over_ps_sessions_supported(struct msg **msg, int32_t val);

/**Sets Last-UE-Activity-Time AVP value and add it in to message structure. This function creates an instance of Last-UE-Activity-Time AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_last_ue_activity_time(struct msg **msg, unsigned char *val, size_t len);

/**Sets IDA-Flags AVP value and add it in to message structure. This function creates an instance of IDA-Flags AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ida_flags(struct msg **msg, uint32_t val);

/**Sets User-State AVP value and add it in to AVP structure that can contain it. This function creates an instance of User-State AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_user_state(struct avp **avp, int32_t val);

/**Sets Geographical-Information AVP value and add it in to AVP structure that can contain it. This function creates an instance of Geographical-Information AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_geographical_information(struct avp **avp, unsigned char *val, size_t len);

/**Sets Geodetic-Information AVP value and add it in to AVP structure that can contain it. This function creates an instance of Geodetic-Information AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_geodetic_information(struct avp **avp, unsigned char *val, size_t len);

/**Sets Current-Location-retrieved AVP value and add it in to AVP structure that can contain it. This function creates an instance of Current-Location-retrieved AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_current_location_retrieved(struct avp **avp, int32_t val);

/**Sets Age-Of-Location-Information AVP value and add it in to AVP structure that can contain it. This function creates an instance of Age-Of-Location-Information AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_age_of_location_information(struct avp **avp, uint32_t val);

/**Sets CSG-Access-Mode AVP value and add it in to AVP structure that can contain it. This function creates an instance of CSG-Access-Mode AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_csg_access_mode(struct avp **avp, int32_t val);

/**Sets CSG-Membership-Indication AVP value and add it in to AVP structure that can contain it. This function creates an instance of CSG-Membership-Indication AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_csg_membership_indication(struct avp **avp, int32_t val);

/**Sets Time-Zone AVP value and add it in to AVP structure that can contain it. This function creates an instance of Time-Zone AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_time_zone(struct avp **avp, unsigned char *val, size_t len);

/**Sets Daylight-Saving-Time AVP value and add it in to AVP structure that can contain it. This function creates an instance of Daylight-Saving-Time AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_daylight_saving_time(struct avp **avp, int32_t val);

/**Sets DSR-Flags AVP value and add it in to message structure. This function creates an instance of DSR-Flags AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_dsr_flags(struct msg **msg, uint32_t val);

/**Sets Context-Identifier AVP value and add it in to message or group AVP structure. This function creates an instance of Context-Identifier AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg_avp : pointer to the message structure pointer or AVP of type grouped where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_context_identifier(avp_or_msg **msg_avp, uint32_t val);

/**Sets DSA-Flags AVP value and add it in to message structure. This function creates an instance of DSA-Flags AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_dsa_flags(struct msg **msg, uint32_t val);

/**Sets PUR-Flags AVP value and add it in to message structure. This function creates an instance of PUR-Flags AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_pur_flags(struct msg **msg, uint32_t val);

/**Sets PUA-Flags AVP value and add it in to message structure. This function creates an instance of PUA-Flags AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_pua_flags(struct msg **msg, uint32_t val);

/**Sets multiple User-Id AVPs value and add it in to message structure. This function creates an instance of User-Id AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_user_id(struct msg **msg, unsigned char *val, size_t len);

/**Sets Visited-Network-Identifier AVP value and add it in to message structure. This function creates an instance of Visited-Network-Identifier AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg_avp : pointer to the message structure pointer or an AVP of typed grouped where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_visited_network_identifier(avp_or_msg **msg_avp, unsigned char *val, size_t len);

/**Sets Service-Selection AVP value and add it in to message structure. This function creates an instance of Service-Selection AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg_avp : pointer to the message structure pointer or an AVP of typed grouped where the AVP will be added after being set
  @param val: the value to be set
  @param len: length, in bytes, of the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_service_selection(avp_or_msg **msg_avp, unsigned char *val, size_t len);

/**Sets Alert-Reason AVP value and add it in to message structure. This function creates an instance of Alert-Reason AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_alert_reason(struct msg **msg, int32_t val);

/**Sets NOR-Flags AVP value and add it in to message structure. This function creates an instance of NOR-Flags AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_nor_flags(struct msg **msg, uint32_t val);

/**Sets IMS-Voice-Over-PS-Sessions-Supported AVP value and add it in to message structure. This function creates an instance of IMS-Voice-Over-PS-Sessions-Supported AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_ims_voice_over_ps_sessions_supported(struct msg **msg,  int32_t val);

/**Sets Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP value and add it in to message structure. This function creates an instance of Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP and set the given value in to it and add the AVP into the given message structure.

  @param msg : pointer to the message structure pointer where the AVP will be added after being set
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_homogeneous_support_ims_vop_sessions(struct msg **msg, int32_t val);

/**Sets Feature-List-ID  AVP value and add it in to AVP structure that can contain it. This function creates an instance of Feature-List-ID AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_feature_list_id(struct avp **avp, uint32_t val);

/**Sets Feature-List  AVP value and add it in to AVP structure that can contain it. This function creates an instance of Feature-List AVP and set the given value in to it and add the AVP into the given message structure.

  @param avp : pointer to an AVP of type grouped pointer where the AVP will be added after being set.
  @param val: the value to be set
  @return 0 : AVP value is set and AVP is added (success)
  @return EINVAL : invalid parameter
  @return (other standard errors may be returned, too, with their standard meaning. Example:
      ENOMEM 	: Memory allocation for the new object element failed.)
*/
int ss_set_feature_list(struct avp **avp, uint32_t val);



/*****************************************************************************************************************/
/*					RETRIEVE AVP VALUE																			 */
/*****************************************************************************************************************/

/**Retrieves Destination-Host AVP value(diameter id) from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  Destination-Host AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_destination_host_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves Destination-Host AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of typed grouped which contains  Destination-Host AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_destination_host(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Origin-Host AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  Origin-Host AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_origin_host_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves Destination-Realm AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  Destination-Realm AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_destination_realm_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves Origin-Realm AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  Origin-Realm AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_origin_realm_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves Destination-Realm AVP value from group Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of typed grouped which contains  Destination-Realm AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_destination_realm(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves User-Name (imsi) AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  User-Name AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_user_name_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves RAT-Type AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  RAT-Type AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_rat_type_msg(struct msg *msg, int32_t *val);

/**Retrieves ULR-Flags AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  ULR-Flags AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_ulr_flags_msg(struct msg *msg, uint32_t *val);

/**Retrieves UE-SRVCC-Capability AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  UE-SRVCC-Capability AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_ue_srvcc_capability_msg(struct msg *msg, int32_t *val);

/**Retrieves Visited-PLMN-Id AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  Visited-PLMN-Id AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_visited_plmn_id_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves SGSN-Number AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  ULR-Flags AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_sgsn_number_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves GMLC-Address AVP value from message . Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  GMLC-Address AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_gmlc_address_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves MME-Number-for-MT-SMS AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  MME-Number-for-MT-SMS AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found an its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_mme_number_for_mt_sms_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves SMS-Register-Request AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  SMS-Register-Request AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_sms_register_request_msg(struct msg *msg, int32_t *val);

/**Retrieves Coupled-Node-Diameter-ID AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains  Coupled-Node-Diameter-ID AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_coupled_node_diameter_id_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves IMEI AVP value from AVP of type grouped. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains IMEI AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_imei(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Software-Version AVP value from AVP of type grouped. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Software-Version AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_software_version(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves 3gpp2-meid AVP value from AVP of type grouped. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains 3gpp2-meid AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_3gpp2_meid(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Context-Identifier AVP value from AVP of type grouped. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Context-Identifier AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_context_identifier(struct avp *gavp, uint32_t *val);

/**Retrieves Service-Selection AVP value from AVP of type grouped. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Service-Selection AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_service_selection(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves multiple Service-Selection AVPs' values from AVP of type grouped. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple Service-Selection AVPs.
  @param array_ret : the values will be saved in **array_ret. 
  @param len : the lengths, in bytes, of the values will be saved in *len.
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_service_selection_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves Visited-Network-Identifier AVP value from AVP of type grouped. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Visited-Network-Identifier AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_visited_network_identifier(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves multiple MIP-Home-Agent-Address AVPs' values from group AVP. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple MIP-Home-Agent-Address AVPs.
  @param array_ret : the values will be saved in **array_ret.  
  @param len : the lengths, in bytes, of the values will be saved in *len.
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_mip_home_agent_address_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves Visited-PLMN-Id AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Visited-PLMN-Id AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_visited_plmn_id(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves multiple Visited-PLMN-Id AVPs' values from group AVP. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple Visited-PLMN-Id AVPs.
  @param array_ret : the values will be saved in **array_ret.  
  @param len : the lengths, in bytes, of the values will be saved in *len.
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_visited_plmn_id_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves Result-Code AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains Result-Code AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_result_code_msg(struct msg *msg, uint32_t *val);

/**Retrieves Error-Diagnostic AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains Error-Diagnostic AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_error_diagnostic_msg(struct msg *msg, int32_t *val);

/**Retrieves ULA-Flags AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains ULA-Flags AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_ula_flags_msg(struct msg *msg, uint32_t *val);

/**Retrieves Vendor-Id AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Vendor-Id AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_vendor_id(struct avp *gavp, uint32_t *val);

/**Retrieves Experimental-Result-Code AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Experimental-Result-Code AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_experimental_result_code(struct avp *gavp, uint32_t *val);

/**Retrieves Subscriber-Status AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Subscriber-Status AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_subscriber_status(struct avp *gavp, int32_t *val);

/**Retrieves MSISDN AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains MSISDN AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_msisdn(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves A-MSISDN AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains A-MSISDN AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_a_msisdn(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves STN-SR AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains STN-SR AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_stn_sr(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves ICS-Indicator AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains ICS-Indicator AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_ics_indicator(struct avp *gavp, int32_t *val);

/**Retrieves Network-Access-Mode AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Network-Access-Mode AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_network_access_mode(struct avp *gavp, int32_t *val);

/**Retrieves Operator-Determined-Barring AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Operator-Determined-Barring AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_operator_determined_barring(struct avp *gavp, uint32_t *val);

/**Retrieves HPLMN-ODB AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains HPLMN-ODB AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_hplmn_odb(struct avp *gavp, uint32_t *val);

/**Retrieves Regional-Subscription-Zone-Code AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Regional-Subscription-Zone-Code AVP.
  @param array_ret : the values will be saved in **array_ret.  
  @param len : the lengths, in bytes, of the values will be saved in *len.
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_regional_subscription_zone_code_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves Access-Restriction-Data AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Access-Restriction-Data AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_access_restriction_data(struct avp *gavp, uint32_t *val);

/**Retrieves APN-OI-Replacement AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains APN-OI-Replacement AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_apn_oi_replacement(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves 3GPP-Charging-Characteristics AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains 3GPP-Charging-Characteristics AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_3gpp_charging_characteristics(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves RAT-Frequency-Selection-Priority-ID AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains RAT-Frequency-Selection-Priority-ID AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_rat_frequency_selection_priority_id(struct avp *gavp, uint32_t *val);

/**Retrieves Roaming-Restricted-Due-To-Unsupported-Feature AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Roaming-Restricted-Due-To-Unsupported-Feature AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_roaming_restricted_unsupported_feature(struct avp *gavp, int32_t *val);

/**Retrieves Subscribed-Periodic-RAU-TAU-Timer AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Subscribed-Periodic-RAU-TAU-Timer AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_subscribed_periodic_rau_tau_timer(struct avp *gavp, uint32_t *val);

/**Retrieves MPS-Priority AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains MPS-Priority AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_mps_priority(struct avp *gavp, uint32_t *val);

/**Retrieves VPLMN-LIPA-Allowed AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains VPLMN-LIPA-Allowed AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_vplmn_lipa_allowed(struct avp *gavp, int32_t *val);

/**Retrieves Relay-Node-Indicator AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Relay-Node-Indicator AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_relay_node_indicator(struct avp *gavp, int32_t *val);

/**Retrieves MDT-User-Consent AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains MDT-User-Consent AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_mdt_user_consent(struct avp *gavp, int32_t *val);

/**Retrieves Subscribed-VSRVCC AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Subscribed-VSRVCC AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_subscribed_vsrvcc(struct avp *gavp, int32_t *val);

/**Retrieves Subscription-Data-Flags AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Subscription-Data-Flags AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_subscription_data_flags(struct avp *gavp, uint32_t *val);

/**Retrieves multiple GMLC-Number AVPs value from group AVP . Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple GMLC-Number AVPs.
  @param array_ret : the values will be saved in **array_ret.  
  @param len : the lengths, in bytes, of the values will be saved in *len.
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_gmlc_number_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves SS-Code AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains SS-Code AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_ss_code(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves SS-Status AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains SS-Status AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_ss_status(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Notification-To-UE-User AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Notification-To-UE-User AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_notification_ue_user(struct avp *gavp, int32_t *val);

/**Retrieves Client-Identity AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Client-Identity AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_client_identity(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves GMLC-Restriction AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains GMLC-Restriction AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_gmlc_restriction(struct avp *gavp, int32_t *val);

/**Retrieves multiple PLMN-Client AVPs value from group AVP. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the *array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple PLMN-Client AVPs.
  @param array_ret : the values will be saved in *array_ret. 
  @param array_size : the number of values written to *array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to *array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_plmn_client_gavp_array(struct avp *gavp, int32_t **array_ret, size_t *array_size);

/**Retrieves ServiceTypeIdentity AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains ServiceTypeIdentity AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_serviceTypeIdentity(struct avp *gavp, uint32_t *val);

/**Retrieves multiple TS-Code AVPs value from group AVP. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple TS-Code AVPs.
  @param array_ret : the values will be saved in **array_ret.  
  @param len : the lengths, in bytes, of the values will be saved in *len.
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_ts_code_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves Max-Requested-Bandwidth-UL AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Max-Requested-Bandwidth-UL AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_max_requested_bandwidth_ul(struct avp *gavp, uint32_t *val);

/**Retrieves Max-Requested-Bandwidth-DL AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Max-Requested-Bandwidth-DL AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_max_requested_bandwidth_dl(struct avp *gavp, uint32_t *val);

/**Retrieves All-APN-Configurations-Included-Indicator AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains All-APN-Configurations-Included-Indicator AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_all_apn_configuration_included_indicator(struct avp *gavp, int32_t *val);

/**Retrieves PDN-Type AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains PDN-Type AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_pdn_type(struct avp *gavp, int32_t *val);

/**Retrieves VPLMN-Dynamic-Address-Allowed AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains VPLMN-Dynamic-Address-Allowed AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_vplmn_dynamic_address_allowed(struct avp *gavp, int32_t *val);

/**Retrieves PDN-GW-Allocation-Type AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains PDN-GW-Allocation-Type AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_pdn_gw_allocation_type(struct avp *gavp, int32_t *val);

/**Retrieves SIPTO-Permission AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains SIPTO-Permission AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_sipto_permission(struct avp *gavp, int32_t *val);

/**Retrieves LIPA-Permission AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains LIPA-Permission AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_lipa_permission(struct avp *gavp, int32_t *val);

/**Retrieves Restoration-Priority AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Restoration-Priority AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_restoration_priority(struct avp *gavp, uint32_t *val);

/**Retrieves SIPTO-Local-Network-Permission AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains SIPTO-Local-Network-Permission AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_sipto_local_network_permission(struct avp *gavp, int32_t *val);

/**Retrieves multiple Served-Party-IP-Address AVPs' values from group AVP. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple Served-Party-IP-Address AVPs.
  @param array_ret : the values will be saved in **array_ret. 
  @param len : the lengths, in bytes, of the values will be saved in *len. 
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_served_party_ip_address_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves QoS-Class-Identifier AVP value from group AVPUpon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains QoS-Class-Identifier AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_qos_class_identifier(struct avp *gavp, int32_t *val);

/**Retrieves Priority-Level AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Priority-Level AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_priority_level(struct avp *gavp, uint32_t *val);

/**Retrieves Pre-emption-Capability AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Pre-emption-Capability AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_pre_emption_capability(struct avp *gavp, int32_t *val);

/**Retrieves Pre-emption-Vulnerability AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Pre-emption-Vulnerability AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_pre_emption_vulnerability(struct avp *gavp, int32_t *val);

/**Retrieves WLAN-offloadability-EUTRAN AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains WLAN-offloadability-EUTRAN AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_wlan_offloadability_eutran(struct avp *gavp, uint32_t *val);

/**Retrieves WLAN-offloadability-UTRAN AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains WLAN-offloadability-UTRAN AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_wlan_offloadability_utran(struct avp *gavp, uint32_t *val);

/**Retrieves Trace-Reference AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Trace-Reference AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_trace_reference(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Trace-Depth AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Trace-Depth AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_trace_depth(struct avp *gavp, int32_t *val);

/**Retrieves Trace-NE-Type-List AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Trace-NE-Type-List AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_trace_ne_type_list(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Trace-Interface-List AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Trace-Interface-List AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_trace_interface_list(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Trace-Event-List AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Trace-Event-List AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_trace_event_list(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves OMC-Id AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains OMC-Id AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_omc_id(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Trace-Collection-Entity AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Trace-Collection-Entity AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_trace_collection_entity(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Job-Type AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Job-Type AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_job_type(struct avp *gavp, int32_t *val);

/**Retrieves multiple Cell-Global-Identity AVPs' values from group AVP. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple Cell-Global-Identity AVPs.
  @param array_ret : the values will be saved in **array_ret. 
  @param len : the lengths, in bytes, of the values will be saved in *len. 
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_cell_global_identity_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves E-UTRAN-Cell-Global-Identity AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains E-UTRAN-Cell-Global-Identity AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_e_utran_cell_global_identity(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves multiple E-UTRAN-Cell-Global-Identity AVPs' values from group AVP. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple E-UTRAN-Cell-Global-Identity AVPs.
  @param array_ret : the values will be saved in **array_ret. 
  @param len : the lengths, in bytes, of the values will be saved in *len. 
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_e_utran_cell_global_identity_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves multiple Routing-Area-Identity AVPs' values from group AVP. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple Routing-Area-Identity AVPs.
  @param array_ret : the values will be saved in **array_ret. 
  @param len : the lengths, in bytes, of the values will be saved in *len. 
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_routing_area_identity_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves multiple Location-Area-Identity AVPs' values from group AVP. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple Location-Area-Identity AVPs.
  @param array_ret : the values will be saved in **array_ret. 
  @param len : the lengths, in bytes, of the values will be saved in *len. 
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_location_area_identity_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves Tracking-Area-Identity AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Tracking-Area-Identity AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_tracking_area_identity(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves multiple Tracking-Area-Identity AVPs' values from group AVP. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple Tracking-Area-Identity AVPs.
  @param array_ret : the values will be saved in **array_ret. 
  @param len : the lengths, in bytes, of the values will be saved in *len. 
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_tracking_area_identity_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves List-Of-Measurements AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains List-Of-Measurements AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_list_of_measurements(struct avp *gavp, uint32_t *val);

/**Retrieves Reporting-Trigger AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Reporting-Trigger AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_reporting_trigger(struct avp *gavp, uint32_t *val);

/**Retrieves Report-Interval AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Report-Interval AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_report_interval(struct avp *gavp, int32_t *val);

/**Retrieves Report-Amount AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Report-Amount AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_report_amount(struct avp *gavp, int32_t *val);

/**Retrieves Event-Threshold-RSRP AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Event-Threshold-RSRP AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_event_threshold_rsrp(struct avp *gavp, uint32_t *val);

/**Retrieves Event-Threshold-RSRQ AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Event-Threshold-RSRQ AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_event_threshold_rsrq(struct avp *gavp, uint32_t *val);

/**Retrieves Logging-Interval AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Logging-Interval AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_logging_interval(struct avp *gavp, int32_t *val);

/**Retrieves Logging-Duration AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Logging-Duration AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_logging_duration(struct avp *gavp, int32_t *val);

/**Retrieves Measurement-Period-LTE AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Measurement-Period-LTE AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_measurement_period_lte(struct avp *gavp, int32_t *val);

/**Retrieves Measurement-Period-UMTS AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Measurement-Period-UMTS AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_measurement_period_umts(struct avp *gavp, int32_t *val);

/**Retrieves Collection-Period-RRM-LTE AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Collection-Period-RRM-LTE AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_collection_period_rrm_lte(struct avp *gavp, int32_t *val);

/**Retrieves Collection-Period-RRM-UMTS AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Collection-Period-RRM-UMTS AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_collection_period_rrm_umts(struct avp *gavp, int32_t *val);

/**Retrieves Positioning-Method AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Positioning-Method AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_positioning_method(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Measurement-Quantity AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Measurement-Quantity AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_measurement_quantity(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Event-Threshold-Event-1F AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Event-Threshold-Event-1F AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_event_threshold_event_1f(struct avp *gavp, int32_t *val);

/**Retrieves Event-Threshold-Event-1I AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Event-Threshold-Event-1I AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_event_threshold_event_1i(struct avp *gavp, int32_t *val);

/**Retrieves multiple MDT-Allowed-PLMN-Id AVPs' values from group AVP. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param gavp : a pointer to an AVP of type grouped which contains multiple MDT-Allowed-PLMN-Id AVPs.
  @param array_ret : the values will be saved in **array_ret. 
  @param len : the lengths, in bytes, of the values will be saved in *len. 
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_mdt_allowed_plmn_id_gavp_array(struct avp *gavp, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves Complete-Data-List-Included-Indicator AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Complete-Data-List-Included-Indicator AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_complete_data_list_included_indicator(struct avp *gavp, int32_t *val);

/**Retrieves PDP-Type AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains PDP-Type AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_pdp_type(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves PDP-Address AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains PDP-Address AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_pdp_address(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves QoS-Subscribed AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains QoS-Subscribed AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_qos_subscribed(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Ext-PDP-Type AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Ext-PDP-Type AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_ext_pdp_type(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Ext-PDP-Address AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Ext-PDP-Address AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_ext_pdp_address(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves CSG-Id AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains CSG-Id AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_csg_id(struct avp *gavp, uint32_t *val);

/**Retrieves Expiration-Date AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Expiration-Date AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_expiration_date(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves ProSe-Permission AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains ProSe-Permission AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_prose_permission(struct avp *gavp, uint32_t *val);

/**Retrieves multiple Reset-ID AVPs' values from message. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param msg : a pointer to a message structure which contains multiple Reset-ID AVPs.
  @param array_ret : the values will be saved in **array_ret. 
  @param len : the lengths, in bytes, of the values will be saved in *len. 
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_reset_id_array(struct msg *msg, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves Number-Of-Requested-Vectors AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Number-Of-Requested-Vectors AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_number_of_requested_vectors(struct avp *gavp, uint32_t *val);

/**Retrieves Immediate-Response-Preferred AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Immediate-Response-Preferred AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
int ss_get_immediate_response_preferred(struct avp *gavp, uint32_t *val);
*/
int ss_get_immediate_response_preferred(struct avp *gavp, uint32_t *val);

/**Retrieves Re-synchronization-Info AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Re-synchronization-Info AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_re_synchronization_info(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Item-Number AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Item-Number AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_item_number(struct avp *gavp, uint32_t *val);

/**Retrieves RAND AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains RAND AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_rand(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves XRES AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains XRES AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_xres(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves AUTN AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains AUTN AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_autn(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves KASME AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains KASME AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_kasme(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Confidentiality-Key AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Confidentiality-Key AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_confidentiality_key(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Integrity-Key AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Integrity-Key AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_integrity_key(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Kc AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Kc AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_kc(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves SRES AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains SRES AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_sres(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Cancellation-Type AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains Cancellation-Type AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_cancellation_type_msg(struct msg *msg, int32_t *val);

/**Retrieves CLR-Flags AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains CLR-Flags AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_clr_flags_msg(struct msg *msg, uint32_t *val);

/**Retrieves IDR-Flags AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains IDR-Flags AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_idr_flags_msg(struct msg *msg, uint32_t *val);

/**Retrieves IMS-Voice-Over-PS-Sessions-Supported AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains IMS-Voice-Over-PS-Sessions-Supported AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_ims_voice_over_ps_sessions_supported_msg(struct msg *msg, int32_t *val);

/**Retrieves Last-UE-Activity-Time AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains Last-UE-Activity-Time AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_last_ue_activity_time_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves IDA-Flags AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains IDA-Flags AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_ida_flags_msg(struct msg *msg, uint32_t *val);

/**Retrieves User-State AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains User-State AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_user_state(struct avp *gavp, int32_t *val);

/**Retrieves Geographical-Information AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Geographical-Information AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_geographical_information(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Geodetic-Information AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Geodetic-Information AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_geodetic_information(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Current-Location-Retrieved AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Current-Location-Retrieved AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_current_location_retrieved(struct avp *gavp, int32_t *val);

/**Retrieves Age-Of-Location-Information AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Age-Of-Location-Information AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_age_of_location_information(struct avp *gavp, uint32_t *val);

/**Retrieves CSG-Access-Mode AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains CSG-Access-Mode AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_csg_access_mode(struct avp *gavp, int32_t *val);

/**Retrieves CSG-Membership-Indication AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains CSG-Membership-Indication AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_csg_membership_indication(struct avp *gavp, int32_t *val);

/**Retrieves Time-Zone AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Time-Zone AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_time_zone(struct avp *gavp, unsigned char **val, size_t *len);

/**Retrieves Daylight-Saving-Time AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Daylight-Saving-Time AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_daylight_saving_time(struct avp *gavp, int32_t *val);

/**Retrieves DSR-Flags AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains DSR-Flags AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_dsr_flags_msg(struct msg *msg, uint32_t *val);

/**Retrieves Context-Identifier AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains Context-Identifier AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_context_identifier_msg(struct msg *msg, uint32_t *val);

/**Retrieves multiple Context-Identifier AVPs' values from message. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param msg : a pointer to a message structure which contains multiple Context-Identifier AVPs.
  @param array_ret : the values will be saved in **array_ret. 
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_context_identifier_array(struct msg *msg, uint32_t **array_ret, size_t *array_size);

/**Retrieves Trace-Reference AVP value from from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains Trace-Reference AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_trace_reference_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves multiple TS-Code AVPs value from message. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param msg : a pointer to a message structure which contains multiple TS-Code AVPs.
  @param array_ret : the values will be saved in **array_ret.  
  @param len : the lengths, in bytes, of the values will be saved in *len.
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_ts_code_array(struct msg *msg, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves multiple SS-Code AVPs value from message. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param msg : a pointer to a message structure which contains multiple SS-Code AVPs.
  @param array_ret : the values will be saved in **array_ret.  
  @param len : the lengths, in bytes, of the values will be saved in *len.
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_ss_code_array(struct msg *msg, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves DSA-Flags AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains DSA-Flags AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_dsa_flags_msg(struct msg *msg, uint32_t *val);

/**Retrieves PUR-Flags AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains PUR-Flags AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_pur_flags_msg(struct msg *msg, uint32_t *val);

/**Retrieves PUA-Flags AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains PUA-Flags AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_pua_flags_msg(struct msg *msg, uint32_t *val);

/**Retrieves multiple User-Id AVPs value from message. Upon successful function return the parameter **array_ret will point to the value. If the return is 0(success) the **array_ret should be freed after use.
 
  @param msg : a pointer to a message structure which contains multiple User-Id AVPs.
  @param array_ret : the values will be saved in **array_ret.  
  @param len : the lengths, in bytes, of the values will be saved in *len.
  @param array_size : the number of values written to **array_ret. if function return is other than 0(success) this value is set to zero.
  @return 0 : The AVPs has been found and its values are written to **array_ret.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
  @return ENOMEM : Memory allocation failed
*/
int ss_get_user_id_array(struct msg *msg, unsigned char ***array_ret, size_t **len, size_t *array_size);

/**Retrieves Visited-Network-Identifier AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains Visited-Network-Identifier AVP.
  @param val : the value will be saved in *val.  
  @param len : the length, in bytes, of the value retrieved will be saved in *len.
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_visited_network_identifier_msg(struct msg *msg, unsigned char **val, size_t *len);

/**Retrieves Service-Selection AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains Service-Selection AVP.
  @param val : the value will be saved in *val. 
  @param len : the length, in bytes, of the value retrieved will be saved in *len. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_service_selection_msg(struct msg *msg, unsigned char **val, size_t *len);

/**valrieves Alert-Reason AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains Alert-Reason AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_alert_reason_msg(struct msg *msg, int32_t *val);

/**valrieves NOR-Flags AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains NOR-Flags AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_nor_flags_msg(struct msg *msg, uint32_t *val);

/**valrieves IMS-Voice-Over-PS-Sessions-Supported AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains IMS-Voice-Over-PS-Sessions-Supported AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_ims_voice_over_ps_sessions_supported_msg(struct msg *msg,  int32_t *ret);

/**valrieves Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP value from message. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param msg : a pointer to a message structure which contains Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_homogeneous_support_of_ims_voice_over_ps_sessions_msg(struct msg *msg, int32_t *val);

/**valrieves Feature-List-ID AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Feature-List-ID AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_feature_list_id(struct avp *gavp, uint32_t *val);

/**valrieves Feature-List AVP value from group AVP. Upon successful function return the parameter *val will point to the value. The value should not be freed since it was not malloced.
 
  @param gavp : a pointer to an AVP of type grouped which contains Feature-List AVP.
  @param val : the value will be saved in *val. 
  @return 0 : The AVP has been found and its value is written to *val.
  @return EINVAL : A parameter is invalid.
  @return ENOENT : No AVP has been found.
*/
int ss_get_feature_list(struct avp *gavp, uint32_t *val);

#endif
