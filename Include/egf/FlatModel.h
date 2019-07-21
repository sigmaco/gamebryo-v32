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
#ifndef EE_FLATMODEL_H
#define EE_FLATMODEL_H

#include <efd/RefCount.h>
#include <egf/PropertyDescriptor.h>
#include <egf/BuiltinModelDescriptor.h>
#include <egf/egfLibType.h>
#include <egf/BehaviorDescriptor.h>
#include <egf/EntityTypes.h>
#include <egf/ExtraData.h>

#include <efd/GenericFactory.h>

namespace egf
{

class FlatModelManager;

/**
    Class encapsulating a flattened model.

    The flattened model contains all the properties and behaviors of models mixed in to it.
*/
class EE_EGF_ENTRY FlatModel : public efd::RefCount
{
    /**
        Allow the FMM to iterate over my protected members, otherwise we'd need to expose all
        sorts of iterator functionality.
    */
    friend class FlatModelManager;

public:

    /// Construction and Destruction
    FlatModel(FlatModelManager* pFlatModelManager);
    ~FlatModel();

    /// @name Identity methods
    //@{

    /**
        Get the name of the flat model

        @return Name of the model
    */
    const efd::utf8string& GetName() const;

    /**
        Set the name of the flat model

        @param name The name of the flat model
    */
    void SetName(const efd::utf8string& name);


    /**
        Get the id of the flat model

        @return ID of the flat model
    */
    FlatModelID GetID() const;


    /**
        Set the ID of the flat model

        @param id The ID of the flat model
    */
    void SetID(FlatModelID id);


    /**
        Retrieves the value of the specified trait

        @param trait The trait to check for
        @return Boolean indicating the value of the trait
    */
    efd::Bool GetTrait(ModelTraits trait) const;


    /**
        Retrieves all traits as a 32bit bitfield.  Useful for testing the equality or the
        traits between two different models

        @return UInt32 bitfield representing all traits.
    */
    efd::UInt32 GetTraits() const;


    /**
        Sets the value of the specified trait.  Note that it is undefined
        behavior of setting a trait after simulation has begun.

        @param trait The trait to set the value of
        @param val Value of the trait
    */
    void SetTrait(ModelTraits trait, efd::Bool val);

    //@}

    /// @name Property methods
    //@{

    /**
        Get the property descriptor for the given property name or ID

        @param propID The property ID to get the descriptor of

        @return PropertyDescriptor* Pointer to an IPropertyDescriptor
    */
    const PropertyDescriptor* GetPropertyDescriptor(PropertyID propID) const;

    /**
        Get the property descriptor for the given property name or ID

        @param name The property name to get the descriptor of

        @return PropertyDescriptor* Pointer to an IPropertyDescriptor
    */
    const PropertyDescriptor* GetPropertyDescriptor(const efd::utf8string& name) const;


    /**
        Checks whether the given property is contained in this model.

        @param propID The property ID to get the descriptor of

        @return bool True if the property exists in this model
    */
    bool ContainsProperty(PropertyID propID) const;

    /**
        Checks whether the given property is contained in this model.

        @param name The property name to get the descriptor of

        @return bool True if the property exists in this model
    */
    bool ContainsProperty(const efd::utf8string& name) const;


    /**
        Add a property descriptor to the flat model.  This will be called
        during initialization.  It is not advised to call this during runtime
        as modifying a model that's already in use could provide undefined
        behavior.

        @param i_pDescriptor A Property descriptor to add to this flat model.
        @return bool True is successfully added
    */
    bool AddPropertyDescriptor(PropertyDescriptor* i_pDescriptor);


    /**
        Gets a list of all the property names included in this model.

        @param[out] o_listOfNames A list to be filled with the property names.
    */
    void GetPropertyNames(efd::list<efd::utf8string>& o_listOfNames) const;


    /**
        Checks our membership in the given replication group.  This will be true if any property
        contained by this model replicates into the given group.

        @param index The group index to check, from 0 to 31
    */
    efd::Bool GetReplicationGroup(efd::UInt32 index) const;


    /**
        Get the replication groups that the model replicates into as a set of bit flags.

        @return UInt32 containing a set bit for each group applicable to the model
    */
    efd::UInt32 GetReplicationGroups() const;

    /**
        Calculate the difference between the properties in this flat model and the properties
        in another flat model. The result is 4 sets: unchanged properties, new properties,
        updated properties, and deleted properties.

        @param pOtherModel The other model to compare properties with.
        @param unchangedProperties set of property descriptor pointers for unchanged properties.
        @param newProperties set of property descriptor pointers for new properties.
        @param updatedProperties set of property descriptor pointers for updated properties.
        @param deletedProperties set of property descriptor pointers for deleted properties.
    */
    void DiffProperties(
        const egf::FlatModel* pOtherModel,
        efd::set<PropertyDescriptorPtr>& unchangedProperties,
        efd::set<PropertyDescriptorPtr>& newProperties,
        efd::set<PropertyDescriptorPtr>& updatedProperties,
        efd::set<PropertyDescriptorPtr>& deletedProperties) const;

    /**
    Calculate the difference between the mix-in models in this flat model and the mix-ins
    in another flat model.

    @param pOtherModel The other model to compare mix-ins with.
    @param addedMixins set of names of added mix-in models.
    @param deletedMixins set of names of deleted mix-in models.
    */
    void DiffMixins(
        const egf::FlatModel* pOtherModel,
        efd::set<efd::utf8string>& addedMixins,
        efd::set<efd::utf8string>& deletedMixins) const;

    //@}

    /// @name BuiltinModel methods
    //@{

    /**
        Returns the BuiltinModel Descriptor that an entity using this
        model must instantiate when it's created.

        @param i_BuiltinModelID The BuiltinModel model ID

        @return const pointer to a BuiltinModelDescriptor
    */
    const BuiltinModelDescriptor* GetBuiltinModelDescriptor(FlatModelID i_BuiltinModelID) const;

    /**
        Returns the BuiltinModel Descriptor that an entity using this
        model must instantiate when it's created.

        @param i_strBuiltinModelName The BuiltinModel name

        @return const pointer to a BuiltinModelDescriptor
    */
    const BuiltinModelDescriptor* GetBuiltinModelDescriptor(
        const efd::utf8string& i_strBuiltinModelName) const;


    /**
        Checks whether the given property is contained in this model.

        @param i_BuiltinModelID The BuiltinModel model ID

        @return bool True if the BuiltinModel exists in this model
    */
    bool ContainsBuiltinModel(FlatModelID i_BuiltinModelID) const;

    /**
        Checks whether the given property is contained in this model.

        @param i_strBuiltinModelName The BuiltinModel name

        @return bool True if the BuiltinModel exists in this model
    */
    bool ContainsBuiltinModel(const efd::utf8string& i_strBuiltinModelName) const;


    /**
        Add a BuiltinModel descriptor to the flat model.  This will be called
        during initialization.  It is not advised to call this during runtime
        as modifying a model that's already in use could provide undefined
        behavior.

        @param i_pDescriptor A BuiltinModel descriptor to add to this flat model.
        @return bool True if successful
    */
    bool AddBuiltinModelDescriptor(BuiltinModelDescriptor* i_pDescriptor);


    /**
        Retrieves a list of all the BuiltinModel objects that are required to instantiate an Entity
        of this FlatModel type.  Note that in the case of derived BuiltinModel objects only the
        most derived BuiltinModel is included in this list.

        @param[out] o_BuiltinModelList filled with the list of BuiltinModel objects used by this
        flat model
    */
    void GetRequiredBuiltinModelsList(BuiltinModelList& o_BuiltinModelList) const;

    /**
        Calculate BuiltinModel differences between two models. BuiltinModel objects that are in
        pOtherModel but not in this model are added BuiltinModel objects. BuiltinModel objects that
        are in this model but not in the other are deleted BuiltinModel objects.

        @param pOtherModel the model to compare against.
        @param addedBuiltinModels BuiltinModel objects found in other and not in this.
        @param deletedBuiltinModels BuiltinModel objects found in this and not in other.
    */
    void DiffBuiltinModels(
        const FlatModel* pOtherModel,
        efd::set<BuiltinModelDescriptorPtr>& addedBuiltinModels,
        efd::set<BuiltinModelDescriptorPtr>& deletedBuiltinModels) const;

    /**
        Generate a list of all the properties in this model that are sourced from the given
        BuiltinModel.

        @param i_pcd The BuiltinModel descriptor who's defaults are being requested
        @param[out] o_defaults The PropertyDescriptorList to be filled with all the default
            property descriptors for the given BuiltinModel.
    */
    void PrepareDefaultPropertyList(
        const BuiltinModelDescriptor* i_pcd,
        PropertyDescriptorList& o_defaults) const;

    //@}

    /// @name Behavior methods
    //@{

    /**
        Looks up a given behavior descriptor within this model.

        @param i_strName The string name of the method to check

        @return const BehaviorDescriptor* The descriptor, or NULL if not found.
    */
    const BehaviorDescriptor* GetBehaviorDescriptor(const efd::utf8string& i_strName) const;

    /**
        Looks up a given behavior descriptor within this model.

        @param i_id The behavior ID of the method to check

        @return const BehaviorDescriptor* The descriptor, or NULL if not found.
    */
    const BehaviorDescriptor* GetBehaviorDescriptor(BehaviorID i_id) const;

    /**
        Looks up a given behavior descriptor within one of our mixed-in models.  When you have
        an extends style behavior then invoking that behavior might require invoking some of
        the mixed-in behaviors as well.  This method provides a convenient function for finding
        these mixed in behaviors.

        @param i_strModelName The string name of the model containing the behavior
        @param i_strBehaviorName The string name of the behavior method to find

        @return const BehaviorDescriptor* The descriptor, or NULL if not found.
    */
    const BehaviorDescriptor* GetMixinBehaviorDescriptor(
        const efd::utf8string& i_strModelName,
        const efd::utf8string& i_strBehaviorName) const;

    /**
        Looks up a given behavior descriptor within one of our mixed-in models.  When you have
        an extends style behavior then invoking that behavior might require invoking some of
        the mixed-in behaviors as well.  This method provides a convenient function for finding
        these mixed in behaviors.

        @param i_behaviorId The behavior ID of the behavior method to find
        @param i_modelId The model ID of the model containing the behavior

        @return const BehaviorDescriptor* The descriptor, or NULL if not found.
    */
    const BehaviorDescriptor* GetMixinBehaviorDescriptor(
        FlatModelID i_modelId,
        BehaviorID i_behaviorId) const;

    /**
        Adds a given behavior descriptor to the list of behaviors for this FlatModel.  Should
        only be called during the parsing of a flat model file while creating the FlatModel
        instance.  The behavior is undefined if this method is called after loading is complete.

        @param i_pBehavior The behavior descriptor to add.  The FlatModel will hold a reference
            to this descriptor throughout its lifespan.
        @return bool True if successfully added
    */
    bool AddBehaviorDescriptor(BehaviorDescriptor* i_pBehavior);

    /**
        Retrieves the list of the named behaviors of the model.

        @param[out] o_listOfNames The list filled with the behavior names
    */
    void GetBehaviorNames(efd::list<efd::utf8string>& o_listOfNames) const;

    //@}

    /// @name Mix-in methods
    //@{

    /**
        Checks if the given model is a mix-in of this model.  Note that models are considered
        to contain themselves as well.

        @param i_id The flat model ID of the model to check
        @return bool True if the given model was mixed in to this model or is this model
    */
    bool ContainsModel(FlatModelID i_id) const;

    /**
        Checks if the given model is a mix-in of this model.  Note that models are considered
        to contain themselves as well.

        @param i_strName The string name of the model to check
        @return bool True if the given model was mixed in to this model or is this model
    */
    bool ContainsModel(const efd::utf8string& i_strName) const;

    /**
        Adds a given model to the list of mixed in models for this FlatModel.  Should only be
        called during the parsing of a flat model file while creating the FlatModel instance.
        The behavior is undefined if this method is called after loading is complete.

        @param i_id The flat model ID of the model that is mixed into this FlatModel
    */
    void AddMixinModel(FlatModelID i_id);

    /**
        Gets a list of all the model names mixed into this model.

        @param[out] o_listOfNames A list to be filled with the mix-in names.
    */
    void GetMixinNames(efd::list<efd::utf8string>& o_listOfNames) const;

    /**
        Gets a list of model/supermodel names in behavior execution order.

        @param i_behaviorName Name of the behavior to query.
        @param[out] o_invocationOrder A list of model/supermodel names in behavior execution order.
    */
    void GetBehaviorInvocationOrder(
        const efd::utf8string& i_behaviorName,
        const efd::list<efd::utf8string>*& o_invocationOrder) const;

    /**
        Behavior names support a "Model:Behavior" form which is used when a specific mix-in needs
        to be invoked.  This method will split this form into a separate model name and behavior
        name.

        @param[in] name The potentially fully qualified behavior name
        @param[out] o_model The model name if one was included, otherwise this parameter is
            left unchanged.
        @param[out] o_behavior the behavior name.  This parameter is always set, if the input
            name was not qualified then this will be set equal to the original name.
        @return bool true if the name was qualified, false if it was not.  o_behavior is
            set regardless of return value but o_model is only set when true.
    */
    static bool SplitModelAndBehavior(
        const efd::utf8string& name,
        efd::utf8string& o_model,
        efd::utf8string& o_behavior);

    /**
        Transforms the current flat model into the new flat model.  But does it
        in-place so that pointer references don't have to be fixed up.

        @param pNewFlatModel The new flat model to mutate into.
    */
    void Mutate(const FlatModel* pNewFlatModel);

    /**
        Adds an ExtraData element onto the flat model for future reference.

        @param extraData The item to add.
    */
    void AddExtraData(ExtraData* extraData);

    /**
        Retrieves all the extra data of a certain type.

        @param type The type of extra data to retrieve.
        @param o_extraData A vector which contains the extra data.
    */
    void GetExtraData(const efd::utf8string& type, efd::list<ExtraDataPtr>& o_extraData) const;

    //@}

protected:

    /// the name of the flat model
    efd::utf8string m_name;

    /// the ID of the flat model
    FlatModelID m_flatModelID;

    /// Traits of this flat model
    efd::UInt32 m_traits;

    /// Bitfield for which replication groups are used by any of the properties that are mixed
    /// into this model.
    efd::UInt32 m_activeReplicationGroups;

    /// @name map to hold each property descriptor
    //@{
    typedef efd::map<PropertyID, PropertyDescriptorPtr> PropertyDescriptorMapByID;
    PropertyDescriptorMapByID m_propertyDescriptorsByID;
    //@}

    /// @name map to hold each property descriptor indexed by property name
    //@{
    typedef efd::map<const efd::utf8string, PropertyDescriptorPtr> PropertyDescriptorMapByName;
    PropertyDescriptorMapByName m_propertyDescriptorsByName;
    //@}

    /// @name map to hold each behavior descriptor
    //@{
    typedef efd::map<BehaviorID, BehaviorDescriptorPtr> BehaviorDescriptorMapByID;
    BehaviorDescriptorMapByID m_BehaviorDescriptorsByID;
    //@}

    /// @name map to hold each behavior descriptor indexed by behavior name
    //@{
    typedef efd::map<const efd::utf8string, BehaviorDescriptorPtr> BehaviorDescriptorMapByName;
    BehaviorDescriptorMapByName m_BehaviorDescriptorsByName;
    //@}

    /// @name the set of BuiltinModel objects an entity of this model type has
    //@{
    typedef efd::map<FlatModelID, BuiltinModelDescriptorPtr> BuiltinModelDescriptorMapByID;
    BuiltinModelDescriptorMapByID m_BuiltinModelDescriptorsByID;
    //@}

    /// @name the set of BuiltinModel objects an entity of this model type has
    //@{
    typedef efd::map<const efd::utf8string, BuiltinModelDescriptorPtr> BuiltinModelDescriptorMapByName;
    BuiltinModelDescriptorMapByName m_BuiltinModelDescriptorsByName;
    //@}

    /// @name Track who all of my parent models are:
    //@{
    typedef efd::list< FlatModelID > SuperModelSet;
    SuperModelSet m_superModels;
    //@}

    /// @name Extra data attached to this flat model
    //@{
    typedef efd::map<efd::utf8string, efd::list<ExtraDataPtr> > ExtraDataByType;
    ExtraDataByType m_extraData;
    //@}

    /// Keep a pointer for interacting with the FlatModelManager service
    FlatModelManager* m_pFlatModelManager;
};


//------------------------------------------------------------------------------------------------
typedef efd::SmartPointer<FlatModel> FlatModelPtr;


//------------------------------------------------------------------------------------------------
} // end namespace egf

#endif // EE_FLATMODEL_H
