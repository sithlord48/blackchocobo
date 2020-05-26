/****************************************************************************/
//    copyright 2012 -2020  Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk.                                           //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "MetadataCreator.h"

#include <QDialogButtonBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>

#include "../data/FF7Save.h"

MetadataCreator::MetadataCreator(QWidget *parent, FF7Save *ff7save)
    : QDialog(parent)
    , ff7(ff7save)
    , btnBox (new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel))
{
    initDisplay();
    for (int i = 0; i < 15; i++)
        InFiles.append(QString());

    setMinimumWidth(fontMetrics().horizontalAdvance("W") * 42);
    setWindowTitle(tr("Create Cloud Save Folder"));
    setFocus();// prevents lineOutPath from Having Focus and hiding its placeholder text.
}
void MetadataCreator::initDisplay(void)
{

    connect(btnBox, &QDialogButtonBox::accepted, this, &MetadataCreator::accepted);
    connect(btnBox, &QDialogButtonBox::rejected, this, &MetadataCreator::close);
    
    btnBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    auto lblOut = new QLabel(tr("Output Path:"));
    auto lineOutPath = new QLineEdit;
    lineOutPath->setPlaceholderText(tr("Folder To Write Files Into"));
    connect(lineOutPath, &QLineEdit::textChanged, this, [this](const QString & string) {
        if (!load)
            OutPath = string;
        btnBox->button(QDialogButtonBox::Ok)->setEnabled(!string.isEmpty());
    });

    auto lblUserID = new QLabel(tr("Sign With User Id"));
    auto lineUserID = new QLineEdit;
    lineUserID->setPlaceholderText(tr("Your SE Id number"));
    connect(lineUserID, &QLineEdit::textChanged, this, [this](const QString & userID) {
        UserID = userID;
    });

    QHBoxLayout *userIDLayout = new QHBoxLayout;
    userIDLayout->addWidget(lblUserID);
    userIDLayout->addWidget(lineUserID);
    userIDLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    auto btnOutPath = new QPushButton("...");
    connect(btnOutPath, &QPushButton::clicked, this, [this, lineOutPath, lineUserID] {
        load = true;
        QString temp = getExistingDirectory(parentWidget(), tr("Select A Directory To Save Into"), QString("%1/Square Enix/FINAL FANTASY VII/").arg(QDir::homePath()));

        if (temp.isEmpty())
            return;

        OutPath = temp;
        lineOutPath->setText(OutPath);
        if (temp.contains(QStringLiteral("_")))
            lineUserID->setText(temp.remove(0, temp.lastIndexOf("_") + 1));
        load = false;
    });

    QHBoxLayout *outpathLayout = new QHBoxLayout;
    outpathLayout->addWidget(lblOut);
    outpathLayout->addWidget(lineOutPath);
    outpathLayout->addWidget(btnOutPath);

    auto SaveGroup = new QGroupBox();
    SaveGroup->setLayout(makeLineLayout());

    QVBoxLayout *FinalLayout = new QVBoxLayout;
    FinalLayout->addLayout(outpathLayout);
    FinalLayout->addLayout(userIDLayout);
    FinalLayout->addWidget(SaveGroup);
    FinalLayout->addWidget(btnBox);

    setLayout(FinalLayout);
}

void MetadataCreator::accepted()
{
    for (int i = 0; i < 10; i++) {
        QString OutFile = QString("%1/save0%2.ff7").arg(OutPath, QString::number(i));

        if (InFiles.at(i).isEmpty()) {
            //No File Supplied Look in OutPath to see if there is a file.
            QFile tempFile(OutFile);
            if (tempFile.exists()) {
                //If we find the file put its path in InFiles
                InFiles.replace(i, OutFile);
            } else {
                ff7->fixMetaData(OutFile, OutPath, UserID);
                continue;
            }//empty and not found
        }
        if (!ff7->loadFile(InFiles.at(i)))
            return;
        if (ff7->format() != FF7SaveInfo::FORMAT::PC)
            ff7->exportPC(OutFile);
        else if (!ff7->saveFile(OutFile))
                QMessageBox::critical(this, QString(tr("File Error")), QString(tr("Failure to write the File: %1")).arg(OutFile));
        ff7->fixMetaData(OutFile, OutPath, UserID);
    }
    QString achievement(QString("%1/achievement.dat").arg(OutPath));
    QFile file(achievement);
    qint64 size = 0;
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly))
            return;
        size = file.size();
        file.close();
    }
    if (size != 8) {
        if (!file.open(QIODevice::WriteOnly))
            return;
        file.write(QByteArray("\x00\x00\x00\x00\x00\x00\x00\x00"));
        file.close();
    }
    close();
}

QVBoxLayout *MetadataCreator::makeLineLayout()
{
    auto returnedLayout = new QVBoxLayout;
    for (int i = 0; i < 10; i++) {
        auto label = new QLabel(tr("Save0%1").arg(QString::number(i)));
        auto lineSave = new QLineEdit;
        auto button = new QPushButton(QStringLiteral("..."));

        if (i == 6)
            lineSave->setPlaceholderText(tr("Add Files For each Save you want in your cloud data."));
        else if (i == 7)
            lineSave->setPlaceholderText(tr("You Can Use Any Format That Black Chocobo Can Open"));
        else if (i == 8)
            lineSave->setPlaceholderText(tr("Unused files will be Looked for in the Save Path"));
        else if (i == 9)
            lineSave->setPlaceholderText(tr("Pressing Ok Will Overwrite Any Metadata in the save path"));

        connect(lineSave, &QLineEdit::textChanged, this, [this, i](const QString & string) {
            if (!load)
                InFiles.replace(i, string);
        });

        connect(button, &QPushButton::clicked, this, [this, i, lineSave] {
            load = true;
            QString path = QFileInfo(lineSave->text()).path().isEmpty() ? QDir::homePath() : QFileInfo(lineSave->text()).path();
            QString temp = QFile(lineSave->text()).fileName();
            temp = getOpenFileName(parentWidget(), tr("Select A File To Use As Save0%1").arg(QString::number(i)), QDir::homePath(), FF7SaveInfo::instance()->knownTypesFilter(), temp);
            if (ff7->loadFile(temp)) {
                InFiles.replace(i, temp);
                lineSave->setText(InFiles.at(i));
            }
            load = false;
        });

        auto layout = new QHBoxLayout;
        layout->addWidget(label);
        layout->addWidget(lineSave);
        layout->addWidget(button);
        returnedLayout->addLayout(layout);
    }
    return returnedLayout;
}

QString MetadataCreator::getOpenFileName(QWidget  *parent, const QString &title, const QString &path , const QString &nameFilters, const QString &initSelection)
{
    QFileDialog dialog(parent, title, path.isEmpty() ? QDir::homePath() : path, nameFilters);
    int dialogWidth = int(parent->geometry().width() * 0.80);
    int dialogHeight = int (parent->geometry().height() * 0.80);
    int fmw = dialog.fontMetrics().height();
    QSize iconSize = QSize(fmw, fmw);
    for(QAbstractButton * btn: dialog.findChildren<QAbstractButton*>(QString(), Qt::FindChildrenRecursively))
        btn->setIconSize(iconSize);
    dialog.setGeometry(parent->geometry().x() + ((parent->geometry().width() - dialogWidth) / 2), parent->geometry().y() + ((parent->geometry().height() - dialogHeight) /2), dialogWidth, dialogHeight);
    dialog.setLabelText(QFileDialog::LookIn, tr("Places"));
    QString fileName = initSelection;
    if (!fileName.isEmpty())
        dialog.selectFile(fileName);

    if(dialog.exec() == QFileDialog::Accepted)
        return dialog.selectedFiles().first();
    return QString();
}

QString MetadataCreator::getExistingDirectory(QWidget *parent, const QString &title, const QString &path, const QString &initSelection)
{
    QRect mainRect = parent->geometry();
    int dialogWidth = int(mainRect.width() * 0.80);
    int dialogHeight = int (mainRect.height() * 0.80);
    QFileDialog dialog(parent, title, path.isEmpty() ? QDir::homePath() : path, initSelection);
    int fmw = dialog.fontMetrics().height();
    QSize iconSize = QSize(fmw, fmw);
    for(QAbstractButton * btn: dialog.findChildren<QAbstractButton*>(QString(), Qt::FindChildrenRecursively))
        btn->setIconSize(iconSize);
    dialog.setGeometry(mainRect.x() + ((mainRect.width() - dialogWidth) / 2), mainRect.y() + ((mainRect.height() - dialogHeight) /2), dialogWidth, dialogHeight);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setFilter(QDir::Dirs);
    QString fileName = initSelection;
    if (!fileName.isEmpty())
        dialog.selectFile(fileName);
    dialog.setLabelText(QFileDialog::LookIn, tr("Places"));

    if(dialog.exec() == QFileDialog::Accepted)
        return dialog.selectedFiles().first();
    return QString();
}
