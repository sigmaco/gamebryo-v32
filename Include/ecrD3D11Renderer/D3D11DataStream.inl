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

namespace ecr
{

//------------------------------------------------------------------------------------------------
inline void D3D11DataStream::SetAccessMask(efd::UInt8 accessMask)
{
    if (IsAccessRequestValid(accessMask, m_eUsage))
        m_uiAccessMask = accessMask;
}

//------------------------------------------------------------------------------------------------
template <class LockPolicy>
inline D3D11LockableDataStream<LockPolicy>::D3D11LockableDataStream(
    const NiDataStreamElementSet& elements, 
    efd::UInt32 count,
    efd::UInt8 accessMask, 
    NiDataStream::Usage usage, 
    D3D11_USAGE d3d11Usage,
    efd::UInt32 bindFlags, 
    efd::UInt32 cpuAccessFlags) :
    D3D11DataStream(elements, count, accessMask, usage, d3d11Usage, bindFlags, cpuAccessFlags)
{
    /* */
}

//------------------------------------------------------------------------------------------------
template <class LockPolicy>
inline D3D11LockableDataStream<LockPolicy>::D3D11LockableDataStream(
    efd::UInt8 accessMask, 
    NiDataStream::Usage usage, 
    D3D11_USAGE d3d11Usage,
    efd::UInt32 bindFlags, 
    efd::UInt32 cpuAccessFlags) :
    D3D11DataStream(accessMask, usage, d3d11Usage, bindFlags, cpuAccessFlags)
{
    /* */
}

//------------------------------------------------------------------------------------------------
template <class LockPolicy>
inline D3D11LockableDataStream<LockPolicy>::~D3D11LockableDataStream()
{
    if (GetLocked())
    {
        D3D11Error::ReportWarning("Destroying locked D3D11DataStream.\n");
    }

    m_lockPolicy.Delete(this);
}

//------------------------------------------------------------------------------------------------
template <class LockPolicy>
inline void* D3D11LockableDataStream<LockPolicy>::LockImpl(efd::UInt8 lockMask)
{
    efd::Bool forceRead = (lockMask & LOCK_TOOL_READ) != 0;
    efd::Bool forceWrite = (lockMask & LOCK_TOOL_WRITE) != 0;
    efd::Bool read = (lockMask & LOCK_READ) != 0;
    efd::Bool write = (lockMask & LOCK_WRITE) != 0;

    if (read || forceRead)
    {
        if (write || forceWrite)
            return m_lockPolicy.LockReadWrite(this, forceRead, forceWrite);
        else
            return m_lockPolicy.LockRead(this, forceRead);
    }
    else// if (bWrite || forceWrite)
    {
        EE_ASSERT(write || forceWrite);
        return m_lockPolicy.LockWrite(this, forceWrite);
    }
}

//------------------------------------------------------------------------------------------------
template <class LockPolicy>
inline void D3D11LockableDataStream<LockPolicy>::UnlockImpl(efd::UInt8 lockMask)
{
    efd::Bool forceRead = (lockMask & LOCK_TOOL_READ) != 0;
    efd::Bool forceWrite = (lockMask & LOCK_TOOL_WRITE) != 0;
    efd::Bool read = (lockMask & LOCK_READ) != 0;
    efd::Bool write = (lockMask & LOCK_WRITE) != 0;

    if (read || forceRead)
    {
        if (write || forceWrite)
            return m_lockPolicy.UnlockReadWrite(this, forceRead, forceWrite);
        else
            return m_lockPolicy.UnlockRead(this, forceRead);
    }
    else// if (bWrite || forceWrite)
    {
        EE_ASSERT(write || forceWrite);
        return m_lockPolicy.UnlockWrite(this, forceWrite);
    }
}

//------------------------------------------------------------------------------------------------
inline D3D11NonLockableDataStream::D3D11NonLockableDataStream(
    const NiDataStreamElementSet& elements, 
    efd::UInt32 count,
    efd::UInt8 accessMask, 
    NiDataStream::Usage usage, 
    D3D11_USAGE d3d11Usage,
    efd::UInt32 bindFlags, 
    efd::UInt32 cpuAccessFlags) :
    D3D11DataStream(elements, count, accessMask, usage, d3d11Usage, bindFlags, cpuAccessFlags)
{
    /* */
}

//------------------------------------------------------------------------------------------------
inline D3D11NonLockableDataStream::D3D11NonLockableDataStream(
    efd::UInt8 accessMask, 
    NiDataStream::Usage usage, 
    D3D11_USAGE d3d11Usage,
    efd::UInt32 bindFlags, 
    efd::UInt32 cpuAccessFlags) :
    D3D11DataStream(accessMask, usage, d3d11Usage, bindFlags, cpuAccessFlags)
{
    /* */
}

//------------------------------------------------------------------------------------------------
inline D3D11NonLockableDataStream::~D3D11NonLockableDataStream()
{
    /* */
}

//------------------------------------------------------------------------------------------------
inline void* D3D11NonLockableDataStream::LockImpl(efd::UInt8 lockMask)
{
    efd::Bool forceRead = (lockMask & LOCK_TOOL_READ) != 0;
    efd::Bool forceWrite = (lockMask & LOCK_TOOL_WRITE) != 0;

    if (forceRead || forceWrite)
    {
        // This is so not thread safe, but it's a very rare situation
        SetLocked(true);
        return MapBuffer(lockMask, 1, 1);
    }
    else
    {
        // Failure by design.
        return NULL;
    }
}

//------------------------------------------------------------------------------------------------
inline void D3D11NonLockableDataStream::UnlockImpl(efd::UInt8 lockMask)
{
    efd::Bool forceRead = (lockMask & LOCK_TOOL_READ) != 0;
    efd::Bool forceWrite = (lockMask & LOCK_TOOL_WRITE) != 0;

    if (forceRead || forceWrite)
    {
        // This is so not thread safe, but it's a very rare situation
        SetLocked(false);
        return UnmapBuffer(lockMask, 0, 0);
    }
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11DataStream::NeedsLocalBuffer(efd::UInt8 accessMask)
{
    return ((accessMask & ACCESS_CPU_WRITE_VOLATILE) != 0) ||
        ((accessMask & ACCESS_CPU_WRITE_MUTABLE) != 0);
}

//------------------------------------------------------------------------------------------------
inline D3D11_USAGE D3D11DataStream::GetD3D11Usage() const
{
    return m_d3d11Usage;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11DataStream::GetD3D11BindFlags() const
{
    return m_d3d11BindFlags;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11DataStream::GetD3D11CPUAccessFlags() const
{
    return m_d3d11CPUAccessFlags;
}

//------------------------------------------------------------------------------------------------
inline ID3D11Buffer* D3D11DataStream::GetBuffer() const
{
    return m_pD3D11Buffer;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
