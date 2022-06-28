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
#include <QStyleFactory>
#include <QTranslator>
#include <QUrl>

#include <FF7SaveInfo.h>

#include "options.h"
#include "bcdialog.h"
#include "../bcsettings.h"
#include "ui_options.h"

Options::Options(QWidget *parent) : QDialog(parent)
  , ui(new Ui::Options)
{
    ui->setupUi(this);
    connect(BCSettings::instance(), &BCSettings::settingsChanged, this, &Options::loadSettings);
    initConnections();
    int fmh = fontMetrics().height();
    QSize iconSize(fmh, fmh);
    updateText();
    const QList<QAbstractButton*> buttons = ui->buttonBox->buttons();
    for (QAbstractButton *btn : buttons)
         btn->setIconSize(iconSize);

    QDir dir (BCSettings::instance()->value(SETTINGS::LANGPATH).toString());
    QStringList langList = dir.entryList(QStringList("bchoco_*.qm"), QDir::Files, QDir::Name);
    for (const QString &translation : langList) {
        auto translator = new QTranslator;
        std::ignore = translator->load(translation, dir.absolutePath());
        QString lang = translation.mid(7, 2);
        ui->comboLanguage->addItem(translator->translate("MainWindow", "TRANSLATE TO YOUR LANGUAGE NAME"), lang);
    }
    ui->comboLanguage->setCurrentIndex(ui->comboLanguage->findData(BCSettings::instance()->value(SETTINGS::LANG, QStringLiteral("en"))));
    ui->comboLanguage->setVisible(ui->comboLanguage->count());
    ui->lblLanguage->setVisible(ui->comboLanguage->count());
    ui->comboAppStyle->addItems(QStyleFactory::keys());

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, [this](const QAbstractButton * button){
        if (button == ui->buttonBox->button(QDialogButtonBox::Apply)) {
            disconnect(BCSettings::instance(), &BCSettings::settingsChanged, this, &Options::loadSettings);
            saveSettings();
            done(1);
        }
        if (button == ui->buttonBox->button(QDialogButtonBox::Cancel))
            done(0);

        if (button == ui->buttonBox->button(QDialogButtonBox::Reset))
            loadSettings();

        if (button == ui->buttonBox->button(QDialogButtonBox::RestoreDefaults))
            restoreDefaultSettings();
    });

    loadSettings();

    if(parent) {
        move(parent->x() + ((parent->width() -  sizeHint().width()) / 2), parent->y() + ((parent->sizeHint().height() - sizeHint().height()) / 2));
    }
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
        updateText();
        break;
    default:
        break;
    }
}
void Options::loadSettings()
{
    ui->defaultSaveLayout->setVisible(false);
    ui->line_default_save->setText(BCSettings::instance()->value(SETTINGS::DEFAULTSAVE, QString()).toString());
    ui->line_char_stat_folder->setText(BCSettings::instance()->value(SETTINGS::STATFOLDER, QString()).toString());
    ui->line_save_pc->setText(BCSettings::instance()->value(SETTINGS::PCSAVEPATH, QString()).toString());
    ui->line_save_emu->setText(BCSettings::instance()->value(SETTINGS::EMUSAVEPATH, QString()).toString());
    ui->line_load_path->setText(BCSettings::instance()->value(SETTINGS::LOADPATH, QString()).toString());
    ui->cbEditableCombos->setChecked(BCSettings::instance()->value(SETTINGS::EDITABLECOMBOS, true).toBool());
    ui->cbCharEditorAdvanced->setChecked(BCSettings::instance()->value(SETTINGS::CHARADVANCED, false).toBool());
    ui->cbChocoboEditorAdvanced->setChecked(BCSettings::instance()->value(SETTINGS::CHOCOADVANCED, false).toBool());
    ui->cbLocationViewerAdvanced->setChecked(BCSettings::instance()->value(SETTINGS::LOCVIEWADVANCED, false).toBool());
    ui->cbTestDataEnabled->setChecked(BCSettings::instance()->value(SETTINGS::ENABLETEST, false).toBool());
    ui->cbGameProgressAdvanced->setChecked(BCSettings::instance()->value(SETTINGS::PROGRESSADVANCED, false).toBool());
    ui->cbOptionsShowMapping->setChecked(BCSettings::instance()->value(SETTINGS::ALWAYSSHOWCONTROLLERMAP, false).toBool());
    ui->cbWorldMapAdvanced->setChecked(BCSettings::instance()->value(SETTINGS::WORLDMAPADVANCED, false).toBool());
    ui->comboRegion->setCurrentText(BCSettings::instance()->value (SETTINGS::REGION, QStringLiteral("NTSC-U")).toString());
    ui->cb_override_def_save->setChecked(BCSettings::instance()->value(SETTINGS::CUSTOMDEFAULTSAVE, false).toBool());
    ui->cbAutoGrowth->setChecked(BCSettings::instance()->value(SETTINGS::AUTOGROWTH, true).toBool());
    ui->comboLanguage->setCurrentIndex(ui->comboLanguage->findData(BCSettings::instance()->value(SETTINGS::LANG)));
    ui->cbNativeDialogs->setChecked(BCSettings::instance()->value(SETTINGS::USENATIVEDIALOGS).toBool());
    ui->btnEditSideBarItems->setVisible(!ui->cbNativeDialogs->isChecked());
    ui->comboColorScheme->setCurrentIndex(BCSettings::instance()->value(SETTINGS::COLORSCHEME).toInt());
    ui->comboAppStyle->setCurrentText(BCSettings::instance()->value(SETTINGS::APPSTYLE).toString());
    ui->cbCapItemQty->setChecked(BCSettings::instance()->value(SETTINGS::ITEMCAP99).toBool());
    adjustSize();
}

void Options::saveSettings()
{
    BCSettings::instance()->setValue(SETTINGS::PCSAVEPATH, ui->line_save_pc->text());
    BCSettings::instance()->setValue(SETTINGS::EMUSAVEPATH, ui->line_save_emu->text());
    BCSettings::instance()->setValue(SETTINGS::LOADPATH, ui->line_load_path->text());
    BCSettings::instance()->setValue(SETTINGS::DEFAULTSAVE, ui->line_default_save->text());
    BCSettings::instance()->setValue(SETTINGS::STATFOLDER, ui->line_char_stat_folder->text());
    BCSettings::instance()->setValue(SETTINGS::CUSTOMDEFAULTSAVE, ui->cb_override_def_save->isChecked());
    BCSettings::instance()->setValue(SETTINGS::CHARADVANCED, ui->cbCharEditorAdvanced->isChecked());
    BCSettings::instance()->setValue(SETTINGS::CHOCOADVANCED, ui->cbChocoboEditorAdvanced->isChecked());
    BCSettings::instance()->setValue(SETTINGS::PROGRESSADVANCED, ui->cbGameProgressAdvanced->isChecked());
    BCSettings::instance()->setValue(SETTINGS::ALWAYSSHOWCONTROLLERMAP, ui->cbOptionsShowMapping->isChecked());
    BCSettings::instance()->setValue(SETTINGS::ENABLETEST, ui->cbTestDataEnabled->isChecked());
    BCSettings::instance()->setValue(SETTINGS::LOCVIEWADVANCED, ui->cbLocationViewerAdvanced->isChecked());
    BCSettings::instance()->setValue(SETTINGS::WORLDMAPADVANCED, ui->cbWorldMapAdvanced->isChecked());
    BCSettings::instance()->setValue(SETTINGS::EDITABLECOMBOS, ui->cbEditableCombos->isChecked());
    BCSettings::instance()->setValue(SETTINGS::REGION, ui->comboRegion->currentText());
    BCSettings::instance()->setValue(SETTINGS::AUTOGROWTH, ui->cbAutoGrowth->isChecked());
    BCSettings::instance()->setValue(SETTINGS::LANG, ui->comboLanguage->currentData());
    BCSettings::instance()->setValue(SETTINGS::USENATIVEDIALOGS, ui->cbNativeDialogs->isChecked());
    BCSettings::instance()->setValue(SETTINGS::COLORSCHEME, ui->comboColorScheme->currentIndex());
    BCSettings::instance()->setValue(SETTINGS::APPSTYLE, ui->comboAppStyle->currentText());
    BCSettings::instance()->setValue(SETTINGS::ITEMCAP99, ui->cbCapItemQty->isChecked());
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
    ui->cbAutoGrowth->setChecked(true);
    ui->comboLanguage->setCurrentIndex(ui->comboLanguage->findData(QStringLiteral("en")));
    ui->cbNativeDialogs->setChecked(false);
    ui->btnEditSideBarItems->setVisible(true);
    ui->comboAppStyle->setCurrentText(QStringLiteral("Fusion"));
    ui->cbCapItemQty->setChecked(false);
}

void Options::initConnections()
{
    connect(ui->btn_set_char_stat_folder, &QPushButton::clicked, this, &Options::btn_set_char_stat_folder_clicked);
    connect(ui->btn_set_default_save, &QPushButton::clicked, this, &Options::btn_set_default_save_clicked);
    connect(ui->btn_set_load_path, &QPushButton::clicked, this, &Options::btn_set_load_path_clicked);
    connect(ui->btn_set_save_emu, &QPushButton::clicked, this, &Options::btn_set_save_emu_clicked);
    connect(ui->btn_set_save_pc, &QPushButton::clicked, this, &Options::btn_set_save_pc_clicked);
    connect(ui->cbNativeDialogs, &QCheckBox::toggled, this, &Options::cbNativeDialogs_clicked);
    connect(ui->comboColorScheme, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Options::comboColorScheme_currentIndexChanged);
    connect(ui->comboAppStyle, &QComboBox::textActivated, this, &Options::comboAppStyle_currentTextChanged);
    connect(ui->cb_override_def_save, &QCheckBox::toggled, ui->defaultSaveLayout, &QFrame::setVisible);

    connect(ui->btnEditSideBarItems, &QPushButton::clicked, this, [this]{
        BCDialog::editSideBarPaths(this);
    });

    connect(ui->comboLanguage, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]{
        emit requestLanguageChange(ui->comboLanguage->currentData());
    });
}

void Options::updateText()
{
    ui->buttonBox->button(QDialogButtonBox::RestoreDefaults)->setToolTip(tr("Reset values to defaults"));
    ui->buttonBox->button(QDialogButtonBox::Reset)->setToolTip(tr("Reset values to stored settings"));
    ui->buttonBox->button(QDialogButtonBox::Apply)->setToolTip(tr("Close and save changes"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setToolTip(tr("Close and forget changes"));
}

void Options::btn_set_save_pc_clicked()
{
    QString temp = BCDialog::getExistingDirectory(this, tr("Select A Directory To Save FF7 PC Saves"), ui->line_save_pc->text(), ui->line_save_pc->text());
    if (!temp.isEmpty())
        ui->line_save_pc->setText(temp);
}

void Options::btn_set_save_emu_clicked()
{
    QString temp = BCDialog::getExistingDirectory(this, tr("Select A Directory To Save mcd/mcr saves"), ui->line_save_emu->text(), ui->line_save_emu->text());
    if (!temp.isEmpty())
        ui->line_save_emu->setText(temp);
}

void Options::btn_set_load_path_clicked()
{
    QString temp = BCDialog::getExistingDirectory(this, tr("Select A Directory To Load FF7 PC Saves From"), ui->line_load_path->text(), ui->line_load_path->text());
    if (!temp.isEmpty())
        ui->line_load_path->setText(temp);
}

void Options::btn_set_default_save_clicked()
{
    QString temp = BCDialog::getOpenFileName(this, tr("Select A Default Save Game (Must Be Raw PSX)"), QFileInfo(BCSettings::instance()->value(SETTINGS::DEFAULTSAVE).toString()).path(), FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PSX), QFile(BCSettings::instance()->value(SETTINGS::DEFAULTSAVE).toString()).fileName());
    if(!temp.isEmpty())
        ui->line_default_save->setText(temp);
}

void Options::btn_set_char_stat_folder_clicked()
{
    QString temp = BCDialog::getExistingDirectory(this, tr("Select A Location To Save Character Stat Files"), ui->line_char_stat_folder->text(), ui->line_char_stat_folder->text());
    if (!temp.isNull())
        ui->line_char_stat_folder->setText(temp);
}

void Options::cbNativeDialogs_clicked(bool checked)
{
    ui->btnEditSideBarItems->setVisible(!checked);
    emit requestChangeNativeDialog(checked);
}

void Options::comboColorScheme_currentIndexChanged(int index)
{
    BCSettings::instance()->setValue(SETTINGS::COLORSCHEME, index);
    qApp->setPalette(BCSettings::instance()->paletteForSetting());
}

void Options::comboAppStyle_currentTextChanged(const QString &text)
{
    BCSettings::instance()->setValue(SETTINGS::APPSTYLE, text);
    qApp->setStyle(QStyleFactory::create(text));
}
