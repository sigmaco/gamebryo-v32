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
#ifndef EE_BAPIINTERNAL_H
#define EE_BAPIINTERNAL_H

#include <efd/StdContainers.h>
#include <egf/BehaviorAPI.h>
#include <egf/egfLibType.h>
#include <egf/EntityManager.h>

// NOTE: Methods in this file are NOT bound into SWIG!  This file exists for internal C++ helper
// methods that are used by various behavior methods and might need to use used by other behavior
// libraries.

namespace bapiInternal
{


/**
    A helper filter function to exclude an entity id when finding all entities.  Can be used
    with the FindAllEntities method to find "all but one" entities.

    @param i_pEntity The entity to compare against the filter
    @param pParam Pointer to an egf::EntityID defining the Id to exclude
    @return True if the provided entity should be included in the results
 */
EE_EGF_ENTRY bool FF_ExcludeSingleID(const egf::Entity* i_pEntity, void* pParam);

/**
    Get a list of all the EntityIDs that match the selection filter and push all the results
    into a list.

    @note Typically you should use EntityManager::GetFilteredIterator directly rather than
    calling this method.  However, for interfacing with scripting it is sometimes helpful to
    generate the equivalent results into a single list.

    @param i_pfnFilter A filter function to filter the entities to return.
    @param pParam The parameter to pass to the filter function.
    @param o_results the resulting list of entity IDs.
    @return The number of entities added to the result list
 */
EE_EGF_ENTRY efd::UInt32 FindAllEntities(
    egf::EntityManager::FilterFunction i_pfnFilter,
    void* pParam,
    efd::list<egf::EntityID>& o_results);


/**
    Given a list of strings, remove all the strings that do not contain the filter substring.

    @param[in] i_filter The pattern that should be in all remaining string
    @param[in,out] io_list The list so string which will have non-matching strings removed
*/
EE_EGF_ENTRY void RemoveNonMatchingStrings(
    const efd::utf8string& i_filter,
    efd::list<efd::utf8string>& io_list);

} // end namespace bapiInternal

#endif // !defined(EE_BAPIINTERNAL_H)
