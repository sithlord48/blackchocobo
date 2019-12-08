/****************************************************************************/
//    copyright 2012 - 2019 Chris Rizzitello <sithlord48@gmail.com>         //
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
/*~~~~~~~~~~~Includes~~~~~~~~*/
#pragma once
#include <QDialog>
#include <QVBoxLayout>
#include "../data/FF7Save.h"

class MetadataCreator : public QDialog
{
    Q_OBJECT
public:
    explicit MetadataCreator(QWidget *parent = nullptr, FF7Save *ff7save = nullptr);
private slots:
    void initDisplay();
    void on_buttonBox_accepted();

private:
    QVBoxLayout *makeLineLayout();
    //Data Parts
    bool load;
    FF7Save *ff7;
    QStringList InFiles;
    QString OutPath;
    QString UserID;
    QPushButton *btnOk = nullptr;
    QPushButton *btnCancel = nullptr;
};
