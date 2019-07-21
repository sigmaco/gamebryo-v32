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
#ifndef EE_TERRAINEDITGIZMO_H
#define EE_TERRAINEDITGIZMO_H

class NiTerrainCell;
class NiTerrain;

namespace egmToolServices
{

class ToolTerrainService;
class TerrainPaintingGuide;

/**
    Class used to manage the gizmo that is displayed on the terrain when editing it in Toolbench.
    See IGizmo for more information
*/
class EE_EGMTOOLSERVICES_ENTRY TerrainEditGizmo : public IGizmo
{
public:
    /**
        Constructor.

        @param pServiceManager pointer to the service manager used to initialize the gizmo
    */
    TerrainEditGizmo(efd::ServiceManager* pServiceManager);
    virtual ~TerrainEditGizmo();

    /// @name Overriden functionality
    /// @see IGizmo
    //@{
    virtual void Connect(Ni3DRenderView* pGizmoView);
    virtual void Disconnect(Ni3DRenderView* pGizmoView);

    virtual efd::Bool OnTick(efd::TimeType timeElapsed, ecr::RenderSurface* pSurface);

    virtual efd::Bool OnMouseScroll(
        ecr::RenderSurface* pSurface,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dScroll,
        efd::Bool bIsClosest);

    virtual efd::Bool OnMouseMove(
        ecr::RenderSurface* pSurface,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dx,
        efd::SInt32 dy,
        efd::Bool bIsClosest);

    virtual efd::Bool OnMouseDown(
        ecr::RenderSurface* pSurface,
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::Bool bIsClosest);

    virtual efd::Bool OnMouseUp(
        ecr::RenderSurface* pSurface,
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::Bool bIsClosest);

    virtual void BeginTransform();
    virtual void EndTransform(efd::Bool cancel);

    virtual efd::Bool HitTest(
        ecr::RenderSurface* pSurface,
        const efd::Point3& rayOrigin,
        const efd::Point3& rayDirection,
        float& outHitDistance);
    //@}

    /**
        Sets the gizmo's root node
    */
    inline void SetGizmoMesh(NiNode* pObject);

    /**
        Gets the gizmo's root node
    */
    inline NiNode* GetGizmoMesh();

    /**
        Sets the gizmo's radius
    */
    inline void SetBrushRadius(efd::Float32 radius);

    /**
        Getsthe gizmo's radius
    */
    inline efd::Float32 GetBrushRadius() const;

    /**
        Retrieves the gizmo's last intersection point with the terrain
    */
    inline efd::Point3 GetLastIntersectionPt() const;

    /**
        Enables / disables the gizmo's airbrush mode
    */
    inline void EnableAirbrushMode(efd::Bool isEnabled);

    /**
        Gets the last cell the gizmo collided with
    */
    const NiTerrainCell* GetLastIntersectedCell() const;

    /**
        Gets the last ray that was used for collision with the terrain
    */
    void GetLastRay(efd::Point3& rayOrigin, efd::Point3& rayDirection);

    /** 
        returns the painting guide
    */
    TerrainPaintingGuide* GetPaintingGuide();

    /**
        Update the gizmo (m_spGizmo) with the latest terrain transform. This will then be used
        by both the painting gizmo and the painting guide.
    */
    void UpdateGizmoTransform(NiTerrain* pTerrain);

    /**
        This function parses through the color stream of the gizmo and inverts them.
    */
    void InvertBrushColor(bool invert);

protected:

    /**
        Transform's the gizmo to the new location.

        @param centerPoint Point where the gizmo should be centered around.
    */
    void UpdateGizmoPosition(const efd::Point3& centerPoint);

    /**
        Updates the gizmo's point's height to follow the terrain.
        @param pHeightMap buffer that holds the heights of the points that should be used to update
            the gizmo.
    */
    void UpdateGizmoShape(HeightMapBuffer* pHeightMap);

    /**
        Returns the worldspace bounding volume arround the gizmo.

        @param intersectionPt The point where the mouse intersects the terrain
        @param[out] x the terrain space coordinate of the gizmo's center point along the x axis
        @param[out] y the terrain space coordinate of the gizmo's center point along the y axis
        @param[out] width the width of the gizmo (in this case the brush's diameter)
        @param[out] height the height of the gizmo (in this case the brush's diameter)
    */
    void GetGizmoBoundingBox(
        const NiPoint3& intersectionPt,
        efd::SInt32& x, efd::SInt32& y, 
        efd::UInt32& width, efd::UInt32& height);

    /**
        Returns the terrain space bounding volume arround the gizmo.

        @param intersectionPt The point where the mouse intersects the terrain
        @param[out] center the point at which the mouse interesected the terrain
        @param[out] dimensions the range that the painting should occur within.
    */
    void GetTerrainSpacePaintArea(const NiPoint3& intersectionPt,
        efd::Point2& center, efd::Point2& dimensions);

    /**
        Checks whether the given ray collides with the terrain.
        If the given ray collides with the terrain, the collisionPt and collisionNormal are set 
        using the terrain collision results. If collision was not detected, the direction is not 
        parallele to the Z vector and the terrain is not behind the ray startpoint, the collision
        point and the collision normal will be approximated.

        @param rayOrigin the ray's start point.
        @param rayDirection the ray's direction.
        @param[out] collisionPt The resulting collision point
        @param[out] collisionNormal The resulting collision normal
        @return true if the ray collided. False otherwise.
    */
    efd::Bool CheckForRayCollision(
        const NiPoint3& rayOrigin,
        const NiPoint3& rayDirection, 
        NiPoint3& collisionPt,
        NiPoint3& collisionNormal);

    /**
        This function creates the PaintMessage to be sent to the external application after 
        ensuring the mouse collides with the terrain and using the brush's data.

        @param startPoint The mouse position the stroke started at
        @param endPoint the mouse position the stroke ended at
        @param pSurface the RenderSurface over which the mouse moved.
    */
    void PaintStroke(
        const NiPoint2& startPoint,
        const NiPoint2& endPoint, 
        ecr::RenderSurface* pSurface);

    efd::MessageService* m_pMessageService;

    /// The last intersection resultin collision point
    NiPoint3 m_currIntersectionPt;

    /// The last intersection resulting collision normal
    NiPoint3 m_currIntersectionNormal;

    /// The last intersection resulting cell
    const NiTerrainCell* m_pCurrIntersectedCell;

    efd::Bool m_isActive;
    
    /// The brush's radius
    efd::Float32 m_brushRadius;

    /// Remaining distance to cover in a paint stroke
    efd::Float32 m_remainingDistance;

    /// The current mouse position
    efd::Point2 m_currMouse;

    /// The last known mouse position
    efd::Point2 m_lastMouse;

    /// The origin of the last ray tested against the terrain
    NiPoint3 m_lastRayOrigin;

    /// The direction of the last ray tested against the terrain
    NiPoint3 m_lastRayDirection;

    // Cache an instance of the terrain service.
    ToolTerrainService* m_pTerrainService;

    /// Terrain painting guide
    TerrainPaintingGuide* m_pTerrainPaintingGuide;

    /// Whether we are currently painting 
    efd::Bool m_isPainting;

    /// Whether air brushing is enabled
    efd::Bool m_isAirbrushModeEnabled;

    /// Whether the gizmo's color is inverted (this is the case when pressing Ctrl to "unpaint"
    efd::Bool m_isColorInverted;

    /// Whether the mouse moved.
    efd::Bool m_mouseMoved;

    /// The gizmo's root node
    NiNodePtr m_spGizmo;
    NiNodePtr m_spGizmoMesh;
};

/// Defines a smart pointer (reference counted) for the TerrainEditGizmo class
typedef efd::SmartPointer<TerrainEditGizmo> TerrainEditGizmoPtr;

} // namespace

#include "TerrainEditGizmo.inl"

#endif // EE_TERRAINEDITGIZMO_H
