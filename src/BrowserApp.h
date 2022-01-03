#pragma once

#include "BrowserClient.h"
#include <include/cef_app.h>
#include <include/wrapper/cef_helpers.h>

class BrowserApp : public CefApp, public CefBrowserProcessHandler, public CefRenderProcessHandler {
public:
    ~BrowserApp() {
        instance = nullptr;
    }

    CefRefPtr<BrowserClient> getInstance() { return instance; }

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }

    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override { return this; }

    void OnContextInitialized() override;

    virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
private:
    CefRefPtr<BrowserClient> instance = nullptr;

    IMPLEMENT_REFCOUNTING(BrowserApp);
};