#include "Main.h"
#include <include/cef_command_line.h>
#include <string>

#include "include/cef_command_line.h"
#include <include/cef_parser.h>

void GuiAppApplication::initialise(const juce::String& commandLine) {
    CefEnableHighDPISupport();
    juce::ignoreUnused(commandLine);
    masterTrack.reset(new MasterTrack());
    app = new BrowserApp();

    CefMainArgs args;
    CefSettings settings;
    settings.no_sandbox = true;
    settings.multi_threaded_message_loop = true;
    CefInitialize(args, settings, app.get(), nullptr);
}

void GuiAppApplication::shutdown() {
    CefShutdown();
    masterTrack = nullptr;
}

void GuiAppApplication::systemRequestedQuit() {
    if (app.get() && !app->getInstance()->IsClosing()) {
        app->getInstance()->CloseAllBrowsers(false);
        return;
    }
    app = nullptr;
}

//==============================================================================
// This macro generates the main() routine that launches the app.
// START_JUCE_APPLICATION(GuiAppApplication)
static juce::JUCEApplicationBase* juce_CreateApplication() { return new GuiAppApplication(); }
extern "C" JUCE_MAIN_FUNCTION {
    CefMainArgs args;
    int res = CefExecuteProcess(args, nullptr, nullptr);
    if (res >= 0) return res;

    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
    return juce::JUCEApplicationBase::main(JUCE_MAIN_FUNCTION_ARGS);
}
