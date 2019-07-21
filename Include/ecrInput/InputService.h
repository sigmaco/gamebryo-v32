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
#ifndef EE_INPUTSERVICE_H
#define EE_INPUTSERVICE_H

#include <efd/ISystemService.h>
#include "InputServiceActionMap.h"
#include "InputServiceEvent.h"
#include "InputActionMessage.h"

#include <egf/EntityID.h>

#include <efd/MessageService.h>
#include <efd/GenericAssetFactory.h>
#include <efd/GenericAssetLoadResponse.h>
#include <NiInputSystem.h>
#include <ecr/ecrSystemServiceIDs.h>

#define EE_NIS_FLOAT_PRECISION (1.0e-6f)
#define EE_NIS_XML_VERSION "1.0"
#define EE_NIS_ACTION_CLSID_INVALID 0
#define EE_NIS_ACTION_CLSID_ACTION 0xeda1
#define EE_NIS_ACTION_CLSID_DPAD 0xeda2
#define EE_NIS_ACTION_CLSID_STICK 0xeda3
#define EE_NIS_ACTION_CLSID_MOUSE 0xeda4

namespace ecrInput
{


/// Callback ID indicating an invalid callback.
static const efd::UInt32 kINVALID_CALLBACK = 0;


/**
    The Input Service handles user input by interfacing to the Core Runtime NiInput
    library.

    The service manages action maps, events and actions. It processes input each tick, sending
    out messages when events occur. This class also facilitates serializing all input mappings
    to and from XML files.

    The input service consists of three basic components - action maps, events and actions.
    Action maps contain events that are triggered when actions occur.

    Action maps (represented by the ecrInput::InputServiceActionMap class) are collections of
    events. An application can define any number of action maps. They are managed as a stack:
    when some action map is activated, it is "pushed" to a top of stack; when it is deactivated,
    it is "popped" from stack and the previously active action map becomes active. There is one
    action map with the name "Global" which always exists. Events added to it are always processed,
    regardless of the presence of an active action map. At each time, only one or two action maps
    process input - the global action map and the active action map (on top of the stack). If the
    stack is empty (no active action map), only the global action map is processed.  Action maps
    are named objects and are accessed through their names. Names are case-sensitive and unique.

    Each action map contains a list of named events (represented by the
    ecrInput::InputServiceEvent class). An event corresponds to a message, which is sent when
    the event occurs.  Message categories are provided by the application on event creation.
    Application receive the event by registering a handler for the particular category. This
    allows a variety of input handling approaches: a single message category may be used to
    direct all events to a single handler, or a unique category and handler may be used for
    each message, or somewhere in between. Each event must have a unique name; no event with
    a duplicate name may be created.

    Each event contains a list of actions, which are assignments to physical device controls
    (buttons, sticks, etc). Event flags specify when the event is triggered and what type of
    message it sends. An event can be triggered when:
      - Any action is triggered (default behavior) - usable for assigning a few physical keys on
        different controllers.
      - All actions are triggered simultaneously. This can be useful when an application needs to
        monitor when keys are pressed simultaneously and modifiers are not sufficient.
      - Actions are triggered as a combo - a sequence of actions where the time between each is
        smaller than some specified threshold.

    An event can send 2 types of messages:
      - An ecrInput::InputActionMessage class message reports only magnitude and user-specified
        data. Use the ecrInput::InputService::EventFlags::RETURN_MAGNITUDE event flag to
        specify this behavior. Magnitude has different meanings for different actions:
          - for digital buttons: 0.0 when button released, 1.0 when pressed
          - for analog buttons it is a magnitude of press in range [0.0,1.0]
          - for axis it is position in range [-1.0,1.0]
          - for mouse axis it is a delta from last position
      - An ecrInput::InputStickMessage class message has an additional 3 coordinates that
        report position of a mouse, stick, or d-pad. Use the
        ecrInput::InputService::EventFlags::RETURN_COORD event flag to specify this behavior.
        Button and axis coordinates are always zero. Coordinates for sticks and d-pads define point
        on a unit circle (or unit sphere in the case of a 3D custom stick), magnitude is radius
        from circle / sphere center to stick position. Coordinates for mice define change since last
        frame in arbitrary hardware units, with the mouse wheel carried in the Z coordinate;
        magnitude is always zero.

    All actions are derived from the ecrInput::InputServiceActionBase class. There are 3 types
    of actions:
      - Button / axis actions (ecrInput::InputServiceAction class) can be assigned to a
        single button or axis. They can check range, or not, and trigger on press (or enter range),
        release (or leave range), continuously while pressed or when magnitude changes. The
        action can be device-specific, or not. If the action is not device-specific, it checks
        itself on all available controllers of a compatible type.
      - D-Pad actions (ecrInput::InputServiceDPad class) are stick-like controls that monitor
        4 directional buttons and fill coordinates as a position on the unit circle,
        magnitude always equal to 1.0. It can
        be used to emulate a stick input.  A custom D-Pad can be defined by specifying semantics of
        4 keys for up, down, left and right. Predefined D-Pads include left and right game pad
        d-pads, keyboard arrows, keyboard numpad arrows, and keyboard WSAD.  Range can be
        specified. Actions can be triggered on activation or direction change, deactivation (X == Y
        == 0.0), continuously sending while active (X != 0.0 || Y != 0.0)
      - Stick actions (ecrInput::InputServiceStick class) are like analog D-Pads. They provide
        direction as coordinates on the unit circle and position of the stick as radius
        (in the magnitude field). For game
        pad sticks, the magnitude is in the range [0.0,1.0], but for joysticks the magnitude
        can be in range [0.0,sqrt(2)] because some joysticks allow moving the stick in a
        square zone.  Sticks can return actual coordinates with magnitude set to 1.0 instead of
        direction / magnitude pair. Range can be sector (where min and max magnitude specified
        along with min and max angles or pair of angles for 3D sphere) or square zone
        (where min x,y,z and max x,y,z are set). A stick can be triggered on position change or
        continuous sending and with selected range on enter, leave, and while in range.
      - Mouse actions (ecrInput::InputServiceMouse class) provide access to an attached mouse
        (or mice), updating with the change in mouse coordinates since the last frame. Units
        are the arbitrary values reported by NiInputMouse. Just like a stick, a mouse event can be
        triggered on position change or set to send updates continuously (one per frame).

    Users can subclass events or action base classes (ecrInput::InputServiceEvent and
    ecrInput::InputServiceActionBase) to define custom processing of actions and directly
    interface with input devices.

    The Input Service also offers a mode where messages are sent for every keyboard or mouse
    event. See the constructor for details. This mode is only supported for use in Gamebryo
    Tool Services and class that interact with them.

    The class documentation refers to parameters and flags defined in the Core Runtime NiInput
    reference documentation (Reference / CoreRuntime Reference / UtilityLibs / NiInput).
*/
class EE_ECRINPUT_ENTRY InputService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(InputService, efd::kCLASSID_InputService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// Flags that indicate how an action is triggered.
    enum ActionFlags
    {
        /// Message sent on button press or when an analog input enters a specified range.
        ON_ACTIVATE = 1 << 0,

        /// Message sent on button release or when an analog input leaves a specified range.
        ON_DEACTIVATE = 1 << 1,

        /// Message sent continuously while a button is pressed or when an analog input
        /// remains in a specified range
        CONTINUOUS = 1 << 2,

        /// Analog button request.  For digital buttons, the magnitude can only be 0 or 1.
        /// This is only valid for button actions.
        ANALOG = 1 << 3,

        /// Check the range for analog inputs.  This is not valid for digital buttons.
        RANGED = 1 << 4,

        /// Transform stick coordinates from a unit square to a unit sphere.
        SPHERIC_COORDS = 1 << 5,

        /// Send a message only if the event occurred on the specified DeviceID.  If this flag is
        /// not set, then check all available devices of the corresponding type.  Currently, only
        /// multiple game pads are supported.
        DEVICE_SPECIFIC = 1 << 6,

        /// Send a message only if modifiers match. This gives the ability to trigger action only
        /// if specific buttons are pressed or released. Modifiers are device-specific and listed
        /// in the device documentation: NiInputKeyboard and NiInputMouse. GamePads have no
        /// modifiers.
        USE_MODIFIERS = 1 << 7,

        /// This flag reverses the X axis. Applicable for sticks and D-Pads.
        REVERSE_X_AXIS = 1 << 8,

        /// This flag reverses the Y axis. Applicable for sticks and D-Pads.
        REVERSE_Y_AXIS = 1 << 9,

        /// This flag reverses the Z axis. Applicable for sticks and D-Pads.
        REVERSE_Z_AXIS = 1 << 10
    };

    /// Event flags that specify how actions trigger events and what messages get sent.
    enum EventFlags
    {
        /// Event sends ecrInput::InputActionMessage.
        RETURN_MAGNITUDE = 0x001,

        /// Event sends ecrInput::InputStickMessage.
        RETURN_COORD = 0x002,

        /// Mask for message type.
        RETURN_MASK = 0x00ff,

        /// Specifies that all actions in the event must simultaneously trigger for message to be
        /// sent. It is recommended to set the action flags to continuously report while pressed /
        /// in range. If no ACTION_* flags are specified, the default behavior is to send a message
        /// when any of the actions are triggered.
        ACTION_AND = 0x100,

        /// Specifies that this is a combo event. A combo event fires when a sequence of actions
        /// completes within a given time.
        ACTION_COMBO = 0x200,

        /// This flag specifies that individual matching actions that are part of the combo
        /// will also be sent.
        COMBO_SEND_ACTIONS = 0x400,

        /// Mask for action type.
        ACTION_MASK = 0xff00
    };

    /// Specifies the stick used for an input action.
    enum StickType
    {
        /// This type is only used to detect uninitialized objects.
        INVALID_STICK = -1,

        /// Left stick of game pad or joystick primary stick.
        GP_STICK_LEFT = NiInputGamePad::NIGP_STICK_LEFT,

        /// Right stick of game pad or some control (analog throttle, pedals, etc) on other game
        /// controllers.
        GP_STICK_RIGHT = NiInputGamePad::NIGP_STICK_RIGHT,

        /// Stick X1, can appear on advanced controllers.
        GP_STICK_X1 = NiInputGamePad::NIGP_STICK_X1,

        /// Stick X2, can appear on advanced controllers.
        GP_STICK_X2 = NiInputGamePad::NIGP_STICK_X2,

        /// Custom stick. Semantics of 3 axes must be specified.
        CUSTOM_STICK
    };

    /// Specifies the directional pad used for an input action.
    enum DPadType
    {
        /// This type is only used to detected uninitialized objects.
        INVALID_DPAD = -1,

        /// Game pad left or primary joystick directional pad.
        GP_DPAD_L,

        /// Directional pad, formed by game pad right 4 buttons buttons.
        GP_DPAD_R,

        /// Directional pad, formed by keyboard arrow keys.
        KEY_DPAD_ARROWS,

        /// Directional pad, formed by keyboard numeric pad arrow keys.
        KEY_DPAD_NUMPAD,

        /// Directional pad, formed by keyboard W, S, A and D keys.
        KEY_DPAD_WSAD,

        /// Custom D-Pad, formed by any 4 buttons on keyboard or game pad.
        /// All 4 buttons must be on one device.
        CUSTOM_DPAD
    };

    /// For input script actions, describe the way in which the callback behavior is
    /// to be invoked - normal (via SendEvent) or immediate (via CallBehavior).
    enum CallbackType
    {
        CALLBACK_NORMAL,   ///< Normal callback type - SendEvent will be used
        CALLBACK_IMMEDIATE ///< Immediate callback type - CallBehavior will be used
    };

    /// Typedef for filtering function, which can change raw stick data.
    typedef void (*InputFilteringCallback)(
        efd::UInt32 appData,
        efd::Float32 &x,
        efd::Float32 &y,
        efd::Float32 &z);

    /// @name Construction and Destruction.
    //@{
    /**
        Constructs the input service.

        The input specific data is not actually allocated or created until the service's
        OnInit method is invoked.

        By default, the Input Service manages only Action Map based messaging. However,
        messages for individual mouse and keyboard events will be sent out
        when the sendSingleMessages parameter is true, regardless of whether or not those
        events are action mapped. See ecrInput::MouseMessage (and derived classes),
        ecrInput::KeyDownMessage and ecrInput::KeyUpMessage. When operating in this mode,
        events are sent for every mouse and keyboard event, and the applications must filter
        the input appropriately.

        For legacy compatibility, the Input Service will send either an InputActionMessage or an
        InputStickMessage message to the category set for each event in the actionmap data file
        whenever that event is triggered.  Now it is recommended that you instead call the
        ListenForInput*Event events to request callbacks for specific events.  If you wish to
        disable this additional message and use only the registered callbacks then you can pass
        false for the legacyMode parameter.
    */
    InputService(const efd::Bool sendSingleMessages = false, const efd::Bool legacyMode = false);

    /// Virtual destructor.
    virtual ~InputService();
    //@}

    /// @name System Service methods
    //@{

    /// Returns "InputService".
    virtual const char* GetDisplayName() const;

    /**
        Pre-initialization function.

        On the Win32 platform, the window and instance reference are discovered from the
        efd::Win32PlatformService, if present. If not present, the application must call
        SetInstanceRef and SetWindowRef before OnInit is called for the service.

        The service also subscribes to messages for action map lookup.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        Initialize the core runtime input system and start processing input.

        The default platform-dependent parameters are used with NiInputSystem::Create.
        Devices are discovered and opened.

        Initialization will fail if there is no keyboard or mouse on Win32, or if devices cannot
        otherwise be enumerated.
    */
    virtual efd::AsyncResult OnInit();

    /// Process global and active action maps and send input messages.
    virtual efd::AsyncResult OnTick();

    /// Destroy action maps, events, and actions and release core runtime input system.
    virtual efd::AsyncResult OnShutdown();

    //@}

    /// @name Win32 methods
    ///
    /// The settings in this section must be done before OnInit in order to take effect.
    //@{

    /**
        Set instance reference.

        Required for creation of input system on Win32 when the efd::Win32PlatformService is not
        present. This method must be called before OnPreInit.
    */
    inline void SetInstanceRef(efd::InstanceRef instanceRef);

    /**
        Set window reference.

        Required for creation of input system on Win32 when the efd::Win32PlatformService is not
        present. This method must be called before OnPreInit.
    */
    inline void SetWindowRef(efd::WindowRef winRef);

    /// Controls if the keyboard will be used exclusively by application, or not.
    ///
    ///  This method must be called before OnInit.
    inline void SetExclusiveKeyboard(efd::Bool exclusive);

    /// Controls if the mouse will be used exclusively by application, or not.
    ///
    ///  This method must be called before OnInit.
    inline void SetExclusiveMouse(efd::Bool exclusive);

    //@}

    /**
        @name Event response handling

        Methods for requesting notification when various events are triggered.  Response can be
        requested via Message or via Behavior invocation.  Events only send notifications for
        registered actions.
    */
    //@{

    /**
        Install an input event listener to call a behavior when the event fires.
        This function works for both InputActionMessage and InputStickMessage.

        @param inputEvent Name of the input event (should match the actionmap file).
        @param entityID Entity which should receive the callback
        @param behavior Name of the behavior which should be called
        @param type Type of callback - immediate (call with CallBehavior)
                 or normal (call with SendEvent)

        @return Either kINVALID_CALLBACK or a callback ID.  The callback ID can be used
             to cancel the callback later.
    */
    efd::UInt32 ListenForInputEvent(
        efd::utf8string inputEvent,
        egf::EntityID entityID,
        efd::utf8string behavior,
        CallbackType type = CALLBACK_NORMAL);

    /**
        Delete all registered input events for a given entityID.

        @param entityID Entity to clear.
    */
    void ClearRegisteredInputEvents(egf::EntityID entityID);

    /**
        Install an input event listener to call a C++ function when the event fires.
        This function works for InputActionMessage.

        @param inputEvent Name of the input event (should match the actionmap file).
        @param callback Callback category which will receive InputActionMessage messages.
        @param userdata User-supplied data pointer which will be delivered with the callback.

        @return Either kINVALID_CALLBACK or a callback ID.  The callback ID can be used
             to cancel the callback later.
    */
    efd::UInt32 ListenForInputActionEvent(
        efd::utf8string inputEvent,
        efd::Category callback,
        void *userdata = NULL);

    /**
        Install an input event listener to call a C++ function when the event fires.
        This function works for InputStickMessage.

        @param inputEvent Name of the input event (should match the actionmap file).
        @param callback Callback category which will receive InputStickMessage messages.
        @param userdata User-supplied data pointer which will be delivered with the callback.

        @return Either kINVALID_CALLBACK or a callback ID.  The callback ID can be used
             to cancel the callback later.
    */
    efd::UInt32 ListenForInputStickEvent(
        efd::utf8string inputEvent,
        efd::Category callback,
        void *userdata = NULL);

    /**
        Delete the specified callback.

        @param callbackID ID of the callback to delete.  The ID is returned from the various
                       ListenFor*Event calls.
    */
    void ClearRegisteredInputEvent(efd::UInt32 callbackID);

    //@}


    /// @name Event Management Functions
    //@{

    /// Searches for the event in all action maps and returns a pointer to it.
    ///
    /// Returns NULL if event could not be found.
    InputServiceEvent* FindEvent(const efd::utf8string& eventName) const;

    /**
        Searches for a given event by name in all action maps.

        If none is found, it creates a message with the given category, flags, and timeout.

        Returns a pointer to the found or created event.
    */
    InputServiceEvent* FindCreateEvent(
        const efd::utf8string& eventName,
        efd::Category msgCat,
        efd::UInt32 eventFlags = RETURN_MAGNITUDE,
        efd::Float32 timeout = 1.0f);

    ///

    /// Returns the message category for the event with the given name.
    ///
    /// If the event doesn't exist, it returns kCAT_INVALID.
    inline efd::Category GetEventMsgCategory(const efd::utf8string& eventName) const;

    /**
        Query flags for the event with the given name.

        The eventFlags returned will be an ORed combination of ecrInput::InputService::EventFlags.

        Returns false if event doesn't exist, otherwise true.
    */
    inline efd::Bool GetEventFlags(
        const efd::utf8string& eventName,
        efd::UInt32& eventFlags) const;

    /// Query timeout for the event with the given name.
    ///
    /// Returns false if event doesn't exist.
    inline efd::Bool GetEventTimeout(
        const efd::utf8string& eventName,
        efd::Float32& timeout) const;

    /**
        Set the flags for the event with the given name.

        The eventFlags must be an ORed combination of ecrInput::InputService::EventFlags.

        Returns false if event doesn't exist.
    */
    inline efd::Bool SetEventFlags(
        const efd::utf8string& eventName,
        efd::UInt32 eventFlags);

    /// Set the timeout for the event with the given name.
    ///
    /// Returns false if event doesn't exist.
    inline efd::Bool SetEventTimeout(
        const efd::utf8string& eventName,
        efd::Float32 timeout);

    //@}

    /// @name Action Map functions
    //@{

    /**
        Create a new action map with the given name.

        @param actionMapName The name to use for the new action map.
        @return Pointer to the created action map or NULL if there was an error,
            such as if the action map with the provided name already exists.
    */
    inline InputServiceActionMap* CreateActionMap(const efd::utf8string& actionMapName);

    /// Return the number of action maps.
    inline efd::UInt32 GetActionMapCount() const;

    /// Returns a pointer to the action map with the given name or NULL if none exists.
    inline InputServiceActionMap* GetActionMap(const efd::utf8string& mapName) const;

    /// Returns a pointer to the action map with the given index or NULL if the index is invalid.
    inline InputServiceActionMap* GetActionMapAt(efd::UInt32 mapIdx) const;

    /// Query the name of the action map at the given index.
    ///
    /// Returns false for invalid indices.
    inline efd::Bool GetActionMapName(efd::UInt32 mapIdx, efd::utf8string& mapName) const;

    /// Removes the action map at the given index.
    ///
    /// Returns false for invalid indices.
    inline efd::Bool RemoveActionMapAt(efd::UInt32 mapIdx);

    /// Removes all defined action maps and clears the global action map.
    void DeleteActionMaps();

    /// Queries the name of the active action map.
    ///
    /// Returns false if the stack is empty.
    inline efd::Bool GetActiveActionMapName(efd::utf8string& actionMapName) const;

    /// Returns a pointer to the active action map on top of the stack.
    ///
    /// Returns NULL if empty.
    inline InputServiceActionMap* GetActiveActionMap() const;

    /// Returns a pointer to the global action map.
    ///
    /// This map is always named "Global".
    inline InputServiceActionMap* GetGlobalActionMap();

    /// Push the action map with a given name to the top of the stack, making it active.
    ///
    /// If the action map has not been created, this returns false.
    inline efd::Bool PushActionMap(const efd::utf8string& actionMapName);

    /// Push the action map with a given index to the top of the stack, making it active.
    ///
    /// If the index is invalid, this returns false.
    inline efd::Bool PushActionMap(efd::UInt32 mapIdx);

    /// Pop the current action map and activate the previous one (if any).
    ///
    /// Returns false if the stack is empty.
    inline efd::Bool PopActionMap();

    /**
        Save all action maps (including the global one) to an XML file.

        @param fileName Name of file.
        @return True on success or false if file cannot be created.
    */
    efd::Bool SaveAllActionMaps(const efd::utf8string& fileName);

    /**
        Request loading of an action map.

        The loading is asychronous. An InputActionMapsLoaded message will be sent on the category
        given by ecrInput::InputService::MessageCategory() when the load is completed. The
        message will be sent even when the load fails, so check the success status of the message
        when it is received. The actions maps requested by this call will not be available
        before the InputActionMapsLoaded message is sent by the service.

        @param urn Action map urn to load. Be sure that the urn locates only a single
            action map file; the load will fail otherwise.
        @return True if the load request could be sent, otherwise false. The send will fail
            if there is no asset factory manager available or if the given urn does not contain
            "urn".
    */
    bool LoadAllActionMaps(const efd::utf8string& urn);

    //@}

    /// @name Action Creation Shortcuts
    //{@

    /// Create an instance of an action by class ID.
    static InputServiceActionBase* CreateAction(efd::UInt32 actionClsID);

    /**
        Add a button or axis action.

        If the event with specified name does not exist, a new event is created in the active
        action map. If no action map is active, then the event is added to the global action map.
        A unique message type is automatically assigned for any new event.
        A button or axis action added in this way will always return the magnitude in an
        ecrInput::InputActionMessage.

        @param eventName Name of the event.
        @param actionCat Message category.
        @param semantic Semantic associated with this action, from NiAction::Semantic.
        @param actionFlags An ORed combination of ecrInput::InputService::ActionFlags.
        @param appData User-defined data.
        @param deviceID Device on which this action should be checked. Typically, deviceID is
            always 0 for keyboard and mouse, and may be 0 to NiInputSystem::MAX_GAMEPADS for
            GamePads.
        @param modifiers Action modifiers. These should be an ORed combination of modifiers
            specific to the device type, taken from one of NiInputKeyboard::Modifiers or
            NiInputMouse::Modifiers (there are no modifiers for GamePad input).
        @param minRange Minimum range of magnitude / axis value.
        @param maxRange Maximum range of magnitude / axis value.
        @return True if the action was added, or false if the parameters are invalid.
    */
    efd::Bool AddAction(
        const efd::utf8string& eventName,
        efd::Category actionCat,
        efd::UInt32 semantic,
        efd::UInt32 actionFlags,
        efd::UInt32 appData = 0,
        efd::UInt32 deviceID = 0,
        efd::UInt32 modifiers = 0,
        efd::Float32 minRange = -1.0f,
        efd::Float32 maxRange = 1.0f);

    /**
        Add a D-Pad action.

        If the event with specified name does not exist, a new event is
        created in the active action map. If no action map is active, then the event is added to
        the global action map. A unique message type is automatically assigned for any new event.
        A D-Pad action added in this way will always return the coordinates in an
        ecrInput::InputStickMessage.

        @param eventName Name of the event.
        @param actionCat Message category.
        @param dpadType Pad type, from ecrInput::InputService::DPadType.
        @param actionFlags An ORed combination of ecrInput::InputService::ActionFlags.
        @param appData User-specified data.
        @param deviceID Device on which this action should be checked. Typically, deviceID is
            always 0 for keyboard and mouse, and may be 0 to NiInputSystem::MAX_GAMEPADS for
            GamePads.
        @param modifiers Modifiers for this action. These should be an ORed combination of
            modifiers specific to the device type, taken from one of NiInputKeyboard::Modifiers or
            NiInputMouse::Modifiers (there are no modifiers for GamePad input).
        @param upSemantic Semantic of up button for custom D-Pad.
        @param downSemantic Semantic of down button for custom D-Pad.
        @param leftSemantic Semantic of left button for custom D-Pad.
        @param rightSemantic Semantic of right button for custom D-Pad.
        @return True if the action was added, or false if the parameters are invalid.
    */
    efd::Bool AddDPad(
        const efd::utf8string& eventName,
        efd::Category actionCat,
        InputService::DPadType dpadType,
        efd::UInt32 actionFlags,
        efd::UInt32 appData = 0,
        efd::UInt32 deviceID = 0,
        efd::UInt32 modifiers = 0,
        efd::UInt32 upSemantic = 0,
        efd::UInt32 downSemantic = 0,
        efd::UInt32 leftSemantic = 0,
        efd::UInt32 rightSemantic = 0);

    /**
        Add a stick action.

        If the event with specified name does not exist, a new event is
        created in the active action map. If no action map is active, then the event is added to
        the global action map.  A unique message type is automatically assigned for any new event.
        A D-Pad action added in this way will always return the coordinates in an
        ecrInput::InputStickMessage.

        @param eventName Name of the event.
        @param actionCat Message category.
        @param stickType See InputService::StickType.
        @param actionFlags An ORed combination of ecrInput::InputService::ActionFlags.
        @param appData User-specified data.
        @param deviceID Which device to listen for events on. Typically, deviceID is
            always 0 for keyboard and mouse, and may be 0 to NiInputSystem::MAX_GAMEPADS for
            GamePads.
        @param modifiers Device modifiers. These should be an ORed combination of
            modifiers specific to the device type, taken from one of NiInputKeyboard::Modifiers or
            NiInputMouse::Modifiers (there are no modifiers for GamePad input).
        @param minRangeX Minimum range on X axis for this action.
        @param maxRangeX Maximum range on X axis for this action.
        @param minRangeY Minimum range on Y axis for this action.
        @param maxRangeY Maximum range on Y axis for this action.
        @param minRangeZ Minimum range on Z axis for this action.
        @param maxRangeZ Maximum range on Z axis for this action.
        @param pFilter A post-process callback for input.
        @param axisSemanticX Semantic of the X axis for custom stick.
        @param axisSemanticY Semantic of the Y axis for custom stick.
        @param axisSemanticZ Semantic of the Z axis for custom stick.
        @return True if the action was added, or false if the parameters are invalid.
    */
    efd::Bool AddStick(
        const efd::utf8string& eventName,
        efd::Category actionCat,
        InputService::StickType stickType,
        efd::UInt32 actionFlags,
        efd::UInt32 appData = 0,
        efd::UInt32 deviceID = 0,
        efd::UInt32 modifiers = 0,
        efd::Float32 minRangeX = -1.0f,
        efd::Float32 maxRangeX = 1.0f,
        efd::Float32 minRangeY = -1.0f,
        efd::Float32 maxRangeY = 1.0f,
        efd::Float32 minRangeZ = -1.0f,
        efd::Float32 maxRangeZ = 1.0f,
        InputFilteringCallback pFilter = NULL,
        efd::UInt32 axisSemanticX = 0,
        efd::UInt32 axisSemanticY = 0,
        efd::UInt32 axisSemanticZ = 0);

    //@}

    /// Accessor for the underlying core runtime input system.
    inline NiInputSystem* GetInputSystem();

    /**
        Accessor for the category used for Input Service Messages.

        This category is used for ActionMapLoadResponse messages.

        Action response messages are sent on the category with which the action was registered.

        Single input messages (when enabled) are sent on the default local category.
    */
    inline static efd::Category MessageCategory();

    /// @cond EMERGENT_INTERNAL

    /// Used internally to fire the correct behavior or message callback when a button related
    /// action has occurred.
    void FireButtonAction(
        const efd::utf8string& eventName,
        efd::UInt32 appData,
        efd::Float32 magnitude,
        efd::Category legacyCategory) const;

    /// Used internally to fire the correct behavior or message callback when a control stick
    /// related action has occurred.
    void FireStickAction(
        const efd::utf8string& eventName,
        efd::UInt32 appData,
        efd::Float32 magnitude,
        efd::Category legacyCategory,
        efd::Float32 x,
        efd::Float32 y,
        efd::Float32 z) const;

    /// Asset load response message handler.
    void HandleAssetLoadResponse(
        const efd::AssetLoadResponse* pMessage,
        efd::Category targetChannel);

    /// @endcond

protected:
    /// For registering input action callbacks, describe the input type a given callback is
    /// designed to handle.
    enum InputType
    {
        /// Send an InputActionMessage message in response to the event (for normal button press
        /// style inputs).
        INPUTTYPE_ACTION,

        /// Send an InputStickMessage message in response to the event (for analog stick, mouse, or
        /// DPad style inputs).
        INPUTTYPE_STICK,

        /// Fire a behavior in response to the event.  The behavior will receive parameters that
        /// define whether this is an action or stick input event.
        INPUTTYPE_NORMAL_BEHAVIOR,

        /// Fire an immediate behavior in response to the event.  The behavior will receive
        /// parameters that define whether this is an action or stick input event.  You should
        /// only use Immediate Behaviors when it is strictly required (if single-frame timing is
        /// required or the behavior must be able to run while the scheduler is paused).
        INPUTTYPE_IMMEDIATE_BEHAVIOR,
    };

    /**
        Inner class to hold a single input event behavior callback request
    */
    class InputEventCallback
    {
    public:
        /// Constructor used when installing an entity-behavior callback
        InputEventCallback(
            InputType type,
            efd::UInt32 callbackID,
            egf::EntityID entityID,
            efd::utf8string m_strBehavior);

        /// Constructor used when creating a callback for InputActionEvents messages
        InputEventCallback(
            InputType type,
            efd::UInt32 callbackID,
            efd::Category callback,
            void *userdata);

        /// Event type
        InputType m_type;

        /// ID of this callback
        efd::UInt32 m_callbackID;

        /// EntityID, if this is a behavior-based callback.
        egf::EntityID m_entityID;

        /// Behavior name, if this is a behavior-based callback.
        efd::utf8string m_strBehavior;

        /// Category to send InputActionEvents to, if appropriate.
        efd::Category m_callback;

        /// Userdata to be passed to a C++ callback function.
        void* m_userdata;
    };

    /// Load string semantic -> semantic value translation map.
    static void LoadTranslationMap();

    /// Unload string semantic -> semantic value translation map.
    static void UnloadTranslationMap();

    /**
        Handle response from the asset loader.

        @param fileName Path to the action map to load.
        @param pXMLString Pointer to an xml string.
        @return True on success or false if file cannot be opened or is invalid.
    */
    efd::Bool ParseAllActionMaps(const char* fileName, const char* pXMLString);

    /// Process old-style input and send messages
    void ProcessSingleMessageInput();

    /// Process global and active action maps events
    void ProcessInput();

    /// Helper for either sending a message or calling a behavior in response to input events.
    void CheckRegisteredHandlers(
        const efd::utf8string& eventName,
        efd::UInt32 appData,
        efd::Float32 magnitude,
        efd::Float32 x = 0.0f,
        efd::Float32 y = 0.0f,
        efd::Float32 z = 0.0f) const;

    efd::stack<InputServiceActionMap*> m_actionMapStack;
    efd::vector<InputServiceActionMap*> m_actionMaps;
    InputServiceActionMap m_globalActionMap;

    NiInputSystem::CreateParams* GetInputSystemCreateParams();

    efd::InstanceRef m_instanceRef;
    efd::WindowRef m_windowRef;
    efd::Bool m_exclusiveKeyboard;
    efd::Bool m_exclusiveMouse;
    NiInputSystemPtr m_spInput;

    efd::MessageService* m_pMessageService;

    efd::GenericAssetFactory* m_pAssetFactory;

    /// List of all registered input callbacks
    typedef EE_STL_NAMESPACE::pair<efd::utf8string, InputEventCallback> InputEventMapEntry;
    typedef EE_STL_NAMESPACE::multimap<
        efd::utf8string,
        InputEventCallback,
        EE_STL_NAMESPACE::less<efd::utf8string>,
        efd::CustomAllocator<InputEventMapEntry> > InputEventMap;
    InputEventMap m_inputEventList;

    /// Last used context for ListenFor*Event return values
    efd::UInt32 m_handlerCount;

    /// When true, every action fires either a InputActionMessage or a InputStickMessage message
    /// to the legacy category set in the actionmap data file.
    efd::Bool m_bLegacyMode;

    /// Boolean for whether we are in "tool" mode where we send messages for every keypress.
    bool m_sendSingleMessages;

    /// Category used for my asset lookup responses
    static efd::Category ms_inputServiceCategory;

#if defined(EE_PLATFORM_XBOX360) || defined(EE_PLATFORM_PS3)
    bool m_keyW;
    bool m_keyA;
    bool m_keyS;
    bool m_keyD;
    bool m_keyUp;
    bool m_keyLeft;
    bool m_keyRight;
#endif
};

typedef efd::SmartPointer<InputService> InputServicePtr;

} // end namespace ecrInput

#include "InputService.inl"

#endif // EE_INPUTSERVICE_H
