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
        {'z', Note::NoteName::c1}, {'s', Note::NoteName::cSharp1},
        {'x', Note::NoteName::d1}, {'d', Note::NoteName::dSharp1},
        {'c', Note::NoteName::e1}, {'v', Note::NoteName::f1},
        {'g', Note::NoteName::fSharp1}, {'b', Note::NoteName::g1},
        {'h', Note::NoteName::gSharp1}, {'n', Note::NoteName::a1},
        {'j', Note::NoteName::aSharp1}, {'m', Note::NoteName::h1},
        {'q', Note::NoteName::c2}, {'2', Note::NoteName::cSharp2},
        {'w', Note::NoteName::d2}, {'3', Note::NoteName::dSharp2},
        {'e', Note::NoteName::e2}, {'r', Note::NoteName::f2},
        {'5', Note::NoteName::fSharp2}, {'t', Note::NoteName::g2}
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