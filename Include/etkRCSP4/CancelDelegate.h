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
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#pragma once
#ifndef EE_CANCELDELEGATE_H
#define EE_CANCELDELEGATE_H

namespace etk
{
    class RCSP4;

    class CancelDelegate : public KeepAlive
    {
    public:
        CancelDelegate();
        virtual ~CancelDelegate();

        virtual int	IsAlive();
        inline void SetRCS(RCSP4* pRCSP4);
    protected:
        RCSP4* m_pRCSP4;
    };
} // namespace etk

#include "CancelDelegate.inl"

#endif // EE_CANCELDELEGATE_H