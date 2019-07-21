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
#ifndef EE_GAMEFRAMEWORK_H
#define EE_GAMEFRAMEWORK_H

// All headers for the Game Framework library are included here.
// For ease of use if another module uses Game Framework. And use of the PCH.

#include <egf/bapiBlock.h>
#include <egf/bapiConfig.h>
#include <egf/bapiEntity.h>
#include <egf/bapiInternal.h>
#include <egf/BehaviorAPI.h>
#include <egf/BehaviorDescriptor.h>
#include <egf/BreakpointMessages.h>
#include <egf/BuiltinModelDescriptor.h>
#include <egf/BuiltinModelHelper.h>
#include <egf/egfBaseIDs.h>
#include <egf/egfClassIDs.h>
#include <egf/egfLibType.h>
#include <egf/egfLogIDs.h>
#include <egf/egfMessageIDs.h>
#include <egf/egfPropertyIDs.h>
#include <egf/egfSDM.h>
#include <egf/egfSystemServiceIDs.h>
#include <egf/Entity.h>
#include <egf/EntityChangeMessage.h>
#include <egf/EntityFactory.h>
#include <egf/EntityFactoryRequest.h>
#include <egf/EntityFactoryResponse.h>
#include <egf/EntityID.h>
#include <egf/EntityIDFactory.h>
#include <egf/EntityLoaderMessages.h>
#include <egf/EntityLoaderService.h>
#include <egf/EntityManager.h>
#include <egf/EntitySetLoadState.h>
#include <egf/EntityTypes.h>
#include <egf/EventID.h>
#include <egf/EventMessage.h>
#include <egf/ExtraData.h>
#include <egf/FlatModel.h>
#include <egf/FlatModelFactory.h>
#include <egf/FlatModelFactoryRequest.h>
#include <egf/FlatModelFactoryResponse.h>
#include <egf/FlatModelManager.h>
#include <egf/GamePauseRequest.h>
#include <egf/GameResumeRequest.h>
#include <egf/GameTimeClock.h>
#include <egf/IBuiltinModel.h>
#include <egf/IBuiltinModelImpl.h>
#include <egf/ICppAPI.h>
#include <egf/IProperty.h>
#include <egf/IPropertyType.h>
#include <egf/ISchedulerScripting.h>
#include <egf/IScriptFactory.h>
#include <egf/NotificationService.h>
#include <egf/PendingBehavior.h>
#include <egf/PrimitiveProperties.h>
#include <egf/PropertyDescriptor.h>
#include <egf/RapidIterationService.h>
#include <egf/SAXBlockParser.h>
#include <egf/SAXEntityParser.h>
#include <egf/SAXModelParser.h>
#include <egf/ScheduledTask.h>
#include <egf/Scheduler.h>
#include <egf/SchedulerQueue.h>
#include <egf/ScriptContext.h>
#include <egf/ScriptFactoryRequest.h>
#include <egf/ScriptFactoryResponse.h>
#include <egf/StandardModelLibraryBehaviorIDs.h>
#include <egf/StandardModelLibraryFlatModelIDs.h>
#include <egf/StandardModelLibraryPropertyIDs.h>
#include <egf/TProperty.h>
#include <egf/UtilityProperties.h>
#include <egf/WorldFactory.h>
#include <egf/WorldFactoryRequest.h>
#include <egf/WorldFactoryResponse.h>
#include <egf/WorldResetRequest.h>

#endif
