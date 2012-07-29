#include "ItemList.h"
//#include <QMessageBox>
ItemList::ItemList(QWidget *parent) :
    QWidget(parent)
{
    tbl_item = new QTableWidget(320,2);
    tbl_item->setContextMenuPolicy(Qt::CustomContextMenu);
    tbl_item->setSelectionBehavior(QAbstractItemView::SelectRows);
    //tbl_item->setSelectionMode(QAbstractItemView::NoSelection);

    connect(tbl_item,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(listSelectionChanged(int,int,int,int)));
    connect(tbl_item,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customContextMenuRequested(QPoint)));
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
    itemupdate();
    //for(int i=0;i<320;i++){itemselector[i]->setCurrentItem(items.at(i));}
}
void ItemList::itemselector_changed(quint16 item)
{
    itemlist.replace(sender()->objectName().toInt(),item);
    emit(itemsChanged(itemlist));
}
// Dont use this unless you can kill bc might not release pop up or kbd/mouse focus.
void ItemList::customContextMenuRequested(const QPoint &pos)
{
        item_preview = new ItemPreview(this);
        item_preview->setItem(Items.itemId(itemlist.at(tbl_item->currentRow())));
        item_preview->exec(tbl_item->mapToGlobal(pos));
}

void ItemList::itemupdate()
{
    QTableWidgetItem *newItem;
    int j= tbl_item->currentRow();
    tbl_item->reset(); // just incase
    tbl_item->clearContents();
    //if(_init){tbl_item->setColumnWidth(0,tbl_item->width()-54);}
    tbl_item->setColumnWidth(0,232);
    tbl_item->setColumnWidth(1,32);
    tbl_item->setRowCount(320);

    for (int i=0;i<320;i++) // set up items
    {
        if (Items.itemQty(itemlist.at(i)) == 0x7F && Items.itemId(itemlist.at(i)) == 0x1FF)
        {
            newItem = new QTableWidgetItem(tr("-------EMPTY--------"),0);
            newItem->setToolTip("");
            tbl_item->setItem(i,0,newItem);
            tbl_item->setRowHeight(i,22);
            newItem = new QTableWidgetItem("",0);
            tbl_item->setItem(i,1,newItem);
        }
        else if(Items.itemId(itemlist.at(i)) > 319)
        {
            newItem = new QTableWidgetItem(tr("-------BAD ID-------"),0);
            newItem->setToolTip("");
            tbl_item->setItem(i,0,newItem);
            tbl_item->setRowHeight(i,22);
            newItem = new QTableWidgetItem("",0);
            tbl_item->setItem(i,1,newItem);
        }
        else
        {
            QString qty;
            //Replaced by new item engine. (Vegeta_Ss4)
            newItem = new QTableWidgetItem(Items.Icon(Items.itemId(itemlist.at(i))),Items.Name(Items.itemId(itemlist.at(i))),0);
            newItem->setToolTip(Items.Desc(Items.itemId(itemlist.at(i))));
            tbl_item->setItem(i,0, newItem);
            tbl_item->setRowHeight(i,22);
            newItem = new QTableWidgetItem(qty.setNum(Items.itemQty(itemlist.at(i))),0);
            tbl_item->setItem(i,1,newItem);

        }
    }
    tbl_item->blockSignals(true);
    tbl_item->setCurrentCell(j,0);
    tbl_item->blockSignals(false);
}
void ItemList::listSelectionChanged(int row,int colum,int prevRow,int prevColum)
{
    //QMessageBox::information(this,"title",QString::number(prevRow));
    //if(prevRow != -1 &&(prevRow !=row)) {itemselector->~QWidget();}
    if ((colum >=0 || colum <= 0) && (prevRow >=0 || prevRow <= 0) &&(prevColum >=0 || prevColum <= 0))
    {/*Stop Warning About unused vars*/}
    itemupdate();
    itemselector = new ItemSelector();
    itemselector->setMinimumWidth(270);
    itemselector->setObjectName(QString::number(row));
    tbl_item->setCellWidget(row,0,itemselector);
    itemselector->setCurrentItem(itemlist.at(row));
    connect(itemselector,SIGNAL(item_changed(quint16)),this,SLOT(itemselector_changed(quint16)));
}
