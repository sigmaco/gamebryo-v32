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
#ifndef DYNAMICMODULE_H
#define DYNAMICMODULE_H

#include <efd/utf8string.h>

namespace efd
{
    typedef void* ModuleHandle;
    typedef void* MethodHandle;

    /**
        A wrapper for dynamically loading modules and maintaining a reference count so that the
        module can be automatically unloaded when no longer in use.
    */
    class EE_EFD_ENTRY DynamicModule
    {
    public:
        /// Constructors and Destructor
        //@{
        DynamicModule();
        DynamicModule(const DynamicModule& i_other);
        ~DynamicModule();
        //@}

        /// Assignment operator
        DynamicModule& operator=(const DynamicModule& i_rhs);

        /**
            Dynamically loads a module.
          
            @note If this fails, you must currently use platform specific calls to find out why the
                call failed.

            @param i_strName the exact name of the module to load.  This may optionally include
                    a complete or partial directory path.  The file name should be a platform
                    specific name, see DynamicModuleNameRules::GetPlatformSpecificName for
                    information on how to generate the platform specific name in a platform
                    neutral manor.
            @param loadLibraryAsDatafile (Windows-only) When this parameter is set to true, the
                    DLL will be loaded for reading resource-data only. Functions will not be 
                    mapped into the current process AND DLLs implicitly linked to the DLL will 
                    not be loaded. 
            @return True if the module was successfully loaded, false otherwise.
          
        */
        bool LoadModule(const efd::utf8string& i_strName, bool loadLibraryAsDatafile = false);

        /**
            Unloads a previously loaded module. The module will automatically unload when the
            DynamicModule object is destroyed, or you can call this to control when the module
            is unloaded.
        */
        bool UnloadModule();

        /// Determine if the module has been loaded.
        bool IsLoaded() const;

        /**
           Looks up a method from the loaded module by name.  You must already know the exact
           calling convention of the returned function pointer and are expected to cast the
           result before using it in any way.
          
            @param i_strName the exact name of the module to load.
            @return bool True if the method was successfully loaded, false otherwise.
        */
        MethodHandle GetMethod(const efd::utf8string& i_strName) const;

        /**
           Returns the module name.  This will be the exact name that was passed to LoadModule
           and is not in any way cleaned up or adjusted based on the final actual module that
           was loaded.  The module name will be an empty string if no module is currently
           successfully loaded.
          
            @return utf8string The module name
        */
        const efd::utf8string& GetModuleName() const;

        /**
           Returns the raw module handle.  This might be needed for passing to other system
           functions in which case it might require a platform specific cast before using.
          
            @return utf8string The module handle
        */
        ModuleHandle GetModuleHandle() const;


#if defined(EE_PLATFORM_XBOX360)
        void Init(efd::utf8string& name);
        void AddMethod(efd::utf8string& name, void* method);
#endif

    private:
        class ModuleData
        {
            EE_DECLARE_CONCRETE_REFCOUNT;
        public:
            ModuleData();

            ModuleHandle m_handle;
            efd::utf8string m_strName;

        private:
            ~ModuleData();
        };
        ModuleData* m_pData;

#if defined(EE_PLATFORM_XBOX360)
        /// For Xbox 360, this map contains symbol-name/ordinal-number associations read from
        /// a module's .def file
        typedef efd::map< const efd::utf8string, int >    ModuleDefOrdinalMap;
        ModuleDefOrdinalMap                                m_modDefOrdMap;
#endif // EE_PLATFORM_XBOX360
    };



    namespace DynamicModuleNameRules
    {
        /**
            Queries for the platform dependent prefix of a shared/dynamic library.
            @return The platform dependent prefix. (e.g. lib under Linux/Unix)
        */
        EE_EFD_ENTRY const char* GetPlatformPrefix();

        /**
            Queries for the platform dependent file extension of a dynamic library.
            @return The platform dependent file extension including the "dot".
                (e.g. "dll" under Windows, "so" under Linux)
        */
        EE_EFD_ENTRY const char* GetPlatformExtension();

        /**
            Convenience method which constructs a string representing the full name of the
            shared library.  Pass in just the root name with no directory information.

            @param i_strBaseName the base name of the module.
            @return utf8string A string containing the platform specific name of the form:
                "<GetPlatformPrefix()><i_strBaseName>.<GetPlatformExtension()>"
        */
        EE_EFD_ENTRY const efd::utf8string GetPlatformSpecificName(
            const efd::utf8string& i_strBaseName);

    } // end namespace DynamicModuleNameRules
} // end namespace efd


#endif // DYNAMICMODULE_H
