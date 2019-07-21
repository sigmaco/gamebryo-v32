// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

//---------------------------------------------------------------------------
inline NiUInt8 NiTerrainCellLeaf::DoGetPixelAt(NiPixelData* pkPixelData, 
    NiIndex kCoordinates, NiUInt32 uiComponent) const
{
    EE_ASSERT(pkPixelData);
    NiUInt32 uiStride = pkPixelData->GetPixelStride();
    NiUInt32 uiWidth = pkPixelData->GetWidth();

    EE_ASSERT(kCoordinates.x < pkPixelData->GetWidth());
    EE_ASSERT(kCoordinates.y < pkPixelData->GetHeight());
    EE_ASSERT(uiComponent < pkPixelData->GetPixelFormat().GetNumComponents());

    // Calculate the pixel index
    NiUInt32 uiPixelIndex = NiUInt32(((kCoordinates.y) * uiWidth + kCoordinates.x) * 
        uiStride + uiComponent);

    unsigned char* pucPixels = pkPixelData->GetPixels();

    return pucPixels[uiPixelIndex];
}
//---------------------------------------------------------------------------
