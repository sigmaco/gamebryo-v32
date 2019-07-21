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

// This file contains helpers for the BuiltinModel helper helpers

namespace egf
{
    namespace BuiltinHelper
    {
        struct PropertyData : public efd::MemObject
        {
            virtual ~PropertyData() {}

            virtual PropertyResult Get(const IBuiltinModel* , void*) const
            {
                return PropertyResult_PropertyNotScalar;
            }
            virtual PropertyResult Set(IBuiltinModel*, const void*)
            {
                return PropertyResult_PropertyNotScalar;
            }
            virtual PropertyResult Get(const IBuiltinModel*, const efd::utf8string&, void*) const
            {
                return PropertyResult_PropertyNotAssociativeArray;
            }
            virtual PropertyResult Set(IBuiltinModel*, const efd::utf8string&, const void*)
            {
                return PropertyResult_PropertyNotAssociativeArray;
            }
            virtual PropertyResult GetAsString(const IBuiltinModel*, efd::utf8string&) const
            {
                return PropertyResult_PropertyNotScalar;
            }
            virtual PropertyResult SetByString(IBuiltinModel*, const efd::utf8string&)
            {
                return PropertyResult_PropertyNotScalar;
            }
            virtual PropertyResult GetAsString(
                const IBuiltinModel*,
                const efd::utf8string&,
                efd::utf8string&) const
            {
                return PropertyResult_PropertyNotAssociativeArray;
            }
            virtual PropertyResult SetByString(
                IBuiltinModel*,
                const efd::utf8string&,
                const efd::utf8string&)
            {
                return PropertyResult_PropertyNotAssociativeArray;
            }
            virtual PropertyResult SetDefault(IBuiltinModel*, const egf::PropertyDescriptor*)
            {
                return PropertyResult_ReadOnlyError;
            }
            virtual efd::ClassID GetType() const
            {
                return 0;
            }

            virtual PropertyResult GetKeyCount(const IBuiltinModel*, efd::UInt32&) const
            {
                return PropertyResult_PropertyNotAssociativeArray;
            }

            virtual PropertyResult GetKeys(const IBuiltinModel*, efd::list<efd::utf8string>&) const
            {
                return PropertyResult_PropertyNotAssociativeArray;
            }

            virtual PropertyResult GetNextPropertyKey(
                const IBuiltinModel*,
                const efd::utf8string&,
                efd::utf8string&) const
            {
                return PropertyResult_PropertyNotAssociativeArray;
            }

            virtual PropertyResult HasValue(const IBuiltinModel*, const efd::utf8string&) const
            {
                return PropertyResult_PropertyNotAssociativeArray;
            }

            virtual PropertyResult RemoveValue(IBuiltinModel*, const efd::utf8string&)
            {
                return PropertyResult_PropertyNotAssociativeArray;
            }

            virtual void Pack(const IBuiltinModel* pThis, efd::Archive& ar) const = 0;
            virtual void Unpack(IBuiltinModel* pThis, efd::Archive& ar) = 0;
            virtual void Skip(const IBuiltinModel* pThis, efd::Archive& ar) const = 0;

            // We want to share a single instance of each individual PropertyData across all
            // instances of the Built-in. We do this by storing the PropertyData as
            // smart pointers in a class-static map referenced by PropertyID. If a new
            // IBuiltinModelImpl is created with the same underlying built-in model properties,
            // we increment the reference count of the existing PropertyData rather than creating
            // a new instance.
            EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT
        };


        /**
            Accessor read-only property PropertyData for a Builtin model scalar property.

            @param CompClass The Builtin model C++ class name.
            @param NativeType The native type used for the property.
            @param ImplClass The class that implements this model if different from CompClass.
            @param pfnGet method to call for property Get.
        */
        template<
            typename CompClass,
            typename NativeType,
            typename ImplClass,
            NativeType (ImplClass::* pfnGet)() const >
        struct PropertyFetch_ReadOnlyAccessor : public PropertyData
        {
            PropertyResult Get(const IBuiltinModel* pThis, void* o_pData) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                *(NativeType*)o_pData = (pImpl->*pfnGet)();
                return PropertyResult_OK;
            }

            PropertyResult GetAsString(const IBuiltinModel* pThis, efd::utf8string& data) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                if (efd::ParseHelper<NativeType>::ToString((pImpl->*pfnGet)(), data))
                    return PropertyResult_OK;
                else
                    return PropertyResult_TypeMismatch;
            }

            efd::ClassID GetType() const
            {
                return efd::GetClassIDFromType<NativeType>();
            }

            void Pack(const IBuiltinModel* pThis, efd::Archive& ar) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                efd::Serializer::SerializeConstObject(
                    static_cast<NativeType>((pImpl->*pfnGet)()),
                    ar);
            }

            void Unpack(IBuiltinModel*, efd::Archive& ar)
            {
                // If your BuiltinModel is a view BuiltinModel then it really shouldn't be using a
                // read-only property.  Read-only properties are typically only valid for
                // owned entities.
                EE_FAIL("Read-only accessors not valid on replicated properties.");
                ar.RaiseError();
            }

            void Skip(const IBuiltinModel*, efd::Archive& ar) const
            {
                // If your BuiltinModel is a view BuiltinModel then it really shouldn't be using a
                // read-only property.  Read-only properties are typically only valid for
                // owned entities.
                EE_FAIL("Read-only accessors not valid on replicated properties.");
                ar.RaiseError();
            }
        };

        /**
            Accessor read-only property PropertyData for a Builtin model scalar property.
            This version gets properties by reference, not by value.

            @param CompClass The Builtin model C++ class name.
            @param NativeType The native type used for the property.
            @param ImplClass The class that implements this model if different from CompClass.
            @param pfnGet method to call for property Get.
        */
        template<
            typename CompClass,
            typename NativeType,
            typename ImplClass,
            const NativeType& (ImplClass::* pfnGet)() const >
        struct PropertyFetch_ReadOnlyAccessor_Ref : public PropertyData
        {
            PropertyResult Get(const IBuiltinModel* pThis, void* o_pData) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                *(NativeType*)o_pData = (pImpl->*pfnGet)();
                return PropertyResult_OK;
            }

            efd::ClassID GetType() const
            {
                return efd::GetClassIDFromType<NativeType>();
            }

            void Pack(const IBuiltinModel* pThis, efd::Archive& ar) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                efd::Serializer::SerializeConstObject(static_cast<NativeType>((pImpl->*pfnGet)()), ar);
            }

            void Unpack(IBuiltinModel*, efd::Archive& ar)
            {
                // If your BuiltinModel is a view BuiltinModel then it really shouldn't be using a
                // read-only property.  Read-only properties are typically only valid for
                // owned entities.
                EE_FAIL("Read-only accessors not valid on replicated properties.");
                ar.RaiseError();
            }

            void Skip(const IBuiltinModel*, efd::Archive& ar) const
            {
                // If your BuiltinModel is a view BuiltinModel then it really shouldn't be using a
                // read-only property.  Read-only properties are typically only valid for
                // owned entities.
                EE_FAIL("Read-only accessors not valid on replicated properties.");
                ar.RaiseError();
            }
        };

        /**
            Accessor read-write property PropertyData for a Built-in model scalar property.

            @param CompClass The Built-in model C++ class name.
            @param NativeType The native type used for the property.
            @param ImplClass The class that implements this model if different from CompClass.
            @param pfnGet method to call for property Get.
            @param pfnSet method to call for property Set.
        */
        template<
            typename CompClass,
            typename NativeType,
            typename ImplClass,
            NativeType (ImplClass::* pfnGet)() const,
            void (ImplClass::* pfnSet)(const NativeType&) >
        struct PropertyFetch_Accessors
            : public PropertyFetch_ReadOnlyAccessor< CompClass, NativeType, ImplClass, pfnGet >
        {
            PropertyResult Set(IBuiltinModel* pThis, const void* i_pData)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                (pImpl->*pfnSet)(*(const NativeType*)i_pData);
                return PropertyResult_OK;
            }

            PropertyResult SetByString(IBuiltinModel* pThis, const efd::utf8string& data)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                NativeType temp;
                if (efd::ParseHelper<NativeType>::FromString(data, temp))
                {
                    (pImpl->*pfnSet)(temp);
                    return PropertyResult_OK;
                }
                return PropertyResult_TypeMismatch;
            }

            PropertyResult SetDefault(IBuiltinModel* pThis, const PropertyDescriptor* pDesc)
            {
                NativeType data;
                const IProperty* pDefault = pDesc->GetDefaultProperty();
                pDefault->GetValue(pDesc->GetPropertyID(), &data);
                return Set(pThis, &data);
            }

            void Unpack(IBuiltinModel* pThis, efd::Archive& ar)
            {
                NativeType data;
                efd::Serializer::SerializeObject(data, ar);
                if (!ar.GetError())
                {
                    Set(pThis, &data);
                }
            }

            void Skip(const IBuiltinModel*, efd::Archive& ar) const
            {
                NativeType data;
                efd::Serializer::SerializeObject(data, ar);
            }
        };

        /**
            Accessor read-write property PropertyData for a Builtin model scalar property.
            This version gets properties by reference, not by value.

            @param CompClass The Builtin model C++ class name.
            @param NativeType The native type used for the property.
            @param ImplClass The class that implements this model if different from CompClass.
            @param pfnGet method to call for property Get.
            @param pfnSet method to call for property Set.
        */
        template<
            typename CompClass,
            typename NativeType,
            typename ImplClass,
            const NativeType& (ImplClass::* pfnGet)() const,
            void (ImplClass::* pfnSet)(const NativeType&) >
        struct PropertyFetch_Accessors_Ref
            : public PropertyFetch_ReadOnlyAccessor_Ref< CompClass, NativeType, ImplClass, pfnGet >
        {
            PropertyResult Set(IBuiltinModel* pThis, const void* i_pData)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                (pImpl->*pfnSet)(*(const NativeType*)i_pData);
                return PropertyResult_OK;
            }

            PropertyResult SetByString(IBuiltinModel* pThis, const efd::utf8string& data)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                NativeType temp;
                if (efd::ParseHelper<NativeType>::FromString(data, temp))
                {
                    (pImpl->*pfnSet)(temp);
                    return PropertyResult_OK;
                }
                return PropertyResult_TypeMismatch;
            }

            PropertyResult SetDefault(IBuiltinModel* pThis, const PropertyDescriptor* pDesc)
            {
                NativeType data;
                const IProperty* pDefault = pDesc->GetDefaultProperty();
                pDefault->GetValue(pDesc->GetPropertyID(), &data);
                return Set(pThis, &data);
            }

            void Unpack(IBuiltinModel* pThis, efd::Archive& ar)
            {
                NativeType data;
                efd::Serializer::SerializeObject(data, ar);
                if (!ar.GetError())
                {
                    Set(pThis, &data);
                }
            }

            void Skip(const IBuiltinModel*, efd::Archive& ar) const
            {
                NativeType data;
                efd::Serializer::SerializeObject(data, ar);
            }
        };


        /**
            Native read-only property PropertyData for a Builtin model scalar property.

            @param CompClass The Builtin model C++ class name.
            @param NativeType The native type used for the property.
            @param ImplClass The class that implements this model if different from CompClass.
            @param Member Pointer to the underlying class member variable, of type NativeType
        */
        template< typename CompClass,
                  typename NativeType,
                  typename ImplClass,
                  NativeType ImplClass::* Member >
        struct PropertyFetch_ReadOnlyNative : public PropertyData
        {
            PropertyResult Get(const IBuiltinModel* pThis, void* o_pData) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                *(NativeType*)o_pData = pImpl->*Member;
                return PropertyResult_OK;
            }

            PropertyResult GetAsString(const IBuiltinModel* pThis, efd::utf8string& data) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                if (efd::ParseHelper<NativeType>::ToString(pImpl->*Member, data))
                    return PropertyResult_OK;
                else
                    return PropertyResult_TypeMismatch;
            }

            PropertyResult SetDefault(IBuiltinModel* pThis, const egf::PropertyDescriptor* pDesc)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                const IProperty* pDefault = pDesc->GetDefaultProperty();
                pDefault->GetValue(pDesc->GetPropertyID(), &(pImpl->*Member));
                return PropertyResult_OK;
            }

            efd::ClassID GetType() const
            {
                return efd::GetClassIDFromType<NativeType>();
            }

            void Pack(const IBuiltinModel* pThis, efd::Archive& ar) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                efd::Serializer::SerializeConstObject(static_cast<NativeType>(pImpl->*Member), ar);
            }

            void Unpack(IBuiltinModel*, efd::Archive& ar)
            {
                // If your BuiltinModel is a view BuiltinModel then it really shouldn't be using a
                // read-only property.  Read-only properties are typically only valid for
                // owned entities.
                EE_FAIL("Read-only accessors not valid on replicated properties.");
                ar.RaiseError();
            }

            void Skip(const IBuiltinModel*, efd::Archive& ar) const
            {
                // If your BuiltinModel is a view BuiltinModel then it really shouldn't be using a
                // read-only property.  Read-only properties are typically only valid for
                // owned entities.
                EE_FAIL("Read-only accessors not valid on replicated properties.");
                ar.RaiseError();
            }
        };

        /**
            Native read-write property PropertyData for a Built-in model scalar property.

            @param CompClass The Built-in model C++ class name.
            @param NativeType The native type used for the property.
            @param ImplClass The class that implements this model if different from CompClass.
            @param Member Pointer to the underlying class member variable, of type NativeType.
        */
        template<
            typename CompClass,
            typename NativeType,
            typename ImplClass,
            NativeType ImplClass::* Member >
        struct PropertyFetch_Native
            : public PropertyFetch_ReadOnlyNative< CompClass, NativeType, ImplClass, Member >
        {
            PropertyResult Set(IBuiltinModel* pThis, const void* i_pData)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                pImpl->*Member = *(NativeType*)i_pData;
                return PropertyResult_OK;
            }

            PropertyResult SetByString(IBuiltinModel* pThis, const efd::utf8string& data)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                if (efd::ParseHelper<NativeType>::FromString(data, pImpl->*Member))
                {
                    return PropertyResult_OK;
                }
                return PropertyResult_TypeMismatch;
            }

            void Unpack(IBuiltinModel* pThis, efd::Archive& ar)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                efd::Serializer::SerializeObject(pImpl->*Member, ar);
            }
            void Skip(const IBuiltinModel*, efd::Archive& ar) const
            {
                NativeType temp;
                efd::Serializer::SerializeObject(temp, ar);
            }
        };

        /**
            Native read-only property PropertyData for a Builtin model associative array property.

            @param CompClass The Builtin model C++ class name.
            @param NativeType The native type used for the property.
            @param ImplClass The class that implements this model if different from CompClass.
            @param Member Pointer to the underlying class member variable, of type
                efd::map<efd::utf8string, NativeType>
        */
        template<
            typename CompClass,
            typename NativeType,
            typename ImplClass,
            efd::map<efd::utf8string, NativeType> ImplClass::* Member >
        struct AssocPropertyFetch_ReadOnlyNative : public PropertyData
        {
            virtual PropertyResult Get(const IBuiltinModel* pThis,
                                       const efd::utf8string& k,
                                       void* val) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                typename efd::map<efd::utf8string, NativeType>::const_iterator it =
                    (pImpl->*Member).find(k);

                if (it != (pImpl->*Member).end())
                {
                    *(NativeType*)val = it->second;
                    return PropertyResult_OK;
                }
                return PropertyResult_KeyNotFound;
            }

            virtual PropertyResult GetAsString(
                const IBuiltinModel* pThis,
                const efd::utf8string& key,
                efd::utf8string& data) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                typename efd::map<efd::utf8string, NativeType>::const_iterator it =
                    (pImpl->*Member).find(key);

                if (it != (pImpl->*Member).end())
                {
                    if (efd::ParseHelper<NativeType>::ToString(it->second, data))
                        return PropertyResult_OK;
                    else
                        return PropertyResult_TypeMismatch;
                }
                return PropertyResult_KeyNotFound;
            }

            efd::ClassID GetType() const
            {
                return efd::GetClassIDFromType<NativeType>();
            }

            virtual PropertyResult Set(IBuiltinModel*, const efd::utf8string&, const void*)
            {
                return PropertyResult_ReadOnlyError;
            }

            virtual PropertyResult SetByString(
                IBuiltinModel*,
                const efd::utf8string&,
                const efd::utf8string&)
            {
                return PropertyResult_ReadOnlyError;
            }

            virtual PropertyResult GetKeyCount(
                const IBuiltinModel* pThis,
                efd::UInt32& i_count) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                i_count = (pImpl->*Member).size();
                return PropertyResult_OK;
            }

            virtual PropertyResult GetKeys(
                const IBuiltinModel* pThis,
                efd::list<efd::utf8string>& i_keys) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);

                i_keys.clear();
                typename efd::map<efd::utf8string, NativeType>::const_iterator it =
                    (pImpl->*Member).begin();

                for (; it != (pImpl->*Member).end(); ++it)
                {
                    i_keys.push_back(it->first);
                }
                return PropertyResult_OK;
            }

            virtual PropertyResult GetNextPropertyKey(
                const IBuiltinModel* pThis,
                const efd::utf8string& prevKey,
                efd::utf8string& nextKey) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                nextKey = "";

                typename efd::map<efd::utf8string, NativeType>::const_iterator it =
                    (pImpl->*Member).begin();

                if (prevKey.empty())
                {
                    nextKey = it->first;
                    return PropertyResult_OK;
                }

                for (; it != (pImpl->*Member).end(); ++it)
                {
                    if (prevKey == it->first)
                    {
                        ++it;
                        if (it != (pImpl->*Member).end())
                        {
                            nextKey = it->first;
                            return PropertyResult_OK;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                return PropertyResult_OK;
            }

            virtual PropertyResult HasValue(
                const IBuiltinModel* pThis,
                const efd::utf8string& key) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                if (0 != (pImpl->*Member).count(key))
                {
                    return PropertyResult_OK;
                }
                return PropertyResult_KeyNotFound;
            }

            virtual PropertyResult RemoveValue(IBuiltinModel*, const efd::utf8string&)
            {
                return PropertyResult_ReadOnlyError;
            }

            void Pack(const IBuiltinModel* pThis, efd::Archive& ar) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                efd::Serializer::SerializeConstObject(
                    static_cast<efd::UInt32>((pImpl->*Member).size()),
                    ar);

                typename efd::map<efd::utf8string, NativeType>::const_iterator it =
                    (pImpl->*Member).begin();
                for (; it != (pImpl->*Member).end(); ++it)
                {
                    efd::Serializer::SerializeConstObject(
                        static_cast<const efd::utf8string>(it->first),
                        ar);
                    efd::Serializer::SerializeConstObject(static_cast<const NativeType>(it->second), ar);
                }
            }

            void Unpack(IBuiltinModel*, efd::Archive& ar)
            {
                // If your BuiltinModel is a view BuiltinModel then it really shouldn't be using a
                // read-only property.  Read-only properties are typically only valid for
                // owned entities.
                EE_FAIL("Read-only accessors not valid on replicated properties.");
                ar.RaiseError();
            }

            void Skip(const IBuiltinModel*, efd::Archive& ar) const
            {
                // If your BuiltinModel is a view BuiltinModel then it really shouldn't be using a
                // read-only property.  Read-only properties are typically only valid for
                // owned entities.
                EE_FAIL("Read-only accessors not valid on replicated properties.");
                ar.RaiseError();
            }
        };

        /**
            Native read-write property PropertyData for a Built-in model associative array property.

            @param CompClass The Built-in model C++ class name.
            @param NativeType The native type used for the property.
            @param ImplClass The class that implements this model if different from CompClass.
            @param Member Pointer to the underlying class member variable, of type
                efd::map<efd::utf8string, NativeType>
        */
        template<
            typename CompClass,
            typename NativeType,
            typename ImplClass,
            efd::map<efd::utf8string, NativeType> ImplClass::* Member >
        struct AssocPropertyFetch_Native :
            public AssocPropertyFetch_ReadOnlyNative<CompClass, NativeType, ImplClass, Member>
        {
            virtual PropertyResult Set(
                IBuiltinModel* pThis,
                const efd::utf8string& key,
                const void* val)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                (pImpl->*Member)[key] = *(NativeType*)val;
                return PropertyResult_OK;
            }

            virtual PropertyResult SetByString(
                IBuiltinModel* pThis,
                const efd::utf8string& sKey,
                const efd::utf8string& sVal)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);

                NativeType val;
                efd::ParseHelper<NativeType>::FromString(sVal.c_str(), val);

                (pImpl->*Member)[sKey] = val;
                return PropertyResult_OK;
            }

            PropertyResult SetDefault(IBuiltinModel* pThis, const PropertyDescriptor* pDesc)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                (pImpl->*Member).clear();

                const IProperty* pDefault = pDesc->GetDefaultProperty();

                efd::utf8string key;
                efd::utf8string prevKey = "";
                pDefault->GetNextPropertyKey(pDesc->GetPropertyID(), prevKey, key);
                while (!key.empty())
                {
                    NativeType val;
                    pDefault->GetValue(pDesc->GetPropertyID(), key, (void *)&val);

                    (pImpl->*Member)[key] = val;

                    prevKey = key;
                    pDefault->GetNextPropertyKey(pDesc->GetPropertyID(), prevKey, key);
                }
                return PropertyResult_OK;
            }

            virtual PropertyResult RemoveValue(IBuiltinModel* pThis, const efd::utf8string& key)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                if ((pImpl->*Member).find(key) == (pImpl->*Member).end())
                {
                    return PropertyResult_KeyNotFound;
                }
                (pImpl->*Member).erase(key);
                return PropertyResult_OK;
            }

            void Unpack(IBuiltinModel* pThis, efd::Archive& ar)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);

                efd::UInt32 count = 0;
                efd::Serializer::SerializeObject(count, ar);
                // Security check, if size is impossibly large don't sit here looping forever. Each
                // item is at least 2 bytes so there must be at least count*2 bytes left.
                if (count*2 > ar.GetRemainingSize())
                {
                    ar.RaiseError();
                    return;
                }

                // if the stream is already in an error state, don't clear the previous value.
                if (ar.GetError())
                    return;
                (pImpl->*Member).clear();

                for (efd::UInt32 i = 0; i < count; ++i)
                {
                    efd::utf8string key;
                    NativeType val;

                    efd::Serializer::SerializeObject(key, ar);
                    efd::Serializer::SerializeObject(val, ar);
                    if (ar.GetError())
                        return;
                    (pImpl->*Member)[key] = val;
                }
            }

            void Skip(const IBuiltinModel*, efd::Archive& ar) const
            {
                efd::UInt32 count = 0;
                efd::Serializer::SerializeObject(count, ar);
                // Security check, if size is impossibly large don't sit here looping forever. Each
                // item is at least 2 bytes so there must be at least count*2 bytes left.
                if (count*2 > ar.GetRemainingSize())
                    return;
                for (efd::UInt32 i = 0; i < count; ++i)
                {
                    efd::utf8string key;
                    NativeType val;

                    efd::Serializer::SerializeObject(key, ar);
                    efd::Serializer::SerializeObject(val, ar);
                }
            }
        };

        /**
            Accessor read-only property PropertyData for a Builtin model associative array property.

            @param CompClass The Builtin model C++ class name.
            @param NativeType The native type used for the property.
            @param ImplClass The class that implements this model if different from CompClass.
            @param pfnGet function called to get a value from the associative array.
            @param pfnCount function called to get the associative array size.
            @param pfnGetNextPropertyKey function called to get the next property key given
                the previous key. @see egf::Entity::GetNextPropertyKey.
        */
        template<
            typename CompClass,
            typename NativeType,
            typename ImplClass,
            egf::PropertyResult (ImplClass::* pfnGet)(const efd::utf8string&, NativeType&) const,
            efd::UInt32 (ImplClass::* pfnCount)() const,
            void (ImplClass::* pfnGetNextPropertyKey)(
                const efd::utf8string&, efd::utf8string&) const >
        struct AssocPropertyFetch_ReadOnlyAccessor : public PropertyData
        {
            virtual egf::PropertyResult Get(
                const IBuiltinModel* pThis,
                const efd::utf8string& key,
                void* val) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                return (pImpl->*pfnGet)(key, *(static_cast<NativeType*>(val)));
            }

            virtual PropertyResult GetAsString(
                const IBuiltinModel* pThis,
                const efd::utf8string& key,
                efd::utf8string& data) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                NativeType value;
                PropertyResult result = (pImpl->*pfnGet)(key, value);
                if (result == PropertyResult_OK)
                {
                    if (efd::ParseHelper<NativeType>::ToString(value, data))
                        return PropertyResult_OK;
                    else
                        return PropertyResult_TypeMismatch;
                }
                return result;
            }

            efd::ClassID GetType() const
            {
                return efd::GetClassIDFromType<NativeType>();
            }

            virtual PropertyResult Set(IBuiltinModel*, const efd::utf8string&, const void*)
            {
                return PropertyResult_ReadOnlyError;
            }

            virtual PropertyResult SetByString(
                IBuiltinModel*,
                const efd::utf8string&,
                const efd::utf8string&)
            {
                return PropertyResult_ReadOnlyError;
            }

            virtual PropertyResult GetKeyCount(
                const IBuiltinModel* pThis,
                efd::UInt32& i_count) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                i_count = (pImpl->*pfnCount)();
                return PropertyResult_OK;
            }

            virtual PropertyResult GetKeys(
                const IBuiltinModel* pThis,
                efd::list<efd::utf8string>& i_keys) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);

                i_keys.clear();
                efd::utf8string k;
                (pImpl->*pfnGetNextPropertyKey)("", k);
                while (!k.empty())
                {
                    i_keys.push_back(k);
                    (pImpl->*pfnGetNextPropertyKey)(k, k);
                }
                return PropertyResult_OK;
            }

            virtual PropertyResult GetNextPropertyKey(
                const IBuiltinModel* pThis,
                const efd::utf8string& prevKey,
                efd::utf8string& nextKey) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);
                (pImpl->*pfnGetNextPropertyKey)(prevKey, nextKey);
                return PropertyResult_OK;
            }

            void Pack(const IBuiltinModel* pThis, efd::Archive& ar) const
            {
                efd::UInt32 count;
                GetKeyCount(pThis, count);
                efd::Serializer::SerializeObject(count, ar);

                efd::list<efd::utf8string> keys;
                GetKeys(pThis, keys);

                efd::list<efd::utf8string>::const_iterator it = keys.begin();
                for (; it != keys.end(); ++it)
                {
                    NativeType val;
                    Get(pThis, *it, (void *)&val);

                    efd::Serializer::SerializeConstObject(*it, ar);
                    efd::Serializer::SerializeObject(val, ar);
                }
            }
        };

        /**
            Accessor read-write PropertyData for a Builtin model associative array property.

            @param CompClass The Builtin model C++ class name.
            @param NativeType The native type used for the property.
            @param ImplClass The class that implements this model if different from CompClass.
            @param pfnGet function called to get a value from the associative array.
            @param pfnCount function called to get the associative array size.
            @param pfnGetNextKey function called to get the next property key given
                the previous key. @see egf::Entity::GetNextPropertyKey.
            @param pfnClear function called to clear the associative array.
            @param pfnRemoveValue function called to remove a value from the associative array.
        */
        template<
            typename CompClass,
            typename NativeType,
            typename ImplClass,
            egf::PropertyResult (ImplClass::* pfnGet)(const efd::utf8string&, NativeType&) const,
            void (ImplClass::* pfnSet)(const efd::utf8string& , const NativeType&),
            efd::UInt32 (ImplClass::* pfnCount)() const,
            void (ImplClass::* pfnGetNextKey)(const efd::utf8string&, efd::utf8string&) const,
            void (ImplClass::* pfnClear)(),
            egf::PropertyResult (ImplClass::* pfnRemoveValue)(const efd::utf8string&) >
        struct AssocPropertyFetch_Accessors
            : public AssocPropertyFetch_ReadOnlyAccessor< CompClass, NativeType,
                ImplClass, pfnGet, pfnCount, pfnGetNextKey >
        {
            virtual PropertyResult Set(
                IBuiltinModel* pThis,
                const efd::utf8string& key,
                const void* val)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                (pImpl->*pfnSet)(key, *(const NativeType*)val);
                return PropertyResult_OK;
            }

            virtual PropertyResult SetByString(
                IBuiltinModel* pThis,
                const efd::utf8string& key,
                const efd::utf8string& val)
            {
                NativeType v;
                efd::ParseHelper<NativeType>::FromString(val, v);

                ImplClass* pImpl = static_cast<CompClass*>(pThis);

                (pImpl->*pfnSet)(key, v);
                return PropertyResult_OK;
            }

            virtual PropertyResult SetDefault(
                IBuiltinModel* pThis,
                const egf::PropertyDescriptor* pDesc)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);

                // clear the existing associative array
                (pImpl->*pfnClear)();

                const IProperty* pDefault = pDesc->GetDefaultProperty();

                efd::utf8string key;
                efd::utf8string prevKey = "";
                pDefault->GetNextPropertyKey(pDesc->GetPropertyID(), prevKey, key);
                while (!key.empty())
                {
                    NativeType val;
                    pDefault->GetValue(pDesc->GetPropertyID(), key, (void *)&val);

                    Set(pThis, key, (void *)&val);

                    prevKey = key;
                    pDefault->GetNextPropertyKey(pDesc->GetPropertyID(), prevKey, key);
                }
                return PropertyResult_OK;
            }

            virtual PropertyResult HasValue(
                const IBuiltinModel* pThis,
                const efd::utf8string& key) const
            {
                const ImplClass* pImpl = static_cast<const CompClass*>(pThis);

                NativeType v;
                return (pImpl->*pfnGet)(key, v);
            }

            virtual PropertyResult RemoveValue(IBuiltinModel* pThis, const efd::utf8string& key)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);
                return (pImpl->*pfnRemoveValue)(key);
            }

            void Unpack(IBuiltinModel* pThis, efd::Archive& ar)
            {
                ImplClass* pImpl = static_cast<CompClass*>(pThis);

                efd::UInt32 count = 0;
                efd::Serializer::SerializeObject(count, ar);
                // Security check, if size is impossibly large don't sit here looping forever. Each
                // item is at least 2 bytes so there must be at least count*2 bytes left.
                if (count*2 > ar.GetRemainingSize())
                {
                    ar.RaiseError();
                    return;
                }

                // if the stream is already in an error state, don't clear the previous value.
                if (ar.GetError())
                    return;
                (pImpl->*pfnClear)();

                for (efd::UInt32 i = 0; i < count; ++i)
                {
                    efd::utf8string key;
                    NativeType val;
                    efd::Serializer::SerializeObject(key, ar);
                    efd::Serializer::SerializeObject(val, ar);
                    if (ar.GetError())
                        return;
                    (pImpl->*pfnSet)(key, val);
                }
            }

            void Skip(const IBuiltinModel*, efd::Archive& ar) const
            {
                efd::UInt32 count;
                efd::Serializer::SerializeObject(count, ar);
                // Security check, if size is impossibly large don't sit here looping forever. Each
                // item is at least 2 bytes so there must be at least count*2 bytes left.
                if (count*2 > ar.GetRemainingSize())
                {
                    ar.RaiseError();
                    return;
                }

                for (efd::UInt32 i = 0; i < count; ++i)
                {
                    efd::utf8string key;
                    NativeType val;
                    efd::Serializer::SerializeObject(key, ar);
                    efd::Serializer::SerializeObject(val, ar);
                }
            }
        };
    } // end namespace BuiltinHelper
} // end namespace egf
