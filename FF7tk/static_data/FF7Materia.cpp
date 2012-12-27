/****************************************************************************/
//    copyright 2010-2012  Chris Rizzitello <sithlord48@gmail.com>          //
//                                                                          //
//    This file is part of <UnNamedToolKit>                                 //
//                                                                          //
//  <UnNamedToolKit> is free software: you can redistribute it and/or modify//
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
// <UnNamedToolKit> is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "FF7Materia.h"
#include <QCoreApplication>
#include "icons/Materia_Icons/all.xpm"

QString FF7Materia::name(int id){return qApp->translate("Materia_Names",Materias[id].name.toLocal8Bit());}
QString FF7Materia::statString(int id){return qApp->translate("Materia_Stats",Materias[id].stats.toLocal8Bit());}
qint8 FF7Materia::statSTR(int id){return Materias[id].str;}
qint8 FF7Materia::statVIT(int id){return Materias[id].vit;}
qint8 FF7Materia::statDEX(int id){return Materias[id].dex;}
qint8 FF7Materia::statMAG(int id){return Materias[id].mag;}
qint8 FF7Materia::statSPI(int id){return Materias[id].spi;}
qint8 FF7Materia::statLCK(int id){return Materias[id].lck;}
qint8 FF7Materia::statHP(int id){return Materias[id].hp;}
qint8 FF7Materia::statMP(int id){return Materias[id].mp;}
qint8 FF7Materia::levels(int id){return Materias[id].levels;}
quint8 FF7Materia::type(int id){return Materias[id].type;}
qint32 FF7Materia::ap(int id,int lvl){return Materias[id].ap[lvl];}
QIcon FF7Materia::icon(int id){return QIcon(QPixmap::fromImage(Materias[id].m_image));}
QImage FF7Materia::image(int id){return Materias[id].m_image;}
QImage FF7Materia::imageEmptyStar(int id){return Materias[id].em_image;}
QImage FF7Materia::imageFullStar(int id){return Materias[id].fm_image;}
QIcon FF7Materia::iconAllMateria(){return QIcon(QPixmap(all_xpm));}
QImage FF7Materia::imageAllMateria(){return QImage(all_xpm);}
QString FF7Materia::enemySkill(int i){return qApp->translate("E_skills",ESkills[i].toLocal8Bit());}
QString FF7Materia::element(int i){return qApp->translate("Elements",Materias[i].elemental.toLocal8Bit());}
QStringList FF7Materia::skills(int i)
{
    QStringList translated_list;
    for(int j=0;j<Materias[i].skills.count();j++)
    {
        translated_list.append(qApp->translate("Materia_Skills",Materias[i].skills.at(j).toLocal8Bit()));
    }
    return translated_list;
}
QStringList FF7Materia::status(int i)
{
    QStringList translated_list;
    for (int j=0;j<Materias[i].status.count();j++)
    {
        translated_list.append(qApp->translate("Status",Materias[i].status.at(j).toLocal8Bit()));
    }
    return translated_list;
}
quint32 FF7Materia::ap2num(quint8 ap[3]){return (ap[0] | (ap[1] << 8) | (ap[2]<<16));}

