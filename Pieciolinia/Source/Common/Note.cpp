#include "Note.h"
#include "Mappers.h"

Note::Note() 
{
    info.length = NoteLength::Quarter;
    info.name = NoteName::c1;
}


void Note::setNoteLength(double time, int bpm) 
{
    double beatDuration = 60000.0 / bpm; 

    if (time >= beatDuration * 4) 
        info.length = NoteLength::Whole;
    else if (time >= beatDuration * 2) 
        info.length = NoteLength::Half;
    else if (time >= beatDuration) 
        info.length = NoteLength::Quarter;
    else if (time >= beatDuration / 2) 
        info.length = NoteLength::Eighth;
    else
        info.length = NoteLength::Sixteenth;
}

void Note::setNoteName(int keyIndex)
{
    info.name = NoteMapper::indexToNoteName[keyIndex];
}



void Note::setNoteInfo(double time, int bpm, int keyIndex)
{
    setNoteLength(time, bpm);
    setNoteName(keyIndex);
}


std::string Note::getNoteFont()
{
    auto& noteFont = NoteMapper::noteToFont.at(info.length).at(info.name);
    return noteFont;
}


int Note::calculateNoteDuration(int bpm) 
{
    double beatDuration = 60000.0 / bpm;

    switch (info.length) {
    case Note::NoteLength::Whole:      
        return static_cast<int>(beatDuration * 4);
    case Note::NoteLength::Half:      
        return static_cast<int>(beatDuration * 2);
    case Note::NoteLength::Quarter:    
        return static_cast<int>(beatDuration);
    case Note::NoteLength::Eighth:     
        return static_cast<int>(beatDuration / 2);
    case Note::NoteLength::Sixteenth:  
        return static_cast<int>(beatDuration / 4);
    default:                           
        return static_cast<int>(beatDuration);
    }
}