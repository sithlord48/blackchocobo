/****************************************************************************/
//    copyright 2013 -2019  Chris Rizzitello <sithlord48@gmail.com>         //
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
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	dialogBox = new QGroupBox;
	dialogPreview = new DialogPreview;
    connect(dialogPreview, &DialogPreview::UL_ColorChanged, this, &OptionsWidget::dialogColorULChanged);
    connect(dialogPreview, &DialogPreview::UR_ColorChanged, this, &OptionsWidget::dialogColorURChanged);
    connect(dialogPreview, &DialogPreview::LL_ColorChanged, this, &OptionsWidget::dialogColorLLChanged);
    connect(dialogPreview, &DialogPreview::LR_ColorChanged, this, &OptionsWidget::dialogColorLRChanged);

    auto layout = new QHBoxLayout;
    layout->addWidget(dialogPreview);
    layout->setContentsMargins(0,0,0,0);
    dialogBox->setLayout(layout);
	dialogBox->setTitle(tr("In-Game Dialog Preview"));

    auto centerLayout = new QVBoxLayout;
    centerLayout->addWidget(dialogBox);
    centerLayout->addSpacerItem(new QSpacerItem (0,6,QSizePolicy::Preferred,QSizePolicy::Preferred));

    auto label = new QLabel(tr("ATB Style"));
    label->setAlignment(Qt::AlignRight);
	comboAtb= new QComboBox;
	comboAtb->addItem(tr("Active"));
	comboAtb->addItem(tr("Recommended"));
	comboAtb->addItem(tr("Wait"));
    connect(comboAtb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWidget::atbChanged);

    layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(comboAtb);
    centerLayout->addLayout(layout);

    label = new QLabel(tr("Sound Mode"));
    label->setAlignment(Qt::AlignRight);
	comboSound = new QComboBox;
	comboSound->addItem(tr("Mono"));
	comboSound->addItem(tr("Stereo"));
    connect(comboSound, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &OptionsWidget::soundChanged);

    layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(comboSound);
    centerLayout->addLayout(layout);

    label = new QLabel(tr("Magic Order"));
    label->setAlignment(Qt::AlignRight);
	comboMagicOrder= new QComboBox;
	comboMagicOrder->addItem(tr("Restore,Attack,Indirect"));
	comboMagicOrder->addItem(tr("Restore,Indirect,Attack"));
	comboMagicOrder->addItem(tr("Attack,Indirect,Restore"));
	comboMagicOrder->addItem(tr("Attack,Restore,Indirect"));
	comboMagicOrder->addItem(tr("Indirect,Restore,Attack"));
	comboMagicOrder->addItem(tr("Indirect,Attack,Restore"));
    connect(comboMagicOrder, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWidget::magicOrderChanged);

    layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(comboMagicOrder);
    centerLayout->addLayout(layout);

    label = new QLabel(tr("Cursor Type"));
    label->setAlignment(Qt::AlignRight);
	comboCursor= new QComboBox;
	comboCursor->addItem(tr("Initial"));
	comboCursor->addItem(tr("Memory"));
    connect(comboCursor, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWidget::cursorChanged);

    layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(comboCursor);
    centerLayout->addLayout(layout);

    label = new QLabel(tr("Camera"));
    label->setAlignment(Qt::AlignRight);
	comboCamera= new QComboBox;
	comboCamera->addItem(tr("Initial"));
	comboCamera->addItem(tr("Memory"));
    connect(comboCamera, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWidget::cameraChanged);

    layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(comboCamera);
    centerLayout->addLayout(layout);

    label = new QLabel(tr("Controller Settings"));
    label->setAlignment(Qt::AlignRight);
	comboControllerMode= new QComboBox;
	comboControllerMode->addItem(tr("Normal"));
	comboControllerMode->addItem(tr("Custom"));
    connect(comboControllerMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWidget::controllerModeChanged);

    layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(comboControllerMode);
    centerLayout->addLayout(layout);

	cbBattleTargets = new QCheckBox;
	cbBattleTargets->setText(tr("Show Battle Targets Labels"));
    connect(cbBattleTargets, &QCheckBox::toggled, this, &OptionsWidget::battleTargetsChanged);
	cbBattleHelp = new QCheckBox;
	cbBattleHelp->setText(tr("Show Battle Help"));
    connect(cbBattleHelp, &QCheckBox::toggled, this, &OptionsWidget::battleHelpChanged);
    cbFieldHelp = new QCheckBox;
	cbFieldHelp->setText(tr("Show Field Help"));
    connect(cbFieldHelp, &QCheckBox::toggled, this, &OptionsWidget::fieldHelpChanged);

    layout = new QHBoxLayout;
    layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred));
    layout->addWidget(cbBattleTargets);
    layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred));
    layout->addWidget(cbBattleHelp);
    layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred));
    layout->addWidget(cbFieldHelp);
    layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred));
    centerLayout->addLayout(layout);

    slideBattleSpeed = new QSlider(Qt::Horizontal);
    slideBattleSpeed->setRange(0,256);
    connect(slideBattleSpeed, &QSlider::valueChanged, this, &OptionsWidget::battleSpeedChanged);

    QHBoxLayout *battleSpeedLayout = new QHBoxLayout;
    battleSpeedLayout->addWidget(new QLabel(tr("Fast")));
	battleSpeedLayout->addWidget(slideBattleSpeed);
    battleSpeedLayout->addWidget(new QLabel(tr("Slow")));

	slideBattleMessageSpeed = new QSlider(Qt::Horizontal);
	slideBattleMessageSpeed->setRange(0,256);
    connect(slideBattleMessageSpeed, &QSlider::valueChanged, this, &OptionsWidget::battleMessageSpeedChanged);

    QHBoxLayout *battleMessageSpeedLayout = new QHBoxLayout;
    battleMessageSpeedLayout->addWidget(new QLabel (tr("Fast")));
	battleMessageSpeedLayout->addWidget(slideBattleMessageSpeed);
    battleMessageSpeedLayout->addWidget(new QLabel (tr("Slow")));

	slideFieldMessageSpeed = new QSlider(Qt::Horizontal);
	slideFieldMessageSpeed->setRange(0,256);
    connect(slideFieldMessageSpeed, &QSlider::valueChanged, this, &OptionsWidget::fieldMessageSpeedChanged);

    QHBoxLayout *fieldMessageSpeedLayout = new QHBoxLayout;
    fieldMessageSpeedLayout->addWidget(new QLabel (tr("Fast")));
	fieldMessageSpeedLayout->addWidget(slideFieldMessageSpeed);
    fieldMessageSpeedLayout->addWidget(new QLabel (tr("Slow")));

    QGridLayout *speedLayout= new QGridLayout;
    speedLayout->addWidget(new  QLabel(tr("Battle Speed:")), 0, 0);
    speedLayout->addWidget(new QLabel(tr("Battle Message Speed:")), 1, 0);
    speedLayout->addWidget(new QLabel(tr("Field Message Speed:")), 2, 0);
	speedLayout->addLayout(battleSpeedLayout,0,1);
	speedLayout->addLayout(battleMessageSpeedLayout,1,1);
	speedLayout->addLayout(fieldMessageSpeedLayout,2,1);
    centerLayout->addLayout(speedLayout);

	controllerMappingBox = new QGroupBox;
	controllerMappingBox->setTitle(tr("Custom Controller Mapping (PSX Only)"));
    controllerMappingBox->setLayout(makeControllerLayout());
    centerLayout->addWidget(controllerMappingBox);

	centerWidget = new QWidget;
	centerWidget->setLayout(centerLayout);
	centerWidget->adjustSize();

	setWidget(centerWidget);
	adjustSize();
}

void OptionsWidget::resizeEvent(QResizeEvent *event)
{
    int margins = contentsMargins().right() + contentsMargins().left();
    if(!verticalScrollBar()->isVisible()) {
        centerWidget->setFixedWidth( width() - margins);
    } else {
        centerWidget->setFixedWidth(width()- (margins + verticalScrollBar()->width()));
    }
	dialogBox->setFixedSize(centerWidget->width()-20,centerWidget->width()/4);
	centerWidget->adjustSize();
    event->accept();
}

void OptionsWidget::setDialogColors(QColor ul, QColor ur, QColor ll, QColor lr)
{
    dialogPreview->blockSignals(true);
	dialogPreview->SetULeft(ul);
	dialogPreview->SetURight(ur);
	dialogPreview->SetLLeft(ll);
	dialogPreview->SetLRight(lr);
    dialogPreview->blockSignals(false);
}
void OptionsWidget::setAtbMode(int mode)
{
    comboAtb->blockSignals(true);
    comboAtb->setCurrentIndex(mode);
    comboAtb->blockSignals(false);
}

void OptionsWidget::setSoundMode(int mode)
{
    comboSound->blockSignals(true);
    comboSound->setCurrentIndex(mode);
    comboSound->blockSignals(false);
}

void OptionsWidget::setMagicOrder(int order)
{
    comboMagicOrder->blockSignals(true);
    comboMagicOrder->setCurrentIndex(order);
    comboMagicOrder->blockSignals(false);
}

void OptionsWidget::setCursor(int mode)
{
    comboCursor->blockSignals(true);
    comboCursor->setCurrentIndex(mode);
    comboCursor->blockSignals(false);
}

void OptionsWidget::setCamera(int mode)
{
    comboCamera->blockSignals(true);
    comboCamera->setCurrentIndex(mode);
    comboCamera->blockSignals(false);
}

void OptionsWidget::setControllerMode(int mode)
{
    comboControllerMode->blockSignals(true);
    comboControllerMode->setCurrentIndex(mode);
    comboControllerMode->blockSignals(false);
}

void OptionsWidget::setBattleTargets(bool shown)
{
    cbBattleTargets->blockSignals(true);
    cbBattleTargets->setChecked(shown);
    cbBattleTargets->blockSignals(false);
}

void OptionsWidget::setBattleHelp(bool shown)
{
    cbBattleHelp->blockSignals(true);
    cbBattleHelp->setChecked(shown);
    cbBattleHelp->blockSignals(false);
}

void OptionsWidget::setFieldHelp(bool shown)
{
    cbFieldHelp->blockSignals(true);
    cbFieldHelp->setChecked(shown);
    cbFieldHelp->blockSignals(false);
}

void OptionsWidget::setBattleSpeed(int speed)
{
    slideBattleSpeed->blockSignals(true);
    slideBattleSpeed->setValue(speed);
    slideBattleSpeed->blockSignals(false);
}

void OptionsWidget::setBattleMessageSpeed(int speed)
{
    slideBattleMessageSpeed->blockSignals(true);
    slideBattleMessageSpeed->setValue(speed);
    slideBattleMessageSpeed->blockSignals(false);
}

void OptionsWidget::setFieldMessageSpeed(int speed)
{
    slideFieldMessageSpeed->blockSignals(true);
    slideFieldMessageSpeed->setValue(speed);
    slideFieldMessageSpeed->blockSignals(false);
}

void OptionsWidget::setSliderStyle(QString styleSheet)
{
	slideBattleSpeed->setStyleSheet(styleSheet);
	slideBattleMessageSpeed->setStyleSheet(styleSheet);
	slideFieldMessageSpeed->setStyleSheet(styleSheet);
}

void OptionsWidget::setControllerMappingVisible(bool visible)
{
    controllerMappingBox->setVisible(visible);
    centerWidget->adjustSize();
}

QGridLayout* OptionsWidget::makeControllerLayout()
{
    auto finalLayout = new QGridLayout;
    for (int i = 0; i < 16; i++) {
        auto label = new QLabel(_inputNames.at(i));
        label->setAlignment(Qt::AlignRight);
        auto comboBox = new QComboBox;
        comboBox->setObjectName(_inputNames.at(i));
        comboBox->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/l2")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/r2")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/l1")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/r1")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/triangle")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/circle")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/cross")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/square")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/select")), QString());
        comboBox->addItem(QIcon(QPixmap()), QString(tr("9")));
        comboBox->addItem(QIcon(QPixmap()), QString(tr("10")));
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/start")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/up")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/right")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/down")), QString());
        comboBox->addItem(QIcon(QPixmap(":/psxButtons/left")), QString());

        connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [comboBox, i, this]{
            emit inputChanged(i, comboBox->currentIndex());
        });

        auto layout = new QHBoxLayout;
        layout->addWidget(label);
        layout->addWidget(comboBox);
        finalLayout->addLayout(layout, i % 4, i / 4);
    }
    return finalLayout;
}

void OptionsWidget::setInput(int controlAction, int newButton)
{
    QComboBox *inputCombo = centerWidget->findChild<QComboBox*>(_actionNames.at(controlAction));
    if(inputCombo->currentIndex() == newButton)
        return;
    inputCombo->blockSignals(true);
    inputCombo->setCurrentIndex(newButton);
    inputCombo->blockSignals(false);
}

void OptionsWidget::setScrollAreaStyleSheet(QString stylesheet)
{
    centerWidget->setStyleSheet(stylesheet);
}
