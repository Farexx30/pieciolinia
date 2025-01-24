/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             RectangleAdvancedTutorial
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Displays rectangles.

 dependencies:     juce_core, juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics
 exporters:        xcode_mac, vs2019, linux_make, xcode_iphone, androidstudio

 type:             Component
 mainClass:        MainContentComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/

#pragma once
class MainContentComponent : public juce::Component
{
public:
    MainContentComponent()
    {
        header.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        header.setButtonText("Header");
        addAndMakeVisible(header);

        footer.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        footer.setButtonText("Footer");
        addAndMakeVisible(footer);

        sidebar.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        sidebar.setButtonText("Sidebar");
        addAndMakeVisible(sidebar);

        limeContent.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(limeContent);

        grapefruitContent.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(grapefruitContent);

        lemonContent.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(lemonContent);

        orangeContent.setColour(juce::TextButton::buttonColourId, juce::Colours::deepskyblue);
        addAndMakeVisible(orangeContent);

        element1.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(element1);

        element2.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(element2);

        element3.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue); // Light blue for middle
        addAndMakeVisible(element3);

        element4.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(element4);

        element5.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(element5);

        element11.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(element11);

        element22.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(element22);

        element33.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue); // Light blue for middle
        addAndMakeVisible(element33);

        setSize(1300, 750);
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black);
    }

    void resized() override
    {
        auto area = getLocalBounds();

        auto headerHeight = 100;
        juce::Rectangle<int> headerArea = area.removeFromTop(headerHeight);

        // Divide header into 5 equal sections
        int sectionWidth = headerArea.getWidth() / 6;
        int minisection = sectionWidth / 2;
        int bigsection = sectionWidth * 2;

        // Position each section
        element1.setBounds(headerArea.removeFromLeft(sectionWidth));
        element2.setBounds(headerArea.removeFromLeft(sectionWidth));
        element3.setBounds(headerArea.removeFromLeft(bigsection));
        element4.setBounds(headerArea.removeFromLeft(sectionWidth));
        element5.setBounds(headerArea);

        //footer.setBounds (area.removeFromBottom (headerFooterHeight));

        /*
        auto sidebarWidth = 80;
        sidebar.setBounds (area.removeFromLeft (sidebarWidth)); // [2]
        */
        auto contentItemHeight = 480;
        orangeContent.setBounds(area.removeFromTop(contentItemHeight));

        /*
        auto headerFooterHeight = 60;
        footer.setBounds(area.removeFromBottom(headerFooterHeight));
        */

        auto footerHeight = 220;
        juce::Rectangle<int> footerArea = area.removeFromTop(footerHeight);

        int smallSectionWidth = footerArea.getWidth() / 5;
        int largeSectionWidth = smallSectionWidth * 3;

        // Position sections
        element11.setBounds(footerArea.removeFromLeft(smallSectionWidth));
        element22.setBounds(footerArea.removeFromLeft(largeSectionWidth));
        element33.setBounds(footerArea.removeFromLeft(smallSectionWidth));
    }

private:
    juce::TextButton header;
    juce::TextButton sidebar;

    juce::TextButton limeContent;
    juce::TextButton grapefruitContent;
    juce::TextButton lemonContent;
    juce::TextButton orangeContent;
    juce::TextButton footer;
    juce::TextButton element1;
    juce::TextButton element2;
    juce::TextButton element3;
    juce::TextButton element4;
    juce::TextButton element5;
    juce::TextButton element11;
    juce::TextButton element22;
    juce::TextButton element33;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};