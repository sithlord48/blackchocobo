/****************************************************************************/
//    copyright 2012 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//   FF7tk is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#ifndef TYPE_MATERIA_H
#define TYPE_MATERIA_H

#ifdef _MSC_VER
#   define PACK(structure)          \
    __pragma(pack(push, 1))     \
    structure                   \
    __pragma(pack(pop))
#elif defined(__MINGW32__)
#define PACK(structure) structure __attribute__ ((gcc_struct, __packed__))
#else
#define PACK(structure) structure Q_PACKED
#endif

/*! \struct materia
 *  \brief materia format saved in materia list or on a character
 *
 * Total Size 4 Bytes 100% known!
 */
PACK(
struct materia{// sizeof 4
    quint8 id;      /**< materias id */
    quint8 ap[3];   /** Ap Storage is done as a 24bit int. */
});
#endif // TYPE_MATERIA_H
