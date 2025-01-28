#include "MidiDeviceListBox.h"
#include "MidiDeviceListEntry.h"
#include "SettingsComponent.h"

MidiDeviceListBox::MidiDeviceListBox(const juce::String& name, SettingsComponent& parent)
    : juce::ListBox(name),
    _parent(parent)
{
    setModel(this);
    setOutlineThickness(1);
    setMultipleSelectionEnabled(true);
    setClickingTogglesRowSelection(true);
}


//Overriden virtual members from juce::ListBoxModel:
int MidiDeviceListBox::getNumRows()
{
    return _parent.getNumberOfMidiOutputs();
}

void MidiDeviceListBox::paintListBoxItem(int rowNumber, juce::Graphics& graphics, int width, int height, bool isRowSelected)
{
    auto textColor = getLookAndFeel()
        .findColour(ListBox::textColourId);

    if (isRowSelected)
    {
        graphics.fillAll(textColor.interpolatedWith(getLookAndFeel()
            .findColour(ListBox::backgroundColourId), 0.5));
    }

    graphics.setColour(textColor);
    graphics.setFont(height * 0.7f);

    if (rowNumber < _parent.getNumberOfMidiOutputs())
    {
        auto midiDevice = _parent.getMidiDevice(rowNumber);
        graphics.drawText(midiDevice->deviceInfo.name,
            5, 0, width, height,
            juce::Justification::centredLeft, true);
    }
}

//TODO: change comment language
//Jesli zostalo zmienione zaznaczenie wierszy w listboxie to otwieramy/zamykamy urzadzenia (zalezy czy zaznaczylismy czy odznaczylismy urzadzenie):
void MidiDeviceListBox::selectedRowsChanged(int)
{
    auto currentSelectedItems = getSelectedRows();
    if (currentSelectedItems != lastSelectedItems)
    {
        for (int i = 0; i < lastSelectedItems.size(); ++i)
        {
            if (!currentSelectedItems.contains(lastSelectedItems[i]))
            {
                _parent.closeDevice(lastSelectedItems[i]);
            }
        }

        for (int i = 0; i < currentSelectedItems.size(); ++i)
        {
            if (!lastSelectedItems.contains(currentSelectedItems[i]))
            {
                _parent.openDevice(currentSelectedItems[i]);
            }
        }

        lastSelectedItems = currentSelectedItems;
    }
}


//TODO: change comment language
//Custom PUBLIC methods:
//Metoda potrzebna nam do aktualizacji zaznaczonych elementow (czysto graficznie) jesli wpielibysmy/odpielibysmy jakies urzadzenie:
void MidiDeviceListBox::syncSelectedItemsWithDeviceList(const juce::ReferenceCountedArray<MidiDeviceListEntry>& midiDevices)
{
    juce::SparseSet<int> selectedRows;
    for (int i = 0; i < midiDevices.size(); ++i)
    {
        if (midiDevices[i]->outputDevice != nullptr)
        {
            selectedRows.addRange(juce::Range<int>(i, i + 1));
        }
    }

    lastSelectedItems = selectedRows;
    updateContent();
    setSelectedRows(selectedRows, juce::dontSendNotification);
}
