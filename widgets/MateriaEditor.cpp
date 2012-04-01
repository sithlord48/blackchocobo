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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "MateriaEditor.h"
/* Path To Common Icons For Copy / Paste / Delete icon*/
#include "static_data/icons/Common_Icons/copy.xpm"
#include "static_data/icons/Common_Icons/paste.xpm"
#include "static_data/icons/Common_Icons/quit.xpm"

MateriaEditor::MateriaEditor(QWidget *parent,int mode):QWidget(parent)
{
    if(mode==0){init_normal_mode();}
    else if(mode ==1){init_compact_mode();}
    init_data();
    init_connections();
}
/*
MateriaEditor::MateriaEditor(QWidget *parent, quint8 materia_id,qint32 materia_ap):QWidget(parent)
{
   this->init_display();
   //we need to initlize the data
   this->init_data();
   this->setMateria(materia_id,materia_ap);
}
*/
void MateriaEditor::init_normal_mode()
{

    QHBoxLayout * type_name_layout = new QHBoxLayout;

    combo_type =new QComboBox;
    combo_materia = new QComboBox;
    combo_type->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
    combo_type->setMinimumHeight(22);
    combo_materia->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
    combo_materia->setMinimumHeight(22);
    type_name_layout->addWidget(combo_type);
    type_name_layout->addWidget(combo_materia);

    QHBoxLayout * ap_layout = new QHBoxLayout;

    sb_ap = new QSpinBox;
    //sb_ap->setWrapping(1);
    sb_ap->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
    sb_ap->setMinimumHeight(22);
    lbl_slash = new QLabel;
    lbl_slash->setText("/");
    lbl_slash->setMinimumHeight(22);
    lcd_max_ap = new QLCDNumber;
    lcd_max_ap->setNumDigits(8);
    lcd_max_ap->setSegmentStyle(QLCDNumber::Flat);
    lcd_max_ap->setMinimumHeight(22);

    btn_rm_materia = new QPushButton;
    btn_rm_materia->setIcon(QIcon::fromTheme("edit-delete",QIcon(QPixmap(quit_xpm))));
    btn_rm_materia->setToolTip(tr("Delete"));
    btn_rm_materia->setMinimumSize(22,22);
    btn_rm_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);

    btn_copy_materia = new QPushButton;
    btn_copy_materia->setIcon(QIcon::fromTheme("edit-copy",QIcon(QPixmap(copy_xpm))));
    btn_copy_materia->setToolTip(tr("Copy"));
    btn_copy_materia->setMinimumSize(22,22);
    btn_copy_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);

    btn_paste_materia = new QPushButton;
    btn_paste_materia->setIcon(QIcon::fromTheme("edit-paste",QIcon(QPixmap(paste_xpm))));
    btn_paste_materia->setToolTip(tr("Paste"));
    btn_paste_materia->setMinimumSize(22,22);
    btn_paste_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);

    ap_layout->addWidget(sb_ap);
    ap_layout->addWidget(lbl_slash);
    ap_layout->addWidget(lcd_max_ap);
    ap_layout->addWidget(btn_copy_materia);
    ap_layout->addWidget(btn_paste_materia);
    ap_layout->addWidget(btn_rm_materia);

    QVBoxLayout *name_ap_layout =  new QVBoxLayout;
    name_ap_layout->addItem(type_name_layout);
    name_ap_layout->addItem(ap_layout);

    frm_name_ap =new QFrame(this);
    frm_name_ap->setLayout(name_ap_layout);
    name_ap_layout->setContentsMargins(6,12,6,6);
    name_ap_layout->setSpacing(3);
    frm_name_ap->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
    frm_name_ap->setMinimumHeight(60);


    box_stars = new QGroupBox(this);
    btn_star1 = new QPushButton;
    btn_star2 = new QPushButton;
    btn_star3 = new QPushButton;
    btn_star4 = new QPushButton;
    btn_star5 = new QPushButton;
    QString style="QPushButton:enabled{background-color: rgba(0,0,0,0);border:0px solid;} QPushButton:hover{background-color:rgba(0,50,50,96);}";
    btn_star1->setStyleSheet(style);
    btn_star2->setStyleSheet(style);
    btn_star3->setStyleSheet(style);
    btn_star4->setStyleSheet(style);
    btn_star5->setStyleSheet(style);
    btn_star1->setFlat(true);
    btn_star2->setFlat(true);
    btn_star3->setFlat(true);
    btn_star4->setFlat(true);
    btn_star5->setFlat(true);
    QHBoxLayout *stars = new QHBoxLayout;
    stars->setContentsMargins(0,0,0,0);
    stars->addWidget(btn_star1);
    stars->addWidget(btn_star2);
    stars->addWidget(btn_star3);
    stars->addWidget(btn_star4);
    stars->addWidget(btn_star5);
    QSpacerItem *spacer1 = new QSpacerItem(30,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    stars->addSpacerItem(spacer1);
    box_stars->setLayout(stars);
    /* Init Skills Area */
    box_skills = new QGroupBox(this);
    lbl_skill1 = new QLabel;
    lbl_skill2 = new QLabel;
    lbl_skill3 = new QLabel;
    lbl_skill4 = new QLabel;
    lbl_skill5 = new QLabel;
    setStarsSize(48);
    box_stats = new QGroupBox(this);
    lbl_stats = new QLabel;

    btn_clear_eskills = new QPushButton;
    btn_clear_eskills->setText(tr("Clear"));
    btn_master_eskills = new QPushButton;
    btn_master_eskills->setText("Master");
    QHBoxLayout *low_eskill_layout = new QHBoxLayout;
    low_eskill_layout->addWidget(btn_master_eskills);
    low_eskill_layout->addWidget(btn_clear_eskills);


    eskill_list = new QListWidget;
    QVBoxLayout * eskill_layout = new QVBoxLayout;
    eskill_layout->addWidget(eskill_list);
    eskill_layout->addItem(low_eskill_layout);

    eskill_group = new QGroupBox;
    eskill_group->setLayout(eskill_layout);
    eskill_group->setHidden(true);
    eskill_group->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);


    QVBoxLayout *skill_layout = new QVBoxLayout;
    skill_layout->addWidget(lbl_skill1);
    skill_layout->addWidget(lbl_skill2);
    skill_layout->addWidget(lbl_skill3);
    skill_layout->addWidget(lbl_skill4);
    skill_layout->addWidget(lbl_skill5);
    skill_layout->addWidget(eskill_group);
    box_skills->setLayout(skill_layout);
    box_skills->setTitle(tr("Skills"));
    skill_layout->setContentsMargins(3,3,0,3);
    skill_layout->setSpacing(3);

    QHBoxLayout *stat_layout = new QHBoxLayout;
    stat_layout->addWidget(lbl_stats);
    box_stats->setTitle(tr("Stat Changes"));
    box_stats->setLayout(stat_layout);
    stat_layout->setContentsMargins(3,0,0,0);
    box_stats->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);


    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0,3,0,3);
    main_layout->setSpacing(3);
    main_layout->addWidget(frm_name_ap);
    main_layout->addWidget(box_stars);
    main_layout->addWidget(box_skills);
    main_layout->addWidget(box_stats);

    QHBoxLayout *Final = new QHBoxLayout(this);
    Final->setContentsMargins(0,0,0,0);
    Final->setSpacing(3);
    Final->addLayout(main_layout);
    this->setLayout(Final);

}
void MateriaEditor::init_compact_mode()
{
    this->setContentsMargins(0,0,0,0);
    QHBoxLayout * type_name_layout = new QHBoxLayout;
    combo_type =new QComboBox;
    combo_type->setMinimumHeight(22);
    combo_type->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    combo_materia = new QComboBox;
    combo_materia->setMinimumHeight(22);
    combo_materia->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);

    btn_rm_materia = new QPushButton;
    btn_rm_materia->setIcon(QIcon::fromTheme("edit-delete",QIcon(QPixmap(quit_xpm))));
    btn_rm_materia->setToolTip(tr("Delete"));
    btn_rm_materia->setMinimumSize(22,22);
    btn_rm_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);

    btn_copy_materia = new QPushButton;
    btn_copy_materia->setIcon(QIcon::fromTheme("edit-copy",QIcon(QPixmap(copy_xpm))));
    btn_copy_materia->setToolTip(tr("Copy"));
    btn_copy_materia->setMinimumSize(22,22);
    btn_copy_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);

    btn_paste_materia = new QPushButton;
    btn_paste_materia->setIcon(QIcon::fromTheme("edit-paste",QIcon(QPixmap(paste_xpm))));
    btn_paste_materia->setToolTip(tr("Paste"));
    btn_paste_materia->setMinimumSize(22,22);
    btn_paste_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);


    type_name_layout->addWidget(combo_type);
    type_name_layout->addWidget(combo_materia);
    type_name_layout->addWidget(btn_copy_materia);
    type_name_layout->addWidget(btn_paste_materia);
    type_name_layout->addWidget(btn_rm_materia);

    QHBoxLayout * ap_layout = new QHBoxLayout;

    sb_ap = new QSpinBox;
    sb_ap->setWrapping(1);
    sb_ap->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    sb_ap->setMinimumHeight(22);
    lbl_slash = new QLabel;
    lbl_slash->setText("/");
    lbl_slash->setMinimumHeight(22);
    lcd_max_ap = new QLCDNumber;
    lcd_max_ap->setNumDigits(8);
    lcd_max_ap->setSegmentStyle(QLCDNumber::Flat);
    lcd_max_ap->setMinimumHeight(22);

    ap_layout->addWidget(sb_ap);
    ap_layout->addWidget(lbl_slash);
    ap_layout->addWidget(lcd_max_ap);

    QFrame *frm_ap = new QFrame(this);
    frm_ap->setLayout(ap_layout);
    frm_ap->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);


    frm_name_ap =new QFrame(this);
    frm_name_ap->setLayout(type_name_layout);

    box_stars = new QGroupBox(this);
    btn_star1 = new QPushButton;
    btn_star2 = new QPushButton;
    btn_star3 = new QPushButton;
    btn_star4 = new QPushButton;
    btn_star5 = new QPushButton;
    QString style="QPushButton:enabled{background-color: rgba(0,0,0,0);border:0px solid;} QPushButton:hover{background-color:rgba(0,50,50,96);}";
    btn_star1->setStyleSheet(style);
    btn_star2->setStyleSheet(style);
    btn_star3->setStyleSheet(style);
    btn_star4->setStyleSheet(style);
    btn_star5->setStyleSheet(style);
    btn_star1->setFlat(true);
    btn_star2->setFlat(true);
    btn_star3->setFlat(true);
    btn_star4->setFlat(true);
    btn_star5->setFlat(true);
    QHBoxLayout *stars = new QHBoxLayout;
    stars->setContentsMargins(0,0,0,0);
    stars->addWidget(btn_star1);
    stars->addWidget(btn_star2);
    stars->addWidget(btn_star3);
    stars->addWidget(btn_star4);
    stars->addWidget(btn_star5);
    box_stars->setLayout(stars);
    box_stars->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);
    /* Init Skills Area */
    box_skills = new QGroupBox(this);
    box_skills->setMaximumHeight(170);
    lbl_skill1 = new QLabel;
    lbl_skill2 = new QLabel;
    lbl_skill3 = new QLabel;
    lbl_skill4 = new QLabel;
    lbl_skill5 = new QLabel;
    setStarsSize(32);

    QVBoxLayout *ap_stars_layout =  new QVBoxLayout;
    ap_stars_layout->addWidget(frm_ap);
    ap_stars_layout->addWidget(box_stars);

    box_stats = new QGroupBox(this);
    lbl_stats = new QLabel;

    btn_clear_eskills = new QPushButton;
    btn_clear_eskills->setText(tr("Clear"));
    btn_master_eskills = new QPushButton;
    btn_master_eskills->setText("Master");
    QHBoxLayout *low_eskill_layout = new QHBoxLayout;
    low_eskill_layout->addWidget(btn_master_eskills);
    low_eskill_layout->addWidget(btn_clear_eskills);
    low_eskill_layout->setContentsMargins(3,0,0,0);


    eskill_list = new QListWidget;
    QVBoxLayout * eskill_layout = new QVBoxLayout;
    eskill_layout->addWidget(eskill_list);
    eskill_layout->addItem(low_eskill_layout);
    eskill_layout->setContentsMargins(3,3,0,0);
    eskill_layout->setSpacing(3);
    eskill_group = new QGroupBox;
    eskill_group->setLayout(eskill_layout);
    eskill_group->setHidden(true);
    eskill_group->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);

    QVBoxLayout *skill_layout = new QVBoxLayout;
    skill_layout->addWidget(lbl_skill1);
    skill_layout->addWidget(lbl_skill2);
    skill_layout->addWidget(lbl_skill3);
    skill_layout->addWidget(lbl_skill4);
    skill_layout->addWidget(lbl_skill5);
    skill_layout->addWidget(eskill_group);
    box_skills->setLayout(skill_layout);
    box_skills->setTitle(tr("Skills"));
    box_skills->setContentsMargins(0,0,0,0);
    skill_layout->setContentsMargins(0,0,0,0);
    skill_layout->setSpacing(2);

    QHBoxLayout *skill_stars_layout = new QHBoxLayout;
    skill_stars_layout->addItem(ap_stars_layout);
    skill_stars_layout->addWidget(box_skills);

    QHBoxLayout *stat_layout = new QHBoxLayout;
    stat_layout->addWidget(lbl_stats);
    stat_layout->setContentsMargins(0,0,0,0);
    box_stats->setTitle(tr("Stat Changes"));
    box_stats->setLayout(stat_layout);
    box_stats->setContentsMargins(3,3,3,3);
    //box_stats->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);


    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0,3,0,0);
    main_layout->setSpacing(3);
    main_layout->addWidget(frm_name_ap);
    main_layout->addItem(skill_stars_layout);
    //main_layout->addWidget(box_stars);
    //main_layout->addWidget(box_skills);
    main_layout->addWidget(box_stats);

    QHBoxLayout *Final = new QHBoxLayout(this);
    Final->setContentsMargins(0,0,0,0);
    Final->setSpacing(2);
    Final->addLayout(main_layout);
    this->setLayout(Final);
    this->setFixedHeight(225);

}
void MateriaEditor::init_connections(void)
{
    connect(btn_star1,SIGNAL(clicked()),this,SLOT(btn_star1_clicked()));
    connect(btn_star2,SIGNAL(clicked()),this,SLOT(btn_star2_clicked()));
    connect(btn_star3,SIGNAL(clicked()),this,SLOT(btn_star3_clicked()));
    connect(btn_star4,SIGNAL(clicked()),this,SLOT(btn_star4_clicked()));
    connect(btn_star5,SIGNAL(clicked()),this,SLOT(btn_star5_clicked()));
    connect(btn_rm_materia,SIGNAL(clicked()),this,SLOT(remove_materia()));
    connect(btn_copy_materia,SIGNAL(clicked()),this,SLOT(copy_materia()));
    connect(btn_paste_materia,SIGNAL(clicked()),this,SLOT(paste_materia()));

    connect(sb_ap,SIGNAL(valueChanged(int)),this,SLOT(sb_ap_changed(int)));
    connect(combo_type,SIGNAL(currentIndexChanged(int)),this,SLOT(type_changed(int)));
    connect(eskill_list,SIGNAL(clicked(QModelIndex)),this,SLOT(eskill_list_clicked(QModelIndex)));
    connect(combo_materia,SIGNAL(currentIndexChanged(QString)),this,SLOT(materia_changed(QString)));
    connect(btn_master_eskills,SIGNAL(clicked()),this,SLOT(btn_master_eskill_clicked()));
    connect(btn_clear_eskills,SIGNAL(clicked()),this,SLOT(btn_clear_eskill_clicked()));
}
void MateriaEditor::init_data()
{
    data = new FF7Materia;
    //Fill Eskill List.
    QListWidgetItem *newItem;
    for(int i=0;i<24;i++)
    {
        newItem = new QListWidgetItem;
        newItem->setText(data->Eskill(i));
        newItem->setCheckState(Qt::Unchecked);
        eskill_list->addItem(newItem);
    }
    eskill_list->setSelectionMode(QAbstractItemView::NoSelection);
    //Fill Combo_type
    combo_type->addItem(data->Icon_AllMateria(),tr("All Materia"));
    combo_type->addItem(data->Icon(0x3B),tr("Magic"));
    combo_type->addItem(data->Icon(0x5A),tr("Summon"));
    combo_type->addItem(data->Icon(0x00),tr("Independent"));
    combo_type->addItem(data->Icon(0x1D),tr("Support"));
    combo_type->addItem(data->Icon(0x24),tr("Command"));

    //Set initial combo_materia info.
    for(int i=0;i<91;i++)
    {
        if(data->Name(i) !="DON'T USE"){combo_materia->addItem(data->Icon(i),data->Name(i));}
    }
    _id=0;
    _current_ap=0;
    buffer_id=0;
    buffer_ap=0;
}

void MateriaEditor::setMateria(quint8 materia_id,qint32 materia_ap)
{
    if (materia_id <91)
    {//valid Materia..
        if(_id != materia_id)
        {
            _id = materia_id;
            _type_icon = QPixmap::fromImage(data->Image(_id));
            _full_star_icon = QPixmap::fromImage(data->Image_FullStar(_id));
            _empty_star_icon = QPixmap::fromImage(data->Image_EmptyStar(_id));
            _name=data->Name(_id);
            _type = data->Type(_id);
            _max_level = data->Levels(_id);
            for(int i=0;i<_max_level;i++){_level_ap[i]=data->Ap(_id,i);}
            emit id_changed(_id);
         }
    }
    else
    {//Invalid Data Reset Materia.
        if(_id != 0xFF){emit id_changed(0xFF);}
        _id=0xFF;
        _current_ap = 16777215;//set since setAp ingores the 0xFF id.
    }
    this->setName();
    this->setAP(materia_ap);
    this->setStats();

}
void MateriaEditor::setAP(qint32 ap)
{
    sb_ap->setMaximum(MaxAP());lcd_max_ap->display(MaxAP());

    if(_id==0xFF){eskill_group->setHidden(true);setLevel();return;}
    else if( (_id ==0x11) || (_id==0x30) || (_id==0x49) ||(_id==0x5A) ||(_id==0x2C))
    {
        sb_ap->setHidden(true);
        lcd_max_ap->setHidden(true);
        lbl_slash->setHidden(true);
        if(_current_ap != ap){_current_ap = ap; emit(ap_changed(_current_ap));}

        if(_id==0x2C)
        {//Eskill Materia Specialness.
            eskill_group->setHidden(false);
            for (int i=0;i<24;i++)
            {
                if (_current_ap & (1 << i)){eskill_list->item(i)->setCheckState(Qt::Checked);}
                else{eskill_list->item(i)->setCheckState(Qt::Unchecked);}
            }
        }
        else{eskill_group->setHidden(true);}
    }
    else
    {//All Other Materia
        eskill_group->setHidden(true);
        sb_ap->setHidden(false);
        lcd_max_ap->setHidden(false);
        lbl_slash->setHidden(false);

        if( (ap <16777215) && (ap<_level_ap[_max_level-1]) )
        {
            _current_ap = ap;
            sb_ap->setValue(_current_ap);
        }
        else
        {
            _current_ap = 16777215;
            sb_ap->setValue(_level_ap[_max_level-1]);
        }
        emit ap_changed(_current_ap);
    }
    setLevel();
}

void MateriaEditor::setName()
{  
    if(_id==0xFF){combo_type->setCurrentIndex(0);combo_materia->setCurrentIndex(-1);}
    else
    {
        if(combo_type->currentIndex()!=0){combo_type->setCurrentIndex(_type);}
        for(int i=0;i<combo_materia->count();i++)
        {//loop thru type and see if name matches if so set index and stop
            if(_name == combo_materia->itemText(i)){combo_materia->setCurrentIndex(i);return;}
        }
    }
}

void MateriaEditor::setStats()
{
    if(_id==0xFF){lbl_stats->clear();}
    else{lbl_stats->setText(data->Stat_String(_id));}
    //Hide If Eskill..
    if(_id==0x2C){box_stats->setHidden(true);}
    else{box_stats->setHidden(false);}
}

void MateriaEditor::setLevel()
{
    _level=0;
    if( (_id==0x2C)||(_id==0x11)||(_id==0x30)||(_id==0x49)||(_id==0x5A)){_level=1;}
    else{for(int i=0;i<_max_level;i++){if(_current_ap >= _level_ap[i]){_level++;}}}
    setStars();
    setSkills();
}

void MateriaEditor::setStars()
{
   //Hide if its eskill Materia

    if((_id==0x2C)||(_id==0x11)||(_id ==0x30)||(_id==0x49)||(_id==0x5A)||(_id==0xFF)){box_stars->setHidden(true);return;}
    else
    {
        box_stars->setHidden(false);
        btn_star1->setHidden(true);
        btn_star2->setHidden(true);
        btn_star3->setHidden(true);
        btn_star4->setHidden(true);
        btn_star5->setHidden(true);
        if(_type !=0)
        {
            btn_star1->setIcon(_empty_star_icon);
            btn_star2->setIcon(_empty_star_icon);
            btn_star3->setIcon(_empty_star_icon);
            btn_star4->setIcon(_empty_star_icon);
            btn_star5->setIcon(_empty_star_icon);
        }
        switch(_level)
        {//no break on purpose
            case 5: btn_star5->setIcon(_full_star_icon);
            case 4: btn_star4->setIcon(_full_star_icon);
            case 3: btn_star3->setIcon(_full_star_icon);
            case 2: btn_star2->setIcon(_full_star_icon);
            case 1: btn_star1->setIcon(_full_star_icon);
        };
        switch(_max_level)
        {//no break on purpose.
            case 5: btn_star5->setHidden(false);
            case 4: btn_star4->setHidden(false);
            case 3: btn_star3->setHidden(false);
            case 2: btn_star2->setHidden(false);
            case 1: btn_star1->setHidden(false);
        };
    }
}

void MateriaEditor::setSkills()
{

    lbl_skill1->setVisible(0);
    lbl_skill2->setVisible(0);
    lbl_skill3->setVisible(0);
    lbl_skill4->setVisible(0);
    lbl_skill5->setVisible(0);
    lbl_skill1->clear();
    lbl_skill2->clear();
    lbl_skill3->clear();
    lbl_skill4->clear();
    lbl_skill5->clear();
    if((_id==0xFF)||(_id==0x2C)){return;}
    else if(_id==0x11 || (_id ==0x30) || (_id==0x49) ||(_id==0x5A))
    {
        lbl_skill5->setVisible(1);
        lbl_skill4->setVisible(1);
        lbl_skill3->setVisible(1);
        lbl_skill2->setVisible(1);
        lbl_skill1->setVisible(1);
        lbl_skill1->setText(data->Skills(_id,0));
        return;
    }
    else
    {

        lbl_skill5->setVisible(1);
        lbl_skill4->setVisible(1);
        lbl_skill3->setVisible(1);
        lbl_skill2->setVisible(1);
        lbl_skill1->setVisible(1);
        switch (_level)
        {// no breaks on purpose
            case 5:lbl_skill5->setText(data->Skills(_id,4));
            case 4:lbl_skill4->setText(data->Skills(_id,3));
            case 3:lbl_skill3->setText(data->Skills(_id,2));
            case 2:lbl_skill2->setText(data->Skills(_id,1));
            case 1:lbl_skill1->setText(data->Skills(_id,0));
        }
    }
}

void MateriaEditor::btn_star1_clicked(){setAP(_level_ap[0]);setLevel();}
void MateriaEditor::btn_star2_clicked(){setAP(_level_ap[1]);setLevel();}
void MateriaEditor::btn_star3_clicked(){setAP(_level_ap[2]);setLevel();}
void MateriaEditor::btn_star4_clicked(){setAP(_level_ap[3]);setLevel();}
void MateriaEditor::btn_star5_clicked(){setAP(16777215);setLevel();}

void MateriaEditor::materia_changed(QString new_name)
{
    for(int i=0;i<91;i++)
    {
        if(data->Name(i)==new_name){if(_id != i){setMateria(i,_current_ap);}return;}
    }
}

void MateriaEditor::type_changed(int new_type)
{
    combo_materia->clear();
    combo_materia->blockSignals(1);
    if(new_type ==0)for(int i=0;i<91;i++){if(data->Name(i) !="DON'T USE"){combo_materia->addItem(data->Icon(i),data->Name(i));}}
    else{for(int i=0;i<91;i++){if(data->Type(i) == new_type){combo_materia->addItem(data->Icon(i),data->Name(i));}}}
    combo_materia->blockSignals(0);
}
/*
qint32 MateriaEditor::raw_data(void)
{
    qint32 materia;
    materia = _id |= _current_ap <<8;
    return materia;
}
*/
void MateriaEditor::remove_materia(void){setMateria(0xFF,0);}

qint32 MateriaEditor::ap(void){return _current_ap;}
qint8 MateriaEditor::id(void){return _id;}
void MateriaEditor::sb_ap_changed(qint32 ap){setAP(ap);}

void MateriaEditor::eskill_list_clicked(QModelIndex index)
{
    int i = index.row();
    if (eskill_list->item(i)->checkState() == Qt::Checked){_current_ap |= (1<<i);}
    else{_current_ap &= ~(1<<i);}
    emit(ap_changed(_current_ap));
}
qint32 MateriaEditor::MaxAP(void)
{
    if( (_id!=0x11) || (_id !=0x30) || (_id!=0x49) ||(_id!=0x5A) || (_id!=0x2C))
    {
        return _level_ap[_max_level-1];
    }
    else{return 16777215;}
}

void MateriaEditor::copy_materia(){buffer_id= _id; buffer_ap = _current_ap;}
void MateriaEditor::paste_materia(){setMateria(buffer_id,buffer_ap);}
void MateriaEditor::btn_clear_eskill_clicked()
{
    for(int i=0;i<24;i++)
    {
        eskill_list->item(i)->setCheckState(Qt::Unchecked);
    }
    if(_current_ap != 0)
    {
        _current_ap = 0;
        emit ap_changed(_current_ap);
    }
}

void MateriaEditor::btn_master_eskill_clicked()
{
    for(int i=0;i<24;i++)
    {
        eskill_list->item(i)->setCheckState(Qt::Checked);
    }
    if(_current_ap != 16777215)
    {
       _current_ap = 16777215;
       emit ap_changed(_current_ap);
    }
}
void MateriaEditor::setStarsSize(int size)
{
    btn_star1->setFixedSize(size,size);
    btn_star2->setFixedSize(size,size);
    btn_star3->setFixedSize(size,size);
    btn_star4->setFixedSize(size,size);
    btn_star5->setFixedSize(size,size);
    btn_star1->setIconSize(QSize(size,size));
    btn_star2->setIconSize(QSize(size,size));
    btn_star3->setIconSize(QSize(size,size));
    btn_star4->setIconSize(QSize(size,size));
    btn_star5->setIconSize(QSize(size,size));
    box_stars->setFixedHeight(size +6);
    box_stars->adjustSize();
}
