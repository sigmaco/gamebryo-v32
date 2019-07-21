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
#ifndef NIMATERIALRESOURCEPRODUCERNODE_H
#define NIMATERIALRESOURCEPRODUCERNODE_H

#include "NiMaterialNode.h"

class NIMAIN_ENTRY NiMaterialResourceProducerNode : public NiMaterialNode
{
    NiDeclareRTTI;
public:
    NiMaterialResourceProducerNode(const NiFixedString& kName,
        const NiFixedString& kProducerType);
    const NiFixedString& GetProducerType();
protected:
    NiFixedString m_kProducerType;
};

typedef efd::SmartPointer<NiMaterialResourceProducerNode>
    NiMaterialResourceProducerNodePtr;

#endif  //#ifndef NIMATERIALRESOURCEPRODUCERNODE_H
