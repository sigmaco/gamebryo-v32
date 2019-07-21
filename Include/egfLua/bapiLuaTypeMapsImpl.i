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

/* File : bapiLuaTypeMapsV2.i */

%import <egf/Warnings.i>
%import <egf/BasicTypes.i>
%import <efd/StdContainers.h>


#ifdef SWIGLUA

/**
    A helper define to map a basic type into and out of scripting. It provides mappings
    for (in), (out), (in) const &, and (argout) &. It also defines lists for the Type.

    (in) arguments are going from Lua to C
    (out) return values are going from C to Lua
    (argout) arguments are pass-by-reference arguments. They're getting read from Lua
             into an temp variable, that temp variable is passed to C, and the final value
             found in the temp variable pushed back to Lua.

    @param T The class being mapped
    @param SWIG_TYPECHECK The priority of the mapping, see SWIG documentation for details.
*/
%define EE_SWIG_LUA_TYPE_WRAP(T, SWIG_TYPECHECK)

// Don't let SWIG generate bogus SwigWrapper instances for this type.
%template() efd::list<T>;

// Const reference
%typemap(in, noblock=1) const T& (T tmp)
{
    // T const reference in
    if (!bapiLua::LuaTraits<T>::FromLuaObject(L, $argnum, tmp)) SWIG_fail;
    $1 = &tmp;
}
%typemap(out, noblock=1) const T&
{
    // T const reference: out
    SWIG_arg += bapiLua::LuaTraits<T>::ToLuaObject(L, *$1);
}
%typemap(argout, noblock=1) const T&
{
    // T const reference argout (no-op) $1
}
%typecheck(SWIG_TYPECHECK)
    const T&
{
   $1 = bapiLua::LuaTraits<T>::IsType(L, $input);
}


// Const pointer
%typemap(in, noblock=1) const T* (T tmp)
{
    // T const pointer in
    if (!bapiLua::LuaTraits<T>::FromLuaObject(L, $argnum, tmp)) SWIG_fail;
    $1 = &tmp;
}
%typemap(out, noblock=1) const T*
{
    // T const pointer: out
    SWIG_arg += bapiLua::LuaTraits<T>::ToLuaObject(L, *$1);
}
%typemap(argout, noblock=1) const T*
{
    // T const pointer argout (no-op) $1
}
%typecheck(SWIG_TYPECHECK)
    const T*
{
   $1 = bapiLua::LuaTraits<T>::IsType(L, $input);
}



// Pass by value
%typemap(in, noblock=1) T
{
    // T pass by value
    if (!bapiLua::LuaTraits<T>::FromLuaObject(L, $argnum, $1)) SWIG_fail;
}
// Return value
%typemap(out, noblock=1) T
{
    // T return value
    SWIG_arg += bapiLua::LuaTraits<T>::ToLuaObject(L, $1);
}
%typecheck(SWIG_TYPECHECK)
    T
{
   $1 = bapiLua::LuaTraits<T>::IsType(L, $input);
}



// Non-const pointer: an out parameter
%typemap(in, numinputs=0, noblock=1) T* (T temp)
{
    // T non-const pointer: in
    $1 = &temp;
}
%typemap(out, noblock=1) const T*
{
    // T non-const pointer: out
    SWIG_arg += bapiLua::LuaTraits<T>::ToLuaObject(L, *$1);
}
%typemap(argout, noblock=1) T*
{
    // T non-const pointer: argout
    SWIG_arg += bapiLua::LuaTraits<T>::ToLuaObject(L, *$1);
}
%typecheck(SWIG_TYPECHECK)
    T*
{
   $1 = bapiLua::LuaTraits<T>::IsType(L, $input);
}



// Non-const reference: an in/out parameter
%typemap(in, noblock=1) T& (T temp)
{
    // T non-const reference: in
    if (!bapiLua::LuaTraits<T>::FromLuaObject(L, $argnum, temp)) SWIG_fail;
    $1 = &temp;
}
%typemap(out, noblock=1) T&
{
    // T non-const reference: out
    SWIG_arg += bapiLua::LuaTraits<T>::ToLuaObject(L, *$1);
}
%typemap(argout, noblock=1) T&
{
    // T non-const reference: argout
    SWIG_arg += bapiLua::LuaTraits<T>::ToLuaObject(L, *$1);
}
%typecheck(SWIG_TYPECHECK)
    T&
{
   $1 = bapiLua::LuaTraits<T>::IsType(L, $input);
}



//  efd::List helpers

// efd::List const reference in
%typemap(in, noblock=1) const efd::list<T>& (efd::list<T> tmp)
{
    // efd::list<T> const reference in
    if (!bapiLua::LuaList_ToEutList<T>(L, $argnum, tmp)) SWIG_fail;
    $1 = &tmp;
}
%typemap(out, noblock=1) const efd::list<T>&
{
    // efd::list<T> const reference: out
    SWIG_arg += bapiLua::LuaList_FromEutList<T>(L, *$1);
}
%typemap(argout, noblock=1) const efd::list<T>&
{
    // efd::list<T> const reference argout (no-op) $1
}
%typecheck(SWIG_TYPECHECK_LIST)
    const efd::list<T>&
{
   $1 = lua_istable(L, $input);
}


// efd::List const pointer in
%typemap(in, noblock=1) const efd::list<T>* (efd::list<T> tmp)
{
    // efd::list<T> const pointer in
    if (!bapiLua::LuaList_ToEutList<T>(L, $argnum, tmp)) SWIG_fail;
    $1 = &tmp;
}
%typemap(out, noblock=1) const efd::list<T>*
{
    // efd::list<T> const pointer: out
    SWIG_arg += bapiLua::LuaList_FromEutList<T>(L, *$1);
}
%typemap(argout, noblock=1) const efd::list<T>*
{
    // efd::list<T> const pointer argout (no-op) $1
}
%typecheck(SWIG_TYPECHECK_LIST)
    const efd::list<T>*
{
   $1 = lua_istable(L, $input);
}


// pass by value
%typemap(in, noblock=1) efd::list<T>
{
    // efd::list<T> pass by value
    if (!bapiLua::LuaList_ToEutList<T>(L, $argnum, $1)) SWIG_fail;
}
// return value
%typemap(out, noblock=1) efd::list<T>
{
    // efd::list<T> return value
    SWIG_arg += bapiLua::LuaList_FromEutList<T>(L, $1);
}
%typecheck(SWIG_TYPECHECK_LIST)
    efd::list<T>
{
   $1 = lua_istable(L, $input);
}



// non-const pointer: an out parameter
%typemap(in, numinputs=0, noblock=1) efd::list<T>* (efd::list<T> temp)
{
    // efd::list<T> non-const pointer: in
    $1 = &temp;
}
%typemap(out, noblock=1) efd::list<T>*
{
    // efd::list<T> non-const pointer: out
    SWIG_arg += bapiLua::LuaList_FromEutList<T>(L, *$1);
}
%typemap(argout, noblock=1) efd::list<T>*
{
    // efd::list<T> non-const pointer: argout
    SWIG_arg += bapiLua::LuaList_FromEutList<T>(L, *$1);
}
%typecheck(SWIG_TYPECHECK_LIST)
    efd::list<T>*
{
   $1 = lua_istable(L, $input);
}



// non-const reference: an in/out parameter
%typemap(in, noblock=1) efd::list<T>& (efd::list<T> temp)
{
    // efd::list<T> non-const reference: in
    if (!bapiLua::LuaList_ToEutList<T>(L, $argnum, temp)) SWIG_fail;
    $1 = &temp;
}
%typemap(out, noblock=1) efd::list<T>&
{
    // efd::list<T> non-const reference: out
    SWIG_arg += bapiLua::LuaList_FromEutList<T>(L, *$1);
}
%typemap(argout, noblock=1) efd::list<T>&
{
    // efd::list<T> non-const reference: argout
    SWIG_arg += bapiLua::LuaList_FromEutList<T>(L, *$1);
}
%typecheck(SWIG_TYPECHECK_LIST)
    efd::list<T>&
{
   $1 = lua_istable(L, $input);
}

%enddef  // EE_SWIG_LUA_TYPE_WRAP



/**
    A helper macro that defines the binding for efd::maps into and out of Python.
 */
%define EE_SWIG_LUA_MAP_WRAP(KeyType, ValueType)

// Don't let SWIG generate bogus SwigWrapper instances for this type.
%template() efd::map<KeyType, ValueType>;

// const reference
%typemap(in, noblock=1) const efd::map<KeyType, ValueType>& (efd::map<KeyType, ValueType> tmp)
{
    // efd::map const reference
    if (!bapiLua::LuaTable_ToEutMap<KeyType, ValueType>(L, $argnum, tmp)) SWIG_fail;
    $1 = &tmp;
}
%typecheck(SWIG_TYPECHECK_MAP)
    const efd::map<KeyType, ValueType>&
{
   $1 = lua_istable(L, $input);
}


// pass by value
%typemap(in, noblock=1) efd::map<KeyType, ValueType>
{
    // efd::map pass by value
    if (!bapiLua::LuaTable_ToEutMap<KeyType, ValueType>(L, $input, $1)) SWIG_fail;
}
%typecheck(SWIG_TYPECHECK_MAP)
    efd::map<KeyType, ValueType>&
{
   $1 = lua_istable(L, $input);
}


// return value
%typemap(out, noblock=1) efd::map<KeyType, ValueType>
{
    // efd::map return value
    $result = bapiLua::LuaTable_FromEutMap<KeyType, ValueType>(L, $1);
}
%typecheck(SWIG_TYPECHECK_MAP)
    efd::map<KeyType, ValueType>
{
   $1 = lua_istable(L, $input);
}

%enddef  // EFD_MAP_WRAP



// define bindings for all of our supported data types.
EE_SWIG_LUA_TYPE_WRAP(efd::Bool, SWIG_TYPECHECK_BOOL)
EE_SWIG_LUA_TYPE_WRAP(efd::Char, SWIG_TYPECHECK_CHAR)
EE_SWIG_LUA_TYPE_WRAP(efd::SInt8, SWIG_TYPECHECK_INT8)
EE_SWIG_LUA_TYPE_WRAP(efd::UInt8, SWIG_TYPECHECK_UINT8)
EE_SWIG_LUA_TYPE_WRAP(efd::SInt16, SWIG_TYPECHECK_INT16)
EE_SWIG_LUA_TYPE_WRAP(efd::UInt16, SWIG_TYPECHECK_UINT16)
EE_SWIG_LUA_TYPE_WRAP(efd::SInt32, SWIG_TYPECHECK_INT32)
EE_SWIG_LUA_TYPE_WRAP(efd::UInt32, SWIG_TYPECHECK_UINT32)
EE_SWIG_LUA_TYPE_WRAP(efd::SInt64, SWIG_TYPECHECK_INT64)
EE_SWIG_LUA_TYPE_WRAP(efd::UInt64, SWIG_TYPECHECK_UINT64)
EE_SWIG_LUA_TYPE_WRAP(efd::Float32, SWIG_TYPECHECK_FLOAT)
EE_SWIG_LUA_TYPE_WRAP(efd::Float64, SWIG_TYPECHECK_DOUBLE)
EE_SWIG_LUA_TYPE_WRAP(efd::utf8string, SWIG_TYPECHECK_STRING)
EE_SWIG_LUA_TYPE_WRAP(efd::Category, SWIG_TYPECHECK_UINT64)
EE_SWIG_LUA_TYPE_WRAP(efd::Color, SWIG_TYPECHECK_FLOAT_ARRAY)
EE_SWIG_LUA_TYPE_WRAP(efd::ColorA, SWIG_TYPECHECK_FLOAT_ARRAY)
EE_SWIG_LUA_TYPE_WRAP(efd::Matrix3, SWIG_TYPECHECK_FLOAT_ARRAY)
EE_SWIG_LUA_TYPE_WRAP(efd::Point2, SWIG_TYPECHECK_FLOAT_ARRAY)
EE_SWIG_LUA_TYPE_WRAP(efd::Point3, SWIG_TYPECHECK_FLOAT_ARRAY)
EE_SWIG_LUA_TYPE_WRAP(efd::Point4, SWIG_TYPECHECK_FLOAT_ARRAY)
EE_SWIG_LUA_TYPE_WRAP(efd::Quaternion, SWIG_TYPECHECK_FLOAT_ARRAY)
EE_SWIG_LUA_TYPE_WRAP(efd::ID128, SWIG_TYPECHECK_STRING)
EE_SWIG_LUA_TYPE_WRAP(efd::AssetID, SWIG_TYPECHECK_STRING)
EE_SWIG_LUA_TYPE_WRAP(efd::TimeType, SWIG_TYPECHECK_DOUBLE)

EE_SWIG_LUA_TYPE_WRAP(egf::EntityID, SWIG_TYPECHECK_POINTER)
EE_SWIG_LUA_TYPE_WRAP(egf::EventID, SWIG_TYPECHECK_UINT64)
EE_SWIG_LUA_TYPE_WRAP(egf::PropertyID, SWIG_TYPECHECK_UINT32)


// Create typemaps for efd::maps containing primatives. We won't attempt to enumerate all the
// possible combinations here. If you need support for another mapping, add it here.
EE_SWIG_LUA_MAP_WRAP(egf::UInt32, egf::UInt32)
EE_SWIG_LUA_MAP_WRAP(efd::UInt32, efd::utf8string)
EE_SWIG_LUA_MAP_WRAP(efd::utf8string, efd::UInt32)
EE_SWIG_LUA_MAP_WRAP(efd::utf8string, efd::utf8string)
EE_SWIG_LUA_MAP_WRAP(egf::EntityID, efd::utf8string)
EE_SWIG_LUA_MAP_WRAP(efd::utf8string, egf:EntityID)

// Special handling for const char*, so that Lua nil can be passed safely
%typemap(in, noblock=1) const char* (const efd::Char* tmp)
{
    if (!bapiLua::LuaTraits<efd::Char*>::FromLuaObject(L, $argnum, tmp)) SWIG_fail;
    $1 = const_cast<char *>(tmp);
}
%typecheck(SWIG_TYPECHECK_STRING)
    const char*
{
   $1 = bapiLua::LuaTraits<efd::Char*>::IsType(L, $input);
}


//------------------------------------------------------------------------------------------------
// ParameterList special handling:
//------------------------------------------------------------------------------------------------
// Running efd::ParameterList* through the default EE_SWIG_LUA_TYPE_WRAP define should give us:
//    |---------------------|---------------|------------------------------------------------------
//    | typename:           | treated as:   | notes:
//    |---------------------|---------------|------------------------------------------------------
//    | ParameterList*         | Input         |
//    | const ParameterList*&  | Input         |
//    | const ParameterList**  | Input         | Pointer must NOT be NULL
//    | ParameterList**        | Output        | Pointer must NOT be NULL
//    | ParameterList*&        | Input-Output  |
//    |---------------------|---------------|------------------------------------------------------
EE_SWIG_LUA_TYPE_WRAP(efd::ParameterList*, SWIG_TYPECHECK_POINTER)

// In addition to those types, we also want to handle a few more:
//    |---------------------|---------------|------------------------------------------------------
//    | typename:           | treated as:   | notes:
//    |---------------------|---------------|------------------------------------------------------
//    | const ParameterList&   | Input         |
//    | ParameterList&         | Input-Output  |
//    |---------------------|---------------|------------------------------------------------------

// const reference: an in parameter
%typemap(in, noblock=1) const efd::ParameterList&
{
    // ParameterList const reference in
    if (!bapiLua::LuaTraits<efd::ParameterList*>::FromLuaObject(L, $argnum, $1)) SWIG_fail;
}
%typemap(argout, noblock=1) const efd::ParameterList&
{
    // ParameterList const reference argout (no-op) $1
}

// Non-const reference: an in/out parameter
%typemap(in, noblock=1) efd::ParameterList&
{
    // efd::ParameterList non-const reference: in
    if (!bapiLua::LuaTraits<efd::ParameterList*>::FromLuaObject(L, $argnum, $1)) SWIG_fail;
}
%typemap(argout, noblock=1) efd::ParameterList&
{
    // efd::ParameterList non-const reference: out
    SWIG_arg += bapiLua::LuaTraits<efd::ParameterList*>::ToLuaObject(L, $1);
}

#endif // SWIGLUA

// end Lua specific
//////////////////////////////////////////////////////////////////////
