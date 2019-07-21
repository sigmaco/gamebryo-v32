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

#ifndef NiTIMEOFDAY_H
#define NiTIMEOFDAY_H

#include <NiFixedString.h>
#include <NiMain.h>
#include <efd/TinyXML.h>
#include "NiTimeOfDayController.h"

class NiEnvironment;
class NiAtmosphere;
class NiSkyDome;

/**
    This class is the main management class for the NiTimeOfDay animation 
    system. It allows almost any variable within a scene to be animated by
    animations described in an XML file. 
*/
class NIENVIRONMENT_ENTRY NiTimeOfDay : public NiAVObject
{
public:
    ///@name Constructor/Destructor
    //@{
    NiTimeOfDay();
    virtual ~NiTimeOfDay();
    //@}

    /**
        Calling this function will set the animation to active and set the
        current animation time to the specified time. 

        @param fTime the animation time to set
    */
    inline void Start(float fTime = 0.0f);

    /**
        Sets a flag allowing animation when bActive is true. Animation will
        pause when bActive is false.

        @param bActive Whether the NiTimeOfDay should be active or not
    */
    inline void SetActive(bool bActive);

    /**
        @return true if the TimeOfDay system is currently animating
    */
    inline bool GetActive() const;

    /**
        Set the time of the animation directly. This allows seeking to a
        specific point in time in the animation.

        @param fTime the animation time to set
    */
    inline void SetTime(float fTime);

    /**
        Gets the time of day according to the TimeOfDay system in seconds. 
        This value is usually calculated in Update and should only be called
        after an Update has been executed.

        @return the current time of day
    */
    inline float GetTime() const;

    /**
        @returns the duration of the time of day sequence, in seconds.
    */
    inline float GetDuration() const;

    /**
        Sets the length of a day

        @param fDuration the length of the day
    */
    inline void SetDuration(float fDuration);

    /**
        Set a time scale multiplier to speedup/slow/reverse the progression of 
        time in the animation. Set this value to 1 for normal animation.

        @param fScale The time multiplier to set
    */  
    inline void SetTimeMultiplier(float fScale);

    /**
        Get the time scale multiplier.

        @return the time multiplier in use
    */
    inline float GetTimeMultiplier() const;

    /**
        Generates a set of property names that can be animated by the current
        instance of the TimeOfDay system.

        @param[out] kPropertyNames List of name for the currently animating properties
    */
    void GetPropertyNames(NiTObjectSet<NiFixedString>& kPropertyNames) const;

    /**
        Generates a set of property names that can be animated by the current
        instance of the TimeOfDay system.

        @param[out] kPropertyNames List of names for the currently animating properties
        @param[out] kPropertyTypes List of Types for the currently animating properties
    */
    void GetPropertyNamesAndTypes(
        NiTObjectSet<NiFixedString>& kPropertyNames, 
        NiTObjectSet<NiFixedString>& kPropertyTypes) const;

    /**
        Returns true if the queried property is being animated by this system.

        @param kPropertyName the name of the property to query
        @return whether the property is bound or not
    */
    bool IsPropertyBound(const NiFixedString& kPropertyName) const;

    /**
        Registers a property in the scene that can be animated.
        This function is templated to allow the correct controller to be 
        generated according to what type the property is.

        @param kPropertyName the name of the property being registered
        @param pkTarget the object that manages the value
        @return true if successful
    */
    template <class T, typename V> inline bool BindProperty(
        const NiFixedString& kPropertyName, 
        const T& pkTarget);
    
    /**
        Load the animation tracks from an XML file
        @param kFileName the name of the file to load the animations from
        @return true if successful
    */
    bool LoadAnimation(const NiString& kFileName);

    /**
        Load the animation tracks from an XML file
        @param pkAnimationElement Pointer to the next xml element to load
        @return true if successful
    */
    bool LoadAnimation(efd::TiXmlElement* pkAnimationElement);

    /**
        Register all the variables available in the NiEnvironment interface
        as possible properties for animations.

        @param pkEnvironment Pointer to the environment object to register
    */
    void RegisterEnvironment(NiEnvironment* pkEnvironment);

    
    /**
        Removes all the variables available in the NiEnvironment interface
        from the associated animation properties .

        @param pkEnvironment Pointer to the environment object to unregister
    */    
    void UnregisterEnvironment(NiEnvironment* pkEnvironment);

    /**
        Register all the variables available in the NiAtmosphere interface
        as possible properties for animations. This function is automatically
        called by the RegisterEnvironment function.

        @param pkAtmosphere Pointer to the atmosphere object to register
    */
    void RegisterAtmosphere(NiAtmosphere* pkAtmosphere);

    /**
        Removes all the variables available in the NiAtmosphere interface
        from the associated animation properties .

        @param pkAtmosphere Pointer to the atmosphere object to unregister
    */ 
    void UnregisterAtmosphere(NiAtmosphere* pkAtmosphere);
    
    /**
        Register all the variables available in the NiSky interface
        as possible properties for animations. This function is automatically
        called by the RegisterEnvironment function.

        @param pkSky Pointer to the sky dome object to register
    */
    void RegisterSkyDome(NiSkyDome* pkSky);

    /**
        Removes all the variables available in the NiSkyDome interface
        from the associated animation properties .

        @param pkSky Pointer to the sky dome object to unregister
    */ 
    void UnregisterSkyDome(NiSkyDome* pkSky);

    /// @cond EMERGENT_INTERNAL
    //@{
    /** 
        Overide the update functionality of nodes so that atmospheric constants
        are updated appropriately when required.

        @see NiNode
    */
    void DoUpdate(NiUpdateProcess& kUpdate);
    virtual void UpdateDownwardPass(NiUpdateProcess& kUpdate);
    virtual void UpdateSelectedDownwardPass(NiUpdateProcess& kUpdate);
    virtual void UpdateRigidDownwardPass(NiUpdateProcess& kUpdate);
    virtual void UpdateControllers(float fTime);
    //@}
    /// @endcond

    /**
        Updates a given property's sequence with the keyframes given in parameter

        @param kPropertyName The name of the property to update
        @param uiNumKeyframes Total number of keyframes to be set to the property sequence
        @param kTimes list of individual keyframe times
        @param kValues list of individual keyframe values
    */
    void UpdatePropertySequence(
        NiFixedString kPropertyName, 
        efd::UInt32 uiNumKeyframes,
        efd::vector<float> kTimes, 
        efd::vector<efd::utf8string> kValues);

    /**
        Updates a given property's sequence with the keyframes given in parameter

        @param kPropertyName The name of the property to update
        @param uiNumKeyframes Total number of keyframes to be set to the property sequence
        @param kTimes list of individual keyframe times
        @param kValues list of individual keyframe values
    */
    void UpdatePropertySequence(
        NiFixedString kPropertyName, 
        efd::UInt32 uiNumKeyframes,
        efd::vector<efd::utf8string> kTimes, 
        efd::vector<efd::utf8string> kValues);

    /**
        Retrieves a given property's sequence

        @param kPropertyName The name of the property to get data from
        @param[out] uiNumKeyframes Total number of keyframes held in the property's sequence
        @param[out] kTimes list of individual keyframe times
        @param[out] kValues list of individual keyframe values
    */
    void GetPropertySequence(
        NiFixedString kPropertyName, 
        efd::UInt32& uiNumKeyframes,
        efd::vector<efd::utf8string>& kTimes, 
        efd::vector<efd::utf8string>& kValues);

    /**
        Removes the properties from the given list

        @param kToRemoveList list of property names to remove
    */
    void RemoveToDProperties(efd::vector<efd::utf8string> kToRemoveList);

    /**
        Helper functions that convert a color into a string

        @param kValue the color to convert
        @return the resulting string.
    */
    NiString ConvertValueToString(efd::ColorA kValue);
    
    /**
        Helper functions that convert a float into a string

        @param fValue the float to convert
        @return the resulting string.
    */
    NiString ConvertValueToString(float fValue);
    
protected:

    /// The animatable property types
    enum PropertyType
    {
        /// The default property type. No animation is possible
        TODPT_UNKNOWN = 0,

        /// A float property type
        TODPT_FLOAT = 1,

        /// A NiColorA property type
        TODPT_COLOR = 2
    };

    /// A class to store relevant data for each property registered
    class Property: public NiMemObject
    {
    public:
        /// The name of the property
        NiFixedString m_kName;

        /// The type of this property
        PropertyType m_kType;

        /// A pointer to the controller used to manipulate this property
        NiTimeOfDayControllerPtr m_spController;

        /// A pointer to the interpolator currently assigned to this property
        NiInterpolatorPtr m_spInterpolator;
    };

    /**
        Adds a property definition to the list of properties and assigns it
        a type. All other variables in the property are set to NULL.

        @param kName the new property's name
        @param kType the new property's type
        @return A pointer to the added property
    */
    Property* AddProperty(NiFixedString kName, PropertyType kType);

    /**
        Finds a particular property and returns its structure.

        @param kName name of the property to retrieve
        @return A pointer to the requested property
    */
    Property* GetProperty(NiFixedString kName);

    /**
        Loads a property definition from an XML section.

        @param pkPropertyElement The root element to load data from
    */
    void LoadPropertyDefinition(efd::TiXmlElement* pkPropertyElement);

    /**
        Loads a sequence definition from an XML section. This will build the
        animation sequence and assign it to the appropriate property if it
        already exists.

        @param pkSequenceElement the element to load data from
        @param fEndTime The time at which the animation sequence should end
    */
    void LoadSequenceDefinition(efd::TiXmlElement* pkSequenceElement, float fEndTime);

    /**
        Sets the interpolator on a particular property. If that property 
        already has a controller assigned to it, then the interpolator is
        also set on that controller and animation will begin in the next update.

        @param pkProperty pointer to the property to be associated with the interpolator
        @param pkInterpolator the interpolator to use with the property
    */
    void SetInterpolator(Property* pkProperty, NiInterpolator* pkInterpolator);    

    /// An interface class used to build animation sequences
    class SequenceBuilder: public NiMemObject
    {
    public:
        /// Destructor
        virtual ~SequenceBuilder(){}

        /**
            Sets the time and value of a particular keyframe in the animation.
            The value of the keyframe is read from the current XML element.

            @param uiKeyID the animation keyframe ID
            @param fTime the time for the keyframe
            @param pkElement pointer to the current xml element
        */
        virtual void SetKey(NiUInt32 uiKeyID, float fTime, efd::TiXmlElement* pkElement) = 0;

        /**
            Sets the time and value of a particular keyframe in the animation.

            @param uiKeyID the animation keyframe ID
            @param fTime the time for the keyframe
            @param kValueAsString keyframe value as a string
        */
        virtual void SetKey(NiUInt32 uiKeyID, float fTime, efd::utf8string kValueAsString) = 0;

        /**
            Validates the sequence and returns a NiInterpolator capable of 
            rendering that animation to a controller. A valid sequence will
            have a keyframe at the beginning and end of the total sequence.

            @param fEndTime The time at which the animation sequence should end
            @return the NiInterpolator for the animation sequence
        */
        virtual NiInterpolator* FinaliseSequence(float fEndTime) = 0;
    };

    /// A templated class used to build animation sequences for arbitrary
    /// value types.
    template <typename Value> class TSequenceBuilder: public SequenceBuilder
    {
    public:
        /// Constructor
        inline TSequenceBuilder(NiUInt32 uiNumKeys);

        /// Destructor
        inline virtual ~TSequenceBuilder();

        /**
            Sets the time and value of a particular keyframe in the animation.
            The value of the keyframe is read from the current XML element using
            an appropriate call to ReadPrimitive based on the type being 
            animated.

            @param uiKeyID the animation keyframe ID
            @param fTime the time for the keyframe
            @param pkElement pointer to the current xml element
        */
        inline virtual void SetKey(NiUInt32 uiKeyID, float fTime, efd::TiXmlElement* pkElement);

        /**
            Sets the time and value of a particular keyframe in the animation.

            @param uiKeyID the animation keyframe ID
            @param fTime the time for the keyframe
            @param kValueAsString keyframe value as a string
        */
        inline virtual void SetKey(NiUInt32 uiKeyID, float fTime, efd::utf8string kValueAsString);

        /**
            Validates the sequence and returns a NiInterpolator capable of 
            rendering that animation to a controller. A valid sequence will
            have a keyframe at the beginning and end of the total sequence.

            @param fEndTime The time at which the animation sequence should end
            @return the NiInterpolator for the animation sequence
        */
        inline virtual NiInterpolator* FinaliseSequence(float fEndTime);

    protected:
        /// The number of keys that are in this animation
        NiUInt32 m_uiNumKeys;

        /// A pointer to the key values for this animation
        Value* m_pkKeyValues;

        /// A pointer to the key times for this animation
        float* m_pkKeyTimes;
    };           

    /**
        Returns an appropriate sequence builder object to build an animation
        of the specified type. 

        @param kType the type of animation that will be build
        @param uiNumKeys the number of keys that will be in this animation
        @return the appropriate sequence builder
    */
    SequenceBuilder* GetSequenceBuilder(PropertyType kType, NiUInt32 uiNumKeys);

    /**
        Helper function used to decode a keyframe time string into a number of 
        seconds. 
        
        @param kString String to convert, must be of the form HH:MM:SS:mm
        @return converted float
    */
    float GetSecondsFromString(NiString kString);

    /**
        Helper function used to encode a time (in seconds) into a keyframe string following
        the format HH:MM:SS:mm

        @param fTime the time in seconds to convert
        @return converted string
    */
    NiString GetStringsFromSeconds(float fTime);
    
    /**
        Helper function used to convert a string into the relevant property
        type. If a string is unknown then the value TODPT_UNKNOWN is returned

        @param kType Property type as a string
        @return The corresponding property type
    */
    PropertyType GetPropertyTypeFromString(NiFixedString kType);

    /**
        Helper function used to return the PropertyType value corresponding
        to the type given.

        @return corresponding property type
    */
    template <typename Value> inline PropertyType GetPropertyTypeFromType();

    /**
        Helper function used to return the property type value of a given type as a string

        @param kType the type to get string from
        @return the type as a string
    */
    NiFixedString GetStringFromPropertyType(PropertyType kType) const;

    /// @name Configuration values
    //@{ 
    /// A list of all the properties registered that can be animated
    NiTFixedStringMap<Property*> m_kProperties;

    /// The complete duration of the time of day animation
    float m_fDuration;

    /// A multiplier to speedup/slow/reverse the progression of the animation
    float m_fTimeMultiplier;
    
    /// A flag to control execution of the animation
    bool m_bActive;
    //@}

    /// @name Time runtime calculation
    //@{ 
    /// The last scaled time that was calculated during an update
    float m_fScaledTime;

    /// The last time an update was executed
    float m_fLastTime;

    /// A list of all the active controllers being animated
    NiTPrimitiveArray<NiTimeOfDayController*> m_kControllers;
    //@}
};

NiSmartPointer(NiTimeOfDay);

#include "NiTimeOfDay.inl"

#endif
