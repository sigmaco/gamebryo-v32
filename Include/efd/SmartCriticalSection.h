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
#ifndef EE_SMARTCRITICALSECTION_H
#define EE_SMARTCRITICALSECTION_H

#include <efd/CriticalSection.h>
#include <efd/Utilities.h>

namespace efd
{
/**
    A SmartCriticalSection is a convenience wrapper around a CriticalSection.  The main purpose
    of the SmartCriticalSection is to Unlock the CriticalSection when the SmartCriticalSection goes
    out of scope.
*/
class EE_EFD_ENTRY SmartCriticalSection
{
public:
    /// @name Construction and Destruction
    //@{
    /// Default constructor.  Does not lock the CriticalSection.
    SmartCriticalSection(CriticalSection& criticalSection);
    SmartCriticalSection(const SmartCriticalSection&);

    /// Destructor.  Unlocks the CriticalSection if it is locked
    ~SmartCriticalSection();
    //@}

    /// Passthrough call to m_criticalSection
    inline void Lock();

    /// Only calls Unlock if CriticalSection is actually locked
    inline void Unlock();

    /// Passthrough call to m_criticalSection
    inline efd::UInt32 GetOwningThreadID() const;

    /// Passthrough call to m_criticalSection
    inline efd::UInt32 GetCurrentLockCount() const;

protected:
    CriticalSection& m_criticalSection;
private:
    // operator= not implemented because it is not valid
    SmartCriticalSection& operator=(const SmartCriticalSection&);
};

} // namespace efd

#include <efd/SmartCriticalSection.inl>

#endif // #ifndef EE_SMARTCRITICALSECTION_H
