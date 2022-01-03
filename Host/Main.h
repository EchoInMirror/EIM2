#pragma once

#include "MasterTrack.h"

class GuiAppApplication : public juce::JUCEApplication {
public:
    GuiAppApplication() {}

    const juce::String getApplicationName() override { return JUCE_APPLICATION_NAME_STRING; }
    const juce::String getApplicationVersion() override { return JUCE_APPLICATION_VERSION_STRING; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const juce::String& commandLine) override;

    void shutdown() override { masterTrack = nullptr; }
private:
    std::unique_ptr<MasterTrack> masterTrack;
};
