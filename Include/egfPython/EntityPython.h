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
#ifndef EE_EntityPython_h
#define EE_EntityPython_h

#if !defined(DISABLE_SCRIPTING) && defined(PYTHON_SCRIPTING)

#include <Python.h>
#include <egfPython/egfPythonLibType.h>


namespace egf
{
/// @name Built-in functions from EntityPython.h

//@{

/**
    This method returns the specified property for the specified entity

    @param self Pointer to the calling Python script (not used)
    @param args Pointer to args passed in by the Python script.  Arguments are:
    \code
        Args:
            Arg 1: Entity ID
            Arg 2: property ID or name (can be specified as either tPropertyID or string)
            Arg 3: key for map properties (optional)
    \endcode

    @return PyObject* : A Python object containing the return value, or Py_None if the specified
        entity doesn't exist or doesn't contain the requested property.

    @note if the result is a multi-part result (like efd::Point3, lists, etc.), then the return
        value is a tuple sequence (corresponds to how values are passed to SetProperty())
*/
EE_EGF_PYTHON_ENTRY PyObject* GetProperty(PyObject* self, PyObject* args);


/**
    This method returns the default value of the specified property for the specified entity.
    The default value is the value specified in the flat model and does not reflect any overrides
    specified in the block file.

    @param self  Pointer to the calling Python script (not used)
    @param args Pointer to args passed in by the Python script.  Arguments are:
    \code
        Args:
            Arg 1: Entity ID
            Arg 2: property ID or name (can be specified as either tPropertyID or string)
            Arg 3: key for map properties (optional)
    \endcode

    @return PyObject* : A Python object containing the return value, or Py_None if the specified
        entity doesn't exist or doesn't contain the requested property.

    @note if the result is a multi-part result (like efd::Point3, lists, etc.), then the return
        value is a tuple sequence (corresponds to how values are passed to SetProperty())
*/
EE_EGF_PYTHON_ENTRY PyObject* GetDefaultProperty(PyObject* self, PyObject* args);


/**
    This method sets the specified property for the specified entity

    @param self  Pointer to the calling Python script (not used)
    @param args Pointer to args passed in by the Python script.  Arguments are:
    \code
        Args:
            Arg 1: Entity ID
            Arg 2: property ID or name (can be specified as either tPropertyID or string)
            Arg 3: key for map properties (optional)
            Arg 4: value
    \endcode

    @return PyObject* : A Python object containing an integer result value.  The value will be
        zero on success or non-zero if an error occurred.

    @note if the property is a multi-part result (like efd::Point3, lists, etc.) then the value
        passed in should be a tuple.
*/
EE_EGF_PYTHON_ENTRY PyObject* SetProperty(PyObject* self, PyObject* args);

/**
    This method sends an event and blocks waiting for a response.

    @param self Pointer to the calling Python script (not used)
    @param args Pointer to args passed in by the Python script.  Arguments are:
    \code
        Args:
           Arg 1: EntityID for the target entity
           Arg 2: String containing the behavior name to call
           Arg 3: (optional) ParameterList* containing arguments to the behavior
           Arg 4: (optional) TimeType with the number of seconds to delay the event
    \endcode

    @return A Python object which wrappers a ParameterList containing the response data.
*/
EE_EGF_PYTHON_ENTRY PyObject* py_SendAndWaitForReply(PyObject* self, PyObject* args);

/**
    This method yields the current coroutine for a specified number of milliseconds.

    @param self  Pointer to the calling Python script (not used)
    @param args Pointer to args passed in by the Python script.  Arguments are:
    \code
        Args:
           Arg 1: Time to sleep in milliseconds
    \endcode

    @return Py_None
*/
EE_EGF_PYTHON_ENTRY PyObject* py_Sleep(PyObject* self, PyObject* args);

//@}

} // end namespace egf

#endif // !defined(DISABLE_SCRIPTING) && defined(PYTHON_SCRIPTING)

#endif // EE_EntityPython_h
