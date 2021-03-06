#include "App.h"
#include <include/cef_app.h>

int main() {
    CefEnableHighDPISupport();
    CefMainArgs main_args;

    CefRefPtr<App> app(new App);

    return CefExecuteProcess(main_args, app.get(), nullptr);
}
