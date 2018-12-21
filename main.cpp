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
#include "version.h"                // contains the program version

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
    QString Version = QString::number(VER_MAJOR);
    Version.append(QString("."));
    Version.append(QString::number(VER_MINOR));
    Version.append(QString("."));
    Version.append(QString::number(VER_SP));
    if(VER_BUILDNR>0){Version.append(QString("."));Version.append(QString::number(VER_BUILDNR));}

    if(argc >1)
    {//Check for and display help to the console :D
        if(QString(argv[1]) == "--help" || QString(argv[1]) =="-h"){printf("Usage: blackchocobo [<filename>]\nUsage: blackchocobo --version :Print Version Info\n");return 0;}
        else if(QString(argv[1]) == "--version"){printf("Black Chocobo Version:%s \n",Version.toLocal8Bit().constData());return 0;}
    }
    //Start application init.
    Q_INIT_RESOURCE(images);
    QApplication a(argc, argv);
    a.setApplicationName("Black Chocobo");
    QSettings * settings;

    a.setApplicationVersion(Version);

    #ifdef STATIC
        settings= new QSettings(QCoreApplication::applicationDirPath() +"/" + "settings.ini",QSettings::IniFormat);
    #endif //STATIC

    if(QFile(QString(QCoreApplication::applicationDirPath() + QDir::separator() + "settings.ini")).exists())
    {

        settings= new QSettings(QCoreApplication::applicationDirPath() +"/" + "settings.ini",QSettings::IniFormat);
    }
    else
    {
        settings= new QSettings(QSettings::NativeFormat,QSettings::UserScope,"blackchocobo","settings",0);
    }

    QTranslator translator;
    #ifdef Q_OS_UNIX
        #ifndef Q_OS_MAC
            if(QCoreApplication::applicationDirPath().startsWith("/usr/bin"))
            {//check the lang path and if running from /usr/bin (and Unix) then usr copies in /usr/share/blackchocobo
                settings->setValue("langPath",QString("/usr/share/blackchocobo"));
            }
            else{settings->setValue("langPath",QCoreApplication::applicationDirPath());}
        #endif
    #else
        settings->setValue("langPath",QCoreApplication::applicationDirPath());
    #endif
    QString lang = settings->value("langPath").toString() +"/"+ "lang/bchoco_";
    if(settings->value("lang").isNull()){settings->setValue("lang",QLocale::system().name().section('_',0,0));} //if no lang set it to os setting.
    lang.append(settings->value("lang").toString());
    if(!translator.load(lang))
    {
        lang = QCoreApplication::applicationDirPath() +"/" +"lang/bchoco_";
        lang.append(settings->value("lang").toString());
        if(translator.load(lang))
        {//if we do load from here reset the path so it can be used by widgets later for autotranslated
            settings->setValue("langPath",QCoreApplication::applicationDirPath());
        }
    }
    a.installTranslator(&translator);
    qsrand(QTime::currentTime().msec());
    MainWindow w(0,settings);
    if(argc ==2){w.loadFileFull(QString(argv[1]),0);}// if command is run w/ a filename after it , load that file.
    w.show();
    return a.exec();
}
