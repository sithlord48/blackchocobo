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
#ifndef SLOTPREVIEW_H
#define SLOTPREVIEW_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	#include <QtWidgets>
#else
	#include <QtGui>
#endif

//set path to save icon class
#include "../data/SaveIcon.h"

/** \class SlotPreview
 *  \brief Preview a Single Slot on a Psx memory card or FF7 Save file.
 *
 * Currently will display the "description" of FF7 Save or a preview of what psx save is in that slot. More games could be added by extending the modes
 */
class SlotPreview : public QLabel
{
	Q_OBJECT
public:
	/** \enum MODE */
	enum MODE{MODE_EMPTY,/**< \brief Empty Slot*/ MODE_PSXGAME, /**< \brief PSX Game or linked block */ MODE_FF7SAVE /**< \brief FF7 Save in slot*/ };
	SlotPreview(int index=0,qreal Scale=1,QWidget *parent = 0);
	int index(void);
	void setParty(QPixmap p1,QPixmap p2,QPixmap p3);
	void setParty(QString p1_style,QString p2_style,QString p3_style);
	void setName(QString);
	void setLevel(int);
	void setLocation(QString);
	void setGil(int);
	void setTime(int hour,int min);
	void setPsxIcon(QByteArray icon_data,quint8 frames=1);
	void setPsxIcon(QList<QByteArray> icon_data);
	void setMode(int mode);

private slots:
	void setIndex(int index);
	//raw pix map for labels
	void set_Party1(QPixmap);
	void set_Party2(QPixmap);
	void set_Party3(QPixmap);
	void set_Party1(QString style);
	void set_Party2(QString style);
	void set_Party3(QString style);
	void removed(void);
	void copy(void);
	void paste(void);
	void set_ff7_save(void);
	void set_empty(void);
	void set_psx_game(void);

private:
	void init_display(void);
	QLabel *party1;
	QLabel *party2;
	QLabel *party3;
	QLabel *name;
	QLabel *lbl_Slot;
	QLabel *lbl_time;
	QLabel *lbl_level;
	QLabel *location;
	QLabel *lbl_gil;
	QPushButton *btn_copy;
	QPushButton *btn_paste;
	QPushButton *btn_remove;
	SaveIcon *icon;
	QHBoxLayout  * btnLayout;
	QVBoxLayout * Final;
	QVBoxLayout *top_layout;
	bool not_pc;
	qreal scale;
protected:
	void mousePressEvent(QMouseEvent *ev);
signals:
	void clicked(int); /**< \brief Signal: User Clicked on preview . \return index number */
	void btn_remove_clicked(int); /**< \brief Signal: User Clicked on remove . \return index number */
	void btn_copy_clicked(int); /**< \brief Signal: User Clicked on copy . \return index number */
	void btn_paste_clicked(int); /**< \brief Signal: User Clicked on paste . \return index number */
};

#endif
