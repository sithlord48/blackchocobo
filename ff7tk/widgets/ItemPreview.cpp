/****************************************************************************/
//    copyright 2012 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
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

bool ItemPreview::eventFilter(QObject *obj, QEvent *ev)
{
	if(obj != this->parent() && (obj != this)){this->close();return true;}
	else if(ev->type()==QEvent::MouseButtonPress || ev->type() == QEvent::Leave){this->close();return true;}
	else{return event(ev);}

}
ItemPreview::ItemPreview(QFlags<Qt::WindowType> WindowFlags, qreal Scale,QWidget *parent) :QWidget(parent)
{
  setWindowFlags(WindowFlags);
  scale = Scale;
  Qt::WindowFlags WidgetType =(this->windowFlags() & Qt::WindowType_Mask);
  if(WidgetType ==Qt::Popup || WidgetType ==Qt::ToolTip)
  {// if popup or tooltip install the eventFilter
	  installEventFilter(this);
   }
  _id=FF7Item::EmptyItem;
  lbl_name=new QLabel();
  lbl_desc=new QLabel();
  lbl_icon=new QLabel();
  lbl_icon->setFixedSize(24*scale,24*scale);
  QSpacerItem *spacer=new QSpacerItem(-1,-1,QSizePolicy::Expanding,QSizePolicy::Minimum);
  lbl_slot_1= new QLabel();
  lbl_slot_1->setFixedSize(24*scale,24*scale);
  lbl_slot_1->setHidden(true);

  lbl_m_link_1= new QLabel();
  lbl_m_link_1->setFixedSize(12*scale,24*scale);

  lbl_slot_2 = new QLabel();
  lbl_slot_2->setFixedSize(24*scale,24*scale);
  lbl_slot_2->setHidden(true);

  QHBoxLayout *slots_1_and_2 = new QHBoxLayout();
  slots_1_and_2->setContentsMargins(0,0,0,0);
  slots_1_and_2->addWidget(lbl_slot_2);
  slots_1_and_2->addWidget(lbl_m_link_1);
  slots_1_and_2->addWidget(lbl_slot_1);
  slots_1_and_2->setSpacing(0);

  lbl_slot_3 = new QLabel();
  lbl_slot_3->setFixedSize(24*scale,24*scale);
  lbl_slot_3->setHidden(true);

  lbl_m_link_2 = new QLabel();
  lbl_m_link_2->setFixedSize(12*scale,24*scale);

  lbl_slot_4 = new QLabel();
  lbl_slot_4->setFixedSize(24*scale,24*scale);
  lbl_slot_4->setHidden(true);

  QHBoxLayout *slots_3_and_4 = new QHBoxLayout();
  slots_3_and_4->setContentsMargins(0,0,0,0);
  slots_3_and_4->addWidget(lbl_slot_4);
  slots_3_and_4->addWidget(lbl_m_link_2);
  slots_3_and_4->addWidget(lbl_slot_3);
  slots_3_and_4->setSpacing(0);

  lbl_slot_5 = new QLabel();
  lbl_slot_5->setFixedSize(24*scale,24*scale);
  lbl_slot_5->setHidden(true);

  lbl_m_link_3 = new QLabel();
  lbl_m_link_3->setFixedSize(12*scale,24*scale);

  lbl_slot_6 = new QLabel();
  lbl_slot_6->setFixedSize(24*scale,24*scale);
  lbl_slot_6->setHidden(true);

  QHBoxLayout *slots_5_and_6 = new QHBoxLayout();
  slots_5_and_6->setContentsMargins(0,0,0,0);
  slots_5_and_6->addWidget(lbl_slot_6);
  slots_5_and_6->addWidget(lbl_m_link_3);
  slots_5_and_6->addWidget(lbl_slot_5);
  slots_5_and_6->setSpacing(0);

  lbl_slot_7 = new QLabel();
  lbl_slot_7->setFixedSize(24*scale,24*scale);
  lbl_slot_7->setHidden(true);

  lbl_m_link_4 = new QLabel();
  lbl_m_link_4->setFixedSize(12*scale,24*scale);

  lbl_slot_8 = new QLabel();
  lbl_slot_8->setFixedSize(24*scale,24*scale);
  lbl_slot_8->setHidden(true);

  QHBoxLayout *slots_7_and_8 = new QHBoxLayout();
  slots_7_and_8->setContentsMargins(0,0,0,0);
  slots_7_and_8->addWidget(lbl_slot_8);
  slots_7_and_8->addWidget(lbl_m_link_4);
  slots_7_and_8->addWidget(lbl_slot_7);
  slots_7_and_8->setSpacing(0);

  materia_slot_box = new QGroupBox();
  materia_slot_box->setContentsMargins(0,0,0,0);
  materia_slot_box->setFixedSize(320*scale,48*scale);

  QHBoxLayout *materia_slots = new QHBoxLayout();
  materia_slots->setContentsMargins(0,0,0,0);
  materia_slots->addLayout(slots_1_and_2);
  materia_slots->addLayout(slots_3_and_4);
  materia_slots->addLayout(slots_5_and_6);
  materia_slots->addLayout(slots_7_and_8);
  materia_slots->addSpacerItem(spacer);
  materia_slots->setSpacing(12);

  materia_slot_box->setLayout(materia_slots);
  materia_slot_box->setHidden(true);

  elemental_effects = new QListWidget();
  QHBoxLayout *elemental = new QHBoxLayout();
  elemental->setContentsMargins(0,0,0,0);
  elemental->addWidget(elemental_effects);

  elemental_box =new QGroupBox();
  elemental_box->setContentsMargins(3,3,3,3);
  elemental_box->setLayout(elemental);
  elemental_box->setTitle(tr("Elemental Effects"));
  elemental_box->setHidden(true);

  status_effects = new QListWidget();
  QHBoxLayout *status =new QHBoxLayout();
  status->setContentsMargins(0,0,0,0);
  status->addWidget(status_effects);

  status_box = new QGroupBox();
  status_box->setContentsMargins(3,3,3,3);
  status_box->setLayout(status);
  status_box->setTitle(tr("Status Effects"));
  status_box->setHidden(true);

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
}
void ItemPreview::setName(QString text){lbl_name->setText(text);lbl_name->adjustSize();}
void ItemPreview::setDesc(QString text){lbl_desc->setText(text);lbl_desc->adjustSize();}
void ItemPreview::setIcon(QPixmap picture){lbl_icon->setPixmap(picture.scaled(lbl_icon->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));lbl_icon->adjustSize();}

void ItemPreview::setItem(quint16 itemraw)
{//see FF7Save::itemDecode(quint16) for proper comments.
	quint16 item;
	int one = 1;
	if (*(char *)&one){item=itemraw;}
	else{item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);}
	int id = (item & 0x1FF);
	setItem(id);
}
void ItemPreview::setItem(int id)
{
	lbl_slot_8->setHidden(true);
	lbl_slot_7->setHidden(true);
	lbl_slot_6->setHidden(true);
	lbl_slot_5->setHidden(true);
	lbl_slot_4->setHidden(true);
	lbl_slot_3->setHidden(true);
	lbl_slot_2->setHidden(true);
	lbl_slot_1->setHidden(true);

	lbl_m_link_1->setPixmap(QPixmap());
	lbl_m_link_2->setPixmap(QPixmap());
	lbl_m_link_3->setPixmap(QPixmap());
	lbl_m_link_4->setPixmap(QPixmap());

	materia_slot_box->setHidden(true);
	lbl_desc->setHidden(true);
	lbl_name->setHidden(true);
	lbl_icon->setHidden(true);
	status_box->setHidden(true);
	elemental_box->setHidden(true);

	if(id<0 || id>319){_id=FF7Item::EmptyItem;/*InValid Number..Do Nothing*/}
	else
	{
		_id=id;
		if(data.name(id) !="")
		{
			lbl_name->setHidden(false);
			setName(data.name(id));
		}

		if(data.desc(id)!="")
		{
			setDesc(data.desc(id));
			lbl_desc->setHidden(false);
		}
		if(!data.image(id).isNull())
		{
			lbl_icon->setHidden(false);
			setIcon(QPixmap::fromImage(data.image(id)));
		}
		this->status_info(id);
		this->elemental_info(id);

		if(data.type(id)>FF7Item::Item && data.type(id)!=FF7Item::Accessory)
		{
			if(data.materiaGrowthRate(id)==0)
			{//no growth slots
                lbl_slot_1->setPixmap(QPixmap::fromImage(data.imageMateriaSlotNoGrowth()).scaled(lbl_slot_1->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_2->setPixmap(QPixmap::fromImage(data.imageMateriaSlotNoGrowth()).scaled(lbl_slot_2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_3->setPixmap(QPixmap::fromImage(data.imageMateriaSlotNoGrowth()).scaled(lbl_slot_3->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_4->setPixmap(QPixmap::fromImage(data.imageMateriaSlotNoGrowth()).scaled(lbl_slot_4->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_5->setPixmap(QPixmap::fromImage(data.imageMateriaSlotNoGrowth()).scaled(lbl_slot_5->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_6->setPixmap(QPixmap::fromImage(data.imageMateriaSlotNoGrowth()).scaled(lbl_slot_6->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_7->setPixmap(QPixmap::fromImage(data.imageMateriaSlotNoGrowth()).scaled(lbl_slot_7->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_8->setPixmap(QPixmap::fromImage(data.imageMateriaSlotNoGrowth()).scaled(lbl_slot_8->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			}
			else
			{//growth slots.
                lbl_slot_1->setPixmap(QPixmap::fromImage(data.imageMateriaSlot()).scaled(lbl_slot_1->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_2->setPixmap(QPixmap::fromImage(data.imageMateriaSlot()).scaled(lbl_slot_2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_3->setPixmap(QPixmap::fromImage(data.imageMateriaSlot()).scaled(lbl_slot_3->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_4->setPixmap(QPixmap::fromImage(data.imageMateriaSlot()).scaled(lbl_slot_4->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_5->setPixmap(QPixmap::fromImage(data.imageMateriaSlot()).scaled(lbl_slot_5->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_6->setPixmap(QPixmap::fromImage(data.imageMateriaSlot()).scaled(lbl_slot_6->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_7->setPixmap(QPixmap::fromImage(data.imageMateriaSlot()).scaled(lbl_slot_7->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                lbl_slot_8->setPixmap(QPixmap::fromImage(data.imageMateriaSlot()).scaled(lbl_slot_8->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			}
			QString ap_rate =tr("APx%1").arg(data.materiaGrowthRate(id));
			materia_slot_box->setTitle(ap_rate);
			materia_slot_box->setHidden(false);
			switch(data.materiaSlots(id))
			{
				case 8:lbl_slot_8->setHidden(false);
				case 7:lbl_slot_7->setHidden(false);
				case 6:lbl_slot_6->setHidden(false);
				case 5:lbl_slot_5->setHidden(false);
				case 4:lbl_slot_4->setHidden(false);
				case 3:lbl_slot_3->setHidden(false);
				case 2:lbl_slot_2->setHidden(false);
				case 1:lbl_slot_1->setHidden(false);
			};

			switch(data.linkedSlots(id))
			{

                case 4: lbl_m_link_4->setPixmap(QPixmap::fromImage(data.imageMateriaLink()).scaled(lbl_m_link_4->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                case 3: lbl_m_link_3->setPixmap(QPixmap::fromImage(data.imageMateriaLink()).scaled(lbl_m_link_3->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                case 2: lbl_m_link_2->setPixmap(QPixmap::fromImage(data.imageMateriaLink()).scaled(lbl_m_link_2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                case 1: lbl_m_link_1->setPixmap(QPixmap::fromImage(data.imageMateriaLink()).scaled(lbl_m_link_1->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			};
		}
	}
	this->adjustSize();
}
void ItemPreview::elemental_info(int id)
{
	int y= elemental_effects->contentsMargins().top() +elemental_effects->contentsMargins().bottom();
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
				case 0: element=data.elementRestoration(id); effect.append(tr("Restoration"));break;
				case 1: element=data.elementFire(id); effect.append(tr("Fire")); break;
				case 2: element=data.elementCold(id); effect.append(tr("Cold")); break;
				case 3: element=data.elementLightning(id); effect.append(tr("Lightning")); break;
				case 4: element=data.elementEarth(id); effect.append(tr("Earth")); break;
				case 5: element=data.elementWind(id); effect.append(tr("Wind")); break;
				case 6: element=data.elementWater(id); effect.append(tr("Water")); break;
				case 7: element=data.elementGravity(id); effect.append(tr("Gravity")); break;
				case 8: element=data.elementHoly(id); effect.append(tr("Holy")); break;
				case 9: element=data.elementPoison(id); effect.append(tr("Poison")); break;
				case 10: element=data.elementCut(id); effect.append(tr("Cut")); break;
				case 11: element=data.elementShoot(id); effect.append(tr("Shoot")); break;
				case 12: element=data.elementPunch(id); effect.append(tr("Punch")); break;
				case 13: element=data.elementHit(id); effect.append(tr("Hit")); break;
			}
			switch(element)
			{
				case FF7Item::Absorb: effect.prepend(tr("Absorb:"));break;
				case FF7Item::Nullify: effect.prepend(tr("Nullify:"));break;
				case FF7Item::Halve: effect.prepend(tr("Halve:"));break;
				case FF7Item::NoEffect: effect.clear();break;
				case FF7Item::Damage: effect.prepend(tr("Attack:"));break;
			}
			if(!effect.isNull())
			{
				elemental_effects->addItem(effect);
				show=true; y+= elemental_effects->sizeHintForRow(0);

			}
		}//end of for Loop
		Qt::WindowFlags WidgetType =(this->windowFlags() & Qt::WindowType_Mask);
		if(WidgetType !=Qt::Popup && WidgetType !=Qt::ToolTip)
		{//make the combo box smaller if not a popup or tooltip
			if(elemental_effects->count() <6)
			{
				//elemental_effects->setFixedHeight(y);
				elemental_box->setFixedSize(160*scale,elemental_effects->height()+elemental_box->contentsMargins().top()+elemental_box->contentsMargins().bottom());
				//elemental_box->setFixedSize(160,y+elemental_box->contentsMargins().top()+elemental_box->contentsMargins().bottom());
			}
			else{elemental_box->setFixedSize(160*scale,elemental_effects->sizeHintForRow(0)*5 +elemental_box->contentsMargins().top()+elemental_box->contentsMargins().bottom());}
		}
		else
		{
			elemental_box->setFixedSize(160*scale,y + elemental_box->contentsMargins().top() +elemental_box->contentsMargins().bottom());
		}}//end of else
   elemental_box->setVisible(show);
   elemental_box->adjustSize();
}//end of function

void ItemPreview::status_info(int id)
{
	int y=status_effects->contentsMargins().top()+ status_effects->contentsMargins().bottom();
	bool show=false;
	status_effects->clear();
	if(id<0 || id>319){/*invalid number*/}
	else
	{
		for(int i=0;i<24;i++)
		{
			QString effect;
			int status=0;
			switch(i)
			{
				case 0: status=data.statusDeath(id); effect.append(tr("Death"));break;
				case 1: status=data.statusSlowNumb(id); effect.append(tr("Slow-Numb"));break;
				case 2: status=data.statusDeathSentence(id); effect.append(tr("D.Sentence"));break;
				case 3: status=data.statusParalysis(id); effect.append(tr("Paralysis"));break;
				case 4: status=data.statusPetrify(id); effect.append(tr("Petrify"));break;
				case 5: status=data.statusSilence(id); effect.append(tr("Silence"));break;
				case 6: status=data.statusSleep(id); effect.append(tr("Sleep"));break;
				case 7: status=data.statusConfusion(id); effect.append(tr("Confusion"));break;
				case 8: status=data.statusBerserk(id); effect.append(tr("Berserk"));break;
				case 9: status=data.statusFrog(id); effect.append(tr("Frog"));break;
				case 10: status=data.statusMini(id); effect.append(tr("Mini"));break;
				case 11: status=data.statusPoison(id); effect.append(tr("Poison"));break;
				case 12: status=data.statusFury(id); effect.append(tr("Fury"));break;
				case 13: status=data.statusSadness(id); effect.append(tr("Sadness"));break;
				case 14: status=data.statusDarkness(id); effect.append(tr("Darkness"));break;
				case 15: status=data.statusHaste(id); effect.append(tr("Haste"));break;
				case 16: status=data.statusSlow(id); effect.append(tr("Slow"));break;
				case 17: status=data.statusStop(id); effect.append(tr("Stop"));break;
				case 18: status=data.statusBarrier(id); effect.append(tr("Barrier"));break;
				case 19: status=data.statusMagicBarrier(id); effect.append(tr("M.Barrier"));break;
				case 20: status=data.statusReflect(id); effect.append(tr("Reflect"));break;
				case 21: status=data.statusShield(id); effect.append(tr("Shield"));break;
				case 22: status=data.statusRegen(id); effect.append(tr("Regen"));break;
				case 23:status=data.statusResist(id); effect.append(tr("Resist"));break;
			}
			switch(status)
			{
				case FF7Item::Protect: effect.prepend(tr("Protect:")); break;
				case FF7Item::Remove: effect.prepend(tr("Remove:")); break;
				case  FF7Item::NoEffect: effect.clear();break;
				case FF7Item::Infilict: effect.prepend(tr("Inflict:")); break;
				case FF7Item::SelfCast: effect.prepend(tr("OnBattle:"));break;
			}
			if(!effect.isNull())
			{
				status_effects->addItem(effect);
				show=true; y+=status_effects->sizeHintForRow(0);
			}
		}//end of for Loop
		Qt::WindowFlags WidgetType =(this->windowFlags() & Qt::WindowType_Mask);
		if(WidgetType !=Qt::Popup && WidgetType !=Qt::ToolTip)
		{//make the combo box smaller if not a popup or tooltip
			if(status_effects->count()<6)
			{
				status_box->setFixedSize(160*scale,y+status_box->contentsMargins().top()+status_box->contentsMargins().bottom());
			}
			else{status_box->setFixedSize(160*scale,status_effects->sizeHintForRow(0)*5 +status_box->contentsMargins().top()+status_box->contentsMargins().bottom());}
		}
		else{status_box->setFixedSize(160*scale,y+status_box->contentsMargins().top()+status_box->contentsMargins().bottom());}
	}//end of else
	status_box->setVisible(show);
	status_box->adjustSize();
}//end of function
int ItemPreview::id(void){return _id;}
