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
#include <QMessageBox>
#include <QFileDialog> // for file dialogs
#include <QDataStream> // for data manip
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"   // contains checksumming functions.
#include "slotselect.h"
#include "loadsave.h"

extern FF7 ff7;
extern int s;
FF7SLOT bufferslot;

void MainWindow::on_actionOpen_Save_File_activated()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Final Fantasy 7 Save"),(""),
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
        tr("Save Final Fantasy 7 PC SaveGame"), "",
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
        tr("Save Final Fantasy 7 MC SaveGame"), "",
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
    tr("Save Final Fantasy 7 SaveGame"),  "",
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
