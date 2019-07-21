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
#ifndef EE_FILECOMMON_H
#define EE_FILECOMMON_H

#include <efd/File.h>

namespace efd
{

/// This calls contains the common code among all the concrete implementations of
/// the File interface.
class EE_EFD_ENTRY FileCommon : public efd::File
{

public:

    /// Virtual destructor.
    virtual ~FileCommon();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual operator bool() const;
    virtual bool eof();
    virtual bool IsGood();

protected:

    // Protected constructor.
    FileCommon();

    // Was the file successfully opened.
    bool m_bGood;

    // How the file was opened.
    OpenMode m_eMode;
};

}   // End namespace efd.

#endif  // EE_FILECOMMON_H
