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
#ifndef EE_INPUTHANDLER_H
#define EE_INPUTHANDLER_H

#include "ecrInputLibType.h"
#include "StandardModelLibraryBehaviorIDs.h"
#include "StandardModelLibraryFlatModelIDs.h"
#include "StandardModelLibraryPropertyIDs.h"

#include <ecr/ecrClassIDs.h>
#include <egf/Entity.h>
#include <egf/BuiltinModelHelper.h>
#include <ecrInput/InputService.h>


namespace ecrInput
{


/**
    A model that binds Input Events to behaviors.  By setting the properties of this model you
    can automatically bind input events from the action map to specifically named behaviors.
    Changing the properties communicates to the ecrInput::InputService to configure the
    necessary behavior callbacks.
*/
class EE_ECRINPUT_ENTRY InputHandler : public egf::IBuiltinModelImpl
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(InputHandler, efd::kCLASSID_InputHandler, egf::IBuiltinModelImpl);
    EE_DECLARE_CONCRETE_REFCOUNT;

public:
    /// @name Normal Event map accessors
    /// These accessors automatically call into the InputService whenever elements are added or
    /// removed from the m_NormalEvents map.
    //@{
    egf::PropertyResult GetNormalEvent(
        const efd::utf8string& i_key,
        efd::utf8string& o_value) const;
    void SetNormalEvent(const efd::utf8string& i_key, const efd::utf8string& i_value);
    egf::PropertyResult RemoveNormalEvent(const efd::utf8string& key);
    efd::UInt32 GetNormalEventSize() const;
    void GetNextNormalEventKey(const efd::utf8string& i_prevKey,
        efd::utf8string& o_nextKey) const;
    void ClearNormalEvents();
    //@}

    /// @name Immediate Event map accessors
    /// These accessors automatically call into the InputService whenever elements are added or
    /// removed from the m_NormalEvents map.
    //@{
    egf::PropertyResult GetImmediateEvent(const efd::utf8string& i_key,
        efd::utf8string& o_value) const;
    void SetImmediateEvent(const efd::utf8string& i_key, const efd::utf8string& i_value);
    egf::PropertyResult RemoveImmediateEvent(const efd::utf8string& key);
    efd::UInt32 GetImmediateEventSize() const;
    void GetNextImmediateEventKey(const efd::utf8string& i_prevKey,
        efd::utf8string& o_nextKey) const;
    void ClearImmediateEvents();
    //@}

    /// @name InputHander.InputsEnabled accessors
    /// Whenever the value of InputsEnabled changes calls are made to the InputService to add
    /// or remove our behavior bindings.
    //@{
    bool GetInputsEnabled() const;
    void SetInputsEnabled(const bool& value);
    //@}

    EE_DECLARE_BUILTINMODEL_PROPERTIES

    EE_BUILTINMODELASSOCPROPERTY_ACCESSOR(
        InputHandler,
        egf::kPropertyID_StandardModelLibrary_NormalEventMap,
        efd::utf8string,
        InputHandler,
        GetNormalEvent, SetNormalEvent,
        GetNormalEventSize, GetNextNormalEventKey,
        ClearNormalEvents, RemoveNormalEvent);

    EE_BUILTINMODELASSOCPROPERTY_ACCESSOR(
        InputHandler,
        egf::kPropertyID_StandardModelLibrary_ImmediateEventMap,
        efd::utf8string,
        InputHandler,
        GetImmediateEvent, SetImmediateEvent,
        GetImmediateEventSize, GetNextImmediateEventKey,
        ClearImmediateEvents, RemoveImmediateEvent);

    EE_BUILTINMODELPROPERTY_ACCESSOR(
        InputHandler,
        egf::kPropertyID_StandardModelLibrary_InputsEnabled,
        efd::Bool,
        InputHandler,
        GetInputsEnabled, SetInputsEnabled)

    EE_END_BUILTINMODEL_PROPERTIES
    /// @endcond

public:

    /// Constructor
    InputHandler();

    /// Destructor
    virtual ~InputHandler();

    /// We respond to lifecycle_OnEntitySetFinished in order to setup our initial input bindings
    /// and to lifecycle_OnDestroy to disable our input bindings.
    virtual void OnEndLifecycle(efd::UInt32 lifecycle);

    /// Allocates an instance of this class
    static egf::IBuiltinModel* Factory();

protected:
    typedef EE_STL_NAMESPACE::pair<efd::utf8string, efd::UInt32> EventMapData;
    typedef efd::map<efd::utf8string, EventMapData> EventMap;

    efd::UInt32 RegisterBehavior(ecrInput::InputService::CallbackType type,
        const efd::utf8string& eventName,
        const efd::utf8string& behaviorName);
    void UnregisterBehavior(EventMapData& io_data);
    void EnableAllEvents();
    void DisableAllEvents();

    EventMap m_NormalEvents;
    EventMap m_ImmediateEvents;
    bool m_enableInput;

    ecrInput::InputService* m_pInputService;
};

typedef efd::SmartPointer<InputHandler> InputHandlerPtr;

} // end namespace ecrInput

#endif // EE_INPUTHANDLER_H
