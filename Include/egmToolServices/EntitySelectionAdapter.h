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
#ifndef EE_ENTITYSELECTIONADAPTER_H
#define EE_ENTITYSELECTIONADAPTER_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <efd/Point3.h>
#include <efd/Matrix3.h>

#include <NiAVObject.h>

#include <ecr\PickService.h>
#include <ecr\SceneGraphService.h>

#include "SelectionAdapter.h"

namespace egmToolServices
{
class SelectionService;

class EE_EGMTOOLSERVICES_ENTRY EntitySelectionAdapter : public SelectionAdapter
{
    EE_DECLARE_CLASS1(EntitySelectionAdapter, kCLASSID_EntitySelectionAdapter, SelectionAdapter);
    EE_DECLARE_CONCRETE_REFCOUNT;

public:
    EntitySelectionAdapter(efd::ServiceManager* pServiceManager);
    virtual ~EntitySelectionAdapter();

    // SelectionAdapter Members
    //=========================================================================

    virtual void OnAdded();
    virtual void OnRemoved();

    virtual efd::Bool HasSelection() const;
    virtual void ClearSelection();

    virtual NiBound GetBound();
    virtual efd::Point3 GetCenter();

    /**
    Selects. 
    
    @param pSurface The surface.
    @param x The x coordinate.
    @param y The y coordinate.
    @param origin The origin.
    @param direction The direction.
    
    @return true if it succeeds, false if it fails.
    */
    virtual efd::Bool Select(
        ecr::RenderSurface* pSurface,
        efd::SInt32 x,
        efd::SInt32 y,
        const efd::Point3& origin,
        const efd::Point3& direction);

    /**
    Select frustum. 
    
    @param pCamera The camera.
    @param pCuller The culler.
    
    @return true if it succeeds, false if it fails.
    */
    virtual efd::Bool SelectFrustum(NiCamera* pCamera, NiMeshCullingProcess* pCuller);

    /**
    Renders a selection.
    
    @param pRenderService The render service.
    @param uiFrameID Identifier for the frame.
    */
    virtual void RenderSelection(
        ecr::RenderService* pRenderService,
        unsigned int uiFrameID);

    //=========================================================================

    efd::Bool IsSelected(const egf::EntityID& entityId);
    
    /**
        Picks the closest entity in the scene and sets the entity id of the one found as well
        as the associated scenegraph object.

        @param [in] rayStart Start position of the selection ray.
        @param [in] rayDir Direction of the ray.
        @param [out] pEntity Stores the resulting entity if an entity was found.
        @param [out] pSelectedObject the selected scene object.
        @return True if an entity was selected, false otherwise.
    */
    efd::Bool PickEntity(
        const efd::Point3& rayStart,
        const efd::Point3& rayDir,
        egf::Entity*& pEntity,
        NiAVObject*& pSelectedObject);

    void SelectEntities(const efd::list<efd::ID128>* pEntities);
    void SelectEntities(const efd::list<egf::Entity*>* pEntities);

    void DeselectEntities(const efd::list<efd::ID128>* pEntities);
    void DeselectEntities(const efd::list<egf::Entity*>* pEntities);

    const efd::map<egf::EntityID, NiAVObjectPtr>& GetSelectedEntities() const;

    /**
        Handle a selectability changed message.
        @param pMsg The selectability changed message.
        @param targetChannel Channel the message was sent on.
     */
    void OnSelectabilityChanged(
        const efd::IMessage* pMsg,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity is removed from the
        EntityManager. If the entity is selected, it will be removed from the
        current selection.
        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityRemovedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity property is changed. If
        the entity is currently selected and the scene graph associated with
        the entity is changed, this method updates the selected representation
        of the entity.
        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

        /**
        Handle a message indicating that scene graph assets have been added.
        @param pMessage The scene graph added message.
        @param targetChannel Channel the message was sent on.
     */
    void OnSceneGraphAdded(
        const ecr::SceneGraphAddedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Handle a message indicating that scene graph assets have changed.
        @param pMessage The scene graph changed message.
        @param targetChannel Channel the message was sent on.
     */
    void OnSceneGraphChanged(
        const efd::StreamMessage* pMessage,
        efd::Category targetChannel);

    /**
        Handle a message indicating that scene graph assets have been removed.
        @param pMessage The scene graph removed message.
        @param targetChannel Channel the message was sent on.
     */
    void OnSceneGraphRemoved(
        const ecr::SceneGraphRemovedMessage* pMessage,
        efd::Category targetChannel);

    /// Helper method to determine if an entity can be selected using the UI.
    bool IsFrozenEntity(const egf::Entity* pEntity) const;

protected:

    void SendSelectionMessage(
        efd::vector<egf::EntityID> added,
        efd::vector<egf::EntityID> removed,
        efd::Bool clear);

    void BeginSelection();
    void EndSelection();

    efd::Bool ToggleSelectedEntity(const egf::Entity* pEntity, NiAVObject* pSelectedNode);

    void AddSelectedEntity(const egf::Entity* pEntity);
    void AddSelectedEntity(const egf::Entity* pEntity, NiAVObject* pSelectedNode);

    void RemoveSelectedEntity(const egf::Entity* pEntity);
    void RemoveSelectedEntity(const egf::Entity* pEntity, NiAVObject* pSelectedNode);

    void ClearSelectedEntities();

    enum UnselectableCategories
    {
        UNSELECTABLE_PER_ENTITY = 0,
        UNSELECTABLE_PER_LAYER,
        UNSELECTABLE_MAX
    };

    efd::MessageService* m_pMessageService;
    egf::EntityManager* m_pEntityManager;
    ecr::RenderService* m_pRenderService;
    ecr::PickService* m_pPickService;
    ecr::SceneGraphService* m_pSceneGraphService;
    SelectionService* m_pSelectionService;

    typedef efd::map<egf::EntityID, NiAVObjectPtr> EntityAVMap;
    EntityAVMap m_selectedEntities;
    efd::map<egf::EntityID, bool> m_unselectableEntities[UNSELECTABLE_MAX];

    efd::Point3 m_center;
    efd::Bool m_centerInvalid;

    typedef efd::vector<const egf::Entity*> EntityList;

    efd::Bool m_tempCleared;
    EntityList m_tempAdded;
    EntityList m_tempRemoved;
};

typedef efd::SmartPointer<EntitySelectionAdapter> EntitySelectionAdapterPtr;

}; // egmToolServices namespace

#endif // EE_ENTITYSELECTIONADAPTER_H
