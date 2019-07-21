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

#pragma once
#ifndef EE_D3D11UTILITY_H
#define EE_D3D11UTILITY_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

#include <efd/UniversalTypes.h>
#include <efd/Matrix3.h>

class NiTransform;

namespace ecr
{

/**
    Internal class that contains some utility functions that are useful in multiple parts of the 
    renderer library.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11Utility
{
public:
    /// Translate an NiTransform into a XMMATRIX.
    static void GetD3DFromNi(XMMATRIX& xnaMatrix, const NiTransform& niTransform);
    /// Translate a rotation, translation, and scale into an XMMATRIX
    static void GetD3DFromNi(
        XMMATRIX& xnaMatrix, 
        const efd::Matrix3& niRotation,
        const efd::Point3& niTranslation, 
        efd::Float32 niScale);
    /// Translate an NiTransform into a XMMATRIX and transpose.
    static void GetD3DTransposeFromNi(XMMATRIX& xnaMatrix, const NiTransform& niTransform);
    /// Translate a rotation, translation, and scale transform into an XMMATRIX and transpose.
    static void GetD3DTransposeFromNi(
        XMMATRIX& xnaMatrix,
        const efd::Matrix3& niRotation, 
        const efd::Point3& niTranslation, 
        efd::Float32 niScale);
};

}   // End namespace ecr.

#endif // EE_D3D11UTILITY_H
