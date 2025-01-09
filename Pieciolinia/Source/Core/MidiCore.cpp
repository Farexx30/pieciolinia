#include "MidiCore.h"
#include "MidiDeviceListEntry.h"
#include "MidiDeviceListBox.h"

//Ctors/Dtors (Constructors/Destructors):
MidiCore::MidiCore()
    : midiKeyboard(midiKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
    midiOutputSelector(new MidiDeviceListBox(ListBoxConstants::midiOutputSelectorName, *this))
{
    addLabelAndSetStyle(midiOutputLabel);

    midiKeyboard.setName(MidiKeyboardConstants::midiKeyboardName);
    //midiKeyboard.setAvailableRange(72, 84); //Jak chcecie obciac sobie pianino (warto zaznaczyc, ze wtedy i tak z klawiatury mozna grac te nie wyswietlone przyciski, wiec trzeba bedzie sie tym zajac!).
    addAndMakeVisible(midiKeyboard);

    addAndMakeVisible(midiOutputSelector.get());

    midiKeyboardState.addListener(this);

    setSize(732, 520);

    updateDeviceList();
}

MidiCore::~MidiCore()
{
    midiOutputs.clear();
    midiOutputSelector.reset();

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


//Virtual members from juce::Component:
void MidiCore::paint(juce::Graphics&)
{
    //Empty - nothing to be added.
}

void MidiCore::resized()
{
    int margin = 10, width = getWidth(), height = getHeight();

    midiOutputLabel.setBounds((width / 2) - 5 * margin, margin, (width / 2) - (2 * margin), 24);
    midiOutputSelector->setBounds((width / 4), (2 * margin) + 24,
        (width / 2) - (2 * margin),
        (height / 2) - ((4 * margin) + 24 + 24));

    midiKeyboard.setBounds(0, (height / 2) + (24 + margin), width, 64);
    //juce::AffineTransform transform = juce::AffineTransform::scale(1.5f, 1.0f); // 1.5x horizontal scale
    //midiKeyboard.setTransform(transform);
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Custom methods !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//==============================================================================
// PUBLIC MEMBERS
//==============================================================================
void MidiCore::openDevice(int index)
{
    midiOutputs[index]->outputDevice = juce::MidiOutput::openDevice(midiOutputs[index]->deviceInfo.identifier);
    if (midiOutputs[index]->outputDevice == nullptr)
    {
        //NOT GOOD:( ERROR - czyli nie udalo sie otworzyc urzadzenia
    }
}

void MidiCore::closeDevice(int index)
{
    midiOutputs[index]->resetDevice();
}

juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> MidiCore::getMidiDevice(int index) const
{
    return midiOutputs[index];
}

int MidiCore::getNumberOfMidiOutputs() const
{
    return midiOutputs.size();
}


//==============================================================================
// PRIVATE MEMBERS
//==============================================================================
void MidiCore::sendToOutputs(const juce::MidiMessage& message)
{
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

//Tak naprawde to niepotrzebne teraz, ale ogolnie sprawdza, czy faktycznie lista aktywnych urzadzen rozni sie od tych, ktore aktualnie nasza aplikacja zna - opisane w "updateDeviceList()" dlaczego poki co zbedne.
bool MidiCore::hasDeviceListChanged(const juce::Array<juce::MidiDeviceInfo>& availableDevices)
{
    if (midiOutputs.size() != availableDevices.size())
    {
        return true;
    }

    for (int i = 0; i < availableDevices.size(); ++i)
    {
        if (availableDevices[i] != midiOutputs[i]->deviceInfo)
        {
            return true;
        }
    }

    return false;
}

juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> MidiCore::findDevice(const juce::MidiDeviceInfo& deviceInfo) const
{
    for (auto& device : midiOutputs)
    {
        //Jesli to urzadzenie juz istnieje, to je po prostu zwroc (czyli jesli nie jest nowe):
        if (device->deviceInfo == deviceInfo)
        {
            return device;
        }
    }

    //Jesli jest nowe, to jeszcze go nie znamy, wiec zwracamy nullptr:
    return nullptr;
}

//Zwalnia zasoby odlaczonych juz urzadzen:
void MidiCore::closeUnpluggedDevices(const juce::Array<juce::MidiDeviceInfo>& currentlyPluggedInDevices)
{
    //I ogolnie dlaczego wszedzie "++i" albo "--i" zamiast po prostu "i++" albo "i--"? Poniewaz efekt ten sam, a --i oraz ++i sa minimalnie bardziej wydajne (w internecie opisane dokladniej dlaczego) - choc tak naprawde teraz kompilatory i tak juz czesto optymalizuja uzycie i++ czy i-- aby byly traktowane jak ++i i --i (tak ja przeczytalem i to zrozumialem).
    for (int i = midiOutputs.size(); --i >= 0;) //Zapis ten sam co: for (int i = midiOutputs.size() - 1; i >= 0; --i)
    {
        auto& device = *midiOutputs[i];
        if (!currentlyPluggedInDevices.contains(device.deviceInfo))
        {
            if (device.outputDevice != nullptr)
            {
                closeDevice(i);
            }

            midiOutputs.remove(i);
        }
    }
}

void MidiCore::updateDeviceList()
{
    auto availableDevices = juce::MidiOutput::getAvailableDevices();
    if (hasDeviceListChanged(availableDevices)) //Tak naprawde to u nas ten if nie jest potrzebny, ale jesli mielibysmy tez midiInputs jak w tym MidiDemo i zastosowalibysmy to samo podejscie co oni, to ten if ma juz wtedy sens.
    {
        closeUnpluggedDevices(availableDevices);

        juce::ReferenceCountedArray<MidiDeviceListEntry> newMidiOutputs; //Ogolnie moznaby nie uzywac tymczasowej tablicy/listy i od razu w tym ifie "if (foundDevice == nullptr) {}" dodac nowe urzadzenie do midiOutputs jednakze uzycie tymczasowego pojemnika na dane jest ogolnie "bezpieczniejsze" jesli mielibysmy jeszcze jakies inne kawalki kodu, w ktorych lista ta moglaby zostac w tym samym czasie zmodyfikowana (np. asynchroniczne). U nas co prawda nie ma takich, ale kto wie jak faktyczny projekt bedzie wygladal, a to i tak nie powoduje zadnej zauwazalnej roznicy w wydajnosci.
        for (auto& device : availableDevices)
        {
            MidiDeviceListEntry::Ptr foundDevice = findDevice(device);

            //Jesli to urzadzenie nie jest nam jeszcze znane (czyli jest nowo podlaczone):
            if (foundDevice == nullptr)
            {
                foundDevice = new MidiDeviceListEntry(device);
            }

            newMidiOutputs.add(foundDevice);
        }
        midiOutputs = newMidiOutputs;

        //Update Listboxa:
        midiOutputSelector->syncSelectedItemsWithDeviceList(midiOutputs);
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

