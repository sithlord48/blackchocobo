/****************************************************************************/
//    copyright 2010-2012 Chris Rizzitello <sithlord48@gmail.com>           //
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
/*~~~~~~~~~~~Includes~~~~~~~~*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

/*~~~~~~~~GUI Set Up~~~~~~~*/
MainWindow::MainWindow(QWidget *parent,FF7Save *ff7data,QSettings *configdata)
    :QMainWindow(parent),ui(new Ui::MainWindow)
{
    this->setAcceptDrops(true);
    //Get Font Info Before Setting up the GUI!
    settings =configdata;
    if(!settings->value("font-size").toString().isEmpty()){QApplication::setFont(QFont(QApplication::font().family(),settings->value("font-size").toInt(),-1,false));}
    if(!settings->value("font-family").toString().isEmpty()){QApplication::setFont(QFont(settings->value("font-family").toString(),QApplication::font().pointSize(),-1,false));}
    ui->setupUi(this);
    _init=true;
    ff7 =ff7data;
    load=true;
    curchar =0;
    mslotsel=0;
    s=0;
    buffer_materia.id=FF7Materia::EmptyId;
    for(int i=0;i<4;i++){buffer_materia.ap[i]=0xFF;} //empty buffer incase
    init_display();
    init_connections();
    init_settings();
    on_actionNew_Game_triggered();
    file_modified(false);
}
void MainWindow::init_display()
{
    //set up tables..
    ui->tbl_location_field->setColumnWidth(0,193);
    ui->tbl_location_field->setColumnWidth(1,50);
    ui->tbl_location_field->setColumnWidth(2,50);
    ui->tbl_location_field->setColumnWidth(3,50);
    ui->tbl_location_field->setColumnWidth(4,50);
    ui->tbl_location_field->setColumnWidth(5,50);


    QTableWidgetItem *newItem;
    FF7Location Locations;
    ui->tbl_location_field->setRowCount(Locations.len());
    for (int i=0;i<ui->tbl_location_field->rowCount();i++)
    {
        newItem = new QTableWidgetItem(Locations.loc_name(i),0);
        ui->tbl_location_field->setItem(i,0,newItem);
        newItem = new QTableWidgetItem(Locations.map_id(i),0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tbl_location_field->setItem(i,1,newItem);
        newItem = new QTableWidgetItem(Locations.loc_id(i),0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tbl_location_field->setItem(i,2,newItem);
        newItem = new QTableWidgetItem(Locations.x(i),0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tbl_location_field->setItem(i,3,newItem);
        newItem = new QTableWidgetItem(Locations.y(i),0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tbl_location_field->setItem(i,4,newItem);
        newItem = new QTableWidgetItem(Locations.z(i),0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tbl_location_field->setItem(i,5,newItem);
    }

    //Hide the stuff that needs to be hidden.
    ui->compare_table->setEnabled(false);
    ui->tbl_diff->setVisible(0);
    ui->bm_unknown->setVisible(0);
    ui->bh_id->setVisible(0);
    ui->leader_id->setVisible(false);

    //chocobo boxes
    ui->box_stable1->setEnabled(false);
    ui->box_stable2->setEnabled(false);
    ui->box_stable3->setEnabled(false);
    ui->box_stable4->setEnabled(false);
    ui->box_stable5->setEnabled(false);
    ui->box_stable6->setEnabled(false);
    //testing stuff.

    ui->tabWidget->setTabEnabled(8,0);
    ui->cb_Region_Slot->setEnabled(false);
    ui->group_controller_mapping->setVisible(false);
    ui->actionNew_Window->setVisible(0);

    // Temp hidden (show only via debug)
    ui->cb_farm_items_1->setVisible(false);
    ui->cb_farm_items_2->setVisible(false);
    ui->cb_farm_items_3->setVisible(false);
    ui->cb_farm_items_4->setVisible(false);
    ui->cb_farm_items_5->setVisible(false);
    ui->cb_farm_items_6->setVisible(false);
    ui->cb_farm_items_7->setVisible(false);
    ui->cb_farm_items_8->setVisible(false);
    load=false;

    ui->lbl_love_barret->setPixmap(Chars.Pixmap(FF7Char::Barret));
    ui->lbl_love_tifa->setPixmap(Chars.Pixmap(FF7Char::Tifa));
    ui->lbl_love_aeris->setPixmap(Chars.Pixmap(FF7Char::Aerith));
    ui->lbl_love_yuffie->setPixmap(Chars.Pixmap(FF7Char::Yuffie));

    ui->lbl_battle_love_barret->setPixmap(Chars.Pixmap(FF7Char::Barret));
    ui->lbl_battle_love_tifa->setPixmap(Chars.Pixmap(FF7Char::Tifa));
    ui->lbl_battle_love_aeris->setPixmap(Chars.Pixmap(FF7Char::Aerith));
    ui->lbl_battle_love_yuffie->setPixmap(Chars.Pixmap(FF7Char::Yuffie));

    for(int i=0;i<11;i++){ui->combo_party1->addItem(Chars.Icon(i),Chars.defaultName(i));}
    for(int i=0;i<11;i++){ui->combo_party2->addItem(Chars.Icon(i),Chars.defaultName(i));}
    for(int i=0;i<11;i++){ui->combo_party3->addItem(Chars.Icon(i),Chars.defaultName(i));}
    ui->combo_party1->addItem(Chars.Icon(0x0B),QString("0x0B"));
    ui->combo_party1->addItem(Chars.Icon(0xFF),tr("-Empty-"));
    ui->combo_party2->addItem(Chars.Icon(0x0B),QString("0x0B"));
    ui->combo_party2->addItem(Chars.Icon(0xFF),tr("-Empty-"));
    ui->combo_party3->addItem(Chars.Icon(0x0B),QString("0x0B"));
    ui->combo_party3->addItem(Chars.Icon(0xFF),tr("-Empty-"));

    ui->cb_world_party_leader->addItem(Chars.Icon(FF7Char::Cloud),Chars.defaultName(FF7Char::Cloud));
    ui->cb_world_party_leader->addItem(Chars.Icon(FF7Char::Tifa),Chars.defaultName(FF7Char::Tifa));
    ui->cb_world_party_leader->addItem(Chars.Icon(FF7Char::Cid),Chars.defaultName(FF7Char::Cid));


    dialog_preview = new DialogPreview();
    QHBoxLayout *dialog_preview_layout = new QHBoxLayout();
    dialog_preview_layout->setContentsMargins(0,0,0,0);
    dialog_preview_layout->addWidget(dialog_preview);
    ui->dialog_preview_box->setLayout(dialog_preview_layout);
    ui->dialog_preview_box->setContentsMargins(0,0,0,0);

    materia_editor = new MateriaEditor;
    materia_editor->setStarsSize(48);
    QVBoxLayout *materia_editor_layout = new QVBoxLayout();
    mat_spacer = new QSpacerItem(0,0,QSizePolicy::Preferred,QSizePolicy::MinimumExpanding);
    materia_editor_layout->setContentsMargins(0,0,0,0);
    materia_editor_layout->setSpacing(0);
    materia_editor_layout->addWidget(materia_editor);
    materia_editor_layout->addSpacerItem(mat_spacer);
    ui->group_materia->setLayout(materia_editor_layout);
    ui->group_materia->setContentsMargins(0,0,0,0);

    char_editor = new CharEditor;
    QHBoxLayout *char_editor_layout = new QHBoxLayout;
    char_editor_layout->setSpacing(0);
    char_editor_layout->setContentsMargins(0,0,0,0);
    char_editor_layout->addWidget(char_editor);
    ui->group_char_editor_box->setLayout(char_editor_layout);

    char_editor->Slider_Limit_FF7_Style();//sets style to ff7 limit bar style
    char_editor->setToolBoxStyle(QString("::tab:hover{background-color:qlineargradient(spread:pad, x1:0.5, y1:0.00568182, x2:0.497, y2:1, stop:0 rgba(67, 67, 67, 128), stop:0.5 rgba(34, 201, 247, 128), stop:1 rgba(67, 67, 67, 128));}"));

    itemlist= new ItemList;
    QHBoxLayout *itemlist_layout = new QHBoxLayout;
    itemlist_layout->setSpacing(0);
    itemlist_layout->setContentsMargins(0,0,0,0);
    itemlist_layout->addWidget(itemlist);
    ui->frm_itemlist->setLayout(itemlist_layout);
    ui->frm_itemlist->adjustSize();

    chocobo_stable_1 = new ChocoboEditor;
    QVBoxLayout *stable_1_layout = new QVBoxLayout;
    stable_1_layout->setContentsMargins(0,0,0,0);
    stable_1_layout->addWidget(chocobo_stable_1);
    ui->box_stable1->setLayout(stable_1_layout);

    chocobo_stable_2 = new ChocoboEditor;
    QVBoxLayout *stable_2_layout = new QVBoxLayout;
    stable_2_layout->setContentsMargins(0,0,0,0);
    stable_2_layout->addWidget(chocobo_stable_2);
    ui->box_stable2->setLayout(stable_2_layout);

    chocobo_stable_3 = new ChocoboEditor;
    QVBoxLayout *stable_3_layout = new QVBoxLayout;
    stable_3_layout->setContentsMargins(0,0,0,0);
    stable_3_layout->addWidget(chocobo_stable_3);
    ui->box_stable3->setLayout(stable_3_layout);

    chocobo_stable_4 = new ChocoboEditor;
    QVBoxLayout *stable_4_layout = new QVBoxLayout;
    stable_4_layout->setContentsMargins(0,0,0,0);
    stable_4_layout->addWidget(chocobo_stable_4);
    ui->box_stable4->setLayout(stable_4_layout);

    chocobo_stable_5 = new ChocoboEditor;
    QVBoxLayout *stable_5_layout = new QVBoxLayout;
    stable_5_layout->setContentsMargins(0,0,0,0);
    stable_5_layout->addWidget(chocobo_stable_5);
    ui->box_stable5->setLayout(stable_5_layout);

    chocobo_stable_6 = new ChocoboEditor;
    QVBoxLayout *stable_6_layout = new QVBoxLayout;
    stable_6_layout->setContentsMargins(0,0,0,0);
    stable_6_layout->addWidget(chocobo_stable_6);
    ui->box_stable6->setLayout(stable_6_layout);
}
void MainWindow::init_connections()
{//check Qt Version and Connect With Apporate Method.
    if(QT_VERSION<0x050000)
    {//QT 4 Style Connect Statements
        // Connect the unknown and unknown compare scrolling.
        connect( ui->tbl_unknown->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->tbl_compare_unknown->verticalScrollBar(), SLOT(setValue(int)) );
        connect( ui->tbl_compare_unknown->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->tbl_unknown->verticalScrollBar(), SLOT(setValue(int)) );
        //connnect the dialogpreview to the data functions.
        connect(dialog_preview,SIGNAL(UL_ColorChanged(QColor)),this,SLOT(set_UL_Color(QColor)));
        connect(dialog_preview,SIGNAL(UR_ColorChanged(QColor)),this,SLOT(set_UR_Color(QColor)));
        connect(dialog_preview,SIGNAL(LL_ColorChanged(QColor)),this,SLOT(set_LL_Color(QColor)));
        connect(dialog_preview,SIGNAL(LR_ColorChanged(QColor)),this,SLOT(set_LR_Color(QColor)));
        //ItemList
        connect(itemlist,SIGNAL(itemsChanged(QList<quint16>)),this,SLOT(Items_Changed(QList<quint16>)));
        //Materia_Editor
        connect(materia_editor,SIGNAL(ap_changed(qint32)),this,SLOT(materia_ap_changed(qint32)));
        connect(materia_editor,SIGNAL(id_changed(qint8)),this,SLOT(materia_id_changed(qint8)));
        //Char_Editor
        connect(ui->action_show_debug,SIGNAL(toggled(bool)),char_editor,(SLOT(setDebug(bool))));
        connect(char_editor,SIGNAL(id_changed(qint8)),this,SLOT(char_id_changed(qint8)));
        connect(char_editor,SIGNAL(level_changed(qint8)),this,SLOT(char_level_changed(qint8)));
        connect(char_editor,SIGNAL(str_changed(quint8)),this,SLOT(char_str_changed(quint8)));
        connect(char_editor,SIGNAL(vit_changed(quint8)),this,SLOT(char_vit_changed(quint8)));
        connect(char_editor,SIGNAL(mag_changed(quint8)),this,SLOT(char_mag_changed(quint8)));
        connect(char_editor,SIGNAL(spi_changed(quint8)),this,SLOT(char_spi_changed(quint8)));
        connect(char_editor,SIGNAL(dex_changed(quint8)),this,SLOT(char_dex_changed(quint8)));
        connect(char_editor,SIGNAL(lck_changed(quint8)),this,SLOT(char_lck_changed(quint8)));
        connect(char_editor,SIGNAL(strBonus_changed(quint8)),this,SLOT(char_strBonus_changed(quint8)));
        connect(char_editor,SIGNAL(vitBonus_changed(quint8)),this,SLOT(char_vitBonus_changed(quint8)));
        connect(char_editor,SIGNAL(magBonus_changed(quint8)),this,SLOT(char_magBonus_changed(quint8)));
        connect(char_editor,SIGNAL(spiBonus_changed(quint8)),this,SLOT(char_spiBonus_changed(quint8)));
        connect(char_editor,SIGNAL(dexBonus_changed(quint8)),this,SLOT(char_dexBonus_changed(quint8)));
        connect(char_editor,SIGNAL(lckBonus_changed(quint8)),this,SLOT(char_lckBonus_changed(quint8)));
        connect(char_editor,SIGNAL(limitLevel_changed(qint8)),this,SLOT(char_limitLevel_changed(qint8)));
        connect(char_editor,SIGNAL(limitBar_changed(quint8)),this,SLOT(char_limitBar_changed(quint8)));
        connect(char_editor,SIGNAL(name_changed(QString)),this,SLOT(char_name_changed(QString)));
        connect(char_editor,SIGNAL(weapon_changed(quint8)),this,SLOT(char_weapon_changed(quint8)));
        connect(char_editor,SIGNAL(armor_changed(quint8)),this,SLOT(char_armor_changed(quint8)));
        connect(char_editor,SIGNAL(accessory_changed(quint8)),this,SLOT(char_accessory_changed(quint8)));
        connect(char_editor,SIGNAL(curHp_changed(quint16)),this,SLOT(char_curHp_changed(quint16)));
        connect(char_editor,SIGNAL(maxHp_changed(quint16)),this,SLOT(char_maxHp_changed(quint16)));
        connect(char_editor,SIGNAL(curMp_changed(quint16)),this,SLOT(char_curMp_changed(quint16)));
        connect(char_editor,SIGNAL(maxMp_changed(quint16)),this,SLOT(char_maxMp_changed(quint16)));
        connect(char_editor,SIGNAL(kills_changed(quint16)),this,SLOT(char_kills_changed(quint16)));
        connect(char_editor,SIGNAL(row_changed(quint8)),this,SLOT(char_row_changed(quint8)));
        connect(char_editor,SIGNAL(levelProgress_changed(quint8)),this,SLOT(char_levelProgress_changed(quint8)));
        connect(char_editor,SIGNAL(sadnessfury_changed(quint8)),this,SLOT(char_sadnessfury_changed(quint8)));
        connect(char_editor,SIGNAL(limits_changed(quint16)),this,SLOT(char_limits_changed(quint16)));
        connect(char_editor,SIGNAL(timesused1_changed(quint16)),this,SLOT(char_timesused1_changed(quint16)));
        connect(char_editor,SIGNAL(timesused2_changed(quint16)),this,SLOT(char_timeused2_changed(quint16)));
        connect(char_editor,SIGNAL(timesused3_changed(quint16)),this,SLOT(char_timeused3_changed(quint16)));
        connect(char_editor,SIGNAL(baseHp_changed(quint16)),this,SLOT(char_baseHp_changed(quint16)));
        connect(char_editor,SIGNAL(baseMp_changed(quint16)),this,SLOT(char_baseMp_changed(quint16)));
        connect(char_editor,SIGNAL(exp_changed(quint32)),this,SLOT(char_exp_changed(quint32)));
        connect(char_editor,SIGNAL(mslotChanged(int)),this,SLOT(char_mslot_changed(int)));
        connect(char_editor,SIGNAL(Materias_changed(materia)),this,SLOT(char_materia_changed(materia)));
        connect(char_editor,SIGNAL(expNext_changed(quint32)),this,SLOT(char_expNext_changed(quint32)));
        //Chocobo Editor 1
        connect(chocobo_stable_1,SIGNAL(name_changed(QString)),this,SLOT(c1_nameChanged(QString)));
        connect(chocobo_stable_1,SIGNAL(cantMate_changed(bool)),this,SLOT(c1_mated_toggled(bool)));
        connect(chocobo_stable_1,SIGNAL(speed_changed(quint16)),this,SLOT(c1_speedChanged(quint16)));
        connect(chocobo_stable_1,SIGNAL(mSpeed_changed(quint16)),this,SLOT(c1_maxspeedChanged(quint16)));
        connect(chocobo_stable_1,SIGNAL(sprint_changed(quint16)),this,SLOT(c1_sprintChanged(quint16)));
        connect(chocobo_stable_1,SIGNAL(mSprint_changed(quint16)),this,SLOT(c1_maxsprintChanged(quint16)));
        connect(chocobo_stable_1,SIGNAL(stamina_changed(quint16)),this,SLOT(c1_staminaChanged(quint16)));
        connect(chocobo_stable_1,SIGNAL(sex_changed(quint8)),this,SLOT(c1_sexChanged(quint8)));
        connect(chocobo_stable_1,SIGNAL(type_changed(quint8)),this,SLOT(c1_typeChanged(quint8)));
        connect(chocobo_stable_1,SIGNAL(accel_changed(quint8)),this,SLOT(c1_accelChanged(quint8)));
        connect(chocobo_stable_1,SIGNAL(coop_changed(quint8)),this,SLOT(c1_coopChanged(quint8)));
        connect(chocobo_stable_1,SIGNAL(intelligence_changed(quint8)),this,SLOT(c1_intelChanged(quint8)));
        connect(chocobo_stable_1,SIGNAL(personality_changed(quint8)),this,SLOT(c1_personalityChanged(quint8)));
        connect(chocobo_stable_1,SIGNAL(pCount_changed(quint8)),this,SLOT(c1_pcountChanged(quint8)));
        connect(chocobo_stable_1,SIGNAL(wins_changed(quint8)),this,SLOT(c1_raceswonChanged(quint8)));
        //Chocobo Editor 2
        connect(chocobo_stable_2,SIGNAL(name_changed(QString)),this,SLOT(c2_nameChanged(QString)));
        connect(chocobo_stable_2,SIGNAL(cantMate_changed(bool)),this,SLOT(c2_mated_toggled(bool)));
        connect(chocobo_stable_2,SIGNAL(speed_changed(quint16)),this,SLOT(c2_speedChanged(quint16)));
        connect(chocobo_stable_2,SIGNAL(mSpeed_changed(quint16)),this,SLOT(c2_maxspeedChanged(quint16)));
        connect(chocobo_stable_2,SIGNAL(sprint_changed(quint16)),this,SLOT(c2_sprintChanged(quint16)));
        connect(chocobo_stable_2,SIGNAL(mSprint_changed(quint16)),this,SLOT(c2_maxsprintChanged(quint16)));
        connect(chocobo_stable_2,SIGNAL(stamina_changed(quint16)),this,SLOT(c2_staminaChanged(quint16)));
        connect(chocobo_stable_2,SIGNAL(sex_changed(quint8)),this,SLOT(c2_sexChanged(quint8)));
        connect(chocobo_stable_2,SIGNAL(type_changed(quint8)),this,SLOT(c2_typeChanged(quint8)));
        connect(chocobo_stable_2,SIGNAL(accel_changed(quint8)),this,SLOT(c2_accelChanged(quint8)));
        connect(chocobo_stable_2,SIGNAL(coop_changed(quint8)),this,SLOT(c2_coopChanged(quint8)));
        connect(chocobo_stable_2,SIGNAL(intelligence_changed(quint8)),this,SLOT(c2_intelChanged(quint8)));
        connect(chocobo_stable_2,SIGNAL(personality_changed(quint8)),this,SLOT(c2_personalityChanged(quint8)));
        connect(chocobo_stable_2,SIGNAL(pCount_changed(quint8)),this,SLOT(c2_pcountChanged(quint8)));
        connect(chocobo_stable_2,SIGNAL(wins_changed(quint8)),this,SLOT(c2_raceswonChanged(quint8)));
        //Chocobo Editor 3
        connect(chocobo_stable_3,SIGNAL(name_changed(QString)),this,SLOT(c3_nameChanged(QString)));
        connect(chocobo_stable_3,SIGNAL(cantMate_changed(bool)),this,SLOT(c3_mated_toggled(bool)));
        connect(chocobo_stable_3,SIGNAL(speed_changed(quint16)),this,SLOT(c3_speedChanged(quint16)));
        connect(chocobo_stable_3,SIGNAL(mSpeed_changed(quint16)),this,SLOT(c3_maxspeedChanged(quint16)));
        connect(chocobo_stable_3,SIGNAL(sprint_changed(quint16)),this,SLOT(c3_sprintChanged(quint16)));
        connect(chocobo_stable_3,SIGNAL(mSprint_changed(quint16)),this,SLOT(c3_maxsprintChanged(quint16)));
        connect(chocobo_stable_3,SIGNAL(stamina_changed(quint16)),this,SLOT(c3_staminaChanged(quint16)));
        connect(chocobo_stable_3,SIGNAL(sex_changed(quint8)),this,SLOT(c3_sexChanged(quint8)));
        connect(chocobo_stable_3,SIGNAL(type_changed(quint8)),this,SLOT(c3_typeChanged(quint8)));
        connect(chocobo_stable_3,SIGNAL(accel_changed(quint8)),this,SLOT(c3_accelChanged(quint8)));
        connect(chocobo_stable_3,SIGNAL(coop_changed(quint8)),this,SLOT(c3_coopChanged(quint8)));
        connect(chocobo_stable_3,SIGNAL(intelligence_changed(quint8)),this,SLOT(c3_intelChanged(quint8)));
        connect(chocobo_stable_3,SIGNAL(personality_changed(quint8)),this,SLOT(c3_personalityChanged(quint8)));
        connect(chocobo_stable_3,SIGNAL(pCount_changed(quint8)),this,SLOT(c3_pcountChanged(quint8)));
        connect(chocobo_stable_3,SIGNAL(wins_changed(quint8)),this,SLOT(c3_raceswonChanged(quint8)));
        //Chocobo Editor 4
        connect(chocobo_stable_4,SIGNAL(name_changed(QString)),this,SLOT(c4_nameChanged(QString)));
        connect(chocobo_stable_4,SIGNAL(cantMate_changed(bool)),this,SLOT(c4_mated_toggled(bool)));
        connect(chocobo_stable_4,SIGNAL(speed_changed(quint16)),this,SLOT(c4_speedChanged(quint16)));
        connect(chocobo_stable_4,SIGNAL(mSpeed_changed(quint16)),this,SLOT(c4_maxspeedChanged(quint16)));
        connect(chocobo_stable_4,SIGNAL(sprint_changed(quint16)),this,SLOT(c4_sprintChanged(quint16)));
        connect(chocobo_stable_4,SIGNAL(mSprint_changed(quint16)),this,SLOT(c4_maxsprintChanged(quint16)));
        connect(chocobo_stable_4,SIGNAL(stamina_changed(quint16)),this,SLOT(c4_staminaChanged(quint16)));
        connect(chocobo_stable_4,SIGNAL(sex_changed(quint8)),this,SLOT(c4_sexChanged(quint8)));
        connect(chocobo_stable_4,SIGNAL(type_changed(quint8)),this,SLOT(c4_typeChanged(quint8)));
        connect(chocobo_stable_4,SIGNAL(accel_changed(quint8)),this,SLOT(c4_accelChanged(quint8)));
        connect(chocobo_stable_4,SIGNAL(coop_changed(quint8)),this,SLOT(c4_coopChanged(quint8)));
        connect(chocobo_stable_4,SIGNAL(intelligence_changed(quint8)),this,SLOT(c4_intelChanged(quint8)));
        connect(chocobo_stable_4,SIGNAL(personality_changed(quint8)),this,SLOT(c4_personalityChanged(quint8)));
        connect(chocobo_stable_4,SIGNAL(pCount_changed(quint8)),this,SLOT(c4_pcountChanged(quint8)));
        connect(chocobo_stable_4,SIGNAL(wins_changed(quint8)),this,SLOT(c4_raceswonChanged(quint8)));
        //Chocobo Editor 5
        connect(chocobo_stable_5,SIGNAL(name_changed(QString)),this,SLOT(c5_nameChanged(QString)));
        connect(chocobo_stable_5,SIGNAL(cantMate_changed(bool)),this,SLOT(c5_mated_toggled(bool)));
        connect(chocobo_stable_5,SIGNAL(speed_changed(quint16)),this,SLOT(c5_speedChanged(quint16)));
        connect(chocobo_stable_5,SIGNAL(mSpeed_changed(quint16)),this,SLOT(c5_maxspeedChanged(quint16)));
        connect(chocobo_stable_5,SIGNAL(sprint_changed(quint16)),this,SLOT(c5_sprintChanged(quint16)));
        connect(chocobo_stable_5,SIGNAL(mSprint_changed(quint16)),this,SLOT(c5_maxsprintChanged(quint16)));
        connect(chocobo_stable_5,SIGNAL(stamina_changed(quint16)),this,SLOT(c5_staminaChanged(quint16)));
        connect(chocobo_stable_5,SIGNAL(sex_changed(quint8)),this,SLOT(c5_sexChanged(quint8)));
        connect(chocobo_stable_5,SIGNAL(type_changed(quint8)),this,SLOT(c5_typeChanged(quint8)));
        connect(chocobo_stable_5,SIGNAL(accel_changed(quint8)),this,SLOT(c5_accelChanged(quint8)));
        connect(chocobo_stable_5,SIGNAL(coop_changed(quint8)),this,SLOT(c5_coopChanged(quint8)));
        connect(chocobo_stable_5,SIGNAL(intelligence_changed(quint8)),this,SLOT(c5_intelChanged(quint8)));
        connect(chocobo_stable_5,SIGNAL(personality_changed(quint8)),this,SLOT(c5_personalityChanged(quint8)));
        connect(chocobo_stable_5,SIGNAL(pCount_changed(quint8)),this,SLOT(c5_pcountChanged(quint8)));
        connect(chocobo_stable_5,SIGNAL(wins_changed(quint8)),this,SLOT(c5_raceswonChanged(quint8)));
        //Chocobo Editor 6
        connect(chocobo_stable_6,SIGNAL(name_changed(QString)),this,SLOT(c6_nameChanged(QString)));
        connect(chocobo_stable_6,SIGNAL(cantMate_changed(bool)),this,SLOT(c6_mated_toggled(bool)));
        connect(chocobo_stable_6,SIGNAL(speed_changed(quint16)),this,SLOT(c6_speedChanged(quint16)));
        connect(chocobo_stable_6,SIGNAL(mSpeed_changed(quint16)),this,SLOT(c6_maxspeedChanged(quint16)));
        connect(chocobo_stable_6,SIGNAL(sprint_changed(quint16)),this,SLOT(c6_sprintChanged(quint16)));
        connect(chocobo_stable_6,SIGNAL(mSprint_changed(quint16)),this,SLOT(c6_maxsprintChanged(quint16)));
        connect(chocobo_stable_6,SIGNAL(stamina_changed(quint16)),this,SLOT(c6_staminaChanged(quint16)));
        connect(chocobo_stable_6,SIGNAL(sex_changed(quint8)),this,SLOT(c6_sexChanged(quint8)));
        connect(chocobo_stable_6,SIGNAL(type_changed(quint8)),this,SLOT(c6_typeChanged(quint8)));
        connect(chocobo_stable_6,SIGNAL(accel_changed(quint8)),this,SLOT(c6_accelChanged(quint8)));
        connect(chocobo_stable_6,SIGNAL(coop_changed(quint8)),this,SLOT(c6_coopChanged(quint8)));
        connect(chocobo_stable_6,SIGNAL(intelligence_changed(quint8)),this,SLOT(c6_intelChanged(quint8)));
        connect(chocobo_stable_6,SIGNAL(personality_changed(quint8)),this,SLOT(c6_personalityChanged(quint8)));
        connect(chocobo_stable_6,SIGNAL(pCount_changed(quint8)),this,SLOT(c6_pcountChanged(quint8)));
        connect(chocobo_stable_6,SIGNAL(wins_changed(quint8)),this,SLOT(c6_raceswonChanged(quint8)));
    }
    else
    {//Qt 5 Style connect Statements
        /*
        //Lock Tables on Test Data Tab Same Scroll Pos.
        connect( ui->tbl_unknown->verticalScrollBar(), SIGNAL(valueChanged(int), ui->tbl_compare_unknown->verticalScrollBar(), SLOT(setValue(int)) );
        connect( ui->tbl_compare_unknown->verticalScrollBar(), SIGNAL(valueChanged(int), ui->tbl_unknown->verticalScrollBar(), SLOT(setValue(int)) );
        //connnect the dialogpreview to the data functions.
        connect(dialog_preview::UL_ColorChanged(QColor),this::set_UL_Color(QColor));
        connect(dialog_preview::UR_ColorChanged(QColor),this::set_UR_Color(QColor));
        connect(dialog_preview::LL_ColorChanged(QColor),this::set_LL_Color(QColor));
        connect(dialog_preview::LR_ColorChanged(QColor),this::set_LR_Color(QColor));
        //ItemList
        connect(itemlist::itemsChanged(QList<quint16>),this::Items_Changed(QList<quint16>));
        //Materia_Editor
        connect(materia_editor::ap_changed(qint32),this::materia_ap_changed(qint32));
        connect(materia_editor::id_changed(qint8),this::materia_id_changed(qint8));
        //Char_Editor
        connect(ui->action_show_debug::toggled(bool),char_editor,(SLOT(setDebug(bool)));
        connect(char_editor::id_changed(qint8),this::char_id_changed(qint8));
        connect(char_editor::level_changed(qint8),this::char_level_changed(qint8));
        connect(char_editor::str_changed(quint8),this::char_str_changed(quint8));
        connect(char_editor::vit_changed(quint8),this::char_vit_changed(quint8));
        connect(char_editor::mag_changed(quint8),this::char_mag_changed(quint8));
        connect(char_editor::spi_changed(quint8),this::char_spi_changed(quint8));
        connect(char_editor::dex_changed(quint8),this::char_dex_changed(quint8));
        connect(char_editor::lck_changed(quint8),this::char_lck_changed(quint8));
        connect(char_editor::strBonus_changed(quint8),this::char_strBonus_changed(quint8));
        connect(char_editor::vitBonus_changed(quint8),this::char_vitBonus_changed(quint8));
        connect(char_editor::magBonus_changed(quint8),this::char_magBonus_changed(quint8));
        connect(char_editor::spiBonus_changed(quint8),this::char_spiBonus_changed(quint8));
        connect(char_editor::dexBonus_changed(quint8),this::char_dexBonus_changed(quint8));
        connect(char_editor::lckBonus_changed(quint8),this::char_lckBonus_changed(quint8));
        connect(char_editor::limitLevel_changed(qint8),this::char_limitLevel_changed(qint8));
        connect(char_editor::limitBar_changed(quint8),this::char_limitBar_changed(quint8));
        connect(char_editor::name_changed(QString),this::char_name_changed(QString));
        connect(char_editor::weapon_changed(quint8),this::char_weapon_changed(quint8));
        connect(char_editor::armor_changed(quint8),this::char_armor_changed(quint8));
        connect(char_editor::accessory_changed(quint8),this::char_accessory_changed(quint8));
        connect(char_editor::curHp_changed(quint16),this::char_curHp_changed(quint16));
        connect(char_editor::maxHp_changed(quint16),this::char_maxHp_changed(quint16));
        connect(char_editor::curMp_changed(quint16),this::char_curMp_changed(quint16));
        connect(char_editor::maxMp_changed(quint16),this::char_maxMp_changed(quint16));
        connect(char_editor::kills_changed(quint16),this::char_kills_changed(quint16));
        connect(char_editor::row_changed(quint8),this::char_row_changed(quint8));
        connect(char_editor::levelProgress_changed(quint8),this::char_levelProgress_changed(quint8));
        connect(char_editor::sadnessfury_changed(quint8),this::char_sadnessfury_changed(quint8));
        connect(char_editor::limits_changed(quint16),this::char_limits_changed(quint16));
        connect(char_editor::timesused1_changed(quint16),this::char_timesused1_changed(quint16));
        connect(char_editor::timesused2_changed(quint16),this::char_timeused2_changed(quint16));
        connect(char_editor::timesused3_changed(quint16),this::char_timeused3_changed(quint16));
        connect(char_editor::baseHp_changed(quint16),this::char_baseHp_changed(quint16));
        connect(char_editor::baseMp_changed(quint16),this::char_baseMp_changed(quint16));
        connect(char_editor::exp_changed(quint32),this::char_exp_changed(quint32));
        connect(char_editor::mslotChanged(int),this::char_mslot_changed(int));
        connect(char_editor::Materias_changed(materia),this::char_materia_changed(materia));
        connect(char_editor::expNext_changed(quint32),this::char_expNext_changed(quint32;
        //Chocobo Editor 1
        connect(chocobo_stable_1::name_changed(QString),this::c1_nameChanged(QString));
        connect(chocobo_stable_1::cantMate_changed(bool),this::c1_mated_toggled(bool));
        connect(chocobo_stable_1::speed_changed(quint16),this::c1_speedChanged(quint16));
        connect(chocobo_stable_1::mSpeed_changed(quint16),this::c1_maxspeedChanged(quint16));
        connect(chocobo_stable_1::sprint_changed(quint16),this::c1_sprintChanged(quint16));
        connect(chocobo_stable_1::mSprint_changed(quint16),this::c1_maxsprintChanged(quint16));
        connect(chocobo_stable_1::stamina_changed(quint16),this::c1_staminaChanged(quint16));
        connect(chocobo_stable_1::sex_changed(quint8),this::c1_sexChanged(quint8));
        connect(chocobo_stable_1::type_changed(quint8),this::c1_typeChanged(quint8));
        connect(chocobo_stable_1::accel_changed(quint8),this::c1_accelChanged(quint8));
        connect(chocobo_stable_1::coop_changed(quint8),this::c1_coopChanged(quint8));
        connect(chocobo_stable_1::intelligence_changed(quint8),this::c1_intelChanged(quint8));
        connect(chocobo_stable_1::personality_changed(quint8),this::c1_personalityChanged(quint8));
        connect(chocobo_stable_1::pCount_changed(quint8),this::c1_pcountChanged(quint8));
        connect(chocobo_stable_1::wins_changed(quint8),this::c1_raceswonChanged(quint8));
        //Chocobo Editor 2
        connect(chocobo_stable_2::name_changed(QString),this::c2_nameChanged(QString));
        connect(chocobo_stable_2::cantMate_changed(bool),this::c2_mated_toggled(bool));
        connect(chocobo_stable_2::speed_changed(quint16),this::c2_speedChanged(quint16));
        connect(chocobo_stable_2::mSpeed_changed(quint16),this::c2_maxspeedChanged(quint16));
        connect(chocobo_stable_2::sprint_changed(quint16),this::c2_sprintChanged(quint16));
        connect(chocobo_stable_2::mSprint_changed(quint16),this::c2_maxsprintChanged(quint16));
        connect(chocobo_stable_2::stamina_changed(quint16),this::c2_staminaChanged(quint16));
        connect(chocobo_stable_2::sex_changed(quint8),this::c2_sexChanged(quint8));
        connect(chocobo_stable_2::type_changed(quint8),this::c2_typeChanged(quint8));
        connect(chocobo_stable_2::accel_changed(quint8),this::c2_accelChanged(quint8));
        connect(chocobo_stable_2::coop_changed(quint8),this::c2_coopChanged(quint8));
        connect(chocobo_stable_2::intelligence_changed(quint8),this::c2_intelChanged(quint8));
        connect(chocobo_stable_2::personality_changed(quint8),this::c2_personalityChanged(quint8));
        connect(chocobo_stable_2::pCount_changed(quint8),this::c2_pcountChanged(quint8));
        connect(chocobo_stable_2::wins_changed(quint8),this::c2_raceswonChanged(quint8));
        //Chocobo Editor 3
        connect(chocobo_stable_3::name_changed(QString),this::c3_nameChanged(QString));
        connect(chocobo_stable_3::cantMate_changed(bool),this::c3_mated_toggled(bool));
        connect(chocobo_stable_3::speed_changed(quint16),this::c3_speedChanged(quint16));
        connect(chocobo_stable_3::mSpeed_changed(quint16),this::c3_maxspeedChanged(quint16));
        connect(chocobo_stable_3::sprint_changed(quint16),this::c3_sprintChanged(quint16));
        connect(chocobo_stable_3::mSprint_changed(quint16),this::c3_maxsprintChanged(quint16));
        connect(chocobo_stable_3::stamina_changed(quint16),this::c3_staminaChanged(quint16));
        connect(chocobo_stable_3::sex_changed(quint8),this::c3_sexChanged(quint8));
        connect(chocobo_stable_3::type_changed(quint8),this::c3_typeChanged(quint8));
        connect(chocobo_stable_3::accel_changed(quint8),this::c3_accelChanged(quint8));
        connect(chocobo_stable_3::coop_changed(quint8),this::c3_coopChanged(quint8));
        connect(chocobo_stable_3::intelligence_changed(quint8),this::c3_intelChanged(quint8));
        connect(chocobo_stable_3::personality_changed(quint8),this::c3_personalityChanged(quint8));
        connect(chocobo_stable_3::pCount_changed(quint8),this::c3_pcountChanged(quint8));
        connect(chocobo_stable_3::wins_changed(quint8),this::c3_raceswonChanged(quint8));
        //Chocobo Editor 4
        connect(chocobo_stable_4::name_changed(QString),this::c4_nameChanged(QString));
        connect(chocobo_stable_4::cantMate_changed(bool),this::c4_mated_toggled(bool));
        connect(chocobo_stable_4::speed_changed(quint16),this::c4_speedChanged(quint16));
        connect(chocobo_stable_4::mSpeed_changed(quint16),this::c4_maxspeedChanged(quint16));
        connect(chocobo_stable_4::sprint_changed(quint16),this::c4_sprintChanged(quint16));
        connect(chocobo_stable_4::mSprint_changed(quint16),this::c4_maxsprintChanged(quint16));
        connect(chocobo_stable_4::stamina_changed(quint16),this::c4_staminaChanged(quint16));
        connect(chocobo_stable_4::sex_changed(quint8),this::c4_sexChanged(quint8));
        connect(chocobo_stable_4::type_changed(quint8),this::c4_typeChanged(quint8));
        connect(chocobo_stable_4::accel_changed(quint8),this::c4_accelChanged(quint8));
        connect(chocobo_stable_4::coop_changed(quint8),this::c4_coopChanged(quint8));
        connect(chocobo_stable_4::intelligence_changed(quint8),this::c4_intelChanged(quint8));
        connect(chocobo_stable_4::personality_changed(quint8),this::c4_personalityChanged(quint8));
        connect(chocobo_stable_4::pCount_changed(quint8),this::c4_pcountChanged(quint8));
        connect(chocobo_stable_4::wins_changed(quint8),this::c4_raceswonChanged(quint8));
        //Chocobo Editor 5
        connect(chocobo_stable_5::name_changed(QString),this::c5_nameChanged(QString));
        connect(chocobo_stable_5::cantMate_changed(bool),this::c5_mated_toggled(bool));
        connect(chocobo_stable_5::speed_changed(quint16),this::c5_speedChanged(quint16));
        connect(chocobo_stable_5::mSpeed_changed(quint16),this::c5_maxspeedChanged(quint16));
        connect(chocobo_stable_5::sprint_changed(quint16),this::c5_sprintChanged(quint16));
        connect(chocobo_stable_5::mSprint_changed(quint16),this::c5_maxsprintChanged(quint16));
        connect(chocobo_stable_5::stamina_changed(quint16),this::c5_staminaChanged(quint16));
        connect(chocobo_stable_5::sex_changed(quint8),this::c5_sexChanged(quint8));
        connect(chocobo_stable_5::type_changed(quint8),this::c5_typeChanged(quint8));
        connect(chocobo_stable_5::accel_changed(quint8),this::c5_accelChanged(quint8));
        connect(chocobo_stable_5::coop_changed(quint8),this::c5_coopChanged(quint8));
        connect(chocobo_stable_5::intelligence_changed(quint8),this::c5_intelChanged(quint8));
        connect(chocobo_stable_5::personality_changed(quint8),this::c5_personalityChanged(quint8));
        connect(chocobo_stable_5::pCount_changed(quint8),this::c5_pcountChanged(quint8));
        connect(chocobo_stable_5::wins_changed(quint8),this::c5_raceswonChanged(quint8));
        //Chocobo Editor 6
        connect(chocobo_stable_6::name_changed(QString),this::c6_nameChanged(QString));
        connect(chocobo_stable_6::cantMate_changed(bool),this::c6_mated_toggled(bool));
        connect(chocobo_stable_6::speed_changed(quint16),this::c6_speedChanged(quint16));
        connect(chocobo_stable_6::mSpeed_changed(quint16),this::c6_maxspeedChanged(quint16));
        connect(chocobo_stable_6::sprint_changed(quint16),this::c6_sprintChanged(quint16));
        connect(chocobo_stable_6::mSprint_changed(quint16),this::c6_maxsprintChanged(quint16));
        connect(chocobo_stable_6::stamina_changed(quint16),this::c6_staminaChanged(quint16));
        connect(chocobo_stable_6::sex_changed(quint8),this::c6_sexChanged(quint8));
        connect(chocobo_stable_6::type_changed(quint8),this::c6_typeChanged(quint8));
        connect(chocobo_stable_6::accel_changed(quint8),this::c6_accelChanged(quint8));
        connect(chocobo_stable_6::coop_changed(quint8),this::c6_coopChanged(quint8));
        connect(chocobo_stable_6::intelligence_changed(quint8),this::c6_intelChanged(quint8));
        connect(chocobo_stable_6::personality_changed(quint8),this::c6_personalityChanged(quint8));
        connect(chocobo_stable_6::pCount_changed(quint8),this::c6_pcountChanged(quint8));
        connect(chocobo_stable_6::wins_changed(quint8),this::c6_raceswonChanged(quint8));
        */
    }
}
void MainWindow::init_settings()
{
    //are any empty? if so set them accordingly.
    if(settings->value("autochargrowth").isNull()){settings->setValue("autochargrowth",1);}
    if(settings->value("load_path").isNull()){settings->setValue("load_path",QDir::homePath());}
    if(settings->value("char_stat_folder").isNull()){settings->setValue("char_stat_folder",QDir::homePath());}
    if(settings->value("color1_r").isNull()){settings->setValue("color1_r","7");}
    if(settings->value("color1_g").isNull()){settings->setValue("color1_g","6");}
    if(settings->value("color1_b").isNull()){settings->setValue("color1_b","6");}
    if(settings->value("color2_r").isNull()){settings->setValue("color2_r","35");}
    if(settings->value("color2_g").isNull()){settings->setValue("color2_g","33");}
    if(settings->value("color2_b").isNull()){settings->setValue("color2_b","33");}
    if(settings->value("color3_r").isNull()){settings->setValue("color3_r","65");}
    if(settings->value("color3_g").isNull()){settings->setValue("color3_g","65");}
    if(settings->value("color3_b").isNull()){settings->setValue("color3_b","65");}
    skip_slot_mask = settings->value("skip_slot_mask").toBool(); //skips setting the mask of last saved slot on writes. testing function

    if(settings->value("show_test").toBool())
    {
        ui->action_show_debug->setChecked(1);
        ui->action_show_debug->setIcon(QIcon(":/icon/debug_sel"));
    }
    else{ui->action_show_debug->setChecked(0);}
    QString style="QWidget#centralWidget{background-color: qlineargradient(spread:repeat, x1:1, y1:1, x2:0, y2:0, stop:0.0625 rgba(";
    style.append(settings->value("color1_r").toString());   style.append(",");
    style.append(settings->value("color1_g").toString());   style.append(",");
    style.append(settings->value("color1_b").toString());   style.append(", 255), stop:0.215909 rgba(");
    style.append(settings->value("color2_r").toString());   style.append(",");
    style.append(settings->value("color2_g").toString());   style.append(",");
    style.append(settings->value("color2_b").toString());   style.append(", 255), stop:0.818182 rgba(");
    style.append(settings->value("color3_r").toString());   style.append(",");
    style.append(settings->value("color3_g").toString());   style.append(",");
    style.append(settings->value("color3_b").toString());   style.append(", 255));}");
    ui->centralWidget->setStyleSheet(style);

    QString tablestyle = "::section{background-color:qlineargradient(spread:pad, x1:0.5, y1:0.00568182, x2:0.497, y2:1, stop:0 rgba(67, 67, 67, 128), stop:0.5 rgba(34, 201, 247, 128), stop:1 rgba(67, 67, 67, 128));;color: white;padding-left:4px;border:1px solid #6c6c6c;}";
    tablestyle.append("QHeaderView:down-arrow{image: url(:/icon/arrow_down);min-width:9px;}");
    tablestyle.append("QHeaderView:up-arrow{image: url(:/icon/arrow_up);min-width:9px;}");

    ui->tbl_location_field->horizontalHeader()->setStyleSheet(tablestyle);
    ui->tbl_unknown->horizontalHeader()->setStyleSheet(tablestyle);
    ui->tbl_compare_unknown->horizontalHeader()->setStyleSheet(tablestyle);
    ui->tbl_diff->horizontalHeader()->setStyleSheet(tablestyle);

    if(settings->value("autochargrowth").toBool())
    {
        ui->action_auto_char_growth->setChecked(1);
        ui->action_auto_char_growth->setIcon(QIcon(":/icon/checkbox_checked"));
    }
    else{ui->action_auto_char_growth->setChecked(0);}

    /* LANGUAGE SELECT */
    if(settings->value("lang").toString() == "en")
    {
        ui->action_Lang_en->setChecked(1);
        ui->action_Lang_en->setIcon(QIcon(":/icon/us_sel"));
    }
    else if(settings->value("lang").toString() == "es")
    {
        ui->action_Lang_es->setChecked(1);
        ui->action_Lang_es->setIcon(QIcon(":/icon/es_sel"));
    }
    else if(settings->value("lang").toString() == "fr")
    {
        ui->action_Lang_fr->setChecked(1);
        ui->action_Lang_fr->setIcon(QIcon(":/icon/fr_sel"));
    }
    else if(settings->value("lang").toString() == "ja")
    {
        ui->action_Lang_jp->setChecked(1);
        ui->action_Lang_jp->setIcon(QIcon(":/icon/jp_sel"));
    }
    else if(settings->value("lang").toString() == "de")
    {
        ui->action_Lang_de->setChecked(1);
        ui->action_Lang_de->setIcon(QIcon(":/icon/de_sel"));
    }
}
/*~~~~~~ END GUI SETUP ~~~~~~~*/
MainWindow::~MainWindow(){delete ui;}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    };
}
void MainWindow::dragEnterEvent(QDragEnterEvent *e) { e->accept(); }
void MainWindow::dropEvent(QDropEvent *e)
{
    if(ff7->isFileModified())
    {
        switch(save_changes())
        {
            case 0: return;//cancel load.
            case 1: break;//continue load
        }
    }
    const QMimeData *mimeData = e->mimeData();
    if(mimeData->hasUrls())
    {
        QStringList fileList;
        QList<QUrl> urlList = mimeData->urls();

        fileList.append(urlList.at(0).toLocalFile());
        loadFileFull(fileList.at(0),0);
     }
}
int MainWindow::save_changes(void)
{//return 0 to ingore the event/ return 1 to process event.
    int result; int rtn=0;
    result = QMessageBox::question(this,tr("Unsaved Changes"),tr("Save Changes to the File:\n%1").arg(ff7->fileName()),QMessageBox::Yes,QMessageBox::No,QMessageBox::Cancel);
    switch(result)
    {
        case QMessageBox::Yes:
                if(ui->action_Save->isEnabled()){on_action_Save_activated();}
                else
                {//user trying to save a file with no header.
                    QStringList types;
                    types << tr("PC")<<tr("Raw Psx Save")<<tr("Generic Emulator Memorycard")<<tr("PSP")<<tr("PS3")<<tr("Dex Drive Memorycard")<<tr("VGS Memorycard");
                    QString result = QInputDialog::getItem(this,tr("Save Error"),tr("Please Select A File Type To Save"),types,-1,0,0,0);
                    //check the string. and assign a type
                    if(result ==types.at(0)){on_actionExport_PC_Save_activated();}
                        else if(result ==types.at(1)){on_actionExport_PSX_activated();}
                        else if(result ==types.at(2)){on_actionExport_MC_triggered();}
                        else if(result ==types.at(3)){QMessageBox::information(this,tr("Black Chocobo"),tr("Can Not Export This Format"));}
                        else if(result ==types.at(4)){QMessageBox::information(this,tr("Black Chocobo"),tr("Can Not Export This Format"));}
                        else if(result ==types.at(5)){on_actionExport_DEX_triggered();}
                        else if(result ==types.at(6)){on_actionExport_VGS_triggered();}
                        else{return rtn;}
                    }
                    rtn=1;
                    break;
         case QMessageBox::Cancel: rtn=0; break;
        case QMessageBox::No:rtn=1;break;
     }
    return rtn;
}
void MainWindow::closeEvent(QCloseEvent *e)
{if(ff7->isFileModified()){
    switch(save_changes())
    {
        case 0: e->ignore(); break;
        case 1: e->accept(); break;
    }
}}
/*~~~~~ New Window ~~~~~*/
void MainWindow::on_actionNew_Window_triggered(){QProcess::startDetached(QCoreApplication::applicationFilePath());}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~LOAD/SAVE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionOpen_Save_File_activated()
{
    if(ff7->isFileModified())
    {
        switch(save_changes())
        {
            case 0: return;//cancel load.
            case 1: break;//yes or no pressed..
        }
    }
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Final Fantasy 7 Save"),settings->value("load_path").toString(),
    tr("Known FF7 Save Types (*.ff7 *-S* *.psv *.vmp *.vgs *.mem *.gme *.mcr *.mcd *.mci *.mc *.ddf *.ps *.psm *.VM1 *.bin);;PC FF7 SaveGame (*.ff7);;Raw PSX FF7 SaveGame (*-S*);;MC SaveGame (*.mcr *.mcd *.mci *.mc *.ddf *.ps *.psm *.VM1 *.bin);;PSV SaveGame (*.psv);;PSP SaveGame (*.vmp);;VGS SaveGame(*.vgs *.mem);;Dex-Drive SaveGame(*.gme);;All Files(*)"));
    if (!fileName.isEmpty()){loadFileFull(fileName,0);}
}
void MainWindow::on_actionReload_triggered(){if(!ff7->fileName().isEmpty()){loadFileFull(ff7->fileName(),1);}}
/*~~~~~~~~~~~~~~~~~Load Full ~~~~~~~~~~~~~~~~~~*/
void MainWindow::loadFileFull(const QString &fileName,int reload)
{//if called from reload then int reload ==1 (don't call slot select)
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly )){QMessageBox::warning(this, tr("Black Chocobo"), tr("Cannot read file %1:\n%2.") .arg(fileName).arg(file.errorString()));  return; }

    if(ff7->LoadFile(fileName))
    {
        _init=false;//we have now loaded a file
        file_modified(false);
    }
    else{QMessageBox::information(this,tr("Load Failed"),tr("Failed to Load File"));return;}

    if (ff7->type() == "PC"){if(reload){guirefresh(0);}else{on_actionShow_Selection_Dialog_activated();}}

    else if (ff7->type() == "PSX" || ff7->type() =="PSV"){s=0;guirefresh(0);}

    else if (ff7->type() == "MC" || ff7->type() =="PSP" || ff7->type() == "VGS" ||ff7->type()=="DEX")
        {if(reload){guirefresh(0);}   else{on_actionShow_Selection_Dialog_activated();}}

    else{/*UNKNOWN FILETYPE*/}
}
/*~~~~~~~~~~~~~~~~~IMPORT PSX~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionFrom_PSX_Slot_activated()
{//should check better to be sure its a raw PSX SAVE. then make file filter *
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Final Fantasy 7 PSX Save"),QDir::homePath(),tr("Raw PSX FF7 SaveGame (*)"));
    if(fileName.isEmpty()){return;}
    else
    {
        ff7->Import_PSX(s,fileName);
        file_modified(true);
        guirefresh(0);
    }
}
/*~~~~~~~~~~~~~~~~~IMPORT PSV~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionFrom_PSV_Slot_activated()
{//check beter to be sure its the correct PSV type file.
    QString fileName = QFileDialog::getOpenFileName(this,tr("Select Final Fantasy 7 PSV Save"),QDir::homePath(),tr("PSV FF7 SaveGame (*.psv)"));
    if (fileName.isEmpty()){return;}
    else
    {
        ff7->Import_PSV(s,fileName);
        file_modified(true);
        guirefresh(0);
    }
}
/*~~~~~~~~~~~~~~~~~IMPORT Char~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionImport_char_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Select FF7 Character Stat File"),settings->value("char_stat_folder").toString(),tr("FF7 Character Stat File(*.char)"));
    if (fileName.isEmpty()){return;}
    else
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly)){QMessageBox::warning(this, tr("Black Chocobo"),tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString())); return; }
        if(file.size() !=0x84){QMessageBox::warning(this, tr("Black Chocobo"),tr("%1:\n%2 is Not a FF7 Character Stat File.").arg(fileName).arg(file.errorString()));return;}
        QByteArray new_char;
        new_char = file.readAll();
        ff7->importChar(s,curchar,new_char);
    }
    file_modified(true);
    char_editor->setChar(ff7->slot[s].chars[curchar],ff7->charName(s,curchar));
}

void MainWindow::on_actionExport_char_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save FF7 Character File"), settings->value("char_stat_folder").toString(),
    tr("FF7 Character Stat File(*.char)"));
    if (!fileName.isEmpty()){ff7->exportChar(s,curchar,fileName);}
}
void MainWindow::on_action_Save_activated()
{
    if(_init)//no file loaded user saving a New Game
    {
        QStringList types;
        types << tr("PC")<<tr("Raw Psx Save")<<tr("Generic Emulator Memorycard")<<tr("PSP")<<tr("PS3")<<tr("Dex Drive Memorycard")<<tr("VGS Memorycard");
        QString result = QInputDialog::getItem(this,tr("Save Error"),tr("Please Select A File Type To Save"),types,-1,0,0,0);
        //check the string. and assign a type
        if(result ==types.at(0)){on_actionExport_PC_Save_activated();}
            else if(result ==types.at(1)){on_actionExport_PSX_activated();}
            else if(result ==types.at(2)){on_actionExport_MC_triggered();}
            else if(result ==types.at(3)){QMessageBox::information(this,tr("Black Chocobo"),tr("Can Not Export This Format"));}
            else if(result ==types.at(4)){QMessageBox::information(this,tr("Black Chocobo"),tr("Can Not Export This Format"));}
            else if(result ==types.at(5)){on_actionExport_DEX_triggered();}
            else if(result ==types.at(6)){on_actionExport_VGS_triggered();}
            else{}
    return;//leave this function.
    }

    if(!ff7->fileName().isEmpty())
    {
        if(ff7->type()=="PSP")
        {
            if(ff7->type()=="PSP"){QMessageBox::information(this,tr("PSP Save Notice"),tr("This File Does Not Have An Updated Checksum.It will not work on your PSP."));}
        }

        else if(ff7->type()=="PSV")
        {
            QMessageBox::information(this,tr("PSV Save Notice"),tr("This File Does Not Have An Updated Checksum.It will not work on your PS3."));
        }

        saveFileFull(ff7->fileName());
    }
    else{on_actionSave_File_As_activated();return;}//there is no filename we should get one from save as..
}

void MainWindow::on_actionSave_File_As_activated()
{QString fileName;
// check for the type of save loaded and set the output type so we don't save the wrong type, all conversion opperations should be done via an Export function.
    if(ff7->type() == "PC")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 PC SaveGame"), settings->value("save_pc_path").toString(),
        tr("FF7 PC SaveGame(*.ff7)"));
    }
    else if(ff7->type() == "PSX")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 PSX SaveGame"), QDir::homePath(),
        tr("FF7 Raw PSX SaveGame(*-S*)"));
    }
    else if(ff7->type() == "MC")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 MC SaveGame"), settings->value("save_emu_path").toString(),
        tr("FF7 MC SaveGame(*.mcr *.mcd *.mci *.mc *.ddf *.ps *.psm *.VM1 *.bin)"));
    }
    else if(ff7->type() == "PSV")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 PSV SaveGame"), QDir::homePath(),
        tr("FF7 PSV SaveGame(*.psv)"));
        QMessageBox::information(this,tr("PSV Save Notice"),tr("This File Does Not Have An Updated Checksum.It will not work on your PS3."));
    }
    else if(ff7->type() == "PSP")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7  PSP SaveGame"), QDir::homePath(),
        tr("FF7 PSP SaveGame(*.vmp)"));
        QMessageBox::information(this,tr("PSP Save Notice"),tr("This File Does Not Have An Updated Checksum.It will not work on your PSP."));
    }
    else if(ff7->type() == "VGS")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7  VGS SaveGame"), settings->value("save_emu_path").toString(),
        tr("FF7 VGS SaveGame(*.vgs *.mem)"));
    }
    else if(ff7->type() == "DEX")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7  Dex-Drive SaveGame"), settings->value("save_emu_path").toString(),
        tr("FF7 Dex SaveGame(*.gme)"));
    }
    else
    {//mystery type. make the user tell us user maybe used new game or made save manually.
        QStringList types;
        types << tr("PC")<<tr("Raw Psx Save")<<tr("Generic Emulator Memorycard")<<tr("PSP")<<tr("PS3")<<tr("Dex Drive Memorycard")<<tr("VGS Memorycard");
        QString result = QInputDialog::getItem(this,tr("Save Error"),tr("Please Select A File Type To Save"),types,-1,0,0,0);
        //check the string. and assign a type
        if(result ==types.at(0)){ff7->setType("PC");}
        else if(result ==types.at(1)){ff7->setType("PSX");}
        else if(result ==types.at(2)){ff7->setType("MC");}
        else if(result ==types.at(3)){ff7->setType("PSP");}
        else if(result ==types.at(4)){ff7->setType("PSV");}
        else if(result ==types.at(5)){ff7->setType("DEX");}
        else if(result ==types.at(6)){ff7->setType("VGS");}
        else{return;}
            on_actionSave_File_As_activated(); //now that we have a type do again.
    }
    if(fileName.isEmpty()){return;}
    saveFileFull(fileName); //reguardless save the file of course if its has a string.
}
/*~~~~~~~~~~~SHORT SAVE~~~~~~~~~~~~*/
void MainWindow::saveFileFull(QString fileName)
{
    if((ff7->type() =="PC") && !(settings->value("skip_slot_mask").toBool())){ff7->fix_pc_bytemask(s);}//fix starting slot on pc

    if(ff7->SaveFile(fileName))
    {
        if(_init)
        {//if no save was loaded and new game was clicked be sure to act like a game was loaded.
            _init=false;
        }
        file_modified(false);
        guirefresh(0);
    }
    else{QMessageBox::information(this,tr("Save Error"),tr("Failed to save file\n%1").arg(fileName));}
}
/*~~~~~~~~~~~~~~~New_Game~~~~~~~~~~~*/
void MainWindow::on_actionNew_Game_triggered()
{
    QString save_name ="";
    if(settings->value("override_default_save").toBool()){save_name = settings->value("default_save_file").toString();}
    ff7->New_Game(s,save_name);//call the new game function
    //detect region and fix names if needed.
    _init=false;
    if(!load){file_modified(true);}
    guirefresh(1);
}
/*~~~~~~~~~~End New_Game~~~~~~~~~~~*/
/*~~~~~~~~~~New Game + ~~~~~~~~~~~~*/
void MainWindow::on_actionNew_Game_Plus_triggered()
{
    QString save_name ="";
    if(settings->value("override_default_save").toBool())
    {save_name = settings->value("default_save_file").toString();}
    ff7->New_Game_Plus(s,ff7->fileName(),save_name);
    if(!load){file_modified(true);}
    guirefresh(0);
}
/*~~~~~~~~~~End New_Game +~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~EXPORT PC~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionExport_PC_Save_activated()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 SaveGame"),  settings->value("export_pc").toString() ,
    tr("FF7 SaveGame(*.ff7)")); // Only Allow PC save Since we are going to make one
    if(fileName.isEmpty()){return;}// catch if Cancel is pressed
    else
    {
        ui->combo_control->setCurrentIndex(0);
        ff7->Export_PC(fileName);
        file_modified(false);
    }
}
/*~~~~~~~~~~~~~~~~~EXPORT PSX~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionExport_PSX_activated()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 SaveGame"), ff7->region(s),
    tr("BASCUS-94163FF7-Sxx(*-S*);;BESCES-00867FF7-Sxx(*-S*);;BESCES-00868FF7-Sxx(*-S*);;BESCES-00869FF7-Sxx(*-S*);;BESCES-00900FF7-Sxx(*-S*);;BISLPS-00700FF7-Sxx(*-S*);;BISLPS-01057FF7-Sxx(*-S*)"));
    if (fileName.isEmpty()){return;}// catch if Cancel is pressed
    else
    {
        ui->combo_control->setCurrentIndex(0);
        ff7->Export_PSX(s,fileName);
        file_modified(false);
    }
}
/*~~~~~Export Mcr/Mcd~~~~~~*/
void MainWindow::on_actionExport_MC_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 MC SaveGame"), settings->value("save_emu_path").toString(),
    tr("FF7 MC SaveGame(*.mcr *.mcd *.mci *.mc *.ddf *.ps *.psm *.bin)"));
    if(fileName.isEmpty()){return;}
    else
    {
        ui->combo_control->setCurrentIndex(0);
        ff7->Export_VMC(fileName);
        file_modified(false);
    }
}
void MainWindow::on_actionExport_VGS_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 VGS SaveGame"), settings->value("save_emu_path").toString(),
    tr("FF7 VGS SaveGame(*.vgs *.mem)"));
    if(fileName.isEmpty()){return;}
    else
    {
        ui->combo_control->setCurrentIndex(0);
        ff7->Export_VGS(fileName);
        file_modified(false);
    }
}
void MainWindow::on_actionExport_DEX_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 Dex-Drive SaveGame"), settings->value("save_emu_path").toString(),tr("FF7 Dex SaveGame(*.gme)"));
    if(fileName.isEmpty()){return;}
    else
    {
        ui->combo_control->setCurrentIndex(0);
        ff7->Export_DEX(fileName);
        file_modified(false);
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END LOAD/SAVE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MENU ACTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~Simple Menu Stuff~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionSlot_01_activated(){s=0; guirefresh(0);}
void MainWindow::on_actionSlot_02_activated(){s=1; guirefresh(0);}
void MainWindow::on_actionSlot_03_activated(){s=2; guirefresh(0);}
void MainWindow::on_actionSlot_04_activated(){s=3; guirefresh(0);}
void MainWindow::on_actionSlot_05_activated(){s=4; guirefresh(0);}
void MainWindow::on_actionSlot_06_activated(){s=5; guirefresh(0);}
void MainWindow::on_actionSlot_07_activated(){s=6; guirefresh(0);}
void MainWindow::on_actionSlot_08_activated(){s=7; guirefresh(0);}
void MainWindow::on_actionSlot_09_activated(){s=8; guirefresh(0);}
void MainWindow::on_actionSlot_10_activated(){s=9; guirefresh(0);}
void MainWindow::on_actionSlot_11_activated(){s=10; guirefresh(0);}
void MainWindow::on_actionSlot_12_activated(){s=11; guirefresh(0);}
void MainWindow::on_actionSlot_13_activated(){s=12; guirefresh(0);}
void MainWindow::on_actionSlot_14_activated(){s=13; guirefresh(0);}
void MainWindow::on_actionSlot_15_activated(){s=14; guirefresh(0);}
void MainWindow::on_actionClear_Slot_activated(){ff7->clearslot(s);  guirefresh(0);}

void MainWindow::on_actionShow_Selection_Dialog_activated(){SlotSelect slotselect(0,ff7);slotselect.setStyleSheet(this->styleSheet());s=slotselect.exec();guirefresh(0);}
void MainWindow::on_actionPrevious_Slot_activated(){if(ff7->type()==""){return;}else{if (s > 0) {s--; guirefresh(0);}}}
void MainWindow::on_actionNext_Slot_activated(){if(ff7->type()==""){return;}else{if (s<14){s++; guirefresh(0);}}}
void MainWindow::on_actionAbout_activated(){about adialog;  adialog.setStyleSheet(this->styleSheet()); adialog.exec();}
void MainWindow::on_actionCopy_Slot_activated(){ff7->CopySlot(s);}
void MainWindow::on_actionPaste_Slot_activated(){ff7->PasteSlot(s); file_modified(true); guirefresh(0);}
void MainWindow::on_actionShow_Options_triggered(){Options odialog(0,settings); odialog.setStyleSheet(this->styleSheet()); odialog.exec(); init_settings(); }
void MainWindow::on_actionCreateNewMetadata_triggered(){ metadataCreator mdata(this,ff7); mdata.setStyleSheet(this->styleSheet()); mdata.exec();}

void MainWindow::on_action_auto_char_growth_triggered(bool checked)
{
    if(checked)
    {
        settings->setValue("autochargrowth",1);
        ui->action_auto_char_growth->setIcon(QIcon(":/icon/checkbox_checked"));
        if(!load){char_editor->setAutoLevel(1); char_editor->setAutoStatCalc(1);}
    }
    else
    {
        settings->setValue("autochargrowth",0);
        char_editor->setAutoLevel(0); char_editor->setAutoStatCalc(0);
        ui->action_auto_char_growth->setIcon(QIcon(":/icon/checkbox_unchecked"));
    }
}
void MainWindow::on_action_show_debug_toggled(bool checked)
{
    if(checked)
    {
        ui->actionNew_Window->setVisible(1);
        ui->tabWidget->setTabEnabled(8,1);
        ui->cb_Region_Slot->setEnabled(true);
        ui->bm_unknown->setVisible(true);
        ui->bh_id->setVisible(true);
        ui->leader_id->setVisible(true);
        if(ff7->type() == "PC"){ui->group_controller_mapping->setVisible(true);}
        settings->setValue("show_test",1);
        ui->action_show_debug->setIcon(QIcon(":/icon/debug_sel"));
        ui->cb_farm_items_1->setVisible(true);
        ui->cb_farm_items_2->setVisible(true);
        ui->cb_farm_items_3->setVisible(true);
        ui->cb_farm_items_4->setVisible(true);
        ui->cb_farm_items_5->setVisible(true);
        ui->cb_farm_items_6->setVisible(true);
        ui->cb_farm_items_7->setVisible(true);
        ui->cb_farm_items_8->setVisible(true);
        testdata_refresh();
    }

    else
    {
        ui->actionNew_Window->setVisible(0);
        ui->tabWidget->setTabEnabled(8,0);
        ui->cb_Region_Slot->setEnabled(false);
        ui->bm_unknown->setVisible(false);
        ui->bh_id->setVisible(false);
        ui->leader_id->setVisible(false);
        if(ff7->type() =="PC"){ui->group_controller_mapping->setVisible(false);}
        settings->setValue("show_test",0);
        ui->action_show_debug->setIcon(QIcon(":/icon/debug_unsel"));
        ui->cb_farm_items_1->setVisible(false);
        ui->cb_farm_items_2->setVisible(false);
        ui->cb_farm_items_3->setVisible(false);
        ui->cb_farm_items_4->setVisible(false);
        ui->cb_farm_items_5->setVisible(false);
        ui->cb_farm_items_6->setVisible(false);
        ui->cb_farm_items_7->setVisible(false);
        ui->cb_farm_items_8->setVisible(false);
    }
}

/*~~~~~~~~~~~~LANGUAGE & REGION ACTIONS~~~~~~~~~~~~~~*/
void MainWindow::on_action_Lang_en_triggered()
{
    //clear other lang
    ui->action_Lang_es->setChecked(0);
    ui->action_Lang_es->setIcon(QIcon(":/icon/es_unsel"));
    ui->action_Lang_fr->setChecked(0);
    ui->action_Lang_fr->setIcon(QIcon(":/icon/fr_unsel"));
    ui->action_Lang_jp->setChecked(0);
    ui->action_Lang_jp->setIcon(QIcon(":/icon/jp_unsel"));
    ui->action_Lang_de->setChecked(0);
    ui->action_Lang_de->setIcon(QIcon(":/icon/de_unsel"));
    settings->setValue("lang","en");
    ui->action_Lang_en->setIcon(QIcon(":/icon/us_sel"));
    QMessageBox::information(this,"Language Changed","You Must Restart For The Language to Change");
}
void MainWindow::on_action_Lang_es_triggered()
{
    ui->action_Lang_en->setChecked(0);
    ui->action_Lang_en->setIcon(QIcon(":/icon/us_unsel"));
    ui->action_Lang_fr->setChecked(0);
    ui->action_Lang_fr->setIcon(QIcon(":/icon/fr_unsel"));
    ui->action_Lang_jp->setChecked(0);
    ui->action_Lang_jp->setIcon(QIcon(":/icon/jp_unsel"));
    ui->action_Lang_de->setChecked(0);
    ui->action_Lang_de->setIcon(QIcon(":/icon/de_unsel"));
    settings->setValue("lang","es");
    ui->action_Lang_es->setIcon(QIcon(":/icon/es_sel"));
    QMessageBox::information(this,QString::fromUtf8("Idioma Cambiado"),QString::fromUtf8("Debe reiniciar Para el cambio de idioma"));
}
void MainWindow::on_action_Lang_fr_triggered()
{
    ui->action_Lang_en->setChecked(0);
    ui->action_Lang_en->setIcon(QIcon(":/icon/us_unsel"));
    ui->action_Lang_es->setChecked(0);
    ui->action_Lang_es->setIcon(QIcon(":/icon/es_unsel"));
    ui->action_Lang_jp->setChecked(0);
    ui->action_Lang_jp->setIcon(QIcon(":/icon/jp_unsel"));
    ui->action_Lang_de->setChecked(0);
    ui->action_Lang_de->setIcon(QIcon(":/icon/de_unsel"));
    settings->setValue("lang","fr");
    ui->action_Lang_fr->setIcon(QIcon(":/icon/fr_sel"));
    QMessageBox::information(this,QString::fromUtf8("Langue Modifiée"),QString::fromUtf8("Vous Devez Redemarrer Pour Changer la Langue"));
}
void MainWindow::on_action_Lang_de_triggered()
{
    ui->action_Lang_en->setChecked(0);
    ui->action_Lang_en->setIcon(QIcon(":/icon/us_unsel"));
    ui->action_Lang_es->setChecked(0);
    ui->action_Lang_es->setIcon(QIcon(":/icon/es_unsel"));
    ui->action_Lang_fr->setChecked(0);
    ui->action_Lang_fr->setIcon(QIcon(":/icon/fr_unsel"));
    ui->action_Lang_jp->setIcon(QIcon(":/icon/jp_unsel"));
    settings->setValue("lang","de");
    ui->action_Lang_de->setIcon(QIcon(":/icon/de_sel"));
    QMessageBox::information(this,QString::fromUtf8("Sprache geändert"),QString::fromUtf8("Neustarten um Sprache zu ändern"));
}
void MainWindow::on_action_Lang_jp_triggered()
{
    ui->action_Lang_en->setChecked(0);
    ui->action_Lang_en->setIcon(QIcon(":/icon/us_unsel"));
    ui->action_Lang_es->setChecked(0);
    ui->action_Lang_es->setIcon(QIcon(":/icon/es_unsel"));
    ui->action_Lang_fr->setChecked(0);
    ui->action_Lang_fr->setIcon(QIcon(":/icon/fr_unsel"));
    ui->action_Lang_de->setChecked(0);
    ui->action_Lang_de->setIcon(QIcon(":/icon/de_unsel"));
    settings->setValue("lang","ja");
    ui->action_Lang_jp->setIcon(QIcon(":/icon/jp_sel"));
    QMessageBox::information(this,QString::fromUtf8("言語の変更"),QString::fromUtf8("プログラムを再起動して言語の変更を適用してください"));
}
/*~~~~~~~~~~~~~SET USA MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_USA_triggered(bool checked)
{if(!load){file_modified(true);
    if(!checked)
    {
        ff7->setRegion(s,"");
        ui->lbl_sg_region->clear();
        ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
    }
    else
    {
        if(ff7->isPAL(s)){set_ntsc_time();}//Convert Time?
        ff7->setRegion(s,"NTSC-U");
        ui->action_Region_PAL_Generic->setChecked(false);
        ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
        ui->action_Region_PAL_French->setChecked(false);
        ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_unsel"));
        ui->action_Region_PAL_German->setChecked(false);
        ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
        ui->action_Region_PAL_Spanish->setChecked(false);
        ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
        ui->action_Region_JPN->setChecked(false);
        ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_JPN_International->setChecked(false);
        ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_USA->setIcon(QIcon(":/icon/us_sel"));
        ui->lbl_sg_region->setText(ff7->region(s).mid(0,ff7->region(s).lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S")+1,2).toInt()-1);
    }
}}
/*~~~~~~~~~~~~~SET PAL MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_Generic_triggered(bool checked)
{if(!load){file_modified(true);
    if(!checked)
    {
        ff7->setRegion(s,"");
        ui->lbl_sg_region->clear();
        ui->action_Region_USA->setIcon(QIcon(":/icon/eu_unsel"));
    }
    else
    {
        if(ff7->isNTSC(s)){set_pal_time();}//Call RegionTime Convertor
        ff7->setRegion(s,"PAL-E");
        ui->action_Region_USA->setChecked(false);
        ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
        ui->action_Region_PAL_German->setChecked(false);
        ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
        ui->action_Region_PAL_French->setChecked(false);
        ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_unsel"));
        ui->action_Region_PAL_Spanish->setChecked(false);
        ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
        ui->action_Region_JPN->setChecked(false);
        ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_JPN_International->setChecked(false);
        ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_sel"));
        ui->lbl_sg_region->setText(ff7->region(s).mid(0,ff7->region(s).lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S")+1,2).toInt()-1);
        //Text.init(0);
    }
}}
/*~~~~~~~~~~~~~SET PAL_German MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_German_triggered(bool checked)
{if(!load){file_modified(true);
    if(!checked)
    {
        ff7->setRegion(s,"");
        ui->lbl_sg_region->clear();
        ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
    }
    else
    {
        if(ff7->isNTSC(s)){set_pal_time();}//Call RegionTime Convertor
        ff7->setRegion(s,"PAL-DE");
        ui->action_Region_USA->setChecked(false);
        ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
        ui->action_Region_PAL_Generic->setChecked(false);
        ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
        ui->action_Region_PAL_French->setChecked(false);
        ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_unsel"));
        ui->action_Region_PAL_Spanish->setChecked(false);
        ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
        ui->action_Region_JPN->setChecked(false);
        ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_JPN_International->setChecked(false);
        ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_sel"));
        ui->lbl_sg_region->setText(ff7->region(s).mid(0,ff7->region(s).lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S")+1,2).toInt()-1);
    }
}}
/*~~~~~~~~~~~~~SET PAL_Spanish MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_Spanish_triggered(bool checked)
{if(!load){file_modified(true);
    if(!checked)
    {
        ff7->setRegion(s,"");
        ui->lbl_sg_region->clear();
        ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
    }
    else
    {
        if(ff7->isNTSC(s)){set_pal_time();}//Call RegionTime Convertor
        ff7->setRegion(s,"PAL-ES");
        ui->action_Region_USA->setChecked(false);
        ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
        ui->action_Region_PAL_Generic->setChecked(false);
        ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
        ui->action_Region_PAL_French->setChecked(false);
        ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_unsel"));
        ui->action_Region_PAL_German->setChecked(false);
        ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
        ui->action_Region_JPN->setChecked(false);
        ui->action_Region_JPN_International->setChecked(false);
        ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_sel"));
        ui->lbl_sg_region->setText(ff7->region(s).mid(0,ff7->region(s).lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S")+1,2).toInt()-1);
    }
}}
/*~~~~~~~~~~~~~SET PAL_French MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_French_triggered(bool checked)
{if(!load){file_modified(true);
    if(!checked)
    {
        ff7->setRegion(s,"");
        ui->lbl_sg_region->clear();
        ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_unsel"));
    }
    else
    {
        if(ff7->isNTSC(s)){set_pal_time();}//Call RegionTime Convertor
        ff7->setRegion(s,"PAL-FR");
        ui->action_Region_USA->setChecked(false);
        ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
        ui->action_Region_PAL_Generic->setChecked(false);
        ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
        ui->action_Region_PAL_Spanish->setChecked(false);
        ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
        ui->action_Region_PAL_German->setChecked(false);
        ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
        ui->action_Region_JPN->setChecked(false);
        ui->action_Region_JPN_International->setChecked(false);
        ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_sel"));
        ui->lbl_sg_region->setText(ff7->region(s).mid(0,ff7->region(s).lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S")+1,2).toInt()-1);
    }
}}
/*~~~~~~~~~~~~~SET JPN MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_JPN_triggered(bool checked)
{if(!load){file_modified(true);
    if(!checked)
    {
        ff7->setRegion(s,"");
        ui->lbl_sg_region->clear();
        ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
    }
    else
    {//First Check If Coming From PAL
        if(ff7->isPAL(s)){set_ntsc_time();}//Convert Time?
        ff7->setRegion(s,"NTSC-J");
        ui->action_Region_USA->setChecked(false);
        ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
        ui->action_Region_PAL_Generic->setChecked(false);
        ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
        ui->action_Region_PAL_French->setChecked(false);
        ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_unsel"));
        ui->action_Region_PAL_German->setChecked(false);
        ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
        ui->action_Region_PAL_Spanish->setChecked(false);
        ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
        ui->action_Region_JPN_International->setChecked(false);
        ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_sel"));
        ui->lbl_sg_region->setText(ff7->region(s).mid(0,ff7->region(s).lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S")+1,2).toInt()-1);
    }
}}
/*~~~~~~~~~~~~~SET JPN_International MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_JPN_International_triggered(bool checked)
{if(!load){file_modified(true);
    if(!checked)
    {
        ff7->setRegion(s,"");
        ui->lbl_sg_region->clear();
        ui->action_Region_JPN_International->setIcon(QIcon(":icon/jp_unsel"));
    }
    else
    {
        if(ff7->isPAL(s)){set_ntsc_time();}//Convert Time?
        ff7->setRegion(s,"NTSC-JI");
        ui->action_Region_USA->setChecked(false);
        ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
        ui->action_Region_PAL_Generic->setChecked(false);
        ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
        ui->action_Region_PAL_French->setChecked(false);
        ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_unsel"));
        ui->action_Region_PAL_German->setChecked(false);
        ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
        ui->action_Region_PAL_Spanish->setChecked(false);
        ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
        ui->action_Region_JPN->setChecked(false);
        ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
        ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_sel"));
        ui->lbl_sg_region->setText(ff7->region(s).mid(0,ff7->region(s).lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S")+1,2).toInt()-1);
    }
}}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END MENU ACTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~GUI FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~Set Menu Items~~~~~~~~~~*/
void MainWindow::setmenu(bool newgame)
{
    load=true;
    /*~~Disable All Items that are dependent on File Type~~*/
    ui->actionSlot_01->setChecked(0);ui->actionSlot_01->setIcon(QIcon(":icon/1_unsel"));
    ui->actionSlot_02->setChecked(0);ui->actionSlot_02->setIcon(QIcon(":icon/2_unsel"));
    ui->actionSlot_03->setChecked(0);ui->actionSlot_03->setIcon(QIcon(":icon/3_unsel"));
    ui->actionSlot_04->setChecked(0);ui->actionSlot_04->setIcon(QIcon(":icon/4_unsel"));
    ui->actionSlot_05->setChecked(0);ui->actionSlot_05->setIcon(QIcon(":icon/5_unsel"));
    ui->actionSlot_06->setChecked(0);ui->actionSlot_06->setIcon(QIcon(":icon/6_unsel"));
    ui->actionSlot_07->setChecked(0);ui->actionSlot_07->setIcon(QIcon(":icon/7_unsel"));
    ui->actionSlot_08->setChecked(0);ui->actionSlot_08->setIcon(QIcon(":icon/8_unsel"));
    ui->actionSlot_09->setChecked(0);ui->actionSlot_09->setIcon(QIcon(":icon/9_unsel"));
    ui->actionSlot_10->setChecked(0);ui->actionSlot_10->setIcon(QIcon(":icon/10_unsel"));
    ui->actionSlot_11->setChecked(0);ui->actionSlot_11->setIcon(QIcon(":icon/11_unsel"));
    ui->actionSlot_12->setChecked(0);ui->actionSlot_12->setIcon(QIcon(":icon/12_unsel"));
    ui->actionSlot_13->setChecked(0);ui->actionSlot_13->setIcon(QIcon(":icon/13_unsel"));
    ui->actionSlot_14->setChecked(0);ui->actionSlot_14->setIcon(QIcon(":icon/14_unsel"));
    ui->actionSlot_15->setChecked(0);ui->actionSlot_15->setIcon(QIcon(":icon/15_unsel"));
    ui->action_Region_USA->setChecked(0);ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
    ui->action_Region_PAL_Generic->setChecked(0);ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
    ui->action_Region_PAL_German->setChecked(0);ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_unsel"));
    ui->action_Region_PAL_French->setChecked(0);ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
    ui->action_Region_PAL_Spanish->setChecked(0);ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
    ui->action_Region_JPN->setChecked(0);ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
    ui->action_Region_JPN_International->setChecked(0);ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
    ui->actionNext_Slot->setEnabled(0);ui->actionPrevious_Slot->setEnabled(0);
    ui->actionShow_Selection_Dialog->setEnabled(0);ui->actionSlot_01->setEnabled(0);ui->actionSlot_02->setEnabled(0);
    ui->actionSlot_03->setEnabled(0);ui->actionSlot_04->setEnabled(0);ui->actionSlot_05->setEnabled(0);
    ui->actionSlot_06->setEnabled(0);ui->actionSlot_07->setEnabled(0);ui->actionSlot_08->setEnabled(0);
    ui->actionSlot_09->setEnabled(0);ui->actionSlot_10->setEnabled(0);ui->actionSlot_11->setEnabled(0);
    ui->actionSlot_12->setEnabled(0);ui->actionSlot_13->setEnabled(0);ui->actionSlot_14->setEnabled(0);
    ui->actionSlot_15->setEnabled(0);ui->actionNew_Game->setEnabled(0);ui->compare_table->setEnabled(0);
    ui->lbl_current_slot_num->clear(); ui->lbl_current_slot_txt->clear();
    /*~~End Clear Menu Items~~*/
    /*~~~~~~Current Slot~~~~~~*/
    switch(s)
    {
        case 0:ui->actionSlot_01->setChecked(1);ui->actionSlot_01->setIcon(QIcon(":icon/1_sel"));break;
        case 1:ui->actionSlot_02->setChecked(1);ui->actionSlot_02->setIcon(QIcon(":icon/2_sel"));break;
        case 2:ui->actionSlot_03->setChecked(1);ui->actionSlot_03->setIcon(QIcon(":icon/3_sel"));break;
        case 3:ui->actionSlot_04->setChecked(1);ui->actionSlot_04->setIcon(QIcon(":icon/4_sel"));break;
        case 4:ui->actionSlot_05->setChecked(1);ui->actionSlot_05->setIcon(QIcon(":icon/5_sel"));break;
        case 5:ui->actionSlot_06->setChecked(1);ui->actionSlot_06->setIcon(QIcon(":icon/6_sel"));break;
        case 6:ui->actionSlot_07->setChecked(1);ui->actionSlot_07->setIcon(QIcon(":icon/7_sel"));break;
        case 7:ui->actionSlot_08->setChecked(1);ui->actionSlot_08->setIcon(QIcon(":icon/8_sel"));break;
        case 8:ui->actionSlot_09->setChecked(1);ui->actionSlot_09->setIcon(QIcon(":icon/9_sel"));break;
        case 9:ui->actionSlot_10->setChecked(1);ui->actionSlot_10->setIcon(QIcon(":icon/10_sel"));break;
        case 10:ui->actionSlot_11->setChecked(1);ui->actionSlot_11->setIcon(QIcon(":icon/11_sel"));break;
        case 11:ui->actionSlot_12->setChecked(1);ui->actionSlot_12->setIcon(QIcon(":icon/12_sel"));break;
        case 12:ui->actionSlot_13->setChecked(1);ui->actionSlot_13->setIcon(QIcon(":icon/13_sel"));break;
        case 13:ui->actionSlot_14->setChecked(1);ui->actionSlot_14->setIcon(QIcon(":icon/14_sel"));break;
        case 14:ui->actionSlot_15->setChecked(1);ui->actionSlot_15->setIcon(QIcon(":icon/15_sel"));break;
    }
    /*~~~~End Current Slot~~~~~*/
    /*~~~~~~~Set Actions By Type~~~~~~~*/
    //For first file load.Don't Bother to disable these again.
    //new game should always be exported. no header...
    if(!newgame)
    {
        ui->actionSave_File_As->setEnabled(1);
        ui->actionReload->setEnabled(1);
    }
    ui->actionExport_PC_Save->setEnabled(1);    ui->actionExport_PSX->setEnabled(1);
    ui->actionExport_MC->setEnabled(1);         ui->actionExport_VGS->setEnabled(1);
    ui->actionExport_DEX->setEnabled(1);        ui->actionExport_char->setEnabled(1);
    ui->actionImport_char->setEnabled(1);       ui->action_Save->setEnabled(1);

    if(!_init)
    {//we haven't loaded a file yet.
        ui->actionNew_Game_Plus->setEnabled(1); ui->actionFrom_PSV_Slot->setEnabled(1);
        ui->actionFrom_PSX_Slot->setEnabled(1); ui->actionCopy_Slot->setEnabled(1);
        ui->actionPaste_Slot->setEnabled(1);
    }
    if (ff7->type()!= "PSX" && ff7->type() !="PSV" && (!_init)) //more then one slot
    {
        ui->actionSlot_01->setEnabled(1);   ui->actionNext_Slot->setEnabled(1);
        ui->actionSlot_02->setEnabled(1);   ui->actionPrevious_Slot->setEnabled(1);
        ui->actionSlot_03->setEnabled(1);   ui->actionShow_Selection_Dialog->setEnabled(1);
        ui->actionSlot_04->setEnabled(1);   ui->actionClear_Slot->setEnabled(1);
        ui->actionSlot_05->setEnabled(1);   ui->actionNew_Game->setEnabled(1);
        ui->actionSlot_06->setEnabled(1);   ui->actionSlot_07->setEnabled(1);
        ui->actionSlot_08->setEnabled(1);   ui->actionSlot_09->setEnabled(1);
        ui->actionSlot_10->setEnabled(1);   ui->actionSlot_11->setEnabled(1);
        ui->actionSlot_12->setEnabled(1);   ui->actionSlot_13->setEnabled(1);
        ui->actionSlot_14->setEnabled(1);   ui->actionSlot_15->setEnabled(1);
        ui->compare_table->setEnabled(1);   ui->lbl_current_slot_txt->setText(tr("Current Slot:"));
        ui->lbl_current_slot_num->setNum(s+1);
    }
    /*~~~End Set Actions By Type~~~*/
    /*~~Set Detected Region ~~*/
    if(ff7->region(s).contains("94163")){ui->action_Region_USA->setChecked(Qt::Checked);ui->action_Region_USA->setIcon(QIcon(":/icon/us_sel"));}
    else if(ff7->region(s).contains("00867")){ui->action_Region_PAL_Generic->setChecked(Qt::Checked);ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_sel"));}
    else if(ff7->region(s).contains("00868")){ui->action_Region_PAL_French->setChecked(Qt::Checked);ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_sel"));}
    else if(ff7->region(s).contains("00869")){ui->action_Region_PAL_German->setChecked(Qt::Checked);ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_sel"));}
    else if(ff7->region(s).contains("00900")){ui->action_Region_PAL_Spanish->setChecked(Qt::Checked);ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_sel"));}
    else if(ff7->region(s).contains("00700")){ui->action_Region_JPN->setChecked(Qt::Checked);ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_sel"));}
    else if(ff7->region(s).contains("01057")){ui->action_Region_JPN_International->setChecked(Qt::Checked);ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_sel"));}
    else if(ff7->region(s).isEmpty()){/*do nothing*/}
    else{QMessageBox::information(this,tr("Region Detect Error"),tr("Region Cannot be Automatically Detected, You Must Set it Manually"));}
    /*~~End Detected Region~~*/
   load=false;
}
void MainWindow::file_modified(bool changed)
{
    ff7->FileModified(changed,s);
    ui->lbl_fileName->setText(ff7->fileName());

    if(changed){ui->lbl_fileName->setText(ui->lbl_fileName->text().append("*"));}
}

/*~~~~~~~~~End Set Menu~~~~~~~~~~~*/
void MainWindow::set_ntsc_time(void)
{
    int result;
    QMessageBox fixtime(this);
    fixtime.setIconPixmap(QPixmap(":/icon/fix_time"));
    fixtime.setText(tr("Would you like to correct the play time?"));
    fixtime.setInformativeText(tr("In this region the game runs 60hz"));
    fixtime.setWindowTitle(tr("PAL -> NTSC Conversion"));
    fixtime.addButton(QMessageBox::Yes);
    fixtime.addButton(QMessageBox::No);
    result=fixtime.exec();

    switch(result)
    {
        case QMessageBox::Yes:
            ff7->slot[s].time = (ff7->slot[s].time*1.2); ff7->setDescTime(s,ff7->slot[s].time);
            load=true;
            ui->sb_time_hour->setValue(ff7->slot[s].time / 3600);
            ui->sb_time_min->setValue(ff7->slot[s].time/60%60);
            ui->sb_time_sec->setValue(ff7->slot[s].time -((ui->sb_time_hour->value()*3600)+ui->sb_time_min->value()*60));
            load=false;
        break;
        case QMessageBox::Cancel:break;
    }
}
void MainWindow::set_pal_time(void)
{
    int result;
    QMessageBox fixtime(this);
    fixtime.setIconPixmap(QPixmap(":/icon/fix_time"));
    fixtime.setText(tr("Would you like to correct the play time?"));
    fixtime.setInformativeText(tr("In this region the game runs 50hz"));
    fixtime.setWindowTitle(tr("NTSC -> PAL Conversion"));
    fixtime.addButton(QMessageBox::Yes);
    fixtime.addButton(QMessageBox::No);
    result=fixtime.exec();

    switch(result)
    {
        case QMessageBox::Yes:
            ff7->slot[s].time = (ff7->slot[s].time/1.2); ff7->setDescTime(s,ff7->slot[s].time);
            load=true;
            ui->sb_time_hour->setValue(ff7->slot[s].time / 3600);
            ui->sb_time_min->setValue(ff7->slot[s].time/60%60);
            ui->sb_time_sec->setValue(ff7->slot[s].time -((ui->sb_time_hour->value()*3600)+ui->sb_time_min->value()*60));
            load=false;
        break;
        case QMessageBox::Cancel:break;
    }
}
void MainWindow::materiaupdate(void)
{
    load=true;
    QTableWidgetItem *newItem;
    int j= ui->tbl_materia->currentRow();
    ui->tbl_materia->reset();
    ui->tbl_materia->clearContents();
    ui->tbl_materia->setColumnWidth(0,(ui->tbl_materia->width()*.65));
    ui->tbl_materia->setColumnWidth(1,(ui->tbl_materia->width()*.25));
    ui->tbl_materia->setRowCount(200);

    for(int mat=0;mat<200;mat++)// partys materias
    {
        qint32 current_ap= ff7->partyMateriaAp(s,mat);
        quint8 current_id= ff7->partyMateriaId(s,mat);
        QString ap;

        if(current_id == FF7Materia::EnemySkill)
        {
            newItem = new QTableWidgetItem(Materias.Icon(current_id),Materias.Name(current_id),0);
            ui->tbl_materia->setItem(mat,0,newItem);
            if (current_ap == FF7Materia::MaxMateriaAp){newItem =new QTableWidgetItem(tr("Master"));ui->tbl_materia->setItem(mat,1,newItem);}
            else{newItem =new QTableWidgetItem(QString("N/A"),0);ui->tbl_materia->setItem(mat,1,newItem);}
        }
        else if (current_id !=FF7Materia::EmptyId)
        {
            newItem = new QTableWidgetItem(Materias.Icon(current_id),Materias.Name(current_id),0);
            ui->tbl_materia->setItem(mat,0,newItem);
            if (current_ap == FF7Materia::MaxMateriaAp){newItem =new QTableWidgetItem(tr("Master"));ui->tbl_materia->setItem(mat,1,newItem);}
            else{newItem =new QTableWidgetItem(ap.setNum(current_ap));ui->tbl_materia->setItem(mat,1,newItem);}
        }
        else
        {
            ff7->setPartyMateria(s,mat,FF7Materia::EmptyId,FF7Materia::MaxMateriaAp);//invalid insure its clear.
            newItem = new QTableWidgetItem(tr("===Empty Slot==="),0);
            ui->tbl_materia->setItem(mat,0,newItem);
            newItem = new QTableWidgetItem("",0);
            ui->tbl_materia->setItem(mat,1,newItem);
        }
    }
    if(ff7->partyMateriaId(s,j) == FF7Materia::EnemySkill){mat_spacer->changeSize(0,0,QSizePolicy::Fixed,QSizePolicy::Fixed);}
    else{mat_spacer->changeSize(0,0,QSizePolicy::Fixed,QSizePolicy::MinimumExpanding);}
    materia_editor->setMateria(ff7->partyMateriaId(s,j),ff7->partyMateriaAp(s,j));
    ui->tbl_materia->setCurrentCell(j,1);//so that right side is set correctly.
    load=false;
}
void MainWindow::materia_ap_changed(qint32 ap)
{if(!load){
    //if(ap>=materia_editor->MaxAP()){ap=16777215;}
    ff7->setPartyMateria(s,ui->tbl_materia->currentRow(),ff7->partyMateriaId(s,ui->tbl_materia->currentRow()),ap);
    materiaupdate();
}}
void MainWindow::materia_id_changed(qint8 id)
{if(!load){
    ff7->setPartyMateria(s,ui->tbl_materia->currentRow(),id,ff7->partyMateriaAp(s,ui->tbl_materia->currentRow()));
    materiaupdate();
}}

void MainWindow::itemupdate(void)
{
    load=true;
    //Field Items Picked up
    if((ff7->slot[s].z_38[48])&(1<<0)){ui->cb_bm_items_1->setChecked(1);}
    else{ui->cb_bm_items_1->setChecked(0);}
    if((ff7->slot[s].z_38[48])&(1<<1)){ui->cb_bm_items_2->setChecked(1);}
    else{ui->cb_bm_items_2->setChecked(0);}
    if((ff7->slot[s].z_38[48])&(1<<2)){ui->cb_bm_items_3->setChecked(1);}
    else{ui->cb_bm_items_3->setChecked(0);}
    if((ff7->slot[s].z_38[48])&(1<<3)){ui->cb_bm_items_4->setChecked(1);}
    else{ui->cb_bm_items_4->setChecked(0);}

    if((ff7->slot[s].itemsmask_1)& (1<<0)){ui->cb_itemmask1_1->setChecked(1);}
    else{ui->cb_itemmask1_1->setChecked(0);}
    if((ff7->slot[s].itemsmask_1)& (1<<1)){ui->cb_itemmask1_2->setChecked(1);}
    else{ui->cb_itemmask1_2->setChecked(0);}
    if((ff7->slot[s].itemsmask_1)& (1<<2)){ui->cb_itemmask1_3->setChecked(1);}
    else{ui->cb_itemmask1_3->setChecked(0);}
    if((ff7->slot[s].itemsmask_1)& (1<<3)){ui->cb_itemmask1_4->setChecked(1);}
    else{ui->cb_itemmask1_4->setChecked(0);}
    if((ff7->slot[s].itemsmask_1)& (1<<4)){ui->cb_itemmask1_5->setChecked(1);}
    else{ui->cb_itemmask1_5->setChecked(0);}
    if((ff7->slot[s].itemsmask_1)& (1<<5)){ui->cb_itemmask1_6->setChecked(1);}
    else{ui->cb_itemmask1_6->setChecked(0);}
    if((ff7->slot[s].itemsmask_1)& (1<<6)){ui->cb_itemmask1_7->setChecked(1);}
    else{ui->cb_itemmask1_7->setChecked(0);}
    if((ff7->slot[s].itemsmask_1)& (1<<7)){ui->cb_itemmask1_8->setChecked(1);}
    else{ui->cb_itemmask1_8->setChecked(0);}

    if((ff7->slot[s].z_9[4])&(1<<0)){ui->cb_s7tg_items_1->setChecked(1);}
    else{ui->cb_s7tg_items_1->setChecked(0);}
    if((ff7->slot[s].z_9[4])&(1<<1)){ui->cb_s7tg_items_2->setChecked(1);}
    else{ui->cb_s7tg_items_2->setChecked(0);}
    if((ff7->slot[s].z_9[4])&(1<<2)){ui->cb_s7tg_items_3->setChecked(1);}
    else{ui->cb_s7tg_items_3->setChecked(0);}
    if((ff7->slot[s].z_9[4])&(1<<3)){ui->cb_s7tg_items_4->setChecked(1);}
    else{ui->cb_s7tg_items_4->setChecked(0);}
    if((ff7->slot[s].z_9[4])&(1<<4)){ui->cb_s7tg_items_5->setChecked(1);}
    else{ui->cb_s7tg_items_5->setChecked(0);}
    if((ff7->slot[s].z_9[4])&(1<<5)){ui->cb_s7tg_items_6->setChecked(1);}
    else{ui->cb_s7tg_items_6->setChecked(0);}
    if((ff7->slot[s].z_9[4])&(1<<6)){ui->cb_s7tg_items_7->setChecked(1);}
    else{ui->cb_s7tg_items_7->setChecked(0);}
    if((ff7->slot[s].z_9[4])&(1<<7)){ui->cb_s7tg_items_8->setChecked(1);}
    else{ui->cb_s7tg_items_8->setChecked(0);}
    load=false;
}
/*~~~~~~~~~~~~~~~~~~~~~GUIREFRESH~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::guirefresh(bool newgame)
{
    load=true;
    /*~~~~Check for SG type and ff7~~~~*/
    if((!ff7->isFF7(s) && !ff7->region(s).isEmpty()) ||
      ((!ff7->isFF7(s))&& (ff7->type() =="MC" || ff7->type() =="VGS" ||ff7->type() =="DEX" ||ff7->type() =="PSP")
                       && (ff7->psx_block_type(s) !=0xA0)))
    {// NOT FF7
        errbox error(0,ff7,s);
        error.setStyleSheet(this->styleSheet());
        switch(error.exec())
        {

         case 0://View Anyway..
            QMessageBox::information(this,tr("Ingoring Non FF7 Save"),tr("Using Unknown Var Table To View Save"));
            ui->tabWidget->setCurrentIndex(8);
            ui->tabWidget_3->setCurrentIndex(1);
            ui->tabWidget->setTabEnabled(8,1);
            unknown_refresh(ui->combo_z_var->count()-1);
            break;

        case 1://Previous Clicked
            s--;
            guirefresh(0);
            break;

        case 2://Next Clicked
            s++;
            guirefresh(0);
            break;

        case 3://exported as psx
            on_actionShow_Selection_Dialog_activated();
            break;
        }

    }
    else
    {//IS FF7 Slot

        QByteArray text;
        if(ff7->region(s).isEmpty()
           && (ff7->type() =="MC" || ff7->type() =="VGS" ||ff7->type() =="DEX" ||ff7->type() =="PSP")
           && ff7->psx_block_type(s)==0xA0)
        {//if empty region string and a virtual memcard format and dir frame says empty.
            ff7->clearslot(s); //file_modified(false);//checking only
        }
        //Clear all check boxes and index's
        ui->cb_replay->setCurrentIndex(0);
        ui->cb_bombing_int->setChecked(Qt::Unchecked);
        ui->cb_field_help->setChecked(Qt::Unchecked);
        ui->cb_battle_targets->setChecked(Qt::Unchecked);
        ui->cb_ruby_dead->setChecked(Qt::Unchecked);
        ui->cb_emerald_dead->setChecked(Qt::Unchecked);
        ui->cb_visible_bronco->setChecked(Qt::Unchecked);
        ui->cb_visible_buggy->setChecked(Qt::Unchecked);
        ui->cb_visible_highwind->setChecked(Qt::Unchecked);
        ui->cb_visible_wild_chocobo->setChecked(Qt::Unchecked);
        ui->cb_visible_yellow_chocobo->setChecked(Qt::Unchecked);
        ui->cb_visible_green_chocobo->setChecked(Qt::Unchecked);
        ui->cb_visible_blue_chocobo->setChecked(Qt::Unchecked);
        ui->cb_visible_black_chocobo->setChecked(Qt::Unchecked);
        ui->cb_visible_gold_chocobo->setChecked(Qt::Unchecked);
        if((ff7->slot[s].ruby_emerald) &(1<<3)){ui->cb_ruby_dead->setChecked(Qt::Checked);}
        if((ff7->slot[s].ruby_emerald)& (1<<4)){ui->cb_emerald_dead->setChecked(Qt::Checked);}
        if((ff7->slot[s].field_help)& (1<<0)){ui->cb_field_help->setChecked(Qt::Checked);}
        if((ff7->slot[s].tut_sub)& (1<<6)){ui->cb_battle_targets->setChecked(Qt::Checked);}
        //item_preview->setItem(-1);//reset.
        /*~~~~Set Region info and icon~~~~*/
        ui->lbl_sg_region->setText(ff7->region(s).mid(0,ff7->region(s).lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S")+1,2).toInt()-1);
        if (ff7->type() != "PC") //we Display an icon. for all formats except for pc
        {
            SaveIcon ico(ff7->slot_header(s).mid(96,160));
            ui->lbl_slot_icon->setPixmap(ico.icon().scaledToHeight(64,Qt::SmoothTransformation));
        }
        /*~~~~~Load Game Options~~~~~*/

        if((ff7->slot[s].options1)& (1<<0)){ui->combo_sound->setCurrentIndex(1);}
        else{ui->combo_sound->setCurrentIndex(0);}

        if((ff7->slot[s].options1) & (1<<2)){ui->combo_control->setCurrentIndex(1);}
        else{ui->combo_control->setCurrentIndex(0);}

        if((ff7->slot[s].options1)&(1<<4)){ui->combo_cursor->setCurrentIndex(1);}
        else{ui->combo_cursor->setCurrentIndex(0);}

        if((ff7->slot[s].options1)&(1<<6)){ui->combo_atb->setCurrentIndex(1);}
        else if((ff7->slot[s].options1)&(1<<7)){ui->combo_atb->setCurrentIndex(2);}
        else{ui->combo_atb->setCurrentIndex(0);}

        ui->slide_battlespeed->setValue(ff7->slot[s].battlespeed);
        ui->slide_battlemspeed->setValue(ff7->slot[s].battlemspeed);
        ui->slide_fieldmspeed->setValue(ff7->slot[s].fieldmspeed);
        if((ff7->slot[s].options2)&(1<<0)){ui->combo_camera->setCurrentIndex(1);}
        else{ui->combo_camera->setCurrentIndex(0);}
        if(((ff7->slot[s].options2)&(1<<2)) && ((ff7->slot[s].options2)&(1<<3))){ui->combo_magic_order->setCurrentIndex(3);}
        else if(((ff7->slot[s].options2)&(1<<2)) && ((ff7->slot[s].options2)&(1<<4))){ui->combo_magic_order->setCurrentIndex(5);}
        else if((ff7->slot[s].options2)&(1<<2)){ui->combo_magic_order->setCurrentIndex(1);}
        else if((ff7->slot[s].options2)&(1<<3)){ui->combo_magic_order->setCurrentIndex(2);}
        else if((ff7->slot[s].options2)&(1<<4)){ui->combo_magic_order->setCurrentIndex(4);}
        else{ui->combo_magic_order->setCurrentIndex(0);}
        if((ff7->slot[s].options2)&(1<<6)){ui->cb_battle_help->setCheckState(Qt::Checked);}
        else{ui->cb_battle_help->setCheckState(Qt::Unchecked);}

        //CONTROLLER MAPPING
        ui->combo_button_1->setCurrentIndex(ff7->slot[s].controller_map[0]);
        ui->combo_button_2->setCurrentIndex(ff7->slot[s].controller_map[1]);
        ui->combo_button_3->setCurrentIndex(ff7->slot[s].controller_map[2]);
        ui->combo_button_4->setCurrentIndex(ff7->slot[s].controller_map[3]);
        ui->combo_button_5->setCurrentIndex(ff7->slot[s].controller_map[4]);
        ui->combo_button_6->setCurrentIndex(ff7->slot[s].controller_map[5]);
        ui->combo_button_7->setCurrentIndex(ff7->slot[s].controller_map[6]);
        ui->combo_button_8->setCurrentIndex(ff7->slot[s].controller_map[7]);
        ui->combo_button_9->setCurrentIndex(ff7->slot[s].controller_map[8]);
        ui->combo_button_10->setCurrentIndex(ff7->slot[s].controller_map[9]);
        ui->combo_button_11->setCurrentIndex(ff7->slot[s].controller_map[10]);
        ui->combo_button_12->setCurrentIndex(ff7->slot[s].controller_map[11]);
        ui->combo_button_13->setCurrentIndex(ff7->slot[s].controller_map[12]);
        ui->combo_button_14->setCurrentIndex(ff7->slot[s].controller_map[13]);
        ui->combo_button_15->setCurrentIndex(ff7->slot[s].controller_map[14]);
        ui->combo_button_16->setCurrentIndex(ff7->slot[s].controller_map[15]);
        //hide buttons config if not debug or non pc save
        if(ff7->type() !="PC" || ui->action_show_debug->isChecked()){ui->group_controller_mapping->setVisible(1);}
        else{ui->group_controller_mapping->setVisible(0);}

        /*~~~~~End Options Loading~~~~~*/
        ui->sb_coster_1->setValue(ff7->slot[s].coster_1);
        ui->sb_coster_2->setValue(ff7->slot[s].coster_2);
        ui->sb_coster_3->setValue(ff7->slot[s].coster_3);
        /*~~~~~~~Set up location Data~~~~~~~*/
        ui->sb_coordx->setValue(ff7->slot[s].coord.x);
        ui->sb_coordy->setValue(ff7->slot[s].coord.y);
        ui->sb_coordz->setValue(ff7->slot[s].coord.z);
        ui->line_location->clear();

        ui->line_location->setText(ff7->location(s));

        ui->sb_map_id->setValue(ff7->slot[s].mapid);
        ui->sb_loc_id->setValue(ff7->slot[s].locationid);
        switch(ui->combo_map_controls->currentIndex())
        {
        case 0: ui->slide_world_x->setValue(ff7->slot[s].l_world & 0x7FFFF);
                ui->slide_world_y->setValue(ff7->slot[s].l_world2& 0x3FFFF);
                break;
        case 1: ui->slide_world_x->setValue(ff7->slot[s].tc_world & 0x7FFFF);
                ui->slide_world_y->setValue(ff7->slot[s].tc_world2& 0x3FFFF);
                break;
        case 2: ui->slide_world_x->setValue(ff7->slot[s].bh_world & 0x7FFFF);
                ui->slide_world_y->setValue(ff7->slot[s].bh_world2& 0x3FFFF);
                break;
        case 3: ui->slide_world_x->setValue(ff7->slot[s].sub_world & 0x7FFFF);
                ui->slide_world_y->setValue(ff7->slot[s].sub_world2& 0x3FFFF);
                break;
        case 4: ui->slide_world_x->setValue(ff7->slot[s].uw_world & 0x7FFFF);
                ui->slide_world_y->setValue(ff7->slot[s].uw_world2& 0x3FFFF);
                break;
        case 5: ui->slide_world_x->setValue(ff7->slot[s].durw_world & 0x7FFFF);
                ui->slide_world_y->setValue(ff7->slot[s].durw_world2& 0x3FFFF);
                break;
        case 6: /* Do Nothing. Don't know emerald weapon Coords
                ui->slide_world_x->setValue(ff7->slot[s].ew_world & 0x7FFFF);
                ui->slide_world_y->setValue(ff7->slot[s].ew_world2& 0x3FFFF);
                */
                break;
        }
        //WORLD TAB
        ui->leader_x->setValue((ff7->slot[s].l_world) & 0x7FFFF);
        ui->leader_id->setValue((ff7->slot[s].l_world >> 19)&0x1F);
        ui->leader_angle->setValue((ff7->slot[s].l_world) >> 24);
        ui->leader_y->setValue((ff7->slot[s].l_world2) & 0x3FFFF);
        ui->leader_z->setValue((ff7->slot[s].l_world2) >> 18);

        ui->durw_x->setValue((ff7->slot[s].durw_world) & 0x7FFFF);
        ui->durw_id->setValue((ff7->slot[s].durw_world >> 19)&0x1F);
        ui->durw_angle->setValue((ff7->slot[s].durw_world) >> 24);
        ui->durw_y->setValue((ff7->slot[s].durw_world2) & 0x3FFFF);
        ui->durw_z->setValue((ff7->slot[s].durw_world2) >> 18);

        /* Do Nothing. Don't know emerald weapon Coords
        ui->ew_x->setValue((ff7->slot[s].ew_world) & 0x7FFFF);
        ui->ew_id->setValue((ff7->slot[s].ew_world >> 19)&0x1F);
        ui->ew_angle->setValue((ff7->slot[s].ew_world) >> 24);
        ui->ew_y->setValue((ff7->slot[s].ew_world2) & 0x3FFFF);
        ui->ew_z->setValue((ff7->slot[s].ew_world2) >> 18);
        */

        ui->uw_x->setValue((ff7->slot[s].uw_world) & 0x7FFFF);
        ui->uw_id->setValue((ff7->slot[s].uw_world >> 19)&0x1F);
        ui->uw_angle->setValue((ff7->slot[s].uw_world) >> 24);
        ui->uw_y->setValue((ff7->slot[s].uw_world2) & 0x3FFFF);
        ui->uw_z->setValue((ff7->slot[s].uw_world2) >> 18);

        ui->tc_x->setValue((ff7->slot[s].tc_world) & 0x7FFFF);
        ui->tc_id->setValue((ff7->slot[s].tc_world >> 19)&0x1F);
        ui->tc_angle->setValue((ff7->slot[s].tc_world) >> 24);
        ui->tc_y->setValue((ff7->slot[s].tc_world2) & 0x3FFFF);
        ui->tc_z->setValue((ff7->slot[s].tc_world2) >> 18);

        ui->bh_x->setValue((ff7->slot[s].bh_world) & 0x7FFFF);
        ui->bh_id->setValue((ff7->slot[s].bh_world >> 19)&0x1F);

        switch(ui->bh_id->value())
        {
            case 0:ui->combo_highwind_buggy->setCurrentIndex(0);break;//empty
            case 6:ui->combo_highwind_buggy->setCurrentIndex(1);break;//buggy
            case 3:ui->combo_highwind_buggy->setCurrentIndex(2);break;//highwind
            default:QMessageBox::information(this,tr("Black Chocobo"),tr("Unknown Id in Buggy/Highwind Location"));break;
        }
        ui->bh_angle->setValue((ff7->slot[s].bh_world) >> 24);
        ui->bh_y->setValue((ff7->slot[s].bh_world2) & 0x3FFFF);
        ui->bh_z->setValue((ff7->slot[s].bh_world2) >> 18);

        ui->sub_x->setValue((ff7->slot[s].sub_world) & 0x7FFFF);
        ui->sub_id->setValue((ff7->slot[s].sub_world >> 19)&0x1F);
        ui->sub_angle->setValue((ff7->slot[s].sub_world) >> 24);
        ui->sub_y->setValue((ff7->slot[s].sub_world2) & 0x3FFFF);
        ui->sub_z->setValue((ff7->slot[s].sub_world2) >> 18);


        if((1 << 0) & ff7->slot[s].world_map_vehicles){ui->cb_visible_buggy->setChecked(Qt::Checked);}
        if((1 << 2) & ff7->slot[s].world_map_vehicles){ui->cb_visible_bronco->setChecked(Qt::Checked);}
        if((1 << 4) & ff7->slot[s].world_map_vehicles){ui->cb_visible_highwind->setChecked(Qt::Checked);}

        if((1 << 0) & ff7->slot[s].world_map_chocobos){ui->cb_visible_wild_chocobo->setChecked(Qt::Checked);}
        if((1 << 2) & ff7->slot[s].world_map_chocobos){ui->cb_visible_yellow_chocobo->setChecked(Qt::Checked);}
        if((1 << 3) & ff7->slot[s].world_map_chocobos){ui->cb_visible_green_chocobo->setChecked(Qt::Checked);}
        if((1 << 4) & ff7->slot[s].world_map_chocobos){ui->cb_visible_blue_chocobo->setChecked(Qt::Checked);}
        if((1 << 5) & ff7->slot[s].world_map_chocobos){ui->cb_visible_black_chocobo->setChecked(Qt::Checked);}
        if((1 << 6) & ff7->slot[s].world_map_chocobos){ui->cb_visible_gold_chocobo->setChecked(Qt::Checked);}


        for (int i=0;i<6;i++)//flyers
        {
            if ((1 << i) & ff7->slot[s].turtleflyers){ui->list_flyers->item(i)->setCheckState(Qt::Checked);}
            else{ui->list_flyers->item(i)->setCheckState(Qt::Unchecked);}
        }

        for (int i=0;i<9;i++)//phsmask
        {
            if ((1 << i) & ff7->slot[s].phsmask){ui->list_phs_chars->item(i)->setCheckState(Qt::Unchecked);}
            else{ui->list_phs_chars->item(i)->setCheckState(Qt::Checked);}
        }
        for (int i=0;i<9;i++)//unlocked
        {
            if ((1 << i) & ff7->slot[s].unlockedchars){ui->list_chars_unlocked->item(i)->setCheckState(Qt::Checked);}
            else{ui->list_chars_unlocked->item(i)->setCheckState(Qt::Unchecked);}
        }
        for (int i=0;i<10;i++)//visible_menu
        {
            if ((1 << i) & ff7->slot[s].menu_visible){ui->list_menu_visible->item(i)->setCheckState(Qt::Checked);}
            else{ui->list_menu_visible->item(i)->setCheckState(Qt::Unchecked);}
        }
        for (int i=0;i<10;i++)//menu_locked
        {
            if ((1 << i) & ff7->slot[s].menu_locked){ui->list_menu_locked->item(i)->setCheckState(Qt::Checked);}
            else{ui->list_menu_locked->item(i)->setCheckState(Qt::Unchecked);}
        }
        for (int i=0;i<51;i++)// key items
        {
            if (ff7->slot[s].keyitems[i/8] & (1 << (i%8))){ui->list_keyitems->item(i)->setCheckState(Qt::Checked);}
            else{ ui->list_keyitems->item(i)->setCheckState(Qt::Unchecked);}
        }
        /*~~~~~party combo boxes (checking for empty slots)~~~*/
        if (ff7->Party(s,0) >= 0x0C){ui->combo_party1->setCurrentIndex(12);}
        else{ui->combo_party1->setCurrentIndex(ff7->Party(s,0));}
        if (ff7->Party(s,1) >= 0x0C){ui->combo_party2->setCurrentIndex(12);}
        else{ui->combo_party2->setCurrentIndex(ff7->Party(s,1));}
        if (ff7->Party(s,2) >= 0x0C){ui->combo_party3->setCurrentIndex(12);}
        else{ui->combo_party3->setCurrentIndex(ff7->Party(s,2));}

        ui->sb_gil->setValue(ff7->Gil(s));
        ui->sb_gp->setValue(ff7->Gp(s));
        ui->sb_runs->setValue(ff7->Runs(s));
        ui->sb_battles->setValue(ff7->Battles(s));
        ui->sb_steps->setValue(ff7->slot[s].steps);
        ui->sb_love_barret->setValue(ff7->slot[s].love.barret);
        ui->sb_love_tifa->setValue(ff7->slot[s].love.tifa);
        ui->sb_love_aeris->setValue(ff7->slot[s].love.aeris);
        ui->sb_love_yuffie->setValue(ff7->slot[s].love.yuffie);
        ui->sb_time_hour->setValue(ff7->slot[s].time / 3600);
        ui->sb_time_min->setValue(ff7->slot[s].time/60%60);
        ui->sb_time_sec->setValue(ff7->slot[s].time -((ui->sb_time_hour->value()*3600)+ui->sb_time_min->value()*60));

        dialog_preview->SetULeft (ff7->Dialog_UL(s));
        dialog_preview->SetURight(ff7->Dialog_UR(s));
        dialog_preview->SetLLeft (ff7->Dialog_LL(s));
        dialog_preview->SetLRight(ff7->Dialog_LR(s));

        if((ff7->slot[s].materiacaves)& (1<<0)){ui->cb_materiacave_1->setChecked(Qt::Checked);}
        else{ui->cb_materiacave_1->setChecked(Qt::Unchecked);}
        if((ff7->slot[s].materiacaves)& (1<<1)){ui->cb_materiacave_2->setChecked(Qt::Checked);}
        else{ui->cb_materiacave_2->setChecked(Qt::Unchecked);}
        if((ff7->slot[s].materiacaves)& (1<<2)){ui->cb_materiacave_3->setChecked(Qt::Checked);}
        else{ui->cb_materiacave_3->setChecked(Qt::Unchecked);}
        if((ff7->slot[s].materiacaves)& (1<<3)){ui->cb_materiacave_4->setChecked(Qt::Checked);}
        else{ui->cb_materiacave_4->setChecked(Qt::Unchecked);}
        if((ff7->slot[s].yuffieforest)& (1<<0)){ui->cb_yuffieforest->setChecked(Qt::Checked);}
        else{ui->cb_yuffieforest->setChecked(Qt::Unchecked);}
        /*~~~~~Stolen Materia~~~~~~~*/
        QTableWidgetItem *newItem;
        ui->tbl_materia_2->reset();
        ui->tbl_materia_2->clearContents();
        ui->tbl_materia_2->setColumnWidth(0,(ui->tbl_materia_2->width()*.65));
        ui->tbl_materia_2->setColumnWidth(1,(ui->tbl_materia_2->width()*.25));
        ui->tbl_materia_2->setRowCount(48);
        for(int mat=0;mat<48;mat++) //materias stolen by yuffie
        {
            QString ap;
            quint8 current_id = ff7->stolenMateriaId(s,mat);
            if (current_id !=FF7Materia::EmptyId)
            {
                newItem = new QTableWidgetItem(QPixmap::fromImage(Materias.Image(current_id)),Materias.Name(current_id),0);
                ui->tbl_materia_2->setItem(mat,0,newItem);
                qint32 current_ap = ff7->stolenMateriaAp(s,mat);
                if (current_ap == FF7Materia::MaxMateriaAp){newItem =new QTableWidgetItem(tr("Master"));ui->tbl_materia_2->setItem(mat,1,newItem);}
                else{newItem =new QTableWidgetItem(ap.setNum(current_ap));ui->tbl_materia_2->setItem(mat,1,newItem);}
            }
            else
            {
                newItem = new QTableWidgetItem(tr("===Empty Slot==="),0);
                ui->tbl_materia_2->setItem(mat,0,newItem);
            }
        }
        //SnowBoard Mini Game Data.
        ui->sbSnowBegMin->setValue((ff7->snowboardTime(s,0)/1000)/60%60);
        ui->sbSnowBegSec->setValue((ff7->snowboardTime(s,0)/1000)-(ui->sbSnowBegMin->value()*60));
        ui->sbSnowBegMsec->setValue(ff7->snowboardTime(s,0)%1000);
        ui->sbSnowBegScore->setValue(ff7->snowboardScore(s,0));

        ui->sbSnowExpMin->setValue((ff7->snowboardTime(s,1)/1000)/60%60);
        ui->sbSnowExpSec->setValue((ff7->snowboardTime(s,1)/1000)-(ui->sbSnowExpMin->value()*60));
        ui->sbSnowExpMsec->setValue(ff7->snowboardTime(s,1)%1000);
        ui->sbSnowExpScore->setValue(ff7->snowboardScore(s,1));

        ui->sbSnowCrazyMin->setValue((ff7->snowboardTime(s,2)/1000)/60%60);
        ui->sbSnowCrazySec->setValue((ff7->snowboardTime(s,2)/1000)-(ui->sbSnowCrazyMin->value()*60));
        ui->sbSnowCrazyMsec->setValue(ff7->snowboardTime(s,2)%1000);
        ui->sbSnowCrazyScore->setValue(ff7->snowboardScore(s,2));

        ui->sb_BikeHighScore->setValue(ff7->BikeHighScore(s));
        ui->sb_BattlePoints->setValue(ff7->battlePoints(s));

        load=false;
        // all functions should set load on their own.
        /*~~~~~Call External Functions~~~~~~~*/
        itemlist->setItems(ff7->items(s));
        setmenu(newgame);
        itemupdate();
        chocobo_refresh();
        materiaupdate();
        progress_update();
        set_char_buttons();
        if(ui->action_show_debug->isChecked()){testdata_refresh();}

        switch(curchar)
        {
            case 0: ui->btn_cloud->click();break;
            case 1: ui->btn_barret->click();break;
            case 2: ui->btn_tifa->click();break;
            case 3: ui->btn_aeris->click();break;
            case 4: ui->btn_red->click();break;
            case 5: ui->btn_yuffie->click();break;
            case 6: ui->btn_cait->click();break;
            case 7: ui->btn_vincent->click();break;
            case 8: ui->btn_cid->click();break;
        }
    }
}/*~~~~~~~~~~~~~~~~~~~~End GUIREFRESH ~~~~~~~~~~~~~~~~~*/
void MainWindow::set_char_buttons()
{
    ui->btn_cloud->setIcon(Chars.Icon(ff7->charID(s,0)));
    ui->btn_barret->setIcon(Chars.Icon(ff7->charID(s,1)));
    ui->btn_tifa->setIcon(Chars.Icon(ff7->charID(s,2)));
    ui->btn_aeris->setIcon(Chars.Icon(ff7->charID(s,3)));
    ui->btn_red->setIcon(Chars.Icon(ff7->charID(s,4)));
    ui->btn_yuffie->setIcon(Chars.Icon(ff7->charID(s,5)));
    ui->btn_cait->setIcon(Chars.Icon(ff7->charID(s,6)));
    ui->btn_vincent->setIcon(Chars.Icon(ff7->charID(s,7)));
    ui->btn_cid->setIcon(Chars.Icon(ff7->charID(s,8)));
}
void MainWindow::progress_update()
{
    load=true;

    ui->sb_curdisc->setValue(ff7->slot[s].disc);
    ui->sb_turkschruch->setValue(ff7->slot[s].aeris_chruch);
    ui->sb_donprog->setValue(ff7->slot[s].donprogress);
    ui->sb_mprogress->setValue(ff7->slot[s].mprogress);
    ui->combo_s7_slums->setCurrentIndex(0);
    if(ff7->slot[s].intbombing == 0x14){ui->cb_bombing_int->setChecked(Qt::Checked);}

    if((ff7->slot[s].bm_progress1)& (1<<0)){ui->cb_bm1_1->setChecked(Qt::Checked);}
    else{ui->cb_bm1_1->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress1)& (1<<1)){ui->cb_bm1_2->setChecked(Qt::Checked);}
    else{ui->cb_bm1_2->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress1)& (1<<2)){ui->cb_bm1_3->setChecked(Qt::Checked);}
    else{ui->cb_bm1_3->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress1)& (1<<3)){ui->cb_bm1_4->setChecked(Qt::Checked);}
    else{ui->cb_bm1_4->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress1)& (1<<4)){ui->cb_bm1_5->setChecked(Qt::Checked);}
    else{ui->cb_bm1_5->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress1)& (1<<5)){ui->cb_bm1_6->setChecked(Qt::Checked);}
    else{ui->cb_bm1_6->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress1)& (1<<6)){ui->cb_bm1_7->setChecked(Qt::Checked);}
    else{ui->cb_bm1_7->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress1)& (1<<7)){ui->cb_bm1_8->setChecked(Qt::Checked);}
    else{ui->cb_bm1_8->setChecked(Qt::Unchecked);}

    if((ff7->slot[s].bm_progress2)& (1<<0)){ui->cb_bm2_1->setChecked(Qt::Checked);}
    else{ui->cb_bm2_1->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress2)& (1<<1)){ui->cb_bm2_2->setChecked(Qt::Checked);}
    else{ui->cb_bm2_2->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress2)& (1<<2)){ui->cb_bm2_3->setChecked(Qt::Checked);}
    else{ui->cb_bm2_3->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress2)& (1<<3)){ui->cb_bm2_4->setChecked(Qt::Checked);}
    else{ui->cb_bm2_4->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress2)& (1<<4)){ui->cb_bm2_5->setChecked(Qt::Checked);}
    else{ui->cb_bm2_5->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress2)& (1<<5)){ui->cb_bm2_6->setChecked(Qt::Checked);}
    else{ui->cb_bm2_6->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress2)& (1<<6)){ui->cb_bm2_7->setChecked(Qt::Checked);}
    else{ui->cb_bm2_7->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress2)& (1<<7)){ui->cb_bm2_8->setChecked(Qt::Checked);}
    else{ui->cb_bm2_8->setChecked(Qt::Unchecked);}

    if((ff7->slot[s].bm_progress3)& (1<<0)){ui->cb_bm3_1->setChecked(Qt::Checked);}
    else{ui->cb_bm3_1->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress3)& (1<<1)){ui->cb_bm3_2->setChecked(Qt::Checked);}
    else{ui->cb_bm3_2->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress3)& (1<<2)){ui->cb_bm3_3->setChecked(Qt::Checked);}
    else{ui->cb_bm3_3->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress3)& (1<<3)){ui->cb_bm3_4->setChecked(Qt::Checked);}
    else{ui->cb_bm3_4->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress3)& (1<<4)){ui->cb_bm3_5->setChecked(Qt::Checked);}
    else{ui->cb_bm3_5->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress3)& (1<<5)){ui->cb_bm3_6->setChecked(Qt::Checked);}
    else{ui->cb_bm3_6->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress3)& (1<<6)){ui->cb_bm3_7->setChecked(Qt::Checked);}
    else{ui->cb_bm3_7->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].bm_progress3)& (1<<7)){ui->cb_bm3_8->setChecked(Qt::Checked);}
    else{ui->cb_bm3_8->setChecked(Qt::Unchecked);}

    if((ff7->slot[s].z_26[0])& (1<<0)){ui->cb_s7pl_1->setChecked(Qt::Checked);}
    else{ui->cb_s7pl_1->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[0])& (1<<1)){ui->cb_s7pl_2->setChecked(Qt::Checked);}
    else{ui->cb_s7pl_2->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[0])& (1<<2)){ui->cb_s7pl_3->setChecked(Qt::Checked);}
    else{ui->cb_s7pl_3->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[0])& (1<<3)){ui->cb_s7pl_4->setChecked(Qt::Checked);}
    else{ui->cb_s7pl_4->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[0])& (1<<4)){ui->cb_s7pl_5->setChecked(Qt::Checked);}
    else{ui->cb_s7pl_5->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[0])& (1<<5)){ui->cb_s7pl_6->setChecked(Qt::Checked);}
    else{ui->cb_s7pl_6->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[0])& (1<<6)){ui->cb_s7pl_7->setChecked(Qt::Checked);}
    else{ui->cb_s7pl_7->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[0])& (1<<7)){ui->cb_s7pl_8->setChecked(Qt::Checked);}
    else{ui->cb_s7pl_8->setChecked(Qt::Unchecked);}

    if((ff7->slot[s].z_26[8])& (1<<0)){ui->cb_s7ts_1->setChecked(Qt::Checked);}
    else{ui->cb_s7ts_1->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[8])& (1<<1)){ui->cb_s7ts_2->setChecked(Qt::Checked);}
    else{ui->cb_s7ts_2->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[8])& (1<<2)){ui->cb_s7ts_3->setChecked(Qt::Checked);}
    else{ui->cb_s7ts_3->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[8])& (1<<3)){ui->cb_s7ts_4->setChecked(Qt::Checked);}
    else{ui->cb_s7ts_4->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[8])& (1<<4)){ui->cb_s7ts_5->setChecked(Qt::Checked);}
    else{ui->cb_s7ts_5->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[8])& (1<<5)){ui->cb_s7ts_6->setChecked(Qt::Checked);}
    else{ui->cb_s7ts_6->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[8])& (1<<6)){ui->cb_s7ts_7->setChecked(Qt::Checked);}
    else{ui->cb_s7ts_7->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_26[8])& (1<<7)){ui->cb_s7ts_8->setChecked(Qt::Checked);}
    else{ui->cb_s7ts_8->setChecked(Qt::Unchecked);}

    if((ff7->slot[s].z_23[26])& (1<<0)){ui->cb_s5_1->setChecked(Qt::Checked);}
    else{ui->cb_s5_1->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_23[26])& (1<<1)){ui->cb_s5_2->setChecked(Qt::Checked);}
    else{ui->cb_s5_2->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_23[26])& (1<<2)){ui->cb_s5_3->setChecked(Qt::Checked);}
    else{ui->cb_s5_3->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_23[26])& (1<<3)){ui->cb_s5_4->setChecked(Qt::Checked);}
    else{ui->cb_s5_4->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_23[26])& (1<<4)){ui->cb_s5_5->setChecked(Qt::Checked);}
    else{ui->cb_s5_5->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_23[26])& (1<<5)){ui->cb_s5_6->setChecked(Qt::Checked);}
    else{ui->cb_s5_6->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_23[26])& (1<<6)){ui->cb_s5_7->setChecked(Qt::Checked);}
    else{ui->cb_s5_7->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].z_23[26])& (1<<7)){ui->cb_s5_8->setChecked(Qt::Checked);}
    else{ui->cb_s5_8->setChecked(Qt::Unchecked);}

    if((ff7->slot[s].midgartrainflags)& (1<<0)){ui->cb_midgartrain_1->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_1->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].midgartrainflags)& (1<<1)){ui->cb_midgartrain_2->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_2->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].midgartrainflags)& (1<<2)){ui->cb_midgartrain_3->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_3->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].midgartrainflags)& (1<<3)){ui->cb_midgartrain_4->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_4->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].midgartrainflags)& (1<<4)){ui->cb_midgartrain_5->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_5->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].midgartrainflags)& (1<<5)){ui->cb_midgartrain_6->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_6->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].midgartrainflags)& (1<<6)){ui->cb_midgartrain_7->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_7->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].midgartrainflags)& (1<<7)){ui->cb_midgartrain_8->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_8->setChecked(Qt::Unchecked);}

    if(ff7->slot[s].z_26[1] ==0x00 &&
      ff7->slot[s].z_26[2] ==0x00 &&
      ff7->slot[s].z_26[3] ==0x00 &&
      ff7->slot[s].z_26[4] ==0x00 &&
      ff7->slot[s].z_26[5] ==0x00 &&
      ff7->slot[s].z_26[6] ==0x00   )
      {ui->combo_s7_slums->setCurrentIndex(1);}

    else if((ff7->slot[s].z_26[1] == 0xFF ||ff7->slot[s].z_26[1] == 0xBF) &&
      (ff7->slot[s].z_26[2] == 0x03 ||ff7->slot[s].z_26[2] == 0x51) &&
      (ff7->slot[s].z_26[3] == 0x04 ||ff7->slot[s].z_26[3] == 0x05) &&
      (ff7->slot[s].z_26[4] == 0x0F ||ff7->slot[s].z_26[4] == 0x17) &&
      (ff7->slot[s].z_26[5] == 0x1F ||ff7->slot[s].z_26[5] == 0x5D) &&
      (ff7->slot[s].z_26[6] == 0x6F ||ff7->slot[s].z_26[6] == 0xEF)   )
      {ui->combo_s7_slums->setCurrentIndex(2);}

    else if((ff7->slot[s].z_26[2]== 0x13)){ui->combo_s7_slums->setCurrentIndex(3);}

    else {ui->combo_s7_slums->setCurrentIndex(0);}

    load=false;
}
/*~~~~~~~~~~~~~~~~~~~~Chocobo Refresh~~~~~~~~~~~~~~~~*/
void MainWindow::chocobo_refresh()
{
    load=true;
    ui->sb_stables_owned->setValue(ff7->slot[s].stables);
    ui->lcd_stables_occupied->display(ff7->slot[s].stablesoccupied);

    if((ff7->slot[s].chocobomask)& (1<<0)){ui->box_stable1->setChecked(1);}
    else{ui->box_stable1->setChecked(0);}
    if((ff7->slot[s].chocobomask)& (1<<1)){ui->box_stable2->setChecked(1);}
    else{ui->box_stable2->setChecked(0);}
    if((ff7->slot[s].chocobomask)& (1<<2)){ui->box_stable3->setChecked(1);}
    else{ui->box_stable3->setChecked(0);}
    if((ff7->slot[s].chocobomask)& (1<<3)){ui->box_stable4->setChecked(1);}
    else{ui->box_stable4->setChecked(0);}
    if((ff7->slot[s].chocobomask)& (1<<4)){ui->box_stable5->setChecked(1);}
    else{ui->box_stable5->setChecked(0);}
    if((ff7->slot[s].chocobomask)& (1<<5)){ui->box_stable6->setChecked(1);}
    else{ui->box_stable6->setChecked(0);}

    chocobo_stable_1->SetChocobo(ff7->chocobo(s,0),ff7->chocoName(s,0),ff7->chocoCantMate(s,0),ff7->chocoStamina(s,0));
    chocobo_stable_2->SetChocobo(ff7->chocobo(s,1),ff7->chocoName(s,1),ff7->chocoCantMate(s,1),ff7->chocoStamina(s,1));
    chocobo_stable_3->SetChocobo(ff7->chocobo(s,2),ff7->chocoName(s,2),ff7->chocoCantMate(s,2),ff7->chocoStamina(s,2));
    chocobo_stable_4->SetChocobo(ff7->chocobo(s,3),ff7->chocoName(s,3),ff7->chocoCantMate(s,3),ff7->chocoStamina(s,3));
    chocobo_stable_5->SetChocobo(ff7->chocobo(s,4),ff7->chocoName(s,4),ff7->chocoCantMate(s,4),ff7->chocoStamina(s,4));
    chocobo_stable_6->SetChocobo(ff7->chocobo(s,5),ff7->chocoName(s,5),ff7->chocoCantMate(s,5),ff7->chocoStamina(s,5));
    //set the penned chocobos
    ui->combo_pen1->setCurrentIndex(ff7->ChocoPen(s,0));
    ui->combo_pen2->setCurrentIndex(ff7->ChocoPen(s,1));
    ui->combo_pen3->setCurrentIndex(ff7->ChocoPen(s,2));
    ui->combo_pen4->setCurrentIndex(ff7->ChocoPen(s,3));
    load=false;
}/*~~~~~~~~~~~End Chocobo Slots~~~~~~~~~*/

/*~~~~~~~~~Test Data~~~~~~~~~~~*/
void MainWindow::testdata_refresh()
{
    load=true;

   //TEST TAB

    ui->cb_tut_sub->setChecked(Qt::Unchecked);
    ui->sb_timer_time_hour->setValue(ff7->slot[s].timer[0]);
    ui->sb_timer_time_min->setValue(ff7->slot[s].timer[1]);
    ui->sb_timer_time_sec->setValue(ff7->slot[s].timer[2]);

    ui->sb_b_love_aeris->setValue(ff7->slot[s].b_love.aeris);
    ui->sb_b_love_tifa->setValue(ff7->slot[s].b_love.tifa);
    ui->sb_b_love_yuffie->setValue(ff7->slot[s].b_love.yuffie);
    ui->sb_b_love_barret->setValue(ff7->slot[s].b_love.barret);
    ui->sb_u_weapon_hp->setValue(ff7->slot[s].u_weapon_hp[0] |(ff7->slot[s].u_weapon_hp[1] << 8) | (ff7->slot[s].u_weapon_hp[2] << 16));

    if((ff7->slot[s].tut_sub)&(1<<2)){ui->cb_tut_sub->setChecked(Qt::Checked);}

    ui->lcdNumber_6->display(ff7->slot[s].tut_sub);

    if(ff7->slot[s].tut_save == 0x3A){ui->cb_tut_worldsave->setCheckState(Qt::Checked);}
    else if(ff7->slot[s].tut_save ==0x32){ui->cb_tut_worldsave->setCheckState(Qt::PartiallyChecked);}
    else{ui->cb_tut_worldsave->setCheckState(Qt::Unchecked);}
    ui->lcdNumber_7->display(ff7->slot[s].tut_save);

    ui->cb_reg_vinny->setChecked(Qt::Unchecked);
    if(ff7->slot[s].reg_vinny == 0xFF){ui->cb_reg_vinny->setChecked(Qt::Checked);}
    ui->lcdNumber_8->display(ff7->slot[s].reg_vinny);

    ui->cb_reg_yuffie->setChecked(Qt::Unchecked);
    if(ff7->slot[s].reg_yuffie == 0x6F){ui->cb_reg_yuffie->setChecked(Qt::Checked);}
    ui->lcdNumber_9->display(ff7->slot[s].reg_yuffie);

    if((ff7->slot[s].z_11[3])&(1<<0)){ui->cb_farm_items_1->setChecked(1);}
    else{ui->cb_farm_items_1->setChecked(0);}
    if((ff7->slot[s].z_11[3])&(1<<1)){ui->cb_farm_items_2->setChecked(1);}
    else{ui->cb_farm_items_2->setChecked(0);}
    if((ff7->slot[s].z_11[3])&(1<<2)){ui->cb_farm_items_3->setChecked(1);}
    else{ui->cb_farm_items_3->setChecked(0);}
    if((ff7->slot[s].z_11[3])&(1<<3)){ui->cb_farm_items_4->setChecked(1);}
    else{ui->cb_farm_items_4->setChecked(0);}
    if((ff7->slot[s].z_11[3])&(1<<4)){ui->cb_farm_items_5->setChecked(1);}
    else{ui->cb_farm_items_5->setChecked(0);}
    if((ff7->slot[s].z_11[3])&(1<<5)){ui->cb_farm_items_6->setChecked(1);}
    else{ui->cb_farm_items_6->setChecked(0);}
    if((ff7->slot[s].z_11[3])&(1<<6)){ui->cb_farm_items_7->setChecked(1);}
    else{ui->cb_farm_items_7->setChecked(0);}
    if((ff7->slot[s].z_11[3])&(1<<7)){ui->cb_farm_items_8->setChecked(1);}
    else{ui->cb_farm_items_8->setChecked(0);}


    if((ff7->slot[s].tut_sub)& (1<<0)){ui->cb_tut_sub_1->setChecked(Qt::Checked);}
    else{ui->cb_tut_sub_1->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].tut_sub)& (1<<1)){ui->cb_tut_sub_2->setChecked(Qt::Checked);}
    else{ui->cb_tut_sub_2->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].tut_sub)& (1<<2)){ui->cb_tut_sub_3->setChecked(Qt::Checked);}
    else{ui->cb_tut_sub_3->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].tut_sub)& (1<<3)){ui->cb_tut_sub_4->setChecked(Qt::Checked);}
    else{ui->cb_tut_sub_4->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].tut_sub)& (1<<4)){ui->cb_tut_sub_5->setChecked(Qt::Checked);}
    else{ui->cb_tut_sub_5->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].tut_sub)& (1<<5)){ui->cb_tut_sub_6->setChecked(Qt::Checked);}
    else{ui->cb_tut_sub_6->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].tut_sub)& (1<<6)){ui->cb_tut_sub_7->setChecked(Qt::Checked);}
    else{ui->cb_tut_sub_7->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].tut_sub)& (1<<7)){ui->cb_tut_sub_8->setChecked(Qt::Checked);}
    else{ui->cb_tut_sub_8->setChecked(Qt::Unchecked);}
    ui->lcd_tut_sub->display(ff7->slot[s].tut_sub);

    //Snowboard Times.
    load=false;

    unknown_refresh(ui->combo_z_var->currentIndex());
}
/*~~~~~~~~~Char Buttons.~~~~~~~~~~~*/
void MainWindow::on_btn_cloud_clicked()     {curchar=0; char_editor->setChar(ff7->Char(s,0),ff7->charName(s,0));ui->btn_cloud->setIcon(Chars.Icon(ff7->charID(s,curchar)));}
void MainWindow::on_btn_barret_clicked()    {curchar=1; char_editor->setChar(ff7->Char(s,1),ff7->charName(s,1));ui->btn_barret->setIcon(Chars.Icon(ff7->charID(s,curchar)));}
void MainWindow::on_btn_tifa_clicked()      {curchar=2; char_editor->setChar(ff7->Char(s,2),ff7->charName(s,2));ui->btn_tifa->setIcon(Chars.Icon(ff7->charID(s,curchar)));}
void MainWindow::on_btn_aeris_clicked()     {curchar=3; char_editor->setChar(ff7->Char(s,3),ff7->charName(s,3));ui->btn_aeris->setIcon(Chars.Icon(ff7->charID(s,curchar)));}
void MainWindow::on_btn_red_clicked()       {curchar=4; char_editor->setChar(ff7->Char(s,4),ff7->charName(s,4));ui->btn_red->setIcon(Chars.Icon(ff7->charID(s,curchar)));}
void MainWindow::on_btn_yuffie_clicked()    {curchar=5; char_editor->setChar(ff7->Char(s,5),ff7->charName(s,5));ui->btn_yuffie->setIcon(Chars.Icon(ff7->charID(s,curchar)));}
void MainWindow::on_btn_cait_clicked()      {curchar=6; char_editor->setChar(ff7->Char(s,6),ff7->charName(s,6));ui->btn_cait->setIcon(Chars.Icon(ff7->charID(s,curchar)));}
void MainWindow::on_btn_vincent_clicked()   {curchar=7; char_editor->setChar(ff7->Char(s,7),ff7->charName(s,7));ui->btn_vincent->setIcon(Chars.Icon(ff7->charID(s,curchar)));}
void MainWindow::on_btn_cid_clicked()       {curchar=8; char_editor->setChar(ff7->Char(s,8),ff7->charName(s,8));ui->btn_cid->setIcon(Chars.Icon(ff7->charID(s,curchar)));}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Party TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_sb_gil_valueChanged(int value){if(!load){file_modified(true); ff7->setGil(s,value); ff7->setDescGil(s,value);}}
void MainWindow::on_sb_gp_valueChanged(int value){if(!load){file_modified(true); ff7->setGp(s,value);}}
void MainWindow::on_sb_battles_valueChanged(int value){if(!load){file_modified(true); ff7->setBattles(s,value);}}
void MainWindow::on_sb_runs_valueChanged(int value){if(!load){file_modified(true); ff7->setRuns(s,value);}}
void MainWindow::on_combo_party1_currentIndexChanged(int index)
{if(!load){file_modified(true);
    if(index == 0x0C) //empty char slot (index 12)
    {
        ff7->setParty(s,0,0xFF);
        //wipe all desc data if noone is there
        ff7->setDescParty(s,0,ff7->Party(s,0));
        ff7->setDescCurHP(s,0);
        ff7->setDescMaxHP(s,0);
        ff7->setDescCurMP(s,0);
        ff7->setDescMaxMP(s,0);
        ff7->setDescLevel(s,0);
        ff7->setDescName(s,QString(QByteArray(16,0xFF)));
    }
    else
    {
        ff7->setParty(s,0,index);
        ff7->setDescParty(s,0,ff7->Party(s,0));
        // IF ID >8 no char slot so for 9, 10, 11 Use slot 6,7,8 char data.
        if(ff7->Party(s,0)== FF7Char::YoungCloud)
        {
            ff7->setDescCurHP(s,ff7->charCurrentHp(s,6));
            ff7->setDescMaxHP(s,ff7->charMaxHp(s,6));
            ff7->setDescCurMP(s,ff7->charCurrentMp(s,6));
            ff7->setDescMaxMP(s,ff7->charMaxMp(s,6));
            ff7->setDescLevel(s,ff7->charLevel(s,6));
            ff7->setDescName(s,ff7->charName(s,6));
        }
        else if(ff7->Party(s,0)== FF7Char::Sephiroth)
        {
            ff7->setDescCurHP(s,ff7->charCurrentHp(s,7));
            ff7->setDescMaxHP(s,ff7->charMaxHp(s,7));
            ff7->setDescCurMP(s,ff7->charCurrentMp(s,7));
            ff7->setDescMaxMP(s,ff7->charMaxMp(s,7));
            ff7->setDescLevel(s,ff7->charLevel(s,7));
            ff7->setDescName(s,ff7->charName(s,7));
        }
        else if(ff7->Party(s,0)== 11)
        {//chocobo? that never really works.
            ff7->setDescCurHP(s,ff7->charCurrentHp(s,8));
            ff7->setDescMaxHP(s,ff7->charMaxHp(s,8));
            ff7->setDescCurMP(s,ff7->charCurrentMp(s,8));
            ff7->setDescMaxMP(s,ff7->charMaxMp(s,8));
            ff7->setDescLevel(s,ff7->charLevel(s,8));
            ff7->setDescName(s,ff7->charName(s,8));
        }
        else
        {
            ff7->setDescCurHP(s,ff7->charCurrentHp(s,ff7->Party(s,0)));
            ff7->setDescMaxHP(s,ff7->charMaxHp(s,ff7->Party(s,0)));
            ff7->setDescCurMP(s,ff7->charCurrentMp(s,ff7->Party(s,0)));
            ff7->setDescMaxMP(s,ff7->charMaxMp(s,ff7->Party(s,0)));
            ff7->setDescLevel(s,ff7->charLevel(s,ff7->Party(s,0)));
            ff7->setDescName(s,ff7->charName(s,ff7->Party(s,0)));
        }
    }
}}
void MainWindow::on_combo_party2_currentIndexChanged(int index)
{if(!load){file_modified(true);
    if(index == 12){ff7->setParty(s,1,FF7Char::Empty);}
    else{ff7->setParty(s,1,index);}
    //either way set the desc
    ff7->setDescParty(s,1,ff7->Party(s,1));
}}
void MainWindow::on_combo_party3_currentIndexChanged(int index)
{if(!load){file_modified(true);
        if(index == 12){ff7->setParty(s,2,FF7Char::Empty);}
        else{ff7->setParty(s,2,index);}
        //either way set the desc
        ff7->setDescParty(s,2,ff7->Party(s,2));
}}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chocobo Tab~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//set data for stables inside
void MainWindow::on_sb_stables_owned_valueChanged(int value)
{
    if(!load){file_modified(true); ff7->slot[s].stables = value;}
    ui->box_stable1->setEnabled(false);
    ui->box_stable2->setEnabled(false);
    ui->box_stable3->setEnabled(false);
    ui->box_stable4->setEnabled(false);
    ui->box_stable5->setEnabled(false);
    ui->box_stable6->setEnabled(false);
    switch(value)
    {//No Breaks On Purpose.
        case 6:ui->box_stable6->setEnabled(true);
        case 5:ui->box_stable5->setEnabled(true);
        case 4:ui->box_stable4->setEnabled(true);
        case 3:ui->box_stable3->setEnabled(true);
        case 2:ui->box_stable2->setEnabled(true);
        case 1:ui->box_stable1->setEnabled(true);
    }
}
/*~~~~~~~~~Occupied~~~~~~~~~~~*/
void MainWindow::on_box_stable1_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].chocobomask |= (1<<0);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<0);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
void MainWindow::on_box_stable2_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].chocobomask |= (1<<1);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<1);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
void MainWindow::on_box_stable3_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].chocobomask |= (1<<2);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<2);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
void MainWindow::on_box_stable4_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].chocobomask |= (1<<3);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<3);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
void MainWindow::on_box_stable5_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].chocobomask |= (1<<4);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<4);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
void MainWindow::on_box_stable6_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].chocobomask |= (1<<5);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<5);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
/*~~~~~ChocoboStats~~~~~*/
void MainWindow::c1_nameChanged(QString text){if(!load){file_modified(true);ff7->setChocoName(s,0,text);}}
void MainWindow::c1_staminaChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoStamina(s,0,value);}}
void MainWindow::c1_speedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSpeed(s,0,value);}}
void MainWindow::c1_maxspeedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSpeed(s,0,value);}}
void MainWindow::c1_sprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSprintSpeed(s,0,value);}}
void MainWindow::c1_maxsprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSprintSpeed(s,0,value);}}
void MainWindow::c1_sexChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoSex(s,0,index);}}
void MainWindow::c1_typeChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoType(s,0,index);}}
void MainWindow::c1_coopChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoCoop(s,0,value);}}
void MainWindow::c1_accelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoAccel(s,0,value);}}
void MainWindow::c1_intelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoIntelligence(s,0,value);}}
void MainWindow::c1_raceswonChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoRaceswon(s,0,value);}}
void MainWindow::c1_pcountChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPCount(s,0,value);}}
void MainWindow::c1_personalityChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPersonality(s,0,value);}}
void MainWindow::c1_mated_toggled(bool checked){if(!load){file_modified(true);ff7->setChocoCantMate(s,0,checked);}}

void MainWindow::c2_nameChanged(QString text){if(!load){file_modified(true);ff7->setChocoName(s,1,text);}}
void MainWindow::c2_staminaChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoStamina(s,1,value);}}
void MainWindow::c2_speedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSpeed(s,1,value);}}
void MainWindow::c2_maxspeedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSpeed(s,1,value);}}
void MainWindow::c2_sprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSprintSpeed(s,1,value);}}
void MainWindow::c2_maxsprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSprintSpeed(s,1,value);}}
void MainWindow::c2_sexChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoSex(s,1,index);}}
void MainWindow::c2_typeChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoType(s,1,index);}}
void MainWindow::c2_coopChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoCoop(s,1,value);}}
void MainWindow::c2_accelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoAccel(s,1,value);}}
void MainWindow::c2_intelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoIntelligence(s,1,value);}}
void MainWindow::c2_raceswonChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoRaceswon(s,1,value);}}
void MainWindow::c2_pcountChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPCount(s,1,value);}}
void MainWindow::c2_personalityChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPersonality(s,1,value);}}
void MainWindow::c2_mated_toggled(bool checked){if(!load){file_modified(true);ff7->setChocoCantMate(s,1,checked);}}

void MainWindow::c3_nameChanged(QString text){if(!load){file_modified(true);ff7->setChocoName(s,2,text);}}
void MainWindow::c3_staminaChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoStamina(s,2,value);}}
void MainWindow::c3_speedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSpeed(s,2,value);}}
void MainWindow::c3_maxspeedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSpeed(s,2,value);}}
void MainWindow::c3_sprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSprintSpeed(s,2,value);}}
void MainWindow::c3_maxsprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSprintSpeed(s,2,value);}}
void MainWindow::c3_sexChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoSex(s,2,index);}}
void MainWindow::c3_typeChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoType(s,2,index);}}
void MainWindow::c3_coopChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoCoop(s,2,value);}}
void MainWindow::c3_accelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoAccel(s,2,value);}}
void MainWindow::c3_intelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoIntelligence(s,2,value);}}
void MainWindow::c3_raceswonChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoRaceswon(s,2,value);}}
void MainWindow::c3_pcountChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPCount(s,2,value);}}
void MainWindow::c3_personalityChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPersonality(s,2,value);}}
void MainWindow::c3_mated_toggled(bool checked){if(!load){file_modified(true);ff7->setChocoCantMate(s,2,checked);}}

void MainWindow::c4_nameChanged(QString text){if(!load){file_modified(true);ff7->setChocoName(s,3,text);}}
void MainWindow::c4_staminaChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoStamina(s,3,value);}}
void MainWindow::c4_speedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSpeed(s,3,value);}}
void MainWindow::c4_maxspeedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSpeed(s,3,value);}}
void MainWindow::c4_sprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSprintSpeed(s,3,value);}}
void MainWindow::c4_maxsprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSprintSpeed(s,3,value);}}
void MainWindow::c4_sexChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoSex(s,3,index);}}
void MainWindow::c4_typeChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoType(s,3,index);}}
void MainWindow::c4_coopChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoCoop(s,3,value);}}
void MainWindow::c4_accelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoAccel(s,3,value);}}
void MainWindow::c4_intelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoIntelligence(s,3,value);}}
void MainWindow::c4_raceswonChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoRaceswon(s,3,value);}}
void MainWindow::c4_pcountChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPCount(s,3,value);}}
void MainWindow::c4_personalityChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPersonality(s,3,value);}}
void MainWindow::c4_mated_toggled(bool checked){if(!load){file_modified(true);ff7->setChocoCantMate(s,3,checked);}}

void MainWindow::c5_nameChanged(QString text){if(!load){file_modified(true);ff7->setChocoName(s,4,text);}}
void MainWindow::c5_staminaChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoStamina(s,4,value);}}
void MainWindow::c5_speedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSpeed(s,4,value);}}
void MainWindow::c5_maxspeedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSpeed(s,4,value);}}
void MainWindow::c5_sprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSprintSpeed(s,4,value);}}
void MainWindow::c5_maxsprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSprintSpeed(s,4,value);}}
void MainWindow::c5_sexChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoSex(s,4,index);}}
void MainWindow::c5_typeChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoType(s,4,index);}}
void MainWindow::c5_coopChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoCoop(s,4,value);}}
void MainWindow::c5_accelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoAccel(s,4,value);}}
void MainWindow::c5_intelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoIntelligence(s,4,value);}}
void MainWindow::c5_raceswonChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoRaceswon(s,4,value);}}
void MainWindow::c5_pcountChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPCount(s,4,value);}}
void MainWindow::c5_personalityChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPersonality(s,4,value);}}
void MainWindow::c5_mated_toggled(bool checked){if(!load){file_modified(true);ff7->setChocoCantMate(s,4,checked);}}

void MainWindow::c6_nameChanged(QString text){if(!load){file_modified(true);ff7->setChocoName(s,5,text);}}
void MainWindow::c6_staminaChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoStamina(s,5,value);}}
void MainWindow::c6_speedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSpeed(s,5,value);}}
void MainWindow::c6_maxspeedChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSpeed(s,5,value);}}
void MainWindow::c6_sprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoSprintSpeed(s,5,value);}}
void MainWindow::c6_maxsprintChanged(quint16 value){if(!load){file_modified(true); ff7->setChocoMaxSprintSpeed(s,5,value);}}
void MainWindow::c6_sexChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoSex(s,5,index);}}
void MainWindow::c6_typeChanged(quint8 index){if(!load){file_modified(true); ff7->setChocoType(s,5,index);}}
void MainWindow::c6_coopChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoCoop(s,5,value);}}
void MainWindow::c6_accelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoAccel(s,5,value);}}
void MainWindow::c6_intelChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoIntelligence(s,5,value);}}
void MainWindow::c6_raceswonChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoRaceswon(s,5,value);}}
void MainWindow::c6_pcountChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPCount(s,5,value);}}
void MainWindow::c6_personalityChanged(quint8 value){if(!load){file_modified(true); ff7->setChocoPersonality(s,5,value);}}
void MainWindow::c6_mated_toggled(bool checked){if(!load){file_modified(true);ff7->setChocoCantMate(s,5,checked);}}

//set data for pens outside
void MainWindow::on_combo_pen1_currentIndexChanged(int index){if(!load){file_modified(true); ff7->setChocoPen(s,0,index);}}
void MainWindow::on_combo_pen2_currentIndexChanged(int index){if(!load){file_modified(true); ff7->setChocoPen(s,1,index);}}
void MainWindow::on_combo_pen3_currentIndexChanged(int index){if(!load){file_modified(true); ff7->setChocoPen(s,2,index);}}
void MainWindow::on_combo_pen4_currentIndexChanged(int index){if(!load){file_modified(true); ff7->setChocoPen(s,3,index);}}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OTHERS TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_list_phs_chars_clicked(const QModelIndex &index)
{if(!load){file_modified(true);
        int j = index.row();
        if(ui->list_phs_chars->item(j)->checkState() ==Qt::Unchecked){ff7->slot[s].phsmask |=(1 <<j);}
        else{ff7->slot[s].phsmask &= ~(1<<j);}
}}

void MainWindow::on_list_chars_unlocked_clicked(const QModelIndex &index)
{if(!load){file_modified(true);
    int j = index.row();
    if(ui->list_chars_unlocked->item(j)->checkState() ==Qt::Checked){ff7->slot[s].unlockedchars |= (1<<j);}
    else{ff7->slot[s].unlockedchars &= ~(1<<j);}
}}
void MainWindow::on_sb_love_barret_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].love.barret = value;}}
void MainWindow::on_sb_love_aeris_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].love.aeris = value;}}
void MainWindow::on_sb_love_tifa_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].love.tifa = value;}}
void MainWindow::on_sb_love_yuffie_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].love.yuffie = value;}}

void MainWindow::on_sb_time_hour_valueChanged(int value)
{if(!load){file_modified(true);
        ff7->slot[s].time = ((value*3600) + (ui->sb_time_min->value()*60) + (ui->sb_time_sec->value()));ff7->setDescTime(s,ff7->slot[s].time);
}}

void MainWindow::on_sb_time_min_valueChanged(int value)
{if(!load){file_modified(true);
        ff7->slot[s].time = ( (ui->sb_time_hour->value()*3600) + ((value*60)) + (ui->sb_time_sec->value()) );ff7->setDescTime(s,ff7->slot[s].time);
}}

void MainWindow::on_sb_time_sec_valueChanged(int value)
{if(!load){file_modified(true);
        ff7->slot[s].time = ((ui->sb_time_hour->value()*3600) + (ui->sb_time_min->value()*60) + (value));ff7->setDescTime(s,ff7->slot[s].time);
}}

void MainWindow::on_sb_steps_valueChanged(int value)
{if(!load){file_modified(true);
  ff7->slot[s].steps = value;
}}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Item Tab~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_list_flyers_clicked(const QModelIndex &index)
{if(!load){file_modified(true);
    int j=index.row();
    if(ui->list_flyers->item(j)->checkState() ==Qt::Checked){ff7->slot[s].turtleflyers |= (1 << j);}
    else{ff7->slot[s].turtleflyers &= ~(1<<j);}
}}
void MainWindow::on_list_keyitems_clicked(const QModelIndex &index)
{if(!load){file_modified(true);
    int j = index.row();
    if (ui->list_keyitems->item(j)->checkState() == Qt::Checked){ff7->slot[s].keyitems[j/8] |= (1<<j%8);}
    else{ff7->slot[s].keyitems[j/8] &= ~(1<<j%8);}
}}

// Field Items Combos
void MainWindow::on_cb_bm_items_1_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_38[48] |= (1<<0);}else{ff7->slot[s].z_38[48] &= ~(1<<0);}}}
void MainWindow::on_cb_bm_items_2_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_38[48] |= (1<<1);}else{ff7->slot[s].z_38[48] &= ~(1<<1);}}}
void MainWindow::on_cb_bm_items_3_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_38[48] |= (1<<2);}else{ff7->slot[s].z_38[48] &= ~(1<<2);}}}
void MainWindow::on_cb_bm_items_4_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_38[48] |= (1<<3);}else{ff7->slot[s].z_38[48] &= ~(1<<3);}}}

void MainWindow::on_cb_s7tg_items_1_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_9[4] |= (1<<0);}else{ff7->slot[s].z_9[4] &= ~(1<<0);}}}
void MainWindow::on_cb_s7tg_items_2_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_9[4] |= (1<<1);}else{ff7->slot[s].z_9[4] &= ~(1<<1);}}}
void MainWindow::on_cb_s7tg_items_3_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_9[4] |= (1<<2);}else{ff7->slot[s].z_9[4] &= ~(1<<2);}}}
void MainWindow::on_cb_s7tg_items_4_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_9[4] |= (1<<3);}else{ff7->slot[s].z_9[4] &= ~(1<<3);}}}
void MainWindow::on_cb_s7tg_items_5_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_9[4] |= (1<<4);}else{ff7->slot[s].z_9[4] &= ~(1<<4);}}}
void MainWindow::on_cb_s7tg_items_6_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_9[4] |= (1<<5);}else{ff7->slot[s].z_9[4] &= ~(1<<5);}}}
void MainWindow::on_cb_s7tg_items_7_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_9[4] |= (1<<6);}else{ff7->slot[s].z_9[4] &= ~(1<<6);}}}
void MainWindow::on_cb_s7tg_items_8_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_9[4] |= (1<<7);}else{ff7->slot[s].z_9[4] &= ~(1<<7);}}}

void MainWindow::on_cb_farm_items_1_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_11[3] |= (1<<0);}else{ff7->slot[s].z_11[3] &= ~(1<<0);}}ui->lcd_farm_items->display(ff7->slot[s].z_11[3]);}
void MainWindow::on_cb_farm_items_2_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_11[3] |= (1<<1);}else{ff7->slot[s].z_11[3] &= ~(1<<1);}}ui->lcd_farm_items->display(ff7->slot[s].z_11[3]);}
void MainWindow::on_cb_farm_items_3_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_11[3] |= (1<<2);}else{ff7->slot[s].z_11[3] &= ~(1<<2);}}ui->lcd_farm_items->display(ff7->slot[s].z_11[3]);}
void MainWindow::on_cb_farm_items_4_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_11[3] |= (1<<3);}else{ff7->slot[s].z_11[3] &= ~(1<<3);}}ui->lcd_farm_items->display(ff7->slot[s].z_11[3]);}
void MainWindow::on_cb_farm_items_5_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_11[3] |= (1<<4);}else{ff7->slot[s].z_11[3] &= ~(1<<4);}}ui->lcd_farm_items->display(ff7->slot[s].z_11[3]);}
void MainWindow::on_cb_farm_items_6_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_11[3] |= (1<<5);}else{ff7->slot[s].z_11[3] &= ~(1<<5);}}ui->lcd_farm_items->display(ff7->slot[s].z_11[3]);}
void MainWindow::on_cb_farm_items_7_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_11[3] |= (1<<6);}else{ff7->slot[s].z_11[3] &= ~(1<<6);}}ui->lcd_farm_items->display(ff7->slot[s].z_11[3]);}
void MainWindow::on_cb_farm_items_8_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_11[3] |= (1<<7);}else{ff7->slot[s].z_11[3] &= ~(1<<7);}}ui->lcd_farm_items->display(ff7->slot[s].z_11[3]);}

void MainWindow::on_btn_clear_keyitems_clicked()
{if(!load){file_modified(true);}//used in other functions
    for(int i=0;i<51;i++)// be sure to clear key items first..
    {
        ui->list_keyitems->item(i)->setCheckState(Qt::Unchecked);
    }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MATERIA TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_tbl_materia_currentCellChanged(int row){if(!load){materia_editor->setMateria(ff7->partyMateriaId(s,row),ff7->partyMateriaAp(s,row));}}


void MainWindow::on_btn_add_all_materia_clicked()
{

    //int j = ui->tbl_materia->currentRow();
    //place one of each at lowest ossible point
    for(int i=117;i<142;i++)
    {//Starting With Magic Materia
        if(i<132){ff7->setPartyMateria(s,i,(i-68),FF7Materia::MaxMateriaAp);}
        else if((i>=132) && (i<136)){ff7->setPartyMateria(s,(i-1),(i-68),FF7Materia::MaxMateriaAp);}
        else if((i>=136) && (i<142)){ff7->setPartyMateria(s,(i-3),(i-68),FF7Materia::MaxMateriaAp);}
    }
    // Then Support
    for(int i=139;i<152;i++){ff7->setPartyMateria(s,i,(i-116),FF7Materia::MaxMateriaAp);}

    for(int i=152;i<166;i++)
    {//Then Command
        if(i<154){ff7->setPartyMateria(s,i,(i-138),FF7Materia::MaxMateriaAp);}
        else if(i<157){ff7->setPartyMateria(s,i,(i-135),FF7Materia::MaxMateriaAp);}
        else if(i<159){ff7->setPartyMateria(s,i,(i-121),FF7Materia::MaxMateriaAp);}
        else if(i<165){ff7->setPartyMateria(s,i,(i-120),FF7Materia::MaxMateriaAp);}
        else {ff7->setPartyMateria(s,i,0x30,FF7Materia::MaxMateriaAp);}
    }
    for(int i=166;i<183;i++)
    {//And Independent
        if(i<180){ff7->setPartyMateria(s,i,(i-166),FF7Materia::MaxMateriaAp);}
        else{ff7->setPartyMateria(s,i,(i-164),FF7Materia::MaxMateriaAp);}
    }
    //Finish With Summons
    for(int i=183;i<200;i++){ff7->setPartyMateria(s,i,(i-109),FF7Materia::MaxMateriaAp);}
    materiaupdate();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SAVE LOCATION TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_tbl_location_field_itemSelectionChanged()
{
    ui->tbl_location_field->setCurrentCell(ui->tbl_location_field->currentRow(),0);
    ui->line_location->setText(ui->tbl_location_field->currentItem()->text());
    ui->tbl_location_field->setCurrentCell(ui->tbl_location_field->currentRow(),1);
    ui->sb_map_id->setValue(ui->tbl_location_field->currentItem()->text().toInt());
    ui->tbl_location_field->setCurrentCell(ui->tbl_location_field->currentRow(),2);
    ui->sb_loc_id->setValue(ui->tbl_location_field->currentItem()->text().toInt());
    ui->tbl_location_field->setCurrentCell(ui->tbl_location_field->currentRow(),3);
    ui->sb_coordx->setValue(ui->tbl_location_field->currentItem()->text().toInt());
    ui->tbl_location_field->setCurrentCell(ui->tbl_location_field->currentRow(),4);
    ui->sb_coordy->setValue(ui->tbl_location_field->currentItem()->text().toInt());
    ui->tbl_location_field->setCurrentCell(ui->tbl_location_field->currentRow(),5);
    ui->sb_coordz->setValue(ui->tbl_location_field->currentItem()->text().toInt());
}
void MainWindow::on_sb_map_id_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].mapid= value;}}
void MainWindow::on_sb_loc_id_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].locationid = value;}}
void MainWindow::on_sb_coordx_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].coord.x = value;}}
void MainWindow::on_sb_coordy_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].coord.y = value;}}
void MainWindow::on_sb_coordz_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].coord.z = value;}}

void MainWindow::on_line_location_textChanged(QString text){if (!load){file_modified(true);ff7->setLocation(s,text);}}

/*~~~~~~~~~~~~~~~~~~~~~~~~CHARACTER TAB~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~ Game Options~~~~~~~~~~~~~~~~~~*/
void MainWindow::set_UL_Color(QColor color){if(!load){file_modified(true);ff7->setDialog_UL(s,color);}}
void MainWindow::set_UR_Color(QColor color){if(!load){file_modified(true);ff7->setDialog_UR(s,color);}}
void MainWindow::set_LL_Color(QColor color){if(!load){file_modified(true);ff7->setDialog_LL(s,color);}}
void MainWindow::set_LR_Color(QColor color){if(!load){file_modified(true);ff7->setDialog_LR(s,color);}}
void MainWindow::on_slide_battlespeed_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].battlespeed = value;}}
void MainWindow::on_slide_battlemspeed_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].battlemspeed = value;}}
void MainWindow::on_slide_fieldmspeed_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].fieldmspeed = value;}}
void MainWindow::on_combo_control_currentIndexChanged(){if(!load){file_modified(true); setoptions_one();}}
void MainWindow::on_combo_sound_currentIndexChanged(){if(!load){file_modified(true); setoptions_one();}}
void MainWindow::on_combo_cursor_currentIndexChanged(){if(!load){file_modified(true); setoptions_one();}}
void MainWindow::on_combo_atb_currentIndexChanged(){if(!load){file_modified(true); setoptions_one();}}
void MainWindow::on_combo_camera_currentIndexChanged(){if(!load){file_modified(true); setoptions_two();}}
void MainWindow::on_combo_magic_order_currentIndexChanged(){if(!load){file_modified(true); setoptions_two();}}
void MainWindow::on_cb_battle_help_toggled(){if(!load){file_modified(true); setoptions_two();}}

void MainWindow::setoptions_one()
{
    load=true;
    ff7->slot[s].options1 = 0;
    if(ui->combo_sound->currentIndex() == 1){ff7->slot[s].options1 += 0x01;}
    if(ui->combo_control->currentIndex() == 1){ff7->slot[s].options1 += 0x04;} //you have to also change mapped buttons for this to work 100%
    if(ui->combo_cursor->currentIndex() == 1){ff7->slot[s].options1 +=0x10;}
    if(ui->combo_atb->currentIndex() == 1){ff7->slot[s].options1 +=0x40;}
    if(ui->combo_atb->currentIndex() == 2){ff7->slot[s].options1 += 0x80;}
    load=false;
}
void MainWindow::setoptions_two()
{
    load=true;
    quint8 temp=0;
    if(ui->combo_camera->currentIndex()==1){temp += 1;}
    if(ui->combo_magic_order->currentIndex() == 1){temp += 0x04;}
    else if(ui->combo_magic_order->currentIndex()==2){temp += 0x08;}
    else if(ui->combo_magic_order->currentIndex()==3){temp += 0x0C;}
    else if(ui->combo_magic_order->currentIndex()==4){temp += 0x10;}
    else if(ui->combo_magic_order->currentIndex()==5){temp += 0x14;}
    if(ui->cb_battle_help->checkState() ==2){temp +=0x40;}
    ff7->slot[s].options2 =temp;
    load=false;
}

/*--------GAME PROGRESS-------*/
void MainWindow::on_sb_curdisc_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].disc = value;}}
void MainWindow::on_sb_mprogress_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].mprogress = value;}}
void MainWindow::on_sb_turkschruch_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].aeris_chruch=value;}}
void MainWindow::on_sb_donprog_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].donprogress=value;}}

void MainWindow::on_cb_bm1_1_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress1 |= (1<<0);}else{ff7->slot[s].bm_progress1 &= ~(1<<0);}}}
void MainWindow::on_cb_bm1_2_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress1 |= (1<<1);}else{ff7->slot[s].bm_progress1 &= ~(1<<1);}}}
void MainWindow::on_cb_bm1_3_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress1 |= (1<<2);}else{ff7->slot[s].bm_progress1 &= ~(1<<2);}}}
void MainWindow::on_cb_bm1_4_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress1 |= (1<<3);}else{ff7->slot[s].bm_progress1 &= ~(1<<3);}}}
void MainWindow::on_cb_bm1_5_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress1 |= (1<<4);}else{ff7->slot[s].bm_progress1 &= ~(1<<4);}}}
void MainWindow::on_cb_bm1_6_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress1 |= (1<<5);}else{ff7->slot[s].bm_progress1 &= ~(1<<5);}}}
void MainWindow::on_cb_bm1_7_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress1 |= (1<<6);}else{ff7->slot[s].bm_progress1 &= ~(1<<6);}}}
void MainWindow::on_cb_bm1_8_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress1 |= (1<<7);}else{ff7->slot[s].bm_progress1 &= ~(1<<7);}}}

void MainWindow::on_cb_bm2_1_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress2 |= (1<<0);}else{ff7->slot[s].bm_progress2 &= ~(1<<0);}}}
void MainWindow::on_cb_bm2_2_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress2 |= (1<<1);}else{ff7->slot[s].bm_progress2 &= ~(1<<1);}}}
void MainWindow::on_cb_bm2_3_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress2 |= (1<<2);}else{ff7->slot[s].bm_progress2 &= ~(1<<2);}}}
void MainWindow::on_cb_bm2_4_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress2 |= (1<<3);}else{ff7->slot[s].bm_progress2 &= ~(1<<3);}}}
void MainWindow::on_cb_bm2_5_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress2 |= (1<<4);}else{ff7->slot[s].bm_progress2 &= ~(1<<4);}}}
void MainWindow::on_cb_bm2_6_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress2 |= (1<<5);}else{ff7->slot[s].bm_progress2 &= ~(1<<5);}}}
void MainWindow::on_cb_bm2_7_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress2 |= (1<<6);}else{ff7->slot[s].bm_progress2 &= ~(1<<6);}}}
void MainWindow::on_cb_bm2_8_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress2 |= (1<<7);}else{ff7->slot[s].bm_progress2 &= ~(1<<7);}}}

void MainWindow::on_cb_bm3_1_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress3 |= (1<<0);}else{ff7->slot[s].bm_progress3 &= ~(1<<0);}}}
void MainWindow::on_cb_bm3_2_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress3 |= (1<<1);}else{ff7->slot[s].bm_progress3 &= ~(1<<1);}}}
void MainWindow::on_cb_bm3_3_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress3 |= (1<<2);}else{ff7->slot[s].bm_progress3 &= ~(1<<2);}}}
void MainWindow::on_cb_bm3_4_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress3 |= (1<<3);}else{ff7->slot[s].bm_progress3 &= ~(1<<3);}}}
void MainWindow::on_cb_bm3_5_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress3 |= (1<<4);}else{ff7->slot[s].bm_progress3 &= ~(1<<4);}}}
void MainWindow::on_cb_bm3_6_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress3 |= (1<<5);}else{ff7->slot[s].bm_progress3 &= ~(1<<5);}}}
void MainWindow::on_cb_bm3_7_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress3 |= (1<<6);}else{ff7->slot[s].bm_progress3 &= ~(1<<6);}}}
void MainWindow::on_cb_bm3_8_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].bm_progress3 |= (1<<7);}else{ff7->slot[s].bm_progress3 &= ~(1<<7);}}}

void MainWindow::on_cb_s7pl_1_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[0] |= (1<<0);}else{ff7->slot[s].z_26[0] &= ~(1<<0);}}}
void MainWindow::on_cb_s7pl_2_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[0] |= (1<<1);}else{ff7->slot[s].z_26[0] &= ~(1<<1);}}}
void MainWindow::on_cb_s7pl_3_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[0] |= (1<<2);}else{ff7->slot[s].z_26[0] &= ~(1<<2);}}}
void MainWindow::on_cb_s7pl_4_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[0] |= (1<<3);}else{ff7->slot[s].z_26[0] &= ~(1<<3);}}}
void MainWindow::on_cb_s7pl_5_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[0] |= (1<<4);}else{ff7->slot[s].z_26[0] &= ~(1<<4);}}}
void MainWindow::on_cb_s7pl_6_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[0] |= (1<<5);}else{ff7->slot[s].z_26[0] &= ~(1<<5);}}}
void MainWindow::on_cb_s7pl_7_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[0] |= (1<<6);}else{ff7->slot[s].z_26[0] &= ~(1<<6);}}}
void MainWindow::on_cb_s7pl_8_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[0] |= (1<<7);}else{ff7->slot[s].z_26[0] &= ~(1<<7);}}}

void MainWindow::on_cb_s7ts_1_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[8] |= (1<<0);}else{ff7->slot[s].z_26[8] &= ~(1<<0);}}}
void MainWindow::on_cb_s7ts_2_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[8] |= (1<<1);}else{ff7->slot[s].z_26[8] &= ~(1<<1);}}}
void MainWindow::on_cb_s7ts_3_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[8] |= (1<<2);}else{ff7->slot[s].z_26[8] &= ~(1<<2);}}}
void MainWindow::on_cb_s7ts_4_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[8] |= (1<<3);}else{ff7->slot[s].z_26[8] &= ~(1<<3);}}}
void MainWindow::on_cb_s7ts_5_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[8] |= (1<<4);}else{ff7->slot[s].z_26[8] &= ~(1<<4);}}}
void MainWindow::on_cb_s7ts_6_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[8] |= (1<<5);}else{ff7->slot[s].z_26[8] &= ~(1<<5);}}}
void MainWindow::on_cb_s7ts_7_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[8] |= (1<<6);}else{ff7->slot[s].z_26[8] &= ~(1<<6);}}}
void MainWindow::on_cb_s7ts_8_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_26[8] |= (1<<7);}else{ff7->slot[s].z_26[8] &= ~(1<<7);}}}

void MainWindow::on_cb_s5_1_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_23[26] |= (1<<0);}else{ff7->slot[s].z_23[26] &= ~(1<<0);}}}
void MainWindow::on_cb_s5_2_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_23[26] |= (1<<1);}else{ff7->slot[s].z_23[26] &= ~(1<<1);}}}
void MainWindow::on_cb_s5_3_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_23[26] |= (1<<2);}else{ff7->slot[s].z_23[26] &= ~(1<<2);}}}
void MainWindow::on_cb_s5_4_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_23[26] |= (1<<3);}else{ff7->slot[s].z_23[26] &= ~(1<<3);}}}
void MainWindow::on_cb_s5_5_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_23[26] |= (1<<4);}else{ff7->slot[s].z_23[26] &= ~(1<<4);}}}
void MainWindow::on_cb_s5_6_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_23[26] |= (1<<5);}else{ff7->slot[s].z_23[26] &= ~(1<<5);}}}
void MainWindow::on_cb_s5_7_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_23[26] |= (1<<6);}else{ff7->slot[s].z_23[26] &= ~(1<<6);}}}
void MainWindow::on_cb_s5_8_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].z_23[26] |= (1<<7);}else{ff7->slot[s].z_23[26] &= ~(1<<7);}}}

void MainWindow::on_cb_bombing_int_stateChanged(int checked)
{if(!load){file_modified(true);
    if(checked == Qt::Checked){ff7->slot[s].intbombing =0x14;}
    else{ff7->slot[s].intbombing =0x56;}
}}

void MainWindow::on_cb_replay_currentIndexChanged(int index)
{
    if(index == 1) // bombing mission
    {
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(1);
        ff7->slot[s].bm_progress1=0;
        ff7->slot[s].bm_progress2=0;
        ff7->slot[s].bm_progress3=0;
        ui->cb_bombing_int->setChecked(1);
        ui->cb_midgartrain_1->setChecked(0);
        ui->cb_midgartrain_2->setChecked(0);
        ui->cb_midgartrain_3->setChecked(0);
        ui->cb_midgartrain_4->setChecked(0);
        ui->cb_midgartrain_5->setChecked(0);
        ui->cb_midgartrain_6->setChecked(0);
        ui->cb_midgartrain_7->setChecked(0);
        ui->cb_midgartrain_8->setChecked(0);
        ui->combo_s7_slums->setCurrentIndex(1);
        ui->cb_s5_7->setChecked(0);//show aeris on roof of chruch durring script
        ui->cb_s5_8->setChecked(0);//not after chruch scene.
        ui->sb_turkschruch->setValue(0); // reset turks.
        ui->line_location->setText(tr("Platform"));
        ui->sb_map_id->setValue(1);
        ui->sb_loc_id->setValue(116);
        ui->sb_coordx->setValue(3655);
        ui->sb_coordy->setValue(27432);
        ui->sb_coordz->setValue(25);
        ui->label_replaynote->setText(tr("Replay the bombing mission from right after you get off the train."));
    }
    else if(index == 2) // The Church In The Slums
    {
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(130);
        ui->sb_turkschruch->setValue(0);
        ff7->slot[s].bm_progress1=120;
        ff7->slot[s].bm_progress2=198;
        ff7->slot[s].bm_progress3=3;
        ui->cb_bombing_int->setChecked(0);
        ui->cb_s5_7->setChecked(0);//show aeris on roof of chruch durring script
        ui->cb_s5_8->setChecked(0);//not after chruch scene.
        ui->line_location->setText(tr("Church in the Slums"));
        ui->sb_map_id->setValue(1);
        ui->sb_loc_id->setValue(183);
        ui->sb_coordx->setValue(65463);
        ui->sb_coordy->setValue(400);
        ui->sb_coordz->setValue(8);
        ui->combo_party1->setCurrentIndex(0);
        ui->combo_party2->setCurrentIndex(12);
        ui->combo_party3->setCurrentIndex(12);
        ui->label_replaynote->setText(tr("Meeting Aeris"));

    }
    else if (index ==3)// Flash back
    {
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(341);
        ff7->slot[s].bm_progress1=120;
        ff7->slot[s].bm_progress2=198;
        ff7->slot[s].bm_progress3=3;
        ui->cb_bombing_int->setChecked(0);
        ui->line_location->setText(tr("Kalm Inn"));
        ui->sb_map_id->setValue(1);
        ui->sb_loc_id->setValue(332);
        ui->sb_coordx->setValue(267);
        ui->sb_coordy->setValue(65429);
        ui->sb_coordz->setValue(15);
        // set up young cloud, Copy Cloud Change ID to young Cloud
        ff7->setChar(s,6,ff7->Char(s,0));
        ff7->setCharID(s,6,FF7Char::YoungCloud);
        //set up Sephiroth
        ff7->setCharID(s,7,FF7Char::Sephiroth);
        if(ff7->region(s).contains("00700") || ff7->region(s).contains("01057"))
        {        ff7->setCharName(s,7,QString::fromUtf8("セフィロス"));
        }
        else{ff7->setCharName(s,7,QString::fromUtf8("Sephiroth"));}
        set_char_buttons();
        if(curchar == FF7Char::CaitSith){char_editor->setChar(ff7->Char(s,6),ff7->charName(s,6));}
        else if(curchar ==FF7Char::Vincent){char_editor->setChar(ff7->Char(s,7),ff7->charName(s,7));}
        ui->label_replaynote->setText(tr("Setting This Will Copy Cloud as is to young cloud (caitsith's slot). sephiroth's stats will come directly from vincent."));
    }

    else if(index == 4) // The Date Scene
    {
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(583);
        ff7->slot[s].bm_progress1=120;
        ff7->slot[s].bm_progress2=198;
        ff7->slot[s].bm_progress3=3;
        ui->cb_bombing_int->setChecked(0);
        ui->line_location->setText(tr("Ropeway Station"));
        ui->sb_map_id->setValue(1);
        ui->sb_loc_id->setValue(496);
        ui->sb_coordx->setValue(64767);
        ui->sb_coordy->setValue(95);
        ui->sb_coordz->setValue(26);
        ui->label_replaynote->setText(tr("Replay the Date Scene, Your Location will be set To Ropeway Station, Talk To The Guy By The Tram To Start The Event, If Your Looking for a special Date be sure to set your love points too."));
    }

    else if (index == 5)//Aeris Death
    {
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(664);
        ff7->slot[s].bm_progress1=120;
        ff7->slot[s].bm_progress2=198;
        ff7->slot[s].bm_progress3=3;
        ui->cb_bombing_int->setChecked(0);
        ui->line_location->setText(tr("Forgotten City"));
        ui->sb_map_id->setValue(1);
        ui->sb_loc_id->setValue(646);
        ui->sb_coordx->setValue(641);
        ui->sb_coordy->setValue(793);
        ui->sb_coordz->setValue(243);
        ui->list_chars_unlocked->item(3)->setCheckState(Qt::Unchecked);
        ui->list_phs_chars->item(3)->setCheckState(Qt::Unchecked);
        ui->label_replaynote->setText(tr("Replay the death of Aeris.This option Will remove Aeris from your PHS"));
    }

    else {ui->label_replaynote->setText(tr("         INFO ON CURRENTLY SELECTED REPLAY MISSION"));}
    if(!load){file_modified(true); progress_update();}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FUNCTIONS FOR TESTING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_btn_remove_all_items_clicked() //used for testing
{
    for(int i=0;i<320;i++){ff7->setItem(s,i,FF7Item::EmptyItemData);}
    if(!load){file_modified(true); }
    itemlist->setItems(ff7->items(s));
    //itemupdate();
}

void MainWindow::on_btn_remove_all_materia_clicked()
{
    for (int i=0;i<200;i++){ff7->setPartyMateria(s,i,FF7Materia::EmptyId,FF7Materia::MaxMateriaAp);}
    if(!load){file_modified(true); }
    materiaupdate();
}

void MainWindow::on_btn_remove_all_stolen_clicked()
{
    for(int i=0;i<48;i++){ff7->setStolenMateria(s,i,FF7Materia::EmptyId,FF7Materia::MaxMateriaAp);}
    if(!load){file_modified(true);}
    guirefresh(0);
}

void MainWindow::on_sb_b_love_aeris_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].b_love.aeris = value;}}
void MainWindow::on_sb_b_love_tifa_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].b_love.tifa = value;}}
void MainWindow::on_sb_b_love_yuffie_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].b_love.yuffie = value;}}
void MainWindow::on_sb_b_love_barret_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].b_love.barret = value;}}
void MainWindow::on_sb_coster_1_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].coster_1=value;}}
void MainWindow::on_sb_coster_2_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].coster_2 = value;}}
void MainWindow::on_sb_coster_3_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].coster_3 = value;}}
void MainWindow::on_sb_timer_time_hour_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].timer[0] = value;}}
void MainWindow::on_sb_timer_time_min_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].timer[1] = value;}}
void MainWindow::on_sb_timer_time_sec_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].timer[2] = value;}}

void MainWindow::on_list_menu_visible_clicked(const QModelIndex &index)
{if(!load){file_modified(true);
        int j=index.row();
        if(ui->list_menu_visible->item(j)->checkState() ==Qt::Checked){ff7->slot[s].menu_visible |= (1<<j);}
        else{ff7->slot[s].menu_visible &= ~(1<<j);}
}}

void MainWindow::on_list_menu_locked_clicked(const QModelIndex &index)
{if(!load){file_modified(true);
        int j=index.row();
        if(ui->list_menu_locked->item(j)->checkState() ==Qt::Checked){ff7->slot[s].menu_locked |= (1<<j);}
        else{ff7->slot[s].menu_locked &= ~(1<<j);}
}}

void MainWindow::on_sb_u_weapon_hp_valueChanged(int value)
{if(!load){file_modified(true);
    load=true;
    int a = (value & 0xff);
    int b = (value & 0xff00) >> 8;
    int c = (value & 0xff0000) >> 16;
    ff7->slot[s].u_weapon_hp[0] = a;
    ff7->slot[s].u_weapon_hp[1] = b;
    ff7->slot[s].u_weapon_hp[2] = c;
    load=false;
}}

void MainWindow::on_cb_reg_vinny_toggled(bool checked)
{if(!load){file_modified(true);
    if (checked){ff7->slot[s].reg_vinny =0xFF;}
    else{ff7->slot[s].reg_vinny =0xFB;}
    testdata_refresh();
}}

void MainWindow::on_cb_itemmask1_1_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<0);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<0);}
}}

void MainWindow::on_cb_itemmask1_2_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<1);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<1);}
}}

void MainWindow::on_cb_itemmask1_3_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<2);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<2);}
}}

void MainWindow::on_cb_itemmask1_4_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<3);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<3);}
}}

void MainWindow::on_cb_itemmask1_5_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<4);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<4);}
}}

void MainWindow::on_cb_itemmask1_6_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<5);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<5);}
}}

void MainWindow::on_cb_itemmask1_7_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<6);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<6);}
}}

void MainWindow::on_cb_itemmask1_8_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<7);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<7);}
}}

void MainWindow::on_cb_materiacave_1_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].materiacaves |= (1<<0);}
    else{ff7->slot[s].materiacaves &= ~(1<<0);}
}}

void MainWindow::on_cb_materiacave_2_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].materiacaves |= (1<<1);}
    else{ff7->slot[s].materiacaves &= ~(1<<1);}
}}

void MainWindow::on_cb_materiacave_3_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].materiacaves |= (1<<2);}
    else{ff7->slot[s].materiacaves &= ~(1<<2);}
}}

void MainWindow::on_cb_materiacave_4_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].materiacaves |= (1<<3);}
    else{ff7->slot[s].materiacaves &= ~(1<<3);}
}}

void MainWindow::on_cb_reg_yuffie_toggled(bool checked)
{if(!load){file_modified(true);
        if (checked){ff7->slot[s].reg_yuffie =0x6F;}
        else{ff7->slot[s].reg_yuffie =0x6E;}
        testdata_refresh();
}}

void MainWindow::on_cb_yuffieforest_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].yuffieforest |= (1<<0);}
    else{ff7->slot[s].yuffieforest &= ~(1<<0);}
}}

void MainWindow::on_cb_midgartrain_1_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].midgartrainflags |= (1<<0);}else{ff7->slot[s].midgartrainflags &= ~(1<<0);}}}
void MainWindow::on_cb_midgartrain_2_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].midgartrainflags |= (1<<1);}else{ff7->slot[s].midgartrainflags &= ~(1<<1);}}}
void MainWindow::on_cb_midgartrain_3_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].midgartrainflags |= (1<<2);}else{ff7->slot[s].midgartrainflags &= ~(1<<2);}}}
void MainWindow::on_cb_midgartrain_4_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].midgartrainflags |= (1<<3);}else{ff7->slot[s].midgartrainflags &= ~(1<<3);}}}
void MainWindow::on_cb_midgartrain_5_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].midgartrainflags |= (1<<4);}else{ff7->slot[s].midgartrainflags &= ~(1<<4);}}}
void MainWindow::on_cb_midgartrain_6_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].midgartrainflags |= (1<<5);}else{ff7->slot[s].midgartrainflags &= ~(1<<5);}}}
void MainWindow::on_cb_midgartrain_7_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].midgartrainflags |= (1<<6);}else{ff7->slot[s].midgartrainflags &= ~(1<<6);}}}
void MainWindow::on_cb_midgartrain_8_toggled(bool checked){if(!load){file_modified(true); if(checked){ff7->slot[s].midgartrainflags |= (1<<7);}else{ff7->slot[s].midgartrainflags &= ~(1<<7);}}}

void MainWindow::on_cb_tut_worldsave_stateChanged(int value)
{if(!load){file_modified(true);
    if (value == 0){ff7->slot[s].tut_save =0x00;}
    else if(value ==1){ff7->slot[s].tut_save =0x32;}
    else if(value ==2){ff7->slot[s].tut_save=0x3A;}
    testdata_refresh();
}}

void MainWindow::on_cb_Region_Slot_currentIndexChanged()
{if(!load){file_modified(true); if(!ff7->region(s).isEmpty()){
    QString new_regionString = ff7->region(s).mid(0,ff7->region(s).lastIndexOf("-")+1);
    new_regionString.append(ui->cb_Region_Slot->currentText().toAscii());
    ff7->setRegion(s,new_regionString);
    if(ff7->type()== "MC"|| ff7->type()=="PSP"|| ff7->type()=="VGS" || ff7->type() =="DEX"){guirefresh(0);}
}}}

void MainWindow::on_cb_field_help_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].field_help |= (1<<0);}
    else{ff7->slot[s].field_help &= ~(1<<0);}
}}

void MainWindow::on_cb_battle_targets_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].tut_sub |= (1<<6);}
    else{ff7->slot[s].tut_sub &= ~(1<<6);}
}}
void MainWindow::on_cb_tut_sub_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].tut_sub |= (1<<2);}
    else{ff7->slot[s].tut_sub &= ~(1<<2);}
    testdata_refresh();
}}
void MainWindow::on_cb_tut_sub_1_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].tut_sub |= (1<<0);}
    else{ff7->slot[s].tut_sub &= ~(1<<0);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_2_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].tut_sub |= (1<<1);}
    else{ff7->slot[s].tut_sub &= ~(1<<1);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_3_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].tut_sub |= (1<<2);}
    else{ff7->slot[s].tut_sub &= ~(1<<2);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_4_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].tut_sub |= (1<<3);}
    else{ff7->slot[s].tut_sub &= ~(1<<3);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_5_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].tut_sub |= (1<<4);}
    else{ff7->slot[s].tut_sub &= ~(1<<4);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_6_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].tut_sub |= (1<<5);}
    else{ff7->slot[s].tut_sub &= ~(1<<5);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_7_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].tut_sub |= (1<<6);}
    else{ff7->slot[s].tut_sub &= ~(1<<6);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_8_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].tut_sub |= (1<<7);}
    else{ff7->slot[s].tut_sub &= ~(1<<7);}
    testdata_refresh();
}}

void MainWindow::on_cb_ruby_dead_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].ruby_emerald |= (1<<3);}
    else{ff7->slot[s].ruby_emerald &= ~(1<<3);}
}}

void MainWindow::on_cb_emerald_dead_toggled(bool checked)
{if(!load){file_modified(true);
    if(checked){ff7->slot[s].ruby_emerald |= (1<<4);}
    else{ff7->slot[s].ruby_emerald &= ~(1<<4);}
}}

void MainWindow::on_combo_highwind_buggy_currentIndexChanged(int index)
{if(!load){file_modified(true);
  switch(index)
  {
  case 1: ui->bh_id->setValue(0x06);ui->cb_visible_buggy->setChecked(Qt::Checked);break;//buggy
  case 2: ui->bh_id->setValue(0x03);ui->cb_visible_highwind->setChecked(Qt::Checked);break;//highwind
  default: break;
  }
}}
void MainWindow::on_cb_visible_buggy_toggled(bool checked)
{if(!load){file_modified(true);
        if(checked){ff7->slot[s].world_map_vehicles |= (1<<0);}
        else{ff7->slot[s].world_map_vehicles &= ~(1<<0);}
}}
void MainWindow::on_cb_visible_bronco_toggled(bool checked)
{if(!load){file_modified(true);
        if(checked){ff7->slot[s].world_map_vehicles |= (1<<2);}
        else{ff7->slot[s].world_map_vehicles &= ~(1<<2);}
}}
void MainWindow::on_cb_visible_highwind_toggled(bool checked)
{if(!load){file_modified(true);
        if(checked){ff7->slot[s].world_map_vehicles |= (1<<4);}
        else{ff7->slot[s].world_map_vehicles &= ~(1<<4);}
}}
void MainWindow::on_cb_visible_wild_chocobo_toggled(bool checked)
{if(!load){file_modified(true);
        if(checked){ff7->slot[s].world_map_chocobos |= (1<<0);}
        else{ff7->slot[s].world_map_chocobos &= ~(1<<0);}
}}
void MainWindow::on_cb_visible_yellow_chocobo_toggled(bool checked)
{if(!load){file_modified(true);
        if(checked){
            ff7->slot[s].world_map_chocobos |= (1<<2);
            ui->cb_visible_green_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_blue_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_black_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_gold_chocobo->setChecked(Qt::Unchecked);
        }
        else{ff7->slot[s].world_map_chocobos &= ~(1<<2);}
}}
void MainWindow::on_cb_visible_green_chocobo_toggled(bool checked)
{if(!load){file_modified(true);
        if(checked){
            ff7->slot[s].world_map_chocobos |= (1<<3);
            ui->cb_visible_yellow_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_blue_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_black_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_gold_chocobo->setChecked(Qt::Unchecked);
        }
        else{ff7->slot[s].world_map_chocobos &= ~(1<<3);}
}}
void MainWindow::on_cb_visible_blue_chocobo_toggled(bool checked)
{if(!load){file_modified(true);
        if(checked){
            ff7->slot[s].world_map_chocobos |= (1<<4);
            ui->cb_visible_yellow_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_green_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_black_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_gold_chocobo->setChecked(Qt::Unchecked);
        }
        else{ff7->slot[s].world_map_chocobos &= ~(1<<4);}
}}

void MainWindow::on_cb_visible_black_chocobo_toggled(bool checked)
{if(!load){file_modified(true);
        if(checked){
            ff7->slot[s].world_map_chocobos |= (1<<5);
            ui->cb_visible_yellow_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_green_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_blue_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_gold_chocobo->setChecked(Qt::Unchecked);
        }
        else{ff7->slot[s].world_map_chocobos &= ~(1<<5);}
}}

void MainWindow::on_cb_visible_gold_chocobo_toggled(bool checked)
{if(!load){file_modified(true);
        if(checked){
            ff7->slot[s].world_map_chocobos |= (1<<6);
            ui->cb_visible_yellow_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_green_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_blue_chocobo->setChecked(Qt::Unchecked);
            ui->cb_visible_black_chocobo->setChecked(Qt::Unchecked);
        }
        else{ff7->slot[s].world_map_chocobos &= ~(1<<6);}
}}
// Leader's world map stuff. 0
void MainWindow::on_leader_id_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].l_world = (ui->leader_x->value()  | value << 19 | ui->leader_angle->value() <<24);}}
void MainWindow::on_leader_angle_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].l_world = (ui->leader_x->value()  | ui->leader_id->value() << 19 | value <<24);}}
void MainWindow::on_leader_z_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].l_world2 = (ui->leader_y->value() | value << 18);}}
void MainWindow::on_leader_x_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].l_world = (value | ui->leader_id->value() << 19 | ui->leader_angle->value() << 24);
    if(ui->combo_map_controls->currentIndex()==0){load=true;ui->slide_world_x->setValue(value);load=false;}
}}

void MainWindow::on_leader_y_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].l_world2 = (value | ui->leader_z->value() << 18);
    if(ui->combo_map_controls->currentIndex()==0){load=true;ui->slide_world_y->setValue(value);load=false;}
}}

//Tiny bronco / chocobo world 1
void MainWindow::on_tc_id_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].tc_world = (ui->tc_x->value()  | value << 19 | ui->tc_angle->value() <<24);}}
void MainWindow::on_tc_angle_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].tc_world = (ui->tc_x->value()  | ui->tc_id->value() << 19 | value <<24);}}
void MainWindow::on_tc_z_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].tc_world2 = (ui->tc_y->value() | value << 18);}}
void MainWindow::on_tc_x_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].tc_world = (value | ui->tc_id->value() << 19 | ui->tc_angle->value() << 24);
    if(ui->combo_map_controls->currentIndex()==1){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_tc_y_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].tc_world2 = (value | ui->tc_z->value() << 18);
    if(ui->combo_map_controls->currentIndex()==1){load=true;ui->slide_world_y->setValue(value);load=false;}
}}

//buggy / highwind world 2
void MainWindow::on_bh_id_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].bh_world = (ui->bh_x->value()  | value << 19 | ui->bh_angle->value() <<24);}}
void MainWindow::on_bh_angle_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].bh_world = (ui->bh_x->value()  | ui->bh_id->value() << 19 | value <<24);}}
void MainWindow::on_bh_z_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].bh_world2 = (ui->bh_y->value() | value << 18);}}
void MainWindow::on_bh_x_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].bh_world = (value | ui->bh_id->value() << 19 | ui->bh_angle->value() << 24);
    if(ui->combo_map_controls->currentIndex()==2){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_bh_y_valueChanged(int value)
{if(!load){file_modified(true);
        ff7->slot[s].bh_world2 = (value | ui->bh_z->value() << 18);
        if(ui->combo_map_controls->currentIndex()==2){load=true;ui->slide_world_y->setValue(value);load=false;}
}}
// sub world 3
void MainWindow::on_sub_id_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].sub_world = (ui->sub_x->value()  | value << 19 | ui->sub_angle->value() <<24);}}
void MainWindow::on_sub_angle_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].sub_world = (ui->sub_x->value()  | ui->sub_id->value() << 19 | value <<24);}}
void MainWindow::on_sub_z_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].sub_world2 = (ui->sub_y->value() | value << 18);}}
void MainWindow::on_sub_x_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].sub_world = (value | ui->sub_id->value() << 19 | ui->sub_angle->value() << 24);
     if(ui->combo_map_controls->currentIndex()==3){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_sub_y_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].sub_world2 = (value | ui->sub_z->value() << 18);
    if(ui->combo_map_controls->currentIndex()==3){load=true;ui->slide_world_y->setValue(value);load=false;}
}}

//Ruby world stuff 4
void MainWindow::on_durw_id_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].durw_world = (ui->durw_x->value()  | value << 19 | ui->durw_angle->value() <<24);}}
void MainWindow::on_durw_angle_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].durw_world = (ui->durw_x->value()  | ui->durw_id->value() << 19 | value <<24);}}
void MainWindow::on_durw_z_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].durw_world2 = (ui->durw_y->value() | value << 18);}}
void MainWindow::on_durw_x_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].durw_world = (value | ui->durw_id->value() << 19 | ui->durw_angle->value() << 24);
     if(ui->combo_map_controls->currentIndex()==4){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_durw_y_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].durw_world2 = (value | ui->durw_z->value() << 18);
     if(ui->combo_map_controls->currentIndex()==4){load=true;ui->slide_world_y->setValue(value);load=false;}
}}
//emerald world 5?
/* Do Nothing. Don't know emerald weapon Coords
void MainWindow::on_ew_id_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].ew_world = (ui->ew_x->value()  | value << 19 | ui->ew_angle->value() <<24);}}
void MainWindow::on_ew_z_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].ew_world2 = (ui->ew_y->value() | value << 18);}}
void MainWindow::on_ew_angle_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].ew_world = (ui->ew_x->value()  | ui->ew_id->value() << 19 | value <<24);}}
void MainWindow::on_ew_x_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].ew_world = (value | ui->ew_id->value() << 19 | ui->ew_angle->value() << 24);
     if(ui->combo_map_controls->currentIndex()==5){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_ew_y_valueChanged(int value)
{if(!load){
        file_modified(true);
        ff7->slot[s].ew_world2 = (value | ui->ew_z->value() << 18);
        if(ui->combo_map_controls->currentIndex()==5){load=true;ui->slide_world_y->setValue(value);load=false;}
}}
*/
//ultimate weapon 6?
void MainWindow::on_uw_id_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].uw_world = (ui->uw_x->value()  | value << 19 | ui->uw_angle->value() <<24);}}
void MainWindow::on_uw_angle_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].uw_world = (ui->uw_x->value()  | ui->uw_id->value() << 19 | value <<24);}}
void MainWindow::on_uw_z_valueChanged(int value){if(!load){file_modified(true); ff7->slot[s].uw_world2 = (ui->uw_y->value() | value << 18);}}
void MainWindow::on_uw_x_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].uw_world = (value | ui->uw_id->value() << 19 | ui->uw_angle->value() << 24);
     if(ui->combo_map_controls->currentIndex()==6){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_uw_y_valueChanged(int value)
{if(!load){file_modified(true);
    ff7->slot[s].uw_world2 = (value | ui->uw_z->value() << 18);
    if(ui->combo_map_controls->currentIndex()==6){load=true;ui->slide_world_y->setValue(value);load=false;}
}}

void MainWindow::on_combo_map_controls_currentIndexChanged(int index)
{
    load=true;
    switch(index)
    {
    case 0: ui->slide_world_x->setValue(ff7->slot[s].l_world  & 0x7FFFF);
            ui->slide_world_y->setValue(ff7->slot[s].l_world2 & 0x3FFFF);
            break;
    case 1: ui->slide_world_x->setValue(ff7->slot[s].tc_world  & 0x7FFFF);
            ui->slide_world_y->setValue(ff7->slot[s].tc_world2 & 0x3FFFF);
            break;
    case 2: ui->slide_world_x->setValue(ff7->slot[s].bh_world  & 0x7FFFF);
            ui->slide_world_y->setValue(ff7->slot[s].bh_world2 & 0x3FFFF);
            break;
    case 3: ui->slide_world_x->setValue(ff7->slot[s].sub_world  & 0x7FFFF);
            ui->slide_world_y->setValue(ff7->slot[s].sub_world2 & 0x3FFFF);
            break;
    case 4: ui->slide_world_x->setValue(ff7->slot[s].uw_world  & 0x7FFFF);
            ui->slide_world_y->setValue(ff7->slot[s].uw_world2 & 0x3FFFF);
            break;
    case 5: ui->slide_world_x->setValue(ff7->slot[s].durw_world  & 0x7FFFF);
            ui->slide_world_y->setValue(ff7->slot[s].durw_world2 & 0x3FFFF);
            break;
    case 6: /* Do Nothing. Don't know emerald weapon Coords
            ui->slide_world_x->setValue(ff7->slot[s].ew_world  & 0x7FFFF);
            ui->slide_world_y->setValue(ff7->slot[s].ew_world2 & 0x3FFFF);
            */
            break;
    }
    load=false;
}

void MainWindow::on_slide_world_x_valueChanged(int value)
{if(!load){file_modified(true);
    switch(ui->combo_map_controls->currentIndex())
    {
    case 0: ui->leader_x->setValue(value);  break;
    case 1: ui->tc_x->setValue(value);      break;
    case 2: ui->bh_x->setValue(value);      break;
    case 3: ui->sub_x->setValue(value);     break;
    case 4: ui->uw_x->setValue(value);      break;
    case 5: ui->durw_x->setValue(value);    break;
    /* Do Nothing. Don't know emerald weapon Coords
    case 6: ui->ew_x->setValue(value);      break;
    */
    }
}}

void MainWindow::on_slide_world_y_valueChanged(int value)
{if(!load){file_modified(true);
    switch(ui->combo_map_controls->currentIndex())
    {
    case 0: ui->leader_y->setValue(value);  break;
    case 1: ui->tc_y->setValue(value);      break;
    case 2: ui->bh_y->setValue(value);      break;
    case 3: ui->sub_y->setValue(value);     break;
    case 4: ui->uw_y->setValue(value);      break;
    case 5: ui->durw_y->setValue(value);    break;
    /* Do Nothing. Don't know emerald weapon Coords
    case 6: ui->ew_y->setValue(value);      break;
    */
    }

}}

void MainWindow::on_world_map_view_customContextMenuRequested(QPoint pos)
{//Need to create a Paint System Here To put Dots where Chars Are Placed.
    QMenu menu(this);
    QAction *sel;
    menu.addAction(tr("Place Leader"));
    menu.addAction(tr("Place Tiny Bronco/Chocobo"));
    menu.addAction(tr("Place Buggy/Highwind"));
    menu.addAction(tr("Place Sub"));
    menu.addAction(tr("Place Wild Chocobo"));
    menu.addAction(tr("Place Diamond/Ultimate/Ruby Weapon"));
    /* Do Nothing. Don't know emerald weapon Coords
    menu.addAction(tr("Place Emerald Weapon?"));
    */
    sel = menu.exec(ui->world_map_view->mapToGlobal(pos));
    if(sel==0){return;}
    file_modified(true);
    if(sel->text()==tr("Place Leader"))
    {
        ui->leader_x->setValue(pos.x() *( 295000/ ui->world_map_view->width()));
        ui->leader_y->setValue(pos.y() *( 230000/ ui->world_map_view->height()));
    }
    else if(sel->text()==tr("Place Tiny Bronco/Chocobo"))
    {
        ui->tc_x->setValue(pos.x() *( 295000/ ui->world_map_view->width()));
        ui->tc_y->setValue(pos.y() *( 230000/ ui->world_map_view->height()));
    }
    else if(sel->text()==tr("Place Buggy/Highwind"))
    {
         ui->bh_x->setValue(pos.x() *( 295000/ ui->world_map_view->width()));
         ui->bh_y->setValue(pos.y() *( 230000/ ui->world_map_view->height()));
    }
    else if(sel->text()==tr("Place Sub"))
    {
         ui->sub_x->setValue(pos.x() *( 295000/ ui->world_map_view->width()));
         ui->sub_y->setValue(pos.y() *( 230000/ ui->world_map_view->height()));
    }
    else if(sel->text()==tr("Place Wild Chocobo"))
    {
         ui->uw_x->setValue(pos.x() *( 295000/ ui->world_map_view->width()));
         ui->uw_y->setValue(pos.y() *( 230000/ ui->world_map_view->height()));
    }
    else if(sel->text()==tr("Place Diamond/Ultimate/Ruby Weapon"))
    {
         ui->durw_x->setValue(pos.x() *( 295000/ ui->world_map_view->width()));
         ui->durw_y->setValue(pos.y() *( 230000/ ui->world_map_view->height()));
    }
    else if(sel->text()==tr("Place Emerald Weapon?"))
    {
         /* Do Nothing. Don't know emerald weapon Coords
         ui->ew_x->setValue(pos.x() *( 295000/ ui->world_map_view->width()));
         ui->ew_y->setValue(pos.y() *( 230000/ ui->world_map_view->height()));
         */
    }
    else{return;}
}//End Of Map Context Menu

void MainWindow::on_btn_item_add_each_item_clicked()
{
    if(!load){file_modified(true); }
    ui->btn_remove_all_items->click();
    for(int i=0;i<320;i++)
    {
      //Replaced by new item engine. (Vegeta_Ss4)
        if(Items.Name(i)!=tr("DON'T USE"))
        {
            if(i<106)
            {
                ff7->setItem(s,i,i,127);
            }
            else// after the block of empty items shift up 23 spots.
            {
                ff7->setItem(s,(i-23),i,127);
            }
        }
        else{ff7->setItem(s,i,0x1FF,0x7F);}//exclude the test items
        if(i>296){ff7->setItem(s,i,0x1FF,0x7F);}//replace the shifted ones w/ empty slots
    }
    //guirefresh(0)
            itemlist->setItems(ff7->items(s));
}


void MainWindow::unknown_refresh(int z)//remember to add/remove case statments in all 3 switches when number of z vars changes.
{//for updating the unknown table(s)
    load=true;
    QString text;
    int rows=0;
    QTableWidgetItem *newItem;
    quint8 value=0;
    QByteArray temp;

    ui->tbl_unknown->reset();
    ui->tbl_unknown->setColumnWidth(0,40);
    ui->tbl_unknown->setColumnWidth(1,40);
    ui->tbl_unknown->setColumnWidth(2,40);
    ui->tbl_unknown->setColumnWidth(3,70);
    ui->tbl_unknown->setColumnWidth(4,20);

    ui->tbl_compare_unknown->reset();
    ui->tbl_compare_unknown->setColumnWidth(0,40);
    ui->tbl_compare_unknown->setColumnWidth(1,40);
    ui->tbl_compare_unknown->setColumnWidth(2,40);
    ui->tbl_compare_unknown->setColumnWidth(3,70);
    ui->tbl_compare_unknown->setColumnWidth(4,20);

    if(ui->combo_compare_slot->currentIndex()==0){ui->btn_all_z_diffs->setEnabled(0);}
    else {ui->btn_all_z_diffs->setEnabled(1);}

    switch(z)//how many rows
    {
      case 0: break;
      case 1: rows=sizeof(ff7->slot[s].z_1); break;
      case 2: rows=sizeof(ff7->slot[s].z_2); break;
      case 3: rows=sizeof(ff7->slot[s].z_3); break;
      case 4: rows=sizeof(ff7->slot[s].z_4); break;
      case 5: rows=sizeof(ff7->slot[s].z_5); break;
      case 6: rows=sizeof(ff7->slot[s].z_6); break;
      case 7: rows=sizeof(ff7->slot[s].z_7); break;
      case 8: rows=sizeof(ff7->slot[s].z_8); break;
      case 9: rows=sizeof(ff7->slot[s].z_9); break;
      case 10: rows=sizeof(ff7->slot[s].z_10); break;
      case 11: rows=sizeof(ff7->slot[s].z_11); break;
      case 12: rows=sizeof(ff7->slot[s].z_12); break;
      case 13: rows=sizeof(ff7->slot[s].z_13); break;
      case 14: rows=sizeof(ff7->slot[s].z_14); break;
      case 15: rows=sizeof(ff7->slot[s].z_15); break;
      case 16: rows=sizeof(ff7->slot[s].z_16); break;
      case 17: rows=sizeof(ff7->slot[s].z_17); break;
      case 18: rows=sizeof(ff7->slot[s].z_18); break;
      case 19: rows=sizeof(ff7->slot[s].z_19); break;
      case 20: rows=sizeof(ff7->slot[s].z_20); break;
      case 21: rows=sizeof(ff7->slot[s].z_21); break;
      case 22: rows=sizeof(ff7->slot[s].z_22); break;
      case 23: rows=sizeof(ff7->slot[s].z_23); break;
      case 24: rows=sizeof(ff7->slot[s].z_24); break;
      case 25: rows=sizeof(ff7->slot[s].z_25); break;
      case 26: rows=sizeof(ff7->slot[s].z_26); break;
      case 27: rows=sizeof(ff7->slot[s].z_27); break;
      case 28: rows=sizeof(ff7->slot[s].z_28); break;
      case 29: rows=sizeof(ff7->slot[s].z_29); break;
      case 30: rows=sizeof(ff7->slot[s].z_30); break;
      case 31: rows=sizeof(ff7->slot[s].z_31); break;
      case 32: rows=sizeof(ff7->slot[s].z_32); break;
      case 33: rows=sizeof(ff7->slot[s].z_33); break;
      case 34: rows=sizeof(ff7->slot[s].z_34); break;
      case 35: rows=sizeof(ff7->slot[s].z_35); break;
      case 36: rows=sizeof(ff7->slot[s].z_36); break;
      case 37: rows=sizeof(ff7->slot[s].z_37); break;
      case 38: rows=sizeof(ff7->slot[s].z_38); break;
      case 39: rows=sizeof(ff7->slot[s].z_39); break;
      case 40: rows=sizeof(ff7->slot[s].z_40); break;
      //Always Last Case , Full Slot
      case 41: rows=sizeof(ff7->slot[s]); break;
    }
    ui->tbl_unknown->setRowCount(rows);
    if(ui->combo_compare_slot->currentIndex()!=0){ui->tbl_compare_unknown->setRowCount(rows);}
    for(int i=0;i<rows;i++)
    {
        if(ui->combo_z_var->currentText()=="SLOT")
        {
            QString hex_str = QString("%1").arg(i,4,16,QChar('0')).toUpper(); //format ex: 000C
            newItem = new QTableWidgetItem(hex_str,0);
            ui->tbl_unknown->setItem(i,0,newItem);
        }
        else
        {
            text.setNum(i);
            newItem = new QTableWidgetItem(text,0);
            ui->tbl_unknown->setItem(i,0,newItem);
        }
        switch(z)//what is the items data one byte at a time
        {
            case 1: value = ff7->slot[s].z_1[i]; break;
            case 2: value = ff7->slot[s].z_2[i]; break;
            case 3: value = ff7->slot[s].z_3[i]; break;
            case 4: value = ff7->slot[s].z_4[i]; break;
            case 5: value = ff7->slot[s].z_5[i]; break;
            case 6: value = ff7->slot[s].z_6[i]; break;
            case 7: value = ff7->slot[s].z_7[i]; break;
            case 8: value = ff7->slot[s].z_8[i]; break;
            case 9: value = ff7->slot[s].z_9[i]; break;
            case 10: value = ff7->slot[s].z_10[i]; break;
            case 11: value = ff7->slot[s].z_11[i]; break;
            case 12: value = ff7->slot[s].z_12[i]; break;
            case 13: value = ff7->slot[s].z_13[i]; break;
            case 14: value = ff7->slot[s].z_14[i]; break;
            case 15: value = ff7->slot[s].z_15[i]; break;
            case 16: value = ff7->slot[s].z_16[i]; break;
            case 17: value = ff7->slot[s].z_17[i]; break;
            case 18: value = ff7->slot[s].z_18[i]; break;
            case 19: value = ff7->slot[s].z_19[i]; break;
            case 20: value = ff7->slot[s].z_20[i]; break;
            case 21: value = ff7->slot[s].z_21[i]; break;
            case 22: value = ff7->slot[s].z_22[i]; break;
            case 23: value = ff7->slot[s].z_23[i]; break;
            case 24: value = ff7->slot[s].z_24[i]; break;
            case 25: value = ff7->slot[s].z_25[i]; break;
            case 26: value = ff7->slot[s].z_26[i]; break;
            case 27: value = ff7->slot[s].z_27[i]; break;
            case 28: value = ff7->slot[s].z_28[i]; break;
            case 29: value = ff7->slot[s].z_29[i]; break;
            case 30: value = ff7->slot[s].z_30[i]; break;
            case 31: value = ff7->slot[s].z_31[i]; break;
            case 32: value = ff7->slot[s].z_32[i]; break;
            case 33: value = ff7->slot[s].z_33[i]; break;
            case 34: value = ff7->slot[s].z_34[i]; break;
            case 35: value = ff7->slot[s].z_35[i]; break;
            case 36: value = ff7->slot[s].z_36[i]; break;
            case 37: value = ff7->slot[s].z_37[i]; break;
            case 38: value = ff7->slot[s].z_38[i]; break;
            case 39: value = ff7->slot[s].z_39[i]; break;
            case 40: value = ff7->slot[s].z_40[i]; break;
            //Always Last Case , Full Slot
            case 41:temp.setRawData(reinterpret_cast<char *>(&ff7->slot[s]),rows);
                    value = temp.at(i);
                    break;
        }
        //Write Hex
        QString hex_str = QString("%1").arg(value,2,16,QChar('0')).toUpper(); //Format: 000C
        newItem = new QTableWidgetItem(hex_str,0);
        ui->tbl_unknown->setItem(i,1,newItem);
        //Write Dec
        newItem = new QTableWidgetItem(text.number(value,10),0);
        ui->tbl_unknown->setItem(i,2,newItem);
        //Write Bin
        QString binary_str = QString("%1").arg(value,8,2,QChar('0')); //New format ex: 00000111 | Vegeta_Ss4 Bin mod
        newItem = new QTableWidgetItem(binary_str,0);
        ui->tbl_unknown->setItem(i,3,newItem);
        //Write Char
        newItem = new QTableWidgetItem(QChar(value),0);
        ui->tbl_unknown->setItem(i,4,newItem);

        if(ui->combo_compare_slot->currentIndex()!=0)
        {//do the same for the compare slot if one has been selected.
            if(ui->combo_z_var->currentText()=="SLOT")
            {
                QString hex_str = QString("%1").arg(i,4,16,QChar('0')).toUpper();
                newItem = new QTableWidgetItem(hex_str,0);
                ui->tbl_compare_unknown->setItem(i,0,newItem);
            }
            else
            {
                newItem = new QTableWidgetItem(text,0);
                ui->tbl_compare_unknown->setItem(i,0,newItem);
            }
        switch(z)
        {
            case 1: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_1[i]; break;
            case 2: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_2[i]; break;
            case 3: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_3[i]; break;
            case 4: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_4[i]; break;
            case 5: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_5[i]; break;
            case 6: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_6[i]; break;
            case 7: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_7[i]; break;
            case 8: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_8[i]; break;
            case 9: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_9[i]; break;
            case 10: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_10[i]; break;
            case 11: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_11[i]; break;
            case 12: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_12[i]; break;
            case 13: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_13[i]; break;
            case 14: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_14[i]; break;
            case 15: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_15[i]; break;
            case 16: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_16[i]; break;
            case 17: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_17[i]; break;
            case 18: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_18[i]; break;
            case 19: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_19[i]; break;
            case 20: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_20[i]; break;
            case 21: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_21[i]; break;
            case 22: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_22[i]; break;
            case 23: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_23[i]; break;
            case 24: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_24[i]; break;
            case 25: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_25[i]; break;
            case 26: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_26[i]; break;
            case 27: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_27[i]; break;
            case 28: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_28[i]; break;
            case 29: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_29[i]; break;
            case 30: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_30[i]; break;
            case 31: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_31[i]; break;
            case 32: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_32[i]; break;
            case 33: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_33[i]; break;
            case 34: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_34[i]; break;
            case 35: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_35[i]; break;
            case 36: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_36[i]; break;
            case 37: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_37[i]; break;
            case 38: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_38[i]; break;
            case 39: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_39[i]; break;
            case 40: value = ff7->slot[ui->combo_compare_slot->currentIndex()-1].z_40[i]; break;
            //Always Last Case , Full Slot
            case 41: temp.setRawData(reinterpret_cast<char *>(&ff7->slot[ui->combo_compare_slot->currentIndex()-1]),rows);
                     value = temp.at(i);
                     break;
        }
        //Write Hex
        QString hex_str = QString("%1").arg(value,2,16,QChar('0')).toUpper(); //New format ex: 0C | Vegeta_Ss4 Hex mod
        newItem = new QTableWidgetItem(hex_str,0);
        ui->tbl_compare_unknown->setItem(i,1,newItem);
        //Write Dec
        newItem = new QTableWidgetItem(text.number(value,10),0);
        ui->tbl_compare_unknown->setItem(i,2,newItem);
        //Write Bin
        QString binary_str = QString("%1").arg(value,8,2,QChar('0')); //New format ex: 00000111 | Vegeta_Ss4 Bin mod
        newItem = new QTableWidgetItem(binary_str,0);
        ui->tbl_compare_unknown->setItem(i,3,newItem);
        //Write Char
        newItem = new QTableWidgetItem(QChar(value),0);
        ui->tbl_compare_unknown->setItem(i,4,newItem);

        if(ui->tbl_compare_unknown->item(i,1)->text()!=ui->tbl_unknown->item(i,1)->text())
        {
            for (int c=0;c<5;c++)
            {//color the diffs ;)
                ui->tbl_compare_unknown->item(i,c)->setBackgroundColor(Qt::yellow);
                ui->tbl_compare_unknown->item(i,c)->setTextColor(Qt::red);
                ui->tbl_unknown->item(i,c)->setBackgroundColor(Qt::yellow);
                ui->tbl_unknown->item(i,c)->setTextColor(Qt::red);
            }
        }
      }
    }
    for(int i=0;i<rows;i++)//set up the item flags
    {
        ui->tbl_unknown->item(i,0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->tbl_unknown->item(i,1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable| Qt::ItemIsEditable);
        ui->tbl_unknown->item(i,2)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable| Qt::ItemIsEditable);
        ui->tbl_unknown->item(i,3)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable| Qt::ItemIsEditable);
        ui->tbl_unknown->item(i,4)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

        if(ui->combo_compare_slot->currentIndex()!=0)
        {
            ui->tbl_compare_unknown->item(i,0)->setFlags(Qt::ItemIsEnabled);
            ui->tbl_compare_unknown->item(i,1)->setFlags(Qt::ItemIsEnabled);
            ui->tbl_compare_unknown->item(i,2)->setFlags(Qt::ItemIsEnabled);
            ui->tbl_compare_unknown->item(i,3)->setFlags(Qt::ItemIsEnabled);
            ui->tbl_compare_unknown->item(i,4)->setFlags(Qt::ItemIsEnabled);
        }
    }
    load=false;
}

void MainWindow::on_combo_z_var_currentIndexChanged(int z){unknown_refresh(z);}

void MainWindow::on_combo_compare_slot_currentIndexChanged(void)
{
    if(ui->combo_compare_slot->currentIndex()==0)
    {
        ui->tbl_compare_unknown->clearContents();
        ui->tbl_compare_unknown->setRowCount(0);
        ui->tbl_diff->clearContents();
        ui->tbl_diff->setRowCount(0);
        ui->btn_all_z_diffs->setEnabled(0);
    }
    else{unknown_refresh(ui->combo_z_var->currentIndex());}
    ui->tbl_diff->setVisible(0);
}

void MainWindow::on_tbl_unknown_itemChanged(QTableWidgetItem* item)
{if(!load){file_modified(true);
    QByteArray temp;
    if(item->column()==1)
    {//column 1 selected
        switch (ui->combo_z_var->currentIndex())
        {
            case 0: break;
            case 1: ff7->slot[s].z_1[item->row()]= item->text().toInt(0,16);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 2: ff7->slot[s].z_2[item->row()]= item->text().toInt(0,16);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 3: ff7->slot[s].z_3[item->row()]= item->text().toInt(0,16);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 4: ff7->slot[s].z_4[item->row()]= item->text().toInt(0,16);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 5: ff7->slot[s].z_5[item->row()]= item->text().toInt(0,16);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 6: ff7->slot[s].z_6[item->row()]= item->text().toInt(0,16);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 7: ff7->slot[s].z_7[item->row()]= item->text().toInt(0,16);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 8: ff7->slot[s].z_8[item->row()]= item->text().toInt(0,16);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 9: ff7->slot[s].z_9[item->row()]= item->text().toInt(0,16);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 10: ff7->slot[s].z_10[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 11: ff7->slot[s].z_11[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 12: ff7->slot[s].z_12[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 13: ff7->slot[s].z_13[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 14: ff7->slot[s].z_14[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 15: ff7->slot[s].z_15[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 16: ff7->slot[s].z_16[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 17: ff7->slot[s].z_17[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 18: ff7->slot[s].z_18[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 19: ff7->slot[s].z_19[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 20: ff7->slot[s].z_20[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 21: ff7->slot[s].z_21[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 22: ff7->slot[s].z_22[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 23: ff7->slot[s].z_23[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 24: ff7->slot[s].z_24[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 25: ff7->slot[s].z_25[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 26: ff7->slot[s].z_26[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 27: ff7->slot[s].z_27[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 28: ff7->slot[s].z_28[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 29: ff7->slot[s].z_29[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 30: ff7->slot[s].z_30[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 31: ff7->slot[s].z_31[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 32: ff7->slot[s].z_32[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 33: ff7->slot[s].z_33[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 34: ff7->slot[s].z_34[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 35: ff7->slot[s].z_35[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 36: ff7->slot[s].z_36[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 37: ff7->slot[s].z_37[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 38: ff7->slot[s].z_38[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 39: ff7->slot[s].z_39[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 40: ff7->slot[s].z_40[item->row()]= item->text().toInt(0,16); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            //Always Last Case , Full Slot
            case 41: temp.setRawData(reinterpret_cast<char *>(&ff7->slot[s]),sizeof(ff7->slot[s]));
                     temp[item->row()]=item->text().toInt(0,16);
                     memcpy(&ff7->slot[s],temp,sizeof(ff7->slot[s]));
                     unknown_refresh(ui->combo_z_var->currentIndex());
                     break;
        }
    }
    else if(item->column()==2)
    {//column 2 selected
        switch (ui->combo_z_var->currentIndex())
        {
            case 0: break;
            case 1: ff7->slot[s].z_1[item->row()]= item->text().toInt();   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 2: ff7->slot[s].z_2[item->row()]= item->text().toInt();   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 3: ff7->slot[s].z_3[item->row()]= item->text().toInt();   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 4: ff7->slot[s].z_4[item->row()]= item->text().toInt();   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 5: ff7->slot[s].z_5[item->row()]= item->text().toInt();   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 6: ff7->slot[s].z_6[item->row()]= item->text().toInt();   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 7: ff7->slot[s].z_7[item->row()]= item->text().toInt();   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 8: ff7->slot[s].z_8[item->row()]= item->text().toInt();   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 9: ff7->slot[s].z_9[item->row()]= item->text().toInt();   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 10: ff7->slot[s].z_10[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 11: ff7->slot[s].z_11[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 12: ff7->slot[s].z_12[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 13: ff7->slot[s].z_13[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 14: ff7->slot[s].z_14[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 15: ff7->slot[s].z_15[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 16: ff7->slot[s].z_16[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 17: ff7->slot[s].z_17[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 18: ff7->slot[s].z_18[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 19: ff7->slot[s].z_19[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 20: ff7->slot[s].z_20[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 21: ff7->slot[s].z_21[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 22: ff7->slot[s].z_22[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 23: ff7->slot[s].z_23[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 24: ff7->slot[s].z_24[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 25: ff7->slot[s].z_25[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 26: ff7->slot[s].z_26[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 27: ff7->slot[s].z_27[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 28: ff7->slot[s].z_28[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 29: ff7->slot[s].z_29[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 30: ff7->slot[s].z_30[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 31: ff7->slot[s].z_31[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 32: ff7->slot[s].z_32[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 33: ff7->slot[s].z_33[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 34: ff7->slot[s].z_34[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 35: ff7->slot[s].z_35[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 36: ff7->slot[s].z_36[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 37: ff7->slot[s].z_37[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 38: ff7->slot[s].z_38[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 39: ff7->slot[s].z_39[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 40: ff7->slot[s].z_40[item->row()]= item->text().toInt(); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            //Always Last Case , Full Slot
            case 41: temp.setRawData(reinterpret_cast<char *>(&ff7->slot[s]),sizeof(ff7->slot[s]));
                     temp[item->row()]=item->text().toInt();
                     memcpy(&ff7->slot[s],temp,sizeof(ff7->slot[s]));
                     unknown_refresh(ui->combo_z_var->currentIndex());
                     break;
        }
    }
    else if(item->column()==3)
    {//column 3 selected
        switch (ui->combo_z_var->currentIndex())
        {
            case 0: break;
            case 1: ff7->slot[s].z_1[item->row()]= item->text().toInt(0,2);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 2: ff7->slot[s].z_2[item->row()]= item->text().toInt(0,2);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 3: ff7->slot[s].z_3[item->row()]= item->text().toInt(0,2);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 4: ff7->slot[s].z_4[item->row()]= item->text().toInt(0,2);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 5: ff7->slot[s].z_5[item->row()]= item->text().toInt(0,2);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 6: ff7->slot[s].z_6[item->row()]= item->text().toInt(0,2);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 7: ff7->slot[s].z_7[item->row()]= item->text().toInt(0,2);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 8: ff7->slot[s].z_8[item->row()]= item->text().toInt(0,2);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 9: ff7->slot[s].z_9[item->row()]= item->text().toInt(0,2);   unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 10: ff7->slot[s].z_10[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 11: ff7->slot[s].z_11[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 12: ff7->slot[s].z_12[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 13: ff7->slot[s].z_13[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 14: ff7->slot[s].z_14[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 15: ff7->slot[s].z_15[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 16: ff7->slot[s].z_16[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 17: ff7->slot[s].z_17[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 18: ff7->slot[s].z_18[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 19: ff7->slot[s].z_19[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 20: ff7->slot[s].z_20[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 21: ff7->slot[s].z_21[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 22: ff7->slot[s].z_22[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 23: ff7->slot[s].z_23[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 24: ff7->slot[s].z_24[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 25: ff7->slot[s].z_25[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 26: ff7->slot[s].z_26[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 27: ff7->slot[s].z_27[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 28: ff7->slot[s].z_28[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 29: ff7->slot[s].z_29[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 30: ff7->slot[s].z_30[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 31: ff7->slot[s].z_31[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 32: ff7->slot[s].z_32[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 33: ff7->slot[s].z_33[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 34: ff7->slot[s].z_34[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 35: ff7->slot[s].z_35[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 36: ff7->slot[s].z_36[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 37: ff7->slot[s].z_37[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 38: ff7->slot[s].z_38[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 39: ff7->slot[s].z_39[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            case 40: ff7->slot[s].z_40[item->row()]= item->text().toInt(0,2); unknown_refresh(ui->combo_z_var->currentIndex());    break;
            //Always Last Case , Full Slot
            case 41: temp.setRawData(reinterpret_cast<char *>(&ff7->slot[s]),sizeof(ff7->slot[s]));
                     temp[item->row()]=item->text().toInt(0,2);
                     memcpy(&ff7->slot[s],temp,sizeof(ff7->slot[s]));
                     unknown_refresh(ui->combo_z_var->currentIndex());
                     break;
        }
    }
    else {/*do nothing*/}
}}
void MainWindow::on_btn_all_z_diffs_clicked()
{
    ui->tbl_diff->reset();

    int num_diff=0;
    qint16 diff =0;
    QString text;
    QTableWidgetItem *newItem;
    int z_index= ui->combo_z_var->currentIndex();
    if(z_index==ui->combo_z_var->count()-1)
    {//if last item in list (SLOT mode)
        for(int i=0;i<ui->tbl_unknown->rowCount();i++)
        {
            if(ui->tbl_compare_unknown->item(i,1)->text()!=ui->tbl_unknown->item(i,1)->text())
            {
                num_diff++;
                ui->tbl_diff->setRowCount(num_diff);
                text.clear();
                //Offset
                QString hex_str = QString("%1").arg(i,4,16,QChar('0')).toUpper(); //Format: 0000C
                newItem = new QTableWidgetItem(hex_str,0);
                ui->tbl_diff->setItem(num_diff-1,0,newItem);
                //Decimal
                diff= ui->tbl_unknown->item(i,2)->text().toInt() - ui->tbl_compare_unknown->item(i,2)->text().toInt() ;
                newItem = new QTableWidgetItem(text.number(diff,10),0);
                ui->tbl_diff->setItem(num_diff-1,1,newItem);

                //Write Bin
                QString binary_str = QString("%1").arg(qAbs(diff),8,2,QChar('0')); //New format ex: 00000111 | Vegeta_Ss4 Bin mod
                newItem = new QTableWidgetItem(binary_str,0);
                ui->tbl_diff->setItem(num_diff-1,2,newItem);

                //set properites for the tableitems
                ui->tbl_diff->setVisible(1);
                ui->tbl_diff->item(num_diff-1,0)->setFlags(Qt::ItemIsEnabled);
                ui->tbl_diff->item(num_diff-1,1)->setFlags(Qt::ItemIsEnabled);
                ui->tbl_diff->item(num_diff-1,2)->setFlags(Qt::ItemIsEnabled);
                ui->tbl_diff->setRowHeight(num_diff-1,20);
            }
        }
    }
    else
    {
        for(int z=0;z<ui->combo_z_var->count()-1;z++)
        {
            ui->combo_z_var->setCurrentIndex(z);
            for(int i=0;i<ui->tbl_unknown->rowCount();i++)
            {
                if(ui->tbl_compare_unknown->item(i,1)->text()!=ui->tbl_unknown->item(i,1)->text())
                {
                    num_diff++;
                    ui->tbl_diff->setRowCount(num_diff);
                    text.clear();
                    text.append("z_");  text.append(QString::number(z));
                    text.append(":");   text.append(QString::number(i));
                    newItem = new QTableWidgetItem(text,0);
                    ui->tbl_diff->setItem(num_diff-1,0,newItem);
                    diff= ui->tbl_unknown->item(i,2)->text().toInt() - ui->tbl_compare_unknown->item(i,2)->text().toInt() ;
                    newItem = new QTableWidgetItem(text.number(diff,10),0);
                    ui->tbl_diff->setItem(num_diff-1,1,newItem);
                    //Write Bin
                    QString binary_str = QString("%1").arg(qAbs(diff),8,2,QChar('0')); //New format ex: 00000111 | Vegeta_Ss4 Bin mod
                    newItem = new QTableWidgetItem(binary_str,0);
                    ui->tbl_diff->setItem(num_diff-1,2,newItem);

                    //set properites for the tableitems
                    ui->tbl_diff->setVisible(1);
                    ui->tbl_diff->item(num_diff-1,0)->setFlags(Qt::ItemIsEnabled);
                    ui->tbl_diff->item(num_diff-1,1)->setFlags(Qt::ItemIsEnabled);
                    ui->tbl_diff->item(num_diff-1,2)->setFlags(Qt::ItemIsEnabled);
                    ui->tbl_diff->setRowHeight(num_diff-1,20);
                }
            }
        }
    }
    ui->tbl_diff->setColumnWidth(0,70);
    ui->tbl_diff->setColumnWidth(1,40);
    ui->tbl_diff->setColumnWidth(2,70);
    ui->tbl_diff->setVisible(1);
    if(num_diff<16){ui->tbl_diff->setFixedHeight((num_diff*21)+20);ui->tbl_diff->setFixedWidth(185);}
    else{ui->tbl_diff->setFixedHeight((15*21)+23);ui->tbl_diff->setFixedWidth(200);}
    ui->combo_z_var->setCurrentIndex(z_index);
    if(num_diff ==0){ui->tbl_diff->clearContents();ui->tbl_diff->setRowCount(0);ui->tbl_diff->setVisible(0);}
}

void MainWindow::on_combo_button_1_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[0]=index;}}
void MainWindow::on_combo_button_2_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[1]=index;}}
void MainWindow::on_combo_button_3_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[2]=index;}}
void MainWindow::on_combo_button_4_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[3]=index;}}
void MainWindow::on_combo_button_5_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[4]=index;}}
void MainWindow::on_combo_button_6_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[5]=index;}}
void MainWindow::on_combo_button_7_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[6]=index;}}
void MainWindow::on_combo_button_8_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[7]=index;}}
void MainWindow::on_combo_button_9_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[8]=index;}}
void MainWindow::on_combo_button_10_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[9]=index;}}
void MainWindow::on_combo_button_11_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[10]=index;}}
void MainWindow::on_combo_button_12_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[11]=index;}}
void MainWindow::on_combo_button_13_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[12]=index;}}
void MainWindow::on_combo_button_14_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[13]=index;}}
void MainWindow::on_combo_button_15_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[14]=index;}}
void MainWindow::on_combo_button_16_currentIndexChanged(int index){if(!load){file_modified(true); ff7->slot[s].controller_map[15]=index;}}

void MainWindow::on_combo_s7_slums_currentIndexChanged(int index)
{if(!load){file_modified(true);
        switch(index)
        {
        default: break; //do nothing
        case 1: //initial slums setting
            ff7->slot[s].z_26[1]=0x00;
            ff7->slot[s].z_26[2]=0x00;
            ff7->slot[s].z_26[3]=0x00;
            ff7->slot[s].z_26[4]=0x00;
            ff7->slot[s].z_26[5]=0x00;
            ff7->slot[s].z_26[6]=0x00;
            break;

        case 2://after first scene. needs game global progress set to 105
            ff7->slot[s].z_26[1]=0xBF;
            ff7->slot[s].z_26[2]=0x03; //03
            ff7->slot[s].z_26[3]=0x05;
            ff7->slot[s].z_26[4]=0x17;//07
            ff7->slot[s].z_26[5]=0x5D;
            ff7->slot[s].z_26[6]=0xEF;
            break;

        case 3://plate falling
            ff7->slot[s].z_26[1]=0xBF;
            ff7->slot[s].z_26[2]=0x13; //Sky is falling
            ff7->slot[s].z_26[3]=0x05;
            ff7->slot[s].z_26[4]=0x17;//07
            ff7->slot[s].z_26[5]=0x5D;
            ff7->slot[s].z_26[6]=0xEF;
            break;
        }
}}
void MainWindow::char_materia_changed(materia mat)
{
    ff7->setCharMateria(s,curchar,mslotsel,mat);
    file_modified(true);
}
void MainWindow::char_accessory_changed(quint8 accessory)
{
    ff7->setCharAccessory(s,curchar,accessory);
    file_modified(true);
}
void MainWindow::char_armor_changed(quint8 armor)
{
    ff7->setCharArmor(s,curchar,armor);
    file_modified(true);
}
void MainWindow::char_baseHp_changed(quint16 hp)
{
    ff7->setCharBaseHp(s,curchar,hp);
    file_modified(true);
}
void MainWindow::char_baseMp_changed(quint16 mp)
{
    ff7->setCharBaseMp(s,curchar,mp);
    file_modified(true);
}
void MainWindow::char_curHp_changed(quint16 hp)
{
    ff7->setCharCurrentHp(s,curchar,hp);
    if(curchar==ff7->Party(s,0)){ff7->setDescCurHP(s,hp);}
    file_modified(true);
}
void MainWindow::char_curMp_changed(quint16 mp)
{
    ff7->setCharCurrentMp(s,curchar,mp);
    if(curchar==ff7->Party(s,0)){ff7->setDescCurMP(s,mp);}
    file_modified(true);
}
void MainWindow::char_id_changed(qint8 id)
{
    ff7->setCharID(s,curchar,id);
    set_char_buttons();
    file_modified(true);
}
void MainWindow::char_level_changed(qint8 level)
{
    ff7->setCharLevel(s,curchar,level);
    if(curchar==ff7->Party(s,0)){ff7->setDescLevel(s,level);}
    file_modified(true);
}
void MainWindow::char_str_changed(quint8 str)
{
    ff7->setCharStr(s,curchar,str);
    file_modified(true);
}

void MainWindow::char_vit_changed(quint8 vit)
{
    ff7->setCharVit(s,curchar,vit);
    file_modified(true);
}

void MainWindow::char_mag_changed(quint8 mag)
{
    ff7->setCharMag(s,curchar,mag);
    file_modified(true);
}
void MainWindow::char_spi_changed(quint8 spi)
{
    ff7->setCharSpi(s,curchar,spi);
    file_modified(true);
}

void MainWindow::char_dex_changed(quint8 dex)
{
    ff7->setCharDex(s,curchar,dex);
    file_modified(true);
}

void MainWindow::char_lck_changed(quint8 lck)
{
    ff7->setCharLck(s,curchar,lck);
    file_modified(true);
}

void MainWindow::char_strBonus_changed(quint8 value)
{
    ff7->setCharStrBonus(s,curchar,value);
    file_modified(true);
}
void MainWindow::char_vitBonus_changed(quint8 value)
{
    ff7->setCharVitBonus(s,curchar,value);
    file_modified(true);
}

void MainWindow::char_magBonus_changed(quint8 value)
{
    ff7->setCharMagBonus(s,curchar,value);
    file_modified(true);
}

void MainWindow::char_spiBonus_changed(quint8 value)
{
    ff7->setCharSpiBonus(s,curchar,value);
    file_modified(true);
}

void MainWindow::char_dexBonus_changed(quint8 value)
{
    ff7->setCharDexBonus(s,curchar,value);
    file_modified(true);
}

void MainWindow::char_lckBonus_changed(quint8 value)
{
    ff7->setCharLckBonus(s,curchar,value);
    file_modified(true);
}

void MainWindow::char_limitLevel_changed(qint8 value)
{
    ff7->setCharLimitLevel(s,curchar,value);
    file_modified(true);
}

void MainWindow::char_limitBar_changed(quint8 value)
{
    ff7->setCharLimitBar(s,curchar,value);
    file_modified(true);
}

void MainWindow::char_name_changed(QString name)
{
    ff7->setCharName(s,curchar,name);
    if(curchar==ff7->Party(s,0)){ff7->setDescName(s,name);}
    file_modified(true);
}

void MainWindow::char_weapon_changed(quint8 value)
{
    ff7->setCharWeapon(s,curchar,value);
    file_modified(true);
}
void MainWindow::char_maxHp_changed(quint16 value)

{
    ff7->setCharMaxHp(s,curchar,value);
    if(curchar==ff7->Party(s,0)){ff7->setDescMaxHP(s,value);}
    file_modified(true);
}
void MainWindow::char_maxMp_changed(quint16 value)
{
    ff7->setCharMaxMp(s,curchar,value);
    if(curchar==ff7->Party(s,0)){ff7->setDescMaxMP(s,value);}
    file_modified(true);
}
void MainWindow::char_kills_changed(quint16 value)
{
    ff7->setCharKills(s,curchar,value);
    file_modified(true);
}

void MainWindow::char_row_changed(quint8 value)
{
    ff7->setCharFlag(s,curchar,1,value);
    file_modified(true);
}

void MainWindow::char_levelProgress_changed(quint8 value)
{
    ff7->setCharFlag(s,curchar,2,value);
    file_modified(true);
}

void MainWindow::char_sadnessfury_changed(quint8 value)
{
    ff7->setCharFlag(s,curchar,0,value);
    file_modified(true);
}

void MainWindow::char_limits_changed(quint16 value)
{
    ff7->setCharLimits(s,curchar,value);
    file_modified(true);
}
void MainWindow::char_timesused1_changed(quint16 value)
{
    ff7->setCharTimeLimitUsed(s,curchar,1,value);
    file_modified(true);
}

void MainWindow::char_timeused2_changed(quint16 value)
{
    ff7->setCharTimeLimitUsed(s,curchar,2,value);
    file_modified(true);
}

void MainWindow::char_timeused3_changed(quint16 value)
{
    ff7->setCharTimeLimitUsed(s,curchar,3,value);
    file_modified(true);
}

void MainWindow::char_exp_changed(quint32 value)
{
    ff7->setCharCurrentExp(s,curchar,value);
    file_modified(true);
}

void MainWindow::char_expNext_changed(quint32 value)
{
    ff7->setCharNextExp(s,curchar,value);
    file_modified(true);
}

void MainWindow::char_mslot_changed(int slot){mslotsel=slot;}

void MainWindow::on_btn_maxChar_clicked()
{
    if(ff7->charID(s,curchar)==FF7Char::YoungCloud || ff7->charID(s,curchar) == FF7Char::Sephiroth  ||  _init){return;}//no char selected, sephiroth and young cloud.
    int result = QMessageBox::question(this,tr("Black Chococbo"),tr("Replace %1's Materia and Equipment").arg(ff7->charName(s,curchar)),QMessageBox::Yes,QMessageBox::No);
    switch(result)
    {
        case QMessageBox::Yes:char_editor->MaxStats();char_editor->MaxEquip();break;
        case QMessageBox::No: char_editor->MaxStats();break;
    }
    switch(curchar)
    {
        case 0: on_btn_cloud_clicked();break;
        case 1: on_btn_barret_clicked();break;
        case 2: on_btn_tifa_clicked();break;
        case 3: on_btn_aeris_clicked();break;
        case 4: on_btn_red_clicked();break;
        case 5: on_btn_yuffie_clicked();break;
        case 6: on_btn_cait_clicked();break;
        case 7: on_btn_vincent_clicked();break;
        case 8: on_btn_cid_clicked();break;
    }
}
void MainWindow::Items_Changed(QList<quint16> items)
{
    ff7->setItems(s,items);
    file_modified(true);
}
void MainWindow::on_sbSnowBegScore_valueChanged(int value){ff7->setSnowboardScore(s,0,value);}
void MainWindow::on_sbSnowExpScore_valueChanged(int value){ff7->setSnowboardScore(s,1,value);}
void MainWindow::on_sbSnowCrazyScore_valueChanged(int value){ff7->setSnowboardScore(s,2,value);}

void MainWindow::on_sbSnowBegMin_valueChanged(int value)
{if(!load){file_modified(true);
    quint32 time;
    time = ((value*60)*1000) + (ui->sbSnowBegSec->value()*1000) + ui->sbSnowBegMsec->value();
    ff7->setSnowboardTime(s,0,time);
}}

void MainWindow::on_sbSnowBegSec_valueChanged(int value)
{if(!load){file_modified(true);
        quint32 time;
        time = ((ui->sbSnowBegMin->value()*60)*1000) + (value*1000) + ui->sbSnowBegMsec->value();
        ff7->setSnowboardTime(s,0,time);
}}

void MainWindow::on_sbSnowBegMsec_valueChanged(int value)
{if(!load){file_modified(true);
        quint32 time;
        time = ((ui->sbSnowBegMin->value()*60)*1000) + (ui->sbSnowBegSec->value()*1000) + value;
        ff7->setSnowboardTime(s,0,time);
}}

void MainWindow::on_sbSnowExpMin_valueChanged(int value)
{if(!load){file_modified(true);
    quint32 time;
    time = ((value*60)*1000) + (ui->sbSnowExpSec->value()*1000) + ui->sbSnowExpMsec->value();
    ff7->setSnowboardTime(s,1,time);
}}

void MainWindow::on_sbSnowExpSec_valueChanged(int value)
{if(!load){file_modified(true);
        quint32 time;
        time = ((ui->sbSnowExpMin->value()*60)*1000) + (value*1000) + ui->sbSnowExpMsec->value();
        ff7->setSnowboardTime(s,1,time);
}}

void MainWindow::on_sbSnowExpMsec_valueChanged(int value)
{if(!load){file_modified(true);
        quint32 time;
        time = ((ui->sbSnowExpMin->value()*60)*1000) + (ui->sbSnowExpSec->value()*1000) + value;
        ff7->setSnowboardTime(s,1,time);
}}

void MainWindow::on_sbSnowCrazyMin_valueChanged(int value)
{if(!load){file_modified(true);
    quint32 time;
    time = ((value*60)*1000) + (ui->sbSnowCrazySec->value()*1000) + ui->sbSnowCrazyMsec->value();
    ff7->setSnowboardTime(s,2,time);
}}

void MainWindow::on_sbSnowCrazySec_valueChanged(int value)
{if(!load){file_modified(true);
        quint32 time;
        time = ((ui->sbSnowCrazyMin->value()*60)*1000) + (value*1000) + ui->sbSnowCrazyMsec->value();
        ff7->setSnowboardTime(s,2,time);
}}

void MainWindow::on_sbSnowCrazyMsec_valueChanged(int value)
{if(!load){file_modified(true);
        quint32 time;
        time = ((ui->sbSnowCrazyMin->value()*60)*1000) + (ui->sbSnowCrazySec->value()*1000) + value;
        ff7->setSnowboardTime(s,2,time);
}}
void MainWindow::on_sb_BikeHighScore_valueChanged(int arg1){if(!load){file_modified(true);ff7->setBikeHighScore(s,arg1);}}
void MainWindow::on_sb_BattlePoints_valueChanged(int arg1){if(!load){file_modified(true);ff7->setBattlePoints(s,arg1);}}
