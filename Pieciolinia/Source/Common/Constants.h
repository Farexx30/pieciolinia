#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

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

#endif