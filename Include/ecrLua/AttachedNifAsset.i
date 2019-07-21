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
// SWIG Lua bindings for ecr::AttachNifData.
//
%module AttachedNifAsset;

// Ignore various warnings
%warnfilter(302) ~AttachNifData;  // destructor redefinition
%warnfilter(401) AttachNifData;   // Nothing known about base class 'efd::IBase'

// Tell SWIG to ignore certain defines
// SWIG doesn't understand these defines, so make them empty.
#if defined(SWIG)

#undef EE_ECR_ENTRY
#define EE_ECR_ENTRY

#endif // SWIG

%import <egfLua/MemObjectBindHelperLua.i>

%rename(AttachedNifAsset) AttachNifData;


namespace ecr 
{
%exception AttachNifData::AttachNifData(
    const efd::utf8string& attachPoint, 
    const efd::AssetID& nifAsset)
{
    result = EE_NEW ecr::AttachNifData(*arg1, *arg2);
}

%extend AttachNifData
{
    efd::utf8string AttachPoint;
    efd::AssetID NifAsset;
    efd::Point3 Translation;
    efd::Point3 Rotation;
    efd::Float32 Scale;
}

} // namespace


// Use the macro defined in MemObjectBindHelperLua.i to add additional class overrides,
// methods, and typemaps. This also sets up certain header includes required when
// wrapping the class.
EE_SWIG_DEFINE_MEMOBJECT_SWIG_CLASS(ecr, AttachNifData)

// Clear out typemaps defined by the macros above as they don't apply.
%clear ecr::AttachNifData;
%clear ecr::AttachNifData&;
%clear ecr::AttachNifData& (ecr::AttachNifData tmp, void*userData=0);
%clear const ecr::AttachNifData& (ecr::AttachNifData tmp, void*userData=0);

%typemap(out) ecr::AttachNifData, ecr::AttachNifData&, const ecr::AttachNifData&
{
    ecr::AttachNifData* pResult = EE_NEW ecr::AttachNifData($result);
    SWIG_Lua_NewPointerObj(L, pResult, $1_descriptor, 1); SWIG_arg++;
}


// Add a __str__ function used in Lua when tostring is called on our object.
EE_SWIG_ADD_STR_FUNCTION(
    ecr, 
    AttachNifData, 
    "AttachedNifAsset(\n\tAttachPoint=%s,\n\tNifAsset=%s,\n\tTranslation=Point3(%.6f, %.6f, %.6f),\n\tRotation=Point3(%.6f, %.6f, %.6f),\n\tScale=%.6f)", 
        $self->GetAttachPoint().c_str(),
        $self->GetNifAsset().c_str(),
        $self->GetTranslation().x, $self->GetTranslation().y, $self->GetTranslation().z,
        $self->GetRotation().x, $self->GetRotation().y, $self->GetRotation().z,
        $self->GetScale())

%{
#include <ecr/AttachNifData.h>
%}

%include "ecr/AttachNifData.h"


//
// Special wrappers for the attributes defined above. These values don't actually
// exist as public members in AttachNifData but we want to expose them directly in Lua. 
//
%{
    void ecr_AttachNifData_AttachPoint_set(ecr::AttachNifData *self, const efd::utf8string& v) 
    { 
        self->SetAttachPoint(v);
    }
    efd::utf8string ecr_AttachNifData_AttachPoint_get(ecr::AttachNifData *self) 
    { 
        return self->GetAttachPoint(); 
    }
    void ecr_AttachNifData_NifAsset_set(ecr::AttachNifData *self, const efd::AssetID& v) 
    { 
        self->SetNifAsset(v);
    }
    efd::AssetID ecr_AttachNifData_NifAsset_get(ecr::AttachNifData *self) 
    { 
        return self->GetNifAsset(); 
    }
    void ecr_AttachNifData_Translation_set(ecr::AttachNifData *self, const efd::Point3& v) 
    { 
        self->SetTranslation(v);
    }
    efd::Point3 ecr_AttachNifData_Translation_get(ecr::AttachNifData *self) 
    { 
        return self->GetTranslation(); 
    }
    void ecr_AttachNifData_Rotation_set(ecr::AttachNifData *self, const efd::Point3& v) 
    { 
        self->SetRotation(v);
    }
    efd::Point3 ecr_AttachNifData_Rotation_get(ecr::AttachNifData *self) 
    { 
        return self->GetRotation(); 
    }
    void ecr_AttachNifData_Scale_set(ecr::AttachNifData *self, efd::Float32 v) 
    { 
        self->SetScale(v);
    }
    efd::Float32 ecr_AttachNifData_Scale_get(ecr::AttachNifData *self) 
    { 
        return self->GetScale();
    }    
%}    