
/*'3GPP TS 29.002 version 12.7.0' document is used as a reference to set the size of some of the AVPs*/
/* Service-Selection AVP's size is base on APN Network Identifiere which is a maximum of 63 octets*/

/* Create database HSS database 'ss_hss' */
DROP DATABASE IF EXISTS ss_hss;
CREATE DATABASE ss_hss;
use ss_hss;

/* Create table structure for subsctioption data*/
/* 3gpp-Charging-Characterstic size from '3GPP TS 29.061 version 12.10.0'*/
/* imsi formatted as specified in '3GPP TS 23.003 version 12.8.0'*/
/* A maximum of 3  TS-Code is allowed in this configuration*/
DROP TABLE IF EXISTS subscriptionData;
CREATE TABLE subscriptionData (
  imsi varchar(15) unique,
  subscStatus enum(/*'SERVICE_GRANTED'*/'0', /*'OPERATOR_DETERMINED_BARRING'*/'1') NOT NULL, 
  msisdn varbinary(9) NOT NULL, 
  amsisdn varbinary(9),
  stnSr varbinary(9),
  icsIndicator enum( /*'FALSE'*/'0', /*'TRUE'*/'1'),
  netAccessMode enum(/*'PACKET_AND_CIRCUIT'*/'0', /*'Reserved'*/'1', /*'ONLY_PACKET'*/'2') NOT NULL,
  odb int(10) unsigned,
  hplmnOdb int(10) unsigned,
  zoneCode0 varbinary(2),
  zoneCode1 varbinary(2),
  zoneCode2 varbinary(2),
  accessRestirData int(10) unsigned,
  apnOiReplacement varbinary(100),
  tsCode0 binary(1),
  tsCode1 binary(1),
  tsCode2 binary(1),
  3gppChargCharacter binary(6),
  maxBwUl int (10) unsigned,
  maxBwDl int (10) unsigned,
  defaultApnContextId int(10) unsigned,
  ratFreqSelPrior int(10) unsigned,
  roamRestrUnSuppFeatur enum(/*'Roaming_Restricted_Due_To_Unsupported_Feature'*/'0'),
  subscPeriodRauTauTimer int(10) unsigned,
  mpsPrior int(10) unsigned,
  vplmnLipaAllow enum(/*'LIPA_NOTALLOWED'*/'0', /*'LIPA_ALLOWED'*/'1'),
  relayNodeIndic enum(/*'NOT_RELAY_NODE'*/'0', /*'RELAY_NODE'*/'1'),
  mdtUserConsent enum(/*'CONSENT_NOT_GIVEN'*/'0', /*'CONSENT_GIVEN'*/'1'),
  subscVsrvcc enum(/*'VSRVCC_SUBSCRIBED'*/'0'),
  prosePermis int(10) unsigned,
  subscDataFlgs int(10) unsigned,
  ratType enum(/*WLAN*/'0',/*VIRTUAL*/ '1',/*UTRAN*/'1000',	/*GERAN*/ '1001',/*GAN*/'1002',	/*HSPA_EVOLUTION*/'1003',/*EUTRAN*/'1004', /*CDMA2000_1X */'2000',/*HRPD*/ '2001',/*UMB*/ '2002',/*EHRPD*/'2003') not NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/* Create table structure for subscriber related data of mme*/
DROP TABLE IF EXISTS mme;
CREATE TABLE mme(
  imsi varchar(15) unique,
  mmeHost varbinary(255) not NULL,
  mmeRealm varbinary(255) not NULL,
  uePurged enum('UE_PURGED'),
  mmeMtSmsNumb varbinary(8)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Create table structure for terminal related info*/
DROP TABLE IF EXISTS termInfo;
CREATE TABLE termInfo(
  imsi varchar(15) unique,
  imei char(14),
  softVersion char(2),
  meid char(14),
  ueSrvccCapab enum(/*'UE_SRVCC_NOT_SUPPORTED'*/'0',/*'UE_SRVCC_SUPPORTED'*/'1')
) ENGINE=InnoDB CHARSET=utf8;;

/*Create Table structure for Reset-Id*/
/*Length and structure of Reset-Id AVP is not specified in '3GPP TS 29.272 version 12.8.0'*/
DROP TABLE IF EXISTS resetId;
CREATE TABLE resetId(
 resetId varbinary(9)
) ENGINE=InnoDB;

/*Create Table structure for User-Id*/
DROP TABLE IF EXISTS userId;
CREATE TABLE userId(
 userId varchar(15)
) ENGINE=InnoDB CHARSET=utf8;

/* Create table structure for CSG-Subscription-Data*/
/* A maximum of 3 Service-Selection AVPs is allowed in this configuration*/
DROP TABLE IF EXISTS csgData;
CREATE TABLE csgData(
  imsi varchar(15) NOT NULL,
  csgId int(10) unsigned,
  expirDate binary(4),
  serviceSelection0 varbinary(63),
  serviceSelection1 varbinary(63),
  serviceSelection2 varbinary(63),
  visitPlmnId binary(3)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/* Create table structure PDP-Context*/
DROP TABLE IF EXISTS pdpContext;
CREATE TABLE pdpContext(
  imsi varchar(15) NOT NULL,
  contextId int(10) unsigned,
  pdpType binary(1),
  pdpAddr varbinary(16),
  qosSubscribed binary(3),
  vplmnDynmAddrAllw enum(/*'NOTALLOWED'*/'0', /*'ALLOWED'*/'1'),
  serviceSelection varbinary(63),
  3gppChargCharacter binary(6),
  extPdpType binary(2),
  extPdpAddr varbinary(16),
  maxBwUl int (10) unsigned,
  maxBwDl int (10) unsigned,
  apnOiReplacement varbinary(100),
  siptoPermis enum(/*'SIPTO_above_RAN_ALLOWED'*/'0', /*'SIPTO_above_RAN_NOTALLOWED'*/'1'),
  lipaPermis enum(/*'LIPA_PROHIBITED'*/'0', /*'LIPA_ONLY'*/'1', /*'LIPA_CONDITIONAL'*/'2', /*'LIPA_NOT_PRESENT'*/'3'),
  restorationPrior int(10) unsigned,
  siptoLocalNetPermis int(10) unsigned
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/* Create table structure for Trace-Data*/
/* A maximum of 3 MDT-Allowed-PLMN-Id AVPs is allowed in this configuration */
DROP TABLE IF EXISTS traceData;
CREATE TABLE traceData(
  imsi varchar(15) unique,
  traceReference binary(6),
  traceDepth enum(/*'Minimum'*/'0', /*'Medium'*/'1', /*'Maximum'*/'2', /*'MinimumWithoutVendorSpecificExtension'*/'3', /*'MediumWithoutVendorSpecificExtension'*/'4',/* 'MaximumWithoutVendorSpecificExtension'*/'5'),
  traceNeTypeList binary(1),
  traceInterfList binary(2),
  traceEventList binary(2),
  omcId binary(20),
  traceCollEnty varbinary(16),
  jobType enum(/*Immediate_MDT_only*/'0', /*Logged_MDT_only*/'1', /*Trace_only*/'2',/*Immediate_MDT_and_Trace*/'3', /*RLF_reports_only*/'4',	/*RCEF_reports_only)*/'5', /*listOfmeas int(10) unsigned*/'6',/*reporTrigg int(10) unsigned*/'7'),
  listOfMeasr int(10) unsigned,
  reporTrig int(10) unsigned,
  reporInterv enum(/*'UMTS_250MS'*/'0', /*'UMTS_500MS'*/'1', /*'UMTS_1000MS'*/'2', /*'UMTS_2000MS'*/'3', /*'UMTS_3000MS'*/'4', /*'UMTS_4000MS'*/'5', /*'UMTS_6000MS'*/'6', /*'UMTS_8000MS'*/'7', /*'UMTS_12000MS'*/'8', /*'UMTS_16000MS'*/'9', /*'UMTS_20000MS'*/'10', /*'UMTS_24000MS'*/'11', /*'UMTS_28000MS'*/'12', /*'UMTS_32000MS'*/'13', /*'UMTS_64000MS'*/'14',/*'LTE_120MS'*/'15', /*'LTE_240MS'*/'16', /*'LTE_480MS'*/'17', /*'LTE_640MS'*/'18', /*'LTE_1024MS'*/'19', /*'LTE_2048MS'*/'20', /*'LTE_5120MS'*/'21', /*'LTE_10240MS'*/'22', /*'LTE_60000MS'*/'23', /*'LTE_360000MS'*/'24', /*'LTE_720000MS'*/'25', /*'LTE_1800000MS'*/'26', /*'LTE_3600000MS'*/'27'),
  reporAmount enum(/*'ONE'*/'0', /*'TWO'*/'1', /*'FOUR'*/'2', /*'EIGHT'*/'3', /*'SIXTEEN'*/'4', /*'THIRTYTWO'*/'5', /*'SIXTYFOUR'*/'6', /*'INFINITY'*/'7'),
  evtThreshRsrp int(10) unsigned,
  evtThreshRsrq int(10) unsigned,
  logInterv enum(/*'LOG_1p28'*/'0', /*'LOG_2p56'*/'1', /*'LOG_5p12'*/'2', /*'LOG_10p24'*/'3', /*'LOG_20p48'*/'4', /*'LOG_30p72'*/'5', /*'LOG_40p96'*/'6', /*'LOG_61p44'*/'7'),
  logDuration enum(/*'LOG_600SEC'*/'0', /*'LOG_1200SEC'*/'1', /*'LOG_2400SEC'*/'2', /*'LOG_3600SEC'*/'3', /*'LOG_5400SEC'*/'4', /*'LOG_7200SEC'*/'5'),
  measrPeriodLte enum(/*'D_1024MS'*/'0', /*'D_1280MS'*/'1', /*'D_2048MS'*/'2', /*'D_2560MS'*/'3', /*'D_5120MS'*/'4', /*'D_10240MS'*/'5', /*'D_1MIN'*/'6'),
  measrPeriodUmts enum(/*'D_250MS'*/'0', /*'D_500MS'*/'1', /*'D_1000MS'*/'2', /*'D_2000MS'*/'3', /*'D_3000MS'*/'4', /*'D_4000MS'*/'5', /*'D_6000MS'*/'6', /*'D_8000MS'*/'7', /*'D_12000MS'*/'8', /*'D_16000MS'*/'9', /*'D_20000MS'*/'10', /*'D_24000MS'*/'11', /*'D_28000MS'*/'12', /*'D_32000MS'*/'13', /*'D_64000MS'*/'14'),
  collecPeriodRmmLte enum(/*'D_1024MS'*/'0', /*'D_1280MS'*/'1', /*'D_2048MS'*/'2', /*'D_2560MS'*/'3', /*'D_5120MS'*/'4', /*'D_10240MS'*/'5', /*'D_1MIN'*/'6'),
  collecPeriodRmmUmts enum(/*'D_250MS'*/'0', /*'D_500MS'*/'1', /*'D_1000MS'*/'2', /*'D_2000MS'*/'3', /*'D_3000MS'*/'4', /*'D_4000MS'*/'5', /*'D_6000MS'*/'6', /*'D_8000MS'*/'7', /*'D_12000MS'*/'8', /*'D_16000MS'*/'9', /*'D_20000MS'*/'10', /*'D_24000MS'*/'11', /*'D_28000MS'*/'12', /*'D_32000MS'*/'13', /*'D_64000MS'*/'14'),
  positionMethod binary(1),
  measrQuant binary(1),
  evtThreshEvt1f int,
  evtThreshEvt1i int,
  mdtAllowPlmnId0 binary(3),
  mdtAllowPlmnId1 binary(3),
  mdtAllowPlmnId2 binary(3)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
				
/* Create table structure for Area-Scope*/
DROP TABLE IF EXISTS areaScope;
CREATE TABLE areaScope(
  imsi varchar(15) NOT NULL,
  cgi binary(7),
  eutranCgi binary(7),
  rai binary(6),
  lai binary(5),
  tai binary(5)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/* Create Table structure for APN-Configuration */
/* Visited-Network-Identifier is coded as 'mnc<MNC>.mcc<MCC>.3gppnetwork.org'*/
DROP TABLE IF EXISTS apnConf;
CREATE TABLE apnConf (
  imsi varchar(15) NOT NULL,
  contextId int(10) unsigned NOT NULL,
  servedPartyIpAddr0 varbinary(16),
  servedPartyIpAddr1 varbinary(16),
  pdnType enum(/*'IPv4'*/'0', /*'IPv6'*/'1', /*'IPv4v6'*/'2', /*'IPv4_OR_IPv6'*/'3') NOT NULL,
  serviceSelection varbinary(63) NOT NULL,
  qosClassId enum(/*'QCI_1'*/'1', /*'QCI_2'*/'2', /*'QCI_3'*/'3', /*'QCI_4'*/'4', /*'QCI_5'*/'5', /*'QCI_6'*/'6', /*'QCI_7'*/'7', /*'QCI_8'*/'8', /*'QCI_9'*/'9', /*'QCI_65'*/'65', /*'QCI_66'*/'66', /*'QCI_69'*/'69', /*'QCI_70'*/'70'),
  priorityLevel int(10) unsigned,
  preEmpCap enum(/*'PRE_EMPTION_CAPABILITY_ENABLED'*/'0', /*'PRE_EMPTION_CAPABILITY_DISABLED'*/'1'),
  preEmpVulner enum(/*'PRE_EMPTION_VULNERABILITY_ENABLED'*/'0', /*'PRE_EMPTION_VULNERABILITY_DISABLED'*/'1'),
  vplmnDynmAddrAllw enum(/*'NOTALLOWED'*/'0', /*'ALLOWED'*/'1'),
  mipHomeAgntAddr0 varbinary(16),
  mipHomeAgntAddr1 varbinary(16),
  mipDestHost varbinary(255),
  mipDestRealm varbinary(255),
  visitNetId char(23),
  pdnGwAllocType enum(/*'STATIC'*/'0', /*'DYNAMIC'*/'1'),
  3gppChargCharacter binary(6),
  maxBwUl int (10) unsigned,
  maxBwDl int (10) unsigned,
  apnOiReplacement varbinary(100),
  siptoPermis enum(/*'SIPTO_above_RAN_ALLOWED'*/'0', /*'SIPTO_above_RAN_NOTALLOWED'*/'1'),
  lipaPermis enum(/*'LIPA_PROHIBITED'*/'0', /*'LIPA_ONLY'*/'1', /*'LIPA_CONDITIONAL'*/'2', /*'LIPA_NOT_PRESENT'*/'3'),
  restorationPrior int(10) unsigned,
  siptoLocalNetPermis int(10) unsigned,
  wlanOffLoadEutran int(10) unsigned,
  wlanOffLoadUtran int(10) unsigned
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/* Create Table structure for Specific-APN-Info*/
/* The contextId is used to relate this with the corresponding APN-Configuration*/
DROP TABLE IF EXISTS specificApnInfo;
CREATE TABLE specificApnInfo (
  imsi varchar(15) NOT NULL,
  contextId int(10) unsigned,
  serviceSelection varbinary(63),   
  mipHomeAgntAddr0 varbinary(16),
  mipHomeAgntAddr1 varbinary(16),
  mipDestHost varbinary(255),
  mipDestRealm varbinary(255),
  visitNetId char(23)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/* Create table structure for LCS-Information */
/* A maximum of 3 GMLC-Number and 3 MO-LR  is allowed in this configuration*/
DROP TABLE IF EXISTS lcsInfo;
CREATE TABLE lcsInfo (
  imsi varchar(15) unique,
  gmlcNum0 varbinary(9),
  gmlcNum1 varbinary(9),
  gmlcNum2 varbinary(9),
  ssCode0 binary(1),
  ssStatus0 binary(1),
  ssCode1 binary(1),
  ssStatus1 binary(1),
  ssCode2 binary(1),
  ssStatus2 binary(1)  
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/* Create table structure for Call-Barring-Info*/
DROP TABLE IF EXISTS callBaringInfo;
CREATE TABLE callBaringInfo (
  imsi varchar(15) NOT NULL,
  ssCode binary(1) NOT NULL,
  ssStatus binary(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/* Create table structure for E-UTRAN-VECTOR*/
DROP TABLE IF EXISTS EUTRANVector;
CREATE TABLE EUTRANVector (
  imsi varchar(15) NOT NULL,
  itemNumb int(10) unsigned NOT NULL,
  rand binary(16) NOT NULL,
  xres varbinary(16) NOT NULL,
  autn binary(16) NOT NULL,
  kasme binary(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/* Create table structure for UTRAN-VECTOR*/
DROP TABLE IF EXISTS UTRANVector;
CREATE TABLE UTRANVector (
  imsi varchar(15) NOT NULL,
  ItemNumb int(10) unsigned NOT NULL,
  rand binary(16) NOT NULL,
  xres varbinary(16) NOT NULL,
  autn binary(16) NOT NULL,
  ck binary(16) NOT NULL,
  ik binary(16) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/* Create table structure for UTRAN-VECTOR */
DROP TABLE IF EXISTS GERANVector;
CREATE TABLE GERANVector (
  imsi varchar(15) NOT NULL,
  ItemNumb int(10) unsigned NOT NULL,
  rand binary(16) NOT NULL,
  xres varbinary(16) NOT NULL,
  kc binary(8) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Insert subscriber data*/
INSERT INTO subscriptionData VALUES ('244444123456789', /*'SERVICE_GRANTED'*/'0', x'00358441234567', x'00358441234568', x'00358449999999',/*'TRUE'*/'1', '0', '1','0',x'0001',x'0002',x'0003', '0','apn.oi.repl',x'01',x'02', x'03','cccccc','10','5','1','1','0','1','1','0','0', NULL,'0','1','0',/*UTRAN*/'1000');
INSERT INTO resetId VALUES ('244444');
INSERT INTO pdpContext VALUES('244444123456789','1','1','abcd','001','0', 'service.select', 'cccccc','01','abcd','10','5','apn.oi.repl','0','0','1','1');
INSERT INTO userId VALUES('24444');
INSERT INTO csgData VALUES('244444123456789', '1','0001','service.select','service.select2','service.select3','ddd');
INSERT INTO traceData VALUES('244444123456789','123456','0','1','01','01','omcid','abcd','0','1','1','0', '0', '1', '1', '0', '0','0','0','0','0', '1','1','-1','-1',x'244001', x'244002', x'244003');
INSERT INTO areaScope VALUES('244444123456789',x'24400100010001', x'24400100010002',x'244001000101',x'2440010001', x'2440010002');
INSERT INTO apnConf VALUES('244444123456789','1','abcdabcdabcdabcd',NULL, 'IPv6','service.select','1','1', '0', '0','0', 'abcdabcdabcdabcd',NULL,'test.localhost','localhost','net.visited.id', '1'/*DYNAMIC*/, 'cccccc', '10', '5', 'apn.oi.repl', '0', '0', '1','1','1','1');
INSERT INTO specificApnInfo VALUES('','1','service.selec','abcdabcdabcdabcd',NULL,'test.localhost','localhost', 'net.visited.id');
INSERT INTO lcsInfo VALUES('244444123456789',x'358123456789',x'358123456798',NULL,'1','1','2','1',NULL,NULL);
INSERT INTO callBaringInfo VALUES('244444123456789','1','1');
INSERT INTO EUTRANVector VALUES('244444123456789','1','1234567890123456','1234567890123456', '1234567890123456', '12345678901234561234567890123456');
INSERT INTO UTRANVector VALUES('244444123456789', '1', '1234567890123456','1234567890123456', '1234567890123456', '1234567890123456', '1234567890123456');
INSERT INTO GERANVector VALUES('244444123456789', '1', '1234567890123456','1234567890123456', '12345678');
