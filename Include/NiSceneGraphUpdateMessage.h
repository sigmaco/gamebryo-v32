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

#ifndef NISCENEGRAPHUPDATEMESSAGE_H
#define NISCENEGRAPHUPDATEMESSAGE_H

#include "NiSceneGraphUpdateServiceLibType.h"
#include "NiSceneGraphUpdate.h"
#include "NiSceneGraphUpdateObject.h"

#include <NiUniversalTypes.h>
#include <NiTArray.h>

#include <efd/IMessage.h>

/**
    Class used to send NiSceneGraphUpdate-related objects across network.

    This class is derived from IMessage so that it can be sent across the network using the
    MessageService. A NiSceneGraphUpdateMessage object acts as a container for sending multiple
    objects of different types with different purposes across the network.

    This class contains several buckets of objects (one for each enum in
    NiSceneGraphUpdate::MessageType). Multiple objects of the same type can be added to a
    message object. Some of these objects are informational (such as
    NiSceneGraphUpdate::MESSAGE_VIEWER_ADDED), while others contain information used to replicate
    scene graph objects (such as NiSceneGraphUpdate::MESSAGE_UPDATE_OBJECT).

    @note This class is used internally by the NiSceneGraphUpdate class and does not need to
    be instantiated in application code.
*/
class NISCENEGRAPHUPDATESERVICE_ENTRY NiSceneGraphUpdateMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(NiSceneGraphUpdateMessage, 0xEEEE9000, efd::IMessage);

    /// @endcond

public:

    /// Initialize object
    NiSceneGraphUpdateMessage();

    /// Release object buckets
    virtual ~NiSceneGraphUpdateMessage();

    /// Returns the class ID used to identify this message object type
    virtual efd::ClassID GetClassID() const;

    /**
        Serialize this message into a stream of bytes to send over the MessageService

        @param io_ar Archive to copy bytes in or out of
    */
    virtual void Serialize(efd::Archive& io_ar);

    /// Serialize all objects in all buckets into arrays of bytes
    bool PreSend();

    /// Release all memory that was allocated in PreSend() for serializing buckets
    bool PostSend();

    /// If there are any objects in at least one bucket, the message is active.
    bool IsActive() const;

    /// @{
    /// Returns true if there are any objects of this type in a bucket
    bool IsViewerAddedMsg() const;
    bool IsViewerRemovedMsg() const;

    bool IsEditorStartedMsg() const;
    bool IsEditorStoppedMsg() const;

    bool IsSetRootNodeMsg() const;
    bool IsSetActiveCameraMsg() const;
    bool IsUpdateObjectMsg() const;
    bool IsRemoveObjectMsg() const;
    bool IsRequestObjectMsg() const;
    bool IsSceneDirtyMsg() const;
    bool IsSceneCleanMsg() const;
    bool IsUpdateSettingsMsg() const;
    /// @}

    /// @{
    /// Process all objects of this type from bucket
    bool HandleSetRootNode() const;
    bool HandleSetActiveCamera() const;
    bool HandleUpdateObject() const;
    bool HandleRemoveObject() const;
    bool HandleRequestObject() const;
    bool HandleSceneDirty() const;
    bool HandleSceneClean() const;
    bool HandleUpdateSettings() const;
    /// @}

    /**
        Compares all objects in buckets

        @param pkMessage Message object to compare this object to
        @return True if the message objects contain the same objects in their buckets
    */
    virtual bool IsEqual(const NiSceneGraphUpdateMessage* pkMessage) const;

    /**
        Insert object into bucket

        @param eType Object type identifier
        @param kObjectId Unique ID of object assigned by editor
        @param pkObject The object to be inserted
    */
    inline void AddObjectId(NiSceneGraphUpdate::MessageType eType,
        const NiSceneGraphUpdateObjectId& kObjectId, NiSceneGraphUpdateObject* pkObject);

    /**
        Returns the size of the serialized object bucket

        @param eType Type of object
        @return The size in bytes
    */
    inline NiUInt32 GetBufferSize(NiSceneGraphUpdate::MessageType eType) const;

    /**
        Returns the pointer to a serialized object bucket

        @param eType Type of object
        @return Pointer to memory containing serialized objects
    */
    inline const char* GetBuffer(NiSceneGraphUpdate::MessageType eType) const;

    /// Create an object of this type
    static efd::IMessagePtr FactoryMethod();

protected:

    NiTMap<NiSceneGraphUpdateObjectId, NiSceneGraphUpdateObjectPtr>
        m_kObjects[NiSceneGraphUpdate::MESSAGE_COUNT];

    NiUInt32 m_auiBufferSize[NiSceneGraphUpdate::MESSAGE_COUNT];
    char* m_apcBuffer[NiSceneGraphUpdate::MESSAGE_COUNT];


};
typedef efd::SmartPointer<NiSceneGraphUpdateMessage> NiSceneGraphUpdateMessagePtr;

//------------------------------------------------------------------------------------------------

#include "NiSceneGraphUpdateMessage.inl"

#endif // #ifndef NISCENEGRAPHUPDATEMESSAGE_H