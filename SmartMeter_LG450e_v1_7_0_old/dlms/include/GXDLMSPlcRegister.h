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

#ifndef GXDLMSPLCREGISTER_H
#define GXDLMSPLCREGISTER_H

#include "enums.h"

class CGXDLMSPlcRegister
{
private:
    unsigned char m_ResponseProbability;
    uint16_t m_AllowedTimeSlots;
    unsigned char m_DiscoverReportInitialCredit;
    unsigned char m_IcEqualCredit;

public:
    unsigned char GetResponseProbability()
    {
        return m_ResponseProbability;
    }

    void SetResponseProbability(unsigned char value)
    {
        m_ResponseProbability = value;
    }

    uint16_t GetAllowedTimeSlots()
    {
        return m_AllowedTimeSlots;
    }

    void SetAllowedTimeSlots(uint16_t value)
    {
        m_AllowedTimeSlots = value;
    }

    unsigned char GetDiscoverReportInitialCredit()
    {
        return m_DiscoverReportInitialCredit;
    }

    void SetDiscoverReportInitialCredit(unsigned char value)
    {
        m_DiscoverReportInitialCredit = value;
    }

    unsigned char GetICEqualCredit()
    {
        return m_IcEqualCredit;
    }

    void SetICEqualCredit(unsigned char value)
    {
        m_IcEqualCredit = value;
    }
};

#endif //GXDLMSPLCREGISTER_H
