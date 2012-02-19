/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
//                                                                          //
//    This file is part of <UnNamedToolKit>                                 //
//                                                                          //
//  <UnNamedToolKit> is free software: you can redistribute it and/or modify//
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
// <UnNamedToolKit> is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#include "ItemPreview.h"

ItemPreview::ItemPreview(QWidget *parent) :QWidget(parent)
{
  lbl_name=new QLabel();
  lbl_desc=new QLabel();
  lbl_icon=new QLabel();
  lbl_icon->setFixedSize(24,24);
  lbl_icon->setScaledContents(1);
  spacer=new QSpacerItem(-1,-1,QSizePolicy::Expanding,QSizePolicy::Minimum);
  lbl_slot_1= new QLabel();
  lbl_slot_1->setFixedSize(24,24);
  lbl_slot_1->setScaledContents(1);
  lbl_slot_1->setHidden(1);

  lbl_m_link_1= new QLabel();
  lbl_m_link_1->setFixedSize(12,24);
  lbl_m_link_1->setScaledContents(1);

  lbl_slot_2 = new QLabel();
  lbl_slot_2->setFixedSize(24,24);
  lbl_slot_2->setScaledContents(1);
  lbl_slot_2->setHidden(1);

  QHBoxLayout *slots_1_and_2 = new QHBoxLayout();
  slots_1_and_2->setContentsMargins(0,0,0,0);
  slots_1_and_2->addWidget(lbl_slot_2);
  slots_1_and_2->addWidget(lbl_m_link_1);
  slots_1_and_2->addWidget(lbl_slot_1);
  slots_1_and_2->setSpacing(0);

  lbl_slot_3 = new QLabel();
  lbl_slot_3->setFixedSize(24,24);
  lbl_slot_3->setScaledContents(1);
  lbl_slot_3->setHidden(1);

  lbl_m_link_2 = new QLabel();
  lbl_m_link_2->setFixedSize(12,24);
  lbl_m_link_2->setScaledContents(1);

  lbl_slot_4 = new QLabel();
  lbl_slot_4->setFixedSize(24,24);
  lbl_slot_4->setScaledContents(1);
  lbl_slot_4->setHidden(1);

  QHBoxLayout *slots_3_and_4 = new QHBoxLayout();
  slots_3_and_4->setContentsMargins(0,0,0,0);
  slots_3_and_4->addWidget(lbl_slot_4);
  slots_3_and_4->addWidget(lbl_m_link_2);
  slots_3_and_4->addWidget(lbl_slot_3);
  slots_3_and_4->setSpacing(0);

  lbl_slot_5 = new QLabel();
  lbl_slot_5->setFixedSize(24,24);
  lbl_slot_5->setScaledContents(1);
  lbl_slot_5->setHidden(1);

  lbl_m_link_3 = new QLabel();
  lbl_m_link_3->setFixedSize(12,24);
  lbl_m_link_3->setScaledContents(1);

  lbl_slot_6 = new QLabel();
  lbl_slot_6->setFixedSize(24,24);
  lbl_slot_6->setScaledContents(1);
  lbl_slot_6->setHidden(1);

  QHBoxLayout *slots_5_and_6 = new QHBoxLayout();
  slots_5_and_6->setContentsMargins(0,0,0,0);
  slots_5_and_6->addWidget(lbl_slot_6);
  slots_5_and_6->addWidget(lbl_m_link_3);
  slots_5_and_6->addWidget(lbl_slot_5);
  slots_5_and_6->setSpacing(0);

  lbl_slot_7 = new QLabel();
  lbl_slot_7->setFixedSize(24,24);
  lbl_slot_7->setScaledContents(1);
  lbl_slot_7->setHidden(1);

  lbl_m_link_4 = new QLabel();
  lbl_m_link_4->setFixedSize(12,24);
  lbl_m_link_4->setScaledContents(1);

  lbl_slot_8 = new QLabel();
  lbl_slot_8->setFixedSize(24,24);
  lbl_slot_8->setScaledContents(1);
  lbl_slot_8->setHidden(1);

  QHBoxLayout *slots_7_and_8 = new QHBoxLayout();
  slots_7_and_8->setContentsMargins(0,0,0,0);
  slots_7_and_8->addWidget(lbl_slot_8);
  slots_7_and_8->addWidget(lbl_m_link_4);
  slots_7_and_8->addWidget(lbl_slot_7);
  slots_7_and_8->setSpacing(0);

  materia_slot_box = new QGroupBox();
  materia_slot_box->setContentsMargins(0,0,0,0);
  materia_slot_box->setShown(0);
  materia_slot_box->setFixedSize(294,40);

  QHBoxLayout *materia_slots = new QHBoxLayout();
  materia_slots->setContentsMargins(0,0,0,0);
  materia_slots->addSpacerItem(spacer);
  materia_slots->addLayout(slots_7_and_8);
  materia_slots->addLayout(slots_5_and_6);
  materia_slots->addLayout(slots_3_and_4);
  materia_slots->addLayout(slots_1_and_2);
  materia_slots->setSpacing(12);
  materia_slot_box->setLayout(materia_slots);

  elemental_effects = new QListWidget();
  QHBoxLayout *elemental = new QHBoxLayout();
  elemental->setContentsMargins(0,0,0,0);
  elemental->addWidget(elemental_effects);

  elemental_box =new QGroupBox();
  elemental_box->setContentsMargins(3,3,3,3);
  elemental_box->setLayout(elemental);
  elemental_box->setTitle(tr("Elemental Effects"));
  elemental_box->setHidden(1);

  status_effects = new QListWidget();
  QHBoxLayout *status =new QHBoxLayout();
  status->setContentsMargins(0,0,0,0);
  status->addWidget(status_effects);

  status_box = new QGroupBox();
  status_box->setContentsMargins(3,3,3,3);
  status_box->setLayout(status);
  status_box->setTitle(tr("Status Effects"));
  status_box->setHidden(1);

  QHBoxLayout *effects_layout =new QHBoxLayout();
  effects_layout->setContentsMargins(0,0,0,0);
  effects_layout->addWidget(elemental_box);
  effects_layout->addWidget(status_box);
  effects_layout->setSpacing(0);

  QHBoxLayout *top = new QHBoxLayout();
  top->addWidget(lbl_icon);
  top->addWidget(lbl_name);

  QVBoxLayout *main_layout =new QVBoxLayout(this);
  main_layout->setContentsMargins(3,3,3,3);
  main_layout->addLayout(top);
  main_layout->addWidget(lbl_desc);
  main_layout->addWidget(materia_slot_box);
  main_layout->addLayout(effects_layout);
}
void ItemPreview::setName(QString text){lbl_name->setText(text);lbl_name->adjustSize();}
void ItemPreview::setDesc(QString text){lbl_desc->setText(text);lbl_desc->adjustSize();}
void ItemPreview::setIcon(QPixmap picture){lbl_icon->setPixmap(picture);lbl_icon->adjustSize();}

void ItemPreview::setItem(int id)
{
    lbl_slot_8->setHidden(1);
    lbl_slot_7->setHidden(1);
    lbl_slot_6->setHidden(1);
    lbl_slot_5->setHidden(1);
    lbl_slot_4->setHidden(1);
    lbl_slot_3->setHidden(1);
    lbl_slot_2->setHidden(1);
    lbl_slot_1->setHidden(1);

    lbl_m_link_1->setPixmap(QPixmap());
    lbl_m_link_2->setPixmap(QPixmap());
    lbl_m_link_3->setPixmap(QPixmap());
    lbl_m_link_4->setPixmap(QPixmap());

    materia_slot_box->setShown(0);
    lbl_desc->setHidden(1);
    lbl_name->setHidden(1);
    lbl_icon->setHidden(1);
    status_box->setHidden(1);
    elemental_box->setHidden(1);

    if(id<0 || id>319){/*InValid Number..Do Nothing*/}
    else
    {
        if(data.Name(id) !="")
        {
            lbl_name->setHidden(0);
            setName(data.Name(id));
        }

        if(data.Desc(id)!="")
        {
            setDesc(data.Desc(id));
            lbl_desc->setHidden(0);
        }
        if(!data.Image(id).isNull())
        {
            lbl_icon->setHidden(0);
            setIcon(QPixmap::fromImage(data.Image(id)));
        }
        this->status_info(id);
        this->elemental_info(id);

        if(data.Type(id)>1 && data.Type(id)<12)
        {
            if(data.m_growth_rate(id)==0)
            {//no growth slots
                lbl_slot_1->setPixmap(QPixmap::fromImage(data.Image_m_no_grow_slot()));
                lbl_slot_2->setPixmap(QPixmap::fromImage(data.Image_m_no_grow_slot()));
                lbl_slot_3->setPixmap(QPixmap::fromImage(data.Image_m_no_grow_slot()));
                lbl_slot_4->setPixmap(QPixmap::fromImage(data.Image_m_no_grow_slot()));
                lbl_slot_5->setPixmap(QPixmap::fromImage(data.Image_m_no_grow_slot()));
                lbl_slot_6->setPixmap(QPixmap::fromImage(data.Image_m_no_grow_slot()));
                lbl_slot_7->setPixmap(QPixmap::fromImage(data.Image_m_no_grow_slot()));
                lbl_slot_8->setPixmap(QPixmap::fromImage(data.Image_m_no_grow_slot()));
            }
            else
            {//growth slots.
                lbl_slot_1->setPixmap(QPixmap::fromImage(data.Image_m_grow_slot()));
                lbl_slot_2->setPixmap(QPixmap::fromImage(data.Image_m_grow_slot()));
                lbl_slot_3->setPixmap(QPixmap::fromImage(data.Image_m_grow_slot()));
                lbl_slot_4->setPixmap(QPixmap::fromImage(data.Image_m_grow_slot()));
                lbl_slot_5->setPixmap(QPixmap::fromImage(data.Image_m_grow_slot()));
                lbl_slot_6->setPixmap(QPixmap::fromImage(data.Image_m_grow_slot()));
                lbl_slot_7->setPixmap(QPixmap::fromImage(data.Image_m_grow_slot()));
                lbl_slot_8->setPixmap(QPixmap::fromImage(data.Image_m_grow_slot()));
            }
            QString ap_rate =tr("APx%1").arg(data.m_growth_rate(id));
            materia_slot_box->setTitle(ap_rate);
            materia_slot_box->setShown(1);
            switch(data.mslots(id))
            {
                case 8:lbl_slot_8->setHidden(0);
                case 7:lbl_slot_7->setHidden(0);
                case 6:lbl_slot_6->setHidden(0);
                case 5:lbl_slot_5->setHidden(0);
                case 4:lbl_slot_4->setHidden(0);
                case 3:lbl_slot_3->setHidden(0);
                case 2:lbl_slot_2->setHidden(0);
                case 1:lbl_slot_1->setHidden(0);
            };

            switch(data.linked(id))
            {

                case 4: lbl_m_link_4->setPixmap(QPixmap::fromImage(data.Image_mlink()));
                case 3: lbl_m_link_3->setPixmap(QPixmap::fromImage(data.Image_mlink()));
                case 2: lbl_m_link_2->setPixmap(QPixmap::fromImage(data.Image_mlink()));
                case 1: lbl_m_link_1->setPixmap(QPixmap::fromImage(data.Image_mlink()));
            };
        }
    }
    this->adjustSize();
}
void ItemPreview::elemental_info(int id)
{

    int y=20;
    bool show=false;
    elemental_effects->clear();
    if(id<0 || id>319){/*invalid number*/}
    else
    {
        switch(data.element_restoration(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Restoration")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Restoration")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Restoration")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Restoration")); show=true; y+=18;break;
        };
        switch(data.element_fire(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Fire")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Fire")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Fire")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Fire")); show=true; y+=18;break;
        };
        switch(data.element_cold(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Cold")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Cold")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Cold")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Cold")); show=true; y+=18;break;
        };
        switch(data.element_lightning(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Lightning")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Lightning")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Lightning")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Lightning")); show=true; y+=18;break;
        };
        switch(data.element_earth(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Earth")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Earth")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Earth")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Earth")); show=true; y+=18;break;
        };
        switch(data.element_wind(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Wind")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Wind")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Wind")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Wind")); show=true; y+=18;break;
        };
        switch(data.element_water(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Water")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Water")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Water")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Water")); show=true; y+=18;break;
        };
        switch(data.element_gravity(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Gravity")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Gravity")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Gravity")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Gravity")); show=true; y+=18;break;
        };
        switch(data.element_holy(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Holy")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Holy")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Holy")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Holy")); show=true; y+=18;break;
        };
        switch(data.element_poison(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Poison")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Poison")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Poison")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Poison")); show=true; y+=18;break;
        };
        switch(data.element_cut(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Cut")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Cut")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Cut")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Cut")); show=true; y+=18;break;
        };
        switch(data.element_shoot(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Shoot")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Shoot")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Shoot")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Shoot")); show=true; y+=18;break;
        };
        switch(data.element_punch(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Punch")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Punch")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Punch")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Punch")); show=true; y+=18;break;
        };
        switch(data.element_hit(id))
        {
        case -3: elemental_effects->addItem(tr("Absorb:Hit")); show=true; y+=18; break;
        case -2: elemental_effects->addItem(tr("Nullify:Hit")); show=true; y+=18; break;
        case -1: elemental_effects->addItem(tr("Halve:Hit")); show=true; y+=18; break;
        case  0: break;
        case +1: elemental_effects->addItem(tr("Attack:Hit")); show=true; y+=18;break;
        };
        if(y<=100){elemental_box->setFixedSize(160,y);}
        else{elemental_box->setFixedSize(160,100);}
    }
    elemental_box->setVisible(show);
}
void ItemPreview::status_info(int id)
{
    int y=20;
    bool show=false;
    status_effects->clear();
    if(id<0 || id>319){/*invalid number*/}
    else
    {
        switch(data.status_death(id))
        {
        case -2: status_effects->addItem(tr("Protect:Death")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Death")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Death")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Death")); show=true; y+=18;break;
        };
        switch(data.status_slow_numb(id))
        {
        case -2: status_effects->addItem(tr("Protect:Slow-Numb")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Slow-Numb")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Slow-Numb")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Slow-Numb")); show=true; y+=18;break;
        };
        switch(data.status_d_sentence(id))
        {
        case -2: status_effects->addItem(tr("Protect:D.Sentence")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:D.Sentence")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:D.Sentence")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:D.Sentence")); show=true; y+=18;break;
        };
        switch(data.status_paralysis(id))
        {
        case -2: status_effects->addItem(tr("Protect:Paralysis")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Paralysis")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Paralysis")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Paralysis")); show=true; y+=18;break;
        };
        switch(data.status_petrify(id))
        {
        case -2: status_effects->addItem(tr("Protect:Petrify")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Petrify")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Petrify")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Petrify")); show=true; y+=18;break;
        };
        switch(data.status_silence(id))
        {
        case -2: status_effects->addItem(tr("Protect:Silence")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Silence")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Silence")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Silence")); show=true; y+=18;break;
        };
        switch(data.status_sleep(id))
        {
        case -2: status_effects->addItem(tr("Protect:Sleep")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Sleep")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Sleep")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Sleep")); show=true; y+=18;break;
        };
        switch(data.status_confusion(id))
        {
        case -2: status_effects->addItem(tr("Protect:Confusion")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Confusion")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Confusion")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Confusion")); show=true; y+=18;break;
        };
        switch(data.status_berserk(id))
        {
        case -2: status_effects->addItem(tr("Protect:Berserk")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Berserk")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Berserk")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Berserk")); show=true; y+=18;break;
        };
        switch(data.status_frog(id))
        {
        case -2: status_effects->addItem(tr("Protect:Frog")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Frog")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Frog")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Frog")); show=true; y+=18;break;
        };
        switch(data.status_mini(id))
        {
        case -2: status_effects->addItem(tr("Protect:Mini")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Mini")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Mini")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Mini")); show=true; y+=18;break;
        };
        switch(data.status_poison(id))
        {
        case -2: status_effects->addItem(tr("Protect:Poison")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Poison")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Poison")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Poison")); show=true; y+=18;break;
        };
        switch(data.status_fury(id))
        {
        case -2: status_effects->addItem(tr("Protect:Fury")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Fury")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Fury")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Fury")); show=true; y+=18;break;
        };
        switch(data.status_sadness(id))
        {
        case -2: status_effects->addItem(tr("Protect:Sadness")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Sadness")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Sadness")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Sadness")); show=true; y+=18;break;
        };
        switch(data.status_darkness(id))
        {
        case -2: status_effects->addItem(tr("Protect:Darkness")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Darkness")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Darkness")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Darkness")); show=true; y+=18;break;
        };
        switch(data.status_haste(id))
        {
        case -2: status_effects->addItem(tr("Protect:Haste")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Haste")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Haste")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Haste")); show=true; y+=18;break;
        };
        switch(data.status_slow(id))
        {
        case -2: status_effects->addItem(tr("Protect:Slow")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Slow")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Slow")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Slow")); show=true; y+=18;break;
        };
        switch(data.status_stop(id))
        {
        case -2: status_effects->addItem(tr("Protect:Stop")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Stop")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Stop")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Stop")); show=true; y+=18;break;
        };
        switch(data.status_barrier(id))
        {
        case -2: status_effects->addItem(tr("Protect:Barrier")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Barrier")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Barrier")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Barrier")); show=true; y+=18;break;
        };
        switch(data.status_m_barrier(id))
        {
        case -2: status_effects->addItem(tr("Protect:M.Barrier")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:M.Barrier")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:M.Barrier")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:M.Barrier")); show=true; y+=18;break;
        };
        switch(data.status_reflect(id))
        {
        case -2: status_effects->addItem(tr("Protect:Reflect")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Reflect")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Reflect")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Reflect")); show=true; y+=18;break;
        };
        switch(data.status_regen(id))
        {
        case -2: status_effects->addItem(tr("Protect:Regen")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Regen")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Regen")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Regen")); show=true; y+=18;break;
        };
        switch(data.status_shield(id))
        {
        case -2: status_effects->addItem(tr("Protect:Shield")); show=true; y+=18; break;
        case -1: status_effects->addItem(tr("Remove:Shield")); show=true; y+=18; break;
        case  0: break;
        case +1: status_effects->addItem(tr("Inflict:Shield")); show=true; y+=18; break;
        case +2: status_effects->addItem(tr("OnBattle:Shield")); show=true; y+=18;break;
        };
        if(y<=100){status_box->setFixedSize(160,y);}
        else{status_box->setFixedSize(160,100);}
    }
    status_box->setVisible(show);
}
