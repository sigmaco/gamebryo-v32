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
#ifndef NIMATERIALRESOURCEBINDING_H
#define NIMATERIALRESOURCEBINDING_H

#include "NiMaterialNode.h"

class NIMAIN_ENTRY NiMaterialResourceBinding : public NiRefObject
{
public:
    NiMaterialResourceBinding(NiMaterialResource* pkSrc,
        NiMaterialNode* pkSrcFrag, NiMaterialResource* pkDest,
        NiMaterialNode* pkDestFrag);

    NiMaterialResource* GetSourceResource();
    NiMaterialResource* GetDestinationResource();

    NiMaterialNode* GetSourceNode();
    NiMaterialNode* GetDestinationNode();

    const NiFixedString& GetVariable();
    void SetVariable(const NiFixedString& kVar);
protected:
    NiMaterialResourcePtr m_spSrcResource;
    NiMaterialResourcePtr m_spDestResource;
    NiMaterialNodePtr m_spSrcNode;
    NiMaterialNodePtr m_spDestNode;
    NiFixedString m_kVariable;
};

typedef efd::SmartPointer<NiMaterialResourceBinding> NiMaterialResourceBindingPtr;

#endif  //#ifndef NIMATERIALRESOURCEBINDING_H
