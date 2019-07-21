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

//--------------------------------------------------------------------------------------------------
inline NSBConstantMap::NSBCM_Entry::NSBCM_Entry() :
    NiShaderConstantMapEntry()
{
    /* */
}

//------------------------------------------------------------------------------------------------
inline const char* NSBConstantMap::GetName() const
{
    return m_pcName;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBConstantMap::GetProgramType()
{
    return m_uiProgramType;
}

//--------------------------------------------------------------------------------------------------
inline void NSBConstantMap::SetProgramType(unsigned int uiProgramType)
{
    m_uiProgramType = uiProgramType;
}

//--------------------------------------------------------------------------------------------------
