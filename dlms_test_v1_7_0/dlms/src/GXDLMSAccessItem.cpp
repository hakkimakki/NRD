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

#include "../include/GXDLMSAccessItem.h"

CGXDLMSObject* CGXDLMSAccessItem::GetTarget()
{
    return m_Target;
}

void CGXDLMSAccessItem::SetTarget(CGXDLMSObject* value)
{
    m_Target = value;
}

DLMS_ACCESS_SERVICE_COMMAND_TYPE CGXDLMSAccessItem::GetCommand()
{
    return m_Command;
}

void CGXDLMSAccessItem::SetCommand(DLMS_ACCESS_SERVICE_COMMAND_TYPE value)
{
    m_Command = value;
}

unsigned char CGXDLMSAccessItem::GetIndex()
{
    return m_Index;
}

/**
 * value: Attribute index.
 */
void CGXDLMSAccessItem::SetIndex(unsigned char value)
{
    m_Index = value;
}

void CGXDLMSAccessItem::SetError(DLMS_ERROR_CODE value)
{
    m_Error = value;
}

DLMS_ERROR_CODE CGXDLMSAccessItem::GetError()
{
    return m_Error;
}

void CGXDLMSAccessItem::SetValue(CGXDLMSVariant& value)
{
    m_Value = value;
}

CGXDLMSVariant& CGXDLMSAccessItem::GetValue()
{
    return m_Value;
}

CGXDLMSAccessItem::CGXDLMSAccessItem()
{
    m_Error = DLMS_ERROR_CODE_OK;
}

CGXDLMSAccessItem::CGXDLMSAccessItem(DLMS_ACCESS_SERVICE_COMMAND_TYPE command,
    CGXDLMSObject* target,
    unsigned char attributeIndex)
{
    m_Error = DLMS_ERROR_CODE_OK;
    m_Command = command;
    m_Target = target;
    m_Index = attributeIndex;
}