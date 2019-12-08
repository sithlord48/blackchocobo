/****************************************************************************/
//    copyright 2012 - 2019  Chris Rizzitello <sithlord48@gmail.com>        //
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
#include <QColorDialog>

DialogPreview::DialogPreview(QWidget *parent) :
    QLabel(parent)
    , btn_ul(new QPushButton(this))
    , btn_ur(new QPushButton(this))
    , btn_ll(new QPushButton(this))
    , btn_lr(new QPushButton(this))
{
    QString style = QString("QPushButton:enabled{background-color: #00000000;border:0px;} QPushButton:hover{background-color: %1;}")
                    .arg(palette().highlight().color().name(QColor::HexRgb).insert(1, QString("60")));
    setStyleSheet(style);
    setMinimumSize(60, 30);

    connect(btn_ul, &QPushButton::clicked, this, [this] {
        QColor color = QColorDialog::getColor(upper_left, this);
        if (color.isValid())
        {
            SetULeft(color);
        }
    });

    connect(btn_ur, &QPushButton::clicked, this, [this] {
        QColor color = QColorDialog::getColor(upper_right, this);
        if (color.isValid())
        {
            SetLRight(color);
        }
    });

    connect(btn_ll, &QPushButton::clicked, this, [this] {
        QColor color = QColorDialog::getColor(lower_left, this);
        if (color.isValid())
        {
            SetLLeft(color);
        }
    });

    connect(btn_lr, &QPushButton::clicked, this, [this] {
        QColor color = QColorDialog::getColor(lower_right, this);
        if (color.isValid())
        {
            SetLRight(color);
        }
    });

    draw();
}

void DialogPreview::SetLLeft(QColor newColor)
{
    if (lower_left != newColor) {
        lower_left = newColor;
        emit LL_ColorChanged(newColor);
        draw();
    }
}

void DialogPreview::SetULeft(QColor newColor)
{
    if (upper_left != newColor) {
        upper_left = newColor;
        emit UL_ColorChanged(newColor);
        draw();
    }
}

void DialogPreview::SetLRight(QColor newColor)
{
    if (lower_right != newColor) {
        lower_right = newColor;
        emit LR_ColorChanged(newColor);
        draw();
    }
}

void DialogPreview::SetURight(QColor newColor)
{
    if (upper_right != newColor) {
        upper_right = newColor;
        emit UR_ColorChanged(newColor);
        draw();
    }
}

void DialogPreview::draw()
{
    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, upper_left.rgb());
    image.setPixel(0, 1, lower_left.rgb());
    image.setPixel(1, 0, upper_right.rgb());
    image.setPixel(1, 1, lower_right.rgb());
    QImage gradient = image.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(QPixmap::fromImage(gradient));
    btn_ul->setGeometry(0, 0, width() / 2, height() / 2);
    btn_ur->setGeometry(btn_ul->width(), 0, width() / 2, height() / 2);
    btn_ll->setGeometry(0, height() / 2, width() / 2, height() / 2);
    btn_lr->setGeometry(btn_ll->width(), height() / 2, width() / 2, height() / 2);
}

void DialogPreview::resizeEvent(QResizeEvent *)
{
    draw();
}
