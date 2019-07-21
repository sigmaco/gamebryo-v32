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

#ifndef NIVIEWERSCENEGRAPHUPDATE_H
#define NIVIEWERSCENEGRAPHUPDATE_H

#include "NiSceneGraphUpdateServiceLibType.h"

#include "NiSceneGraphUpdate.h"

class efd::ServiceManager;

/**
    This singleton is used by a viewer application to cache a scene graph that is replicated
    from an editor.

    The singleton can be used to access the scene graph root, current camera, and config
    settings sent by a NiEditorSceneGraphUpdate object. In addition, this object interprets
    the timeline related config settings sent by the editor to start, restart, and stop
    animations in the replicated scene graph.
*/
class NISCENEGRAPHUPDATESERVICE_ENTRY NiViewerSceneGraphUpdate : public NiSceneGraphUpdate
{
public:
    /// Initialize object
    NiViewerSceneGraphUpdate();

    /// Destroy object
    virtual ~NiViewerSceneGraphUpdate();

    /**
        Initialize NiSceneGraphUpdate singleton with a NiViewerSceneGraphUpdate object

        This method invokes the NiSceneGraphUpdate::Initialize() method to initialize object-based
        network messaging.

        In addition, this method registers a new NiSceneGraphUpdateService object with the
        ServiceManager to enable sending and receiving messages between the singleton and the
        network messaging system.

        @param pkViewerSceneGraphUpdate Optional NiSceneGraphUpdate object to be used as singleton.
            If this parameter is NULL, a new NiViewerSceneGraphUpdate will be instantiated.
        @param pkServiceManager Optional ServiceManager object to use when registering the
            NiSceneGraphUpdateService and other services. If this value
            is NULL, a new ServiceManager will be created.
    */
    static void InitializeViewer(NiViewerSceneGraphUpdate* pkViewerSceneGraphUpdate = NULL,
        efd::ServiceManager* pkServiceManager = NULL);

    /// Halts replication and invokes shutdown on the NiSceneGraphUpdate singleton
    static void ShutdownViewer();

    /// If this object created the ServiceManager (see InitializeViewer()), this method ticks the
    /// ServiceManager until all queued messages have been sent before returning
    virtual bool Update();

    /// Send NiSceneGraphUpdate::MESSAGE_VIEWER_ADDED to alert editor that a new viewer is on the
    /// network and start replication of scene graph
    virtual bool Start(NiUInt32 uiWaitForNetworkInitInSec = 0);

    /// Delete all objects in the local cache, send NiSceneGraphUpdate::MESSAGE_VIEWER_REMOVED
    /// message, and stop replication
    virtual bool Stop();

    /// This method is called after objects have been received and inserted into the scene graph
    virtual void PostHandleUpdateObject();

    /// This method is called after the config settings have been updated
    virtual void PostHandleUpdateSettings();

protected:

    inline bool IsPSController(NiTimeController* pkController) const;

    void RestartLoopingAnimations();
    void CheckForPlaybackEndTime();
    void RunUpAllParticleSystems();
    void StartAnimationControllers(NiObjectNET* pkObj, float fTime);
    void StopAnimationControllers(NiObjectNET* pkObj, bool bSkipParticleSystems);

    bool m_bAnimationsStopped;
    float m_fPlaybackStartTime;
    float m_fPlaybackEndTime;
};

#include "NiViewerSceneGraphUpdate.inl"

#endif // NIVIEWERSCENEGRAPHUPDATE_H
