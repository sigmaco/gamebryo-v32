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
#ifndef NIPATH_H
#define NIPATH_H

#include "NiSystem.h"
#include <efd/PathUtils.h>

//--------------------------------------------------------------------------------------------------
#define NI_PATH_DELIMITER_STR EE_PATH_DELIMITER_STR
#define NI_PATH_DELIMITER_CHAR EE_PATH_DELIMITER_CHAR
#define NI_PATH_DELIMITER_INCORRECT_STR EE_PATH_DELIMITER_INCORRECT_STR
#define NI_PATH_DELIMITER_INCORRECT_CHAR EE_PATH_DELIMITER_INCORRECT_CHAR
#define NI_MAX_PATH efd::EE_MAX_PATH

//--------------------------------------------------------------------------------------------------
class NISYSTEM_ENTRY NiPath
{
public:
    static bool IsRelative(const char *pcPath);

    static bool IsUniqueAbsolute(const char *pcPath);

    static size_t ConvertToRelative(
        char* pcRelativePath,
        size_t stRelBytes,
        const char* pcAbsolutePath,
        const char* pcRelativeToHere);

    static size_t ConvertToAbsolute(
        char* pcPath,
        size_t stBytes,
        const char* pcRelativeToHere);

    static size_t ConvertToAbsolute(
        char* pcPath,
        size_t stBytes);

    static size_t ConvertToAbsolute(
        char* pcAbsolutePath,
        size_t stBytes,
        const char* pcRelativePath,
        const char* pcRelativeToHere);

    static void RemoveSlashDotSlash(char* pcPath);
    static void RemoveDotDots(char* pcPath);
    static bool GetCurrentWorkingDirectory(char* pcPath,
        size_t stDestSize);
    static bool GetExecutableDirectory(char* pcPath,
        size_t stDestSize);
    static bool Standardize(char* pcPath);

    // Note: this function should only be used with filenames, not entire
    // paths. It detects '/' and '\\' characters as invalid.
    static void ReplaceInvalidFilenameCharacters(char* pcFilename,
        char cReplacement);

#ifdef _PS3
    static bool SetCWDandEWDfromArgV0(const char* pcArgV0);
    static void SetExecutableDirectory(const char* pcPath);
    static void SetCurrentWorkingDirectory(const char* pcPath);
#endif

protected:
    static const char* StripAbsoluteBase(const char* pcAbsolutePath);
    static char* StripAbsoluteBase(char* pcAbsolutePath);
};
//

//--------------------------------------------------------------------------------------------------
inline bool NiPath::IsRelative(const char *pcPath)
{
    return efd::PathUtils::IsRelativePath(pcPath);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPath::IsUniqueAbsolute(const char *pcPath)
{
    return efd::PathUtils::IsStandarizedAbsolutePath(pcPath);
}

//--------------------------------------------------------------------------------------------------
inline size_t NiPath::ConvertToRelative(char* pcRelativePath, size_t stRelBytes,
    const char* pcAbsolutePath, const char* pcRelativeToHere)
{
    return efd::PathUtils::ConvertToRelative(pcRelativePath, stRelBytes,
        pcAbsolutePath, pcRelativeToHere);
}

//--------------------------------------------------------------------------------------------------
inline size_t NiPath::ConvertToAbsolute(char* pcPath, size_t stBytes,
    const char* pcRelativeToHere)
{
    return efd::PathUtils::ConvertToAbsolute(pcPath, stBytes, pcRelativeToHere);
}

//--------------------------------------------------------------------------------------------------
inline size_t NiPath::ConvertToAbsolute(char* pcPath, size_t stBytes)
{
    return efd::PathUtils::ConvertToAbsolute(pcPath, stBytes);
}

//--------------------------------------------------------------------------------------------------
inline size_t NiPath::ConvertToAbsolute(char* pcAbsolutePath, size_t stBytes,
    const char* pcRelativePath, const char* pcRelativeToHere)
{
    return efd::PathUtils::ConvertToAbsolute(pcAbsolutePath, stBytes,
        pcRelativePath, pcRelativeToHere);
}

//--------------------------------------------------------------------------------------------------
inline void NiPath::RemoveSlashDotSlash(char* pcPath)
{
    efd::PathUtils::RemoveSlashDotSlash(pcPath);
}

//--------------------------------------------------------------------------------------------------
inline void NiPath::RemoveDotDots(char* pcPath)
{
    efd::PathUtils::RemoveDotDots(pcPath);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPath::GetCurrentWorkingDirectory(char* pcPath,
    size_t stDestSize)
{
    return efd::PathUtils::GetWorkingDirectory(pcPath, stDestSize);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPath::GetExecutableDirectory(char* pcPath,
    size_t stDestSize)
{
    return efd::PathUtils::GetExecutableDirectory(pcPath, stDestSize);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPath::Standardize(char* pcPath)
{
    return efd::PathUtils::Standardize(pcPath);
}

//--------------------------------------------------------------------------------------------------
inline void NiPath::ReplaceInvalidFilenameCharacters(char* pcFilename,
    char cReplacement)
{
    efd::PathUtils::ReplaceInvalidFilenameCharacters(pcFilename, cReplacement);
}

//--------------------------------------------------------------------------------------------------
inline const char* NiPath::StripAbsoluteBase(const char* pcAbsolutePath)
{
    return efd::PathUtils::StripAbsoluteBase(pcAbsolutePath);
}

//--------------------------------------------------------------------------------------------------
inline char* NiPath::StripAbsoluteBase(char* pcAbsolutePath)
{
    return efd::PathUtils::StripAbsoluteBase(pcAbsolutePath);
}

//--------------------------------------------------------------------------------------------------
#ifdef _PS3
inline bool NiPath::SetCWDandEWDfromArgV0(const char* pcArgV0)
{
    return efd::PathUtils::SetCWDandEWDfromArgV0(pcArgV0);
}

//--------------------------------------------------------------------------------------------------
inline void NiPath::SetExecutableDirectory(const char* pcPath)
{
    efd::PathUtils::SetExecutableDirectory(pcPath);
}

//--------------------------------------------------------------------------------------------------
inline void NiPath::SetCurrentWorkingDirectory(const char* pcPath)
{
    efd::PathUtils::SetCurrentWorkingDirectory(pcPath);
}

//--------------------------------------------------------------------------------------------------
#endif // _PS3

#endif // NIPATH_H
