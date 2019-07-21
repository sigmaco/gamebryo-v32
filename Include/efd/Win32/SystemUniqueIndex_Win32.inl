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

#include <efd/utf8string.h>

namespace efd
{

/**
    SystemUniqueIndex

    This class creates a cross-process unique index given a base name.  For example, if you pass
    in your process name as the base name then it will give you an index that is guaranteed not
    to be in use by any of the other processes which could be used to generate, say, a unique
    log file name like "MyProcessName%d.log".  To accomplish this a named kernel object is used.
    As such the instance of the SystemUniqueIndex class must have the same lifespan as your usage
    of that index.  Indices will be reused as soon as the SystemUniqueIndex class that used that
    index is destructed.

    Note: indices start at 1, index 0 indicates an error.
 */
class SystemUniqueIndex
{
public:

    /**
        Default constructor. Does not acquire an index.
    */
    SystemUniqueIndex()
        : m_handle(NULL)
        , m_index(0)
    {
    }

    /**
        Constructor that acquires an index based on the string passed.
        @param strBaseName name of the index to acquire.
    */
    SystemUniqueIndex(const efd::utf8string& strBaseName)
        : m_handle(NULL)
        , m_index(0)
    {
        AquireIndex(strBaseName);
    }

    /**
        Destructor.  Releases any index acquired by this instance.
    */
    ~SystemUniqueIndex()
    {
        ReleaseIndex();
    }

    /**
        Acquire a new index.  Releases any previously held index.
        @param strBaseName name of the index to acquire.
    */
    bool AquireIndex(const efd::utf8string& strBaseName)
    {
        ReleaseIndex();
        for (efd::UInt32 i = 1; i; ++i)
        {
            m_name.sprintf("%s_%d", strBaseName.c_str(), i);

            HANDLE handle = CreateEventA(NULL, false, true, m_name.c_str());
            if (handle && GetLastError() != ERROR_ALREADY_EXISTS)
            {
                m_handle = handle;
                m_index = i;
                return true;
            }
            else
            {
                CloseHandle(handle);
            }
        }
        return false;
    }

    /**
        Releases any currently held index. Safe to call even if no index is held.
    */
    void ReleaseIndex()
    {
        if (m_handle)
        {
            CloseHandle(m_handle);
        }
        m_handle = NULL;
        m_index = 0;
    }

    /**
        Returns the currently held index or 0 if no index is currently held.
    */
    efd::UInt32 GetIndex() const
    {
        return m_index;
    }

    /**
        Returns the name of the currently held index of empty string if no index is currently held.
    */
    efd::utf8string GetName() const
    {
        return m_name;
    }

protected:
    HANDLE m_handle;
    efd::UInt32 m_index;
    efd::utf8string m_name;
};


} // end namespace efd

