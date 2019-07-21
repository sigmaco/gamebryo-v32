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


// TODO DT#23952 -- write typechecks for each of these. See bapiLuaTypeMaps.i for examples. 

/* File : bapiTypeMaps.i */

#ifdef SWIGPYTHON

/**
    A helper define to map a basic type into and out of scripting. It provides mappings
    for (in), (out), (in) const &, and (argout) &. It also defines lists for the Type.
    
    (in) input arguments are going from Python to C
    (out) return arguments are going from C to Python
    (argout) arguments are pass-by-reference arguments. They're getting read from Python
             into an temp variable, that temp variable is passed to C, and the final value
             found in the temp variable pushed back to Python.               
 */
%define EE_SWIG_PYTHON_TYPE_WRAP(T)

// Const reference
%typemap(in) const T& (T temp)
{
    // T const reference in
    temp = bapiPython::PyTraits<T>::FromPyObject($input);
    $1 = &temp;
}
%typemap(out) const T&
{
    PyObject *o = bapiPython::PyTraits<T>::ToPyObject(*$1);
    $result = bapiPython::AddPyObjectToPyTuple($result, o);
}
%typemap(argout) const T&
{
    // T const reference argout (no-op) $1
}

// Const pointer
%typemap(in) const T* (T temp)
{
    // T const pointer in
    temp = bapiPython::PyTraits<T>::FromPyObject($input);
    $1 = &temp;
}
%typemap(out) const T*
{
    PyObject *o = bapiPython::PyTraits<T>::ToPyObject(*$1);
    $result = bapiPython::AddPyObjectToPyTuple($result, o);
}
%typemap(argout) const T*
{
    // T const pointer argout (no-op) $1
}

// pass by value
%typemap(in) T 
{
    // T pass by value
    $1 = bapiPython::PyTraits<T>::FromPyObject($input);
}

// return value
%typemap(out) T
{
    // T return value
    $result = bapiPython::PyTraits<T>::ToPyObject($1);
}


// Non-const pointer: an out parameter
%typemap(in, numinputs=0) T* (T temp)
{
    // T non-const pointer in
    $1 = &temp;
}
%typemap(out) T*
{
    // T non-const pointer out
    PyObject *o = bapiPython::PyTraits<T>::ToPyObject(*$1);
    $result = bapiPython::AddPyObjectToPyTuple($result, o);
}
%typemap(argout) T*
{
    // T non-const pointer out
    PyObject *o = bapiPython::PyTraits<T>::ToPyObject(*$1);
    $result = bapiPython::AddPyObjectToPyTuple($result, o);
}


// Non-const reference: an in/out parameter
%typemap(in) T& (T temp)
{
    // T non-const pointer in
    temp = bapiPython::PyTraits<T>::FromPyObject($input);
    $1 = &temp;
}
%typemap(out) T&
{
    // T non-const reference out
    PyObject *o = bapiPython::PyTraits<T>::ToPyObject(*$1);
    $result = bapiPython::AddPyObjectToPyTuple($result, o);
}
%typemap(argout) T&
{
    // T non-const reference out
    PyObject *o = bapiPython::PyTraits<T>::ToPyObject(*$1);
    $result = bapiPython::AddPyObjectToPyTuple($result, o);
}


//  efd::List helpers

// const reference 
%typemap(in) const efd::list<T>& (efd::list<T> tmp)
{
    // efd::list<T> const reference in
    tmp = bapiPython::PyList_ToEutList<T>($input);
    $1 = &tmp;
}
%typemap(out) const efd::list<T>&
{
    // efd::List<T> return
    $result = bapiPython::PyList_FromEutList<T>($1);
}
%typemap(argout) const efd::list<T>&
{
    // efd::list<T> const reference argout (no-op) $1
}

// const pointer 
%typemap(in) const efd::list<T>* (efd::list<T> tmp)
{
    // efd::list<T> const pointer in
    tmp = bapiPython::PyList_ToEutList<T>($input);
    $1 = &tmp;
}
%typemap(out) const efd::list<T>*
{
    // efd::List<T> return
    $result = bapiPython::PyList_FromEutList<T>($1);
}
%typemap(argout) const efd::list<T>*
{
    // efd::list<T> const pointer argout (no-op) $1
}


// pass by value
%typemap(in) efd::list<T>
{
    // efd::list<T> pass by value
    $1 = bapiPython::PyList_ToEutList<T>($input);
}


// return type
%typemap(out) efd::list<T>
{
    // efd::List<T> return
    $result = bapiPython::PyList_FromEutList<T>($1);
}

// Non-const pointer: an out parameter
%typemap(in, numinputs=0) efd::list<T>* (efd::list<T> temp) {
    // efd::list<T> non-const pointer: in
    $1 = &temp;
}
%typemap(out) efd::list<T>*
{
    // efd::list<T> non-const pointer: out
    PyObject *o;
    o = bapiPython::PyList_FromEutList(*$1);
    if ((!$result) || ($result == Py_None)) 
    {
        $result = o;
    }
    else
    {
        if (!PyList_Check($result)) 
        {
            PyObject *o2 = $result;
            $result = PyList_New(0);
            PyList_Append($result,o2);
            Py_XDECREF(o2);
        }
        PyList_Append($result,o);
        Py_XDECREF(o);
    }
}

%typemap(argout) efd::list<T>*
{
    // efd::list<T> non-const pointer: out
    PyObject *o;
    o = bapiPython::PyList_FromEutList(*$1);
    if ((!$result) || ($result == Py_None)) 
    {
        $result = o;
    }
    else
    {
        if (!PyList_Check($result)) 
        {
            PyObject *o2 = $result;
            $result = PyList_New(0);
            PyList_Append($result,o2);
            Py_XDECREF(o2);
        }
        PyList_Append($result,o);
        Py_XDECREF(o);
    }
}

// Non-const reference: an in/out parameter
%typemap(in) efd::list<T>& (efd::list<T> temp)
{
    // efd::list<T> non-const pointer: in
    temp = bapiPython::PyList_ToEutList<T>($input);
    $1 = &temp;
}
%typemap(out) efd::list<T>&
{
    // efd::list<T> non-const pointer: out
    PyObject *o;
    o = bapiPython::PyList_FromEutList(*$1);
    if ((!$result) || ($result == Py_None))
    {
        $result = o;
    }
    else
    {
        if (!PyList_Check($result))
        {
            PyObject *o2 = $result;
            $result = PyList_New(0);
            PyList_Append($result,o2);
            Py_XDECREF(o2);
        }
        PyList_Append($result,o);
        Py_XDECREF(o);
    }
}
%typemap(argout) efd::list<T>&
{
    // efd::list<T> non-const pointer: out
    PyObject *o;
    o = bapiPython::PyList_FromEutList(*$1);
    if ((!$result) || ($result == Py_None))
    {
        $result = o;
    }
    else
    {
        if (!PyList_Check($result))
        {
            PyObject *o2 = $result;
            $result = PyList_New(0);
            PyList_Append($result,o2);
            Py_XDECREF(o2);
        }
        PyList_Append($result,o);
        Py_XDECREF(o);
    }
}
%enddef  // EE_PYTHON_SWIG_TYPE_WRAP


/**
    A helper macro that defines the binding for efd::maps into and out of Python.
 */
%define EE_SWIG_PYTHON_MAP_WRAP(KeyType, ValueType)

// const reference 
%typemap(in) const efd::map<KeyType, ValueType>& (efd::map<KeyType, ValueType> tmp)
{
    // efd::map const reference in
    tmp = bapiPython::PyDict_ToEutMap<KeyType, ValueType>($input);
    $1 = &tmp;
}


// pass by value
%typemap(in) efd::map<KeyType, ValueType>
{
    // efd::map pass by value
    $1 = bapiPython::PyDict_ToEutMap<KeyType, ValueType>($input);
}


// return value
%typemap(out) efd::map<KeyType, ValueType>
{
    // efd::map return value
    $result = bapiPython::PyDict_FromEutMap<KeyType, ValueType>($1);
}

%typemap(out) efd::map<KeyType, ValueType>&
{
    // efd::map return value
    $result = bapiPython::PyDict_FromEutMap<KeyType, ValueType>($1);
}
%typemap(argout) efd::map<KeyType, ValueType>&
{
    // efd::map return value
    $result = bapiPython::PyDict_FromEutMap<KeyType, ValueType>($1);
}

%enddef  // EE_SWIG_PYTHON_MAP_WRAP



// define bindings for all of our supported data types.
EE_SWIG_PYTHON_TYPE_WRAP(efd::Bool)
EE_SWIG_PYTHON_TYPE_WRAP(efd::Char)
EE_SWIG_PYTHON_TYPE_WRAP(efd::SInt8)
EE_SWIG_PYTHON_TYPE_WRAP(efd::UInt8)
EE_SWIG_PYTHON_TYPE_WRAP(efd::SInt16)
EE_SWIG_PYTHON_TYPE_WRAP(efd::UInt16)
EE_SWIG_PYTHON_TYPE_WRAP(efd::SInt32)
EE_SWIG_PYTHON_TYPE_WRAP(efd::UInt32)
EE_SWIG_PYTHON_TYPE_WRAP(efd::SInt64)
EE_SWIG_PYTHON_TYPE_WRAP(efd::UInt64)
EE_SWIG_PYTHON_TYPE_WRAP(efd::Float32)
EE_SWIG_PYTHON_TYPE_WRAP(efd::Float64)
EE_SWIG_PYTHON_TYPE_WRAP(efd::utf8string)
EE_SWIG_PYTHON_TYPE_WRAP(efd::Category)
EE_SWIG_PYTHON_TYPE_WRAP(efd::Color)
EE_SWIG_PYTHON_TYPE_WRAP(efd::ColorA)
EE_SWIG_PYTHON_TYPE_WRAP(efd::Matrix3)
EE_SWIG_PYTHON_TYPE_WRAP(efd::Point2)
EE_SWIG_PYTHON_TYPE_WRAP(efd::Point3)
EE_SWIG_PYTHON_TYPE_WRAP(efd::Point4)
EE_SWIG_PYTHON_TYPE_WRAP(efd::Quaternion)
EE_SWIG_PYTHON_TYPE_WRAP(efd::ID128)

EE_SWIG_PYTHON_TYPE_WRAP(egf::EntityID)
EE_SWIG_PYTHON_TYPE_WRAP(egf::EventID)
EE_SWIG_PYTHON_TYPE_WRAP(egf::PropertyID)

// Create typemaps for efd::maps containing primatives. We won't attempt to enumerate all the
// possible combinations here. If you need support for another mapping, add it here.
EE_SWIG_PYTHON_MAP_WRAP(egf::UInt32, egf::UInt32)
EE_SWIG_PYTHON_MAP_WRAP(efd::UInt32, efd::utf8string)
EE_SWIG_PYTHON_MAP_WRAP(efd::utf8string, efd::UInt32)
EE_SWIG_PYTHON_MAP_WRAP(efd::utf8string, efd::utf8string)
EE_SWIG_PYTHON_MAP_WRAP(egf::EntityID, efd::utf8string)
EE_SWIG_PYTHON_MAP_WRAP(efd::utf8string, egf:EntityID)

//------------------------------------------------------------------------------------------------
// ParameterList special handling:
//------------------------------------------------------------------------------------------------
// Running efd::ParameterList* through the default EE_SWIG_PYTHON_TYPE_WRAP define should give us:
//    |------------------------|---------------|--------------------------------------------------
//    | typename:              | treated as:   | notes:
//    |------------------------|---------------|--------------------------------------------------
//    | ParameterList*         | Input         |
//    | const ParameterList*&  | Input         |
//    | const ParameterList**  | Input         | Pointer must NOT be NULL
//    | ParameterList**        | Output        | Pointer must NOT be NULL
//    | ParameterList*&        | Input-Output  |
//    |------------------------|---------------|--------------------------------------------------
EE_SWIG_PYTHON_TYPE_WRAP(efd::ParameterList*)

// In addition to those types, we also want to handle a few more:
//    |------------------------|---------------|--------------------------------------------------
//    | typename:              | treated as:   | notes:
//    |------------------------|---------------|--------------------------------------------------
//    | const ParameterList&   | Input         |
//    | ParameterList&         | Input-Output  |
//    |------------------------|---------------|--------------------------------------------------

// const reference: an in parameter
%typemap(in) const efd::ParameterList&
{
    // ParameterList const reference in
    $1 = bapiPython::PyTraits<efd::ParameterList*>::FromPyObject($input)
}
%typemap(argout) const efd::ParameterList&
{
    // ParameterList const reference argout (no-op) $1
}

// Non-const reference: an in/out parameter
%typemap(in) efd::ParameterList&
{
    // efd::ParameterList non-const reference: in
    $1 = bapiPython::PyTraits<efd::ParameterList*>::FromPyObject($input)
}
%typemap(argout) efd::ParameterList&
{
    // efd::ParameterList non-const reference: out
    PyObject *o = bapiPython::PyTraits<efd::ParameterList*>::ToPyObject($1);
    $result = bapiPython::AddPyObjectToPyTuple($result, o);
}

#endif //SWIGPYTHON


// end python specific
//////////////////////////////////////////////////////////////////////

