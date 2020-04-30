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

#include <QTableWidget>
#include <QEvent>

class ItemPreview;
class ItemSelector;

class ItemList : public QTableWidget
{
    Q_OBJECT
public:
    explicit ItemList(qreal Scale = 1, QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject *, QEvent *);
    void changeEvent(QEvent *e);
signals:
    void itemsChanged(QList<quint16> items);
public slots:
    void setItems(QList<quint16> items);
    void setMaximumItemQty(int maxQty);
    void setEditableItemCombo(bool);
private slots:
    void listSelectionChanged(int row, int colum, int prevRow, int prevColum);
    void itemSelector_changed(quint16);
private:
    void itemupdate();
    void updateItem(int row);
    ItemSelector *itemSelector = nullptr;
    ItemPreview *itemPreview = nullptr;
    QList<quint16> itemlist;
    qreal scale;
    int itemQtyLimit;
    bool createdSelector;
    bool createdTooltip;
    bool editableItemCombo;
};
