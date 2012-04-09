#ifndef TYPE_FF7CHAR_H
#define TYPE_FF7CHAR_H

#include "static_data/Type_materia.h"

#endif // TYPE_FF7CHAR_H

struct FF7CHAR {        	// [0x0084] Character info -98% - 1 Unknown
    quint8 id;			// [0x0000] Character id (used by Sephiroth/Vincent slot)
    quint8 level;        	// [0x0001] Level (0-99)
    quint8 strength;		// [0x0002] Strength (0-255)
    quint8 vitality;		// [0x0003] Vitality (0-255)
    quint8 magic;		// [0x0004] Magic (0-255)
    quint8 spirit;		// [0x0005] Spirit (0-255)
    quint8 dexterity;		// [0x0006] Dexterity (0-255)
    quint8 luck;		// [0x0007] Luck (0-255)
    quint8 strength_bonus;      // [0x0008] Str Bonus
    quint8 vitality_bonus;	// [0x0009] Vitality (0-255)
    quint8 magic_bonus;		// [0x000A] Magic (0-255)
    quint8 spirit_bonus;	// [0x000B] Spirit (0-255)
    quint8 dexterity_bonus;	// [0x000C] Dexterity (0-255)
    quint8 luck_bonus;		// [0x000D] Luck (0-255)
    qint8  limitlevel;		// [0x000E] Current limit level (1-4)
    quint8 limitbar;		// [0x000F] Current limit bar (0xFF = limit break)
    quint8 name[12];		// [0x0010] Name (ff7)
    quint8 weapon;		// [0x001C] Equipped weapon
    quint8 armor;               // [0x001D] Equipped armor
    quint8 accessory;		// [0x001E] Equipped accessory
    quint8 flags[3];		// [0x001F] Character flags[0:0x10] 1: Sadness.[0:0x20] 1: Fury. [1:0x01] 1: Front row.  0: Back row. [2:0x00-0xFF] TNL bar.
    quint16 limits;		// [0x0022] Learned limit skills
    quint16 kills;		// [0x0024] Kill Char Has
    quint16 timesused1;		// [0x0026] Times limit 1-1 used
    quint16 timesused2;         // [0x0028] Times limit 2-1 used
    quint16 timesused3;         // [0x002A] Times limit 3-1 used
    quint16 curHP;		// [0x002C] Current HP
    quint16 baseHP;		// [0x002E] Base HP (before materia alterations)
    quint16 curMP;		// [0x0030] Current MP
    quint16 baseMP;		// [0x0032] Base MP (before materia alterations)
    quint8 z_4[4];              // [0x0034] UNKNOWN!!!!
    quint16 maxHP;		// [0x0038] Maximum HP (after materia alterations)
    quint16 maxMP;		// [0x003A] Maximum MP (after materia alterations)
    quint32 exp;		// [0x003C] Current EXP
    materia materias[16];	// [0x0040] Materia slots (0-7=weapon,8-15=armor)
    quint32 expNext;            // [0x0080] EXP to next level
}__attribute__((__packed__));
