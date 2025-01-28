#pragma once
#ifndef MIDIDEVICELISTBOX_H
#define MIDIDEVICELISTBOX_H

#include<JuceHeader.h>

// --- Declarations ---
class SettingsComponent;
struct MidiDeviceListEntry;


class MidiDeviceListBox final
    : public juce::ListBox,
    private juce::ListBoxModel

{
public:
    //Ctors/Dtors:
    MidiDeviceListBox(const juce::String& name, SettingsComponent& parent);

    //Overriden virtual members from juce::ListBoxModel:
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& graphics, int width, int height, bool isRowSelected) override;
    void selectedRowsChanged(int) override;

    //Custom public methods:
    void syncSelectedItemsWithDeviceList(const juce::ReferenceCountedArray<MidiDeviceListEntry>& midiDevices);

private:
    //Private properties:
    SettingsComponent& _parent;
    juce::SparseSet<int> lastSelectedItems;
};

#endif
