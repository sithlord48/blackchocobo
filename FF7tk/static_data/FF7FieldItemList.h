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
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
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
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<0,QStringList()<<"md8_3",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<1,QStringList()<<"ealin_1",QT_TRANSLATE_NOOP("Items","Phoenix Down")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<2,QStringList()<<"eals_1",QT_TRANSLATE_NOOP("Items","Ether")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<3,QStringList()<<"eals_1",QT_TRANSLATE_NOOP("Materia_Names","Cover")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<4,QStringList()<<"farm",QT_TRANSLATE_NOOP("Materia_Names","Choco-Mog")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<5,QStringList()<<"mds6_22",QT_TRANSLATE_NOOP("Materia_Names","Sence")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<6,QStringList()<<"crcin_2",QT_TRANSLATE_NOOP("Materia_Names","Ramuh")},
    {QList<quint16>()<<0x0BD4,QList<quint8>()<<7,QStringList()<<"zz1",QT_TRANSLATE_NOOP("KeyItems","Mythril")},

    {QList<quint16>()<<0x0BD5,QList<quint8>()<<0,QStringList()<<"zz5",QT_TRANSLATE_NOOP("Materia_Names","Mime")},
    {QList<quint16>()<<0x0BD5,QList<quint8>()<<1,QStringList()<<"zz6",QT_TRANSLATE_NOOP("Materia_Names","HP <-> MP")},
    {QList<quint16>()<<0x0BD5,QList<quint8>()<<2,QStringList()<<"zz7",QT_TRANSLATE_NOOP("Materia_Names","Quadra Magic")},
    {QList<quint16>()<<0x0BD5,QList<quint8>()<<3,QStringList()<<"zz8",QT_TRANSLATE_NOOP("Materia_Names","Knights Of the Round")},

    {QList<quint16>()<<0x0FC4,QList<quint8>()<<0,QStringList()<<"md1stin",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<1,QStringList()<<"md1stin",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<2,QStringList()<<"nmkin_3",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<3,QStringList()<<"nmkin_1",QT_TRANSLATE_NOOP("Items","Phoenix Down")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<4,QStringList()<<"blin67_1",QT_TRANSLATE_NOOP("Materia_Names","Poison")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<5,QStringList()<<"colne_b1",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<6,QStringList()<<"",""},
    {QList<quint16>()<<0x0FC4,QList<quint8>()<<7,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("Items","Potion")},

    {QList<quint16>()<<0x0FC5,QList<quint8>()<<0,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<1,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<2,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<3,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("Items","Bolt Armlet")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<4,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("Items","HypnoCrown")}, // add var[5][58] == 1 to this.
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<5,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("Items","Megalixir")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<6,QStringList()<<"smkin_1",QT_TRANSLATE_NOOP("Items","Ether")},
    {QList<quint16>()<<0x0FC5,QList<quint8>()<<7,QStringList()<<"slfrst_2",QT_TRANSLATE_NOOP("Materia_Names","Kujata")},

    {QList<quint16>()<<0x0FC6<<0x0FC6,QList<quint8>()<<0<<1,QStringList()<<"sininb42",QT_TRANSLATE_NOOP("Materia_Names","Destruct")},
    {QList<quint16>()<<0x0FC6<<0x0FC6,QList<quint8>()<<2<<3,QStringList()<<"blin68_1"<<"blin68_2",QT_TRANSLATE_NOOP("Materia_Names","Enemy Skill")},
    {QList<quint16>()<<0x0FC6<<0x0FC6,QList<quint8>()<<4<<5,QStringList()<<"sinin2_1",QT_TRANSLATE_NOOP("Materia_Names","Odin")},
    {QList<quint16>()<<0x0FC6,QList<quint8>()<<6,QStringList()<<"nvdun1",QT_TRANSLATE_NOOP("Materia_Names","Counter")},
    {QList<quint16>()<<0x0FC6,QList<quint8>()<<7,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("Materia_Names","Magic Plus")},

    {QList<quint16>()<<0x0FC7,QList<quint8>()<<0,QStringList()<<"colne_b1",QT_TRANSLATE_NOOP("Materia_Names","Steal")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<1,QStringList()<<"sinin1_2",QT_TRANSLATE_NOOP("Items","Twin Viper")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<2,QStringList()<<"sinin1_2",QT_TRANSLATE_NOOP("Items","Silver M-Phone")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<3,QStringList()<<"sinin2_1",QT_TRANSLATE_NOOP("Items","Enemy Launcher")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<4,QStringList()<<"sinin2_2",QT_TRANSLATE_NOOP("Items","Magic Source")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<5,QStringList()<<"bonevil",QT_TRANSLATE_NOOP("Items","Buntline")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<6,QStringList()<<"loslake1",QT_TRANSLATE_NOOP("Items","Aurora Armlet")},
    {QList<quint16>()<<0x0FC7,QList<quint8>()<<7,QStringList()<<"sango3",QT_TRANSLATE_NOOP("Items","Viper Halberd")},

    {QList<quint16>()<<0x0FC8,QList<quint8>()<<0,QStringList()<<"mtnvl2",QT_TRANSLATE_NOOP("Items","Rune Blade")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<1,QStringList()<<"mtnvl2",QT_TRANSLATE_NOOP("Items","Plus Barrette")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<2,QStringList()<<"nvdun1",QT_TRANSLATE_NOOP("Items","Powersoul")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<3,QStringList()<<"nvdun4",QT_TRANSLATE_NOOP("Items","Sniper CR")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<4,QStringList()<<"nvdun2",QT_TRANSLATE_NOOP("Items","Elixir")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<5,QStringList()<<"nvdun1",QT_TRANSLATE_NOOP("Materia_Names","All")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<6,QStringList()<<"nvdun3",QT_TRANSLATE_NOOP("Materia_Names","Elemental")},
    {QList<quint16>()<<0x0FC8,QList<quint8>()<<7,QStringList()<<"",""},

    {QList<quint16>()<<0x0FC9,QList<quint8>()<<0,QStringList()<<"sundun_2",QT_TRANSLATE_NOOP("Items","Power Source")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<1,QStringList()<<"sango1",QT_TRANSLATE_NOOP("Items","Water Ring")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<2,QStringList()<<"anfrst_2",QT_TRANSLATE_NOOP("Materia_Names","Typoon")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<3,QStringList()<<"anfrst_3",QT_TRANSLATE_NOOP("Items","Supershot ST")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<4,QStringList()<<"anfrst_1",QT_TRANSLATE_NOOP("Materia_Names","Slash-All")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<5,QStringList()<<"anfrst_1",QT_TRANSLATE_NOOP("Items","Minerva Band")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<6,QStringList()<<"anfrst_5",QT_TRANSLATE_NOOP("Items","Apocalypse")},
    {QList<quint16>()<<0x0FC9,QList<quint8>()<<7,QStringList()<<"anfrst_5",QT_TRANSLATE_NOOP("Items","Elixir")},

    {QList<quint16>()<<0x0FCA,QList<quint8>()<<0,QStringList()<<"anfrst_3",QT_TRANSLATE_NOOP("Items","Spring Gun Clip")},
    {QList<quint16>()<<0x0FCA,QList<quint8>()<<1,QStringList()<<"bonevil",QT_TRANSLATE_NOOP("Items","Mop")},
    {QList<quint16>()<<0x0FCA,QList<quint8>()<<2,QStringList()<<"bonevil",QT_TRANSLATE_NOOP("Items","Megalixir")},
    {QList<quint16>()<<0x0FCA,QList<quint8>()<<3,QStringList()<<"blackbg1"<<"mds5_5"<<"bonevil",QT_TRANSLATE_NOOP("KeyItems","Key To Sector 5")}
};
#endif // FF7FIELDITEMLIST_H
