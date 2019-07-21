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

namespace ecr
{

//------------------------------------------------------------------------------------------------
    inline void D3D11Direct3DResource::SetWidth(efd::UInt32 width)
{
    m_width = width;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Direct3DResource::SetHeight(efd::UInt32 height)
{
    m_height = height;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Direct3DResource::SetDepth(efd::UInt32 depth)
{
    m_depth = depth;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Direct3DResource::SetArrayCount(efd::UInt32 arrayCount)
{
    m_arrayCount = arrayCount;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
