#include "MidiCore.h"
#include "MidiDeviceList.h"
#include "MidiDeviceListEntry.h"
#include "MidiDeviceListBox.h"
#include "SettingsWindow.h"
#include "../Common/Mappers.h"
#include "../Common/Note.h"

//==============================================================================
// PUBLIC MEMBERS
//==============================================================================

//Ctors/Dtors (Constructors/Destructors):
MidiCore::MidiCore(MidiDeviceList& midiDeviceList)
    : _midiDeviceList(midiDeviceList),
    midiKeyboard(midiKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{    

    // --- Midi keyboard ---
    midiKeyboardElement.addAndMakeVisible(midiKeyboard);
    midiKeyboardElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(midiKeyboardElement);
    midiKeyboard.setName(MidiKeyboardConstants::midiKeyboardName);
    midiKeyboard.setAvailableRange(72, 91);
    midiKeyboardState.addListener(this);


#pragma region Buttons

    // --- Notes management buttons --- 
    arrowDownButton = std::make_unique<juce::DrawableButton>("ArrowDownButton", juce::DrawableButton::ImageFitted);
    auto arrowDownImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8arrowdown50_png, BinaryData::icons8arrowdown50_pngSize));
    arrowDownButton->setImages(arrowDownImage.get());
    arrowDownElement.addAndMakeVisible(arrowDownButton.get());
    arrowDownButton->onClick = [this] {arrowDownClick(); };
    
    arrowDownElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(arrowDownElement);
  

    arrowUpButton = std::make_unique<juce::DrawableButton>("ArrowUpButton", juce::DrawableButton::ImageFitted);
    auto arrowUpImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8arrowup50_png, BinaryData::icons8arrowup50_pngSize));
    arrowUpButton->setImages(arrowUpImage.get());
    arrowUpElement.addAndMakeVisible(arrowUpButton.get());
    arrowUpButton->onClick = [this] {arrowUpClick(); };

    arrowUpElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(arrowUpElement);


    backspaceButton = std::make_unique<juce::DrawableButton>("BackspaceButton", juce::DrawableButton::ImageFitted);
    auto backspaceImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8backspace50_png, BinaryData::icons8backspace50_pngSize));
    backspaceButton->setImages(backspaceImage.get());
    backspaceElement.addAndMakeVisible(backspaceButton.get());
    backspaceButton->onClick = [this] {deleteLastNote(); };

    backspaceElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(backspaceElement);




    // --- Playback buttons ---
    pauseButton = std::make_unique<juce::DrawableButton>("PauseButton", juce::DrawableButton::ImageFitted);
    auto pauseImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8pause50_png, BinaryData::icons8pause50_pngSize));
    pauseButton->setImages(pauseImage.get());
    pauseButton->setEnabled(false);
    pauseElement.addAndMakeVisible(pauseButton.get());
    pauseButton->onClick = [this] { pausePlayback(); };

    pauseElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(pauseElement);


    playButton = std::make_unique<juce::DrawableButton>("PlayButton", juce::DrawableButton::ImageFitted);
    auto playImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8play50_png, BinaryData::icons8play50_pngSize));
    playButton->setImages(playImage.get());
    playElement.addAndMakeVisible(playButton.get());
    playButton->onClick = [this] { startPlayback(); };

    playElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(playElement);


    stopButton = std::make_unique<juce::DrawableButton>("StopButton", juce::DrawableButton::ImageFitted);
    auto stopImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8stop50_png, BinaryData::icons8stop50_pngSize));
    stopButton->setImages(stopImage.get());
    stopButton->setEnabled(false);
    stopElement.addAndMakeVisible(stopButton.get());
    stopButton->onClick = [this] { stopPlayback(); };

    stopElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(stopElement);




    // --- Settings and file management ---
    settingsButton = std::make_unique<juce::DrawableButton>("SettingsButton", juce::DrawableButton::ImageFitted);
    auto settingsImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8settings50_png, BinaryData::icons8settings50_pngSize));
    settingsButton->setImages(settingsImage.get());
    settingsElement.addAndMakeVisible(settingsButton.get());
    settingsButton->onClick = [this] { showSettingsWindow(); };

    settingsElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(settingsElement);

    
    saveCompositionNameButton = std::make_unique<juce::DrawableButton>("saveCompositionNameButton", juce::DrawableButton::ImageFitted);
    auto verifyImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8verified50_png, BinaryData::icons8verified50_pngSize));
    saveCompositionNameButton->setImages(verifyImage.get());
    saveCompositionNameElement.addAndMakeVisible(saveCompositionNameButton.get());

    saveCompositionNameElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(saveCompositionNameElement);


    saveFileButton = std::make_unique<juce::DrawableButton>("saveFileButton", juce::DrawableButton::ImageFitted);
    auto saveImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8savefile66_png, BinaryData::icons8savefile66_pngSize));
    saveFileButton->setImages(saveImage.get());
    saveFileElement.addAndMakeVisible(saveFileButton.get());

    saveFileElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(saveFileElement);


    folderButton = std::make_unique<juce::DrawableButton>("FolderButton", juce::DrawableButton::ImageFitted);
    auto folderImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8folder50_png, BinaryData::icons8folder50_pngSize));
    folderButton->setImages(folderImage.get());
    folderElement.addAndMakeVisible(folderButton.get());

    folderElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(folderElement);




    // --- Other ---
    logoButton = std::make_unique<juce::DrawableButton>("LogoButton", juce::DrawableButton::ImageFitted);
    auto logoImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::icons8logo50_png, BinaryData::icons8logo50_pngSize));
    logoImage->setTransform(juce::AffineTransform::scale(4.0f));
    logoButton->setImages(logoImage.get());
    logoButton->setToggleable(false);
    LogoElement.addAndMakeVisible(logoButton.get());
    
    LogoElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0CF82));
    addAndMakeVisible(LogoElement);



    // --- Notes ---
    wholeNoteButton = std::make_unique<juce::DrawableButton>("wholeNoteButton", juce::DrawableButton::ImageFitted);
    auto cImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::cnote_png, BinaryData::cnote_pngSize));
    wholeNoteButton->setImages(cImage.get());
    wholeNoteElement.addAndMakeVisible(wholeNoteButton.get());
	wholeNoteButton->onClick = [this] { addNoteByButton(Note::NoteLength::Whole); };

    wholeNoteElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(wholeNoteElement);


    wholeNoteRestButton = std::make_unique<juce::DrawableButton>("wholeNoteRestButton", juce::DrawableButton::ImageFitted);
    auto dImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::dnote_png, BinaryData::dnote_pngSize));
    wholeNoteRestButton->setImages(dImage.get());
    wholeNoteRestElement.addAndMakeVisible(wholeNoteRestButton.get());
    wholeNoteRestButton->onClick = [this] { addNoteRestByButton(Note::NoteLength::Whole); };

    wholeNoteRestElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(wholeNoteRestElement);


    halfNoteButton = std::make_unique<juce::DrawableButton>("halfNoteButton", juce::DrawableButton::ImageFitted);
    auto eImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::enote_png, BinaryData::enote_pngSize));
    halfNoteButton->setImages(eImage.get());
    halfNoteElement.addAndMakeVisible(halfNoteButton.get());
	halfNoteButton->onClick = [this] { addNoteByButton(Note::NoteLength::Half); };

    halfNoteElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(halfNoteElement);


    halfNoteRestButton = std::make_unique<juce::DrawableButton>("halfNoteRestButton", juce::DrawableButton::ImageFitted);
    auto fImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::fnote_png, BinaryData::fnote_pngSize));
    halfNoteRestButton->setImages(fImage.get());
    halfNoteRestElement.addAndMakeVisible(halfNoteRestButton.get());
    halfNoteRestButton->onClick = [this] { addNoteRestByButton(Note::NoteLength::Half); };

    halfNoteRestElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(halfNoteRestElement);


    quarterNoteButton = std::make_unique<juce::DrawableButton>("quarterNoteButton", juce::DrawableButton::ImageFitted);
    auto gImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::gnote_png, BinaryData::gnote_pngSize));
    quarterNoteButton->setImages(gImage.get());
    quarterNoteElement.addAndMakeVisible(quarterNoteButton.get());
    quarterNoteButton->onClick = [this] { addNoteByButton(Note::NoteLength::Quarter); };

    quarterNoteElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(quarterNoteElement);


    quarterNoteRestButton = std::make_unique<juce::DrawableButton>("quarterNoteRestButton", juce::DrawableButton::ImageFitted);
    auto aImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::anote_png, BinaryData::anote_pngSize));
    quarterNoteRestButton->setImages(aImage.get());
    quarterNoteRestElement.addAndMakeVisible(quarterNoteRestButton.get());
    quarterNoteRestButton->onClick = [this] { addNoteRestByButton(Note::NoteLength::Quarter); };
    
    quarterNoteRestElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(quarterNoteRestElement);


    eighthNoteButton = std::make_unique<juce::DrawableButton>("eighthNoteButton", juce::DrawableButton::ImageFitted);
    auto bImage = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::Bnote_png, BinaryData::Bnote_pngSize));
    eighthNoteButton->setImages(bImage.get());
    eighthNoteElement.addAndMakeVisible(eighthNoteButton.get());
	eighthNoteButton->onClick = [this] { addNoteByButton(Note::NoteLength::Eighth); };
    
    eighthNoteElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(eighthNoteElement);


    eighthNoteRestButton = std::make_unique<juce::DrawableButton>("eighthNoteRestButton", juce::DrawableButton::ImageFitted);
    auto c2Image = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::c2note_png, BinaryData::c2note_pngSize));
    eighthNoteRestButton->setImages(c2Image.get());
    eighthNoteRestElement.addAndMakeVisible(eighthNoteRestButton.get());
    eighthNoteRestButton->onClick = [this] { addNoteRestByButton(Note::NoteLength::Eighth); };
    
    eighthNoteRestElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(eighthNoteRestElement);


    sixteenthNoteButton = std::make_unique<juce::DrawableButton>("sixteenthNoteButton", juce::DrawableButton::ImageFitted);
    auto d2Image = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::d2note_png, BinaryData::d2note_pngSize));
    sixteenthNoteButton->setImages(d2Image.get());
    sixteenthNoteElement.addAndMakeVisible(sixteenthNoteButton.get());
	sixteenthNoteButton->onClick = [this] { addNoteByButton(Note::NoteLength::Sixteenth); };

    sixteenthNoteElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(sixteenthNoteElement);


    sixteenthNoteRestButton = std::make_unique<juce::DrawableButton>("sixteenthNoteRestButton", juce::DrawableButton::ImageFitted);
    auto e2Image = std::make_unique<juce::DrawableImage>(juce::ImageCache::getFromMemory(BinaryData::e2note_png, BinaryData::e2note_pngSize));
    sixteenthNoteRestButton->setImages(e2Image.get());
    sixteenthNoteRestElement.addAndMakeVisible(sixteenthNoteRestButton.get());
    sixteenthNoteRestButton->onClick = [this] { addNoteRestByButton(Note::NoteLength::Sixteenth); };

    sixteenthNoteRestElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(sixteenthNoteRestElement);
#pragma endregion



#pragma region Text editors
    // --- Custom font --
    auto typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::PiecioliniaMusiQwik_ttf, BinaryData::PiecioliniaMusiQwik_ttfSize);
    juce::Font notesFont(typeface);
    notesFont.setHeight(128.0f);

    // --- Text editors ---
    compositionNotesTextEditor.setMultiLine(true);
    compositionNotesTextEditor.setReturnKeyStartsNewLine(true);
    compositionNotesTextEditor.setReadOnly(true);        
    compositionNotesTextEditor.applyFontToAllText(notesFont);
    compositionNotesTextEditor.setBounds(0, 0, 1300, 450);
	compositionNotesTextEditor.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xFFE4E6D9));
	compositionNotesTextEditor.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    
    compositionNotesElement.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE4E6D9));
    addAndMakeVisible(compositionNotesElement);

    compositionNotesElement.addAndMakeVisible(compositionNotesTextEditor);

    switchNoteTextEditor = std::make_unique<juce::TextEditor>();
    switchNoteTextEditor->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xFFE4E6D9));
    switchNoteTextEditor->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    switchNoteTextEditor->setColour(juce::TextEditor::outlineColourId, juce::Colours::grey);
    switchNoteTextEditor->setJustification(juce::Justification::centred);
    switchNoteTextEditor->setEnabled(false);
    switchNoteTextEditor->setReadOnly(true);
    switchNoteTextEditor->applyFontToAllText(notesFont);
	switchNoteTextEditor->setText("000;000");
    addAndMakeVisible(*switchNoteTextEditor);


    nameSongTextEditor = std::make_unique<juce::TextEditor>();
    nameSongTextEditor->setMultiLine(false);
    nameSongTextEditor->setReturnKeyStartsNewLine(false);
    nameSongTextEditor->setFont(juce::Font(35.0f));
    nameSongTextEditor->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xFFE4E6D9));
    nameSongTextEditor->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    nameSongTextEditor->setColour(juce::TextEditor::outlineColourId, juce::Colours::grey);
    nameSongTextEditor->setJustification(juce::Justification::centred);
    nameSongTextEditor->setInputRestrictions(50);
    addAndMakeVisible(*nameSongTextEditor);
#pragma endregion

	saveFileButton->onClick = [this] { saveToFile(); };
	folderButton->onClick = [this] { readFromFile(); };

    setSize(1301, 751);
    setSize(1300, 750);
}

MidiCore::~MidiCore()
{
    if (settingsWindow != nullptr) 
    {
        settingsWindow->removeChangeListener(this);
        settingsWindow.deleteAndZero();
    }

    stopPlayback(); 
    if (playbackThread.joinable()) {
        playbackThread.join();
    }

    midiKeyboardState.removeListener(this);
}



//Overriden virtual members from juce::MidiKeyboardState::Listener:
void MidiCore::handleNoteOn(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    if (!isKeyboardLocked)
    {
        timer.reset(); // Start of measuring time
        juce::MidiMessage message(juce::MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity));
        message.setTimeStamp(juce::Time::getMillisecondCounterHiRes() * 0.001);//TODO: change comment //po prostu zalecana wartosc timestampa dla czystego i precyzyjnego brzmienia, a * 0.001, poniewaz wartosc ta jest okreslana domyslnie w sekundach, a "getMillisecondCounterHiRes()" zwraca wynik w milisekundach.
        sendToOutputs(message);
    }
}

void MidiCore::handleNoteOff(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    if (!isKeyboardLocked)
    {
        double elapsed = timer.elapsedMilliseconds(); // Checking Time
        juce::MidiMessage message(juce::MidiMessage::noteOff(midiChannel, midiNoteNumber, velocity));
        message.setTimeStamp(juce::Time::getMillisecondCounterHiRes() * 0.001);//TODO: change comment //po prostu zalecana wartosc timestampa dla czystego i precyzyjnego brzmienia, a * 0.001, poniewaz wartosc ta jest okreslana domyslnie w sekundach, a "getMillisecondCounterHiRes()" zwraca wynik w milisekundach.
        sendToOutputs(message);
        auto currentNote = std::make_unique<Note>();
        currentNote->setNoteInfo(elapsed, 120, midiNoteNumber);
        addText(compositionNotesTextEditor, currentNote->getNoteFont());
        CompositionConstants::notes.push_back(std::move(currentNote));
    }
}


void MidiCore::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == settingsWindow)
    {
        settingsWindow->removeChangeListener(this);
        settingsButton->setEnabled(true);
    }
}

//TODO: Delete?
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
    LogoElement.setBounds(headerArea.removeFromLeft(mediumbigsection));
    logoButton->setBounds(-50, -50,300,200); 

    saveFileButton->setBounds(saveFileElement.getLocalBounds().reduced(10));
    saveFileElement.setBounds(headerArea.removeFromLeft(sectionWidth));

    folderButton -> setBounds(folderElement.getLocalBounds().reduced(10));
    folderElement.setBounds(headerArea.removeFromLeft(sectionWidth));

    nameSongTextEditor->setBounds(headerArea.removeFromLeft(bigsection));

    saveCompositionNameElement.setBounds(headerArea.removeFromLeft(sectionWidth));
    saveCompositionNameButton->setBounds(saveCompositionNameElement.getLocalBounds().reduced(10));

    playButton->setBounds(playElement.getLocalBounds().reduced(10));
    playElement.setBounds(headerArea.removeFromLeft(sectionWidth));

    pauseButton->setBounds(pauseElement.getLocalBounds().reduced(10));
    pauseElement.setBounds(headerArea.removeFromLeft(sectionWidth));

    stopButton->setBounds(stopElement.getLocalBounds().reduced(10));
    stopElement.setBounds(headerArea.removeFromLeft(sectionWidth));

    settingsButton->setBounds(settingsElement.getLocalBounds().reduced(10));
    settingsElement.setBounds(headerArea.removeFromLeft(sectionWidth));

    auto contentItemHeight = 450;
    compositionNotesElement.setBounds(area.removeFromTop(contentItemHeight));

    //TODO: delete?
    /*
    auto headerFooterHeight = 60;
    footer.setBounds(area.removeFromBottom(headerFooterHeight));
    */

    auto footerHeight = 200;
    juce::Rectangle<int> footerArea = area.removeFromTop(footerHeight);

   
    int smallSectionWidth = footerArea.getWidth() / 19;

    int mediumSectionWidth = smallSectionWidth * 2;
    int bigSectionWidth = smallSectionWidth * 9;

    switchNoteTextEditor->setBounds(footerArea.removeFromLeft(mediumSectionWidth));

    juce::Rectangle<int> firstColumn = footerArea.removeFromLeft(smallSectionWidth); // Kopia prostokąta dla prawej kolumny
    int smallColumnHeight = footerHeight / 2;

    arrowUpElement.setBounds(firstColumn.removeFromTop(smallColumnHeight));
    arrowDownElement.setBounds(firstColumn);

    arrowUpButton->setBounds(arrowUpElement.getLocalBounds().reduced(10));
    arrowDownButton->setBounds(arrowDownElement.getLocalBounds().reduced(10));

    backspaceElement.setBounds(footerArea.removeFromLeft(mediumSectionWidth));
    backspaceButton->setBounds(backspaceElement.getLocalBounds().reduced(10));



    midiKeyboard.setBounds(midiKeyboardElement.getLocalBounds());
    midiKeyboardElement.setBounds(footerArea.removeFromLeft(bigSectionWidth));
    juce::Rectangle<int> thirdColumn = footerArea.removeFromLeft(smallSectionWidth);

    wholeNoteElement.setBounds(thirdColumn.removeFromTop(smallColumnHeight));
    wholeNoteButton->setBounds(wholeNoteElement.getLocalBounds().reduced(10));

    wholeNoteRestElement.setBounds(thirdColumn);
    wholeNoteRestButton->setBounds(wholeNoteElement.getLocalBounds().reduced(10));

    juce::Rectangle<int> fourthColumn = footerArea.removeFromLeft(smallSectionWidth);

    halfNoteElement.setBounds(fourthColumn.removeFromTop(smallColumnHeight));
    halfNoteButton->setBounds(wholeNoteElement.getLocalBounds().reduced(10));

    halfNoteRestElement.setBounds(fourthColumn);
    halfNoteRestButton->setBounds(wholeNoteElement.getLocalBounds().reduced(10));

    juce::Rectangle<int> fifthColumn = footerArea.removeFromLeft(smallSectionWidth);

    quarterNoteElement.setBounds(fifthColumn.removeFromTop(smallColumnHeight));
    quarterNoteButton->setBounds(wholeNoteElement.getLocalBounds().reduced(10));

    quarterNoteRestButton->setBounds(wholeNoteElement.getLocalBounds().reduced(10));
    quarterNoteRestElement.setBounds(fifthColumn);

    juce::Rectangle<int> sisxthColumn = footerArea.removeFromLeft(smallSectionWidth);

    eighthNoteElement.setBounds(sisxthColumn.removeFromTop(smallColumnHeight));
    eighthNoteButton->setBounds(wholeNoteElement.getLocalBounds().reduced(10));

    eighthNoteRestButton->setBounds(wholeNoteElement.getLocalBounds().reduced(10));
    eighthNoteRestElement.setBounds(sisxthColumn);


    juce::Rectangle<int> secondColumn = footerArea.removeFromLeft(smallSectionWidth);

    sixteenthNoteButton->setBounds(wholeNoteElement.getLocalBounds().reduced(10));
    sixteenthNoteElement.setBounds(secondColumn.removeFromTop(smallColumnHeight));

    sixteenthNoteRestButton->setBounds(wholeNoteElement.getLocalBounds().reduced(10));
    sixteenthNoteRestElement.setBounds(secondColumn);

}



//==============================================================================
// PRIVATE MEMBERS
//==============================================================================

void MidiCore::showSettingsWindow()
{
    settingsWindow = new SettingsWindow("Settings", _midiDeviceList);

    settingsWindow->addChangeListener(this);
    settingsButton->setEnabled(false);
}

void MidiCore::sendToOutputs(const juce::MidiMessage& message)
{
    auto midiOutputs = _midiDeviceList.getMidiDevices();
    for (auto* midiOutput : midiOutputs)
    {
        if (auto* outputDevice = midiOutput->outputDevice.get())
        {
            outputDevice->sendMessageNow(message);
        }
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

//Method used in composition text editor to add notes
void MidiCore::addText(juce::TextEditor& editor, const juce::String& text)
{
    editor.setCaretPosition(editor.getText().length()); // Move caret to the end
    editor.insertTextAtCaret(text);
}


#pragma region Playback
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
    compositionNotesTextEditor.setCaretPosition(0);
    stopButton->setEnabled(true);
    pauseButton->setEnabled(true);
    playButton->setEnabled(false);

    lockInputs();
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

    unlockInputs();
}

//This method executes in the background on a separate thread for each note
void MidiCore::playbackWorker() {
    auto& notes = CompositionConstants::notes;

    for (size_t i = 0; i < notes.size(); ++i) {
        {
            std::unique_lock<std::mutex> lock(pauseMutex);
            pauseCondition.wait(lock, [this] { return !isPaused || !isPlaying; });

            if (!isPlaying) return;
        }

        auto& note = notes[i];

        if (note->info.name != Note::NoteName::rest)
        {
            int midiNote = NoteMapper::noteToIndex.at(note->info.name);

            juce::MidiMessage onMsg = juce::MidiMessage::noteOn(1, midiNote, 1.0f);
            sendToOutputs(onMsg);

            int noteDurationMs = note->calculateNoteDuration(CompositionConstants::bpm);
            std::this_thread::sleep_for(std::chrono::milliseconds(noteDurationMs));

            juce::MidiMessage offMsg = juce::MidiMessage::noteOff(1, midiNote, 1.0f);
            sendToOutputs(offMsg);
        }
        else
        {
            int noteDurationMs = note->calculateNoteDuration(CompositionConstants::bpm);
            std::this_thread::sleep_for(std::chrono::milliseconds(noteDurationMs));
        }
        juce::MessageManager::callAsync([this]
            {
                int currentPosition = compositionNotesTextEditor.getCaretPosition();
                int textLength = compositionNotesTextEditor.getText().length();

                if (currentPosition < textLength)
                {
                    auto text = compositionNotesTextEditor.getText();
                    int n = 0;
                    for (int i = currentPosition; i < textLength; ++i)
                    {
                        n++;
                        if (text[i] == '0')
                        {
                            break;
                        }
                    }

                    compositionNotesTextEditor.setCaretPosition(currentPosition + n);
                }
            });
    }

    isPlaying = false;
    juce::MessageManager::callAsync([this]
        {
            playButton->setEnabled(true);
            pauseButton->setEnabled(false);
            stopButton->setEnabled(false);
            unlockInputs();
        });

}


void MidiCore::lockInputs()
{
    backspaceButton->setEnabled(false);
    saveFileButton->setEnabled(false);
    folderButton->setEnabled(false);


    wholeNoteButton->setEnabled(false);
    wholeNoteRestButton->setEnabled(false);
    halfNoteButton->setEnabled(false);
    halfNoteRestButton->setEnabled(false);
    quarterNoteButton->setEnabled(false);
    quarterNoteRestButton->setEnabled(false);
    eighthNoteButton->setEnabled(false);
    eighthNoteRestButton->setEnabled(false);
    sixteenthNoteButton->setEnabled(false);
    sixteenthNoteRestButton->setEnabled(false);

    isKeyboardLocked = true;
}


void MidiCore::unlockInputs()
{
    backspaceButton->setEnabled(true);
    saveFileButton->setEnabled(true);
    folderButton->setEnabled(true);


    wholeNoteButton->setEnabled(true);
    wholeNoteRestButton->setEnabled(true);
    halfNoteButton->setEnabled(true);
    halfNoteRestButton->setEnabled(true);
    quarterNoteButton->setEnabled(true);
    quarterNoteRestButton->setEnabled(true);
    eighthNoteButton->setEnabled(true);
    eighthNoteRestButton->setEnabled(true);
    sixteenthNoteButton->setEnabled(true);
    sixteenthNoteRestButton->setEnabled(true);

    isKeyboardLocked = false;
}
#pragma endregion


#pragma region Notes management by buttons
void MidiCore::arrowUpClick()
{
    switchNoteTextEditor->setText(setHigherNote(switchNoteTextEditor->getText()));
}


void MidiCore::arrowDownClick()
{
    switchNoteTextEditor->setText(setNoteLower(switchNoteTextEditor->getText()));
}


void MidiCore::addNoteByButton(Note::NoteLength noteLength)
{
    auto currentNote = std::make_unique<Note>();
    currentNote->info.length = noteLength;
    currentNote->info.name = chosenNoteName;
    addText(compositionNotesTextEditor, currentNote->getNoteFont());
    CompositionConstants::notes.push_back(std::move(currentNote));
}


void MidiCore::addNoteRestByButton(Note::NoteLength noteLength)
{
    auto currentNote = std::make_unique<Note>();
    currentNote->info.length = noteLength;
    currentNote->info.name = Note::NoteName::rest;
    addText(compositionNotesTextEditor, currentNote->getNoteFont());
    CompositionConstants::notes.push_back(std::move(currentNote));
}


void MidiCore::deleteLastNote()
{
    auto text = compositionNotesTextEditor.getText();
    if (!text.isEmpty())
    {
        text = text.dropLastCharacters(1);
        while (text.getLastCharacter() != '0' && !text.isEmpty())
        {
            text = text.dropLastCharacters(1);
        }
        CompositionConstants::notes.pop_back();
    }
    compositionNotesTextEditor.setText(text);
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
void MidiCore::showMessageBox(const juce::AlertWindow::AlertIconType& iconType, const juce::String& title, const juce::String& message)
{
    juce::AlertWindow::showMessageBoxAsync(iconType,
        title,
        message);
}
#pragma endregion


#pragma region File management
// --- File export (only .pieciolinia or .midi) ---
void MidiCore::saveToFile()
{
    fileChooser = std::make_unique<juce::FileChooser>("Select a location to save the file...",
        juce::File{},
        "Pieciolinia Files (*.pieciolinia)|MIDI Files (*.midi)");

    auto chooserFlags = juce::FileBrowserComponent::saveMode
        | juce::FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();

            if (file != juce::File{})
            {
                auto fileExtenstion = file.getFileExtension();
				if (fileExtenstion.equalsIgnoreCase(".pieciolinia"))
				{
					saveAsPiecioliniaFile(file);
				}
				else if (fileExtenstion.equalsIgnoreCase(".midi"))
				{
					saveAsMidiFile(file);
				}
                else
                {
                    showMessageBox(juce::AlertWindow::AlertIconType::WarningIcon,
                        "Invalid file extension!",
                        "Please select a valid file extension (.pieciolinia or .midi)");
                }
            }
        });
}

void MidiCore::saveAsPiecioliniaFile(const juce::File& file)
{
    std::string contentToSave = "";
    for (auto& note : CompositionConstants::notes)
    {
        contentToSave += NoteMapper::noteToFont.at(note->info.length).at(note->info.name);
    }
    file.replaceWithText(contentToSave);
}

void MidiCore::saveAsMidiFile(const juce::File& file)
{
    juce::MidiMessageSequence midiMessageSequence;
    double standardMidiResolution = 960.0;
    double currentTime = 0.0;

    for (const auto& note : CompositionConstants::notes)
    {
        //Calculate note duration in MIDI ticks:
        double noteDurationBeats = (note->calculateNoteDuration(CompositionConstants::bpm) / 1000.0)
            * (CompositionConstants::bpm / 60.0);
        double noteDurationTicks = noteDurationBeats * standardMidiResolution;

        if (note->info.name != Note::NoteName::rest)
        {
            //Map to midiNote:
            int midiNote = NoteMapper::noteToIndex.at(note->info.name);

            //noteOn message:
            juce::MidiMessage onMsg = juce::MidiMessage::noteOn(1, midiNote, 1.0f);
            midiMessageSequence.addEvent(onMsg, currentTime);

            //noteOff message:
            juce::MidiMessage offMsg = juce::MidiMessage::noteOff(1, midiNote, 1.0f);
            midiMessageSequence.addEvent(offMsg, currentTime + noteDurationTicks);
        }
        //Update time position for next note:
        currentTime += noteDurationTicks;
    }
    midiMessageSequence.updateMatchedPairs();

    juce::MidiFile midiFile;
    midiFile.setTicksPerQuarterNote(standardMidiResolution);
    midiFile.addTrack(midiMessageSequence);

    juce::FileOutputStream outputStream(file);
    if (outputStream.openedOk())
    {
        midiFile.writeTo(outputStream);
        outputStream.flush();
    }
    else
    {
        showMessageBox(juce::AlertWindow::AlertIconType::WarningIcon,
            "Error!",
            "An error occurred during saving a MIDI file");
    }
}

// --- File import (only .pieciolinia) ---
void MidiCore::readFromFile()
{
    fileChooser = std::make_unique<juce::FileChooser>("Select a .pieciolinia file to import...",
        juce::File{},
        "*.pieciolinia");

    auto chooserFlags = juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();

            if (file != juce::File{})
            {
				auto fileExtenstion = file.getFileExtension();
                if (fileExtenstion.equalsIgnoreCase(".pieciolinia"))
                {
                    //Reads file content:
                    auto content = file.loadFileAsString();

                    //Getting content file ready to play and display:
                    getNotesFromImportedFile(content);
                    setLoadedCompositionData(content, file.getFileNameWithoutExtension());
                }
                else
                {
                    showMessageBox(juce::AlertWindow::AlertIconType::WarningIcon,
                        "Invalid file extension!",
                        "Please select a file with valid extension (.pieciolinia)");
                }
            }
        });
}


void MidiCore::getNotesFromImportedFile(const juce::String& content)
{
    std::string fontSymbol = "";
    for (int i = 0; i < content.length(); ++i)
    {
        if (content[i] != '0')
        {
            fontSymbol.push_back(content[i]);
        }
        else
        {
            fontSymbol.push_back(content[i]);
            
            auto& notePair = NoteMapper::fontToNote[fontSymbol];
            auto currentNote = std::make_unique<Note>();
            currentNote->setNoteData(notePair.first, notePair.second);
            CompositionConstants::notes.push_back(std::move(currentNote));
            fontSymbol.clear();
        }
    }
}

void MidiCore::setLoadedCompositionData(const juce::String& content, const juce::String& fileNameWithoutExtension)
{
    nameSongTextEditor->setText(fileNameWithoutExtension);
    compositionNotesTextEditor.setText(content);
}
#pragma endregion
