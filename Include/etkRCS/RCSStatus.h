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
#ifndef EE_RCSSTATUS_H
#define EE_RCSSTATUS_H

#include "etkRCSLibType.h"

#include <efd/utf8string.h>

namespace etk
{
    /**
        This class is used to return the revision control system status of a file. The caller
        passes this object to the RCSProvider::Status() method to determine the current RCS
        state of a file.
    */
    class EE_RCS_ENTRY RCSStatus : public efd::MemObject
    {
    public:
        /// The current RCS state of a file
        enum RCSAction 
        {
            /// Indicates that file is not currently under revision control
            RCS_ACTION_UNKNOWN,
            /// File is under revision control
            RCS_ACTION_NORMAL,
            /// File is scheduled to be added to revision control
            RCS_ACTION_ADD,
            /// File has been marked for deletion
            RCS_ACTION_DELETE,
            /// File has been locally modified
            RCS_ACTION_EDIT,
            /// The file has been branched from another file under revision control
            RCS_ACTION_BRANCH,
            /// The file is schedule to be integrated into an existing file in revision control
            RCS_ACTION_INTEGRATE,
        };

        //@{
        /// Constructor and destructor. Do not inherit from this class.
        inline RCSStatus();
        inline ~RCSStatus();
        //@}

        /// Reset the status object. This method is invoked every time a status object is 
        /// constructed or passed to the RCSProvider::Status() method.
        inline void Clear();

        //@{
        /// The current RCS state of the file
        inline RCSAction GetAction() const;
        inline void SetAction(RCSAction action);
        //@}

        //@{
        /// The RCS user ID associated with the current state of the file. For example, the
        /// person performing the delete action.
        inline const efd::utf8string& GetActionOwner() const;
        inline void SetActionOwner(const char* pActionOwner);
        //@}

        //@{
        /// The absolute path to the local file. For example: 
        /// @verbatim c:\projects\foobar.txt @endverbatim
        inline const efd::utf8string& GetClientFilename() const;
        inline void SetClientFilename(const char* pClientFilename);
        //@}

        //@{
        /// The RCS path to the local file. For example, in P4: 
        /// @verbatim //depot/foobar.txt @endverbatim
        inline const efd::utf8string& GetDepotFilename() const;
        inline void SetDepotFilename(const char* pDepotFilename);
        //@}

        //@{
        /// The filename of the original file that the current file is being branched from.
        inline const efd::utf8string& GetBranchFromFilename() const;
        inline void SetBranchFromFilename(const char* pFromFilename);
        //@}

        //@{
        /// RCS lock status of the file
        inline bool IsLocked() const;
        inline void SetLocked(bool lock);
        //@}

        //@{
        /// Has the file already been deleted from the revision control system
        inline bool IsDeleted() const;
        inline void SetDeleted(bool deleted);
        //@}

        //@{
        /// Does the local file need to be merged with the most recently checked-in version
        /// of the file?
        inline bool IsResolveNeeded() const;
        inline void SetResolveNeeded(bool resolveNeeded);
        //@}

        //@{
        /// Has the file been replaced in revision control?
        inline bool IsReplaced() const;
        inline void SetReplaced(bool replaced);
        //@}

    protected:
        efd::utf8string m_depotFile; // e.g. //depot/Sandboxes/rtaylor/SCMTest/z.txt
        efd::utf8string m_clientFile; // e.g.  c:\EGT\Sandboxes\rtaylor\SCMTest\z.txt
        efd::utf8string m_branchFromFile;
        RCSAction m_action; // e.g. branch
        efd::utf8string m_actionOwner;
        efd::utf8string m_type; // e.g. text
        efd::utf8string m_resolved;
        bool m_locked;
        bool m_deleted;
        bool m_resolveNeeded;
        bool m_replaced;
    };

} // end namespace etk

#include "RCSStatus.inl"

#endif // EE_RCSSTATUS_H
