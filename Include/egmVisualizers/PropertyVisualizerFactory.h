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
#ifndef EE_PROPERTYVISUALIZERFACTORY_H
#define EE_PROPERTYVISUALIZERFACTORY_H

#include <efd/RefCount.h>
#include <egf/egfLibType.h>
#include <egf/Entity.h>
#include <egf/ExtraData.h>
#include <ecr/SceneGraphService.h>
#include <NiMesh.h>
#include <NiCamera.h>
#include <efd/ServiceManager.h>
#include <egmVisualizers/IPropertyVisualizer.h>
#include "VisualizerConnectionTracker.h"
#include "VisualizerVisibilityTracker.h"

namespace egmVisualizers
{

/**
    Visualizer factory.

    This is a static class for factory creation functions.
*/
class EE_EGMVISUALIZERS_ENTRY PropertyVisualizerFactory : public efd::MemObject
{
public:
    /**
        Creates a specific property visualizer based on the extra data passed in.

        @param spVisualizerExtraData the extra data that drives the property visualizers.
        @param pEntityManager the entity manager which can be used to lookup all the entities.
        @param pConnectionTracker tracker keeping track of visualizer connections
        @param pVisibilityTracker tracker keeping track of entity visibility
    */
    IPropertyVisualizerPtr CreatePropertyVisualizer(
        egf::ExtraDataPtr spVisualizerExtraData,
        egf::EntityManager* pEntityManager,
        VisualizerConnectionTracker* pConnectionTracker,
        VisualizerVisibilityTracker* pVisibilityTracker);
};

} // namespace

#endif
