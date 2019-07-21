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
#ifndef EE_BUILTINMODELDESCRIPTOR_H
#define EE_BUILTINMODELDESCRIPTOR_H

#include <efd/UniversalTypes.h>
#include <efd/RefCount.h>
#include <egf/egfLibType.h>
#include <egf/EntityTypes.h>
#include <efd/BitUtils.h>
#include <efd/utf8string.h>

namespace egf
{

/**
    @class BuiltinModelDescriptor

    @brief A data based description of a built-in model

    Built-in models provide a method for implementing models as C++ objects as opposed to
    generic property bags.  The BuiltinModelDescriptor is created when parsing the FlatModel
    definition of an entity that uses built-in models.  Built-in models are also models but when
    loading a model that mixes in built-in models we don't need the complete FlatModel description
    for the built-in so a simplified BuiltinModelDecriptor is used instead.  This description
    can be created from the derived Flat Model without having to also load the built-in model's
    Flat Model.

    When an Entity is created from a FlatModel a list is generated of all the built-in models
    that are mixed in.  This list is then used to factory the correct C++ objects to implement
    these built-in models.
*/
class EE_EGF_ENTRY BuiltinModelDescriptor : public efd::RefCount
{
public:

    /// Constructor
    BuiltinModelDescriptor();

    /// Copy constructor
    BuiltinModelDescriptor(const BuiltinModelDescriptor& other);

    /// Assignment operator
    BuiltinModelDescriptor& operator=(const BuiltinModelDescriptor& other);


    /**
        Retrieves the ID of the built-in model.  The ID of a built-in model is identical to the
        ID of the FlatModel that defines the built-in model.

        @return FlatModelID The FlatModelID for this built-in model
    */
    FlatModelID GetID() const;

    /**
        Sets the built-in model's ID.  This should only be called during FlatModel parsing by the
        parser itself.  Calling this at any other time will have undefined results.

        @param propID The FlatModelID
    */
    void SetID(FlatModelID propID);

    /**
        Retrieves the name of the built-in model.  The name of a built-in model is identical to
        the name of the model that defines the built-in model.  This is also the name used by the
        built-in model factory to create the built-in model.

        @return utf8string The Name
    */
    const efd::utf8string& GetName() const;

    /**
        Sets the name of the BuiltinModel.  This should only be called during FlatModel parsing
        by the parser itself.  Calling this at any other time will have undefined results.

        @param name The Name
    */
    void SetName(const efd::utf8string& name);

    /**
        Retrieves the value of the specified trait.  Certain traits are needed to know when
        the BuiltinModel object should be used.  In a client-server setting BuiltinModel objects
        can be client-only, server-only, replication-only, master-only, or any combination thereof.
        These traits are the same traits that FlatModel definitions use.

        @note The traits for the BuiltinModelDescriptor may not exactly match the traits for the
        matching FlatModel that defines the same BuiltinModel.  Only the BuiltinModel-related traits
        are guaranteed to be set in the BuiltinModelDescriptor.

        @param trait The trait to check for.
        @return Bool True if the request trait is set, false otherwise
    */
    efd::Bool GetTrait(ModelTraits trait) const;

    /**
        Sets the value of the specified trait.  This should only be called during FlatModel
        parsing by the parser itself.  Calling this at any other time will have undefined
        results.

        @param trait The trait to set
        @param val Value of the trait
    */
    void SetTrait(ModelTraits trait, efd::Bool val);

protected:

    /// Destructor.  Protected, use RefCount
    ~BuiltinModelDescriptor();

    /// BuiltinModel objects have a unique name and id (they are models, after all) that uniquely
    /// identify them.  Note that for any BuiltinModel there is also a FlatModel of the same name,
    /// the BuiltinModel descriptor only contains a small subset of the data the full flat model
    /// would contain.  This allows us to avoid ever loading the full FlatModel in most cases.
    //@{
    efd::utf8string m_name;
    FlatModelID m_id;
    //@}

    /// The traits of the BuiltinModel are also needed.  These don't exactly match the traits for
    /// the full FlatModel itself because BuiltinModel objects only care about the BuiltinModel
    /// related traits (kBuiltinModel, kReplicaBuiltinModel, and the client-only/server-only
    /// modifiers).
    efd::UInt32 m_traits;
};


/// A SmartPointer to a BuiltinModelDescriptor.  Used to assist in reference counting.
typedef efd::SmartPointer<BuiltinModelDescriptor> BuiltinModelDescriptorPtr;

/// Used to describe to an Entity all the BuiltinModel classes that it requires.  The FlatModel
/// can generate this list from its data.
typedef efd::list< BuiltinModelDescriptor* > BuiltinModelList;


//--------------------------------------------------------------------------------------------------
} // end namespace egf


//--------------------------------------------------------------------------------------------------
#include <egf/BuiltinModelDescriptor.inl>


#endif // EE_BUILTINMODELDESCRIPTOR_H
