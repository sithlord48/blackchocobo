/****************************************************************************/
//    copyright 2012 Chris Rizzitello <sithlord48@gmail.com>           //
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
/*~~~~~~~~~~~Includes~~~~~~~~*/

#include "metadatacreator.h"
#include "ui_metadatacreator.h"
#include <QFileDialog>

metadataCreator::metadataCreator(QWidget *parent,FF7Save *ff7save) :
    QDialog(parent),
    ui(new Ui::metadataCreator)
{
    ui->setupUi(this);
    for(int i=0;i<15;i++){InFiles.append(QString(""));}
     ff7 = ff7save;
}

metadataCreator::~metadataCreator()
{
    delete ui;
}

void metadataCreator::on_lineOutPath_textChanged(const QString &arg1){if(!load){OutPath=arg1;}}
void metadataCreator::on_btnOutPath_clicked()
{
    load = true;
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save Into"),QString("%1/Square Enix/FINAL FANTASY VII/").arg(QDir::homePath()));
    if(!temp.isNull()){OutPath=temp;}
    ui->lineOutPath->setText(OutPath);
    ui->lineUserID->setText(temp.remove(0,temp.lastIndexOf("_")+1));
    load=false;
}

void metadataCreator::on_lineSave00_textChanged(const QString &arg1){if(!load){InFiles.replace(0,arg1);}}
void metadataCreator::on_btnSave00_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save00"),QDir::homePath());
    if(ff7->LoadFile(temp)){InFiles.replace(0,temp); ui->lineSave00->setText(InFiles.at(0));}
    else{ui->lineSave00->clear();}
    load=false;
}

void metadataCreator::on_lineSave01_textChanged(const QString &arg1){if(!load){InFiles.replace(1,arg1);}}
void metadataCreator::on_btnSave01_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save01"),QDir::homePath());
    if(ff7->LoadFile(temp)){InFiles.replace(1,temp); ui->lineSave01->setText(InFiles.at(1));}
    else{ui->lineSave01->clear();}
    load=false;
}

void metadataCreator::on_lineSave02_textChanged(const QString &arg1){if(!load){InFiles.replace(2,arg1);}}
void metadataCreator::on_btnSave02_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save02"),QDir::homePath());
    if(ff7->LoadFile(temp)){InFiles.replace(2,temp); ui->lineSave02->setText(InFiles.at(2));}
    else{ui->lineSave02->clear();}
    load=false;
}

void metadataCreator::on_lineSave03_textChanged(const QString &arg1){if(!load){InFiles.replace(3,arg1);}}
void metadataCreator::on_btnSave03_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save03"),QDir::homePath());
    if(ff7->LoadFile(temp)){InFiles.replace(3,temp); ui->lineSave03->setText(InFiles.at(3));}
    else{ui->lineSave03->clear();}
    load=false;
}

void metadataCreator::on_lineSave04_textChanged(const QString &arg1){if(!load){InFiles.replace(4,arg1);}}
void metadataCreator::on_btnSave04_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save04"),QDir::homePath());
    if(ff7->LoadFile(temp)){InFiles.replace(4,temp); ui->lineSave04->setText(InFiles.at(4));}
    else{ui->lineSave04->clear();}
    load=false;
}

void metadataCreator::on_lineSave05_textChanged(const QString &arg1){if(!load){InFiles.replace(5,arg1);}}
void metadataCreator::on_btnSave05_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save05"),QDir::homePath());
    if(ff7->LoadFile(temp)){InFiles.replace(5,temp); ui->lineSave05->setText(InFiles.at(5));}
    else{ui->lineSave05->clear();}
    load=false;
}

void metadataCreator::on_lineSave06_textChanged(const QString &arg1){if(!load){InFiles.replace(6,arg1);}}
void metadataCreator::on_btnSave06_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save06"),QDir::homePath());
    if(ff7->LoadFile(temp)){InFiles.replace(6,temp); ui->lineSave06->setText(InFiles.at(6));}
    else{ui->lineSave06->clear();}
    load=false;
}

void metadataCreator::on_lineSave07_textChanged(const QString &arg1){if(!load){InFiles.replace(7,arg1);}}
void metadataCreator::on_btnSave07_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save07"),QDir::homePath());
    if(ff7->LoadFile(temp)){InFiles.replace(7,temp);ui->lineSave07->setText(InFiles.at(7));}
     else{ui->lineSave07->clear();}
    load=false;
}

void metadataCreator::on_lineSave08_textChanged(const QString &arg1){if(!load){InFiles.replace(8,arg1);}}
void metadataCreator::on_btnSave08_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save08"),QDir::homePath());
    if(ff7->LoadFile(temp)){InFiles.replace(8,temp); ui->lineSave08->setText(InFiles.at(8));}
    else{ui->lineSave08->clear();}
    load=false;
}

void metadataCreator::on_lineSave09_textChanged(const QString &arg1){if(!load){InFiles.replace(9,arg1);}}
void metadataCreator::on_btnSave09_clicked()
{
    load = true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A File To Use As Save09"),QDir::homePath());
    if(ff7->LoadFile(temp)){InFiles.replace(9,temp); ui->lineSave09->setText(InFiles.at(9));}
    else{ui->lineSave09->clear();}
    load=false;
}

void metadataCreator::on_buttonBox_accepted()
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
            else{ff7->FixMetaData(OutFile,OutPath,ui->lineUserID->text()); continue;}//empty and not found
        }
        if(!ff7->LoadFile(InFiles.at(i))){return;}
        if(ff7->type()!="PC"){ff7->Export_PC(OutFile);}
        else{ff7->SaveFile(OutFile);}
        ff7->FixMetaData(OutFile,OutPath,ui->lineUserID->text());
    }

    QString achevement(QString("%1/achievement.dat").arg(OutPath));
    FILE *pfile;
    long size;

    pfile = fopen(achevement.toAscii(),"rb");
    //If file exist, get the size
    if (pfile!=NULL){fseek(pfile, 0, SEEK_END); size=ftell(pfile); fclose(pfile);}

    pfile = fopen(achevement.toAscii(),"wb");
    if(pfile != NULL){
        if(size != 8) {//if size is different, rewrite it
            quint8 byte=0x00;
            fwrite(&byte,1,8,pfile);
        }
        fclose(pfile);
    }
    else {}//show the write error msg ("Couldn't write achievement.dat")

    this->close();
}
void metadataCreator::on_buttonBox_rejected(){this->close();}
