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

#ifndef NITERRAINCELLLEAF_H
#define NITERRAINCELLLEAF_H

#include "NiTerrainCellNode.h"
#include "NiSurface.h"

class NiTerrainDataSnapshot;

/**
    This class represents a small portion of a terrain sector at it's highest level of detail. 
    This class thus handles the rendering of high detail portions of the terrain and the storage
    of the surface information for that area.
*/
class NITERRAIN_ENTRY NiTerrainCellLeaf : public NiTerrainCell
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:
    enum
    {
        /// The maximum number of surfaces a single leaf can reference
        MAX_NUM_SURFACES = 4
    };

    /// Constructor
    NiTerrainCellLeaf(NiTerrainSector* pkSector, NiUInt32 uiLevel);
    /// Destructor
    virtual ~NiTerrainCellLeaf();

    /**
        Remove all surfaces from this leaf and resets the surface and priority
        arrays
    */
    void RemoveAllSurfaces();

    /**
        Replaces the surface at a given priority with the given surface.
        If the surface doesn't exits, it will add it to the terrain and use the
        data of the surface at the given pririty.
        If the surface is already on the leaf it will remove the surface at 
        the given priority and add the values to the existing surface        
        
        This function will return false if we are attempting to replace a 
        surface by the same surface.
        
        @param pkSurface The surface to replace with.
        @param uiPriority The position of the surface to replace.
        @param bForceReplace Forces replacement without checking validity This should 
            only be used if all leaves will have this surface replaced.
        @return True if the replacement was successful, 
            false if both surfaces are the same.
    */
    bool ReplaceSurface(const NiSurface* pkSurface, NiUInt32 uiPriority, bool bForceReplace = false);
        
    /**
        Retrieves the current drawing priority of the given NiSurface.
        
        @return True if the surface exists within this leaf.
    */
    bool GetSurfacePriority(const NiSurface* pkSurface, 
        NiUInt32& uiPriority) const;

    /**
        Retrieves the current drawing priority of the given NiSurface.
        
        @return True if the surface exists within this leaf.
    */
    bool GetSurfacePriority(NiUInt32 uiSurfaceIndex, 
        NiUInt32& uiPriority) const;

    /** 
        The number of surfaces that this leaf uses, at this level. Does not 
        include inherited surfaces, only surfaces unique to this level.
        
        @return The number of surfaces used
    */
    NiUInt32 GetSurfaceCount() const;

    /** 
        Gets the surface associated with the given mask priority.
        
        Does not take into account inherited surfaces from parents, only
        surfaces unique to this level.
        
        @param uiPriority Which surface to retrieve
        @return A pointer to the surface in use at the given priority, or 0 if
            no valid surface was found.
    */
    const NiSurface* GetSurface(NiUInt32 uiPriority) const;

    /**
        Gets the surface index associated with the given priority.

        @param uiPriority Which surface to retrieve.
        @return the index of the requested surface. -1 if it could not 
            be found.
    */
    NiInt32 GetSurfaceIndex(NiUInt32 uiPriority) const;

    /**
        Update the surface masks for the terrain.

        @param bCalcUV Indicates whether the UV sets need to be recalculated.
    */
    void MarkSurfaceMasksChanged(bool bCalcUV = false);

    /** 
        @name Overridden functions for the case of a leaf cell (including high detail shader data)
        Refer to the NiTerrainCell documentation for more information.
        @see NiTerrainCell
    */
    //@{

    virtual bool ProcessLOD();
    virtual void Update();
    virtual void SetTextureRegion(NiPoint2 kOffset, float fScale, 
        NiTerrainCell::TextureType::Value eTexType);
    virtual void SetTexture(NiTexture* pkTexture, 
        NiTerrainCell::TextureType::Value eTexType);
    virtual NiTexture* GetTexture(NiTerrainCell::TextureType::Value eTexType);
    virtual const NiTextureRegion& GetTextureRegion(
        NiTerrainCell::TextureType::Value eType) const;
    virtual NiTextureRegion& GetTextureRegion(
        NiTerrainCell::TextureType::Value eType);    
    virtual NiUInt8 GetPixelAt(NiTerrainCell::TextureType::Value eType, 
        NiIndex kCoordinates, NiUInt32 uiComponent) const;    
    virtual void SetPixelAt(NiTerrainCell::TextureType::Value eType, 
        NiIndex kCoordinates, NiUInt32 uiComponent, NiUInt8 ucNewValue);
    //@}

    /**
        Function to determine the terrain space region of this leaf (useful for painting buffers).
    */
    void GetTerrainSpaceRegion(NiRect<efd::SInt32>& kRegion);

    /**
        Function to take a snapshot of a particular dataset on the cell
    */
    void TakeSnapshot(NiTerrainDataSnapshot* pkSnapshot, efd::UInt32 eDataSet);

protected:

    /// @name Overridden functions for the case of a leaf cell (including high detail shader data)
    /// @see NiTerrainCell
    ///@{    
    virtual bool DoAddSurface(NiUInt32 uiSurfaceIndex, NiUInt32 uiNewPriority);
    virtual bool DoRemoveSurface(NiUInt32 uiSurfaceIndex);
    /// @}

    /**
        Replaces the surface at a given priority with the surface pointed by 
        the given index.
        If the surface is already on the leaf it will remove the surface at 
        the given priority and add the values to the existing surface        
        
        This function will return false if we are attempting to replace a 
        surface by the same surface.
        
        @param uiSurfaceIndex The surface index to replace with.
        @param uiPriority The position of the surface to replace.
        @param bForceReplace Forces replacement without checking validity. This should 
            only be set to true if all leaves will have this surface replaced.
        @return True if the replacement was successful, 
            false if both surfaces are the same.
    */
    bool DoReplaceSurface(NiUInt32 uiSurfaceIndex, NiUInt32 uiPriority, bool bForceReplace);

    /**
        Function that checks if a surface we want to replace is present on the 
        borders of a cell. If it is, it checks if the surface we want to 
        replace it with exist on the corresponding adjacent leaf.

        @param uiSurfaceIndex The index of the surface we want to use
        @param uiPriority Priority of the surface we want to replace
        @return true if we can replace a surface
    */
    bool EnsureValidReplace(NiUInt32 uiSurfaceIndex, NiUInt32 uiPriority);

    /**
        Helper function which clears border values of the adjacent cell and for
        the defined surface. It will set the border values to usValue.

        @param uiPriority Priority, on the current leaf, of the material we 
            want to clear.
        @param usValue Value to clear the boder values with.
    */
    void ClearAdjacentBorders(NiUInt32 uiPriority, NiUInt8 usValue = 0);

    /**
        Prepares this leaf for painting. This may involve creating a new 
        blend mask texture for the leaf.
    */
    void PrepareForPainting();

    /**
        Clears all the values of a surface mask to a particular value. 
        NOTE: This function will also set the bordering values of the mask to
        the given value. To re sync the border values use the 
        SyncAdjacentSurfaceMask functions.

        @param uiPriority the mask channel to modify.
        @param uiClearValue the value to set the masks to.
    */
    void ClearSurfaceMask(NiUInt32 uiPriority, NiUInt8 uiClearValue);

    /**
        Synchronizes the border surface mask values with all the adjacent 
        cells. For further information on the parameters of this function, see
        the SyncAdjacentSurfaceMask function

        @see SyncAdjacentSurfaceMask
        @return true if we succeeded for all leaves, false otherwise
    */
    void SyncAdjacentSurfaceMasks(NiUInt32 uiPriority, bool bPushValues = true);

    /**
        Synchronizes the surface mask values with the adjacent block specified
        by uiDirection (values from NiTerrainCell::BORDERS). 

        @param uiPriority the channel of the surface mask to sync.
        @param uiDirection the bordering block to synchronize with 
            (top/bottom/left/right and corners)
        @param bPushValues true if this leaf's mask values should be copied
            to the other leaf. False if the other leaf's values should be 
            copied to this one.

        @return true if we succeeded, false otherwise
    */
    void SyncAdjacentSurfaceMask(NiUInt32 uiPriority, NiUInt32 uiDirection, 
        bool bPushValues = true);

    /**
        Copies a surface mask from one channel to another.

        @param uiPrioritySrc the source channel of the data
        @param uiPriorityDst the destination channel of the data
    */
    void CopySurfaceMask(NiUInt32 uiPrioritySrc, NiUInt32 uiPriorityDst);

    /**
        Set the value of a pixel's component. This function is used to 
        directly manipulate a texture's data. This function simply performs
        the data transfer (no border testing etc)
    */
    void DoSetPixelAt(NiPixelData* pkPixelData, NiIndex kCoordinates, 
        NiUInt32 uiComponent, NiUInt8 ucNewValue);

    /**
        Get the value of a pixel's component. This function is used to 
        directly query a texture's data. This function simply performs
        the data transfer.
    */
    NiUInt8 DoGetPixelAt(NiPixelData* pkPixelData, NiIndex kCoordinates, 
        NiUInt32 uiComponent) const;

    /**
        Updates changes made to the masks and resends the appropriate data to
        the shader (added / removed materials....)
    */
    void UpdateLeafShaderData();

    /// The number of surfaces this leaf currently references
    NiUInt32 m_uiNumUsedSurfaces;
    
    /// defines the index for a surface at a specific priority (channel in blend texture)
    NiInt32 m_aiSurfaceIndex[MAX_NUM_SURFACES];

    /// Combined alpha surface mask defining the amount of blending to use
    NiTextureRegion m_kBlendTextureRegion;

    /// Has the contents of a surface changed?
    bool m_bSurfaceChanged;
    
    /// Has a mask been added or removed?       
    bool m_bSurfaceLayersChanged;  
};

NiSmartPointer(NiTerrainCellLeaf);

#include "NiTerrainCellLeaf.inl"
#endif
