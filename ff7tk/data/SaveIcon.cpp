/****************************************************************************/
//    copyright 2010 Arzel Jérôme <myst6re@gmail.com>                       //
//              2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>         //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "SaveIcon.h"

#include <QByteArray>
#include <QList>
#include <QTimer>

QTimer SaveIcon::timer;

SaveIcon::SaveIcon()
    : nbFrames(0)
{
}

SaveIcon::SaveIcon(const QByteArray &data, quint8 nbFrames)
{
    setAll(data, nbFrames);
}

SaveIcon::SaveIcon(const QList<QByteArray> &data)
{
    setAll(data);
}

void SaveIcon::setAll(const QByteArray &data, quint8 nbFrames)
{
    this->data = data;
    this->nbFrames = nbFrames;
    if(nbFrames > 1) {
        connect(&timer, &QTimer::timeout, this, &SaveIcon::nextFrame);
        timer.start(160);
    }
}

void SaveIcon::setAll(const QList<QByteArray> &data)
{
    this->data.clear();
    nbFrames = quint8(data.size());
    for(int i= 0; i < nbFrames; i++) {
        this->data.append(data.at(i));
    }
    if(nbFrames>1) {
        connect(&timer, &QTimer::timeout, this, &SaveIcon::nextFrame);
        timer.start(160);
    }
}

const QByteArray &SaveIcon::save()
{
    return data;
}

QByteArray SaveIcon::sauver()
{
    return data;
}

QPixmap SaveIcon::icon(bool chocobo_world_icon)
{
    quint16 i;
    quint8 y = 0, x = 0;

    if (data.isEmpty()) {
        return QPixmap();
    }

    if (!chocobo_world_icon) {
        //palette
        const char *access_data = data.constData();
        QList<QRgb> colors;
        quint16 color;
        for (i = 0 ; i < 16 ; ++i) {
            memcpy(&color, access_data, 2);
            colors.append(qRgb(int((color & 31) * 8.2258), int((color >> 5 & 31) * 8.2258), int((color >> 10 & 31) * 8.2258)));
            access_data += 2;
        }

        QImage image(16, 16, QImage::Format_RGB32);
        quint8 index;
        quint16 firstPos = 32 + curFrame * 128, lastPos = firstPos + 128;

        if (data.size() < lastPos) {
            return QPixmap();
        }

        for (i = firstPos ; i < lastPos ; ++i) {
            index = quint8(data.at(i));
            image.setPixel(x, y, colors.at(index & 0xF));
            if (x == 15) {
                x = 0;
                ++y;
            } else {
                ++x;
            }
            image.setPixel(x, y, colors.at(index >> 4));

            if (x == 15) {
                x = 0;
                ++y;
            } else {
                ++x;
            }
        }
        return QPixmap::fromImage(image);
    }

    if (data.size() != 288) {
        return QPixmap();
    }

    QImage image(32, 32, QImage::Format_Mono);
    quint8 j, curPx;

    for (i = 160 ; i < 288 ; ++i) {
        curPx = quint8(data.at(i));
        for (j = 0 ; j < 8 ; ++j) {
            image.setPixel(x, y, !((curPx >> j) & 1));
            if (x == 31) {
                x = 0;
                ++y;
            } else {
                ++x;
            }
        }
    }
    return QPixmap::fromImage(image);
}

void SaveIcon::nextFrame()
{
    if (nbFrames != 0) {
        curFrame = (curFrame + 1) % nbFrames;
        QPixmap pix = icon();

        if (!pix.isNull()) {
            emit nextIcon(pix);
        }
    }
}
