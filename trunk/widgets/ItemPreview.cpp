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

#include "ItemPreview.h"

ItemPreview::ItemPreview(QWidget *parent) :QWidget(parent)
{
  lbl_name=new QLabel();
  lbl_desc=new QLabel();
  lbl_icon=new QLabel();
  lbl_icon->setFixedSize(24,24);
  lbl_icon->setScaledContents(1);
  QSpacerItem *spacer=new QSpacerItem(-1,-1,QSizePolicy::Expanding,QSizePolicy::Minimum);
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
  materia_slot_box->setFixedSize(320,48);

  QHBoxLayout *materia_slots = new QHBoxLayout();
  materia_slots->setContentsMargins(0,0,0,0);
  materia_slots->addSpacerItem(spacer);
  materia_slots->addLayout(slots_7_and_8);
  materia_slots->addLayout(slots_5_and_6);
  materia_slots->addLayout(slots_3_and_4);
  materia_slots->addLayout(slots_1_and_2);
  materia_slots->setSpacing(12);

  materia_slot_box->setLayout(materia_slots);
  materia_slot_box->setShown(0);

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
  QSpacerItem *spacer2 = new QSpacerItem(-1,-1,QSizePolicy::Expanding,QSizePolicy::Minimum);
  effects_layout->addSpacerItem(spacer2);
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
  this->adjustSize();
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
        for(int i=0;i<14;i++)
        {
            QString effect;
            int element=0;
            switch(i)
            {
                case 0: element=data.element_restoration(id); effect.append(tr("Restoration"));break;
                case 1: element=data.element_fire(id); effect.append(tr("Fire")); break;
                case 2: element=data.element_cold(id); effect.append(tr("Cold")); break;
                case 3: element=data.element_lightning(id); effect.append(tr("Lightning")); break;
                case 4: element=data.element_earth(id); effect.append(tr("Earth")); break;
                case 5: element=data.element_wind(id); effect.append(tr("Wind")); break;
                case 6: element=data.element_water(id); effect.append(tr("Water")); break;
                case 7: element=data.element_gravity(id); effect.append(tr("Gravity")); break;
                case 8: element=data.element_holy(id); effect.append(tr("Holy")); break;
                case 9: element=data.element_poison(id); effect.append(tr("Poison")); break;
                case 10: element=data.element_cut(id); effect.append(tr("Cut")); break;
                case 11: element=data.element_shoot(id); effect.append(tr("Shoot")); break;
                case 12: element=data.element_punch(id); effect.append(tr("Punch")); break;
                case 13: element=data.element_hit(id); effect.append(tr("Hit")); break;
            }
            switch(element)
            {
                case -3: effect.prepend(tr("Absorb:"));break;
                case -2: effect.prepend(tr("Nullify:"));break;
                case -1: effect.prepend(tr("Halve:"));break;
                case  0: effect.clear();break;
                case +1: effect.prepend(tr("Attack:"));break;
            }
            if(!effect.isNull())
            {
                elemental_effects->addItem(effect);
                show=true; y+=18;
            }
        }//end of for Loop
        if(y<=100){elemental_box->setFixedSize(160,y);}
        else{elemental_box->setFixedSize(160,100);}
   }//end of else
   elemental_box->setVisible(show);
   elemental_box->adjustSize();
}//end of function

void ItemPreview::status_info(int id)
{
    int y=20;
    bool show=false;
    status_effects->clear();
    if(id<0 || id>319){/*invalid number*/}
    else
    {
        for(int i=0;i<23;i++)
        {
            QString effect;
            int status=0;
            switch(i)
            {
                case 0: status=data.status_death(id); effect.append(tr("Death"));break;
                case 1: status=data.status_slow_numb(id); effect.append(tr("Slow-Numb"));break;
                case 2: status=data.status_d_sentence(id); effect.append(tr("D.Sentence"));break;
                case 3: status=data.status_paralysis(id); effect.append(tr("Paralysis"));break;
                case 4: status=data.status_petrify(id); effect.append(tr("Petrify"));break;
                case 5: status=data.status_silence(id); effect.append(tr("Silence"));break;
                case 6: status=data.status_sleep(id); effect.append(tr("Sleep"));break;
                case 7: status=data.status_confusion(id); effect.append(tr("Confusion"));break;
                case 8: status=data.status_berserk(id); effect.append(tr("Berserk"));break;
                case 9: status=data.status_frog(id); effect.append(tr("Frog"));break;
                case 10: status=data.status_mini(id); effect.append(tr("Mini"));break;
                case 11: status=data.status_poison(id); effect.append(tr("Poison"));break;
                case 12: status=data.status_fury(id); effect.append(tr("Fury"));break;
                case 13: status=data.status_sadness(id); effect.append(tr("Sadness"));break;
                case 14: status=data.status_darkness(id); effect.append(tr("Darkness"));break;
                case 15: status=data.status_haste(id); effect.append(tr("Haste"));break;
                case 16: status=data.status_slow(id); effect.append(tr("Slow"));break;
                case 17: status=data.status_stop(id); effect.append(tr("Stop"));break;
                case 18: status=data.status_barrier(id); effect.append(tr("Barrier"));break;
                case 19: status=data.status_m_barrier(id); effect.append(tr("M.Barrier"));break;
                case 20: status=data.status_reflect(id); effect.append(tr("Reflect"));break;
                case 21: status=data.status_shield(id); effect.append(tr("Shield"));break;
                case 22: status=data.status_regen(id); effect.append(tr("Regen"));break;
            }
            switch(status)
            {
                case -2: effect.prepend(tr("Protect:")); break;
                case -1: effect.prepend(tr("Remove:")); break;
                case  0: effect.clear();break;
                case +1: effect.prepend(tr("Inflict:")); break;
                case +2: effect.prepend(tr("OnBattle:"));break;
            }
            if(!effect.isNull())
            {
                status_effects->addItem(effect);
                show=true; y+=18;
            }
        }//end of for Loop
        if(y<=100){status_box->setFixedSize(160,y);}
        else{status_box->setFixedSize(160,100);}
    }//end of else
    status_box->setVisible(show);
    status_box->adjustSize();
}//end of function
