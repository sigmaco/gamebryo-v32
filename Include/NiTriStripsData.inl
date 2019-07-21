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

#ifndef EE_REMOVE_BACK_COMPAT_STREAMING

//--------------------------------------------------------------------------------------------------
inline unsigned short NiTriStripsData::GetStripCount() const
{
    return m_usStrips;
}

//--------------------------------------------------------------------------------------------------
inline unsigned short* NiTriStripsData::GetStripLengths() const
{
    return m_pusStripLengths;
}

//--------------------------------------------------------------------------------------------------
inline unsigned short* NiTriStripsData::GetStripLists() const
{
    return m_pusStripLists;
}

//--------------------------------------------------------------------------------------------------
inline unsigned short NiTriStripsData::GetStripLengthSum() const
{
    return m_usTriangles + 2 * m_usStrips;
}

//--------------------------------------------------------------------------------------------------
inline void NiTriStripsData::GetTriangleIndices_Inline(unsigned short i,
    unsigned short& i0, unsigned short& i1, unsigned short& i2) const
{
    EE_ASSERT(i < m_usTriangles);

    unsigned short usTriangles;
    unsigned short usStrip = 0;

    // const function so we need a local copy.
    unsigned short* pusStripLists = m_pusStripLists;

    while (i >= (usTriangles = m_pusStripLengths[usStrip] - 2))
    {
        i = (unsigned short)(i - usTriangles);
        pusStripLists += m_pusStripLengths[usStrip++];
    }

    if (i & 1)
    {
        i0 = pusStripLists[i + 1];
        i1 = pusStripLists[i];
    }
    else
    {
        i0 = pusStripLists[i];
        i1 = pusStripLists[i + 1];
    }

    i2 = pusStripLists[i + 2];
}

//--------------------------------------------------------------------------------------------------
#endif // #ifndef EE_REMOVE_BACK_COMPAT_STREAMING
