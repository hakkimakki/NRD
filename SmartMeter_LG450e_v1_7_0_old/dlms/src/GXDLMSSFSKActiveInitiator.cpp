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

#include "../include/GXDLMSSFSKActiveInitiator.h"

#ifndef DLMS_IGNORE_SFSK_ACTIVE_INITIATOR
//Constructor.
CGXDLMSSFSKActiveInitiator::CGXDLMSSFSKActiveInitiator() :
    CGXDLMSSFSKActiveInitiator("0.0.26.1.0.255", 0)
{
}

//SN Constructor.
CGXDLMSSFSKActiveInitiator::CGXDLMSSFSKActiveInitiator(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_SFSK_ACTIVE_INITIATOR, ln, sn)
{

}

//LN Constructor.
CGXDLMSSFSKActiveInitiator::CGXDLMSSFSKActiveInitiator(std::string ln) :
    CGXDLMSSFSKActiveInitiator(ln, 0)
{

}

CGXByteBuffer& CGXDLMSSFSKActiveInitiator::GetSystemTitle()
{
    return m_SystemTitle;
}

void CGXDLMSSFSKActiveInitiator::SetSystemTitle(CGXByteBuffer& value)
{
    m_SystemTitle = value;
}

uint16_t CGXDLMSSFSKActiveInitiator::GetMacAddress()
{
    return m_MacAddress;
}

void CGXDLMSSFSKActiveInitiator::SetMacAddress(uint16_t value)
{
    m_MacAddress = value;
}

unsigned char CGXDLMSSFSKActiveInitiator::GetLSapSelector()
{
    return m_LSapSelector;
}

void CGXDLMSSFSKActiveInitiator::SetLSapSelector(unsigned char value)
{
    m_LSapSelector = value;
}

// Returns amount of attributes.
int CGXDLMSSFSKActiveInitiator::GetAttributeCount()
{
    return 1;
}

// Returns amount of methods.
int CGXDLMSSFSKActiveInitiator::GetMethodCount()
{
    return 1;
}

void CGXDLMSSFSKActiveInitiator::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    std::stringstream sb;
    sb << m_SystemTitle.ToHexString(false);
    sb << ", ";
    sb << GXHelpers::IntToString(m_MacAddress);
    sb << ", ";
    sb << GXHelpers::IntToString(m_LSapSelector);
    values.push_back(sb.str());
}

void CGXDLMSSFSKActiveInitiator::GetAttributeIndexToRead(bool all, std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (all || CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    // Active Initiator
    if (all || CanRead(2))
    {
        attributes.push_back(2);
    }
}

int CGXDLMSSFSKActiveInitiator::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSSFSKActiveInitiator::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret;
    if (e.GetIndex() == 1)
    {
        CGXDLMSVariant tmp;
        if ((ret = GetLogicalName(this, tmp)) == 0)
        {
            e.SetValue(tmp);
        }
    }
    else if (e.GetIndex() == 2)
    {
        CGXByteBuffer bb;
        if ((ret = bb.SetUInt8(DLMS_DATA_TYPE_STRUCTURE)) == 0 &&
            (ret = bb.SetUInt8(3)) == 0 &&
            (ret = GXHelpers::SetData2(&settings, bb, DLMS_DATA_TYPE_OCTET_STRING, m_SystemTitle)) == 0 &&
            (ret = GXHelpers::SetData2(&settings, bb, DLMS_DATA_TYPE_UINT16, m_MacAddress)) == 0 &&
            (ret = GXHelpers::SetData2(&settings, bb, DLMS_DATA_TYPE_UINT8, m_LSapSelector)) == 0)
        {
            e.SetValue(bb);
        }
    }
    else
    {
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}

// Set value of given attribute.
int CGXDLMSSFSKActiveInitiator::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = 0;
    switch (e.GetIndex())
    {
    case 1:
        ret = SetLogicalName(this, e.GetValue());
        break;
    case 2:
        if (e.GetValue().vt == DLMS_DATA_TYPE_STRUCTURE)
        {
            m_SystemTitle.Clear();
            e.GetValue().Arr[0].GetBytes(m_SystemTitle);
            m_MacAddress = e.GetValue().Arr[1].ToInteger();
            m_LSapSelector = e.GetValue().Arr[2].ToInteger();
        }
        else
        {
            m_SystemTitle.Clear();
            m_MacAddress = 0;
            m_LSapSelector = 0;
        }
        break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}
#endif //DLMS_IGNORE_SFSK_ACTIVE_INITIATOR