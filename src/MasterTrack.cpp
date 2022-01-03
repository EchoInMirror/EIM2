#include "MasterTrack.h"

MasterTrack::MasterTrack(): SynchronizedAudioProcessorGraph() {
	manager.addDefaultFormats();

	knownPluginListXMLFile = juce::File::getCurrentWorkingDirectory().getChildFile("knownPlugins.xml");
	if (knownPluginListXMLFile.exists()) {
		list.recreateFromXml(*juce::XmlDocument::parse(knownPluginListXMLFile.loadFileAsString()).release());
	} else scanPlugins();

	deviceManager.getAudioDeviceSetup(setup);
	deviceManager.initialiseWithDefaultDevices(0, 2);

	deviceManager.addAudioCallback(&graphPlayer);
	graphPlayer.setProcessor(this);
	outputNodeID = addNode(std::make_unique<juce::AudioProcessorGraph::AudioGraphIOProcessor>(juce::AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode))->nodeID;

	setPlayConfigDetails(0, 2, sampleRate, bufferSize);
	prepareToPlay(sampleRate, bufferSize);

	auto track = createTrack()->getProcessor();
	((Track*)track)->setGenerator(loadPlugin(0));
}

void MasterTrack::scanPlugins() {
	auto file = "C:\\Program Files\\Common Files\\VST3\\Arturia\\pigments.vst3";
	auto formats = manager.getFormats();
	bool flag = false;
	for (auto it = formats.begin(); it <= formats.end(); it++) {
		if ((*it)->fileMightContainThisPluginType(file)) {
			auto arr = new juce::OwnedArray<juce::PluginDescription>();
			if (list.scanAndAddFile(file, true, *arr, **it)) {
				flag = true;
				break;
			}
		}
	}

	if (flag) {
		list.createXml().release()->writeToFile(knownPluginListXMLFile, "");
	}
}

std::unique_ptr<PluginWrapper> MasterTrack::loadPlugin(int id) {
	juce::String err;
	auto instance = manager.createPluginInstance(*list.getType(id), getSampleRate(), getBlockSize(), err);
	return std::make_unique<PluginWrapper>(std::move(instance));
}

juce::AudioProcessorGraph::Node::Ptr MasterTrack::createTrack() {
	auto track = std::make_unique<Track>();
	track->setPlayConfigDetails(2, 2, getSampleRate(), getBlockSize());
	track->prepareToPlay(getSampleRate(), getBlockSize());
	auto node = addNode(std::move(track));
	tracks.push_back(node);
	addConnection({ { node->nodeID, 0 }, { outputNodeID, 0 } });
	addConnection({ { node->nodeID, 1 }, { outputNodeID, 1 } });
	return node;
}

void MasterTrack::removeTrack(int id) {
	removeNode(tracks[id]);
}