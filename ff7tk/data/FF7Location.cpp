/****************************************************************************/
//    copyright 2012 - 2020  Chris Rizzitello <sithlord48@gmail.com>        //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "FF7Location.h"

#include <QQmlEngine>

FF7Location *FF7Location::instance()
{
    static FF7Location m;
    return &m;
}

FF7Location::FF7Location(QObject *parent) :
    QObject(parent)
    , dPtr(new FF7LocationPrivate)
{
}

FF7Location::~FF7Location()
{
    delete dPtr;
}

QObject *FF7Location::qmlSingletonRegister(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine)
    engine->setObjectOwnership(instance(), QQmlEngine::CppOwnership);
    return instance();
}

const QString &FF7Location::fileName(int index)
{
    return dPtr->_locations.at(index).filename;
}

const FF7Location::LOCATION &FF7Location::location(int index)
{
    if (index >= 0 && index < size()) {
        return dPtr->_locations.at(index);
    }
    return dPtr->_emptyLocation;
}

int FF7Location::size() const
{
    return dPtr->_locations.size();
}

const QString &FF7Location::fileName(int MapID, int LocID)
{
    for (const LOCATION &location : dPtr->_locations) {
        if ((MapID == location.map_id.toInt())
                && (LocID == location.loc_id.toInt())) {
            return location.filename;
        }
    }
    return dPtr->_emptyLocation.filename;
}
QString FF7Location::rawLocationString(int index)
{
    return dPtr->_locations.at(index).location;
}
QString FF7Location::rawLocationString(const QString &fileName)
{
    for (const LOCATION &location : dPtr->_locations) {
        if (fileName == location.filename) {
            return location.location;
        }
    }
    return dPtr->_emptyLocation.filename;
}
QString FF7Location::locationString(int index)
{
    return tr(dPtr->_locations.at(index).location.toLocal8Bit());
}

QString FF7Location::locationString(const QString &fileName)
{
    for (const LOCATION &location : dPtr->_locations) {
        if (fileName == location.filename) {
            return tr(location.location.toLocal8Bit());
        }
    }
    return dPtr->_emptyLocation.filename;
}

const QString &FF7Location::mapID(int index)
{
    return dPtr->_locations.at(index).map_id;
}

const QString &FF7Location::mapID(const QString &fileName)
{
    for (const LOCATION &location : dPtr->_locations) {
        if (fileName == location.filename) {
            return location.map_id;
        }
    }
    return dPtr->_emptyLocation.map_id;
}

const QString &FF7Location::locationID(int index)
{
    return dPtr->_locations.at(index).loc_id;
}

const QString &FF7Location::locationID(const QString &fileName)
{
    for (const LOCATION &location : dPtr->_locations) {
        if (fileName == location.filename) {
            return location.loc_id;
        }
    }
    return dPtr->_emptyLocation.loc_id;
}

const QString &FF7Location::x(int index)
{
    return dPtr->_locations.at(index).x;
}

const QString &FF7Location::x(const QString &fileName)
{
    for (const LOCATION &location : dPtr->_locations) {
        if (fileName == location.filename) {
            return location.x;
        }
    }
    return dPtr->_emptyLocation.x;
}

const QString &FF7Location::y(int index)
{
    return dPtr->_locations.at(index).y;
}

const QString &FF7Location::y(const QString &fileName)
{
    for (const LOCATION &location : dPtr->_locations) {
        if (fileName == location.filename) {
            return location.y;
        }
    }
    return dPtr->_emptyLocation.y;
}

const QString &FF7Location::t(int index)
{
    return dPtr->_locations.at(index).t;
}

const QString &FF7Location::t(const QString &fileName)
{
    for (const LOCATION &location : dPtr->_locations) {
        if (fileName == location.filename) {
            return location.t;
        }
    }
    return dPtr->_emptyLocation.t;
}

const QString &FF7Location::d(int index)
{
    return dPtr->_locations.at(index).d;
}

const QString &FF7Location::d(const QString &fileName)
{
    for (const LOCATION &location : dPtr->_locations) {
        if (fileName == location.filename) {
            return location.d;
        }
    }
    return dPtr->_emptyLocation.d;
}
