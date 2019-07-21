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
#ifndef EE_RCSPROVIDER_H
#define EE_RCSPROVIDER_H

#include "etkRCSLibType.h"
#include <etkRCS/RCSStatus.h>
#include <etkRCS/RCSFeedback.h>
#include <etkRCS/RCSResult.h>

#include <efd/utf8string.h>

namespace etk
{ 
    /**
        This class represents a generic interface to a revision control system. Objects derived
        from this class should be used to wrap specific revision control systems like Perforce or 
        Subversion. This object is intended to be implemented in a plug-in DLL which is loaded 
        by the RCSFactory singleton.        
        <br>
        Ideally, a RCS-specific implementation of this class only overrides the abstract connection
        and Simple*() methods. The public RCS operation and Robust*() methods contain logic that 
        should apply to all revision control systems, but they can be overridden, if necessary.
        <br> 
        The top-level RCS methods (Add(), Edit(), etc) add retry logic to the RCS provider. The 
        Robust*() methods (RobustAdd(), RobustEdit(), etc) add fallback logic. For example, if the
        caller attempts to Edit a file that is not in revision control, it will be Added
        automatically. The Simple*() methods are straight pass-throughs to the underlying RCS.
    */
    class EE_RCS_ENTRY RCSProvider : public efd::MemObject
    {
        EE_DECLARE_ABSTRACT_REFCOUNT;
    
    public:
        //@{
        /// Constructor and destructor
        RCSProvider();
        virtual ~RCSProvider();
        //@}

        /// The functionality supported by the RCS provider
        enum RCSCapabilites
        {
            /// A call to RCSProvider::Edit() is required before modifying a file. For example:
            /// Perforce
            RCS_CAPS_EDIT_REQUIRED,
            /// RCS operations can be cancelled by calling RCSProvider::Cancel() 
            RCS_CAPS_CANCEL
        };

        /// Return true if the provider supports a specific feature
        /// @param capability The feature to query
        virtual bool IsSupported(RCSCapabilites capability) const = 0;

        /// Initializes the provider object, but does not actually connect to the revision control
        /// system (call Connect() to connect to RCS).
        virtual bool Initialize(RCSResult* pResult = NULL) = 0;

        /// Disconnect (if connected) and release resources used by the provider object
        virtual void Shutdown() = 0;

        /** Initialize a connection to the revision control system
            @param username The user ID associated with the RCS
            @param password The password associated with the user ID
            @param host The server to connect to
            @param pResult Optional object used to return detailed status information
            @return True if a connection was established with the server
        */
        virtual bool Connect(
            const efd::utf8string& username, 
            const efd::utf8string& password, 
            const efd::utf8string& host,
            RCSResult* pResult = NULL) = 0;

        /** Disconnect from the revision control system
            @param pResult Optional object used to return detailed status information
            @return True if a connection was cleanly shutdown
        */
        virtual bool Disconnect(RCSResult* pResult = NULL) = 0;

        /// Returns true if the provider object is currently connected to a RCS server
        virtual bool IsConnected(RCSResult* pResult = NULL) = 0;

        //@{
        /// The feedback object is used to display status and error messages to the user. 
        /// In addition, this object can be used to ask the user what to do in case of an error.
        inline void SetFeedback(RCSFeedback* pFeedback);
        inline const RCSFeedback* GetFeedback() const;
        //@}

        //@{
        /// All RCS operations will be associated with the changelist name specified by these
        /// methods.
        inline void SetChangelist(const efd::utf8string& changelistName);
        inline const efd::utf8string& GetChangelist() const;
        //@}

        /// Abort the current RCS operation (check IsSupported() to verify this functionality
        /// is available in the current provider)
        inline void Cancel();

        /// Is the provider waiting to cancel the next operation?
        inline bool IsCancelled();

        /// This method is called after the RCS operation has been successfully cancelled to reset
        /// the state of the provider.
        inline void ResetCancel();

        /** Add a file to the revision control system's depot or repository.
            @param fileName File location on the local filesystem. For example: 
                @verbatim c:\project\foo.bar @endverbatim
            @param pResult Optional object used to return detailed status information
            @return True if the file is scheduled for add in the RCS changelist.
        */
        virtual bool Add(const efd::utf8string& fileName, RCSResult* pResult = NULL);

        /** Edit a file that is already under revision control.
            @param fileName File location on the local filesystem. For example: 
                @verbatim c:\project\foo.bar @endverbatim
            @param pResult Optional object used to return detailed status information
            @return True if the file is marked for edit in the RCS changelist.
        */
        virtual bool Edit(const efd::utf8string& fileName, RCSResult* pResult = NULL);

        /** Delete a file that is already under revision control.
            @param fileName File location on the local filesystem. For example: 
                @verbatim c:\project\foo.bar @endverbatim
            @param pResult Optional object used to return detailed status information
            @return True if the file is scheduled for delete in the RCS changelist.
        */
        virtual bool Delete(const efd::utf8string& fileName, RCSResult* pResult = NULL);

        /** Delete a file that is already under revision control.
            @param fromFileName File location on the local filesystem of the original file. 
                For example: @verbatim c:\project\foo.bar @endverbatim
            @param toFileName File location on the local filesystem of the new filename. 
                For example: @verbatim c:\project\newfoo.bar @endverbatim
            @param pResult Optional object used to return detailed status information
            @return True if the file is scheduled for rename (usually delete "from" and branch "to"
                file) in the RCS changelist.
        */
        virtual bool Rename(
            const efd::utf8string& fromFileName, 
            const efd::utf8string& toFileName,
            RCSResult* pResult = NULL);

        /** Revert a RCS operation of a file on the local filesystem
            @param fileName File location on the local filesystem. For example: 
                @verbatim c:\project\foo.bar @endverbatim
            @param pResult Optional object used to return detailed status information
            @return True if the file is reverted to match the latest version is revision control
        */
        virtual bool Revert(const efd::utf8string& fileName, RCSResult* pResult = NULL);

        /** Query the RCS state of a file that is under revision control.
            @param fileName File location on the local filesystem. For example: 
                @verbatim c:\project\foo.bar @endverbatim
            @param status Object used to return the RCS status information for the file
            @param pResult Optional object used to return detailed status information
            @param bReportErrors if true, report errors back to the calling application.
            @return True if the file is successfully queried
        */
        virtual bool Status(
            const efd::utf8string& fileName, 
            RCSStatus& status,
            RCSResult* pResult = NULL,
            bool bReportErrors = true);

        /** Display a message using the RCSFeedback object that was associated with the provider
            using the SetFeedback() method.
            @param severity The type of message being issued by the RCS provider 
            @param pFormat Printf-style format string
        */
        inline void LogMessage(RCSFeedback::MessageSeverity severity, const char* pFormat, ...);

    protected:
        virtual bool RobustAdd(const efd::utf8string& fileName, RCSResult& result);
        virtual bool RobustEdit(const efd::utf8string& fileName, RCSResult& result);
        virtual bool RobustDelete(const efd::utf8string& fileName, RCSResult& result);
        virtual bool RobustRename(
            const efd::utf8string& fromFileName, 
            const efd::utf8string& toFileName,
             RCSResult& result);
        virtual bool RobustRevert(
            const efd::utf8string& fileName,
            bool modifyFile,
            RCSResult& result);
        virtual bool RobustStatus(
            const efd::utf8string& fileName, 
            RCSStatus& status,
            RCSResult& result);

        virtual bool SimpleAdd(const efd::utf8string& fileName, RCSResult& result) = 0;
        virtual bool SimpleEdit(const efd::utf8string& fileName, RCSResult& result) = 0;
        virtual bool SimpleDelete(const efd::utf8string& fileName, RCSResult& result) = 0;
        virtual bool SimpleRename(
            const efd::utf8string& fromFileName, 
            const efd::utf8string& toFileName,
             RCSResult& result) = 0;
        virtual bool SimpleRevert(
            const efd::utf8string& fileName,
            bool modifyFile,
            RCSResult& result) = 0;
        virtual bool SimpleStatus(
            const efd::utf8string& fileName, 
            RCSStatus& status,
             RCSResult& result) = 0;

        inline RCSFeedback::ErrorAction HandleError(RCSResult& result);

        bool m_cancel;
        RCSFeedback* m_pFeedback;
        efd::utf8string m_changelistName;
    };

} // end namespace etk

#include "RCSProvider.inl"

#endif // EE_RCSPROVIDER_H
