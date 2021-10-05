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

#ifndef CGXDLMSACCESSITEM_H
#define CGXDLMSACCESSITEM_H

#include "GXDLMSObject.h"

/**
Access item is used to generate Access Service message.
*/
class CGXDLMSAccessItem
{
    /**
     * COSEM target object.
     */
    CGXDLMSObject* m_Target;
    /**
     * Executed command type.
     */
    DLMS_ACCESS_SERVICE_COMMAND_TYPE m_Command;

    /**
     * Attribute index.
     */
    unsigned char m_Index;

    //Reply error code.
    DLMS_ERROR_CODE m_Error;

    // Reply value.
    CGXDLMSVariant m_Value;
public:
    /**
     * Returns COSEM target object.
     */
    CGXDLMSObject* GetTarget();

    /**
     * value: COSEM target object.
     */
    void SetTarget(CGXDLMSObject* value);

    /**
     * Returns Executed command type.
     */
    DLMS_ACCESS_SERVICE_COMMAND_TYPE GetCommand();

    /**
     * value: Executed command type.
     */
    void SetCommand(DLMS_ACCESS_SERVICE_COMMAND_TYPE value);

    /**
     * Returns Attribute index.
     */
    unsigned char GetIndex();

    /**
     * value: Attribute index.
     */
    void SetIndex(unsigned char value);

    /**
     * value: Reply error code.
     */
    void SetError(DLMS_ERROR_CODE value);

    /**
     * Returns reply error code.
     */
    DLMS_ERROR_CODE GetError();

    /**
     * value:  Reply value.
     */
    void SetValue(CGXDLMSVariant& value);
    /**
     *  Returns reply value.
     */
    CGXDLMSVariant& GetValue();

    /**
     * Constructor.
     */
    CGXDLMSAccessItem();

    /**
     * Constructor.
     *
     * command: Command to execute.
     * target: COSEM target object.
     * attributeIndex: Attribute index.
     */
    CGXDLMSAccessItem(DLMS_ACCESS_SERVICE_COMMAND_TYPE command,
        CGXDLMSObject* target,
        unsigned char attributeIndex);
};
#endif //CGXDLMSACCESSITEM_H