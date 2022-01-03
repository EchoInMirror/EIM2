#include "BrowserClient.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_callback.h"

void BrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    if (browserList.empty()) rootBrowser = browser;
    browserList.push_back(browser);
}

bool BrowserClient::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    if (browserList.size() == 1) closing = true;
    return false;
}

void BrowserClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    BrowserList::iterator bit = browserList.begin();
    for (; bit != browserList.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            browserList.erase(bit);
            break;
        }
    }

    if (browserList.empty()) {
        rootBrowser = nullptr;
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }
}

void BrowserClient::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) {
    CEF_REQUIRE_UI_THREAD();
    OutputDebugStringW(L"OnLoadEnd()\n");
    std::cout << "OnLoadEnd(" << httpStatusCode << ")" << std::endl;
    loaded = true;
}

void BrowserClient::OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward) {
    CEF_REQUIRE_UI_THREAD();
    OutputDebugStringW(isLoading ? L"OnLoadingStateChange: yes\n" : L"OnLoadingStateChange:  no\n");
}

void BrowserClient::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) {
    CEF_REQUIRE_UI_THREAD();
    OutputDebugStringW(L"OnLoadStart()\n");
}

void BrowserClient::CloseAllBrowsers(bool forceClose) {
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, base::BindOnce(&BrowserClient::CloseAllBrowsers, this, forceClose));
        return;
    }
    if (browserList.empty()) return;
    auto it = browserList.begin();
    for (; it != browserList.end(); ++it) (*it)->GetHost()->CloseBrowser(forceClose);
}
