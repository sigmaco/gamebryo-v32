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

namespace etk
{
//--------------------------------------------------------------------------------------------------
RCSStatus::RCSStatus()
{
    Clear();
};
//--------------------------------------------------------------------------------------------------
RCSStatus::~RCSStatus()
{
}
//--------------------------------------------------------------------------------------------------
void RCSStatus::Clear()
{
    m_depotFile = "";
    m_clientFile = "";
    m_branchFromFile = "";
    m_action = RCS_ACTION_UNKNOWN;
    m_actionOwner = "";
    m_type = "";
    m_resolved = "";
    m_locked = false;
    m_deleted = false;
    m_resolveNeeded = false;
    m_replaced = false;
}
//--------------------------------------------------------------------------------------------------
RCSStatus::RCSAction RCSStatus::GetAction() const
{
    if (!m_branchFromFile.empty())
        return RCS_ACTION_BRANCH;

    return m_action;
}
//--------------------------------------------------------------------------------------------------
void RCSStatus::SetAction(RCSAction action) 
{
    m_action = action;
}
//--------------------------------------------------------------------------------------------------
const efd::utf8string& RCSStatus::GetActionOwner() const
{
    return m_actionOwner;
}
//--------------------------------------------------------------------------------------------------
void RCSStatus::SetActionOwner(const char* pActionOwner)
{
    m_actionOwner = pActionOwner;
}
//--------------------------------------------------------------------------------------------------
const efd::utf8string& RCSStatus::GetClientFilename() const
{
    return m_clientFile;
}
//--------------------------------------------------------------------------------------------------
void RCSStatus::SetClientFilename(const char* pClientFilename)
{
    m_clientFile = pClientFilename;
}
//--------------------------------------------------------------------------------------------------
const efd::utf8string& RCSStatus::GetDepotFilename() const
{
    return m_depotFile;
}
//--------------------------------------------------------------------------------------------------
void RCSStatus::SetDepotFilename(const char* pDepotFilename)
{
    m_depotFile = pDepotFilename;
}
//--------------------------------------------------------------------------------------------------
const efd::utf8string& RCSStatus::GetBranchFromFilename() const
{
    return m_branchFromFile;
}
//--------------------------------------------------------------------------------------------------
void RCSStatus::SetBranchFromFilename(const char* pFromFilename)
{
    m_branchFromFile = pFromFilename;
}
//--------------------------------------------------------------------------------------------------
bool RCSStatus::IsLocked() const
{
    return m_locked;
}
//--------------------------------------------------------------------------------------------------
void RCSStatus::SetLocked(bool lock)
{
    m_locked = lock;
}
//--------------------------------------------------------------------------------------------------
bool RCSStatus::IsDeleted() const
{
    return m_deleted;
}
//--------------------------------------------------------------------------------------------------
void RCSStatus::SetDeleted(bool deleted)
{
    m_deleted = deleted;
}
//--------------------------------------------------------------------------------------------------
bool RCSStatus::IsResolveNeeded() const
{
    return m_resolveNeeded;
}
//--------------------------------------------------------------------------------------------------
void RCSStatus::SetResolveNeeded(bool resolveNeeded)
{
    m_resolveNeeded = resolveNeeded;
}
//--------------------------------------------------------------------------------------------------
bool RCSStatus::IsReplaced() const
{
    // DT32639 This is only used by SVN, so we need change status to be factored
    // by the provider, and make the factory method virtual so each provider can create their 
    // own derived status object with their own status options.

    return m_replaced;
}
//--------------------------------------------------------------------------------------------------
void RCSStatus::SetReplaced(bool replaced)
{
    m_replaced = replaced;
}
//--------------------------------------------------------------------------------------------------
} // end namespace etk
