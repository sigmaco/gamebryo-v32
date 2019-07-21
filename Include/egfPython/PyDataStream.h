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
#ifndef EE_PyDataStream_h
#define EE_PyDataStream_h

#include <egfPython/egfPythonLibType.h>
#include <efd/ParameterList.h>
#include <Python.h>

namespace egf
{
    /// @name Python ParameterList functions from PyParameterList.h

    //@{

    /// Method to initialize the ParameterList module which implements the ParameterList class
    EE_EGF_PYTHON_ENTRY void pyinit_ParameterList();

    /// Convert a PyParameterList to an efd::ParameterList.
    /// @param py A Python object
    /// @return A ParameterList pointer, or NULL if py is not of type PyParameterList.
    EE_EGF_PYTHON_ENTRY efd::ParameterList* PyParameterList_AsParameterList(PyObject* py);

    /// Create a new PyParameterList that references an existing efd::ParameterList.
    /// @param pStream A ParameterList pointer, which can be NULL.
    /// @return A new PyObject of type PyParameterList
    EE_EGF_PYTHON_ENTRY PyObject* PyParameterList_Create(efd::ParameterList* pStream);

    /// Check if the given PyObject is of type PyParameterList
    /// @param py The object to check
    /// @return True if the object is a PyParameterList
    EE_EGF_PYTHON_ENTRY bool PyParameterList_Check(PyObject* py);

    /// A simple helper for returning Py_None.
    inline PyObject* PyNone()
    {
        Py_INCREF(Py_None);
        return Py_None;
    }

    /// A simple helper for returning Py_True.
    inline PyObject* PyTrue()
    {
        Py_INCREF(Py_True);
        return Py_True;
    }

    /// A simple helper for returning Py_False.
    inline PyObject* PyFalse()
    {
        Py_INCREF(Py_False);
        return Py_False;
    }

    /// A simple helper for returning Py_True or Py_False based on the parameter.
    inline PyObject* PyTrueOrFalse(bool b)
    {
        return b ? PyTrue() : PyFalse();
    }

    /**
        The storage structure for a custom Python class.  The PyObject_HEAD macro defines all
        the python-specific goo and must come first.  After that you simply list whatever data
        you need.  If a PyObject* returns true from PyParameterList_Check then it is safe to cast
        the PyObject* to a PyParameterList*.
    */
    struct PyParameterList
    {
        PyObject_HEAD
        efd::ParameterList* m_pParameters;
        efd::UInt32 m_lastRead;
    };

    //@}

} // end namespace egf


#endif  // EE_PyDataStream_h
