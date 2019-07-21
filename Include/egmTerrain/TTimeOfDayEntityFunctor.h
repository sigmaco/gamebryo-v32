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

#ifndef TTIMEOFDAYENTITYFUNCTOR_H
#define TTIMEOFDAYENTITYFUNCTOR_H

#include "egmTerrainLibType.h"
#include <egf/EntityID.h>
#include <egf/egfPropertyIDs.h>

// foreward declaration
namespace egf
{
    class EntityManager;
}

namespace egmTerrain
{

/**
    Functor class allowing egf::Entity object to be registered with the NiTimeOfDay object.

    This is a templated class that can be associated with any property types supported by the 
    NiTimeOfDay. It will use the member variable set by the constructor to allow the NiTimeOfDay 
    object to animate the appropriate property values.

    @see NiTTimeOfDayDefaultFunctor for more information.
*/
template<class Value>
class EE_EGMTERRAIN_ENTRY TTimeOfDayEntityFunctor
{
public:
    /// References the templated type in use for this functor.
    typedef Value TargetValue;

    /**
        Default constructor
    */
    TTimeOfDayEntityFunctor() {}
    
    /**
        Initialization constructor
    */
    inline TTimeOfDayEntityFunctor(egf::EntityManager* pEntityManager,
        egf::EntityID targetObject, egf::PropertyID targetProperty);

    /**
        Sets the value of the target entity property.
        @param val The values to set.
    */
    inline void SetValue(Value val);

private:

    /// The object that the functor targets
    egf::EntityID m_functorTargetObject;

    /// The property targeted by the functor
    egf::PropertyID m_functorTargetProperty;

    /// The entity manager to all for the look up of the entity
    egf::EntityManager* m_pEntityManager;

};

#include "TTimeOfDayEntityFunctor.inl"

}; //namespace

#endif