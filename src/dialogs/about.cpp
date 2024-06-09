/****************************************************************************/
//    copyright 2010-2020 Chris Rizzitello <sithlord48@gmail.com>           //
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

#include "about.h"
#include "ui_about.h"

#include <ff7tkInfo>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    setFixedSize(parent->width() * 0.5F, parent->height() * 0.7F);
    ui->pushButton->setIcon(QIcon::fromTheme("window-close"));
    ui->lbl_icon->setFixedSize(fontMetrics().height() * 6, fontMetrics().height() * 6);
    ui->lbl_icon->setPixmap(QPixmap(":/icons/common/blackchocobo"));
    ui->lbl_name->setText(QCoreApplication::applicationName());
    ui->lbl_bc_version->setText(QString(tr("Version: %1")).arg(QCoreApplication::applicationVersion()));
    ui->lbl_ff7tk_version->setText(QString(tr("ff7tk: %1")).arg(ff7tkInfo::version()));
    ui->lbl_qt_version->setText(QString(tr("Qt: %1")).arg(qVersion()));
    move(parent->x() + ((parent->width() -  width()) / 2), parent->y() + ((parent->sizeHint().height() - height()) / 2));
}

About::~About()
{
    delete ui;
}

void About::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
