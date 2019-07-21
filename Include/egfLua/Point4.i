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
// SWIG Lua bindings for efd::Point4.
//
%module "Point4"

%import "egfLua/ObjectBindHelperLua.i"
%import "egfLua/Point3.i"

//
// efd::Point4 is not a MemObject-based class. No need to override constructors / destructors
//
namespace efd
{

// Rename Point4(const Point3&) to avoid shadowing.
%rename(FromPoint3) Point4::Point4(const efd::Point3& kPt);

// Rename "Point4::operator() Point3" as SWIG doesn't do this automatically.
%rename(ToPoint3) Point4::operator efd::Point3;

// Make the arguments explicit for operator* and operator/
%rename(ScalarMultiply) Point4::operator*;
%rename(ScalarDivide) Point4::operator/;

}

//
// Special wrappers for the x,y,z,w attributes defined above. These values don't actually
// exist in Point4.h but we want to expose them directly in Lua.
%wrapper 
%{
    void efd_Point4_x_set(efd::Point4 *self, efd::Float32 v) 
    { 
        self->m_afPt[0] = v; 
    }
    efd::Float32 efd_Point4_x_get(efd::Point4 *self) 
    { 
        return self->m_afPt[0]; 
    }
    void efd_Point4_y_set(efd::Point4 *self, efd::Float32 v) 
    { 
        self->m_afPt[1] = v; 
    }
    efd::Float32 efd_Point4_y_get(efd::Point4 *self) 
    { 
        return self->m_afPt[1]; 
    }
    void efd_Point4_z_set(efd::Point4 *self, efd::Float32 v) 
    { 
        self->m_afPt[2] = v; 
    }
    efd::Float32 efd_Point4_z_get(efd::Point4 *self) 
    { 
        return self->m_afPt[2]; 
    }
    
    void efd_Point4_w_set(efd::Point4 *self, efd::Float32 v) 
    { 
        self->m_afPt[3] = v; 
    }
    efd::Float32 efd_Point4_w_get(efd::Point4 *self) 
    { 
        return self->m_afPt[3]; 
    }    
%}    


// efd::Point4 is a non-MemObject based class.
EE_SWIG_DEFINE_OBJECT_SWIG_CLASS(efd, Point4);

%include <efd/Point4.h>


// Add a __str__ function used in Lua when tostring is called on our object.
EE_SWIG_ADD_STR_FUNCTION(
    efd,
    Point4,
    "Point4(%.6f, %.6f, %.6f, %.6f)",
    $self->X(), $self->Y(), $self->Z(), $self->W());


namespace efd
{
// Add support for operator[]
%extend Point4
{
    //
    // SWIG cannot automatically generated operator[] but we can do it manually
    // by implementing __getitem__ and __setitem__
    //
    efd::Float32 __getitem__(efd::SInt32 index) const
    {
        // Point4[1]=x, Point4[2]=y, Point4[3]=z, Point4[4]=w
        
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
        
        if (index == 1) return $self->X();
        else if (index == 2) return $self->Y();
        else if (index == 3) return $self->Z();
        else return $self->W();
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
    
        if (index == 1) $self->SetX(val);
        else if (index == 2) $self->SetY(val);
        else if (index == 3) $self->SetZ(val);
        else $self->SetW(val);
    }
    
    efd::Float32 x;
    efd::Float32 y;
    efd::Float32 z;
    efd::Float32 w;
}

} // namespace efd


%{
#include <efd/Point4.h>
%}
