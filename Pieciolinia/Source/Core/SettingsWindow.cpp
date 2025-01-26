#include "SettingsWindow.h"
#include "MidiDeviceListBox.h"
#include "SettingsComponent.h"
#include "MidiDeviceList.h"

SettingsWindow::SettingsWindow(const juce::String& name, MidiDeviceList& midiDeviceList)
	: DocumentWindow(name,
		juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
		DocumentWindow::allButtons),
    _midiDeviceList(midiDeviceList)
{
    setUsingNativeTitleBar(true);
    auto settingsComponent = new SettingsComponent(_midiDeviceList);
    setContentOwned(settingsComponent, true);

#if JUCE_IOS || JUCE_ANDROID
    setFullScreen(true);
#else
    setResizable(true, true);
    setResizeLimits(300, 250, 10000, 10000);
    centreWithSize(getWidth(), getHeight());
#endif

    setVisible(true);
}

SettingsWindow::~SettingsWindow()
{
    this->removeAllChangeListeners();
}

void SettingsWindow::closeButtonPressed()
{
    sendChangeMessage();
    juce::MessageManager::callAsync([this] { delete this; });
}

