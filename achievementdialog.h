/****************************************************************************/
//    copyright 2013 Chris Rizzitello <sithlord48@gmail.com>                //
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
#ifndef ACHIEVEMENTDIALOG_H
#define ACHIEVEMENTDIALOG_H

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
#include "ff7tk/widgets/AchievementEditor.h"

class achievementDialog : public QDialog
{
	Q_OBJECT
public:
	explicit achievementDialog(qreal Scale=1,QString FileName="",QWidget *parent=0);

signals:

public slots:
	void accept();
private:
   AchievementEditor *achEditor;
   QPushButton *btnSave;
   QPushButton *btnNo;
   QString fileName;
};

#endif // ACHIEVEMENTDIALOG_H
