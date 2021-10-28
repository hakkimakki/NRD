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

#ifndef GXDLMSIECTWISTEDPAIRSETUP_H
#define GXDLMSIECTWISTEDPAIRSETUP_H

#include "GXIgnore.h"
#include "GXDLMSObject.h"
#ifndef DLMS_IGNORE_IEC_TWISTED_PAIR_SETUP

/**
Online help:
http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSIecTwistedPairSetup
*/
class CGXDLMSIecTwistedPairSetup : public CGXDLMSObject
{
    /*
    * Working mode.
    */
    DLMS_IEC_TWISTED_PAIR_SETUP_MODE m_Mode;

    /*
     * Communication speed.
     */
    DLMS_BAUD_RATE m_Speed;

    /*
     * List of Primary Station Addresses.
     */
    std::vector<unsigned char> m_PrimaryAddresses;

    /*
     * List of the TAB(i) for which the real equipment has been programmed in
     * the case of forgotten station call.
     */
    std::vector<char> m_Tabis;

public:
    //Constructor.
    CGXDLMSIecTwistedPairSetup();

    //SN Constructor.
    CGXDLMSIecTwistedPairSetup(std::string ln, unsigned short sn);

    //LN Constructor.
    CGXDLMSIecTwistedPairSetup(std::string ln);

    /**
    * Working mode.
    */
    DLMS_IEC_TWISTED_PAIR_SETUP_MODE GetMode();
    void SetMode(DLMS_IEC_TWISTED_PAIR_SETUP_MODE value);

    /**
     * Communication speed.
     */
    DLMS_BAUD_RATE GetSpeed();
    void SetSpeed(DLMS_BAUD_RATE value);

    /*
     * list of Primary Station Addresses.
     */
    std::vector<unsigned char>& GetPrimaryAddresses();

    /*
     * list of the TABis.
     */
    std::vector<char>& GetTabis();

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
#endif //DLMS_IGNORE_IEC_TWISTED_PAIR_SETUP
#endif //GXDLMSIECTWISTEDPAIRSETUP_H