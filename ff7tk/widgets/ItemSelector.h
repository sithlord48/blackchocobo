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
#ifndef ITEMSELECTOR_H
#define ITEMSELECTOR_H

#include <QtWidgets>
//Include Data class
#include "../data/FF7Item.h"

class ItemSelector : public QWidget
{
    Q_OBJECT
public:
	explicit ItemSelector(qreal Scale=1,QWidget *parent = 0);
    int id();// current id
    int combo_item_width();//width of the item box.
    int combo_type_width();//width of the type box.
    int qty_width();//width of qty area.
    void setFixedHeight(int h);
signals:
    void item_changed(quint16);//return selected rawitem
public slots:
    void setCurrentItem(quint16 ff7item);
    void setCurrentItem(int id,int qty);
    void setMaximumQty(int maxQty);
    void setEditableItemCombo(bool editable);
private slots:
    void setFilter(int type);
    void comboItem_changed(int index);
    void sb_qty_changed(int qty);
    void btn_remove_clicked();
private:
    void init_display();
    void init_connections();
    void init_data();
    int type_offset(int type);
    FF7Item *Items;
    QComboBox *combo_type;
    QComboBox *combo_item;
    QSpinBox  *sb_qty;
    QPushButton *btn_remove;
    quint16 current_item;
	qreal scale;
};
#endif // ITEMSELECTOR_H
