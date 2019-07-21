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

#ifndef NIVIDEODECODER_H
#define NIVIDEODECODER_H

#include "NiVideoLibType.h"
#include <NiRenderer.h>

class NIVIDEO_ENTRY NiVideoDecoder : public NiRefObject
{
public:

    enum Method // Method - how to use the decoder.
    {
        ASMOVIE   = 0,
        ASTEXTURE
    };

    enum Flags  // Misc. flags.
    {
        USE_OVERLAY     = 0x10000000,
        USE_BORDERCOLOR = 0x20000000,
        LOOPING         = 0x40000000,
        THREADED        = 0x80000000,
        SCALED          = 0x00010000,
        SCALINGMASK     = 0x0000ffff
    };

    enum Status // Status of decoder.
    {
        ERROR_OCCURED   = 0x80000000,
        UNKNOWN         = 0,
        READYTOPLAY,
        PLAYING,
        PAUSED,
        STOPPED,
        COMPLETE
    };

    enum Action // Action to perform.
    {
        NONE = 0,
        PLAY,
        STOP,
        PAUSE,
        RESET
    };

    enum Error  // Error flags.
    {
        ERR_OK                      = 0x00000000,
        ERR_GENERIC                 = 0x80000001,
        ERR_INVALIDFILE             = 0x80000002,
        ERR_TEXTURECREATEFAILED     = 0x80000003,
        ERR_INVALIDFORMAT           = 0x80000004,
        ERR_INVALIDPARAMS           = 0x80000005,
        ERR_INVALIDMETHOD           = 0x80000006
    };

    class NIVIDEO_ENTRY CallbackObject  // Callback class.
    {
    public:
        virtual ~CallbackObject(){}
        // Called when the video has completed play - ASMOVIE only.
        virtual Action VideoCompleted(NiVideoDecoder* pkDecoder) = 0;

        // Called when there is an error in the video system.
        virtual Action VideoError(NiVideoDecoder* pkDecoder,
            Error eError) = 0;
    };

protected:
    NiVideoDecoder(NiRenderer* pkRenderer, Method eMethod,
        unsigned int uiFlags, char* pszVideoFile, bool bPreLoadAll);

public:
    virtual ~NiVideoDecoder();

    // Static creation call - must be implemented by all derived classes.
    static NiVideoDecoder* Create(NiRenderer* pkRenderer,
        Method eMethod, unsigned int uiFlags,
        char* pszVideoFile, bool bPreLoadAll);

    // Texture-based playback.
    virtual bool ProcessVideoFrame(float fTime,
        NiTexture* pkVideoTexture);
    virtual NiTexture* CreateVideoTexture(
        NiTexture::FormatPrefs& kPrefs);

    // Callback object.
    const CallbackObject* GetCallbackObject() const;
    void SetCallbackObject(CallbackObject* pkCallback);

    // Access functions.
    Method GetDecodeMethod() const;
    Status GetStatus() const;
    unsigned int GetFlags() const;

    // Frame sync.
    bool GetFrameSync() const;
    void SetFrameSync(bool bSync);

    // Border color - cut-scene only.
    const NiColor& GetBorderColor() const;
    void SetBorderColor(const NiColor& kColor);

    // Frame stats
    unsigned int GetCurrentFrame() const;
    unsigned int GetTotalFrames() const;

    // Last error
    Error GetLastError() const;

    // Helper function
    static unsigned int SetupFlags(bool bUseOverlay, bool bUseBorderColor,
        bool bThreaded, bool bUseScaling, unsigned int uiScaleFactor);

    // *** Begin Gamebryo internal use only. ***
    virtual bool IsOverlayAvailable(NiRenderer* pkRenderer);
    // *** End Gamebryo internal use only. ***

protected:
    CallbackObject* m_pkCallback;
    Method m_eMethod;   // Method for decoder use.
    unsigned int m_uiFlags;
    Status m_eStatus;
    char* m_pszVideoFile;
    float m_fLastUpdate;    // Last update time.
    bool m_bFrameSync;  // Flag for frame sync to video rate.
    NiColor m_kBorderColor; // Border color for scaled movie playback.

    // Frame counts
    unsigned int m_uiCurrentFrame;
    unsigned int m_uiTotalFrames;

    unsigned int m_uiPlayedCount;   // Number of times movie has been played.
    Error m_eLastError; // Last error that occured.

    bool m_bPreLoadAll; // Whether to preload the entire animation into memory.
};

NiSmartPointer(NiVideoDecoder);

#include <NiVideoDecoder.inl>

#endif  //#ifndef NIVIDEODECODER_H
