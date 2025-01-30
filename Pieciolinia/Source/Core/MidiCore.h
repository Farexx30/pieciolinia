#pragma once
#ifndef MIDICORE_H
#define MIDICORE_H

#include<JuceHeader.h>
#include "../Common/Constants.h"
#include "CustomMidiKeyboardComponent.h"
#include "../Common/Timer.h"


// --- Declarations ---
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
    void resized() override;

    //Custom public methods:
    //Playback:
    void startPlayback();
    void pausePlayback();
    void stopPlayback();



private:
    //Custom private methods:
    void showSettingsWindow();
    void sendToOutputs(const juce::MidiMessage& message);
    void addLabelAndSetStyle(juce::Label& label);
    void addText(juce::TextEditor& editor, const juce::String& text);

    //Buttons management:
    void lockInputs();
    void unlockInputs();

    //Playback:
    void playbackWorker();

    //Notes management:
    void arrowUpClick();
    void arrowDownClick();
    void addNoteByButton(Note::NoteLength noteLength);
    void addNoteRestByButton(Note::NoteLength noteLength);
    void deleteLastNote();

    juce::String setHigherNote(juce::String text);
    juce::String setNoteLower(juce::String text);

    //MessageBox management:
	void showMessageBox(const juce::AlertWindow::AlertIconType& iconType, 
        const juce::String& title, 
        const juce::String& message);

    //File management:
	void saveToFile();
	void saveAsPiecioliniaFile(const juce::File& file);
	void saveAsMidiFile(const juce::File& file);
	void readFromFile();
    void getNotesFromImportedFile(const juce::String& content);
    void setLoadedCompositionData(const juce::String& content, const juce::String& fileNameWithoutExtension);



    //Private properties:
    Timer timer;
	Note::NoteName chosenNoteName = Note::NoteName::a1;
    juce::String compositionName;
    juce::TextEditor compositionNotesTextEditor;

    bool isKeyboardLocked = false;

    MidiDeviceList& _midiDeviceList;

    juce::MidiKeyboardState midiKeyboardState;
    CustomMidiKeyboardComponent midiKeyboard;

    juce::Component::SafePointer<SettingsWindow> settingsWindow;

	//Playback properties
    std::thread playbackThread;
    std::atomic<bool> isPlaying{ false };
    std::atomic<bool> isPaused{ false };
    std::condition_variable pauseCondition;
    std::mutex pauseMutex;

    //For file saving/reading:
	std::unique_ptr<juce::FileChooser> fileChooser;

    //For GUI
    juce::TextButton header;
    juce::TextButton LogoElement;
    juce::TextButton saveFileElement;
    juce::TextButton folderElement;
    juce::TextButton playElement;
    juce::TextButton pauseElement;
    juce::TextButton stopElement;
    juce::TextButton settingsElement;
    juce::TextButton arrowUpElement;
    juce::TextButton arrowDownElement;
    juce::TextButton backspaceElement;
    juce::TextButton midiKeyboardElement;
    juce::TextButton sixteenthNoteElement;
    juce::TextButton sixteenthNoteRestElement;
    juce::TextButton wholeNoteElement;
    juce::TextButton wholeNoteRestElement;
    juce::TextButton halfNoteElement;
    juce::TextButton halfNoteRestElement;
    juce::TextButton quarterNoteElement;
    juce::TextButton quarterNoteRestElement;
    juce::TextButton eighthNoteElement;
    juce::TextButton eighthNoteRestElement;
    juce::TextButton compositionNotesElement;

    std::unique_ptr<juce::DrawableButton> saveFileButton;
    std::unique_ptr<juce::DrawableButton> folderButton;
    std::unique_ptr<juce::DrawableButton> pauseButton;
    std::unique_ptr<juce::DrawableButton> playButton;
    std::unique_ptr<juce::DrawableButton> backspaceButton;
    std::unique_ptr<juce::DrawableButton> stopButton;
    std::unique_ptr<juce::DrawableButton> settingsButton;
    std::unique_ptr<juce::DrawableButton> arrowUpButton;
    std::unique_ptr<juce::DrawableButton> arrowDownButton;
    std::unique_ptr<juce::DrawableButton> logoButton;
    std::unique_ptr<juce::DrawableButton> wholeNoteButton;
    std::unique_ptr<juce::DrawableButton> wholeNoteRestButton;
    std::unique_ptr<juce::DrawableButton> halfNoteButton;
    std::unique_ptr<juce::DrawableButton> halfNoteRestButton;
    std::unique_ptr<juce::DrawableButton> quarterNoteButton;
    std::unique_ptr<juce::DrawableButton> quarterNoteRestButton;
    std::unique_ptr<juce::DrawableButton> eighthNoteButton;
    std::unique_ptr<juce::DrawableButton> eighthNoteRestButton;
    std::unique_ptr<juce::DrawableButton> sixteenthNoteButton;
    std::unique_ptr<juce::DrawableButton> sixteenthNoteRestButton;

    std::unique_ptr<juce::TextEditor> nameSongTextEditor;
    std::unique_ptr<juce::TextEditor> switchNoteTextEditor;

    //const properties:
    const int lowestNote = 72;
    const int highestNote = 91;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiCore)
};

#endif
