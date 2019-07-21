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

#define PYTHON_SCRIPTING
%{
#include <egfPython/bapiPython.h>
#include <egfPython/EntityPython.h>
%}

%rename(LogMessage) BehaviorAPI::LogMessagePython;
%rename(LogError) BehaviorAPI::LogErrorPython;

%native(GetProperty) PyObject* egf::GetProperty(PyObject* self, PyObject* args);
%native(GetDefaultProperty) PyObject* egf::GetDefaultProperty(PyObject* self, PyObject* args);
%native(SetProperty) PyObject* egf::SetProperty(PyObject* self, PyObject* args);
%native(SendAndWaitForReply) PyObject* egf::py_SendAndWaitForReply(PyObject* self, PyObject* args);
%native(Sleep) PyObject* egf::py_Sleep(PyObject* self, PyObject* args);

%import "egfPython/bapiPythonTypeMaps.i"

// Simply include the real BehaviorAPI.i file:
%include "egf/BehaviorAPI.i" 
