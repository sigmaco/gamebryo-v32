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
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#pragma once
#ifndef EE_RCSFACTORY_H
#define EE_RCSFACTORY_H

#include <etkRCS/etkRCSLibType.h>
#include <etkRCS/RCSProvider.h>

#include <efd/DynamicModule.h>

namespace etk
{ 
    class RCSResult;

    typedef etk::RCSProvider* (*CreateRCSFunction)(void);

    /**
        This singleton object is used to create a revision control system provider object
        from available provider plug-in DLLs.
        <br>
        When the RCSFactory singleton is initialized, it will attempt to load 
        plug-ins that are used to access RCS through a common RCSProvider interface. 
        The available providers can be queried after initialization.
    */
    class EE_RCS_ENTRY RCSFactory : public efd::MemObject
    {
    public:

        /** Create the singleton and query for RCS providers by attempting to load plug-in DLLs.
            @param pResult Optional result object passed by the caller to hold any error messages
                generated during initialization
            @param pPluginDirectory Optional path to a directory to find the providers DLLs. 
                If no directory is supplied the following directory will be used 
                %EMERGENT_PATH%\\sdk\\Win32\\DLL.
            @return True if the singleton was successfully created and there is at least one
                provider plug-in available. Check pResult for additional details when an 
                error occurs.
        */
        static bool Initialize(RCSResult* pResult = NULL, const char* pPluginDirectory = NULL);

        /** Unload all provider DLLs and destroy the singleton.
            @note Make sure all provider objects previously created by the Create() method are 
                deleted prior to calling this method since it will unload the DLL associated with
                the implementation of these objects.
        */
        static void Shutdown();

        /** Query the display names for the available revision control system providers.
            For example: "Perforce" or "Subversion" 
            @param rcsNames An list of RCS name strings
            @note The RCS names returned by this method only indicate the provider DLLs are
                available. It does not guarantee the RCS client software required to access
                the system is properly installed. This check is not performed until the Create()
                method is called.
            @return True is there is at least one provider available.
        */
        static bool GetAvailableProviders(efd::list<efd::utf8string>& rcsNames);

        /** Instantiate a provider object that can be used to access a revision control system
            through the common RCSProvider interface.
            @param rcsName Name of RCS system obtained from GetAvailableProviders() method call.
            @param pResult Optional result object passed by the caller to hold any error messages
                generated while trying to instantiate a RCS provider object
            @return This method will return NULL if the underlying RCS client is not properly
                installed. For example, if the Subversion DLLs are not in the PATH, Windows 
                error message boxes will be displayed and this method will return NULL.
        */
        static RCSProvider* Create(const efd::utf8string& rcsName, RCSResult* pResult = NULL);

        /** Checks whether the factory has been successfully initialized.
            @return True if the singleton has been instantiated and at least one RCS provider
        */
        static bool IsInitialized();

    private:
        /// This is a singleton, do not allow it to be subclassed.
        RCSFactory();
        ~RCSFactory();

        bool LoadDynamicModules(RCSResult& result, const char* pPluginDirectory = NULL);
        bool FindPluginDLLs(
            efd::list<efd::utf8string>& dllNames, 
            RCSResult& result,
            const char* pPluginDirectory = NULL);
        void GetRCSNames(efd::list<efd::utf8string>& rcsNames);
        static efd::utf8string GetEnvVar(const char* pVarName);
        RCSProvider* CreateRCS(const efd::utf8string& rcsName, RCSResult& result);


        // List of plug-in DLLs and provider names used to create provide objects
        // ProviderModulePair.first.first = user-displayable provider name (e.g. "Subversion")
        // ProviderModulePair.first.second = provider DLL name (e.g. "etkRCSSVN")
        // ProviderModulePair.second = DynamicModule object used to load DLL
        typedef EE_STL_NAMESPACE::pair<efd::utf8string, efd::utf8string> ProviderDllPair;
        typedef EE_STL_NAMESPACE::pair<ProviderDllPair, efd::DynamicModule> ProviderModulePair;
        typedef efd::list<ProviderModulePair> ProviderModulePairList;

        ProviderModulePairList m_providerNameAndModuleList;

        /// Singleton instance of the class
        static RCSFactory* ms_pInstance;
    };
} // end namespace etk

#endif // EE_RCSFACTORY_H
