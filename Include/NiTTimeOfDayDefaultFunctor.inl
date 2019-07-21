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

template <class T, class V>
inline NiTTimeOfDayDefaultFunctor<T,V>::NiTTimeOfDayDefaultFunctor(TargetType* pkTarget, 
    SetFunctionType kSetFunction) :
    m_kSetFunction(kSetFunction),
    m_pkFunctorTarget(pkTarget)
{
    EE_ASSERT(kSetFunction);
    EE_ASSERT(pkTarget);
}

//--------------------------------------------------------------------------------------------------
template <class T, class V>
inline NiTTimeOfDayDefaultFunctor<T,V>::~NiTTimeOfDayDefaultFunctor()
{

}

//--------------------------------------------------------------------------------------------------
template <class T, class V>
inline void NiTTimeOfDayDefaultFunctor<T,V>::SetValue(ValueType kToSet)
{
    (((TargetType*)m_pkFunctorTarget)->*m_kSetFunction)(kToSet);
}

//--------------------------------------------------------------------------------------------------