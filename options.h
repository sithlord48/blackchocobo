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

#pragma once

#include <QDialog>
#include <QSettings>
#include <QDir>
namespace Ui
{
class Options;
}

namespace SETTINGS {
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
    inline const static QString SCALE = QStringLiteral("scale");
    inline const static QString ENABLETEST = QStringLiteral("show_test");
    inline const static QString WORLDMAPADVANCED = QStringLiteral("worldMapAdvanced");
    inline const static QString USENATIVEDIALOGS = QStringLiteral("useNativeDialogs");
    inline const static QString SIDEBARURLS = QStringLiteral("sidebarUrls");
}

class Options : public QDialog
{
    Q_OBJECT

public:
    
    explicit Options(QWidget *parent = nullptr, QSettings *config_data = nullptr);
    ~Options();

protected:
    void changeEvent(QEvent *e);
signals:
    void requestLanguageChange(const QVariant &data);
    void requestChangeNativeDialog(bool UseNativeDialogs);
private slots:
    void on_btn_set_char_stat_folder_clicked();
    void on_btn_set_default_save_clicked();
    void on_btn_set_load_path_clicked();
    void on_btn_set_save_emu_clicked();
    void on_btn_set_save_pc_clicked();
    void on_cb_override_def_save_toggled(bool checked);
    void on_comboLanguage_currentIndexChanged(const QString &arg1);
    void on_cbNativeDialogs_clicked(bool checked);
    void on_btnEditSideBarItems_clicked();
private:
    Ui::Options *ui;
    QSettings *settings;
    void loadSettings();
    void saveSettings();
    void restoreDefaultSettings();
    void cleanSettings();
    inline static const QStringList validSettingsNames = {
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
        SETTINGS::SCALE,
        SETTINGS::ENABLETEST,
        SETTINGS::WORLDMAPADVANCED,
        SETTINGS::USENATIVEDIALOGS,
        SETTINGS::SIDEBARURLS
    };
};
