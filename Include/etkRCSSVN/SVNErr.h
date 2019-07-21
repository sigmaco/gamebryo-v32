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
#ifndef EE_SVNERROR_H
#define EE_SVNERROR_H

#include <etkRCSSVN/etkRCSSVNLibType.h>
#include <etkRCS/RCSProvider.h>

// Forward delcare svn types
struct svn_error_t;

namespace etk
{ 
    class SVNErr
    {
    public:
        SVNErr(RCSResult* pResult);
        virtual ~SVNErr();

        inline bool Success();
        inline svn_error_t* GetError();        
        inline SVNErr& operator=(svn_error_t* pSvnErr);
        
        void Clear();
        void SetError(svn_error_t* pSvnErr);
        bool Ignore(apr_status_t errorToIgnore);

    private:
        svn_error_t* m_pSvnErr;
        RCSResult* m_pResult;
    };
} // end namespace etk

#include "SVNErr.inl"

#endif // EE_SVNERROR_H
