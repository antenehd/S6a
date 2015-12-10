
#include "internal_ssix.h"

static void ss_ans_cb(void * data, struct msg ** msg){

	printf("Answer received\n");

	/* Free the message */
	CHECK_FCT_DO(fd_msg_free(*msg), return);
	*msg = NULL;
}

int ss_req( enum s6_cmd cmd, void *msg){

	struct msg * req = NULL;
	union avp_value val;
	struct avp *avp, *gavp;
	struct session *sess = NULL;
	int check_return = 1;
	int check_cmd = (int) cmd;

	if(msg){

		/* Set the rest of the AVPs based on the command type*/
		switch(check_cmd){
			
			case ULR:				
				check_return = ss_msg_ulr_set(&req,(struct ulr_msg *)msg);
				break;

			case AIR:
				check_return = ss_msg_air_set(&req,(struct air_msg *)msg);
				break;

			case CLR:
				check_return = ss_msg_clr_set(&req,(struct clr_msg *)msg);
				break;

			case IDR:
				check_return = ss_msg_idr_set(&req,(struct idr_msg *)msg);
				break;

			case DSR:
				check_return = ss_msg_dsr_set(&req,(struct dsr_msg *)msg);
				break;

			case PUR:
				check_return = ss_msg_pur_set(&req,(struct pur_msg *)msg);
				break;

			case RSR:
				check_return = ss_msg_rsr_set(&req,(struct rsr_msg *)msg);
				break;

			case NOR:
				check_return = ss_msg_nor_set(&req,(struct nor_msg *)msg);
				break;			
			
		}

		/* Send the message to the destination peer*/
		if(check_return != 0)
			CHECK_FCT_DO( fd_msg_send( &req, ss_ans_cb, NULL), goto error );

	}	

	else
		return 0;

	return 1;

	error:
		printf("ERROR: in functin 'ss_req( %d, msg)'\n", cmd);
		return 0;
	
}
