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

#ifndef TIMEOFDAYFILE_H
#define TIMEOFDAYFILE_H

#include "ecr/ecrClassIDs.h"
#include "egmTerrainLibType.h"

// foreward declaration:
namespace efd
{
    class TiXmlDocument;
};

namespace egmTerrain
{

/**
    Class that defines how to read and write from and to a time of day file
*/
class EE_EGMTERRAIN_ENTRY TimeOfDayFile : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(TimeOfDayFile, efd::kCLASSID_TimeOfDayFile, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:

    /// Defines a keyframe to facilitate saving and loading to and from a file.
    struct Keyframe
    {
        /// The time of the keyframe.
        efd::utf8string time;
        /// The value of the keyframe.
        efd::utf8string value;
    };

    /// Version type for storing the file version
    typedef efd::UInt32 FileVersion;

    /**
        Create a TimeOfDayFile object capable of traversing the 
        data stored in the given file.

        @param pToDFile The path to a .tod file to open for iteration.
        @param pEntManager The entity manager.
        @param writeAccess Set to true if we are going to output to a file.
            Can only read OR write at once, not both.

        @return True if the file could be opened, the version has been 
            recognized, and the first block appears intact, otherwise false.
    */
    static TimeOfDayFile* Open(const char* pToDFile, egf::EntityManager* pEntManager,
        bool writeAccess = false);

    /// Destructor.
    virtual ~TimeOfDayFile();

    /**
        Return the version of the file being written/read.
    */
    inline virtual FileVersion GetFileVersion() const;

    /**
        Return true if file is ready to be written/read.
    */
    inline virtual bool IsReady() const;

    /**
        Return true if the file has been opened for write access.
    */
    inline virtual bool IsWritable() const;

    /**
        function returning the file version that is currently in use
    */
    inline static FileVersion GetCurrentVersion();

    /**
        Function returning the associated file path
    */
    inline efd::utf8string GetFilePath() const;

    /**
        Add the entity name to the file.
    */
    inline void AddEntity(efd::ID128 entityID, efd::utf8string entityName);

    /**
        Adds the property name to the file.
    */
    inline bool AddProperty(efd::ID128 entityID, EnvironmentService::ToDProperty toAdd);

    /**
        Adds keyframe data to the property map for a specified property name.
        The property will be added if it did not exist before.

        @param propertyName Name of the property for which to add a keyframe
        @param time the time of the new keyframe
        @param value the value of the new keyframe
        @return true if successful
    */
    bool AddKeyframe(efd::utf8string propertyName, efd::utf8string time, efd::utf8string value);

    /**
        Returns keyframe data for a particular property name
    */
    efd::vector<Keyframe> GetPropertyKeyframes(efd::utf8string propertyName);

    /**
        Returns Keyframe data for a particular property name

        @param propertyName the Name of the property to retrieve data for
        @param[out] times List of all keyframe times
        @param[out] values list of all keyframe values
    */
    void GetPropertyKeyframes(efd::utf8string propertyName, efd::vector<efd::utf8string>& times,
        efd::vector<efd::utf8string>& values);

    /**
        returns a vector containing all the property names for the specified entity
    */
    efd::vector<EnvironmentService::ToDProperty> GetProperties(efd::ID128 entityID);

    /**
        Write the file header to the tod file
    */
    bool WriteFileHeader();

    /**
        Write the file content for all entities saved by this file
    */
    void WriteFileContent();

protected:
        
    /**
        Constructor for this time of day file iterator

        @param pFileName the time of day file to attempt to open
        @param writeAccess Marks whether to read or write the file
    */
    TimeOfDayFile(const char* pFileName, bool writeAccess);

    
    /**
        Constructor for this time of day file iterator. This constructor takes in a pointer to an
        existing file and copies its content. This is used to update file data rather than destroy
        content that has not changed.
    */
    TimeOfDayFile(TimeOfDayFile* pFile, bool writeAccess);

    /**
        Initialize the class by opening the file and reading the first couple
        of headers. 

        @return true if the class was successfully initialized.
    */
    virtual bool Initialize(egf::EntityManager* pEntManager);

    /**
        Write the properties to the file
    */
    bool WritePropertySet(efd::ID128 entityID);
   
    /**
        Read the list of keyframes from a section of a DOM document.
    */
    virtual bool ReadPropertySet(const efd::TiXmlElement* pRootElement);

    /// The file version this class is capable of reading/writing
    static const FileVersion ms_fileVersion = FileVersion(2);

    // File data:
    /// The filename of the terrain file
    efd::utf8string m_fileName;
    /// The file object to access the file through
    efd::TiXmlDocument m_file;
    /// The access mode used to open this file
    bool m_writeAccess;
    /// This file is ready to be read/written
    bool m_ready;

    // Current File Data:
    /// The version of the file being read
    FileVersion m_fileVersion;

    /// A map of all registered entities for this file
    typedef efd::map< efd::ID128, efd::utf8string > EntityMap;
    EntityMap m_registeredEntities;

    /// A map of properties indexed according to entity names.
    typedef efd::vector<EnvironmentService::ToDProperty> PropertyVector;
    typedef efd::map< efd::ID128, PropertyVector > EntityToPropertyMap;
    EntityToPropertyMap m_entityToPropertyMap;

    /// The map of property name to keyframe sequences
    typedef efd::vector<Keyframe> KeyframeVector;
    typedef efd::map< efd::utf8string, KeyframeVector > PropertyToKeyframeMap;
    PropertyToKeyframeMap m_propertyMap;

    /// Cached services that are used by the time of day files
    egf::EntityManagerPtr m_spEntityManager;

};

/// Defines a smart pointer (reference counted) for the TimeOfDayFile class
typedef efd::SmartPointer<TimeOfDayFile> TimeOfDayFilePtr;

};// namespace

#include "TimeOfDayFile.inl"
#endif
