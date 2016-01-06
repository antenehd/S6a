
 S6a Application Interface Module
 Work in progress
 The freediameter library has some modified code in file message.c found in directory libfdproto, in file cnxctx.c found in directory libfdcore and in file sctp.c found in directory libfdcore. All the modified codes are put between comment 'MODIFIED' and 'ENDMODIFIED'.


/*
 * FUNCTION:	fd_msg_send, fd_msg_send_timeout  
 *
 * PARAMETERS:
 *  pmsg 	: Location of the message to be sent on the network (set to NULL on function return to avoid double deletion).
 *  anscb	: A callback to be called when corresponding answer is received, when sending a request (not used with answers)
 *  anscb_data	: opaque data to be passed back to the anscb (or expirecb) when it is called.
 *  expirecb    : (only for fd_msg_send_timeout) If the request did not get an answer before timeout, this callback is called.
 *  timeout     : (only for fd_msg_send_timeout) sets the absolute time until when to wait for an answer. Past this time,
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
 *              sentto : pointer to the peer to which the message was sent and no answer received within timeout.
 *		request: location of the pointer to the request that was not answered.
 *
 * RETURN VALUE:
 *  0      	: The message has been queued for sending (sending may fail asynchronously).
 *  EINVAL 	: A parameter is invalid (ex: anscb provided but message is not a request).
 *  ...
 */
int fd_msg_send ( struct msg ** pmsg, void (*anscb)(void *, struct msg **), void * data );
int fd_msg_send_timeout ( struct msg ** pmsg, void (*anscb)(void *, struct msg **), void * data, void (*expirecb)(void *, DiamId_t, size_t, struct msg **), const struct timespec *timeout );

	

/*
 * FUNCTION:	fd_disp_register
 *
 * PARAMETERS:
 *  cb 		  : The callback function to register (see dispatch_callback description above).
 *  how	  	  : How the callback must be registered.
 *  when          : Values that must match, depending on the how argument.
 *  opaque        : A pointer that is passed back to the handler. The content is not interpreted by the framework.
 *  handle        : On success, a handler to the registered callback is stored here if not NULL. 
 *		   This handler can be used to unregister the cb.
 *
 * DESCRIPTION: 
 *   Register a new callback to handle messages delivered locally.
 *
 * RETURN VALUE:
 *  0      	: The callback is registered.
 *  EINVAL 	: A parameter is invalid.
 *  ENOMEM	: Not enough memory to complete the operation
 */
int fd_disp_register ( int (*cb)( struct msg **, struct avp *, struct session *, void *, enum disp_action *), 
			enum disp_how how, struct disp_when * when, void * opaque, struct disp_hdl ** handle );


/*
 * FUNCTION:	fd_disp_unregister
 *
 * PARAMETERS:
 *  handle       : Location of the handle of the callback that must be unregistered.
 *  opaque       : If not NULL, the opaque data that was registered is restored here.
 *
 * DESCRIPTION: 
 *   Removes a callback previously registered by fd_disp_register.
 *
 * RETURN VALUE:
 *  0      	: The callback is unregistered.
 *  EINVAL 	: A parameter is invalid.
 */
int fd_disp_unregister ( struct disp_hdl ** handle, void ** opaque );

/* Destroy all handlers */
void fd_disp_unregister_all ( void );













/*
 * FUNCTION:	fd_msg_send, fd_msg_send_timeout  
 *
 * PARAMETERS:
 *  pmsg 	: Location of the message to be sent on the network (set to NULL on function return to avoid double deletion).
 *  anscb	: A callback to be called when corresponding answer is received, when sending a request (not used with answers)
 *  anscb_data	: opaque data to be passed back to the anscb (or expirecb) when it is called.
 *  expirecb    : (only for fd_msg_send_timeout) If the request did not get an answer before timeout, this callback is called.
 *  timeout     : (only for fd_msg_send_timeout) sets the absolute time until when to wait for an answer. Past this time,
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
 *              sentto : pointer to the peer to which the message was sent and no answer received within timeout.
 *		request: location of the pointer to the request that was not answered.
 *
 * RETURN VALUE:
 *  0      	: The message has been queued for sending (sending may fail asynchronously).
 *  EINVAL 	: A parameter is invalid (ex: anscb provided but message is not a request).
 *  ...
 */
int fd_msg_send ( struct msg ** pmsg, void (*anscb)(void *, struct msg **), void * data );
int fd_msg_send_timeout ( struct msg ** pmsg, void (*anscb)(void *, struct msg **), void * data, void (*expirecb)(void *, DiamId_t, size_t, struct msg **), const struct timespec *timeout );
	
