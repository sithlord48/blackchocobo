/****************************************************************************/
//    copyright 2010-2016 Chris Rizzitello <sithlord48@gmail.com>           //
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
#include "ff7tk/data/FF7SaveInfo.h"
#include <QMessageBox>
#include <QFileDialog>

errbox::errbox(QWidget *parent,FF7Save *ff7data,int slot)
    : QDialog(parent)
    , s(slot)
    , save_icon(new SaveIcon(ff7data->slotIcon(s)))
    , ff7(ff7data)
    , btnNext(new QPushButton(QIcon::fromTheme("go-next",QIcon(":/icon/next")),QString()))
    , btnPrev(new QPushButton(QIcon::fromTheme("go-previous",QIcon(":/icon/prev")),QString()))
    , btnView(new QPushButton(QIcon::fromTheme("window-close",QIcon(":/icon/quit")),tr("View Anyway")))
    , btnExport(new QPushButton(QIcon(":/icon/psxmc"),tr("&Export As Raw PSX")))
    , lblRegionString(new QLabel)
    , lblIcon(new QLabel)
    , singleSlot(false)
{
    if (ff7data->format() == FF7SaveInfo::FORMAT::PC) {
        close();
    }
    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
	setWindowFlags(((this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));//remove close
	setWindowTitle(tr("Non Final Fantasy VII Slot"));

    connect(save_icon, SIGNAL(nextIcon(QPixmap)), this, SLOT(setIcon(QPixmap)));

	lblRegionString->setAlignment(Qt::AlignTop);
    lblIcon->setMinimumSize(64,64);
	lblIcon->setMaximumSize(128,128);
    lblIcon->setPixmap(save_icon->icon().scaled(lblIcon->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));

    btnPrev->setShortcut(QKeySequence::Back);
	btnPrev->setFixedHeight(24);
    connect(btnPrev,SIGNAL(clicked()),this,SLOT(btnPrevClicked()));
	btnView->setShortcut(QKeySequence::Close);
	btnView->setFixedHeight(24);
    connect(btnView,SIGNAL(clicked()),this,SLOT(btnViewClicked()));


	btnNext->setShortcut(QKeySequence::Forward);
	btnNext->setFixedHeight(24);
    connect(btnNext,SIGNAL(clicked()),this,SLOT(btnNextClicked()));

	btnExport->setFixedHeight(24);
    connect(btnExport,SIGNAL(clicked()),this,SLOT(btnExportClicked()));

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

    QString Slottext= QString(tr("Slot:%1\n").arg(QString::number(s+1),2,QChar('0')));
    if (ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK)
     || ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK)
     || ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK)
     || ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK)) {
        btnView->setEnabled(false);
        btnExport->setEnabled(false);
        switch (ff7->psx_block_type(s))
        {
            case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK):   Slottext.append(tr("       Mid-Linked Block")); break;
            case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK):  Slottext.append(tr("    Mid-Linked Block (Deleted)")); break;
            case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK):  Slottext.append(tr("      End Of Linked Blocks")); break;
            case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK): Slottext.append(tr("      End Of Linked Blocks (Deleted)")); break;
            default: Slottext.append(tr("ERROR")); break;
        }
    }
    Slottext.append(ff7->psxDesc(s));

    if (ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK)
     && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK)
     && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK)
     && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK)) {
        Slottext.append(tr("\n Game Uses %n Save Block(s)", nullptr, ff7->psx_block_size(s)));
    }

    if (ff7->psx_block_next(s) != 0xFF) {
        Slottext.append(tr("\n   Next Data Chunk @ Slot:%1").arg(QString::number(ff7->psx_block_next(s)+1)));
    }

    lblRegionString->setText(Slottext);
    if (s == 0 || s == 14) {
        btnPrev->setEnabled(false);
    }
}


void errbox::keyPressEvent(QKeyEvent *e)
{//catch esc press and send it to view button
    if(e->key()!=Qt::Key_Escape) {
        QDialog::keyPressEvent(e);
    } else {
        btnView->click();
    }
}

void errbox::btnViewClicked()
{
    this->done(0);
}

void errbox::btnPrevClicked()
{
    this->done(1);
}

void errbox::btnNextClicked()
{
    this->done(2);
}

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
void errbox::setSingleSlot(bool single)
{
	if(single)
	{
		btnNext->setEnabled(false);
		btnPrev->setEnabled(false);
		singleSlot= true;
	}
	else
	{
		btnNext->setEnabled(true);
		btnPrev->setEnabled(true);
		singleSlot= false;
	}
}

bool errbox::isSingleSlot()
{
    return singleSlot;
}

void errbox::setIcon(QPixmap pix)
{
	lblIcon->setPixmap(pix.scaled(lblIcon->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
}
