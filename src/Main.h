#pragma once

#include "MainComponent.h"
#include "BrowserApp.h"

class MainWindow : public juce::DocumentWindow {
public:
    explicit MainWindow(juce::String name);

    void closeButtonPressed() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};

class GuiAppApplication : public juce::JUCEApplication {
public:
    GuiAppApplication() {}

    const juce::String getApplicationName() override { return JUCE_APPLICATION_NAME_STRING; }
    const juce::String getApplicationVersion() override { return JUCE_APPLICATION_VERSION_STRING; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const juce::String& commandLine) override;

    void shutdown() override;

    void systemRequestedQuit() override;

    CefRefPtr<BrowserApp> getBrowserApp() { return app; }

private:
    CefRefPtr<BrowserApp> app;
    std::unique_ptr<MainWindow> mainWindow;
};
