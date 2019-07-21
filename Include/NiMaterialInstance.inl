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
inline NiMaterialInstance::NiMaterialInstance() :
    m_uiMaterialExtraData(
        (unsigned int) NiMaterialInstance::DEFAULT_EXTRA_DATA),
    m_kVertexDeclarationCache(NULL),
    m_kAdapterTable(0),
    m_eNeedsUpdate(DIRTY)
{
    /* */
}

//--------------------------------------------------------------------------------------------------
inline NiMaterialInstance::NiMaterialInstance(
    const NiMaterialInstance& kMatInst) :
    m_spCachedShader(kMatInst.m_spCachedShader),
    m_spMaterial(kMatInst.m_spMaterial),
    m_uiMaterialExtraData(kMatInst.m_uiMaterialExtraData),
    m_kVertexDeclarationCache(kMatInst.m_kVertexDeclarationCache),
    m_kAdapterTable(0),
    m_eNeedsUpdate(DIRTY)
{
    m_kAdapterTable = kMatInst.m_kAdapterTable;
    EE_ASSERT((m_kVertexDeclarationCache == NULL) ==
        (m_spCachedShader == NULL));
    if (m_spCachedShader)
    {
        m_spCachedShader->ReferenceVertexDeclarationCache(
            m_kVertexDeclarationCache);
    }
}

//--------------------------------------------------------------------------------------------------
inline NiMaterialInstance::NiMaterialInstance(NiMaterial* pkMaterial) :
    m_spMaterial(pkMaterial),
    m_uiMaterialExtraData(
        (unsigned int) NiMaterialInstance::DEFAULT_EXTRA_DATA),
    m_kVertexDeclarationCache(NULL),
    m_kAdapterTable(0),
    m_eNeedsUpdate(DIRTY)
{
    /* */
}

//--------------------------------------------------------------------------------------------------
inline NiMaterialInstance::NiMaterialInstance(NiMaterial* pkMaterial,
    unsigned int uiMaterialExtraData) :
    m_spMaterial(pkMaterial),
    m_uiMaterialExtraData(uiMaterialExtraData),
    m_kVertexDeclarationCache(NULL),
    m_kAdapterTable(0),
    m_eNeedsUpdate(DIRTY)
{
    /* */
}

//--------------------------------------------------------------------------------------------------
inline NiMaterialInstance::~NiMaterialInstance()
{
    ClearCachedShader();
}

//--------------------------------------------------------------------------------------------------
inline NiMaterialInstance& NiMaterialInstance::operator=(
    const NiMaterialInstance& kMatInst)
{
    m_spCachedShader = kMatInst.m_spCachedShader;
    m_spMaterial = kMatInst.m_spMaterial;
    m_uiMaterialExtraData = kMatInst.m_uiMaterialExtraData;
    m_kVertexDeclarationCache = kMatInst.m_kVertexDeclarationCache;
    m_kAdapterTable = kMatInst.m_kAdapterTable;
    m_eNeedsUpdate = kMatInst.m_eNeedsUpdate;

    EE_ASSERT((m_kVertexDeclarationCache == NULL) ==
        (m_spCachedShader == NULL));
    if (m_spCachedShader)
    {
        m_spCachedShader->ReferenceVertexDeclarationCache(
            m_kVertexDeclarationCache);
    }

    return *this;
}

//--------------------------------------------------------------------------------------------------
inline NiShader* NiMaterialInstance::GetCachedShader() const
{
    return m_spCachedShader;
}

//--------------------------------------------------------------------------------------------------
inline bool NiMaterialInstance::ShaderEquals(
    const NiMaterialInstance* pkInMatInst) const
{
    if (pkInMatInst->m_spMaterial != m_spMaterial)
        return false;

    if (pkInMatInst->m_uiMaterialExtraData != m_uiMaterialExtraData)
        return false;

    if (pkInMatInst->m_spCachedShader != m_spCachedShader)
        return false;

    return true;
}

//--------------------------------------------------------------------------------------------------
inline void NiMaterialInstance::ClearCachedShader()
{
    if (m_spCachedShader && m_kVertexDeclarationCache)
    {
        m_spCachedShader->ReleaseVertexDeclarationCache(
            m_kVertexDeclarationCache);
    }
    m_kVertexDeclarationCache = NULL;
    m_spCachedShader = NULL;
    m_kAdapterTable.InitializeTable(0);
}

//--------------------------------------------------------------------------------------------------
inline NiMaterial* NiMaterialInstance::GetMaterial() const
{
    return m_spMaterial;
}

//--------------------------------------------------------------------------------------------------
inline void NiMaterialInstance::Reinitialize()
{
    ClearCachedShader();
    m_spMaterial = NULL;
    m_eNeedsUpdate = DIRTY;
}

//--------------------------------------------------------------------------------------------------
inline void NiMaterialInstance::SetMaterialNeedsUpdate(bool bNeedsUpdate)
{
    m_eNeedsUpdate = (bNeedsUpdate ? DIRTY : CLEAN);
}

//--------------------------------------------------------------------------------------------------
inline NiVertexDeclarationCache NiMaterialInstance::GetVertexDeclarationCache()
    const
{
    return m_kVertexDeclarationCache;
}

//--------------------------------------------------------------------------------------------------
inline const NiSemanticAdapterTable&
    NiMaterialInstance::GetSemanticAdapterTable() const
{
    return m_kAdapterTable;
}

//--------------------------------------------------------------------------------------------------
inline NiSemanticAdapterTable& NiMaterialInstance::GetSemanticAdapterTable()
{
    return m_kAdapterTable;
}

//--------------------------------------------------------------------------------------------------
inline void NiMaterialInstance::SetMaterialExtraData(unsigned int uiExtraData)
{
    m_uiMaterialExtraData = uiExtraData;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiMaterialInstance::GetMaterialExtraData() const
{
    return m_uiMaterialExtraData;
}

//--------------------------------------------------------------------------------------------------
inline void NiMaterialInstance::SetVertexDeclarationCache(
    NiVertexDeclarationCache kCache)
{
    EE_ASSERT(m_kVertexDeclarationCache == NULL);
    m_kVertexDeclarationCache = kCache;
    m_spCachedShader->ReferenceVertexDeclarationCache(kCache);
}

//--------------------------------------------------------------------------------------------------
inline void NiMaterialInstance::ClearVertexDeclarationCache()
{
    if (m_kVertexDeclarationCache)
    {
        m_spCachedShader->ReleaseVertexDeclarationCache(
            m_kVertexDeclarationCache);
        m_kVertexDeclarationCache = NULL;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiMaterialInstance::SetShaderCache(NiShader* pkCachedShader)
{
    m_spCachedShader = pkCachedShader;
}

//--------------------------------------------------------------------------------------------------