/****************************************************************************/
//    copyright 2010-2012 Chris Rizzitello <sithlord48@gmail.com>           //
//                                                                          //
//    This file is part of FF7tk                                            //
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
#ifndef FF7TEXT_H
  #define FF7TEXT_H
#include <QObject>

class FF7TEXT{
private:
    QString eng;
    QString jap;
    QString jap_fa;
    QString jap_fb;
    QString jap_fc;
    QString jap_fd;
    QString jap_fe;
    bool in_ja;
    QString character(quint8 ord, quint8 table);
public:
    FF7TEXT();
    void init(bool);
    QString toPC(QByteArray text);
    QByteArray toFF7(QString string);
};
#endif //FF7TEXT_H
