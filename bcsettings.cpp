/****************************************************************************/
//    copyright 2020 Chris Rizzitello <sithlord48@gmail.com>                //
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
#include "bcsettings.h"
#include <QSettings>
#include <QCoreApplication>
#include <QFile>
#include <QStandardPaths>
#include <QDir>


BCSettings *BCSettings::instance()
{
    static BCSettings m;
    return &m;
}

BCSettings::BCSettings(QObject *parent) 
    : QObject(parent)
{
    initSettings();
    cleanSettings();
}

void BCSettings::initSettings()
{
#ifdef STATIC
    settings = new QSettings(QStringLiteral("%1/settings.ini").arg(QCoreApplication::applicationDirPath()), QSettings::IniFormat);
#else //STATIC
    if (QFile(QStringLiteral("%1/settings.ini").arg(QCoreApplication::applicationDirPath())).exists())
        settings = new QSettings(QStringLiteral("%1/settings.ini").arg(QCoreApplication::applicationDirPath()), QSettings::IniFormat);
    else
        settings = new QSettings(QSettings::NativeFormat, QSettings::UserScope, QStringLiteral("blackchocobo"), QStringLiteral("settings"), nullptr);
#endif //STATIC
#ifdef Q_OS_UNIX
#ifndef Q_OS_MAC
    //check the lang path and if running from /usr/bin (and Unix) then usr copies in /usr/share/blackchocobo
    if (QCoreApplication::applicationDirPath().startsWith("/usr/bin"))
        settings->setValue(SETTINGS::LANGPATH, QStringLiteral("/usr/share/blackchocobo"));
    else
        settings->setValue(SETTINGS::LANGPATH, QCoreApplication::applicationDirPath());
#endif
#else
    settings->setValue(SETTINGS::LANGPATH, QCoreApplication::applicationDirPath());
#endif
    if (settings->value(SETTINGS::SIDEBARURLS).isNull()) {
        QStringList defaultBarUrls;
        defaultBarUrls.append(QDir::rootPath());
        defaultBarUrls.append(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        if (!settings->value(SETTINGS::LOADPATH).toString().isEmpty())
            defaultBarUrls.append(settings->value(SETTINGS::LOADPATH).toString());
        if (!settings->value(SETTINGS::PCSAVEPATH).toString().isEmpty())
            defaultBarUrls.append(settings->value(SETTINGS::PCSAVEPATH).toString());
        if (!settings->value(SETTINGS::EMUSAVEPATH).toString().isEmpty())
            defaultBarUrls.append(settings->value(SETTINGS::EMUSAVEPATH).toString());
        if (!settings->value(SETTINGS::STATFOLDER).toString().isEmpty())
            defaultBarUrls.append(settings->value(SETTINGS::STATFOLDER).toString());
        settings->setValue(SETTINGS::SIDEBARURLS, defaultBarUrls);
    }
    if (settings->value(SETTINGS::EDITABLECOMBOS).isNull())
        settings->setValue(SETTINGS::EDITABLECOMBOS, true);

    if (settings->value(SETTINGS::REGION).isNull())
        settings->setValue(SETTINGS::REGION, QStringLiteral("NTSC-U"));
}

void BCSettings::cleanSettings()
{
    for(const QString &key : settings->allKeys()) {
        if(!validSettingsNames.contains(key))
            settings->remove(key);
    }
}

void BCSettings::setValue(const QString &setting, const QVariant &value)
{
    settings->setValue(setting, value);
    settings->sync();
    settingsChanged();
}

QVariant BCSettings::value(const QString &setting, const QVariant &defaultValue)
{
    return settings->value(setting, defaultValue);
}

void BCSettings::restoreDefaultSettings()
{
    settings->setValue(SETTINGS::LOADPATH, QString());
    settings->setValue(SETTINGS::LOADPATH, QString());
    settings->setValue(SETTINGS::DEFAULTSAVE, QString());
    settings->setValue(SETTINGS::STATFOLDER, QString());
    settings->setValue(SETTINGS::PCSAVEPATH, QString());
    settings->setValue(SETTINGS::EMUSAVEPATH, QString());
    settings->setValue(SETTINGS::EDITABLECOMBOS, true);
    settings->setValue(SETTINGS::CHARADVANCED, false);
    settings->setValue(SETTINGS::CHOCOADVANCED, false);
    settings->setValue(SETTINGS::LOCVIEWADVANCED, false);
    settings->setValue(SETTINGS::ENABLETEST, false);
    settings->setValue(SETTINGS::PROGRESSADVANCED, false);
    settings->setValue(SETTINGS::ALWAYSSHOWCONTROLLERMAP, false);
    settings->setValue(SETTINGS::WORLDMAPADVANCED, false);
    settings->setValue(SETTINGS::REGION, QStringLiteral("NTSC-U"));
    settings->setValue(SETTINGS::CUSTOMDEFAULTSAVE, false);
    settings->setValue(SETTINGS::SCALE, 1.00);
    settings->setValue(SETTINGS::AUTOGROWTH, true);
    settings->setValue(SETTINGS::USENATIVEDIALOGS, false);
}
