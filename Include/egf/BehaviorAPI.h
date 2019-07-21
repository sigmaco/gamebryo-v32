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

#if !defined(EE_BEHAVIORAPI_H)
#define EE_BEHAVIORAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <egf/EntityID.h>
#include <egf/EventID.h>
#include <egf/FlatModel.h>
#include <egf/BehaviorDescriptor.h>
#include <efdNetwork/NetCategory.h>
#include <efd/IMessage.h>


// NOTE: This is a SWIG parsed file.  All methods listed in this file will have script wrappers
// generated.
//
// A note on argument types:
//
// Given any type the SWIG generated bindings will make certain assumptions about whether the
// parameter is an input argument, and output argument, or an input-output argument.  Given
// a type T, it will be treated as follows:
//
//    |---------------|---------------|------------------------------------------------------
//    | typename:     | treated as:   | notes:
//    |---------------|---------------|------------------------------------------------------
//    | T             | Input         |
//    | const T&      | Input         |
//    | const T*      | Input         | Pointer must NOT be NULL
//    | T*            | Output        | Pointer must NOT be NULL
//    | T&            | Input-Output  |
//    |---------------|---------------|------------------------------------------------------
//
// The one exception to the argument type rules above is efd::ParameterList.  efd::ParameterList*
// is treated as a basic type for the purpose of these rules, not efd::ParameterList itself.  For
// example, this means that "efd::ParameterList*" is treated as a plain ParameterList Input argument
// and "efd::ParameterList*&" is treated as an in-out efd::ParameterList parameter.  One additional
// special case, for convenance "efd::ParameterList&" is also treated as an in-out parameter.

/**
    The BehaviorAPI namespace defines functions that are wrapped by SWIG and made available in
    scripting languages. This exposes a rich set of features to the scripting runtimes. SWIG will
    bind these functions to the script engine by creating a _wrap file and exposing an
    initialization function. This initialization function must be executed after the runtime
    is created but before any scripts are executed.

    When BehaviorAPI is included in a dynamic module/DLL, the initialization function is specified
    in the config.ini (or equivalent) file and loaded during script runtime startup. The
    configuration section for the dynamic library binding looks like this:

    Python:
    @verbatim
    [ScriptEngine.Python]
    LoadBuiltin#=egfPython!init_BehaviorAPI
    @endverbatim

    Lua:
    @verbatim
    [ScriptEngine.Lua]
    LoadBuiltin#=egfLua!luaopen_BehaviorAPI
    @endverbatim

    When BehaviorAPI is included as part of a static library, initialization is still required but
    not driven by the configuration file. Instead, the application must tell the scripting runtime
    to call the initialization function as part of the runtime startup sequence. This is done
    by calling the runtimes AddStaticBuiltinInitFunction from main. It looks something like this:

    Python:main.cpp
    @verbatim
    extern "C" void init_BehaviorAPI();
    ...
    SchedulerPython::AddStaticBuiltinInitFunction(init_BehaviorAPI);
    @endverbatim

    Lua:main.cpp
    @verbatim
    extern "C" void luaopen_BehaviorAPI(lua_State *);
    ...
    SchedulerLua::AddStaticBuiltinInitFunction(luaopen_BehaviorAPI)
    @endverbatim


    SWIG will ignore this namespace but C++ won't.  since the namespace name matches the module
    name we end up with effectively the same syntax.  BehaviorAPI::Method for C++ and the
    similar BehaviorAPI.Method for Python and Lua.
 */
namespace BehaviorAPI
{

/// @name Behavior API User Functions
//@{

/**
    Returns the real time in seconds since the start of the process (framework).

    @return Floating point time in seconds.
*/
EE_EGF_ENTRY efd::Float64 GetServiceManagerTime();

/**
    Returns the game time in seconds.  Game Time is maintained by the scheduler and supports
    features like pausing the clock, applying a scale verse real time, entering a "fixed delta"
    mode an other features.  All behavior related events operate relative to game time.

    @return Floating point time in seconds.
*/
EE_EGF_ENTRY efd::Float64 GetGameTime();

/**
    Returns the name of the model of the entity that is executing.

    @return The model name.
*/
EE_EGF_ENTRY const efd::utf8string& GetModelName();

/**
    Creates a new category ID from its base values and returns the new Category.

    @param usage Expected usage for this category ID - @see efd::UniversalID::ExpectedChannelUsage.
    @param netID The Net ID that created this ID.
    @param baseID The base ID.
    @return The new category.
*/
EE_EGF_ENTRY efd::Category CreateCategory(
    efd::UInt8 usage,
    efd::UInt32 netID,
    efd::UInt32 baseID);

/**
    Creates a new Category with a fixed base id and expected usage for easier script category
    creation.
    Uses the BaseID efd::kBASEID_ApplicationCategory and usage of efd::UniversalID::ECU_Any.
    @param appCategoryID The application specified unique id to be set into the Net ID bitfield.
    @return The new category.
*/
EE_EGF_ENTRY efd::Category CreateApplicationCategory(efd::UInt32 appCategoryID);


/**
    Get a public Category as determined by the ISystemService ClassID and an optional index.
    If multiple public Categories are desired, categoryIndex can be set to a value other than
    the default to create a new public Category.
    Public Categories are not unique to a specific process. Categories generated by this
    function will be the same if multiple processes pass in the same values for serviceID and
    categoryIndex. Subsequent calls to this method by the any process will produce
    the same result.

    @param serviceID The ClassID of the ISystemService to create the Category for.
    @param categoryIndex (optional) The Category number for the specified ISystemService to create.
    @return Category generated.
*/
EE_EGF_ENTRY efd::Category GetServicePublicCategory(
    efd::UInt32 serviceID,
    efd::UInt32 categoryIndex = -1);

/**
    Allocate a Category that is unique only in the context of this process.
    Subsequent calls to this method with the same ClassID by any process will produce
    a different result.
    @param serviceID The ClassID of the ISystemService to create the Category for.
    @return Category generated.
*/
EE_EGF_ENTRY efd::Category GetServiceProcessUniqueCategory(efd::UInt32 serviceID);

/**
    Get a private Category for the instance of the ISystemService local to this process.
    Only a single private Category can be generated in this way and is unique to the process
    that generates it.  Subsequent calls to this method by the same process will produce
    the same result.

    @param serviceID The ClassID of the ISystemService to create the Category for.
    @return Category generated.
*/
EE_EGF_ENTRY efd::Category GetServicePrivateCategory(efd::UInt32 serviceID);

/**
    Get a private Category for the instance of the ISystemService local to this process.
    Only a single private Category can be generated in this way and is unique to the process
    that generates it.  Subsequent calls to this method by the same process will produce
    the same result.

    @param serviceID The ClassID of the ISystemService to create the Category for.
    @param netID The NetID of the process you want the private category for.
    @return Category generated.
*/
EE_EGF_ENTRY efd::Category GetServicePrivateCategory(efd::ClassID serviceID, efd::UInt32 netID);

/**
    Allocate a globally unique Category.
    Subsequent calls to this method by any process will produce
    a different result.
    @return Category generated.
*/
EE_EGF_ENTRY efd::Category GetGloballyUniqueCategory();

/**
    Convert the string name of any ClassID, BaseID or ServiceID into the corresponding integer
    value.
    Note: Use of this function requires the EnumManager to be registered and initialized.
    @param strEnumName friendly name of enum to lookup id in
    @param strIDName String name of the id to convert.
    @return The integer value of the ID, 0 if not found.
*/
EE_EGF_ENTRY efd::UInt32 GetEnumValue(const char* strEnumName, const char* strIDName);

/**
    Checks to see if a particular model exists in the flat model manager.  If the model exists
    but is not in the cache yet, it is loaded into memory.

    @param strModelName The name of the model to check.
    @return True if the model exists.
*/
EE_EGF_ENTRY bool DoesModelExist(const char* strModelName);

/**
    Sends an event message that will launch the target behavior on the specified entity.
    A callback behavior may optionally be specified which will be invoked on the current entity
    after the target behavior finishes.  The target behavior can send arguments to the callback
    behavior by using the SendReply built-in.  Once the event has been sent the new behavior will
    be queued for execution and the current behavior will continue to execute.  The target entity
    can be any entity including the current entity.

    @param categoryID The Category on which the requested behavior should be sent
    @param strBehavior The behavior to execute for this event
    @param args [Optional] The ParameterList of arguments to be included in the event message, or
        NULL if there are no arguments.
    @param strCallback [Optional] The behavior to launch for any reply message.
    @param delay [Optional] Game Time in seconds to wait before actually executing the event.
    @return True if a valid Event was generated and sent.  A true result does not guarantee
        that the event will be successfully delivered or executed.
*/
EE_EGF_ENTRY bool SendEvent(
    efd::Category categoryID,
    const char* strBehavior,
    efd::ParameterList* args = NULL,   /* if NULL, no arguments to the called behavior */
    const char* strCallback = NULL, /* if NULL or empty, no callback */
    double delay = 0.0);


/*dev notes
    @fn efd::ParameterList* SendAndWaitForReply(egf::EntityID entityID, const char* strBehavior, efd::ParameterList* pStream = NULL, double delay = 0.0)

    Sends a blocking event message that will launch another behavior and waits for a response. The
    current behavior will be suspended until the called behavior runs to completion.  The
    called behavior can return data to the current behavior by using the SendReply built-in


    @b python:
    @verbatim
        import BehaviorAPI
        import ParameterList

        args = ParameterList.ParameterList()
        args.PutString("foo")
        strmResult = BehaviorAPI.SendAndWaitForReply(targetEntity, "BehaviorToInvoke", args, 0.0)
        if strmResult is not None:
            # read results from the stream
            value = strmResult.GetString()
        else
            # no results where returned

        # the last two methods are optional, if no arguments need to be passed you can use:
        strmResult = BehaviorAPI.SendAndWaitForReply(targetEntity, "BehaviorWithNoArgs")

        # Finally, you may pass None for the ParameterList to send a delayed event with no args:
        strmResult = BehaviorAPI.SendAndWaitForReply(targetEntity, "BehaviorWithNoArgs", None, 5.0)
    @endverbatim

    @b lua:
    @verbatim
        -- BehaviorAPI and ParameterList are automatically imported, no need to require them
        local args = ParameterList.ParameterList()
        args:PutString("foo")
        local strmResult = message.SendAndWaitForReply(targetEntity, "BehaviorToInvoke", args, 0.0)
        if strmResult != nil then
            -- read results from the stream
            value = strmResult:GetString()
        else
            -- no results where returned
        end

        -- the last two methods are optional, if no arguments need to be passed you can use:
        strmResult = message.SendAndWaitForReply(targetEntity, "BehaviorWithNoArgs")

        -- Finally, you may pass nil for the ParameterList to send a delayed event with no args:
        strmResult = message.SendAndWaitForReply(targetEntity, "BehaviorWithNoArgs", nil, 5.0)

    @endverbatim

    @param entityID The ID of the target entity
    @param strBehavior The name of the behavior to execute for this event
    @param pStream [Optional] Reference to the stream of arguments to be included in the event message.
    @param delay [Optional] Game Time in seconds to wait before actually executing the event.
    @return The ParameterList return by the recipient of this event via SendReply.
*/


/**
    Sends a reply event message back to the entity behavior that initiated the current behavior.
    The entity which initiated this behavior is either an entity that called SendAndWaitForReply
    or else an entity that passed a callback behavior to SendEvent.  In the SendAndWaitForReply
    case the ParameterList passed into SendReply is the stream that will be returned from the
    SendAndWaitForReply call in the originating behavior.  In the SendEvent with callback case
    the data stream passed to SendReply will be the argument stream to the callback behavior.

    @param pStream Pointer to the stream of arguments to be returned in the reply event.
*/
EE_EGF_ENTRY void SendReply(efd::ParameterList* pStream);



/**
    Execute a behavior immediately.  The behavior will be run to completion before this method
    returns. The entity on which this behavior is called must be local and the behavior that is
    being called must have the Immediate behavior trait.

    @param entityID The ID of the target entity
    @param strBehavior The name of the behavior to invoke.  Names of the form "Model:Method"
        are supported if you want to invoke a specific model's behavior.  Normally you should
        simply pass the Method name in order to invoke the most-derived implementation.
    @param pArgs A stream containing the arguments to the behavior.
    @return bool True if the behavior was invoked, which does not imply that the behavior
        succeeded.
*/
EE_EGF_ENTRY bool CallBehavior(
    egf::EntityID entityID,
    const efd::utf8string& strBehavior,
    efd::ParameterList* pArgs);

/**
    Sends a data stream of the specified message class type to the given category.
    Before calling this method you must first register a StreamMessage derived class in your
    C++ code by calling ServiceManager::RegisterFactoryMethod.  This is most commonly done
    using the MessageWrapper class.

    @see ServiceManager::RegisterFactoryMethod
    @see MessageWrapper
    @see RegisterMessageWrapperFactory

    @param catID The category ID to send the stream over the network on
    @param msgClassID The message type to tag the stream with
    @param pStream The ParameterList to send over the network
*/
EE_EGF_ENTRY void SendStream(
    efd::Category catID,
    efd::ClassID msgClassID,
    efd::ParameterList* pStream);

/**
    Sends a data stream of the specified message class type to the local message service.
    Before calling this method you must first register a StreamMessage derived class in your
    C++ code by calling ServiceManager::RegisterFactoryMethod.  This is most commonly done
    using the MessageWrapper class.

    @see ServiceManager::RegisterFactoryMethod
    @see MessageWrapper
    @see RegisterMessageWrapperFactory

    @param msgClassID The message type to tag the stream with
    @param strm The ParameterList to send over the network
*/
EE_EGF_ENTRY void SendStreamLocal(efd::ClassID msgClassID, efd::ParameterList* strm);


/**
    Places a message at the specified module name and log level into the framework log file.

    @param module Module id.
    @param i_level integer specifying the log level (0-3 are legal).
    @param i_pszMessage message string.
    @param i_echoToStdOut If true, echo the message to stdout.
*/
EE_EGF_ENTRY void FlexLogMessage(
    efd::UInt16 module,
    efd::UInt32 i_level,
    const char* i_pszMessage,
    bool i_echoToStdOut=false);

/**
    Places an error message at the specified module name and log level into the
    framework log file.

    @param module Module id.
    @param i_level integer specifying the log level (0-3 are legal)
    @param i_pszMessage error string
    @param i_echoToStdErr If true, echo the message to stdout.
*/
EE_EGF_ENTRY void FlexLogError(
    efd::UInt16 module,
    efd::UInt32 i_level,
    const char* i_pszMessage,
    bool i_echoToStdErr = false);

/**
    Places a "Python" message of the specified log level into the framework log file.

    @param i_level integer specifying the log level (0-3 are legal)
    @param i_pszMessage message string
    @param i_echoToStdOut If true, echo the message to stdout.
*/
EE_EGF_ENTRY void LogMessagePython(
    efd::UInt32 i_level,
    const char* i_pszMessage,
    bool i_echoToStdOut = false);

/**
    Places a "Python" error message of the specified log level into the framework log file.

    @param i_level integer specifying the log level (0-3 are legal)
    @param i_pszMessage error string
    @param i_echoToStdOut If true, echo the message to stdout.
*/
EE_EGF_ENTRY void LogErrorPython(
    efd::UInt32 i_level,
    const char* i_pszMessage,
    bool i_echoToStdOut = false);

/**
    Places a "Lua" message of the specified log level into the framework log file.

    @param i_level integer specifying the log level (0-3 are legal)
    @param i_pszMessage message string
    @param i_echoToStdOut If true, echo the message to stdout.
*/
EE_EGF_ENTRY void LogMessageLua(
    efd::UInt32 i_level,
    const char* i_pszMessage,
    bool i_echoToStdOut = false);

/**
    Places a "Lua" error message of the specified log level into the framework log file.

    @param i_level integer specifying the log level (0-3 are legal)
    @param i_pszMessage error string
    @param i_echoToStdOut If true, echo the message to stdout.
*/
EE_EGF_ENTRY void LogErrorLua(
    efd::UInt32 i_level,
    const char* i_pszMessage,
    bool i_echoToStdOut = false);

/**
    Output a debug message.  This only functions in debug builds and will output the message in a
    platform specific manner to best display the message in an attached C++ debugger.  Often the
    resulting message is only visible if such a debugger is attached to the running process at the
    time of the method call.

    @note This uses EE_OUTPUT_DEBUG_STRING internally, see that macro for further details on
    platform specific behavior.

    @param pMessage debug string
*/
EE_EGF_ENTRY void OutputDebugMessage(const char* pMessage);

/**
    Get the number of entries in an associative array property and return this value in count.
    This function returns PropertyResult_PropertyNotFound if the Entity doesn't exist,
    PropertyResult_PropertyNotAssociativeArray if the property is not an associative array,
    or PropertyResult_OK when successful.

    @param entityID The entity to look up.
    @param strPropertyName The name of the associative array property.
    @param count The number of entries in the property.
 */
EE_EGF_ENTRY efd::UInt32 GetPropertyCount(
    egf::EntityID entityID,
    const efd::utf8string& strPropertyName,
    efd::UInt32* count);

EE_EGF_ENTRY bool AddUpdateNotificationByEntity(
    egf::EntityID callbackEntityID,
    const efd::utf8string& strCallbackBehavior,
    egf::EntityID targetEntityID);

EE_EGF_ENTRY bool AddUpdateNotificationByModel(
    egf::EntityID callbackEntityID,
    const efd::utf8string& strCallbackBehavior,
    const efd::utf8string& modelName);

//@}

} // end namespace BehaviorAPI


#endif // !defined(EE_BEHAVIORAPI_H)
