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
#ifndef EE_ISCRIPTFACTORY_H
#define EE_ISCRIPTFACTORY_H

#include <efd/BaseAssetFactory.h>
#include <egf/EntityTypes.h>
#include <egf/egfClassIDs.h>

namespace egf
{

/**
    Abstract base class for script factories used to load behavior script files using th
    efd::AssetFactoryManager. Script factories for specific runtimes should publicly inherit
    from this class.
 */
class EE_EGF_ENTRY IScriptFactory : public efd::BaseAssetFactory
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(IScriptFactory, efd::kCLASSID_IScriptFactory, efd::BaseAssetFactory);
    /// @endcond

public:
    /**
        Get the behavior type supported by this script factory.

        @return the type of scripted behavior associated with this factory.
    */
    virtual egf::BehaviorTypes GetScriptType() const = 0;
};

/// A SmartPointer for the IScriptFactory class
typedef efd::SmartPointer<IScriptFactory> IScriptFactoryPtr;

} // end namespace egf

#endif // EE_ISCRIPTFACTORY_H
