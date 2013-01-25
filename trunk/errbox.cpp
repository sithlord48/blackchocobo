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
#include "errbox.h"
#include <QMessageBox>
#include <QFileDialog>

errbox::errbox(QWidget *parent,FF7Save *ff7data,int slot) :QDialog(parent)
{
    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    setWindowFlags(((this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));//remove close
    setWindowTitle(tr("Non Final Fantasy VII Slot Detected"));
    //set up Gui
    lblRegionString = new QLabel;
    lblRegionString->setFixedHeight(64);
    lblRegionString->setAlignment(Qt::AlignTop);

    lblIcon = new QLabel;
    lblIcon->setFixedSize(64,64);
    lblIcon->setScaledContents(true);

    btnPrev = new QPushButton(QIcon(":/icon/prev"),tr("&Previous Slot "));
    btnPrev->setShortcut(QKeySequence::Back);
    btnPrev->setFixedHeight(24);

    btnView = new QPushButton(QIcon(":/icon/quit"),tr("View Anyway "));
    btnView->setShortcut(QKeySequence::Close);
    btnView->setFixedHeight(24);

    btnNext = new QPushButton(QIcon(":/icon/next"),tr("    &Next Slot"));
    btnNext->setShortcut(QKeySequence::Forward);
    btnNext->setLayoutDirection(Qt::RightToLeft);
    btnNext->setFixedHeight(24);

    btnExport = new QPushButton(QIcon(":/icon/psxmc"),tr("&Export As Raw PSX"));
    btnExport->setFixedHeight(24);

    QHBoxLayout *slotLayout = new QHBoxLayout;
    slotLayout->setContentsMargins(0,0,3,0);
    slotLayout->setSpacing(0);
    slotLayout->addWidget(lblIcon);
    slotLayout->addWidget(lblRegionString);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(3);
    btnLayout->addWidget(btnPrev);
    btnLayout->addWidget(btnView);
    btnLayout->addWidget(btnNext);

    QVBoxLayout * finalLayout = new QVBoxLayout;
    finalLayout->setContentsMargins(3,3,3,3);
    finalLayout->setSpacing(3);
    finalLayout->addLayout(slotLayout);
    finalLayout->addLayout(btnLayout);
    finalLayout->addWidget(btnExport);
    setLayout(finalLayout);

    setFixedHeight(finalLayout->sizeHint().height());

    connect(btnPrev,SIGNAL(clicked()),this,SLOT(btnPrevClicked()));
    connect(btnNext,SIGNAL(clicked()),this,SLOT(btnNextClicked()));
    connect(btnView,SIGNAL(clicked()),this,SLOT(btnViewClicked()));
    connect(btnExport,SIGNAL(clicked()),this,SLOT(btnExportClicked()));

    QByteArray data;
    s=slot;
    ff7 = ff7data;
    int numslots;
    int nextslot;
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

    lblIcon->setPixmap(save_icon.icon());
    connect(&save_icon, SIGNAL(nextIcon(QPixmap)), lblIcon, SLOT(setPixmap(QPixmap)));
    // Get the games desc string
    QByteArray desc;
    QTextCodec *codec = QTextCodec::codecForName(QByteArray("Shift-JIS"));
    desc = data.mid(4,64);
    int index;
    if((index = desc.indexOf('\x00')) != -1) {desc.truncate(index);}
    //assume NOT PC SAVE.

    QString Slottext= QString(tr("Slot:%1\n").arg(QString::number(s+1)));
    if(ff7->psx_block_type(s) != FF7Save::BLOCK_MIDLINK && ff7->psx_block_type(s) != FF7Save::BLOCK_ENDLINK && ff7->psx_block_type(s) != FF7Save::BLOCK_DELETED_MIDLINK && ff7->psx_block_type(s) !=FF7Save::BLOCK_DELETED_ENDLINK){Slottext.append(codec->toUnicode(desc));}

    else if((ff7->psx_block_type(s)==FF7Save::BLOCK_MIDLINK)||(ff7->psx_block_type(s)==FF7Save::BLOCK_DELETED_MIDLINK)){Slottext.append(tr("\n Mid-Linked Block "));}

    else if((ff7->psx_block_type(s)==FF7Save::BLOCK_ENDLINK)||(ff7->psx_block_type(s)==FF7Save::BLOCK_DELETED_ENDLINK)){Slottext.append(tr("\n End Of Linked Data"));}

    if((ff7->psx_block_type(s)==FF7Save::BLOCK_DELETED_MAIN)||(ff7->psx_block_type(s)==FF7Save::BLOCK_DELETED_MIDLINK)||(ff7->psx_block_type(s)==FF7Save::BLOCK_DELETED_ENDLINK)){Slottext.append(tr("(Deleted)"));}
    numslots = ff7->psx_block_size(s);
    nextslot= ff7->psx_block_next(s)+1;
    if(ff7->psx_block_type(s) != FF7Save::BLOCK_MIDLINK && ff7->psx_block_type(s) != FF7Save::BLOCK_ENDLINK && ff7->psx_block_type(s) != FF7Save::BLOCK_DELETED_MIDLINK && ff7->psx_block_type(s) !=FF7Save::BLOCK_DELETED_ENDLINK){Slottext.append(tr("\n Game Uses %1 Save Block").arg(QString::number(numslots)));}
    if(numslots !=1)
    {
            if(ff7->psx_block_next(s)!=0xFF)
            {
                if(ff7->psx_block_type(s) != FF7Save::BLOCK_MIDLINK){Slottext.append(tr("s\n   Next Data Chunk @ Slot:%1").arg(QString::number(nextslot)));}
                else{Slottext.append(tr("Next Data Chunk @ Slot:%1").arg(QString::number(nextslot)));}
            }
    }
    if(ff7->psx_block_type(s) == FF7Save::BLOCK_MIDLINK || ff7->psx_block_type(s) == FF7Save::BLOCK_ENDLINK || ff7->psx_block_type(s) ==FF7Save::BLOCK_DELETED_MIDLINK || ff7->psx_block_type(s) == FF7Save::BLOCK_DELETED_ENDLINK)
    {
        btnExport->setDisabled(1);
        btnView->setDisabled(1);
    }
    lblRegionString->setText(Slottext);

    if(s==0){btnPrev->setEnabled(false);}
    else if(s==14){btnNext->setEnabled(false);}
}

void errbox::keyPressEvent(QKeyEvent *e)
{//catch esc press and send it to view button
    if(e->key()!=Qt::Key_Escape) QDialog::keyPressEvent(e);
    else{btnView->click();}
}

void errbox::btnViewClicked(){this->done(0);}
void errbox::btnPrevClicked(){this->done(1);}
void errbox::btnNextClicked(){this->done(2);}

void errbox::btnExportClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Raw PSX File"), ff7->region(s),tr("All Files(*)"));
    if(fileName.isEmpty()){return;}
    else
    {
        if(ff7->exportPSX(s,fileName))
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
