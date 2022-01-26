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

#ifndef GXDLMSSFSKMACCOUNTERS_H
#define GXDLMSSFSKMACCOUNTERS_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_SFSK_MAC_COUNTERS
#include "GXDLMSObject.h"

/**
Online help:
http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSSFSKMacCounters
*/
class CGXDLMSSFSKMacCounters : public CGXDLMSObject
{
    /**
     * List of synchronization registers.
     */
    std::vector< std::pair<uint16_t, uint32_t> > m_SynchronizationRegister;

    uint32_t m_PhysicalLayerDesynchronization;
    uint32_t m_TimeOutNotAddressedDesynchronization;

    uint32_t m_TimeOutFrameNotOkDesynchronization;

    uint32_t m_WriteRequestDesynchronization;
    uint32_t m_WrongInitiatorDesynchronization;
    /**
     * List of broadcast frames counter.
     */
    std::vector< std::pair<uint16_t, uint32_t> > m_BroadcastFramesCounter;
    /**
     * Repetitions counter.
     */
    uint32_t m_RepetitionsCounter;
    /**
     * Transmissions counter.
     */
    uint32_t m_TransmissionsCounter;

    /**
     * CRC OK frames counter.
     */
    uint32_t m_CrcOkFramesCounter;
    /**
     * CRC NOK frames counter.
     */
    uint32_t m_CrcNOkFramesCounter;
public:
    //Constructor.
    CGXDLMSSFSKMacCounters();

    //SN Constructor.
    CGXDLMSSFSKMacCounters(std::string ln, unsigned short sn);

    //LN Constructor.
    CGXDLMSSFSKMacCounters(std::string ln);

    /**
    * List of synchronization registers.
    */
    std::vector< std::pair<uint16_t, uint32_t> >& GetSynchronizationRegister();

    long GetPhysicalLayerDesynchronization();
    void SetPhysicalLayerDesynchronization(uint32_t value);

    long GetTimeOutNotAddressedDesynchronization();
    void SetTimeOutNotAddressedDesynchronization(uint32_t value);

    long GetTimeOutFrameNotOkDesynchronization();
    void SetTimeOutFrameNotOkDesynchronization(long value);

    long GetWriteRequestDesynchronization();
    void SetWriteRequestDesynchronization(uint32_t value);

    long GetWrongInitiatorDesynchronization();
    void SetWrongInitiatorDesynchronization(uint32_t value);

    /*
     * List of broadcast frames counter.
     */
    std::vector< std::pair<uint16_t, uint32_t> >& GetBroadcastFramesCounter();

    /*
     * Repetitions counter.
     */
    uint32_t GetRepetitionsCounter();
    void SetRepetitionsCounter(uint32_t value);

    /**
     * Transmissions counter.
     */
    uint32_t GetTransmissionsCounter();
    void SetTransmissionsCounter(uint32_t value);

    /*
    * CRC OK frames counter.
    */
    uint32_t GetCrcOkFramesCounter();
    void SetCrcOkFramesCounter(uint32_t value);

    /**
     * @return CRC NOK frames counter.
     */
    uint32_t GetCrcNOkFramesCounter();
    void SetCrcNOkFramesCounter(uint32_t value);

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
#endif //DLMS_IGNORE_SFSK_MAC_COUNTERS
#endif //GXDLMSSFSKMACCOUNTERS_H