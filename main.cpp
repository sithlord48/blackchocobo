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
#include "qglobal.h"

#include <QtWidgets/QApplication>
#include <QLocale>
#include <QTranslator>
#include <QTime>
#include <QSettings>
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
    QVersionNumber version(1, 9, 96);

    if(argc >1) {
        if(QString(argv[1]) == "--help" || QString(argv[1]) =="-h")
            printf("Usage: blackchocobo [<filename>]\nUsage: blackchocobo --version :Print Version Info\n");
        else if(QString(argv[1]) == "--version")
            printf("Black Chocobo Version:%s \n",version.toString().toLocal8Bit().constData());
        return 0;
    }
    //Start application init.
    Q_INIT_RESOURCE(images);
    QApplication a(argc, argv);
#ifndef Q_OS_LINUX
    a.setStyle(QStyleFactory::create("Fusion"));
#endif
    a.setAttribute(Qt::AA_DontUseNativeDialogs);
    a.setApplicationName("Black Chocobo");
    a.setApplicationVersion(version.toString());

    QRandomGenerator(quint32(QTime::currentTime().msec()));
    MainWindow w;
    if(argc ==2)
        w.loadFileFull(QString(argv[1]), 0);// if command is run w/ a filename after it , load that file.
    w.show();
    return a.exec();
}
