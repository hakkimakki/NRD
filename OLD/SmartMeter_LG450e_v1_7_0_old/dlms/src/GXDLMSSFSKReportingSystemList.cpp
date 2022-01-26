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

#include "../include/GXDLMSSFSKReportingSystemList.h"

#ifndef DLMS_IGNORE_SFSK_REPORTING_SYSTEM_LIST
//Constructor.
CGXDLMSSFSKReportingSystemList::CGXDLMSSFSKReportingSystemList() :
    CGXDLMSSFSKReportingSystemList("0.0.26.6.0.255", 0)
{
}

//SN Constructor.
CGXDLMSSFSKReportingSystemList::CGXDLMSSFSKReportingSystemList(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_SFSK_REPORTING_SYSTEM_LIST, ln, sn)
{

}

//LN Constructor.
CGXDLMSSFSKReportingSystemList::CGXDLMSSFSKReportingSystemList(std::string ln) :
    CGXDLMSSFSKReportingSystemList(ln, 0)
{

}

// Returns amount of attributes.
int CGXDLMSSFSKReportingSystemList::GetAttributeCount()
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSSFSKReportingSystemList::GetMethodCount()
{
    return 0;
}

void CGXDLMSSFSKReportingSystemList::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);

    std::stringstream sb;
    sb << '[';
    bool empty = true;
    for (std::vector<CGXByteBuffer>::iterator it = m_ReportingSystemList.begin(); it != m_ReportingSystemList.end(); ++it)
    {
        if (!empty)
        {
            sb << ", ";
        }
        else
        {
            empty = false;
        }
        sb << it->ToHexString(false);
    }
    sb << ']';
    values.push_back(sb.str());
}

void CGXDLMSSFSKReportingSystemList::GetAttributeIndexToRead(bool all, std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (all || CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //ReportingSystemList
    if (all || CanRead(2))
    {
        attributes.push_back(2);
    }
}

int CGXDLMSSFSKReportingSystemList::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSSFSKReportingSystemList::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = DLMS_ERROR_CODE_OK;
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
        CGXByteBuffer data;
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        // Add count
        GXHelpers::SetObjectCount((unsigned long)m_ReportingSystemList.size(), data);
        for (std::vector<CGXByteBuffer>::iterator it = m_ReportingSystemList.begin(); it != m_ReportingSystemList.end(); ++it)
        {
            if ((ret = GXHelpers::SetData2(&settings, data, DLMS_DATA_TYPE_OCTET_STRING, *it)) != 0)
            {
                break;
            }
        }
        e.SetValue(data);
    }
    else
    {
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}

// Set value of given attribute.
int CGXDLMSSFSKReportingSystemList::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = 0;
    if (e.GetIndex() == 1)
    {
        ret = SetLogicalName(this, e.GetValue());
    }
    else if (e.GetIndex() == 2)
    {
        m_ReportingSystemList.clear();
        if (e.GetValue().vt == DLMS_DATA_TYPE_ARRAY)
        {
            CGXByteBuffer bb;
            for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            {
                if ((ret = it->GetBytes(bb)) != 0)
                {
                    break;
                }
                m_ReportingSystemList.push_back(bb);
            }
        }
    }
    else
    {
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}

#endif //DLMS_IGNORE_SFSK_REPORTING_SYSTEM_LIST