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

#ifndef DIALOGPREVIEW_H
#define DIALOGPREVIEW_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif

class DialogPreview : public QLabel
{
    Q_OBJECT
public:
    DialogPreview(QWidget *parent = 0);
    void SetLLeft(QColor);
    void SetULeft(QColor);
    void SetLRight(QColor);
    void SetURight(QColor);
    QColor ll();
    QColor lr();
    QColor ul();
    QColor ur();
    QPushButton *btn_ul;
    QPushButton *btn_ur;
    QPushButton *btn_ll;
    QPushButton *btn_lr;
private:
    void draw();
    QColor upper_left;
    QColor upper_right;
    QColor lower_left;
    QColor lower_right;


protected:
    void resizeEvent(QResizeEvent*);
private slots:
     void btn_ul_clicked();
     void btn_ur_clicked();
     void btn_ll_clicked();
     void btn_lr_clicked();
signals:
     void LL_ColorChanged(QColor color);
     void LR_ColorChanged(QColor color);
     void UL_ColorChanged(QColor color);
     void UR_ColorChanged(QColor color);

};

#endif
