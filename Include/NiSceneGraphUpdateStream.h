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

#ifndef NISCENEGRAPHUPDATESTREAM_H
#define NISCENEGRAPHUPDATESTREAM_H

#include "NiSceneGraphUpdateServiceLibType.h"

#include <NiStream.h>

#include "NiSceneGraphUpdateObject.h"

/**
    Custom stream class that is aware of the objects cached by NiSceneGraphUpdate singleton

    This class is used to serialize NiObjects that are to be sent from the editor to the viewer.
    In addition, this class can unserialize objects in-place. This means that the memory address
    of the updated object does not change in the replicated scene graph.

    Objects that already exist in the NiSceneGraphUpdate cache (and are not dirty) are not
    serialized. In this case, the NiSceneGraphUpdateObjectId is serialized in place of the link
    id in the stream.

    This class is used internally by NiSceneGraphUpdate and does not need to be instantiated
    by application code.
*/
class NISCENEGRAPHUPDATESERVICE_ENTRY NiSceneGraphUpdateStream : public NiStream
{
public:
    /// Create object
    NiSceneGraphUpdateStream();

    /// Destroy object
    virtual ~NiSceneGraphUpdateStream();

    /**
        Save link ID for object in the stream, if the object already exists in the
        NiSceneGraphUpdate, save the NiSceneGraphUpdateObjectId instead.

        @param pkObject Object whose id is to be stored in the stream
    */
    virtual void SaveLinkID(const NiObject* pkObject);

    /// Returns the link ID of the object from the stream (ignore NiSceneGraphUpdateObjectId if
    /// present) to maintain backward compatibility with NiStream
    virtual void ReadLinkID();

    /// Return NiObject from stream (if present) or NiSceneGraphUpdate singleton
    virtual NiObject* ResolveLinkID();

    /// Instantiate new objects in stream or overwrite existing objects cached in
    /// NiSceneGraphUpdate singleton
    virtual bool LoadRTTI();

    /**
        Add top level object to stream that is to be replicated

        @param kId Unique identifier for object (assigned by editor)
        @param uiObjectState Whether object is dirty or clean
        @param pkObject Object to be inserted
    */
    void InsertObject(const NiSceneGraphUpdateObjectId& kId, const NiUInt32 uiObjectState,
        NiObject* pkObject);

    /**

        Copy stream to a buffer

        @param uiBufferSize Returns the buffer size in bytes
        @param pcBuffer Returns pointer to buffer. This must be release by the caller using
            NiFree().
    */
    bool Save(NiUInt32& uiBufferSize, char*& pcBuffer);

    /**
        Initialize stream from a buffer

        @param uiBufferSize Size of buffer in bytes
        @param pcBuffer Pointer to buffer
    */
    bool Load(const NiUInt32 uiBufferSize, const char* pcBuffer);

private:

    bool SaveObjectIds();
    bool LoadObjectIds();

    // Map used while saving
    NiTLargePrimitiveArray<NiSceneGraphUpdateObjectId> m_kObjectIds;
    NiTLargePrimitiveArray<NiUInt32> m_kObjectStates;

    // Map used while inserting
    NiTLargePrimitiveArray<NiSceneGraphUpdateObjectId> m_kTopObjectIds;
    NiTLargePrimitiveArray<NiUInt32> m_kTopObjectStates;

    // Mapping used to replace old objects to new when linking
    NiTMap<const NiObject*, NiObject*> m_kReplaceObjects;

};

#endif // NISCENEGRAPHUPDATESTREAM_H
