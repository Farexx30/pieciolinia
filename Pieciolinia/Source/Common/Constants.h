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
//maybe for later mapping from keyboard
namespace KeyToNoteMapping
{
    inline std::unordered_map<char, Note::NoteName> keyToNote = {
        {'B', Note::NoteName::c1},

    };
}

namespace NoteMapping
{
    inline std::unordered_map<Note::NoteLength, std::unordered_map<Note::NoteName, std::string>> noteToFont = {
    {Note::NoteLength::Whole, {
        {Note::NoteName::c1,      "r"}, 
        {Note::NoteName::cSharp1, "\u00D3r"}, 
        {Note::NoteName::d1,      "s"},
        {Note::NoteName::dSharp1, "\u00D4s"},
        {Note::NoteName::e1,      "t"},
        {Note::NoteName::f1,      "u"},
        {Note::NoteName::fSharp1, "\u00D6u"},
        {Note::NoteName::g1,      "v"},
        {Note::NoteName::gSharp1, "\u00D7v"},
        {Note::NoteName::a1,      "w"},
        {Note::NoteName::aSharp1, "\u00D8w"},
        {Note::NoteName::h1,      "x"},
        {Note::NoteName::c2,      "y"},
        {Note::NoteName::cSharp2, "\u00DAy"},
        {Note::NoteName::d2,      "z"},
        {Note::NoteName::dSharp2, "\u00DBz"},
        {Note::NoteName::e2,      "{"},
        {Note::NoteName::f2,      "|"},
        {Note::NoteName::fSharp2, "\u00DC|"},
        {Note::NoteName::g2,      "}"}

    }},
    {Note::NoteLength::Half, {
        {Note::NoteName::c1,      "b"},
        {Note::NoteName::cSharp1, "b"},
        {Note::NoteName::d1,      "c"},
        {Note::NoteName::dSharp1, "c"},
        {Note::NoteName::e1,      "d"},
        {Note::NoteName::f1,      "e"},
        {Note::NoteName::fSharp1, "e"},
        {Note::NoteName::g1,      "f"},
        {Note::NoteName::gSharp1, "f"},
        {Note::NoteName::a1,      "g"},
        {Note::NoteName::aSharp1, "g"},
        {Note::NoteName::h1,      "h"},
        {Note::NoteName::c2,      "i"},
        {Note::NoteName::cSharp2, "i"},
        {Note::NoteName::d2,      "j"},
        {Note::NoteName::dSharp2, "j"},
        {Note::NoteName::e2,      "k"},
        {Note::NoteName::f2,      "l"},
        {Note::NoteName::fSharp2, "l"},
        {Note::NoteName::g2,      "m"}
    }},
    {Note::NoteLength::Quarter, {
        {Note::NoteName::c1,      "R"},
        {Note::NoteName::cSharp1, "R"},
        {Note::NoteName::d1,      "S"},
        {Note::NoteName::dSharp1, "S"},
        {Note::NoteName::e1,      "T"},
        {Note::NoteName::f1,      "U"},
        {Note::NoteName::fSharp1, "U"},
        {Note::NoteName::g1,      "V"},
        {Note::NoteName::gSharp1, "V"},
        {Note::NoteName::a1,      "W"},
        {Note::NoteName::aSharp1, "W"},
        {Note::NoteName::h1,      "X"},
        {Note::NoteName::c2,      "Y"},
        {Note::NoteName::cSharp2, "Y"},
        {Note::NoteName::d2,      "Z"},
        {Note::NoteName::dSharp2, "Z"},
        {Note::NoteName::e2,      "["},
        {Note::NoteName::f2,      "\u005C"},
        {Note::NoteName::fSharp2, "\u005C"},
        {Note::NoteName::g2,      "]"}
    }},
    {Note::NoteLength::Eighth, {
        {Note::NoteName::c1,      "B"},
        {Note::NoteName::cSharp1, "B"},
        {Note::NoteName::d1,      "C"},
        {Note::NoteName::dSharp1, "C"},
        {Note::NoteName::e1,      "D"},
        {Note::NoteName::f1,      "E"},
        {Note::NoteName::fSharp1, "E"},
        {Note::NoteName::g1,      "F"},
        {Note::NoteName::gSharp1, "F"},
        {Note::NoteName::a1,      "G"},
        {Note::NoteName::aSharp1, "G"},
        {Note::NoteName::h1,      "H"},
        {Note::NoteName::c2,      "I"},
        {Note::NoteName::cSharp2, "I"},
        {Note::NoteName::d2,      "J"},
        {Note::NoteName::dSharp2, "J"},
        {Note::NoteName::e2,      "K"},
        {Note::NoteName::f2,      "L"},
        {Note::NoteName::fSharp2, "L"},
        {Note::NoteName::g2,      "M"}
    }},
    {Note::NoteLength::Sixteenth, {
        {Note::NoteName::c1,      "\u00C2"},
        {Note::NoteName::cSharp1, "\u00C2"},
        {Note::NoteName::d1,      "\u00C3"},
        {Note::NoteName::dSharp1, "\u00C3"},
        {Note::NoteName::e1,      "\u00C4"},
        {Note::NoteName::f1,      "\u00C5"},
        {Note::NoteName::fSharp1, "\u00C5"},
        {Note::NoteName::g1,      "\u00C6"},
        {Note::NoteName::gSharp1, "\u00C6"},
        {Note::NoteName::a1,      "\u00C7"},
        {Note::NoteName::aSharp1, "\u00C7"},
        {Note::NoteName::h1,      "\u00C8"},
        {Note::NoteName::c2,      "\u00C9"},
        {Note::NoteName::cSharp2, "\u00C9"},
        {Note::NoteName::d2,      "\u00CA"},
        {Note::NoteName::dSharp2, "\u00CA"},
        {Note::NoteName::e2,      "\u00CB"},
        {Note::NoteName::f2,      "\u00CC"},
        {Note::NoteName::fSharp2, "\u00CC"},
        {Note::NoteName::g2,      "\u00CD"}
    }}
    };

    std::unordered_map<int, Note::NoteName> indexToNoteName = {
        {72, Note::NoteName::c1},
        {73, Note::NoteName::cSharp1}, 
        {74, Note::NoteName::d1}, 
        {75, Note::NoteName::dSharp1},
        {76, Note::NoteName::e1}, 
        {77, Note::NoteName::f1}, 
        {78, Note::NoteName::fSharp1}, 
        {79, Note::NoteName::g1},
        {80, Note::NoteName::gSharp1}, 
        {81, Note::NoteName::a1}, 
        {82, Note::NoteName::aSharp1}, 
        {83, Note::NoteName::h1},
        {84, Note::NoteName::c2}, 
        {85, Note::NoteName::cSharp2}, 
        {86, Note::NoteName::d2}, 
        {87, Note::NoteName::dSharp2},
        {88, Note::NoteName::e2}, 
        {89, Note::NoteName::f2}, 
        {90, Note::NoteName::fSharp2}, 
        {91, Note::NoteName::g2}
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