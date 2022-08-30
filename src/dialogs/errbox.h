/****************************************************************************/
//    copyright 2010-2020 Chris Rizzitello <sithlord48@gmail.com>           //
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
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <FF7Save>
#include <SaveIcon>

class errbox : public QDialog
{
    Q_OBJECT

public:
    explicit errbox(QWidget *parent = nullptr, FF7Save *ff7data = nullptr, int slot = 0);
    bool isSingleSlot();
    void setSingleSlot(bool single);
protected:
    void keyPressEvent(QKeyEvent *e);
private slots:
    void setIcon(QPixmap);
    void btnPrevClicked();
    void btnExportClicked();
    void btnViewClicked();
    void btnNextClicked();
private:
    int s;
    bool singleSlot = false;
    FF7Save *ff7save = nullptr;
    SaveIcon *save_icon = nullptr;
    QPushButton *btnNext = nullptr;
    QPushButton *btnPrev = nullptr;
    QPushButton *btnView = nullptr;
    QPushButton *btnExport = nullptr;
    QLabel *lblRegionString = nullptr;
    QLabel *lblIcon = nullptr;
};
