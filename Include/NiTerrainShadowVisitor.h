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

#ifndef NITERRAINSHADOWVISITOR_H
#define NITERRAINSHADOWVISITOR_H

#include "NiShadowVisitor.h"

///@cond EMERGENT_INTERNAL

/**
    An internal class used to control the rendering of terrain shadows. It disables the processing
    of all of terrain's nodes (without this all levels of detail stored in the terrain would be
    processed).
*/
class NITERRAIN_ENTRY NiTerrainShadowVisitor : public NiShadowVisitor
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

    // Empty Destructor
    virtual ~NiTerrainShadowVisitor();

    /**
        Creates a Terrain Shadow Visitor.
    */
    static NiShadowVisitor* CreateTerrainShadowVisitor();

protected:
    virtual bool ShouldProcessNodeChildren(NiNode* pkNode);
};

///@endcond

#endif // NITERRAINSHADOWVISITOR_H