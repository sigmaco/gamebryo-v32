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
#ifndef EE_EGMSAMPLELIBTYPE_H
#define EE_EGMSAMPLELIBTYPE_H

// so we know the names our dll exports (if we compile for windows)
#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
    #ifdef EE_EGMSAMPLE_EXPORT
        //Defined if we are building the library.
        #define EE_EGMSAMPLE_ENTRY __declspec (dllexport)

        // Disable warning C4251.  Template classes cannot be exported for the obvious
        // reason that the code is not generated until an instance of the class is
        // declared.  With this warning enabled, you get thousands of complaints about
        // class data members that are of template type.  For example, a member such
        // as 'SmartPointer<SomeObject> m_objectPointer' generates the warning.
        //
        // When maintaining the DLL code itself, you might want to enable the warning
        // to check for cases where you might have failed to put the LIBRARYNAME_ENTRY
        // after the class keyword.  In particular, nested classes must have
        // LIBRARYNAME_ENTRY.  Also, friend functions must be tagged with
        // LIBRARYNAME_ENTRY.   (Where LIBRARYNAME_ENTRY is, e.g., EE_EGMSAMPLE_ENTRY)
        #pragma warning(disable : 4251)

    #elif defined(_WINDLL) || defined (USEDLL) || defined(EE_EGMSAMPLE_IMPORT)
        // if we are including as part of a client (we are a library)
        #define EE_EGMSAMPLE_ENTRY __declspec (dllimport)
    #else
        // if we are defining for a static build (NOT a .dll)
        #define EE_EGMSAMPLE_ENTRY
    #endif

// 4275 - non dll-interface class used as base for dll-interface class.
#pragma warning(disable:4275)

#else
    // if we are compiling for a non-windows build
    #define EE_EGMSAMPLE_ENTRY
#endif

#endif //EE_EGMSAMPLELIBTYPE_H

