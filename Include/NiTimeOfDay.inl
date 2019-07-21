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

#include "NiTimeOfDay.h"

#include "NiAnimation.h"

//--------------------------------------------------------------------------------------------------
inline void NiTimeOfDay::Start(float fTime)
{
    SetTime(fTime);
    SetActive(true);
}

//--------------------------------------------------------------------------------------------------
inline void NiTimeOfDay::SetActive(bool bActive)
{
    m_bActive = bActive;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTimeOfDay::GetActive() const
{
    return m_bActive;
}

//--------------------------------------------------------------------------------------------------
inline void NiTimeOfDay::SetTime(float fTime)
{
    m_fScaledTime = fTime;
    UpdateControllers(fTime);
}

//--------------------------------------------------------------------------------------------------
inline float NiTimeOfDay::GetTime() const
{
    return m_fScaledTime;
}

//--------------------------------------------------------------------------------------------------
inline float NiTimeOfDay::GetDuration() const
{
    return m_fDuration;
}

//--------------------------------------------------------------------------------------------------
inline void NiTimeOfDay::SetDuration(float fDuration)
{
    m_fDuration = fDuration;
}

//--------------------------------------------------------------------------------------------------
inline void NiTimeOfDay::SetTimeMultiplier(float fScale)
{
    m_fTimeMultiplier = fScale;
}

//--------------------------------------------------------------------------------------------------
inline float NiTimeOfDay::GetTimeMultiplier() const
{
    return m_fTimeMultiplier;
}

//--------------------------------------------------------------------------------------------------
template <typename Value> inline NiTimeOfDay::PropertyType NiTimeOfDay::GetPropertyTypeFromType()
{
    return TODPT_UNKNOWN;
}

//--------------------------------------------------------------------------------------------------
template <> inline NiTimeOfDay::PropertyType NiTimeOfDay::GetPropertyTypeFromType<float>()
{
    return TODPT_FLOAT;
}

//--------------------------------------------------------------------------------------------------
template <> inline NiTimeOfDay::PropertyType NiTimeOfDay::GetPropertyTypeFromType<NiColorA>()
{
    return TODPT_COLOR;
}

//--------------------------------------------------------------------------------------------------
template <class T, typename V> inline bool NiTimeOfDay::BindProperty(
    const NiFixedString& kPropertyName, 
    const T& kTarget)
{
    // Check if we already have a property created
    Property* pkProperty = GetProperty(kPropertyName);
    PropertyType kType = GetPropertyTypeFromType<V>();
    if (pkProperty)
    {
        // Check that the type is correct:
        EE_ASSERT(pkProperty->m_kType == kType);
        // Make sure the property is not bound already
        EE_ASSERT(pkProperty->m_spController == NULL);
    }
    else
    {
        // Create the property
        pkProperty = AddProperty(kPropertyName, kType);
    }

    // Create the controller
    typedef NiTTimeOfDayController<T, V> ControllerType;    
    ControllerType* pkController = NiNew ControllerType(kTarget);
    pkProperty->m_spController = pkController;

    // Bind the controller to the animation sequence:
    if (pkProperty->m_spInterpolator)
        SetInterpolator(pkProperty, pkProperty->m_spInterpolator);

    return true;
}

//--------------------------------------------------------------------------------------------------
template <typename Value> inline NiTimeOfDay::TSequenceBuilder<Value>::TSequenceBuilder(
    NiUInt32 uiNumKeys) :
    m_uiNumKeys(uiNumKeys),
    m_pkKeyValues(NULL),
    m_pkKeyTimes(NULL)
{
    m_pkKeyValues = NiAlloc(Value, uiNumKeys);
    m_pkKeyTimes = NiAlloc(float, uiNumKeys);
}

//--------------------------------------------------------------------------------------------------
template <typename Value> inline NiTimeOfDay::TSequenceBuilder<Value>::~TSequenceBuilder()
{
    if (m_pkKeyValues)
        NiFree(m_pkKeyValues);

    if (m_pkKeyTimes)
        NiFree(m_pkKeyTimes);
}

//--------------------------------------------------------------------------------------------------
template <typename Value> inline void NiTimeOfDay::TSequenceBuilder<Value>::SetKey(
    NiUInt32 uiKeyID, 
    float fTime, 
    efd::TiXmlElement* pkElement)
{
    Value kValue;
    efd::ParseHelper<Value>::FromString(pkElement->GetText(), kValue);

    EE_ASSERT(uiKeyID < m_uiNumKeys);
    m_pkKeyValues[uiKeyID] = kValue;
    m_pkKeyTimes[uiKeyID] = fTime;
}

//--------------------------------------------------------------------------------------------------
template <typename Value> inline void NiTimeOfDay::TSequenceBuilder<Value>::SetKey(
    NiUInt32 uiKeyID, 
    float fTime, 
    efd::utf8string kValueAsString)
{
    Value kValue;
    efd::ParseHelper<Value>::FromString(kValueAsString, kValue);
    
    EE_ASSERT(uiKeyID < m_uiNumKeys);
    m_pkKeyValues[uiKeyID] = kValue;
    m_pkKeyTimes[uiKeyID] = fTime;
}

//--------------------------------------------------------------------------------------------------
template <typename Value> inline 
    NiInterpolator* NiTimeOfDay::TSequenceBuilder<Value>::FinaliseSequence(float fEndTime)
{
    return NULL;
}

//--------------------------------------------------------------------------------------------------
template <> inline
    NiInterpolator* NiTimeOfDay::TSequenceBuilder<efd::Float32>::FinaliseSequence(float fEndTime)
{
    typedef float ValueType;
    typedef NiLinFloatKey KeyType;
    typedef NiFloatData AnimationDataType;
    typedef NiFloatInterpolator InterpolatorType;
    const NiAnimationKey::KeyType eInterpolationType = NiAnimationKey::LINKEY;

    // Create an interpolator of the appropriate type
    InterpolatorType* pkInterpolator = NiNew InterpolatorType();
    
    float fMaxTime = m_pkKeyTimes[m_uiNumKeys-1];
    float fMinTime = m_pkKeyTimes[0];

    NiUInt32 uiRequiredKeys = m_uiNumKeys;
    if (fMaxTime < fEndTime)
        uiRequiredKeys++;
    if (fMinTime > 0.0f)
        uiRequiredKeys++;

    if (uiRequiredKeys != m_uiNumKeys)
    {
        float* pkKeyTimes = NiAlloc(float, uiRequiredKeys);
        ValueType* pkKeyValues = NiAlloc(ValueType, uiRequiredKeys);

        // Calculate intermediate value at the end (and the beginning) of the 
        // sequence
        KeyType kTempKeys[2];

        kTempKeys[0].SetValue(m_pkKeyValues[m_uiNumKeys-1]);
        kTempKeys[0].SetTime(m_pkKeyTimes[m_uiNumKeys-1]);

        kTempKeys[1].SetValue(m_pkKeyValues[0]);
        kTempKeys[1].SetTime(fEndTime + m_pkKeyTimes[0]);

        EE_ASSERT(fEndTime <= kTempKeys[1].GetTime());
        float fNormalisedTime = fEndTime / kTempKeys[1].GetTime();
        ValueType kInterpValue;

        NiAnimationKey::InterpFunction InterpFunction = 
            KeyType::GetInterpFunction(eInterpolationType);
        InterpFunction(fNormalisedTime, &kTempKeys[0], &kTempKeys[1], 
            &kInterpValue); 

        NiUInt32 uiCurrentKey = 0;

        // New Beginning Keyframe?
        if (fMinTime > 0.0f)
        {
            pkKeyTimes[uiCurrentKey] = 0.0f;
            pkKeyValues[uiCurrentKey] = kInterpValue;
            uiCurrentKey++;
        }

        // Copy user input values
        for (NiUInt32 ui = 0; ui < m_uiNumKeys; ++ui)
        {
            pkKeyTimes[uiCurrentKey] = m_pkKeyTimes[ui];
            pkKeyValues[uiCurrentKey] = m_pkKeyValues[ui];
            uiCurrentKey++;
        }

        // New end keyframe?
        if (fMaxTime < fEndTime)
        {
            pkKeyTimes[uiCurrentKey] = fEndTime;
            pkKeyValues[uiCurrentKey] = kInterpValue;
        }

        NiFree(m_pkKeyTimes);
        NiFree(m_pkKeyValues);
        m_pkKeyTimes = pkKeyTimes;
        m_pkKeyValues = pkKeyValues;
        m_uiNumKeys = uiRequiredKeys;
    }
    
    // Generate the final animation sequence
    KeyType* pkKeys = NiNew KeyType[m_uiNumKeys];
    
    for (NiUInt32 uiIndex = 0; uiIndex < m_uiNumKeys; ++uiIndex)
    {
        pkKeys[uiIndex].SetTime(m_pkKeyTimes[uiIndex]);
        pkKeys[uiIndex].SetValue(m_pkKeyValues[uiIndex]);
    }

    AnimationDataType* pkAnimationData = NiNew AnimationDataType();
    pkAnimationData->SetAnim(pkKeys, m_uiNumKeys, eInterpolationType);

    // Formalise the animation on the interpolator
    pkInterpolator->SetFloatData(pkAnimationData);

    return pkInterpolator;
}

//--------------------------------------------------------------------------------------------------
template <> inline
NiInterpolator* NiTimeOfDay::TSequenceBuilder<efd::ColorA>::FinaliseSequence(float fEndTime)
{
    typedef NiColorA ValueType;
    typedef NiLinColorKey KeyType;
    typedef NiColorData AnimationDataType;
    typedef NiColorInterpolator InterpolatorType;
    const NiAnimationKey::KeyType eInterpolationType = NiAnimationKey::LINKEY;

    // Create an interpolator to use
    InterpolatorType* pkInterpolator = NiNew InterpolatorType();

    float fMaxTime = m_pkKeyTimes[m_uiNumKeys-1];
    float fMinTime = m_pkKeyTimes[0];

    NiUInt32 uiRequiredKeys = m_uiNumKeys;
    if (fMaxTime < fEndTime)
        uiRequiredKeys++;
    if (fMinTime > 0.0f)
        uiRequiredKeys++;

    if (uiRequiredKeys != m_uiNumKeys)
    {
        float* pkKeyTimes = NiAlloc(float, uiRequiredKeys);
        ValueType* pkKeyValues = NiAlloc(ValueType, uiRequiredKeys);

        // Calculate intermediate value at the end (and the beginning) of the 
        // sequence
        KeyType kTempKeys[2];

        kTempKeys[0].SetColor(m_pkKeyValues[m_uiNumKeys-1]);
        kTempKeys[0].SetTime(m_pkKeyTimes[m_uiNumKeys-1]);

        kTempKeys[1].SetColor(m_pkKeyValues[0]);
        kTempKeys[1].SetTime(fEndTime + m_pkKeyTimes[0]);

        EE_ASSERT(fEndTime <= kTempKeys[1].GetTime());
        float fNormalisedTime = fEndTime / kTempKeys[1].GetTime();
        ValueType kInterpValue;

        NiAnimationKey::InterpFunction pfnInterpFunction = 
            KeyType::GetInterpFunction(eInterpolationType);
        pfnInterpFunction(fNormalisedTime, &kTempKeys[0], &kTempKeys[1], 
            &kInterpValue); 

        NiUInt32 uiCurrentKey = 0;

        // New Beginning Keyframe?
        if (fMinTime > 0.0f)
        {
            pkKeyTimes[uiCurrentKey] = 0.0f;
            pkKeyValues[uiCurrentKey] = kInterpValue;
            uiCurrentKey++;
        }

        // Copy user input values
        for (NiUInt32 ui = 0; ui < m_uiNumKeys; ++ui)
        {
            pkKeyTimes[uiCurrentKey] = m_pkKeyTimes[ui];
            pkKeyValues[uiCurrentKey] = m_pkKeyValues[ui];
            uiCurrentKey++;
        }

        // New end keyframe?
        if (fMaxTime < fEndTime)
        {
            pkKeyTimes[uiCurrentKey] = fEndTime;
            pkKeyValues[uiCurrentKey] = kInterpValue;
        }

        NiFree(m_pkKeyTimes);
        NiFree(m_pkKeyValues);
        m_pkKeyTimes = pkKeyTimes;
        m_pkKeyValues = pkKeyValues;
        m_uiNumKeys = uiRequiredKeys;
    }

    // Generate the final animation sequence
    KeyType* pkKeys = NiNew KeyType[m_uiNumKeys];

    for (NiUInt32 uiIndex = 0; uiIndex < m_uiNumKeys; ++uiIndex)
    {
        pkKeys[uiIndex].SetTime(m_pkKeyTimes[uiIndex]);
        pkKeys[uiIndex].SetColor(m_pkKeyValues[uiIndex]);
    }

    AnimationDataType* pkAnimationData = NiNew AnimationDataType();
    pkAnimationData->SetAnim(pkKeys, m_uiNumKeys, eInterpolationType);

    // Formalise the animation on the interpolator
    pkInterpolator->SetColorData(pkAnimationData);

    return pkInterpolator;
}

//--------------------------------------------------------------------------------------------------