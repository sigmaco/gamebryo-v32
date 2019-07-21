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
#ifndef EE_ENTITYCREATIONGIZMOADAPTER_H
#define EE_ENTITYCREATIONGIZMOADAPTER_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "CreationGizmoAdapter.h"

#include <efd/MessageService.h>
#include <egf/EntityManager.h>
#include <egf/FlatModelManager.h>

namespace egmToolServices
{

class SelectionService;
class GizmoService;
class ToolSnapService;

class EE_EGMTOOLSERVICES_ENTRY EntityCreationGizmoAdapter : public CreationGizmoAdapter
{
    EE_DECLARE_CLASS1(EntityCreationGizmoAdapter, kCLASSID_EntityCreationGizmoAdapter, CreationGizmoAdapter);
    EE_DECLARE_CONCRETE_REFCOUNT;

public:
    EntityCreationGizmoAdapter(efd::ServiceManager* pServiceManager);

    virtual ~EntityCreationGizmoAdapter();

    virtual void OnTick();
    virtual void OnRemoved();

    virtual efd::Bool IsVisible() const;
    virtual efd::Bool IsSelected(NiAVObject* pObject) const;

    virtual efd::Point3 GetOrigin() const;
    virtual efd::Matrix3 GetRotation() const;
    virtual efd::UInt32 GetTargets() const;

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

    virtual void Create();

protected:

    // Property Names
    //-------------------------------------------------------------------------
    efd::utf8string m_positionName;
    efd::utf8string m_rotationName;
    efd::utf8string m_scaleName;

    // Temporary Entity
    //-------------------------------------------------------------------------
    efd::utf8string m_modelName;
    efd::Bool m_bEntityAdded;
    egf::EntityPtr m_spTempEntity;

    efd::Point3 m_startingRotation;

    // Services
    //-------------------------------------------------------------------------
    egf::EntityManager* m_pEntityManager;
    egf::FlatModelManager* m_pFlatModelManager;
    ecr::RenderService* m_pRenderService;
    ToolSceneGraphService* m_pSceneGraphService;
    GizmoService* m_pGizmoService;
    SelectionService* m_pSelectionService;
    ToolSnapService* m_pSnapService;
};

typedef efd::SmartPointer<EntityCreationGizmoAdapter> EntityCreationGizmoAdapterPtr;

}; // egmToolServices namespace

#endif // EE_ENTITYCREATIONGIZMOADAPTER_H