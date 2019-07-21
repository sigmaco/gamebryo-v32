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

#include <efd/Color.h>
#include <efd/Point2.h>
#include <efd/Point3.h>
#include <efd/Point4.h>
#include <efd/Matrix3.h>
#include <efd/Quaternion.h>
#include <efd/ID128.h>
#include <efd/AssetID.h>

namespace efd
{

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(bool val)
{
    // Unlike most of the other write methods to stream, we must cast bool to one of the known
    // types since standard "bool" can be different sizes across platforms.
    efd::UInt8 bval = val;
    WriteRawBuffer(reinterpret_cast < void * > (&bval), sizeof(efd::UInt8));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(efd::SInt8 val)
{
    WriteRawBuffer(reinterpret_cast < void * > (&val), sizeof(efd::SInt8));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(efd::UInt8 val)
{
    WriteRawBuffer(reinterpret_cast < void * > (&val), sizeof(efd::UInt8));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(efd::SInt16 val)
{
    Swap16(reinterpret_cast< efd::UInt8* >(&val));
    WriteRawBuffer(reinterpret_cast < void * > (&val), sizeof(efd::SInt16));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(efd::UInt16 val)
{
    Swap16(reinterpret_cast< efd::UInt8* >(&val));
    WriteRawBuffer(reinterpret_cast < void * > (&val), sizeof(efd::UInt16));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(efd::SInt32 val)
{
    Swap32(reinterpret_cast< efd::UInt8* >(&val));
    WriteRawBuffer(reinterpret_cast < void * > (&val), sizeof(efd::SInt32));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(efd::UInt32 val)
{
    Swap32(reinterpret_cast< efd::UInt8* >(&val));
    WriteRawBuffer(reinterpret_cast < void * > (&val), sizeof(efd::UInt32));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(efd::SInt64 val)
{
    Swap64(reinterpret_cast< efd::UInt8* >(&val));
    WriteRawBuffer(reinterpret_cast < void * > (&val), sizeof(efd::SInt64));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(efd::UInt64 val)
{
    Swap64(reinterpret_cast< efd::UInt8* >(&val));
    WriteRawBuffer(reinterpret_cast < void * > (&val), sizeof(efd::UInt64));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(efd::Float32 val)
{
    Swap32(reinterpret_cast< efd::UInt8* >(&val));
    WriteRawBuffer(reinterpret_cast < void * > (&val), sizeof(efd::Float32));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(efd::Float64 val)
{
    Swap64(reinterpret_cast< efd::UInt8* >(&val));
    WriteRawBuffer(reinterpret_cast < void * > (&val), sizeof(efd::Float64));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::utf8string& val)
{
    // size_t is 64bit on 64bit platforms.  Strings that have sizes larger than 32bits are not
    // supported.
    efd::UInt32 size = static_cast<efd::UInt32>(val.size());
    Write(size);
    WriteRawBuffer(val.data(), size);   // val.data() pts to raw buffer in efd::utf8string.
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::utf8char_t& val)
{
    efd::UInt8 size = (efd::UInt8) val.size();  // This size is never > 4.
    Write(size);
    WriteRawBuffer (val.c_str(), val.size());   // val.c_str() pts to raw buffer in utf8char_t.
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::utf16char_t& val)
{
    efd::UInt8 size = (efd::UInt8) val.size();  // This size is never > 2.
    Write(size);
    WriteRawBuffer(val.c_str(), val.size()*2); // val.c_str() pts to raw buffer in utf16char_t.
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::Color& val)
{
    Write(val.m_r);
    Write(val.m_g);
    Write(val.m_b);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::ColorA& val)
{
    Write(val.m_r);
    Write(val.m_g);
    Write(val.m_b);
    Write(val.m_a);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::Matrix3& val)
{
    Point3 row;
    val.GetRow(0, row);
    Write(row);
    val.GetRow(1, row);
    Write(row);
    val.GetRow(2, row);
    Write(row);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::Point2& val)
{
    Write(val.x);
    Write(val.y);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::Point3& val)
{
    Write(val.x);
    Write(val.y);
    Write(val.z);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::Point4& val)
{
    Write(val.W());
    Write(val.X());
    Write(val.Y());
    Write(val.Z());
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::Quaternion& val)
{
    Write(val.GetW());
    Write(val.GetX());
    Write(val.GetY());
    Write(val.GetZ());
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::ID128& val)
{
    for (efd::UInt8 ui = 0; ui < 16; ++ui)
        Write(val.m_value[ui]);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Write(const efd::AssetID& val)
{
    Write(val.GetURN());
    Write(val.GetMultiplicity());
    Write(static_cast<efd::UInt32>(val.GetCachingPolicy()));
}

//------------------------------------------------------------------------------------------------
inline size_t DataStream::GetPos() const
{
    return m_pCurrentStreamPos - m_buffer;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// Read from Stream: Standard Types

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(bool& val) const
{
    efd::UInt8    bval;
    // Unlike most of the other read methods to stream, use the known sized value from stream, and
    // then give it to the user, since standard "bool" can be different sizes across platforms.
    ReadRawBuffer(&bval, sizeof(bval));
    val = bval ? true : false;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// Read from Stream: UniveralTypes

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::SInt8& val) const
{
    ReadRawBuffer(&val, sizeof(efd::SInt8));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::UInt8& val) const
{
    ReadRawBuffer(&val, sizeof(efd::UInt8));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::SInt16& val) const
{
    ReadRawBuffer(&val, sizeof(efd::SInt16));
    Swap16(reinterpret_cast< efd::UInt8* >(&val));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::UInt16& val) const
{
    ReadRawBuffer(&val, sizeof(efd::UInt16));
    Swap16(reinterpret_cast< efd::UInt8* >(&val));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::SInt32& val) const
{
    ReadRawBuffer(&val, sizeof(efd::SInt32));
    Swap32(reinterpret_cast< efd::UInt8* >(&val));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::UInt32& val) const
{
    ReadRawBuffer(&val, sizeof(efd::UInt32));
    Swap32(reinterpret_cast< efd::UInt8* >(&val));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::SInt64& val) const
{
    ReadRawBuffer(&val, sizeof(efd::SInt64));
    Swap64(reinterpret_cast< efd::UInt8* >(&val));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::UInt64& val) const
{
    ReadRawBuffer(&val, sizeof(efd::UInt64));
    Swap64(reinterpret_cast< efd::UInt8* >(&val));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::Float32& val) const
{
    ReadRawBuffer(&val, sizeof(efd::Float32));
    Swap32(reinterpret_cast< efd::UInt8* >(&val));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::Float64& val) const
{
    ReadRawBuffer(&val, sizeof(efd::Float64));
    Swap64(reinterpret_cast< efd::UInt8* >(&val));
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::utf8string& val) const
{
    efd::UInt32 size = 0;
    Read(size);

    // DT20092 Security fix: before blindly allocating a potentially huge amount of memory here, we
    // should ensure that the DataStream has at least size remaining bytes in the stream.  Also, it
    // is critical that we ensure the Read above actually succeeded before we continue or we will
    // use the wrong size to allocate!

    // This read into a temporary buffer is required since the string may actually cross multiple
    // internal buffers.  Also, the NULL terminator was stripped off when this stream was written,
    // so it should be replaced.
    efd::Char* cTmp = EE_ALLOC(efd::Char,size+1);
    ReadRawBuffer(cTmp, size);
    cTmp[size] = 0;

    val = cTmp;

    EE_FREE(cTmp);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::utf8char_t& val) const
{
    // DT20094 Streaming the size is not required; we should remove it to reduce size.
    efd::UInt8 size = 0;    // This size is never > 4.
    Read(size);

    if (size <= 4)
    {
        // This read into a temporary buffer is required since the string may actually cross
        // multiple internal buffers.
        efd::Char cTmp[5];
        ReadRawBuffer(cTmp, size);
        cTmp[size] = 0;

        val = efd::utf8char_t::from_stream(cTmp);
    }
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::utf16char_t& val) const
{
    // DT20094 Streaming the size is not required; we should remove it to reduce size.
    efd::UInt8 size = 0;    // This size is never > 2.
    Read(size);

    if (size <= 2)
    {
        // This read into a temporary buffer is required since the string may actually cross
        // multiple internal buffers.
        efd::WChar cTmp[3];
        ReadRawBuffer(cTmp, size*sizeof(efd::WChar));
        cTmp[size] = 0;

        val = efd::utf16char_t::from_stream(cTmp);
    }
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(Color& val) const
{
    Read(val.m_r);
    Read(val.m_g);
    Read(val.m_b);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(ColorA& val) const
{
    Read(val.m_r);
    Read(val.m_g);
    Read(val.m_b);
    Read(val.m_a);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(Matrix3& val) const
{
    Point3 row;
    Read(row);
    val.SetRow(0, row);
    Read(row);
    val.SetRow(1, row);
    Read(row);
    val.SetRow(2, row);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(Point2& val) const
{
    Read(val.x);
    Read(val.y);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::Point3& val) const
{
    Read(val.x);
    Read(val.y);
    Read(val.z);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::Point4& val) const
{
    efd::Float32 component;
    Read(component);
    val.SetW(component);
    Read(component);
    val.SetX(component);
    Read(component);
    val.SetY(component);
    Read(component);
    val.SetZ(component);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::Quaternion& val) const
{
    Read(val.m_fW);
    Read(val.m_fX);
    Read(val.m_fY);
    Read(val.m_fZ);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::ID128& val) const
{
    for (efd::UInt8 ui = 0; ui < 16; ++ui)
        Read(val.m_value[ui]);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Read(efd::AssetID& val) const
{
    utf8string urn;
    efd::UInt8 multiplicity;
    efd::UInt32 cachingPolicy;

    Read(urn);
    Read(multiplicity);
    Read(cachingPolicy);

    val.SetURN(urn);
    val.SetMultiplicity(multiplicity);
    val.SetCachingPolicy(static_cast<AssetID::CachingPolicy>(cachingPolicy));
}

//------------------------------------------------------------------------------------------------
// Skip the stream forward by the size needed for each type: Standard Types

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const bool& val) const
{
    // Unlike most of the other read methods to stream, use the known sized value from stream;
    // then give it to the user, since standard "bool" can be different sizes across platforms.
    SeekFromCurrentPos(sizeof(efd::UInt8));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// Skip the stream forward by the size needed for each type: UniveralTypes

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::SInt8& val) const
{
    SeekFromCurrentPos(sizeof(efd::SInt8));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::UInt8& val) const
{
    SeekFromCurrentPos(sizeof(efd::UInt8));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::SInt16& val) const
{
    SeekFromCurrentPos(sizeof(efd::SInt16));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::UInt16& val) const
{
    SeekFromCurrentPos(sizeof(efd::UInt16));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::SInt32& val) const
{
    SeekFromCurrentPos(sizeof(efd::SInt32));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::UInt32& val) const
{
    SeekFromCurrentPos(sizeof(efd::UInt32));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::SInt64& val) const
{
    SeekFromCurrentPos(sizeof(efd::SInt64));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::UInt64& val) const
{
    SeekFromCurrentPos(sizeof(efd::UInt64));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::Float32& val) const
{
    SeekFromCurrentPos(sizeof(efd::Float32));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::Float64& val) const
{
    SeekFromCurrentPos(sizeof(efd::Float64));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::utf8string& val) const
{
    efd::UInt32 size = 0;
    Read(size);

    // DT20092 Security fix: before blindly allocating a potentially huge amount of memory here, we
    // should ensure that the DataStream has at least size remaining bytes in the stream.  Also, it
    // is critical that we ensure the Read above actually succeeded before we continue or we will
    // use the wrong size to allocate!

    SeekFromCurrentPos(size);
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::utf8char_t& val) const
{
    // DT20094 Streaming the size is not required; we should remove it to reduce size.
    efd::UInt8 size = 0;    // This size is never > 4.
    Read(size);

    if (size <= 4)
    {
        // This read into a temporary buffer is required since the string may actually cross
        // multiple internal buffers.
        SeekFromCurrentPos(size);
    }
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::utf16char_t& val) const
{
    // DT20094 Streaming the size is not required; we should remove it to reduce size.
    efd::UInt8 size = 0;    // This size is never > 2.
    Read(size);

    if (size <= 2)
    {
        // This read into a temporary buffer is required since the string may actually cross
        // multiple internal buffers
        SeekFromCurrentPos(size*sizeof(efd::WChar));
    }
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::Color& val) const
{
    SeekFromCurrentPos(sizeof(efd::Float32) * 3);
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::ColorA& val) const
{
    SeekFromCurrentPos(sizeof(efd::Float32) * 4);
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::Matrix3& val) const
{
    efd::Point3 point;
    Skip(point);
    Skip(point);
    Skip(point);
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::Point2& val) const
{
    SeekFromCurrentPos(sizeof(efd::Float32) * 2);
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::Point3& val) const
{
    SeekFromCurrentPos(sizeof(efd::Float32) * 3);
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::Point4& val) const
{
    SeekFromCurrentPos(sizeof(efd::Float32) * 4);
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::Quaternion& val) const
{
    SeekFromCurrentPos(sizeof(efd::Float32) * 4);
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::ID128& val) const
{
    SeekFromCurrentPos(sizeof(efd::UInt8) * 16);
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Skip(const efd::AssetID& val) const
{
    utf8string urn;
    efd::UInt8 multiplicity;
    efd::UInt32 cachingPolicy;

    Skip(urn);
    Skip(multiplicity);
    Skip(cachingPolicy);
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
// Set endianess for this stream.
inline void DataStream::SetEndian(efd::StreamInfo::Endian eType)
{
    m_spStreamInfo->SetEndian(eType);
}

//------------------------------------------------------------------------------------------------
// Get endianess for this stream.
inline efd::StreamInfo::Endian DataStream::GetEndian () const
{
    return m_spStreamInfo->GetEndian();
}

//------------------------------------------------------------------------------------------------
// Set variant (state ID) for this stream.  Variants are a state enumeration that can be used to
// differentiate a stream condition (in packing/unpacking).
inline void DataStream::SetVariant(efd::SInt32 var)
{
    m_spStreamInfo->SetVariant(var);
}

//------------------------------------------------------------------------------------------------
// Get variant (state ID) for this stream.  Variants are a state enumeration that can be used to
// differentiate a stream condition (in packing/unpacking).
inline efd::SInt32 DataStream::GetVariant() const
{
    return m_spStreamInfo->GetVariant();
}

//------------------------------------------------------------------------------------------------
// Set version ID for this stream.
inline void DataStream::SetVersion(efd::UInt32 version)
{
    m_spStreamInfo->SetVersion(version);
}

//------------------------------------------------------------------------------------------------
// Get version ID for this stream.
inline efd::UInt32 DataStream::GetVersion() const
{
    return m_spStreamInfo->GetVersion();
}

//------------------------------------------------------------------------------------------------
inline void DataStream::SetReadOnly() const
{
    m_readOnly = true;
}

//------------------------------------------------------------------------------------------------
inline bool DataStream::IsReadOnly() const
{
    return m_readOnly;
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Reset() const
{
    m_pCurrentStreamPos = m_buffer;
}

//------------------------------------------------------------------------------------------------
inline size_t DataStream::GetSize() const
{
    return m_usedBytes;
}

//------------------------------------------------------------------------------------------------
bool DataStream::SeekFromCurrentPos(size_t bytes) const
{
    return Seek(GetPos() + bytes);
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// Byte swap helpers.

//------------------------------------------------------------------------------------------------
void DataStream::Swap16 (efd::UInt8* buf) const
{
    if (m_spStreamInfo->NeedsSwap())
    {
        efd::UInt8 tmp = buf[0];
        buf[0] = buf[1];
        buf[1] = tmp;
    }
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Swap32 (efd::UInt8* buf) const
{
    if (m_spStreamInfo->NeedsSwap())
    {
        efd::UInt8 tmp = buf[0];
        buf[0] = buf[3];
        buf[3] = tmp;
        tmp = buf[1];
        buf[1] = buf[2];
        buf[2] = tmp;
    }
}

//------------------------------------------------------------------------------------------------
inline void DataStream::Swap64 (efd::UInt8* buf) const
{
    if (m_spStreamInfo->NeedsSwap())
    {
        efd::UInt8 tmp = buf[0];
        buf[0] = buf[7];
        buf[7] = tmp;
        tmp = buf[1];
        buf[1] = buf[6];
        buf[6] = tmp;
        tmp = buf[2];
        buf[2] = buf[5];
        buf[5] = tmp;
        tmp = buf[3];
        buf[3] = buf[4];
        buf[4] = tmp;
    }
}

//------------------------------------------------------------------------------------------------
inline const UInt8* DataStream::GetRawBuffer() const
{
    return m_pCurrentStreamPos;
}

//------------------------------------------------------------------------------------------------
inline size_t DataStream::GetRawBytesRemaining() const
{
    return m_pCurrentStreamPos - m_buffer;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// StreamInfo support methods

//------------------------------------------------------------------------------------------------
// Set Endianess for this stream.
inline void StreamInfo::SetEndian(efd::StreamInfo::Endian eType)
{
    m_endian = eType;
}

//------------------------------------------------------------------------------------------------
// Get Endianess for this stream.
inline efd::StreamInfo::Endian StreamInfo::GetEndian () const
{
    return m_endian;
}

//------------------------------------------------------------------------------------------------
// Set variant (state ID) for this stream.  Variants are a state enumeration that can be used to
// differentiate a stream condition (in packing/unpacking).
inline void StreamInfo::SetVariant(efd::SInt32 var)
{
    m_variant = var;
}

//------------------------------------------------------------------------------------------------
// Get variant (state ID) for this stream.  Variants are a state enumeration that can be used to
// differentiate a stream condition (in packing/unpacking).
inline efd::SInt32 StreamInfo::GetVariant() const
{
    return m_variant;
}

//------------------------------------------------------------------------------------------------
// Set version ID for this stream.
inline void StreamInfo::SetVersion(efd::UInt32 version)
{
    m_version = version;
}

//------------------------------------------------------------------------------------------------
// Get version ID for this stream.
inline efd::UInt32 StreamInfo::GetVersion() const
{
    return m_version;
}

//------------------------------------------------------------------------------------------------
inline bool StreamInfo::IsHostLittleEndian()
{
    static union { int i; char a[4]; } u = {1};
    return u.a[0] == 1;
}

//------------------------------------------------------------------------------------------------
inline bool StreamInfo::NeedsSwap() const
{
    return (((m_endian == StreamInfo::Endian_Little) && !IsHostLittleEndian()) ||
             ((m_endian == StreamInfo::Endian_Big) && IsHostLittleEndian()));
}

} // end namespace efd
