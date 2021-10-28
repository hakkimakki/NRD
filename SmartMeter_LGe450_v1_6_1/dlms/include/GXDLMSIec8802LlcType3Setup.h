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

#ifndef GXDLMSIEC8802LLCTYPE3SETUP_H
#define GXDLMSIEC8802LLCTYPE3SETUP_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_IEC_8802_LLC_TYPE3_SETUP
#include "GXDLMSObject.h"

/**
Online help:
http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSIec8802LlcType3Setup
*/
class CGXDLMSIec8802LlcType3Setup : public CGXDLMSObject
{
    /**
    * Maximum number of octets in an ACn command PDU, N3.
    */
    uint16_t m_MaximumOctetsACnPdu;
    /**
    * Maximum number of times in transmissions N4.
    */
    unsigned char m_MaximumTransmissions;
    /**
    * Acknowledgement time, T1.
    */
    uint16_t m_AcknowledgementTime;
    /**
    * Receive lifetime variable, T2.
    */
    uint16_t m_ReceiveLifetime;
    /**
    * Transmit lifetime variable, T3.
    */
    uint16_t m_TransmitLifetime;
public:
    //Constructor.
    CGXDLMSIec8802LlcType3Setup();

    //SN Constructor.
    CGXDLMSIec8802LlcType3Setup(std::string ln, unsigned short sn);

    //LN Constructor.
    CGXDLMSIec8802LlcType3Setup(std::string ln);

    /**
    * Maximum number of octets in an ACn command PDU, N3.
    */
    uint16_t GetMaximumOctetsACnPdu();
    void SetMaximumOctetsACnPdu(uint16_t value);

    /**
     * Maximum number of times in transmissions N4.
     */
    unsigned char GetMaximumTransmissions();
    void SetMaximumTransmissions(unsigned char value);

    /**
     * Acknowledgement time, T1.
     */
    uint16_t GetAcknowledgementTime();
    void SetAcknowledgementTime(uint16_t value);

    /**
     * Receive lifetime variable, T2.
     */
    uint16_t GetReceiveLifetime();
    void SetReceiveLifetime(uint16_t value);

    /**
     * Transmit lifetime variable, T3.
     */
    uint16_t GetTransmitLifetime();
    void SetTransmitLifetime(uint16_t value);

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
#endif //DLMS_IGNORE_IEC_8802_LLC_TYPE3_SETUP
#endif //GXDLMSIEC8802LLCTYPE3SETUP_H