#pragma once
#ifndef MIDIDEVICELISTENTRY_H
#define MIDIDEVICELISTENTRY_H

#include<JuceHeader.h>


struct MidiDeviceListEntry final
    : juce::ReferenceCountedObject
{
    //Ctors/Dtors:
    explicit MidiDeviceListEntry(juce::MidiDeviceInfo deviceInfo);

    //Public properties:
    juce::MidiDeviceInfo deviceInfo;
    std::unique_ptr<juce::MidiOutput> outputDevice;
    using Ptr = juce::ReferenceCountedObjectPtr<MidiDeviceListEntry>;

    //Custom public methods:
    void resetDevice();
};

#endif
