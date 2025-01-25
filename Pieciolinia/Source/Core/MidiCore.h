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
struct MidiDeviceListEntry;
class MidiDeviceListBox;


class MidiCore final
    : public juce::Component,
    private juce::MidiKeyboardState::Listener
{
public:
    //Ctors/Dtors:
    MidiCore();
    ~MidiCore();

    //Overriden virtual members from juce::MidiKeyboardState::Listener:
    void handleNoteOn(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;

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
    bool hasDeviceListChanged(const juce::Array<juce::MidiDeviceInfo>& availableDevices);
    juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> findDevice(const juce::MidiDeviceInfo& deviceInfo) const;
    void closeUnpluggedDevices(const juce::Array<juce::MidiDeviceInfo>& currentlyPluggedInDevices);
    void updateDeviceList(); //Only for output devices (w przypadku tego programu).
    void addLabelAndSetStyle(juce::Label& label);
    void addText(juce::TextEditor& editor, const juce::String& text);

    //Private properties:
    juce::TextEditor textEditorForNotesTest;
    Timer timer;

    //For GUI
    juce::TextButton header;
    juce::TextButton element1;
    juce::TextButton element2;
    juce::TextButton element3;
    juce::TextButton element4;
    juce::TextButton element5;
    juce::TextButton element6;
    juce::TextButton element7;
    juce::TextButton element8;
    juce::TextButton element9;
    juce::TextButton element11;
    juce::TextButton element22;
    juce::TextButton element33;
    juce::TextButton element44;
    juce::TextButton element55;
    juce::TextButton element66;
    juce::TextButton element77;
    juce::TextButton element88;
    juce::TextButton element99;
    juce::TextButton element111;
    juce::TextButton element222;
    juce::TextButton element333;
    juce::TextButton element444;
    juce::TextButton element555;
    juce::TextButton element666;
    juce::TextButton orangeContent;

    std::unique_ptr<juce::DrawableButton> saveButton;
    std::unique_ptr<juce::DrawableButton> folderButton;
    std::unique_ptr<juce::DrawableButton> pauseButton;
    std::unique_ptr<juce::DrawableButton> playButton;
    std::unique_ptr<juce::DrawableButton> backspaceButton;
    std::unique_ptr<juce::DrawableButton> stopButton;
    std::unique_ptr<juce::DrawableButton> settingsButton;
    std::unique_ptr<juce::DrawableButton> arrowUpButton;
    std::unique_ptr<juce::DrawableButton> arrowDownButton;
    std::unique_ptr<juce::DrawableButton> verifyButton;
    std::unique_ptr<juce::DrawableButton> logoButton;
    std::unique_ptr<juce::DrawableButton> cfButton;
    std::unique_ptr<juce::DrawableButton> dButton;
    std::unique_ptr<juce::DrawableButton> eButton;
    std::unique_ptr<juce::DrawableButton> fButton;
    std::unique_ptr<juce::DrawableButton> gButton;
    std::unique_ptr<juce::DrawableButton> aButton;
    std::unique_ptr<juce::DrawableButton> bButton;
    std::unique_ptr<juce::DrawableButton> c2Button;


    juce::Label midiOutputLabel{ LabelConstants::midiOutputName, LabelConstants::midiOutputText };

    juce::MidiKeyboardState midiKeyboardState; 
    CustomMidiKeyboardComponent midiKeyboard;

    juce::ReferenceCountedArray<MidiDeviceListEntry> midiOutputs;
    std::unique_ptr<MidiDeviceListBox> midiOutputSelector;

    juce::MidiDeviceListConnection connection = juce::MidiDeviceListConnection::make([this]
        {
            updateDeviceList();
        });

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiCore)
};

#endif
