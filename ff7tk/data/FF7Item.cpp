/****************************************************************************/
//    copyright 2012 - 2020  Chris Rizzitello <sithlord48@gmail.com>        //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "FF7Item.h"

#include <QIcon>
#include <QQmlEngine>

FF7Item *FF7Item::instance()
{
    static FF7Item m;
    return &m;
}

FF7Item::FF7Item(QObject *parent) :
    QObject(parent)
    , d(new FF7ItemPrivate)
{
}

FF7Item::~FF7Item()
{
    delete d;
}

QObject *FF7Item::qmlSingletonRegister(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine)
    engine->setObjectOwnership(instance(), QQmlEngine::CppOwnership);
    return instance();
}

const FF7Item::ITEM &FF7Item::item(int id)
{
    if (id >= 0 && id < size()) {
        return d->_items.at(id);
    }
    return d->_emptyitem;
}

QString FF7Item::name(int id)
{
    return tr(item(id).name.toLocal8Bit());
}

QString FF7Item::desc(int id)
{
    return tr(item(id).desc.toLocal8Bit());
}

QString FF7Item::iconResource(int id)
{
    QString temp = item(id).imageString;
    return temp.remove(":/");
}

int FF7Item::type(int id)
{
    return item(id).type;
}

QIcon FF7Item::icon(int id)
{
    return QIcon(QPixmap::fromImage(image(id)));
}

QString FF7Item::materiaSlotNoGrowthResource()
{
    return d->_resourceSlotNoGrowth;
}

QString FF7Item::materiaSlotResource()
{
    return d->_resourceSlot;
}

QString FF7Item::materiaLinkResource()
{
    return d->_resourceLink;
}

QImage FF7Item::image(int id)
{
    return QImage(item(id).imageString);
}

int FF7Item::materiaSlots(int id)
{
    return item(id).mslots;
}

int FF7Item::linkedSlots(int id)
{
    return item(id).linked;
}

int FF7Item::materiaGrowthRate(int id)
{
    return item(id).mgrowth;
}

int FF7Item::statHP(int id)
{
    return item(id).hp;
}

int FF7Item::statMP(int id)
{
    return item(id).mp;
}

int FF7Item::statSTR(int id)
{
    return item(id).str;
}

int FF7Item::statVIT(int id)
{
    return item(id).vit;
}

int FF7Item::statDEX(int id)
{
    return item(id).dex;
}

int FF7Item::statLCK(int id)
{
    return item(id).lck;
}

int FF7Item::statMAG(int id)
{
    return item(id).mag;
}

int FF7Item::statSPI(int id)
{
    return item(id).spi;
}

quint16 FF7Item::itemDecode(quint16 itemraw)
{
    //see FF7Save::itemDecode for full comments
    quint16 item;
#ifdef Q_BYTE_ORDER
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    item = itemraw;
#elif Q_BYTE_ORDER == Q_BIG_ENDIAN
    item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);
#else
    int one = 1;
    if (*(char *)&one) {
        item = itemraw;
    } else {
        item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);
    }
#endif
#else
    int one = 1;
    if (*(char *)&one) {
        item = itemraw;
    } else {
        item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);
    }
#endif
    return item;
}
quint16 FF7Item::itemEncode(quint16 id, quint8 qty)
{
    //see FF7Save::itemEncode for full comments
    quint16 item, itemraw;
#ifdef Q_BYTE_ORDER
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
    itemraw = item;
#elif Q_BYTE_ORDER == Q_BIG_ENDIAN
    item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
    itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
#else
    int one = 1;
    if (*(char *)&one) {
        item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
        itemraw = item;
    } else {
        item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
        itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
    }
#endif
#else
    int one = 1;
    if (*(char *)&one) {
        item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
        itemraw = item;
    } else {
        item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
        itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
    }
#endif
    return itemraw;
}

quint16 FF7Item::itemId(quint16 item)
{
    quint16 new_item = itemDecode(item);
    return quint16(new_item & 0x1FF);
}
quint8 FF7Item::itemQty(quint16 item)
{
    quint16 new_item = itemDecode(item);
    quint8 qty = (new_item & 0xFE00) >> 9;
    return qty;
}

QStringList FF7Item::elementalEffects(int id)
{

    QStringList elementList;
    if (id < 0 || id > 319) {
        return elementList;
    }
    for (int i = 0; i < 14; i++) {
        QString effect;
        int element = 0;
        switch (i) {
        case 0: element = elementRestoration(id); effect.append(tr("Restoration")); break;
        case 1: element = elementFire(id); effect.append(tr("Fire")); break;
        case 2: element = elementCold(id); effect.append(tr("Cold")); break;
        case 3: element = elementLightning(id); effect.append(tr("Lightning")); break;
        case 4: element = elementEarth(id); effect.append(tr("Earth")); break;
        case 5: element = elementWind(id); effect.append(tr("Wind")); break;
        case 6: element = elementWater(id); effect.append(tr("Water")); break;
        case 7: element = elementGravity(id); effect.append(tr("Gravity")); break;
        case 8: element = elementHoly(id); effect.append(tr("Holy")); break;
        case 9: element = elementPoison(id); effect.append(tr("Poison")); break;
        case 10: element = elementCut(id); effect.append(tr("Cut")); break;
        case 11: element = elementShoot(id); effect.append(tr("Shoot")); break;
        case 12: element = elementPunch(id); effect.append(tr("Punch")); break;
        case 13: element = elementHit(id); effect.append(tr("Hit")); break;
        }
        switch (element) {
        case FF7Item::Absorb: effect.prepend(tr("Absorb:")); break;
        case FF7Item::Nullify: effect.prepend(tr("Nullify:")); break;
        case FF7Item::Halve: effect.prepend(tr("Halve:")); break;
        case FF7Item::NoEffect: effect.clear(); break;
        case FF7Item::Damage: effect.prepend(tr("Attack:")); break;
        }
        if (!effect.isEmpty()) {
            elementList.append(effect);
        }
    }//end of for Loop
    return elementList;
}

int FF7Item::elementRestoration(int id)
{
    return item(id).e_restoration;
}

int FF7Item::elementFire(int id)
{
    return item(id).e_fire;
}

int FF7Item::elementCold(int id)
{
    return item(id).e_cold;
}

int FF7Item::elementLightning(int id)
{
    return item(id).e_lightning;
}

int FF7Item::elementEarth(int id)
{
    return item(id).e_earth;
}

int FF7Item::elementWind(int id)
{
    return item(id).e_wind;
}

int FF7Item::elementWater(int id)
{
    return item(id).e_water;
}

int FF7Item::elementGravity(int id)
{
    return item(id).e_gravity;
}

int FF7Item::elementHoly(int id)
{
    return item(id).e_holy;
}

int FF7Item::elementPoison(int id)
{
    return item(id).e_poison;
}

int FF7Item::elementCut(int id)
{
    return item(id).e_cut;
}

int FF7Item::elementShoot(int id)
{
    return item(id).e_shoot;
}

int FF7Item::elementPunch(int id)
{
    return item(id).e_punch;
}

int FF7Item::elementHit(int id)
{
    return item(id).e_hit;
}

QStringList FF7Item::statusEffects(int id)
{

    QStringList statusList;
    if (id < 0 || id > 319) {
        return statusList;
    }
    for (int i = 0; i < 24; i++) {
        QString effect;
        int status = 0;
        switch (i) {
        case 0: status = statusDeath(id); effect.append(tr("Death")); break;
        case 1: status = statusSlowNumb(id); effect.append(tr("Slow-Numb")); break;
        case 2: status = statusDeathSentence(id); effect.append(tr("D.Sentence")); break;
        case 3: status = statusParalysis(id); effect.append(tr("Paralysis")); break;
        case 4: status = statusPetrify(id); effect.append(tr("Petrify")); break;
        case 5: status = statusSilence(id); effect.append(tr("Silence")); break;
        case 6: status = statusSleep(id); effect.append(tr("Sleep")); break;
        case 7: status = statusConfusion(id); effect.append(tr("Confusion")); break;
        case 8: status = statusBerserk(id); effect.append(tr("Berserk")); break;
        case 9: status = statusFrog(id); effect.append(tr("Frog")); break;
        case 10: status = statusMini(id); effect.append(tr("Mini")); break;
        case 11: status = statusPoison(id); effect.append(tr("Poison")); break;
        case 12: status = statusFury(id); effect.append(tr("Fury")); break;
        case 13: status = statusSadness(id); effect.append(tr("Sadness")); break;
        case 14: status = statusDarkness(id); effect.append(tr("Darkness")); break;
        case 15: status = statusHaste(id); effect.append(tr("Haste")); break;
        case 16: status = statusSlow(id); effect.append(tr("Slow")); break;
        case 17: status = statusStop(id); effect.append(tr("Stop")); break;
        case 18: status = statusBarrier(id); effect.append(tr("Barrier")); break;
        case 19: status = statusMagicBarrier(id); effect.append(tr("M.Barrier")); break;
        case 20: status = statusReflect(id); effect.append(tr("Reflect")); break;
        case 21: status = statusShield(id); effect.append(tr("Shield")); break;
        case 22: status = statusRegen(id); effect.append(tr("Regen")); break;
        case 23: status = statusResist(id); effect.append(tr("Resist")); break;
        }
        switch (status) {
        case FF7Item::Protect: effect.prepend(tr("Protect:")); break;
        case FF7Item::Remove: effect.prepend(tr("Remove:")); break;
        case FF7Item::NoEffect: effect.clear(); break;
        case FF7Item::Infilict: effect.prepend(tr("Inflict:")); break;
        case FF7Item::SelfCast: effect.prepend(tr("OnBattle:")); break;
        }
        if (!effect.isEmpty()) {
            statusList.append(effect);
        }
    }//end of for Loop
    return statusList;
}

int FF7Item::statusDeath(int id)
{
    return item(id).s_death;
}

int FF7Item::statusSlowNumb(int id)
{
    return item(id).s_slow_numb;
}

int FF7Item::statusDeathSentence(int id)
{
    return item(id).s_d_sentence;
}

int FF7Item::statusParalysis(int id)
{
    return item(id).s_paralysis;
}

int FF7Item::statusPetrify(int id)
{
    return item(id).s_petrify;
}

int FF7Item::statusSilence(int id)
{
    return item(id).s_silence;
}

int FF7Item::statusSleep(int id)
{
    return item(id).s_sleep;
}

int FF7Item::statusConfusion(int id)
{
    return item(id).s_confusion;
}

int FF7Item::statusBerserk(int id)
{
    return item(id).s_berserk;
}

int FF7Item::statusFrog(int id)
{
    return item(id).s_frog;
}

int FF7Item::statusMini(int id)
{
    return item(id).s_mini;
}

int FF7Item::statusPoison(int id)
{
    return item(id).s_poison;
}

int FF7Item::statusFury(int id)
{
    return item(id).s_fury;
}

int FF7Item::statusSadness(int id)
{
    return item(id).s_sadness;
}

int FF7Item::statusDarkness(int id)
{
    return item(id).s_darkness;
}

int FF7Item::statusHaste(int id)
{
    return item(id).s_haste;
}

int FF7Item::statusSlow(int id)
{
    return item(id).s_slow;
}

int FF7Item::statusStop(int id)
{
    return item(id).s_stop;
}

int FF7Item::statusBarrier(int id)
{
    return item(id).s_barrier;
}

int FF7Item::statusMagicBarrier(int id)
{
    return item(id).s_m_barrier;
}

int FF7Item::statusReflect(int id)
{
    return item(id).s_reflect;
}

int FF7Item::statusShield(int id)
{
    return item(id).s_sheild;
}

int FF7Item::statusRegen(int id)
{
    return item(id).s_regen;
}

int FF7Item::statusResist(int id)
{
    return item(id).s_resist;
}

int FF7Item::size() const
{
    return d->_items.size();
}

QImage FF7Item::imageMateriaSlotNoGrowth()
{
    return QImage(materiaSlotNoGrowthResource());
}

QImage FF7Item::imageMateriaSlot()
{
    return QImage(materiaSlotResource());
}

QImage FF7Item::imageMateriaLink()
{
    return QImage(materiaLinkResource());
}

const QString &FF7Item::styleMateriaSlotNoGrowth()
{
    return d->_styleSlotNoGrowth;
}

const QString &FF7Item::styleMateriaSlot()
{
    return d->_styleSlot;
}

const QString &FF7Item::styleMateriaLink()
{
    return d->_styleLink;
}
