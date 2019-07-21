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
// SWIG Lua bindings for efd::Point3.
//
%module Point3;

%import <egfLua/MemObjectBindHelperLua.i>


// Ignore SDM-related functions as they're not needed from script.
%ignore efd::Point3::_SDMInit;
%ignore efd::Point3::_SDMShutdown;

// We can't distinguish between a efd::Point3* pointer and an array of Point3 values.
// Ignore these functions for now. If we need them, reimplement them below.
%ignore efd::Point3::PointsPlusEqualFloatTimesPoints;
%ignore efd::Point3::WeightedPointsPlusWeightedPoints;
%ignore efd::Point3::UnitizeVectors;

// Make this an explicit function so it doesn't conflict with Point3::operator*
%rename(ScalarMultiply) operator*(efd::Float32 scalar, const Point3& pt);

// Use the macro defined in MemObjectBindHelperLua.i to add additional class overrides,
// methods, and typemaps. This also sets up certain header includes required when
// wrapping the class.
EE_SWIG_DEFINE_MEMOBJECT_SWIG_CLASS(efd, Point3)

//
//   Override the default versions of these functions generated by SWIG to ensure we use
//   the correct allocator. By default SWIG uses the standard allocator. We want SWIG to
//   use the Emergent allocator when creating instances of this type.
//
namespace efd
{
%exception Point3::Point3(efd::Float32, efd::Float32, efd::Float32)
{
   result = EE_NEW efd::Point3(arg1, arg2, arg3);
}

// Normally the default Point3 constructor leaves members uninitialized for performace reasons
// but when bound to swig we need the members initialized before they get used and we don't have
// as much control over this as C++ code typically does, so we replace the default constructor
// with one that initializes the parameters.
%exception Point3::Point3()
{
   result = EE_NEW efd::Point3(0.0f, 0.0f, 0.0f);
}

} // namespace efd


// Add a __str__ function used in Lua when tostring is called on our object.
EE_SWIG_ADD_STR_FUNCTION(efd, Point3, "Point3(%.6f, %.6f, %.6f)", $self->x, $self->y, $self->z);

// Add support for operator[]
EE_SWIG_ADD_ARRAY_ACCESSORS(efd, Point3, 3);


//
// Add some additional functionality to the SWIG generated Point3 wrapper.
//
%extend efd::Point3 {

    //
    // Construct a Point3 that is the addition of this vector with the scalar multiple
    // of the 'vector' parameter.
    //
    Point3 ScalarMultiplyAdd(const efd::Point3& vector, efd::Float32 multiple)
    {
        return *$self + vector * multiple;
    }

    //
    // Given a Point3 goal and an Point3 zero vector, calculate a vector from this Point3
    // position to the goal position. Returns the length of the direction vector followed
    // by the unitized version of the direction vector.
    //
    efd::Float32 CreateDirectionVectorTo(const efd::Point3& goal, efd::Point3& io_vector)
    {
        io_vector = goal - *$self;
        return io_vector.Unitize();
    }

    //
    //  Calculate the 2d (x,y) distance between this Point3 position and a Point3 goal position.
    //
    efd::Float32 Calculate2dDistanceTo(const efd::Point3& goal)
    {
        efd::Float32 distance = (goal.x - $self->x) * (goal.x - $self->x) +
                                (goal.y - $self->y) * (goal.y - $self->y);
        return sqrt(distance);
    }
}


%{
#include <efd/Point3.h>
%}

%include "efd/Point3.h"