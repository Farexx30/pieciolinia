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

        compositionNotesElement.setColour(juce::TextButton::buttonColourId, juce::Colours::deepskyblue);
        addAndMakeVisible(compositionNotesElement);

        LogoElement.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(LogoElement);

        saveFileElement.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(saveFileElement);

        folderElement.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue); // Light blue for middle
        addAndMakeVisible(folderElement);

        saveCompositionNameElement.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(saveCompositionNameElement);


        arrowUpElement.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
        addAndMakeVisible(arrowUpElement);

        arrowDownElement.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue); // Light blue for middle
        addAndMakeVisible(arrowDownElement);

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
        LogoElement.setBounds(headerArea.removeFromLeft(sectionWidth));
        saveFileElement.setBounds(headerArea.removeFromLeft(sectionWidth));
        folderElement.setBounds(headerArea.removeFromLeft(bigsection));
        saveCompositionNameElement.setBounds(headerArea);

        //footer.setBounds (area.removeFromBottom (headerFooterHeight));

        /*
        auto sidebarWidth = 80;
        sidebar.setBounds (area.removeFromLeft (sidebarWidth)); // [2]
        */
        auto contentItemHeight = 480;
        compositionNotesElement.setBounds(area.removeFromTop(contentItemHeight));

        /*
        auto headerFooterHeight = 60;
        footer.setBounds(area.removeFromBottom(headerFooterHeight));
        */

        auto footerHeight = 220;
        juce::Rectangle<int> footerArea = area.removeFromTop(footerHeight);

        int smallSectionWidth = footerArea.getWidth() / 5;
        int largeSectionWidth = smallSectionWidth * 3;

        // Position sections
        arrowUpElement.setBounds(footerArea.removeFromLeft(largeSectionWidth));
        arrowDownElement.setBounds(footerArea.removeFromLeft(smallSectionWidth));
    }

private:
    juce::TextButton header;
    juce::TextButton sidebar;

    juce::TextButton limeContent;
    juce::TextButton grapefruitContent;
    juce::TextButton lemonContent;
    juce::TextButton compositionNotesElement;
    juce::TextButton footer;
    juce::TextButton LogoElement;
    juce::TextButton saveFileElement;
    juce::TextButton folderElement;
    juce::TextButton saveCompositionNameElement;
    juce::TextButton arrowUpElement;
    juce::TextButton arrowDownElement;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};