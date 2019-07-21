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
#ifndef EE_ASSETAPPLICATIONINFOMSG_H
#define EE_ASSETAPPLICATIONINFOMSG_H

#include <efd/IMessage.h>
#include <efd/UniversalTypes.h>

namespace efd
{
    /**
     Message class used for AssetApplicationInfoMsg messages. This message is intended to be sent
     by an application after receiving a NetServiceConnectionEstablished message. The message
     allows the application to send information about itself to an asset controller's channel
     manager. The asset controller can use this information to offer additional information
     about connections or connection loss to clients.
    */
    class EE_EFD_ENTRY AssetApplicationInfoMsg : public IMessage
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(AssetApplicationInfoMsg, kCLASSID_AssetApplicationInfoMsg, IMessage);
        /// @endcond

    public:

        /**
        Embedded convenience class used for storing and retrieving information contained within the
        AssetApplicationInfoMsg class.
        */
        class AppInfo
        {
        public:
            AppInfo()
            {
                m_PrivateCategory = 0;
                m_Port = 0;
                m_bConnected = false;
                m_strAppName = "UNKNOWN";
                m_strAppType = "UNKNOWN";
                m_strExtraInfo = "";
            }

            UInt64 m_PrivateCategory;
            int m_Port;
            bool m_bConnected;
            utf8string m_strAppName;
            utf8string m_strAppType;
            utf8string m_strExtraInfo;
        };

        /// Constructor
        AssetApplicationInfoMsg();
        AssetApplicationInfoMsg(const AppInfo& ci);

        // Overridden virtual functions inherit base documentation and thus not documented here.
        virtual void Serialize(efd::Archive& ar);

        /** Set the private category which will be used by the asset controller to inform the
        application of new connections or connection lost. The application may generate a private
        category like the following:

            AssetControllerPrivateCategory = efd::Category(efd::UniversalID::ECU_Any,
                pNetService->GetNetID(), efd::kBASEID_AssetController).GetValue();
        */
        void SetPrivateCategory(UInt64 category);

        /** Get the privated category which is set by the application. */
        UInt64 GetPrivateCategory() const;

        /** Set the application port. This value should be the local port number of the
        application. This port value is used by the asset controller to look up application
        information when a connection has been closed.
        */
        void SetAppPort(int port);

        /** Get the application port. This value represents the applications local port number.
        */
        int GetAppPort() const;

        /** Set the connected status for the application. This value should not be set by any
        application other than the asset controller.
        */
        void SetConnected(bool bConnected);

        /** Get the connected status for the application. */
        bool GetConnected() const;

        /** Set the name of the application. The default value is "UNKNOWN".
        */
        void SetApplicationName(const utf8string& appName);

        /** Get the name of the application. */
        const utf8string& GetApplicationName() const;

        /** Set the application type. The application type may be used to distinguish one type of
        application from another. For example, a previewer could be distinguished from a game or
        a tool. The default value is "UNKNOWN".
        */
        void SetApplicationType(const utf8string& appType);

        /** Get the application type.
        */
        const utf8string& GetApplicationType() const;

        /** Set any additional extra string data that may be helpful to convey. For example,
        passing along data like "SupportsRapidIteration=TRUE" might be useful to some recipients
        of the message.
        */
        void SetExtraInfo(const utf8string& extraInfo);

        /** Get the extra string information associated with the application.
        */
        const utf8string& GetExtraInfo() const;

        /** Set the application info using the embedded convenience class.
        */
        void SetApplicationInfo(const AppInfo& ai);

        /** Get a copy of the application info that is stored in the embedded convenience class.
        */
        AppInfo GetApplicationInfo() const;

    protected:
        AppInfo m_info;
    };

    typedef SmartPointer<AssetApplicationInfoMsg> AssetApplicationInfoMsgPtr;

} // end namespace efd

#endif // EE_ASSETAPPLICATIONINFOMSG_H

