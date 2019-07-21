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
#ifndef __PathUtils_h__
#define __PathUtils_h__

#include <efd/utf8string.h>

#ifdef EE_PLATFORM_PS3
#include <sys/paths.h>
#define EE_PATH_DELIMITER_STR "/"
#define EE_PATH_DELIMITER_CHAR '/'
#define EE_PATH_DELIMITER_INCORRECT_STR "\\"
#define EE_PATH_DELIMITER_INCORRECT_CHAR '\\'
#elif defined(EE_PLATFORM_LINUX)
#define EE_PATH_DELIMITER_STR "/"
#define EE_PATH_DELIMITER_CHAR '/'
#define EE_PATH_DELIMITER_INCORRECT_STR "\\"
#define EE_PATH_DELIMITER_INCORRECT_CHAR '\\'
#else
#define EE_PATH_DELIMITER_STR "\\"
#define EE_PATH_DELIMITER_CHAR '\\'
#define EE_PATH_DELIMITER_INCORRECT_STR "/"
#define EE_PATH_DELIMITER_INCORRECT_CHAR '/'
#endif


namespace efd
{
    static const efd::UInt32 EE_MAX_PATH = 260;

    /**
        PathUtils contains helpful functions for dealing with paths and filenames in a platform
        agnostic manor.
    */
    namespace PathUtils
    {
        /// Returns the default platform specific path separator character (i.e. '/' or '\'
        /// depending on the platform).
        inline efd::Char GetNativePathSeperator();

        /// Returns whichever path separator character is not used on this platform.
        inline efd::Char GetNonNativePathSeperator();

        /// Returns true if the platform supports relative paths for operations like opening
        /// a file.  Windows and Linux support relative paths, PS3 and Xbox360 do not.
        inline bool GetPlatformSupportsRelativePaths();

        /// Returns true if the character is any type of path separator (i.e. '/' or '\').
        EE_EFD_ENTRY bool IsPathSeperator(const efd::utf8char_t& i_ch);

        /// Returns true if the character is the file extension separator (i.e. '.').
        EE_EFD_ENTRY bool IsExtensionSeperator(const efd::utf8char_t& i_ch);

        /**
            Returns true if the provided path is an absolute path - utf8string version.

            An absolute path is one
            that is not relative (see IsRelativePath) and does not contain any ".." substrings.
        */
        EE_EFD_ENTRY bool IsAbsolutePath(const efd::utf8string& i_strPath);

        /**
            Returns true if the provided path is an absolute path - char* version.

            An absolute path is one
            that is not relative (see IsRelativePath) and does not contain any ".." substrings.
        */
        EE_EFD_ENTRY bool IsAbsolutePath(const efd::Char* pCStr);

        /**
            Returns true if pcPath is an absolute path already in "standardized" form
            (see PathUtils::Standardize), with no removable ".." substring
            (see PathUtils::RemoveDotDots). This is the utf8string version.
        */
        EE_EFD_ENTRY bool IsStandarizedAbsolutePath(const efd::utf8string& i_strPath);

        /**
            Returns true if pcPath is an absolute path already in "standardized" form
            (see PathUtils::Standardize), with no removable ".." substring
            (see PathUtils::RemoveDotDots). This is the char* version.
        */
        EE_EFD_ENTRY bool IsStandarizedAbsolutePath(const efd::Char* pCStr);

        /**
            Returns true if the provided path is a relative path - utf8string version.

            On most platforms and path that begins with a slash is not relative.
            On Windows and Xbox360 paths that begin with a drive letter followed
            by a colon are also not relative.
        */
        EE_EFD_ENTRY bool IsRelativePath(const efd::utf8string& i_strPath);

        /**
            Returns true if the provided path is a relative path - char* version.

            On most platforms and path that begins with a slash is not relative.
            On Windows and Xbox360 paths that begin with a drive letter followed
            by a colon are also not relative.
        */
        EE_EFD_ENTRY bool IsRelativePath(const efd::Char* pCStr);

        /**
            Return true if the path follows the Universal Naming Convention (UNC) style.  A UNC
            path has the form "\\server\share\path\filename."  For our purposes any path that
            starts with two slashes will be considered UNC-style.
        */
        EE_EFD_ENTRY bool IsUNCPath(const efd::utf8string& i_strPath);

        /**
            On platforms that support drive designations, this returns true if the given path
            starts with a drive designation.  Windows and Xbox360 support drive letters of the
            form "l:" (where 'l' is any letter from 'a' to 'z' including upper case variants)
            optionally followed by a path separator. Other platforms always return false
            from this method.
        */
        EE_EFD_ENTRY bool PathContainsDrive(const efd::utf8string& i_strPath);

        /**
            Converts non-native path separators into native path separators.  For example, on
            Windows this would convert "c:/foo\bar/whatever" into "c:\foo\bar\whatever".
        */
        EE_EFD_ENTRY efd::utf8string PathMakeNative(const efd::utf8string& i_strPath);

        /**
            Converts native path separators into non-native path separators.  For example, on
            Windows this would convert "\foo\bar\whatever" into "/foo/bar/whatever".
        */
        EE_EFD_ENTRY efd::utf8string PathMakeNonNative(const efd::utf8string& i_strPath);

        /**
            Given a root path and an additional path or filename, combine the two sections.
            If needed a native path separator will be inserted between the two sections.

            Examples:
            @code
                "some/root/path" + "file.ext" => "some/root/path/file.ext"
                "some/root/path/" + "file.ext" => "some/root/path/file.ext"
                "some/root/path" + "/file.ext" => "some/root/path/file.ext"
                "some/root/path" + "more/path" => "some/root/path/more/path"
                "some/root/path/" + "/more/path" => "some/root/path/more/path"
            @endcode

            NOTE: Any empty strings are treated as if they contained a slash.  So for example:
            @code
                "" + "filename" => "filename"
                "/" + "filename" => "/filename"
                "" + "/filename" => "/filename"
                "path" + "" => "path"
                "path" + "/" => "path/"
                "path/" + "" => "path/"
            @endcode
        */
        EE_EFD_ENTRY efd::utf8string PathCombine(const efd::utf8string& i_strRoot,
                                                 const efd::utf8string& i_strMore);

        /**
            Gets the file extension, if any, from the path with file name. The extensions is
            all characters following the last extension separator in the portion of the path
            after the last path separator. If there is no extension the empty string is returned.

            Examples:
            @code
                "filename.ext" => "ext"
                "filename.foo.ext" => "ext"
                "filename" => ""
                "filename." => ""
                "some.path/filename.ext" => "ext"
                "some.path/filename" => ""
                "some.path\filename" => ""
            @endcode
        */
        EE_EFD_ENTRY efd::utf8string PathGetExtension(const efd::utf8string& i_strPath);

        /**
            Adds an extension to the current filename.  Ensures that a "." separates the
            extension from the rest of the filename.

            Examples:
            @code
                "filename" + "ext" => "filename.ext"
                "filename" + ".ext" => "filename.ext"
            @endcode

            NOTE: this adds an extension, it does not change an extension.  So for example:
            @code
                "filename.ext" + "ext" => "filename.ext.ext"
                "filename.ext" + ".ext" => "filename.ext.ext"
                "filename." + "ext" => "filename..ext"
                "filename." + ".ext" => "filename..ext"
            @endcode
        */
        EE_EFD_ENTRY efd::utf8string PathAddExtension(const efd::utf8string& i_strRoot,
                                                      const efd::utf8string& i_strExt);

        /**
            Remove the file extension, if any, from the path with file name.  The extension is
            all characters following the last extension separator in the portion of the path
            after the last path separator.  The extension separator itself is also removed.

            Examples:
            @code
                "path/filename.ext" => "path/filename"
                "path/filename" => "path/filename"
                "path.with.dot/filename.ext" => "path.with.dot/filename"
                "path.with.dot/filename" => "path.with.dot/filename"
                "file.with.multiple.dots" => "file.with.multiple"
                ".ext" => ""
                "." => ""
                ".." => "."
            @endcode
        */
        EE_EFD_ENTRY efd::utf8string PathRemoveFileExtension(const efd::utf8string& i_strPath);

        /**
            Remove the file name from the path with file name.  The filename is all characters
            following the last path separator.
        */
        EE_EFD_ENTRY efd::utf8string PathRemoveFileName(const efd::utf8string& i_strPath);

        /**
            Get the file name portion from the full path with file name.  The filename is all
            characters following the last path separator.  If no path separator is present, the
            result is the entire source file name.
        */
        EE_EFD_ENTRY efd::utf8string PathGetFileName(const efd::utf8string& i_strPath);

        /**
            Remove any double slashes from the middle of the path.  This will not remove leading
            double slashes which denote a UNC share.  Only native path separators are considered.

            Examples:
            @code
                "c:\\foo\\bar" => "c:\foo\bar"
                "\\server\share\\something" => "\\server\share\something"
            @endcode
        */
        EE_EFD_ENTRY efd::utf8string PathRemoveSlashSlash(const efd::utf8string& i_strPath);

        /**
            Remove any occurrences of syntactically irrelevant "current directories".  Only native
            path separators are considered.

            Examples:
            @code
                "some\.\path\.\with\.\redundant\.\info" => "some\path\with\redundant\info"
                ".\some\.\path" => ".\some\path"
                "some\.\.\.\.\.\.\path" => ".\some\path"
            @endcode
        */
        EE_EFD_ENTRY efd::utf8string PathRemoveSlashDotSlash(const efd::utf8string& i_strPath);

        /**
            Simplifies paths that use the ".." relative path notion to their simplest form.
            Both native and non-native path separators are considered and the resulting path
            will use only native path separators.

            Examples:
            @code
                "some\path\..\with\relative\..\info" => "some\with\info"
                "..\some\..\..\path" => "..\..\path"
            @endcode
        */
        EE_EFD_ENTRY efd::utf8string PathRemoveDotDots(const efd::utf8string& i_strPath);

        /// Converts an absolute path into a relative path from the current working directory.
        EE_EFD_ENTRY bool ConvertToRelative(
            const efd::utf8string& i_strAbsolutePath,
            efd::utf8string& o_result);

        /// Converts an absolute path into a relative path from the given base directory.
        EE_EFD_ENTRY bool ConvertToRelative(
            const efd::utf8string& i_strAbsolutePath,
            const efd::utf8string& i_strRelativeToHere,
            efd::utf8string& o_result);

        /// Converts a relative path from the current working directory into an absolute path.
        EE_EFD_ENTRY efd::utf8string ConvertToAbsolute(
            const efd::utf8string& i_strRelativePath);

        /// Converts a relative path from the given base to an absolute path.
        EE_EFD_ENTRY efd::utf8string ConvertToAbsolute(
            const efd::utf8string& i_strRelativePath,
            const efd::utf8string& i_strRelativeToHere);

        /**
            Converts relative path pcPath relative to pcRelativeToHere to a standardized absolute
            path. Assumes pcPath was allocated with stBytes bytes of memory. Returns the string
            length of pcPath. This function will return 0 if the resulting path will not fit
            within the size of the buffer, and pcPath will be set to an empty string.
            If pcRelativeToHere is an empty string, the current working directory will be used
            instead. None of the char* input parameters should be NULL.
        */
        EE_EFD_ENTRY size_t ConvertToAbsolute(
            efd::Char* pcPath,
            size_t stBytes,
            const efd::Char* pcRelativeToHere);

        /**
            Converts relative path pcPath relative to the current working directory to a
            standardized absolute path. Assumes pcPath was allocated with stBytes bytes of memory.
            Returns the string length of pcPath. This function will return 0 if the resulting
            path will not fit within the size of the buffer, and pcPath will be set to an empty
            string. The char* input parameter should not be NULL.
        */
        EE_EFD_ENTRY size_t ConvertToAbsolute(efd::Char* pcPath, size_t stBytes);

        /**
            Converts the absolute path pcAbsolutePath to a relative path relative to absolute
            path pcRelativeToHere, writes the resulting relative path to pcRelativePath, and returns
            the number of bytes written. pcRelativePath is assumed to have been allocated with
            stRelBytes bytes of memory. This function assumes that pcAbsolutePath and
            pcRelativeToHere are both absolute paths. This function will return 0 if
             pcAbsolutePath and pcRelativeToHere have no common root, for example if one is
            located on a different drive than the other.
        */
        EE_EFD_ENTRY size_t ConvertToAbsolute(
            efd::Char* pcAbsolutePath,
            size_t stBytes,
            const efd::Char* pcRelativePath,
            const efd::Char* pcRelativeToHere);

        /**
            Returns the platform specific default working directory - utf8string version.

            The platform specific default working directory is:
                Windows, Linux - the current working directory;
                Xbox360 - "d:\\";
                PS3 - "/app_home/".
        */
        EE_EFD_ENTRY efd::utf8string GetWorkingDirectory();

        /**
            Returns the platform specific default working directory - char* version.

            The platform specific default working directory is:
                Windows, Linux - the current working directory;
                Xbox360 - "d:\\";
                PS3 - "/app_home/".
        */
        EE_EFD_ENTRY efd::Bool GetWorkingDirectory(efd::Char* pcPath, size_t stDestSize);

        /// Writes a string with the application executable's directory to pcPath, assuming pcPath
        /// was allocated with stDestSize bytes. Returns true if the function succeeded.
        EE_EFD_ENTRY efd::Bool GetExecutableDirectory(efd::Char* pcPath, size_t stDestSize);

        /// Writes a string with the application's default log directory to pcPath, assuming pcPath
        /// was allocated with stDestSize bytes. Returns true if the function succeeded.
        EE_EFD_ENTRY efd::Bool GetDefaultLogDirectory(efd::Char* pcPath, size_t stDestSize);

        /// Convert a file path from Windows/Unix to the specific platform's format.
        EE_EFD_ENTRY efd::Bool Standardize(efd::Char* pcPath);

        /**
            Converts the absolute path pcAbsolutePath to a relative path relative to absolute
            path pcRelativeToHere, writes the resulting relative path to pcRelativePath, and
            returns the number of bytes written. pcRelativePath is assumed to have been allocated
            with stRelBytes bytes of memory. This function assumes that pcAbsolutePath and
            pcRelativeToHere are both absolute paths. This function will return 0 if
            pcAbsolutePath and pcRelativeToHere have no common root, for example if one is
            located on a different drive than the other.
        */
        EE_EFD_ENTRY size_t ConvertToRelative(
            efd::Char* pcRelativePath,
            size_t stRelBytes,
            const efd::Char* pcAbsolutePath,
            const efd::Char* pcRelativeToHere);

        /// Given an absolute or relative path pcString, removes in-place any removable
        /// ".." substring from the path. For example, will convert "C:\Foo\..\Bar" to "C:\Bar."
        EE_EFD_ENTRY void RemoveDotDots(efd::Char* pcPath);

        /**
            Given an absolute or relative path pcString, replaces in-place any removable
            "\.\" substring in the path with "\". For example, will convert
            "C:\Foo\.\Bar" to "C:\Foo\Bar."
        */
        EE_EFD_ENTRY void RemoveSlashDotSlash(efd::Char* pcPath);

        /**
            Given the string pcFilename, replaces all characters that are invalid for a filename
            with cReplacement. Invalid characters include: /, \\, :, *, ?, &quot;, &lt;, &gt; , and |.
            NOTE: Because slashes are treated as invalid, this function should not be used on full
            paths, only filenames.
        */
        EE_EFD_ENTRY void ReplaceInvalidFilenameCharacters(efd::Char* pcFilename,
            efd::Char cReplacement);

        /// Removes the 'base' from an absolute path. For example "C:\Foo\Bar.txt" would
        /// become "\Foo\Bar.txt"
        EE_EFD_ENTRY const efd::Char* StripAbsoluteBase(const efd::Char* pcAbsolutePath);

        /// Removes the 'base' from an absolute path. For example "C:\Foo\Bar.txt" would
        /// become "\Foo\Bar.txt"
        EE_EFD_ENTRY efd::Char* StripAbsoluteBase(efd::Char* pcAbsolutePath);

#ifdef EE_PLATFORM_PS3

        /// Set the current working directory and executable directory given argv[0].
        EE_EFD_ENTRY bool SetCWDandEWDfromArgV0(const char* pcArgV0);

        /// Set the directory that contains the executable.
        EE_EFD_ENTRY void SetExecutableDirectory(const char* pcPath);

        /// Set the current working directory.
        EE_EFD_ENTRY void SetCurrentWorkingDirectory(const char* pcPath);

#endif

#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_LINUX)
        typedef struct {
            efd::UInt32 HiBits;     // high-order of 64 bit timestamp
            efd::UInt32 LoBits;     // low-order of 64 bit timestamp
        } FileTimestamp;

        /// Get last modified time for a directory or file (platform-specific implementation)
        EE_EFD_ENTRY efd::Bool GetLastModifed(const efd::utf8string& path,
            efd::PathUtils::FileTimestamp* modified);
#endif

    } // end namespace PathUtils
} // end namespace efd

#if defined (EE_PLATFORM_WIN32)
#include <efd/Win32/PathUtils_Win32.inl>
#elif defined (EE_PLATFORM_LINUX)
#include <efd/Linux/PathUtils_Linux.inl>
#elif defined (EE_PLATFORM_PS3)
#include <efd/PS3/PathUtils_PS3.inl>
#elif defined (EE_PLATFORM_XBOX360)
#include <efd/XBox360/PathUtils_XBox360.inl>
#endif

#endif // __PathUtils_h__
