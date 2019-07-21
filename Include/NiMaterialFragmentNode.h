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
#ifndef NIMATERIALFRAGMENTNODE_H
#define NIMATERIALFRAGMENTNODE_H

#include "NiMaterialNode.h"
#include "NiCodeBlock.h"
#include "NiTPtrSet.h"

class NIMAIN_ENTRY NiMaterialFragmentNode : public NiMaterialNode
{
    NiDeclareRTTI;
public:
    inline virtual ~NiMaterialFragmentNode(){};

    unsigned int GetCodeBlockCount();
    NiCodeBlock* GetCodeBlock(unsigned int uiCode);
    NiCodeBlock* GetCodeBlock(const NiFixedString& kLanguage,
        const NiFixedString& kPlatform,
        const NiTObjectPtrSet<NiFixedString>* pkValidTargets);
    void AddCodeBlock(NiCodeBlock* pkBlock);

    const NiString& GetDescription();
    void SetDescription(const NiString& kBlock);

    virtual NiMaterialNode* Clone();

protected:
    virtual void CopyMembers(NiMaterialNode* pkOther);
    NiTObjectArray<NiCodeBlockPtr> m_kCodeBlocks;
    NiString m_kDescription;
};

typedef efd::SmartPointer<NiMaterialFragmentNode> NiMaterialFragmentNodePtr;

#endif  //#ifndef NIMATERIALFRAGMENT_H
