#include "ItemSelector.h"
// include icon data
#include "../static_data/icons/Common_Icons/quit.xpm"

ItemSelector::ItemSelector(QWidget *parent): QWidget(parent)
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
    sb_qty->setMinimum(1);
    sb_qty->setWrapping(true);
    sb_qty->setToolTip("");
    btn_remove = new QPushButton;
    btn_remove->setIcon(QIcon(QPixmap(quit_xpm)));
    btn_remove->setToolTip(tr("Empty Item"));
    btn_remove->setFixedSize(22,22);
    init_data(); //before setting layout set dat
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(combo_type);
    layout->addWidget(combo_item);
    layout->addWidget(sb_qty);
    layout->addWidget(btn_remove);
    this->setLayout(layout);
    this->layout()->update();
    this->adjustSize();
}
void ItemSelector::init_connections()
{
    if(QT_VERSION<0x050000)
    {//QT4 Style Connections
        connect(combo_type,SIGNAL(currentIndexChanged(int)),this,SLOT(setFilter(int)));
        connect(combo_item,SIGNAL(currentIndexChanged(int)),this,SLOT(comboItem_changed(int)));
        connect(sb_qty,SIGNAL(valueChanged(int)),this,SLOT(sb_qty_changed(int)));
        connect(btn_remove,SIGNAL(clicked()),this,SLOT(btn_remove_clicked()));
    }
    else
    {//QT5 Style Connections
        /*
        connect(combo_type::currentIndexChanged(int),this::setFilter(int));
        connect(combo_item::currentIndexChanged(int),this::comboItem_changed(int));
        connect(sb_qty::valueChanged(int),this::sb_qty_changed(int));
        connect(btn_remove::clicked(),this::btn_remove_clicked());
        */
    }
}
void ItemSelector::init_data()
{
    combo_type->addItem(Items.Icon(FF7Item::Potion),tr(""));
    combo_type->addItem(Items.Icon(FF7Item::BronzeBangle),tr(""));
    combo_type->addItem(Items.Icon(FF7Item::Ribbon),tr(""));
    combo_type->addItem(Items.Icon(FF7Item::BusterSword),tr(""));
    combo_type->addItem(Items.Icon(FF7Item::GatlingGun),tr(""));
    combo_type->addItem(Items.Icon(FF7Item::GodsHand),tr(""));
    combo_type->addItem(Items.Icon(FF7Item::AdamanClip),tr(""));
    combo_type->addItem(Items.Icon(FF7Item::StrikingStaff),tr(""));
    combo_type->addItem(Items.Icon(FF7Item::Mop),tr(""));
    combo_type->addItem(Items.Icon(FF7Item::FourPointShuriken),tr(""));
    combo_type->addItem(Items.Icon(FF7Item::CrystalMphone),tr(""));
    combo_type->addItem(Items.Icon(FF7Item::SupershotST),tr(""));
    sb_qty->setEnabled(false);
    //Fill Combo_Item (all items type is 0 or no filter defalut)
    for(int i=0;i<320;i++){combo_item->addItem(Items.Icon(i),Items.Name(i));}
    combo_type->setCurrentIndex(-1);
    combo_item->setCurrentIndex(-1);
    current_item=FF7Item::EmptyItemData;
}
void ItemSelector::btn_remove_clicked()
{
    combo_item->blockSignals(true);
    combo_type->setCurrentIndex(-1);
    combo_item->setCurrentIndex(-1);
    combo_item->blockSignals(false);
    sb_qty->setEnabled(false);
    current_item =FF7Item::EmptyItemData;
    emit item_changed(current_item);
}
void ItemSelector::setFilter(int type)
{
    type++;//for hiding no filter.
    int id = Items.itemId(current_item);
    combo_item->blockSignals(true);
    combo_item->clear();
    for(int i=0;i<320;i++)
    {
        if(type !=FF7Item::Unknown){if(Items.Type(i) == type){combo_item->addItem(Items.Icon(i),Items.Name(i));}}
        else{combo_item->addItem(Items.Icon(i),Items.Name(i));}
    }

    current_item = Items.itemEncode(id,Items.itemQty(current_item));
    if(current_item !=FF7Item::EmptyItemData){combo_item->setCurrentIndex(combo_item->findText(Items.Name(Items.itemId(current_item))));}
    else{combo_item->setCurrentIndex(-1);}
    this->layout()->update();
    combo_item->blockSignals(false);
}
void ItemSelector::comboItem_changed(int index)
{
    if(combo_item->currentText()==Items.Name(FF7Item::Masamune)){sb_qty->setMaximum(126);}
    else{sb_qty->setMaximum(127);}
    int offset = type_offset(combo_type->currentIndex()+1);
    if(index+offset != Items.itemId(current_item))
    {
        if(current_item==FF7Item::EmptyItemData){current_item=Items.itemEncode(index+offset,sb_qty->value());}
        else{current_item=Items.itemEncode(index+offset,Items.itemQty(current_item));}
        if(current_item ==FF7Item::EmptyItemData){sb_qty->setEnabled(false);}
        else{sb_qty->setEnabled(true);}
        emit(item_changed(current_item));
    }
}
void ItemSelector::setCurrentItem(int id,int qty)
{

    if(id<0 || id >319 || qty <0 || qty >127){if(id!=FF7Item::EmptyItem){return;}}
    this->blockSignals(true);
    if(id == FF7Item::Masamune && qty == 127){qty =126;}
    if(id == FF7Item::EmptyItem)
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
        current_item=Items.itemEncode(id,qty);
    }
    this->blockSignals(false);

}
void ItemSelector::setCurrentItem(quint16 ff7item)
{
    this->blockSignals(true);
    if((Items.itemId(ff7item) == FF7Item::Masamune) && (Items.itemQty(ff7item) ==127)){ ff7item = Items.itemEncode(FF7Item::Masamune,126);}

    if(ff7item ==FF7Item::EmptyItemData)
    {
        btn_remove->blockSignals(true);
        btn_remove_clicked();
        btn_remove->blockSignals(false);
    }
    else
    {
        combo_type->setCurrentIndex(Items.Type(Items.itemId(ff7item))-1);
        combo_item->setCurrentIndex(Items.itemId(ff7item) - type_offset(Items.Type(Items.itemId(ff7item))));
        sb_qty->setValue(Items.itemQty(ff7item));
        current_item=ff7item;
    }
    this->blockSignals(false);
}
void ItemSelector::sb_qty_changed(int qty)
{
    if(qty != Items.itemQty(current_item))
    {
        current_item = Items.itemEncode(Items.itemId(current_item),qty);
        emit(item_changed(current_item));
    }
}


int ItemSelector::type_offset(int type)
{
    int offset = 0;
    switch(type)
    {//set offset for type.
        case FF7Item::Unknown: offset =0; break;
        case FF7Item::Item: offset =0; break;
        case FF7Item::Armor: offset =256; break;
        case FF7Item::Accessory: offset =288; break;
        case FF7Item::WeaponCloud: offset =128; break;
        case FF7Item::WeaponBarret: offset =160; break;
        case FF7Item::WeaponTifa: offset =144; break;
        case FF7Item::WeaponRed: offset =176; break;
        case FF7Item::WeaponAerith: offset =190; break;
        case FF7Item::WeaponCid: offset =201; break;
        case FF7Item::WeaponYuffie: offset=215; break;
        case FF7Item::WeaponCait: offset=229; break;
        case FF7Item::WeaponVincent: offset=242; break;
        default: offset= -1; break;//ERROR INVALID TYPE.
    }
    return offset;
}
int ItemSelector::id(void){return (int)Items.itemId(current_item);}
int ItemSelector::combo_item_width(){return combo_item->width();}
