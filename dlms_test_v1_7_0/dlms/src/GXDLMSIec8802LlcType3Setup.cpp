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

#include "../include/GXDLMSIec8802LlcType3Setup.h"

#ifndef DLMS_IGNORE_IEC_8802_LLC_TYPE3_SETUP
//Constructor.
CGXDLMSIec8802LlcType3Setup::CGXDLMSIec8802LlcType3Setup() :
    CGXDLMSIec8802LlcType3Setup("", 0)
{
}

//SN Constructor.
CGXDLMSIec8802LlcType3Setup::CGXDLMSIec8802LlcType3Setup(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_IEC_8802_LLC_TYPE3_SETUP, ln, sn)
{
    m_MaximumOctetsACnPdu = 0;
    m_MaximumTransmissions = 0;
    m_AcknowledgementTime = 0;
    m_ReceiveLifetime = 0;
    m_TransmitLifetime = 0;
}

//LN Constructor.
CGXDLMSIec8802LlcType3Setup::CGXDLMSIec8802LlcType3Setup(std::string ln) :
    CGXDLMSIec8802LlcType3Setup(ln, 0)
{

}

uint16_t CGXDLMSIec8802LlcType3Setup::GetMaximumOctetsACnPdu()
{
    return m_MaximumOctetsACnPdu;
}

void CGXDLMSIec8802LlcType3Setup::SetMaximumOctetsACnPdu(uint16_t value)
{
    m_MaximumOctetsACnPdu = value;
}

unsigned char CGXDLMSIec8802LlcType3Setup::GetMaximumTransmissions()
{
    return m_MaximumTransmissions;
}

void CGXDLMSIec8802LlcType3Setup::SetMaximumTransmissions(unsigned char value)
{
    m_MaximumTransmissions = value;
}

uint16_t CGXDLMSIec8802LlcType3Setup::GetAcknowledgementTime()
{
    return m_AcknowledgementTime;
}

void CGXDLMSIec8802LlcType3Setup::SetAcknowledgementTime(uint16_t value)
{
    m_AcknowledgementTime = value;
}

uint16_t CGXDLMSIec8802LlcType3Setup::GetReceiveLifetime()
{
    return m_ReceiveLifetime;
}

void CGXDLMSIec8802LlcType3Setup::SetReceiveLifetime(uint16_t value)
{
    m_ReceiveLifetime = value;
}

uint16_t CGXDLMSIec8802LlcType3Setup::GetTransmitLifetime()
{
    return m_TransmitLifetime;
}

void CGXDLMSIec8802LlcType3Setup::SetTransmitLifetime(uint16_t value)
{
    m_TransmitLifetime = value;
}

int CGXDLMSIec8802LlcType3Setup::GetAttributeCount()
{
    return 6;
}

int CGXDLMSIec8802LlcType3Setup::GetMethodCount()
{
    return 0;
}

void CGXDLMSIec8802LlcType3Setup::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(GXHelpers::IntToString(m_MaximumOctetsACnPdu));
    values.push_back(GXHelpers::IntToString(m_MaximumTransmissions));
    values.push_back(GXHelpers::IntToString(m_AcknowledgementTime));
    values.push_back(GXHelpers::IntToString(m_ReceiveLifetime));
    values.push_back(GXHelpers::IntToString(m_TransmitLifetime));
}

void CGXDLMSIec8802LlcType3Setup::GetAttributeIndexToRead(bool all, std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (all || CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //MaximumOctetsACnPdu
    if (all || CanRead(2))
    {
        attributes.push_back(2);
    }
    // MaximumTransmissions
    if (all || CanRead(3))
    {
        attributes.push_back(3);
    }
    // AcknowledgementTime
    if (all || CanRead(4))
    {
        attributes.push_back(4);
    }
    // ReceiveLifetime
    if (all || CanRead(5))
    {
        attributes.push_back(5);
    }
    // TransmitLifetime
    if (all || CanRead(6))
    {
        attributes.push_back(6);
    }
}

int CGXDLMSIec8802LlcType3Setup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    int ret = DLMS_ERROR_CODE_OK;
    switch (index) {
    case 1:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 3:
        type = DLMS_DATA_TYPE_UINT8;
        break;
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        type = DLMS_DATA_TYPE_UINT16;
        break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}

// Returns value of given attribute.
int CGXDLMSIec8802LlcType3Setup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
        e.SetValue(m_MaximumOctetsACnPdu);
        break;
    case 3:
        e.SetValue(m_MaximumTransmissions);
        break;
    case 4:
        e.SetValue(m_AcknowledgementTime);
        break;
    case 5:
        e.SetValue(m_ReceiveLifetime);
        break;
    case 6:
        e.SetValue(m_TransmitLifetime);
        break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    }
    return ret;
}

// Set value of given attribute.
int CGXDLMSIec8802LlcType3Setup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = DLMS_ERROR_CODE_OK;
    switch (e.GetIndex())
    {
    case 1:
        ret = SetLogicalName(this, e.GetValue());
        break;
    case 2:
        m_MaximumOctetsACnPdu = e.GetValue().ToInteger();
        break;
    case 3:
        m_MaximumTransmissions = e.GetValue().ToInteger();
        break;
    case 4:
        m_AcknowledgementTime = e.GetValue().ToInteger();
        break;
    case 5:
        m_ReceiveLifetime = e.GetValue().ToInteger();
        break;
    case 6:
        m_TransmitLifetime = e.GetValue().ToInteger();
        break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    }
    return ret;
}

#endif //DLMS_IGNORE_IEC_8802_LLC_TYPE3_SETUP