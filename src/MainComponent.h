#pragma once

#include "BrowserComponent.h"
#include <juce_gui_extra/juce_gui_extra.h>

class MainComponent : public juce::Component {
public:
    MainComponent();

    void paint(juce::Graphics&) override;
    void resized() override;
private:
    BrowserComponent browserComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
