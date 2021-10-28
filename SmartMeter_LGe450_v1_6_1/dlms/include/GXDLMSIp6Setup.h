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

#ifndef GXDLMSIP6SETUP_H
#define GXDLMSIP6SETUP_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_IP6_SETUP
#include "GXDLMSObject.h"
#include "GXNeighborDiscoverySetup.h"

#if defined(_WIN32) || defined(_WIN64)//Windows includes
#include <ws2tcpip.h>
#else //Linux includes.
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define IN6_ADDR struct in6_addr
#endif

// Enumerated Address config modes.
typedef enum {
    // Auto Configuration.
    DLMS_IP6_ADDRESS_CONFIG_MODE_AUTO,
    // DHCP v6.
    DLMS_IP6_ADDRESS_CONFIG_MODE_DHCP_V6,
    // Manual
    DLMS_IP6_ADDRESS_CONFIG_MODE_MANUAL,
    // Neighbour Discovery.
    DLMS_IP6_ADDRESS_CONFIG_MODE_NEIGHBOUR_DISCOVERY
}DLMS_IP6_ADDRESS_CONFIG_MODE;

/**
Online help:
http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSIp6Setup
*/
class CGXDLMSIp6Setup : public CGXDLMSObject
{
    friend class CGXXmlWriter;
    std::string m_DataLinkLayerReference;
    DLMS_IP6_ADDRESS_CONFIG_MODE m_AddressConfigMode;
    std::vector<IN6_ADDR> m_UnicastIPAddress;
    std::vector<IN6_ADDR> m_MulticastIPAddress;
    std::vector<IN6_ADDR> m_GatewayIPAddress;
    IN6_ADDR m_PrimaryDNSAddress;
    IN6_ADDR m_SecondaryDNSAddress;
    unsigned char m_TrafficClass;
    std::vector<CGXNeighborDiscoverySetup*> m_NeighborDiscoverySetup;
public:
    //Constructor.
    CGXDLMSIp6Setup();

    //SN Constructor.
    CGXDLMSIp6Setup(std::string ln, unsigned short sn);

    //LN Constructor.
    CGXDLMSIp6Setup(std::string ln);

    //Destructor.
    ~CGXDLMSIp6Setup();

    std::string& GetDataLinkLayerReference() {
        return m_DataLinkLayerReference;
    }

    void SetDataLinkLayerReference(std::string& value)
    {
        m_DataLinkLayerReference = value;
    }

    DLMS_IP6_ADDRESS_CONFIG_MODE GetAddressConfigMode()
    {
        return m_AddressConfigMode;
    }

    void SetAddressConfigMode(DLMS_IP6_ADDRESS_CONFIG_MODE value)
    {
        m_AddressConfigMode = value;
    }

    std::vector<IN6_ADDR>& GetUnicastIPAddress()
    {
        return m_UnicastIPAddress;
    }

    void SetUnicastIPAddress(std::vector<IN6_ADDR>& value)
    {
        m_UnicastIPAddress = value;
    }

    std::vector<IN6_ADDR>& GetMulticastIPAddress()
    {
        return m_MulticastIPAddress;
    }

    void setMulticastIPAddress(std::vector<IN6_ADDR>& value)
    {
        m_MulticastIPAddress = value;
    }

    std::vector<IN6_ADDR>& GetGatewayIPAddress()
    {
        return m_GatewayIPAddress;
    }

    void SetGatewayIPAddress(std::vector<IN6_ADDR>& value)
    {
        m_GatewayIPAddress = value;
    }

    IN6_ADDR& GetPrimaryDNSAddress()
    {
        return m_PrimaryDNSAddress;
    }

    void SetPrimaryDNSAddress(IN6_ADDR& value)
    {
        m_PrimaryDNSAddress = value;
    }

    IN6_ADDR& GetSecondaryDNSAddress()
    {
        return m_SecondaryDNSAddress;
    }

    void m_SetSecondaryDNSAddress(IN6_ADDR& value)
    {
        m_SecondaryDNSAddress = value;
    }

    unsigned char GetTrafficClass() {
        return m_TrafficClass;
    }

    void m_SetTrafficClass(unsigned char value) {
        m_TrafficClass = value;
    }

    std::vector<CGXNeighborDiscoverySetup*>& GetNeighborDiscoverySetup() {
        return m_NeighborDiscoverySetup;
    }

    // Returns amount of attributes.
    int GetAttributeCount();

    // Returns amount of methods.
    int GetMethodCount();

    //Get attribute values of object.
    void GetValues(std::vector<std::string>& values);

    /////////////////////////////////////////////////////////////////////////
    // Returns collection of attributes to read.
    //
    // If attribute is static and already read or device is returned
    // HW error it is not returned.
    //
    // all: All items are returned even if they are read already.
    // attributes: Collection of attributes to read.
    void GetAttributeIndexToRead(bool all, std::vector<int>& attributes);

    int GetDataType(int index, DLMS_DATA_TYPE& type);

    // Returns value of given attribute.
    int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    // Set value of given attribute.
    int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);
};
#endif //DLMS_IGNORE_IP6_SETUP
#endif //GXDLMSIP6SETUP_H