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

namespace efd
{

//------------------------------------------------------------------------------------------------
template<typename T>
inline int SequenceCompare(T lhs, T rhs)
{
    typedef typename SelectStorageForBytes<sizeof(T)>::unsignedType UT;

    // Ensure that the T used is a signed value.
    EE_COMPILETIME_ASSERT((T)(-1) < (T)(0));

    // Early out for the equal case.
    if (lhs == rhs)
        return 0;

    if (lhs)
    {
        if (rhs)
        {
            // If the left-hand-side, treated as an unsigned number, is greater than the
            // right-hand-side, then when the subtraction (rhs - lhs) is done, it will wrap past
            // zero.  Since we want to skip over zero, that means we need to subtract one more
            // number in that case.
            if ((UT)(lhs) > (UT)(rhs))
                ++lhs;

            // A >?< B
            // A-A >?< B-A
            // 0 >?< B-A
            T delta = rhs - lhs;

            if (0 >= delta)
                return 1;

            return -1;
        }

        // X > 0 is true for all X != 0
        return 1;
    }

    // 0 < X is true for all X != 0
    return -1;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline SequenceNumber<T>::SequenceNumber() : m_sequence(0)
{
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline SequenceNumber<T>::SequenceNumber(const SequenceNumber& other)
    : m_sequence(other.m_sequence)
{
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline SequenceNumber<T>::SequenceNumber(T other) : m_sequence(other)
{
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline bool SequenceNumber<T>::IsSet() const
{
    return m_sequence != 0;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline T SequenceNumber<T>::GetValue() const
{
    return m_sequence;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline void SequenceNumber<T>::operator=(const SequenceNumber& other)
{
    m_sequence = other.m_sequence;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline void SequenceNumber<T>::operator=(T other)
{
    m_sequence = other;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline bool SequenceNumber<T>::operator==(const SequenceNumber& other) const
{
    return m_sequence == other.m_sequence;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline bool SequenceNumber<T>::operator!=(const SequenceNumber& other) const
{
    return m_sequence != other.m_sequence;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline bool SequenceNumber<T>::operator>(const SequenceNumber& other) const
{
    return SequenceCompare(m_sequence, other.m_sequence) > 0;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline bool SequenceNumber<T>::operator>=(const SequenceNumber& other) const
{
    return SequenceCompare(m_sequence, other.m_sequence) >= 0;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline bool SequenceNumber<T>::operator<(const SequenceNumber& other) const
{
    return SequenceCompare(m_sequence, other.m_sequence) < 0;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline bool SequenceNumber<T>::operator<=(const SequenceNumber& other) const
{
    return SequenceCompare(m_sequence, other.m_sequence) <= 0;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline void SequenceNumber<T>::operator++()
{
    ++m_sequence;

    if (0 == m_sequence)
        ++m_sequence;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline void SequenceNumber<T>::Serialize(efd::Archive& ar)
{
    Serializer::SerializeObject(m_sequence, ar);
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
