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
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef NITERRAINCELLNODE_H
#define NITERRAINCELLNODE_H

#include <NiNode.h>
#include "NiTerrainCell.h"


class NITERRAIN_ENTRY NiTerrainCellNode : public NiTerrainCell
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:
    /// Constructor
    NiTerrainCellNode(NiTerrainSector* pkSector, NiUInt32 uiLevel);
    /// Destructor
    virtual ~NiTerrainCellNode();

    /// @{
    /**
        Get/Set the child quadtree node at the specified index. 
        Index 0 = Bottom Left cell
        Index 1 = Bottom Right cell
        Index 2 = Top Right cell
        Index 3 = Top Left cell
    */
    inline const NiTerrainCell* GetChildAt(NiUInt32 uiIndex) const;
    inline NiTerrainCell* GetChildAt(NiUInt32 uiIndex);
    inline void SetChildAt(NiUInt32 uiIndex, NiTerrainCell* pkChild);
    /// @}

    /// @{
    /// Overridden functions to apply to the case where a cell has children
    /// @see NiTerrainCell
    virtual void Update();
    virtual bool ProcessLOD();
    virtual void ProcessBorders();
    virtual void SetTextureRegion(NiPoint2 kOffset, float fScale, 
        NiTerrainCell::TextureType::Value eTexType);
    virtual void SetTexture(NiTexture* pkTexture, 
        NiTerrainCell::TextureType::Value eTexType);
    virtual void UpdateBounds();
    /// @}

protected:

    /// @{
    /// Overridden functions to apply to the case where a cell has children
    /// @see NiTerrainCell
    virtual bool DoAddSurface(NiUInt32 uiSurfaceIndex, 
        NiUInt32 uiNewPriority = 0);
    virtual bool DoRemoveSurface(NiUInt32 uiSurfaceIndex);
    /// @}

    /// The array of quadtree children
    NiTerrainCell* m_apkChildren[4];
};

NiSmartPointer(NiTerrainCellNode);

#include "NiTerrainCellNode.inl"
#endif