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
#include <QMessageBox>

bool ItemList::eventFilter(QObject *obj, QEvent *ev)
{//Catch toolTip related events and process them(i.e custom tooltips :P)
    if(obj->isWidgetType())
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
    else{return event(ev);}
}
ItemList::ItemList(QWidget *parent) : QTableWidget(parent)
{


    installEventFilter(this);
    createdTooltip=false;
    setRowCount(320);
    setColumnCount(3);
    setStyleSheet(QString(";"));//set a style and itemSelector will have a normal size column 1
    setEditTriggers(QAbstractItemView::NoEditTriggers);// thats a long 0
    setContextMenuPolicy(Qt::CustomContextMenu);
    setSelectionMode(QAbstractItemView::NoSelection);
    itemSelector = new ItemSelector();
    createdSelector=true;
    setCellWidget(0,0,itemSelector);
    setColumnWidth(1,itemSelector->combo_item_width());
    itemSelector->setFixedWidth(itemSelector->combo_item_width()+66+this->font().pointSize()*5+verticalScrollBar()->width()+contentsMargins().left()+contentsMargins().right());
    if(QT_VERSION<0x050000)
    {//QT4 Style Connections
        connect(this,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(listSelectionChanged(int,int,int,int)));
    }
    else
    {//QT5 Style Connections
        /*
        connect(this::currentCellChanged(int,int,int,int),this::listSelectionChanged(int,int,int,int));
        */
    }
    horizontalHeader()->hide();
    verticalHeader()->hide();
    verticalScrollBar()->setToolTip("");//negate custom tooltip
    adjustSize();
    createdSelector = false;
    for(int i=0;i<320;i++){itemlist.append(FF7Item::EmptyItemData);}//initlize the data.
    this->setFixedWidth(itemSelector->size().width());
    itemupdate();// redraw Display After data init.
}


void ItemList::setItems(QList<quint16> items)
{
    itemlist = items;
    createdSelector=false;
    itemupdate();
}
void ItemList::itemSelector_changed(quint16 item)
{
    if(createdTooltip)
    {
        itemPreview->close();
        createdTooltip=false;
    }
    itemlist.replace(sender()->objectName().toInt(),item);
    emit(itemsChanged(itemlist));
}

void ItemList::itemupdate()
{
    QTableWidgetItem *newItem;
    int j= currentRow();
    int column_one_width =columnWidth(1);
    reset(); // just incase
    clearContents();
    setColumnWidth(0,40);
    setColumnWidth(1,column_one_width);
    setColumnWidth(2,(this->font().pointSize()*5)+22);
    setRowCount(320);

    for (int i=0;i<320;i++) // set up items
    {
        if (itemlist.at(i) == FF7Item::EmptyItemData)
        {
            newItem = new QTableWidgetItem("",0);
            setItem(i,0,newItem);
            newItem = new QTableWidgetItem(tr("-------EMPTY--------"),0);
            setItem(i,1,newItem);
            setRowHeight(i,22);
            newItem = new QTableWidgetItem("",0);
            setItem(i,2,newItem);
        }
        else if(Items.itemId(itemlist.at(i)) > 319)
        {
            newItem = new QTableWidgetItem("",0);
            setItem(i,0,newItem);
            newItem = new QTableWidgetItem(tr("-------BAD ID-------"),0);
            setItem(i,1,newItem);
            setRowHeight(i,22);
            newItem = new QTableWidgetItem("",0);
            setItem(i,2,newItem);
        }
        else
        {
            QString qty;
            //Replaced by new item engine. (Vegeta_Ss4)
            newItem = new QTableWidgetItem(Items.Icon(Items.itemId(itemlist.at(i))),"",0);
            setItem(i,0,newItem);
            newItem = new QTableWidgetItem(Items.Name(Items.itemId(itemlist.at(i))),0);
            setItem(i,1, newItem);
            setRowHeight(i,22);
            newItem = new QTableWidgetItem(qty.setNum(Items.itemQty(itemlist.at(i))),0);
            setItem(i,2,newItem);

        }
    }
    blockSignals(true);
    setCurrentCell(j,0);
    if(createdSelector==false){clearSelection();}//if there is no Selector made its because of a new item list.
    blockSignals(false);
}
void ItemList::listSelectionChanged(int row,int colum,int prevRow,int prevColum)
{
    if(createdSelector){itemSelector->close();createdSelector=false;}
    if(createdTooltip){itemPreview->close();createdTooltip=false;}
    if ((colum >=0 || colum <= 0) && (prevRow >=0 || prevRow <= 0) &&(prevColum >=0 || prevColum <= 0))
    {/*Stop Warning About unused vars*/}
    itemupdate();
    itemSelector = new ItemSelector;
    createdSelector = true;
    itemSelector->setObjectName(QString::number(row));
    //Clear the Current Row So the item selector is not over text.
    QTableWidgetItem *newItem = new QTableWidgetItem("",0);
    setItem(row,0,newItem);
    newItem = new QTableWidgetItem("",0);//can't put the same item in two places.
    setItem(row,1,newItem);
    newItem = new QTableWidgetItem("",0);//can't put the same item in two places.
    setItem(row,2,newItem);
    itemSelector->setMinimumWidth(itemSelector->width());
    setCellWidget(row,0,itemSelector);
    itemSelector->setCurrentItem(itemlist.at(row));
    if(QT_VERSION<0x050000)
    {//QT4 Style Connection
        connect(itemSelector,SIGNAL(item_changed(quint16)),this,SLOT(itemSelector_changed(quint16)));
    }
    else
    {//QT5 Style Connection
        /*
        connect(itemSelector::item_changed(quint16),this::itemSelector_changed(quint16));
        */
    }
}
