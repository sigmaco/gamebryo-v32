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
#ifndef NIDEFORMATIONBUFFER_H
#define NIDEFORMATIONBUFFER_H

#include <NiRefObject.h>
#include "NiTerrainLibType.h"

/**
    A class used to hold a 2D array of values used in the painting of the terrain.
    At present two types of buffer are defined. A heightmap buffer and a surface mask buffer. 
    These objects are designed to be initialized by a NiTerrain object. 

    The buffer manages it's own memory allowing a single buffer object to be reused many times
    with minimal memory allocations.
*/
template<class BufferType> class NiTerrainDeformationBuffer : public NiRefObject
{
public:
    /// The type of data values being stored in the buffer
    typedef BufferType DataType;

    /// Constructor
    NiTerrainDeformationBuffer();
    /// Copy Constructor
    NiTerrainDeformationBuffer(const NiTerrainDeformationBuffer& kTerrainDeformationBuffer);
    /// Destructor
    ~NiTerrainDeformationBuffer();

    /// Fetch a pointer to the beginning of the buffer
    BufferType* GetBuffer() const;
    /// Fetch the length of the buffer in elements
    efd::UInt32 GetLength() const;
    /// Fetch the length of the buffer in bytes
    efd::UInt32 GetSize() const;

    /// Get the range of sectors affected by this deformation buffer (inclusive)
    const NiRect<efd::SInt32>& GetAffectedSectorRange() const;
    /// Get the range of the data set that is affected by this deformation buffer (inclusive).
    /// Coordinates are defined according to the sector range. 
    const NiRect<efd::SInt32>& GetDataRegion() const;
    /// Get the width of the buffer in elements
    efd::UInt32 GetWidth() const;
    /// Get the height of the buffer in elements
    efd::UInt32 GetHeight() const;
    /// Get a specific entry from the buffer
    BufferType& SamplePoint(efd::UInt32 uiX, efd::UInt32 uiY);
    /// Get the terrain space region that the buffer operates over
    const NiRect<efd::Float32>& GetTerrainSpaceRegion() const;
    
    /// Set the region over which the deformation buffer is relevant. A call to this function
    /// may cause the buffer to be reallocated to accommodate the size of the region. The buffer
    /// is also initialized to zeros
    bool SetDeformationRegion(NiRect<efd::SInt32> kAffectedSectorRange, 
        NiRect<efd::SInt32> kDataRegion, NiRect<efd::Float32> kTerrainSpaceRegion, 
        efd::UInt32 uiWidth, efd::UInt32 uiHeight);

private:
    /// The buffer
    BufferType* m_pkBuffer;
    /// The length of the buffer
    efd::UInt32 m_uiAllocatedSize;
    /// The affected sector range
    NiRect<efd::SInt32> m_kAffectedSectorRange;
    /// The affected data region
    NiRect<efd::SInt32> m_kDataRegion;
    /// The terrainspace region
    NiRect<efd::Float32> m_kTerrainSpaceRegion;
    /// The width of the buffer
    efd::UInt32 m_uiWidth;
    /// The height of the buffer
    efd::UInt32 m_uiHeight;
};
typedef NiTerrainDeformationBuffer<efd::UInt8> SurfaceMaskBuffer;
typedef NiTerrainDeformationBuffer<efd::UInt16> HeightMapBuffer;

#include "NiTerrainDeformationBuffer.inl"

#endif // NIDEFORMATIONBUFFER_H
