/****************************************************************************/
//    copyright 2012 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//   FF7tk is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#ifndef CHAREDITOR_H
#define CHAREDITOR_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets>
#else
#include <QtGui>
#endif

//set path to FF7Item FF7Materia and FF7Char
#include "../data/FF7Item.h"
#include "../data/FF7Materia.h"
#include "../data/FF7Char.h"
#include "../data/Type_FF7CHAR.h"
#include "MateriaEditor.h"

/** \class CharEditor
 *  \brief Widget to allow editing of a character using FF7Char for data.
 */
class CharEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CharEditor(qreal Scale = 1, QWidget *parent = 0);
    void setChar(FF7CHAR Chardata, QString Processed_Name = "");
    bool AutoLevel();
    bool AutoStatCalc();
    bool Editable();
    bool AdvancedMode();
    void setSliderStyle(QString style);
    void MaxStats();
    void MaxEquip();
    quint8 id();
    quint8 level();
    quint8 str();
    quint8 vit();
    quint8 mag();
    quint8 spi();
    quint8 dex();
    quint8 lck();
    quint8 strBonus();
    quint8 vitBonus();
    quint8 magBonus();
    quint8 spiBonus();
    quint8 dexBonus();
    quint8 lckBonus();
    qint8 limitLevel();
    quint8 limitBar();
    QString name();
    quint8 weapon();
    quint8 armor();
    quint8 accessory();
    quint16 curHp();
    quint16 maxHp();
    quint16 curMp();
    quint16 maxMp();
    quint16 kills();
    quint8 row();
    quint8 levelProgress();
    quint8 sadnessfury();
    quint16 limits();
    quint16 timesused1();
    quint16 timesused2();
    quint16 timesused3();
    quint16 baseHp();
    quint16 baseMp();
    quint32 exp();
    quint32 expNext();
    materia char_materia(int mat);

protected:
    void changeEvent(QEvent *e);

signals:
    void id_changed(qint8);
    void level_changed(qint8);
    void str_changed(quint8);
    void vit_changed(quint8);
    void mag_changed(quint8);
    void spi_changed(quint8);
    void dex_changed(quint8);
    void lck_changed(quint8);
    void strBonus_changed(quint8);
    void vitBonus_changed(quint8);
    void magBonus_changed(quint8);
    void spiBonus_changed(quint8);
    void dexBonus_changed(quint8);
    void lckBonus_changed(quint8);
    void limitLevel_changed(qint8);
    void limitBar_changed(quint8);
    void name_changed(QString);
    void weapon_changed(quint8);
    void armor_changed(quint8);
    void accessory_changed(quint8);
    void curHp_changed(quint16);
    void maxHp_changed(quint16);
    void curMp_changed(quint16);
    void maxMp_changed(quint16);
    void kills_changed(quint16);
    void row_changed(quint8);
    void levelProgress_changed(quint8);
    void sadnessfury_changed(quint8);
    void limits_changed(quint16);
    void timesused1_changed(quint16);
    void timesused2_changed(quint16);
    void timesused3_changed(quint16);
    void baseHp_changed(quint16);
    void baseMp_changed(quint16);
    void exp_changed(quint32);
    void mslotChanged(int);
    void Materias_changed(materia);
    void expNext_changed(quint32);

public slots:
    void setAutoLevel(bool);
    void setAutoStatCalc(bool);
    void setEditable(bool);
    void setAdvancedMode(bool);
    void setToolBoxStyle(QString);
    void setEditableComboBoxes(bool);

private slots:
    void setId(int);
    void setLevel(int);
    void setStr(int);
    void setVit(int);
    void setMag(int);
    void setSpi(int);
    void setDex(int);
    void setLck(int);
    void setStrBonus(int);
    void setVitBonus(int);
    void setMagBonus(int);
    void setSpiBonus(int);
    void setDexBonus(int);
    void setLckBonus(int);
    void setLimitLevel(int);
    void setLimitBar(int);
    void setName(QString);
    void setWeapon(int);
    void setArmor(int);
    void setAccessory(int);
    void setRow(bool front_row);
    void setLevelProgress(int);
    void setSadnessFury(int);
    void setLimits(int);
    void setTimesused1(int);
    void setTimesused2(int);
    void setTimesused3(int);
    void setBaseHp(int);
    void setBaseMp(int);
    void setExp(int);
    void setExpNext(int);
    void setCurMp(int);
    void setCurHp(int);
    void setMaxMp(int);
    void setMaxHp(int);
    void setKills(int);
    void cb_fury_toggled(bool);
    void cb_sadness_toggled(bool);
    void cb_idChanger_toggled(bool);
    void calc_limit_value(QModelIndex);
    void Level_Changed(int);// used for tracking growth of char
    void Exp_Changed(int);// used for tracking growth of char
    void weapon_slot_1_clicked();
    void weapon_slot_2_clicked();
    void weapon_slot_3_clicked();
    void weapon_slot_4_clicked();
    void weapon_slot_5_clicked();
    void weapon_slot_6_clicked();
    void weapon_slot_7_clicked();
    void weapon_slot_8_clicked();
    void armor_slot_1_clicked();
    void armor_slot_2_clicked();
    void armor_slot_3_clicked();
    void armor_slot_4_clicked();
    void armor_slot_5_clicked();
    void armor_slot_6_clicked();
    void armor_slot_7_clicked();
    void armor_slot_8_clicked();
    void matAp_changed(qint32);
    void matId_changed(qint8);
private:
    void mButtonPress(int Mslot);
    void init_display(void);
    void init_connections(void);
    void disconnectAll(void);
    void calc_stats(void);//calc stat changes if autostatcalc == true;
    void level_up(int);
    void update_tnl_bar();
    void elemental_info();
    void status_info();
    void update_materia_slots();
    void setSlotFrame(void);
    void updateText();
//Data
    bool load;
    FF7Char Chars;
    FF7Item Items;
    FF7Materia Materias;
    FF7CHAR data;
    QString _name;
    bool autolevel;
    bool autostatcalc;
    bool editable;
    bool advancedMode;
    int mslotsel;//select materia slot
    qint32 ap;
    qreal scale;
//GUI PARTS
    QLabel *lbl_avatar = nullptr;
    QLineEdit *line_name = nullptr;
    QSpinBox *sb_level = nullptr;
    QSpinBox *sb_curMp = nullptr;
    QSpinBox *sb_maxMp = nullptr;
    QSpinBox *sb_curHp = nullptr;
    QSpinBox *sb_maxHp = nullptr;
    QSpinBox *sb_kills = nullptr;
    QLabel *lbl_hp = nullptr;
    QLabel *lbl_hp_slash = nullptr;
    QLabel *lbl_hp_max = nullptr;
    QLabel *lbl_mp = nullptr;
    QLabel *lbl_mp_slash = nullptr;
    QLabel *lbl_mp_max = nullptr;
    QCheckBox *cb_fury = nullptr;
    QCheckBox *cb_sadness = nullptr;
    QCheckBox *cb_front_row = nullptr;
    QComboBox *combo_id = nullptr;

    QSpinBox *sb_total_exp = nullptr;
    QLabel *lbl_level_progress = nullptr;
    QLabel *lbl_level_next = nullptr;
    QProgressBar *bar_tnl = nullptr;
    QLabel *lbl_limit_bar = nullptr;
    QSlider *slider_limit = nullptr;
    QLCDNumber *lcd_limit_value = nullptr;

    QLabel *lbl_str = nullptr;
    QSpinBox *sb_str = nullptr;
    QSpinBox *sb_str_bonus = nullptr;
    QLabel *lbl_str_mat_bonus = nullptr;
    QLabel *lbl_str_total = nullptr;

    QLabel *lbl_vit = nullptr;
    QSpinBox *sb_vit = nullptr;
    QSpinBox *sb_vit_bonus = nullptr;
    QLabel *lbl_vit_mat_bonus = nullptr;
    QLabel *lbl_vit_total = nullptr;

    QLabel *lbl_mag = nullptr;
    QSpinBox *sb_mag = nullptr;
    QSpinBox *sb_mag_bonus = nullptr;
    QLabel *lbl_mag_mat_bonus = nullptr;
    QLabel *lbl_mag_total = nullptr;

    QLabel *lbl_spi = nullptr;
    QSpinBox *sb_spi = nullptr;
    QSpinBox *sb_spi_bonus = nullptr;
    QLabel *lbl_spi_mat_bonus = nullptr;
    QLabel *lbl_spi_total = nullptr;

    QLabel *lbl_dex = nullptr;
    QSpinBox *sb_dex = nullptr;
    QSpinBox *sb_dex_bonus = nullptr;
    QLabel *lbl_dex_mat_bonus = nullptr;
    QLabel *lbl_dex_total = nullptr;

    QLabel *lbl_lck = nullptr;
    QSpinBox *sb_lck = nullptr;
    QSpinBox *sb_lck_bonus = nullptr;
    QLabel *lbl_lck_mat_bonus = nullptr;
    QLabel *lbl_lck_total = nullptr;

    QLabel *lbl_base_hp = nullptr;
    QSpinBox *sb_base_hp = nullptr;
    QLabel *lbl_base_hp_bonus = nullptr;

    QLabel *lbl_base_mp = nullptr;
    QSpinBox *sb_base_mp = nullptr;
    QLabel *lbl_base_mp_bonus = nullptr;

    QLabel *lbl_limit_level = nullptr;
    QSpinBox *sb_limit_level = nullptr;
    QSpinBox *sb_uses_limit_1_1 = nullptr;
    QSpinBox *sb_uses_limit_2_1 = nullptr;
    QSpinBox *sb_uses_limit_3_1 = nullptr;
    QListWidget *list_limits = nullptr;
    QLabel *lbl_uses = nullptr;
    QLabel *lbl_1_1 = nullptr;
    QLabel *lbl_2_1 = nullptr;
    QLabel *lbl_3_1 = nullptr;
    QLabel *lbl_0x34 = nullptr;
    QLabel *lbl_0x35 = nullptr;
    QLabel *lbl_0x36 = nullptr;
    QLabel *lbl_0x37 = nullptr;
    QLabel *lblWeaponStats = nullptr;
    QLabel *lblArmorStats = nullptr;
    QComboBox *weapon_selection = nullptr;
    QComboBox *armor_selection = nullptr;
    QComboBox *accessory_selection = nullptr;
    MateriaEditor *materia_edit = nullptr;
    QGroupBox *elemental_box = nullptr;
    QGroupBox *status_box = nullptr;
    QListWidget *elemental_effects = nullptr;
    QListWidget *status_effects = nullptr;
    QFrame *weapon_materia_box = nullptr;
    QFrame *armor_materia_box = nullptr;
    QGroupBox *weapon_box = nullptr;
    QGroupBox *armor_box = nullptr;
    QGroupBox *accessory_box = nullptr;
    QFrame *weapon_frm_1 = nullptr;
    QFrame *weapon_frm_2 = nullptr;
    QFrame *weapon_frm_3 = nullptr;
    QFrame *weapon_frm_4 = nullptr;
    QFrame *weapon_frm_5 = nullptr;
    QFrame *weapon_frm_6 = nullptr;
    QFrame *weapon_frm_7 = nullptr;
    QFrame *weapon_frm_8 = nullptr;
    QPushButton *weapon_slot_1 = nullptr;
    QPushButton *weapon_slot_2 = nullptr;
    QPushButton *weapon_slot_3 = nullptr;
    QPushButton *weapon_slot_4 = nullptr;
    QPushButton *weapon_slot_5 = nullptr;
    QPushButton *weapon_slot_6 = nullptr;
    QPushButton *weapon_slot_7 = nullptr;
    QPushButton *weapon_slot_8 = nullptr;
    QFrame *armor_frm_1 = nullptr;
    QFrame *armor_frm_2 = nullptr;
    QFrame *armor_frm_3 = nullptr;
    QFrame *armor_frm_4 = nullptr;
    QFrame *armor_frm_5 = nullptr;
    QFrame *armor_frm_6 = nullptr;
    QFrame *armor_frm_7 = nullptr;
    QFrame *armor_frm_8 = nullptr;
    QPushButton *armor_slot_1 = nullptr;
    QPushButton *armor_slot_2 = nullptr;
    QPushButton *armor_slot_3 = nullptr;
    QPushButton *armor_slot_4 = nullptr;
    QPushButton *armor_slot_5 = nullptr;
    QPushButton *armor_slot_6 = nullptr;
    QPushButton *armor_slot_7 = nullptr;
    QPushButton *armor_slot_8 = nullptr;
    QLabel *weapon_m_link_1 = nullptr;
    QLabel *weapon_m_link_2 = nullptr;
    QLabel *weapon_m_link_3 = nullptr;
    QLabel *weapon_m_link_4 = nullptr;
    QLabel *armor_m_link_1 = nullptr;
    QLabel *armor_m_link_2 = nullptr;
    QLabel *armor_m_link_3 = nullptr;
    QLabel *armor_m_link_4 = nullptr;
    QToolBox *toolbox = nullptr;
    QFrame *unknown_box = nullptr;
    QLCDNumber *lcd_0x34 = nullptr;
    QLCDNumber *lcd_0x35 = nullptr;
    QLCDNumber *lcd_0x36 = nullptr;
    QLCDNumber *lcd_0x37 = nullptr;
    QCheckBox *cb_idChanger = nullptr;
};

#endif // CHAREDITOR_H
