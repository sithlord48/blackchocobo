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

#include <QStandardPaths>
#include <QStyle>
#include <QTranslator>
#include <QUrl>
#include "options.h"
#include "bcdialog.h"
#include "ui_options.h"
#include "ff7tk/data/FF7SaveInfo.h"

Options::Options(QWidget *parent, QSettings *config_data) :
    QDialog(parent)
  , ui(new Ui::Options)
  , settings(config_data)
{
    ui->setupUi(this);
    int fmh = fontMetrics().height();
    QSize iconSize(fmh, fmh);
    ui->buttonBox->button(QDialogButtonBox::Help)->setText(tr("C&leanup"));
    ui->buttonBox->button(QDialogButtonBox::Help)->setIcon(QIcon());
    ui->buttonBox->button(QDialogButtonBox::Help)->setToolTip(tr("Remove invalid entries from the stored settings file"));
    ui->buttonBox->button(QDialogButtonBox::RestoreDefaults)->setToolTip(tr("Reset values to defaults"));
    ui->buttonBox->button(QDialogButtonBox::Reset)->setToolTip(tr("Reset values to stored settings"));
    ui->buttonBox->button(QDialogButtonBox::Apply)->setToolTip(tr("Close and save changes"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setToolTip(tr("Close and forget changes"));
    for (QAbstractButton *btn : ui->buttonBox->buttons())
         btn->setIconSize(iconSize);
    ui->lblPixNormal->setPixmap(QPixmap(":/icon/bchoco").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lblPixScaled->setPixmap(QPixmap(":/icon/bchoco").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QDir dir(QStringLiteral("%1/lang").arg(settings->value(SETTINGS::LANGPATH).toString()));
    QStringList langList = dir.entryList(QStringList("bchoco_*.qm"), QDir::Files, QDir::Name);
    for (const QString &translation : langList) {
        auto translator = new QTranslator;
        translator->load(translation, dir.absolutePath());
        QString lang = translation.mid(7, 2);
        ui->comboLanguage->addItem(translator->translate("MainWindow", "TRANSLATE TO YOUR LANGUAGE NAME"), lang);
        ui->comboLanguage->setCurrentIndex(ui->comboLanguage->findData(settings->value(SETTINGS::LANG, QStringLiteral("en"))));
    }
    ui->comboLanguage->setVisible(ui->comboLanguage->count());
    ui->lblLanguage->setVisible(ui->comboLanguage->count());

    connect(ui->sliderScale, &QSlider::valueChanged, this, [this](int value){
        value = int(((value * 0.25) + 0.5) * 100);
        ui->labelScale->setText(QStringLiteral("%1%").arg(value, 3, 10, QChar('0')));
        value = int(64 * (value / 100.0));
        ui->lblPixScaled->setPixmap(QPixmap(":/icon/bchoco").scaled(value, value, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    });

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, [this](QAbstractButton * button){
        if (button == ui->buttonBox->button(QDialogButtonBox::Apply)) {
            saveSettings();
            done(1);
        }
        if (button == ui->buttonBox->button(QDialogButtonBox::Cancel))
            done(0);

        if (button == ui->buttonBox->button(QDialogButtonBox::Reset))
            loadSettings();

        if (button == ui->buttonBox->button(QDialogButtonBox::RestoreDefaults))
            restoreDefaultSettings();

        if (button == ui->buttonBox->button(QDialogButtonBox::Help))
            cleanSettings();
    });

    loadSettings();
    setGeometry(x(), y(), width(), minimumHeight());
}

Options::~Options()
{
    delete ui;
}

void Options::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void Options::loadSettings()
{
    ui->defaultSaveLayout->setVisible(false);
    ui->line_default_save->setText(settings->value(SETTINGS::DEFAULTSAVE, QString()).toString());
    ui->line_char_stat_folder->setText(settings->value(SETTINGS::STATFOLDER, QString()).toString());
    ui->line_save_pc->setText(settings->value(SETTINGS::PCSAVEPATH, QString()).toString());
    ui->line_save_emu->setText(settings->value(SETTINGS::EMUSAVEPATH, QString()).toString());
    ui->line_load_path->setText(settings->value(SETTINGS::LOADPATH, QString()).toString());
    ui->cbEditableCombos->setChecked(settings->value(SETTINGS::EDITABLECOMBOS, true).toBool());
    ui->cbCharEditorAdvanced->setChecked(settings->value(SETTINGS::CHARADVANCED, false).toBool());
    ui->cbChocoboEditorAdvanced->setChecked(settings->value(SETTINGS::CHOCOADVANCED, false).toBool());
    ui->cbLocationViewerAdvanced->setChecked(settings->value(SETTINGS::LOCVIEWADVANCED, false).toBool());
    ui->cbTestDataEnabled->setChecked(settings->value(SETTINGS::ENABLETEST, false).toBool());
    ui->cbGameProgressAdvanced->setChecked(settings->value(SETTINGS::PROGRESSADVANCED, false).toBool());
    ui->cbOptionsShowMapping->setChecked(settings->value(SETTINGS::ALWAYSSHOWCONTROLLERMAP, false).toBool());
    ui->cbWorldMapAdvanced->setChecked(settings->value(SETTINGS::WORLDMAPADVANCED, false).toBool());
    ui->comboRegion->setCurrentText(settings->value (SETTINGS::REGION, QStringLiteral("NTSC-U")).toString());
    ui->cb_override_def_save->setChecked(settings->value(SETTINGS::CUSTOMDEFAULTSAVE, false).toBool());
    ui->sliderScale->setValue(int((settings->value(SETTINGS::SCALE, 1.00).toDouble() - 0.50) / 0.25));
    ui->cbAutoGrowth->setChecked(settings->value(SETTINGS::AUTOGROWTH, true).toBool());
    ui->comboLanguage->setCurrentIndex(ui->comboLanguage->findData(settings->value(SETTINGS::LANG)));
    ui->cbNativeDialogs->setChecked(settings->value(SETTINGS::USENATIVEDIALOGS).toBool());
    ui->btnEditSideBarItems->setVisible(!ui->cbNativeDialogs->isChecked());
}

void Options::saveSettings()
{
    settings->setValue(SETTINGS::PCSAVEPATH, ui->line_save_pc->text());
    settings->setValue(SETTINGS::EMUSAVEPATH, ui->line_save_emu->text());
    settings->setValue(SETTINGS::LOADPATH, ui->line_load_path->text());
    settings->setValue(SETTINGS::DEFAULTSAVE, ui->line_default_save->text());
    settings->setValue(SETTINGS::STATFOLDER, ui->line_char_stat_folder->text());
    settings->setValue(SETTINGS::CUSTOMDEFAULTSAVE, ui->cb_override_def_save->isChecked());
    settings->setValue(SETTINGS::CHARADVANCED, ui->cbCharEditorAdvanced->isChecked());
    settings->setValue(SETTINGS::CHOCOADVANCED, ui->cbChocoboEditorAdvanced->isChecked());
    settings->setValue(SETTINGS::PROGRESSADVANCED, ui->cbGameProgressAdvanced->isChecked());
    settings->setValue(SETTINGS::ALWAYSSHOWCONTROLLERMAP, ui->cbOptionsShowMapping->isChecked());
    settings->setValue(SETTINGS::ENABLETEST, ui->cbTestDataEnabled->isChecked());
    settings->setValue(SETTINGS::LOCVIEWADVANCED, ui->cbLocationViewerAdvanced->isChecked());
    settings->setValue(SETTINGS::WORLDMAPADVANCED, ui->cbWorldMapAdvanced->isChecked());
    settings->setValue(SETTINGS::EDITABLECOMBOS, ui->cbEditableCombos->isChecked());
    settings->setValue(SETTINGS::REGION, ui->comboRegion->currentText());
    settings->setValue(SETTINGS::SCALE, ((ui->sliderScale->value() * 0.25) + 0.5));
    settings->setValue(SETTINGS::AUTOGROWTH, ui->cbAutoGrowth->isChecked());
    settings->setValue(SETTINGS::LANG, ui->comboLanguage->currentData());
    settings->setValue(SETTINGS::USENATIVEDIALOGS, ui->cbNativeDialogs->isChecked());
}

void Options::restoreDefaultSettings()
{
    ui->defaultSaveLayout->setVisible(false);
    ui->line_default_save->setText(QString());
    ui->line_char_stat_folder->setText(QDir::homePath());
    ui->line_save_pc->setText(QDir::homePath());
    ui->line_save_emu->setText(QDir::homePath());
    ui->line_load_path->setText(QDir::homePath());
    ui->cbEditableCombos->setChecked(true);
    ui->cbCharEditorAdvanced->setChecked(false);
    ui->cbChocoboEditorAdvanced->setChecked(false);
    ui->cbLocationViewerAdvanced->setChecked(false);
    ui->cbTestDataEnabled->setChecked(false);
    ui->cbGameProgressAdvanced->setChecked(false);
    ui->cbOptionsShowMapping->setChecked(false);
    ui->cbWorldMapAdvanced->setChecked(false);
    ui->comboRegion->setCurrentText(QStringLiteral("NTSC-U"));
    ui->cb_override_def_save->setChecked(false);
    ui->sliderScale->setValue(2);
    ui->cbAutoGrowth->setChecked(true);
    ui->comboLanguage->setCurrentIndex(ui->comboLanguage->findData(QStringLiteral("en")));
    ui->cbNativeDialogs->setChecked(true);
}

void Options::cleanSettings()
{
    for(const QString &key : settings->allKeys()) {
        if(!validSettingsNames.contains(key))
            settings->remove(key);
    }
}
void Options::on_btn_set_save_pc_clicked()
{
    QString temp = BCDialog::getExistingDirectory(this, settings, tr("Select A Directory To Save FF7 PC Saves"), ui->line_save_pc->text(), ui->line_save_pc->text());
    if (!temp.isEmpty())
        ui->line_save_pc->setText(temp);
}

void Options::on_btn_set_save_emu_clicked()
{
    QString temp = BCDialog::getExistingDirectory(this, settings, tr("Select A Directory To Save mcd/mcr saves"), ui->line_save_emu->text(), ui->line_save_emu->text());
    if (!temp.isEmpty())
        ui->line_save_emu->setText(temp);
}

void Options::on_btn_set_load_path_clicked()
{
    QString temp = BCDialog::getExistingDirectory(this, settings, tr("Select A Directory To Load FF7 PC Saves From"), ui->line_load_path->text(), ui->line_load_path->text());
    if (!temp.isEmpty())
        ui->line_load_path->setText(temp);
}

void Options::on_btn_set_default_save_clicked()
{
    QString temp = BCDialog::getOpenFileName(this, settings, tr("Select A Default Save Game (Must Be Raw PSX)"), QFileInfo(settings->value(SETTINGS::DEFAULTSAVE).toString()).path(), FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PSX), QFile(settings->value(SETTINGS::DEFAULTSAVE).toString()).fileName());
    if(!temp.isEmpty())
        ui->line_default_save->setText(temp);
}

void Options::on_btn_set_char_stat_folder_clicked()
{
    QString temp = BCDialog::getExistingDirectory(this, settings, tr("Select A Location To Save Character Stat Files"), ui->line_char_stat_folder->text(), ui->line_char_stat_folder->text());
    if (!temp.isNull())
        ui->line_char_stat_folder->setText(temp);
}

void Options::on_cb_override_def_save_toggled(bool checked)
{
    ui->defaultSaveLayout->setVisible(checked);
}

void Options::on_comboLanguage_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    emit requestLanguageChange(ui->comboLanguage->currentData());
}

void Options::on_cbNativeDialogs_clicked(bool checked)
{
    ui->btnEditSideBarItems->setVisible(!checked);
    emit requestChangeNativeDialog(checked);
}

void Options::on_btnEditSideBarItems_clicked()
{
    BCDialog::editSideBarPaths(this, settings);
}
