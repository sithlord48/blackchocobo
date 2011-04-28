/****************************************************************************/
//    copyright 2010,2011 Chris Rizzitello <sithlord48@gmail.com>           //
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
#include <QFileDialog> // for file dialogs
#include <QDataStream> // for data manip
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"    // contains checksumming functions
#include "slotselect.h" // slot selection dialog stuff.
#include "options.h" // contains the options dialog
#include "about.h"      // about dialog stuff.
#include "errbox.h" //non ff7 error box
#include <QSettings>
#include <SaveIcon.h>
/*~~~~~GLOBALS~~~~~~*/
bool load =false; //used for checking if data is initial load (to block some overrights when gui objects change)
extern FF7 ff7; // our save file struct
extern int s; //keeps track of our slot globally
FF7SLOT bufferslot; // a buffer slot to keep copied slots in
QString buffer_region; //keep track of the region of any copied slots.
char chFF7[256];  // char arrary for converting to ff7 chars , so far not used.
int curchar =0; //keeps track of current character displayed
int mslotsel = 0; //keeps track of materia slot on char selected
QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"blackchocobo","settings",0);
QString filename;

/*~~~~~~~~GUI Set Up~~~~~~~*/
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i=0; i<256; i++)
    {
        for (int j=255; j>=0; j--)
        {
            if (chPC[j] == (char)i)
            chFF7[i] = (char)j;
        }
    }
    load=true;

    //set up comboboxes.
    for (int i=256;i<288;i++){ui->combo_armor->addItem(QIcon(Items[i].image),Items[i].name);}
    for (int i=288;i<320;i++){ui->combo_acc->addItem(QIcon(Items[i].image),Items[i].name);}
    for (int i=0;i<320;i++){ui->combo_additem->addItem(QIcon(Items[i].image),Items[i].name);}
    for (int i=0;i<0x5b;i++){ui->combo_add_mat->addItem(QIcon(Materias[i].image),Materias[i].name);}
    for (int i=0;i<0x5b;i++){if(Materias[i].name !="DON'T USE"){ui->combo_add_mat_2->addItem(QIcon(Materias[i].image),Materias[i].name);}}
    for (int i=0;i<0x5b;i++){ui->combo_add_mat_slot->addItem(QIcon(Materias[i].image),Materias[i].name);}

    //set up tables..
    ui->tbl_location_field->setColumnWidth(0,147);
    ui->tbl_location_field->setColumnWidth(1,50);
    ui->tbl_location_field->setColumnWidth(2,50);
    ui->tbl_location_field->setColumnWidth(3,50);
    ui->tbl_location_field->setColumnWidth(4,50);

    //Hide the stuff that needs to be hidden.
    ui->eskill_group->setVisible(false);
    ui->eskill_group_2->setVisible(false);
    ui->combo_add_mat->setVisible(false);

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
    ui->sb_bm_progress1->setEnabled(false);
    ui->sb_bm_progress2->setEnabled(false);
    ui->sb_bm_progress3->setEnabled(false);

    load=false;

    // load settings
    if(settings.value("show_test").toBool())
    {
        ui->action_show_test_data->setChecked(1);
        ui->action_show_test_data->setIcon(QIcon(":/icon/debug_sel"));
    }
   //are any empty? if so set them accordingly.
   if(settings.value("default_save_file").isNull()){settings.setValue("default_save_file",QString(QCoreApplication::applicationDirPath()) + "/"+ "save0");}
   if(settings.value("load_path").isNull()){settings.setValue("load_path",QDir::homePath());}
   if(settings.value("char_stat_folder").isNull()){settings.setValue("char_stat_folder",settings.value("load_path").toString());}
   if(settings.value("color1_r").isNull()){settings.setValue("color1_r","7");}
   if(settings.value("color1_g").isNull()){settings.setValue("color1_g","6");}
   if(settings.value("color1_b").isNull()){settings.setValue("color1_b","6");}

   if(settings.value("color2_r").isNull()){settings.setValue("color2_r","35");}
   if(settings.value("color2_g").isNull()){settings.setValue("color2_g","33");}
   if(settings.value("color2_b").isNull()){settings.setValue("color2_b","33");}

   if(settings.value("color3_r").isNull()){settings.setValue("color3_r","65");}
   if(settings.value("color3_g").isNull()){settings.setValue("color3_g","65");}
   if(settings.value("color3_b").isNull()){settings.setValue("color3_b","65");}

   QString style="QWidget#centralWidget{background-color: qlineargradient(spread:repeat, x1:1, y1:1, x2:0, y2:0, stop:0.0625 rgba(";
   style.append(settings.value("color1_r").toString());
   style.append(",");
   style.append(settings.value("color1_g").toString());
   style.append(",");
   style.append(settings.value("color1_b").toString());
   style.append(", 255), stop:0.215909 rgba(");
   style.append(settings.value("color2_r").toString());
   style.append(",");
   style.append(settings.value("color2_g").toString());
   style.append(",");
   style.append(settings.value("color2_b").toString());
   style.append(", 255), stop:0.818182 rgba(");
   style.append(settings.value("color3_r").toString());
   style.append(",");
   style.append(settings.value("color3_g").toString());
   style.append(",");
   style.append(settings.value("color3_b").toString());
   style.append(", 255));}");
   ui->centralWidget->setStyleSheet(style);


   QString tablestyle = "::section{background-color:rgba(10,10,10,128);color: white;padding-left:4px;border:1px solid #6c6c6c;}";
   tablestyle.append("QHeaderView:down-arrow{image: url(:/icon/arrow_down);min-width:9px;}");
   tablestyle.append("QHeaderView:up-arrow{image: url(:/icon/arrow_up);min-width:9px;}");

   ui->tbl_location_field->horizontalHeader()->setStyleSheet(tablestyle);

   /* LANGUAGE SELECT */
   if(settings.value("lang").toString() == "en")
   {
       ui->action_Lang_en->setChecked(1);
       ui->action_Lang_en->setIcon(QIcon(":/icon/us_sel"));
   }
   else if(settings.value("lang").toString() == "es")
   {
       ui->action_Lang_es->setChecked(1);
       ui->action_Lang_es->setIcon(QIcon(":/icon/es_sel"));
   }
   else if(settings.value("lang").toString() == "fr")
   {
       ui->action_Lang_fr->setChecked(1);
       ui->action_Lang_fr->setIcon(QIcon(":/icon/fr_sel"));
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
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~LOAD/SAVE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionOpen_Save_File_activated()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Final Fantasy 7 Save"),settings.value("load_path").toString(),
    tr("Known FF7 Save Types (*.ff7 *-S* *.psv *.vmp *.mcr *.mcd *.mc *.ddf *.ps *.psm);;PC FF7 SaveGame (*.ff7);;Raw PSX FF7 SaveGame (*-S*);;MC SaveGame (*.mcr *.mcd *.mc *.ddf *.ps *.psm);;PSV SaveGame (*.psv);;PSP SaveGame (*.vmp)"));
    if (!fileName.isEmpty()) loadFileFull(fileName);
}

void MainWindow::loadFileFull(const QString &fileName)
{
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
    if(file_size == FF7_PC_SAVE_GAME_SIZE)
    {
       ff7.SG_SIZE          = FF7_PC_SAVE_GAME_SIZE;
       ff7.SG_HEADER        = FF7_PC_SAVE_GAME_HEADER;
       ff7.SG_FOOTER        = FF7_PC_SAVE_GAME_FOOTER;
       ff7.SG_DATA_SIZE     = FF7_PC_SAVE_GAME_DATA_SIZE;
       ff7.SG_SLOT_HEADER   = FF7_PC_SAVE_GAME_SLOT_HEADER;
       ff7.SG_SLOT_FOOTER   = FF7_PC_SAVE_GAME_SLOT_FOOTER;
       ff7.SG_SLOT_SIZE     = FF7_PC_SAVE_GAME_SLOT_SIZE;
       ff7.SG_SLOT_NUMBER   = FF7_PC_SAVE_GAME_SLOT_NUMBER;
       ff7.SG_TYPE          = "PC";
       ff7.file_headerp     = ff7.file_header_pc;           //pointer to pc file header
       ff7.file_footerp     = ff7.file_footer_pc;           //pointer to pc file footer
       ff7.savetype         = 1;
    }
    else if(file_size == FF7_PSX_SAVE_GAME_SIZE)
    {
       ff7.SG_SIZE          = FF7_PSX_SAVE_GAME_SIZE;
       ff7.SG_HEADER        = FF7_PSX_SAVE_GAME_HEADER;
       ff7.SG_FOOTER        = FF7_PSX_SAVE_GAME_FOOTER;
       ff7.SG_DATA_SIZE     = FF7_PSX_SAVE_GAME_DATA_SIZE;
       ff7.SG_SLOT_HEADER   = FF7_PSX_SAVE_GAME_SLOT_HEADER;
       ff7.SG_SLOT_FOOTER   = FF7_PSX_SAVE_GAME_SLOT_FOOTER;
       ff7.SG_SLOT_SIZE     = FF7_PSX_SAVE_GAME_SLOT_SIZE;
       ff7.SG_SLOT_NUMBER   = FF7_PSX_SAVE_GAME_SLOT_NUMBER;
       ff7.SG_TYPE          = "PSX";
       ff7.file_headerp     = ff7.file_header_psx;          //pointer to psx file header
       ff7.file_footerp     = ff7.file_footer_psx;          //pointer to psx file footer
       ff7.savetype         = 2;
    }
    else if(file_size == FF7_MC_SAVE_GAME_SIZE)
    {
       ff7.SG_SIZE          = FF7_MC_SAVE_GAME_SIZE;
       ff7.SG_HEADER        = FF7_MC_SAVE_GAME_HEADER;
       ff7.SG_FOOTER        = FF7_MC_SAVE_GAME_FOOTER;
       ff7.SG_DATA_SIZE     = FF7_MC_SAVE_GAME_DATA_SIZE;
       ff7.SG_SLOT_HEADER   = FF7_MC_SAVE_GAME_SLOT_HEADER;
       ff7.SG_SLOT_FOOTER   = FF7_MC_SAVE_GAME_SLOT_FOOTER;
       ff7.SG_SLOT_SIZE     = FF7_MC_SAVE_GAME_SLOT_SIZE;
       ff7.SG_SLOT_NUMBER   = FF7_MC_SAVE_GAME_SLOT_NUMBER;
       ff7.SG_TYPE          = "MC";
       ff7.file_headerp     = ff7.file_header_mc;           //pointer to mc file header
       ff7.file_footerp     = ff7.file_footer_mc;           //pointer to mc file footer
       ff7.savetype         = 3;

    }
    else if(file_size == FF7_PSV_SAVE_GAME_SIZE)
    {
       ff7.SG_SIZE          = FF7_PSV_SAVE_GAME_SIZE;
       ff7.SG_HEADER        = FF7_PSV_SAVE_GAME_HEADER;
       ff7.SG_FOOTER        = FF7_PSV_SAVE_GAME_FOOTER;
       ff7.SG_DATA_SIZE     = FF7_PSV_SAVE_GAME_DATA_SIZE;
       ff7.SG_SLOT_HEADER   = FF7_PSV_SAVE_GAME_SLOT_HEADER;
       ff7.SG_SLOT_FOOTER   = FF7_PSV_SAVE_GAME_SLOT_FOOTER;
       ff7.SG_SLOT_SIZE     = FF7_PSV_SAVE_GAME_SLOT_SIZE;
       ff7.SG_SLOT_NUMBER   = FF7_PSV_SAVE_GAME_SLOT_NUMBER;
       ff7.SG_TYPE          = "PSV";
       ff7.file_headerp     = ff7.file_header_psv;          //pointer to psv file header
       ff7.file_footerp     = ff7.file_footer_psv;          //pointer to psv file footer
       ff7.savetype         = 4;
    }
    else if(file_size ==FF7_PSP_SAVE_GAME_SIZE)
    {
        ff7.SG_SIZE          = FF7_PSP_SAVE_GAME_SIZE;
        ff7.SG_HEADER        = FF7_PSP_SAVE_GAME_HEADER;
        ff7.SG_FOOTER        = FF7_PSP_SAVE_GAME_FOOTER;
        ff7.SG_DATA_SIZE     = FF7_PSP_SAVE_GAME_DATA_SIZE;
        ff7.SG_SLOT_HEADER   = FF7_PSP_SAVE_GAME_SLOT_HEADER;
        ff7.SG_SLOT_FOOTER   = FF7_PSP_SAVE_GAME_SLOT_FOOTER;
        ff7.SG_SLOT_SIZE     = FF7_PSP_SAVE_GAME_SLOT_SIZE;
        ff7.SG_SLOT_NUMBER   = FF7_PSP_SAVE_GAME_SLOT_NUMBER;
        ff7.SG_TYPE          = "PSP";
        ff7.file_headerp     = ff7.file_header_psp;          //pointer to psp file header
        ff7.file_footerp     = ff7.file_footer_psp;          //pointer to psp file footer
        ff7.savetype         = 5;
    }
    else
    {
        QMessageBox::warning(this, tr("Unknown Filetype"),
        tr("File: %1 \nis not a FF7 SaveGame.")
        .arg(fileName));
        return;
    }

    /*~~~~~~~~~~Start Load~~~~~~~~~~*/
    memcpy(ff7.file_headerp,ff7file.mid(0x0000,ff7.SG_HEADER),ff7.SG_HEADER);// collect header (0x09) bytes (PC), (0x00) bytes (PSX), (0x2000) bytes (MC)
    for (int i=0;i<ff7.SG_SLOT_NUMBER;i++)
    {
        int index = (ff7.SG_SLOT_SIZE*i) + ff7.SG_HEADER + ff7.SG_SLOT_HEADER;
        memcpy(ff7.hf[i].sl_header,ff7file.mid((ff7.SG_SLOT_SIZE*i) + (ff7.SG_HEADER + 0x0000),ff7.SG_SLOT_HEADER),ff7.SG_SLOT_HEADER);// collect slot header (0x00) bytes (PC), (0x0200) bytes (PSX), (0x0200) bytes (MC)
        temp = ff7file.mid(index,0x10f4);
        memcpy(&ff7.slot[i],temp,0x10f4);
        memcpy(ff7.hf[i].sl_footer,ff7file.mid((ff7.SG_SLOT_SIZE*i)+ (ff7.SG_HEADER+ff7.SG_SLOT_HEADER+ff7.SG_DATA_SIZE),ff7.SG_SLOT_FOOTER),ff7.SG_SLOT_FOOTER);// collect slot footer (0x00) bytes (PC), (0x0D0C) bytes (PSX), (0x0D0C) bytes (MC)
    }
    /*~~~~~~~End Load~~~~~~~~~~~~~~*/
    if (ff7.savetype == 1)
    {
        if(ff7.slot[0].checksum != 0x0000 && ff7.slot[0].checksum != 0x4D1D){ff7.SG_Region_String[0]= "BASCUS-94163FF7-S01";} else {ff7.SG_Region_String[0] = "";}
        if(ff7.slot[1].checksum != 0x0000 && ff7.slot[1].checksum != 0x4D1D){ff7.SG_Region_String[1]= "BASCUS-94163FF7-S02";} else {ff7.SG_Region_String[1] = "";}
        if(ff7.slot[2].checksum != 0x0000 && ff7.slot[2].checksum != 0x4D1D){ff7.SG_Region_String[2]= "BASCUS-94163FF7-S03";} else {ff7.SG_Region_String[2] = "";}
        if(ff7.slot[3].checksum != 0x0000 && ff7.slot[3].checksum != 0x4D1D){ff7.SG_Region_String[3]= "BASCUS-94163FF7-S04";} else {ff7.SG_Region_String[3] = "";}
        if(ff7.slot[4].checksum != 0x0000 && ff7.slot[4].checksum != 0x4D1D){ff7.SG_Region_String[4]= "BASCUS-94163FF7-S05";} else {ff7.SG_Region_String[4] = "";}
        if(ff7.slot[5].checksum != 0x0000 && ff7.slot[5].checksum != 0x4D1D){ff7.SG_Region_String[5]= "BASCUS-94163FF7-S06";} else {ff7.SG_Region_String[5] = "";}
        if(ff7.slot[6].checksum != 0x0000 && ff7.slot[6].checksum != 0x4D1D){ff7.SG_Region_String[6]= "BASCUS-94163FF7-S07";} else {ff7.SG_Region_String[6] = "";}
        if(ff7.slot[7].checksum != 0x0000 && ff7.slot[7].checksum != 0x4D1D){ff7.SG_Region_String[7]= "BASCUS-94163FF7-S08";} else {ff7.SG_Region_String[7] = "";}
        if(ff7.slot[8].checksum != 0x0000 && ff7.slot[8].checksum != 0x4D1D){ff7.SG_Region_String[8]= "BASCUS-94163FF7-S09";} else {ff7.SG_Region_String[8] = "";}
        if(ff7.slot[9].checksum != 0x0000 && ff7.slot[9].checksum != 0x4D1D){ff7.SG_Region_String[9]= "BASCUS-94163FF7-S10";} else {ff7.SG_Region_String[9] = "";}
        if(ff7.slot[10].checksum != 0x0000 && ff7.slot[10].checksum != 0x4D1D){ff7.SG_Region_String[10]= "BASCUS-94163FF7-S11";} else {ff7.SG_Region_String[10] = "";}
        if(ff7.slot[11].checksum != 0x0000 && ff7.slot[11].checksum != 0x4D1D){ff7.SG_Region_String[11]= "BASCUS-94163FF7-S12";} else {ff7.SG_Region_String[11] = "";}
        if(ff7.slot[12].checksum != 0x0000 && ff7.slot[12].checksum != 0x4D1D){ff7.SG_Region_String[12]= "BASCUS-94163FF7-S13";} else {ff7.SG_Region_String[12] = "";}
        if(ff7.slot[13].checksum != 0x0000 && ff7.slot[13].checksum != 0x4D1D){ff7.SG_Region_String[13]= "BASCUS-94163FF7-S14";} else {ff7.SG_Region_String[13] = "";}
        if(ff7.slot[14].checksum != 0x0000 && ff7.slot[14].checksum != 0x4D1D){ff7.SG_Region_String[14]= "BASCUS-94163FF7-S15";} else {ff7.SG_Region_String[14] = "";}
        SlotSelect slotselect;
        slotselect.exec();
    }

    else if (ff7.savetype == 2 || ff7.savetype == 4)
    {
        s=0;
             if(fileName.contains("00867")){ff7.SG_Region_String[s] = "BESCES-00867FF7-S01";}
        else if(fileName.contains("00869")){ff7.SG_Region_String[s] = "BESCES-00869FF7-S01";}
        else if(fileName.contains("00900")){ff7.SG_Region_String[s] = "BESCES-00900FF7-S01";}
        else if(fileName.contains("94163")){ff7.SG_Region_String[s] = "BASCUS-94163FF7-S01";}
        else if(fileName.contains("00700")){ff7.SG_Region_String[s] = "BISLPS-00700FF7-S01";}
        else if(fileName.contains("01057")){ff7.SG_Region_String[s] = "BISLPS-01057FF7-S01";}
        else {ff7.SG_Region_String[s] ="";}

        for(int i=1;i<14;i++){clearslot(i);}
    }

    else if (ff7.savetype == 3 || ff7.savetype ==5)
    {
        QByteArray mc_header;
        int offset = 0;
        if(ff7.savetype ==5){offset = 0x80;} // psp save. start after the extra vmp header info
        mc_header = ff7file.mid(offset,ff7.SG_HEADER);
        int index=0;
        for(int i=0; i<15;i++)
        {
            index = (128*i) +138;
            ff7.SG_Region_String[i] = QString(mc_header.mid(index,19));
        }
        SlotSelect slotselect;
        slotselect.exec();
    }
    else
    {
        s=0;
        for(int i=1;i<14;i++){clearslot(i);}
    }
    this->setWindowTitle(tr("Black Chocobo - ") + fileName); //eslava this is for you :)
    filename = fileName.mid(fileName.lastIndexOf("/")+1,fileName.lastIndexOf(".")-1-fileName.lastIndexOf("/"));
    guirefresh();
}
/*~~~~~~~~~~~~~~~~~IMPORT PSX~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionFrom_PSX_Slot_activated()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Select Final Fantasy 7 PSX Save"),(""),tr("Raw PSX FF7 SaveGame (*-S*)"));
    if(fileName== ""){return;}
    if (!fileName.isEmpty())
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
        int index = 0x200;
        temp = ff7file.mid(index,0x10f4);
        memcpy(&ff7.slot[s],temp,0x10f4);
        if(fileName.contains("00867")){ff7.SG_Region_String[s] = "BESCES-00867FF7-S01";}
   else if(fileName.contains("00869")){ff7.SG_Region_String[s] = "BESCES-00869FF7-S01";}
   else if(fileName.contains("00900")){ff7.SG_Region_String[s] = "BESCES-00900FF7-S01";}
   else if(fileName.contains("94163")){ff7.SG_Region_String[s] = "BASCUS-94163FF7-S01";}
   else if(fileName.contains("00700")){ff7.SG_Region_String[s] = "BISLPS-00700FF7-S01";}
   else if(fileName.contains("01057")){ff7.SG_Region_String[s] = "BISLPS-01057FF7-S01";}
   else {ff7.SG_Region_String[s] ="";}
    }//Parse slot data....
    guirefresh();
}
/*~~~~~~~~~~~~~~~~~IMPORT PSV~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionFrom_PSV_Slot_activated()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Select Final Fantasy 7 PSV Save"),(""),tr("PSX FF7 SaveGame (*.psv)"));
    if (fileName == ""){return;}
    if (!fileName.isEmpty())
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
            int index = 0x284;
            temp = ff7file.mid(index,0x10f4);
            memcpy(&ff7.slot[s],temp,0x10f4);
            if(fileName.contains("00867")){ff7.SG_Region_String[s] = "BESCES-00867FF7-S01";}
       else if(fileName.contains("00869")){ff7.SG_Region_String[s] = "BESCES-00869FF7-S01";}
       else if(fileName.contains("00900")){ff7.SG_Region_String[s] = "BESCES-00900FF7-S01";}
       else if(fileName.contains("94163")){ff7.SG_Region_String[s] = "BASCUS-94163FF7-S01";}
       else if(fileName.contains("00700")){ff7.SG_Region_String[s] = "BISLPS-00700FF7-S01";}
       else if(fileName.contains("01057")){ff7.SG_Region_String[s] = "BISLPS-01057FF7-S01";}
       else {ff7.SG_Region_String[s] ="";}
        }//Parse slot data....
    guirefresh();
}
void MainWindow::on_actionImport_char_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Select FF7 Character Stat File"),settings.value("char_stat_folder").toString(),tr("FF7 Character Stat File(*.char)"));
    if (fileName == ""){return;}
    if (!fileName.isEmpty())
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
            memcpy(&ff7.slot[s].chars[curchar],ff7file,132);
        }
guirefresh();
}

void MainWindow::on_actionExport_char_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save FF7 Character File"), settings.value("char_stat_folder").toString(),
    tr("FF7 Character Stat File(*.char)"));
    if (!fileName.isEmpty())
    {
        FILE *pfile;
        pfile = fopen(fileName.toAscii(),"wb");
        fwrite(&ff7.slot[s].chars[curchar],132,1,pfile);
        fclose(pfile);
    }
}

void MainWindow::on_actionSave_File_activated()
{
// check for the type of save loaded and set the output type so we don't save the wrong type, all conversion opperations should be done via an Export function.
    if(ff7.savetype==1)
    {
        QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 PC SaveGame"), settings.value("save_pc_path").toString(),
        tr("FF7 PC SaveGame(*.ff7)"));
        if (!fileName.isEmpty())
            fix_pc_bytemask();// adjust the bytemask so the correct slots are shown
            saveFileFull(fileName);
    }
    else if(ff7.savetype==2)
    {
        QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 PSX SaveGame"), ff7.SG_Region_String[s],
        tr("FF7 Raw PSX SaveGame(*-S*)"));
        if (!fileName.isEmpty())
        {
            if((ff7.slot[s].time/3600)>99){ff7.hf[s].sl_header[27]=0x58;ff7.hf[s].sl_header[29]=0x58;}
            else
            {
                ff7.hf[s].sl_header[27] = ((ff7.slot[s].time/3600)/10)+0x4F;
                ff7.hf[s].sl_header[29] = ((ff7.slot[s].time/3600)%10)+0x4F;
            }
            ff7.hf[s].sl_header[33] = ((ff7.slot[s].time/60%60)/10)+0x4F;
            ff7.hf[s].sl_header[35] = ((ff7.slot[s].time/60%60)%10)+0x4F;
            //above is to set the playtime
            saveFileFull(fileName);
        }
    }
    else if(ff7.savetype==3)
    {
        QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 MC SaveGame"), settings.value("save_emu_path").toString(),
        tr("FF7 MC SaveGame(*.mcr *.mcd *.mc *.ddf *.ps *.psm)"));

        if (!fileName.isEmpty())
        {

            QByteArray mc_header_2;
            mc_header_2.append("MC");
            quint8 xor_byte = 0x00;
            int index=2;
            for(int k=0; k<125;k++){mc_header_2.append(ff7.file_header_mc[k+index]);}
            xor_byte= 0x00;
            for(int x=0;x<127;x++){xor_byte^=mc_header_2[x];}
            //write xor byte..
            mc_header_2.append(xor_byte);
            // thats a normal header
            for(int i=0;i<15;i++)
            {
                //calc xor byte..
                index= (128 +(128*i));
             if(ff7.SG_Region_String[i].contains("00867") ||ff7.SG_Region_String[i].contains("00869") ||
                ff7.SG_Region_String[i].contains("00900") ||ff7.SG_Region_String[i].contains("94163") ||
                ff7.SG_Region_String[i].contains("00700") ||ff7.SG_Region_String[i].contains("01057"))
                {
                 QByteArray temp;

                    temp.resize(10);
                    temp[0]=0x51;temp[1]=0x00;temp[2]=0x00;temp[3]=0x00;temp[4]=0x00;
                    temp[5]=0x20;temp[6]=0x00;temp[7]=0x00;temp[8]=0xFF;temp[9]=0xFF;
                    mc_header_2.append(temp);
                    mc_header_2.append(ff7.SG_Region_String[i]);
                    temp.resize(98);
                    for(int f=0;f<98;f++){temp[f]=0x00;}
                    mc_header_2.append(temp);
                    xor_byte = 0x00;
                    for(int x=0;x<127;x++){xor_byte^=mc_header_2[x+index];}
                    mc_header_2.append(xor_byte);
                    switch(i)
                    {
                    case 0:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S01[P];}
                        break;

                    case 1:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S02[P];}
                        break;

                    case 2:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S03[P];}
                        break;

                    case 3:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S04[P];}
                        break;

                    case 4:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S05[P];}
                        break;

                    case 5:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S06[P];}
                        break;

                    case 6:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S07[P];}
                        break;

                    case 7:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S08[P];}
                        break;

                    case 8:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S09[P];}
                        break;

                    case 9:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S10[P];}
                        break;

                    case 10:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S11[P];}
                        break;

                    case 11:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S12[P];}
                        break;

                    case 12:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S13[P];}
                        break;

                    case 13:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S14[P];}
                        break;

                    case 14:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S15[P];}
                        break;
                    }
                    if((ff7.slot[i].time/3600)>99){ff7.hf[i].sl_header[27]=0x58;ff7.hf[i].sl_header[29]=0x58;}
                    else
                    {
                        ff7.hf[i].sl_header[27] = ((ff7.slot[i].time/3600)/10)+0x4F;
                        ff7.hf[i].sl_header[29] = ((ff7.slot[i].time/3600)%10)+0x4F;
                    }
                    ff7.hf[i].sl_header[33] = ((ff7.slot[i].time/60%60)/10)+0x4F;
                    ff7.hf[i].sl_header[35] = ((ff7.slot[i].time/60%60)%10)+0x4F;
                } // write string if found

                else{for(int j=0;j<128;j++){mc_header_2.append(ff7.file_header_mc[index+j]);}} //write what ever is in the header.(NOT FF7 SAVE)

            }
            index=2048;
            for(int i=0;i<6143;i++){mc_header_2.append(ff7.file_header_mc[index+i]);}// fill the remainder
            memcpy(&ff7.file_header_mc,mc_header_2,0x2000);


            saveFileFull(fileName);
        }
    }
    else if(ff7.savetype==4)
    {
        QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 PSV SaveGame"), "",
        tr("FF7 PSV SaveGame(*.psv)"));
        if (!fileName.isEmpty())
            saveFileFull(fileName);
    }
    else if(ff7.savetype==5)
    {
        QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7  PSP SaveGame"), "",
        tr("FF7 PSP SaveGame(*.vmp)"));
        if (!fileName.isEmpty())
        {
            QByteArray mc_header_2;
            for(int i=0; i<0x80; i++){mc_header_2.append(ff7.file_header_psp[i]);}
            quint8 xor_byte = 0x00;
            int index=0x82;
            mc_header_2.append("MC");
            for(int k=2; k<125;k++){mc_header_2.append(ff7.file_header_psp[k+index]);}
            xor_byte= 0x00;
            for(int x=128;x<255;x++){xor_byte^=mc_header_2[x];}
            //write xor byte..
            mc_header_2.append(xor_byte);
            // thats a normal header
            for(int i=0;i<15;i++)
            {
                //calc xor byte..
                index= (128 +(128*i))+ (0x80);
             if(ff7.SG_Region_String[i].contains("00867") ||ff7.SG_Region_String[i].contains("00869") ||
                ff7.SG_Region_String[i].contains("00900") ||ff7.SG_Region_String[i].contains("94163") ||
                ff7.SG_Region_String[i].contains("00700") ||ff7.SG_Region_String[i].contains("01057"))
                {
                    QByteArray temp;
                    temp.resize(10);
                    temp[0]= 0x51;temp[1]=0x00;temp[2]=0x00;temp[3]=0x00;temp[4]=0x00;
                    temp[5]=0x20;temp[6]=0x00;temp[7]=0x00;temp[8]=0xFF;temp[9]=0xFF;

                    mc_header_2.append(temp);
                    mc_header_2.append(ff7.SG_Region_String[i]);
                    temp.resize(98);
                    for(int f=0;f<98;f++){temp[f]=0x00;}
                    mc_header_2.append(temp);
                    xor_byte = 0x00;
                    for(int x=0;x<127;x++){xor_byte^=mc_header_2[x+index];}
                    mc_header_2.append(xor_byte);
                    switch(i)
                    {
                    case 0:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S01[P];}
                        break;

                    case 1:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S02[P];}
                        break;

                    case 2:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S03[P];}
                        break;

                    case 3:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S04[P];}
                        break;

                    case 4:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S05[P];}
                        break;

                    case 5:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S06[P];}
                        break;

                    case 6:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S07[P];}
                        break;

                    case 7:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S08[P];}
                        break;

                    case 8:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S09[P];}
                        break;

                    case 9:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S10[P];}
                        break;

                    case 10:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S11[P];}
                        break;

                    case 11:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S12[P];}
                        break;

                    case 12:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S13[P];}
                        break;

                    case 13:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S14[P];}
                        break;

                    case 14:
                        for(int P=0;P<512;P++){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S15[P];}
                        break;
                    }
                    if((ff7.slot[i].time/3600)>99){ff7.hf[i].sl_header[27]=0x58;ff7.hf[i].sl_header[29]=0x58;}
                    else
                    {
                        ff7.hf[i].sl_header[27] = ((ff7.slot[i].time/3600)/10)+0x4F;
                        ff7.hf[i].sl_header[29] = ((ff7.slot[i].time/3600)%10)+0x4F;
                    }
                    ff7.hf[i].sl_header[33] = ((ff7.slot[i].time/60%60)/10)+0x4F;
                    ff7.hf[i].sl_header[35] = ((ff7.slot[i].time/60%60)%10)+0x4F;
                } // write string if found

                else{for(int j=0;j<128;j++){mc_header_2.append(ff7.file_header_psp[index+j]);}}//write what ever is in the header (NOT FF7 SAVE DATA).

            }
            index=2048+0x80;
            for(int i=0;i<6143;i++){mc_header_2.append(ff7.file_header_psp[index+i]);}// fill the remainder
            memcpy(&ff7.file_header_psp,mc_header_2,0x2080);
            saveFileFull(fileName);
            //PUT PSP CHECKSUMING HERE ..
            QMessageBox::information(this,tr("PSP Save Notice"),tr("This File Does Not Have An Updated Checksum.It will not work on your PSP."));
        }
    }
    else {QMessageBox::warning(this, tr("Black Chocobo"),tr("Cannot save This Type of File"));}
}
/*~~~~~~~~~~~SHORT SAVE~~~~~~~~~~~~*/
void MainWindow::saveFileFull(const QString &fileName)
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
    fwrite(ff7.file_headerp,ff7.SG_HEADER,1,pfile);
    for(int si=0;si<ff7.SG_SLOT_NUMBER;si++)
    {
        fwrite(&ff7.hf[si].sl_header,ff7.SG_SLOT_HEADER,1,pfile);
        fwrite(&ff7.slot[si],ff7.SG_DATA_SIZE,1,pfile);
        fwrite(&ff7.hf[si].sl_footer,ff7.SG_SLOT_FOOTER,1,pfile);
    }
    fwrite(ff7.file_footerp,ff7.SG_FOOTER,1,pfile);
    fclose(pfile);
    fix_sum(fileName);
}
/*~~~~~~~~END SHORT SAVE~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~New_Game~~~~~~~~~~~*/
void MainWindow::on_actionNew_Game_triggered()
{
            QFile file(settings.value("default_save_file").toString());
            if(!file.open(QFile::ReadOnly))
            {
                QMessageBox::warning(this, tr("Black Chocobo"),
                tr("Cannot read file %1:\n%2 Be Sure its is a Raw PSX Save")
                .arg(settings.value("default_save_file").toString()).arg(file.errorString()));
                return;
            }
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        QByteArray temp; // create a temp to be used when needed
        int index = 0x200;
        temp = ff7file.mid(index,0x10f4);
        memcpy(&ff7.slot[s],temp,0x10f4);
    if(ff7.SG_Region_String[s] == ""){ff7.SG_Region_String[s] = "BASCUS-94163FF7-S01";}
    guirefresh();
}
/*~~~~~~~~~~End New_Game~~~~~~~~~~~*/
/*~~~~~~~~~~New Game + ~~~~~~~~~~~~*/
void MainWindow::on_actionNew_Game_Plus_triggered()
{
    QFile file(settings.value("default_save_file").toString());
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Black Chocobo"),
        tr("Cannot read file %1:\n%2., Be Sure its is a Raw PSX Save")
        .arg(settings.value("default_save_file").toString()).arg(file.errorString()));
        return;
    }
    QByteArray ff7file;
    ff7file = file.readAll(); //put all data in temp raw file
    QByteArray temp; // create a temp to be used when needed
    int index = 0x200;
    temp = ff7file.mid(index,0x10f4); // dump file -> temp
    memcpy(&bufferslot,temp,0x10f4);  // copy temp to the buffer slot
    buffer_region = ff7.SG_Region_String[s];
    ui->line_location->setText(tr("New Game +"));
    memcpy(&bufferslot.desc,&ff7.slot[s].desc,0x44); // keep a old preview
    memcpy(&bufferslot.colors,&ff7.slot[s].colors,12); // keep old colors.
    for(int i=0;i<9;i++) // keep all old character info.
    {
        if((i==6)||(i==7))// except we have to export cait sith and vincent.the game needs y.cloud/seppie,for the flash back.
        {
            QString fileName;
            if(i==6) //export cait sith. cait sith's stats are only generated when he joins the party.
            {
                    fileName = settings.value("char_stat_folder").toString();
                    fileName.append("/");
                    fileName.append(filename);
                    fileName.append("-cait_sith");
                    if(ff7.savetype == 1 || ff7.savetype == 3 || ff7.savetype ==5)
                    {
                        fileName.append("-");
                        QString str;
                        str.setNum(s,10);
                        fileName.append(str);
                    }
                }
            else if(i==7)// export vincent. vincent's stats are only generated when he joins the party.
                {
                    fileName = settings.value("char_stat_folder").toString();
                    fileName.append("/");
                    fileName.append(filename);
                    fileName.append("-vincent");
                    if(ff7.savetype == 1 || ff7.savetype == 3 || ff7.savetype ==5)
                    {
                        fileName.append("-");
                        QString str;
                        str.setNum(s,10);
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
            fwrite(&ff7.slot[s].chars[i],132,1,pfile);
            fclose(pfile);

        }
        else{memcpy(&bufferslot.chars[i],&ff7.slot[s].chars[i],0x84);} // normal character
    }
    memcpy(&bufferslot.items,ff7.slot[s].items,640);// copy items
    memcpy(&bufferslot.materias,ff7.slot[s].materias,800); // copy materia
    bufferslot.gil = ff7.slot[s].gil; // copy gil
    bufferslot.battles = ff7.slot[s].battles; // copy battle count
    bufferslot.runs = ff7.slot[s].runs; // copy run count
    bufferslot.gp = ff7.slot[s].gp; // copy gp
    //copy chocobo info.
    bufferslot.stables = ff7.slot[s].stables;
    bufferslot.stablesoccupied = ff7.slot[s].stablesoccupied;
    for(int i=0;i<4;i++){memcpy(&bufferslot.chocobos[i],&ff7.slot[s].chocobos[i],0x10);}
    memcpy(&bufferslot.chocobonames,&ff7.slot[s].chocobonames,36);
    memcpy(&bufferslot.chocostaminas,&ff7.slot[s].chocostaminas,12);
    for(int i=0;i<2;i++){memcpy(&bufferslot.choco56,&ff7.slot[s].choco56,0x10);}
    // copy options
    bufferslot.battlespeed =ff7.slot[s].battlespeed;
    bufferslot.battlemspeed =ff7.slot[s].battlemspeed;
    bufferslot.options1 = ff7.slot[s].options1;
    bufferslot.options2 = ff7.slot[s].options2;
    memcpy(&bufferslot.controller_map,&ff7.slot[s].controller_map,16);
    bufferslot.fieldmspeed = ff7.slot[s].fieldmspeed;
    /*~~ buffer now ready to be copied~*/
    memcpy(&ff7.slot[s],&bufferslot,0x10f4); // copy buffer to the current slot.
    guirefresh();
}
/*~~~~~~~~~~End New_Game +~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~EXPORT PC~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionExport_PC_Save_activated()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 SaveGame"),  settings.value("export_pc").toString() ,
    tr("FF7 SaveGame(*.ff7)")); // Only Allow PC save Since we are going to make one
    if (fileName ==""){return;}// catch if Cancel is pressed
    if(ff7.SG_TYPE !="PC")
    {
        ui->combo_control->setCurrentIndex(0); // if not pc then chance of breaking controls.
        // no need to change if its pc already.
        ff7.SG_SIZE          = FF7_PC_SAVE_GAME_SIZE;
        ff7.SG_HEADER        = FF7_PC_SAVE_GAME_HEADER;
        ff7.SG_FOOTER        = FF7_PC_SAVE_GAME_FOOTER;
        ff7.SG_DATA_SIZE     = FF7_PC_SAVE_GAME_DATA_SIZE;
        ff7.SG_SLOT_HEADER   = FF7_PC_SAVE_GAME_SLOT_HEADER;
        ff7.SG_SLOT_FOOTER   = FF7_PC_SAVE_GAME_SLOT_FOOTER;
        ff7.SG_SLOT_SIZE     = FF7_PC_SAVE_GAME_SLOT_SIZE;
        ff7.SG_SLOT_NUMBER   = FF7_PC_SAVE_GAME_SLOT_NUMBER;
        ff7.SG_TYPE          = "PC";
        ff7.file_headerp     = ff7.file_header_pc;           //pointer to pc file header
        ff7.file_footerp     = ff7.file_footer_pc;           //pointer to pc file footer
    }
    fix_pc_bytemask();
    /*~~~~~~~~~~~~~~~SHORT SAVE - SITHLORD48~~~~~~~~~~~~*/
    QFile file(fileName);
    if(!file.open(QFile::ReadWrite))
    {
        QMessageBox::warning(this, tr("Black Chocobo"),
        tr("Cannot write file %1:\n%2.")
            .arg(fileName)
            .arg(file.errorString()));
        return;
    }
    FILE *pfile; // this section is starting to work correctly!
    pfile = fopen(fileName.toAscii(),"wb");
    fwrite(ff7.file_headerp,9,1,pfile);
    for(int si=0;si<15;si++)
    {
        if(ff7.SG_Region_String[si].contains("00867") || ff7.SG_Region_String[si].contains("00869") ||
           ff7.SG_Region_String[si].contains("00900") || ff7.SG_Region_String[si].contains("94163") ||
           ff7.SG_Region_String[si].contains("00700") || ff7.SG_Region_String[si].contains("01057"))
           {
            Write:
            fwrite(ff7.hf[si].sl_header,ff7.SG_SLOT_HEADER,1,pfile);
            fwrite(&ff7.slot[si],ff7.SG_DATA_SIZE,1,pfile);
            fwrite(ff7.hf[si].sl_footer,ff7.SG_SLOT_FOOTER,1,pfile);
           }
        else {clearslot(si);    goto Write;} //the program is incomplete with out one use of a goto.
    }
    fwrite(ff7.file_footerp,ff7.SG_FOOTER,1,pfile);
    fclose(pfile);
    fix_sum(fileName);

    /*~~~~~~~~~~~END SHORT SAVE -SITHLORD48~~~~~~~~~~~~~*/
}
/*~~~~~~~~~~~~~~~~~EXPORT PSX~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionExport_PSX_activated()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 SaveGame"), ff7.SG_Region_String[s],
    tr("BASCUS-94163FF7-Sxx(*-S*);;BESCES-00867FF7-Sxx(*-S*);;BESCES-00869FF7-Sxx(*-S*);;BESCES-00900FF7-Sxx(*-S*);;BISLPS-00700FF7-Sxx(*-S*);;BISLPS-01057FF7-Sxx(*-S*)"));//;;BASCUS-94163FF7-S07(*-S07);;BASCUS-94163FF7-S08(*-S08);;BASCUS-94163FF7-S09(*-S09);;BASCUS-94163FF7-S10(*-S10);;BASCUS-94163FF7-S11(*-S11);;BASCUS-94163FF7-S12(*-S12);;BASCUS-94163FF7-S13(*-S13);;BASCUS-94163FF7-S14(*-S14);;BASCUS-94163FF7-S15(*-S15)")); // Only Allow PSX save slots Since we are going to force its creation.
    if(fileName ==""){return;}

    if(ff7.SG_TYPE != "PSX")
    {
        ui->combo_control->setCurrentIndex(0);

        ff7.SG_SIZE          = FF7_PSX_SAVE_GAME_SIZE;
        ff7.SG_HEADER        = FF7_PSX_SAVE_GAME_HEADER;
        ff7.SG_FOOTER        = FF7_PSX_SAVE_GAME_FOOTER;
        ff7.SG_DATA_SIZE     = FF7_PSX_SAVE_GAME_DATA_SIZE;
        ff7.SG_SLOT_HEADER   = FF7_PSX_SAVE_GAME_SLOT_HEADER;
        ff7.SG_SLOT_FOOTER   = FF7_PSX_SAVE_GAME_SLOT_FOOTER;
        ff7.SG_SLOT_SIZE     = FF7_PSX_SAVE_GAME_SLOT_SIZE;
        ff7.SG_SLOT_NUMBER   = FF7_PSX_SAVE_GAME_SLOT_NUMBER;
        ff7.SG_TYPE          = "PSX";
        ff7.file_headerp     = ff7.file_header_psx;           //pointer to psx file header
        ff7.file_footerp     = ff7.file_footer_psx;           //pointer to psx file footer
    }
    /*~~~~~~~ SHORT SAVE - SITHLORD48 ~~~~~~~~~*/
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

    QByteArray temp; temp.resize(512);//

         if(fileName.endsWith("S01")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S01[i];}}
    else if(fileName.endsWith("S02")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S02[i];}}
    else if(fileName.endsWith("S03")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S03[i];}}
    else if(fileName.endsWith("S04")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S04[i];}}
    else if(fileName.endsWith("S05")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S05[i];}}
    else if(fileName.endsWith("S06")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S06[i];}}
    else if(fileName.endsWith("S07")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S07[i];}}
    else if(fileName.endsWith("S08")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S08[i];}}
    else if(fileName.endsWith("S09")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S09[i];}}
    else if(fileName.endsWith("S10")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S10[i];}}
    else if(fileName.endsWith("S11")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S11[i];}}
    else if(fileName.endsWith("S12")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S12[i];}}
    else if(fileName.endsWith("S13")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S13[i];}}
    else if(fileName.endsWith("S14")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S14[i];}}
    else if(fileName.endsWith("S15")){for(int i=0;i<256;i++){temp[i] = PSX_SAVE_GAME_FILE_HEADER_S15[i];}}
    else{QMessageBox::information(this,tr("Bad Psx Save Name"), tr("Can't Decide On What Header to Write, Please Add the suffix -SXX (where x= 01-15, with leading 0 if < 10) A Header for that slot number will be written to the save"));return;}

    for(int i=256;i<512;i++){temp[i]= 0x00;};

    if(ui->sb_time_hour->value()>99){temp[27]=0x58;temp[29]=0x58;}
    else
    {
        temp[27] = (ui->sb_time_hour->value()/10)+0x4F;
        temp[29] = (ui->sb_time_hour->value()%10)+0x4F;
    }
    temp[33] = (ui->sb_time_min->value()/10)+0x4F;
    temp[35] = (ui->sb_time_min->value()%10)+0x4F;

    fwrite(temp,512,1,pfile); // Write Header.

    fwrite(&ff7.slot[s],ff7.SG_DATA_SIZE,1,pfile);
    fwrite(ff7.hf[s].sl_footer,ff7.SG_SLOT_FOOTER,1,pfile);
    fwrite(ff7.file_footerp,ff7.SG_FOOTER,1,pfile);
    fclose(pfile);
    fix_sum(fileName);
    /*~~~~END NEW SHORT SAVE -SITHLORD48- V.1.4~~~~*/
}
/*~~~~~Export Mcr/Mcd~~~~~~*/
void MainWindow::on_actionExport_MC_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 MC SaveGame"), settings.value("save_emu_path").toString(),
    tr("FF7 MC SaveGame(*.mcr *.mcd *.mc *.ddf *.ps *.psm)"));

    if(fileName==""){return;}

    if(ff7.SG_TYPE != "MC")
    {
        ui->combo_control->setCurrentIndex(0);

        ff7.SG_SIZE          = FF7_MC_SAVE_GAME_SIZE;
        ff7.SG_HEADER        = FF7_MC_SAVE_GAME_HEADER;
        ff7.SG_FOOTER        = FF7_MC_SAVE_GAME_FOOTER;
        ff7.SG_DATA_SIZE     = FF7_MC_SAVE_GAME_DATA_SIZE;
        ff7.SG_SLOT_HEADER   = FF7_MC_SAVE_GAME_SLOT_HEADER;
        ff7.SG_SLOT_FOOTER   = FF7_MC_SAVE_GAME_SLOT_FOOTER;
        ff7.SG_SLOT_SIZE     = FF7_MC_SAVE_GAME_SLOT_SIZE;
        ff7.SG_SLOT_NUMBER   = FF7_MC_SAVE_GAME_SLOT_NUMBER;
        ff7.SG_TYPE          = "MC";
        ff7.file_headerp     = ff7.file_header_mc;           //pointer to mc file header
        ff7.file_footerp     = ff7.file_footer_mc;           //pointer to mc file footer
    }
        QByteArray mc_header_2;
        mc_header_2.append("MC");
        quint8 xor_byte = 0x00;
        int index=2;
        for(int k=0; k<125;k++){mc_header_2.append(ff7.file_header_mc[k+index]);}
        xor_byte= 0x00;
        for(int x=0;x<127;x++){xor_byte^=mc_header_2[x];}
        //write xor byte..
        mc_header_2.append(xor_byte);
        // thats a normal header
        for(int i=0;i<15;i++)
        {
            //calc xor byte..
            index= (128 +(128*i));
         if(ff7.SG_Region_String[i].contains("00867") || ff7.SG_Region_String[i].contains("00869") ||
            ff7.SG_Region_String[i].contains("00900") || ff7.SG_Region_String[i].contains("94163") ||
            ff7.SG_Region_String[i].contains("00700") || ff7.SG_Region_String[i].contains("01057"))
            {
                QByteArray temp;
                temp.resize(10);
                temp[0]=0x51;temp[1]=0x00;temp[2]=0x00;temp[3]=0x00;temp[4]=0x00;
                temp[5]=0x20;temp[6]=0x00;temp[7]=0x00;temp[8]=0xFF;temp[9]=0xFF;

                mc_header_2.append(temp);
                mc_header_2.append(ff7.SG_Region_String[i]);
                temp.resize(98);
                for(int f=0;f<98;f++){temp[f]=0x00;}
                mc_header_2.append(temp);
                xor_byte = 0x00;
                for(int x=0;x<127;x++){xor_byte^=mc_header_2[x+index];}
                mc_header_2.append(xor_byte);
                switch(i)
                {
                case 0:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S01[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 1:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S02[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 2:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S03[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 3:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S04[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 4:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S05[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 5:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S06[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 6:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S07[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 7:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S08[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 8:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S09[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 9:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S10[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 10:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S11[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 11:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S12[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 12:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S13[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 13:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S14[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                case 14:
                    for(int P=0;P<512;P++)
                    {
                        if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S15[P];}
                        else{ff7.hf[i].sl_header[P]= 0x00;}
                    }
                    break;
                }

            if((ff7.slot[i].time/3600)>99){ff7.hf[i].sl_header[27]=0x58;ff7.hf[i].sl_header[29]=0x58;}
            else
            {
                ff7.hf[i].sl_header[27] = ((ff7.slot[i].time/3600)/10)+0x4F;
                ff7.hf[i].sl_header[29] = ((ff7.slot[i].time/3600)%10)+0x4F;
            }
            ff7.hf[i].sl_header[33] = ((ff7.slot[i].time/60%60)/10)+0x4F;
            ff7.hf[i].sl_header[35] = ((ff7.slot[i].time/60%60)%10)+0x4F;

            } // write string if found

            else{for(int j=0;j<128;j++){mc_header_2.append(ff7.file_header_mc[index+j]);}} //write what ever is in the header.(NOT FF7 SAVE)

        }
        index=2048;
        for(int i=0;i<6143;i++){mc_header_2.append(ff7.file_header_mc[index+i]);}// fill the remainder
        memcpy(&ff7.file_header_mc,mc_header_2,0x2000);

        saveFileFull(fileName);
}
/*~~~~~~~~~~~ START CHECKSUM VEGETA~~~~~~~~~~~*/
void fix_sum(const QString &fileName)
{
    void * memory;
    long file_size;
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite )){return;}
    QDataStream out (&file);
    out.setByteOrder(QDataStream::LittleEndian);
    file.seek(0);//Set pointer to the Beggining
    QByteArray ff7savefile;
    ff7savefile = file.readAll(); //put all data in temp raw file
    file_size = file.size();//Get File Size
    memory = (void*) malloc(ff7.SG_SIZE);//Memory Allocation
    if (!memory){return;}
    file.seek(0);
    memcpy(memory,ff7savefile.mid(0x00000,ff7.SG_SIZE),ff7.SG_SIZE);
    //Do checksum foreach slot
    for(int i=0, checksum=0; i<ff7.SG_SLOT_NUMBER; i++)
    {
        char * data_pointer = ((char*)memory + ff7.SG_HEADER + ff7.SG_SLOT_SIZE*i + ff7.SG_SLOT_HEADER + 0x04);
        checksum = ff7__checksum(data_pointer); //2 Bytes checksum (a 16-bit Byte checksum)
        if(checksum != 0x4D1D) //if is a blank slot don't write checksum!
        {
            int index = ff7.SG_HEADER + ff7.SG_SLOT_SIZE*i + ff7.SG_SLOT_HEADER;
            file.seek(index);
            out << checksum;
        }
    }
    file.close();
    free(memory);
}
/*~~~~~~~~~~~~ END CHECKSUM VEGETA~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END LOAD/SAVE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MENU ACTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~LANGUAGE ACTIONS~~~~~~~~~~~~~~*/
void MainWindow::on_action_Lang_en_triggered()
{
    //clear other lang
    ui->action_Lang_es->setIcon(QIcon(":/icon/es_unsel"));
    ui->action_Lang_es->setChecked(0);
    ui->action_Lang_fr->setIcon(QIcon(":/icon/fr_unsel"));
    ui->action_Lang_fr->setChecked(0);
    settings.setValue("lang","en");
    ui->action_Lang_en->setIcon(QIcon(":/icon/us_sel"));
    QMessageBox::information(this,"Language Changed","You Must Restart For The Language to Change");
}
void MainWindow::on_action_Lang_es_triggered()
{
    ui->action_Lang_en->setChecked(0);
    ui->action_Lang_en->setIcon(QIcon(":/icon/us_unsel"));
    ui->action_Lang_fr->setChecked(0);
    ui->action_Lang_fr->setIcon(QIcon(":/icon/fr_unsel"));
    settings.setValue("lang","es");
    ui->action_Lang_es->setIcon(QIcon(":/icon/es_sel"));
    QMessageBox::information(this,"Idioma Cambiado","Debe reiniciar Para el cambio de idioma");

}
void MainWindow::on_action_Lang_fr_triggered()
{
    ui->action_Lang_en->setChecked(0);
    ui->action_Lang_en->setIcon(QIcon(":/icon/us_unsel"));
    ui->action_Lang_es->setChecked(0);
    ui->action_Lang_es->setIcon(QIcon(":/icon/es_unsel"));
    settings.setValue("lang","fr");
    ui->action_Lang_fr->setIcon(QIcon(":/icon/fr_sel"));
    QMessageBox::information(this,"Langue Modifiée","Vous Devez Redemarrer Pour Changer la Langue");
}
/*~~~~~~~~~~~END LANGUAGE ACTIONS~~~~~~~~~~*/

void MainWindow::on_actionCopy_Slot_activated()
{
    memcpy(&bufferslot,&ff7.slot[s],0x10f4);
    buffer_region = ff7.SG_Region_String[s];
}

void MainWindow::on_actionPaste_Slot_activated()
{
    memcpy(&ff7.slot[s],&bufferslot,0x10f4);
    ff7.SG_Region_String[s] = buffer_region;
    ff7.SG_Region_String[s].chop(2);
    switch(s)
    {
        case 0:ff7.SG_Region_String[s].append("01"); break;
        case 1:ff7.SG_Region_String[s].append("02"); break;
        case 2:ff7.SG_Region_String[s].append("03"); break;
        case 3:ff7.SG_Region_String[s].append("04"); break;
        case 4:ff7.SG_Region_String[s].append("05"); break;
        case 5:ff7.SG_Region_String[s].append("06"); break;
        case 6:ff7.SG_Region_String[s].append("07"); break;
        case 7:ff7.SG_Region_String[s].append("08"); break;
        case 8:ff7.SG_Region_String[s].append("09"); break;
        case 9:ff7.SG_Region_String[s].append("10"); break;
        case 10:ff7.SG_Region_String[s].append("11"); break;
        case 11:ff7.SG_Region_String[s].append("12"); break;
        case 12:ff7.SG_Region_String[s].append("13"); break;
        case 13:ff7.SG_Region_String[s].append("14"); break;
        case 14:ff7.SG_Region_String[s].append("15"); break;
    }
    guirefresh();
}

void MainWindow::on_actionSlot_01_activated(){s=0; guirefresh();}
void MainWindow::on_actionSlot_02_activated(){s=1; guirefresh();}
void MainWindow::on_actionSlot_03_activated(){s=2; guirefresh();}
void MainWindow::on_actionSlot_04_activated(){s=3; guirefresh();}
void MainWindow::on_actionSlot_05_activated(){s=4; guirefresh();}
void MainWindow::on_actionSlot_06_activated(){s=5; guirefresh();}
void MainWindow::on_actionSlot_07_activated(){s=6; guirefresh();}
void MainWindow::on_actionSlot_08_activated(){s=7; guirefresh();}
void MainWindow::on_actionSlot_09_activated(){s=8; guirefresh();}
void MainWindow::on_actionSlot_10_activated(){s=9; guirefresh();}
void MainWindow::on_actionSlot_11_activated(){s=10; guirefresh();}
void MainWindow::on_actionSlot_12_activated(){s=11; guirefresh();}
void MainWindow::on_actionSlot_13_activated(){s=12; guirefresh();}
void MainWindow::on_actionSlot_14_activated(){s=13; guirefresh();}
void MainWindow::on_actionSlot_15_activated(){s=14; guirefresh();}
void MainWindow::on_actionShow_Selection_Dialog_activated(){SlotSelect slotselect; slotselect.exec(); guirefresh();}
void MainWindow::on_actionClear_Slot_activated(){clearslot(s);  guirefresh();}
void MainWindow::on_actionPrevious_Slot_activated(){if (s > 0) {s--; guirefresh();}}
void MainWindow::on_actionNext_Slot_activated(){if (s<14){s++; guirefresh();}}

void MainWindow::on_action_show_test_data_toggled()
{
    if(ui->action_show_test_data->isChecked())
    {
        ui->tab_test->setEnabled(true);
        ui->tabWidget->setTabEnabled(8,1);
        testdata_refresh();
        ui->lbl_0x34->setVisible(true);
        ui->lbl_0x35->setVisible(true);
        ui->lbl_0x36->setVisible(true);
        ui->lbl_0x37->setVisible(true);
        ui->lcd_0x34->setVisible(true);
        ui->lcd_0x35->setVisible(true);
        ui->lcd_0x36->setVisible(true);
        ui->lcd_0x37->setVisible(true);
        ui->sb_bm_progress1->setEnabled(true);
        ui->sb_bm_progress2->setEnabled(true);
        ui->sb_bm_progress3->setEnabled(true);
        ui->btn_vincent->setEnabled(true);
        ui->cb_id->setEnabled(true);
        ui->btn_cait->setEnabled(true);

        settings.setValue("show_test",1);
        ui->action_show_test_data->setIcon(QIcon(":/icon/debug_sel"));
    }

    else
    {
        ui->tab_test->setEnabled(false);
        ui->tabWidget->setTabEnabled(8,0);
        ui->lbl_0x34->setVisible(false);
        ui->lbl_0x35->setVisible(false);
        ui->lbl_0x36->setVisible(false);
        ui->lbl_0x37->setVisible(false);
        ui->lcd_0x34->setVisible(false);
        ui->lcd_0x35->setVisible(false);
        ui->lcd_0x36->setVisible(false);
        ui->lcd_0x37->setVisible(false);
        ui->sb_bm_progress1->setEnabled(false);
        ui->sb_bm_progress2->setEnabled(false);
        ui->sb_bm_progress3->setEnabled(false);
        if(ff7.slot[s].chars[6].id == 9) {ui->btn_vincent->setEnabled(false);}
        ui->cb_id->setEnabled(false);
        if(ff7.slot[s].chars[7].id == 10) {ui->btn_cait->setEnabled(false);}
        settings.setValue("show_test",0);
        ui->action_show_test_data->setIcon(QIcon(":/icon/debug_unsel"));
    }
}
/*~~~~~~~~~~~~~SET USA MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_USA_triggered()
{
    if(!load)
    {
        if(!ui->action_Region_USA->isChecked())
        {
            ff7.SG_Region_String[s].clear();
            ui->lbl_sg_region->clear();
            ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
        }
        else
        {
            switch(s)
            {
                case 0:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S01"; break;
                case 1:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S02"; break;
                case 2:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S03"; break;
                case 3:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S04"; break;
                case 4:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S05"; break;
                case 5:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S06"; break;
                case 6:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S07"; break;
                case 7:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S08"; break;
                case 8:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S09"; break;
                case 9:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S10"; break;
                case 10:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S11"; break;
                case 11:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S12"; break;
                case 12:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S13"; break;
                case 13:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S14"; break;
                case 14:ff7.SG_Region_String[s] = "BASCUS-94163FF7-S15"; break;
            }
            ui->action_Region_PAL_Generic->setChecked(false);
            ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
            ui->action_Region_PAL_German->setChecked(false);
            ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
            ui->action_Region_PAL_Spanish->setChecked(false);
            ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
            ui->action_Region_JPN->setChecked(false);
            ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
            ui->action_Region_JPN_International->setChecked(false);
            ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
            ui->action_Region_USA->setIcon(QIcon(":/icon/us_sel"));
            ui->lbl_sg_region->setText(ff7.SG_Region_String[s]);
        }
    }
}
/*~~~~~~~~~~~~~SET PAL MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_Generic_triggered()
{
    if(!load)
    {
        if(!ui->action_Region_PAL_Generic->isChecked())
        {
            ff7.SG_Region_String[s].clear();
            ui->lbl_sg_region->clear();
            ui->action_Region_USA->setIcon(QIcon(":/icon/eu_unsel"));
        }
        else
        {
            switch(s)
            {
                case 0:ff7.SG_Region_String[s] = "BESCES-00867FF7-S01"; break;
                case 1:ff7.SG_Region_String[s] = "BESCES-00867FF7-S02"; break;
                case 2:ff7.SG_Region_String[s] = "BESCES-00867FF7-S03"; break;
                case 3:ff7.SG_Region_String[s] = "BESCES-00867FF7-S04"; break;
                case 4:ff7.SG_Region_String[s] = "BESCES-00867FF7-S05"; break;
                case 5:ff7.SG_Region_String[s] = "BESCES-00867FF7-S06"; break;
                case 6:ff7.SG_Region_String[s] = "BESCES-00867FF7-S07"; break;
                case 7:ff7.SG_Region_String[s] = "BESCES-00867FF7-S08"; break;
                case 8:ff7.SG_Region_String[s] = "BESCES-00867FF7-S09"; break;
                case 9:ff7.SG_Region_String[s] = "BESCES-00867FF7-S10"; break;
                case 10:ff7.SG_Region_String[s] = "BESCES-00867FF7-S11"; break;
                case 11:ff7.SG_Region_String[s] = "BESCES-00867FF7-S12"; break;
                case 12:ff7.SG_Region_String[s] = "BESCES-00867FF7-S13"; break;
                case 13:ff7.SG_Region_String[s] = "BESCES-00867FF7-S14"; break;
                case 14:ff7.SG_Region_String[s] = "BESCES-00867FF7-S15"; break;
            }
            ui->action_Region_USA->setChecked(false);
            ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
            ui->action_Region_PAL_German->setChecked(false);
            ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
            ui->action_Region_PAL_Spanish->setChecked(false);
            ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
            ui->action_Region_JPN->setChecked(false);
            ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
            ui->action_Region_JPN_International->setChecked(false);
            ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
            ui->lbl_sg_region->setText(ff7.SG_Region_String[s]);
            ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_sel"));
        }
    }
}
/*~~~~~~~~~~~~~SET PAL_German MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_German_triggered()
{
    if(!load)
    {
        if(!ui->action_Region_PAL_German->isChecked())
        {
            ff7.SG_Region_String[s].clear();
            ui->lbl_sg_region->clear();
            ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
        }
        else
        {
            switch(s)
            {
                case 0:ff7.SG_Region_String[s] = "BESCES-00869FF7-S01"; break;
                case 1:ff7.SG_Region_String[s] = "BESCES-00869FF7-S02"; break;
                case 2:ff7.SG_Region_String[s] = "BESCES-00869FF7-S03"; break;
                case 3:ff7.SG_Region_String[s] = "BESCES-00869FF7-S04"; break;
                case 4:ff7.SG_Region_String[s] = "BESCES-00869FF7-S05"; break;
                case 5:ff7.SG_Region_String[s] = "BESCES-00869FF7-S06"; break;
                case 6:ff7.SG_Region_String[s] = "BESCES-00869FF7-S07"; break;
                case 7:ff7.SG_Region_String[s] = "BESCES-00869FF7-S08"; break;
                case 8:ff7.SG_Region_String[s] = "BESCES-00869FF7-S09"; break;
                case 9:ff7.SG_Region_String[s] = "BESCES-00869FF7-S10"; break;
                case 10:ff7.SG_Region_String[s] = "BESCES-00869FF7-S11"; break;
                case 11:ff7.SG_Region_String[s] = "BESCES-00869FF7-S12"; break;
                case 12:ff7.SG_Region_String[s] = "BESCES-00869FF7-S13"; break;
                case 13:ff7.SG_Region_String[s] = "BESCES-00869FF7-S14"; break;
                case 14:ff7.SG_Region_String[s] = "BESCES-00869FF7-S15"; break;
            }
            ui->action_Region_USA->setChecked(false);
            ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
            ui->action_Region_PAL_Generic->setChecked(false);
            ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
            ui->action_Region_PAL_Spanish->setChecked(false);
            ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
            ui->action_Region_JPN->setChecked(false);
            ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
            ui->action_Region_JPN_International->setChecked(false);
            ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
            ui->lbl_sg_region->setText(ff7.SG_Region_String[s]);
            ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_sel"));
        }
    }
}
/*~~~~~~~~~~~~~SET PAL_Spanish MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_Spanish_triggered()
{
    if(!load)
    {
        if(!ui->action_Region_PAL_Spanish->isChecked())
        {
            ff7.SG_Region_String[s].clear();
            ui->lbl_sg_region->clear();
            ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
        }
        else
        {
            switch(s)
            {
                case 0:ff7.SG_Region_String[s] = "BESCES-00900FF7-S01"; break;
                case 1:ff7.SG_Region_String[s] = "BESCES-00900FF7-S02"; break;
                case 2:ff7.SG_Region_String[s] = "BESCES-00900FF7-S03"; break;
                case 3:ff7.SG_Region_String[s] = "BESCES-00900FF7-S04"; break;
                case 4:ff7.SG_Region_String[s] = "BESCES-00900FF7-S05"; break;
                case 5:ff7.SG_Region_String[s] = "BESCES-00900FF7-S06"; break;
                case 6:ff7.SG_Region_String[s] = "BESCES-00900FF7-S07"; break;
                case 7:ff7.SG_Region_String[s] = "BESCES-00900FF7-S08"; break;
                case 8:ff7.SG_Region_String[s] = "BESCES-00900FF7-S09"; break;
                case 9:ff7.SG_Region_String[s] = "BESCES-00900FF7-S10"; break;
                case 10:ff7.SG_Region_String[s] = "BESCES-00900FF7-S11"; break;
                case 11:ff7.SG_Region_String[s] = "BESCES-00900FF7-S12"; break;
                case 12:ff7.SG_Region_String[s] = "BESCES-00900FF7-S13"; break;
                case 13:ff7.SG_Region_String[s] = "BESCES-00900FF7-S14"; break;
                case 14:ff7.SG_Region_String[s] = "BESCES-00900FF7-S15"; break;
            }
            ui->action_Region_USA->setChecked(false);
            ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
            ui->action_Region_PAL_Generic->setChecked(false);
            ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
            ui->action_Region_PAL_German->setChecked(false);
            ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
            ui->action_Region_JPN->setChecked(false);
            ui->action_Region_JPN_International->setChecked(false);
            ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
            ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
            ui->lbl_sg_region->setText(ff7.SG_Region_String[s]);
            ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_sel"));

        }
    }
}
/*~~~~~~~~~~~~~SET JPN MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_JPN_triggered()
{
    if(!load)
    {
        if(!ui->action_Region_JPN->isChecked())
        {
            ff7.SG_Region_String[s].clear();
            ui->lbl_sg_region->clear();
            ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));

        }
        else
        {
            switch(s)
            {
                case 0:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S01"; break;
                case 1:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S02"; break;
                case 2:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S03"; break;
                case 3:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S04"; break;
                case 4:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S05"; break;
                case 5:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S06"; break;
                case 6:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S07"; break;
                case 7:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S08"; break;
                case 8:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S09"; break;
                case 9:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S10"; break;
                case 10:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S11"; break;
                case 11:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S12"; break;
                case 12:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S13"; break;
                case 13:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S14"; break;
                case 14:ff7.SG_Region_String[s] = "BISLPS-00700FF7-S15"; break;
            }
            ui->action_Region_USA->setChecked(false);
            ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
            ui->action_Region_PAL_Generic->setChecked(false);
            ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
            ui->action_Region_PAL_German->setChecked(false);
            ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
            ui->action_Region_PAL_Spanish->setChecked(false);
            ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
            ui->action_Region_JPN_International->setChecked(false);
            ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
            ui->lbl_sg_region->setText(ff7.SG_Region_String[s]);
            ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_sel"));
        }
    }
}
/*~~~~~~~~~~~~~SET JPN_International MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_JPN_International_triggered()
{
    if(!load)
    {
        if(!ui->action_Region_JPN_International->isChecked())
        {
            ff7.SG_Region_String[s].clear();
            ui->lbl_sg_region->clear();
            ui->action_Region_JPN_International->setIcon(QIcon(":icon/jp_unsel"));
        }
        else
        {
            switch(s)
            {
                case 0:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S01"; break;
                case 1:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S02"; break;
                case 2:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S03"; break;
                case 3:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S04"; break;
                case 4:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S05"; break;
                case 5:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S06"; break;
                case 6:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S07"; break;
                case 7:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S08"; break;
                case 8:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S09"; break;
                case 9:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S10"; break;
                case 10:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S11"; break;
                case 11:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S12"; break;
                case 12:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S13"; break;
                case 13:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S14"; break;
                case 14:ff7.SG_Region_String[s] = "BISLPS-01057FF7-S15"; break;
            }

            ui->action_Region_USA->setChecked(false);
            ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
            ui->action_Region_PAL_Generic->setChecked(false);
            ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
            ui->action_Region_PAL_German->setChecked(false);
            ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
            ui->action_Region_PAL_Spanish->setChecked(false);
            ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
            ui->action_Region_JPN->setChecked(false);
            ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
            ui->lbl_sg_region->setText(ff7.SG_Region_String[s]);
            ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_sel"));
        }
    }
}
void MainWindow::on_actionEdit_Paths_triggered()
{
    Options odialog; odialog.exec();

    QString style="QWidget#centralWidget{background-color: qlineargradient(spread:repeat, x1:1, y1:1, x2:0, y2:0, stop:0.0625 rgba(";
    style.append(settings.value("color1_r").toString());
    style.append(",");
    style.append(settings.value("color1_g").toString());
    style.append(",");
    style.append(settings.value("color1_b").toString());
    style.append(", 255), stop:0.215909 rgba(");
    style.append(settings.value("color2_r").toString());
    style.append(",");
    style.append(settings.value("color2_g").toString());
    style.append(",");
    style.append(settings.value("color2_b").toString());
    style.append(", 255), stop:0.818182 rgba(");
    style.append(settings.value("color3_r").toString());
    style.append(",");
    style.append(settings.value("color3_g").toString());
    style.append(",");
    style.append(settings.value("color3_b").toString());
    style.append(", 255));}");
    ui->centralWidget->setStyleSheet(style);
}

void MainWindow::on_actionAbout_activated()
{
   about adialog; adialog.exec();
}

void MainWindow::on_actionAbout_Qt_activated()
{
    qApp->aboutQt();
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END MENU ACTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~GUI FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~Char Update~~~~~~~~~~*/
void MainWindow::charupdate(void)
{   //clear the text incase there is something there
    //mslotsel=0;
    ui->cb_id->setText("");
    ui->cb_id->setChecked(false);
    ui->cb_id->setVisible(false);
    if(curchar== 6)
    {
        ui->cb_id->setText(tr("Young Cloud"));
        ui->cb_id->setVisible(true);
        if (ff7.slot[s].chars[curchar].id == 9){ui->cb_id->setChecked(true); ui->lbl_avatar->setPixmap(QPixmap(":/icon/y_cloud_icon"));ui->btn_cait->setStyleSheet("image: url(:/icon/y_cloud_icon);");}
        else{ui->cb_id->setChecked(false);ui->lbl_avatar->setPixmap(QPixmap(":/icon/cait_icon"));ui->btn_cait->setStyleSheet("image: url(:/icon/cait_icon);");}
    }
    if(curchar==7)
    {
        ui->cb_id->setText(tr("Sephiroth"));
        ui->cb_id->setVisible(true);
        if (ff7.slot[s].chars[curchar].id == 10){ui->cb_id->setChecked(true);ui->lbl_avatar->setPixmap(QPixmap(":/icon/sep_icon"));ui->btn_vincent->setStyleSheet("image: url(:/icon/sep_icon);");}
        else{ui->cb_id->setChecked(false);ui->lbl_avatar->setPixmap(QPixmap(":/icon/vincent_icon"));ui->btn_vincent->setStyleSheet("image: url(:/icon/vincent_icon);");}
    }
    ui->line_name->clear();
    for (int n=0;n<12;n++)
    {
        if(chPC[ff7.slot[s].chars[curchar].name[n]] =='\0'){break;}
        else{this->ui->line_name->setText( this->ui->line_name->text() + chPC[ff7.slot[s].chars[curchar].name[n]]);}
    }
    ui->sb_exp->setValue(ff7.slot[s].chars[curchar].exp);
    ui->sb_next->setValue(ff7.slot[s].chars[curchar].expNext);
    ui->sb_lvl->setValue(ff7.slot[s].chars[curchar].level);
    ui->sb_curhp->setValue(ff7.slot[s].chars[curchar].curHP);
    ui->sb_curmp->setValue(ff7.slot[s].chars[curchar].curMP);
    ui->sb_maxhp->setValue(ff7.slot[s].chars[curchar].maxHP);
    ui->sb_maxmp->setValue(ff7.slot[s].chars[curchar].maxMP);
    ui->sb_str->setValue(ff7.slot[s].chars[curchar].strength);
    ui->sb_mag->setValue(ff7.slot[s].chars[curchar].magic);
    ui->sb_lck->setValue(ff7.slot[s].chars[curchar].luck);
    ui->sb_spr->setValue(ff7.slot[s].chars[curchar].spirit);
    ui->sb_dex->setValue(ff7.slot[s].chars[curchar].dexterity);
    ui->sb_vit->setValue(ff7.slot[s].chars[curchar].vitality);
    ui->sb_hp->setValue(ff7.slot[s].chars[curchar].baseHP);
    ui->sb_mp->setValue(ff7.slot[s].chars[curchar].baseMP);
    ui->sb_kills->setValue(ff7.slot[s].chars[curchar].kills);
    ui->sb_used1->setValue(ff7.slot[s].chars[curchar].timesused1);
    ui->sb_used2->setValue(ff7.slot[s].chars[curchar].timesused2);
    ui->sb_used3->setValue(ff7.slot[s].chars[curchar].timesused3);
    ui->sb_limitlvl->setValue(ff7.slot[s].chars[curchar].limitlevel);
    ui->slide_limit->setValue(ff7.slot[s].chars[curchar].limitbar);
    ui->cb_sadness->setChecked(0);
    ui->cb_fury->setChecked(0);
    ui->cb_front->setChecked(0);
    if(ff7.slot[s].chars[curchar].flags[0] == 16){ui->cb_sadness->setChecked(1);}
    if(ff7.slot[s].chars[curchar].flags[0] == 32){ui->cb_fury->setChecked(1);}
    if(ff7.slot[s].chars[curchar].flags[1] == 255){ui->cb_front->setChecked(1);}
    ui->combo_armor->setCurrentIndex(ff7.slot[s].chars[curchar].armor);
    ui->combo_acc->setCurrentIndex(ff7.slot[s].chars[curchar].accessory);
    ui->combo_weapon->clear();
    if(ff7.slot[s].chars[curchar].materias[8].id != 0xFF){ui->a_m_s1->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[8].id].image));}else{ui->a_m_s1->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[9].id != 0xFF){ui->a_m_s2->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[9].id].image));}else{ui->a_m_s2->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[10].id != 0xFF){ui->a_m_s3->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[10].id].image));}else{ui->a_m_s3->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[11].id != 0xFF){ui->a_m_s4->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[11].id].image));}else{ui->a_m_s4->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[12].id != 0xFF){ui->a_m_s5->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[12].id].image));}else{ui->a_m_s5->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[13].id != 0xFF){ui->a_m_s6->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[13].id].image));}else{ui->a_m_s6->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[14].id != 0xFF){ui->a_m_s7->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[14].id].image));}else{ui->a_m_s7->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[15].id != 0xFF){ui->a_m_s8->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[15].id].image));}else{ui->a_m_s8->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[0].id != 0xFF){ui->w_m_s1->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[0].id].image));}else{ui->w_m_s1->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[1].id != 0xFF){ui->w_m_s2->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[1].id].image));}else{ui->w_m_s2->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[2].id != 0xFF){ui->w_m_s3->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[2].id].image));}else{ui->w_m_s3->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[3].id != 0xFF){ui->w_m_s4->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[3].id].image));}else{ui->w_m_s4->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[4].id != 0xFF){ui->w_m_s5->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[4].id].image));}else{ui->w_m_s5->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[5].id != 0xFF){ui->w_m_s6->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[5].id].image));}else{ui->w_m_s6->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[6].id != 0xFF){ui->w_m_s7->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[6].id].image));}else{ui->w_m_s7->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[7].id != 0xFF){ui->w_m_s8->setIcon(QIcon(Materias[ff7.slot[s].chars[curchar].materias[7].id].image));}else{ui->w_m_s8->setIcon(QIcon(QString("")));}
    if(ff7.slot[s].chars[curchar].materias[8].id != 0xFF){ui->a_m_s1->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[8].id].name);}else{ui->a_m_s1->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[9].id != 0xFF){ui->a_m_s2->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[9].id].name);}else{ui->a_m_s2->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[10].id != 0xFF){ui->a_m_s3->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[10].id].name);}else{ui->a_m_s3->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[11].id != 0xFF){ui->a_m_s4->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[11].id].name);}else{ui->a_m_s4->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[12].id != 0xFF){ui->a_m_s5->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[12].id].name);}else{ui->a_m_s5->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[13].id != 0xFF){ui->a_m_s6->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[13].id].name);}else{ui->a_m_s6->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[14].id != 0xFF){ui->a_m_s7->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[14].id].name);}else{ui->a_m_s7->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[15].id != 0xFF){ui->a_m_s8->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[15].id].name);}else{ui->a_m_s8->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[0].id != 0xFF){ui->w_m_s1->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[0].id].name);}else{ui->w_m_s1->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[1].id != 0xFF){ui->w_m_s2->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[1].id].name);}else{ui->w_m_s2->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[2].id != 0xFF){ui->w_m_s3->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[2].id].name);}else{ui->w_m_s3->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[3].id != 0xFF){ui->w_m_s4->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[3].id].name);}else{ui->w_m_s4->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[4].id != 0xFF){ui->w_m_s5->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[4].id].name);}else{ui->w_m_s5->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[5].id != 0xFF){ui->w_m_s6->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[5].id].name);}else{ui->w_m_s6->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[6].id != 0xFF){ui->w_m_s7->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[6].id].name);}else{ui->w_m_s7->setToolTip(QString("Empty"));}
    if(ff7.slot[s].chars[curchar].materias[7].id != 0xFF){ui->w_m_s8->setToolTip(Materias[ff7.slot[s].chars[curchar].materias[7].id].name);}else{ui->w_m_s8->setToolTip(QString("Empty"));}
    setarmorslots();
    setweaponslots();
    ui->sb_strbonus->setValue(ff7.slot[s].chars[curchar].strength_bonus);
    ui->sb_vitbonus->setValue(ff7.slot[s].chars[curchar].vitality_bonus);
    ui->sb_magbonus->setValue(ff7.slot[s].chars[curchar].magic_bonus);
    ui->sb_sprbonus->setValue(ff7.slot[s].chars[curchar].spirit_bonus);
    ui->sb_dexbonus->setValue(ff7.slot[s].chars[curchar].dexterity_bonus);
    ui->sb_lckbonus->setValue(ff7.slot[s].chars[curchar].luck_bonus);
    ui->pbar_level->setValue(ff7.slot[s].chars[curchar].flags[2]);
    ui->lcd_0x34->display(ff7.slot[s].chars[curchar].z_4[0]);
    ui->lcd_0x35->display(ff7.slot[s].chars[curchar].z_4[1]);
    ui->lcd_0x36->display(ff7.slot[s].chars[curchar].z_4[2]);
    ui->lcd_0x37->display(ff7.slot[s].chars[curchar].z_4[3]);
}
/*~~~~~~~END Char Update~~~~~~~~*/
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
    switch(Items[256 +ff7.slot[s].chars[curchar].armor].mslots)
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
    switch(Items[256 +ff7.slot[s].chars[curchar].armor].linked)
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

    switch(curchar)
    {
    case 0:{
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
            break;
        }
    case 7:{
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
    }
}
/*~~~~~End Armor/Weapon Update~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~GUIREFRESH~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::guirefresh(void)
{
    load = true; //used to cheat the removal of "apply buttons"
    /*~~~~Check for SG type and ff7~~~~*/
    if(ff7.savetype == 3 || ff7.savetype == 5 )
    {
        if(ff7.SG_Region_String[s].contains("00867") || ff7.SG_Region_String[s].contains("00869") ||
           ff7.SG_Region_String[s].contains("00900") || ff7.SG_Region_String[s].contains("94163") ||
           ff7.SG_Region_String[s].contains("00700") || ff7.SG_Region_String[s].contains("01057") ||
           ff7.SG_Region_String[s].isEmpty())    {/*FF7 Save Game*/ }
        else
        {
            errbox error;
            switch(error.exec())
            {
            case 0://View Anyway..
                QMessageBox::information(this,tr("Ingoring Non FF7 Save"),tr("Be Cautious This Might Not Work."));
                break;

            case 1://Previous or next was clicked
                guirefresh();
                break;

            case 2://export as psx
                SlotSelect selector;
                selector.exec();
                guirefresh();
            break;
}


        }//NOT FF7
    }
/*~~~~ END Type Check~~~~*/
    ui->lcd_current_slot->display(s+1);
    //dialog preview
    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));
    //make the preview nice
    ui->cb_replay->setCurrentIndex(0);
    ui->sb_bm_progress1->setValue(ff7.slot[s].bm_progress1);
    ui->sb_bm_progress2->setValue(ff7.slot[s].bm_progress2);
    ui->sb_bm_progress3->setValue(ff7.slot[s].bm_progress3);
    ui->sb_mprogress->setValue(ff7.slot[s].mprogress);

    if(ff7.slot[s].intbombing == 0x14){ui->cb_bombing_int->setChecked(Qt::Checked);}
    else if(ff7.slot[s].intbombing ==0x56){ui->cb_bombing_int->setChecked(Qt::Unchecked);}

    /*~~~~~Set Menu Items~~~~~~~~~~~~~~*/
    ui->actionImport_char->setEnabled(0);
    ui->actionExport_char->setEnabled(0);
    ui->actionSlot_01->setChecked(0);
    ui->actionSlot_01->setIcon(QIcon(":icon/1_unsel"));
    ui->actionSlot_02->setChecked(0);
    ui->actionSlot_02->setIcon(QIcon(":icon/2_unsel"));
    ui->actionSlot_03->setChecked(0);
    ui->actionSlot_03->setIcon(QIcon(":icon/3_unsel"));
    ui->actionSlot_04->setChecked(0);
    ui->actionSlot_04->setIcon(QIcon(":icon/4_unsel"));
    ui->actionSlot_05->setChecked(0);
    ui->actionSlot_05->setIcon(QIcon(":icon/5_unsel"));
    ui->actionSlot_06->setChecked(0);
    ui->actionSlot_06->setIcon(QIcon(":icon/6_unsel"));
    ui->actionSlot_07->setChecked(0);
    ui->actionSlot_07->setIcon(QIcon(":icon/7_unsel"));
    ui->actionSlot_08->setChecked(0);
    ui->actionSlot_08->setIcon(QIcon(":icon/8_unsel"));
    ui->actionSlot_09->setChecked(0);
    ui->actionSlot_09->setIcon(QIcon(":icon/9_unsel"));
    ui->actionSlot_10->setChecked(0);
    ui->actionSlot_10->setIcon(QIcon(":icon/10_unsel"));
    ui->actionSlot_11->setChecked(0);
    ui->actionSlot_11->setIcon(QIcon(":icon/11_unsel"));
    ui->actionSlot_12->setChecked(0);
    ui->actionSlot_12->setIcon(QIcon(":icon/12_unsel"));
    ui->actionSlot_13->setChecked(0);
    ui->actionSlot_13->setIcon(QIcon(":icon/13_unsel"));
    ui->actionSlot_14->setChecked(0);
    ui->actionSlot_14->setIcon(QIcon(":icon/14_unsel"));
    ui->actionSlot_15->setChecked(0);
    ui->actionSlot_15->setIcon(QIcon(":icon/15_unsel"));
    ui->menuRegion->setEnabled(0);
    ui->actionNew_Game_Plus->setEnabled(0);

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


    if (ff7.savetype ==1)//PC
    {
        ui->actionImport_char->setEnabled(1);
        ui->actionExport_char->setEnabled(1);
        ui->actionSave_File->setEnabled(1);
        ui->actionExport_PC_Save->setEnabled(1);
        ui->actionExport_PSX->setEnabled(1);
        ui->actionExport_MC->setEnabled(1);
        ui->actionFrom_PSV_Slot->setEnabled(1);
        ui->actionFrom_PSX_Slot->setEnabled(1);
        ui->actionNew_Game_Plus->setEnabled(1);
        ui->actionClear_Slot->setEnabled(1);
        ui->actionPaste_Slot->setEnabled(1);
        ui->actionCopy_Slot->setEnabled(1);
        ui->actionNext_Slot->setEnabled(1);
        ui->actionPrevious_Slot->setEnabled(1);
        ui->actionShow_Selection_Dialog->setEnabled(1);
        ui->menuRegion->setEnabled(1);
        ui->actionSlot_01->setEnabled(1);
        ui->actionSlot_02->setEnabled(1);
        ui->actionSlot_03->setEnabled(1);
        ui->actionSlot_04->setEnabled(1);
        ui->actionSlot_05->setEnabled(1);
        ui->actionSlot_06->setEnabled(1);
        ui->actionSlot_07->setEnabled(1);
        ui->actionSlot_08->setEnabled(1);
        ui->actionSlot_09->setEnabled(1);
        ui->actionSlot_10->setEnabled(1);
        ui->actionSlot_11->setEnabled(1);
        ui->actionSlot_12->setEnabled(1);
        ui->actionSlot_13->setEnabled(1);
        ui->actionSlot_14->setEnabled(1);
        ui->actionSlot_15->setEnabled(1);
    }
    else if (ff7.savetype == 2)//PSX
    {
        ui->actionImport_char->setEnabled(1);
        ui->actionExport_char->setEnabled(1);
        ui->actionSave_File->setEnabled(1);
        ui->actionExport_PC_Save->setEnabled(1);
        ui->actionExport_PSX->setEnabled(1);
        ui->actionExport_MC->setEnabled(1);
        ui->actionFrom_PSV_Slot->setEnabled(1);
        ui->actionFrom_PSX_Slot->setEnabled(1);
        ui->actionNew_Game_Plus->setEnabled(1);
        ui->actionClear_Slot->setEnabled(0);
        ui->actionPaste_Slot->setEnabled(1);
        ui->actionCopy_Slot->setEnabled(1);
        ui->actionNext_Slot->setEnabled(0);
        ui->actionPrevious_Slot->setEnabled(0);
        ui->actionShow_Selection_Dialog->setEnabled(0);
        ui->actionSlot_01->setEnabled(0);
        ui->actionSlot_02->setEnabled(0);
        ui->actionSlot_03->setEnabled(0);
        ui->actionSlot_04->setEnabled(0);
        ui->actionSlot_05->setEnabled(0);
        ui->actionSlot_06->setEnabled(0);
        ui->actionSlot_07->setEnabled(0);
        ui->actionSlot_08->setEnabled(0);
        ui->actionSlot_09->setEnabled(0);
        ui->actionSlot_10->setEnabled(0);
        ui->actionSlot_11->setEnabled(0);
        ui->actionSlot_12->setEnabled(0);
        ui->actionSlot_13->setEnabled(0);
        ui->actionSlot_14->setEnabled(0);
        ui->actionSlot_15->setEnabled(0);

    }
    else if (ff7.savetype == 3)//mcr/mcd
    {
        ui->actionImport_char->setEnabled(1);
        ui->actionExport_char->setEnabled(1);
        ui->actionSave_File->setEnabled(1);
        ui->actionExport_PC_Save->setEnabled(1);
        ui->actionExport_PSX->setEnabled(1);
        ui->actionExport_MC->setEnabled(1);
        ui->actionFrom_PSV_Slot->setEnabled(1);
        ui->actionFrom_PSX_Slot->setEnabled(1);
        ui->actionNew_Game_Plus->setEnabled(1);
        ui->actionClear_Slot->setEnabled(1);
        ui->actionPaste_Slot->setEnabled(1);
        ui->actionCopy_Slot->setEnabled(1);
        ui->actionNext_Slot->setEnabled(1);
        ui->actionPrevious_Slot->setEnabled(1);
        ui->actionShow_Selection_Dialog->setEnabled(1);
        ui->actionSlot_01->setEnabled(1);
        ui->actionSlot_02->setEnabled(1);
        ui->actionSlot_03->setEnabled(1);
        ui->actionSlot_04->setEnabled(1);
        ui->actionSlot_05->setEnabled(1);
        ui->actionSlot_06->setEnabled(1);
        ui->actionSlot_07->setEnabled(1);
        ui->actionSlot_08->setEnabled(1);
        ui->actionSlot_09->setEnabled(1);
        ui->actionSlot_10->setEnabled(1);
        ui->actionSlot_11->setEnabled(1);
        ui->actionSlot_12->setEnabled(1);
        ui->actionSlot_13->setEnabled(1);
        ui->actionSlot_14->setEnabled(1);
        ui->actionSlot_15->setEnabled(1);
    }
    else if (ff7.savetype ==4)//PSV
    {
        ui->actionImport_char->setEnabled(1);
        ui->actionExport_char->setEnabled(1);
        ui->actionSave_File->setEnabled(0); // read only
        ui->actionExport_PC_Save->setEnabled(1);
        ui->actionExport_PSX->setEnabled(1);
        ui->actionExport_MC->setEnabled(1);
        ui->actionFrom_PSV_Slot->setEnabled(0);
        ui->actionFrom_PSX_Slot->setEnabled(0);
        ui->actionNew_Game_Plus->setEnabled(0);
        ui->actionClear_Slot->setEnabled(0);
        ui->actionPaste_Slot->setEnabled(0); // read only no point
        ui->actionCopy_Slot->setEnabled(1);
        ui->actionNext_Slot->setEnabled(0);
        ui->actionPrevious_Slot->setEnabled(0);
        ui->actionShow_Selection_Dialog->setEnabled(0);
        ui->actionSlot_01->setEnabled(0);
        ui->actionSlot_02->setEnabled(0);
        ui->actionSlot_03->setEnabled(0);
        ui->actionSlot_04->setEnabled(0);
        ui->actionSlot_05->setEnabled(0);
        ui->actionSlot_06->setEnabled(0);
        ui->actionSlot_07->setEnabled(0);
        ui->actionSlot_08->setEnabled(0);
        ui->actionSlot_09->setEnabled(0);
        ui->actionSlot_10->setEnabled(0);
        ui->actionSlot_11->setEnabled(0);
        ui->actionSlot_12->setEnabled(0);
        ui->actionSlot_13->setEnabled(0);
        ui->actionSlot_14->setEnabled(0);
        ui->actionSlot_15->setEnabled(0);
    }
    else if (ff7.savetype ==5)//PSP
    {
        ui->actionImport_char->setEnabled(1);
        ui->actionExport_char->setEnabled(1);
        ui->actionSave_File->setEnabled(1);
        ui->actionExport_PC_Save->setEnabled(1);
        ui->actionExport_PSX->setEnabled(1);
        ui->actionExport_MC->setEnabled(1);
        ui->actionFrom_PSV_Slot->setEnabled(1);
        ui->actionFrom_PSX_Slot->setEnabled(1);
        ui->actionNew_Game_Plus->setEnabled(1);
        ui->actionClear_Slot->setEnabled(1);
        ui->actionPaste_Slot->setEnabled(1);
        ui->actionCopy_Slot->setEnabled(1);
        ui->actionNext_Slot->setEnabled(1);
        ui->actionPrevious_Slot->setEnabled(1);
        ui->actionShow_Selection_Dialog->setEnabled(1);
        ui->actionSlot_01->setEnabled(1);
        ui->actionSlot_02->setEnabled(1);
        ui->actionSlot_03->setEnabled(1);
        ui->actionSlot_04->setEnabled(1);
        ui->actionSlot_05->setEnabled(1);
        ui->actionSlot_06->setEnabled(1);
        ui->actionSlot_07->setEnabled(1);
        ui->actionSlot_08->setEnabled(1);
        ui->actionSlot_09->setEnabled(1);
        ui->actionSlot_10->setEnabled(1);
        ui->actionSlot_11->setEnabled(1);
        ui->actionSlot_12->setEnabled(1);
        ui->actionSlot_13->setEnabled(1);
        ui->actionSlot_14->setEnabled(1);
        ui->actionSlot_15->setEnabled(1);
    }
    else
    {
        ui->actionImport_char->setEnabled(1);
        ui->actionExport_char->setEnabled(1);
        ui->actionSave_File->setEnabled(0);
        ui->actionExport_PC_Save->setEnabled(1);
        ui->actionExport_PSX->setEnabled(1);
        ui->actionExport_MC->setEnabled(1);
        ui->actionFrom_PSV_Slot->setEnabled(1);
        ui->actionFrom_PSX_Slot->setEnabled(1);
        ui->actionClear_Slot->setEnabled(1);
        ui->actionPaste_Slot->setEnabled(1);
        ui->actionCopy_Slot->setEnabled(1);
        ui->actionNext_Slot->setEnabled(1);
        ui->actionPrevious_Slot->setEnabled(1);
        ui->actionShow_Selection_Dialog->setEnabled(1);
        ui->actionSlot_01->setEnabled(1);
        ui->actionSlot_02->setEnabled(1);
        ui->actionSlot_03->setEnabled(1);
        ui->actionSlot_04->setEnabled(1);
        ui->actionSlot_05->setEnabled(1);
        ui->actionSlot_06->setEnabled(1);
        ui->actionSlot_07->setEnabled(1);
        ui->actionSlot_08->setEnabled(1);
        ui->actionSlot_09->setEnabled(1);
        ui->actionSlot_10->setEnabled(1);
        ui->actionSlot_11->setEnabled(1);
        ui->actionSlot_12->setEnabled(1);
        ui->actionSlot_13->setEnabled(1);
        ui->actionSlot_14->setEnabled(1);
        ui->actionSlot_15->setEnabled(1);
        ui->menuRegion->setEnabled(1);
    }
    ui->menuRegion->setEnabled(1);
    ui->action_Region_USA->setChecked(0);
    ui->action_Region_PAL_Generic->setChecked(0);
    ui->action_Region_PAL_German->setChecked(0);
    ui->action_Region_PAL_Spanish->setChecked(0);
    ui->action_Region_JPN->setChecked(0);
    ui->action_Region_JPN_International->setChecked(0);
    ui->action_Region_USA->setIcon(QIcon(":/icon/us_unsel"));
    ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_unsel"));
    ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_unsel"));
    ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_unsel"));
    ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_unsel"));
    ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_unsel"));
    if(ff7.SG_Region_String[s].contains("94163")){ui->action_Region_USA->setChecked(Qt::Checked);ui->action_Region_USA->setIcon(QIcon(":/icon/us_sel"));}
    else if (ff7.SG_Region_String[s].contains("00867")){ui->action_Region_PAL_Generic->setChecked(Qt::Checked);ui->action_Region_PAL_Generic->setIcon(QIcon(":/icon/eu_sel"));}
    else if (ff7.SG_Region_String[s].contains("00869")){ui->action_Region_PAL_German->setChecked(Qt::Checked);ui->action_Region_PAL_German->setIcon(QIcon(":/icon/de_sel"));}
    else if (ff7.SG_Region_String[s].contains("00900")){ui->action_Region_PAL_Spanish->setChecked(Qt::Checked);ui->action_Region_PAL_Spanish->setIcon(QIcon(":/icon/es_sel"));}
    else if (ff7.SG_Region_String[s].contains("00700")){ui->action_Region_JPN->setChecked(Qt::Checked);ui->action_Region_JPN->setIcon(QIcon(":/icon/jp_sel"));}
    else if (ff7.SG_Region_String[s].contains("01057")){ui->action_Region_JPN_International->setChecked(Qt::Checked);ui->action_Region_JPN_International->setIcon(QIcon(":/icon/jp_sel"));}
    else {/*QMessageBox::information(this,tr("Region Detect Error"),tr("Unknow Region String, this is  not a ff7 save"));*/}
    ui->lbl_sg_region->setText(ff7.SG_Region_String[s]);
    if (ff7.savetype == 2 || ff7.savetype == 3 || ff7.savetype ==5)
    {
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[s].sl_header[i]);}
        SaveIcon ico(data.mid(96,160));
        ui->lbl_slot_icon->setPixmap(ico.icon().scaledToHeight(64,Qt::SmoothTransformation));
    }
/*~~~~~End of menu options~~~~*/
/*~~~~~Load Game Options~~~~~*/
    if((ff7.slot[s].options1)& (1<<0)){ui->combo_sound->setCurrentIndex(1);}
    else{ui->combo_sound->setCurrentIndex(0);}
    if((ff7.slot[s].options1) & (1<<2)){ui->combo_control->setCurrentIndex(1);}
    else{ui->combo_control->setCurrentIndex(0);}
    if((ff7.slot[s].options1)&(1<<4)){ui->combo_cursor->setCurrentIndex(1);}
    else{ui->combo_cursor->setCurrentIndex(0);}
    if((ff7.slot[s].options1)&(1<<6)){ui->combo_atb->setCurrentIndex(1);}
    else{ui->combo_atb->setCurrentIndex(0);}
    if((ff7.slot[s].options1)&(1<<7)){ui->combo_atb->setCurrentIndex(2);}
    else{ui->combo_atb->setCurrentIndex(0);}
    ui->slide_battlespeed->setValue(ff7.slot[s].battlespeed);
    ui->slide_battlemspeed->setValue(ff7.slot[s].battlemspeed);
    ui->slide_fieldmspeed->setValue(ff7.slot[s].fieldmspeed);
    if((ff7.slot[s].options2)&(1<<0)){ui->combo_camera->setCurrentIndex(1);}
    else{ui->combo_camera->setCurrentIndex(0);}
    if(((ff7.slot[s].options2)&(1<<2)) && ((ff7.slot[s].options2)&(1<<3))){ui->combo_magic_order->setCurrentIndex(3);}
    else if(((ff7.slot[s].options2)&(1<<2)) && ((ff7.slot[s].options2)&(1<<4))){ui->combo_magic_order->setCurrentIndex(5);}
    else if((ff7.slot[s].options2)&(1<<2)){ui->combo_magic_order->setCurrentIndex(1);}
    else if((ff7.slot[s].options2)&(1<<3)){ui->combo_magic_order->setCurrentIndex(2);}
    else if((ff7.slot[s].options2)&(1<<4)){ui->combo_magic_order->setCurrentIndex(4);}
    else{ui->combo_magic_order->setCurrentIndex(0);}
    if((ff7.slot[s].options2)&(1<<6)){ui->cb_battle_help->setCheckState(Qt::Checked);}
    else{ui->cb_battle_help->setCheckState(Qt::Unchecked);}
/*~~~~~End Options Loading~~~~~*/
    ui->sb_curdisc->setValue(ff7.slot[s].disc);
    if(ui->action_show_test_data->isChecked())
    {
        ui->btn_vincent->setEnabled(true);
        ui->btn_cait->setEnabled(true);
        ui->cb_id->setEnabled(true);
    }
    else //test mode off..check for seppie and young cloud to avoid possible breakage of save game since we don't account for them yet.
    {
        if (ff7.slot[s].chars[6].id == 9)
        {
            ui->btn_cait->setEnabled(false);
            if(curchar ==6){curchar =0;
        }
    }
        else {ui->btn_cait->setEnabled(true);}

        if (ff7.slot[s].chars[7].id == 10)
        {
            ui->btn_vincent->setEnabled(false);
            if(curchar ==7){curchar = 0;}
        }
        else {ui->btn_vincent->setEnabled(true);}
    }

/*~~~~~~~Set up location Data~~~~~~~*/
    ui->sb_coordx->setValue(ff7.slot[s].coord.x);
    ui->sb_coordy->setValue(ff7.slot[s].coord.y);
    ui->sb_coordz->setValue(ff7.slot[s].coord.z);
    ui->line_location->clear();
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
        else{ui->line_location->setText( ui->line_location->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
    }
    ui->sb_map_id->setValue(ff7.slot[s].mapid);
    ui->sb_loc_id->setValue(ff7.slot[s].locationid);
    for (int i=0;i<6;i++)//flyers
    {
        ui->list_flyers->setCurrentRow(i);
        if ((1 << i) & ff7.slot[s].turtleflyers){ui->list_flyers->currentItem()->setCheckState(Qt::Checked);}
        else{ui->list_flyers->currentItem()->setCheckState(Qt::Unchecked);}
        ui->list_flyers->setCurrentRow(-1);
    }
    for (int i=0;i<9;i++)//phsmask
    {
        ui->list_phs_chars->setCurrentRow(i);
        if ((1 << i) & ff7.slot[s].phsmask){ui->list_phs_chars->currentItem()->setCheckState(Qt::Unchecked);}
        else{ui->list_phs_chars->currentItem()->setCheckState(Qt::Checked);}
        ui->list_phs_chars->setCurrentRow(-1);
    }
    for (int i=0;i<9;i++)//unlocked
    {
        ui->list_chars_unlocked->setCurrentRow(i);
        if ((1 << i) & ff7.slot[s].unlockedchars){ui->list_chars_unlocked->currentItem()->setCheckState(Qt::Checked);}
        else{ui->list_chars_unlocked->currentItem()->setCheckState(Qt::Unchecked);}
        ui->list_chars_unlocked->setCurrentRow(-1);
    }
    for (int i=0;i<10;i++)//visible_menu
    {
        ui->list_menu_visible->setCurrentRow(i);
        if ((1 << i) & ff7.slot[s].menu_visible){ui->list_menu_visible->currentItem()->setCheckState(Qt::Checked);}
        else{ui->list_menu_visible->currentItem()->setCheckState(Qt::Unchecked);}
        ui->list_menu_visible->setCurrentRow(-1);
    }
    for (int i=0;i<10;i++)//menu_locked
    {
        ui->list_menu_locked->setCurrentRow(i);
        if ((1 << i) & ff7.slot[s].menu_locked){ui->list_menu_locked->currentItem()->setCheckState(Qt::Checked);}
        else{ui->list_menu_locked->currentItem()->setCheckState(Qt::Unchecked);}
        ui->list_menu_locked->setCurrentRow(-1);
    }
    for(int i=0;i<51;i++)// be sure to clear key items first..
    {
        ui->list_keyitems->setCurrentRow(i);
        ui->list_keyitems->currentItem()->setCheckState(Qt::Unchecked);
    }

    for (int i=0;i<51;i++)// key items
    {
        if (ff7.slot[s].keyitems[i/8] & (1 << (i%8)))
        {
            ui->list_keyitems->setCurrentRow(i);
            ui->list_keyitems->currentItem()->setCheckState(Qt::Checked);
        }
    }
    ui->list_keyitems->setCurrentRow(-1);

/*~~~~~party combo boxes (checking for empty slots)~~~*/
    if (ff7.slot[s].party[0] >= 0x0C){ui->combo_party1->setCurrentIndex(12);}
    else{ui->combo_party1->setCurrentIndex(ff7.slot[s].party[0]);}
    if (ff7.slot[s].party[1] >= 0x0C){ui->combo_party2->setCurrentIndex(12);}
    else{ui->combo_party2->setCurrentIndex(ff7.slot[s].party[1]);}
    if (ff7.slot[s].party[2] >= 0x0C){ui->combo_party3->setCurrentIndex(12);}
    else{ui->combo_party3->setCurrentIndex(ff7.slot[s].party[2]);}

    ui->sb_gil->setValue(ff7.slot[s].gil);
    ui->sb_gp->setValue(ff7.slot[s].gp);
    ui->sb_time_hour->setValue(ff7.slot[s].time / 3600);
    ui->sb_time_min->setValue(ff7.slot[s].time/60%60);
    ui->sb_time_sec->setValue(ff7.slot[s].time -((ui->sb_time_hour->value()*3600)+ui->sb_time_min->value()*60));
    ui->slide_ul_r->setValue(ff7.slot[s].colors[0][0]);
    ui->slide_ul_g->setValue(ff7.slot[s].colors[0][1]);
    ui->slide_ul_b->setValue(ff7.slot[s].colors[0][2]);
    ui->slide_ur_r->setValue(ff7.slot[s].colors[1][0]);
    ui->slide_ur_g->setValue(ff7.slot[s].colors[1][1]);
    ui->slide_ur_b->setValue(ff7.slot[s].colors[1][2]);
    ui->slide_ll_r->setValue(ff7.slot[s].colors[2][0]);
    ui->slide_ll_g->setValue(ff7.slot[s].colors[2][1]);
    ui->slide_ll_b->setValue(ff7.slot[s].colors[2][2]);
    ui->slide_lr_r->setValue(ff7.slot[s].colors[3][0]);
    ui->slide_lr_g->setValue(ff7.slot[s].colors[3][1]);
    ui->slide_lr_b->setValue(ff7.slot[s].colors[3][2]);
    ui->sb_runs->setValue(ff7.slot[s].runs);
    ui->sb_battles->setValue(ff7.slot[s].battles);
    ui->sb_love_barret->setValue(ff7.slot[s].love.barret);
    ui->sb_love_tifa->setValue(ff7.slot[s].love.tifa);
    ui->sb_love_aeris->setValue(ff7.slot[s].love.aeris);
    ui->sb_love_yuffie->setValue(ff7.slot[s].love.yuffie);

    QTableWidgetItem *newItem;
/*~~~~~Item Table Code~~~~~*/

    int j= ui->tbl_itm->currentRow();
    ui->tbl_itm->reset(); // just incase
    ui->tbl_itm->setColumnWidth(0,145);
    ui->tbl_itm->setColumnWidth(1,32);
    ui->tbl_itm->setRowCount(320);
    for (int i=0;i<320;i++) // set up items
    {
        if (ff7.slot[s].items[i].qty == 0xFF && ff7.slot[s].items[i].id == 0xFF)
        {
            newItem = new QTableWidgetItem("-------EMPTY--------",0);
            ui->tbl_itm->setItem(i,0,newItem);
            ui->tbl_itm->setRowHeight(i,22);
            newItem = new QTableWidgetItem("",0);
            ui->tbl_itm->setItem(i,1,newItem);
        }
        else
        {
            QString qty;
            if(ff7.slot[s].items[i].qty %2 ==0)
            {
                newItem = new QTableWidgetItem(QIcon(Items[ff7.slot[s].items[i].id].image),Items[ff7.slot[s].items[i].id].name,0);
                ui->tbl_itm->setItem(i,0, newItem);
                ui->tbl_itm->setRowHeight(i,22);
                newItem = new QTableWidgetItem(qty.setNum(ff7.slot[s].items[i].qty/2),0);
                ui->tbl_itm->setItem(i,1,newItem);
            }
            else
            {
                newItem = new QTableWidgetItem(QIcon(Items[256+(ff7.slot[s].items[i].id)].image),Items[256+(ff7.slot[s].items[i].id)].name,0);
                ui->tbl_itm->setItem(i,0, newItem);
                ui->tbl_itm->setRowHeight(i,22);
                newItem = new QTableWidgetItem(qty.setNum(ff7.slot[s].items[i].qty/2),0);
                ui->tbl_itm->setItem(i,1,newItem);
            }
        }
    }
    ui->tbl_itm->setCurrentCell(j,0);
/*~~~~~End Item Code~~~~~*/
/*~~~~~Materia Code~~~~~~*/

    j= ui->tbl_materia->currentRow();
    ui->tbl_materia->reset();
    ui->tbl_materia->setColumnWidth(0,145);
    ui->tbl_materia->setColumnWidth(1,64);
    ui->tbl_materia->setRowCount(200);
    for(int mat=0;mat<200;mat++)// partys materias
    {
        qint32 aptemp=0;
        QString ap;
        if (ff7.slot[s].materias[mat].id == 0x2C)
        {
            newItem = new QTableWidgetItem(QIcon(Materias[ff7.slot[s].materias[mat].id].image),Materias[ff7.slot[s].materias[mat].id].name,0);
            ui->tbl_materia->setItem(mat,0,newItem);
            aptemp = ff7.slot[s].materias[mat].ap[0] |(ff7.slot[s].materias[mat].ap[1] << 8) | (ff7.slot[s].materias[mat].ap[2] << 16);
            if (aptemp == 0xFFFFFF){newItem =new QTableWidgetItem(tr("Master"));ui->tbl_materia->setItem(mat,1,newItem);}
            else{newItem =new QTableWidgetItem(QString("N/A"),0);ui->tbl_materia->setItem(mat,1,newItem);}
        }
        else if (ff7.slot[s].materias[mat].id !=0xff)
        {
            newItem = new QTableWidgetItem(QIcon(Materias[ff7.slot[s].materias[mat].id].image),Materias[ff7.slot[s].materias[mat].id].name,0);
            ui->tbl_materia->setItem(mat,0,newItem);
            aptemp = ff7.slot[s].materias[mat].ap[0] |(ff7.slot[s].materias[mat].ap[1] << 8) | (ff7.slot[s].materias[mat].ap[2] << 16);
            if (aptemp == 0xFFFFFF){newItem =new QTableWidgetItem(tr("Master"));ui->tbl_materia->setItem(mat,1,newItem);}
            else{newItem =new QTableWidgetItem(ap.setNum(aptemp));ui->tbl_materia->setItem(mat,1,newItem);}
        }
        else
        {
            newItem = new QTableWidgetItem(tr("===Empty Slot==="),0);
            ui->tbl_materia->setItem(mat,0,newItem);
            newItem = new QTableWidgetItem("",0);
            ui->tbl_materia->setItem(mat,1,newItem);
        }
    }
    if(ff7.slot[s].materias[j].id == 0xFF) //if the slot is empty take some precautions
    {
        ui->lbl_mat_stats->setText(tr("Empty Slot"));
        ui->lcd_ap_master->display(0);
        ui->sb_addap->setValue(0);
        ui->sb_addap->setMaximum(0);
        ui->combo_mat_type->setCurrentIndex(0);
        ui->combo_add_mat->setCurrentIndex(0);
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
    }

    else if(Materias[ff7.slot[s].materias[j].id].name == tr("DON'T USE")) //this is a placeholder materia.
    {

        ui->lbl_mat_stats->setText(Materias[ff7.slot[s].materias[j].id].stats);
        ui->lcd_ap_master->display(tr("NO CAP"));
        ui->sb_addap->setMaximum(16777215);
        qint32 aptemp = ff7.slot[s].materias[j].ap[0] |(ff7.slot[s].materias[j].ap[1] << 8) | (ff7.slot[s].materias[j].ap[2] << 16);
        ui->sb_addap->setValue(aptemp);
        // Hide the Stars
        ui->btn_m_lvl1->setVisible(0);
        ui->btn_m_lvl2->setVisible(0);
        ui->btn_m_lvl3->setVisible(0);
        ui->btn_m_lvl4->setVisible(0);
        ui->btn_m_lvl5->setVisible(0);
        // Set the unknown skills
        ui->spell_lvl1_group->setVisible(1);
        ui->lbl_spell_lvl1->setText(Materias[ui->combo_add_mat->currentIndex()].skills[0]);
    }

    else // make the materia look nice
    {

        ui->lbl_mat_stats->setText(Materias[ui->combo_add_mat->currentIndex()].stats);// set stat string..
        qint32 aptemp = ff7.slot[s].materias[j].ap[0] |(ff7.slot[s].materias[j].ap[1] << 8) | (ff7.slot[s].materias[j].ap[2] << 16);
        qint32 masterap = (Materias[ui->combo_add_mat->currentIndex()].ap[Materias[ui->combo_add_mat->currentIndex()].levels-2]);
        ui->lcd_ap_master->display(masterap);
// Check Materia Max AP and Set the Spin Box's Max Value.
        if(Materias[ui->combo_add_mat->currentIndex()].levels>1){ui->sb_addap->setMaximum(masterap);}
        else{ui->sb_addap->setMaximum(16777215);}
        ui->sb_addap->setValue(aptemp);
//Show levels stars
        int level=0;
        QString e_icon;
        QString f_icon;
        switch(Materias[ui->combo_add_mat->currentIndex()].type)
        {// COLORS 1-magic(g),2-summon(r),3-independent(f),4-support(b),5-command(y),0-unknown
            case 0:
                e_icon= "\0";
                f_icon= "\0";
                break;
            case 1:
                e_icon= ":/icon/magic_empty";
                f_icon= ":/icon/magic_full";
                break;

            case 2:
                e_icon= ":/icon/summon_empty";
                f_icon= ":/icon/summon_full";
                break;

            case 3:
                e_icon= ":/icon/independent_empty";
                f_icon= ":/icon/independent_full";
                break;

            case 4:
                e_icon= ":/icon/support_empty";
                f_icon= ":/icon/support_full";
                break;

            case 5:
                e_icon= ":/icon/command_empty";
                f_icon= ":/icon/command_full";
                break;
        }
        for(int i=0; i<Materias[ui->combo_add_mat->currentIndex()].levels;i++){if(aptemp >= Materias[ui->combo_add_mat->currentIndex()].ap[i]){level++;}}
        switch (Materias[ui->combo_add_mat->currentIndex()].levels)
        {
            case 0:
                ui->btn_m_lvl1->setVisible(0);
                ui->btn_m_lvl2->setVisible(0);
                ui->btn_m_lvl3->setVisible(0);
                ui->btn_m_lvl4->setVisible(0);
                ui->btn_m_lvl5->setVisible(0);
                break;
            case 1:
                ui->btn_m_lvl1->setVisible(1);
                ui->btn_m_lvl1->setIcon((QIcon(f_icon)));
                ui->btn_m_lvl2->setVisible(0);
                ui->btn_m_lvl3->setVisible(0);
                ui->btn_m_lvl4->setVisible(0);
                ui->btn_m_lvl5->setVisible(0);
                ui->lcd_ap_master->display(0);
                break;
            case 2:
                ui->btn_m_lvl1->setVisible(1);
                ui->btn_m_lvl1->setIcon((QIcon(f_icon)));
                ui->btn_m_lvl2->setVisible(1);
                if (level >1){ui->btn_m_lvl2->setIcon((QIcon(f_icon)));}
                else{ui->btn_m_lvl2->setIcon((QIcon(e_icon)));}
                ui->btn_m_lvl3->setVisible(0);
                ui->btn_m_lvl4->setVisible(0);
                ui->btn_m_lvl5->setVisible(0);
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
                ui->btn_m_lvl4->setVisible(0);
                ui->btn_m_lvl5->setVisible(0);
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
                ui->btn_m_lvl5->setVisible(0);
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
                ui->spell_lvl2_group->setVisible(0);
                ui->spell_lvl3_group->setVisible(0);
                ui->spell_lvl4_group->setVisible(0);
                ui->spell_lvl5_group->setVisible(0);
                ui->lbl_spell_lvl1->setText(Materias[ui->combo_add_mat->currentIndex()].skills[0]);
                break;
            case 1:
                ui->spell_lvl1_group->setVisible(1);
                ui->spell_lvl2_group->setVisible(0);
                ui->spell_lvl3_group->setVisible(0);
                ui->spell_lvl4_group->setVisible(0);
                ui->spell_lvl5_group->setVisible(0);
                ui->lbl_spell_lvl1->setText(Materias[ui->combo_add_mat->currentIndex()].skills[0]);
                break;
            case 2:
                ui->spell_lvl1_group->setVisible(1);
                ui->spell_lvl2_group->setVisible(1);
                ui->spell_lvl3_group->setVisible(0);
                ui->spell_lvl4_group->setVisible(0);
                ui->spell_lvl5_group->setVisible(0);
                ui->lbl_spell_lvl1->setText(Materias[ui->combo_add_mat->currentIndex()].skills[0]);
                ui->lbl_spell_lvl2->setText(Materias[ui->combo_add_mat->currentIndex()].skills[1]);
                break;
            case 3:
                ui->spell_lvl1_group->setVisible(1);
                ui->spell_lvl2_group->setVisible(1);
                ui->spell_lvl3_group->setVisible(1);
                ui->spell_lvl4_group->setVisible(0);
                ui->spell_lvl5_group->setVisible(0);
                ui->lbl_spell_lvl1->setText(Materias[ui->combo_add_mat->currentIndex()].skills[0]);
                ui->lbl_spell_lvl2->setText(Materias[ui->combo_add_mat->currentIndex()].skills[1]);
                ui->lbl_spell_lvl3->setText(Materias[ui->combo_add_mat->currentIndex()].skills[2]);
                break;
            case 4:
                ui->spell_lvl1_group->setVisible(1);
                ui->spell_lvl2_group->setVisible(1);
                ui->spell_lvl3_group->setVisible(1);
                ui->spell_lvl4_group->setVisible(1);
                ui->spell_lvl5_group->setVisible(0);
                ui->lbl_spell_lvl1->setText(Materias[ui->combo_add_mat->currentIndex()].skills[0]);
                ui->lbl_spell_lvl2->setText(Materias[ui->combo_add_mat->currentIndex()].skills[1]);
                ui->lbl_spell_lvl3->setText(Materias[ui->combo_add_mat->currentIndex()].skills[2]);
                ui->lbl_spell_lvl4->setText(Materias[ui->combo_add_mat->currentIndex()].skills[3]);
                break;
            case 5:
                ui->spell_lvl1_group->setVisible(1);
                ui->spell_lvl2_group->setVisible(1);
                ui->spell_lvl3_group->setVisible(1);
                ui->spell_lvl4_group->setVisible(1);
                ui->spell_lvl5_group->setVisible(1);
                ui->lbl_spell_lvl1->setText(Materias[ui->combo_add_mat->currentIndex()].skills[0]);
                ui->lbl_spell_lvl2->setText(Materias[ui->combo_add_mat->currentIndex()].skills[1]);
                ui->lbl_spell_lvl3->setText(Materias[ui->combo_add_mat->currentIndex()].skills[2]);
                ui->lbl_spell_lvl4->setText(Materias[ui->combo_add_mat->currentIndex()].skills[3]);
                ui->lbl_spell_lvl5->setText(Materias[ui->combo_add_mat->currentIndex()].skills[4]);
                break;
        }
    } //end of else
// this will ensure that the right side of materia stuff is set correctly.
    load=false;
    ui->tbl_materia->setCurrentCell(j,1);
    load=true;
/*~~~~~End Materia Code~~~~~*/
/*~~~~~Stolen Materia~~~~~~~*/
    ui->tbl_materia_2->reset();
    ui->tbl_materia_2->setColumnWidth(0,145);
    ui->tbl_materia_2->setColumnWidth(1,64);
    ui->tbl_materia_2->setRowCount(48);
    for(int mat=0;mat<48;mat++) //materias stolen by yuffie
    {
        int aptemp;
        QString ap;
        if (ff7.slot[s].stolen[mat].id !=0xff)
        {
            newItem = new QTableWidgetItem(QIcon(Materias[ff7.slot[s].stolen[mat].id].image),Materias[ff7.slot[s].stolen[mat].id].name,0);
            ui->tbl_materia_2->setItem(mat,0,newItem);
            aptemp = ff7.slot[s].stolen[mat].ap[0] |(ff7.slot[s].stolen[mat].ap[1] << 8) | (ff7.slot[s].stolen[mat].ap[2] << 16);
            if (aptemp == 0xFFFFFF){newItem =new QTableWidgetItem(tr("Master"));ui->tbl_materia_2->setItem(mat,1,newItem);}
            else{newItem =new QTableWidgetItem(ap.setNum(aptemp));ui->tbl_materia_2->setItem(mat,1,newItem);}
        }
        else
        {
            newItem = new QTableWidgetItem(tr("===Empty Slot==="),0);
            ui->tbl_materia_2->setItem(mat,0,newItem);
        }
    }

/*~~~~~End Stolen Materia~~~~*/
    if((ff7.slot[s].materiacaves)& (1<<0)){ui->cb_materiacave_1->setChecked(Qt::Checked);}
    else{ui->cb_materiacave_1->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].materiacaves)& (1<<1)){ui->cb_materiacave_2->setChecked(Qt::Checked);}
    else{ui->cb_materiacave_2->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].materiacaves)& (1<<2)){ui->cb_materiacave_3->setChecked(Qt::Checked);}
    else{ui->cb_materiacave_3->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].materiacaves)& (1<<3)){ui->cb_materiacave_4->setChecked(Qt::Checked);}
    else{ui->cb_materiacave_4->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].yuffieforest)& (1<<0)){ui->cb_yuffieforest->setChecked(Qt::Checked);}
    else{ui->cb_yuffieforest->setChecked(Qt::Unchecked);}

    load =false; // all functions should set load on their own.
/*~~~~~Call External Functions~~~~~~~*/
    chocobo_refresh();
    switch (curchar) // click char button for who?
    {
        case 0:{ui->btn_cloud->click();break;}
        case 1:{ui->btn_barret->click();break;}
        case 2:{ui->btn_tifa->click();break;}
        case 3:{ui->btn_aeris->click();break;}
        case 4:{ui->btn_red->click();break;}
        case 5:{ui->btn_yuffie->click();break;}
        case 6:{ui->btn_cait->click();break;}
        case 7:{ui->btn_vincent->click();break;}
        case 8:{ui->btn_cid->click();break;}
    }
    if(ui->action_show_test_data->isChecked()){testdata_refresh();}
}/*~~~~~~~~~~~~~~~~~~~~End GUIREFRESH ~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~Chocobo Refresh~~~~~~~~~~~~~~~~*/
void MainWindow::chocobo_refresh()
{
    load=true;
    ui->sb_stables_owned->setValue(ff7.slot[s].stables);
    ui->sb_stables_occupied->setValue(ff7.slot[s].stablesoccupied);

    switch(ui->sb_stables_occupied->value())
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

    ui->line_c1_name->clear();
    for (int n=0;n<6;n++)
    {
        if(chPC[ff7.slot[s].chocobonames[0][n]] =='\0'){break;}
        else{this->ui->line_c1_name->setText( ui->line_c1_name->text() + chPC[ff7.slot[s].chocobonames[0][n]]);}
    }
    //ui->cb_c1_personality->setCurrentIndex(ff7.slot[s].chocobos[0].personality); //need more data for this.
    ui->sb_c1_sprint->setValue(ff7.slot[s].chocobos[0].sprintspd);
    ui->sb_c1_maxsprint->setValue(ff7.slot[s].chocobos[0].maxsprintspd);
    ui->sb_c1_speed->setValue(ff7.slot[s].chocobos[0].speed);
    ui->sb_c1_maxspeed->setValue((ff7.slot[s].chocobos[0].maxspeed));
    ui->cb_c1_sex->setCurrentIndex(ff7.slot[s].chocobos[0].sex);
    ui->cb_c1_type->setCurrentIndex(ff7.slot[s].chocobos[0].type);
    ui->sb_c1_accel->setValue(ff7.slot[s].chocobos[0].accel);
    ui->sb_c1_coop->setValue(ff7.slot[s].chocobos[0].coop);
    ui->sb_c1_intel->setValue(ff7.slot[s].chocobos[0].intelligence);
    ui->sb_c1_pcount->setValue(ff7.slot[s].chocobos[0].pcount);
    ui->sb_c1_raceswon->setValue(ff7.slot[s].chocobos[0].raceswon);
    ui->sb_c1_stamina->setValue(ff7.slot[s].chocostaminas[0]);//Bug fixed Before was chocostaminas[0]*10 and (999*10 != 9999), is 9990 (Vegeta_Ss4) v0.8.3
    // end choco 1

    ui->line_c2_name->clear();
    for (int n=0;n<6;n++)
    {
        if(chPC[ff7.slot[s].chocobonames[1][n]] =='\0'){break;}
        else{this->ui->line_c2_name->setText( ui->line_c2_name->text() + chPC[ff7.slot[s].chocobonames[1][n]]);}
    }
    //ui->cb_c2_personality->setCurrentIndex(ff7.slot[s].chocobos[1].personality); //need more data for this.
    ui->sb_c2_sprint->setValue(ff7.slot[s].chocobos[1].sprintspd);
    ui->sb_c2_maxsprint->setValue(ff7.slot[s].chocobos[1].maxsprintspd);
    ui->sb_c2_speed->setValue(ff7.slot[s].chocobos[1].speed);
    ui->sb_c2_maxspeed->setValue((ff7.slot[s].chocobos[1].maxspeed));
    ui->cb_c2_sex->setCurrentIndex(ff7.slot[s].chocobos[1].sex);
    ui->cb_c2_type->setCurrentIndex(ff7.slot[s].chocobos[1].type);
    ui->sb_c2_accel->setValue(ff7.slot[s].chocobos[1].accel);
    ui->sb_c2_coop->setValue(ff7.slot[s].chocobos[1].coop);
    ui->sb_c2_intel->setValue(ff7.slot[s].chocobos[1].intelligence);
    ui->sb_c2_pcount->setValue(ff7.slot[s].chocobos[1].pcount);
    ui->sb_c2_raceswon->setValue(ff7.slot[s].chocobos[1].raceswon);
    ui->sb_c2_stamina->setValue(ff7.slot[s].chocostaminas[1]);//Bug fix (Vegeta_Ss4) v0.8.3
    //end Choco 2
    ui->line_c3_name->clear();
    for (int n=0;n<6;n++)
    {
        if(chPC[ff7.slot[s].chocobonames[2][n]] =='\0'){break;} //Bug Fixed before was pointing chocobonames[1][n] (Vegeta_Ss4) v0.8.3
        else{this->ui->line_c3_name->setText( ui->line_c3_name->text() + chPC[ff7.slot[s].chocobonames[2][n]]);}
    }
    //ui->cb_c3_personality->setCurrentIndex(ff7.slot[s].chocobos[2].personality); //need more data for this.
    ui->sb_c3_sprint->setValue(ff7.slot[s].chocobos[2].sprintspd);
    ui->sb_c3_maxsprint->setValue(ff7.slot[s].chocobos[2].maxsprintspd);
    ui->sb_c3_speed->setValue(ff7.slot[s].chocobos[2].speed);
    ui->sb_c3_maxspeed->setValue((ff7.slot[s].chocobos[2].maxspeed));
    ui->cb_c3_sex->setCurrentIndex(ff7.slot[s].chocobos[2].sex);
    ui->cb_c3_type->setCurrentIndex(ff7.slot[s].chocobos[2].type);
    ui->sb_c3_accel->setValue(ff7.slot[s].chocobos[2].accel);
    ui->sb_c3_coop->setValue(ff7.slot[s].chocobos[2].coop);
    ui->sb_c3_intel->setValue(ff7.slot[s].chocobos[2].intelligence);
    ui->sb_c3_pcount->setValue(ff7.slot[s].chocobos[2].pcount);
    ui->sb_c3_raceswon->setValue(ff7.slot[s].chocobos[2].raceswon);
    ui->sb_c3_stamina->setValue(ff7.slot[s].chocostaminas[2]);//Bug fix (Vegeta_Ss4) v0.8.3
    // end choco 3
    ui->line_c4_name->clear();
    for (int n=0;n<6;n++)
    {
        if(chPC[ff7.slot[s].chocobonames[3][n]] =='\0'){break;} //Bug Fixed before was pointing chocobonames[1][n] (Vegeta_Ss4) v0.8.3
        else{this->ui->line_c4_name->setText( ui->line_c4_name->text() + chPC[ff7.slot[s].chocobonames[3][n]]);}
    }
    //ui->cb_c4_personality->setCurrentIndex(ff7.slot[s].chocobos[3].personality); //need more data for this.
    ui->sb_c4_sprint->setValue(ff7.slot[s].chocobos[3].sprintspd);
    ui->sb_c4_maxsprint->setValue(ff7.slot[s].chocobos[3].maxsprintspd);
    ui->sb_c4_speed->setValue(ff7.slot[s].chocobos[3].speed);
    ui->sb_c4_maxspeed->setValue((ff7.slot[s].chocobos[3].maxspeed));
    ui->cb_c4_sex->setCurrentIndex(ff7.slot[s].chocobos[3].sex);
    ui->cb_c4_type->setCurrentIndex(ff7.slot[s].chocobos[3].type);
    ui->sb_c4_accel->setValue(ff7.slot[s].chocobos[3].accel);
    ui->sb_c4_coop->setValue(ff7.slot[s].chocobos[3].coop);
    ui->sb_c4_intel->setValue(ff7.slot[s].chocobos[3].intelligence);
    ui->sb_c4_pcount->setValue(ff7.slot[s].chocobos[3].pcount);
    ui->sb_c4_raceswon->setValue(ff7.slot[s].chocobos[3].raceswon);
    ui->sb_c4_stamina->setValue(ff7.slot[s].chocostaminas[3]);//Bug fix (Vegeta_Ss4) v0.8.3
    // end choco 4
    ui->line_c5_name->clear();
    for (int n=0;n<6;n++)
    {
        if(chPC[ff7.slot[s].chocobonames[4][n]] =='\0'){break;} //Bug Fixed before was pointing chocobonames[1][n] (Vegeta_Ss4) v0.8.3
        else{this->ui->line_c5_name->setText( ui->line_c5_name->text() + chPC[ff7.slot[s].chocobonames[4][n]]);}
    }
    //ui->cb_c5_personality->setCurrentIndex(ff7.slot[s].choco56[0].personality); //need more data for this.
    ui->sb_c5_sprint->setValue(ff7.slot[s].choco56[0].sprintspd);
    ui->sb_c5_maxsprint->setValue(ff7.slot[s].choco56[0].maxsprintspd);
    ui->sb_c5_speed->setValue(ff7.slot[s].choco56[0].speed);
    ui->sb_c5_maxspeed->setValue((ff7.slot[s].choco56[0].maxspeed));
    ui->cb_c5_sex->setCurrentIndex(ff7.slot[s].choco56[0].sex);
    ui->cb_c5_type->setCurrentIndex(ff7.slot[s].choco56[0].type);
    ui->sb_c5_accel->setValue(ff7.slot[s].choco56[0].accel);
    ui->sb_c5_coop->setValue(ff7.slot[s].choco56[0].coop);
    ui->sb_c5_intel->setValue(ff7.slot[s].choco56[0].intelligence);
    ui->sb_c5_pcount->setValue(ff7.slot[s].choco56[0].pcount);
    ui->sb_c5_raceswon->setValue(ff7.slot[s].choco56[0].raceswon);
    ui->sb_c5_stamina->setValue(ff7.slot[s].chocostaminas[4]);//Bug fix (Vegeta_Ss4) v0.8.3
    // end choco 5
    ui->line_c6_name->clear();
    for (int n=0;n<6;n++)
    {
        if(chPC[ff7.slot[s].chocobonames[5][n]] =='\0'){break;} //Bug Fixed before was pointing chocobonames[1][n] (Vegeta_Ss4) v0.8.3
        else{this->ui->line_c6_name->setText( ui->line_c6_name->text() + chPC[ff7.slot[s].chocobonames[5][n]]);}
    }
    //ui->cb_c6_personality->setCurrentIndex(ff7.slot[s].choco56[1].personality); //need more data for this.
    ui->sb_c6_sprint->setValue(ff7.slot[s].choco56[1].sprintspd);
    ui->sb_c6_maxsprint->setValue(ff7.slot[s].choco56[1].maxsprintspd);
    ui->sb_c6_speed->setValue(ff7.slot[s].choco56[1].speed);
    ui->sb_c6_maxspeed->setValue((ff7.slot[s].choco56[1].maxspeed));
    ui->cb_c6_sex->setCurrentIndex(ff7.slot[s].choco56[1].sex);
    ui->cb_c6_type->setCurrentIndex(ff7.slot[s].choco56[1].type);
    ui->sb_c6_accel->setValue(ff7.slot[s].choco56[1].accel);
    ui->sb_c6_coop->setValue(ff7.slot[s].choco56[1].coop);
    ui->sb_c6_intel->setValue(ff7.slot[s].choco56[1].intelligence);
    ui->sb_c6_pcount->setValue(ff7.slot[s].choco56[1].pcount);
    ui->sb_c6_raceswon->setValue(ff7.slot[s].choco56[1].raceswon);
    ui->sb_c6_stamina->setValue(ff7.slot[s].chocostaminas[5]);//Bug fix (Vegeta_Ss4) v0.8.3
    // end choco 6
    //set the penned chocobos
    ui->combo_pen1->setCurrentIndex(ff7.slot[s].pennedchocos[0]);
    ui->combo_pen2->setCurrentIndex(ff7.slot[s].pennedchocos[1]);
    ui->combo_pen3->setCurrentIndex(ff7.slot[s].pennedchocos[2]);
    ui->combo_pen4->setCurrentIndex(ff7.slot[s].pennedchocos[3]);
    load=false;
}/*~~~~~~~~~~~End Chocobo Slots~~~~~~~~~*/
/*~~~~~~~~~~~Clear Slots~~~~~~~~~~~~~~*/
void MainWindow::clearslot(int rmslot)
{
    QByteArray temp;
    temp.fill(0x00,0x10f4);
    memcpy(&ff7.hf[rmslot].sl_header,temp,ff7.SG_SLOT_HEADER);// clear the header..
    memcpy(&ff7.slot[rmslot],temp,0x10f4);
    memcpy(&ff7.hf[rmslot].sl_footer,temp,ff7.SG_SLOT_FOOTER);// clear the footer..
    ff7.SG_Region_String[rmslot]="";
}

/*~~~~~~~~~Char Buttons.~~~~~~~~~~~*/

void MainWindow::on_btn_cloud_clicked()
{
    curchar=0;
    load=true;
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/cloud_icon"));
    charupdate();
//enable boxes for limits
    ui->limit_1a->setEnabled(1);
    ui->limit_1b->setEnabled(1);
    ui->limit_2a->setEnabled(1);
    ui->limit_2b->setEnabled(1);
    ui->limit_3a->setEnabled(1);
    ui->limit_3b->setEnabled(1);
    ui->limit_4->setEnabled(1);
//clear cheked on all boxes
    ui->limit_1a->setChecked(0);
    ui->limit_1b->setChecked(0);
    ui->limit_2a->setChecked(0);
    ui->limit_2b->setChecked(0);
    ui->limit_3a->setChecked(0);
    ui->limit_3b->setChecked(0);
    ui->limit_4->setChecked(0);
//show enabled boxes
    ui->limit_1a->setVisible(1);
    ui->limit_1b->setVisible(1);
    ui->limit_2a->setVisible(1);
    ui->limit_2b->setVisible(1);
    ui->limit_3a->setVisible(1);
    ui->limit_3b->setVisible(1);
    ui->limit_4->setVisible(1);
//label boxes
    ui->limit_1a->setText(tr("Braver"));
    ui->limit_1b->setText(tr("Cross-Slash"));
    ui->limit_2a->setText(tr("Blade Beam"));
    ui->limit_2b->setText(tr("Climhazzard"));
    ui->limit_3a->setText(tr("Meteorain"));
    ui->limit_3b->setText(tr("Finishing Touch"));
    ui->limit_4->setText(tr("OmniSlash"));
// set up checked limits
    int n = ff7.slot[s].chars[curchar].limits;
    if (n & (1<<0)) ui->limit_1a->setChecked(1);
    if (n & (1<<1)) ui->limit_1b->setChecked(1);
    if (n & (1<<3)) ui->limit_2a->setChecked(1);
    if (n & (1<<4)) ui->limit_2b->setChecked(1);
    if (n & (1<<6)) ui->limit_3a->setChecked(1);
    if (n & (1<<7)) ui->limit_3b->setChecked(1);
    if (n & (1<<9)) ui->limit_4->setChecked(1);
//label weapons then set current...
    for(int i=128;i<144;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),Items[i].name);}
    ui->combo_weapon->setCurrentIndex(ff7.slot[s].chars[curchar].weapon);
    load = false;
}
void MainWindow::on_btn_barret_clicked()
{
    curchar=1;
    load=true;
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/barret_icon"));
    charupdate();
//enable boxes for limits
    ui->limit_1a->setEnabled(1);
    ui->limit_1b->setEnabled(1);
    ui->limit_2a->setEnabled(1);
    ui->limit_2b->setEnabled(1);
    ui->limit_3a->setEnabled(1);
    ui->limit_3b->setEnabled(1);
    ui->limit_4->setEnabled(1);
//show enabled boxes
    ui->limit_1a->setVisible(1);
    ui->limit_1b->setVisible(1);
    ui->limit_2a->setVisible(1);
    ui->limit_2b->setVisible(1);
    ui->limit_3a->setVisible(1);
    ui->limit_3b->setVisible(1);
    ui->limit_4->setVisible(1);
// clear all checks
    ui->limit_1a->setChecked(0);
    ui->limit_1b->setChecked(0);
    ui->limit_2a->setChecked(0);
    ui->limit_2b->setChecked(0);
    ui->limit_3a->setChecked(0);
    ui->limit_3b->setChecked(0);
    ui->limit_4->setChecked(0);
//label boxes
    ui->limit_1a->setText(tr("Big Shot"));
    ui->limit_1b->setText(tr("Mindblow"));
    ui->limit_2a->setText(tr("Grenade Bomb"));
    ui->limit_2b->setText(tr("Hammerblow"));
    ui->limit_3a->setText(tr("Satellite Beam"));
    ui->limit_3b->setText(tr("Angermax"));
    ui->limit_4->setText(tr("Catastrophe"));
//check off learned limits
    int n = ff7.slot[s].chars[curchar].limits;
    if (n & (1<<0)) ui->limit_1a->setChecked(1);
    if (n & (1<<1)) ui->limit_1b->setChecked(1);
    if (n & (1<<3)) ui->limit_2a->setChecked(1);
    if (n & (1<<4)) ui->limit_2b->setChecked(1);
    if (n & (1<<6)) ui->limit_3a->setChecked(1);
    if (n & (1<<7)) ui->limit_3b->setChecked(1);
    if (n & (1<<9)) ui->limit_4->setChecked(1);
//label then set current weapon
    for(int i=160;i<176;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),Items[i].name);}
    ui->combo_weapon->setCurrentIndex((ff7.slot[s].chars[curchar].weapon)-32);
    load=false;
}
void MainWindow::on_btn_tifa_clicked()
{
    curchar=2;
    load=true;
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/tifa_icon"));
    charupdate();
//enable boxes for limits
    ui->limit_1a->setEnabled(1);
    ui->limit_1b->setEnabled(1);
    ui->limit_2a->setEnabled(1);
    ui->limit_2b->setEnabled(1);
    ui->limit_3a->setEnabled(1);
    ui->limit_3b->setEnabled(1);
    ui->limit_4->setEnabled(1);
    ui->limit_1a->setChecked(0);
    ui->limit_1b->setChecked(0);
    ui->limit_2a->setChecked(0);
    ui->limit_2b->setChecked(0);
    ui->limit_3a->setChecked(0);
    ui->limit_3b->setChecked(0);
    ui->limit_4->setChecked(0);
//show enabled boxes
    ui->limit_1a->setVisible(1);
    ui->limit_1b->setVisible(1);
    ui->limit_2a->setVisible(1);
    ui->limit_2b->setVisible(1);
    ui->limit_3a->setVisible(1);
    ui->limit_3b->setVisible(1);
    ui->limit_4->setVisible(1);
//label boxes
    ui->limit_1a->setText(tr("Beat Rush"));
    ui->limit_1b->setText(tr("SomerSault"));
    ui->limit_2a->setText(tr("Waterkick"));
    ui->limit_2b->setText(tr("Meteodrive"));
    ui->limit_3a->setText(tr("Dolphin Blow"));
    ui->limit_3b->setText(tr("Meteor Strike"));
    ui->limit_4->setText(tr("Final Heaven"));
// check off learned limits
    int n = ff7.slot[s].chars[curchar].limits;
    if (n & (1<<0)) ui->limit_1a->setChecked(1);
    if (n & (1<<1)) ui->limit_1b->setChecked(1);
    if (n & (1<<3)) ui->limit_2a->setChecked(1);
    if (n & (1<<4)) ui->limit_2b->setChecked(1);
    if (n & (1<<6)) ui->limit_3a->setChecked(1);
    if (n & (1<<7)) ui->limit_3b->setChecked(1);
    if (n & (1<<9)) ui->limit_4->setChecked(1);
// fill then set weapon
    for(int i=144;i<160;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),Items[i].name);}
    ui->combo_weapon->setCurrentIndex(ff7.slot[s].chars[curchar].weapon-16);
    load=false;
}
void MainWindow::on_btn_aeris_clicked()
{
    curchar=3;
    load=true;
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/aeris_icon"));
    charupdate();
//enable boxes for limits
    ui->limit_1a->setEnabled(1);
    ui->limit_1b->setEnabled(1);
    ui->limit_2a->setEnabled(1);
    ui->limit_2b->setEnabled(1);
    ui->limit_3a->setEnabled(1);
    ui->limit_3b->setEnabled(1);
    ui->limit_4->setEnabled(1);
//clear all checks
    ui->limit_1a->setChecked(0);
    ui->limit_1b->setChecked(0);
    ui->limit_2a->setChecked(0);
    ui->limit_2b->setChecked(0);
    ui->limit_3a->setChecked(0);
    ui->limit_3b->setChecked(0);
    ui->limit_4->setChecked(0);
//show enabled boxes
    ui->limit_1a->setVisible(1);
    ui->limit_1b->setVisible(1);
    ui->limit_2a->setVisible(1);
    ui->limit_2b->setVisible(1);
    ui->limit_3a->setVisible(1);
    ui->limit_3b->setVisible(1);
    ui->limit_4->setVisible(1);
//label boxes
    ui->limit_1a->setText(tr("Healing Wind"));
    ui->limit_1b->setText(tr("Seal Evil"));
    ui->limit_2a->setText(tr("Breath of the Earth"));
    ui->limit_2b->setText(tr("Fury Brand"));
    ui->limit_3a->setText(tr("Planet Protector"));
    ui->limit_3b->setText(tr("Pulse of Life"));
    ui->limit_4->setText(tr("Great Gospel"));
//check off learned limits
    int n = ff7.slot[s].chars[curchar].limits;
    if (n & (1<<0)) ui->limit_1a->setChecked(1);
    if (n & (1<<1)) ui->limit_1b->setChecked(1);
    if (n & (1<<3)) ui->limit_2a->setChecked(1);
    if (n & (1<<4)) ui->limit_2b->setChecked(1);
    if (n & (1<<6)) ui->limit_3a->setChecked(1);
    if (n & (1<<7)) ui->limit_3b->setChecked(1);
    if (n & (1<<9)) ui->limit_4->setChecked(1);
//fill weapons and select current
    for(int i=190;i<201;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),Items[i].name);}
    ui->combo_weapon->setCurrentIndex(ff7.slot[s].chars[curchar].weapon-62);
    load=false;
}
void MainWindow::on_btn_red_clicked()
{
    curchar=4;
    load=true;
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/red_icon"));
    charupdate();
//enable boxes for limits
    ui->limit_1a->setEnabled(1);
    ui->limit_1b->setEnabled(1);
    ui->limit_2a->setEnabled(1);
    ui->limit_2b->setEnabled(1);
    ui->limit_3a->setEnabled(1);
    ui->limit_3b->setEnabled(1);
    ui->limit_4->setEnabled(1);
//clear all checks
    ui->limit_1a->setChecked(0);
    ui->limit_1b->setChecked(0);
    ui->limit_2a->setChecked(0);
    ui->limit_2b->setChecked(0);
    ui->limit_3a->setChecked(0);
    ui->limit_3b->setChecked(0);
    ui->limit_4->setChecked(0);
//show enabled boxes
    ui->limit_1a->setVisible(1);
    ui->limit_1b->setVisible(1);
    ui->limit_2a->setVisible(1);
    ui->limit_2b->setVisible(1);
    ui->limit_3a->setVisible(1);
    ui->limit_3b->setVisible(1);
    ui->limit_4->setVisible(1);
//label boxes
    ui->limit_1a->setText(tr("Sled Fang"));
    ui->limit_1b->setText(tr("Lunatic High"));
    ui->limit_2a->setText(tr("Blood Fang"));
    ui->limit_2b->setText(tr("Stardust Ray"));
    ui->limit_3a->setText(tr("Howling Moon"));
    ui->limit_3b->setText(tr("Earth Rave"));
    ui->limit_4->setText(tr("Cosmo Memory"));
//set learned limits
    int n = ff7.slot[s].chars[curchar].limits;
    if (n & (1<<0)) ui->limit_1a->setChecked(1);
    if (n & (1<<1)) ui->limit_1b->setChecked(1);
    if (n & (1<<3)) ui->limit_2a->setChecked(1);
    if (n & (1<<4)) ui->limit_2b->setChecked(1);
    if (n & (1<<6)) ui->limit_3a->setChecked(1);
    if (n & (1<<7)) ui->limit_3b->setChecked(1);
    if (n & (1<<9)) ui->limit_4->setChecked(1);
//fill and set weapons
    for(int i=176;i<190;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),Items[i].name);}
    ui->combo_weapon->setCurrentIndex(ff7.slot[s].chars[curchar].weapon-48);
    load=false;
}
void MainWindow::on_btn_yuffie_clicked()
{
    curchar=5;
    load=true;
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/yuffie_icon"));
    charupdate();
//enable boxes for limits
    ui->limit_1a->setEnabled(1);
    ui->limit_1b->setEnabled(1);
    ui->limit_2a->setEnabled(1);
    ui->limit_2b->setEnabled(1);
    ui->limit_3a->setEnabled(1);
    ui->limit_3b->setEnabled(1);
    ui->limit_4->setEnabled(1);
//clear all checks
    ui->limit_1a->setChecked(0);
    ui->limit_1b->setChecked(0);
    ui->limit_2a->setChecked(0);
    ui->limit_2b->setChecked(0);
    ui->limit_3a->setChecked(0);
    ui->limit_3b->setChecked(0);
    ui->limit_4->setChecked(0);
//show enabled boxes
    ui->limit_1a->setVisible(1);
    ui->limit_1b->setVisible(1);
    ui->limit_2a->setVisible(1);
    ui->limit_2b->setVisible(1);
    ui->limit_3a->setVisible(1);
    ui->limit_3b->setVisible(1);
    ui->limit_4->setVisible(1);
//label boxes
    ui->limit_1a->setText(tr("Greased Lightning"));
    ui->limit_1b->setText(tr("Clear Tranquil"));
    ui->limit_2a->setText(tr("Landscaper"));
    ui->limit_2b->setText(tr("Bloodfest"));
    ui->limit_3a->setText(tr("Gauntlet"));
    ui->limit_3b->setText(tr("Doom of the Living"));
    ui->limit_4->setText(tr("All Creation"));
//set learned limits
    int n = ff7.slot[s].chars[curchar].limits;
    if (n & (1<<0)) ui->limit_1a->setChecked(1);
    if (n & (1<<1)) ui->limit_1b->setChecked(1);
    if (n & (1<<3)) ui->limit_2a->setChecked(1);
    if (n & (1<<4)) ui->limit_2b->setChecked(1);
    if (n & (1<<6)) ui->limit_3a->setChecked(1);
    if (n & (1<<7)) ui->limit_3b->setChecked(1);
    if (n & (1<<9)) ui->limit_4->setChecked(1);
//fill and set weapons
    for(int i=215;i<229;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),Items[i].name);}
    ui->combo_weapon->setCurrentIndex(ff7.slot[s].chars[curchar].weapon-87);
    load=false;
}
void MainWindow::on_btn_cait_clicked()
{
    curchar=6;
    load=true;
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/cait_icon"));
    charupdate();
//enable boxes for limits
    ui->limit_1a->setEnabled(1);
    ui->limit_1b->setEnabled(0);
    ui->limit_2a->setEnabled(1);
    ui->limit_2b->setEnabled(0);
    ui->limit_3a->setEnabled(0);
    ui->limit_3b->setEnabled(0);
    ui->limit_4->setEnabled(0);
//clear all checks
    ui->limit_1a->setChecked(0);
    ui->limit_1b->setChecked(0);
    ui->limit_2a->setChecked(0);
    ui->limit_2b->setChecked(0);
    ui->limit_3a->setChecked(0);
    ui->limit_3b->setChecked(0);
    ui->limit_4->setChecked(0);
//show enabled boxes
    ui->limit_1a->setVisible(1);
    ui->limit_1b->setVisible(0);
    ui->limit_2a->setVisible(1);
    ui->limit_2b->setVisible(0);
    ui->limit_3a->setVisible(0);
    ui->limit_3b->setVisible(0);
    ui->limit_4->setVisible(0);
//label limits
    ui->limit_1a->setText(tr("Dice"));
    ui->limit_1b->setText("");
    ui->limit_2a->setText(tr("Slots"));
    ui->limit_2b->setText("");
    ui->limit_3a->setText("");
    ui->limit_3b->setText("");
    ui->limit_4->setText("");
//set learned limits
    int n = ff7.slot[s].chars[curchar].limits;
    if (n & (1<<0)) ui->limit_1a->setChecked(1);
    if (n & (1<<3)) ui->limit_2a->setChecked(1);
//fill and set weapon
    for(int i=229;i<242;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),Items[i].name);}
    ui->combo_weapon->setCurrentIndex(ff7.slot[s].chars[curchar].weapon-101);
    load=false;
}
void MainWindow::on_btn_vincent_clicked()
{
    curchar=7;
    load=true;
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/vincent_icon"));
    charupdate();
//enable boxes for limits
    ui->limit_1a->setEnabled(1);
    ui->limit_1b->setEnabled(0);
    ui->limit_2a->setEnabled(1);
    ui->limit_2b->setEnabled(0);
    ui->limit_3a->setEnabled(1);
    ui->limit_3b->setEnabled(0);
    ui->limit_4->setEnabled(1);
//clear all checks
    ui->limit_1a->setChecked(0);
    ui->limit_1b->setChecked(0);
    ui->limit_2a->setChecked(0);
    ui->limit_2b->setChecked(0);
    ui->limit_3a->setChecked(0);
    ui->limit_3b->setChecked(0);
    ui->limit_4->setChecked(0);
//show enabled boxes
    ui->limit_1a->setVisible(1);
    ui->limit_1b->setVisible(0);
    ui->limit_2a->setVisible(1);
    ui->limit_2b->setVisible(0);
    ui->limit_3a->setVisible(1);
    ui->limit_3b->setVisible(0);
    ui->limit_4->setVisible(1);
//label boxes
    ui->limit_1a->setText(tr("Gallian Beast"));
    ui->limit_1b->setText("");
    ui->limit_2a->setText(tr("Death Gigas"));
    ui->limit_2b->setText("");
    ui->limit_3a->setText(tr("Hellmasker"));
    ui->limit_3b->setText("");
    ui->limit_4->setText(tr("Chaos"));
//check learned limits
    int n = ff7.slot[s].chars[curchar].limits;
    if (n & (1<<0)) ui->limit_1a->setChecked(1);
    if (n & (1<<3)) ui->limit_2a->setChecked(1);
    if (n & (1<<6)) ui->limit_3a->setChecked(1);
    if (n & (1<<9)) ui->limit_4->setChecked(1);
//fill and select weapon
    for(int i=242;i<255;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),Items[i].name);}
    ui->combo_weapon->setCurrentIndex(ff7.slot[s].chars[curchar].weapon-114);
    load=false;
}
void MainWindow::on_btn_cid_clicked()
{
    curchar=8;
    load=true;
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/cid_icon"));
    charupdate();
//enable boxes for limits
    ui->limit_1a->setEnabled(1);
    ui->limit_1b->setEnabled(1);
    ui->limit_2a->setEnabled(1);
    ui->limit_2b->setEnabled(1);
    ui->limit_3a->setEnabled(1);
    ui->limit_3b->setEnabled(1);
    ui->limit_4->setEnabled(1);
//clear all checks
    ui->limit_1a->setChecked(0);
    ui->limit_1b->setChecked(0);
    ui->limit_2a->setChecked(0);
    ui->limit_2b->setChecked(0);
    ui->limit_3a->setChecked(0);
    ui->limit_3b->setChecked(0);
    ui->limit_4->setChecked(0);
//show enabled boxes
    ui->limit_1a->setVisible(1);
    ui->limit_1b->setVisible(1);
    ui->limit_2a->setVisible(1);
    ui->limit_2b->setVisible(1);
    ui->limit_3a->setVisible(1);
    ui->limit_3b->setVisible(1);
    ui->limit_4->setVisible(1);
//label boxes
    ui->limit_1a->setText(tr("Boost Jump"));
    ui->limit_1b->setText(tr("Dynamite"));
    ui->limit_2a->setText(tr("Hyper Jump"));
    ui->limit_2b->setText(tr("Dragon"));
    ui->limit_3a->setText(tr("Dragon Dive"));
    ui->limit_3b->setText(tr("Big Brawl"));
    ui->limit_4->setText(tr("Highwind"));
//set learned limits
    int n = ff7.slot[s].chars[curchar].limits;
    if (n & (1<<0)) ui->limit_1a->setChecked(1);
    if (n & (1<<1)) ui->limit_1b->setChecked(1);
    if (n & (1<<3)) ui->limit_2a->setChecked(1);
    if (n & (1<<4)) ui->limit_2b->setChecked(1);
    if (n & (1<<6)) ui->limit_3a->setChecked(1);
    if (n & (1<<7)) ui->limit_3b->setChecked(1);
    if (n & (1<<9)) ui->limit_4->setChecked(1);
//fill and set weapon
    for(int i=201;i<215;i++){ui->combo_weapon->addItem(QIcon(Items[i].image),Items[i].name);}
    ui->combo_weapon->setCurrentIndex(ff7.slot[s].chars[curchar].weapon-73);
    load=false;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Party TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_sb_gil_valueChanged()
{
    ff7.slot[s].gil = ui->sb_gil->value();
    ff7.slot[s].desc.gil = ff7.slot[s].gil;
}
void MainWindow::on_combo_party1_currentIndexChanged(int index)
{
    if(index == 12) //empty char slot?
    {
        ff7.slot[s].party[0] = 0xFF;
        //whipe all desc data if noone is there
        ff7.slot[s].desc.party[0]=ff7.slot[s].party[0];
        ff7.slot[s].desc.curHP =0;
        ff7.slot[s].desc.maxHP =0;
        ff7.slot[s].desc.curMP =0;
        ff7.slot[s].desc.maxMP =0;
        ff7.slot[s].desc.level =0;
        for(int n=0;n<16;n++)
        {
            ff7.slot[s].desc.name[n]=0xFF;
        }
    }
    else
    {
        ff7.slot[s].party[0] = index;
        ff7.slot[s].desc.party[0]=ff7.slot[s].party[0];
        ff7.slot[s].desc.curHP =ff7.slot[s].chars[ui->combo_party1->currentIndex()].curHP;
        ff7.slot[s].desc.maxHP =ff7.slot[s].chars[ui->combo_party1->currentIndex()].maxHP;
        ff7.slot[s].desc.curMP =ff7.slot[s].chars[ui->combo_party1->currentIndex()].curMP;
        ff7.slot[s].desc.maxMP =ff7.slot[s].chars[ui->combo_party1->currentIndex()].maxMP;
        ff7.slot[s].desc.level = ff7.slot[s].chars[ui->combo_party1->currentIndex()].level;
        for(int n=0;n<16;n++)
        {
            if(n<13){ff7.slot[s].desc.name[n]=ff7.slot[s].chars[ui->combo_party1->currentIndex()].name[n];}
            else{ff7.slot[s].desc.name[n]=0xFF;}
        }
    }
}
void MainWindow::on_combo_party2_currentIndexChanged(int index)
{
    if(index == 12){ff7.slot[s].party[1]= 0xFF;}
    else{ff7.slot[s].party[1] = index;}
    //either way set the desc
    ff7.slot[s].desc.party[1]=ff7.slot[s].party[1];
}
void MainWindow::on_combo_party3_currentIndexChanged(int index)
{
    if(index ==12){ff7.slot[s].party[2] =0xFF;}
    else{ff7.slot[s].party[2] = index;}
    ff7.slot[s].desc.party[2]=ff7.slot[s].party[2];
}
void MainWindow::on_sb_gp_valueChanged()
{
    ff7.slot[s].gp = ui->sb_gp->value();
}
void MainWindow::on_sb_runs_valueChanged()
{
    ff7.slot[s].runs = ui->sb_runs->value();
}
void MainWindow::on_sb_battles_valueChanged()
{
    ff7.slot[s].battles = ui->sb_battles->value();
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chocobo Tab~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//set data for pens outside
void MainWindow::on_combo_pen1_currentIndexChanged(int index)
{
    ff7.slot[s].pennedchocos[0]=index;
}
void MainWindow::on_combo_pen2_currentIndexChanged(int index)
{
    ff7.slot[s].pennedchocos[1]=index;
}
void MainWindow::on_combo_pen3_currentIndexChanged(int index)
{
    ff7.slot[s].pennedchocos[2]=index;
}
void MainWindow::on_combo_pen4_currentIndexChanged(int index)
{
    ff7.slot[s].pennedchocos[3]=index;
}
//set data for stables inside
void MainWindow::on_sb_stables_owned_valueChanged()
{
    ff7.slot[s].stables = ui->sb_stables_owned->value();
    if(ui->sb_stables_occupied->value() > ui->sb_stables_owned->value()){ui->sb_stables_occupied->setValue(ui->sb_stables_owned->value());}
}
void MainWindow::on_sb_stables_occupied_valueChanged(int value)
{
    if (value <= ui->sb_stables_owned->value())
    {
        ff7.slot[s].chocobomask = 0;
        for (int i=0;i<value;i++)
        {
            ff7.slot[s].chocobomask |= (1<<i);
        }
        ff7.slot[s].stablesoccupied = value;
        chocobo_refresh();
    }
    else {ui->sb_stables_occupied->setValue(ui->sb_stables_owned->value());}
}

/*~~~~~ChocoboStats~~~~~*/
void MainWindow::on_sb_c1_speed_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[0].speed = value;}
}
void MainWindow::on_sb_c1_maxspeed_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[0].maxspeed = value;}
}
void MainWindow::on_sb_c1_sprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[0].sprintspd = value;}
}
void MainWindow::on_sb_c1_maxsprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[0].maxsprintspd = value;}
}
void MainWindow::on_cb_c1_sex_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].chocobos[0].sex = index;}
}
void MainWindow::on_cb_c1_type_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].chocobos[0].type = index;}
}
void MainWindow::on_sb_c1_coop_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[0].coop= ui->sb_c1_coop->value();}
}
void MainWindow::on_sb_c1_accel_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[0].accel= ui->sb_c1_accel->value();}
}
void MainWindow::on_sb_c1_intel_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[0].intelligence = ui->sb_c1_intel->value();}
}
void MainWindow::on_sb_c1_raceswon_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[0].raceswon = ui->sb_c1_raceswon->value();}
}
void MainWindow::on_sb_c1_pcount_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[0].pcount= ui->sb_c1_pcount->value();}
}

void MainWindow::on_sb_c2_speed_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[1].speed = value;}
}
void MainWindow::on_sb_c2_maxspeed_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[1].maxspeed = value;}
}
void MainWindow::on_sb_c2_sprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[1].sprintspd = value;}
}
void MainWindow::on_sb_c2_maxsprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[1].maxsprintspd = value;}
}
void MainWindow::on_cb_c2_sex_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].chocobos[1].sex = index;}
}
void MainWindow::on_cb_c2_type_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].chocobos[1].type = index;}
}
void MainWindow::on_sb_c2_coop_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[1].coop= ui->sb_c2_coop->value();}
}
void MainWindow::on_sb_c2_accel_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[1].accel= ui->sb_c2_accel->value();}
}
void MainWindow::on_sb_c2_intel_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[1].intelligence = ui->sb_c2_intel->value();}
}
void MainWindow::on_sb_c2_raceswon_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[1].raceswon = ui->sb_c2_raceswon->value();}
}
void MainWindow::on_sb_c2_pcount_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[1].pcount= ui->sb_c2_pcount->value();}
}

void MainWindow::on_sb_c3_speed_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[2].speed = value;}
}
void MainWindow::on_sb_c3_maxspeed_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[2].maxspeed = value;}
}
void MainWindow::on_sb_c3_sprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[2].sprintspd = value;}
}
void MainWindow::on_sb_c3_maxsprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[2].maxsprintspd = value;}
}
void MainWindow::on_cb_c3_sex_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].chocobos[2].sex = index;}
}
void MainWindow::on_cb_c3_type_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].chocobos[2].type = index;}
}
void MainWindow::on_sb_c3_coop_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[2].coop= ui->sb_c3_coop->value();}
}
void MainWindow::on_sb_c3_accel_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[2].accel= ui->sb_c3_accel->value();}
}
void MainWindow::on_sb_c3_intel_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[2].intelligence = ui->sb_c3_intel->value();}
}
void MainWindow::on_sb_c3_raceswon_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[2].raceswon = ui->sb_c3_raceswon->value();}
}
void MainWindow::on_sb_c3_pcount_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[2].pcount= ui->sb_c3_pcount->value();}
}

void MainWindow::on_sb_c4_speed_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[3].speed = value;}
}
void MainWindow::on_sb_c4_maxspeed_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[3].maxspeed = value;}
}
void MainWindow::on_sb_c4_sprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[3].sprintspd = value;}
}
void MainWindow::on_sb_c4_maxsprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].chocobos[3].maxsprintspd = value;}
}

void MainWindow::on_cb_c4_sex_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].chocobos[3].sex = index;}
}
void MainWindow::on_cb_c4_type_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].chocobos[3].type = index;}
}
void MainWindow::on_sb_c4_coop_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[3].coop= ui->sb_c4_coop->value();}
}
void MainWindow::on_sb_c4_accel_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[3].accel= ui->sb_c4_accel->value();}
}
void MainWindow::on_sb_c4_intel_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[3].intelligence = ui->sb_c4_intel->value();}
}
void MainWindow::on_sb_c4_raceswon_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[3].raceswon = ui->sb_c4_raceswon->value();}
}
void MainWindow::on_sb_c4_pcount_valueChanged()
{
    if(!load){ff7.slot[s].chocobos[3].pcount= ui->sb_c4_pcount->value();}
}

void MainWindow::on_sb_c5_speed_valueChanged(int value)
{
    if(!load){ff7.slot[s].choco56[0].speed = value;}
}
void MainWindow::on_sb_c5_maxspeed_valueChanged(int value)
{
    if(!load){ff7.slot[s].choco56[0].maxspeed = value;}
}
void MainWindow::on_sb_c5_sprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].choco56[0].sprintspd = value;}
}
void MainWindow::on_sb_c5_maxsprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].choco56[0].maxsprintspd = value;}
}
void MainWindow::on_cb_c5_sex_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].choco56[0].sex = index;}
}
void MainWindow::on_cb_c5_type_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].choco56[0].type = index;}
}
void MainWindow::on_sb_c5_coop_valueChanged()
{
    if(!load){ff7.slot[s].choco56[0].coop= ui->sb_c5_coop->value();}
}
void MainWindow::on_sb_c5_accel_valueChanged()
{
    if(!load){ff7.slot[s].choco56[0].accel= ui->sb_c5_accel->value();}
}
void MainWindow::on_sb_c5_intel_valueChanged()
{
    if(!load){ff7.slot[s].choco56[0].intelligence = ui->sb_c5_intel->value();}
}
void MainWindow::on_sb_c5_raceswon_valueChanged()
{
    if(!load){ff7.slot[s].choco56[0].raceswon = ui->sb_c5_raceswon->value();}
}
void MainWindow::on_sb_c5_pcount_valueChanged()
{
    if(!load){ff7.slot[s].choco56[0].pcount= ui->sb_c5_pcount->value();}
}

void MainWindow::on_sb_c6_speed_valueChanged(int value)
{
    if(!load){ff7.slot[s].choco56[1].speed = value;}
}
void MainWindow::on_sb_c6_maxspeed_valueChanged(int value)
{
    if(!load){ff7.slot[s].choco56[1].maxspeed = value;}
}
void MainWindow::on_sb_c6_sprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].choco56[1].sprintspd = value;}
}
void MainWindow::on_sb_c6_maxsprint_valueChanged(int value)
{
    if(!load){ff7.slot[s].choco56[1].maxsprintspd = value;}
}
void MainWindow::on_cb_c6_sex_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].choco56[1].sex = index;}
}
void MainWindow::on_cb_c6_type_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].choco56[1].type = index;}
}
void MainWindow::on_sb_c6_coop_valueChanged()
{
    if(!load){ff7.slot[s].choco56[1].coop= ui->sb_c6_coop->value();}
}
void MainWindow::on_sb_c6_accel_valueChanged()
{
    if(!load){ff7.slot[s].choco56[1].accel= ui->sb_c6_accel->value();}
}
void MainWindow::on_sb_c6_intel_valueChanged()
{
    if(!load){ff7.slot[s].choco56[1].intelligence = ui->sb_c6_intel->value();}
}
void MainWindow::on_sb_c6_raceswon_valueChanged()
{
    if(!load){ff7.slot[s].choco56[1].raceswon = ui->sb_c6_raceswon->value();}
}
void MainWindow::on_sb_c6_pcount_valueChanged()
{
    if(!load){ff7.slot[s].choco56[1].pcount= ui->sb_c6_pcount->value();}
}
void MainWindow::on_sb_c1_stamina_valueChanged()
{
    ff7.slot[s].chocostaminas[0] = ui->sb_c1_stamina->value();//Bug fixed Before was ui->sb_c1_stamina->value()*10 and (999*10 != 9999), is 9990 (Vegeta_Ss4) v0.8.3
}
void MainWindow::on_sb_c2_stamina_valueChanged()
{
    ff7.slot[s].chocostaminas[1] = ui->sb_c2_stamina->value();//Bug fix (Vegeta_Ss4) v0.8.3
}
void MainWindow::on_sb_c3_stamina_valueChanged()
{
    ff7.slot[s].chocostaminas[2] = ui->sb_c3_stamina->value();//Bug fix (Vegeta_Ss4) v0.8.3
}
void MainWindow::on_sb_c4_stamina_valueChanged()
{
    ff7.slot[s].chocostaminas[3] = ui->sb_c4_stamina->value();//Bug fix (Vegeta_Ss4) v0.8.3
}
void MainWindow::on_sb_c5_stamina_valueChanged()
{
    ff7.slot[s].chocostaminas[4] = ui->sb_c5_stamina->value();//Bug fix (Vegeta_Ss4) v0.8.3
}
void MainWindow::on_sb_c6_stamina_valueChanged()
{
    ff7.slot[s].chocostaminas[5] = ui->sb_c6_stamina->value();//Bug fix (Vegeta_Ss4) v0.8.3
}
void MainWindow::on_line_c1_name_lostFocus()
{
    if(!load)
    {
        for (int i=0;i<6;i++){ff7.slot[s].chocobonames[0][i] =0xFF;}
        for (int i=0;i<ui->line_c1_name->text().size();i++){ff7.slot[s].chocobonames[0][i] = chFF7[ui->line_c1_name->text().at(i).toAscii()];}
    }
}
void MainWindow::on_line_c2_name_lostFocus()
{
    for (int i=0;i<6;i++){ff7.slot[s].chocobonames[1][i] =0xFF;}
    for (int i=0;i<ui->line_c2_name->text().size();i++){ff7.slot[s].chocobonames[1][i] = chFF7[ui->line_c2_name->text().at(i).toAscii()];}
}
void MainWindow::on_line_c3_name_lostFocus()
{
    for (int i=0;i<6;i++){ff7.slot[s].chocobonames[2][i] =0xFF;}
    for (int i=0;i<ui->line_c3_name->text().size();i++){ff7.slot[s].chocobonames[2][i] = chFF7[ui->line_c3_name->text().at(i).toAscii()];}
}
void MainWindow::on_line_c4_name_lostFocus()
{
    for (int i=0;i<6;i++){ff7.slot[s].chocobonames[3][i] =0xFF;}
    for (int i=0;i<ui->line_c4_name->text().size();i++){ff7.slot[s].chocobonames[3][i] = chFF7[ui->line_c4_name->text().at(i).toAscii()];}
}
void MainWindow::on_line_c5_name_lostFocus()
{
    for (int i=0;i<6;i++){ff7.slot[s].chocobonames[4][i] =0xFF;}
    for (int i=0;i<ui->line_c5_name->text().size();i++){ff7.slot[s].chocobonames[4][i] = chFF7[ui->line_c5_name->text().at(i).toAscii()];}
}
void MainWindow::on_line_c6_name_lostFocus()
{
    for (int i=0;i<6;i++){ff7.slot[s].chocobonames[5][i] =0xFF;}
    for (int i=0;i<ui->line_c6_name->text().size();i++){ff7.slot[s].chocobonames[5][i] = chFF7[ui->line_c6_name->text().at(i).toAscii()];}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OTHERS TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_list_phs_chars_itemChanged()
{
    if(!load)
    {
        int j = ui->list_phs_chars->currentRow();       
        if(ui->list_phs_chars->currentItem()->checkState() ==Qt::Unchecked){ff7.slot[s].phsmask |=(1 <<j);}
        else{ff7.slot[s].phsmask &= ~(1<<j);}
    }
}

void MainWindow::on_list_chars_unlocked_itemChanged()
{
    if(!load)
    {
        int j=ui->list_chars_unlocked->currentRow();
        if(ui->list_chars_unlocked->currentItem()->checkState() ==Qt::Checked){ff7.slot[s].unlockedchars |= (1<<j);}
        else{ff7.slot[s].unlockedchars &= ~(1<<j);}
    }
}
void MainWindow::on_sb_curdisc_valueChanged()
{
    if(!load){ff7.slot[s].disc = ui->sb_curdisc->value();}
}
void MainWindow::on_sb_love_barret_valueChanged()
{
    if(!load){ff7.slot[s].love.barret = ui->sb_love_barret->value();}
}
void MainWindow::on_sb_love_aeris_valueChanged()
{
    if(!load){ff7.slot[s].love.aeris = ui->sb_love_aeris->value();}
}
void MainWindow::on_sb_love_tifa_valueChanged()
{
    if(!load){ff7.slot[s].love.tifa = ui->sb_love_tifa->value();}
}
void MainWindow::on_sb_love_yuffie_valueChanged()
{
    if(!load){ff7.slot[s].love.yuffie = ui->sb_love_yuffie->value();}
}

void MainWindow::on_sb_time_hour_valueChanged(int value)
{
    if(!load){ff7.slot[s].time = ((value*3600) + (ui->sb_time_min->value()*60) + (ui->sb_time_sec->value())); ff7.slot[s].desc.time = ff7.slot[s].time;}
}

void MainWindow::on_sb_time_min_valueChanged(int value)
{
    if(!load){ff7.slot[s].time = ( (ui->sb_time_hour->value()*3600) + ((value*60)) + (ui->sb_time_sec->value()) );ff7.slot[s].desc.time = ff7.slot[s].time; }
}

void MainWindow::on_sb_time_sec_valueChanged(int value)
{
    if(!load){ff7.slot[s].time = ((value*3600) + (ui->sb_time_min->value()*60) + (value)); ff7.slot[s].desc.time = ff7.slot[s].time;}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Item Tab~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_list_flyers_itemChanged()
{
    if(!load)
    {
        int j=ui->list_flyers->currentRow();
        ff7.slot[s].turtleflyers=0x40;
        for (int i=0;i<6;i++)
        {
            ui->list_flyers->setCurrentRow(i);
            if(ui->list_flyers->currentItem()->checkState() ==Qt::Checked){ff7.slot[s].turtleflyers |= (1 << i);}
        }
        ui->list_flyers->setCurrentRow(j);
    }
}
void MainWindow::on_list_keyitems_itemChanged()
{
    if (!load)
    {
        int j = ui->list_keyitems->currentRow();
        if (ui->list_keyitems->currentItem()->checkState() == Qt::Checked){ff7.slot[s].keyitems[j/8] |= (1<<j%8);}
        else{ff7.slot[s].keyitems[j/8] &= ~(1<<j%8);}
    }
}
void MainWindow::on_clearItem_clicked()
{
    ff7.slot[s].items[ui->tbl_itm->currentRow()].id = 0xFF;
    ff7.slot[s].items[ui->tbl_itm->currentRow()].qty = 0xFF;
    guirefresh();
}
void MainWindow::on_combo_additem_currentIndexChanged(int index)
{
    if(!load)
    {   //we must also set the qty, since that determins how the table and the game will reconize the item and prevents bug#3014592.
        if (index<256){ff7.slot[s].items[ui->tbl_itm->currentRow()].id = index;ff7.slot[s].items[ui->tbl_itm->currentRow()].qty = quint8(ui->sb_addqty->value() * 2);}
        else{ff7.slot[s].items[ui->tbl_itm->currentRow()].id = (index-256);ff7.slot[s].items[ui->tbl_itm->currentRow()].qty  = quint8(ui->sb_addqty->value()* 2) +1;}
        guirefresh();
    }
}
void MainWindow::on_sb_addqty_valueChanged(int value)
{
    if(!load)
    {
        if (ui->combo_additem->currentIndex()<256){ff7.slot[s].items[ui->tbl_itm->currentRow()].qty = quint8(value * 2);}
        else{ff7.slot[s].items[ui->tbl_itm->currentRow()].qty  = quint8(value* 2) +1;}
        guirefresh();
    }
}
void MainWindow::on_tbl_itm_currentCellChanged(int row)
{
    if(!load)
    {
        if (ff7.slot[s].items[row].qty == 255 && ff7.slot[s].items[row].id == 255){/*empty slot.....do nothing*/}
        else
        {
            load =true;
            if(ff7.slot[s].items[row].qty %2 ==0)
            {
                ui->combo_additem->setCurrentIndex(ff7.slot[s].items[row].id);
                ui->sb_addqty->setValue(ff7.slot[s].items[row].qty/2);
            }
            else
            {
                ui->combo_additem->setCurrentIndex(ff7.slot[s].items[row].id+256);
                ui->sb_addqty->setValue(ff7.slot[s].items[row].qty/2);
            }
            load = false;
        }
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MATERIA TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_tbl_materia_currentCellChanged(int row)
{
    if(!load)
    {
        if(ff7.slot[s].materias[row].id == 0x2C)
        {
            ui->eskill_group->setVisible(true);
            geteskills(row);
            ui->combo_add_mat->setCurrentIndex(ff7.slot[s].materias[row].id);
            ui->sb_addap->setEnabled(0);
        }
        else if(ff7.slot[s].materias[row].id == 0xFF) //if the slot is empty take some precautions
        {
            load=true;
            ui->lbl_mat_stats->setText(tr("Empty Slot"));
            ui->lcd_ap_master->display(0);
            ui->sb_addap->setValue(0);
            ui->sb_addap->setMaximum(0);
            ui->combo_mat_type->setCurrentIndex(0);
            ui->combo_add_mat->setCurrentIndex(0);
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
            ui->combo_add_mat->setCurrentIndex(ff7.slot[s].materias[row].id);
            ui->sb_addap->setEnabled(1);
            ui->sb_addap->setValue(ff7.slot[s].materias[row].ap[0] |(ff7.slot[s].materias[row].ap[1] << 8) | (ff7.slot[s].materias[row].ap[2] << 16));
        }
    }
}

void MainWindow::on_sb_addap_valueChanged(int value)
{
    if(!load && ui->tbl_materia->currentRow() >-1)
    {
        if(value == Materias[ui->combo_add_mat->currentIndex()].ap[Materias[ui->combo_add_mat->currentIndex()].levels -2] && Materias[ui->combo_add_mat->currentIndex()].levels >1)
        {
            for(int i=0;i<3;i++){ff7.slot[s].materias[ui->tbl_materia->currentRow()].ap[i] = 0xFF;}
        }

        else
        {
            int a = (value & 0xff);
            int b = (value & 0xff00) >> 8;
            int c = (value & 0xff0000) >> 16;
            ff7.slot[s].materias[ui->tbl_materia->currentRow()].ap[0] = a;
            ff7.slot[s].materias[ui->tbl_materia->currentRow()].ap[1] = b;
            ff7.slot[s].materias[ui->tbl_materia->currentRow()].ap[2] = c;
        }
        guirefresh();
    }
}
void MainWindow::on_combo_add_mat_currentIndexChanged(int index)
{
    if(ui->combo_add_mat->currentText() =="DON'T USE")// this is a placeholder materia
    {
        QMessageBox::information(this,tr("Empty Materia"),tr("Place holder Materia Detected\n Remember 16777215 AP = master"));
        guirefresh();// clean up the gui.
        return; //we are done here.
    }

    ui->combo_mat_type->setCurrentIndex(Materias[index].type);
    for(int i=0;i<ui->combo_add_mat_2->count();i++)
    {
        if(ui->combo_add_mat_2->itemText(i)==Materias[index].name){ui->combo_add_mat_2->setCurrentIndex(i);}
    }

    if(!load)
    {
        ff7.slot[s].materias[ui->tbl_materia->currentRow()].id = index;
        guirefresh();
    }
}
void MainWindow::on_btn_m_lvl1_clicked()
{
    ui->sb_addap->setValue(0);
    guirefresh();
}
void MainWindow::on_btn_m_lvl2_clicked()
{
    ui->sb_addap->setValue(Materias[ui->combo_add_mat->currentIndex()].ap[0]);
    guirefresh();
}
void MainWindow::on_btn_m_lvl3_clicked()
{
    ui->sb_addap->setValue(Materias[ui->combo_add_mat->currentIndex()].ap[1]);
    guirefresh();
}
void MainWindow::on_btn_m_lvl4_clicked()
{
    ui->sb_addap->setValue(Materias[ui->combo_add_mat->currentIndex()].ap[2]);
    guirefresh();
}
void MainWindow::on_btn_m_lvl5_clicked()
{
    ui->sb_addap->setValue(Materias[ui->combo_add_mat->currentIndex()].ap[3]);
    guirefresh();
}

void MainWindow::on_combo_mat_type_currentIndexChanged(int index)
{
    if(!load)
    {
        ui->combo_add_mat_2->clear();
        if(index == 0)
        {
            for(int i=0;i<0x5B;i++)
            {
                if(Materias[i].name !="DON'T USE"){ui->combo_add_mat_2->addItem(QIcon(Materias[i].image),Materias[i].name);}
            }
        }
        else
        {
            load=true;
            for(int i=0;i<0x5B;i++){if(index==Materias[i].type){ui->combo_add_mat_2->addItem(QIcon(Materias[i].image),Materias[i].name);}}
            load=false;
        }
    }
}
void MainWindow::on_combo_add_mat_2_currentIndexChanged()
{
    if(!load)
    {//set combo_add_mat.setCurrentindex = selected materia.id
        for(int i=0;i<0x5B;i++)
        {
            if(ui->combo_add_mat_2->currentText()== Materias[i].name){ui->combo_add_mat->setCurrentIndex(i);}
        }
// if its eskill set it up right , or else do normal setup.
        if(ui->combo_add_mat_2->currentText()== "Enemy Skill"){ui->eskill_group->setVisible(true);ui->sb_addap->setEnabled(0);geteskills(ui->tbl_materia->currentRow());}
        else{ui->eskill_group->setVisible(false);ui->sb_addap->setEnabled(1);}
    }
}
void MainWindow::on_clearMateria_clicked()
{
    ff7.slot[s].materias[ui->tbl_materia->currentRow()].id = 0xFF;
    ui->sb_addap->setValue(0xFFFFFF);
    guirefresh();
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
    load = true;
    quint32 temp = ff7.slot[s].materias[row].ap[0] |(ff7.slot[s].materias[row].ap[1] << 8) | (ff7.slot[s].materias[row].ap[2] << 16);
    ui->sb_addap->setValue(temp);// no one cares cause there is no ap really..
    on_btn_eskillclear_clicked();
    for (int i=0;i<24;i++)
    {
        ui->list_eskill->setCurrentRow(i);
        if ((1 << i) & temp){ui->list_eskill->currentItem()->setCheckState(Qt::Checked);}
    }
    ui->list_eskill->setCurrentRow(-1);
    load = false;
}
void MainWindow::on_list_eskill_itemChanged()
{
    if(!load)
    {
        quint32 temp = ff7.slot[s].materias[ui->tbl_materia->currentRow()].ap[0] |(ff7.slot[s].materias[ui->tbl_materia->currentRow()].ap[1] << 8) | (ff7.slot[s].materias[ui->tbl_materia->currentRow()].ap[2] << 16);
        if(ui->list_eskill->currentItem()->checkState()){temp |= (1 << ui->list_eskill->currentRow());}
        else{temp &= ~(1<<ui->list_eskill->currentRow());}
        load = true;
        ui->sb_addap->setValue(temp);
        load = false;
        int a = (temp & 0xff);
        int b = (temp & 0xff00) >> 8;
        int c = (temp & 0xff0000) >> 16;
        ff7.slot[s].materias[ui->tbl_materia->currentRow()].ap[0] = a;
        ff7.slot[s].materias[ui->tbl_materia->currentRow()].ap[1] = b;
        ff7.slot[s].materias[ui->tbl_materia->currentRow()].ap[2] = c;
    }
}
void MainWindow::on_btn_eskillclear_clicked()
{
    for (int i=0;i<24;i++)
    {
        ui->list_eskill->setCurrentRow(i);
        ui->list_eskill->currentItem()->setCheckState(Qt::Unchecked);
    }//loop thru and uncheck no need to apply each one should thrown an itemChanged() event
    ui->list_eskill->setCurrentRow(-1);
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
void MainWindow::on_sb_map_id_valueChanged()
{
    if(!load){ff7.slot[s].mapid= ui->sb_map_id->value();}
}
void MainWindow::on_sb_loc_id_valueChanged()
{
    if(!load){ff7.slot[s].locationid = ui->sb_loc_id->value();}
}
void MainWindow::on_line_location_textChanged()
{
    if (!load)
    {
        for (int i=0;i<32;i++){ff7.slot[s].desc.location[i] =0xFF;}
        for (int i=0;i<ui->line_location->text().size();i++){ff7.slot[s].desc.location[i] = chFF7[ui->line_location->text().at(i).toAscii()];}
    }
}
void MainWindow::on_sb_coordx_valueChanged()
{
    if(!load){ff7.slot[s].coord.x = ui->sb_coordx->value();}
}
void MainWindow::on_sb_coordy_valueChanged()
{
    if(!load){ff7.slot[s].coord.y = ui->sb_coordy->value();}
}
void MainWindow::on_sb_coordz_valueChanged()
{
    if(!load){ff7.slot[s].coord.z = ui->sb_coordz->value();}
}

//char stats tab
void MainWindow::on_cb_id_toggled(bool checked)
{

    if(!load)
    {
        if (curchar ==6)
        {
            if (checked){ff7.slot[s].chars[6].id = 9;ui->lbl_avatar->setPixmap(QPixmap(":/icon/y_cloud_icon"));ui->btn_cait->setStyleSheet("image: url(:/icon/y_cloud_icon);");}
            else {ff7.slot[s].chars[6].id = 6;ui->lbl_avatar->setPixmap(QPixmap(":/icon/cait_icon"));ui->btn_cait->setStyleSheet("image: url(:/icon/cait_icon);");}
        }
        if (curchar ==7)
        {
            if (checked){ff7.slot[s].chars[7].id = 10;ui->lbl_avatar->setPixmap(QPixmap(":/icon/sep_icon"));ui->btn_vincent->setStyleSheet("image: url(:/icon/sep_icon);");}
            else {ff7.slot[s].chars[7].id = 7;ui->lbl_avatar->setPixmap(QPixmap(":/icon/vincent_icon"));ui->btn_vincent->setStyleSheet("image: url(:/icon/vincent_icon);");}
        }
    }
}
void MainWindow::on_line_name_lostFocus()
{
    if(!load)
    {
        for (int i=0;i<12;i++){ff7.slot[s].chars[curchar].name[i] =0xFF;}
        for (int i=0;i<ui->line_name->text().size();i++){ff7.slot[s].chars[curchar].name[i] = chFF7[ui->line_name->text().at(i).toAscii()];}
        if (curchar == ui->combo_party1->currentIndex())
        {
            for (int i=0;i<16;i++){ff7.slot[s].desc.name[i] =0xFF;}
            for (int i=0;i<ui->line_name->text().size();i++){ff7.slot[s].desc.name[i] = chFF7[ui->line_name->text().at(i).toAscii()];}
        }
    }
}
void MainWindow::on_sb_lvl_valueChanged()
{
    if(!load)
    {
        ff7.slot[s].chars[curchar].level = ui->sb_lvl->value();
        ff7.slot[s].desc.level = ui->sb_lvl->value();
    }
}
void MainWindow::on_sb_curhp_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].curHP = ui->sb_curhp->value();}
}
void MainWindow::on_sb_curmp_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].curMP = ui->sb_curmp->value();}
}
void MainWindow::on_sb_maxhp_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].maxHP =ui->sb_maxhp->value();}
}
void MainWindow::on_sb_maxmp_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].maxMP =ui->sb_maxmp->value();}
}
void MainWindow::on_sb_hp_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].baseHP = ui->sb_hp->value();}
}
void MainWindow::on_sb_mp_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].baseMP = ui->sb_mp->value();}
}
void MainWindow::on_sb_next_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].expNext =  ui->sb_next->value();}
}
void MainWindow::on_sb_exp_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].exp = ui->sb_exp->value();}
}
void MainWindow::on_sb_kills_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].kills = ui->sb_kills->value();}
}
void MainWindow::on_sb_str_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].strength = ui->sb_str->value();}
}
void MainWindow::on_sb_dex_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].dexterity = ui->sb_dex->value();}
}
void MainWindow::on_sb_mag_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].magic = ui->sb_mag->value();}
}
void MainWindow::on_sb_vit_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].vitality = ui->sb_vit->value();}
}
void MainWindow::on_sb_spr_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].spirit = ui->sb_spr->value();}
}
void MainWindow::on_sb_lck_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].luck = ui->sb_lck->value();}
}
void MainWindow::on_sb_strbonus_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].strength_bonus = ui->sb_strbonus->value();}
}
void MainWindow::on_sb_dexbonus_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].dexterity_bonus = ui->sb_dexbonus->value();}
}
void MainWindow::on_sb_magbonus_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].magic_bonus = ui->sb_magbonus->value();}
}
void MainWindow::on_sb_vitbonus_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].vitality_bonus = ui->sb_vitbonus->value();}
}
void MainWindow::on_sb_sprbonus_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].spirit_bonus = ui->sb_sprbonus->value();}
}
void MainWindow::on_sb_lckbonus_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].luck_bonus = ui->sb_lckbonus->value();}
}
void MainWindow::on_cb_front_clicked(bool checked)
{
    if(!load)
    {
        if(checked) ff7.slot[s].chars[curchar].flags[1] = 255;
        if(!checked)ff7.slot[s].chars[curchar].flags[1] =254;
    }
}
void MainWindow::on_cb_fury_clicked(bool checked)
{
    if(!load)
    {
        if(checked){ui->cb_sadness->setChecked(0); ff7.slot[s].chars[curchar].flags[0] =32;}
        else {ff7.slot[s].chars[curchar].flags[0]=0;}
    }
}
void MainWindow::on_cb_sadness_clicked(bool checked)
{
    if(!load)
    {
        if(checked){ui->cb_fury->setChecked(0); ff7.slot[s].chars[curchar].flags[0] =16;}
        else {ff7.slot[s].chars[curchar].flags[0]=0;}
    }
}
//char limit stuff
void MainWindow::on_sb_used1_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].timesused1 = ui->sb_used1->value();}
}
void MainWindow::on_sb_used2_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].timesused2 = ui->sb_used2->value();}
}
void MainWindow::on_sb_used3_valueChanged()
{
    if(!load){ff7.slot[s].chars[curchar].timesused3 = ui->sb_used3->value();}
}
void MainWindow::on_sb_limitlvl_valueChanged(int value)
{
    if(!load){ff7.slot[s].chars[curchar].limitlevel= value;} //ui->sb_limitlvl->value();
}
void MainWindow::on_slide_limit_valueChanged(int value)
{
    if(!load){ff7.slot[s].chars[curchar].limitbar = value;} //ui->slide_limit->value();
}
void MainWindow::limitapply()
{
    ff7.slot[s].chars[curchar].limits = 0;
    if (curchar == 7)
    {
        if (ui->limit_1a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<0);
        if (ui->limit_2a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<3);
        if (ui->limit_3a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<6);
        if (ui->limit_4 ->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<9);
    }
    else if (curchar == 6)
    {
        if (ui->limit_1a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<0);
        if (ui->limit_2a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<3);
    }
    else
    {
        if (ui->limit_1a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<0);
        if (ui->limit_1b->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<1);
        if (ui->limit_2a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<3);
        if (ui->limit_2b->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<4);
        if (ui->limit_3a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<6);
        if (ui->limit_3b->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<7);
        if (ui->limit_4 ->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<9);
    }
}
void MainWindow::on_limit_1a_toggled()
{
    if(!load) {limitapply();}
}
void MainWindow::on_limit_1b_toggled()
{
    if(!load) {limitapply();}
}
void MainWindow::on_limit_2a_toggled()
{
    if(!load) {limitapply();}
}
void MainWindow::on_limit_2b_toggled()
{
    if(!load) {limitapply();}
}
void MainWindow::on_limit_3a_toggled()
{
    if(!load) {limitapply();}
}
void MainWindow::on_limit_3b_toggled()
{
    if(!load) {limitapply();}
}
void MainWindow::on_limit_4_toggled()
{
    if(!load) {limitapply();}
}

//Char Equiptment Tab

void MainWindow::on_combo_weapon_currentIndexChanged()
{
    setweaponslots();
}
void MainWindow::on_combo_armor_currentIndexChanged(int index)
{
    if(!load)
    {
        ff7.slot[s].chars[curchar].armor = index;
        setarmorslots();
    }
}
void MainWindow::on_combo_acc_currentIndexChanged(int index)
{
    if(!load){ff7.slot[s].chars[curchar].accessory = index;}
}
void MainWindow::on_combo_weapon_activated(int index)
{
    switch(curchar)
    {
        case 0:{ff7.slot[s].chars[curchar].weapon = index;break;}
        case 1:{ff7.slot[s].chars[curchar].weapon = index+32;break;}
        case 2:{ff7.slot[s].chars[curchar].weapon = index+16;break;}
        case 3:{ff7.slot[s].chars[curchar].weapon = index+62;break;}
        case 4:{ff7.slot[s].chars[curchar].weapon = index+48;break;}
        case 5:{ff7.slot[s].chars[curchar].weapon = index+87;break;}
        case 6:{ff7.slot[s].chars[curchar].weapon = index+101;break;}
        case 7:{ff7.slot[s].chars[curchar].weapon = index+114;break;}
        case 8:{ff7.slot[s].chars[curchar].weapon = index+73;break;}
    }
}
void MainWindow::on_combo_add_mat_slot_currentIndexChanged(int index)
{
    if(!load)
    {
        ff7.slot[s].chars[curchar].materias[mslotsel].id = Materias[index].id;
        guirefresh();
    }
    if(ff7.slot[s].chars[curchar].materias[mslotsel].id == 0x2C)
    {
        ui->eskill_group_2->setVisible(true);
        geteskills2(mslotsel);
        ui->sb_addap_slot->setEnabled(false);
    }
    else
    {
        ui->eskill_group_2->setVisible(false);
        ui->sb_addap_slot->setEnabled(true);
    }
}
void MainWindow::on_sb_addap_slot_valueChanged(int value)
{
    if(!load)
    {
        int a = (value & 0xff);
        int b = (value & 0xff00) >> 8;
        int c = (value & 0xff0000) >> 16;
        ff7.slot[s].chars[curchar].materias[mslotsel].ap[0] = a;
        ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] = b;
        ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] = c;
    }
}

void MainWindow::on_btn_mastermateria_slot_clicked()
{
    ui->sb_addap_slot->setValue(0xFFFFFF);
    mslotcalc();
}
void MainWindow::on_clearMateria_slot_clicked()
{
    ff7.slot[s].chars[curchar].materias[mslotsel].id = 0xFF;
    ui->sb_addap_slot->setValue(0xFFFFFF);
    guirefresh();
}
void MainWindow::mslotcalc()
{
    if(ff7.slot[s].chars[curchar].materias[mslotsel].id != 0x2C)
    {
        int aptemp;
        load =true;
        aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
        ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
        ui->sb_addap_slot->setValue(aptemp);
        load=false;
    }
    else
    {
        load=true;
        ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
        load=false;
        geteskills2(mslotsel);
    }
}
void MainWindow::on_w_m_s1_clicked()
{
    mslotsel =0;
    mslotcalc();
}
void MainWindow::on_w_m_s2_clicked()
{
    mslotsel =1;
    mslotcalc();
}
void MainWindow::on_w_m_s3_clicked()
{
    mslotsel =2;
    mslotcalc();
}
void MainWindow::on_w_m_s4_clicked()
{
    mslotsel =3;
    mslotcalc();
}
void MainWindow::on_w_m_s5_clicked()
{
    mslotsel =4;
    mslotcalc();
}
void MainWindow::on_w_m_s6_clicked()
{
    mslotsel =5;
    mslotcalc();
}
void MainWindow::on_w_m_s7_clicked()
{
    mslotsel =6;
    mslotcalc();
}
void MainWindow::on_w_m_s8_clicked()
{
    mslotsel =7;
    mslotcalc();
}

void MainWindow::on_a_m_s1_clicked()
{
    mslotsel =8;
    mslotcalc();
}
void MainWindow::on_a_m_s2_clicked()
{
    mslotsel =9;
    mslotcalc();
}
void MainWindow::on_a_m_s3_clicked()
{
    mslotsel =10;
    mslotcalc();
}
void MainWindow::on_a_m_s4_clicked()
{
    mslotsel =11;
    mslotcalc();
}
void MainWindow::on_a_m_s5_clicked()
{
    mslotsel =12;
    mslotcalc();
}
void MainWindow::on_a_m_s6_clicked()
{
    mslotsel =13;
    mslotcalc();
}
void MainWindow::on_a_m_s7_clicked()
{
    mslotsel =14;
    mslotcalc();
}
void MainWindow::on_a_m_s8_clicked()
{
    mslotsel = 15;
    mslotcalc();
}

void MainWindow::geteskills2(int row)
{
    load=true;
    quint32 temp = ff7.slot[s].chars[curchar].materias[row].ap[0] |(ff7.slot[s].chars[curchar].materias[row].ap[1] << 8) | (ff7.slot[s].chars[curchar].materias[row].ap[2] << 16);
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
{
    if(!load)
    {
        quint32 temp = ff7.slot[s].chars[curchar].materias[mslotsel].ap[0] |(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8) | (ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16);
        if(ui->list_eskill_2->currentItem()->checkState()){temp |= (1 << ui->list_eskill_2->currentRow());}
        else{temp &= ~(1<<ui->list_eskill_2->currentRow());}
        int a = (temp & 0xff);
        int b = (temp & 0xff00) >> 8;
        int c = (temp & 0xff0000) >> 16;
        ff7.slot[s].chars[curchar].materias[mslotsel].ap[0] = a;
        ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] = b;
        ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] = c;
        load=true;
        ui->sb_addap_slot->setValue(temp);
        load=false;
    }
}

// game options
void MainWindow::on_slide_ul_r_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[0][0] = value;}

    QString g_style = "QSlider#slide_ul_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ul_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ul_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ul_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ul_b->value()));
    g_style.append(",255));}");

    QString b_style =  "QSlider#slide_ul_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ul_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ul_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ul_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ul_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_ul_g->setStyleSheet(g_style);
    ui->slide_ul_b->setStyleSheet(b_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));
}
void MainWindow::on_slide_ul_g_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[0][1] = value;}

    QString r_style = "QSlider#slide_ul_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_b->value()));
    r_style.append(",255));}");

    QString b_style =  "QSlider#slide_ul_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ul_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ul_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ul_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ul_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_ul_r->setStyleSheet(r_style);
    ui->slide_ul_b->setStyleSheet(b_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));
}
void MainWindow::on_slide_ul_b_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[0][2] = value;}

    QString r_style = "QSlider#slide_ul_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ul_b->value()));
    r_style.append(",255));}");

    QString g_style = "QSlider#slide_ul_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ul_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ul_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ul_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ul_b->value()));
    g_style.append(",255));}");

    ui->slide_ul_r->setStyleSheet(r_style);
    ui->slide_ul_g->setStyleSheet(g_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));
}

void MainWindow::on_slide_ur_r_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[1][0] = value;}
    QString g_style = "QSlider#slide_ur_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ur_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ur_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ur_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ur_b->value()));
    g_style.append(",255));}");

    QString b_style =  "QSlider#slide_ur_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ur_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ur_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ur_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ur_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_ur_g->setStyleSheet(g_style);
    ui->slide_ur_b->setStyleSheet(b_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));

}
void MainWindow::on_slide_ur_g_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[1][1] = value;}
    QString r_style = "QSlider#slide_ur_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_b->value()));
    r_style.append(",255));}");

    QString b_style =  "QSlider#slide_ur_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ur_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ur_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ur_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ur_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_ur_r->setStyleSheet(r_style);
    ui->slide_ur_b->setStyleSheet(b_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));
}
void MainWindow::on_slide_ur_b_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[1][2] = value;}
    QString r_style = "QSlider#slide_ur_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ur_b->value()));
    r_style.append(",255));}");

    QString g_style = "QSlider#slide_ur_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ur_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ur_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ur_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ur_b->value()));
    g_style.append(",255));}");

    ui->slide_ur_r->setStyleSheet(r_style);
    ui->slide_ur_g->setStyleSheet(g_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));
}

void MainWindow::on_slide_ll_r_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[2][0] = value;}
    QString g_style = "QSlider#slide_ll_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ll_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ll_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ll_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ll_b->value()));
    g_style.append(",255));}");

    QString b_style =  "QSlider#slide_ll_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ll_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ll_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ll_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ll_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_ll_g->setStyleSheet(g_style);
    ui->slide_ll_b->setStyleSheet(b_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));

}
void MainWindow::on_slide_ll_g_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[2][1] = value;}
    QString r_style = "QSlider#slide_ll_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_b->value()));
    r_style.append(",255));}");

    QString b_style =  "QSlider#slide_ll_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_ll_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ll_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_ll_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_ll_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_ll_r->setStyleSheet(r_style);
    ui->slide_ll_b->setStyleSheet(b_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));
}
void MainWindow::on_slide_ll_b_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[2][2] = value;}
    QString r_style = "QSlider#slide_ll_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_ll_b->value()));
    r_style.append(",255));}");

    QString g_style = "QSlider#slide_ll_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_ll_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ll_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_ll_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_ll_b->value()));
    g_style.append(",255));}");

    ui->slide_ll_r->setStyleSheet(r_style);
    ui->slide_ll_g->setStyleSheet(g_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));
}

void MainWindow::on_slide_lr_r_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[3][0] = value;}
    QString g_style = "QSlider#slide_lr_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_lr_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_lr_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_lr_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_lr_b->value()));
    g_style.append(",255));}");

    QString b_style =  "QSlider#slide_lr_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_lr_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_lr_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_lr_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_lr_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_lr_g->setStyleSheet(g_style);
    ui->slide_lr_b->setStyleSheet(b_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));

}
void MainWindow::on_slide_lr_g_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[3][1] = value;}
    QString r_style = "QSlider#slide_lr_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_b->value()));
    r_style.append(",255));}");

    QString b_style =  "QSlider#slide_lr_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_lr_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_lr_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_lr_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_lr_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_lr_r->setStyleSheet(r_style);
    ui->slide_lr_b->setStyleSheet(b_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));
}
void MainWindow::on_slide_lr_b_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[3][2] = value;}
    QString r_style = "QSlider#slide_lr_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_lr_b->value()));
    r_style.append(",255));}");

    QString g_style = "QSlider#slide_lr_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_lr_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_lr_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_lr_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_lr_b->value()));
    g_style.append(",255));}");

    ui->slide_lr_r->setStyleSheet(r_style);
    ui->slide_lr_g->setStyleSheet(g_style);

    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, QColor(int(ff7.slot[s].colors[0][0]),int(ff7.slot[s].colors[0][1]),int(ff7.slot[s].colors[0][2])).rgb());
    image.setPixel(1, 0, QColor(int(ff7.slot[s].colors[1][0]),int(ff7.slot[s].colors[1][1]),int(ff7.slot[s].colors[1][2])).rgb());
    image.setPixel(0, 1, QColor(int(ff7.slot[s].colors[2][0]),int(ff7.slot[s].colors[2][1]),int(ff7.slot[s].colors[2][2])).rgb());
    image.setPixel(1, 1, QColor(int(ff7.slot[s].colors[3][0]),int(ff7.slot[s].colors[3][1]),int(ff7.slot[s].colors[3][2])).rgb());
    QImage gradient = image.scaled(ui->lbl_window_preview->width(),ui->lbl_window_preview->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->lbl_window_preview->setPixmap(QPixmap::fromImage(gradient));
}

/*end of color sliders*/

void MainWindow::on_slide_battlespeed_valueChanged(int value)
{
    ff7.slot[s].battlespeed = value;
}
void MainWindow::on_slide_battlemspeed_valueChanged(int value)
{
    ff7.slot[s].battlemspeed = value;
}
void MainWindow::on_slide_fieldmspeed_valueChanged(int value)
{
    ff7.slot[s].fieldmspeed = value;
}
void MainWindow::on_combo_control_currentIndexChanged()
{
    if(!load){setoptions_one();}
}
void MainWindow::on_combo_sound_currentIndexChanged()
{
    if(!load){setoptions_one();}
}
void MainWindow::on_combo_cursor_currentIndexChanged()
{
    if(!load){setoptions_one();}
}
void MainWindow::on_combo_atb_currentIndexChanged()
{
    if(!load){setoptions_one();}
}
void MainWindow::on_combo_camera_currentIndexChanged()
{
    if(!load){setoptions_two();}
}
void MainWindow::on_combo_magic_order_currentIndexChanged()
{
    if(!load){setoptions_two();}
}
void MainWindow::on_cb_battle_help_toggled()
{
    if(!load){setoptions_two();}
}
void MainWindow::setoptions_one()
{
    load = true;
    ff7.slot[s].options1 = 0;
    if(ui->combo_sound->currentIndex() == 1){ff7.slot[s].options1 += 0x01;}
    if(ui->combo_control->currentIndex() == 1){ff7.slot[s].options1 += 0x04;} //you have to also change mapped buttons for this to work 100%
    if(ui->combo_cursor->currentIndex() == 1){ff7.slot[s].options1 +=0x10;}
    if(ui->combo_atb->currentIndex() == 1){ff7.slot[s].options1 +=0x40;}
    if(ui->combo_atb->currentIndex() == 2){ff7.slot[s].options1 += 0x80;}
    load =false;
}
void MainWindow::setoptions_two()
{
    load = true;
    quint8 temp=0;
    if(ui->combo_camera->currentIndex()==1){temp += 1;}
    if(ui->combo_magic_order->currentIndex() == 1){temp += 0x04;}
    else if(ui->combo_magic_order->currentIndex()==2){temp += 0x08;}
    else if(ui->combo_magic_order->currentIndex()==3){temp += 0x0C;}
    else if(ui->combo_magic_order->currentIndex()==4){temp += 0x10;}
    else if(ui->combo_magic_order->currentIndex()==5){temp += 0x14;}
    if(ui->cb_battle_help->checkState() ==2){temp +=0x40;}
    ff7.slot[s].options2 =temp;
    load=false;
}

/*--------WIP Section PLACE ALL NEW FUNCTIONS HERE  untill tested them move to proper section-------*/

void MainWindow::on_cb_c2_born_toggled(bool checked) // not working correctly.
{
    if(checked== Qt::Checked){ff7.slot[s].chocoborn |= (1<<1);}
    else{ff7.slot[s].chocoborn |= (0<<1);}
}

void MainWindow::on_sb_mprogress_valueChanged()
{
    if(!load){ff7.slot[s].mprogress = ui->sb_mprogress->value();}
}

void MainWindow::on_sb_bm_progress1_valueChanged(int value)
{
if(!load){ff7.slot[s].bm_progress1 =value;}
}

void MainWindow::on_sb_bm_progress2_valueChanged(int value)
{
    if(!load){ff7.slot[s].bm_progress2 =value;}
}

void MainWindow::on_sb_bm_progress3_valueChanged(int value)
{
    if(!load){ff7.slot[s].bm_progress3 =value;}
}

void MainWindow::on_cb_replay_currentIndexChanged(int index)
{
    if(index == 1) // bombing mission
    {
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(1);
        ui->sb_bm_progress1->setValue(0);
        ui->sb_bm_progress2->setValue(0);
        ui->sb_bm_progress3->setValue(0);
        ui->cb_bombing_int->setChecked(1);
        ui->cb_midgartrain_1->setChecked(0);
        ui->cb_midgartrain_2->setChecked(0);
        ui->cb_midgartrain_3->setChecked(0);
        ui->cb_midgartrain_4->setChecked(0);
        ui->cb_midgartrain_5->setChecked(0);
        ui->cb_midgartrain_6->setChecked(0);
        ui->cb_midgartrain_7->setChecked(0);
        ui->cb_midgartrain_8->setChecked(0);
        ui->line_location->setText(tr("Platform"));
        ui->sb_map_id->setValue(1);
        ui->sb_loc_id->setValue(116);
        ui->sb_coordx->setValue(3655);
        ui->sb_coordy->setValue(27432);
        ui->sb_coordz->setValue(25);
        ui->label_replaynote->setText(tr("Replay the bombing mission from right after you get off the first train, game might crash after the mission right before jessie talks to you about midgar."));
    }

    else if (index ==2)// Flash back
    {
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(341);
        ui->sb_bm_progress1->setValue(120);
        ui->sb_bm_progress2->setValue(198);
        ui->sb_bm_progress3->setValue(3);
        ui->cb_bombing_int->setChecked(0);
        ui->line_location->setText(tr("Kalm Inn"));
        ui->sb_map_id->setValue(1);
        ui->sb_loc_id->setValue(332);
        ui->sb_coordx->setValue(267);
        ui->sb_coordy->setValue(65429);
        ui->sb_coordz->setValue(15);
// set up young cloud
        ff7.slot[s].chars[6].id=9;
        for(int i=0;i<12;i++){ff7.slot[s].chars[6].name[i] = ff7.slot[s].chars[0].name[i];}
        ff7.slot[s].chars[6].level =ff7.slot[s].chars[0].level;
        ff7.slot[s].chars[6].armor=ff7.slot[s].chars[0].armor;
        ff7.slot[s].chars[6].accessory=ff7.slot[s].chars[0].accessory;
        ff7.slot[s].chars[6].weapon= ff7.slot[s].chars[0].weapon;
        ff7.slot[s].chars[6].baseHP=ff7.slot[s].chars[0].baseHP;
        ff7.slot[s].chars[6].baseMP=ff7.slot[s].chars[0].baseMP;
        ff7.slot[s].chars[6].exp=ff7.slot[s].chars[0].exp;
        ff7.slot[s].chars[6].expNext=ff7.slot[s].chars[0].expNext;
        ff7.slot[s].chars[6].curHP=ff7.slot[s].chars[0].curHP;
        ff7.slot[s].chars[6].maxHP=ff7.slot[s].chars[0].maxHP;
        ff7.slot[s].chars[6].curMP=ff7.slot[s].chars[0].curMP;
        ff7.slot[s].chars[6].maxMP=ff7.slot[s].chars[0].maxMP;
        ff7.slot[s].chars[6].dexterity=ff7.slot[s].chars[0].dexterity;
        ff7.slot[s].chars[6].dexterity_bonus=ff7.slot[s].chars[0].dexterity_bonus;
        ff7.slot[s].chars[6].strength=ff7.slot[s].chars[0].strength;
        ff7.slot[s].chars[6].strength_bonus=ff7.slot[s].chars[0].strength_bonus;
        ff7.slot[s].chars[6].magic=ff7.slot[s].chars[0].magic;
        ff7.slot[s].chars[6].magic_bonus=ff7.slot[s].chars[0].magic_bonus;
        ff7.slot[s].chars[6].spirit=ff7.slot[s].chars[0].spirit;
        ff7.slot[s].chars[6].spirit_bonus=ff7.slot[s].chars[0].spirit_bonus;
        ff7.slot[s].chars[6].vitality= ff7.slot[s].chars[0].vitality;
        ff7.slot[s].chars[6].vitality_bonus= ff7.slot[s].chars[0].vitality_bonus;
        ff7.slot[s].chars[6].luck= ff7.slot[s].chars[0].luck;
        ff7.slot[s].chars[6].luck_bonus= ff7.slot[s].chars[0].luck_bonus;
        ff7.slot[s].chars[6].flags[0]= ff7.slot[s].chars[0].flags[0];
        ff7.slot[s].chars[6].flags[1]= ff7.slot[s].chars[0].flags[1];
        ff7.slot[s].chars[6].flags[2]= ff7.slot[s].chars[0].flags[2];
        ff7.slot[s].chars[6].kills=ff7.slot[s].chars[0].kills;
        ff7.slot[s].chars[6].limitbar= ff7.slot[s].chars[0].limitbar;
        ff7.slot[s].chars[6].limitlevel= ff7.slot[s].chars[0].limitlevel;
        ff7.slot[s].chars[6].limits= ff7.slot[s].chars[0].limits;
        for (int i=0;i<16;i++)
        {
            ff7.slot[s].chars[6].materias[i].id = ff7.slot[s].chars[0].materias[i].id;
            for (int j=0;j<3;j++){ff7.slot[s].chars[6].materias[i].ap[j]=ff7.slot[s].chars[0].materias[i].ap[j];}
        }
        ff7.slot[s].chars[6].timesused1 = ff7.slot[s].chars[0].timesused1;
        ff7.slot[s].chars[6].timesused2 = ff7.slot[s].chars[0].timesused2;
        ff7.slot[s].chars[6].timesused3 = ff7.slot[s].chars[0].timesused3;
        for(int i=0;i<4;i++){ff7.slot[s].chars[6].z_4[i] = ff7.slot[s].chars[0].z_4[i];}
        //set up Sephiroth
        ff7.slot[s].chars[7].id=10;
        ff7.slot[s].chars[7].name[0] = chFF7['S'];
        ff7.slot[s].chars[7].name[1] = chFF7['e'];
        ff7.slot[s].chars[7].name[2] = chFF7['p'];
        ff7.slot[s].chars[7].name[3] = chFF7['h'];
        ff7.slot[s].chars[7].name[4] = chFF7['i'];
        ff7.slot[s].chars[7].name[5] = chFF7['r'];
        ff7.slot[s].chars[7].name[6] = chFF7['o'];
        ff7.slot[s].chars[7].name[7] = chFF7['t'];
        ff7.slot[s].chars[7].name[8] = chFF7['h'];
        for (int i=9; i<12;i++){ff7.slot[s].chars[7].name[i] = 0xFF;}
        ui->label_replaynote->setText(tr("Setting This Will Copy Cloud as is to young cloud (caitsith's slot). sephiroth's stats will come directly from vincent, if you wish to edit cloud or vincent after selecting this replay then change the box to the first(blank) entry and then when you have set those chars as you wish reselect this replay from the combobox."));
    }


    else if(index == 3) // The Date Scene
    {
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(583);
        ui->sb_bm_progress1->setValue(120);
        ui->sb_bm_progress2->setValue(198);
        ui->sb_bm_progress3->setValue(3);
        ui->cb_bombing_int->setChecked(0);
        ui->line_location->setText(tr("Ropeway Station"));
        ui->sb_map_id->setValue(1);
        ui->sb_loc_id->setValue(496);
        ui->sb_coordx->setValue(64767);
        ui->sb_coordy->setValue(95);
        ui->sb_coordz->setValue(26);
        ui->label_replaynote->setText(tr("Replay the Date Scene, Your Location will be set To Ropeway Station, Talk To The Guy By The Tram To Start The Event, If Your Looking for a special Date be sure to set your love points too."));
    }

    else if (index == 4)//Aerith Death
    {
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(664);
        ui->sb_bm_progress1->setValue(120);
        ui->sb_bm_progress2->setValue(198);
        ui->sb_bm_progress3->setValue(3);
        ui->cb_bombing_int->setChecked(0);
        ui->line_location->setText(tr("Forgotten City"));
        ui->sb_map_id->setValue(1);
        ui->sb_loc_id->setValue(646);
        ui->sb_coordx->setValue(641);
        ui->sb_coordy->setValue(793);
        ui->sb_coordz->setValue(243);
        ui->list_chars_unlocked->item(3)->setCheckState(Qt::Unchecked);
        ui->list_phs_chars->item(3)->setCheckState(Qt::Unchecked);
        ui->label_replaynote->setText(tr("Replay the death of Aerith.This option Will remove Aerith from your PHS"));
    }

    else {ui->label_replaynote->setText(tr("         INFO ON CURRENTLY SELECTED REPLAY MISSION"));}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FUNCTIONS FOR TESTING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_btn_remove_all_items_clicked() //used for testing
{
    for(int i=0;i<320;i++)
    {
        ff7.slot[s].items[i].id=0xFF;
        ff7.slot[s].items[i].qty=0xFF;
    }
    guirefresh();
}

void MainWindow::on_btn_remove_all_materia_clicked()
{
    for (int i=0;i<200;i++)
    {
        ff7.slot[s].materias[i].id =0xFF;
        ff7.slot[s].materias[i].ap[0]=0xFF;
        ff7.slot[s].materias[i].ap[1]=0xFF;
        ff7.slot[s].materias[i].ap[2]=0xFF;
    }
    guirefresh();
}

void MainWindow::on_btn_remove_all_stolen_clicked()
{
    for(int i=0;i<48;i++)
    {
        ff7.slot[s].stolen[i].id =0xFF;
        ff7.slot[s].stolen[i].ap[0]=0xFF;
        ff7.slot[s].stolen[i].ap[1]=0xFF;
        ff7.slot[s].stolen[i].ap[2]=0xFF;
    }
    guirefresh();
}

void MainWindow::testdata_refresh()
{
    load=true;

    ui->sb_timer_time_hour->setValue(ff7.slot[s].timer[0]);
    ui->sb_timer_time_min->setValue(ff7.slot[s].timer[1]);
    ui->sb_timer_time_sec->setValue(ff7.slot[s].timer[2]);

    ui->sb_b_love_aeris->setValue(ff7.slot[s].b_love.aeris);
    ui->sb_b_love_tifa->setValue(ff7.slot[s].b_love.tifa);
    ui->sb_b_love_yuffie->setValue(ff7.slot[s].b_love.yuffie);
    ui->sb_b_love_barret->setValue(ff7.slot[s].b_love.barret);
    ui->sb_u_weapon_hp->setValue(ff7.slot[s].u_weapon_hp[0] |(ff7.slot[s].u_weapon_hp[1] << 8) | (ff7.slot[s].u_weapon_hp[2] << 16));

    if(ff7.slot[s].tut_sub == 0x2F){ui->cb_tut_sub->setCheckState(Qt::Checked);}
    else if(ff7.slot[s].tut_sub ==0x2B){ui->cb_tut_sub->setCheckState(Qt::PartiallyChecked);}
    else{ui->cb_tut_sub->setCheckState(Qt::Unchecked);}
    ui->lcdNumber_6->display(ff7.slot[s].tut_sub);


    if(ff7.slot[s].tut_save == 0x3A){ui->cb_tut_worldsave->setCheckState(Qt::Checked);}
    else if(ff7.slot[s].tut_save ==0x32){ui->cb_tut_worldsave->setCheckState(Qt::PartiallyChecked);}
    else{ui->cb_tut_worldsave->setCheckState(Qt::Unchecked);}
    ui->lcdNumber_7->display(ff7.slot[s].tut_save);

    if(ff7.slot[s].reg_vinny == 0xFF){ui->cb_reg_vinny->setChecked(Qt::Checked);}
    else if(ff7.slot[s].reg_vinny ==0xFB){ui->cb_reg_vinny->setChecked(Qt::Unchecked);}
    ui->lcdNumber_8->display(ff7.slot[s].reg_vinny);

    if(ff7.slot[s].reg_yuffie == 0x6F){ui->cb_reg_yuffie->setChecked(Qt::Checked);}
    else if(ff7.slot[s].reg_yuffie==0x6E){ui->cb_reg_yuffie->setChecked(Qt::Unchecked);}
    ui->lcdNumber_9->display(ff7.slot[s].reg_yuffie);

    if((ff7.slot[s].itemsmask_1)& (1<<0)){ui->cb_itemmask1_1->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_1->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].itemsmask_1)& (1<<1)){ui->cb_itemmask1_2->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_2->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].itemsmask_1)& (1<<2)){ui->cb_itemmask1_3->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_3->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].itemsmask_1)& (1<<3)){ui->cb_itemmask1_4->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_4->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].itemsmask_1)& (1<<4)){ui->cb_itemmask1_5->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_5->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].itemsmask_1)& (1<<5)){ui->cb_itemmask1_6->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_6->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].itemsmask_1)& (1<<6)){ui->cb_itemmask1_7->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_7->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].itemsmask_1)& (1<<7)){ui->cb_itemmask1_8->setChecked(Qt::Checked);}
    else{ui->cb_itemmask1_8->setChecked(Qt::Unchecked);}
    ui->lcd_itemmask_1->display(ff7.slot[s].itemsmask_1);


    if((ff7.slot[s].midgartrainflags)& (1<<0)){ui->cb_midgartrain_1->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_1->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].midgartrainflags)& (1<<1)){ui->cb_midgartrain_2->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_2->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].midgartrainflags)& (1<<2)){ui->cb_midgartrain_3->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_3->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].midgartrainflags)& (1<<3)){ui->cb_midgartrain_4->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_4->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].midgartrainflags)& (1<<4)){ui->cb_midgartrain_5->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_5->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].midgartrainflags)& (1<<5)){ui->cb_midgartrain_6->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_6->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].midgartrainflags)& (1<<6)){ui->cb_midgartrain_7->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_7->setChecked(Qt::Unchecked);}
    if((ff7.slot[s].midgartrainflags)& (1<<7)){ui->cb_midgartrain_8->setChecked(Qt::Checked);}
    else{ui->cb_midgartrain_8->setChecked(Qt::Unchecked);}
    ui->lcd_midgartrain->display(ff7.slot[s].midgartrainflags);

    load=false;}//end of testdata_refresh()

void MainWindow::on_list_menu_visible_itemChanged()
{
    if(!load)
    {
        int j=ui->list_menu_visible->currentRow();
        if(ui->list_menu_visible->currentItem()->checkState() ==Qt::Checked){ff7.slot[s].menu_visible |= (1<<j);}
        else{ff7.slot[s].menu_visible &= ~(1<<j);}
    }
}

void MainWindow::on_list_menu_locked_itemChanged()
{
    if(!load)
    {
        int j=ui->list_menu_locked->currentRow();
        if(ui->list_menu_locked->currentItem()->checkState() ==Qt::Checked){ff7.slot[s].menu_locked |= (1<<j);}
        else{ff7.slot[s].menu_locked &= ~(1<<j);}
    }
}

void MainWindow::on_sb_b_love_aeris_valueChanged(int value)
{
    if(!load){ff7.slot[s].b_love.aeris = value;}
}

void MainWindow::on_sb_b_love_tifa_valueChanged(int value)
{
    if(!load){ff7.slot[s].b_love.tifa = value;}
}

void MainWindow::on_sb_b_love_yuffie_valueChanged(int value)
{
    if(!load){ff7.slot[s].b_love.yuffie = value;}
}

void MainWindow::on_sb_b_love_barret_valueChanged(int value)
{
    if(!load){ff7.slot[s].b_love.barret = value;}
}

void MainWindow::on_sb_coster_1_valueChanged(int value)
{
    if(!load){ff7.slot[s].coster_1=value;}
}
void MainWindow::on_sb_coster_2_valueChanged(int value)
{
    if(!load){ff7.slot[s].coster_2 = value;}
}
void MainWindow::on_sb_coster_3_valueChanged(int value)
{
    if(!load){ff7.slot[s].coster_3 = value;}
}

void MainWindow::on_sb_u_weapon_hp_valueChanged(int value)
{
    if(!load)
    {
        load=true;
        int a = (value & 0xff);
        int b = (value & 0xff00) >> 8;
        int c = (value & 0xff0000) >> 16;
        ff7.slot[s].u_weapon_hp[0] = a;
        ff7.slot[s].u_weapon_hp[1] = b;
        ff7.slot[s].u_weapon_hp[2] = c;
        load=false;
    }
}

void MainWindow::on_cb_reg_vinny_toggled(bool checked)
{
    if(!load)
    {
        if (checked){ff7.slot[s].reg_vinny =0xFF;}
        else{ff7.slot[s].reg_vinny =0xFB;}
        testdata_refresh();
    }
}

void MainWindow::on_cb_itemmask1_1_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].itemsmask_1 |= (1<<0);}
        else{ff7.slot[s].itemsmask_1 &= ~(1<<0);}
        ui->lcd_itemmask_1->display(ff7.slot[s].itemsmask_1);
    }
}
void MainWindow::on_cb_itemmask1_2_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].itemsmask_1 |= (1<<1);}
        else{ff7.slot[s].itemsmask_1 &= ~(1<<1);}
        ui->lcd_itemmask_1->display(ff7.slot[s].itemsmask_1);
    }
}

void MainWindow::on_cb_itemmask1_3_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].itemsmask_1 |= (1<<2);}
        else{ff7.slot[s].itemsmask_1 &= ~(1<<2);}
        ui->lcd_itemmask_1->display(ff7.slot[s].itemsmask_1);
    }
}

void MainWindow::on_cb_itemmask1_4_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].itemsmask_1 |= (1<<3);}
        else{ff7.slot[s].itemsmask_1 &= ~(1<<3);}
        ui->lcd_itemmask_1->display(ff7.slot[s].itemsmask_1);
    }
}

void MainWindow::on_cb_itemmask1_5_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].itemsmask_1 |= (1<<4);}
        else{ff7.slot[s].itemsmask_1 &= ~(1<<4);}
        ui->lcd_itemmask_1->display(ff7.slot[s].itemsmask_1);
    }
}

void MainWindow::on_cb_itemmask1_6_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].itemsmask_1 |= (1<<5);}
        else{ff7.slot[s].itemsmask_1 &= ~(1<<5);}
        ui->lcd_itemmask_1->display(ff7.slot[s].itemsmask_1);
    }
}

void MainWindow::on_cb_itemmask1_7_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].itemsmask_1 |= (1<<6);}
        else{ff7.slot[s].itemsmask_1 &= ~(1<<6);}
        ui->lcd_itemmask_1->display(ff7.slot[s].itemsmask_1);
    }
}

void MainWindow::on_cb_itemmask1_8_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].itemsmask_1 |= (1<<7);}
        else{ff7.slot[s].itemsmask_1 &= ~(1<<7);}
        ui->lcd_itemmask_1->display(ff7.slot[s].itemsmask_1);
    }
}

void MainWindow::on_cb_materiacave_1_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].materiacaves |= (1<<0);}
        else{ff7.slot[s].materiacaves &= ~(1<<0);}
    }
}
void MainWindow::on_cb_materiacave_2_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].materiacaves |= (1<<1);}
        else{ff7.slot[s].materiacaves &= ~(1<<1);}
    }
}
void MainWindow::on_cb_materiacave_3_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].materiacaves |= (1<<2);}
        else{ff7.slot[s].materiacaves &= ~(1<<2);}
    }
}
void MainWindow::on_cb_materiacave_4_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].materiacaves |= (1<<3);}
        else{ff7.slot[s].materiacaves &= ~(1<<3);}
    }
}

void MainWindow::on_cb_reg_yuffie_toggled(bool checked)
{
    if(!load)
    {
        if (checked){ff7.slot[s].reg_yuffie =0x6F;}
        else{ff7.slot[s].reg_yuffie =0x6E;}
        testdata_refresh();
    }
}

void MainWindow::on_cb_yuffieforest_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].yuffieforest |= (1<<0);}
        else{ff7.slot[s].yuffieforest &= ~(1<<0);}
    }
}

void MainWindow::on_cb_midgartrain_1_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].midgartrainflags |= (1<<0);}
        else{ff7.slot[s].midgartrainflags &= ~(1<<0);}
        ui->lcd_midgartrain->display(ff7.slot[s].midgartrainflags);
    }
}

void MainWindow::on_cb_midgartrain_2_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].midgartrainflags |= (1<<1);}
        else{ff7.slot[s].midgartrainflags &= ~(1<<1);}
        ui->lcd_midgartrain->display(ff7.slot[s].midgartrainflags);
    }
}

void MainWindow::on_cb_midgartrain_3_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].midgartrainflags |= (1<<2);}
        else{ff7.slot[s].midgartrainflags &= ~(1<<2);}
        ui->lcd_midgartrain->display(ff7.slot[s].midgartrainflags);
    }
}

void MainWindow::on_cb_midgartrain_4_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].midgartrainflags |= (1<<3);}
        else{ff7.slot[s].midgartrainflags &= ~(1<<3);}
        ui->lcd_midgartrain->display(ff7.slot[s].midgartrainflags);
    }
}

void MainWindow::on_cb_midgartrain_5_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].midgartrainflags |= (1<<4);}
        else{ff7.slot[s].midgartrainflags &= ~(1<<4);}
        ui->lcd_midgartrain->display(ff7.slot[s].midgartrainflags);
    }
}

void MainWindow::on_cb_midgartrain_6_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].midgartrainflags |= (1<<5);}
        else{ff7.slot[s].midgartrainflags &= ~(1<<5);}
        ui->lcd_midgartrain->display(ff7.slot[s].midgartrainflags);
    }
}

void MainWindow::on_cb_midgartrain_7_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].midgartrainflags |= (1<<6);}
        else{ff7.slot[s].midgartrainflags &= ~(1<<6);}
        ui->lcd_midgartrain->display(ff7.slot[s].midgartrainflags);
    }
}

void MainWindow::on_cb_midgartrain_8_toggled(bool checked)
{
    if(!load)
    {
        if(checked){ff7.slot[s].midgartrainflags |= (1<<7);}
        else{ff7.slot[s].midgartrainflags &= ~(1<<7);}
        ui->lcd_midgartrain->display(ff7.slot[s].midgartrainflags);
    }
}

void MainWindow::on_sb_timer_time_hour_valueChanged(int value)
{
    if(!load){ff7.slot[s].timer[0] = value;}
}

void MainWindow::on_sb_timer_time_min_valueChanged(int value)
{
    if(!load){ff7.slot[s].timer[1] = value;}
}

void MainWindow::on_sb_timer_time_sec_valueChanged(int value)
{
    if(!load){ff7.slot[s].timer[2] = value;}
}

void MainWindow::on_cb_tut_sub_stateChanged(int value)
{
    if(!load)
    {
        if (value == 0){ff7.slot[s].tut_sub =0x00;}
        else if(value ==1){ff7.slot[s].tut_sub =0x2B;}
        else if(value ==2){ff7.slot[s].tut_sub=0x2F;}
        testdata_refresh();
    }
}

void MainWindow::on_cb_tut_worldsave_stateChanged(int value)
{
    if(!load)
    {
        if (value == 0){ff7.slot[s].tut_save =0x00;}
        else if(value ==1){ff7.slot[s].tut_save =0x32;}
        else if(value ==2){ff7.slot[s].tut_save=0x3A;}
        testdata_refresh();
    }
}

void MainWindow::on_cb_bombing_int_stateChanged(int checked)
{
    if(checked == Qt::Checked){ff7.slot[s].intbombing =0x14;}
    else{ff7.slot[s].intbombing =0x56;}
}