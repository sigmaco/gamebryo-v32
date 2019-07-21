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
#ifndef EE_SCREENTEXTURECLICK_H
#define EE_SCREENTEXTURECLICK_H

#include <efd/IBase.h>
#include <efd/Point2.h>
#include <efd/Category.h>

#include <NiViewRenderClick.h>
#include <NiMaterialProperty.h>
#include "egmSampleLibType.h"


class NiMeshScreenElements;
class NiMesh2DRenderView;
class NiMaterialProperty;

namespace egmSample
{

/**
    ScreenTextureClick is a wrapper class for render clicks that are drawn in screen space,
    like HUDs and Splash Screens. It uses the PreRender callback to update all elements
    before being rendered. It also adds the ability to find texture assets using the
    AssetLocator.

    Internally it contains a single render view with multiple 2D mesh elements.
*/
class EE_EGMSAMPLE_ENTRY ScreenTextureClick : public NiViewRenderClick
{
public:
    ScreenTextureClick();

    /// Destructor. Cleanup all resources.
    virtual ~ScreenTextureClick();

    enum SizeType
    {
        szScreen = -2,  ///< Scale texture to the screen size.
        szTexture = -1, ///< Keep the original texture size.
    };

    enum PositionType
    {
        posCenter  = 0x00, ///< Centered, used for both vertical and horizontal.
        posLeft    = 0x01, ///< X position relative to left edge of screen.
        posRight   = 0x02, ///< X position relative to right edge of screen.
        posTop     = 0x04, ///< Y position relative to top of screen.
        posBottom  = 0x08, ///< Y position relative to bottom of screen.
    };

    static const efd::Point2 UseTextureSize;
    static const efd::Point2 UseScreenSize;

    struct Element
    {
        /**
            Define a texture element to add to the ScreenTextureClick.
            @param textureName Full path to a texture file.
            @param alignment The element should be centered on the screen. If this parameter is
                 not posAbsolute then the position parameter above is used as an offset from
                 the absolute center.
            @param size Width and height of the element. You may use szScreen for either
                 dimension to cause that dimension to be stretched to fill the screen,
                 or, szTexture to make it the same size as the texture in that dimension.
                 If both dimensions are set to szScreen (i.e. UseScreenSize) then the texture's
                 aspect ratio will be kept the same as the original. There are two constants,
                 UseTextureSize and UseScreenSize that set both dimensions to either szScreen
                 or szTexture.
            @param position X and Y coordinates for positioning the element. Positive values
                 are relative to the left or top side of the screen and negative values are
                 relative to the right or bottom side of the screen.
        */
        Element(const efd::utf8string& textureName,
                PositionType alignment = posCenter,
                const efd::Point2& size = UseTextureSize,
                const efd::Point2& position = efd::Point2(0,0));

        /**
            Scale and possibly reposition the texture element.
            @param scale Multiplier for size. I.e. 0.95 means scale to 95% of normal size.
            @param screenSize Current screen (window) size. For scaling to screen size.
        */
        virtual void SetSize(efd::Float32 scale, const efd::Point2& screenSize);

        // name of texture file to load
        efd::utf8string m_textureName;
        PositionType m_alignment;
        efd::Point2 m_position;
        // rendered size of texture
        efd::Point2 m_size;
        // actual size of texture
        efd::Point2 m_textureSize;
        NiMeshScreenElements* m_pScreenElement;
        virtual ~Element();
    };

    /**
        Add a texture to this render click.
        @param pElement Pointer to Element to add.
        @param name Application defined string to use to find this element.
    */
    virtual void AddTexture(Element* pElement, const efd::utf8string& name = "");

    /**
        Enable/disable prerendering callback. Override PreRenderCallback to handle.
        @param enable If true, enables callbacks, false disables.
    */
    inline void EnablePreRenderCallback(efd::Bool enable);

protected:
    /// Calculates the rendering aspect ratio
    efd::Float32 GetAspectRatio() const;

    /**
        Called during the pre-render stage of the render click. Updates any dynamic elements
        immediately before render. Since changing dynamic elements might be a GPU-blocking
        operation, we want to give the longest time possible to the GPU to complete the
        previous frame's work before issuing an update. You must call
        EnablePreRenderCallback(true) before callbacks will occur.
    */
    virtual efd::Bool PreRenderCallback();

    typedef efd::map<efd::utf8string, Element*> ElementMap;

    ElementMap m_elementMap;

    /// Aspect ratio of screen or window
    efd::Float32 m_aspect;
    efd::Point2 m_screenSize;

    /// offset of the upper, left corner of the "safe zone" for rendering.
    efd::Point2 m_ulOffset;

    /// offset of the lower, right corner of the "safe zone" for rendering.
    efd::Point2 m_lrOffset;

    NiMaterialPropertyPtr m_spFadeMaterial;

private:
    NiMesh2DRenderView* m_pRenderView;

    /**
        Private dispatch function for prerender callbacks. Translates the static function
        call into a member function call to PreRenderCallback().
    */
    static efd::Bool PreRenderDispatch(NiRenderClick* pkCurrentRenderClick, void* pvCallbackData);

    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;
    /// @endcond
};


} // end namespace egmSample

#include "ScreenTextureClick.inl"

#endif // EE_SCREENTEXTURECLICK_H
