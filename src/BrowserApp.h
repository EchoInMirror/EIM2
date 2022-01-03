#pragma once

#include <include/cef_app.h>
#include "BrowserClient.h"
#include <include/wrapper/cef_helpers.h>

class BrowserApp : public CefApp, public CefBrowserProcessHandler {
public:
    ~BrowserApp() {
        instance = nullptr;
    }

    CefRefPtr<BrowserClient> getInstance() { return instance; }

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }

    void OnContextInitialized() override;

private:
    CefRefPtr<BrowserClient> instance = nullptr;

    IMPLEMENT_REFCOUNTING(BrowserApp);
};