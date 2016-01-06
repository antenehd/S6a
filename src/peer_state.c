
#include "ssix_interface.h"

#define ALMOST_CASE_INSENSITIVE_SEARCH 1


/*Checks the connection state with remote peer. Only after the connection state is open that S6 messages may be sent to remote peer.*/
inline int ss_peer_state(char * diamid, size_t diamidlen){

	struct peer_hdr * peer;

	/*get peer by diameter identity*/
	CHECK_FCT_DO(fd_peer_getbyid( diamid, diamidlen, ALMOST_CASE_INSENSITIVE_SEARCH, &peer ), goto error);
	
	/*if peer is found*/
	if(peer){
		return fd_peer_get_state(peer);		
	}

error:	
	return -1;
}
