/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
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

#ifndef DOUBLECHECKBOX_H
#define DOUBLECHECKBOX_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif

class DoubleCheckBox : public QWidget
{
    Q_OBJECT
public:
    explicit DoubleCheckBox(QWidget *parent = 0);
    explicit DoubleCheckBox(const QString &text,QWidget *parent = 0);
    void setText(QString text);
    void setChecked(int box,bool checked);
    bool checked(int box);
    void setBoxToolTip(int box,QString text);
    void setToolTip(QString text);
signals:
    void box1_toggled(bool checked);
    void box2_toggled(bool checked);
private slots:
    void cb_one_toggled(bool checked);
    void cb_two_toggled(bool checked);
private:
    void init_display();
    void init_connections();
    QCheckBox *cb_one;
    QCheckBox *cb_two;
    QLabel * label;
};

#endif // DOUBLECHECKBOX_H
