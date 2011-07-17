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

void fix_sum(const QString &fileName);


namespace Ui {
    class MainWindow;
    }

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

public slots:

private slots:
    void on_cb_tut_sub_8_toggled(bool);
    void on_cb_tut_sub_7_toggled(bool);
    void on_cb_tut_sub_6_toggled(bool);
    void on_cb_tut_sub_5_toggled(bool);
    void on_cb_tut_sub_4_toggled(bool);
    void on_cb_tut_sub_3_toggled(bool);
    void on_cb_tut_sub_2_toggled(bool);
    void on_cb_tut_sub_1_toggled(bool);
    void on_cb_tut_sub_toggled(bool checked);
    void on_cb_bombing_int_stateChanged(int);
    void on_cb_tut_worldsave_stateChanged(int);
    void on_sb_timer_time_sec_valueChanged(int);
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
    void on_list_menu_locked_itemChanged();
    void on_list_menu_visible_itemChanged();

    void on_sb_turkschruch_valueChanged(int );
    void on_actionEdit_Paths_triggered();

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

    //wip functions

    void on_cb_replay_currentIndexChanged(int index);
    void on_sb_bm_progress1_valueChanged(int);
    void on_sb_bm_progress2_valueChanged(int);
    void on_sb_bm_progress3_valueChanged(int);
    void on_sb_mprogress_valueChanged();
    void on_cb_c2_born_toggled(bool checked);

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
    void on_sb_coordz_valueChanged();
    void on_sb_coordy_valueChanged();
    void on_sb_coordx_valueChanged();
    void on_line_location_textChanged();
    void on_sb_loc_id_valueChanged();
    void on_sb_map_id_valueChanged();
    void on_tbl_location_field_itemSelectionChanged();


    //other tab
    void on_list_chars_unlocked_itemChanged();
    void on_list_phs_chars_itemChanged();
    void on_sb_curdisc_valueChanged();
    void on_sb_love_yuffie_valueChanged();
    void on_sb_love_tifa_valueChanged();
    void on_sb_love_aeris_valueChanged();
    void on_sb_love_barret_valueChanged();
    void on_sb_time_sec_valueChanged(int);
    void on_sb_time_min_valueChanged(int);
    void on_sb_time_hour_valueChanged(int);

    //items tab
    void on_list_flyers_itemChanged();
    void on_list_keyitems_itemChanged();
    void on_tbl_itm_currentCellChanged(int row);
    void on_combo_additem_currentIndexChanged(int);
    void on_sb_addqty_valueChanged(int);
    void on_clearItem_clicked();
    void on_btn_item_add_each_item_clicked();
    void on_btn_remove_all_items_clicked();

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

    //chocobo tab
    void on_sb_stables_owned_valueChanged();
    void on_sb_stables_occupied_valueChanged(int);
    void on_line_c1_name_lostFocus();
    void on_line_c2_name_lostFocus();
    void on_line_c3_name_lostFocus();
    void on_line_c4_name_lostFocus();
    void on_line_c5_name_lostFocus();
    void on_line_c6_name_lostFocus();
    void on_sb_c1_stamina_valueChanged();
    void on_sb_c2_stamina_valueChanged();
    void on_sb_c3_stamina_valueChanged();
    void on_sb_c4_stamina_valueChanged();
    void on_sb_c5_stamina_valueChanged();
    void on_sb_c6_stamina_valueChanged();
    void on_sb_c1_raceswon_valueChanged();
    void on_sb_c2_raceswon_valueChanged();
    void on_sb_c3_raceswon_valueChanged();
    void on_sb_c4_raceswon_valueChanged();
    void on_sb_c5_raceswon_valueChanged();
    void on_sb_c6_raceswon_valueChanged();
    void on_sb_c1_pcount_valueChanged();
    void on_sb_c2_pcount_valueChanged();
    void on_sb_c3_pcount_valueChanged();
    void on_sb_c4_pcount_valueChanged();
    void on_sb_c5_pcount_valueChanged();
    void on_sb_c6_pcount_valueChanged();
    void on_sb_c1_intel_valueChanged();
    void on_sb_c2_intel_valueChanged();
    void on_sb_c3_intel_valueChanged();
    void on_sb_c4_intel_valueChanged();
    void on_sb_c5_intel_valueChanged();
    void on_sb_c6_intel_valueChanged();
    void on_sb_c1_accel_valueChanged();
    void on_sb_c2_accel_valueChanged();
    void on_sb_c3_accel_valueChanged();
    void on_sb_c4_accel_valueChanged();
    void on_sb_c5_accel_valueChanged();
    void on_sb_c6_accel_valueChanged();
    void on_sb_c1_coop_valueChanged();
    void on_sb_c2_coop_valueChanged();
    void on_sb_c3_coop_valueChanged();
    void on_sb_c4_coop_valueChanged();
    void on_sb_c5_coop_valueChanged();
    void on_sb_c6_coop_valueChanged();
    void on_cb_c1_type_currentIndexChanged(int index);
    void on_cb_c2_type_currentIndexChanged(int index);
    void on_cb_c3_type_currentIndexChanged(int index);
    void on_cb_c4_type_currentIndexChanged(int index);
    void on_cb_c5_type_currentIndexChanged(int index);
    void on_cb_c6_type_currentIndexChanged(int index);
    void on_cb_c1_sex_currentIndexChanged(int index);
    void on_cb_c2_sex_currentIndexChanged(int index);
    void on_cb_c3_sex_currentIndexChanged(int index);
    void on_cb_c4_sex_currentIndexChanged(int index);
    void on_cb_c5_sex_currentIndexChanged(int index);
    void on_cb_c6_sex_currentIndexChanged(int index);
    void on_sb_c1_maxsprint_valueChanged(int);
    void on_sb_c1_sprint_valueChanged(int);
    void on_sb_c1_maxspeed_valueChanged(int);
    void on_sb_c1_speed_valueChanged(int);
    void on_sb_c2_maxsprint_valueChanged(int);
    void on_sb_c2_sprint_valueChanged(int);
    void on_sb_c2_maxspeed_valueChanged(int);
    void on_sb_c2_speed_valueChanged(int);
    void on_sb_c3_maxsprint_valueChanged(int);
    void on_sb_c3_sprint_valueChanged(int);
    void on_sb_c3_maxspeed_valueChanged(int);
    void on_sb_c3_speed_valueChanged(int);
    void on_sb_c4_maxsprint_valueChanged(int);
    void on_sb_c4_sprint_valueChanged(int);
    void on_sb_c4_maxspeed_valueChanged(int);
    void on_sb_c4_speed_valueChanged(int);
    void on_sb_c5_maxsprint_valueChanged(int);
    void on_sb_c5_sprint_valueChanged(int);
    void on_sb_c5_maxspeed_valueChanged(int);
    void on_sb_c5_speed_valueChanged(int);
    void on_sb_c6_maxsprint_valueChanged(int);
    void on_sb_c6_sprint_valueChanged(int);
    void on_sb_c6_maxspeed_valueChanged(int);
    void on_sb_c6_speed_valueChanged(int);

    //The Chocobo pens.
    void on_combo_pen1_currentIndexChanged(int index);
    void on_combo_pen2_currentIndexChanged(int index);
    void on_combo_pen3_currentIndexChanged(int index);
    void on_combo_pen4_currentIndexChanged(int index);


    // gui functions functions
    void guirefresh(void);
    void charupdate(void);
    void setarmorslots(void);
    void setweaponslots(void);
    void setchar_growth(int caller);
    void materiaupdate_slot(void);
    void materiaupdate(void);
    void itemupdate(void);
    void chocobo_refresh(void);
    void clearslot(int rmslot);
    void setmenu(void);
    void testdata_refresh(void);

    //menu actions

    //load save items
    void on_actionNew_Window_triggered();

    void on_actionOpen_Save_File_activated();
    void loadFileFull(const QString &fileName);//(Vegeta_Ss4) v0.8.3

    void on_actionImport_char_triggered();
    void on_actionFrom_PSX_Slot_activated();
    void on_actionFrom_PSV_Slot_activated();

    void on_action_Save_activated();
    void on_actionSave_File_As_activated();
    void saveFileFull(QString);//(Vegeta_Ss4) v0.8.3
    void on_actionExport_MC_triggered();
    void on_actionExport_VGS_triggered();
    void on_actionExport_DEX_triggered();
    void on_actionExport_PC_Save_activated();
    void on_actionExport_PSX_activated();
    void on_actionExport_char_triggered();

    void on_actionCopy_Slot_activated();
    void on_actionPaste_Slot_activated();
    void on_actionClear_Slot_activated();
    void on_actionNext_Slot_activated();
    void on_actionPrevious_Slot_activated();
    void on_actionShow_Selection_Dialog_activated();

    void on_actionNew_Game_triggered();
    void on_actionNew_Game_Plus_triggered();

    void on_actionAbout_activated();
    void on_actionAbout_Qt_activated();

    void on_action_auto_char_growth_triggered(bool checked);
    void on_action_show_test_data_toggled(bool checked);

    void on_action_Lang_fr_triggered();
    void on_action_Lang_es_triggered();
    void on_action_Lang_en_triggered();

    void on_action_Region_JPN_triggered(bool checked);
    void on_action_Region_JPN_International_triggered(bool checked);
    void on_action_Region_PAL_Generic_triggered(bool checked);
    void on_action_Region_PAL_German_triggered(bool checked);
    void on_action_Region_PAL_Spanish_triggered(bool checked);
    void on_action_Region_USA_triggered(bool checked);

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

    //party tab
    void on_btn_cloud_clicked();
    void on_btn_barret_clicked();
    void on_btn_tifa_clicked();
    void on_btn_aeris_clicked();
    void on_btn_red_clicked();
    void on_btn_cait_clicked();
    void on_btn_cid_clicked();
    void on_btn_yuffie_clicked();
    void on_btn_vincent_clicked();
    void on_combo_party1_currentIndexChanged(int index);
    void on_combo_party2_currentIndexChanged(int index);
    void on_combo_party3_currentIndexChanged(int index);
    void on_sb_battles_valueChanged();
    void on_sb_runs_valueChanged();
    void on_sb_gp_valueChanged();
    void on_sb_gil_valueChanged();

    //char stats
   // void on_cb_id_clicked(bool checked);
    void on_line_name_lostFocus();
    void on_sb_lvl_valueChanged();
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
    void on_sb_spr_valueChanged();
    void on_sb_sprbonus_valueChanged();
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

};
#endif // MAINWINDOW_H
