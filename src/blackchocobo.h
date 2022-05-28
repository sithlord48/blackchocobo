/****************************************************************************/
//    copyright 2010-2020 Chris Rizzitello <sithlord48@gmail.com>           //
//                                                                          //
//    This file is part of Black Chocobo.                                   //
//                                                                          //
//    Black Chocobo is free software: you can redistribute it and/or modify //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    Black Chocobo is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#pragma once
#include <QMainWindow>
#include <QMap>

#include <Type_materia.h>

class FF7Save;
class FF7ItemModel;
class SaveIcon;
class PartyTab;
class PhsListWidget;
class MenuListWidget;
class OptionsWidget;
class MateriaEditor;
class QSpacerItem;
class ItemListView;
class QHexEdit;
class ChocoboManager;
class LocationViewer;
class QTableWidgetItem;
class QTranslator;

namespace Ui
{
class BlackChocobo;
}

class BlackChocobo : public QMainWindow
{
    Q_OBJECT
public:
    explicit BlackChocobo(QWidget *parent = nullptr);
    QString checkIconTheme();
    ~BlackChocobo();

    void setRegion(QString region);
protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);
    void resizeEvent(QResizeEvent *);
    void moveEvent(QMoveEvent *);
private:
    Ui::BlackChocobo *ui;
//  qreal scale;
    qint64 hexCursorPos;
    bool skip_slot_mask;
    bool _init; //set true then false after a file load.
    bool load; // are we loading data? if so don't save it to the file.
    //bool showLocPreview;
    FF7Save *ff7 = nullptr; // our save file struct pointer.
    SaveIcon *saveIcon = nullptr;
    int s; //track slot
    materia buffer_materia; // buffer for a materia
    //ITEM buffer_item; // for use later
    int curchar; //keeps track of current character displayed
    int mslotsel; //keeps track of materia slot on char selected
    PhsListWidget *phsList = nullptr;
    MenuListWidget *menuList = nullptr;
    OptionsWidget *optionsWidget = nullptr;
    MateriaEditor *materia_editor = nullptr;
    QSpacerItem *mat_spacer = nullptr;
    PartyTab *partyTab = nullptr;
    ItemListView *itemListView = nullptr;
    QHexEdit *hexEditor = nullptr;
    ChocoboManager *chocoboManager = nullptr;
    LocationViewer *locationViewer = nullptr;
    QString prevFile;
    QMap<QString, QList<QTranslator *>> m_translations;
    typedef QList<quint16> fieldItemOffsetList;
    typedef QList<quint8> fieldItemBitList;

    FF7ItemModel *ff7ItemModel = nullptr;
    QList<fieldItemOffsetList> *fieldItemOffset;
    QList<fieldItemBitList> *fieldItemBit;
    void populateCombos();
    void initDisplay();
    void setItemSizes();
    void init_style();
    void init_connections();
    void loadBasicSettings();
    void loadChildWidgetSettings();
    void detectTranslations();
public slots:
    void loadFileFull(const QString &fileName, int reload); //(Vegeta_Ss4) v0.8.3

private slots://try to keep these in the same order as the .cpp file
    /*Loading and Saving related Functions*/
    /**
     * @brief Creates a dialog to ask user if they wish to save the file, saves if user chooses Yes.
     * @return true to accept and false to ignore.
     */
    bool saveChanges(void);
    /**
     * @brief save thefile.
     * @param fileName: path of the file to save.
     * @return true if successful.
     */
    bool saveFileFull(const QString &fileName);
    void setControllerMappingVisible(bool);
    void Items_Changed(QList<quint16>);
    /*Simple Menu Actions */
    void actionOpenSaveFile_triggered();
    void actionReload_triggered();
    void actionImportChar_triggered();
    void actionExportChar_triggered();
    bool actionSave_triggered();
    bool actionSaveFileAs_triggered();
    void actionNewGame_triggered();
    void actionNewGamePlus_triggered();
    void actionShowSelectionDialog_triggered();
    void actionClearSlot_triggered();
    void actionPreviousSlot_triggered();
    void actionNextSlot_triggered();
    void actionAbout_triggered();
    void actionCopySlot_triggered();
    void actionPasteSlot_triggered();
    void actionShowOptions_triggered();
    void actionOpenAchievementFile_triggered();
    void actionCreateNewMetadata_triggered();
    void actionImportSlotFromFile_triggered();
    /*Language and Region Data*/
    void actionRegionUSA_triggered(bool checked);
    void actionRegionPALGeneric_triggered(bool checked);
    void actionRegionPALFrench_triggered(bool checked);
    void actionRegionPALGerman_triggered(bool checked);
    void actionRegionPALSpanish_triggered(bool checked);
    void actionRegionJPN_triggered(bool checked);
    void actionRegionJPNInternational_triggered(bool checked);
    void changeLanguage(const QVariant &data);
    void setOpenFileText(const QString &text);

    /*GuiFunctions*/
    void setmenu(bool newgame);
    void materiaupdate(void);
    void guirefresh(bool newgame);
    void progress_update(void);
    void unknown_refresh(int);
    void set_ntsc_time(void);
    void set_pal_time(void);
    void CheckGame(void);
    void othersUpdate();
    void tabWidget_currentChanged(int index);
    void locationToolBox_currentChanged(int index);
    void testDataTabWidget_currentChanged(int index);
    void fileModified(bool changed);
    void updateStolenMateria();

    /*HexEditor Tab */
    void hexTabUpdate(int viewMode);
    void comboHexEditor_currentIndexChanged(int index);
    void comboSlotRegionChanged(int index);
    void hexEditorChanged(void);
    void update_hexEditor_PSXInfo(void);
    //QString avatar_style(int);

    /*CharButtons*/
    void charButtonClicked(int charSlot = 0);
    void partyMembersChanged(int partySlot, int id = 0xFF);
    /*PARTY TAB*/
    void sbGil_valueChanged(double);
    void sbGp_valueChanged(int);
    void sbBattles_valueChanged(int);
    void sbRuns_valueChanged(int);
    /*Chocobo Tab*/
    /* ChocoboManager*/
    void cm_stablesOwnedChanged(qint8);
    void cm_stablesOccupiedChanged(qint8);
    void cm_stableMaskChanged(qint8);
    void cm_nameChanged(int, QString);
    void cm_staminaChanged(int, quint16);
    void cm_speedChanged(int, quint16);
    void cm_maxspeedChanged(int, quint16);
    void cm_sprintChanged(int, quint16);
    void cm_maxsprintChanged(int, quint16);
    void cm_sexChanged(int, quint8);
    void cm_typeChanged(int, quint8);
    void cm_coopChanged(int, quint8);
    void cm_accelChanged(int, quint8);
    void cm_intelChanged(int, quint8);
    void cm_raceswonChanged(int, quint8);
    void cm_pcountChanged(int, quint8);
    void cm_personalityChanged(int, quint8);
    void cm_mated_toggled(int, bool);
    void cm_pensChanged(int pen, int index);
    void cm_ratingChanged(int, quint8);

    //The Chocobo pens.

    /* Others Tab */
    void sbCurdisc_valueChanged(int);
    void sbLoveYuffie_valueChanged(int);
    void sbLoveTifa_valueChanged(int);
    void sbLoveAeris_valueChanged(int);
    void sbLoveBarret_valueChanged(int);
    void sbTimeSec_valueChanged(int);
    void sbTimeMin_valueChanged(int);
    void sbTimeHour_valueChanged(int);

//NOT IN ORDER FROM HERE DOWN
    void char_id_changed(qint8);
    void char_level_changed(qint8);
    void char_str_changed(quint8);
    void char_vit_changed(quint8);
    void char_mag_changed(quint8);
    void char_spi_changed(quint8);
    void char_dex_changed(quint8);
    void char_lck_changed(quint8);
    void char_strBonus_changed(quint8);
    void char_vitBonus_changed(quint8);
    void char_magBonus_changed(quint8);
    void char_spiBonus_changed(quint8);
    void char_dexBonus_changed(quint8);
    void char_lckBonus_changed(quint8);
    void char_limitLevel_changed(qint8);
    void char_limitBar_changed(quint8);
    void char_name_changed(QString);
    void char_weapon_changed(quint8);
    void char_armor_changed(quint8);
    void char_accessory_changed(quint8);
    void char_curHp_changed(quint16);
    void char_maxHp_changed(quint16);
    void char_curMp_changed(quint16);
    void char_maxMp_changed(quint16);
    void char_kills_changed(quint16);
    void char_row_changed(quint8);
    void char_levelProgress_changed(quint8);
    void char_sadnessfury_changed(quint8);
    void char_limits_changed(quint16);
    void char_timesused1_changed(quint16);
    void char_timeused2_changed(quint16);
    void char_timeused3_changed(quint16);
    void char_baseHp_changed(quint16);
    void char_baseMp_changed(quint16);
    void char_exp_changed(quint32);
    void char_mslot_changed(int);
    void char_materia_changed(materia);
    void char_expNext_changed(quint32);

    void sbTimerTimeHour_valueChanged(int);
    void sbTimerTimeMin_valueChanged(int);
    void sbTimerTimeSec_valueChanged(int);
    void cbTutWorldSave_stateChanged(int);
    void cbBombingInt_stateChanged(int);
    void cbTutSub_toggled(bool checked);

    void cbMidgartrain_8_toggled(bool);
    void cbMidgartrain_7_toggled(bool);
    void cbMidgartrain_6_toggled(bool);
    void cbMidgartrain_5_toggled(bool);
    void cbMidgartrain_4_toggled(bool);
    void cbMidgartrain_3_toggled(bool);
    void cbMidgartrain_2_toggled(bool);
    void cbMidgartrain_1_toggled(bool);

    void cbYuffieForest_toggled(bool);
    void cbRegYuffie_toggled(bool);
    void cbRegVinny_toggled(bool);

    void sbUweaponHp_valueChanged(int);
    void sbCoster1_valueChanged(int);
    void sbCoster2_valueChanged(int);
    void sbCoster3_valueChanged(int);
    void sbBloveBarret_valueChanged(int);
    void sbBloveYuffie_valueChanged(int);
    void sbBloveTifa_valueChanged(int);
    void sbBloveAeris_valueChanged(int);

    void sbTurkschurch_valueChanged(int);

    void btnRemoveAllMateria_clicked();
    void btnRemoveAllStolen_clicked();

    //progress functions

    void comboReplay_currentIndexChanged(int index);
    void sbMprogress_valueChanged(int value);
    void cbBm1_1_toggled(bool checked);
    void cbBm1_2_toggled(bool checked);
    void cbBm1_3_toggled(bool checked);
    void cbBm1_4_toggled(bool checked);
    void cbBm1_5_toggled(bool checked);
    void cbBm1_6_toggled(bool checked);
    void cbBm1_7_toggled(bool checked);
    void cbBm1_8_toggled(bool checked);

    void cbBm2_1_toggled(bool checked);
    void cbBm2_2_toggled(bool checked);
    void cbBm2_3_toggled(bool checked);
    void cbBm2_4_toggled(bool checked);
    void cbBm2_5_toggled(bool checked);
    void cbBm2_6_toggled(bool checked);
    void cbBm2_7_toggled(bool checked);
    void cbBm2_8_toggled(bool checked);

    void cbBm3_1_toggled(bool checked);
    void cbBm3_2_toggled(bool checked);
    void cbBm3_3_toggled(bool checked);
    void cbBm3_4_toggled(bool checked);
    void cbBm3_5_toggled(bool checked);
    void cbBm3_6_toggled(bool checked);
    void cbBm3_7_toggled(bool checked);
    void cbBm3_8_toggled(bool checked);

    void cbS7pl_1_toggled(bool checked);
    void cbS7pl_2_toggled(bool checked);
    void cbS7pl_3_toggled(bool checked);
    void cbS7pl_4_toggled(bool checked);
    void cbS7pl_5_toggled(bool checked);
    void cbS7pl_6_toggled(bool checked);
    void cbS7pl_7_toggled(bool checked);
    void cbS7pl_8_toggled(bool checked);

    void cbS7ts_1_toggled(bool checked);
    void cbS7ts_2_toggled(bool checked);
    void cbS7ts_3_toggled(bool checked);
    void cbS7ts_4_toggled(bool checked);
    void cbS7ts_5_toggled(bool checked);
    void cbS7ts_6_toggled(bool checked);
    void cbS7ts_7_toggled(bool checked);
    void cbS7ts_8_toggled(bool checked);

    // game options tab

    void setDialogColorUL(QColor color);
    void setDialogColorUR(QColor color);
    void setDialogColorLL(QColor color);
    void setDialogColorLR(QColor color);
    void setButtonMapping(int controlAction, int newButton);
    void setBattleHelp(bool checked);
    void setBattleTargets(bool checked);
    void setFieldHelp(bool checked);
    void setFieldMessageSpeed(int value);
    void setBattleMessageSpeed(int value);
    void setBattleSpeed(int value);

    void setMagicOrder(int order);
    void setCameraMode(int mode);
    void setAtbMode(int mode);
    void setCursorMode(int mode);
    void setControlMode(int mode);
    void setSoundMode(int mode);

    //save location tab
    void map_id_valueChanged(int);
    void loc_id_valueChanged(int);
    void coord_x_valueChanged(int);
    void coord_y_valueChanged(int);
    void coord_t_valueChanged(int);
    void coord_d_valueChanged(int);

    void locationSelectionChanged(QString);
    void location_textChanged(QString);

    //items tab
    void btnAddAllItems_clicked();
    void btnRemoveAllItems_clicked();

    // Materia Tab
    void tblMateria_currentCellChanged(int row);
    void materia_ap_changed(qint32 ap);
    void materia_id_changed(qint8 id);

    void cbRubyDead_toggled(bool checked);
    void cbEmeraldDead_toggled(bool checked);
    void comboSlotNumber_currentIndexChanged(int index);
    void comboHighwindBuggy_currentIndexChanged(int index);

//Map Stuff
    void sbLeaderX_valueChanged(int);
    void sbLeaderY_valueChanged(int);
    void sbLeaderZ_valueChanged(int);
    void sbLeaderId_valueChanged(int);
    void sbLeaderAngle_valueChanged(int);

    void sbTcX_valueChanged(int);
    void sbTcY_valueChanged(int);
    void sbTcZ_valueChanged(int);
    void sbTcId_valueChanged(int);
    void sbTcAngle_valueChanged(int);

    void sbBhX_valueChanged(int);
    void sbBhY_valueChanged(int);
    void sbBhZ_valueChanged(int);
    void sbBhId_valueChanged(int);
    void sbBhAngle_valueChanged(int);

    void sbSubX_valueChanged(int);
    void sbSubY_valueChanged(int);
    void sbSubZ_valueChanged(int);
    void sbSubId_valueChanged(int);
    void sbSubAngle_valueChanged(int);

    void sbDurwX_valueChanged(int);
    void sbDurwY_valueChanged(int);
    void sbDurwZ_valueChanged(int);
    void sbDurwId_valueChanged(int);
    void sbDurwAngle_valueChanged(int);

    void sbWcX_valueChanged(int);
    void sbWcY_valueChanged(int);
    void sbWcZ_valueChanged(int);
    void sbWcId_valueChanged(int);
    void sbWcAngle_valueChanged(int);

    void comboMapControls_currentIndexChanged(int index);
    void slideWorldX_valueChanged(int value);
    void slideWorldY_valueChanged(int value);
    void worldMapView_customContextMenuRequested(QPoint pos);

    void sbDonprog_valueChanged(int);
    void comboZVar_currentIndexChanged(int);
    void tblUnknown_itemChanged(QTableWidgetItem *item);

    void btnAddAllMateria_clicked();
    void comboCompareSlot_currentIndexChanged(int index);
    void sbSteps_valueChanged(int);
    void comboS7Slums_currentIndexChanged(int index);
    void cbVisibleBuggy_toggled(bool checked);
    void cbVisibleBronco_toggled(bool checked);
    void cbVisibleHighwind_toggled(bool checked);
    void cbVisibleWildChocobo_toggled(bool checked);
    void cbVisibleYellowChocobo_toggled(bool checked);
    void cbVisibleGreenChocobo_toggled(bool checked);
    void cbVisibleBlueChocobo_toggled(bool checked);
    void cbVisibleBlackChocobo_toggled(bool checked);
    void cbVisibleGoldChocobo_toggled(bool checked);
    void set_char_buttons();
    void sbSnowBegScore_valueChanged(int value);
    void sbSnowExpScore_valueChanged(int value);
    void sbSnowCrazyScore_valueChanged(int value);
    void sbSnowBegMin_valueChanged(int value);
    void sbSnowBegSec_valueChanged(int value);
    void sbSnowBegMsec_valueChanged(int value);
    void sbSnowExpMin_valueChanged(int value);
    void sbSnowExpSec_valueChanged(int value);
    void sbSnowExpMsec_valueChanged(int value);
    void sbSnowCrazyMin_valueChanged(int value);
    void sbSnowCrazySec_valueChanged(int value);
    void sbSnowCrazyMsec_valueChanged(int value);
    void sbBikeHighScore_valueChanged(int arg1);
    void sbBattlePoints_valueChanged(int arg1);

    void phsList_box_allowed_toggled(int row, bool checked);
    void phsList_box_visible_toggled(int row, bool checked);
    void menuList_box_locked_toggled(int row, bool checked);
    void menuList_box_visible_toggled(int row, bool checked);
    void sbCondorFunds_valueChanged(int arg1);
    void sbCondorWins_valueChanged(int arg1);
    void sbCondorLosses_valueChanged(int arg1);
    void cbPandorasBox_toggled(bool checked);
    //new feildItem Stuff
    void connectFieldItem(quint8, QList<quint16>, QList<quint8>);
    void checkFieldItem(int);
    void fieldItemStateChanged(int ID, bool checked);
    void sbSaveMapId_valueChanged(int arg1);
    void sbSaveX_valueChanged(int arg1);
    void sbSaveY_valueChanged(int arg1);
    void sbSaveZ_valueChanged(int arg1);
    void cbSubGameWon_toggled(bool checked);
    void cbMysteryPanties_toggled(bool checked);
    void cbLetterToDaughter_toggled(bool checked);
    void cbLetterToWife_toggled(bool checked);
    void btnSearchFlyers_clicked();
    void btnSearchKeyItems_clicked();
    void btnReplay_clicked();
    void linePsxDesc_textChanged(const QString &arg1);
    void cbFlashbackPiano_toggled(bool checked);
};
