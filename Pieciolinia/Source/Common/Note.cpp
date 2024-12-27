#include "Note.h"

Note::Note() {
    //some domyœlnie wartoœci
    info.length = NoteLength::Quarter;
    info.name = NoteName::c1;
}

Note::getNodeLength(double time, int bpm, Note note) {

    if (time > 500 && time < 1000) {
        note.info.length = NoteLength::Quarter;
   }
    else if (time < 1000 && time < 2000) {
        note.info.length = NoteLength::Half;
    }
    else if (time > 2000) {
        note.info.length = NoteLength::Whole;
    }
    else if (time > 250 && time < 500) {
        note.info.length = NoteLength::Eighth;
    }
    else if (time > 125 && time < 250) {
        note.info.length = NoteLength::Sixteenth;
    }
}