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
#ifndef EE_BEHAVIOR_DESCRIPTOR_H
#define EE_BEHAVIOR_DESCRIPTOR_H

#include <egf/EntityID.h>
#include <egf/EventID.h>
#include <efd/StdContainers.h>
#include <efd/DynamicModule.h>
#include <efd/RefCount.h>
#include <egf/EntityTypes.h>

namespace efd
{
// Forward declaration:
class ParameterList;
}
namespace egf
{
// Forward declaration:
class Entity;

/**
    Define a behavior "C function" type.

    This typedef defines the calling protocol (and function pointer) for all "C" callable behavior
    script functions.

    @note Calling sequence is a single argument (a binary stream pointer).
*/
typedef void (*CBehaviorFunc)(egf::Entity*, efd::ParameterList*);

/// Implementation class for a behavior definition.
class EE_EGF_ENTRY BehaviorDescriptor : public efd::RefCount
{
public:
    /// Define an invocation-ordered model list.
    typedef efd::list<efd::utf8string> InvocationOrderedModelNamesList;

    /**
        Constructor.

        @param i_idBehavior ID of the behavior.
        @param i_strName Name of the behavior.
        @param i_strSource Name of the original model that contains this behavior (used to
            determine module, DLL/SO, or built-in model containing the behavior method).
        @param i_BehaviorType Behavior types of the behavior.
        @param i_traits Traits flags for the behavior.
    */
    BehaviorDescriptor(
        BehaviorID i_idBehavior,
        const efd::utf8string& i_strName,
        const efd::utf8string& i_strSource,
        BehaviorTypes i_BehaviorType,
        efd::UInt32 i_traits = BehaviorTrait_None);

    /**
        Copy Constructor.

        @param i_other Behavior descriptor being copied.
    */
    BehaviorDescriptor(const BehaviorDescriptor& i_other);

protected:
    // Protected destructor.
    ~BehaviorDescriptor();

public:
    /**
        Prepares the behavior to be invoked.

        For C/C++ behaviors, these steps involve loading the DLL/SO that implements the methods.
        For built-in behaviors, these steps involve verifying that the given BuiltinModel name is
        valid.  (It does not guarantee that any given entity actually has that built-in model
        mixed in.)  For remote behaviors, this function has no effect.

        @return True if the behavior is ready for execution (or is remote).
    */
    bool Initialize();

    /**
        Get the ID for this behavior.

        @return 32-bit unsigned integer used for behavior ID.
    */
    BehaviorID GetID() const;

    /**
        Get a pointer to the name for this behavior.

        @return Name of this behavior.
    */
    const efd::utf8string& GetName() const;

    /**
        Get a pointer to the original model name where this behavior was defined.

        @note This name is not the flat model name, but the original model name.

        @return Name of the model for this behavior.
    */
    const efd::utf8string& GetModelName() const;

    /**
        Set the original model name.

        @note This name is not the flat model name, but the original model name.

        @param modelName Name of the model for this behavior.
    */
    void SetModelName(const efd::utf8string& modelName);

    /**
        Get the script type for this behavior

        @return Enumerated type for this behavior (C, Python, etc.).
    */
    BehaviorTypes GetType() const;

    /**
        Set the script type for this behavior.

        @param i_newType Enumerated type for this behavior (C, Python, etc.).
    */
    void SetType(BehaviorTypes i_newType);

    /**
        Get a string name for the behavior type.  Only works with built-in behavior types.

        @return String representation of the BehaviorTypes value.
    */
    const char* GetTypeName() const;

    /**
        Retrieves the value of the specified trait.

        @param trait Trait to check.
        @return Indicates whether the behavior possesses the trait (true or false).
    */
    efd::Bool GetTrait(BehaviorTraits trait) const;

    /**
        Retrieves all traits as a 32-bit bitfield.

        Useful for testing the equality of the traits between two different BehaviorDescriptors.

        @return 32-bit bitfield representing all traits.
    */
    efd::UInt32 GetTraits() const;

    /**
        Sets the value of the specified trait.

        @note It is undefined behavior to set a trait after simulation has begun.

        @param trait Trait whose value is being set.
        @param val Value of the trait.
    */
    void SetTrait(BehaviorTraits trait, efd::Bool val);

    /**
        Get the pointer to the "C" function for this behavior (if it exists).

        @return Pointer to the "C" DLL function for this behavior (if it exists).
    */
    CBehaviorFunc GetCFunctionPtr() const;

    /*!
        Verifies that all data fields contain valid data, and no illegal trait or type
        combinations have been specified.

        @return True if all data fields contain valid data; false otherwise.
    */
    bool IsValid() const;

    /**
        Get a reference to the behavior's invocation order list.

        @return Reference to the behavior's invocation order list.
    */
    const InvocationOrderedModelNamesList& GetInvocationOrderedModelNames() const;

    /**
        Add a model name to the behavior's invocation order list.

        @param modelName Model name to be added to the behavior's invocation order list.
    */
    void AddInvocationOrderedModelName(const efd::utf8string& modelName);

    /**
        Clear the behavior's invocation order list. This is used when adapting traits during model
        parsing when we detect that the invocation list will not be required.
    */
    void ClearInvocationOrderList();

    /**
        Add a C/C++ behavior function pointer to the static map of model/behavior name behavior
        function pointers.

        @param modelName Name of the model for which to register a behavior function pointer.
        @param behaviorName Name of the behavior for which to register a behavior function
            pointer.
        @param behaviorFunction Behavior function pointer to register.
        @return True if behavior function pointer was successfully added to the static map; false
            otherwise.
    */
    static bool AddStaticBahavior(
        const efd::utf8string& modelName,
        const efd::utf8string& behaviorName,
        CBehaviorFunc behaviorFunction);

    /**
        Get a C/C++ behavior function pointer out of the static map of model/behavior name
        behavior function pointers.

        @param modelName Name of the model registered.
        @param behaviorName Name of the behavior registered.
        @return Behavior function pointer registered, or NULL if none found.
    */
    static CBehaviorFunc GetStaticBehavior(
        const efd::utf8string& modelName,
        const efd::utf8string& behaviorName);

    /// @cond EMERGENT_INTERNAL

    static void _SDMInit();
    static void _SDMShutdown();

    /// @endcond
protected:
    /// Helper for generating memory leak reports
    static void LeakDump(void* pMem, char* o_buffer, unsigned int i_cchBuffer);

    /// Behavior ID.
    BehaviorID m_behaviorID;

    /// Flags for the behavior traits.
    efd::UInt32 m_traits;

    /// Name of this behavior.
    efd::utf8string m_name;

    /// Name of the model implementing this behavior.
    efd::utf8string m_modelName;

    /// Type of this behavior (Python, C, etc.).
    BehaviorTypes m_type;

    /// Behavior's invocation-ordered model list, used only for extends style behaviors.
    InvocationOrderedModelNamesList m_invocationOrderedModelNames;

    /// Reference to the module that implements this behavior (C/C++ behaviors only).
    /// For C/C++ behaviors, we load them from a shared object/DLL. In order to be able to unload
    /// and reload this module at run-time, we need to keep track of the module so we can later
    /// free it and hopefully have its ref-count reach zero.
    efd::DynamicModule m_source;

    /// Pointer to "C" callable behavior function in model DLL.
    CBehaviorFunc m_pBehaviorFunction;

    /// Static map of model/behavior name behavior function pointer, used for statically registered
    /// behavior functions.
    typedef efd::map<efd::utf8string, CBehaviorFunc> BehaviorMap;
    static BehaviorMap ms_behaviorMap;
};

/// Define a behavior descriptor smart pointer.
typedef efd::SmartPointer<BehaviorDescriptor> BehaviorDescriptorPtr;

} // end namespace egf

#endif  // EE_BEHAVIOR_DESCRIPTOR_H
