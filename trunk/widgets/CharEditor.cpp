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
#include "CharEditor.h"
//#include <QMessageBox>
CharEditor::CharEditor(QWidget *parent) :
    QWidget(parent)
{
    init_display();
    init_connections();
    //auto level and auto stat calc are enabled by default.
    //always check them when doing these actions.

    autolevel=true;
    autostatcalc=true;
    editable=true;
    mslotsel =0;
    //init the data..(just incase)
    //_name= "Cloud";
    //QByteArray temp;
    //temp.fill(0x00,132);
    //memcpy(&data,temp,132);

    //data.accessory = 0xFF;
    //data.weapon = 0;
    //data.armor =0;
    //setChar(data,_name);
 }
void CharEditor::init_display()
{
    lbl_avatar = new QLabel;
    lbl_avatar->setFixedSize(86,98);
    //lbl_avatar->setContextMenuPolicy(Qt::CustomContextMenu);
    line_name = new QLineEdit;
    lbl_level = new QLabel(tr("Level"));
    lbl_kills = new QLabel(tr("Kills"));
    lbl_hp = new QLabel(tr("HP"));
    lbl_mp = new QLabel(tr("MP"));
    lbl_mp_slash = new QLabel("/");
    lbl_hp_slash = new QLabel("/");
    sb_level = new QSpinBox;
    sb_curMp = new QSpinBox;
    sb_curHp = new QSpinBox;
    sb_maxMp = new QSpinBox;
    sb_maxHp = new QSpinBox;
    sb_kills = new QSpinBox;
    cb_fury=new QCheckBox(tr("Fury"));
    cb_sadness = new QCheckBox(tr("Sadness"));
    cb_front_row = new QCheckBox(tr("Front Row"));
    lbl_id = new QLabel(tr("ID"));
    combo_id = new QComboBox;
    for(int i=0;i<11;i++){combo_id->addItem(Chars.Icon(i),Chars.defaultName(i));}

    lbl_base_hp = new QLabel(tr("Base HP"));
    lbl_base_hp_bonus = new QLabel;
    lbl_base_hp->setFixedWidth(this->font().pointSize()*6);
    lbl_base_hp_bonus->setFixedWidth(this->font().pointSize()*5);
    sb_base_hp = new QSpinBox;
    sb_base_hp->setFixedWidth(this->font().pointSize()*7);

    lbl_base_mp = new QLabel(tr("Base MP"));
    lbl_base_mp_bonus = new QLabel;
    sb_base_mp = new QSpinBox;
    lbl_base_mp->setFixedWidth(this->font().pointSize()*6);
    lbl_base_mp_bonus->setFixedWidth(this->font().pointSize()*5);
    sb_base_mp->setFixedWidth(this->font().pointSize()*7);

    lbl_total_xp = new QLabel(tr("Total Exp"));
    lbl_level_progress = new QLabel(tr("Level Progress"));
    bar_tnl = new QProgressBar;
    bar_tnl->setMaximum(61);//strange indeed..
    bar_tnl->setTextVisible(false);
    lbl_level_next = new QLabel(tr("Next"));
    sb_total_exp = new QSpinBox;
    sb_total_exp->setMaximum(2147483647);

    lcd_tnl = new QLCDNumber;
    lcd_tnl->setNumDigits(8);
    lcd_tnl->setSegmentStyle(QLCDNumber::Flat);
    lbl_limit_bar = new QLabel (tr("Limit Bar"));
    slider_limit = new QSlider;
    slider_limit->setMaximum(255);
    slider_limit->setOrientation(Qt::Horizontal);
    lcd_limit_value = new QLCDNumber;


    lbl_str = new QLabel(tr("Str"));
    sb_str = new QSpinBox;
    sb_str->setAlignment(Qt::AlignCenter);
    QLabel *lbl_str_plus_1 = new QLabel(tr("+"));
    lbl_str_plus_1->setAlignment(Qt::AlignCenter);
    sb_str_bonus = new QSpinBox;
    sb_str_bonus->setAlignment(Qt::AlignCenter);
    QLabel *lbl_str_plus_2 = new QLabel(tr("+"));
    lbl_str_plus_2->setAlignment(Qt::AlignCenter);
    lbl_str_mat_bonus = new QLabel;
    QLabel *lbl_str_equals = new QLabel(tr("="));
    lbl_str_total = new QLabel;

    lbl_vit = new QLabel(tr("Vit"));
    sb_vit = new QSpinBox;
    sb_vit->setAlignment(Qt::AlignCenter);
    QLabel *lbl_vit_plus_1 = new QLabel(tr("+"));
    lbl_vit_plus_1->setAlignment(Qt::AlignCenter);
    sb_vit_bonus = new QSpinBox;
    sb_vit_bonus->setAlignment(Qt::AlignCenter);
    QLabel *lbl_vit_plus_2 = new QLabel(tr("+"));
    lbl_vit_plus_2->setAlignment(Qt::AlignCenter);
    lbl_vit_mat_bonus = new QLabel;
    QLabel *lbl_vit_equals = new QLabel(tr("="));
    lbl_vit_total = new QLabel;

    lbl_mag = new QLabel(tr("Mag"));
    sb_mag = new QSpinBox;
    sb_mag->setAlignment(Qt::AlignCenter);
    QLabel *lbl_mag_plus_1 = new QLabel(tr("+"));
    lbl_mag_plus_1->setAlignment(Qt::AlignCenter);
    sb_mag_bonus = new QSpinBox;
    sb_mag_bonus->setAlignment(Qt::AlignCenter);
    QLabel *lbl_mag_plus_2 = new QLabel(tr("+"));
    lbl_mag_plus_2->setAlignment(Qt::AlignCenter);
    lbl_mag_mat_bonus = new QLabel;
    QLabel *lbl_mag_equals = new QLabel(tr("="));
    lbl_mag_total = new QLabel;

    lbl_spi = new QLabel(tr("Spi"));
    sb_spi = new QSpinBox;
    sb_spi->setAlignment(Qt::AlignCenter);
    QLabel *lbl_spi_plus_1 = new QLabel(tr("+"));
    lbl_spi_plus_1->setAlignment(Qt::AlignCenter);
    sb_spi_bonus = new QSpinBox;
    sb_spi_bonus->setAlignment(Qt::AlignCenter);
    QLabel *lbl_spi_plus_2 = new QLabel(tr("+"));
    lbl_spi_plus_2->setAlignment(Qt::AlignCenter);
    lbl_spi_mat_bonus = new QLabel;
    QLabel *lbl_spi_equals = new QLabel(tr("="));
    lbl_spi_total = new QLabel;

    lbl_dex = new QLabel(tr("Dex"));
    sb_dex = new QSpinBox;
    sb_dex->setAlignment(Qt::AlignCenter);
    QLabel *lbl_dex_plus_1 = new QLabel(tr("+"));
    lbl_dex_plus_1->setAlignment(Qt::AlignCenter);
    sb_dex_bonus = new QSpinBox;
    sb_dex_bonus->setAlignment(Qt::AlignCenter);
    QLabel *lbl_dex_plus_2 = new QLabel(tr("+"));
    lbl_dex_plus_2->setAlignment(Qt::AlignCenter);
    lbl_dex_mat_bonus = new QLabel;
    QLabel *lbl_dex_equals = new QLabel(tr("="));
    lbl_dex_total = new QLabel;

    lbl_lck = new QLabel(tr("Lck"));
    sb_lck = new QSpinBox;
    sb_lck->setAlignment(Qt::AlignCenter);
    QLabel *lbl_lck_plus_1 = new QLabel(tr("+"));
    lbl_lck_plus_1->setAlignment(Qt::AlignCenter);
    sb_lck_bonus = new QSpinBox;
    sb_lck_bonus->setAlignment(Qt::AlignCenter);
    QLabel *lbl_lck_plus_2 = new QLabel(tr("+"));
    lbl_lck_plus_2->setAlignment(Qt::AlignCenter);
    lbl_lck_mat_bonus = new QLabel;
    QLabel *lbl_lck_equals = new QLabel(tr("="));
    lbl_lck_total = new QLabel;

    //Spin Boxes for limit uses.
    sb_uses_limit_1_1 = new QSpinBox;
    sb_uses_limit_2_1 = new QSpinBox;
    sb_uses_limit_3_1 = new QSpinBox;
    sb_uses_limit_1_1->setFixedWidth(this->font().pointSize()*7);
    sb_uses_limit_2_1->setFixedWidth(this->font().pointSize()*7);
    sb_uses_limit_3_1->setFixedWidth(this->font().pointSize()*7);


    lbl_uses = new QLabel(tr("Limit Uses"));
    lbl_uses->setAlignment(Qt::AlignHCenter);
    lbl_1_1 = new QLabel(tr("1-1"));
    lbl_2_1 = new QLabel(tr("2-1"));
    lbl_3_1 = new QLabel(tr("3-1"));
    lbl_1_1->setFixedWidth(this->font().pointSize()*3);
    lbl_2_1->setFixedWidth(this->font().pointSize()*3);
    lbl_3_1->setFixedWidth(this->font().pointSize()*3);
    lbl_1_1->setAlignment(Qt::AlignHCenter);
    lbl_2_1->setAlignment(Qt::AlignHCenter);
    lbl_3_1->setAlignment(Qt::AlignHCenter);


    QVBoxLayout *layout_1_1 = new QVBoxLayout;
    layout_1_1->setContentsMargins(0,0,0,0);
    layout_1_1->setSpacing(3);
    layout_1_1->addWidget(lbl_1_1);
    layout_1_1->addWidget(sb_uses_limit_1_1);

    QVBoxLayout *layout_2_1 = new QVBoxLayout;
    layout_2_1->setContentsMargins(0,0,0,0);
    layout_2_1->setSpacing(3);
    layout_2_1->addWidget(lbl_2_1);
    layout_2_1->addWidget(sb_uses_limit_2_1);
    QVBoxLayout *layout_3_1 = new QVBoxLayout;
    layout_3_1->setContentsMargins(0,0,0,0);
    layout_3_1->setSpacing(3);
    layout_3_1->addWidget(lbl_3_1);
    layout_3_1->addWidget(sb_uses_limit_3_1);


    QHBoxLayout *used_layout = new QHBoxLayout;
    used_layout->setContentsMargins(0,0,0,0);
    used_layout->setSpacing(3);
    used_layout->addLayout(layout_1_1);
    used_layout->addLayout(layout_2_1);
    used_layout->addLayout(layout_3_1);

    QVBoxLayout *used_limits_layout = new QVBoxLayout;
    used_limits_layout->setContentsMargins(0,0,0,0);
    used_limits_layout->setSpacing(3);
    used_limits_layout->addWidget(lbl_uses);
    used_limits_layout->addLayout(used_layout);

    list_limits = new QListWidget;
    lbl_limit_level = new QLabel(tr("Limit Level"));
    sb_limit_level = new QSpinBox;
    sb_limit_level->setFixedWidth(this->font().pointSize()*4);



    QHBoxLayout *limit_level_layout = new QHBoxLayout;
    limit_level_layout->setContentsMargins(0,36,0,0);//push it far down so it lines up w/ the uses section
    QSpacerItem *limitSpacer = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    limit_level_layout->addSpacerItem(limitSpacer);
    limit_level_layout->addWidget(lbl_limit_level);
    limit_level_layout->addWidget(sb_limit_level);


    sb_level->setMaximum(99);
    sb_curMp->setMaximum(32767);
    sb_curHp->setMaximum(32767);
    sb_maxMp->setMaximum(32767);
    sb_maxHp->setMaximum(32767);
    sb_base_hp->setMaximum(32767);
    sb_base_mp->setMaximum(32767);
    sb_kills->setMaximum(65535);
    sb_str->setMaximum(255);
    sb_str_bonus->setMaximum(255);
    sb_vit->setMaximum(255);
    sb_vit_bonus->setMaximum(255);
    sb_mag->setMaximum(255);
    sb_mag_bonus->setMaximum(255);
    sb_spi->setMaximum(255);
    sb_spi_bonus->setMaximum(255);
    sb_dex->setMaximum(255);
    sb_dex_bonus->setMaximum(255);
    sb_lck->setMaximum(255);
    sb_lck_bonus->setMaximum(255);
    sb_limit_level->setMaximum(4);
    sb_uses_limit_1_1->setMaximum(32767);
    sb_uses_limit_2_1->setMaximum(32767);
    sb_uses_limit_3_1->setMaximum(32767);
    line_name->setMaxLength(12);
    line_name->setMaximumWidth(this->font().pointSize()*12);
    bar_tnl->setMaximumWidth(line_name->width()*1.5);
    QHBoxLayout * name_level_layout= new QHBoxLayout;
    name_level_layout->addWidget(line_name);
    QSpacerItem *name_spacer = new QSpacerItem(20,0,QSizePolicy::Fixed,QSizePolicy::Fixed);
    name_level_layout->addSpacerItem(name_spacer);
    name_level_layout->addWidget(lbl_level);
    name_level_layout->addWidget(sb_level);

    QHBoxLayout *hp_layout = new QHBoxLayout;
    hp_layout->addWidget(lbl_hp);
    hp_layout->addWidget(sb_curHp);
    hp_layout->addWidget(lbl_hp_slash);
    hp_layout->addWidget(sb_maxHp);
    QSpacerItem *hp_spacer1 = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    hp_layout->addSpacerItem(hp_spacer1);
    QSpacerItem *hp_spacer = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    hp_layout->addSpacerItem(hp_spacer);

    QHBoxLayout *mp_layout = new QHBoxLayout;
    mp_layout->addWidget(lbl_mp);
    mp_layout->addWidget(sb_curMp);
    mp_layout->addWidget(lbl_mp_slash);
    mp_layout->addWidget(sb_maxMp);
    QSpacerItem *mp_spacer1 = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    mp_layout->addSpacerItem(mp_spacer1);
    QSpacerItem *mp_spacer = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    mp_layout->addSpacerItem(mp_spacer);


    QHBoxLayout *exp_layout = new QHBoxLayout;
    exp_layout->setContentsMargins(0,12,0,0);
    exp_layout->addWidget(lbl_total_xp);
    exp_layout->addWidget(sb_total_exp);

    QHBoxLayout *kills_layout = new QHBoxLayout;
    kills_layout->addWidget(lbl_kills);
    kills_layout->addWidget(sb_kills);
    QSpacerItem *kills_spacer1 = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    kills_layout->addSpacerItem(kills_spacer1);
    QSpacerItem *kills_spacer = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    kills_layout->addSpacerItem(kills_spacer);


    QVBoxLayout *name_hp_mp_kills_layout = new QVBoxLayout;
    name_hp_mp_kills_layout->addLayout(name_level_layout);
    name_hp_mp_kills_layout->addLayout(hp_layout);
    name_hp_mp_kills_layout->addLayout(mp_layout);
    name_hp_mp_kills_layout->addLayout(kills_layout);


    QVBoxLayout *fury_sadness_layout = new QVBoxLayout;
    fury_sadness_layout->setContentsMargins(0,0,0,0);
    fury_sadness_layout->setSpacing(2);
    fury_sadness_layout->addWidget(cb_fury);
    fury_sadness_layout->addWidget(cb_sadness);


    QFrame *frm_fury_sadness =new QFrame;
    frm_fury_sadness->setLayout(fury_sadness_layout);

    QHBoxLayout *id_layout = new QHBoxLayout;
    id_layout->setContentsMargins(0,0,0,0);
    id_layout->addWidget(lbl_id);
    id_layout->addWidget(combo_id);

    QVBoxLayout *level_next_layout = new QVBoxLayout;
    level_next_layout->setContentsMargins(0,0,0,0);
    level_next_layout->addWidget(lbl_level_next);
    level_next_layout->addWidget(lcd_tnl);

    QVBoxLayout *sadness_row_id_layout =new QVBoxLayout;
    sadness_row_id_layout->addWidget(frm_fury_sadness);
    sadness_row_id_layout->addWidget(cb_front_row);
    sadness_row_id_layout->addLayout(id_layout);

    QHBoxLayout *avatar_name_layout = new QHBoxLayout;
    avatar_name_layout->addWidget(lbl_avatar);
    avatar_name_layout->addLayout(name_hp_mp_kills_layout);
    avatar_name_layout->addLayout(sadness_row_id_layout);

    QVBoxLayout *level_bar_layout = new QVBoxLayout;
    level_bar_layout->setContentsMargins(0,0,0,0);
    level_bar_layout->addWidget(lbl_level_progress);
    level_bar_layout->addWidget(bar_tnl);

    QHBoxLayout *level_progress_layout = new QHBoxLayout;
    level_progress_layout->addLayout(level_bar_layout);
    level_progress_layout->addLayout(level_next_layout);


    QHBoxLayout *limit_bar_layout = new QHBoxLayout;
    limit_bar_layout->setContentsMargins(0,0,0,0);
    limit_bar_layout->addWidget(lbl_limit_bar);
    limit_bar_layout->addWidget(slider_limit);
    limit_bar_layout->addWidget(lcd_limit_value);

    QHBoxLayout *level_exp_limit_layout = new QHBoxLayout;
    level_exp_limit_layout->setContentsMargins(0,0,0,0);
    level_exp_limit_layout->addLayout(exp_layout);
    level_exp_limit_layout->addLayout(level_progress_layout);

    QHBoxLayout *str_layout = new QHBoxLayout;
    str_layout->setContentsMargins(0,0,0,0);
    str_layout->addWidget(lbl_str);
    str_layout->addWidget(sb_str);
    str_layout->addWidget(lbl_str_plus_1);
    str_layout->addWidget(sb_str_bonus);
    str_layout->addWidget(lbl_str_plus_2);
    str_layout->addWidget(lbl_str_mat_bonus);
    str_layout->addWidget(lbl_str_equals);
    str_layout->addWidget(lbl_str_total);

    QHBoxLayout *vit_layout = new QHBoxLayout;
    vit_layout->setContentsMargins(0,0,0,0);
    vit_layout->addWidget(lbl_vit);
    vit_layout->addWidget(sb_vit);
    vit_layout->addWidget(lbl_vit_plus_1);
    vit_layout->addWidget(sb_vit_bonus);
    vit_layout->addWidget(lbl_vit_plus_2);
    vit_layout->addWidget(lbl_vit_mat_bonus);
    vit_layout->addWidget(lbl_vit_equals);
    vit_layout->addWidget(lbl_vit_total);

    QHBoxLayout *mag_layout = new QHBoxLayout;
    mag_layout->setContentsMargins(0,0,0,0);
    mag_layout->addWidget(lbl_mag);
    mag_layout->addWidget(sb_mag);
    mag_layout->addWidget(lbl_mag_plus_1);
    mag_layout->addWidget(sb_mag_bonus);
    mag_layout->addWidget(lbl_mag_plus_2);
    mag_layout->addWidget(lbl_mag_mat_bonus);
    mag_layout->addWidget(lbl_mag_equals);
    mag_layout->addWidget(lbl_mag_total);

    QHBoxLayout *spi_layout = new QHBoxLayout;
    spi_layout->setContentsMargins(0,0,0,0);
    spi_layout->addWidget(lbl_spi);
    spi_layout->addWidget(sb_spi);
    spi_layout->addWidget(lbl_spi_plus_1);
    spi_layout->addWidget(sb_spi_bonus);
    spi_layout->addWidget(lbl_spi_plus_2);
    spi_layout->addWidget(lbl_spi_mat_bonus);
    spi_layout->addWidget(lbl_spi_equals);
    spi_layout->addWidget(lbl_spi_total);

    QHBoxLayout *dex_layout = new QHBoxLayout;
    dex_layout->setContentsMargins(0,0,0,0);
    dex_layout->addWidget(lbl_dex);
    dex_layout->addWidget(sb_dex);
    dex_layout->addWidget(lbl_dex_plus_1);
    dex_layout->addWidget(sb_dex_bonus);
    dex_layout->addWidget(lbl_dex_plus_2);
    dex_layout->addWidget(lbl_dex_mat_bonus);
    dex_layout->addWidget(lbl_dex_equals);
    dex_layout->addWidget(lbl_dex_total);

    QHBoxLayout *lck_layout = new QHBoxLayout;
    lck_layout->setContentsMargins(0,0,0,0);
    lck_layout->addWidget(lbl_lck);
    lck_layout->addWidget(sb_lck);
    lck_layout->addWidget(lbl_lck_plus_1);
    lck_layout->addWidget(sb_lck_bonus);
    lck_layout->addWidget(lbl_lck_plus_2);
    lck_layout->addWidget(lbl_lck_mat_bonus);
    lck_layout->addWidget(lbl_lck_equals);
    lck_layout->addWidget(lbl_lck_total);

    QSpacerItem *base_hp_spacer = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    QHBoxLayout *base_hp_layout = new QHBoxLayout;
    base_hp_layout->setContentsMargins(0,0,0,0);
    base_hp_layout->addWidget(lbl_base_hp);
    base_hp_layout->addWidget(sb_base_hp);
    base_hp_layout->addWidget(lbl_base_hp_bonus);
    base_hp_layout->addSpacerItem(base_hp_spacer);

    QSpacerItem *base_mp_spacer = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    QHBoxLayout *base_mp_layout = new QHBoxLayout;
    base_mp_layout->setContentsMargins(0,0,0,0);
    base_mp_layout->addWidget(lbl_base_mp);
    base_mp_layout->addWidget(sb_base_mp);
    base_mp_layout->addWidget(lbl_base_mp_bonus);
    base_mp_layout->addSpacerItem(base_mp_spacer);

    QHBoxLayout *base_hp_mp_layout = new QHBoxLayout;
    base_hp_mp_layout->setContentsMargins(0,0,0,0);
    base_hp_mp_layout->setSpacing(3);
    base_hp_mp_layout->addLayout(base_hp_layout);
    base_hp_mp_layout->addLayout(base_mp_layout);

    QVBoxLayout *stat_layout = new QVBoxLayout;
    stat_layout->setContentsMargins(0,3,0,0);
    stat_layout->setSpacing(3);
    stat_layout->addLayout(str_layout);
    stat_layout->addLayout(vit_layout);
    stat_layout->addLayout(mag_layout);
    stat_layout->addLayout(spi_layout);
    stat_layout->addLayout(dex_layout);
    stat_layout->addLayout(lck_layout);
    stat_layout->addLayout(base_hp_mp_layout);

    QGroupBox *stat_box= new QGroupBox;
    //stat_box->setFixedHeight(this->font().pointSize()*22);
    stat_box->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::MinimumExpanding);
    stat_box->setLayout(stat_layout);

    QHBoxLayout *limit_uses_level_layout = new QHBoxLayout;
    limit_uses_level_layout->setContentsMargins(0,0,0,0);
    limit_uses_level_layout->setSpacing(3);
    limit_uses_level_layout->addLayout(limit_level_layout);
    limit_uses_level_layout->addLayout(used_limits_layout);

    QVBoxLayout *limit_box = new QVBoxLayout;
    limit_box->addLayout(limit_uses_level_layout);
    limit_box->addLayout(limit_bar_layout);
    limit_box->addWidget(list_limits);


    QVBoxLayout *lower_section = new QVBoxLayout;
    lower_section->setContentsMargins(0,0,0,0);
    lower_section->addWidget(stat_box);
    //lower_section->addLayout(limit_box);


    QVBoxLayout *left_Final = new QVBoxLayout;
    left_Final->setContentsMargins(0,0,0,0);
    //left_Final->addLayout(avatar_name_layout);
    left_Final->addLayout(level_exp_limit_layout);
    left_Final->addLayout(lower_section);



    weapon_selection = new QComboBox;

    armor_selection = new QComboBox;
    for(int i=256;i<288;i++){armor_selection->addItem(QPixmap::fromImage(Items.Image(i)),Items.Name(i));}

    accessory_selection = new QComboBox;
    for(int i=288;i<320;i++){accessory_selection->addItem(QPixmap::fromImage(Items.Image(i)),Items.Name(i));}
    accessory_selection->addItem(QPixmap::fromImage(Items.Image(288)),tr("-NONE-"));
    materia_edit  = new MateriaEditor;
    materia_edit->setStarsSize(32);

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

    //set up materia slots and box for weapon.
    weapon_materia_box = new QGroupBox;
    weapon_materia_box->setFixedHeight(50);
    QSpacerItem *weapon_spacer=new QSpacerItem(-1,-1,QSizePolicy::Expanding,QSizePolicy::Minimum);
    //I Like the No Growth Slots They Look Better so i always use them
    // you can use FF7Item::Style_m_grow_slot() to get the style of that slot

    weapon_slot_1 = new QPushButton();
    weapon_slot_1->setFixedSize(32,32);
    weapon_slot_1->setIconSize(QSize(32,32));
    weapon_slot_1->setStyleSheet(Items.Style_m_no_grow_slot());
    weapon_slot_1->setHidden(1);

    weapon_m_link_1= new QLabel();
    weapon_m_link_1->setFixedSize(12,16);

    weapon_slot_2 = new QPushButton();
    weapon_slot_2->setFixedSize(32,32);
    weapon_slot_2->setIconSize(QSize(32,32));
    weapon_slot_2->setStyleSheet(Items.Style_m_no_grow_slot());
    weapon_slot_2->setHidden(1);

    QHBoxLayout *weapon_slots_1_and_2 = new QHBoxLayout();
    weapon_slots_1_and_2->setContentsMargins(0,0,0,0);
    weapon_slots_1_and_2->addWidget(weapon_slot_1);
    weapon_slots_1_and_2->addWidget(weapon_m_link_1);
    weapon_slots_1_and_2->addWidget(weapon_slot_2);
    weapon_slots_1_and_2->setSpacing(0);

    weapon_slot_3 = new QPushButton();
    weapon_slot_3->setFixedSize(32,32);
    weapon_slot_3->setFlat(true);
    weapon_slot_3->setAutoFillBackground(true);
    weapon_slot_3->setIconSize(QSize(32,32));
    weapon_slot_3->setStyleSheet(Items.Style_m_no_grow_slot());
    weapon_slot_3->setHidden(1);

    weapon_m_link_2 = new QLabel();
    weapon_m_link_2->setFixedSize(12,16);
    weapon_m_link_2->setScaledContents(1);

    weapon_slot_4 = new QPushButton();
    weapon_slot_4->setFixedSize(32,32);
    weapon_slot_1->setStyleSheet(Items.Style_m_no_grow_slot());
    weapon_slot_4->setFlat(true);
    weapon_slot_4->setAutoFillBackground(true);
    weapon_slot_4->setIconSize(QSize(32,32));
    weapon_slot_4->setStyleSheet(Items.Style_m_no_grow_slot());
    weapon_slot_4->setHidden(1);

    QHBoxLayout *weapon_slots_3_and_4 = new QHBoxLayout();
    weapon_slots_3_and_4->setContentsMargins(0,0,0,0);
    weapon_slots_3_and_4->addWidget(weapon_slot_3);
    weapon_slots_3_and_4->addWidget(weapon_m_link_2);
    weapon_slots_3_and_4->addWidget(weapon_slot_4);
    weapon_slots_3_and_4->setSpacing(0);

    weapon_slot_5 = new QPushButton();
    weapon_slot_5->setFixedSize(32,32);
    weapon_slot_5->setFlat(true);
    weapon_slot_5->setAutoFillBackground(true);
    weapon_slot_5->setIconSize(QSize(32,32));
    weapon_slot_5->setStyleSheet(Items.Style_m_no_grow_slot());
    weapon_slot_5->setHidden(1);

    weapon_m_link_3 = new QLabel();
    weapon_m_link_3->setFixedSize(12,16);
    weapon_m_link_3->setScaledContents(1);

    weapon_slot_6 = new QPushButton();
    weapon_slot_6->setFixedSize(32,32);
    weapon_slot_6->setFlat(true);
    weapon_slot_6->setAutoFillBackground(true);
    weapon_slot_6->setIconSize(QSize(32,32));
    weapon_slot_6->setStyleSheet(Items.Style_m_no_grow_slot());
    weapon_slot_6->setHidden(1);

    QHBoxLayout *weapon_slots_5_and_6 = new QHBoxLayout();
    weapon_slots_5_and_6->setContentsMargins(0,0,0,0);
    weapon_slots_5_and_6->addWidget(weapon_slot_5);
    weapon_slots_5_and_6->addWidget(weapon_m_link_3);
    weapon_slots_5_and_6->addWidget(weapon_slot_6);
    weapon_slots_5_and_6->setSpacing(0);

    weapon_slot_7 = new QPushButton();
    weapon_slot_7->setFixedSize(32,32);
    weapon_slot_7->setFlat(true);
    weapon_slot_7->setAutoFillBackground(true);
    weapon_slot_7->setIconSize(QSize(32,32));
    weapon_slot_7->setStyleSheet(Items.Style_m_no_grow_slot());
    weapon_slot_7->setHidden(1);

    weapon_m_link_4 = new QLabel();
    weapon_m_link_4->setFixedSize(12,16);
    weapon_m_link_4->setScaledContents(1);

    weapon_slot_8 = new QPushButton();
    weapon_slot_8->setFixedSize(32,32);
    weapon_slot_8->setFlat(true);
    weapon_slot_8->setAutoFillBackground(true);
    weapon_slot_8->setIconSize(QSize(32,32));
    weapon_slot_8->setStyleSheet(Items.Style_m_no_grow_slot());
    weapon_slot_8->setHidden(1);

    QHBoxLayout *weapon_slots_7_and_8 = new QHBoxLayout();
    weapon_slots_7_and_8->setContentsMargins(0,0,0,0);
    weapon_slots_7_and_8->addWidget(weapon_slot_7);
    weapon_slots_7_and_8->addWidget(weapon_m_link_4);
    weapon_slots_7_and_8->addWidget(weapon_slot_8);
    weapon_slots_7_and_8->setSpacing(0);

    QHBoxLayout *weapon_materia_slots = new QHBoxLayout();
    weapon_materia_slots->setContentsMargins(0,0,0,0);
    weapon_materia_slots->addLayout(weapon_slots_1_and_2);
    weapon_materia_slots->addLayout(weapon_slots_3_and_4);
    weapon_materia_slots->addLayout(weapon_slots_5_and_6);
    weapon_materia_slots->addLayout(weapon_slots_7_and_8);
    weapon_materia_slots->addSpacerItem(weapon_spacer);
    weapon_materia_slots->setSpacing(12);

    weapon_materia_box->setLayout(weapon_materia_slots);

    //set up armor materia buttons.
    armor_materia_box = new QGroupBox;
    armor_materia_box->setFixedHeight(50);
    QSpacerItem *armor_spacer=new QSpacerItem(-1,-1,QSizePolicy::Expanding,QSizePolicy::Minimum);
    //I Like the No Growth Slots They Look Better so i always use them
    // you can use FF7Item::Style_m_grow_slot() to get the style of that slot

    armor_slot_1 = new QPushButton();
    armor_slot_1->setFixedSize(32,32);
    armor_slot_1->setFlat(true);
    armor_slot_1->setAutoFillBackground(true);
    armor_slot_1->setIconSize(QSize(32,32));
    armor_slot_1->setStyleSheet(Items.Style_m_no_grow_slot());
    armor_slot_1->setHidden(1);

    armor_m_link_1= new QLabel();
    armor_m_link_1->setFixedSize(12,16);

    armor_slot_2 = new QPushButton();
    armor_slot_2->setFixedSize(32,32);
    armor_slot_2->setFlat(true);
    armor_slot_2->setAutoFillBackground(true);
    armor_slot_2->setIconSize(QSize(32,32));
    armor_slot_2->setStyleSheet(Items.Style_m_no_grow_slot());
    armor_slot_2->setHidden(1);

    QHBoxLayout *armor_slots_1_and_2 = new QHBoxLayout();
    armor_slots_1_and_2->setContentsMargins(0,0,0,0);
    armor_slots_1_and_2->addWidget(armor_slot_1);
    armor_slots_1_and_2->addWidget(armor_m_link_1);
    armor_slots_1_and_2->addWidget(armor_slot_2);
    armor_slots_1_and_2->setSpacing(0);

    armor_slot_3 = new QPushButton();
    armor_slot_3->setFixedSize(32,32);
    armor_slot_3->setFlat(true);
    armor_slot_3->setAutoFillBackground(true);
    armor_slot_3->setIconSize(QSize(32,32));
    armor_slot_3->setStyleSheet(Items.Style_m_no_grow_slot());
    armor_slot_3->setHidden(1);

    armor_m_link_2 = new QLabel();
    armor_m_link_2->setFixedSize(12,16);
    armor_m_link_2->setScaledContents(1);

    armor_slot_4 = new QPushButton();
    armor_slot_4->setFixedSize(32,32);
    armor_slot_1->setStyleSheet(Items.Style_m_no_grow_slot());
    armor_slot_4->setFlat(true);
    armor_slot_4->setAutoFillBackground(true);
    armor_slot_4->setIconSize(QSize(32,32));
    armor_slot_4->setStyleSheet(Items.Style_m_no_grow_slot());
    armor_slot_4->setHidden(1);

    QHBoxLayout *armor_slots_3_and_4 = new QHBoxLayout();
    armor_slots_3_and_4->setContentsMargins(0,0,0,0);
    armor_slots_3_and_4->addWidget(armor_slot_3);
    armor_slots_3_and_4->addWidget(armor_m_link_2);
    armor_slots_3_and_4->addWidget(armor_slot_4);
    armor_slots_3_and_4->setSpacing(0);

    armor_slot_5 = new QPushButton();
    armor_slot_5->setFixedSize(32,32);
    armor_slot_5->setFlat(true);
    armor_slot_5->setAutoFillBackground(true);
    armor_slot_5->setIconSize(QSize(32,32));
    armor_slot_5->setStyleSheet(Items.Style_m_no_grow_slot());
    armor_slot_5->setHidden(1);

    armor_m_link_3 = new QLabel();
    armor_m_link_3->setFixedSize(12,16);
    armor_m_link_3->setScaledContents(1);

    armor_slot_6 = new QPushButton();
    armor_slot_6->setFixedSize(32,32);
    armor_slot_6->setFlat(true);
    armor_slot_6->setAutoFillBackground(true);
    armor_slot_6->setIconSize(QSize(32,32));
    armor_slot_6->setStyleSheet(Items.Style_m_no_grow_slot());
    armor_slot_6->setHidden(1);

    QHBoxLayout *armor_slots_5_and_6 = new QHBoxLayout();
    armor_slots_5_and_6->setContentsMargins(0,0,0,0);
    armor_slots_5_and_6->addWidget(armor_slot_5);
    armor_slots_5_and_6->addWidget(armor_m_link_3);
    armor_slots_5_and_6->addWidget(armor_slot_6);
    armor_slots_5_and_6->setSpacing(0);

    armor_slot_7 = new QPushButton();
    armor_slot_7->setFixedSize(32,32);
    armor_slot_7->setFlat(true);
    armor_slot_7->setAutoFillBackground(true);
    armor_slot_7->setIconSize(QSize(32,32));
    armor_slot_7->setStyleSheet(Items.Style_m_no_grow_slot());
    armor_slot_7->setHidden(1);

    armor_m_link_4 = new QLabel();
    armor_m_link_4->setFixedSize(12,16);
    armor_m_link_4->setScaledContents(1);

    armor_slot_8 = new QPushButton();
    armor_slot_8->setFixedSize(32,32);
    armor_slot_8->setFlat(true);
    armor_slot_8->setAutoFillBackground(true);
    armor_slot_8->setIconSize(QSize(32,32));
    armor_slot_8->setStyleSheet(Items.Style_m_no_grow_slot());
    armor_slot_8->setHidden(1);

    QHBoxLayout *armor_slots_7_and_8 = new QHBoxLayout();
    armor_slots_7_and_8->setContentsMargins(0,0,0,0);
    armor_slots_7_and_8->addWidget(armor_slot_7);
    armor_slots_7_and_8->addWidget(armor_m_link_4);
    armor_slots_7_and_8->addWidget(armor_slot_8);
    armor_slots_7_and_8->setSpacing(0);

    QHBoxLayout *armor_materia_slots = new QHBoxLayout();
    armor_materia_slots->setContentsMargins(0,0,0,0);
    armor_materia_slots->addLayout(armor_slots_1_and_2);
    armor_materia_slots->addLayout(armor_slots_3_and_4);
    armor_materia_slots->addLayout(armor_slots_5_and_6);
    armor_materia_slots->addLayout(armor_slots_7_and_8);
    armor_materia_slots->addSpacerItem(armor_spacer);
    armor_materia_slots->setSpacing(12);

    armor_materia_box->setLayout(armor_materia_slots);


    QVBoxLayout *weapon_layout = new QVBoxLayout;
    weapon_layout->setContentsMargins(0,0,0,0);
    weapon_layout->addWidget(weapon_selection);
    weapon_layout->addWidget(weapon_materia_box);

    weapon_box = new QGroupBox(tr("Weapon"));
    weapon_box->setLayout(weapon_layout);
    weapon_box->setMinimumHeight(100);

    QVBoxLayout *armor_layout = new QVBoxLayout;
    armor_layout->setContentsMargins(0,0,0,0);
    armor_layout->addWidget(armor_selection);
    armor_layout->addWidget(armor_materia_box);

    armor_box = new QGroupBox(tr("Armor"));
    armor_box->setLayout(armor_layout);
    armor_box->setMinimumHeight(100);

    QVBoxLayout *accessory_layout = new QVBoxLayout;
    accessory_layout->setContentsMargins(0,0,0,0);
    accessory_layout->addWidget(accessory_selection);

    accessory_box = new QGroupBox(tr("Accessory"));
    accessory_box->setLayout(accessory_layout);
    accessory_box->setMinimumHeight(40);

    QVBoxLayout *right_Top = new QVBoxLayout;
    right_Top->setContentsMargins(0,0,0,0);
    right_Top->addWidget(weapon_box);
    right_Top->addWidget(armor_box);
    right_Top->addWidget(accessory_box);

    QWidget *right_top = new QWidget;
    right_top->setContentsMargins(0,0,0,0);
    right_top->setLayout(right_Top);
    right_top->adjustSize();
    right_top->setFixedHeight(right_top->height());
    right_top->setFixedWidth(410);

    QVBoxLayout *right_bottom = new QVBoxLayout;
    right_bottom->addWidget(materia_edit);
    right_bottom->addLayout(effects_layout);
    QSpacerItem *rtb_spacer = new QSpacerItem(0,0,QSizePolicy::Fixed,QSizePolicy::Expanding);
    right_bottom->addSpacerItem(rtb_spacer);

    materia_edit->setMaximumWidth(410);


    QVBoxLayout *right_Final = new QVBoxLayout;
    right_Final->addWidget(right_top);
    right_Final->setSpacing(3);
    right_Final->addLayout(right_bottom);

    QWidget *equipment_stuff = new QWidget;
    equipment_stuff->setLayout(right_Final);
    equipment_stuff->setMinimumHeight(610);
    equipment_stuff->adjustSize();


    QVBoxLayout *equip_layout = new QVBoxLayout;
    //equip_layout->addWidget(equipment_section);
    equip_layout->addWidget(equipment_stuff);

    QWidget *equip_widget = new QWidget;
    equip_widget->setLayout(equip_layout);

    equipment_section = new QScrollArea;
    equipment_section->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    equipment_section->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    equipment_section->setWidget(equipment_stuff);
    equipment_section->setMinimumWidth(440);
    equipment_section->adjustSize();

    list_limits->setFixedHeight(this->font().pointSize()*14);
    //QHBoxLayout *Final = new QHBoxLayout;
    //Final->setContentsMargins(0,0,0,0);
    //Final->addLayout(left_Final);
    //Final->addLayout(right_Final);
    //Final->addWidget(equipment_section);
    //this->setLayout(Final);

    toolbox = new QToolBox;

    QGroupBox *tab_1 = new QGroupBox;
    tab_1->setLayout(left_Final);
    toolbox->addItem(tab_1,QString(tr("Status Info")));

    QGroupBox *tab_2 = new QGroupBox;
    tab_2->setLayout(limit_box);
    toolbox->addItem(tab_2,QString(tr("Limits")));

    QVBoxLayout *toolbox_layout = new QVBoxLayout;
    toolbox_layout->addLayout(avatar_name_layout);
    toolbox_layout->addWidget(toolbox);

    QWidget *Status_Section = new QWidget;
    Status_Section->setLayout(toolbox_layout);

    //QGroupBox *tab_3 = new QGroupBox;
    //tab_3->setLayout(equip_layout);
    //toolbox->addItem(tab_3,QString(tr("Equipment")));

    main_widget = new QStackedWidget;
    main_widget->addWidget(Status_Section);
    main_widget->addWidget(equipment_section);

    btnPage = new QPushButton;
    btnPage->setText(QString(tr("Equipment")));

    main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0,0,0,0);
    main_layout->addWidget(btnPage);
    main_layout->addWidget(main_widget);
   this->setLayout(main_layout);
}
void CharEditor::init_connections()
{
    connect(sb_level,SIGNAL(valueChanged(int)),this,SLOT(Level_Changed(int)));
    connect(sb_curMp,SIGNAL(valueChanged(int)),this,SLOT(setCurMp(int)));
    connect(sb_curHp,SIGNAL(valueChanged(int)),this,SLOT(setCurHp(int)));
    connect(sb_maxMp,SIGNAL(valueChanged(int)),this,SLOT(setMaxMp(int)));
    connect(sb_maxHp,SIGNAL(valueChanged(int)),this,SLOT(setMaxHp(int)));
    connect(sb_base_hp,SIGNAL(valueChanged(int)),this,SLOT(setBaseHp(int)));
    connect(sb_base_mp,SIGNAL(valueChanged(int)),this,SLOT(setBaseMp(int)));
    connect(sb_kills,SIGNAL(valueChanged(int)),this,SLOT(setKills(int)));
    connect(line_name,SIGNAL(textChanged(QString)),this,SLOT(setName(QString)));
    connect(cb_front_row,SIGNAL(toggled(bool)),this,SLOT(setRow(bool)));
    connect(cb_fury,SIGNAL(toggled(bool)),this,SLOT(cb_fury_toggled(bool)));
    connect(cb_sadness,SIGNAL(toggled(bool)),this,SLOT(cb_sadness_toggled(bool)));
    connect(sb_str,SIGNAL(valueChanged(int)),this,SLOT(setStr(int)));
    connect(sb_str_bonus,SIGNAL(valueChanged(int)),this,SLOT(setStrBonus(int)));
    connect(sb_vit,SIGNAL(valueChanged(int)),this,SLOT(setVit(int)));
    connect(sb_vit_bonus,SIGNAL(valueChanged(int)),this,SLOT(setVitBonus(int)));
    connect(sb_mag,SIGNAL(valueChanged(int)),this,SLOT(setMag(int)));
    connect(sb_mag_bonus,SIGNAL(valueChanged(int)),this,SLOT(setMagBonus(int)));
    connect(sb_spi,SIGNAL(valueChanged(int)),this,SLOT(setSpi(int)));
    connect(sb_spi_bonus,SIGNAL(valueChanged(int)),this,SLOT(setSpiBonus(int)));
    connect(sb_dex,SIGNAL(valueChanged(int)),this,SLOT(setDex(int)));
    connect(sb_dex_bonus,SIGNAL(valueChanged(int)),this,SLOT(setDexBonus(int)));
    connect(sb_lck,SIGNAL(valueChanged(int)),this,SLOT(setLck(int)));
    connect(sb_lck_bonus,SIGNAL(valueChanged(int)),this,SLOT(setLckBonus(int)));
    connect(slider_limit,SIGNAL(valueChanged(int)),this,SLOT(setLimitBar(int)));
    connect(sb_total_exp,SIGNAL(valueChanged(int)),this,SLOT(Exp_Changed(int)));
    connect(slider_limit,SIGNAL(valueChanged(int)),lcd_limit_value,SLOT(display(int)));
    connect(list_limits,SIGNAL(clicked(QModelIndex)),this,SLOT(calc_limit_value(QModelIndex)));
    connect(combo_id,SIGNAL(currentIndexChanged(int)),this,SLOT(setId(int)));
    connect(weapon_selection,SIGNAL(currentIndexChanged(int)),this,SLOT(setWeapon(int)));
    connect(armor_selection,SIGNAL(currentIndexChanged(int)),this,SLOT(setArmor(int)));
    connect(accessory_selection,SIGNAL(currentIndexChanged(int)),this,SLOT(setAccessory(int)));

    connect(weapon_slot_1,SIGNAL(clicked()),this,SLOT(weapon_slot_1_clicked()));
    connect(weapon_slot_2,SIGNAL(clicked()),this,SLOT(weapon_slot_2_clicked()));
    connect(weapon_slot_3,SIGNAL(clicked()),this,SLOT(weapon_slot_3_clicked()));
    connect(weapon_slot_4,SIGNAL(clicked()),this,SLOT(weapon_slot_4_clicked()));
    connect(weapon_slot_5,SIGNAL(clicked()),this,SLOT(weapon_slot_5_clicked()));
    connect(weapon_slot_6,SIGNAL(clicked()),this,SLOT(weapon_slot_6_clicked()));
    connect(weapon_slot_7,SIGNAL(clicked()),this,SLOT(weapon_slot_7_clicked()));
    connect(weapon_slot_8,SIGNAL(clicked()),this,SLOT(weapon_slot_8_clicked()));

    connect(armor_slot_1,SIGNAL(clicked()),this,SLOT(armor_slot_1_clicked()));
    connect(armor_slot_2,SIGNAL(clicked()),this,SLOT(armor_slot_2_clicked()));
    connect(armor_slot_3,SIGNAL(clicked()),this,SLOT(armor_slot_3_clicked()));
    connect(armor_slot_4,SIGNAL(clicked()),this,SLOT(armor_slot_4_clicked()));
    connect(armor_slot_5,SIGNAL(clicked()),this,SLOT(armor_slot_5_clicked()));
    connect(armor_slot_6,SIGNAL(clicked()),this,SLOT(armor_slot_6_clicked()));
    connect(armor_slot_7,SIGNAL(clicked()),this,SLOT(armor_slot_7_clicked()));
    connect(armor_slot_8,SIGNAL(clicked()),this,SLOT(armor_slot_8_clicked()));

    connect(materia_edit,SIGNAL(ap_changed(qint32)),this,SLOT(matAp_changed(qint32)));
    connect(materia_edit,SIGNAL(id_changed(qint8)),this,SLOT(matId_changed(qint8)));
    connect(btnPage,SIGNAL(clicked()),this,SLOT(btn_page_clicked()));
    //connect(lbl_avatar,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(charMenu(QPoint)));
}
qint8 CharEditor::id(){return data.id;}
qint8 CharEditor::level(){return data.level;}
quint8 CharEditor::str(){return data.strength;}
quint8 CharEditor::vit(){return data.vitality;}
quint8 CharEditor::mag(){return data.magic;}
quint8 CharEditor::spi(){return data.spirit;}
quint8 CharEditor::dex(){return data.dexterity;}
quint8 CharEditor::lck(){return data.luck;}
quint8 CharEditor::strBonus(){return data.strength_bonus;}
quint8 CharEditor::vitBonus(){return data.vitality_bonus;}
quint8 CharEditor::magBonus(){return data.magic_bonus;}
quint8 CharEditor::spiBonus(){return data.spirit_bonus;}
quint8 CharEditor::dexBonus(){return data.dexterity_bonus;}
quint8 CharEditor::lckBonus(){return data.luck_bonus;}
qint8 CharEditor::limitLevel(){return data.limitlevel;}
quint8 CharEditor::limitBar(){return data.limitbar;}
QString CharEditor::name(){return line_name->text();}
quint8 CharEditor::weapon(){return data.weapon;}
quint8 CharEditor::armor(){return data.armor;}
quint8 CharEditor::accessory(){return data.accessory;}
quint16 CharEditor::curHp(){return data.curHP;}
quint16 CharEditor::maxHp(){return data.maxHP;}
quint16 CharEditor::curMp(){return data.curMP;}
quint16 CharEditor::maxMp(){return data.maxMP;}
quint16 CharEditor::kills(){return data.kills;}
quint8 CharEditor::row(){return data.flags[1];}
quint8 CharEditor::levelProgress(){return data.flags[2];}
quint8 CharEditor::sadnessfury(){return data.flags[0];}
quint16 CharEditor::limits(){return data.limits;}
quint16 CharEditor::timesused1(){return data.timesused1;}
quint16 CharEditor::timesused2(){return data.timesused2;}
quint16 CharEditor::timesused3(){return data.timesused3;}
quint16 CharEditor::baseHp(){return data.baseHP;}
quint16 CharEditor::baseMp(){return data.baseMP;}
quint32 CharEditor::exp(){return data.exp;}
quint32 CharEditor::expNext(){return data.expNext;}
materia CharEditor::char_materia(int mat){return data.materias[mat];}

void CharEditor::Exp_Changed(int exp)
{
    setExp(exp);
    if(autolevel)
    {
        if( (data.exp>=Chars.Total_Exp_For_Level(data.id,data.level)) || (data.exp<=Chars.Total_Exp_For_Level(data.id,data.level-1)) )
        {
            int level=0;
            int prev_level = data.level;
            for (int i=level;i<99;i++)
            {
                if(data.exp>=Chars.Total_Exp_For_Level(data.id,i)){level++;}
             }
            sb_level->blockSignals(true);
            sb_level->setValue(level);
            setLevel(level);
            sb_level->blockSignals(false);
            level_up(prev_level);
        }
        update_tnl_bar();
    }
}

void CharEditor::Level_Changed(int level)
{
        if(autolevel)
        {
            int prev_level=data.level;
            setLevel(level);
            if(level<=0){setExp(0);}
            else{setExp(Chars.Total_Exp_For_Level(data.id,level-1));}
            sb_total_exp->blockSignals(true);
            sb_total_exp->setValue(data.exp);
            sb_total_exp->blockSignals(false);
            level_up(prev_level);
            update_tnl_bar();
        }
        else{setLevel(level);}
}
void CharEditor::setChar(FF7CHAR Chardata,QString Processed_Name)
{
    data = Chardata;
    _name=Processed_Name;
    //more here like setting the gui stuff.
    lbl_avatar->setPixmap(Chars.Pixmap(data.id));
    line_name->setText(_name);
    sb_level->setValue(data.level);
    sb_curMp->setValue(data.curMP);
    sb_curHp->setValue(data.curHP);
    sb_maxMp->setValue(data.maxMP);
    sb_maxHp->setValue(data.maxHP);
    sb_kills->setValue(data.kills);

    combo_id->blockSignals(true);
    combo_id->setCurrentIndex(data.id);
    combo_id->blockSignals(false);

    cb_fury->blockSignals(true);//block when manually toggling.
    cb_sadness->blockSignals(true);//block when manually toggling
    if(data.flags[0]==0x10){cb_fury->setChecked(Qt::Checked);}
    else if(data.flags[0]==0x20 ){cb_sadness->setChecked(Qt::Checked);}
    else{cb_fury->setChecked(Qt::Unchecked);cb_sadness->setChecked(Qt::Unchecked);}
    cb_fury->blockSignals(false);
    cb_sadness->blockSignals(false);

    cb_front_row->blockSignals(true);
    if(data.flags[1] ==0xFF){cb_front_row->setChecked(Qt::Checked);}
    else{cb_front_row->setChecked(Qt::Unchecked);}
    cb_front_row->blockSignals(false);

    sb_total_exp->setValue(data.exp);
    lcd_tnl->display(int(data.expNext));
    slider_limit->setValue(data.limitbar);

    bar_tnl->setValue(data.flags[2]);

    sb_str->setValue(data.strength);
    sb_str_bonus->setValue(data.strength_bonus);

    sb_vit->setValue(data.vitality);
    sb_vit_bonus->setValue(data.vitality_bonus);

    sb_dex->setValue(data.dexterity);
    sb_dex_bonus->setValue(data.dexterity_bonus);

    sb_mag->setValue(data.magic);
    sb_mag_bonus->setValue(data.magic_bonus);

    sb_spi->setValue(data.spirit);
    sb_spi_bonus->setValue(data.spirit_bonus);

    sb_lck->setValue(data.luck);
    sb_lck_bonus->setValue(data.luck_bonus);

    //Process the limits.
    list_limits->blockSignals(true);
    list_limits->clear();
    list_limits->addItems(Chars.limits(data.id));
    for(int i=0;i<7;i++)
    {//Process the List. Hide "" entries, and Check Limts Learned.

        if(list_limits->item(i)->text()=="") {list_limits->item(i)->setHidden(true);}
        else{list_limits->item(i)->setHidden(false);}

        if(data.limits & (1<<i)){list_limits->item(i)->setCheckState(Qt::Checked);}
        else{list_limits->item(i)->setCheckState(Qt::Unchecked);}
    }

    list_limits->blockSignals(false);

    weapon_selection->blockSignals(true);
    weapon_selection->clear();
    for(int i = Chars.weapon_offset(data.id); i < Chars.num_weapons(data.id)+Chars.weapon_offset(data.id);i++)
    {
        weapon_selection->addItem(QPixmap::fromImage(Items.Image(i)),Items.Name(i));
    }
    weapon_selection->setCurrentIndex(data.weapon);
    update_materia_slots();
    weapon_selection->blockSignals(false);

    armor_selection->setCurrentIndex(data.armor);
    if(data.accessory != 0xFF){accessory_selection->setCurrentIndex(data.accessory);}
    else{accessory_selection->setCurrentIndex(32);}
    update_materia_slots();
    calc_stats();
}

void CharEditor::setLevel(int level)
{
    if(data.level == level){return;}
    else
    {
        if(level<0){data.level=0;}
        else if(level>99){data.level=99;}
        else{data.level=level;}
        emit level_changed(data.level);
        //QMessageBox::information(this,"EMIT",QString("Level_Changed:%1").arg(QString::number(data.level)));
    }
}
void CharEditor::cb_sadness_toggled(bool sad)
{
    if(sad)
    {
        setSadnessFury(0x20);
        cb_fury->blockSignals(true);
        cb_fury->setChecked(Qt::Unchecked);
        cb_fury->blockSignals(false);
    }
    else{setSadnessFury(0);}
}
void CharEditor::cb_fury_toggled(bool fury)
{
    if(fury)
    {
        setSadnessFury(0x10);
        cb_sadness->blockSignals(true);
        cb_sadness->setChecked(Qt::Unchecked);
        cb_sadness->blockSignals(false);
    }
    else{setSadnessFury(0);}
}
void CharEditor::setMaxHp(int maxHp)
{
    if(data.maxHP == maxHp){return;}
    else
    {
        if(maxHp<0){data.maxHP=0;}
        else if(maxHp >32767){data.maxHP=32767;}
        else{data.maxHP=maxHp;}
        emit maxHp_changed(data.maxHP);
        //QMessageBox::information(this,"EMIT",QString("MaxHp_Changed:%1").arg(QString::number(data.maxHP)));
    }
}
void CharEditor::setCurHp(int curHp)
{
    if(data.curHP == curHp){return;}
    else
    {
        if(curHp<0){data.curHP=0;}
        else if(curHp >32767){data.curHP=32767;}
        else{data.curHP=curHp;}
        emit curHp_changed(data.curHP);
        //QMessageBox::information(this,"EMIT",QString("CurHp_Changed:%1").arg(QString::number(data.curHP)));
    }
}
void CharEditor::setMaxMp(int maxMp)
{
    if(data.maxMP == maxMp){return;}
    else
    {
        if(maxMp<0){data.maxMP=0;}
        else if(maxMp >32767){data.maxMP=32767;}
        else{data.maxMP=maxMp;}
        emit maxMp_changed(data.maxMP);
        //QMessageBox::information(this,"EMIT",QString("MaxMp_Changed:%1").arg(QString::number(data.maxMP)));
    }
}
void CharEditor::setCurMp(int curMp)
{
    if(data.curMP == curMp){return;}
    else
    {
        if(curMp<0){data.curMP=0;}
        else if(curMp >32767){data.curMP=32767;}
        else{data.curMP=curMp;}
        emit curMp_changed(data.curMP);
        //QMessageBox::information(this,"EMIT",QString("CurMp_Changed:%1").arg(QString::number(data.curMP)));
    }
}
void CharEditor::setKills(int kills)
{
    if(data.kills == kills){return;}
    else
    {
        if(kills<0){data.kills=0;}
        else if(kills >65535){data.kills=65535;}
        else{data.kills=kills;}
        emit kills_changed(data.kills);
        //QMessageBox::information(this,"EMIT",QString("Kills_Changed:%1").arg(QString::number(data.kills)));
    }
}
void CharEditor::setName(QString name)
{
    if(_name==name){return;}
    else
    {
        if(name==""){_name = QByteArray(12,0xFF);}
        else{_name = name;}
        emit name_changed(_name);
        //QMessageBox::information(this,"EMIT",QString("Name_Changed:%1").arg(name));
    }
}
void CharEditor::setId(int id)
{
    if(data.id ==id){return;}
    else
    {
        if(id<0){data.id = 0;}
        else if(id>0x0B){data.id=0xFF;}
        else{data.id = id;}
        setChar(data,line_name->text());
        emit id_changed(data.id);
        //QMessageBox::information(this,"EMIT",QString("Id_Changed:%1").arg(QString::number(data.id)));
    }
}
void CharEditor::setStr(int strength)
{
    if(data.strength ==strength){return;}
    else
    {
        if(strength<0){data.strength=0;}
        else if(strength>0xFF){data.strength=0xFF;}
        else{data.strength = strength;}
        emit str_changed(data.strength);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("str_Changed:%1").arg(QString::number(data.strength)));
    }
}
void CharEditor::setVit(int vitality)
{
    if(data.vitality ==vitality){return;}
    else
    {
        if(vitality<0){data.vitality = 0;}
        else if(vitality>0xFF){data.vitality=0xFF;}
        else{data.vitality = vitality;}
        emit vit_changed(data.vitality);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("vit_Changed:%1").arg(QString::number(data.vitality)));
    }
}
void CharEditor::setMag(int magic)
{
    if(data.magic ==magic){return;}
    else
    {
        if(magic<0){data.magic = 0;}
        else if(magic>0xFF){data.magic=0xFF;}
        else{data.magic = magic;}
        emit mag_changed(data.magic);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("mag_Changed:%1").arg(QString::number(data.magic)));
    }
}
void CharEditor::setSpi(int spirit)
{
    if(data.spirit ==spirit){return;}
    else
    {
        if(spirit<0){data.spirit = 0;}
        else if(spirit>0xFF){data.spirit=0xFF;}
        else{data.spirit = spirit;}
        emit spi_changed(data.spirit);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("spi_Changed:%1").arg(QString::number(data.spirit)));
    }
}
void CharEditor::setDex(int dexterity)
{
    if(data.dexterity ==dexterity){return;}
    else
    {
        if(dexterity<0){data.dexterity = 0;}
        else if(dexterity>0xFF){data.dexterity=0xFF;}
        else{data.dexterity = dexterity;}
        emit dex_changed(data.dexterity);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("dex_Changed:%1").arg(QString::number(data.dexterity)));
    }
}
void CharEditor::setLck(int luck)
{
    if(data.luck ==luck){return;}
    else
    {
        if(luck<0){data.luck = 0;}
        else if(luck>0xFF){data.luck=0xFF;}
        else{data.luck = luck;}
        emit lck_changed(data.luck);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("lck_Changed:%1").arg(QString::number(data.luck)));
    }
}
void CharEditor::setStrBonus(int strength_bonus)
{
    if(data.strength_bonus ==strength_bonus){return;}
    else
    {
        if(strength_bonus<0){data.strength_bonus = 0;}
        else if(strength_bonus>0xFF){data.strength_bonus=0xFF;}
        else{data.strength_bonus = strength_bonus;}
        emit strBonus_changed(data.strength_bonus);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("strBonus_Changed:%1").arg(QString::number(data.strength_bonus)));
    }
}
void CharEditor::setVitBonus(int vitality_bonus)
{
    if(data.vitality_bonus ==vitality_bonus){return;}
    else
    {
        if(vitality_bonus<0){data.vitality_bonus = 0;}
        else if(vitality_bonus>0xFF){data.vitality_bonus=0xFF;}
        else{data.vitality_bonus = vitality_bonus;}
        emit vitBonus_changed(data.vitality_bonus);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("vitBonus_Changed:%1").arg(QString::number(data.vitality_bonus)));
    }
}
void CharEditor::setMagBonus(int magic_bonus)
{
    if(data.magic_bonus ==magic_bonus){return;}
    else
    {
        if(magic_bonus<0){data.magic_bonus = 0;}
        else if(magic_bonus>0xFF){data.magic_bonus=0xFF;}
        else{data.magic_bonus = magic_bonus;}
        emit magBonus_changed(data.magic_bonus);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("magBonus_Changed:%1").arg(QString::number(data.magic_bonus)));
    }
}
void CharEditor::setSpiBonus(int spirit_bonus)
{
    if(data.spirit_bonus ==spirit_bonus){return;}
    else
    {
        if(spirit_bonus<0){data.spirit_bonus = 0;}
        else if(spirit_bonus>0xFF){data.spirit_bonus=0xFF;}
        else{data.spirit_bonus = spirit_bonus;}
        emit spiBonus_changed(data.spirit_bonus);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("spiBonus_Changed:%1").arg(QString::number(data.spirit_bonus)));
    }
}
void CharEditor::setDexBonus(int dexterity_bonus)
{
    if(data.dexterity_bonus ==dexterity_bonus){return;}
    else
    {
        if(dexterity_bonus<0){data.dexterity_bonus = 0;}
        else if(dexterity_bonus>0xFF){data.dexterity_bonus=0xFF;}
        else{data.dexterity_bonus = dexterity_bonus;}
        emit dexBonus_changed(data.dexterity_bonus);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("dexBonus_Changed:%1").arg(QString::number(data.dexterity_bonus)));
    }
}
void CharEditor::setLckBonus(int luck_bonus)
{
    if(data.luck ==luck_bonus){return;}
    else
    {
        if(luck_bonus<0){data.luck_bonus = 0;}
        else if(luck_bonus>0xFF){data.luck_bonus=0xFF;}
        else{data.luck_bonus = luck_bonus;}
        emit lckBonus_changed(data.luck_bonus);
        calc_stats();
        //QMessageBox::information(this,"EMIT",QString("lckBonus_Changed:%1").arg(QString::number(data.luck_bonus)));
    }
}
void CharEditor::setLimitLevel(int limitlevel)
{
    if(data.limitlevel ==limitlevel){return;}
    else
    {
        if(limitlevel<0){data.limitlevel = 0;}
        else if(limitlevel>4){data.limitlevel=4;}
        else{data.limitlevel = limitlevel;}
        emit limitLevel_changed(data.limitlevel);
        //QMessageBox::information(this,"EMIT",QString("limitLevel_Changed:%1").arg(QString::number(data.limitlevel)));
    }
}
void CharEditor::setLimitBar(int limitbar)
{
    if(data.limitbar ==limitbar){return;}
    else
    {
        if(limitbar<0){data.limitbar = 0;}
        else if(limitbar>0xFF){data.limitbar=0xFF;}
        else{data.limitbar = limitbar;}
        emit limitBar_changed(data.limitbar);
        //QMessageBox::information(this,"EMIT",QString("limitBar_Changed:%1").arg(QString::number(data.limitbar)));
    }
}
void CharEditor::setWeapon(int weapon)
{
    if(weapon == data.weapon){return;}
    else
    {
        if(weapon<0){data.weapon=0;}
        else if(weapon>Chars.num_weapons(data.id)){data.weapon=Chars.num_weapons(data.id);}
        else {data.weapon=weapon;}
        emit weapon_changed(data.weapon);
        //Update the Widget.
        elemental_info();
        status_info();
        update_materia_slots();
        if(autostatcalc){calc_stats();}
        //QMessageBox::information(this,"EMIT",QString("weapon_Changed:%1").arg(QString::number(data.weapon)));
    }
}
void CharEditor::setArmor(int armor)
{
    if(armor == data.armor){return;}
    else
    {
        if(armor<0){data.armor=0;}
        else if(armor>32){data.armor=0xFF;}
        else {data.armor= armor; }
        emit armor_changed(data.armor);
        elemental_info();
        status_info();
        update_materia_slots();
        if(autostatcalc){calc_stats();}
        //QMessageBox::information(this,"EMIT",QString("armor_Changed:%1").arg(QString::number(data.armor)));
    }
}
void CharEditor::setAccessory(int accessory)
{
    if(accessory == data.accessory){return;}
    else
    {
        if(accessory<0){data.accessory=0;}
        else if(accessory>32){data.accessory=0xFF;}
        else {data.accessory = accessory;}
        emit accessory_changed(data.accessory);
        elemental_info();
        status_info();
        if(autostatcalc){calc_stats();}
        //QMessageBox::information(this,"EMIT",QString("accessory_Changed:%1").arg(QString::number(data.accessory)));
    }
}
void CharEditor::setSadnessFury(int sad_fury)
{
    if(sad_fury == data.flags[0]){return;}
    else
    {
        if(sad_fury==0x10){data.flags[0]=0x10;}
        else if( sad_fury==0x20 ){data.flags[0]=0x20;}
        else{data.flags[0]=0;}
        emit sadnessfury_changed(data.flags[0]);
    }
    //QMessageBox::information(this,"EMIT",QString("sad_fury_Changed:%1").arg(QString::number(data.flags[0])));

}
void CharEditor::setRow(bool front_row)
{
    if( (front_row) && (data.flags[1]==0xFF) ){return;}
    else if((!front_row) && (data.flags[1]==0xFE)){return;}
    else
    {
        if(front_row){data.flags[1]=0xFF;}
        else{data.flags[1]=0xFE;}
        emit row_changed(data.flags[1]);
        //QMessageBox::information(this,"EMIT",QString("row_Changed:%1").arg(QString::number(data.flags[1])));
    }
}

void CharEditor::setLevelProgress(int level_progress)
{//Level progress bar (0-63) game ingores values <4 4-63 are visible as "progress"
    if(level_progress ==data.flags[2]){return;}
    else
    {
        if(level_progress<0){data.flags[2]=0;}
        else if(level_progress >63){data.flags[2]=63;}
        else{data.flags[2]=level_progress;}
        emit levelProgress_changed(data.flags[2]);
        ////QMessageBox::information(this,"EMIT",QString("Level_Progress_Changed:%1").arg(QString::number(data.flags[2])));
    }
}

void CharEditor::setLimits(int limits)
{
    if(limits ==data.limits){return;}
    else
    {
        if(limits <0){data.limits=0;}
        else if(limits>32767){data.limits=32767;}
        else {data.limits = limits;}
        emit limits_changed(data.limits);
        //QMessageBox::information(this,"EMIT",QString("Limits_Changed:%1").arg(QString::number(data.limits,2)));
    }
}
void CharEditor::setTimesused1(int timesused)
{
    if(timesused ==data.timesused1){return;}
    else
    {
        if(timesused <0){data.timesused1=0;}
        else if(timesused>65535){data.timesused1=65535;}
        else{data.timesused1 = timesused;}
    }
}

void CharEditor::setTimesused2(int timesused)
{
    if(timesused ==data.timesused2){return;}
    else
    {
        if(timesused <0){data.timesused2=0;}
        else if(timesused>65535){data.timesused2=65535;}
        else{data.timesused2 = timesused;}
    }
}
void CharEditor::setTimesused3(int timesused)
{
    if(timesused ==data.timesused3){return;}
    else
    {
        if(timesused <0){data.timesused3=0;}
        else if(timesused>65535){data.timesused3=65535;}
        else{data.timesused3 = timesused;}
    }
}
void CharEditor::setBaseHp(int baseHp)
{
    if(data.baseHP == baseHp){return;}
    else
    {
        if(baseHp<0){data.baseHP=0;}
        else if(baseHp >32767){data.baseHP=32767;}
        else{data.baseHP=baseHp;}
        emit baseHp_changed(data.baseHP);
        if(autostatcalc){calc_stats(); }
        //QMessageBox::information(this,"EMIT",QString("baseHp_Changed:%1").arg(QString::number(data.baseHP)));
    }
}
void CharEditor::setBaseMp(int baseMp)
{
    if(data.baseMP == baseMp){return;}
    else
    {
        if(baseMp<0){data.baseMP=0;}
        else if(baseMp >32767){data.baseMP=32767;}
        else{data.baseMP=baseMp;}
        emit baseMp_changed(data.baseMP);
        if(autostatcalc){calc_stats();}
        //QMessageBox::information(this,"EMIT",QString("baseMp_Changed:%1").arg(QString::number(data.baseMP)));
    }
}
void CharEditor::setExp(int exp)
{
    if(data.exp == quint32(exp)){return;}
    else
    {
        if(exp<0){data.exp=0;}
        else{data.exp=exp;}
        emit exp_changed(data.exp);
        //QMessageBox::information(this,"EMIT",QString("exp_Changed:%1").arg(QString::number(data.exp)));
    }
}
void CharEditor::setExpNext(int expNext)
{
    if(data.expNext == quint32(expNext)){return;}
    else
    {
        if(expNext<0){data.expNext=0;}
        else{data.expNext=expNext;}
        emit expNext_changed(data.expNext);
        //QMessageBox::information(this,"EMIT",QString("expNext_Changed:%1").arg(QString::number(data.expNext)));
    }
}

void CharEditor::calc_limit_value(QModelIndex item)
{
    int row = item.row();
    int limits = data.limits;
    if(list_limits->item(row)->checkState() ==Qt::Checked){limits |= (1<<row);}
    else{limits &= ~(1<<row);}
    setLimits(limits);
}

void CharEditor::charMenu(QPoint pos)
{//this has problems with out reading all chars. i.e no dynamic entries to the list.
    QMenu menu(this);
    QAction *sel;


    menu.addAction(Chars.Icon(0),Chars.defaultName(0));
    menu.addAction(Chars.Icon(1),Chars.defaultName(1));
    menu.addAction(Chars.Icon(2),Chars.defaultName(2));
    menu.addAction(Chars.Icon(3),Chars.defaultName(3));
    menu.addAction(Chars.Icon(4),Chars.defaultName(4));
    menu.addAction(Chars.Icon(5),Chars.defaultName(5));
    menu.addAction(Chars.Icon(6),Chars.defaultName(6));
    menu.addAction(Chars.Icon(7),Chars.defaultName(7));
    menu.addAction(Chars.Icon(8),Chars.defaultName(8));

    sel = menu.exec(lbl_avatar->mapToGlobal(pos));
    if(sel==0){return;}

    else{return;}
}//End Of Map Context Menu

void CharEditor::setAutoLevel(bool ans){autolevel=ans;}//used to turn off auto char leveling
bool CharEditor::AutoLevel(void){return autolevel;}
void CharEditor::setAutoStatCalc(bool ans){autostatcalc=ans;}
bool CharEditor::AutoStatCalc(void){return autostatcalc;}
void CharEditor::setEditable(bool edit)
{
    editable = edit;
    if(editable){
    // unlock all items, do this better later on.
    this->setEnabled(true);
    }
    else{
    //lock all items
    this->setEnabled(false);
    }
}
bool CharEditor::Editable(void){return editable;}

void CharEditor::calc_stats(void)
{
    int str_total=0;
    int vit_total=0;
    int spi_total=0;
    int dex_total=0;
    int mag_total=0;
    int lck_total=0;

    int str_bonus=0;
    int vit_bonus=0;
    int spi_bonus=0;
    int dex_bonus=0;
    int mag_bonus=0;
    int lck_bonus=0;
    int hp_bonus=0;
    int mp_bonus=0;

    str_total = data.strength + data.strength_bonus;
    vit_total= data.vitality + data.vitality_bonus;
    dex_total = data.dexterity + data.dexterity_bonus;
    spi_total = data.spirit + data.spirit_bonus;
    mag_total = data.magic + data.magic_bonus;
    lck_total = data.luck + data.luck_bonus;

    if(autostatcalc)
    {
        //add equipment bonuses
        //Weapon
        str_bonus +=Items.Stat_str(data.weapon + Chars.weapon_offset(data.id));
        vit_bonus +=Items.Stat_vit(data.weapon + Chars.weapon_offset(data.id));
        dex_bonus +=Items.Stat_dex(data.weapon + Chars.weapon_offset(data.id));
        spi_bonus +=Items.Stat_spi(data.weapon + Chars.weapon_offset(data.id));
        mag_bonus +=Items.Stat_mag(data.weapon + Chars.weapon_offset(data.id));
        lck_bonus +=Items.Stat_lck(data.weapon + Chars.weapon_offset(data.id));
        hp_bonus+=Items.Stat_hp(data.weapon + Chars.weapon_offset(data.id));
        mp_bonus+=Items.Stat_mp(data.weapon + Chars.weapon_offset(data.id));
        QString title;
        title.append(tr("AP:x%1").arg(QString::number(Items.m_growth_rate(data.weapon + Chars.weapon_offset(data.id)))));

        if(Items.Stat_str(data.weapon + Chars.weapon_offset(data.id))!=0)
        {
            title.append(tr(" Str:+%1").arg(QString::number(Items.Stat_str(data.weapon + Chars.weapon_offset(data.id)))));
        }
        if(Items.Stat_vit(data.weapon + Chars.weapon_offset(data.id))!=0)
        {
            title.append(tr(" Vit:+%1").arg(QString::number(Items.Stat_vit(data.weapon + Chars.weapon_offset(data.id)))));
        }
        if(Items.Stat_dex(data.weapon + Chars.weapon_offset(data.id))!=0)
        {
            title.append(tr(" Dex:+%1").arg(QString::number(Items.Stat_dex(data.weapon + Chars.weapon_offset(data.id)))));
        }
        if(Items.Stat_spi(data.weapon + Chars.weapon_offset(data.id))!=0)
        {
            title.append(tr(" Spi:+%1").arg(QString::number(Items.Stat_spi(data.weapon + Chars.weapon_offset(data.id)))));
        }
        if(Items.Stat_mag(data.weapon + Chars.weapon_offset(data.id))!=0)
        {
            title.append(tr(" Mag:+%1").arg(QString::number(Items.Stat_mag(data.weapon + Chars.weapon_offset(data.id)))));
        }
        if(Items.Stat_lck(data.weapon + Chars.weapon_offset(data.id))!=0)
        {
            title.append(tr(" Lck:+%1").arg(QString::number(Items.Stat_lck(data.weapon + Chars.weapon_offset(data.id)))));
        }
        if(Items.Stat_hp(data.weapon + Chars.weapon_offset(data.id))!=0)
        {
            title.append(tr(" Hp:+%1%").arg(QString::number(Items.Stat_hp(data.weapon + Chars.weapon_offset(data.id)))));
        }
        if(Items.Stat_mp(data.weapon + Chars.weapon_offset(data.id))!=0)
        {
            title.append(tr(" Mp:+%1%").arg(QString::number(Items.Stat_mp(data.weapon + Chars.weapon_offset(data.id)))));
        }
        weapon_materia_box->setTitle(title);
        //Armor
        str_bonus += Items.Stat_str(data.armor + 256);
        vit_bonus +=Items.Stat_vit(data.armor + 256);
        dex_bonus +=Items.Stat_dex(data.armor + 256);
        spi_bonus +=Items.Stat_spi(data.armor + 256);
        mag_bonus +=Items.Stat_mag(data.armor + 256);
        lck_bonus +=Items.Stat_lck(data.armor+ 256);
        hp_bonus+=Items.Stat_hp(data.armor + 256);
        mp_bonus+=Items.Stat_mp(data.armor + 256);
        title.clear();
        title.append(tr("AP:x%1").arg(QString::number(Items.m_growth_rate(data.armor + 256))));
        if(Items.Stat_str(data.armor + 256) != 0)
        {
            title.append(tr(" Str:+%1").arg(QString::number(Items.Stat_str(data.armor + 256))));
        }
        if(Items.Stat_vit(data.armor + 256) !=0)
        {
            title.append(tr(" Vit:+%1").arg(QString::number(Items.Stat_vit(data.armor + 256))));
        }
        if(Items.Stat_dex(data.armor + 256)!=0)
        {
            title.append(tr(" Dex:+%1").arg(QString::number(Items.Stat_dex(data.armor + 256))));
        }
        if(Items.Stat_spi(data.armor + 256)!=0)
        {
            title.append(tr(" Spi:+%1").arg(QString::number(Items.Stat_spi(data.armor + 256))));
        }
        if(Items.Stat_mag(data.armor + 256)!=0)
        {
            title.append(tr(" Mag:+%1").arg(QString::number(Items.Stat_mag(data.armor + 256))));
        }
        if(Items.Stat_lck(data.armor + 256)!=0)
        {
            title.append(tr(" Lck:+%1").arg(QString::number(Items.Stat_lck(data.armor + 256))));
        }
        if(Items.Stat_hp(data.armor + 256)!=0)
        {
            title.append(tr(" Hp:+%1%").arg(QString::number(Items.Stat_hp(data.armor + 256))));
        }
        if(Items.Stat_mp(data.armor + 256)!=0)
        {
            title.append(tr(" Mp:+%1%").arg(QString::number(Items.Stat_mp(data.armor + 256))));
        }
        armor_materia_box->setTitle(title);
        //Accessory
        if(data.accessory <32)
        {
            str_bonus += Items.Stat_str(data.accessory + 288);
            vit_bonus +=Items.Stat_vit(data.accessory + 288);
            dex_bonus +=Items.Stat_dex(data.accessory + 288);
            spi_bonus +=Items.Stat_spi(data.accessory + 288);
            mag_bonus +=Items.Stat_mag(data.accessory + 288);
            lck_bonus +=Items.Stat_lck(data.accessory+ 288);
            hp_bonus+=Items.Stat_hp(data.accessory + 288);
            mp_bonus+=Items.Stat_mp(data.accessory + 288);
            title.clear();
            title.append(tr("Accessory"));
            if(Items.Stat_str(data.accessory + 288) != 0)
            {
                title.append(tr(" Str:+%1").arg(QString::number(Items.Stat_str(data.accessory + 288))));
            }
            if(Items.Stat_vit(data.accessory + 288) !=0)
            {
                title.append(tr(" Vit:+%1").arg(QString::number(Items.Stat_vit(data.accessory + 288))));
            }
            if(Items.Stat_dex(data.accessory + 288)!=0)
            {
                title.append(tr(" Dex:+%1").arg(QString::number(Items.Stat_dex(data.accessory + 288))));
            }
            if(Items.Stat_spi(data.accessory + 288)!=0)
            {
                title.append(tr(" Spi:+%1").arg(QString::number(Items.Stat_spi(data.accessory + 288))));
            }
            if(Items.Stat_mag(data.accessory + 288)!=0)
            {
                title.append(tr(" Mag:+%1").arg(QString::number(Items.Stat_mag(data.accessory + 288))));
            }
            if(Items.Stat_lck(data.accessory + 288)!=0)
            {
                title.append(tr(" Lck:+%1").arg(QString::number(Items.Stat_lck(data.accessory + 288))));
            }
            if(Items.Stat_hp(data.accessory + 288)!=0)
            {
                title.append(tr(" Hp:+%1%").arg(QString::number(Items.Stat_hp(data.accessory + 288))));
            }
            if(Items.Stat_mp(data.accessory + 288)!=0)
            {
                title.append(tr(" Mp:+%1%").arg(QString::number(Items.Stat_mp(data.accessory + 288))));
            }
            accessory_box->setTitle(title);
        }
        else{title.clear();title.append(tr("Accessory"));accessory_box->setTitle(title);}
        //process materia
        for(int i=0;i<16;i++)
        {
            if(data.materias[i].id!=0xFF)
            {
                bool add=true;
                int level=0;
                int aptemp = Materias.ap2num(data.materias[i].ap);
                for(int m=0; m<Materias.Levels(data.materias[i].id);m++){if(aptemp >= Materias.Ap(data.materias[i].id,m)){level++;}}

                switch(i)
                {
                    case 0: if(weapon_slot_1->isHidden()){add=false;};break;
                    case 1: if(weapon_slot_2->isHidden()){add=false;}break;
                    case 2: if(weapon_slot_3->isHidden()){add=false;}break;
                    case 3: if(weapon_slot_4->isHidden()){add=false;}break;
                    case 4: if(weapon_slot_5->isHidden()){add=false;}break;
                    case 5: if(weapon_slot_6->isHidden()){add=false;}break;
                    case 6: if(weapon_slot_7->isHidden()){add=false;}break;
                    case 7: if(weapon_slot_8->isHidden()){add=false;}break;
                    case 8: if(armor_slot_1->isHidden()){add=false;}break;
                    case 9: if(armor_slot_2->isHidden()){add=false;}break;
                    case 10:if(armor_slot_3->isHidden()){add=false;}break;
                    case 11:if(armor_slot_4->isHidden()){add=false;}break;
                    case 12:if(armor_slot_5->isHidden()){add=false;}break;
                    case 13:if(armor_slot_6->isHidden()){add=false;}break;
                    case 14:if(armor_slot_7->isHidden()){add=false;}break;
                    case 15:if(armor_slot_8->isHidden()){add=false;}break;
                }
                if(add)
                {
                    // no special materia that affects these stats.
                    str_bonus +=Materias.Stat_Str(data.materias[i].id);
                    vit_bonus +=Materias.Stat_Vit(data.materias[i].id);
                    spi_bonus +=Materias.Stat_Spi(data.materias[i].id);
                    //Show in Percentage.
                    if(data.materias[i].id == 0x00){mp_bonus +=(10*level);}                                                 else{mp_bonus+=Materias.Stat_Mp(data.materias[i].id);}
                    if(data.materias[i].id == 0x01){hp_bonus += (10*level);}                                                 else{hp_bonus+=Materias.Stat_Hp(data.materias[i].id);}
                    //show exact numbers
                    if(data.materias[i].id == 0x02){dex_bonus += data.dexterity * (0.01*(level*10));}   else{dex_bonus +=Materias.Stat_Dex(data.materias[i].id);}
                    if(data.materias[i].id ==0x03){ mag_bonus += data.magic * (0.01*(level*10));}        else{mag_bonus +=Materias.Stat_Mag(data.materias[i].id);}
                    if(data.materias[i].id ==0x04){ lck_bonus += data.luck * (0.01*(level*10));}              else{lck_bonus +=Materias.Stat_Lck(data.materias[i].id);}
                 }// end of add case.
            }
        }

        lbl_str_mat_bonus->setText(QString::number(str_bonus));
        lbl_vit_mat_bonus->setText(QString::number(vit_bonus));
        lbl_dex_mat_bonus->setText(QString::number(dex_bonus));
        lbl_spi_mat_bonus->setText(QString::number(spi_bonus));
        lbl_mag_mat_bonus->setText(QString::number(mag_bonus));
        lbl_lck_mat_bonus->setText(QString::number(lck_bonus));
    }

    str_total+=str_bonus;
    vit_total+= vit_bonus;
    dex_total+= dex_bonus;
    spi_total+= spi_bonus;
    mag_total+= mag_bonus;
    lck_total+= lck_bonus;

    if(str_total < 256)lbl_str_total->setText(QString::number(str_total));
    else{lbl_str_total->setText(QString::number(255));}

    if(vit_total  < 256)lbl_vit_total->setText(QString::number(vit_total));
    else{lbl_vit_total->setText(QString::number(255));}

    if(dex_total < 256)lbl_dex_total->setText(QString::number(dex_total));
    else{lbl_dex_total->setText(QString::number(255));}

    if(spi_total < 256)lbl_spi_total->setText(QString::number(spi_total));
    else{lbl_spi_total->setText(QString::number(255));}

    if(mag_total < 256)lbl_mag_total->setText(QString::number(mag_total));
    else{lbl_mag_total->setText(QString::number(255));}

    if(lck_total < 256)lbl_lck_total->setText(QString::number(lck_total));
    else{lbl_lck_total->setText(QString::number(255));}

    if(hp_bonus !=0){lbl_base_hp_bonus->setText(QString("%1%").arg(QString::number(hp_bonus)));} else{lbl_base_hp_bonus->setText(QString(""));}
    if(mp_bonus!=0){lbl_base_mp_bonus->setText(QString("%1%").arg(QString::number(mp_bonus)));} else{lbl_base_mp_bonus->setText(QString(""));}

    sb_maxHp->setValue(data.baseHP + (data.baseHP * (hp_bonus*.01)));
    sb_maxMp->setValue(data.baseMP + (data.baseMP *(mp_bonus *.01)));
}

void CharEditor::level_up(int pre_level)
{
    if(pre_level < data.level)
    {//level up
        for(int i=pre_level;i<data.level;i++)
        {// for stat_gain stat guide, 0=str; 1=vit;2=mag;3=spr;4=dex;5=lck;6=basehp;7basemp also use id incase of mods that could move a char.
            sb_str->setValue(data.strength + Chars.stat_gain(data.id,0,data.strength,i+1));
            sb_vit->setValue(data.vitality + Chars.stat_gain(data.id,1,data.vitality,i+1));
            sb_mag->setValue(data.magic + Chars.stat_gain(data.id,2,data.magic,i+1));
            sb_spi->setValue(data.spirit + Chars.stat_gain(data.id,3,data.spirit,i+1));
            sb_dex->setValue(data.dexterity + Chars.stat_gain(data.id,4,data.dexterity,i+1));
            sb_lck->setValue(data.luck + Chars.stat_gain(data.id,5,data.luck,i+1));
            sb_base_hp->setValue(data.baseHP + Chars.stat_gain(data.id,6,data.baseHP,i+1));
            sb_base_mp->setValue(data.baseMP + Chars.stat_gain(data.id,7,data.baseMP,i+1));
         }
    }
    else if(pre_level > data.level)
    {//level down
        for(int i=pre_level;i>data.level;i--)
        {// for stat_gain stat guide, 0=str; 1=vit;2=mag;3=spr;4=dex;5=lck;6=basehp;7basemp
            sb_str->setValue(data.strength - Chars.stat_gain(data.id,0,data.strength,i));
            sb_vit->setValue(data.vitality - Chars.stat_gain(data.id,1,data.vitality,i));
            sb_mag->setValue(data.magic - Chars.stat_gain(data.id,2,data.magic,i));
            sb_spi->setValue(data.spirit - Chars.stat_gain(data.id,3,data.spirit,i));
            sb_dex->setValue(data.dexterity - Chars.stat_gain(data.id,4,data.dexterity,i));
            sb_lck->setValue(data.luck - Chars.stat_gain(data.id,5,data.luck,i));
            sb_base_hp->setValue(data.baseHP - Chars.stat_gain(data.id,6,data.baseHP,i));
            sb_base_mp->setValue(data.baseMP - Chars.stat_gain(data.id,7,data.baseMP,i));
        }
    } //little broken when going down..
    calc_stats();
}
void CharEditor::update_tnl_bar(void)
{
    QString numvalue;

    if(data.level!=99)
    {
        setExpNext(Chars.Total_Exp_For_Level(data.id,data.level)- data.exp);
        if(data.level>0)
        {
             setLevelProgress(((Chars.Tnl_For_Level(data.id,data.level)-data.expNext)*62)/Chars.Tnl_For_Level(data.id,data.level));
        }
    }
    else
    {
        setExpNext(0);
        setLevelProgress(0x3D);
    }
    bar_tnl->setValue(data.flags[2]);
    if(bar_tnl->value()<4){bar_tnl->setValue(0);}//ff7 ingores the value if its <4 (but we don't save this)
    numvalue.setNum(data.expNext);
    lcd_tnl->display(numvalue);
}

void CharEditor::elemental_info(void)
{
    int y=20;
    bool show=false;
    int item_id = 0;
    QString m_effect;
    elemental_effects->clear();
    for(int r=0;r<3;r++)
    {
        switch (r)
        {
            case 0:item_id = data.weapon +Chars.weapon_offset(data.id); break;
            case 1:item_id = data.armor +256; break;
            case 2:item_id = data.accessory +288; break;
         }
        if(item_id <0 || item_id >319){}
        else
        {
            for(int i=0;i<14;i++)
            {
                QString effect;
                int element=0;
                switch(i)
                {
                    case 0: element=Items.element_restoration(item_id); effect.append(tr("Restoration"));break;
                    case 1: element=Items.element_fire(item_id); effect.append(tr("Fire")); break;
                    case 2: element=Items.element_cold(item_id); effect.append(tr("Cold")); break;
                    case 3: element=Items.element_lightning(item_id); effect.append(tr("Lightning")); break;
                    case 4: element=Items.element_earth(item_id); effect.append(tr("Earth")); break;
                    case 5: element=Items.element_wind(item_id); effect.append(tr("Wind")); break;
                    case 6: element=Items.element_water(item_id); effect.append(tr("Water")); break;
                    case 7: element=Items.element_gravity(item_id); effect.append(tr("Gravity")); break;
                    case 8: element=Items.element_holy(item_id); effect.append(tr("Holy")); break;
                    case 9: element=Items.element_poison(item_id); effect.append(tr("Poison")); break;
                    case 10: element=Items.element_cut(item_id); effect.append(tr("Cut")); break;
                    case 11: element=Items.element_shoot(item_id); effect.append(tr("Shoot")); break;
                    case 12: element=Items.element_punch(item_id); effect.append(tr("Punch")); break;
                    case 13: element=Items.element_hit(item_id); effect.append(tr("Hit")); break;
                }
                switch(element)
                {
                    case -3: effect.prepend(tr("Absorb:"));break;
                    case -2: effect.prepend(tr("Nullify:"));break;
                    case -1: effect.prepend(tr("Halve:"));break;
                    case  0: effect.clear();break;
                    case +1: effect.prepend(tr("Attack:"));break;
                }
                if(!effect.isNull() && !m_effect.contains(effect,Qt::CaseSensitive))
                {
                        m_effect.append(effect);
                        elemental_effects->addItem(effect);
                        show=true; y+=18;
                 }
             }//end of for Loop
            if(y<=100){elemental_box->setFixedSize(200,y);}
            else{elemental_box->setFixedSize(200,100);}
        }//end of else.
    }//end of other loop.
   elemental_box->setVisible(show);
   elemental_box->adjustSize();
}//end of function

void CharEditor::status_info(void)
{
    int y=20;
    bool show=false;
    int item_id =0;
    QString m_status;
    status_effects->clear();
    for(int r=0;r<3;r++)
    {
        switch (r)
        {
            case 0:item_id = data.weapon +Chars.weapon_offset(data.id); break;
            case 1:item_id = data.armor +256; break;
            case 2:item_id = data.accessory +288; break;
         }
         if(item_id <0 || item_id >319){}
         else
         {
            for(int i=0;i<23;i++)
            {
                QString effect;
                int status=0;
                switch(i)
                {
                    case 0: status=Items.status_death(item_id); effect.append(tr("Death"));break;
                    case 1: status=Items.status_slow_numb(item_id); effect.append(tr("Slow-Numb"));break;
                    case 2: status=Items.status_d_sentence(item_id); effect.append(tr("D.Sentence"));break;
                    case 3: status=Items.status_paralysis(item_id); effect.append(tr("Paralysis"));break;
                    case 4: status=Items.status_petrify(item_id); effect.append(tr("Petrify"));break;
                    case 5: status=Items.status_silence(item_id); effect.append(tr("Silence"));break;
                    case 6: status=Items.status_sleep(item_id); effect.append(tr("Sleep"));break;
                    case 7: status=Items.status_confusion(item_id); effect.append(tr("Confusion"));break;
                    case 8: status=Items.status_berserk(item_id); effect.append(tr("Berserk"));break;
                    case 9: status=Items.status_frog(item_id); effect.append(tr("Frog"));break;
                    case 10: status=Items.status_mini(item_id); effect.append(tr("Mini"));break;
                    case 11: status=Items.status_poison(item_id); effect.append(tr("Poison"));break;
                    case 12: status=Items.status_fury(item_id); effect.append(tr("Fury"));break;
                    case 13: status=Items.status_sadness(item_id); effect.append(tr("Sadness"));break;
                    case 14: status=Items.status_darkness(item_id); effect.append(tr("Darkness"));break;
                    case 15: status=Items.status_haste(item_id); effect.append(tr("Haste"));break;
                    case 16: status=Items.status_slow(item_id); effect.append(tr("Slow"));break;
                    case 17: status=Items.status_stop(item_id); effect.append(tr("Stop"));break;
                    case 18: status=Items.status_barrier(item_id); effect.append(tr("Barrier"));break;
                    case 19: status=Items.status_m_barrier(item_id); effect.append(tr("M.Barrier"));break;
                    case 20: status=Items.status_reflect(item_id); effect.append(tr("Reflect"));break;
                    case 21: status=Items.status_shield(item_id); effect.append(tr("Shield"));break;
                    case 22: status=Items.status_regen(item_id); effect.append(tr("Regen"));break;
                }
                switch(status)
                {
                    case -2: effect.prepend(tr("Protect:")); break;
                    case -1: effect.prepend(tr("Remove:")); break;
                    case  0: effect.clear();break;
                    case +1: effect.prepend(tr("Inflict:")); break;
                    case +2: effect.prepend(tr("OnBattle:"));break;
                }
                if(!effect.isNull() && !m_status.contains(effect,Qt::CaseSensitive))
                {
                    m_status.append(effect);
                    status_effects->addItem(effect);
                    show=true; y+=18;
                 }
            }//end of for Loop
            if(y<=100){status_box->setFixedSize(200,y);}
            else{status_box->setFixedSize(200,100);}
        }//end of else.
     }//end of loop
    status_box->setVisible(show);
    status_box->adjustSize();
}//end of function
void CharEditor::update_materia_slots()
{
    weapon_slot_8->setHidden(1);
    weapon_slot_7->setHidden(1);
    weapon_slot_6->setHidden(1);
    weapon_slot_5->setHidden(1);
    weapon_slot_4->setHidden(1);
    weapon_slot_3->setHidden(1);
    weapon_slot_2->setHidden(1);
    weapon_slot_1->setHidden(1);
    armor_slot_8->setHidden(1);
    armor_slot_7->setHidden(1);
    armor_slot_6->setHidden(1);
    armor_slot_5->setHidden(1);
    armor_slot_4->setHidden(1);
    armor_slot_3->setHidden(1);
    armor_slot_2->setHidden(1);
    armor_slot_1->setHidden(1);


    weapon_m_link_1->setStyleSheet(QString(""));
    weapon_m_link_2->setStyleSheet(QString(""));
    weapon_m_link_3->setStyleSheet(QString(""));
    weapon_m_link_4->setStyleSheet(QString(""));
    armor_m_link_1->setStyleSheet(QString(""));
    armor_m_link_2->setStyleSheet(QString(""));
    armor_m_link_3->setStyleSheet(QString(""));
    armor_m_link_4->setStyleSheet(QString(""));

     //fill the slots.

     if(data.materias[0].id!=0xFF){weapon_slot_1->setIcon(Materias.Icon(data.materias[0].id));}else{weapon_slot_1->setIcon(QIcon(QString("")));}
     if(data.materias[0].id!=0xFF){weapon_slot_1->setToolTip(Materias.Name(data.materias[0].id));}else{weapon_slot_1->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[1].id!=0xFF){weapon_slot_2->setIcon(Materias.Icon(data.materias[1].id));}else{weapon_slot_2->setIcon(QIcon(QString("")));}
     if(data.materias[1].id!=0xFF){weapon_slot_2->setToolTip(Materias.Name(data.materias[1].id));}else{weapon_slot_2->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[2].id!=0xFF){weapon_slot_3->setIcon(Materias.Icon(data.materias[2].id));}else{weapon_slot_3->setIcon(QIcon(QString("")));}
     if(data.materias[2].id!=0xFF){weapon_slot_3->setToolTip(Materias.Name(data.materias[2].id));}else{weapon_slot_3->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[3].id!=0xFF){weapon_slot_4->setIcon(Materias.Icon(data.materias[3].id));}else{weapon_slot_4->setIcon(QIcon(QString("")));}
     if(data.materias[3].id!=0xFF){weapon_slot_4->setToolTip(Materias.Name(data.materias[3].id));}else{weapon_slot_4->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[4].id!=0xFF){weapon_slot_5->setIcon(Materias.Icon(data.materias[4].id));}else{weapon_slot_5->setIcon(QIcon(QString("")));}
     if(data.materias[4].id!=0xFF){weapon_slot_5->setToolTip(Materias.Name(data.materias[4].id));}else{weapon_slot_5->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[5].id!=0xFF){weapon_slot_6->setIcon(Materias.Icon(data.materias[5].id));}else{weapon_slot_6->setIcon(QIcon(QString("")));}
     if(data.materias[5].id!=0xFF){weapon_slot_6->setToolTip(Materias.Name(data.materias[5].id));}else{weapon_slot_6->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[6].id!=0xFF){weapon_slot_7->setIcon(Materias.Icon(data.materias[6].id));}else{weapon_slot_7->setIcon(QIcon(QString("")));}
     if(data.materias[6].id!=0xFF){weapon_slot_7->setToolTip(Materias.Name(data.materias[6].id));}else{weapon_slot_7->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[7].id!=0xFF){weapon_slot_8->setIcon(Materias.Icon(data.materias[7].id));}else{weapon_slot_8->setIcon(QIcon(QString("")));}
     if(data.materias[7].id!=0xFF){weapon_slot_8->setToolTip(Materias.Name(data.materias[7].id));}else{weapon_slot_8->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[8].id!=0xFF){armor_slot_1->setIcon(Materias.Icon(data.materias[8].id));}else{armor_slot_1->setIcon(QIcon(QString("")));}
     if(data.materias[8].id!=0xFF){armor_slot_1->setToolTip(Materias.Name(data.materias[8].id));}else{armor_slot_1->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[9].id!=0xFF){armor_slot_2->setIcon(Materias.Icon(data.materias[9].id));}else{armor_slot_2->setIcon(QIcon(QString("")));}
     if(data.materias[9].id!=0xFF){armor_slot_2->setToolTip(Materias.Name(data.materias[9].id));}else{armor_slot_2->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[10].id!=0xFF){armor_slot_3->setIcon(Materias.Icon(data.materias[10].id));}else{armor_slot_3->setIcon(QIcon(QString("")));}
     if(data.materias[10].id!=0xFF){armor_slot_3->setToolTip(Materias.Name(data.materias[10].id));}else{armor_slot_3->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[11].id!=0xFF){armor_slot_4->setIcon(Materias.Icon(data.materias[11].id));}else{armor_slot_4->setIcon(QIcon(QString("")));}
     if(data.materias[11].id!=0xFF){armor_slot_4->setToolTip(Materias.Name(data.materias[11].id));}else{armor_slot_4->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[12].id!=0xFF){armor_slot_5->setIcon(Materias.Icon(data.materias[12].id));}else{armor_slot_5->setIcon(QIcon(QString("")));}
     if(data.materias[12].id!=0xFF){armor_slot_5->setToolTip(Materias.Name(data.materias[12].id));}else{armor_slot_5->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[13].id!=0xFF){armor_slot_6->setIcon(Materias.Icon(data.materias[13].id));}else{armor_slot_6->setIcon(QIcon(QString("")));}
     if(data.materias[13].id!=0xFF){armor_slot_6->setToolTip(Materias.Name(data.materias[13].id));}else{armor_slot_6->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[14].id!=0xFF){armor_slot_7->setIcon(Materias.Icon(data.materias[14].id));}else{armor_slot_7->setIcon(QIcon(QString("")));}
     if(data.materias[14].id!=0xFF){armor_slot_7->setToolTip(Materias.Name(data.materias[14].id));}else{armor_slot_7->setToolTip(QString(tr("-Empty-")));}
     if(data.materias[15].id!=0xFF){armor_slot_8->setIcon(Materias.Icon(data.materias[15].id));}else{armor_slot_8->setIcon(QIcon(QString("")));}
     if(data.materias[15].id!=0xFF){armor_slot_8->setToolTip(Materias.Name(data.materias[15].id));}else{armor_slot_8->setToolTip(QString(tr("-Empty-")));}

     //set up weapon
     QString ap_rate =tr("AP:x%1").arg(Items.m_growth_rate(data.weapon +Chars.weapon_offset(data.id)));
     weapon_materia_box->setTitle(ap_rate);
     switch(Items.mslots(data.weapon +Chars.weapon_offset(data.id)))
     {
        case 8:weapon_slot_8->setHidden(0);
        case 7:weapon_slot_7->setHidden(0);
        case 6:weapon_slot_6->setHidden(0);
        case 5:weapon_slot_5->setHidden(0);
        case 4:weapon_slot_4->setHidden(0);
        case 3:weapon_slot_3->setHidden(0);
        case 2:weapon_slot_2->setHidden(0);
        case 1:weapon_slot_1->setHidden(0);
     };
     switch(Items.linked((data.weapon +Chars.weapon_offset(data.id))))
      {
        case 4: weapon_m_link_4->setStyleSheet(Items.Style_mlink());
        case 3: weapon_m_link_3->setStyleSheet(Items.Style_mlink());
        case 2: weapon_m_link_2->setStyleSheet(Items.Style_mlink());
        case 1: weapon_m_link_1->setStyleSheet(Items.Style_mlink());
      };
     //set up armor
     ap_rate =tr("AP:x%1").arg(Items.m_growth_rate(data.armor+256));
     armor_materia_box->setTitle(ap_rate);
     switch(Items.mslots(data.armor +256))
     {
        case 8:armor_slot_8->setHidden(0);
        case 7:armor_slot_7->setHidden(0);
        case 6:armor_slot_6->setHidden(0);
        case 5:armor_slot_5->setHidden(0);
        case 4:armor_slot_4->setHidden(0);
        case 3:armor_slot_3->setHidden(0);
        case 2:armor_slot_2->setHidden(0);
        case 1:armor_slot_1->setHidden(0);
     };
     switch(Items.linked((data.armor +256)))
     {
        case 4: armor_m_link_4->setStyleSheet(Items.Style_mlink());
        case 3: armor_m_link_3->setStyleSheet(Items.Style_mlink());
        case 2: armor_m_link_2->setStyleSheet(Items.Style_mlink());
        case 1: armor_m_link_1->setStyleSheet(Items.Style_mlink());
      };
     if(autostatcalc){calc_stats();}
}
void CharEditor::matId_changed(qint8 id)
{
    if(id>=0 &&id<91){data.materias[mslotsel].id = id;}
    else{data.materias[mslotsel].id = 0xFF;}
    update_materia_slots();
    emit Materias_changed(data.materias[mslotsel]);
    if(autostatcalc){calc_stats();}
}
void CharEditor::matAp_changed(qint32 ap)
{
    if(ap>=0 && ap<16777215)
    {
        int a = (ap & 0xff);
        int b = (ap & 0xff00) >> 8;
        int c = (ap & 0xff0000) >> 16;
        data.materias[mslotsel].ap[0]=a;
        data.materias[mslotsel].ap[1]=b;
        data.materias[mslotsel].ap[2]=c;
    }
    else
    {
        data.materias[mslotsel].ap[0]=0xFF;
        data.materias[mslotsel].ap[1]=0xFF;
        data.materias[mslotsel].ap[2]=0xFF;
    }
    update_materia_slots();
    emit Materias_changed(data.materias[mslotsel]);
}
void CharEditor::weapon_slot_1_clicked(void)
{
    mslotsel = 0;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::weapon_slot_2_clicked(void)
{
    mslotsel = 1;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::weapon_slot_3_clicked(void)
{
    mslotsel = 2;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::weapon_slot_4_clicked(void)
{
    mslotsel = 3;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::weapon_slot_5_clicked(void)
{
    mslotsel = 4;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::weapon_slot_6_clicked(void)
{
    mslotsel = 5;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::weapon_slot_7_clicked(void)
{
    mslotsel = 6;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::weapon_slot_8_clicked(void)
{
    mslotsel = 7;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::armor_slot_1_clicked(void)
{
    mslotsel = 8;
    emit mslotChanged(mslotsel);
     materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::armor_slot_2_clicked(void)
{
    mslotsel = 9;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::armor_slot_3_clicked(void)
{
    mslotsel = 10;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::armor_slot_4_clicked(void)
{
    mslotsel = 11;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::armor_slot_5_clicked(void)
{
    mslotsel = 12;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::armor_slot_6_clicked(void)
{
    mslotsel = 13;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::armor_slot_7_clicked(void)
{
    mslotsel = 14;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::armor_slot_8_clicked(void)
{
    mslotsel = 15;
    emit mslotChanged(mslotsel);
    materia_edit->setMateria(data.materias[mslotsel].id,Materias.ap2num(data.materias[mslotsel].ap));
}
void CharEditor::btn_page_clicked()
{
    if(main_widget->currentIndex()==0)
    {
        main_widget->setCurrentIndex(1);
        btnPage->setText(QString(tr("Character Info")));
        main_layout->removeWidget(btnPage);
        main_layout->removeWidget(main_widget);
        main_layout->addWidget(main_widget);
        main_layout->addWidget(btnPage);
    }
    else if (main_widget->currentIndex()==1)
    {
        main_widget->setCurrentIndex(0);
        btnPage->setText(QString(tr("Equipment / Materia")));
        main_layout->removeWidget(btnPage);
        main_layout->removeWidget(main_widget);
        main_layout->addWidget(btnPage);
        main_layout->addWidget(main_widget);
    }
}
//void setFlags(int,int);
//void setZ_4[4](int);
