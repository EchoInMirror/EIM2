#pragma once

#include "App.h"

void App::OnContextInitialized()  {
    CEF_REQUIRE_UI_THREAD();

    CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();

    instance = new Client();
    CefWindowInfo window_info;
    CefBrowserSettings browser_settings;

    window_info.SetAsPopup(nullptr, "Echo In Mirror");

    CefBrowserHost::CreateBrowser(window_info, instance, "file:///index.html", browser_settings, nullptr, nullptr);
}
