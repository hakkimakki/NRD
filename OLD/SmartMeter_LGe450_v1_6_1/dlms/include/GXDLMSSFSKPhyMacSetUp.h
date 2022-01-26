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

#ifndef CGXDLMSSFSKPHYMACSETUP_H
#define CGXDLMSSFSKPHYMACSETUP_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_SFSK_PHY_MAC_SETUP
#include "GXDLMSObject.h"

/*
Online help:
http://www.gurux.fi/Gurux.DLMS.Objects.CGXDLMSSFSKPhyMacSetUp
*/
class CGXDLMSSFSKPhyMacSetUp : public CGXDLMSObject
{
    /**
     * Initiator electrical phase.
     */
    DLMS_INITIATOR_ELECTRICAL_PHASE m_InitiatorElectricalPhase;

    /**
     * Delta electrical phase.
     */
    DLMS_DELTA_ELECTRICAL_PHASE m_DeltaElectricalPhase;

    /**
     * Corresponds to the maximum allowed gain bound to be used by the server
     * system in the receiving mode. The default unit is dB.
     */
    unsigned char m_MaxReceivingGain;
    /**
     * Corresponds to the maximum attenuation bound to be used by the server
     * system in the transmitting mode.The default unit is dB.
     */
    unsigned char m_MaxTransmittingGain;
    /**
     * Intelligent search initiator process. If the value of the initiator
     * signal is above the value of this attribute, a fast synchronization
     * process is possible.
     */
    unsigned char m_SearchInitiatorThreshold;
    /**
     * Mark frequency required for S-FSK modulation.
     */
    uint32_t m_MarkFrequency;
    /**
     * Space frequency required for S-FSK modulation.
     */
    uint32_t m_SpaceFrequency;
    /**
     * Mac Address.
     */
    uint16_t m_MacAddress;

    /**
     * MAC group addresses.
     */
    std::vector<uint16_t> m_MacGroupAddresses;
    /**
     * Specifies are all frames repeated.
     */
    DLMS_REPEATER m_Repeater;
    /**
     * Repeater status.
     */
    bool m_RepeaterStatus;
    /**
     * Min delta credit.
     */
    unsigned char m_MinDeltaCredit;

    /**
     * Initiator MAC address.
     */
    int m_InitiatorMacAddress;

    /**
     * Synchronization locked/unlocked state.
     */
    bool m_SynchronizationLocked;
    /**
     * Transmission speed supported by the physical device.
     */
    DLMS_BAUD_RATE m_TransmissionSpeed;

public:
    //Constructor.
    CGXDLMSSFSKPhyMacSetUp();

    //SN Constructor.
    CGXDLMSSFSKPhyMacSetUp(std::string ln, unsigned short sn);

    //LN Constructor.
    CGXDLMSSFSKPhyMacSetUp(std::string ln);

    /**
   * Initiator electrical phase.
   */
    DLMS_INITIATOR_ELECTRICAL_PHASE GetInitiatorElectricalPhase();
    void SetInitiatorElectricalPhase(DLMS_INITIATOR_ELECTRICAL_PHASE value);

    /**
     * Delta electrical phase.
     */
    DLMS_DELTA_ELECTRICAL_PHASE GetDeltaElectricalPhase();
    void SetDeltaElectricalPhase(DLMS_DELTA_ELECTRICAL_PHASE value);

    /**
     * Corresponds to the maximum allowed gain bound to be used by the
     *         server system in the receiving mode. The default unit is dB.
     */
    unsigned char GetMaxReceivingGain();
    void SetMaxReceivingGain(unsigned char value);

    /**
     * Corresponds to the maximum attenuation bound to be used by the
     *         server system in the transmitting mode.The default unit is dB.
     */
    unsigned char GetMaxTransmittingGain();
    void SetMaxTransmittingGain(unsigned char value);

    /**
    * Intelligent search initiator process. If the value of the
    *         initiator signal is above the value of this attribute, a fast
    *         synchronization process is possible.
    */
    unsigned char GetSearchInitiatorThreshold();
    void SetSearchInitiatorThreshold(unsigned char value);

    /**
     * Mark frequency required for S-FSK modulation.
     */
    uint32_t GetMarkFrequency();
    void SetMarkFrequency(uint32_t value);

    /**
     * Space frequency required for S-FSK modulation.
     */
    uint32_t GetSpaceFrequency();
    void SetSpaceFrequency(uint32_t value);

    /**
     * Mac Address.
     */
    uint16_t GetMacAddress();
    void SetMacAddress(uint16_t value);

    /**
     * MAC group addresses.
     */
    std::vector<uint16_t>& GetMacGroupAddresses();

    /**
     * Specifies are all frames repeated.
     */
    DLMS_REPEATER GetRepeater();

    /**
     * @param value
     *            Specifies are all frames repeated.
     */
    void SetRepeater(DLMS_REPEATER value);

    /**
     * Repeater status.
     */
    bool GetRepeaterStatus();
    void SetRepeaterStatus(bool value);

    /**
     * Min delta credit.
     */
    unsigned char GetMinDeltaCredit();
    void SetMinDeltaCredit(unsigned char value);

    /**
     * Initiator MAC address.
     */
    uint16_t GetInitiatorMacAddress();
    void SetInitiatorMacAddress(uint16_t value);

    /**
     * Synchronization locked/unlocked state.
     */
    bool GetSynchronizationLocked();
    void SetSynchronizationLocked(bool value);

    /**
     * Transmission speed supported by the physical device.
     */
    DLMS_BAUD_RATE GetTransmissionSpeed();
    void SetTransmissionSpeed(DLMS_BAUD_RATE value);

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
#endif //DLMS_IGNORE_SFSK_PHY_MAC_SETUP
#endif //CGXDLMSSFSKPHYMACSETUP_H