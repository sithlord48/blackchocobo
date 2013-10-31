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
#ifndef FF7ACHIEVEMENTS_H
#define FF7ACHIEVEMENTS_H
#include <QObject>
class FF7Achievements : public QObject
{
    Q_OBJECT
    public:
        bool achievmentUnlocked(int bit);
        void setAchievementUnlocked(int bit,bool unlocked);
        explicit FF7Achievements(QObject *parent = 0);
        bool openFile(QString fileName="");
        bool saveFile(QString fileName="");
        QString name(int bit);
    private:
        QByteArray Achievements;
};
#endif // FF7ACHIEVEMENTS_H
