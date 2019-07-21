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
template <class T>
inline TTimeOfDayEntityFunctor<T>::TTimeOfDayEntityFunctor(egf::EntityManager* pEntityManager,
    egf::EntityID targetObject, egf::PropertyID targetProperty) :
    m_functorTargetObject(targetObject),
    m_functorTargetProperty(targetProperty),
    m_pEntityManager(pEntityManager)
{
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline void TTimeOfDayEntityFunctor<T>::SetValue(TargetValue val)
{
    egf::Entity* pEntity = m_pEntityManager->LookupEntity(m_functorTargetObject);

    if (!pEntity)
        return;

    efd::ClassID propertyType;
    if (pEntity->GetPropertyType(m_functorTargetProperty, propertyType) != egf::PropertyResult_OK)
    {
        return;
    }

    if (pEntity->SetPropertyValue(m_functorTargetProperty, val) != egf::PropertyResult_OK)
    {
        EE_LOG(efd::kGamebryoGeneral0, efd::ILogger::kERR1, ("Time of Day entity functor: "
            "failed to set the property value of a ToD registered entity"));
    }
}

//--------------------------------------------------------------------------------------------------
template <> 
inline void TTimeOfDayEntityFunctor<efd::ColorA>::SetValue(TargetValue val)
{
    // This special case is used to set entity color values that do not use a alpha channel
    // It is needed as color key interpolators only support NiColorA.

    egf::Entity* pEntity = m_pEntityManager->LookupEntity(m_functorTargetObject);

    if (!pEntity)
        return;

    efd::ClassID propertyType;
    if (pEntity->GetPropertyType(m_functorTargetProperty, propertyType) != egf::PropertyResult_OK)
    {
        return;
    }

    efd::Color temp(val.r, val.g, val.b);
    switch(propertyType)
    {
    case efd::kPropID_Color:        
        pEntity->SetPropertyValue(m_functorTargetProperty, temp);
        break;
    case efd::kPropID_ColorA:
        pEntity->SetPropertyValue(m_functorTargetProperty, val);
        break;
    }
}