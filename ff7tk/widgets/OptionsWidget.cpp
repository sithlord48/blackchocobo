/****************************************************************************/
//    copyright 2013 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk.                                           //
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
#include "OptionsWidget.h"

OptionsWidget::OptionsWidget(QWidget *parent) :
	QScrollArea(parent)
{
	init_Display();
	init_Connections();
}

void OptionsWidget::init_Display()
{
	dialogBox = new QGroupBox;
	dialogPreview = new DialogPreview;
	QHBoxLayout *dialogLayout = new QHBoxLayout;
	dialogLayout->addWidget(dialogPreview);
	dialogLayout->setContentsMargins(0,0,0,0);
	dialogBox->setLayout(dialogLayout);
	dialogBox->setTitle(tr("In-Game Dialog Preview"));

	QLabel* lblAtb = new QLabel(tr("ATB Style"));
	lblAtb->setAlignment(Qt::AlignRight);
	comboAtb= new QComboBox;
	comboAtb->addItem(tr("Active"));
	comboAtb->addItem(tr("Recommended"));
	comboAtb->addItem(tr("Wait"));
	QHBoxLayout * atbLayout = new QHBoxLayout;
	atbLayout->addWidget(lblAtb);
	atbLayout->addWidget(comboAtb);

	QLabel* lblSound = new QLabel(tr("Sound Mode"));
	lblSound->setAlignment(Qt::AlignRight);
	comboSound = new QComboBox;
	comboSound->addItem(tr("Mono"));
	comboSound->addItem(tr("Stereo"));
	QHBoxLayout * soundLayout = new QHBoxLayout;
	soundLayout->addWidget(lblSound);
	soundLayout->addWidget(comboSound);

	QLabel* lblMagicOrder = new QLabel(tr("Magic Order"));
	lblMagicOrder->setAlignment(Qt::AlignRight);
	comboMagicOrder= new QComboBox;
	comboMagicOrder->addItem(tr("Restore,Attack,Indirect"));
	comboMagicOrder->addItem(tr("Restore,Indirect,Attack"));
	comboMagicOrder->addItem(tr("Attack,Indirect,Restore"));
	comboMagicOrder->addItem(tr("Attack,Restore,Indirect"));
	comboMagicOrder->addItem(tr("Indirect,Restore,Attack"));
	comboMagicOrder->addItem(tr("Indirect,Attack,Restore"));
	QHBoxLayout * magicOrderLayout = new QHBoxLayout;
	magicOrderLayout->addWidget(lblMagicOrder);
	magicOrderLayout->addWidget(comboMagicOrder);

	QLabel* lblCursor = new QLabel(tr("Cursor Type"));
	lblCursor->setAlignment(Qt::AlignRight);
	comboCursor= new QComboBox;
	comboCursor->addItem(tr("Initial"));
	comboCursor->addItem(tr("Memory"));
	QHBoxLayout * cursorLayout = new QHBoxLayout;
	cursorLayout->addWidget(lblCursor);
	cursorLayout->addWidget(comboCursor);

	QLabel* lblCamera = new QLabel(tr("Camera"));
	lblCamera->setAlignment(Qt::AlignRight);
	comboCamera= new QComboBox;
	comboCamera->addItem(tr("Initial"));
	comboCamera->addItem(tr("Memory"));
	QHBoxLayout * cameraLayout = new QHBoxLayout;
	cameraLayout->addWidget(lblCamera);
	cameraLayout->addWidget(comboCamera);

	QLabel* lblControllerMode = new QLabel(tr("Controller Settings"));
	lblControllerMode->setAlignment(Qt::AlignRight);
	comboControllerMode= new QComboBox;
	comboControllerMode->addItem(tr("Normal"));
	comboControllerMode->addItem(tr("Custom"));
	QHBoxLayout * controllerModeLayout = new QHBoxLayout;
	controllerModeLayout->addWidget(lblControllerMode);
	controllerModeLayout->addWidget(comboControllerMode);

	cbBattleTargets = new QCheckBox;
	cbBattleTargets->setText(tr("Show Battle Targets Labels"));
	cbBattleHelp = new QCheckBox;
	cbBattleHelp->setText(tr("Show Battle Help"));
	cbFieldHelp = new QCheckBox;
	cbFieldHelp->setText(tr("Show Field Help"));

	QHBoxLayout *helpLayout = new QHBoxLayout;
	QSpacerItem * helpSpacer1= new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred);
	helpLayout->addSpacerItem(helpSpacer1);
	helpLayout->addWidget(cbBattleTargets);
	QSpacerItem * helpSpacer2= new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred);
	helpLayout->addSpacerItem(helpSpacer2);
	helpLayout->addWidget(cbBattleHelp);
	QSpacerItem * helpSpacer3= new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred);
	helpLayout->addSpacerItem(helpSpacer3);
	helpLayout->addWidget(cbFieldHelp);
	QSpacerItem * helpSpacer4= new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred);
	helpLayout->addSpacerItem(helpSpacer4);

	QLabel *lblBattleSpeed = new  QLabel(tr("Battle Speed:"));
	slideBattleSpeed = new QSlider(Qt::Horizontal);
	slideBattleSpeed->setRange(0,256);
	QHBoxLayout *battleSpeedLayout = new QHBoxLayout;
	QLabel *lblBattleSpeedFast = new QLabel (tr("Fast"));
	QLabel *lblBattleSpeedSlow = new QLabel (tr("Slow"));

	battleSpeedLayout->addWidget(lblBattleSpeedFast);
	battleSpeedLayout->addWidget(slideBattleSpeed);
	battleSpeedLayout->addWidget(lblBattleSpeedSlow);

	QLabel *lblBattleMessageSpeed = new QLabel(tr("Battle Message Speed:"));
	slideBattleMessageSpeed = new QSlider(Qt::Horizontal);
	slideBattleMessageSpeed->setRange(0,256);
	QHBoxLayout *battleMessageSpeedLayout = new QHBoxLayout;
	QLabel *lblBattleMessageSpeedFast = new QLabel (tr("Fast"));
	QLabel *lblBattleMessageSpeedSlow = new QLabel (tr("Slow"));
	battleMessageSpeedLayout->addWidget(lblBattleMessageSpeedFast);
	battleMessageSpeedLayout->addWidget(slideBattleMessageSpeed);
	battleMessageSpeedLayout->addWidget(lblBattleMessageSpeedSlow);

	QLabel *lblFieldMessageSpeed = new QLabel(tr("Field Message Speed:"));
	slideFieldMessageSpeed = new QSlider(Qt::Horizontal);
	slideFieldMessageSpeed->setRange(0,256);
	QHBoxLayout *fieldMessageSpeedLayout = new QHBoxLayout;
	QLabel *lblFieldMessageSpeedFast = new QLabel (tr("Fast"));
	QLabel *lblFieldMessageSpeedSlow = new QLabel (tr("Slow"));
	fieldMessageSpeedLayout->addWidget(lblFieldMessageSpeedFast);
	fieldMessageSpeedLayout->addWidget(slideFieldMessageSpeed);
	fieldMessageSpeedLayout->addWidget(lblFieldMessageSpeedSlow);

	QGridLayout *speedLayout= new QGridLayout;
	speedLayout->addWidget(lblBattleSpeed,0,0);
	speedLayout->addWidget(lblBattleMessageSpeed,1,0);
	speedLayout->addWidget(lblFieldMessageSpeed,2,0);
	speedLayout->addLayout(battleSpeedLayout,0,1);
	speedLayout->addLayout(battleMessageSpeedLayout,1,1);
	speedLayout->addLayout(fieldMessageSpeedLayout,2,1);

    QLabel *lblBtnUp = new QLabel(tr("Up"));
	lblBtnUp->setAlignment(Qt::AlignRight);
	comboBtnUp = new QComboBox;
    comboBtnUp->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
    comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnUp->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnUp->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnUp->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnUpLayout = new QHBoxLayout;
	BtnUpLayout->addWidget(lblBtnUp);
	BtnUpLayout->addWidget(comboBtnUp);


	QLabel *lblBtnRight = new QLabel(tr("Right"));
	lblBtnRight->setAlignment(Qt::AlignRight);
	comboBtnRight = new QComboBox;
    comboBtnRight->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnRight->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnRight->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnRight->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnRightLayout = new QHBoxLayout;
	BtnRightLayout->addWidget(lblBtnRight);
	BtnRightLayout->addWidget(comboBtnRight);

	QLabel *lblBtnDown = new QLabel(tr("Down"));
	lblBtnDown->setAlignment(Qt::AlignRight);
	comboBtnDown = new QComboBox;
    comboBtnDown->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
    comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnDown->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnDown->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnDown->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnDownLayout = new QHBoxLayout;
	BtnDownLayout->addWidget(lblBtnDown);
	BtnDownLayout->addWidget(comboBtnDown);

	QLabel *lblBtnLeft = new QLabel(tr("Left"));
	lblBtnLeft->setAlignment(Qt::AlignRight);
	comboBtnLeft = new QComboBox;
    comboBtnLeft->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnLeft->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnLeft->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnLeft->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnLeftLayout = new QHBoxLayout;
	BtnLeftLayout->addWidget(lblBtnLeft);
	BtnLeftLayout->addWidget(comboBtnLeft);

	QLabel *lblBtnMenu = new QLabel(tr("Menu"));
	lblBtnMenu->setAlignment(Qt::AlignRight);
	comboBtnMenu = new QComboBox;
    comboBtnMenu->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnMenu->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnMenu->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnMenu->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnMenuLayout = new QHBoxLayout;
	BtnMenuLayout->addWidget(lblBtnMenu);
	BtnMenuLayout->addWidget(comboBtnMenu);

	QLabel *lblBtnOk = new QLabel(tr("Ok"));
	lblBtnOk->setAlignment(Qt::AlignRight);
	comboBtnOk = new QComboBox;
    comboBtnOk->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnOk->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnOk->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnOk->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnOkLayout = new QHBoxLayout;
	BtnOkLayout->addWidget(lblBtnOk);
	BtnOkLayout->addWidget(comboBtnOk);

	QLabel *lblBtnCancel = new QLabel(tr("Cancel"));
	lblBtnCancel->setAlignment(Qt::AlignRight);
	comboBtnCancel = new QComboBox;
    comboBtnCancel->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnCancel->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnCancel->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnCancel->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnCancelLayout = new QHBoxLayout;
	BtnCancelLayout->addWidget(lblBtnCancel);
	BtnCancelLayout->addWidget(comboBtnCancel);

	QLabel *lblBtnSwitch = new QLabel(tr("Switch"));
	lblBtnSwitch->setAlignment(Qt::AlignRight);
	comboBtnSwitch = new QComboBox;
    comboBtnSwitch->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnSwitch->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnSwitch->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnSwitchLayout = new QHBoxLayout;
	BtnSwitchLayout->addWidget(lblBtnSwitch);
	BtnSwitchLayout->addWidget(comboBtnSwitch);

	QLabel *lblBtnCamera = new QLabel(tr("Camera"));
	lblBtnCamera->setAlignment(Qt::AlignRight);
	comboBtnCamera = new QComboBox;
    comboBtnCamera->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnCamera->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnCamera->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnCamera->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnCameraLayout = new QHBoxLayout;
	BtnCameraLayout->addWidget(lblBtnCamera);
	BtnCameraLayout->addWidget(comboBtnCamera);

	QLabel *lblBtnTarget = new QLabel(tr("Target"));
	lblBtnTarget->setAlignment(Qt::AlignRight);
	comboBtnTarget = new QComboBox;
    comboBtnTarget->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnTarget->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnTarget->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnTarget->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnTargetLayout = new QHBoxLayout;
	BtnTargetLayout->addWidget(lblBtnTarget);
	BtnTargetLayout->addWidget(comboBtnTarget);

	QLabel *lblBtnPgUp = new QLabel(tr("Page Up"));
	lblBtnPgUp->setAlignment(Qt::AlignRight);
	comboBtnPgUp = new QComboBox;
    comboBtnPgUp->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnPgUp->addItem(QIcon(QPixmap()),QString(tr("? 10")));;
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnPgUp->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnPgUpLayout = new QHBoxLayout;
	BtnPgUpLayout->addWidget(lblBtnPgUp);
	BtnPgUpLayout->addWidget(comboBtnPgUp);

	QLabel *lblBtnPgDn = new QLabel(tr("Page Down"));
	lblBtnPgDn->setAlignment(Qt::AlignRight);
	comboBtnPgDn = new QComboBox;
    comboBtnPgDn->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnPgDn->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnPgDn->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnPgDnLayout = new QHBoxLayout;
	BtnPgDnLayout->addWidget(lblBtnPgDn);
	BtnPgDnLayout->addWidget(comboBtnPgDn);

	QLabel *lblBtnHelp = new QLabel(tr("Help"));
	lblBtnHelp->setAlignment(Qt::AlignRight);
	comboBtnHelp = new QComboBox;
    comboBtnHelp->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnHelp->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnHelp->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnHelp->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnHelpLayout = new QHBoxLayout;
	BtnHelpLayout->addWidget(lblBtnHelp);
	BtnHelpLayout->addWidget(comboBtnHelp);

	QLabel *lblBtnPause = new QLabel(tr("Pause"));
	lblBtnPause->setAlignment(Qt::AlignRight);
    comboBtnPause = new QComboBox;
    comboBtnPause->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtnPause->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtnPause->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtnPause->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *BtnPauseLayout = new QHBoxLayout;
	BtnPauseLayout->addWidget(lblBtnPause);
	BtnPauseLayout->addWidget(comboBtnPause);

	QLabel *lblBtn9 = new QLabel(tr("Unknown (9)"));
	lblBtn9->setAlignment(Qt::AlignRight);
	comboBtn9 = new QComboBox;
    comboBtn9->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtn9->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtn9->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtn9->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *Btn9Layout = new QHBoxLayout;
	Btn9Layout->addWidget(lblBtn9);
	Btn9Layout->addWidget(comboBtn9);

	QLabel *lblBtn10 = new QLabel(tr("Unknown(10)"));
	lblBtn10->setAlignment(Qt::AlignRight);
	comboBtn10 = new QComboBox;
    comboBtn10->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));;
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/l2")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/r2")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/l1")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/r1")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/triangle")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/circle")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/cross")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/square")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/select")),"");
	comboBtn10->addItem(QIcon(QPixmap()),QString(tr("? 9")));
	comboBtn10->addItem(QIcon(QPixmap()),QString(tr("? 10")));
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/start")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/up")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/right")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/down")),"");
	comboBtn10->addItem(QIcon(QPixmap(":/psxButtons/left")),"");
	QHBoxLayout *Btn10Layout = new QHBoxLayout;
	Btn10Layout->addWidget(lblBtn10);
	Btn10Layout->addWidget(comboBtn10);

	QVBoxLayout *btnLayout1 = new QVBoxLayout;
	btnLayout1->addLayout(BtnUpLayout);
	btnLayout1->addLayout(BtnRightLayout);
	btnLayout1->addLayout(BtnDownLayout);
	btnLayout1->addLayout(BtnLeftLayout);

	QVBoxLayout *btnLayout2 = new QVBoxLayout;
	btnLayout2->addLayout(BtnMenuLayout);
	btnLayout2->addLayout(BtnOkLayout);
	btnLayout2->addLayout(BtnCancelLayout);
	btnLayout2->addLayout(BtnSwitchLayout);

	QVBoxLayout *btnLayout3 = new QVBoxLayout;
	btnLayout3->addLayout(BtnCameraLayout);
	btnLayout3->addLayout(BtnTargetLayout);
	btnLayout3->addLayout(BtnPgUpLayout);
	btnLayout3->addLayout(BtnPgDnLayout);

	QVBoxLayout *btnLayout4 = new QVBoxLayout;
	btnLayout4->addLayout(BtnHelpLayout);
	btnLayout4->addLayout(BtnPauseLayout);
	btnLayout4->addLayout(Btn9Layout);
	btnLayout4->addLayout(Btn10Layout);

	QHBoxLayout *controllerMappingLayout = new QHBoxLayout;
	controllerMappingLayout->addLayout(btnLayout1);
	controllerMappingLayout->addLayout(btnLayout2);
	controllerMappingLayout->addLayout(btnLayout3);
	controllerMappingLayout->addLayout(btnLayout4);

	controllerMappingBox = new QGroupBox;
	controllerMappingBox->setTitle(tr("Custom Controller Mapping (PSX Only)"));
	controllerMappingBox->setLayout(controllerMappingLayout);

	centerLayout = new QVBoxLayout;
	centerLayout->addWidget(dialogBox);
	QSpacerItem *centerSpacer1 = new QSpacerItem (0,6,QSizePolicy::Preferred,QSizePolicy::Preferred);
	centerLayout->addSpacerItem(centerSpacer1);
	centerLayout->addLayout(atbLayout);
	centerLayout->addLayout(soundLayout);
	centerLayout->addLayout(magicOrderLayout);
	centerLayout->addLayout(cursorLayout);
	centerLayout->addLayout(cameraLayout);
	centerLayout->addLayout(controllerModeLayout);
	centerLayout->addLayout(helpLayout);
	centerLayout->addLayout(speedLayout);
	centerLayout->addWidget(controllerMappingBox);

	centerWidget = new QWidget;
	centerWidget->setLayout(centerLayout);
	centerWidget->adjustSize();

	setWidget(centerWidget);
	adjustSize();
}

void OptionsWidget::resizeEvent(QResizeEvent*)
{
	int margins =contentsMargins().right() + contentsMargins().left();
	if(!verticalScrollBar()->isVisible()){centerWidget->setFixedWidth( width() - margins);}
	else{centerWidget->setFixedWidth(width()- (margins + verticalScrollBar()->width()));}
	dialogBox->setFixedSize(centerWidget->width()-20,centerWidget->width()/4);
	centerWidget->adjustSize();
}

void OptionsWidget::init_Connections()
{
	connect(dialogPreview,SIGNAL(UL_ColorChanged(QColor)),this,SLOT(ulColorChange(QColor)));
	connect(dialogPreview,SIGNAL(UR_ColorChanged(QColor)),this,SLOT(urColorChange(QColor)));
	connect(dialogPreview,SIGNAL(LL_ColorChanged(QColor)),this,SLOT(llColorChange(QColor)));
	connect(dialogPreview,SIGNAL(LR_ColorChanged(QColor)),this,SLOT(lrColorChange(QColor)));
	connect(comboAtb,SIGNAL(currentIndexChanged(int)),this,SLOT(atbChanged(int)));
	connect(comboSound,SIGNAL(currentIndexChanged(int)),this,SLOT(soundChanged(int)));
	connect(comboMagicOrder,SIGNAL(currentIndexChanged(int)),this,SLOT(magicOrderChanged(int)));
	connect(comboCursor,SIGNAL(currentIndexChanged(int)),this,SLOT(cursorChanged(int)));
	connect(comboCamera,SIGNAL(currentIndexChanged(int)),this,SLOT(cameraChanged(int)));
	connect(comboControllerMode,SIGNAL(currentIndexChanged(int)),this,SLOT(controllerModeChanged(int)));
	connect(cbBattleTargets,SIGNAL(clicked(bool)),this,SLOT(battleTargetsChanged(bool)));
	connect(cbBattleHelp,SIGNAL(clicked(bool)),this,SLOT(battleHelpChanged(bool)));
	connect(cbFieldHelp,SIGNAL(clicked(bool)),this,SLOT(fieldHelpChanged(bool)));
	connect(slideBattleSpeed,SIGNAL(valueChanged(int)),this,SLOT(battleSpeedChanged(int)));
	connect(slideBattleMessageSpeed,SIGNAL(valueChanged(int)),this,SLOT(battleMessageSpeedChanged(int)));
	connect(slideFieldMessageSpeed,SIGNAL(valueChanged(int)),this,SLOT(fieldMessageSpeedChanged(int)));
	connect(comboBtnUp,SIGNAL(currentIndexChanged(int)),this,SLOT(btnUpChanged(int)));
	connect(comboBtnRight,SIGNAL(currentIndexChanged(int)),this,SLOT(btnRightChanged(int)));
	connect(comboBtnDown,SIGNAL(currentIndexChanged(int)),this,SLOT(btnDownChanged(int)));
	connect(comboBtnLeft,SIGNAL(currentIndexChanged(int)),this,SLOT(btnLeftChanged(int)));
	connect(comboBtnMenu,SIGNAL(currentIndexChanged(int)),this,SLOT(btnMenuChanged(int)));
	connect(comboBtnOk,SIGNAL(currentIndexChanged(int)),this,SLOT(btnOkChanged(int)));
	connect(comboBtnCancel,SIGNAL(currentIndexChanged(int)),this,SLOT(btnCancelChanged(int)));
	connect(comboBtnSwitch,SIGNAL(currentIndexChanged(int)),this,SLOT(btnSwitchChanged(int)));
	connect(comboBtnCamera,SIGNAL(currentIndexChanged(int)),this,SLOT(btnCameraChanged(int)));
	connect(comboBtnTarget,SIGNAL(currentIndexChanged(int)),this,SLOT(btnTargetChanged(int)));
	connect(comboBtnPgUp,SIGNAL(currentIndexChanged(int)),this,SLOT(btnPgUpChanged(int)));
	connect(comboBtnPgDn,SIGNAL(currentIndexChanged(int)),this,SLOT(btnPgDnChanged(int)));
	connect(comboBtnHelp,SIGNAL(currentIndexChanged(int)),this,SLOT(btnHelpChanged(int)));
	connect(comboBtnPause,SIGNAL(currentIndexChanged(int)),this,SLOT(btnPauseChanged(int)));
	connect(comboBtn9,SIGNAL(currentIndexChanged(int)),this,SLOT(btn9Changed(int)));
	connect(comboBtn10,SIGNAL(currentIndexChanged(int)),this,SLOT(btn10Changed(int)));
}

void OptionsWidget::ulColorChange(QColor color){emit(dialogColorULChanged(color));}
void OptionsWidget::urColorChange(QColor color){emit(dialogColorURChanged(color));}
void OptionsWidget::llColorChange(QColor color){emit(dialogColorLLChanged(color));}
void OptionsWidget::lrColorChange(QColor color){emit(dialogColorLRChanged(color));}
void OptionsWidget::atbChanged(int index){emit(AtbChanged(index));}
void OptionsWidget::soundChanged(int index){emit(SoundChanged(index));}
void OptionsWidget::magicOrderChanged(int index){emit(MagicOrderChanged(index));}
void OptionsWidget::cursorChanged(int index){emit(CursorChanged(index));}
void OptionsWidget::cameraChanged(int index){emit(CameraChanged(index));}
void OptionsWidget::controllerModeChanged(int index){emit(ControllerModeChanged(index));}
void OptionsWidget::battleTargetsChanged(bool checked){emit BattleTargetsChanged(checked);}
void OptionsWidget::battleHelpChanged(bool checked){emit BattleHelpChanged(checked);}
void OptionsWidget::fieldHelpChanged(bool checked){emit FieldHelpChanged(checked);}
void OptionsWidget::battleSpeedChanged(int speed){emit BattleSpeedChanged(speed);}
void OptionsWidget::battleMessageSpeedChanged(int speed){emit BattleMessageSpeedChanged(speed);}
void OptionsWidget::fieldMessageSpeedChanged(int speed){emit FieldMessageSpeedChanged(speed);}

void OptionsWidget::btnUpChanged(int btnNumber){emit BtnUpChanged(btnNumber);}
void OptionsWidget::btnRightChanged(int btnNumber){emit BtnRightChanged(btnNumber);}
void OptionsWidget::btnDownChanged(int btnNumber){emit BtnDownChanged(btnNumber);}
void OptionsWidget::btnLeftChanged(int btnNumber){emit BtnLeftChanged(btnNumber);}

void OptionsWidget::btnMenuChanged(int btnNumber){emit BtnMenuChanged(btnNumber);}
void OptionsWidget::btnOkChanged(int btnNumber){emit BtnOkChanged(btnNumber);}
void OptionsWidget::btnCancelChanged(int btnNumber){emit BtnCancelChanged(btnNumber);}
void OptionsWidget::btnSwitchChanged(int btnNumber){emit BtnSwitchChanged(btnNumber);}

void OptionsWidget::btnCameraChanged(int btnNumber){emit BtnCameraChanged(btnNumber);}
void OptionsWidget::btnTargetChanged(int btnNumber){emit BtnTargetChanged(btnNumber);}
void OptionsWidget::btnPgUpChanged(int btnNumber){emit BtnPgUpChanged(btnNumber);}
void OptionsWidget::btnPgDnChanged(int btnNumber){emit BtnPgDnChanged(btnNumber);}

void OptionsWidget::btnHelpChanged(int btnNumber){emit BtnHelpChanged(btnNumber);}
void OptionsWidget::btnPauseChanged(int btnNumber){emit BtnPauseChanged(btnNumber);}
void OptionsWidget::btn9Changed(int btnNumber){emit Btn9Changed(btnNumber);}
void OptionsWidget::btn10Changed(int btnNumber){emit Btn10Changed(btnNumber);}

void OptionsWidget::setDialogColors(QColor ul, QColor ur, QColor ll, QColor lr)
{
	disconnect(dialogPreview,SIGNAL(UL_ColorChanged(QColor)),this,SLOT(ulColorChange(QColor)));
	disconnect(dialogPreview,SIGNAL(UR_ColorChanged(QColor)),this,SLOT(urColorChange(QColor)));
	disconnect(dialogPreview,SIGNAL(LL_ColorChanged(QColor)),this,SLOT(llColorChange(QColor)));
	disconnect(dialogPreview,SIGNAL(LR_ColorChanged(QColor)),this,SLOT(lrColorChange(QColor)));

	dialogPreview->SetULeft(ul);
	dialogPreview->SetURight(ur);
	dialogPreview->SetLLeft(ll);
	dialogPreview->SetLRight(lr);

	connect(dialogPreview,SIGNAL(UL_ColorChanged(QColor)),this,SLOT(ulColorChange(QColor)));
	connect(dialogPreview,SIGNAL(UR_ColorChanged(QColor)),this,SLOT(urColorChange(QColor)));
	connect(dialogPreview,SIGNAL(LL_ColorChanged(QColor)),this,SLOT(llColorChange(QColor)));
	connect(dialogPreview,SIGNAL(LR_ColorChanged(QColor)),this,SLOT(lrColorChange(QColor)));
}
void OptionsWidget::setAtb(int mode)
{
	disconnect(comboAtb,SIGNAL(currentIndexChanged(int)),this,SLOT(atbChanged(int)));
	comboAtb->setCurrentIndex(mode);
	connect(comboAtb,SIGNAL(currentIndexChanged(int)),this,SLOT(atbChanged(int)));
}

void OptionsWidget::setSoundMode(int mode)
{
	disconnect(comboSound,SIGNAL(currentIndexChanged(int)),this,SLOT(soundChanged(int)));
	comboSound->setCurrentIndex(mode);
	connect(comboSound,SIGNAL(currentIndexChanged(int)),this,SLOT(soundChanged(int)));
}

void OptionsWidget::setMagicOrder(int order)
{
	disconnect(comboMagicOrder,SIGNAL(currentIndexChanged(int)),this,SLOT(magicOrderChanged(int)));
	comboMagicOrder->setCurrentIndex(order);
	connect(comboMagicOrder,SIGNAL(currentIndexChanged(int)),this,SLOT(magicOrderChanged(int)));
}

void OptionsWidget::setCursor(int mode)
{
	disconnect(comboCursor,SIGNAL(currentIndexChanged(int)),this,SLOT(cursorChanged(int)));
	comboCursor->setCurrentIndex(mode);
	connect(comboCursor,SIGNAL(currentIndexChanged(int)),this,SLOT(cursorChanged(int)));
}

void OptionsWidget::setCamera(int mode)
{
	disconnect(comboCamera,SIGNAL(currentIndexChanged(int)),this,SLOT(cameraChanged(int)));
	comboCamera->setCurrentIndex(mode);
	connect(comboCamera,SIGNAL(currentIndexChanged(int)),this,SLOT(cameraChanged(int)));
}

void OptionsWidget::setControllerMode(int mode)
{
	disconnect(comboControllerMode,SIGNAL(currentIndexChanged(int)),this,SLOT(controllerModeChanged(int)));
	comboControllerMode->setCurrentIndex(mode);
	connect(comboControllerMode,SIGNAL(currentIndexChanged(int)),this,SLOT(controllerModeChanged(int)));
}
void OptionsWidget::setBattleTargets(bool shown)
{
	disconnect(cbBattleTargets,SIGNAL(clicked(bool)),this,SLOT(battleTargetsChanged(bool)));
	cbBattleTargets->setChecked(shown);
	connect(cbBattleTargets,SIGNAL(clicked(bool)),this,SLOT(battleTargetsChanged(bool)));
}
void OptionsWidget::setBattleHelp(bool shown)
{
	disconnect(cbBattleHelp,SIGNAL(clicked(bool)),this,SLOT(battleHelpChanged(bool)));
	cbBattleHelp->setChecked(shown);
	connect(cbBattleHelp,SIGNAL(clicked(bool)),this,SLOT(battleHelpChanged(bool)));
}

void OptionsWidget::setFieldHelp(bool shown)
{
	disconnect(cbFieldHelp,SIGNAL(clicked(bool)),this,SLOT(fieldHelpChanged(bool)));
	cbFieldHelp->setChecked(shown);
	connect(cbFieldHelp,SIGNAL(clicked(bool)),this,SLOT(fieldHelpChanged(bool)));
}
void OptionsWidget::setBattleSpeed(int speed)
{
	disconnect(slideBattleSpeed,SIGNAL(valueChanged(int)),this,SLOT(battleSpeedChanged(int)));
	slideBattleSpeed->setValue(speed);
	connect(slideBattleSpeed,SIGNAL(valueChanged(int)),this,SLOT(battleSpeedChanged(int)));
}
void OptionsWidget::setBattleMessageSpeed(int speed)
{
	disconnect(slideBattleMessageSpeed,SIGNAL(valueChanged(int)),this,SLOT(battleMessageSpeedChanged(int)));
	slideBattleMessageSpeed->setValue(speed);
	connect(slideBattleMessageSpeed,SIGNAL(valueChanged(int)),this,SLOT(battleMessageSpeedChanged(int)));
}
void OptionsWidget::setFieldMessageSpeed(int speed)
{
	disconnect(slideFieldMessageSpeed,SIGNAL(valueChanged(int)),this,SLOT(fieldMessageSpeedChanged(int)));
	slideFieldMessageSpeed->setValue(speed);
	connect(slideFieldMessageSpeed,SIGNAL(valueChanged(int)),this,SLOT(fieldMessageSpeedChanged(int)));
}

void OptionsWidget::setBtnUp(int btnNumber)
{
	disconnect(comboBtnUp,SIGNAL(currentIndexChanged(int)),this,SLOT(btnUpChanged(int)));
	comboBtnUp->setCurrentIndex(btnNumber);
	connect(comboBtnUp,SIGNAL(currentIndexChanged(int)),this,SLOT(btnUpChanged(int)));
}
void OptionsWidget::setBtnRight(int btnNumber)
{
	disconnect(comboBtnRight,SIGNAL(currentIndexChanged(int)),this,SLOT(btnRightChanged(int)));
	comboBtnRight->setCurrentIndex(btnNumber);
	connect(comboBtnRight,SIGNAL(currentIndexChanged(int)),this,SLOT(btnRightChanged(int)));
}
void OptionsWidget::setBtnDown(int btnNumber)
{
	disconnect(comboBtnDown,SIGNAL(currentIndexChanged(int)),this,SLOT(btnDownChanged(int)));
	comboBtnDown->setCurrentIndex(btnNumber);
	connect(comboBtnDown,SIGNAL(currentIndexChanged(int)),this,SLOT(btnDownChanged(int)));
}
void OptionsWidget::setBtnLeft(int btnNumber)
{
	disconnect(comboBtnLeft,SIGNAL(currentIndexChanged(int)),this,SLOT(btnLeftChanged(int)));
	comboBtnLeft->setCurrentIndex(btnNumber);
	connect(comboBtnLeft,SIGNAL(currentIndexChanged(int)),this,SLOT(btnLeftChanged(int)));
}

void OptionsWidget::setBtnMenu(int btnNumber)
{
	disconnect(comboBtnMenu,SIGNAL(currentIndexChanged(int)),this,SLOT(btnMenuChanged(int)));
	comboBtnMenu->setCurrentIndex(btnNumber);
	connect(comboBtnMenu,SIGNAL(currentIndexChanged(int)),this,SLOT(btnMenuChanged(int)));
}
void OptionsWidget::setBtnOk(int btnNumber)
{
	disconnect(comboBtnOk,SIGNAL(currentIndexChanged(int)),this,SLOT(btnOkChanged(int)));
	comboBtnOk->setCurrentIndex(btnNumber);
	connect(comboBtnOk,SIGNAL(currentIndexChanged(int)),this,SLOT(btnOkChanged(int)));
}
void OptionsWidget::setBtnCancel(int btnNumber)
{
	disconnect(comboBtnCancel,SIGNAL(currentIndexChanged(int)),this,SLOT(btnCancelChanged(int)));
	comboBtnCancel->setCurrentIndex(btnNumber);
	connect(comboBtnCancel,SIGNAL(currentIndexChanged(int)),this,SLOT(btnCancelChanged(int)));
}
void OptionsWidget::setBtnSwitch(int btnNumber)
{
	disconnect(comboBtnSwitch,SIGNAL(currentIndexChanged(int)),this,SLOT(btnSwitchChanged(int)));
	comboBtnSwitch->setCurrentIndex(btnNumber);
	connect(comboBtnSwitch,SIGNAL(currentIndexChanged(int)),this,SLOT(btnSwitchChanged(int)));
}

void OptionsWidget::setBtnCamera(int btnNumber)
{
	disconnect(comboBtnCamera,SIGNAL(currentIndexChanged(int)),this,SLOT(btnCameraChanged(int)));
	comboBtnCamera->setCurrentIndex(btnNumber);
	connect(comboBtnCamera,SIGNAL(currentIndexChanged(int)),this,SLOT(btnCameraChanged(int)));
}
void OptionsWidget::setBtnTarget(int btnNumber)
{
	disconnect(comboBtnTarget,SIGNAL(currentIndexChanged(int)),this,SLOT(btnTargetChanged(int)));
	comboBtnTarget->setCurrentIndex(btnNumber);
	connect(comboBtnTarget,SIGNAL(currentIndexChanged(int)),this,SLOT(btnTargetChanged(int)));
}
void OptionsWidget::setBtnPgUp(int btnNumber)
{
	disconnect(comboBtnPgUp,SIGNAL(currentIndexChanged(int)),this,SLOT(btnPgUpChanged(int)));
	comboBtnPgUp->setCurrentIndex(btnNumber);
	connect(comboBtnPgUp,SIGNAL(currentIndexChanged(int)),this,SLOT(btnPgUpChanged(int)));
}
void OptionsWidget::setBtnPgDn(int btnNumber)
{
	disconnect(comboBtnPgDn,SIGNAL(currentIndexChanged(int)),this,SLOT(btnPgDnChanged(int)));
	comboBtnPgDn->setCurrentIndex(btnNumber);
	connect(comboBtnPgDn,SIGNAL(currentIndexChanged(int)),this,SLOT(btnPgDnChanged(int)));
}
void OptionsWidget::setBtnHelp(int btnNumber)
{
	disconnect(comboBtnHelp,SIGNAL(currentIndexChanged(int)),this,SLOT(btnHelpChanged(int)));
	comboBtnHelp->setCurrentIndex(btnNumber);
	connect(comboBtnHelp,SIGNAL(currentIndexChanged(int)),this,SLOT(btnHelpChanged(int)));
}
void OptionsWidget::setBtnPause(int btnNumber)
{
	disconnect(comboBtnPause,SIGNAL(currentIndexChanged(int)),this,SLOT(btnPauseChanged(int)));
	comboBtnPause->setCurrentIndex(btnNumber);
	connect(comboBtnPause,SIGNAL(currentIndexChanged(int)),this,SLOT(btnPauseChanged(int)));
}void OptionsWidget::setBtn9(int btnNumber)
{
	disconnect(comboBtn9,SIGNAL(currentIndexChanged(int)),this,SLOT(btn9Changed(int)));
	comboBtn9->setCurrentIndex(btnNumber);
	connect(comboBtn9,SIGNAL(currentIndexChanged(int)),this,SLOT(btn9Changed(int)));
}
void OptionsWidget::setBtn10(int btnNumber)
{
	disconnect(comboBtn10,SIGNAL(currentIndexChanged(int)),this,SLOT(btn10Changed(int)));
	comboBtn10->setCurrentIndex(btnNumber);
	connect(comboBtn10,SIGNAL(currentIndexChanged(int)),this,SLOT(btn10Changed(int)));
}

void OptionsWidget::setSliderStyle(QString styleSheet)
{
	slideBattleSpeed->setStyleSheet(styleSheet);
	slideBattleMessageSpeed->setStyleSheet(styleSheet);
	slideFieldMessageSpeed->setStyleSheet(styleSheet);
}

void OptionsWidget::setControllerMappingVisible(bool visible){controllerMappingBox->setVisible(visible);centerWidget->adjustSize();}
void OptionsWidget::setScrollAreaStyleSheet(QString styleSheet){centerWidget->setStyleSheet(styleSheet);}
