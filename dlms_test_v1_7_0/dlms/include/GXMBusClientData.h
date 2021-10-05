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

#ifndef GXMBUSCLIENTDATA_H
#define GXMBUSCLIENTDATA_H

#include "GXBytebuffer.h"
#include "GXDLMSVariant.h"

/**
*  M-Bus data definition element.
*/
class CGXMBusClientData
{
    /**
      * Data information block.
      */
    CGXByteBuffer m_DataInformation;
    /**
     * Value information block.
     */
    CGXByteBuffer m_ValueInformation;

    /**
     * Data.
     */
    CGXDLMSVariant m_Data;
public:
    /**
     * Returns Data information block.
     */
    CGXByteBuffer& GetDataInformation()
    {
        return m_DataInformation;
    }

    /**
     * @param value
     *            Data information block.
     */
    void SetDataInformation(CGXByteBuffer& value)
    {
        m_DataInformation = value;
    }

    /**
     * Returns Value information block.
     */
    CGXByteBuffer& GetValueInformation()
    {
        return m_ValueInformation;
    }

    /**
     * @param value
     *            Value information block.
     */
    void SetValueInformation(CGXByteBuffer& value)
    {
        m_ValueInformation = value;
    }

    /**
     * Returns Data.
     */
    CGXDLMSVariant& GetData()
    {
        return m_Data;
    }

    /**
     * @param value
     *            Data.
     */
    void SetData(CGXDLMSVariant& value)
    {
        m_Data = value;
    }
};
#endif //GXMBUSCLIENTDATA_H