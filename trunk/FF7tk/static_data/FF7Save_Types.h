/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#ifndef FF7SAVE_TYPES_H
#define FF7SAVE_TYPES_H

#include "Type_FF7CHAR.h"
//Materia Type is included as part of FF7Char

/*~~~~~~~~~~~~~~~~~~~~~~~~STRUCT TYPES AND SAVE STRUCT~~~~~~~~~~~~~~~~*/

struct LOVE
{
qint8 aeris;
qint8 tifa;
qint8 yuffie;
qint8 barret;
}__attribute__((__packed__));

struct FF7DESC {		// [0x0044] Descriptions; no actual game data -100%
    quint8 level;		// [0x0000] Lead character's level
    quint8 party[3];             // [0x0001] Party
    quint8 name[16];		// [0x0004] Lead character's name (ff7 string)
    quint16 curHP;		// [0x0014] Lead character's current HP
    quint16 maxHP;		// [0x0016] Lead character's base HP
    quint16 curMP;		// [0x0018] Lead character's current MP
    quint16 maxMP;		// [0x001A] Lead character's base MP
    quint32 gil;		// [0x001C] Amount of gil
    quint32 time;		// [0x0020] Total number of seconds played
    quint8 location[32];	// [0x0024] Save location (ff7 string)
}__attribute__((__packed__));
struct FF7WORLD_COORDS
{
quint8 x[3];                   //[0x00] x on map
quint8 angle;                  //[0x03] viewing angle 0-0xff
quint8 y[3];                   //[0x04] y on map 0-
qint8  z;                      //[0x05] z min=-127 max=127
}__attribute__((__packed__));



struct FF7CHOCOBO {		// [0x0010] Chocobo - 99% - 1 Personality unknown!
    quint16 sprintspd;		// [0x0000] Speed
    quint16 maxsprintspd;       // [0x0002] Max Speed
    quint16 speed;		// [0x0004] Sprint speed
    quint16 maxspeed;		// [0x0006] Max Sprint speed
    quint8 accel;               // [0x0008] acceleration
    quint8 coop;                // [0x0009] cooperation
    quint8 intelligence;	// [0x000A] Intelligence
    quint8 personality;         // [0x000B] personality Type - THIS NEED TO HAVE A RANGE FOUND!
    quint8 pcount;              // [0x000C] P count ??
    quint8 raceswon;		// [0x000D] Number of races won
    quint8 sex;			// [0x000E] Sex (0=male,1=female)
    quint8 type;		// [0x000F] Type (Yellow,Green,Blue,Black,Gold)
}__attribute__((__packed__));

struct FF7XYZ {                 // size of 6. used for coords
    quint16 x;
    quint16 y;
    quint16 z;
}__attribute__((__packed__));

struct FF7SLOT {		// Save slot - Length 0x10F4
    qint16 checksum;		// [0x0000] Checksum
    quint8 z_1[2];              // [0x0002] Unknown data
    FF7DESC desc;		// [0x0004] Length:0x44] Slot description
    quint8 colors[4][3];	// [0x0048] Window colors (RGB)
    FF7CHAR chars[9];		// [0x0054:84] The nine characters (Cl,Ba,Ti,Ae,Re,Yu,Ca,Vi,Ci)
    qint8 party[3];		// [0x04F8] Party members
    quint8 z_2[1];              // [0x04FB] always 0xFF
    quint16 items[320];		// [0x04FC] Items (320 slots)
    materia materias[200];	// [0x077C] Materia (200 slots)
    materia stolen[48];         // [0x0A9C] materia stolen by yuffie.
    quint8 z_3[32];             // [0x0B5C] UNKNOWN DATA (Always 0xFF?)
    quint32 gil;		// [0x0B7C] Party gil
    quint32 time;		// [0x0B80] Total number of seconds played
    quint8 timer[3];            // [0x0B84] countdown timer H:M:S
    quint8 z_4[13];             // [0x0B87] UNKNOWN DATA
    quint16 mapid;		// [0x0B94] Current map
    quint16 locationid;		// [0x0B96] Current location
    quint8 z_5[2];              // [0x0B98] UNKNOWN DATA
    FF7XYZ coord;		// [0x0B9A] Current coordinates (world map)
    quint8 z_6[4];              // [0x0BA0] UNKNOWN DATA
    quint16 mprogress;          // [0x0BA4] Main Progress var
    quint8 z_7[1];              // [0x0BA6] UNKNOWN DATA
    LOVE love;                  // [0X0BA7] Main love points.
    quint8 z_8[17];             // [0x0BAB] UNKNOWN DATA
    quint16 battles;            // [0x0BBC] Number of battle
    quint16 runs;               // [0x0BBE] Number of escapes
    quint16 menu_visible;       // [0x0BC0] Menu items Visible
    quint16 menu_locked;        // [0x0BC2] Menu items locked
    quint8 z_9[16];             // [0x0BC4] UNKNOWN DATA
    quint8 itemsmask_1;         // [0x0BD4] Item mask_1
    quint8 materiacaves;        // [0x0BD5] materia caves picked up  0x01 mime,0x02 HP<->MP,0x04 4xmag, 0x08 KOTR
    quint8 z_10[14];            // [0x0BD6] UNKNOWN DATA
    quint8 keyitems[8];         // [0x0BE4] Key items
    quint8 z_11[8];             // [0x0BEC] UNKNOWN DATA
    LOVE b_love;                // [0x0BF4] Battle Love Points
    quint8 z_12[1];             // [0x0BF8] UNKNOWN DATA
    qint8 pennedchocos[4];      // [0x0BF9] chocos in fenced area at farm rating
    quint8 z_13[2];             // [0x0BFD] UNKNOWN DATA
    quint8 u_weapon_hp[3];      // [0x0BFF] Ultimate Weapons Remaining Hp
    quint8 z_14[28];            // [0x0C02] UNKNOWN DATA
    quint8 tut_sub;             // [0x0C1E] Have we seen the sub tutorial 0x04 =on Show Battle Targets Label 0x40=on
    quint8 ruby_emerald;        // [0x0C1F] WEAPONS ALIVE? 0x05=both 0x1D =non 0x0D = emerald
    quint8 z_15[2];             // [0x0C20] UNKNOWN DATA
    quint8 world_map_chocobos;  // [0x0C22] what is chocobos are visible on world map
    quint8 world_map_vehicles;  // [0x0C23] what is vehicles are visible on world map 0x00 empty,0x01 buggy,0x04 tiny bronco,0x10 highwind (combineable; never 0x11)
    quint8 z_16[97];            // [0x0C24] UNKNOWN DATA
    quint8 bm_progress1;        // [0x0C85] Bombing Mission Flag 1
    quint8 bm_progress2;        // [0x0C86] Bombing Mission Flag 2
    quint8 z_17[45];            // [0X0C87] UNKNOWN DATA 45 50
    quint8 aeris_chruch;        // [0x0CB4] aeris chruch
    quint8 z_18[49];            // [0x0CB5] UNKNOWN
    quint8 bm_progress3;        // [0X0CE6] Bombing mission flag 3
    quint8 z_19[7];             // [0X0CE7] UNKNOWN DATA
    quint16 gp;                 // [0x0CEE] Party GP (0-10000)
    quint8 z_20[12];            // [0x0CF0] UNKNOWN DATA
    qint8 stables;              // [0x0CFC] Number of chocobo stables owned
    qint8 stablesoccupied;      // [0x0CFD] Number of occupied stables
    quint8 z_21[1];             // [0x0CFE] UNKNOWN DATA
    qint8 chocobomask;          // [0x0CFF] Mask of occupied stables
    quint8 chocomated;          // [0x0D00] what stalls can't mate
    quint8 z_22[40];            // [0x0D01] UNKNOWN DATA
    quint8 yuffieforest;        // [0x0D29] yuffie in forest if bit1 = 1 then yes.. others here too?
    quint8 z_23[28];            // [0x0D2A] UNKNOWN DATA
    quint8 donprogress;         // [0x0D46] don's progress var. 00 - 03 when done
    quint8 z_24[31];            // [0x0D47] UNKNOWN DATA
    quint8 turtleflyers;        // [0x0D66] turtles paradice flyers.
    quint8 z_25[12];            // [0X0D67] UNKNOWN DATA
    quint8 reg_yuffie;          // [0x0D73] yuffie regular? 0x6F=yes 0x6E=no
    quint8 z_26[15];            // [0x0D74] UNKNOWN DATA
    quint8 midgartrainflags;    // [0x0D83] Midgar Train Flags.
    quint8 z_27[64];            // [0x0D84] UNKNOWN DATA
    FF7CHOCOBO chocobos[4];     // [0x0DC4] Chocobo slots
    quint8 z_28[32];            // [0x0E04] UNKNOWN DATA
    quint16 coster_2;           // [0x0E24] Coster 2nd place score
    quint16 coster_3;           // [0x0E26] Coster 3rd place score
    quint8 z_29[17];            // [0x0E28] UNKNOWN DATA
    quint16 coster_1;           // [0x0E39] Coster 1st place
    quint8 z_30[105];           // [0x0E3C] UNKNOWN DATA
    qint8 disc;                 // [0x0EA4] Current CD
    quint8 z_31[1];             // [0x0EA5] UNKNOWN DATA
    quint8 intbombing;          // [0x0EA6] 0x14 On Start of Bombing Mission , 0x56 On first Save..
    quint8 z_32[3];             // [0x0EA7] UNKNOWN DATA
    quint16 steps;              // [0x0EAA] Number of steps used in glacear to make you pass out @ 544 steps
    quint8 z_33[22];            // [0x0EAC] Unknown
    quint8 field_help;          // [0x0EC2] Show field hand 1=on 0=off
    quint8 z_34[1];             // [0x0EC3] UNKNOWN
    quint8 chocobonames[6][6];  // [0x0EC4] <-OK Chocobo names
    quint16 chocostaminas[6];   // [0x0EE8] Chocobo staminas 12 bytes
    quint8 reg_vinny;           // [0x0EF4] 0xFF for true 0xFB false (vincent a regualar?)
    quint8 z_35[23];            // [0x0EF5] UNKNOWN DATA
    quint8 location[24];        // [0x0F0C] Location String
    quint8 z_36[5];             // [0x0F24] UNKNOWN DATA
    quint8 tut_save;            // [0x0F29] Have we seen save tut ? 0x3A true , 0x32 false
    quint8 z_37[50];            // [0x0F2A] UNKNOWN DATA
    quint32 l_world;            // [0x0F5C] coords of the leader on the world map part 1 (X, id, angle)
    quint32 l_world2;           // [0x0F60] leader coords part 2 (Y,Z)
    quint32 uw_world;           // [0x0F64] unknown? coords part 1
    quint32 uw_world2;          // [0x0F68] unknown weapon? coords part2
    quint32 tc_world;           // [0x0F6C] tiny bronco/chocobo coords part 1
    quint32 tc_world2;          // [0x0F70] tiny bronco/chocobo coords part2
    quint32 bh_world;           // [0x0F74] Bronco / highwind coords 1
    quint32 bh_world2;          // [0x0F78] brono /highwind coords 2
    quint32 sub_world;          // [0x0F7C] sub on world part 1
    quint32 sub_world2;         // [0x0F80] sub on world part 2
    quint32 durw_world;         // [0x0F84] Diamond/ Ultimate And Ruby Weapons Coords.
    quint32 durw_world2;        // [0x0F88] Diamond/ Ultimate And Ruby Weapons Coords.
    quint16 pole1_x;            // [0x0F8C] 1st Snow Pole X Coordinate.
    quint16 pole1_y;            // [0x0F8E] 1st Snow Pole Y Coordinate.
    quint16 pole2_x;            // [0x0F90] 2nd Snow Pole X Coordinate.
    quint16 pole2_y;            // [0x0F92] 2nd Snow Pole Y Coordinate.
    quint16 pole3_x;            // [0x0F94] 3ed Snow Pole X Coordinate.
    quint16 pole3_y;            // [0x0F96] 3ed Snow Pole Y Coordinate.
    quint8 z_38[236];           // [0x0F98] UNKNOWN
    FF7CHOCOBO choco56[2];      // [0x1084] Chocobo slots 5-6
    quint16 phsmask;            // [0x10A4] who is allowed in the phs
    quint16 unlockedchars;      // [0x10A6] who is visible in the phs
    quint8 z_39[48];            // [0x10A8] UNKNOWN DATA
    quint8 battlespeed;         // [0x10D8] Battle Speed
    quint8 battlemspeed;        // [0x10D9] Battle Message Speed
    quint8 options1;            // [0x10DA] Options 1
    quint8 options2;            // [0x10DB] Options 2
    quint8 controller_map[16];  // [0x10DC] controller mapping?
    quint8 fieldmspeed;         // [0x10EC] Message Speed On field
    quint8 z_40[7];             // [0x10ED] UNKNOWN DATA
}__attribute__((__packed__));
/* FF7HEADFOOT FORMAT COMPATIBILITY (Vegeta_Ss4) v0.8.3*/
    struct FF7HEADFOOT {
    quint8 sl_header[0x0200];       // [0x0000] Slot Header
    quint8 sl_footer[0x0D0C];       // [0x0000] Slot Footer
}__attribute__((__packed__));

#endif // FF7SAVE_TYPES_H
