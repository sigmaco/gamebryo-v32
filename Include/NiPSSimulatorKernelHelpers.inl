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

#include "NiPSFlagsHelpers.h"
#include <NiOS.h>
#include <NiMath.h>

//--------------------------------------------------------------------------------------------------
EE_FORCEINLINE void NiPSSimulatorKernelHelpers::UpdateParticlePosition(
    NiPoint3& kOPosition,
    const NiPoint3& kIPosition,
    const NiPoint3& kIVelocity,
    const float fILastUpdate,
    const float fCurrentTime)
{
    kOPosition = kIPosition + (kIVelocity * (fCurrentTime - fILastUpdate));
}

//--------------------------------------------------------------------------------------------------
EE_FORCEINLINE void NiPSSimulatorKernelHelpers::UpdateParticleSize(float& fOSize,
    const NiUInt16 usIGeneration, const float fIAge, const float fILifeSpan, const float fGrowTime,
    const float fShrinkTime, const NiUInt16 usGrowGeneration, const NiUInt16 usShrinkGeneration,
    const NiUInt8 ucNumKeys, const NiPSKernelFloatKey* pkKeys, const NiPSLoopBehavior eLoopBehavior)
{
    float fGrow = 1.0f;
    if (usIGeneration == usGrowGeneration &&
        fIAge < fGrowTime &&
        fGrowTime > 0.0f)
    {
        fGrow = fIAge / fGrowTime;
    }

    float fShrink = 1.0f;
    float fTimeLeft = fILifeSpan - fIAge;
    if (usIGeneration == usShrinkGeneration &&
        fTimeLeft < fShrinkTime &&
        fShrinkTime > 0.0f)
    {
        fShrink = fTimeLeft / fShrinkTime;
    }

    float fGrowShrinkSize = (fShrink > fGrow ? fGrow : fShrink);

    float fKeyedSize = 1.0f;
    if (ucNumKeys == 1)
    {
        fKeyedSize = pkKeys[0].m_fValue;
    }
    else if (ucNumKeys > 1)
    {
        // Compute scaled age (between 0.0 and 1.0).
        const float fFirstTime = pkKeys[0].m_fTime;
        const float fLastTime = pkKeys[ucNumKeys - 1].m_fTime;
        const float fScaledAge =
            ComputeAnimationTime(fIAge, fILifeSpan, eLoopBehavior, fFirstTime, fLastTime);

        // Catch cases where the time is outside the key range.
        if (fScaledAge <= fFirstTime)
        {
            fKeyedSize = pkKeys[0].m_fValue;
        }
        else if (fScaledAge >= fLastTime)
        {
            fKeyedSize = pkKeys[ucNumKeys - 1].m_fValue;
        }
        else
        {
            // Find surrounding values in the keys.
            const NiPSKernelFloatKey* pkPrevKey = pkKeys;
            const NiPSKernelFloatKey* pkNextKey = pkPrevKey;
            for (NiUInt8 uc = 1; uc < ucNumKeys; ++uc)
            {
                pkNextKey = pkKeys + uc;
                if (fScaledAge <= pkNextKey->m_fTime)
                {
                    break;
                }

                pkPrevKey = pkNextKey;
            }

            // Compute normalized time between the keys.
            float fNormTime = (fScaledAge - pkPrevKey->m_fTime) /
                (pkNextKey->m_fTime - pkPrevKey->m_fTime);

            // Linear interpolation only.
            fKeyedSize = (1.0f - fNormTime) * pkPrevKey->m_fValue +
                fNormTime * pkNextKey->m_fValue;
        }
    }

    fOSize = fKeyedSize * fGrowShrinkSize;
    if (fOSize < NIPSKERNEL_EPSILON)
    {
        fOSize = NIPSKERNEL_EPSILON;
    }
}

//--------------------------------------------------------------------------------------------------
EE_FORCEINLINE void NiPSSimulatorKernelHelpers::UpdateParticleColor(NiRGBA& kOColor,
    const NiRGBA& kIColor, const float fIAge, const float fILifeSpan,
    const NiUInt8 ucNumKeys, const NiPSKernelColorKey* pkKeys, const NiPSLoopBehavior eLoopBehavior,
    const NiUInt8 ucBGRA)
{
    if (ucNumKeys == 0)
    {
        kOColor = kIColor;
        return;
    }

    if (ucNumKeys == 1)
    {
        kOColor = pkKeys[0].m_kColor;
        return;
    }

    // Compute scaled age (between 0.0 and 1.0).
    const float fFirstTime = pkKeys[0].m_fTime;
    const float fLastTime = pkKeys[ucNumKeys - 1].m_fTime;
    const float fScaledAge =
        ComputeAnimationTime(fIAge, fILifeSpan, eLoopBehavior, fFirstTime, fLastTime);

    // Catch cases where the time is outside the key range.
    if (fScaledAge <= fFirstTime)
    {
        kOColor = pkKeys[0].m_kColor;
        return;
    }

    if (fScaledAge >= fLastTime)
    {
        kOColor = pkKeys[ucNumKeys - 1].m_kColor;
        return;
    }

    // Find surrounding color values in the color keys.
    const NiPSKernelColorKey* pkPrevKey = pkKeys;
    const NiPSKernelColorKey* pkNextKey = pkPrevKey;
    for (NiUInt8 uc = 1; uc < ucNumKeys; ++uc)
    {
        pkNextKey = pkKeys + uc;
        if (fScaledAge <= pkNextKey->m_fTime)
        {
            break;
        }

        pkPrevKey = pkNextKey;
    }

    // Compute normalized time between the keys.
    float fNormTime = (fScaledAge - pkPrevKey->m_fTime) /
        (pkNextKey->m_fTime - pkPrevKey->m_fTime);

    // Linear interpolation only.
    NiRGBA kColor = (1.0f - fNormTime) * pkPrevKey->m_kColor +
        fNormTime * pkNextKey->m_kColor;

    if (!ucBGRA)
    {
        kOColor = kColor;
    }
    else
    {
        // BGRA
        kOColor.r() = kColor.b();
        kOColor.g() = kColor.g();
        kOColor.b() = kColor.r();
        kOColor.a() = kColor.a();
    }
}

//--------------------------------------------------------------------------------------------------
EE_FORCEINLINE void NiPSSimulatorKernelHelpers::UpdateParticleRotation(float& fORotAngle,
    const float fIRotAngle, const float fIRotSpeed, const float fIAge,
    const float fILifeSpan, const NiUInt8 ucNumKeys, const NiPSKernelFloatKey* pkKeys,
    const NiPSLoopBehavior eLoopBehavior)
{
    // Add in any addition key info
    float fKeyedAngle = 0.0f;
    if (ucNumKeys == 1)
    {
        fKeyedAngle = pkKeys[0].m_fValue;
    }
    else if (ucNumKeys > 1)
    {
        // Compute scaled age (between 0.0 and 1.0).
        const float fFirstTime = pkKeys[0].m_fTime;
        const float fLastTime = pkKeys[ucNumKeys - 1].m_fTime;
        const float fScaledAge =
            ComputeAnimationTime(fIAge, fILifeSpan, eLoopBehavior, fFirstTime, fLastTime);

        // Catch cases where the time is outside the key range.
        if (fScaledAge <= fFirstTime)
        {
            fKeyedAngle = pkKeys[0].m_fValue;
        }
        else if (fScaledAge >= fLastTime)
        {
            fKeyedAngle = pkKeys[ucNumKeys - 1].m_fValue;
        }
        else
        {
            // Find surrounding values in the keys.
            const NiPSKernelFloatKey* pkPrevKey = pkKeys;
            const NiPSKernelFloatKey* pkNextKey = pkPrevKey;
            for (NiUInt8 uc = 1; uc < ucNumKeys; ++uc)
            {
                pkNextKey = pkKeys + uc;
                if (fScaledAge <= pkNextKey->m_fTime)
                {
                    break;
                }

                pkPrevKey = pkNextKey;
            }

            // Compute normalized time between the keys.
            float fNormTime = (fScaledAge - pkPrevKey->m_fTime) /
                (pkNextKey->m_fTime - pkPrevKey->m_fTime);

            // Linear interpolation only.
            fKeyedAngle = (1.0f - fNormTime) * pkPrevKey->m_fValue +
                fNormTime * pkNextKey->m_fValue;
        }
    }

    // Compute updated rotation angle.
    fORotAngle = fIRotAngle + (fIRotSpeed * fIAge) + fKeyedAngle;
}

//--------------------------------------------------------------------------------------------------
EE_FORCEINLINE void NiPSSimulatorKernelHelpers::UpdateParticleAgeDeath(
    float& fOAge,
    float& fOLastUpdateTime,
    NiUInt32& uiOFlags,
    const float fIAge,
    const float fILifeSpan,
    const float fILastUpdateTime,
    const NiUInt32 uiIFlags,
    const float fCurrentTime,
    const bool bSpawnOnDeath,
    const NiUInt16 ucSpawnerID)
{
    // Update age.
    fOAge = fIAge + (fCurrentTime - fILastUpdateTime);

    // Copy last update time.
    fOLastUpdateTime = fILastUpdateTime;

    // Copy particle flags.
    uiOFlags = uiIFlags;

    // Update death.
    if (fOAge > fILifeSpan)
    {
        // Set the particle to be killed.
        NiPSFlagsHelpers::SetShouldDie(uiOFlags, true);

        // Handle spawning.
        if (bSpawnOnDeath)
        {
            // Update fOLastUpdateTime with the time of death. This is used
            // when spawning on death.
            fOLastUpdateTime = fCurrentTime - (fOAge - fILifeSpan);

            // Set the particle to spawn.
            NiPSFlagsHelpers::SetShouldSpawn(uiOFlags, true);
            NiPSFlagsHelpers::SetSpawnerID(uiOFlags, ucSpawnerID);
        }
    }
}

//--------------------------------------------------------------------------------------------------
EE_FORCEINLINE void NiPSSimulatorKernelHelpers::UpdateMeshAlignmentFF(
    float& fOScale, const NiPoint3& kIVelocity, const float fIRadius, const float fISize,
    const float fIScaleAmount, const float fIScaleRest, const float fIScaleLimit)
{
    float fVelocity = kIVelocity.Length();
    float fScale = (fIScaleAmount * fVelocity * fIScaleLimit + fIScaleRest) /
        (fIScaleAmount * fVelocity + 1.0f);
    fOScale = NiMax(fIRadius * fISize * fScale, 0.0f);
}

//--------------------------------------------------------------------------------------------------
EE_FORCEINLINE void NiPSSimulatorKernelHelpers::UpdateMeshAlignmentFFR(
    NiPoint3& kORotCol0, NiPoint3& kORotCol1, NiPoint3& kORotCol2,
    float& fOScale, const NiMatrix3& kIBasis, const NiPoint3& kIVelocity,
    const float fIRadius, const float fISize, const float fIRotAngle, const NiPoint3& fIRotAxis,
    const float fIAge, const float fILifeSpan, const NiUInt8 ucNumKeys,
    const NiPSKernelQuaternionKey* pkKeys, const NiPSLoopBehavior eLoopBehavior,
    const float fIScaleAmount, const float fIScaleRest, const float fIScaleLimit)
{
    NiMatrix3 kSpeedRotate;
    kSpeedRotate.MakeRotation(fIRotAngle, fIRotAxis.x, fIRotAxis.y, fIRotAxis.z);

    //
    // Add in any addition key info
    //
    NiMatrix3 kKeyedRotate;
    if (ucNumKeys == 1)
    {
        pkKeys[0].m_kValue.ToRotation(kKeyedRotate);
    }
    else if (ucNumKeys > 1)
    {
        // Compute scaled age (between 0.0 and 1.0).
        const float fFirstTime = pkKeys[0].m_fTime;
        const float fLastTime = pkKeys[ucNumKeys - 1].m_fTime;
        const float fScaledAge =
            ComputeAnimationTime(fIAge, fILifeSpan, eLoopBehavior, fFirstTime, fLastTime);

        // Catch cases where the time is outside the key range.
        if (fScaledAge <= fFirstTime)
        {
            pkKeys[0].m_kValue.ToRotation(kKeyedRotate);
        }
        else if (fScaledAge >= fLastTime)
        {
            pkKeys[ucNumKeys - 1].m_kValue.ToRotation(kKeyedRotate);
        }
        else
        {
            // Find surrounding values in the keys.
            const NiPSKernelQuaternionKey* pkPrevKey = pkKeys;
            const NiPSKernelQuaternionKey* pkNextKey = pkPrevKey;
            for (NiUInt8 uc = 1; uc < ucNumKeys; ++uc)
            {
                pkNextKey = pkKeys + uc;
                if (fScaledAge <= pkNextKey->m_fTime)
                {
                    break;
                }

                pkPrevKey = pkNextKey;
            }

            // Compute normalized time between the keys.
            float fNormTime = (fScaledAge - pkPrevKey->m_fTime) /
                (pkNextKey->m_fTime - pkPrevKey->m_fTime);

            // Linear interpolation only.
            NiQuaternion kOutput =
                NiQuaternion::Slerp(fNormTime, pkPrevKey->m_kValue, pkNextKey->m_kValue);
            kOutput.ToRotation(kKeyedRotate);
        }
    }
    else
    {
        kKeyedRotate.MakeIdentity();
    }

    NiMatrix3 kRotation = kKeyedRotate * kSpeedRotate * kIBasis;

    kRotation.GetCol(0, kORotCol0);
    kRotation.GetCol(1, kORotCol1);
    kRotation.GetCol(2, kORotCol2);

    float fVelocity = kIVelocity.Length();
    float fScale = (fIScaleAmount * fVelocity * fIScaleLimit + fIScaleRest) /
        (fIScaleAmount * fVelocity + 1.0f);
    fOScale = NiMax(fIRadius * fISize * fScale, 0.0f);
}

//--------------------------------------------------------------------------------------------------
EE_FORCEINLINE void NiPSSimulatorKernelHelpers::UpdateMeshAlignmentVV(
    NiPoint3& kORotCol0, NiPoint3& kORotCol1, NiPoint3& kORotCol2,
    float& fOScale, const NiPoint3& kINormal, const NiPoint3& kIUp,
    const NiPoint3& kIVelocity, const float fIRadius, const float fISize,
    const float fIScaleAmount, const float fIScaleRest, const float fIScaleLimit)
{
    // When kNormal is zero, this code places kUp in kORotCol2 and leaves
    // kORotCol0 and kORotCol1 as zero vector. When kUp is zero, kORotCol0
    // is set to kNormal and the other vectors will be zero. Calling code
    // must detect these invalid rotation matrices and take appropriate action.

    kORotCol0 = kINormal;
    if (kORotCol0.x == 0.0f &&
        kORotCol0.y == 0.0f &&
        kORotCol0.z == 0.0f)
    {
        kORotCol1.x = 0.0f;
        kORotCol1.y = 0.0f;
        kORotCol1.z = 0.0f;

        kORotCol2 = kIUp;
    }
    else
    {
        kORotCol1 = kIUp.UnitCross(kINormal);
        kORotCol2 = kINormal.Cross(kORotCol1);
    }

    float fVelocity = kIVelocity.Length();
    float fScale = (fIScaleAmount * fVelocity * fIScaleLimit + fIScaleRest) /
        (fIScaleAmount * fVelocity + 1.0f);
    fOScale = NiMax(fIRadius * fISize * fScale, 0.0f);
}

//--------------------------------------------------------------------------------------------------
EE_FORCEINLINE void NiPSSimulatorKernelHelpers::UpdateMeshAlignmentVVR(
    NiPoint3& kORotCol0, NiPoint3& kORotCol1, NiPoint3& kORotCol2, float& fOScale,
    const NiPoint3& kINormal, const NiPoint3& kIUp, const NiPoint3& kIVelocity,
    const float fIRadius, const float fISize, const float fIRotAngle, const NiPoint3& fIRotAxis,
    const float fIAge, const float fILifeSpan, const NiUInt8 ucNumKeys,
    const NiPSKernelQuaternionKey* pkKeys, const NiPSLoopBehavior eLoopBehavior,
    const float fIScaleAmount, const float fIScaleRest, const float fIScaleLimit)
{
    // When kNormal is zero, this code uses kUp as the third column of the basis matrix
    // and leaves the other columns of the basis matrix as zero. As a result, the final
    // computed rotations will have a non-zero third column and zero other columns.
    // When kUp is zero the behavior is similar except that the first column is the
    // non-zero entry. Calling code must deal with the resulting invalid rotations.

    NiPoint3 kRight = kIUp.UnitCross(kINormal);
    NiPoint3 kUp = kINormal.Cross(kRight);

    if (kINormal.x == 0.0f &&
        kINormal.y == 0.0f &&
        kINormal.z == 0.0f)
    {
        kRight.x = 0.0f;
        kRight.y = 0.0f;
        kRight.z = 0.0f;

        kUp = kIUp;
    }

    NiMatrix3 kBasis;
    kBasis.SetCol(0, kINormal);
    kBasis.SetCol(1, kRight);
    kBasis.SetCol(2, kUp);

    NiMatrix3 kSpeedRotate;
    kSpeedRotate.MakeRotation(fIRotAngle, fIRotAxis.x, fIRotAxis.y, fIRotAxis.z);

    //
    // Add in any addition key info
    //
    NiMatrix3 kKeyedRotate;
    if (ucNumKeys == 1)
    {
        pkKeys[0].m_kValue.ToRotation(kKeyedRotate);
    }
    else if (ucNumKeys > 1)
    {
        // Compute scaled age (between 0.0 and 1.0).
        const float fFirstTime = pkKeys[0].m_fTime;
        const float fLastTime = pkKeys[ucNumKeys - 1].m_fTime;
        const float fScaledAge =
            ComputeAnimationTime(fIAge, fILifeSpan, eLoopBehavior, fFirstTime, fLastTime);

        // Catch cases where the time is outside the key range.
        if (fScaledAge <= fFirstTime)
        {
            pkKeys[0].m_kValue.ToRotation(kKeyedRotate);
        }
        else if (fScaledAge >= fLastTime)
        {
            pkKeys[ucNumKeys].m_kValue.ToRotation(kKeyedRotate);
        }
        else
        {
            // Find surrounding values in the keys.
            const NiPSKernelQuaternionKey* pkPrevKey = pkKeys;
            const NiPSKernelQuaternionKey* pkNextKey = pkPrevKey;
            for (NiUInt8 uc = 1; uc < ucNumKeys; ++uc)
            {
                pkNextKey = pkKeys + uc;
                if (fScaledAge <= pkNextKey->m_fTime)
                {
                    break;
                }

                pkPrevKey = pkNextKey;
            }

            // Compute normalized time between the keys.
            float fNormTime = (fScaledAge - pkPrevKey->m_fTime) /
                (pkNextKey->m_fTime - pkPrevKey->m_fTime);

            // Linear interpolation only.
            NiQuaternion kOutput =
                NiQuaternion::Slerp(fNormTime, pkPrevKey->m_kValue, pkNextKey->m_kValue);
            kOutput.ToRotation(kKeyedRotate);
        }
    }
    else
    {
        kKeyedRotate.MakeIdentity();
    }

    NiMatrix3 kRotation = kKeyedRotate * kSpeedRotate * kBasis;

    kRotation.GetCol(0, kORotCol0);
    kRotation.GetCol(1, kORotCol1);
    kRotation.GetCol(2, kORotCol2);

    float fVelocity = kIVelocity.Length();
    float fScale = (fIScaleAmount * fVelocity * fIScaleLimit + fIScaleRest) /
        (fIScaleAmount * fVelocity + 1.0f);
    fOScale = NiMax(fIRadius * fISize * fScale, 0.0f);
}

//--------------------------------------------------------------------------------------------------
EE_FORCEINLINE float NiPSSimulatorKernelHelpers::ComputeAnimationTime(const float fAge,
    const float fLife, const NiPSLoopBehavior eLoop, const float fFirstKeyTime,
    const float fLastKeyTime)
{
    switch (eLoop)
    {
        case PSKERNELLOOP_CLAMP_BIRTH:
            return fAge + fFirstKeyTime;

        case PSKERNELLOOP_CLAMP_DEATH:
            return fLastKeyTime - fLife + fAge;

        case PSKERNELLOOP_AGESCALE:
            return fAge * (fLastKeyTime - fFirstKeyTime) / fLife + fFirstKeyTime;

        case PSKERNELLOOP_LOOP:
        {
            float fKeyDiff = fLastKeyTime - fFirstKeyTime;
            if (fKeyDiff > NIPSKERNEL_EPSILON)
            {
                return NiFmod(fAge, fLastKeyTime - fFirstKeyTime);
            }
            else
            {
                return fFirstKeyTime;
            }
        }

        case PSKERNELLOOP_REFLECT:
        {
            float fKeyDiff = fLastKeyTime - fFirstKeyTime;
            if (fKeyDiff > NIPSKERNEL_EPSILON)
            {
                float fRatio = fAge / fKeyDiff;
                float fWhole = NiFloor(fRatio);
                float fRemainder = fRatio - fWhole;
                NiUInt32 uiReverse = (NiUInt32)fWhole % 2;
                if (uiReverse > 0)
                    return fLastKeyTime - fRemainder;
                else
                    return fRemainder;
            }
            else
            {
                return fFirstKeyTime;
            }
        }
    }

    return 0.0f;
}

//--------------------------------------------------------------------------------------------------
