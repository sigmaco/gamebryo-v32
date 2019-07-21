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
#ifndef EE_BAPIPYTHON_H
#define EE_BAPIPYTHON_H

#include <egf/BehaviorAPI.h>
#include <efd/ParseHelper.h>
#include <egfPython/PyDataStream.h>

namespace bapiPython
{

/// Convert a python long or int to efd::SInt64.
inline efd::SInt64 PyLongOrInt_AsLongLong(PyObject* py);

/// Convert a python long or int to efd::UInt64.
inline efd::UInt64 PyLongOrInt_AsUnsignedLongLong(PyObject* py);

/// Templated helper functions for converting C++ data types to python and vice-versa.
template<typename T>
struct PyTraits
{
};

/// Python trait handler for efd::Bool.
template<>
struct PyTraits<efd::Bool>
{
    static efd::Bool FromPyObject(PyObject* py)
    {
        return 0 != PyInt_AsLong(py);
    }

    static PyObject* ToPyObject(efd::Bool i_data)
    {
        return egf::PyTrueOrFalse(i_data);
    }
};

/// Python trait handler for efd::utf8string.
template<>
struct PyTraits<efd::utf8string>
{
    static efd::utf8string FromPyObject(PyObject* py)
    {
        if (PyString_Check(py))
            return efd::utf8string(PyString_AsString(py));
        return efd::utf8string::NullString();
    }

    static PyObject* ToPyObject(const efd::utf8string& i_data)
    {
        return Py_BuildValue("s", i_data.c_str());
    }
};

/// Python trait handler for efd::Char*.
template<>
struct PyTraits<efd::Char*>
{
    static const efd::Char* FromPyObject(PyObject* py)
    {
        return PyString_AsString(py);
    }

    static PyObject* ToPyObject(const efd::Char* i_data)
    {
        return Py_BuildValue("z", i_data);
    }
};

/// Python trait handler for wchar_t*.
template<>
struct PyTraits<wchar_t*>
{
    static const efd::WChar* FromPyObject(PyObject* py)
    {
        return (const efd::WChar*)PyUnicode_AsUnicode(py);
    }

    static PyObject* ToPyObject(const efd::WChar* i_data)
    {
        return Py_BuildValue("u", i_data);
    }
};

/// Python trait handler for efd::SInt8.
template<>
struct PyTraits<efd::SInt8>
{
    static efd::SInt8 FromPyObject(PyObject* py)
    {
         return (efd::SInt8)PyInt_AsLong(py);
    }

    static PyObject* ToPyObject(efd::SInt8 i_data)
    {
        return Py_BuildValue("b", i_data);
    }
};

/// Python trait handler for efd::UInt8.
template<>
struct PyTraits<efd::UInt8>
{
    static efd::UInt8 FromPyObject(PyObject* py)
    {
        return (efd::UInt8)PyInt_AsUnsignedLongMask(py);
    }

    static PyObject* ToPyObject(efd::UInt8 i_data)
    {
        return Py_BuildValue("B", i_data);
    }
};

/// Python trait handler for efd::SInt16.
template<>
struct PyTraits<efd::SInt16>
{
    static efd::SInt16 FromPyObject(PyObject* py)
    {
         return (efd::SInt16)PyInt_AsLong(py);
    }

    static PyObject* ToPyObject(efd::SInt16 i_data)
    {
        return Py_BuildValue("h", i_data);
    }
};

/// Python trait handler for efd::UInt16.
template<>
struct PyTraits<efd::UInt16>
{
    static efd::UInt16 FromPyObject(PyObject* py)
    {
        return (efd::UInt16)PyInt_AsUnsignedLongMask(py);
    }

    static PyObject* ToPyObject(efd::UInt16 i_data)
    {
        return Py_BuildValue("H", i_data);
    }
};

/// Python trait handler for efd::SInt32.
template<>
struct PyTraits<efd::SInt32>
{
    static efd::SInt32 FromPyObject(PyObject* py)
    {
         return PyInt_AsLong(py);
    }

    static PyObject* ToPyObject(efd::SInt32 i_data)
    {
        return Py_BuildValue("i", i_data);
    }
};

/// Python trait handler for efd::UInt32.
template<>
struct PyTraits<efd::UInt32>
{
    static efd::UInt32 FromPyObject(PyObject* py)
    {
        return PyInt_AsUnsignedLongMask(py);
    }

    static PyObject* ToPyObject(efd::UInt32 i_data)
    {
        return Py_BuildValue("I", i_data);
    }
};

/// Python trait handler for efd::SInt64.
template<>
struct PyTraits<efd::SInt64>
{
    static efd::SInt64 FromPyObject(PyObject* py)
    {
        return PyLongOrInt_AsLongLong(py);
    }

    static PyObject* ToPyObject(efd::SInt64 i_data)
    {
        return Py_BuildValue("L", i_data);
    }
};

/// Python trait handler for efd::UInt64.
template<>
struct PyTraits<efd::UInt64>
{
    static efd::UInt64 FromPyObject(PyObject* py)
    {
        return PyLongOrInt_AsUnsignedLongLong(py);
    }

    static PyObject* ToPyObject(efd::UInt64 i_data)
    {
        return Py_BuildValue("K", i_data);
    }
};

/// Python trait handler for efd::UniversalID.
template<>
struct PyTraits<efd::UniversalID>
{
    static efd::UniversalID FromPyObject(PyObject* py)
    {
        return PyLongOrInt_AsUnsignedLongLong(py);
    }

    static PyObject* ToPyObject(efd::UniversalID i_data)
    {
        return Py_BuildValue("K", i_data.GetValue());
    }
};

/// Python trait handler for efd::Category.
template<>
struct PyTraits<efd::Category>
{
    static efd::Category FromPyObject(PyObject* py)
    {
        return PyLongOrInt_AsUnsignedLongLong(py);
    }

    static PyObject* ToPyObject(efd::Category i_data)
    {
        return Py_BuildValue("K", i_data.GetValue());
    }
};

/// Python trait handler for efd::EntityID.
template<>
struct PyTraits<egf::EntityID>
{
    static egf::EntityID FromPyObject(PyObject* py)
    {
        return PyLongOrInt_AsUnsignedLongLong(py);
    }

    static PyObject* ToPyObject(egf::EntityID i_data)
    {
        return Py_BuildValue("K", i_data.GetValue());
    }
};

/// Python trait handler for efd::EventID.
template<>
struct PyTraits<egf::EventID>
{
    static egf::EventID FromPyObject(PyObject* py)
    {
        return PyLongOrInt_AsUnsignedLongLong(py);
    }

    static PyObject* ToPyObject(egf::EventID i_data)
    {
        return Py_BuildValue("K", i_data.GetValue());
    }
};

/// Python trait handler for efd::Float32.
template<>
struct PyTraits<efd::Float32>
{
    static efd::Float32 FromPyObject(PyObject* py)
    {
        return (efd::Float32)PyFloat_AsDouble(py);
    }

    static PyObject* ToPyObject(efd::Float32 i_data)
    {
        return Py_BuildValue("f", i_data);
    }
};

/// Python trait handler for efd::Float64.
template<>
struct PyTraits<efd::Float64>
{
    static efd::Float64 FromPyObject(PyObject* py)
    {
        return PyFloat_AsDouble(py);
    }

    static PyObject* ToPyObject(efd::Float64 i_data)
    {
        return Py_BuildValue("d", i_data);
    }
};

/// Python trait handler for type efd::ParameterList*
template<>
struct PyTraits<efd::ParameterList*>
{
    static efd::ParameterList* FromPyObject(PyObject* py)
    {
        return egf::PyParameterList_AsParameterList(py);
    }
    static PyObject* ToPyObject(efd::ParameterList* i_data)
    {
        return egf::PyParameterList_Create(i_data);
    }
};

/// Python trait handler for efd::Point2.
template<>
struct PyTraits<efd::Point2>
{
    static efd::Point2 FromPyObject(PyObject* py)
    {
        efd::Point2 retVal;
        PyArg_ParseTuple(py, "ff", &retVal.x, &retVal.y);
        return retVal;
    }

    static PyObject* ToPyObject(efd::Point2 i_data)
    {
        return Py_BuildValue("ff", i_data.x, i_data.y);
    }
};

/// Python trait handler for efd::Point3.
template<>
struct PyTraits<efd::Point3>
{
    static efd::Point3 FromPyObject(PyObject* py)
    {
        efd::Point3 retVal;
        PyArg_ParseTuple(py, "fff", &retVal.x, &retVal.y, &retVal.z);

        return retVal;
    }

    static PyObject* ToPyObject(efd::Point3 i_data)
    {
        return Py_BuildValue("fff", i_data.x, i_data.y, i_data.z);
    }
};

/// Python trait handler for type efd::Color
template<>
struct PyTraits<efd::Color>
{
    static efd::Color FromPyObject(PyObject* py)
    {
        efd::Color retVal;
        PyArg_ParseTuple(py, "fff", &retVal.m_r, &retVal.m_g, &retVal.m_b);

        return retVal;
    }

    static PyObject* ToPyObject(const efd::Color& i_data)
    {
        return Py_BuildValue("fff", i_data.m_r, i_data.m_g, i_data.m_b);
    }
};

/// Python trait handler for type efd::ColorA
template<>
struct PyTraits<efd::ColorA>
{
    static efd::ColorA FromPyObject(PyObject* py)
    {
        efd::ColorA retVal;
        PyArg_ParseTuple(py, "ffff", &retVal.m_r, &retVal.m_g, &retVal.m_b, &retVal.m_a);

        return retVal;
    }

    static PyObject* ToPyObject(const efd::ColorA& i_data)
    {
        return Py_BuildValue("ffff", i_data.m_r, i_data.m_g, i_data.m_b, i_data.m_a);
    }
};

/// Python trait handler for efd::ID128.
template<>
struct PyTraits<efd::ID128>
{
    static efd::ID128 FromPyObject(PyObject* py)
    {
        efd::ID128 result;
        if (PyString_Check(py))
        {
            efd::utf8string str(PyString_AsString(py));
            EE_VERIFY(efd::ParseHelper<efd::ID128>::FromString(str, result));
        }

        return result;
    }

    static PyObject* ToPyObject(const efd::ID128& i_data)
    {
        efd::utf8string str;
        EE_VERIFY(efd::ParseHelper<efd::ID128>::ToString(i_data, str));

        return Py_BuildValue("s", str.c_str());
    }
};

/// Python trait handler for efd::Matrix3.
template<>
struct PyTraits<efd::Matrix3>
{
    static efd::Matrix3 FromPyObject(PyObject* py)
    {
        efd::Point3 col0;
        efd::Point3 col1;
        efd::Point3 col2;
        PyArg_ParseTuple(py, "(fff)(fff)(fff)",
            &col0.x, &col1.x, &col2.x,
            &col0.y, &col1.y, &col2.y,
            &col0.z, &col1.z, &col2.z);
        return efd::Matrix3(col0, col1, col2);
    }

    static PyObject* ToPyObject(const efd::Matrix3& i_data)
    {
        efd::Point3 row;
        i_data.GetRow(0, row);
        PyObject* py0 = Py_BuildValue("fff", row.x, row.y, row.z);

        i_data.GetRow(1, row);
        PyObject* py1 = Py_BuildValue("fff", row.x, row.y, row.z);

        i_data.GetRow(2, row);
        PyObject* py2 = Py_BuildValue("fff", row.x, row.y, row.z);

        // Use N to pass our reference to the constructed value
        return Py_BuildValue("NNN", py0, py1, py2);
    }
};

/// Python trait handler for efd::AssetID.
template<>
struct PyTraits<efd::AssetID>
{
    static efd::AssetID FromPyObject(PyObject* py)
    {
        if (PyString_Check(py))
        {
            return efd::AssetID(PyString_AsString(py));
        }
        return efd::AssetID::INVALID_ASSET_ID;
    }

    static PyObject* ToPyObject(const efd::AssetID& i_data)
    {
        return Py_BuildValue("s", i_data.c_str());
    }
};

/// Python trait handler for efd::utf8char_t.
template<>
struct PyTraits<efd::utf8char_t>
{
    static efd::utf8char_t FromPyObject(PyObject* py)
    {
        if (PyString_Check(py))
        {
            return efd::utf8char_t::from_stream(PyString_AsString(py));
        }
        return efd::utf8char_t();
    }

    static PyObject* ToPyObject(const efd::utf8char_t& i_data)
    {
        return Py_BuildValue("s", i_data.c_str());
    }
};

/// Python list to efd::list.
template<typename T>
efd::list<T> PyList_ToEutList(PyObject* py);

/// Python list from efd::list.
template<typename T>
PyObject* PyList_FromEutList(const efd::list<T>& l);

/// Python dictionary to efd::map.
template<typename KEY, typename DATA>
efd::map<KEY, DATA> PyDict_ToEutMap(PyObject* py);

/// Python dictionary from efd::map.
template<typename KEY, typename DATA>
PyObject* PyDict_FromEutMap(const efd::map<KEY, DATA>& m);

/**
    This method is a helper for building the python representation for built-in APIs that have
    multiple return values.

    It takes the built-ins return value, if any, and also appends an additional output parameter.
    The result is a PyTuple containing all the results.  Use this method in your SWIG typemap to
    simplify the process of building the result.  This approach avoids having to repeat this logic
    directly in your typename for each type that can be used as an output parameter.  For example,
    say you wanted to return two efd::Point3 parameters from a built-in with the following
    signature:

        @verbatim
        bool PointTest(efd::Point3 arg1, efd::Point3& out1, efd::Point3& out2);
        @endverbatim

    To do so, you may use the following SWIG typemap:

        @verbatim
        // The following statement in typename tells SWIG that any "Point3&" is treated as an
        // output parameter.
        // Note:  This approach will NOT work for in/out parameters, only for pure output
        // parameters.
        // The "(efd::Point3 temp)" causes a temporary variable of type Point3 to be declared.
        %typemap(in, numinputs=0) efd::Point3& (efd::Point3 temp)
        {
            // The following statement tells SWIG that the pointer to the parameter is the
            // temporary variable declared above.
            $1 = &temp;
        }

        // This typename tells SWIG how to place the C++ object returned by your built-in API into
        // the PyObject that is the binding method's result.
        %typemap(argout) efd::Point3&
        {
            // By using PyTraits, we may trivially convert the argument into a PyObject.  Remember
            // that our argument is a pointer to the local variable "temp" defined above, so we
            // need to pass the value pointed to (*$1 not just $1).  We cannot directly use the
            // "temp" variable, but must use $1.
            PyObject *o = bapiPython::PyTraits<efd::Point3>::ToPyObject(*$1);

            // The typemap doesn't know if the built-in API being bound has one or many results,
            // but luckily the AddPyObjectToTuple handles this situation for us.  So we may simply
            // call this method.
            $result = bapiPython::AddPyObjectToTuple($result, o);
        }
        @endverbatim

    @note There is a special case to keep in mind:  If the function you are binding returns a type
        that gets converted into a tuple (e.g., Point3), then any additional return values will
        get added to the returned tuple.  For example, if a function returned a Point3 but also
        had a Point3 as an output parameter, then it is impossible for the typename to tell this
        case apart from a function with multiple output parameters.  As a consequence, python will
        see the result as a single tuple with four elements.  The first three elements are the x,
        y, and z values from the returned Point3, and the fourth element will be another tuple
        containing the output parameter Point3.

    @param result The "result so far".  It could be NULL if we are binding a function with a void
        return type and this is the first output parameter.  It could be the function's return
        value converted into a PyObject.  It could also be a PyTuple resulting from a previous
        call to this method.
    @param objToAdd Current output parameter to be added to the result.  It can be any type of
        PyObject, including another container like list or tuple.  It will become the last element
        in a Tuple.

    @return Pointer to a PyObject, a tuple containing all the results, with an additional output
        parameter appended as the last element in the tuple.
 */
inline PyObject* AddPyObjectToPyTuple(PyObject* result, PyObject* objToAdd);

}   // End namespace bapiPython.

#include <egfPython/bapiPython.inl>

#endif  // EE_BAPIPYTHON_H
