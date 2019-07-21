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

// BehaviorAPI Lua module
%module BehaviorAPI;

#define LUA_SCRIPTING
%{
#include <egfLua/bapiLua.h>
#include <egfLua/EntityLua.h>
%}

%rename(LogMessage) BehaviorAPI::LogMessageLua;
%rename(LogError) BehaviorAPI::LogErrorLua;
%ignore BehaviorAPI::LogMessagePython;
%ignore BehaviorAPI::LogErrorPython;

%native(GetProperty) int egf::lua_GetProperty(lua_State *L);
%native(GetDefaultProperty) int egf::lua_GetDefaultProperty(lua_State *L);
%native(SetProperty) int egf::lua_SetProperty(lua_State* L);
%native(SendAndWaitForReply) int egf::lua_SendAndWaitForReply(lua_State* L);
%native(Sleep) int egf::lua_Sleep(lua_State* L);
%native(DumpProperties) int egf::lua_DumpProperties(lua_State* L);
%native(BreakIfFalse) int egf::lua_BreakIfFalse(lua_State* L);
%native(CreateEntityAndWait) int egf::lua_CreateEntityAndWait(lua_State* L);

%import "egfLua/bapiLuaTypeMaps.i"

// Simply include the real BehaviorAPI.i file:
%include "egf/BehaviorAPI.i"
