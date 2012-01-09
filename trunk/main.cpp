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

#include <QtGui/QApplication>
#include <QLocale>
#include <QTranslator>
#include "mainwindow.h"
#include <QSettings>
#include <QPlastiqueStyle>
#include <QTime>

int main(int argc, char *argv[])
{
    if(argc >1)
    {//Check for and display help to the console :D
        if(QString(argv[1]) == "--help" || QString(argv[1]) =="-h"){printf("Usage: blackchocobo [<filename>]\n");return 0;}
    }
    QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"blackchocobo","settings",0);
    Q_INIT_RESOURCE(images);
    QApplication a(argc, argv);
    a.setApplicationName("Black Chocobo");
    a.setStyle("Plastique");
    a.setApplicationVersion("1.9.52");
    QTranslator translator;
    QString lang = QCoreApplication::applicationDirPath() +"/"+ "lang/bchoco_";
    if(settings.value("lang").isNull()){settings.setValue("lang",QLocale::system().name().section('_',0,0));} //if no lang set it to os setting.
    lang.append(settings.value("lang").toString());
    translator.load(lang);
    a.installTranslator(&translator);
    FF7 ff7; //main ff7 data
    qsrand(QTime::currentTime().msec());
    MainWindow w(0,&ff7,&settings);
    if(argc ==2){w.loadFileFull(QString(argv[1]),0);}// if command is run w/ a filename after it , load that file.
    w.show();
    return a.exec();
}
