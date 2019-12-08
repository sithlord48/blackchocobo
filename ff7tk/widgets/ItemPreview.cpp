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
#include "ItemPreview.h"
#include <QEvent>
#include <QHBoxLayout>
#include <QtEndian>

bool ItemPreview::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj != this->parent() && (obj != this)) {
        close();
        return true;
    }

    if (ev->type() == QEvent::MouseButtonPress || ev->type() == QEvent::Leave) {
        close();
        return true;
    }

    return event(ev);

}
ItemPreview::ItemPreview(QFlags<Qt::WindowType> WindowFlags, float Scale, QWidget *parent)
    : QWidget(parent)
    , lbl_name(new QLabel(this))
    , lbl_desc(new QLabel(this))
    , lbl_icon(new QLabel(this))
    , scale(Scale)
    , slotSize(fontMetrics().height(), fontMetrics().height())
    , linkSize(fontMetrics().height() /2, fontMetrics().height())
{
    for(int i= 0; i < 8; i++) {
        slotLabels.append(new QLabel(this));
        slotLabels.at(i)->setFixedSize(slotSize);
        slotLabels.at(i)->setHidden(true);
    }

    for(int i =0; i< 4; i++) {
        slotLinks.append(new QLabel(this));
        slotLinks.at(i)->setFixedSize(linkSize);
    }

    setWindowFlags(WindowFlags);
    Qt::WindowFlags WidgetType = (this->windowFlags() & Qt::WindowType_Mask);
    if (WidgetType == Qt::Popup || WidgetType == Qt::ToolTip)
        installEventFilter(this);

    _id = FF7Item::EmptyItem;
    lbl_icon->setFixedSize(slotSize);

    auto materia_slots = new QHBoxLayout();
    materia_slots->setContentsMargins(0, 0, 0, 0);
    materia_slots->addLayout(makeMateriaPair(slotLabels.at(0), slotLabels.at(1), slotLinks.at(0)));
    materia_slots->addLayout(makeMateriaPair(slotLabels.at(2), slotLabels.at(3), slotLinks.at(1)));
    materia_slots->addLayout(makeMateriaPair(slotLabels.at(4), slotLabels.at(5), slotLinks.at(2)));
    materia_slots->addLayout(makeMateriaPair(slotLabels.at(6), slotLabels.at(7), slotLinks.at(3)));
    materia_slots->addSpacerItem(new QSpacerItem(-1, -1, QSizePolicy::Expanding, QSizePolicy::Minimum));
    materia_slots->setSpacing(12);

    materia_slot_box = new QGroupBox(this);
    materia_slot_box->setMinimumWidth(int(320 * scale));
    materia_slot_box->setLayout(materia_slots);
    materia_slot_box->setHidden(true);

    elemental_effects = new QListWidget();
    elemental_effects->setMinimumWidth(fontMetrics().horizontalAdvance(tr("Elemental Effects")));
    elemental_effects->setResizeMode(QListView::Adjust);
    QHBoxLayout *elemental = new QHBoxLayout();
    elemental->setContentsMargins(0, 0, 0, 0);
    elemental->addWidget(elemental_effects);

    elemental_box = new QGroupBox();
    elemental_box->setContentsMargins(3, 3, 3, 3);
    elemental_box->setLayout(elemental);
    elemental_box->setTitle(tr("Elemental Effects"));
    elemental_box->setHidden(true);

    status_effects = new QListWidget();
    status_effects->setMinimumWidth(fontMetrics().horizontalAdvance(tr("Status Effects")));
    status_effects->setResizeMode(QListView::Adjust);
    QHBoxLayout *status = new QHBoxLayout();
    status->setContentsMargins(0, 0, 0, 0);
    status->addWidget(status_effects);

    status_box = new QGroupBox();
    status_box->setContentsMargins(3, 3, 3, 3);
    status_box->setLayout(status);
    status_box->setTitle(tr("Status Effects"));
    status_box->setHidden(true);

    auto effects_layout = new QHBoxLayout();
    effects_layout->setContentsMargins(0, 0, 0, 0);
    effects_layout->addWidget(elemental_box);
    effects_layout->addWidget(status_box);
    effects_layout->addSpacerItem(new QSpacerItem(-1, -1, QSizePolicy::Expanding, QSizePolicy::Minimum));
    effects_layout->setSpacing(0);

    auto top = new QHBoxLayout();
    top->addWidget(lbl_icon);
    top->addWidget(lbl_name);

    auto main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(3, 3, 3, 3);
    main_layout->addLayout(top);
    main_layout->addWidget(lbl_desc);
    main_layout->addWidget(materia_slot_box);
    main_layout->addLayout(effects_layout);
}

void ItemPreview::setName(QString text)
{
    lbl_name->setText(text);
    lbl_name->adjustSize();
}

void ItemPreview::setDesc(QString text)
{
    lbl_desc->setText(text);
    lbl_desc->adjustSize();
}

void ItemPreview::setIcon(QPixmap picture)
{
    lbl_icon->setPixmap(picture.scaled(lbl_icon->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    lbl_icon->adjustSize();
}

void ItemPreview::setItem(quint16 itemraw)
{
    quint16 item;
    if(QSysInfo::ByteOrder == QSysInfo::LittleEndian)
        item = itemraw;
    else
        item = qToLittleEndian(itemraw);

    int id = (item & 0x1FF);
    setItem(id);
}

void ItemPreview::setItem(int id)
{
    for(auto slot : qAsConst(slotLabels))
        slot->setHidden(true);

    for(auto link : qAsConst(slotLinks))
        link->clear();

    materia_slot_box->setHidden(true);
    lbl_desc->setHidden(true);
    lbl_name->setHidden(true);
    lbl_icon->setHidden(true);
    status_box->setHidden(true);
    elemental_box->setHidden(true);

    if (id < 0 || id > 319)
        _id = FF7Item::EmptyItem;/*InValid Number..Do Nothing*/
    else {
        _id = id;
        if (!data.name(id).isEmpty()) {
            lbl_name->setHidden(false);
            setName(data.name(id));
        }

        if (!data.desc(id).isEmpty()) {
            setDesc(data.desc(id));
            lbl_desc->setHidden(false);
        }

        if (!data.image(id).isNull()) {
            lbl_icon->setHidden(false);
            setIcon(QPixmap::fromImage(data.image(id)));
        }

        status_info(id);
        elemental_info(id);

        if (data.type(id) > FF7Item::Item && data.type(id) != FF7Item::Accessory) {
            for (auto slot : qAsConst(slotLabels))
               slot->setPixmap(QPixmap::fromImage(data.materiaGrowthRate(id) == 0 ? data.imageMateriaSlotNoGrowth() : data.imageMateriaSlot()).scaled(slot->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

            QString ap_rate = tr("APx%1").arg(data.materiaGrowthRate(id));
            materia_slot_box->setTitle(ap_rate);
            materia_slot_box->setHidden(false);

            for(int i = 0; i < data.materiaSlots(id); i++)
                slotLabels.at(i)->setHidden(false);

            for(int i = 0; i < data.linkedSlots(id); i++)
                slotLinks.at(i)->setPixmap(QPixmap::fromImage(data.imageMateriaLink().scaled(slotLinks.at(i)->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        }
    }
    adjustSize();
}
void ItemPreview::elemental_info(int id)
{
    elemental_effects->clear();
    bool show = false;
    if (id < 0 || id > 319) {/*invalid number*/}
    else {
        for (int i = 0; i < 14; i++) {
            QString effect;
            int element = 0;
            switch (i) {
            case 0: element = data.elementRestoration(id); effect.append(tr("Restoration")); break;
            case 1: element = data.elementFire(id); effect.append(tr("Fire")); break;
            case 2: element = data.elementCold(id); effect.append(tr("Cold")); break;
            case 3: element = data.elementLightning(id); effect.append(tr("Lightning")); break;
            case 4: element = data.elementEarth(id); effect.append(tr("Earth")); break;
            case 5: element = data.elementWind(id); effect.append(tr("Wind")); break;
            case 6: element = data.elementWater(id); effect.append(tr("Water")); break;
            case 7: element = data.elementGravity(id); effect.append(tr("Gravity")); break;
            case 8: element = data.elementHoly(id); effect.append(tr("Holy")); break;
            case 9: element = data.elementPoison(id); effect.append(tr("Poison")); break;
            case 10: element = data.elementCut(id); effect.append(tr("Cut")); break;
            case 11: element = data.elementShoot(id); effect.append(tr("Shoot")); break;
            case 12: element = data.elementPunch(id); effect.append(tr("Punch")); break;
            case 13: element = data.elementHit(id); effect.append(tr("Hit")); break;
            }
            switch (element) {
            case FF7Item::Absorb: effect.prepend(tr("Absorb:")); break;
            case FF7Item::Nullify: effect.prepend(tr("Nullify:")); break;
            case FF7Item::Halve: effect.prepend(tr("Halve:")); break;
            case FF7Item::NoEffect: effect.clear(); break;
            case FF7Item::Damage: effect.prepend(tr("Attack:")); break;
            }
            if (!effect.isNull()) {
                elemental_effects->addItem(effect);
                show = true;
            }
        }//end of for Loop
        int topMargin = elemental_box->contentsMargins().top() + elemental_effects->contentsMargins().top();
        int bottomMargin = elemental_box->contentsMargins().bottom() + elemental_effects->contentsMargins().bottom();

        Qt::WindowFlags WidgetType = (this->windowFlags() & Qt::WindowType_Mask);
        if (WidgetType != Qt::Popup && WidgetType != Qt::ToolTip) {
            if (elemental_effects->count() < 6)
                elemental_box->setFixedHeight(elemental_effects->sizeHintForRow(0) * elemental_effects->count() + topMargin + bottomMargin);
            else
                elemental_box->setFixedHeight((elemental_effects->sizeHintForRow(0)) * 5 + topMargin + bottomMargin);
        } else
            elemental_box->setFixedHeight(elemental_effects->sizeHintForRow(0) * elemental_effects->count() + topMargin + bottomMargin);
    }//end of else
    elemental_box->setVisible(show);
    elemental_box->adjustSize();
}//end of function

void ItemPreview::status_info(int id)
{
    int y = status_effects->contentsMargins().top() + status_effects->contentsMargins().bottom();
    status_effects->clear();
    bool show = false;
    if (id < 0 || id > 319) {/*invalid number*/}
    else {
        for (int i = 0; i < 24; i++) {
            QString effect;
            int status = 0;
            switch (i) {
            case 0: status = data.statusDeath(id); effect.append(tr("Death")); break;
            case 1: status = data.statusSlowNumb(id); effect.append(tr("Slow-Numb")); break;
            case 2: status = data.statusDeathSentence(id); effect.append(tr("D.Sentence")); break;
            case 3: status = data.statusParalysis(id); effect.append(tr("Paralysis")); break;
            case 4: status = data.statusPetrify(id); effect.append(tr("Petrify")); break;
            case 5: status = data.statusSilence(id); effect.append(tr("Silence")); break;
            case 6: status = data.statusSleep(id); effect.append(tr("Sleep")); break;
            case 7: status = data.statusConfusion(id); effect.append(tr("Confusion")); break;
            case 8: status = data.statusBerserk(id); effect.append(tr("Berserk")); break;
            case 9: status = data.statusFrog(id); effect.append(tr("Frog")); break;
            case 10: status = data.statusMini(id); effect.append(tr("Mini")); break;
            case 11: status = data.statusPoison(id); effect.append(tr("Poison")); break;
            case 12: status = data.statusFury(id); effect.append(tr("Fury")); break;
            case 13: status = data.statusSadness(id); effect.append(tr("Sadness")); break;
            case 14: status = data.statusDarkness(id); effect.append(tr("Darkness")); break;
            case 15: status = data.statusHaste(id); effect.append(tr("Haste")); break;
            case 16: status = data.statusSlow(id); effect.append(tr("Slow")); break;
            case 17: status = data.statusStop(id); effect.append(tr("Stop")); break;
            case 18: status = data.statusBarrier(id); effect.append(tr("Barrier")); break;
            case 19: status = data.statusMagicBarrier(id); effect.append(tr("M.Barrier")); break;
            case 20: status = data.statusReflect(id); effect.append(tr("Reflect")); break;
            case 21: status = data.statusShield(id); effect.append(tr("Shield")); break;
            case 22: status = data.statusRegen(id); effect.append(tr("Regen")); break;
            case 23: status = data.statusResist(id); effect.append(tr("Resist")); break;
            }

            switch (status) {
            case FF7Item::Protect: effect.prepend(tr("Protect:")); break;
            case FF7Item::Remove: effect.prepend(tr("Remove:")); break;
            case FF7Item::NoEffect: effect.clear(); break;
            case FF7Item::Infilict: effect.prepend(tr("Inflict:")); break;
            case FF7Item::SelfCast: effect.prepend(tr("OnBattle:")); break;
            }

            if (!effect.isNull()) {
                status_effects->addItem(effect);
                show = true;
                y += status_effects->sizeHintForRow(0);
            }
        }//end of for Loop
        Qt::WindowFlags WidgetType = (this->windowFlags() & Qt::WindowType_Mask);
        if (WidgetType != Qt::Popup && WidgetType != Qt::ToolTip) {
            //make the combo box smaller if not a popup or tooltip
            if (status_effects->count() < 6)
                status_box->setFixedHeight(y + status_box->contentsMargins().top() + status_box->contentsMargins().bottom());
            else
                status_box->setFixedHeight(status_effects->sizeHintForRow(0) * 5 + status_box->contentsMargins().top() + status_box->contentsMargins().bottom());
        } else
            status_box->setFixedHeight(y + status_box->contentsMargins().top() + status_box->contentsMargins().bottom());
    }//end of else
    status_box->setVisible(show);
    status_box->adjustSize();
}//end of function

int ItemPreview::id(void)
{
    return _id;
}

QHBoxLayout * ItemPreview::makeMateriaPair(QLabel *slot1, QLabel *slot2, QLabel *link)
{
    auto finalLayout = new QHBoxLayout();
    finalLayout->setContentsMargins(0, 0, 0, 0);
    finalLayout->addWidget(slot1);
    finalLayout->addWidget(link);
    finalLayout->addWidget(slot2);
    finalLayout->setSpacing(0);
    return finalLayout;
}
