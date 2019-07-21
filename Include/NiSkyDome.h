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

#ifndef NISKYDOME_H
#define NISKYDOME_H

#include <NiNode.h>
#include <NiMesh.h>
#include <NiDirectionalLight.h>
#include "NiAtmosphere.h"
#include "NiSky.h"

class NIENVIRONMENT_ENTRY NiSkyDome : public NiSky
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:

    /// @name Constructor
    //@{
    NiSkyDome();
    //@}

    /// Virtual destructor
    virtual ~NiSkyDome();

    /// @name Dome Configuration Management
    //@{

    /** 
        Set the sky dome radius. This can be used to control how far the 
        horizon appears to be in the distance. The default value for this 
        radius is recommended. This function will cause the skydome to
        be regenerated in next update pass.
        @param fRadius the distance of the horizon.
    */
    void SetDomeRadius(float fRadius);

    /** 
        Set the skydome detail multipler. By default the skydome will be 
        made up of 100 vertices distributed across the dome. This detail
        value is a multipler to increase or decrease that number of 
        verticies. This allows vertex shader interpolation artificats to
        be minimised by selecting the appropriate detail level for the 
        application. NOTE: the default skydome material
        destroys the depth information of the dome so far clipping and
        depth culling are not an issue. This function will cause the skydome 
        to be regenerated in next update pass.
        @param fDetail the detail multipler.
    */
    void SetDomeDetail(float fDetail);

    /** 
        Set the skydome detail axis bias. By default the skydome will
        be made up of a set number of verticies across the dome. Adjusting 
        this value allows the designer to distribute more vertices on the
        latitudes of the skydome, or the longitudes. A value of 0 will 
        cause almost all of the verticies to be distributed on the longitudes. 
        This function will cause the skydome to be regenerated in next update 
        pass.
        @param fBias the axis bias.
    */
    void SetDomeDetailAxisBias(float fBias);

    /** 
        Set the skydome horizon bias. By default the skydome will
        be made up of a set number of verticies across the dome. Adjusting 
        this value allows the designer to adjust the distribution of verticies
        along the longitudes. A value closer to 0 will have a linear 
        distribution while a value of 1 will have a power of 3 distribution, 
        concentrated at    the horizon. Values inbetween allow a medium to be 
        selected between the two    extremes. This function will cause the 
        skydome to be regenerated in next update pass.
        @param fBias the horizon bias.
    */
    void SetDomeDetailHorizonBias(float fBias);
    
    /**
        Get the sky dome's radius.
    */
    float GetDomeRadius();

    /**
        Get the sky dome's detail multiplier.
    */
    float GetDomeDetail();

    /**
        Get the sky dome's axis detail bias.
    */
    float GetDomeDetailAxisBias();

    /**
        Get the sky dome's horizon detail bias.
    */
    float GetDomeDetailHorizonBias();

protected:

    /**
        Load all the default values for the sky.
    */
    virtual void LoadDefaultConfiguration();

    /**
        Update the sky geometry with the new settings.
    */
    virtual void UpdateGeometry();

private:

    /// @name Skydome Management
    //@{

    /**
        Generate a sky dome.
    */
    NiMesh* GenerateSkyDome(float fDomeRadius, float fDetail, 
        float fAxisDetailBias, float fHorizonBias);

    /**
        Transform a linear value into the horizon biased value.
    */
    float HorizonBiasFunction(float fValue, float fBias);
    //@}

protected:
    
    /// @name Skydome configuration
    //@{

    /// The radius of the sky dome
    float m_fDomeRadius;

    /// The sky dome's detail multiplier
    float m_fDomeDetail;

    /// The sky dome's axis detail bias
    float m_fDomeDetailAxisBias;

    /// The sky dome's horizon detail bias
    float m_fDomeDetailHorizonBias;
    //@}
};

NiSmartPointer(NiSkyDome);

#include "NiSkyDome.inl"

#endif