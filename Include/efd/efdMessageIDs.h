//
// This is a generated file.  You should not alter this file manually.

//Source enum: efdMessageIDs.enum

#pragma once
#ifndef EE_efdMessageIDs_h_INCLUDED
#define EE_efdMessageIDs_h_INCLUDED

#include <efd/UniversalTypes.h>
#include <efd/ClassInfo.h>

namespace efd
{

    static const ClassID kMSGID_SubscribeExternal                =       4096u; // 0x00001000
    static const ClassID kMSGID_UnsubscribeExternal              =       4097u; // 0x00001001
    static const ClassID kMSGID_Resubscribe                      =       4098u; // 0x00001002
    static const ClassID kMSGID_BeginCategoryProduction          =       4099u; // 0x00001003
    static const ClassID kMSGID_EndCategoryProduction            =       4100u; // 0x00001004
    static const ClassID kMSGID_RequestNetID                     =       4101u; // 0x00001005
    static const ClassID kMSGID_SetNetID                         =       4102u; // 0x00001006
    static const ClassID kMSGID_RemoteWrapper                    =       4103u; // 0x00001007
    static const ClassID kMSGID_SendToProducer                   =       4104u; // 0x00001008
    static const ClassID kMSGID_ResubscribeComplete              =       4105u; // 0x00001009
    static const ClassID kMSGID_AnnounceNetID                    =       4106u; // 0x0000100A
    static const ClassID kMSGID_UnreliableVersion                =       4107u; // 0x0000100B
    static const ClassID kMSGID_ConnectionConnectedMsg           =       4108u; // 0x0000100C
    static const ClassID kMSGID_ConnectionFailedToConnectMsg     =       4109u; // 0x0000100D
    static const ClassID kMSGID_ConnectionDisconnectedMsg        =       4110u; // 0x0000100E
    static const ClassID kMSGID_ConnectionDataReceivedMsg        =       4111u; // 0x0000100F
    static const ClassID kMSGID_ConnectionAcceptedMsg            =       4112u; // 0x00001010
    static const ClassID kMSGID_ConnectionFailedToAcceptMsg      =       4113u; // 0x00001011
    static const ClassID kMSGID_NetServiceConnectionEstablished  =       4114u; // 0x00001012
    static const ClassID kMSGID_NetServiceConnectionClosed       =       4115u; // 0x00001013
    static const ClassID kMSGID_NetServiceConnectionFailed       =       4116u; // 0x00001014
    static const ClassID kMSGID_ChannelManagerConnectionAccepted =       4117u; // 0x00001015
    static const ClassID kMSGID_ChannelManagerConnectionClosed   =       4118u; // 0x00001016
    static const ClassID kMSGID_NetworkBufferOK                  =       4119u; // 0x00001017
    static const ClassID kMSGID_NetworkBuffer1X                  =       4120u; // 0x00001018
    static const ClassID kMSGID_NetworkBuffer2X                  =       4121u; // 0x00001019
    static const ClassID kMSGID_NetworkBuffer3X                  =       4122u; // 0x0000101A
    static const ClassID kMSGID_NetworkFailure                   =       4123u; // 0x0000101B
    static const ClassID kMSGID_ConsoleInput                     =       4124u; // 0x0000101C
    static const ClassID kMSGID_LogServiceRequest                =       4125u; // 0x0000101D
    static const ClassID kMSGID_LogServiceResponse               =       4126u; // 0x0000101E
    static const ClassID kMSGID_GetLogDestinationsRequest        =       4127u; // 0x0000101F
    static const ClassID kMSGID_GetLogDestinationsResponse       =       4128u; // 0x00001020
    static const ClassID kMSGID_GetModulesRequest                =       4129u; // 0x00001021
    static const ClassID kMSGID_GetModulesResponse               =       4130u; // 0x00001022
    static const ClassID kMSGID_GetLogLevelRequest               =       4131u; // 0x00001023
    static const ClassID kMSGID_GetLogLevelResponse              =       4132u; // 0x00001024
    static const ClassID kMSGID_GetMsgLogLevelRequest            =       4133u; // 0x00001025
    static const ClassID kMSGID_GetMsgLogLevelResponse           =       4134u; // 0x00001026
    static const ClassID kMSGID_SetLogLevelRequest               =       4135u; // 0x00001027
    static const ClassID kMSGID_SetLogLevelResponse              =       4136u; // 0x00001028
    static const ClassID kMSGID_SetMsgLogLevelRequest            =       4137u; // 0x00001029
    static const ClassID kMSGID_SetMsgLogLevelResponse           =       4138u; // 0x0000102A
    static const ClassID kMSGID_StartLogStreamRequest            =       4139u; // 0x0000102B
    static const ClassID kMSGID_StartLogStreamResponse           =       4140u; // 0x0000102C
    static const ClassID kMSGID_StopLogStreamRequest             =       4141u; // 0x0000102D
    static const ClassID kMSGID_StopLogStreamResponse            =       4142u; // 0x0000102E
    static const ClassID kMSGID_LogEntriesMessage                =       4143u; // 0x0000102F
    static const ClassID kMSGID_AssetLocatorRequest              =       4144u; // 0x00001030
    static const ClassID kMSGID_AssetServerConnectNotify         =       4145u; // 0x00001031
    static const ClassID kMSGID_AssetLocatorResponse             =       4146u; // 0x00001032
    static const ClassID kMSGID_AssetServerChangeNotify          =       4147u; // 0x00001033
    static const ClassID kMSGID_AssetFetchDataRequest            =       4148u; // 0x00001034
    static const ClassID kMSGID_AssetFetchDataResponse           =       4149u; // 0x00001035
    static const ClassID kMSGID_AssetConfigRequest               =       4151u; // 0x00001037
    static const ClassID kMSGID_AssetConfigResponse              =       4152u; // 0x00001038
    static const ClassID kMSGID_AssetConfigNotify                =       4153u; // 0x00001039
    static const ClassID kMSGID_AssetBrowseInfoRequest           =       4154u; // 0x0000103A
    static const ClassID kMSGID_AssetBrowseInfoResponse          =       4155u; // 0x0000103B
    static const ClassID kMSGID_AssetTagsInfoRequest             =       4156u; // 0x0000103C
    static const ClassID kMSGID_AssetTagsInfoResponse            =       4157u; // 0x0000103D
    static const ClassID kMSGID_AssetLocateEnumResponse          =       4158u; // 0x0000103E
    static const ClassID kMSGID_TestShutdown                     =       4159u; // 0x0000103F
    static const ClassID kMSGID_StartTick                        =       4160u; // 0x00001040
    static const ClassID kMSGID_SyncState                        =       4161u; // 0x00001041
    static const ClassID kMSGID_AssetLoadRequest                 =       4162u; // 0x00001042
    static const ClassID kMSGID_AssetLoadResponse                =       4163u; // 0x00001043
    static const ClassID kMSGID_GenericAssetLoadResponse         =       4164u; // 0x00001044
    static const ClassID kMSGID_AssetCacheResponse               =       4165u; // 0x00001045
    static const ClassID kMSGID_ClientLogServiceRequest          =       4166u; // 0x00001046
    static const ClassID kMSGID_ClientLogServiceResponse         =       4167u; // 0x00001047
    static const ClassID kMSGID_ServiceDiscoveryRequest          =       4168u; // 0x00001048
    static const ClassID kMSGID_ServiceDiscoveryResponse         =       4169u; // 0x00001049
    static const ClassID kMSGID_NetErrorMessage                  =       4171u; // 0x0000104B
    static const ClassID kMSGID_AckNetID                         =       4172u; // 0x0000104C
    static const ClassID kMSGID_ChannelManagerClientJoin         =       4173u; // 0x0000104D
    static const ClassID kMSGID_ChannelManagerClientLeave        =       4174u; // 0x0000104E
    static const ClassID kMSGID_AssetServerShutdown              =       4175u; // 0x0000104F
    static const ClassID kMSGID_ChannelManagerPortInUse          =       4176u; // 0x00001050
    static const ClassID kMSGID_AssetFlushRequest                =       4177u; // 0x00001051
    static const ClassID kMSGID_AssetFlushSuccess                =       4178u; // 0x00001052
    static const ClassID kMSGID_AssetFlushFailed                 =       4179u; // 0x00001053
    static const ClassID kMSGID_AssetConfigurationMessage        =       4180u; // 0x00001054

} // end namespace efd

#endif // EE_efdMessageIDs_h_INCLUDED
