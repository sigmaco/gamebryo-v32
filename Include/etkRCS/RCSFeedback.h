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
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#pragma once
#ifndef EE_RCSFEEDBACK_H
#define EE_RCSFEEDBACK_H

#include "etkRCSLibType.h"

#include <efd/utf8string.h>

namespace etk
{ 
    class RCSResult;

    /**
        This class allows a provider object to report errors back to the calling application. 
        This includes display status/progress messages and an error handler that enables the 
        user to interactively abort, retry, or ignore an error that results from a failed
        RCS operation.
        <br>
        To add feedback to a provider, inherit from RCSFeedback and use RCSProvider::SetFeedback()
        to associate your feedback object to the provider object.
    */
    class EE_RCS_ENTRY RCSFeedback
    {
    public:
        /// Destructor
        virtual ~RCSFeedback();

        /// Actions that can be taken by a provider in response to an RCS operation error
        enum ErrorAction
        {
            /// Stop attempting the RCS operation
            RCS_ERR_ACTION_ABORT = 0,
            /// Try the RCS operation again
            RCS_ERR_ACTION_RETRY,
            /// Ignore the current RCS error and continue
            RCS_ERR_ACTION_IGNORE
        };

        /// The importance of a status message being logged by a RCS provider
        enum MessageSeverity
        {
            /// Informational and progress message
            RCS_INFO = 0,
            /// The RCS operation succeeded but the user may want to review the results
            RCS_WARNING,
            /// Indicates RCS operation failed
            RCS_ERROR
        };

        /** This method is invoked when a provider encounters an error while attempting a RCS
            operation. For example, the caller may implement this method to display a 
            message box with retry and abort options. 
            @param result Object passed-in by the caller to return status/error information for
                displaying to the user.
            @return The value returned by this method is used to determine how the error will be
                handled. The return value should be specified by the user through UI.
        */
        virtual ErrorAction HandleError(RCSResult& result) = 0;

        /** This method is called by the provider object to display progress and status messages.
            The caller typically implements this method to display messages in an output window
            or log file.
            @param severity The type of message being issued by the RCS provider 
            @param message Caller supplied-object used to return the actual message
        */
        virtual void LogMessage(MessageSeverity severity, const efd::utf8string& message) = 0;

        /** Printf-style convenience method that formats a message with 0 or more arguments and
            then calls LogMessage() to display the message.
            @param severity The type of message being issued by the RCS provider 
            @param pFormat Printf-style format string
        */
        void LogMessage(RCSFeedback::MessageSeverity severity, const char* pFormat, ...);

        /** Varargs convenience method that can be used to by other classes to implement 
            printf-style convenience methods. This method calls LogMessage() once the message has
            been formatted.
            @param severity The type of message being issued by the RCS provider 
            @param pFormat Printf-style format string
            @param args Variable argument list
        */
        void VLogMessage(RCSFeedback::MessageSeverity severity, const char* pFormat, va_list args);
    };

} // end namespace etk

#endif // EE_RCSFEEDBACK_H
