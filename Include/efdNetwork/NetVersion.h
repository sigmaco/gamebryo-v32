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
#ifndef EE_NETVERSION_H
#define EE_NETVERSION_H

namespace efd
{

class EE_EFDNETWORK_ENTRY NetVersion
{
public:
    NetVersion();
    virtual ~NetVersion();

    inline bool operator==(const NetVersion& other) const
    {
        return m_versions == other.m_versions;
    }

    inline void AddVersionString(const efd::utf8string& version)
    {
        m_versions.push_back(version);
    }

    /// Serialize into a very specific format which is totally carved in stone and must never
    /// ever ever change.
    virtual void Serialize(efd::Archive& ar);

protected:
    efd::vector<efd::utf8string> m_versions;
};

} // end namespace efd

#endif // EE_NETVERSION_H
