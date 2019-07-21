// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#ifndef NIDEFAULTSHADOWVISITOR_H
#define NIDEFAULTSHADOWVISITOR_H

#include "NiShadowVisitor.h"

class NIMAIN_ENTRY NiDefaultShadowVisitor : public NiShadowVisitor
{
    NiDeclareRTTI;

    // Empty Destructor
    virtual ~NiDefaultShadowVisitor();

    // Default callback for specifying the NiShadowVisitor to use. This
    // default callback creates the NiDefaultShadowVisitor.
    static NiShadowVisitor* CreateDefaultShadowVisitor();

protected:
    virtual bool ShouldProcessNodeChildren(NiNode* pkNode);
};

#endif // NIDEFAULTSHADOWVISITOR_H