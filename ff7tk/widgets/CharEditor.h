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
//   FF7tk is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#ifndef CHAREDITOR_H
#define CHAREDITOR_H


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
    explicit CharEditor(qreal Scale = 1, QWidget *parent = nullptr);
    void setChar(const FF7CHAR &Chardata, const QString &Processed_Name = "");
    bool AutoLevel();
    bool AutoStatCalc();
    bool Editable();
    bool AdvancedMode();
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
    void changeEvent(QEvent *e) override;

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
    void setToolBoxStyle(const QString &styleSheet);
    void setSliderStyle(const QString &style);
    void setEditableComboBoxes(bool);

private:
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
    void setName(const QString &name);
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
    void materiaSlotClicked(int slotClicked);
    void matAp_changed(qint32);
    void matId_changed(qint8);
    void init_display();
    void init_connections();
    void disconnectAll();
    void calc_stats();//calc stat changes if autostatcalc == true;
    void level_up(int);
    void update_tnl_bar();
    void elemental_info();
    void status_info();
    void update_materia_slots();
    void updateMateriaToolTips();
    void setSlotFrame();
    /**
     * @brief Creates all items that have text or tooltips, Future calls updates the text on these widgets.
     *  This is called once durring the constructor and again for languageChangeEvents to retranslate the text.
     */
    void updateText();

    /**
     * @brief Create a Widget containing all the Items to calculate a stat
     * @param statBaseSpinBox: QSpinBox* for the Base Stat.
     * @param statSourceSpinBox: QSpinBox* for the Source Use for Stat, a nullptr will remove this from the layout.
     * @param statLabel: Label containing the name of the stat
     * @param statMateriaBonusLabel: Label containing bonuses to the stat given by equipment and / or materia
     * @param statTotalLabel: Label containing the total value of the stat
     * @return Constructed Widget that contains all Items used to calculate a stat.
     */
    QWidget* makeStatWidget(QSpinBox* statBaseSpinBox = nullptr, QSpinBox* statSourceSpinBox = nullptr
            , QLabel* statLabel = nullptr, QLabel* statMateriaBonusLabel = nullptr, QLabel* statTotalLabel = nullptr);

    /**
     * @brief Create the a widget containing all the various stats Calls makeStatWidget once for each stat.
     * @return Widget containing all the controls for all the stats
     */
    QFrame* makeStatFrame();

    /**
     * @brief Create a pair of materia slots.
     * @param button1: First Materia Slot
     * @param button2: Second Materia Slot
     * @param frame1: Frame that will contain button1
     * @param frame2: Frame that will contain button2
     * @param linkLabel: Label Where the link will be shown if materia slots are linked
     * @return: One set of materia slots.
     */
    QHBoxLayout * makeMateriaSlotPair(QPushButton* button1 = nullptr, QPushButton* button2 = nullptr, QFrame *frame1 = nullptr, QFrame *frame2 = nullptr, QLabel* linkLabel = nullptr);

    /**
     * @brief Creates the layout for the limit related controls.
     * @return Layout containing the controls for the limit items.
     */
    QVBoxLayout * makeLimitLayout();
//Data
    bool load{false};
    bool autolevel{true};
    bool autostatcalc{true};
    bool editable{true};
    bool advancedMode{false};
    int mslotsel{-1};
    qint32 ap{0};
    FF7Char Chars;
    FF7Item Items;
    FF7Materia Materias;
    FF7CHAR data;
    QString _name;
    qreal scale;
//GUI PARTS
    QLabel *lblAvatar = nullptr;
    QLineEdit *lineName = nullptr;
    QSpinBox *sbLevel = nullptr;
    QSpinBox *sbCurrentMp = nullptr;
    QSpinBox *sbCurrentHp = nullptr;

    QLabel *lblBaseHp = nullptr;
    QSpinBox *sbBaseHp = nullptr;
    QLabel *lblBaseHpBonus = nullptr;

    QLabel *lblBaseMp = nullptr;
    QSpinBox *sbBaseMp = nullptr;
    QLabel *lblBaseMpBonus = nullptr;

    QSpinBox *sbKills = nullptr;
    QLabel *lblCurrentHp = nullptr;
    QLabel *lblMaxHp = nullptr;
    QLabel *lblCurrentMp = nullptr;
    QLabel *lblMaxMp = nullptr;
    QCheckBox *cbFury = nullptr;
    QCheckBox *cbSadness = nullptr;
    QCheckBox *cbFrontRow = nullptr;
    QComboBox *comboId = nullptr;

    QSpinBox *sbTotalExp = nullptr;
    QLabel *lbl_level_next = nullptr;
    QProgressBar *bar_tnl = nullptr;
    QLabel *lbl_limit_bar = nullptr;
    QSlider *slider_limit = nullptr;
    QLCDNumber *lcdLimitValue = nullptr;

    QLabel *lblStr = nullptr;
    QSpinBox *sbStr = nullptr;
    QSpinBox *sbStrSourceUse = nullptr;
    QLabel *lblStrMateriaBonus = nullptr;
    QLabel *lblStrTotal = nullptr;

    QLabel *lblVit = nullptr;
    QSpinBox *sbVit = nullptr;
    QSpinBox *sbVitSourceUse = nullptr;
    QLabel *lblVitMateriaBonus = nullptr;
    QLabel *lblVitTotal = nullptr;

    QLabel *lblMag = nullptr;
    QSpinBox *sbMag = nullptr;
    QSpinBox *sbMagSourceUse = nullptr;
    QLabel *lblMagMateriaBonus = nullptr;
    QLabel *lblMagTotal = nullptr;

    QLabel *lblSpi = nullptr;
    QSpinBox *sbSpi = nullptr;
    QSpinBox *sbSpiSourceUse = nullptr;
    QLabel *lblSpiMateriaBonus = nullptr;
    QLabel *lblSpiTotal = nullptr;

    QLabel *lblDex = nullptr;
    QSpinBox *sbDex = nullptr;
    QSpinBox *sbDexSourceUse = nullptr;
    QLabel *lblDexMateriaBonus = nullptr;
    QLabel *lblDexTotal = nullptr;

    QLabel *lblLck = nullptr;
    QSpinBox *sbLck = nullptr;
    QSpinBox *sbLckSourceUse = nullptr;
    QLabel *lblLckMateriaBonus = nullptr;
    QLabel *lblLckTotal = nullptr;

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
    QList<QFrame *> materiaSlotFrames;
    QList<QPushButton *> materiaSlots;
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
    //Static Limits
    inline static const int quint8Max = 255;
    inline static const int qint16Max = 32767;
    inline static const int quint16Max = 65535;

};

#endif // CHAREDITOR_H
