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

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    ui->pushButton->setIcon(QIcon::fromTheme("window-close", style()->standardIcon(QStyle::SP_DialogCloseButton)));
    ui->lbl_icon->setFixedSize(fontMetrics().height() * 4, fontMetrics().height() * 4);
    ui->lbl_icon->setPixmap(QPixmap(":/icon/bchoco").scaled(ui->lbl_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lbl_name->setText(QCoreApplication::applicationName().toLatin1());
    ui->lbl_bc_version->setText(QString(tr("Version: %1")).arg(QCoreApplication::applicationVersion()));
    ui->lbl_qt_version->setText(QString(tr("Using Qt: %1")).arg(qVersion()));
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
