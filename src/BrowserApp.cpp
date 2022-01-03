#pragma once

#include "BrowserApp.h"

void BrowserApp::OnContextInitialized()  {
    CEF_REQUIRE_UI_THREAD();

    CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();

    instance = new BrowserClient();
    CefWindowInfo window_info;
    CefBrowserSettings browser_settings;

    window_info.SetAsPopup(nullptr, "Echo In Mirror");

    CefBrowserHost::CreateBrowser(window_info, instance, "http://127.0.0.1/", browser_settings, nullptr, nullptr);
}
