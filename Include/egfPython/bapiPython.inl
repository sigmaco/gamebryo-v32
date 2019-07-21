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

namespace bapiPython
{

//------------------------------------------------------------------------------------------------
inline efd::SInt64 PyLongOrInt_AsLongLong(PyObject* py)
{
    efd::SInt64 result;

    if (PyLong_Check(py))
        result = PyLong_AsLongLong(py);
    else
        result = PyInt_AsLong(py);

    return result;
}
//------------------------------------------------------------------------------------------------
inline efd::UInt64 PyLongOrInt_AsUnsignedLongLong(PyObject* py)
{
    efd::UInt64 result;

    if (PyLong_Check(py))
        result = PyLong_AsUnsignedLongLong(py);
    else
        result = PyInt_AsUnsignedLongMask(py);

    return result;
}
//------------------------------------------------------------------------------------------------
template<typename T>
inline efd::list<T> PyList_ToEutList(PyObject* py)
{
    efd::list<T> ret;
    if (PyList_Check(py))
    {
        size_t size = PyList_Size(py);
        for (size_t i = 0; i < size; ++i)
        {
            PyObject* py = PyList_GetItem(py, i);
            ret.append(PyTraits<T>::FromPyObject(py));
        }
    }

    return ret;
}
//------------------------------------------------------------------------------------------------
template<typename T>
inline PyObject* PyList_FromEutList(const efd::list<T>& l)
{
    PyObject* pList = PyList_New(0);
    for (typename efd::list<T>::const_iterator iter = l.begin(); iter != l.end(); ++iter)
    {
        PyObject* pItem = PyTraits<T>::ToPyObject(*iter);
        PyList_Append(pList, pItem);
    }

    return pList;
}
//------------------------------------------------------------------------------------------------
template<typename KEY, typename DATA>
inline efd::map<KEY, DATA> PyDict_ToEutMap(PyObject* py)
{
    efd::map<KEY, DATA> ret;
    if (PyDict_Check(py))
    {
        PyObject *key;
        PyObject *value;
        size_t pos = 0;

        while (PyDict_Next(py, &pos, &key, &value))
        {
            ret[ PyTraits<KEY>::FromPyObject(key) ] = PyTraits<DATA>::FromPyObject(value);
        }
    }

    return ret;
}
//------------------------------------------------------------------------------------------------
template<typename KEY, typename DATA>
inline PyObject* PyDict_FromEutMap(const efd::map<KEY, DATA>& m)
{
    PyObject* pDict = PyDict_New(m.size());
    for (typename efd::map<KEY, DATA>::const_iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        PyObject* pKey = PyTraits<KEY>::ToPyObject(iter->first);
        PyObject* pData = PyTraits<DATA>::ToPyObject(iter->second);
        PyDict_SetItem(pDict, pKey, pData);
    }

    return pDict;
}
//------------------------------------------------------------------------------------------------
inline PyObject* AddPyObjectToPyTuple(PyObject* result, PyObject* objToAdd)
{
    if ((!result) || (result == Py_None))
    {
        result = objToAdd;
    }
    else
    {
        if (!PyTuple_Check(result))
        {
            PyObject *oringalResult = result;
            result = PyTuple_New(2);
            PyTuple_SetItem(result, 0, oringalResult);
            PyTuple_SetItem(result, 1, objToAdd);
            Py_XDECREF(oringalResult);
            Py_XDECREF(objToAdd);
        }
        else
        {
            // Resize to fit the new item:
            Py_ssize_t size = PyTuple_Size(result);
            _PyTuple_Resize(&result, size+1);

            // Set new item as the last element:
            PyTuple_SetItem(result, size, objToAdd);
            Py_XDECREF(objToAdd);
        }
    }

    return result;
}
//------------------------------------------------------------------------------------------------

}   // End namespace bapiPython.
