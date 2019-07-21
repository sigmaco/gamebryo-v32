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
// SWIG Lua bindings for efd::ColorA.
//
%module ColorA;

%import <egfLua/MemObjectBindHelperLua.i>

%ignore *::GetAs(Color& kColor) const;
%ignore Color;
%ignore ColorA_UInt8;
%ignore efd::ColorA::GetAs(ColorA_UInt8& kColor) const;


namespace efd 
{
//
// ColorA has default arguments for each of the three constructor parameters. We need
// to explicitly override each instance to ensure SWIG uses the Emergent allocator.
//
%exception ColorA::ColorA(efd::Float32 r)
{
    result = EE_NEW efd::ColorA(arg1);
}

%exception ColorA::ColorA(efd::Float32 r, efd::Float32 g)
{
    result = EE_NEW efd::ColorA(arg1, arg2);
}

%exception ColorA::ColorA(efd::Float32 r, efd::Float32 g, efd::Float32 b)
{
    result = EE_NEW efd::ColorA(arg1, arg2, arg3);
}

%exception ColorA::ColorA(efd::Float32 r, efd::Float32 g, efd::Float32 b, efd::Float32 a)
{
    result = EE_NEW efd::ColorA(arg1, arg2, arg3, arg4);
}

//
// Add some additional helper functions to the class.
//
%extend ColorA
{
    // Copy constructor
    ColorA(const efd::ColorA& c)
    {
        return EE_NEW efd::ColorA(c.r, c.g, c.b, c.a);
    }
        
    //
    // SWIG cannot automatically generated operator[] but we can do it manually
    // by implementing __getitem__ and __setitem__
    //
    efd::Float32 __getitem__(efd::SInt32 index) const
    {
        // colorA[1]=red, colorA[2]=green, colorA[3]=blue, colorA[4]=alpha
        
        // Verify the index is valid.
        if (abs(index) > 4)
        {
            // If you hit this assert you attempted to index an object from Lua past the end
            // of the object's array bounds.
            EE_ASSERT(abs(index) > 4);
            return 0;
        }
        
        // If index is negative, start from the back.
        if (index < 0) index = 4 - index + 1;               
        
        if (index == 1) return $self->r;
        else if (index == 2) return $self->g;
        else if (index == 3) return $self->b;
        else return $self->a;
    }
    void __setitem__(efd::SInt32 index, efd::Float32 val)
    {
        // Verify the index is valid.
        if (abs(index) > 4)
        {
            // If you hit this assert you attempted to index an object from Lua past the end
            // of the object's array bounds.
            EE_ASSERT(abs(index) > 4);
            return;
        }
        
        // If index is negative, start from the back.
        if (index < 0) index = 4 - index + 1;               
    
        if (index == 1) $self->r = val;
        else if (index == 2) $self->g = val;
        else if (index == 3) $self->b = val;
        else if (index == 4) $self->a = val;
    }
} // extend

} // namespace


// Use the macro defined in MemObjectBindHelperLua.i to add additional class overrides,
// methods, and typemaps. This also sets up certain header includes required when
// wrapping the class.
EE_SWIG_DEFINE_MEMOBJECT_SWIG_CLASS(efd, ColorA)

// Add a __str__ function used in Lua when tostring is called on our object.
EE_SWIG_ADD_STR_FUNCTION(efd, ColorA, "ColorA(%.6f, %.6f, %.6f, %.6f)", $self->r, $self->g, $self->b, $self->a);

%{
#include <efd/Color.h>
%}

%include "efd/Color.h"
