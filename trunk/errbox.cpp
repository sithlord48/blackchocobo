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

#include "errbox.h"
#include "ui_errbox.h"

/*~~~~~GLOBALS~~~~~~*/

errbox::errbox(QWidget *parent,FF7 *ff7data,int slot) :
    QDialog(parent),
    ui(new Ui::errbox)
{
    ui->setupUi(this);
    QByteArray data;
    invalid=false;
    s=slot;
    ff7 = ff7data;
    for(int i=0;i<0x200;i++){data.append(ff7->hf[s].sl_header[i]);}

    switch((quint8)data.at(2))
    {
        case 0x11://1 frame
        save_icon.setAll(data.mid(96,160));
        break;

        case 0x12://2 frames
        save_icon.setAll(data.mid(96,288), 2);
        break;

        case 0x13://3 frames
        save_icon.setAll(data.mid(96,416), 3);
        break;

        default:
        invalid = true;
    }

    if(!invalid)
    {
        ui->lbl_icon->setPixmap(save_icon.icon());
        connect(&save_icon, SIGNAL(nextIcon(QPixmap)), ui->lbl_icon, SLOT(setPixmap(QPixmap)));
    }
    ui->lbl_regionstring->setText(ff7->SG_Region_String[s].toAscii());
}

errbox::~errbox(){delete ui;}

void errbox::on_btn_prev_clicked()
{
    if(s>0){s--;this->done(1);}
    else{QMessageBox::information(this,tr("Your At Slot 1"),tr("Sorry There is no Previous Slot"));}
}

void errbox::on_btn_next_clicked()
{
    if(s<14){s++; this->done(2);}
    else{QMessageBox::information(this,tr("Your At Slot 15"),tr("Sorry There is no Next Slot"));}
}

void errbox::on_btn_export_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Raw PSX File"), ff7->SG_Region_String[s],
    tr("All Files(*)"));
    if(fileName ==""){return;}

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
    FILE *pfile; // this section is starting to work correctly!
    pfile = fopen(fileName.toAscii(),"wb");
    fwrite(ff7->hf[s].sl_header,ff7->SG_SLOT_HEADER,1,pfile); // Write Header.
    fwrite(&ff7->slot[s],ff7->SG_DATA_SIZE,1,pfile);
    fwrite(ff7->hf[s].sl_footer,ff7->SG_SLOT_FOOTER,1,pfile);
    fwrite(ff7->file_footerp,ff7->SG_FOOTER,1,pfile);
    fclose(pfile);
    QMessageBox::information(this,tr("Save Successfully"),tr("File Saved Successfully, Going Back To The Selection Dialog"));
    this->done(3);
}

void errbox::on_btn_view_clicked(){this->done(0);}
