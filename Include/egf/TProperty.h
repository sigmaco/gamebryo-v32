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

#pragma once
#ifndef EE_TPROPERTY_H
#define EE_TPROPERTY_H

#include <egf/IProperty.h>
#include <egf/IPropertyType.h>
#include <efd/ServiceManager.h>
#include <egf/egfLibType.h>
#include <efd/ParseHelper.h>
#include <efd/SerializeRoutines.h>
#if defined(EE_MEMTRACKER_DETAILEDREPORTING)
#include <efd/MemTracker.h>
#endif

/**
    Macros to create scalar properties using the TPropertyScalar template class
*/
#define EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(Typename, Type, ClassID) \
    typedef egf::TPropertyScalar<Type, ClassID> Typename##ScalarProperty; \
    egf::IProperty* Typename##ScalarPropertyFactory();

#define EE_IMPLEMENT_PRIMITIVE_SCALAR_PROPERTY(Typename) \
    egf::IProperty* Typename##ScalarPropertyFactory() { \
        return EE_NEW Typename##ScalarProperty(); \
    }


/**
    Macros to create associative array properties using the TPropertyAssoc
    template class
*/
#define EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(Typename, Type, ClassID) \
    typedef egf::TPropertyAssoc<Type, ClassID> Typename##AssocProperty; \
    egf::IProperty* Typename##AssocPropertyFactory();

#define EE_IMPLEMENT_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(Typename) \
    egf::IProperty* Typename##AssocPropertyFactory() { \
        return EE_NEW Typename##AssocProperty(); \
    }

namespace egf
{

/**
    Templated class that implements scalar properties.
*/
template<typename TType, efd::ClassID TClassID>
class TPropertyScalar : public IProperty
{
    typedef TPropertyScalar<TType, TClassID> MyClassName;

public:

    static const efd::ClassID CLASS_ID = TClassID;

    /// Assignment operator
    TPropertyScalar<TType, TClassID>& operator=(const TPropertyScalar<TType, TClassID>& other)
    {
        m_data = other.m_data;
        return *this;
    }

    // Overridden virtual functions inherit base documentation and thus are not documented here.

    virtual bool operator==(const IProperty& other) const
    {
        if (this == &other) return true;
        if (other.GetPropertyType() != GetPropertyType()) return false;

        const MyClassName* otherClass = static_cast<const MyClassName *>(&other);
        return otherClass->m_data == m_data;
    }

    virtual PropertyResult GetValue(PropertyID propID, void* data) const
    {
        EE_UNUSED_ARG(propID);
        *((TType*) data) = m_data;
        return PropertyResult_OK;
    }

    virtual PropertyResult SetValue(PropertyID propID, const void* data)
    {
        EE_UNUSED_ARG(propID);
        if (m_data != *((TType*) data))
        {
            m_data = *((TType*) data);
        }
        return PropertyResult_OK;
    }

    virtual PropertyResult GetValue(PropertyID propID, const efd::utf8string& key, void* data) const
    {
        EE_UNUSED_ARG(propID);
        EE_UNUSED_ARG(key);
        EE_UNUSED_ARG(data);
        return PropertyResult_PropertyNotAssociativeArray;
    }

    virtual PropertyResult SetValue(PropertyID propID, const efd::utf8string& key, const void* data)
    {
        EE_UNUSED_ARG(propID);
        EE_UNUSED_ARG(key);
        EE_UNUSED_ARG(data);
        return PropertyResult_PropertyNotAssociativeArray;
    }

    virtual IProperty* Clone() const
    {
        MyClassName* pProp = EE_NEW MyClassName();
        if (!pProp)
        {
            return NULL;
        }

        *pProp = *this;

        return pProp;
    }

    virtual PropertyResult GetValueAsString(
        PropertyID propID,
        efd::utf8string& data) const
    {
        EE_UNUSED_ARG(propID);
        if (efd::ParseHelper<TType>::ToString(m_data, data))
            return PropertyResult_OK;
        else
            return PropertyResult_TypeMismatch;
    }

    virtual PropertyResult SetValueByString(PropertyID propID, const efd::utf8string& data)
    {
        TType temp;
        if (efd::ParseHelper<TType>::FromString(data, temp))
        {
            return SetValue(propID, &temp);
        }

        return PropertyResult_TypeMismatch;
    }

    virtual efd::ClassID GetPropertyType() const
    {
        return CLASS_ID;
    }

    virtual efd::ClassID GetDataType(PropertyID i_propID) const
    {
        EE_UNUSED_ARG(i_propID);
        return efd::GetClassIDFromType<TType>();
    }

    void SerializeProperty(PropertyID, efd::Archive& ar)
    {
        efd::Serializer::SerializeObject(m_data, ar);
    }

    void AdvanceStream(PropertyID, efd::Archive& ar) const
    {
        EE_ASSERT(ar.IsUnpacking());
        TType temp;
        efd::Serializer::SerializeObject(temp, ar);
    }

#if defined(EE_MEMTRACKER_DETAILEDREPORTING)
    /// A constructor that registers a detailed memory leak reporting method for this instance.
    TPropertyScalar()
    {
        EE_MEM_SETDETAILEDREPORT(this, MyClassName::LeakDump);
    }

    /// A leak dumping method for use in detailed memory reports. To enable detailed memory leak
    /// reporting recompile all source with the EE_USE_MEMTRACKER_DETAILEDREPORTING macro defined.
    /// See efd/MemTracker.h and efd/MemDefines.h for details.
    static void LeakDump(void* pMem, char* o_buffer, unsigned int i_cchBuffer)
    {
        EE_UNUSED_ARG(pMem);
        efd::Snprintf(o_buffer, i_cchBuffer, EE_TRUNCATE,
            "TPropertyScalar<%s, 0x%08X>",
            efd::ParseHelper<TType>::GetNameOfType(),
            CLASS_ID);
    }
#endif

protected:
    /// Storage for templated data type
    TType m_data;
};



/**
    Templated class that implements associative properties.
*/
template<typename TType, efd::ClassID TClassID>
class TPropertyAssoc : public IProperty
{
    typedef TPropertyAssoc<TType, TClassID> MyClassName;

public:

    static const efd::ClassID CLASS_ID = TClassID;

    /// Assignment operator
    TPropertyAssoc<TType, TClassID>& operator=(const TPropertyAssoc<TType, TClassID>& other)
    {
        m_data = other.m_data;
        return *this;
    }

    // Overridden virtual functions inherit base documentation and thus are not documented here.

    virtual bool operator==(const IProperty& other) const
    {
        if (this == &other) return true;
        if (other.GetPropertyType() != GetPropertyType()) return false;

        const MyClassName* otherClass = static_cast<const MyClassName *>(&other);
        return otherClass->m_data == m_data;
    }

    virtual PropertyResult GetValue(PropertyID propID, void* data) const
    {
        EE_UNUSED_ARG(propID);
        EE_UNUSED_ARG(data);
        return PropertyResult_PropertyNotScalar;
    }

    virtual PropertyResult SetValue(PropertyID propID, const void* data)
    {
        EE_UNUSED_ARG(propID);
        EE_UNUSED_ARG(data);
        return PropertyResult_PropertyNotScalar;
    }

    virtual PropertyResult GetValue(PropertyID propID, const efd::utf8string& key, void* data) const
    {
        EE_UNUSED_ARG(propID);
        typename AssocProcMap::const_iterator iterValues = m_data.find(key);
        if (iterValues != m_data.end())
        {
            *((TType*) data) = iterValues->second;
            return PropertyResult_OK;
        }
        else
        {
            return PropertyResult_KeyNotFound;
        }
    }

    virtual PropertyResult SetValue(PropertyID propID, const efd::utf8string& key, const void* data)
    {
        EE_UNUSED_ARG(propID);
        m_data[key] = *((TType*) data);
        return PropertyResult_OK;
    }

    virtual PropertyResult HasValue(PropertyID propID, const efd::utf8string& key) const
    {
        EE_UNUSED_ARG(propID);

        if (0 != m_data.count(key))
        {
            return PropertyResult_OK;
        }
        return PropertyResult_KeyNotFound;
    }

    virtual PropertyResult RemoveValue(PropertyID propID, const efd::utf8string& key)
    {
        EE_UNUSED_ARG(propID);

        typename AssocProcMap::iterator iterValues = m_data.find(key);
        if (iterValues != m_data.end())
        {
            m_data.erase(iterValues);
            return PropertyResult_OK;
        }

        return PropertyResult_KeyNotFound;
    }

    virtual IProperty* Clone() const
    {
        MyClassName* pProp = EE_NEW MyClassName();
        if (!pProp)
        {
            return NULL;
        }

        *pProp = *this;

        return pProp;
    }

    virtual PropertyResult GetValueAsString(
        PropertyID propID,
        const efd::utf8string& key,
        efd::utf8string& data) const
    {
        EE_UNUSED_ARG(propID);
        typename AssocProcMap::const_iterator iterValues = m_data.find(key);
        if (iterValues != m_data.end())
        {
            if (efd::ParseHelper<TType>::ToString(iterValues->second, data))
                return PropertyResult_OK;
            else
                return PropertyResult_TypeMismatch;
        }
        else
        {
            return PropertyResult_KeyNotFound;
        }
    }

    virtual PropertyResult SetValueByString(
        PropertyID propID,
        const efd::utf8string& key,
        const efd::utf8string& data)
    {
        TType temp;
        if (efd::ParseHelper<TType>::FromString(data, temp))
        {
            return SetValue(propID, key, &temp);
        }

        return PropertyResult_TypeMismatch;
    }

    virtual efd::ClassID GetPropertyType() const
    {
        return CLASS_ID;
    }

    virtual efd::ClassID GetDataType(PropertyID i_propID) const
    {
        EE_UNUSED_ARG(i_propID);
        return efd::GetClassIDFromType<TType>();
    }

    virtual PropertyResult GetPropertyCount(PropertyID i_propID, efd::UInt32& o_count) const
    {
        EE_UNUSED_ARG(i_propID);
        o_count = (efd::UInt32)m_data.size();
        return PropertyResult_OK;
    }

    virtual PropertyResult GetPropertyKeys(
        PropertyID i_propID,
        efd::list<efd::utf8string>& o_keys) const
    {
        EE_UNUSED_ARG(i_propID);
        o_keys.clear();
        for (typename AssocProcMap::const_iterator iter = m_data.begin();
            iter != m_data.end();
            ++iter)
        {
            o_keys.push_back(iter->first);
        }
        return PropertyResult_OK;
    }

    virtual PropertyResult GetNextPropertyKey(
        PropertyID i_propID,
        const efd::utf8string& i_previousKey,
        efd::utf8string& o_nextKey) const
    {
        EE_UNUSED_ARG(i_propID);
        typename AssocProcMap::const_iterator iter;
        if (i_previousKey.empty())
        {
            iter = m_data.begin();
        }
        else
        {
            iter = m_data.find(i_previousKey);
            if (iter == m_data.end())
            {
                return PropertyResult_KeyNotFound;
            }

            ++iter;
        }

        if (iter == m_data.end())
        {
            o_nextKey.clear();
            return PropertyResult_NoMoreKeys;
        }

        o_nextKey = iter->first;
        return PropertyResult_OK;
    }

    void SerializeProperty(PropertyID, efd::Archive& ar)
    {
        efd::SR_StdMap<>::Serialize(m_data, ar);
    }

    void AdvanceStream(PropertyID, efd::Archive& ar) const
    {
        EE_ASSERT(ar.IsUnpacking());
        AssocProcMap temp;
        efd::SR_StdMap<>::Serialize(temp, ar);
    }


#if defined(EE_MEMTRACKER_DETAILEDREPORTING)
    /// A constructor that registers a detailed memory leak reporting method for this instance.
    TPropertyAssoc()
    {
        EE_MEM_SETDETAILEDREPORT(this, MyClassName::LeakDump);
    }

    /// A leak dumping method for use in detailed memory reports. To enable detailed memory leak
    /// reporting recompile all source with the EE_USE_MEMTRACKER_DETAILEDREPORTING macro defined.
    /// See efd/MemTracker.h and efd/MemDefines.h for details.
    static void LeakDump(void* pMem, char* o_buffer, unsigned int i_cchBuffer)
    {
        MyClassName* pProp = reinterpret_cast<MyClassName*>(pMem);
        efd::Snprintf(o_buffer, i_cchBuffer, EE_TRUNCATE,
            "TPropertyAssoc<%s, 0x%08X>(size=%d)",
            efd::ParseHelper<TType>::GetNameOfType(),
            CLASS_ID,
            pProp->m_data.size());
    }
#endif

protected:
    typedef efd::map<efd::utf8string, TType> AssocProcMap;
    /// Storage for templated data as a map<efd::utf8string, TType>
    AssocProcMap m_data;
};


} // end namespace egf

#endif //EE_TPROPERTY_H
