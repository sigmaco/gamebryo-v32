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

//
// Macros to help when binding non MemObject-based classes into SWIG. These macros
// attempt to make the binding process easier.
//

// Avoid generating unnecessary wrappers when creating member variable accessor functions.
%naturalvar;

%import "egf/Warnings.i"
%import "efd/RTLib.h"
%import "efd/StdContainers.h"
%import "egfLua/bapiLuaTypeMapsImpl.i"

//
// Define SWIG bindings, overrides, and typemaps to encapsulate a non-efd::MemObject based
// class (For example efd::Point4). This macro introduces a 'Clone' function to
// perform a deep copy of an object. And it overrides typemaps for certain SWIG generated
// functions that use non-const pointers to 'this'.
//
// @param CLASSNAME The fully qualified class name. For example, efd::Color.
//
%define EE_SWIG_DEFINE_OBJECT_SWIG_CLASS(NAMESPACE, CLASSNAME)

// SWIG doesn't understand these defines, so make them empty.
#if defined(SWIG)

#undef EE_RESTRICT
#define EE_RESTRICT

#undef EE_EFD_ENTRY
#define EE_EFD_ENTRY

#endif // SWIG

%{
#include <egfLua/bapiLua.h>
%}

namespace NAMESPACE
{

%extend CLASSNAME 
{    
    //
    // We're not allowed to overload operator=. Instead we provide a clone method.
    //
    CLASSNAME Clone() const
    {
        return NAMESPACE::CLASSNAME(*$self);
    }    
}

//
// Add typemaps for the 'self' and 'ary' named pointers. SWIG generates code for functions
// that take no arguments as receiving a non-const pointer to 'self'. It will always push the
// argument on the stack so we can't use our default efd::T* typemap, which assumes no arguments.
//
%typemap(in,noblock=1) CLASSNAME const *self, CLASSNAME* ary
{
   // CLASSNAME* self input
   if (!SWIG_IsOK(SWIG_ConvertPtr(L,$argnum,(void**)&arg$argnum,$1_descriptor,1)))
   {   
        efd::utf8string tMsg("SWIGTYPE_p_");
        tMsg += "NAMESPACE";
        tMsg += "__";
        tMsg += "CLASSNAME";
        
        SWIG_fail_ptr(tMsg.c_str(),1,$1_descriptor);
   }
}
%typemap(in,noblock=1) CLASSNAME *self = CLASSNAME const *self;

// 
// No need to return self.
//
%typemap(argout,noblock=1) CLASSNAME const *self, CLASSNAME const *ary
{
    // CLASSNAME self argout -- noop
}

%typemap(argout,noblock=1) CLASSNAME *self = CLASSNAME const *self;
%typemap(argout,noblock=1) CLASSNAME *ary = CLASSNAME const *ary;

} // namespace


//
// Change the default typemap for arguments passed by reference. We want to
// expose the underlying value directly.
//
//
// Change the default typemap for arguments passed by reference. We want to
// expose the underlying value directly.
//
%typemap(in,noblock=1) NAMESPACE::CLASSNAME& (NAMESPACE::CLASSNAME tmp, void* userData=0), 
             const NAMESPACE::CLASSNAME& (NAMESPACE::CLASSNAME tmp, void* userData=0)
{
    // NAMESPACE::CLASSNAME reference: in
    if (lua_isuserdata(L, $argnum))
    {
        userData = lua_touserdata(L, $argnum);
            
        if (!SWIG_IsOK(SWIG_ConvertPtr(L,$argnum,(void**)&$1,$1_descriptor,1)))
        {
            efd::utf8string tMsg("SWIGTYPE_p_");
            tMsg += "NAMESPACE";
            tMsg += "__";
            tMsg += "CLASSNAME";
            
            SWIG_fail_ptr(tMsg.c_str(),1,$1_descriptor);
        }
    }
    else if (lua_istable(L, $argnum))
    {
        if (!bapiLua::LuaTraits<NAMESPACE::CLASSNAME>::FromLuaObject(L, $argnum, tmp)) SWIG_fail;
        $1 = &tmp;
    }
    else
    {
        SWIG_fail;
    }
}

%typemap(out,noblock=1) NAMESPACE::CLASSNAME&, const NAMESPACE::CLASSNAME&
{
    // NAMESPACE::CLASSNAME reference: out
    SWIG_arg += bapiLua::LuaTraits<NAMESPACE::CLASSNAME>::ToLuaObject(L, *$1);
}

%typemap(argout,noblock=1) NAMESPACE::CLASSNAME&
{
    // NAMESPACE::CLASSNAME reference: argout
    if (userData$argnum)
    {
        // Push a copy of our userdata back on the stack.    
        lua_pushvalue(L, $argnum);
        SWIG_arg++;
    }
    else
    {
        // Push a copy of the argument back on the stack.
        SWIG_arg += bapiLua::LuaTraits<NAMESPACE::CLASSNAME>::ToLuaObject(L, *$1);    
    }
}

%typemap(argout,noblock=1) const NAMESPACE::CLASSNAME&
{
    // NAMESPACE::CLASSNAME const reference argout -- noop
}

%typemap(out,noblock=1) NAMESPACE::CLASSNAME
{
    // NAMESPACE::CLASSNAME return by value
    SWIG_arg += bapiLua::LuaTraits<NAMESPACE::CLASSNAME>::ToLuaObject(L, $1);
}

%enddef


//
// Generate array access functions. This wraps operator[] in Lua __getitem__ and __setitem__
// metamethods.
//
// @param CLASSNAME The fully qualified class name.
//
%define EE_SWIG_ADD_ARRAY_ACCESSORS(NAMESPACE, CLASSNAME, ARRAYSIZE)
namespace NAMESPACE
{
%extend CLASSNAME 
{
    //
    // SWIG cannot automatically generated operator[] but we can do it manually
    // by implementing __getitem__ and __setitem__
    //
    efd::Float32 __getitem__(efd::SInt32 index) const
    {
        // Verify the index is valid.
        if (abs(index) > ARRAYSIZE)
        {
            // If you hit this assert you attempted to index an object from Lua past the end
            // of the object's array bounds.
            EE_ASSERT(abs(index) > ARRAYSIZE);
            return 0;
        }
    
        // If index is negative, start from the back.
        if (index < 0) index = ARRAYSIZE - index + 1;
            
        // substract 1 from index to conform to Lua standards where indexes start at 1.
        return $self->operator[](index-1);
    }
    void __setitem__(efd::SInt32 index, efd::Float32 val)
    {
        // Verify the index is valid.
        if (abs(index) > ARRAYSIZE)
        {
            // If you hit this assert you attempted to index an object from Lua past the end
            // of the object's array bounds.
            EE_ASSERT(abs(index) > ARRAYSIZE);
            return;            
        }
    
        // If index is negative, start from the back.
        if (index < 0) index = ARRAYSIZE - index + 1;
    
        // substract 1 from index to conform to Lua standards where indexes start at 1.
        $self->operator[](index-1) = val;
    }
}
} // namespace

%enddef


//
// Extend a class to include a __str__ function, which is used in Lua when tostring is called.
//
// @param CLASSNAME The fully qualified class name.
// @param FORMAT_STRING The format string used to pretty print instances of the class.
// @param ARGS Arguments to the format string, in printf format. These can include references
//      to $self, which represents a 'this' pointer in SWIG.
//      
//
// Example:
//      ADD_STR_FUNCTION(efd::Point3, "Point3(%.6f, %.6f, %.6f)", $self->x, $self->y, $self->z)
//
// This macro will tell SWIG to generate code like this:
//      sprintf(buffer, "Point3(%.6f, %.6f, %.6f)", this->x, this->y, this-z);
//
%define EE_SWIG_ADD_STR_FUNCTION(NAMESPACE, CLASSNAME, FORMAT_STRING, ARGS...)

namespace NAMESPACE 
{
%extend CLASSNAME {
    
    // 
    // Support for Lua tostring - pretty print a CLASSNAME value.
    //
    const char* __str__() const
    {
        static char buffer[100];
        sprintf(buffer, FORMAT_STRING, ARGS);
        return buffer;
    }
}

} // namespace 

%enddef 
