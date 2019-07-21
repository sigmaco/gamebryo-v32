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

#ifndef NISCENEGRAPHUPDATESETTINGS_H
#define NISCENEGRAPHUPDATESETTINGS_H

#include "NiSceneGraphUpdateServiceLibType.h"

#include "NiRefObject.h"
#include "NiString.h"
#include "NiBool.h"

class NiStream;

NiSmartPointer(NiSceneGraphUpdateSettings);

/**
    This class is used to store NiSceneGraphUpdate config settings and send the settings from
    the editor to the viewer.

    The settings in this class are used to control the way the viewer handles starting, restarting,
    and stopping animations in the scene graph.
*/
class NISCENEGRAPHUPDATESERVICE_ENTRY NiSceneGraphUpdateSettings : public NiRefObject
{
public:
    /// Initialize object
    NiSceneGraphUpdateSettings();

    /// Destroy object
    virtual ~NiSceneGraphUpdateSettings();

    /// @{
    /// Start time of the playback timeline
    inline float GetPlaybackStartTimeInSec() const;
    inline void SetPlaybackStartTimeInSec(float fStartTime);
    /// @}

    /// Is start time less than stop and is stop time greater than 0?
    inline bool IsPlaybackStopTimeValid();

    /// @{
    /// Stop time of the playback timeline
    inline float GetPlaybackStopTimeInSec() const;
    inline void SetPlaybackStopTimeInSec(float fStopTime);
    /// @}

    /// This enum is used to map to values in the Maya UI.
    /// Update NiMayaParticleCommand::GetViewerOptionsFromMaya() if this data type is changed.
    enum PlaybackMode
    {
        /// Play animations once
        SGU_PLAYBACK_ONCE = 0,
        /// Loop animations continuously
        SGU_PLAYBACK_LOOP
    };

    /// @{
    /// Controls whether animations loop or play once
    inline PlaybackMode GetPlaybackMode() const;
    inline void SetPlaybackMode(PlaybackMode ePlaybackMode);
    /// @}

    /// @{
    /// Restart animations after any change is made on the editor
    inline bool GetRestartPlaybackAfterEdit() const;
    inline void SetRestartPlaybackAfterEdit(bool bEnabled);
    /// @}

    /// @{
    /// Continue simulating particles past the end time (when playing animations once)
    inline bool GetSimulatePastEndTime() const;
    inline void SetSimulatePastEndTime(bool bEnabled);
    /// @}

    /// @{
    /// Simulate particles after edit to create the appearance of continuous particle streams
    inline bool GetRunUpParticlesAfterEdit() const;
    inline void SetRunUpParticlesAfterEdit(bool bEnabled);
    /// @}

    /// @{
    /// Insert default lights into the scene on the viewer
    inline bool GetAddDefaultLights() const;
    inline void SetAddDefaultLights(bool bEnabled);
    /// @}

    /// @{
    /// Hide viewer UI
    inline bool GetViewerHideUI() const;
    inline void SetViewerHideUI(bool bEnabled);
    /// @}

    /**
        Unserialize object from buffer

        @param uiBufferSize Size in bytes
        @param pcBuffer Pointer to buffer containing serialized object
    */
    void Load(const NiUInt32 uiBufferSize, const char* pcBuffer);

    /**
        Serialize object to array of bytes

        @param uiBufferSize Returns size of buffer in bytes
        @param pcBuffer Returns allocated buffer containing object. It is the caller's
            responsibility to free this buffer using NiFree().
    */
    void Save(NiUInt32& uiBufferSize, char*& pcBuffer);

protected:
    float m_fPlaybackStartTimeInSec;
    float m_fPlaybackStopTimeInSec;
    PlaybackMode m_ePlaybackMode;
    // NiBool is used instead of bool because these values are streamed across platforms
    // and 'bool' isn't implemented the same everywhere
    NiBool m_bRestartPlaybackAfterEdit;
    NiBool m_bSimulatePastEndTime;
    NiBool m_bRunUpParticlesAfterEdit;
    NiBool m_bAddDefaultLights;
    NiBool m_bViewerHideUI;
};

#include "NiSceneGraphUpdateSettings.inl"

#endif // NISCENEGRAPHUPDATESETTINGS_H
