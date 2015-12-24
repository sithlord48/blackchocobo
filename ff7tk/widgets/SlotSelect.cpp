/****************************************************************************/
//    copyright 2012 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "SlotSelect.h"

SlotSelect::SlotSelect(qreal Scale,FF7Save *data, bool showLoad,QWidget *parent):QDialog(parent)
{
	scale=Scale;
	ff7 = data;
	list_preview = new QScrollArea();
	btnNew = new QPushButton (QIcon::fromTheme(QString("document-open"),QPixmap()),tr("Load Another File"));
	connect (btnNew,SIGNAL(clicked()),this, SLOT(newFile()));
	setWindowFlags(((windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));//remove close button
	setWindowTitle(tr("Select A Slot"));
	preview_layout = new QVBoxLayout;
	frm_preview = new QFrame;
	frm_preview->setLayout(preview_layout);
	frm_preview->setContentsMargins(0,0,0,0);
	preview_layout->setContentsMargins(0,0,0,0);
	preview_layout->setSpacing(3);
	for(int i=0;i<15;i++)
	{
		preview[i] = new SlotPreview(i,scale);
		preview_layout->addWidget(preview[i]);
		setSlotPreview(i);
	}
	//frm_preview->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
	list_preview->setWidget(frm_preview);
	list_preview->setContentsMargins(0,0,0,0);
	QVBoxLayout *dialog_layout = new QVBoxLayout;
	dialog_layout->setContentsMargins(0,0,0,0);
	dialog_layout->setSpacing(2);
	dialog_layout->addWidget(list_preview);
	dialog_layout->addWidget(btnNew);
	this->showLoad(showLoad); //by defalut hide the load new save button
	this->setLayout(dialog_layout);
	setFixedWidth(preview[1]->contentsRect().size().width() +contentsMargins().left()+contentsMargins().right()+ list_preview->verticalScrollBar()->widthMM()+14*scale);
	this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
}
void SlotSelect::button_clicked(int s){this->done(s);}

void SlotSelect::remove_slot(int s)
{
	if(ff7->type()!="PC")
	{
		if((ff7->psx_block_type(s)!=FF7Save::BLOCK_MAIN) && (ff7->psx_block_type(s) != FF7Save::BLOCK_DELETED_MAIN)){return;}//only can remove Main blocks (they will clean up their sub blocks).
		int size = ff7->psx_block_size(s);
		for (int i=0;  i<size; i++)
		{
			int t=ff7->psx_block_next(s);
			ff7->clearSlot(s);
			ReIntSlot(s);
			s=t;
		}
	}
	else
	{
		ff7->clearSlot(s);
		ReIntSlot(s);
	}
}

void SlotSelect::copy_slot(int s)
{
	if(ff7->isFF7(s)){ff7->copySlot(s);}
	//don't Copy Non FF7 Slots Since we don't modify their region data
	else{/*NOT FF7 SAVE INGORE*/}
}

void SlotSelect::paste_slot(int s)
{
	if(ff7->psx_block_type(s)==FF7Save::BLOCK_MIDLINK || ff7->psx_block_type(s)==FF7Save::BLOCK_ENDLINK){return;}//Don't Overwrite parts of other saves.
	if( (!ff7->isFF7(s)) && (ff7->type()!="PC") && (ff7->psx_block_size(s)>1))
	{
		int old_s = s;
		int size = ff7->psx_block_size(s);
		for(int i=0;i<size;i++)
		{
			int t=ff7->psx_block_next(s);
			ff7->clearSlot(s);
			ReIntSlot(s);
			s=t;
		}
	   s=old_s;
	}
	ff7->pasteSlot(s);
	ReIntSlot(s);
}

void SlotSelect::ReIntSlot(int s)
{
	preview[s]->~SlotPreview();
	preview[s]= new SlotPreview(s,scale);
	preview_layout->insertWidget(s,preview[s]);
	setSlotPreview(s);
}

void SlotSelect::setSlotPreview(int s)
{
	if(((ff7->type()!="PC") && (((ff7->psx_block_type(s)==FF7Save::BLOCK_MIDLINK) || (ff7->psx_block_type(s) == FF7Save::BLOCK_ENDLINK)) || ((ff7->psx_block_type(s)==FF7Save::BLOCK_DELETED_MIDLINK) || (ff7->psx_block_type(s) == FF7Save::BLOCK_DELETED_ENDLINK)))))
	{
		preview[s]->setMode(SlotPreview::MODE_PSXGAME);
		preview[s]->setPsxIcon(ff7->slotIcon(s));
		QString Slottext;
		switch (ff7->psx_block_type(s))
		{
			case FF7Save::BLOCK_MIDLINK:   Slottext =tr("       Mid-Linked Block, Next Data Chunk @ Slot:%1").arg(QString::number(ff7->psx_block_next(s)+1)); break;
			case  FF7Save::BLOCK_DELETED_MIDLINK:  Slottext =tr("    Mid-Linked Block (Deleted), Next Data Chunk @ Slot:%1").arg(QString::number(ff7->psx_block_next(s)+1)); break;
			case FF7Save::BLOCK_ENDLINK:  Slottext =tr("      End Of Linked Blocks"); break;
			case  FF7Save::BLOCK_DELETED_ENDLINK: Slottext =tr("      End Of Linked Blocks (Deleted)"); break;
			default: Slottext = tr("ERROR"); break;
		}
		preview[s]->setLocation(Slottext);
	}

	else if(ff7->isFF7(s))
	{
		preview[s]->setMode(SlotPreview::MODE_FF7SAVE);
		//show real Dialog background.
		QImage image(2, 2, QImage::Format_ARGB32);
		image.setPixel(0, 0, ff7->dialogColorUL(s).rgb());
		image.setPixel(1, 0, ff7->dialogColorUR(s).rgb());
		image.setPixel(0, 1, ff7->dialogColorLL(s).rgb());
		image.setPixel(1, 1, ff7->dialogColorLR(s).rgb());
		QImage gradient = image.scaled(preview[s]->width(),preview[s]->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		preview[s]->setPixmap(QPixmap::fromImage(gradient));
		preview[s]->setParty(Chars.pixmap(ff7->descParty(s,0)),Chars.pixmap(ff7->descParty(s,1)),Chars.pixmap(ff7->descParty(s,2)));
		preview[s]->setLocation(ff7->descLocation(s));
		preview[s]->setName(ff7->descName(s));
		preview[s]->setLevel(ff7->descLevel(s));
		preview[s]->setGil(ff7->descGil(s));
		preview[s]->setTime((ff7->descTime(s)/3600),(ff7->descTime(s)/60 %60));
	}
	else if(ff7->region(s).isEmpty() || ff7->psx_block_type(s) ==FF7Save::BLOCK_EMPTY )
	{
		preview[s]->setMode(SlotPreview::MODE_EMPTY);
	}
	else
	{// all other psx saves.
		preview[s]->setMode(SlotPreview::MODE_PSXGAME);
		preview[s]->setPsxIcon(ff7->slotIcon(s));
		QString Slottext= ff7->psxDesc(s);
		Slottext.prepend("      ");
		if((ff7->psx_block_type(s)==FF7Save::BLOCK_DELETED_MAIN)||(ff7->psx_block_type(s)==FF7Save::BLOCK_DELETED_MIDLINK) || (ff7->psx_block_type(s)==FF7Save::BLOCK_DELETED_ENDLINK)){Slottext.append(tr("(Deleted)"));}
		Slottext.append(tr("\n\t Game Uses %1 Save Block").arg(QString::number(ff7->psx_block_size(s))));
		if(ff7->psx_block_next(s)!=0xFF){Slottext.append(tr("s; Next Data Chunk @ Slot:%1").arg(QString::number(ff7->psx_block_next(s)+1)));}
		preview[s]->setLocation(Slottext);
	}
	//more checks after this....
	//for any item
	connect(preview[s],SIGNAL(clicked(int)),this,SLOT(button_clicked(int)));
	connect(preview[s],SIGNAL(btn_remove_clicked(int)),this,SLOT(remove_slot(int)));
	connect(preview[s],SIGNAL(btn_copy_clicked(int)),this,SLOT(copy_slot(int)));
	connect(preview[s],SIGNAL(btn_paste_clicked(int)),this,SLOT(paste_slot(int)));
}

void SlotSelect::newFile(void)
{
	this->done(-1);
}

void SlotSelect::showLoad(bool show)
{
	btnNew->setVisible(show);
	if(show){this->setMinimumHeight(442);}
	else{this->setMinimumHeight(420);}
}
