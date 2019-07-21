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
#ifndef NISTREAMOUTSETTINGS_H
#define NISTREAMOUTSETTINGS_H

#include "NiRefObject.h"
#include "NiTArray.h"
#include "NiSmartPointer.h"
#include "NiFixedString.h"

class efd::BinaryStream;

class NIMAIN_ENTRY NiStreamOutSettings : public NiRefObject
{
public:
    NiStreamOutSettings();
    virtual ~NiStreamOutSettings();

    NiStreamOutSettings& operator=(
        const NiStreamOutSettings& kStreamOutSettings);

    inline void SetStreamOutAppend(bool bStreamOutAppend);
    inline bool GetStreamOutAppend() const;

    inline void SetStreamOutTargets(
        const NiTObjectArray<NiFixedString>& kStreamOutTargets);
    inline void ClearStreamOutTargets();
    inline void AppendStreamOutTargets(const char* pcStreamOutTarget);

    inline unsigned int GetStreamOutTargetCount() const;
    inline const NiFixedString& GetStreamOutTarget(int uiIndex) const;

    // Streaming support
    bool LoadBinary(efd::BinaryStream& kStream);
    bool SaveBinary(efd::BinaryStream& kStream) const;

private:
    NiTObjectArray<NiFixedString> m_kStreamOutTargets;
    bool m_bStreamOutAppend;
};

typedef efd::SmartPointer<NiStreamOutSettings> NiStreamOutSettingsPtr;

#include "NiStreamOutSettings.inl"

#endif  //NISTREAMOUTSETTINGS_H
