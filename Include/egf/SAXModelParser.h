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
#ifndef EE_SAXMODELPARSER_H
#define EE_SAXMODELPARSER_H

#include <efd/TinyXML.h>
#include <egf/FlatModel.h>
#include <egf/PropertyDescriptor.h>
#include <egf/BehaviorDescriptor.h>

namespace egf
{

// forward declare
struct XmlModelStringConstants;
class FlatModelManager;

/**
    A SAX-based XML parser for Emergent's Model file format
*/
class EE_EGF_ENTRY SAXModelParser
    : public efd::TiXmlDefaultHandler
    , public efd::MemObject
{

    enum ParserState
    {
        NotParsing = 0,
        InModel,
        InModelTrait,
        InProperty,
        InPropertySet,
        InPropertyTrait,
        InBehavior,
        InBehaviorTrait,
        InBehaviorInvocationOrder,
        InBehaviorInvocationOrderModel,
        InMixin,
        InExtraData,
        InExtraDataEntry,
    };

public:
    /// Construction and Destruction
    SAXModelParser(FlatModelManager& pModelManager);
    virtual ~SAXModelParser();

    /**
     Parse a model file.

     @param modelFile Full path name of the model file to parse
     @return Smart pointer to a FlatModel instance
    */
    FlatModelPtr Parse(const efd::utf8string& modelFile);

#if defined(WIN32)
    /**
    Parse a model buffer.

    @param virtualModelFile This name is really just to suggest what type of model is being loaded
    for logging purposes.
    @param pBuffer The model data to load.
    @return Smart pointer to a FlatModel instance
    */
    FlatModelPtr ParseBuffer(const efd::utf8string& virtualModelFile, const char* pBuffer);
#endif

    /// @cond EMERGENT_INTERNAL

    //@{
    static void _SDMInit();
    static void _SDMShutdown();
    //@}

    /// @endcond

protected:
    /// @name SAX Handlers
    /// overridden methods from XML sax parser callbacks
    //@{
    virtual void startElement(
        const EE_TIXML_STRING& localname,
        const efd::TiXmlAttributeSet& attrs);

    virtual void endElement(const EE_TIXML_STRING& localname);

    virtual void characters(const EE_TIXML_STRING& chars);
    //@}

    /// Pointer to the flat model manager.  Models get added to here once they get parsed.
    FlatModelManager* m_pFlatModelManager;

    /// Filename of the file currently being processed
    efd::utf8string m_modelFile;

    /// We don't stop parsing on the first error, we keep going as long as we can.  This provides
    /// a more helpful log output so you can fix all the bugs at once.
    efd::UInt32 m_errors;

    /// current state of the parser
    ParserState m_parserState;

    /// temporary flat model.  created at start of flat model element, completely
    /// constructed with properties/behaviors, then added to the flat model mgr.
    FlatModelPtr m_spFlatModel;

    /// temporary extra data.  created at start of an extra data element, constructed,
    /// then added to the flat model's extra data.
    ExtraDataPtr m_spExtraData;

    /// temporary property descriptor.  created at start of property element,
    /// assigned to, then saved with the flat model.
    PropertyDescriptorPtr m_tempPropertyDescriptor;

    /// Helper so FinalizeTraits only does its work once.
    bool m_fTraitsFinalized;

    /// temporary property.  created at start of set element then assigned to the
    /// property descriptor.
    IProperty* m_tempDefaultProperty;

    /// temporary behavior descriptor.  created at start of behavior element,
    /// assigned to, then saved with the flat model.
    BehaviorDescriptorPtr m_spBehaviorDesc;

    /// Properties that contain EntityRef data have special requirement that it can only be set to
    /// 0 (invalid entity id) and so we need to know when we are parsing one of those.
    bool m_propIsEntityRef;

    typedef efd::map<efd::utf8string, ModelTraits> ModelTraitMap;
    ModelTraitMap m_modelTraitMap;

    typedef efd::map<efd::utf8string, PropertyTraits> PropertyTraitMap;
    PropertyTraitMap m_propertyTraitMap;

    typedef efd::map<efd::utf8string, efd::UInt32> ReplicationGroupMap;
    ReplicationGroupMap m_propertyReplicationGroupMap;

    typedef efd::map<efd::utf8string, BehaviorTraits> BehaviorTraitMap;
    BehaviorTraitMap m_behaviorTraitMap;

    typedef efd::map<efd::utf8string, BehaviorTypes> BehaviorTypeMap;
    BehaviorTypeMap m_behaviorTypeMap;

    /// parse the attributes contained within the model tag and create a model
    void ParseModel(const efd::TiXmlAttributeSet& attrs);

    /// parse a trait associated with the current model
    void ParseModelTrait(const efd::TiXmlAttributeSet& attrs);

    /// parse the attributes contained with the property tag and create a prop
    void ParseProperty(const efd::TiXmlAttributeSet& attrs);

    /// parse any attributes contained in the set tag.  This currently only
    /// applies to the key element for associative array properties.
    void ParsePropertyValue(const efd::TiXmlAttributeSet& attrs);

    /// parse a trait associated with the current property
    void ParsePropertyTrait(const efd::TiXmlAttributeSet& attrs);

    /// parse the attributes contained with the behavior tag and create a prop
    void ParseBehavior(const efd::TiXmlAttributeSet& attrs);

    /// parse a trait associated with the current behavior
    void ParseBehaviorTrait(const efd::TiXmlAttributeSet& attrs);

    /// parse an invocation order list associated with the current behavior
    void ParseBehaviorInvocationOrder(const efd::TiXmlAttributeSet& attrs);

    /// parse an invocation order list element associated with the current behavior
    void ParseBehaviorInvocationOrderModel(const efd::TiXmlAttributeSet& attrs);

    /// parse a mix-in for the current model
    void ParseMixin(const efd::TiXmlAttributeSet& attrs);

    /// parse an extra data element for the current model
    void ParseExtraData(const efd::TiXmlAttributeSet& attrs);

    /// parse an extra data entry for the current model
    void ParseExtraDataElement(const efd::TiXmlAttributeSet& attrs);

    /**
     Called to ensure that all of our traits for the current model have been adapted to
     run-time conditions.  We know that all traits are listed first so as soon as we
     encounter a non-trait tag under the model tag we can finalize the traits.  This needs
     to be done before parsing a property tag so that built-in model properties can be adapted.
    */
    void FinalizeTraits();

    /// Called after reaching a closing model tag.
    void FinishedModel();

    /// Called after reaching a closed property tag.
    void FinishedProperty();

    /// Called after reaching a closed behavior tag.
    void FinishedBehavior();

    /// Method to prune out known errors generated by ToolBench
    bool ValidateBehavior();

    /// Parsing helpers:
    //@{
    bool FlatModelTraitFromName(const efd::utf8string& i_strTraitName, ModelTraits& o_mt);
    PropertyTraits PropertyTraitFromName(const efd::utf8string& i_strTraitName);
    efd::UInt32 ReplicationGroupFromName(const efd::utf8string& i_strTraitName);
    BehaviorTypes BehaviorTypeFromName(const efd::utf8string& i_strTypeName);
    BehaviorTraits BehaviorTraitFromName(const efd::utf8string& i_strTraitName);
    efd::ClassID PropertyTypeFromName(const efd::utf8string& i_strPropTypeName);
    //@}

    /**
     Temporary methods to perform run-time adaptation of a common model to specific client and
     server versions.  Eventually the tool will be able to perform this task and generate
     separate client and server versions of data.
    */
    bool _AdaptModelToProgramType();
    bool _AdaptPropertyToProgramType();
    bool _AdaptBehaviorToProgramType();
    bool _AdaptBuiltinModelToProgramType(class BuiltinModelDescriptor* pComp);

protected:
    static XmlModelStringConstants* ms_constants;

    /// Hiding default ctor
    SAXModelParser();
};


} // end namespace egf

#endif //EE_SAXMODELPARSER_H
