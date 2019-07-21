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

#ifndef EE_PROPERTYVISUALIATIONHELPERS_H
#define EE_PROPERTYVISUALIATIONHELPERS_H

#include "egmVisualizersPCH.h"

#include <egf/ExtraData.h>
#include <egf/Entity.h>

#include <NiColor.h>
#include <NiMesh.h>
#include <NiMath.h>

#include <ecr/RenderService.h>
#include <ecr/SceneGraphService.h>

namespace egmVisualizers
{

/**
    PropertyVisualizationHelpers contains a set of static methods intended to be used
    by the property visualizers to do their task.  There are utility functions to
    create geometry and get property values that a visualizer depends on.
*/
class PropertyVisualizationHelpers
{
public:
    /**
        Creates a non-filled circle with Z=0.  If there are no streams, they will be
        created.  Otherwise, the existing streams will be modified, so it's
        important that subsequent calls to CreateCircle on the same mesh
        have the same numSlices (which will result in the same amount of
        vertices being created).

        @param pMesh Mesh to put the circle data on.
        @param radius Radius of the circle to create.
        @param numSlices Number of slices around the radius.
    */
    static void CreateCircle(
        NiMesh* pMesh,
        efd::Float32 radius,
        efd::UInt16 numSlices);

    /**
        Creates a wireframe sphere.  If there are no streams, they will be
        created.  Otherwise, the existing streams will be modified, so it's
        important that subsequent calls to CreateWireSphere on the same mesh
        have the same numSlices and numStacks (which will result in the same
        amount of vertices being created).

        @param pMesh Mesh to put the sphere data on.
        @param radius Radius of the sphere to create.
        @param numSlices Number of slices around the radius.
        @param numStacks Number of stacks along the main axis.
    */
    static void CreateWireSphere(
        NiMesh* pMesh,
        efd::Float32 radius,
        efd::UInt16 numSlices,
        efd::UInt16 numStacks);

    /**
        Creates a wireframe "cube" (rectangular parallelpiped.)
        If there are no streams, they will be created.
        Otherwise, the existing streams will be modified.

        @param pMesh Mesh to put the cube data on.
        @param width Width of the cube side (X dimension).
        @param length Length of the cube side (Y dimension).
        @param height Height of the cube side (Z dimension).
    */
    static void CreateWireCube(
        NiMesh* pMesh,
        efd::Float32 width,
        efd::Float32 length,
        efd::Float32 height);

    /**
        Creates a solid triangle list "cube" 
        If there are no streams, they will be created.
        Otherwise, the existing streams will be modified.

        @param pMesh Mesh to put the cube data on.
        @param width Width of the cube side (X dimension).
        @param length Length of the cube side (Y dimension).
        @param height Height of the cube side (Z dimension).
    */
    static void CreateSolidCube(
        NiMesh* pMesh,
        efd::Float32 width,
        efd::Float32 length,
        efd::Float32 height);

    /**
        Creates a wireframe representation of a view frustum.
        If there are no streams, they will be created.
        Otherwise, the existing streams will be modified.

        @param pMesh Mesh to put the frustum data on.
        @param fov Field of view.
        @param near Near plane.
        @param far Far plane.
        @param aspect Aspect ratio.
    */
    static void CreateFrustum(
        NiMesh* pMesh,
        efd::Float32 fov,
        efd::Float32 near,
        efd::Float32 far,
        efd::Float32 aspect);

    /**
        Creates a wireframe representation of an asterisk.
        If there are no streams, they will be created.
        Otherwise, the existing streams will be modified.

        @param pMesh Mesh to put the asterisk data on.
    */
    static void CreateAsterisk(NiMesh* pMesh);

    /**
        Creates a line between two points.
        @param pMesh Mesh to put the line data on.
        @param point1 the start point of the line.
        @param point2 the end point of the line.
    */
    static void CreateLine(
        NiMesh* pMesh,
        const NiPoint3& point1,
        const NiPoint3& point2);

    /**
        Creates a spline between two points.
        @param pMesh Mesh to put the line data on.
        @param point1 the start point of the line.
        @param point2 the end point of the line.
    */
    static void CreateSpline(
        NiMesh* pMesh,
        const NiPoint3& point1,
        const NiPoint3& point2);

    /**
        Creates a 'line' which is really a 3D box extending
        between two points.
        If there are no streams, they will be created.
        Otherwise, the existing streams will be modified.

        @param pMesh Mesh to put the box data on.
        @param point1 the start point of the line.
        @param point2 the target point of the line.
        @param thickness the thickness (in world units, not pixels) of the line.
    */
    static void CreateThickLine(
        NiMesh* pMesh,
        const NiPoint3& point1,
        const NiPoint3& point2,
        float thickness);

    /// Attaches a material property with default settings to the mesh.
    static NiMaterialProperty* AttachDefaultMaterial(NiMesh* pMesh);

    /**
        Adds a single mesh to the scene graph service.
        This is simply an ease-of-use function.

        @param spMesh Mesh to add.
        @param pSceneGraphService Scene graph service to add the mesh to.
    */
    static ecr::SceneGraphService::SceneGraphHandle AddMeshToSceneGraphService(
        NiMeshPtr spMesh,
        ecr::SceneGraphService* pSceneGraphService);

    /**
        Gets an numeric property as a float.  There may be some conversion
        involved, and thus there may be a loss in precision.

        @param pEntity Entity to retrieve the property value from.
        @param propertyName Name of the property to retrieve.
        @param value Returned value of the property.
        @return Status of the conversion operation.
    */
    static egf::PropertyResult GetPropertyAsFloat(
        egf::Entity* pEntity,
        const efd::utf8string& propertyName,
        efd::Float32& value);

    /**
        Gets a scalar property as a string.

        @param pEntity Entity to retrieve the property from.
        @param propertyName Name of the property to retrieve.
        @param value The string representation of the property.
        @return Status of the conversion operation.
    */
    static egf::PropertyResult GetPropertyAsString(
        egf::Entity* pEntity,
        const efd::utf8string& propertyName,
        efd::utf8string& value);

    /**
        Gets a visualizer dependency from an entity, looking at a default if necessary.

        @param spExtraData Extra data that contains the visualizer definition.
        @param pEntity Entity to retrieve the dependency from.
        @param dependency The type of the dependency to retrieve.
        @param defaultProperty The default property name if no dependency is specified.
        @param value The property value.
        @return Status of the conversion operation.
    */
    template<class T>
    inline static egf::PropertyResult GetDependency(
        egf::ExtraDataPtr spExtraData,
        egf::Entity* pEntity,
        const efd::utf8string& dependency,
        const efd::utf8string& defaultProperty,
        T& value);

    /**
        Gets an associative array dependency from an entity, looking at a default if necessary.

        @param spExtraData Extra data that contains the visualizer definition.
        @param pEntity Entity to retrieve the dependency from.
        @param dependency The type of the dependency to retrieve.
        @param defaultProperty The default property name if no dependency is specified.
        @param o_values The property keys/value.
        @return Status of the conversion operation.
    */
    template<class T>
    inline static egf::PropertyResult GetAssocArrayDependency(
        egf::ExtraDataPtr spExtraData,
        egf::Entity* pEntity,
        const efd::utf8string& dependency,
        const efd::utf8string& defaultProperty,
        efd::map<efd::utf8string, T>& o_values);

    /**
        Gets a visualizer dependency from an entity, looking at a default if necessary.
        This is a specialization of a templated-version of this function which works with floats.

        @param spExtraData Extra data that contains the visualizer definition.
        @param pEntity Entity to retrieve the dependency from.
        @param dependency The type of the dependency to retrieve.
        @param defaultProperty The default property name if no dependency is specified.
        @param value The property value.
        @return Status of the conversion operation.
    */
    static egf::PropertyResult GetDependency(
        egf::ExtraDataPtr spExtraData,
        egf::Entity* pEntity,
        const efd::utf8string& dependency,
        const efd::utf8string& defaultProperty,
        efd::Float32& value);

protected:
    /**
        Creates all the vertices necessary to construct a sphere.

        @param pPoints the array where the vertices will be written to.
        @param radius the radius of the sphere.
        @param numSlices the number of slices.
        @param numStacks the number of stacks.
    */
    static void CreateSphereVerts(
        NiPoint3* pPoints,
        efd::Float32 radius,
        efd::UInt32 numSlices,
        efd::UInt32 numStacks);
};

}

#include "PropertyVisualizationHelpers.inl"

#endif
