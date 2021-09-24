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

#include "../include/GXHdlcSettings.h"

CGXHdlcSettings::CGXHdlcSettings()
{
    m_MaxInfoTX = DEFAULT_MAX_INFO_TX;
    m_MaxInfoRX = DEFAULT_MAX_INFO_RX;
    m_WindowSizeTX = DEFAULT_WINDOWS_SIZE_TX;
    m_WindowSizeRX = DEFAULT_WINDOWS_SIZE_RX;
}

unsigned short CGXHdlcSettings::GetMaxInfoTX()
{
    return m_MaxInfoTX;
}

void CGXHdlcSettings::SetMaxInfoTX(unsigned short value)
{
    m_MaxInfoTX = value;
}

unsigned short CGXHdlcSettings::GetMaxInfoRX()
{
    return m_MaxInfoRX;
}

void CGXHdlcSettings::SetMaxInfoRX(unsigned short value)
{
    m_MaxInfoRX = value;
}

unsigned char CGXHdlcSettings::GetWindowSizeTX()
{
    return m_WindowSizeRX;
}

void CGXHdlcSettings::SetWindowSizeTX(unsigned char value)
{
    m_WindowSizeRX = value;
}

unsigned char CGXHdlcSettings::GetWindowSizeRX()
{
    return m_WindowSizeTX;
}

void CGXHdlcSettings::SetWindowSizeRX(unsigned char value)
{
    m_WindowSizeTX = value;
}
