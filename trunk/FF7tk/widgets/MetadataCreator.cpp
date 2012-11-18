/****************************************************************************/
//    copyright 2012 Chris Rizzitello <sithlord48@gmail.com>           //
//                                                                          //
//    This file is part of FF7tk.                                   //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
/*~~~~~~~~~~~Includes~~~~~~~~*/

#include "MetadataCreator.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

MetadataCreator::MetadataCreator(QWidget *parent,FF7Save *ff7save) :    QDialog(parent)
{
    initDisplay();
    initConnections();
    for(int i=0;i<15;i++){InFiles.append(QString(""));}
     ff7 = ff7save;
     buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
     this->setWindowTitle(tr("Create Cloud Save Folder"));
     this->setFocus();// prevents lineOutPath from Having Focus and hiding its placeholder text.
}
void MetadataCreator::initDisplay(void)
{
    this->setMinimumSize(458,438);
    lblOut= new QLabel(tr("Output Path:"));
    lineOutPath = new QLineEdit;
    lineOutPath->setPlaceholderText(tr("Folder To Write Files Into"));

    btnOutPath = new QPushButton("...");

    QHBoxLayout *outpathLayout = new QHBoxLayout;
    outpathLayout->addWidget(lblOut);
    outpathLayout->addWidget(lineOutPath);
    outpathLayout->addWidget(btnOutPath);

    lblUserID=new QLabel(tr("Sign With User Id"));
    lineUserID = new QLineEdit;
    lineUserID->setPlaceholderText(tr("Your SE Id number"));
    IDSpacer= new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);

    QHBoxLayout *userIDLayout = new QHBoxLayout;
    userIDLayout->addWidget(lblUserID);
    userIDLayout->addWidget(lineUserID);
    userIDLayout->addSpacerItem(IDSpacer);

    lblSave00=new QLabel(tr("Save00"));
    lineSave00= new QLineEdit;
    btnSave00= new QPushButton("...");

    QHBoxLayout *savegroup00 = new QHBoxLayout;
    savegroup00->addWidget(lblSave00);
    savegroup00->addWidget(lineSave00);
    savegroup00->addWidget(btnSave00);

    lblSave01=new QLabel(tr("Save01"));
    lineSave01= new QLineEdit;
    btnSave01= new QPushButton("...");

    QHBoxLayout *savegroup01 = new QHBoxLayout;
    savegroup01->addWidget(lblSave01);
    savegroup01->addWidget(lineSave01);
    savegroup01->addWidget(btnSave01);

    lblSave02=new QLabel(tr("Save02"));
    lineSave02= new QLineEdit;
    btnSave02= new QPushButton("...");

    QHBoxLayout *savegroup02 = new QHBoxLayout;
    savegroup02->addWidget(lblSave02);
    savegroup02->addWidget(lineSave02);
    savegroup02->addWidget(btnSave02);

    lblSave03=new QLabel(tr("Save03"));
    lineSave03= new QLineEdit;
    btnSave03= new QPushButton("...");

    QHBoxLayout *savegroup03 = new QHBoxLayout;
    savegroup03->addWidget(lblSave03);
    savegroup03->addWidget(lineSave03);
    savegroup03->addWidget(btnSave03);

    lblSave04=new QLabel(tr("Save04"));
    lineSave04= new QLineEdit;
    btnSave04= new QPushButton("...");

    QHBoxLayout *savegroup04 = new QHBoxLayout;
    savegroup04->addWidget(lblSave04);
    savegroup04->addWidget(lineSave04);
    savegroup04->addWidget(btnSave04);

    lblSave05=new QLabel(tr("Save05"));
    lineSave05= new QLineEdit;
    btnSave05= new QPushButton("...");

    QHBoxLayout *savegroup05 = new QHBoxLayout;
    savegroup05->addWidget(lblSave05);
    savegroup05->addWidget(lineSave05);
    savegroup05->addWidget(btnSave05);

    lblSave06=new QLabel(tr("Save06"));
    lineSave06= new QLineEdit;
    lineSave06->setPlaceholderText(tr("Add Files For each Save you want in your cloud data."));
    btnSave06= new QPushButton("...");

    QHBoxLayout *savegroup06 = new QHBoxLayout;
    savegroup06->addWidget(lblSave06);
    savegroup06->addWidget(lineSave06);
    savegroup06->addWidget(btnSave06);

    lblSave07=new QLabel(tr("Save07"));
    lineSave07= new QLineEdit;
    lineSave07->setPlaceholderText(tr("You Can Use Any Format That Black Chocobo Can Open"));
    btnSave07= new QPushButton("...");

    QHBoxLayout *savegroup07 = new QHBoxLayout;
    savegroup07->addWidget(lblSave07);
    savegroup07->addWidget(lineSave07);
    savegroup07->addWidget(btnSave07);

    lblSave08=new QLabel(tr("Save08"));
    lineSave08= new QLineEdit;
    lineSave08->setPlaceholderText(tr("Unused files will be Looked for in the Save Path"));
    btnSave08= new QPushButton("...");

    QHBoxLayout *savegroup08 = new QHBoxLayout;
    savegroup08->addWidget(lblSave08);
    savegroup08->addWidget(lineSave08);
    savegroup08->addWidget(btnSave08);

    lblSave09=new QLabel(tr("Save09"));
    lineSave09= new QLineEdit;
    lineSave09->setPlaceholderText(tr("Pressing Ok WIll Overwrite Any Metadata in the save path"));
    btnSave09= new QPushButton("...");

    QHBoxLayout *savegroup09 = new QHBoxLayout;
    savegroup09->addWidget(lblSave09);
    savegroup09->addWidget(lineSave09);
    savegroup09->addWidget(btnSave09);

    QVBoxLayout *SaveGroupLayout = new QVBoxLayout;
    SaveGroupLayout->addLayout(savegroup00);
    SaveGroupLayout->addLayout(savegroup01);
    SaveGroupLayout->addLayout(savegroup02);
    SaveGroupLayout->addLayout(savegroup03);
    SaveGroupLayout->addLayout(savegroup04);
    SaveGroupLayout->addLayout(savegroup05);
    SaveGroupLayout->addLayout(savegroup06);
    SaveGroupLayout->addLayout(savegroup07);
    SaveGroupLayout->addLayout(savegroup08);
    SaveGroupLayout->addLayout(savegroup09);

    SaveGroup = new QGroupBox(tr(""));
    SaveGroup->setLayout(SaveGroupLayout);

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    QVBoxLayout *FinalLayout=new QVBoxLayout;
    FinalLayout->addLayout(outpathLayout);
    FinalLayout->addLayout(userIDLayout);
    FinalLayout->addWidget(SaveGroup);
    FinalLayout->addWidget(buttonBox);

    setLayout(FinalLayout);
}
void MetadataCreator::initConnections(void)
{
    connect(lineOutPath,SIGNAL(textChanged(QString)),this,SLOT(on_lineOutPath_textChanged(QString)));
    connect(btnOutPath,SIGNAL(clicked()),this,SLOT(on_btnOutPath_clicked()));

    connect(lineSave00,SIGNAL(textChanged(QString)),this,SLOT(on_lineSave00_textChanged(QString)));
    connect(btnSave00,SIGNAL(clicked()),this,SLOT(on_btnSave00_clicked()));

    connect(lineSave01,SIGNAL(textChanged(QString)),this,SLOT(on_lineSave01_textChanged(QString)));
    connect(btnSave01,SIGNAL(clicked()),this,SLOT(on_btnSave01_clicked()));

    connect(lineSave02,SIGNAL(textChanged(QString)),this,SLOT(on_lineSave02_textChanged(QString)));
    connect(btnSave02,SIGNAL(clicked()),this,SLOT(on_btnSave02_clicked()));

    connect(lineSave03,SIGNAL(textChanged(QString)),this,SLOT(on_lineSave03_textChanged(QString)));
    connect(btnSave03,SIGNAL(clicked()),this,SLOT(on_btnSave03_clicked()));

    connect(lineSave04,SIGNAL(textChanged(QString)),this,SLOT(on_lineSave04_textChanged(QString)));
    connect(btnSave04,SIGNAL(clicked()),this,SLOT(on_btnSave04_clicked()));

    connect(lineSave05,SIGNAL(textChanged(QString)),this,SLOT(on_lineSave05_textChanged(QString)));
    connect(btnSave05,SIGNAL(clicked()),this,SLOT(on_btnSave05_clicked()));

    connect(lineSave06,SIGNAL(textChanged(QString)),this,SLOT(on_lineSave06_textChanged(QString)));
    connect(btnSave06,SIGNAL(clicked()),this,SLOT(on_btnSave06_clicked()));

    connect(lineSave07,SIGNAL(textChanged(QString)),this,SLOT(on_lineSave07_textChanged(QString)));
    connect(btnSave07,SIGNAL(clicked()),this,SLOT(on_btnSave07_clicked()));

    connect(lineSave08,SIGNAL(textChanged(QString)),this,SLOT(on_lineSave08_textChanged(QString)));
    connect(btnSave08,SIGNAL(clicked()),this,SLOT(on_btnSave08_clicked()));

    connect(lineSave09,SIGNAL(textChanged(QString)),this,SLOT(on_lineSave09_textChanged(QString)));
    connect(btnSave09,SIGNAL(clicked()),this,SLOT(on_btnSave09_clicked()));

    connect(buttonBox,SIGNAL(accepted()),this,SLOT(on_buttonBox_accepted()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(on_buttonBox_rejected()));
}

void MetadataCreator::on_lineOutPath_textChanged(const QString &arg1)
{
    if(!load){OutPath=arg1;}
    if(arg1.isEmpty()){buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);}
    else{buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);}
}
void MetadataCreator::on_btnOutPath_clicked()
{
    load = true;
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save Into"),QString("%1/Square Enix/FINAL FANTASY VII/").arg(QDir::homePath()));
    if(!temp.isNull()){OutPath=temp;}
    lineOutPath->setText(OutPath);
    lineUserID->setText(temp.remove(0,temp.lastIndexOf("_")+1));
    load=false;
}

void MetadataCreator::on_lineSave00_textChanged(const QString &arg1){if(!load){InFiles.replace(0,arg1);}}
void MetadataCreator::on_btnSave00_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save00"),QDir::homePath());
    if(ff7->loadFile(temp)){InFiles.replace(0,temp); lineSave00->setText(InFiles.at(0));}
    else{lineSave00->clear();}
    load=false;
}

void MetadataCreator::on_lineSave01_textChanged(const QString &arg1){if(!load){InFiles.replace(1,arg1);}}
void MetadataCreator::on_btnSave01_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save01"),QDir::homePath());
    if(ff7->loadFile(temp)){InFiles.replace(1,temp); lineSave01->setText(InFiles.at(1));}
    else{lineSave01->clear();}
    load=false;
}

void MetadataCreator::on_lineSave02_textChanged(const QString &arg1){if(!load){InFiles.replace(2,arg1);}}
void MetadataCreator::on_btnSave02_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save02"),QDir::homePath());
    if(ff7->loadFile(temp)){InFiles.replace(2,temp); lineSave02->setText(InFiles.at(2));}
    else{lineSave02->clear();}
    load=false;
}

void MetadataCreator::on_lineSave03_textChanged(const QString &arg1){if(!load){InFiles.replace(3,arg1);}}
void MetadataCreator::on_btnSave03_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save03"),QDir::homePath());
    if(ff7->loadFile(temp)){InFiles.replace(3,temp); lineSave03->setText(InFiles.at(3));}
    else{lineSave03->clear();}
    load=false;
}

void MetadataCreator::on_lineSave04_textChanged(const QString &arg1){if(!load){InFiles.replace(4,arg1);}}
void MetadataCreator::on_btnSave04_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save04"),QDir::homePath());
    if(ff7->loadFile(temp)){InFiles.replace(4,temp); lineSave04->setText(InFiles.at(4));}
    else{lineSave04->clear();}
    load=false;
}

void MetadataCreator::on_lineSave05_textChanged(const QString &arg1){if(!load){InFiles.replace(5,arg1);}}
void MetadataCreator::on_btnSave05_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save05"),QDir::homePath());
    if(ff7->loadFile(temp)){InFiles.replace(5,temp); lineSave05->setText(InFiles.at(5));}
    else{lineSave05->clear();}
    load=false;
}

void MetadataCreator::on_lineSave06_textChanged(const QString &arg1){if(!load){InFiles.replace(6,arg1);}}
void MetadataCreator::on_btnSave06_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save06"),QDir::homePath());
    if(ff7->loadFile(temp)){InFiles.replace(6,temp); lineSave06->setText(InFiles.at(6));}
    else{lineSave06->clear();}
    load=false;
}

void MetadataCreator::on_lineSave07_textChanged(const QString &arg1){if(!load){InFiles.replace(7,arg1);}}
void MetadataCreator::on_btnSave07_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save07"),QDir::homePath());
    if(ff7->loadFile(temp)){InFiles.replace(7,temp);lineSave07->setText(InFiles.at(7));}
     else{lineSave07->clear();}
    load=false;
}

void MetadataCreator::on_lineSave08_textChanged(const QString &arg1){if(!load){InFiles.replace(8,arg1);}}
void MetadataCreator::on_btnSave08_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save08"),QDir::homePath());
    if(ff7->loadFile(temp)){InFiles.replace(8,temp); lineSave08->setText(InFiles.at(8));}
    else{lineSave08->clear();}
    load=false;
}

void MetadataCreator::on_lineSave09_textChanged(const QString &arg1){if(!load){InFiles.replace(9,arg1);}}
void MetadataCreator::on_btnSave09_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save09"),QDir::homePath());
    if(ff7->loadFile(temp)){InFiles.replace(9,temp); lineSave09->setText(InFiles.at(9));}
    else{lineSave09->clear();}
    load=false;
}

void MetadataCreator::on_buttonBox_accepted()
{
    for(int i=0;i<10;i++)
    {
        QString OutFile =QString("%1/save0%2.ff7").arg(OutPath,QString::number(i));
        if(InFiles.at(i) =="")
        {//No File Supplied Look in OutPath to see if there is a file.
            QFile tempFile(OutFile);
            if(tempFile.exists())
            {//If we find the file put its path in InFiles
                InFiles.replace(i,OutFile);
            }
            else{ff7->fixMetaData(OutFile,OutPath,lineUserID->text()); continue;}//empty and not found
        }
        if(!ff7->loadFile(InFiles.at(i))){return;}
        if(ff7->type()!="PC"){ff7->exportPC(OutFile);}
        else{ff7->saveFile(OutFile);}
        ff7->fixMetaData(OutFile,OutPath,lineUserID->text());
    }

    QString achevement(QString("%1/achievement.dat").arg(OutPath));
    FILE *pfile;
    long size=0;

    pfile = fopen(achevement.toAscii(),"rb");
    //If file exist, get the size
    if (pfile!=NULL){fseek(pfile, 0, SEEK_END); size=ftell(pfile); fclose(pfile);}

    pfile = fopen(achevement.toAscii(),"wb");
    if(pfile != NULL){
        if(size != 8) {//if size is different, rewrite it
            unsigned int byte[8] = {0,0,0,0,0,0,0,0};
            fwrite(&byte,1,8,pfile);
        }
        fclose(pfile);
    }
    else {}//show the write error msg ("Couldn't write achievement.dat")

    this->close();
}
void MetadataCreator::on_buttonBox_rejected(){this->close();}
