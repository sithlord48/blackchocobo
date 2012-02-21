/****************************************************************************/
//    copyright 2010-2012 Chris Rizzitello <sithlord48@gmail.com>           //
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

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    ui->lbl_svn_lbl->setHidden(1);
    QString svn_version=VER;
    if(!svn_version.isEmpty()){ui->lbl_svn_lbl->setHidden(0); ui->lbl_svn_version->setText(svn_version);}
    ui->lbl_name->setText(QCoreApplication::applicationName().toAscii());
    ui->lbl_bc_version->setText(QCoreApplication::applicationVersion().toAscii());
    ui->lbl_qt_version->setText(qVersion());
}

about::~about()
{
    delete ui;
}

void about::changeEvent(QEvent *e)
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

void about::on_pushButton_clicked()
{
    this->close();
}

