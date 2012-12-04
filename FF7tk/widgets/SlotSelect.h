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
#ifndef SLOTSELECT_H
#define SLOTSELECT_H

#include <QDialog>
#include <QScrollArea>
#include <QLayout>
#include <QFrame>
#include "../static_data/FF7Save.h"
#include "../static_data/FF7Char.h"
#include "SlotPreview.h"

class SlotSelect : public QDialog
{
    Q_OBJECT
public:
    explicit SlotSelect(QWidget *parent = 0,FF7Save *data=0);
private slots:
    void button_clicked(int s);
    void remove_slot(int s);
    void copy_slot(int s);
    void paste_slot(int s);
private:
    void setSlotPreview(int s);
    void ReIntSlot(int s);
    QFrame *frm_preview;
    QVBoxLayout *preview_layout;
    QScrollArea *list_preview;
    SlotPreview *preview[15];
    //Private Data
    FF7Save *ff7;
    FF7Char Chars;
};

#endif // SLOTSELECT_H
