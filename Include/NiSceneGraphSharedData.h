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
#ifndef NISCENEGRAPHSHAREDDATA_H
#define NISCENEGRAPHSHAREDDATA_H

#include "NiStandardSharedDataLibType.h"
#include "NiSharedData.h"
#include "NiPluginToolkitDefinitions.h"
#include "NiTPtrSet.h"
#include <NiNode.h>
#include "NiString.h"
#include <NiTMap.h>

class NiMeshProfileProcessor;

/// This class indicates which scene graph is currently in use. The scene
/// graph shared data object is one of the basic shared data objects
/// provided by Gamebryo.
class NISTANDARDSHAREDDATA_ENTRY NiSceneGraphSharedData : public NiSharedData
{
public:
    NiDeclareRTTI;

    /// Default constructor.
    NiSceneGraphSharedData();

    /// Virtual destructor.
    virtual ~NiSceneGraphSharedData();

    /// Adds a root into the root array. This broadcasts a message to any
    /// handlers.
    void AddRoot(NiNode* pkRoot, const char* pcName = "",
        bool bStreamable = true);

    /// Removes root from the root list. This broadcasts a message to any
    /// handlers.
    NiNodePtr RemoveRoot(NiNode* pkRoot);

    /// Removes all the roots from the root list. This broadcasts a message
    /// for each root removed.
    void RemoveAllRoots();

    /// Update all of the roots. This broadcasts a message to any handlers.
    void UpdateAll(float fTime);

    /// Update a specific root. This broadcasts a message to any handlers.
    void UpdateRoot(NiNode* pkRoot, float fTime);

    /// Get the total number of roots in the system
    unsigned int GetRootCount();

    /// Get a root out of the shared data by index.
    NiNode* GetRootAt(unsigned int uiIndex);

    /// Returns the stored name of the specified root node.
    NiString GetRootName(NiNode* pkRoot);

    /// Returns whether or not the specified root node is streamable.
    bool IsRootStreamable(NiNode* pkRoot);

    /// Returns the last time that the specified root node was updated at.
    float GetLastUpdateTime(NiNode* pkRoot);

    /// Returns all root nodes attached as children of an empty node.
    NiNodePtr GetFullSceneGraph();

    /// Returns if an exporter using this data should preserve the
    /// endianness of the original scene.  (default: false)
    bool GetPreserveEndianness();

    /// Returns if the endianness an exporter should preserve is little.
    bool GetSourceLittleEndian();

    /// Set the endianness that should be preserved.
    void SetSourceLittleEndian(bool bLittleEndian, bool bPreserve = true);

    /// This class contains placeholder information for meta-data about the
    /// scene that should end up as meta-data in the final NiStream.
    class NISTANDARDSHAREDDATA_ENTRY MetaDataObject : public NiRefObject
    {
    public:
        /// Constructor
        /// @param uiTag The type of meta-data that is being written
        /// @param uiBufferSize The size of the meta-data buffer
        /// @param pucBuffer The buffer being written
        MetaDataObject(unsigned int uiTag, unsigned int uiBufferSize,
            const NiUInt8* pucBuffer);

        /// Default destructor
        ~MetaDataObject();

        /// The type of meta-data that is being written
        unsigned int m_uiTag;

        ///The size of the meta-data buffer
        unsigned int m_uiBufferSize;

        /// The buffer being written
        NiUInt8* m_pucBuffer;
    };

    /// @cond EMERGENT_INTERNAL

    NiSmartPointer(NiSceneGraphSharedData::MetaDataObject);

    /// @endcond


    /// Get the meta-data object by index for the specified root.
    const MetaDataObject* GetMetaData(unsigned int uiWhichObject,
        unsigned int uiWhichRoot = 0) const;

    /// Get the number of meta-data objects associated with a root.
    unsigned int GetMetaDataCount(unsigned int uiWhichRoot = 0) const;

    /// Add meta-data to a given root
    void AddMetaData(MetaDataObject* pkObject,
        unsigned int uiWhichRoot = 0);

    /// Remove meta-data from a given root.
    void RemoveMetaData(unsigned int uiWhichObject,
        unsigned int uiWhichRoot = 0);

    /// Clear the meta-data for all roots.
    void ClearMetaData();

    /// Get the number of meta-data root objects.
    unsigned int GetMetaDataRootCount() const;

protected:

    /// Updates the shared data elements associated with the scene graph.
    void UpdateAssociatedSharedData();

    // The pointer to the mesh profile
    NiMeshProfileProcessor* m_pkMeshProfileProcessor;

    /// The main root node for all added root nodes.
    NiNodePtr m_spMainRoot;

    /// The set of scene root nodes. This set is provided for convenience
    /// only. The root nodes are "owned" by m_spMainRoot.
    NiTPtrSet<NiNode*, NiTMallocInterface<NiNode*> > m_kSceneRoots;

    class NodeInfo : public NiRefObject
    {
    public:
        NodeInfo(NiString strName, bool bStreamable)
        {
            m_strName = strName;
            m_bStreamable = bStreamable;
            m_fLastUpdateTime = 0.0f;
        }

        NiString m_strName;
        bool m_bStreamable;
        float m_fLastUpdateTime;
    };
    typedef efd::SmartPointer<NodeInfo> NodeInfoPtr;

    /// The names and streamability corresponding to the root nodes.
    NiTMap<NiNode*, NodeInfoPtr> m_kNodeInfoMap;
    NiTPrimitiveArray<NiTObjectArray<MetaDataObjectPtr>* > m_kMetaData;

    /// Endian behavior
    bool m_bPreserveEndian;
    bool m_bLittleEndian;
};

NiSmartPointer(NiSceneGraphSharedData);

#endif  // #ifndef NISCENEGRAPHSHAREDDATA_H
