//
// This is a generated file.  You should not alter this file manually.

//Source enum: efdClassIDs.enum

#pragma once
#ifndef EE_efdClassIDs_h_INCLUDED
#define EE_efdClassIDs_h_INCLUDED

#include <efd/UniversalTypes.h>
#include <efd/ClassInfo.h>

namespace efd
{

    static const ClassID kCLASSID_MsgClassIDAndCatLogMask           = 3758096384u; // 0xE0000000
    static const ClassID kCLASSID_XMLMemLogHandler                  = 3758096385u; // 0xE0000001
    static const ClassID kCLASSID_FileDestination                   = 3758096386u; // 0xE0000002
    static const ClassID kCLASSID_NetDestination                    = 3758096387u; // 0xE0000003
    static const ClassID kCLASSID_PrintDestination                  = 3758096388u; // 0xE0000004
    static const ClassID kCLASSID_SystemLogger                      = 3758096389u; // 0xE0000005
    static const ClassID kCLASSID_ConfigSource                      = 3758096390u; // 0xE0000006
    static const ClassID kCLASSID_CommandLineSource                 = 3758096391u; // 0xE0000007
    static const ClassID kCLASSID_IniSource                         = 3758096392u; // 0xE0000008
    static const ClassID kCLASSID_EnvVarSource                      = 3758096393u; // 0xE0000009
    static const ClassID kCLASSID_IConfigSource                     = 3758096394u; // 0xE000000A
    static const ClassID kCLASSID_IMessage                          = 3758096395u; // 0xE000000B
    static const ClassID kCLASSID_IStreamable                       = 3758096396u; // 0xE000000C
    static const ClassID kCLASSID_INetListener                      = 3758096397u; // 0xE000000D
    static const ClassID kCLASSID_EnvelopeMessage                   = 3758096398u; // 0xE000000E
    static const ClassID kCLASSID_StreamMessage                     = 3758096399u; // 0xE000000F
    static const ClassID kCLASSID_ServiceManager                    = 3758096400u; // 0xE0000010
    static const ClassID kCLASSID_AssetLocatorRequest               = 3758096401u; // 0xE0000011
    static const ClassID kCLASSID_AssetLocatorResponse              = 3758096402u; // 0xE0000012
    static const ClassID kCLASSID_AssetLocationMap                  = 3758096403u; // 0xE0000013
    static const ClassID kCLASSID_NetMessage                        = 3758096404u; // 0xE0000014
    static const ClassID kCLASSID_NetListener                       = 3758096405u; // 0xE0000015
    static const ClassID kCLASSID_NetworkStatus                     = 3758096406u; // 0xE0000016
    static const ClassID kCLASSID_ISectionEntry                     = 3758096407u; // 0xE0000017
    static const ClassID kCLASSID_ConfigSection                     = 3758096408u; // 0xE0000018
    static const ClassID kCLASSID_AssetTagger                       = 3758096409u; // 0xE0000019
    static const ClassID kCLASSID_AutoTagger_Mime                   = 3758096410u; // 0xE000001A
    static const ClassID kCLASSID_AutoTagger_PlatSample             = 3758096411u; // 0xE000001B
    static const ClassID kCLASSID_AutoTagger_LogicalId              = 3758096412u; // 0xE000001C
    static const ClassID kCLASSID_AutoTagger_PrecacheSample         = 3758096413u; // 0xE000001D
    static const ClassID kCLASSID_AutoTagger_Directory              = 3758096414u; // 0xE000001E
    static const ClassID kCLASSID_NameResolutionMessage             = 3758096415u; // 0xE000001F
    static const ClassID kCLASSID_NameResolutionRequestV1           = 3758096416u; // 0xE0000020
    static const ClassID kCLASSID_NameResolutionResponseV1          = 3758096417u; // 0xE0000021
    static const ClassID kCLASSID_NameResolutionLocalDone           = 3758096418u; // 0xE0000022
    static const ClassID kCLASSID_NameResolutionRemoteDone          = 3758096419u; // 0xE0000023
    static const ClassID kCLASSID_ProxyMessageTarget                = 3758096420u; // 0xE0000024
    static const ClassID kCLASSID_HighPrecisionClock                = 3758096421u; // 0xE0000025
    static const ClassID kCLASSID_StepHighPrecisionClock            = 3758096422u; // 0xE0000026
    static const ClassID kCLASSID_Logger                            = 3758096423u; // 0xE0000027
    static const ClassID kCLASSID_AssetApplicationInfoMsg           = 3758096424u; // 0xE0000028
    static const ClassID kCLASSID_IAssetFactory                     = 3758096425u; // 0xE0000029
    static const ClassID kCLASSID_BaseAssetFactory                  = 3758096426u; // 0xE000002A
    static const ClassID kCLASSID_GenericAssetFactory               = 3758096427u; // 0xE000002B
    static const ClassID kCLASSID_IAssetResponseData                = 3758096428u; // 0xE000002C
    static const ClassID kCLASSID_GenericAssetFactoryData           = 3758096429u; // 0xE000002D
    static const ClassID kCLASSID_SyncState                         = 3758096430u; // 0xE000002E
    static const ClassID kCLASSID_WaitForConnectionEstablishedState = 3758096431u; // 0xE000002F
    static const ClassID kCLASSID_AssetImporter                     = 3758096432u; // 0xE0000030
    static const ClassID kCLASSID_NameResolutionResponseV2          = 3758096433u; // 0xE0000031
    static const ClassID kCLASSID_FailState                         = 3758096434u; // 0xE0000032
    static const ClassID kCLASSID_DirectedMessage                   = 3758096435u; // 0xE0000033
    static const ClassID kCLASSID_NetMetricsDestination             = 3758096436u; // 0xE0000034
    static const ClassID kCLASSID_WaitForNetIDAssignedState         = 3758096437u; // 0xE0000035
    static const ClassID kCLASSID_ParameterListMessage              = 3758096438u; // 0xE0000036
    static const ClassID kCLASSID_NameResolutionRequest             = 3758096439u; // 0xE0000037
    static const ClassID kCLASSID_NameResolutionResponse            = 3758096440u; // 0xE0000038

} // end namespace efd

#endif // EE_efdClassIDs_h_INCLUDED
