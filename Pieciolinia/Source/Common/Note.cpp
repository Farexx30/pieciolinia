#include "Note.h"

Note::Note() {
    //some domyœlnie wartoœci
    info.length = NoteLength::Quarter;
    info.name = NoteName::c1;
}

void Note::calculateNoteLength(double time, int bpm, Note note) {

    double beatDuration = 60000.0 / bpm; 

    if (time >= beatDuration * 4) {
        note.info.length = NoteLength::Whole;
    }
    else if (time >= beatDuration * 2) {
        note.info.length = NoteLength::Half;
    }
    else if (time >= beatDuration) {
        note.info.length = NoteLength::Quarter;
    }
    else if (time >= beatDuration / 2) {
        note.info.length = NoteLength::Eighth;
    }
    else {
        note.info.length = NoteLength::Sixteenth;
    }
}