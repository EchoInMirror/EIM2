#pragma once

#include "BrowserApp.h"

void BrowserApp::OnContextInitialized()  {
    CEF_REQUIRE_UI_THREAD();

    CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();

    instance = new BrowserClient();
    CefWindowInfo window_info;
    CefBrowserSettings browser_settings;

#if defined(OS_WIN)
    CefRect rt(0, 0, 600, 400);
    window_info.SetAsChild((HWND) windowHandle, rt);
#endif

    CefBrowserHost::CreateBrowser(window_info, instance, "http://example.com/", browser_settings, nullptr, nullptr);
}
