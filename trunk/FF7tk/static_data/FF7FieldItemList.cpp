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
#include "FF7FieldItemList.h"
#include <QCoreApplication>

FF7FieldItemList::FF7FieldItemList(){}
QList<quint16> FF7FieldItemList::offset(int index){return FILIST[index].Offset;}
QList<quint8> FF7FieldItemList::bit(int index){return FILIST[index].Bit;}
QStringList FF7FieldItemList::maps(int index){return FILIST[index].Maps;}
QString FF7FieldItemList::text(int index){return qApp->translate("FieldItems",FILIST[index].Text.toLocal8Bit());}
int FF7FieldItemList::count(){return 296;}//sync w/ item count
