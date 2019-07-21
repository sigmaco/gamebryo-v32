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
#ifndef EE_BAPIONLINE
#define EE_BAPIONLINE

#include <efdNetwork/NetCategory.h>
#include <egf/EntityID.h>
#include <eon/OnlineEntry.h>
#include <efd/TimeType.h>
#include <efd/ParameterList.h>


// NOTE: This is a SWIG parsed file.  All methods listed in this file will have script wrappers
// generated.
//
// A note on argument types:
//
// Given any type the SWIG generated bindings will make certain assumptions about whether the
// parameter is an input argument, and output argument, or an input-output argument.  Given
// a type T, it will be treated as follows:
//
//    |---------------|---------------|------------------------------------------------------
//    | typename:     | treated as:   | notes:
//    |---------------|---------------|------------------------------------------------------
//    | T             | Input         |
//    | const T&      | Input         |
//    | const T*      | Input         | Pointer must NOT be NULL
//    | T*            | Output        | Pointer must NOT be NULL
//    | T&            | Input-Output  |
//    |---------------|---------------|------------------------------------------------------
//
// The one exception to the argument type rules above is efd::ParameterList.  efd::ParameterList*
// is treated as a basic type for the purpose of these rules, not efd::ParameterList itself.  For
// example, this means that "efd::ParameterList*" is treated as a plain ParameterList Input argument
// and "efd::ParameterList*&" is treated as an in-out efd::ParameterList parameter.  One additional
// special case, for convenance "efd::ParameterList&" is also treated as an in-out parameter.

namespace bapiOnline
{

/**
    Retrieves the current Virtual Process ID from the Service Manager. This is usually the same
    as the NetID, but may differ when using rapid iteration based on the order of connection to
    Toolbench verse the channel manager. The last connection established determines the virtual
    process ID but only the channel manager connection effects the NetID.

    @return The virtual process id.
*/
EE_EONENTRY efd::UInt32 GetVirtualProcessId();

/**
    Get the NetID for this process from the Net Service. The NetID starts with a default value
    and changes to a globally unique value when the process joins a channel manager. If connection
    to the channel manager is lost this will change back to the default value. Multiprocess
    applications can use this value to generate unique categories for their process but must pay
    attention to the connection state.

    @return The NetID.
*/
EE_EONENTRY efd::UInt32 GetNetID();

/**
    Find all entities that are reflected to this process.  Similar to
    BehaviorAPI::FindAllEntities only it excludes entities that are locally owned by the
    scheduler.

    @warning: If a large number of entities are reflected this API might consume excessive
        amounts of memory and take a long time to execute.  We recommend against using this
        API in general purpose settings, although it can often be helpful for certain
        debugging cases

    @param [out] OutValue : the list of entities that are found
    @return UInt32 the number of entities found
 */
EE_EONENTRY efd::UInt32 FindAllReplicatedEntities(efd::list<egf::EntityID>* OutValue);

/**
    Creates a list of all Entities that are published into the given Category. This includes
    both producing entities that produce to this category and consumer entities which are
    replicated to this process because they use that category.

    @param replicationCategory The Category to which the interesting Entities are being published
    @param[out] OutValue The resulting list of Entities.
    @return The number of entities that were found.
*/
EE_EONENTRY efd::UInt32 FindAllEntitiesByReplicationCategory(
    efd::Category replicationCategory,
    efd::list<egf::EntityID>* OutValue);

/**
    Sends a view behavior invocation request to the given event channel on behalf of the given
    entity. All replicas of that entity which are using the given replication channel
    will attempt to invoke the behavior. Typically the categories used are the same categories
    to which the producer entity replicates, but any category that the Replication Service is
    subscribed to maybe used (for example, any category used in SubscribeReplicationChannel).

    Note that the SendEvent method can only send behavior requests to the owned producer entity
    and not to the replicas of that entity. You must use one of the ViewEvent methods to send a
    behavior to a replica entity. Replica entities cannot use callback behaviors either as the
    callback will be invoked on the owned entity and not the replica.

    @param eventChannel The category for sending the event request, typically a replication
        channel.
    @param entityID The ID of the target replicated entity
    @param strBehavior The name of the behavior to execute for this event
    @param pStream The argument stream to pass to the behavior
    @param delay An optional time to wait before actually executing the event.
    @return True if the view event was generated and sent. A true value does not guarantee that the
        event message will be received or a behavior will execute.
*/
EE_EONENTRY bool SendViewEvent(
    efd::Category eventChannel,
    egf::EntityID entityID,
    const char* strBehavior,
    efd::ParameterList* pStream = NULL,
    double delay = 0.0);

/**
    Sends a view behavior invocation request to the given local replica entity. Only the local
    replica, if present, will run the behavior in question. This can be used from a running view
    behavior in order to queue an additional view behavior on the current entity, for example.

    Note that the SendEvent method can only send behavior requests to the owned producer entity
    and not to the replicas of that entity. You must use one of the ViewEvent methods to send a
    behavior to a replica entity. Replica entities cannot use callback behaviors either as the
    callback will be invoked on the owned entity and not the replica.

    @param entityID The ID of the target replica entity
    @param strBehavior The name of the behavior to execute for this event
    @param pStream The argument stream to pass to the behavior
    @param delay An optional time to wait before actually executing the event.
    @return True if the specified entity exists. A true value does not guarantee that the
        behavior is valid or will execute.
*/
EE_EONENTRY bool SendLocalViewEvent(
    egf::EntityID entityID,
    const char* strBehavior,
    efd::ParameterList* pStream = NULL,
    double delay = 0.0);

/**
    Causes the local ReplicationService to subscribe to the specified replication category. This
    will cause any remote entity publishing to that category to be replicated to this process.
    There must eventually be one matching call to UnsubscribeReplicationChannel method for every
    call to SubscribeReplicationChannel or else subscription references will be leaked causing
    unused data to remain in the current process.

    @param replicationChannel The channel for the replication group
*/
EE_EONENTRY void SubscribeReplicationChannel(efd::Category replicationChannel);

/**
    Causes the local ReplicationService to unsubscribe from the specified replication category.
    This will cause any replica entities that are replicated to this process only using the given
    category to be cleanly removed. There must be one matching call to UnsubscribeReplicationChannel
    method for every call to SubscribeReplicationChannel or else subscription references will be
    leaked.

    @param replicationChannel The channel for the replication group
*/
EE_EONENTRY void UnsubscribeReplicationChannel(efd::Category replicationChannel);

/// @name Replication groups
/// Methods to get or set entity replication groups which determine who can remotely "see" the
/// various properties on the entity.
//@{
/**
    Get the category to which the specified replication group for the given entity is published.
    This can be called on either the publishing entity or on a replica of that entity.

    @param id The entity id to get replication Category for.
    @param group The replication group to get the Category for. Valid range is 0 to 31 inclusive.
    @return The replication group Category for the specified entity and group.
*/
EE_EONENTRY efd::Category GetReplicationCategory(egf::EntityID id, efd::UInt32 group);

/**
    Set the replication group category for the given producer entity. The entity will stop
    producing to the previously set category, which can result in entity loss for remote consumers,
    and then start producing to the new category, which can result in entity discovery for remote
    consumers (remote consumers who consume both the old and new categories will not see any loss
    or discovery). Each producer entity can have up to 32 different replication groups each of which
    can use a different category so you must specify which group is being set. Your categorization
    policy will inform you as to which groups are used for what purpose.

    @param id The entity to set a replication category for.
    @param group The replication group to set the Category for.
    @param cat The replication Category to produce into for the specified entity and group.
    @return True if the specified entity is a valid producer entity which uses the specified
        replication group.
*/
EE_EONENTRY bool SetReplicationCategory(
    egf::EntityID id,
    efd::UInt32 group,
    efd::Category cat);

/**
    Determines if the given entity uses the specified replication channel for any replication group.
    This can be called on either the producer entity or on a replica of that entity.

    @param entityID The entity to check.
    @param catID The Category to check for use.
    @return True if the given entity is found and uses the specified category for any replication
        group.
*/
EE_EONENTRY bool UsesReplicationCategory(egf::EntityID entityID, efd::Category catID);

//@}

/**
    Set the default minimum update interval for a replication group. Changing this value will
    effect all entities that are using the specified group starting on the next update pass.

    @param group The replication group to set the update interval for.
    @param newDelta The new minimum update delta in seconds.
*/
EE_EONENTRY void SetGroupUpdateInterval(
    efd::UInt32 group,
    efd::TimeType newDelta);

} // end namespace bapiOnline

#endif // !defined(EE_BAPIONLINE)
