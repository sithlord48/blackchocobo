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
#ifndef SLOTPREVIEW_H
#define SLOTPREVIEW_H

#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>

//set path to save icon class
#include "../static_data/SaveIcon.h"

class SlotPreview : public QLabel
{
    Q_OBJECT
public:
    SlotPreview(QWidget *parent = 0);
    void setParty(QPixmap p1,QPixmap p2,QPixmap p3);
    void setParty(QString p1_style,QString p2_style,QString p3_style);
    void setName(QString);
    void set_Button_Label(QString);
    void setLevel(int);
    void setLocation(QString);
    void setGil(int);
    void setTime(int hour,int min);
    void setPsxIcon(QByteArray,quint8 frames=1);
    void setMode(int mode);

private slots:
    //raw pix map for labels
    void set_Party1(QPixmap);
    void set_Party2(QPixmap);
    void set_Party3(QPixmap);

    void set_Party1(QString style);
    void set_Party2(QString style);
    void set_Party3(QString style);
    void selected(void);
    void set_ff7_save(void);
    void set_empty(void);
    void set_psx_game(void);

private:
    QLabel *party1;
    QLabel *party2;
    QLabel *party3;
    QLabel *name;
    QLabel *lbl_time;
    QLabel *lbl_level;
    QLabel *location;
    QLabel *lbl_gil;
    QPushButton *btn_select;
    QGroupBox *top_most;
    SaveIcon *icon;
    bool not_pc;
signals:
    void button_clicked(QString);
};

#endif
