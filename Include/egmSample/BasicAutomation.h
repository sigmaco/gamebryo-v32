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
#ifndef EE_BASICAUTOMATIONSERVICE_H
#define EE_BASICAUTOMATIONSERVICE_H

#include <efd/ISystemService.h>
#include <efd/IConfigSection.h>
#include "egmSampleLibType.h"
#include "egfDemoSystemServiceIDs.h"


namespace egmSample
{
/**
    Useful to help with automating framework based applications.  This service, when activated, can:
    1.) switch the program into a fixed timestep mode
    2.) load or unload specific blocks on specific ticks
    3.) take screenshots on specific frames

    The activation and utilization of the service is controlled completely by configuration
    settings:

    @verbatim
    BasicAutomation.Enabled = <bool>
    BasicAutomation.RealTimeClockDelta = <double>
    BasicAutomation.ScreenShotDir = <path for placing screenshots>
    BasicAutomation.ScreenShotPrefix = <prefix added to all screenshot filenames>
    BasicAutomation.ScreenShotSuffix = <suffix added to all screenshot filenames before the extension>
    BasicAutomation.ScreenInterval = <integer, a screen shot will be taken every this-many frames>
    BasicAutomation.DependentServices.# = <Service Name to wait for in OnInit before starting Frame 0>
    BasicAutomation.Frame<#>.ChangeDir = <new ScreenShotDir value, can be blank>
    BasicAutomation.Frame<#>.ChangePrefix = <new ScreenShotPrefix value, can be blank>
    BasicAutomation.Frame<#>.ChangeSuffix = <new ScreenShotSuffix value, can be blank>
    BasicAutomation.Frame<#>.LoadBlock = <urn to load>
    BasicAutomation.Frame<#>.AutoEnter = <bool, if loading a block this frame should entities in that block auto-enter the world. Defaults to true.>
    BasicAutomation.Frame<#>.UnloadBlock = <urn to unload>
    BasicAutomation.Frame<#>.ScreenShot = <optional additional filename, prefix and suffix will be added>
    BasicAutomation.Frame<#>.Shutdown
    @endverbatim

    Frame numbers begin counting at 1 on the first OnTick call to this service
*/
class EE_EGMSAMPLE_ENTRY BasicAutomation : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(BasicAutomation, efd::kCLASSID_BasicAutomation, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// Constructor
    BasicAutomation();

    /**
        Take a screen shot.

        The filename can use several special tokens that will be replaced in the resulting name:

        @verbatim
            %F - Frame count. The number of times the service has been ticked.
            %I - Index. An index that starts at one and goes up every time a screen shot is taken.
            %N - process Name. The value returned from ServiceManager::GetVirtualProcessName.
            %P - Prefix string. The value specified by the BasicAutomation.ScreenShotPrefix config
                parameter (or the overridden value from the most recent Frame#).
            %S - Suffix string. The value specified by the BasicAutomation.ScreenShotSuffix config
                parameter (or the overridden value from the most recent Frame#).
        @endverbatim

        These tokens are replaced in the following order: %P, %S, %N, %F, %I. As a result it is
        possible to include some additional specifiers in some replacement strings.

        The root name is optional, if no name is provided then "%P%N%I%S" is used with appropriate
        replacements. The path as provided by BasicAutomation.ScreenShotDir (or the override from
        the most recent frame) is always used. The file extension is always set to ".png" and files
        are always stored in the PNG format.
    */
    void TakeScreenShot(const char* root = NULL);

protected:
    /**
        Reads the configuration data, sets the real time clock step
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        Increments the frame count.
        Performs and requested frame actions
    */
    virtual efd::AsyncResult OnTick();

    virtual const char* GetDisplayName() const;

    void PrepareScreenShotDirectory();
    efd::utf8string PrepareFilename(const char* root = NULL);
    void LoadBlock(const efd::utf8string& urn, bool autoEnter);
    void UnloadBlock(const efd::utf8string& urn);

    efd::UInt32 m_tickCount;
    efd::UInt32 m_snapShotsTaken;

    const efd::ISection* m_pConfig;

    bool m_fEnabled;
    efd::utf8string m_screenShotDir;
    efd::utf8string m_screenShotPrefix;
    efd::utf8string m_screenShotSuffix;
    efd::UInt32 m_screenInterval;
    efd::Float64 m_clockStep;
};
typedef efd::SmartPointer<BasicAutomation> BasicAutomationPtr;

} // end namespace egmSample


#endif // EE_BASICAUTOMATIONSERVICE_H
