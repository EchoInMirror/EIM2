#pragma once

#include <include/cef_app.h>
#include <include/wrapper/cef_helpers.h>

class App : public CefApp, public CefRenderProcessHandler {
public:
    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override { return this; }
private:
    IMPLEMENT_REFCOUNTING(App);
};