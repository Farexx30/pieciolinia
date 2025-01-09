#pragma once
#ifndef NOTE_H
#define NOTE_H

#include <string>

class Note {
public:
    Note();

    void getNodeLength(double time, int bpm, Note note);

    enum class NoteLength {
        Whole,
        Half,
        Quarter,
        Eighth,
        Sixteenth
    };

    enum class NoteName {
        c1, cSharp1, d1, dSharp1, e1, f1, fSharp1, g1, gSharp1,
        a1, aSharp1, h1, c2, cSharp2, d2, dSharp2, e2, f2, fSharp2, g2
    };


    struct NoteInfo {
        NoteLength length;
        NoteName name;
    };

private:
    int whichNote;
    NoteInfo info;
};

#endif
