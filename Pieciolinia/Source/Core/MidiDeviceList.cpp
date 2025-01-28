#include "MidiDeviceList.h"
#include "MidiDeviceListEntry.h"
#include "MidiDeviceListBox.h"

MidiDeviceList::MidiDeviceList()
{
    updateDeviceList();
}

MidiDeviceList::~MidiDeviceList()
{
    midiOutputs.clear();
}

void MidiDeviceList::openDevice(int index)
{
    midiOutputs[index]->outputDevice = juce::MidiOutput::openDevice(midiOutputs[index]->deviceInfo.identifier);
    if (midiOutputs[index]->outputDevice == nullptr)
    {
		jassert("Failed to open MIDI output device");
    }
}

void MidiDeviceList::closeDevice(int index)
{
    midiOutputs[index]->resetDevice();
}

juce::ReferenceCountedArray<MidiDeviceListEntry> MidiDeviceList::getMidiDevices() const
{
    return midiOutputs;
}

juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> MidiDeviceList::getMidiDevice(int index) const
{
    return midiOutputs[index];
}

int MidiDeviceList::getNumberOfMidiOutputs() const
{
    return midiOutputs.size();
}

void MidiDeviceList::openDevice(const juce::ReferenceCountedObjectPtr<MidiDeviceListEntry>& device)
{
	device->outputDevice = juce::MidiOutput::openDevice(device->deviceInfo.identifier);
    if (device->outputDevice == nullptr)
    {
        jassert("Failed to open MIDI output device");
    }
}

juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> MidiDeviceList::findDevice(const juce::MidiDeviceInfo& deviceInfo) const
{
    for (auto& device : midiOutputs)
    {
        //TODO: change comment language
        //Jesli to urzadzenie juz istnieje, to je po prostu zwroc (czyli jesli nie jest nowe):
        if (device->deviceInfo == deviceInfo)
        {
            return device;
        }
    }
    //TODO: change comment language
    //Jesli jest nowe, to jeszcze go nie znamy, wiec zwracamy nullptr:
    return nullptr;
}

//TODO: change comment language
//Zwalnia zasoby odlaczonych juz urzadzen:
void MidiDeviceList::closeUnpluggedDevices(const juce::Array<juce::MidiDeviceInfo>& currentlyPluggedInDevices)
{//TODO: change comment language
    //I ogolnie dlaczego wszedzie "++i" albo "--i" zamiast po prostu "i++" albo "i--"? Poniewaz efekt ten sam, a --i oraz ++i sa minimalnie bardziej wydajne (w internecie opisane dokladniej dlaczego) - choc tak naprawde teraz kompilatory i tak juz czesto optymalizuja uzycie i++ czy i-- aby byly traktowane jak ++i i --i (tak ja przeczytalem i to zrozumialem).
    for (int i = midiOutputs.size(); --i >= 0;)//TODO: change comment language //Zapis ten sam co: for (int i = midiOutputs.size() - 1; i >= 0; --i)
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

void MidiDeviceList::updateDeviceList()
{
    auto availableDevices = juce::MidiOutput::getAvailableDevices(); 
    closeUnpluggedDevices(availableDevices);

    juce::ReferenceCountedArray<MidiDeviceListEntry> newMidiOutputs;//TODO: change comment language //Ogolnie moznaby nie uzywac tymczasowej tablicy/listy i od razu w tym ifie "if (foundDevice == nullptr) {}" dodac nowe urzadzenie do midiOutputs jednakze uzycie tymczasowego pojemnika na dane jest ogolnie "bezpieczniejsze" jesli mielibysmy jeszcze jakies inne kawalki kodu, w ktorych lista ta moglaby zostac w tym samym czasie zmodyfikowana (np. asynchroniczne). U nas co prawda nie ma takich, ale kto wie jak faktyczny projekt bedzie wygladal, a to i tak nie powoduje zadnej zauwazalnej roznicy w wydajnosci.
    for (auto& device : availableDevices)
    {
        MidiDeviceListEntry::Ptr foundDevice = findDevice(device);
        //TODO: change comment language
        //If this device is unknown yet for our application (if it just has been connected):
        if (foundDevice == nullptr)
        {
			//Create new MidiDeviceListEntry object and open the device:
            foundDevice = new MidiDeviceListEntry(device);
			openDevice(foundDevice);
        }

        newMidiOutputs.add(foundDevice);
    }
    midiOutputs = newMidiOutputs;

    sendChangeMessage();
}
