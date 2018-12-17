/****************************************************************************/
//    copyright 2012 - 2018 Chris Rizzitello <sithlord48@gmail.com>         //
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

#pragma once
#include <QtWidgets>

class DialogPreview : public QLabel
{
    Q_OBJECT
public:
    DialogPreview(QWidget *parent = nullptr);
    ~DialogPreview() = default;
    inline QColor ll(){return lower_left;}
    inline QColor lr(){return lower_right;}
    inline QColor ul(){return upper_left;}
    inline QColor ur(){return upper_right;};
    void SetLLeft(QColor newColor);
    void SetULeft(QColor newColor);
    void SetLRight(QColor newColor);
    void SetURight(QColor newColor);
signals:
     void LL_ColorChanged(QColor color);
     void LR_ColorChanged(QColor color);
     void UL_ColorChanged(QColor color);
     void UR_ColorChanged(QColor color);
private:
    void draw();
    QColor upper_left;
    QColor upper_right;
    QColor lower_left;
    QColor lower_right;
    QPushButton *btn_ul = nullptr;
    QPushButton *btn_ur = nullptr;
    QPushButton *btn_ll = nullptr;
    QPushButton *btn_lr = nullptr;
protected:
    void resizeEvent(QResizeEvent*);
};

