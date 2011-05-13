/****************************************************************************/
//    copyright 2010, 2011 Chris Rizzitello <sithlord48@gmail.com>          //
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

#ifndef ERRBOX_H
#define ERRBOX_H

#include <QDialog>
#include "globals.h"    // contains checksumming functions
#include <SaveIcon.h>
namespace Ui {
    class errbox;
}

class errbox : public QDialog
{
    Q_OBJECT

public:
    explicit errbox(QWidget *parent = 0);
    ~errbox();

private slots:
    void on_btn_prev_clicked();

    void on_btn_export_clicked();

    void on_btn_view_clicked();

    void on_btn_next_clicked();

private:
    Ui::errbox *ui;
};

#endif // ERRBOX_H
