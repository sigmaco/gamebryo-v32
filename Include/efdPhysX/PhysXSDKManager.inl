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

// NiPhysXManager inline functions

//--------------------------------------------------------------------------------------------------
inline efdPhysX::PhysXSDKManager* efdPhysX::PhysXSDKManager::GetManager()
{
    return ms_pPhysXManager;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool efdPhysX::PhysXSDKManager::IsInitialized() const
{
    return m_pPhysXSDK != 0;
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXSDKManager::WaitSDKLock()
{
    m_sdkCritSect.Lock();
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXSDKManager::ReleaseSDKLock()
{
    m_sdkCritSect.Unlock();
}

//--------------------------------------------------------------------------------------------------
