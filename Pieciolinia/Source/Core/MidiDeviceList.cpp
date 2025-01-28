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
		//If the device already exists, we just return it (if it's not new):
        if (device->deviceInfo == deviceInfo)
        {
            return device;
        }
    }
    //If the device is new, we don't know it yet so we return nullptr:
    return nullptr;
}


//This method releases resources of already disconnected devices:
void MidiDeviceList::closeUnpluggedDevices(const juce::Array<juce::MidiDeviceInfo>& currentlyPluggedInDevices)
{
    for (int i = midiOutputs.size(); --i >= 0;)
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

    juce::ReferenceCountedArray<MidiDeviceListEntry> newMidiOutputs;
    for (auto& device : availableDevices)
    {
        MidiDeviceListEntry::Ptr foundDevice = findDevice(device);
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
