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
#include "FF7Item.h"
#include <QCoreApplication>

QString FF7Item::name(int i){return qApp->translate("Items",Items[i].name.toLocal8Bit());}
QString FF7Item::desc(int i){return qApp->translate("Item_desc",Items[i].desc.toLocal8Bit());}
qint8  FF7Item::type(int i){return Items[i].type;}
QImage FF7Item::image(int i){return QImage(Items[i].imageString);}
QIcon FF7Item::icon(int i){return QIcon(QPixmap::fromImage(image(i)));}
qint8 FF7Item::materiaSlots(int i){return Items[i].mslots;}
qint8 FF7Item::linkedSlots(int i){return Items[i].linked;}
qint8 FF7Item::materiaGrowthRate(int i){return Items[i].mgrowth;}
qint8 FF7Item::statHP(int i){return Items[i].hp;}
qint8 FF7Item::statMP(int i){return Items[i].mp;}
qint8 FF7Item::statSTR(int i){return Items[i].str;}
qint8 FF7Item::statVIT(int i){return Items[i].vit;}
qint8 FF7Item::statDEX(int i){return Items[i].dex;}
qint8 FF7Item::statLCK(int i){return Items[i].lck;}
qint8 FF7Item::statMAG(int i){return Items[i].mag;}
qint8 FF7Item::statSPI(int i){return Items[i].spi;}
QImage FF7Item::imageMateriaSlotNoGrowth(void){return QImage(QString(":/items/m_no_grow_slot"));}
QImage FF7Item::imageMateriaSlot(void){return QImage(QString(":/items/m_grow_slot"));}
QImage FF7Item::imageMateriaLink(void){return QImage(QString(":/items/mlink"));}
qint8 FF7Item::elementRestoration(int i){return Items[i].e_restoration;}
qint8 FF7Item::elementFire(int i){return Items[i].e_fire;}
qint8 FF7Item::elementCold(int i){return Items[i].e_cold;}
qint8 FF7Item::elementLightning(int i){return Items[i].e_lightning;}
qint8 FF7Item::elementEarth(int i){return Items[i].e_earth;}
qint8 FF7Item::elementWind(int i){return Items[i].e_wind;}
qint8 FF7Item::elementWater(int i){return Items[i].e_water;}
qint8 FF7Item::elementGravity(int i){return Items[i].e_gravity;}
qint8 FF7Item::elementHoly(int i){return Items[i].e_holy;}
qint8 FF7Item::elementPoison(int i){return Items[i].e_poison;}
qint8 FF7Item::elementCut(int i){return Items[i].e_cut;}
qint8 FF7Item::elementShoot(int i){return Items[i].e_shoot;}
qint8 FF7Item::elementPunch(int i){return Items[i].e_punch;}
qint8 FF7Item::elementHit(int i){return Items[i].e_hit;}
//Status Functions
qint8 FF7Item::statusDeath(int i){return Items[i].s_death;}
qint8 FF7Item::statusSlowNumb(int i){return Items[i].s_slow_numb;}
qint8 FF7Item::statusDeathSentence(int i){return Items[i].s_d_sentence;}
qint8 FF7Item::statusParalysis(int i){return Items[i].s_paralysis;}
qint8 FF7Item::statusPetrify(int i){return Items[i].s_petrify;}
qint8 FF7Item::statusSilence(int i){return Items[i].s_silence;}
qint8 FF7Item::statusSleep(int i){return Items[i].s_sleep;}
qint8 FF7Item::statusConfusion(int i){return Items[i].s_confusion;}
qint8 FF7Item::statusBerserk(int i){return Items[i].s_berserk;}
qint8 FF7Item::statusFrog(int i){return Items[i].s_frog;}
qint8 FF7Item::statusMini(int i){return Items[i].s_mini;}
qint8 FF7Item::statusPoison(int i){return Items[i].s_poison;}
qint8 FF7Item::statusFury(int i){return Items[i].s_fury;}
qint8 FF7Item::statusSadness(int i){return Items[i].s_sadness;}
qint8 FF7Item::statusDarkness(int i){return Items[i].s_darkness;}
qint8 FF7Item::statusHaste(int i){return Items[i].s_haste;}
qint8 FF7Item::statusSlow(int i){return Items[i].s_slow;}
qint8 FF7Item::statusStop(int i){return Items[i].s_stop;}
qint8 FF7Item::statusBarrier(int i){return Items[i].s_barrier;}
qint8 FF7Item::statusMagicBarrier(int i){return Items[i].s_m_barrier;}
qint8 FF7Item::statusReflect(int i){return Items[i].s_reflect;}
qint8 FF7Item::statusShield(int i){return Items[i].s_sheild;}
qint8 FF7Item::statusRegen(int i){return Items[i].s_regen;}
qint8 FF7Item::statusResist(int i){return Items[i].s_resist;}
QString FF7Item::styleMateriaSlotNoGrowth(void)
{
    return QString("QPushButton:enabled{border: 0px;border-radius:16px;background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.814, fx:0.5, fy:0.5, stop:0 rgba(0, 1, 0, 255), stop:0.079096 rgba(77, 77, 77, 255), stop:0.152542 rgba(11, 28, 19, 255), stop:0.429379 rgba(37, 37, 37, 255), stop:0.514124 rgba(200, 195, 194, 255), stop:0.576271 rgba(153, 152, 152, 255), stop:0.655367 rgba(185, 181, 179, 255), stop:0.677966 rgba(37, 37, 37, 0));}QPushButton:hover{}");
}
QString FF7Item::styleMateriaSlot(void)
{
    return QString("QPushButton:enabled{border: 0px;border-radius:16px;background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.814, fx:0.5, fy:0.5, stop:0 rgba(0, 1, 0, 255), stop:0.429379 rgba(37, 37, 37, 255), stop:0.514124 rgba(200, 195, 194, 255), stop:0.576271 rgba(153, 152, 152, 255), stop:0.655367 rgba(185, 181, 179, 255), stop:0.677966 rgba(37, 37, 37, 0));}QPushButton:hover{}");
}
QString FF7Item::styleMateriaLink(void)
{
    return QString("QLabel:enabled{background-color: qlineargradient(spread:reflect, x1:0.5, y1:0.5, x2:0.5, y2:0, stop:0.0225989 rgba(37, 37, 37, 255), stop:0.231638 rgba(153, 152, 152, 255), stop:0.389831 rgba(200, 195, 194, 255), stop:0.502825 rgba(138, 137, 137, 255), stop:0.621469 rgba(200, 195, 194, 255), stop:0.768362 rgba(138, 137, 137, 255), stop:0.932584 rgba(37, 37, 37, 0));}");
}

quint16 FF7Item::itemDecode( quint16 itemraw )
{//see FF7Save::itemDecode for full comments
    quint16 item;
    #ifdef Q_BYTE_ORDER
        #if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
            item = itemraw;
        #elif Q_BYTE_ORDER == Q_BIG_ENDIAN
            item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);
        #else
            int one = 1;
            if (*(char *)&one){item = itemraw;}
            else {item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);}
        #endif
    #else
        int one = 1;
        if (*(char *)&one){item = itemraw;}
        else {item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);}
    #endif

    return item;
}
quint16 FF7Item::itemEncode( quint16 id, quint8 qty )
{//see FF7Save::itemEncode for full comments
    quint16 item,itemraw;
    #ifdef Q_BYTE_ORDER
        #if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
            item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
            itemraw = item;
        #elif Q_BYTE_ORDER == Q_BIG_ENDIAN
            item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
            itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
        #else
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
        #endif
    #else
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
    #endif

    return itemraw;
}

quint16 FF7Item::itemId(quint16 item)
{
    quint16 new_item = itemDecode(item);
    quint16 id = (new_item & 0x1FF);
    return id;
}
quint8 FF7Item::itemQty(quint16 item)
{
    quint16 new_item = itemDecode(item);
    quint8 qty;
    qty = (new_item & 0xFE00) >> 9;
    return qty;
}
