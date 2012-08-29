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

#ifndef METADATACREATOR_H
#define METADATACREATOR_H

#include <QDialog>
#include "FF7tk/static_data/FF7Save.h"
namespace Ui {
class metadataCreator;
}

class metadataCreator : public QDialog
{
    Q_OBJECT
    
public:
    explicit metadataCreator(QWidget *parent = 0,FF7Save *ff7save=0);
    ~metadataCreator();
    
private slots:
    void on_btnOutPath_clicked();
    void on_lineOutPath_textChanged(const QString &arg1);
    void on_btnSave00_clicked();
    void on_lineSave00_textChanged(const QString &arg1);
    void on_btnSave01_clicked();
    void on_lineSave01_textChanged(const QString &arg1);
    void on_btnSave02_clicked();
    void on_lineSave02_textChanged(const QString &arg1);
    void on_btnSave03_clicked();
    void on_lineSave03_textChanged(const QString &arg1);
    void on_btnSave04_clicked();
    void on_lineSave04_textChanged(const QString &arg1);
    void on_btnSave05_clicked();
    void on_lineSave05_textChanged(const QString &arg1);
    void on_btnSave06_clicked();
    void on_lineSave06_textChanged(const QString &arg1);
    void on_btnSave07_clicked();
    void on_lineSave07_textChanged(const QString &arg1);
    void on_btnSave08_clicked();
    void on_lineSave08_textChanged(const QString &arg1);
    void on_btnSave09_clicked();
    void on_lineSave09_textChanged(const QString &arg1);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
private:
    Ui::metadataCreator *ui;
    bool load;
    FF7Save *ff7;
    QStringList InFiles;
    QString OutPath;
    QString UserID;
};

#endif // METADATACREATOR_H
