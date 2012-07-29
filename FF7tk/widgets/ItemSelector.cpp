#include "ItemSelector.h"
//#include <QMessageBox>
// include icon data
#include "../static_data/icons/Common_Icons/quit.xpm"

ItemSelector::ItemSelector(QWidget *parent) :
    QWidget(parent)
{
    init_display();
    init_connections();
}
void ItemSelector::init_display()
{
    combo_type = new QComboBox;
    combo_type->setFixedWidth(40);

    combo_item = new QComboBox;

    sb_qty = new QSpinBox;
    sb_qty->setFixedWidth(this->font().pointSize()*5);
    sb_qty->setAlignment(Qt::AlignCenter);
    sb_qty->setMaximum(127);

    btn_remove = new QPushButton;
    btn_remove->setIcon(QIcon(QPixmap(quit_xpm)));
    btn_remove->setToolTip(tr("Empty Item"));
    btn_remove->setFixedSize(22,22);

    init_data(); //before setting layout set data.
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(2);
    layout->addWidget(combo_type);
    layout->addWidget(combo_item);
    layout->addWidget(sb_qty);
    layout->addWidget(btn_remove);
    this->setLayout(layout);
    this->setFixedHeight(22);
    this->adjustSize();
}
void ItemSelector::init_connections()
{
    connect(combo_type,SIGNAL(currentIndexChanged(int)),this,SLOT(setFilter(int)));
    connect(combo_item,SIGNAL(currentIndexChanged(int)),this,SLOT(comboItem_changed(int)));
    connect(sb_qty,SIGNAL(valueChanged(int)),this,SLOT(sb_qty_changed(int)));
    connect(btn_remove,SIGNAL(clicked()),this,SLOT(btn_remove_clicked()));
}
void ItemSelector::init_data()
{
    combo_type->addItem(Items.Icon(1),tr(""));
    combo_type->addItem(Items.Icon(256),tr(""));
    combo_type->addItem(Items.Icon(288),tr(""));
    combo_type->addItem(Items.Icon(128),tr(""));
    combo_type->addItem(Items.Icon(160),tr(""));
    combo_type->addItem(Items.Icon(144),tr(""));
    combo_type->addItem(Items.Icon(176),tr(""));
    combo_type->addItem(Items.Icon(190),tr(""));
    combo_type->addItem(Items.Icon(201),tr(""));
    combo_type->addItem(Items.Icon(215),tr(""));
    combo_type->addItem(Items.Icon(229),tr(""));
    combo_type->addItem(Items.Icon(242),tr(""));

    //Fill Combo_Item (all items type is 0 or no filter defalut)
    for(int i=0;i<320;i++){combo_item->addItem(Items.Icon(i),Items.Name(i));}
    combo_type->setCurrentIndex(-1);
    combo_item->setCurrentIndex(-1);
    current_item=0xFFFF;
}
void ItemSelector::btn_remove_clicked()
{
    combo_item->blockSignals(true);
    combo_type->setCurrentIndex(-1);
    combo_item->setCurrentIndex(-1);
    combo_item->blockSignals(false);

    sb_qty->blockSignals(true);
    sb_qty->setValue(-1);
    sb_qty->clear();
    sb_qty->blockSignals(false);

    current_item = 0xFFFF;
    emit item_changed(current_item);
}
void ItemSelector::setFilter(int type)
{
    //for hiding no filter.
    type++;

    int id = itemId(current_item);
    combo_item->blockSignals(true);
    combo_item->clear();
    for(int i=0;i<320;i++)
    {
        if(type !=0)
        {
            if(Items.Type(i) == type)
            {
                combo_item->addItem(Items.Icon(i),Items.Name(i));
            }
        }
        else{combo_item->addItem(Items.Icon(i),Items.Name(i));}
    }
    current_item = itemEncode(id,itemQty(current_item));
    if(current_item != 0xFFFF){combo_item->setCurrentIndex(combo_item->findText(Items.Name(itemId(current_item))));}
    else{combo_item->setCurrentIndex(-1);}
    combo_item->blockSignals(false);
}
void ItemSelector::comboItem_changed(int index)
{
    int offset = type_offset(combo_type->currentIndex()+1);
    if(index+offset != itemId(current_item))
    {
        current_item=itemEncode(index+offset,itemQty(current_item));
        emit(item_changed(current_item));
    //    QMessageBox::information(this,"Id_Change",QString("Id:%1").arg(QString::number(itemId(current_item))));
    }
}
void ItemSelector::setCurrentItem(int id,int qty)
{

    if(id<0 || id >319 || qty <0 || qty >127){if(id!=0x1FF){return;}}
    this->blockSignals(true);
    if(id == 0x1FF)
    {
        btn_remove->blockSignals(true);
        btn_remove_clicked();
        btn_remove->blockSignals(false);
    }
    else
    {
        combo_type->setCurrentIndex(Items.Type(id)-1);
        combo_item->setCurrentIndex(id-type_offset(Items.Type(id)));
        sb_qty->setValue(qty);
        current_item=itemEncode(id,qty);
    }
    this->blockSignals(false);

}
void ItemSelector::setCurrentItem(quint16 ff7item)
{
    this->blockSignals(true);
    if(ff7item == 0xFFFF)
    {
        btn_remove->blockSignals(true);
        btn_remove_clicked();
        btn_remove->blockSignals(false);
    }
    combo_type->setCurrentIndex(Items.Type(itemId(ff7item))-1);
    combo_item->setCurrentIndex(itemId(ff7item) - type_offset(Items.Type(itemId(ff7item))));
    sb_qty->setValue(itemQty(ff7item));
    current_item=ff7item;
    this->blockSignals(false);
}
void ItemSelector::sb_qty_changed(int qty)
{
    if(qty != itemQty(current_item))
    {
        current_item = itemEncode(itemId(current_item),qty);
        emit(item_changed(current_item));
    //    QMessageBox::information(this,"Qty_Change",QString("Qty:%1").arg(QString::number(itemQty(current_item))));
    }
}
quint16 ItemSelector::itemDecode( quint16 itemraw )
{//see FF7Save::itemDecode for full comments
    quint16 item;
    int one = 1;
    if (*(char *)&one){item = itemraw;}
    else {item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);}
    return item;
}
quint16 ItemSelector::itemEncode( quint16 id, quint8 qty )
{//see FF7Save::itemEncode for full comments
    quint16 item,itemraw;
    int one = 1;
    if (*(char *)&one)
    {
        item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
        itemraw = item;
    }
    else
    {
        item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
        itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
    }
    return itemraw;
}

quint16 ItemSelector::itemId(quint16 item)
{
    quint16 new_item = itemDecode(item);
    quint16 id = (new_item & 0x1FF);
    return id;
}
quint8 ItemSelector::itemQty(quint16 item)
{
    quint16 new_item = itemDecode(item);
    quint8 qty;
    qty = (new_item & 0xFE00) >> 9;
    return qty;
}

int ItemSelector::type_offset(int type)
{
    int offset = 0;
    switch(type)
    {//set offset for type.
        case 0: offset =0; break;
        case 1: offset =0; break;
        case 2: offset =256; break;
        case 3: offset =288; break;
        case 4: offset =128; break;
        case 5: offset =160; break;
        case 6: offset =144; break;
        case 7: offset =176; break;
        case 8: offset =190; break;
        case 9: offset =201; break;
        case 10: offset=215; break;
        case 11: offset=229; break;
        case 12: offset=242; break;
        default: offset= -1; break;//ERROR INVALID TYPE.
    }
    return offset;
}
int ItemSelector::id(void){return (int)itemId(current_item);}
