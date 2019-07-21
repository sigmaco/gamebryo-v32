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

#ifndef NIFRAGMENTOPERATIONS_H
#define NIFRAGMENTOPERATIONS_H

#include "NiFragment.h"

/**
    This class is another helper NiFragment class used to provide basic vector operation
    functionality to any materials that reference it. 
*/
class NITERRAIN_ENTRY NiFragmentOperations : public NiFragment
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:

    /// Constructor
    NiFragmentOperations();

    /// An enum storing the set of shader versions for this material
    enum ShaderVersion
    {
        /// The current vertex version. Adjusting this invalidates the vertex
        /// cache and forces new shaders to be generated.
        VERTEX_VERSION = 1,
        /// The current geometry version. Adjusting this invalidates the
        /// geometry cache and forces new shaders to be generated.
        GEOMETRY_VERSION = 0,
        /// The current pixel version. Adjusting this invalidates the pixel
        /// cache and forces new shaders to be generated.
        PIXEL_VERSION = 1,
    };

    /**
        This method controls the application of alpha testing to the pixel
        shade tree. This is currently only used for D3D10 and D3D11 shade trees.
    */
    bool HandleAlphaTest(Context& kContext,
        bool bAlphaTest,
        NiMaterialResource* pkAlphaTestInput);

    /**
        This is a utility method to add material nodes to normalize a float2,
        float3, or float4 vector.
    */
    bool NormalizeVector(Context& kContext,
        NiMaterialResource*& pkVector);

    /**
        Convert a color to it's luminance value (useful for converting to greyscale)
    */
    bool ColorToLuminance(Context& kContext, NiMaterialResource* pkColor, 
        NiMaterialResource*& pkLuminance);

    /**
        Extract a specific channel from a vector
    */
    bool ExtractChannel(Context& kContext, NiMaterialResource* pkVector,
        efd::UInt32 uiChannel, NiMaterialResource*& pkOutput);

    /**
        This is a utility method to add material nodes to add float, float2,
        float3, or float4 vectors.
    */
    bool AddVector(Context& kContext,
        NiMaterialResource* pkVector1, NiMaterialResource* pkVector2,
        NiMaterialResource*& pkValue);

    /**
        This is a utility method to add material nodes to multiply float,
        float2, float3, or float4 vectors.
    */
    bool MultiplyVector(Context& kContext,
        NiMaterialResource* pkVector1, NiMaterialResource* pkVector2,
        NiMaterialResource*& pkValue);

    /**
        This is a utility method to cross product two vectors of float3 format. 
    */
    bool CrossVector(Context& kContext,
        NiMaterialResource* pkVector1, NiMaterialResource* pkVector2,
        NiMaterialResource*& pkValue);

    /**
        This is a utility method to add material nodes to multiply/add float3
        vectors.
    */
    bool MultiplyAddVector(Context& kContext,
        NiMaterialResource* pkVector1, NiMaterialResource* pkVector2,
        NiMaterialResource* pkVector3, NiMaterialResource*& pkValue);

    /**
        This is a utility method to add material nodes to linearly interpolate
        float, float2, float3, or float4 vectors.
    */
    bool LerpVector(Context& kContext,
        NiMaterialResource* pkVector1, NiMaterialResource* pkVector2,
        NiMaterialResource* pkLerpAmount, NiMaterialResource*& pkValue);

    /**
        This is a utility method to add material nodes to multiply a float,
        float2, float3, or float4 vector by a single float.
    */
    bool ScaleVector(Context& kContext,
        NiMaterialResource* pkVector, NiMaterialResource* pkScale,
        NiMaterialResource*& pkValue);

    /**
        This is a utility method to add material nodes to saturate float,
        float2, float3, or float4 vector.
    */
    bool SaturateVector(Context& kContext,
        NiMaterialResource* pkVector, NiMaterialResource*& pkValue);

    /**
        This is a utility method to add material nodes to multiply a float3
        vector by the sum of another float3 vector and a scalar.
    */
    bool MultiplyScalarSatAddVector(
        Context& kContext, NiMaterialResource* pkVector1,
        NiMaterialResource* pkVector2, NiMaterialResource* pkScale,
        NiMaterialResource*& pkValue);

    /**
        This method will add material nodes to split a float4 vector into
        float3 and float vectors.
    */
    bool SplitColorAndOpacity(Context& kContext,
        NiMaterialResource* pkColorAndOpacity, NiMaterialResource*& pkColor,
        NiMaterialResource*& pkOpacity);

    /**
        This method will add material nodes to split a float4 vector into
        float3 and float vectors.
    */
    bool SplitRGBA(Context& kContext,
        NiMaterialResource* pkColorAndOpacity, NiMaterialResource*& pkRed,
        NiMaterialResource*& pkGreen, NiMaterialResource*& pkBlue,
        NiMaterialResource*& pkAlpha);

    /**
        This utility method will invoke conversion functions when binding
        resources with common float count mismatches, i.e. binding a float4
        to a float3 truncates the fourth float value. When the resources match
        types, a normal bind occurs.
    */
    bool TypeCastBind(Context& kContext,
        NiMaterialResource* pkSrc, NiMaterialResource* pkDest);

    /**
        Given two vectors (type float), will attempt to combine them into a single float vector of
        the same dimension as the sum of the two inputs.
    */
    bool Combine(Context& kContext, NiMaterialResource* pkInputA, NiMaterialResource* pkInputB, 
        NiMaterialResource*& pkOutput);

    /**
        Given two vectors (type float), will attempt to combine them into a single float vector of
        the same dimension as the sum of the two inputs. 
        Once they are combined this will also attempt to bind the output.
    */
    bool CombineBind(Context& kContext, NiMaterialResource* pkInputA, NiMaterialResource* pkInputB, 
        NiMaterialResource* pkOutput);

    /**
        This utility methods will attempt to bind two resources together.
        If one of the resource does not exist, then the binding will not be attempted. 
    */
    bool OptionalBind(Context& kContext, NiFixedString kSrcName, NiMaterialNode* pkSrcNode, 
        NiFixedString kDestName, NiMaterialNode* pkDestNode);

    /**
        This utility methods will attempt to bind two resources together.
        If one of the resource does not exist, then the binding will not be attempted. 
    */
    bool OptionalBind(Context& kContext, NiMaterialResource* pkSrc, 
        NiFixedString kDestName, NiMaterialNode* pkDestNode);

    /**
        This utility methods will attempt to bind two resources together.
        If one of the resource does not exist, then the binding will not be attempted. 
    */
    bool OptionalBind(Context& kContext, NiFixedString kSrcName, NiMaterialNode* pkSrcNode, 
        NiMaterialResource* pkDest);

    /**
        This utility methods will attempt to bind two resources together.
        If one of the resource does not exist, then the binding will not be attempted. 
    */
    bool OptionalBind(Context& kContext, NiMaterialResource* pkSrc, NiMaterialResource* pkDest);

    /**
        Generate a shader static constant based on the value passed in. Useful for converting
        C++ boolean values into shader booleans and integers etc. 
    */
    NiMaterialResource* GenerateShaderConstant(Context& kContext, bool bValue);

    /**
        Generate a shader static constant based on the value passed in. Useful for converting
        C++ boolean values into shader booleans and integers etc. 
    */
    NiMaterialResource* GenerateShaderConstant(Context& kContext, efd::SInt32 iValue);

    /**
        Generate a shader static constant based on the value passed in. Useful for converting
        C++ boolean values into shader booleans and integers etc. 
    */
    NiMaterialResource* GenerateShaderConstant(Context& kContext, float fValue);

    /**
        Generate a shader static constant based on the value passed in. Useful for converting
        C++ boolean values into shader booleans and integers etc. 
    */
    NiMaterialResource* GenerateShaderConstant(Context& kContext, const NiPoint4& kPoint);

    /**
        Generate a shader static constant based on the value passed in. Useful for converting
        C++ boolean values into shader booleans and integers etc. 
    */
    NiMaterialResource* GenerateShaderConstant(Context& kContext, const NiPoint3& kPoint);

    /**
        Generate a shader static constant based on the value passed in. Useful for converting
        C++ boolean values into shader booleans and integers etc. 
    */
    NiMaterialResource* GenerateShaderConstant(Context& kContext, const NiPoint2& kPoint);

    /**
        Generate a shader static constant based on the value passed in. Useful for converting
        C++ boolean values into shader booleans and integers etc. 
    */
    NiMaterialResource* GenerateShaderConstant(Context& kContext, const NiColor& kColor);

    /**
        Cast the source value into the specified type
    */
    bool TypeCast(Context& kContext, NiFixedString kDstType,
        NiMaterialResource* pkInput, NiMaterialResource*& pkOutput);

    /**
        This method will transform an input position by the given 
        transformation. Useful in converting between world/view/projection 
        spaces. 
    */
    bool TransformPosition(Context& kContext, 
        NiMaterialResource* pkPosition, NiMaterialResource* pkTransform,
        NiMaterialResource*& pkTransformPos);

    /**
        This method will rotate an input direction by the given transformation.
        Useful in rotating things into world/view/projection spaces.
    */
    bool TransformDirection(Context& kContext,
        NiMaterialResource* pkDirection, NiMaterialResource* pkTransform,
        NiMaterialResource*& pkTransformDir);
};

#endif  //#ifndef NIFRAGMENTOPERATIONS_H
