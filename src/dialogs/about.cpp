//  SPDX-FileCopyrightText: 2010 -2020 Chris Rizzitello <sithlord48@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

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
