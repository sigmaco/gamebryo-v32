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

#ifndef NISKY_H
#define NISKY_H

#include <NiNode.h>
#include "NiEnvironmentLibType.h"
#include "NiAtmosphere.h"
#include "NiDirectionalLight.h"
#include "NiSkyMaterial.h"
#include "NiSkyBlendStage.h"

/**
    This abstract class is used to represent a Sky mesh. Subclasses are responsible for
    implementing the actual mesh geometry, whilst this class takes care of the application
    of the NiSkyMaterial and the relevant configuration required for the NiSkyMaterial.
*/
class NIENVIRONMENT_ENTRY NiSky : public NiNode
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond
public:

    /**
        Constructor.
    */
    NiSky();

    /**
        Virtual Destructor.
    */
    virtual ~NiSky();

    /// Replicate the number of blend stages available
    enum Constraints
    {
        /// The maximum number of blend stages supported by the Sky Material
        NUM_BLEND_STAGES = NiSkyMaterial::NUM_BLEND_STAGES,
    };

    /// Expose the NiSkyMaterial atmosphere calculation mode
    typedef NiSkyMaterial::AtmosphericCalcMode AtmosphericCalcMode;

    /** 
        Set the Atmosphere object to use when calculating atmospheric
        colors for the sky. 
        @param pkAtmosphere a configured NiAtmosphere object
    */
    virtual void SetAtmosphere(NiAtmosphere* pkAtmosphere);

    /** 
        Set the directional light to be used as the sun in all
        atmospheric calculations on the sky. Only the direction is 
        used in calculations.
        @param pkSun a directional light object configured to be the sun
    */
    virtual void SetSun(NiDirectionalLight* pkSun);

    /**
        Get the atmosphere object in use.
    */
    inline NiAtmosphere* GetAtmosphere();

    /**
        Get the sun light object in use.
    */
    inline NiDirectionalLight* GetSun();

    /** 
        Set the atmospheric calculation mode. This allows the designer
        to select from 3 options, and in future versions, 4 options.
        NONE - No atmospheric calculations
        GPU_VS - Vertex shader calculations 
        GPU_PS - Pixel shader calculations
        and in future, CPU calculations.
        @param eCalcMode the selected calculation mode.
    */
    void SetAtmosphericCalcMode(AtmosphericCalcMode::Value eCalcMode);

    /**
        Get the atmospheric calculation mode in use
    */
    AtmosphericCalcMode::Value GetAtmosphericCalcMode();

    /**
        Get a pointer to the blend parameters for the given stage
    */
    NiSkyBlendStage* GetBlendStage(NiUInt32 uiStage);

    /**
        Insert a set of stage parameters at the given point, moving any existing
        stages down backwards in position.
    */
    void InsertBlendStage(NiUInt32 uiStage, NiSkyBlendStage* pkStage);

    /**
        Set the parameters for the given stage.
    */
    void SetBlendStage(NiUInt32 uiStage, NiSkyBlendStage* pkStage);

    /**
        Notify the skydome that it needs to update the material with up to date
        shader constants. Should be called whenever the stages are modifies
    */
    void MarkBlendStagesChanged();

    /// @cond EMERGENT_INTERNAL
    
    /// @name Update Path
    //@{

    /** 
    Override the update functionality of nodes such that the sky is
    updated appropriately.

    @see NiNode
    */
    void DoUpdate(NiUpdateProcess& kUpdate);
    virtual void UpdateDownwardPass(NiUpdateProcess& kUpdate);
    virtual void UpdateSelectedDownwardPass(NiUpdateProcess& kUpdate);
    virtual void UpdateRigidDownwardPass(NiUpdateProcess& kUpdate);
    //@}

    /// @endcond

protected:
    /**
        Load all the default values for the sky.
    */
    virtual void LoadDefaultConfiguration();

    /**
        Update the sky geometry with the new settings.
    */
    virtual void UpdateGeometry() = 0;

    /**
        Attach all the extra data required for the proper material
        selection.
    */
    void AttachExtraData(NiAVObject* pkObject);

    /**
        Send the latest shader constant values to the graphics card.
    */
    void UpdateShaderConstants(NiAVObject* pkObject);

    /**
        Apply the appropriate NiSkyMaterial extra data configuration
        using the settings stored in NiSky.
    */
    void UpdateBlendStages(NiAVObject* pkObject, bool bForceUpdate = false);

    /// @name Configuration
    //@{

    /// The light to use as the sun
    NiDirectionalLight* m_pkSun;

    /// The atmospheric calculation mode to use
    AtmosphericCalcMode::Value m_eAtmosphericCalcMode;

    /// The NiSkyMaterial blend stage configuration
    NiSkyBlendStagePtr m_aspBlendStages[NiSkyMaterial::NUM_BLEND_STAGES];
    //@}

    /// @name Runtime values
    //@{

    /// A smart pointer to the Atmosphere used.
    NiAtmospherePtr m_spAtmosphere;

    /// A smart pointer to the sky material in use
    NiSkyMaterialPtr m_spSkyMaterial;

    /// A smart pointer to the geometry mesh
    NiMeshPtr m_spGeometry;

    /// Flag causing sky material blend stage information to be updated
    bool m_bBlendStagesChanged;

    /// Flag causing a rebuild of the geometry when true
    bool m_bGeometrySettingsChanged;
    //@}    
};

NiSmartPointer(NiSky);

#include "NiSky.inl"

#endif // NISKY_H