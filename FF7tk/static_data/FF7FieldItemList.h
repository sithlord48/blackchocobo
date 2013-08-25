/****************************************************************************/
//    copyright 2013  Chris Rizzitello <sithlord48@gmail.com>               //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the tsplied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
//
#ifndef FF7FIELDITEMLIST_H
#define FF7FIELDITEMLIST_H

#include<QStringList>

struct FieldItemList
{
  QList<quint16> Offset;
  QList<quint8> Bit;
  QStringList Maps;
  QString Text;
};

class FF7FieldItemList
{
public:
    FF7FieldItemList();
    QList<quint16> offset(int index);
    QList<quint8> bit(int index);
    QStringList maps(int index);
    QString text(int index);
    int count();
};

static FieldItemList FILIST[]=
{//don't forget to update count on entry
    {QList<quint16>()<<0x0BC8,QList<quint8>()<<0,QStringList()<<"mds7st1",QT_TRANSLATE_NOOP("FieldItems","Hi-Potion")},
    {QList<quint16>()<<0x0BC8,QList<quint8>()<<1,QStringList()<<"mds7st1",QT_TRANSLATE_NOOP("FieldItems","Echo Screen")},
    {QList<quint16>()<<0x0BC8,QList<quint8>()<<2,QStringList()<<"mds7st2",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0BC8,QList<quint8>()<<3,QStringList()<<"mds7st2",QT_TRANSLATE_NOOP("FieldItems","Ether")},
    {QList<quint16>()<<0x0BC8,QList<quint8>()<<4,QStringList()<<"mds7st1",QT_TRANSLATE_NOOP("FieldItems","Hi-Potion")},
    {QList<quint16>()<<0x0BC8,QList<quint8>()<<5,QStringList()<<"mds7st1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0BC8,QList<quint8>()<<6,QStringList()<<"mds7st1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0BC8,QList<quint8>()<<7,QStringList()<<"mds7st2",QT_TRANSLATE_NOOP("FieldItems","Hi-Potion")},

    {QList<quint16>()<<0x0BD4,QList<quint8>()<<0,QStringList()<<"md8_3",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<1,QStringList()<<"ealin_1",QT_TRANSLATE_NOOP("FieldItems","Phoenix Down")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<2,QStringList()<<"eals_1",QT_TRANSLATE_NOOP("FieldItems","Ether")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<3,QStringList()<<"eals_1",QT_TRANSLATE_NOOP("FieldItems","Cover")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<4,QStringList()<<"farm",QT_TRANSLATE_NOOP("FieldItems","Choco/Mog")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<5,QStringList()<<"mds6_22",QT_TRANSLATE_NOOP("FieldItems","Sense")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<6,QStringList()<<"crcin_2",QT_TRANSLATE_NOOP("FieldItems","Ramuh")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<7,QStringList()<<"zz1",QT_TRANSLATE_NOOP("FieldItems","Mythril")},

    {QList<quint16>()<<0x0BD5,QList<quint8>()<<0,QStringList()<<"zz5",QT_TRANSLATE_NOOP("FieldItems","Mime")},
    {QList<quint16>()<<0x0BD5,QList<quint8>()<<1,QStringList()<<"zz6",QT_TRANSLATE_NOOP("FieldItems","HP <-> MP")},
    {QList<quint16>()<<0x0BD5,QList<quint8>()<<2,QStringList()<<"zz7",QT_TRANSLATE_NOOP("FieldItems","Quadra Magic")},
    {QList<quint16>()<<0x0BD5,QList<quint8>()<<3,QStringList()<<"zz8",QT_TRANSLATE_NOOP("FieldItems","Knights of the Round")},

    {QList<quint16>()<<0x0FA4,QList<quint8>()<<0,QStringList()<<"",""},
    {QList<quint16>()<<0x0FA4,QList<quint8>()<<1,QStringList()<<"gaiin_4",QT_TRANSLATE_NOOP("FieldItems","Enhance Sword")},
    {QList<quint16>()<<0x0FA4,QList<quint8>()<<2,QStringList()<<"gaiin_5",QT_TRANSLATE_NOOP("FieldItems","Fire Armlet")},
    {QList<quint16>()<<0x0FA4,QList<quint8>()<<3,QStringList()<<"gaiin_3",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
    {QList<quint16>()<<0x0FA4,QList<quint8>()<<4,QStringList()<<"gaiin_3",QT_TRANSLATE_NOOP("FieldItems","Speed Source")},
    {QList<quint16>()<<0x0FA4,QList<quint8>()<<5,QStringList()<<"gaiin_1",QT_TRANSLATE_NOOP("FieldItems","Javelin")},
    {QList<quint16>()<<0x0FA4,QList<quint8>()<<6,QStringList()<<"gaiin_5",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
    {QList<quint16>()<<0x0FA4,QList<quint8>()<<7,QStringList()<<"gaiin_1",QT_TRANSLATE_NOOP("FieldItems","Ribbon")},

    {QList<quint16>()<<0x0FA5,QList<quint8>()<<0,QStringList()<<"ncoin1",QT_TRANSLATE_NOOP("FieldItems","Ether")},
    {QList<quint16>()<<0x0FA5,QList<quint8>()<<1,QStringList()<<"ncoin3",QT_TRANSLATE_NOOP("FieldItems","Catastrophe")},
    {QList<quint16>()<<0x0FA5,QList<quint8>()<<2,QStringList()<<"snmin2",QT_TRANSLATE_NOOP("FieldItems","Hero Drink")},
    {QList<quint16>()<<0x0FA5,QList<quint8>()<<3,QStringList()<<"snmin2",QT_TRANSLATE_NOOP("FieldItems","Vaccine")},
    {QList<quint16>()<<0x0FA5,QList<quint8>()<<4,QStringList()<<"sninn",QT_TRANSLATE_NOOP("FieldItems","X-Potion")},
    {QList<quint16>()<<0x0FA5,QList<quint8>()<<5,QStringList()<<"snmayor",QT_TRANSLATE_NOOP("FieldItems","Turbo Ether")},
    {QList<quint16>()<<0x0FA5,QList<quint8>()<<6,QStringList()<<"",""},
    {QList<quint16>()<<0x0FA5,QList<quint8>()<<7,QStringList()<<"",""},

    {QList<quint16>()<<0x0FA6,QList<quint8>()<<0,QStringList()<<"trnad_2",QT_TRANSLATE_NOOP("FieldItems","Neo Bahamut")},
    {QList<quint16>()<<0x0FA6,QList<quint8>()<<1,QStringList()<<"trnad_4",QT_TRANSLATE_NOOP("FieldItems","Poison Ring")},
    {QList<quint16>()<<0x0FA6,QList<quint8>()<<2,QStringList()<<"trnad_3",QT_TRANSLATE_NOOP("FieldItems","Hero Drink")},
    {QList<quint16>()<<0x0FA6,QList<quint8>()<<3,QStringList()<<"trnad_4",QT_TRANSLATE_NOOP("FieldItems","MP Turbo")},
    {QList<quint16>()<<0x0FA6,QList<quint8>()<<4,QStringList()<<"",""},
    {QList<quint16>()<<0x0FA6,QList<quint8>()<<5,QStringList()<<"",""},
    {QList<quint16>()<<0x0FA6,QList<quint8>()<<6,QStringList()<<"",""},
    {QList<quint16>()<<0x0FA6,QList<quint8>()<<7,QStringList()<<"",""},


    {QList<quint16>()<<0x0FC4,QList<quint8>()<<0,QStringList()<<"md1stin",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<1,QStringList()<<"md1stin",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<2,QStringList()<<"nmkin_3",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<3,QStringList()<<"nmkin_1",QT_TRANSLATE_NOOP("FieldItems","Phoenix Down")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<4,QStringList()<<"blin67_1",QT_TRANSLATE_NOOP("FieldItems","Poison")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<5,QStringList()<<"colne_b1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<6,QStringList()<<"",""},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<7,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("FieldItems","Potion")},

    {QList<quint16>()<<0x0FC5,QList<quint8>()<<0,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<1,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<2,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<3,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("FieldItems","Bolt Armlet")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<4,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("FieldItems","HypnoCrown")}, // add var[5][58] == 1 to this.
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<5,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<6,QStringList()<<"smkin_1",QT_TRANSLATE_NOOP("FieldItems","Ether")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<7,QStringList()<<"slfrst_2",QT_TRANSLATE_NOOP("FieldItems","Kujata")},

    {QList<quint16>()<<0x0FC6<<0x0FC6,QList<quint8>()<<0<<1,QStringList()<<"sininb42",QT_TRANSLATE_NOOP("FieldItems","Destruct")},
    {QList<quint16>()<<0x0FC6<<0x0FC6,QList<quint8>()<<2<<3,QStringList()<<"blin68_1"<<"blin68_2",QT_TRANSLATE_NOOP("FieldItems","Enemy Skill")},
    {QList<quint16>()<<0x0FC6<<0x0FC6,QList<quint8>()<<4<<5,QStringList()<<"sinin2_1",QT_TRANSLATE_NOOP("FieldItems","Odin")},
    {QList<quint16>()<<0x0FC6,QList<quint8>()<<6,QStringList()<<"nvdun1",QT_TRANSLATE_NOOP("FieldItems","Counter")},
    {QList<quint16>()<<0x0FC6,QList<quint8>()<<7,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("FieldItems","Magic Plus")},

    {QList<quint16>()<<0x0FC7,QList<quint8>()<<0,QStringList()<<"colne_b1",QT_TRANSLATE_NOOP("FieldItems","Steal")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<1,QStringList()<<"sinin1_2",QT_TRANSLATE_NOOP("FieldItems","Twin Viper")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<2,QStringList()<<"sinin1_2",QT_TRANSLATE_NOOP("FieldItems","Silver M-phone")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<3,QStringList()<<"sinin2_1",QT_TRANSLATE_NOOP("FieldItems","Enemy Launcher")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<4,QStringList()<<"sinin2_2",QT_TRANSLATE_NOOP("FieldItems","Magic Source")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<5,QStringList()<<"bonevil",QT_TRANSLATE_NOOP("FieldItems","Buntline")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<6,QStringList()<<"loslake1",QT_TRANSLATE_NOOP("FieldItems","Aurora Armlet")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<7,QStringList()<<"sango3",QT_TRANSLATE_NOOP("FieldItems","Viper Halberd")},

    {QList<quint16>()<<0x0FC8,QList<quint8>()<<0,QStringList()<<"mtnvl2",QT_TRANSLATE_NOOP("FieldItems","Rune Blade")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<1,QStringList()<<"mtnvl2",QT_TRANSLATE_NOOP("FieldItems","Plus Barrette")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<2,QStringList()<<"nvdun1",QT_TRANSLATE_NOOP("FieldItems","Powersoul")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<3,QStringList()<<"nvdun4",QT_TRANSLATE_NOOP("FieldItems","Sniper CR")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<4,QStringList()<<"nvdun2",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<5,QStringList()<<"nvdun1",QT_TRANSLATE_NOOP("FieldItems","All")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<6,QStringList()<<"nvdun3",QT_TRANSLATE_NOOP("FieldItems","Elemental")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<7,QStringList()<<"",""},

    {QList<quint16>()<<0x0FC9,QList<quint8>()<<0,QStringList()<<"sundun_2",QT_TRANSLATE_NOOP("FieldItems","Power Source")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<1,QStringList()<<"sango1",QT_TRANSLATE_NOOP("FieldItems","Water Ring")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<2,QStringList()<<"anfrst_2",QT_TRANSLATE_NOOP("FieldItems","Typhon")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<3,QStringList()<<"anfrst_3",QT_TRANSLATE_NOOP("FieldItems","Supershot ST")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<4,QStringList()<<"anfrst_1",QT_TRANSLATE_NOOP("FieldItems","Slash-All")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<5,QStringList()<<"anfrst_1",QT_TRANSLATE_NOOP("FieldItems","Minerva Band")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<6,QStringList()<<"anfrst_5",QT_TRANSLATE_NOOP("FieldItems","Apocalypse")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<7,QStringList()<<"anfrst_5",QT_TRANSLATE_NOOP("FieldItems","Elixir")},

    {QList<quint16>()<<0x0FCA,QList<quint8>()<<0,QStringList()<<"anfrst_3",QT_TRANSLATE_NOOP("FieldItems","Spring Gun Clip")},
    {QList<quint16>()<<0x0FCA,QList<quint8>()<<1,QStringList()<<"bonevil",QT_TRANSLATE_NOOP("FieldItems","Mop")},
    {QList<quint16>()<<0x0FCA,QList<quint8>()<<2,QStringList()<<"bonevil",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},
    {QList<quint16>()<<0x0FCA,QList<quint8>()<<3,QStringList()<<"blackbg1"<<"mds5_5"<<"bonevil",QT_TRANSLATE_NOOP("FieldItems","Key To Sector 5")},

    {QList<quint16>()<<0x0FF4,QList<quint8>()<<0,QStringList()<<"4sbwy_6",QT_TRANSLATE_NOOP("FieldItems","Tent")},
    {QList<quint16>()<<0x0FF4,QList<quint8>()<<1,QStringList()<<"4sbwy_3",QT_TRANSLATE_NOOP("FieldItems","Potion")},
    {QList<quint16>()<<0x0FF4,QList<quint8>()<<2,QStringList()<<"4sbwy_1",QT_TRANSLATE_NOOP("Items","Ether")},
    {QList<quint16>()<<0x0FF4,QList<quint8>()<<3,QStringList()<<"psdun_3",QT_TRANSLATE_NOOP("FieldItems","Ether")},
    {QList<quint16>()<<0x0FF4,QList<quint8>()<<4,QStringList()<<"psdun_4",QT_TRANSLATE_NOOP("FieldItems","Hi-Potion")},
    {QList<quint16>()<<0x0FF4,QList<quint8>()<<5,QStringList()<<"psdun_4",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
    {QList<quint16>()<<0x0FF4,QList<quint8>()<<6,QStringList()<<"psdun_3",QT_TRANSLATE_NOOP("FieldItems","Long Range")},
    {QList<quint16>()<<0x0FF4,QList<quint8>()<<7,QStringList()<<"gnmk",QT_TRANSLATE_NOOP("FieldItems","Titan")},

    {QList<quint16>()<<0x0FF5,QList<quint8>()<<0,QStringList()<<"elmin2_2",QT_TRANSLATE_NOOP("FieldItems","Ether")},
    {QList<quint16>()<<0x0FF5,QList<quint8>()<<1,QStringList()<<"losin1",QT_TRANSLATE_NOOP("FieldItems","Comet")},
    {QList<quint16>()<<0x0FF5,QList<quint8>()<<2,QStringList()<<"gonjun1",QT_TRANSLATE_NOOP("FieldItems","Deathblow")},
    {QList<quint16>()<<0x0FF5,QList<quint8>()<<3,QStringList()<<"q_4",QT_TRANSLATE_NOOP("FieldItems","Hades")},
    {QList<quint16>()<<0x0FF5,QList<quint8>()<<4,QStringList()<<"q_4",QT_TRANSLATE_NOOP("FieldItems","Outsider")},
    {QList<quint16>()<<0x0FF5,QList<quint8>()<<5,QStringList()<<"q_3",QT_TRANSLATE_NOOP("FieldItems","Escort Guard")},
    {QList<quint16>()<<0x0FF5,QList<quint8>()<<6,QStringList()<<"q_3",QT_TRANSLATE_NOOP("FieldItems","Conformer")},
    {QList<quint16>()<<0x0FF5,QList<quint8>()<<7,QStringList()<<"q_4",QT_TRANSLATE_NOOP("FieldItems","Spirit Lance")},

    {QList<quint16>()<<0x0FF6,QList<quint8>()<<0,QStringList()<<"q_1",QT_TRANSLATE_NOOP("FieldItems","Heaven's Cloud")},
    {QList<quint16>()<<0x0FF6,QList<quint8>()<<1,QStringList()<<"q_3",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},
    {QList<quint16>()<<0x0FF6,QList<quint8>()<<2,QStringList()<<"q_4",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},
    {QList<quint16>()<<0x0FF6,QList<quint8>()<<3,QStringList()<<"losinn",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
    {QList<quint16>()<<0x0FF6,QList<quint8>()<<4,QStringList()<<"losin2",QT_TRANSLATE_NOOP("FieldItems","Guard Source")},
    {QList<quint16>()<<0x0FF6,QList<quint8>()<<5,QStringList()<<"losin3",QT_TRANSLATE_NOOP("FieldItems","Magic Source")},
    {QList<quint16>()<<0x0FF6,QList<quint8>()<<6,QStringList()<<"las1_2"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Elixir")}, //also needs to edit 11[142]:4 (field var) on las4_0
    {QList<quint16>()<<0x0FF6,QList<quint8>()<<7,QStringList()<<"las1_2"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Mystile")}, //also needs to edit 11[142]:1 (field var) on las4_0
 //Below Should Be Tested.
    {QList<quint16>()<<0x0FF7,QList<quint8>()<<0,QStringList()<<"las1_2"<<"las1_3"<<"las0_4",QT_TRANSLATE_NOOP("FieldItems","Speed Source")}, //also needs to edit 11[142]:3 on las4_0
    {QList<quint16>()<<0x0FF7,QList<quint8>()<<1,QStringList()<<"las1_3",QT_TRANSLATE_NOOP("FieldItems","Tetra Elemental")},
    {QList<quint16>()<<0x0FF7,QList<quint8>()<<2,QStringList()<<"las1_3"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},// also needs to edit 11[142]:6 on las4_0
    {QList<quint16>()<<0x0FF7,QList<quint8>()<<3,QStringList()<<"las1_3"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Megalixir")}, // also needs to edit 11[142]:2 on las4_0
    {QList<quint16>()<<0x0FF7,QList<quint8>()<<4,QStringList()<<"las0_5",QT_TRANSLATE_NOOP("FieldItems","Power Source")},
    {QList<quint16>()<<0x0FF7,QList<quint8>()<<5,QStringList()<<"las0_5",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
    {QList<quint16>()<<0x0FF7,QList<quint8>()<<6,QStringList()<<"las0_4"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Guard Source")}, //also needs to edit 11[142]:0 (field var) on las4_0
    {QList<quint16>()<<0x0FF7,QList<quint8>()<<7,QStringList()<<"las0_5"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Mind Source")}, //also needs to edit 11[142]:2 (field var) on las4_0

    {QList<quint16>()<<0x0FF8,QList<quint8>()<<0,QStringList()<<"goson",QT_TRANSLATE_NOOP("FieldItems","White M-phone")},
    {QList<quint16>()<<0x0FF8,QList<quint8>()<<1,QStringList()<<"gninn",QT_TRANSLATE_NOOP("FieldItems","X-Potion")},
    {QList<quint16>()<<0x0FF8,QList<quint8>()<<2,QStringList()<<"rktsid",QT_TRANSLATE_NOOP("FieldItems","Drill Arm")},
    {QList<quint16>()<<0x0FF8,QList<quint8>()<<3,QStringList()<<"rktmin2",QT_TRANSLATE_NOOP("FieldItems","Power Source")},
    {QList<quint16>()<<0x0FF8,QList<quint8>()<<4,QStringList()<<"rckt",QT_TRANSLATE_NOOP("FieldItems","Yoshiyuki")},
    {QList<quint16>()<<0x0FF8,QList<quint8>()<<5,QStringList()<<"rckt2",QT_TRANSLATE_NOOP("FieldItems","Venus Gospel")},
    {QList<quint16>()<<0x0FF8,QList<quint8>()<<6,QStringList()<<"las0_4",QT_TRANSLATE_NOOP("FieldItems","Save Crystal")},
    {QList<quint16>()<<0x0FF8,QList<quint8>()<<7,QStringList()<<"elmtow",QT_TRANSLATE_NOOP("FieldItems","Peacemaker")},

    {QList<quint16>()<<0x0FF9,QList<quint8>()<<0,QStringList()<<"losinn",QT_TRANSLATE_NOOP("FieldItems","Enemy Skill")},
    {QList<quint16>()<<0x0FF9,QList<quint8>()<<1,QStringList()<<"elmin1_1",QT_TRANSLATE_NOOP("FieldItems","Ether")},
    {QList<quint16>()<<0x0FF9,QList<quint8>()<<2,QStringList()<<"las0_5",QT_TRANSLATE_NOOP("FieldItems","Magic Source")},
    {QList<quint16>()<<0x0FF9,QList<quint8>()<<3,QStringList()<<"elmin3_2",QT_TRANSLATE_NOOP("FieldItems","Guard Source")},
    {QList<quint16>()<<0x0FF9,QList<quint8>()<<4,QStringList()<<"elmin4_1",QT_TRANSLATE_NOOP("FieldItems","Ether")}, // shown if(5[9] ==0)
    {QList<quint16>()<<0x0FF9,QList<quint8>()<<5,QStringList()<<"rkt_w",QT_TRANSLATE_NOOP("FieldItems","Fourth Bracelet")}, // shown if gamemoment >999
    {QList<quint16>()<<0x0FF9,QList<quint8>()<<6,QStringList()<<"rkt_i",QT_TRANSLATE_NOOP("FieldItems","Guard Source")}, // shown if gamemoment >999
    {QList<quint16>()<<0x0FF9,QList<quint8>()<<7,QStringList()<<"elminn_2",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},

    {QList<quint16>()<<0x0FFA,QList<quint8>()<<0,QStringList()<<"las0_5",QT_TRANSLATE_NOOP("FieldItems","Guard Source")},
    {QList<quint16>()<<0x0FFA,QList<quint8>()<<1,QStringList()<<"q_3",QT_TRANSLATE_NOOP("FieldItems","Double Cut")},
    {QList<quint16>()<<0x0FFA,QList<quint8>()<<2,QStringList()<<"q_4",QT_TRANSLATE_NOOP("FieldItems","Highwind")},
    {QList<quint16>()<<0x0FFA,QList<quint8>()<<3,QStringList()<<"las0_5",QT_TRANSLATE_NOOP("FieldItems","HP Absorb")},
    {QList<quint16>()<<0x0FFA,QList<quint8>()<<4,QStringList()<<"psdun_2",QT_TRANSLATE_NOOP("FieldItems","Mind Source")},
    {QList<quint16>()<<0x0FFA,QList<quint8>()<<5,QStringList()<<"psdun_3",QT_TRANSLATE_NOOP("FieldItems","Tent")},
    {QList<quint16>()<<0x0FFA,QList<quint8>()<<6,QStringList()<<"",""},
    {QList<quint16>()<<0x0FFA,QList<quint8>()<<7,QStringList()<<"",""}

};
#endif // FF7FIELDITEMLIST_H
