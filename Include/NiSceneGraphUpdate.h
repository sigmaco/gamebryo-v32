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

#ifndef NISCENEGRAPHUPDATE_H
#define NISCENEGRAPHUPDATE_H

#include "NiSceneGraphUpdateServiceLibType.h"
#include "NiSceneGraphUpdateObjectId.h"
#include "NiSceneGraphUpdateObject.h"
#include "NiSceneGraphUpdateSettings.h"

#include <NiMemObject.h>
#include <NiTMap.h>
#include <NiNode.h>
#include <NiCamera.h>
#include <NiString.h>
#include <NiMetricsTimer.h>
#include <NiPSEmitterCtlr.h>
#include <NiPSResetOnLoopCtlr.h>

namespace efd {
class ServiceManager;
}

/**
    The NiSceneGraphUpdate replicates a Gamebryo scene graph across a network connection.

    This singleton manages the updates to a cache of NiObjects that can be replicated to other
    NiSceneGraphUpdate instances. The object enables an editor to send an entire scene
    graph or incremental changes (as small as an individual NiObject) to one or more viewers.

    Two derived classes (NiEditorSceneGraphUpdate and NiViewerSceneGraphUpdate) specialize
    the class for use in the corresponding application. Use one of these derived classes instead
    of NiSceneGraphUpdate when creating an application.
*/
class NISCENEGRAPHUPDATESERVICE_ENTRY NiSceneGraphUpdate : public NiMemObject
{
    friend class NiEditorSceneGraphUpdate;
    friend class NiViewerSceneGraphUpdate;
    friend class NiSceneGraphUpdateStream; // The only way to add an object
    friend class NiSceneGraphUpdateMessage; // The way to remove set root and camera nodes
public:

    /// Messages exchanged between NiSceneGraphUpdate instances across the network
    enum MessageType
    {
        /// Invalid message ID
        MESSAGE_INVALID = -1,
        /// This message is sent by the viewer after it connects to the network
        MESSAGE_VIEWER_ADDED = 0,
        /// This message is sent by the viewer before it disconnects from the network
        MESSAGE_VIEWER_REMOVED,
        /// This message is sent by the editor after it connects to the network
        MESSAGE_EDITOR_STARTED,
        /// This message is sent by the editor before it disconnects from the network
        MESSAGE_EDITOR_STOPPED,
        /// Set the root scene graph node for replicated scene graph
        MESSAGE_SET_ROOT_NODE,
        /// Set the current camera object for viewers
        MESSAGE_SET_ACTIVE_CAMERA,
        /// Update an object in-place in a replicated scene graph
        MESSAGE_UPDATE_OBJECT,
        /// Replace an existing object in a replicated scene graph
        MESSAGE_REPLACE_OBJECT,
        /// Remove object from replicated scene graph
        MESSAGE_REMOVE_OBJECT,
        /// The viewer requests an object
        MESSAGE_REQUEST_OBJECT,
        /// Changes have been made to the scene in the editor
        MESSAGE_SCENE_DIRTY,
        /// All update messages have been processed
        MESSAGE_SCENE_CLEAN,
        /// Config settings have been updated
        MESSAGE_UPDATE_SETTINGS,
        /// Total number of message types
        MESSAGE_COUNT
    };

    /// State of individual replicated objects
    enum ObjectState
    {
        /// The object is up-to-date
        OS_CLEAN,
        /// Update an existing object in-place
        OS_UPDATE,
        /// Replace an existing object
        OS_REPLACE,
    };

    /// Helper function that returns false if state is not clean
    inline static bool IsObjectStateDirty(const NiUInt32 uiState);

    /// Initialize object
    NiSceneGraphUpdate();

    /// Destroy scene graph and shutdown network communication services
    virtual ~NiSceneGraphUpdate();

    /// Returns the singleton
    static NiSceneGraphUpdate* GetInstance();

    /**
        Creates log for debug and release builds

        @param pcLogName Log file name (can be absolute or relative to current working directory)
    */
    void SetupLogging(const char* pcLogName);

    // Helper functions
#ifdef WIN32
    /// Returns the IP address of the primary Ethernet adapter on a Windows PC
    static NiString GetPrimaryIPAddress();
#endif

    /// Returns the port number that the editor listens for connections on
    static NiUInt16 GetListenPort();

    /**
        Used by viewer to establish a connection with a editor running on a specific host

        Use GetStatusMsg() method to determine current connection status.

        @param pcChannelMgrHost IP address of the machine running editor
        @param usChannelMgrPort Port number to connect to
        @return True if an attempt to connect will be made on the next tick, false if the
            NiSceneGraphUpdateService has not been successfully created.
    */
    bool Connect(const char* pcChannelMgrHost, NiUInt16 usChannelMgrPort);

    /// Returns the port number used by underlying NiSceneGraphUpdateService to connect
    /// to the editor
    NiUInt16 GetRemotePort();

    /**
        Queues message with the NiSceneGraphUpdateService to be sent across the network

        @param eType Type identifies the purpose of the message
        @param kId A unique identifier assigned by the editor to associate objects on the viewer
            with objects on the editor
        @param pkObject The object to be transmitted across the network connection
        @return True if the messages was successfully queued
    */
    bool Send(MessageType eType,
        const NiSceneGraphUpdateObjectId& kId = NiSceneGraphUpdateObjectId::NULL_OBJECT_ID,
        NiSceneGraphUpdateObject* pkObject = NULL);

    /**
        Immediately send message across the network

        This method queues message and immediately ticks the NiSceneGraphUpdateService until it
        has been sent across the network.

        @param eType Type identifies the purpose of the message
        @param kId A unique identifier assigned by the editor to associate objects on the viewer
            with objects on the editor
        @param pkObject The object to be transmitted across the network connection
        @return True if the messages was successfully sent, false if the method timed out
    */
    bool SendImmediate(MessageType eType,
        const NiSceneGraphUpdateObjectId& kId = NiSceneGraphUpdateObjectId::NULL_OBJECT_ID,
        NiSceneGraphUpdateObject* pkObject = NULL);

    /// Pure virtual method implemented by editor and viewer subclasses
    virtual bool Update() = 0;

    /**
        Start replicating scene graph from editor to viewers

        Internally, the method flips the Ready flag to true.

        @param uiWaitForNetworkInitInSec If the caller specified a non-zero value, this method will
            wait until the network connection is established before returning
        @return False if a wait time was specified and the network connection was not established
            before the time out
    */
    virtual bool Start(NiUInt32 uiWaitForNetworkInitInSec = 0);

    /// Halts replication of the scene graph
    virtual bool Stop();

    /// Intended to be overridden by editor to indicate when a Refresh has started
    virtual bool Refresh();

    /**
        Insert an object object to be replicated from editors to viewers

        @param kId Unique identifier defined by the editor
        @param pkNiObject The object to be replicated
    */
    virtual bool AddObject(const NiSceneGraphUpdateObjectId kId, NiObject* pkNiObject);

    /// Send all objects in the local cache to viewers and then set camera, set root node,
    /// and send config settings to match editor settings.
    virtual void UpdateAllObjects();

    /// Remove all replicated objects from viewers
    virtual void RemoveAllObjects();

    /**
        Inserts multiple objects with corresponding IDs into local object cache to be replicated
        to viewers.

        @param kAddObjects Objects and IDs assigned by the editor
        @return True if objects were successfully inserted
    */
    bool AddObjects(const NiTMap<NiSceneGraphUpdateObjectId, NiObjectPtr>& kAddObjects);


    /**
        Has the node been added to the insert list?

        @param pkNode Node in question
        @return True if object is in the insert list
    */
    bool IsInsertNode(const NiNode* pkNode) const;

    /**
        Has the node been added to the insert list?

        @param kId Unique ID assigned by editor that identifies object in question
        @return True if object is in the insert list
    */
    bool IsInsertNode(const NiSceneGraphUpdateObjectId& kId) const;

    /**
        Insert node into the insert list of objects to be replicated

        @param kId Unique ID of the node to be added to scene graph
        @param pkNode New node
        @return True if object is successfully added
    */
    bool AddInsertNode(const NiSceneGraphUpdateObjectId& kId, NiNode* pkNode);

    /**
        Removes node from insert list

        @param kId The unique ID of the object to remove
        @return True if the node was found and successfully removed
    */
    bool RemoveInsertNode(const NiSceneGraphUpdateObjectId& kId);

    /// Returns true if replication is active
    inline bool IsReady() const;

    /// Returns true if there are pending updates from the editor
    inline bool IsDirty() const;

    /**
        Returns the object from local cache identified by unique ID

        @param kId ID assigned by editor application
        @return Smart pointer to object, if it exits in the local cache
    */
    inline NiSceneGraphUpdateObjectPtr GetObject(const NiSceneGraphUpdateObjectId& kId) const;

    /**
        Returns the unique object ID for the specified object

        @param pkObject The object in question
        @return Object ID or NiSceneGraphUpdateObjectId::NULL_OBJECT_ID if the object can not be
            found in the local cache
    */
    inline NiSceneGraphUpdateObjectId GetObjectId(const NiObject* pkObject) const;

    /// Returns the settings object for the NiSceneGraphUpdate singleton
    inline NiSceneGraphUpdateSettings& GetSettings();

    /// Returns the root node of the scene graph being replicated
    inline NiNode* GetRootNode();

    /// Returns the unique ID of the scene graph root being replicated
    inline NiSceneGraphUpdateObjectId GetRootNodeId() const;

    /// Returns the camera object set by the editor.
    /// The viewer can chose to use this object or not.
    inline NiCamera* GetActiveCamera();

    /// Returns the unique ID for the camera object set by the editor
    inline NiSceneGraphUpdateObjectId GetActiveCameraId() const;

    /**
        Replace object in replicated scene graphs with caller-supplied object

        @param kId The unique editor-assigned ID of the object to be replaced
        @param pkNiObject The new object
    */
    void UpdateObject(const NiSceneGraphUpdateObjectId& kId, NiObject* pkNiObject);

    /**
        Remove object from replicated scene graphs

        @param kId The unique editor-assigned ID of the object to be removed
    */
    void RemoveObject(const NiSceneGraphUpdateObjectId& kId);

    /// Update properties and effects on the entire cached scene graph
    void CleanupObjects();

    /// This method is called after objects have been received and inserted into the scene graph
    virtual void PostHandleUpdateObject();

    /// This method is called after objects have been removed from the replicated scene graph
    virtual void PostHandleRemoveObject();

    /// This method is called after the config settings have been updated
    virtual void PostHandleUpdateSettings();

    /// Function to set the scene ready callback. This gets called when the root node
    /// has been set.
    typedef bool (*NISCENEGRAPHUPDATE_SCENEREADYCALLBACK)(void* pkParam);
    inline void SetSceneReadyCallback(NISCENEGRAPHUPDATE_SCENEREADYCALLBACK pfnSceneReadyCallback,
        void* pkParam);

    /// Returns a brief message about the connection status
    const char* GetStatusMsg() const;

    enum
    {
        /// Default port to be used for editor-to-viewer communication
        NI_DEFAULT_PORT = 13123,
        /// Invalid port number for NiSceneGraphUpdate
        NI_INVALID_PORT = 0
    };

    /// @cond EMERGENT_INTERNAL

    /// Returns the instance ID that was set by SetInstanceId() calling
    inline NiUInt32 GetInstanceId() const;

    /// Assign an instance ID that can be used to distinguish objects sent by applications
    /// on the viewer.
    inline void SetInstanceId(const NiUInt32 uiInstanceId);

    /// Increment counter of objects to be sent in update
    virtual void PreHandleAddMessage();

    /// Decrement counter of objects to be sent in update
    virtual void PostHandleRemoveMessage();

    /// @endcond EMERGENT_INTERNAL

protected:

    /**
        Initialize network and message passing services

        This method creates the following services, if they have not already been registered
        with the SericeManager:
        * ConfigService: Used to read INI file for settings
        * NetService: TCP network communication
        * MessageService: Object-based network messaging.

        @note This method is protected since it is intended to be called by a specialized
            subclass.
    */
    static void Initialize(NiSceneGraphUpdate* pkSceneGraphUpdate = NULL,
        efd::ServiceManager* pkServiceManager = NULL);

    bool UpdateServiceManager();

    static bool GetConfigFilename(NiString& kConfigFilename);

    static void Shutdown();

    // Function to clean up after we have received an update or remove message
    void PostHandleMessageCleanup();

    // Function to get a unique object id
    NiSceneGraphUpdateObjectId GetNextObjectId();

    // Function to check to see if we support this type of object to be added to the system.
    bool CanUpdateObject(const NiObject* pkObject) const;

    // Used only by the NiSceneGraphUpdateStream
    NiSceneGraphUpdateObject* AddObject(const NiSceneGraphUpdateObjectId& kId);
    void SetNiObject(const NiSceneGraphUpdateObjectId& kId, NiObject* pkObject);

    // Used only by the NiSceneGraphUpdateMessage
    virtual void RemoveObjectLocal(const NiSceneGraphUpdateObjectId& kId);
    inline void SetSceneDirty();
    inline void SetSceneClean();
    inline void SetRootNode(const NiSceneGraphUpdateObjectId& kId);
    inline void SetActiveCamera(const NiSceneGraphUpdateObjectId& kId);

    bool m_bOwnsServiceManager;
    bool m_bIsReady;
    bool m_bIsDirty;
    NiUInt32 m_uiInstanceId;
    NiUInt32 m_uiProcessingMessageCount;

    NISCENEGRAPHUPDATE_SCENEREADYCALLBACK m_pfnSceneReadyCallback;
    void* m_pkSceneReadyCallbackParam;
    efd::ServiceManager* m_pServiceManager;

    // Owns data
    NiTMap<NiSceneGraphUpdateObjectId, NiSceneGraphUpdateObjectPtr> m_kObjects;
    NiTMap<const NiObject*, NiSceneGraphUpdateObjectId> m_kNiObjects;
    NiTMap<NiUInt32, NiSceneGraphUpdateObjectId> m_kRootNodes;
    NiTMap<NiUInt32, NiSceneGraphUpdateObjectId> m_kActiveCameras;

    // Replacement nodes that were supplied by the application
    NiTMap<NiSceneGraphUpdateObjectId, NiNodePtr> m_kInsertNodes;
    NiTMap<NiSceneGraphUpdateObjectId, NiNodePtr> m_kInsertNodesBackup;

    NiSceneGraphUpdateSettings m_kSettings;

    static NiSceneGraphUpdate* ms_pkThis;

    // Internal class that simply adds all the object to the update library
    class NiAddObjects : public NiStream
    {
    public:
        NiAddObjects(const NiTMap<NiSceneGraphUpdateObjectId, NiObjectPtr>& kAddObjects,
            NiSceneGraphUpdate* pkThis);
        bool IsValid() const { return m_bIsValid; }
    private:
        bool m_bIsValid;
    };
};

#include "NiSceneGraphUpdate.inl"

#endif // NISCENEGRAPHUPDATE_H
