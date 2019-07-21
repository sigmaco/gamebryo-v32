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
#ifndef EE_PICKSERVICE_H
#define EE_PICKSERVICE_H

// To get SDM chains correct we need to pull in the top-level Ni header.
// In this case, NiCollision.
#include <NiCollision.h>
#include "ecrLibType.h"

#include "RenderService.h"
#include "SceneGraphService.h"
#include <ecr/ecrSystemServiceIDs.h>

namespace egf
{
    class EntityManager;
}

namespace ecr
{

/**
    The picking service is responsible for issuing pick requests on the scene
    graphs contained in the SceneGraphService.

    The PickService class provides functions for performing picking, and functions for
    script built-ins. It requires the SceneGraphService and the EntityManager to be present.

    See the NiPick reference documentation for more information on picking.
*/
class EE_ECR_ENTRY PickService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(PickService, efd::kCLASSID_PickService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /**
        A PickRecord object stores the information used when issuing a pick and
        retrieving the results of the pick operation.
    */
    class EE_ECR_ENTRY PickRecord : public efd::MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;

    public:

        /// Constructor takes the origin of the picking ray and its direction.
        PickRecord(const efd::Point3& origin, const efd::Point3& direction);

        /// Returns the picking ray origin.
        const efd::Point3& GetRayOrigin() const;

        /// Returns the picking ray direction.
        const efd::Point3& GetRayDirection() const;

        /// Returns the results of the pick operation.
        const NiPick::Results* GetPickResult() const;

    private:

        efd::Point3 m_rayOrigin;
        efd::Point3 m_rayDirection;
        NiPick::Results* m_pResults;

        friend class PickService;
    };

    /// A smart pointer type for the PickRecord class.
    typedef efd::SmartPointer<PickRecord> PickRecordPtr;

    /**
        Constructs the picking service and performs pre-init operations.

        The picking policy is set to an IgnoreParticlePickObjectPolicy object, which causes
        particle systems to not be picked. The picker is told to return normal vector
        information and to pick at the triangle level (NiPick::INTERSECT_TRIANGLE).

        @param bPickAppCulled If true, objects with the App Culled flag set (hidden) may
            be picked. If false, App Culled objects will not be picked.
        @param bPickFrontOnly If true, only front facing triangles are considered. All triangles
            are considered when this argument is false.
        @param bPickClosestOnly If true, only the closest object is picked. All objects along the
            ray are returned when this argument is false.
    */
    PickService(
        const bool bPickAppCulled = true,
        const bool bPickFrontOnly = true,
        const bool bPickClosestOnly = false);

    /**
        Perform a pick operation.

        The given ray is tested against all Entity-based scene graphs known to the
        SceneGraphService. The default App Culled, Front Facing and Closest Only flags are used.

        @return A PickRecord object containing the results of the pick. The calling code is
            responsible for deleting the pointer (using EE_DELETE).
    */
    virtual PickRecord* PerformPick(const efd::Point3& rayOrigin, const efd::Point3& rayDir);

    /**
        Perform a pick operation with the given App Culled, Front Only, and Closest Only flags.

        The given ray is tested against all Entity-based scene graphs known to the
        SceneGraphService.

        @return A PickRecord object containing the results of the pick. The calling code is
            responsible for deleting the pointer (using EE_DELETE).
    */
    virtual PickRecord* PerformPick(
        const efd::Point3& rayOrigin,
        const efd::Point3& rayDir,
        const bool bPickFrontOnly,
        const bool bPickAppCulled,
        const bool bPickClosestOnly);

    /**
        Perform a pick operation on a specific scene graph.

        The default App Culled, Front Facing and Closest Only flags are used.

        @return A PickRecord object containing the results of the pick. The calling code is
            responsible for deleting the pointer (using EE_DELETE).
    */
    virtual PickRecord* PerformPick(
        const efd::Point3& rayOrigin,
        const efd::Point3& rayDir,
        NiAVObject* testObject);

    /**
        Perform a pick operation on a specific scene graph with the given App Culled,
        Front Only, and Closest Only flags.

        @return A PickRecord object containing the results of the pick. The calling code is
            responsible for deleting the pointer (using EE_DELETE).
    */
    virtual PickRecord* PerformPick(
        const efd::Point3& rayOrigin,
        const efd::Point3& rayDir,
        NiAVObject* testObject,
        const bool bPickFrontOnly,
        const bool bPickAppCulled,
        const bool bPickClosestOnly);

    /**
        Allows pick policies to be registered for a particular entity model. All entities
        containing the specified model will then use the registered pick policy/mechanism.

        This method may be called prior to OnInit.

        @param modelName Name of the model with which to use custom picking logic.
        @param pPolicy Pick policy object to use on entities containing the specified model.
        @return True if registration was successful, false otherwise. Note, only one policy object
            may be specified per model name.

        @note Pick policies are only functional with entity based scene graphs. Any scene graphs
            added through the handle mechanism will not use pick policies.
    */
    efd::Bool RegisterPickPolicy(
        const efd::utf8string& modelName,
        NiPick::PickObjectPolicy* pPolicy);

    /**
        Unregisters the pick policy for the specified model name.

        This method may be called prior to OnInit.

        @param modelName Name of the model with which to remove the policy.
        @return True if successful, false if there was no pick policy registered for the specified
            model name.
    */
    efd::Bool UnregisterPickPolicy(const efd::utf8string& modelName);

    /**
        Gets a pointer to the underlying pick object used to resolve scene graph pick requests.

        This may be called during OnInit, but will return NULL during OnPreInit.

        @return Pointer to the pick object.
    */
    inline NiPick* GetPickObject() const;

protected:
    /**
        Returns the name of the service, "PickService".
    */
    virtual const char* GetDisplayName() const;

    /**
        Caches pointers to other services.

        @return SyncResult_Complete
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        The picking service does not perform any shutdown work.

        @return AsyncResult_Complete
    */
    virtual efd::AsyncResult OnShutdown();

    /**
        Functor class which is called for each entity in the scene graph service when a pick
        request is made. The functor will check for a pick policy based on the set of registered
        model names and perform a pick operation accordingly. If a specific pick policy has not
        been specified for a given model, the default pick policy is used.
    */
    class PickObjectFunctor : public SceneGraphService::EntitySceneGraphFunctor
    {
    public:

        /**
            Operator to apply to each entity's scene graph.
        */
        efd::Bool operator()(const egf::Entity* entity,
            const efd::vector<NiObjectPtr>& objects);

        PickService* m_pPickService;
        egf::EntityManager* m_pEntityManager;
        NiPoint3 m_rayOrigin;
        NiPoint3 m_rayDir;
    };

    /**
        Cleans up any remaining resources used by the picking service.
    */
    virtual ~PickService();

    efd::map<efd::utf8string, NiPick::PickObjectPolicyPtr> m_pickPolicies;
    NiPick::PickObjectPolicyPtr m_spDefaultPickPolicy;

    PickObjectFunctor m_pickFunctor;

    NiPick* m_pPicker;
    bool m_bPickFrontOnly;
    bool m_bPickAppCulled;
    bool m_bPickClosestOnly;
    SceneGraphServicePtr m_spSceneGraphService;

    friend class PickObjectFunctor;
};

typedef efd::SmartPointer<PickService> PickServicePtr;

}; // namespace

#include "PickService.inl"

namespace ecr
{

class EE_ECR_ENTRY IgnoreParticlePickObjectPolicy :
    public SimpleSkinPickObjectPolicy
{
public:
    virtual bool FindIntersections(
        const NiPoint3& kOrigin, const NiPoint3& kDir, NiPick& kPick,
        NiRenderObject* pkRenderObj);
};

}; // namespace

#endif  // EE_PICKSERVICE_H
