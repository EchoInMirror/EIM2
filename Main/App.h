#pragma once

#include "Client.h"
#include <include/cef_app.h>
#include <include/wrapper/cef_helpers.h>

class App : public CefApp, public CefBrowserProcessHandler {
public:
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }

    void OnContextInitialized() override;
private:
    CefRefPtr<Client> instance = nullptr;

    IMPLEMENT_REFCOUNTING(App);
};