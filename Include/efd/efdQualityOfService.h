//
// This is a generated file.  You should not alter this file manually.

//Source enum: efdQualityOfService.enum

#pragma once
#ifndef EE_efdQualityOfService_h_INCLUDED
#define EE_efdQualityOfService_h_INCLUDED

#include <efd/UniversalTypes.h>

namespace efd
{

    static const QualityOfService kQOS_TCP                      =          6u; // 0x00000006
    static const QualityOfService kQOS_ReliableAES              =         13u; // 0x0000000D
    static const QualityOfService kQOS_TCPAES                   =         14u; // 0x0000000E
    static const QualityOfService kQOS_TCPSSL                   =         22u; // 0x00000016
    static const QualityOfService kQOS_ReliableCompressed       =         37u; // 0x00000025
    static const QualityOfService kQOS_TCPCompressed            =         38u; // 0x00000026
    static const QualityOfService kQOS_ReliableAESCompressed    =         45u; // 0x0000002D
    static const QualityOfService kQOS_TCPAESCompressed         =         46u; // 0x0000002E
    static const QualityOfService kQOS_Local                    =        132u; // 0x00000084
    static const QualityOfService kQOS_Reliable                 =        262u; // 0x00000106
    static const QualityOfService kQOS_Unreliable               =        513u; // 0x00000201
    static const QualityOfService kQOS_UnreliableConnectionless =        577u; // 0x00000241
    static const QualityOfService kQOS_ReliableEncrypted        =       1029u; // 0x00000405
    static const QualityOfService kQOS_TCPEncrypted             =       1030u; // 0x00000406
    static const QualityOfService kQOS_Voice                    =       2561u; // 0x00000A01
    static const QualityOfService kQOS_TCPTool                  =       8198u; // 0x00002006
    static const QualityOfService kQOS_ReliableTotalOrder       =      16389u; // 0x00004005
    static const QualityOfService kQOS_TCPTotalOrder            =      16390u; // 0x00004006

    // Alias values:
    static const QualityOfService kQOS_Invalid                  =          0u; // 0x00000000
    static const QualityOfService kQOS_UnreliableOrdered        =          1u; // 0x00000001

} // end namespace efd

#endif // EE_efdQualityOfService_h_INCLUDED
