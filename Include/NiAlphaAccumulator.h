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
#ifndef NIALPHAACCUMULATOR_H
#define NIALPHAACCUMULATOR_H

#include "NiBackToFrontAccumulator.h"

class NIMAIN_ENTRY NiAlphaAccumulator : public NiBackToFrontAccumulator
{
    NiDeclareRTTI;
    NiDeclareClone(NiAlphaAccumulator);
    NiDeclareStream;

public:
    // creation and destruction
    NiAlphaAccumulator ();
    virtual ~NiAlphaAccumulator ();

    // Observe the "no sort" NiAlphaProperty hint flags?
    inline void SetObserveNoSortHint(bool bObserve);
    inline bool GetObserveNoSortHint() const;

    inline void SetSortByClosestPoint(bool bClosest);
    inline bool GetSortByClosestPoint() const;

    // *** begin Emergent internal use only ***

    virtual void RegisterObjectArray (NiVisibleArray& kArray);

    // *** end Emergent internal use only ***

protected:
    virtual void Sort ();

    bool m_bObserveNoSortHint;
    bool m_bSortByClosestPoint;

};

typedef efd::SmartPointer<NiAlphaAccumulator> NiAlphaAccumulatorPtr;

//------------------------------------------------------------------------------------------------
//  Inline include
#include "NiAlphaAccumulator.inl"

//------------------------------------------------------------------------------------------------

#endif

