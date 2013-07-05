/****************************************************************************/
//    copyright 2010-2013 Chris Rizzitello <sithlord48@gmail.com>           //
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui/QMainWindow>
    #include <QtGui/QWidget>
    #include <QMessageBox>
    #include <QFileDialog>              // for file dialogs
#endif

#include <QDataStream>              // for data manip
#include <QSettings>
#include <QtXml/QDomDocument>       // for metadata.xml parse
#include "options.h"                // contains the options dialog
#include "about.h"                  // about dialog stuff.
#include "errbox.h"                 // non ff7 error box
//FF7tk Items
#include "FF7tk/static_data/SaveIcon.h"
#include "FF7tk/static_data/FF7Item.h"
#include "FF7tk/static_data/FF7Save.h"
#include "FF7tk/static_data/FF7Char.h"
#include "FF7tk/static_data/FF7Materia.h"
#include "FF7tk/static_data/FF7Location.h"
#include "FF7tk/widgets/OptionsWidget.h"
#include "FF7tk/widgets/MateriaEditor.h"
#include "FF7tk/widgets/SlotSelect.h"
#include "FF7tk/widgets/ChocoboEditor.h"
#include "FF7tk/widgets/CharEditor.h"
#include "FF7tk/widgets/ItemList.h"
#include "FF7tk/widgets/MetadataCreator.h"
#include "FF7tk/widgets/PhsListWidget.h"
#include "FF7tk/widgets/MenuListWidget.h"
#include "FF7tk/widgets/ChocoboManager.h"
#include "FF7tk/widgets/LocationViewer.h"
//QHexedit
#include "qhexedit/qhexedit.h"

namespace Ui {
    class MainWindow;
    }

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0,FF7Save *ff7data=0,QSettings *config_data=0);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);
private:
    Ui::MainWindow *ui;
    bool skip_slot_mask;
    bool _init; //set true then false after a file load.
    bool load; // are we loading data? if so don't save it to the file.
    //bool showLocPreview;
    FF7Save *ff7; // our save file struct pointer.
    QSettings *settings;//Pointer To settings object.
    int s; //track slot
    FF7Char Chars; //FF7Char Static Data
    FF7Item Items; //FF7Item Static Data
    FF7Materia Materias;//FF7Materia Static Data.
    FF7Location Locations; // FF7 Location Data
    MATERIA buffer_materia; // buffer for a materia
    //ITEM buffer_item; // for use later
    int curchar; //keeps track of current character displayed
    int mslotsel; //keeps track of materia slot on char selected
    PhsListWidget *phsList;
    MenuListWidget *menuList;
    ItemPreview *item_preview;
    OptionsWidget *optionsWidget;
    MateriaEditor *materia_editor;
    QSpacerItem *mat_spacer;
    CharEditor * char_editor;
    ItemList *itemlist;
    ChocoboManager *chocoboManager;
    LocationViewer *locationViewer;
    QHexEdit *hexEditor;
    void init_display();
    void init_style();
    void init_connections();
    void init_settings();
public slots:
    void loadFileFull(const QString &fileName,int reload);//(Vegeta_Ss4) v0.8.3

private slots://try to keep these in the same order as the .cpp file  
    /*Loading and Saving related Functions*/
    int save_changes(void); //return 1 to accept and 0 to ingore the event
    void setControllerMappingVisible(bool);
    void on_actionNew_Window_triggered();
    void on_actionOpen_Save_File_triggered();
    void on_actionReload_triggered();
    void Items_Changed(QList<quint16>);
    void on_actionFrom_PSX_Slot_triggered();
    void on_actionFrom_PSV_Slot_triggered();
    void on_actionImport_char_triggered();
    void on_actionExport_char_triggered();
    void on_action_Save_triggered();
    void on_actionSave_File_As_triggered();
    void saveFileFull(QString);//(Vegeta_Ss4) v0.8.3
    void on_actionNew_Game_triggered();
    void on_actionNew_Game_Plus_triggered();
  /*Simple Menu Actions */
    void on_actionSlot_01_triggered();
    void on_actionSlot_02_triggered();
    void on_actionSlot_03_triggered();
    void on_actionSlot_04_triggered();
    void on_actionSlot_05_triggered();
    void on_actionSlot_06_triggered();
    void on_actionSlot_07_triggered();
    void on_actionSlot_08_triggered();
    void on_actionSlot_09_triggered();
    void on_actionSlot_10_triggered();
    void on_actionSlot_11_triggered();
    void on_actionSlot_12_triggered();
    void on_actionSlot_13_triggered();
    void on_actionSlot_14_triggered();
    void on_actionSlot_15_triggered();
    void on_actionShow_Selection_Dialog_triggered();
    void on_actionClear_Slot_triggered();
    void on_actionPrevious_Slot_triggered();
    void on_actionNext_Slot_triggered();
    void on_actionAbout_triggered();
    void on_actionCopy_Slot_triggered();
    void on_actionPaste_Slot_triggered();
    void on_actionShow_Options_triggered();
    void on_action_auto_char_growth_triggered(bool checked);
    void on_action_AdvancedMode_toggled(bool checked);
    /*Language and Region Data*/
    void on_action_Lang_en_triggered();
    void on_action_Lang_es_triggered();
    void on_action_Lang_fr_triggered();
    void on_action_Lang_de_triggered();
    void on_action_Lang_jp_triggered();
    void on_action_Region_USA_triggered(bool checked);
    void on_action_Region_PAL_Generic_triggered(bool checked);
    void on_action_Region_PAL_French_triggered(bool checked);
    void on_action_Region_PAL_German_triggered(bool checked);
    void on_action_Region_PAL_Spanish_triggered(bool checked);
    void on_action_Region_JPN_triggered(bool checked);
    void on_action_Region_JPN_International_triggered(bool checked);
    /*GuiFunctions*/
    void setmenu(bool newgame);
    void materiaupdate(void);
    void itemupdate(void);
    void guirefresh(bool newgame);
    void progress_update(void);
    void unknown_refresh(int);
    void set_ntsc_time(void);
    void set_pal_time(void);
    void CheckGame(void);
    void othersUpdate();
    void on_tabWidget_currentChanged(int index);
    void on_locationToolBox_currentChanged(int index);
    void on_testDataTabWidget_currentChanged(int index);
    void fileModified(bool changed);
    //QString avatar_style(int);

    /*CharButtons*/
    void on_btn_cloud_clicked();
    void on_btn_barret_clicked();
    void on_btn_tifa_clicked();
    void on_btn_aeris_clicked();
    void on_btn_red_clicked();
    void on_btn_yuffie_clicked();
    void on_btn_cait_clicked();
    void on_btn_vincent_clicked();
    void on_btn_cid_clicked();
    /*PARTY TAB*/
    void on_sb_gil_valueChanged(int);
    void on_sb_gp_valueChanged(int);
    void on_sb_battles_valueChanged(int);
    void on_sb_runs_valueChanged(int);
    void on_combo_party1_currentIndexChanged(int index);
    void on_combo_party2_currentIndexChanged(int index);
    void on_combo_party3_currentIndexChanged(int index);
    /*Chocobo Tab*/
    /* ChocoboManager*/
    void cm_stablesOwnedChanged(qint8);
    void cm_stablesOccupiedChanged(qint8);
    void cm_stableMaskChanged(qint8);
    void cm_nameChanged(int,QString);
    void cm_staminaChanged(int,quint16);
    void cm_speedChanged(int,quint16);
    void cm_maxspeedChanged(int,quint16);
    void cm_sprintChanged(int,quint16);
    void cm_maxsprintChanged(int,quint16);
    void cm_sexChanged(int,quint8);
    void cm_typeChanged(int,quint8);
    void cm_coopChanged(int,quint8);
    void cm_accelChanged(int,quint8);
    void cm_intelChanged(int,quint8);
    void cm_raceswonChanged(int,quint8);
    void cm_pcountChanged(int,quint8);
    void cm_personalityChanged(int,quint8);
    void cm_mated_toggled(int,bool);
    void cm_pensChanged(int pen,int index);

    //The Chocobo pens.

    /* Others Tab */    
    void on_sb_curdisc_valueChanged(int);
    void on_sb_love_yuffie_valueChanged(int);
    void on_sb_love_tifa_valueChanged(int);
    void on_sb_love_aeris_valueChanged(int);
    void on_sb_love_barret_valueChanged(int);
    void on_sb_time_sec_valueChanged(int);
    void on_sb_time_min_valueChanged(int);
    void on_sb_time_hour_valueChanged(int);


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

    void on_cb_tut_sub_8_toggled(bool);
    void on_cb_tut_sub_7_toggled(bool);
    void on_cb_tut_sub_6_toggled(bool);
    void on_cb_tut_sub_5_toggled(bool);
    void on_cb_tut_sub_4_toggled(bool);
    void on_cb_tut_sub_3_toggled(bool);
    void on_sb_timer_time_sec_valueChanged(int);
    void on_cb_tut_worldsave_stateChanged(int);
    void on_cb_bombing_int_stateChanged(int);
    void on_cb_tut_sub_toggled(bool checked);
    void on_cb_tut_sub_1_toggled(bool);
    void on_cb_tut_sub_2_toggled(bool);
    void on_sb_timer_time_min_valueChanged(int);
    void on_sb_timer_time_hour_valueChanged(int);
    void on_cb_midgartrain_8_toggled(bool);
    void on_cb_midgartrain_7_toggled(bool);
    void on_cb_midgartrain_6_toggled(bool);
    void on_cb_midgartrain_5_toggled(bool);
    void on_cb_midgartrain_4_toggled(bool);
    void on_cb_midgartrain_3_toggled(bool);
    void on_cb_midgartrain_2_toggled(bool);
    void on_cb_midgartrain_1_toggled(bool);
    void on_cb_yuffieforest_toggled(bool);
    void on_cb_reg_yuffie_toggled(bool);
    void on_cb_materiacave_1_toggled(bool);
    void on_cb_materiacave_2_toggled(bool);
    void on_cb_materiacave_3_toggled(bool);
    void on_cb_materiacave_4_toggled(bool);

    void on_cb_itemmask1_1_toggled(bool);
    void on_cb_itemmask1_2_toggled(bool);
    void on_cb_itemmask1_3_toggled(bool);
    void on_cb_itemmask1_4_toggled(bool);
    void on_cb_itemmask1_5_toggled(bool);
    void on_cb_itemmask1_6_toggled(bool);
    void on_cb_itemmask1_7_toggled(bool);
    void on_cb_itemmask1_8_toggled(bool);

    void on_cb_reg_vinny_toggled(bool);

    void on_sb_u_weapon_hp_valueChanged(int);
    void on_sb_coster_1_valueChanged(int);
    void on_sb_coster_2_valueChanged(int);
    void on_sb_coster_3_valueChanged(int);
    void on_sb_b_love_barret_valueChanged(int);
    void on_sb_b_love_yuffie_valueChanged(int);
    void on_sb_b_love_tifa_valueChanged(int);
    void on_sb_b_love_aeris_valueChanged(int);

    void on_sb_turkschruch_valueChanged(int );

    void on_btn_remove_all_materia_clicked();
    void on_btn_remove_all_stolen_clicked();

    //progress functions

    void on_cb_replay_currentIndexChanged(int index);
    void on_sb_mprogress_valueChanged(int value);

    void on_cb_bm1_1_toggled(bool checked);
    void on_cb_bm1_2_toggled(bool checked);
    void on_cb_bm1_3_toggled(bool checked);
    void on_cb_bm1_4_toggled(bool checked);
    void on_cb_bm1_5_toggled(bool checked);
    void on_cb_bm1_6_toggled(bool checked);
    void on_cb_bm1_7_toggled(bool checked);
    void on_cb_bm1_8_toggled(bool checked);

    void on_cb_bm2_1_toggled(bool checked);
    void on_cb_bm2_2_toggled(bool checked);
    void on_cb_bm2_3_toggled(bool checked);
    void on_cb_bm2_4_toggled(bool checked);
    void on_cb_bm2_5_toggled(bool checked);
    void on_cb_bm2_6_toggled(bool checked);
    void on_cb_bm2_7_toggled(bool checked);
    void on_cb_bm2_8_toggled(bool checked);

    void on_cb_bm3_1_toggled(bool checked);
    void on_cb_bm3_2_toggled(bool checked);
    void on_cb_bm3_3_toggled(bool checked);
    void on_cb_bm3_4_toggled(bool checked);
    void on_cb_bm3_5_toggled(bool checked);
    void on_cb_bm3_6_toggled(bool checked);
    void on_cb_bm3_7_toggled(bool checked);
    void on_cb_bm3_8_toggled(bool checked);

    void on_cb_s7pl_1_toggled(bool checked);
    void on_cb_s7pl_2_toggled(bool checked);
    void on_cb_s7pl_3_toggled(bool checked);
    void on_cb_s7pl_4_toggled(bool checked);
    void on_cb_s7pl_5_toggled(bool checked);
    void on_cb_s7pl_6_toggled(bool checked);
    void on_cb_s7pl_7_toggled(bool checked);
    void on_cb_s7pl_8_toggled(bool checked);

    void on_cb_s7ts_1_toggled(bool checked);
    void on_cb_s7ts_2_toggled(bool checked);
    void on_cb_s7ts_3_toggled(bool checked);
    void on_cb_s7ts_4_toggled(bool checked);
    void on_cb_s7ts_5_toggled(bool checked);
    void on_cb_s7ts_6_toggled(bool checked);
    void on_cb_s7ts_7_toggled(bool checked);
    void on_cb_s7ts_8_toggled(bool checked);

    void on_cb_farm_items_1_toggled(bool checked);
    void on_cb_farm_items_2_toggled(bool checked);
    void on_cb_farm_items_3_toggled(bool checked);
    void on_cb_farm_items_4_toggled(bool checked);
    void on_cb_farm_items_5_toggled(bool checked);
    void on_cb_farm_items_6_toggled(bool checked);
    void on_cb_farm_items_7_toggled(bool checked);
    void on_cb_farm_items_8_toggled(bool checked);

    void on_cb_s5_1_toggled(bool checked);
    void on_cb_s5_2_toggled(bool checked);
    void on_cb_s5_3_toggled(bool checked);
    void on_cb_s5_4_toggled(bool checked);
    void on_cb_s5_5_toggled(bool checked);
    void on_cb_s5_6_toggled(bool checked);
    void on_cb_s5_7_toggled(bool checked);
    void on_cb_s5_8_toggled(bool checked);

    // game options tab

    void setDialogColorUL(QColor color);
    void setDialogColorUR(QColor color);
    void setDialogColorLL(QColor color);
    void setDialogColorLR(QColor color);

    void setButtonCamera(int index);
    void setButtonTarget(int index);
    void setButtonPageUp(int index);
    void setButtonPageDown(int index);
    void setButtonMenu(int index);
    void setButtonOk(int index);
    void setButtonCancel(int index);
    void setButtonSwitch(int index);
    void setButtonHelp(int index);
    void setButtonUnknown1(int index);
    void setButtonUnknown2(int index);
    void setButtonPause(int index);
    void setButtonUp(int index);
    void setButtonDown(int index);
    void setButtonLeft(int index);
    void setButtonRight(int index);

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
    void on_list_flyers_clicked(const QModelIndex &index);
    void on_list_keyitems_clicked(const QModelIndex &index);
    void on_btn_item_add_each_item_clicked();
    void on_btn_remove_all_items_clicked();
    void on_cb_bm_items_1_toggled(bool checked);
    void on_cb_bm_items_2_toggled(bool checked);
    void on_cb_bm_items_3_toggled(bool checked);
    void on_cb_bm_items_4_toggled(bool checked);

    void on_cb_s7tg_items_1_toggled(bool checked);
    void on_cb_s7tg_items_2_toggled(bool checked);
    void on_cb_s7tg_items_3_toggled(bool checked);
    void on_cb_s7tg_items_4_toggled(bool checked);
    void on_cb_s7tg_items_5_toggled(bool checked);
    void on_cb_s7tg_items_6_toggled(bool checked);
    void on_cb_s7tg_items_7_toggled(bool checked);
    void on_cb_s7tg_items_8_toggled(bool checked);

    // Materia Tab
    void on_tbl_materia_currentCellChanged(int row);
    void materia_ap_changed(qint32 ap);
    void materia_id_changed(qint8 id);  

    void on_cb_Region_Slot_currentIndexChanged();
    void on_cb_ruby_dead_toggled(bool checked);
    void on_cb_emerald_dead_toggled(bool checked);
    void on_combo_highwind_buggy_currentIndexChanged(int index);

//Map Stuff
    void on_leader_x_valueChanged(int);
    void on_leader_y_valueChanged(int);
    void on_leader_z_valueChanged(int);
    void on_leader_id_valueChanged(int);
    void on_leader_angle_valueChanged(int);

    void on_tc_x_valueChanged(int);
    void on_tc_y_valueChanged(int);
    void on_tc_z_valueChanged(int);
    void on_tc_id_valueChanged(int);
    void on_tc_angle_valueChanged(int);

    void on_bh_x_valueChanged(int);
    void on_bh_y_valueChanged(int);
    void on_bh_z_valueChanged(int);
    void on_bh_id_valueChanged(int);
    void on_bh_angle_valueChanged(int);

    void on_sub_x_valueChanged(int);
    void on_sub_id_valueChanged(int);
    void on_sub_angle_valueChanged(int);
    void on_sub_y_valueChanged(int);
    void on_sub_z_valueChanged(int);

    void on_durw_x_valueChanged(int);
    void on_durw_y_valueChanged(int);
    void on_durw_z_valueChanged(int);
    void on_durw_id_valueChanged(int);
    void on_durw_angle_valueChanged(int);

    void on_uw_x_valueChanged(int);
    void on_uw_y_valueChanged(int);
    void on_uw_z_valueChanged(int);
    void on_uw_id_valueChanged(int);
    void on_uw_angle_valueChanged(int);

    void on_combo_map_controls_currentIndexChanged(int index);
    void on_slide_world_x_valueChanged(int value);
    void on_slide_world_y_valueChanged(int value);
    void on_world_map_view_customContextMenuRequested(QPoint pos);

    void on_btn_clear_keyitems_clicked();
    void on_sb_donprog_valueChanged(int );
    void on_combo_z_var_currentIndexChanged(int);
    void on_tbl_unknown_itemChanged(QTableWidgetItem* item);

    void on_btn_add_all_materia_clicked();
    void on_combo_compare_slot_currentIndexChanged(void);
    void on_btn_all_z_diffs_clicked();
    void on_sb_steps_valueChanged(int );

    void on_combo_s7_slums_currentIndexChanged(int index);
    void on_cb_visible_buggy_toggled(bool checked);
    void on_cb_visible_bronco_toggled(bool checked);
    void on_cb_visible_highwind_toggled(bool checked);
    void on_cb_visible_wild_chocobo_toggled(bool checked);
    void on_cb_visible_yellow_chocobo_toggled(bool checked);
    void on_cb_visible_green_chocobo_toggled(bool checked);
    void on_cb_visible_blue_chocobo_toggled(bool checked);
    void on_cb_visible_black_chocobo_toggled(bool checked);
    void on_cb_visible_gold_chocobo_toggled(bool checked);
    void set_char_buttons();
    void on_btn_maxChar_clicked();
    void on_sbSnowBegScore_valueChanged(int value);
    void on_sbSnowExpScore_valueChanged(int value);
    void on_sbSnowCrazyScore_valueChanged(int value);
    void on_sbSnowBegMin_valueChanged(int value);
    void on_sbSnowBegSec_valueChanged(int value);
    void on_sbSnowBegMsec_valueChanged(int value);
    void on_sbSnowExpMin_valueChanged(int value);
    void on_sbSnowExpSec_valueChanged(int value);
    void on_sbSnowExpMsec_valueChanged(int value);
    void on_sbSnowCrazyMin_valueChanged(int value);
    void on_sbSnowCrazySec_valueChanged(int value);
    void on_sbSnowCrazyMsec_valueChanged(int value);
    void on_sb_BikeHighScore_valueChanged(int arg1);
    void on_sb_BattlePoints_valueChanged(int arg1);
    void on_actionCreateNewMetadata_triggered();
    void hexEditorRefresh();
    void on_combo_hexEditor_currentIndexChanged(void);
    void hexEditorChanged(void);
    void phsList_box_allowed_toggled(int row, bool checked);
    void phsList_box_visible_toggled(int row, bool checked);
    void menuList_box_locked_toggled(int row, bool checked);
    void menuList_box_visible_toggled(int row, bool checked);
    void on_cb_gaiin_1Javelin_toggled(bool checked);
    void on_cb_gaiin_1Ribbon_toggled(bool checked);
    void on_cb_gaiin_3Elixir_toggled(bool checked);
    void on_cb_gaiin_3SpeedSource_toggled(bool checked);
    void on_cb_gaiin_4EnhanceSword_toggled(bool checked);
    void on_cb_gaiin_5FireArmlet_toggled(bool checked);
    void on_cb_gaiin_5Elixir_toggled(bool checked);
    void on_cb_snmayorTurboEther_toggled(bool checked);
    void on_cb_sninn2XPotion_toggled(bool checked);
    void on_cb_snmin2Vaccine_toggled(bool checked);
    void on_cb_snmin2HeroDrink_toggled(bool checked);
    void on_cb_ncoin3Catastrophe_toggled(bool checked);
    void on_cb_ncoin1Ether_toggled(bool checked);
    void on_cb_trnad_4PoisonRing_toggled(bool checked);
    void on_cb_trnad_4MpTurbo_toggled(bool checked);
    void on_cb_trnad_3KaiserKnuckle_toggled(bool checked);
    void on_cb_trnad_2NeoBahmut_toggled(bool checked);
    void on_sbCondorFunds_valueChanged(int arg1);
    void on_sbCondorWins_valueChanged(int arg1);
    void on_sbCondorLoses_valueChanged(int arg1);
};
#endif // MAINWINDOW_H
