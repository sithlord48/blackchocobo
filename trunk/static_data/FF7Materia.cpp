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
#include "FF7Materia.h"
#include <QCoreApplication>
#include "icons/Materia_Icons/all.xpm"

QString FF7Materia::Name(int id){return qApp->translate("Materia_Names",Materias[id].name.toAscii());}
QString FF7Materia::Stat_String(int id){return qApp->translate("Materia_Stats",Materias[id].stats.toAscii());}
QString FF7Materia::Skills(int id,int lvl){return qApp->translate("Materia_Skills",Materias[id].skills[lvl].toAscii());}
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


