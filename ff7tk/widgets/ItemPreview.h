/****************************************************************************/
//    copyright 2012 - 2016 Chris Rizzitello <sithlord48@gmail.com>         //
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

#ifndef ITEMPREVIEW_H
#define ITEMPREVIEW_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif

//Besure to set FF7Item Path!
#include "../data/FF7Item.h"

class ItemPreview : public QWidget
{
Q_OBJECT
  public:
	ItemPreview(QFlags<Qt::WindowType> WindowFlags=Qt::Widget,qreal Scale=1,QWidget *parent=0);
    int id(void);//return shown id.
  public slots:
    void setItem(quint16);
    void setItem(int);
  private:
    void setName(QString);
    void setDesc(QString);
    void setIcon(QPixmap);
    void elemental_info(int);
    void status_info(int);
    bool eventFilter(QObject *obj, QEvent *ev);
    QLabel *lbl_name;
    QLabel *lbl_desc;
    QLabel *lbl_icon;
    QLabel *lbl_slot_1;
    QLabel *lbl_slot_2;
    QLabel *lbl_slot_3;
    QLabel *lbl_slot_4;
    QLabel *lbl_slot_5;
    QLabel *lbl_slot_6;
    QLabel *lbl_slot_7;
    QLabel *lbl_slot_8;
    QLabel *lbl_m_link_1;
    QLabel *lbl_m_link_2;
    QLabel *lbl_m_link_3;
    QLabel *lbl_m_link_4;
    QGroupBox *materia_slot_box;
    QGroupBox *elemental_box;
    QGroupBox *status_box;
    QListWidget *elemental_effects;
    QListWidget *status_effects;
    FF7Item data;
    int _id;
	qreal scale;
};
#endif//ITEMPREVIEW_H
