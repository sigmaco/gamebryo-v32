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
#ifndef NISTANDARDSHAREDDATALIBTYPE_H
#define NISTANDARDSHAREDDATALIBTYPE_H

#ifdef NISTANDARDSHAREDDATA_EXPORT
    // DLL library project uses this
    #define NISTANDARDSHAREDDATA_ENTRY __declspec(dllexport)
#else
    // client of DLL uses this
    #define NISTANDARDSHAREDDATA_ENTRY __declspec(dllimport)
#endif

#endif  // #ifndef NISTANDARDSHAREDDATALIBTYPE_H
