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
#ifndef NIMATERIALDESCRIPTOR_H
#define NIMATERIALDESCRIPTOR_H

#include "NiRefObject.h"
#include "NiSmartPointer.h"
#include "NiFixedString.h"

class NIMAIN_ENTRY NiMaterialDescriptor : public NiRefObject
{
public:
    NiMaterialDescriptor();
    NiMaterialDescriptor(NiMaterialDescriptor* pkMatDescriptor);
    NiMaterialDescriptor(unsigned int uiDWORDCount);
    NiMaterialDescriptor(unsigned int uiDWORDCount, unsigned int* pkBitArray);

    virtual ~NiMaterialDescriptor();

    bool GenerateKey(char* pcValue, unsigned int uiMaxSize);
    bool IsEqual(const NiMaterialDescriptor* pkOther) const;

    void CopyData(const NiMaterialDescriptor* pkOther);

    NiMaterialDescriptor& operator=(const NiMaterialDescriptor& kDescriptor);

    NiFixedString m_kIdentifier;

    unsigned int m_uiDWORDCount;
    unsigned int* m_pkBitArray;
    bool m_bExternalAlloc;
};

typedef efd::SmartPointer<NiMaterialDescriptor> NiMaterialDescriptorPtr;

#endif  //#ifndef NIMATERIALDESCRIPTOR_H
