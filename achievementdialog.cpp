/****************************************************************************/
//    copyright 2013 - 2019 Chris Rizzitello <sithlord48@gmail.com>         //
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
#include "achievementdialog.h"

achievementDialog::achievementDialog(const QString &FileName, QWidget *parent) :
    QDialog(parent)
    , achEditor(new AchievementEditor)
    , btnSave(new QPushButton(QIcon::fromTheme("document-save", QIcon(":/icon/save")), tr("  &Save")))
    , btnNo(new QPushButton(QIcon::fromTheme("window-close", QIcon(":/icon/quit")), tr("  &Cancel")))
    , fileName(FileName)
{
    setWindowTitle(tr("Achievement Editor"));
    achEditor->openFile(fileName);
    achEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->setSpacing(2);
    btnLayout->addWidget(btnSave);
    btnLayout->addWidget(btnNo);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(achEditor);
    layout->addLayout(btnLayout);
    setLayout(layout);
    connect(btnSave, &QPushButton::clicked, this, &achievementDialog::accept);
    connect(btnNo, &QPushButton::clicked, this, &achievementDialog::close);
}
void achievementDialog::accept(void)
{
    if (fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, tr("Save As"), QDir::homePath(), tr("Dat Files (*.dat)"));
    }
    if (fileName.isEmpty()) {
        return;
    } else {
        if (achEditor->saveFile(fileName)) {
            this->close();
        } else {
            QMessageBox::critical(this, tr("Failed To Save File"), QString(tr("Failed To Write File\nFile:%1")).arg(fileName));
        }
    }
}
