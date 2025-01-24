#include "MidiCore.h"
#include "MidiDeviceListEntry.h"
#include "MidiDeviceListBox.h"


//Ctors/Dtors (Constructors/Destructors):
MidiCore::MidiCore()
    : midiKeyboard(midiKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
    midiOutputSelector(new MidiDeviceListBox(ListBoxConstants::midiOutputSelectorName, *this))
{
    
    element1.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(element1);

    saveButton = std::make_unique<juce::DrawableButton>("SaveButton", juce::DrawableButton::ImageFitted);


    auto saveImage = std::make_unique<juce::DrawableImage>(
        juce::ImageCache::getFromMemory(BinaryData::icons8savefile66_png, BinaryData::icons8savefile66_pngSize)
    );

    saveButton->setImages(saveImage.get());
    // Arrow Down Button
    arrowDownButton = std::make_unique<juce::DrawableButton>("ArrowDownButton", juce::DrawableButton::ImageFitted);
    auto arrowDownImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8arrowdown50_png, BinaryData::icons8arrowdown50_pngSize));
    arrowDownButton->setImages(arrowDownImage.get());
    element33.addAndMakeVisible(arrowDownButton.get());

    // Arrow Up Button
    arrowUpButton = std::make_unique<juce::DrawableButton>("ArrowUpButton", juce::DrawableButton::ImageFitted);
    auto arrowUpImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8arrowup50_png, BinaryData::icons8arrowup50_pngSize));
    arrowUpButton->setImages(arrowUpImage.get());
    element22.addAndMakeVisible(arrowUpButton.get());

    // Backspace Button
    backspaceButton = std::make_unique<juce::DrawableButton>("BackspaceButton", juce::DrawableButton::ImageFitted);
    auto backspaceImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8backspace50_png, BinaryData::icons8backspace50_pngSize));
    backspaceButton->setImages(backspaceImage.get());
    element44.addAndMakeVisible(backspaceButton.get());

    // Pause Button
    pauseButton = std::make_unique<juce::DrawableButton>("PauseButton", juce::DrawableButton::ImageFitted);
    auto pauseImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8pause50_png, BinaryData::icons8pause50_pngSize));
    pauseButton->setImages(pauseImage.get());
    element7.addAndMakeVisible(pauseButton.get());

    // Play Button
    playButton = std::make_unique<juce::DrawableButton>("PlayButton", juce::DrawableButton::ImageFitted);
    auto playImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8play50_png, BinaryData::icons8play50_pngSize));
    playButton->setImages(playImage.get());
    element6.addAndMakeVisible(playButton.get());

    // Settings Button
    settingsButton = std::make_unique<juce::DrawableButton>("SettingsButton", juce::DrawableButton::ImageFitted);
    auto settingsImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8settings50_png, BinaryData::icons8settings50_pngSize));
    settingsButton->setImages(settingsImage.get());
    element9.addAndMakeVisible(settingsButton.get());

    // Stop Button
    stopButton = std::make_unique<juce::DrawableButton>("StopButton", juce::DrawableButton::ImageFitted);
    auto stopImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8stop50_png, BinaryData::icons8stop50_pngSize));
    stopButton->setImages(stopImage.get());
    element8.addAndMakeVisible(stopButton.get());

    // Logo Button
    logoButton = std::make_unique<juce::DrawableButton>("LogoButton", juce::DrawableButton::ImageFitted);
    auto logoImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8logo50_png, BinaryData::icons8logo50_pngSize));
    logoButton->setImages(logoImage.get());
    element1.addAndMakeVisible(logoButton.get());

    // Verified Button
    verifyButton = std::make_unique<juce::DrawableButton>("verifyButton", juce::DrawableButton::ImageFitted);
    auto verifyImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8verified50_png, BinaryData::icons8verified50_pngSize));
    verifyButton->setImages(verifyImage.get());
    element5.addAndMakeVisible(verifyButton.get());

    element2.addAndMakeVisible(saveButton.get());

    folderButton = std::make_unique<juce::DrawableButton>("FolderButton", juce::DrawableButton::ImageFitted);

    auto folderImage = std::make_unique<juce::DrawableImage>(
        juce::ImageCache::getFromMemory(BinaryData::icons8folder50_png, BinaryData::icons8folder50_pngSize)
    );
    folderButton->setImages(folderImage.get());

    element3.addAndMakeVisible(folderButton.get());

    element2.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(element2);

    element3.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82)); 
    addAndMakeVisible(element3);

    element4.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    element4.setButtonText("Nazwa Utworu");
    element4.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    addAndMakeVisible(element4);

    element5.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element5);

    element6.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(element6);

    element7.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(element7);

    element8.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(element8);

    element9.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(element9);


    orangeContent.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(orangeContent);

    

    element11.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element11);

    element22.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element22);

    element33.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element33);

    element44.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element44);

    element55.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element55);

    element66.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element66);


    auto typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::MusiQwikPieciolinia_ttf, BinaryData::MusiQwikPieciolinia_ttfSize);
    juce::Font customFont(typeface);
    customFont.setHeight(100.0f);

    element77.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    element77.setButtonText("B0");
    element77.setFont(juce::Font("NazwaCustomCzcionki", 20.0f, juce::Font::plain));
    addAndMakeVisible(element77);

    element88.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element88);

    element99.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element99);

    element111.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element111);

    element222.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element222);

    element333.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element333);

    element444.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element444);

    element555.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element555);

    element55.addAndMakeVisible(midiKeyboard);

    element666.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element666);


    //addLabelAndSetStyle(midiOutputLabel);

    midiKeyboard.setName(MidiKeyboardConstants::midiKeyboardName);
    midiKeyboard.setAvailableRange(72, 91); //Jak chcecie obciac sobie pianino (warto zaznaczyc, ze wtedy i tak z klawiatury mozna grac te nie wyswietlone przyciski, wiec trzeba bedzie sie tym zajac!).
    //addAndMakeVisible(midiKeyboard);

    //addAndMakeVisible(midiOutputSelector.get());

    midiKeyboardState.addListener(this);

    auto typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::MusiQwikPieciolinia_ttf, BinaryData::MusiQwikPieciolinia_ttfSize);
    juce::Font customFont(typeface);
    customFont.setHeight(100.0f);

    textEditorForNotesTest.setMultiLine(true);
    textEditorForNotesTest.setReturnKeyStartsNewLine(true);
    textEditorForNotesTest.setReadOnly(true);        
    textEditorForNotesTest.applyFontToAllText(customFont);
    textEditorForNotesTest.setBounds(0, 0, 1300, 500);

    orangeContent.addAndMakeVisible(textEditorForNotesTest);
    // Add to the component
    //addAndMakeVisible(textEditorForNotesTest);

    setSize(1300, 750);

    updateDeviceList();
}

MidiCore::~MidiCore()
{
    midiOutputs.clear();
    midiOutputSelector.reset();

    midiKeyboardState.removeListener(this);
}


//Overriden virtual members from juce::MidiKeyboardState::Listener:
//Obsluga klikniecia klawisza pianina:
void MidiCore::handleNoteOn(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    timer.reset(); // start of measuring time
    juce::MidiMessage message(juce::MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity));
    message.setTimeStamp(juce::Time::getMillisecondCounterHiRes() * 0.001); //po prostu zalecana wartosc timestampa dla czystego i precyzyjnego brzmienia, a * 0.001, poniewaz wartosc ta jest okreslana domyslnie w sekundach, a "getMillisecondCounterHiRes()" zwraca wynik w milisekundach.
    sendToOutputs(message);
}

//Obsluga puszczenia klawisza pianina:
void MidiCore::handleNoteOff(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    double elapsed = timer.elapsedMilliseconds(); // Checking Time
    juce::MidiMessage message(juce::MidiMessage::noteOff(midiChannel, midiNoteNumber, velocity));
    message.setTimeStamp(juce::Time::getMillisecondCounterHiRes() * 0.001); //po prostu zalecana wartosc timestampa dla czystego i precyzyjnego brzmienia, a * 0.001, poniewaz wartosc ta jest okreslana domyslnie w sekundach, a "getMillisecondCounterHiRes()" zwraca wynik w milisekundach.
    sendToOutputs(message);
    auto currentNote = new Note();
    currentNote->setNoteInfo(elapsed, 120, midiNoteNumber);
    CompositionConstants::notes.push_back(currentNote);
    addText(textEditorForNotesTest, currentNote->getNoteFont());
}

void MidiCore::addText(juce::TextEditor& editor, const juce::String& text)
{
    editor.setCaretPosition(editor.getText().length()); // Move caret to the end
    editor.insertTextAtCaret(text); // Insert new text
}

//Virtual members from juce::Component:
void MidiCore::paint(juce::Graphics&)
{
    //Empty - nothing to be added.
}

void MidiCore::resized()
{
    auto area = getLocalBounds();

    auto headerHeight = 100;
    juce::Rectangle<int> headerArea = area.removeFromTop(headerHeight);

    // Divide header into 5 equal sections
    int sectionWidth = headerArea.getWidth() / 13;
    int minisection = sectionWidth / 2;
    int bigsection = sectionWidth * 4;
    int mediumbigsection = sectionWidth * 2;

    // Position each section
    element1.setBounds(headerArea.removeFromLeft(mediumbigsection));
    logoButton->setBounds(element1.getLocalBounds().reduced(10));

    saveButton->setBounds(element2.getLocalBounds().reduced(10));


    element2.setBounds(headerArea.removeFromLeft(sectionWidth));

    folderButton -> setBounds(element3.getLocalBounds().reduced(10));
    element3.setBounds(headerArea.removeFromLeft(sectionWidth));
    element4.setBounds(headerArea.removeFromLeft(bigsection));
    element5.setBounds(headerArea.removeFromLeft(sectionWidth));
    verifyButton->setBounds(element5.getLocalBounds().reduced(10));
    element6.setBounds(headerArea.removeFromLeft(sectionWidth));
    playButton->setBounds(element6.getLocalBounds().reduced(10));
    element7.setBounds(headerArea.removeFromLeft(sectionWidth));
    pauseButton->setBounds(element7.getLocalBounds().reduced(10));
    element8.setBounds(headerArea.removeFromLeft(sectionWidth));
    stopButton->setBounds(element8.getLocalBounds().reduced(10));
    element9.setBounds(headerArea.removeFromLeft(sectionWidth));
    settingsButton->setBounds(element9.getLocalBounds().reduced(10));

    auto contentItemHeight = 450;
    orangeContent.setBounds(area.removeFromTop(contentItemHeight));

    /*
    auto headerFooterHeight = 60;
    footer.setBounds(area.removeFromBottom(headerFooterHeight));
    */

    auto footerHeight = 200;
    juce::Rectangle<int> footerArea = area.removeFromTop(footerHeight);

    // Dzielimy obszar na dwie kolumny: małą (lewa) i dużą (prawa)
    int smallSectionWidth = footerArea.getWidth() / 19;

    int mediumSectionWidth = smallSectionWidth * 2;
    int bigSectionWidth = smallSectionWidth * 9;

    element11.setBounds(footerArea.removeFromLeft(mediumSectionWidth));

    juce::Rectangle<int> firstColumn = footerArea.removeFromLeft(smallSectionWidth); // Kopia prostokąta dla prawej kolumny
    int smallColumnHeight = footerHeight / 2;

    element22.setBounds(firstColumn.removeFromTop(smallColumnHeight));
    element33.setBounds(firstColumn);
    arrowUpButton->setBounds(element22.getLocalBounds().reduced(10));
    arrowDownButton->setBounds(element33.getLocalBounds().reduced(10));

    element44.setBounds(footerArea.removeFromLeft(mediumSectionWidth));
    backspaceButton->setBounds(element44.getLocalBounds().reduced(10));
    element55.setBounds(footerArea.removeFromLeft(bigSectionWidth));

    juce::Rectangle<int> secondColumn = footerArea.removeFromLeft(smallSectionWidth); 

    element66.setBounds(secondColumn.removeFromTop(smallColumnHeight));
    element77.setBounds(secondColumn);

    juce::Rectangle<int> thirdColumn = footerArea.removeFromLeft(smallSectionWidth);
    element88.setBounds(thirdColumn.removeFromTop(smallColumnHeight));
    element99.setBounds(thirdColumn);

    juce::Rectangle<int> fourthColumn = footerArea.removeFromLeft(smallSectionWidth);
    element111.setBounds(fourthColumn.removeFromTop(smallColumnHeight));
    element222.setBounds(fourthColumn);
    juce::Rectangle<int> fifthColumn = footerArea.removeFromLeft(smallSectionWidth);
    element333.setBounds(fifthColumn.removeFromTop(smallColumnHeight));
    element444.setBounds(fifthColumn);

    juce::Rectangle<int> sisxthColumn = footerArea.removeFromLeft(smallSectionWidth);
    element555.setBounds(sisxthColumn.removeFromTop(smallColumnHeight));
    element666.setBounds(sisxthColumn);

    midiKeyboard.setBounds(element55.getLocalBounds());

    /*
    int margin = 10, width = getWidth(), height = getHeight();

    midiOutputLabel.setBounds((width / 2) - 5 * margin, margin, (width / 2) - (2 * margin), 24);
    midiOutputSelector->setBounds((width / 4), (2 * margin) + 24,
        (width / 2) - (2 * margin),
        (height / 2) - ((4 * margin) + 24 + 24));

    midiKeyboard.setBounds(width / 2 - 204, (height / 2) + (24 + margin), 612, 256);
    textEditorForNotesTest.setBounds(10, 10, 100, 100);
    */
    //juce::AffineTransform transform = juce::AffineTransform::scale(1.5f, 1.0f); // 1.5x horizontal scale
    //midiKeyboard.setTransform(transform);
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Custom methods !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//==============================================================================
// PUBLIC MEMBERS
//==============================================================================
void MidiCore::openDevice(int index)
{
    midiOutputs[index]->outputDevice = juce::MidiOutput::openDevice(midiOutputs[index]->deviceInfo.identifier);
    if (midiOutputs[index]->outputDevice == nullptr)
    {
        //NOT GOOD:( ERROR - czyli nie udalo sie otworzyc urzadzenia
    }
}

void MidiCore::closeDevice(int index)
{
    midiOutputs[index]->resetDevice();
}

juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> MidiCore::getMidiDevice(int index) const
{
    return midiOutputs[index];
}

int MidiCore::getNumberOfMidiOutputs() const
{
    return midiOutputs.size();
}


//==============================================================================
// PRIVATE MEMBERS
//==============================================================================


void MidiCore::sendToOutputs(const juce::MidiMessage& message)
{
    for (auto* midiOutput : midiOutputs)
    {
        if (auto* outputDevice = midiOutput->outputDevice.get())
        {
            outputDevice->sendMessageNow(message);
        }
        //Powyzszy zapis jest rownoznaczny z tym:
        //if (midiOutput->outputDevice != nullptr)
        //{
        //    midiOutput->outputDevice->sendMessageNow(message);
        //}
    }
}

//Tak naprawde to niepotrzebne teraz, ale ogolnie sprawdza, czy faktycznie lista aktywnych urzadzen rozni sie od tych, ktore aktualnie nasza aplikacja zna - opisane w "updateDeviceList()" dlaczego poki co zbedne.
bool MidiCore::hasDeviceListChanged(const juce::Array<juce::MidiDeviceInfo>& availableDevices)
{
    if (midiOutputs.size() != availableDevices.size())
    {
        return true;
    }

    for (int i = 0; i < availableDevices.size(); ++i)
    {
        if (availableDevices[i] != midiOutputs[i]->deviceInfo)
        {
            return true;
        }
    }

    return false;
}

juce::ReferenceCountedObjectPtr<MidiDeviceListEntry> MidiCore::findDevice(const juce::MidiDeviceInfo& deviceInfo) const
{
    for (auto& device : midiOutputs)
    {
        //Jesli to urzadzenie juz istnieje, to je po prostu zwroc (czyli jesli nie jest nowe):
        if (device->deviceInfo == deviceInfo)
        {
            return device;
        }
    }

    //Jesli jest nowe, to jeszcze go nie znamy, wiec zwracamy nullptr:
    return nullptr;
}

//Zwalnia zasoby odlaczonych juz urzadzen:
void MidiCore::closeUnpluggedDevices(const juce::Array<juce::MidiDeviceInfo>& currentlyPluggedInDevices)
{
    //I ogolnie dlaczego wszedzie "++i" albo "--i" zamiast po prostu "i++" albo "i--"? Poniewaz efekt ten sam, a --i oraz ++i sa minimalnie bardziej wydajne (w internecie opisane dokladniej dlaczego) - choc tak naprawde teraz kompilatory i tak juz czesto optymalizuja uzycie i++ czy i-- aby byly traktowane jak ++i i --i (tak ja przeczytalem i to zrozumialem).
    for (int i = midiOutputs.size(); --i >= 0;) //Zapis ten sam co: for (int i = midiOutputs.size() - 1; i >= 0; --i)
    {
        auto& device = *midiOutputs[i];
        if (!currentlyPluggedInDevices.contains(device.deviceInfo))
        {
            if (device.outputDevice != nullptr)
            {
                closeDevice(i);
            }

            midiOutputs.remove(i);
        }
    }
}

void MidiCore::updateDeviceList()
{
    auto availableDevices = juce::MidiOutput::getAvailableDevices();
    if (hasDeviceListChanged(availableDevices)) //Tak naprawde to u nas ten if nie jest potrzebny, ale jesli mielibysmy tez midiInputs jak w tym MidiDemo i zastosowalibysmy to samo podejscie co oni, to ten if ma juz wtedy sens.
    {
        closeUnpluggedDevices(availableDevices);

        juce::ReferenceCountedArray<MidiDeviceListEntry> newMidiOutputs; //Ogolnie moznaby nie uzywac tymczasowej tablicy/listy i od razu w tym ifie "if (foundDevice == nullptr) {}" dodac nowe urzadzenie do midiOutputs jednakze uzycie tymczasowego pojemnika na dane jest ogolnie "bezpieczniejsze" jesli mielibysmy jeszcze jakies inne kawalki kodu, w ktorych lista ta moglaby zostac w tym samym czasie zmodyfikowana (np. asynchroniczne). U nas co prawda nie ma takich, ale kto wie jak faktyczny projekt bedzie wygladal, a to i tak nie powoduje zadnej zauwazalnej roznicy w wydajnosci.
        for (auto& device : availableDevices)
        {
            MidiDeviceListEntry::Ptr foundDevice = findDevice(device);

            //Jesli to urzadzenie nie jest nam jeszcze znane (czyli jest nowo podlaczone):
            if (foundDevice == nullptr)
            {
                foundDevice = new MidiDeviceListEntry(device);
            }

            newMidiOutputs.add(foundDevice);
        }
        midiOutputs = newMidiOutputs;

        //Update Listboxa:
        midiOutputSelector->syncSelectedItemsWithDeviceList(midiOutputs);
    }
}

void MidiCore::addLabelAndSetStyle(juce::Label& label)
{
    label.setFont(juce::FontOptions(15.00f, juce::Font::plain));
    label.setJustificationType(juce::Justification::centredLeft);
    label.setEditable(false, false, false);
    label.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label);
}

