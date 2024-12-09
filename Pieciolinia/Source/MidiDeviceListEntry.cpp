#include "MidiDeviceListEntry.h"


//Ctors/Dtors:
MidiDeviceListEntry::MidiDeviceListEntry(juce::MidiDeviceInfo deviceInfo)
    :deviceInfo(deviceInfo)
{
    //Empty
}


//Custom PUBLIC methods:
void MidiDeviceListEntry::resetDevice()
{
    outputDevice.reset();
}
