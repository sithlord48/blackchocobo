/****************************************************************************/
//    copyright 2012 - 2019 Chris Rizzitello <sithlord48@gmail.com>         //
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

#pragma once

#include <QtWidgets>

/** \class DoubleCheckBox
 *	\brief one text two checkable boxes
 */
class DoubleCheckBox : public QWidget
{
	Q_OBJECT
public:
	/** \brief create a new empty Double Checkbox
	 *	\param parent parent of this widget
	*/
    explicit DoubleCheckBox(QWidget *parent = nullptr);
	/** \brief create a new empty Double Checkbox
	 *	\param text Text for this checkbox
	 *	\param parent parent of this widget
	 */
    explicit DoubleCheckBox(const QString &text, QWidget *parent = nullptr);
    ~DoubleCheckBox() = default;
	/** \brief set the text displayed
	 *	\param text Text for this checkbox
	 */
    void setText(const QString& text);

	/** \brief set if a box is checked
	 *	\param box checkbox (1-2) 1 is closest to text
	 *	\param checked is this box checked?
	 */
	void setChecked(int box,bool checked);

	/** \brief check if a box has been checked .
	 *	\param box checkbox (1-2) 1 is closest to text
	 *	\return checkbox checked ?
	 */
    bool isChecked(int box);

	/** \brief Set the tooltip for a checkbox
	 *	\param box checkbox (1-2) 1 is closest to text
	 *	\param text tooltip text
	 */
    void setBoxToolTip(int box, const QString& text);

	/** \brief Set the tooltip for the widget
	 *	\param text tooltip text
	 */
    void setToolTip(const QString& text);

signals:
	/** \brief Signal: box1 has had its state changed
	 *	\param checked checked state
	 */
	void box1_toggled(bool checked);

	/** \brief Signal: box2 has had its state changed
	 *	\param checked checked state
	 */
	void box2_toggled(bool checked);
private:
    void init_display();
    QCheckBox *cb_one = nullptr;
    QCheckBox *cb_two = nullptr;
    QLabel * label = nullptr;
    qreal _scale = 1;
};
