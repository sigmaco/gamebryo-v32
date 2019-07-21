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
#ifndef EE_TOOLCAMERASERVICE_H
#define EE_TOOLCAMERASERVICE_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <efd/MessageHandlerBase.h>
#include <efd/ISystemService.h>
#include <efd/StreamMessage.h>

#include <Ni2DStringRenderClick.h>

#include <egf/EntityManager.h>

#include <ecr/RenderSurface.h>
#include <ecr/RenderService.h>
#include <ecr/ecrSystemServiceIDs.h>
#include <ecrInput/KeyboardMessages.h>

#include "ToolCamera.h"
#include "ICameraMode.h"

#include "ToolSceneService.h"
#include "ToolServicesMessages.h"
#include "IInteractionDelegate.h"

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY ToolCameraService : public efd::ISystemService,
                                                   public IInteractionDelegate
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS2(ToolCameraService,
        efd::kCLASSID_ToolCameraService,
        efd::ISystemService,
        IInteractionDelegate);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    ToolCameraService();

    ToolCamera* GetActiveCamera();
    ToolCamera* GetActiveCamera(ecr::RenderSurface* pSurface);

    void SetActiveCamera(const efd::utf8string& cameraName, efd::WindowRef window);
    void SetActiveCamera(const efd::utf8string& cameraName);

    void SetActiveCameraMode(const efd::utf8string& name);

    void LookAtSelection();
    void MoveToSelection();

    void ZoomToExtents(ToolCamera* pCamera, const NiBound& kBound);

    void Reset();

    inline bool GetIsLooking() const;
    inline bool GetIsTranslating() const;
    inline bool GetIsPanning() const;

    inline bool MovingForward() const;
    inline bool MovingBackward() const;
    inline bool MovingLeft() const;
    inline bool MovingRight() const;
    inline bool MovingFast() const;

    inline float GetTurboScale() const;
    inline void SetTurboScale(float value);

    inline float GetKeyboardBaseMovement() const;
    inline void SetKeyboardBaseMovement(float value);
    inline float GetMouseBaseMovement() const;
    inline void SetMouseBaseMovement(float value);

    inline float GetMovementScale() const;
    inline void SetMovementScale(float value);
    inline float GetLookScale() const;
    inline void SetLookScale(float value);

    inline bool IsFlyingLevel() const;
    inline void IsFlyingLevel(bool value);

    inline float GetNearPlane() const;
    inline float GetFarPlane() const;

    // IInteractionDelegate Members
    //=========================================================================

    virtual efd::SInt32 GetInteractionPriority();

    virtual bool OnPreMouseScroll(efd::SInt32 x, efd::SInt32 y, efd::SInt32 dScroll);
    virtual bool OnPreMouseMove(efd::SInt32 x, efd::SInt32 y, efd::SInt32 dx, efd::SInt32 dy);
    virtual bool OnPreMouseDown(ecrInput::MouseMessage::MouseButton eButton, efd::SInt32 x,
        efd::SInt32 y);
    virtual bool OnPreMouseUp(ecrInput::MouseMessage::MouseButton eButton, efd::SInt32 x,
        efd::SInt32 y);

    virtual bool OnMouseScroll(efd::Bool handled, efd::SInt32 x, efd::SInt32 y,
        efd::SInt32 dScroll);
    virtual bool OnMouseMove(efd::Bool handled, efd::SInt32 x, efd::SInt32 y, efd::SInt32 dx,
        efd::SInt32 dy);
    virtual bool OnMouseDown(efd::Bool handled, ecrInput::MouseMessage::MouseButton eButton,
        efd::SInt32 x, efd::SInt32 y);
    virtual bool OnMouseUp(efd::Bool handled, ecrInput::MouseMessage::MouseButton eButton,
        efd::SInt32 x, efd::SInt32 y);

    void OnInputAction(const InputActionMessage* pMsg, efd::Category targetChannel);

    bool IsDefaultCamera(const efd::utf8string& cameraName);
    bool IsEntityBoundToAnyCamera(const egf::EntityID& entity);

    bool IsCameraEntityBound(ToolCamera* pCamera);

    void HandleEntityRemovedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    void SyncBoundEntities();

protected:

    /// Returns "ToolCameraService".
    virtual const char* GetDisplayName() const;
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();

    virtual ~ToolCameraService();

    void CreateDefaultCameras();
    void AdjustOrthoDistance(ToolCamera* pCamera);

    // Methods used for binding an entity to a camera so it will be updated
    // when the camera updates
    void UpdateCameraFromEntity(const egf::EntityID& entityID, ToolCamera* pCamera);
    void UpdateEntityFromCamera(const egf::EntityID& entityID, ToolCamera* pCamera);
    void ChangeEntityVisibility(const egf::EntityID& entityID, bool isVisible);
    egf::EntityID GetEntityBinding(const efd::utf8string& cameraName);
    bool IsEntityOrtho(const egf::EntityID& entityID);

    void BindCamera(const egf::EntityID& entityID, ToolCamera* pCamera);
    void UnbindCamera(ToolCamera* pCamera);

    void InitializeCameraViewFrustum(ToolCameraPtr spCamera,
        ecr::RenderSurface* pSurface);

    static void HandleSurfaceRemoved(ecr::RenderSurface* pSurface);

    efd::MessageService* m_pMessageService;
    ecr::RenderServicePtr m_spRenderService;
    egmToolServices::ToolSceneGraphServicePtr m_spToolSceneGraphService;

    efd::map<efd::utf8string, ToolCameraPtr> m_defaultCameras;
    efd::map<efd::WindowRef, ToolCameraPtr> m_activeCameras;
    efd::map<efd::WindowRef, ToolCameraPtr> m_savedCameras;

    ICameraMode* m_activeCameraMode;
    efd::map<efd::utf8string, ICameraModePtr> m_cameraModeMap;

    NiFontPtr m_spViewportFont;
    Ni2DStringPtr m_spViewportText;

    egf::EntityManager* m_pEntityManager;

    bool m_forward;
    bool m_backward;
    bool m_strafeLeft;
    bool m_strafeRight;
    bool m_shift;

    efd::TimeType m_lastUpdateTime;

    bool m_isLooking;
    bool m_isTranslating;
    bool m_isPanning;

    float m_turboScale;
    float m_keyboardBaseMovement;
    float m_mouseBaseMovement;

    float m_movementScale;
    float m_lookScale;
    bool m_flyLevel;

    float m_nearPlane;
    float m_farPlane;
};

typedef efd::SmartPointer<ToolCameraService> ToolCameraServicePtr;

} // namespace

#include "ToolCameraService.inl"

#endif // EE_TOOLCAMERASERVICE_H
