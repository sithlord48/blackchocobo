/****************************************************************************/
//    copyright 2012 -2019  Chris Rizzitello <sithlord48@gmail.com>         //
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

MateriaEditor::MateriaEditor(QWidget *parent):QWidget(parent)
{
	init_display();
	setMateria(FF7Materia::EmptyId,FF7Materia::MaxMateriaAp);//Smallest Possible Size. ready for use now.
}
MateriaEditor::MateriaEditor(quint8 materia_id,qint32 materia_ap,QWidget *parent):QWidget(parent)
{
	init_display();
	setMateria(materia_id,materia_ap);
}
void MateriaEditor::init_display()
{
    _id=0;
    _current_ap = 0;
    buffer_id = 0;
    buffer_ap = 0;
    _editable = true;
    data = new FF7Materia;
    _iconSize= QSize(fontMetrics().height(), fontMetrics().height());
    _highlightColor = QString("%1,%2,%3,128").arg(QString::number(this->palette().highlight().color().red()),QString::number(this->palette().highlight().color().green()),QString::number(this->palette().highlight().color().blue()));
    v_spacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding);
//Set up display
	this->setContentsMargins(0,0,0,0);

    auto main_layout = new QVBoxLayout;
	main_layout->setContentsMargins(3,0,0,0);
	main_layout->setSpacing(2);
    main_layout->addLayout(makeNameLayout());
    main_layout->addWidget(makeStarWidget());
    main_layout->addWidget(makeSkillWidget());
    main_layout->addWidget(makeStatWidget());

    auto Final = new QVBoxLayout(this);
	Final->setSpacing(0);
	Final->addLayout(main_layout);
    Final->addSpacerItem(v_spacer);
	Final->setContentsMargins(6,6,6,0);
    setLayout(Final);
}


void MateriaEditor::setMateria(quint8 materia_id,qint32 materia_ap)
{
	if (materia_id <91)
	{//valid Materia..
		if(_id != materia_id)
		{
			_id = materia_id;
			sb_ap->setEnabled(1);
            emit id_changed(qint8(_id));
		 }
	}
	else
	{//Invalid Data Reset Materia.
        if(_id != FF7Materia::EmptyId){emit id_changed(qint8(FF7Materia::EmptyId));}
		_id=FF7Materia::EmptyId;
		sb_ap->setEnabled(0);
		sb_ap->setValue(FF7Materia::MaxMateriaAp);
		_current_ap = FF7Materia::MaxMateriaAp;//set since setAp ingores the 0xFF id.
		box_status_effects->setHidden(true);
		box_stats->setHidden(true);
	}
	this->setName();
	this->setAP(materia_ap);
	this->setStats();


}
void MateriaEditor::setAP(qint32 ap)
{
	sb_ap->setMaximum(MaxAP());
	lbl_max_ap->setText(QString(" %1").arg(QString::number(MaxAP())));

	if( (_id ==FF7Materia::Underwater) || (_id==FF7Materia::MasterCommand) || (_id==FF7Materia::MasterMagic) ||(_id==FF7Materia::MasterSummon) ||(_id==FF7Materia::EnemySkill))
	{
		frm_ap_stars->setHidden(true);
		if(_current_ap != ap){_current_ap = ap; emit(ap_changed(_current_ap));}
		if(_id==FF7Materia::EnemySkill)
		{//Eskill Materia Specialness.
			for (int i=0;i<24;i++)
			{
				if (_current_ap & (1 << i)){eskill_list->item(i)->setCheckState(Qt::Checked);}
				else{eskill_list->item(i)->setCheckState(Qt::Unchecked);}
			}
		}
	}
	else if(_id ==FF7Materia::EmptyId)
	{
		frm_ap_stars->setHidden(true);
		lbl_max_ap->setText("");
	}
	else
	{//All Other Materia
		frm_ap_stars->setHidden(false);
		if( (ap <FF7Materia::MaxMateriaAp) && (ap< data->ap(_id,data->levels(_id)-1)) )
		{
			_current_ap = ap;
			sb_ap->setValue(_current_ap);
		}
		else
		{
			_current_ap = FF7Materia::MaxMateriaAp;
			sb_ap->setValue(data->ap(_id,data->levels(_id)-1));
		}
		emit ap_changed(_current_ap);
	}
	setLevel();
}

void MateriaEditor::setName()
{
    if(_id==FF7Materia::EmptyId) {
        combo_type->setCurrentIndex(0);
        combo_materia->setCurrentIndex(-1);
        lbl_materiaName->clear();
        lbl_materiaIcon->setPixmap(QPixmap());
    } else {
        lbl_materiaIcon->setPixmap(QPixmap::fromImage(data->image(_id)));
		lbl_materiaName->setText(data->name(_id));
        if(combo_type->currentIndex()!=FF7Materia::Unknown) {
            combo_type->setCurrentIndex(data->type(_id));
        }
        for(int i=0;i<combo_materia->count();i++) {//loop thru type and see if name matches if so set index and stop
            if(data->name(_id) == combo_materia->itemText(i)) {
                combo_materia->setCurrentIndex(i);
                return;
            }
		}
	}
}

void MateriaEditor::setStats()
{
	list_status->clear();
	lbl_stats->clear();
	QString title = tr("Skills");
	if(_id !=FF7Materia::EmptyId)
	{
		if(data->element(_id)!="")
		{
			title.append("-");
			title.append(data->element(_id));
		}
		if(data->statString(_id)!="")
		{
			lbl_stats->setText(data->statString(_id));
			box_stats->setHidden(false);
		}
		else{box_stats->setHidden(true);}
		if(data->status(_id).at(0).toLocal8Bit() !="")
		{
			list_status->addItems(data->status(_id));
			box_status_effects->setFixedWidth(this->width()/3);
			box_status_effects->setHidden(false);
		}
		else{box_status_effects->setHidden(true);}
		box_skills->setTitle(title);
	}
}
void MateriaEditor::setLevel()
{
	_level=0;
    if( _id == FF7Materia::EmptyId){/*catch to avoid CID 25848*/ }
	else if( (_id==FF7Materia::EnemySkill)||(_id==FF7Materia::Underwater)||(_id==FF7Materia::MasterCommand)||(_id==FF7Materia::MasterMagic)||(_id==FF7Materia::MasterSummon)){_level=1;}
	else{for(int i=0;i<data->levels(_id);i++){if(_current_ap >= data->ap(_id,i)){_level++;}}}
	setStars();
	setSkills();
}

void MateriaEditor::setStars()
{
   //Hide if its eskill Materia
    if((_id == FF7Materia::EnemySkill)
     ||(_id == FF7Materia::Underwater)
     ||(_id == FF7Materia::MasterCommand)
     ||(_id == FF7Materia::MasterMagic)
     ||(_id == FF7Materia::MasterSummon)
     ||(_id == FF7Materia::EmptyId)) {
        box_stars->setHidden(true);
        return;
    } else {
		box_stars->setHidden(false);
        for (QPushButton *button : qAsConst(btn_stars)) {
            button->setHidden(true);
        }
        if(data->type(_id) !=0) {
            for (QPushButton *button : qAsConst(btn_stars)) {
                button->setIcon(QPixmap::fromImage(data->imageEmptyStar(_id)).scaled(button->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
            }
		}
        for( int i = 0 ; i <_level ;i ++) {
            btn_stars.at(i)->setIcon(QPixmap::fromImage(data->imageFullStar(_id)).scaled(btn_stars.at(i)->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        }

        for( int i = 0 ; i < data->levels(_id) ;i ++) {
            btn_stars.at(i)->setHidden(false);
        }
	}
}

void MateriaEditor::setSkills()
{
	list_skills->clear();
	if( _id ==FF7Materia::EnemySkill)
	{
		box_skills->setHidden(false);
		list_skills->setHidden(true);
		eskill_group->setHidden(false);
		v_spacer->changeSize(0,0,QSizePolicy::Fixed,QSizePolicy::Fixed);
		v_spacer->invalidate();
	}
	else if(_id ==FF7Materia::EmptyId)
	{
		box_skills->setHidden(true);
		list_skills->setHidden(true);
		eskill_group->setHidden(true);
		v_spacer->changeSize(0,0,QSizePolicy::Preferred,QSizePolicy::Expanding);
		v_spacer->invalidate();
	}
	else
	{
		box_skills->setHidden(false);
		list_skills->setHidden(false);
		eskill_group->setHidden(true);
		v_spacer->changeSize(0,0,QSizePolicy::Preferred,QSizePolicy::Expanding);
		v_spacer->invalidate();

        for (int i=0; i <_level; i++) {
            if(data->skills(_id).count()>i){list_skills->insertItem(0,data->skills(_id).at(i));}
        }
    }
    frm_skill_status->adjustSize();
    layout()->update();
    adjustSize();
}

void MateriaEditor::typeChanged(int new_type)
{
    combo_materia->clear();
    combo_materia->blockSignals(1);
    if(new_type ==0) {
        for(int i=0;i<91;i++) {
            if(data->name(i) !="DON'T USE") {
                combo_materia->addItem(data->icon(i),data->name(i));
            }
        }
    } else {
        for(int i=0;i<91;i++) {
            if(data->type(i) == new_type) {
                combo_materia->addItem(data->icon(i),data->name(i));
            }
        }
    }
    if(_id !=FF7Materia::EmptyId) {
        combo_materia->setCurrentIndex(combo_materia->findText(data->name(_id)));
    } else {
        combo_materia->setCurrentIndex(-1);
    }
    combo_materia->blockSignals(0);
}

void MateriaEditor::materia_changed(QString new_name)
{
    for(quint8 i=0;i<91;i++)
	{
        if(data->name(i)==new_name){if(_id != i){setMateria(i,_current_ap);}return;}
	}
}

qint32 MateriaEditor::ap(void){return _current_ap;}
qint8 MateriaEditor::id(void){return qint8(_id);}

qint32 MateriaEditor::MaxAP(void)
{
	if( (_id==FF7Materia::Underwater) || (_id ==FF7Materia::MasterCommand) || (_id==FF7Materia::MasterMagic) ||(_id==FF7Materia::MasterSummon) || (_id==FF7Materia::EnemySkill))
	{
		return FF7Materia::MaxMateriaAp;
	}
	else{return data->ap(_id,data->levels(_id)-1);}
}

void MateriaEditor::setStarsSize(int size)
{
    QSize iconSize (size, size);
    for( QPushButton* button : qAsConst(btn_stars)) {
        button->setFixedSize(iconSize);
        button->setIconSize(iconSize);
    }
    box_stars->setFixedHeight(size +(size/8));
	setStars();
	box_stars->adjustSize();

    auto layout = dynamic_cast<QGridLayout*>(frm_ap_stars->layout());

    if(size <= sb_ap->contentsRect().height()) {
        layout->addWidget(box_stars, 0, 0, 1, 1, Qt::AlignLeft);
        layout->addWidget(frm_ap, 0, 1, 1, 1, Qt::AlignRight);
        if(box_stars->sizeHint().height() < frm_ap->sizeHint().height()) {
            frm_ap_stars->setFixedHeight(frm_ap->sizeHint().height() + 6);
        } else {
            frm_ap_stars->setFixedHeight(box_stars->sizeHint().height() + 6);
        }
    } else {
        layout->addWidget(box_stars, 0, 0, 1, 1, Qt::AlignLeft);
        layout->addWidget(frm_ap, 1, 0, 1, 1, Qt::AlignLeft);
        frm_ap_stars->setFixedHeight((size +(size/6)) + (frm_ap->sizeHint().height()+6));
	}
	frm_ap_stars->adjustSize();
}

bool MateriaEditor::isEditable(void){return _editable;}

void MateriaEditor::setEditable(bool edit)
{
    _editable = edit;
	editMode();
}

void MateriaEditor::editMode(void)
{
    for (QPushButton* button : qAsConst(btn_stars)) {
        button->blockSignals(!_editable);
    }

    if(_id != FF7Materia::EmptyId) {
        sb_ap->setEnabled(_editable);
    }
    btn_paste_materia->setHidden(!_editable);
    btn_rm_materia->setHidden(!_editable);
    combo_materia->setHidden(!_editable);
    combo_type->setHidden(!_editable);

    lbl_materiaIcon->setHidden(_editable);
    lbl_materiaName->setHidden(_editable);
    eskillButtons->setHidden(!_editable);

    if(_editable) {
        for(int i=0;i<eskill_list->count();i++) {
            eskill_list->item(i)->setFlags(eskill_list->item(i)->flags() |= Qt::ItemIsUserCheckable);
        }
        eskill_list->setStyleSheet(_itemStyle.arg(_highlightColor, QString::number(fontMetrics().height())));
        for (QPushButton* button : qAsConst(btn_stars)) {
            button->setStyleSheet(_buttonStyle.arg(_highlightColor));
        }
    } else {
       for(int i=0;i<eskill_list->count();i++) {
           eskill_list->item(i)->setFlags(eskill_list->item(i)->flags() &=~Qt::ItemIsUserCheckable);
       }
       QString emptyColor = QStringLiteral("0,0,0,0");
       eskill_list->setStyleSheet(_itemStyle.arg(emptyColor, QString::number(fontMetrics().height())));
       for (QPushButton* button : qAsConst(btn_stars)) {
           button->setStyleSheet(_buttonStyle.arg(emptyColor));
       }
   }
}

void MateriaEditor::setEditableMateriaCombo(bool enabled)
{
	combo_materia->setEditable(enabled);
	combo_materia->setInsertPolicy(QComboBox::NoInsert);
}

QPushButton* MateriaEditor::newStyledButton(const QIcon &icon, QKeySequence shortcut, const QString &tooltip, QWidget *parent)
{
    auto newButton = new QPushButton(parent);
    newButton->setIcon(icon);
    newButton->setStyleSheet(_buttonStyle.arg(_highlightColor));
    newButton->setShortcut(shortcut);
    newButton->setToolTip(tooltip);
    newButton->setIconSize(_iconSize);
    newButton->setMaximumSize(_iconSize);
    newButton->setFlat(true);
    return newButton;
}

QHBoxLayout* MateriaEditor::makeNameLayout()
{
    combo_type =new QComboBox;
    combo_type->setIconSize(_iconSize);
    combo_type->setMinimumHeight(fontMetrics().height() + fontMetrics().xHeight());
    combo_type->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    combo_type->addItem(QIcon(QPixmap::fromImage(data->imageAllMateria())), tr("All Materia"));
    combo_type->addItem(QIcon(data->pixmap(FF7Materia::MasterMagic)), tr("Magic"));
    combo_type->addItem(QIcon(data->pixmap(FF7Materia::MasterSummon)), tr("Summon"));
    combo_type->addItem(QIcon(data->pixmap(FF7Materia::Underwater)), tr("Independent"));
    combo_type->addItem(QIcon(data->pixmap(FF7Materia::StealAsWell)), tr("Support"));
    combo_type->addItem(QIcon(data->pixmap(FF7Materia::MasterCommand)), tr("Command"));
    connect(combo_type, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MateriaEditor::typeChanged);

    combo_materia = new QComboBox;
    combo_materia->setIconSize(_iconSize);
    combo_materia->setMinimumHeight(fontMetrics().height());
    combo_materia->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    for(int i=0;i<91;i++) {
        if(data->name(i) !="DON'T USE"){combo_materia->addItem(data->pixmap(i), data->name(i));}
    }
    connect(combo_materia, QOverload<const QString&>::of(&QComboBox::currentIndexChanged), this, &MateriaEditor::materia_changed);

    btn_rm_materia = newStyledButton(QIcon::fromTheme(QString("edit-clear"), QPixmap(":/common/edit-clear"))
                                    , QKeySequence::Delete
                                    , tr("Delete")
                                    , this);
    connect(btn_rm_materia, &QPushButton::clicked, this, [this] {
        setMateria(FF7Materia::EmptyId,FF7Materia::MaxMateriaAp);
    });


    btn_copy_materia = newStyledButton(QIcon::fromTheme(QString("edit-copy"),QPixmap(":/common/edit-copy"))
                , QKeySequence::Copy
                , tr("Copy")
                , this);
    connect(btn_copy_materia, &QPushButton::clicked, this, [this] {
        buffer_id = _id;
        buffer_ap = _current_ap;
    });

    btn_paste_materia = newStyledButton(QIcon::fromTheme(QString("edit-paste"),QPixmap(":/common/edit-paste"))
                                        , QKeySequence::Paste
                                        , tr("Paste")
                                        , this);
    connect(btn_paste_materia, &QPushButton::clicked, this, [this] {
        setMateria(buffer_id, buffer_ap);
    });

    lbl_materiaIcon = new QLabel;
    lbl_materiaIcon->setFixedSize(_iconSize);
    lbl_materiaIcon->setScaledContents(true);
    lbl_materiaIcon->setHidden(_editable);

    lbl_materiaName= new QLabel;
    lbl_materiaName->setHidden(_editable);

    auto layout = new QHBoxLayout;
    layout->addWidget(lbl_materiaIcon);
    layout->addWidget(lbl_materiaName);
    layout->addWidget(combo_type);
    layout->addWidget(combo_materia);
    layout->addWidget(btn_copy_materia);
    layout->addWidget(btn_paste_materia);
    layout->addWidget(btn_rm_materia);
    layout->setContentsMargins(3,0,0,0);
    return layout;
}

QWidget* MateriaEditor::makeStarWidget()
{
    sb_ap = new QSpinBox;
    sb_ap->setWrapping(1);
    sb_ap->setAlignment(Qt::AlignCenter);
    sb_ap->setFixedSize(fontMetrics().width(QChar('W'))*7, fontMetrics().height() + fontMetrics().xHeight());
    connect(sb_ap, QOverload<int>::of(&QSpinBox::valueChanged), this, [this] (const qint32 ap) {
        setAP(ap);
    });

    box_stars = new QFrame;
    for (int i = 0; i < 5; i++) {
        btn_stars.replace(i, newStyledButton());
        if(i < 4) {
            connect(btn_stars.at(i), &QPushButton::clicked, this, [this, i] {
                setAP(data->ap(_id, i));
                setLevel();
            });
        } else {
            connect(btn_stars.at(i), &QPushButton::clicked, this, [this] {
                setAP(FF7Materia::MaxMateriaAp);
                setLevel();
            });
        }
    }
    auto lbl_slash = new QLabel("/");
    lbl_slash->setFixedWidth(this->font().pointSize());

    lbl_max_ap = new QLabel;
    frm_ap = new QFrame;

    auto ap_layout = new QHBoxLayout;
    ap_layout->addWidget(sb_ap);
    ap_layout->addWidget(lbl_slash);
    ap_layout->addWidget(lbl_max_ap);
    ap_layout->setContentsMargins(0,0,0,0);
    frm_ap->setLayout(ap_layout);

    auto stars = new QHBoxLayout;
    stars->setContentsMargins(3,0,0,0);
    for (QPushButton* button : qAsConst(btn_stars)) {
        stars->addWidget(button);
    }
    auto spacer = new QSpacerItem(30,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    stars->addSpacerItem(spacer);
    box_stars->setLayout(stars);

    /* Init Skills Area */
    auto layout = new QGridLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(box_stars,0,0,1,1,Qt::AlignLeft);
    layout->addWidget(frm_ap,0,1,1,1,Qt::AlignRight);
    frm_ap_stars = new QFrame();
    frm_ap_stars->setLayout(layout);
    return frm_ap_stars;
}
void MateriaEditor::changeEvent(QEvent *e)
{
    if (e->type() != QEvent::LanguageChange)
        return;

    updateESkillList();
    box_skills->setTitle(tr("Skills"));
    box_status_effects->setTitle(tr("Added Effect"));
    box_stats->setTitle(tr("Stat Changes"));
    btn_rm_materia->setToolTip(tr("Delete"));
    btn_paste_materia->setToolTip(tr("Paste"));
    btn_copy_materia->setToolTip(tr("Copy"));
    btn_eskill_master->setText(tr("Master"));
    btn_eskill_clear->setText(tr("Clear"));
    combo_type->setItemText(0, tr("All Materia"));
    combo_type->setItemText(1, tr("Magic"));
    combo_type->setItemText(2, tr("Summon"));
    combo_type->setItemText(3, tr("Independent"));
    combo_type->setItemText(4, tr("Support"));
    combo_type->setItemText(5, tr("Command"));
    typeChanged(combo_type->currentIndex());
    setStats();
    setSkills();
}
void MateriaEditor::updateESkillList()
{
    if (eskill_list) {
        for (int i = 0; i< 24; i++) {
            eskill_list->item(i)->setText(data->enemySkill(i));
        }
    } else {
        eskill_list = new QListWidget;
        eskill_list->clear();
        //Fill Eskill List.
        for(int i=0;i<24;i++) {
            QListWidgetItem *newItem = new QListWidgetItem();
            newItem->setText(data->enemySkill(i));
            newItem->setCheckState(Qt::Unchecked);
            eskill_list->addItem(newItem);
        }
    }
}
QWidget* MateriaEditor::makeSkillWidget()
{
    updateESkillList();
    eskill_list->setStyleSheet(_itemStyle.arg(_highlightColor, QString::number(fontMetrics().height())));
    eskill_list->setMaximumHeight(eskill_list->sizeHintForRow(0)*48 +eskill_list->contentsMargins().top() + eskill_list->contentsMargins().bottom());
    eskill_list->setSelectionMode(QAbstractItemView::NoSelection);
    eskill_list->setUniformItemSizes(true);

    connect(eskill_list, &QListWidget::itemPressed, this, [](QListWidgetItem *item) {
        if (item->flags() & Qt::ItemIsUserCheckable) {
            item->setCheckState((item->checkState() ? Qt::Unchecked : Qt::Checked));
        }
    });

    connect(eskill_list, &QListWidget::clicked, this, [this] (QModelIndex index) {
        int i = index.row();
        if (eskill_list->item(i)->checkState() == Qt::Checked) {
            _current_ap |= (1<<i);
        } else {
            _current_ap &= ~(1<<i);
        }
        emit(ap_changed(_current_ap));
    });

    btn_eskill_clear = new QPushButton(tr("Clear"));
    connect(btn_eskill_clear, &QPushButton::clicked, this, [this] {
        if(_current_ap!=0) {
            setAP(0);
        }
    });

    btn_eskill_master = new QPushButton(tr("Master"));
    connect(btn_eskill_master, &QPushButton::clicked, this, [this] {
        if(_current_ap != FF7Materia::MaxMateriaAp) {
            setAP(FF7Materia::MaxMateriaAp);
        }
    });

    auto eSkillButtonLayout = new QHBoxLayout;
    eSkillButtonLayout->addWidget(btn_eskill_master);
    eSkillButtonLayout->addWidget(btn_eskill_clear);

    eskillButtons = new QWidget;
    eskillButtons->setLayout(eSkillButtonLayout);

    auto eskill_layout = new QVBoxLayout;
    eskill_layout->setContentsMargins(0,0,0,0);
    eskill_layout->setSpacing(0);
    eskill_layout->addWidget(eskill_list);
    eskill_layout->addWidget(eskillButtons);

    eskill_group = new QGroupBox;
    eskill_group->setHidden(true);
    eskill_group->setMinimumHeight(150);
    eskill_group->setLayout(eskill_layout);
    eskill_group->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    list_skills = new QListWidget;
    list_skills->addItem(new QListWidgetItem("Item"));
    list_skills->setFixedHeight(list_skills->sizeHintForRow(0)*5 +list_skills->contentsMargins().top()+ list_skills->contentsMargins().bottom()+3);
    list_skills->setSelectionMode(QAbstractItemView::NoSelection);

    auto skill_layout = new QVBoxLayout;
    skill_layout->setContentsMargins(3,0,0,0);
    skill_layout->setSpacing(2);
    skill_layout->addWidget(list_skills);
    skill_layout->addWidget(eskill_group);

    box_skills = new QGroupBox(tr("Skills"));
    box_skills->setLayout(skill_layout);

    list_status = new QListWidget;
    list_status->setFixedHeight(list_skills->height());
    list_status->setSelectionMode(QAbstractItemView::NoSelection);

    auto status_effect_layout = new QHBoxLayout;
    status_effect_layout->addWidget(list_status);
    status_effect_layout->setContentsMargins(3,0,0,0);

    box_status_effects = new QGroupBox(tr("Added Effect"));
    box_status_effects->setHidden(true);
    box_status_effects->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);
    box_status_effects->setLayout(status_effect_layout);

    auto skill_status_layout = new QHBoxLayout;
    skill_status_layout->addWidget(box_skills);
    skill_status_layout->addWidget(box_status_effects);

    frm_skill_status = new QFrame;
    frm_skill_status->setContentsMargins(0,0,0,0);
    frm_skill_status->setLayout(skill_status_layout);
    frm_skill_status->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    return frm_skill_status;
}

QWidget* MateriaEditor::makeStatWidget()
{
    lbl_stats = new QLabel;
    auto stat_layout = new QHBoxLayout;
    stat_layout->setContentsMargins(3,0,0,0);
    stat_layout->addWidget(lbl_stats);

    box_stats = new QGroupBox(tr("Stat Changes"));
    box_stats->setHidden(true);
    box_stats->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    box_stats->setLayout(stat_layout);

    return box_stats;
}
