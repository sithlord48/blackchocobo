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

    QDir translationDir(QStringLiteral("%1/%2").arg(QCoreApplication::applicationDirPath(), QStringLiteral("translations")));
    QStringList nameFilter{QStringLiteral("blackchocobo_*.qm")};
    if (translationDir.entryList(nameFilter, QDir::Files, QDir::Name).isEmpty()) {
        translationDir.setPath(QStringLiteral("%1/../translations").arg(QCoreApplication::applicationDirPath()));
        if (translationDir.entryList(nameFilter, QDir::Files, QDir::Name).isEmpty()) {
            translationDir.setPath(QStringLiteral("%1/../share/blackchocobo/translations").arg(QCoreApplication::applicationDirPath()));
            if (translationDir.entryList(nameFilter, QDir::Files, QDir::Name).isEmpty()) {
                translationDir.setPath(QStringLiteral("%1/%2").arg(QDir::homePath(), QStringLiteral(".local/share/blackchocobo/translations")));
                if (translationDir.entryList(nameFilter, QDir::Files, QDir::Name).isEmpty()) {
                    translationDir.setPath(QStringLiteral("/usr/local/share/blackchocobo/translations"));
                    if (translationDir.entryList(nameFilter, QDir::Files, QDir::Name).isEmpty()) {
                        translationDir.setPath(QStringLiteral("/usr/share/blackchocobo/translations"));
                    }
                }
            }
        }
    }
    settings->setValue(SETTINGS::LANGPATH, translationDir.absolutePath());
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
    if (instance()->settings->value(setting) == value)
        return;

    if (value.toString().isEmpty() && !value.isValid())
        instance()->settings->remove(setting);
    else
        instance()->settings->setValue(setting, value);
    instance()->settings->sync();
    emit instance()->settingsChanged();
}

QVariant BCSettings::value(const QString &setting, const QVariant &defaultValue)
{
    return instance()->settings->value(setting, defaultValue);
}

void BCSettings::restoreDefaultSettings()
{
    instance()->settings->setValue(SETTINGS::LOADPATH, QString());
    instance()->settings->setValue(SETTINGS::DEFAULTSAVE, QString());
    instance()->settings->setValue(SETTINGS::STATFOLDER, QString());
    instance()->settings->setValue(SETTINGS::PCSAVEPATH, QString());
    instance()->settings->setValue(SETTINGS::EMUSAVEPATH, QString());
    instance()->settings->setValue(SETTINGS::EDITABLECOMBOS, true);
    instance()->settings->setValue(SETTINGS::CHARADVANCED, false);
    instance()->settings->setValue(SETTINGS::CHOCOADVANCED, false);
    instance()->settings->setValue(SETTINGS::LOCVIEWADVANCED, false);
    instance()->settings->setValue(SETTINGS::ENABLETEST, false);
    instance()->settings->setValue(SETTINGS::PROGRESSADVANCED, false);
    instance()->settings->setValue(SETTINGS::ALWAYSSHOWCONTROLLERMAP, false);
    instance()->settings->setValue(SETTINGS::WORLDMAPADVANCED, false);
    instance()->settings->setValue(SETTINGS::REGION, QStringLiteral("NTSC-U"));
    instance()->settings->setValue(SETTINGS::CUSTOMDEFAULTSAVE, false);
    instance()->settings->setValue(SETTINGS::AUTOGROWTH, true);
    instance()->settings->setValue(SETTINGS::USENATIVEDIALOGS, true);
    instance()->settings->setValue(SETTINGS::COLORSCHEME, 0);
    instance()->settings->setValue(SETTINGS::APPSTYLE, QStringLiteral("Fusion"));
    instance()->settings->setValue(SETTINGS::ITEMCAP99, false);
    instance()->settings->setValue(SETTINGS::SHOWPLACEHOLDERS, false);
}
QPalette BCSettings::paletteForSetting()
{
    int index = instance()->settings->value(SETTINGS::COLORSCHEME).toInt();
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
