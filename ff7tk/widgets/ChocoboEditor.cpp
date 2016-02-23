/****************************************************************************/
//	copyright 2012 -2016  Chris Rizzitello <sithlord48@gmail.com>		 //
//																		  //
//	This file is part of FF7tk											//
//																		  //
//	FF7tk is free software: you can redistribute it and/or modify		 //
//	it under the terms of the GNU General Public License as published by  //
//	the Free Software Foundation, either version 3 of the License, or	 //
//	(at your option) any later version.								   //
//																		  //
//	FF7tk is distributed in the hope that it will be useful,			  //
//	but WITHOUT ANY WARRANTY; without even the implied warranty of		//
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the		  //
//	GNU General Public License for more details.						  //
/****************************************************************************/
#include "ChocoboEditor.h"
// Pull in Icons, Be Sure Paths Are Correct

void ChocoboEditor::resizeEvent(QResizeEvent *ev)
{
	if(ev->type()==QEvent::Resize)
	{
		Final->setColumnMinimumWidth(0,width()/4);
		Final->setColumnMinimumWidth(1,width()/4);
		Final->setColumnStretch(0,width()/4);
		Final->setColumnStretch(1,width()/4);
	}
}
ChocoboEditor::ChocoboEditor(QWidget *parent) :
	QWidget(parent)
{
	init_display();
	init_connections();
}
//Simple Data Return Functions.
quint16 ChocoboEditor::sprint(void){return choco_data.sprintspd;}
quint16 ChocoboEditor::mSprint(void){return choco_data.maxsprintspd;}
quint16 ChocoboEditor::speed(void){return choco_data.speed;}
quint16 ChocoboEditor::mSpeed(void){return choco_data.maxspeed;}
quint16 ChocoboEditor::stamina(void){return choco_stamina;}
bool ChocoboEditor::cantMate(void){return choco_cant_mate;}
QString ChocoboEditor::name(void){return choco_name;}
quint8 ChocoboEditor::accel(void){return choco_data.accel;}
quint8 ChocoboEditor::coop(void){return choco_data.coop;}
quint8 ChocoboEditor::intelligence(void){return choco_data.intelligence;}
quint8 ChocoboEditor::personality(void){return choco_data.personality;}
quint8 ChocoboEditor::pCount(void){return choco_data.pcount;}
quint8 ChocoboEditor::wins(void){return choco_data.raceswon;}
quint8 ChocoboEditor::sex(void){return choco_data.sex;}
quint8 ChocoboEditor::type(void){return choco_data.type;}
quint8 ChocoboEditor::rating(void){return choco_rating;}

//Data Set Functions.
void ChocoboEditor::setRating(int rating)
{
	if(rating <0){rating=0;}
	else if (rating>8){rating=8;}
	combo_rating->setCurrentIndex(rating);
	choco_rating=rating;
}
void ChocoboEditor::setSprint(int sprint_speed)
{
	if(sprint_speed <0){sprint_speed =0;}
	else if (sprint_speed > 9999){sprint_speed = 9999;}
	sb_sprint->setValue(sprint_speed);
	choco_data.sprintspd = sprint_speed;
}
void ChocoboEditor::setMsprint(int max_sprint_speed)
{
	if(max_sprint_speed <0){max_sprint_speed =0;}
	else if (max_sprint_speed > 9999){max_sprint_speed = 9999;}
	sb_mSprint->setValue(max_sprint_speed);
	choco_data.maxsprintspd = max_sprint_speed;
}
void ChocoboEditor::setSpeed(int speed)
{
	if(speed <0){speed =0;}
	else if (speed > 9999){speed = 9999;}
	sb_speed->setValue(speed);
	choco_data.speed = speed;
}
void ChocoboEditor::setMspeed(int max_speed)
{
	if(max_speed <0){max_speed =0;}
	else if (max_speed > 9999){max_speed = 9999;}
	sb_mSpeed->setValue(max_speed);
	choco_data.maxspeed = max_speed;
}
void ChocoboEditor::setStamina(int stamina)
{
	if(stamina <0){stamina =0;}
	else if (stamina > 9999){stamina = 9999;}
	sb_stamina->setValue(stamina);
	choco_stamina = stamina;
}
void ChocoboEditor::setAccel(int accel)
{
	if(accel <0){accel =0;}
	else if (accel > 255){accel =255;}
	sb_accel->setValue(accel);
	choco_data.accel = accel;
}
void ChocoboEditor::setCoop(int coop)
{
	if(coop < 0){coop =0;}
	else if (coop >255){coop =255;}
	sb_coop->setValue(coop);
	choco_data.coop = coop;
}
void ChocoboEditor::setIntelligence(int intel)
{
	if(intel <0){intel =0;}
	else if(intel >255){intel = 255;}
	sb_intel->setValue(intel);
	choco_data.intelligence = intel;
}
void ChocoboEditor::setPersonality (int personality)
{//need to be researched further.
	if(personality <0){personality =0;}
	else if (personality >255){personality = 255;}
	sb_personality->setValue(personality);
	choco_data.personality = personality;
}
void ChocoboEditor::setPcount(int pCount)
{
	if(pCount <0){pCount =0;}
	else if (pCount >255){pCount =255;}
	sb_pCount->setValue(pCount);
	choco_data.pcount=pCount;
}
void ChocoboEditor::setWins(int wins)
{
	if(wins <0){wins = 0;}
	else if (wins>255){wins = 255;}
	sb_wins->setValue(wins);
	choco_data.raceswon = wins;
	getRank();
}
void ChocoboEditor::setSex(int sex)
{
	if(sex<0){sex=0;}
	else if(sex > 1){sex = 1;}
	combo_sex->setCurrentIndex(sex);
	choco_data.sex = sex;
}
void ChocoboEditor::setType(int type)
{
	if(type<0){type=0;}
	else if(type > 4){type = 4;}
	combo_type->setCurrentIndex(type);
	choco_data.type = type;
}
void ChocoboEditor::setName(QString new_name)
{
	choco_name=new_name.mid(0,6);
	if(choco_name =="\xff\xff\xff\xff\xff\xff"){line_name->setText("");}
	else{line_name->setText(choco_name);}
}
void ChocoboEditor::setCantMate(bool cantMate)
{
	cb_cantMate->setChecked(cantMate);
	choco_cant_mate=cantMate;
}

//Same again but with the emits..
void ChocoboEditor::RatingChanged(int rating)
{
	choco_rating=rating;
	emit ratingChanged(choco_rating);
}
void ChocoboEditor::SprintChanged(int sprint_speed)
{
	choco_data.sprintspd = sprint_speed;
	emit sprintChanged(choco_data.sprintspd);
}
void ChocoboEditor::MsprintChanged(int max_sprint_speed)
{
	choco_data.maxsprintspd = max_sprint_speed;
	emit mSprintChanged(choco_data.maxsprintspd);
}
void ChocoboEditor::SpeedChanged(int speed)
{
	choco_data.speed = speed;
	emit speedChanged(choco_data.speed);
}
void ChocoboEditor::MspeedChanged(int max_speed)
{
	choco_data.maxspeed = max_speed;
	emit mSpeedChanged(choco_data.maxspeed);
}
void ChocoboEditor::StaminaChanged(int stamina)
{
	choco_stamina = stamina;
	emit staminaChanged(choco_stamina);
}
void ChocoboEditor::AccelChanged(int accel)
{
	choco_data.accel = accel;
	emit accelChanged(choco_data.accel);
}
void ChocoboEditor::CoopChanged(int coop)
{
	choco_data.coop = coop;
	emit coopChanged(choco_data.coop);
}
void ChocoboEditor::IntelligenceChanged(int intel)
{
	choco_data.intelligence = intel;
	emit intelligenceChanged(choco_data.intelligence);
}
void ChocoboEditor::PersonalityChanged (int personality)
{//need to be researched further.
	choco_data.personality = personality;
	emit personalityChanged(choco_data.personality);
}
void ChocoboEditor::PcountChanged(int pCount)
{
	choco_data.pcount=pCount;
	emit pCountChanged(choco_data.pcount);
}
void ChocoboEditor::WinsChanged(int wins)
{
	choco_data.raceswon = wins;
	getRank();
	emit winsChanged(choco_data.raceswon);
}
void ChocoboEditor::SexChanged(int sex)
{
	choco_data.sex = sex;
	emit sexChanged(choco_data.sex);
}
void ChocoboEditor::TypeChanged(int type)
{
	choco_data.type = type;
	emit typeChanged(choco_data.type);
}
void ChocoboEditor::NameChanged(QString new_name)
{
	if(new_name !=choco_name)
	{
		choco_name=new_name.mid(0,6);
		emit nameChanged(new_name);
	}
}
void ChocoboEditor::CantMateChanged(bool cantMate)
{
	choco_cant_mate=cantMate;
	emit cantMateChanged(choco_cant_mate);
}
void ChocoboEditor::init_display(void)
{
	//create Gui Widgets.
	combo_sex = new QComboBox;
	combo_type = new QComboBox;
	line_name = new QLineEdit;
	sb_speed = new QSpinBox;
	sb_mSpeed = new QSpinBox;
	sb_sprint = new QSpinBox;
	sb_mSprint = new QSpinBox;
	sb_stamina = new QSpinBox;
	sb_accel = new QSpinBox;
	sb_wins = new QSpinBox;
	sb_coop = new QSpinBox;
	sb_pCount = new QSpinBox;
	sb_intel = new QSpinBox;
	sb_personality = new QSpinBox;
	cb_cantMate = new QCheckBox(tr("Unable To Mate"));

	lbl_rank = new QLabel();
	lbl_stamina  = new QLabel(tr("Stamina"));
	lbl_speed = new QLabel(tr("Run Speed"));
	lbl_div_speed = new QLabel("/");
	lbl_div_speed->setAlignment(Qt::AlignHCenter);
	lbl_div_speed->setMaximumWidth(font().pointSize());
	lbl_sprint = new QLabel(tr("Sprint Speed"));
	lbl_div_sprint = new QLabel("/");
	lbl_div_sprint->setAlignment(Qt::AlignHCenter);
	lbl_div_sprint->setMaximumWidth(font().pointSize());
	lbl_accel = new QLabel(tr("Acceleration"));
	lbl_wins = new QLabel(tr("Races Won"));
	lbl_coop = new QLabel(tr("Cooperation"));
	lbl_pCount = new QLabel(tr("pCount"));
	lbl_intel = new QLabel(tr("Intelligence"));
	lbl_personality = new QLabel(tr("Personality"));
	lbl_rating = new QLabel(tr("Choco Billy's Rating: "));
	//Set Widgets up
	line_name->setMaxLength(6);
	line_name->setPlaceholderText(tr("Name"));
	sb_speed->setMaximum(9999);
	sb_speed->setAlignment(Qt::AlignHCenter);
	sb_mSpeed->setMaximum(9999);
	sb_mSpeed->setAlignment(Qt::AlignHCenter);
	sb_sprint->setMaximum(9999);
	sb_sprint->setAlignment(Qt::AlignHCenter);
	sb_mSprint->setMaximum(9999);
	sb_mSprint->setAlignment(Qt::AlignHCenter);
	sb_stamina->setMaximum(9999);
	sb_stamina->setAlignment(Qt::AlignHCenter);
	sb_coop->setMaximum(255);
	sb_coop->setAlignment(Qt::AlignHCenter);
	sb_accel->setMaximum(255);
	sb_accel->setAlignment(Qt::AlignHCenter);
	sb_wins->setMaximum(255);
	sb_wins->setAlignment(Qt::AlignHCenter);
	sb_pCount->setMaximum(255);
	sb_pCount->setAlignment(Qt::AlignHCenter);
	sb_intel->setMaximum(255);
	sb_intel->setAlignment(Qt::AlignHCenter);
	sb_personality->setMaximum(255);
	sb_personality->setAlignment(Qt::AlignHCenter);
	sb_speed->setWrapping(true);
	sb_mSpeed->setWrapping(true);
	sb_sprint->setWrapping(true);
	sb_mSprint->setWrapping(true);
	sb_stamina->setWrapping(true);
	sb_coop->setWrapping(true);
	sb_accel->setWrapping(true);
	sb_wins->setWrapping(true);
	sb_pCount->setWrapping(true);
	sb_intel->setWrapping(true);
	sb_personality->setWrapping(true);

	QStringList typeList;
	typeList.append(tr("Empty"));
	typeList.append(tr("Wonderful"));
	typeList.append(tr("Great"));
	typeList.append(tr("Good"));
	typeList.append(tr("Fair"));
	typeList.append(tr("Average"));
	typeList.append(tr("Poor"));
	typeList.append(tr("Bad"));
	typeList.append(tr("Terrible"));

	//Fill Combos.
	combo_sex->addItem(tr("Male %1").arg(QString::fromUtf8("♂")));
	combo_sex->addItem(tr("Female %1").arg(QString::fromUtf8("♀")));

	combo_type->addItem(QIcon(QPixmap(":/chocobo/yellow")),tr("Yellow"));
	combo_type->addItem(QIcon(QPixmap(":/chocobo/green")),tr("Green"));
	combo_type->addItem(QIcon(QPixmap(":/chocobo/blue")),tr("Blue"));
	combo_type->addItem(QIcon(QPixmap(":/chocobo/black")),tr("Black"));
	combo_type->addItem(QIcon(QPixmap(":/chocobo/gold")),tr("Gold"));

	combo_rating = new QComboBox;
	combo_rating->addItems(typeList);


	//Make Layouts

	QHBoxLayout *speed_layout = new QHBoxLayout;
	speed_layout->addWidget(lbl_speed);
	speed_layout->addWidget(sb_speed);
	speed_layout->addWidget(lbl_div_speed);
	speed_layout->addWidget(sb_mSpeed);

	QHBoxLayout *sprint_layout = new QHBoxLayout;
	sprint_layout->addWidget(lbl_sprint);
	sprint_layout->addWidget(sb_sprint);
	sprint_layout->addWidget(lbl_div_sprint);
	sprint_layout->addWidget(sb_mSprint);

	QHBoxLayout *accel_layout = new QHBoxLayout;
	accel_layout->addWidget(lbl_accel);
	accel_layout->addWidget(sb_accel);

	QHBoxLayout *stamina_layout = new QHBoxLayout;
	stamina_layout->addWidget(lbl_stamina);
	stamina_layout->addWidget(sb_stamina);

	QHBoxLayout *wins_layout = new QHBoxLayout;
	wins_layout->addWidget(lbl_wins);
	wins_layout->addWidget(sb_wins);

	QHBoxLayout *coop_layout = new QHBoxLayout;
	coop_layout->addWidget(lbl_coop);
	coop_layout->addWidget(sb_coop);

	QHBoxLayout *intel_layout = new QHBoxLayout;
	intel_layout->addWidget(lbl_intel);
	intel_layout->addWidget(sb_intel);

	QHBoxLayout *pCount_layout = new QHBoxLayout;
	pCount_layout->addWidget(lbl_pCount);
	pCount_layout->addWidget(sb_pCount);

	QHBoxLayout *personality_layout = new QHBoxLayout;
	personality_layout->addWidget(lbl_personality);
	personality_layout->addWidget(sb_personality);

	QHBoxLayout *pCount_personality_layout = new QHBoxLayout;
	pCount_personality_layout->addLayout(pCount_layout);
	pCount_personality_layout->addLayout(personality_layout);

	QHBoxLayout *ratingLayout=new QHBoxLayout;
	ratingLayout->addWidget(lbl_rating);
	ratingLayout->addWidget(combo_rating);

	lblSpeedWarning = new QLabel(tr("Speed Values Are The Raw Values\nThe km/h speeds are calculated while playing "));
	advancedModeBox = new QFrame;
	advancedModeBox->setStyleSheet("QFrame:enabled{background-color: rgba(0,0,0,0);}");
	advancedModeBox->setLayout(pCount_personality_layout);
	advancedModeBox->setHidden(true);

	Final = new QGridLayout;
	Final->setContentsMargins(0,0,0,0);
	Final->setAlignment(Qt::AlignCenter);
	Final->setColumnMinimumWidth(0,width()/4);
	Final->setColumnMinimumWidth(1,width()/4);
	Final->setColumnStretch(0,width()/4);
	Final->setColumnStretch(1,width()/4);

	Final->addWidget(line_name,0,0);
	Final->addWidget(combo_sex,0,1);
	Final->addWidget(lbl_rank,2,0);
	Final->addWidget(combo_type,1,0);
	Final->addWidget(cb_cantMate,1,1);
	Final->addLayout(wins_layout,2,1);
	Final->addLayout(accel_layout,3,0);
	Final->addLayout(stamina_layout,3,1);
	Final->addLayout(coop_layout,4,0);
	Final->addLayout(intel_layout,4,1);
	Final->addLayout(speed_layout,5,0,1,2);
	Final->addLayout(sprint_layout,6,0,1,2);
	Final->addLayout(ratingLayout,7,0,1,2);
	Final->addWidget(lblSpeedWarning,9,0,2,2,Qt::AlignCenter);
	Final->addWidget(advancedModeBox,10,0,1,2);
	Final->addItem(new QSpacerItem(0,0,QSizePolicy::Preferred,QSizePolicy::Expanding),11,0,1,2);
	this->setLayout(Final);
}
void ChocoboEditor::init_connections(void)
{
	connect(combo_type,SIGNAL(currentIndexChanged(int)),this,SLOT(TypeChanged(int)));
	connect(combo_sex,SIGNAL(currentIndexChanged(int)),this,SLOT(SexChanged(int)));
	connect(combo_rating,SIGNAL(currentIndexChanged(int)),this,SLOT(RatingChanged(int)));
	connect(cb_cantMate,SIGNAL(toggled(bool)),this,SLOT(CantMateChanged(bool)));
	connect(line_name,SIGNAL(textChanged(QString)),this,SLOT(NameChanged(QString)));
	connect(sb_sprint,SIGNAL(valueChanged(int)),this,SLOT(SprintChanged(int)));
	connect(sb_mSprint,SIGNAL(valueChanged(int)),this,SLOT(MsprintChanged(int)));
	connect(sb_speed,SIGNAL(valueChanged(int)),this,SLOT(SpeedChanged(int)));
	connect(sb_mSpeed,SIGNAL(valueChanged(int)),this,SLOT(MspeedChanged(int)));
	connect(sb_stamina,SIGNAL(valueChanged(int)),this,SLOT(StaminaChanged(int)));
	connect(sb_accel,SIGNAL(valueChanged(int)),this,SLOT(AccelChanged(int)));
	connect(sb_coop,SIGNAL(valueChanged(int)),this,SLOT(CoopChanged(int)));
	connect(sb_intel,SIGNAL(valueChanged(int)),this,SLOT(IntelligenceChanged(int)));
	connect(sb_personality,SIGNAL(valueChanged(int)),this,SLOT(PersonalityChanged(int)));
	connect(sb_pCount,SIGNAL(valueChanged(int)),this,SLOT(PcountChanged(int)));
	connect(sb_wins,SIGNAL(valueChanged(int)),this,SLOT(WinsChanged(int)));
}
void ChocoboEditor::SetChocobo(FF7CHOCOBO choco, QString Processed_Name, bool cant_mate, quint16 stamina,quint8 rating)
{
	choco_data = choco;
	if(Processed_Name =="	  "){Processed_Name ="";}
	else if(Processed_Name =="\xff\xff\xff\xff\xff\xff"){Processed_Name ="";}
	choco_name = Processed_Name;
	choco_cant_mate = cant_mate;
	choco_stamina = stamina;
	choco_rating = rating;
	line_name->setText(choco_name);
	combo_type->setCurrentIndex(choco_data.type);
	combo_sex->setCurrentIndex(choco_data.sex);
	if(choco_cant_mate){cb_cantMate->setCheckState(Qt::Checked);}
	else{cb_cantMate->setCheckState(Qt::Unchecked);}
	sb_speed->setValue(choco_data.speed);
	sb_mSpeed->setValue(choco_data.maxspeed);
	sb_sprint->setValue(choco_data.sprintspd);
	sb_mSprint->setValue(choco_data.maxsprintspd);
	sb_stamina->setValue(choco_stamina);
	sb_accel->setValue(choco_data.accel);
	sb_wins->setValue(choco_data.raceswon);
	sb_pCount->setValue(choco_data.pcount);
	sb_coop->setValue(choco_data.coop);
	sb_intel->setValue(choco_data.intelligence);
	sb_personality->setValue(choco_data.personality);
	combo_rating->setCurrentIndex(choco_rating);
	getRank();
}
void ChocoboEditor::getRank(void)
{
	if(choco_data.raceswon <3){lbl_rank->setText(tr("Rank: C"));}
	else if(choco_data.raceswon<6){lbl_rank->setText(tr("Rank: B"));}
	else if(choco_data.raceswon<9){lbl_rank->setText(tr("Rank: A"));}
	else{lbl_rank->setText(tr("Rank: S"));}
}
void ChocoboEditor::setAdvancedMode(bool advancedMode){advancedModeBox->setHidden(!advancedMode);}

