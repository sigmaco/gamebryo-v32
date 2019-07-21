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
// Macros to help when binding efd::MemObject-based classes into SWIG. These macros
// attempt to make the binding process easier.
//

// Avoid generating unnecessary wrappers when creating member variable accessor functions.
%naturalvar;

%import "egf/Warnings.i"
%import "efd/RTLib.h"
%import "efd/StdContainers.h"
%import "egfLua/ObjectBindHelperLua.i"


//
// Define SWIG bindings, overrides, and typemaps to encapsulate an efd::MemObject based
// class (For example efd::Point2). This macro overrides the default SWIG generated
// default constructor and destructor wrappers. It introduces a 'Clone' function to
// perform a deep copy of an object. And it overrides typemaps for certain SWIG generated
// functions that use non-const pointers to 'this'.
//
// @param CLASSNAME The fully qualified class name. For example, efd::Color.
//
%define EE_SWIG_DEFINE_MEMOBJECT_SWIG_CLASS(NAMESPACE, CLASSNAME)

EE_SWIG_DEFINE_OBJECT_SWIG_CLASS(NAMESPACE, CLASSNAME)

namespace NAMESPACE
{

//
// Override the default constructor. This should always be used as the SWIG-generated
// wrapper uses the wrong allocator.
//
%exception CLASSNAME::CLASSNAME()
{
    result = EE_NEW NAMESPACE::CLASSNAME();
}

//
// Copy constructor.
//
%exception CLASSNAME::CLASSNAME(const NAMESPACE::CLASSNAME&)
{
    result = EE_NEW NAMESPACE::CLASSNAME(arg1);
}

%extend CLASSNAME 
{
    //
    // Override the destructor so we use the correct deallocator.
    //
    ~CLASSNAME() { EE_DELETE $self; }    
}

} // namespace

%enddef
