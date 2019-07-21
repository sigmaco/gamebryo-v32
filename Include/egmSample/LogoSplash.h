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
#ifndef EE_LOGOSPLASH_H
#define EE_LOGOSPLASH_H

#include <efd/utf8string.h>
#include <efd/Point2.h>

#include <NiFloatInterpolator.h>

#include "ScreenTextureClick.h"
#include "egmSampleLibType.h"

namespace efd
{
    class ServiceManager;
}

class NiDefaultClickRenderStep;

namespace egmSample
{

/**
    The LogoSplash class loads a texture file, creates a screen space textured quad
    and renders the logo. If interpolators are provided they can be used to change the
    size and alpha of the quad so that the image is scaled or faded in/out over time.
*/
class EE_EGMSAMPLE_ENTRY LogoSplash : public ScreenTextureClick
{
public:
    /**
        LogoSplash Constructor

        @param texname Path to logo image, any texture format is good.
        @param skippable User can interrupt (once all loading is done)
        @param size Size of the texture element. See ScreenTextureClick
                    for default values.
        @param duration (default 5.0) Total duration of sequence
    */
    LogoSplash(
        const efd::utf8string& texname,
        efd::Bool skippable = true,
        const efd::Point2& size = UseScreenSize,
        efd::Float32 duration = 5.0);

    /// Destructor
    ~LogoSplash();

    /// Overridden virtual functions inherit base documentation and are not documented here.
    virtual void OnInit(efd::ServiceManager* pServiceManager);
    virtual efd::Bool IsDrawing() const;
    virtual efd::Bool Abort();
    virtual efd::Bool IsDone() const;

    /**
        Override the size interpolator.
        @note All interpolators are owned by the LogoSplash class and will be deleted when the
              splash screen is destroyed or the interpolator is changed again..
    */
    void SetSizeInterpolator(NiFloatInterpolator* pSize);
    /**
        Override the size interpolator
        @note All interpolators are owned by the LogoSplash class and will be deleted when the
              splash screen is destroyed or the interpolator is changed again..
    */
    void SetAlphaInterpolator(NiFloatInterpolator* pAlpha);

    /**
        Creates a size interpolator that grows over its duration.
    */
    static NiFloatInterpolator* GrowSize();
    /**
        Creates an alpha interpolator that fades in, then out.
    */
    static NiFloatInterpolator* FadeInOutAlpha();
    /**
        Creates an interpolator that always returns the given value.
        @param value Constant value the interpolator should return.
    */
    static NiFloatInterpolator* ConstInterpolator(efd::Float32 value);

protected:
    /**
        Returns the elapsed time between the first rendered frame until now. The first time
        it is called it initializes itself with the current system manager time (thus it is
        not affected by pausing the SystemManager.)
        @return Elapsed time since the first time it was called.
    */
    efd::Float64 ElapsedTime() const;

    /// Overridden virtual functions inherit base documentation and are not documented here.
    virtual efd::Bool PreRenderCallback();

private:
    // name of texture file to load
    efd::Bool m_skippable;
    efd::Float32 m_duration;
    // Alpha interpolator
    NiFloatInterpolatorPtr m_spAlphaInterpolator;
    // Size interpolator
    NiFloatInterpolatorPtr m_spSizeInterpolator;
    efd::ServiceManager* m_pServiceManager;
    mutable efd::TimeType m_startTime;
    NiDefaultClickRenderStep* m_pRenderStep;

    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;
    /// @endcond
};

typedef efd::SmartPointer<LogoSplash> LogoSplashPtr;

} // end namespace egmSample

#endif // EE_LOGOSPLASH_H
