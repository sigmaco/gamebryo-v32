//
// This is a generated file.  You should not alter this file manually.

//Source enum: egfMessageIDs.enum

#pragma once
#ifndef EE_egfMessageIDs_h_INCLUDED
#define EE_egfMessageIDs_h_INCLUDED

#include <efd/UniversalTypes.h>
#include <efd/ClassInfo.h>

namespace efd
{

    static const ClassID kMSGID_Event                              =       8192u; // 0x00002000
    static const ClassID kMSGID_EventReturn                        =       8193u; // 0x00002001
    static const ClassID kMSGID_EventCancel                        =       8194u; // 0x00002002
    static const ClassID kMSGID_OwnedEntityAdded                   =       8195u; // 0x00002003
    static const ClassID kMSGID_OwnedEntityUpdated                 =       8196u; // 0x00002004
    static const ClassID kMSGID_OwnedEntityRemoved                 =       8197u; // 0x00002005
    static const ClassID kMSGID_EntityChangeMessage                =       8198u; // 0x00002006
    static const ClassID kMSGID_SchedulerBeginReload               =       8199u; // 0x00002007
    static const ClassID kMSGID_SchedulerCleared                   =       8200u; // 0x00002008
    static const ClassID kMSGID_ELSUnloaded                        =       8201u; // 0x00002009
    static const ClassID kMSGID_EntityLoadRequest                  =       8202u; // 0x0000200A
    static const ClassID kMSGID_EntityLoadResult                   =       8203u; // 0x0000200B
    static const ClassID kMSGID_EntityPreloadRequest               =       8204u; // 0x0000200C
    static const ClassID kMSGID_EntityPreloadResponse              =       8205u; // 0x0000200D
    static const ClassID kMSGID_NoticeEntityDiscovered             =       8206u; // 0x0000200E
    static const ClassID kMSGID_NoticeEntityUpdated                =       8207u; // 0x0000200F
    static const ClassID kMSGID_NoticeEntityRemoved                =       8208u; // 0x00002010
    static const ClassID kMSGID_StartDebuggerRequest               =       8209u; // 0x00002011
    static const ClassID kMSGID_BreakpointRequest                  =       8210u; // 0x00002012
    static const ClassID kMSGID_BreakpointResponse                 =       8211u; // 0x00002013
    static const ClassID kMSGID_ClearBreakpoints                   =       8212u; // 0x00002014
    static const ClassID kMSGID_ClearBreakpointsResponse           =       8213u; // 0x00002015
    static const ClassID kMSGID_InsertModelBreakpoint              =       8214u; // 0x00002016
    static const ClassID kMSGID_RemoveModelBreakpoint              =       8215u; // 0x00002017
    static const ClassID kMSGID_GetModelBreakpoints                =       8216u; // 0x00002018
    static const ClassID kMSGID_GetModelBreakpointsResponse        =       8217u; // 0x00002019
    static const ClassID kMSGID_InsertEntityBreakpoint             =       8218u; // 0x0000201A
    static const ClassID kMSGID_RemoveEntityBreakpoint             =       8219u; // 0x0000201B
    static const ClassID kMSGID_GetEntityBreakpoints               =       8220u; // 0x0000201C
    static const ClassID kMSGID_GetEntityBreakpointsResponse       =       8221u; // 0x0000201D
    static const ClassID kMSGID_ScriptDebuggerCommand              =       8222u; // 0x0000201E
    static const ClassID kMSGID_ScriptDebuggerResponse             =       8223u; // 0x0000201F
    static const ClassID kMSGID_WorldResetRequest                  =       8224u; // 0x00002020
    static const ClassID kMSGID_GamePauseRequest                   =       8225u; // 0x00002021
    static const ClassID kMSGID_GameResumeRequest                  =       8226u; // 0x00002022
    static const ClassID kMSGID_PhysXSceneMessage                  =       8227u; // 0x00002023
    static const ClassID kMSGID_PhysXSceneAdded                    =       8228u; // 0x00002024
    static const ClassID kMSGID_PhysXSceneRemoving                 =       8229u; // 0x00002025
    static const ClassID kMSGID_PhysXSceneRemoved                  =       8230u; // 0x00002026
    static const ClassID kMSGID_PhysXSceneSimulation               =       8231u; // 0x00002027
    static const ClassID kMSGID_PhysXSceneSimulationStarting       =       8232u; // 0x00002028
    static const ClassID kMSGID_PhysXSceneSimulationFinishing      =       8233u; // 0x00002029
    static const ClassID kMSGID_PhysXSceneSimulationFinished       =       8234u; // 0x0000202A
    static const ClassID kMSGID_PhysXSceneSimulationTimeUpdated    =       8235u; // 0x0000202B
    static const ClassID kMSGID_FlatModelFactoryRequest            =       8236u; // 0x0000202C
    static const ClassID kMSGID_FlatModelFactoryResponse           =       8237u; // 0x0000202D
    static const ClassID kMSGID_EntityFactoryRequest               =       8238u; // 0x0000202E
    static const ClassID kMSGID_EntityFactoryResponse              =       8239u; // 0x0000202F
    static const ClassID kMSGID_WorldFactoryRequest                =       8240u; // 0x00002030
    static const ClassID kMSGID_WorldFactoryResponse               =       8241u; // 0x00002031
    static const ClassID kMSGID_ScriptFactoryRequest               =       8242u; // 0x00002032
    static const ClassID kMSGID_ScriptFactoryResponse              =       8243u; // 0x00002033
    static const ClassID kMSGID_SimDebuggerCommand                 =       8244u; // 0x00002034
    static const ClassID kMSGID_DebugNoteBase                      =       8245u; // 0x00002035
    static const ClassID kMSGID_DebugNoteEvent                     =       8246u; // 0x00002036
    static const ClassID kMSGID_DebugNoteSessionStarted            =       8247u; // 0x00002037
    static const ClassID kMSGID_DebugNoteFlatModelDefined          =       8248u; // 0x00002038
    static const ClassID kMSGID_DebugNoteEntityCreated             =       8249u; // 0x00002039
    static const ClassID kMSGID_DebugNoteEntityDestroyed           =       8250u; // 0x0000203A
    static const ClassID kMSGID_DebugNotePropertyChanged           =       8251u; // 0x0000203B
    static const ClassID kMSGID_DebugNoteCollectionPropertyChanged =       8252u; // 0x0000203C
    static const ClassID kMSGID_OwnedEntityEnterWorld              =       8253u; // 0x0000203D
    static const ClassID kMSGID_OwnedEntityExitWorld               =       8254u; // 0x0000203E
    static const ClassID kMSGID_WorldResetBegin                    =       8255u; // 0x0000203F
    static const ClassID kMSGID_WorldResetEnd                      =       8256u; // 0x00002040

} // end namespace efd

#endif // EE_egfMessageIDs_h_INCLUDED
