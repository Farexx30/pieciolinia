#pragma once
#ifndef CUSTOMMIDIKYEBOARDCOMPONENT_H
#define CUSTOMMIDIKYEBOARDCOMPONENT_H
 
//Custom MIDI Keyboard Component with larger keys (implementation kept in .h for simplicity):

#include <JuceHeader.h>

class CustomMidiKeyboardComponent : public juce::MidiKeyboardComponent
{
public:
    CustomMidiKeyboardComponent(juce::MidiKeyboardState& state, Orientation orientation)
        : juce::MidiKeyboardComponent(state, orientation)
    {
        setKeyWidth(51.0f);
    }

    void drawWhiteNote(int midiNoteNumber, juce::Graphics& g, juce::Rectangle<float> area,
        bool isDown, bool isOver, juce::Colour lineColour, juce::Colour textColour) override
    {
        g.setColour(isDown ? juce::Colours::lightgrey : juce::Colours::white);
        g.fillRect(area);

        g.setColour(lineColour);
        g.drawRect(area);

        if (isOver)
        {
            g.setColour(juce::Colours::lightgrey.withAlpha(0.2f));
            g.fillRect(area);
        }
    }

    void drawBlackNote(int midiNoteNumber, juce::Graphics& g, juce::Rectangle<float> area,
        bool isDown, bool isOver, juce::Colour noteFillColour) override
    {
        g.setColour(isDown ? noteFillColour.brighter() : noteFillColour);
        g.fillRect(area);

        if (isOver)
        {
            g.setColour(juce::Colours::white.withAlpha(0.1f));
            g.fillRect(area);
        }
    }
};

#endif