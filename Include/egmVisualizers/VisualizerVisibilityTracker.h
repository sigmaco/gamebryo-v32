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
#ifndef EE_VISUALIZERVISIBILITYTRACKER_H
#define EE_VISUALIZERVISIBILITYTRACKER_H

#include <egf/Entity.h>
#include <egf/EntityID.h>
#include <ecr/ecrSystemServiceIDs.h>
#include "egmVisualizersLibType.h"

namespace egmVisualizers
{

/**
    Class used by the PropertyVisualizationService and some of the property visualizers
    to track if an entity is invisible so that the service can make the visualizer invisible
    in response.
*/
class EE_EGMVISUALIZERS_ENTRY VisualizerVisibilityTracker : public efd::MemObject
{
    EE_DECLARE_CONCRETE_REFCOUNT;

public:

    /**
        Set entity visibility.  Note that this does not affect the entity itself, but is
        instead bookkeeping for objects of this class.
        Since there can be multiple sources changing the visibility of an entity, we need
        to keep track of each source and whether it has set the entity to visible/invisible.
        If ANY source marks the entity as invisible, the entity should be invisible and so
        should its property visualizers.
        @param entityID The entity whose visibility has changed.
        @param source The source of the visibility change.  This should be a unique string.
        @param category An extra integer ID that the source can pass in if it changes the entity
            visibility in multiple ways.  For instance, ToolSceneService uses 0 for when
            a button is pressed or 1 for when an entire layer is made invisible.
            This number must be between 0 and 31 and must be unique within the source.
        @param isVisible Whether the entity is visible or not.
    */
    void SetEntityVisibility(egf::EntityID entityID,
        const efd::utf8string& source,
        efd::UInt32 category,
        bool isVisible);

    /**
        Returns whether an entity is visible or not, evaluating all the different sources
        that could turn an entity invisible for its final determination.
        @param entityID The entity ID.
        @return Whether the entity is visible or not.
    */
    bool IsEntityVisible(egf::EntityID entityID);

private:

    // Keep track of entity visibility so we can turn on/off visualizer visibility
    // We're using a map of bitflags (where each bit represents a different action that turned
    // the entity invisible); a 0 means that the entity is completely visible.
    efd::map<egf::EntityID, efd::map<efd::utf8string, efd::UInt32> > m_entityVisibility;
};

}

#endif
