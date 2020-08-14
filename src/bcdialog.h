/****************************************************************************/
//    copyright 2020 Chris Rizzitello <sithlord48@gmail.com>                //
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
#pragma once

#include <QDir>

class QString;
class QWidget;
class QSettings;
class FF7Save;

class BCDialog
{
public:
    static QString getOpenFileName(QWidget  *parent = nullptr, const QString &title = QString(), const QString &path = QDir::homePath(), const QString &nameFilters = QString(), const QString &initSelection = QString());
    static QString getExistingDirectory(QWidget  *parent = nullptr, const QString &title = QString(), const QString &path = QDir::homePath(), const QString &initSelection = QString());
    static QString getSaveFileName(QWidget  *parent = nullptr, const QString &region = QString(), const QString &title = QString(), const QString &path = QDir::homePath(), const QString &nameFilters = QString(), QString *chosenType = nullptr, const QString &initSelection = QString());
    static void editSideBarPaths(QWidget *parent= nullptr);
    static int fixTimeDialog(QWidget* parent, bool slotPAL = false);
};
