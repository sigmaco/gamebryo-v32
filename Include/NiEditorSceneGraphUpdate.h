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

#ifndef NIEDITORSCENEGRAPHUPDATE_H
#define NIEDITORSCENEGRAPHUPDATE_H

#include "NiSceneGraphUpdateServiceLibType.h"

#include "NiSceneGraphUpdate.h"

namespace efd
{
    class DynamicModule;
}

/**
    This singleton is used by an editor application to replicate a scene graph to one or more
    viewers.

    The caller can insert arbitrary NiObjects into this object along with a unique ID. The
    objects will then be replicated to any NiViewerSceneGraphUpdate objects that have connected
    to this object's ChannelManager service. Likewise, the editor can set the root node, current
    camera, and config settings that will be sent to all viewers.
*/
class NISCENEGRAPHUPDATESERVICE_ENTRY NiEditorSceneGraphUpdate : public NiSceneGraphUpdate
{
public:
    /// Initialize object
    NiEditorSceneGraphUpdate();

    /// Destroy object
    virtual ~NiEditorSceneGraphUpdate();

    /**
        Initialize NiSceneGraphUpdate singleton with a NiEditorSceneGraphUpdate object

        This method invokes the NiSceneGraphUpdate::Initialize() method to initialize object-based
        network messaging.

        In addition, this method registers a new NiSceneGraphUpdateService object with the
        ServiceManager to enable sending and receiving messages between the singleton and the
        network messaging system.

        Lastly, the editor also creates a ChannelManager service (if it doesn't already exist) to
        accept network connections from viewers and route messages to multiple viewers.

        @param pkEditorSceneGraphUpdate Optional NiSceneGraphUpdate object to be used as singleton.
            If this parameter is NULL, a new NiEditorSceneGraphUpdate will be instantiated.
        @param pkServiceManager Optional ServiceManager object to use when registering the
            NiSceneGraphUpdateService and other services. If this value is NULL, a new
            ServiceManager will be created.
    */
    static void InitializeEditor(NiEditorSceneGraphUpdate* pkEditorSceneGraphUpdate = NULL,
        efd::ServiceManager* pkServiceManager = NULL);

    /**
        Sends NiSceneGraphUpdate::MESSAGE_EDITOR_STOPPED message and invokes
        NiSceneGraphUpdate::Shutdown() to clear the object cache and stop network communication.
    */
    static void ShutdownEditor();

    /// If this object created the ServiceManager (see InitializeEditor()), this method ticks the
    /// ServiceManager until all queued messages have been sent before returning
    virtual bool Update();

private:

};

#include "NiEditorSceneGraphUpdate.inl"

#endif // NIEDITORSCENEGRAPHUPDATE_H
