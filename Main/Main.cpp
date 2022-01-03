#include <include/cef_command_line.h>
#include <include/cef_parser.h>
#include <include/wrapper/cef_helpers.h>
#include <include/cef_app.h>
#include "App.h"

int main(int argc, char* argv[]) {
    CefMainArgs mainArgs;
    CefRefPtr<App> app(new App);
    CefSettings settings;
    settings.no_sandbox = true;
    CefString(&settings.browser_subprocess_path).FromASCII("EIMRender.exe");
    CefInitialize(mainArgs, settings, app.get(), nullptr);
    CefRunMessageLoop();
    CefShutdown();
    return 0;
}
