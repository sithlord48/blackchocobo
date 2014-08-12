/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
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
#ifndef SLOTSELECT_H
#define SLOTSELECT_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	#include <QtWidgets>
#else
	#include <QtGui>
#endif

#include <QFrame>
#include "../data/FF7Save.h"
#include "../data/FF7Char.h"
#include "SlotPreview.h"

/**	\class SlotSelect
 *	\brief Display a preview of the contents of a PSX memory card file or FF7 PC save.
 *
 * When the dialog is run it will return the slot selected (0-14) or -1 if the load button was pushed.
 * Copy Paste and Remove are are internal so no need to worry about doing those.
 * Copy will currently only copies FF7 Saves.
 */
class SlotSelect : public QDialog
{
	Q_OBJECT
public:

	/** \brief create a new SlotSelect Dialog.
	 *	\param parent Dialogs Parent
	 *	\param data Pointer to a FF7Save object
	 *  \param showLoad show the load new file button
	 */
	explicit SlotSelect(QWidget *parent = 0,FF7Save *data=0,bool showLoad=false);
private slots:
	void button_clicked(int s);
	void remove_slot(int s);
	void copy_slot(int s);
	void paste_slot(int s);
	void newFile(void);
private:
	void setSlotPreview(int s);
	void showLoad(bool shown);
	void ReIntSlot(int s);
	QFrame *frm_preview;
	QVBoxLayout *preview_layout;
	QScrollArea *list_preview;
	SlotPreview *preview[15];
	QPushButton *btnNew;
	//Private Data
	FF7Save *ff7;
	FF7Char Chars;
};

#endif // SLOTSELECT_H
