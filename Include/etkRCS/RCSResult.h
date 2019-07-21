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
#ifndef EE_RCSRESULT_H
#define EE_RCSRESULT_H

#include "etkRCSLibType.h"

#include <efd/utf8string.h>

namespace etk
{ 
    /**
        This class is used to return status and error information from RCS methods. The caller
        passes a RCSResult object into the method, which is populated by the based on the results
        of the RCS operation.
    */
    class EE_RCS_ENTRY RCSResult : public efd::MemObject
    {
    public:
        /// The reason an RCS operation failed
        enum Reason
        {
            /// The operation succeeded. No error occurred
            RCS_NO_ERROR = 0,
            /// A serious error has occurred that cannot be retried by RCSFeedback::HandleError()
            /// method.
            RCS_UNRECOVERABLE_ERROR,
            /// A RCS operation has failed, but a retry is possible is a custom RCSFeedback object
            /// has been assigned to the provider
            RCS_ERROR,
            /// The file is not in the depot or repository
            RCS_NOT_UNDER_REVISION_CONTROL,
            /// The user has chosen to ignore the RCS operation.
            RCS_USER_IGNORE,
            /// The user has cancelled the RCS operation by invoking RCSProvider::Cancel()
            RCS_USER_CANCEL
        };

        //@{
        /// Constructor and destructor
        RCSResult();
        virtual ~RCSResult();
        //@}

        /// Returns true if the RCS operation succeeded
        inline bool Succeeded();

        /// Returns true if the RCS operation failed
        inline bool Failed();

        /// Returns true if the RCSProvider::Cancel() method was used to abort the RCS operation
        inline bool Cancelled();

        /// Set result object to failed or succeeded based on the reason passed-in by the caller.
        /// @param reason The reason the result object represents success or failure
        inline void SetFailed(Reason reason);

        /// Set result object to indicate success
        inline void SetSucceeded();

        /// Returns the reason for the result's current state (success or fail)
        inline Reason GetReason();

        /** Returns a string that indicates the high-level RCS action that was being attempting. For
            example: "add C:\foo\bar.txt". This string is included in the GetDisplayMessage() 
            method.
        */
        inline efd::utf8string& GetAction();

        /** Set the high-level action that is being attempted by the method. For example: "delete 
            old.txt".
            @param pAction User-displayable message
        */
        inline void SetAction(const char* pAction);

        /** Sets flag indicating that the RCS command should be hidden from the user by 
            GetDisplayMessage(). This is rarely used when the RCS command fails, but may confuse
            the user since it may not map directly to the high-level action being performed or in
            cases where the command succeeds (like a RCSProvider::Status() method), but the status
            indicates that something failed.
            @param hideCommand True indicates that the command should not be included in the
                message returned by GetDisplayMessage().
        */
        inline void SetHideCommand(bool hideCommand);

        /// Returns a RCS command line approximation for the for the operation that
        /// was being attempted. This string  is included in the GetDisplayMessage() method.
        inline efd::utf8string& GetCommand();

        /** Assign a RCS command line equivalent for the attempted action so that the user can
            see what was attempted and potentially take corrective action. This is especially
            useful when the message is displayed through the RCSFeedback::HandleError() method.
            @param pCommand The RCS command line for the attempted operation
        */
        inline void SetCommand(const char* pCommand);

        /// Returns the string message returned by the revision control system for the most
        /// recent operation.
        inline efd::utf8string& GetResponse();

        /** Store the message returned by the revision control system in the result object. This
            message is used to construct the message returned by GetDisplayMessage().
            @param pResponse The user-displayable message returned by the RCS
        */
        inline void SetResponseMessage(const char* pResponse);

        //@{
        /// Save a message that may help the user correct the problem. This text is used to 
        /// construct the message returned by GetDisplayMessage().            
        inline void SetHelpMessage(const char* pHelp);
        inline efd::utf8string& GetHelpMessage();
        //@}

        /** This method combines the action, command, and response associated with a RCS operation
            into a single user-displayable string. The command portion will be excluded if the
            the SetHideCommand() method has been called to set hide to true.
        */
        efd::utf8string GetDisplayMessage();

    protected:
        Reason m_reason;
        efd::utf8string m_action;
        efd::utf8string m_command;
        efd::utf8string m_response;
        efd::utf8string m_help;
        bool m_failed;
        bool m_hideCommand;
    };

} // end namespace etk

#include "RCSResult.inl"

#endif // EE_RCSRESULT_H