/****************************************************************************/
//    copyright 2012 - 2020  Chris Rizzitello <sithlord48@gmail.com>        //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "FF7Text.h"

#include <QQmlEngine>

/*~~~~~~~~TEXT CLASS~~~~~~~~~*/
// the PC function is modified from Makou Reactor (thanks Myst6re)
FF7TEXT *FF7TEXT::instance()
{
    static FF7TEXT m;
    return &m;
}

FF7TEXT::FF7TEXT(QObject *parent) :
    QObject(parent)
    , d(new FF7TEXTPrivate)
{
}

FF7TEXT::~FF7TEXT()
{
    delete d;
}

QObject *FF7TEXT::qmlSingletonRegister(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine)
    engine->setObjectOwnership(instance(), QQmlEngine::CppOwnership);
    return instance();
}

void FF7TEXT::setJapanese(bool japanese)
{
    if(japanese == d->in_ja)
        return;
    d->in_ja = japanese;
    emit languageChanged();
}

bool FF7TEXT::isJapanese()
{
    return d->in_ja;
}
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
        if (d->in_ja) {
            switch (index) {
            case 0xFA:
                ++i;
                String += d->jap_fa[quint8(text.at(i))];
                break;
            case 0xFB:
                ++i;
                String += d->jap_fb[quint8(text.at(i))];
                break;
            case 0xFC:
                ++i;
                String += d->jap_fc[quint8(text.at(i))];
                break;
            case 0xFD:
                ++i;
                String += d->jap_fd[quint8(text.at(i))];
                break;
            case 0xFE:
                ++i;
                if (quint8(text.at(i)) == 0xE2) {
                    i += 4;
                }
                String += d->jap_fe[quint8(text.at(i))];
                break;
            default:
                String.append(d->jap.at(index));
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
                String.append(d->eng.at(index));
                break;
            }
        }
    }
    return String;
}
//This Converter is Modified From Hyne (thanks Myst6re)
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
        if (d->in_ja) {
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
        return d->jap.at(ord);
    case 2:
        return d->jap_fa.at(ord);
    case 3:
        return d->jap_fb.at(ord);
    case 4:
        return d->jap_fc.at(ord);
    case 5:
        return d->jap_fd.at(ord);
    case 6:
        return d->jap_fe.at(ord);
    default:
        return d->eng.at(ord);
    }
}
