/****************************************************************************/
//    copyright 2010 Chris Rizzitello <sithlord48@gmail.com>                //
//                                                                          //
//    This file is part of Black Chocobo.                                   //
//                                                                          //
//    Black Chocobo is free software: you can redistribute it and/or modify //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    Black Chocobo is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#ifndef GLOBALS_H
#define GLOBALS_H
    #ifndef FF7SAVE_H
        #include "FF7SAVE.h"
    #endif

int ff7__checksum(void * qw );

void preptext (void);
void fix_pc_bytemask(void);
static char chPC[256] = {
        ' ',	// 00: Space
        '!',
        '"',
        '#',
        '$',
        '%',
        '&',
        '\'',	// 07: "'" (apostrophe)
        '(',
        ')',
        '*',
        '+',
        ',',
        '-',
        '.',
        '/',
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        ':',
        ';',
        '<',
        '=',
        '>',
        '?',
        '@',
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
        'G',
        'H',
        'I',
        'J',
        'K',
        'L',
        'M',
        'N',
        'O',
        'P',
        'Q',
        'R',
        'S',
        'T',
        'U',
        'V',
        'W',
        'X',
        'Y',
        'Z',
        '[',
        '\\',
(char)	']',
        '^',
        '_',
        '`',
        'a',
        'b',
        'c',
        'd',
        'e',
        'f',
        'g',
        'h',
        'i',
        'j',
        'k',
        'l',
        'm',
        'n',
        'o',
        'p',
        'q',
        'r',
        's',
        't',
        'u',
        'v',
        'w',
        'x',
        'y',
        'z',
        '{',
        '|',
        '}',
        '~',
        ' ',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        ' ',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        ' ',	// non-equality
        '�',
        '�',
        ' ',	// infinity
        '�',
        ' ',	// <=
        ' ',	// >=
        '�',
        '�',
        ' ',	// a-like symbol
        ' ',	// sum
        ' ',	// capital pi
        ' ',	// pi
        ' ',	// J-like symbol
        ' ',	// a-underline
        ' ',	// o-underline
        ' ',	// capital omega
        '�',
        '�',
        '�',
        '�',
        '�',
        ' ',	// check mark
        '�',
        ' ',	// approximate to
        ' ',	// capital delta
        '�',
        '�',
        '�',	// '...' character
        ' ',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        ' ',	// romboid
        '�',
        '/',
        '�',
        '�',
        '�',
        ' ',	// fi-like
        ' ',	// fl-like
        '�',	// filled square
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        ' ',	// A-dash
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        '�',
        ' ',	// apple
        '�',
        '�',
        '�',
        ' ',	// wide U
        ' ',	// low vertical dash
        ' ',	// D5: Cyan (following FE)
        ' ',
        ' ',	// D7: Purple (following FE)
        ' ',
        ' ',	// D9: White (following FE)
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',	// E0
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',	// E7: Line feed (?)
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',	// F0
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',	// FE: Change text color
        '\0'	// FF: End of string (NULL)
};
#endif // GLOBALS_H


