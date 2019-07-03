/****************************************************************************/
//    copyright 2012 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
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
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
/*~~~~~~~~~~~Includes~~~~~~~~*/

#include "MetadataCreator.h"
#include "../data/FF7SaveInfo.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

MetadataCreator::MetadataCreator(QWidget *parent,FF7Save *ff7save)
    : QDialog(parent)
    , ff7(ff7save)
    , btnOk(new QPushButton(QIcon::fromTheme(QStringLiteral("dialog-ok"), style()->standardIcon(QStyle::SP_DialogOkButton)), tr("&Ok")))
    , btnCancel(new QPushButton(QIcon::fromTheme(QStringLiteral("dialog-cancel"), style()->standardIcon(QStyle::SP_DialogCancelButton)), tr("&Cancel")))
{
	initDisplay();
    for(int i=0;i<15;i++) {
        InFiles.append(QString());
    }
    setMinimumWidth(fontMetrics().width("W") * 42);
    setWindowTitle(tr("Create Cloud Save Folder"));
    setFocus();// prevents lineOutPath from Having Focus and hiding its placeholder text.
}
void MetadataCreator::initDisplay(void)
{

    btnOk->setEnabled(false);
    connect(btnOk, &QPushButton::clicked, this, &MetadataCreator::on_buttonBox_accepted);

    connect(btnCancel, &QPushButton::clicked, this, &MetadataCreator::close);

    auto btnBox = new QHBoxLayout;
    btnBox->addWidget(btnOk);
    btnBox->addWidget(btnCancel);

    auto lblOut = new QLabel(tr("Output Path:"));
    auto lineOutPath = new QLineEdit;
    lineOutPath->setPlaceholderText(tr("Folder To Write Files Into"));
    connect(lineOutPath, &QLineEdit::textChanged, this, [this] (const QString &string) {
        if (!load) {
            OutPath = string;
        }
        btnOk->setEnabled(!string.isEmpty());
    });

    auto lblUserID = new QLabel(tr("Sign With User Id"));
    auto lineUserID = new QLineEdit;
    lineUserID->setPlaceholderText(tr("Your SE Id number"));
    connect(lineUserID, &QLineEdit::textChanged, this, [this](const QString &userID){
        UserID = userID;
    });

    QHBoxLayout *userIDLayout = new QHBoxLayout;
    userIDLayout->addWidget(lblUserID);
    userIDLayout->addWidget(lineUserID);
    userIDLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum));

    auto btnOutPath = new QPushButton("...");
    connect(btnOutPath, &QPushButton::clicked, this, [this, lineOutPath, lineUserID] {
        load = true;

        QString temp = QFileDialog::getExistingDirectory(
                    this
                    ,tr("Select A Directory To Save Into")
                    , QString("%1/Square Enix/FINAL FANTASY VII/").arg(QDir::homePath()));

        if (!temp.isNull()) {
            OutPath=temp;
        }
        lineOutPath->setText(OutPath);
        lineUserID->setText(temp.remove(0, temp.lastIndexOf("_") + 1));
        load = false;
    });

	QHBoxLayout *outpathLayout = new QHBoxLayout;
	outpathLayout->addWidget(lblOut);
	outpathLayout->addWidget(lineOutPath);
	outpathLayout->addWidget(btnOutPath);

    auto SaveGroup = new QGroupBox();
    SaveGroup->setLayout(makeLineLayout());

    QVBoxLayout *FinalLayout=new QVBoxLayout;
	FinalLayout->addLayout(outpathLayout);
	FinalLayout->addLayout(userIDLayout);
	FinalLayout->addWidget(SaveGroup);
    FinalLayout->addLayout(btnBox);

	setLayout(FinalLayout);
}

void MetadataCreator::on_buttonBox_accepted()
{
    for(int i=0;i<10;i++) {
        QString OutFile = QString("%1/save0%2.ff7").arg(OutPath, QString::number(i));

        if(InFiles.at(i).isEmpty()) {
        //No File Supplied Look in OutPath to see if there is a file.
			QFile tempFile(OutFile);
            if(tempFile.exists()) {
				//If we find the file put its path in InFiles
				InFiles.replace(i,OutFile);
            } else {
                ff7->fixMetaData(OutFile, OutPath, UserID);
                continue;
            }//empty and not found
		}
        if(!ff7->loadFile(InFiles.at(i))) {
            return;
        }
        if(ff7->format()!= FF7SaveInfo::FORMAT::PC) {
            ff7->exportPC(OutFile);
        } else {
            if(!ff7->saveFile(OutFile)) {
                QMessageBox::critical(this,QString(tr("File Error")),QString(tr("Failure to write the File: %1")).arg(OutFile));
            }
		}
        ff7->fixMetaData(OutFile, OutPath, UserID);
	}
	QString achievement(QString("%1/achievement.dat").arg(OutPath));
	QFile file(achievement);
	qint64 size=0;
    if(file.exists()) {
        if(!file.open(QIODevice::ReadOnly)) {
            return;
        } else {
            size = file.size();
			file.close();
		}
	}
    if(size!=8) {
        if(!file.open(QIODevice::WriteOnly)) {
            return;
        } else {
			file.write(QByteArray("\x00\x00\x00\x00\x00\x00\x00\x00"));
			file.close();
		}
	}
    close();
}

QVBoxLayout* MetadataCreator::makeLineLayout()
{
    auto returnedLayout = new QVBoxLayout;
    for (int i = 0; i < 10; i++) {
        auto label = new QLabel(tr("Save0%1").arg(QString::number(i)));
        auto lineSave = new QLineEdit;
        auto button = new QPushButton(QStringLiteral("..."));

        if(i == 6) {
            lineSave->setPlaceholderText(tr("Add Files For each Save you want in your cloud data."));
        } else if (i == 7) {
            lineSave->setPlaceholderText(tr("You Can Use Any Format That Black Chocobo Can Open"));
        } else if (i == 8 ) {
            lineSave->setPlaceholderText(tr("Unused files will be Looked for in the Save Path"));
        } else if (i == 9) {
            lineSave->setPlaceholderText(tr("Pressing Ok Will Overwrite Any Metadata in the save path"));
        }

        connect(lineSave, &QLineEdit::textChanged, this, [this, i] (const QString &string) {
            if(!load) {
                InFiles.replace(i, string);
            }
        });

        connect(button, &QPushButton::clicked, this, [this, i, &lineSave] {
            load = true;
            QString temp = QFileDialog::getOpenFileName (
                        this
                        ,tr("Select A File To Use As Save0%1")
                            .arg(QString::number(i))
                        , QDir::homePath());
            if (ff7->loadFile(temp)) {
                InFiles.replace(i, temp);
                lineSave->setText(InFiles.at(i));
            } else {
                lineSave->clear();
            }
            load=false;
        });

        auto layout = new QHBoxLayout;
        layout->addWidget(label);
        layout->addWidget(lineSave);
        layout->addWidget(button);
        returnedLayout->addLayout(layout);
    }
    return returnedLayout;
}
