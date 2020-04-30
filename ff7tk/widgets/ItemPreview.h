/****************************************************************************/
//    copyright 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>         //
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
#pragma once

#include <QWidget>

class QGroupBox;
class QHBoxLayout;
class QLabel;
class QListWidget;

class ItemPreview : public QWidget
{
    Q_OBJECT
public:
    ItemPreview(QFlags<Qt::WindowType> WindowFlags = Qt::Widget, float Scale = 1, QWidget *parent = nullptr);
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
    QHBoxLayout *makeMateriaPair(QLabel *slot1, QLabel *slot2 , QLabel *link);
    bool eventFilter(QObject *obj, QEvent *ev);
    QLabel *lbl_name = nullptr;
    QLabel *lbl_desc = nullptr;
    QLabel *lbl_icon = nullptr;
    QList<QLabel *> slotLabels;
    QList<QLabel *> slotLinks;
    QGroupBox *materia_slot_box = nullptr;
    QGroupBox *elemental_box = nullptr;
    QGroupBox *status_box = nullptr;
    QListWidget *elemental_effects = nullptr;
    QListWidget *status_effects = nullptr;
    int _id;
    float scale;
    QSize slotSize;
    QSize linkSize;
};
