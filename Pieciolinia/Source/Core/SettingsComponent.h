#pragma once
#ifndef SETTINGSCOMPONENT_H
#define SETTINGSCOMPONENT_H

#include<JuceHeader.h>
#include "../Common/Constants.h"
class MidiDeviceListBox;
class MidiDeviceList;
struct MidiDeviceListEntry;

class SettingsComponent final : public juce::Component,
    public juce::ChangeListener
{
public:
    SettingsComponent(MidiDeviceList& midiDeviceList);
    ~SettingsComponent();

    void resized() override;

    void openDevice(int index);
    void closeDevice(int index);
    juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> getMidiDevice(int index) const;
    int getNumberOfMidiOutputs() const;

    //Listeners:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
private:
    MidiDeviceList& _midiDeviceList;
    std::unique_ptr<MidiDeviceListBox> midiOutputSelector;
};
#endif
