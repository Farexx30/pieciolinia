#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <vector>
#include <memory>
#include "Note.h"

namespace ListBoxConstants
{
    constexpr const char* midiOutputSelectorName = "Midi output selector";
}

namespace MidiKeyboardConstants
{
    constexpr const char* midiKeyboardName = "Midi Keyboard";
}

namespace CompositionConstants
{
    // Global vector with notes
    inline std::vector<std::unique_ptr<Note>> notes;

    //Global bpm
    inline int bpm = 120;
}
#endif