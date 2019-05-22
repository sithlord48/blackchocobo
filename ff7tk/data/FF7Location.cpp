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

#include "FF7Location.h"
const FF7Location::LOCATION& FF7Location::location(int index)
{
    if(index >= 0 && index < size()) {
        return _locations.at(index);
    }
    return _emptyLocation;
}

int FF7Location::size() const
{
    return _locations.size();
}

const QString& FF7Location::fileName(int MapID,int LocID)
{
    for (const LOCATION &location : _locations) {
        if((MapID == location.map_id.toInt())
        &&(LocID == location.loc_id.toInt())) {
            return location.filename;
        }
    }
    return _emptyLocation.filename;
}

QString FF7Location::locationString(int index)
{
    return tr(_locations.at(index).location.toLocal8Bit());
}

QString FF7Location::locationString(const QString &fileName)
{
    for (const LOCATION &location : _locations) {
        if(fileName == location.filename) {
            return tr(location.location.toLocal8Bit());
        }
	}
    return _emptyLocation.filename;
}

const QString& FF7Location::mapID(const QString &fileName)
{
    for (const LOCATION &location : _locations) {
        if(fileName == location.filename) {
            return location.map_id;
        }
	}
    return _emptyLocation.map_id;
}

const QString& FF7Location::locationID(const QString &fileName)
{
    for (const LOCATION &location : _locations) {
        if(fileName == location.filename) {
            return location.loc_id;
        }
	}
    return _emptyLocation.loc_id;
}

const QString& FF7Location::x(const QString &fileName)
{
    for (const LOCATION &location : _locations) {
        if(fileName == location.filename) {
            return location.x;
        }
    }
    return _emptyLocation.x;
}

const QString& FF7Location::y(const QString &fileName)
{
    for (const LOCATION &location : _locations) {
        if(fileName == location.filename) {
            return location.y;
        }
    }
    return _emptyLocation.y;
}

const QString& FF7Location::t(const QString &fileName)
{
    for (const LOCATION &location : _locations) {
        if(fileName == location.filename) {
            return location.t;
        }
    }
    return _emptyLocation.t;
}

const QString& FF7Location::d(const QString &fileName)
{
    for (const LOCATION &location : _locations) {
        if(fileName == location.filename) {
            return location.d;
        }
    }
    return _emptyLocation.d;
}
