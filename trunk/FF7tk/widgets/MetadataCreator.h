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

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif
#include "../static_data/FF7Save.h"


class MetadataCreator : public QDialog
{
    Q_OBJECT
    
public:
    explicit MetadataCreator(QWidget *parent = 0,FF7Save *ff7save=0);
private slots:
    void initDisplay();
    void initConnections();
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
    //GUI Parts
    QLineEdit *lineOutPath;
    QLineEdit *lineUserID;
    QLineEdit *lineSave00;
    QLineEdit *lineSave01;
    QLineEdit *lineSave02;
    QLineEdit *lineSave03;
    QLineEdit *lineSave04;
    QLineEdit *lineSave05;
    QLineEdit *lineSave06;
    QLineEdit *lineSave07;
    QLineEdit *lineSave08;
    QLineEdit *lineSave09;
    QPushButton *btnOutPath;
    QPushButton *btnSave00;
    QPushButton *btnSave01;
    QPushButton *btnSave02;
    QPushButton *btnSave03;
    QPushButton *btnSave04;
    QPushButton *btnSave05;
    QPushButton *btnSave06;
    QPushButton *btnSave07;
    QPushButton *btnSave08;
    QPushButton *btnSave09;
    QDialogButtonBox *buttonBox;
    QSpacerItem *IDSpacer;
    QLabel *lblSave00;
    QLabel *lblSave01;
    QLabel *lblSave02;
    QLabel *lblSave03;
    QLabel *lblSave04;
    QLabel *lblSave05;
    QLabel *lblSave06;
    QLabel *lblSave07;
    QLabel *lblSave08;
    QLabel *lblSave09;
    QLabel *lblOut;
    QLabel *lblUserID;
    QGroupBox *SaveGroup;
    //Data Parts
    bool load;
    FF7Save *ff7;
    QStringList InFiles;
    QString OutPath;
    QString UserID;
};

#endif // METADATACREATOR_H
