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
#ifndef EE_D3D11DATASTREAM_H
#define EE_D3D11DATASTREAM_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Error.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

#include <NiDataStream.h>
#include <NiDataStreamLockPolicy.h>
#include <efd/SmartPointer.h>

namespace ecr
{

/**
    D3D11-specific implementation of NiDataStream.

    Data streams will typically be created through the NiDataStream interface itself, which will 
    create an instance of this class using the correct factory. ecr::D3D11DataStream objects 
    encapsulate an ID3D11Buffer, regardless of how the buffer will actually be bound to the 
    device.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11DataStream : public NiDataStream
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// Create from an ID3D11Buffer object
    static D3D11DataStream* Create(ID3D11Buffer* pBuffer);

    /// Adjusts the size of the stream, specified in bytes. Contents of stream 
    /// are undefined afterwards.
    virtual void Resize(efd::UInt32 size);

    /// Returns the D3D11 usage for the buffer, which describes the read/write behavior the
    /// buffer expects.
    inline D3D11_USAGE GetD3D11Usage() const;

    /// Returns the D3D11 bind flags for the buffer, which indicate how the buffer can be used.
    inline efd::UInt32 GetD3D11BindFlags() const;

    /// Returns the D3D11 CPU Access flags, which indicate whether an application can read or
    /// write to the buffer from main memory.
    inline efd::UInt32 GetD3D11CPUAccessFlags() const;

    /// Returns the D3D11 buffer.
    inline ID3D11Buffer* GetBuffer() const;

    /**
        Reinterprets the Gamebryo access mask and usage parameters and returns the corresponding
        D3D11 usage enumeration, bind flags, and CPU access flags. If an exact match cannot be 
        found, the function returns false.

        @param accessMask Gamebryo access mask, from NiDataStream::Access. When this function
            returns, the accessMask will be updated with the actual access mask that the D3D11
            values represent.
        @param usage Gamebryo usage, from NiDataStream::Usage.
        @param d3d11Usage Outputs the resulting D3D11_USAGE enumeration.
        @param bindFlags Outputs the resulting D3D11_BIND_FLAG bitfield.
        @param cpuAccessFlags Outputs the resulting D3D11_CPU_ACCESS_FLAG bitfield.
        @return Returns true if the function succeeds, or false if an exact match cannot be found.
    */
    static efd::Bool InterpretDataStreamFlags(
        efd::UInt8& accessMask,
        Usage usage, 
        D3D11_USAGE& d3d11Usage, 
        efd::UInt32& bindFlags,
        efd::UInt32& cpuAccessFlags);
    /**
        Reinterprets the Gamebryo access mask and returns the corresponding D3D11 usage enumeration.
        If an exact match cannot be found, the function returns false.

        @param accessMask Gamebryo access mask, from NiDataStream::Access. 
        @param usage Outputs the resulting D3D11_USAGE enumeration.
        @return Returns true if the function succeeds, or false if an exact match cannot be found.
    */
    static efd::Bool InterpretAccessMask(
        efd::UInt8 accessMask,
        D3D11_USAGE& usage);
    /**
        Reinterprets the Gamebryo access mask and usage parameters and returns the corresponding
        D3D11 bind flags. 

        @param usage Gamebryo usage, from NiDataStream::Usage.
        @param accessMask Gamebryo access mask, from NiDataStream::Access. 
        @return The resulting D3D11_BIND_FLAG bitfield.
    */
    static efd::UInt32 InterpretUsage(
        Usage usage, 
        efd::UInt32 accessMask);
    /**
        Reinterprets the D3D11 usage enumeration, bind flags, and CPU access flags and returns the 
        corresponding Gamebryo access mask and usage parameters. If an exact match cannot be 
        found, the function returns false.

        @param d3d11Usage D3D11_USAGE enumeration.
        @param d3d11BindFlags D3D11_BIND_FLAG bitfield.
        @param d3d11CPUAccessFlags D3D11_CPU_ACCESS_FLAG bitfield.
        @param usage Outputs the resulting Gamebryo usage, from NiDataStream::Usage.
        @param accessFlags Outputs the resulting Gamebryo access mask, from NiDataStream::Access.
        @return Returns true if the function succeeds, or false if an exact match cannot be found.
    */
    static efd::Bool InterpretD3D11Parameters(
        D3D11_USAGE d3d11Usage,
        efd::UInt32 d3d11BindFlags, 
        efd::UInt32 d3d11CPUAccessFlags,
        Usage& usage, 
        efd::UInt8& accessFlags);

    /// @cond EMERGENT_INTERNAL

    /// Maps the data stream in response to a lock, and returns a pointer to that memory.
    void* MapBuffer(
        efd::UInt8 lockMask, 
        efd::UInt32 readLockCount,
        efd::UInt32 writeLockCount);

    /// Unmaps the data stream in response to a unlock.
    void UnmapBuffer(
        efd::UInt8 lockMask, 
        efd::UInt32 readLockCount,
        efd::UInt32 writeLockCount);

    /// Override function to direclty set the access mask on a buffer. Use with extreme caution.
    inline void SetAccessMask(efd::UInt8 accessMask);

    /// Forces any changes to the data stream to be uploaded to the D3D11 buffers.
    void UpdateD3D11Buffers(efd::Bool releaseSystemMemory = false);

    /// @endcond

protected:
    /// Hidden constructor with NiDataStreamElementSet
    D3D11DataStream(
        const NiDataStreamElementSet& elements,
        efd::UInt32 count, 
        efd::UInt8 accessMask, 
        Usage usage,
        D3D11_USAGE d3d11Usage, 
        efd::UInt32 bindFlags,
        efd::UInt32 cpuAccessFlags);

    /// Hidden constructor without NiDataStreamElementSet
    D3D11DataStream(
        efd::UInt8 accessMask, 
        Usage usage,
        D3D11_USAGE d3d11Usage, 
        efd::UInt32 bindFlags,
        efd::UInt32 cpuAccessFlags);

    /// Destructor
    virtual ~D3D11DataStream();

    /// Allocates the data for a data stream.
    virtual void Allocate();

    /// Deallocates data
    void Deallocate();

    /// Allocates the D3D11 buffer
    void D3D11Allocate(efd::Bool initialize);

    /// Copies the data from the system-memory buffer to the D3D11 buffer
    void PerformD3D11BufferUpdate();

    /// Returns whether or not a buffer with the given access mask would require a system-memory
    /// backing buffer.
    inline static efd::Bool NeedsLocalBuffer(efd::UInt8 accessMask);

    ID3D11Buffer* m_pD3D11Buffer;
    void* m_pBackingBuffer;

    efd::UInt32 m_d3d11BindFlags;
    efd::UInt32 m_d3d11CPUAccessFlags;
    D3D11_USAGE m_d3d11Usage;

    efd::Bool m_dirty;
    efd::Bool m_hidingBufferInBackingBuffer;

    friend class D3D11DataStreamFactory;
};

/// Internal D3D11DataStream class representing a data stream that can be locked.
template <class LockPolicy>
class D3D11LockableDataStream : public D3D11DataStream
{
public:
    /// @cond EMERGENT_INTERNAL

    /// Constructor with NiDataStreamElementSet
    D3D11LockableDataStream(
        const NiDataStreamElementSet& elements,
        efd::UInt32 count, 
        efd::UInt8 accessMask, 
        Usage usage,
        D3D11_USAGE d3d11Usage, 
        efd::UInt32 bindFlags,
        efd::UInt32 cpuAccessFlags);

    /// Constructor without NiDataStreamElementSet
    D3D11LockableDataStream(
        efd::UInt8 accessMask, 
        Usage usage,
        D3D11_USAGE d3d11Usage, 
        efd::UInt32 bindFlags,
        efd::UInt32 cpuAccessFlags);

    /// @endcond

protected:
    /// Destructor
    virtual ~D3D11LockableDataStream();

    /// Locks the underlying buffer with the specified constraints
    virtual void* LockImpl(efd::UInt8 lockMask);

    /// Unlocks the vertex buffer
    virtual void UnlockImpl(efd::UInt8 lockMask);

    LockPolicy m_lockPolicy;

    friend class D3D11DataStreamFactory;
};

/// Internal D3D11DataStream class representing a data stream that cannot be locked, such as
/// a stream-out buffer.
class D3D11NonLockableDataStream : public D3D11DataStream
{
public:
    /// @cond EMERGENT_INTERNAL

    /// Constructor with NiDataStreamElementSet
    D3D11NonLockableDataStream(
        const NiDataStreamElementSet& elements,
        efd::UInt32 count, 
        efd::UInt8 accessMask, 
        Usage usage,
        D3D11_USAGE d3d11Usage, 
        efd::UInt32 bindFlags,
        efd::UInt32 cpuAccessFlags);

    /// Constructor without NiDataStreamElementSet
    D3D11NonLockableDataStream(
        efd::UInt8 accessMask, 
        Usage usage,
        D3D11_USAGE d3d11Usage, 
        efd::UInt32 bindFlags,
        efd::UInt32 cpuAccessFlags);

    /// @endcond

protected:
    /// Destructor
    virtual ~D3D11NonLockableDataStream();

    /// Locks the buffer, but will always fail and return NULL unless TOOL masks used.
    virtual void* LockImpl(efd::UInt8 lockMask);

    /// Unlocks the buffer, but will do nothing unless TOOL masks used.
    virtual void UnlockImpl(efd::UInt8 lockMask);

    friend class D3D11DataStreamFactory;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11DataStream
/// class.
class D3D11DataStream;
typedef efd::SmartPointer<D3D11DataStream> D3D11DataStreamPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11DataStream.inl>

#endif // EE_D3D11DATASTREAM_H
