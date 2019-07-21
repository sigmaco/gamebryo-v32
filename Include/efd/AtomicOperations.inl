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

//-------------------------------------------------------------------------------------------------
template <typename T>
inline void Atomic::SetValue(volatile T* pDestination, T newValue)
{
    do
    {
    } while (!Atomic::CompareAndSwap(pDestination, *pDestination, newValue));
}
//-------------------------------------------------------------------------------------------------
template <typename T>
inline T Atomic::CompareAndSwapReturnInit(volatile T* pDestination, T comparand, T exchange)
{
    typedef typename SelectMatchingUIntBySize<sizeof(T), T>::Result CompatibleType;

    return (T)AtomicCompareAndSwap(
        (volatile CompatibleType*)(pDestination),
        (CompatibleType)comparand,
        (CompatibleType)exchange);
}
//-------------------------------------------------------------------------------------------------
template <typename T>
inline bool Atomic::CompareAndSwap(volatile T* pDestination, T comparand, T exchange)
{
    typedef typename SelectMatchingUIntBySize<sizeof(T), T>::Result CompatibleType;

    return ((T)AtomicCompareAndSwap(
        (volatile CompatibleType*)(pDestination),
        (CompatibleType)comparand,
        (CompatibleType)exchange)) == comparand;
}
//-------------------------------------------------------------------------------------------------

} // end namespace efd
