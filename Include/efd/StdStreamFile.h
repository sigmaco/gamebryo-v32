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
#ifndef EE_STDSTREAMFILE_H
#define EE_STDSTREAMFILE_H

#include <efd/FileCommon.h>

namespace efd
{

/// File implementation to write to STDOUT/STDERR and read from STDIN
class EE_EFD_ENTRY StdStreamFile : public FileCommon
{
public:
    /**
        Create an instance of a StdStreamFile object.

        It creates an instance with the FILE object passed in as the argument. This FILE object
        will not be freed when the StdStreamFile object is destroyed. It's the responsibility of
        the user to manage the FILE object.

        @param stream Pointer to the FILE object to be used for this StdStreamFile instance.
        @return Pointer to an instance of a StdStreamFile object.
    */
    static StdStreamFile* GetFile(FILE* stream);

    /// Virtual destructor. As noted in the comment for the GetFile() method, the FILE object passed
    /// in at the construction will NOT be freed. The user must manage the FILE object.
    virtual ~StdStreamFile();


    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual unsigned int Read(void *pvBuffer, unsigned int uiBytes);
    virtual unsigned int Write(const void *pvBuffer, unsigned int uiBytes);
    virtual bool Flush();
    virtual operator bool() const;
    virtual bool Seek(int iNumBytes);
    virtual bool Seek(int iOffset, SeekOrigin iWhence);
    virtual unsigned int GetFileSize() const;
    virtual bool eof();
    virtual bool IsGood();
    virtual void SetEndianSwap(bool);

protected:
    StdStreamFile(FILE* stream);
    FILE* m_stream;
};

}   // End namespace efd.

#endif  // EE_STDSTREAMFILE_H
