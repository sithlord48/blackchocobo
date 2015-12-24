/****************************************************************************/
//    copyright 2010-2016 Chris Rizzitello <sithlord48@gmail.com>           //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QSettings>

namespace Ui {
    class About;
}

class About : public QDialog {
    Q_OBJECT
public:
    explicit About(QWidget *parent = 0, QSettings* config_data =0);
    ~About();


protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
    void resizeEvent(QResizeEvent *);
    void moveEvent(QMoveEvent *);

private:
    Ui::About *ui;
    QSettings *settings;
};
#endif // ABOUT_H
