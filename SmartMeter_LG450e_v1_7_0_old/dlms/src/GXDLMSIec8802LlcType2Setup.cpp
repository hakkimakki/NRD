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

#include "../include/GXDLMSIec8802LlcType2Setup.h"

#ifndef DLMS_IGNORE_IEC_8802_LLC_TYPE2_SETUP
//Constructor.
CGXDLMSIec8802LlcType2Setup::CGXDLMSIec8802LlcType2Setup() :
    CGXDLMSIec8802LlcType2Setup("0.0.27.1.0.255", 0)
{
}

//SN Constructor.
CGXDLMSIec8802LlcType2Setup::CGXDLMSIec8802LlcType2Setup(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_IEC_8802_LLC_TYPE2_SETUP, ln, sn)
{
    m_TransmitWindowSizeK = 1;
    m_TransmitWindowSizeRW = 1;
    m_MaximumOctetsPdu = 128;
    m_MaximumNumberTransmissions = 0;
    m_AcknowledgementTimer = 0;
    m_BitTimer = 0;
    m_RejectTimer = 0;
    m_BusyStateTimer = 0;
}

//LN Constructor.
CGXDLMSIec8802LlcType2Setup::CGXDLMSIec8802LlcType2Setup(std::string ln) :
    CGXDLMSIec8802LlcType2Setup(ln, 0)
{

}

// Returns amount of attributes.
int CGXDLMSIec8802LlcType2Setup::GetAttributeCount()
{
    return 9;
}

int CGXDLMSIec8802LlcType2Setup::GetMethodCount()
{
    return 0;
}

unsigned char CGXDLMSIec8802LlcType2Setup::GetTransmitWindowSizeK()
{
    return m_TransmitWindowSizeK;
}

void CGXDLMSIec8802LlcType2Setup::SetTransmitWindowSizeK(unsigned char value)
{
    m_TransmitWindowSizeK = value;
}

unsigned char CGXDLMSIec8802LlcType2Setup::GetTransmitWindowSizeRW()
{
    return m_TransmitWindowSizeRW;
}

void CGXDLMSIec8802LlcType2Setup::SetTransmitWindowSizeRW(unsigned char value)
{
    m_TransmitWindowSizeRW = value;
}

uint16_t CGXDLMSIec8802LlcType2Setup::GetMaximumOctetsPdu()
{
    return m_MaximumOctetsPdu;
}

void CGXDLMSIec8802LlcType2Setup::SetMaximumOctetsPdu(uint16_t value)
{
    m_MaximumOctetsPdu = value;
}

unsigned char CGXDLMSIec8802LlcType2Setup::GetMaximumNumberTransmissions()
{
    return m_MaximumNumberTransmissions;
}

void CGXDLMSIec8802LlcType2Setup::SetMaximumNumberTransmissions(unsigned char value)
{
    m_MaximumNumberTransmissions = value;
}

uint16_t CGXDLMSIec8802LlcType2Setup::GetAcknowledgementTimer()
{
    return m_AcknowledgementTimer;
}

void CGXDLMSIec8802LlcType2Setup::SetAcknowledgementTimer(uint16_t value)
{
    m_AcknowledgementTimer = value;
}

uint16_t CGXDLMSIec8802LlcType2Setup::GetBitTimer()
{
    return m_BitTimer;
}

void CGXDLMSIec8802LlcType2Setup::SetBitTimer(uint16_t value)
{
    m_BitTimer = value;
}

uint16_t CGXDLMSIec8802LlcType2Setup::GetRejectTimer()
{
    return m_RejectTimer;
}

void CGXDLMSIec8802LlcType2Setup::SetRejectTimer(uint16_t value)
{
    m_RejectTimer = value;
}

uint16_t CGXDLMSIec8802LlcType2Setup::GetBusyStateTimer()
{
    return m_BusyStateTimer;
}
void CGXDLMSIec8802LlcType2Setup::SetBusyStateTimer(uint16_t value)
{
    m_BusyStateTimer = value;
}

void CGXDLMSIec8802LlcType2Setup::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(GXHelpers::IntToString(m_TransmitWindowSizeK));
    values.push_back(GXHelpers::IntToString(m_TransmitWindowSizeRW));
    values.push_back(GXHelpers::IntToString(m_MaximumOctetsPdu));
    values.push_back(GXHelpers::IntToString(m_MaximumNumberTransmissions));
    values.push_back(GXHelpers::IntToString(m_AcknowledgementTimer));
    values.push_back(GXHelpers::IntToString(m_BitTimer));
    values.push_back(GXHelpers::IntToString(m_RejectTimer));
    values.push_back(GXHelpers::IntToString(m_BusyStateTimer));
}

void CGXDLMSIec8802LlcType2Setup::GetAttributeIndexToRead(bool all, std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (all || CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //TransmitWindowSizeK
    if (all || CanRead(2))
    {
        attributes.push_back(2);
    }
    // TransmitWindowSizeRW
    if (all || CanRead(3))
    {
        attributes.push_back(3);
    }
    // MaximumOctetsPdu
    if (all || CanRead(4))
    {
        attributes.push_back(4);
    }
    // MaximumNumberTransmissions
    if (all || CanRead(5))
    {
        attributes.push_back(5);
    }
    // AcknowledgementTimer
    if (all || CanRead(6))
    {
        attributes.push_back(6);
    }
    // BitTimer
    if (all || CanRead(7))
    {
        attributes.push_back(7);
    }
    // RejectTimer
    if (all || CanRead(8))
    {
        attributes.push_back(8);
    }
    // BusyStateTimer
    if (all || CanRead(9))
    {
        attributes.push_back(9);
    }
}

int CGXDLMSIec8802LlcType2Setup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    int ret = 0;
    switch (index)
    {
    case 1:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 2:
    case 3:
    case 5:
        type = DLMS_DATA_TYPE_UINT8;
        break;
    case 4:
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
int CGXDLMSIec8802LlcType2Setup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
        e.SetValue(m_TransmitWindowSizeK);
        break;
    case 3:
        e.SetValue(m_TransmitWindowSizeRW);
        break;
    case 4:
        e.SetValue(m_MaximumOctetsPdu);
        break;
    case 5:
        e.SetValue(m_MaximumNumberTransmissions);
        break;
    case 6:
        e.SetValue(m_AcknowledgementTimer);
        break;
    case 7:
        e.SetValue(m_BitTimer);
        break;
    case 8:
        e.SetValue(m_RejectTimer);
        break;
    case 9:
        e.SetValue(m_BusyStateTimer);
        break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    }
    return ret;

}

// Set value of given attribute.
int CGXDLMSIec8802LlcType2Setup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = DLMS_ERROR_CODE_OK;
    switch (e.GetIndex())
    {
    case 1:
        ret = SetLogicalName(this, e.GetValue());
        break;
    case 2:
        m_TransmitWindowSizeK = e.GetValue().ToInteger();
        break;
    case 3:
        m_TransmitWindowSizeRW = e.GetValue().ToInteger();
        break;
    case 4:
        m_MaximumOctetsPdu = e.GetValue().ToInteger();
        break;
    case 5:
        m_MaximumNumberTransmissions = e.GetValue().ToInteger();
        break;
    case 6:
        m_AcknowledgementTimer = e.GetValue().ToInteger();
        break;
    case 7:
        m_BitTimer = e.GetValue().ToInteger();
        break;
    case 8:
        m_RejectTimer = e.GetValue().ToInteger();
        break;
    case 9:
        m_BusyStateTimer = e.GetValue().ToInteger();
        break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    }
    return ret;
}
#endif //DLMS_IGNORE_IEC_8802_LLC_TYPE2_SETUP
