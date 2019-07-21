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

#ifndef _SchedulerPython_h_
#define _SchedulerPython_h_

#include <egfPython/egfPythonLibType.h>
#include <egf/ISchedulerScripting.h>
#include <efd/StdContainers.h>

#include <efd/MessageHandlerBase.h>
#include <efd/DynamicModule.h>
#include <egf/egfClassIDs.h>

#if !defined(DISABLE_SCRIPTING) && defined(PYTHON_SCRIPTING)
#include <Python.h>
#else
class PyObject;
#endif

namespace efd
{
    class AssetLocatorResponse;
    class AssetConfigurationMessage;
}

namespace egf
{

/// A Python specific implementation of SchedulerScripting.
class EE_EGF_PYTHON_ENTRY SchedulerPython : public egf::ISchedulerScripting
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1( SchedulerPython, efd::kCLASSID_SchedulerPython, egf::ISchedulerScripting );
    /// @endcond

public:

    ///@ name Construction and Destruction
    //@{
    SchedulerPython();
    virtual ~SchedulerPython();
    //@}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool InitForScripting( Scheduler* pScheduler );
    virtual bool DoScriptBehavior(egf::PendingBehavior* pPendBehavior);
    virtual void Shutdown();

    /// The function prototype for a SWIG-generated python initialization function.
    typedef void (*PythonScriptInitFunction)();

    /**
        Register a SWIG-Generated Python initialization method with the Python runtime. These
        functions are called during InitForScripting. Any calls made to this function after the
        engine is initialized are ignored.
    */
    static bool AddStaticBuiltinInitFunction(PythonScriptInitFunction i_pfn);

protected:

    bool InitPython();
    bool InitBuiltins();
    bool InitSystemPath();
    bool InitUserPath();
    bool InitCMUserPath();
    void AddPythonPath(efd::utf8string strPath);
    bool InitAssetUserPath();

    // All the dynamic modules containing built-ins that we know about:
    efd::list<efd::DynamicModule> m_BuiltinModules;

    // Some built-ins are coming from static libraries linked directly to the final
    // executable and cannot be easily moved into DLLs.  We still need to allow these to be
    // initialized so call some static functions directly.  Since these functions are static
    // linked we don't need to hold onto the dynamic module handles
    typedef efd::list<PythonScriptInitFunction> StaticBuiltinList;
    static StaticBuiltinList ms_StaticBuiltinInitFunctions;

    // local python objects used to add/remove python behavior breakpoints
    PyObject* m_pyConnectToDebugger;
    PyObject* m_pyAddModelBreakpoint;
    PyObject* m_pyRemoveModelBreakpoint;
    PyObject* m_pyAddEntityBreakpoint;
    PyObject* m_pyRemoveEntityBreakpoint;

public:
    void HandleAssetLookupMsg(const efd::AssetLocatorResponse* pMessage, efd::Category targetChannel);

};

typedef efd::SmartPointer<SchedulerPython> ISchedulerPythonPtr;

} // end namespace egf

#endif // _SchedulerPython_h_
