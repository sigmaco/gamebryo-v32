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

// Namespace in include guard to avoid conflict with other SceneMessage in other namespaces.
#ifndef EE_EGFPHYSX_SCENEMESSAGE_H
#define EE_EGFPHYSX_SCENEMESSAGE_H

#include "egfPhysXLibType.h"

#include <efd/Category.h>
#include <efd/IDs.h>
#include <efd/IMessage.h>
#include <efd/SystemFrameworkEnums.h>
#include <efdPhysX/PhysXSDKManager.h>
#include <egf/egfMessageIDs.h>
#include <egf/Entity.h>
#include <egf/egfSystemServiceIDs.h>

namespace egfPhysX
{
    // This is a special category used by the SceneService to send messages.
    static const efd::Category kCAT_egfPhysXMessage =
        efd::Category(efd::UniversalID::ECU_Any, efd::kNetID_Any, efd::kCLASSID_SceneService);

    /**
        Message class for SceneAddedMessage, SceneRemovingMessage, SceneRemovedMessage messages
    */
    class EE_EGFPHYSX_ENTRY SceneMessage :
        public efd::IMessage
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(SceneMessage, efd::kMSGID_PhysXSceneMessage, IMessage);
        /// @endcond

    public:
        SceneMessage();

        virtual void Serialize(efd::Archive& ar);

        inline const efd::utf8string& GetSceneName() const;
        inline void SetSceneName(const efd::utf8string& sceneName);

        inline NxScene* GetScene() const;
        inline void SetScene(NxScene* pScene);

        //inline const egf::EntityPtr GetEntity() const;
        //inline void SetEntity(egf::EntityPtr spEntity);

        inline static efd::IBasePtr FactoryMethod();

    protected:
        efd::utf8string m_sceneName;
        NxScene* m_pScene;
        //egf::EntityPtr m_spEntity;
    };
    typedef efd::SmartPointer<SceneMessage> SceneMessagePtr;

    /// @name MessageWrappers from SceneMessage.h
    //@{
    typedef efd::MessageWrapper<SceneMessage, efd::kMSGID_PhysXSceneAdded> SceneAddedMessage;
    typedef efd::MessageWrapper<SceneMessage, efd::kMSGID_PhysXSceneRemoving> SceneRemovingMessage;
    typedef efd::MessageWrapper<SceneMessage, efd::kMSGID_PhysXSceneRemoved> SceneRemovedMessage;
    //@}

    /**
        Message class for StartSimulationMessage, FinishingSimulationMessage,
        FinishedSimulationMessage, and SimulationTimeUpdatedMessage messages
    */
    class EE_EGFPHYSX_ENTRY SimulationMessage :
        public efd::IMessage
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(SimulationMessage, efd::kMSGID_PhysXSceneSimulation, IMessage);
        /// @endcond

    public:
        SimulationMessage();

        virtual void Serialize(efd::Archive& ar);

        inline const efd::utf8string& GetSceneName() const;
        inline void SetSceneName(const efd::utf8string& sceneName);

        inline const efd::TimeType& GetTime() const;
        inline void SetTime(const efd::TimeType& time);

        inline efd::Bool GetBlockOnFetch() const;
        inline void SetBlockOnFetch(efd::Bool blockOnFetch);

        inline static efd::IBasePtr FactoryMethod();

    protected:
        efd::utf8string m_sceneName;
        efd::TimeType m_time;
        efd::Bool m_blockOnFetch;
    };
    typedef efd::SmartPointer<SimulationMessage> SimulationMessagePtr;

    /// @name MessageWrappers from SceneMessage.h
    //@{
    typedef efd::MessageWrapper<SimulationMessage, efd::kMSGID_PhysXSceneSimulationStarting>
        StartSimulationMessage;
    typedef efd::MessageWrapper<SimulationMessage, efd::kMSGID_PhysXSceneSimulationFinishing>
        FinishingSimulationMessage;
    typedef efd::MessageWrapper<SimulationMessage, efd::kMSGID_PhysXSceneSimulationFinished>
        FinishedSimulationMessage;
    typedef efd::MessageWrapper<SimulationMessage, efd::kMSGID_PhysXSceneSimulationTimeUpdated>
        SimulationTimeUpdatedMessage;
    //@}
} // namespace egfPhysX

#include <egfPhysX/SceneMessage.inl>

#endif // EE_EGFPHYSX_SCENEMESSAGE_H