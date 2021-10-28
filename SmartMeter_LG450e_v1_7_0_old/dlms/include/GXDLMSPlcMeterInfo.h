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
// and/or modify it under the terms of the GNU General License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXDLMSPLCMETERINFO_H
#define GXDLMSPLCMETERINFO_H

#include "enums.h"
#include "GXBytebuffer.h"

//Information from the discovered PLC meter(s).
class CGXDLMSPlcMeterInfo
{
private:
    /**
     * Source Address.
     */
    uint16_t m_SourceAddress;

    /**
     * Destination Address.
     */
    uint16_t m_DestinationAddress;
    /**
     * System title.
     */
    CGXByteBuffer m_SystemTitle;
    /**
     * Alarm descriptor.
     */
    short m_AlarmDescriptor;

public:

    uint16_t GetSourceAddress()
    {
        return m_SourceAddress;
    }

    void SetSourceAddress(uint16_t value)
    {
        m_SourceAddress = value;
    }

    /**
     * Destination Address.
     */
    uint16_t GetDestinationAddress()
    {
        return m_DestinationAddress;
    }

    void SetDestinationAddress(uint16_t value)
    {
        m_DestinationAddress = value;
    }

    /**
     * System title.
     */
    CGXByteBuffer& GetSystemTitle()
    {
        return m_SystemTitle;
    }

    void SetSystemTitle(CGXByteBuffer& value)
    {
        m_SystemTitle = value;
    }

    /**
     * Alarm descriptor.
     */
    short GetAlarmDescriptor()
    {
        return m_AlarmDescriptor;
    }

    void SetAlarmDescriptor(short value)
    {
        m_AlarmDescriptor = value;
    }
};

#endif //GXDLMSPLCMETERINFO_H
