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

//---------------------------------------------------------------------------
template <class T, class V>
NiTTimeOfDayController<T,V>::NiTTimeOfDayController(
    TargetFunctor kFunctor):
    m_kTargetFunctor(kFunctor)
{

}

//---------------------------------------------------------------------------
template <class T, class V>
void NiTTimeOfDayController<T,V>::Update(float fTime)
{
    if (m_spInterpolator)
    {
        ValueType kValue;
        if (m_spInterpolator->Update(fTime, NULL, kValue))
            m_kTargetFunctor.SetValue(kValue);
    }
}

//---------------------------------------------------------------------------
template <class T, class V>
void NiTTimeOfDayController<T,V>::SetInterpolator(
    NiInterpolator* pkInterpolator)
{
    m_spInterpolator = pkInterpolator;
}

//---------------------------------------------------------------------------