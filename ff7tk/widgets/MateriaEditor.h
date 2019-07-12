/****************************************************************************/
//    copyright 2012 - 2016 Chris Rizzitello <sithlord48@gmail.com>         //
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

#include <QtWidgets>
/* SET FF7Materia PATH ACCORDINGLY*/
#include "../data/FF7Materia.h"

class MateriaEditor : public QWidget
{
    Q_OBJECT
public:
    MateriaEditor(QWidget *parent = 0);
    MateriaEditor(quint8 materia_id = 0, qint32 ap = 0, QWidget *parent = 0);
    void setMateria(quint8 materia_id = 0, qint32 materia_ap = 0);
    void setAP(qint32 current_ap = 0);
    void setStarsSize(int);
    qint32 ap(void);
    qint32 MaxAP(void);
    qint8 id(void);
    bool isEditable(void);
    void setEditable(bool);
//    qint32 raw_data(void);
protected:
    void changeEvent(QEvent *e);
public slots:
    void setEditableMateriaCombo(bool enabled);
private:
    //Private Functions
    void init_display(void);
    QHBoxLayout *makeNameLayout();
    QWidget *makeStarWidget();
    QWidget *makeSkillWidget();
    QWidget *makeStatWidget();
    void setStars(void);
    void setName(void);
    void setStats(void);
    void setSkills(void);
    void setLevel(void);
    void updateESkillList();
    //Private Gui Parts.
    QLabel *lbl_max_ap = nullptr;
    QHBoxLayout *Final = nullptr;
    QComboBox *combo_type = nullptr;
    QComboBox *combo_materia = nullptr;
    QPushButton *btn_paste_materia = nullptr;
    QPushButton *btn_rm_materia = nullptr;
    QPushButton *btn_copy_materia = nullptr;
    QPushButton *btn_eskill_master = nullptr;
    QPushButton *btn_eskill_clear = nullptr;
    QSpinBox *sb_ap = nullptr;
    QFrame *frm_ap = nullptr;
    QFrame *frm_skill_status = nullptr;
    QList<QPushButton *> btn_stars = {nullptr, nullptr, nullptr, nullptr, nullptr};
    QFrame *box_stars = nullptr;
    QGroupBox *box_skills = nullptr;
    QGroupBox *eskill_group = nullptr;
    QListWidget *eskill_list = nullptr;
    QWidget *eskillButtons = nullptr;
    QListWidget *list_skills = nullptr;
    QGroupBox *box_stats = nullptr;
    QGroupBox *box_status_effects = nullptr;
    QLabel *lbl_stats = nullptr;
    QListWidget *list_status = nullptr;
    FF7Materia *data = nullptr;
    QSpacerItem *v_spacer = nullptr;
    QFrame *frm_ap_stars = nullptr;
    QLabel *lbl_materiaIcon = nullptr;
    QLabel *lbl_materiaName = nullptr;
    //Private Data Members
    quint8 _id;// current id
    quint8 buffer_id;
    qint32 buffer_ap;
    qint8 _level;//current level
    qint32 _current_ap;// current ap amount
    QString _highlightColor;
    QSize _iconSize;
    bool _editable;
    inline static const auto _buttonStyle = QStringLiteral("QPushButton:enabled{background-color: rgba(0,0,0,0);border:0px solid;} QPushButton:hover{background-color:rgba(%1);}");
    inline static const auto _itemStyle = QStringLiteral("QListWidget::item { padding-left: 0px; padding-top: 1px; padding-bottom: 1px;} QListView::item:hover { background-color: rgba(%1); } QListView::item:focus { background-color: rgba(%1); } QListView::indicator { width: %2px; height: %2px; } QListView::indicator:unchecked {image: url(:/materia/command_star_empty);} QListView::indicator:checked{image: url(:/materia/command_star_full);}");
private slots:
    void typeChanged(int new_type);
    void materia_changed(QString new_name);
    void editMode(void);
    QPushButton *newStyledButton(const QIcon &icon = QIcon(), QKeySequence shortcut = QKeySequence(), const QString &toolip = QString(), QWidget *parent = nullptr);
signals:
    void apChanged(qint32);
    void idChanged(qint8);
};
#endif //MateriaEditor
