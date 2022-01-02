#include "Main.h"
#include <include/cef_command_line.h>
#include <string>

#include "include/cef_command_line.h"
#include <include/cef_parser.h>

MainWindow::MainWindow(juce::String name) : DocumentWindow(name,
    juce::Desktop::getInstance().getDefaultLookAndFeel()
    .findColour(ResizableWindow::backgroundColourId),
    DocumentWindow::allButtons) {
    setUsingNativeTitleBar(true);
    setContentOwned(new MainComponent(), true);

    setResizable(true, true);
    centreWithSize(getWidth(), getHeight());

    setVisible(true);
}

void MainWindow::closeButtonPressed() { juce::JUCEApplication::getInstance()->systemRequestedQuit(); }

void GuiAppApplication::initialise(const juce::String& commandLine) {
    CefEnableHighDPISupport();
    juce::ignoreUnused(commandLine);
    mainWindow.reset(new MainWindow(getApplicationName()));
    app = new BrowserApp(mainWindow.get()->getContentComponent()->getWindowHandle());

    CefMainArgs args;
    CefSettings settings;
    settings.no_sandbox = true;
    settings.multi_threaded_message_loop = true;
    CefInitialize(args, settings, app.get(), nullptr);
}

void GuiAppApplication::shutdown() {
    CefShutdown();
    mainWindow = nullptr;
}

void GuiAppApplication::systemRequestedQuit() {
    if (app.get() && !app.get()->getInstance()->IsClosing()) {
        app.get()->getInstance().get()->CloseAllBrowsers(false);
        return;
    }
    app = nullptr;
    mainWindow.get()->removeFromDesktop();
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
