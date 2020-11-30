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
#include <QApplication>
#include <QStyle>

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
    const QStringList keys = settings->allKeys();
    for(const QString &key : keys) {
        if (!validSettingsNames.contains(key))
            settings->remove(key);
        if (settings->value(key).toString().isEmpty() && !settings->value(key).isValid())
            settings->remove(key);
    }
}

void BCSettings::setValue(const QString &setting, const QVariant &value)
{
    if (settings->value(setting) == value)
        return;

    if (value.toString().isEmpty() && !value.isValid())
        settings->remove(setting);
    else
        settings->setValue(setting, value);
    settings->sync();
    emit settingsChanged();
}

QVariant BCSettings::value(const QString &setting, const QVariant &defaultValue)
{
    return settings->value(setting, defaultValue);
}

void BCSettings::restoreDefaultSettings()
{
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
    settings->setValue(SETTINGS::COLORSCHEME, 0);
}
QPalette BCSettings::paletteForSetting()
{
    int index = settings->value(SETTINGS::COLORSCHEME).toInt();
    QPalette newPalette;
    if( index != 0) {
        newPalette.setColor(QPalette::Window, index == 1 ? darkWindow : lightWindow);
        newPalette.setColor(QPalette::Base, index == 1 ? darkButton : lightButton);
        newPalette.setColor(QPalette::Text, index == 1 ? darkText : lightText);
        newPalette.setColor(QPalette::AlternateBase, index == 1 ? darkWindow : lightWindow);
        newPalette.setColor(QPalette::WindowText, index == 1 ? darkText : lightText);
        newPalette.setColor(QPalette::Button, index == 1 ? darkButton : lightButton);
        newPalette.setColor(QPalette::ButtonText,index == 1 ? darkText : lightText);
        newPalette.setColor(QPalette::PlaceholderText, index == 1 ? darkPlaceholderText : lightPlaceholderText);
        newPalette.setColor(QPalette::Disabled, QPalette::Button, index == 1 ? darkDisableButton : lightDisableButton);
        newPalette.setColor(QPalette::Disabled, QPalette::Window, index == 1 ? darkDisableButton : lightDisableButton);
        newPalette.setColor(QPalette::Disabled, QPalette::WindowText, index == 1 ? darkInactiveText : lightInactiveText);
        newPalette.setColor(QPalette::Disabled,QPalette::ButtonText, index == 1 ? darkInactiveText : lightInactiveText);
        newPalette.setColor(QPalette::ToolTipBase, index == 1 ? darkText : lightText);
        newPalette.setColor(QPalette::ToolTipText, index == 1 ? darkWindow : lightWindow);
        newPalette.setColor(QPalette::Highlight,index == 1 ? darkHighlight : lightHighlight);
        newPalette.setColor(QPalette::HighlightedText, index == 1 ? darkWindow : lightWindow);
        newPalette.setColor(QPalette::Inactive, QPalette::HighlightedText, index == 1 ? darkButton : lightButton);
        newPalette.setColor(QPalette::Active, QPalette::Text, index == 1 ? darkText : lightText);
        newPalette.setColor(QPalette::Link, index == 1 ? darkLink : lightLink);
        newPalette.setColor(QPalette::LinkVisited, index == 1 ? darkInactiveText : lightInactiveText);
    }
    return newPalette;
}
