#include "Client.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_callback.h"

void Client::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    browserList.push_back(browser);
}

bool Client::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    if (browserList.size() == 1) closing = true;
    return false;
}

void Client::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    BrowserList::iterator bit = browserList.begin();
    for (; bit != browserList.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            browserList.erase(bit);
            break;
        }
    }

    if (browserList.empty()) CefQuitMessageLoop();
}

void Client::CloseAllBrowsers(bool forceClose) {
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, base::BindOnce(&Client::CloseAllBrowsers, this, forceClose));
        return;
    }
    if (browserList.empty()) return;
    auto it = browserList.begin();
    for (; it != browserList.end(); ++it) (*it)->GetHost()->CloseBrowser(forceClose);
}
