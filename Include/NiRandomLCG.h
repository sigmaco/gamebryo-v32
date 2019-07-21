// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2007 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef NIRANDOMLCG_H
#define NIRANDOMLCG_H

#define NIRANDOMLCG_MAX 0x7fff

#include <NiRefObject.h>
#include <NiSmartPointer.h>

#include "NiMainLibType.h"

/**
    A simple LCG pseudo-random implementation that stores its own private seed.
    This allows an application to have multiple random number dependent tasks
    that do not disrupt each other

    @note this is implementation will return identical pseudo-random number 
		results across all platforms.
 */
class NIMAIN_ENTRY NiRandomLCG : public NiRefObject
{
public:

    /**
        Parameterized constructor

        @param uiSeed Initial random seed
    */
    inline NiRandomLCG(NiUInt32 uiSeed);
    inline ~NiRandomLCG();

    /**
        Sets the seed to base future number generations from
    */
    inline void SetSeed(NiUInt32 uiSeed);
    
    /**
        Return a pseudo-random number between 0 and 32767
    */
    inline NiUInt32 GetNextReal();
    
    /**
        Return a pseudo-random number between 0.0f and 1.0f inclusive
    */
    inline float GetNextUnit();

    /**
        Return a pseudo-random number between -1.0f and 1.0f inclusive
    */
    inline float GetNextSymmetricUnit();

private:
    NiUInt32 m_uiSeed;
};

NiSmartPointer(NiRandomLCG);

#include "NiRandomLCG.inl"

#endif // NIRANDOMLCG_H