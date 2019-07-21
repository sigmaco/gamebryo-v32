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
#ifndef EE_TOOLSERVICEMANAGER_H
#define EE_TOOLSERVICEMANAGER_H

#include <efd/ServiceManager.h>

namespace efd
{

/**
    The ToolServiceManager is a version of the ServiceManager for use in tools. It provides
    additional methods for ticking services in special ways that would normally be dangerous but
    may be required by certain tools.
*/
class EE_EFD_ENTRY ToolServiceManager : public efd::ServiceManager
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        ToolServiceManager,
        efd::kCLASSID_ToolServiceManager,
        efd::ServiceManager);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /**
        InitializeServices is used to Initialize the ServiceManager in situations where the
        application calls RunOnce() directly. The InitializeServices function will block until
        all services have completed their initialization state. Note that services initialize one
        at a time in dependency order so some services may have been ticking for a while by the
        time this returns.
    */
    virtual void InitializeServices();

    /**
        InitializeService is used to Initialize the ServiceManager in situations where the
        application calls RunOnce() directly.  The InitializeService function will block until
        the specified service has completed its initialization state. Note that other services
        may be ticking while waiting for this service to initialize and there may be services that
        have not started initialization when this returns.
    */
    virtual void InitializeService(efd::SSID idSysSer);
};

} // end namespace efd

#endif // EE_TOOLSERVICEMANAGER_H
