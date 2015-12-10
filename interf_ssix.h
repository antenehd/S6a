
#ifndef SS_INTERF_SSIX
#define SS_INTERF_SSIX

#include <stdint.h>


enum s6_cmd{
	ULR,	/*UPDATE LOCATION REQUEST*/
	ULA,	/*UPDATE LOCATION ANSWER*/
	CLR,	/*CANCEL LOCATION REQUEST*/
	CLA,	/*CANCEL LOCATION ANSWER*/
	AIR,	/*AUTHENTICATION INFORMATION REQUEST*/
	AIA,	/*AUTHENTICATION INFORMATION ANSWER*/
	IDR,	/*INSERT SUBSCRIBER DATA REQUEST*/
	IDA,	/*INSERT SUBSCRIBER DATA ANSWER*/
	DSR,	/*DELETE SUBSCRIBER DATA REQUEST*/
	DSA,	/*DELETE SUBSCRIBER DATA ANSWER*/
	PUR,	/*PURGE UE REQUEST*/
	PUA,	/*PURGE UE ANSWER*/
	RSR,	/*RESET REQUEST*/
	RSA,	/*RESET ANSWER*/
	NOR,	/*NOTIFY REQUEST*/
	NOA	/*NOTIFY ANSWER*/
};

/*UE-SRVCC-Capability*/
enum ue_srvcc_cap{
	UE_SRVCC_NOT_SUPPORTED = 0,
	UE_SRVCC_SUPPORTED

};

/*Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions */
enum hm_suprt_ims_vop_sess{
	NOT_SUPPORTED = 0,
	SUPPORTED
};

enum rat_type{
	WLAN = 0,
	VIRTUAL = 1,
	UTRAN = 1000,
	GERAN = 1001,
	GAN = 1002,
	HSPA_EVOLUTION = 1003,
	EUTRAN = 1004,
	CDMA2000_1X = 2000,
	HRPD = 2001,
	UMB = 2002,
	EHRPD = 2003
};

enum sms_reg_req{
	SMS_REGISTRATION_REQUIRED = 0,  
	SMS_REGISTRATION_NOT_PREFERRED, 
	NO_PREFERENCE	
};

enum err_diagn{
	PRS_DATA_SUBSCRIBED = 0,
	NO_GPRS_DATA_SUBSCRIBED,
	ODB_ALL_APN,
	ODB_HPLMN_APN,
	ODB_VPLMN_APN
};

enum subc_status{
	SERVICE_GRANTED  = 0,
	OPERATOR_DETERMINED_BARRING 
};

enum ics_indic{
	False = 0,
	True
};

enum net_acc_mod{
	PACKET_AND_CIRCUIT = 0,
	Reserved,
	ONLY_PACKET 
};

enum notf_ue_usr{
	NOTIFY_LOCATION_ALLOWED = 0, 
	NOTIFYANDVERIFY_LOCATION_ALLOWED_IF_NO_RESPONSE, 
	NOTIFYANDVERIFY_LOCATION_NOT_ALLOWED_IF_NO_RESPONSE, 
	LOCATION_NOT_ALLOWED
};

enum gmlc_restr{
	GMLC_LIST = 0, 
	HOME_COUNTRY 
};

enum enum_plmn_cln{
	BROADCAST_SERVICE = 0, 
	O_AND_M_HPLMN, 
	O_AND_M_VPLMN,
	ANONYMOUS_LOCATION, 
	TARGET_UE_SUBSCRIBED_SERVICE	 
};

enum all_apn_inc{
	All_APN_CONFIGURATIONS_INCLUDED = 0, 
	MODIFIED_ADDED_APN_CONFIGURATIONS_INCLUDED
};

enum pdn_typ{
	IPv4 = 0,
	IPv6,
	IPv4v6,
	IPv4_OR_IPv6	 	
};

enum qos_cls_id{
	QCI_1 = 1,
	QCI_2,
	QCI_3,
	QCI_4,
	QCI_5,
	QCI_6,
	QCI_7,
	QCI_8,
	QCI_9,
	QCI_65 = 65,
	QCI_66 = 66,
	QCI_69 = 69,
	QCI_70 = 70
};

enum pre_emp_cap{
	PRE_EMPTION_CAPABILITY_ENABLED =0,
	PRE_EMPTION_CAPABILITY_DISABLED
};

enum pre_emp_vuln{
	PRE_EMPTION_VULNERABILITY_ENABLED = 0,
	PRE_EMPTION_VULNERABILITY_DISABLED
};

enum vplmn_dyn_addr_allw{
	NOTALLOWED = 0,
	ALLOWED
};

enum pdn_gw_alloc_typ{
	STATIC = 0,
	DYNAMIC
};

enum sipto_perm{
	SIPTO_above_RAN_ALLOWED = 0, 
	SIPTO_above_RAN_NOTALLOWED
};

enum lipa_perm{
	LIPA_PROHIBITED = 0,
	LIPA_ONLY,
	LIPA_CONDITIONAL,
	LIPA_NOT_PRESENT
};

enum trace_depth{
	Minimum = 0,  
	Medium,  
	Maximum, 
	MinimumWithoutVendorSpecificExtension,
	MediumWithoutVendorSpecificExtension, 
	MaximumWithoutVendorSpecificExtension
};

enum job_typ{
	Immediate_MDT_only = 0, 
	Logged_MDT_only, 
	Trace_only,
	Immediate_MDT_and_Trace, 
	RLF_reports_only, 
	RCEF_reports_only
};

enum repor_interv{
	UMTS_250MS = 0,  
	UMTS_500MS,  
	UMTS_1000MS,  
	UMTS_2000MS,  
	UMTS_3000MS, 
	UMTS_4000MS,  
	UMTS_6000MS,  
	UMTS_8000MS,  
	UMTS_12000MS,  
	UMTS_16000MS,  
	UMTS_20000MS,  
	UMTS_24000MS,  
	UMTS_28000MS,  
	UMTS_32000MS,  
	UMTS_64000MS,
	LTE_120MS,
	LTE_240MS,
	LTE_480MS,  
	LTE_640MS,
	LTE_1024MS,  
	LTE_2048MS,  
	LTE_5120MS,  
	LTE_10240MS,  
	LTE_60000MS,  
	LTE_360000MS,  
	LTE_720000MS,  
	LTE_1800000MS,  
	LTE_3600000MS
};

enum repor_amnt{
	ONE = 0,  
	TWO,
	FOUR,
	EIGHT, 
	SIXTEEN,  
	THIRTYTWO,
 	SIXTYFOUR,
	enum_INFINITY
};

enum log_interv{
	LOG_1p28 = 0, 
	LOG_2p56,  
	LOG_5p12,  
	LOG_10p24, 
	LOG_20p48,  
	LOG_30p72, 
	LOG_40p96,  
	LOG_61p44
};

enum log_dur{
	LOG_600SEC = 0,  
	LOG_1200SEC,  
	LOG_2400SEC,  
	LOG_3600SEC,  
	LOG_5400SEC,  
	LOG_7200SEC
};

enum period_lte{
	D_1024MS = 0, 
	D_1280MS, 
	D_2048MS, 
	D_2560MS, 
	D_5120MS,
	D_10240MS,
	D_1MIN
};

enum period_umts{
	D_250MS = 0,  
	D_500MS,  
	D_1000MS,  
	D_2000MS,  
	D_3000MS, 
	D_4000MS,  
	D_6000MS,  
	D_8000MS,
	D_12000MS,  
	D_16000MS,  
	D_20000MS,  
	D_24000MS,  
	D_28000MS,  
	D_32000MS,  
	D_64000MS
};

enum comp_data_lst_incl_ind{
	All_PDP_CONTEXTS_INCLUDED = 0,
	MODIFIED_ADDED_PDP_CONTEXTS_INCLUDED
};

enum roam_restr_unsuppr{
	Roaming_Restricted_Due_To_Unsupported_Feature = 0
};

enum vplmn_lipa_allw{
	LIPA_NOTALLOWED = 0,
	LIPA_ALLOWED
};

enum relay_nod_ind{
	NOT_RELAY_NODE = 0,
	RELAY_NODE
};

enum mdt_usr_consent{
	CONSENT_NOT_GIVEN = 0,
	CONSENT_GIVEN
};

enum subsc_vsrvcc{
	VSRVCC_SUBSCRIBED = 0
};

enum cancel_typ{
	MME_UPDATE_PROCEDUR = 0,
	SGSN_UPDATE_PROCEDURE,
	UBSCRIPTION_WITHDRAWAL,
	UPDATE_PROCEDURE_IWF,
	INITIAL_ATTACH_PROCEDURE
};

enum ims_vops_sess_suprt{
	IMS_NOT_SUPPORTED = 0,
	IMS_SUPPORTED
};

enum user_state{
	DETACHED = 0,
	ATTACHED_NOT_REACHABLE_FOR_PAGING,
	ATTACHED_REACHABLE_FOR_PAGING,
	CONNECTED_NOT_REACHABLE_FOR_PAGING,
	CONNECTED_REACHABLE_FOR_PAGING,
	RESERVED
};

/*Current-Location-Retrieved*/
enum curr_loc_retr{
	ACTIVE_LOCATION_RETRIEVAL = 0
};

/*CSG-Access-Mode*/
enum csg_accs_mode{
	CLOSED = 0,
	HYBRIDE
};

/*CSG-Membership-Indication*/
enum csg_memb_ind{
	Not_CSG_MEMBER = 0,
	CSG_MEMBER
};

/*Daylight-Saving-Time*/
enum day_save_time{
	NO_ADJUSTMENT = 0, 
	PLUS_ONE_HOUR_ADJUSTMENT,
	PLUS_TWO_HOURS_ADJUSTMENT
};

/*Alert-Reason*/
enum alert_reason{
	UE_PRESENT = 0, 
	UE_MEMORY_AVAILABLE
};

enum sipto_loc_net_perm{
     siptoAtLocalNetworkAllowed = 0, 
     siptoAtLocalNetworkNotAllowed 
};
/*******************************************************************************/
/*	message structure used by MME to send message to the diameter application  */
/*******************************************************************************/


typedef uint32_t unsigned32;
typedef int32_t integer32;
typedef unsigned char  utf8string;
typedef unsigned char  diameterid;
typedef unsigned char octetstring;
typedef unsigned char address;
typedef unsigned char ss_time;

struct suprt_feature{
		unsigned32 * vendor_id;
		unsigned32 * feature_list_id;
		unsigned32 * feature_list;
		
		struct suprt_feature * next; /*used for concatenation*/
}; 

struct terminal_info{
 		utf8string * imei;
		utf8string * soft_vrs;
		octetstring * meid;
};

/*struct mip_hm_agt_hst: MIP-Home-Agent-Host*/
struct mip_hm_agt_hst{
	diameterid *dst_rlm;
	diameterid *dst_hst;	
};

/*struct mip6_agent_info: MIP6-Agent-Info		*/
/*		hm_agt_addr: MIP-Home-Agent-Address		*/
/*		hm_agt_hst: MIP-Home-Agent-Host			*/
struct mip6_agent_info{
	address * hm_agt_addr1;
	address * hm_agt_addr2;
	struct mip_hm_agt_hst * hm_agt_hst;
};

struct spec_apn_inf{
	utf8string * serv_sel;
	struct mip6_agent_info * agt_inf; 
	octetstring * vist_net_id;

	struct spec_apn_inf *next;/*used for concatenation*/
};

/*struct active_apn: Active-APN*/
/*		contxt_id: Context-Identifier*/
/*		serv_sel:  Service-Selection*/
struct active_apn{
	unsigned32 * contxt_id;
	utf8string * serv_sel;
	struct mip6_agent_info * agt_inf; 
	octetstring * vist_net_id;
	struct spec_apn_inf * apn_inf; 

	struct active_apn * next; /*used for concatenation*/
};

struct vis_plmn_id{
	octetstring * plmn_id;

	struct vis_plmn_id * next;
};

/*struct eqv_plmn_lst: Equivalent-PLMN-List */
/*		vis_plmn_id: Visited-PLMN-Id		*/
struct eqv_plmn_lst{
	struct vis_plmn_id * vis_plmn_id;
};

/*struct reg_subsc_zn_cd: concatinated Regional-Subscription-Zone-Code AVPs*/
/*		zn_cd: Regional-Subscription-Zone-Code*/
/*		next: the next Regional-Subscription-Zone-Code or NULL is it the last one*/
struct reg_subsc_zn_cd{
	octetstring * zn_cd;
	
	struct reg_subsc_zn_cd * next;
};

/*struct gmlc_num: concatenated GMLC-Number AVPs*/
/*		num: GMLC-Number*/
/*		next: the next GMLC-Number or NULL is it the last one*/
struct gmlc_num{
	octetstring * num;

	struct gmlc_num * next;
};

/*struct exter_cln: concatenated External-Client AVPs			  */
/*		cln_id: Client-Identity									  */
/*		gmlc_rstr: GMLC-Restriction								  */
/*		ntf_usr: Notification-To-UE-User 						  */
/*		next: the next External-Client or NULL is it the last one */
struct exter_cln{
	octetstring * cln_id;
	enum gmlc_restr * gmlc_rstr;
	enum notf_ue_usr * ntf_usr;	

	struct exter_cln * next;
};

/*struct plmn_cln: concatenated PLMN-Client AVPs*/
/*		cln: PLMN-Client*/
/*		next: the next PLMN-Client or NULL is it the last one*/
struct plmn_cln{
	enum enum_plmn_cln * cln;

	struct plmn_cln * next;
};

/*struct serv_type: concatenated Service-Type AVPs*/
/*		servtyp_id: ServiceTypeIdentity*/
/*		gmlc_rstr: GMLC-Restriction*/
/*		ntf_usr: Notification-To-UE-User */
/*		next: the next Service-Type or NULL is it the last one*/
struct serv_type{
	unsigned32 * servtyp_id; 
	enum gmlc_restr * gmlc_rstr;
	enum notf_ue_usr * ntf_usr;	

	struct serv_type * next;
};

/*struct lcs_prvexcp: concatenated LCS-PrivacyException AVPs*/
/*		ss_cd: SS-Code*/
/*		ss_sts: SS-Status*/
/*		ntf_usr: Notification-To-UE-User*/
/*		extr_cln: External-Client*/
/*		plmn_cln: PLMN-Client*/
/*		srv_typ: Service-Type*/
/*		next: the next LCS-PrivacyException or NULL is it the last one*/
struct lcs_prvexcp{
	octetstring * ss_cd;
	octetstring * ss_sts;
	enum notf_ue_usr * ntf_usr;	
	struct exter_cln * extr_cln; 
	struct plmn_cln * plmn_cln; 
	struct serv_type * srv_typ;

	struct lcs_prvexcp * next;	
};

/*struct mo_lr: concatenated MO-LR AVPs*/
/*		ss_cd: SS-Code*/
/*		ss_sts: SS-Status*/
/*		next: the next MO-LR or NULL is it the last one*/
struct mo_lr{
	octetstring * ss_cd;
	octetstring * ss_sts; 

	struct mo_lr * next;		
};
	
/*struct lcs_info: LCS-Info*/
/*		gmlc_nm: GMLC-Number*/
/*		prv_excp: LCS-PrivacyException*/
/*		mo_lr: MO-LR*/
struct lcs_info{
	struct gmlc_num * gmlc_nm; 
	struct lcs_prvexcp * prv_excp;
 	struct mo_lr * mo_lr;
};

/*struct ts_code: concatinated TS-Code AVPs*/
/*		code: TS-Code*/
/*		next: the next TS-Code or NULL is it the last one*/
struct ts_code{
	octetstring * code;

	struct ts_code * next; 
};

/*struct tele_srv: Teleservice-List*/
/*		ts_cd:  TS-Code*/
struct tele_srv{
	struct ts_code * ts_cd;
};

/*struct ts_code: concatinated Call-Barring-Info AVPs*/
/*		ss_cd: SS-Code*/
/*		ss_sts: SS-Status*/
/*		next: the next Call-Barring-Info or NULL is it the last one*/
struct call_bar_inf{
	octetstring * ss_cd;
	octetstring * ss_sts;

	struct call_bar_inf * next;
};

/*struct ambr: AMBR*/
/*		mx_req_bw_ul: Max-Requested-Bandwidth-UL */
/*		mx_req_bw_dl: Max-Requested-Bandwidth-DL*/
struct ambr{
	unsigned32 * mx_req_bw_ul; 
	unsigned32 * mx_req_bw_dl; 
};

/*struct apn_conf: concatinated Served-Party-IP-Address AVPs*/
/*		addr: Served-Party-IP-Address*/
/*		next: the next Served-Party-IP-Address or NULL is it the last one*/
struct servd_prty_ip_addr{
	address * addr;

	struct servd_prty_ip_addr * next;
};

/*struct alloc_ret_prio: Allocation-Retention-Priority*/
/*		prio_lev: Priority-Level */
/*		emp_cap: Pre-emption-Capability*/
/*		emp_vuln: Pre-emption-Vulnerability*/
struct alloc_ret_prio{
	unsigned32 * prio_lev; 
	enum pre_emp_cap * emp_cap; 
	enum pre_emp_vuln * emp_vuln;
};

/*struct eps_subcd_qos_prof: EPS-Subscribed-QoS-Profile */
/*		cls_id: QoS-Class-Identifier					*/
/*		allc_ret_prio:  Allocation-Retention-Priority   */
struct eps_subcd_qos_prof{
	enum qos_cls_id * cls_id;
	struct alloc_ret_prio * allc_ret_prio;
};

/*struct wlan_offld: WLAN-offloadability	*/
/*		eutran: WLAN-offloadability-EUTRAN  */
/*		utran: WLAN-offloadability-UTRAN	*/
struct wlan_offld{
	unsigned32 * eutran; 
	unsigned32 * utran; 
};

/*struct apn_conf: concatinated APN-Configuration AVPs*/
/*		contxt_id: Context-Identifier*/
/*		srv_prty_addr: Served-Party-IP-Address*/
/*		pdn_typ: PDN-Type*/
/*		srv_sel:  Service-Selection*/
/*		eps_qos_prof: EPS-Subscribed-QoS-Profile*/
/*		vplmn_dyn_allw: VPLMN-Dynamic-Address-Allowed*/
/*		mip6_agt_inf: MIP6-Agent-Info*/
/*		vist_net_id: Visited-Network-Identifier */
/*		pdn_alloc_typ: PDN-GW-Allocation-Type*/
/*		charg_char: 3GPP-Charging-Characteristics*/
/*		ambr: AMBR*/
/*		apn_inf: Specific-APN-Info*/
/*		apn_oi_repl: APN-OI-Replacement*/
/*		sipto_perm: SIPTO-Permission*/
/*		lipa_perm: LIPA-Permission*/
/*		res_prio: Restoration-Priority*/
/*		sipto_lc_net_perm: SIPTO-Local-Network-Permission*/
/*		wln_offld: WLAN-offloadability*/
/*		next: the next APN-Configuration or NULL is it the last one*/
struct apn_conf{
	unsigned32 * contxt_id;
	struct servd_prty_ip_addr * srv_prty_addr;
	enum pdn_typ * pdn_typ; 
	utf8string * srv_sel;
	struct eps_subcd_qos_prof * eps_qos_prof;
 	enum vplmn_dyn_addr_allw * vplmn_dyn_allw;
	struct mip6_agent_info * mip6_agt_inf;  
	octetstring * vist_net_id;
	enum pdn_gw_alloc_typ * pdn_alloc_typ;
	utf8string * charg_char;  
	struct ambr * ambr; 
	struct spec_apn_inf * apn_inf;   
	utf8string * apn_oi_repl;
	enum sipto_perm * sipto_perm;
	enum lipa_perm * lipa_perm;
	unsigned32 * res_prio;
	enum sipto_loc_net_perm * sipto_lc_net_perm;
	struct wlan_offld * wln_offld;

	struct apn_conf * next;
};

/*struct apn_conf_prf: APN-Configuration-Profile			*/
/*		contxt_id: Context-Identifier						*/
/*		all_apn: All-APN-Configurations-Included-Indicator  */
/*		apn_cnf: APN-Configuration							*/
struct apn_conf_prf{
	unsigned32 * contxt_id;
	enum all_apn_inc * all_apn;
	struct apn_conf * apn_cnf;
};

/*struct apn_conf: concatinated Cell-Global-Identity AVPs				*/
/*		id: Cell-Global-Identity										*/
/*		next: the next Cell-Global-Identity or NULL is it the last one  */
struct cgi{
	octetstring * id;
	
	struct cgi * next;
};

/*struct eutran_cgi: concatinated E-UTRAN-Cell-Global-Identity AVPs				*/
/*		id: E-UTRAN-Cell-Global-Identity										*/
/*		next: the next E-UTRAN-Cell-Global-Identity or NULL is it the last one  */
struct eutran_cgi{
	octetstring * id;
	
	struct eutran_cgi * next;
};

/*struct rout_area_id: concatinated Routing-Area-Identity AVPs			*/
/*		id: Routing-Area-Identity										*/
/*		next: the next Routing-Area-Identity or NULL is it the last one */
struct rout_area_id{
	octetstring * id;

	struct rout_area_id * next;
};

/*struct lai: concatinated Location-Area-Identity AVPs			*/
/*		id: Location-Area-Identity										*/
/*		next: the next Location-Area-Identity or NULL is it the last one */
struct lai{
	octetstring * id;

	struct lai * next;
};

/*struct tai: concatinated Tracking-Area-Identity AVPs				     */
/*		id: Tracking-Area-Identity										 */
/*		next: the next Tracking-Area-Identity or NULL is it the last one */
struct tai{
	octetstring * id;

	struct tai * next;
};

/*struct area_scope: Area-Scope*/
/*		cgi: Cell-Global-Identity*/
/*		eu_cgi: E-UTRAN-Cell-Global-Identity*/
/*		rt_area_id: Routing-Area-Identity*/
/*		lai: Location-Area-Identity */
/*		tai: Tracking-Area-Identity*/
struct area_scope{
	struct cgi * cgi; 
	struct eutran_cgi * eu_cgi;
	struct rout_area_id * rt_area_id;
	struct lai * lai;
	struct tai * tai;
};

/*struct mdt_allw_plmn_id: concatinated MDT-Allowed-PLMN-Id AVPs      */
/*		id :MDT-Allowed-PLMN-Id										  */
/*		next: the next MDT-Allowed-PLMN-Id or NULL is it the last one */
struct mdt_allw_plmn_id{
	octetstring * id;

	struct mdt_allw_plmn_id * next;
};

/*struct mdt_conf: MDT-Configuration*/
/*		jb_typ: Job-Type*/
/*		area_scop: Area-Scope */
/*		lst_of_measr: List-Of-Measurements */
/*		repr_trig: Reporting-Trigger*/
/*		repr_interv: Report-Interval */
/*		repr_amnt: Report-Amount*/
/*		evt_thrd_rsrp: Event-Threshold-RSRP*/
/*		evt_thrd_rsrq: Event-Threshold-RSRQ */
/*		lg_interv: Logging-Interval*/
/*		lg_dur: Logging-Duration*/
/*		mst_prd_lte: Measurement-Period-LTE */
/*		mst_prd_umts: Measurement-Period-UMTS*/
/*		cl_prd_rmm_lte: Collection-Period-RMM-LTE*/
/*		cl_prd_rmm_umts: Collection-Period-RRM-UMTS*/
/*		pos_measr: Positioning-Method*/
/*		measr_qnt: Measurement-Quantity*/
/*		evt_thrd_evt_1f: Event-Threshold-Event-1F*/
/*		evt_thrd_evt_1i: Event-Threshold-Event-1I*/
/*		allw_plmn_id: MDT-Allowed-PLMN-Id*/
struct mdt_conf{
	enum job_typ * jb_typ;
	struct area_scope * area_scop;
	unsigned32 * lst_of_measr;
	unsigned32 * repr_trig; 
	enum repor_interv * repr_interv;
	enum repor_amnt * repr_amnt; 
	unsigned32 * evt_thrd_rsrp;  
	unsigned32 * evt_thrd_rsrq;  
	enum log_interv * lg_interv;
	enum log_dur * lg_dur;
	enum period_lte * mst_prd_lte;
	enum period_umts * mst_prd_umts;
	enum period_lte * cl_prd_rmm_lte;
	enum period_umts * cl_prd_rmm_umts;
	octetstring * pos_measr;
	octetstring * measr_qnt; 
	integer32 * evt_thrd_evt_1f;
	integer32 * evt_thrd_evt_1i;
	struct mdt_allw_plmn_id * allw_plmn_id; 
};

/*struct trace_data: Trace-Data*/
/*		trc_ref: Trace-Reference*/
/*		trc_dpz: Trace-Depth*/
/*		trc_ne_typ_lst: Trace-NE-Type-List*/
/*		trc_if_lst: Trace-Interface-List*/
/*		trc_evn_lst: Trace-Event-List*/
/*		omc_id: OMC-Id*/
/*		trc_coll_enty: Trace-Collection-Entity*/
/*		mdt_cnf: MDT-Configuration*/
struct trace_data{
	octetstring * trc_ref; 
	enum trace_depth * trc_dpz;
	octetstring * trc_ne_typ_lst;
	octetstring * trc_if_lst;
	octetstring * trc_evn_lst;
	octetstring * omc_id;
	address * trc_coll_enty;
	struct mdt_conf * mdt_cnf;
};

/*struct pdp_ctxt: concatinated PDP-Context AVPs     		 */
/*		contxt_id : Context-Identifier 						 */
/*		pdp_typ: PDP-Type									 */
/*		pdp_addr: PDP-Address								 */
/*		qos_subcd: QoS-Subscribed							 */
/*		vplmn_dyn_allw: VPLMN-Dynamic-Address-Allowed 		 */
/*		serv_sel: Service-Selection							 */
/*		charg_char: 3GPP-Charging-Characteristics			 */
/*		ext_pdp_typ: Ext-PDP-Type							 */
/*		ext_pdp_addr: Ext-PDP-Address						 */
/*		ambr: AMBR											 */
/*		apn_oi_repl: APN-OI-Replacement 					 */
/*		sipto_perm: SIPTO-Permission						 */
/*		lipa_perm: LIPA-Permission							 */
/*		res_prio: Restoration-Priority 						 */
/*		sipto_lc_net_perm: SIPTO-Local-Network-Permission 	 */
/*		next: the next PDP-Context or NULL is it the last one */
struct pdp_ctxt{
	unsigned32 * contxt_id;
	octetstring * pdp_typ;
	address * pdp_addr;
	octetstring * qos_subcd;
 	enum vplmn_dyn_addr_allw * vplmn_dyn_allw;
	utf8string * serv_sel;
	utf8string * charg_char;
	octetstring * ext_pdp_typ;
	address * ext_pdp_addr;
	struct ambr * ambr; 
	utf8string * apn_oi_repl;
	enum sipto_perm * sipto_perm;
	enum lipa_perm * lipa_perm;
	unsigned32 * res_prio;
	enum sipto_loc_net_perm * sipto_lc_net_perm;

	struct pdp_ctxt * next;
};

/*struct gprs_subsc_dt: GPRS-Subscription-Data*/
/*		incl_ind: Complete-Data-List-Included-Indicator */
/*		pdp_ctx: PDP-Context*/
struct gprs_subsc_dt{
	enum comp_data_lst_incl_ind * incl_ind;
	struct pdp_ctxt * pdp_ctx;
};

/*struct servc_sel: concatinated Service-Selection AVPs  	        */
/*		serv_sel: Service-Selection											*/
/*		next: the next Service-Selection or NULL is it the last one */
struct servc_sel{
	utf8string * serv_sel;	

	struct servc_sel * next;
};

/*struct csg_subsc_dt: concatinated CSG-Subscription-Data AVPs         */
/*		csg_id: CSG-Id*/
/*		expr_date: Expiration-Date*/
/*		serv_sel: Service-Selection*/
/*		vis_plmn_id: Visited-PLMN-Id*/
/*		next: the next CSG-Subscription-Data or NULL is it the last one */
struct csg_subsc_dt{
	unsigned32 * csg_id;
	ss_time * expr_date;
	struct servc_sel * serv_sel;
	octetstring * vis_plmn_id;

	struct csg_subsc_dt * next;
};

/*struct prose_subsc_dt: ProSe-Subscription-Data*/
/*		prose_perm: ProSe-Permission			*/
struct prose_subsc_dt{
	unsigned32 * prose_perm;
};

/*struct subsc_data: Subscription-Data*/
/*		subc_st: Subscriber-Status*/
/*		msisdn: MSISDN*/
/*		a_msisdn: A-MSISDN*/
/*		stn_sr: STN-SR*/
/*		ics_ind: ICS-Indicator*/
/*		net_acc_mod: Network-Access-Mode*/
/*		odb: Operator-Determined-Barring*/
/*		hplmn_odb: HPLMN-ODB*/
/*		rg_zn_cd: Regional-Subscription-Zone-Code*/
/*		acc_restr_dt: Access-Restriction-Data*/
/*		apn_oi_repl: APN-OI-Replacement */
/*		lcs_inf: LCS-Info*/
/*		tele_srv: Teleservice-List */
/*		call_br_inf: Call-Barring-Info*/
/*		charg_char: 3GPP-Charging-Characteristics*/
/*		ambr: AMBR*/
/*		apn_cnf_prf: APN-Configuration-Profile*/
/*		rat_frq_sel_pri_id:  RAT-Frequency-Selection-Priority-ID*/
/*		trc_dt: Trace-Data*/
/*		gprs_sub_dt: GPRS-Subscription-Data*/
/*		csg_sub_dt: CSG-Subscription-Data*/
/*		roam_restr: Roaming-Restricted-Due-To-Unsupported-Feature*/
/*		subcd_rau_tau_tmr: Subscribed-Periodic-RAU-TAU-Timer*/
/*		mps_prio: MPS-Priority*/
/*		vplmn_lipa_allw: VPLMN-LIPA-Allowed */
/*		rly_ind: Relay-Node-Indicator*/
/*		mdt_usr_cnst: MDT-User-Consent*/
/*		subsc_vsrvcc: Subscribed-VSRVCC*/
/*		prose_subsc_dt: ProSe-Subscription-Data*/
/*		subsc_dt_flgs: Subscription-Data-Flags */
struct subsc_data{
	enum subc_status * subc_st; 
	octetstring * msisdn;  
	octetstring * a_msisdn;  
	octetstring * stn_sr; 
	enum ics_indic * ics_ind; 
	enum net_acc_mod * net_acc_mod;
	unsigned32 * odb;
	unsigned32 * hplmn_odb;
	struct reg_subsc_zn_cd * rg_zn_cd; 
	unsigned32 * acc_restr_dt;  
	utf8string * apn_oi_repl;
	struct lcs_info * lcs_inf; 
	struct tele_srv * tele_srv;  
	struct call_bar_inf * call_br_inf;
	utf8string * charg_char;  
	struct ambr * ambr; 
	struct apn_conf_prf * apn_cnf_prf;
	unsigned32 * rat_frq_sel_pri_id;
	struct trace_data * trc_dt;
	struct gprs_subsc_dt * gprs_sub_dt;
	struct csg_subsc_dt * csg_sub_dt; 
	enum roam_restr_unsuppr * roam_restr;
	unsigned32 * subcd_rau_tau_tmr;
	unsigned32 * mps_prio;
	enum vplmn_lipa_allw * vplmn_lipa_allw;
	enum relay_nod_ind * rly_ind;
	enum mdt_usr_consent * mdt_usr_cnst;
	enum subsc_vsrvcc * subsc_vsrvcc;
	struct prose_subsc_dt * prose_subsc_dt;
	unsigned32 * subsc_dt_flgs;
};

/*struct reset_id: concatinated Reset-ID AVPs   	       */
/*		id: Reset-ID								   	   */
/*		next: the next Reset-ID or NULL is it the last one */
struct reset_id{
	octetstring * id;

	struct reset_id * next;
};

/*struct req_auth_info: Requested-EUTRAN-Authentication-Info or Requested-UTRAN-GERAN-Authentication-Info :/ */
/*		num_req_vect: Number-Of-Requested-Vectors*/
/*		immd_resp_pref: Immediate-Response-Preferred*/
/*		re_sync_inf: Re-synchronization-Info*/
struct req_auth_info{
	unsigned32 * num_req_vect;
	unsigned32 * immd_resp_pref;
	octetstring * re_sync_inf;
};

/*struct eutran_vect: E-UTRAN-Vector*/
/*		itm_num: Item-Number*/
/*		rand: RAND*/
/*		xres: XRES */
/*		autn: AUTN*/
/*		kasme:  KASME*/
struct eutran_vect{
	unsigned32 * itm_num;
	octetstring * rand; 
	octetstring * xres; 
	octetstring * autn; 
	octetstring * kasme;

	struct eutran_vect * next;
};

/*struct utran_vect: UTRAN-Vector*/
/*		itm_num: Item-Number*/
/*		rand: RAND*/
/*		xres: XRES */
/*		autn: AUTN*/
/*		confd_key: Confidentiality-Key*/
/*		intgy_key: Integrity-Key*/
struct utran_vect{
	unsigned32 * itm_num;
	octetstring * rand; 
	octetstring * xres; 
	octetstring * autn; 
	octetstring * confd_key; 
	octetstring * intgy_key;

	struct utran_vect * next;
};

/*struct geran_vect: GERAN-Vector*/
/*		itm_num: Item-Number*/
/*		rand: RAND*/
/*		xres: XRES */
/*		kc: Kc*/
struct geran_vect{
	unsigned32 * itm_num;
	octetstring * rand; 
	octetstring * xres; 
	octetstring * kc; 

	struct geran_vect * next;
};
/*struct auth_info: Authentication-Info */
/*		eutran_vct: E-UTRAN-Vector*/
/*		utran_vct: UTRAN-Vector*/
/*		geran_vct: GERAN-Vector*/
struct auth_info{
	struct eutran_vect * eutran_vct;
	struct utran_vect * utran_vct;
	struct utran_vect * geran_vct;
};

struct exprm_result{
	unsigned32 * vend_id;
	unsigned32 * res_cd;
};

/*struct mme_sgns_usr_state : MME-User-State OR SGSN-User-State*/
/*		usr_st: User-State*/
struct mme_sgns_usr_state{
	enum user_state * usr_st;
};

/*struct eps_usr_state: EPS-User-State*/
/*		mme_usr_st: MME-User-State*/
/*		sgsn_usr_st: SGSN-User-State*/
struct eps_usr_state{
	struct mme_sgns_usr_state * mme_usr_st;
	struct mme_sgns_usr_state * sgsn_usr_st;
};

/*struct usr_csg_info: User-CSG-Information*/
/*		csg_id: CSG-Id						*/
/*		accs_mod: CSG-Access-Mode			*/
/*		memb_ind: CSG-Membership-Indication*/
struct usr_csg_info{
	unsigned32 * csg_id;
	enum csg_accs_mode * accs_mod;
	enum csg_memb_ind * memb_ind;
};

/*struct mme_loc_info: MME-Location-Information		*/	
/*		eutran_cgi: E-UTRAN-Cell-Global-Identity	*/
/*		trak_area_id: Tracking-Area-Identity		*/
/*		geog_inf: Geographical-Information			*/
/*		geod_inf: Geodetic-Information				*/
/*		curr_loc_ret: Current-Location-Retrieved	*/
/*		age_loc_inf: Age-Of-Location-Information	*/
/*		ust_csg_inf: User-CSG-Information			*/
struct mme_loc_info{
	octetstring * eutran_cgi;
	octetstring * trak_area_id;
	octetstring * geog_inf;
	octetstring * geod_inf;
	enum curr_loc_retr * curr_loc_ret;
	unsigned32 * age_loc_inf;
	struct usr_csg_info * ust_csg_inf;
};

/*struct sgsn_loc_info: SGSN-Location-Information	*/
/*		cgi: Cell-Global-Identity					*/
/*		lai: Location-Area-Identity					*/
/*		sai: Service-Area-Identity					*/
/*		rai: Routing-Area-Identity					*/
/*		geog_inf: Geographical-Information			*/
/*		geod_inf: Geodetic-Information				*/
/*		curr_loc_ret: Current-Location-Retrieved	*/
/*		age_loc_inf: Age-Of-Location-Information	*/
/*		ust_csg_inf: User-CSG-Information			*/
struct sgsn_loc_info{
	octetstring * cgi;
	octetstring * lai;
	octetstring * sai;
	octetstring * rai;
	octetstring * geog_inf;
	octetstring * geod_inf;
	enum curr_loc_retr * curr_loc_ret;
	unsigned32 * age_loc_inf;
	struct usr_csg_info * ust_csg_inf;
};

/*struct eps_loc_info: EPS-Location-Information	*/
/*		mme_loc_inf: MME-Location-Information	*/
/*		sgns_loc_inf: SGSN-Location-Information */
struct eps_loc_info{
	struct mme_loc_info * mme_loc_inf;
	struct sgsn_loc_info * sgns_loc_inf;
};

/*struct local_time_zone: Local-Time-Zone	*/
/*		tm_zn: Time-Zone					*/
/*		dy_sv_tm: Daylight-Saving-Time		*/
struct local_time_zone{
	utf8string * tm_zn;
	enum day_save_time * dy_sv_tm;
};

/*struct context_identifier: concatinated Context-Identifier AVPs     */
/*		id: Context-Identifier								   	      */
/*		next: the next Context-Identifier or NULL is it the last one  */
struct context_identifier{
	unsigned32 * id;

	struct context_identifier * next;
};

/*struct ss_code: concatinated SS-Code AVPs   	       	   */
/*		code: SS-Code								   	   */
/*		next: the next SS-Code or NULL is it the last one  */
struct ss_code{
	octetstring * code;

	struct ss_code * next;	
};

/*struct user_id: concatinated User-Id AVPs   	       	   */
/*		id: User-Id									   	   */
/*		next: the next User-Id or NULL is it the last one  */
struct user_id{
	utf8string * id;
	
	struct user_id * next;
};
/*struct ulr_msg: contains the avps defined in update-location-request message*/
/*		dst_host: Destination-Host				*/
/*		dst_realm: Destination-Realm			*/
/*		usr_name: User-Name						*/
/*		suprt_ftr: Supported-Features			*/
/*		term_info: Terminal-Information*/
/*		rat_type: RAT-Type*/
/*		ulr_flg: ULR-Flags*/
/*		ue_srvcc: UE-SRVCC-Capability*/
/*		vis_plmn_id: Visited-PLMN-Id*/
/*		sgsn_num: SGSN-Number*/
/*		hm_ims_vop: Homogeneous-Support-of-IMS-Voice-Over-PS-Session*/
/*		gmlc_addr: GMLC-Address*/
/*		act_apn: Active-APN*/
/*		plmn_lst: Equivalent-PLMN-List*/
/*		mme_num_mtsmsm: MME-Number-for-MT-SMS*/
/*		sms_reg: SMS-Register-Request */
/*		coupl_nd_dia_id: Coupled-Node-Diameter-ID */
struct ulr_msg{ 
	diameterid * dst_host;
	diameterid * dst_realm;
	utf8string * usr_name;
	struct suprt_feature *suprt_ftr;
    struct terminal_info *term_info;
	enum rat_type * rat_type;
	unsigned32 * ulr_flg;
	enum ue_srvcc_cap * ue_srvcc;
	octetstring * vis_plmn_id;
	octetstring * sgsn_num;
	enum hm_suprt_ims_vop_sess * hm_ims_vop;
	address * gmlc_addr;
	struct active_apn * act_apn; 
	struct eqv_plmn_lst * eqv_plmn_lst;
	octetstring * mme_num_mtsmsm;
	enum sms_reg_req * sms_reg;
	diameterid * coupl_nd_dia_id;
};

/*struct ula_msg: Update-Location-Answer*/
/*		res_cd: Result-Code */
/*		expr_res: Experimental-Result*/
/*		err_dg: Error-Diagnostic*/
/*		orig_hst: Origin-Host*/
/*		orig_rlm: Origin-Realm */
/*		suprt_ftr: Supported-Features*/
/*		ula_flg: ULA-Flags*/
/*		subc_dt: Subscription-Data*/
/*		rst_id: Reset-ID*/
struct ula_msg{
	unsigned32 * res_cd;
	struct exprm_result * expr_res;
	enum err_diagn * err_dg;
	diameterid * orig_hst;
	diameterid * orig_rlm;
	struct suprt_feature * suprt_ftr;
	unsigned32 * ula_flg; 
	struct subsc_data * subc_dt;
	struct reset_id * rst_id;
};
/*struct air_msg:  Authentication-Information-Request*/
/*		dst_host: Destination-Host				*/
/*		dst_realm: Destination-Realm			*/
/*		usr_name: User-Name						*/
/*		suprt_ftr: Supported-Features			*/
/*		req_eutran_auth: Requested-EUTRAN-Authentication-Info*/
/*		req_utran_geran_auth: Requested-UTRAN-GERAN-Authentication-Info*/
/*		vis_plmn_id: Visited-PLMN-Id*/
struct air_msg{
	diameterid * dst_host;
	diameterid * dst_realm;
	utf8string * usr_name; 
	struct suprt_feature *suprt_ftr;/*If more than one Supported-Features occurs in a message, concatenate it*/
	struct req_auth_info * req_eutran_auth;
	struct req_auth_info * req_utran_geran_auth;
	octetstring * vis_plmn_id;
};

/*struct aia_msg: Authentication-Information-Answer*/
/*		res_cd: Result-Code */
/*		expr_res: Experimental-Result*/
/*		err_dg: Error-Diagnostic*/
/*		orig_hst: Origin-Host*/
/*		orig_rlm: Origin-Realm */
/*		suprt_ftr: Supported-Features*/
/*		auth_inf: Authentication-Info*/
struct aia_msg{
	unsigned32 * res_cd;
	struct exprm_result * expr_res;
	enum err_diagn * err_dg;
	diameterid * orig_hst;
	diameterid * orig_rlm;
	struct suprt_feature *suprt_ftr;
	struct auth_info * auth_inf;
};

/*struct clr_msg: Cancel-Location-Request	*/
/*		dst_host: Destination-Host				*/
/*		dst_realm: Destination-Realm			*/
/*		usr_name: User-Name						*/
/*		suprt_ftr: Supported-Features			*/
/*		canc_typ: Cancellation-Type 		*/
/*		clr_flgs: CLR-Flags             	*/
struct clr_msg{
	diameterid * dst_host;
	diameterid * dst_realm;
	utf8string * usr_name; 
	struct suprt_feature *suprt_ftr;
	enum cancel_typ * canc_typ;
	unsigned32 * clr_flgs;
};

/*struct cla_msg: Cancel-Location-Answer*/
/*		suprt_ftr: Supported-Features*/
/*		res_cd: Result-Code */
/*		expr_res: Experimental-Result*/
/*		orig_hst: Origin-Host*/
/*		orig_rlm: Origin-Realm */
struct cla_msg{
	struct suprt_feature *suprt_ftr;
	unsigned32 * res_cd;
	struct exprm_result * expr_res;
	diameterid * orig_hst;
	diameterid * orig_rlm; 
};

/*struct idr_msg: Insert-Subscriber-Data-Request*/
/*		dst_host: Destination-Host				*/
/*		dst_realm: Destination-Realm			*/
/*		usr_name: User-Name						*/
/*		suprt_ftr: Supported-Features			*/
/*		subc_dt: Subscription-Data*/
/*		idr_flgs: IDR- Flags*/
/*		rst_id: Reset-ID*/
struct idr_msg{
	diameterid * dst_host;
	diameterid * dst_realm;
	utf8string * usr_name; 
	struct suprt_feature *suprt_ftr;/*If more than one Supported-Features occurs in a message, concatenate it*/
	struct subsc_data * subc_dt;
	unsigned32 * idr_flgs;
	struct reset_id * rst_id;
};

/*struct ida_msg:  Insert-Subscriber-Data-Answer	*/
/*		suprt_ftr: Supported-Features*/
/*		res_cd: Result-Code */
/*		expr_res: Experimental-Result*/
/*		orig_hst: Origin-Host*/
/*		orig_rlm: Origin-Realm */
/*		ims_voips:	IMS-Voice-Over-PS-Sessions-Supported*/
/*		last_ue_act_tm: Last-UE-Activity-Time */
/*		rat_type:  RAT-Type */
/*		ida_flgs: IDA-Flags */
/*		eps_usr_st: EPS-User-State */
/*		eps_loc_inf: EPS-Location-Information */
/*		lcl_tm_zn: Local-Time-Zone*/
struct ida_msg{
	struct suprt_feature *suprt_ftr;
	unsigned32 * res_cd;
	struct exprm_result * expr_res;
	diameterid * orig_hst;
	diameterid * orig_rlm;
	enum ims_vops_sess_suprt * ims_voips; 
	ss_time * last_ue_act_tm;
	enum rat_type * rat_type;
	unsigned32 * ida_flgs;
	struct eps_usr_state * eps_usr_st;
	struct eps_loc_info * eps_loc_inf;
	struct local_time_zone * lcl_tm_zn;
};

/*struct dsr_msg: Delete-Subscriber-Data-Request*/
/*		dst_host: Destination-Host				*/
/*		dst_realm: Destination-Realm			*/
/*		usr_name: User-Name						*/
/*		suprt_ftr: Supported-Features			*/
/*		dsr_flgs: DSR-Flags						*/
/*		cntx_id: Context-Identifier				*/
/*		trc_ref: Trace-Reference				*/
/*		ts_cd: TS-Code							*/
/*		ss_cd: SS-Code							*/
struct dsr_msg{
	diameterid * dst_host;
	diameterid * dst_realm;
	utf8string * usr_name; 
	struct suprt_feature *suprt_ftr;
	unsigned32 * dsr_flgs;
	struct context_identifier * cntx_id;
	octetstring * trc_ref;
	struct ts_code * ts_cd;
	struct ss_code * ss_cd;
};

/*struct dsa_msg:  Delete-Subscriber-Data-Answer*/
/*		suprt_ftr: Supported-Features			*/
/*		res_cd: Result-Code						*/
/*		expr_res: Experimental-Result			*/
/*		orig_hst: Origin-Host					*/
/*		orig_rlm: Origin-Realm					*/
/*		dsa_flgs: DSA-Flags						*/
struct dsa_msg{
	struct suprt_feature *suprt_ftr;
	unsigned32 * res_cd;
	struct exprm_result * expr_res;
	diameterid * orig_hst;
	diameterid * orig_rlm;
	unsigned32 * dsa_flgs;
};

/*struct pur_msg: Purge-UE-Request 				*/
/*		dst_host: Destination-Host				*/
/*		dst_realm: Destination-Realm			*/
/*		usr_name: User-Name						*/
/*		pur_flgs: PUR-Flags						*/
/*		suprt_ftr: Supported-Features			*/
/*		eps_lc_inf: EPS-Location-Information	*/
struct pur_msg{
	diameterid * dst_host;
	diameterid * dst_realm;
	utf8string * usr_name; 
	unsigned32 * pur_flgs;
	struct suprt_feature *suprt_ftr;
	struct eps_loc_info * eps_lc_inf;
};

/*struct pua_msg:  Purge-UE-Answer		*/
/*		suprt_ftr: Supported-Features	*/
/*		res_cd: Result-Code				*/
/*		expr_res: Experimental-Result	*/
/*		orig_hst: Origin-Host			*/
/*		orig_rlm: Origin-Realm			*/
/*		pua_flgs: PUA-Flags				*/
struct pua_msg{
	struct suprt_feature *suprt_ftr;
	unsigned32 * res_cd;
	struct exprm_result * expr_res;
	diameterid * orig_hst;
	diameterid * orig_rlm;
	unsigned32 * pua_flgs;
};

/*struct rsr_msg: Reset-Request			*/
/*		dst_host: Destination-Host		*/
/*		dst_realm: Destination-Realm	*/
/*		suprt_ftr: Supported-Features	*/
/*		usr_id: User-Id					*/
/*		rst_id: Reset-ID				*/
struct rsr_msg{
	diameterid * dst_host;
	diameterid * dst_realm;
	struct suprt_feature *suprt_ftr;
	struct user_id * usr_id;
	struct reset_id * rst_id;
};

/*struct rsa_msg: Reset-Answer			*/
/*		suprt_ftr: Supported-Features	*/
/*		res_cd: Result-Code				*/
/*		expr_res: Experimental-Result	*/
/*		orig_hst: Origin-Host			*/
/*		orig_rlm: Origin-Realm			*/
struct rsa_msg{
	struct suprt_feature *suprt_ftr;
	unsigned32 * res_cd;
	struct exprm_result * expr_res;
	diameterid * orig_hst;
	diameterid * orig_rlm;
};

/*struct nor_msg: Notify-Request 				*/
/*		dst_host: Destination-Host				*/
/*		dst_realm: Destination-Realm			*/
/*		usr_name: User-Name						*/
/*		suprt_ftr: Supported-Features			*/
/*		term_info: Terminal-Information			*/
/*		mip6_agt_inf: MIP6-Agent-Info			*/
/*		vist_net_id: Visited-Network-Identifier	*/
/*		contxt_id: Context-Identifier			*/
/*		serv_sel: Service-Selection				*/
/*		alrt_reasn: Alert-Reason				*/
/*		ue_srvcc: UE-SRVCC-Capability			*/
/*		nor_flgs: NOR-Flags						*/
/*		hm_ims_vop: Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions */
struct nor_msg{
	diameterid * dst_host;
	diameterid * dst_realm;
	utf8string * usr_name; 
	struct suprt_feature *suprt_ftr;
	struct terminal_info *term_info;
	struct mip6_agent_info * mip6_agt_inf;  
	octetstring * vist_net_id;
	unsigned32 * contxt_id;
 	utf8string * serv_sel;
	enum alert_reason * alrt_reasn;
	enum ue_srvcc_cap * ue_srvcc;
	unsigned32 * nor_flgs;
	enum hm_suprt_ims_vop_sess * hm_ims_vop;
};

/*struct noa_msg: Notify-Answer			*/
/*		res_cd: Result-Code				*/
/*		expr_res: Experimental-Result	*/
/*		orig_hst: Origin-Host			*/
/*		orig_rlm: Origin-Realm			*/
/*		suprt_ftr: Supported-Features	*/
struct noa_msg{
	unsigned32 * res_cd;
	struct exprm_result * expr_res;
	diameterid * orig_hst;
	diameterid * orig_rlm;
	struct suprt_feature *suprt_ftr;
};

/*extern diameterid * dest_realm; */

/*int init_ssix():*/
/*	Initializes the diameter protocol.*/
/*	It parses the configuration file and initialize global variables based on*/
/*	the values in the configration file. It creats a connection with peers*/
/*	given in the confguration file.*/
int ss_init();

/*Waites untill the diameter application gracefully shuts down */
void  ss_wait_shutdown();

int ss_req( enum s6_cmd cmd, void *msg);

#endif
