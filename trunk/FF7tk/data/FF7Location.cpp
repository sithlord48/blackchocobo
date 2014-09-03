/****************************************************************************/
//    copyright 2012 -2014  Chris Rizzitello <sithlord48@gmail.com>         //
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

#include "FF7Location.h"
#include <QCoreApplication>

QString FF7Location::fileName(int i){return Locations[i].filename;}
QString FF7Location::locationString(int i){return qApp->translate("Locations",Locations[i].location.toLocal8Bit());}
QString FF7Location::mapID(int i){return Locations[i].map_id;}
QString FF7Location::locationID(int i){return Locations[i].loc_id;}
QString FF7Location::x(int i){return Locations[i].x;}
QString FF7Location::y(int i){return Locations[i].y;}
QString FF7Location::t(int i){return Locations[i].t;}
QString FF7Location::d(int i){return Locations[i].d;}

int FF7Location::len(){return 571;}// keep current num locations in list.

QString FF7Location::fileName(int MapID,int LocID)
{
	QString temp;
	for(int i =0;i < len(); i++)
	{
		if( (MapID==Locations[i].map_id.toInt()) && (LocID ==Locations[i].loc_id.toInt())){temp= Locations[i].filename;}
	}
	return temp;
}
QString FF7Location::locationString(QString fileName)
{
	QString temp;
	for (int i=0;i<len();i++)
	{
		if(fileName == Locations[i].filename){temp=Locations[i].location;}
	}
	return temp;
}
QString FF7Location::mapID(QString fileName)
{
	QString temp;
	for (int i=0;i<len();i++)
	{
		if(fileName == Locations[i].filename){temp=Locations[i].map_id;}
	}
	return temp;
}
QString FF7Location::locationID(QString fileName)
{
	QString temp;
	for (int i=0;i<len();i++)
	{
		if(fileName == Locations[i].filename){temp=Locations[i].loc_id;}
	}
	return temp;
}
QString FF7Location::x(QString fileName)
{
	QString temp;
	for (int i=0;i<len();i++)
	{
		if(fileName == Locations[i].filename){temp=Locations[i].x;}
	}
	return temp;
}
QString FF7Location::y(QString fileName)
{
	QString temp;
	for (int i=0;i<len();i++)
	{
		if(fileName == Locations[i].filename){temp=Locations[i].y;}
	}
	return temp;
}
QString FF7Location::t(QString fileName)
{
	QString temp;
	for (int i=0;i<len();i++)
	{
		if(fileName == Locations[i].filename){temp=Locations[i].t;}
	}
	return temp;
}
QString FF7Location::d(QString fileName)
{
	QString temp;
	for (int i=0;i<len();i++)
	{
		if(fileName == Locations[i].filename){temp=Locations[i].d;}
	}
	return temp;
}
