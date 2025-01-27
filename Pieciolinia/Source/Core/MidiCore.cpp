#include "MidiCore.h"
#include "MidiDeviceList.h"
#include "MidiDeviceListEntry.h"
#include "MidiDeviceListBox.h"
#include "SettingsWindow.h"
#include "../Common/Mappers.h"
#include "../Common/Note.h"

//Ctors/Dtors (Constructors/Destructors):
MidiCore::MidiCore(MidiDeviceList& midiDeviceList)
    : _midiDeviceList(midiDeviceList),
    midiKeyboard(midiKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{    
    element1.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(element1);

    saveButton = std::make_unique<juce::DrawableButton>("SaveButton", juce::DrawableButton::ImageFitted);


    auto saveImage = std::make_unique<juce::DrawableImage>(
        juce::ImageCache::getFromMemory(BinaryData::icons8savefile66_png, BinaryData::icons8savefile66_pngSize)
    );

    saveButton->setImages(saveImage.get());

#pragma region Buttons
    // Arrow Down Button
    arrowDownButton = std::make_unique<juce::DrawableButton>("ArrowDownButton", juce::DrawableButton::ImageFitted);
    auto arrowDownImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8arrowdown50_png, BinaryData::icons8arrowdown50_pngSize));
    arrowDownButton->setImages(arrowDownImage.get());
    element33.addAndMakeVisible(arrowDownButton.get());
	arrowDownButton->onClick = [this] {ArrowDownClick(); };

    // Arrow Up Button
    arrowUpButton = std::make_unique<juce::DrawableButton>("ArrowUpButton", juce::DrawableButton::ImageFitted);
    auto arrowUpImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8arrowup50_png, BinaryData::icons8arrowup50_pngSize));
    arrowUpButton->setImages(arrowUpImage.get());
    element22.addAndMakeVisible(arrowUpButton.get());
    arrowUpButton->onClick = [this] {ArrowUpClick(); };

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
	pauseButton->onClick = [this] { pausePlayback(); };

    // Play Button
    playButton = std::make_unique<juce::DrawableButton>("PlayButton", juce::DrawableButton::ImageFitted);
    auto playImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8play50_png, BinaryData::icons8play50_pngSize));
    playButton->setImages(playImage.get());
    element6.addAndMakeVisible(playButton.get());
	playButton->onClick = [this] { startPlayback(); };

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
	stopButton->onClick = [this] { stopPlayback(); };

    // Logo Button
    logoButton = std::make_unique<juce::DrawableButton>("LogoButton", juce::DrawableButton::ImageFitted);
    auto logoImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8logo50_png, BinaryData::icons8logo50_pngSize));
    logoImage->setTransform(juce::AffineTransform::scale(4.0f));
    logoButton->setImages(logoImage.get());
    element1.addAndMakeVisible(logoButton.get());

    // Verified Button
    verifyButton = std::make_unique<juce::DrawableButton>("verifyButton", juce::DrawableButton::ImageFitted);
    auto verifyImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8verified50_png, BinaryData::icons8verified50_pngSize));
    verifyButton->setImages(verifyImage.get());
    element5.addAndMakeVisible(verifyButton.get());


    // Staff Button
    staffButton = std::make_unique<juce::DrawableButton>("staffButton", juce::DrawableButton::ImageFitted);
    auto staffImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8staff50_png, BinaryData::icons8staff50_pngSize));
    staffButton->setImages(staffImage.get());
    element11.addAndMakeVisible(staffButton.get());

    // C Button
    cButton = std::make_unique<juce::DrawableButton>("cButton", juce::DrawableButton::ImageFitted);
    auto cImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::cnote_png, BinaryData::cnote_pngSize));
    cButton->setImages(cImage.get());
    element88.addAndMakeVisible(cButton.get());
	cButton->onClick = [this] { AddNoteByButton(Note::NoteLength::Whole); };
    // D Button
    dButton = std::make_unique<juce::DrawableButton>("dButton", juce::DrawableButton::ImageFitted);
    auto dImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::dnote_png, BinaryData::dnote_pngSize));
    dButton->setImages(dImage.get());
    element99.addAndMakeVisible(dButton.get());

    // E Button
    eButton = std::make_unique<juce::DrawableButton>("eButton", juce::DrawableButton::ImageFitted);
    auto eImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::enote_png, BinaryData::enote_pngSize));
    eButton->setImages(eImage.get());
    element111.addAndMakeVisible(eButton.get());
	eButton->onClick = [this] { AddNoteByButton(Note::NoteLength::Half); };

    // F Button
    fButton = std::make_unique<juce::DrawableButton>("fButton", juce::DrawableButton::ImageFitted);
    auto fImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::fnote_png, BinaryData::fnote_pngSize));
    fButton->setImages(fImage.get());
    element222.addAndMakeVisible(fButton.get());

    // G Button
    gButton = std::make_unique<juce::DrawableButton>("gButton", juce::DrawableButton::ImageFitted);
    auto gImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::gnote_png, BinaryData::gnote_pngSize));
    gButton->setImages(gImage.get());
    element333.addAndMakeVisible(gButton.get());
	gButton->onClick = [this] { AddNoteByButton(Note::NoteLength::Quarter); };

    // A Button
    aButton = std::make_unique<juce::DrawableButton>("aButton", juce::DrawableButton::ImageFitted);
    auto aImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::anote_png, BinaryData::anote_pngSize));
    aButton->setImages(aImage.get());
    element444.addAndMakeVisible(aButton.get());

    // B Button
    bButton = std::make_unique<juce::DrawableButton>("bButton", juce::DrawableButton::ImageFitted);
    auto bImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::Bnote_png, BinaryData::Bnote_pngSize));
    bButton->setImages(bImage.get());
    element555.addAndMakeVisible(bButton.get());
	bButton->onClick = [this] { AddNoteByButton(Note::NoteLength::Eighth); };

    // C2 Button
    c2Button = std::make_unique<juce::DrawableButton>("c2Button", juce::DrawableButton::ImageFitted);
    auto c2Image = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::c2note_png, BinaryData::c2note_pngSize));
    c2Button->setImages(c2Image.get());
    element666.addAndMakeVisible(c2Button.get());

    // D2 Button
    d2Button = std::make_unique<juce::DrawableButton>("d2Button", juce::DrawableButton::ImageFitted);
    auto d2Image = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::d2note_png, BinaryData::d2note_pngSize));
    d2Button->setImages(d2Image.get());
    element66.addAndMakeVisible(d2Button.get());
	d2Button->onClick = [this] { AddNoteByButton(Note::NoteLength::Sixteenth); };

    // E2 Button
    e2Button = std::make_unique<juce::DrawableButton>("e2Button", juce::DrawableButton::ImageFitted);
    auto e2Image = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::e2note_png, BinaryData::e2note_pngSize));
    e2Button->setImages(e2Image.get());
    element77.addAndMakeVisible(e2Button.get());
#pragma endregion

    element2.addAndMakeVisible(saveButton.get());

    folderButton = std::make_unique<juce::DrawableButton>("FolderButton", juce::DrawableButton::ImageFitted);

    auto folderImage = std::make_unique<juce::DrawableImage>(
        juce::ImageCache::getFromMemory(BinaryData::icons8folder50_png, BinaryData::icons8folder50_pngSize)
    );
    folderButton->setImages(folderImage.get());

#pragma region elements


    element3.addAndMakeVisible(folderButton.get());

    element2.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(element2);

    element3.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82)); 
    addAndMakeVisible(element3);

   

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



    element22.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element22);

    element33.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element33);

    element44.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element44);

    element55.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element55);

  

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

    element66.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element66);

    element77.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(element77);

#pragma endregion
    settingsButton->onClick = [this] { showSettingsWindow(); };

    midiKeyboard.setName(MidiKeyboardConstants::midiKeyboardName);
    midiKeyboard.setAvailableRange(72, 91); //Jak chcecie obciac sobie pianino (warto zaznaczyc, ze wtedy i tak z klawiatury mozna grac te nie wyswietlone przyciski, wiec trzeba bedzie sie tym zajac!).
    //addAndMakeVisible(midiKeyboard);

    //addAndMakeVisible(midiOutputSelector.get());

    midiKeyboardState.addListener(this);

    auto typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::MusiQwikPieciolinia_ttf, BinaryData::MusiQwikPieciolinia_ttfSize);
    juce::Font customFont(typeface);
    customFont.setHeight(128.0f);

    textEditorForNotesTest.setMultiLine(true);
    textEditorForNotesTest.setReturnKeyStartsNewLine(true);
    textEditorForNotesTest.setReadOnly(true);        
    textEditorForNotesTest.applyFontToAllText(customFont);
    textEditorForNotesTest.setBounds(0, 0, 1300, 450);
	textEditorForNotesTest.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xFFE4E6D9));
	textEditorForNotesTest.setColour(juce::TextEditor::textColourId, juce::Colours::black);


    switchNoteEditor = std::make_unique<juce::TextEditor>();
    switchNoteEditor->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xFFE4E6D9));
    switchNoteEditor->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    switchNoteEditor->setColour(juce::TextEditor::outlineColourId, juce::Colours::grey);
    switchNoteEditor->setJustification(juce::Justification::centred);
    switchNoteEditor->setEnabled(false);
    switchNoteEditor->setReadOnly(true);
    switchNoteEditor->applyFontToAllText(customFont);
	switchNoteEditor->setText("000;000");
    


    addAndMakeVisible(*switchNoteEditor);


    nameSongEditor = std::make_unique<juce::TextEditor>();
    nameSongEditor->setMultiLine(false);
    nameSongEditor->setReturnKeyStartsNewLine(false);
    nameSongEditor->setFont(juce::Font(35.0f));
    nameSongEditor->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xFFE4E6D9));
    nameSongEditor->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    nameSongEditor->setColour(juce::TextEditor::outlineColourId, juce::Colours::grey);
    nameSongEditor->setJustification(juce::Justification::centred);
    nameSongEditor->setInputRestrictions(50);

    addAndMakeVisible(*nameSongEditor);


    orangeContent.addAndMakeVisible(textEditorForNotesTest);
    midiKeyboardState.addListener(this);

    setSize(1300, 750);
}

MidiCore::~MidiCore()
{
    if (settingsWindow != nullptr) 
    {
        settingsWindow->removeChangeListener(this);
        settingsWindow.deleteAndZero();
    }
    stopPlayback(); // Upewniamy się, że wątek jest zakończony przy destrukcji obiektu
    if (playbackThread.joinable()) {
        playbackThread.join();
    }
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
    auto currentNote = std::make_unique<Note>();
    currentNote->setNoteInfo(elapsed, 120, midiNoteNumber);
    addText(textEditorForNotesTest, currentNote->getNoteFont());
    CompositionConstants::notes.push_back(std::move(currentNote));
}

void MidiCore::addText(juce::TextEditor& editor, const juce::String& text)
{
    editor.setCaretPosition(editor.getText().length()); // Move caret to the end
    editor.insertTextAtCaret(text); // Insert new text
}

void MidiCore::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == settingsWindow)
    {
        settingsWindow->removeChangeListener(this);
        settingsButton->setEnabled(true);
    }
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
    logoButton->setBounds(-50, -50,300,200); // Powiększamy przycisk


    saveButton->setBounds(element2.getLocalBounds().reduced(10));
    staffButton->setBounds(element11.getLocalBounds().reduced(10));


    element2.setBounds(headerArea.removeFromLeft(sectionWidth));

    folderButton -> setBounds(element3.getLocalBounds().reduced(10));
    element3.setBounds(headerArea.removeFromLeft(sectionWidth));
    nameSongEditor->setBounds(headerArea.removeFromLeft(bigsection));
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

    switchNoteEditor->setBounds(footerArea.removeFromLeft(mediumSectionWidth));

    juce::Rectangle<int> firstColumn = footerArea.removeFromLeft(smallSectionWidth); // Kopia prostokąta dla prawej kolumny
    int smallColumnHeight = footerHeight / 2;

    element22.setBounds(firstColumn.removeFromTop(smallColumnHeight));
    element33.setBounds(firstColumn);
    arrowUpButton->setBounds(element22.getLocalBounds().reduced(10));
    arrowDownButton->setBounds(element33.getLocalBounds().reduced(10));

    element44.setBounds(footerArea.removeFromLeft(mediumSectionWidth));
    backspaceButton->setBounds(element44.getLocalBounds().reduced(10));
    element55.setBounds(footerArea.removeFromLeft(bigSectionWidth));

    juce::Rectangle<int> thirdColumn = footerArea.removeFromLeft(smallSectionWidth);
    element88.setBounds(thirdColumn.removeFromTop(smallColumnHeight));
    cButton->setBounds(element88.getLocalBounds().reduced(10));
    element99.setBounds(thirdColumn);
    dButton->setBounds(element88.getLocalBounds().reduced(10));
    juce::Rectangle<int> fourthColumn = footerArea.removeFromLeft(smallSectionWidth);
    element111.setBounds(fourthColumn.removeFromTop(smallColumnHeight));
    eButton->setBounds(element88.getLocalBounds().reduced(10));
    element222.setBounds(fourthColumn);
    fButton->setBounds(element88.getLocalBounds().reduced(10));
    juce::Rectangle<int> fifthColumn = footerArea.removeFromLeft(smallSectionWidth);
    element333.setBounds(fifthColumn.removeFromTop(smallColumnHeight));
    gButton->setBounds(element88.getLocalBounds().reduced(10));
    element444.setBounds(fifthColumn);

    juce::Rectangle<int> sisxthColumn = footerArea.removeFromLeft(smallSectionWidth);
    element555.setBounds(sisxthColumn.removeFromTop(smallColumnHeight));
    aButton->setBounds(element88.getLocalBounds().reduced(10));
    bButton->setBounds(element88.getLocalBounds().reduced(10));
    c2Button->setBounds(element88.getLocalBounds().reduced(10));
    d2Button->setBounds(element88.getLocalBounds().reduced(10));
    e2Button->setBounds(element88.getLocalBounds().reduced(10));
    element666.setBounds(sisxthColumn);
    juce::Rectangle<int> secondColumn = footerArea.removeFromLeft(smallSectionWidth);
    element66.setBounds(secondColumn.removeFromTop(smallColumnHeight));
    element77.setBounds(secondColumn);
    midiKeyboard.setBounds(element55.getLocalBounds());
}



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Custom methods !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//==============================================================================
// PUBLIC MEMBERS
//==============================================================================
void MidiCore::showSettingsWindow()
{
    settingsWindow = new SettingsWindow("Settings", _midiDeviceList);

    settingsWindow->addChangeListener(this);
    settingsButton->setEnabled(false);
}

//==============================================================================
// PRIVATE MEMBERS
//==============================================================================


void MidiCore::sendToOutputs(const juce::MidiMessage& message)
{
    auto midiOutputs = _midiDeviceList.getMidiDevices();
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

void MidiCore::addLabelAndSetStyle(juce::Label& label)
{
    label.setFont(juce::FontOptions(15.00f, juce::Font::plain));
    label.setJustificationType(juce::Justification::centredLeft);
    label.setEditable(false, false, false);
    label.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label);
}

void MidiCore::startPlayback() {
    if (isPlaying)
    {
        if (isPaused)
        {
            isPaused = false;
            pauseCondition.notify_one();
            pauseButton->setEnabled(true);
			playButton->setEnabled(false);
            return;
        }
        return;
    }

    //Checking if a thread is joinable, meaning it can be joined with the calling thread, by verifying that its thread ID is not zero.
	//It is important to join the thread before starting a new one(for example: by starting playing composition second time during the session),
    //otherwise the program will crash.
    if (playbackThread.joinable()) {
        playbackThread.join();
    }

    isPlaying = true;

    playbackThread = std::thread(&MidiCore::playbackWorker, this);

	stopButton->setEnabled(true);
	pauseButton->setEnabled(true);
	playButton->setEnabled(false);
}

void MidiCore::pausePlayback() {
	if (!isPlaying) return;
    isPaused = true;

	playButton->setEnabled(true);
	pauseButton->setEnabled(false);
}

void MidiCore::stopPlayback() {
    isPlaying = false;
    isPaused = false;

    pauseCondition.notify_one();

	stopButton->setEnabled(false);
	pauseButton->setEnabled(false);
	playButton->setEnabled(true);
}

void MidiCore::playbackWorker() {
    auto& notes = CompositionConstants::notes;

    for (size_t i = 0; i < notes.size(); ++i) {
        {
            std::unique_lock<std::mutex> lock(pauseMutex);
            pauseCondition.wait(lock, [this] { return !isPaused || !isPlaying; });

            if (!isPlaying) return;
        }

        auto& note = notes[i];
        int midiNote = NoteMapper::noteToIndex.at(note->info.name);
        juce::MidiMessage onMsg = juce::MidiMessage::noteOn(1, midiNote, 1.0f);
        sendToOutputs(onMsg);

        int noteDurationMs = note->calculateNoteDuration(CompositionConstants::bpm);

        std::this_thread::sleep_for(std::chrono::milliseconds(noteDurationMs));

        juce::MidiMessage offMsg = juce::MidiMessage::noteOff(1, midiNote, 1.0f);
        sendToOutputs(offMsg);
    }

    isPlaying = false;
    juce::MessageManager::callAsync([this] {
        playButton->setEnabled(true);
        pauseButton->setEnabled(false);
        stopButton->setEnabled(false);
        });

}



juce::String MidiCore::setHigherNote(juce::String text)
{
	char note = text[3];
    switch (note)
    {
	case '6':
		chosenNoteName = Note::NoteName::cSharp1;
		return("000r600");
		break;
	case 'r':
		chosenNoteName = Note::NoteName::d1;
        return("0007000");
        break;
	case '7':
		chosenNoteName = Note::NoteName::dSharp1;
		return("000s700");
        break;
	case 's':
		chosenNoteName = Note::NoteName::e1;
		return("0008000");
		break;
	case '8':
		chosenNoteName = Note::NoteName::f1;
		return("0009000");
		break;
	case '9':
		chosenNoteName = Note::NoteName::fSharp1;
		return("000u900");
		break;
	case 'u':
		chosenNoteName = Note::NoteName::g1;
		return("000:000");
    case ':':
		chosenNoteName = Note::NoteName::gSharp1;
		return("000v:00");
		break;
    case 'v':
		chosenNoteName = Note::NoteName::a1;
		return("000;000");
	case ';':
		chosenNoteName = Note::NoteName::aSharp1;
		return("000w;00");
        break;
	case 'w':
		chosenNoteName = Note::NoteName::h1;
        return("000<000");
		break;
	case '<':
		chosenNoteName = Note::NoteName::c2;
		return("000=000");
		break;
	case '=':
		chosenNoteName = Note::NoteName::cSharp2;
		return("000y=00");
		break;
	case 'y':
		chosenNoteName = Note::NoteName::d2;
		return("000>000");
		break;
	case '>':
		chosenNoteName = Note::NoteName::dSharp2;
		return("000z>00");
		break;
	case 'z':
		chosenNoteName = Note::NoteName::e2;
		return("000?000");
		break;
	case '?':
		chosenNoteName = Note::NoteName::f2;
		return("000@000");
		break;
	case '@':
		chosenNoteName = Note::NoteName::fSharp2;
		return("000|@00");
		break;
	case '|':
		chosenNoteName = Note::NoteName::g2;
		return("000A000");
		break;
	case 'A':
		return("000A000");
		break;
    default:
		chosenNoteName = Note::NoteName::a1;
		return("000;000");
        break;
    }
}

juce::String MidiCore::setNoteLower(juce::String text)
{
    char note = text[3];
    switch (note)
    {
    case '6':
        chosenNoteName = Note::NoteName::c1;
        return("000600");
        break;
	case 'r':
		chosenNoteName = Note::NoteName::c1;
		return("000600");
		break;
	case '7':
		chosenNoteName = Note::NoteName::cSharp1;
		return("000r600");
		break;
	case 's':
		chosenNoteName = Note::NoteName::d1;
		return("0007000");
		break;
	case '8':
		chosenNoteName = Note::NoteName::dSharp1;
		return("000s700");
		break;
	case '9':
		chosenNoteName = Note::NoteName::e1;
		return("0008000");
		break;
	case 'u':
		chosenNoteName = Note::NoteName::f1;
		return("0009000");
		break;
	case ':':
		chosenNoteName = Note::NoteName::fSharp1;
		return("000u900");
		break;
	case 'v':
		chosenNoteName = Note::NoteName::g1;
		return("000:000");
		break;
	case ';':
		chosenNoteName = Note::NoteName::gSharp1;
		return("000v:00");
		break;
	case 'w':
		chosenNoteName = Note::NoteName::a1;
		return("000;000");
		break;
	case '<':
		chosenNoteName = Note::NoteName::aSharp1;
		return("000w;00");
		break;
	case '=':
		chosenNoteName = Note::NoteName::h1;
		return("000<000");
		break;
	case 'y':
		chosenNoteName = Note::NoteName::c2;
		return("000=000");
		break;
	case '>':
		chosenNoteName = Note::NoteName::cSharp2;
		return("000y=00");
		break;
	case 'z':
		chosenNoteName = Note::NoteName::d2;
		return("000>000");
		break;
	case '?':
		chosenNoteName = Note::NoteName::dSharp2;
		return("000z>00");
		break;
	case '@':
		chosenNoteName = Note::NoteName::e2;
		return("000?000");
		break;
	case '|':
		chosenNoteName = Note::NoteName::f2;
		return("000@000");
		break;
	case 'A':
		chosenNoteName = Note::NoteName::fSharp2;
		return("000|@00");
		break;
	default:
		chosenNoteName = Note::NoteName::a1;
		return("000;000");
		break;
    }

}

void MidiCore::ArrowUpClick()
{
	switchNoteEditor->setText(setHigherNote(switchNoteEditor->getText()));
}

void MidiCore::ArrowDownClick()
{
	switchNoteEditor->setText(setNoteLower(switchNoteEditor->getText()));
}

void MidiCore::AddNoteByButton(Note::NoteLength noteLength)
{
	auto currentNote = std::make_unique<Note>();
	currentNote->info.length = noteLength;
    currentNote->info.name = chosenNoteName;
	addText(textEditorForNotesTest, currentNote->getNoteFont());
	CompositionConstants::notes.push_back(std::move(currentNote));

    int midiNote = NoteMapper::noteToIndex.at(currentNote->info.name);
    juce::MidiMessage onMsg = juce::MidiMessage::noteOn(1, midiNote, 1.0f);
    sendToOutputs(onMsg);

    int noteDurationMs = currentNote->calculateNoteDuration(CompositionConstants::bpm);

    std::this_thread::sleep_for(std::chrono::milliseconds(noteDurationMs));

    juce::MidiMessage offMsg = juce::MidiMessage::noteOff(1, midiNote, 1.0f);
    sendToOutputs(offMsg);
}