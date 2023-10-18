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
#pragma once
#include <QColor>
#include <QObject>
#include <QSettings>
#include <QVariant>
struct SETTINGS {
    inline const static QString MAINGEOMETRY = QStringLiteral("MainGeometry");
    inline const static QString AUTOGROWTH = QStringLiteral("autochargrowth");
    inline const static QString CHARADVANCED = QStringLiteral("charEditorAdvanced");
    inline const static QString STATFOLDER = QStringLiteral("char_stat_folder");
    inline const static QString CHOCOADVANCED = QStringLiteral("chocoboEditorAdvanced");
    inline const static QString DEFAULTSAVE = QStringLiteral("default_save");
    inline const static QString EDITABLECOMBOS = QStringLiteral("editableCombos");
    inline const static QString PROGRESSADVANCED = QStringLiteral("gameProgressAdvanced");
    inline const static QString LANG = QStringLiteral("lang");
    inline const static QString LANGPATH = QStringLiteral("langPath");
    inline const static QString LOADPATH = QStringLiteral("load_path");
    inline const static QString LOCVIEWADVANCED = QStringLiteral("locationViewerAdvanced");
    inline const static QString ALWAYSSHOWCONTROLLERMAP = QStringLiteral("optionsShowMapping");
    inline const static QString CUSTOMDEFAULTSAVE = QStringLiteral("override_default_save");
    inline const static QString REGION = QStringLiteral("region");
    inline const static QString EMUSAVEPATH = QStringLiteral("save_emu_path");
    inline const static QString PCSAVEPATH = QStringLiteral("save_pc_path");
    inline const static QString ENABLETEST = QStringLiteral("show_test");
    inline const static QString WORLDMAPADVANCED = QStringLiteral("worldMapAdvanced");
    inline const static QString USENATIVEDIALOGS = QStringLiteral("useNativeDialogs");
    inline const static QString SIDEBARURLS = QStringLiteral("sidebarUrls");
    inline const static QString COLORSCHEME = QStringLiteral("colorScheme");
    inline const static QString APPSTYLE = QStringLiteral("appStyle");
    inline const static QString ITEMCAP99 = QStringLiteral("alwaysCapItemsAt99");
    inline const static QString SHOWPLACEHOLDERS = QStringLiteral("showPlaceHolders");
    inline const static QString MAKEBACKUPS = QStringLiteral("createBackups");
};

class BCSettings : public QObject
{
    Q_OBJECT
public:
    static BCSettings *instance();
    static void setValue(const QString &setting = QString(), const QVariant &value = QVariant());
    static QVariant value(const QString &setting = QString(), const QVariant &defaultValue = QVariant());
    static void restoreDefaultSettings();
    static QPalette paletteForSetting();
signals:
    void settingsChanged();
private:
    explicit BCSettings(QObject *parent = nullptr);
    BCSettings *operator = (BCSettings &other) = delete;
    BCSettings(const BCSettings &other) = delete;
    ~BCSettings() = default;
    void initSettings();
    void cleanSettings();
    QSettings *settings = nullptr;
    const QStringList validSettingsNames = {
        SETTINGS::MAINGEOMETRY,
        SETTINGS::AUTOGROWTH,
        SETTINGS::CHARADVANCED,
        SETTINGS::STATFOLDER,
        SETTINGS::CHOCOADVANCED,
        SETTINGS::DEFAULTSAVE,
        SETTINGS::EDITABLECOMBOS,
        SETTINGS::PROGRESSADVANCED,
        SETTINGS::LANG,
        SETTINGS::LANGPATH,
        SETTINGS::LOADPATH,
        SETTINGS::LOCVIEWADVANCED,
        SETTINGS::ALWAYSSHOWCONTROLLERMAP,
        SETTINGS::CUSTOMDEFAULTSAVE,
        SETTINGS::REGION,
        SETTINGS::EMUSAVEPATH,
        SETTINGS::PCSAVEPATH,
        SETTINGS::ENABLETEST,
        SETTINGS::WORLDMAPADVANCED,
        SETTINGS::USENATIVEDIALOGS,
        SETTINGS::SIDEBARURLS,
        SETTINGS::COLORSCHEME,
        SETTINGS::APPSTYLE,
        SETTINGS::ITEMCAP99,
        SETTINGS::SHOWPLACEHOLDERS,
        SETTINGS::MAKEBACKUPS
    };
    //Theme Colors
    inline static const QColor lightWindow = QColor(252, 252, 252);
    inline static const QColor lightDisableWindow = QColor(192, 192, 192);
    inline static const QColor lightText = QColor(35, 38, 39);
    inline static const QColor lightButton = QColor(239, 240, 241);
    inline static const QColor lightDisableButton = QColor(180, 181, 182);
    inline static const QColor lightHighlight = QColor(61,174,233);
    inline static const QColor lightInactiveText = QColor(127,140,141);
    inline static const QColor lightLink = QColor(41, 128, 185);
    inline static const QColor lightPlaceholderText = QColor(96, 96, 96);
    inline static const QColor darkWindow = QColor(35, 38, 41);
    inline static const QColor darkDisableWindow = QColor(100, 100, 100);
    inline static const QColor darkText = QColor(239, 240, 241);
    inline static const QColor darkDisableButton = QColor(67, 74, 81);
    inline static const QColor darkButton = QColor(49, 54, 59);
    inline static const QColor darkHighlight = QColor(61,174,233);
    inline static const QColor darkInactiveText = QColor(189, 195, 199);
    inline static const QColor darkLink = QColor(41, 128, 185);
    inline static const QColor darkPlaceholderText = QColor(196, 196, 196);
};
