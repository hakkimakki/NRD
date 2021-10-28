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

#include "../include/GXDLMSIp6Setup.h"
#ifndef DLMS_IGNORE_IP6_SETUP
//Constructor.
CGXDLMSIp6Setup::CGXDLMSIp6Setup() :
    CGXDLMSIp6Setup("0.0.25.7.0.255", 0)
{
}

//SN Constructor.
CGXDLMSIp6Setup::CGXDLMSIp6Setup(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_IP6_SETUP, ln, sn)
{

}

//LN Constructor.
CGXDLMSIp6Setup::CGXDLMSIp6Setup(std::string ln) :
    CGXDLMSIp6Setup(ln, 0)
{

}

CGXDLMSIp6Setup::~CGXDLMSIp6Setup()
{
    for (std::vector<CGXNeighborDiscoverySetup*>::iterator it = m_NeighborDiscoverySetup.begin();
        it != m_NeighborDiscoverySetup.end(); ++it)
    {
        delete* it;
    }
    m_NeighborDiscoverySetup.clear();
}

// Returns amount of attributes.
int CGXDLMSIp6Setup::GetAttributeCount()
{
    return 10;
}

// Returns amount of methods.
int CGXDLMSIp6Setup::GetMethodCount()
{
    return 2;
}


int GetIPAddress(std::vector<std::string>& values, std::vector<IN6_ADDR>& list)
{
    char tmp[64];
    std::string sb = "{";
    bool first = true;
    if (!list.empty())
    {
        for (std::vector<IN6_ADDR>::iterator it = list.begin(); it != list.end(); ++it)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                sb += ", ";
            }
            inet_ntop(AF_INET6, &(*it), tmp, sizeof(tmp));
            sb += tmp;
        }
    }
    sb += "}";
    values.push_back(sb);
    return 0;
}

int GetNeighborDiscoverySetupAsString(std::vector< std::string >& values, std::vector<CGXNeighborDiscoverySetup*>& list)
{
    std::string sb = "{";
    bool first = true;
    for (std::vector<CGXNeighborDiscoverySetup*>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            sb += ", ";
        }
        sb += "[";
        sb += GXHelpers::IntToString((*it)->GetMaxRetry());
        sb += ", ";
        sb += GXHelpers::IntToString((*it)->GetRetryWaitTime());
        sb += ", ";
        sb += GXHelpers::IntToString((*it)->GetSendPeriod());
        sb += "]";
    }
    sb += "}";
    values.push_back(sb);
    return 0;
}

void CGXDLMSIp6Setup::GetValues(std::vector<std::string>& values)
{
    char tmp[64];
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(m_DataLinkLayerReference);
    values.push_back(GXHelpers::IntToString(m_AddressConfigMode));
    GetIPAddress(values, m_UnicastIPAddress);
    GetIPAddress(values, m_MulticastIPAddress);
    GetIPAddress(values, m_GatewayIPAddress);
    inet_ntop(AF_INET6, &m_PrimaryDNSAddress, tmp, sizeof(tmp));
    values.push_back(tmp);
    inet_ntop(AF_INET6, &m_SecondaryDNSAddress, tmp, sizeof(tmp));
    values.push_back(tmp);
    values.push_back(GXHelpers::IntToString(m_TrafficClass));
    GetNeighborDiscoverySetupAsString(values, m_NeighborDiscoverySetup);
}

void CGXDLMSIp6Setup::GetAttributeIndexToRead(bool all, std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (all || CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    // DataLinkLayerReference
    if (all || CanRead(2))
    {
        attributes.push_back(2);
    }
    // AddressConfigMode
    if (all || CanRead(3)) {
        attributes.push_back(3);
    }
    // UnicastIPAddress
    if (all || CanRead(4)) {
        attributes.push_back(4);
    }
    // MulticastIPAddress
    if (all || CanRead(5)) {
        attributes.push_back(5);
    }
    // GatewayIPAddress
    if (all || CanRead(6)) {
        attributes.push_back(6);
    }
    // PrimaryDNSAddress
    if (all || CanRead(7)) {
        attributes.push_back(7);
    }
    // SecondaryDNSAddress
    if (all || !IsRead(8)) {
        attributes.push_back(8);
    }
    // TrafficClass
    if (all || CanRead(9)) {
        attributes.push_back(9);
    }
    // NeighborDiscoverySetup
    if (all || CanRead(10)) {
        attributes.push_back(10);
    }
}

int CGXDLMSIp6Setup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    switch (index) {
    case 1:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 2:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 3:
        type = DLMS_DATA_TYPE_ENUM;
        break;
    case 4:
        type = DLMS_DATA_TYPE_ARRAY;
        break;
    case 5:
        type = DLMS_DATA_TYPE_ARRAY;
        break;
    case 6:
        type = DLMS_DATA_TYPE_ARRAY;
        break;
    case 7:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 8:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 9:
        type = DLMS_DATA_TYPE_UINT8;
        break;
    case 10:
        type = DLMS_DATA_TYPE_ARRAY;
        break;
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

int GetAddress(CGXDLMSSettings& settings, std::vector<IN6_ADDR>& list, CGXDLMSValueEventArg& e)
{
    int ret = 0;
    e.SetByteArray(true);
    CGXByteBuffer data;
    data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
    GXHelpers::SetObjectCount((unsigned long)list.size(), data);
    CGXDLMSVariant tmp;
    for (std::vector<IN6_ADDR>::iterator it = list.begin(); it != list.end(); ++it)
    {
#if defined(_WIN32) || defined(_WIN64)//Windows includes
        tmp.byteArr = it->u.Byte;
#else //Linux includes.
        tmp.byteArr = it->s6_addr;
#endif
        tmp.size = 16;
        tmp.vt = DLMS_DATA_TYPE_OCTET_STRING;
        ret = GXHelpers::SetData(&settings, data, DLMS_DATA_TYPE_OCTET_STRING, tmp);
        tmp.vt = DLMS_DATA_TYPE_NONE;
        if (ret != 0)
        {
            break;
        }
    }
    if (ret == 0)
    {
        e.SetValue(data);
    }
    return ret;
}

// Returns value of given attribute.
int CGXDLMSIp6Setup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    CGXDLMSVariant tmp;
    int ret = 0;
    switch (e.GetIndex())
    {
    case 1:
    {
        if ((ret = GetLogicalName(this, tmp)) == 0)
        {
            e.SetValue(tmp);
        }
        break;
    }
    case 2:
    {
        GXHelpers::SetLogicalName(m_DataLinkLayerReference.c_str(), tmp);
        e.SetValue(tmp);
    }
    break;
    case 3:
        e.SetValue((unsigned char)m_AddressConfigMode);
        break;
    case 4:
        ret = GetAddress(settings, m_UnicastIPAddress, e);
        break;
    case 5:
        ret = GetAddress(settings, m_MulticastIPAddress, e);
        break;
    case 6:
        ret = GetAddress(settings, m_GatewayIPAddress, e);
        break;
    case 7:
    {
        e.SetByteArray(true);
        CGXByteBuffer data;
#if defined(_WIN32) || defined(_WIN64)//Windows includes
        tmp.byteArr = m_PrimaryDNSAddress.u.Byte;
#else //Linux includes.
        tmp.byteArr = m_PrimaryDNSAddress.s6_addr;
#endif
        tmp.size = 16;
        tmp.vt = DLMS_DATA_TYPE_OCTET_STRING;
        ret = GXHelpers::SetData(&settings, data, DLMS_DATA_TYPE_OCTET_STRING, tmp);
        tmp.vt = DLMS_DATA_TYPE_NONE;
        if (ret == 0)
        {
            e.SetValue(data);
        }
    }
    break;
    case 8:
    {
        e.SetByteArray(true);
        CGXByteBuffer data;
#if defined(_WIN32) || defined(_WIN64)//Windows includes
        tmp.byteArr = m_SecondaryDNSAddress.u.Byte;
#else //Linux includes.
        tmp.byteArr = m_SecondaryDNSAddress.s6_addr;
#endif
        tmp.size = 16;
        tmp.vt = DLMS_DATA_TYPE_OCTET_STRING;
        ret = GXHelpers::SetData(&settings, data, DLMS_DATA_TYPE_OCTET_STRING, tmp);
        tmp.vt = DLMS_DATA_TYPE_NONE;
        if (ret == 0)
        {
            e.SetValue(data);
        }
    }
    break;
    case 9:
        e.SetValue((unsigned char)m_TrafficClass);
        break;
    case 10:
    {
        e.SetByteArray(true);
        CGXByteBuffer data;
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        GXHelpers::SetObjectCount((unsigned long)m_NeighborDiscoverySetup.size(), data);
        for (std::vector<CGXNeighborDiscoverySetup*>::iterator it = m_NeighborDiscoverySetup.begin();
            it != m_NeighborDiscoverySetup.end(); ++it)
        {
            data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
            data.SetUInt8(3);
            GXHelpers::SetData2(&settings, data, DLMS_DATA_TYPE_UINT8, (*it)->GetMaxRetry());
            GXHelpers::SetData2(&settings, data, DLMS_DATA_TYPE_UINT16, (*it)->GetRetryWaitTime());
            GXHelpers::SetData2(&settings, data, DLMS_DATA_TYPE_UINT32, (*it)->GetSendPeriod());
        }
        e.SetValue(data);
    }
    break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    }
    return ret;
}

// Set value of given attribute.
int CGXDLMSIp6Setup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetValue());
    }
    else if (e.GetIndex() == 2)
    {
        if (e.GetValue().vt == DLMS_DATA_TYPE_STRING)
        {
            m_DataLinkLayerReference = e.GetValue().ToString();
        }
        else
        {
            m_DataLinkLayerReference.clear();
            GXHelpers::GetLogicalName(e.GetValue().byteArr, m_DataLinkLayerReference);
        }
    }
    else if (e.GetIndex() == 3)
    {
        m_AddressConfigMode = (DLMS_IP6_ADDRESS_CONFIG_MODE)e.GetValue().ToInteger();
    }
    else if (e.GetIndex() == 4)
    {
        m_UnicastIPAddress.clear();
        if (e.GetValue().vt == DLMS_DATA_TYPE_ARRAY)
        {
            for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            {
                if (it->GetSize() != 16)
                {
                    return DLMS_ERROR_CODE_INCONSISTENT_CLASS_OR_OBJECT;
                }
                m_UnicastIPAddress.push_back(*((IN6_ADDR*)it->byteArr));
            }
        }
    }
    else if (e.GetIndex() == 5)
    {
        m_MulticastIPAddress.clear();
        if (e.GetValue().vt == DLMS_DATA_TYPE_ARRAY)
        {
            for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            {
                if (it->GetSize() != 16)
                {
                    return DLMS_ERROR_CODE_INCONSISTENT_CLASS_OR_OBJECT;
                }
                m_MulticastIPAddress.push_back(*((IN6_ADDR*)it->byteArr));
            }
        }
    }
    else if (e.GetIndex() == 6)
    {
        m_GatewayIPAddress.clear();
        if (e.GetValue().vt == DLMS_DATA_TYPE_ARRAY)
        {
            for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            {
                if (it->GetSize() != 16)
                {
                    return DLMS_ERROR_CODE_INCONSISTENT_CLASS_OR_OBJECT;
                }
                m_GatewayIPAddress.push_back(*((IN6_ADDR*)it->byteArr));
            }
        }
    }
    else if (e.GetIndex() == 7)
    {
        if (e.GetValue().GetSize() != 16)
        {
            return DLMS_ERROR_CODE_INCONSISTENT_CLASS_OR_OBJECT;
        }
        m_PrimaryDNSAddress = *((IN6_ADDR*)e.GetValue().byteArr);
    }
    else if (e.GetIndex() == 8)
    {
        if (e.GetValue().GetSize() != 16)
        {
            return DLMS_ERROR_CODE_INCONSISTENT_CLASS_OR_OBJECT;
        }
        m_SecondaryDNSAddress = *((IN6_ADDR*)e.GetValue().byteArr);
    }
    else if (e.GetIndex() == 9)
    {
        m_TrafficClass = (DLMS_IP6_ADDRESS_CONFIG_MODE)e.GetValue().ToInteger();
    }
    else if (e.GetIndex() == 10)
    {
        m_NeighborDiscoverySetup.clear();
        if (e.GetValue().vt == DLMS_DATA_TYPE_ARRAY)
        {
            for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            {
                CGXNeighborDiscoverySetup* v = new CGXNeighborDiscoverySetup();
                v->SetMaxRetry(it->Arr[0].ToInteger());
                v->SetRetryWaitTime(it->Arr[1].ToInteger());
                v->SetSendPeriod(it->Arr[2].ToInteger());
                m_NeighborDiscoverySetup.push_back(v);
            }
        }
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

#endif //DLMS_IGNORE_IP6_SETUP