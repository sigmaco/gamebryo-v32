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
#ifndef EE_TERRAINPAINTINGGUIDE_H
#define EE_TERRAINPAINTINGGUIDE_H

#include <NiTerrain.h>

namespace egmToolServices
{

class ToolTerrainService;

/**
    The painting guide creates squares that will overlap terrain cells that already hold 4 
    materials and therefore can no longer be painting with a new material.
*/
class EE_EGMTOOLSERVICES_ENTRY TerrainPaintingGuide : public efd::MemObject
{
    /// @cond EMERGENT_INTERNAL    
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// Constructor
    TerrainPaintingGuide(efd::ServiceManager* pServiceManager);
    
    /// Destructor.
    ~TerrainPaintingGuide();

    /**
        Called on every tick when the painting guide is displayed
    */
    void OnTick(NiNode* pParent);

    /**
        Function that updates the painting guide if necessary
    */
    bool Update();
    
    /**
        Checks whether a leaf should be highlighted or not using the given identification data.
    */
    void AddChangedLeaf(efd::Point2 sectorID, efd::UInt32 leafID);

    /**
        Calls upon the AddChangeLeaf overload to check whether a leaf should be highlighted
        or not.
    */
    void AddChangedLeaf(NiTerrainCellLeaf* pLeaf);

    /**
        Requests the painting guide to be rebuilt
    */
    void RequestFullRebuild();

    /**
        returns the painting guide's root object. 
    */
    NiNode* GetPaintingGuideRoot();

    /**
        Function that sets whether to display the painting guide or not
    */
    void DisplayPaintingGuide(bool showGuide);

    /**
        Function that sets the texture to display on the overlay mesh
    */
    bool SetDisplayTexture(efd::utf8string fileName);

protected:
    
    /**
        Internal class that allows basic comparison on a leaf identification object.
        A leaf is identified by its sector index and its leaf id
    */
    class InternalLeafID
    {
    public:
        efd::utf8string m_internalID;
        efd::Point2 m_sectorIndex;
        efd::UInt32 m_leafID;

        inline InternalLeafID();
        inline InternalLeafID(efd::utf8string iD);
        inline InternalLeafID(efd::Point2 sector, efd::UInt32 leaf);

        inline bool operator == (const InternalLeafID& id) const;
        inline bool operator != (const InternalLeafID& id) const;
        inline InternalLeafID& operator = (const InternalLeafID& id);
    };

    /**
        Update the painting guide with the new leaves that require a mesh overlay
    */
    void UpdatePaintingGuide();

    /**
        Parses through all the leaves on the loaded sector and calls AddChangedLeaf
    */
    void ForceOverlayRebuild();

    /**
        Resolves whether a given leaf can be painted upon with the currently active materials
    */
    bool CanPaintLeaf(InternalLeafID leaf);

    /**
        Creates a mesh for the given leaf
    */
    NiMesh* CreateLeafOverlayMesh(InternalLeafID leaf);

    // Cache an instance of the terrain service.
    ToolTerrainService* m_pTerrainService;

    /// Texture displayed on each leaf mesh
    NiTexturePtr m_spDisplayTexture;

    /// Flag marking whether the overlay needs to be rebuilt
    efd::Bool m_rebuildOverlay;

    /// Flag marking whether the overlay needs to be redrawn
    efd::Bool m_dirty;

    /// Flag marking whether the painting guide should be displayed or not
    efd::Bool m_isPaintingGuideEnabled;

    /// Flag marking whether the painting guide is displayed or not
    efd::Bool m_isPaintingGuideDisplayed;

    /// List of leaves that have changed and require a mesh to be created
    efd::vector<InternalLeafID> m_changedLeaves;

    /// List of leaves currently affected by the overlay
    efd::vector<InternalLeafID> m_affectedLeaves;
    
    /// The root node for the painting guide
    NiNodePtr m_spGuideRoot;        
};

/// Defines a smart pointer (reference counted) for the TerrainPaintingGuide class
typedef efd::SmartPointer<TerrainPaintingGuide> TerrainPaintingGuidePtr;

} // namespace

#include "TerrainPaintingGuide.inl"

#endif // EE_TERRAINPAINTINGGUIDE_H