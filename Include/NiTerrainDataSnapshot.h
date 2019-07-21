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
#ifndef NITERRAINDATASNAPSHOT_H
#define NITERRAINDATASNAPSHOT_H

#include <NiRefObject.h>
#include "NiTerrainLibType.h"
#include "NiTerrainSector.h"

/**
    A class used to hold a snapshot of the terrain's data over a number of cells. This is used
    to preserve a terrain's state and allow the state to be restored at a later point in time. 
*/
class NITERRAIN_ENTRY NiTerrainDataSnapshot: public NiMemObject
{
public:
    /// Expose the standard SectorID type to this class
    typedef NiTerrainSector::SectorID SectorID;
    /// Expose the standard CellID type to this class
    typedef NiTerrainSector::CellID CellID;

    /**
        An enumeration to represent the different types of buffer that can be snapshotted.
    */
    struct BufferType
    {
        enum Value
        {
            /// A heightmap buffer snapshot
            HEIGHTMAP,
            /// A surface mask buffer snapshot
            SURFACE_MASK,

            /// The total number of types of snapshots
            NUM_BUFFER_TYPES
        };
    };

    /**
        A class to store the snapshot data relevant to an individual cell of the terrain.
    */
    class NITERRAIN_ENTRY CellSnapshot: public NiMemObject
    {
    public:
        /// Helper typedef to use to manage a map of surface masks
        typedef efd::map< efd::UInt32, NiPointer<SurfaceMaskBuffer> > SurfaceMaskMap;

        /// Constructor
        CellSnapshot();
        /// Destructor
        ~CellSnapshot();

        /**
            Mark the cell snapshot as containing data of a particular type. NOTE: Even if the
            snapshot doesn't contain data for this type, that counts as identifying that 
            the cell does not have any data when the snapshot was taken. 

            @param eBufferType The type of buffer that has been snapshotted. 
        */
        void MarkContainsData(efd::UInt32 eBufferType);

        /**
            Query the cell snapshot as to whether the snapshot contains data of a particular type. 

            @param eBufferType The type of data the caller is looking for. 
            @return True, if relevant data of the specified type exists. 
        */
        bool ContainsData(efd::UInt32 eBufferType) const;

        /**
            Append a heightmap buffer to the snapshot of the cell. 
            NOTE: This does not mark the snapshot as containing this data. 
            The snapshot will take ownership of the data passed to it. 

            @param pkHeightmap The heightmap data to store in the snapshot. 
        */
        void AppendData(HeightMapBuffer* pkHeightmap);

        /**
            Append a surface mask buffer to the snapshot of the cell for a particular surface. 
            NOTE: This does not mark the snapshot as containing this data. 
            The snapshot will take ownership of the data passed to it. 

            @param uiSurfaceIndex The surface index of the surface to store data for
            @param pkMask The surface mask data for the surface
        */
        void AppendData(efd::UInt32 uiSurfaceIndex, SurfaceMaskBuffer* pkMask);

        /// Get the heightmap data stored in the snapshot. 
        HeightMapBuffer* GetHeightmap() const;
        /// Get the map of surface masks stored in the snapshot. 
        inline const SurfaceMaskMap& GetSurfaceMasks() const;

        /**
            Get the surface mask stored for a specific surface on this cell. 

            @param uiSurfaceIndex The surface index of the surface to query the data for
        */
        SurfaceMaskBuffer* GetSurfaceMask(efd::UInt32 uiSurfaceIndex) const;

    private:
        /// A smart pointer to the heightmap buffer stored. 
        NiPointer<HeightMapBuffer> m_pkHeightmap;
        /// A map of surface masks stored in the snapshot. 
        SurfaceMaskMap m_kSurfaceMasks;
        /// A bitfield indicating what data types are currently stored in the snapshot.
        efd::UInt32 m_uiStoredData;
    };

    /// Helper typedef to define a mapping of cellID's to CellSnapshots
    typedef efd::map<CellID, CellSnapshot*> CellMap;
    /// Helper typedef to define the list of cells in a specific order.
    typedef efd::vector<CellID> CellStack;

    /// Constructor
    NiTerrainDataSnapshot();
    /// Destructor
    ~NiTerrainDataSnapshot();

    /**
        Get the cell snapshot for a particular cell.

        @param kCellID the cellID of the cell data to retrieve. 
        @return A CellSnapshot object storing the data for that particular cell (or NULL).
    */
    CellSnapshot* GetCellSnapshot(CellID kCellID);
    /// A const version of the previous function
    const CellSnapshot* GetCellSnapshot(CellID kCellID) const;

    /**
        Check if this snapshot stores a particular type of data for a given cell

        @param kCellID The cell to query the data of
        @param eBufferType The type of data the caller is interested in
        @return True if data is stored for that buffer type on that cell
    */
    bool ContainsData(CellID kCellID, BufferType::Value eBufferType) const;

    /**
        Append heightmap data to the snapshot for a particular cell.

        @param kCellID The cell to add data for
        @param pkHeightmap The heightmap data for that cell
    */
    void AppendData(CellID kCellID, HeightMapBuffer* pkHeightmap);

    /**
        Append surface mask data to the snapshot for a particular cell.

        @param kCellID The cell to add data for
        @param uiSurfaceIndex The surface the mask data represents
        @param pkMask The surface mask data for that cell
    */
    void AppendData(CellID kCellID, efd::UInt32 uiSurfaceIndex, SurfaceMaskBuffer* pkMask);

    /**
        Fetch the heightmap data from the snapshot of a given cell

        @param kCellID The cell to query the data of
        @param pkHeightmap The heightmap buffer pointer to store the data pointer in
        @return True if data is successfully queried from the snapshot
    */
    bool FetchData(CellID kCellID, HeightMapBuffer*& pkHeightmap) const;
    
    /**
        Fetch the surface mask data from the snapshot of a given cell for a particular surface

        @param kCellID The cell to query the data of
        @param uiSurfaceIndex The surface the caller is interested in
        @param pkMask The surface mask buffer pointer to store the data pointer in
        @return True if data is successfully queried from the snapshot
    */
    bool FetchData(CellID kCellID, efd::UInt32 uiSurfaceIndex, SurfaceMaskBuffer*& pkMask) const;
    
    /**
        Fetch the heightmap data from the snapshot of a given cell

        @param kCellID The cell to query the data of
        @param pkMasks The surface mask map pointer to store the data pointer in
        @return True if data is successfully queried from the snapshot
    */
    bool FetchSurfaceMasks(CellID kCellID, const CellSnapshot::SurfaceMaskMap*& pkMasks) const;
    
    /// Get the map of all cell snapshots stored
    const CellMap& GetCellSnapshots() const;
    
    /**
        Get the list of cells with data stored in this snapshot (in the order that the cells were 
        added.
    */
    const CellStack& GetCellStack() const;

private:
    /// The mapping of CellID's to CellSnapshots
    CellMap m_kCells;
    /// The list of cells in the order that they were added to the snapshot
    CellStack m_kCellStack;
};

#include "NiTerrainDataSnapshot.inl"

#endif // NITERRAINDATASNAPSHOT_H
