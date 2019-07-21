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
#ifndef __StringConverters_h__
#define __StringConverters_h__


#include <efd/UniversalTypes.h>
#include <efd/EEHelpers.h>
#include <efd/Asserts.h>


namespace efd
{


#if defined(EE_PLATFORM_LINUX)


// On Linux wchar_t is a 32bit type but our WChar is always 16 bit.  So this will do a simple
// conversion from 16 to 32 so that OS functions can be called.  The exact same syntax can be
// used on Windows to generate a no-op.
EE_COMPILETIME_ASSERT(sizeof(wchar_t) == 4);



class WStrToNative
{
public:
    WStrToNative(const efd::WChar* i_psz)
    : m_bAllocated(false)
    , m_psz(m_szBuff)
    {
        efd::UInt32 len = efd::Strlen(i_psz);
        if (len > EE_ARRAYSIZEOF(m_szBuff))
        {
            m_psz = EE_EXTERNAL_NEW wchar_t[len];
            m_bAllocated = true;
        }
        //DT32424 In the rare and unlikely case where we have an extended UTF16 character this
        // will not work correctly.
        for (efd::UInt32 i=0; i <= len; ++i)
        {
            m_psz[i] = static_cast<wchar_t>(i_psz[i]);
        }
    }

    ~WStrToNative()
    {
        if (m_bAllocated)
        {
            EE_EXTERNAL_DELETE [] m_psz;
        }
    }

    operator const wchar_t*() const
    {
        return m_psz;
    }

protected:
    bool m_bAllocated;
    wchar_t* m_psz;
    wchar_t m_szBuff[20];
};


#else

EE_COMPILETIME_ASSERT(sizeof(wchar_t) == 2);


inline const wchar_t* WStrToNative(const efd::WChar* i_psz)
{
    return (const wchar_t*)i_psz;
}


#endif // defined EE_PLATFORM_LINUX


} // end namespace efd


#endif // __StringConverters_h__
