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
#include "ItemList.h"

bool ItemList::eventFilter(QObject *obj, QEvent *ev)
{//Catch toolTip related events and process them(i.e custom tooltips :P)
    if(obj->isWidgetType() && obj->objectName()== "ItemList")
    {//our object will be the itemlist always in this event.
        int row=-1;//row @ -1 this way we can catch when were not over A QTableWidgetItem
        QTableWidgetItem *tbl_item=itemAt(mapFromGlobal(viewport()->cursor().pos()));
        if(tbl_item !=0){row =tbl_item->row();}//And only update our row if vaild.
        if(ev->type() == QEvent::ToolTip)
        {//ToolTip Event Popup.
            if(createdTooltip)
            {//We already are showing a tooltip
                if(row ==-1)
                {//Invaild Row (off widget perhaps)
                    itemPreview->close();
                    createdTooltip=false;
                    return true;
                }
                else
                {//On a QTableWidgetItem if we are on the same one do nothing
                    if(Items.itemId(itemlist.at(row))==itemPreview->id()){return true;}
                    else
                    {//otherwise close our old ItemPreview
                        itemPreview->close();
                        createdTooltip=false;
                        return true;
                    }
                }
            }//end of If(createdToolTip)
            //If our Entry is an Empty Item then don't show a tooltip
            if(Items.itemId(itemlist.at(row))==FF7Item::EmptyItem){return true;}
            else
            {//unless our xcoord is off on the scrollbar) show for item in row
             //scrollbars are ontop of the viewport and trigger events for items below.
             //the width() function returns inner size so it stops at scrollbar
                if(mapFromGlobal(cursor().pos()).x()>viewport()->width()){return true;}
                //make an ItemPreview, but give it A ToolTip Flags so it looks/acts as one
                itemPreview = new ItemPreview(this,Qt::ToolTip);
                itemPreview->setItem(Items.itemId(itemlist.at(row)));
                itemPreview->setGeometry(QRect(cursor().pos(),itemPreview->size()));
                itemPreview->show();
                createdTooltip=true;
                return true;
            }
        }//End of ToolTip Event Processing
        else if(ev->type()==QEvent::HoverLeave)
        {//HoverLeave Event is used to clean up tooltips when needed.
            if(createdTooltip)
            {//if we have made a tooltip then we need to clean it up.
                if(row ==-1)
                {//off widget maybe , but not on a QTableWidgetItem
                    itemPreview->close();
                    createdTooltip=false;
                    return true;
                }
                else
                {//This case is called when a tooltip is spawned as its placed under your cursor
                    if(Items.itemId(itemlist.at(row))==itemPreview->id()){return true;}
                    else
                    {//if the item is the same do nothing, otherwise you have to close your tooltip
                        itemPreview->close();
                        createdTooltip=false;
                        return true;
                    }
                }
            }//End Of HoverLeave Processing
            else{return event(ev);}
        }
        else{return event(ev);}
    }
    else{return false;}
}
ItemList::ItemList(QWidget *parent) : QTableWidget(parent)
{
    setObjectName("ItemList");
    installEventFilter(this);
    createdTooltip=false;
    itemQtyLimit=127;
    setRowCount(320);
    setColumnCount(3);
    setStyleSheet(QString(";"));//set a style and itemSelector will have a normal size column 1
    setEditTriggers(QAbstractItemView::NoEditTriggers);// thats a long 0
    setContextMenuPolicy(Qt::NoContextMenu);
    setSelectionMode(QAbstractItemView::NoSelection);
    itemSelector = new ItemSelector();
    createdSelector=true;
    setCellWidget(0,0,itemSelector);
    setColumnWidth(0,itemSelector->combo_type_width());
    setColumnWidth(1,itemSelector->combo_item_width());
    setColumnWidth(2,itemSelector->qty_width());
    itemSelector->setFixedWidth(itemSelector->combo_type_width()+itemSelector->combo_item_width()+itemSelector->qty_width());
    connect(this,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(listSelectionChanged(int,int,int,int)));
    horizontalHeader()->hide();
    verticalHeader()->hide();
    verticalScrollBar()->setToolTip("");//negate custom tooltip
    for(int i=0;i<320;i++){itemlist.append(FF7Item::EmptyItemData);}//initlize the data.
    itemSelector->setFixedHeight(this->sizeHintForRow(0)+contentsMargins().top()+contentsMargins().bottom());
    setFixedWidth(itemSelector->frameGeometry().width()+ verticalScrollBar()->width() + contentsMargins().left() + contentsMargins().right()+6);
    itemSelector->close();
    createdSelector = false;
    itemupdate();// redraw Display After data init.
}

void ItemList::setMaximumItemQty(int maxQty)
{
    itemQtyLimit = maxQty;
    //check that any items Qty is not greater then the new Qty. if so fix it.
    for(int i=0;i<320;i++)
    {
        if( (Items.itemQty(itemlist.at(i)) > itemQtyLimit) && (itemlist.at(i)!=FF7Item::EmptyItemData ) )
        {//qty not above limit and item is not empty.
            itemlist.replace(i,Items.itemEncode(Items.itemId(itemlist.at(i)),itemQtyLimit));
        }
        else{continue;}
    }
    itemupdate();
}

void ItemList::setItems(QList<quint16> items)
{
    itemlist = items;
    if(createdSelector){itemSelector->close();createdSelector=false;}
    if(createdTooltip){itemPreview->close();createdTooltip=false;}
    itemupdate();
}
void ItemList::itemSelector_changed(quint16 item)
{
    if(createdTooltip){itemPreview->close();createdTooltip=false;}

    itemlist.replace(sender()->objectName().toInt(),item);
    if(item == FF7Item::EmptyItemData)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem("",0);
        setItem(sender()->objectName().toInt(),0,newItem);
        newItem = new QTableWidgetItem(tr("-------EMPTY--------"),0);
        setItem(sender()->objectName().toInt(),1,newItem);
        setRowHeight(sender()->objectName().toInt(),22);
        newItem = new QTableWidgetItem("",0);
        setItem(sender()->objectName().toInt(),2,newItem);
    }
    else if(createdSelector)
    {
        for(int i=0;i<3;i++)
        {
            QTableWidgetItem* newItem = new QTableWidgetItem("",0);
            setItem(sender()->objectName().toInt(),i,newItem);
        }
    }
    emit(itemsChanged(itemlist));
}

void ItemList::itemupdate()
{
    int j= currentRow();
    int column0width =columnWidth(0);
    int column1width =columnWidth(1);
    int column2width =columnWidth(2);
    int selectorLocation=321;
    clearContents();
    setColumnWidth(0,column0width);
    setColumnWidth(1,column1width);
    setColumnWidth(2,column2width);
    setRowCount(320);
    if(createdSelector){selectorLocation = itemSelector->objectName().toInt(); itemSelector->setMaximumQty(itemQtyLimit);}
    for (int i=0;i<320;i++) // set up items
    {
        if(i == selectorLocation){continue;}
        else{updateItem(i);}

    }
    blockSignals(true);
    if(createdSelector)
    {
        setCurrentCell(j,0);
        setCellWidget(j,0,itemSelector);
        if(itemlist.at(j)== FF7Item::EmptyItemData){/*nice empty under the selector*/}
        else
        {//wipe the data under the selector so its easier to read.
            for(int i=0;i<3;i++)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem("",0);
                setItem(j,i,newItem);
            }
        }
        itemSelector->setCurrentItem(itemlist.at(j));
    }
    blockSignals(false);
}
void ItemList::listSelectionChanged(int row,int colum,int prevRow,int prevColum)
{
    if(createdSelector){itemSelector->close();createdSelector=false;}
    if(createdTooltip){itemPreview->close();createdTooltip=false;}
    if(prevColum>=0 ||prevColum<=0){/*Stop warning about unused var.*/}
    if(colum<0||row <0){return;}//Ingore if selecting -1 (clearContents)
    if (prevRow>=0){updateItem(prevRow);}//update the previews Row so its filled again.
    itemSelector = new ItemSelector;
    itemSelector->setEditableItemCombo(editableItemCombo);
    createdSelector = true;
    itemSelector->setMaximumQty(itemQtyLimit);
    itemSelector->setObjectName(QString::number(row));
   
    if(itemlist.at(row)==FF7Item::EmptyItemData){/*nice Empty Item under the selector*/}
    else
    {//Clear whats under the selector 
        for(int i=0;i<3;i++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem("",0);
            setItem(row,i,newItem);
        }
    }
    itemSelector->setMinimumWidth(itemSelector->width());
    setCellWidget(row,0,itemSelector);
    itemSelector->setCurrentItem(itemlist.at(row));
    connect(itemSelector,SIGNAL(item_changed(quint16)),this,SLOT(itemSelector_changed(quint16)));
}
void ItemList::updateItem(int row)
{
    QTableWidgetItem *newItem;
    if (itemlist.at(row) == FF7Item::EmptyItemData)
    {
        newItem = new QTableWidgetItem("",0);
        setItem(row,0,newItem);
        newItem = new QTableWidgetItem(tr("-------EMPTY--------"),0);
        setItem(row,1,newItem);
        setRowHeight(row,22);
        newItem = new QTableWidgetItem("",0);
        setItem(row,2,newItem);
    }
    else if(Items.itemId(itemlist.at(row)) > 319)
    {
        newItem = new QTableWidgetItem("",0);
        setItem(row,0,newItem);
        newItem = new QTableWidgetItem(tr("-------BAD ID-------"),0);
        setItem(row,1,newItem);
        setRowHeight(row,22);
        newItem = new QTableWidgetItem("",0);
        setItem(row,2,newItem);
    }
    else
    {
        QString qty;
        //Replaced by new item engine. (Vegeta_Ss4)
        newItem = new QTableWidgetItem(Items.icon(Items.itemId(itemlist.at(row))),"",0);
        setItem(row,0,newItem);
        newItem = new QTableWidgetItem(Items.name(Items.itemId(itemlist.at(row))),0);
        setItem(row,1, newItem);
        setRowHeight(row,22);
        newItem = new QTableWidgetItem(qty.setNum(Items.itemQty(itemlist.at(row))),0);
        setItem(row,2,newItem);
    }
}
void ItemList::setEditableItemCombo(bool editable){editableItemCombo=editable;}
