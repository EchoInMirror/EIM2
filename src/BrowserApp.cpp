#pragma once

#include "BrowserApp.h"

void BrowserApp::OnContextInitialized()  {
    CEF_REQUIRE_UI_THREAD();

    CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();

    instance = new BrowserClient();
    CefWindowInfo window_info;
    CefBrowserSettings browser_settings;

    window_info.SetAsPopup(nullptr, "Echo In Mirror");

    CefBrowserHost::CreateBrowser(window_info, instance, "file:///index.html", browser_settings, nullptr, nullptr);
}

class CSimpleV8Handler : public CefV8Handler {
public:
    bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,
        CefRefPtr<CefV8Value>& retval, CefString& exception) override {
        DBG("88888888888888");
        if (juce::JUCEApplication::getInstance()) DBG("23333");
        return true;
    }

private:
    IMPLEMENT_REFCOUNTING(CSimpleV8Handler);
};

void BrowserApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
    CefRefPtr<CefV8Value> object = context->GetGlobal();

    // Create a new V8 string value. See the "Basic JS Types" section below.
    CefRefPtr<CefV8Value> str = CefV8Value::CreateString("My Value!");

    // Add the string to the window object as "window.myval". See the "JS Objects" section below.
    object->SetValue("myval", str, V8_PROPERTY_ATTRIBUTE_NONE);
}
