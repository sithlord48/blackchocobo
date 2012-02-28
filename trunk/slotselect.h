/****************************************************************************/
//    copyright 2010-2012 Chris Rizzitello <sithlord48@gmail.com>           //
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

#ifndef SLOTSELECT_H
#define SLOTSELECT_H

#include <QDialog>
#include "globals.h"
#include "SaveIcon.h"
#include "QMessageBox"

#ifndef FF7TEXT_H
#include "static_data/FF7Text.h"
#endif
namespace Ui {
    class SlotSelect;
}

class SlotSelect : public QDialog {
    Q_OBJECT
public:
    SlotSelect(QWidget *parent = 0, FF7 *ff7data=0);
    ~SlotSelect();

protected:
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent *e);
private:
    Ui::SlotSelect *ui;
    SaveIcon icons[15];
    TEXT Text;
    FF7 *ff7;
private slots:


private slots:
    void on_btn_s1_clicked();
    void on_btn_s2_clicked();
    void on_btn_s3_clicked();
    void on_btn_s4_clicked();
    void on_btn_s5_clicked();
    void on_btn_s6_clicked();
    void on_btn_s7_clicked();
    void on_btn_s8_clicked();
    void on_btn_s9_clicked();
    void on_btn_s10_clicked();
    void on_btn_s11_clicked();
    void on_btn_s12_clicked();
    void on_btn_s13_clicked();
    void on_btn_s14_clicked();
    void on_btn_s15_clicked();
};

#endif // SLOTSELECT_H
