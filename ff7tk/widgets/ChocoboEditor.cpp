/****************************************************************************/
//    copyright 2012 - 2020  Chris Rizzitello <sithlord48@gmail.com>        //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "ChocoboEditor.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QResizeEvent>
#include <QSpinBox>

void ChocoboEditor::resizeEvent(QResizeEvent *ev)
{
    if (ev->type() == QEvent::Resize) {
        Final->setColumnMinimumWidth(0, width() / 4);
        Final->setColumnMinimumWidth(1, width() / 4);
        Final->setColumnStretch(0, width() / 4);
        Final->setColumnStretch(1, width() / 4);
    }
}
void ChocoboEditor::updateText()
{
    lbl_speed->setText(tr("Run Speed"));
    lbl_sprint->setText(tr("Sprint Speed"));
    lbl_accel->setText(tr("Acceleration"));
    lbl_stamina->setText(tr("Stamina"));
    lbl_wins->setText(tr("Races Won"));
    lbl_coop->setText(tr("Cooperation"));
    lbl_intel->setText(tr("Intelligence"));
    lbl_pCount->setText(tr("pCount"));
    lbl_personality->setText(tr("Personality"));
    lbl_rating->setText(tr("Choco Billy's Rating: "));
    lblSpeedWarning->setText(tr("Speed Values Are The Raw Values\nThe km/h speeds are calculated while playing "));
    line_name->setPlaceholderText(tr("Name"));
    cb_cantMate->setText(tr("Unable To Mate"));
    getRank();

    if (combo_sex->count() != 0) {
        combo_sex->setItemText(0, tr("Male %1").arg(QString::fromUtf8("♂")));
        combo_sex->setItemText(1, tr("Female %1").arg(QString::fromUtf8("♀")));
    } else {
        combo_sex->addItem(tr("Male %1").arg(QString::fromUtf8("♂")));
        combo_sex->addItem(tr("Female %1").arg(QString::fromUtf8("♀")));
    }

    if (combo_type->count() != 0) {
        combo_type->setItemText(0, tr("Yellow"));
        combo_type->setItemText(1, tr("Green"));
        combo_type->setItemText(2, tr("Blue"));
        combo_type->setItemText(3, tr("Black"));
        combo_type->setItemText(4, tr("Gold"));
    } else {
        combo_type->addItem(QIcon(QPixmap(":/chocobo/yellow")), tr("Yellow"));
        combo_type->addItem(QIcon(QPixmap(":/chocobo/green")), tr("Green"));
        combo_type->addItem(QIcon(QPixmap(":/chocobo/blue")), tr("Blue"));
        combo_type->addItem(QIcon(QPixmap(":/chocobo/black")), tr("Black"));
        combo_type->addItem(QIcon(QPixmap(":/chocobo/gold")), tr("Gold"));
    }

    QStringList typelist {
        tr("Empty"), tr("Wonderful"), tr("Great")
        , tr("Good"), tr("Fair"), tr("Average")
        , tr("Poor"), tr("Bad"), tr("Terrible")
    };

    if (combo_rating->count() != 0) {
        for (int i = 0; i < typelist.count(); i++) {
            combo_rating->setItemText(i, typelist.at(i));
        }
    } else {
        combo_rating->addItems(typelist);
    }
}
ChocoboEditor::ChocoboEditor(QWidget *parent) :
    QWidget(parent)
    , lbl_rank(new QLabel)
    , lbl_speed(new QLabel)
    , lbl_sprint(new QLabel)
    , lbl_accel(new QLabel)
    , lbl_stamina(new QLabel)
    , lbl_wins(new QLabel)
    , lbl_coop(new QLabel)
    , lbl_intel(new QLabel)
    , lbl_pCount(new QLabel)
    , lbl_personality(new QLabel)
    , lbl_rating(new QLabel)
    , lblSpeedWarning(new QLabel)
    , combo_sex(new QComboBox(this))
    , combo_type(new QComboBox(this))
    , combo_rating(new QComboBox(this))
    , cb_cantMate(new QCheckBox(this))
    , line_name(new QLineEdit(this))
{
    cb_cantMate->setStyleSheet(QStringLiteral("QCheckBox::indicator {width: %1px; height: %1px;}").arg(QString::number(fontMetrics().height())));
    //create Gui Widgets.
    sb_speed = makeSpinBox(9999);
    sb_mSpeed = makeSpinBox(9999);
    sb_sprint = makeSpinBox(9999);
    sb_mSprint = makeSpinBox(9999);
    sb_stamina = makeSpinBox(9999);
    sb_accel = makeSpinBox(255);
    sb_wins = makeSpinBox(255);
    sb_coop = makeSpinBox(255);
    sb_pCount = makeSpinBox(255);
    sb_intel = makeSpinBox(255);
    sb_personality = makeSpinBox(255);
    combo_type->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));
    line_name->setMaxLength(6);

    auto lbl_div_speed = new QLabel(QStringLiteral("/"), this);
    lbl_div_speed->setAlignment(Qt::AlignHCenter);
    lbl_div_speed->setMaximumWidth(font().pointSize());

    auto lbl_div_sprint = new QLabel(QStringLiteral("/"), this);
    lbl_div_sprint->setAlignment(Qt::AlignHCenter);
    lbl_div_sprint->setMaximumWidth(font().pointSize());

    updateText();

    auto speed_layout = new QHBoxLayout;
    speed_layout->addWidget(lbl_speed);
    speed_layout->addWidget(sb_speed);
    speed_layout->addWidget(lbl_div_speed);
    speed_layout->addWidget(sb_mSpeed);

    auto sprint_layout = new QHBoxLayout;
    sprint_layout->addWidget(lbl_sprint);
    sprint_layout->addWidget(sb_sprint);
    sprint_layout->addWidget(lbl_div_sprint);
    sprint_layout->addWidget(sb_mSprint);

    auto accel_layout = new QHBoxLayout;
    accel_layout->addWidget(lbl_accel);
    accel_layout->addWidget(sb_accel);

    auto stamina_layout = new QHBoxLayout;
    stamina_layout->addWidget(lbl_stamina);
    stamina_layout->addWidget(sb_stamina);

    auto wins_layout = new QHBoxLayout;
    wins_layout->addWidget(lbl_wins);
    wins_layout->addWidget(sb_wins);

    auto coop_layout = new QHBoxLayout;
    coop_layout->addWidget(lbl_coop);
    coop_layout->addWidget(sb_coop);

    auto intel_layout = new QHBoxLayout;
    intel_layout->addWidget(lbl_intel);
    intel_layout->addWidget(sb_intel);

    auto pCount_layout = new QHBoxLayout;
    pCount_layout->addWidget(lbl_pCount);
    pCount_layout->addWidget(sb_pCount);

    auto personality_layout = new QHBoxLayout;
    personality_layout->addWidget(lbl_personality);
    personality_layout->addWidget(sb_personality);

    auto pCount_personality_layout = new QHBoxLayout;
    pCount_personality_layout->addLayout(pCount_layout);
    pCount_personality_layout->addLayout(personality_layout);

    advancedModeBox = new QFrame(this);
    advancedModeBox->setHidden(true);
    advancedModeBox->setLayout(pCount_personality_layout);

    auto ratingLayout = new QHBoxLayout;
    ratingLayout->addWidget(lbl_rating);
    ratingLayout->addWidget(combo_rating);

    Final = new QGridLayout(this);
    Final->setContentsMargins(0, 0, 0, 0);
    Final->setAlignment(Qt::AlignCenter);
    Final->setColumnMinimumWidth(0, width() / 4);
    Final->setColumnMinimumWidth(1, width() / 4);
    Final->setColumnStretch(0, width() / 4);
    Final->setColumnStretch(1, width() / 4);
    Final->addWidget(line_name, 0, 0);
    Final->addWidget(combo_sex, 0, 1);
    Final->addWidget(lbl_rank, 2, 0);
    Final->addWidget(combo_type, 1, 0);
    Final->addWidget(cb_cantMate, 1, 1);
    Final->addLayout(wins_layout, 2, 1);
    Final->addLayout(accel_layout, 3, 0);
    Final->addLayout(stamina_layout, 3, 1);
    Final->addLayout(coop_layout, 4, 0);
    Final->addLayout(intel_layout, 4, 1);
    Final->addLayout(speed_layout, 5, 0, 1, 2);
    Final->addLayout(sprint_layout, 6, 0, 1, 2);
    Final->addLayout(ratingLayout, 7, 0, 1, 2);
    Final->addWidget(lblSpeedWarning, 8, 0, 2, 2, Qt::AlignCenter);
    Final->addWidget(advancedModeBox, 10, 0, 1, 2);
    Final->addItem(new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding), 11, 0, 1, 2);
    this->setLayout(Final);
    init_connections();
}

void ChocoboEditor::init_connections()
{
    connect(combo_sex, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int newSex) {
        if (choco_data.sex != newSex) {
            choco_data.sex = quint8(newSex);
            emit sexChanged(choco_data.sex);
        }
    });
    connect(combo_type, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int newType) {
        if (choco_data.type != newType) {
            choco_data.type = quint8(newType);
            emit typeChanged(choco_data.type);
        }
    });
    connect(line_name, &QLineEdit::textChanged, this, [this](QString newName) {
        if (newName != choco_name) {
            choco_name = newName.mid(0, 6);
            emit nameChanged(newName);
        }
    });
    connect(cb_cantMate, &QCheckBox::toggled, this, [this](bool checked) {
        if (choco_cant_mate != checked) {
            choco_cant_mate = checked;
            emit cantMateChanged(checked);
        }
    });
    connect(sb_speed, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int speed)    {
        if (choco_data.speed != speed) {
            choco_data.speed = quint16(speed);
            emit speedChanged(choco_data.speed);
        }
    });
    connect(sb_mSpeed, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int max_speed) {
        if (choco_data.maxspeed != max_speed) {
            choco_data.maxspeed = quint16(max_speed);
            emit mSpeedChanged(choco_data.maxspeed);
        }
    });
    connect(sb_sprint, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int sprint_speed)  {
        if (choco_data.sprintspd != sprint_speed) {
            choco_data.sprintspd = quint16(sprint_speed);
            emit sprintChanged(choco_data.sprintspd);
        }
    });
    connect(sb_mSprint, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int max_sprint_speed)    {
        if (choco_data.maxsprintspd != max_sprint_speed) {
            choco_data.maxsprintspd = quint16(max_sprint_speed);
            emit mSprintChanged(choco_data.maxsprintspd);
        }
    });
    connect(sb_accel, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int accel) {
        if (choco_data.accel != accel) {
            choco_data.accel = quint8(accel);
            emit accelChanged(choco_data.accel);
        }
    });
    connect(sb_stamina, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int stamina) {
        if (choco_stamina != stamina) {
            choco_stamina = quint16(stamina);
            emit staminaChanged(choco_stamina);
        }
    });
    connect(sb_wins, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int wins) {
        if (choco_data.raceswon != wins) {
            choco_data.raceswon = quint8(wins);
            getRank();
            emit winsChanged(choco_data.raceswon);
        }
    });
    connect(sb_coop, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int coop) {
        if (choco_data.coop != coop) {
            choco_data.coop = quint8(coop);
            emit coopChanged(choco_data.coop);
        }
    });
    connect(sb_intel, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int intel) {
        if (choco_data.intelligence != intel) {
            choco_data.intelligence = quint8(intel);
            emit intelligenceChanged(choco_data.intelligence);
        }
    });
    connect(sb_pCount, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int pCount) {
        if (choco_data.pcount != pCount) {
            choco_data.pcount = quint8(pCount);
            emit pCountChanged(choco_data.pcount);
        }
    });
    connect(sb_personality, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int personality) {
        //need to be researched further.
        if (choco_data.personality != personality) {
            choco_data.personality = quint8(personality);
            emit personalityChanged(choco_data.personality);
        }
    });

    connect(combo_rating, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int rating) {
        if (choco_rating != rating) {
            choco_rating = quint8(rating);
            emit ratingChanged(choco_rating);
        }
    });
}
void ChocoboEditor::SetChocobo(FF7CHOCOBO choco, const QString &Processed_Name, bool cant_mate, quint16 stamina, quint8 rating)
{
    setName(Processed_Name);
    setType(choco.type);
    setSex(choco.sex);
    setSpeed(choco.speed);
    setMspeed(choco.maxspeed);
    setSprint(choco.sprintspd);
    setMsprint(choco.maxsprintspd);
    setAccel(choco.accel);
    setWins(choco.raceswon);
    setPcount(choco.pcount);
    setCoop(choco.coop);
    setIntelligence(choco.intelligence);
    setPersonality(choco.personality);
    setStamina(stamina);
    setCantMate(cant_mate);
    setRating(rating);
}
void ChocoboEditor::getRank(void)
{
    if (choco_data.raceswon < 3) {
        lbl_rank->setText(tr("Rank: C"));
    } else if (choco_data.raceswon < 6) {
        lbl_rank->setText(tr("Rank: B"));
    } else if (choco_data.raceswon < 9) {
        lbl_rank->setText(tr("Rank: A"));
    } else {
        lbl_rank->setText(tr("Rank: S"));
    }
}

void ChocoboEditor::setAdvancedMode(bool advancedMode)
{
    advancedModeBox->setHidden(!advancedMode);
}

//Data Set Functions.
void ChocoboEditor::setRating(int rating)
{
    rating = std::clamp(rating, 0, 8);
    if (choco_rating != rating) {
        combo_rating->setCurrentIndex(rating);
        choco_rating = quint8(rating);
    }
}
void ChocoboEditor::setSprint(int sprint_speed)
{
    sprint_speed = std::clamp(sprint_speed, 0, 9999);
    if (choco_data.sprintspd != sprint_speed) {
        sb_sprint->setValue(sprint_speed);
        choco_data.sprintspd = quint16(sprint_speed);
    }
}
void ChocoboEditor::setMsprint(int max_sprint_speed)
{
    max_sprint_speed = std::clamp(max_sprint_speed, 0, 9999);
    if (choco_data.maxsprintspd != max_sprint_speed) {
        sb_mSprint->setValue(max_sprint_speed);
        choco_data.maxsprintspd = quint16(max_sprint_speed);
    }
}

void ChocoboEditor::setSpeed(int speed)
{
    speed = std::clamp(speed, 0, 9999);
    if (choco_data.speed != speed) {
        sb_speed->setValue(speed);
        choco_data.speed = quint16(speed);
    }
}

void ChocoboEditor::setMspeed(int max_speed)
{
    max_speed = std::clamp(max_speed, 0, 9999);
    if (choco_data.maxspeed != max_speed) {
        sb_mSpeed->setValue(max_speed);
        choco_data.maxspeed = quint16(max_speed);
    }
}

void ChocoboEditor::setStamina(int stamina)
{
    stamina = std::clamp(stamina, 0, 9999);
    if (choco_stamina != stamina) {
        sb_stamina->setValue(stamina);
        choco_stamina = quint16(stamina);
    }
}

void ChocoboEditor::setAccel(int accel)
{
    accel = std::clamp(accel, 0, 255);
    if (choco_data.accel != accel) {
        sb_accel->setValue(accel);
        choco_data.accel = quint8(accel);
    }
}

void ChocoboEditor::setCoop(int coop)
{
    coop = std::clamp(coop, 0, 255);
    if (choco_data.coop != coop) {
        sb_coop->setValue(coop);
        choco_data.coop = quint8(coop);
    }
}

void ChocoboEditor::setIntelligence(int intel)
{
    intel = std::clamp(intel, 0, 255);
    if (choco_data.intelligence != intel) {
        sb_intel->setValue(intel);
        choco_data.intelligence = quint8(intel);
    }
}

void ChocoboEditor::setPersonality(int personality)
{
    //need to be researched further.
    personality = std::clamp(personality, 0, 255);
    if (choco_data.personality != personality) {
        sb_personality->setValue(personality);
        choco_data.personality = quint8(personality);
    }
}

void ChocoboEditor::setPcount(int pCount)
{
    pCount = std::clamp(pCount, 0, 255);
    if (choco_data.pcount != pCount) {
        sb_pCount->setValue(pCount);
        choco_data.pcount = quint8(pCount);
    }
}

void ChocoboEditor::setWins(int wins)
{
    wins = std::clamp(wins, 0, 255);
    if (choco_data.raceswon != wins) {
        sb_wins->setValue(wins);
        choco_data.raceswon = quint8(wins);
        getRank();
    }
}
void ChocoboEditor::setSex(int sex)
{
    sex = std::clamp(sex, 0, 1);
    if (choco_data.sex != sex) {
        combo_sex->setCurrentIndex(sex);
        choco_data.sex = quint8(sex);
    }
}
void ChocoboEditor::setType(int type)
{
    type = std::clamp(type, 0, 4);
    if (choco_data.type != type) {
        combo_type->setCurrentIndex(type);
        choco_data.type = quint8(type);
    }
}
void ChocoboEditor::setName(const QString &newName)
{
    if (choco_name != newName) {
        choco_name = newName.mid(0, 6);
        if (choco_name.startsWith(QString("\xff"), Qt::CaseInsensitive) || choco_name == QString(6, '\x20')) {
            line_name->setText(QString());
        } else {
            line_name->setText(choco_name);
        }
    }
}

void ChocoboEditor::setCantMate(bool cantMate)
{
    if (choco_cant_mate != cantMate) {
        cb_cantMate->setChecked(cantMate);
        choco_cant_mate = cantMate;
    }
}

QSpinBox *ChocoboEditor::makeSpinBox(int maxValue)
{
    auto spinbox = new QSpinBox(this);
    spinbox->setWrapping(true);
    spinbox->setAlignment(Qt::AlignHCenter);
    spinbox->setMaximum(maxValue);
    return spinbox;
}

void ChocoboEditor::changeEvent(QEvent *e)
{
    if (e->type() != QEvent::LanguageChange) {
        QWidget::changeEvent(e);
    }
    updateText();
}
