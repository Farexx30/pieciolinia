#include "MidiCore.h"
#include "MidiDeviceList.h"
#include "MidiDeviceListEntry.h"
#include "MidiDeviceListBox.h"


//Ctors/Dtors (Constructors/Destructors):
MidiCore::MidiCore(MidiDeviceList& midiDeviceList)
    : midiKeyboard(midiKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
    _midiDeviceList(midiDeviceList)
{
    midiKeyboard.setName(MidiKeyboardConstants::midiKeyboardName);
    midiKeyboard.setAvailableRange(72, 84); //Jak chcecie obciac sobie pianino (warto zaznaczyc, ze wtedy i tak z klawiatury mozna grac te nie wyswietlone przyciski, wiec trzeba bedzie sie tym zajac!).
    addAndMakeVisible(midiKeyboard);;

    midiKeyboardState.addListener(this);

    setSize(732, 520);
}

MidiCore::~MidiCore()
{
    midiKeyboardState.removeListener(this);
}


//Overriden virtual members from juce::MidiKeyboardState::Listener:
//Obsluga klikniecia klawisza pianina:
void MidiCore::handleNoteOn(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    timer.reset(); // start of measuring time
    juce::MidiMessage message(juce::MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity));
    message.setTimeStamp(juce::Time::getMillisecondCounterHiRes() * 0.001); //po prostu zalecana wartosc timestampa dla czystego i precyzyjnego brzmienia, a * 0.001, poniewaz wartosc ta jest okreslana domyslnie w sekundach, a "getMillisecondCounterHiRes()" zwraca wynik w milisekundach.
    sendToOutputs(message);
}

//Obsluga puszczenia klawisza pianina:
void MidiCore::handleNoteOff(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    double elapsed = timer.elapsedMilliseconds(); // Checking Time
    juce::MidiMessage message(juce::MidiMessage::noteOff(midiChannel, midiNoteNumber, velocity));
    message.setTimeStamp(juce::Time::getMillisecondCounterHiRes() * 0.001); //po prostu zalecana wartosc timestampa dla czystego i precyzyjnego brzmienia, a * 0.001, poniewaz wartosc ta jest okreslana domyslnie w sekundach, a "getMillisecondCounterHiRes()" zwraca wynik w milisekundach.
    sendToOutputs(message);
}

void MidiCore::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &_midiDeviceList)
    {
        std::cout << "XD" << source;
    }
}


//Virtual members from juce::Component:
void MidiCore::paint(juce::Graphics&)
{
    //Empty - nothing to be added.
}

void MidiCore::resized()
{
    int margin = 10, width = getWidth(), height = getHeight();

    midiKeyboard.setBounds(width / 2 - 204, (height / 2) + (24 + margin), 408, 256);
}



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Custom methods !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//==============================================================================
// PUBLIC MEMBERS
//==============================================================================
void MidiCore::openDevice(int index)
{
    _midiDeviceList.openDevice(index);
}

void MidiCore::closeDevice(int index)
{
    _midiDeviceList.closeDevice(index);
}

juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> MidiCore::getMidiDevice(int index) const
{
    return _midiDeviceList.getMidiDevice(index);
}

int MidiCore::getNumberOfMidiOutputs() const
{
    return _midiDeviceList.getNumberOfMidiOutputs();
}


//==============================================================================
// PRIVATE MEMBERS
//==============================================================================
void MidiCore::sendToOutputs(const juce::MidiMessage& message)
{
    auto midiOutputs = _midiDeviceList.getMidiDevices();
    for (auto* midiOutput : midiOutputs)
    {
        if (auto* outputDevice = midiOutput->outputDevice.get())
        {
            outputDevice->sendMessageNow(message);
        }
        //Powyzszy zapis jest rownoznaczny z tym:
        //if (midiOutput->outputDevice != nullptr)
        //{
        //    midiOutput->outputDevice->sendMessageNow(message);
        //}
    }
}

void MidiCore::addLabelAndSetStyle(juce::Label& label)
{
    label.setFont(juce::FontOptions(15.00f, juce::Font::plain));
    label.setJustificationType(juce::Justification::centredLeft);
    label.setEditable(false, false, false);
    label.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label);
}

