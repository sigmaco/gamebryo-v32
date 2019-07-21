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
#ifndef EE_RCSP4_H
#define EE_RCSP4_H

#include "etkRCSP4LibType.h"
#include <etkRCS/RCSProvider.h>

#include <efd/CriticalSection.h>

// Forward declare P4 classes and classes that require P4 classes. 
// Do not include P4 headers so that this head does not require the P4 SDK.
class ClientApi;
class Error;

namespace etk
{ 
    class RCSResult;
    class RCSClientUser;
    class ArgListConverter;
    class CancelDelegate;

    /**
        Perforce-specific implementation of RCSProvider interface. Refer to the RCSProvider
        documentation for descriptions of the methods. 
    */
    class EE_RCSP4_ENTRY RCSP4 : public RCSProvider
    {
        EE_DECLARE_CONCRETE_REFCOUNT;

    public:
        RCSP4();
        virtual ~RCSP4();

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

        // Perforce specific method
        virtual void SetClient(const efd::utf8string& client);
        virtual void SetCharset(const efd::utf8string& charset);

    protected:
        virtual bool Delete(const efd::utf8string& fileName, RCSResult* pResult = NULL);

        virtual bool Rename(
            const efd::utf8string& fromFileName, 
            const efd::utf8string& toFileName,
            RCSResult* pResult = NULL);

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

        bool Login(
            const efd::utf8string& username, 
            const efd::utf8string& password,
            const efd::utf8string& host,
            RCSResult& result);
        bool Sync(const efd::utf8string& fileName, RCSResult& result);

        bool EstablishConnection(RCSResult &result);
        void RunP4Cmd(const char* pCmd, 
            const efd::list<efd::utf8string>& args, 
            bool addToChangelist, 
            RCSResult& result);
        void RunP4Cmd(const char* pCmd, 
            const efd::list<efd::utf8string>& args,
            bool addToChangelist,
            RCSClientUser& ui,
            RCSResult& result);

        bool CreateChangelist(RCSResult &result);

        void ConstructP4Command(
            const char* pCmd, 
            const ArgListConverter& argList, 
            RCSResult &result);
        void CopyErrorToResult(Error& error, RCSResult &result);

        CancelDelegate* m_pCancelDelegate;
        efd::utf8string m_changelistID;
        ClientApi* m_pClient;
        bool m_clientInited;

        efd::CriticalSection m_critSection;
    };
} // end namespace etk

#endif // EE_RCSP4_H
