
#pragma once
#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW

#include<JuceHeader.h>

class SettingsWindow final
{
public:
	SettingsWindow();
	~SettingsWindow();



private:

	void addLabelAndSetStyle(juce::Label& label);
};

#endif
