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
#ifndef EE_QOSCOMPARE_H
#define EE_QOSCOMPARE_H

#include <efd/efdLibType.h>
#include <efd/NetEnums.h>
#include <efd/UniversalTypes.h>
#include <efd/utf8string.h>

namespace efd
{

class IConfigManager;
class EnumManager;
class EE_EFD_ENTRY QOSCompare
{
public:
    /// @name Construction and Destruction
    //@{
    QOSCompare(efd::QualityOfService);
    //@}

    /// @name Operator methods
    //@{
    bool operator==(const efd::QualityOfService& rhs) const;
    bool operator!=(const efd::QualityOfService& rhs) const;
    //@}

    /**
        Compare two Quality of Service values.
        @param virtualQOS Virtual Quality of Service to compare to passed Physical Quality of 
            Service. Can actually be either a Virtual or Physical Quality of Service.
        @param physicalQOS Physical Quality of Service to compare to. Must actually be a Physical
            Quality of Service as no conversion is performed on this parameter.
    */
    static bool Compare(efd::QualityOfService virtualQOS, efd::QualityOfService physicalQOS);

    /**
        Read configuration data from the passed in Config Manager to populate the static mapping
        of Virtual to Physical Qualities of Service.
        @param pConfigManager The Config Manager to read configuration information out of.
        @param pEnumManager The EnumManager to use to look up Quality of Service enum values.
    */
    static void ReadConfig(IConfigManager* pConfigManager, EnumManager* pEnumManager);

    /**
        Release all memory used by static mapping of Virtual to Physical Qualities of Service.
    */
    static void Cleanup();

    /**
        Lookup the passed in string in the EnumManager to try to get the corresponding
        Virtual Quality of Service integer value. If the string lookup fails the string will be 
        passed to atoi to attempt to read the string as a integer directly.
        @param pEnumManager Pointer to the EnumManager to use for lookup.
        @param stringName The string name of the Virtual Quality of Service to look up.
        @return The Virtual Quality of Service if found of QOS_INVALID if not found.
    */
    static efd::QualityOfService GetVirtualQOS(
        EnumManager* pEnumManager, 
        const utf8string& stringName);

    /**
        Lookup the passed in string in the EnumManager to try to get the corresponding
        Physical Quality of Service integer value. If the string lookup fails the string will be
        passed to atoi to attempt to read the string as a integer directly.
        @param pEnumManager Pointer to the EnumManager to use for lookup.
        @param stringName The string name of the Physical Quality of Service to look up.
        @return The Physical Quality of Service if found of QOS_INVALID if not found.
    */
    static efd::QualityOfService GetPhysicalQOS(
        EnumManager* pEnumManager, 
        const utf8string& stringName);

    /**
        Looks up the corresponding Physical Quality of Service for the passed in
        Virtual Quality of Service in the Virtual to Physical Qualities of Service
        map.
        @param virtualQOS The Virtual Quality of Service to look up.
        @return The Physical Quality of Service if found, or the default Quality of Service if not
            found.
        NOTE: If the Quality of Service passed in is already a Physical Quality of Service
            (which can be determined by checking to see if the NET_VIRTUAL bit is set) the passed
            in Physical Quality of Service will be returned without performing a lookup.
    */
    static efd::QualityOfService LookupPhysical(efd::QualityOfService virtualQOS);

    /**
        Sets the default Quality of Service to use. The default Quality of Service is used any
        time a specific override is not found in the Virtual to Physical Qualities of Service
        map. QOS_UNRELIABLE if not overridden automatically maps to kQOS_Unreliable and
        QOS_CONNECTIONLESS if not overridden automatically maps to kQOS_UnreliableConnectionless.

        @param physicalQOS The default Quality of Service to use.
    */
    static void SetDefaultQualityOfService(efd::QualityOfService physicalQOS);

protected:

    /// Static mapping of Virtual to Physical Qualities of Service.
    static efd::map< efd::QualityOfService, efd::QualityOfService > ms_virtualToPhysical;

    /// True if config information has already been read.
    static bool ms_configRead;

    /// The default QualityOfService.
    static QualityOfService ms_defaultQualityOfService;

    /// Virtual (or physical) QualityOfService used in comparison.
    efd::QualityOfService m_virtualQOS;
};

} // end namespace efd

#include <efd/QOSCompare.inl>

#endif //EE_QOSCOMPARE_H
