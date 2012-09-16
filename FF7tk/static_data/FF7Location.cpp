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
#include "FF7Location.h"
#include <QCoreApplication>

QString FF7Location::loc_name(int i){return qApp->translate("Locations",Locations[i].location.toAscii());}
QString FF7Location::map_id(int i){return Locations[i].map_id;}
QString FF7Location::loc_id(int i){return Locations[i].loc_id;}
QString FF7Location::x(int i){return Locations[i].x;}
QString FF7Location::y(int i){return Locations[i].y;}
QString FF7Location::z(int i){return Locations[i].z;}
int FF7Location::len(){return 255;}// keep current num locations in list.
