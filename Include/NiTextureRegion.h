// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef NITEXTUREREGION_H
#define NITEXTUREREGION_H

#include "NiIndex.h"
#include "NiPoint2.h"
#include <NiTexture.h>

/**
    This class is used to define the region of a specific texture and provide basic functions
    to allow access to that texture's pixels based on the relevant region.
*/
class NITERRAIN_ENTRY NiTextureRegion : public NiMemObject
{
public:
    
    /**
        Constructor.
    */
    NiTextureRegion();

    /**
        Destructor.
    */
    virtual ~NiTextureRegion();

    /**
        Initializes the texture region with the data given in parameter

        @param pkTexture Texture associated with the region
        @param kOffset Offset defining the starting location of the 
            texture region on the associated texture
        @param fScale defines the repetition of the factor of the texture
    */
    void InitializeTextureRegion(NiTexture* pkTexture, 
        NiPoint2 kOffset, float fScale);
    
    /**
        Sets the associated texture for this texture region
    */
    void SetTexture(NiTexture* pkTexture);

    /**
        Sets the associated texture for this texture region
    */
    NiTexture* GetTexture() const;

    /**
        Sets the scale and offset for this texture region
    */
    void SetRegion(NiPoint2 kOffset, float fTextureScale);

    /**
        Gets the scale and offset for this texture region
    */
    NiPoint2 GetTextureOffset() const;

    /**
        Gets the scale and offset for this texture region
    */
    float GetTextureScale() const;

    /**
        Gets the start pixel index that this region relates to on the texture
    */
    NiIndex GetStartPixelIndex() const;

    /**
        Gets the end pixel index that this region relates to on the texture
    */
    NiIndex GetEndPixelIndex() const;

private:

    /// Region offset
    NiPoint2 m_kTextureOffset;

    /// Region scale
    float m_fTextureScale;

    /// Associated texture
    NiTexturePtr m_spTexture;
};

#include "NiTextureRegion.inl"

#endif
