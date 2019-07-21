// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 2006-2009 Todd Berkebile.
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net


//------------------------------------------------------------------------------------------------
template<typename FROM, typename TO>
efd::ParameterResult efd::ParameterConverter<FROM, TO>::GetParameter(
    const efd::ParameterList& i_params,
    efd::UInt32 i_index,
    void* o_result) const
{
    FROM from;
    efd::ParameterResult result = i_params.GetParameter<FROM>(i_index, from);
    if (pr_OK == result)
    {
        TO& to = *(TO*)o_result;
        efd::ConvertingAssignment<FROM, TO>(to, from);
    }
    return result;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt64 efd::ParameterConverterManager::MakeConverterID(
    efd::ClassID from,
    efd::ClassID to)
{
    return ((efd::UInt64)from << 32) | (efd::UInt64)to;
}

//------------------------------------------------------------------------------------------------
template<typename FROM, typename TO>
void efd::ParameterConverterManager::MakeDefaultConverter()
{
    efd::ClassID from = efd::GetClassIDFromType<FROM>();
    efd::ClassID to = efd::GetClassIDFromType<TO>();
    RegisterConverter(from, to, EE_NEW efd::ParameterConverter<FROM, TO>);
}

//------------------------------------------------------------------------------------------------
template<typename FROM, typename TO>
void efd::ParameterConverterManager::MakeDefaultBidirectionalConverters()
{
    efd::ClassID from = efd::GetClassIDFromType<FROM>();
    efd::ClassID to = efd::GetClassIDFromType<TO>();
    RegisterConverter(from, to, EE_NEW efd::ParameterConverter<FROM, TO>);
    RegisterConverter(to, from, EE_NEW efd::ParameterConverter<TO, FROM>);
}


//------------------------------------------------------------------------------------------------
// ParameterList
//------------------------------------------------------------------------------------------------
template<typename T>
efd::SInt32 efd::ParameterList::AddParameter(const T& parameter)
{
    efd::Archive ar = PrepareNewParameter();
    SetParameterData(parameter, ar);
    return FinishNewParameter(ar);
}

//------------------------------------------------------------------------------------------------
template<typename T>
efd::SInt32 efd::ParameterList::AddParameter(const efd::utf8string& pszName, const T& parameter)
{
    UInt32 index = GetIndexFromName(pszName.c_str());
    if (index < m_typeInfo.size())
    {
        // Name already exists in the parameter list
        return -1;
    }

    efd::Archive ar = PrepareNewParameter();
    SetParameterName(pszName, ar);
    SetParameterData(parameter, ar);
    return FinishNewParameter(ar);
}

//------------------------------------------------------------------------------------------------
template<typename T>
void efd::ParameterList::SetParameterData(const T& parameter, efd::Archive& ar)
{
    EE_ASSERT(ar.IsPacking());
    ParameterTypeInfo& pti = m_typeInfo.back();
    pti.m_dataType = efd::GetClassIDFromType<T>();
    pti.m_container = ct_Scalar;

    // then we add the data:
    pti.m_offset = (efd::UInt16)ar.GetCurrentPosition();
    efd::Serializer::SerializeConstObject(parameter, ar);
    pti.m_size = (efd::UInt16)ar.GetCurrentPosition() - pti.m_offset;
    EE_ASSERT(ar.GetCurrentPosition() > pti.m_offset);
}

//------------------------------------------------------------------------------------------------
template<typename T>
void efd::ParameterList::SetParameterData(const efd::list<T>& parameter, efd::Archive& ar)
{
    EE_ASSERT(ar.IsPacking());
    ParameterTypeInfo& pti = m_typeInfo.back();
    pti.m_dataType = efd::GetClassIDFromType<T>();
    pti.m_container = ct_List;

    pti.m_offset = (efd::UInt16)ar.GetCurrentPosition();
    efd::SR_StdList<>::Serialize(const_cast<efd::list<T>&>(parameter), ar);
    pti.m_size = (efd::UInt16)ar.GetCurrentPosition() - pti.m_offset;
    EE_ASSERT(ar.GetCurrentPosition() > pti.m_offset);
}

//------------------------------------------------------------------------------------------------
template<typename T>
void efd::ParameterList::SetParameterData(
    const efd::map<efd::utf8string, T>& parameter,
    efd::Archive& ar)
{
    EE_ASSERT(ar.IsPacking());
    ParameterTypeInfo& pti = m_typeInfo.back();
    pti.m_dataType = efd::GetClassIDFromType<T>();
    pti.m_container = ct_Map_StringKeyed;

    pti.m_offset = (efd::UInt16)ar.GetCurrentPosition();
    efd::SR_StdMap<>::Serialize(const_cast<efd::map<efd::utf8string, T>&>(parameter), ar);
    pti.m_size = (efd::UInt16)ar.GetCurrentPosition() - pti.m_offset;
    EE_ASSERT(ar.GetCurrentPosition() > pti.m_offset);
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 efd::ParameterList::GetSize() const
{
    return m_typeInfo.size();
}

//------------------------------------------------------------------------------------------------
template<typename T>
efd::ParameterResult efd::ParameterList::GetParameter(efd::SInt32 i_index, T& o_result) const
{
    return GetParameter((efd::UInt32)i_index, o_result);
}

//------------------------------------------------------------------------------------------------
template<typename T>
efd::ParameterResult efd::ParameterList::GetParameter(const char* i_pszName, T& o_result) const
{
    efd::UInt32 index = GetIndexFromName(i_pszName);
    if (index >= m_typeInfo.size())
    {
        return pr_BadName;
    }
    return GetParameter(index, o_result);
}

//------------------------------------------------------------------------------------------------
template<typename T>
efd::ParameterResult efd::ParameterList::GetParameter(efd::UInt32 i_index, T& o_result) const
{
    if (i_index >= m_typeInfo.size())
    {
        return pr_OutOfRange;
    }

    if (m_typeInfo[i_index].m_container != ct_Scalar)
    {
        return pr_ContainerMismatch;
    }

    efd::ClassID from = m_typeInfo[i_index].m_dataType;
    efd::ClassID to = efd::GetClassIDFromType<T>();
    if (from != to)
    {
        IParameterConverter* converter = FindConverter(from, to);
        if (converter)
        {
            return converter->GetParameter(*this, i_index, &o_result);
        }
        return pr_TypeMismatch;
    }

    // Make a window to ensure no data over/under flow
    efd::Archive ar(efd::Archive::Unpacking, m_parameterStorage.MakeWindow(
        m_typeInfo[i_index].m_offset,
        m_typeInfo[i_index].m_size));
    efd::Serializer::SerializeObject(o_result, ar);
    ar.CheckForUnderflow();
    if (ar.GetError())
    {
        return pr_DataError;
    }
    return pr_OK;
}

//------------------------------------------------------------------------------------------------
template<typename T>
efd::ParameterResult efd::ParameterList::GetParameter(
    efd::UInt32 i_index,
    efd::list<T>& o_result) const
{
    if (i_index >= m_typeInfo.size())
    {
        return pr_OutOfRange;
    }

    if (m_typeInfo[i_index].m_container != ct_List)
    {
        return pr_ContainerMismatch;
    }

    efd::ClassID from = m_typeInfo[i_index].m_dataType;
    efd::ClassID to = efd::GetClassIDFromType<T>();
    if (from != to)
    {
        // NOTE: No converters for non-scalar types
        return pr_TypeMismatch;
    }

    // Make a window to ensure no data over/under flow
    efd::Archive ar(efd::Archive::Unpacking, m_parameterStorage.MakeWindow(
        m_typeInfo[i_index].m_offset,
        m_typeInfo[i_index].m_size));
    efd::SR_StdList<>::Serialize(o_result, ar);
    ar.CheckForUnderflow();
    if (ar.GetError())
    {
        return pr_DataError;
    }
    return pr_OK;
}

//------------------------------------------------------------------------------------------------
template<typename T>
efd::ParameterResult efd::ParameterList::GetParameter(
    efd::UInt32 i_index,
    efd::map<efd::utf8string, T>& o_result) const
{
    if (i_index >= m_typeInfo.size())
    {
        return pr_OutOfRange;
    }

    if (m_typeInfo[i_index].m_container != ct_Map_StringKeyed)
    {
        return pr_ContainerMismatch;
    }

    efd::ClassID from = m_typeInfo[i_index].m_dataType;
    efd::ClassID to = efd::GetClassIDFromType<T>();
    if (from != to)
    {
        // NOTE: No converters for non-scalar types
        return pr_TypeMismatch;
    }

    // Make a window to ensure no data over/under flow
    efd::Archive ar(efd::Archive::Unpacking, m_parameterStorage.MakeWindow(
        m_typeInfo[i_index].m_offset,
        m_typeInfo[i_index].m_size));
    efd::SR_StdMap<>::Serialize(o_result, ar);
    ar.CheckForUnderflow();
    if (ar.GetError())
    {
        return pr_DataError;
    }
    return pr_OK;
}

//------------------------------------------------------------------------------------------------
template<typename T>
bool efd::ParameterList::IsExactKind(efd::UInt32 i_index)
{
    if (i_index >= m_typeInfo.size())
    {
        return false;
    }
    T* pDummy = NULL;
    return IsExactKindHelper(i_index, *pDummy);
}

//------------------------------------------------------------------------------------------------
template<typename T>
bool efd::ParameterList::IsExactKindHelper(efd::UInt32 i_index, const T&)
{
    ParameterTypeInfo& pti = m_typeInfo[i_index];
    return pti.m_container == efd::ct_Scalar && pti.m_dataType == efd::GetClassIDFromType<T>();
}

//------------------------------------------------------------------------------------------------
template<typename T>
bool efd::ParameterList::IsExactKindHelper(efd::UInt32 i_index, const efd::list<T>&)
{
    ParameterTypeInfo& pti = m_typeInfo[i_index];
    return pti.m_container == efd::ct_List && pti.m_dataType == efd::GetClassIDFromType<T>();
}

//------------------------------------------------------------------------------------------------
template<typename T>
bool efd::ParameterList::IsExactKindHelper(efd::UInt32 i_index, const efd::map<efd::utf8string, T>&)
{
    ParameterTypeInfo& pti = m_typeInfo[i_index];
    return pti.m_container == efd::ct_Map_StringKeyed &&
        pti.m_dataType == efd::GetClassIDFromType<T>();
}

