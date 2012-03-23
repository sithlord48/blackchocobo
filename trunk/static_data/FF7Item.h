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
#ifndef FF7ITEM_H
    #define FF7ITEM_H
#include <QObject>
#include <QImage>

#include "icons/Item_Icons/accessory.xpm"
#include "icons/Item_Icons/armor.xpm"
#include "icons/Item_Icons/clip.xpm"
#include "icons/Item_Icons/glove.xpm"
#include "icons/Item_Icons/gun.xpm"
#include "icons/Item_Icons/gunarm.xpm"
#include "icons/Item_Icons/item.xpm"
#include "icons/Item_Icons/mphone.xpm"
#include "icons/Item_Icons/spear.xpm"
#include "icons/Item_Icons/staff.xpm"
#include "icons/Item_Icons/star.xpm"
#include "icons/Item_Icons/sword.xpm"

struct ITEM {
        QString name;
        QString desc;
        qint8 type; //0-unknown 1-item 2-cloud 3-barret 4-tifa 5-red 6-aerith 7-cid 8-yuffie 9-cait 10-vincent 11-armor 12-accessory
        QImage image;
        qint8 mgrowth;
        qint8 mslots;
        qint8 linked;
        qint8 hp;
        qint8 mp;
        qint8 str;
        qint8 vit;
        qint8 dex;
        qint8 lck;
        qint8 mag;
        qint8 spi;

        /* all Elements in FF7
           -3: Absorb
           -2: Nullify
           -1: Halve
            0: No Effect
           +1: damage
         */
        qint8 e_restoration;
        qint8 e_fire;
        qint8 e_cold;
        qint8 e_lightning;
        qint8 e_earth;
        qint8 e_wind;
        qint8 e_water;
        qint8 e_gravity;
        qint8 e_holy;
        qint8 e_poison;
        qint8 e_cut;
        qint8 e_shoot;
        qint8 e_punch;
        qint8 e_hit;

        /* all Status Effects in FF7
           -2: Protect
           -1: Remove
            0: No Effect
           +1: Infilict
           +2: Auto SelfCast
        */
        qint8 s_death;
        qint8 s_slow_numb;
        qint8 s_d_sentence;
        qint8 s_paralysis;
        qint8 s_petrify;
        qint8 s_silence;
        qint8 s_sleep;
        qint8 s_confusion;
        qint8 s_berserk;
        qint8 s_frog;
        qint8 s_mini;
        qint8 s_poison;
        qint8 s_fury;
        qint8 s_sadness;
        qint8 s_darkness;
        qint8 s_haste;
        qint8 s_slow;
        qint8 s_stop;
        qint8 s_barrier;
        qint8 s_m_barrier;
        qint8 s_reflect;
        qint8 s_sheild;
        qint8 s_regen;
};
class FF7Item
{
  public:
    QString Name(int);
    QString Desc(int);
    qint8 Type(int);
    QImage Image(int);
    QImage Image_m_no_grow_slot(void);
    QImage Image_m_grow_slot(void);
    QImage Image_mlink(void);
    qint8 mslots(int);
    qint8 linked(int);
    qint8 Stat_hp(int);
    qint8 Stat_mp(int);
    qint8 Stat_str(int);
    qint8 Stat_vit(int);
    qint8 Stat_dex(int);
    qint8 Stat_lck(int);
    qint8 Stat_mag(int);
    qint8 Stat_spi(int);
    //don't forget to add nessessary items for growth rate and status/elements.
    qint8 m_growth_rate(int);
    //Elemental Functions
    qint8 element_restoration(int);
    qint8 element_fire(int);
    qint8 element_cold(int);
    qint8 element_lightning(int);
    qint8 element_earth(int);
    qint8 element_wind(int);
    qint8 element_water(int);
    qint8 element_gravity(int);
    qint8 element_holy(int);
    qint8 element_poison(int);
    qint8 element_cut(int);
    qint8 element_shoot(int);
    qint8 element_punch(int);
    qint8 element_hit(int);
    //Status Functions
    qint8 status_death(int);
    qint8 status_slow_numb(int);
    qint8 status_d_sentence(int);
    qint8 status_paralysis(int);
    qint8 status_petrify(int);
    qint8 status_silence(int);
    qint8 status_sleep(int);
    qint8 status_confusion(int);
    qint8 status_berserk(int);
    qint8 status_frog(int);
    qint8 status_mini(int);
    qint8 status_poison(int);
    qint8 status_fury(int);
    qint8 status_sadness(int);
    qint8 status_darkness(int);
    qint8 status_haste(int);
    qint8 status_slow(int);
    qint8 status_stop(int);
    qint8 status_barrier(int);
    qint8 status_m_barrier(int);
    qint8 status_reflect(int);
    qint8 status_shield(int);
    qint8 status_regen(int);
};
static ITEM Items[]=
{
    {QT_TRANSLATE_NOOP("Items","Potion"),QT_TRANSLATE_NOOP("Item_desc","Restores 100 HP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Hi-Potion"),QT_TRANSLATE_NOOP("Item_desc","Restores 500 HP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","X-Potion"),QT_TRANSLATE_NOOP("Item_desc","Restores all lost HP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Ether"),QT_TRANSLATE_NOOP("Item_desc","Restores 100 MP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Turbo Ether"),QT_TRANSLATE_NOOP("Item_desc","Restores all lost MP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Elixir"),QT_TRANSLATE_NOOP("Item_desc","Fully Restores HP/MP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Megalixir"),QT_TRANSLATE_NOOP("Item_desc","Fully Restores all Members HP/MP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Phoenix Down"),QT_TRANSLATE_NOOP("Item_desc","Restores life"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Antidote"),QT_TRANSLATE_NOOP("Item_desc","Cures [Poison]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Soft"),QT_TRANSLATE_NOOP("Item_desc","Cures [Petrify]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Maiden's Kiss"),QT_TRANSLATE_NOOP("Item_desc","Cures [Frog]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Cornucopia"),QT_TRANSLATE_NOOP("Item_desc","Cures [Small]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Echo screen"),QT_TRANSLATE_NOOP("Item_desc","Cures [Silence]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Hyper"),QT_TRANSLATE_NOOP("Item_desc","Cures [Sadness]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,-1,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Tranquilizer"),QT_TRANSLATE_NOOP("Item_desc","Cures [Fury]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,+1,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Remedy"),QT_TRANSLATE_NOOP("Item_desc","Cures abnormal status"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Smoke Bomb"),QT_TRANSLATE_NOOP("Item_desc","Can escape from opponents during battle"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Speed Drink"),QT_TRANSLATE_NOOP("Item_desc","Casts [Haste] on one ally"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Hero Drink"),QT_TRANSLATE_NOOP("Item_desc","Raises ability once during battle"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Vaccine"),QT_TRANSLATE_NOOP("Item_desc","Protects against transformations"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Grenade"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Shrapnel"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Right arm"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Hourglass"),QT_TRANSLATE_NOOP("Item_desc","Stops all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Kiss of Death"),QT_TRANSLATE_NOOP("Item_desc","Uses [Death] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Spider Web"),QT_TRANSLATE_NOOP("Item_desc","Slows all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Dream Powder"),QT_TRANSLATE_NOOP("Item_desc","Uses [Sleepel] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Mute Mask"),QT_TRANSLATE_NOOP("Item_desc","Uses [Silence] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","War Gong"),QT_TRANSLATE_NOOP("Item_desc","Uses [Berserk] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Loco weed"),QT_TRANSLATE_NOOP("Item_desc","Uses [Confu] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Fire Fang"),QT_TRANSLATE_NOOP("Item_desc","Uses [Fire2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Fire Veil"),QT_TRANSLATE_NOOP("Item_desc","Uses [Fire3] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Antarctic Wind"),QT_TRANSLATE_NOOP("Item_desc","Uses [Ice2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Ice Crystal"),QT_TRANSLATE_NOOP("Item_desc","Uses [Ice3] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Bolt Plume"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bolt2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Swift Bolt"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bolt3] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Earth Drum"),QT_TRANSLATE_NOOP("Item_desc","Uses [Quake2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Earth Mallet"),QT_TRANSLATE_NOOP("Item_desc","Uses [Quake3] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Deadly Waste"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bio2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","M-Tentacles"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bio3] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Stardust"),QT_TRANSLATE_NOOP("Item_desc","Uses [Comet2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Vampire Fang"),QT_TRANSLATE_NOOP("Item_desc","Drains HP out of one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Ghost Hand"),QT_TRANSLATE_NOOP("Item_desc","Drains MP out of one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Vagyrisk Claw"),QT_TRANSLATE_NOOP("Item_desc","Petrifies one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Light Curtain"),QT_TRANSLATE_NOOP("Item_desc","Creates [Barrier] around all allies"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Lunar Curtain"),QT_TRANSLATE_NOOP("Item_desc","Creates [MBarrier] around all allies"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Mirror"),QT_TRANSLATE_NOOP("Item_desc","Uses [Reflect] on all allies"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0},
    {QT_TRANSLATE_NOOP("Items","Holy Torch"),QT_TRANSLATE_NOOP("Item_desc","Uses [DeSpell] on all allies"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1},
    {QT_TRANSLATE_NOOP("Items","Bird Wing"),QT_TRANSLATE_NOOP("Item_desc","Uses whirlwind on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Dragon Scales"),QT_TRANSLATE_NOOP("Item_desc","Water damage on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Impaler"),QT_TRANSLATE_NOOP("Item_desc","Changes one opponent to a frog"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Shrivel"),QT_TRANSLATE_NOOP("Item_desc","Uses [Mini] on one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Eye drop"),QT_TRANSLATE_NOOP("Item_desc","Cures [Darkness]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Molotov"),QT_TRANSLATE_NOOP("Item_desc","Fire damage on one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","S-mine"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage on one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","8-inch Cannon"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Graviball"),QT_TRANSLATE_NOOP("Item_desc","Uses [Demi] against one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","T/S Bomb"),QT_TRANSLATE_NOOP("Item_desc","Uses [Demi2] against one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Ink"),QT_TRANSLATE_NOOP("Item_desc","Uses [Darkness] against one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Dazers"),QT_TRANSLATE_NOOP("Item_desc","Paralyzes one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Dragon Fang"),QT_TRANSLATE_NOOP("Item_desc","Lightning damage against all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Cauldron"),QT_TRANSLATE_NOOP("Item_desc","Uses [Poison/Confu/Sleepel/Silence/Small/Frog]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,+1,+1,0,+1,+1,+1,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Sylkis Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Reagan Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Mimett Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Curiel Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Pahsana Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Tantal Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Krakka Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Gysahl Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Tent"),QT_TRANSLATE_NOOP("Item_desc","Restores ally's max HP/MP. Use at Save Point."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Power Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Strength]"),1,QImage(item_xpm),
     0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Guard Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Vitality]"),1,QImage(item_xpm),
     0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Magic Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Magic Power]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Mind Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Spirit]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Speed Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Dexterity]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Luck Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Luck]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Zeio Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Carob Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Porov Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Pram Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Lasan Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Saraha Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Luchile Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Pepio Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Battery"),QT_TRANSLATE_NOOP("Item_desc","Looks like it can start some sort of machine"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Tissue"),QT_TRANSLATE_NOOP("Item_desc","This one's a little tough..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Omnislash"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Omnislash]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Catastrophe"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Catastrophe]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Final Heaven"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Final Heaven]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Great Gospel"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Great Gospel]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Cosmo Memory"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Cosmo Memory]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","All Creation"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [All Creation]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Chaos"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Chaos]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Highwind"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Highwind]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","1/35 soldier"),QT_TRANSLATE_NOOP("Item_desc","Shinra armored 'attack' soldiers: 12 in the Set!"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Super Sweeper"),QT_TRANSLATE_NOOP("Item_desc","A new machine to protect the reactor!"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Masamune Blade"),QT_TRANSLATE_NOOP("Item_desc","A prefect copy of Sephiroth's sword!"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Save Crystal"),QT_TRANSLATE_NOOP("Item_desc","Use This to create a SAVE Point in the 'North Cave'"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Combat Diary"),QT_TRANSLATE_NOOP("Item_desc","A record of Master Dio's fiercest battles"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Autograph"),QT_TRANSLATE_NOOP("Item_desc","Dio's autograph"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Gambler"),QT_TRANSLATE_NOOP("Item_desc","Second part of Dio's diary: The Gold Saucer years"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Desert Rose"),QT_TRANSLATE_NOOP("Item_desc","Blooms once every 1000 years"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Earth Harp"),QT_TRANSLATE_NOOP("Item_desc","Calms the hearts of all who hear it"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Guide Book"),QT_TRANSLATE_NOOP("Item_desc","Map of another world. It Slumbers with sunken ships"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  //nothing 106-127
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //cloud weapons 128 -143
   {QT_TRANSLATE_NOOP("Items","Buster Sword"),QT_TRANSLATE_NOOP("Item_desc","Initial equiping"),2,QImage(sword_xpm),
    1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Saber"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Hardedge"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Butterfly Edge"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Enhance Sword"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    1,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Organics"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    1,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Sword"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Force Stealer"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rune Blade"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Murasame"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Nail Bat"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Yoshiyuki"),QT_TRANSLATE_NOOP("Item_desc","Sword is used when an ally is down"),2,QImage(sword_xpm),
    0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Apocalypse"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    3,3,0,0,0,0,0,0,0,0,+13,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Heaven's Cloud"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ragnarok"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    1,6,3,0,0,0,0,0,0,0,+35,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ultima Weapon"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(sword_xpm),
    0,8,4,0,0,0,0,0,0,0,+24,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   ///tifa's weapons 144-159/tifa's weapons 144-159
   {QT_TRANSLATE_NOOP("Items","Leather Glove"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Metal Knuckle"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Claw"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Grand Glove"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Tiger Fang"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Diamond Knuckle"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Dragon Claw"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    1,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Glove"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Motor Drive"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Platinum Fist"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Kaiser Knuckle"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    1,8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Work Glove"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Powersoul"),QT_TRANSLATE_NOOP("Item_desc","Power up when [Near death]"),4,QImage(glove_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Master Fist"),QT_TRANSLATE_NOOP("Item_desc","Power up when condition changes"),4,QImage(glove_xpm),
    1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","God's Hand"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Premium Heart"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(glove_xpm),
    0,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //barret's weapons 160-175
   {QT_TRANSLATE_NOOP("Items","Gatling Gun"),QT_TRANSLATE_NOOP("Item_desc","Initial equip. Long Range Weapon"),3,QImage(gunarm_xpm),
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Assault Gun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),3,QImage(gunarm_xpm),
    1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Cannon Ball"),QT_TRANSLATE_NOOP("Item_desc",""),3,QImage(gunarm_xpm),
    1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Atomic Scissors"),QT_TRANSLATE_NOOP("Item_desc",""),3,QImage(gunarm_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Heavy Vulcan"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),3,QImage(gunarm_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Chainsaw"),QT_TRANSLATE_NOOP("Item_desc",""),3,QImage(gunarm_xpm),
    1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Microlaser"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),3,QImage(gunarm_xpm),
    1,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","A M Cannon"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),3,QImage(gunarm_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","W Machine Gun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),3,QImage(gunarm_xpm),
    2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Drill Arm"),QT_TRANSLATE_NOOP("Item_desc",""),3,QImage(gunarm_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Solid Bazooka"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),3,QImage(gunarm_xpm),
    1,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rocket Punch"),QT_TRANSLATE_NOOP("Item_desc",""),3,QImage(gunarm_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Enemy Launcher"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),3,QImage(gunarm_xpm),
    1,5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Pile Banger"),QT_TRANSLATE_NOOP("Item_desc",""),3,QImage(gunarm_xpm),
    0,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Max Ray"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),3,QImage(gunarm_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Missing Score"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),3,QImage(gunarm_xpm),
    0,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //red's weapons 176-189
   {QT_TRANSLATE_NOOP("Items","Mythril Clip"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Diamond Pin"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Barette"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gold Barette"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Adaman Clip"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    1,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Comb"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Magic Comb"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Plus Barrette"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Centclip"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Hairpin"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QImage(clip_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Seraph Comb"),QT_TRANSLATE_NOOP("Item_desc","Memento of father"),5,QImage(clip_xpm),
    1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Behemoth Horn"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    1,6,0,0,0,0,+35,0,0,0,+18,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Spring Gun Clip"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Limited Moon"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(clip_xpm),
    0,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //aeris weapons 190-200
   {QT_TRANSLATE_NOOP("Items","Guard Stick"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(staff_xpm),
    1,2,1,0,0,0,+1,0,0,0,+4,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Rod"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(staff_xpm),
    1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Full Metal Staff"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(staff_xpm),
    1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Striking Staff"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(staff_xpm),
    1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Prism Staff"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(staff_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Aurora Rod"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(staff_xpm),
    1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wizard Staff"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(staff_xpm),
    2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wizer Staff"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(staff_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fairy Tale"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(staff_xpm),
    1,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Umbrella"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(staff_xpm),
    0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Princess Guard"),QT_TRANSLATE_NOOP("Item_desc","Raises Power when you need to protect others nearby"),6,QImage(staff_xpm),
    1,7,3,0,0,0,+12,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //cid weapons 201-214
   {QT_TRANSLATE_NOOP("Items","Spear"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Slash Lance"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Trident"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mast Ax"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    1,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Partisan"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Viper Halberd"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Javelin"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    2,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Grow Lance"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mop"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Dragoon Lance"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Scimitar"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Flayer"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Spirit Lance"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    1,4,2,0,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Venus Gospel"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(spear_xpm),
    0,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //yuffie weapons 215-228
   {QT_TRANSLATE_NOOP("Items","4-point Shuriken"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Boomerang"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Pinwheel"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Razor Ring"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Hawkeye"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    1,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Cross"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wind Slash"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Twin Viper"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Spiral Shuriken"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    1,8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Superball"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Magic Shuriken"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    1,3,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rising Sun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    2,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Oritsuru"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    1,8,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Conformer"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),8,QImage(star_xpm),
    0,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //cait sith weapons 229-241
   {QT_TRANSLATE_NOOP("Items","Yellow M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Green M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Blue M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Red M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    1,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","White M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Black M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Trumpet Shell"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gold M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    1,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Battle Trumpet"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    0,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Starlight Phone"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    1,8,4,0,0,0,+30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","HP Shout"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(mphone_xpm),
    0,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //vincent weapons... 242-254
   {QT_TRANSLATE_NOOP("Items","Quicksilver"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shotgun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shortbarrel"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Lariat"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    1,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Winchester"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Peacemaker"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    2,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Buntline"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    2,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Long Barrel R"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    1,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Rifle"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Sniper CR"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Supershot ST"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    0,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Outsider"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    1,8,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Death Penalty"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(gun_xpm),
    0,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //sepi weapon =255
   {QT_TRANSLATE_NOOP("Items","Masamune"),QT_TRANSLATE_NOOP("Item_desc",""),1,QImage(item_xpm),
    0,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //armor  256-287
   {QT_TRANSLATE_NOOP("Items","Bronze Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Iron Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Titan Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Carbon Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gold Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Diamond Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Platinum Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rune Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Edincoat"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,7,0,0,0,0,0,0,0,+5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wizard Bracelet"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,8,4,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Adaman Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gigas Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    0,5,2,0,0,+30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Imperial Guard"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Aegis Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fourth Bracelet"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,5,2,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Warrior Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    0,4,2,0,0,+5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shinra Beta"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shinra Alpha"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Four Slots"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fire Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains [Fire] attacks"),11,QImage(armor_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Aurora Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains [Cold] attacks"),11,QImage(armor_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Bolt Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains [Lightning] attacks"),11,QImage(armor_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Dragon Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains 1/2 [Fire/Cold/Lightning] attack"),11,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Minerva Band"),QT_TRANSLATE_NOOP("Item_desc","Women's Armlet nullifies [Fire/Cold/Gravity/Holy]"),11,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,-2,-2,0,0,0,0,-2,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Escort Guard"),QT_TRANSLATE_NOOP("Item_desc","Man's Armlet nullifies [Lightning/Earth/Water/Poison]"),11,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,-2,-2,0,-2,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mystile"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ziedrich"),QT_TRANSLATE_NOOP("Item_desc","Decreases all elemental attacks by 1/2"),11,QImage(armor_xpm),
    0,0,0,0,0,+20,0,0,0,+20,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Precious Watch"),QT_TRANSLATE_NOOP("Item_desc","A gorgeous watch"),11,QImage(armor_xpm),
    0,8,0,0,0,0,0,+30,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Chocobracelet"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(armor_xpm),
    0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //accessorys 288-319
   {QT_TRANSLATE_NOOP("Items","Power Wrist"),QT_TRANSLATE_NOOP("Item_desc","Strength +10"),12,QImage(accessory_xpm),
    0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Protect Vest"),QT_TRANSLATE_NOOP("Item_desc","Vitality +10"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Earring"),QT_TRANSLATE_NOOP("Item_desc","Magic +10"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Talisman"),QT_TRANSLATE_NOOP("Item_desc","Spirit +10"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Choco Feather"),QT_TRANSLATE_NOOP("Item_desc","Dexterity +10"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Amulet"),QT_TRANSLATE_NOOP("Item_desc","Luck +10"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Champion Belt"),QT_TRANSLATE_NOOP("Item_desc","Power & Vitality +30"),12,QImage(accessory_xpm),
    0,0,0,0,0,+30,+30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Poison Ring"),QT_TRANSLATE_NOOP("Item_desc","Drains [Poison] attacks, protects against [Poison]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Tough Ring"),QT_TRANSLATE_NOOP("Item_desc","Vitality & Spirit +50"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,+50,0,0,0,+50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Circlet"),QT_TRANSLATE_NOOP("Item_desc","Magic & Spirit +30"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,+30,+30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Star Pendant"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Poison]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Glasses"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Darkness]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Headband"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Sleep]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fairy Ring"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Poison/Darkness]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,-2,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Jem Ring"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Paralyze/Petrify/Slow-numb]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,-2,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","White Cape"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Frog/Small]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Sprint Shoes"),QT_TRANSLATE_NOOP("Item_desc","Automatically put you in [Haste]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Peace Ring"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Berserk/Fury/Sadness]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,-2,-2,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ribbon"),QT_TRANSLATE_NOOP("Item_desc","Protects against all abnormal status"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fire Ring"),QT_TRANSLATE_NOOP("Item_desc","Nullifies [Fire] attacks"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ice Ring"),QT_TRANSLATE_NOOP("Item_desc","Nullifies [Cold] attacks"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Bolt Ring"),QT_TRANSLATE_NOOP("Item_desc","Nullifies [Lightning] attacks"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Tetra Elemental"),QT_TRANSLATE_NOOP("Item_desc","Drains [Fire/Cold/Lightning/Earth] attacks"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,-3,-3,-3,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Safety Bit"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Sudden Death/Petrify/Slow-numb]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fury Ring"),QT_TRANSLATE_NOOP("Item_desc","Automatically puts you in [Berserk]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Curse Ring"),QT_TRANSLATE_NOOP("Item_desc","It increases each status but..."),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Protect Ring"),QT_TRANSLATE_NOOP("Item_desc","Automatically sets up [Barrier/MBarrier]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,+2,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Cat's Bell"),QT_TRANSLATE_NOOP("Item_desc","Restores HP as you walk"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Reflect Ring"),QT_TRANSLATE_NOOP("Item_desc","Automatically sets up [Reflect]"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0},
   {QT_TRANSLATE_NOOP("Items","Water Ring"),QT_TRANSLATE_NOOP("Item_desc","Drains Water attacks"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Sneak Glove"),QT_TRANSLATE_NOOP("Item_desc","Increases Stealing rate"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","HypnoCrown"),QT_TRANSLATE_NOOP("Item_desc","Increases Manipulation rate"),12,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
#endif //FF7Item
