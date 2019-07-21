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

//--------------------------------------------------------------------------------------------------
template <class C, class T>
inline void NiSPAlgorithms::QuickSortObjects(C* pkCollection, NiInt32 iLeft,
    NiInt32 iRight)
{
    if (iRight <= iLeft)
        return;
    NiInt32 iPartition =
        NiSPAlgorithms::Internal::PartitionObjects<C, T>(pkCollection, iLeft, iRight);
    QuickSortObjects<C, T>(pkCollection, iLeft, iPartition - 1);
    QuickSortObjects<C, T>(pkCollection, iPartition + 1, iRight);
}

//--------------------------------------------------------------------------------------------------
template <class C, class T>
inline void NiSPAlgorithms::QuickSortPointers(C* pkCollection, NiInt32 iLeft,
    NiInt32 iRight)
{
    if (iRight <= iLeft)
        return;
    NiInt32 iPartition =
        NiSPAlgorithms::Internal::PartitionPointers<C, T>(pkCollection, iLeft, iRight);
    QuickSortPointers<C, T>(pkCollection, iLeft, iPartition - 1);
    QuickSortPointers<C, T>(pkCollection, iPartition + 1, iRight);
}

//--------------------------------------------------------------------------------------------------
template <class C, class T>
inline NiInt32 NiSPAlgorithms::Internal::PartitionObjects(C* pkCollection, NiInt32 iLeft,
    NiInt32 iRight)
{
    NiInt32 i = iLeft - 1;
    NiInt32 j = iRight;
    const T& kElement = pkCollection->GetAt(iRight);

    for (;;)
    {
        while (pkCollection->GetAt(++i) < kElement) { }
        while (kElement < pkCollection->GetAt(--j))
            if (j == iLeft)
                break;
        if (i >= j)
            break;
        NiSPAlgorithms::Internal::SwapObjects<C, T>(pkCollection, i, j);
    }
    NiSPAlgorithms::Internal::SwapObjects<C, T>(pkCollection, i, iRight);

    return i;
}

//--------------------------------------------------------------------------------------------------
template <class C, class T>
inline NiInt32 NiSPAlgorithms::Internal::PartitionPointers(C* pkCollection, NiInt32 iLeft,
                                         NiInt32 iRight)
{
    NiInt32 i = iLeft - 1;
    NiInt32 j = iRight;
    T pkElement = pkCollection->GetAt(iRight);

    for (;;)
    {
        while (*pkCollection->GetAt(++i) < *pkElement) { }
        while (*pkElement < *pkCollection->GetAt(--j))
            if (j == iLeft)
                break;
        if (i >= j)
            break;
        NiSPAlgorithms::Internal::SwapPointers<C, T>(pkCollection, i, j);
    }
    NiSPAlgorithms::Internal::SwapPointers<C, T>(pkCollection, i, iRight);

    return i;
}

//--------------------------------------------------------------------------------------------------
template <class C, class T>
inline void NiSPAlgorithms::Internal::SwapObjects(C* pkCollection, NiInt32 iAtIndex1,
    NiInt32 iAtIndex2)
{
    const T& kTmp = pkCollection->GetAt(iAtIndex1);
    pkCollection->ReplaceAt(iAtIndex1, pkCollection->GetAt(iAtIndex2));
    pkCollection->ReplaceAt(iAtIndex2, kTmp);
}

//--------------------------------------------------------------------------------------------------
template <class C, class T>
inline void NiSPAlgorithms::Internal::SwapPointers(C* pkCollection, NiInt32 iAtIndex1,
    NiInt32 iAtIndex2)
{
    T pkTmp = pkCollection->GetAt(iAtIndex1);
    pkCollection->ReplaceAt(iAtIndex1, pkCollection->GetAt(iAtIndex2));
    pkCollection->ReplaceAt(iAtIndex2, pkTmp);
}

//--------------------------------------------------------------------------------------------------
template <>
inline void NiSPAlgorithms::Internal::SwapPointers< NiTObjectPtrSet<NiSPTaskPtr>, NiSPTaskPtr >
    (NiTObjectPtrSet<NiSPTaskPtr>* pkCollection, NiInt32 iIndex1, NiInt32 iIndex2)
{
    pkCollection->GetAt(iIndex1).Swap(pkCollection->GetAt(iIndex2));
}

//--------------------------------------------------------------------------------------------------
inline NiUInt64 NiSPAlgorithms::Align128(NiUInt64 uiSize)
{
    return (uiSize + 127) & ~127;
}

//--------------------------------------------------------------------------------------------------
inline void* NiSPAlgorithms::PreAlign128(void* uiSize)
{
    return (void*)(((NiUInt64)uiSize) & ~127);
}

//--------------------------------------------------------------------------------------------------
