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

//--------------------------------------------------------------------------------------------------
inline void _EE_Swap(char* pcA, char* pcB)
{
    EE_ASSERT(pcA != pcB);
    char acValue = pcA[0];
    pcA[0] = pcB[0];
    pcB[0] = acValue;
}

//--------------------------------------------------------------------------------------------------
inline void Endian::Swap16(char* pcValue, unsigned int uiCount)
{
    for (unsigned int ui = 0; ui < uiCount; ui++)
    {
        _EE_Swap(&pcValue[0], &pcValue[1]);
        pcValue += 2;
    }
}

//--------------------------------------------------------------------------------------------------
inline void Endian::Swap32(char* pcValue, unsigned int uiCount)
{
    for (unsigned int ui = 0; ui < uiCount; ui++)
    {
        _EE_Swap(&pcValue[0], &pcValue[3]);
        _EE_Swap(&pcValue[1], &pcValue[2]);
        pcValue += 4;
    }
}

//--------------------------------------------------------------------------------------------------
inline void Endian::Swap64(char* pcValue, unsigned int uiCount)
{
    for (unsigned int ui = 0; ui < uiCount; ui++)
    {
        _EE_Swap(&pcValue[0], &pcValue[7]);
        _EE_Swap(&pcValue[1], &pcValue[6]);
        _EE_Swap(&pcValue[2], &pcValue[5]);
        _EE_Swap(&pcValue[3], &pcValue[4]);
        pcValue += 8;
    }
}

//--------------------------------------------------------------------------------------------------

} // end namespace efd
