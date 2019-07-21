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
#ifndef NIPRIMENUMBER_H
#define NIPRIMENUMBER_H

#include "NiAnimationLibType.h"

class NIANIMATION_ENTRY NiPrimeNumber
{
public:
    static unsigned int GetPrimeArrayCount();
    static unsigned int GetPrimeAt(unsigned int uiIndex);
    static unsigned int GetMaxPrime();
    static bool GetNearbyPrime(unsigned int uiNumber, unsigned int& uiPrime);
};

#endif
