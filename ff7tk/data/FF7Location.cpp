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
    auto it = std::find_if(dPtr->_locations.begin(), dPtr->_locations.end(), [MapID, LocID](const LOCATION &loc){return ((MapID == loc.map_id.toInt()) && (LocID == loc.loc_id.toInt()));});
    if(it != dPtr->_locations.end())
        return it->filename;
    return dPtr->_emptyLocation.filename;
}
QString FF7Location::rawLocationString(int index)
{
    return dPtr->_locations.at(index).location;
}
QString FF7Location::rawLocationString(const QString &fileName)
{
    auto it = std::find_if(dPtr->_locations.begin(), dPtr->_locations.end(), [fileName](const LOCATION &loc){return fileName == loc.filename;});
    if(it != dPtr->_locations.end())
        return it->location;
    return dPtr->_emptyLocation.filename;
}
QString FF7Location::locationString(int index)
{
    return tr(dPtr->_locations.at(index).location.toLocal8Bit());
}

QString FF7Location::locationString(const QString &fileName)
{
    auto it = std::find_if(dPtr->_locations.begin(), dPtr->_locations.end(), [fileName](const LOCATION &loc){return fileName == loc.filename;});
    if(it != dPtr->_locations.end())
        return tr(it->location.toLocal8Bit());
    return dPtr->_emptyLocation.filename;
}

const QString &FF7Location::mapID(int index)
{
    return dPtr->_locations.at(index).map_id;
}

const QString &FF7Location::mapID(const QString &fileName)
{
    auto it = std::find_if(dPtr->_locations.begin(), dPtr->_locations.end(), [fileName](const LOCATION &loc){return fileName == loc.filename;});
    if(it != dPtr->_locations.end())
        return it->map_id;
    return dPtr->_emptyLocation.map_id;
}

const QString &FF7Location::locationID(int index)
{
    return dPtr->_locations.at(index).loc_id;
}

const QString &FF7Location::locationID(const QString &fileName)
{
    auto it = std::find_if(dPtr->_locations.begin(), dPtr->_locations.end(), [fileName](const LOCATION &loc){return fileName == loc.filename;});
    if(it != dPtr->_locations.end())
        return it->loc_id;
    return dPtr->_emptyLocation.loc_id;
}

const QString &FF7Location::x(int index)
{
    return dPtr->_locations.at(index).x;
}

const QString &FF7Location::x(const QString &fileName)
{
    auto it = std::find_if(dPtr->_locations.begin(), dPtr->_locations.end(), [fileName](const LOCATION &loc){return fileName == loc.filename;});
    if(it != dPtr->_locations.end())
        return it->x;
    return dPtr->_emptyLocation.x;
}

const QString &FF7Location::y(int index)
{
    return dPtr->_locations.at(index).y;
}

const QString &FF7Location::y(const QString &fileName)
{
    auto it = std::find_if(dPtr->_locations.begin(), dPtr->_locations.end(), [fileName](const LOCATION &loc){return fileName == loc.filename;});
    if(it != dPtr->_locations.end())
        return it->y;
    return dPtr->_emptyLocation.y;
}

const QString &FF7Location::t(int index)
{
    return dPtr->_locations.at(index).t;
}

const QString &FF7Location::t(const QString &fileName)
{
    auto it = std::find_if(dPtr->_locations.begin(), dPtr->_locations.end(), [fileName](const LOCATION &loc){return fileName == loc.filename;});
    if(it != dPtr->_locations.end())
        return it->t;
    return dPtr->_emptyLocation.t;
}

const QString &FF7Location::d(int index)
{
    return dPtr->_locations.at(index).d;
}

const QString &FF7Location::d(const QString &fileName)
{
    auto it = std::find_if(dPtr->_locations.begin(), dPtr->_locations.end(), [fileName](const LOCATION &loc){return fileName == loc.filename;});
    if(it != dPtr->_locations.end())
        return it->d;
    return dPtr->_emptyLocation.d;}
