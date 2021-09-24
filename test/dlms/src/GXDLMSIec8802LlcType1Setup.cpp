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

#include "../include/GXDLMSIec8802LlcType1Setup.h"

#ifndef DLMS_IGNORE_IEC_8802_LLC_TYPE1_SETUP
//Constructor.
CGXDLMSIec8802LlcType1Setup::CGXDLMSIec8802LlcType1Setup() :
    CGXDLMSIec8802LlcType1Setup("0.0.27.0.0.255", 0)
{
}

//SN Constructor.
CGXDLMSIec8802LlcType1Setup::CGXDLMSIec8802LlcType1Setup(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_IEC_8802_LLC_TYPE1_SETUP, ln, sn)
{

}

//LN Constructor.
CGXDLMSIec8802LlcType1Setup::CGXDLMSIec8802LlcType1Setup(std::string ln) :
    CGXDLMSIec8802LlcType1Setup(ln, 0)
{

}

uint16_t CGXDLMSIec8802LlcType1Setup::GetMaximumOctetsUiPdu()
{
    return m_MaximumOctetsUiPdu;
}

void CGXDLMSIec8802LlcType1Setup::SetMaximumOctetsUiPdu(uint16_t value)
{
    m_MaximumOctetsUiPdu = 128;
}

// Returns amount of attributes.
int CGXDLMSIec8802LlcType1Setup::GetAttributeCount()
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSIec8802LlcType1Setup::GetMethodCount()
{
    return 0;
}

void CGXDLMSIec8802LlcType1Setup::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(GXHelpers::IntToString(m_MaximumOctetsUiPdu));
}

void CGXDLMSIec8802LlcType1Setup::GetAttributeIndexToRead(bool all, std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (all || CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //MaximumOctetsUiPdu
    if (all || CanRead(2))
    {
        attributes.push_back(2);
    }
}

int CGXDLMSIec8802LlcType1Setup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSIec8802LlcType1Setup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = 0;
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
        e.SetValue(m_MaximumOctetsUiPdu);
    }
    else
    {
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}

// Set value of given attribute.
int CGXDLMSIec8802LlcType1Setup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetValue());
    }
    else if (e.GetIndex() == 2)
    {
        m_MaximumOctetsUiPdu = e.GetValue().ToInteger();
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
#endif //DLMS_IGNORE_IEC_8802_LLC_TYPE1_SETUP