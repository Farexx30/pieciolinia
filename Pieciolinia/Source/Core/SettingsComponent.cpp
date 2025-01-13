#include "SettingsComponent.h"
#include "MidiDeviceListBox.h"
#include "MidiDeviceList.h"
#include "MidiDeviceListEntry.h"

SettingsComponent::SettingsComponent(MidiDeviceList& midiDeviceList)
	: _midiDeviceList(midiDeviceList),
    midiOutputSelector(new MidiDeviceListBox(ListBoxConstants::midiOutputSelectorName, *this))
{
    _midiDeviceList.addChangeListener(this);

    addAndMakeVisible(midiOutputSelector.get());

    setSize(720, 480);
}

SettingsComponent::~SettingsComponent()
{
    _midiDeviceList.removeChangeListener(this);
    midiOutputSelector.reset();
}

void SettingsComponent::paint(juce::Graphics&)
{
}

void SettingsComponent::resized()
{
    int margin = 10, width = getWidth(), height = getHeight();

    midiOutputSelector->setBounds((width / 4), (2 * margin) + 24,
        (width / 2) - (2 * margin),
        (height / 2) - ((4 * margin) + 24 + 24));
}

void SettingsComponent::openDevice(int index)
{
    _midiDeviceList.openDevice(index);
}

void SettingsComponent::closeDevice(int index)
{
    _midiDeviceList.closeDevice(index);
}

juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> SettingsComponent::getMidiDevice(int index) const
{
    return _midiDeviceList.getMidiDevice(index);
}

int SettingsComponent::getNumberOfMidiOutputs() const
{
    return _midiDeviceList.getNumberOfMidiOutputs();
}

void SettingsComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &_midiDeviceList)
    {
        auto midiDevices = _midiDeviceList.getMidiDevices();
        midiOutputSelector->syncSelectedItemsWithDeviceList(midiDevices);
    }
}

void SettingsComponent::addLabelAndSetStyle(juce::Label& label)
{

}
