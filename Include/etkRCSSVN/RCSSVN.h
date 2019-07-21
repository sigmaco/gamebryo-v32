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
#ifndef EE_RCSSVN_H
#define EE_RCSSVN_H

#include <etkRCSSVN/etkRCSSVNLibType.h>
#include <etkRCS/RCSProvider.h>

#include <efd/CriticalSection.h>

// Forward declare Subversion types to avoid depending on Subversion SDK headers
struct apr_pool_t;
struct svn_error_t;
struct svn_auth_cred_simple_t;
struct apr_pool_t;

namespace etk
{ 
    class SVNErr;

    /**
        Subversion-specific implementation of RCSProvider interface. Refer to the RCSProvider
        documentation for descriptions of the methods. 
    */
    class EE_RCSSVN_ENTRY RCSSVN : public RCSProvider
    {
        EE_DECLARE_CONCRETE_REFCOUNT;

    public:
        RCSSVN();
        ~RCSSVN();

        virtual bool Initialize(RCSResult* pResult = NULL);
        virtual void Shutdown();

        virtual bool IsSupported(RCSCapabilites capability) const;

        virtual bool Connect(
            const efd::utf8string& username, 
            const efd::utf8string& password, 
            const efd::utf8string& host,
            RCSResult* pResult = NULL);
        virtual bool Disconnect(RCSResult* pResult = NULL);
        virtual bool IsConnected(RCSResult* pResult = NULL);

    protected:
        virtual bool Delete(const efd::utf8string& fileName, RCSResult* pResult = NULL);

        virtual bool Rename(
            const efd::utf8string& fromFileName, 
            const efd::utf8string& toFileName,
            RCSResult* pResult = NULL);

        virtual bool RobustRename(
            const efd::utf8string& fromFileName, 
            const efd::utf8string& toFileName,
            RCSResult& result);

        virtual bool SimpleAdd(const efd::utf8string& fileName, RCSResult& result);
        virtual bool SimpleEdit(const efd::utf8string& fileName, RCSResult& result);
        virtual bool SimpleDelete(const efd::utf8string& fileName, RCSResult& result);
        virtual bool SimpleRename(
            const efd::utf8string& fromFileName, 
            const efd::utf8string& toFileName,
            RCSResult& result);
        virtual bool SimpleRevert(
            const efd::utf8string& fileName,
            bool modifyFile,
            RCSResult& result);
        virtual bool SimpleStatus(
            const efd::utf8string& fileName, 
            RCSStatus& status,
            RCSResult& result);

        bool IsCompatibleVersion(RCSResult& result) const;
        bool AddToChangelist(const efd::utf8string& fileName, SVNErr& err);

        bool FlushPendingFiles(SVNErr& err, bool success);

        bool ReplaceRevert(const efd::utf8string& fileName);

        static svn_error_t* SimplePromptCallback(
                                            svn_auth_cred_simple_t **ppCred,
                                            void* pBaton,
                                            const char* pRealm,
                                            const char* pUsername,
                                            svn_boolean_t maySave,
                                            apr_pool_t* pPool);

        static void NotificationCallback(
                                    void* pBaton, 
                                    const svn_wc_notify_t* pNotify, 
                                    apr_pool_t* pPool);

        static svn_error_t* CancellationCallback(void* pBaton);

        efd::utf8string m_username;
        efd::utf8string m_password;
        efd::utf8string m_host;

        apr_pool_t* m_pMemPool;
        svn_client_ctx_t* m_pCtx;

        efd::list<efd::utf8string> m_pendingFiles;
    };
} // end namespace etk

#endif // EE_RCSSVN_H
