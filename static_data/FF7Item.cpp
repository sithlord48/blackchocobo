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
//Static Images
#include "icons/Item_Icons/mlink.xpm"
#include "icons/Item_Icons/m_no_grow_slot.xpm"
#include "icons/Item_Icons/m_grow_slot.xpm"
#include <QCoreApplication>

QString FF7Item::Name(int i){return qApp->translate("Items",Items[i].name.toAscii());}
QString FF7Item::Desc(int i){return qApp->translate("Item_desc",Items[i].desc.toAscii());}
qint8  FF7Item::Type(int i){return Items[i].type;}
QImage FF7Item::Image(int i){return Items[i].image;}
qint8 FF7Item::mslots(int i){return Items[i].mslots;}
qint8 FF7Item::linked(int i){return Items[i].linked;}
qint8 FF7Item::m_growth_rate(int i){return Items[i].mgrowth;}
qint8 FF7Item::Stat_hp(int i){return Items[i].hp;}
qint8 FF7Item::Stat_mp(int i){return Items[i].mp;}
qint8 FF7Item::Stat_str(int i){return Items[i].str;}
qint8 FF7Item::Stat_vit(int i){return Items[i].vit;}
qint8 FF7Item::Stat_dex(int i){return Items[i].dex;}
qint8 FF7Item::Stat_lck(int i){return Items[i].lck;}
qint8 FF7Item::Stat_mag(int i){return Items[i].mag;}
qint8 FF7Item::Stat_spi(int i){return Items[i].spi;}
QImage FF7Item::Image_m_no_grow_slot(void){return QImage(m_no_grow_slot_xpm);}
QImage FF7Item::Image_m_grow_slot(void){return QImage(m_grow_slot_xpm);}
QImage FF7Item::Image_mlink(void){return QImage(mlink_xpm);}
qint8 FF7Item::element_restoration(int i){return Items[i].e_restoration;}
qint8 FF7Item::element_fire(int i){return Items[i].e_fire;}
qint8 FF7Item::element_cold(int i){return Items[i].e_cold;}
qint8 FF7Item::element_lightning(int i){return Items[i].e_lightning;}
qint8 FF7Item::element_earth(int i){return Items[i].e_earth;}
qint8 FF7Item::element_wind(int i){return Items[i].e_wind;}
qint8 FF7Item::element_water(int i){return Items[i].e_water;}
qint8 FF7Item::element_gravity(int i){return Items[i].e_gravity;}
qint8 FF7Item::element_holy(int i){return Items[i].e_holy;}
qint8 FF7Item::element_poison(int i){return Items[i].e_poison;}
qint8 FF7Item::element_cut(int i){return Items[i].e_cut;}
qint8 FF7Item::element_shoot(int i){return Items[i].e_shoot;}
qint8 FF7Item::element_punch(int i){return Items[i].e_punch;}
qint8 FF7Item::element_hit(int i){return Items[i].e_hit;}
//Status Functions
qint8 FF7Item::status_death(int i){return Items[i].s_death;}
qint8 FF7Item::status_slow_numb(int i){return Items[i].s_slow_numb;}
qint8 FF7Item::status_d_sentence(int i){return Items[i].s_d_sentence;}
qint8 FF7Item::status_paralysis(int i){return Items[i].s_paralysis;}
qint8 FF7Item::status_petrify(int i){return Items[i].s_petrify;}
qint8 FF7Item::status_silence(int i){return Items[i].s_silence;}
qint8 FF7Item::status_sleep(int i){return Items[i].s_sleep;}
qint8 FF7Item::status_confusion(int i){return Items[i].s_confusion;}
qint8 FF7Item::status_berserk(int i){return Items[i].s_berserk;}
qint8 FF7Item::status_frog(int i){return Items[i].s_frog;}
qint8 FF7Item::status_mini(int i){return Items[i].s_mini;}
qint8 FF7Item::status_poison(int i){return Items[i].s_poison;}
qint8 FF7Item::status_fury(int i){return Items[i].s_fury;}
qint8 FF7Item::status_sadness(int i){return Items[i].s_sadness;}
qint8 FF7Item::status_darkness(int i){return Items[i].s_darkness;}
qint8 FF7Item::status_haste(int i){return Items[i].s_haste;}
qint8 FF7Item::status_slow(int i){return Items[i].s_slow;}
qint8 FF7Item::status_stop(int i){return Items[i].s_stop;}
qint8 FF7Item::status_barrier(int i){return Items[i].s_barrier;}
qint8 FF7Item::status_m_barrier(int i){return Items[i].s_m_barrier;}
qint8 FF7Item::status_reflect(int i){return Items[i].s_reflect;}
qint8 FF7Item::status_shield(int i){return Items[i].s_sheild;}
qint8 FF7Item::status_regen(int i){return Items[i].s_regen;}

