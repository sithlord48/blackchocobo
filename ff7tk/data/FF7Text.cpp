/****************************************************************************/
//    copyright 2012 - 2018  Chris Rizzitello <sithlord48@gmail.com>        //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//   FF7tk is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#include "FF7Text.h"
/*~~~~~~~~TEXT CLASS~~~~~~~~~*/
// the PC function is modified from Makou Reactor (thanks Myst6re)
QString FF7TEXT::toPC(QByteArray text)
{
    int txt = 0;
    if ((txt = text.indexOf('\xFF')) != -1) {
        text.truncate(txt);
    }

    QString String;

    for (quint16 i = 0 ; i < text.size() ; ++i) {
        quint8 index = quint8(text.at(i));
        if (index == 0xFF) {
            break;
        }
        if (in_ja) {
            switch (index) {
            case 0xFA:
                ++i;
                String += jap_fa[quint8(text.at(i))];
                break;
            case 0xFB:
                ++i;
                String += jap_fb[quint8(text.at(i))];
                break;
            case 0xFC:
                ++i;
                String += jap_fc[quint8(text.at(i))];
                break;
            case 0xFD:
                ++i;
                String += jap_fd[quint8(text.at(i))];
                break;
            case 0xFE:
                ++i;
                if (quint8(text.at(i)) == 0xE2) {
                    i += 4;
                }
                String += jap_fe[quint8(text.at(i))];
                break;
            default:
                String.append(jap.at(index));
                break;
            }
        } else {
            switch (index) {
            case 0xFA: case 0xFB: case 0xFC: case 0xFD:
                ++i;
                String += "¶";
                break;
            case 0xFE:
                ++i;
                if (quint8(text.at(i)) == 0xE2) {
                    i += 4;
                }
                String += "¶";
                break;
            default:
                String.append(eng.at(index));
                break;
            }
        }
    }
    return String;
}
//This Convertor is Modified From Hyne (thanks Myst6re)
QByteArray FF7TEXT::toFF7(const QString &string)
{
    QByteArray ff7str;
    QChar comp;
    int stringSize = string.size(), i, table;

    for (int c = 0 ; c < stringSize ; ++c) {
        comp = string.at(c);
        for (i = 0 ; i <= 0xff ; ++i) {
            if (!QString::compare(comp, character(quint8(i), 0))) {
                ff7str.append(char(i));
                goto end;
            }
        }
        if (in_ja) {
            for (table = 1 ; table < 7 ; ++table) {
                for (i = 0 ; i <= 0xff ; ++i) {
                    if (!QString::compare(comp, character(quint8(i), quint8(table)))) {
                        switch (table) {
                        case 1: break;
                        case 2: ff7str.append('\xFA');   break;
                        case 3: ff7str.append('\xFB');   break;
                        case 4: ff7str.append('\xFC');   break;
                        case 5: ff7str.append('\xFD');   break;
                        case 6: ff7str.append('\xFE');   break;
                        }
                        ff7str.append(char(i));
                        goto end;
                    }
                }
            }
        }
    end:;
    }
    return ff7str;
}

QString FF7TEXT::character(quint8 ord, quint8 table)
{
    switch (table) {
    case 1:
        return jap.at(ord);
    case 2:
        return jap_fa.at(ord);
    case 3:
        return jap_fb.at(ord);
    case 4:
        return jap_fc.at(ord);
    case 5:
        return jap_fd.at(ord);
    case 6:
        return jap_fe.at(ord);
    default:
        return eng.at(ord);
    }
}
