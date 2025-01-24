/*
  ==============================================================================

    CustomTextButton.h
    Created: 24 Jan 2025 10:22:59pm
    Author:  Lenovo

  ==============================================================================
*/


#pragma once
#include <JuceHeader.h>

class CustomTextButton : public juce::TextButton
{
public:
    CustomTextButton(const juce::String& text, const juce::Font& customFont);
    void paint(juce::Graphics& g) override;

private:
    juce::Font m_customFont;
};