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
#ifndef EE_Win32PlatformServiceService_h
#define EE_Win32PlatformServiceService_h

#include <efd/OS.h>

#include <efd/ISystemService.h>
#include <efd/ServiceManager.h>


namespace efd
{
class EE_EFD_ENTRY Win32PlatformService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(Win32PlatformService, efd::kCLASSID_Win32PlatformService, ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

protected:
    /// Destructor
    virtual ~Win32PlatformService();

public:
    /// Constructor
    Win32PlatformService(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
        efd::SInt32 nCmdShow = SW_SHOWNORMAL);

    /// @name Configuration options
    /// These functions are only useful to call prior to PreInit.  These values are used
    /// during the default RegisterClass/InitInstance functions.
    //@{

    /// Sets the initial window title from a string. The window title should be set shortly
    /// after creating the platform service and before ticking services.
    void SetWindowTitle(const efd::utf8string& strTitle);
    /// Sets the initial window title from a resource string. The window title should be set
    /// shortly after creating the platform service and before ticking services.
    void SetWindowTitle(efd::UInt32 titleResourceID);

    /// Sets the window class to use when creating a window. The window class should be set
    /// shortly after creating the platform service and before ticking services.
    void SetWindowClass(const efd::utf8string& strClass);
    /// Sets the window class to use when creating a window from a resource string. The window class
    /// should be set shortly after creating the platform service and before ticking services.
    void SetWindowClass(efd::UInt32 classResourceID);

    /// Sets the large (and optionally small) icons for the created window using resource IDs. If
    /// the icon is not set the system will use a default icon. The window icon, if set, should be
    /// set shortly after creating the platform service and before ticking services.
    void SetWindowIcon(efd::UInt32 largeIconResourceID, efd::UInt32 smallIconResourceID = 0);

    /// Sets the initial window width. This can be called as soon as the service is created. If
    /// called before the service is initialized this will set the initial width of the window. If
    /// called after that point this will adjust the window size on the next tick of this service.
    void SetWindowWidth(efd::UInt32 width);

    /// Sets the initial window height. This can be called as soon as the service is allocated. If
    /// called before the service is initialized this will set the initial height of the window. If
    /// called after that point this will adjust the window size on the next tick of this service.
    void SetWindowHeight(efd::UInt32 height);

    /// Sets the window left position. This can be called as soon as the service is allocated. If
    /// called before the service is initialized this will set the initial position of the window.
    /// If called after that point this will adjust the window position on the next tick of this
    /// service.
    void SetWindowLeft(efd::UInt32 left);

    // Sets the window top position. This can be called as soon as the service is allocated. If
    /// called before the service is initialized this will set the initial position of the window.
    /// If called after that point this will adjust the window position on the next tick of this
    /// service.
    void SetWindowTop(efd::UInt32 top);

    /// Sets the message processing function for the main window. The provided procedure will
    /// replace the default procedure. The window procedure, if set, must be set shortly after
    /// creating the platform service and before initializing services. Calling this method after
    /// the service has completed OnPreInit will have no effect.
    void SetWndProc(WNDPROC pFunc);
    //@}

    /// @name Window accessor functions
    //@{
    /// Return the HINSTANCE for this window.
    efd::InstanceRef GetInstanceRef() const;

    /// Returns the HWND for this window.
    efd::WindowRef GetWindowRef() const;
    //@}

protected:
    /// Creates the window.
    virtual BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

    /// Registers the window class to be created in InitInstance.
    virtual ATOM RegisterClass(HINSTANCE hInstance);

    /// Sets up window instance.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /// Default message pump.  Quits on quit message.
    virtual efd::AsyncResult OnTick();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual const char* GetDisplayName() const;

    /// Default WndProc function.  Quits on escape button.
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    efd::InstanceRef m_hInstance;
    efd::InstanceRef m_hPrevInstance;
    LPTSTR m_lpCmdLine;
    efd::SInt32 m_nCmdShow;
    efd::WindowRef m_hWnd;

    efd::utf8string m_strWindowTitle;
    efd::utf8string m_strWindowClass;

    efd::UInt32 m_idWindowMenu;
    efd::UInt32 m_idLargeIcon;
    efd::UInt32 m_idSmallIcon;

    efd::UInt32 m_windowWidth;
    efd::UInt32 m_windowHeight;
    efd::UInt32 m_windowLeft;
    efd::UInt32 m_windowTop;
    bool m_isDirty;

    efd::UInt32 m_maxMessagesPerTick;

    WNDPROC m_pWndProc;
};

typedef efd::SmartPointer<Win32PlatformService> Win32PlatformServicePtr;

} // end namespace efd

#endif // EE_Win32PlatformServiceService_h
