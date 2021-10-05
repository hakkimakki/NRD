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

#ifndef GXDLMSIEC8802LLCTYPE2SETUP_H
#define GXDLMSIEC8802LLCTYPE2SETUP_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_IEC_8802_LLC_TYPE2_SETUP
#include "GXDLMSObject.h"

/**
Online help:
http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSIec8802LlcType2Setup
*/
class CGXDLMSIec8802LlcType2Setup : public CGXDLMSObject
{
    /**
     * Transmit Window Size K.
     */
    unsigned char m_TransmitWindowSizeK;
    /**
     * Transmit Window Size RW.
     */
    unsigned char m_TransmitWindowSizeRW;
    /**
     * Maximum octets in I Pdu N1.
     */
    uint16_t m_MaximumOctetsPdu;
    /**
     * Maximum number of transmissions, N2.
     */
    unsigned char m_MaximumNumberTransmissions;
    /**
     * Acknowledgement timer in seconds.
     */
    uint16_t m_AcknowledgementTimer;
    /**
     * P-bit timer in seconds.
     */
    uint16_t m_BitTimer;
    /**
     * Reject timer.
     */
    uint16_t m_RejectTimer;
    /**
     * Busy state timer.
     */
    uint16_t m_BusyStateTimer;
public:
    //Constructor.
    CGXDLMSIec8802LlcType2Setup();

    //SN Constructor.
    CGXDLMSIec8802LlcType2Setup(std::string ln, unsigned short sn);

    //LN Constructor.
    CGXDLMSIec8802LlcType2Setup(std::string ln);

    /**
    * Transmit Window Size K.
    */
    unsigned char GetTransmitWindowSizeK();
    void SetTransmitWindowSizeK(unsigned char value);

    /**
     * Transmit Window Size RW.
     */
    unsigned char GetTransmitWindowSizeRW();
    void SetTransmitWindowSizeRW(unsigned char value);

    /**
     * Maximum octets in I Pdu N1.
     */
    uint16_t GetMaximumOctetsPdu();
    void SetMaximumOctetsPdu(uint16_t value);

    /**
     * Maximum number of transmissions, N2.
     */
    unsigned char GetMaximumNumberTransmissions();
    void SetMaximumNumberTransmissions(unsigned char value);

    /**
     * Acknowledgement timer in seconds.
     */
    uint16_t GetAcknowledgementTimer();
    void SetAcknowledgementTimer(uint16_t value);

    /**
     * P-bit timer in seconds.
     */
    uint16_t GetBitTimer();
    void SetBitTimer(uint16_t value);

    /**
     * Reject timer.
     */
    uint16_t GetRejectTimer();
    void SetRejectTimer(uint16_t value);

    /**
     * Busy state timer.
     */
    uint16_t GetBusyStateTimer();
    void SetBusyStateTimer(uint16_t value);

    // Returns amount of attributes.
    int GetAttributeCount();

    // Returns amount of methods.
    int GetMethodCount();

    //Get attribute values of object.
    void GetValues(std::vector<std::string>& values);

    /////////////////////////////////////////////////////////////////////////
    // Returns collection of attributes to read.
    //
    // If attribute is static and already read or device is returned
    // HW error it is not returned.
    //
    // all: All items are returned even if they are read already.
    // attributes: Collection of attributes to read.
    void GetAttributeIndexToRead(bool all, std::vector<int>& attributes);

    int GetDataType(int index, DLMS_DATA_TYPE& type);

    // Returns value of given attribute.
    int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    // Set value of given attribute.
    int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);
};
#endif //DLMS_IGNORE_IEC_8802_LLC_TYPE2_SETUP
#endif //GXDLMSIEC8802LLCTYPE2SETUP_H