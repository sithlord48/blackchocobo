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
#ifndef MateriaEditor_H
  #define MateriaEditor_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif

/* SET FF7Materia PATH ACCORDINGLY*/
#include "../data/FF7Materia.h"

class MateriaEditor : public QWidget
{
    Q_OBJECT
public:
	MateriaEditor(qreal Scale=1,QWidget *parent=0);
	MateriaEditor(quint8 materia_id=0,qint32 ap=0,qreal Scale=1,QWidget *parent=0);
    void setMateria(quint8 materia_id=0,qint32 materia_ap=0);
    void setAP (qint32 current_ap=0);
    void setStarsSize(int);
    qint32 ap(void);
    qint32 MaxAP(void);
    qint8 id(void);
    bool isEditable(void);
    void setEditable(bool);
    void setHoverStyle(QString hoverColor);
//    qint32 raw_data(void);
public slots:
    void setEditableMateriaCombo(bool enabled);
private:
    //Private Functions
    void init_display(void);
    void init_normal_mode(void);
    void init_compact_mode(void);
    void init_data(void);
    void init_connections(void);
    void setStars(void);
    void setName(void);
    void setStats(void);
    void setSkills(void);
    void setLevel(void);
    //Private Gui Parts.
	QLabel * lbl_max_ap;
    QLabel * lbl_slash;
    QHBoxLayout *Final;
    QComboBox *combo_type;
    QComboBox *combo_materia;
    QPushButton *btn_rm_materia;
    QPushButton *btn_copy_materia;
    QPushButton *btn_paste_materia;
    QSpinBox * sb_ap;
    QFrame *frm_name_type;
    QFrame *frm_ap;
    QFrame *frm_skill_status;
    QPushButton *btn_star1;
    QPushButton *btn_star2;
    QPushButton *btn_star3;
    QPushButton *btn_star4;
    QPushButton *btn_star5;
    QFrame *box_stars;
    QGroupBox *box_skills;
    QGroupBox * eskill_group;
    QListWidget * eskill_list;
    QPushButton * btn_clear_eskills;
    QPushButton * btn_master_eskills;
    QListWidget *list_skills;
    QGroupBox *box_stats;
    QGroupBox *box_status_effects;
    QLabel *lbl_stats;
    QListWidget *list_status;
    FF7Materia *data;
    QSpacerItem *v_spacer;
    QFrame * frm_ap_stars;
    QGridLayout *ap_stars_layout;
    //Private Data Members
    quint8 _id;// current id
    qint8 buffer_id;
    qint32 buffer_ap;
    qint8 _level;//current level
    qint32 _current_ap;// current ap amount
    QLabel *lbl_materiaIcon;
    QLabel *lbl_materiaName;
    bool editable;
	qreal scale;
private slots:
    void btn_star1_clicked();
    void btn_star2_clicked();
    void btn_star3_clicked();
    void btn_star4_clicked();
    void btn_star5_clicked();
    void type_changed(int new_type);
    void materia_changed(QString new_name);
    void remove_materia(void);
    void copy_materia(void);
    void paste_materia(void);
    void sb_ap_changed(int);
    void eskill_list_clicked(QModelIndex);
    void btn_master_eskill_clicked();
    void btn_clear_eskill_clicked();
    void editMode(void);
signals:
    void ap_changed(qint32);
    void id_changed(qint8);

};
#endif //MateriaEditor
