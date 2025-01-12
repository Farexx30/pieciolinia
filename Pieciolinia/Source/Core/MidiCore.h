#pragma once
#ifndef MIDICORE_H
#define MIDICORE_H

#include<JuceHeader.h>
#include "../Common/Constants.h"
#include "CustomMidiKeyboardComponent.h"
#include "../Common/Timer.h"

//Zadeklarowanie, ze takie struktury/klasy istnieja (pliki naglowkowe zaimportowane w pliku .cpp).
//Powod? Musimy odwolac sie z tej klasy do klasy MidiDeviceListBox, a z klasy klasy MidiDeviceListBox do tej klasy, wiec jest to konieczne jesli chcemy zachowac ich implementacje/definicje w osobnych plikach, a do tego nie popasc w nieskonczona petle importowania plikow naglowkowych (blad na etapie kompilacj).
//Co prawda w przypadku struktury MidiDeviceListEntry nie byloby tego problemu, bo nie musimy się z MidiDeviceListEntry odwolywac do MidiCore, ale wydaje sie to byc mimo wszystko dobra praktyka promujaca zasade open-closed principle z SOLIDA.
class MidiDeviceList;
struct MidiDeviceListEntry;


class MidiCore final
    : public juce::Component,
    public juce::ChangeListener,
    private juce::MidiKeyboardState::Listener
{
public:
    //Ctors/Dtors:
    MidiCore(MidiDeviceList& midiDeviceList);
    ~MidiCore();

    //Overriden virtual members from juce::MidiKeyboardState::Listener:
    void handleNoteOn(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;

    //Listeners:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    //Overriden virtual members from juce::Component:
    void paint(juce::Graphics&) override;
    void resized() override;

    //Custom public methods:
    void openDevice(int index);
    void closeDevice(int index);
    juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> getMidiDevice(int index) const;
    int getNumberOfMidiOutputs() const;


private:
    //Custom private methods:
    void sendToOutputs(const juce::MidiMessage& message);
    void addLabelAndSetStyle(juce::Label& label);

    //Private properties:
    Timer timer;

    juce::MidiKeyboardState midiKeyboardState; 
    CustomMidiKeyboardComponent midiKeyboard;

    MidiDeviceList& _midiDeviceList;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiCore)
};

#endif
