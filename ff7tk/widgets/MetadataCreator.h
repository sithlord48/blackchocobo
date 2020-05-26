/****************************************************************************/
//    copyright 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>         //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#pragma once

#include <QDialog>

#include "../data/FF7SaveInfo.h"

class FF7Save;
class QDialogButtonBox;
class QVBoxLayout;

class MetadataCreator : public QDialog
{
    Q_OBJECT
public:
    explicit MetadataCreator(QWidget *parent = nullptr, FF7Save *ff7save = nullptr);
private slots:
    void initDisplay();
    void accepted();

private:
    QString getOpenFileName(QWidget  *parent = nullptr, const QString &title = QString(), const QString &path = QString(), const QString &nameFilters = QString(), const QString &initSelection = QString());
    QString getExistingDirectory(QWidget *parent = nullptr, const QString &title = QString(), const QString &path = QString(), const QString &initSelection = QString());
    QVBoxLayout *makeLineLayout();
    //Data Parts
    bool load;
    FF7Save *ff7;
    QStringList InFiles;
    QString OutPath;
    QString UserID;
    QDialogButtonBox *btnBox = nullptr;
};
