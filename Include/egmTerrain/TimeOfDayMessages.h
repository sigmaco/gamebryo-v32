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
#ifndef EE_EGFTIMEOFDAYMESSAGE_H
#define EE_EGFTIMEOFDAYMESSAGE_H

#include <ecr/ecrMessageIDs.h>
#include <efd/IMessage.h>

#include "egmTerrainLibType.h"

namespace egmTerrain
{

/**
    Helper class defining the time of day message category
*/
class EE_EGMTERRAIN_ENTRY ToDMessagesConstants 
{
public:
    /// The Time of day message category
    static const efd::Category ms_timeOfDayMessageCategory;
};

/**
    This class defines a message sent by an application to set whether the time of day should
    be animated or not.
*/
class EE_EGMTERRAIN_ENTRY ToDAnimationChangedMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ToDAnimationChangedMessage, efd::kMSGID_ToDAnimationChangedMessage, 
        efd::IMessage);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /**
        The message's factory method. 
        @return a pointer to the newly instanciated object.
    */
    static efd::IBasePtr FactoryMethod();
    virtual efd::ClassID GetClassID() const { return CLASS_ID; }

    /**
        Default constructor
    */
    ToDAnimationChangedMessage() { }
    virtual ~ToDAnimationChangedMessage() { }

    virtual void Serialize(efd::Archive& ar);

public:

    /**
        Sets the animation's status for the message.
    */
    inline void SetAnimationStatus(bool status);

    /**
        Gets the animation's status for the message.
    */
    inline bool GetAnimationStatus() const;

    /**
        Sets the animation's speed multiplier for the message.
    */
    inline void SetAnimationSpeedMultiplier(efd::UInt32 uiMultiplier);
    
    /**
        Sets the animation's speed multiplier for the message.
    */
    inline efd::UInt32 GetAnimationSpeedMultiplier() const;

protected:

    /// The status the animation should be set to
    bool m_animationRunning;

    /// The speed multiplier for the animation
    efd::UInt32 m_speedMultiplier;
};

/// Defines a smart pointer (reference counted) for the ToDAnimationChangedMessage class
typedef efd::SmartPointer<ToDAnimationChangedMessage> ToDAnimationChangedMessagePtr;


/**
    This class defines messages sent by an application to set the Time of Day current time.
*/
class EE_EGMTERRAIN_ENTRY ToDTimeChangedMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ToDTimeChangedMessage, efd::kMSGID_ToDTimeChangedMessage, efd::IMessage);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /**
        The message's factory method. 
        @return a pointer to the newly instanciated object.
    */
    static efd::IBasePtr FactoryMethod();

    virtual efd::ClassID GetClassID() const { return CLASS_ID; }

    /**
        Default constructor
    */
    ToDTimeChangedMessage() { }

    virtual ~ToDTimeChangedMessage() { }

    virtual void Serialize(efd::Archive& ar);

public:

    /**
        Sets the new time for the message.
    */
    inline void SetNewTime(float time);

    /**
        Gets the new time for the message.
    */
    inline float GetNewTime() const;

protected:

    /// The new time value
    float m_currentTime;
};

/// Defines a smart pointer (reference counted) for the ToDTimeChangedMessage class
typedef efd::SmartPointer<ToDTimeChangedMessage> ToDTimeChangedMessagePtr;

/**
    This class defines messages sent by an application when a tod property keyframe was
    added, removed or changed. It holds the entire collection of keyframes in order to update the
    animation sequence
*/
class EE_EGMTERRAIN_ENTRY ToDKeyframesChangedMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ToDKeyframesChangedMessage, 
        efd::kMSGID_ToDKeyframesChangedMessage, efd::IMessage);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /**
        The message's factory method. 
        @return a pointer to the newly instanciated object.
    */
    static efd::IBasePtr FactoryMethod();

    virtual efd::ClassID GetClassID() const { return CLASS_ID; }

    /**
        Default constructor
    */
    ToDKeyframesChangedMessage() { }

    virtual ~ToDKeyframesChangedMessage() { }

    virtual void Serialize(efd::Archive& ar);

public:

    /**
        Sets the property name for the message.
    */
    inline void SetPropertyName(efd::utf8string name);

    /**
        Gets the property name for the message.
    */
    inline efd::utf8string GetPropertyName() const;

    /**
        Sets the number of keyframes associated with the property for the message.
    */
    inline void SetNumberOfKeyframes(efd::UInt32 num);

    /**
        Gets the number of keyframes associated with the property for the message.
    */
    inline efd::UInt32 GetNumberOfKeyframes() const;

    /**
        Adds a keyframe in the message's keyframe vectors.

        @param time The time of the keyframe.
        @param keyframeValue The value of the keyframe.
    */
    inline void AddKeyframe(float time, efd::utf8string keyframeValue);

    /**
        Returns the keyframe time and value associated with the given index.

        @param index the index of the keyframe to retrieve data from.
        @param[out] time the time of the requested keyframe.
        @param[out] keyframeValue the value of the requested keyframe.
    */
    inline void GetKeyframe(efd::UInt32 index, float& time, efd::utf8string& keyframeValue) const;

protected:

    /// The property name the message is sent for
    efd::utf8string m_propertyName;

    /// The number of keyframes associated with the property
    efd::UInt32 m_numberOfKeyframes;

    /// The keyframes' times for the property
    efd::vector<float> m_keyframesTimes;

    /// The keyframes' values for the property
    efd::vector<efd::utf8string> m_keyframesValue;
};

/// Defines a smart pointer (reference counted) for the ToDKeyframesChangedMessage class
typedef efd::SmartPointer<ToDKeyframesChangedMessage> ToDKeyframesChangedMessagePtr;

};

#include "TimeOfDayMessages.inl"

#endif //EE_EGFTIMEOFDAYMESSAGE_H