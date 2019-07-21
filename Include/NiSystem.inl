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
// Use 128 bit aligned arrays with size multiples of 4 floats on SSE
// capable PCs. Use on __declspec(align(16)) float or DWORD arrays
inline void NiMemcpyFloatArraySSE(float* pDst, const float* pSrc, int SizeInFloats)
{
    int iCount = SizeInFloats >> 2;

    __asm {
        mov     ecx,    iCount
        mov     edi,    pDst
        mov     esi,    pSrc

    loop1:
        movaps  xmm0,   [esi]
        movaps  [edi],  xmm0

        add     esi,    16
        add     edi,    16

        dec     ecx
        jnz     loop1
    }
}

//--------------------------------------------------------------------------------------------------
// Use 32 bit aligned arrays with size multiples of 4 bytes.
// Use on __declspec(align(4)) float or DWORD arrays
inline void NiMemcpyFloatArray(float* pDst, const float* pSrc, int SizeInFloats)
{
    int iBytes = sizeof(float) * SizeInFloats;

    __asm {
        mov     ecx,    iBytes
        shr     ecx,    2

        cld                         // clear direction flag
        mov     esi,    pSrc
        mov     edi,    pDst
        rep     movsd               // copy dword at a time
    }
}

//--------------------------------------------------------------------------------------------------
inline int NiMemcpyBytes(long* pDst,const long* pSrc, unsigned long SizeInBytes)
{
    _asm
    {
        pusha;

        mov  ebx,SizeInBytes;
        mov  edi,pDst;
        mov  esi,pSrc;

looping:
        // read to register
        mov ecx, [esi];
        // write from register
        mov [edi], ecx;

        add esi, 1;
        add edi, 1;
        dec ebx;

        jnz  looping;

        popa;
    }
    return 0;
}

//--------------------------------------------------------------------------------------------------
