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
inline egmToolServices::TerrainPaintingGuide::InternalLeafID::InternalLeafID() :
    m_internalID(""),
    m_sectorIndex(0,0),
    m_leafID(0)
{

}

//--------------------------------------------------------------------------------------------------
inline egmToolServices::TerrainPaintingGuide::InternalLeafID::InternalLeafID(efd::utf8string iD)
{
    efd::vector<efd::utf8string> splittedID;
    if (iD.split(":", splittedID) == 2)
    {
        efd::Point2 index;
        efd::UInt32 leaf;
        if (efd::ParseHelper<efd::Point2>::FromString(splittedID[0], index) &&
            efd::ParseHelper<efd::UInt32>::FromString(splittedID[1], leaf))
        {
            m_internalID = iD;
            m_sectorIndex = NiPoint2(index.x, index.y);
            m_leafID = leaf;
        }

    }
}

//--------------------------------------------------------------------------------------------------
inline egmToolServices::TerrainPaintingGuide::InternalLeafID::InternalLeafID(
    efd::Point2 sector, 
    efd::UInt32 leaf)
{
    m_sectorIndex = sector;
    m_leafID = leaf;
    m_internalID.sprintf("%d,%d:%d",(efd::UInt32)sector.x, (efd::UInt32)sector.y, leaf);
}

//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::TerrainPaintingGuide::InternalLeafID::operator == (
    const InternalLeafID& id) const
{
    return m_internalID == id.m_internalID;
}

//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::TerrainPaintingGuide::InternalLeafID::operator != (
    const InternalLeafID& id) const
{
    return m_internalID != id.m_internalID;
}

//--------------------------------------------------------------------------------------------------
inline egmToolServices::TerrainPaintingGuide::InternalLeafID& 
    egmToolServices::TerrainPaintingGuide::InternalLeafID::operator = (const InternalLeafID& id)
{
    m_internalID = id.m_internalID;
    m_sectorIndex = id.m_sectorIndex;
    m_leafID = id.m_leafID;

    return *this;
}

//--------------------------------------------------------------------------------------------------