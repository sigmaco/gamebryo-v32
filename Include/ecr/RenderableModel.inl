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

//-------------------------------------------------------------------------------------------------
inline efd::Bool ecr::RenderableModel::GetIsVisible() const
{
    return m_isVisible;
}

//-------------------------------------------------------------------------------------------------
inline void ecr::RenderableModel::SetIsVisible(const efd::Bool& isVisible)
{
    if (m_isVisible != isVisible)
    {
        m_isVisible = isVisible;
        
        InvokeCallbacks(
            egf::kFlatModelID_StandardModelLibrary_Renderable,
            m_pOwningEntity,
            egf::kPropertyID_StandardModelLibrary_IsVisible,
            this,
            0,
            0);
    }
}

//-------------------------------------------------------------------------------------------------
inline void ecr::RenderableModel::SetInternalIsVisible(
    const efd::Bool isVisible,
    egf::IPropertyCallback* ignoreCallback)
{
    if (m_isVisible != isVisible)
    {
        m_isVisible = isVisible;
    
        m_pOwningEntity->BuiltinPropertyChanged(
            egf::kPropertyID_StandardModelLibrary_IsVisible,
            this);

        InvokeCallbacks(
            egf::kFlatModelID_StandardModelLibrary_Renderable,
            m_pOwningEntity,
            egf::kPropertyID_StandardModelLibrary_IsVisible,
            this,
            0,
            ignoreCallback);
    }
}

//-------------------------------------------------------------------------------------------------
inline void ecr::RenderableModel::AddCallback(egf::IPropertyCallback* pCallback)
{
    RenderableModel temp;
    temp.AddPropertyCallback(pCallback);
}

//-------------------------------------------------------------------------------------------------
inline void ecr::RenderableModel::RemoveCallback(egf::IPropertyCallback* pCallback)
{
    RenderableModel temp;
    temp.RemovePropertyCallback(pCallback);
}
