/****************************************************************************/
//    copyright 2013 - 2018 Chris Rizzitello <sithlord48@gmail.com>         //
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

#include "FF7Achievements.h"
#include <QFile>

bool FF7Achievements::openFile(const QString &fileName)
{
    if (!fileName.isEmpty()) {
        QFile data(fileName);
        if (data.open(QIODevice::ReadOnly)) {
            _achievements = data.readAll();
            data.close();
        } else {
            return false;
        }
        return true;
    }
    return false;
}

bool FF7Achievements::saveFile(const QString &fileName)
{
    if (!fileName.isEmpty()) {
        QFile data(fileName);
        if (data.open(QIODevice::WriteOnly)) {
            data.seek(0);
            data.write(_achievements.data(), 8);
            data.close();
        } else {
            return false;
        }
        return true;
    }
    return false;
}

bool FF7Achievements::achievmentUnlocked(int bit)
{
    bit = std::clamp(bit, 28, 63);
    return (_achievements.at(bit / 8) & (1 << (7 - (bit % 8))));
}

void FF7Achievements::setAchievementUnlocked(int bit, bool unlocked)
{
    bit = std::clamp(bit, 28, 63);
    char temp = _achievements.at(bit / 8);
    if (unlocked) {
        temp |= (1 << (7 - (bit % 8)));
    } else {
        temp &= ~(1 << (7 - (bit % 8)));
    }
    _achievements[bit / 8] = temp;
}

QString FF7Achievements::name(int bit)
{
    QString temp;
    if (bit >=28 && bit <=63) {
        temp = tr(_names.at(bit - 28).toLocal8Bit());
    }
    return temp;
}

