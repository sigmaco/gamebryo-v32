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

#ifndef EE_PyObjectPtr_h
#define EE_PyObjectPtr_h
#pragma once

#include <egfPython/egfPythonLibType.h>
#include <Python.h>

namespace egf
{

/// Special value used to distinguish an adopting constructor from a normal constructor.
enum _Adopt
{
    Adopt,
};

/**
    A smart pointer for PyObject pointers.  Automatically manages the reference count of python
    objects that are returned from methods like Py_BuildValue and PyObject_CallObject.

    @note: Because this is designed to work with existing Python functions it has different
    semantics than efd::SmartPointer.  Mainly, when a raw pointer is assigned to a PyObjectPtr
    it is assumed that pointer already has one outstanding reference so we do not call PyINCREF.
    As result special care must be taken if you use a PyObjectPtr to store a "borrowed" PyObject
    such as would be returned by, for example, PyDict_GetItemString.  You must set such borrowed
    references using the Adopt method.

    @code
        // Good usages of PyObjectPtr:
        PyObjectPtr pyModule = PyImport_ImportModule("scheduler");
        PyObjectPtr pyDictionary = PyModule_GetDict(pyModule);
        PyObjectPtr pyMethod.Adopt(PyDict_GetItemString(pyDictionary, "StartBehavior"));

        // ERROR: The following will result in the item being deleted from the dictionary!
        PyObjectPtr pyBadUsage = PyDict_GetItemString(pyDictionary, "StartBehavior");
    @endcode
*/
class EE_EGF_PYTHON_ENTRY PyObjectPtr
{
    PyObject* m_py;

public:
    /// Copy Constructor
    PyObjectPtr(const PyObjectPtr& rhs);

    /**
        Constructor. This assumes that the passed in object already has an extra reference on it;
        the object is stored without adding any additional references. Use the default constructor
        and call Adopt instead if an extra reference needs to be held on the object.
    */
    PyObjectPtr(PyObject* rhs);

    /**
        Adopting Constructor. This will add a reference to the passed in object.
    */
    PyObjectPtr(_Adopt, PyObject* rhs);

    /// Default Constructor
    PyObjectPtr();

    /// Destructor
    ~PyObjectPtr();

    /// Cast operator
    operator PyObject*() const;

    /// Dereference operator
    PyObject* operator->() const;

    /// Assignment operator.
    PyObjectPtr& operator=(const PyObjectPtr& rhs);

    /**
        Assignment operator. This assumes that the passed in object already has an extra reference
        on it; the object is stored without adding any additional references. Use Adopt instead if
        an extra reference needs to be held on the object.
    */
    PyObjectPtr& operator=(PyObject* rhs);

    /**
        Assigns a PyObject pointer that doesn't have an extra reference into the smart pointer.
        This will add a reference to the passed in object and release any reference previously held
        by the smart pointer.
    */
    void Adopt(PyObject* rhs);

    /**
        Returns the contained PyObject pointer and sets the internal pointer to NULL.  Afterwards
        the caller is responsible for eventually freeing the returned PyObject pointer.
    */
    PyObject* Orphan();
};

} // end namespace egf

#endif // EE_PyObjectPtr_h
