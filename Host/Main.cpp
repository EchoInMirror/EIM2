#include "Main.h"
#include <string>

void GuiAppApplication::initialise(const juce::String& commandLine) {
    juce::ignoreUnused(commandLine);
    masterTrack.reset(new MasterTrack());
}

START_JUCE_APPLICATION(GuiAppApplication)
