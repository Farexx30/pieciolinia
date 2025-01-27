#pragma once
#ifndef MIDIDEVICESLIST_H
#define MIDIDEVICELIST_H

#include<JuceHeader.h>
struct MidiDeviceListEntry;

class MidiDeviceList final : public juce::ChangeBroadcaster
{
public:
	MidiDeviceList();
	~MidiDeviceList();

	void openDevice(int index);
	void closeDevice(int index);

	juce::ReferenceCountedArray<MidiDeviceListEntry> getMidiDevices() const;
	juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> getMidiDevice(int index) const;
	int getNumberOfMidiOutputs() const;
private:
	juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> findDevice(const juce::MidiDeviceInfo& deviceInfo) const;
	void closeUnpluggedDevices(const juce::Array<juce::MidiDeviceInfo>& currentlyPluggedInDevices);
	void updateDeviceList(); //Only for output devices

	juce::ReferenceCountedArray<MidiDeviceListEntry> midiOutputs;

	juce::MidiDeviceListConnection connection = juce::MidiDeviceListConnection::make([this]
	{
		updateDeviceList();
	});
};

#endif
