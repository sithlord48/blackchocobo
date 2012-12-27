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

#include "DialogPreview.h"

DialogPreview::DialogPreview(QWidget *parent) : QLabel(parent)
{
    btn_ul = new QPushButton(this);
    btn_ur = new QPushButton(this);
    btn_ll = new QPushButton(this);
    btn_lr = new QPushButton(this);
    QString style="QPushButton:enabled{background-color: rgba(0,0,0,0);border:0px solid;} QPushButton:hover{background-color:rgba(0,50,50,96);}";
    btn_ul->setStyleSheet(style);
    btn_ur->setStyleSheet(style);
    btn_ll->setStyleSheet(style);
    btn_lr->setStyleSheet(style);
    setMinimumSize(60,30);
    draw();
    connect(btn_ul,SIGNAL(clicked()),this,SLOT(btn_ul_clicked()));
    connect(btn_ur,SIGNAL(clicked()),this,SLOT(btn_ur_clicked()));
    connect(btn_ll,SIGNAL(clicked()),this,SLOT(btn_ll_clicked()));
    connect(btn_lr,SIGNAL(clicked()),this,SLOT(btn_lr_clicked()));
}

void DialogPreview::SetLLeft(QColor color)  {lower_left=color;  draw(); emit LL_ColorChanged(lower_left);}
void DialogPreview::SetULeft(QColor color)  {upper_left=color;  draw(); emit UL_ColorChanged(upper_left);}
void DialogPreview::SetLRight(QColor color) {lower_right=color; draw(); emit LR_ColorChanged(lower_right);}
void DialogPreview::SetURight(QColor color) {upper_right=color; draw(); emit UR_ColorChanged(upper_right);}

QColor DialogPreview::ll(){return lower_left;}
QColor DialogPreview::lr(){return lower_right;}
QColor DialogPreview::ul(){return upper_left;}
QColor DialogPreview::ur(){return upper_right;}

void DialogPreview::btn_ll_clicked(){QColor color = QColorDialog::getColor(lower_left,this);    if(color.isValid()){SetLLeft(color);}}
void DialogPreview::btn_lr_clicked(){QColor color = QColorDialog::getColor(lower_right,this); if(color.isValid()){SetLRight(color);}}
void DialogPreview::btn_ul_clicked(){QColor color = QColorDialog::getColor(upper_left,this);  if(color.isValid()){SetULeft(color);}}
void DialogPreview::btn_ur_clicked(){QColor color = QColorDialog::getColor(upper_right,this);if(color.isValid()){SetURight(color);}}

void DialogPreview::draw()
{
    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, upper_left.rgb());
    image.setPixel(0, 1, lower_left.rgb());
    image.setPixel(1, 0, upper_right.rgb());
    image.setPixel(1, 1, lower_right.rgb());
    QImage gradient = image.scaled(width(),height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(QPixmap::fromImage(gradient));
    btn_ul->setGeometry(0,0,width()/2,height()/2);
    btn_ur->setGeometry(btn_ul->width(),0,width()/2,height()/2);
    btn_ll->setGeometry(0,height()/2,width()/2,height()/2);
    btn_lr->setGeometry(btn_ll->width(),height()/2,width()/2,height()/2);
}
void DialogPreview::resizeEvent(QResizeEvent*){draw();}
