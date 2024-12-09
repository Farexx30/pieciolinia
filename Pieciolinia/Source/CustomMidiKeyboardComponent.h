//#pragma once
//
// 
// 
// 
// 
// !!!TO SIE MOZE PRZYDAC NA POTEM (MOZNA ZCUSTOMIZOWAC KEYBOARD COMPONENT, NP. POD WZGLEDEM WYGLADU).!!!
// Oczywiscie sama ta implementacja ponizej nie jest gotowa do wykorzystania, chodzi tylko o sens.
// 
// 
// 
// 
// 
//#include<JuceHeader.h>
//
//class CustomMidiKeyboardComponent : public juce::MidiKeyboardComponent
//{
//public:
//    CustomMidiKeyboardComponent(juce::MidiKeyboardState& state, Orientation orientation)
//        : juce::MidiKeyboardComponent(state, orientation) {}
//
//    void drawWhiteNote(int midiNoteNumber, juce::Graphics& g, juce::Rectangle<float> area,
//        bool isDown, bool isOver, juce::Colour lineColour, juce::Colour textColour) override
//    {
//        // Adjust the area to make the keys thinner (less height) and wider (more width)
//        area = area.withSizeKeepingCentre(area.getWidth() + 20.0f, area.getHeight() - 10.0f);
//
//        // Draw the key background
//        g.setColour(isDown ? juce::Colours::orange : juce::Colours::white);
//        g.fillRect(area);
//
//        // Draw the border
//        g.setColour(isOver ? juce::Colours::yellow : lineColour);
//        g.drawRect(area, 1.0f);
//
//        // Optionally, draw the note name
//        if (isDown)
//        {
//            g.setColour(textColour);
//            g.drawText(juce::MidiMessage::getMidiNoteName(midiNoteNumber, true, true, 3),
//                area.reduced(2.0f), juce::Justification::centred);
//        }
//    }
//
//    void drawBlackNote(int midiNoteNumber, juce::Graphics& g, juce::Rectangle<float> area,
//        bool isDown, bool isOver, juce::Colour noteFillColour) override
//    {
//        // Adjust the area to make the black keys thinner and wider
//        area = area.withSizeKeepingCentre(area.getWidth() + 15.0f, area.getHeight() - 8.0f);
//
//        // Draw the key background
//        g.setColour(isDown ? juce::Colours::orange : noteFillColour);
//        g.fillRect(area);
//
//        // Draw the border
//        g.setColour(isOver ? juce::Colours::yellow : juce::Colours::black);
//        g.drawRect(area, 1.0f);
//    }
//};
//
//
//
//
