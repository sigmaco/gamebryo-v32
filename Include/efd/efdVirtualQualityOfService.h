//
// This is a generated file.  You should not alter this file manually.

//Source enum: efdVirtualQualityOfService.enum

#pragma once
#ifndef EE_efdVirtualQualityOfService_h_INCLUDED
#define EE_efdVirtualQualityOfService_h_INCLUDED

#include <efd/UniversalTypes.h>

namespace efd
{

    static const QualityOfService QOS_INVALID                 =          0u; // 0x00000000

    static const QualityOfService QOS_DEFAULT                 = 2147483649u; // 0x80000001
    static const QualityOfService QOS_SUBSCRIPTION            = 2147483650u; // 0x80000002
    static const QualityOfService QOS_TOOL                    = 2147483651u; // 0x80000003
    static const QualityOfService QOS_TOTAL_ORDER             = 2147483652u; // 0x80000004
    static const QualityOfService QOS_LOCAL                   = 2147483653u; // 0x80000005
    static const QualityOfService QOS_VOICE                   = 2147483654u; // 0x80000006
    static const QualityOfService QOS_RELIABLE                = 2147483655u; // 0x80000007
    static const QualityOfService QOS_RELIABLE_AES            = 2147483656u; // 0x80000008
    static const QualityOfService QOS_RELIABLE_COMPRESSED     = 2147483657u; // 0x80000009
    static const QualityOfService QOS_RELIABLE_COMPRESSED_AES = 2147483658u; // 0x8000000A
    static const QualityOfService QOS_UNRELIABLE              = 2147483659u; // 0x8000000B
    static const QualityOfService QOS_UNRELIABLE_ORDERED      = 2147483660u; // 0x8000000C
    static const QualityOfService QOS_CONNECTIONLESS          = 2147483661u; // 0x8000000D
    static const QualityOfService QOS_TCP                     = 2147483662u; // 0x8000000E
    static const QualityOfService QOS_TCP_AES                 = 2147483663u; // 0x8000000F
    static const QualityOfService QOS_TCP_COMPRESSED          = 2147483664u; // 0x80000010
    static const QualityOfService QOS_TCP_COMPRESSED_AES      = 2147483665u; // 0x80000011
    static const QualityOfService QOS_TCP_SSL                 = 2147483666u; // 0x80000012

} // end namespace efd

#endif // EE_efdVirtualQualityOfService_h_INCLUDED
