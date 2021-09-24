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

#include "../include/GXDLMSArbitrator.h"
#ifndef DLMS_IGNORE_ARBITRATOR
//Constructor.
CGXDLMSArbitrator::CGXDLMSArbitrator() :
    CGXDLMSArbitrator("", 0)
{
}

//SN Constructor.
CGXDLMSArbitrator::CGXDLMSArbitrator(std::string ln, unsigned short sn) :
    CGXDLMSObject(DLMS_OBJECT_TYPE_ARBITRATOR, ln, sn)
{

}

//LN Constructor.
CGXDLMSArbitrator::CGXDLMSArbitrator(std::string ln) :
    CGXDLMSArbitrator(ln, 0)
{

}

// Returns amount of attributes.
int CGXDLMSArbitrator::GetAttributeCount()
{
    return 6;
}

// Returns amount of methods.
int CGXDLMSArbitrator::GetMethodCount()
{
    return 2;
}

void CGXDLMSArbitrator::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    std::stringstream sb;
    sb << "{";
    bool empty = true;
    for (std::vector<CGXDLMSActionItem>::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it)
    {
        if (empty)
        {
            empty = false;
        }
        else
        {
            sb << ", ";
        }
        sb << "[";
        sb << it->GetLogicalName();
        sb << ", ";
        sb << it->GetScriptSelector();
        sb << "]";
    }
    sb << "}";
    values.push_back(sb.str());
    sb.clear();
    sb << "{";
    empty = true;
    for (std::vector<std::string>::iterator it = m_PermissionsTable.begin(); it != m_PermissionsTable.end(); ++it)
    {
        if (empty)
        {
            empty = false;
        }
        else
        {
            sb << ", ";
        }
        sb << *it;
    }
    sb << "}";
    values.push_back(sb.str());
    sb.clear();
    sb << "{";
    empty = true;
    for (std::vector<std::vector<uint16_t>>::iterator it = m_WeightingsTable.begin(); it != m_WeightingsTable.end(); ++it)
    {
        if (empty)
        {
            empty = false;
        }
        else
        {
            sb << ", ";
        }
        empty = true;
        for (std::vector<uint16_t>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
        {
            if (empty)
            {
                empty = false;
            }
            else
            {
                sb << ", ";
            }
            sb << *it2;
        }
    }
    sb << "}";
    values.push_back(sb.str());
    sb.clear();
    sb << "{";
    empty = true;
    for (std::vector<std::string>::iterator it = m_MostRecentRequestsTable.begin(); it != m_MostRecentRequestsTable.end(); ++it)
    {
        if (empty)
        {
            empty = false;
        }
        else
        {
            sb << ", ";
        }
    }
    sb << "}";
    values.push_back(sb.str());
    sb.clear();
    values.push_back(GXHelpers::IntToString(m_LastOutcome));
}

void CGXDLMSArbitrator::GetAttributeIndexToRead(bool all, std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (all || CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //Actions
    if (all || CanRead(2))
    {
        attributes.push_back(2);
    }
    //Permissions table
    if (all || CanRead(3))
    {
        attributes.push_back(3);
    }
    //Weightings table
    if (all || CanRead(4))
    {
        attributes.push_back(4);
    }
    //Most recent requests table
    if (all || CanRead(5))
    {
        attributes.push_back(5);
    }
    //Last outcome
    if (all || CanRead(6))
    {
        attributes.push_back(6);
    }
}

int CGXDLMSArbitrator::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    switch (index)
    {
    case 1:
        type = DLMS_DATA_TYPE_OCTET_STRING;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        type = DLMS_DATA_TYPE_ARRAY;
        break;
    case 6:
        type = DLMS_DATA_TYPE_UINT8;
        break;
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return 0;
}

// Returns value of given attribute.
int CGXDLMSArbitrator::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = 0;
    CGXByteBuffer data;
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
    {
        unsigned char ln[6];
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        GXHelpers::SetObjectCount((unsigned long)m_Actions.size(), data);
        for (std::vector<CGXDLMSActionItem>::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it)
        {
            CGXDLMSVariant tmp(ln, 6, DLMS_DATA_TYPE_OCTET_STRING);
            if ((ret = data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE)) != 0 ||
                //Count
                (ret = data.SetUInt8(2)) != 0 ||
                (ret = GXHelpers::SetLogicalName(it->GetLogicalName().c_str(), ln)) != 0 ||
                (ret = GXHelpers::SetData(&settings, data, DLMS_DATA_TYPE_OCTET_STRING, tmp)) != 0 ||
                (ret = GXHelpers::SetData2(&settings, data, DLMS_DATA_TYPE_UINT16, it->GetScriptSelector())) != 0)
            {
                break;
            }
        }
        e.SetValue(data);
    }
    break;
    case 3:
    {
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        GXHelpers::SetObjectCount((unsigned long)m_PermissionsTable.size(), data);
        for (std::vector<std::string>::iterator it = m_PermissionsTable.begin(); it != m_PermissionsTable.end(); ++it)
        {
            if ((ret = GXHelpers::SetData2(&settings, data, DLMS_DATA_TYPE_BIT_STRING, *it)) != 0)
            {
                break;
            }
        }
        e.SetValue(data);
    }
    break;
    case 4:
    {
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        GXHelpers::SetObjectCount((unsigned long)m_WeightingsTable.size(), data);
        for (std::vector<std::vector<uint16_t>>::iterator it = m_WeightingsTable.begin(); it != m_WeightingsTable.end(); ++it)
        {
            data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
            GXHelpers::SetObjectCount((unsigned long)it->size(), data);
            for (std::vector<uint16_t>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
            {
                if ((ret = GXHelpers::SetData2(&settings, data, DLMS_DATA_TYPE_UINT16, *it2)) != 0)
                {
                    break;
                }
            }
        }
        e.SetValue(data);
    }
    break;
    case 5:
    {
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        GXHelpers::SetObjectCount((unsigned long)m_MostRecentRequestsTable.size(), data);
        for (std::vector<std::string>::iterator it = m_MostRecentRequestsTable.begin(); it != m_MostRecentRequestsTable.end(); ++it)
        {
            if ((ret = GXHelpers::SetData2(&settings, data, DLMS_DATA_TYPE_BIT_STRING, *it)) != 0)
            {
                break;
            }
        }
        e.SetValue(data);
    }
    break;
    case 6:
        e.SetValue(m_LastOutcome);
        break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    }
    return ret;

}

/// Create a new action.
int CreateAction(std::vector<CGXDLMSVariant>& it, CGXDLMSActionItem& item)
{
    std::string ln;
    GXHelpers::GetLogicalName(it[0].byteArr, ln);
    item.SetLogicalName(ln);
    item.SetScriptSelector(it[1].ToInteger());
    return 0;
}

// Set value of given attribute.
int CGXDLMSArbitrator::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret = 0;
    switch (e.GetIndex())
    {
    case 1:
        ret = SetLogicalName(this, e.GetValue());
        break;
    case 2:
    {
        m_Actions.clear();
        for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
        {
            CGXDLMSActionItem item;
            if ((ret = CreateAction(it->Arr, item)) != 0)
            {
                break;
            }
            m_Actions.push_back(item);
        }
    }
    break;
    case 3:
    {
        m_PermissionsTable.clear();
        for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
        {
            m_PermissionsTable.push_back(it->ToString());
        }
    }
    break;
    case 4:
    {
        m_WeightingsTable.clear();
        for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
        {
            std::vector<uint16_t> list;
            for (std::vector<CGXDLMSVariant>::iterator it2 = it->Arr.begin(); it2 != it->Arr.end(); ++it2)
            {
                list.push_back(it2->ToInteger());
            }
            m_WeightingsTable.push_back(list);
        }
    }
    break;
    case 5:
    {
        m_MostRecentRequestsTable.clear();
        for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
        {
            m_MostRecentRequestsTable.push_back(it->ToString());
        }
    }
    break;
    case 6:
        m_LastOutcome = e.GetValue().ToInteger();
        break;
    default:
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    }
    return ret;
}

#endif //DLMS_IGNORE_ARBITRATOR