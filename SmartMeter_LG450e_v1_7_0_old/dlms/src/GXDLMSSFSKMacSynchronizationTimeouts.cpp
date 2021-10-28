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

#include "../include/GXDLMSSFSKMacSynchronizationTimeouts.h"

#ifndef DLMS_IGNORE_SFSK_MAC_SYNCHRONIZATION_TIMEOUTS
//Constructor.
CGXDLMSSFSKMacSynchronizationTimeouts::CGXDLMSSFSKMacSynchronizationTimeouts() :
    CGXDLMSSFSKMacSynchronizationTimeouts("0.0.26.2.0.255", 0)
{
}

//SN Constructor.
CGXDLMSSFSKMacSynchronizationTimeouts::CGXDLMSSFSKMacSynchronizationTimeouts(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_SFSK_MAC_SYNCHRONIZATION_TIMEOUTS, ln, sn)
{

}

//LN Constructor.
CGXDLMSSFSKMacSynchronizationTimeouts::CGXDLMSSFSKMacSynchronizationTimeouts(std::string ln) :
    CGXDLMSSFSKMacSynchronizationTimeouts(ln, 0)
{
    m_SearchInitiatorTimeout = 0;
    m_SynchronizationConfirmationTimeout = 0;
    m_TimeOutNotAddressed = 0;
    m_TimeOutFrameNotOK = 0;
}

int CGXDLMSSFSKMacSynchronizationTimeouts::GetSearchInitiatorTimeout()
{
    return m_SearchInitiatorTimeout;
}

void CGXDLMSSFSKMacSynchronizationTimeouts::SetSearchInitiatorTimeout(uint32_t value)
{
    m_SearchInitiatorTimeout = value;
}

uint32_t CGXDLMSSFSKMacSynchronizationTimeouts::GetSynchronizationConfirmationTimeout()
{
    return m_SynchronizationConfirmationTimeout;
}

void CGXDLMSSFSKMacSynchronizationTimeouts::SetSynchronizationConfirmationTimeout(uint32_t value)
{
    m_SynchronizationConfirmationTimeout = value;
}

uint32_t CGXDLMSSFSKMacSynchronizationTimeouts::GetTimeOutNotAddressed()
{
    return m_TimeOutNotAddressed;
}

void CGXDLMSSFSKMacSynchronizationTimeouts::SetTimeOutNotAddressed(uint32_t value)
{
    m_TimeOutNotAddressed = value;
}

uint32_t CGXDLMSSFSKMacSynchronizationTimeouts::GetTimeOutFrameNotOK()
{
    return m_TimeOutFrameNotOK;
}

void CGXDLMSSFSKMacSynchronizationTimeouts::SetTimeOutFrameNotOK(uint32_t value)
{
    m_TimeOutFrameNotOK = value;
}


// Returns amount of attributes.
int CGXDLMSSFSKMacSynchronizationTimeouts::GetAttributeCount()
{
    return 5;
}

// Returns amount of methods.
int CGXDLMSSFSKMacSynchronizationTimeouts::GetMethodCount()
{
    return 0;
}

void CGXDLMSSFSKMacSynchronizationTimeouts::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(GXHelpers::IntToString(m_SearchInitiatorTimeout));
    values.push_back(GXHelpers::IntToString(m_SynchronizationConfirmationTimeout));
    values.push_back(GXHelpers::IntToString(m_TimeOutNotAddressed));
    values.push_back(GXHelpers::IntToString(m_TimeOutFrameNotOK));
}

void CGXDLMSSFSKMacSynchronizationTimeouts::GetAttributeIndexToRead(bool all, std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (all || CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //SearchInitiatorTimeout
    if (all || CanRead(2))
    {
        attributes.push_back(2);
    }
    // SynchronizationConfirmationTimeout
    if (all || CanRead(3))
    {
        attributes.push_back(3);
    }
    // TimeOutNotAddressed
    if (all || CanRead(4))
    {
        attributes.push_back(4);
    }
    // TimeOutFrameNotOK
    if (all || CanRead(5))
    {
        attributes.push_back(5);
    }
}

int CGXDLMSSFSKMacSynchronizationTimeouts::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    switch (index) {
    case 1:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        type = DLMS_DATA_TYPE_UINT16;
        break;
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSSFSKMacSynchronizationTimeouts::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = 0;
    switch (e.GetIndex())
    {
    case 1:
    {
        CGXDLMSVariant tmp;
        if ((ret = GetLogicalName(this, tmp)) == 0)
        {
            e.SetValue(tmp);
        }
    }
    break;
    case 2:
        e.SetValue(m_SearchInitiatorTimeout);
        break;
    case 3:
        e.SetValue(m_SynchronizationConfirmationTimeout);
        break;
    case 4:
        e.SetValue(m_TimeOutNotAddressed);
        break;
    case 5:
        e.SetValue(m_TimeOutFrameNotOK);
        break;
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}

// Set value of given attribute.
int CGXDLMSSFSKMacSynchronizationTimeouts::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = 0;
    switch (e.GetIndex())
    {
    case 1:
        ret = SetLogicalName(this, e.GetValue());
        break;
    case 2:
        m_SearchInitiatorTimeout = e.GetValue().ToInteger();
        break;
    case 3:
        m_SynchronizationConfirmationTimeout = e.GetValue().ToInteger();
        break;
    case 4:
        m_TimeOutNotAddressed = e.GetValue().ToInteger();
        break;
    case 5:
        m_TimeOutFrameNotOK = e.GetValue().ToInteger();
        break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}
#endif //DLMS_IGNORE_SFSK_MAC_SYNCHRONIZATION_TIMEOUTS