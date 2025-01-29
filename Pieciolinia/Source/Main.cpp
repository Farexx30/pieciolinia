#include <JuceHeader.h>
#include "Core/MidiCore.h"
#include "Common/Constants.h"
#include "CssFile.h"
#include "Core/MidiDeviceList.h"
//==============================================================================
class PiecioliniaApplication
    : public juce::JUCEApplication
{
public:
    //==============================================================================
    PiecioliniaApplication() {}

    const juce::String getApplicationName() override { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override { return ProjectInfo::versionString; }

    //==============================================================================
    void initialise(const juce::String&) override
    {
        midiDeviceList = std::make_unique<MidiDeviceList>();
        auto midiCore = new MidiCore(*midiDeviceList);
        mainWindow = std::make_unique<MainWindow>(getApplicationName(), midiCore);
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..
        mainWindow.reset();
        midiDeviceList.reset();
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        quit();
    }

    class MainWindow
        : public juce::DocumentWindow
    {
    public:
        MainWindow(const juce::String& name, MidiCore* midiCore)
            : DocumentWindow(name,
                juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
                DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(midiCore, true);

#if JUCE_IOS || JUCE_ANDROID
            setFullScreen(true);
#else
            setResizable(false, false);
            setResizeLimits(300, 250, 10000, 10000);
            centreWithSize(getWidth(), getHeight());
#endif

            setVisible(true);
        }

        void closeButtonPressed() override
        {         
            JUCEApplication::getInstance()->systemRequestedQuit();
        }


    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
    std::unique_ptr<MidiDeviceList> midiDeviceList;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(PiecioliniaApplication)
