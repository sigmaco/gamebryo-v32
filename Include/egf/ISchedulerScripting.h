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
#ifndef _ISchedulerScripting_h_
#define _ISchedulerScripting_h_

#include <egf/egfLibType.h>
#include <efd/utf8string.h>
#include <egf/EntityID.h>
#include <efd/IDs.h>
#include <egf/egfClassIDs.h>
#include <efd/Category.h>

namespace efd
{
    class AssetLoadResponse;

}

namespace egf
{
    class Entity;
    class Scheduler;
    class PendingBehavior;
    class EventMessage;


/**
    Interface class for scheduler scripting support. This provides a common interface
    when embedding scripting language support into the scheduler.
 */
class EE_EGF_ENTRY ISchedulerScripting : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ISchedulerScripting, efd::kCLASSID_ISchedulerScripting, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:
    /// The status of the runtime.
    enum RuntimeStatus
    {
        /// the runtime is ready for initialization.
        rtstat_PreInit,

        /// the runtime is available for use.
        rtstat_Ready,

        /// the runtime is disabled.
        rtstat_Disabled,

        /// the runtime has shutdown
        rtstat_Shutdown,
    };

    /// @name Construction and Destruction
    //@{
    /// Construct a new ISchedulerScripting object.
    ISchedulerScripting()
        : m_runtimeStatus(rtstat_PreInit)
        , m_pScheduler(0)
    {}

    virtual ~ISchedulerScripting();
    //@}

    /// Called during Init to setup scripting. InitForScripting is called from the Scheduler
    /// to initialize this runtime and prepare it to execute behavior scripts.
    virtual bool InitForScripting(Scheduler* pScheduler) = 0;

    /// Called to shutdown scripting. Once this is called the runtime is no
    /// longer valid and can no longer execute behavior scripts. When overriding this method
    /// be sure to call the base class.
    virtual void Shutdown()
    {
        m_runtimeStatus = rtstat_Shutdown;
    }

    /**
        Preload a script module.  This can be called to avoid hitches caused by script loading.

        @param name The name of the script file to preload.
        @param callback Optional category to receive a ScriptLoadResponse message once the script is
            loaded. 
    */
    virtual void PreloadModule(const char* name, efd::Category callback=efd::kCAT_INVALID)
    {
        EE_UNUSED_ARG(name);
        EE_UNUSED_ARG(callback);
    }

    /**
        Used to request that a module be reloaded.  It is typically called when the system
        detects that the source file has changed.  This has no effect unless the specified
        module is already loaded
        @param name The name of the already loaded Lua script file to reload
        @return True if the module was reloaded.
    */
    virtual bool ReloadModule(const char* name)
    {
        EE_UNUSED_ARG(name);
        return true;
    }

    /// Execute a pending behavior.
    virtual bool DoScriptBehavior(egf::PendingBehavior* pPendBehavior) = 0;

    /// Returns the runtime status
    inline RuntimeStatus GetStatus()
    {
        return m_runtimeStatus;
    }

    /**
        Get the category used to load script assets.
    */
    virtual efd::Category GetAssetLoadCategory() const 
    {
        return efd::kCAT_INVALID;
    }

    /**
        Handle an asset load response message for a script.
    */
    virtual void HandleAssetLoadResponse(const efd::AssetLoadResponse*, efd::Category)
    {
        // noop implementation
    }

protected:
    RuntimeStatus m_runtimeStatus;
    Scheduler* m_pScheduler;

public:

    /// Split the given string at the first instance of i_ch and place the results
    /// in o_strFirst and o_strSecond
    bool split(
        const efd::utf8string& i_str,
        char i_ch,
        efd::utf8string& o_strFirst,
        efd::utf8string& o_strSecond);
};

typedef efd::SmartPointer<ISchedulerScripting> ISchedulerScriptingPtr;

} // end namespace egf

#endif // _ISchedulerScripting_h_
