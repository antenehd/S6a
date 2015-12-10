#include <stdio.h>
#include <stdlib.h>
#include "interf_ssix.h"

int test_ulr(char * dest_host){

	diameterid * dst_host= (diameterid *) dest_host;
	diameterid * dst_rlm = (diameterid *)"localdomain";
	utf8string * usr_name = (utf8string *)"244444123456789";
	
	/*suprt-feat*/
	unsigned32 vendor_id = 10415;
	unsigned32 ftr_list_id = 1;
	unsigned32 ftr_list = 1; 		
	struct suprt_feature suprt_ftr = {&vendor_id, &ftr_list_id, &ftr_list, NULL};

	/*term-info*/
	utf8string * imei = (utf8string *)"2345";
	utf8string * soft_vrs = (utf8string *)"22";/*(utf8string *)"12"*/
	octetstring * meid = NULL;/*(octetstring *)"2345";*/
    struct terminal_info term_info = {imei, soft_vrs, meid};
	
	enum rat_type rat_type = VIRTUAL;
	unsigned32 ulr_flg = 0;
	enum ue_srvcc_cap ue_srvcc = UE_SRVCC_SUPPORTED;
	octetstring * vis_plmn_id = (octetstring *)"plan_id";
	
	octetstring  sgsn_num [] = {0x25,0x14,0x56};
	enum hm_suprt_ims_vop_sess hm_ims_vop = SUPPORTED;
	address * gmlc_addr = (address *)"ma.at";

	/*active-apn*/
	unsigned32 contxt_id = 1;
	utf8string * serv_sel = (utf8string *)"serv1";
	/*mip6*/	
	address * hm_agt_addr = (address *)"hm-adr1";
	address * hm_agt_addr2 = (address *)"hm-adr2";
	struct mip_hm_agt_hst * hm_agt_hst = NULL;
	struct mip6_agent_info agt_inf = {hm_agt_addr, hm_agt_addr2, hm_agt_hst}; /*end mip6*/	
	octetstring * vist_net_id = (octetstring *)"vis-id";
	struct spec_apn_inf apn_inf = {serv_sel, &agt_inf, vist_net_id, NULL}; 
	struct active_apn act_apn = {&contxt_id, serv_sel, &agt_inf, vist_net_id, &apn_inf, NULL}; 

	/*eqn-plmn*/
	struct vis_plmn_id plmn_id = {vis_plmn_id, NULL};
	struct eqv_plmn_lst plmn_lst ={&plmn_id};

	octetstring * mme_num_mtsmsm = (octetstring *)"mme-23";
	enum sms_reg_req sms_reg = SMS_REGISTRATION_REQUIRED;
	diameterid * coupl_nd_dia_id = (diameterid *)"coupl-node";

	struct ulr_msg msg = {dst_host, dst_rlm, usr_name, &suprt_ftr, &term_info, &rat_type, &ulr_flg, &ue_srvcc,
		vis_plmn_id, sgsn_num, &hm_ims_vop, gmlc_addr, &act_apn, &plmn_lst, mme_num_mtsmsm, &sms_reg, 
		coupl_nd_dia_id};

	/*send request*/
	ss_req( ULR, (void *)&msg);

	return 1;
}

int main(int argc, char **argv){
	
	ss_init();
	printf("INFO::ssix initialized \n");
	sleep(60);
	if(argc==2)
		test_ulr(argv[1]);

	ss_wait_shutdown();
	
	return 1;	
}
