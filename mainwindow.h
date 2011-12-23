/****************************************************************************/
//    copyright 2010, 2011 Chris Rizzitello <sithlord48@gmail.com>          //
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

#include <QFileDialog> // for file dialogs
#include <QDataStream> // for data manip
#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include "slotselect.h" // slot selection dialog stuff.
#include "options.h" // contains the options dialog
#include "about.h"      // about dialog stuff.
#include "errbox.h" //non ff7 error box
#include <QSettings>
#include <SaveIcon.h>



namespace Ui {
    class MainWindow;
    }

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0,FF7 *ff7data=0,QSettings *config_data=0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);
    //void closeEvent();
private:
    Ui::MainWindow *ui;
    bool skip_slot_mask;
    bool _init; //set true then false after a file load.
    bool load; // are we loading data? if so don't save it to the file.
    bool file_changed; //if file changed after load.
    FF7 *ff7; // our save file struct pointer.
    QSettings *settings;
    int s; //track slot
    ff7names FF7Strings; //class of strings used in ff7
    FF7SLOT bufferslot; // a buffer slot to keep copied slots in
    QString buffer_region; //holds region data for bufferslot.
    MATERIA buffer_materia; // buffer for a materia
    //ITEM buffer_item; // for use later
    QString filename; //holds file name
    int curchar; //keeps track of current character displayed
    int mslotsel; //keeps track of materia slot on char selected
    TEXT Text; //our sting conversion item.
public slots:
    void loadFileFull(const QString &fileName,int reload);//(Vegeta_Ss4) v0.8.3

private slots://try to keep these in the same order as the .cpp file  
    /*Loading and Saving related Functions*/
    int save_changes(); //return 1 to accept and 0 to ingore the event
    void setPreviewColors();
    void on_actionNew_Window_triggered();
    void on_actionOpen_Save_File_activated();
    void on_actionReload_triggered();

    void on_actionFrom_PSX_Slot_activated();
    void on_actionFrom_PSV_Slot_activated();
    void on_actionImport_char_triggered();
    void on_actionExport_char_triggered();
    void on_action_Save_activated();
    void on_actionSave_File_As_activated();
    void saveFileFull(QString);//(Vegeta_Ss4) v0.8.3
    void on_actionNew_Game_triggered();
    void on_actionNew_Game_Plus_triggered();
    void on_actionExport_PC_Save_activated();
    void on_actionExport_PSX_activated();
    void on_actionExport_MC_triggered();
    void on_actionExport_VGS_triggered();
    void on_actionExport_DEX_triggered();  
  /*Simple Menu Actions */
    void on_actionSlot_01_activated();
    void on_actionSlot_02_activated();
    void on_actionSlot_03_activated();
    void on_actionSlot_04_activated();
    void on_actionSlot_05_activated();
    void on_actionSlot_06_activated();
    void on_actionSlot_07_activated();
    void on_actionSlot_08_activated();
    void on_actionSlot_09_activated();
    void on_actionSlot_10_activated();
    void on_actionSlot_11_activated();
    void on_actionSlot_12_activated();
    void on_actionSlot_13_activated();
    void on_actionSlot_14_activated();
    void on_actionSlot_15_activated();
    void on_actionShow_Selection_Dialog_activated();
    void on_actionClear_Slot_activated();
    void on_actionPrevious_Slot_activated();
    void on_actionNext_Slot_activated();
    void on_actionAbout_activated();
    void on_actionAbout_Qt_activated();
    void on_actionCopy_Slot_activated();
    void on_actionPaste_Slot_activated();
    void on_actionShow_Options_triggered();
    void on_action_auto_char_growth_triggered(bool checked);
    void on_action_show_debug_toggled(bool checked);
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
    void fix_sum(const QString &fileName);
    void charupdate(void);
    void update_stat_totals(void);
    void weapon_stat(void);
    void setchar_growth(int caller);
    void setarmorslots(void);
    void setweaponslots(void);
    void setmenu(bool newgame);
    void materiaupdate_slot(void);
    void materiaupdate(void);
    void itemupdate(void);
    void guirefresh(bool newgame);
    void chocobo_refresh(void);
    void progress_update(void);
    void clearslot(int rmslot);
    void testdata_refresh(void);
    void unknown_refresh(int);
    void set_ntsc_time(void);
    void set_pal_time(void);

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
    void on_sb_stables_owned_valueChanged(int);
    void on_box_stable1_toggled(bool checked);
    void on_box_stable2_toggled(bool checked);
    void on_box_stable3_toggled(bool checked);
    void on_box_stable4_toggled(bool checked);
    void on_box_stable5_toggled(bool checked);
    void on_box_stable6_toggled(bool checked);
    /*Chocobo Stall #1*/
    void on_line_c1_name_textChanged(QString text);
    void on_sb_c1_stamina_valueChanged(int);
    void on_sb_c1_speed_valueChanged(int);
    void on_sb_c1_maxspeed_valueChanged(int);
    void on_sb_c1_sprint_valueChanged(int);
    void on_sb_c1_maxsprint_valueChanged(int);
    void on_cb_c1_sex_currentIndexChanged(int index);
    void on_cb_c1_type_currentIndexChanged(int index);
    void on_sb_c1_coop_valueChanged(int);
    void on_sb_c1_accel_valueChanged(int);
    void on_sb_c1_intel_valueChanged(int);
    void on_sb_c1_raceswon_valueChanged(int);
    void on_sb_c1_pcount_valueChanged(int);
    void on_sb_c1_personality_valueChanged(int);
    void on_cb_c1_mated_toggled(bool checked);
    /*Chocobo Stall #2*/
    void on_line_c2_name_textChanged(QString text);
    void on_sb_c2_stamina_valueChanged(int);
    void on_sb_c2_speed_valueChanged(int);
    void on_sb_c2_maxspeed_valueChanged(int);
    void on_sb_c2_sprint_valueChanged(int);
    void on_sb_c2_maxsprint_valueChanged(int);
    void on_cb_c2_sex_currentIndexChanged(int index);
    void on_cb_c2_type_currentIndexChanged(int index);
    void on_sb_c2_coop_valueChanged(int);
    void on_sb_c2_accel_valueChanged(int);
    void on_sb_c2_intel_valueChanged(int);
    void on_sb_c2_raceswon_valueChanged(int);
    void on_sb_c2_pcount_valueChanged(int);
    void on_sb_c2_personality_valueChanged(int);
    void on_cb_c2_mated_toggled(bool checked);
    /*Chocobo Stall #3*/
    void on_line_c3_name_textChanged(QString text);
    void on_sb_c3_stamina_valueChanged(int);
    void on_sb_c3_speed_valueChanged(int);
    void on_sb_c3_maxspeed_valueChanged(int);
    void on_sb_c3_sprint_valueChanged(int);
    void on_sb_c3_maxsprint_valueChanged(int);
    void on_cb_c3_sex_currentIndexChanged(int index);
    void on_cb_c3_type_currentIndexChanged(int index);
    void on_sb_c3_coop_valueChanged(int);
    void on_sb_c3_accel_valueChanged(int);
    void on_sb_c3_intel_valueChanged(int);
    void on_sb_c3_raceswon_valueChanged(int);
    void on_sb_c3_pcount_valueChanged(int);
    void on_sb_c3_personality_valueChanged(int);
    void on_cb_c3_mated_toggled(bool checked);
    /*Chocobo Stall #4*/
    void on_line_c4_name_textChanged(QString text);
    void on_sb_c4_stamina_valueChanged(int);
    void on_sb_c4_speed_valueChanged(int);
    void on_sb_c4_maxspeed_valueChanged(int);
    void on_sb_c4_sprint_valueChanged(int);
    void on_sb_c4_maxsprint_valueChanged(int);
    void on_cb_c4_sex_currentIndexChanged(int index);
    void on_cb_c4_type_currentIndexChanged(int index);
    void on_sb_c4_coop_valueChanged(int);
    void on_sb_c4_accel_valueChanged(int);
    void on_sb_c4_intel_valueChanged(int);
    void on_sb_c4_raceswon_valueChanged(int);
    void on_sb_c4_pcount_valueChanged(int);
    void on_sb_c4_personality_valueChanged(int);
    void on_cb_c4_mated_toggled(bool checked);
    /*Chocobo Stall #5*/
    void on_line_c5_name_textChanged(QString text);
    void on_sb_c5_stamina_valueChanged(int);
    void on_sb_c5_speed_valueChanged(int);
    void on_sb_c5_maxspeed_valueChanged(int);
    void on_sb_c5_sprint_valueChanged(int);
    void on_sb_c5_maxsprint_valueChanged(int);
    void on_cb_c5_sex_currentIndexChanged(int index);
    void on_cb_c5_type_currentIndexChanged(int index);
    void on_sb_c5_coop_valueChanged(int);
    void on_sb_c5_accel_valueChanged(int);
    void on_sb_c5_intel_valueChanged(int);
    void on_sb_c5_raceswon_valueChanged(int);
    void on_sb_c5_pcount_valueChanged(int);
    void on_sb_c5_personality_valueChanged(int);
    void on_cb_c5_mated_toggled(bool checked);
    /*Chocobo Stall #6*/
    void on_line_c6_name_textChanged(QString text);
    void on_sb_c6_stamina_valueChanged(int);
    void on_sb_c6_speed_valueChanged(int);
    void on_sb_c6_maxspeed_valueChanged(int);
    void on_sb_c6_sprint_valueChanged(int);
    void on_sb_c6_maxsprint_valueChanged(int);
    void on_cb_c6_sex_currentIndexChanged(int index);
    void on_cb_c6_type_currentIndexChanged(int index);
    void on_sb_c6_coop_valueChanged(int);
    void on_sb_c6_accel_valueChanged(int);
    void on_sb_c6_intel_valueChanged(int);
    void on_sb_c6_raceswon_valueChanged(int);
    void on_sb_c6_pcount_valueChanged(int);
    void on_sb_c6_personality_valueChanged(int);
    void on_cb_c6_mated_toggled(bool checked);

    //The Chocobo pens.
    void on_combo_pen1_currentIndexChanged(int index);
    void on_combo_pen2_currentIndexChanged(int index);
    void on_combo_pen3_currentIndexChanged(int index);
    void on_combo_pen4_currentIndexChanged(int index);
    /* Others Tab */    
    void on_list_phs_chars_itemChanged(QListWidgetItem*);
    void on_list_chars_unlocked_itemChanged(QListWidgetItem*);
    void on_sb_curdisc_valueChanged(int);
    void on_sb_love_yuffie_valueChanged(int);
    void on_sb_love_tifa_valueChanged(int);
    void on_sb_love_aeris_valueChanged(int);
    void on_sb_love_barret_valueChanged(int);
    void on_sb_time_sec_valueChanged(int);
    void on_sb_time_min_valueChanged(int);
    void on_sb_time_hour_valueChanged(int);


//NOT IN ORDER FROM HERE DOWN
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
    void on_list_menu_locked_itemChanged(QListWidgetItem*);
    void on_list_menu_visible_itemChanged(QListWidgetItem*);

    void on_sb_turkschruch_valueChanged(int );


    void on_cb_id_toggled(bool checked);

    void on_slide_lr_b_valueChanged(int value);
    void on_slide_lr_g_valueChanged(int value);
    void on_slide_lr_r_valueChanged(int value);
    void on_slide_ll_b_valueChanged(int value);
    void on_slide_ll_g_valueChanged(int value);
    void on_slide_ll_r_valueChanged(int value);
    void on_slide_ur_b_valueChanged(int value);
    void on_slide_ur_g_valueChanged(int value);
    void on_slide_ur_r_valueChanged(int value);
    void on_slide_ul_b_valueChanged(int value);
    void on_slide_ul_g_valueChanged(int value);
    void on_slide_ul_r_valueChanged(int value);
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
    void setoptions_one();
    void setoptions_two();
    void on_cb_battle_help_toggled();
    void on_cb_battle_targets_toggled(bool checked);
    void on_cb_field_help_toggled(bool checked);
    void on_combo_magic_order_currentIndexChanged();
    void on_combo_camera_currentIndexChanged();
    void on_combo_atb_currentIndexChanged();
    void on_combo_cursor_currentIndexChanged();
    void on_combo_control_currentIndexChanged();
    void on_combo_sound_currentIndexChanged();
    void on_slide_fieldmspeed_valueChanged(int value);
    void on_slide_battlemspeed_valueChanged(int value);
    void on_slide_battlespeed_valueChanged(int value);

    //save location tab
    void on_sb_map_id_valueChanged(int);
    void on_sb_loc_id_valueChanged(int);
    void on_sb_coordx_valueChanged(int);
    void on_sb_coordy_valueChanged(int);
    void on_sb_coordz_valueChanged(int);
    void on_line_location_textChanged(QString);
    void on_tbl_location_field_itemSelectionChanged();


    //items tab
    void on_list_flyers_itemChanged(QListWidgetItem*);
    void on_list_keyitems_itemChanged(QListWidgetItem*);
    void on_tbl_itm_currentCellChanged(int row);
    void on_combo_additem_currentIndexChanged(int);
    void on_sb_addqty_valueChanged(int);
    void on_clearItem_clicked();
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
    void on_clearMateria_clicked();
    void on_combo_add_mat_currentIndexChanged(int index);
    void on_sb_addap_valueChanged(int);
    void on_btn_eskillall_clicked();
    void geteskills(int row);
    void on_btn_eskillclear_clicked();
    void on_list_eskill_itemChanged();
    void on_combo_add_mat_2_currentIndexChanged();
    void on_combo_mat_type_currentIndexChanged(int index);
    void on_btn_m_lvl5_clicked();
    void on_btn_m_lvl4_clicked();
    void on_btn_m_lvl3_clicked();
    void on_btn_m_lvl2_clicked();
    void on_btn_m_lvl1_clicked();

//char stats

    void on_line_name_textChanged(QString text);
    void on_sb_lvl_valueChanged(int value);
    void on_sb_exp_valueChanged();
    void on_sb_kills_valueChanged();
    void on_cb_front_clicked(bool checked);
    void on_cb_fury_clicked(bool checked);
    void on_cb_sadness_clicked(bool checked);
    void on_sb_hp_valueChanged();
    void on_sb_mp_valueChanged();
    void on_sb_maxmp_valueChanged();
    void on_sb_maxhp_valueChanged();
    void on_sb_curhp_valueChanged();
    void on_sb_curmp_valueChanged();
    void on_sb_str_valueChanged();
    void on_sb_strbonus_valueChanged();
    void on_sb_dex_valueChanged();
    void on_sb_dexbonus_valueChanged();
    void on_sb_mag_valueChanged();
    void on_sb_magbonus_valueChanged();
    void on_sb_vit_valueChanged();
    void on_sb_vitbonus_valueChanged();
    void on_sb_spi_valueChanged();
    void on_sb_spibonus_valueChanged();
    void on_sb_lck_valueChanged();
    void on_sb_lckbonus_valueChanged();
    void on_combo_mat_type_slot_currentIndexChanged(int);
    void on_combo_add_mat_slot_2_currentIndexChanged();
    // LIMITS STUFFS
    void on_limit_1a_toggled();
    void on_limit_1b_toggled();
    void on_limit_2a_toggled();
    void on_limit_2b_toggled();
    void on_limit_3a_toggled();
    void on_limit_3b_toggled();
    void on_limit_4_toggled();
    void limitapply();
    void on_sb_limitlvl_valueChanged(int);
    void on_slide_limit_valueChanged(int);
    void on_sb_used1_valueChanged();
    void on_sb_used2_valueChanged();
    void on_sb_used3_valueChanged();

    //char equipment Tab
    void on_combo_weapon_activated(int);
    void on_combo_weapon_currentIndexChanged();
    void on_combo_armor_currentIndexChanged(int);
    void on_combo_acc_currentIndexChanged(int);
    void on_a_m_s1_clicked();
    void on_a_m_s2_clicked();
    void on_a_m_s3_clicked();
    void on_a_m_s4_clicked();
    void on_a_m_s5_clicked();
    void on_a_m_s6_clicked();
    void on_a_m_s7_clicked();
    void on_a_m_s8_clicked();
    void on_w_m_s1_clicked();
    void on_w_m_s2_clicked();
    void on_w_m_s3_clicked();
    void on_w_m_s4_clicked();
    void on_w_m_s5_clicked();
    void on_w_m_s6_clicked();
    void on_w_m_s7_clicked();
    void on_w_m_s8_clicked();
    void on_clearMateria_slot_clicked();
    void on_sb_addap_slot_valueChanged(int);
    void on_combo_add_mat_slot_currentIndexChanged(int index);
    void geteskills2(int row);
    void on_btn_m_lvl5_slot_clicked();
    void on_btn_m_lvl4_slot_clicked();
    void on_btn_m_lvl3_slot_clicked();
    void on_btn_m_lvl2_slot_clicked();
    void on_btn_m_lvl1_slot_clicked();
    void on_list_eskill_2_itemChanged();
    void on_cb_Region_Slot_currentIndexChanged();
    void on_combo_id_currentIndexChanged(int index);
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

    void on_ew_x_valueChanged(int);
    void on_ew_y_valueChanged(int);
    void on_ew_z_valueChanged(int);
    void on_ew_id_valueChanged(int);
    void on_ew_angle_valueChanged(int);
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
    void on_combo_button_1_currentIndexChanged(int index);
    void on_combo_button_2_currentIndexChanged(int index);
    void on_combo_button_3_currentIndexChanged(int index);
    void on_combo_button_4_currentIndexChanged(int index);
    void on_combo_button_5_currentIndexChanged(int index);
    void on_combo_button_6_currentIndexChanged(int index);
    void on_combo_button_7_currentIndexChanged(int index);
    void on_combo_button_8_currentIndexChanged(int index);
    void on_combo_button_9_currentIndexChanged(int index);
    void on_combo_button_10_currentIndexChanged(int index);
    void on_combo_button_11_currentIndexChanged(int index);
    void on_combo_button_12_currentIndexChanged(int index);
    void on_combo_button_13_currentIndexChanged(int index);
    void on_combo_button_14_currentIndexChanged(int index);
    void on_combo_button_15_currentIndexChanged(int index);
    void on_combo_button_16_currentIndexChanged(int index);
    void on_btn_copy_materia_clicked();
    void on_btn_paste_materia_clicked();
    void on_btn_copy_materia_slot_clicked();
    void on_btn_paste_materia_slot_clicked();
    void on_combo_s7_slums_currentIndexChanged(int index);
    void on_cb_visible_buggy_toggled(bool checked);
    void on_cb_visible_bronco_toggled(bool checked);
    void on_cb_visible_highwind_toggled(bool checked);
};
#endif // MAINWINDOW_H
