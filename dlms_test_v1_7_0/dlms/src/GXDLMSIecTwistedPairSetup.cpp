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

#include "../include/GXDLMSIecTwistedPairSetup.h"

#ifndef DLMS_IGNORE_IEC_TWISTED_PAIR_SETUP

//Constructor.
CGXDLMSIecTwistedPairSetup::CGXDLMSIecTwistedPairSetup() :
    CGXDLMSIecTwistedPairSetup("0.0.23.0.0.255", 0)
{
}

//SN Constructor.
CGXDLMSIecTwistedPairSetup::CGXDLMSIecTwistedPairSetup(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_IEC_TWISTED_PAIR_SETUP, ln, sn)
{

}

//LN Constructor.
CGXDLMSIecTwistedPairSetup::CGXDLMSIecTwistedPairSetup(std::string ln) :
    CGXDLMSIecTwistedPairSetup(ln, 0)
{

}

DLMS_IEC_TWISTED_PAIR_SETUP_MODE CGXDLMSIecTwistedPairSetup::GetMode()
{
    return m_Mode;
}

void CGXDLMSIecTwistedPairSetup::SetMode(DLMS_IEC_TWISTED_PAIR_SETUP_MODE value)
{
    m_Mode = value;
}

DLMS_BAUD_RATE CGXDLMSIecTwistedPairSetup::GetSpeed()
{
    return m_Speed;
}

void CGXDLMSIecTwistedPairSetup::SetSpeed(DLMS_BAUD_RATE value)
{
    m_Speed = value;
}

std::vector<unsigned char>& CGXDLMSIecTwistedPairSetup::GetPrimaryAddresses()
{
    return m_PrimaryAddresses;
}

std::vector<char>& CGXDLMSIecTwistedPairSetup::GetTabis()
{
    return m_Tabis;
}

// Returns amount of attributes.
int CGXDLMSIecTwistedPairSetup::GetAttributeCount()
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSIecTwistedPairSetup::GetMethodCount()
{
    return 0;
}

void CGXDLMSIecTwistedPairSetup::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(GXHelpers::IntToString(m_Mode));
    values.push_back(GXHelpers::IntToString(m_Speed));
    std::stringstream sb;
    sb << "{";
    bool empty = true;
    for (std::vector<unsigned char>::iterator it = m_PrimaryAddresses.begin(); it != m_PrimaryAddresses.end(); ++it)
    {
        if (empty)
        {
            empty = false;
        }
        else
        {
            sb << ',';
        }
        sb << GXHelpers::IntToString(*it);
    }
    sb << "}";
    values.push_back(sb.str());
    sb.clear();
    sb << "{";
    empty = true;
    for (std::vector<char>::iterator it = m_Tabis.begin(); it != m_Tabis.end(); ++it)
    {
        if (empty)
        {
            empty = false;
        }
        else
        {
            sb << ',';
        }
        sb << GXHelpers::IntToString(*it);
    }
    sb << "}";
    values.push_back(sb.str());
}

void CGXDLMSIecTwistedPairSetup::GetAttributeIndexToRead(bool all, std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (all || CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //Mode
    if (all || CanRead(2))
    {
        attributes.push_back(2);
    }
    //Speed
    if (all || CanRead(3))
    {
        attributes.push_back(3);
    }
    //PrimaryAddresses
    if (all || CanRead(4))
    {
        attributes.push_back(4);
    }
    //Tabis
    if (all || CanRead(5))
    {
        attributes.push_back(5);
    }
}

int CGXDLMSIecTwistedPairSetup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    switch (index)
    {
    case 1:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 2:
    case 3:
        type = DLMS_DATA_TYPE_ENUM;
        break;
    case 4:
    case 5:
        type = DLMS_DATA_TYPE_ARRAY;
        break;
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return 0;
}

// Returns value of given attribute.
int CGXDLMSIecTwistedPairSetup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
        e.SetValue(m_Mode);
        break;
    case 3:
        e.SetValue(m_Speed);
        break;
    case 4:
    {
        CGXByteBuffer data;
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        data.SetUInt8((unsigned char)m_PrimaryAddresses.size());
        for (std::vector<unsigned char>::iterator it = m_PrimaryAddresses.begin(); it != m_PrimaryAddresses.end(); ++it)
        {
            if ((ret = data.SetUInt8(DLMS_DATA_TYPE_UINT8)) != 0 ||
                (ret = data.SetUInt8(*it)) != 0)
            {
                break;
            }
        }
        e.SetValue(data);
        break;
    }

    case 5:
    {
        CGXByteBuffer data;
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        data.SetUInt8((unsigned char)m_Tabis.size());
        for (std::vector<char>::iterator it = m_Tabis.begin(); it != m_Tabis.end(); ++it)
        {
            if ((ret = data.SetUInt8(DLMS_DATA_TYPE_INT8)) != 0 ||
                (ret = data.SetUInt8(*it)) != 0)
            {
                break;
            }
        }
        e.SetValue(data);
        break;
    }
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    }
    return ret;
}

// Set value of given attribute.
int CGXDLMSIecTwistedPairSetup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = DLMS_ERROR_CODE_OK;
    switch (e.GetIndex())
    {
    case 1:
        return SetLogicalName(this, e.GetValue());
        break;
    case 2:
        m_Mode = (DLMS_IEC_TWISTED_PAIR_SETUP_MODE)e.GetValue().ToInteger();
        break;
    case 3:
        m_Speed = (DLMS_BAUD_RATE)e.GetValue().ToInteger();
        break;
    case 4:
    {
        m_PrimaryAddresses.clear();
        if (e.GetValue().vt == DLMS_DATA_TYPE_ARRAY)
        {
            for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            {
                m_PrimaryAddresses.push_back(it->ToInteger());
            }
        }
        break;
    }
    case 5:
    {
        m_Tabis.clear();
        if (e.GetValue().vt == DLMS_DATA_TYPE_ARRAY)
        {
            for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            {
                m_Tabis.push_back(it->ToInteger());
            }
        }
        break;
    }
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    }
    return ret;
}
#endif //DLMS_IGNORE_IEC_TWISTED_PAIR_SETUP