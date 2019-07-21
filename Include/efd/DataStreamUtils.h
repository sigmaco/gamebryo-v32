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
#ifndef EE_DATASTREAMUTILS_H
#define EE_DATASTREAMUTILS_H

#include <efd/DataStream.h>

#include <efd/Point2.h>
#include <efd/Point3.h>
#include <efd/Matrix3.h>
#include <efd/Color.h>
#include <efd/Point4.h>
#include <efd/Quaternion.h>
#include <efd/ID128.h>

namespace efd
{
    /// The following templated are for quickly marshaling data structures that contain actual
    /// data elements.  They will not work if your structure contains, for example, a pointer
    /// to the data you want marshaled instead of the data itself.  When we switch to the new
    /// Serializer system it has support for more robust data structure marshaling.
    ///

    /// @name Templated functions from DataStreamUtils.h
    //@{

    /**
        Adds the contents of the given vector to the stream.

        @param strm Stream to add values into
        @param val Values to add to the stream.
        @return A reference to the DataStream.
    */
    template< typename Data >
    inline efd::DataStream& operator<<(efd::DataStream& strm, const efd::vector< Data >& val);
    template< typename Data >

    /**
        Extract a vector from the stream.
        
        @param strm Stream to retrieve values from.
        @param val container to populate.
        @return A reference to the DataStream.
    */
    inline const efd::DataStream& operator>>(const efd::DataStream& strm, efd::vector< Data >& val);
    template< typename Data >

    /**
        Advance a DataStream past a vector.

        @param strm Stream to advance.
        @param val value to skip.
    */
    inline void DataStreamSkip(const efd::DataStream& strm, const efd::vector< Data >& val);

    /**
        Adds the contents of the given list to the stream.

        @param strm Stream to add values into
        @param val Values to add to the stream.
        @return A reference to the DataStream.
    */
    template< typename Data >
    inline efd::DataStream& operator<<(efd::DataStream& strm, const efd::list< Data >& val);

    /**
        Extract a list from the stream.

        @param strm Stream to retrieve values from.
        @param val container to populate.
        @return A reference to the DataStream.
    */
    template< typename Data >
    inline const efd::DataStream& operator>>(const efd::DataStream& strm, efd::list< Data >& val);

    /**
        Advance a DataStream past a list.

        @param strm Stream to advance.
        @param val value to skip.
    */
    template< typename Data >
    inline void DataStreamSkip(const efd::DataStream& strm, const efd::list< Data >& val);

    /**
        Adds the contents of the given map to the stream.

        @param strm Stream to add values into
        @param val Values to add to the stream.
        @return A reference to the DataStream.
    */
    template< typename Key, typename Data >
    inline efd::DataStream& operator<<(efd::DataStream& strm, const efd::map< Key, Data >& val);

    /**
        Extract a map from the stream.

        @param strm Stream to retrieve values from.
        @param val container to populate.
        @return A reference to the DataStream.
    */
    template< typename Key, typename Data >
    inline const efd::DataStream& operator>>(const efd::DataStream& strm, efd::map< Key,
        Data >& val);

    /**
        Advance a DataStream past a map.

        @param strm Stream to advance.
        @param val value to skip.
    */
    template< typename Key, typename Data >
    inline void DataStreamSkip(const efd::DataStream& strm, const efd::map< Key, Data >& val);

    //@}

    /// @name Operators from DataStreamUtils.h
    //@{

    /**
     * Adds the contents of an efd::Point2 into the stream
     *
     * @param strm Stream to add the values into
     * @param val Values to add to the stream
     * @return A reference to the IOStream
    */
    inline efd::DataStream& operator<<(efd::DataStream& strm, const efd::Point2& val);


    /**
     * Populates the efd::Point2 with data from the stream
     *
     * @param strm Stream to read the values from
     * @param val Structure to set the values in
     * @return A Reference to the IOStream
    */
    inline const efd::DataStream& operator>>(const efd::DataStream& strm, efd::Point2& val);

    /**
        Advance a DataStream past a Point2.

        @param strm Stream to advance.
        @param val value to skip.
    */
    inline void DataStreamSkip(const efd::DataStream& strm, const efd::Point2& val);


    /**
     * Adds the contents of an efd::Point3 into the stream
     *
     * @param strm Stream to add the values into
     * @param val Values to add to the stream
     * @return A reference to the IOStream
    */
    inline efd::DataStream& operator<<(efd::DataStream& strm, const efd::Point3& val);
    /**
     * Populates the efd::Point3 with data from the stream
     *
     * @param strm Stream to read the values from
     * @param val Structure to set the values in
     * @return A Reference to the IOStream
    */
    inline const efd::DataStream& operator>>(const efd::DataStream& strm, efd::Point3& val);

    /**
        Advance a DataStream past a Point3.

        @param strm Stream to advance.
        @param val value to skip.
    */
    inline void DataStreamSkip(const efd::DataStream& strm, const efd::Point3& val);



    /**
     * Adds the contents of an efd::Matrix3 into the stream
     *
     * @param strm Stream to add the values into
     * @param val Values to add to the stream
     * @return A reference to the IOStream
    */
    inline efd::DataStream& operator<<(efd::DataStream& strm, const efd::Matrix3& val);

    /**
     * Populates the efd::Matrix3 with data from the stream
     *
     * @param strm Stream to read the values from
     * @param val Structure to set the values in
     * @return A Reference to the IOStream
    */
    inline const efd::DataStream& operator>>(const efd::DataStream& strm, efd::Matrix3& val);

    /**
        Advance a DataStream past a Matrix3.

        @param strm Stream to advance.
        @param val value to skip.
    */
    inline void DataStreamSkip(const efd::DataStream& strm, const efd::Matrix3& val);


    /**
     * Adds the contents of an efd::Color into the stream
     *
     * @param strm Stream to add the values into
     * @param val Values to add to the stream
     * @return A reference to the IOStream
    */
    inline efd::DataStream& operator<<(efd::DataStream& strm, const efd::Color& val);

    /**
     * Populates the efd::Color with data from the stream
     *
     * @param strm Stream to read the values from
     * @param val Structure to set the values in
     * @return A Reference to the IOStream
    */
    inline const efd::DataStream& operator>>(const efd::DataStream& strm, efd::Color& val);

    /**
        Advance a DataStream past a color.

        @param strm Stream to advance.
        @param val value to skip.
    */
    inline void DataStreamSkip(const efd::DataStream& strm, const efd::Color& val);



    /**
     * Adds the contents of an efd::ColorA into the stream
     *
     * @param strm Stream to add the values into
     * @param val Values to add to the stream
     * @return A reference to the IOStream
    */
    inline efd::DataStream& operator<<(efd::DataStream& strm, const efd::ColorA& val);

    /**
     * Populates the efd::ColorA with data from the stream
     *
     * @param strm Stream to read the values from
     * @param val Structure to set the values in
     * @return A Reference to the IOStream
    */
    inline const efd::DataStream& operator>>(const efd::DataStream& strm, efd::ColorA& val);

    /**
        Advance a DataStream past a ColorA.

        @param strm Stream to advance.
        @param val value to skip.
    */
    inline void DataStreamSkip(const efd::DataStream& strm, const efd::ColorA& val);


    /**
    * Adds the contents of an efd::ID128 into the stream
    *
    * @param strm Stream to add the values into
    * @param val Values to add to the stream
    * @return A reference to the IOStream
    */
    inline efd::DataStream& operator<<(efd::DataStream& strm, const efd::ID128& val);

    /**
    * Populates the efd::ID128 with data from the stream
    *
    * @param strm Stream to read the values from
    * @param val Structure to set the values in
    * @return A Reference to the IOStream
    */
    inline const efd::DataStream& operator>>(const efd::DataStream& strm, efd::ID128& val);

    /**
        Advance a DataStream past a ID128.

        @param strm Stream to advance.
        @param val value to skip.
    */
    inline void DataStreamSkip(const efd::DataStream& strm, const efd::ID128& val);


    /**
    * Adds the contents of an efd::Point4 into the stream
    *
    * @param strm Stream to add the values into
    * @param val Values to add to the stream
    * @return A reference to the IOStream
    */
    inline efd::DataStream& operator<<(efd::DataStream& strm, const efd::Point4& val);

    /**
    * Populates the efd::Point4 with data from the stream
    *
    * @param strm Stream to read the values from
    * @param val Structure to set the values in
    * @return A Reference to the IOStream
    */
    inline const efd::DataStream& operator>>(const efd::DataStream& strm, efd::Point4& val);

    /**
        Advance a DataStream past a Point4.

        @param strm Stream to advance.
        @param val value to skip.
    */
    inline void DataStreamSkip(const efd::DataStream& strm, const efd::Point4& val);

    /**
    * Adds the contents of an efd::Quaternion into the stream
    *
    * @param strm Stream to add the values into
    * @param val Values to add to the stream
    * @return A reference to the IOStream
    */
    inline efd::DataStream& operator<<(efd::DataStream& strm, const efd::Quaternion& val);

    /**
    * Populates the efd::Quaternion with data from the stream
    *
    * @param strm Stream to read the values from
    * @param val Structure to set the values in
    * @return A Reference to the IOStream
    */
    inline const efd::DataStream& operator>>(const efd::DataStream& strm, efd::Quaternion& val);

    /**
        Advance a DataStream past a Quaternion.

        @param strm Stream to advance.
        @param val value to skip.
    */
    inline void DataStreamSkip(const efd::DataStream& strm, const efd::Quaternion& val);

    //@}

} // end namespace efd


#include <efd/DataStreamUtils.inl>


#endif // EE_DATASTREAMUTILS_H
