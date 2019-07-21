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
#ifndef EE_ICONFIGSOURCE_H
#define EE_ICONFIGSOURCE_H

#include <efd/ISystemService.h>
#include <efd/utf8string.h>
#include <efd/efdClassIDs.h>

namespace efd
{

class ISection;
class IConfigManager;

/// Interface for configuration sources used in the Configuration Manager (IConfigManager).
class EE_EFD_ENTRY IConfigSource : public IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(IConfigSource, efd::kCLASSID_IConfigSource, IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

protected:
    virtual ~IConfigSource() {}

public:
    /**
        Definition of the default source types.

        Addition sources types may be to the "Configuration Manager" (IConfigManager) but need not
        be added to this enumeration.  It is merely a convenience.
    */
    enum tSourceType
    {
        /// Unknown source.
        kSourceUnknown,

        /// Command-line source.
        kSourceCommandLine,

        /// INI file source.
        kSourceIniFile,

        /// Environment variable source.
        kSourceEnvVar,

        /// Assign new source types any greater number.
        kSourceTypeMax
    };

    /**
        Definition of the default source priorities.

        Higher numbers equal higher priority source that will overwrite lower priority source
        information.
    */
    enum tSourcePriorities
    {
        /// Low priority source.
        kSourcePriorityLow = 0,

        /// Normal priority source is used for the default ini source file.
        kSourcePriorityNormal = 100,

        /// High priority source.
        kSourcePriorityHigh = 200,

        /// Command-line source priority is the highest.
        kSourcePriorityCmdLine = 300
    };

    /**
        Returns the priority for this configuration source.

        A higher number is a higher priority and overwrites lower values.

        @return Priority value for this source.
    */
    virtual int GetPriority() const = 0;

    /**
        Retrieves the source type of the configuration source as defined in tSourceType.

        Other source types may be added and they should be assigned numbers starting with
        tSourceType::kSourceTypeMax.

        @return Source type.
    */
    virtual unsigned int GetSourceType() const = 0;

    /**
        Returns the string name assigned to this configuration source.

        In general, it will contain the file name or address of the data used by this
        configuration source.

        @return Name of the source.
    */
    virtual const efd::utf8string& GetSourceName() const = 0;

    /**
        Converts the information identifying this source into a string that may be used for
        printing.

        @return Identification string.
    */
    virtual efd::utf8string SourceToString() const = 0;

    /**
        Sets the root so this source may add to the configuration.

        @param pRoot Pointer to the root of the configuration hierarchy.
        @param iPriority Priority of the configuration source.
    */
    virtual void SetConfiguration(
        ISection *pRoot,
        int iPriority) = 0;

    /**
        Reads the source data and add or modifies sections and name/value pairs in the root
        hierarchy.

        @param pManager Pointer to the configuration manager.
        @return True if the configuration data was read correctly.
    */
    virtual bool ReadConfiguration(IConfigManager *pManager) = 0;
};

/// Define smart pointer for the IConfigSource class.
typedef efd::SmartPointer<IConfigSource> IConfigSourcePtr;

} // end namespace efd

#endif // EE_ICONFIGSOURCE_H
