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
#ifndef EE_EnumManager_h
#define EE_EnumManager_h

#include <efd/ISystemService.h>
#include <efd/DDEParser.h>

namespace efd
{
// Forward declarations
class IConfigManager;
class IDs;

/**
    The EnumManager is used to load data driven enumeration files that can map between
    string names and numerical values and vice versa. Data driven enumerations also differ
    from C++ enumerations in that they can be extended. This allows code in foundation
    to reference a base enumeration but still be able to lookup a name-value pair defined
    in core runtime, game framework, or the final application. The Gamebryo code uses these
    enumerations to make log file output easier to read.  There is also support to use these
    enumerations from scripted code so that friendly string names can be used in script.  It
    is recommended that this service be used at least when log files are enabled.

    @note All methods in EnumManager may be used as soon as EnumManager::LoadConfigOptions has been
        called. This call will happen automatically during EnumManager::OnPreInit but this method
        can be called earlier in order to make the EnumManager available sooner.
*/
class EE_EFD_ENTRY EnumManager : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EnumManager, kCLASSID_EnumManager, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// Constructor
    EnumManager();

    /// Find a data driven enumeration by its friendly name
    efd::DataDrivenEnumBase* FindEnum(const efd::utf8string& enumName);
    /// Load a data driven enumeration by its friendly name
    efd::DataDrivenEnumBase* LoadEnum(const efd::utf8string& enumName);
    /// Find or load a data driven enumeration by its friendly name
    efd::DataDrivenEnumBase* FindOrLoadEnum(const efd::utf8string& enumName);

    /// Load a data driven enumeration by its physical file name.
    efd::DataDrivenEnumBase* LoadFile(const efd::utf8string& fileName);

    /// Add an enumeration to the manager
    bool AddEnum(DataDrivenEnumBase* pEnum);

    /// Lookup the value for a given name in the specified enumeration
    template< typename T >
    bool FindEnumValue(
        const efd::utf8string& i_enumName,
        const efd::utf8string& i_itemName,
        T& o_value);

    /// Lookup the value for a given name in the specified enumeration, load the enum if not
    /// found
    template< typename T >
    bool FindOrLoadEnumValue(
        const efd::utf8string& i_enumName,
        const efd::utf8string& i_itemName,
        T& o_value);

    /// Lookup the name for a given value in the specified enumeration
    template< typename T >
    bool FindEnumName(
        const efd::utf8string& i_enumName,
        const T& i_value,
        efd::utf8string& o_itemName);

    // See ISystemService::GetDisplayName
    virtual const char* GetDisplayName() const;

    /// Used during header generation.  This plug-in object is responsible for parsing the
    /// "header" tag in enum files, when not present the header tag is ignored.  During
    /// normal operation no IDDEHeaderGenerator should be provided.
    void SetHeaderGenerator(efd::IDDEHeaderGenerator* pHeaderGen);

    /// Load enum manager configuration options.  This is called during OnPreInit but can
    /// be called earlier in order to use enums prior to OnPreInit being called.  Once this
    /// has been called enumerations can be loaded.
    void LoadConfigOptions(efd::IConfigManager* pConfig);

protected:
    void RegisterIDs();

    // See ISystemService::OnPreInit
    efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /// Helper to map from friendly enum names to source file names.  This will use cached
    /// results from asset locator queries, or fall back to a default filename otherwise.
    efd::utf8string GetFileForEnum(const efd::utf8string& enumName);

    efd::IDDEHeaderGeneratorPtr m_pHeaderGen;
    typedef efd::map< efd::utf8string, DataDrivenEnumPtr > DDEnumMap;
    DDEnumMap m_enums;

    bool m_configLoaded;
    efd::utf8string m_loadPath;
    IDs* m_lastIDProcessed;
};

/// SmartPointer typedef for the EnumManager class
typedef efd::SmartPointer<EnumManager> EnumManagerPtr;

} // end namespace efd

#include <efd/EnumManager.inl>

#endif // EE_EnumManager_h
