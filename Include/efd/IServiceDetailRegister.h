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
#ifndef EE_ISERVICEDETAILREGISTER_H
#define EE_ISERVICEDETAILREGISTER_H

#include <efd/efdLibType.h>
#include <efd/SystemFrameworkEnums.h>

namespace efd
{

/**
    When an efd::ISystemService is registered with ServiceManager::RegisterSystemService the service
    is provided this interface in a callback in order to register aliases. This interface can only
    be used from within the ISystemService::OnServiceRegistered method, you cannot store the
    interface for later use.
*/
class EE_EFD_ENTRY IAliasRegistrar
{
public:
    /**
        Used to register an additional system service ID that maps to the current service.  This
        can be called multiple times to register multiple aliases.  Use this for services that
        derive from one or more other services.  Once called, multiple values can be passed to
        ServiceManager::GetSystemService in order to lookup the current service.

        @return True if the identity was added for this service, false if the given SSID is invalid
            or already in use.
    */
    virtual bool AddIdentity(SSID idSysSer) = 0;

    /**
        A convenience version of AddIdentity that automatically determines the SSID of the service
        from the CLASS_ID member that is defined in IBase derived classes and then simply calls the
        AddIdentity method with that SSID.

        @return True if the identity was added for this service, false if the given SSID is invalid
            or already in use.
    */
    template<typename T>
    inline bool AddIdentity()
    {
        return AddIdentity(T::CLASS_ID);
    }

protected:
    /// Destructor
    virtual ~IAliasRegistrar() {}
};


/// Flags for use by the IDependencyRegistrar::AddDependency method to describe the nature of the
/// dependency. These flags can be combined to specify multiple options in a single call.
enum ServiceDependencyFlags
{
    /// This is an optional dependency, if the specified service is present then we will be
    /// dependent on it but if it's not present this won't be treated as an error.
    sdf_Optional = 0,

    /// The specified service is a required dependency. If that service isn't found it will be
    /// treated as a fatal error.
    sdf_Required = 1,

    /// This is a normal dependency, we depend on the specified service and it will be
    /// initialized before us and shutdown after us.
    sdf_Normal = 0,

    /// The specified service is a reverse dependency, in other words the specified service
    /// should be treated as being dependent on us. Normally a service is initialized after the
    /// services that it depends on, but with a reverse dependency you are requesting to be
    /// initialized before the specified service and shutdown after that service.
    sdf_Reverse = 2,

    /// A convenience alias that combines the Optional and Reverse flags.
    sdf_OptionalReverse = sdf_Optional | sdf_Reverse,

    /// A convenience alias that combines the Required and Reverse flags.
    sdf_RequiredReverse = sdf_Required | sdf_Reverse,

    /// A convenience alias for the flags that are used by default
    sdf_DefaultFlags = sdf_Required | sdf_Normal,
};


/**
    When an efd::ISystemService is pre-initialized with ISystemService::OnPreInit the service
    is provided this interface in order to register service dependencies. This interface can only
    be used from within the ISystemService::OnPreInit method, you cannot store the interface for
    later use.
*/
class EE_EFD_ENTRY IDependencyRegistrar
{
public:
    /**
        Use to register a dependency on another service. The dependencies will determine the order
        in which the services are initialized and shutdown. The dependencies are not evaluated
        immediately, rather they are evaluated during the next tick of the ServiceManager after
        and service registrations or un-registrations are processed. This avoids complications by
        allowing the services to be constructed and registered in any order but it also means any
        errors in the dependencies such as circular dependencies or missing required services can
        not be immediately detected. When detected, dependency error conditions will log a critical
        error, throw an assert and then shutdown the service manager.

        @param idSysSer The service I depend on (or that depends on me for reverse dependencies).
        @param flags Flags to control whether this dependency is optional or required and whether
            it is normal or reverse.
        @return True if the SSID and flags are valid. A true result does not imply that the
            specified dependency is valid, only that the supplied data is valid.
    */
    virtual bool AddDependency(SSID idSysSer, efd::UInt32 flags = sdf_DefaultFlags) = 0;

    /**
        A convenience version of AddDependency that automatically determines the SSID of the
        service from the CLASS_ID member that is defined in IBase derived classes and then simply
        calls the AddDependency method.

        @param flags Flags to control whether this dependency is optional or required and whether
            it is normal or reverse.
        @return True if the SSID and flags are valid. A true result does not imply that the
            specified dependency is valid, only that the supplied data is valid.
    */
    template<typename T>
    inline bool AddDependency(efd::UInt32 flags = sdf_DefaultFlags)
    {
        return AddDependency(T::CLASS_ID, flags);
    }

protected:
    /// Destructor
    virtual ~IDependencyRegistrar() {}
};

} // end namespace efd

#endif // EE_ISERVICEDETAILREGISTER_H
