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

#ifndef GXDLMSSFSKMACSYNCHRONIZATIONTIMEOUTS_H
#define GXDLMSSFSKMACSYNCHRONIZATIONTIMEOUTS_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_SFSK_MAC_SYNCHRONIZATION_TIMEOUTS
#include "GXDLMSObject.h"

/**
Online help:
http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSSFSKMacSynchronizationTimeouts
*/
class CGXDLMSSFSKMacSynchronizationTimeouts : public CGXDLMSObject
{
    /**
    * Search initiator timeout.
    */
    uint32_t m_SearchInitiatorTimeout;
    /**
     * Synchronization confirmation timeout.
     */
    uint32_t m_SynchronizationConfirmationTimeout;
    /**
     * Time out not addressed.
     */
    uint32_t m_TimeOutNotAddressed;
    /**
     * Time out frame not OK.
     */
    uint32_t m_TimeOutFrameNotOK;

public:
    //Constructor.
    CGXDLMSSFSKMacSynchronizationTimeouts();

    //SN Constructor.
    CGXDLMSSFSKMacSynchronizationTimeouts(std::string ln, unsigned short sn);

    //LN Constructor.
    CGXDLMSSFSKMacSynchronizationTimeouts(std::string ln);

    int GetSearchInitiatorTimeout();
    void SetSearchInitiatorTimeout(uint32_t value);

    uint32_t GetSynchronizationConfirmationTimeout();
    void SetSynchronizationConfirmationTimeout(uint32_t value);

    uint32_t GetTimeOutNotAddressed();
    void SetTimeOutNotAddressed(uint32_t value);

    uint32_t GetTimeOutFrameNotOK();
    void SetTimeOutFrameNotOK(uint32_t value);

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
#endif //DLMS_IGNORE_SFSK_MAC_SYNCHRONIZATION_TIMEOUTS
#endif //GXDLMSSFSKMACSYNCHRONIZATIONTIMEOUTS_H