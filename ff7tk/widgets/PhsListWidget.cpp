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
#include "PhsListWidget.h"
PhsListWidget::PhsListWidget(QWidget *parent) :
	QWidget(parent)
{
	init_display();
	connectAll();
}
void PhsListWidget::init_display()
{
	lbl_phs = new QLabel(QString(tr("PHS Manager")));
	lbl_phs->setStyleSheet(QString("text-decoration: underline;"));
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(lbl_phs);
	layout->setSpacing(3);
	layout->setContentsMargins(0,0,0,0);
	cb_cloud= new DoubleCheckBox(QString(tr("Cloud")));
	cb_cloud->setBoxToolTip(1,QString(tr("Allowed")));
	cb_cloud->setBoxToolTip(2,QString(tr("Visible")));
	layout->addWidget(cb_cloud);

	cb_barret= new DoubleCheckBox(QString(tr("Barret")));
	cb_barret->setBoxToolTip(1,QString(tr("Allowed")));
	cb_barret->setBoxToolTip(2,QString(tr("Visible")));
	layout->addWidget(cb_barret);

	cb_tifa= new DoubleCheckBox(QString(tr("Tifa")));
	cb_tifa->setBoxToolTip(1,QString(tr("Allowed")));
	cb_tifa->setBoxToolTip(2,QString(tr("Visible")));
	layout->addWidget(cb_tifa);

	cb_aerith= new DoubleCheckBox(QString(tr("Aerith")));
	cb_aerith->setBoxToolTip(1,QString(tr("Allowed")));
	cb_aerith->setBoxToolTip(2,QString(tr("Visible")));
	layout->addWidget(cb_aerith);

	cb_red= new DoubleCheckBox(QString(tr("Red XIII")));
	cb_red->setBoxToolTip(1,QString(tr("Allowed")));
	cb_red->setBoxToolTip(2,QString(tr("Visible")));
	layout->addWidget(cb_red);

	cb_yuffie= new DoubleCheckBox(QString(tr("Yuffie")));
	cb_yuffie->setBoxToolTip(1,QString(tr("Allowed")));
	cb_yuffie->setBoxToolTip(2,QString(tr("Visible")));
	layout->addWidget(cb_yuffie);

	cb_cait= new DoubleCheckBox(QString(tr("Cait Sith")));
	cb_cait->setBoxToolTip(1,QString(tr("Allowed")));
	cb_cait->setBoxToolTip(2,QString(tr("Visible")));
	layout->addWidget(cb_cait);

	cb_vincent= new DoubleCheckBox(QString(tr("Vincent")));
	cb_vincent->setBoxToolTip(1,QString(tr("Allowed")));
	cb_vincent->setBoxToolTip(2,QString(tr("Visible")));
	layout->addWidget(cb_vincent);

	cb_cid= new DoubleCheckBox(QString(tr("Cid")));
	cb_cid->setBoxToolTip(1,QString(tr("Allowed")));
	cb_cid->setBoxToolTip(2,QString(tr("Visible")));
	layout->addWidget(cb_cid);

	this->setLayout(layout);
	this->adjustSize();
}

void PhsListWidget::setChecked(int row, int box, bool checked)
{
	disconnectAll();
	switch (row)
	{
		case 0: cb_cloud->setChecked(box,checked); break;
		case 1: cb_barret->setChecked(box,checked); break;
		case 2: cb_tifa->setChecked(box,checked); break;
		case 3: cb_aerith->setChecked(box,checked); break;
		case 4: cb_red->setChecked(box,checked); break;
		case 5: cb_yuffie->setChecked(box,checked); break;
		case 6: cb_cait->setChecked(box,checked); break;
		case 7: cb_vincent->setChecked(box,checked); break;
		case 8: cb_cid->setChecked(box,checked); break;
	};
	connectAll( );
}

void PhsListWidget::cb_cloud_allowedToggled(bool checked){emit(allowedToggled(0,checked));}
void PhsListWidget::cb_cloud_visibleToggled(bool checked){emit(visibleToggled(0,checked));}
void PhsListWidget::cb_barret_allowedToggled(bool checked){emit(allowedToggled(1,checked));}
void PhsListWidget::cb_barret_visibleToggled(bool checked){emit(visibleToggled(1,checked));}
void PhsListWidget::cb_tifa_allowedToggled(bool checked){emit(allowedToggled(2,checked));}
void PhsListWidget::cb_tifa_visibleToggled(bool checked){emit(visibleToggled(2,checked));}
void PhsListWidget::cb_aerith_allowedToggled(bool checked){emit(allowedToggled(3,checked));}
void PhsListWidget::cb_aerith_visibleToggled(bool checked){emit(visibleToggled(3,checked));}
void PhsListWidget::cb_red_allowedToggled(bool checked){emit(allowedToggled(4,checked));}
void PhsListWidget::cb_red_visibleToggled(bool checked){emit(visibleToggled(4,checked));}
void PhsListWidget::cb_yuffie_allowedToggled(bool checked){emit(allowedToggled(5,checked));}
void PhsListWidget::cb_yuffie_visibleToggled(bool checked){emit(visibleToggled(5,checked));}
void PhsListWidget::cb_cait_allowedToggled(bool checked){emit(allowedToggled(6,checked));}
void PhsListWidget::cb_cait_visibleToggled(bool checked){emit(visibleToggled(6,checked));}
void PhsListWidget::cb_vincent_allowedToggled(bool checked){emit(allowedToggled(7,checked));}
void PhsListWidget::cb_vincent_visibleToggled(bool checked){emit(visibleToggled(7,checked));}
void PhsListWidget::cb_cid_allowedToggled(bool checked){emit(allowedToggled(8,checked));}
void PhsListWidget::cb_cid_visibleToggled(bool checked){emit(visibleToggled(8,checked));}

void PhsListWidget::connectAll()
{
	connect(cb_cloud,SIGNAL(box1_toggled(bool)),this,SLOT(cb_cloud_allowedToggled(bool)));
	connect(cb_cloud,SIGNAL(box2_toggled(bool)),this,SLOT(cb_cloud_visibleToggled(bool)));
	connect(cb_barret,SIGNAL(box1_toggled(bool)),this,SLOT(cb_barret_allowedToggled(bool)));
	connect(cb_barret,SIGNAL(box2_toggled(bool)),this,SLOT(cb_barret_visibleToggled(bool)));
	connect(cb_tifa,SIGNAL(box1_toggled(bool)),this,SLOT(cb_tifa_allowedToggled(bool)));
	connect(cb_tifa,SIGNAL(box2_toggled(bool)),this,SLOT(cb_tifa_visibleToggled(bool)));
	connect(cb_aerith,SIGNAL(box1_toggled(bool)),this,SLOT(cb_aerith_allowedToggled(bool)));
	connect(cb_aerith,SIGNAL(box2_toggled(bool)),this,SLOT(cb_aerith_visibleToggled(bool)));
	connect(cb_red,SIGNAL(box1_toggled(bool)),this,SLOT(cb_red_allowedToggled(bool)));
	connect(cb_red,SIGNAL(box2_toggled(bool)),this,SLOT(cb_red_visibleToggled(bool)));
	connect(cb_yuffie,SIGNAL(box1_toggled(bool)),this,SLOT(cb_yuffie_allowedToggled(bool)));
	connect(cb_yuffie,SIGNAL(box2_toggled(bool)),this,SLOT(cb_yuffie_visibleToggled(bool)));
	connect(cb_cait,SIGNAL(box1_toggled(bool)),this,SLOT(cb_cait_allowedToggled(bool)));
	connect(cb_cait,SIGNAL(box2_toggled(bool)),this,SLOT(cb_cait_visibleToggled(bool)));
	connect(cb_vincent,SIGNAL(box1_toggled(bool)),this,SLOT(cb_vincent_allowedToggled(bool)));
	connect(cb_vincent,SIGNAL(box2_toggled(bool)),this,SLOT(cb_vincent_visibleToggled(bool)));
	connect(cb_cid,SIGNAL(box1_toggled(bool)),this,SLOT(cb_cid_allowedToggled(bool)));
	connect(cb_cid,SIGNAL(box2_toggled(bool)),this,SLOT(cb_cid_visibleToggled(bool)));
}
void PhsListWidget::disconnectAll()
{
	disconnect(cb_cloud,SIGNAL(box1_toggled(bool)),this,SLOT(cb_cloud_allowedToggled(bool)));
	disconnect(cb_cloud,SIGNAL(box2_toggled(bool)),this,SLOT(cb_cloud_visibleToggled(bool)));
	disconnect(cb_barret,SIGNAL(box1_toggled(bool)),this,SLOT(cb_barret_allowedToggled(bool)));
	disconnect(cb_barret,SIGNAL(box2_toggled(bool)),this,SLOT(cb_barret_visibleToggled(bool)));
	disconnect(cb_tifa,SIGNAL(box1_toggled(bool)),this,SLOT(cb_tifa_allowedToggled(bool)));
	disconnect(cb_tifa,SIGNAL(box2_toggled(bool)),this,SLOT(cb_tifa_visibleToggled(bool)));
	disconnect(cb_aerith,SIGNAL(box1_toggled(bool)),this,SLOT(cb_aerith_allowedToggled(bool)));
	disconnect(cb_aerith,SIGNAL(box2_toggled(bool)),this,SLOT(cb_aerith_visibleToggled(bool)));
	disconnect(cb_red,SIGNAL(box1_toggled(bool)),this,SLOT(cb_red_allowedToggled(bool)));
	disconnect(cb_red,SIGNAL(box2_toggled(bool)),this,SLOT(cb_red_visibleToggled(bool)));
	disconnect(cb_yuffie,SIGNAL(box1_toggled(bool)),this,SLOT(cb_yuffie_allowedToggled(bool)));
	disconnect(cb_yuffie,SIGNAL(box2_toggled(bool)),this,SLOT(cb_yuffie_visibleToggled(bool)));
	disconnect(cb_cait,SIGNAL(box1_toggled(bool)),this,SLOT(cb_cait_allowedToggled(bool)));
	disconnect(cb_cait,SIGNAL(box2_toggled(bool)),this,SLOT(cb_cait_visibleToggled(bool)));
	disconnect(cb_vincent,SIGNAL(box1_toggled(bool)),this,SLOT(cb_vincent_allowedToggled(bool)));
	disconnect(cb_vincent,SIGNAL(box2_toggled(bool)),this,SLOT(cb_vincent_visibleToggled(bool)));
	disconnect(cb_cid,SIGNAL(box1_toggled(bool)),this,SLOT(cb_cid_allowedToggled(bool)));
	disconnect(cb_cid,SIGNAL(box2_toggled(bool)),this,SLOT(cb_cid_visibleToggled(bool)));
}
