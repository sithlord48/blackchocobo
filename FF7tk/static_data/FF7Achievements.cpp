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
#include "FF7Achievements.h"
#include <QFile>
#include <QCoreApplication>

FF7Achievements::FF7Achievements(QObject *parent) :
    QObject(parent)
{
    Achievements = QByteArray("\x00\x00\x00\x00\x00\x00\x00\x00");
}
bool FF7Achievements::openFile(QString fileName)
{
    if(!fileName.isEmpty())
    {
        QFile data(fileName);
        if(data.open(QIODevice::ReadOnly))
        {
            Achievements = data.readAll();
            data.close();
        }
        else{return false;}
        return true;
    }
    return false;
}
bool FF7Achievements::saveFile(QString fileName)
{
    if(!fileName.isEmpty())
    {
        QFile data(fileName);
        if(data.open(QIODevice::WriteOnly))
        {
            data.seek(0);
            data.write(Achievements.data(),8);
            data.close();
        }
        else{return false;}
        return true;
    }
    return false;
}
bool FF7Achievements::achievmentUnlocked(int bit){return (Achievements.at(bit/8) &(1<< (7-(bit%8))));}
void FF7Achievements::setAchievementUnlocked(int bit,bool unlocked)
{
    char temp = Achievements.at(bit/8);
    if(unlocked){ temp |= (1<< (7-(bit%8)));}
    else{temp &= ~(1<< (7-(bit%8)));}
    Achievements[bit/8]=temp;
}
QString FF7Achievements::name(int bit)
{
    switch(bit)
    {
    case 63: return qApp->translate("Achievement_Names","End of Part I"); break;
    case 62: return qApp->translate("Achievement_Names","End of Part II"); break;
    case 61: return qApp->translate("Achievement_Names","End of Game"); break;
    case 60: return qApp->translate("Achievement_Names","Master Materia"); break;
    case 59: return qApp->translate("Achievement_Names","Master of Gil"); break;
    case 58: return qApp->translate("Achievement_Names","Top Level"); break;
    case 57: return qApp->translate("Achievement_Names","Knights of the Round"); break;
    case 56: return qApp->translate("Achievement_Names","Omnislash"); break;
    case 55: return qApp->translate("Achievement_Names","Catastrophe"); break;
    case 54: return qApp->translate("Achievement_Names","Chaos"); break;
    case 53: return qApp->translate("Achievement_Names","Great Gospel"); break;
    case 52: return qApp->translate("Achievement_Names","Highwind"); break;
    case 51: return qApp->translate("Achievement_Names","Final Heaven"); break;
    case 50: return qApp->translate("Achievement_Names","All Creation"); break;
    case 49: return qApp->translate("Achievement_Names","Cosmo Memory"); break;
    case 48: return qApp->translate("Achievement_Names","Slots"); break;
    case 47: return qApp->translate("Achievement_Names","Bahamut Zero"); break;
    case 46: return qApp->translate("Achievement_Names","Ultimate Weapon"); break;
    case 45: return qApp->translate("Achievement_Names","Diamond Weapon"); break;
    case 44: return qApp->translate("Achievement_Names","Ruby Weapon"); break;
    case 43: return qApp->translate("Achievement_Names","Emerald Weapon"); break;
    case 42: return qApp->translate("Achievement_Names","Vincent"); break;
    case 41: return qApp->translate("Achievement_Names","Yuffie"); break;
    case 40: return qApp->translate("Achievement_Names","Materia Overlord"); break;
    case 39: return qApp->translate("Achievement_Names","Battle Square"); break;
    case 38: return qApp->translate("Achievement_Names","Gold Chocobo"); break;
    case 37: return qApp->translate("Achievement_Names","First Battle"); break;
    case 36: return qApp->translate("Achievement_Names","Braver"); break;
    case 35: return qApp->translate("Achievement_Names","Big Shot"); break;
    case 34: return qApp->translate("Achievement_Names","Galian Beast"); break;
    case 33: return qApp->translate("Achievement_Names","Healing Wind"); break;
    case 32: return qApp->translate("Achievement_Names","Boost Jump"); break;
    case 31: return qApp->translate("Achievement_Names","Beat Rush"); break;
    case 30: return qApp->translate("Achievement_Names","Greased Lightning"); break;
    case 29: return qApp->translate("Achievement_Names","Sled Fang"); break;
    case 28: return qApp->translate("Achievement_Names","Dice"); break;
    default: return QString(""); break;
    }
}
