#pragma once
#include "Note.h"
#include <unordered_map>

namespace NoteMapper
{
    inline std::unordered_map<int, Note::NoteName> indexToNoteName =
    {
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

    inline std::unordered_map<Note::NoteName, int> noteToIndex =
    {
        {Note::NoteName::c1,      72},
        {Note::NoteName::cSharp1, 73},
        {Note::NoteName::d1,      74},
        {Note::NoteName::dSharp1, 75},
        {Note::NoteName::e1,      76},
        {Note::NoteName::f1,      77},
        {Note::NoteName::fSharp1, 78},
        {Note::NoteName::g1,      79},
        {Note::NoteName::gSharp1, 80},
        {Note::NoteName::a1,      81},
        {Note::NoteName::aSharp1, 82},
        {Note::NoteName::h1,      83},
        {Note::NoteName::c2,      84},
        {Note::NoteName::cSharp2, 85},
        {Note::NoteName::d2,      86},
        {Note::NoteName::dSharp2, 87},
        {Note::NoteName::e2,      88},
        {Note::NoteName::f2,      89},
        {Note::NoteName::fSharp2, 90},
        {Note::NoteName::g2,      91}
    };

    inline std::unordered_map<Note::NoteLength,
        std::unordered_map<Note::NoteName, std::string>> noteToFont =
    {
        {Note::NoteLength::Whole,
            {
                {Note::NoteName::c1,      "Z0"},
                {Note::NoteName::cSharp1, "rZ0"},
                {Note::NoteName::d1,      "[0"},
                {Note::NoteName::dSharp1, "s[0"},
                {Note::NoteName::e1,      "\u005C0"},
                {Note::NoteName::f1,      "]0"},
                {Note::NoteName::fSharp1, "u]0"},
                {Note::NoteName::g1,      "^0"},
                {Note::NoteName::gSharp1, "v^0"},
                {Note::NoteName::a1,      "\u005F0"},
                {Note::NoteName::aSharp1, "w\u005F0"},
                {Note::NoteName::h1,      "\u00600"},
                {Note::NoteName::c2,      "a0"},
                {Note::NoteName::cSharp2, "ya0"},
                {Note::NoteName::d2,      "b0"},
                {Note::NoteName::dSharp2, "zb0"},
                {Note::NoteName::e2,      "c0"},
                {Note::NoteName::f2,      "d0"},
                {Note::NoteName::fSharp2, "\u007Cd0"},
                {Note::NoteName::g2,      "e0"}
            }
        },
        {Note::NoteLength::Half,
            {
                {Note::NoteName::c1,      "N0"},
                {Note::NoteName::cSharp1, "rN0"},
                {Note::NoteName::d1,      "O0"},
                {Note::NoteName::dSharp1, "sO0"},
                {Note::NoteName::e1,      "Q0"},
                {Note::NoteName::f1,      "P0"},
                {Note::NoteName::fSharp1, "uP0"},
                {Note::NoteName::g1,      "R0"},
                {Note::NoteName::gSharp1, "vR0"},
                {Note::NoteName::a1,      "S0"},
                {Note::NoteName::aSharp1, "wS0"},
                {Note::NoteName::h1,      "T0"},
                {Note::NoteName::c2,      "U0"},
                {Note::NoteName::cSharp2, "yU0"},
                {Note::NoteName::d2,      "V0"},
                {Note::NoteName::dSharp2, "zV0"},
                {Note::NoteName::e2,      "W0"},
                {Note::NoteName::f2,      "X0"},
                {Note::NoteName::fSharp2, "\u007CX0"},
                {Note::NoteName::g2,      "Y0"}
            }
        },
        {Note::NoteLength::Quarter,
            {
                {Note::NoteName::c1,      "B0"},
                {Note::NoteName::cSharp1, "rB0"},
                {Note::NoteName::d1,      "C0"},
                {Note::NoteName::dSharp1, "sC0"},
                {Note::NoteName::e1,      "D0"},
                {Note::NoteName::f1,      "E0"},
                {Note::NoteName::fSharp1, "uE0"},
                {Note::NoteName::g1,      "F0"},
                {Note::NoteName::gSharp1, "vF0"},
                {Note::NoteName::a1,      "G0"},
                {Note::NoteName::aSharp1, "wG0"},
                {Note::NoteName::h1,      "H0"},
                {Note::NoteName::c2,      "I0"},
                {Note::NoteName::cSharp2, "yI0"},
                {Note::NoteName::d2,      "J0"},
                {Note::NoteName::dSharp2, "zJ0"},
                {Note::NoteName::e2,      "K0"},
                {Note::NoteName::f2,      "L0"},
                {Note::NoteName::fSharp2, "\u007CL0"},
                {Note::NoteName::g2,      "M0"}
            }
        },
        {Note::NoteLength::Eighth,
            {
                {Note::NoteName::c1,      "60"},
                {Note::NoteName::cSharp1, "r60"},
                {Note::NoteName::d1,      "70"},
                {Note::NoteName::dSharp1, "s70"},
                {Note::NoteName::e1,      "80"},
                {Note::NoteName::f1,      "90"},
                {Note::NoteName::fSharp1, "u90"},
                {Note::NoteName::g1,      ":0"},
                {Note::NoteName::gSharp1, "v:0"},
                {Note::NoteName::a1,      ";0"},
                {Note::NoteName::aSharp1, "w;0"},
                {Note::NoteName::h1,      "<0"},
                {Note::NoteName::c2,      "=0"},
                {Note::NoteName::cSharp2, "y=0"},
                {Note::NoteName::d2,      ">0"},
                {Note::NoteName::dSharp2, "z>0"},
                {Note::NoteName::e2,      "?0"},
                {Note::NoteName::f2,      "@0"},
                {Note::NoteName::fSharp2, "\u007C@0"},
                {Note::NoteName::g2,      "A0"}
            }
        },
        {Note::NoteLength::Sixteenth,
            {
                {Note::NoteName::c1,      "f0"},
                {Note::NoteName::cSharp1, "rf0"},
                {Note::NoteName::d1,      "g0"},
                {Note::NoteName::dSharp1, "sg0"},
                {Note::NoteName::e1,      "h0"},
                {Note::NoteName::f1,      "i0"},
                {Note::NoteName::fSharp1, "ui0"},
                {Note::NoteName::g1,      "j0"},
                {Note::NoteName::gSharp1, "vj0"},
                {Note::NoteName::a1,      "k0"},
                {Note::NoteName::aSharp1, "wk0"},
                {Note::NoteName::h1,      "l0"},
                {Note::NoteName::c2,      "m0"},
                {Note::NoteName::cSharp2, "ym0"},
                {Note::NoteName::d2,      "n0"},
                {Note::NoteName::dSharp2, "zn0"},
                {Note::NoteName::e2,      "o0"},
                {Note::NoteName::f2,      "p0"},
                {Note::NoteName::fSharp2, "\u007Cp0"},
                {Note::NoteName::g2,      "q0"}
            }
        }
    };
}
