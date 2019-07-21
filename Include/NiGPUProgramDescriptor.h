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
#ifndef NIGPUPROGRAMDESCRIPTOR_H
#define NIGPUPROGRAMDESCRIPTOR_H

#include "NiFixedString.h"

class NIMAIN_ENTRY NiGPUProgramDescriptor : public NiMemObject
{
public:
    NiGPUProgramDescriptor();
    NiGPUProgramDescriptor(unsigned int uiByteCount);
    NiGPUProgramDescriptor(const NiGPUProgramDescriptor&);

    virtual ~NiGPUProgramDescriptor();

    bool GenerateKey(char* pcValue, unsigned int uiMaxSize) const;
    bool IsEqual(const NiGPUProgramDescriptor* pkOther) const;

    NiGPUProgramDescriptor& operator=(
        const NiGPUProgramDescriptor& kDescriptor);

    NiFixedString m_kIdentifier;

    unsigned int m_uiIntCount;
    unsigned int* m_pkBitArray;
};
#endif  //#ifndef NIGPUPROGRAMDESCRIPTOR_H
