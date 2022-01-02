#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>
#include <include/base/cef_bind.h>
#include <include/cef_app.h>

class BrowserClient :
    public CefClient,
    public CefDisplayHandler,
    public CefLifeSpanHandler,
    public CefLoadHandler {
public:
    BrowserClient() { }

    BrowserClient* BrowserClient::GetInstance() { return this; }

    CefRefPtr<CefBrowser> GetRootBrowser() { return rootBrowser; }

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }

    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }

    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }

    // CefLifeSpanHandler methods.
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

    bool DoClose(CefRefPtr<CefBrowser> browser) override;

    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override;

    void OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward);

    void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);

    void CloseAllBrowsers(bool forceClose);

    bool IsClosing() const {
        return closing;
    }

    bool IsLoaded() const {
        return loaded;
    }

private:
    bool closing = false;
    bool loaded = false;

    typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
    BrowserList browserList;
    CefRefPtr<CefBrowser> rootBrowser;

    IMPLEMENT_REFCOUNTING(BrowserClient);
};