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
#ifndef EE_BAPICORERUNTIME_H
#define EE_BAPICORERUNTIME_H

#include <egf/EntityID.h>

#include <ecr/ecrLibType.h>

namespace bapiCoreRuntime
{

/**
    A script may call this method to attach one entity to another, at a particular
    scene graph node location.
    
    Internally, the entity to attach is set to have it's Placeable model updated using the
    transform of the given scene grpah node on the target entity. This function will fail if
    a circular dependency is created (an entity is attached to itself, for instance).

    @param i_entityToAttachID The ID of the entity to be attached.
    @param i_entityTargetID The ID of the entity to attach to.
    @param i_nodeToAttachAt The name of the scene graph node to attach to.
    @param i_inheritScale When true, the scale of the attached entity inherited from the
        node to which it is attached. When false, the attached entity uses its own scale.
    @return False if either entity is not found, the target does not have a scene graph, the
        named node is not found, or a dependency causes failure. True if the attachment
        succeeded.
*/
EE_ECR_ENTRY bool AttachEntity(
    egf::EntityID i_entityToAttachID,
    egf::EntityID i_entityTargetID,
    const efd::utf8string& i_nodeToAttachAt,
    bool i_inheritScale);

/**
    A script may call this method to detach a previously attached entity.
    
    The entity must have previously attached using AttachEntity, and the node name must match
    the attach call.

    @param i_entityToDetachID The ID of the entity that was attached (i_entityToAttachID from the
        AttachEntity call).
    @param i_entityTargetID The ID of the entity to detach from.
    @param i_nodeToDetachFrom The name of the scene graph node to which the entity is attached.
    @return False if the entity is not found or the attempt to detach otherwise fails (due to
        a lack of existing attachment, most likely); otherwise true.
*/
EE_ECR_ENTRY bool DetachEntity(
    egf::EntityID i_entityToDetachID,
    egf::EntityID i_entityTargetID,
    const efd::utf8string& i_nodeToDetachFrom);

/**
    A script may call this method to attach a scene graph to an entity at a particular
    location.

    @param entityID The entity to attach to.
    @param attachmentKey The attachmentKey must be one of the keys on the AttachedObjects map
           property of the entity.
    @param assetURN The urn for the asset to attach at the location determined by the
           attachmentKey.
    @return False is returned if the entity is not found, the key is invalid, or the URN is
            invalid. The attachment is not guaranteed to occur even when true is returned,
            because errors from loading the asset may be delayed.
*/
EE_ECR_ENTRY bool AttachSceneGraph(
    egf::EntityID entityID,
    const efd::utf8string& attachmentKey,
    const efd::utf8string& assetURN);

/**
    A script may call this method to detach a scene graph from an entity at a particular
    location.

    @param entityID The entity to attach to.
    @param attachmentKey The attachmentKey must be one of the keys on the AttachedObjects map
           property of the entity.
    @return False if the entity is not found, the key is invalid, or there is no
            attached asset at that location.
*/
EE_ECR_ENTRY bool DetachSceneGraph(
    egf::EntityID entityID,
    const efd::utf8string& attachmentKey);

/**
    A script may call this method to query the URN of the scene graph attached to an entity at
    a particular location.

    @param entityID The entity to query.
    @param attachmentKey The attachmentKey must be one of the keys on the AttachedObjects map
           property of the entity.
    @return The URN of the attached scene graph.  The empty string is returned on error or if
            nothing is attached.
*/
EE_ECR_ENTRY efd::utf8string GetAttachedSceneGraph(
    egf::EntityID entityID,
    const efd::utf8string& attachmentKey);

/**
    A script may call this method to modify the translation offset applied to an attached asset.

    @param entityID The entity with this attachment.
    @param attachmentKey The attachmentKey must be one of the keys on the AttachedObjects map
           property of the entity.
    @param offset The new translation offset.
    @return True on success.  False if the entity is not found or the key is invalid.
*/
EE_ECR_ENTRY bool SetAttachmentOffset(
    egf::EntityID entityID,
    const efd::utf8string& attachmentKey,
    const efd::Point3& offset);

/**
    A script may call this method to modify the rotation applied to an attached asset.

    @param entityID The entity with this attachment.
    @param attachmentKey The attachmentKey must be one of the keys on the AttachedObjects map
           property of the entity.
    @param rotation The new rotation (given in Euler angles.)
    @return True on success.  False if the entity is not found or the key is invalid.
*/
EE_ECR_ENTRY bool SetAttachmentRotation(
    egf::EntityID entityID,
    const efd::utf8string& attachmentKey,
    const efd::Point3& rotation);

/**
    A script may call this method to modify the scale applied to an attached asset.

    @param entityID The entity with this attachment.
    @param attachmentKey The attachmentKey must be one of the keys on the AttachedObjects map
           property of the entity.
    @param scale The new scale for this attachment.
    @return True on success.  False if the entity is not found or the key is invalid.
*/
EE_ECR_ENTRY bool SetAttachmentScale(
    egf::EntityID entityID,
    const efd::utf8string& attachmentKey,
    efd::Float32 scale);

/**
    A script may call this method to obtain the translation offset applied to an attached asset.

    @param i_entityID The entity with this attachment.
    @param i_attachmentKey The attachmentKey must be one of the keys on the AttachedObjects map
           property of the entity.
    @param o_offset The queried translation offset.
    @return True on success.  False if the entity is not found or the key is invalid.
*/
EE_ECR_ENTRY bool GetAttachmentOffset(
    egf::EntityID i_entityID,
    const efd::utf8string& i_attachmentKey,
    efd::Point3* o_offset);

/**
    A script may call this method to obtain the rotation applied to an attached asset.

    @param i_entityID The entity with this attachment.
    @param i_attachmentKey The attachmentKey must be one of the keys on the AttachedObjects map
           property of the entity.
    @param o_rotation The queried translation offset (in Euler angles.)
    @return True on success.  False if the entity is not found or the key is invalid.
*/
EE_ECR_ENTRY bool GetAttachmentRotation(
    egf::EntityID i_entityID,
    const efd::utf8string& i_attachmentKey,
    efd::Point3* o_rotation);

/**
    A script may call this method to obtain the scale applied to an attached asset.

    @param i_entityID The entity with this attachment.
    @param i_attachmentKey The attachmentKey must be one of the keys on the AttachedObjects map
           property of the entity.
    @param o_scale The queried scale.
    @return True on success.  False if the entity is not found or the key is invalid.
*/
EE_ECR_ENTRY bool GetAttachmentScale(
    egf::EntityID i_entityID,
    const efd::utf8string& i_attachmentKey,
    efd::Float32* o_scale);

/**
    A script may call this method to obtain the world transformation of a node within the
    primary scene graph associated with the given entity.

    @param i_entityID The entity with this attachment.
    @param i_nodeName The node to query.
    @param o_position The queried translation of this node.
    @param o_rotation The queried rotation (in Euler angles) of this node.
    @param o_scale The queried scale of this node.
    @return True on success.  False if the entity is not found, the entity does not have
            a scene graph, or the named node is not found.
*/
EE_ECR_ENTRY bool GetSceneGraphNodeTransform(
    egf::EntityID i_entityID,
    const char* i_nodeName,
    efd::Point3* o_position,
    efd::Point3* o_rotation,
    efd::Float32* o_scale);


/**
    A script may call this method to find the closest object along a ray, and its distance from
    the ray origin.

    @param i_origin The origin of the ray.
    @param i_direction The direction of the ray. This need not be a unit vector, but must be
        non-zero.
    @param o_entityID Upon return, the closest entity along the ray. The return value will be
        the invalid entity ID if the ray does not hit any entity's scene graph.
    @param o_distance Upon return, the distance from the ray origin to the entity. This distance
        is in units of the ray's length. The intersection point of the ray and the entity
        can be found by computing origin + direction * distance.
    @return True if any entity is found along the ray.
*/
EE_ECR_ENTRY bool ClosestObjectOnRay(
    const efd::Point3& i_origin,
    const efd::Point3& i_direction,
    egf::EntityID* o_entityID,
    efd::Float32* o_distance);

/**
    A script may call this method to find the distance to a particular entity along a ray.

    @param i_origin The origin of the ray.
    @param i_direction The direction of the ray. This need not be a unit vector, but must be
        non-zero.
    @param i_entityID The Entity to look for along the ray.
    @param o_distance Upon return, the distance from the ray origin to the closest point on
        the entity. This distance is in units of the ray's length. The intersection point
        of the ray and the entity can be found by computing origin + direction * distance.
    @return True if any entity is found along the ray.
*/
EE_ECR_ENTRY bool DistanceToEntityAlongRay(
    const efd::Point3& i_origin,
    const efd::Point3& i_direction,
    egf::EntityID i_entityID,
    efd::Float32* o_distance);

} // end namespace bapiCoreRuntime

#endif // EE_BAPICORERUNTIME_H
