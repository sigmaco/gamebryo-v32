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
#ifndef EE_BUILTINMODELHELPER_H
#define EE_BUILTINMODELHELPER_H

#include <egf/IBuiltinModelImpl.h>


/** @file BuiltinModelHelper.h

    This file contains helpers to make implementing a built-in model easier.

    You can use this to implement IBuiltinModel methods and bind properties and methods.  The
    result will be a map based lookup from static data every time a built-in model method is
    invoked.

    @code
    class MyBuiltinModel : public IBuiltinModelImpl
    {
        EE_DECLARE_BUILTINMODEL_PROPERTIES
            // for types natively supported as IProperties you can directly bind the type:
            EE_BUILTINMODELPROPERTY(MyBuiltinModel, kPropID_Foo, UInt32, MyBuiltinModel, m_foo)
            EE_BUILTINMODELPROPERTY_READONLY(MyBuiltinModel, kPropID_Bar, Float32, MyBuiltinModel, m_bar)
            EE_BUILTINMODELPROPERTY(MyBuiltinModel, kPropID_Velocity, Vector3, MyBuiltinModel, m_velocity)

            // If you have standard get and set methods you can export these as if they are a property:
            // These macros return the property by value.
            EE_BUILTINMODELPROPERTY_ACCESSOR(MyBuiltinModel, kPropID_X, Float32, MyBuiltinModel, GetX, SetX)
            // You can export read-only properties that are potentially computed values:
            EE_BUILTINMODELPROPERTY_READONLY_ACCESSOR(MyBuiltinModel, kPropID_Normalized, bool, MyBuiltinModel, IsNormalized)

            // You can also return values by const reference.
            EE_BUILTINMODELPROPERTY_ACCESSOR_REF(MyBuiltinModel, kPropID_name, utf8string, MyBuiltinModel, GetName, SetName)
            // You can export read-only properties by reference. Make sure not to return local temporaries in these methods.
            EE_BUILTINMODELPROPERTY_READONLY_ACCESSOR_REF(MyBuiltinModel, kPropID_SSID, utf8string, MyBuiltinModel, GetSSID)

            // for associative array types using efd::map, you can directly bind to the type:
            EE_BUILTINMODELASSOCPROPERTY(MyBuiltinModel, kPropID_array, Float32, MyBuiltinModel, m_array)
            EE_BUILTINMODELASSOCPROPERTY_READONLY(MyBuiltinModel, kPropID_ROArray, UInt32, MyBuiltinModel, m_roArray)

            // If your associative array does not use efd::map, or you want fine-grained control
            // over the way your associative array is access, you can define the property so
            // it uses accessors.
            EE_BUILTINMODELASSOCPROPERTY_ACCESSOR(MyBuiltinModel, kPropID_arrayAccessor, utf8string,
                MyBuiltinModel, Get, Set, KeyCount,GetNextPropertyKey, Clear, RemovePropertyValue)

        EE_END_BUILTINMODEL_PROPERTIES

        EE_DECLARE_NO_BEHAVIORS

    public:
        Float32 GetX() const
        {
            return m_velocity.x;
        }
        void SetX(const Float32& x)
        {
            m_velocity.x = x;
        }

        const utf8string& GetName() const
        {
            return m_name;
        }

        void SetName(const utf8string& name)
        {
            m_name = name;
        }

        const utf8string& GetSSID() const
        {
            return m_SSID;
        }

        bool IsNormalized() const
        {
            return m_velocity.IsNormalized();
        }

        // Accessor 'Get' method for an associative array
        PropertyResult Get(const efd::utf8string& key, efd::utf8string& val) const
        {
            PropertyResult r = PropertyResult_OK;
            efd::map<efd::utf8string, efd::utf8string>::const_iterator it = m_arrayAccessor.find(key);
            if (it != m_arrayAccessor.end())
            {
                val = it->second;
            }
            else
            {
                r = PropertyResult_KeyNotFound;
            }
            return r;
        }

        // Accessor 'Set' method for an associative array
        void Set(const efd::utf8string& key, const efd::utf8string& val)
        {
            m_arrayAccessor[key] = val;
        }

        // Accessor 'KeyCount' method for an associative array
        efd::UInt32 KeyCount() const
        {
            return m_arrayAccessor.size();
        }

        // Accessor 'Clear' method for an associative array
        void Clear()
        {
            m_arrayAccessor.clear();
        }

        // Accessor 'GetNextKey' method for an associative array
        void GetNextKey(const efd::utf8string& prevKey, efd::utf8string& nextKey) const
        {
            efd::map<efd::utf8string, efd::utf8string>::const_iterator it = m_arrayAccessor.begin();
            if (prevKey.empty())
            {
            nextKey = it->first;
            return;
            }

            for (; it != m_arrayAccessor.end(); ++it)
            {
                if (prevKey == it->first)
                {
                    ++it;
                    if (it != m_arrayAccessor.end())
                    {
                        nextKey = it->first;
                        return;
                    }
                    else
                    {
                        nextKey = "";
                        return;
                    }
                }
            }
        }

        // Accessor 'RemovePropertyValue' method for an associative array.
        PropertyResult RemovePropertyValue(const efd::utf8string& key)
        {
            PropertyResult r = PropertyResult_OK;
            if (m_arrayAccessor.find(key) != m_arrayAccessor.end())
            {
                m_arrayAccessor.erase(key);
            }
            else
            {
                r = PropertyResult_KeyNotFound;
            }
            return r;
        }

    private:
        UInt32 m_foo;
        Float32 m_bar;
        Vector3 m_velocity;
        utf8string m_name;
        utf8string m_SSID;
        efd::map<efd::utf8string, efd::Float32> m_array;
        const efd::map<efd::utf8string, efd::UInt32> m_roArray;
        efd::map<efd::utf8string, efd::utf8string> m_arrayAccessor;
    };
    @endcode

    In your .cpp, make sure to add the EE_IMPLEMENT_BUILTINMODEL_PROPERTIES macro
    to correctly initialize the builtin model property map. e.g.

    @code
    EE_IMPLEMENT_BUILTINMODEL_PROPERTIES(MyBuiltinModel);
    @endcode
*/


/**
    @def EE_DECLARE_BUILTINMODEL_PROPERTIES

    Used to begin a block of built-in model property bindings.  This declares the static methods
    that are needed to implement the built-in model.  You must end the block of property defines
    using the EE_END_BUILTINMODEL_PROPERTIES macro. You must also add the implementation macro
    EE_IMPLEMENT_BUILTINMODEL_PROPERTIES to your .cpp file.

    We don't use SDM here because we would have to remember to add every Builtin Model class
    to the SDM init chain. Instead, we'll manage the life time of each IBuiltinModelImpl instance
    such that we initialize and clean up our static data in the correct order. This will only
    work if you derive your builtin model classes from efd::BuiltinModelImpl or you call
    InitializePropertyMap in your constructor and ReleasePropertyMap in your destructor.
*/
#define EE_DECLARE_BUILTINMODEL_PROPERTIES                                                      \
private:                                                                                        \
    static egf::BuiltinModelPropertyMap ms_propertyMap;                                         \
public:                                                                                         \
    virtual const egf::BuiltinModelPropertyMap& GetPropertyMap() const                          \
    {                                                                                           \
        if (ms_propertyMap.empty())                                                             \
        {                                                                                       \
            egf::BuiltinModelPropertyMap& map = ms_propertyMap;                                 \


/**
    @def EE_BUILTINMODELPROPERTY

    Declares a simple read-write property who's native storage type exactly matches the underlying
    IProperty type.

    @param FinalClass the class being defined.  This is the final IBuiltinModel implementation
    @param name the name of the property you are binding (expressed as its PropertyID)
    @param Type the C++ data type for the storage.  This must be both the type used to store
        the actual data and must also be a valid IProperty type.  The default values of all
        properties including built-in model properties are held in IProperty implementations so
        this requirement exists to support initialization from default properties.  If you
        are using a custom type you can create the required IProperty wrapper using the macros
        defined in TProperty.h.
    @param ImplClass This is the class that actually contains the variable being bound.  This
        class can be the same as FinalClass if you are not inheriting an implementation, otherwise
        it must be a base class of FinalClass.  This allows the IBuiltinModel implementation to
        simply derive from existing classes containing the desired variable.
    @param var the name of the variable that is being bound.  It must be of type 'Type'.
*/
#define EE_BUILTINMODELPROPERTY(FinalClass, name, Type, ImplClass, var) \
    map[ name ] = EE_NEW egf::BuiltinHelper::PropertyFetch_Native< FinalClass, Type, \
        ImplClass, &ImplClass::var >();


/**
    @def EE_BUILTINMODELASSOCPROPERTY

    Declares a simple read-write associative array property.

    @param FinalClass the class being defined.  This is the final IBuiltinModel implementation.
    @param name the name of the property you are binding (expressed as its PropertyID)
    @param Type the C++ data type for the storage.  The IProperty type is constructed
        from this type using the preprocessor. For example, an associative array with
        UInt32 values will have an IProperty type of 'UInt32AssocProperty'. The default values of
        all properties including built-in model properties are held in IProperty implementations so
        this requirement exists to support initialization from default properties.  If you
        are using a custom type you can create the required IProperty wrapper using the macros
        defined in TProperty.h.
    @param ImplClass This is the class that actually contains the variable being bound.  This
        class can be the same as FinalClass if you are not inheriting an implementation, otherwise
        it must be a base class of FinalClass.  This allows the IBuiltinModel implementation to
        simply derive from existing classes containing the desired variable.
    @param var the name of the variable that is being bound.  It must be of type
        'efd::map<efd::utf8string, Type>'
*/
#define EE_BUILTINMODELASSOCPROPERTY(FinalClass, name, Type, ImplClass, var) \
    map[ name ] = EE_NEW egf::BuiltinHelper::AssocPropertyFetch_Native< FinalClass, Type, \
        ImplClass, &ImplClass::var >();



/**
    @def EE_BUILTINMODELPROPERTY_READONLY

    Declares a simple read-only property who's native storage type exactly matches the underlying
    IProperty type.

    @param FinalClass the class being defined.  This is the final IBuiltinModel implementation
    @param name the name of the property you are binding (expressed as its PropertyID)
    @param Type the C++ data type for the storage.  This must be both the type used to store
        the actual data and must also be a valid IProperty type.  The default values of all
        properties including built-in model properties are held in IProperty implementations so
        this requirement exists to support initialization from default properties.  If you
        are using a custom type you can create the required IProperty wrapper using the macros
        defined in TProperty.h.
    @param ImplClass This is the class that actually contains the variable being bound.  This
        class can be the same as FinalClass if you are not inheriting an implementation, otherwise
        it must be a base class of FinalClass.  This allows the IBuiltinModel implementation to
        simply derive from existing classes containing the desired variable.
    @param var the name of the variable that is being bound.  It must be of type 'Type'.
*/
#define EE_BUILTINMODELPROPERTY_READONLY(FinalClass, name, Type, ImplClass, var) \
    map[ name ] = EE_NEW egf::BuiltinHelper::PropertyFetch_ReadOnlyNative< FinalClass, Type, \
        ImplClass, &ImplClass::var >();


/**
    @def EE_BUILTINMODELASSOCPROPERTY_READONLY

    Declares a simple read-only associative array property.

    @param FinalClass the class being defined.  This is the final IBuiltinModel implementation.
    @param name the name of the property you are binding (expressed as its PropertyID)
    @param Type the C++ data type for the storage.  The IProperty type is constructed
        from this type using the preprocessor. For example, an associative array with
        UInt32 values will have an IProperty type of 'UInt32AssocProperty'. The default values of
        all properties including built-in model properties are held in IProperty implementations so
        this requirement exists to support initialization from default properties.  If you
        are using a custom type you can create the required IProperty wrapper using the macros
        defined in TProperty.h.
    @param ImplClass This is the class that actually contains the variable being bound.  This
        class can be the same as FinalClass if you are not inheriting an implementation, otherwise
        it must be a base class of FinalClass.  This allows the IBuiltinModel implementation to
        simply derive from existing classes containing the desired variable.
    @param var the name of the variable that is being bound.  It must be of type
        'efd::map<efd::utf8string, Type>'
*/
#define EE_BUILTINMODELASSOCPROPERTY_READONLY(FinalClass, name, Type, ImplClass, var) \
    map[ name ] = EE_NEW egf::BuiltinHelper::AssocPropertyFetch_ReadOnlyNative< FinalClass, \
        Type, ImplClass, &ImplClass::var >();



/**
    @def EE_BUILTINMODELPROPERTY_ACCESSOR

    Declares a read-write property which is implemented as two accessor functions.  These
    accessors must have a specific format:

        Type YourGettorFunctionNameHere() const;
        void YourSettorFunctionNameHere(const Type&);

    Pay special attention to the use of 'const', improper const-correctness is a common error
    which often leads to confusing error messages from many compilers.

    @param FinalClass the class being defined.  This is the final IBuiltinModel implementation
    @param name the name of the property you are binding (expressed as its PropertyID)
    @param Type the C++ data type for the storage.  This must be both the type used by the
        accessor methods and must also be a valid IProperty type.  The default values of all
        properties including built-in model properties are held in IProperty implementations so
        this requirement exists to support initialization from default properties.  If you
        are using a custom type you can create the required IProperty wrapper using the macros
        defined in TProperty.h.
    @param ImplClass This is the class that actually contains the methods being bound.  This
        class can be the same as FinalClass if you are not inheriting an implementation, otherwise
        it must be a base class of FinalClass.  This allows the IBuiltinModel implementation to
        simply derive from existing classes containing the desired methods.
    @param pfnGet the name of the method that is called to get the value.
    @param pfnSet the name of the method that is called to set the value.
*/
#define EE_BUILTINMODELPROPERTY_ACCESSOR(FinalClass, name, Type, ImplClass, pfnGet, pfnSet) \
    map[ name ] = EE_NEW egf::BuiltinHelper::PropertyFetch_Accessors< FinalClass, Type, \
        ImplClass, &ImplClass::pfnGet, &ImplClass::pfnSet >();

/**
    @def EE_BUILTINMODELPROPERTY_ACCESSOR_REF

    Declares a read-write property which is implemented as two accessor functions.  These
    accessors must have a specific format:

    const Type& YourGettorFunctionNameHere() const;
    void YourSettorFunctionNameHere(const Type&);

    Pay special attention to the use of 'const', improper const-correctness is a common error
    which often leads to confusing error messages from many compilers.

    @param FinalClass the class being defined.  This is the final IBuiltinModel implementation
    @param name the name of the property you are binding (expressed as its PropertyID)
    @param Type the C++ data type for the storage.  This must be both the type used by the
    accessor methods and must also be a valid IProperty type.  The default values of all
    properties including built-in model properties are held in IProperty implementations so
    this requirement exists to support initialization from default properties.  If you
    are using a custom type you can create the required IProperty wrapper using the macros
    defined in TProperty.h.
    @param ImplClass This is the class that actually contains the methods being bound.  This
    class can be the same as FinalClass if you are not inheriting an implementation, otherwise
    it must be a base class of FinalClass.  This allows the IBuiltinModel implementation to
    simply derive from existing classes containing the desired methods.
    @param pfnGet the name of the method that is called to get the value.
    @param pfnSet the name of the method that is called to set the value.
*/
#define EE_BUILTINMODELPROPERTY_ACCESSOR_REF(FinalClass, name, Type, ImplClass, pfnGet, pfnSet) \
    map[ name ] = EE_NEW egf::BuiltinHelper::PropertyFetch_Accessors_Ref< FinalClass, Type, \
    ImplClass, &ImplClass::pfnGet, &ImplClass::pfnSet >();


/**
    @def EE_BUILTINMODELASSOCPROPERTY_ACCESSOR

    Declares a read-write associative array property which is implemented as six accessor 
    functions. These accessors must have a specific format:

        PropertyResult YourGettorFunctionNameHere(const efd::utf8string& key, Type& val) const;
        void YourSettorFunctionNameHere(const efd::utf8string& key, const Type& val);
        efd::UInt32 YourGetKeyCountFunctionNameHere() const;
        void YourClearArrayFunctionNameHere();
        void YourGetNextKeyFunctionNameHere(const efd::utf8string& prevKey,
                                            efd::utf8string& nextKey) const;
        PropertyResult YourRemovePropertyValueFunctionNameHere(const efd::utf8string& key);

    Pay special attention to the use of 'const', improper const-correctness is a common error
    which often leads to confusing error messages from many compilers.

    @param FinalClass the class being defined.  This is the final IBuiltinModel implementation
    @param name the name of the property you are binding (expressed as its PropertyID)
    @param Type the C++ data type for the storage.  The IProperty type is constructed
    from this type using the preprocessor. For example, an associative array with
    UInt32 values will have an IProperty type of 'UInt32AssocProperty'. The default values of
    all properties including built-in model properties are held in IProperty implementations so
    this requirement exists to support initialization from default properties.  If you
    are using a custom type you can create the required IProperty wrapper using the macros
    defined in TProperty.h.
    @param ImplClass This is the class that actually contains the methods being bound.  This
        class can be the same as FinalClass if you are not inheriting an implementation, otherwise
        it must be a base class of FinalClass.  This allows the IBuiltinModel implementation to
        simply derive from existing classes containing the desired methods.
    @param pfnGet the name of the method that is called to get the value.
    @param pfnSet the name of the method that is called to set the value.
    @param pfnCount the name of the method that is called to get the array size / entry count.
    @param pfnGetNextKey the name of the method that is called to get the next associative array
    key. @see egf::Entity::GetNextPropertyKey.
    @param pfnClear the name of the method that is called to clear the associative array.
    @param pfnRemoveValue the name of the method that is called to remove an entry from the
    associative array.
*/
#define EE_BUILTINMODELASSOCPROPERTY_ACCESSOR(FinalClass, name, Type, ImplClass, pfnGet, pfnSet, \
        pfnCount, pfnGetNextKey, pfnClear, pfnRemoveValue) \
    map[ name ] = EE_NEW egf::BuiltinHelper::AssocPropertyFetch_Accessors< FinalClass, Type, \
        ImplClass, &ImplClass::pfnGet, &ImplClass::pfnSet, &ImplClass::pfnCount, \
        &ImplClass::pfnGetNextKey, &ImplClass::pfnClear, &ImplClass::pfnRemoveValue >();

/**
    @def EE_BUILTINMODELPROPERTY_READONLY_ACCESSOR

    Declares a read-only property which is implemented as an accessor function.  This
    accessors must have a specific format:

        Type YourGettorFunctionNameHere() const;

    Pay special attention to the use of 'const', improper const-correctness is a common error
    which often leads to confusing error messages from many compilers.

    @param FinalClass the class being defined.  This is the final IBuiltinModel implementation
    @param name the name of the property you are binding (expressed as its PropertyID)
    @param Type the C++ data type for the storage.  This must be both the type used by the
        accessor methods and must also be a valid IProperty type.  The default values of all
        properties including built-in model properties are held in IProperty implementations so
        this requirement exists to support initialization from default properties.  If you
        are using a custom type you can create the required IProperty wrapper using the macros
        defined in TProperty.h.
    @param ImplClass This is the class that actually contains the methods being bound.  This
        class can be the same as FinalClass if you are not inheriting an implementation, otherwise
        it must be a base class of FinalClass.  This allows the IBuiltinModel implementation to
        simply derive from existing classes containing the desired methods.
    @param pfnGet the name of the method that is called to get the value.
*/
#define EE_BUILTINMODELPROPERTY_READONLY_ACCESSOR(FinalClass, name, Type, ImplClass, pfnGet) \
    map[ name ] = EE_NEW egf::BuiltinHelper::PropertyFetch_ReadOnlyAccessor< FinalClass, Type,\
        ImplClass, &ImplClass::pfnGet >();

/**
    @def EE_BUILTINMODELPROPERTY_READONLY_ACCESSOR_REF

    Declares a read-only property which is implemented as an accessor function.  This
    accessors must have a specific format:

    const Type& YourGettorFunctionNameHere() const;

    Pay special attention to the use of 'const', improper const-correctness is a common error
    which often leads to confusing error messages from many compilers.

    @param FinalClass the class being defined.  This is the final IBuiltinModel implementation
    @param name the name of the property you are binding (expressed as its PropertyID)
    @param Type the C++ data type for the storage.  This must be both the type used by the
    accessor methods and must also be a valid IProperty type.  The default values of all
    properties including built-in model properties are held in IProperty implementations so
    this requirement exists to support initialization from default properties.  If you
    are using a custom type you can create the required IProperty wrapper using the macros
    defined in TProperty.h.
    @param ImplClass This is the class that actually contains the methods being bound.  This
    class can be the same as FinalClass if you are not inheriting an implementation, otherwise
    it must be a base class of FinalClass.  This allows the IBuiltinModel implementation to
    simply derive from existing classes containing the desired methods.
    @param pfnGet the name of the method that is called to get the value.
*/
#define EE_BUILTINMODELPROPERTY_READONLY_ACCESSOR_REF(FinalClass, name, Type, ImplClass, pfnGet) \
    map[ name ] = EE_NEW egf::BuiltinHelper::PropertyFetch_ReadOnlyAccessor_Ref< \
        FinalClass, Type, ImplClass, &ImplClass::pfnGet >();

/**
    @def EE_BUILTINMODELASSOCPROPERTY_READONLY_ACCESSOR

    Declares a read-write associative array property which is implemented as three accessor 
    functions. These accessors must have a specific format:

        Type YourGettorFunctionNameHere() const;
        efd::UInt32 YourGetKeyCountFunctionNameHere() const;
        void YourGetNextKeyFunctionNameHere(const efd::utf8string& prevKey,
                                            efd::utf8string& nextKey) const;

    Pay special attention to the use of 'const', improper const-correctness is a common error
    which often leads to confusing error messages from many compilers.

    @param FinalClass the class being defined.  This is the final IBuiltinModel implementation
    @param name the name of the property you are binding (expressed as its PropertyID)
    @param Type the C++ data type for the storage.  The IProperty type is constructed
    from this type using the preprocessor. For example, an associative array with
    UInt32 values will have an IProperty type of 'UInt32AssocProperty'. The default values of
    all properties including built-in model properties are held in IProperty implementations so
    this requirement exists to support initialization from default properties.  If you
    are using a custom type you can create the required IProperty wrapper using the macros
    defined in TProperty.h.
    @param ImplClass This is the class that actually contains the methods being bound.  This
        class can be the same as FinalClass if you are not inheriting an implementation, otherwise
        it must be a base class of FinalClass.  This allows the IBuiltinModel implementation to
        simply derive from existing classes containing the desired methods.
    @param pfnGet the name of the method that is called to get the value.
    @param pfnCount the name of the method that is called to get the array size / entry count.
    @param pfnGetNextKey the name of the method that is called to get the next associative array
    key. This follows the same convention as egf::Entity::GetNextPropertyKey.
*/
#define EE_BUILTINMODELASSOCPROPERTY_READONLY_ACCESSOR(FinalClass, name, Type, ImplClass, \
        pfnGet, pfnCount, pfnGetNextKey) \
    map[ name ] = EE_NEW egf::BuiltinHelper::AssocPropertyFetch_ReadOnlyAccessor< FinalClass, \
        Type, ImplClass, &ImplClass::pfnGet, &ImplClass::pfnCount, &ImplClass::pfnGetNextKey >();


/**
    @def EE_END_BUILTINMODEL_PROPERTIES

    Used to terminate a built-in model property declaration block.  Every use of
    EE_DECLARE_BUILTINMODEL_PROPERTIES must end with a call to this macro.
*/
#define EE_END_BUILTINMODEL_PROPERTIES                                                          \
            if (!ms_propertyMap.empty())                                                        \
            {                                                                                   \
                egf::BuiltinModelStaticMapCleaner::CleanMapAtSDMShutdown(ms_propertyMap);       \
            }                                                                                   \
        }                                                                                       \
        return ms_propertyMap;                                                                  \
    }

/**
    @def EE_IMPLEMENT_BUILTINMODEL_PROPERTIES

    Used to implement the static mapping of property ID to PropertyData. You must include this
    macro in your C++ builtin model source file when using EE_DECLARE_BUILTINMODEL_PROPERTIES.

    @param implClass This is the class that actually contains the methods being bound.  This
    class can be the same as FinalClass if you are not inheriting an implementation, otherwise
    it must be a base class of FinalClass.  This allows the IBuiltinModel implementation to
    simply derive from existing classes containing the desired methods.
 */
#define EE_IMPLEMENT_BUILTINMODEL_PROPERTIES(implClass)                                         \
    efd::map<egf::PropertyID,efd::SmartPointer<egf::BuiltinHelper::PropertyData> >              \
        implClass::ms_propertyMap;                                                              \



/**
    @def EE_NO_BUILTINMODEL_PROPERTIES

    If you want to use the built-in model helpers to bind behaviors but you expose no properties
    then you can use this macro instead of using both EE_DECLARE_BUILTINMODEL_PROPERTIES followed
    by EE_END_BUILTINMODEL_PROPERTIES.  This will implement enough methods to satisfy the property
    access requirements of IBuiltinModelImpl.
*/
#define EE_NO_BUILTINMODEL_PROPERTIES                                                           \
public:                                                                                         \
    virtual const egf::BuiltinModelPropertyMap& GetPropertyMap() const                          \
    {                                                                                           \
        static egf::BuiltinModelPropertyMap propertyMap;                                        \
        return propertyMap;                                                                     \
    }                                                                                           \


#endif // EE_BUILTINMODELHELPER_H

