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

#include "errbox.h"
#include "ui_errbox.h"

/*~~~~~GLOBALS~~~~~~*/
errbox::errbox(QWidget *parent,FF7Save *ff7data,int slot) :
    QDialog(parent),
    ui(new Ui::errbox)
{
    ui->setupUi(this);
    QByteArray data;
    s=slot;
    ff7 = ff7data;
    int numslots;
    int nextslot;
    this->setWindowFlags(((this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));//remove close
    data= ff7->slot_header(s);
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

        default: //Black Box
        QByteArray tmp;
        tmp.fill(00,0x200);
        save_icon.setAll(tmp);
        break;
    }

    ui->lbl_icon->setPixmap(save_icon.icon());
    if(QT_VERSION<0x050000)
    {//QT4 Style Connection
        connect(&save_icon, SIGNAL(nextIcon(QPixmap)), ui->lbl_icon, SLOT(setPixmap(QPixmap)));
    }
    else
    {//QT5 Style Connection
    //    connect(&save_icon::nextIcon(QPixmap), ui->lbl_icon::setPixmap(QPixmap));
    }
    // Get the games desc string
    QByteArray desc;
    QTextCodec *codec = QTextCodec::codecForName(QByteArray("Shift-JIS"));
    desc = data.mid(4,64);
    int index;
    if((index = desc.indexOf('\x00')) != -1) {desc.truncate(index);}
    //assume NOT PC SAVE.

    QString Slottext;
    if(ff7->psx_block_type(s) != 0x52 && ff7->psx_block_type(s) != 0x53 && ff7->psx_block_type(s) != 0xA2 && ff7->psx_block_type(s) !=0xA3){Slottext= codec->toUnicode(desc);}

    else if((ff7->psx_block_type(s)==0x52)||(ff7->psx_block_type(s)==0xA2)){Slottext = tr("Mid-Linked Block ");}

    else if((ff7->psx_block_type(s)==0x53)||(ff7->psx_block_type(s)==0xA3)){Slottext = tr("End Of Linked Data");}

    if((ff7->psx_block_type(s)==0xA1)||(ff7->psx_block_type(s)==0xA2)||(ff7->psx_block_type(s)==0xA3)){Slottext.append(tr("(Deleted)"));}
    numslots = ff7->psx_block_size(s);
    nextslot= ff7->psx_block_next(s)+1;
    if(ff7->psx_block_type(s) != 0x52 && ff7->psx_block_type(s) != 0x53 && ff7->psx_block_type(s) != 0xA2 && ff7->psx_block_type(s) !=0xA3){Slottext.append(tr("\n Game Uses %1 Save Block").arg(QString::number(numslots)));}
    if(numslots !=1)
    {
            if(ff7->psx_block_next(s)!=0xFF)
            {
                if(ff7->psx_block_type(s) != 0x52){Slottext.append(tr("s; Next Data Chunk @ Slot:%1").arg(QString::number(nextslot)));}
                else{Slottext.append(tr("Next Data Chunk @ Slot:%1").arg(QString::number(nextslot)));}
            }
    }
    if(ff7->psx_block_type(s) == 0x52 || ff7->psx_block_type(s) == 0x53 || ff7->psx_block_type(s) ==0xA2 || ff7->psx_block_type(s) == 0xA3 || numslots !=1)
    {
        ui->btn_export->setDisabled(1);
        ui->btn_view->setDisabled(1);
    }
    ui->lbl_regionstring->setText(Slottext);
}

void errbox::keyPressEvent(QKeyEvent *e)
{//catch esc press and send it to view button
    if(e->key()!=Qt::Key_Escape) QDialog::keyPressEvent(e);
    else{ui->btn_view->click();}
}
errbox::~errbox(){delete ui;}

void errbox::on_btn_prev_clicked()
{
    if(s>0){this->done(1);}
    else{QMessageBox::information(this,tr("Your At Slot 1"),tr("Sorry There is no Previous Slot"));}
}

void errbox::on_btn_next_clicked()
{
    if(s<14){this->done(2);}
    else{QMessageBox::information(this,tr("Your At Slot 15"),tr("Sorry There is no Next Slot"));}
}

void errbox::on_btn_export_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Raw PSX File"), ff7->region(s),
    tr("All Files(*)"));
    if(fileName.isEmpty()){return;}
    else
    {
        if(ff7->Export_PSX(s,fileName))
        {
            QMessageBox::information(this,tr("Save Successfully"),tr("File Saved Successfully, Going Back To The Selection Dialog"));
            this->done(3);
        }
        else
        {
            QMessageBox::information(this,tr("Save Error"),tr("Error On File Save, Going Back To The Selection Dialog"));
            this->done(3);
        }
    }
}

void errbox::on_btn_view_clicked(){this->done(0);}
