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

#pragma once
#ifndef EE_BAPIBLOCK_H
#define EE_BAPIBLOCK_H

#include <efd/StdContainers.h>
#include <egf/BehaviorAPI.h>
#include <egf/egfLibType.h>
#include <egf/BlockLoadParameters.h>


// NOTE: This is a SWIG parsed file.  All methods listed in this file will have script wrappers
// generated.
//
// A note on argument types:
//
// Given any type the SWIG generated bindings will make certain assumptions about whether the
// parameter is an input argument, and output argument, or an input-output argument.  Given
// a type T, it will be treated as follows:
//
//    |---------------|---------------|------------------------------------------------------
//    | typename:     | treated as:   | notes:
//    |---------------|---------------|------------------------------------------------------
//    | T             | Input         |
//    | const T&      | Input         |
//    | const T*      | Input         | Pointer must NOT be NULL
//    | T*            | Output        | Pointer must NOT be NULL
//    | T&            | Input-Output  |
//    |---------------|---------------|------------------------------------------------------
//
// The one exception to the argument type rules above is efd::ParameterList.  efd::ParameterList*
// is treated as a basic type for the purpose of these rules, not efd::ParameterList itself.  For
// example, this means that "efd::ParameterList*" is treated as a plain ParameterList Input argument
// and "efd::ParameterList*&" is treated as an in-out efd::ParameterList parameter.  One additional
// special case, for convenance "efd::ParameterList&" is also treated as an in-out parameter.

namespace BehaviorAPI
{


/**
    Loads a block file and optionally invokes a callback behavior when complete. Any valid
    AssetID can be specified, such as a URN-style query or a logical asset ID.

    @param blockURN The block to load
    @param callback [optional] The behavior to invoke when the block load completes.  This
        behavior will be called if the load fails or when the block is completely loaded.
    @param context [optional] A context that will be returned in the callback data
    @param autoEnterWorld [optional] Specify whether entities in the loaded block(s) should
        automatically enter the world once created.
    @return True if the block load has been started.
*/
EE_EGF_ENTRY bool LoadBlockFile(
    char* blockURN,
    char* callback = NULL,
    efd::UInt32 context = 0,
    bool autoEnterWorld = egf::BlockLoadParameters::GetDefaultAutoEnterWorld());


/**
    Loads a block file with the ability to set all block loading parameters.  Any valid AssetID can
    be specified, such as a URN-style query or a logical asset ID. Takes a ParameterList containing
    whatever BlockLoadParameters you want to set. All parameters are optional so set only those you
    require. Valid options to place in the parameter list include:

    - Instance (UInt32): sets the instance ID which along with the blockURN uniquely defined the
        block to load. The same block can be loaded multiple times so long as a different instance
        number is used with each load.
    - AutoEnter (boolean): controls whether entities in the block automatically enter the world.
    - Callback (string): the name of a callback behavior on the current script entity.
    - Context (UInt32): a context that will be passed back to the callback behavior.
    - ActiveCallbacks (UInt32): a combination of BlockLoadCallback flags defining when the callback
        should be invoked.
    - Rotation (Point3): a rotation about the origin that can adjust the position and rotation of
        all entities in the loaded block.
    - Offset (Point3): an offset that can adjust the position of all entities in the loaded block.
    - LoadThreashold (UInt32): an override for the EntityLoaderService::GetMaxEntityLoadThrottle
        that will effect only this block.
    - UnloadThreashold (UInt32): an override for the EntityLoaderService::GetMaxEntityUnloadThrottle
        that will effect only this block.

    @param blockURN The block to load
    @param pParams A ParameterList containing various parameters as defined above.
    @return True if the block load has been started.
*/
EE_EGF_ENTRY bool LoadBlockFile(char* blockURN, efd::ParameterList* pParams);


/**
    Unload an already loaded block file and optionally invokes a callback behavior when complete.
    The URN can be any valid query that resolves to a currently loaded block or blocks.

    @param blockURN The block to unload
    @param callback [optional] The behavior to invoke when the block unload completes.  This
        behavior will be called if the unload fails or when the block is completely unloaded.
    @param context [optional] A context that will be returned in the callback data
    @return True if the block unload has been started.
*/
EE_EGF_ENTRY bool UnloadBlockFile(char* blockURN, char* callback = NULL, efd::UInt32 context = 0);


/**
    Unload an instanced block file and optionally invokes a callback behavior when complete.
    The URN used to unload a block should match the URN used to load the block. Takes a
    ParameterList containing additional settings. All parameters are optional so set only those you
    require. Valid options to place in the parameter list include:

    - Instance (UInt32): sets the instance ID which along with the blockURN uniquely defined the
        block to load. The same block can be loaded multiple times so long as a different instance
        number is used with each load.
    - Callback (string): the name of a callback behavior on the current script entity.
    - Context (UInt32): a context that will be passed back to the callback behavior.

    @param blockURN The block to unload
    @param pParams A ParameterList containing various parameters as defined above.
    @return True if the block unload has been started.
*/
EE_EGF_ENTRY bool UnloadBlockFile(char* blockURN, efd::ParameterList* pParams);

/**
    Request the specified entity set enter the world. This will cause the OnEnterWorld behavior,
    if it exists, to be called for each entity in the entity set that is not already in the world.
    The URN can be either the Physical AssetID of a specific block or it can be the exact URN used
    to originally load the block, for example as passed to the LoadBlockFile API.

    @param[in] blockURN The block to ask to enter the world.
    @param[in] instance The instance number of the block to unload
    @return boolean true for success
*/
EE_EGF_ENTRY bool EntitySetEnterWorld(char* blockURN, efd::UInt32 instance = 0);

/**
    Request the specified entity set enter the world. This will cause the OnExitWorld behavior,
    if it exists, to be called for each entity in the entity set that is already in the world.
    The URN can be either the Physical AssetID of a specific block or it can be the exact URN used
    to originally load the block, for example as passed to the LoadBlockFile API.

    @param[in] blockURN The block to ask to exit the world.
    @param[in] instance The instance number of the block to unload
    @return boolean true for success
*/
EE_EGF_ENTRY bool EntitySetExitWorld(char* blockURN, efd::UInt32 instance = 0);

} // end namespace BehaviorAPI

#endif // !defined(EE_BAPIBLOCK_H)
