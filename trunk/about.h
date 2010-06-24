/****************************************************************************/
//    copyright 2010 Chris Rizzitello <sithlord48@gmail.com>                //
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
#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
    class about;
}

class about : public QDialog {
    Q_OBJECT
public:
    about(QWidget *parent = 0);
    ~about();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::about *ui;
};

#endif // ABOUT_H
