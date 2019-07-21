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
#ifndef NISTREAMMACROS_H
#define NISTREAMMACROS_H

class NiStream;
class NiObject;

//--------------------------------------------------------------------------------------------------
// Macros for declaring and registering streams.
//--------------------------------------------------------------------------------------------------
// Insert in class declaration (note the start of public scope).  The
// routine IsEqual is for debugging purposes only.
#define NiDeclareAbstractStream \
    public: \
        virtual void LoadBinary(NiStream& kStream); \
        virtual void LinkObject(NiStream& kStream); \
        virtual bool RegisterStreamables(NiStream& kStream); \
        virtual void SaveBinary(NiStream& kStream); \
        virtual bool IsEqual(NiObject* pkObject)

#define NiDeclareStream \
    NiDeclareAbstractStream; \
        static NiObject* CreateObject(const char** pcArguments = 0, \
            unsigned int uiArgCount = 0)

// Call for each streamable class in libname##SDM::Init function.
#define NiRegisterStream(classname) \
    NiStream::RegisterLoader(#classname, classname::CreateObject)

// Call for each streamable class in libname##SDM::Shutdown function.
#define NiUnregisterStream(classname) \
    NiStream::UnregisterLoader(#classname)

// Macro that implements NiObject construction for streamable objects.
// This macro has two modes of operation. If (NULL, 0) arguments are passed in,
// a new object is created by allocating memory (i.e. normal object construction).
// If an array containing NI_RECREATE_FLAG and an existing NiObject is passed in by the
// caller, the in-place destructor and constructor will be called on the NiObject.
// In addition, the smart pointer reference count to the original NiObject is preserved.
// This results in the replacement of a NiObject with a newly initialized object of the
// same type.
#define NI_RECREATE_FLAG -1
#define NiImplementCreateObject(classname) \
    NiObject* classname::CreateObject(const char** pcArguments, \
            unsigned int uiArgCount) \
    { \
        classname* pkObject = NULL; \
        if (uiArgCount == 2 && pcArguments != NULL && \
            *((NiInt32*)pcArguments[0]) == NI_RECREATE_FLAG) \
        { \
            pkObject = (classname*)pcArguments[1]; \
            EE_ASSERT(pkObject); \
            unsigned int uiRefCount = pkObject->GetRefCount(); \
            pkObject->~classname(); \
            new (pkObject) classname(); \
            for (unsigned int uiIndex = 0; uiIndex < uiRefCount; ++uiIndex) \
            { \
                pkObject->IncRefCount(); \
            } \
        } \
        if (!pkObject) \
        { \
            pkObject = NiNew classname; \
            EE_ASSERT(pkObject != NULL); \
        } \
        return pkObject; \
    }

#endif // NISTREAMMACROS_H
