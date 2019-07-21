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
#ifndef EE_ENTITYTYPES_H
#define EE_ENTITYTYPES_H

#include <efd/UniversalTypes.h>
#include <efd/RefCount.h>
#include <efd/Serialize.h>
#include <egf/egfLibType.h>

// NOTE: This file is directly bound into SWIG.  Do not place complexe data or code that should
// not be exposed to scripting in this file.

namespace egf
{
    /// @name Definitions from EntityTypes.h
    //@{

    /// Unique identifier for FlatModel instances
    typedef efd::UInt32 FlatModelID;
    static const FlatModelID kFlatModelID_INVALID = 0;

    /// Unique identifier for PropertyDescriptor instances
    typedef efd::UInt32 PropertyID;
    static const PropertyID kPropertyID_INVALID = 0;

    /// Unique identifier for BehaviorDescriptor instances
    typedef efd::UInt32 BehaviorID;
    static const BehaviorID kBehaviorID_INVALID = 0;

    /**
        Model Traits enum.  These are used by FlatModel and BuiltinModelDescriptor.
        Each value must be a power of 2.
    */
    enum ModelTraits
    {
        /// The value when no traits have been set
        ModelTrait_None,

        /// The model is expected to run behaviors (is active)
        ModelTrait_Active        = 0x01,

        /// The model represents an IBuiltinModel implementation that should be created on the
        /// owned instance of the entity. Any properties added to this model will be built-in
        /// properties exported from the IBuiltinModel implementation.
        ModelTrait_BuiltinModel     = 0x04,

        /// The model represents an IBuiltinModel implementation that should be created on the
        /// replicated instances of this entity. This trait can be combined with BuiltinModel
        /// to use a built-in model for both producers and consumers. This trait has no effect
        /// when replication is not being used.
        ModelTrait_ReplicaBuiltinModel = 0x08,

        /// The model is a built-in model for replicated entities on the server and a normal
        /// model on clients. Must be combined with ReplicaBuiltinModel. The efd::ServiceManager
        /// program type must be set to indicate whether the process is considered a server.
        /// Eventually the tools will create separate versions of the model data for client and
        /// server which will make this trait obsolete.
        ModelTrait_ServerOnlyReplicaBuiltinModel = 0x08000000,

        /// The model is a built-in model for replicated entities on clients. Must be combined
        /// with ReplicaBuiltinModel. The efd::ServiceManager program type must be set to
        /// indicate whether the process is considered a client. Eventually the tools will create
        /// separate versions of the model data for client and server which will make this trait
        /// obsolete.
        ModelTrait_ClientOnlyReplicaBuiltinModel = 0x10000000,

        /// The model is a built-in model on the server and a normal model on clients. Must be
        /// combined with BuiltinModel. The efd::ServiceManager program type must be set to
        /// indicate whether the process is considered a server. Eventually the tools will create
        /// separate versions of the model data for client and server which will make this trait
        /// obsolete.
        ModelTrait_ServerOnlyBuiltinModel    = 0x20000000,

        /// The model is a built-in model on clients and a normal model on the server. Must be
        /// combined with BuiltinModel. The efd::ServiceManager program type must be set to
        /// indicate whether the process is considered a client. Eventually the tools will create
        /// separate versions of the model data for client and server which will make this trait
        /// obsolete.
        ModelTrait_ClientOnlyBuiltinModel    = 0x40000000,

        /// I'm a built-in model even when run inside a tool.  Normally nothing is a built-in
        /// model when run inside a tool even if the client and server traits otherwise match.
        /// It should be very rare to use this trait as requiring built-in models inside a tool
        /// can create difficult dependencies.  Must be combined with ModelTrait_BuiltinModel.
        ModelTrait_ToolBuiltinModel          = 0x80000000,
    };


    /// Traits of a property, used by PropertyDescriptor.  Each value must be a power of 2.
    enum PropertyTraits
    {
        /// The value when no traits have been set
        PropertyTrait_None            = 0,

        /// Can only be read, not written to.
        PropertyTrait_ReadOnly        = 0x0001,

        /// Only available on the original entity, not on replicas.
        /// @note This trait is not yet implemented so it currently does nothing.
        PropertyTrait_Private         = 0x0002,

        /// Must be persisted to the database when the entity is stored
        PropertyTrait_Persisted       = 0x0004,

        /// The property is exported from a built-in model which is responsible for its in-memory
        /// storage.
        /// @note The default value is still stored as an IProperty.
        PropertyTrait_FromBuiltinModel   = 0x0008,

        /// The property is exported from a replica built-in model which is responsible for its
        /// in-memory storage.
        /// @note The default value is still stored as an IProperty.
        PropertyTrait_FromReplicaBuiltinModel = 0x0010,

        /**
            Can be written to when not owned.  This does not override ReadOnly but it does
            allow properties to be written on replicated entities.  Note that changes to a
            replicated entity are local only and will NOT be updated on other replicated copies
            of the entity or synchronized back to the original entity.  A Mutable property can
            be written to as normal when it is owned and such updates will replicate as normal
            which will over write any changes made to the mutable copy.
        */
        PropertyTrait_Mutable         = 0x0020,

        /**
            This property is for use by the server only.  It will be completely stripped from
            the client's view.  ServerOnly properties can reflect to other servers but must not
            be reflected to the client as the client will not understand the property.
        */
        PropertyTrait_ServerOnly      = 0x40000000,

        /**
            This property is for use by the client only.  It will be completely stripped from
            the server's view.  This can be used for client side decorative entities or for
            mutable properties on reflected entities.
        */
        PropertyTrait_ClientOnly      = 0x80000000,

    };


    /// Traits used for BehaviorsDescriptors.  Each value must be a power of 2.
    enum BehaviorTraits
    {
        /// The value when no traits have been set
        BehaviorTrait_None = 0,

        /// The behavior can only run on the original entity, not on any replicas of that entity.
        BehaviorTrait_Private = 0x0001,

        /// The behavior can only run in a process that is viewing the entity. To view the entity
        /// means that the ReplicationService is consuming a replication category to which this
        /// entity is producing a replication group. This often means the behavior will run on a
        /// replica of the original entity, but the process containing the original entity may also
        /// be viewing the entity. Because this often runs on replica entities view behaviors
        /// should only write to mutable properties.
        BehaviorTrait_ViewOnly = 0x0008,

        /// This behavior will never attempt to block (always executes as a one-shot).  Any
        /// call to a blocking API will fail.
        BehaviorTrait_NoBlock = 0x0010,

        /// This behavior uses the 'extends' invocation order policy, in which mixed-in
        /// implementations of the behavior are also called. The order in which the mixed-in
        /// implementations will be invoked is specified in the flat model and depends on the
        /// priorities of the mixed-in models.
        BehaviorTrait_Extends = 0x0020,

        /// This behavior is allowed to be Immediately invoked. Immediate also implies NoBlock
        /// and the FlatModel parser will automatically set NoBlock when it sees this trait. This
        /// does not prevent the behavior from being run normally, but this trait is required in
        /// order to be called immediately. Be careful not to do too much work in an immediate
        /// behavior as it might effect your framerate
        BehaviorTrait_Immediate = 0x0040,

        /// This behavior is only allowed to run when the Entity is in the world. Any attempt to
        /// run a behavior with trait before the Entity has entered the world or after the Entity
        /// has exited the world will fail.
        BehaviorTrait_InWorldOnly = 0x0080,

        /// Only executed on the server; completely removed on the client.
        BehaviorTrait_ServerExecOnly = 0x10000000,

        /// Only executed on the client; completely removed on the server.
        BehaviorTrait_ClientExecOnly = 0x20000000,

        /**
        If the behavior is BehaviorTrait_ServerExecOnly or BehaviorTrait_ClientExecOnly,
        and the BehaviorTrait_RemotelyVisible trait is set, then the behavior will have
        its type switched to Remote on a non-matching program type.  This allows the name
        and ID of the behavior to be mapped in order to pass in an EventMessage.

        Without this trait the default behavior is to completely remove behaviors with
        a non-matching program type.  This trait has no effect unless it is combined with
        BehaviorTrait_ServerExecOnly or BehaviorTrait_ClientExecOnly.
        */
        BehaviorTrait_RemotelyVisible = 0x40000000,

        /// This behavior has been initialized; it is for internal use only.
        BehaviorTrait_Init = 0x80000000,
    };

    /// Behavior execution types.
    enum BehaviorTypes
    {
        /// Invalid behavior execution type.
        BehaviorType_Invalid,

        /// "C" code.
        BehaviorType_C,

        /// "C++" code.
        BehaviorType_Cpp,

        /// Implemented via IBuiltinModel::Dispatch().
        BehaviorType_Builtin,

        /// Behavior lives remotely; we only know about its name and ID.
        BehaviorType_Remote,

        /// Behavior is not implemented by the current model, but is by a supermodel. The
        /// BehaviorDescriptor will specify an invocation list describing what actual methods are
        /// invoked for this behavior.
        BehaviorType_Virtual,

        /// Lua script.
        BehaviorType_Lua,

        /// Python script.
        BehaviorType_Python,

        /// Behavior does not actually exist, but is provided in tools so that mixed-in classes
        /// can override. These should not appear in flat models but are stripped out if they do
        /// appear.
        BehaviorType_Abstract,
    };

    //@}

} // end namespace egf

EE_SPECIALIZE_ENUM(egf::ModelTraits, efd::UInt32);
EE_SPECIALIZE_ENUM(egf::PropertyTraits, efd::UInt32);
EE_SPECIALIZE_ENUM(egf::BehaviorTraits, efd::UInt32);
EE_SPECIALIZE_ENUM(egf::BehaviorTypes, efd::UInt16);

#endif // EE_ENTITYTYPES_H
