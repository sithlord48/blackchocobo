/****************************************************************************/
//    copyright 2012 -2019  Chris Rizzitello <sithlord48@gmail.com>         //
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
#include "ItemSelector.h"
//Besure to set FF7Item Path!
#include "../data/FF7Item.h"
#include <QHBoxLayout>

ItemSelector::ItemSelector(qreal Scale, QWidget *parent): QWidget(parent)
{
    scale = Scale;
    init_display();
    init_connections();
}
void ItemSelector::init_display()
{
    QSize iconSize = QSize(fontMetrics().height(), fontMetrics().height());
    combo_type = new QComboBox;
    combo_type->setIconSize(iconSize);

    combo_item = new QComboBox;
    combo_item->setIconSize(iconSize);

    sb_qty = new QSpinBox;
    sb_qty->setAlignment(Qt::AlignLeft);
    sb_qty->setMinimum(1);
    sb_qty->setMaximum(127);
    sb_qty->setToolTip("");
    sb_qty->setWrapping(true);

    btn_remove = new QPushButton();
    btn_remove->setIconSize(iconSize);
    btn_remove->setIcon(QIcon::fromTheme(QStringLiteral("edit-clear"), QPixmap(":/common/edit-clear")));
    btn_remove->setToolTip(tr("Empty Item"));
    btn_remove->setShortcut(QKeySequence::Delete);

    init_data(); //before setting layout set dat
    btn_remove->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    combo_type->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    combo_item->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    combo_type->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(combo_type);
    layout->addWidget(combo_item);
    layout->addWidget(sb_qty);
    layout->addWidget(btn_remove);
    setLayout(layout);
    adjustSize();
}
void ItemSelector::setMaximumQty(int maxQty)
{
    sb_qty->setMaximum(maxQty);
}

void ItemSelector::init_connections()
{
    connect(combo_type, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ItemSelector::setFilter);
    connect(combo_item, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ItemSelector::comboItem_changed);
    connect(sb_qty, QOverload<int>::of(&QSpinBox::valueChanged), this, &ItemSelector::sb_qty_changed);
    connect(btn_remove, &QPushButton::clicked, this, &ItemSelector::btn_remove_clicked);
}

void ItemSelector::init_data()
{

    combo_type->addItem(FF7Item::instance()->icon(FF7Item::Potion), QString());
    combo_type->addItem(FF7Item::instance()->icon(FF7Item::BronzeBangle), QString());
    combo_type->addItem(FF7Item::instance()->icon(FF7Item::Ribbon), QString());
    combo_type->addItem(FF7Item::instance()->icon(FF7Item::BusterSword), QString());
    combo_type->addItem(FF7Item::instance()->icon(FF7Item::GatlingGun), QString());
    combo_type->addItem(FF7Item::instance()->icon(FF7Item::GodsHand), QString());
    combo_type->addItem(FF7Item::instance()->icon(FF7Item::AdamanClip), QString());
    combo_type->addItem(FF7Item::instance()->icon(FF7Item::StrikingStaff), QString());
    combo_type->addItem(FF7Item::instance()->icon(FF7Item::Mop), QString());
    combo_type->addItem(FF7Item::instance()->icon(FF7Item::FourPointShuriken), QString());
    combo_type->addItem(FF7Item::instance()->icon(FF7Item::CrystalMphone), QString());
    combo_type->addItem(FF7Item::instance()->icon(FF7Item::SupershotST), QString());
    sb_qty->setEnabled(false);
    //Fill Combo_Item (all items type is 0 or no filter defalut)
    for (int i = 0; i < 320; i++) {
        combo_item->addItem(FF7Item::instance()->icon(i), FF7Item::instance()->name(i));
    }
    combo_type->setCurrentIndex(-1);
    combo_item->setCurrentIndex(-1);
    current_item = FF7Item::EmptyItemData;
}

void ItemSelector::btn_remove_clicked()
{
	combo_item->blockSignals(true);
	combo_type->setCurrentIndex(-1);
	combo_item->setCurrentIndex(-1);
	combo_item->blockSignals(false);
	sb_qty->setEnabled(false);
	current_item = FF7Item::EmptyItemData;
    emit itemChanged(current_item);
}

void ItemSelector::setFilter(int type)
{
    type++;//for hiding no filter.
    int id = FF7Item::instance()->itemId(current_item);
    combo_item->blockSignals(true);
    combo_item->clear();
    for (int i = 0; i < 320; i++) {
        if (type != FF7Item::Unknown) {
            if (FF7Item::instance()->type(i) == type) {
                combo_item->addItem(FF7Item::instance()->icon(i), FF7Item::instance()->name(i));
            }
        } else {
            combo_item->addItem(FF7Item::instance()->icon(i), FF7Item::instance()->name(i));
        }
    }

    current_item = FF7Item::instance()->itemEncode(quint16(id), FF7Item::instance()->itemQty(current_item));
    if (current_item != FF7Item::EmptyItemData) {
        combo_item->setCurrentIndex(combo_item->findText(FF7Item::instance()->name(FF7Item::instance()->itemId(current_item))));
    } else {
        combo_item->setCurrentIndex(-1);
    }
    this->layout()->update();
    combo_item->blockSignals(false);
}
void ItemSelector::comboItem_changed(int index)
{
    if (sb_qty->maximum() == 127) {
        if (combo_item->currentText() == FF7Item::instance()->name(FF7Item::Masamune)) {
            sb_qty->setMaximum(126);
        } else {
            sb_qty->setMaximum(127);
        }
    }

	int offset = type_offset(combo_type->currentIndex()+1);
    if (index+offset != FF7Item::instance()->itemId(current_item)) {
        if (current_item == FF7Item::EmptyItemData) {
            current_item = FF7Item::instance()->itemEncode(quint16(index+offset), quint8(sb_qty->value()));
        } else {
            current_item = FF7Item::instance()->itemEncode(quint16(index+offset), quint8(FF7Item::instance()->itemQty(current_item)));
        }
		if (current_item == FF7Item::EmptyItemData) {
            sb_qty->setEnabled(false);
        } else {
            sb_qty->setEnabled(true);
            
        }
        emit(itemChanged(current_item));
	}
}

void ItemSelector::setCurrentItem(int id,int qty)
{

    if (id < 0 || id > 319 || qty < 0 || qty > 127) {
        if (id != FF7Item::EmptyItem) {
            return;
        }
    }
    this->blockSignals(true);
    if (id == FF7Item::Masamune && qty == 127) {
        qty = 126;
    }
    if (id == FF7Item::EmptyItem) {
        btn_remove->blockSignals(true);
        btn_remove_clicked();
        btn_remove->blockSignals(false);
    } else {
        combo_type->setCurrentIndex(FF7Item::instance()->type(id) - 1);
        combo_item->setCurrentIndex(id - type_offset(FF7Item::instance()->type(id)));
        sb_qty->setValue(qty);
        current_item = FF7Item::instance()->itemEncode(quint16(id), quint8(qty));
    }
    this->blockSignals(false);

}
void ItemSelector::setCurrentItem(quint16 ff7item)
{
    this->blockSignals(true);
    if ((FF7Item::instance()->itemId(ff7item) == FF7Item::Masamune) && (FF7Item::instance()->itemQty(ff7item) == 127)) {
        ff7item = FF7Item::instance()->itemEncode(FF7Item::Masamune, 126);
    }

    if (ff7item == FF7Item::EmptyItemData) {
        btn_remove->blockSignals(true);
        btn_remove_clicked();
        btn_remove->blockSignals(false);
    } else {
        combo_type->setCurrentIndex(FF7Item::instance()->type(FF7Item::instance()->itemId(ff7item)) - 1);
        combo_item->setCurrentIndex(FF7Item::instance()->itemId(ff7item) - type_offset(FF7Item::instance()->type(FF7Item::instance()->itemId(ff7item))));
        sb_qty->setValue(FF7Item::instance()->itemQty(ff7item));
        current_item = ff7item;
    }
    this->blockSignals(false);
}
void ItemSelector::sb_qty_changed(int qty)
{
    if (qty != FF7Item::instance()->itemQty(current_item)) {
        current_item = FF7Item::instance()->itemEncode(FF7Item::instance()->itemId(current_item), quint8(qty));
        emit(itemChanged(current_item));
    }
}

int ItemSelector::type_offset(int type)
{
    int offset = 0;
    switch (type) {
    //set offset for type.
    case FF7Item::Unknown: offset = 0; break;
    case FF7Item::Item: offset = 0; break;
    case FF7Item::Armor: offset = 256; break;
    case FF7Item::Accessory: offset = 288; break;
    case FF7Item::WeaponCloud: offset = 128; break;
    case FF7Item::WeaponBarret: offset = 160; break;
    case FF7Item::WeaponTifa: offset = 144; break;
    case FF7Item::WeaponRed: offset = 176; break;
    case FF7Item::WeaponAerith: offset = 190; break;
    case FF7Item::WeaponCid: offset = 201; break;
    case FF7Item::WeaponYuffie: offset = 215; break;
    case FF7Item::WeaponCait: offset = 229; break;
    case FF7Item::WeaponVincent: offset = 242; break;
    default: offset = -1; break; //ERROR INVALID TYPE.
    }
    return offset;
}

int ItemSelector::id(void)
{
    return int(FF7Item::instance()->itemId(current_item));
}
int ItemSelector::combo_item_width()
{
    return combo_item->sizeHint().width();
}
int ItemSelector::combo_type_width()
{
    return combo_type->sizeHint().width();
}
int ItemSelector::qty_width()
{
    return sb_qty->sizeHint().width() + btn_remove->sizeHint().width();
}

void ItemSelector::setFixedHeight(int h)
{
    sb_qty->setFixedHeight(h);
    combo_type->setFixedHeight(h);
    combo_item->setFixedHeight(h);
    btn_remove->setFixedHeight(h);
}
void ItemSelector::setEditableItemCombo(bool editable)
{
    combo_item->setEditable(editable);
    combo_item->setInsertPolicy(QComboBox::NoInsert);
}
