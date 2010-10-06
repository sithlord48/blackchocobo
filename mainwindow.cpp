/****************************************************************************/
//    copyright 2010 Chris Rizzitello <sithlord48@gmail.com>                //
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
#include <QSettings>
/*~~~~~GLOBALS~~~~~~*/
bool load =false; //used for checking if data is initial load (to block some overrights when gui objects change)
extern FF7 ff7; // our save file struct
extern int s; //keeps track of our slot globally
FF7SLOT bufferslot; // a buffer slot to keep copied slots in
char chFF7[256];  // char arrary for converting to ff7 chars , so far not used.

int curchar; //keeps track of current character displayed
int mslotsel = 0; //keeps track of materia slot on char selected

QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"blackchocobo","settings",0);

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
    for (int i=256;i<288;i++){ui->combo_armor->addItem(QIcon(Items[i].image),Items[i].name);}// set up the combo boxes
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
    ui->btn_remove_all_items->setVisible(false);
    ui->btn_remove_all_materia->setVisible(false);
    ui->btn_remove_all_stolen->setVisible(false);
    ui->lbl_z_4_0->setVisible(false);
    ui->lbl_z_4_1->setVisible(false);
    ui->lbl_z_4_2->setVisible(false);
    ui->lbl_z_4_3->setVisible(false);
    ui->lcd_z_4_0->setVisible(false);
    ui->lcd_z_4_1->setVisible(false);
    ui->lcd_z_4_2->setVisible(false);
    ui->lcd_z_4_3->setVisible(false);
    load=false;

    // load settings
    if(settings.value("show_test").toBool())
    {
        ui->action_show_test_data->setChecked(1);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
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
    tr("Known FF7 Save Types (*.ff7 *-S* *.mcr *.mcd *.psv *.vmp);;PC FF7 SaveGame (*.ff7);;PSX FF7 SaveGame (*-S*);;MC SaveGame (*.mcr *.mcd);;PSV SaveGame (*.psv);;PSP SaveGame (*.vmp)"));

    if (!fileName.isEmpty())
        loadFileFull(fileName);
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
        //ff7.SG_TYPE          = "UNKNOWN";
        //ff7.savetype         = 0;
        QMessageBox::warning(this, tr("Unknown File"),
        tr("File: %1 \nisn't a FF7 SaveGame.")
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
    if (ff7.savetype == 1 || ff7.savetype == 3 || ff7.savetype ==5)
    {
        SlotSelect slotselect;
        slotselect.exec();
    }
    else
    {
        s=0;
        for(int i=1;i<14;i++){clearslot(i);}
    }
    guirefresh();
}

void MainWindow::on_actionFrom_PSX_Slot_activated()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Select Final Fantasy 7 PSX Save"),(""),tr("PSX FF7 SaveGame (*-S*)"));
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
    }//Parse slot data....
    guirefresh();
}

void MainWindow::on_actionFrom_PSV_Slot_activated()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Select Final Fantasy 7 PSV Save"),(""),tr("PSX FF7 SaveGame (*.psv)"));
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
        }//Parse slot data....
    guirefresh();
}

void MainWindow::on_actionCopy_Slot_activated()
{
    memcpy(&bufferslot,&ff7.slot[s],0x10f4);
}

void MainWindow::clearslot(int rmslot)
{
    QByteArray temp;
    temp.fill(0x00,0x10f4);
    memcpy(&ff7.slot[rmslot],temp,0x10f4);
}

void MainWindow::on_actionPaste_Slot_activated()
{
    memcpy(&ff7.slot[s],&bufferslot,0x10f4);
    guirefresh();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~New Save Section - Sithlord48 ~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionSave_File_activated()
{
// check for the type of save loaded and set the output type so we don't save the wrong type, all conversion opperations should be done via an Export function.
    if(ff7.savetype==1)
    {
        QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 PC SaveGame"), settings.value("save_pc_path").toString(),
        tr("FF7 PC SaveGame(*.ff7)"));
        if (!fileName.isEmpty())
            saveFileFull(fileName);
    }
    else if(ff7.savetype==2)
    {
        QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 PSX SaveGame"), "",
        tr("FF7 PSX SaveGame(*-S*)"));//this should really be *-S*
        if (!fileName.isEmpty())
            saveFileFull(fileName);
    }
    else if(ff7.savetype==3)
    {
        QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Final Fantasy 7 MC SaveGame"), settings.value("save_emu_path").toString(),
        tr("FF7 MC SaveGame(*.mcr *.mcd)"));
        if (!fileName.isEmpty())
            saveFileFull(fileName);
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
            saveFileFull(fileName);
    }
    else {QMessageBox::warning(this, tr("Black Chocobo"),tr("Cannot save This Type of File"));}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ NEW SHORT SAVE - SITHLORD48 - V. 1.4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::saveFileFull(const QString &fileName)
{
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
/*~~~~~~~~~~~~~~~~~~~~~~END NEW SHORT SAVE -SITHLORD48- V.1.4~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_actionExport_PC_Save_activated()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 SaveGame"),  settings.value("export_pc").toString() ,
    tr("FF7 SaveGame(*.ff7)")); // Only Allow PC save Since we are going to make one

    if(ff7.SG_TYPE !="PC")
    {
        ui->combo_control->setCurrentIndex(0); // if not pc then chance of breaking controls.
    }
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

/*~~~~~~~~~~~~~~~~~~~~~~~~ NEW SHORT SAVE - SITHLORD48 - V. 1.4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    FILE *pfile; // this section is starting to work correctly!
    pfile = fopen(fileName.toAscii(),"wb");
    fwrite(ff7.file_headerp,ff7.SG_HEADER,1,pfile);
    for(int si=0;si<15;si++)
    {
        fwrite(ff7.hf[si].sl_header,ff7.SG_SLOT_HEADER,1,pfile);
        fwrite(&ff7.slot[si],ff7.SG_DATA_SIZE,1,pfile);
        fwrite(ff7.hf[si].sl_footer,ff7.SG_SLOT_FOOTER,1,pfile);
    }
    fwrite(ff7.file_footerp,ff7.SG_FOOTER,1,pfile);
    fclose(pfile);
    fix_sum(fileName);
    /*~~~~~~~~~~~~~~~~~~~~~~END NEW SHORT SAVE -SITHLORD48- V.1.4~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}

void MainWindow::on_actionExport_PSX_activated()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Final Fantasy 7 SaveGame"), "BASCUS-94163FF7-",
    tr("BASCUS-94163FF7-S01(*-S01);;BASCUS-94163FF7-S02(*-S02);;BASCUS-94163FF7-S03(*-S03);;BASCUS-94163FF7-S04(*-S04);;BASCUS-94163FF7-S05(*-S05);;BASCUS-94163FF7-S06(*-S06);;BASCUS-94163FF7-S07(*-S07);;BASCUS-94163FF7-S08(*-S08);;BASCUS-94163FF7-S09(*-S09);;BASCUS-94163FF7-S10(*-S10);;BASCUS-94163FF7-S11(*-S11);;BASCUS-94163FF7-S12(*-S12);;BASCUS-94163FF7-S13(*-S13);;BASCUS-94163FF7-S14(*-S14);;BASCUS-94163FF7-S15(*-S15)")); // Only Allow PSX save slots Since we are going to force its creation.

    if(ff7.SG_TYPE != "PSX")
    {
        ui->combo_control->setCurrentIndex(0);
    }
    ff7.SG_SIZE          = FF7_PSX_SAVE_GAME_SIZE;
    ff7.SG_HEADER        = FF7_PSX_SAVE_GAME_HEADER;
    ff7.SG_FOOTER        = FF7_PSX_SAVE_GAME_FOOTER;
    ff7.SG_DATA_SIZE     = FF7_PSX_SAVE_GAME_DATA_SIZE;
    ff7.SG_SLOT_HEADER   = FF7_PSX_SAVE_GAME_SLOT_HEADER;
    ff7.SG_SLOT_FOOTER   = FF7_PSX_SAVE_GAME_SLOT_FOOTER;
    ff7.SG_SLOT_SIZE     = FF7_PSX_SAVE_GAME_SLOT_SIZE;
    ff7.SG_SLOT_NUMBER   = FF7_PSX_SAVE_GAME_SLOT_NUMBER;
    ff7.SG_TYPE          = "PSX";
    ff7.file_headerp     = ff7.file_header_psx;           //pointer to pc file header
    ff7.file_footerp     = ff7.file_footer_psx;           //pointer to pc file footer

/*~~~~~~~~~~~~~~~~~~~~~~~~ NEW SHORT SAVE - SITHLORD48 - V. 1.4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    FILE *pfile; // this section is starting to work correctly!
    pfile = fopen(fileName.toAscii(),"wb");

    if(fileName.endsWith("S01")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S01,0x100,1,pfile);}
    else if(fileName.endsWith("S02")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S02,0x100,1,pfile);}
    else if(fileName.endsWith("S03")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S03,0x100,1,pfile);}
    else if(fileName.endsWith("S04")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S04,0x100,1,pfile);}
    else if(fileName.endsWith("S05")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S05,0x100,1,pfile);}
    else if(fileName.endsWith("S06")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S06,0x100,1,pfile);}
    else if(fileName.endsWith("S07")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S07,0x100,1,pfile);}
    else if(fileName.endsWith("S08")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S08,0x100,1,pfile);}
    else if(fileName.endsWith("S09")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S09,0x100,1,pfile);}
    else if(fileName.endsWith("S10")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S10,0x100,1,pfile);}
    else if(fileName.endsWith("S11")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S11,0x100,1,pfile);}
    else if(fileName.endsWith("S12")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S12,0x100,1,pfile);}
    else if(fileName.endsWith("S13")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S13,0x100,1,pfile);}
    else if(fileName.endsWith("S14")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S14,0x100,1,pfile);}
    else if(fileName.endsWith("S15")){fwrite(&PSX_SAVE_GAME_FILE_HEADER_S15,0x100,1,pfile);}
    else{QMessageBox::information(this,"Bad Psx Save Name", "Can't Decide On What Header to Write, Please Add the sufix SXX (where x= 01-15, with leading 0 if < 10) US Header for that slot number will be written to the save"   );return;}

    QByteArray temp;
    temp.fill(0x00,0x100);
    fwrite(temp,256,1,pfile); // 256  bytes of 0x00 (rest of psx header data)

    fwrite(&ff7.slot[s],ff7.SG_DATA_SIZE,1,pfile);
    fwrite(ff7.hf[s].sl_footer,ff7.SG_SLOT_FOOTER,1,pfile);
    fwrite(ff7.file_footerp,ff7.SG_FOOTER,1,pfile);
    fclose(pfile);
    fix_sum(fileName);
/*~~~~~~~~~~~~~~~~~~~~~~END NEW SHORT SAVE -SITHLORD48- V.1.4~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START CHECKSUM VEGETA~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END CHECKSUM VEGETA~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~END LOAD/SAVE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//MENU ACTIONS

void MainWindow::on_actionSlot_01_activated()
{
    s=0;
    guirefresh();
}
void MainWindow::on_actionSlot_02_activated()
{
    s=1;
    guirefresh();
}
void MainWindow::on_actionSlot_03_activated()
{
    s=2;
    guirefresh();
}
void MainWindow::on_actionSlot_04_activated()
{
    s=3;
    guirefresh();
}
void MainWindow::on_actionSlot_05_activated()
{
    s=4;
    guirefresh();
}
void MainWindow::on_actionSlot_06_activated()
{
    s=5;
    guirefresh();
}
void MainWindow::on_actionSlot_07_activated()
{
    s=6;
    guirefresh();
}
void MainWindow::on_actionSlot_08_activated()
{
    s=7;
    guirefresh();
}
void MainWindow::on_actionSlot_09_activated()
{
    s=8;
    guirefresh();
}
void MainWindow::on_actionSlot_10_activated()
{
    s=9;
    guirefresh();
}
void MainWindow::on_actionSlot_11_activated()
{
    s=10;
    guirefresh();
}
void MainWindow::on_actionSlot_12_activated()
{
    s=11;
    guirefresh();
}
void MainWindow::on_actionSlot_13_activated()
{
    s=12;
    guirefresh();
}
void MainWindow::on_actionSlot_14_activated()
{
    s=13;
    guirefresh();
}
void MainWindow::on_actionSlot_15_activated()
{
    s=14;
    guirefresh();
}
void MainWindow::on_actionShow_Selection_Dialog_activated()
{
    SlotSelect slotselect;
    slotselect.exec();
}
void MainWindow::on_actionClear_Slot_activated()
{
    clearslot(s);
    guirefresh();
}
void MainWindow::on_actionPrevious_Slot_activated()
{
    if (s > 0) {s--; guirefresh();}
}
void MainWindow::on_actionNext_Slot_activated()
{
    if (s<14){s++; guirefresh();}
}
void MainWindow::on_actionAbout_activated()
{
   about adialog;
   adialog.exec();
}
void MainWindow::on_actionEdit_Paths_triggered()
{
    Options odialog;
    odialog.exec();
}
void MainWindow::on_actionAbout_Qt_activated()
{
    qApp->aboutQt();
}

//gui functions

void MainWindow::charupdate(void)
{   //clear the text incase there is something there
    //mslotsel=0;
    ui->cb_id->setText("");
    ui->cb_id->setChecked(false);
    ui->cb_id->setVisible(false);
    if(curchar== 6)
    {

        ui->cb_id->setText("Young Cloud");
        ui->cb_id->setVisible(true);
        if (ff7.slot[s].chars[curchar].id == 9){ui->cb_id->setChecked(true);}
        else{ui->cb_id->setChecked(false);}
    }
    if(curchar==7)
    {
        ui->cb_id->setText("Sephiroth");
        ui->cb_id->setVisible(true);
        if (ff7.slot[s].chars[curchar].id == 10){ui->cb_id->setChecked(true);}
        else{ui->cb_id->setChecked(false);}
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
    ui->lcd_z_4_0->display(ff7.slot[s].chars[curchar].z_4[0]);
    ui->lcd_z_4_1->display(ff7.slot[s].chars[curchar].z_4[1]);
    ui->lcd_z_4_2->display(ff7.slot[s].chars[curchar].z_4[2]);
    ui->lcd_z_4_3->display(ff7.slot[s].chars[curchar].z_4[3]);

}
void MainWindow::setarmorslots(void)
{
    ui->a_m_l1->setHidden(1);
    ui->a_m_l2->setHidden(1);
    ui->a_m_l3->setHidden(1);
    ui->a_m_l4->setHidden(1);
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
    case 1:{ui->a_m_l1->setHidden(0);break;}
    case 2:{ui->a_m_l1->setHidden(0);ui->a_m_l2->setHidden(0);break;}
    case 3:{ui->a_m_l1->setHidden(0);ui->a_m_l2->setHidden(0);ui->a_m_l3->setHidden(0);break;}
    case 4:{ui->a_m_l1->setHidden(0);ui->a_m_l2->setHidden(0);ui->a_m_l3->setHidden(0);ui->a_m_l4->setHidden(0);break;}
    }

}
void MainWindow::setweaponslots(void)
{
    ui->w_m_l1->setHidden(1);
    ui->w_m_l2->setHidden(1);
    ui->w_m_l3->setHidden(1);
    ui->w_m_l4->setHidden(1);
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
            case 1:{ui->w_m_l1->setHidden(0);break;}
            case 2:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);break;}
            case 3:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);break;}
            case 4:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);ui->w_m_l4->setHidden(0);break;}
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
            case 1:{ui->w_m_l1->setHidden(0);break;}
            case 2:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);break;}
            case 3:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);break;}
            case 4:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);ui->w_m_l4->setHidden(0);break;}
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
            case 1:{ui->w_m_l1->setHidden(0);break;}
            case 2:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);break;}
            case 3:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);break;}
            case 4:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);ui->w_m_l4->setHidden(0);break;}
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
            case 1:{ui->w_m_l1->setHidden(0);break;}
            case 2:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);break;}
            case 3:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);break;}
            case 4:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);ui->w_m_l4->setHidden(0);break;}
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
            case 1:{ui->w_m_l1->setHidden(0);break;}
            case 2:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);break;}
            case 3:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);break;}
            case 4:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);ui->w_m_l4->setHidden(0);break;}
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
            case 1:{ui->w_m_l1->setHidden(0);break;}
            case 2:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);break;}
            case 3:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);break;}
            case 4:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);ui->w_m_l4->setHidden(0);break;}
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
            case 1:{ui->w_m_l1->setHidden(0);break;}
            case 2:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);break;}
            case 3:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);break;}
            case 4:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);ui->w_m_l4->setHidden(0);break;}
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
            case 1:{ui->w_m_l1->setHidden(0);break;}
            case 2:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);break;}
            case 3:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);break;}
            case 4:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);ui->w_m_l4->setHidden(0);break;}
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
            case 1:{ui->w_m_l1->setHidden(0);break;}
            case 2:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);break;}
            case 3:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);break;}
            case 4:{ui->w_m_l1->setHidden(0);ui->w_m_l2->setHidden(0);ui->w_m_l3->setHidden(0);ui->w_m_l4->setHidden(0);break;}
            }
            break;
        }

    }

}
void MainWindow::guirefresh(void)
{
    load = true; //used to cheat the removal of "apply buttons"

    ui->lcd_current_slot->display(s+1);
    ui->cb_replay->setCurrentIndex(0);
    ui->sb_bm_progress1->setValue(ff7.slot[s].bm_progress1);
    ui->sb_bm_progress2->setValue(ff7.slot[s].bm_progress2);
    ui->sb_bm_progress3->setValue(ff7.slot[s].bm_progress3);
    ui->sb_mprogress->setValue(ff7.slot[s].mprogress);
/*~~~~~~~~~~~~~~~~~~~~~~~~~Set Menu Items~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ui->actionSlot_01->setChecked(0);
ui->actionSlot_02->setChecked(0);
ui->actionSlot_03->setChecked(0);
ui->actionSlot_04->setChecked(0);
ui->actionSlot_05->setChecked(0);
ui->actionSlot_06->setChecked(0);
ui->actionSlot_07->setChecked(0);
ui->actionSlot_08->setChecked(0);
ui->actionSlot_09->setChecked(0);
ui->actionSlot_10->setChecked(0);
ui->actionSlot_11->setChecked(0);
ui->actionSlot_12->setChecked(0);
ui->actionSlot_13->setChecked(0);
ui->actionSlot_14->setChecked(0);
ui->actionSlot_15->setChecked(0);
switch(s)
{
case 0:ui->actionSlot_01->setChecked(1);break;
case 1:ui->actionSlot_02->setChecked(1);break;
case 2:ui->actionSlot_03->setChecked(1);break;
case 3:ui->actionSlot_04->setChecked(1);break;
case 4:ui->actionSlot_05->setChecked(1);break;
case 5:ui->actionSlot_06->setChecked(1);break;
case 6:ui->actionSlot_07->setChecked(1);break;
case 7:ui->actionSlot_08->setChecked(1);break;
case 8:ui->actionSlot_09->setChecked(1);break;
case 9:ui->actionSlot_10->setChecked(1);break;
case 10:ui->actionSlot_11->setChecked(1);break;
case 11:ui->actionSlot_12->setChecked(1);break;
case 12:ui->actionSlot_13->setChecked(1);break;
case 13:ui->actionSlot_14->setChecked(1);break;
case 14:ui->actionSlot_15->setChecked(1);break;
}

if (ff7.savetype ==1)
{
    ui->actionSave_File->setEnabled(1);
    ui->actionExport_PC_Save->setEnabled(1);
    ui->actionExport_PSX->setEnabled(1);
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

}
else if (ff7.savetype ==2)
{

    ui->actionSave_File->setEnabled(1);
    ui->actionExport_PC_Save->setEnabled(1);
    ui->actionExport_PSX->setEnabled(1);
    ui->actionFrom_PSV_Slot->setEnabled(1);
    ui->actionFrom_PSX_Slot->setEnabled(1);
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
else if (ff7.savetype ==3)
{
    ui->actionSave_File->setEnabled(1);
    ui->actionExport_PC_Save->setEnabled(1);
    ui->actionExport_PSX->setEnabled(1);
    ui->actionFrom_PSV_Slot->setEnabled(1);
    ui->actionFrom_PSX_Slot->setEnabled(1);
    ui->actionClear_Slot->setEnabled(0);
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
else if (ff7.savetype ==4)
{
    ui->actionSave_File->setEnabled(0); // read only
    ui->actionExport_PC_Save->setEnabled(1);
    ui->actionExport_PSX->setEnabled(1);
    ui->actionFrom_PSV_Slot->setEnabled(0);
    ui->actionFrom_PSX_Slot->setEnabled(0);
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
else if (ff7.savetype ==5)
{
    ui->actionSave_File->setEnabled(0);          // read only
    ui->actionExport_PC_Save->setEnabled(1);
    ui->actionExport_PSX->setEnabled(1);
    ui->actionFrom_PSV_Slot->setEnabled(0);    //read only
    ui->actionFrom_PSX_Slot->setEnabled(0);   //read only
    ui->actionClear_Slot->setEnabled(0);
    ui->actionPaste_Slot->setEnabled(0);      //read only
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
    ui->actionSave_File->setEnabled(0);
    ui->actionExport_PC_Save->setEnabled(0);
    ui->actionExport_PSX->setEnabled(0);
    ui->actionFrom_PSV_Slot->setEnabled(0);
    ui->actionFrom_PSX_Slot->setEnabled(0);
    ui->actionClear_Slot->setEnabled(0);
    ui->actionPaste_Slot->setEnabled(0);
    ui->actionCopy_Slot->setEnabled(0);
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
//Load Game Options
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
//Load Current Disk
ui->sb_curdisc->setValue(ff7.slot[s].disc);

// ui->sb_kalmprog->setValue(ff7.slot[s].kalmprog);

// check for seppie and young cloud to avoid possible breakage of save game since we don't account for them yet.


if (ff7.slot[s].chars[6].id == 9)
{
    ui->btn_cait->setEnabled(false);
    if(curchar ==6){curchar =0;}
}
else {ui->btn_cait->setEnabled(true);}

if (ff7.slot[s].chars[7].id == 10)
{
    ui->btn_vincent->setEnabled(false);
    if(curchar ==7){curchar = 0;}
}
else {ui->btn_vincent->setEnabled(true);}

if(ui->action_show_test_data->isChecked())
{
    ui->btn_vincent->setEnabled(true);
    ui->btn_cait->setEnabled(true);
    ui->cb_id->setEnabled(true);
}

//Set up location Data
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
}
for (int i=0;i<9;i++)//phsmask
{
    ui->list_phs_chars->setCurrentRow(i);
    if ((1 << i) & ff7.slot[s].phsmask){ui->list_phs_chars->currentItem()->setCheckState(Qt::Unchecked);}
    else{ui->list_phs_chars->currentItem()->setCheckState(Qt::Checked);}
}
for (int i=0;i<9;i++)//unlocked
{
    ui->list_chars_unlocked->setCurrentRow(i);
    if ((1 << i) & ff7.slot[s].unlockedchars){ui->list_chars_unlocked->currentItem()->setCheckState(Qt::Checked);}
    else{ui->list_chars_unlocked->currentItem()->setCheckState(Qt::Unchecked);}
}
for(int i=0;i<51;i++)
{
ui->list_keyitems->setCurrentRow(i);
ui->list_keyitems->currentItem()->setCheckState(Qt::Unchecked);
}
for (int i=0;i<51;i++)// key items
{
   // if (ff7.slot[s].keyitems[div(i,8).quot] & (1 << (div(i,8).rem)))
    if (ff7.slot[s].keyitems[i/8] & (1 << (i%8)))
    {
        ui->list_keyitems->setCurrentRow(i);
        ui->list_keyitems->currentItem()->setCheckState(Qt::Checked);
    }
}

//set up party combo boxes (checking for empty slots)
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
    //set up item table
int j= ui->tbl_itm->currentRow();
    ui->tbl_itm->clear(); // just incase
    ui->tbl_itm->setColumnWidth(0,145);
    ui->tbl_itm->setColumnWidth(1,32);
    ui->tbl_itm->setRowCount(320);
    for (int i=0;i<320;i++) // set up items
    {
        if (ff7.slot[s].items[i].qty == 255 && ff7.slot[s].items[i].id == 255)
        {
            newItem = new QTableWidgetItem("-------EMPTY--------",0);
            ui->tbl_itm->setItem(i,0,newItem);
            ui->tbl_itm->setRowHeight(i,22);

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
        ui->tbl_itm->setCurrentCell(j,0);
    }

    j= ui->tbl_materia->currentRow();

    //set up materia table.
    //ui->tbl_materia->clear();
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
            if (aptemp == 0xFFFFFF){newItem =new QTableWidgetItem("Master");ui->tbl_materia->setItem(mat,1,newItem);}
            else{newItem =new QTableWidgetItem(QString("N/A"),0);ui->tbl_materia->setItem(mat,1,newItem);}

        }
        else if (ff7.slot[s].materias[mat].id !=0xff)
        {
            newItem = new QTableWidgetItem(QIcon(Materias[ff7.slot[s].materias[mat].id].image),Materias[ff7.slot[s].materias[mat].id].name,0);
            ui->tbl_materia->setItem(mat,0,newItem);
            aptemp = ff7.slot[s].materias[mat].ap[0] |(ff7.slot[s].materias[mat].ap[1] << 8) | (ff7.slot[s].materias[mat].ap[2] << 16);
            if (aptemp == 0xFFFFFF){newItem =new QTableWidgetItem("Master");ui->tbl_materia->setItem(mat,1,newItem);}
            else{newItem =new QTableWidgetItem(ap.setNum(aptemp));ui->tbl_materia->setItem(mat,1,newItem);}
        }
        else
        {
            newItem = new QTableWidgetItem("===Empty Slot===",0);
            ui->tbl_materia->setItem(mat,0,newItem);
            newItem = new QTableWidgetItem("",0);
            ui->tbl_materia->setItem(mat,1,newItem);
        }
    }
    ui->tbl_materia->setCurrentCell(j,0,QItemSelectionModel::ClearAndSelect);

    /*~~~~~~~~~~~~~~~~~~~~~~`New Materia Code~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        //clear then set the skill list & stats
        //ui->list_spells->clear();

        //for (int i=0; i<Materias[ui->combo_add_mat->currentIndex()].levels;i++){ui->list_spells->addItem(Materias[ui->combo_add_mat->currentIndex()].skills[i]);}

        ui->lbl_mat_stats->setText(Materias[ui->combo_add_mat->currentIndex()].stats);// set stat string..

        qint32 aptemp = ff7.slot[s].materias[j].ap[0] |(ff7.slot[s].materias[j].ap[1] << 8) | (ff7.slot[s].materias[j].ap[2] << 16);

        qint32 masterap = Materias[ui->combo_add_mat->currentIndex()].ap[Materias[ui->combo_add_mat->currentIndex()].levels-2];

        ui->lcd_ap_master->display(masterap);

        // Check Materia Max AP and Set the Spin Box's Max Value.
        if(Materias[ui->combo_add_mat->currentIndex()].levels>1)
        {
          ui->sb_addap->setMaximum(masterap);
        }
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
        //fill all stars needed..
               }
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
    /*~~~~~~~~~~~~~~~~~~~~~~End Of New Materia Code~~~~~~~~~~~~~~~~~~~~~*/



    //set up materia_2 table
    ui->tbl_materia_2->clear();
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
            if (aptemp == 0xFFFFFF){newItem =new QTableWidgetItem("Master");ui->tbl_materia_2->setItem(mat,1,newItem);}
            else{newItem =new QTableWidgetItem(ap.setNum(aptemp));ui->tbl_materia_2->setItem(mat,1,newItem);}
        }
        else
        {
            newItem = new QTableWidgetItem("===Empty Slot===",0);
            ui->tbl_materia_2->setItem(mat,0,newItem);
        }
    }

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
    load =false;
 }
void MainWindow::chocobo_refresh()
{
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
ui->sb_c2_sprint->setValue(ff7.slot[s].chocobos[1].sprintspd);
ui->sb_c2_maxsprint->setValue(ff7.slot[s].chocobos[1].maxsprintspd);
ui->sb_c2_speed->setValue(ff7.slot[s].chocobos[1].speed);
ui->sb_c2_maxspeed->setValue((ff7.slot[s].chocobos[1].maxspeed));
//ui->cb_c2_personality->setCurrentIndex(ff7.slot[s].chocobos[1].personality); //need more data for this.
//below are OK
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
ui->sb_c3_sprint->setValue(ff7.slot[s].chocobos[2].sprintspd);
ui->sb_c3_maxsprint->setValue(ff7.slot[s].chocobos[2].maxsprintspd);
ui->sb_c3_speed->setValue(ff7.slot[s].chocobos[2].speed);
ui->sb_c3_maxspeed->setValue((ff7.slot[s].chocobos[2].maxspeed));
//ui->cb_c3_personality->setCurrentIndex(ff7.slot[s].chocobos[2].personality); //need more data for this.
//below are OK
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
ui->sb_c4_sprint->setValue(ff7.slot[s].chocobos[3].sprintspd);
ui->sb_c4_maxsprint->setValue(ff7.slot[s].chocobos[3].maxsprintspd);
ui->sb_c4_speed->setValue(ff7.slot[s].chocobos[3].speed);
ui->sb_c4_maxspeed->setValue((ff7.slot[s].chocobos[3].maxspeed));
//ui->cb_c4_personality->setCurrentIndex(ff7.slot[s].chocobos[3].personality); //need more data for this.
//below are OK
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
ui->sb_c5_sprint->setValue(ff7.slot[s].choco56[0].sprintspd);
ui->sb_c5_maxsprint->setValue(ff7.slot[s].choco56[0].maxsprintspd);
ui->sb_c5_speed->setValue(ff7.slot[s].choco56[0].speed);
ui->sb_c5_maxspeed->setValue((ff7.slot[s].choco56[0].maxspeed));
//ui->cb_c5_personality->setCurrentIndex(ff7.slot[s].choco56[0].personality); //need more data for this.
//below are OK
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
ui->sb_c6_sprint->setValue(ff7.slot[s].choco56[1].sprintspd);
ui->sb_c6_maxsprint->setValue(ff7.slot[s].choco56[1].maxsprintspd);
ui->sb_c6_speed->setValue(ff7.slot[s].choco56[1].speed);
ui->sb_c6_maxspeed->setValue((ff7.slot[s].choco56[1].maxspeed));
//ui->cb_c6_personality->setCurrentIndex(ff7.slot[s].choco56[1].personality); //need more data for this.
//below are OK
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
}

//Char Buttons.

void MainWindow::on_btn_cloud_clicked()
{
    curchar=0;
    load=true;
    charupdate();
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/cloud_icon"));
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
    ui->limit_1a->setText("Braver");
    ui->limit_1b->setText("Cross-Slash");
    ui->limit_2a->setText("Blade Beam");
    ui->limit_2b->setText("Climhazzard");
    ui->limit_3a->setText("Meteorain");
    ui->limit_3b->setText("Finishing Touch");
    ui->limit_4->setText("OmniSlash");
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
    charupdate();
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/barret_icon"));

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
    ui->limit_1a->setText("Big Shot");
    ui->limit_1b->setText("Mindblow");
    ui->limit_2a->setText("Grenade Bomb");
    ui->limit_2b->setText("Hammerblow");
    ui->limit_3a->setText("Satellite Beam");
    ui->limit_3b->setText("Angermax");
    ui->limit_4->setText("Catastrophe");
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
    charupdate();
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/tifa_icon"));
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
    ui->limit_1a->setText("Beat Rush");
    ui->limit_1b->setText("SomerSault");
    ui->limit_2a->setText("Waterkick");
    ui->limit_2b->setText("Meteodrive");
    ui->limit_3a->setText("Dolphin Blow");
    ui->limit_3b->setText("Meteor Strike");
    ui->limit_4->setText("Final Heaven");
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
    charupdate();
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/aeris_icon"));
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
    ui->limit_1a->setText("Healing Wind");
    ui->limit_1b->setText("Seal Evil");
    ui->limit_2a->setText("Breath of the Earth");
    ui->limit_2b->setText("Fury Brand");
    ui->limit_3a->setText("Planet Protector");
    ui->limit_3b->setText("Pulse of Life");
    ui->limit_4->setText("Great Gospel");
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
{   curchar=4;
    load=true;
    charupdate();
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/red_icon"));
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
    ui->limit_1a->setText("Sled Fang");
    ui->limit_1b->setText("Lunatic High");
    ui->limit_2a->setText("Blood Fang");
    ui->limit_2b->setText("Stardust Ray");
    ui->limit_3a->setText("Howling Moon");
    ui->limit_3b->setText("Earth Rave");
    ui->limit_4->setText("Cosmo Memory");
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
    charupdate();
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/yuffie_icon"));
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
    ui->limit_1a->setText("Greased Lightning");
    ui->limit_1b->setText("Clear Tranquil");
    ui->limit_2a->setText("Landscaper");
    ui->limit_2b->setText("Bloodfest");
    ui->limit_3a->setText("Gauntlet");
    ui->limit_3b->setText("Doom of the Living");
    ui->limit_4->setText("All Creation");
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
    charupdate();
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/cait_icon"));
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
    ui->limit_1a->setText("Dice");
    ui->limit_1b->setText("");
    ui->limit_2a->setText("Slots");
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
    charupdate();
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/vincent_icon"));
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
    ui->limit_1a->setText("Gallian Beast");
    ui->limit_1b->setText("");
    ui->limit_2a->setText("Death Gigas");
    ui->limit_2b->setText("");
    ui->limit_3a->setText("Hellmasker");
    ui->limit_3b->setText("");
    ui->limit_4->setText("Chaos");
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
    charupdate();
    ui->lbl_avatar->setPixmap(QPixmap(":/icon/cid_icon"));
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
    ui->limit_1a->setText("Boost Jump");
    ui->limit_1b->setText("Dynamite");
    ui->limit_2a->setText("Hyper Jump");
    ui->limit_2b->setText("Dragon");
    ui->limit_3a->setText("Dragon Dive");
    ui->limit_3b->setText("Big Brawl");
    ui->limit_4->setText("Highwind");
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

//party tab

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
    {ff7.slot[s].party[0] = index;

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

//Chocobo Tab
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
    if(ui->sb_stables_occupied->value() > ui->sb_stables_owned->value())
    {
    ui->sb_stables_occupied->setValue(ui->sb_stables_owned->value());
    }
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

//ChocoboStats

void MainWindow::on_cb_c1_sex_currentIndexChanged(int index)
{
    ff7.slot[s].chocobos[0].sex = index;
}
void MainWindow::on_cb_c1_type_currentIndexChanged(int index)
{
    ff7.slot[s].chocobos[0].type = index;
}
void MainWindow::on_sb_c1_coop_valueChanged()
{
    ff7.slot[s].chocobos[0].coop= ui->sb_c1_coop->value();
}
void MainWindow::on_sb_c1_accel_valueChanged()
{
    ff7.slot[s].chocobos[0].accel= ui->sb_c1_accel->value();
}
void MainWindow::on_sb_c1_intel_valueChanged()
{
    ff7.slot[s].chocobos[0].intelligence = ui->sb_c1_intel->value();
}
void MainWindow::on_sb_c1_raceswon_valueChanged()
{
    ff7.slot[s].chocobos[0].raceswon = ui->sb_c1_raceswon->value();
}
void MainWindow::on_sb_c1_pcount_valueChanged()
{
    ff7.slot[s].chocobos[0].pcount= ui->sb_c1_pcount->value();
}
void MainWindow::on_cb_c2_sex_currentIndexChanged(int index)
{
    ff7.slot[s].chocobos[1].sex = index;
}
void MainWindow::on_cb_c2_type_currentIndexChanged(int index)
{
    ff7.slot[s].chocobos[1].type = index;
}
void MainWindow::on_sb_c2_coop_valueChanged()
{
    ff7.slot[s].chocobos[1].coop= ui->sb_c2_coop->value();
}
void MainWindow::on_sb_c2_accel_valueChanged()
{
    ff7.slot[s].chocobos[1].accel= ui->sb_c2_accel->value();
}
void MainWindow::on_sb_c2_intel_valueChanged()
{
    ff7.slot[s].chocobos[1].intelligence = ui->sb_c2_intel->value();
}
void MainWindow::on_sb_c2_raceswon_valueChanged()
{
    ff7.slot[s].chocobos[1].raceswon = ui->sb_c2_raceswon->value();
}
void MainWindow::on_sb_c2_pcount_valueChanged()
{
    ff7.slot[s].chocobos[1].pcount= ui->sb_c2_pcount->value();
}
void MainWindow::on_cb_c3_sex_currentIndexChanged(int index)
{
    ff7.slot[s].chocobos[2].sex = index;
}
void MainWindow::on_cb_c3_type_currentIndexChanged(int index)
{
    ff7.slot[s].chocobos[2].type = index;
}
void MainWindow::on_sb_c3_coop_valueChanged()
{
    ff7.slot[s].chocobos[2].coop= ui->sb_c3_coop->value();
}
void MainWindow::on_sb_c3_accel_valueChanged()
{
    ff7.slot[s].chocobos[2].accel= ui->sb_c3_accel->value();
}
void MainWindow::on_sb_c3_intel_valueChanged()
{
    ff7.slot[s].chocobos[2].intelligence = ui->sb_c3_intel->value();
}
void MainWindow::on_sb_c3_raceswon_valueChanged()
{
    ff7.slot[s].chocobos[2].raceswon = ui->sb_c3_raceswon->value();
}
void MainWindow::on_sb_c3_pcount_valueChanged()
{
    ff7.slot[s].chocobos[2].pcount= ui->sb_c3_pcount->value();
}
void MainWindow::on_cb_c4_sex_currentIndexChanged(int index)
{
    ff7.slot[s].chocobos[3].sex = index;
}
void MainWindow::on_cb_c4_type_currentIndexChanged(int index)
{
    ff7.slot[s].chocobos[3].type = index;
}
void MainWindow::on_sb_c4_coop_valueChanged()
{
    ff7.slot[s].chocobos[3].coop= ui->sb_c4_coop->value();
}
void MainWindow::on_sb_c4_accel_valueChanged()
{
    ff7.slot[s].chocobos[3].accel= ui->sb_c4_accel->value();
}
void MainWindow::on_sb_c4_intel_valueChanged()
{
    ff7.slot[s].chocobos[3].intelligence = ui->sb_c4_intel->value();
}
void MainWindow::on_sb_c4_raceswon_valueChanged()
{
    ff7.slot[s].chocobos[3].raceswon = ui->sb_c4_raceswon->value();
}
void MainWindow::on_sb_c4_pcount_valueChanged()
{
    ff7.slot[s].chocobos[3].pcount= ui->sb_c4_pcount->value();
}
void MainWindow::on_cb_c5_sex_currentIndexChanged(int index)
{
    ff7.slot[s].choco56[0].sex = index;
}
void MainWindow::on_cb_c5_type_currentIndexChanged(int index)
{
    ff7.slot[s].choco56[0].type = index;
}
void MainWindow::on_sb_c5_coop_valueChanged()
{
    ff7.slot[s].choco56[0].coop= ui->sb_c5_coop->value();
}
void MainWindow::on_sb_c5_accel_valueChanged()
{
    ff7.slot[s].choco56[0].accel= ui->sb_c5_accel->value();
}
void MainWindow::on_sb_c5_intel_valueChanged()
{
    ff7.slot[s].choco56[0].intelligence = ui->sb_c5_intel->value();
}
void MainWindow::on_sb_c5_raceswon_valueChanged()
{
    ff7.slot[s].choco56[0].raceswon = ui->sb_c5_raceswon->value();
}
void MainWindow::on_sb_c5_pcount_valueChanged()
{
    ff7.slot[s].choco56[0].pcount= ui->sb_c5_pcount->value();
}
void MainWindow::on_cb_c6_sex_currentIndexChanged(int index)
{
    ff7.slot[s].choco56[1].sex = index;
}
void MainWindow::on_cb_c6_type_currentIndexChanged(int index)
{
    ff7.slot[s].choco56[1].type = index;
}
void MainWindow::on_sb_c6_coop_valueChanged()
{
    ff7.slot[s].choco56[1].coop= ui->sb_c6_coop->value();
}
void MainWindow::on_sb_c6_accel_valueChanged()
{
    ff7.slot[s].choco56[1].accel= ui->sb_c6_accel->value();
}
void MainWindow::on_sb_c6_intel_valueChanged()
{
    ff7.slot[s].choco56[1].intelligence = ui->sb_c6_intel->value();
}
void MainWindow::on_sb_c6_raceswon_valueChanged()
{
    ff7.slot[s].choco56[1].raceswon = ui->sb_c6_raceswon->value();
}
void MainWindow::on_sb_c6_pcount_valueChanged()
{
    ff7.slot[s].choco56[1].pcount= ui->sb_c6_pcount->value();
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

    for (int i=0;i<6;i++){ff7.slot[s].chocobonames[0][i] =0xFF;}
    for (int i=0;i<ui->line_c1_name->text().size();i++){ff7.slot[s].chocobonames[0][i] = chFF7[ui->line_c1_name->text().at(i).toAscii()];}

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

//others tab

void MainWindow::on_list_phs_chars_itemChanged()
{
    if(!load)
    {
    quint16 temp =0;
    int j = ui->list_phs_chars->currentRow();
    for (int i=0;i<9;i++)
    {
        ui->list_phs_chars->setCurrentRow(i);
        if(ui->list_phs_chars->currentItem()->checkState() ==Qt::Unchecked)
            temp |=(1 <<i);
    }
    ff7.slot[s].phsmask=temp;
    ui->list_phs_chars->setCurrentRow(j);
    }
}

void MainWindow::on_list_chars_unlocked_itemChanged()
{
    if(!load)
    {
    quint16 temp=0;
    int j=ui->list_chars_unlocked->currentRow();
    for (int i=0;i<9;i++)
    {
        ui->list_chars_unlocked->setCurrentRow(i);
        if(ui->list_chars_unlocked->currentItem()->checkState() ==Qt::Checked)
        {temp |= (1<<i);}
    }
    ff7.slot[s].unlockedchars=temp;
    ui->list_chars_unlocked->setCurrentRow(j);
   }
}
void MainWindow::on_sb_curdisc_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].disc = ui->sb_curdisc->value();
    }
}
void MainWindow::on_sb_love_barret_valueChanged()
{
   if(!load)
   {
   ff7.slot[s].love.barret = ui->sb_love_barret->value();
   }
}
void MainWindow::on_sb_love_aeris_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].love.aeris = ui->sb_love_aeris->value();
    }
}
void MainWindow::on_sb_love_tifa_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].love.tifa = ui->sb_love_tifa->value();
    }
}
void MainWindow::on_sb_love_yuffie_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].love.yuffie = ui->sb_love_yuffie->value();
    }
}

//Item Tab

void MainWindow::on_list_flyers_itemChanged()
{
    if(!load)
    {int j=ui->list_flyers->currentRow();
        ff7.slot[s].turtleflyers=0x40;
        for (int i=0;i<6;i++)
        {
        ui->list_flyers->setCurrentRow(i);
        if(ui->list_flyers->currentItem()->checkState() ==2){ff7.slot[s].turtleflyers |= (1 << i);}
        }
     ui->list_flyers->setCurrentRow(j);
    }
}
void MainWindow::on_list_keyitems_itemChanged()
{
    if (!load)
    {
        int j = ui->list_keyitems->currentRow();
        for (int i=0;i<8;i++) {ff7.slot[s].keyitems[i] = 0; }
        for (int i=0;i<51;i++)
        {
            ui->list_keyitems->setCurrentRow(i);
            if (ui->list_keyitems->currentItem()->checkState() == Qt::Checked)
            {
                ff7.slot[s].keyitems[i/8] |= (1<<i%8);
            }
        }
        ui->list_keyitems->setCurrentRow(j);
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
    if (ff7.slot[s].items[row].qty == 255 && ff7.slot[s].items[row].id == 255) // if you click on an empty slot add whats in the item and qty boxes.
    {
        if (ui->combo_additem->currentIndex()<256){ff7.slot[s].items[row].id = ui->combo_additem->currentIndex();ff7.slot[s].items[row].qty = quint8(ui->sb_addqty->value() * 2);}
        else{ff7.slot[s].items[row].id = (ui->combo_additem->currentIndex()-256);ff7.slot[s].items[row].qty  = quint8(ui->sb_addqty->value()* 2) +1;}
        guirefresh();
    }
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

//materia Tab

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

    else
    {
    ui->eskill_group->setVisible(false);
    if(ui->tbl_materia->currentItem()->text() == "===Empty Slot===")
        {
            ui->combo_mat_type->setCurrentIndex(0);
            ui->combo_add_mat->setCurrentIndex(0);
            ff7.slot[s].materias[row].id =0xFF;
            ff7.slot[s].materias[row].ap[0]=0xFF;
            ff7.slot[s].materias[row].ap[1]=0xFF;
            ff7.slot[s].materias[row].ap[2]=0xFF;
            guirefresh();
        }

    else
        {
            ui->combo_add_mat->setCurrentIndex(ff7.slot[s].materias[row].id);
            ui->sb_addap->setEnabled(1);
            ui->sb_addap->setValue(ff7.slot[s].materias[row].ap[0] |(ff7.slot[s].materias[row].ap[1] << 8) | (ff7.slot[s].materias[row].ap[2] << 16));
        }
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
    ui->combo_mat_type->setCurrentIndex(Materias[index].type);
    for(int i=0;i<ui->combo_add_mat_2->count();i++)
        {if(ui->combo_add_mat_2->itemText(i)==Materias[index].name){ui->combo_add_mat_2->setCurrentIndex(i);}}

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
        for(int i=0;i<0x5B;i++){if(index==Materias[i].type){ui->combo_add_mat_2->addItem(QIcon(Materias[i].image),Materias[i].name);}}
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
}

void MainWindow::geteskills(int row)
{
    load = true;
    quint32 temp = ff7.slot[s].materias[row].ap[0] |(ff7.slot[s].materias[row].ap[1] << 8) | (ff7.slot[s].materias[row].ap[2] << 16);
    ui->sb_addap->setValue(temp);
    on_btn_eskillclear_clicked();
    for (int i=0;i<24;i++)
        {
        ui->list_eskill->setCurrentRow(i);
        if ((1 << i) & temp){ui->list_eskill->currentItem()->setCheckState(Qt::Checked);}
        }
    load = false;
}
void MainWindow::on_list_eskill_itemChanged()
{
 if(!load)apply_eskills();
}
void MainWindow::on_btn_eskillclear_clicked()
{
    for (int i=0;i<24;i++)
    {
        ui->list_eskill->setCurrentRow(i);
        ui->list_eskill->currentItem()->setCheckState(Qt::Unchecked);
    }//loop thru and uncheck no need to apply each one should thrown an itemChanged() event
}
void MainWindow::apply_eskills()
{if(!load){
load =true;
int j = ui->list_eskill->currentRow();
quint32 ap_temp =0;
quint32 temp =0;
for (int i=0;i<24;i++)
    {
    ui->list_eskill->setCurrentRow(i);
    if (ui->list_eskill->currentItem()->checkState() == Qt::Checked)
       {temp |= (1 << i);}
    }
ap_temp= (temp & 0xFFFFFF);
ui->list_eskill->setCurrentRow(j);
load =false;
ui->sb_addap->setValue(ap_temp);
guirefresh();
}}

//save location tab
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
    ff7.slot[s].mapid= ui->sb_map_id->value();
}
void MainWindow::on_sb_loc_id_valueChanged()
{
    ff7.slot[s].locationid = ui->sb_loc_id->value();
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
    ff7.slot[s].coord.x = ui->sb_coordx->value();
}
void MainWindow::on_sb_coordy_valueChanged()
{
    ff7.slot[s].coord.y = ui->sb_coordy->value();
}
void MainWindow::on_sb_coordz_valueChanged()
{
    ff7.slot[s].coord.z = ui->sb_coordz->value();
}

//char stats tab
void MainWindow::on_cb_id_toggled(bool checked)
{
if(!load)
{
    if (curchar ==6)
    {
        if (checked){ff7.slot[s].chars[6].id = 9;}
        else {ff7.slot[s].chars[6].id = 6;}
    }
    if (curchar ==7)
    {
        if (checked){ff7.slot[s].chars[7].id = 10;}
        else {ff7.slot[s].chars[7].id = 7;}
    }
//charupdate();
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
    if(!load)
    {
    ff7.slot[s].chars[curchar].curHP = ui->sb_curhp->value();
    }
}
void MainWindow::on_sb_curmp_valueChanged()
{
   if(!load)
   {
   ff7.slot[s].chars[curchar].curMP = ui->sb_curmp->value();
   }
}
void MainWindow::on_sb_maxhp_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].maxHP =ui->sb_maxhp->value();
    }
}
void MainWindow::on_sb_maxmp_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].maxMP =ui->sb_maxmp->value();
    }
}
void MainWindow::on_sb_hp_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].baseHP = ui->sb_hp->value();
    }
}
void MainWindow::on_sb_mp_valueChanged()
{
   if(!load)
   {
   ff7.slot[s].chars[curchar].baseMP = ui->sb_mp->value();
   }
}
void MainWindow::on_sb_next_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].expNext =  ui->sb_next->value();
    }
}
void MainWindow::on_sb_exp_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].exp = ui->sb_exp->value();
    }
}
void MainWindow::on_sb_kills_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].kills = ui->sb_kills->value();
    }
}

void MainWindow::on_sb_str_valueChanged()
{
   if(!load)
   {
   ff7.slot[s].chars[curchar].strength = ui->sb_str->value();
   }
}
void MainWindow::on_sb_dex_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].dexterity = ui->sb_dex->value();
    }
}
void MainWindow::on_sb_mag_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].magic = ui->sb_mag->value();
    }
}
void MainWindow::on_sb_vit_valueChanged()
{
   if(!load)
   {
   ff7.slot[s].chars[curchar].vitality = ui->sb_vit->value();
   }
}
void MainWindow::on_sb_spr_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].spirit = ui->sb_spr->value();
    }
}
void MainWindow::on_sb_lck_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].luck = ui->sb_lck->value();
    }
}
void MainWindow::on_sb_strbonus_valueChanged()
{
   if(!load)
   {
   ff7.slot[s].chars[curchar].strength_bonus = ui->sb_strbonus->value();
   }
}
void MainWindow::on_sb_dexbonus_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].dexterity_bonus = ui->sb_dexbonus->value();
    }
}
void MainWindow::on_sb_magbonus_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].magic_bonus = ui->sb_magbonus->value();
    }
}
void MainWindow::on_sb_vitbonus_valueChanged()
{
   if(!load)
   {
   ff7.slot[s].chars[curchar].vitality_bonus = ui->sb_vitbonus->value();
   }
}
void MainWindow::on_sb_sprbonus_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].spirit_bonus = ui->sb_sprbonus->value();
    }
}
void MainWindow::on_sb_lckbonus_valueChanged()
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].luck_bonus = ui->sb_lckbonus->value();
    }
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
   if(!load)
   {
   ff7.slot[s].chars[curchar].timesused1 = ui->sb_used1->value();
   }
}
void MainWindow::on_sb_used2_valueChanged()
{
   if(!load)
   {
   ff7.slot[s].chars[curchar].timesused2 = ui->sb_used2->value();
   }
}
void MainWindow::on_sb_used3_valueChanged()
{
   if(!load)
   {
   ff7.slot[s].chars[curchar].timesused3 = ui->sb_used3->value();
   }
}
void MainWindow::on_sb_limitlvl_valueChanged(int value)
{
    if(!load)
    {
    ff7.slot[s].chars[curchar].limitlevel= value; //ui->sb_limitlvl->value();
    }
}
void MainWindow::on_slide_limit_valueChanged(int value)
{
   if(!load)
   {
   ff7.slot[s].chars[curchar].limitbar = value; //ui->slide_limit->value();
    }
}
void MainWindow::limitapply()
{
    ff7.slot[s].chars[curchar].limits = 0;
            if (curchar == 7) {
                    if (ui->limit_1a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<0);
                    if (ui->limit_2a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<3);
                    if (ui->limit_3a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<6);
                    if (ui->limit_4 ->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<9);
            }
            else if (curchar == 6) {
                    if (ui->limit_1a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<0);
                    if (ui->limit_2a->isChecked()==1) ff7.slot[s].chars[curchar].limits |= (1<<3);
            }
            else {
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
    if(!load)
    {
    ff7.slot[s].chars[curchar].accessory = index;
    }
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
    load=true;
        int a = (value & 0xff);
        int b = (value & 0xff00) >> 8;
        int c = (value & 0xff0000) >> 16;

       ff7.slot[s].chars[curchar].materias[mslotsel].ap[0] = a;
       ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] = b;
       ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] = c;
       guirefresh();
    load=false;
    }

}

void MainWindow::on_btn_mastermateria_slot_clicked()
{
    ui->sb_addap_slot->setValue(0xFFFFFF);
    if(ff7.slot[s].chars[curchar].materias[mslotsel].id == 0x2C) {geteskills2(mslotsel);}
    guirefresh();
}
void MainWindow::on_clearMateria_slot_clicked()
{
    ff7.slot[s].chars[curchar].materias[mslotsel].id = 0xFF;
    ui->sb_addap_slot->setValue(0xFFFFFF);
    if(ff7.slot[s].chars[curchar].materias[mslotsel].id == 0x2C) {geteskills2(mslotsel);}
    guirefresh();
}

void MainWindow::on_w_m_s1_clicked()
{
    mslotsel =0;
    int aptemp;
    load =true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_w_m_s2_clicked()
{
    mslotsel =1;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_w_m_s3_clicked()
{
    mslotsel =2;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_w_m_s4_clicked()
{
    mslotsel =3;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_w_m_s5_clicked()
{
    mslotsel =4;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_w_m_s6_clicked()
{
    mslotsel =5;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_w_m_s7_clicked()
{
    mslotsel =6;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_w_m_s8_clicked()
{
    mslotsel =7;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}

void MainWindow::on_a_m_s1_clicked()
{
    mslotsel =8;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_a_m_s2_clicked()
{
    mslotsel =9;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_a_m_s3_clicked()
{
    mslotsel =10;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_a_m_s4_clicked()
{
    mslotsel =11;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_a_m_s5_clicked()
{
    mslotsel =12;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_a_m_s6_clicked()
{
    mslotsel =13;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_a_m_s7_clicked()
{
    mslotsel =14;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}
void MainWindow::on_a_m_s8_clicked()
{
    mslotsel = 15;
    int aptemp;
    load=true;
    aptemp = (ff7.slot[s].chars[curchar].materias[mslotsel].ap[0]|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[1] << 8)|(ff7.slot[s].chars[curchar].materias[mslotsel].ap[2] << 16));
    ui->combo_add_mat_slot->setCurrentIndex(ff7.slot[s].chars[curchar].materias[mslotsel].id);
    ui->sb_addap_slot->setValue(aptemp);
    load=false;
}

void MainWindow::geteskills2(int row)
{
    quint32 temp = ff7.slot[s].chars[curchar].materias[row].ap[0] |(ff7.slot[s].chars[curchar].materias[row].ap[1] << 8) | (ff7.slot[s].chars[curchar].materias[row].ap[2] << 16);
    ui->sb_addap_slot->setValue(temp);

    for (int i=0;i<24;i++)
                {
                    ui->list_eskill_2->setCurrentRow(i);
                    if ((1 << i) & temp){ui->list_eskill_2->currentItem()->setCheckState(Qt::Checked);}
                    else{ui->list_eskill_2->currentItem()->setCheckState(Qt::Unchecked);}
                }

}
void MainWindow::on_list_eskill_2_itemChanged()
{
    apply_eskills2();
}
void MainWindow::apply_eskills2()
{
if(!load)
    load =true;
   {
   int j = ui->list_eskill_2->currentRow();
   quint32 ap_temp =0;
   quint32 temp =0;
   for (int i=0;i<24;i++)
           {
                ui->list_eskill_2->setCurrentRow(i);
                if (ui->list_eskill_2->currentItem()->checkState() == Qt::Checked){temp |= (1 << i);}
                else{};
           }
            ap_temp=(temp & 0xFFFFFF);
    ui->list_eskill_2->setCurrentRow(j);
    load =false;
    ui->sb_addap_slot->setValue(ap_temp);//set the values

    }
}


// game options
void MainWindow::on_slide_ul_r_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[0][0] = value;}
}
void MainWindow::on_slide_ul_g_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[0][1] = value;}
}
void MainWindow::on_slide_ul_b_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[0][2] = value;}
}

void MainWindow::on_slide_ur_r_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[1][0] = value;}
}
void MainWindow::on_slide_ur_g_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[1][1] = value;}
}
void MainWindow::on_slide_ur_b_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[1][2] = value;}
}

void MainWindow::on_slide_ll_r_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[2][0] = value;}
}
void MainWindow::on_slide_ll_g_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[2][1] = value;}
}
void MainWindow::on_slide_ll_b_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[2][2] = value;}
}

void MainWindow::on_slide_lr_r_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[3][0] = value;}
}
void MainWindow::on_slide_lr_g_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[3][1] = value;}
}
void MainWindow::on_slide_lr_b_valueChanged(int value)
{
    if(!load){ff7.slot[s].colors[3][2] = value;}
}

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
if(ui->combo_sound->currentIndex() == 1)
    {ff7.slot[s].options1 += 0x01;}
if(ui->combo_control->currentIndex() == 1)
    {ff7.slot[s].options1 += 0x04;} //you have to also change mapped buttons for this to work 100%
if(ui->combo_cursor->currentIndex() == 1)
    {ff7.slot[s].options1 +=0x10;}
if(ui->combo_atb->currentIndex() == 1)
    {ff7.slot[s].options1 +=0x40;}
if(ui->combo_atb->currentIndex() == 2)
    {
    ff7.slot[s].options1 += 0x80;
    }
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
    if(checked== 2){ff7.slot[s].chocoborn |= (1<<1);}
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
    ui->line_location->setText("Platform");
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
    ui->line_location->setText("Kalm Inn");
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
    ui->line_location->setText("Ropeway Station");
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
    ui->line_location->setText("Forgotten City");
    ui->sb_map_id->setValue(1);
    ui->sb_loc_id->setValue(646);
    ui->sb_coordx->setValue(641);
    ui->sb_coordy->setValue(793);
    ui->sb_coordz->setValue(243);
    ui->list_chars_unlocked->item(3)->setCheckState(Qt::Unchecked);
    ui->list_phs_chars->item(3)->setCheckState(Qt::Unchecked);
    ui->label_replaynote->setText(tr("Replay the death of Aerith.This option Will remove Aerith from your PHS"));
    }
    else {ui->label_replaynote->setText("         INFO ON CURRENTLY SELECTED REPLAY MISSION");}
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

void MainWindow::on_action_show_test_data_toggled()
{
    if(ui->action_show_test_data->isChecked())
     {
        ui->btn_remove_all_items->setVisible(true);
        ui->btn_remove_all_materia->setVisible(true);
        ui->btn_remove_all_stolen->setVisible(true);
        ui->lbl_z_4_0->setVisible(true);
        ui->lbl_z_4_1->setVisible(true);
        ui->lbl_z_4_2->setVisible(true);
        ui->lbl_z_4_3->setVisible(true);
        ui->lcd_z_4_0->setVisible(true);
        ui->lcd_z_4_1->setVisible(true);
        ui->lcd_z_4_2->setVisible(true);
        ui->lcd_z_4_3->setVisible(true);
        ui->btn_vincent->setEnabled(true);
        ui->cb_id->setEnabled(true);
        ui->btn_cait->setEnabled(true);
        settings.setValue("show_test",1);
    }
    else
    {
        ui->btn_remove_all_items->setVisible(false);
        ui->btn_remove_all_materia->setVisible(false);
        ui->btn_remove_all_stolen->setVisible(false);
        ui->lbl_z_4_0->setVisible(false);
        ui->lbl_z_4_1->setVisible(false);
        ui->lbl_z_4_2->setVisible(false);
        ui->lbl_z_4_3->setVisible(false);
        ui->lcd_z_4_0->setVisible(false);
        ui->lcd_z_4_1->setVisible(false);
        ui->lcd_z_4_2->setVisible(false);
        ui->lcd_z_4_3->setVisible(false);
        if(ff7.slot[s].chars[6].id == 9) {ui->btn_vincent->setEnabled(false);}
        ui->cb_id->setEnabled(false);
        if(ff7.slot[s].chars[7].id == 10) {ui->btn_cait->setEnabled(false);}
        settings.setValue("show_test",0);
    }
}

void MainWindow::on_action_Region_USA_triggered()
{
    ui->action_Region_PAL->setChecked(false);
    ui->action_Region_JPN->setChecked(false);
}

void MainWindow::on_action_Region_PAL_triggered()
{
    ui->action_Region_USA->setChecked(false);
    ui->action_Region_JPN->setChecked(false);
}

void MainWindow::on_action_Region_JPN_triggered()
{
    ui->action_Region_PAL->setChecked(false);
    ui->action_Region_USA->setChecked(false);
}

void MainWindow::on_action_Lang_en_triggered()
{
    ui->action_Lang_es->setChecked(false);
    ui->action_Lang_fr->setChecked(false);
    settings.setValue("lang","en");
    QMessageBox::information(this,"Language Changed","You Must Restart For The Language to Change");
}

void MainWindow::on_action_Lang_es_triggered()
{
    ui->action_Lang_en->setChecked(false);
    ui->action_Lang_fr->setChecked(false);
    settings.setValue("lang","es");
    QMessageBox::information(this,"Idioma Cambiado","Debe reiniciar Para el cambio de idioma");

}

void MainWindow::on_action_Lang_fr_triggered()
{
    ui->action_Lang_es->setChecked(false);
    ui->action_Lang_en->setChecked(false);
    settings.setValue("lang","fr");
    QMessageBox::information(this,"Langue Modifiée","Vous Devez Redemarrer Pour Changer la Langue");
}

