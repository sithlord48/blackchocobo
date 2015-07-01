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

#include "DoubleCheckBox.h"
DoubleCheckBox::DoubleCheckBox(QWidget *parent) :
	QWidget(parent)
{
	init_display();
	init_connections();
}
DoubleCheckBox::DoubleCheckBox(const QString &text,QWidget *parent) :
	QWidget(parent)
{
	init_display();
	init_connections();
	setText(text);
}
void DoubleCheckBox::init_display()
{
    qreal scaleX = qApp->desktop()->logicalDpiX()/96;
    qreal scaleY = qApp->desktop()->logicalDpiY()/96;
	cb_one = new QCheckBox;
	cb_two = new QCheckBox;
	label = new QLabel;
    cb_one->setMaximumSize(22*scaleX,22*scaleY);
    cb_two->setMaximumSize(22*scaleX,22*scaleY);
	QHBoxLayout *boxLayout = new QHBoxLayout;
	boxLayout->addWidget(cb_one);
	boxLayout->addWidget(cb_two);
	boxLayout->setContentsMargins(0,0,0,0);
	boxLayout->setSpacing(2);
	QHBoxLayout *Final = new QHBoxLayout;
	Final->addWidget(label);
	Final->addLayout(boxLayout);
	Final->setContentsMargins(0,0,0,0);
	this->setLayout(Final);
}
void DoubleCheckBox::init_connections()
{
	connect(cb_one,SIGNAL(toggled(bool)),this,SLOT(cb_one_toggled(bool)));
	connect(cb_two,SIGNAL(toggled(bool)),this,SLOT(cb_two_toggled(bool)));
}
void DoubleCheckBox::setText(QString text){label->setText(text);}
void DoubleCheckBox::setChecked(int box, bool checked)
{
	switch(box)
	{
		case 1: cb_one->setChecked(checked); break;
		case 2: cb_two->setChecked(checked); break;
		default: break;
	}
}
bool DoubleCheckBox::checked(int box)
{
	switch(box)
	{
		case 1: return cb_one->isChecked(); break;
		case 2: return cb_two->isChecked(); break;
		default: return false; break;
	}
}
void DoubleCheckBox::cb_one_toggled(bool checked){emit box1_toggled(checked);}
void DoubleCheckBox::cb_two_toggled(bool checked){emit box2_toggled(checked);}

void DoubleCheckBox::setBoxToolTip(int box,QString text)
{
	switch(box)
	{
		case 1: cb_one->setToolTip(text); break;
		case 2: cb_two->setToolTip(text); break;
		default: break;
	}
}
void DoubleCheckBox::setToolTip(QString text){label->setToolTip(text);}
