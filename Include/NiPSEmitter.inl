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

//--------------------------------------------------------------------------------------------------
inline const NiFixedString& NiPSEmitter::GetName() const
{
    return m_kName;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetName(const NiFixedString& kName)
{
    m_kName = kName;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetSpeed() const
{
    return m_fSpeed;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetSpeed(float fSpeed)
{
    m_fSpeed = fSpeed;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetSpeedVar() const
{
    return m_fSpeedVar;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetSpeedVar(float fSpeedVar)
{
    m_fSpeedVar = fSpeedVar;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetSpeedFlipRatio() const
{
    return m_fSpeedFlipRatio;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetSpeedFlipRatio(float fFlipRatio)
{
    m_fSpeedFlipRatio = fFlipRatio;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetDeclination() const
{
    return m_fDeclination;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetDeclination(float fDeclination)
{
    m_fDeclination = fDeclination;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetDeclinationVar() const
{
    return m_fDeclinationVar;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetDeclinationVar(float fDeclinationVar)
{
    m_fDeclinationVar = fDeclinationVar;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetPlanarAngle() const
{
    return m_fPlanarAngle;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetPlanarAngle(float fPlanarAngle)
{
    m_fPlanarAngle = fPlanarAngle;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetPlanarAngleVar() const
{
    return m_fPlanarAngleVar;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetPlanarAngleVar(float fPlanarAngleVar)
{
    m_fPlanarAngleVar = fPlanarAngleVar;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetSize() const
{
    return m_fSize;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetSize(float fSize)
{
    m_fSize = fSize;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetSizeVar() const
{
    return m_fSizeVar;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetSizeVar(float fSizeVar)
{
    m_fSizeVar = fSizeVar;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetLifeSpan() const
{
    return m_fLifeSpan;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetLifeSpan(float fLifeSpan)
{
    m_fLifeSpan = fLifeSpan;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetLifeSpanVar() const
{
    return m_fLifeSpanVar;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetLifeSpanVar(float fLifeSpanVar)
{
    m_fLifeSpanVar = fLifeSpanVar;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetRotAngle() const
{
    return m_fRotAngle;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetRotAngle(float fRotAngle)
{
    m_fRotAngle = fRotAngle;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetRotAngleVar() const
{
    return m_fRotAngleVar;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetRotAngleVar(float fRotAngleVar)
{
    m_fRotAngleVar = fRotAngleVar;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetRotSpeed() const
{
    return m_fRotSpeed;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetRotSpeed(float fRotSpeed)
{
    m_fRotSpeed = fRotSpeed;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::GetRotSpeedVar() const
{
    return m_fRotSpeedVar;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetRotSpeedVar(float fRotSpeedVar)
{
    m_fRotSpeedVar = fRotSpeedVar;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSEmitter::GetRandomRotSpeedSign() const
{
    return m_bRandomRotSpeedSign;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetRandomRotSpeedSign(bool bRandomRotSpeedSign)
{
    m_bRandomRotSpeedSign = bRandomRotSpeedSign;
}

//--------------------------------------------------------------------------------------------------
inline const NiPoint3& NiPSEmitter::GetRotAxis() const
{
    return m_kRotAxis;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetRotAxis(const NiPoint3& kRotAxis)
{
    m_kRotAxis = kRotAxis;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSEmitter::GetRandomRotAxis() const
{
    return m_bRandomRotAxis;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetRandomRotAxis(bool bRandomRotAxis)
{
    m_bRandomRotAxis = bRandomRotAxis;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::ResetTransformation()
{
    m_bResetRequired = true;
}

//--------------------------------------------------------------------------------------------------
inline NiRGBA NiPSEmitter::GetColorBackCompat() const
{
    return m_kColorBackCompat;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSEmitter::SetColorBackCompat(const NiRGBA& kInitialColor)
{
    m_kColorBackCompat = kInitialColor;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSEmitter::ComputeSpeed() const
{
    return (m_fSpeed + (m_fSpeedVar * (NiUnitRandom() - 0.5f)));
}

//--------------------------------------------------------------------------------------------------
inline NiPoint3 NiPSEmitter::ComputeDirection(bool bNewDirection) const
{
    NiPoint3 kDir(NiPoint3::UNIT_Z);

    float fDec = m_fDeclination;
    if (m_fDeclinationVar != 0.0f)
    {
        fDec += m_fDeclinationVar * NiSymmetricRandom();
    }

    if (fDec != 0.0f)
    {
        float fPlan = m_fPlanarAngle;
        if (m_fPlanarAngleVar != 0.0f)
        {
            fPlan += m_fPlanarAngleVar * NiSymmetricRandom();
        }

        // Compute the direction using the new method. This is a method that was developed for RPI.
        if (bNewDirection)
        {
            float fDecSin, fDecCos;
            NiSinCos(fDec, fDecSin, fDecCos);
            float fPlanSin, fPlanCos;
            NiSinCos(fPlan, fPlanSin, fPlanCos);

            kDir = NiPoint3(fDecCos * fPlanSin, -fDecSin, fDecCos * fPlanCos);
        }
        else
        {
            float fSinDec = 0.0f;
            float fCosDec = 1.0f;
            NiSinCos(fDec, fSinDec, fCosDec);

            float fSinPlan = 0.0f;
            float fCosPlan = 1.0f;
            if (fPlan != 0.0f)
            {
                NiSinCos(fPlan, fSinPlan, fCosPlan);
            }

            kDir = NiPoint3(fSinDec * fCosPlan, fSinDec * fSinPlan, fCosDec);
        }
    }

    return kDir;
}

//--------------------------------------------------------------------------------------------------
