/****************************************************************************/
//    copyright 2010, 2011 Chris Rizzitello <sithlord48@gmail.com>          //
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
#include <QCoreApplication>
#include <QTextCodec>

int ff7__checksum(void * qw );
void fix_pc_bytemask(FF7*ff7 ,int,bool);
void fix_psx_header(FF7*ff7,int);
void fix_vmc_header(FF7*ff7);
QString avatar_style(int);

class locations
{
public:
    QString loc_name(int);
    QString map_id(int);
    QString loc_id(int);
    QString x(int);
    QString y(int);
    QString z(int);
    int len(void);
};
class ff7names
{
public:
    QString ItemNames(int);
    QString MateriaNames(int);
    QString MateriaStats(int);
    QString MateriaSkills(int,int);
};

class TEXT{
private:
    QString eng;
    QString jap;
    QString jap_fa;
    QString jap_fb;
    QString jap_fc;
    QString jap_fd;
    QString jap_fe;
    bool in_ja;
    QString character(quint8 ord, quint8 table);
public:
    TEXT();
    void init(bool);
    QString toPC(QByteArray text);
    QByteArray toFF7(QString string);
};

struct LOCATION {//Location Table Stuff
    QString location;
    QString map_id;
    QString loc_id;
    QString x;
    QString y;
    QString z;
};
static ITEM Items[]=
 {//ITEMS 0-105,
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
  {":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},{":/icon/item",0,0},
//nothing 106-127
  {'\0',0,0},{'\0',0,0},{'\0',0,0},{'\0',0,0},{'\0',0,0},
  {'\0',0,0},{'\0',0,0},{'\0',0,0},{'\0',0,0},{'\0',0,0},
  {'\0',0,0},{'\0',0,0},{'\0',0,0},{'\0',0,0},{'\0',0,0},
  {'\0',0,0},{'\0',0,0},{'\0',0,0},{'\0',0,0},{'\0',0,0},
  {'\0',0,0},{'\0',0,0},{'\0',0,0},
//cloud weapons 128 -143
  {":/icon/cloud_weapon",2,1},{":/icon/cloud_weapon",3,1},{":/icon/cloud_weapon",4,1},
  {":/icon/cloud_weapon",4,2},{":/icon/cloud_weapon",8,4},{":/icon/cloud_weapon",6,2},
  {":/icon/cloud_weapon",6,3},{":/icon/cloud_weapon",3,0},{":/icon/cloud_weapon",4,0},
  {":/icon/cloud_weapon",5,2},{":/icon/cloud_weapon",0,0},{":/icon/cloud_weapon",2,0},
  {":/icon/cloud_weapon",3,0},{":/icon/cloud_weapon",6,0},{":/icon/cloud_weapon",6,3},
  {":/icon/cloud_weapon",8,4},
//tifa's weapons 144-159
  {":/icon/tifa_weapon",1,0},{":/icon/tifa_weapon",2,1},{":/icon/tifa_weapon",3,1},
  {":/icon/tifa_weapon",4,1},{":/icon/tifa_weapon",4,2},{":/icon/tifa_weapon",5,2},
  {":/icon/tifa_weapon",6,2},{":/icon/tifa_weapon",6,3},{":/icon/tifa_weapon",3,0},
  {":/icon/tifa_weapon",4,0},{":/icon/tifa_weapon",8,1},{":/icon/tifa_weapon",0,0},
  {":/icon/tifa_weapon",4,0},{":/icon/tifa_weapon",6,0},{":/icon/tifa_weapon",4,2},
  {":/icon/tifa_weapon",8,4},
// barret's weapons 160-175
  {":/icon/barret_weapon",1,0},{":/icon/barret_weapon",2,1},{":/icon/barret_weapon",3,1},
  {":/icon/barret_weapon",4,2},{":/icon/barret_weapon",4,2},{":/icon/barret_weapon",5,2},
  {":/icon/barret_weapon",6,2},{":/icon/barret_weapon",6,3},{":/icon/barret_weapon",3,0},
  {":/icon/barret_weapon",4,0},{":/icon/barret_weapon",8,4},{":/icon/barret_weapon",0,0},
  {":/icon/barret_weapon",5,1},{":/icon/barret_weapon",6,3},{":/icon/barret_weapon",6,3},
  {":/icon/barret_weapon",8,4},
//red's weapons 176-189
  {":/icon/red_weapon",3,1},{":/icon/red_weapon",4,1},{":/icon/red_weapon",4,2},
  {":/icon/red_weapon",5,2},{":/icon/red_weapon",6,2},{":/icon/red_weapon",6,3},
  {":/icon/red_weapon",3,0},{":/icon/red_weapon",4,0},{":/icon/red_weapon",8,0},
  {":/icon/red_weapon",0,0},{":/icon/red_weapon",4,0},{":/icon/red_weapon",6,0},
  {":/icon/red_weapon",6,3},{":/icon/red_weapon",8,4},
//aeris weapons 190-200
  {":/icon/aeris_weapon",2,1},{":/icon/aeris_weapon",3,1},{":/icon/aeris_weapon",3,1},
  {":/icon/aeris_weapon",4,1},{":/icon/aeris_weapon",4,2},{":/icon/aeris_weapon",5,2},
  {":/icon/aeris_weapon",3,0},{":/icon/aeris_weapon",4,0},{":/icon/aeris_weapon",7,0},
  {":/icon/aeris_weapon",0,0},{":/icon/aeris_weapon",7,3},
//cid weapons 201-214
  {":/icon/cid_weapon",1,0},{":/icon/cid_weapon",5,2},{":/icon/cid_weapon",6,0},
  {":/icon/cid_weapon",6,2},{":/icon/cid_weapon",6,3},{":/icon/cid_weapon",4,0},
  {":/icon/cid_weapon",5,2},{":/icon/cid_weapon",6,3},{":/icon/cid_weapon",0,0},
  {":/icon/cid_weapon",8,0},{":/icon/cid_weapon",2,1},{":/icon/cid_weapon",6,0},
  {":/icon/cid_weapon",4,2},{":/icon/cid_weapon",8,4},
//yuffie weapons 215-228
  {":/icon/yuffie_weapon",3,1},{":/icon/yuffie_weapon",4,1},{":/icon/yuffie_weapon",4,2},
  {":/icon/yuffie_weapon",5,2},{":/icon/yuffie_weapon",6,2},{":/icon/yuffie_weapon",6,3},
  {":/icon/yuffie_weapon",3,0},{":/icon/yuffie_weapon",4,0},{":/icon/yuffie_weapon",8,1},
  {":/icon/yuffie_weapon",0,0},{":/icon/yuffie_weapon",3,0},{":/icon/yuffie_weapon",4,2},
  {":/icon/yuffie_weapon",8,2},{":/icon/yuffie_weapon",8,4},
//cait sith weapons 229-241
  {":/icon/cait_weapon",4,2},{":/icon/cait_weapon",4,2},{":/icon/cait_weapon",5,2},
  {":/icon/cait_weapon",6,2},{":/icon/cait_weapon",6,3},{":/icon/cait_weapon",3,0},
  {":/icon/cait_weapon",4,0},{":/icon/cait_weapon",8,0},{":/icon/cait_weapon",0,0},
  {":/icon/cait_weapon",8,4},{":/icon/cait_weapon",6,3},{":/icon/cait_weapon",8,4},
  {":/icon/cait_weapon",8,4},
//vincent weapons... 242-254
  {":/icon/vincent_weapon",4,1},{":/icon/vincent_weapon",4,1},{":/icon/vincent_weapon",5,2},
  {":/icon/vincent_weapon",6,2},{":/icon/vincent_weapon",6,3},{":/icon/vincent_weapon",3,1},
  {":/icon/vincent_weapon",4,2},{":/icon/vincent_weapon",8,4},{":/icon/vincent_weapon",0,0},
  {":/icon/vincent_weapon",4,2},{":/icon/vincent_weapon",6,3},{":/icon/vincent_weapon",8,2},
  {":/icon/vincent_weapon",8,4},
//sepi weapon =255
  {":/icon/item",5,2},
//armor  256-287
  {":/icon/armor",0,0},{":/icon/armor",1,0},{":/icon/armor",2,0},{":/icon/armor",2,1},
  {":/icon/armor",3,1},{":/icon/armor",4,1},{":/icon/armor",4,2},{":/icon/armor",5,2},
  {":/icon/armor",6,3},{":/icon/armor",2,0},{":/icon/armor",4,0},{":/icon/armor",7,0},
  {":/icon/armor",8,4},{":/icon/armor",2,1},{":/icon/armor",5,2},{":/icon/armor",6,3},
  {":/icon/armor",4,2},{":/icon/armor",5,2},{":/icon/armor",4,2},{":/icon/armor",4,1},
  {":/icon/armor",6,3},{":/icon/armor",4,0},{":/icon/armor",4,2},{":/icon/armor",4,2},
  {":/icon/armor",4,2},{":/icon/armor",6,3},{":/icon/armor",6,3},{":/icon/armor",6,3},
  {":/icon/armor",6,3},{":/icon/armor",0,0},{":/icon/armor",8,0},{":/icon/armor",4,0},
//accessorys 288-319
  {":/icon/accessory",0,0},{":/icon/accessory",0,0},{":/icon/accessory",0,0},
  {":/icon/accessory",0,0},{":/icon/accessory",0,0},{":/icon/accessory",0,0},
  {":/icon/accessory",0,0},{":/icon/accessory",0,0},{":/icon/accessory",0,0},
  {":/icon/accessory",0,0},{":/icon/accessory",0,0},{":/icon/accessory",0,0},
  {":/icon/accessory",0,0},{":/icon/accessory",0,0},{":/icon/accessory",0,0},
  {":/icon/accessory",0,0},{":/icon/accessory",0,0},{":/icon/accessory",0,0},
  {":/icon/accessory",0,0},{":/icon/accessory",0,0},{":/icon/accessory",0,0},
  {":/icon/accessory",0,0},{":/icon/accessory",0,0},{":/icon/accessory",0,0},
  {":/icon/accessory",0,0},{":/icon/accessory",0,0},{":/icon/accessory",0,0},
  {":/icon/accessory",0,0},{":/icon/accessory",0,0},{":/icon/accessory",0,0},
  {":/icon/accessory",0,0},{":/icon/accessory",0,0}
};

static MATERIA Materias[]=
{//ID   hp,mp,str,vit,dex,lck,mag,spi
    {QT_TRANSLATE_NOOP("Materia_Names","MP Plus"),          ":/icon/independent", 0x00,/*{0,0,0,0,0,0,0,0}*/{10000,20000,30000,50000},3,5},
    {QT_TRANSLATE_NOOP("Materia_Names","HP Plus"),          ":/icon/independent", 0x01,/*{0,0,0,0,0,0,0,0}*/{10000,20000,30000,50000},3,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Speed Plus"),       ":/icon/independent", 0x02,/*{0,0,0,0,0,0,0,0}*/{15000,30000,60000,100000},3,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Magic Plus"),       ":/icon/independent", 0x03,/*{0,0,0,0,0,0,0,0}*/{10000,20000,30000,50000},3,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Luck Plus"),        ":/icon/independent", 0x04,/*{0,0,0,0,0,0,0,0}*/{15000,30000,60000,100000},3,5},
    {QT_TRANSLATE_NOOP("Materia_Names","EXP Plus"),         ":/icon/independent", 0x05,/*{0,0,0,0,0,+1,0,0}*/{60000,150000,0,0},3,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Gil Plus"),         ":/icon/independent", 0x06,/*{0,0,0,0,0,+1,0,0}*/{80000,150000,0,0},3,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Enemy Away"),       ":/icon/independent", 0x07,/*{0,0,0,0,0,+1,0,0}*/{10000,50000,0,0},3,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Enemy Lure"),       ":/icon/independent", 0x08,/*{0,0,0,0,0,-1,0,0}*/{10000,50000,0,0},3,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Chocobo Lure"),     ":/icon/independent", 0x09,/*{0,0,0,0,0,+1,0,0}*/{3000,10000,30000,0},3,4},
    {QT_TRANSLATE_NOOP("Materia_Names","Pre-emptive"),      ":/icon/independent", 0x0A,/*{0,0,0,0,+2,0,0,0}*/{8000,20000,40000,80000},3,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Long Range"),       ":/icon/independent", 0x0B,/*{0,0,0,0,0,0,0,0}*/{80000,0,0,0},3,2},
    {QT_TRANSLATE_NOOP("Materia_Names","Mega All"),         ":/icon/independent", 0x0C,/*{0,0,0,0,0,0,0,0}*/{20000,40000,80000,160000},3,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Counter Attack"),   ":/icon/independent", 0x0D,/*{0,0,0,0,0,0,0,0}*/{10000,20000,50000,100000},3,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Slash-All"),        ":/icon/command",     0x0E,/*{0,0,0,0,0,0,0,0}*/{130000,150000,0,0},5,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Double Cut"),       ":/icon/command",     0x0F,/*{0,0,0,0,+2,0,0,0}*/{100000,150000,0,0},5,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Cover"),            ":/icon/independent", 0x10,/*{0,0,0,+1,0,0,0,0}*/{2000,10000,25000,40000},3,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Underwater"),       ":/icon/independent", 0x11,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},3,1},
    {QT_TRANSLATE_NOOP("Materia_Names","HP <-> MP"),        ":/icon/independent", 0x12,/*{0,0,0,0,0,0,0,0}*/{80000,0,0,0},3,2},
    {QT_TRANSLATE_NOOP("Materia_Names","W-Magic"),          ":/icon/command",     0x13,/*{0,0,0,0,0,0,0,0}*/{250000,0,0,0},5,2},
    {QT_TRANSLATE_NOOP("Materia_Names","W-Summon"),         ":/icon/command",     0x14,/*{0,0,0,0,0,0,0,0}*/{250000,0,0,0},5,2},
    {QT_TRANSLATE_NOOP("Materia_Names","W-Item"),           ":/icon/command",     0x15,/*{0,0,0,0,0,0,0,0}*/{250000,0,0,0},5,2},
    {QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),        "",                   0X16,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},0,0},
    {QT_TRANSLATE_NOOP("Materia_Names","All"),              ":/icon/support",     0x17,/*{0,0,0,0,0,0,0,0}*/{1500,6000,18000,35000},4,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Counter"),          ":/icon/support",     0x18,/*{0,0,0,0,0,0,0,0}*/{20000,40000,60000,100000},4,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Magic Counter"),    ":/icon/support",     0x19,/*{0,0,0,0,0,0,0,0}*/{20000,40000,80000,300000},4,5},
    {QT_TRANSLATE_NOOP("Materia_Names","MP Turbo"),         ":/icon/support",     0x1A,/*{0,0,0,0,0,0,0,0}*/{10000,30000,60000,120000},4,5},
    {QT_TRANSLATE_NOOP("Materia_Names","MP Absorb"),        ":/icon/support",     0x1B,/*{0,0,0,0,0,0,0,0}*/{100000,0,0,0},4,2},
    {QT_TRANSLATE_NOOP("Materia_Names","HP Absorb"),        ":/icon/support",     0x1C,/*{0,0,0,0,0,0,0,0}*/{100000,0,0,0},4,2},
    {QT_TRANSLATE_NOOP("Materia_Names","Elemental"),        ":/icon/support",     0x1D,/*{0,0,0,0,0,0,0,0}*/{10000,40000,80000,0},4,4},
    {QT_TRANSLATE_NOOP("Materia_Names","Added Effect"),     ":/icon/support",     0x1E,/*{0,0,0,0,0,0,0,0}*/{100000,0,0,0},4,2},
    {QT_TRANSLATE_NOOP("Materia_Names","Sneak Attack"),     ":/icon/support",     0x1F,/*{0,0,0,0,0,0,0,0}*/{20000,60000,100000,150000},4,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Final Attack"),     ":/icon/support",     0x20,/*{0,0,0,0,0,0,0,0}*/{20000,40000,80000,160000},4,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Added Cut"),        ":/icon/support",     0x21,/*{0,0,0,0,0,0,0,0}*/{200000,0,0,0},4,2},
    {QT_TRANSLATE_NOOP("Materia_Names","Steal-As-Well"),    ":/icon/support",     0x22,/*{0,0,0,0,0,0,0,0}*/{200000,0,0,0},4,2},
    {QT_TRANSLATE_NOOP("Materia_Names","Quadra Magic"),     ":/icon/support",     0x23,/*{0,0,0,0,0,0,0,0}*/{40000,80000,120000,200000},4,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Steal"),            ":/icon/command",     0x24,/*{0,0,0,0,+2,0,0,0}*/{40000,50000,0,0},5,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Sense"),            ":/icon/command",     0x25,/*{0,0,0,0,0,0,0,0}*/{40000,0,0,0},5,2},
    {QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),        "" ,                  0X26,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},0,0},
    {QT_TRANSLATE_NOOP("Materia_Names","Throw"),            ":/icon/command",     0x27,/*{0,0,0,+1,0,0,0,0}*/{45000,60000,0,0},5,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Morph"),            ":/icon/command",     0x28,/*{0,0,0,0,0,0,0,0}*/{100000,0,0,0},5,2},
    {QT_TRANSLATE_NOOP("Materia_Names","Deathblow"),        ":/icon/command",     0x29,/*{0,0,0,0,0,+1,0,0}*/{40000,0,0,0},5,2},
    {QT_TRANSLATE_NOOP("Materia_Names","Manipulate"),       ":/icon/command",     0x2A,/*{0,0,0,0,0,0,0,0}*/{40000,0,0,0},5,2},
    {QT_TRANSLATE_NOOP("Materia_Names","Mime"),             ":/icon/command",     0x2B,/*{0,0,0,0,0,0,0,0}*/{100000,0,0,0},5,2},
    {QT_TRANSLATE_NOOP("Materia_Names","Enemy Skill"),      ":/icon/command",     0x2C,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},5,1},
    {QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),        "",                   0X2D,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},0,0},
    {QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),        "",                   0X2E,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},0,0},
    {QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),        "",                   0X2F,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},0,0},
    {QT_TRANSLATE_NOOP("Materia_Names","Master Command"),   ":/icon/command",     0x30,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},5,1},
    {QT_TRANSLATE_NOOP("Materia_Names","Fire"),             ":/icon/magic",       0x31,/*{-2,+2,-1,0,0,0,+1,0}*/{2000,18000,35000,0},1,4},
    {QT_TRANSLATE_NOOP("Materia_Names","Ice"),              ":/icon/magic",       0x32,/*{-2,+2,-1,0,0,0,+1,0}*/{2000,18000,35000,0},1,4},
    {QT_TRANSLATE_NOOP("Materia_Names","Earth"),            ":/icon/magic",       0x33,/*{-2,+2,-1,0,0,0,+1,0}*/{6000,22000,40000,0},1,4},
    {QT_TRANSLATE_NOOP("Materia_Names","Lightning"),        ":/icon/magic",       0x34,/*{-2,+2,-1,0,0,0,+1,0}*/{2000,18000,35000,0},1,4},
    {QT_TRANSLATE_NOOP("Materia_Names","Restore"),          ":/icon/magic",       0x35,/*{-2,+2,-1,0,0,0,+1,0}*/{2500,17000,25000,40000},1,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Heal"),             ":/icon/magic",       0x36,/*{-2,+2,-1,0,0,0,+1,0}*/{12000,52000,60000,0},1,4},
    {QT_TRANSLATE_NOOP("Materia_Names","Revive"),           ":/icon/magic",       0x37,/*{-5,+5,-2,-1,0,0,+2,+1}*/{45000,55000,0,0},1,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Seal"),             ":/icon/magic",       0x38,/*{-2,+2,-1,0,0,0,+1,0}*/{10000,20000,0,0},1,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Mystify"),          ":/icon/magic",       0x39,/*{-2,+2,-1,0,0,0,+1,0}*/{12000,25000,0,0},1,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Transform"),        ":/icon/magic",       0x3A,/*{-2,+2,-1,0,0,0,+1,0}*/{8000,24000,0,0},1,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Exit"),             ":/icon/magic",       0x3B,/*{-2,+2,-1,0,0,0,+1,0}*/{10000,30000,0,0},1,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Poison"),           ":/icon/magic",       0x3C,/*{-2,+2,-1,0,0,0,+1,0}*/{5000,20000,38000,0},1,4},
    {QT_TRANSLATE_NOOP("Materia_Names","Gravity"),          ":/icon/magic",       0x3D,/*{-2,+2,-1,0,0,0,+1,0}*/{10000,20000,40000,0},1,4},
    {QT_TRANSLATE_NOOP("Materia_Names","Barrier"),          ":/icon/magic",       0x3E,/*{-5,+5,-2,-1,0,0,+2,+1}*/{5000,15000,30000,45000},1,5},
    {QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),        "",                   0X3F,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},0,0},
    {QT_TRANSLATE_NOOP("Materia_Names","Comet"),            ":/icon/magic",       0x40,/*{-5,+5,-2,-1,0,0,+2,+1}*/{12000,60000,0,0},1,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Time"),             ":/icon/magic",       0x41,/*{-5,+5,-2,-1,0,0,+2,+1}*/{10000,20000,42000,0},1,4},
    {QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),        "",                   0X42,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},0,0},
    {QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),        "",                   0X43,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},0,0},
    {QT_TRANSLATE_NOOP("Materia_Names","Destruct"),         ":/icon/magic",       0x44,/*{-5,+5,-2,-1,0,0,+2,+1}*/{6000,10000,45000,0},1,4},
    {QT_TRANSLATE_NOOP("Materia_Names","Contain"),          ":/icon/magic",       0x45,/*{-10,+10,-4,-2,0,0,+4+2}*/{5000,10000,15000,60000},1,5},
    {QT_TRANSLATE_NOOP("Materia_Names","FullCure"),         ":/icon/magic",       0x46,/*{-10,+10,-4,-2,0,0,+4,+2}*/{3000,100000,0,0},1,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Shield"),           ":/icon/magic",       0x47,/*{-10,+10,-4,-2,0,0,+4,+2}*/{10000,100000,0,0},1,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Ultima"),           ":/icon/magic",       0x48,/*{-10,+10,-4,-2,0,0,+4,+2}*/{5000,100000,0,0},1,3},
    {QT_TRANSLATE_NOOP("Materia_Names","Master Magic"),     ":/icon/magic",       0x49,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},1,1},
    {QT_TRANSLATE_NOOP("Materia_Names","Choco/Mog"),        ":/icon/summon",      0x4A,/*{-2,+2,0,0,0,0,+1,0}*/{2000,14000,25000,35000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Shiva"),            ":/icon/summon",      0x4B,/*{-2,+2,0,0,0,0,+1,0}*/{4000,15000,30000,50000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Ifrit"),            ":/icon/summon",      0x4C,/*{-2,+2,0,0,0,0,+1,0}*/{5000,20000,35000,60000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Ramuh"),            ":/icon/summon",      0x4D,/*{-2,+2,0,0,0,0,+1,0}*/{10000,25000,50000,70000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Titan"),            ":/icon/summon",      0x4E,/*{-2,+2,0,0,0,0,+1,0}*/{15000,30000,60000,80000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Odin"),             ":/icon/summon",      0x4F,/*{-5,+5,0,0,0,0,+1,+1}*/{16000,32000,65000,90000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Leviathan"),        ":/icon/summon",      0x50,/*{-5,+5,0,0,0,0,+1,+1}*/{18000,38000,70000,100000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Bahamut"),          ":/icon/summon",      0x51,/*{-5,+5,0,0,0,0,+1,+1}*/{20000,50000,80000,120000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Kujata"),           ":/icon/summon",      0x52,/*{-5,+5,0,0,0,0,+1,+1}*/{22000,60000,90000,140000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Alexander"),        ":/icon/summon",      0x53,/*{-5,+5,0,0,0,0,+1,+1}*/{25000,65000,100000,150000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Phoenix"),          ":/icon/summon",      0x54,/*{-10,+10,0,0,0,0,+2,+2}*/{28000,70000,120000,180000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Neo Bahamut"),      ":/icon/summon",      0x55,/*{-10,+10,0,0,0,0,+2,+2}*/{30000,80000,140000,200000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Hades"),            ":/icon/summon",      0x56,/*{-10,+15,0,0,0,0,+4,+4}*/{35000,120000,150000,250000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Typhon"),           ":/icon/summon",      0x57,/*{-10,+15,0,0,0,0,+4,+4}*/{35000,120000,150000,250000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Bahamut ZERO"),     ":/icon/summon",      0x58,/*{-10,+15,0,0,0,0,+4,+4}*/{35000,120000,150000,250000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Knights of Round"), ":/icon/summon",      0x59,/*{-10,+20,0,0,0,0,+8,+8}*/{50000,200000,300000,500000},2,5},
    {QT_TRANSLATE_NOOP("Materia_Names","Master Summon"),    ":/icon/summon",      0x5A,/*{0,0,0,0,0,0,0,0}*/{0,0,0,0},2,1}
};
#endif // GLOBALS_H


