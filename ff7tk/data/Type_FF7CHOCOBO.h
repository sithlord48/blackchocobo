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

#ifndef TYPE_FF7CHOCOBO_H
#define TYPE_FF7CHOCOBO_H
#ifdef _MSC_VER
#	define PACK(structure)			\
		__pragma(pack(push, 1))		\
		structure					\
		__pragma(pack(pop))
#else
#	define PACK(structure) structure Q_PACKED
#endif
/*! \struct FF7CHOCOBO
 *  \brief a chocobo in save game
 *
 *  16 Bytes total size 15 known 1 Byte Unknown
 *  \todo Research The Personality byte
 *  \todo Research the pcount byte
 */
PACK(
struct FF7CHOCOBO {
	quint16 sprintspd;		/**< [0x0000] Speed */
	quint16 maxsprintspd;	/**< [0x0002] Max Speed*/
	quint16 speed;			/**< [0x0004] Sprint speed*/
	quint16 maxspeed;		/**< [0x0006] Max Sprint speed*/
	quint8 accel;			/**< [0x0008] acceleration*/
	quint8 coop;			/**< [0x0009] cooperation*/
	quint8 intelligence;	/**< [0x000A] Intelligence*/
	quint8 personality;		/**< [0x000B] personality Type - THIS NEED TO HAVE A RANGE FOUND!*/
	quint8 pcount;			/**< [0x000C] P count ??*/
	quint8 raceswon;		/**< [0x000D] Number of races won*/
	quint8 sex;				/**< [0x000E] Sex (0=male,1=female)*/
	quint8 type;			/**< [0x000F] Type (Yellow,Green,Blue,Black,Gold)*/
});

#endif // TYPE_FF7CHOCOBO_H
