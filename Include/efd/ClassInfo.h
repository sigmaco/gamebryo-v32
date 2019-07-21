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
#ifndef EE_CLASSINFO_H
#define EE_CLASSINFO_H

#include <efd/MemObject.h>
#include <efd/Asserts.h>

namespace efd
{

/// Typedef for a class or interface identifier.
typedef efd::UInt32 ClassID;
static const ClassID kInvalidClassID = 0;

/**
    Class that encapsulates Run-Time Type Identification (RTTI) behavior for the Emergent
    ServiceManager.

    @note Since this class does not perform any dynamic memory allocations, there is a maximum
        number of parent classes and interfaces supported.  This maximum value is enumerated as
        MAX_PARENT_IDS.
    @note The first entry in the ClassInfo class array should be the most derived type of the
        class.
*/
class EE_EFD_ENTRY ClassInfo : public MemObject
{
public:
    /// Typedef for all SetupClassInfo static functions.
    typedef void (*CLASSINFO_FUNC)(ClassInfo* pClassInfo, efd::UInt32 offsetFromClass);

    /**
        Constructor.

        @param pClassInfoFunc Pointer to a static function that initializes this ClassInfo.
    */
    inline ClassInfo(CLASSINFO_FUNC pClassInfoFunc);

    /**
        Query if a class, or any of its parent classes implements the ClassID specified.

        This method assumes that pSrc != NULL.

        @param classID Class ID that we are attempting to become.
        @param pSrc Address of the object we are trying to convert.
        @return Pointer address after a typecast of pSrc.
    */
    inline void* TypeCast(
        const ClassID classID,
        const void* pSrc) const;

    /**
        Get the ID of this class.

        @return Class ID.
    */
    inline ClassID GetClassID() const;

    /**
        Get the class name of this class.

        @return Class name.
    */
    inline const char* GetClassName() const;

    /**
        Static method used to determine if a ClassInfo contains a known class ID.

        @param pClassInfo Pointer to a ClassInfo instance.
        @param classID A known class ID.
        @return True if the ClassInfo contains a known class ID; false otherwise.
    */
    inline static bool IsKindOf(
        const ClassInfo* pClassInfo,
        const ClassID classID);

    /// Static method used to determine if a ClassInfo's zeroth class ID matches a known class ID.
    inline static bool IsExactKindOf(
        const ClassInfo* pClassInfo,
        const ClassID classID);

    /**
        Add a parent class or interface.

        @param name A statically defined character string that is the name of a parent class.
        @param id ClassID of the parent class.
        @param offset Given a pointer to the most derived type in the list, offset specifies how
            many bytes should be added to the pointer to create a pointer that is addressable as
            the parent type.
        @param parent Parent ClassInfo instance.  If this value is NULL, then the ClassInfo will
            assume that an interface is being stored.
    */
    inline void AddClass(
        const char* name,
        ClassID id,
        efd::UInt32 offset,
        const ClassInfo* parent);

protected:
    enum
    {
        // Maximum number of parent ID's supported.
        MAX_PARENT_IDS = 32
    };

    // Internal class data structure used to store parent class information.
    struct ClassDef
    {
        ClassID m_ID;
        const char* m_Name;
        const ClassInfo* m_ClassInfo;   // May not be needed.
        efd::UInt32 m_Offset;
    };

    // Total number of classes implemented by this class.
    efd::UInt32 m_ClassCount;

    // List of ClassDef's implemented by this class.
    ClassDef m_Classes[MAX_PARENT_IDS];
};


//------------------------------------------------------------------------------------------------
/// Macro used to determine the offset of a given class relative to a derived class.
#define EE_OFFSET_OF_CLASS(base, derived) ((size_t)(static_cast<base*>((derived*)8))-8)

//------------------------------------------------------------------------------------------------
/// Macro used to implement a static instance of a ClassInfo in a cpp file.
#define EE_IMPLEMENT_CONCRETE_CLASS_INFO(classname)                             \
    const efd::ClassInfo classname::ms_ClassInfo(&classname::SetupClassInfo);

//------------------------------------------------------------------------------------------------
/// Macro used to implement a static instance of a ClassInfo in a cpp file; this macro is used if
/// classname is a template.
#define EE_IMPLEMENT_CONCRETE_TEMPLATE_CLASS_INFO(classname, T)             \
    template <class T> const efd::ClassInfo classname<T>::ms_ClassInfo(     \
    &classname<T>::SetupClassInfo);

/** @name RTTI Macros
    These macros are used inside IBase derived classes in order to provide all the meta data
    needed by the Emergent RTTI system.

    The app writer is responsible for generating the system-wide unique classID to pass to these
    macros.  No two classes can use the same classID.  The Data Driven Enum system is the
    recommended approach for generating IDs that will not collide and is used throughout the
    Gamebryo code base.
*/
//@{

//------------------------------------------------------------------------------------------------
/**
    @def EE_BEGIN_DECLARE_CLASS(classname, idvalue)

    Macro used to declare the required methods for the Foundation RTTI system for a class. This
    macro begins a block that can contain zero or more EE_INCLUDE_CLASS macros and must be
    terminated using the EE_END_DECLARE_CLASS macro. This macro should be invoked inside the class
    definition for the class that will use Foundation RTTI. As a side effect, this macro will enter
    a public access level so it is recommend that this macro be followed by a specific setting of
    the desired access level. Use this macro with final concrete classes, for interface classes use
    the EE_BEGIN_DECLARE_INTERFACE macro instead.

    @note This macro adds a static member to the class which must be declared in a .cpp file by
        using a corresponding EE_IMPLEMENT_CONCRETE_CLASS_INFO call.
    @note The unmatched '{' near the end is correct.
*/
#define EE_BEGIN_DECLARE_CLASS(classname, idvalue)                                  \
public:                                                                             \
    static const efd::ClassID CLASS_ID = idvalue;                                   \
    typedef classname thisClass;                                                    \
    static const efd::ClassInfo ms_ClassInfo;                                       \
    virtual const efd::ClassInfo* GetClassDesc() const {return &ms_ClassInfo;};     \
    virtual bool TypeCast(const efd::ClassID id, const void** ppValue) const        \
    {                                                                               \
        *(ppValue) = ms_ClassInfo.TypeCast(id, this);                               \
        if (*(ppValue) != NULL)                                                     \
            return true;                                                            \
        return false;                                                               \
    }                                                                               \
    virtual bool TypeCast(const efd::ClassID id, void** ppValue) const              \
    {                                                                               \
        *(ppValue) = ms_ClassInfo.TypeCast(id, this);                               \
        if (*(ppValue) != NULL)                                                     \
            return true;                                                            \
        return false;                                                               \
    }                                                                               \
    static void SetupClassInfo(efd::ClassInfo* pClassInfo,                          \
        efd::UInt32 offsetFromClass)                                                \
    {                                                                               \
        EE_ASSERT(pClassInfo);                                                      \
        pClassInfo->AddClass(#classname, idvalue, offsetFromClass, &ms_ClassInfo);

//------------------------------------------------------------------------------------------------
/// Macro used inside a EE_BEGIN_DECLARE_CLASS block to include the RTTI information for a base
/// class. One EE_INCLUDE_CLASS call should be used for each RTTI enabled base class.
#define EE_INCLUDE_CLASS(parentname)                                \
    parentname::SetupClassInfo(pClassInfo,                          \
    offsetFromClass + EE_OFFSET_OF_CLASS(parentname, thisClass));

//------------------------------------------------------------------------------------------------
/// Macro used inside a EE_BEGIN_DECLARE_INTERFACE block to include the RTTI information for a base
/// class. One EE_INCLUDE_INTERFACE call should be used for each RTTI enabled base class.
#define EE_INCLUDE_INTERFACE(parentname)                            \
    parentname::SetupClassInfo(pClassInfo,                          \
    offsetFromClass + EE_OFFSET_OF_CLASS(parentname, thisClass));

//------------------------------------------------------------------------------------------------
/**
    Macro used to terminate an EE_BEGIN_DECLARE_CLASS block.

    @note The unmatched '}' is correct.
*/
#define EE_END_DECLARE_CLASS()  }

//------------------------------------------------------------------------------------------------
/**
    @def EE_BEGIN_DECLARE_INTERFACE(classname, idvalue)

    Macro used to declare the required methods for the Foundation RTTI system for an interface
    class. This macro begins a block that can contain zero or more EE_INCLUDE_INTERFACE macros and
    must be terminated using the EE_END_DECLARE_INTERFACE macro. This macro should be invoked inside
    the class definition for the interface that will use Foundation RTTI. As a side effect, this
    macro block will enter a public access level so it is recommend that this macro be followed by a
    specific setting of the desired access level. Use this macro with interface classes that must
    be derived from before using, for concrete final classes use the EE_BEGIN_DECLARE_CLASS macro
    instead.

    @note This macro does not allocate any static data so it does not require a matching
        EE_IMPLEMENT_CONCRETE_CLASS_INFO call.
    @note The unmatched '{' near the end is correct.
*/
#define EE_BEGIN_DECLARE_INTERFACE(classname, idvalue)                                      \
public:                                                                                     \
    static const efd::ClassID CLASS_ID = idvalue;                                           \
    typedef classname thisClass;                                                            \
    static void SetupClassInfo(efd::ClassInfo* pClassInfo, efd::UInt32 offsetFromClass)     \
    {                                                                                       \
        EE_ASSERT(pClassInfo);                                                              \
        pClassInfo->AddClass(#classname, idvalue, offsetFromClass, 0);

//------------------------------------------------------------------------------------------------
/**
    Macro used to terminate an EE_BEGIN_DECLARE_INTERFACE block.

    @note The unmatched '}' is correct.
*/
#define EE_END_DECLARE_INTERFACE()  };

//------------------------------------------------------------------------------------------------
/// Macro used as a shortcut to declare an EE_BEGIN_DECLARE_INTERFACE block with no parent
/// interfaces.
#define EE_DECLARE_INTERFACE(classname, idvalue)        \
    EE_BEGIN_DECLARE_INTERFACE(classname, idvalue);     \
    EE_END_DECLARE_INTERFACE();

//------------------------------------------------------------------------------------------------
/// Macro used as a shortcut to declare an EE_BEGIN_DECLARE_INTERFACE block with 1 parent
/// interface.
#define EE_DECLARE_INTERFACE1(classname, idvalue, parentInterface)  \
    EE_BEGIN_DECLARE_INTERFACE(classname, idvalue);                 \
        EE_INCLUDE_INTERFACE(parentInterface);                      \
    EE_END_DECLARE_INTERFACE();

//------------------------------------------------------------------------------------------------
/// Macro used as a shortcut to declare an EE_BEGIN_DECLARE_CLASS block with no parent interfaces.
#define EE_DECLARE_CLASS(classname, idvalue)        \
    EE_BEGIN_DECLARE_CLASS(classname, idvalue);     \
    EE_END_DECLARE_CLASS();

//------------------------------------------------------------------------------------------------
/// Macro used as a shortcut to declare an EE_BEGIN_DECLARE_CLASS block with 1 parent interface or
/// class.
#define EE_DECLARE_CLASS1(classname, idvalue, parentname)   \
    EE_BEGIN_DECLARE_CLASS(classname, idvalue);             \
        EE_INCLUDE_CLASS(parentname);                       \
    EE_END_DECLARE_CLASS();

//------------------------------------------------------------------------------------------------
/// Macro used as a shortcut to declare an EE_BEGIN_DECLARE_CLASS block with 2 parent interfaces
/// or classes.
#define EE_DECLARE_CLASS2(classname, idvalue, parent1name, parent2name)     \
    EE_BEGIN_DECLARE_CLASS(classname, idvalue);                             \
        EE_INCLUDE_CLASS(parent1name);                                      \
        EE_INCLUDE_CLASS(parent2name);                                      \
    EE_END_DECLARE_CLASS();

//------------------------------------------------------------------------------------------------
/// Macro used as a shortcut to declare an EE_BEGIN_DECLARE_CLASS block with 3 parent interfaces
/// or classes.
#define EE_DECLARE_CLASS3(classname, idvalue, parent1name, parent2name, parent3name)    \
    EE_BEGIN_DECLARE_CLASS(classname, idvalue);                                         \
        EE_INCLUDE_CLASS(parent1name);                                                  \
        EE_INCLUDE_CLASS(parent2name);                                                  \
        EE_INCLUDE_CLASS(parent3name);                                                  \
    EE_END_DECLARE_CLASS();

// end RTTI Macros
//@}

//------------------------------------------------------------------------------------------------
/**
    @def EE_IS_KIND_OF(classname, pObject)

    Macro used to test if an object can be cast to a known class.

    The classname must specify an RTTI enabled class. If the object is or derives from the specified
    class type this will evaluate to true.
*/
#define EE_IS_KIND_OF(classname, pObject) \
    efd::ClassInfo::IsKindOf(pObject != NULL ? pObject->GetClassDesc(): NULL, classname::CLASS_ID)

//------------------------------------------------------------------------------------------------
/**
    @def EE_IS_EXACT_KIND_OF(classname, pObject)

    Macro used to test if an object is an instance of a known class.

    The classname must specify an RTTI enabled class. If the object's type exactly matches the
    classname's type this will evaluate to true.
*/
#define EE_IS_EXACT_KIND_OF(classname, pObject)                                     \
    efd::ClassInfo::IsExactKindOf(pObject != NULL ? pObject->GetClassDesc(): NULL,  \
    classname::CLASS_ID)

//------------------------------------------------------------------------------------------------
} // end namespace efd

#include <efd/ClassInfo.inl>

#endif
