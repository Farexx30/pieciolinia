/*
  ==============================================================================

    SettingsComponent.h
    Created: 12 Jan 2025 11:29:01pm
    Author:  Łukasz

  ==============================================================================
*/

#pragma once
#ifndef SETTINGSCOMPONENT_H
#define SETTINGSCOMPONENT_H

#include<JuceHeader.h>
#include "../Common/Constants.h"
class MidiDeviceListBox;
class MidiDeviceList;
struct MidiDeviceListEntry;

class SettingsComponent : public juce::Component,
    public juce::ChangeListener
{
public:
    SettingsComponent(MidiDeviceList& midiDeviceList);
    ~SettingsComponent();

    void paint(juce::Graphics&) override;
    void resized() override;


    void openDevice(int index);
    void closeDevice(int index);
    juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> getMidiDevice(int index) const;
    int getNumberOfMidiOutputs() const;

    //Listeners:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
private:
    void addLabelAndSetStyle(juce::Label& label);

    MidiDeviceList& _midiDeviceList;
    std::unique_ptr<MidiDeviceListBox> midiOutputSelector;
};
#endif
