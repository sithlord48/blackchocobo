//  SPDX-FileCopyrightText: 2010 - 2020 Chris Rizzitello <sithlord48@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

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

private:
    Ui::Options *ui;
    void loadSettings();
    void saveSettings();
    void restoreDefaultSettings();
    void initConnections();
    void updateText();
    void btn_set_char_stat_folder_clicked();
    void btn_set_default_save_clicked();
    void btn_set_load_path_clicked();
    void btn_set_save_emu_clicked();
    void btn_set_save_pc_clicked();
    void cbNativeDialogs_clicked(bool checked);
    void comboColorScheme_currentIndexChanged(int index);
    void comboAppStyle_currentTextChanged(const QString &text);
    void cbButtonsSave_clicked(bool checked);
};
