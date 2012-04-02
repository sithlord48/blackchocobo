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

QString FF7Materia::Name(int id){return qApp->translate("Materia_Names",Materias[id].name.toAscii());}
QString FF7Materia::Stat_String(int id){return qApp->translate("Materia_Stats",Materias[id].stats.toAscii());}
qint8 FF7Materia::Stat_Str(int id){return Materias[id].str;}
qint8 FF7Materia::Stat_Vit(int id){return Materias[id].vit;}
qint8 FF7Materia::Stat_Dex(int id){return Materias[id].dex;}
qint8 FF7Materia::Stat_Mag(int id){return Materias[id].mag;}
qint8 FF7Materia::Stat_Spi(int id){return Materias[id].spi;}
qint8 FF7Materia::Stat_Lck(int id){return Materias[id].lck;}
qint8 FF7Materia::Stat_Hp(int id){return Materias[id].hp;}
qint8 FF7Materia::Stat_Mp(int id){return Materias[id].mp;}
qint8 FF7Materia::Levels(int id){return Materias[id].levels;}
quint8 FF7Materia::Type(int id){return Materias[id].type;}
qint32 FF7Materia::Ap(int id,int lvl){return Materias[id].ap[lvl];}
QIcon FF7Materia::Icon(int id){return QIcon(QPixmap::fromImage(Materias[id].m_image));}
QImage FF7Materia::Image(int id){return Materias[id].m_image;}
QImage FF7Materia::Image_EmptyStar(int id){return Materias[id].em_image;}
QImage FF7Materia::Image_FullStar(int id){return Materias[id].fm_image;}
QIcon FF7Materia::Icon_AllMateria(){return QIcon(all_xpm);}
QImage FF7Materia::Image_AllMateria(){return QImage(all_xpm);}
QString FF7Materia::Eskill(int i){return qApp->translate("E_skills",ESkills[i].toAscii());}
QString FF7Materia::Element(int i){return qApp->translate("Elements",Materias[i].elemental.toAscii());}
QStringList FF7Materia::Skills(int i)
{
    QStringList translated_list;
    for(int j=0;j<Materias[i].skills.count();j++)
    {
        translated_list.append(qApp->translate("Materia_Skills",Materias[i].skills.at(j).toAscii()));
    }
    return translated_list;
}
QStringList FF7Materia::Status(int i)
{
    QStringList translated_list;
    for (int j=0;j<Materias[i].status.count();j++)
    {
        translated_list.append(qApp->translate("Status",Materias[i].status.at(j).toAscii()));
    }
    return translated_list;
}

