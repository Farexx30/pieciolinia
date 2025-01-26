#pragma once
#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include<JuceHeader.h>
class MidiDeviceList;

class SettingsWindow final : public juce::DocumentWindow,
	public juce::ChangeBroadcaster
{
public:
	SettingsWindow(const juce::String& name, MidiDeviceList& midiDeviceList);
	~SettingsWindow();

	void closeButtonPressed() override;
private:
	MidiDeviceList& _midiDeviceList;
};

#endif
