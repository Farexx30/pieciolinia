#include "SettingsWindow.h"

SettingsWindow::SettingsWindow(const juce::String& name)
	: DocumentWindow(name,
		juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
		DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);

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

}

void SettingsWindow::closeButtonPressed()
{
    sendChangeMessage();
    juce::MessageManager::callAsync([this] { delete this; });
}

void SettingsWindow::addLabelAndSetStyle(juce::Label& label)
{
}

