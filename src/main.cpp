/****************************************************************************/
//    copyright 2010-2020 Chris Rizzitello <sithlord48@gmail.com>           //
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
#include <QApplication>
#include <QLocale>
#include <QStyle>
#include <QStyleFactory>
#include <QTranslator>
#include <QTime>
#include <QRandomGenerator>

#include "bcsettings.h"
#include "mainwindow.h"

#if defined(STATIC) && (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#include <QtPlugin> //FOR STATIC BUILD. Q_IMPORT_PLUGIN: Allow to make use of a static plugins (qjpcodecs)
//FOR STATIC BUILD.(WILL FAIL HERE IF NOT STATICLY BUILT QT!)
Q_IMPORT_PLUGIN(qcncodecs)
Q_IMPORT_PLUGIN(qjpcodecs)  //(Japanese Text Support)
Q_IMPORT_PLUGIN(qtwcodecs)
Q_IMPORT_PLUGIN(qkrcodecs)
#endif

int main(int argc, char *argv[])
{
    if(argc >1) {
        if(QString(argv[1]) == "--help" || QString(argv[1]) =="-h") {
            printf("Usage: blackchocobo [<filename>]\nUsage: blackchocobo --version :Print Version Info\n");
            return 0;
        }

        if(QString(argv[1]) == "--version") {
            printf("Black Chocobo Version:%s \n", BC_VERSION);
            return 0;
        }
    }
    Q_INIT_RESOURCE(icons);

    QApplication a(argc, argv);
    //Start application init.
    a.setStyle(QStyleFactory::create(BCSettings::instance()->value(SETTINGS::APPSTYLE, QVariant(QString(a.style()->objectName()))).toString()));
    a.setPalette(BCSettings::instance()->paletteForSetting());
    a.setAttribute(Qt::AA_DontUseNativeDialogs, !BCSettings::instance()->value(SETTINGS::USENATIVEDIALOGS).toBool());
    a.setApplicationName("Black Chocobo");
    a.setApplicationVersion(BC_VERSION);

    QRandomGenerator(quint32(QTime::currentTime().msec()));
    MainWindow w;
    if(argc == 2)
        w.loadFileFull(QString(argv[1]), 0);
    w.show();
    return a.exec();
}
