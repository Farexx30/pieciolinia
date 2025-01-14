#include "Note.h"

Note::Note() {
    //some domylnie wartosci
    info.length = NoteLength::Quarter;
    info.name = NoteName::c1;
}

//usun�am przekazanie note w metodzie, poniewa� nie modyfikowa�oby to warto�ci obiektu
void Note::getNoteLength(double time, int bpm) {

    double beatDuration = 60000.0 / bpm; 

    if (time >= beatDuration * 4) {
        info.length = NoteLength::Whole;
    }
    else if (time >= beatDuration * 2) {
        info.length = NoteLength::Half;
    }
    else if (time >= beatDuration) {
        info.length = NoteLength::Quarter;
    }
    else if (time >= beatDuration / 2) {
        info.length = NoteLength::Eighth;
    }
    else {
        info.length = NoteLength::Sixteenth;
    }
}