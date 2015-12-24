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

#ifndef TYPE_FF7CHAR_H
#define TYPE_FF7CHAR_H

#include "Type_materia.h"

/*! \struct FF7CHAR
 * \brief  Character Info in the save game.
 *
 * 132 Bytes total size 128 Bytes Known, 4 Bytes Unknown (possibly unused)
 * \todo Check Unknown bits to see if ever used
 */
struct FF7CHAR {
	quint8 id;				/**< [0x0000] Character id (used by Sephiroth/Vincent slot)*/
	quint8 level;			/**< [0x0001] Level (0-99)*/
	quint8 strength;		/**< [0x0002] Strength Stat (0-255)*/
	quint8 vitality;		/**< [0x0003] Vitality Stat(0-255)*/
	quint8 magic;			/**< [0x0004] Magic Stat(0-255)*/
	quint8 spirit;			/**< [0x0005] Spirit Stat(0-255)*/
	quint8 dexterity;		/**< [0x0006] Dexterity Stat(0-255)*/
	quint8 luck;			/**< [0x0007] Luck Stat(0-255)*/
	quint8 strength_bonus;	/**< [0x0008] Str Bonus (0-255)*/
	quint8 vitality_bonus;	/**< [0x0009] Vit Bonus (0-255)*/
	quint8 magic_bonus;		/**< [0x000A] Magic Bonus (0-255)*/
	quint8 spirit_bonus;	/**< [0x000B] Spirit Bonus(0-255)*/
	quint8 dexterity_bonus;	/**< [0x000C] Dex Bonus(0-255)*/
	quint8 luck_bonus;		/**< [0x000D] Luck Bonus (0-255)*/
	qint8  limitlevel;		/**< [0x000E] Current limit level (1-4)*/
	quint8 limitbar;		/**< [0x000F] Current limit bar amount (0xFF = limit break)*/
	quint8 name[12];		/**< [0x0010] Name (ff7)*/
	quint8 weapon;			/**< [0x001C] Equipped weapon*/
	quint8 armor;			/**< [0x001D] Equipped armor*/
	quint8 accessory;		/**< [0x001E] Equipped accessory*/
	quint8 flags[3];		/**< [0x001F] Character flags[0:0x10] 1: Sadness.[0:0x20] 1: Fury. [1:0x01] 1: Front row.  0: Back row. [2:0x00-0xFF] TNL bar.*/
	quint16 limits;			/**< [0x0022] Learned limit skills*/
	quint16 kills;			/**< [0x0024] Kills Character Has*/
	quint16 timesused1;		/**< [0x0026] Times limit 1-1 used*/
	quint16 timesused2;		/**< [0x0028] Times limit 2-1 used*/
	quint16 timesused3;		/**< [0x002A] Times limit 3-1 used*/
	quint16 curHP;			/**< [0x002C] Current HP*/
	quint16 baseHP;			/**< [0x002E] Base HP */
	quint16 curMP;			/**< [0x0030] Current MP*/
	quint16 baseMP;			/**< [0x0032] Base MP */
	quint8 z_4[4];			/**< [0x0034] UNKNOWN!!!! Most likley unused yet to see with value other then 0*/
	quint16 maxHP;			/**< [0x0038] Maximum HP (Base Hp +  equipment & materia changes )*/
	quint16 maxMP;			/**< [0x003A] Maximum MP (Base Mp +  equipment & materia changes )*/
	quint32 exp;			/**< [0x003C] Current EXP*/
	materia materias[16];	/**< [0x0040] Materia slots (0-7=weapon,8-15=armor)*/
	quint32 expNext;		/**< [0x0080] EXP to next level*/
}__attribute__((__packed__));
#endif //< TYPE_FF7CHAR_H
