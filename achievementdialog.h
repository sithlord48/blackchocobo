/****************************************************************************/
//    copyright 2013 - 2019 Chris Rizzitello <sithlord48@gmail.com>         //
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
#include <QDialog>
#include "ff7tk/widgets/AchievementEditor.h"

class QPushButton;
class achievementDialog : public QDialog
{
    Q_OBJECT
public:
    explicit achievementDialog(const QString &FileName, QWidget *parent = nullptr);
public slots:
    void accept();
private:
    AchievementEditor *achEditor = nullptr;
    QPushButton *btnSave = nullptr;
    QPushButton *btnNo = nullptr;
    QString fileName;
};
