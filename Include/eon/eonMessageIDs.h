//
// This is a generated file.  You should not alter this file manually.

//Source enum: eonMessageIDs.enum

#pragma once
#ifndef EE_eonMessageIDs_h_INCLUDED
#define EE_eonMessageIDs_h_INCLUDED

#include <efd/UniversalTypes.h>
#include <efd/ClassInfo.h>

namespace efd
{

    static const ClassID kMSGID_EntityMessage                        =      24576u; // 0x00006000
    static const ClassID kMSGID_EntityDiscoveryMessage               =      24577u; // 0x00006001
    static const ClassID kMSGID_EntityUpdateMessage                  =      24578u; // 0x00006002
    static const ClassID kMSGID_EntityLossMessage                    =      24579u; // 0x00006003
    static const ClassID kMSGID_ViewEvent                            =      24580u; // 0x00006004
    static const ClassID kMSGID_ClientReLogin                        =      24581u; // 0x00006005
    static const ClassID kMSGID_LoginService_RequestLogin            =      24582u; // 0x00006006
    static const ClassID kMSGID_LoginService_SendLoginResponse       =      24583u; // 0x00006007
    static const ClassID kMSGID_LoginService_RequestLogout           =      24584u; // 0x00006008
    static const ClassID kMSGID_LoginService_JoinChannelResponse     =      24585u; // 0x00006009
    static const ClassID kMSGID_ClientForward                        =      24586u; // 0x0000600A
    static const ClassID kMSGID_GatewayConnectionAccepted            =      24587u; // 0x0000600B
    static const ClassID kMSGID_GatewayConnectionClosed              =      24588u; // 0x0000600C
    static const ClassID kMSGID_Gateway_OnClientLogin                =      24589u; // 0x0000600D
    static const ClassID kMSGID_Gateway_OnClientLogout               =      24590u; // 0x0000600E
    static const ClassID kMSGID_LoginService_OnGatewayLoginComplete  =      24591u; // 0x0000600F
    static const ClassID kMSGID_LoginService_OnGatewayLogoutComplete =      24592u; // 0x00006010
    static const ClassID kMSGID_EmbodymentApproval                   =      24593u; // 0x00006011
    static const ClassID kMSGID_Proxy_SetControllerID                =      24594u; // 0x00006012
    static const ClassID kMSGID_Proxy_JoinChannel                    =      24595u; // 0x00006013
    static const ClassID kMSGID_Proxy_LeaveChannel                   =      24596u; // 0x00006014
    static const ClassID kMSGID_LoginNew                             =      24597u; // 0x00006015
    static const ClassID kMSGID_LoginResponse                        =      24598u; // 0x00006016
    static const ClassID kMSGID_LogoutExit                           =      24599u; // 0x00006017
    static const ClassID kMSGID_LogoutRequest                        =      24600u; // 0x00006018
    static const ClassID kMSGID_ControllerLogin                      =      24601u; // 0x00006019
    static const ClassID kMSGID_ControllerLogout                     =      24602u; // 0x0000601A
    static const ClassID kMSGID_ReplicatedEntityAdded                =      24603u; // 0x0000601B
    static const ClassID kMSGID_ReplicatedEntityUpdated              =      24604u; // 0x0000601C
    static const ClassID kMSGID_ReplicatedEntityRemoved              =      24606u; // 0x0000601E
    static const ClassID kMSGID_PeerJoinResponse                     =      24607u; // 0x0000601F
    static const ClassID kMSGID_DBRequestEnvelope                    =      24608u; // 0x00006020
    static const ClassID kMSGID_DBResponseEnvelope                   =      24609u; // 0x00006021
    static const ClassID kMSGID_IDBRequestMessage                    =      24610u; // 0x00006022
    static const ClassID kMSGID_IDBResponseMessage                   =      24611u; // 0x00006023
    static const ClassID kMSGID_ServerToClientMessage                =      24612u; // 0x00006024
    static const ClassID kMSGID_RequestDiscovery                     =      24613u; // 0x00006025
    static const ClassID kMSGID_ClientDebuggerRequest                =      24614u; // 0x00006026

} // end namespace efd

#endif // EE_eonMessageIDs_h_INCLUDED
