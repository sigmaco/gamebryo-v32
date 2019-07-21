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
#ifndef EE_VISUALIZERCONNECTIONTRACKER_H
#define EE_VISUALIZERCONNECTIONTRACKER_H

#include <egf/Entity.h>
#include <egf/EntityID.h>
#include <ecr/ecrSystemServiceIDs.h>
#include "IPropertyVisualizer.h"
#include "egmVisualizersLibType.h"

namespace egmVisualizers
{

/**
    Class used by the PropertyVisualizationService and some of the property visualizers
    to track visualizers that rely on multiple entities ('connections').
*/
class EE_EGMVISUALIZERS_ENTRY VisualizerConnectionTracker : public efd::MemObject
{
    EE_DECLARE_CONCRETE_REFCOUNT;

public:

    /**
        Default constructor.
    */
    VisualizerConnectionTracker();

    /**
        Gets a list of all the visualizers referencing a specific entity.  This list
        does not include the visualizers that are attached directly to the entity.
        @param entityID The entity ID.
        @param connections A list of all the visualizers referencing the desired entity.
    */
    void GetConnections(
        egf::EntityID entityID,
        efd::list<IPropertyVisualizerPtr> &connections);

    /**
        Gets a list of all the visualizers which should be connected to an entity,
        but the desired entity hasn't been discovered yet.
        @param connections A list of visualizers still missing their connected entities.
    */
    void GetUnresolvedConnections(
        efd::list<IPropertyVisualizerPtr> &connections);

    /**
        Add a connection to this tracker.
        @param entityID The entity ID for the entity being connected.
        @param spVisualizer The visualizer establishing the connection.
    */
    void AddConnection(
        egf::EntityID entityID,
        IPropertyVisualizerPtr spVisualizer);

    /**
        Remove a connection from this tracker.
        @param entityID The entity ID for the entity being disconnected.
        @param spVisualizer The visualizer that no longer needs the connection.
    */
    void RemoveConnection(
        egf::EntityID entityID,
        IPropertyVisualizerPtr spVisualizer);

    /**
        Prepares an entity for upcoming removal from the tracker.  This allows
        visualizers using the tracker to know that the entity is being removed
        even though it hasn't been removed from the EntityManager yet.  Thus,
        a visualizer can be given an opportunity to free up any links to an entity.
        @param entityID The entity ID.
    */
    void SetupEntityForRemoval(egf::EntityID entityID);

    /**
        Returns whether a given entity is in the process of being removed.
        @param entityID The entity ID.
        @return Whether the entity is being removed or not.
    */
    bool IsEntityBeingRemoved(egf::EntityID entityID);

    /**
        Removes an entity setup for removal via SetupEntityForRemoval from
        this tracker.  This will break all connections between the entity
        and any visualizers that may want to use it.
    */
    void RemoveEntity();
private:

    /// Discovered connections between a visualizer and entities that the visualizer doesn't
    /// 'directly' effect.
    efd::map<egf::EntityID, efd::list<IPropertyVisualizerPtr> > m_connectionMap;

    egf::EntityID m_removing;
};

}

#endif
