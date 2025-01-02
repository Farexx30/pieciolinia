#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <vector>
#include "Note.h"
#include <unordered_map>

namespace ListBoxConstants
{
    //Bardziej nowoczesny i wydajniejszy sposob na stale w C++:
    constexpr const char* midiOutputSelectorName = "Midi output selector";
}

namespace MidiKeyboardConstants
{
    constexpr const char* midiKeyboardName = "Midi Keyboard";
}

namespace LabelConstants
{
    constexpr const char* midiOutputName = "Midi Output Label";
    constexpr const char* midiOutputText = "Midi Output:";
}
namespace KeyToNoteMapping
{
    inline std::unordered_map<char, Note::NoteName> keyToNote = {
        {'B', Note::NoteName::c1},
        
    };
}
namespace CompositionConstants
{
    // Global vector with notes
    inline std::vector<Note> notes;

    //Global bpm
    inline int bpm = 120;
}


//Na pozniej dodawanie do nut do globalnego wektora

/*
* void addNoteToComposition(Note newNote) {
    CompositionConstants::notes.push_back(newNote);
}
* 
* A tutaj czytanie
* 
void printComposition() {
    for (const auto& note : CompositionConstants::notes) {
        std::cout << "Note: " << static_cast<int>(note.info.name) 
                  << ", Length: " << static_cast<int>(note.info.length) << std::endl;
    }
}
*/

#endif