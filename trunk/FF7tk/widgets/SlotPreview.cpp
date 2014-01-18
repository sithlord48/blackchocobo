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
#include "SlotPreview.h"
/*
#include "../static_data/icons/Common_Icons/quit.xpm"
#include "../static_data/icons/Common_Icons/copy.xpm"
#include "../static_data/icons/Common_Icons/paste.xpm"
*/
//Slot Preview Widget is for display of the previewed save data.
SlotPreview::SlotPreview(int index, QWidget *parent):QLabel(parent)
{
    Final = new QVBoxLayout();
    Final->setContentsMargins(2,2,2,2);
    setIndex(index);
    setLayout(Final);
    setFixedSize(581,135);
    setStyleSheet("SlotPreview{border:3px solid;}");
    setCursor(Qt::PointingHandCursor);
}

void SlotPreview::init_display(void)
{
    lbl_Slot = new QLabel;
    lbl_Slot->setText(QString(tr("Slot: %1")).arg(QString::number(index()+1)));

    btn_remove = new QPushButton(QIcon::fromTheme(QString("edit-clear"),QPixmap("://common/edit-clear")),"",this);
    btn_remove->setStyleSheet("QPushButton{border:1px solid;}");
    btn_remove->setToolTip(tr("Clear Slot"));
    btn_remove->setMaximumSize(22,22);
    btn_remove->setCursor(Qt::BitmapCursor);

    btn_copy = new QPushButton(QIcon::fromTheme(QString("edit-copy"),QPixmap("://common/edit-copy")),"",this);
    btn_copy->setStyleSheet("QPushButton{border:1px solid;}");
    btn_copy->setToolTip(tr("Copy Slot"));
    btn_copy->setMaximumSize(22,22);
    btn_copy->setCursor(Qt::BitmapCursor);

    btn_paste = new QPushButton(QIcon::fromTheme(QString("edit-paste"),QPixmap("://common/edit-paste")),"",this);
    btn_paste->setStyleSheet("QPushButton{border:1px solid;}");
    btn_paste->setToolTip(tr("Paste Into Slot"));
    btn_paste->setMaximumSize(22,22);
    btn_paste->setCursor(Qt::BitmapCursor);

    btnLayout = new QHBoxLayout;
    btnLayout->setContentsMargins(3,0,3,0);
    btnLayout->addWidget(lbl_Slot);
    btnLayout->addWidget(btn_copy);
    btnLayout->addWidget(btn_paste);
    btnLayout->addWidget(btn_remove);

    btn_remove->setHidden(true);
    btn_copy->setHidden(true);
    btn_paste->setHidden(true);

    connect(btn_remove,SIGNAL(clicked()),this,SLOT(removed()));
    connect(btn_copy,SIGNAL(clicked()),this,SLOT(copy()));
    connect(btn_paste,SIGNAL(clicked()),this,SLOT(paste()));
}
void SlotPreview::setMode(int mode)
{
    switch(mode)
    {
       case 0: set_empty(); break;
       case 1: set_psx_game();break;
       case 2: set_ff7_save();break;
    }
}
void SlotPreview::set_empty(void)
{
    init_display();
    btn_paste->setHidden(false);
    lbl_Slot->setStyleSheet(QString("font: 75 14pt \"Verdana\";"));
    QString style="font: 75 14pt \"Verdana\"; color:yellow;";
    location=new QLabel(tr("-Empty-"));
    location->setStyleSheet(style);
    QVBoxLayout *empty_layout = new QVBoxLayout;
    empty_layout->setContentsMargins(12,12,12,12);
    empty_layout->addWidget(location);
    top_layout = new QVBoxLayout;
    top_layout->setContentsMargins(6,0,0,0);
    top_layout->addLayout(btnLayout);
    top_layout->addItem(empty_layout);
    Final->addLayout(top_layout);
}

void SlotPreview::set_psx_game(void)
{
    init_display();
    lbl_Slot->setStyleSheet(QString("font: 75 14pt \"Verdana\";"));
    btn_remove->setHidden(false);
    btn_paste->setHidden(false);
    icon= new SaveIcon;
    QString style="font-size: 10pt;";
    party1 = new QLabel;
    party1->setFixedSize(90,100);
    party1->setScaledContents(1);
    connect(icon,SIGNAL(nextIcon(QPixmap)),party1,SLOT(setPixmap(QPixmap)));
    location = new QLabel;
    location->setStyleSheet(style);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(party1);
    layout->addWidget(location);
    top_layout= new QVBoxLayout;
    top_layout->setContentsMargins(6,0,0,0);
    top_layout->setSpacing(3);
    top_layout->addLayout(btnLayout);
    top_layout->addItem(layout);
    Final->addLayout(top_layout);
}

void SlotPreview::set_ff7_save(void)
{
    init_display();
    lbl_Slot->setStyleSheet("background-color:rgba(0,0,0,0);font: 75 14pt \"Verdana\";color:white");
    QString style="background-color:rbga(0,0,0,0);font: 75 14pt \"Verdana\"; color:white;";

    party1 = new QLabel;
    party1->setFixedSize(84,96);
    party1->setStyleSheet(style);

    party2 = new QLabel;
    party2->setFixedSize(84,96);
    party2->setStyleSheet(style);

    party3 = new QLabel;
    party3->setFixedSize(84,96);
    party3->setStyleSheet(style);

    lbl_gil = new QLabel;
    lbl_gil->setStyleSheet(style);
    lbl_gil->setAlignment(Qt::AlignCenter);

    name = new QLabel;
    name->setStyleSheet(style);
    name->setAlignment(Qt::AlignCenter);

    lbl_time = new QLabel;
    lbl_time->setStyleSheet(style);
    lbl_time->setAlignment(Qt::AlignCenter);

    lbl_level = new QLabel;
    lbl_level->setStyleSheet(style);
    lbl_level->setAlignment(Qt::AlignCenter);

    location = new QLabel;
    location->setStyleSheet(style);
    location->setAlignment(Qt::AlignCenter);

    QHBoxLayout *partybox = new QHBoxLayout;
    partybox->addWidget(party1);
    partybox->addWidget(party2);
    partybox->addWidget(party3);

    QHBoxLayout *levelgilbox = new QHBoxLayout;
    levelgilbox->setContentsMargins(0,0,0,0);
    levelgilbox->setSpacing(0);
    levelgilbox->addWidget(lbl_level);
    levelgilbox->addWidget(lbl_gil);

    QHBoxLayout *nametimebox =new QHBoxLayout;
    nametimebox->setContentsMargins(0,0,0,0);
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
    top_layout->setContentsMargins(6,0,0,0);
    top_layout->setSpacing(3);
    Final->addLayout(top_layout);
}

void SlotPreview::setParty(QPixmap p1,QPixmap p2,QPixmap p3)
{
    this->set_Party1(p1);
    this->set_Party2(p2);
    this->set_Party3(p3);
}

void SlotPreview::setParty(QString p1_style,QString p2_style,QString p3_style)
{
    this->set_Party1(p1_style);
    this->set_Party2(p2_style);
    this->set_Party3(p3_style);
}
void SlotPreview::setIndex(int index){this->setObjectName(QString::number(index));}
int SlotPreview::index(void){return this->objectName().toInt();}
void SlotPreview::set_Party1(QPixmap pix){party1->setPixmap(pix);}
void SlotPreview::set_Party1(QString style){party1->setStyleSheet(style);}
void SlotPreview::set_Party2(QPixmap pix){party2->setPixmap(pix);}
void SlotPreview::set_Party2(QString style){party2->setStyleSheet(style);}
void SlotPreview::set_Party3(QPixmap pix){party3->setPixmap(pix);}
void SlotPreview::set_Party3(QString style){party3->setStyleSheet(style);}
void SlotPreview::setName(QString Name){name->setText(Name);}
void SlotPreview::setLevel(int lvl){lbl_level->setText(QString(tr("Level:%1")).arg(QString::number(lvl)));}
void SlotPreview::setLocation(QString loc){location->setText(loc);}
void SlotPreview::setGil(int gil){lbl_gil->setText(QString(tr("Gil:%1")).arg(QString::number(gil)));}
void SlotPreview::setTime(int hr,int min){lbl_time->setText(QString(tr("Time:%1:%2")).arg(QString::number(hr),QString("%1").arg(QString::number(min),2,QChar('0'))));}
void SlotPreview::removed(void){emit btn_remove_clicked(index());}
void SlotPreview::copy(void){emit btn_copy_clicked(index());}
void SlotPreview::paste(void){emit btn_paste_clicked(index());}
void SlotPreview::setPsxIcon(QByteArray icon_data,quint8 frames){icon->setAll(icon_data,frames);party1->setPixmap(icon->icon());}
void SlotPreview::mousePressEvent(QMouseEvent *ev){if(ev->button() ==Qt::LeftButton){emit clicked(index());}}
