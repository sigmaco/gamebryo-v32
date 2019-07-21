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
#ifndef EE_EntityTransformGizmoAdapter_H
#define EE_EntityTransformGizmoAdapter_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "TransformGizmoAdapter.h"

#include <efd/MessageService.h>
#include <egf/EntityManager.h>

namespace egmToolServices
{

class SelectionService;
class GizmoService;
class ToolSnapService;

class EE_EGMTOOLSERVICES_ENTRY EntityTransformGizmoAdapter : public TransformGizmoAdapter
{
    EE_DECLARE_CLASS1(EntityTransformGizmoAdapter, kCLASSID_EntityTransformGizmoAdapter, TransformGizmoAdapter);
    EE_DECLARE_CONCRETE_REFCOUNT;

public:
    EntityTransformGizmoAdapter(efd::ServiceManager* pServiceManager);

    virtual ~EntityTransformGizmoAdapter();

    virtual efd::Bool IsVisible() const;
    virtual efd::Bool IsSelected(NiAVObject* pObject) const;

    virtual efd::Point3 GetOrigin() const;
    virtual efd::Matrix3 GetRotation() const;
    virtual efd::UInt32 GetTargets() const;

    virtual void BeginTransform();
    virtual void EndTransform(bool cancel);

    virtual efd::Bool SnapToPoints(efd::UInt32 targetIndex, efd::Point3 translationDelta);

    virtual efd::Bool CanTranslate(efd::UInt32 targetIndex);
    virtual efd::Point3 GetTranslationStart(efd::UInt32 targetIndex) const;
    virtual void GetTranslation(efd::UInt32 targetIndex, efd::Point3& position) const;
    virtual void SetTranslation(efd::UInt32 targetIndex, const efd::Point3& position);

    virtual efd::Bool CanRotate(efd::UInt32 targetIndex);
    virtual efd::Matrix3 GetRotationStart(efd::UInt32 targetIndex) const;
    virtual void GetRotation(efd::UInt32 targetIndex, efd::Matrix3& rotation) const;
    virtual void SetRotation(efd::UInt32 targetIndex, const efd::Matrix3& rotation);

    virtual efd::Bool CanScale(efd::UInt32 targetIndex);
    virtual efd::Float32 GetScaleStart(efd::UInt32 targetIndex) const;
    virtual void GetScale(efd::UInt32 targetIndex, efd::Float32& scale) const;
    virtual void SetScale(efd::UInt32 targetIndex, const efd::Float32& scale);

    virtual void OnTransformClone();

protected:

    struct EntityMemento
    {
        egf::Entity* Entity;

        efd::Point3 StartPosition;
        efd::Matrix3 StartRotation;
        efd::Float32 StartScale;

        bool HasPosition;
        bool HasRotation;
        bool HasScale;
    };

    void ClearMementos();

    // Property Names
    //-------------------------------------------------------------------------
    efd::utf8string m_positionName;
    efd::utf8string m_rotationName;
    efd::utf8string m_scaleName;

    // Entity Start States
    //-------------------------------------------------------------------------
    typedef efd::vector<EntityMemento*> EntityMementos;
    EntityMementos m_entityStartStates;
    
    // Dirty
    //-------------------------------------------------------------------------
    efd::Bool m_translateDirty;
    efd::Bool m_rotateDirty;
    efd::Bool m_scaleDirty;

    // Services
    //-------------------------------------------------------------------------
    egf::EntityManager* m_pEntityManager;
    ToolSceneGraphService* m_pSceneGraphService;
    GizmoService* m_pGizmoService;
    SelectionService* m_pSelectionService;
    ToolSnapService* m_pSnapService;
};

typedef efd::SmartPointer<EntityTransformGizmoAdapter> EntityTransformGizmoAdapterPtr;

}; // namespace

#endif // EE_EntityTransformGizmoAdapter_H