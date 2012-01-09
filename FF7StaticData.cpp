/****************************************************************************/
//    copyright 2010-2012 Chris Rizzitello <sithlord48@gmail.com>           //
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
#include "FF7StaticData.h"
#include <QCoreApplication>

QString FF7StaticData::ItemNames(int i){return qApp->translate("Items",Items[i].name.toAscii());}
QString FF7StaticData::MateriaNames(int i){return qApp->translate("Materia_Names",Materias[i].name.toAscii());}
QString FF7StaticData::MateriaStats(int i){return qApp->translate("Materia_Stats",Materias[i].stats.toAscii());}
QString FF7StaticData::MateriaSkills(int i,int l){return qApp->translate("Materia_Skills",Materias[i].skills[l].toAscii());}
qint8 FF7StaticData::MateriaStats_Str(int i){return Materias[i].str;}
qint8 FF7StaticData::MateriaStats_Vit(int i){return Materias[i].vit;}
qint8 FF7StaticData::MateriaStats_Dex(int i){return Materias[i].dex;}
qint8 FF7StaticData::MateriaStats_Mag(int i){return Materias[i].mag;}
qint8 FF7StaticData::MateriaStats_Spi(int i){return Materias[i].spi;}
qint8 FF7StaticData::MateriaStats_Lck(int i){return Materias[i].lck;}
qint8 FF7StaticData::MateriaStats_Hp(int i){return Materias[i].hp;}
qint8 FF7StaticData::MateriaStats_Mp(int i){return Materias[i].mp;}

//Location Class
QString locations::loc_name(int i){return qApp->translate("Locations",Locations[i].location.toAscii());}
QString locations::map_id(int i){return Locations[i].map_id;}
QString locations::loc_id(int i){return Locations[i].loc_id;}
QString locations::x(int i){return Locations[i].x;}
QString locations::y(int i){return Locations[i].y;}
QString locations::z(int i){return Locations[i].z;}
int locations::len(){return 51;}// keep current num locations in list.
