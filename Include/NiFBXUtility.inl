// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net


//-----------------------------------------------------------------------------------------------
inline void NiFBXUtility::ConvertTransform(NiAVObject* pkObject, KFbxNode* pkTarget) 
{
    NiTransform kTransform = pkObject->GetLocalTransform();
    float fX, fY, fZ;
    kTransform.m_Rotate.ToEulerAnglesZYX(fZ, fY, fX);
    
    pkTarget->SetDefaultR(
        KFbxVector4(-fX, -fY, -fZ) * 180.0 / NI_PI);

    pkTarget->SetDefaultS(
        KFbxVector4(kTransform.m_fScale, kTransform.m_fScale, kTransform.m_fScale));

    pkTarget->SetDefaultT(
        ConvertNiPoint(kTransform.m_Translate));
}
//-----------------------------------------------------------------------------------------------
inline KFbxVector4 NiFBXUtility::ConvertNiPoint(const NiPoint3& k) {
    return KFbxVector4(k.x, k.y, k.z);
}
//-----------------------------------------------------------------------------------------------
inline KFbxVector2 NiFBXUtility::ConvertNiPoint(const NiPoint2& k) {
    return KFbxVector2(k.x, k.y);
}
//-----------------------------------------------------------------------------------------------
inline KFbxColor NiFBXUtility::ConvertNiColor(const NiColor& k) {
    return KFbxColor(k.r, k.g, k.b);
}
//-----------------------------------------------------------------------------------------------
inline fbxDouble3 NiFBXUtility::ConvertNiColorToDouble3(const NiColor& k) {
    return fbxDouble3(k.r, k.g, k.b);
}
//-----------------------------------------------------------------------------------------------
