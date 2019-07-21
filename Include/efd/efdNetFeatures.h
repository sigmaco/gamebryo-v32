//
// This is a generated file.  You should not alter this file manually.

//Source enum: efdNetFeatures.enum

#pragma once
#ifndef EE_efdNetFeatures_h_INCLUDED
#define EE_efdNetFeatures_h_INCLUDED

#include <efd/UniversalTypes.h>

namespace efd
{

    typedef efd::UInt32 NetFeatures;
    static const NetFeatures NET_INVALID        =          0u; // 0x00000000

    static const NetFeatures NET_UDP            =          1u; // 0x00000001
    static const NetFeatures NET_TCP            =          2u; // 0x00000002
    static const NetFeatures NET_RELIABLE       =          4u; // 0x00000004
    static const NetFeatures NET_AES            =          8u; // 0x00000008
    static const NetFeatures NET_SSL            =         16u; // 0x00000010
    static const NetFeatures NET_COMPRESSED     =         32u; // 0x00000020
    static const NetFeatures NET_CONNECTIONLESS =         64u; // 0x00000040
    static const NetFeatures NET_LOCAL          =        128u; // 0x00000080
    static const NetFeatures NET_DEFAULT        =        256u; // 0x00000100
    static const NetFeatures NET_UNORDERED      =        512u; // 0x00000200
    static const NetFeatures NET_ENCRYPTED      =       1024u; // 0x00000400
    static const NetFeatures NET_VOICE          =       2048u; // 0x00000800
    static const NetFeatures NET_ENET           =       4096u; // 0x00001000
    static const NetFeatures NET_TOOL           =       8192u; // 0x00002000
    static const NetFeatures NET_TOTAL_ORDER    =      16384u; // 0x00004000
    static const NetFeatures NET_CONSOLE        =      32768u; // 0x00008000
    static const NetFeatures NET_VIRTUAL        = 2147483648u; // 0x80000000

} // end namespace efd

#endif // EE_efdNetFeatures_h_INCLUDED
