#pragma once

#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>
#include <include/base/cef_bind.h>
#include <include/cef_app.h>

class Client :
    public CefClient,
    public CefLifeSpanHandler,
    public CefLoadHandler {
public:
    Client() { }

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }

    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }

    // CefLifeSpanHandler methods.
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

    bool DoClose(CefRefPtr<CefBrowser> browser) override;

    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    void CloseAllBrowsers(bool forceClose);

    bool IsClosing() const {
        return closing;
    }

private:
    bool closing = false;

    typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
    BrowserList browserList;

    IMPLEMENT_REFCOUNTING(Client);
};