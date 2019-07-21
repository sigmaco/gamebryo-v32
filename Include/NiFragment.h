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

#ifndef NIFRAGMENT_H
#define NIFRAGMENT_H

#include "NiFragmentMaterial.h"

/// @cond EMERGENT_INTERNAL
/**
    This function exposes functionality from NiFragmentMaterial to a new
    type of class to split the functionality of generating shaders up into
    logical groups. Such as, General operations, Lighting, Texture application
    etc.

    This class is currently for Emergent internal use only as the interface
    will change in the near future.
*/
class NIMAIN_ENTRY NiFragment: public NiObject
{
    NiDeclareRTTI;

public:
    /**
        Bring all the Shader generation relevant enums into a single place
        for consistency.
    */
    /// @see NiFragmentMaterial::Context
    typedef NiFragmentMaterial::Context Context;

    /// @see NiFragmentMaterial::ReturnCode
    typedef enum NiFragmentMaterial::ReturnCode ReturnCode;

    /// @see NiFragmentMaterial::RenderPassDescriptor
    typedef NiFragmentMaterial::RenderPassDescriptor RenderPassDescriptor;

    /// @see NiFragmentMaterial
    typedef NiFragmentMaterial EnumSource;

    /// @see NiFragmentMaterial::ObjectResourceOffset
    typedef NiFragmentMaterial::ObjectResourceOffset ObjectResourceOffset;

    /// @see NiFragmentMaterial::TextureMapSamplerType
    typedef enum NiFragmentMaterial::TextureMapSamplerType TextureMapSamplerType;

    /// Destructor routine
    virtual ~NiFragment();

    /**
        Set the owning material of this fragment, a side effect of this function
        is an increase of the version numbers for the using material based on
        the version of this fragment. This function must be called by owning
        material upon first instantiation. (i.e. in the constructor)

        @param pkMaterial The material that owns this fragment
    */
    void SetOwner(NiFragmentMaterial* pkMaterial);

    /**
        Function to fetch a specific fragment from the owning material. The 
        type of the pointer sent to pkFragment determines which
        fragment is fetched from the material. 
    */
    template <class T> static void Fetch(NiFragmentMaterial* pkMaterial, 
        T*& pkFragment);

protected:  

    /**
        Fetch any fragments that this fragment is dependant upon. Classes
        deriving from NiFragment should override this function to gather
        references to other NiFragmentClasses that it may require the use of. 
    */
    virtual void FetchDependencies();

	/**
        Find a material node from the material libraries that matches the input
        name and clone it for use in a shade-tree.

        @see NiFragmentMaterial::GetAttachableNodeFromLibrary
    */
    NiMaterialNode* GetAttachableNodeFromLibrary(const NiFixedString&
        kNodeName);

    /**
        Add a texture sampler to the uniforms for this shade-tree.

        @see NiFragmentMaterial::InsertTextureSampler
    */
    NiMaterialResource* InsertTextureSampler(
        Context& kContext,
        const NiFixedString& kMapName,
        TextureMapSamplerType eSamplerType,
        unsigned int uiOccurance,
        NiShaderAttributeDesc::ObjectType eObjectType =
            NiShaderAttributeDesc::OT_UNDEFINED);

    /**
        Add a NiShaderConstantMap::DefinedMappings shader constant to the
        uniforms for this shade-tree.

        @see NiFragmentMaterial::AddOutputPredefined
    */
    NiMaterialResource* AddOutputPredefined(NiMaterialNode* pkNode,
        NiShaderConstantMap::DefinedMappings eMapping,
        unsigned int uiNumRegisters = 1, unsigned int uiCount = 1,
        unsigned int uiExtraData = 0);

    /**
        Add a NiShaderConstantMap::ObjectMappings shader constant to the
        uniforms for this shade-tree.

        @see NiFragmentMaterial::AddOutputObject
    */
    NiMaterialResource* AddOutputObject(NiMaterialNode* pkNode,
        NiShaderConstantMap::ObjectMappings eMapping,
        NiShaderAttributeDesc::ObjectType eObjectType,
        unsigned int uiObjectCount, const char* pcVariableModifier = NULL,
        unsigned int uiCount = 1);

    /**
        Add a custom extra data shader constant to the uniforms for this
        shade-tree.

        @see NiFragmentMaterial::AddOutputAttribute
    */
    NiMaterialResource* AddOutputAttribute(NiMaterialNode* pkNode,
        const NiFixedString& kVariableName,
        NiShaderAttributeDesc::AttributeType eType,
        unsigned int uiCount = 1);

    /**
        Add a global attribute shader constant to the uniforms for this
        shade-tree.

        @see NiFragmentMaterial::AddOutputGlobal
    */
    NiMaterialResource* AddOutputGlobal(NiMaterialNode* pkNode,
        const NiFixedString& kVariableName,
        NiShaderAttributeDesc::AttributeType eType,
        unsigned int uiCount = 1);

    /**
        Utility method that searches through the object offsets for all render
        passes and finds the highest offset thus far for the given ObjectType.

        @see NiFragmentMaterial::GetHighestObjectOffset
    */
    static unsigned int GetHighestObjectOffset(
        NiShaderAttributeDesc::ObjectType eObjectType,
        RenderPassDescriptor* pkRenderPasses, unsigned int uiCount);

    /// Protected constructor
    NiFragment(NiUInt16 usVertexVersion,
        NiUInt16 usGeometryVersion,
        NiUInt16 usPixelVersion);

    /// Collection of fragment dependancies
    NiTPrimitiveSet<NiFragment*> m_kFragments;

    /// Collection of required material node libraries
    NiTObjectPtrSet<NiMaterialNodeLibraryPtr> m_kLibraries;

    /// Fragment Versioning system - Vertex shader version
    NiUInt16 m_usVertexVersion;

    /// Fragment Versioning system - Geometry shader version
    NiUInt16 m_usGeometryVersion;

    /// Fragment Versioning system - Pixel shader version
    NiUInt16 m_usPixelVersion;

    /// A reference to the material using this library
    NiFragmentMaterial* m_pkMaterial;
};

NiSmartPointer(NiFragment);
/// @endcond

#include "NiFragment.inl"

#endif  //#ifndef NIFRAGMENT_H
