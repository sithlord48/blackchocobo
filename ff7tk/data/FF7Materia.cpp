/****************************************************************************/
//    copyright 2012 - 2018  Chris Rizzitello <sithlord48@gmail.com>        //
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

#include "FF7Materia.h"

const FF7Materia::MATERIA &FF7Materia::Materias(int id)
{
    if (id >= 0 && id <= 0x5A) {
        return _materiaList.at(id);
    }
    return _emptyMateria;
}

qint32 FF7Materia::ap(int id, int lvl)
{
    lvl = std::clamp(lvl, 0, 4);
    return Materias(id).ap.at(lvl);
}

QString FF7Materia::name(int id)
{
    return tr(Materias(id).name.toLocal8Bit());
}

QString FF7Materia::statString(int id)
{
    return tr(Materias(id).stats.toLocal8Bit());
}

QString FF7Materia::enemySkill(int id)
{
    id = std::clamp(id, 0, _enemySkills.size() -1);
    return tr(_enemySkills.at(id).toLocal8Bit());
}

QString FF7Materia::element(int id)
{
    return tr(Materias(id).elemental.toLocal8Bit());
}

QStringList FF7Materia::skills(int id)
{
    QStringList translated_list;
    for(const QString &skill : Materias(id).skills) {
        translated_list.append(tr(skill.toLocal8Bit()));
    }
    return translated_list;
}

QStringList FF7Materia::status(int id)
{
    QStringList translated_list;
    for(const QString& stat : Materias(id).status) {
        translated_list.append(tr(stat.toLocal8Bit()));
    }
    return translated_list;
}
QString FF7Materia::iconResource(int id)
{
    QString temp = Materias(id).imageString;
    return temp.remove(QStringLiteral(":/"));
}

QString FF7Materia::fullStarResource(int id)
{
    QString temp = Materias(id).fullStarString;
    return temp.remove(QStringLiteral(":/"));
}

QString FF7Materia::emptyStartResource(int id)
{
    QString temp = Materias(id).emptyStarString;
    return temp.remove(QStringLiteral(":/"));
}

