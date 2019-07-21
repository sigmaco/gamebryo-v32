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
#ifndef NIACTORMANAGER_H
#define NIACTORMANAGER_H

#include "NiAnimationConstants.h"
#include <NiRefObject.h>
#include <NiNode.h>
#include <NiTObjectList.h>
#include "NiKFMTool.h"
#include "NiSequenceData.h"
#include "NiControllerManager.h"
#include "NiTextKeyMatch.h"

class NiPoseBinding;
class NiSkinningLODController;

NiSmartPointer(NiTextKeyMatch);

class NIANIMATION_ENTRY NiActorManager :
    public NiRefObject,
    public NiSequenceData::ActivationCallback,
    public NiControllerSequence::TextKeyCallback
{
public:
    typedef unsigned int SequenceID;

    // Deprecated typedef.
    typedef SequenceID EventCode;

    class NIANIMATION_ENTRY CallbackObject
    {
    public:
        // Virtual destructor defined in case derived classes need virtual
        // destruction.
        virtual ~CallbackObject() {};
        virtual void AnimActivated(NiActorManager* pkManager,
            SequenceID eSequenceID,
            NiControllerSequence* pkSeq,
            float fEventTime) = 0;
        virtual void AnimDeactivated(NiActorManager* pkManager,
            SequenceID eSequenceID,
            NiControllerSequence* pkSeq,
            float fEventTime) = 0;
        virtual void AnimCompleted(NiActorManager* pkManager,
            SequenceID eSequenceID,
            NiControllerSequence* pkSeq,
            float fEventTime) = 0;
        virtual void TextKeyEvent(NiActorManager* pkManager,
            SequenceID eSequenceID,
            const NiFixedString& kTextKey,
            const NiTextKeyMatch* pkMatchObject,
            NiControllerSequence* pkSeq,
            float fEventTime) = 0;
        virtual void EndOfSequence(NiActorManager* pkManager,
            SequenceID eSequenceID,
            NiControllerSequence* pkSeq,
            float fEventTime) = 0;
    };

    enum EventType
    {
        ANIM_ACTIVATED,
        ANIM_DEACTIVATED,
        ANIM_COMPLETED,
        TEXT_KEY_EVENT,
        END_OF_SEQUENCE
    };

    enum TransitionState
    {
        NO_TRANSITION,
        BLENDING,
        MORPHING,
        CROSSFADING
    };

    // Static constants.
    static const SequenceID ANY_SEQUENCE_ID;
    static const SequenceID INVALID_SEQUENCE_ID;
    static const float INVALID_TIME;
    static const float SEQUENCE_DATA_FREQUENCY;

    // Deprecated static constants.
    static const SequenceID ANY_EVENT_CODE;
    static const SequenceID INVALID_EVENT_CODE;

    // Static creation functions.
    static NiActorManager* Create(const char* pcKFMFilename,
        bool bCumulativeAnimations = false, bool bLoadFilesFromDisk = true,
        NiStream* pkStream = NULL, NiPoseBinding* pkPoseBinding = NULL);
    static NiActorManager* Create(NiKFMTool* pkKFMTool,
        const char* pcKFMFilePath, bool bCumulativeAnimations = false,
        bool bLoadFilesFromDisk = true, NiStream* pkStream = NULL,
        NiPoseBinding* pkPoseBinding = NULL);

    // Destructor.
    ~NiActorManager();

    // Cloning function. Creates a clone of the NiActorManager and all of
    // its contents.
    NiActorManager* Clone(NiCloningProcess* pkCloningProcess = NULL);

    // Reloads the NIF file using the info in the NiKFMTool class.
    // If bLoadNIFFile is false, the NIF root will be loaded directly from
    // pkStream without loading a NIF file. pkStream cannot be NULL if
    // bLoadNIFFile is false.
    bool ReloadNIFFile(NiStream* pkStream = NULL, bool bLoadNIFFile = true,
        NiPoseBinding* pkPoseBinding = NULL);

    // Reloads a single KF file from disk.
    bool ReloadKFFile(const char* pcFile);

    // Changes the NIF root and actor root that are being used for the
    // NiActorManager. This function does the same thing as ReloadNIFFile but
    // does not require the root objects to reside in an NiStream object or
    // to be loaded from disk.
    bool ChangeNIFRoot(NiAVObject* pkNIFRoot,
        NiPoseBinding* pkPoseBinding = NULL);

    // Loads the specified sequence data using the info in the
    // NiKFMTool class. If bLoadKFFile is false, the sequence data
    // will be loaded directly from pkStream without loading a KF file.
    // pkStream cannot be NULL if bLoadKFFile is false.
    bool LoadSequenceData(SequenceID eSequenceID, bool bLoadKFFile = true,
        NiStream* pkStream = NULL);

    // Loads all the sequence datas in the NiKFMTool class.
    // If pkStream is NULL this function creates and deletes its own
    // stream, otherwise it uses the given stream.
    bool LoadAllSequenceData(NiStream* pkStream = NULL);

    // Changes the NiSequenceData object that is used for the specified
    // SequenceID. This function does the same thing as LoadSequenceData
    // but does not require the NiSequenceData object to reside in
    // an NiStream object or to be loaded from disk.
    bool ChangeSequenceData(SequenceID eSequenceID,
        NiSequenceData* pkSeqData);

    // Unloads the specified sequence data from the actor manager, removing
    // it from the NiControllerManager in the process. If there is no other
    // smart pointer referencing this sequence data, it will be deleted.
    void UnloadSequenceData(SequenceID eSequenceID);

    // Update function. Must be called with the current time periodically to
    // update the state machine.
    void Update(float fTime);
    inline float GetLastUpdateTime() const;

    // Functions for setting/getting the next target animation.
    SequenceID GetTargetAnimation() const;
    inline bool SetTargetAnimation(SequenceID eSequenceID);
    inline void Reset();

    // Functions for getting the current state of the actor manager.
    SequenceID GetCurAnimation() const;
    TransitionState GetTransitionState() const;
    SequenceID GetNextAnimation() const;

    // Functions for setting/getting the callback object.
    inline void SetCallbackObject(CallbackObject* pkCallbackObject);
    CallbackObject* GetCallbackObject() const;

    // Gets the root of the NIF file that was loaded.
    inline NiAVObject* GetNIFRoot() const;

    // Gets the actor root (the target of the NiControllerManager).
    inline NiAVObject* GetActorRoot() const;

    // Accessor functions.
    inline NiKFMTool* GetKFMTool() const;
    inline NiControllerManager* GetControllerManager() const;
    inline NiSkinningLODController* GetSkinningLODController() const;
    inline NiSequenceData* GetSequenceData(SequenceID eSequenceID) const;

    // Returns the first active sequence assigned to eSequenceID.
    NiControllerSequence* GetActiveSequence(SequenceID eSequenceID,
        bool bCheckExtraSequences, bool bCheckStateSequences) const;

    // Returns the ID of the specified sequence.
    SequenceID GetSequenceID(NiControllerSequence* pkSequence,
        bool bCheckExtraSequences, bool bCheckStateSequences) const;

    // Gets the accumulation root of the actor, if there is one.
    inline NiAVObject* GetAccumRoot() const;

    // Finds the SequenceID for the first found sequence data with a given
    // name.  Returns INVALID_SEQUENCE_ID if the name is not found.
    // pcName must be non-NULL.
    SequenceID FindSequenceID(const char* pcName) const;

    // Functions for registering and unregistering callback events to occur
    // within some advance notification time.
    bool RegisterCallback(EventType eEventType, SequenceID eSequenceID,
        const NiFixedString& kTextKey);
    void UnregisterCallback(EventType eEventType, SequenceID eSequenceID,
        const NiFixedString& kTextKey);
    bool RegisterCallback(EventType eEventType, SequenceID eSequenceID,
        NiTextKeyMatch* pkMatchObject = NULL);
    void UnregisterCallback(EventType eEventType, SequenceID eSequenceID,
        NiTextKeyMatch* pkMatchObject = NULL);
    inline void ClearAllRegisteredCallbacks();

    // Copy registered callbacks from an existing actor manager into this one.
    // This will destroy all existing callbacks.
    void CopyCallbacks(NiActorManager* pkSource);

    // Gets the time of the next event. If the next time cannot be predicted,
    // INVALID_TIME is returned.
    inline float GetNextEventTime(EventType eEventType,
        SequenceID eSequenceID, const NiFixedString& kTextKey);
    inline float GetNextEventTime(EventType eEventType,
        SequenceID eSequenceID, NiTextKeyMatch* pkMatchObject = NULL);

    // Activate a sequence separately from the internal state machine. This
    // is useful for layering animations on top of a base animation that is
    // controlled by the state machine. The newly activated sequence is
    // returned. Callbacks are available for these animations.
    NiControllerSequence* ActivateSequence(SequenceID eSequenceID,
        int iPriority = 0, float fWeight = 1.0f, float fEaseInTime = 0.0f,
        SequenceID eTimeSyncSeqID = NiKFMTool::SYNC_SEQUENCE_ID_NONE,
        float fFrequency = SEQUENCE_DATA_FREQUENCY,
        float fStartFrame = 0.0f,
        bool bAdditiveBlend = false,
        float fAdditiveRefFrame = 0.0f);

    // Deactivates an extra sequence.  Returns false if the sequence could not
    // be found or if the sequence was already inactive.  fEaseOutTime
    // specifies the amount of time for a fully active sequence to deactivate.
    bool DeactivateSequence(SequenceID eSequenceID,
        float fEaseOutTime = 0.0f);

    bool IsPaused() const;
    void SetPaused(bool bIsPaused);

    // Refreshes the NiActorManager's internal pointer to its
    // NiControllerManager. This function is useful if you have
    // programmatically changed the NiControllerManager that the actor
    // manager is using and need the NiActorManager to reflect that change.
    inline void RefreshControllerManager();

    // *** begin Emergent internal use only ***

    // Specialized clone mechanism for cloning just animation data and not the scene graph the
    // animation uses.  This function copies the accumulation settings of the given
    // actor manager.
    NiActorManager* CloneOnlyAnimation(NiAVObject* pkAVObject);

    // Specialized clone mechanism for cloning just animation data and not the scene graph the
    // animation uses.  This function uses an explicit accumulation settings.
    NiActorManager* CloneOnlyAnimation(NiAVObject* pkAVObject, bool bCumulativeAnimation);

    // Override for NiSequenceData::ActivationCallback
    virtual void ActivationChanged(NiControllerSequence* pkSequence,
        NiAnimState eState);

    // Override for NiControllerSequence::TextKeyCallback
    virtual void TextKeyEvent(NiControllerSequence* pkSequence,
        const NiTextKeyMatch* pkMatchObject,
        const NiFixedString& kTextKey,
        float fEventTime);

    NiKFMTool::KFM_RC ChangeSequenceID(SequenceID eOldID, SequenceID eNewID);

    class ChainCompletionInfo : public NiRefObject
    {
    public:
        ChainCompletionInfo();
        ~ChainCompletionInfo();

        inline void SetName(const NiFixedString& kName);
        inline void SetNextName(const NiFixedString& kNextName);

        float m_fSeqStart;
        float m_fTransStart;
        float m_fTransEnd;
        float m_fInSeqBeginFrame;
        NiFixedString m_kName;
        NiFixedString m_kNextName;
        NiKFMTool::Transition* m_pkTransition;
        unsigned int m_uiSrcID;
        unsigned int m_uiDesID;
    };
    typedef efd::SmartPointer<ChainCompletionInfo> ChainCompletionInfoPtr;
    typedef NiTObjectSet<ChainCompletionInfoPtr> ChainCompletionInfoPtrSet;

    class CompletionInfo : public NiRefObject
    {
    public:
        float m_fFrameInDestWhenTransitionCompletes;
        float m_fTimeToCompleteTransition;
        float m_fFrameTransitionOccursInSrc;
        float m_fTimeForChainToComplete;
        NiKFMTool::Transition::BlendPair* m_pkBlendPair;
        ChainCompletionInfoPtrSet m_kChainCompletionInfoSet;
    };
    typedef efd::SmartPointer<CompletionInfo> CompletionInfoPtr;

    class CallbackData : public NiRefObject
    {
    public:
        CallbackData(EventType eEventType, SequenceID eSequenceID,
            NiTextKeyMatch * pkMatchObject = NULL);
        ~CallbackData();

        EventType m_eEventType;
        SequenceID m_eSequenceID;

        NiTextKeyMatchPtr GetMatchObject() const;
        inline void SetMatchObject(NiTextKeyMatch * pkMatchObject);

    protected:
        NiTextKeyMatchPtr m_spMatchObject;
    };
    typedef efd::SmartPointer<CallbackData> CallbackDataPtr;

    bool FindTimeForAnimationToCompleteTransition(
        unsigned int uiTransSrcID, unsigned int uiTransDesID,
        NiKFMTool::Transition* pkTransition, float fBeginSQTime,
        float fDesiredTransitionSQTime, CompletionInfo* pkInfoOut);

    bool AddSequenceData(SequenceID eSequenceID, NiStream& kStream,
        bool bLoadKFFile);

    // *** end Emergent internal use only ***

protected:

    ChainCompletionInfo* FillChainComplete(unsigned int uiSrcID,
        unsigned int uiDesID, float fDuration,
        float& fSrcBeginFrame, float& fTotalTime);

    NiActorManager(NiKFMTool* pkKFMTool, bool bCumulativeAnimations);

    bool Initialize(NiStream& kStream, NiPoseBinding* pkPoseBinding);
    bool LoadNIFFile(NiStream& kStream, bool bLoadNIFFile,
        NiPoseBinding* pkPoseBinding);

    float GetNextAnimActivatedTime(SequenceID eSequenceID);
    float GetNextAnimDeactivatedTime(SequenceID eSequenceID);
    float GetNextTextKeyEventTime(SequenceID eSequenceID,
        NiTextKeyMatch* pkMatchObject);
    float GetNextTextKeyEventTime(SequenceID eSequenceID,
        const NiFixedString& kTextKey);

    inline float GetNextEndOfSequenceTime(SequenceID eSequenceID);

    void ProcessExtraSeqCallbacks(float fEndTime);
    void RaiseAnimActivatedEvents(SequenceID eSequenceID,
        NiControllerSequence* pkSeq, float fEventTime);
    void RaiseAnimDeactivatedEvents(SequenceID eSequenceID,
        NiControllerSequence* pkSeq, float fEventTime);
    void RaiseAnimCompletedEvents(SequenceID eSequenceID,
        NiControllerSequence* pkSeq, float fEventTime);

    void AddCallbacks(SequenceID eSeqID, NiControllerSequence* pkSeq);

    // Adds callback data to all relevant sequences.
    bool InitCallback(CallbackData* pCallback);

    NiKFMTool::Transition::BlendPair* GetNextBlendPair(
        unsigned int uiTransSrcID, unsigned int uiTransDesID,
        NiKFMTool::Transition* pkTransition, float fFrameTime,
        float& fActualUnboundedFrame);

    NiControllerSequence* GetExtraSequence(SequenceID eSequenceID) const;
    void RemoveInactiveExtraSequences();
    NiKFMToolPtr m_spKFMTool;
    NiAVObjectPtr m_spNIFRoot;
    NiControllerManagerPtr m_spManager;

    CallbackObject* m_pkCallbackObject;

    SequenceID m_eTargetID;
    float m_fTime;
    float m_fPauseTime;

    bool m_bStartTransition;
    TransitionState m_eTransitionState;
    float m_fTransStartTime;
    float m_fTransEndTime;
    float m_fTransStartFrameTime;
    const char* m_pcTargetKey;
    SequenceID m_eCurID;
    NiControllerSequencePtr m_spCurSequence;
    SequenceID m_eNextID;
    NiSequenceDataPtr m_spNextSeqData;
    NiControllerSequencePtr m_spNextSequence;
    float m_fNextChainTime;
    NiTPointerList<unsigned int> m_kChainIDs;
    NiTPointerList<float> m_kChainDurations;
    bool m_bChainActive;

    bool m_bCumulativeAnimationsRequested;

    NiTPointerMap<SequenceID, NiSequenceDataPtr> m_kSeqDataMap;

    NiTObjectArray<CallbackDataPtr> m_kCallbacks;

    // Allow just one active extra sequence per ID.
    NiTPointerMap<SequenceID, NiControllerSequencePtr> m_kExtraSequenceMap;
};

NiSmartPointer(NiActorManager);

#include "NiActorManager.inl"

#endif  // #ifndef NIACTORMANAGER_H
