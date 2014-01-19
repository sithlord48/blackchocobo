/****************************************************************************/
//    copyright 2010-2013 Chris Rizzitello <sithlord48@gmail.com>           //
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
#ifndef ERRBOX_H
#define ERRBOX_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets/QDialog>
    #include <QtWidgets/QLabel>
    #include <QtWidgets/QPushButton>
    #include <QtWidgets/QHBoxLayout>
    #include <QtWidgets/QVBoxLayout>
#else
    #include <QtGui/QDialog>
#endif
#include "FF7tk/data/FF7Save.h"
#include "FF7tk/data/SaveIcon.h"

class errbox : public QDialog
{
    Q_OBJECT

public:
    explicit errbox(QWidget *parent = 0,FF7Save *ff7data=0,int slot=0);
protected:
    void keyPressEvent(QKeyEvent *e);
private slots:
    void btnPrevClicked();
    void btnExportClicked();
    void btnViewClicked();
    void btnNextClicked();
private:
    int s;
    SaveIcon save_icon;
    FF7Save *ff7;
    /* Gui Objects*/
    QPushButton * btnNext;
    QPushButton * btnPrev;
    QPushButton * btnView;
    QPushButton * btnExport;
    QLabel *lblRegionString;
    QLabel *lblIcon;
};

#endif // ERRBOX_H
