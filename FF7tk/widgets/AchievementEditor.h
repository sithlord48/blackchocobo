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
#ifndef ACHIEVEMENTEDITOR_H
#define ACHIEVEMENTEDITOR_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif

#include "../static_data/FF7Achievements.h"

class AchievementEditor : public QWidget
{
    Q_OBJECT
public:
    explicit AchievementEditor(QWidget *parent = 0);
public slots:
    bool openFile(QString fileName="");
    bool saveFile(QString fileName="");
private slots:
    void itemToggled(QModelIndex index);
private:
    void initDisplay(void);
    void initConnect(void);
    void initDisconnect(void);
    FF7Achievements achievements;
    QListWidget *achievementList;
};

#endif // ACHIEVEMENTEDITOR_H
