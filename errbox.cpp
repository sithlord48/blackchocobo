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
	singleSlot=false;
	setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
	setWindowFlags(((this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));//remove close
	setWindowTitle(tr("Non Final Fantasy VII Slot"));
	//set up Gui
	lblRegionString = new QLabel;
	lblRegionString->setAlignment(Qt::AlignTop);

	lblIcon = new QLabel;
	lblIcon->setMinimumSize(64,64);
	lblIcon->setScaledContents(true);

	btnPrev = new QPushButton(QIcon::fromTheme("go-previous",QIcon(":/icon/prev")),"");
	btnPrev->setShortcut(QKeySequence::Back);
	btnPrev->setFixedHeight(24);

	btnView = new QPushButton(QIcon::fromTheme("window-close",QIcon(":/icon/quit")),tr("View Anyway"));
	btnView->setShortcut(QKeySequence::Close);
	btnView->setFixedHeight(24);

	btnNext = new QPushButton(QIcon::fromTheme("go-next",QIcon(":/icon/next")),"");
	btnNext->setShortcut(QKeySequence::Forward);
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

	connect(btnPrev,SIGNAL(clicked()),this,SLOT(btnPrevClicked()));
	connect(btnNext,SIGNAL(clicked()),this,SLOT(btnNextClicked()));
	connect(btnView,SIGNAL(clicked()),this,SLOT(btnViewClicked()));
	connect(btnExport,SIGNAL(clicked()),this,SLOT(btnExportClicked()));

	s=slot;
	ff7 = ff7data;
	int numslots;
	int nextslot;

	save_icon.setAll(ff7->slotIcon(s));
	lblIcon->setPixmap(save_icon.icon());
	connect(&save_icon, SIGNAL(nextIcon(QPixmap)), lblIcon, SLOT(setPixmap(QPixmap)));

	//assume NOT PC SAVE.
	QString Slottext= QString(tr("Slot:%1\n").arg(QString::number(s+1),2,QChar('0')));
	if(ff7->psx_block_type(s) != FF7Save::BLOCK_MIDLINK && ff7->psx_block_type(s) != FF7Save::BLOCK_ENDLINK && ff7->psx_block_type(s) != FF7Save::BLOCK_DELETED_MIDLINK && ff7->psx_block_type(s) !=FF7Save::BLOCK_DELETED_ENDLINK){Slottext.append(ff7->psxDesc(s));}

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
bool errbox::isSingleSlot(){return singleSlot;}
