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
#include <QMessageBox>
MateriaEditor::MateriaEditor(QWidget *parent):QWidget(parent)
{
    init_display();
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
void MateriaEditor::init_display()
{//Make Widgets and set Properties.
    //Widget Creation.
    combo_type =new QComboBox;
    combo_materia = new QComboBox;
    sb_ap = new QSpinBox;
    lbl_slash = new QLabel;
    lcd_max_ap = new QLCDNumber;
    btn_rm_materia = new QPushButton;
    btn_copy_materia = new QPushButton;
    btn_paste_materia = new QPushButton;
    box_stars = new QGroupBox(this);
    btn_star1 = new QPushButton;
    btn_star2 = new QPushButton;
    btn_star3 = new QPushButton;
    btn_star4 = new QPushButton;
    btn_star5 = new QPushButton;
    eskill_list = new QListWidget;
    box_skills = new QGroupBox;
    list_skills = new QListWidget;
    box_stats = new QGroupBox;
    lbl_stats = new QLabel;
    btn_clear_eskills = new QPushButton;
    btn_master_eskills = new QPushButton;
    eskill_group = new QGroupBox;
    list_status = new QListWidget;
    box_status_effects = new QGroupBox;
    frm_name_type =new QFrame;
    frm_ap = new QFrame;
    v_spacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding);
    //Special Properties Of Above Widgets
    sb_ap->setWrapping(1);
    lcd_max_ap->setNumDigits(8);
    lcd_max_ap->setSegmentStyle(QLCDNumber::Flat);
    btn_rm_materia->setIcon(QIcon::fromTheme("edit-delete",QIcon(QPixmap(quit_xpm))));
    btn_copy_materia->setIcon(QIcon::fromTheme("edit-copy",QIcon(QPixmap(copy_xpm))));
    btn_paste_materia->setIcon(QIcon::fromTheme("edit-paste",QIcon(QPixmap(paste_xpm))));

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
    //Set Label Text
    lbl_slash->setText("/");
    btn_clear_eskills->setText(tr("Clear"));
    btn_master_eskills->setText(tr("Master"));
    box_skills->setTitle(tr("Skills"));
    box_stats->setTitle(tr("Stat Changes"));
    btn_rm_materia->setToolTip(tr("Delete"));
    btn_copy_materia->setToolTip(tr("Copy"));
    btn_paste_materia->setToolTip(tr("Paste"));
    box_status_effects->setTitle(tr("Status"));
    //set Hidden
    eskill_group->setHidden(true);
    box_status_effects->setHidden(true);
    box_stats->setHidden(true);
    //set Minimum Sizes.
    btn_copy_materia->setMinimumSize(22,22);
    btn_paste_materia->setMinimumSize(22,22);
    sb_ap->setMinimumHeight(22);
    combo_type->setMinimumHeight(22);
    combo_materia->setMinimumHeight(22);
    lbl_slash->setMinimumHeight(22);
    lcd_max_ap->setMinimumHeight(22);
    btn_rm_materia->setMinimumSize(22,22);
    list_skills->setFixedHeight((this->font().pointSize()*10)+6);
    list_skills->setSelectionMode(QAbstractItemView::NoSelection);
    list_status->setFixedHeight((this->font().pointSize()*10)+6);
    list_status->setSelectionMode(QAbstractItemView::NoSelection);
    //size policies
    combo_materia->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
    combo_type->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
    sb_ap->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
    btn_rm_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    btn_copy_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    btn_paste_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    box_stats->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    frm_ap->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    box_status_effects->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);
//Set up display
    this->setContentsMargins(0,6,0,0);
    QHBoxLayout * type_name_layout = new QHBoxLayout;
    type_name_layout->addWidget(combo_type);
    type_name_layout->addWidget(combo_materia);
    type_name_layout->addWidget(btn_copy_materia);
    type_name_layout->addWidget(btn_paste_materia);
    type_name_layout->addWidget(btn_rm_materia);
    type_name_layout->setContentsMargins(3,6,0,0);
    QHBoxLayout * ap_layout = new QHBoxLayout;
    ap_layout->addWidget(sb_ap);
    ap_layout->addWidget(lbl_slash);
    ap_layout->addWidget(lcd_max_ap);
    ap_layout->setContentsMargins(3,0,0,0);

    frm_name_type->setLayout(type_name_layout);
    frm_ap->setLayout(ap_layout);


    QHBoxLayout *stars = new QHBoxLayout;
    stars->setContentsMargins(3,0,0,0);
    stars->addWidget(btn_star1);
    stars->addWidget(btn_star2);
    stars->addWidget(btn_star3);
    stars->addWidget(btn_star4);
    stars->addWidget(btn_star5);
    QSpacerItem *spacer1 = new QSpacerItem(30,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    stars->addSpacerItem(spacer1);
    box_stars->setLayout(stars);


    /* Init Skills Area */
    QHBoxLayout *ap_stars_layout =  new QHBoxLayout;
    ap_stars_layout->addWidget(box_stars);
    ap_stars_layout->addWidget(frm_ap);

    QHBoxLayout *low_eskill_layout = new QHBoxLayout;
    low_eskill_layout->addWidget(btn_master_eskills);
    low_eskill_layout->addWidget(btn_clear_eskills);

    QVBoxLayout * eskill_layout = new QVBoxLayout;
    eskill_layout->addWidget(eskill_list);
    eskill_layout->addItem(low_eskill_layout);
    eskill_layout->setContentsMargins(0,0,0,0);
    eskill_group->setLayout(eskill_layout);

    QVBoxLayout *skill_layout = new QVBoxLayout;
    skill_layout->addWidget(list_skills);
    skill_layout->addWidget(eskill_group);

    box_skills->setLayout(skill_layout);
    skill_layout->setContentsMargins(3,0,0,0);
    skill_layout->setSpacing(2);

    QHBoxLayout *stat_layout = new QHBoxLayout;
    stat_layout->addWidget(lbl_stats);
    stat_layout->setContentsMargins(3,0,0,0);
    box_stats->setLayout(stat_layout);

    QHBoxLayout * status_effect_layout = new QHBoxLayout;
    status_effect_layout->addWidget(list_status);
    box_status_effects->setLayout(status_effect_layout);

    QHBoxLayout *skill_status_layout = new QHBoxLayout;
    skill_status_layout->addWidget(box_skills);
    skill_status_layout->addWidget(box_status_effects);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(3,0,0,0);
    main_layout->setSpacing(3);
    main_layout->addWidget(frm_name_type);
    main_layout->addItem(ap_stars_layout);
    main_layout->addItem(skill_status_layout);
    main_layout->addWidget(box_stats);

    QVBoxLayout *Final = new QVBoxLayout(this);
    Final->setSpacing(0);
    Final->addLayout(main_layout);
    Final->addSpacerItem(v_spacer);
    Final->setContentsMargins(3,6,0,0);
    this->setLayout(Final);
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
            _skill_list = data->Skills(_id);
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

    if( (_id ==0x11) || (_id==0x30) || (_id==0x49) ||(_id==0x5A) ||(_id==0x2C))
    {
        frm_ap->setHidden(true);
        if(_current_ap != ap){_current_ap = ap; emit(ap_changed(_current_ap));}
        if(_id==0x2C)
        {//Eskill Materia Specialness.
            for (int i=0;i<24;i++)
            {
                if (_current_ap & (1 << i)){eskill_list->item(i)->setCheckState(Qt::Checked);}
                else{eskill_list->item(i)->setCheckState(Qt::Unchecked);}
            }
        }
    }
    else if(_id ==0xFF){frm_ap->setHidden(false);}
    else
    {//All Other Materia
        frm_ap->setHidden(false);
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
    list_status->clear();
    lbl_stats->clear();
    QString title = tr("Skills");
    if(_id !=0xFF)
    {
        if(data->Element(_id)!="")
        {
            title.append("-");
            title.append(data->Element(_id));
        }
        if(data->Stat_String(_id)!="")
        {
            lbl_stats->setText(data->Stat_String(_id));
            box_stats->setHidden(false);
        }
        else{box_stats->setHidden(true);}
        if(data->Status(_id).at(0).toAscii() !="")
        {
            list_status->addItems(data->Status(_id));
            box_status_effects->setHidden(false);
            box_status_effects->setFixedWidth(this->width()/3);
            box_skills->adjustSize();
        }
        else{box_status_effects->setHidden(true);}
        box_skills->setTitle(title);
    }
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
    list_skills->clear();
    if(_id==0x11 || (_id ==0x30) || (_id==0x49) ||(_id==0x5A))
    {
        list_skills->setHidden(false);
        eskill_group->setHidden(true);
        list_skills->addItem(_skill_list.at(0));
        v_spacer->changeSize(0,0,QSizePolicy::Preferred,QSizePolicy::Expanding);
    }
    else if( _id ==0x2C)
    {
        list_skills->setHidden(true);
        eskill_group->setHidden(false);
        v_spacer->changeSize(0,6,QSizePolicy::Preferred,QSizePolicy::Fixed);
    }
    else if(_id ==0xFF)
    {
        list_skills->setHidden(true);
        eskill_group->setHidden(true);
        v_spacer->changeSize(0,0,QSizePolicy::Preferred,QSizePolicy::Expanding);
    }
    else
    {
        list_skills->setHidden(false);
        eskill_group->setHidden(true);
        v_spacer->changeSize(0,0,QSizePolicy::Preferred,QSizePolicy::Expanding);
        switch (_level)
        {// no breaks on purpose
            case 5:if(_skill_list.count()>4){list_skills->insertItem(0,_skill_list.at(4));}
            case 4:if(_skill_list.count()>3){list_skills->insertItem(0,_skill_list.at(3));}
            case 3:if(_skill_list.count()>2){list_skills->insertItem(0,_skill_list.at(2));}
            case 2:if(_skill_list.count()>1){list_skills->insertItem(0,_skill_list.at(1));}
            case 1:if(_skill_list.count()>0){list_skills->insertItem(0,_skill_list.at(0));}
        }
    }
    this->layout()->update();
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

void MateriaEditor::btn_clear_eskill_clicked(){if(_current_ap!=0){setAP(0);}}
void MateriaEditor::btn_master_eskill_clicked(){if(_current_ap != 16777215){setAP(16777215);}}

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
