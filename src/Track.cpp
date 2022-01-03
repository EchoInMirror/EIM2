#include "Track.h"
#include "ProcessorBase.h"

Track::Track(): juce::AudioProcessorGraph()  {
	auto input = addNode(std::make_unique<juce::AudioProcessorGraph::AudioGraphIOProcessor>(juce::AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode));
	begin = addNode(std::make_unique<ProcessorBase>());
	end = addNode(std::make_unique<juce::AudioProcessorGraph::AudioGraphIOProcessor>(juce::AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode));

	addConnection({ { input->nodeID, 0 }, { begin->nodeID, 0 } });
	addConnection({ { input->nodeID, 1 }, { begin->nodeID, 1 } });
	addConnection({ { begin->nodeID, 0 }, { end->nodeID, 0 } });
	addConnection({ { begin->nodeID, 1 }, { end->nodeID, 1 } });
	BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
		.withOutput("Output", juce::AudioChannelSet::stereo(), true);
}

void Track::setGenerator(std::unique_ptr<PluginWrapper> instance) {
	auto node = addNode(std::move(instance));
	addConnection({ { node->nodeID, 0 }, { end->nodeID, 0 } });
	addConnection({ { node->nodeID, 1 }, { end->nodeID, 1 } });
}
