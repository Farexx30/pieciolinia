#pragma once
#ifndef NOTE_H
#define NOTE_H

#include <string>

class Note {
public:
    Note();

    void setNoteInfo(double time, int bpm, int keyIndex);
    int Note::calculateNoteDuration(int bpm);
    std::string getNoteFont();

    //which symbol 
    enum class NoteLength {
        Whole,
        Half,
        Quarter,
        Eighth,
        Sixteenth
    };
    //which note which means which line
    enum class NoteName {
        c1, cSharp1, d1, dSharp1, e1, f1, fSharp1, g1, gSharp1,
        a1, aSharp1, h1, c2, cSharp2, d2, dSharp2, e2, f2, fSharp2, g2
    };


    struct NoteInfo {
        NoteLength length;
        NoteName name;
    };


    //int whichNote;
    NoteInfo info;
private:
    void setNoteLength(double time, int bpm);
    void setNoteName(int keyIndex);

};

#endif
