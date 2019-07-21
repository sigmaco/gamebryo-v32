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
#ifndef EE_CAMERADATA_H
#define EE_CAMERADATA_H

#include "ecrLibType.h"

#include <NiCamera.h>
#include <egf/Entity.h>
#include <efd/SmartPointer.h>
#include <egf/EntityManager.h>

namespace ecr
{

/**
    CameraData holds per camera data needed by the CameraService. This data includes
    an NiCamera, a reference to the camera entity, and a zoom factor.
*/
class EE_ECR_ENTRY CameraData : public efd::MemObject
{
    EE_DECLARE_CONCRETE_REFCOUNT;

public:

    /// Fully qualified constructor. The zoom is set to 1.
    CameraData(NiCamera* pCamera, egf::EntityManager* pEntityManager);

    /// Get a pointer to the NiCamera object held by this data.
    NiCamera* GetCamera() const;

    /// Get the entity ID of the camera.
    egf::EntityID GetId() const;

    /// Set the entity ID of the camera.
    void SetId(egf::EntityID id);

    /**
        Set the rotation for the camera on the entity. Note that this will not directly
        change the NiCamera object's rotation. That is handled by the CameraService when
        it receives an entity update message. Since rotation on entities is stored as
        a triple of Euler angles, this matrix form of the set method will extract the angles
        from the rotation matrix.
        @param rotation Camera rotation stored as a 3x3 rotation matrix.
    */
    void SetRotate(const NiMatrix3& rotation);

    /**
        Get the translation of the camera entity.
    */
    efd::Point3 GetTranslate();

    /**
        Get the rotation of the camera entity as a triple of Euler angles.
    */
    efd::Point3 GetRotate();

    /**
        Get the scale of the camera entity.
    */
    efd::Float32 GetScale();

    /**
        Get the zoom of the camera entity.
    */
    efd::Float32 GetZoomFactor();

    /**
        Set the translation for the camera on the entity. Note that this will not directly
        change the NiCamera object's rotation. That is handled by the CameraService when
        it receives an entity update message.
    */
    void SetTranslate(efd::Point3 translation);

    /**
        Set the rotation for the camera on the entity. Note that this will not directly
        change the NiCamera object's rotation. That is handled by the CameraService when
        it receives an entity update message.
        @param rotation Camera rotation stored as an Euler angle triple.
    */
    void SetRotate(efd::Point3 rotation);

    /**
        Set the scale for the camera on the entity. Note that this will not directly
        change the NiCamera object's rotation. That is handled by the CameraService when
        it receives an entity update message.
    */
    void SetScale(efd::Float32 scale);

    /**
        Set the zoom for the camera on the entity. Note that this will not directly
        change the NiCamera object's rotation. That is handled by the CameraService when
        it receives an entity update message.
    */
    void SetZoomFactor(efd::Float32 zoom);

private:

    egf::EntityID m_id;

    NiCameraPtr m_spCamera;
    efd::SmartPointer< egf::EntityManager > m_spEntityManager;

public:

    /// Current zoom of the camera.
    efd::Float32 m_zoom;
};

typedef efd::SmartPointer<CameraData> CameraDataPtr;

}; // namespace

#endif // EE_CAMERADATA_H
