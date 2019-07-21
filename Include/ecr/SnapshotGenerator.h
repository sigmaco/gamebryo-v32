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
#ifndef EE_SNAPSHOTGENERATOR_H
#define EE_SNAPSHOTGENERATOR_H

// SnapshotGenerator is compiled out of Shipping configurations
#ifndef EE_CONFIG_SHIPPING

#include "ecrLibType.h"
#include <ecr/ecrClassIDs.h>

namespace efd
{
    class MessageService;
    class ServiceManager;
    class StreamMessage;
}

namespace ecr
{

/**
    The SnapshotGenerator is used to produce live images from the game for display in a connected,
    Toolbench-hosted Simulation Debugger. These images can be generated from arbitrary world
    locations to give a better idea of the state of the game beyond screen space.
*/
class EE_ECR_ENTRY SnapshotGenerator : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SnapshotGenerator, efd::kCLASSID_SnapshotGenerator, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// Creates the singleton instance of SnapshotGenerator.
    static void Create(efd::ServiceManager* pServiceMgr);
    /// Destroys the singleton instance of SnapshotGenerator.
    static void Destroy();

    /// Processes image generation requests from the connected Simulation Debugger.
    void HandleSimDebuggerCommand(const efd::StreamMessage* pMessage, efd::Category targetChannel);

private:
    /// Default constructor. 
    SnapshotGenerator();

    /// Prepares SnapshotGenerator for use.
    void Initialize(efd::ServiceManager* pServiceMgr);
    /// Frees resources used by SnapshotGenerator.
    void Shutdown();

    /**
        The main image generation algorithm used to fulfill Toolbench requests.
        @param width The width in pixels of the image to generate.
        @param height The height in pixels of the image to generate.
        @param cameraPos The world position of the camera used to render the image.
        @param isBackdrop True if the generated image is intended to serve as a world backdrop.
        @return True if image generation succeeds, yielding a results message to Toolbench.
    */
    bool GenerateImage(efd::UInt32 width, efd::UInt32 height, const efd::Point3& cameraPos,
        efd::Bool isBackdrop);

    /// Flag indicating whether SnapshotGenerator has registered to handle requests.
    efd::Bool m_initialized;

    /// Cached pointer to the ServiceManager.
    efd::ServiceManager* m_pServiceManager;
    /// Cached pointer to the MessageService.
    efd::MessageService* m_pMessageService;

    /// The singleton SnapshotGenerator instance.
    static efd::SmartPointer<SnapshotGenerator> ms_spInstance;
};

/// A smart pointer type for SnapshotGenerator.
typedef efd::SmartPointer<SnapshotGenerator> SnapshotGeneratorPtr;

}

#endif // EE_CONFIG_SHIPPING

#endif
