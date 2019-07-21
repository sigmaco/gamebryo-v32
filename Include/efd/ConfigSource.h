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
#ifndef EE_CONFIGSOURCE_H
#define EE_CONFIGSOURCE_H

#include <efd/IConfigSource.h>
#include <efd/File.h>

namespace efd
{

class ISection;

/**
    Base class for all the configuration sources.

    It provides the basic handlers for priority and source information.  It is a system service.
*/
class EE_EFD_ENTRY ConfigSource : public IConfigSource
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(ConfigSource, kCLASSID_ConfigSource, IConfigSource);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

    /**
        Constructor for configuration source class.

        It initializes the source type, source name, and priority values.

        @param sourceType Value of the type defined in IConfig::tSourceType.
        @param sourceName String name assigned to this configuration source.
    */
    ConfigSource(
        IConfigSource::tSourceType sourceType,
        const efd::utf8string& sourceName);

public:
    /// Destructor for the configuration source.
    virtual ~ConfigSource();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual int GetPriority() const;
    virtual unsigned int GetSourceType() const;
    virtual const efd::utf8string& GetSourceName() const;
    virtual efd::utf8string SourceToString() const;
    virtual void SetConfiguration(
        ISection *pRoot,
        int iPriority);

protected:
    /*
        Checks a string to see if it is a name/value pair.
        If it is, then the function adds it to the specified section.
          pManager : Pointer to the configuration manager for adding sources.
          pSection : Pointer to the current section.
          pairString : String containing the name/value pair.
          return : True if the string contains a valid name/value pair.
    */
    virtual bool ProcessNameValuePair(
        IConfigManager *pManager,
        ISection *pSection,
        const efd::utf8string& pairString);

    /*
        Adds the specified filename to the list of configuration sources to process.
          pManager : Pointer to the configuration manager for adding sources.
          sectionName : Name of the section to which the filename is being added.
          fileName : Filename to add to the sources list.
          return : True if the file is successfully added to sources list.
    */
    virtual bool AddFileSource(
        IConfigManager *pManager,
        const efd::utf8string& sectionName,
        const efd::utf8string& fileName,
        int priority = IConfigSource::kSourcePriorityNormal);

    // Source type identification.
    IConfigSource::tSourceType m_sourceType;

    // Name of the source.
    efd::utf8string m_sourceName;

    // Path to the source file (if applicable).
    efd::utf8string m_basePath;

    // Root of the configuration for added info.
    ISection *m_pRoot;

    // Priority number of the source.
    int m_priority;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the ConfigSource class.
typedef efd::SmartPointer<ConfigSource> ConfigSourcePtr;

/**
    Class for processing command-line parameters to the application.

    It automatically finds the command-line parameters passed to the application and processes
    them.

    Parameters passed on the command-line must be in the following form and surrounded by quotes
    if they contain spaces:

        @verbatim
        Name=Value
        @endverbatim

    For a link:

        @verbatim
        LinkName>NameToLinkTo
        @endverbatim

    To load an additional configuration file (other the default Config.ini), you can use the plus
    symbol (+) with the name and path of the file to load.  Optionally, you may include a
    section/subsection specifier to the left of the plus sign to load all contents of the file as
    children of that section.  Whenever a file is loaded via the plus operator (+), the contents
    of that file are loaded at a lower priority, so that items in the file or command-line that
    loaded the file take precedent over the other values.

        @verbatim
        +Path\And\Name\Of\Additional\Config\File\To\Load
        Section.Subsection+Path\And\Name\Of\Additional\Config\File\To\Load\As\Children
        @endverbatim

    To Add/Update values/links in sections use dots to separate the sections in the forms:

        @verbatim
        Section.SubSection.SubSubSection.Name=Value
        Section.SubSection.SubSubSection.LinkName>Section.SubSection.NameToLinkTo
        @endverbatim

    If name/value pairs have spaces in them, the entire name/value pair must be enclosed in quotes
    so that they will appear as a single command-line parameter.

    All command-line parameters that do not conform to the name/value or link syntax automatically
    will be added to the default section (kDefaultSection) for the command-line source, and will
    be assigned the name kParam_name with the parameter number appended to it.  This approach
    enables the configuration manager to handle current applications parameters in a backwards
    compatible manner.  One exception to the naming convention is the application name, which is
    always the first parameter to a program.  It will be added to the default section but for
    convenience be assigned the name kExeName.

    So the following example command-line:

        @verbatim
        c:\Apps\MyApp.exe NotANameVal Repeats=5 "Output=Say Hello" Addresses.Mine=127.0.0.1
            +AnotherConfig.ini MyConfig+MyConfig.ini
        @endverbatim

    would be equivalent to the following configuration INI File:

        @verbatim
        ;Whatever is in the file AnotherConfig.ini
        Repeats=5
        Output=Say Hello
        [CommandLineSource]
        ExeName=c:\Apps\MyApp.exe
        Param1=NotANameVal
        [Addresses]
        Mine=127.0.0.1
        [MyConfig]
        ;What ever is in the file MyConfig.ini
        @endverbatim
*/
class EE_EFD_ENTRY CommandLineSource : public ConfigSource
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(CommandLineSource, kCLASSID_CommandLineSource, ConfigSource);

    /// @endcond

public:
    /// Default section name for storing command-line parameters that do not conform to the
    /// name/value syntax.
    const static char *kDefaultSection;

    /// Prefix of the name assigned to parameters that do not conform to the name/value syntax.
    const static char *kParam_name;

    /// Name assigned to the application name parameter.
    const static char *kExeName;

    /// Command-line source constructor.
    CommandLineSource(
        int argcInit,
        char **argvInit);

    /// Virtual destructor.
    virtual ~CommandLineSource();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool ReadConfiguration(IConfigManager *pManager);

protected:
    // Number of arguments passed to the application.
    int m_argc;

    // Array of strings containing each of the arguments.
    char **m_ppArgv;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the CommandLineSource
/// class.
typedef efd::SmartPointer<CommandLineSource> CommandLineSourcePtr;

/**
    Class to read an INI style source and add the information to the master configuration
    hierarchy, updating any existing values of equal or lower priority.

    The INI file can have the standard form:

        @verbatim
        Name=Value
        AnotherName=Some Other Value
        [Section]
        NameInSection=Some value in the section
        [Another Section]
        More Names=For More Values
        @endverbatim

    In order to be able to define a hierarchical configuration, the class provides multiple
    extensions to the standard INI syntax.  You may create a subsection by using dot separated
    section names as follows:

        @verbatim
        Name=Value
        [Section]
        NameInSection=Some value in the section
        [Section.SubSection]
        SubSection Names=SubSection Values
        [Section.SubSection.SubSubSection]
        SubSubSection Names=SubSubSection Values
        [Section.AnotherSubSection]
        AnotherSubSection Names=AnotherSubSection Values
        @endverbatim

    To make the hierarchy easier to specify, relative section names are supported using curly
    brackets {}.  This method is much less prone to typographical errors and is easier to read.
    It takes the form:

        @verbatim
        Name=Value
        { Section
            NameInSection=Some value in the section
            { SubSection
                SubSection Names=SubSection Values
                { SubSubSection
                    SubSubSection Names=SubSubSection Values
                }
            }
            { AnotherSubSection
                AnotherSubSection Names=AnotherSubSection Values
            }
        }
        @endverbatim

    Although both methods may be used in a single file, it is not recommended.  However, if they
    are both used in a single file, [] sections become relative to the {} section that they are
    in and visa versa.

    Another extension to the syntax is used to support linking one entry to another in the
    hierarchy.  The equals sign (=) can be replaced with the greater than sign (>) to create a
    link.  In that case, the value of the entry should specify the name of the other entry or
    section to link with.  This approach effectively enables items to be remapped within the
    hierarchy.  So using the INI sample above, the following line would create a link at the root
    level to the entry in the SubSubSection:

        @verbatim
        MyLink>Section.SubSection.SubSubSection.SubSubSection Names
        @endverbatim

    To support include files in the config files, you may use the plus symbol (+) with the name
    and path of the file to load.  Optionally, you may include a section/subsection specifier to
    the left of the plus sign to load all contents of the file as children of that section.  Also,
    if you are in a section already and load an additional config file, the contents will also
    become children of that section.  So in general you should load additional config files at the
    beginning of the file to prevent them from being added as children of another section.
    Finally, the last section of an additional file being loaded does not affect the rest of the
    contents of the current file being loaded.  Examples to clarify include:

        @verbatim
        Config.ini
        +Config2.ini
        [MyExtraConfigs]
        +ExtraConfigs.ini
        [OtherSettings]
        Something=SomeValue
        @endverbatim

        @verbatim
        Config2.ini
        NameFrom2=ValueFrom2
        [SectionFrom2]
        AnotherNameFrom2=AnotherValueFrom2
        @endverbatim

        @verbatim
        ExtraConfigs.ini
        NameFromExtra=ValueFromExtra
        [SectionFromExtra]
        AnotherNameFromExtra=AnotherValueFromExtra
        @endverbatim

        @verbatim
        Should result in the equivalent configuration file
        NameFrom2=ValueFrom2
        [SectionFrom2]
        AnotherNameFrom2=AnotherValueFrom2
        [MyExtraConfigs]
        NameFromExtra=ValueFromExtra
        [MyExtraConfigs.SectionFromExtra]
        AnotherNameFromExtra=AnotherValueFromExtra
        [OtherSettings]
        Something=SomeValue
        @endverbatim

    So you can see that the fact that a section is defined in Config2.ini does not affect the
    hierarchy of sections in the originally config file.  Also, see that the ExtrsConfig.ini
    contents ended up as children of the MyExtraConfigs section because that was the current
    section when the include was specified.

    This class is a system service.
*/
class EE_EFD_ENTRY IniSource : public ConfigSource
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(IniSource, kCLASSID_IniSource, ConfigSource);

    /// @endcond

public:
    /// Comment character - must be the first none whitespace character.
    const static char kCommentChar;

    /// Character to open a relative section.
    const static char kSectionRelativeOpenChar;

    /// Character to close a relative section.
    const static char kSectionRelativeCloseChar;

    /// Character to open an absolute section header.
    const static char kSectionAbsoluteOpenChar;

    /// Character to close an absolute section header.
    const static char kSectionAbsoluteCloseChar;

    /**
        Constructor for the INI file source.

        @param strFileName Name of file from which to read entries.
    */
    IniSource(const efd::utf8string& strFileName);

    /// Virtual destructor.
    virtual ~IniSource();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool ReadConfiguration(IConfigManager *pManager);
};

/// Define a smart pointer (reference counting, self deleting pointer) for the CommandLineSource
/// class.
typedef efd::SmartPointer<CommandLineSource> CommandLineSourcePtr;

/**
    Class that reads in all the environment variables and adds them to the configuration
    hierarchy.

    All of the values that are read by the Environment Variables class are added to a special
    section defined by the constant EnvVarSource::kDefaultSection.  The resulting section entries
    may be linked into other sections or used directly by the application and system services.
    The source generates a section such as:

        @verbatim
        [Environment Variables]
        PATH = c:\windows\
        COMPUTERNAME = DEV_MACHINE
        PROCESSOR_ARCHITECTURE = x86
        @endverbatim

    This class is a system service.
*/
class EnvVarSource : public ConfigSource
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(EnvVarSource, kCLASSID_EnvVarSource, ConfigSource);

    /// @endcond

public:
    /// Default section name for storing environment variables.
    const static char *kDefaultSection;

    /// Constructor for the Environment Variable class.
    EnvVarSource();

    /// Virtual destructor.
    virtual ~EnvVarSource();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool ReadConfiguration(IConfigManager *pManager);
};

/// Define a smart pointer (reference counting, self deleting pointer) for the EnvVarSource class.
typedef efd::SmartPointer<EnvVarSource> EnvVarSourcePtr;

}   // End namespace efd.

#endif  // EE_CONFIGSOURCE_H
