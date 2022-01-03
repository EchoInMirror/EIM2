#include "PluginWrapper.h"

PluginWrapper::PluginWrapper(std::unique_ptr<juce::AudioPluginInstance> instance) : juce::DocumentWindow(
	instance->getName(), juce::Colours::lightgrey, juce::DocumentWindow::closeButton), SynchronizedAudioProcessorGraph() {
	setChannelLayoutOfBus(true, 0, juce::AudioChannelSet::canonicalChannelSet(2));
	setChannelLayoutOfBus(false, 0, juce::AudioChannelSet::canonicalChannelSet(2));
	instance->enableAllBuses();
	auto inputChannels = instance->getTotalNumInputChannels();
	auto outputChannels = instance->getTotalNumOutputChannels();
	if (inputChannels) instance->setChannelLayoutOfBus(true, 0, juce::AudioChannelSet::canonicalChannelSet(inputChannels));
	if (outputChannels) instance->setChannelLayoutOfBus(false, 0, juce::AudioChannelSet::canonicalChannelSet(outputChannels));
	setContentOwned(instance->createEditorIfNeeded(), true);
	auto pluginNode = addNode(std::move(instance));
	auto outputNode = addNode(std::make_unique<juce::AudioProcessorGraph::AudioGraphIOProcessor>(juce::AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode));
	addConnection({ { pluginNode->nodeID, 0 }, { outputNode->nodeID, 0 } });
	addConnection({ { pluginNode->nodeID, 1 }, { outputNode->nodeID, 1 } });
	
	/*
	juce::AudioBuffer<double> buffer(outputChannels, 1024);
	auto midi = new juce::MidiBuffer();
	midi->addEvent(juce::MidiMessage::noteOn(1, 80, (juce::uint8)120), 1);
	midi->addEvent(juce::MidiMessage::noteOff(1, 80, (juce::uint8)120), 1);
	graph.processBlock(buffer, *midi);
	*/

	setVisible(true);
}

int PluginWrapper::getDesktopWindowStyleFlags() const {
	return DocumentWindow::getDesktopWindowStyleFlags();
}

void PluginWrapper::closeButtonPressed() {
	setVisible(false);
}
