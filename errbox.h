/****************************************************************************/
//    copyright 2010-2016 Chris Rizzitello <sithlord48@gmail.com>           //
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
#include "ff7tk/data/FF7Save.h"
#include "ff7tk/data/SaveIcon.h"

class errbox : public QDialog
{
	Q_OBJECT

public:
	explicit errbox(QWidget *parent = 0,FF7Save *ff7data=0,int slot=0);
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
    SaveIcon *save_icon = nullptr;
    FF7Save *ff7 = nullptr;
	/* Gui Objects*/
    QPushButton * btnNext = nullptr;
    QPushButton * btnPrev = nullptr;
    QPushButton * btnView = nullptr;
    QPushButton * btnExport = nullptr;
    QLabel *lblRegionString = nullptr;
    QLabel *lblIcon = nullptr;
    bool singleSlot = false;
};

#endif // ERRBOX_H
