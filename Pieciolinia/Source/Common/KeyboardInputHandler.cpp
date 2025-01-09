/*
  ==============================================================================

    KeyboardInputHandler.cpp
    Created: 2 Jan 2025 11:32:11am
    Author:  Lenovo

  ==============================================================================
*/

#include "KeyboardInputHandler.h"
#include "Constants.h"
#include "Note.h"
#include "Note.cpp"
#include <iostream>

void handleKeyPress(char key) {
    auto it = KeyToNoteMapping::keyToNote.find(key);
    if (it != KeyToNoteMapping::keyToNote.end()) {
        Note note;
        note.info.name = it->second;

        CompositionConstants::notes.push_back(note);

        std::cout << "Added note: " << static_cast<int>(note.info.name) << std::endl;
    }
    else {
        std::cerr << "Invalid key pressed: " << key << std::endl;
    }
}