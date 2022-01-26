//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#include "../include/GXIgnore.h"
#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXDLMSClient.h"

#ifndef DLMS_IGNORE_ACTION_SCHEDULE
#include "../include/GXDLMSActionSchedule.h"
#endif //DLMS_IGNORE_ACTION_SCHEDULE
#ifndef DLMS_IGNORE_ACTIVITY_CALENDAR
#include "../include/GXDLMSActivityCalendar.h"
#endif //DLMS_IGNORE_ACTIVITY_CALENDAR
#ifndef DLMS_IGNORE_ASSOCIATION_LOGICAL_NAME
#include "../include/GXDLMSAssociationLogicalName.h"
#endif //DLMS_IGNORE_ASSOCIATION_LOGICAL_NAME
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
#include "../include/GXDLMSAssociationShortName.h"
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
#ifndef DLMS_IGNORE_AUTO_ANSWER
#include "../include/GXDLMSAutoAnswer.h"
#endif //DLMS_IGNORE_AUTO_ANSWER
#ifndef DLMS_IGNORE_AUTO_CONNECT
#include "../include/GXDLMSAutoConnect.h"
#endif //DLMS_IGNORE_AUTO_CONNECT
#ifndef DLMS_IGNORE_CLOCK
#include "../include/GXDLMSClock.h"
#endif //DLMS_IGNORE_CLOCK
#ifndef DLMS_IGNORE_DATA
#include "../include/GXDLMSData.h"
#endif //DLMS_IGNORE_DATA
#ifndef DLMS_IGNORE_REGISTER
#include "../include/GXDLMSRegister.h"
#endif //DLMS_IGNORE_REGISTER
#ifndef DLMS_IGNORE_EXTENDED_REGISTER
#include "../include/GXDLMSExtendedRegister.h"
#endif //DLMS_IGNORE_EXTENDED_REGISTER
#ifndef DLMS_IGNORE_DEMAND_REGISTER
#include "../include/GXDLMSDemandRegister.h"
#endif //DLMS_IGNORE_DEMAND_REGISTER
#ifndef DLMS_IGNORE_REGISTER_MONITOR
#include "../include/GXDLMSRegisterMonitor.h"
#endif //DLMS_IGNORE_REGISTER_MONITOR
#ifndef DLMS_IGNORE_PROFILE_GENERIC
#include "../include/GXDLMSProfileGeneric.h"
#endif //DLMS_IGNORE_PROFILE_GENERIC
#ifndef DLMS_IGNORE_TCP_UDP_SETUP
#include "../include/GXDLMSTcpUdpSetup.h"
#endif //DLMS_IGNORE_TCP_UDP_SETUP
#ifndef DLMS_IGNORE_GPRS_SETUP
#include "../include/GXDLMSGPRSSetup.h"
#endif //DLMS_IGNORE_GPRS_SETUP
#ifndef DLMS_IGNORE_ACTION_SCHEDULE
#include "../include/GXDLMSActionSchedule.h"
#endif //DLMS_IGNORE_ACTION_SCHEDULE
#ifndef DLMS_IGNORE_SPECIAL_DAYS_TABLE
#include "../include/GXDLMSSpecialDaysTable.h"
#endif //DLMS_IGNORE_SPECIAL_DAYS_TABLE
#ifndef DLMS_IGNORE_IMAGE_TRANSFER
#include "../include/GXDLMSImageTransfer.h"
#endif //DLMS_IGNORE_IMAGE_TRANSFER
#ifndef DLMS_IGNORE_DISCONNECT_CONTROL
#include "../include/GXDLMSDisconnectControl.h"
#endif //DLMS_IGNORE_DISCONNECT_CONTROL
#ifndef DLMS_IGNORE_LIMITER
#include "../include/GXDLMSLimiter.h"
#endif //DLMS_IGNORE_LIMITER
#ifndef DLMS_IGNORE_MBUS_CLIENT
#include "../include/GXDLMSMBusClient.h"
#endif //DLMS_IGNORE_MBUS_CLIENT
#ifndef DLMS_IGNORE_SCRIPT_TABLE
#include "../include/GXDLMSScriptTable.h"
#endif //DLMS_IGNORE_SCRIPT_TABLE
#ifndef DLMS_IGNORE_MBUS_SLAVE_PORT_SETUP
#include "../include/GXDLMSMBusSlavePortSetup.h"
#endif //DLMS_IGNORE_MBUS_SLAVE_PORT_SETUP
#ifndef DLMS_IGNORE_SECURITY_SETUP
#include "../include/GXDLMSSecuritySetup.h"
#endif //DLMS_IGNORE_SECURITY_SETUP
#ifndef DLMS_IGNORE_PPP_SETUP
#include "../include/GXDLMSPppSetup.h"
#endif //DLMS_IGNORE_PPP_SETUP
#ifndef DLMS_IGNORE_MAC_ADDRESS_SETUP
#include "../include/GXDLMSMacAddressSetup.h"
#endif //DLMS_IGNORE_MAC_ADDRESS_SETUP
#ifndef DLMS_IGNORE_HDLC_SETUP
#include "../include/GXDLMSHdlcSetup.h"
#endif //DLMS_IGNORE_HDLC_SETUP
#ifndef DLMS_IGNORE_IEC_LOCAL_PORT_SETUP
#include "../include/GXDLMSIECOpticalPortSetup.h"
#endif //DLMS_IGNORE_IEC_LOCAL_PORT_SETUP
#ifndef DLMS_IGNORE_IP4_SETUP
#include "../include/GXDLMSIp4Setup.h"
#endif //DLMS_IGNORE_IP4_SETUP
#ifndef DLMS_IGNORE_IP6_SETUP
#include "../include/GXDLMSIp6Setup.h"
#endif //DLMS_IGNORE_IP6_SETUP
#ifndef DLMS_IGNORE_REGISTER_ACTIVATION
#include "../include/GXDLMSRegisterActivation.h"
#endif //DLMS_IGNORE_REGISTER_ACTIVATION
#ifndef DLMS_IGNORE_SCHEDULE
#include "../include/GXDLMSSchedule.h"
#endif //DLMS_IGNORE_SCHEDULE
#ifndef DLMS_IGNORE_MODEM_CONFIGURATION
#include "../include/GXDLMSModemConfiguration.h"
#endif //DLMS_IGNORE_MODEM_CONFIGURATION
#ifndef DLMS_IGNORE_SAP_ASSIGNMENT
#include "../include/GXDLMSSapAssignment.h"
#endif //DLMS_IGNORE_SAP_ASSIGNMENT
#ifndef DLMS_IGNORE_MBUS_MASTER_PORT_SETUP
#include "../include/GXDLMSMBusMasterPortSetup.h"
#endif //DLMS_IGNORE_MBUS_MASTER_PORT_SETUP
#ifndef DLMS_IGNORE_MESSAGE_HANDLER
#include "../include/GXDLMSMessageHandler.h"
#endif //DLMS_IGNORE_MESSAGE_HANDLER
#ifndef DLMS_IGNORE_PUSH_SETUP
#include "../include/GXDLMSPushSetup.h"
#endif //DLMS_IGNORE_PUSH_SETUP
#ifndef DLMS_IGNORE_GSM_DIAGNOSTIC
#include "../include/GXDLMSGSMDiagnostic.h"
#endif //DLMS_IGNORE_GSM_DIAGNOSTIC
#ifndef DLMS_IGNORE_ACCOUNT
#include "../include/GXDLMSAccount.h"
#endif //DLMS_IGNORE_ACCOUNT
#ifndef DLMS_IGNORE_CREDIT
#include "../include/GXDLMSCredit.h"
#endif //DLMS_IGNORE_CREDIT
#ifndef DLMS_IGNORE_CHARGE
#include "../include/GXDLMSCharge.h"
#endif //DLMS_IGNORE_CHARGE
#ifndef DLMS_IGNORE_PARAMETER_MONITOR
#include "../include/GXDLMSParameterMonitor.h"
#endif //DLMS_IGNORE_PARAMETER_MONITOR
#include "../include/GXDLMSTokenGateway.h"
#ifndef DLMS_IGNORE_TOKEN_GATEWAY
#include "../include/GXDLMSCompactData.h"
#endif //DLMS_IGNORE_TOKEN_GATEWAY
#ifndef DLMS_IGNORE_UTILITY_TABLES
#include "../include/GXDLMSUtilityTables.h"
#endif //DLMS_IGNORE_UTILITY_TABLES
#ifndef DLMS_IGNORE_LLC_SSCS_SETUP
#include "../include/GXDLMSLlcSscsSetup.h"
#endif //DLMS_IGNORE_LLC_SSCS_SETUP
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_PHYSICAL_LAYER_COUNTERS
#include "../include/GXDLMSPrimeNbOfdmPlcPhysicalLayerCounters.h"
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_PHYSICAL_LAYER_COUNTERS
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_SETUP
#include "../include/GXDLMSPrimeNbOfdmPlcMacSetup.h"
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_SETUP
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_FUNCTIONAL_PARAMETERS
#include "../include/GXDLMSPrimeNbOfdmPlcMacFunctionalParameters.h"
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_FUNCTIONAL_PARAMETERS
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_COUNTERS
#include "../include/GXDLMSPrimeNbOfdmPlcMacCounters.h"
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_COUNTERS
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_NETWORK_ADMINISTRATION_DATA
#include "../include/GXDLMSPrimeNbOfdmPlcMacNetworkAdministrationData.h"
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_NETWORK_ADMINISTRATION_DATA
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_APPLICATIONS_IDENTIFICATION
#include "../include/GXDLMSPrimeNbOfdmPlcApplicationsIdentification.h"
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_APPLICATIONS_IDENTIFICATION
#ifndef DLMS_IGNORE_IEC_8802_LLC_TYPE1_SETUP
#include "../include/GXDLMSIec8802LlcType1Setup.h"
#endif //DLMS_IGNORE_IEC_8802_LLC_TYPE1_SETUP
#ifndef DLMS_IGNORE_IEC_8802_LLC_TYPE2_SETUP
#include "../include/GXDLMSIec8802LlcType2Setup.h"
#endif //DLMS_IGNORE_IEC_8802_LLC_TYPE2_SETUP
#ifndef DLMS_IGNORE_IEC_8802_LLC_TYPE3_SETUP
#include "../include/GXDLMSIec8802LlcType3Setup.h"
#endif //DLMS_IGNORE_IEC_8802_LLC_TYPE3_SETUP
#ifndef DLMS_IGNORE_SFSK_REPORTING_SYSTEM_LIST
#include "../include/GXDLMSSFSKReportingSystemList.h"
#endif //DLMS_IGNORE_SFSK_REPORTING_SYSTEM_LIST
#ifndef DLMS_IGNORE_ARBITRATOR
#include "../include/GXDLMSArbitrator.h"
#endif //DLMS_IGNORE_ARBITRATOR
#ifndef DLMS_IGNORE_SFSK_MAC_COUNTERS
#include "../include/GXDLMSSFSKMacCounters.h"
#endif //DLMS_IGNORE_SFSK_MAC_COUNTERS
#ifndef DLMS_IGNORE_SFSK_MAC_SYNCHRONIZATION_TIMEOUTS
#include "../include/GXDLMSSFSKMacSynchronizationTimeouts.h"
#endif //DLMS_IGNORE_SFSK_MAC_SYNCHRONIZATION_TIMEOUTS
#ifndef DLMS_IGNORE_SFSK_ACTIVE_INITIATOR
#include "../include/GXDLMSSFSKActiveInitiator.h"
#endif //DLMS_IGNORE_SFSK_ACTIVE_INITIATOR
#ifndef DLMS_IGNORE_SFSK_PHY_MAC_SETUP
#include "../include/GXDLMSSFSKPhyMacSetUp.h"
#endif //DLMS_IGNORE_SFSK_PHY_MAC_SETUP
#ifndef DLMS_IGNORE_IEC_TWISTED_PAIR_SETUP
#include "../include/GXDLMSIecTwistedPairSetup.h"
#endif //DLMS_IGNORE_IEC_TWISTED_PAIR_SETUP

// Reserved for internal use.
CGXDLMSObject* CGXDLMSObjectFactory::CreateObject(DLMS_OBJECT_TYPE type)
{
    switch (type)
    {
#ifndef DLMS_IGNORE_ACTION_SCHEDULE
    case DLMS_OBJECT_TYPE_ACTION_SCHEDULE:
        return new CGXDLMSActionSchedule();
#endif //DLMS_IGNORE_ACTION_SCHEDULE
#ifndef DLMS_IGNORE_ACTIVITY_CALENDAR
    case DLMS_OBJECT_TYPE_ACTIVITY_CALENDAR:
        return new CGXDLMSActivityCalendar();
#endif //DLMS_IGNORE_ACTIVITY_CALENDAR
#ifndef DLMS_IGNORE_ASSOCIATION_LOGICAL_NAME
    case DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME:
        return new CGXDLMSAssociationLogicalName();
#endif //DLMS_IGNORE_ASSOCIATION_LOGICAL_NAME
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    case DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME:
        return new CGXDLMSAssociationShortName();
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
#ifndef DLMS_IGNORE_AUTO_ANSWER
    case DLMS_OBJECT_TYPE_AUTO_ANSWER:
        return new CGXDLMSAutoAnswer();
#endif //DLMS_IGNORE_AUTO_ANSWER
#ifndef DLMS_IGNORE_AUTO_CONNECT
    case DLMS_OBJECT_TYPE_AUTO_CONNECT:
        return new CGXDLMSAutoConnect();
#endif //DLMS_IGNORE_AUTO_CONNECT
#ifndef DLMS_IGNORE_CLOCK
    case DLMS_OBJECT_TYPE_CLOCK:
        return new CGXDLMSClock();
#endif //DLMS_IGNORE_CLOCK
#ifndef DLMS_IGNORE_DATA
    case DLMS_OBJECT_TYPE_DATA:
        return new CGXDLMSData();
#endif //DLMS_IGNORE_DATA
#ifndef DLMS_IGNORE_DEMAND_REGISTER
    case DLMS_OBJECT_TYPE_DEMAND_REGISTER:
        return new CGXDLMSDemandRegister();
#endif //DLMS_IGNORE_DEMAND_REGISTER
#ifndef DLMS_IGNORE_MAC_ADDRESS_SETUP
    case DLMS_OBJECT_TYPE_MAC_ADDRESS_SETUP:
        return new CGXDLMSMacAddressSetup();
#endif //DLMS_IGNORE_MAC_ADDRESS_SETUP
#ifndef DLMS_IGNORE_EXTENDED_REGISTER
    case DLMS_OBJECT_TYPE_EXTENDED_REGISTER:
        return new CGXDLMSExtendedRegister();
#endif //DLMS_IGNORE_EXTENDED_REGISTER
#ifndef DLMS_IGNORE_GPRS_SETUP
    case DLMS_OBJECT_TYPE_GPRS_SETUP:
        return new CGXDLMSGPRSSetup();
#endif //DLMS_IGNORE_GPRS_SETUP
#ifndef DLMS_IGNORE_SECURITY_SETUP
    case DLMS_OBJECT_TYPE_SECURITY_SETUP:
        return new CGXDLMSSecuritySetup();
#endif //DLMS_IGNORE_SECURITY_SETUP
#ifndef DLMS_IGNORE_IEC_HDLC_SETUP
    case DLMS_OBJECT_TYPE_IEC_HDLC_SETUP:
        return new CGXDLMSIecHdlcSetup();
#endif //DLMS_IGNORE_IEC_HDLC_SETUP
#ifndef DLMS_IGNORE_IEC_LOCAL_PORT_SETUP
    case DLMS_OBJECT_TYPE_IEC_LOCAL_PORT_SETUP:
        return new CGXDLMSIECLocalPortSetup();
#endif //DLMS_IGNORE_IEC_LOCAL_PORT_SETUP
#ifndef DLMS_IGNORE_IEC_TWISTED_PAIR_SETUP
    case DLMS_OBJECT_TYPE_IEC_TWISTED_PAIR_SETUP:
        return new CGXDLMSIecTwistedPairSetup();
#endif //DLMS_IGNORE_IEC_TWISTED_PAIR_SETUP
#ifndef DLMS_IGNORE_IP4_SETUP
    case DLMS_OBJECT_TYPE_IP4_SETUP:
        return new CGXDLMSIp4Setup();
#endif //DLMS_IGNORE_IP4_SETUP
#ifndef DLMS_IGNORE_IP6_SETUP
    case DLMS_OBJECT_TYPE_IP6_SETUP:
        return new CGXDLMSIp6Setup();
#endif //DLMS_IGNORE_IP6_SETUP
#ifndef DLMS_IGNORE_MBUS_SLAVE_PORT_SETUP
    case DLMS_OBJECT_TYPE_MBUS_SLAVE_PORT_SETUP:
        return new CGXDLMSMBusSlavePortSetup();
#endif //DLMS_IGNORE_MBUS_SLAVE_PORT_SETUP
#ifndef DLMS_IGNORE_IMAGE_TRANSFER
    case DLMS_OBJECT_TYPE_IMAGE_TRANSFER:
        return new CGXDLMSImageTransfer();
#endif //DLMS_IGNORE_IMAGE_TRANSFER
#ifndef DLMS_IGNORE_DISCONNECT_CONTROL
    case DLMS_OBJECT_TYPE_DISCONNECT_CONTROL:
        return new CGXDLMSDisconnectControl();
#endif //DLMS_IGNORE_DISCONNECT_CONTROL
#ifndef DLMS_IGNORE_LIMITER
    case DLMS_OBJECT_TYPE_LIMITER:
        return new CGXDLMSLimiter();
#endif //DLMS_IGNORE_LIMITER
#ifndef DLMS_IGNORE_MBUS_CLIENT
    case DLMS_OBJECT_TYPE_MBUS_CLIENT:
        return new CGXDLMSMBusClient();
#endif //DLMS_IGNORE_MBUS_CLIENT
#ifndef DLMS_IGNORE_MODEM_CONFIGURATION
    case DLMS_OBJECT_TYPE_MODEM_CONFIGURATION:
        return new CGXDLMSModemConfiguration();
#endif //DLMS_IGNORE_MODEM_CONFIGURATION
#ifndef DLMS_IGNORE_PPP_SETUP
    case DLMS_OBJECT_TYPE_PPP_SETUP:
        return new CGXDLMSPppSetup();
#endif //DLMS_IGNORE_PPP_SETUP
#ifndef DLMS_IGNORE_PROFILE_GENERIC
    case DLMS_OBJECT_TYPE_PROFILE_GENERIC:
        return new CGXDLMSProfileGeneric();
#endif //DLMS_IGNORE_PROFILE_GENERIC
#ifndef DLMS_IGNORE_REGISTER
    case DLMS_OBJECT_TYPE_REGISTER:
        return new CGXDLMSRegister();
#endif //DLMS_IGNORE_REGISTER
#ifndef DLMS_IGNORE_REGISTER_ACTIVATION
    case DLMS_OBJECT_TYPE_REGISTER_ACTIVATION:
        return new CGXDLMSRegisterActivation();
#endif //DLMS_IGNORE_REGISTER_ACTIVATION
#ifndef DLMS_IGNORE_REGISTER_MONITOR
    case DLMS_OBJECT_TYPE_REGISTER_MONITOR:
        return new CGXDLMSRegisterMonitor();
#endif //DLMS_IGNORE_REGISTER_MONITOR
#ifndef DLMS_IGNORE_REGISTER_TABLE
    case DLMS_OBJECT_TYPE_REGISTER_TABLE:
        return new CGXDLMSCustomObject(type);
#endif //DLMS_IGNORE_REGISTER_TABLE
#ifndef DLMS_IGNORE_ZIG_BEE_SAS_STARTUP
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_STARTUP:
        return new CGXDLMSCustomObject(type);
#endif //DLMS_IGNORE_ZIG_BEE_SAS_STARTUP
#ifndef DLMS_IGNORE_ZIG_BEE_SAS_JOIN
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_JOIN:
        return new CGXDLMSCustomObject(type);
#endif //DLMS_IGNORE_ZIG_BEE_SAS_JOIN
#ifndef DLMS_IGNORE_ZIG_BEE_SAS_APS_FRAGMENTATION
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_APS_FRAGMENTATION:
        return new CGXDLMSCustomObject(type);
#endif //DLMS_IGNORE_ZIG_BEE_SAS_APS_FRAGMENTATION
#ifndef DLMS_IGNORE_SAP_ASSIGNMENT
    case DLMS_OBJECT_TYPE_SAP_ASSIGNMENT:
        return new CGXDLMSSapAssignment();
#endif //DLMS_IGNORE_SAP_ASSIGNMENT
#ifndef DLMS_IGNORE_SCHEDULE
    case DLMS_OBJECT_TYPE_SCHEDULE:
        return new CGXDLMSSchedule();
#endif //DLMS_IGNORE_SCHEDULE
#ifndef DLMS_IGNORE_SCRIPT_TABLE
    case DLMS_OBJECT_TYPE_SCRIPT_TABLE:
        return new CGXDLMSScriptTable();
#endif //DLMS_IGNORE_SCRIPT_TABLE
#ifndef DLMS_IGNORE_SMTP_SETUP
    case DLMS_OBJECT_TYPE_SMTP_SETUP:
        return new CGXDLMSCustomObject(type);
#endif //DLMS_IGNORE_SMTP_SETUP
#ifndef DLMS_IGNORE_SPECIAL_DAYS_TABLE
    case DLMS_OBJECT_TYPE_SPECIAL_DAYS_TABLE:
        return new CGXDLMSSpecialDaysTable();
#endif //DLMS_IGNORE_SPECIAL_DAYS_TABLE
#ifndef DLMS_IGNORE_STATUS_MAPPING
    case DLMS_OBJECT_TYPE_STATUS_MAPPING:
        return new CGXDLMSCustomObject(type);
#endif //DLMS_IGNORE_STATUS_MAPPING
#ifndef DLMS_IGNORE_TCP_UDP_SETUP
    case DLMS_OBJECT_TYPE_TCP_UDP_SETUP:
        return new CGXDLMSTcpUdpSetup();
#endif //DLMS_IGNORE_TCP_UDP_SETUP
#ifndef DLMS_IGNORE_UTILITY_TABLES
    case DLMS_OBJECT_TYPE_UTILITY_TABLES:
        return new CGXDLMSUtilityTables();
#endif //DLMS_IGNORE_UTILITY_TABLES
#ifndef DLMS_IGNORE_MBUS_MASTER_PORT_SETUP
    case DLMS_OBJECT_TYPE_MBUS_MASTER_PORT_SETUP:
        return new CGXDLMSMBusMasterPortSetup();
#endif //DLMS_IGNORE_MBUS_MASTER_PORT_SETUP
#ifndef DLMS_IGNORE_MESSAGE_HANDLER
    case DLMS_OBJECT_TYPE_MESSAGE_HANDLER:
        return new CGXDLMSMessageHandler();
#endif //DLMS_IGNORE_MESSAGE_HANDLER
#ifndef DLMS_IGNORE_PUSH_SETUP
    case DLMS_OBJECT_TYPE_PUSH_SETUP:
        return new CGXDLMSPushSetup();
#endif //DLMS_IGNORE_PUSH_SETUP
#ifndef DLMS_IGNORE_GSM_DIAGNOSTIC
    case DLMS_OBJECT_TYPE_GSM_DIAGNOSTIC:
        return new CGXDLMSGSMDiagnostic();
#endif //DLMS_IGNORE_GSM_DIAGNOSTIC
#ifndef DLMS_IGNORE_ACCOUNT
    case DLMS_OBJECT_TYPE_ACCOUNT:
        return new CGXDLMSAccount();
#endif //DLMS_IGNORE_ACCOUNT
#ifndef DLMS_IGNORE_CREDIT
    case DLMS_OBJECT_TYPE_CREDIT:
        return new CGXDLMSCredit();
#endif //DLMS_IGNORE_CREDIT
#ifndef DLMS_IGNORE_CHARGE
    case DLMS_OBJECT_TYPE_CHARGE:
        return new CGXDLMSCharge();
#endif //DLMS_IGNORE_CHARGE
#ifndef DLMS_IGNORE_PARAMETER_MONITOR
    case DLMS_OBJECT_TYPE_PARAMETER_MONITOR:
        return new CGXDLMSParameterMonitor();
#endif //DLMS_IGNORE_PARAMETER_MONITOR
#ifndef DLMS_IGNORE_TOKEN_GATEWAY
    case DLMS_OBJECT_TYPE_TOKEN_GATEWAY:
        return new CGXDLMSTokenGateway();
#endif //DLMS_IGNORE_TOKEN_GATEWAY
#ifndef DLMS_IGNORE_COMPACT_DATA
    case DLMS_OBJECT_TYPE_COMPACT_DATA:
        return new CGXDLMSCompactData();
#endif //DLMS_IGNORE_COMPACT_DATA
#ifndef DLMS_IGNORE_LLC_SSCS_SETUP
    case DLMS_OBJECT_TYPE_LLC_SSCS_SETUP:
        return new CGXDLMSLlcSscsSetup();
#endif //DLMS_IGNORE_LLC_SSCS_SETUP
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_PHYSICAL_LAYER_COUNTERS
    case DLMS_OBJECT_TYPE_PRIME_NB_OFDM_PLC_PHYSICAL_LAYER_COUNTERS:
        return new CGXDLMSPrimeNbOfdmPlcPhysicalLayerCounters();
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_PHYSICAL_LAYER_COUNTERS
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_SETUP
    case DLMS_OBJECT_TYPE_PRIME_NB_OFDM_PLC_MAC_SETUP:
        return new CGXDLMSPrimeNbOfdmPlcMacSetup();
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_SETUP
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_FUNCTIONAL_PARAMETERS
    case DLMS_OBJECT_TYPE_PRIME_NB_OFDM_PLC_MAC_FUNCTIONAL_PARAMETERS:
        return new CGXDLMSPrimeNbOfdmPlcMacFunctionalParameters();
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_FUNCTIONAL_PARAMETERS
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_COUNTERS
    case DLMS_OBJECT_TYPE_PRIME_NB_OFDM_PLC_MAC_COUNTERS:
        return new CGXDLMSPrimeNbOfdmPlcMacCounters();
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_COUNTERS
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_NETWORK_ADMINISTRATION_DATA
    case DLMS_OBJECT_TYPE_PRIME_NB_OFDM_PLC_MAC_NETWORK_ADMINISTRATION_DATA:
        return new CGXDLMSPrimeNbOfdmPlcMacNetworkAdministrationData();
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_MAC_NETWORK_ADMINISTRATION_DATA
#ifndef DLMS_IGNORE_PRIME_NB_OFDM_PLC_APPLICATIONS_IDENTIFICATION
    case DLMS_OBJECT_TYPE_PRIME_NB_OFDM_PLC_APPLICATIONS_IDENTIFICATION:
        return new CGXDLMSPrimeNbOfdmPlcApplicationsIdentification();
#endif //DLMS_IGNORE_PRIME_NB_OFDM_PLC_APPLICATIONS_IDENTIFICATION
#ifndef DLMS_IGNORE_IEC_8802_LLC_TYPE1_SETUP
    case DLMS_OBJECT_TYPE_IEC_8802_LLC_TYPE1_SETUP:
        return new CGXDLMSIec8802LlcType1Setup();
#endif //DLMS_IGNORE_IEC_8802_LLC_TYPE1_SETUP
#ifndef DLMS_IGNORE_IEC_8802_LLC_TYPE2_SETUP
    case DLMS_OBJECT_TYPE_IEC_8802_LLC_TYPE2_SETUP:
        return new CGXDLMSIec8802LlcType2Setup();
#endif //DLMS_IGNORE_IEC_8802_LLC_TYPE2_SETUP
#ifndef DLMS_IGNORE_IEC_8802_LLC_TYPE3_SETUP
    case DLMS_OBJECT_TYPE_IEC_8802_LLC_TYPE3_SETUP:
        return new CGXDLMSIec8802LlcType3Setup();
#endif //DLMS_IGNORE_IEC_8802_LLC_TYPE3_SETUP
#ifndef DLMS_IGNORE_SFSK_REPORTING_SYSTEM_LIST
    case DLMS_OBJECT_TYPE_SFSK_REPORTING_SYSTEM_LIST:
        return new CGXDLMSSFSKReportingSystemList();
#endif //DLMS_IGNORE_SFSK_REPORTING_SYSTEM_LIST
#ifndef DLMS_IGNORE_ARBITRATOR
    case DLMS_OBJECT_TYPE_ARBITRATOR:
        return new CGXDLMSArbitrator();
#endif //DLMS_IGNORE_ARBITRATOR
#ifndef DLMS_IGNORE_SFSK_MAC_COUNTERS
    case DLMS_OBJECT_TYPE_SFSK_MAC_COUNTERS:
        return new CGXDLMSSFSKMacCounters();
#endif //DLMS_IGNORE_SFSK_MAC_COUNTERS
#ifndef DLMS_IGNORE_SFSK_MAC_SYNCHRONIZATION_TIMEOUTS
    case DLMS_OBJECT_TYPE_SFSK_MAC_SYNCHRONIZATION_TIMEOUTS:
        return new CGXDLMSSFSKMacSynchronizationTimeouts();
#endif //DLMS_IGNORE_SFSK_MAC_SYNCHRONIZATION_TIMEOUTS
#ifndef DLMS_IGNORE_SFSK_ACTIVE_INITIATOR
    case DLMS_OBJECT_TYPE_SFSK_ACTIVE_INITIATOR:
        return new CGXDLMSSFSKActiveInitiator();
#endif //DLMS_IGNORE_SFSK_ACTIVE_INITIATOR
#ifndef DLMS_IGNORE_SFSK_PHY_MAC_SETUP
    case DLMS_OBJECT_TYPE_SFSK_PHY_MAC_SETUP:
        return new CGXDLMSSFSKPhyMacSetUp();
#endif //DLMS_IGNORE_SFSK_PHY_MAC_SETUP
    default:
#ifdef _DEBUG
        printf("Unknown object: %d\r\n", type);
#endif //_DEBUG
        return NULL;
    }
}

CGXDLMSObject* CGXDLMSObjectFactory::CreateObject(DLMS_OBJECT_TYPE type, std::string ln)
{
    CGXDLMSObject* pObj = CreateObject(type);
    if (pObj != NULL)
    {
        GXHelpers::SetLogicalName(ln.c_str(), pObj->m_LN);
    }
    return pObj;
}
