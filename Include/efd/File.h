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
#ifndef EE_FILE_H
#define EE_FILE_H

#include <efd/BinaryStream.h>
#if defined(_PS3)
#include <cell/cell_fs.h>
#endif

namespace efd
{

/// Platform-independent abstract class that defines the interface for writing to
/// and reading from files.  In addition to defining the interface it also provides
/// a mechanism to replace the default concrete implementation of the File interface.
class EE_EFD_ENTRY File : public efd::BinaryStream
{

public:

    /// Enumerates how a file is to be opened.
    typedef enum
    {
        /// The file is opened in binary read-only mode, and no data may be written to the file.
        READ_ONLY,

        /// The file is opened in binary write-only mode, and no data may be read from the file.
        WRITE_ONLY,

#if defined(EE_PLATFORM_PS3)
        /// The file is opened in binary read-only mode.  If encryption support is enabled,
        /// the file must be validly encrypted, otherwise the file will fail to be read/opened.
        /// @note This mode is currently only supported on the PS3 platform.  On other platforms
        /// this behaves identically to READ_ONLY
        READ_ONLY_ENCRYPTED,
#endif

        /**
            The file is opened in binary append-only mode, and data may only be appended to the
            end of the file.

            It is illegal to call Seek() for a File that is opened in this mode.
        */
        APPEND_ONLY,

#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_LINUX) || defined(EE_PLATFORM_XBOX360)
        /// The file is opened in text read-only mode, and no data may be written to the file.
        /// @note This mode is only supported on Windows, Linux, and Xbox360 platforms.  On other
        /// platforms this behaves identically to READ_ONLY.
        READ_ONLY_TEXT,

        /// The file is opened in text write-only mode, and no data may be read from the file.
        /// @note This mode is only supported on Windows, Linux, and Xbox360 platforms.  On other
        /// platforms this behaves identically to WRITE_ONLY.
        WRITE_ONLY_TEXT,

        /**
            The file is opened in text append-only mode, and data may only be appended to the
            end of the file.

            It is illegal to call Seek() for a File that is opened in this mode.

            @note This mode is only supported on Windows, Linux, and Xbox360 platforms.  On other
            platforms this behaves identically to APPEND_ONLY.
        */
        APPEND_ONLY_TEXT,
#else
        READ_ONLY_TEXT = READ_ONLY,
        WRITE_ONLY_TEXT = WRITE_ONLY,
        APPEND_ONLY_TEXT = APPEND_ONLY,
#endif // defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_LINUX)

#if !defined(EE_PLATFORM_PS3)
        /// The file is opened in binary read-only mode.  If encryption support is enabled,
        /// the file must be validly encrypted, otherwise the file will fail to be read/opened.
        /// @note This mode is currently only supported on the PS3 platform.  On other platforms
        /// this behaves identically to READ_ONLY
        READ_ONLY_ENCRYPTED = READ_ONLY
#endif

    } OpenMode;

    /// Enumerates where a seek is to start.
    typedef enum
    {
        /// Seek from the beginning of the stream (set the offset).
        SO_BEGIN = 0,

        /// Seek from the current position in the stream.
        SO_CURRENT = 1,

        /// Seek from the end of the stream.
        SO_END = 2,

        //@{
        /// These names are deprecated, and remain only for backwards compatibility.
        ms_iSeekSet = SO_BEGIN,
        ms_iSeekCur = SO_CURRENT,
        ms_iSeekEnd = SO_END
        //@}
    } SeekOrigin;

    /// Enumerates the type of file error that occurred.
    typedef enum
    {
        /// An error occurred opening the file.
        FILE_ERROR_OPEN,

        /// An error occurred closing the file.
        FILE_ERROR_CLOSE,

        /// An error occurred while seeking within the file.
        FILE_ERROR_SEEK,

        /// An error occurred while reading from the file.
        FILE_ERROR_READ,

        /// An error occurred while writing to the file.
        FILE_ERROR_WRITE,
    } FileError;

    /// Virtual destructor.
    virtual ~File();

    /**
        Create an instance of a File object.

        By default, it calls a function that simply allocates a File object.  To override its
        behavior, an application can cause its own version of the function to be called instead by
        passing a pointer to its version of the function to File::SetFileCreateFunc().

        @param pcName Filename.
        @param eMode Open mode (read versus write versus append).
        @param uiBufferSize Buffer size (defaults to 32768).
        @param flushOnWrite if false buffer writes until we fill the buffer. If true, flush after
        every write call.
        @return Pointer to an instance of a File object.
    */
    static File* GetFile(
        const char *pcName,
        OpenMode eMode,
        unsigned int uiBufferSize = 32768,
        bool flushOnWrite=false);

    /// Define a function to create File objects.
    typedef File* (*FILECREATEFUNC)(const char *pcName, OpenMode eMode,
        unsigned int uiBufferSize, bool flushOnWrite);

    /**
        Set the file creation function or restore to the default value if pfnFunc is NULL.

        This function can be useful if the application wishes to override the creation of File
        objects when Emergent products internally create a File object to read a file (for
        example, to read an external texture referenced by a NIF file).  Use SetFileCreateFunc()
        to override the behavior of GetFile().

        @param pfnFunc Pointer to a file creation function.
    */
    static void SetFileCreateFunc(FILECREATEFUNC pfnFunc);

    /**
        Determine whether a file with the name pcName exists and can be accessed with permissions
        defined by eMode. The behavior of this function depends on the requested access mode.

        When eMode is set to READ_ONLY, the Access function returns false if the file does not exist
        or if you do not have permission to open the file.

        When eMode is set to WRITE_ONLY or APPEND_ONLY, the Access function returns false only if
        you do not have permission to write to the file.

        The behavior of this function can be overridden by calling SetFileAccessFunc().

        @param pcName Filename.
        @param eMode Open mode (read versus write versus append).
        @return False if you do not have permissions to open the file for the given OpenMode
        or if the file does not exist when requesting READ_ONLY access. True if you do have
        permission to open the file.
    */
    static bool Access(
        const char* pcName,
        OpenMode eMode);

    /// Define a function to check if a file exists and can be accessed.
    typedef bool (*FILEACCESSFUNC)(const char* pcName, OpenMode eMode);

    /**
        Set the pointer to the function that is used to determine whether a file exists and can be
        accessed.

        If pfnFunc is NULL, then the default value is restored.  If SetFileCreateFunc() is used to
        override the creation of File objects, it is usually also necessary to use
        SetFileAccessFunc() to override the determination of file existence.  SetFileAccessFunc()
        overrides the behavior of File::Access() in the same way that File::SetFileCreateFunc()
        overrides the behavior of File::GetFile().

        @param pfnFunc Pointer to a function to check if a file exists and can be accessed.
    */
    static void SetFileAccessFunc(FILEACCESSFUNC pfnFunc);

    /**
        Create a single named directory.

        @note Only the last directory in the path specified will be created.

        @param pcDirName Name of directory to be created.
        @return True if directory was created successfully; false otherwise.
    */
    static bool CreateDirectory(const char* pcDirName);

    /// Define a function to create a single directory.
    typedef bool (*CREATEDIRFUNC)(const char* pcName);

    /**
        Set the pointer to the function that creates a directory.

        If pfnFunc is NULL, the default value is restored.  If SetCreateDirectoryFunc() is used to
        override the creation of a directory, it is usually also necessary to use
        SetDirectoryExistsFunc() to override the determination of directory existence.  This
        function overrides the behavior of File::CreateDirectory() in the same way that
        File::SetFileCreateFunc() overrides the behavior of File::GetFile().

        @param pfnFunc Pointer to a function to create a single directory.
    */
    static void SetCreateDirectoryFunc(CREATEDIRFUNC pfnFunc);

    /**
        Determine whether or not a directory path exists.

        @param pcDirName Name of directory to be checked.
        @return True if directory exists; false otherwise.
    */
    static bool DirectoryExists(const char* pcDirName);

    /// Define a function to check if a directory exists.
    typedef bool (*DIREXISTSFUNC)(const char* pcName);

    /**
        Set the pointer to the function that determines if a directory exists.

        If pfnFunc is NULL, the default value is restored.  If SetCreateDirectoryFunc() is used to
        override the creation of a directory, it is usually also necessary to use
        SetDirectoryExistsFunc() to override the determination of directory existence.  This
        function overrides the behavior of File::DirectoryExists() in the same way that
        File::SetFileCreateFunc() overrides the behavior of File::GetFile().

        @param pfnFunc Pointer to a function to check if a directory exists.
    */
    static void SetDirectoryExistsFunc(DIREXISTSFUNC pfnFunc);

    /**
        Recursively check to see if all named directories exist in the path, and if not, create
        them one at a time.

        @note All directories in the path that do not exist will be created.

        @param pcFullPath Pointer to full path string.
        @return True if function is successful; false otherwise.
    */
    static bool CreateDirectoryRecursive(const char* pcFullPath);

#if defined(EE_PLATFORM_PS3)
    /**
        This type is for a pointer to a function that is called when a file error occurs on PS3.

        @param pcFile Contains the filename if the error occurs when opening the file.
                      Otherwise it will be an empty string ("").
        @param eMode Describes the mode used to open the file
        @param eError Describes the operation that triggered the error
        @param eResult The CellFsErrno detected during a file system operation
    */
    typedef void (*PS3_FILE_ERROR_HANDLER_FUNC)(const char* pcFilename,
        OpenMode eMode, FileError eError, CellFsErrno eResult);

    /// Registers an error handler to be invoked whenever a file operation has a problem
    static void SetErrorCallback(PS3_FILE_ERROR_HANDLER_FUNC pfnFunc);
#endif

#if defined(EE_PLATFORM_XBOX360)
    /// Enumerates the file handling method.
    enum FileMethod
    {
        FILE_USE_POINTER = 0x00,
        FILE_USE_HANDLE = 0x01,
        FILE_USE_MASK   = 0x0f,
        FILE_USE_DOUBLEBUFFER = 0x80
    };

    /// @name Access to File Handling Methods
    //@{
    static void SetFileMethod(unsigned int uiFileMethod);
    static unsigned int GetFileMethod(void);
    //@}
#endif

    /// Operator to report on current success state of the File instance.
    virtual operator bool() const = 0;

    /**
        Flush all buffered data to the file.

        @return : True if flush of all buffered data to file succeeded; false otherwise.
    */
    virtual bool Flush() = 0;

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool Seek(int iNumBytes);

    /**
        Reset the current read/write position of the file.  The new position is determined by
        an offset and a starting location.  The starting location for the seek operation can
        be one of the following:

          - Beginning of the file
          - End of the file
          - Current location in the file.

        Passing a negative value into iOffset will move the current position back towards the
        beginning of the file, while a positive value will advance the position towards the end
        of the file.

        @param offset Number of bytes to move (forward or backward) from the starting location
            of the seek operation.
        @param seekFrom Starting location of the seek operation.
        @return true if successful, false otherwise.
    */
    virtual bool Seek(int offset, SeekOrigin seekFrom) = 0;

    /**
        Return the size of the file in bytes.
    */
    virtual unsigned int GetFileSize() const = 0;


    /**
        Return true if we've reached the end of file.
    */
    virtual bool eof() = 0;

    /**
        Return true if the file is in a known-good state ready for read and/or write.
    */
    virtual bool IsGood() = 0;

    /// @name Default overridable functions.  See corresponding function for more info.
    //@{
    /// Default GetFile().
    static File* DefaultFileCreateFunc(
        const char *pcName,
        OpenMode eMode,
        unsigned int uiBufferSize,
        bool flushOnWrite=false);
    /// Default Access().
    static bool DefaultFileAccessFunc(
        const char *pcName,
        OpenMode eMode);
    /// Default CreateDirectory().
    static bool DefaultCreateDirectoryFunc(const char* pcDir);
    /// Default DirectoryExists().
    static bool DefaultDirectoryExistsFunc(const char* pcDir);
    //@}

    /// Enables or disables enforcement of the READ_ONLY_ENCRYPTED semantics.
    /// Note: This currently only affects the behavior of the PS3.
    static void SetEncryptionCheckEnabled(bool enabled);

    /// Returns the state of the encryption checking when READ_ONLY_ENCRYPTED is specified
    static bool GetEncryptionCheckEnabled();
protected:
    // State of the encryption checking when READ_ONLY_ENCRYPTED is specified
    static bool ms_EncryptionCheckEnabled;

    // Protected constructor.  Use File::GetFile() instead.
    File();

    // Pointers to file handling functions.
    static FILECREATEFUNC ms_pfnFileCreateFunc;
    static FILEACCESSFUNC ms_pfnFileAccessFunc;
    static CREATEDIRFUNC  ms_pfnCreateDirFunc;
    static DIREXISTSFUNC  ms_pfnDirExistsFunc;
#if defined(EE_PLATFORM_PS3)
    static PS3_FILE_ERROR_HANDLER_FUNC ms_pfnErrorCallback;
#elif defined(EE_PLATFORM_XBOX360)
    // Global method, used when opening a file.
    static unsigned int ms_uiFileMethodFlags;
#endif
};

}   // End namespace efd.

#endif  // EE_FILE_H
