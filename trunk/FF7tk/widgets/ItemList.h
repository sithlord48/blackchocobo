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
#ifndef ITEMLIST_H
#define ITEMLIST_H

//#include <QTableWidget>
//#include <QHeaderView>
//#include <QScrollBar>
//#include <QEvent>
#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif

#include "ItemPreview.h"
#include "ItemSelector.h"
#include "../static_data/FF7Item.h"

class ItemList : public QTableWidget
{
    Q_OBJECT
public:
    explicit ItemList(QWidget *parent = 0);
protected:
    bool eventFilter(QObject *, QEvent *);
signals:
    void itemsChanged(QList<quint16> items);
public slots:
    void setItems(QList<quint16> items);

private slots:
    void listSelectionChanged(int row,int colum,int prevRow,int prevColum);
    void itemSelector_changed(quint16);
private:
    void itemupdate();
    FF7Item Items;
    ItemSelector * itemSelector;
    ItemPreview *itemPreview;
    QList<quint16> itemlist;
    bool createdSelector;
    bool createdTooltip;
};

#endif // ITEMLIST_H
