
#pragma once
#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW

#include<JuceHeader.h>

class SettingsWindow final : public juce::DocumentWindow,
	public juce::ChangeBroadcaster
{
public:
	SettingsWindow(const juce::String& name);
	~SettingsWindow();

	void closeButtonPressed() override;
private:

	void addLabelAndSetStyle(juce::Label& label);
};

#endif
