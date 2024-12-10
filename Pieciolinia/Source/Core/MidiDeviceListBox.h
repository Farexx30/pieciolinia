#pragma once
#ifndef MIDIDEVICELISTBOX_H
#define MIDIDEVICELISTBOX_H

#include<JuceHeader.h>

//Zadeklarowanie, ze taka klasa istnieje (plik naglowkowy zaimportowany w pliku .cpp).
//Powod? Musimy odwolac sie z tej klasy do klasy MidiCore, a z klasy MidiCore do tej klasy, wiec jest to konieczne jesli chcemy zachowac ich implementacje/definicje w osobnych plikach, a do tego nie popasc w nieskonczona petle importowania plikow naglowkowych (blad na etapie kompilacj).
class MidiCore;
struct MidiDeviceListEntry;



class MidiDeviceListBox final
    : public juce::ListBox,
    private juce::ListBoxModel

{
public:
    //Ctors/Dtors:
    MidiDeviceListBox(const juce::String& name, MidiCore& midiCore);

    //Overriden virtual members from juce::ListBoxModel:
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& graphics, int width, int height, bool isRowSelected) override;
    void selectedRowsChanged(int) override;

    //Custom public methods:
    void syncSelectedItemsWithDeviceList(const juce::ReferenceCountedArray<MidiDeviceListEntry>& midiDevices);

private:
    //Private properties:
    MidiCore& parent;
    juce::SparseSet<int> lastSelectedItems;
};

#endif
