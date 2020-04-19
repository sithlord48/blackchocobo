/****************************************************************************/
//    copyright 2013 - 2020 Chris Rizzitello <sithlord48@gmail.com>         //
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

#include <QDialogButtonBox>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

achievementDialog::achievementDialog(const QString &FileName, QWidget *parent) :
    QDialog(parent)
    , achievementEditor(new AchievementEditor(this))
    , buttonBox(new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, this))
    , fileName(FileName)
{
    setWindowTitle(tr("Achievement Editor"));
    setMinimumWidth(fontMetrics().horizontalAdvance(QChar('W')) * 25);
    setMinimumHeight(fontMetrics().height() * 15);
    achievementEditor->openFile(fileName);
    achievementEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(achievementEditor);
    layout->addWidget(buttonBox);
    setLayout(layout);
    buttonBox->button(QDialogButtonBox::Save)->setToolTip(tr("Close and save changes"));
    buttonBox->button(QDialogButtonBox::Cancel)->setToolTip(tr("Close and forget changes"));

    connect(buttonBox, &QDialogButtonBox::rejected, this, &achievementDialog::close);
    connect(buttonBox, &QDialogButtonBox::accepted, this, [this] {
        if (!achievementEditor->saveFile(fileName))
            QMessageBox::critical(this, tr("Failed To Save File"), QString(tr("Failed To Write File\nFile:%1")).arg(fileName));
        close();
    });

}
