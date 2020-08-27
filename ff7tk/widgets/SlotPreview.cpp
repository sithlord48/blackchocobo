/****************************************************************************/
//    copyright 2012 -2020  Chris Rizzitello <sithlord48@gmail.com>         //
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
#include "SlotPreview.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>

#include "../data/SaveIcon.h"

SlotPreview::SlotPreview(int index, qreal Scale, QWidget *parent)
    : QLabel(parent)
    , scale(Scale)
    , m_index(index)
{
    Final = new QVBoxLayout();
    Final->setContentsMargins(2, 2, 2, 2);
    setLayout(Final);
    setFixedSize(int(582 * scale), int(135 * scale));
    setStyleSheet(_previewStyle);
    setCursor(Qt::PointingHandCursor);
}

void SlotPreview::init_display(void)
{
    lbl_Slot = new QLabel;
    lbl_Slot->setText(QString(tr("Slot: %1")).arg(QString::number(index() + 1)));

    btn_remove = new QPushButton(QIcon::fromTheme(QString("edit-clear"), QPixmap(":/common/edit-clear")), "", this);
    btn_remove->setToolTip(tr("Clear Slot"));
    connect(btn_remove, &QPushButton::clicked, this, [this] { emit btn_remove_clicked(m_index); });

    btn_copy = new QPushButton(QIcon::fromTheme(QString("edit-copy"), QPixmap(":/common/edit-copy")), "", this);
    btn_copy->setToolTip(tr("Copy Slot"));
    connect(btn_copy, &QPushButton::clicked, this, [this] { emit btn_copy_clicked(m_index); });

    btn_paste = new QPushButton(QIcon::fromTheme(QString("edit-paste"), QPixmap(":/common/edit-paste")), "", this);
    btn_paste->setToolTip(tr("Paste Into Slot"));
    connect(btn_paste, &QPushButton::clicked, this, [this] { emit btn_paste_clicked(m_index); });

    const QList<QPushButton*> buttons = findChildren<QPushButton *>();
    for (auto btn : buttons) {
        btn->setMaximumSize(int(22 * scale), int(22 * scale));
        btn->setCursor(Qt::BitmapCursor);
        btn->setHidden(true);
    }

    btnLayout = new QHBoxLayout;
    btnLayout->setContentsMargins(3, 0, 3, 0);
    btnLayout->addWidget(lbl_Slot);
    btnLayout->addWidget(btn_copy);
    btnLayout->addWidget(btn_paste);
    btnLayout->addWidget(btn_remove);
}

void SlotPreview::setMode(int mode)
{
    init_display();
    switch (mode) {
        case 0: set_empty(); break;
        case 1: set_psx_game(); break;
        case 2: set_ff7_save(); break;
    }
}
void SlotPreview::set_empty(void)
{
    btn_paste->setHidden(false);
    lbl_Slot->setStyleSheet(_genericStyle);
    location = new QLabel(tr("-Empty Slot-"));
    location->setAlignment(Qt::AlignCenter);
    location->setStyleSheet(_emptyTextStyle);
    QVBoxLayout *empty_layout = new QVBoxLayout;
    empty_layout->setContentsMargins(12, 12, 12, 12);
    empty_layout->addWidget(location);
    top_layout = new QVBoxLayout;
    top_layout->setContentsMargins(6, 0, 0, 0);
    top_layout->addLayout(btnLayout);
    top_layout->addItem(empty_layout);
    Final->addLayout(top_layout);
}

void SlotPreview::set_psx_game(void)
{
    lbl_Slot->setStyleSheet(_genericStyle);
    btn_remove->setHidden(false);
    btn_paste->setHidden(false);
    icon = new SaveIcon;
    party1 = new QLabel;
    party1->setScaledContents(true);
    party1->setFixedSize(int(96 * scale), int(96 * scale));
    connect (icon, &SaveIcon::nextIcon, party1, &QLabel::setPixmap);
    location = new QLabel;
    location->setStyleSheet(_genericStyle);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(party1);
    layout->addWidget(location);
    top_layout = new QVBoxLayout;
    top_layout->setContentsMargins(6, 0, 0, 0);
    top_layout->setSpacing(3);
    top_layout->addLayout(btnLayout);
    top_layout->addItem(layout);
    Final->addLayout(top_layout);

}

void SlotPreview::set_ff7_save(void)
{
    QSize avatarSize(int(84 * scale), int(96 * scale));

    party1 = new QLabel;
    party1->setFixedSize(avatarSize);

    party2 = new QLabel;
    party2->setFixedSize(avatarSize);

    party3 = new QLabel;
    party3->setFixedSize(avatarSize);

    lbl_gil = new QLabel;
    lbl_gil->setAlignment(Qt::AlignCenter);

    name = new QLabel;
    name->setAlignment(Qt::AlignCenter);

    lbl_time = new QLabel;
    lbl_time->setAlignment(Qt::AlignCenter);

    lbl_level = new QLabel;
    lbl_level->setAlignment(Qt::AlignCenter);

    location = new QLabel;
    location->setAlignment(Qt::AlignCenter);

    QHBoxLayout *partybox = new QHBoxLayout;
    partybox->addWidget(party1);
    partybox->addWidget(party2);
    partybox->addWidget(party3);

    QHBoxLayout *levelgilbox = new QHBoxLayout;
    levelgilbox->setContentsMargins(0, 0, 0, 0);
    levelgilbox->setSpacing(0);
    levelgilbox->addWidget(lbl_level);
    levelgilbox->addWidget(lbl_gil);

    QHBoxLayout *nametimebox = new QHBoxLayout;
    nametimebox->setContentsMargins(0, 0, 0, 0);
    nametimebox->setSpacing(0);
    nametimebox->addWidget(name);
    nametimebox->addWidget(lbl_time);

    QVBoxLayout *upperhalf = new QVBoxLayout;
    upperhalf->addLayout(nametimebox);
    upperhalf->addLayout(levelgilbox);
    upperhalf->addWidget(location);

    QHBoxLayout *midbox = new QHBoxLayout;
    midbox->addLayout(partybox);
    midbox->addLayout(upperhalf);

    btn_remove->setHidden(false);
    btn_paste->setHidden(false);
    btn_copy->setHidden(false);

    top_layout = new QVBoxLayout;
    top_layout->addLayout(btnLayout);
    top_layout->addLayout(midbox);
    top_layout->addWidget(lbl_Slot);
    top_layout->setContentsMargins(6, 0, 0, 0);
    top_layout->setSpacing(3);
    Final->addLayout(top_layout);

    const QList<QLabel*> labels = findChildren<QLabel *>();
    for (auto lbl : labels)
        lbl->setStyleSheet(_ff7SlotStyle);
}

void SlotPreview::setParty(QPixmap p1, QPixmap p2, QPixmap p3)
{
    party1->setPixmap(p1.scaled(party1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    party2->setPixmap(p2.scaled(party2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    party3->setPixmap(p3.scaled(party3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void SlotPreview::setParty(QString p1_style, QString p2_style, QString p3_style)
{
    party1->setStyleSheet(p1_style);
    party2->setStyleSheet(p2_style);
    party3->setStyleSheet(p3_style);
}

int SlotPreview::index(void)
{
    return m_index;
}

void SlotPreview::setName(QString Name)
{
    name->setText(Name);
}

void SlotPreview::setLevel(int lvl)
{
    lbl_level->setText(QString(tr("Level:%1")).arg(QString::number(lvl)));
}

void SlotPreview::setLocation(QString loc)
{
    location->setText(loc);
}

void SlotPreview::setGil(int gil)
{
    lbl_gil->setText(QString(tr("Gil:%1")).arg(QString::number(gil)));
}

void SlotPreview::setTime(int hr, int min)
{
    lbl_time->setText(QString(tr("Time:%1:%2")).arg(QString::number(hr), QString("%1").arg(QString::number(min), 2, QChar('0'))));
}

void SlotPreview::setPsxIcon(QByteArray icon_data, quint8 frames)
{
    icon->setAll(icon_data, frames);
    party1->setPixmap(icon->icon());
}

void SlotPreview::setPsxIcon(QList<QByteArray> icon_data)
{
    icon->setAll(icon_data);
    party1->setPixmap(icon->icon());
}

void SlotPreview::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        emit clicked(index());
}
