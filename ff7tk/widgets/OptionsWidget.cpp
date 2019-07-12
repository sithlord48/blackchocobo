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
    , dialogPreview(new DialogPreview)
    , dialogBox(new QGroupBox)
    , comboAtb(new QComboBox)
    , comboSound(new QComboBox)
    , comboMagicOrder(new QComboBox)
    , comboCursor(new QComboBox)
    , comboCamera(new QComboBox)
    , comboControllerMode(new QComboBox)
    , cbBattleTargets(new QCheckBox)
    , cbBattleHelp(new QCheckBox)
    , cbFieldHelp(new QCheckBox)
    , controllerMappingBox(new QGroupBox)
    , labelAtb(new QLabel)
    , labelSound(new QLabel)
    , labelMagic(new QLabel)
    , labelCursor(new QLabel)
    , labelCamera(new QLabel)
    , labelControllerMode(new QLabel)
    , lblBattleSpeedMax(new QLabel)
    , lblBattleSpeedMin(new QLabel)
    , lblBattleMessageSpeedMax(new QLabel)
    , lblBattleMessageSpeedMin(new QLabel)
    , lblFieldMessageSpeedMax(new QLabel)
    , lblFieldMessageSpeedMin(new QLabel)
    , lblBattleSpeed(new QLabel)
    , lblBattleMessageSpeed(new QLabel)
    , lblFieldMessageSpeed(new QLabel)
{
    updateText();
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    connect(dialogPreview, &DialogPreview::UL_ColorChanged, this, &OptionsWidget::dialogColorULChanged);
    connect(dialogPreview, &DialogPreview::UR_ColorChanged, this, &OptionsWidget::dialogColorURChanged);
    connect(dialogPreview, &DialogPreview::LL_ColorChanged, this, &OptionsWidget::dialogColorLLChanged);
    connect(dialogPreview, &DialogPreview::LR_ColorChanged, this, &OptionsWidget::dialogColorLRChanged);

    auto layout = new QHBoxLayout;
    layout->addWidget(dialogPreview);
    layout->setContentsMargins(0, 0, 0, 0);
    dialogBox->setLayout(layout);

    auto centerLayout = new QVBoxLayout;
    centerLayout->addWidget(dialogBox);
    centerLayout->addSpacerItem(new QSpacerItem(0, 6, QSizePolicy::Preferred, QSizePolicy::Preferred));

    labelAtb->setAlignment(Qt::AlignRight);
    connect(comboAtb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWidget::atbChanged);

    layout = new QHBoxLayout;
    layout->addWidget(labelAtb);
    layout->addWidget(comboAtb);
    centerLayout->addLayout(layout);

    labelSound->setAlignment(Qt::AlignRight);
    connect(comboSound, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWidget::soundChanged);

    layout = new QHBoxLayout;
    layout->addWidget(labelSound);
    layout->addWidget(comboSound);
    centerLayout->addLayout(layout);

    labelMagic->setAlignment(Qt::AlignRight);
    connect(comboMagicOrder, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWidget::magicOrderChanged);

    layout = new QHBoxLayout;
    layout->addWidget(labelMagic);
    layout->addWidget(comboMagicOrder);
    centerLayout->addLayout(layout);

    labelCursor->setAlignment(Qt::AlignRight);
    connect(comboCursor, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWidget::cursorChanged);

    layout = new QHBoxLayout;
    layout->addWidget(labelCursor);
    layout->addWidget(comboCursor);
    centerLayout->addLayout(layout);

    labelCamera->setAlignment(Qt::AlignRight);
    connect(comboCamera, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWidget::cameraChanged);

    layout = new QHBoxLayout;
    layout->addWidget(labelCamera);
    layout->addWidget(comboCamera);
    centerLayout->addLayout(layout);

    labelControllerMode->setAlignment(Qt::AlignRight);
    connect(comboControllerMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWidget::controllerModeChanged);

    layout = new QHBoxLayout;
    layout->addWidget(labelControllerMode);
    layout->addWidget(comboControllerMode);
    centerLayout->addLayout(layout);

    connect(cbBattleTargets, &QCheckBox::toggled, this, &OptionsWidget::battleTargetsChanged);
    connect(cbBattleHelp, &QCheckBox::toggled, this, &OptionsWidget::battleHelpChanged);
    connect(cbFieldHelp, &QCheckBox::toggled, this, &OptionsWidget::fieldHelpChanged);

    layout = new QHBoxLayout;
    layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
    layout->addWidget(cbBattleTargets);
    layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
    layout->addWidget(cbBattleHelp);
    layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
    layout->addWidget(cbFieldHelp);
    layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
    centerLayout->addLayout(layout);

    slideBattleSpeed = new QSlider(Qt::Horizontal);
    slideBattleSpeed->setRange(0, 256);
    connect(slideBattleSpeed, &QSlider::valueChanged, this, &OptionsWidget::battleSpeedChanged);

    QHBoxLayout *battleSpeedLayout = new QHBoxLayout;
    battleSpeedLayout->addWidget(lblBattleSpeedMax);
    battleSpeedLayout->addWidget(slideBattleSpeed);
    battleSpeedLayout->addWidget(lblBattleSpeedMin);

    slideBattleMessageSpeed = new QSlider(Qt::Horizontal);
    slideBattleMessageSpeed->setRange(0, 256);
    connect(slideBattleMessageSpeed, &QSlider::valueChanged, this, &OptionsWidget::battleMessageSpeedChanged);

    QHBoxLayout *battleMessageSpeedLayout = new QHBoxLayout;
    battleMessageSpeedLayout->addWidget(lblBattleMessageSpeedMax);
    battleMessageSpeedLayout->addWidget(slideBattleMessageSpeed);
    battleMessageSpeedLayout->addWidget(lblBattleMessageSpeedMin);

    slideFieldMessageSpeed = new QSlider(Qt::Horizontal);
    slideFieldMessageSpeed->setRange(0, 256);
    connect(slideFieldMessageSpeed, &QSlider::valueChanged, this, &OptionsWidget::fieldMessageSpeedChanged);

    QHBoxLayout *fieldMessageSpeedLayout = new QHBoxLayout;
    fieldMessageSpeedLayout->addWidget(lblFieldMessageSpeedMax);
    fieldMessageSpeedLayout->addWidget(slideFieldMessageSpeed);
    fieldMessageSpeedLayout->addWidget(lblFieldMessageSpeedMin);

    QGridLayout *speedLayout = new QGridLayout;
    speedLayout->addWidget(lblBattleSpeed, 0, 0);
    speedLayout->addWidget(lblBattleMessageSpeed, 1, 0);
    speedLayout->addWidget(lblFieldMessageSpeed, 2, 0);
    speedLayout->addLayout(battleSpeedLayout, 0, 1);
    speedLayout->addLayout(battleMessageSpeedLayout, 1, 1);
    speedLayout->addLayout(fieldMessageSpeedLayout, 2, 1);
    centerLayout->addLayout(speedLayout);

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
    if (!verticalScrollBar()->isVisible()) {
        centerWidget->setFixedWidth(width() - margins);
    } else {
        centerWidget->setFixedWidth(width() - (margins + verticalScrollBar()->width()));
    }
    dialogBox->setFixedSize(centerWidget->width() - 20, centerWidget->width() / 4);
    centerWidget->adjustSize();
    event->accept();
}
void OptionsWidget::changeEvent(QEvent *e)
{
    if (e->type() != QEvent::LanguageChange) {
        return;
    }
    updateText();
}
void OptionsWidget::updateText()
{
    dialogBox->setTitle(tr("In-Game Dialog Preview"));
    labelAtb->setText(tr("ATB Style"));
    if (comboAtb->count() != 0) {
        for (int i = 0; i < comboAtb->count(); i++) {
            comboAtb->setItemText(i, tr(_atbList.at(i).toLatin1()));
        }
    } else {
        comboAtb->addItems(_atbList);
    }

    labelSound->setText(tr("Sound Mode"));
    if (comboSound->count() != 0) {
        for (int i = 0; i < comboSound->count(); i++) {
            comboSound->setItemText(i, tr(_soundList.at(i).toLatin1()));
        }
    } else {
        comboSound->addItems(_soundList);
    }

    labelMagic->setText(tr("Magic Order"));
    if (comboMagicOrder->count() != 0) {
        for (int i = 0; i < comboMagicOrder->count(); i++) {
            comboMagicOrder->setItemText(i, tr(_magicOrderList.at(i).toLatin1()));
        }
    } else {
        comboMagicOrder->addItems(_magicOrderList);
    }

    labelCursor->setText(tr("Cursor Type"));
    if (comboCursor->count() != 0) {
        for (int i = 0; i < comboCursor->count(); i++) {
            comboCursor->setItemText(i, tr(_cursorCameraList.at(i).toLatin1()));
        }
    } else {
        comboCursor->addItems(_cursorCameraList);
    }

    labelCamera->setText(tr("Camera"));
    if (comboCamera->count() != 0) {
        for (int i = 0; i < comboCamera->count(); i++) {
            comboCamera->setItemText(i, tr(_cursorCameraList.at(i).toLatin1()));
        }
    } else {
        comboCamera->addItems(_cursorCameraList);
    }

    labelControllerMode->setText(tr("Controller Settings"));
    if (comboControllerMode->count() != 0) {
        for (int i = 0; i < comboControllerMode->count(); i++) {
            comboControllerMode->setItemText(i, tr(_controllerModeList.at(i).toLatin1()));
        }
    } else {
        comboControllerMode->addItems(_controllerModeList);
    }

    cbBattleTargets->setText(tr("Show Battle Targets Labels"));
    cbBattleHelp->setText(tr("Show Battle Help"));
    cbFieldHelp->setText(tr("Show Field Help"));
    lblBattleSpeedMax->setText(tr(_fast.toLatin1()));
    lblBattleMessageSpeedMax->setText(tr(_fast.toLatin1()));
    lblFieldMessageSpeedMax->setText(tr(_fast.toLatin1()));
    lblBattleSpeedMin->setText(tr(_slow.toLatin1()));
    lblBattleMessageSpeedMin->setText(tr(_slow.toLatin1()));
    lblFieldMessageSpeedMin->setText(tr(_slow.toLatin1()));
    lblBattleSpeed->setText(tr("Battle Speed:"));
    lblBattleMessageSpeed->setText(tr("Battle Message Speed:"));
    lblFieldMessageSpeed->setText(tr("Field Message Speed:"));
    controllerMappingBox->setTitle(tr("Custom Controller Mapping (PSX Only)"));

    if (!lblInputs.isEmpty()) {
        for (int i = 0; i < lblInputs.count(); i++) {
            lblInputs[i]->setText(tr(_inputNames.at(i).toLatin1()));
        }
    } else {
        for (int i = 0; i < 16; i++) {
            lblInputs.append(new QLabel(tr(_inputNames.at(i).toLatin1())));
        }
    }
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

QGridLayout *OptionsWidget::makeControllerLayout()
{
    auto finalLayout = new QGridLayout;
    for (int i = 0; i < 16; i++) {
        lblInputs[i]->setAlignment(Qt::AlignRight);
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

        connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [comboBox, i, this] {
            emit inputChanged(i, comboBox->currentIndex());
        });

        auto layout = new QHBoxLayout;
        layout->addWidget(lblInputs[i]);
        layout->addWidget(comboBox);
        finalLayout->addLayout(layout, i % 4, i / 4);
    }
    return finalLayout;
}

void OptionsWidget::setInput(int controlAction, int newButton)
{
    QComboBox *inputCombo = centerWidget->findChild<QComboBox *>(_actionNames.at(controlAction));
    if (inputCombo->currentIndex() == newButton) {
        return;
    }
    inputCombo->blockSignals(true);
    inputCombo->setCurrentIndex(newButton);
    inputCombo->blockSignals(false);
}

void OptionsWidget::setScrollAreaStyleSheet(QString stylesheet)
{
    centerWidget->setStyleSheet(stylesheet);
}
