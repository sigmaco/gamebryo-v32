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
#ifndef NICONTROLLERSEQUENCE_H
#define NICONTROLLERSEQUENCE_H

#include <NiObject.h>
#include "NiAnimationLibType.h"
#include "NiAnimState.h"
#include "NiTextKeyMatch.h"
#include "NiPoseBuffer.h"
#include "NiSequenceData.h"
#include "NiScratchPad.h"

class NiControllerManager;

NiSmartPointer(NiControllerSequence);
typedef NiTObjectArray<NiControllerSequencePtr>
    NiControllerSequencePointerArray;


class NIANIMATION_ENTRY NiControllerSequence : public NiObject
{
public:
    NiDeclareRTTI;

public:
    static const float INVALID_TIME;
    static const float CURRENT_FRAME;
    static const float SEQUENCE_DATA_FREQUENCY;

    // Destructor.
    ~NiControllerSequence();

    // Functions for getting the sequence name.
    inline const NiFixedString& GetName() const;

    // Function that returns a "unique" ID for differentiating between
    // different instances of a recycled sequence.
    inline unsigned int GetActivationID() const;

    // Functions to get associated objects
    inline NiSequenceData* GetSequenceData() const;
    inline NiTextKeyExtraData* GetTextKeys() const;
    inline NiControllerSequence* GetTimeSyncSequence() const;
    inline NiPoseBuffer* GetPoseBuffer() const;
    inline NiScratchPad* GetScratchPad() const;

    // Function to reset the sequence to the beginning.
    inline void ResetSequence();

    // Function that returns the animation state for this sequence.
    inline NiAnimState GetState() const;

    // Functions for querying whether the sequence is additively blending.
    inline bool IsAdditiveBlend() const;
    inline NiPoseBuffer* GetAdditiveRefFrame() const;

    // Functions for getting and setting the offset for this sequence.
    inline float GetOffset() const;
    inline void SetOffset(float fOffset);

    // Functions for getting and setting the sequence priority and weight.
    inline int GetPriority() const;
    inline float GetWeight() const;
    inline void SetWeight(float fWeight);

    // Functions for getting and setting timing information.
    inline float GetDuration() const;
    inline float GetDurationDivFreq() const;
    inline NiTimeController::CycleType GetCycleType() const;
    inline bool SetCycleType(NiTimeController::CycleType eType);
    inline float GetFrequency() const;
    inline void SetFrequency(float fFrequency);

    // Functions to adjust time by frequency of sequence.
    inline float TimeDivFreq(float fTime) const;
    inline float TimeMultFreq(float fTime) const;

    // Functions to provide easy access to the last stored time values.
    inline float GetLastTime() const;
    inline float GetLastScaledTime() const;

    // Function for looking up the time of a text key.
    inline float GetTimeAt(const NiFixedString& kTextKey, float fCurrentTime = 0.0f);
    float GetTimeAt(NiTextKeyMatch* pkMatchObject, float fCurrentTime = 0.0f);

    // Function for looking up the key time for a particular text key.
    inline float GetKeyTimeAt(const NiFixedString& kTextKey) const;
    float GetKeyTimeAt(NiTextKeyMatch* pkMatchObject) const;

    // Functions dealing with evaluators.
    inline unsigned int GetNumEvaluators() const;
    inline NiEvaluator* GetEvaluatorAt(unsigned int uiIndex) const;
    void DisableEvaluatorAt(unsigned int uiIndex, bool bInvalidatePBData);
    void DisableEvaluatorChannelAt(unsigned int uiEvaluatorIndex,
        unsigned int uiChannelIndex, bool bInvalidatePBData);

    // Functions related to callback objects.
    // Initialized to default list in NiSequenceData upon activation.
    inline void AddActivationCallback(
        NiSequenceData::ActivationCallback* pkCallback);
    inline void RemoveActivationCallback(
        NiSequenceData::ActivationCallback* pkCallback);
    inline unsigned int GetActivationCallbackCount() const;
    inline NiSequenceData::ActivationCallback* GetActivationCallbackAt(
        unsigned int uiIndex);

    // Unpause the sequence at fTime.  This will make it appear from
    // the sequence's point of view that no time has passed since
    // the last update until fTime, at which point time will move
    // forward normally again.
    void Unpause(float fTime);

    // *** begin Emergent internal use only ***
    class NIANIMATION_ENTRY TextKeyCallback
    {
    public:
        virtual ~TextKeyCallback() {}
        virtual void TextKeyEvent(NiControllerSequence* pkSequence,
            const NiTextKeyMatch* pkMatchObject,
            const NiFixedString& kTextKey,
            float fEventTime) = 0;
    };
    inline void AddTextKeyCallback(TextKeyCallback* pkCallback,
        NiTextKeyMatch* pkMatchObject);
    inline void RemoveTextKeyCallback(const TextKeyCallback* pkCallback,
        const NiTextKeyMatch* pkMatchObject);
    inline void RemoveTextKeyCallback(const TextKeyCallback* pkCallback,
        const NiFixedString& kTextKey);
    inline unsigned int GetTextKeyCallbackCount() const;

    enum
    {
        LODSKIPEVALUATOR = -2,
        EVALMAXCHANNELS = NiEvaluator::EVALMAXCHANNELS,
    };

    NiControllerSequence();

    // Functions for getting and setting the controller manager on which
    // this active sequence is being played.
    inline NiControllerManager* GetOwner() const;
    inline bool SetOwner(NiControllerManager* pkOwner);

    inline bool SetSequenceData(NiSequenceData* pkSequenceData);

    void Update(float fTime, int iLOD, bool bUpdateEvaluators, bool bThrowTextKeys);

    static NiControllerSequence* Activate(NiControllerManager* pkOwner,
        NiSequenceData* pkSeqData, int iPriority,
        float fWeight, float fEaseInTime,
        NiControllerSequence* pkTimeSyncSeq = NULL,
        float fFrequency = SEQUENCE_DATA_FREQUENCY,
        float fStartFrame = 0.0f,
        bool bTransition = false,
        bool bHoldTransitionFrame = false,
        bool bAdditiveBlend = false,
        float fAdditiveRefFrame = 0.0f);
    bool Reactivate(int iPriority,
        float fWeight, float fEaseInTime,
        NiControllerSequence* pkTimeSyncSeq = NULL,
        float fStartFrame = CURRENT_FRAME,
        bool bTransition = false,
        bool bProcessCallbacks = true);
    // Deactivate a sequence.
    // This will return true if the sequence was deactivated.  It will fail if
    // the sequence was already inactive.  fEaseOutTime specifies the amount
    // of time required for a fully active sequence to deactivate.
    bool Deactivate(float fEaseOutTime,
        bool bTransition = false,
        bool bHoldTransitionFrame = false,
        bool bProcessCallbacks = true);

    inline NiControllerSequence* StartBlend(NiSequenceData* pkDestSeqData,
        float fDuration, const char* pcDestTextKey, int iPriority,
        float fSourceWeight, float fDestWeight,
        NiControllerSequence* pkDestTimeSyncSeq = NULL,
        float fDestFrequency = SEQUENCE_DATA_FREQUENCY);
    NiControllerSequence* StartBlend(NiSequenceData* pkDestSeqData,
        float fDuration, float fDestFrame, int iPriority,
        float fSourceWeight, float fDestWeight,
        NiControllerSequence* pkDestTimeSyncSeq = NULL,
        float fDestFrequency = SEQUENCE_DATA_FREQUENCY);

    NiControllerSequence* StartMorph(NiSequenceData* pkDestSeqData,
        float fDuration, int iPriority, float fSourceWeight,
        float fDestWeight,
        float fDestFrequency = SEQUENCE_DATA_FREQUENCY);

    float FindCorrespondingMorphFrame(NiControllerSequence* pkSourceSequence,
        float fSourceSequenceTime);
    float ComputeScaledTime(float fTime, bool bStoreLastTime = true);

    inline float GetSpinnerScaledWeight() const;
    inline float GetEaseSpinner() const;
    inline float GetEaseEndTime() const;
    inline float GetDestFrame() const;
    inline bool IsMoreImportantThan(const NiControllerSequence* pkSequence) const;

    void PrepareForRecycling();

    inline void SetLastAccumTransform(const NiQuatTransform& kTransform);
    inline void ClearAccumTransformData();

    NIANIMATION_ENTRY struct TextKeyCallbackData : public NiMemObject
    {
        inline TextKeyCallbackData(int iUnused = 0);
        inline bool operator ==(const TextKeyCallbackData& kRHS) const;
        inline bool operator !=(const TextKeyCallbackData& kRHS) const;

        TextKeyCallback* m_pkCallback;
        NiTextKeyMatchPtr m_spMatch;
    };
    // *** end Emergent internal use only ***

protected:
    inline bool VerifyDependencies(NiControllerSequence* pkSequence);
    bool VerifyMatchingMorphKeys(NiControllerSequence* pkTimeSyncSeq);

    void ThrowAllTextKeys(float fLastTime, float fTime,
        float fLastScaledTime, float fScaledTime,
        float fLastWeightedTime, float fWeightedTime);
    void ThrowTextKeysBetween(float fLastTime, float fTime,
        float fLastScaledTime, float fScaledTime,
        float fFrameDuration, bool bIncludeFirst);

    // Commits an update.  Sets new times, throws text keys,
    // updates evaluators.
    void DoUpdate(float fTime, int iLOD, bool bUpdateEvaluators,
        bool bThrowTextKeys);

    // ID to differentiate between different instances of a recycled sequence.
    unsigned int m_uiActivationID;

    // The controller manager that owns this sequence.
    NiControllerManager* m_pkOwner;

    // The buffer to which the animated pose is written on each update call.
    NiPoseBufferPtr m_spPoseBuffer;
    unsigned short m_usNumPoseBufferItems;
    short m_sLastPoseBufferUpdateLOD;
    float m_fLastPoseBufferUpdateTime;

    // The scratch pad which holds instance data for the evaluators.
    NiScratchPadPtr m_spScratchPad;

    // The shared sequence data containing the source animation content.
    NiSequenceDataPtr m_spSeqData;

    // Text keys which point to times in the animation.
    NiTextKeyExtraDataPtr m_spTextKeys;

    // Priority and weights of the sequence.
    int m_iPriority;
    float m_fWeight;
    float m_fTransSpinner;
    float m_fEaseSpinner;

    // Timing variables.
    float m_fDuration;
    NiTimeController::CycleType m_eCycleType;
    float m_fFrequency;
    float m_fLastTime;
    float m_fLastUpdateTime;
    float m_fWeightedLastTime;
    float m_fLastScaledTime;

    // The current state of the sequence.
    NiAnimState m_eState;

    // Variables used for time measurement.
    float m_fOffset;
    float m_fStartTime;
    float m_fEndTime;
    float m_fDestFrame;
    bool m_bHoldDestFrame;
    bool m_bNeedFirstTextKey;

    // If additively blending, this is valid.
    NiPoseBufferPtr m_spAdditiveRefFrame;

    // Variables used for time synchronization.
    NiControllerSequencePtr m_spPartnerSequence;

    // Callback objects.
    NiTPrimitiveArray<NiSequenceData::ActivationCallback*>
        m_kActivationCallbacks;

    NiTObjectArray<TextKeyCallbackData> m_kTextKeyCallbacks;
};

#include "NiControllerSequence.inl"

#endif  // #ifndef NICONTROLLERSEQUENCE_H
