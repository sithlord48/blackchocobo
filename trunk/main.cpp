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
#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets/QApplication>
    #include <QStyleFactory>
#else
    #include <QtGui/QApplication>
    #include <QPlastiqueStyle>
#endif

#include <QLocale>
#include <QTranslator>
#include <QTime>
#include <QSettings>
#include "mainwindow.h"
#include "version.h"                // contains the program version

#ifdef STATIC
#include <QtPlugin> //FOR STATIC BUILD. Q_IMPORT_PLUGIN: Allow to make use of a static plugins (qjpcodecs)
//FOR STATIC BUILD.(WILL FAIL HERE IF NOT STATICLY BUILT QT!)
Q_IMPORT_PLUGIN(qcncodecs)
Q_IMPORT_PLUGIN(qjpcodecs)  //(Japanese Text Support)
Q_IMPORT_PLUGIN(qtwcodecs)
Q_IMPORT_PLUGIN(qkrcodecs)
#endif

int main(int argc, char *argv[])
{
    QString Version = QString::number(VER_MAJOR);
    Version.append(QString("."));
    Version.append(QString::number(VER_MINOR));
    Version.append(QString("."));
    Version.append(QString::number(VER_SP));

    if(argc >1)
    {//Check for and display help to the console :D
        if(QString(argv[1]) == "--help" || QString(argv[1]) =="-h"){printf("Usage: blackchocobo [<filename>]\nUsage: blackchocobo --version :Print Version Info\n");return 0;}
        else if(QString(argv[1]) == "--version"){printf("Black Chocobo Version:%s \n",Version.toLocal8Bit().constData());return 0;}
    }
    //Start application init.
    Q_INIT_RESOURCE(images);
    QApplication a(argc, argv);
    a.setApplicationName("Black Chocobo");
    if(QT_VERSION < 0x50000){a.setStyle("Plastique");}
    else{a.setStyle(QStyleFactory::create("fusion"));}
    a.setApplicationVersion(Version);

    #ifdef STATIC
    QSettings settings(QCoreApplication::applicationDirPath() +"/" + "settings.ini",QSettings::IniFormat);
    #else
    QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"blackchocobo","settings",0);
    #endif //STATIC

    QTranslator translator;
    QString lang = QCoreApplication::applicationDirPath() +"/"+ "lang/bchoco_";
    if(settings.value("lang").isNull()){settings.setValue("lang",QLocale::system().name().section('_',0,0));} //if no lang set it to os setting.
    lang.append(settings.value("lang").toString());
    translator.load(lang);
    a.installTranslator(&translator);
    FF7Save ff7; //main ff7 data
    qsrand(QTime::currentTime().msec());
    MainWindow w(0,&ff7,&settings);
    if(argc ==2){w.loadFileFull(QString(argv[1]),0);}// if command is run w/ a filename after it , load that file.
    w.show();
    return a.exec();
}
