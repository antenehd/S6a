
#include "internal.h"

/*This file contains AVP definition required for S6a interface. Most of the definitions are copied from freeDiameter
  implementation. Specifically from freediameter extentions 'dict_dcca_3gpp', 'dict_dcca_3gpp' and 'dict_nasreq'*/

/*the following two macros is copied form freediameter 'dict_dcca_3gpp.c'*/
#define CHECK_dict_new( _type, _data, _parent, _ref )	\
	CHECK_FCT(  fd_dict_new( fd_g_config->cnf_dict, (_type), (_data), (_parent), (_ref))  );
#define CHECK_dict_search( _type, _criteria, _what, _result )	\
	CHECK_FCT(  fd_dict_search( fd_g_config->cnf_dict, (_type), (_criteria), (_what), (_result), ENOENT) );

/*Loads the AVP definition required for S6a interface*/
int ss_dict_load_dict(){
	
	/********  START of copy of definitions Copied from freediameter 'dict_dcca_3gpp.c' ************************/

	/*The following definitions until the comment 'END of copy from dict_dcca_3gpp.c' is copied from 'dict_dcca_3gpp.c'*/

	/* Create the vendor */    
	struct dict_vendor_data vendor_data = { 10415, "3GPP" };
    CHECK_FCT(fd_dict_new(fd_g_config->cnf_dict, DICT_VENDOR, &vendor_data, NULL, NULL));
   
	struct dict_object * Address_type;
	struct dict_object * DiameterIdentity_type;
	struct dict_object * DiameterURI_type;
	struct dict_object * IPFilterRule_type;
	struct dict_object * Time_type;
	struct dict_object * UTF8String_type;

	CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "Address", &Address_type);
	CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "DiameterIdentity", &DiameterIdentity_type);
	CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "DiameterURI", &DiameterURI_type);
	CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "IPFilterRule", &IPFilterRule_type);
	CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "Time", &Time_type);
	CHECK_dict_search( DICT_TYPE, TYPE_BY_NAME, "UTF8String", &UTF8String_type);
	
	/* Supported-Features */
	{
		struct dict_avp_data data = {
			628,	/* Code */
			10415,	/* Vendor */
			"Supported-Features",	/* Name */
			AVP_FLAG_VENDOR,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* VPLMN-CSG-Subscription-Data */
	{
		struct dict_avp_data data = {
			1641,	/* Code */
			10415,	/* Vendor */
			"VPLMN-CSG-Subscription-Data",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* User-Id */
	{
		struct dict_avp_data data = {
			1444,	/* Code */
			10415,	/* Vendor */
			"User-Id",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, UTF8String_type, NULL);
	};

	/* Feature-List */
	{
		struct dict_avp_data data = {
			630,	/* Code */
			10415,	/* Vendor */
			"Feature-List",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Feature-List-ID */
	{
		struct dict_avp_data data = {
			629,	/* Code */
			10415,	/* Vendor */
			"Feature-List-ID",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Terminal-Information */
	{
		struct dict_avp_data data = {
			1401,	/* Code */
			10415,	/* Vendor */
			"Terminal-Information",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* RAT-Type */
	{
		struct dict_avp_data data = {
			1032,	/* Code */
			10415,	/* Vendor */
			"RAT-Type",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		struct dict_object		*type;
		struct dict_type_data	 tdata = { AVP_TYPE_INTEGER32, "3GPP/Enumerated(RAT-Type)", NULL, NULL, NULL };
		CHECK_dict_new(DICT_TYPE, &tdata, NULL, &type);
		CHECK_dict_new(DICT_AVP, &data, type, NULL);
	};

	/* Requested-EUTRAN-Authentication-Info */
	{
		struct dict_avp_data data = {
			1408,	/* Code */
			10415,	/* Vendor */
			"Requested-EUTRAN-Authentication-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Requested-UTRAN-GERAN-Authentication-Info */
	{
		struct dict_avp_data data = {
			1409,	/* Code */
			10415,	/* Vendor */
			"Requested-UTRAN-GERAN-Authentication-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Cancellation-Type */
	{
		struct dict_avp_data data = {
			1420,	/* Code */
			10415,	/* Vendor */
			"Cancellation-Type",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* ULR-Flags */
	{
		struct dict_avp_data data = {
			1405,	/* Code */
			10415,	/* Vendor */
			"ULR-Flags",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* ULA-Flags */
	{
		struct dict_avp_data data = {
			1406,	/* Code */
			10415,	/* Vendor */
			"ULA-Flags",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* CLR-Flags */
	{
		struct dict_avp_data data = {
			1638,	/* Code */
			10415,	/* Vendor */
			"CLR-Flags",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* TS-Code */
	{
		struct dict_avp_data data = {
			1487,	/* Code */
			10415,	/* Vendor */
			"TS-Code",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Call-Barring-Info */
	{
		struct dict_avp_data data = {
			1488,	/* Code */
			10415,	/* Vendor */
			"Call-Barring-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* SGSN-Number */
	{
		struct dict_avp_data data = {
			1489,	/* Code */
			10415,	/* Vendor */
			"SGSN-Number",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* IDR-Flags */
	{
		struct dict_avp_data data = {
			1490,	/* Code */
			10415,	/* Vendor */
			"IDR-Flags",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* DSR-Flags */
	{
		struct dict_avp_data data = {
			1421,	/* Code */
			10415,	/* Vendor */
			"DSR-Flags",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* DSA-Flags */
	{
		struct dict_avp_data data = {
			1422,	/* Code */
			10415,	/* Vendor */
			"DSA-Flags",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Context-Identifier */
	{
		struct dict_avp_data data = {
			1423,	/* Code */
			10415,	/* Vendor */
			"Context-Identifier",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Ext-PDP-Address */
	{
		struct dict_avp_data data = {
			1621,	/* Code */
			10415,	/* Vendor */
			"Ext-PDP-Address",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, Address_type, NULL);
	};

	/* Ext-PDP-Type */
	{
		struct dict_avp_data data = {
			1620,	/* Code */
			10415,	/* Vendor */
			"Ext-PDP-Type",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* QoS-Subscribed */
	{
		struct dict_avp_data data = {
			1404,	/* Code */
			10415,	/* Vendor */
			"QoS-Subscribed",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Subscriber-Status */
	{
		struct dict_avp_data data = {
			1424,	/* Code */
			10415,	/* Vendor */
			"Subscriber-Status",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Operator-Determined-Barring */
	{
		struct dict_avp_data data = {
			1425,	/* Code */
			10415,	/* Vendor */
			"Operator-Determined-Barring",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Access-Restriction-Data */
	{
		struct dict_avp_data data = {
			1426,	/* Code */
			10415,	/* Vendor */
			"Access-Restriction-Data",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};
	
	/* PUR-Flags */
	{
		struct dict_avp_data data = {
			1635,	/* Code */
			10415,	/* Vendor */
			"PUR-Flags",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* UE-SRVCC-Capability */
	{
		struct dict_avp_data data = {
			1615,	/* Code */
			10415,	/* Vendor */
			"UE-SRVCC-Capability",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* MPS-Priority */
	{
		struct dict_avp_data data = {
			1616,	/* Code */
			10415,	/* Vendor */
			"MPS-Priority",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* VPLMN-LIPA-Allowed */
	{
		struct dict_avp_data data = {
			1617,	/* Code */
			10415,	/* Vendor */
			"VPLMN-LIPA-Allowed",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* LIPA-Permission */
	{
		struct dict_avp_data data = {
			1618,	/* Code */
			10415,	/* Vendor */
			"LIPA-Permission",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* APN-OI-Replacement */
	{
		struct dict_avp_data data = {
			1427,	/* Code */
			10415,	/* Vendor */
			"APN-OI-Replacement",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, UTF8String_type, NULL);
	};

	/* EPS-Subscribed-QoS-Profile */
	{
		struct dict_avp_data data = {
			1431,	/* Code */
			10415,	/* Vendor */
			"EPS-Subscribed-QoS-Profile",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* QoS-Class-Identifier */
	{
		struct dict_avp_data data = {
			1028,	/* Code */
			10415,	/* Vendor */
			"QoS-Class-Identifier",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* VPLMN-Dynamic-Address-Allowed */
	{
		struct dict_avp_data data = {
			1432,	/* Code */
			10415,	/* Vendor */
			"VPLMN-Dynamic-Address-Allowed",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* STN-SR */
	{
		struct dict_avp_data data = {
			1433,	/* Code */
			10415,	/* Vendor */
			"STN-SR",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Alert-Reason */
	{
		struct dict_avp_data data = {
			1434,	/* Code */
			10415,	/* Vendor */
			"Alert-Reason",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* AMBR */
	{
		struct dict_avp_data data = {
			1435,	/* Code */
			10415,	/* Vendor */
			"AMBR",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* CSG-Subscription-Data */
	{
		struct dict_avp_data data = {
			1436,	/* Code */
			10415,	/* Vendor */
			"CSG-Subscription-Data",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* CSG-Id */
	{
		struct dict_avp_data data = {
			1437,	/* Code */
			10415,	/* Vendor */
			"CSG-Id",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* IDA-Flags */
	{
		struct dict_avp_data data = {
			1441,	/* Code */
			10415,	/* Vendor */
			"IDA-Flags",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* PUA-Flags */
	{
		struct dict_avp_data data = {
			1442,	/* Code */
			10415,	/* Vendor */
			"PUA-Flags",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* NOR-Flags */
	{
		struct dict_avp_data data = {
			1443,	/* Code */
			10415,	/* Vendor */
			"NOR-Flags",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Trace-Data */
	{
		struct dict_avp_data data = {
			1458,	/* Code */
			10415,	/* Vendor */
			"Trace-Data",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Trace-Reference */
	{
		struct dict_avp_data data = {
			1459,	/* Code */
			10415,	/* Vendor */
			"Trace-Reference",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Trace-Depth */
	{
		struct dict_avp_data data = {
			1462,	/* Code */
			10415,	/* Vendor */
			"Trace-Depth",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Trace-NE-Type-List */
	{
		struct dict_avp_data data = {
			1463,	/* Code */
			10415,	/* Vendor */
			"Trace-NE-Type-List",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Trace-Interface-List */
	{
		struct dict_avp_data data = {
			1464,	/* Code */
			10415,	/* Vendor */
			"Trace-Interface-List",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Trace-Event-List */
	{
		struct dict_avp_data data = {
			1465,	/* Code */
			10415,	/* Vendor */
			"Trace-Event-List",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* OMC-Id */
	{
		struct dict_avp_data data = {
			1466,	/* Code */
			10415,	/* Vendor */
			"OMC-Id",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* GPRS-Subscription-Data */
	{
		struct dict_avp_data data = {
			1467,	/* Code */
			10415,	/* Vendor */
			"GPRS-Subscription-Data",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Complete-Data-List-Included-Indicator */
	{
		struct dict_avp_data data = {
			1468,	/* Code */
			10415,	/* Vendor */
			"Complete-Data-List-Included-Indicator",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Expiration-Date */
	{
		struct dict_avp_data data = {
			1439,	/* Code */
			10415,	/* Vendor */
			"Expiration-Date",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, Time_type, NULL);
	};

	/* PDP-Address */
	{
		struct dict_avp_data data = {
			1227,	/* Code */
			10415,	/* Vendor */
			"PDP-Address",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, Address_type, NULL);
	};

	/* PDP-Context */
	{
		struct dict_avp_data data = {
			1469,	/* Code */
			10415,	/* Vendor */
			"PDP-Context",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* PDP-Type */
	{
		struct dict_avp_data data = {
			1470,	/* Code */
			10415,	/* Vendor */
			"PDP-Type",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* 3GPP2-MEID */
	{
		struct dict_avp_data data = {
			1471,	/* Code */
			10415,	/* Vendor */
			"3GPP2-MEID",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Specific-APN-Info */
	{
		struct dict_avp_data data = {
			1472,	/* Code */
			10415,	/* Vendor */
			"Specific-APN-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* LCS-Info */
	{
		struct dict_avp_data data = {
			1473,	/* Code */
			10415,	/* Vendor */
			"LCS-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Visited-Network-Identifier */
	{
		struct dict_avp_data data = {
			600,	/* Code */
			10415,	/* Vendor */
			"Visited-Network-Identifier",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};
	
	/* ICS-Indicator */
	{
		struct dict_avp_data data = {
			1491,	/* Code */
			10415,	/* Vendor */
			"ICS-Indicator",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		struct dict_object		*type;
		struct dict_type_data	 tdata = { AVP_TYPE_INTEGER32, "3GPP/Enumerated(ICS-Indicator)", NULL, NULL, NULL };
		CHECK_dict_new(DICT_TYPE, &tdata, NULL, &type);
		CHECK_dict_new(DICT_AVP, &data, type, NULL);
	};

	/* GMLC-Number */
	{
		struct dict_avp_data data = {
			1474,	/* Code */
			10415,	/* Vendor */
			"GMLC-Number",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* GMLC-Address */
	{
		struct dict_avp_data data = {
			2405,	/* Code */
			10415,	/* Vendor */
			"GMLC-Address",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, Address_type, NULL);
	};

	/* LCS-PrivacyException */
	{
		struct dict_avp_data data = {
			1475,	/* Code */
			10415,	/* Vendor */
			"LCS-PrivacyException",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* SS-Code */
	{
		struct dict_avp_data data = {
			1476,	/* Code */
			10415,	/* Vendor */
			"SS-Code",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Notification-To-UE-User */
	{
		struct dict_avp_data data = {
			1478,	/* Code */
			10415,	/* Vendor */
			"Notification-To-UE-User",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* External-Client */
	{
		struct dict_avp_data data = {
			1479,	/* Code */
			10415,	/* Vendor */
			"External-Client",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Client-Identity */
	{
		struct dict_avp_data data = {
			1480,	/* Code */
			10415,	/* Vendor */
			"Client-Identity",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* GMLC-Restriction */
	{
		struct dict_avp_data data = {
			1481,	/* Code */
			10415,	/* Vendor */
			"GMLC-Restriction",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* PLMN-Client */
	{
		struct dict_avp_data data = {
			1482,	/* Code */
			10415,	/* Vendor */
			"PLMN-Client",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Service-Type */
	{
		struct dict_avp_data data = {
			1483,	/* Code */
			10415,	/* Vendor */
			"Service-Type",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* ServiceTypeIdentity */
	{
		struct dict_avp_data data = {
			1484,	/* Code */
			10415,	/* Vendor */
			"ServiceTypeIdentity",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Visited-PLMN-Id */
	{
		struct dict_avp_data data = {
			1407,	/* Code */
			10415,	/* Vendor */
			"Visited-PLMN-Id",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* IMS-Voice-Over-PS-Sessions-Supported */
	{
		struct dict_avp_data data = {
			1492,	/* Code */
			10415,	/* Vendor */
			"IMS-Voice-Over-PS-Sessions-Supported",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* MO-LR */
	{
		struct dict_avp_data data = {
			1485,	/* Code */
			10415,	/* Vendor */
			"MO-LR",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions */
	{
		struct dict_avp_data data = {
			1493,	/* Code */
			10415,	/* Vendor */
			"Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Last-UE-Activity-Time */
	{
		struct dict_avp_data data = {
			1494,	/* Code */
			10415,	/* Vendor */
			"Last-UE-Activity-Time",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, Time_type, NULL);
	};

	/* EPS-User-State */
	{
		struct dict_avp_data data = {
			1495,	/* Code */
			10415,	/* Vendor */
			"EPS-User-State",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* EPS-Location-Information */
	{
		struct dict_avp_data data = {
			1496,	/* Code */
			10415,	/* Vendor */
			"EPS-Location-Information",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* MME-User-State */
	{
		struct dict_avp_data data = {
			1497,	/* Code */
			10415,	/* Vendor */
			"MME-User-State",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* SGSN-User-State */
	{
		struct dict_avp_data data = {
			1498,	/* Code */
			10415,	/* Vendor */
			"SGSN-User-State",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* User-State */
	{
		struct dict_avp_data data = {
			1499,	/* Code */
			10415,	/* Vendor */
			"User-State",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* MME-Location-Information */
	{
		struct dict_avp_data data = {
			1600,	/* Code */
			10415,	/* Vendor */
			"MME-Location-Information",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* SGSN-Location-Information */
	{
		struct dict_avp_data data = {
			1601,	/* Code */
			10415,	/* Vendor */
			"SGSN-Location-Information",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* E-UTRAN-Cell-Global-Identity */
	{
		struct dict_avp_data data = {
			1602,	/* Code */
			10415,	/* Vendor */
			"E-UTRAN-Cell-Global-Identity",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Tracking-Area-Identity */
	{
		struct dict_avp_data data = {
			1603,	/* Code */
			10415,	/* Vendor */
			"Tracking-Area-Identity",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Cell-Global-Identity */
	{
		struct dict_avp_data data = {
			1604,	/* Code */
			10415,	/* Vendor */
			"Cell-Global-Identity",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Routing-Area-Identity */
	{
		struct dict_avp_data data = {
			1605,	/* Code */
			10415,	/* Vendor */
			"Routing-Area-Identity",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Location-Area-Identity */
	{
		struct dict_avp_data data = {
			1606,	/* Code */
			10415,	/* Vendor */
			"Location-Area-Identity",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Service-Area-Identity */
	{
		struct dict_avp_data data = {
			1607,	/* Code */
			10415,	/* Vendor */
			"Service-Area-Identity",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Geographical-Information */
	{
		struct dict_avp_data data = {
			1608,	/* Code */
			10415,	/* Vendor */
			"Geographical-Information",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Geodetic-Information */
	{
		struct dict_avp_data data = {
			1609,	/* Code */
			10415,	/* Vendor */
			"Geodetic-Information",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Current-Location-Retrieved */
	{
		struct dict_avp_data data = {
			1610,	/* Code */
			10415,	/* Vendor */
			"Current-Location-Retrieved",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* CSG-Access-Mode */
	{
		struct dict_avp_data data = {
			2317,	/* Code */
			10415,	/* Vendor */
			"CSG-Access-Mode",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* CSG-Membership-Indication */
	{
		struct dict_avp_data data = {
			2318,	/* Code */
			10415,	/* Vendor */
			"CSG-Membership-Indication",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Age-Of-Location-Information */
	{
		struct dict_avp_data data = {
			1611,	/* Code */
			10415,	/* Vendor */
			"Age-Of-Location-Information",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* User-CSG-Information */
	{
		struct dict_avp_data data = {
			2319,	/* Code */
			10415,	/* Vendor */
			"User-CSG-Information",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Active-APN */
	{
		struct dict_avp_data data = {
			1612,	/* Code */
			10415,	/* Vendor */
			"Active-APN",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Time-Zone */
	{
		struct dict_avp_data data = {
			1642,	/* Code */
			10415,	/* Vendor */
			"Time-Zone",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, UTF8String_type, NULL);
	};

	/* A-MSISDN */
	{
		struct dict_avp_data data = {
			1643,	/* Code */
			10415,	/* Vendor */
			"A-MSISDN",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* MME-Number-for-MT-SMS */
	{
		struct dict_avp_data data = {
			1645,	/* Code */
			10415,	/* Vendor */
			"MME-Number-for-MT-SMS",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* SMS-Register-Request */
	{
		struct dict_avp_data data = {
			1648,	/* Code */
			10415,	/* Vendor */
			"SMS-Register-Request",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Local-Time-Zone */
	{
		struct dict_avp_data data = {
			1649,	/* Code */
			10415,	/* Vendor */
			"Local-Time-Zone",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Daylight-Saving-Time */
	{
		struct dict_avp_data data = {
			1650,	/* Code */
			10415,	/* Vendor */
			"Daylight-Saving-Time",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Subscription-Data-Flags */
	{
		struct dict_avp_data data = {
			1654,	/* Code */
			10415,	/* Vendor */
			"Subscription-Data-Flags",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Measurement-Period-UMTS */
	{
		struct dict_avp_data data = {
			1655,	/* Code */
			10415,	/* Vendor */
			"Measurement-Period-UMTS",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		struct dict_object		*type;
		struct dict_type_data	 tdata = { AVP_TYPE_INTEGER32, "3GPP/Enumerated(Measurement-Period-UMTS)", NULL, NULL, NULL };
		CHECK_dict_new(DICT_TYPE, &tdata, NULL, &type);
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Measurement-Period-LTE */
	{
		struct dict_avp_data data = {
			1656,	/* Code */
			10415,	/* Vendor */
			"Measurement-Period-LTE",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Collection-Period-RRM-LTE */
	{
		struct dict_avp_data data = {
			1657,	/* Code */
			10415,	/* Vendor */
			"Collection-Period-RRM-LTE",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Collection-Period-RRM-UMTS */
	{
		struct dict_avp_data data = {
			1658,	/* Code */
			10415,	/* Vendor */
			"Collection-Period-RRM-UMTS",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Positioning-Method */
	{
		struct dict_avp_data data = {
			1659,	/* Code */
			10415,	/* Vendor */
			"Positioning-Method",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Measurement-Quantity */
	{
		struct dict_avp_data data = {
			1660,	/* Code */
			10415,	/* Vendor */
			"Measurement-Quantity",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Event-Threshold-Event-1F */
	{
		struct dict_avp_data data = {
			1661,	/* Code */
			10415,	/* Vendor */
			"Event-Threshold-Event-1F",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Event-Threshold-Event-1I */
	{
		struct dict_avp_data data = {
			1662,	/* Code */
			10415,	/* Vendor */
			"Event-Threshold-Event-1I",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Error-Diagnostic */
	{
		struct dict_avp_data data = {
			1614,	/* Code */
			10415,	/* Vendor */
			"Error-Diagnostic",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Subscription-Data */
	{
		struct dict_avp_data data = {
			1400,	/* Code */
			10415,	/* Vendor */
			"Subscription-Data",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Requested-EUTRAN-Authentication-Info */
	{
		struct dict_avp_data data = {
			1408,	/* Code */
			10415,	/* Vendor */
			"Requested-EUTRAN-Authentication-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Requested-UTRAN-GERAN-Authentication-Info */
	{
		struct dict_avp_data data = {
			1409,	/* Code */
			10415,	/* Vendor */
			"Requested-UTRAN-GERAN-Authentication-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Number-Of-Requested-Vectors */
	{
		struct dict_avp_data data = {
			1410,	/* Code */
			10415,	/* Vendor */
			"Number-Of-Requested-Vectors",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Re-Synchronization-Info */
	{
		struct dict_avp_data data = {
			1411,	/* Code */
			10415,	/* Vendor */
			"Re-Synchronization-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Immediate-Response-Preferred */
	{
		struct dict_avp_data data = {
			1412,	/* Code */
			10415,	/* Vendor */
			"Immediate-Response-Preferred",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Authentication-Info */
	{
		struct dict_avp_data data = {
			1413,	/* Code */
			10415,	/* Vendor */
			"Authentication-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* E-UTRAN-Vector */
	{
		struct dict_avp_data data = {
			1414,	/* Code */
			10415,	/* Vendor */
			"E-UTRAN-Vector",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* UTRAN-Vector */
	{
		struct dict_avp_data data = {
			1415,	/* Code */
			10415,	/* Vendor */
			"UTRAN-Vector",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* GERAN-Vector */
	{
		struct dict_avp_data data = {
			1416,	/* Code */
			10415,	/* Vendor */
			"GERAN-Vector",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Network-Access-Mode */
	{
		struct dict_avp_data data = {
			1417,	/* Code */
			10415,	/* Vendor */
			"Network-Access-Mode",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* HPLMN-ODB */
	{
		struct dict_avp_data data = {
			1418,	/* Code */
			10415,	/* Vendor */
			"HPLMN-ODB",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Item-Number */
	{
		struct dict_avp_data data = {
			1419,	/* Code */
			10415,	/* Vendor */
			"Item-Number",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Regional-Subscription-Zone-Code */
	{
		struct dict_avp_data data = {
			1446,	/* Code */
			10415,	/* Vendor */
			"Regional-Subscription-Zone-Code",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* RAND */
	{
		struct dict_avp_data data = {
			1447,	/* Code */
			10415,	/* Vendor */
			"RAND",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* XRES */
	{
		struct dict_avp_data data = {
			1448,	/* Code */
			10415,	/* Vendor */
			"XRES",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* AUTN */
	{
		struct dict_avp_data data = {
			1449,	/* Code */
			10415,	/* Vendor */
			"AUTN",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* KASME */
	{
		struct dict_avp_data data = {
			1450,	/* Code */
			10415,	/* Vendor */
			"KASME",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Trace-Collection-Entity */
	{
		struct dict_avp_data data = {
			1452,	/* Code */
			10415,	/* Vendor */
			"Trace-Collection-Entity",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, Address_type, NULL);
	};

	/* Kc */
	{
		struct dict_avp_data data = {
			1453,	/* Code */
			10415,	/* Vendor */
			"Kc",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* SRES */
	{
		struct dict_avp_data data = {
			1454,	/* Code */
			10415,	/* Vendor */
			"SRES",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* PDN-Type */
	{
		struct dict_avp_data data = {
			1456,	/* Code */
			10415,	/* Vendor */
			"PDN-Type",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Roaming-Restricted-Due-To-Unsupported-Feature */
	{
		struct dict_avp_data data = {
			1457,	/* Code */
			10415,	/* Vendor */
			"Roaming-Restricted-Due-To-Unsupported-Feature",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Trace-Data */
	{
		struct dict_avp_data data = {
			1458,	/* Code */
			10415,	/* Vendor */
			"Trace-Data",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Integrity-Key */
	{
		struct dict_avp_data data = {
			626,	/* Code */
			10415,	/* Vendor */
			"Integrity-Key",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Confidentiality-Key */
	{
		struct dict_avp_data data = {
			625,	/* Code */
			10415,	/* Vendor */
			"Confidentiality-Key",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* IMEI */
	{
		struct dict_avp_data data = {
			1402,	/* Code */
			10415,	/* Vendor */
			"IMEI",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, UTF8String_type, NULL);
	};

	/* Software-Version */
	{
		struct dict_avp_data data = {
			1403,	/* Code */
			10415,	/* Vendor */
			"Software-Version",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, UTF8String_type, NULL);
	};

	/* MSISDN */
	{
		struct dict_avp_data data = {
			701,	/* Code */
			10415,	/* Vendor */
			"MSISDN",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Teleservice-List */
	{
		struct dict_avp_data data = {
			1486,	/* Code */
			10415,	/* Vendor */
			"Teleservice-List",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* 3GPP-Charging-Characteristics */
	{
		struct dict_avp_data data = {
			13,	/* Code */
			10415,	/* Vendor */
			"3GPP-Charging-Characteristics",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, UTF8String_type, NULL);
	};

	/* All-APN-Configurations-Included-Indicator */
	{
		struct dict_avp_data data = {
			1428,	/* Code */
			10415,	/* Vendor */
			"All-APN-Configurations-Included-Indicator",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* APN-Configuration-Profile */
	{
		struct dict_avp_data data = {
			1429,	/* Code */
			10415,	/* Vendor */
			"APN-Configuration-Profile",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* APN-Configuration */
	{
		struct dict_avp_data data = {
			1430,	/* Code */
			10415,	/* Vendor */
			"APN-Configuration",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* RAT-Frequency-Selection-Priority-ID */
	{
		struct dict_avp_data data = {
			1440,	/* Code */
			10415,	/* Vendor */
			"RAT-Frequency-Selection-Priority-ID",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Max-Requested-Bandwidth-DL */
	{
		struct dict_avp_data data = {
			515,	/* Code */
			10415,	/* Vendor */
			"Max-Requested-Bandwidth-DL",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Max-Requested-Bandwidth-UL */
	{
		struct dict_avp_data data = {
			516,	/* Code */
			10415,	/* Vendor */
			"Max-Requested-Bandwidth-UL",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Pre-emption-Capability */
	{
		struct dict_avp_data data = {
			1047,	/* Code */
			10415,	/* Vendor */
			"Pre-emption-Capability",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Pre-emption-Vulnerability */
	{
		struct dict_avp_data data = {
			1048,	/* Code */
			10415,	/* Vendor */
			"Pre-emption-Vulnerability",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Priority-Level */
	{
		struct dict_avp_data data = {
			1046,	/* Code */
			10415,	/* Vendor */
			"Priority-Level",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Subscribed-Periodic-RAU-TAU-Timer */
	{
		struct dict_avp_data data = {
			1619,	/* Code */
			10415,	/* Vendor */
			"Subscribed-Periodic-RAU-TAU-Timer",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* MDT-Configuration */
	{
		struct dict_avp_data data = {
			1622,	/* Code */
			10415,	/* Vendor */
			"MDT-Configuration",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Job-Type */
	{
		struct dict_avp_data data = {
			1623,	/* Code */
			10415,	/* Vendor */
			"Job-Type",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Area-Scope */
	{
		struct dict_avp_data data = {
			1624,	/* Code */
			10415,	/* Vendor */
			"Area-Scope",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* List-Of-Measurements */
	{
		struct dict_avp_data data = {
			1625,	/* Code */
			10415,	/* Vendor */
			"List-Of-Measurements",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Reporting-Trigger */
	{
		struct dict_avp_data data = {
			1626,	/* Code */
			10415,	/* Vendor */
			"Reporting-Trigger",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Report-Interval */
	{
		struct dict_avp_data data = {
			1627,	/* Code */
			10415,	/* Vendor */
			"Report-Interval",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Report-Amount */
	{
		struct dict_avp_data data = {
			1628,	/* Code */
			10415,	/* Vendor */
			"Report-Amount",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Event-Threshold-RSRP */
	{
		struct dict_avp_data data = {
			1629,	/* Code */
			10415,	/* Vendor */
			"Event-Threshold-RSRP",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Event-Threshold-RSRQ */
	{
		struct dict_avp_data data = {
			1630,	/* Code */
			10415,	/* Vendor */
			"Event-Threshold-RSRQ",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Logging-Interval */
	{
		struct dict_avp_data data = {
			1631,	/* Code */
			10415,	/* Vendor */
			"Logging-Interval",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Logging-Duration */
	{
		struct dict_avp_data data = {
			1632,	/* Code */
			10415,	/* Vendor */
			"Logging-Duration",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Relay-Node-Indicator */
	{
		struct dict_avp_data data = {
			1633,	/* Code */
			10415,	/* Vendor */
			"Relay-Node-Indicator",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* MDT-User-Consent */
	{
		struct dict_avp_data data = {
			1634,	/* Code */
			10415,	/* Vendor */
			"MDT-User-Consent",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Subscribed-VSRVCC */
	{
		struct dict_avp_data data = {
			1636,	/* Code */
			10415,	/* Vendor */
			"Subscribed-VSRVCC",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Equivalent-PLMN-List */
	{
		struct dict_avp_data data = {
			1637,	/* Code */
			10415,	/* Vendor */
			"Equivalent-PLMN-List",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Served-Party-IP-Address */
	{
		struct dict_avp_data data = {
			848,	/* Code */
			10415,	/* Vendor */
			"Served-Party-IP-Address",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, Address_type, NULL);
	};

	/* PDN-GW-Allocation-Type */
	{
		struct dict_avp_data data = {
			1438,	/* Code */
			10415,	/* Vendor */
			"PDN-GW-Allocation-Type",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* Allocation-Retention-Priority */
	{
		struct dict_avp_data data = {
			1034,	/* Code */
			10415,	/* Vendor */
			"Allocation-Retention-Priority",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};

	/* SIPTO-Permission */
	{
		struct dict_avp_data data = {
			1613,	/* Code */
			10415,	/* Vendor */
			"SIPTO-Permission",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};
	
	/* Restoration-Info */
	{
		struct dict_avp_data data = {
			649,	/* Code */
			10415,	/* Vendor */
			"Restoration-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};
		CHECK_dict_new(DICT_AVP, &data, NULL, NULL);
	};


	/**************     END of copy from dict_dcca_3gpp.c   ****************************************************/


	/*Define 'Service-Selection' AVP, type is UTF8String */
	{
		struct dict_avp_data data = {
			493,	/* Code */
			0,	/* Vendor */
			"Service-Selection",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			0 ,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};		
		CHECK_dict_new( DICT_AVP, &data, UTF8String_type, NULL);
	}	

	/*Define 'Reset-ID' AVP */
	{
		struct dict_avp_data data = {
			1670,	/* Code */
			10415,	/* Vendor */
			"Reset-ID",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}

	/*Define 'MDT-Allowed-PLMN-Id' AVP */
	{
		struct dict_avp_data data = {
			1671,	/* Code */
			10415,	/* Vendor */
			"MDT-Allowed-PLMN-Id",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}

	/* Define 'SS-Status' AVP , this AVP is defined as type grouped in 'dict_dcca_3gpp' extension found in 	
	 * freediameter which contradicts with '3GPP TS 29.272 version 12.8.0 Release 12' document which define it as 	
	 * type octetstring
	 */
	{
		struct dict_avp_data data = {
			1477,	/* Code */
			10415,	/* Vendor */
			"SS-Status",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
		};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}

	/*Define 'Restoration-Priority' AVP */
	{
		struct dict_avp_data data = {
			1663,	/* Code */
			10415,	/* Vendor */
			"Restoration-Priority",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
		};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}

	/* Define 'SIPTO-Local-Network-Permission' AVP */
	/* This AVP is defined in '3GPP TS 29.272 version 12.8.0 Release 12' as unsigned32, but is defined */
	/* as enumerated in '3GPP TS 29.002 version 12.7.0 Release 12' and based on the values it takes its */
	/* is defined here as enumerated*/
	{
		struct dict_avp_data data = {
			1665,	/* Code */
			10415,	/* Vendor */
			"SIPTO-Local-Network-Permission",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_INTEGER32	/* base type of data */
		};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}

	/*Define 'WLAN-offloadability' AVP */
	{
		struct dict_avp_data data = {
			1667,	/* Code */
			10415,	/* Vendor */
			"WLAN-offloadability",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
		};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}

	/*Define 'WLAN-offloadability-EUTRAN' AVP */
	{
		struct dict_avp_data data = {
			1668,	/* Code */
			10415,	/* Vendor */
			"WLAN-offloadability-EUTRAN",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
			};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}

	/*Define 'WLAN-offloadability-UTRAN' AVP */
	{
		struct dict_avp_data data = {
			1669,	/* Code */
			10415,	/* Vendor */
			"WLAN-offloadability-UTRAN",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR ,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
			};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}

	/*Define 'ProSe-Subscription-Data' AVP */
	{
		struct dict_avp_data data = {
			3701,	/* Code */
			10415,	/* Vendor */
			"ProSe-Subscription-Data",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
			};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}
	
	/*Define 'ProSe-Permission' AVP */
	{
		struct dict_avp_data data = {
			3702,	/* Code */
			10415,	/* Vendor */
			"ProSe-Permission",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flag values */
			AVP_TYPE_UNSIGNED32	/* base type of data */
			};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}

	/*Define 'MIP6-Agent-Info' AVP */
	{
		struct dict_avp_data data = {
			486,	/* Code */
			0,	/* Vendor */
			"MIP6-Agent-Info",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			0,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
			};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}

	/*Define 'MIP-Home-Agent-Address' AVP, type is address */
	{
		struct dict_avp_data data = {
			334,	/* Code */
			0,	/* Vendor */
			"MIP-Home-Agent-Address",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			0,	/* Fixed flag values */
			AVP_TYPE_OCTETSTRING	/* base type of data */
			};		
		CHECK_dict_new( DICT_AVP, &data, Address_type, NULL);
	}

	/*Define 'MIP-Home-Agent-Host' AVP */
	{
		struct dict_avp_data data = {
			348,	/* Code */
			0,	/* Vendor */
			"MIP-Home-Agent-Host",	/* Name */
			AVP_FLAG_VENDOR |AVP_FLAG_MANDATORY,	/* Fixed flags */
			0,	/* Fixed flag values */
			AVP_TYPE_GROUPED	/* base type of data */
			};		
		CHECK_dict_new( DICT_AVP, &data, NULL, NULL);
	}

	/*Coupled-Node-Diameter-ID*/
	{
		struct dict_avp_data data = { 
			1666, 					/* Code */
			10415, 					/* Vendor */
			"Coupled-Node-Diameter-ID", 			/* Name */
			AVP_FLAG_VENDOR | AVP_FLAG_MANDATORY, 	/* Fixed flags */
			AVP_FLAG_VENDOR,			/* Fixed flag values */
			AVP_TYPE_OCTETSTRING 			/* base type of data */
			};
		CHECK_dict_new(DICT_AVP, &data , DiameterIdentity_type, NULL);	
	}

	return 0;
}
