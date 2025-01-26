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
class SettingsWindow;


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

    void startPlayback();
    void pausePlayback();
    void stopPlayback();

private:
    //Custom private methods:
    void showSettingsWindow();
    void sendToOutputs(const juce::MidiMessage& message);
    void addLabelAndSetStyle(juce::Label& label);
    void addText(juce::TextEditor& editor, const juce::String& text);
    void playbackWorker();

    //Private properties:

    juce::TextEditor textEditorForNotesTest;
    Timer timer;

	//Playback properties
    std::thread playbackThread;
    std::atomic<bool> isPlaying{ false };
    std::atomic<bool> isPaused{ false };
    std::condition_variable pauseCondition;
    std::mutex pauseMutex;

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
    std::unique_ptr<juce::DrawableButton> staffButton;
    std::unique_ptr<juce::DrawableButton> cButton;
    std::unique_ptr<juce::DrawableButton> dButton;
    std::unique_ptr<juce::DrawableButton> eButton;
    std::unique_ptr<juce::DrawableButton> fButton;
    std::unique_ptr<juce::DrawableButton> gButton;
    std::unique_ptr<juce::DrawableButton> aButton;
    std::unique_ptr<juce::DrawableButton> bButton;
    std::unique_ptr<juce::DrawableButton> c2Button;
    std::unique_ptr<juce::DrawableButton> d2Button;
    std::unique_ptr<juce::DrawableButton> e2Button;


    juce::Label midiOutputLabel{ LabelConstants::midiOutputName, LabelConstants::midiOutputText };
    MidiDeviceList& _midiDeviceList;

    juce::MidiKeyboardState midiKeyboardState; 
    CustomMidiKeyboardComponent midiKeyboard;

    juce::Component::SafePointer<SettingsWindow> settingsWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiCore)
};

#endif
