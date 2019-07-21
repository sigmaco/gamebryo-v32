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


//------------------------------------------------------------------------------------------------
template<typename Data>
inline efd::DataStream& efd::operator<<(efd::DataStream& strm, const efd::vector< Data >& i_val)
{
    efd::UInt32 size = i_val.size();
    strm << size;
    for (efd::UInt32 i = 0; i < size; ++i)
    {
        strm << i_val[i];
    }

    return strm;
}

//------------------------------------------------------------------------------------------------
template<typename Data>
inline const efd::DataStream& efd::operator>>(const efd::DataStream& strm,
    efd::vector< Data >& o_val)
{
    efd::UInt32 size = 0;
    strm >> size;

    // DT20093 Security alert: We should check the remaining bytes in the stream so we can check if
    // the requested number of elements is feasible before we grow the vector.  This prevents
    // corrupt data from consuming massive amounts of memory leading to a crash.
    o_val.resize(size);

    for (efd::UInt32 i = 0; i < size; ++i)
    {
        strm >> o_val[i];
    }

    EE_ASSERT(o_val.size() == size);

    return strm;
}

//------------------------------------------------------------------------------------------------
template<typename Data>
inline void efd::DataStreamSkip(const efd::DataStream& strm, const efd::vector< Data >& val)
{
    efd::UInt32 size = 0;
    strm >> size;

    // NOTE: This looks shaky, I'm deliberately dereferencing a NULL pointer.  In this case
    // I happen to know that the resulting object is only used to choose a method specialization
    // and will not actually be used.
    Data* pDummyData = NULL;
    for (efd::UInt32 i = 0; i < size; ++i)
    {
        DataStreamSkip(strm, *pDummyData);
    }
}

//------------------------------------------------------------------------------------------------
template<typename Data>
inline efd::DataStream& efd::operator<<(efd::DataStream& strm, const efd::list< Data >& i_val)
{
    efd::UInt32 size = i_val.size();
    strm << size;

    typename efd::list<Data>::const_iterator iter = i_val.begin();
    for (; iter != i_val.end(); ++iter)
    {
        strm << *iter;
    }

    return strm;
}

//------------------------------------------------------------------------------------------------
template<typename Data>
inline const efd::DataStream& efd::operator>>(const efd::DataStream& strm,
    efd::list< Data >& o_val)
{
    efd::UInt32 size = 0;
    strm >> size;

    // DT20093 Security alert: We should check the remaining bytes in the stream so we can check if
    // the requested number of elements is feasible before we grow the vector.  This prevents
    // corrupt data from consuming massive amounts of memory leading to a crash.

    for (efd::UInt32 i = 0; i < size; ++i)
    {
        Data temp;
        strm >> temp;
        o_val.push_tail(temp);
    }

    EE_ASSERT(o_val.size() == size);

    return strm;
}

//------------------------------------------------------------------------------------------------
template<typename Data>
inline void efd::DataStreamSkip(const efd::DataStream& strm, const efd::list< Data >& o_val)
{
    efd::UInt32 size = 0;
    strm >> size;

    // NOTE: This looks shaky, I'm deliberately dereferencing a NULL pointer.  In this case
    // I happen to know that the resulting object is only used to choose a method specialization
    // and will not actually be used.
    Data* pDummyData = NULL;
    for (efd::UInt32 i = 0; i < size; ++i)
    {
        DataStreamSkip(strm, *pDummyData);
    }
}

//------------------------------------------------------------------------------------------------
template< typename Key, typename Data >
inline efd::DataStream& efd::operator<<(efd::DataStream& strm, const efd::map< Key, Data >& i_val)
{
    efd::UInt32 size = (efd::UInt32)i_val.size();
    strm << size;

    typename efd::map<Key,Data>::const_iterator iter = i_val.begin();
    for (; iter != i_val.end(); ++iter)
    {
        strm << iter->first;
        strm << iter->second;
    }

    return strm;
}

//------------------------------------------------------------------------------------------------
template< typename Key, typename Data >
inline const efd::DataStream& efd::operator>>(const efd::DataStream& strm, efd::map< Key,
    Data >& o_val)
{
    efd::UInt32 size = 0;
    strm >> size;

    // DT20093 Security alert: We should check the remaining bytes in the stream so we can check if
    // the requested number of elements is feasible before we grow the vector.  This prevents
    // corrupt data from consuming massive amounts of memory leading to a crash.
    for (efd::UInt32 i = 0; i < size; ++i)
    {
        Key key;
        strm >> key;

        Data data;
        strm >> data;

        o_val[key] = data;
    }

    return strm;
}

//------------------------------------------------------------------------------------------------
template< typename Key, typename Data >
inline void efd::DataStreamSkip(const efd::DataStream& strm, const efd::map< Key, Data >& o_val)
{
    efd::UInt32 size = 0;
    strm >> size;

    // NOTE: This looks shaky, I'm deliberately dereferencing a NULL pointer.  In this case
    // I happen to know that the resulting object is only used to choose a method specialization
    // and will not actually be used.
    Key* pDummyKey = NULL;
    Data* pDummyData = NULL;
    for (efd::UInt32 i = 0; i < size; ++i)
    {
        DataStreamSkip(strm, *pDummyKey);
        DataStreamSkip(strm, *pDummyData);
    }

    EE_UNUSED_ARG(o_val);
}

//------------------------------------------------------------------------------------------------
inline efd::DataStream& efd::operator<<(efd::DataStream& strm, const efd::Point2& val)
{
    strm << val.x;
    strm << val.y;

    return strm;
}

//------------------------------------------------------------------------------------------------
inline const efd::DataStream& efd::operator>>(const efd::DataStream& strm, efd::Point2& val)
{
    strm >> val.x;
    strm >> val.y;

    return strm;
}

//------------------------------------------------------------------------------------------------
inline void efd::DataStreamSkip(const efd::DataStream& strm, const efd::Point2& val)
{
    strm.SeekFromCurrentPos(2 * sizeof(efd::Float32));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline efd::DataStream& efd::operator<<(efd::DataStream& strm, const efd::Point3& val)
{
    strm << val.x;
    strm << val.y;
    strm << val.z;

    return strm;
}

//------------------------------------------------------------------------------------------------
inline const efd::DataStream& efd::operator>>(const efd::DataStream& strm, efd::Point3& val)
{
    strm >> val.x;
    strm >> val.y;
    strm >> val.z;

    return strm;
}

//------------------------------------------------------------------------------------------------
inline void efd::DataStreamSkip(const efd::DataStream& strm, const efd::Point3& val)
{
    strm.SeekFromCurrentPos(3 * sizeof(efd::Float32));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline efd::DataStream& efd::operator<<(efd::DataStream& strm, const efd::Point4& val)
{
    strm << val.W();
    strm << val.X();
    strm << val.Y();
    strm << val.Z();
    return strm;
}

//------------------------------------------------------------------------------------------------
inline const efd::DataStream& efd::operator>>(const efd::DataStream& strm, efd::Point4& val)
{
    efd::Float32 tmp;
    strm >> tmp;
    val.SetW(tmp);
    strm >> tmp;
    val.SetX(tmp);
    strm >> tmp;
    val.SetY(tmp);
    strm >> tmp;
    val.SetZ(tmp);

    return strm;
}

//------------------------------------------------------------------------------------------------
inline void efd::DataStreamSkip(const efd::DataStream& strm, const efd::Point4& val)
{
    strm.SeekFromCurrentPos(4 * sizeof(efd::Float32));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline efd::DataStream& efd::operator<<(efd::DataStream& strm, const efd::Quaternion& val)
{
    strm << val.GetW();
    strm << val.GetX();
    strm << val.GetY();
    strm << val.GetZ();
    return strm;
}

//------------------------------------------------------------------------------------------------
inline const efd::DataStream& efd::operator>>(const efd::DataStream& strm, efd::Quaternion& val)
{
    efd::Float32 tmp;
    strm >> tmp;
    val.SetW(tmp);
    strm >> tmp;
    val.SetX(tmp);
    strm >> tmp;
    val.SetY(tmp);
    strm >> tmp;
    val.SetZ(tmp);

    return strm;
}

//------------------------------------------------------------------------------------------------
inline void efd::DataStreamSkip(const efd::DataStream& strm, const efd::Quaternion& val)
{
    strm.SeekFromCurrentPos(4 * sizeof(efd::Float32));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline efd::DataStream& efd::operator<<(efd::DataStream& strm, const efd::Matrix3& val)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            strm << val.GetEntry(row, col);
        }
    }

    return strm;
}

//------------------------------------------------------------------------------------------------
inline const efd::DataStream& efd::operator>>(const efd::DataStream& strm, efd::Matrix3& val)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            float fEntry;
            strm >> fEntry;
            val.SetEntry(row, col, fEntry);
        }
    }

    return strm;
}

//------------------------------------------------------------------------------------------------
inline void efd::DataStreamSkip(const efd::DataStream& strm, const efd::Matrix3& val)
{
    strm.SeekFromCurrentPos(9 * sizeof(efd::Float32));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline efd::DataStream& efd::operator<<(efd::DataStream& strm, const efd::Color& val)
{
    strm << val.m_r;
    strm << val.m_g;
    strm << val.m_b;

    return strm;
}

//------------------------------------------------------------------------------------------------
inline const efd::DataStream& efd::operator>>(const efd::DataStream& strm, efd::Color& val)
{
    strm >> val.m_r;
    strm >> val.m_g;
    strm >> val.m_b;

    return strm;
}

//------------------------------------------------------------------------------------------------
inline void efd::DataStreamSkip(const efd::DataStream& strm, const efd::Color& val)
{
    strm.SeekFromCurrentPos(3 * sizeof(efd::Float32));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline efd::DataStream& efd::operator<<(efd::DataStream& strm, const efd::ColorA& val)
{
    strm << val.m_r;
    strm << val.m_g;
    strm << val.m_b;
    strm << val.m_a;

    return strm;
}

//------------------------------------------------------------------------------------------------
inline const efd::DataStream& efd::operator>>(const efd::DataStream& strm, efd::ColorA& val)
{
    strm >> val.m_r;
    strm >> val.m_g;
    strm >> val.m_b;
    strm >> val.m_a;

    return strm;
}

//------------------------------------------------------------------------------------------------
inline void efd::DataStreamSkip(const efd::DataStream& strm, const efd::ColorA& val)
{
    strm.SeekFromCurrentPos(4 * sizeof(efd::Float32));
    EE_UNUSED_ARG(val);
}

//------------------------------------------------------------------------------------------------
inline efd::DataStream& efd::operator<<(efd::DataStream& strm, const efd::ID128& val)
{
    strm.WriteRawBuffer((void *)val.m_value, 16 * sizeof(efd::UInt8));

    return strm;
}

//------------------------------------------------------------------------------------------------
inline const efd::DataStream& efd::operator>>(const efd::DataStream& strm, efd::ID128& val)
{
    strm.ReadRawBuffer(val.m_value, 16 * sizeof(efd::UInt8));

    return strm;
}

//------------------------------------------------------------------------------------------------
inline void efd::DataStreamSkip(const efd::DataStream& strm, const efd::ID128& val)
{
    strm.SeekFromCurrentPos(16 * sizeof(efd::UInt8));
    EE_UNUSED_ARG(val);
}
