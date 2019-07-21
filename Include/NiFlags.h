// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef NIFLAGS_H
#define NIFLAGS_H

#define NiDeclareFlags(type) \
    private: \
        type m_uFlags; \
        void SetField(type uVal, type uMask, type uPos) \
        { \
            m_uFlags = (m_uFlags & ~uMask) | (uVal << uPos); \
        } \
        type GetField(type uMask, type uPos) const \
        { \
            return (m_uFlags & uMask) >> uPos; \
        } \
        void SetBit(bool bVal, type uMask) \
        { \
            if (bVal) \
            { \
                m_uFlags |= uMask; \
            } \
            else \
            { \
                m_uFlags &= ~uMask; \
            } \
        }\
        bool GetBit(type uMask) const \
        { \
            return (m_uFlags & uMask) != 0; \
        }

#endif // NIFLAGS_H
