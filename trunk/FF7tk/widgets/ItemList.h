#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include "ItemSelector.h"
#include <QSignalMapper>
#include "ItemPreview.h"

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
    //void customContextMenuRequested(const QPoint &pos);
private:
    ItemSelector * itemselector[320];
    ItemPreview *item_preview;
    QTableWidget * tbl_item;
    QList<quint16> itemlist;
};

#endif // ITEMLIST_H
