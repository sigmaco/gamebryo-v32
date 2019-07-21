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
template <typename TRegionFunctor>
inline bool NiMeshAlgorithms::ForEachUniqueRegion(
    NiMesh* pkMesh,
    const NiFixedString& kSemantic,
    NiUInt32 uiSemanticIndex,
    TRegionFunctor& kFunc,
    NiUInt8 ucLockMask)
{
    EE_ASSERT(pkMesh);

    NiDataStreamRef* pkStreamRef;
    NiDataStreamElement kElement;

    // Make sure that the element actually exists
    if (!pkMesh->FindStreamRefAndElementBySemantic(kSemantic, uiSemanticIndex,
        NiDataStreamElement::F_UNKNOWN, pkStreamRef, kElement))
    {
        return false;
    }

    if (!pkStreamRef)
        return false;

    NiDataStream* pkDataStream = pkStreamRef->GetDataStream();

    if (!pkDataStream)
        return false;

    NiUInt32 uiStride = pkDataStream->GetStride();
    NiUInt32 uiElementOffset = kElement.GetOffset();

    void* pData = pkDataStream->Lock(ucLockMask);

    if (pData == NULL)
        return false;

    for (NiUInt32 uiSubmesh = 0; uiSubmesh < pkMesh->GetSubmeshCount();
        uiSubmesh++)
    {
        NiUInt32 uiRegion = pkStreamRef->GetRegionIndexForSubmesh(uiSubmesh);

        bool bUnvisited = true;

        // Since we may be iterating over a large array of data, and
        // regions may be duplicated, we ignore previously visited regions.
        for (NiUInt32 uiPrevSubmesh = 0; uiPrevSubmesh < uiSubmesh;
            uiPrevSubmesh++)
        {
            NiUInt32 uiPrevRegion = pkStreamRef->GetRegionIndexForSubmesh(
                uiPrevSubmesh);

            if (uiRegion == uiPrevRegion)
            {
                bUnvisited = false;
                break;
            }
        }

        // If we haven't visited this vertex region, then pass the region
        // to the functor.
        if (bUnvisited)
        {
            NiDataStream::Region& pkRegion =
                pkStreamRef->GetRegionForSubmesh(uiSubmesh);

            void* pRegionDataBegin = pkRegion.ComputeStart(pData, uiStride,
                uiElementOffset);
            void* pRegionDataEnd = pkRegion.ComputeEnd(pData, uiStride);

            kFunc(pRegionDataBegin, pRegionDataEnd, uiStride,
                kElement.GetFormat());
        }
    }
    pkDataStream->Unlock(ucLockMask);

    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachPrimitiveAllSubmeshes(
    NiMesh* pkMesh,
    TPrimitiveFunctor& kFunctor,
    NiUInt8 ucLockMask,
    bool bAllowEarlyOut)
{
    EE_ASSERT(pkMesh);

    NiDataStreamRef* pkStreamRef;
    NiDataStreamElement kElement;

    bool bIndicesExist = false;

    // Make sure that the element actually exists
    if (pkMesh->FindStreamRefAndElementBySemantic(NiCommonSemantics::INDEX(),
        0, NiDataStreamElement::F_UNKNOWN, pkStreamRef, kElement))
    {
        bIndicesExist = true;
    }
    else
    {
        // If the indices don't exist, find the positions
        if (!pkMesh->FindStreamRefAndElementBySemantic(
            NiCommonSemantics::POSITION(), 0,
            NiDataStreamElement::F_UNKNOWN, pkStreamRef, kElement))
        {
            return false;
        }
    }

    if (!pkStreamRef)
        return false;

    if (!kElement.IsValid())
        return false;

    NiDataStream* pkDataStream = pkStreamRef->GetDataStream();

    if (!pkDataStream)
        return false;

    if (bIndicesExist)
    {
        for (NiUInt32 ui = 0; ui < pkMesh->GetSubmeshCount(); ui++)
        {
            NiUInt32 uiRegion =
                pkStreamRef->GetRegionIndexForSubmesh(ui);
            if (!ForEachPrimitiveByRegion(pkMesh->GetPrimitiveType(),
                pkDataStream, uiRegion, (NiUInt16)ui, kFunctor, ucLockMask,
                bAllowEarlyOut))
            {
                return false;
            }
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < pkMesh->GetSubmeshCount(); ui++)
        {
            NiDataStream::Region kRegion =
                pkStreamRef->GetRegionForSubmesh(ui);
            NiUInt32 uiIndexCount = kRegion.GetRange();

            if (!ForEachPrimitiveCore(pkMesh->GetPrimitiveType(),
                NiDataStreamElement::F_FLOAT32_1, NULL,
                uiIndexCount, (NiUInt16)ui, kFunctor, bAllowEarlyOut))
            {
                return false;
            }
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachPrimitiveOneSubmesh(NiMesh* pkMesh,
    NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor, NiUInt8 ucLockMask,
    bool bAllowEarlyOut)
{
    EE_ASSERT(pkMesh);
    EE_ASSERT(uiSubMesh < pkMesh->GetSubmeshCount());

    NiDataStreamRef* pkStreamRef;
    NiDataStreamElement kElement;

    bool bIndicesExist = false;

    // Make sure that the element actually exists
    if (pkMesh->FindStreamRefAndElementBySemantic(NiCommonSemantics::INDEX(),
        0, NiDataStreamElement::F_UNKNOWN, pkStreamRef, kElement))
    {
        bIndicesExist = true;
    }
    else
    {
        // If the indices don't exist, find the positions
        if (!pkMesh->FindStreamRefAndElementBySemantic(
            NiCommonSemantics::POSITION(), 0,
            NiDataStreamElement::F_UNKNOWN, pkStreamRef, kElement))
        {
            return false;
        }
    }

    if (!pkStreamRef)
        return false;

    if (!kElement.IsValid())
        return false;

    NiDataStream* pkDataStream = pkStreamRef->GetDataStream();

    if (!pkDataStream)
        return false;

    if (bIndicesExist)
    {
        NiUInt32 uiRegion =
            pkStreamRef->GetRegionIndexForSubmesh(uiSubMesh);
        if (!ForEachPrimitiveByRegion(pkMesh->GetPrimitiveType(),
            pkDataStream, uiRegion, uiSubMesh, kFunctor, ucLockMask,
            bAllowEarlyOut))
        {
            return false;
        }
    }
    else
    {
        NiDataStream::Region kRegion =
            pkStreamRef->GetRegionForSubmesh(uiSubMesh);
        NiUInt32 uiIndexCount = kRegion.GetRange();

        if (!ForEachPrimitiveCore(pkMesh->GetPrimitiveType(),
            NiDataStreamElement::F_FLOAT32_1, NULL,
            uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut))
        {
            return false;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachPrimitiveByRegion(
    NiPrimitiveType::Type eType,
    NiDataStream* pkDataStream,
    NiUInt32 uiRegion, NiUInt16 uiSubMesh,
    TPrimitiveFunctor& kFunctor,
    NiUInt8 ucLockMask,
    bool bAllowEarlyOut)
{
    EE_ASSERT(pkDataStream);
    EE_ASSERT(pkDataStream->GetElementDescCount() == 1);

    NiDataStreamElement::Format eFormat =
        pkDataStream->GetElementDescAt(0).GetFormat();

    NiDataStream::Region kRegion = pkDataStream->GetRegion(uiRegion);
    void* pData = pkDataStream->LockRegion(uiRegion, ucLockMask);
    NiUInt32 uiIndexCount = kRegion.GetRange();

    if (!pData)
        return false;

    if (uiIndexCount == 0)
    {
        pkDataStream->Unlock(ucLockMask);
        return false;
    }

    bool bReturn = ForEachPrimitiveCore(eType, eFormat,
        pData, uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);

    pkDataStream->Unlock(ucLockMask);

    return bReturn;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachPrimitiveCore(
    NiPrimitiveType::Type eType, NiDataStreamElement::Format eFormat,
    void* pData, NiUInt32 uiIndexCount, NiUInt16 uiSubMesh,
    TPrimitiveFunctor& kFunctor, bool bAllowEarlyOut)
{
    bool bIndexed = pData != NULL;
    switch (eType)
    {
        case NiPrimitiveType::PRIMITIVE_TRIANGLES:
            if (!bIndexed)
            {
                return ForEachUnindexedTriangle(uiIndexCount, uiSubMesh,
                    kFunctor, bAllowEarlyOut);
            }

            switch (eFormat)
            {
                case NiDataStreamElement::F_UINT16_1:
                    return ForEachIndexedTriangle((NiUInt16*) pData,
                        uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                    break;
                case NiDataStreamElement::F_UINT32_1:
                    return ForEachIndexedTriangle((NiUInt32*) pData,
                        uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                    break;
                default:
                    EE_FAIL("Unsupported NiDataStreamElement::Format!");
                    return false;
            }
            break;
        case NiPrimitiveType::PRIMITIVE_TRISTRIPS:
            if (!bIndexed)
            {
                return ForEachUnindexedTriStrip(uiIndexCount, uiSubMesh,
                    kFunctor, bAllowEarlyOut);
            }

            switch (eFormat)
            {
                case NiDataStreamElement::F_UINT16_1:
                    return ForEachIndexedTriStrip((NiUInt16*) pData,
                        uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                    break;
                case NiDataStreamElement::F_UINT32_1:
                    return ForEachIndexedTriStrip((NiUInt32*) pData,
                        uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                    break;
                default:
                    EE_FAIL("Unsupported NiDataStreamElement::Format!");
                    return false;
            }
            break;
        case NiPrimitiveType::PRIMITIVE_POINTS:
            if (!bIndexed)
            {
                return ForEachUnindexedPoint(uiIndexCount, uiSubMesh,
                    kFunctor, bAllowEarlyOut);
            }

            switch (eFormat)
            {
            case NiDataStreamElement::F_UINT16_1:
                return ForEachIndexedPoint((NiUInt16*) pData,
                    uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                break;
            case NiDataStreamElement::F_UINT32_1:
                return ForEachIndexedPoint((NiUInt32*) pData,
                    uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                break;
            default:
                EE_FAIL("Unsupported NiDataStreamElement::Format!");
                return false;
            }
            break;
        case NiPrimitiveType::PRIMITIVE_LINES:
            if (!bIndexed)
            {
                return ForEachUnindexedLine(uiIndexCount, uiSubMesh,
                    kFunctor, bAllowEarlyOut);
            }

            switch (eFormat)
            {
            case NiDataStreamElement::F_UINT16_1:
                return ForEachIndexedLine((NiUInt16*) pData,
                    uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                break;
            case NiDataStreamElement::F_UINT32_1:
                return ForEachIndexedLine((NiUInt32*) pData,
                    uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                break;
            default:
                EE_FAIL("Unsupported NiDataStreamElement::Format!");
                return false;
            }
            break;

        case NiPrimitiveType::PRIMITIVE_LINESTRIPS:
            if (!bIndexed)
            {
                return ForEachUnindexedLineStrip(uiIndexCount, uiSubMesh,
                    kFunctor, bAllowEarlyOut);
            }

            switch (eFormat)
            {
            case NiDataStreamElement::F_UINT16_1:
                return ForEachIndexedLineStrip((NiUInt16*) pData,
                    uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                break;
            case NiDataStreamElement::F_UINT32_1:
                return ForEachIndexedLineStrip((NiUInt32*) pData,
                    uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                break;
            default:
                EE_FAIL("Unsupported NiDataStreamElement::Format!");
                return false;
            }
            break;

        case NiPrimitiveType::PRIMITIVE_QUADS:
            if (!bIndexed)
            {
                return ForEachUnindexedQuad(uiIndexCount, uiSubMesh,
                    kFunctor, bAllowEarlyOut);
            }

            switch (eFormat)
            {
            case NiDataStreamElement::F_UINT16_1:
                return ForEachIndexedQuad((NiUInt16*) pData,
                    uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                break;
            case NiDataStreamElement::F_UINT32_1:
                return ForEachIndexedQuad((NiUInt32*) pData,
                    uiIndexCount, uiSubMesh, kFunctor, bAllowEarlyOut);
                break;
            default:
                EE_FAIL("Unsupported NiDataStreamElement::Format!");
                return false;
            }
            break;

        default:
            EE_FAIL("Unknown Primitive Type!");
            return false;
    }
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedTriangle(NiUInt32* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiTriangle = 0;
    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            if (!kFunctor(&pIndices[ui], 3, uiTriangle, uiSubMesh))
                return false;

            ui += 3;
            uiTriangle++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            kFunctor(&pIndices[ui], 3, uiTriangle, uiSubMesh);
            ui += 3;
            uiTriangle++;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedTriangle(NiUInt16* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiTriangle = 0;
    NiUInt32 auiIndices[3];
    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            auiIndices[0] = pIndices[ui];
            auiIndices[1] = pIndices[ui + 1];
            auiIndices[2] = pIndices[ui + 2];
            if (!kFunctor(auiIndices, 3, uiTriangle, uiSubMesh))
                return false;
            ui += 3;
            uiTriangle++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            auiIndices[0] = pIndices[ui];
            auiIndices[1] = pIndices[ui + 1];
            auiIndices[2] = pIndices[ui + 2];
            kFunctor(auiIndices, 3, uiTriangle, uiSubMesh);
            ui += 3;
            uiTriangle++;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachUnindexedTriangle(NiUInt32 uiIndexCount,
    NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor, bool bAllowEarlyOut)
{
    NiUInt32 uiTriangle = 0;
    NiUInt32 auiIndices[3];

    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            auiIndices[0] = ui;
            auiIndices[1] = ui + 1;
            auiIndices[2] = ui + 2;
            if (!kFunctor(auiIndices, 3, uiTriangle, uiSubMesh))
                return false;
            ui += 3;
            uiTriangle++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            auiIndices[0] = ui;
            auiIndices[1] = ui + 1;
            auiIndices[2] = ui + 2;
            kFunctor(auiIndices, 3, uiTriangle, uiSubMesh);
            ui += 3;
            uiTriangle++;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedTriStrip(NiUInt32* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiTriangle = 0;
    NiUInt32 auiIndices[3];
    bool bOdd = false;
    NiUInt32 auiOffsets[2][2];
    auiOffsets[0][0] = 0;
    auiOffsets[0][1] = 1;
    auiOffsets[1][0] = 1;
    auiOffsets[1][1] = 0;

    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            auiIndices[0] = pIndices[ui + auiOffsets[bOdd][0]];
            auiIndices[1] = pIndices[ui + auiOffsets[bOdd][1]];
            auiIndices[2] = pIndices[ui + 2];
            if (!kFunctor(auiIndices, 3, uiTriangle, uiSubMesh))
                return false;
            bOdd = !bOdd;
            ui+=1;
            uiTriangle++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            auiIndices[0] = pIndices[ui + auiOffsets[bOdd][0]];
            auiIndices[1] = pIndices[ui + auiOffsets[bOdd][1]];
            auiIndices[2] = pIndices[ui + 2];
            kFunctor(auiIndices, 3, uiTriangle, uiSubMesh);
            bOdd = !bOdd;
            ui+=1;
            uiTriangle++;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedTriStrip(NiUInt16* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiTriangle = 0;
    NiUInt32 auiIndices[3];
    bool bOdd = false;
    NiUInt32 auiOffsets[2][2];
    auiOffsets[0][0] = 0;
    auiOffsets[0][1] = 1;
    auiOffsets[1][0] = 1;
    auiOffsets[1][1] = 0;

    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            auiIndices[0] = pIndices[ui + auiOffsets[bOdd][0]];
            auiIndices[1] = pIndices[ui + auiOffsets[bOdd][1]];
            auiIndices[2] = pIndices[ui + 2];
            if (!kFunctor(auiIndices, 3, uiTriangle, uiSubMesh))
                return false;
            bOdd = !bOdd;
            ui += 1;
            uiTriangle++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            auiIndices[0] = pIndices[ui + auiOffsets[bOdd][0]];
            auiIndices[1] = pIndices[ui + auiOffsets[bOdd][1]];
            auiIndices[2] = pIndices[ui + 2];
            kFunctor(auiIndices, 3, uiTriangle, uiSubMesh);
            bOdd = !bOdd;
            ui += 1;
            uiTriangle++;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachUnindexedTriStrip(NiUInt32 uiIndexCount,
    NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor, bool bAllowEarlyOut)
{
    NiUInt32 uiTriangle = 0;
    NiUInt32 auiIndices[3];
    bool bOdd = false;
    NiUInt32 auiOffsets[2][2];
    auiOffsets[0][0] = 0;
    auiOffsets[0][1] = 1;
    auiOffsets[1][0] = 1;
    auiOffsets[1][1] = 0;

    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            auiIndices[0] = ui + auiOffsets[bOdd][0];
            auiIndices[1] = ui + auiOffsets[bOdd][1];
            auiIndices[2] = ui + 2;
            if (!kFunctor(auiIndices, 3, uiTriangle, uiSubMesh))
                return false;
            bOdd = !bOdd;
            ui += 1;
            uiTriangle++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 2;)
        {
            auiIndices[0] = ui + auiOffsets[bOdd][0];
            auiIndices[1] = ui + auiOffsets[bOdd][1];
            auiIndices[2] = ui + 2;
            kFunctor(auiIndices, 3, uiTriangle, uiSubMesh);
            bOdd = !bOdd;
            ui += 1;
            uiTriangle++;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachUnindexedPoint(NiUInt32 uiIndexCount,
    NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor, bool bAllowEarlyOut)
{
    NiUInt32 uiPoint = 0;
    NiUInt32 auiIndices[1];

    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount;)
        {
            auiIndices[0] = ui;
            if (!kFunctor(auiIndices, 1, uiPoint, uiSubMesh))
                return false;
            ui ++;
            uiPoint++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount;)
        {
            auiIndices[0] = ui;
            kFunctor(auiIndices, 1, uiPoint, uiSubMesh);
            ui ++;
            uiPoint++;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedPoint(NiUInt32* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiPoint = 0;
    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount;)
        {
            if (!kFunctor(&pIndices[ui], 1, uiPoint, uiSubMesh))
                return false;

            ui ++;
            uiPoint++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount;)
        {
            kFunctor(&pIndices[ui], 1, uiPoint, uiSubMesh);
            ui ++;
            uiPoint++;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedPoint(NiUInt16* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiPoint = 0;
    NiUInt32 auiIndices[1];
    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount;)
        {
            auiIndices[0] = pIndices[ui];
            if (!kFunctor(auiIndices, 1, uiPoint, uiSubMesh))
                return false;
            ui ++;
            uiPoint++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount;)
        {
            auiIndices[0] = pIndices[ui];
            kFunctor(auiIndices, 1, uiPoint, uiSubMesh);
            ui ++;
            uiPoint++;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedLine(NiUInt32* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiLine = 0;
    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            if (!kFunctor(&pIndices[ui], 2, uiLine, uiSubMesh))
                return false;

            ui += 2;
            uiLine++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            kFunctor(&pIndices[ui], 2, uiLine, uiSubMesh);
            ui += 2;
            uiLine++;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedLine(NiUInt16* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiLine = 0;
    NiUInt32 auiIndices[2];
    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            auiIndices[0] = pIndices[ui];
            auiIndices[1] = pIndices[ui + 1];
            if (!kFunctor(auiIndices, 2, uiLine, uiSubMesh))
                return false;
            ui += 2;
            uiLine++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            auiIndices[0] = pIndices[ui];
            auiIndices[1] = pIndices[ui + 1];
            kFunctor(auiIndices, 2, uiLine, uiSubMesh);
            ui += 2;
            uiLine++;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachUnindexedLine(NiUInt32 uiIndexCount,
    NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor, bool bAllowEarlyOut)
{
    NiUInt32 uiLine = 0;
    NiUInt32 auiIndices[2];

    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            auiIndices[0] = ui;
            auiIndices[1] = ui + 1;
            if (!kFunctor(auiIndices, 2, uiLine, uiSubMesh))
                return false;
            ui += 2;
            uiLine++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            auiIndices[0] = ui;
            auiIndices[1] = ui + 1;
            kFunctor(auiIndices, 2, uiLine, uiSubMesh);
            ui += 2;
            uiLine++;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedLineStrip(NiUInt32* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiLine = 0;
    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            if (!kFunctor(&pIndices[ui], 2, uiLine, uiSubMesh))
                return false;

            ui ++;
            uiLine++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            kFunctor(&pIndices[ui], 2, uiLine, uiSubMesh);
            ui ++;
            uiLine++;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedLineStrip(NiUInt16* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiLine = 0;
    NiUInt32 auiIndices[2];
    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            auiIndices[0] = pIndices[ui];
            auiIndices[1] = pIndices[ui + 1];
            if (!kFunctor(auiIndices, 2, uiLine, uiSubMesh))
                return false;
            ui ++;
            uiLine++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            auiIndices[0] = pIndices[ui];
            auiIndices[1] = pIndices[ui + 1];
            kFunctor(auiIndices, 2, uiLine, uiSubMesh);
            ui ++;
            uiLine++;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachUnindexedLineStrip(NiUInt32 uiIndexCount,
    NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor, bool bAllowEarlyOut)
{
    NiUInt32 uiLine = 0;
    NiUInt32 auiIndices[2];

    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            auiIndices[0] = ui;
            auiIndices[1] = ui + 1;
            if (!kFunctor(auiIndices, 2, uiLine, uiSubMesh))
                return false;
            ui ++;
            uiLine++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 1;)
        {
            auiIndices[0] = ui;
            auiIndices[1] = ui + 1;
            kFunctor(auiIndices, 2, uiLine, uiSubMesh);
            ui ++;
            uiLine++;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedQuad(NiUInt32* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiQuad = 0;
    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 3;)
        {
            if (!kFunctor(&pIndices[ui], 4, uiQuad, uiSubMesh))
                return false;

            ui += 4;
            uiQuad++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 3;)
        {
            kFunctor(&pIndices[ui], 4, uiQuad, uiSubMesh);
            ui += 4;
            uiQuad++;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachIndexedQuad(NiUInt16* pIndices,
    NiUInt32 uiIndexCount, NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor,
    bool bAllowEarlyOut)
{
    NiUInt32 uiQuad = 0;
    NiUInt32 auiIndices[4];
    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 3;)
        {
            auiIndices[0] = pIndices[ui];
            auiIndices[1] = pIndices[ui + 1];
            auiIndices[2] = pIndices[ui + 2];
            auiIndices[3] = pIndices[ui + 3];
            if (!kFunctor(auiIndices, 4, uiQuad, uiSubMesh))
                return false;
            ui += 4;
            uiQuad++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 3;)
        {
            auiIndices[0] = pIndices[ui];
            auiIndices[1] = pIndices[ui + 1];
            auiIndices[2] = pIndices[ui + 2];
            auiIndices[3] = pIndices[ui + 3];
            kFunctor(auiIndices, 4, uiQuad, uiSubMesh);
            ui += 4;
            uiQuad++;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename TPrimitiveFunctor>
inline bool NiMeshAlgorithms::ForEachUnindexedQuad(NiUInt32 uiIndexCount,
    NiUInt16 uiSubMesh, TPrimitiveFunctor& kFunctor, bool bAllowEarlyOut)
{
    NiUInt32 uiQuad = 0;
    NiUInt32 auiIndices[4];

    if (bAllowEarlyOut)
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 3;)
        {
            auiIndices[0] = ui;
            auiIndices[1] = ui + 1;
            auiIndices[2] = ui + 2;
            auiIndices[3] = ui + 3;
            if (!kFunctor(auiIndices, 4, uiQuad, uiSubMesh))
                return false;
            ui += 4;
            uiQuad++;
        }
    }
    else
    {
        for (NiUInt32 ui = 0; ui < uiIndexCount - 3;)
        {
            auiIndices[0] = ui;
            auiIndices[1] = ui + 1;
            auiIndices[2] = ui + 2;
            auiIndices[3] = ui + 3;
            kFunctor(auiIndices, 4, uiQuad, uiSubMesh);
            ui += 4;
            uiQuad++;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------