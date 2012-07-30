#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QSignalMapper>
#include "ItemPreview.h"

#include "ItemSelector.h"
#include "../static_data/FF7Item.h"

class ItemList : public QWidget
{
    Q_OBJECT
public:
    explicit ItemList(QWidget *parent = 0);
    
signals:
    void itemsChanged(QList<quint16> items);
public slots:
    void setItems(QList<quint16> items);

private slots:
    void itemselector_changed(quint16);
    void listSelectionChanged(int row,int colum,int prevRow,int prevColum);
    void customContextMenuRequested(const QPoint &pos);
private:
    void itemupdate();
    FF7Item Items;
    ItemSelector * itemselector;
    ItemPreview *item_preview;
    QTableWidget * tbl_item;
    QList<quint16> itemlist;
    bool createdSelector;
};

#endif // ITEMLIST_H
