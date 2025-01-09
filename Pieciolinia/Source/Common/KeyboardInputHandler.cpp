/*
  ==============================================================================

    KeyboardInputHandler.cpp
    Created: 2 Jan 2025 11:32:11am
    Author:  Lenovo

  ==============================================================================
*/

#include "Constants.h"
#include "KeyboardInputHandler.h"
#include "Note.h"
//#include "Note.cpp"
#include <iostream>
#include "NoteInfo.h"


void handleKeyPress(char key) {
    auto it = KeyToNoteMapping::keyToNote.find(key);
    if (it != KeyToNoteMapping::keyToNote.end()) {
        Note note;
        NoteInfo noteInfo;
        noteInfo.name = it->second; 
        note.setInfo(noteInfo);    

        CompositionConstants::notes.push_back(note);

        std::cout << "Added note: " << static_cast<int>(note.getInfo().name) << std::endl;
    }
    else {
        std::cerr << "Invalid key pressed: " << key << std::endl;
    }
}