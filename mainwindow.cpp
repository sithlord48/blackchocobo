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
//#include <QInputDialog>
/*~~~~~GLOBALS~~~~~~*/
//see the Header file private data members of the class.
/*~~~~~~EXTERNS~~~~~~~~*/
//these should be part of the ff7names class at some point.
extern quint32 chartnls[11][99]; //  Chars tnl Table (cloud - sephiroth)
extern quint32 charlvls[11][99]; //  Chars lvl Table
/*~~~~~~~~GUI Set Up~~~~~~~*/

MainWindow::MainWindow(QWidget *parent,FF7 *ff7data,QSettings *configdata)
    :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _init=true;
    ff7 =ff7data;
    settings =configdata;
    skip_slot_mask = settings->value("skip_slot_mask").toBool(); //skips setting the mask of last saved slot on writes. testing function
    file_changed=false;
    load=true;
    curchar =0;
    mslotsel=0;
    s=0;
    //set up comboboxes.
    for (int i=256;i<288;i++){ui->combo_armor->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
    for (int i=288;i<320;i++){ui->combo_acc->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
                              ui->combo_acc->addItem(QIcon(Items[288].image),tr("-None-"));//add clear option for accessories
    for (int i=0;i<320;i++){ui->combo_additem->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
    for (int i=0;i<0x5b;i++){ui->combo_add_mat->addItem(QIcon(Materias[i].image),FF7Strings.MateriaNames(i));}
    for (int i=0;i<0x5b;i++){ui->combo_add_mat_slot->addItem(QIcon(Materias[i].image),FF7Strings.MateriaNames(i));}
    for (int i=0;i<0x5b;i++){if(FF7Strings.MateriaNames(i) !=tr("DON'T USE")){ui->combo_add_mat_2->addItem(QIcon(Materias[i].image),FF7Strings.MateriaNames(i));}}
    for (int i=0;i<0x5b;i++){if(FF7Strings.MateriaNames(i) !=tr("DON'T USE")){ui->combo_add_mat_slot_2->addItem(QIcon(Materias[i].image),FF7Strings.MateriaNames(i));}}

    //set up tables..
    ui->tbl_location_field->setColumnWidth(0,147);
    ui->tbl_location_field->setColumnWidth(1,50);
    ui->tbl_location_field->setColumnWidth(2,50);
    ui->tbl_location_field->setColumnWidth(3,50);
    ui->tbl_location_field->setColumnWidth(4,50);

    QTableWidgetItem *newItem;
    locations Locations;
    ui->tbl_location_field->setRowCount(Locations.len());
    for (int i=0;i<ui->tbl_location_field->rowCount();i++)
    {
        newItem = new QTableWidgetItem(Locations.loc_name(i),0);
        ui->tbl_location_field->setItem(i,0,newItem);
        newItem = new QTableWidgetItem(Locations.map_id(i),0);
        ui->tbl_location_field->setItem(i,1,newItem);
        newItem = new QTableWidgetItem(Locations.loc_id(i),0);
        ui->tbl_location_field->setItem(i,2,newItem);
        newItem = new QTableWidgetItem(Locations.x(i),0);
        ui->tbl_location_field->setItem(i,3,newItem);
        newItem = new QTableWidgetItem(Locations.y(i),0);
        ui->tbl_location_field->setItem(i,4,newItem);
        newItem = new QTableWidgetItem(Locations.z(i),0);
        ui->tbl_location_field->setItem(i,5,newItem);
    }

    //Hide the stuff that needs to be hidden.
    ui->eskill_group->setVisible(false);
    ui->eskill_group_2->setVisible(false);
    ui->combo_add_mat->setVisible(false);
    ui->combo_add_mat_slot->setVisible(false);
    ui->combo_id->setVisible(false);
    ui->lbl_id->setVisible(false);
    ui->compare_table->setEnabled(false);
    ui->tbl_diff->setVisible(0);
    ui->bm_unknown->setVisible(0);
    ui->bh_id->setVisible(0);

    //chocobo boxes
    ui->box_stable1->setEnabled(false);
    ui->box_stable2->setEnabled(false);
    ui->box_stable3->setEnabled(false);
    ui->box_stable4->setEnabled(false);
    ui->box_stable5->setEnabled(false);
    ui->box_stable6->setEnabled(false);
    //testing stuff.

    ui->tabWidget->setTabEnabled(8,0);
    ui->lbl_0x34->setVisible(false);
    ui->lbl_0x35->setVisible(false);
    ui->lbl_0x36->setVisible(false);
    ui->lbl_0x37->setVisible(false);
    ui->lcd_0x34->setVisible(false);
    ui->lcd_0x35->setVisible(false);
    ui->lcd_0x36->setVisible(false);
    ui->lcd_0x37->setVisible(false);
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

    // load settings
    if(settings->value("show_test").toBool())
    {
        ui->action_show_debug->setChecked(1);
        ui->action_show_debug->setIcon(QIcon(":/icon/debug_sel"));
    }
    else{ui->action_show_debug->setChecked(0);}

    //are any empty? if so set them accordingly.
    if(!settings->value("font-size").toString().isEmpty()){QApplication::setFont(QFont(QApplication::font().family(),settings->value("font-size").toInt(),-1,false));}
    if(!settings->value("font-family").toString().isEmpty()){QApplication::setFont(QFont(settings->value("font-family").toString(),QApplication::font().pointSize(),-1,false));}
    if(settings->value("autochargrowth").isNull()){settings->setValue("autochargrowth",1);}
    if(settings->value("default_save_file").isNull()){settings->setValue("default_save_file",QString(QCoreApplication::applicationDirPath()) + "/"+ "save0");}
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
    // Connect the unknown and unknown compare scrolling.
    connect( ui->tbl_unknown->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->tbl_compare_unknown->verticalScrollBar(), SLOT(setValue(int)) );
    connect( ui->tbl_compare_unknown->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->tbl_unknown->verticalScrollBar(), SLOT(setValue(int)) );
    file_changed=false;
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
int MainWindow::save_changes(void)
{//return 0 to ingore the event/ return 1 to process event.
    int result; int rtn=0;
    result = QMessageBox::question(this,tr("Unsaved Changes"),tr("Save Changes to the File:\n%1").arg(filename),QMessageBox::Yes,QMessageBox::No,QMessageBox::Cancel);
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
        case QMessageBox::No:rtn=1;break;
        case QMessageBox::Cancel: rtn=0; break;
    }
    return rtn;
}
void MainWindow::closeEvent(QCloseEvent *e)
{if(file_changed){
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
    if(file_changed)
    {
        switch(save_changes())
        {
            case 0: return;//cancel load.
            case 1: break;//yes or no pressed..
        }
    }
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Final Fantasy 7 Save"),settings->value("load_path").toString(),
    tr("Known FF7 Save Types (*.ff7 *-S* *.psv *.vmp *.vgs *.mem *.gme *.mcr *.mcd *.mci *.mc *.ddf *.ps *.psm *.bin);;PC FF7 SaveGame (*.ff7);;Raw PSX FF7 SaveGame (*-S*);;MC SaveGame (*.mcr *.mcd *.mci *.mc *.ddf *.ps *.psm *.bin);;PSV SaveGame (*.psv);;PSP SaveGame (*.vmp);;VGS SaveGame(*.vgs *.mem);;Dex-Drive SaveGame(*.gme);;All Files(*)"));
    if (!fileName.isEmpty()){loadFileFull(fileName,0);}

}
void MainWindow::on_actionReload_triggered(){if(!filename.isEmpty()){loadFileFull(filename,1);}}
/*~~~~~~~~~~~~~~~~~Load Full ~~~~~~~~~~~~~~~~~~*/
void MainWindow::loadFileFull(const QString &fileName,int reload)
{//if called from reload then int reload ==1 (don't call slot select)
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly ))
    {
        QMessageBox::warning(this, tr("Black Chocobo"),
        tr("Cannot read file %1:\n%2.")
        .arg(fileName).arg(file.errorString()));
        return;
    }
    QByteArray ff7file;
    ff7file = file.readAll(); //put all data in temp raw file
    QByteArray temp; // create a temp to be used when needed
/*~~~~~~~~~~~~~~~~~~~~~~~~~~Set File Type Vars ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    int file_size = file.size();
    if((file_size == FF7_PC_SAVE_GAME_SIZE) && ff7file.startsWith("\x71\x73"))
    {
       ff7->SG_SIZE          = FF7_PC_SAVE_GAME_SIZE;
       ff7->SG_HEADER        = FF7_PC_SAVE_GAME_HEADER;
       ff7->SG_FOOTER        = FF7_PC_SAVE_GAME_FOOTER;
       ff7->SG_DATA_SIZE     = FF7_PC_SAVE_GAME_DATA_SIZE;
       ff7->SG_SLOT_HEADER   = FF7_PC_SAVE_GAME_SLOT_HEADER;
       ff7->SG_SLOT_FOOTER   = FF7_PC_SAVE_GAME_SLOT_FOOTER;
       ff7->SG_SLOT_SIZE     = FF7_PC_SAVE_GAME_SLOT_SIZE;
       ff7->SG_SLOT_NUMBER   = FF7_PC_SAVE_GAME_SLOT_NUMBER;
       ff7->SG_TYPE          = "PC";
       ff7->file_headerp     = ff7->file_header_pc;           //pointer to pc file header
       ff7->file_footerp     = ff7->file_footer_pc;           //pointer to pc file footer
    }
    else if((file_size == FF7_PSX_SAVE_GAME_SIZE)&& ff7file.startsWith("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60"))
    {//This should catch just about any false positive named *-S*
       ff7->SG_SIZE          = FF7_PSX_SAVE_GAME_SIZE;
       ff7->SG_HEADER        = FF7_PSX_SAVE_GAME_HEADER;
       ff7->SG_FOOTER        = FF7_PSX_SAVE_GAME_FOOTER;
       ff7->SG_DATA_SIZE     = FF7_PSX_SAVE_GAME_DATA_SIZE;
       ff7->SG_SLOT_HEADER   = FF7_PSX_SAVE_GAME_SLOT_HEADER;
       ff7->SG_SLOT_FOOTER   = FF7_PSX_SAVE_GAME_SLOT_FOOTER;
       ff7->SG_SLOT_SIZE     = FF7_PSX_SAVE_GAME_SLOT_SIZE;
       ff7->SG_SLOT_NUMBER   = FF7_PSX_SAVE_GAME_SLOT_NUMBER;
       ff7->SG_TYPE          = "PSX";
       ff7->file_headerp     = ff7->file_header_psx;          //pointer to psx file header
       ff7->file_footerp     = ff7->file_footer_psx;          //pointer to psx file footer
    }
    else if((file_size == FF7_MC_SAVE_GAME_SIZE) && ff7file.startsWith("\x4D\x43"))
    {
       ff7->SG_SIZE          = FF7_MC_SAVE_GAME_SIZE;
       ff7->SG_HEADER        = FF7_MC_SAVE_GAME_HEADER;
       ff7->SG_FOOTER        = FF7_MC_SAVE_GAME_FOOTER;
       ff7->SG_DATA_SIZE     = FF7_MC_SAVE_GAME_DATA_SIZE;
       ff7->SG_SLOT_HEADER   = FF7_MC_SAVE_GAME_SLOT_HEADER;
       ff7->SG_SLOT_FOOTER   = FF7_MC_SAVE_GAME_SLOT_FOOTER;
       ff7->SG_SLOT_SIZE     = FF7_MC_SAVE_GAME_SLOT_SIZE;
       ff7->SG_SLOT_NUMBER   = FF7_MC_SAVE_GAME_SLOT_NUMBER;
       ff7->SG_TYPE          = "MC";
       ff7->file_headerp     = ff7->file_header_mc;           //pointer to mc file header
       ff7->file_footerp     = ff7->file_footer_mc;           //pointer to mc file footer
    }

    else if((file_size == FF7_PSV_SAVE_GAME_SIZE) && ff7file.startsWith("\x00\x56\x53\x50"))
    {//CAUTION: be sure we are loading the correct kind of psv, pSX uses the extension for it's state files.
       ff7->SG_SIZE          = FF7_PSV_SAVE_GAME_SIZE;
       ff7->SG_HEADER        = FF7_PSV_SAVE_GAME_HEADER;
       ff7->SG_FOOTER        = FF7_PSV_SAVE_GAME_FOOTER;
       ff7->SG_DATA_SIZE     = FF7_PSV_SAVE_GAME_DATA_SIZE;
       ff7->SG_SLOT_HEADER   = FF7_PSV_SAVE_GAME_SLOT_HEADER;
       ff7->SG_SLOT_FOOTER   = FF7_PSV_SAVE_GAME_SLOT_FOOTER;
       ff7->SG_SLOT_SIZE     = FF7_PSV_SAVE_GAME_SLOT_SIZE;
       ff7->SG_SLOT_NUMBER   = FF7_PSV_SAVE_GAME_SLOT_NUMBER;
       ff7->SG_TYPE          = "PSV";
       ff7->file_headerp     = ff7->file_header_psv;          //pointer to psv file header
       ff7->file_footerp     = ff7->file_footer_psv;          //pointer to psv file footer
    }
    else if((file_size ==FF7_PSP_SAVE_GAME_SIZE) && ff7file.startsWith("\x00\x50\x4D\x56"))
    {
        ff7->SG_SIZE          = FF7_PSP_SAVE_GAME_SIZE;
        ff7->SG_HEADER        = FF7_PSP_SAVE_GAME_HEADER;
        ff7->SG_FOOTER        = FF7_PSP_SAVE_GAME_FOOTER;
        ff7->SG_DATA_SIZE     = FF7_PSP_SAVE_GAME_DATA_SIZE;
        ff7->SG_SLOT_HEADER   = FF7_PSP_SAVE_GAME_SLOT_HEADER;
        ff7->SG_SLOT_FOOTER   = FF7_PSP_SAVE_GAME_SLOT_FOOTER;
        ff7->SG_SLOT_SIZE     = FF7_PSP_SAVE_GAME_SLOT_SIZE;
        ff7->SG_SLOT_NUMBER   = FF7_PSP_SAVE_GAME_SLOT_NUMBER;
        ff7->SG_TYPE          = "PSP";
        ff7->file_headerp     = ff7->file_header_psp;          //pointer to psp file header
        ff7->file_footerp     = ff7->file_footer_psp;          //pointer to psp file footer
    }
    else if((file_size ==FF7_VGS_SAVE_GAME_SIZE) && ff7file.startsWith("\x56\x67\x73\x4D"))
    {
        ff7->SG_SIZE          = FF7_VGS_SAVE_GAME_SIZE;
        ff7->SG_HEADER        = FF7_VGS_SAVE_GAME_HEADER;
        ff7->SG_FOOTER        = FF7_VGS_SAVE_GAME_FOOTER;
        ff7->SG_DATA_SIZE     = FF7_VGS_SAVE_GAME_DATA_SIZE;
        ff7->SG_SLOT_HEADER   = FF7_VGS_SAVE_GAME_SLOT_HEADER;
        ff7->SG_SLOT_FOOTER   = FF7_VGS_SAVE_GAME_SLOT_FOOTER;
        ff7->SG_SLOT_SIZE     = FF7_VGS_SAVE_GAME_SLOT_SIZE;
        ff7->SG_SLOT_NUMBER   = FF7_VGS_SAVE_GAME_SLOT_NUMBER;
        ff7->SG_TYPE          = "VGS";
        ff7->file_headerp     = ff7->file_header_vgs;          //pointer to vgs file header
        ff7->file_footerp     = ff7->file_footer_vgs;          //pointer to vgs file footer
    }
    else if((file_size ==FF7_DEX_SAVE_GAME_SIZE) && ff7file.startsWith("\x31\x32\x33\x2D\x34\x35\x36\x2D\x53\x54\x44"))
    {
        ff7->SG_SIZE          = FF7_DEX_SAVE_GAME_SIZE;
        ff7->SG_HEADER        = FF7_DEX_SAVE_GAME_HEADER;
        ff7->SG_FOOTER        = FF7_DEX_SAVE_GAME_FOOTER;
        ff7->SG_DATA_SIZE     = FF7_DEX_SAVE_GAME_DATA_SIZE;
        ff7->SG_SLOT_HEADER   = FF7_DEX_SAVE_GAME_SLOT_HEADER;
        ff7->SG_SLOT_FOOTER   = FF7_DEX_SAVE_GAME_SLOT_FOOTER;
        ff7->SG_SLOT_SIZE     = FF7_DEX_SAVE_GAME_SLOT_SIZE;
        ff7->SG_SLOT_NUMBER   = FF7_DEX_SAVE_GAME_SLOT_NUMBER;
        ff7->SG_TYPE          = "DEX";
        ff7->file_headerp     = ff7->file_header_dex;          //pointer to dex file header
        ff7->file_footerp     = ff7->file_footer_dex;          //pointer to dex file footer
    }
    else
    {
        QMessageBox::warning(this, tr("Unknown Filetype"),
        tr("File: %1 \nis not a FF7 SaveGame.")
        .arg(fileName));
        return;
    }
    filename=fileName;
    /*~~~~~~~~~~Start Load~~~~~~~~~~*/
    memcpy(ff7->file_headerp,ff7file.mid(0x0000,ff7->SG_HEADER),ff7->SG_HEADER);// collect header (0x09) bytes (PC), (0x00) bytes (PSX), (0x2000) bytes (MC)
    for (int i=0;i<ff7->SG_SLOT_NUMBER;i++)
    {
        int index = (ff7->SG_SLOT_SIZE*i) + ff7->SG_HEADER + ff7->SG_SLOT_HEADER;
        memcpy(ff7->hf[i].sl_header,ff7file.mid((ff7->SG_SLOT_SIZE*i) + (ff7->SG_HEADER + 0x0000),ff7->SG_SLOT_HEADER),ff7->SG_SLOT_HEADER);// collect slot header (0x00) bytes (PC), (0x0200) bytes (PSX), (0x0200) bytes (MC)
        temp = ff7file.mid(index,0x10f4);
        memcpy(&ff7->slot[i],temp,0x10f4);
        memcpy(ff7->hf[i].sl_footer,ff7file.mid((ff7->SG_SLOT_SIZE*i)+ (ff7->SG_HEADER+ff7->SG_SLOT_HEADER+ff7->SG_DATA_SIZE),ff7->SG_SLOT_FOOTER),ff7->SG_SLOT_FOOTER);// collect slot footer (0x00) bytes (PC), (0x0D0C) bytes (PSX), (0x0D0C) bytes (MC)
    }
    /*~~~~~~~End Load~~~~~~~~~~~~~~*/
    _init=false;//we have now loaded a file
    ui->lbl_fileName->setText(fileName); //set filename then type specific actions.
    //Call guirefresh when not using slot select dialog.
    if (ff7->SG_TYPE == "PC")
    {
        if(ff7->slot[0].checksum != 0x0000 && ff7->slot[0].checksum != 0x4D1D){ff7->SG_Region_String[0]= "BASCUS-94163FF7-S01";} else {ff7->SG_Region_String[0].clear();}
        if(ff7->slot[1].checksum != 0x0000 && ff7->slot[1].checksum != 0x4D1D){ff7->SG_Region_String[1]= "BASCUS-94163FF7-S02";} else {ff7->SG_Region_String[1].clear();}
        if(ff7->slot[2].checksum != 0x0000 && ff7->slot[2].checksum != 0x4D1D){ff7->SG_Region_String[2]= "BASCUS-94163FF7-S03";} else {ff7->SG_Region_String[2].clear();}
        if(ff7->slot[3].checksum != 0x0000 && ff7->slot[3].checksum != 0x4D1D){ff7->SG_Region_String[3]= "BASCUS-94163FF7-S04";} else {ff7->SG_Region_String[3].clear();}
        if(ff7->slot[4].checksum != 0x0000 && ff7->slot[4].checksum != 0x4D1D){ff7->SG_Region_String[4]= "BASCUS-94163FF7-S05";} else {ff7->SG_Region_String[4].clear();}
        if(ff7->slot[5].checksum != 0x0000 && ff7->slot[5].checksum != 0x4D1D){ff7->SG_Region_String[5]= "BASCUS-94163FF7-S06";} else {ff7->SG_Region_String[5].clear();}
        if(ff7->slot[6].checksum != 0x0000 && ff7->slot[6].checksum != 0x4D1D){ff7->SG_Region_String[6]= "BASCUS-94163FF7-S07";} else {ff7->SG_Region_String[6].clear();}
        if(ff7->slot[7].checksum != 0x0000 && ff7->slot[7].checksum != 0x4D1D){ff7->SG_Region_String[7]= "BASCUS-94163FF7-S08";} else {ff7->SG_Region_String[7].clear();}
        if(ff7->slot[8].checksum != 0x0000 && ff7->slot[8].checksum != 0x4D1D){ff7->SG_Region_String[8]= "BASCUS-94163FF7-S09";} else {ff7->SG_Region_String[8].clear();}
        if(ff7->slot[9].checksum != 0x0000 && ff7->slot[9].checksum != 0x4D1D){ff7->SG_Region_String[9]= "BASCUS-94163FF7-S10";} else {ff7->SG_Region_String[9].clear();}
        if(ff7->slot[10].checksum != 0x0000 && ff7->slot[10].checksum != 0x4D1D){ff7->SG_Region_String[10]= "BASCUS-94163FF7-S11";} else {ff7->SG_Region_String[10].clear();}
        if(ff7->slot[11].checksum != 0x0000 && ff7->slot[11].checksum != 0x4D1D){ff7->SG_Region_String[11]= "BASCUS-94163FF7-S12";} else {ff7->SG_Region_String[11].clear();}
        if(ff7->slot[12].checksum != 0x0000 && ff7->slot[12].checksum != 0x4D1D){ff7->SG_Region_String[12]= "BASCUS-94163FF7-S13";} else {ff7->SG_Region_String[12].clear();}
        if(ff7->slot[13].checksum != 0x0000 && ff7->slot[13].checksum != 0x4D1D){ff7->SG_Region_String[13]= "BASCUS-94163FF7-S14";} else {ff7->SG_Region_String[13].clear();}
        if(ff7->slot[14].checksum != 0x0000 && ff7->slot[14].checksum != 0x4D1D){ff7->SG_Region_String[14]= "BASCUS-94163FF7-S15";} else {ff7->SG_Region_String[14].clear();}
        if(reload){guirefresh(0);}   else{on_actionShow_Selection_Dialog_activated();}
    }

    else if (ff7->SG_TYPE == "PSX")
    {
        s=0;
        if((fileName.contains("00867")) || (fileName.contains("00869")) || (fileName.contains("00900")) ||
           (fileName.contains("94163")) || (fileName.contains("00700")) || (fileName.contains("01057")) ||
           (fileName.contains("00868")) )
        {
            QString string;
            string = fileName.mid(fileName.lastIndexOf("/")+1,fileName.lastIndexOf(".")-1-fileName.lastIndexOf("/"));
            ff7->SG_Region_String[s]= string.mid(string.lastIndexOf("BA")-1,string.lastIndexOf("FF7-S")+8);
        }
        else {ff7->SG_Region_String[s].clear();}
        for(int i=1;i<14;i++){clearslot(i);}
        guirefresh(0);
    }

    else if (ff7->SG_TYPE =="PSV")
    {
        s=0;
        ff7->SG_Region_String[s] = QString(ff7file.mid(0x64,19));
        for(int i=1;i<14;i++){clearslot(i);}
        guirefresh(0);
    }

    else if (ff7->SG_TYPE == "MC" || ff7->SG_TYPE =="PSP" || ff7->SG_TYPE == "VGS" ||ff7->SG_TYPE=="DEX")
    {
        QByteArray mc_header;
        int offset = 0;//raw psx card types
        if(ff7->SG_TYPE =="PSP"){offset = 0x80;}
        if(ff7->SG_TYPE =="VGS"){offset = 0x40;}
        if(ff7->SG_TYPE =="DEX"){offset = 0xF40;}
        mc_header = ff7file.mid(offset,ff7->SG_HEADER);
        int index=0;
        for(int i=0; i<15;i++)
        {
            index = (128*i) +138;
            ff7->SG_Region_String[i] = QString(mc_header.mid(index,19));
        }
        if(reload){guirefresh(0);}   else{on_actionShow_Selection_Dialog_activated();}
    }
    else{/*UNKNOWN FILETYPE*/}
    file_changed=false;
}
/*~~~~~~~~~~~~~~~~~IMPORT PSX~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionFrom_PSX_Slot_activated()
{//should check better to be sure its a raw PSX SAVE. then make file filter *
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Select Final Fantasy 7 PSX Save"),QDir::homePath(),tr("Raw PSX FF7 SaveGame (*)"));

    if(fileName.isEmpty()){return;}
    else
    {
            QFile file(fileName);
            if(!file.open(QFile::ReadOnly))
            {
                QMessageBox::warning(this, tr("Black Chocobo"),
                tr("Cannot read file %1:\n%2.")
                .arg(fileName).arg(file.errorString()));
                return;
            }
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file

        if((file.size() ==FF7_PSX_SAVE_GAME_SIZE) && ff7file.startsWith("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60"))
        {
            QByteArray temp; // create a temp to be used when needed
            int index = 0x200;
            temp = ff7file.mid(index,0x10f4);
            memcpy(&ff7->slot[s],temp,0x10f4);
            if((fileName.contains("00867")) || (fileName.contains("00869")) || (fileName.contains("00900")) ||
              (fileName.contains("94163")) || (fileName.contains("00700")) || (fileName.contains("01057")) || (fileName.contains("00868")))
            {
                QString string;
                string = fileName.mid(fileName.lastIndexOf("/")+1,fileName.lastIndexOf(".")-1-fileName.lastIndexOf("/"));
                ff7->SG_Region_String[s]= string.mid(string.lastIndexOf("BA")-1,string.lastIndexOf("FF7-S")+8);
            }
            else {ff7->SG_Region_String[s].clear();}
        }
        else{QMessageBox::warning(this,tr("Black Chocobo"),tr("The File %1\n is NOT a PSX Save").arg(fileName));return;}
    }//Parse slot data....
    guirefresh(0);
    file_changed=true;

}
/*~~~~~~~~~~~~~~~~~IMPORT PSV~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionFrom_PSV_Slot_activated()
{//check beter to be sure its the correct PSV type file.
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Select Final Fantasy 7 PSV Save"),QDir::homePath(),tr("PSV FF7 SaveGame (*.psv)"));
    if (fileName.isEmpty()){return;}
    else
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly))
        {
            QMessageBox::warning(this, tr("Black Chocobo"),
            tr("Cannot read file %1:\n%2.")
            .arg(fileName).arg(file.errorString()));
            return;
        }
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        QByteArray temp; // create a temp to be used when needed
        if((file.size() ==FF7_PSV_SAVE_GAME_SIZE) && ff7file.startsWith("\x00\x56\x53\x50"))
        {
            int index = 0x284;
            temp = ff7file.mid(index,0x10f4);
            memcpy(&ff7->slot[s],temp,0x10f4);
            if((fileName.contains("00867")) || (fileName.contains("00869")) || (fileName.contains("00900")) ||
               (fileName.contains("94163")) || (fileName.contains("00700")) || (fileName.contains("01057")) || (fileName.contains("00868")))
                {ff7->SG_Region_String[s] = QString(ff7file.mid(0x64,19));}
            else {ff7->SG_Region_String[s].clear();}
        }//Parse slot data....
        else{QMessageBox::warning(this,tr("Black Chocobo"),tr("The File %1\n is NOT a PSV Save").arg(fileName)); return;}
    file_changed=true;
    guirefresh(0);
    }
}
/*~~~~~~~~~~~~~~~~~IMPORT Char~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionImport_char_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Select FF7 Character Stat File"),settings->value("char_stat_folder").toString(),tr("FF7 Character Stat File(*.char)"));
    if (fileName.isEmpty()){return;}
    else
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly))
        {
            QMessageBox::warning(this, tr("Black Chocobo"),
            tr("Cannot read file %1:\n%2.")
            .arg(fileName).arg(file.errorString()));
            return;
        }
        if(file.size() !=0x84)
        {
            QMessageBox::warning(this, tr("Black Chocobo"),
            tr("%1:\n%2 is Not a FF7 Character Stat File.")
            .arg(fileName).arg(file.errorString()));
            return;
        }
        QByteArray ff7file;
        ff7file = file.readAll();
        memcpy(&ff7->slot[s].chars[curchar],ff7file,132);
    }
    file_changed=true;
    charupdate();
}

void MainWindow::on_actionExport_char_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save FF7 Character File"), settings->value("char_stat_folder").toString(),
    tr("FF7 Character Stat File(*.char)"));
    if (!fileName.isEmpty())
    {
        FILE *pfile;
        pfile = fopen(fileName.toAscii(),"wb");
        fwrite(&ff7->slot[s].chars[curchar],132,1,pfile);
        fclose(pfile);
    }
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

    if(!filename.isEmpty())
    {
        if(ff7->SG_TYPE=="PC"){fix_pc_bytemask(ff7,s,skip_slot_mask);}
        else if(ff7->SG_TYPE=="PSX"){fix_psx_header(ff7,s);}

        else if(ff7->SG_TYPE=="MC" || ff7->SG_TYPE=="PSP" || ff7->SG_TYPE=="VGS" || ff7->SG_TYPE =="DEX")
        {
            fix_vmc_header(ff7);
            if(ff7->SG_TYPE=="PSP"){QMessageBox::information(this,tr("PSP Save Notice"),tr("This File Does Not Have An Updated Checksum.It will not work on your PSP."));}
        }

        else if(ff7->SG_TYPE=="PSV")
        {
            /*FIX CHECKSUM FIRST!*/
            QMessageBox::information(this,tr("PSV Save Notice"),tr("This File Does Not Have An Updated Checksum.It will not work on your PS3."));
        }
        else {QMessageBox::warning(this, tr("Black Chocobo"),tr("Cannot save This Type of File"));return;}
        saveFileFull(filename);
    }
    else{on_actionSave_File_As_activated();return;}//there is no filename we should get one from save as..
}

void MainWindow::on_actionSave_File_As_activated()
{QString fileName;
// check for the type of save loaded and set the output type so we don't save the wrong type, all conversion opperations should be done via an Export function.
    if(ff7->SG_TYPE == "PC")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 PC SaveGame"), settings->value("save_pc_path").toString(),
        tr("FF7 PC SaveGame(*.ff7)"));
        fix_pc_bytemask(ff7,s,skip_slot_mask);// adjust the bytemask so the correct slots are shown
    }
    else if(ff7->SG_TYPE == "PSX")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 PSX SaveGame"), QDir::homePath(),
        tr("FF7 Raw PSX SaveGame(*-S*)"));
        fix_psx_header(ff7,s);
    }
    else if(ff7->SG_TYPE == "MC")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 MC SaveGame"), settings->value("save_emu_path").toString(),
        tr("FF7 MC SaveGame(*.mcr *.mcd *.mci *.mc *.ddf *.ps *.psm *.bin)"));
        fix_vmc_header(ff7);

    }
    else if(ff7->SG_TYPE == "PSV")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 PSV SaveGame"), QDir::homePath(),
        tr("FF7 PSV SaveGame(*.psv)"));
        QMessageBox::information(this,tr("PSV Save Notice"),tr("This File Does Not Have An Updated Checksum.It will not work on your PS3."));
    }
    else if(ff7->SG_TYPE == "PSP")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7  PSP SaveGame"), QDir::homePath(),
        tr("FF7 PSP SaveGame(*.vmp)"));
        fix_vmc_header(ff7);
        QMessageBox::information(this,tr("PSP Save Notice"),tr("This File Does Not Have An Updated Checksum.It will not work on your PSP."));

    }
    else if(ff7->SG_TYPE == "VGS")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7  VGS SaveGame"), settings->value("save_emu_path").toString(),
        tr("FF7 VGS SaveGame(*.vgs *.mem)"));
        fix_vmc_header(ff7);
    }
    else if(ff7->SG_TYPE == "DEX")
    {
        fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7  Dex-Drive SaveGame"), settings->value("save_emu_path").toString(),
        tr("FF7 Dex SaveGame(*.gme)"));
        fix_vmc_header(ff7);
    }
    else
    {//mystery type. make the user tell us user maybe used new game or made save manually.
        QStringList types;
        types << tr("PC")<<tr("Raw Psx Save")<<tr("Generic Emulator Memorycard")<<tr("PSP")<<tr("PS3")<<tr("Dex Drive Memorycard")<<tr("VGS Memorycard");
        QString result = QInputDialog::getItem(this,tr("Save Error"),tr("Please Select A File Type To Save"),types,-1,0,0,0);
        //check the string. and assign a type
        if(result ==types.at(0)){ff7->SG_TYPE = "PC";}
            else if(result ==types.at(1)){ff7->SG_TYPE = "PSX";}
            else if(result ==types.at(2)){ff7->SG_TYPE = "MC";}
            else if(result ==types.at(3)){ff7->SG_TYPE = "PSP";}
            else if(result ==types.at(4)){ff7->SG_TYPE = "PSV";}
            else if(result ==types.at(5)){ff7->SG_TYPE = "DEX";}
            else if(result ==types.at(6)){ff7->SG_TYPE = "VGS";}
            else{return;}
            on_actionSave_File_As_activated(); //now that we have a type do again.
    }
    if(fileName.isEmpty()){return;}
    saveFileFull(fileName); //reguardless save the file of course if its has a string.
    filename=fileName;//update filename.
    ui->lbl_fileName->setText(filename);//update bar..
}
/*~~~~~~~~~~~SHORT SAVE~~~~~~~~~~~~*/
void MainWindow::saveFileFull(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadWrite))
    {
        QMessageBox::warning(this, tr("Black Chocobo"),
        tr("Cannot write file %1:\n%2.")
            .arg(fileName)
            .arg(file.errorString()));
        return;
    }
    FILE *pfile;
    pfile = fopen(fileName.toAscii(),"wb");
    fwrite(ff7->file_headerp,ff7->SG_HEADER,1,pfile);
    for(int si=0;si<ff7->SG_SLOT_NUMBER;si++)
    {
        fwrite(ff7->hf[si].sl_header,ff7->SG_SLOT_HEADER,1,pfile);
        fwrite(&ff7->slot[si],ff7->SG_DATA_SIZE,1,pfile);
        fwrite(ff7->hf[si].sl_footer,ff7->SG_SLOT_FOOTER,1,pfile);
    }
    fwrite(ff7->file_footerp,ff7->SG_FOOTER,1,pfile);
    fclose(pfile);
    fix_sum(fileName);
    file_changed=false;
    if(_init)
    {//if no save was loaded and new game was clicked be sure to act like a game was loaded.
        filename=fileName;//update filename.
        ui->lbl_fileName->setText(filename);//update bar..
        _init=false;
        guirefresh(0);
    }
}

/*~~~~~~~~~~~ START CHECKSUM VEGETA~~~~~~~~~~~*/
void MainWindow::fix_sum(const QString &fileName)
{
    void * memory;
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite )){return;}
    QDataStream out (&file);
    out.setByteOrder(QDataStream::LittleEndian);
    file.seek(0);//Set pointer to the Beggining
    QByteArray ff7savefile;
    ff7savefile = file.readAll(); //put all data in temp raw file
    memory = (void*) malloc(ff7->SG_SIZE);//Memory Allocation
    if (!memory){return;}
    file.seek(0);
    memcpy(memory,ff7savefile.mid(0x00000,ff7->SG_SIZE),ff7->SG_SIZE);
    //Do checksum foreach slot
    for(int i=0, checksum=0; i<ff7->SG_SLOT_NUMBER; i++)
    {
        char * data_pointer = ((char*)memory + ff7->SG_HEADER + ff7->SG_SLOT_SIZE*i + ff7->SG_SLOT_HEADER + 0x04);
        checksum = ff7__checksum(data_pointer); //2 Bytes checksum (a 16-bit Byte checksum)
        if(checksum != 0x4D1D) //if is a blank slot don't write checksum!
        {
            int index = ff7->SG_HEADER + ff7->SG_SLOT_SIZE*i + ff7->SG_SLOT_HEADER;
            file.seek(index);
            out << checksum;
        }
    }
    file.close();
    free(memory);
}
/*~~~~~~~~~~~~ END CHECKSUM VEGETA~~~~~~~~~~~*/
/*~~~~~~~~END SHORT SAVE~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~New_Game~~~~~~~~~~~*/
void MainWindow::on_actionNew_Game_triggered()
{
    QFile file(settings->value("default_save_file").toString());
    if(!file.open(QFile::ReadOnly))
    {
         QMessageBox::warning(this, tr("Black Chocobo"),
             tr("Cannot read file %1:\n%2 Be Sure its is a Raw PSX Save")
            .arg(settings->value("default_save_file").toString()).arg(file.errorString()));
         return;
    }
    QByteArray ff7file;
    ff7file = file.readAll(); //put all data in temp raw file
    QByteArray temp; // create a temp to be used when needed
    int index = 0x200;
    temp = ff7file.mid(index,0x10f4);
    memcpy(&ff7->slot[s],temp,0x10f4);
    //check for non english and set names accordingly.
    if(ff7->SG_Region_String[s].contains("00700") || ff7->SG_Region_String[s].contains("01057"))
    {
        for(int c=0;c<9;c++){for(int i=0;i<12;i++){ff7->slot[s].chars[c].name[i]=0xFF;}}
        QByteArray temp =Text.toFF7(QString::fromUtf8("元ソルジャー"));
        memcpy(ff7->slot[s].chars[0].name,temp,temp.length());
        temp =Text.toFF7(QString::fromUtf8("バレット"));
        memcpy(&ff7->slot[s].chars[1].name,temp,temp.length());
        temp =Text.toFF7(QString::fromUtf8("ティファ"));
        memcpy(&ff7->slot[s].chars[2].name,temp,temp.length());
        temp =Text.toFF7(QString::fromUtf8("エアリス"));
        memcpy(&ff7->slot[s].chars[3].name,temp,temp.length());
        temp =Text.toFF7(QString::fromUtf8("レッド⑬"));
        memcpy(&ff7->slot[s].chars[4].name,temp,temp.length());
        temp =Text.toFF7(QString::fromUtf8("ユフィ"));
        memcpy(&ff7->slot[s].chars[5].name,temp,temp.length());
        temp =Text.toFF7(QString::fromUtf8(""));
        memcpy(&ff7->slot[s].chars[6].name,temp,temp.length());
        temp =Text.toFF7(QString::fromUtf8("セフィロス"));
        memcpy(&ff7->slot[s].chars[7].name,temp,temp.length());
        temp =Text.toFF7(QString::fromUtf8("シド"));
        memcpy(&ff7->slot[s].chars[8].name,temp,temp.length());
    }
    else if(ff7->SG_Region_String[s].isEmpty()){ff7->SG_Region_String[s] = "BASCUS-94163FF7-S01";}
    if(!load){file_changed=true;}
    guirefresh(1);
}
/*~~~~~~~~~~End New_Game~~~~~~~~~~~*/
/*~~~~~~~~~~New Game + ~~~~~~~~~~~~*/
void MainWindow::on_actionNew_Game_Plus_triggered()
{
    QFile file(settings->value("default_save_file").toString());
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Black Chocobo"),
        tr("Cannot read file %1:\n%2., Be Sure its is a Raw PSX Save")
        .arg(settings->value("default_save_file").toString()).arg(file.errorString()));
        return;
    }
    QByteArray ff7file;
    ff7file = file.readAll(); //put all data in temp raw file
    QByteArray temp; // create a temp to be used when needed
    int index = 0x200;
    temp = ff7file.mid(index,0x10f4); // dump file -> temp
    memcpy(&bufferslot,temp,0x10f4);  // copy temp to the buffer slot
    buffer_region = ff7->SG_Region_String[s];
    ui->line_location->setText(tr("New Game +"));
    memcpy(&bufferslot.desc,&ff7->slot[s].desc,0x44); // keep a old preview
    memcpy(&bufferslot.colors,&ff7->slot[s].colors,12); // keep old colors.
    for(int i=0;i<9;i++) // keep all old character info.
    {
        if((i==6)||(i==7))// except we have to export cait sith and vincent.the game needs y.cloud/seppie,for the flash back.
        {
            QString fileName;
            if(i==6) //export cait sith. cait sith's stats are only generated when he joins the party.
            {
                    fileName.append(filename);
                    fileName.append("-cait_sith");
                    if(ff7->SG_TYPE != "PSX" || ff7->SG_TYPE != "PSV")
                    {
                        fileName.append("-");
                        QString str;
                        str.setNum(s,10)+1;
                        fileName.append(str);
                    }
                }
            else if(i==7)// export vincent. vincent's stats are only generated when he joins the party.
                {
                    fileName.append(filename);
                    fileName.append("-vincent");
                    if(ff7->SG_TYPE != "PSX" || ff7->SG_TYPE != "PSV")
                    {
                        fileName.append("-");
                        QString str;
                        str.setNum(s,10)+1;
                        fileName.append(str);
                    }
                }
            fileName.append(".char");
            QFile file(fileName);
            if(!file.open(QFile::ReadWrite))
            {
                QMessageBox::warning(this, tr("Black Chocobo"),
                tr("Cannot write file %1:\n%2.")
                    .arg(fileName)
                    .arg(file.errorString()));
                return;
            }
            FILE *pfile;
            pfile = fopen(fileName.toAscii(),"wb");
            fwrite(&ff7->slot[s].chars[i],132,1,pfile);
            fclose(pfile);

        }
        else{memcpy(&bufferslot.chars[i],&ff7->slot[s].chars[i],0x84);} // normal character
    }
    memcpy(&bufferslot.items,ff7->slot[s].items,640);// copy items
    memcpy(&bufferslot.materias,ff7->slot[s].materias,800); // copy materia
    bufferslot.gil = ff7->slot[s].gil; // copy gil
    bufferslot.battles = ff7->slot[s].battles; // copy battle count
    bufferslot.runs = ff7->slot[s].runs; // copy run count
    bufferslot.gp = ff7->slot[s].gp; // copy gp
    //copy chocobo info.
    bufferslot.stables = ff7->slot[s].stables;
    bufferslot.stablesoccupied = ff7->slot[s].stablesoccupied;
    for(int i=0;i<4;i++){memcpy(&bufferslot.chocobos[i],&ff7->slot[s].chocobos[i],0x10);}
    memcpy(&bufferslot.chocobonames,ff7->slot[s].chocobonames,36);
    memcpy(&bufferslot.chocostaminas,ff7->slot[s].chocostaminas,12);
    for(int i=0;i<2;i++){memcpy(&bufferslot.choco56,ff7->slot[s].choco56,0x10);}
    // copy options
    bufferslot.battlespeed =ff7->slot[s].battlespeed;
    bufferslot.battlemspeed =ff7->slot[s].battlemspeed;
    bufferslot.options1 = ff7->slot[s].options1;
    bufferslot.options2 = ff7->slot[s].options2;
    memcpy(&bufferslot.controller_map,ff7->slot[s].controller_map,16);
    bufferslot.fieldmspeed = ff7->slot[s].fieldmspeed;
    /*~~ buffer now ready to be copied~*/
    memcpy(&ff7->slot[s],&bufferslot,0x10f4); // copy buffer to the current slot.
    if(!load){file_changed=true;}
    guirefresh(0);
}
/*~~~~~~~~~~End New_Game +~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~EXPORT PC~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionExport_PC_Save_activated()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 SaveGame"),  settings->value("export_pc").toString() ,
    tr("FF7 SaveGame(*.ff7)")); // Only Allow PC save Since we are going to make one
    if (fileName.isEmpty()){return;}// catch if Cancel is pressed
    if(ff7->SG_TYPE !="PC")
    {
        ui->combo_control->setCurrentIndex(0); // if not pc then chance of breaking controls.
        // no need to change if its pc already.
        ff7->SG_SIZE          = FF7_PC_SAVE_GAME_SIZE;
        ff7->SG_HEADER        = FF7_PC_SAVE_GAME_HEADER;
        ff7->SG_FOOTER        = FF7_PC_SAVE_GAME_FOOTER;
        ff7->SG_DATA_SIZE     = FF7_PC_SAVE_GAME_DATA_SIZE;
        ff7->SG_SLOT_HEADER   = FF7_PC_SAVE_GAME_SLOT_HEADER;
        ff7->SG_SLOT_FOOTER   = FF7_PC_SAVE_GAME_SLOT_FOOTER;
        ff7->SG_SLOT_SIZE     = FF7_PC_SAVE_GAME_SLOT_SIZE;
        ff7->SG_SLOT_NUMBER   = FF7_PC_SAVE_GAME_SLOT_NUMBER;
        ff7->SG_TYPE          = "PC";
        ff7->file_headerp     = ff7->file_header_pc;           //pointer to pc file header
        ff7->file_footerp     = ff7->file_footer_pc;           //pointer to pc file footer
        // Add File Header
        for(int i=0;i<9;i++){ff7->file_header_pc[i]= PC_SAVE_GAME_FILE_HEADER[i];}
    }
    fix_pc_bytemask(ff7,s,skip_slot_mask);
    int result=0;
    for(int si=0;si<15;si++)//clean up non ff7 saves and fix time for Pal Saves.
    {
        if (ff7->SG_Region_String[si].contains("94163") || ff7->SG_Region_String[si].contains("00700") || ff7->SG_Region_String[si].contains("01057")){/*FF7File AND NTSC*/}
        else if(ff7->SG_Region_String[si].contains("00867") || ff7->SG_Region_String[si].contains("00868")|| ff7->SG_Region_String[si].contains("00869") || ff7->SG_Region_String[si].contains("00900"))
        {/*PAL, Correct Time?*/
            if((result==QMessageBox::YesToAll) || (result==QMessageBox::NoToAll)){/*Already Chosen Yes/No to all*/}
            else
            {//Show the Dialog
                QMessageBox fixtime(this);
                fixtime.setIconPixmap(QPixmap(":/icon/fix_time"));
                fixtime.setText(tr("Slot:%1 Contains A PAL region save").arg(QString::number(si+1)));
                fixtime.setInformativeText(tr("PAL PSX runs at 50/60 speed\nThis results in an incorrect playtime\nWould you like to correct the playtime?"));
                fixtime.setWindowTitle(tr("PAL Slot Detected"));
                fixtime.addButton(QMessageBox::Yes);
                fixtime.addButton(QMessageBox::YesToAll);
                fixtime.addButton(QMessageBox::No);
                fixtime.addButton(QMessageBox::NoToAll);
                fixtime.setButtonText( QMessageBox::YesToAll,tr("Always Correct"));
                fixtime.setButtonText( QMessageBox::NoToAll,tr("Never Correct"));
                fixtime.setDefaultButton(QMessageBox::YesToAll);
                result=fixtime.exec();
            }
            switch(result)
            {
            case QMessageBox::No:break;
            case QMessageBox::NoToAll:break;
            default:ff7->slot[si].time = (ff7->slot[si].time*1.2); ff7->slot[si].desc.time = ff7->slot[si].time;break;
            }
        }

        else{clearslot(si);}
    }
    saveFileFull(fileName);
}
/*~~~~~~~~~~~~~~~~~EXPORT PSX~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionExport_PSX_activated()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 SaveGame"), ff7->SG_Region_String[s],
    tr("BASCUS-94163FF7-Sxx(*-S*);;BESCES-00867FF7-Sxx(*-S*);;BESCES-00868FF7-Sxx(*-S*);;BESCES-00869FF7-Sxx(*-S*);;BESCES-00900FF7-Sxx(*-S*);;BISLPS-00700FF7-Sxx(*-S*);;BISLPS-01057FF7-Sxx(*-S*)"));
    if(ff7->SG_TYPE != "PSX")
    {
        ui->combo_control->setCurrentIndex(0);

        ff7->SG_SIZE          = FF7_PSX_SAVE_GAME_SIZE;
        ff7->SG_HEADER        = FF7_PSX_SAVE_GAME_HEADER;
        ff7->SG_FOOTER        = FF7_PSX_SAVE_GAME_FOOTER;
        ff7->SG_DATA_SIZE     = FF7_PSX_SAVE_GAME_DATA_SIZE;
        ff7->SG_SLOT_HEADER   = FF7_PSX_SAVE_GAME_SLOT_HEADER;
        ff7->SG_SLOT_FOOTER   = FF7_PSX_SAVE_GAME_SLOT_FOOTER;
        ff7->SG_SLOT_SIZE     = FF7_PSX_SAVE_GAME_SLOT_SIZE;
        ff7->SG_SLOT_NUMBER   = FF7_PSX_SAVE_GAME_SLOT_NUMBER;
        ff7->SG_TYPE          = "PSX";
        ff7->file_headerp     = ff7->file_header_psx;           //pointer to psx file header
        ff7->file_footerp     = ff7->file_footer_psx;           //pointer to psx file footer
    }
    if(fileName.endsWith("S01")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S01[i];}}
    else if(fileName.endsWith("S02")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S02[i];}}
    else if(fileName.endsWith("S03")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S03[i];}}
    else if(fileName.endsWith("S04")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S04[i];}}
    else if(fileName.endsWith("S05")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S05[i];}}
    else if(fileName.endsWith("S06")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S06[i];}}
    else if(fileName.endsWith("S07")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S07[i];}}
    else if(fileName.endsWith("S08")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S08[i];}}
    else if(fileName.endsWith("S09")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S09[i];}}
    else if(fileName.endsWith("S10")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S10[i];}}
    else if(fileName.endsWith("S11")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S11[i];}}
    else if(fileName.endsWith("S12")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S12[i];}}
    else if(fileName.endsWith("S13")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S13[i];}}
    else if(fileName.endsWith("S14")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S14[i];}}
    else if(fileName.endsWith("S15")){for(int i=0;i<256;i++){ff7->hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S15[i];}}
    else{QMessageBox::information(this,tr("Bad Psx Save Name"), tr("Can't Decide On What Header to Write, Please Add the suffix -SXX (where x= 01-15, with leading 0 if < 10) A Header for that slot number will be written to the save"));return;}
    fix_psx_header(ff7,0);
    saveFileFull(fileName);
}
/*~~~~~Export Mcr/Mcd~~~~~~*/
void MainWindow::on_actionExport_MC_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 MC SaveGame"), settings->value("save_emu_path").toString(),
    tr("FF7 MC SaveGame(*.mcr *.mcd *.mci *.mc *.ddf *.ps *.psm *.bin)"));

        if(fileName.isEmpty()){return;}
    if(ff7->SG_TYPE != "MC")
    {
        ui->combo_control->setCurrentIndex(0);

        ff7->SG_SIZE          = FF7_MC_SAVE_GAME_SIZE;
        ff7->SG_HEADER        = FF7_MC_SAVE_GAME_HEADER;
        ff7->SG_FOOTER        = FF7_MC_SAVE_GAME_FOOTER;
        ff7->SG_DATA_SIZE     = FF7_MC_SAVE_GAME_DATA_SIZE;
        ff7->SG_SLOT_HEADER   = FF7_MC_SAVE_GAME_SLOT_HEADER;
        ff7->SG_SLOT_FOOTER   = FF7_MC_SAVE_GAME_SLOT_FOOTER;
        ff7->SG_SLOT_SIZE     = FF7_MC_SAVE_GAME_SLOT_SIZE;
        ff7->SG_SLOT_NUMBER   = FF7_MC_SAVE_GAME_SLOT_NUMBER;
        ff7->SG_TYPE          = "MC";
        ff7->file_headerp     = ff7->file_header_mc;           //pointer to mc file header
        ff7->file_footerp     = ff7->file_footer_mc;           //pointer to mc file footer
    }
    fix_vmc_header(ff7);
    saveFileFull(fileName);
}
void MainWindow::on_actionExport_VGS_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 VGS SaveGame"), settings->value("save_emu_path").toString(),
    tr("FF7 VGS SaveGame(*.vgs *.mem)"));
    if(fileName.isEmpty()){return;}
    if(ff7->SG_TYPE != "VGS")
    {
        ui->combo_control->setCurrentIndex(0);

        ff7->SG_SIZE          = FF7_VGS_SAVE_GAME_SIZE;
        ff7->SG_HEADER        = FF7_VGS_SAVE_GAME_HEADER;
        ff7->SG_FOOTER        = FF7_VGS_SAVE_GAME_FOOTER;
        ff7->SG_DATA_SIZE     = FF7_VGS_SAVE_GAME_DATA_SIZE;
        ff7->SG_SLOT_HEADER   = FF7_VGS_SAVE_GAME_SLOT_HEADER;
        ff7->SG_SLOT_FOOTER   = FF7_VGS_SAVE_GAME_SLOT_FOOTER;
        ff7->SG_SLOT_SIZE     = FF7_VGS_SAVE_GAME_SLOT_SIZE;
        ff7->SG_SLOT_NUMBER   = FF7_VGS_SAVE_GAME_SLOT_NUMBER;
        ff7->SG_TYPE          = "VGS";
        ff7->file_headerp     = ff7->file_header_vgs;           //pointer to mc file header
        ff7->file_footerp     = ff7->file_footer_vgs;           //pointer to mc file footer
        // Fill the Header With The Needed Default
        ff7->file_header_vgs[0] =0x56;
        ff7->file_header_vgs[1] =0x67;
        ff7->file_header_vgs[2] =0x73;
        ff7->file_header_vgs[3] =0x4D;
        ff7->file_header_vgs[4] =0x01;
        ff7->file_header_vgs[8] =0x01;
        ff7->file_header_vgs[12] =0x01;
    }
    fix_vmc_header(ff7);
    saveFileFull(fileName);
}
void MainWindow::on_actionExport_DEX_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 Dex-Drive SaveGame"), settings->value("save_emu_path").toString(),tr("FF7 Dex SaveGame(*.gme)"));
    if(fileName.isEmpty()){return;}
    if(ff7->SG_TYPE != "DEX")
    {
        ui->combo_control->setCurrentIndex(0);

        ff7->SG_SIZE          = FF7_DEX_SAVE_GAME_SIZE;
        ff7->SG_HEADER        = FF7_DEX_SAVE_GAME_HEADER;
        ff7->SG_FOOTER        = FF7_DEX_SAVE_GAME_FOOTER;
        ff7->SG_DATA_SIZE     = FF7_DEX_SAVE_GAME_DATA_SIZE;
        ff7->SG_SLOT_HEADER   = FF7_DEX_SAVE_GAME_SLOT_HEADER;
        ff7->SG_SLOT_FOOTER   = FF7_DEX_SAVE_GAME_SLOT_FOOTER;
        ff7->SG_SLOT_SIZE     = FF7_DEX_SAVE_GAME_SLOT_SIZE;
        ff7->SG_SLOT_NUMBER   = FF7_DEX_SAVE_GAME_SLOT_NUMBER;
        ff7->SG_TYPE          = "DEX";
        ff7->file_headerp     = ff7->file_header_dex;           //pointer to mc file header
        ff7->file_footerp     = ff7->file_footer_dex;           //pointer to mc file footer
        //default header..
        ff7->file_header_dex[0]=0x31;
        ff7->file_header_dex[1]=0x32;
        ff7->file_header_dex[2]=0x33;
        ff7->file_header_dex[3]=0x2D;
        ff7->file_header_dex[4]=0x34;
        ff7->file_header_dex[5]=0x35;
        ff7->file_header_dex[6]=0x36;
        ff7->file_header_dex[7]=0x2D;
        ff7->file_header_dex[8]=0x53;
        ff7->file_header_dex[9]=0x54;
        ff7->file_header_dex[10]=0x44;
        ff7->file_header_dex[18]=0x01;
        ff7->file_header_dex[20]=0x01;
        ff7->file_header_dex[21]=0x4D;
        ff7->file_header_dex[22]=0x51;
        for(int i=0x17;i<0x25;i++){ff7->file_header_dex[i]=0xA0;}
        ff7->file_header_dex[38]=0xFF;
    }
    fix_vmc_header(ff7);
    saveFileFull(fileName);
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
void MainWindow::on_actionClear_Slot_activated(){clearslot(s);  guirefresh(0);}

void MainWindow::on_actionShow_Selection_Dialog_activated(){SlotSelect slotselect(0,ff7);slotselect.setStyleSheet(this->styleSheet());s=slotselect.exec();guirefresh(0);}
void MainWindow::on_actionPrevious_Slot_activated(){if(ff7->SG_TYPE==""){return;}else{if (s > 0) {s--; guirefresh(0);}}}
void MainWindow::on_actionNext_Slot_activated(){if(ff7->SG_TYPE==""){return;}else{if (s<14){s++; guirefresh(0);}}}
void MainWindow::on_actionAbout_activated(){about adialog;  adialog.setStyleSheet(this->styleSheet()); adialog.exec();}
void MainWindow::on_actionAbout_Qt_activated(){qApp->aboutQt();}
void MainWindow::on_actionCopy_Slot_activated(){memcpy(&bufferslot,&ff7->slot[s],0x10f4); buffer_region = ff7->SG_Region_String[s];}
void MainWindow::on_actionPaste_Slot_activated()
{
    memcpy(&ff7->slot[s],&bufferslot,0x10f4);
    ff7->SG_Region_String[s] = buffer_region;
    ff7->SG_Region_String[s].chop(2);
    switch(s)
    {
        case 0: ff7->SG_Region_String[s].append("01"); break;
        case 1: ff7->SG_Region_String[s].append("02"); break;
        case 2: ff7->SG_Region_String[s].append("03"); break;
        case 3: ff7->SG_Region_String[s].append("04"); break;
        case 4: ff7->SG_Region_String[s].append("05"); break;
        case 5: ff7->SG_Region_String[s].append("06"); break;
        case 6: ff7->SG_Region_String[s].append("07"); break;
        case 7: ff7->SG_Region_String[s].append("08"); break;
        case 8: ff7->SG_Region_String[s].append("09"); break;
        case 9: ff7->SG_Region_String[s].append("10"); break;
        case 10: ff7->SG_Region_String[s].append("11"); break;
        case 11: ff7->SG_Region_String[s].append("12"); break;
        case 12: ff7->SG_Region_String[s].append("13"); break;
        case 13: ff7->SG_Region_String[s].append("14"); break;
        case 14: ff7->SG_Region_String[s].append("15"); break;
    }
    file_changed=true;
    guirefresh(0);
}
void MainWindow::on_actionShow_Options_triggered()
{
    Options odialog(0,settings);  odialog.setStyleSheet(this->styleSheet());    odialog.exec();
    QString style="QWidget#centralWidget{background-color: qlineargradient(spread:repeat, x1:1, y1:1, x2:0, y2:0, stop:0.0625 rgba(";
    style.append(settings->value("color1_r").toString());    style.append(",");
    style.append(settings->value("color1_g").toString());    style.append(",");
    style.append(settings->value("color1_b").toString());    style.append(", 255), stop:0.215909 rgba(");
    style.append(settings->value("color2_r").toString());    style.append(",");
    style.append(settings->value("color2_g").toString());    style.append(",");
    style.append(settings->value("color2_b").toString());    style.append(", 255), stop:0.818182 rgba(");
    style.append(settings->value("color3_r").toString());    style.append(",");
    style.append(settings->value("color3_g").toString());    style.append(",");
    style.append(settings->value("color3_b").toString());    style.append(", 255));}");
    ui->centralWidget->setStyleSheet(style);
}
void MainWindow::on_action_auto_char_growth_triggered(bool checked)
{
    if(checked)
    {
        settings->setValue("autochargrowth",1);
        ui->action_auto_char_growth->setIcon(QIcon(":/icon/checkbox_checked"));
        if(!load){setchar_growth(0);}
    }
    else
    {
        settings->setValue("autochargrowth",0);
        ui->action_auto_char_growth->setIcon(QIcon(":/icon/checkbox_unchecked"));
    }
}
void MainWindow::on_action_show_debug_toggled(bool checked)
{
    if(checked)
    {
        ui->actionNew_Window->setVisible(1);
        ui->tabWidget->setTabEnabled(8,1);
        ui->lbl_0x34->setVisible(true);
        ui->lbl_0x35->setVisible(true);
        ui->lbl_0x36->setVisible(true);
        ui->lbl_0x37->setVisible(true);
        ui->lcd_0x34->setVisible(true);
        ui->lcd_0x35->setVisible(true);
        ui->lcd_0x36->setVisible(true);
        ui->lcd_0x37->setVisible(true);
        ui->cb_Region_Slot->setEnabled(true);
        ui->combo_id->setVisible(true);
        ui->lbl_id->setVisible(true);
        ui->bm_unknown->setVisible(true);
        if(ff7->SG_TYPE == "PC"){ui->group_controller_mapping->setVisible(true);}
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
        ui->lbl_0x34->setVisible(false);
        ui->lbl_0x35->setVisible(false);
        ui->lbl_0x36->setVisible(false);
        ui->lbl_0x37->setVisible(false);
        ui->lcd_0x34->setVisible(false);
        ui->lcd_0x35->setVisible(false);
        ui->lcd_0x36->setVisible(false);
        ui->lcd_0x37->setVisible(false);
        ui->cb_Region_Slot->setEnabled(false);
        ui->combo_id->setVisible(false);
        ui->lbl_id->setVisible(false);
        ui->bm_unknown->setVisible(false);
        if(ff7->SG_TYPE =="PC"){ui->group_controller_mapping->setVisible(false);}
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
{if(!load){file_changed=true;
    if(!checked)
    {
        ff7->SG_Region_String[s].clear();
        ui->lbl_sg_region->clear();
        ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
    }
    else
    {
        if((ff7->SG_Region_String[s].contains("BESCES-00869"))||(ff7->SG_Region_String[s].contains("BESCES-00867"))||(ff7->SG_Region_String[s].contains("BESCES-00900"))||(ff7->SG_Region_String[s].contains("BESCES-00868")))
            {set_ntsc_time();}//Call RegionTime Convertor
        switch(s)
        {
            case 0:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S01"; break;
            case 1:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S02"; break;
            case 2:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S03"; break;
            case 3:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S04"; break;
            case 4:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S05"; break;
            case 5:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S06"; break;
            case 6:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S07"; break;
            case 7:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S08"; break;
            case 8:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S09"; break;
            case 9:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S10"; break;
            case 10:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S11"; break;
            case 11:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S12"; break;
            case 12:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S13"; break;
            case 13:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S14"; break;
            case 14:ff7->SG_Region_String[s] = "BASCUS-94163FF7-S15"; break;
        }
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
        ui->lbl_sg_region->setText(ff7->SG_Region_String[s].mid(0,ff7->SG_Region_String[s].lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->SG_Region_String[s].mid(ff7->SG_Region_String[s].lastIndexOf("S")+1,2).toInt()-1);
        Text.init(0);
    }
}}
/*~~~~~~~~~~~~~SET PAL MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_Generic_triggered(bool checked)
{if(!load){file_changed=true;
    if(!checked)
    {
        ff7->SG_Region_String[s].clear();
        ui->lbl_sg_region->clear();
        ui->action_Region_USA->setIcon(QIcon(":/icon/eu_unsel"));
    }
    else
    {
        if((ff7->SG_Region_String[s].contains("BASCUS-94163"))||(ff7->SG_Region_String[s].contains("BISLPS-00700"))||(ff7->SG_Region_String[s].contains("BISLPS-01057")))
            {set_pal_time();}//Call RegionTime Convertor
        switch(s)
        {
            case 0:ff7->SG_Region_String[s] = "BESCES-00867FF7-S01"; break;
            case 1:ff7->SG_Region_String[s] = "BESCES-00867FF7-S02"; break;
            case 2:ff7->SG_Region_String[s] = "BESCES-00867FF7-S03"; break;
            case 3:ff7->SG_Region_String[s] = "BESCES-00867FF7-S04"; break;
            case 4:ff7->SG_Region_String[s] = "BESCES-00867FF7-S05"; break;
            case 5:ff7->SG_Region_String[s] = "BESCES-00867FF7-S06"; break;
            case 6:ff7->SG_Region_String[s] = "BESCES-00867FF7-S07"; break;
            case 7:ff7->SG_Region_String[s] = "BESCES-00867FF7-S08"; break;
            case 8:ff7->SG_Region_String[s] = "BESCES-00867FF7-S09"; break;
            case 9:ff7->SG_Region_String[s] = "BESCES-00867FF7-S10"; break;
            case 10:ff7->SG_Region_String[s] = "BESCES-00867FF7-S11"; break;
            case 11:ff7->SG_Region_String[s] = "BESCES-00867FF7-S12"; break;
            case 12:ff7->SG_Region_String[s] = "BESCES-00867FF7-S13"; break;
            case 13:ff7->SG_Region_String[s] = "BESCES-00867FF7-S14"; break;
            case 14:ff7->SG_Region_String[s] = "BESCES-00867FF7-S15"; break;
        }
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
        ui->lbl_sg_region->setText(ff7->SG_Region_String[s].mid(0,ff7->SG_Region_String[s].lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->SG_Region_String[s].mid(ff7->SG_Region_String[s].lastIndexOf("S")+1,2).toInt()-1);
        Text.init(0);
    }
}}
/*~~~~~~~~~~~~~SET PAL_German MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_German_triggered(bool checked)
{if(!load){file_changed=true;
    if(!checked)
    {
        ff7->SG_Region_String[s].clear();
        ui->lbl_sg_region->clear();
        ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
    }
    else
    {
        if((ff7->SG_Region_String[s].contains("BASCUS-94163"))||(ff7->SG_Region_String[s].contains("BISLPS-00700"))||(ff7->SG_Region_String[s].contains("BISLPS-01057")))
            {set_pal_time();}//Call RegionTime Convertor
        switch(s)
        {
            case 0:ff7->SG_Region_String[s] = "BESCES-00869FF7-S01"; break;
            case 1:ff7->SG_Region_String[s] = "BESCES-00869FF7-S02"; break;
            case 2:ff7->SG_Region_String[s] = "BESCES-00869FF7-S03"; break;
            case 3:ff7->SG_Region_String[s] = "BESCES-00869FF7-S04"; break;
            case 4:ff7->SG_Region_String[s] = "BESCES-00869FF7-S05"; break;
            case 5:ff7->SG_Region_String[s] = "BESCES-00869FF7-S06"; break;
            case 6:ff7->SG_Region_String[s] = "BESCES-00869FF7-S07"; break;
            case 7:ff7->SG_Region_String[s] = "BESCES-00869FF7-S08"; break;
            case 8:ff7->SG_Region_String[s] = "BESCES-00869FF7-S09"; break;
            case 9:ff7->SG_Region_String[s] = "BESCES-00869FF7-S10"; break;
            case 10:ff7->SG_Region_String[s] = "BESCES-00869FF7-S11"; break;
            case 11:ff7->SG_Region_String[s] = "BESCES-00869FF7-S12"; break;
            case 12:ff7->SG_Region_String[s] = "BESCES-00869FF7-S13"; break;
            case 13:ff7->SG_Region_String[s] = "BESCES-00869FF7-S14"; break;
            case 14:ff7->SG_Region_String[s] = "BESCES-00869FF7-S15"; break;
        }
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
        ui->lbl_sg_region->setText(ff7->SG_Region_String[s].mid(0,ff7->SG_Region_String[s].lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->SG_Region_String[s].mid(ff7->SG_Region_String[s].lastIndexOf("S")+1,2).toInt()-1);
        Text.init(0);
    }
}}
/*~~~~~~~~~~~~~SET PAL_Spanish MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_Spanish_triggered(bool checked)
{if(!load){file_changed=true;
    if(!checked)
    {
        ff7->SG_Region_String[s].clear();
        ui->lbl_sg_region->clear();
        ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
    }
    else
    {
        if((ff7->SG_Region_String[s].contains("BASCUS-94163"))||(ff7->SG_Region_String[s].contains("BISLPS-00700"))||(ff7->SG_Region_String[s].contains("BISLPS-01057")))
            {set_pal_time();}//Call RegionTime Convertor
        switch(s)
        {
            case 0:ff7->SG_Region_String[s] = "BESCES-00900FF7-S01"; break;
            case 1:ff7->SG_Region_String[s] = "BESCES-00900FF7-S02"; break;
            case 2:ff7->SG_Region_String[s] = "BESCES-00900FF7-S03"; break;
            case 3:ff7->SG_Region_String[s] = "BESCES-00900FF7-S04"; break;
            case 4:ff7->SG_Region_String[s] = "BESCES-00900FF7-S05"; break;
            case 5:ff7->SG_Region_String[s] = "BESCES-00900FF7-S06"; break;
            case 6:ff7->SG_Region_String[s] = "BESCES-00900FF7-S07"; break;
            case 7:ff7->SG_Region_String[s] = "BESCES-00900FF7-S08"; break;
            case 8:ff7->SG_Region_String[s] = "BESCES-00900FF7-S09"; break;
            case 9:ff7->SG_Region_String[s] = "BESCES-00900FF7-S10"; break;
            case 10:ff7->SG_Region_String[s] = "BESCES-00900FF7-S11"; break;
            case 11:ff7->SG_Region_String[s] = "BESCES-00900FF7-S12"; break;
            case 12:ff7->SG_Region_String[s] = "BESCES-00900FF7-S13"; break;
            case 13:ff7->SG_Region_String[s] = "BESCES-00900FF7-S14"; break;
            case 14:ff7->SG_Region_String[s] = "BESCES-00900FF7-S15"; break;
        }
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
        ui->lbl_sg_region->setText(ff7->SG_Region_String[s].mid(0,ff7->SG_Region_String[s].lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->SG_Region_String[s].mid(ff7->SG_Region_String[s].lastIndexOf("S")+1,2).toInt()-1);
        Text.init(0);
    }
}}
/*~~~~~~~~~~~~~SET PAL_French MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_French_triggered(bool checked)
{if(!load){file_changed=true;
    if(!checked)
    {
        ff7->SG_Region_String[s].clear();
        ui->lbl_sg_region->clear();
        ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_unsel"));
    }
    else
    {
        if((ff7->SG_Region_String[s].contains("BASCUS-94163"))||(ff7->SG_Region_String[s].contains("BISLPS-00700"))||(ff7->SG_Region_String[s].contains("BISLPS-01057")))
            {set_pal_time();}//Call RegionTime Convertor
        switch(s)
        {
            case 0:ff7->SG_Region_String[s] = "BESCES-00868FF7-S01"; break;
            case 1:ff7->SG_Region_String[s] = "BESCES-00868FF7-S02"; break;
            case 2:ff7->SG_Region_String[s] = "BESCES-00868FF7-S03"; break;
            case 3:ff7->SG_Region_String[s] = "BESCES-00868FF7-S04"; break;
            case 4:ff7->SG_Region_String[s] = "BESCES-00868FF7-S05"; break;
            case 5:ff7->SG_Region_String[s] = "BESCES-00868FF7-S06"; break;
            case 6:ff7->SG_Region_String[s] = "BESCES-00868FF7-S07"; break;
            case 7:ff7->SG_Region_String[s] = "BESCES-00868FF7-S08"; break;
            case 8:ff7->SG_Region_String[s] = "BESCES-00868FF7-S09"; break;
            case 9:ff7->SG_Region_String[s] = "BESCES-00868FF7-S10"; break;
            case 10:ff7->SG_Region_String[s] = "BESCES-00868FF7-S11"; break;
            case 11:ff7->SG_Region_String[s] = "BESCES-00868FF7-S12"; break;
            case 12:ff7->SG_Region_String[s] = "BESCES-00868FF7-S13"; break;
            case 13:ff7->SG_Region_String[s] = "BESCES-00868FF7-S14"; break;
            case 14:ff7->SG_Region_String[s] = "BESCES-00868FF7-S15"; break;
        }
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
        ui->lbl_sg_region->setText(ff7->SG_Region_String[s].mid(0,ff7->SG_Region_String[s].lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->SG_Region_String[s].mid(ff7->SG_Region_String[s].lastIndexOf("S")+1,2).toInt()-1);
        Text.init(0);
    }
}}
/*~~~~~~~~~~~~~SET JPN MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_JPN_triggered(bool checked)
{if(!load){file_changed=true;
    if(!checked)
    {        
        ff7->SG_Region_String[s].clear();
        ui->lbl_sg_region->clear();
        ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
    }
    else
    {//First Check If Coming From PAL
        if((ff7->SG_Region_String[s].contains("BESCES-00869"))||(ff7->SG_Region_String[s].contains("BESCES-00867"))||(ff7->SG_Region_String[s].contains("BESCES-00900"))||(ff7->SG_Region_String[s].contains("BESCES-00868")))
            {set_ntsc_time();}//Call RegionTime Convertor
        switch(s)
        {
            case 0:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S01"; break;
            case 1:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S02"; break;
            case 2:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S03"; break;
            case 3:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S04"; break;
            case 4:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S05"; break;
            case 5:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S06"; break;
            case 6:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S07"; break;
            case 7:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S08"; break;
            case 8:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S09"; break;
            case 9:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S10"; break;
            case 10:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S11"; break;
            case 11:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S12"; break;
            case 12:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S13"; break;
            case 13:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S14"; break;
            case 14:ff7->SG_Region_String[s] = "BISLPS-00700FF7-S15"; break;
        }
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
        ui->lbl_sg_region->setText(ff7->SG_Region_String[s].mid(0,ff7->SG_Region_String[s].lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->SG_Region_String[s].mid(ff7->SG_Region_String[s].lastIndexOf("S")+1,2).toInt()-1);
        Text.init(1);
    }
}}
/*~~~~~~~~~~~~~SET JPN_International MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_JPN_International_triggered(bool checked)
{if(!load){file_changed=true;
    if(!checked)
    {
        ff7->SG_Region_String[s].clear();
        ui->lbl_sg_region->clear();
        ui->action_Region_JPN_International->setIcon(QIcon(":icon/jp_unsel"));
    }
    else
    {
        if((ff7->SG_Region_String[s].contains("BESCES-00869"))||(ff7->SG_Region_String[s].contains("BESCES-00867"))||(ff7->SG_Region_String[s].contains("BESCES-00900"))||(ff7->SG_Region_String[s].contains("BESCES-00868")))
            {set_ntsc_time();}//Call RegionTime Convertor
        switch(s)
        {
            case 0:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S01"; break;
            case 1:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S02"; break;
            case 2:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S03"; break;
            case 3:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S04"; break;
            case 4:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S05"; break;
            case 5:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S06"; break;
            case 6:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S07"; break;
            case 7:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S08"; break;
            case 8:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S09"; break;
            case 9:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S10"; break;
            case 10:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S11"; break;
            case 11:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S12"; break;
            case 12:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S13"; break;
            case 13:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S14"; break;
            case 14:ff7->SG_Region_String[s] = "BISLPS-01057FF7-S15"; break;
        }
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
        ui->lbl_sg_region->setText(ff7->SG_Region_String[s].mid(0,ff7->SG_Region_String[s].lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->SG_Region_String[s].mid(ff7->SG_Region_String[s].lastIndexOf("S")+1,2).toInt()-1);
        Text.init(1);
    }
}}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END MENU ACTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~GUI FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~Char Update~~~~~~~~~~*/
void MainWindow::charupdate(void)
{
    load=true;
    QByteArray text;
    quint8 char_weapon_offset=0;
    //clear everthing.
    ui->cb_id->setText("");
    ui->cb_id->setChecked(false);
    ui->cb_id->setVisible(false);
    ui->line_name->clear();
    ui->cb_sadness->setChecked(0);
    ui->cb_fury->setChecked(0);
    ui->cb_front->setChecked(0);
    ui->combo_weapon->clear();

    if(curchar== 6)
    {
        ui->cb_id->setText(tr("Young Cloud"));
        ui->cb_id->setVisible(true);
        if(ff7->slot[s].chars[6].id == 9){ui->cb_id->setChecked(1);}
        else{ui->cb_id->setChecked(0);}
    }

    if(curchar==7)
    {
        ui->cb_id->setText(tr("Sephiroth"));
        ui->cb_id->setVisible(true);
        if(ff7->slot[s].chars[7].id == 10){ui->cb_id->setChecked(1);}
        else{ui->cb_id->setChecked(0);}
    }

    ui->combo_id->setCurrentIndex(ff7->slot[s].chars[curchar].id);

    for (int n=0;n<12;n++){text.append(ff7->slot[s].chars[curchar].name[n]);}
    ui->line_name->setText(Text.toPC(text));

    ui->sb_exp->setValue(ff7->slot[s].chars[curchar].exp);
    ui->pbar_level->setValue(ff7->slot[s].chars[curchar].flags[2]);
    ui->lcd_next->display(double(ff7->slot[s].chars[curchar].expNext));
    ui->sb_lvl->setValue(ff7->slot[s].chars[curchar].level);
    ui->sb_curhp->setValue(ff7->slot[s].chars[curchar].curHP);
    ui->sb_curmp->setValue(ff7->slot[s].chars[curchar].curMP);
    ui->sb_maxhp->setValue(ff7->slot[s].chars[curchar].maxHP);
    ui->sb_maxmp->setValue(ff7->slot[s].chars[curchar].maxMP);
    ui->sb_str->setValue(ff7->slot[s].chars[curchar].strength);
    ui->sb_mag->setValue(ff7->slot[s].chars[curchar].magic);
    ui->sb_lck->setValue(ff7->slot[s].chars[curchar].luck);
    ui->sb_spi->setValue(ff7->slot[s].chars[curchar].spirit);
    ui->sb_dex->setValue(ff7->slot[s].chars[curchar].dexterity);
    ui->sb_vit->setValue(ff7->slot[s].chars[curchar].vitality);
    ui->sb_hp->setValue(ff7->slot[s].chars[curchar].baseHP);
    ui->sb_mp->setValue(ff7->slot[s].chars[curchar].baseMP);
    ui->sb_kills->setValue(ff7->slot[s].chars[curchar].kills);
    ui->sb_used1->setValue(ff7->slot[s].chars[curchar].timesused1);
    ui->sb_used2->setValue(ff7->slot[s].chars[curchar].timesused2);
    ui->sb_used3->setValue(ff7->slot[s].chars[curchar].timesused3);
    ui->sb_limitlvl->setValue(ff7->slot[s].chars[curchar].limitlevel);
    ui->slide_limit->setValue(ff7->slot[s].chars[curchar].limitbar);
    if(ff7->slot[s].chars[curchar].flags[0] == 16){ui->cb_sadness->setChecked(1);}
    if(ff7->slot[s].chars[curchar].flags[0] == 32){ui->cb_fury->setChecked(1);}
    if(ff7->slot[s].chars[curchar].flags[1] == 255){ui->cb_front->setChecked(1);}
    ui->sb_strbonus->setValue(ff7->slot[s].chars[curchar].strength_bonus);
    ui->sb_vitbonus->setValue(ff7->slot[s].chars[curchar].vitality_bonus);
    ui->sb_magbonus->setValue(ff7->slot[s].chars[curchar].magic_bonus);
    ui->sb_spibonus->setValue(ff7->slot[s].chars[curchar].spirit_bonus);
    ui->sb_dexbonus->setValue(ff7->slot[s].chars[curchar].dexterity_bonus);
    ui->sb_lckbonus->setValue(ff7->slot[s].chars[curchar].luck_bonus);
    ui->lcd_0x34->display(ff7->slot[s].chars[curchar].z_4[0]);
    ui->lcd_0x35->display(ff7->slot[s].chars[curchar].z_4[1]);
    ui->lcd_0x36->display(ff7->slot[s].chars[curchar].z_4[2]);
    ui->lcd_0x37->display(ff7->slot[s].chars[curchar].z_4[3]);

    //Set up Limit Boxes Clear and hide all
    ui->limit_1a->setChecked(0);    ui->limit_1a->setVisible(0);
    ui->limit_1b->setChecked(0);    ui->limit_1b->setVisible(0);
    ui->limit_2a->setChecked(0);    ui->limit_2a->setVisible(0);
    ui->limit_2b->setChecked(0);    ui->limit_2b->setVisible(0);
    ui->limit_3a->setChecked(0);    ui->limit_3a->setVisible(0);
    ui->limit_3b->setChecked(0);    ui->limit_3b->setVisible(0);
    ui->limit_4->setChecked(0);     ui->limit_4->setVisible(0);
    //set Visible based on char's limits and check the boxes
    switch(ff7->slot[s].chars[curchar].id)
    {
    case 6://Cait Sith Has 2 Limits
        ui->limit_1a->setVisible(1);
        ui->limit_2a->setVisible(1);
        //set learned limits
        if (ff7->slot[s].chars[curchar].limits & (1<<0)) ui->limit_1a->setChecked(1);
        if (ff7->slot[s].chars[curchar].limits & (1<<3)) ui->limit_2a->setChecked(1);
        break;
    case 7://Vincent Has 4 Limits
        ui->limit_1a->setVisible(1);
        ui->limit_2a->setVisible(1);
        ui->limit_3a->setVisible(1);
        ui->limit_4->setVisible(1);
        //check learned limits
        if (ff7->slot[s].chars[curchar].limits & (1<<0)) ui->limit_1a->setChecked(1);
        if (ff7->slot[s].chars[curchar].limits & (1<<3)) ui->limit_2a->setChecked(1);
        if (ff7->slot[s].chars[curchar].limits & (1<<6)) ui->limit_3a->setChecked(1);
        if (ff7->slot[s].chars[curchar].limits & (1<<9)) ui->limit_4->setChecked(1);
        break;

    case 10:break;//Sephiroth Has no limits

    default://Normal Chars Have 7 limits
        ui->limit_1a->setVisible(1);
        ui->limit_1b->setVisible(1);
        ui->limit_2a->setVisible(1);
        ui->limit_2b->setVisible(1);
        ui->limit_3a->setVisible(1);
        ui->limit_3b->setVisible(1);
        ui->limit_4->setVisible(1);
        //check off learned limits
        if (ff7->slot[s].chars[curchar].limits & (1<<0)) ui->limit_1a->setChecked(1);
        if (ff7->slot[s].chars[curchar].limits & (1<<1)) ui->limit_1b->setChecked(1);
        if (ff7->slot[s].chars[curchar].limits & (1<<3)) ui->limit_2a->setChecked(1);
        if (ff7->slot[s].chars[curchar].limits & (1<<4)) ui->limit_2b->setChecked(1);
        if (ff7->slot[s].chars[curchar].limits & (1<<6)) ui->limit_3a->setChecked(1);
        if (ff7->slot[s].chars[curchar].limits & (1<<7)) ui->limit_3b->setChecked(1);
        if (ff7->slot[s].chars[curchar].limits & (1<<9)) ui->limit_4->setChecked(1);
        break;
    }
    //Now Set Char Specific Things
    switch (ff7->slot[s].chars[curchar].id)
    {
        case 0:char_weapon_offset=0;    break;
        case 1:char_weapon_offset=32;   break;
        case 2:char_weapon_offset=16;   break;
        case 3:char_weapon_offset=62;   break;
        case 4:char_weapon_offset=48;   break;
        case 5:char_weapon_offset=87;   break;
        case 6:char_weapon_offset=101;  break;
        case 7:char_weapon_offset=114;  break;
        case 8:char_weapon_offset=73;   break;
        case 9:char_weapon_offset=0;    break;
        case 10:char_weapon_offset=0;   break;
    }
    switch(ff7->slot[s].chars[curchar].id)
    {
    case 0: case 9://cloud
        ui->limit_1a->setText(tr("Braver"));
        ui->limit_1b->setText(tr("Cross-Slash"));
        ui->limit_2a->setText(tr("Blade Beam"));
        ui->limit_2b->setText(tr("Climhazzard"));
        ui->limit_3a->setText(tr("Meteorain"));
        ui->limit_3b->setText(tr("Finishing Touch"));
        ui->limit_4->setText(tr("Omnislash"));
        for(int i=128;i<144;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
        break;
    case 1://barret
        ui->limit_1a->setText(tr("Big Shot"));
        ui->limit_1b->setText(tr("Mindblow"));
        ui->limit_2a->setText(tr("Grenade Bomb"));
        ui->limit_2b->setText(tr("Hammerblow"));
        ui->limit_3a->setText(tr("Satellite Beam"));
        ui->limit_3b->setText(tr("Angermax"));
        ui->limit_4->setText(tr("Catastrophe"));
        for(int i=160;i<176;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
        break;
    case 2://tifa
        ui->limit_1a->setText(tr("Beat Rush"));
        ui->limit_1b->setText(tr("Somersault"));
        ui->limit_2a->setText(tr("Waterkick"));
        ui->limit_2b->setText(tr("Meteodrive"));
        ui->limit_3a->setText(tr("Dolphin Blow"));
        ui->limit_3b->setText(tr("Meteor Strike"));
        ui->limit_4->setText(tr("Final Heaven"));
        for(int i=144;i<160;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
        break;
    case 3://aerith
        ui->limit_1a->setText(tr("Healing Wind"));
        ui->limit_1b->setText(tr("Seal Evil"));
        ui->limit_2a->setText(tr("Breath of the Earth"));
        ui->limit_2b->setText(tr("Fury Brand"));
        ui->limit_3a->setText(tr("Planet Protector"));
        ui->limit_3b->setText(tr("Pulse of Life"));
        ui->limit_4->setText(tr("Great Gospel"));
        for(int i=190;i<201;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
        break;
    case 4://red
        ui->limit_1a->setText(tr("Sled Fang"));
        ui->limit_1b->setText(tr("Lunatic High"));
        ui->limit_2a->setText(tr("Blood Fang"));
        ui->limit_2b->setText(tr("Stardust Ray"));
        ui->limit_3a->setText(tr("Howling Moon"));
        ui->limit_3b->setText(tr("Earth Rave"));
        ui->limit_4->setText(tr("Cosmo Memory"));
        for(int i=176;i<190;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
        break;
    case 5://yuffie
        ui->limit_1a->setText(tr("Greased Lightning"));
        ui->limit_1b->setText(tr("Clear Tranquil"));
        ui->limit_2a->setText(tr("Landscaper"));
        ui->limit_2b->setText(tr("Bloodfest"));
        ui->limit_3a->setText(tr("Gauntlet"));
        ui->limit_3b->setText(tr("Doom of the Living"));
        ui->limit_4->setText(tr("All Creation"));
        for(int i=215;i<229;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
        break;
    case 6://cait
        ui->limit_1a->setText(tr("Dice"));
        ui->limit_2a->setText(tr("Slots"));
        for(int i=229;i<242;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
        break;
    case 7://vincent
        ui->limit_1a->setText(tr("Galian Beast"));
        ui->limit_2a->setText(tr("Death Gigas"));
        ui->limit_3a->setText(tr("Hellmasker"));
        ui->limit_4->setText(tr("Chaos"));
        for(int i=242;i<255;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
        break;
    case 8://cid
        ui->limit_1a->setText(tr("Boost Jump"));
        ui->limit_1b->setText(tr("Dynamite"));
        ui->limit_2a->setText(tr("Hyper Jump"));
        ui->limit_2b->setText(tr("Dragon"));
        ui->limit_3a->setText(tr("Dragon Dive"));
        ui->limit_3b->setText(tr("Big Brawl"));
        ui->limit_4->setText(tr("Highwind"));
        for(int i=201;i<215;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),FF7Strings.ItemNames(i));}
        break;
    case 10://sephiroth
        ui->combo_weapon->addItem(QIcon(Items[255].image),FF7Strings.ItemNames(255));
        ui->combo_weapon->setCurrentIndex(0); //only set seppie's weapon cause he has only one.
        break;
    }

    //Equipment Tab Stuff.
    if(ff7->slot[s].chars[curchar].id !=10){ui->combo_weapon->setCurrentIndex((ff7->slot[s].chars[curchar].weapon)-char_weapon_offset);}//if not seppie set the weapon

    ui->combo_armor->setCurrentIndex(ff7->slot[s].chars[curchar].armor);

    ui->combo_acc->setCurrentIndex(ff7->slot[s].chars[curchar].accessory);

    //Set up char buttons and avatar icon.
    ui->lbl_avatar->setStyleSheet(avatar_style(ff7->slot[s].chars[curchar].id));
    ui->btn_cloud->setStyleSheet(avatar_style(ff7->slot[s].chars[0].id));
    ui->btn_barret->setStyleSheet(avatar_style(ff7->slot[s].chars[1].id));
    ui->btn_tifa->setStyleSheet(avatar_style(ff7->slot[s].chars[2].id));
    ui->btn_aeris->setStyleSheet(avatar_style(ff7->slot[s].chars[3].id));
    ui->btn_red->setStyleSheet(avatar_style(ff7->slot[s].chars[4].id));
    ui->btn_yuffie->setStyleSheet(avatar_style(ff7->slot[s].chars[5].id));
    ui->btn_cait->setStyleSheet(avatar_style(ff7->slot[s].chars[6].id));
    ui->btn_vincent->setStyleSheet(avatar_style(ff7->slot[s].chars[7].id));
    ui->btn_cid->setStyleSheet(avatar_style(ff7->slot[s].chars[8].id));
    load=false;
    setweaponslots();
    setarmorslots();
    materiaupdate_slot();
    update_stat_totals();
    weapon_stat();
    if(ui->action_auto_char_growth->isChecked()){setchar_growth(0);}
}
void MainWindow::weapon_stat(void)
{
    if(ui->combo_weapon->currentText()==FF7Strings.ItemNames(140)){ui->lbl_weapon_bonus->setText(tr("spi +13"));}//apocalpse}
    else if(ui->combo_weapon->currentText()==FF7Strings.ItemNames(142)){ui->lbl_weapon_bonus->setText(tr("spi +35"));}//ragnarok
    else if(ui->combo_weapon->currentText()==FF7Strings.ItemNames(143)){ui->lbl_weapon_bonus->setText(tr("spi +24"));}//Ultimate Weapon
    else if(ui->combo_weapon->currentText()==FF7Strings.ItemNames(187)){ui->lbl_weapon_bonus->setText(tr("vit +35 spi +18"));}//behemoth horn
    else if(ui->combo_weapon->currentText()==FF7Strings.ItemNames(190)){ui->lbl_weapon_bonus->setText(tr("vit +1 spi +4"));}//Guard Stick
    else if(ui->combo_weapon->currentText()==FF7Strings.ItemNames(199)){ui->lbl_weapon_bonus->setText(tr("vit +20"));}//Umbrella
    else if(ui->combo_weapon->currentText()==FF7Strings.ItemNames(200)){ui->lbl_weapon_bonus->setText(tr("vit +12 spi +20"));}//Princess Guard
    else if(ui->combo_weapon->currentText()==FF7Strings.ItemNames(213)){ui->lbl_weapon_bonus->setText(tr("spi +20"));}//Spirt Lance
    else if(ui->combo_weapon->currentText()==FF7Strings.ItemNames(225)){ui->lbl_weapon_bonus->setText(tr("dex +10"));}//Magic Shuriken
    else if(ui->combo_weapon->currentText()==FF7Strings.ItemNames(240)){ui->lbl_weapon_bonus->setText(tr("vit +30"));}//Starlight M Phone
    else{ui->lbl_weapon_bonus->setText("");}

    switch(ff7->slot[s].chars[curchar].armor)
    {
        case 11:ui->lbl_armor_bonus->setText(tr("mag +5")); break;//Enincoat
        case 12:ui->lbl_armor_bonus->setText(tr("mag +20")); break;//Wizard Bracelet
        case 14:ui->lbl_armor_bonus->setText(tr("str +30")); break;//Gigas Armlet
        case 17:ui->lbl_armor_bonus->setText(tr("mag +20")); break;//Forth Braclet
        case 18:ui->lbl_armor_bonus->setText(tr("str +5")); break;//Warrior Bangle
        case 29:ui->lbl_armor_bonus->setText(tr("str +20 mag +20")); break;//Ziedrich
        case 31:ui->lbl_armor_bonus->setText(tr("dex +30 lck +20")); break;//chocobobracelet
        default:ui->lbl_armor_bonus->setText(""); break;
    }

    switch(ff7->slot[s].chars[curchar].accessory)
    {
        case 0x00: ui->lbl_acc_bonus->setText(tr("str +10"));break;//power wrist
        case 0x01: ui->lbl_acc_bonus->setText(tr("vit +10"));break;//protect ring
        case 0x02: ui->lbl_acc_bonus->setText(tr("mag +10"));break;//earing
        case 0x03: ui->lbl_acc_bonus->setText(tr("spi +10"));break;//tailsman
        case 0x04: ui->lbl_acc_bonus->setText(tr("dex +10"));break;//choco-feather
        case 0x05: ui->lbl_acc_bonus->setText(tr("lck +10%"));break;//amulet +10%
        case 0x06: ui->lbl_acc_bonus->setText(tr("str +30 vit +30"));break;// champ's belt
        case 0x08: ui->lbl_acc_bonus->setText(tr("str +50 spi +50"));break;// tough ring
        case 0x09: ui->lbl_acc_bonus->setText(tr("mag +30 spi +30"));break;// circlet
        default: ui->lbl_acc_bonus->setText("");break;
    }
}
void MainWindow::update_stat_totals(void)
{
    int strbonus=0;  int magbonus=0; int spibonus=0; int lckbonus=0; int stat_temp=0;
    int vitbonus=0;  int dexbonus=0; int hpbonus=0; int mpbonus=0;


    for(int i=0;i<16;i++)
    {//Check each materia slot and create a runing total for each stat.
        if(ff7->slot[s].chars[curchar].materias[i].id != 0xFF)
        {
            strbonus += FF7Strings.MateriaStats_Str(ff7->slot[s].chars[curchar].materias[i].id);

            vitbonus += FF7Strings.MateriaStats_Vit(ff7->slot[s].chars[curchar].materias[i].id);
            if(ff7->slot[s].chars[curchar].materias[i].id == 0x03)
            {//Catch Magic Plus
                int level=1;
                int aptemp = ff7->slot[s].chars[curchar].materias[i].ap[0] |  ff7->slot[s].chars[curchar].materias[i].ap[1] <<8 | ff7->slot[s].chars[curchar].materias[i].ap[2] <<16;
                for(int m=0; m<Materias[1].levels;m++){if(aptemp >= Materias[1].ap[m]){level++;}}
                magbonus += ff7->slot[s].chars[curchar].magic * (0.01*(level*10));
            }
            else{magbonus += FF7Strings.MateriaStats_Mag(ff7->slot[s].chars[curchar].materias[i].id);}

            spibonus += FF7Strings.MateriaStats_Spi(ff7->slot[s].chars[curchar].materias[i].id);

            if(ff7->slot[s].chars[curchar].materias[i].id == 0x02)
            {//Catch Speed Plus
                int level=1;
                int aptemp = ff7->slot[s].chars[curchar].materias[i].ap[0] |  ff7->slot[s].chars[curchar].materias[i].ap[1] <<8 | ff7->slot[s].chars[curchar].materias[i].ap[2] <<16;
                for(int m=0; m<Materias[1].levels;m++){if(aptemp >= Materias[1].ap[m]){level++;}}
                dexbonus += ff7->slot[s].chars[curchar].dexterity * (0.01*(level*10));
            }
            else{dexbonus += FF7Strings.MateriaStats_Dex(ff7->slot[s].chars[curchar].materias[i].id);}

            if(ff7->slot[s].chars[curchar].materias[i].id == 0x04)
            {//Catch Luck Plus
                int level=1;
                int aptemp = ff7->slot[s].chars[curchar].materias[i].ap[0] |  ff7->slot[s].chars[curchar].materias[i].ap[1] <<8 | ff7->slot[s].chars[curchar].materias[i].ap[2] <<16;
                for(int m=0; m<Materias[1].levels;m++){if(aptemp >= Materias[1].ap[m]){level++;}}
                lckbonus += ff7->slot[s].chars[curchar].magic * (0.01*(level*10));
            }
            else{lckbonus += FF7Strings.MateriaStats_Lck(ff7->slot[s].chars[curchar].materias[i].id);}

            if(ff7->slot[s].chars[curchar].materias[i].id == 0x01)
            {//Catch HP Plus
                int level=1;
                int aptemp = ff7->slot[s].chars[curchar].materias[i].ap[0] |  ff7->slot[s].chars[curchar].materias[i].ap[1] <<8 | ff7->slot[s].chars[curchar].materias[i].ap[2] <<16;
                for(int m=0; m<Materias[1].levels;m++){if(aptemp >= Materias[1].ap[m]){level++;}}
                hpbonus +=level*10;
            }
            else{hpbonus += FF7Strings.MateriaStats_Hp(ff7->slot[s].chars[curchar].materias[i].id);}

            if(ff7->slot[s].chars[curchar].materias[i].id ==0x00)
            {//Catch Mp Plus
                int level=1;
                int aptemp = ff7->slot[s].chars[curchar].materias[i].ap[0] |  ff7->slot[s].chars[curchar].materias[i].ap[1] <<8 | ff7->slot[s].chars[curchar].materias[i].ap[2] <<16;
                for(int m=0; m<Materias[0].levels;m++){if(aptemp >= Materias[0].ap[m]){level++;}}
                mpbonus +=level*10;
            }
            else{mpbonus +=FF7Strings.MateriaStats_Mp(ff7->slot[s].chars[curchar].materias[i].id);}
        }
    }
    //out of the loop need to check things like accessory and armor/weapon for modifiers.
    if(ff7->slot[s].chars[curchar].accessory == 0x00) {strbonus+=10;ui->lbl_acc_bonus->setText(tr("str +10"));} //power wrist
    else if(ff7->slot[s].chars[curchar].accessory == 0x01) {vitbonus+=10;ui->lbl_acc_bonus->setText(tr("vit +10"));} //protect ring
    else if(ff7->slot[s].chars[curchar].accessory == 0x02) {magbonus+=10;ui->lbl_acc_bonus->setText(tr("mag +10"));} //earing
    else if(ff7->slot[s].chars[curchar].accessory == 0x03) {spibonus+=10;ui->lbl_acc_bonus->setText(tr("spi +10"));} //tailsman
    else if(ff7->slot[s].chars[curchar].accessory == 0x04) {dexbonus+=10;ui->lbl_acc_bonus->setText(tr("dex +10"));} //choco-feather
    else if(ff7->slot[s].chars[curchar].accessory == 0x05) {lckbonus+= (ff7->slot[s].chars[curchar].luck*0.1);ui->lbl_acc_bonus->setText(tr("lck +") + QString::number(int(ff7->slot[s].chars[curchar].luck*0.1)));} //amulet +10%
    else if(ff7->slot[s].chars[curchar].accessory == 0x06) {strbonus+=30; vitbonus+=30;ui->lbl_acc_bonus->setToolTip(tr("str +30 vit +30"));} // champ's belt
    else if(ff7->slot[s].chars[curchar].accessory == 0x08) {strbonus+=50; spibonus+=50;ui->lbl_acc_bonus->setToolTip(tr("str +50 spi +50"));} // tough ring
    else if(ff7->slot[s].chars[curchar].accessory == 0x09) {magbonus+=30; spibonus+=30;ui->lbl_acc_bonus->setToolTip(tr("mag +30 spi +30"));} // circlet
    else{ui->lbl_acc_bonus->setText("");}
    //end of accessories
    if(ui->combo_weapon->currentText() == FF7Strings.ItemNames(140)){spibonus+=13;}//apocalpse}
    else if(ui->combo_weapon->currentText() == FF7Strings.ItemNames(142)){spibonus+=35;}//ragnarok
    else if(ui->combo_weapon->currentText() == FF7Strings.ItemNames(143)){spibonus+=24;}//Ultimate Weapon
    else if(ui->combo_weapon->currentText() == FF7Strings.ItemNames(187)){spibonus+=18;vitbonus+=35;}//behemoth horn
    else if(ui->combo_weapon->currentText() == FF7Strings.ItemNames(190)){vitbonus+=1; spibonus+=4;}//Guard Stick
    else if(ui->combo_weapon->currentText() == FF7Strings.ItemNames(199)){vitbonus+=20;}//Umbrella
    else if(ui->combo_weapon->currentText() == FF7Strings.ItemNames(200)){vitbonus+=12; spibonus+=20;}//Princess Guard
    else if(ui->combo_weapon->currentText() == FF7Strings.ItemNames(213)){spibonus+=20;}//Spirt Lance
    else if(ui->combo_weapon->currentText() == FF7Strings.ItemNames(225)){dexbonus+=10;}//Magic Shuriken
    else if(ui->combo_weapon->currentText() == FF7Strings.ItemNames(240)){vitbonus+=30;}//Starlight M Phone

    //end weapons
    if(ff7->slot[s].chars[curchar].armor == 31){dexbonus+=30;lckbonus+=20;} //chocobobracelet
    else if(ff7->slot[s].chars[curchar].armor == 11){magbonus+=5;}//Enincoat
    else if(ff7->slot[s].chars[curchar].armor == 12){magbonus+=20;}//Wizard Bracelet
    else if(ff7->slot[s].chars[curchar].armor == 14){strbonus+=30;}//Gigas Armlet
    else if(ff7->slot[s].chars[curchar].armor == 17){magbonus+=20;}//Forth Braclet
    else if(ff7->slot[s].chars[curchar].armor == 18){strbonus+=20;}//Warrior Bangle
    else if(ff7->slot[s].chars[curchar].armor == 29){strbonus+=20; magbonus+=20;}//Ziedrich
    //end armor

    //set the labels for the bonuses.
    ui->lbl_str_mat->setText(QString::number(strbonus));
    ui->lbl_vit_mat->setText(QString::number(vitbonus));
    ui->lbl_mag_mat->setText(QString::number(magbonus));
    ui->lbl_spi_mat->setText(QString::number(spibonus));
    ui->lbl_dex_mat->setText(QString::number(dexbonus));
    ui->lbl_lck_mat->setText(QString::number(lckbonus));
    ui->lbl_hp_mat->setText(QString::number(hpbonus)+ "%");
    ui->lbl_mp_mat->setText(QString::number(mpbonus) + "%");

    //do the math for the stat , if grater then 255 then ingore and use 255 instead.
    stat_temp=ui->sb_str->value()+ui->sb_strbonus->value()+strbonus;    if(stat_temp>256){stat_temp=255;}
    ui->lbl_str_total->setText(QString::number(stat_temp));
    stat_temp=ui->sb_vit->value()+ui->sb_vitbonus->value()+vitbonus;    if(stat_temp>256){stat_temp=255;}
    ui->lbl_vit_total->setText(QString::number(stat_temp));
    stat_temp=ui->sb_mag->value()+ui->sb_magbonus->value()+magbonus;    if(stat_temp>256){stat_temp=255;}
    ui->lbl_mag_total->setText(QString::number(stat_temp));
    stat_temp=ui->sb_spi->value()+ui->sb_spibonus->value()+spibonus;    if(stat_temp>256){stat_temp=255;}
    ui->lbl_spi_total->setText(QString::number(stat_temp));
    stat_temp=ui->sb_dex->value()+ui->sb_dexbonus->value()+dexbonus;    if(stat_temp>256){stat_temp=255;}
    ui->lbl_dex_total->setText(QString::number(stat_temp));
    stat_temp=ui->sb_lck->value()+ui->sb_lckbonus->value()+lckbonus;    if(stat_temp>256){stat_temp=255;}
    ui->lbl_lck_total->setText(QString::number(stat_temp));
    // hp/mp adjustment
    if(ui->action_auto_char_growth->isChecked())
    {
        ui->sb_maxhp->setValue(ui->sb_hp->value() + (ui->sb_hp->value()*(hpbonus*0.01)));
        ui->sb_maxmp->setValue(ui->sb_mp->value() + (ui->sb_mp->value()*(mpbonus*0.01)));
     }
}
/*~~~~~~~END Char Update~~~~~~~~*/
void MainWindow::setchar_growth(int caller)
{ /* This Function only gets called if automatic exp<->lvl is enabled.*/
  /* caller can be 0==just read, 1==exp_changed, 2==lvl_changed */
    if(caller==0 && ff7->slot[s].chars[curchar].level==0){return;}//viewing a blank slot on slotchange lets keep it that way
    load=true;

    //Update base Stats Var
    int pre_level = ff7->slot[s].chars[curchar].level;


    //if the lvl changed we need to set the exp correctly before we continue
    if(caller==2){
        //Basic lv change
        ff7->slot[s].chars[curchar].level = ui->sb_lvl->value();
        if(curchar==ff7->slot[s].party[0]){ff7->slot[s].desc.level = ui->sb_lvl->value();}
        //Exp calc
        ff7->slot[s].chars[curchar].exp = charlvls[ff7->slot[s].chars[curchar].id][ui->sb_lvl->value()-1];
        ui->sb_exp->setValue(ff7->slot[s].chars[curchar].exp);
    }
    for (int i=1;i<100;i++)
    {
        if(ff7->slot[s].chars[curchar].exp>=charlvls[ff7->slot[s].chars[curchar].id][i]){
            if(i==99){ui->sb_lvl->setValue(i);}
        }
        else{
            ui->sb_lvl->setValue(i);break;
        }
    }
    //if the exp was changed make sure the lvl is set correctly.
    if(caller==1){
        ff7->slot[s].chars[curchar].level=ui->sb_lvl->value();
        if(curchar==ff7->slot[s].party[0]){
            ff7->slot[s].desc.level = ui->sb_lvl->value();
        }
    }

    //Update base Stats Code
    int curlv = ui->sb_lvl->value();
    if(caller==1 || caller==2)
    {
        if(pre_level < curlv)
        {//level up
            for(int i=pre_level;i<curlv;i++)
            {// for stat_gain stat guide, 0=str; 1=vit;2=mag;3=spr;4=dex;5=lck;6=basehp;7basemp also use id incase of mods that could move a char.
                ui->sb_str->setValue(ui->sb_str->value() + stat_gain(ff7->slot[s].chars[curchar].id,0,ff7->slot[s].chars[curchar].strength,i+1));
                ui->sb_vit->setValue(ui->sb_vit->value() + stat_gain(ff7->slot[s].chars[curchar].id,1,ff7->slot[s].chars[curchar].vitality,i+1));
                ui->sb_mag->setValue(ui->sb_mag->value() + stat_gain(ff7->slot[s].chars[curchar].id,2,ff7->slot[s].chars[curchar].magic,i+1));
                ui->sb_spi->setValue(ui->sb_spi->value() + stat_gain(ff7->slot[s].chars[curchar].id,3,ff7->slot[s].chars[curchar].spirit,i+1));
                ui->sb_dex->setValue(ui->sb_dex->value() + stat_gain(ff7->slot[s].chars[curchar].id,4,ff7->slot[s].chars[curchar].dexterity,i+1));
                ui->sb_lck->setValue(ui->sb_lck->value() + stat_gain(ff7->slot[s].chars[curchar].id,5,ff7->slot[s].chars[curchar].luck,i+1));
                ui->sb_hp->setValue(ui->sb_hp->value() + stat_gain(ff7->slot[s].chars[curchar].id,6,ff7->slot[s].chars[curchar].baseHP,i+1));
                ui->sb_mp->setValue(ui->sb_mp->value() + stat_gain(ff7->slot[s].chars[curchar].id,7,ff7->slot[s].chars[curchar].baseMP,i+1));
            }
        }
        else if(pre_level > curlv)
        {//level down
            for(int i=pre_level;i>curlv;i--)
            {// for stat_gain stat guide, 0=str; 1=vit;2=mag;3=spr;4=dex;5=lck;6=basehp;7basemp
                ui->sb_str->setValue(ui->sb_str->value() - stat_gain(ff7->slot[s].chars[curchar].id,0,ff7->slot[s].chars[curchar].strength,i));
                ui->sb_vit->setValue(ui->sb_vit->value() - stat_gain(ff7->slot[s].chars[curchar].id,1,ff7->slot[s].chars[curchar].vitality,i));
                ui->sb_mag->setValue(ui->sb_mag->value() - stat_gain(ff7->slot[s].chars[curchar].id,2,ff7->slot[s].chars[curchar].magic,i));
                ui->sb_spi->setValue(ui->sb_spi->value() - stat_gain(ff7->slot[s].chars[curchar].id,3,ff7->slot[s].chars[curchar].spirit,i));
                ui->sb_dex->setValue(ui->sb_dex->value() - stat_gain(ff7->slot[s].chars[curchar].id,4,ff7->slot[s].chars[curchar].dexterity,i));
                ui->sb_lck->setValue(ui->sb_lck->value() - stat_gain(ff7->slot[s].chars[curchar].id,5,ff7->slot[s].chars[curchar].luck,i));
                ui->sb_hp->setValue(ui->sb_hp->value() - stat_gain(ff7->slot[s].chars[curchar].id,6,ff7->slot[s].chars[curchar].baseHP,i));
                ui->sb_mp->setValue(ui->sb_mp->value() - stat_gain(ff7->slot[s].chars[curchar].id,7,ff7->slot[s].chars[curchar].baseMP,i));
            }
        } //little broken when going down..
        update_stat_totals();
    }

    QString numvalue;
    if(ui->sb_lvl->value()!=99)
    {
       ff7->slot[s].chars[curchar].expNext= charlvls[ff7->slot[s].chars[curchar].id][ui->sb_lvl->value()]- ui->sb_exp->value();
       ff7->slot[s].chars[curchar].flags[2]=((chartnls[ff7->slot[s].chars[curchar].id][ui->sb_lvl->value()]-ff7->slot[s].chars[curchar].expNext)*62)/(chartnls[ff7->slot[s].chars[curchar].id][ui->sb_lvl->value()]);//level progress is in 62 parts.
    }

    else
    {
        ff7->slot[s].chars[curchar].expNext=0;
        ff7->slot[s].chars[curchar].flags[2]=0x3D;
    }
    ui->pbar_level->setValue(ff7->slot[s].chars[curchar].flags[2]);
    if(ui->pbar_level->value()<4){ui->pbar_level->setValue(0);}//ff7 ingores the value if its <4 (but we don't save this)
    numvalue.setNum(ff7->slot[s].chars[curchar].expNext);
    ui->lcd_next->display(numvalue);
    load=false;
}
/*~~~~~~~~~Armor/Weapon Update~~~~~~~~~~*/
void MainWindow::setarmorslots(void)
{
    ui->a_m_l1->setPixmap(QPixmap(""));
    ui->a_m_l2->setPixmap(QPixmap(""));
    ui->a_m_l3->setPixmap(QPixmap(""));
    ui->a_m_l4->setPixmap(QPixmap(""));
    ui->a_m_s1->setHidden(1);
    ui->a_m_s2->setHidden(1);
    ui->a_m_s3->setHidden(1);
    ui->a_m_s4->setHidden(1);
    ui->a_m_s5->setHidden(1);
    ui->a_m_s6->setHidden(1);
    ui->a_m_s7->setHidden(1);
    ui->a_m_s8->setHidden(1);
    switch(Items[256 +ff7->slot[s].chars[curchar].armor].mslots)
    {
    case 0:{break;}
    case 1:{ui->a_m_s1->setHidden(0);break;}
    case 2:{ui->a_m_s1->setHidden(0);ui->a_m_s2->setHidden(0);break;}
    case 3:{ui->a_m_s1->setHidden(0);ui->a_m_s2->setHidden(0);ui->a_m_s3->setHidden(0);break;}
    case 4:{ui->a_m_s1->setHidden(0);ui->a_m_s2->setHidden(0);ui->a_m_s3->setHidden(0);ui->a_m_s4->setHidden(0);break;}
    case 5:{ui->a_m_s1->setHidden(0);ui->a_m_s2->setHidden(0);ui->a_m_s3->setHidden(0);ui->a_m_s4->setHidden(0);ui->a_m_s5->setHidden(0);break;}
    case 6:{ui->a_m_s1->setHidden(0);ui->a_m_s2->setHidden(0);ui->a_m_s3->setHidden(0);ui->a_m_s4->setHidden(0);ui->a_m_s5->setHidden(0);ui->a_m_s6->setHidden(0);break;}
    case 7:{ui->a_m_s1->setHidden(0);ui->a_m_s2->setHidden(0);ui->a_m_s3->setHidden(0);ui->a_m_s4->setHidden(0);ui->a_m_s5->setHidden(0);ui->a_m_s6->setHidden(0);ui->a_m_s7->setHidden(0);break;}
    case 8:{ui->a_m_s1->setHidden(0);ui->a_m_s2->setHidden(0);ui->a_m_s3->setHidden(0);ui->a_m_s4->setHidden(0);ui->a_m_s5->setHidden(0);ui->a_m_s6->setHidden(0);ui->a_m_s7->setHidden(0);ui->a_m_s8->setHidden(0);break;}
    }
    switch(Items[256 +ff7->slot[s].chars[curchar].armor].linked)
    {
    case 0:{break;}
    case 1:{ui->a_m_l1->setPixmap(QPixmap(":/icon/mlink"));break;}
    case 2:{ui->a_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->a_m_l2->setPixmap(QPixmap(":/icon/mlink"));break;}
    case 3:{ui->a_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->a_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->a_m_l3->setPixmap(QPixmap(":/icon/mlink"));break;}
    case 4:{ui->a_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->a_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->a_m_l3->setPixmap(QPixmap(":/icon/mlink"));ui->a_m_l4->setPixmap(QPixmap(":/icon/mlink"));break;}
    }
}
void MainWindow::setweaponslots(void)
{
    ui->w_m_l1->setPixmap(QPixmap(""));
    ui->w_m_l2->setPixmap(QPixmap(""));
    ui->w_m_l3->setPixmap(QPixmap(""));
    ui->w_m_l4->setPixmap(QPixmap(""));
    ui->w_m_s1->setHidden(1);
    ui->w_m_s2->setHidden(1);
    ui->w_m_s3->setHidden(1);
    ui->w_m_s4->setHidden(1);
    ui->w_m_s5->setHidden(1);
    ui->w_m_s6->setHidden(1);
    ui->w_m_s7->setHidden(1);
    ui->w_m_s8->setHidden(1);
    switch(ff7->slot[s].chars[curchar].id)
    {
    case 0: case 9:{
        clouds_weapons:
            switch(Items[128 +ui->combo_weapon->currentIndex()].mslots)
            {
            case 0:{break;}
            case 1:{ui->w_m_s1->setHidden(0);break;}
            case 2:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);break;}
            case 3:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);break;}
            case 4:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);break;}
            case 5:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);break;}
            case 6:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);break;}
            case 7:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);break;}
            case 8:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);ui->w_m_s8->setHidden(0);break;}
            }
            switch(Items[128+ui->combo_weapon->currentIndex()].linked)
            {
            case 0:{break;}
            case 1:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 2:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 3:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 4:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l4->setPixmap(QPixmap(":/icon/mlink"));break;}
            }
            break;
        }
    case 1:{
            switch(Items[160 +ui->combo_weapon->currentIndex()].mslots)
            {
            case 0:{break;}
            case 1:{ui->w_m_s1->setHidden(0);break;}
            case 2:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);break;}
            case 3:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);break;}
            case 4:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);break;}
            case 5:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);break;}
            case 6:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);break;}
            case 7:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);break;}
            case 8:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);ui->w_m_s8->setHidden(0);break;}
            }
            switch(Items[160+ui->combo_weapon->currentIndex()].linked)
            {
            case 0:{break;}
            case 1:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 2:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 3:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 4:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l4->setPixmap(QPixmap(":/icon/mlink"));break;}
           }
            break;
        }
    case 2:{
            switch(Items[144 +ui->combo_weapon->currentIndex()].mslots)
            {
            case 0:{break;}
            case 1:{ui->w_m_s1->setHidden(0);break;}
            case 2:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);break;}
            case 3:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);break;}
            case 4:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);break;}
            case 5:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);break;}
            case 6:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);break;}
            case 7:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);break;}
            case 8:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);ui->w_m_s8->setHidden(0);break;}
            }
            switch(Items[144+ui->combo_weapon->currentIndex()].linked)
            {
            case 0:{break;}
            case 1:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 2:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 3:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 4:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l4->setPixmap(QPixmap(":/icon/mlink"));break;}
            }
            break;
        }
    case 3:{
            switch(Items[190 +ui->combo_weapon->currentIndex()].mslots)
            {
            case 0:{break;}
            case 1:{ui->w_m_s1->setHidden(0);break;}
            case 2:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);break;}
            case 3:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);break;}
            case 4:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);break;}
            case 5:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);break;}
            case 6:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);break;}
            case 7:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);break;}
            case 8:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);ui->w_m_s8->setHidden(0);break;}
            }
            switch(Items[190+ui->combo_weapon->currentIndex()].linked)
            {
            case 0:{break;}
            case 1:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 2:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 3:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 4:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l4->setPixmap(QPixmap(":/icon/mlink"));break;}
            }
            break;
        }
    case 4:{
            switch(Items[176 +ui->combo_weapon->currentIndex()].mslots)
            {
            case 0:{break;}
            case 1:{ui->w_m_s1->setHidden(0);break;}
            case 2:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);break;}
            case 3:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);break;}
            case 4:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);break;}
            case 5:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);break;}
            case 6:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);break;}
            case 7:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);break;}
            case 8:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);ui->w_m_s8->setHidden(0);break;}
            }
            switch(Items[176+ui->combo_weapon->currentIndex()].linked)
            {
            case 0:{break;}
            case 1:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 2:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 3:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 4:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l4->setPixmap(QPixmap(":/icon/mlink"));break;}
          }
            break;
       }
    case 5:{
            switch(Items[215 +ui->combo_weapon->currentIndex()].mslots)
            {
            case 0:{break;}
            case 1:{ui->w_m_s1->setHidden(0);break;}
            case 2:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);break;}
            case 3:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);break;}
            case 4:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);break;}
            case 5:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);break;}
            case 6:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);break;}
            case 7:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);break;}
            case 8:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);ui->w_m_s8->setHidden(0);break;}
            }
            switch(Items[215+ui->combo_weapon->currentIndex()].linked)
            {
            case 0:{break;}
            case 1:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 2:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 3:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 4:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l4->setPixmap(QPixmap(":/icon/mlink"));break;}
           }
            break;
        }
    case 6:{
            if(ff7->slot[s].chars[curchar].id==6)
            {
                switch(Items[229 +ui->combo_weapon->currentIndex()].mslots)
                {
                case 0:{break;}
                case 1:{ui->w_m_s1->setHidden(0);break;}
                case 2:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);break;}
                case 3:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);break;}
                case 4:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);break;}
                case 5:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);break;}
                case 6:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);break;}
                case 7:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);break;}
                case 8:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);ui->w_m_s8->setHidden(0);break;}
                }
                switch(Items[229+ui->combo_weapon->currentIndex()].linked)
                {
                case 0:{break;}
                case 1:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));break;}
                case 2:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));break;}
                case 3:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));break;}
                case 4:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l4->setPixmap(QPixmap(":/icon/mlink"));break;}
               }
            }
            else {goto clouds_weapons;}//jump to case0
            break;
        }
    case 7:{
            if(ff7->slot[s].chars[curchar].id==7)
            {
                switch(Items[242 +ui->combo_weapon->currentIndex()].mslots)
                {
                case 0:{break;}
                case 1:{ui->w_m_s1->setHidden(0);break;}
                case 2:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);break;}
                case 3:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);break;}
                case 4:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);break;}
                case 5:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);break;}
                case 6:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);break;}
                case 7:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);break;}
                case 8:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);ui->w_m_s8->setHidden(0);break;}
                }
                switch(Items[242+ui->combo_weapon->currentIndex()].linked)
                {
                case 0:{break;}
                case 1:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));break;}
                case 2:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));break;}
                case 3:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));break;}
                case 4:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l4->setPixmap(QPixmap(":/icon/mlink"));break;}
                }
            }                       
            break;
        }
    case 8:{
            switch(Items[201 +ui->combo_weapon->currentIndex()].mslots)
            {
            case 0:{break;}
            case 1:{ui->w_m_s1->setHidden(0);break;}
            case 2:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);break;}
            case 3:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);break;}
            case 4:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);break;}
            case 5:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);break;}
            case 6:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);break;}
            case 7:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);break;}
            case 8:{ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);ui->w_m_s7->setHidden(0);ui->w_m_s8->setHidden(0);break;}
            }
            switch(Items[201+ui->combo_weapon->currentIndex()].linked)
            {
            case 0:{break;}
            case 1:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 2:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 3:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));break;}
            case 4:{ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l4->setPixmap(QPixmap(":/icon/mlink"));break;}
           }
            break;
           }
    case 10:{//sephiroth has only one weapon.
            ui->w_m_s1->setHidden(0);ui->w_m_s2->setHidden(0);ui->w_m_s3->setHidden(0);ui->w_m_s4->setHidden(0);ui->w_m_s5->setHidden(0);ui->w_m_s6->setHidden(0);
            ui->w_m_l1->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l2->setPixmap(QPixmap(":/icon/mlink"));ui->w_m_l3->setPixmap(QPixmap(":/icon/mlink"));
            break;
        }
    }
}
//}
/*~~~~~End Armor/Weapon Update~~~~*/
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
    if (ff7->SG_TYPE!= "PSX" && ff7->SG_TYPE !="PSV" && (!_init)) //more then one slot
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
    if(ff7->SG_Region_String[s].contains("94163")){ui->action_Region_USA->setChecked(Qt::Checked);ui->action_Region_USA->setIcon(QIcon(":/icon/us_sel"));}
    else if(ff7->SG_Region_String[s].contains("00867")){ui->action_Region_PAL_Generic->setChecked(Qt::Checked);ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_sel"));}
    else if(ff7->SG_Region_String[s].contains("00868")){ui->action_Region_PAL_French->setChecked(Qt::Checked);ui->action_Region_PAL_French->setIcon(QIcon(":/icon/fr_sel"));}
    else if(ff7->SG_Region_String[s].contains("00869")){ui->action_Region_PAL_German->setChecked(Qt::Checked);ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_sel"));}
    else if(ff7->SG_Region_String[s].contains("00900")){ui->action_Region_PAL_Spanish->setChecked(Qt::Checked);ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_sel"));}
    else if(ff7->SG_Region_String[s].contains("00700")){ui->action_Region_JPN->setChecked(Qt::Checked);ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_sel"));}
    else if(ff7->SG_Region_String[s].contains("01057")){ui->action_Region_JPN_International->setChecked(Qt::Checked);ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_sel"));}
    else if(ff7->SG_Region_String[s].isEmpty()){/*do nothing*/}
    else{QMessageBox::information(this,tr("Region Detect Error"),tr("Region Cannot be Automatically Detected, You Must Set it Manually"));}
    /*~~End Detected Region~~*/
    load=false;
}
void MainWindow::setPreviewColors()
{//never needs load set.
    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7->slot[s].colors[0][0]),int(ff7->slot[s].colors[0][1]),int(ff7->slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7->slot[s].colors[1][0]),int(ff7->slot[s].colors[1][1]),int(ff7->slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7->slot[s].colors[2][0]),int(ff7->slot[s].colors[2][1]),int(ff7->slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7->slot[s].colors[3][0]),int(ff7->slot[s].colors[3][1]),int(ff7->slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));
}
void MainWindow::materiaupdate_slot(void)
{
load=true;
if(ff7->slot[s].chars[curchar].materias[0].id != 0xFF){ui->w_m_s1->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[0].id].image));}else{ui->w_m_s1->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[1].id != 0xFF){ui->w_m_s2->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[1].id].image));}else{ui->w_m_s2->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[2].id != 0xFF){ui->w_m_s3->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[2].id].image));}else{ui->w_m_s3->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[3].id != 0xFF){ui->w_m_s4->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[3].id].image));}else{ui->w_m_s4->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[4].id != 0xFF){ui->w_m_s5->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[4].id].image));}else{ui->w_m_s5->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[5].id != 0xFF){ui->w_m_s6->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[5].id].image));}else{ui->w_m_s6->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[6].id != 0xFF){ui->w_m_s7->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[6].id].image));}else{ui->w_m_s7->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[7].id != 0xFF){ui->w_m_s8->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[7].id].image));}else{ui->w_m_s8->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[0].id != 0xFF){ui->w_m_s1->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[0].id));}else{ui->w_m_s1->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[1].id != 0xFF){ui->w_m_s2->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[1].id));}else{ui->w_m_s2->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[2].id != 0xFF){ui->w_m_s3->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[2].id));}else{ui->w_m_s3->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[3].id != 0xFF){ui->w_m_s4->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[3].id));}else{ui->w_m_s4->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[4].id != 0xFF){ui->w_m_s5->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[4].id));}else{ui->w_m_s5->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[5].id != 0xFF){ui->w_m_s6->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[5].id));}else{ui->w_m_s6->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[6].id != 0xFF){ui->w_m_s7->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[6].id));}else{ui->w_m_s7->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[7].id != 0xFF){ui->w_m_s8->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[7].id));}else{ui->w_m_s8->setToolTip(QString(tr("Empty")));}

if(ff7->slot[s].chars[curchar].materias[8].id != 0xFF){ui->a_m_s1->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[8].id].image));}else{ui->a_m_s1->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[9].id != 0xFF){ui->a_m_s2->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[9].id].image));}else{ui->a_m_s2->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[10].id != 0xFF){ui->a_m_s3->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[10].id].image));}else{ui->a_m_s3->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[11].id != 0xFF){ui->a_m_s4->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[11].id].image));}else{ui->a_m_s4->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[12].id != 0xFF){ui->a_m_s5->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[12].id].image));}else{ui->a_m_s5->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[13].id != 0xFF){ui->a_m_s6->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[13].id].image));}else{ui->a_m_s6->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[14].id != 0xFF){ui->a_m_s7->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[14].id].image));}else{ui->a_m_s7->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[15].id != 0xFF){ui->a_m_s8->setIcon(QIcon(Materias[ff7->slot[s].chars[curchar].materias[15].id].image));}else{ui->a_m_s8->setIcon(QIcon(QString("")));}
if(ff7->slot[s].chars[curchar].materias[8].id != 0xFF){ui->a_m_s1->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[8].id));}else{ui->a_m_s1->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[9].id != 0xFF){ui->a_m_s2->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[9].id));}else{ui->a_m_s2->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[10].id != 0xFF){ui->a_m_s3->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[10].id));}else{ui->a_m_s3->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[11].id != 0xFF){ui->a_m_s4->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[11].id));}else{ui->a_m_s4->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[12].id != 0xFF){ui->a_m_s5->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[12].id));}else{ui->a_m_s5->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[13].id != 0xFF){ui->a_m_s6->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[13].id));}else{ui->a_m_s6->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[14].id != 0xFF){ui->a_m_s7->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[14].id));}else{ui->a_m_s7->setToolTip(QString(tr("Empty")));}
if(ff7->slot[s].chars[curchar].materias[15].id != 0xFF){ui->a_m_s8->setToolTip(FF7Strings.MateriaNames(ff7->slot[s].chars[curchar].materias[15].id));}else{ui->a_m_s8->setToolTip(QString(tr("Empty")));}

quint8 current_id = ff7->slot[s].chars[curchar].materias[mslotsel].id;
ui->btn_m_lvl1_slot->setVisible(0);
ui->btn_m_lvl2_slot->setVisible(0);
ui->btn_m_lvl3_slot->setVisible(0);
ui->btn_m_lvl4_slot->setVisible(0);
ui->btn_m_lvl5_slot->setVisible(0);
ui->spell_lvl1_group_slot->setVisible(0);
ui->spell_lvl2_group_slot->setVisible(0);
ui->spell_lvl3_group_slot->setVisible(0);
ui->spell_lvl4_group_slot->setVisible(0);
ui->spell_lvl5_group_slot->setVisible(0);
ui->w_m_s1_frame->setFrameStyle(0);
ui->w_m_s2_frame->setFrameStyle(0);
ui->w_m_s3_frame->setFrameStyle(0);
ui->w_m_s4_frame->setFrameStyle(0);
ui->w_m_s5_frame->setFrameStyle(0);
ui->w_m_s6_frame->setFrameStyle(0);
ui->w_m_s7_frame->setFrameStyle(0);
ui->w_m_s8_frame->setFrameStyle(0);
ui->a_m_s1_frame->setFrameStyle(0);
ui->a_m_s2_frame->setFrameStyle(0);
ui->a_m_s3_frame->setFrameStyle(0);
ui->a_m_s4_frame->setFrameStyle(0);
ui->a_m_s5_frame->setFrameStyle(0);
ui->a_m_s6_frame->setFrameStyle(0);
ui->a_m_s7_frame->setFrameStyle(0);
ui->a_m_s8_frame->setFrameStyle(0);
switch(mslotsel)
{
    case 0: ui->w_m_s1_frame->setFrameStyle(1);    break;
    case 1: ui->w_m_s2_frame->setFrameStyle(1);    break;
    case 2: ui->w_m_s3_frame->setFrameStyle(1);    break;
    case 3: ui->w_m_s4_frame->setFrameStyle(1);    break;
    case 4: ui->w_m_s5_frame->setFrameStyle(1);    break;
    case 5: ui->w_m_s6_frame->setFrameStyle(1);    break;
    case 6: ui->w_m_s7_frame->setFrameStyle(1);    break;
    case 7: ui->w_m_s8_frame->setFrameStyle(1);    break;
    case 8: ui->a_m_s1_frame->setFrameStyle(1);    break;
    case 9: ui->a_m_s2_frame->setFrameStyle(1);    break;
    case 10:ui->a_m_s3_frame->setFrameStyle(1);    break;
    case 11:ui->a_m_s4_frame->setFrameStyle(1);    break;
    case 12:ui->a_m_s5_frame->setFrameStyle(1);    break;
    case 13:ui->a_m_s6_frame->setFrameStyle(1);    break;
    case 14:ui->a_m_s7_frame->setFrameStyle(1);    break;
    case 15:ui->a_m_s8_frame->setFrameStyle(1);    break;
}

if(current_id == 0xFF) //if the slot is empty take some precautions
{
    ui->combo_add_mat_slot_2->clear();
    for(int i=0;i<0x5B;i++)
    {
        if(FF7Strings.MateriaNames(i) !=tr("DON'T USE")){ui->combo_add_mat_slot_2->addItem(QIcon(Materias[i].image),FF7Strings.MateriaNames(i));}
    }
    ui->combo_add_mat_slot->setCurrentIndex(0);
    ui->combo_mat_type_slot->setCurrentIndex(0);
    load=true;//type calls reset load
    ui->lbl_mat_stats_slot->setText(tr("Empty Slot"));
    ui->lcd_ap_master_slot->display(0);
    ui->sb_addap_slot->setValue(0);
    ui->sb_addap_slot->setMaximum(0);
    ff7->slot[s].chars[curchar].materias[mslotsel].id =0xFF;
    ff7->slot[s].chars[curchar].materias[mslotsel].ap[0]=0xFF;//Just incase so the ap is set correct
    ff7->slot[s].chars[curchar].materias[mslotsel].ap[1]=0xFF;//This will avoid the possiblity of
    ff7->slot[s].chars[curchar].materias[mslotsel].ap[2]=0xFF;//the "gravity" bug dlpb found.
}

else if(Materias[current_id].name == tr("DON'T USE")) //this is a placeholder materia.
{
    ui->lbl_mat_stats_slot->setText(FF7Strings.MateriaStats(current_id));
    ui->lcd_ap_master_slot->display(tr("NO CAP"));
    ui->sb_addap_slot->setMaximum(16777215);
    qint32 aptemp = ff7->slot[s].chars[curchar].materias[mslotsel].ap[0] |(ff7->slot[s].chars[curchar].materias[mslotsel].ap[1] << 8) | (ff7->slot[s].chars[curchar].materias[mslotsel].ap[2] << 16);
    ui->sb_addap_slot->setValue(aptemp);
    ui->combo_add_mat_slot->setCurrentIndex(current_id);
    // Set the unknown skills
    ui->spell_lvl1_group_slot->setVisible(1);
    ui->lbl_spell_lvl1_slot->setText(FF7Strings.MateriaSkills(ui->combo_add_mat_slot->currentIndex(),0));
}

else // make the materia look nice
{
    load=true;
    qint32 masterap=0;
    ui->lbl_mat_stats_slot->setText(FF7Strings.MateriaStats(current_id));// set stat string..
    qint32 aptemp = ff7->slot[s].chars[curchar].materias[mslotsel].ap[0] |(ff7->slot[s].chars[curchar].materias[mslotsel].ap[1] << 8) | (ff7->slot[s].chars[curchar].materias[mslotsel].ap[2] << 16);
    if(Materias[current_id].levels >1){masterap = (Materias[current_id].ap[Materias[current_id].levels-2]);}
    ui->lcd_ap_master_slot->display(masterap);
    // Check Materia Max AP and Set the Spin Box's Max Value.
    if(Materias[current_id].levels>1){ui->sb_addap_slot->setMaximum(masterap);}
    else{ui->sb_addap_slot->setMaximum(16777215);}
    ui->sb_addap_slot->setValue(aptemp);
    //Show levels stars
    int level=0;
    QString e_icon;
    QString f_icon;
    if(Materias[current_id].type == 0){ e_icon ="\0";   f_icon= "\0";}
    else{e_icon= Materias[current_id].image +"_empty";  f_icon= Materias[current_id].image +"_full";}
    ui->combo_mat_type_slot->setCurrentIndex(Materias[current_id].type);
    load=true;//mat_type calls reset load.
    ui->combo_add_mat_slot->setCurrentIndex(Materias[current_id].id);
    load=false;
    for(int i=0; i<Materias[current_id].levels;i++){if(aptemp >= Materias[current_id].ap[i]){level++;}}
    switch (Materias[current_id].levels)
    {
        case 0: break;
        case 1:
            ui->btn_m_lvl1_slot->setVisible(1);
            ui->btn_m_lvl1_slot->setIcon((QIcon(f_icon)));
            break;
        case 2:
            ui->btn_m_lvl1_slot->setVisible(1);
            ui->btn_m_lvl1_slot->setIcon((QIcon(f_icon)));
            ui->btn_m_lvl2_slot->setVisible(1);
            if (level >1){ui->btn_m_lvl2_slot->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl2_slot->setIcon((QIcon(e_icon)));}
            break;
        case 3:
            ui->btn_m_lvl1_slot->setVisible(1);
            ui->btn_m_lvl1_slot->setIcon((QIcon (f_icon)));
            ui->btn_m_lvl2_slot->setVisible(1);
            if (level >1){ui->btn_m_lvl2_slot->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl2_slot->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl3_slot->setVisible(1);
            if (level >2){ui->btn_m_lvl3_slot->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl3_slot->setIcon((QIcon(e_icon)));}
            break;
        case 4:
            ui->btn_m_lvl1_slot->setVisible(1);
            ui->btn_m_lvl1_slot->setIcon((QIcon(f_icon)));
            ui->btn_m_lvl2_slot->setVisible(1);
            if (level >1){ui->btn_m_lvl2_slot->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl2_slot->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl3_slot->setVisible(1);
            if (level >2){ui->btn_m_lvl3_slot->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl3_slot->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl4_slot->setVisible(1);
            if (level >3){ui->btn_m_lvl4_slot->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl4_slot->setIcon((QIcon(e_icon)));}
            break;
        case 5:
            ui->btn_m_lvl1_slot->setVisible(1);
            ui->btn_m_lvl1_slot->setIcon((QIcon(f_icon)));
            ui->btn_m_lvl2_slot->setVisible(1);
            if (level >1){ui->btn_m_lvl2_slot->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl2_slot->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl3_slot->setVisible(1);
            if (level >2){ui->btn_m_lvl3_slot->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl3_slot->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl4_slot->setVisible(1);
            if (level >3){ui->btn_m_lvl4_slot->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl4_slot->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl5_slot->setVisible(1);
            if (level >4){ui->btn_m_lvl5_slot->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl5_slot->setIcon((QIcon(e_icon)));}
            break;
    }
//fill all stars needed..
    switch(level)
    {
        case 0:
            ui->spell_lvl1_group_slot->setVisible(1);
            ui->lbl_spell_lvl1_slot->setText(FF7Strings.MateriaSkills(current_id,0));
            break;
        case 1:
            ui->spell_lvl1_group_slot->setVisible(1);
            ui->lbl_spell_lvl1_slot->setText(FF7Strings.MateriaSkills(current_id,0));
            break;
        case 2:
            ui->spell_lvl1_group_slot->setVisible(1);
            ui->spell_lvl2_group_slot->setVisible(1);
            ui->lbl_spell_lvl1_slot->setText(FF7Strings.MateriaSkills(current_id,0));
            ui->lbl_spell_lvl2_slot->setText(FF7Strings.MateriaSkills(current_id,1));
            break;
        case 3:
            ui->spell_lvl1_group_slot->setVisible(1);
            ui->spell_lvl2_group_slot->setVisible(1);
            ui->spell_lvl3_group_slot->setVisible(1);
            ui->lbl_spell_lvl1_slot->setText(FF7Strings.MateriaSkills(current_id,0));
            ui->lbl_spell_lvl2_slot->setText(FF7Strings.MateriaSkills(current_id,1));
            ui->lbl_spell_lvl3_slot->setText(FF7Strings.MateriaSkills(current_id,2));
            break;
        case 4:
            ui->spell_lvl1_group_slot->setVisible(1);
            ui->spell_lvl2_group_slot->setVisible(1);
            ui->spell_lvl3_group_slot->setVisible(1);
            ui->spell_lvl4_group_slot->setVisible(1);
            ui->lbl_spell_lvl1_slot->setText(FF7Strings.MateriaSkills(current_id,0));
            ui->lbl_spell_lvl2_slot->setText(FF7Strings.MateriaSkills(current_id,1));
            ui->lbl_spell_lvl3_slot->setText(FF7Strings.MateriaSkills(current_id,2));
            ui->lbl_spell_lvl4_slot->setText(FF7Strings.MateriaSkills(current_id,3));
            break;
        case 5:
            ui->spell_lvl1_group_slot->setVisible(1);
            ui->spell_lvl2_group_slot->setVisible(1);
            ui->spell_lvl3_group_slot->setVisible(1);
            ui->spell_lvl4_group_slot->setVisible(1);
            ui->spell_lvl5_group_slot->setVisible(1);
            ui->lbl_spell_lvl1_slot->setText(FF7Strings.MateriaSkills(current_id,0));
            ui->lbl_spell_lvl2_slot->setText(FF7Strings.MateriaSkills(current_id,1));
            ui->lbl_spell_lvl3_slot->setText(FF7Strings.MateriaSkills(current_id,2));
            ui->lbl_spell_lvl4_slot->setText(FF7Strings.MateriaSkills(current_id,3));
            ui->lbl_spell_lvl5_slot->setText(FF7Strings.MateriaSkills(current_id,4));
            break;
    }
} //end of else
load=false;
update_stat_totals();
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
            ff7->slot[s].time = (ff7->slot[s].time*1.2); ff7->slot[s].desc.time = ff7->slot[s].time;
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
            ff7->slot[s].time = (ff7->slot[s].time/1.2); ff7->slot[s].desc.time = ff7->slot[s].time;
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
        qint32 aptemp=0;
        QString ap;
        if (ff7->slot[s].materias[mat].id == 0x2C)
        {
            newItem = new QTableWidgetItem(QIcon(Materias[ff7->slot[s].materias[mat].id].image),FF7Strings.MateriaNames(ff7->slot[s].materias[mat].id),0);
            ui->tbl_materia->setItem(mat,0,newItem);
            aptemp = ff7->slot[s].materias[mat].ap[0] |(ff7->slot[s].materias[mat].ap[1] << 8) | (ff7->slot[s].materias[mat].ap[2] << 16);
            if (aptemp == 0xFFFFFF){newItem =new QTableWidgetItem(tr("Master"));ui->tbl_materia->setItem(mat,1,newItem);}
            else{newItem =new QTableWidgetItem(QString("N/A"),0);ui->tbl_materia->setItem(mat,1,newItem);}
        }
        else if (ff7->slot[s].materias[mat].id !=0xff)
        {
            newItem = new QTableWidgetItem(QIcon(Materias[ff7->slot[s].materias[mat].id].image),FF7Strings.MateriaNames(ff7->slot[s].materias[mat].id),0);
            ui->tbl_materia->setItem(mat,0,newItem);
            aptemp = ff7->slot[s].materias[mat].ap[0] |(ff7->slot[s].materias[mat].ap[1] << 8) | (ff7->slot[s].materias[mat].ap[2] << 16);
            if (aptemp == 0xFFFFFF){newItem =new QTableWidgetItem(tr("Master"));ui->tbl_materia->setItem(mat,1,newItem);}
            else{newItem =new QTableWidgetItem(ap.setNum(aptemp));ui->tbl_materia->setItem(mat,1,newItem);}
        }
        else
        {
            newItem = new QTableWidgetItem(tr("===Empty Slot==="),0);
            ff7->slot[s].materias[mat].ap[0]=0xFF;//just incase the empty slot has 0 ap
            ff7->slot[s].materias[mat].ap[1]=0xFF;//this will fix the "gravity" bug
            ff7->slot[s].materias[mat].ap[2]=0xFF;//that was reported by dlpb
            ui->tbl_materia->setItem(mat,0,newItem);
            newItem = new QTableWidgetItem("",0);
            ui->tbl_materia->setItem(mat,1,newItem);
        }
    }
    quint8 current_id= ff7->slot[s].materias[j].id;
    //before we check to see what kind of materia and lvl hide buttons and spellgroups
    ui->btn_m_lvl1->setVisible(0);
    ui->btn_m_lvl2->setVisible(0);
    ui->btn_m_lvl3->setVisible(0);
    ui->btn_m_lvl4->setVisible(0);
    ui->btn_m_lvl5->setVisible(0);
    ui->spell_lvl1_group->setVisible(0);
    ui->spell_lvl2_group->setVisible(0);
    ui->spell_lvl3_group->setVisible(0);
    ui->spell_lvl4_group->setVisible(0);
    ui->spell_lvl5_group->setVisible(0);

    if(current_id == 0xFF) //if the slot is empty take some precautions
    {

        ui->combo_add_mat->setCurrentIndex(0);
        ui->combo_mat_type->setCurrentIndex(0);
        load=true;
        ui->lbl_mat_stats->setText(tr("Empty Slot"));
        ui->lcd_ap_master->display(0);
        ui->sb_addap->setValue(0);
        ui->sb_addap->setMaximum(0);
    }

    else if(FF7Strings.MateriaNames(current_id) == tr("DON'T USE")) //this is a placeholder materia.
    {
        ui->lbl_mat_stats->setText(FF7Strings.MateriaStats(current_id));
        ui->lcd_ap_master->display(tr("NO CAP"));
        ui->sb_addap->setMaximum(16777215);
        qint32 aptemp = ff7->slot[s].materias[j].ap[0] |(ff7->slot[s].materias[j].ap[1] << 8) | (ff7->slot[s].materias[j].ap[2] << 16);
        load=true;
        ui->sb_addap->setValue(aptemp);
        // Set the unknown skills
        ui->spell_lvl1_group->setVisible(1);    ui->combo_add_mat_slot->setCurrentIndex(0);
        ui->combo_mat_type->setCurrentIndex(0);
        load=true;
        ui->lbl_spell_lvl1->setText(FF7Strings.MateriaSkills(current_id,0));
    }

    else // make the materia look nice
    {
        qint32 masterap=0;
        ui->lbl_mat_stats->setText(FF7Strings.MateriaStats(current_id));// set stat string..
        qint32 aptemp = ff7->slot[s].materias[j].ap[0] |(ff7->slot[s].materias[j].ap[1] << 8) | (ff7->slot[s].materias[j].ap[2] << 16);
        if(Materias[current_id].levels >1){masterap = (Materias[current_id].ap[Materias[current_id].levels-2]);}
        ui->lcd_ap_master->display(masterap);
        // Check Materia Max AP and Set the Spin Box's Max Value.
        if(Materias[current_id].levels>1){ui->sb_addap->setMaximum(masterap);}
        else{ui->sb_addap->setMaximum(16777215);}
        load=true;
        ui->sb_addap->setValue(aptemp);
        //Show levels stars
        int level=0;
        QString e_icon;
        QString f_icon;
        if(Materias[current_id].type == 0){ e_icon ="\0";   f_icon= "\0";}
        else{e_icon= Materias[current_id].image +"_empty";  f_icon= Materias[current_id].image +"_full";}

    for(int i=0; i<Materias[current_id].levels;i++){if(aptemp >= Materias[current_id].ap[i]){level++;}}
    switch (Materias[current_id].levels)
    {
        case 0: break;
        case 1:
            ui->btn_m_lvl1->setVisible(1);
            ui->btn_m_lvl1->setIcon((QIcon(f_icon)));
            break;
        case 2:
            ui->btn_m_lvl1->setVisible(1);
            ui->btn_m_lvl1->setIcon((QIcon(f_icon)));
            ui->btn_m_lvl2->setVisible(1);
            if (level >1){ui->btn_m_lvl2->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl2->setIcon((QIcon(e_icon)));}
            break;
        case 3:
            ui->btn_m_lvl1->setVisible(1);
            ui->btn_m_lvl1->setIcon((QIcon (f_icon)));
            ui->btn_m_lvl2->setVisible(1);
            if (level >1){ui->btn_m_lvl2->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl2->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl3->setVisible(1);
            if (level >2){ui->btn_m_lvl3->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl3->setIcon((QIcon(e_icon)));}
            break;
        case 4:
            ui->btn_m_lvl1->setVisible(1);
            ui->btn_m_lvl1->setIcon((QIcon(f_icon)));
            ui->btn_m_lvl2->setVisible(1);
            if (level >1){ui->btn_m_lvl2->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl2->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl3->setVisible(1);
            if (level >2){ui->btn_m_lvl3->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl3->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl4->setVisible(1);
            if (level >3){ui->btn_m_lvl4->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl4->setIcon((QIcon(e_icon)));}
            break;
        case 5:
            ui->btn_m_lvl1->setVisible(1);
            ui->btn_m_lvl1->setIcon((QIcon(f_icon)));
            ui->btn_m_lvl2->setVisible(1);
            if (level >1){ui->btn_m_lvl2->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl2->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl3->setVisible(1);
            if (level >2){ui->btn_m_lvl3->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl3->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl4->setVisible(1);
            if (level >3){ui->btn_m_lvl4->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl4->setIcon((QIcon(e_icon)));}
            ui->btn_m_lvl5->setVisible(1);
            if (level >4){ui->btn_m_lvl5->setIcon((QIcon(f_icon)));}
            else{ui->btn_m_lvl5->setIcon((QIcon(e_icon)));}
            break;
    }
//fill all stars needed..
    switch(level)
    {
        case 0:
            ui->spell_lvl1_group->setVisible(1);
            ui->lbl_spell_lvl1->setText(FF7Strings.MateriaSkills(current_id,0));
            break;
        case 1:
            ui->spell_lvl1_group->setVisible(1);
            ui->lbl_spell_lvl1->setText(FF7Strings.MateriaSkills(current_id,0));
            break;
        case 2:
            ui->spell_lvl1_group->setVisible(1);
            ui->spell_lvl2_group->setVisible(1);
            ui->lbl_spell_lvl1->setText(FF7Strings.MateriaSkills(current_id,0));
            ui->lbl_spell_lvl2->setText(FF7Strings.MateriaSkills(current_id,1));
            break;
        case 3:
            ui->spell_lvl1_group->setVisible(1);
            ui->spell_lvl2_group->setVisible(1);
            ui->spell_lvl3_group->setVisible(1);
            ui->lbl_spell_lvl1->setText(FF7Strings.MateriaSkills(current_id,0));
            ui->lbl_spell_lvl2->setText(FF7Strings.MateriaSkills(current_id,1));
            ui->lbl_spell_lvl3->setText(FF7Strings.MateriaSkills(current_id,2));
            break;
        case 4:
            ui->spell_lvl1_group->setVisible(1);
            ui->spell_lvl2_group->setVisible(1);
            ui->spell_lvl3_group->setVisible(1);
            ui->spell_lvl4_group->setVisible(1);
            ui->lbl_spell_lvl1->setText(FF7Strings.MateriaSkills(current_id,0));
            ui->lbl_spell_lvl2->setText(FF7Strings.MateriaSkills(current_id,1));
            ui->lbl_spell_lvl3->setText(FF7Strings.MateriaSkills(current_id,2));
            ui->lbl_spell_lvl4->setText(FF7Strings.MateriaSkills(current_id,3));
            break;
        case 5:
            ui->spell_lvl1_group->setVisible(1);
            ui->spell_lvl2_group->setVisible(1);
            ui->spell_lvl3_group->setVisible(1);
            ui->spell_lvl4_group->setVisible(1);
            ui->spell_lvl5_group->setVisible(1);
            ui->lbl_spell_lvl1->setText(FF7Strings.MateriaSkills(current_id,0));
            ui->lbl_spell_lvl2->setText(FF7Strings.MateriaSkills(current_id,1));
            ui->lbl_spell_lvl3->setText(FF7Strings.MateriaSkills(current_id,2));
            ui->lbl_spell_lvl4->setText(FF7Strings.MateriaSkills(current_id,3));
            ui->lbl_spell_lvl5->setText(FF7Strings.MateriaSkills(current_id,4));
            break;
    }
} //end of else
load=false;
ui->tbl_materia->setCurrentCell(j,1);//so that right side is set correctly.
}
void MainWindow::itemupdate()
{
    QTableWidgetItem *newItem;
    int j= ui->tbl_itm->currentRow();
    ui->tbl_itm->reset(); // just incase
    ui->tbl_itm->clearContents();
    ui->tbl_itm->setColumnWidth(0,ui->tbl_itm->width()-54);
    ui->tbl_itm->setColumnWidth(1,32);
    ui->tbl_itm->setRowCount(320);
    for (int i=0;i<320;i++) // set up items
    {
        if (ff7->slot[s].items[i].qty == 0xFF && ff7->slot[s].items[i].id == 0xFF)
        {
            newItem = new QTableWidgetItem(tr("-------EMPTY--------"),0);
            ui->tbl_itm->setItem(i,0,newItem);
            ui->tbl_itm->setRowHeight(i,22);
            newItem = new QTableWidgetItem("",0);
            ui->tbl_itm->setItem(i,1,newItem);
        }
        else
        {
            QString qty;
            if(ff7->slot[s].items[i].qty %2 ==0)
            {
                newItem = new QTableWidgetItem(QIcon(Items[ff7->slot[s].items[i].id].image),FF7Strings.ItemNames(ff7->slot[s].items[i].id),0);
                ui->tbl_itm->setItem(i,0, newItem);
                ui->tbl_itm->setRowHeight(i,22);
                newItem = new QTableWidgetItem(qty.setNum(ff7->slot[s].items[i].qty/2),0);
                ui->tbl_itm->setItem(i,1,newItem);
            }
            else
            {
                newItem = new QTableWidgetItem(QIcon(Items[256+(ff7->slot[s].items[i].id)].image),FF7Strings.ItemNames(256+(ff7->slot[s].items[i].id)),0);
                ui->tbl_itm->setItem(i,0, newItem);
                ui->tbl_itm->setRowHeight(i,22);
                newItem = new QTableWidgetItem(qty.setNum(ff7->slot[s].items[i].qty/2),0);
                ui->tbl_itm->setItem(i,1,newItem);
            }
        }
    }
    ui->tbl_itm->setCurrentCell(j,0);

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

    if((ff7->slot[s].itemsmask_1)& (1<<0)){ui->cb_itemmask1_1->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_1->setChecked(Qt::Unchecked);}

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
    load=false;
}
/*~~~~~~~~~~~~~~~~~~~~~GUIREFRESH~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::guirefresh(bool newgame)
{
    load=true;
    int reserve_start=128+(128*s);
    if (ff7->SG_TYPE =="PSP"){reserve_start+=0x80;}
    else if (ff7->SG_TYPE =="VGS"){reserve_start+=0x40;}
    else if (ff7->SG_TYPE =="DEX"){reserve_start+=0xF40;}
    else {}

    /*~~~~Check for SG type and ff7~~~~*/
    if(!ff7->SG_Region_String[s].contains("00867") && !ff7->SG_Region_String[s].contains("00869") &&
       !ff7->SG_Region_String[s].contains("00900") && !ff7->SG_Region_String[s].contains("94163") &&
       !ff7->SG_Region_String[s].contains("00700") && !ff7->SG_Region_String[s].contains("01057") &&
       !ff7->SG_Region_String[s].contains("00868") && !ff7->SG_Region_String[s].isEmpty()  )
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
    /*if empty and a Virtual memcard format and frame not empty must be link or mid link skip block!*/
    else if((!ff7->SG_Region_String[s].contains("00867") && !ff7->SG_Region_String[s].contains("00869") &&
            !ff7->SG_Region_String[s].contains("00900") && !ff7->SG_Region_String[s].contains("94163") &&
            !ff7->SG_Region_String[s].contains("00700") && !ff7->SG_Region_String[s].contains("01057") &&
            !ff7->SG_Region_String[s].contains("00868"))
         && (ff7->SG_TYPE =="MC" || ff7->SG_TYPE =="VGS" ||ff7->SG_TYPE =="DEX" ||ff7->SG_TYPE =="PSP")
         && (ff7->file_headerp[reserve_start] !=0xA0))
        {
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
        if(ff7->SG_Region_String[s].isEmpty()
           && (ff7->SG_TYPE =="MC" || ff7->SG_TYPE =="VGS" ||ff7->SG_TYPE =="DEX" ||ff7->SG_TYPE =="PSP")
           && ff7->file_headerp[reserve_start]==0xA0)
        {//if empty region string and a virtual memcard format and dir frame says empty.
            clearslot(s); //file_changed=false;//checking only
        }
        if(ff7->SG_Region_String[s].contains("00700") || ff7->SG_Region_String[s].contains("01057")){Text.init(1);}//Japanese
        else{Text.init(0);}// not japanese save.


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

        /*~~~~Set Region info and icon~~~~*/
        ui->lbl_sg_region->setText(ff7->SG_Region_String[s].mid(0,ff7->SG_Region_String[s].lastIndexOf("-")+1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->SG_Region_String[s].mid(ff7->SG_Region_String[s].lastIndexOf("S")+1,2).toInt()-1);
        if (ff7->SG_TYPE != "PC") //we Display an icon. for all formats except for pc
        {
            QByteArray data;
            for(int i=0;i<0x200;i++){data.append(ff7->hf[s].sl_header[i]);}
            SaveIcon ico(data.mid(96,160));
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
        if(ff7->SG_TYPE !="PC" || ui->action_show_debug->isChecked()){ui->group_controller_mapping->setVisible(1);}
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
        for (int loc=0; loc<32;loc++){text.append(ff7->slot[s].location[loc]);}
        ui->line_location->setText(Text.toPC(text));
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
            ui->list_flyers->setCurrentRow(i);
            if ((1 << i) & ff7->slot[s].turtleflyers){ui->list_flyers->currentItem()->setCheckState(Qt::Checked);}
            else{ui->list_flyers->currentItem()->setCheckState(Qt::Unchecked);}
            ui->list_flyers->setCurrentRow(-1);
        }

        for (int i=0;i<9;i++)//phsmask
        {
            ui->list_phs_chars->setCurrentRow(i);
            if ((1 << i) & ff7->slot[s].phsmask){ui->list_phs_chars->currentItem()->setCheckState(Qt::Unchecked);}
            else{ui->list_phs_chars->currentItem()->setCheckState(Qt::Checked);}
            ui->list_phs_chars->setCurrentRow(-1);
        }
        for (int i=0;i<9;i++)//unlocked
        {
            ui->list_chars_unlocked->setCurrentRow(i);
            if ((1 << i) & ff7->slot[s].unlockedchars){ui->list_chars_unlocked->currentItem()->setCheckState(Qt::Checked);}
            else{ui->list_chars_unlocked->currentItem()->setCheckState(Qt::Unchecked);}
            ui->list_chars_unlocked->setCurrentRow(-1);
        }
        for (int i=0;i<10;i++)//visible_menu
        {
            ui->list_menu_visible->setCurrentRow(i);
            if ((1 << i) & ff7->slot[s].menu_visible){ui->list_menu_visible->currentItem()->setCheckState(Qt::Checked);}
            else{ui->list_menu_visible->currentItem()->setCheckState(Qt::Unchecked);}
            ui->list_menu_visible->setCurrentRow(-1);
        }
        for (int i=0;i<10;i++)//menu_locked
        {
            ui->list_menu_locked->setCurrentRow(i);
            if ((1 << i) & ff7->slot[s].menu_locked){ui->list_menu_locked->currentItem()->setCheckState(Qt::Checked);}
            else{ui->list_menu_locked->currentItem()->setCheckState(Qt::Unchecked);}
            ui->list_menu_locked->setCurrentRow(-1);
        }

        ui->btn_clear_keyitems->click();
        for (int i=0;i<51;i++)// key items
        {
            if (ff7->slot[s].keyitems[i/8] & (1 << (i%8)))
            {
                ui->list_keyitems->setCurrentRow(i);
                ui->list_keyitems->currentItem()->setCheckState(Qt::Checked);
            }
        }
        ui->list_keyitems->setCurrentRow(0);//move list up totop
        ui->list_keyitems->setCurrentRow(-1);//unselect list

        /*~~~~~party combo boxes (checking for empty slots)~~~*/
        if (ff7->slot[s].party[0] >= 0x0C){ui->combo_party1->setCurrentIndex(12);}
        else{ui->combo_party1->setCurrentIndex(ff7->slot[s].party[0]);}
        if (ff7->slot[s].party[1] >= 0x0C){ui->combo_party2->setCurrentIndex(12);}
        else{ui->combo_party2->setCurrentIndex(ff7->slot[s].party[1]);}
        if (ff7->slot[s].party[2] >= 0x0C){ui->combo_party3->setCurrentIndex(12);}
        else{ui->combo_party3->setCurrentIndex(ff7->slot[s].party[2]);}

        ui->sb_gil->setValue(ff7->slot[s].gil);
        ui->sb_gp->setValue(ff7->slot[s].gp);
        ui->sb_runs->setValue(ff7->slot[s].runs);
        ui->sb_battles->setValue(ff7->slot[s].battles);
        ui->sb_steps->setValue(ff7->slot[s].steps);
        ui->sb_love_barret->setValue(ff7->slot[s].love.barret);
        ui->sb_love_tifa->setValue(ff7->slot[s].love.tifa);
        ui->sb_love_aeris->setValue(ff7->slot[s].love.aeris);
        ui->sb_love_yuffie->setValue(ff7->slot[s].love.yuffie);
        ui->sb_time_hour->setValue(ff7->slot[s].time / 3600);
        ui->sb_time_min->setValue(ff7->slot[s].time/60%60);
        ui->sb_time_sec->setValue(ff7->slot[s].time -((ui->sb_time_hour->value()*3600)+ui->sb_time_min->value()*60));
        ui->slide_ul_r->setValue(ff7->slot[s].colors[0][0]);
        ui->slide_ul_g->setValue(ff7->slot[s].colors[0][1]);
        ui->slide_ul_b->setValue(ff7->slot[s].colors[0][2]);
        ui->slide_ur_r->setValue(ff7->slot[s].colors[1][0]);
        ui->slide_ur_g->setValue(ff7->slot[s].colors[1][1]);
        ui->slide_ur_b->setValue(ff7->slot[s].colors[1][2]);
        ui->slide_ll_r->setValue(ff7->slot[s].colors[2][0]);
        ui->slide_ll_g->setValue(ff7->slot[s].colors[2][1]);
        ui->slide_ll_b->setValue(ff7->slot[s].colors[2][2]);
        ui->slide_lr_r->setValue(ff7->slot[s].colors[3][0]);
        ui->slide_lr_g->setValue(ff7->slot[s].colors[3][1]);
        ui->slide_lr_b->setValue(ff7->slot[s].colors[3][2]);

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
                int aptemp;
                QString ap;
                if (ff7->slot[s].stolen[mat].id !=0xff)
                {
                    newItem = new QTableWidgetItem(QIcon(Materias[ff7->slot[s].stolen[mat].id].image),FF7Strings.MateriaNames(ff7->slot[s].stolen[mat].id),0);
                    ui->tbl_materia_2->setItem(mat,0,newItem);
                    aptemp = ff7->slot[s].stolen[mat].ap[0] |(ff7->slot[s].stolen[mat].ap[1] << 8) | (ff7->slot[s].stolen[mat].ap[2] << 16);
                    if (aptemp == 0xFFFFFF){newItem =new QTableWidgetItem(tr("Master"));ui->tbl_materia_2->setItem(mat,1,newItem);}
                    else{newItem =new QTableWidgetItem(ap.setNum(aptemp));ui->tbl_materia_2->setItem(mat,1,newItem);}
                }
                else
                {
                    newItem = new QTableWidgetItem(tr("===Empty Slot==="),0);
                    ui->tbl_materia_2->setItem(mat,0,newItem);
                }
            }
        load=false;
        // all functions should set load on their own.
        /*~~~~~Call External Functions~~~~~~~*/
        setmenu(newgame);
        itemupdate();
        chocobo_refresh();
        charupdate();
        materiaupdate();
        progress_update();
        setPreviewColors();
        if(ui->action_show_debug->isChecked()){testdata_refresh();}
        ui->w_m_s1->click();
        }
}/*~~~~~~~~~~~~~~~~~~~~End GUIREFRESH ~~~~~~~~~~~~~~~~~*/
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
    QByteArray text;
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
    if((ff7->slot[s].chocomated)& (1<<0)){ui->cb_c1_mated->setChecked(1);}
    else{ui->cb_c1_mated->setChecked(0);}
    if((ff7->slot[s].chocomated)& (1<<1)){ui->cb_c2_mated->setChecked(1);}
    else{ui->cb_c2_mated->setChecked(0);}
    if((ff7->slot[s].chocomated)& (1<<2)){ui->cb_c3_mated->setChecked(1);}
    else{ui->cb_c3_mated->setChecked(0);}
    if((ff7->slot[s].chocomated)& (1<<3)){ui->cb_c4_mated->setChecked(1);}
    else{ui->cb_c4_mated->setChecked(0);}
    if((ff7->slot[s].chocomated)& (1<<4)){ui->cb_c5_mated->setChecked(1);}
    else{ui->cb_c5_mated->setChecked(0);}
    if((ff7->slot[s].chocomated)& (1<<5)){ui->cb_c6_mated->setChecked(1);}
    else{ui->cb_c6_mated->setChecked(0);}

    ui->line_c1_name->clear();
    text.clear();
    for (int n=0;n<6;n++){text.append(ff7->slot[s].chocobonames[0][n]);}
    ui->line_c1_name->setText(Text.toPC(text));
    //ui->cb_c1_personality->setCurrentIndex(ff7->slot[s].chocobos[0].personality); //need more data for this.
    ui->sb_c1_sprint->setValue(ff7->slot[s].chocobos[0].sprintspd);
    ui->sb_c1_maxsprint->setValue(ff7->slot[s].chocobos[0].maxsprintspd);
    ui->sb_c1_speed->setValue(ff7->slot[s].chocobos[0].speed);
    ui->sb_c1_maxspeed->setValue((ff7->slot[s].chocobos[0].maxspeed));
    ui->cb_c1_sex->setCurrentIndex(ff7->slot[s].chocobos[0].sex);
    ui->cb_c1_type->setCurrentIndex(ff7->slot[s].chocobos[0].type);
    ui->sb_c1_accel->setValue(ff7->slot[s].chocobos[0].accel);
    ui->sb_c1_coop->setValue(ff7->slot[s].chocobos[0].coop);
    ui->sb_c1_intel->setValue(ff7->slot[s].chocobos[0].intelligence);
    ui->sb_c1_pcount->setValue(ff7->slot[s].chocobos[0].pcount);
    ui->sb_c1_raceswon->setValue(ff7->slot[s].chocobos[0].raceswon);
    ui->sb_c1_stamina->setValue(ff7->slot[s].chocostaminas[0]);//Bug fixed Before was chocostaminas[0]*10 and (999*10 != 9999), is 9990 (Vegeta_Ss4) v0.8.3
    ui->sb_c1_personality->setValue(ff7->slot[s].chocobos[0].personality);
    // end choco 1

    ui->line_c2_name->clear();
    text.clear();
    for (int n=0;n<6;n++){text.append(ff7->slot[s].chocobonames[1][n]);}
    ui->line_c2_name->setText(Text.toPC(text));
    //ui->cb_c2_personality->setCurrentIndex(ff7->slot[s].chocobos[1].personality); //need more data for this.
    ui->sb_c2_sprint->setValue(ff7->slot[s].chocobos[1].sprintspd);
    ui->sb_c2_maxsprint->setValue(ff7->slot[s].chocobos[1].maxsprintspd);
    ui->sb_c2_speed->setValue(ff7->slot[s].chocobos[1].speed);
    ui->sb_c2_maxspeed->setValue((ff7->slot[s].chocobos[1].maxspeed));
    ui->cb_c2_sex->setCurrentIndex(ff7->slot[s].chocobos[1].sex);
    ui->cb_c2_type->setCurrentIndex(ff7->slot[s].chocobos[1].type);
    ui->sb_c2_accel->setValue(ff7->slot[s].chocobos[1].accel);
    ui->sb_c2_coop->setValue(ff7->slot[s].chocobos[1].coop);
    ui->sb_c2_intel->setValue(ff7->slot[s].chocobos[1].intelligence);
    ui->sb_c2_pcount->setValue(ff7->slot[s].chocobos[1].pcount);
    ui->sb_c2_raceswon->setValue(ff7->slot[s].chocobos[1].raceswon);
    ui->sb_c2_stamina->setValue(ff7->slot[s].chocostaminas[1]);//Bug fix (Vegeta_Ss4) v0.8.3
    ui->sb_c2_personality->setValue(ff7->slot[s].chocobos[1].personality);
    //end Choco 2

    ui->line_c3_name->clear();
    text.clear();
    for (int n=0;n<6;n++){text.append(ff7->slot[s].chocobonames[2][n]);}
    ui->line_c3_name->setText(Text.toPC(text));
    //ui->cb_c3_personality->setCurrentIndex(ff7->slot[s].chocobos[2].personality); //need more data for this.
    ui->sb_c3_sprint->setValue(ff7->slot[s].chocobos[2].sprintspd);
    ui->sb_c3_maxsprint->setValue(ff7->slot[s].chocobos[2].maxsprintspd);
    ui->sb_c3_speed->setValue(ff7->slot[s].chocobos[2].speed);
    ui->sb_c3_maxspeed->setValue((ff7->slot[s].chocobos[2].maxspeed));
    ui->cb_c3_sex->setCurrentIndex(ff7->slot[s].chocobos[2].sex);
    ui->cb_c3_type->setCurrentIndex(ff7->slot[s].chocobos[2].type);
    ui->sb_c3_accel->setValue(ff7->slot[s].chocobos[2].accel);
    ui->sb_c3_coop->setValue(ff7->slot[s].chocobos[2].coop);
    ui->sb_c3_intel->setValue(ff7->slot[s].chocobos[2].intelligence);
    ui->sb_c3_pcount->setValue(ff7->slot[s].chocobos[2].pcount);
    ui->sb_c3_raceswon->setValue(ff7->slot[s].chocobos[2].raceswon);
    ui->sb_c3_stamina->setValue(ff7->slot[s].chocostaminas[2]);//Bug fix (Vegeta_Ss4) v0.8.3
    ui->sb_c3_personality->setValue(ff7->slot[s].chocobos[2].personality);
    // end choco 3

    ui->line_c4_name->clear();
    text.clear();
    for (int n=0;n<6;n++){text.append(ff7->slot[s].chocobonames[3][n]);}
    ui->line_c4_name->setText(Text.toPC(text));
    //ui->cb_c4_personality->setCurrentIndex(ff7->slot[s].chocobos[3].personality); //need more data for this.
    ui->sb_c4_sprint->setValue(ff7->slot[s].chocobos[3].sprintspd);
    ui->sb_c4_maxsprint->setValue(ff7->slot[s].chocobos[3].maxsprintspd);
    ui->sb_c4_speed->setValue(ff7->slot[s].chocobos[3].speed);
    ui->sb_c4_maxspeed->setValue((ff7->slot[s].chocobos[3].maxspeed));
    ui->cb_c4_sex->setCurrentIndex(ff7->slot[s].chocobos[3].sex);
    ui->cb_c4_type->setCurrentIndex(ff7->slot[s].chocobos[3].type);
    ui->sb_c4_accel->setValue(ff7->slot[s].chocobos[3].accel);
    ui->sb_c4_coop->setValue(ff7->slot[s].chocobos[3].coop);
    ui->sb_c4_intel->setValue(ff7->slot[s].chocobos[3].intelligence);
    ui->sb_c4_pcount->setValue(ff7->slot[s].chocobos[3].pcount);
    ui->sb_c4_raceswon->setValue(ff7->slot[s].chocobos[3].raceswon);
    ui->sb_c4_stamina->setValue(ff7->slot[s].chocostaminas[3]);//Bug fix (Vegeta_Ss4) v0.8.3
    ui->sb_c4_personality->setValue(ff7->slot[s].chocobos[3].personality);
    // end choco 4

    ui->line_c5_name->clear();
    text.clear();
    for (int n=0;n<6;n++){text.append(ff7->slot[s].chocobonames[4][n]);}
    ui->line_c5_name->setText(Text.toPC(text));
    //ui->cb_c5_personality->setCurrentIndex(ff7->slot[s].choco56[0].personality); //need more data for this.
    ui->sb_c5_sprint->setValue(ff7->slot[s].choco56[0].sprintspd);
    ui->sb_c5_maxsprint->setValue(ff7->slot[s].choco56[0].maxsprintspd);
    ui->sb_c5_speed->setValue(ff7->slot[s].choco56[0].speed);
    ui->sb_c5_maxspeed->setValue((ff7->slot[s].choco56[0].maxspeed));
    ui->cb_c5_sex->setCurrentIndex(ff7->slot[s].choco56[0].sex);
    ui->cb_c5_type->setCurrentIndex(ff7->slot[s].choco56[0].type);
    ui->sb_c5_accel->setValue(ff7->slot[s].choco56[0].accel);
    ui->sb_c5_coop->setValue(ff7->slot[s].choco56[0].coop);
    ui->sb_c5_intel->setValue(ff7->slot[s].choco56[0].intelligence);
    ui->sb_c5_pcount->setValue(ff7->slot[s].choco56[0].pcount);
    ui->sb_c5_raceswon->setValue(ff7->slot[s].choco56[0].raceswon);
    ui->sb_c5_stamina->setValue(ff7->slot[s].chocostaminas[4]);//Bug fix (Vegeta_Ss4) v0.8.3
    ui->sb_c5_personality->setValue(ff7->slot[s].choco56[0].personality);
    // end choco 5
    ui->line_c6_name->clear();
    text.clear();
    for (int n=0;n<6;n++){text.append(ff7->slot[s].chocobonames[5][n]);}
    ui->line_c6_name->setText(Text.toPC(text));
    //ui->cb_c6_personality->setCurrentIndex(ff7->slot[s].choco56[1].personality); //need more data for this.
    ui->sb_c6_sprint->setValue(ff7->slot[s].choco56[1].sprintspd);
    ui->sb_c6_maxsprint->setValue(ff7->slot[s].choco56[1].maxsprintspd);
    ui->sb_c6_speed->setValue(ff7->slot[s].choco56[1].speed);
    ui->sb_c6_maxspeed->setValue((ff7->slot[s].choco56[1].maxspeed));
    ui->cb_c6_sex->setCurrentIndex(ff7->slot[s].choco56[1].sex);
    ui->cb_c6_type->setCurrentIndex(ff7->slot[s].choco56[1].type);
    ui->sb_c6_accel->setValue(ff7->slot[s].choco56[1].accel);
    ui->sb_c6_coop->setValue(ff7->slot[s].choco56[1].coop);
    ui->sb_c6_intel->setValue(ff7->slot[s].choco56[1].intelligence);
    ui->sb_c6_pcount->setValue(ff7->slot[s].choco56[1].pcount);
    ui->sb_c6_raceswon->setValue(ff7->slot[s].choco56[1].raceswon);
    ui->sb_c6_stamina->setValue(ff7->slot[s].chocostaminas[5]);//Bug fix (Vegeta_Ss4) v0.8.3
    ui->sb_c6_personality->setValue(ff7->slot[s].choco56[1].personality);
    // end choco 6
    //set the penned chocobos
    ui->combo_pen1->setCurrentIndex(ff7->slot[s].pennedchocos[0]);
    ui->combo_pen2->setCurrentIndex(ff7->slot[s].pennedchocos[1]);
    ui->combo_pen3->setCurrentIndex(ff7->slot[s].pennedchocos[2]);
    ui->combo_pen4->setCurrentIndex(ff7->slot[s].pennedchocos[3]);
    load=false;
}/*~~~~~~~~~~~End Chocobo Slots~~~~~~~~~*/
/*~~~~~~~~~~~Clear Slots~~~~~~~~~~~~~~*/
void MainWindow::clearslot(int rmslot)
{
    QByteArray temp;
    temp.fill(0x00,0x10f4);
    memcpy(ff7->hf[rmslot].sl_header,temp,ff7->SG_SLOT_HEADER);// clear the header..
    memcpy(&ff7->slot[rmslot],temp,0x10f4);
    memcpy(ff7->hf[rmslot].sl_footer,temp,ff7->SG_SLOT_FOOTER);// clear the footer..
    ff7->SG_Region_String[rmslot].clear();
    if(ff7->SG_TYPE =="MC" || ff7->SG_TYPE =="PSP" || ff7->SG_TYPE =="VGS" || ff7->SG_TYPE =="DEX")
    {//clean the mem card header if needed.
        int index = (128+(128*rmslot));
        if (ff7->SG_TYPE == "PSP"){index +=0x80;}
        else if (ff7->SG_TYPE == "VGS"){index +=0x40;}
        else if (ff7->SG_TYPE == "DEX"){index +=0xF40;}
        temp.resize(128);
        temp.fill(0x00);
        temp[0]=0xA0;
        temp[8]=0xFF;
        temp[9]=0xFF;
        temp[0x7F]=0xA0;
        memcpy(&ff7->file_headerp[index],temp,128);
    }
}
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

    if((ff7->slot[s].itemsmask_1)& (1<<1)){ui->cb_itemmask1_2->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_2->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].itemsmask_1)& (1<<2)){ui->cb_itemmask1_3->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_3->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].itemsmask_1)& (1<<3)){ui->cb_itemmask1_4->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_4->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].itemsmask_1)& (1<<4)){ui->cb_itemmask1_5->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_5->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].itemsmask_1)& (1<<5)){ui->cb_itemmask1_6->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_6->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].itemsmask_1)& (1<<6)){ui->cb_itemmask1_7->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_7->setChecked(Qt::Unchecked);}
    if((ff7->slot[s].itemsmask_1)& (1<<7)){ui->cb_itemmask1_8->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_8->setChecked(Qt::Unchecked);}
    ui->lcd_itemmask_1->display(ff7->slot[s].itemsmask_1);

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
    load=false;

    unknown_refresh(ui->combo_z_var->currentIndex());
}
/*~~~~~~~~~Char Buttons.~~~~~~~~~~~*/
void MainWindow::on_btn_cloud_clicked()     {curchar=0; charupdate();ui->btn_cloud->setStyleSheet(avatar_style(ff7->slot[s].chars[curchar].id));}
void MainWindow::on_btn_barret_clicked()    {curchar=1; charupdate();ui->btn_barret->setStyleSheet(avatar_style(ff7->slot[s].chars[curchar].id));}
void MainWindow::on_btn_tifa_clicked()      {curchar=2; charupdate();ui->btn_tifa->setStyleSheet(avatar_style(ff7->slot[s].chars[curchar].id));}
void MainWindow::on_btn_aeris_clicked()     {curchar=3; charupdate();ui->btn_aeris->setStyleSheet(avatar_style(ff7->slot[s].chars[curchar].id));}
void MainWindow::on_btn_red_clicked()       {curchar=4; charupdate();ui->btn_red->setStyleSheet(avatar_style(ff7->slot[s].chars[curchar].id));}
void MainWindow::on_btn_yuffie_clicked()    {curchar=5; charupdate();ui->btn_yuffie->setStyleSheet(avatar_style(ff7->slot[s].chars[curchar].id));}
void MainWindow::on_btn_cait_clicked()      {curchar=6; charupdate();ui->btn_cait->setStyleSheet(avatar_style(ff7->slot[s].chars[curchar].id));}
void MainWindow::on_btn_vincent_clicked()   {curchar=7; charupdate();ui->btn_vincent->setStyleSheet(avatar_style(ff7->slot[s].chars[curchar].id));}
void MainWindow::on_btn_cid_clicked()       {curchar=8; charupdate();ui->btn_cid->setStyleSheet(avatar_style(ff7->slot[s].chars[curchar].id));}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Party TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_sb_gil_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].gil = value;   ff7->slot[s].desc.gil = value;}}
void MainWindow::on_sb_gp_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].gp = value;}}
void MainWindow::on_sb_battles_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].battles = value;}}
void MainWindow::on_sb_runs_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].runs = value;}}
void MainWindow::on_combo_party1_currentIndexChanged(int index)
{if(!load){file_changed=true;
    if(index == 12) //empty char slot?
    {
        ff7->slot[s].party[0] = 0xFF;
        //wipe all desc data if noone is there
        ff7->slot[s].desc.party[0]=ff7->slot[s].party[0];
        ff7->slot[s].desc.curHP =0;
        ff7->slot[s].desc.maxHP =0;
        ff7->slot[s].desc.curMP =0;
        ff7->slot[s].desc.maxMP =0;
        ff7->slot[s].desc.level =0;
        for(int n=0;n<16;n++)
        {
            ff7->slot[s].desc.name[n]=0xFF;
        }
    }
    else
    {
        ff7->slot[s].party[0] = index;
        ff7->slot[s].desc.party[0]=ff7->slot[s].party[0];
        ff7->slot[s].desc.curHP =ff7->slot[s].chars[ui->combo_party1->currentIndex()].curHP;
        ff7->slot[s].desc.maxHP =ff7->slot[s].chars[ui->combo_party1->currentIndex()].maxHP;
        ff7->slot[s].desc.curMP =ff7->slot[s].chars[ui->combo_party1->currentIndex()].curMP;
        ff7->slot[s].desc.maxMP =ff7->slot[s].chars[ui->combo_party1->currentIndex()].maxMP;
        ff7->slot[s].desc.level = ff7->slot[s].chars[ui->combo_party1->currentIndex()].level;
        for(int n=0;n<16;n++)
        {
            if(n<13){ff7->slot[s].desc.name[n]=ff7->slot[s].chars[ui->combo_party1->currentIndex()].name[n];}
            else{ff7->slot[s].desc.name[n]=0xFF;}
        }
    }
}}
void MainWindow::on_combo_party2_currentIndexChanged(int index)
{if(!load){file_changed=true;
    if(index == 12){ff7->slot[s].party[1]= 0xFF;}
    else{ff7->slot[s].party[1] = index;}
    //either way set the desc
    ff7->slot[s].desc.party[1]=ff7->slot[s].party[1];
}}
void MainWindow::on_combo_party3_currentIndexChanged(int index)
{if(!load){file_changed=true;
    if(index ==12){ff7->slot[s].party[2] =0xFF;}
    else{ff7->slot[s].party[2] = index;}
    ff7->slot[s].desc.party[2]=ff7->slot[s].party[2];
}}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chocobo Tab~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//set data for stables inside
void MainWindow::on_sb_stables_owned_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].stables = value;}
    switch(value)
    {
        case 0:
            ui->box_stable1->setEnabled(false);
            ui->box_stable2->setEnabled(false);
            ui->box_stable3->setEnabled(false);
            ui->box_stable4->setEnabled(false);
            ui->box_stable5->setEnabled(false);
            ui->box_stable6->setEnabled(false);
            break;

        case 1:
            ui->box_stable1->setEnabled(true);
            ui->box_stable2->setEnabled(false);
            ui->box_stable3->setEnabled(false);
            ui->box_stable4->setEnabled(false);
            ui->box_stable5->setEnabled(false);
            ui->box_stable6->setEnabled(false);
        break;

        case 2:
            ui->box_stable1->setEnabled(true);
            ui->box_stable2->setEnabled(true);
            ui->box_stable3->setEnabled(false);
            ui->box_stable4->setEnabled(false);
            ui->box_stable5->setEnabled(false);
            ui->box_stable6->setEnabled(false);
            break;

        case 3:
            ui->box_stable1->setEnabled(true);
            ui->box_stable2->setEnabled(true);
            ui->box_stable3->setEnabled(true);
            ui->box_stable4->setEnabled(false);
            ui->box_stable5->setEnabled(false);
            ui->box_stable6->setEnabled(false);
            break;

        case 4:
            ui->box_stable1->setEnabled(true);
            ui->box_stable2->setEnabled(true);
            ui->box_stable3->setEnabled(true);
            ui->box_stable4->setEnabled(true);
            ui->box_stable5->setEnabled(false);
            ui->box_stable6->setEnabled(false);
            break;

        case 5:
            ui->box_stable1->setEnabled(true);
            ui->box_stable2->setEnabled(true);
            ui->box_stable3->setEnabled(true);
            ui->box_stable4->setEnabled(true);
            ui->box_stable5->setEnabled(true);
            ui->box_stable6->setEnabled(false);
            break;

        case 6:
            ui->box_stable1->setEnabled(true);
            ui->box_stable2->setEnabled(true);
            ui->box_stable3->setEnabled(true);
            ui->box_stable4->setEnabled(true);
            ui->box_stable5->setEnabled(true);
            ui->box_stable6->setEnabled(true);
            break;
    }
}
/*~~~~~~~~~Occupied~~~~~~~~~~~*/
void MainWindow::on_box_stable1_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocobomask |= (1<<0);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<0);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
void MainWindow::on_box_stable2_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocobomask |= (1<<1);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<1);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
void MainWindow::on_box_stable3_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocobomask |= (1<<2);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<2);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
void MainWindow::on_box_stable4_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocobomask |= (1<<3);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<3);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
void MainWindow::on_box_stable5_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocobomask |= (1<<4);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<4);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
void MainWindow::on_box_stable6_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocobomask |= (1<<5);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()+1);}
    else{ff7->slot[s].chocobomask &= ~(1<<5);ui->lcd_stables_occupied->display(ui->lcd_stables_occupied->value()-1);}
    ff7->slot[s].stablesoccupied=ui->lcd_stables_occupied->value();
}}
/*~~~~~ChocoboStats~~~~~*/
void MainWindow::on_line_c1_name_textChanged(QString text)
{if(!load){file_changed=true;
        QByteArray temp = Text.toFF7(text);
        for (int i=0;i<6;i++){ff7->slot[s].chocobonames[0][i] =0xFF;}
        memcpy(ff7->slot[s].chocobonames[0],temp,temp.length());
}}
void MainWindow::on_sb_c1_stamina_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocostaminas[0] = value;}}
void MainWindow::on_sb_c1_speed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[0].speed = value;}}
void MainWindow::on_sb_c1_maxspeed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[0].maxspeed = value;}}
void MainWindow::on_sb_c1_sprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[0].sprintspd = value;}}
void MainWindow::on_sb_c1_maxsprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[0].maxsprintspd = value;}}
void MainWindow::on_cb_c1_sex_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].chocobos[0].sex = index;}}
void MainWindow::on_cb_c1_type_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].chocobos[0].type = index;}}
void MainWindow::on_sb_c1_coop_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[0].coop= value;}}
void MainWindow::on_sb_c1_accel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[0].accel= value;}}
void MainWindow::on_sb_c1_intel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[0].intelligence = value;}}
void MainWindow::on_sb_c1_raceswon_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[0].raceswon = value;}}
void MainWindow::on_sb_c1_pcount_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[0].pcount= value;}}
void MainWindow::on_sb_c1_personality_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[0].personality=value;}}
void MainWindow::on_cb_c1_mated_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocomated |= (1<<0);}
    else{ff7->slot[s].chocomated &= ~(1<<0);}
}}

void MainWindow::on_line_c2_name_textChanged(QString text)
{if(!load){file_changed=true;
        QByteArray temp = Text.toFF7(text);
        for (int i=0;i<6;i++){ff7->slot[s].chocobonames[1][i] =0xFF;}
        memcpy(ff7->slot[s].chocobonames[1],temp,temp.length());
}}
void MainWindow::on_sb_c2_stamina_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocostaminas[1] = value;}}
void MainWindow::on_sb_c2_speed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[1].speed = value;}}
void MainWindow::on_sb_c2_maxspeed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[1].maxspeed = value;}}
void MainWindow::on_sb_c2_sprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[1].sprintspd = value;}}
void MainWindow::on_sb_c2_maxsprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[1].maxsprintspd = value;}}
void MainWindow::on_cb_c2_sex_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].chocobos[1].sex = index;}}
void MainWindow::on_cb_c2_type_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].chocobos[1].type = index;}}
void MainWindow::on_sb_c2_coop_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[1].coop= value;}}
void MainWindow::on_sb_c2_accel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[1].accel= value;}}
void MainWindow::on_sb_c2_intel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[1].intelligence = value;}}
void MainWindow::on_sb_c2_raceswon_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[1].raceswon = value;}}
void MainWindow::on_sb_c2_pcount_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[1].pcount= value;}}
void MainWindow::on_sb_c2_personality_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[1].personality=value;}}
void MainWindow::on_cb_c2_mated_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocomated |= (1<<1);}
    else{ff7->slot[s].chocomated &= ~(1<<1);}
}}

void MainWindow::on_line_c3_name_textChanged(QString text)
{if(!load){file_changed=true;
        QByteArray temp = Text.toFF7(text);
        for (int i=0;i<6;i++){ff7->slot[s].chocobonames[2][i] =0xFF;}
        memcpy(ff7->slot[s].chocobonames[2],temp,temp.length());
}}
void MainWindow::on_sb_c3_stamina_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocostaminas[2] =value;}}
void MainWindow::on_sb_c3_speed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[2].speed = value;}}
void MainWindow::on_sb_c3_maxspeed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[2].maxspeed = value;}}
void MainWindow::on_sb_c3_sprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[2].sprintspd = value;}}
void MainWindow::on_sb_c3_maxsprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[2].maxsprintspd = value;}}
void MainWindow::on_cb_c3_sex_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].chocobos[2].sex = index;}}
void MainWindow::on_cb_c3_type_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].chocobos[2].type = index;}}
void MainWindow::on_sb_c3_coop_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[2].coop= value;}}
void MainWindow::on_sb_c3_accel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[2].accel= value;}}
void MainWindow::on_sb_c3_intel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[2].intelligence = value;}}
void MainWindow::on_sb_c3_raceswon_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[2].raceswon = value;}}
void MainWindow::on_sb_c3_pcount_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[2].pcount= value;}}
void MainWindow::on_sb_c3_personality_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[2].personality=value;}}
void MainWindow::on_cb_c3_mated_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocomated |= (1<<2);}
    else{ff7->slot[s].chocomated &= ~(1<<2);}
}}

void MainWindow::on_line_c4_name_textChanged(QString text)
{if(!load){file_changed=true;
        QByteArray temp = Text.toFF7(text);
        for (int i=0;i<6;i++){ff7->slot[s].chocobonames[3][i] =0xFF;}
        memcpy(ff7->slot[s].chocobonames[3],temp,temp.length());
}}
void MainWindow::on_sb_c4_stamina_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocostaminas[3] = value;}}
void MainWindow::on_sb_c4_speed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[3].speed = value;}}
void MainWindow::on_sb_c4_maxspeed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[3].maxspeed = value;}}
void MainWindow::on_sb_c4_sprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[3].sprintspd = value;}}
void MainWindow::on_sb_c4_maxsprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[3].maxsprintspd = value;}}
void MainWindow::on_cb_c4_sex_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].chocobos[3].sex = index;}}
void MainWindow::on_cb_c4_type_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].chocobos[3].type = index;}}
void MainWindow::on_sb_c4_coop_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[3].coop= value;}}
void MainWindow::on_sb_c4_accel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[3].accel= value;}}
void MainWindow::on_sb_c4_intel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[3].intelligence = value;}}
void MainWindow::on_sb_c4_raceswon_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[3].raceswon = value;}}
void MainWindow::on_sb_c4_pcount_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[3].pcount= value;}}
void MainWindow::on_sb_c4_personality_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocobos[3].personality=value;}}
void MainWindow::on_cb_c4_mated_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocomated |= (1<<3);}
    else{ff7->slot[s].chocomated &= ~(1<<3);}
}}

void MainWindow::on_line_c5_name_textChanged(QString text)
{if(!load){file_changed=true;
        QByteArray temp = Text.toFF7(text);
        for (int i=0;i<6;i++){ff7->slot[s].chocobonames[4][i] =0xFF;}
        memcpy(ff7->slot[s].chocobonames[4],temp,temp.length());
}}
void MainWindow::on_sb_c5_stamina_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocostaminas[4] = value;}}
void MainWindow::on_sb_c5_speed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[0].speed = value;}}
void MainWindow::on_sb_c5_maxspeed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[0].maxspeed = value;}}
void MainWindow::on_sb_c5_sprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[0].sprintspd = value;}}
void MainWindow::on_sb_c5_maxsprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[0].maxsprintspd = value;}}
void MainWindow::on_cb_c5_sex_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].choco56[0].sex = index;}}
void MainWindow::on_cb_c5_type_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].choco56[0].type = index;}}
void MainWindow::on_sb_c5_coop_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[0].coop= value;}}
void MainWindow::on_sb_c5_accel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[0].accel= value;}}
void MainWindow::on_sb_c5_intel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[0].intelligence = value;}}
void MainWindow::on_sb_c5_raceswon_valueChanged(int value){ if(!load){file_changed=true; ff7->slot[s].choco56[0].raceswon = value;}}
void MainWindow::on_sb_c5_pcount_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[0].pcount= value;}}
void MainWindow::on_sb_c5_personality_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[0].personality=value;}}
void MainWindow::on_cb_c5_mated_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocomated |= (1<<4);}
    else{ff7->slot[s].chocomated &= ~(1<<4);}
}}

void MainWindow::on_line_c6_name_textChanged(QString text)
{if(!load){file_changed=true;
        QByteArray temp = Text.toFF7(text);
        for (int i=0;i<6;i++){ff7->slot[s].chocobonames[5][i] =0xFF;}
        memcpy(ff7->slot[s].chocobonames[5],temp,temp.length());
}}
void MainWindow::on_sb_c6_stamina_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chocostaminas[5] = value;}}
void MainWindow::on_sb_c6_speed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[1].speed = value;}}
void MainWindow::on_sb_c6_maxspeed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[1].maxspeed = value;}}
void MainWindow::on_sb_c6_sprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[1].sprintspd = value;}}
void MainWindow::on_sb_c6_maxsprint_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[1].maxsprintspd = value;}}
void MainWindow::on_cb_c6_sex_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].choco56[1].sex = index;}}
void MainWindow::on_cb_c6_type_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].choco56[1].type = index;}}
void MainWindow::on_sb_c6_coop_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[1].coop= value;}}
void MainWindow::on_sb_c6_accel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[1].accel= value;}}
void MainWindow::on_sb_c6_intel_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[1].intelligence = value;}}
void MainWindow::on_sb_c6_raceswon_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[1].raceswon = value;}}
void MainWindow::on_sb_c6_pcount_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[1].pcount= value;}}
void MainWindow::on_sb_c6_personality_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].choco56[1].personality=value;}}
void MainWindow::on_cb_c6_mated_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].chocomated |= (1<<5);}
    else{ff7->slot[s].chocomated &= ~(1<<5);}
}}

//set data for pens outside
void MainWindow::on_combo_pen1_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].pennedchocos[0]=index;}}
void MainWindow::on_combo_pen2_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].pennedchocos[1]=index;}}
void MainWindow::on_combo_pen3_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].pennedchocos[2]=index;}}
void MainWindow::on_combo_pen4_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].pennedchocos[3]=index;}}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OTHERS TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_list_phs_chars_itemChanged(QListWidgetItem * item)
{if(!load){file_changed=true;
    int j = item->listWidget()->currentRow();
    if(item->checkState() ==Qt::Unchecked){ff7->slot[s].phsmask |=(1 <<j);}
    else{ff7->slot[s].phsmask &= ~(1<<j);}
}}

void MainWindow::on_list_chars_unlocked_itemChanged(QListWidgetItem * item)
{if(!load){file_changed=true;
    int j = item->listWidget()->currentRow();
    if(item->checkState() ==Qt::Checked){ff7->slot[s].unlockedchars |= (1<<j);}
    else{ff7->slot[s].unlockedchars &= ~(1<<j);}
}}

void MainWindow::on_sb_love_barret_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].love.barret = value;}}
void MainWindow::on_sb_love_aeris_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].love.aeris = value;}}
void MainWindow::on_sb_love_tifa_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].love.tifa = value;}}
void MainWindow::on_sb_love_yuffie_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].love.yuffie = value;}}

void MainWindow::on_sb_time_hour_valueChanged(int value)
{if(!load){file_changed=true;
        ff7->slot[s].time = ((value*3600) + (ui->sb_time_min->value()*60) + (ui->sb_time_sec->value())); ff7->slot[s].desc.time = ff7->slot[s].time;
}}

void MainWindow::on_sb_time_min_valueChanged(int value)
{if(!load){file_changed=true;
        ff7->slot[s].time = ( (ui->sb_time_hour->value()*3600) + ((value*60)) + (ui->sb_time_sec->value()) );ff7->slot[s].desc.time = ff7->slot[s].time;
}}

void MainWindow::on_sb_time_sec_valueChanged(int value)
{if(!load){file_changed=true;
        ff7->slot[s].time = ((ui->sb_time_hour->value()*3600) + (ui->sb_time_min->value()*60) + (value)); ff7->slot[s].desc.time = ff7->slot[s].time;
}}

void MainWindow::on_sb_steps_valueChanged(int value)
{if(!load){file_changed=true;
  ff7->slot[s].steps = value;
}}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Item Tab~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_list_flyers_itemChanged(QListWidgetItem * item)
{if(!load){file_changed=true;
    int j=item->listWidget()->currentRow();
    if(item->checkState() ==Qt::Checked){ff7->slot[s].turtleflyers |= (1 << j);}
    else{ff7->slot[s].turtleflyers &= ~(1<<j);}
 }}

void MainWindow::on_list_keyitems_itemChanged(QListWidgetItem *item)
{if(!load){file_changed=true;
    int j = item->listWidget()->currentRow();
    if (item->checkState() == Qt::Checked){ff7->slot[s].keyitems[j/8] |= (1<<j%8);}
    else{ff7->slot[s].keyitems[j/8] &= ~(1<<j%8);}
}}
// Field Items Combos
void MainWindow::on_cb_bm_items_1_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_38[48] |= (1<<0);}else{ff7->slot[s].z_38[48] &= ~(1<<0);}}}
void MainWindow::on_cb_bm_items_2_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_38[48] |= (1<<1);}else{ff7->slot[s].z_38[48] &= ~(1<<1);}}}
void MainWindow::on_cb_bm_items_3_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_38[48] |= (1<<2);}else{ff7->slot[s].z_38[48] &= ~(1<<2);}}}
void MainWindow::on_cb_bm_items_4_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_38[48] |= (1<<3);}else{ff7->slot[s].z_38[48] &= ~(1<<3);}}}

void MainWindow::on_cb_s7tg_items_1_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_9[4] |= (1<<0);}else{ff7->slot[s].z_9[4] &= ~(1<<0);}}}
void MainWindow::on_cb_s7tg_items_2_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_9[4] |= (1<<1);}else{ff7->slot[s].z_9[4] &= ~(1<<1);}}}
void MainWindow::on_cb_s7tg_items_3_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_9[4] |= (1<<2);}else{ff7->slot[s].z_9[4] &= ~(1<<2);}}}
void MainWindow::on_cb_s7tg_items_4_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_9[4] |= (1<<3);}else{ff7->slot[s].z_9[4] &= ~(1<<3);}}}
void MainWindow::on_cb_s7tg_items_5_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_9[4] |= (1<<4);}else{ff7->slot[s].z_9[4] &= ~(1<<4);}}}
void MainWindow::on_cb_s7tg_items_6_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_9[4] |= (1<<5);}else{ff7->slot[s].z_9[4] &= ~(1<<5);}}}
void MainWindow::on_cb_s7tg_items_7_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_9[4] |= (1<<6);}else{ff7->slot[s].z_9[4] &= ~(1<<6);}}}
void MainWindow::on_cb_s7tg_items_8_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_9[4] |= (1<<7);}else{ff7->slot[s].z_9[4] &= ~(1<<7);}}}

void MainWindow::on_cb_farm_items_1_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_11[3] |= (1<<0);}else{ff7->slot[s].z_11[3] &= ~(1<<0);}}}
void MainWindow::on_cb_farm_items_2_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_11[3] |= (1<<1);}else{ff7->slot[s].z_11[3] &= ~(1<<1);}}}
void MainWindow::on_cb_farm_items_3_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_11[3] |= (1<<2);}else{ff7->slot[s].z_11[3] &= ~(1<<2);}}}
void MainWindow::on_cb_farm_items_4_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_11[3] |= (1<<3);}else{ff7->slot[s].z_11[3] &= ~(1<<3);}}}
void MainWindow::on_cb_farm_items_5_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_11[3] |= (1<<4);}else{ff7->slot[s].z_11[3] &= ~(1<<4);}}}
void MainWindow::on_cb_farm_items_6_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_11[3] |= (1<<5);}else{ff7->slot[s].z_11[3] &= ~(1<<5);}}}
void MainWindow::on_cb_farm_items_7_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_11[3] |= (1<<6);}else{ff7->slot[s].z_11[3] &= ~(1<<6);}}}
void MainWindow::on_cb_farm_items_8_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_11[3] |= (1<<7);}else{ff7->slot[s].z_11[3] &= ~(1<<7);}}}

void MainWindow::on_clearItem_clicked()
{
    ff7->slot[s].items[ui->tbl_itm->currentRow()].id = 0xFF;
    ff7->slot[s].items[ui->tbl_itm->currentRow()].qty = 0xFF;
    itemupdate();
}
void MainWindow::on_btn_clear_keyitems_clicked()
{if(!load){file_changed=true; }//used in other functions
    for(int i=0;i<51;i++)// be sure to clear key items first..
    {
        ui->list_keyitems->setCurrentRow(i);
        ui->list_keyitems->currentItem()->setCheckState(Qt::Unchecked);
    }
    ui->list_keyitems->setCurrentRow(0);
    ui->list_keyitems->setCurrentRow(-1);
}

void MainWindow::on_combo_additem_currentIndexChanged(int index)
{if(!load){file_changed=true;    //we must also set the qty, since that determins how the table and the game will reconize the item and prevents bug#3014592.
    if (index<256){ff7->slot[s].items[ui->tbl_itm->currentRow()].id = index;ff7->slot[s].items[ui->tbl_itm->currentRow()].qty = quint8(ui->sb_addqty->value() * 2);}
    else{ff7->slot[s].items[ui->tbl_itm->currentRow()].id = (index-256);ff7->slot[s].items[ui->tbl_itm->currentRow()].qty  = quint8(ui->sb_addqty->value()* 2) +1;}
    itemupdate();
}}

void MainWindow::on_sb_addqty_valueChanged(int value)
{if(!load){file_changed=true;
    if (ui->combo_additem->currentIndex()<256){ff7->slot[s].items[ui->tbl_itm->currentRow()].qty = quint8(value * 2);}
    else{ff7->slot[s].items[ui->tbl_itm->currentRow()].qty  = quint8(value* 2) +1;}
    itemupdate();
}}

void MainWindow::on_tbl_itm_currentCellChanged(int row)
{if(!load){//file_changed=true;
    if (ff7->slot[s].items[row].qty == 255 && ff7->slot[s].items[row].id == 255){/*empty slot.....do nothing*/}
    else
    {
        load=true;
        if(ff7->slot[s].items[row].qty %2 ==0)
        {
            ui->combo_additem->setCurrentIndex(ff7->slot[s].items[row].id);
            ui->sb_addqty->setValue(ff7->slot[s].items[row].qty/2);
        }
        else
        {
            ui->combo_additem->setCurrentIndex(ff7->slot[s].items[row].id+256);
            ui->sb_addqty->setValue(ff7->slot[s].items[row].qty/2);
        }
        load=false;
    }
}}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MATERIA TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_tbl_materia_currentCellChanged(int row)
{if(!load){//file_changed=true;
    if(ff7->slot[s].materias[row].id == 0x2C)//E.Skill Materia
    {
       ui->eskill_group->setVisible(true);
       geteskills(row);
       ui->combo_add_mat->setCurrentIndex(ff7->slot[s].materias[row].id);
       ui->sb_addap->setEnabled(0);
    }
    else if(ff7->slot[s].materias[row].id == 0xFF) //if the slot is empty take some precautions
    {
       load=true;
       ui->lbl_mat_stats->setText(tr("Empty Slot"));
       ui->lcd_ap_master->display(0);
       ui->sb_addap->setValue(0);
       ui->sb_addap->setMaximum(0);
       ui->combo_add_mat->setCurrentIndex(0);
       ui->combo_mat_type->setCurrentIndex(0);
       ui->combo_add_mat_2->clear();
       for(int i=0;i<0x5B;i++)
       {
           if(FF7Strings.MateriaNames(i) !=tr("DON'T USE")){ui->combo_add_mat_2->addItem(QIcon(Materias[i].image),FF7Strings.MateriaNames(i));}
       }
       ui->btn_m_lvl1->setVisible(0);
       ui->btn_m_lvl2->setVisible(0);
       ui->btn_m_lvl3->setVisible(0);
       ui->btn_m_lvl4->setVisible(0);
       ui->btn_m_lvl5->setVisible(0);
       ui->spell_lvl1_group->setVisible(0);
       ui->spell_lvl2_group->setVisible(0);
       ui->spell_lvl3_group->setVisible(0);
       ui->spell_lvl4_group->setVisible(0);
       ui->spell_lvl5_group->setVisible(0);
       ui->eskill_group->setVisible(false);
       load=false;
    }
    else
    {
        ui->eskill_group->setVisible(false);
        ui->combo_add_mat->setCurrentIndex(ff7->slot[s].materias[row].id);
        ui->sb_addap->setEnabled(1);
        ui->sb_addap->setValue(ff7->slot[s].materias[row].ap[0] |(ff7->slot[s].materias[row].ap[1] << 8) | (ff7->slot[s].materias[row].ap[2] << 16));
    }
}}

void MainWindow::on_sb_addap_valueChanged(int value)
{if(!load && ui->tbl_materia->currentRow() >-1){file_changed=true;
    if(value == Materias[ui->combo_add_mat->currentIndex()].ap[Materias[ui->combo_add_mat->currentIndex()].levels -2] && Materias[ui->combo_add_mat->currentIndex()].levels >1)
    {
        for(int i=0;i<3;i++){ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[i] = 0xFF;}
    }
    else
    {
        int a = (value & 0xff);
        int b = (value & 0xff00) >> 8;
        int c = (value & 0xff0000) >> 16;
        ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[0] = a;
        ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[1] = b;
        ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[2] = c;
    }
    materiaupdate();
}}

void MainWindow::on_combo_add_mat_currentIndexChanged(int index)
{if(!load){
    if(ui->combo_add_mat->currentText() ==tr("DON'T USE"))// this is a placeholder materia
    {
        QMessageBox::information(this,tr("Empty Materia"),tr("Place holder Materia Detected\n Remember 16777215 AP = master"));
        materiaupdate();//clean up the materia.
        return; //we are done here.
    }
        ui->combo_mat_type->setCurrentIndex(Materias[index].type);
        load=true;
        for(int i=0;i<ui->combo_add_mat_2->count();i++)
        {
            if(ui->combo_add_mat_2->itemText(i)==FF7Strings.MateriaNames(index))
            {
                ui->combo_add_mat_2->setCurrentIndex(i);
            }
        }
        load=false;
    ff7->slot[s].materias[ui->tbl_materia->currentRow()].id = index;
    materiaupdate();
}}

void MainWindow::on_btn_m_lvl1_clicked(){ui->sb_addap->setValue(0);    materiaupdate();}
void MainWindow::on_btn_m_lvl2_clicked(){ui->sb_addap->setValue(Materias[ui->combo_add_mat->currentIndex()].ap[0]);    materiaupdate();}
void MainWindow::on_btn_m_lvl3_clicked(){ui->sb_addap->setValue(Materias[ui->combo_add_mat->currentIndex()].ap[1]);    materiaupdate();}
void MainWindow::on_btn_m_lvl4_clicked(){ui->sb_addap->setValue(Materias[ui->combo_add_mat->currentIndex()].ap[2]);    materiaupdate();}
void MainWindow::on_btn_m_lvl5_clicked(){ui->sb_addap->setValue(Materias[ui->combo_add_mat->currentIndex()].ap[3]);    materiaupdate();}

void MainWindow::on_combo_mat_type_currentIndexChanged(int index)
{
    load=true;
    ui->combo_add_mat_2->clear();
    if(index == 0)
    {
        for(int i=0;i<0x5B;i++)
        {
            if(FF7Strings.MateriaNames(i) !=tr("DON'T USE")){ui->combo_add_mat_2->addItem(QIcon(Materias[i].image),FF7Strings.MateriaNames(i));}
        }
    }
    else{for(int i=0;i<0x5B;i++){if(index==Materias[i].type){ui->combo_add_mat_2->addItem(QIcon(Materias[i].image),FF7Strings.MateriaNames(i));}}}
    load=false;
}

void MainWindow::on_combo_add_mat_2_currentIndexChanged()
{if(!load){//file_changed=true; //set combo_add_mat.setCurrentindex = selected materia.id
    for(int i=0;i<0x5B;i++)
    {
        if(ui->combo_add_mat_2->currentText()== FF7Strings.MateriaNames(i)){ui->combo_add_mat->setCurrentIndex(i);}
    }
// if its eskill set it up right , or else do normal setup.
    if(ui->combo_add_mat_2->currentText()== tr("Enemy Skill")){ui->eskill_group->setVisible(true);ui->sb_addap->setEnabled(0);geteskills(ui->tbl_materia->currentRow());}
    else{ui->eskill_group->setVisible(false);ui->sb_addap->setEnabled(1);}
}}


void MainWindow::on_clearMateria_clicked()
{
    ff7->slot[s].materias[ui->tbl_materia->currentRow()].id = 0xFF;
    ui->sb_addap->setValue(0xFFFFFF);
    materiaupdate();
}

void MainWindow::on_btn_eskillall_clicked()
{
    for (int i=0;i<24;i++)
    {
        ui->list_eskill->setCurrentRow(i);
        ui->list_eskill->currentItem()->setCheckState(Qt::Checked);
    }
    ui->list_eskill->setCurrentRow(-1);
}

void MainWindow::geteskills(int row)
{
    load=true;
    quint32 temp = ff7->slot[s].materias[row].ap[0] |(ff7->slot[s].materias[row].ap[1] << 8) | (ff7->slot[s].materias[row].ap[2] << 16);
    ui->sb_addap->setValue(temp);// no one cares cause there is no ap really..
    on_btn_eskillclear_clicked();
    for (int i=0;i<24;i++)
    {
        ui->list_eskill->setCurrentRow(i);
        if ((1 << i) & temp){ui->list_eskill->currentItem()->setCheckState(Qt::Checked);}
    }
    ui->list_eskill->setCurrentRow(-1);
    load=false;
}

void MainWindow::on_list_eskill_itemChanged()
{if(!load){file_changed=true;
    quint32 temp = ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[0] |(ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[1] << 8) | (ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[2] << 16);
    if(ui->list_eskill->currentItem()->checkState()){temp |= (1 << ui->list_eskill->currentRow());}
    else{temp &= ~(1<<ui->list_eskill->currentRow());}
    load=true;
    ui->sb_addap->setValue(temp);
    load=false;
    int a = (temp & 0xff);
    int b = (temp & 0xff00) >> 8;
    int c = (temp & 0xff0000) >> 16;
    ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[0] = a;
    ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[1] = b;
    ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[2] = c;
}}

void MainWindow::on_btn_eskillclear_clicked()
{
    for (int i=0;i<24;i++)
    {
        ui->list_eskill->setCurrentRow(i);
        ui->list_eskill->currentItem()->setCheckState(Qt::Unchecked);
    }//loop thru and uncheck no need to apply each one should thrown an itemChanged() event
    ui->list_eskill->setCurrentRow(-1);
}

void MainWindow::on_btn_add_all_materia_clicked()
{
    int j = ui->tbl_materia->currentRow();
    for(int i=117;i<200;i++)
    {//place one of each at lowest possible point
        ui->tbl_materia->setCurrentCell(i,0);
        //starting w/ magic (every first materia needs to be manually set) then support, command,indpendent , summon. fill the table w/ materia.
        if(i==117){ff7->slot[s].materias[i].id = 0x31; ff7->slot[s].materias[i].ap[0]=0xFF;ff7->slot[s].materias[i].ap[1]=0xFF;ff7->slot[s].materias[i].ap[2]=0xFF;}
        else if(i>117 && i<139)
        {
            ui->combo_mat_type->setCurrentIndex(1);
            ui->combo_add_mat_2->setCurrentIndex(i-117);
            ui->sb_addap->setValue(ui->sb_addap->maximum());
        }
        else if (i==139){ff7->slot[s].materias[i].id = 0x17; ff7->slot[s].materias[i].ap[0]=0xFF;ff7->slot[s].materias[i].ap[1]=0xFF;ff7->slot[s].materias[i].ap[2]=0xFF;}
        else if (i>139 && i<152)
        {
            ui->combo_mat_type->setCurrentIndex(4);
            ui->combo_add_mat_2->setCurrentIndex(i-139);
            ui->sb_addap->setValue(ui->sb_addap->maximum());
        }
        else if (i==152){ff7->slot[s].materias[i].id = 0x0E; ff7->slot[s].materias[i].ap[0]=0xFF;ff7->slot[s].materias[i].ap[1]=0xFF;ff7->slot[s].materias[i].ap[2]=0xFF;}
        else if (i>152 && i<166)
        {
            ui->combo_mat_type->setCurrentIndex(5);
            ui->combo_add_mat_2->setCurrentIndex(i-152);
            ui->sb_addap->setValue(ui->sb_addap->maximum());
        }
        else if (i==166){ff7->slot[s].materias[i].id = 0x00; ff7->slot[s].materias[i].ap[0]=0xFF;ff7->slot[s].materias[i].ap[1]=0xFF;ff7->slot[s].materias[i].ap[2]=0xFF;}
        else if (i>166 && i<183)
        {
            ui->combo_mat_type->setCurrentIndex(3);
            ui->combo_add_mat_2->setCurrentIndex(i-166);
            ui->sb_addap->setValue(ui->sb_addap->maximum());
        }
        else if (i==183){ff7->slot[s].materias[i].id = 0x4A; ff7->slot[s].materias[i].ap[0]=0xFF;ff7->slot[s].materias[i].ap[1]=0xFF;ff7->slot[s].materias[i].ap[2]=0xFF;}
        else if (i>183 && i<200)
        {
            ui->combo_mat_type->setCurrentIndex(2);
            ui->combo_add_mat_2->setCurrentIndex(i-183);
            ui->sb_addap->setValue(ui->sb_addap->maximum());
        }
    }
    ui->tbl_materia->setCurrentCell(j,0);
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
void MainWindow::on_sb_map_id_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].mapid= value;}}
void MainWindow::on_sb_loc_id_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].locationid = value;}}
void MainWindow::on_sb_coordx_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].coord.x = value;}}
void MainWindow::on_sb_coordy_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].coord.y = value;}}
void MainWindow::on_sb_coordz_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].coord.z = value;}}

void MainWindow::on_line_location_textChanged(QString text)
{if (!load){file_changed=true;
    for (int i=0;i<24;i++){ff7->slot[s].location[i] =0xFF;}
    QByteArray temp = Text.toFF7(text);
    memcpy(ff7->slot[s].location,temp,temp.length());
    //and the description.
    for (int i=0;i<32;i++){ff7->slot[s].desc.location[i] =0xFF;}
    memcpy(ff7->slot[s].desc.location,temp,temp.length());
}}

/*~~~~~~~~~~~~~~~~~~~~~~~~CHARACTER TAB~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_cb_id_toggled(bool checked)
{if(!load){file_changed=true;
    if (curchar ==6)
    {
        if (checked){ff7->slot[s].chars[6].id = 9;}
        else {ff7->slot[s].chars[6].id = 6;}
        charupdate();
    }
    if (curchar ==7)
    {
        if (checked){ff7->slot[s].chars[7].id = 10;}
        else {ff7->slot[s].chars[7].id = 7;}
        charupdate();
    }
}}

void MainWindow::on_line_name_textChanged(QString text)
{if(!load){file_changed=true;
    for (int i=0;i<12;i++){ff7->slot[s].chars[curchar].name[i] =0xFF;}
    QByteArray temp = Text.toFF7(text);
    memcpy(ff7->slot[s].chars[curchar].name,temp,temp.length());
    if (curchar == ui->combo_party1->currentIndex())
    {
        for (int i=0;i<16;i++){ff7->slot[s].desc.name[i] =0xFF;}
        memcpy(ff7->slot[s].desc.name,temp,temp.length());
    }
}}

void MainWindow::on_sb_lvl_valueChanged(int value)
{if(!load){file_changed=true;
    if(settings->value("autochargrowth").toBool()){setchar_growth(2);}
    //Basic lv change
    else{
        ff7->slot[s].chars[curchar].level = value;
        if(curchar==ff7->slot[s].party[0]){ff7->slot[s].desc.level = value;}
    }
}}

void MainWindow::on_sb_exp_valueChanged()
{if(!load){file_changed=true;
    ff7->slot[s].chars[curchar].exp = ui->sb_exp->value();
    if(settings->value("autochargrowth").toBool()){setchar_growth(1);}
}}

void MainWindow::on_sb_curhp_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].curHP = ui->sb_curhp->value();}}
void MainWindow::on_sb_curmp_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].curMP = ui->sb_curmp->value();}}
void MainWindow::on_sb_maxhp_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].maxHP =ui->sb_maxhp->value();}}
void MainWindow::on_sb_maxmp_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].maxMP =ui->sb_maxmp->value();}}
void MainWindow::on_sb_hp_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].baseHP = ui->sb_hp->value(); update_stat_totals();}}
void MainWindow::on_sb_mp_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].baseMP = ui->sb_mp->value(); update_stat_totals();}}
void MainWindow::on_sb_kills_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].kills = ui->sb_kills->value();}}
void MainWindow::on_sb_str_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].strength = ui->sb_str->value(); update_stat_totals();}}
void MainWindow::on_sb_dex_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].dexterity = ui->sb_dex->value();update_stat_totals();}}
void MainWindow::on_sb_mag_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].magic = ui->sb_mag->value();update_stat_totals();}}
void MainWindow::on_sb_vit_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].vitality = ui->sb_vit->value();update_stat_totals();}}
void MainWindow::on_sb_spi_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].spirit = ui->sb_spi->value();update_stat_totals();}}
void MainWindow::on_sb_lck_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].luck = ui->sb_lck->value();update_stat_totals();}}
void MainWindow::on_sb_strbonus_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].strength_bonus = ui->sb_strbonus->value();update_stat_totals();}}
void MainWindow::on_sb_dexbonus_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].dexterity_bonus = ui->sb_dexbonus->value();update_stat_totals();}}
void MainWindow::on_sb_magbonus_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].magic_bonus = ui->sb_magbonus->value();update_stat_totals();}}
void MainWindow::on_sb_vitbonus_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].vitality_bonus = ui->sb_vitbonus->value();update_stat_totals();}}
void MainWindow::on_sb_spibonus_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].spirit_bonus = ui->sb_spibonus->value();update_stat_totals();}}
void MainWindow::on_sb_lckbonus_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].luck_bonus = ui->sb_lckbonus->value();update_stat_totals();}}

void MainWindow::on_cb_front_clicked(bool checked)
{if(!load){file_changed=true;
    if(checked) ff7->slot[s].chars[curchar].flags[1] = 255;
    if(!checked)ff7->slot[s].chars[curchar].flags[1] =254;
}}

void MainWindow::on_cb_fury_clicked(bool checked)
{if(!load){file_changed=true;
    if(checked){ui->cb_sadness->setChecked(0); ff7->slot[s].chars[curchar].flags[0] =32;}
    else {ff7->slot[s].chars[curchar].flags[0]=0;}
}}

void MainWindow::on_cb_sadness_clicked(bool checked)
{if(!load){file_changed=true;
    if(checked){ui->cb_fury->setChecked(0); ff7->slot[s].chars[curchar].flags[0] =16;}
    else {ff7->slot[s].chars[curchar].flags[0]=0;}
}}

//char limit stuff
void MainWindow::on_sb_used1_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].timesused1 = ui->sb_used1->value();}}
void MainWindow::on_sb_used2_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].timesused2 = ui->sb_used2->value();}}
void MainWindow::on_sb_used3_valueChanged(){if(!load){file_changed=true; ff7->slot[s].chars[curchar].timesused3 = ui->sb_used3->value();}}
void MainWindow::on_sb_limitlvl_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chars[curchar].limitlevel= value;}}
void MainWindow::on_slide_limit_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].chars[curchar].limitbar = value;}}

void MainWindow::limitapply()
{
    ff7->slot[s].chars[curchar].limits = 0;
    if (curchar == 7)
    {
        if (ui->limit_1a->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<0);
        if (ui->limit_2a->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<3);
        if (ui->limit_3a->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<6);
        if (ui->limit_4 ->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<9);
    }
    else if (curchar == 6)
    {
        if (ui->limit_1a->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<0);
        if (ui->limit_2a->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<3);
    }
    else
    {
        if (ui->limit_1a->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<0);
        if (ui->limit_1b->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<1);
        if (ui->limit_2a->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<3);
        if (ui->limit_2b->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<4);
        if (ui->limit_3a->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<6);
        if (ui->limit_3b->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<7);
        if (ui->limit_4 ->isChecked()==1) ff7->slot[s].chars[curchar].limits |= (1<<9);
    }
}

void MainWindow::on_limit_1a_toggled(){if(!load) {limitapply();}}
void MainWindow::on_limit_1b_toggled(){if(!load) {limitapply();}}
void MainWindow::on_limit_2a_toggled(){if(!load) {limitapply();}}
void MainWindow::on_limit_2b_toggled(){if(!load) {limitapply();}}
void MainWindow::on_limit_3a_toggled(){if(!load) {limitapply();}}
void MainWindow::on_limit_3b_toggled(){if(!load) {limitapply();}}
void MainWindow::on_limit_4_toggled(){if(!load) {limitapply();}}

//Char Equiptment Tab

void MainWindow::on_combo_armor_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].chars[curchar].armor = index;    setarmorslots(); update_stat_totals();weapon_stat();}}
void MainWindow::on_combo_weapon_currentIndexChanged(){setweaponslots();update_stat_totals();weapon_stat();} //no matter what we need to update materia slots.
void MainWindow::on_combo_acc_currentIndexChanged(int index){if(!load){file_changed=true; if(index==32){index=0xFF;} ff7->slot[s].chars[curchar].accessory = index;update_stat_totals();weapon_stat();}}

void MainWindow::on_combo_weapon_activated(int index)
{if(!load){file_changed=true;
    switch(curchar)
    {
        case 0:{ff7->slot[s].chars[curchar].weapon = index;break;}
        case 1:{ff7->slot[s].chars[curchar].weapon = index+32;break;}
        case 2:{ff7->slot[s].chars[curchar].weapon = index+16;break;}
        case 3:{ff7->slot[s].chars[curchar].weapon = index+62;break;}
        case 4:{ff7->slot[s].chars[curchar].weapon = index+48;break;}
        case 5:{ff7->slot[s].chars[curchar].weapon = index+87;break;}
        case 6:{ff7->slot[s].chars[curchar].weapon = index+101;break;}
        case 7:{ff7->slot[s].chars[curchar].weapon = index+114;break;}
        case 8:{ff7->slot[s].chars[curchar].weapon = index+73;break;}
    }
}}

void MainWindow::on_sb_addap_slot_valueChanged(int value)
{if(!load){file_changed=true;
    if(value == Materias[ui->combo_add_mat_slot->currentIndex()].ap[Materias[ui->combo_add_mat_slot->currentIndex()].levels -2] && Materias[ui->combo_add_mat_slot->currentIndex()].levels >1)
    {
        for(int i=0;i<3;i++){ff7->slot[s].chars[curchar].materias[mslotsel].ap[i] = 0xFF;}
    }
    else
    {
        int a = (value & 0xff);
        int b = (value & 0xff00) >> 8;
        int c = (value & 0xff0000) >> 16;
        ff7->slot[s].chars[curchar].materias[mslotsel].ap[0] = a;
        ff7->slot[s].chars[curchar].materias[mslotsel].ap[1] = b;
        ff7->slot[s].chars[curchar].materias[mslotsel].ap[2] = c;
    }
    materiaupdate_slot();
}}

void MainWindow::on_clearMateria_slot_clicked()
{
    ui->combo_mat_type_slot->setCurrentIndex(0);
    ui->combo_add_mat_slot->setCurrentIndex(0);
    ff7->slot[s].chars[curchar].materias[mslotsel].id = 0xFF;
    ui->sb_addap_slot->setValue(0xFFFFFF);
    if(!load){file_changed=true; }
    materiaupdate_slot();
}

void MainWindow::on_combo_mat_type_slot_currentIndexChanged(int index)
{
    load=true;
    ui->combo_add_mat_slot_2->clear();
    if(index == 0)
    {
        for(int i=0;i<0x5B;i++)
        {
            if(FF7Strings.MateriaNames(i) !=tr("DON'T USE")){ui->combo_add_mat_slot_2->addItem(QIcon(Materias[i].image),FF7Strings.MateriaNames(i));}
        }
    }
    else{for(int i=0;i<0x5B;i++){if(index==Materias[i].type){ui->combo_add_mat_slot_2->addItem(QIcon(Materias[i].image),FF7Strings.MateriaNames(i));}}}
    load=false;
}
void MainWindow::on_combo_add_mat_slot_currentIndexChanged(int index)
{
    if(ui->combo_add_mat_slot->currentText() ==tr("DON'T USE"))// this is a placeholder materia
    {
        QMessageBox::information(this,tr("Empty Materia"),tr("Place holder Materia Detected\n Remember 16777215 AP = master"));
        guirefresh(0);// clean up the gui.
        return; //we are done here.
    }
    if(!load)
    {
        file_changed=true;
        ff7->slot[s].chars[curchar].materias[mslotsel].id = Materias[index].id;
    }
    ui->combo_mat_type_slot->setCurrentIndex(Materias[index].type);
    for(int i=0;i<ui->combo_add_mat_slot_2->count();i++)
    {
        if(ui->combo_add_mat_slot_2->itemText(i)==FF7Strings.MateriaNames(index)){ui->combo_add_mat_slot_2->setCurrentIndex(i);}
    }
    materiaupdate_slot();
}

void MainWindow::on_combo_add_mat_slot_2_currentIndexChanged()
{if(!load){//set combo_add_mat.setCurrentindex = selected materia.id
    for(int i=0;i<0x5B;i++)
    {
        if(ui->combo_add_mat_slot_2->currentText()== FF7Strings.MateriaNames(i)){ui->combo_add_mat_slot->setCurrentIndex(i);}
    }

    if(ff7->slot[s].chars[curchar].materias[mslotsel].id == 0x2C)
    {
        ui->mskill_group->setVisible(false);
        ui->eskill_group_2->setVisible(true);
        geteskills2(mslotsel);
        ui->sb_addap_slot->setEnabled(false);
    }
    else
    {
        ui->mskill_group->setVisible(true);
        ui->eskill_group_2->setVisible(false);
        ui->sb_addap_slot->setEnabled(true);
    }
}}
void MainWindow::on_btn_copy_materia_slot_clicked()
{
    buffer_materia.id = ff7->slot[s].chars[curchar].materias[mslotsel].id;
    buffer_materia.ap[0] = ff7->slot[s].chars[curchar].materias[mslotsel].ap[0];
    buffer_materia.ap[1] = ff7->slot[s].chars[curchar].materias[mslotsel].ap[1];
    buffer_materia.ap[2] = ff7->slot[s].chars[curchar].materias[mslotsel].ap[2];
}

void MainWindow::on_btn_paste_materia_slot_clicked()
{
    ff7->slot[s].chars[curchar].materias[mslotsel].id = buffer_materia.id;
    ff7->slot[s].chars[curchar].materias[mslotsel].ap[0]= buffer_materia.ap[0];
    ff7->slot[s].chars[curchar].materias[mslotsel].ap[1]= buffer_materia.ap[1];
    ff7->slot[s].chars[curchar].materias[mslotsel].ap[2]= buffer_materia.ap[2];
    if(!load){file_changed=true; }
    materiaupdate_slot();
}

void MainWindow::on_w_m_s1_clicked(){mslotsel=0;    if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_w_m_s2_clicked(){mslotsel=1;    if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_w_m_s3_clicked(){mslotsel=2;    if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_w_m_s4_clicked(){mslotsel=3;    if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_w_m_s5_clicked(){mslotsel=4;    if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_w_m_s6_clicked(){mslotsel=5;    if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_w_m_s7_clicked(){mslotsel=6;    if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_w_m_s8_clicked(){mslotsel=7;    if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_a_m_s1_clicked(){mslotsel=8;    if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_a_m_s2_clicked(){mslotsel=9;    if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_a_m_s3_clicked(){mslotsel=10;   if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_a_m_s4_clicked(){mslotsel=11;   if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_a_m_s5_clicked(){mslotsel=12;   if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_a_m_s6_clicked(){mslotsel=13;   if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_a_m_s7_clicked(){mslotsel=14;   if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_a_m_s8_clicked(){mslotsel=15;   if(ff7->slot[s].chars[curchar].materias[mslotsel].id != 0xff){load=true;ui->combo_add_mat_slot->setCurrentIndex(ff7->slot[s].chars[curchar].materias[mslotsel].id);}  materiaupdate_slot();}
void MainWindow::on_btn_m_lvl1_slot_clicked(){ui->sb_addap_slot->setValue(0);    materiaupdate_slot();}
void MainWindow::on_btn_m_lvl2_slot_clicked(){ui->sb_addap_slot->setValue(Materias[ui->combo_add_mat_slot->currentIndex()].ap[0]);    materiaupdate_slot();}
void MainWindow::on_btn_m_lvl3_slot_clicked(){ui->sb_addap_slot->setValue(Materias[ui->combo_add_mat_slot->currentIndex()].ap[1]);    materiaupdate_slot();}
void MainWindow::on_btn_m_lvl4_slot_clicked(){ui->sb_addap_slot->setValue(Materias[ui->combo_add_mat_slot->currentIndex()].ap[2]);    materiaupdate_slot();}
void MainWindow::on_btn_m_lvl5_slot_clicked(){ui->sb_addap_slot->setValue(Materias[ui->combo_add_mat_slot->currentIndex()].ap[3]);    materiaupdate_slot();}

void MainWindow::geteskills2(int row)
{
    load=true;
    quint32 temp = ff7->slot[s].chars[curchar].materias[row].ap[0] |(ff7->slot[s].chars[curchar].materias[row].ap[1] << 8) | (ff7->slot[s].chars[curchar].materias[row].ap[2] << 16);
    ui->sb_addap_slot->setValue(temp);
    for (int i=0;i<24;i++)
    {
        ui->list_eskill_2->setCurrentRow(i);
        if ((1 << i) & temp){ui->list_eskill_2->currentItem()->setCheckState(Qt::Checked);}
        else{ui->list_eskill_2->currentItem()->setCheckState(Qt::Unchecked);}
    }
    ui->list_eskill_2->setCurrentRow(-1);
    load=false;
}
void MainWindow::on_list_eskill_2_itemChanged()
{if(!load){file_changed=true;
    quint32 temp = ff7->slot[s].chars[curchar].materias[mslotsel].ap[0] |(ff7->slot[s].chars[curchar].materias[mslotsel].ap[1] << 8) | (ff7->slot[s].chars[curchar].materias[mslotsel].ap[2] << 16);
    if(ui->list_eskill_2->currentItem()->checkState()){temp |= (1 << ui->list_eskill_2->currentRow());}
    else{temp &= ~(1<<ui->list_eskill_2->currentRow());}
    int a = (temp & 0xff);
    int b = (temp & 0xff00) >> 8;
    int c = (temp & 0xff0000) >> 16;
    ff7->slot[s].chars[curchar].materias[mslotsel].ap[0] = a;
    ff7->slot[s].chars[curchar].materias[mslotsel].ap[1] = b;
    ff7->slot[s].chars[curchar].materias[mslotsel].ap[2] = c;
    load=true;
    ui->sb_addap_slot->setValue(temp);
    load=false;
}}

/*~~~~~~~~~~~~~~~~~~~ Game Options~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_slide_ul_r_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[0][0] = value;}

    QString g_style = "QSlider#slide_ul_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ul_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_ul_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ul_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_ul_b->value()));   g_style.append(",255));}");

    QString b_style =  "QSlider#slide_ul_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ul_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ul_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ul_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ul_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_ul_g->setStyleSheet(g_style);
    ui->slide_ul_b->setStyleSheet(b_style);
    setPreviewColors();
}
void MainWindow::on_slide_ul_g_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[0][1] = value;}

    QString r_style = "QSlider#slide_ul_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_b->value()));   r_style.append(",255));}");

    QString b_style =  "QSlider#slide_ul_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ul_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ul_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ul_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ul_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_ul_r->setStyleSheet(r_style);
    ui->slide_ul_b->setStyleSheet(b_style);
    setPreviewColors();
}
void MainWindow::on_slide_ul_b_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[0][2] = value;}

    QString r_style = "QSlider#slide_ul_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_b->value()));   r_style.append(",255));}");

    QString g_style = "QSlider#slide_ul_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ul_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_ul_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ul_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_ul_b->value()));   g_style.append(",255));}");

    ui->slide_ul_r->setStyleSheet(r_style);
    ui->slide_ul_g->setStyleSheet(g_style);
    setPreviewColors();
}

void MainWindow::on_slide_ur_r_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[1][0] = value;}
    QString g_style = "QSlider#slide_ur_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ur_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_ur_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ur_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_ur_b->value()));   g_style.append(",255));}");

    QString b_style =  "QSlider#slide_ur_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ur_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ur_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ur_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ur_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_ur_g->setStyleSheet(g_style);
    ui->slide_ur_b->setStyleSheet(b_style);
    setPreviewColors();
}
void MainWindow::on_slide_ur_g_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[1][1] = value;}
    QString r_style = "QSlider#slide_ur_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_b->value()));   r_style.append(",255));}");

    QString b_style =  "QSlider#slide_ur_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ur_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ur_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ur_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ur_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_ur_r->setStyleSheet(r_style);
    ui->slide_ur_b->setStyleSheet(b_style);
    setPreviewColors();
}
void MainWindow::on_slide_ur_b_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[1][2] = value;}
    QString r_style = "QSlider#slide_ur_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_b->value()));   r_style.append(",255));}");

    QString g_style = "QSlider#slide_ur_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ur_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_ur_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ur_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_ur_b->value()));   g_style.append(",255));}");

    ui->slide_ur_r->setStyleSheet(r_style);
    ui->slide_ur_g->setStyleSheet(g_style);
    setPreviewColors();
}

void MainWindow::on_slide_ll_r_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[2][0] = value;}
    QString g_style = "QSlider#slide_ll_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ll_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_ll_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ll_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_ll_b->value()));   g_style.append(",255));}");

    QString b_style =  "QSlider#slide_ll_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ll_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ll_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ll_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ll_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_ll_g->setStyleSheet(g_style);
    ui->slide_ll_b->setStyleSheet(b_style);
    setPreviewColors();
}
void MainWindow::on_slide_ll_g_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[2][1] = value;}
    QString r_style = "QSlider#slide_ll_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_b->value()));   r_style.append(",255));}");

    QString b_style =  "QSlider#slide_ll_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ll_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ll_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ll_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_ll_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_ll_r->setStyleSheet(r_style);
    ui->slide_ll_b->setStyleSheet(b_style);
    setPreviewColors();
}
void MainWindow::on_slide_ll_b_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[2][2] = value;}
    QString r_style = "QSlider#slide_ll_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_b->value()));   r_style.append(",255));}");

    QString g_style = "QSlider#slide_ll_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ll_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_ll_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ll_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_ll_b->value()));   g_style.append(",255));}");

    ui->slide_ll_r->setStyleSheet(r_style);
    ui->slide_ll_g->setStyleSheet(g_style);
    setPreviewColors();
}

void MainWindow::on_slide_lr_r_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[3][0] = value;}
    QString g_style = "QSlider#slide_lr_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_lr_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_lr_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_lr_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_lr_b->value()));   g_style.append(",255));}");

    QString b_style =  "QSlider#slide_lr_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_lr_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_lr_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_lr_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_lr_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_lr_g->setStyleSheet(g_style);
    ui->slide_lr_b->setStyleSheet(b_style);
    setPreviewColors();

}
void MainWindow::on_slide_lr_g_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[3][1] = value;}
    QString r_style = "QSlider#slide_lr_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_b->value()));   r_style.append(",255));}");

    QString b_style =  "QSlider#slide_lr_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_lr_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_lr_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_lr_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_lr_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_lr_r->setStyleSheet(r_style);
    ui->slide_lr_b->setStyleSheet(b_style);
    setPreviewColors();
}
void MainWindow::on_slide_lr_b_valueChanged(int value)
{
    if(!load){file_changed=true; ff7->slot[s].colors[3][2] = value;}
    QString r_style = "QSlider#slide_lr_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_b->value()));   r_style.append(",255));}");

    QString g_style = "QSlider#slide_lr_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_lr_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_lr_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_lr_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_lr_b->value()));   g_style.append(",255));}");

    ui->slide_lr_r->setStyleSheet(r_style);
    ui->slide_lr_g->setStyleSheet(g_style);
    setPreviewColors();
}

/*end of color sliders*/

void MainWindow::on_slide_battlespeed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].battlespeed = value;}}
void MainWindow::on_slide_battlemspeed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].battlemspeed = value;}}
void MainWindow::on_slide_fieldmspeed_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].fieldmspeed = value;}}
void MainWindow::on_combo_control_currentIndexChanged(){if(!load){file_changed=true; setoptions_one();}}
void MainWindow::on_combo_sound_currentIndexChanged(){if(!load){file_changed=true; setoptions_one();}}
void MainWindow::on_combo_cursor_currentIndexChanged(){if(!load){file_changed=true; setoptions_one();}}
void MainWindow::on_combo_atb_currentIndexChanged(){if(!load){file_changed=true; setoptions_one();}}
void MainWindow::on_combo_camera_currentIndexChanged(){if(!load){file_changed=true; setoptions_two();}}
void MainWindow::on_combo_magic_order_currentIndexChanged(){if(!load){file_changed=true; setoptions_two();}}
void MainWindow::on_cb_battle_help_toggled(){if(!load){file_changed=true; setoptions_two();}}

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
void MainWindow::on_sb_curdisc_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].disc = value;}}
void MainWindow::on_sb_mprogress_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].mprogress = value;}}
void MainWindow::on_sb_turkschruch_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].aeris_chruch=value;}}
void MainWindow::on_sb_donprog_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].donprogress=value;}}

void MainWindow::on_cb_bm1_1_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress1 |= (1<<0);}else{ff7->slot[s].bm_progress1 &= ~(1<<0);}}}
void MainWindow::on_cb_bm1_2_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress1 |= (1<<1);}else{ff7->slot[s].bm_progress1 &= ~(1<<1);}}}
void MainWindow::on_cb_bm1_3_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress1 |= (1<<2);}else{ff7->slot[s].bm_progress1 &= ~(1<<2);}}}
void MainWindow::on_cb_bm1_4_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress1 |= (1<<3);}else{ff7->slot[s].bm_progress1 &= ~(1<<3);}}}
void MainWindow::on_cb_bm1_5_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress1 |= (1<<4);}else{ff7->slot[s].bm_progress1 &= ~(1<<4);}}}
void MainWindow::on_cb_bm1_6_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress1 |= (1<<5);}else{ff7->slot[s].bm_progress1 &= ~(1<<5);}}}
void MainWindow::on_cb_bm1_7_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress1 |= (1<<6);}else{ff7->slot[s].bm_progress1 &= ~(1<<6);}}}
void MainWindow::on_cb_bm1_8_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress1 |= (1<<7);}else{ff7->slot[s].bm_progress1 &= ~(1<<7);}}}

void MainWindow::on_cb_bm2_1_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress2 |= (1<<0);}else{ff7->slot[s].bm_progress2 &= ~(1<<0);}}}
void MainWindow::on_cb_bm2_2_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress2 |= (1<<1);}else{ff7->slot[s].bm_progress2 &= ~(1<<1);}}}
void MainWindow::on_cb_bm2_3_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress2 |= (1<<2);}else{ff7->slot[s].bm_progress2 &= ~(1<<2);}}}
void MainWindow::on_cb_bm2_4_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress2 |= (1<<3);}else{ff7->slot[s].bm_progress2 &= ~(1<<3);}}}
void MainWindow::on_cb_bm2_5_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress2 |= (1<<4);}else{ff7->slot[s].bm_progress2 &= ~(1<<4);}}}
void MainWindow::on_cb_bm2_6_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress2 |= (1<<5);}else{ff7->slot[s].bm_progress2 &= ~(1<<5);}}}
void MainWindow::on_cb_bm2_7_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress2 |= (1<<6);}else{ff7->slot[s].bm_progress2 &= ~(1<<6);}}}
void MainWindow::on_cb_bm2_8_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress2 |= (1<<7);}else{ff7->slot[s].bm_progress2 &= ~(1<<7);}}}

void MainWindow::on_cb_bm3_1_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress3 |= (1<<0);}else{ff7->slot[s].bm_progress3 &= ~(1<<0);}}}
void MainWindow::on_cb_bm3_2_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress3 |= (1<<1);}else{ff7->slot[s].bm_progress3 &= ~(1<<1);}}}
void MainWindow::on_cb_bm3_3_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress3 |= (1<<2);}else{ff7->slot[s].bm_progress3 &= ~(1<<2);}}}
void MainWindow::on_cb_bm3_4_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress3 |= (1<<3);}else{ff7->slot[s].bm_progress3 &= ~(1<<3);}}}
void MainWindow::on_cb_bm3_5_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress3 |= (1<<4);}else{ff7->slot[s].bm_progress3 &= ~(1<<4);}}}
void MainWindow::on_cb_bm3_6_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress3 |= (1<<5);}else{ff7->slot[s].bm_progress3 &= ~(1<<5);}}}
void MainWindow::on_cb_bm3_7_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress3 |= (1<<6);}else{ff7->slot[s].bm_progress3 &= ~(1<<6);}}}
void MainWindow::on_cb_bm3_8_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].bm_progress3 |= (1<<7);}else{ff7->slot[s].bm_progress3 &= ~(1<<7);}}}

void MainWindow::on_cb_s7pl_1_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[0] |= (1<<0);}else{ff7->slot[s].z_26[0] &= ~(1<<0);}}}
void MainWindow::on_cb_s7pl_2_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[0] |= (1<<1);}else{ff7->slot[s].z_26[0] &= ~(1<<1);}}}
void MainWindow::on_cb_s7pl_3_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[0] |= (1<<2);}else{ff7->slot[s].z_26[0] &= ~(1<<2);}}}
void MainWindow::on_cb_s7pl_4_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[0] |= (1<<3);}else{ff7->slot[s].z_26[0] &= ~(1<<3);}}}
void MainWindow::on_cb_s7pl_5_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[0] |= (1<<4);}else{ff7->slot[s].z_26[0] &= ~(1<<4);}}}
void MainWindow::on_cb_s7pl_6_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[0] |= (1<<5);}else{ff7->slot[s].z_26[0] &= ~(1<<5);}}}
void MainWindow::on_cb_s7pl_7_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[0] |= (1<<6);}else{ff7->slot[s].z_26[0] &= ~(1<<6);}}}
void MainWindow::on_cb_s7pl_8_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[0] |= (1<<7);}else{ff7->slot[s].z_26[0] &= ~(1<<7);}}}

void MainWindow::on_cb_s7ts_1_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[8] |= (1<<0);}else{ff7->slot[s].z_26[8] &= ~(1<<0);}}}
void MainWindow::on_cb_s7ts_2_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[8] |= (1<<1);}else{ff7->slot[s].z_26[8] &= ~(1<<1);}}}
void MainWindow::on_cb_s7ts_3_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[8] |= (1<<2);}else{ff7->slot[s].z_26[8] &= ~(1<<2);}}}
void MainWindow::on_cb_s7ts_4_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[8] |= (1<<3);}else{ff7->slot[s].z_26[8] &= ~(1<<3);}}}
void MainWindow::on_cb_s7ts_5_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[8] |= (1<<4);}else{ff7->slot[s].z_26[8] &= ~(1<<4);}}}
void MainWindow::on_cb_s7ts_6_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[8] |= (1<<5);}else{ff7->slot[s].z_26[8] &= ~(1<<5);}}}
void MainWindow::on_cb_s7ts_7_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[8] |= (1<<6);}else{ff7->slot[s].z_26[8] &= ~(1<<6);}}}
void MainWindow::on_cb_s7ts_8_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_26[8] |= (1<<7);}else{ff7->slot[s].z_26[8] &= ~(1<<7);}}}

void MainWindow::on_cb_s5_1_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_23[26] |= (1<<0);}else{ff7->slot[s].z_23[26] &= ~(1<<0);}}}
void MainWindow::on_cb_s5_2_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_23[26] |= (1<<1);}else{ff7->slot[s].z_23[26] &= ~(1<<1);}}}
void MainWindow::on_cb_s5_3_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_23[26] |= (1<<2);}else{ff7->slot[s].z_23[26] &= ~(1<<2);}}}
void MainWindow::on_cb_s5_4_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_23[26] |= (1<<3);}else{ff7->slot[s].z_23[26] &= ~(1<<3);}}}
void MainWindow::on_cb_s5_5_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_23[26] |= (1<<4);}else{ff7->slot[s].z_23[26] &= ~(1<<4);}}}
void MainWindow::on_cb_s5_6_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_23[26] |= (1<<5);}else{ff7->slot[s].z_23[26] &= ~(1<<5);}}}
void MainWindow::on_cb_s5_7_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_23[26] |= (1<<6);}else{ff7->slot[s].z_23[26] &= ~(1<<6);}}}
void MainWindow::on_cb_s5_8_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].z_23[26] |= (1<<7);}else{ff7->slot[s].z_23[26] &= ~(1<<7);}}}

void MainWindow::on_cb_bombing_int_stateChanged(int checked)
{if(!load){file_changed=true;
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
// set up young cloud
        ff7->slot[s].chars[6].id=9;
        for(int i=0;i<12;i++){ff7->slot[s].chars[6].name[i] = ff7->slot[s].chars[0].name[i];}
        ff7->slot[s].chars[6].level =ff7->slot[s].chars[0].level;
        ff7->slot[s].chars[6].armor=ff7->slot[s].chars[0].armor;
        ff7->slot[s].chars[6].accessory=ff7->slot[s].chars[0].accessory;
        ff7->slot[s].chars[6].weapon= ff7->slot[s].chars[0].weapon;
        ff7->slot[s].chars[6].baseHP=ff7->slot[s].chars[0].baseHP;
        ff7->slot[s].chars[6].baseMP=ff7->slot[s].chars[0].baseMP;
        ff7->slot[s].chars[6].exp=ff7->slot[s].chars[0].exp;
        ff7->slot[s].chars[6].expNext=ff7->slot[s].chars[0].expNext;
        ff7->slot[s].chars[6].curHP=ff7->slot[s].chars[0].curHP;
        ff7->slot[s].chars[6].maxHP=ff7->slot[s].chars[0].maxHP;
        ff7->slot[s].chars[6].curMP=ff7->slot[s].chars[0].curMP;
        ff7->slot[s].chars[6].maxMP=ff7->slot[s].chars[0].maxMP;
        ff7->slot[s].chars[6].dexterity=ff7->slot[s].chars[0].dexterity;
        ff7->slot[s].chars[6].dexterity_bonus=ff7->slot[s].chars[0].dexterity_bonus;
        ff7->slot[s].chars[6].strength=ff7->slot[s].chars[0].strength;
        ff7->slot[s].chars[6].strength_bonus=ff7->slot[s].chars[0].strength_bonus;
        ff7->slot[s].chars[6].magic=ff7->slot[s].chars[0].magic;
        ff7->slot[s].chars[6].magic_bonus=ff7->slot[s].chars[0].magic_bonus;
        ff7->slot[s].chars[6].spirit=ff7->slot[s].chars[0].spirit;
        ff7->slot[s].chars[6].spirit_bonus=ff7->slot[s].chars[0].spirit_bonus;
        ff7->slot[s].chars[6].vitality= ff7->slot[s].chars[0].vitality;
        ff7->slot[s].chars[6].vitality_bonus= ff7->slot[s].chars[0].vitality_bonus;
        ff7->slot[s].chars[6].luck= ff7->slot[s].chars[0].luck;
        ff7->slot[s].chars[6].luck_bonus= ff7->slot[s].chars[0].luck_bonus;
        ff7->slot[s].chars[6].flags[0]= ff7->slot[s].chars[0].flags[0];
        ff7->slot[s].chars[6].flags[1]= ff7->slot[s].chars[0].flags[1];
        ff7->slot[s].chars[6].flags[2]= ff7->slot[s].chars[0].flags[2];
        ff7->slot[s].chars[6].kills=ff7->slot[s].chars[0].kills;
        ff7->slot[s].chars[6].limitbar= ff7->slot[s].chars[0].limitbar;
        ff7->slot[s].chars[6].limitlevel= ff7->slot[s].chars[0].limitlevel;
        ff7->slot[s].chars[6].limits= ff7->slot[s].chars[0].limits;
        for (int i=0;i<16;i++)
        {
            ff7->slot[s].chars[6].materias[i].id = ff7->slot[s].chars[0].materias[i].id;
            for (int j=0;j<3;j++){ff7->slot[s].chars[6].materias[i].ap[j]=ff7->slot[s].chars[0].materias[i].ap[j];}
        }
        ff7->slot[s].chars[6].timesused1 = ff7->slot[s].chars[0].timesused1;
        ff7->slot[s].chars[6].timesused2 = ff7->slot[s].chars[0].timesused2;
        ff7->slot[s].chars[6].timesused3 = ff7->slot[s].chars[0].timesused3;
        for(int i=0;i<4;i++){ff7->slot[s].chars[6].z_4[i] = ff7->slot[s].chars[0].z_4[i];}
        //set up Sephiroth
        ff7->slot[s].chars[7].id=10;
        if(ff7->SG_Region_String[s].contains("00700") || ff7->SG_Region_String[s].contains("01057"))
        {
            for(int i=0;i<12;i++){ff7->slot[s].chars[7].name[i]=0xFF;}
            QByteArray temp =Text.toFF7(QString::fromUtf8("セフィロス"));
            memcpy(ff7->slot[s].chars[7].name,temp,temp.length());
        }
        else
        {
            for(int i=0;i<12;i++){ff7->slot[s].chars[7].name[i]=0xFF;}
            QByteArray temp = Text.toFF7("Sephiroth");
            memcpy(ff7->slot[s].chars[7].name,temp,temp.length());
        }
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
    if(!load){file_changed=true; progress_update();}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FUNCTIONS FOR TESTING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_btn_remove_all_items_clicked() //used for testing
{
    for(int i=0;i<320;i++)
    {
        ff7->slot[s].items[i].id=0xFF;
        ff7->slot[s].items[i].qty=0xFF;
    }
    if(!load){file_changed=true; }
    itemupdate();
}

void MainWindow::on_btn_remove_all_materia_clicked()
{
    for (int i=0;i<200;i++)
    {
        ff7->slot[s].materias[i].id =0xFF;
        ff7->slot[s].materias[i].ap[0]=0xFF;
        ff7->slot[s].materias[i].ap[1]=0xFF;
        ff7->slot[s].materias[i].ap[2]=0xFF;
    }
    if(!load){file_changed=true; }
    materiaupdate();
}

void MainWindow::on_btn_remove_all_stolen_clicked()
{
    for(int i=0;i<48;i++)
    {
        ff7->slot[s].stolen[i].id =0xFF;
        ff7->slot[s].stolen[i].ap[0]=0xFF;
        ff7->slot[s].stolen[i].ap[1]=0xFF;
        ff7->slot[s].stolen[i].ap[2]=0xFF;
    }
    if(!load){file_changed=true; }
    guirefresh(0);
}

void MainWindow::on_sb_b_love_aeris_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].b_love.aeris = value;}}
void MainWindow::on_sb_b_love_tifa_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].b_love.tifa = value;}}
void MainWindow::on_sb_b_love_yuffie_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].b_love.yuffie = value;}}
void MainWindow::on_sb_b_love_barret_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].b_love.barret = value;}}
void MainWindow::on_sb_coster_1_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].coster_1=value;}}
void MainWindow::on_sb_coster_2_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].coster_2 = value;}}
void MainWindow::on_sb_coster_3_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].coster_3 = value;}}
void MainWindow::on_combo_id_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].chars[curchar].id=index; charupdate();}}
void MainWindow::on_sb_timer_time_hour_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].timer[0] = value;}}
void MainWindow::on_sb_timer_time_min_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].timer[1] = value;}}
void MainWindow::on_sb_timer_time_sec_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].timer[2] = value;}}

void MainWindow::on_list_menu_visible_itemChanged(QListWidgetItem *item)
{if(!load){file_changed=true;
    int j=item->listWidget()->currentRow();
    if(item->checkState() ==Qt::Checked){ff7->slot[s].menu_visible |= (1<<j);}
    else{ff7->slot[s].menu_visible &= ~(1<<j);}
}}

void MainWindow::on_list_menu_locked_itemChanged(QListWidgetItem *item)
{if(!load){file_changed=true;
    int j=item->listWidget()->currentRow();
    if(item->checkState() ==Qt::Checked){ff7->slot[s].menu_locked |= (1<<j);}
    else{ff7->slot[s].menu_locked &= ~(1<<j);}
}}

void MainWindow::on_sb_u_weapon_hp_valueChanged(int value)
{if(!load){file_changed=true;
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
{if(!load){file_changed=true;
    if (checked){ff7->slot[s].reg_vinny =0xFF;}
    else{ff7->slot[s].reg_vinny =0xFB;}
    testdata_refresh();
}}

void MainWindow::on_cb_itemmask1_1_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<0);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<0);}
    ui->lcd_itemmask_1->display(ff7->slot[s].itemsmask_1);
}}

void MainWindow::on_cb_itemmask1_2_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<1);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<1);}
    ui->lcd_itemmask_1->display(ff7->slot[s].itemsmask_1);
}}

void MainWindow::on_cb_itemmask1_3_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<2);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<2);}
    ui->lcd_itemmask_1->display(ff7->slot[s].itemsmask_1);
}}

void MainWindow::on_cb_itemmask1_4_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<3);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<3);}
    ui->lcd_itemmask_1->display(ff7->slot[s].itemsmask_1);
}}

void MainWindow::on_cb_itemmask1_5_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<4);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<4);}
    ui->lcd_itemmask_1->display(ff7->slot[s].itemsmask_1);
}}

void MainWindow::on_cb_itemmask1_6_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<5);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<5);}
    ui->lcd_itemmask_1->display(ff7->slot[s].itemsmask_1);
}}

void MainWindow::on_cb_itemmask1_7_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<6);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<6);}
    ui->lcd_itemmask_1->display(ff7->slot[s].itemsmask_1);
}}

void MainWindow::on_cb_itemmask1_8_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].itemsmask_1 |= (1<<7);}
    else{ff7->slot[s].itemsmask_1 &= ~(1<<7);}
    ui->lcd_itemmask_1->display(ff7->slot[s].itemsmask_1);
}}

void MainWindow::on_cb_materiacave_1_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].materiacaves |= (1<<0);}
    else{ff7->slot[s].materiacaves &= ~(1<<0);}
}}

void MainWindow::on_cb_materiacave_2_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].materiacaves |= (1<<1);}
    else{ff7->slot[s].materiacaves &= ~(1<<1);}
}}

void MainWindow::on_cb_materiacave_3_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].materiacaves |= (1<<2);}
    else{ff7->slot[s].materiacaves &= ~(1<<2);}
}}

void MainWindow::on_cb_materiacave_4_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].materiacaves |= (1<<3);}
    else{ff7->slot[s].materiacaves &= ~(1<<3);}
}}

void MainWindow::on_cb_reg_yuffie_toggled(bool checked)
{if(!load){file_changed=true;
        if (checked){ff7->slot[s].reg_yuffie =0x6F;}
        else{ff7->slot[s].reg_yuffie =0x6E;}
        testdata_refresh();
}}

void MainWindow::on_cb_yuffieforest_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].yuffieforest |= (1<<0);}
    else{ff7->slot[s].yuffieforest &= ~(1<<0);}
}}

void MainWindow::on_cb_midgartrain_1_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].midgartrainflags |= (1<<0);}else{ff7->slot[s].midgartrainflags &= ~(1<<0);}}}
void MainWindow::on_cb_midgartrain_2_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].midgartrainflags |= (1<<1);}else{ff7->slot[s].midgartrainflags &= ~(1<<1);}}}
void MainWindow::on_cb_midgartrain_3_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].midgartrainflags |= (1<<2);}else{ff7->slot[s].midgartrainflags &= ~(1<<2);}}}
void MainWindow::on_cb_midgartrain_4_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].midgartrainflags |= (1<<3);}else{ff7->slot[s].midgartrainflags &= ~(1<<3);}}}
void MainWindow::on_cb_midgartrain_5_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].midgartrainflags |= (1<<4);}else{ff7->slot[s].midgartrainflags &= ~(1<<4);}}}
void MainWindow::on_cb_midgartrain_6_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].midgartrainflags |= (1<<5);}else{ff7->slot[s].midgartrainflags &= ~(1<<5);}}}
void MainWindow::on_cb_midgartrain_7_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].midgartrainflags |= (1<<6);}else{ff7->slot[s].midgartrainflags &= ~(1<<6);}}}
void MainWindow::on_cb_midgartrain_8_toggled(bool checked){if(!load){file_changed=true; if(checked){ff7->slot[s].midgartrainflags |= (1<<7);}else{ff7->slot[s].midgartrainflags &= ~(1<<7);}}}

void MainWindow::on_cb_tut_worldsave_stateChanged(int value)
{if(!load){file_changed=true;
    if (value == 0){ff7->slot[s].tut_save =0x00;}
    else if(value ==1){ff7->slot[s].tut_save =0x32;}
    else if(value ==2){ff7->slot[s].tut_save=0x3A;}
    testdata_refresh();
}}

void MainWindow::on_cb_Region_Slot_currentIndexChanged()
{if(!load){file_changed=true; if(!ff7->SG_Region_String[s].isEmpty()){
    QString new_regionString = ff7->SG_Region_String[s].mid(0,ff7->SG_Region_String[s].lastIndexOf("-")+1);
    new_regionString.append(ui->cb_Region_Slot->currentText().toAscii());
    ff7->SG_Region_String[s].clear();
    ff7->SG_Region_String[s].append(&new_regionString);
    if(ff7->SG_TYPE== "MC"|| ff7->SG_TYPE=="PSP"|| ff7->SG_TYPE=="VGS" || ff7->SG_TYPE =="DEX"){fix_vmc_header(ff7); guirefresh(0);}
}}}

void MainWindow::on_cb_field_help_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].field_help |= (1<<0);}
    else{ff7->slot[s].field_help &= ~(1<<0);}
}}

void MainWindow::on_cb_battle_targets_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].tut_sub |= (1<<6);}
    else{ff7->slot[s].tut_sub &= ~(1<<6);}
}}
void MainWindow::on_cb_tut_sub_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].tut_sub |= (1<<2);}
    else{ff7->slot[s].tut_sub &= ~(1<<2);}
    testdata_refresh();
}}
void MainWindow::on_cb_tut_sub_1_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].tut_sub |= (1<<0);}
    else{ff7->slot[s].tut_sub &= ~(1<<0);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_2_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].tut_sub |= (1<<1);}
    else{ff7->slot[s].tut_sub &= ~(1<<1);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_3_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].tut_sub |= (1<<2);}
    else{ff7->slot[s].tut_sub &= ~(1<<2);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_4_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].tut_sub |= (1<<3);}
    else{ff7->slot[s].tut_sub &= ~(1<<3);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_5_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].tut_sub |= (1<<4);}
    else{ff7->slot[s].tut_sub &= ~(1<<4);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_6_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].tut_sub |= (1<<5);}
    else{ff7->slot[s].tut_sub &= ~(1<<5);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_7_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].tut_sub |= (1<<6);}
    else{ff7->slot[s].tut_sub &= ~(1<<6);}
    testdata_refresh();
}}

void MainWindow::on_cb_tut_sub_8_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].tut_sub |= (1<<7);}
    else{ff7->slot[s].tut_sub &= ~(1<<7);}
    testdata_refresh();
}}

void MainWindow::on_cb_ruby_dead_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].ruby_emerald |= (1<<3);}
    else{ff7->slot[s].ruby_emerald &= ~(1<<3);}
}}

void MainWindow::on_cb_emerald_dead_toggled(bool checked)
{if(!load){file_changed=true;
    if(checked){ff7->slot[s].ruby_emerald |= (1<<4);}
    else{ff7->slot[s].ruby_emerald &= ~(1<<4);}
}}

void MainWindow::on_combo_highwind_buggy_currentIndexChanged(int index)
{if(!load){file_changed=true;
  switch(index)
  {
  case 1: ui->bh_id->setValue(0x06);ui->cb_visible_buggy->setChecked(Qt::Checked);break;//buggy
  case 2: ui->bh_id->setValue(0x03);ui->cb_visible_highwind->setChecked(Qt::Checked);break;//highwind
  default: break;
  }
}}
void MainWindow::on_cb_visible_buggy_toggled(bool checked)
{if(!load){file_changed=true;
        if(checked){ff7->slot[s].world_map_vehicles |= (1<<0);}
        else{ff7->slot[s].world_map_vehicles &= ~(1<<0);}
}}
void MainWindow::on_cb_visible_bronco_toggled(bool checked)
{if(!load){file_changed=true;
        if(checked){ff7->slot[s].world_map_vehicles |= (1<<2);}
        else{ff7->slot[s].world_map_vehicles &= ~(1<<2);}
}}
void MainWindow::on_cb_visible_highwind_toggled(bool checked)
{if(!load){file_changed=true;
        if(checked){ff7->slot[s].world_map_vehicles |= (1<<4);}
        else{ff7->slot[s].world_map_vehicles &= ~(1<<4);}
}}
void MainWindow::on_cb_visible_wild_chocobo_toggled(bool checked)
{if(!load){file_changed=true;
        if(checked){ff7->slot[s].world_map_chocobos |= (1<<0);}
        else{ff7->slot[s].world_map_chocobos &= ~(1<<0);}
}}
void MainWindow::on_cb_visible_yellow_chocobo_toggled(bool checked)
{if(!load){file_changed=true;
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
{if(!load){file_changed=true;
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
{if(!load){file_changed=true;
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
{if(!load){file_changed=true;
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
{if(!load){file_changed=true;
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
void MainWindow::on_leader_id_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].l_world = (ui->leader_x->value()  | value << 19 | ui->leader_angle->value() <<24);}}
void MainWindow::on_leader_angle_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].l_world = (ui->leader_x->value()  | ui->leader_id->value() << 19 | value <<24);}}
void MainWindow::on_leader_z_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].l_world2 = (ui->leader_y->value() | value << 18);}}
void MainWindow::on_leader_x_valueChanged(int value)
{if(!load){file_changed=true;
    ff7->slot[s].l_world = (value | ui->leader_id->value() << 19 | ui->leader_angle->value() << 24);
    if(ui->combo_map_controls->currentIndex()==0){load=true;ui->slide_world_x->setValue(value);load=false;}
}}

void MainWindow::on_leader_y_valueChanged(int value)
{if(!load){file_changed=true;
    ff7->slot[s].l_world2 = (value | ui->leader_z->value() << 18);
    if(ui->combo_map_controls->currentIndex()==0){load=true;ui->slide_world_y->setValue(value);load=false;}
}}

//Tiny bronco / chocobo world 1
void MainWindow::on_tc_id_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].tc_world = (ui->tc_x->value()  | value << 19 | ui->tc_angle->value() <<24);}}
void MainWindow::on_tc_angle_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].tc_world = (ui->tc_x->value()  | ui->tc_id->value() << 19 | value <<24);}}
void MainWindow::on_tc_z_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].tc_world2 = (ui->tc_y->value() | value << 18);}}
void MainWindow::on_tc_x_valueChanged(int value)
{if(!load){file_changed=true;
    ff7->slot[s].tc_world = (value | ui->tc_id->value() << 19 | ui->tc_angle->value() << 24);
    if(ui->combo_map_controls->currentIndex()==1){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_tc_y_valueChanged(int value)
{if(!load){file_changed=true;
    ff7->slot[s].tc_world2 = (value | ui->tc_z->value() << 18);
    if(ui->combo_map_controls->currentIndex()==1){load=true;ui->slide_world_y->setValue(value);load=false;}
}}

//buggy / highwind world 2
void MainWindow::on_bh_id_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].bh_world = (ui->bh_x->value()  | value << 19 | ui->bh_angle->value() <<24);}}
void MainWindow::on_bh_angle_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].bh_world = (ui->bh_x->value()  | ui->bh_id->value() << 19 | value <<24);}}
void MainWindow::on_bh_z_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].bh_world2 = (ui->bh_y->value() | value << 18);}}
void MainWindow::on_bh_x_valueChanged(int value)
{if(!load){file_changed=true;
    ff7->slot[s].bh_world = (value | ui->bh_id->value() << 19 | ui->bh_angle->value() << 24);
    if(ui->combo_map_controls->currentIndex()==2){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_bh_y_valueChanged(int value)
{if(!load){file_changed=true;
        ff7->slot[s].bh_world2 = (value | ui->bh_z->value() << 18);
        if(ui->combo_map_controls->currentIndex()==2){load=true;ui->slide_world_y->setValue(value);load=false;}
}}
// sub world 3
void MainWindow::on_sub_id_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].sub_world = (ui->sub_x->value()  | value << 19 | ui->sub_angle->value() <<24);}}
void MainWindow::on_sub_angle_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].sub_world = (ui->sub_x->value()  | ui->sub_id->value() << 19 | value <<24);}}
void MainWindow::on_sub_z_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].sub_world2 = (ui->sub_y->value() | value << 18);}}
void MainWindow::on_sub_x_valueChanged(int value)
{if(!load){file_changed=true;
    ff7->slot[s].sub_world = (value | ui->sub_id->value() << 19 | ui->sub_angle->value() << 24);
     if(ui->combo_map_controls->currentIndex()==3){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_sub_y_valueChanged(int value)
{if(!load){file_changed=true;
    ff7->slot[s].sub_world2 = (value | ui->sub_z->value() << 18);
    if(ui->combo_map_controls->currentIndex()==3){load=true;ui->slide_world_y->setValue(value);load=false;}
}}

//Ruby world stuff 4
void MainWindow::on_durw_id_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].durw_world = (ui->durw_x->value()  | value << 19 | ui->durw_angle->value() <<24);}}
void MainWindow::on_durw_angle_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].durw_world = (ui->durw_x->value()  | ui->durw_id->value() << 19 | value <<24);}}
void MainWindow::on_durw_z_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].durw_world2 = (ui->durw_y->value() | value << 18);}}
void MainWindow::on_durw_x_valueChanged(int value)
{if(!load){file_changed=true;
    ff7->slot[s].durw_world = (value | ui->durw_id->value() << 19 | ui->durw_angle->value() << 24);
     if(ui->combo_map_controls->currentIndex()==4){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_durw_y_valueChanged(int value)
{if(!load){file_changed=true;
    ff7->slot[s].durw_world2 = (value | ui->durw_z->value() << 18);
     if(ui->combo_map_controls->currentIndex()==4){load=true;ui->slide_world_y->setValue(value);load=false;}
}}
//emerald world 5?
/* Do Nothing. Don't know emerald weapon Coords
void MainWindow::on_ew_id_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].ew_world = (ui->ew_x->value()  | value << 19 | ui->ew_angle->value() <<24);}}
void MainWindow::on_ew_z_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].ew_world2 = (ui->ew_y->value() | value << 18);}}
void MainWindow::on_ew_angle_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].ew_world = (ui->ew_x->value()  | ui->ew_id->value() << 19 | value <<24);}}
void MainWindow::on_ew_x_valueChanged(int value)
{if(!load){file_changed=true;
    ff7->slot[s].ew_world = (value | ui->ew_id->value() << 19 | ui->ew_angle->value() << 24);
     if(ui->combo_map_controls->currentIndex()==5){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_ew_y_valueChanged(int value)
{if(!load){
        file_changed=true;
        ff7->slot[s].ew_world2 = (value | ui->ew_z->value() << 18);
        if(ui->combo_map_controls->currentIndex()==5){load=true;ui->slide_world_y->setValue(value);load=false;}
}}
*/
//ultimate weapon 6?
void MainWindow::on_uw_id_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].uw_world = (ui->uw_x->value()  | value << 19 | ui->uw_angle->value() <<24);}}
void MainWindow::on_uw_angle_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].uw_world = (ui->uw_x->value()  | ui->uw_id->value() << 19 | value <<24);}}
void MainWindow::on_uw_z_valueChanged(int value){if(!load){file_changed=true; ff7->slot[s].uw_world2 = (ui->uw_y->value() | value << 18);}}
void MainWindow::on_uw_x_valueChanged(int value)
{if(!load){file_changed=true;
    ff7->slot[s].uw_world = (value | ui->uw_id->value() << 19 | ui->uw_angle->value() << 24);
     if(ui->combo_map_controls->currentIndex()==6){load=true;ui->slide_world_x->setValue(value);load=false;}
}}
void MainWindow::on_uw_y_valueChanged(int value)
{if(!load){file_changed=true;
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
{if(!load){file_changed=true;
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
{if(!load){file_changed=true;
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
    file_changed=true;
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
    if(!load){file_changed=true; }
    ui->btn_remove_all_items->click();
    for(int i=0;i<320;i++)
    {
        if(FF7Strings.ItemNames(i)!=tr("DON'T USE"))
        {
            if(i<106)
            {
                ff7->slot[s].items[i].id = i;
                if(i<256){ ff7->slot[s].items[i].qty = 198;}//254
                else {ff7->slot[s].items[i].qty=199;}//255
            }
            else// after the block of empty items shift up 23 spots.
            {
                ff7->slot[s].items[i-23].id = i;
                if(i<256){ ff7->slot[s].items[i-23].qty = 198;}
                else {ff7->slot[s].items[i-23].qty=199;}
            }
        }
        else{ff7->slot[s].items[i].id=0xFF;ff7->slot[s].items[i].qty=0xFF;}//exclude the test items
    if(i>296){ff7->slot[s].items[i].id=0xFF;ff7->slot[s].items[i].qty=0xFF;}//replace the shifted ones w/ empty slots
    }
    guirefresh(0);
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
{if(!load){file_changed=true;
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

void MainWindow::on_combo_button_1_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[0]=index;}}
void MainWindow::on_combo_button_2_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[1]=index;}}
void MainWindow::on_combo_button_3_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[2]=index;}}
void MainWindow::on_combo_button_4_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[3]=index;}}
void MainWindow::on_combo_button_5_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[4]=index;}}
void MainWindow::on_combo_button_6_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[5]=index;}}
void MainWindow::on_combo_button_7_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[6]=index;}}
void MainWindow::on_combo_button_8_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[7]=index;}}
void MainWindow::on_combo_button_9_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[8]=index;}}
void MainWindow::on_combo_button_10_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[9]=index;}}
void MainWindow::on_combo_button_11_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[10]=index;}}
void MainWindow::on_combo_button_12_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[11]=index;}}
void MainWindow::on_combo_button_13_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[12]=index;}}
void MainWindow::on_combo_button_14_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[13]=index;}}
void MainWindow::on_combo_button_15_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[14]=index;}}
void MainWindow::on_combo_button_16_currentIndexChanged(int index){if(!load){file_changed=true; ff7->slot[s].controller_map[15]=index;}}

void MainWindow::on_btn_copy_materia_clicked()
{
    if(ui->tbl_materia->currentRow() == -1){return;}
    else
    {
        buffer_materia.id = ff7->slot[s].materias[ui->tbl_materia->currentRow()].id;
        buffer_materia.ap[0] = ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[0];
        buffer_materia.ap[1] = ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[1];
        buffer_materia.ap[2] = ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[2];
    }
}

void MainWindow::on_btn_paste_materia_clicked()
{if(!load){file_changed=true;}
    if(ui->tbl_materia->currentRow() == -1){return;}
    else
    {
        ff7->slot[s].materias[ui->tbl_materia->currentRow()].id = buffer_materia.id;
        ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[0]= buffer_materia.ap[0];
        ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[1]= buffer_materia.ap[1];
        ff7->slot[s].materias[ui->tbl_materia->currentRow()].ap[2]= buffer_materia.ap[2];
        materiaupdate();
    }
}

void MainWindow::on_combo_s7_slums_currentIndexChanged(int index)
{if(!load){file_changed=true;
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
