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
#ifndef PHSLISTWIDGET_H
#define PHSLISTWIDGET_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	#include <QtWidgets>
#else
	#include <QtGui>
#endif
#include "DoubleCheckBox.h"
/** \class PhsListWidget
 *	\brief Easily manage the who can be in the phs
 *
 *	Ment to be used with FF7Save
 */
class PhsListWidget : public QWidget
{
	Q_OBJECT
public:
	/** \enum Box
	 *	\brief Acces to Allow and Visible boxes without knowing their index
	 */
	enum Box {PHSALLOWED=1/**< 1*/,PHSVISIBLE=2/**< 2*/};

	explicit PhsListWidget(QWidget *parent = 0);

signals:
	/** \brief SIGNAL: The allowed box has changed its checked state
	 *	\param row the row its changed in (FF7Char::Char)
	 *	\param checked the new check state
	 */
	void allowedToggled(int row,bool checked);

	/** \brief SIGNAL: The visible box has changed its checked state
	 *	\param row the row its changed in (FF7Char::Char)
	 *	\param checked the new check state
	 */
	void visibleToggled(int row,bool checked);
public slots:

	/** \brief SLOT: set the check state for an item
	 *	\param row the row (char id is row order)
	 *	\param box the box that is being set (PhsListWidget::Box)
	 *	\param checked the new check state
	 */
	 void setChecked(int row,int box,bool checked);
private slots:
	void cb_cloud_allowedToggled(bool checked);
	void cb_cloud_visibleToggled(bool checked);
	void cb_barret_allowedToggled(bool checked);
	void cb_barret_visibleToggled(bool checked);
	void cb_tifa_allowedToggled(bool checked);
	void cb_tifa_visibleToggled(bool checked);
	void cb_aerith_allowedToggled(bool checked);
	void cb_aerith_visibleToggled(bool checked);
	void cb_red_allowedToggled(bool checked);
	void cb_red_visibleToggled(bool checked);
	void cb_yuffie_allowedToggled(bool checked);
	void cb_yuffie_visibleToggled(bool checked);
	void cb_cait_allowedToggled(bool checked);
	void cb_cait_visibleToggled(bool checked);
	void cb_vincent_allowedToggled(bool checked);
	void cb_vincent_visibleToggled(bool checked);
	void cb_cid_allowedToggled(bool checked);
	void cb_cid_visibleToggled(bool checked);

private:
	DoubleCheckBox *cb_cloud;
	DoubleCheckBox *cb_barret;
	DoubleCheckBox *cb_tifa;
	DoubleCheckBox *cb_aerith;
	DoubleCheckBox *cb_red;
	DoubleCheckBox *cb_yuffie;
	DoubleCheckBox *cb_cait;
	DoubleCheckBox *cb_vincent;
	DoubleCheckBox *cb_cid;
	QLabel *lbl_phs;
	void init_display();
	void connectAll();
	void disconnectAll();
};

#endif // PHSMENULIST_H
