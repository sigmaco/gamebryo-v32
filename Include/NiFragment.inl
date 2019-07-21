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
template <class T> void NiFragment::Fetch(NiFragmentMaterial* pkMaterial, 
    T*& pkFragment)
{   
    pkFragment = NULL;
    
    // Search for an instance of this fragment on the material
    for (NiUInt32 ui = 0; ui < pkMaterial->m_kFragments.GetSize(); ui++)
    {
        NiObject* pkObj = pkMaterial->m_kFragments.GetAt(ui);
        if (NiIsExactKindOf(T, pkObj))
        {
            pkFragment = NiDynamicCast(T, pkObj);
            break;
        }
    }
    
    if (!pkFragment)
    {
        // Create an instance of this fragment
        pkFragment = NiNew T();
        pkFragment->SetOwner(pkMaterial);
    }
}

//--------------------------------------------------------------------------------------------------
