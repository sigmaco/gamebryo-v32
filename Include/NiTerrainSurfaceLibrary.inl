// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed excekPt in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

//--------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs, class TargetType> 
inline NiTerrainSurfaceLibrary::EventDelegate_PackageReference<Sender, EventArgs, TargetType>::
    EventDelegate_PackageReference(TargetType* pkTarget, CallbackType kCallback)
        : NiTerrainEventHandlerDelegate<Sender, EventArgs, TargetType>(pkTarget, kCallback)
        , m_uiReferenceCount(1)
{

}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs, class TargetType>
inline bool NiTerrainSurfaceLibrary::EventDelegate_PackageReference<Sender, EventArgs, TargetType>::
    CanAttachHandler(const NiTerrainEventHandlerBase<Sender, EventArgs>* pkOtherHandler)
{
    if (*pkOtherHandler == *this)
    {
        m_uiReferenceCount++;
        return false;
    }

    return true;
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs, class TargetType>
inline bool NiTerrainSurfaceLibrary::EventDelegate_PackageReference<Sender, EventArgs, TargetType>::
    CanDetachHandler()
{
    EE_ASSERT(m_uiReferenceCount > 0);
    m_uiReferenceCount--;
    
    return (m_uiReferenceCount == 0);
}

//--------------------------------------------------------------------------------------------------
template <class TargetType, typename CallbackType>
inline void NiTerrainSurfaceLibrary::RegisterReference(const NiTerrainAssetReference& kReference, 
    TargetType* pkTarget, CallbackType kCallback)
{
    typedef EventDelegate_PackageReference<NiSurfacePackage, const efd::utf8string&, TargetType> 
        DelegateType;

    DelegateType* pkDelegate = NULL;
    if (pkTarget != NULL && kCallback != NULL)
    {
        pkDelegate = NiNew DelegateType(pkTarget, kCallback);
    }

    RegisterReference_Internal(kReference, pkDelegate);
}

//--------------------------------------------------------------------------------------------------
template <class TargetType, typename CallbackType>
inline void NiTerrainSurfaceLibrary::DeregisterReference(const NiTerrainAssetReference& kReference, 
    TargetType* pkTarget, CallbackType kCallback)
{
    typedef EventDelegate_PackageReference<NiSurfacePackage, const efd::utf8string&, TargetType> 
        DelegateType;

    DelegateType kDelegate(pkTarget, kCallback);
    DeregisterReference_Internal(kReference, &kDelegate);
}

//--------------------------------------------------------------------------------------------------


