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

class Options : public QDialog
{
    Q_OBJECT

public:
    
    explicit Options(QWidget *parent = nullptr);
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
    void on_comboColorScheme_currentIndexChanged(int index);
    
private:
    Ui::Options *ui;
    void loadSettings();
    void saveSettings();
    void restoreDefaultSettings();
};
