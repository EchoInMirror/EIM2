#pragma once

#include "PluginWrapper.h"

class Track: public juce::AudioProcessorGraph {
public:
    Track();

    void setGenerator(std::unique_ptr<PluginWrapper>);
private:
    juce::AudioProcessorGraph::Node::Ptr begin, end;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Track)
};
