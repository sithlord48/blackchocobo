#include "ItemList.h"
#include <QMessageBox>
ItemList::ItemList(QWidget *parent) :
    QWidget(parent)
{
    tbl_item = new QTableWidget(320,1);
    tbl_item->setContextMenuPolicy(Qt::CustomContextMenu);
    tbl_item->setSelectionMode(QAbstractItemView::NoSelection);
    for(int i=0;i<320;i++)
    {
        itemselector[i] = new ItemSelector;
        itemselector[i]->setObjectName(QString::number(i));
        tbl_item->setCellWidget(i,0,itemselector[i]);
        connect(itemselector[i],SIGNAL(item_changed(quint16)),this,SLOT(itemselector_changed(quint16)));
        //connect(tbl_item,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customContextMenuRequested(QPoint)));
    }
    tbl_item->horizontalHeader()->hide();
    tbl_item->verticalHeader()->hide();
    tbl_item->setColumnWidth(0,270);
    tbl_item->adjustSize();
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(tbl_item);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);
    this->adjustSize();

    for(int i=0;i<320;i++){itemlist.append(0xFFFF);}//initlize the data.
}
void ItemList::setItems(QList<quint16> items)
{
    itemlist = items;
    for(int i=0;i<320;i++){itemselector[i]->setCurrentItem(items.at(i));}
}
void ItemList::itemselector_changed(quint16 item)
{
    itemlist.replace(sender()->objectName().toInt(),item);
    emit(itemsChanged(itemlist));
}
/* Dont use this unless you can kill bc might not release pop up or kbd/mouse focus.
void ItemList::customContextMenuRequested(const QPoint &pos)
{
        item_preview = new ItemPreview(this);
        item_preview->setItem(itemselector[tbl_item->currentRow()]->id());
        item_preview->exec(tbl_item->mapToGlobal(pos));
}
*/
