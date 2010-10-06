#include "options.h"
#include "ui_options.h"
#include <QFileDialog>
#include <QSettings>
QSettings bchoco_settings(QSettings::NativeFormat,QSettings::UserScope,"blackchocobo","settings",0);

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
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

void Options::on_btn_set_save_pc_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save FF7 PC Saves"),bchoco_settings.value("save_pc_path").toString());
    bchoco_settings.setValue("save_pc_path",temp);
}

void Options::on_btn_set_save_emu_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save mcd/mcr saves"),bchoco_settings.value("save_emu_path").toString());
    bchoco_settings.setValue("save_emu_path",temp);
}

void Options::on_btn_set_load_pc_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Load FF7 PC Saves From"),bchoco_settings.value("load_path").toString());
    bchoco_settings.setValue("load_path",temp);
}

void Options::on_btn_set_export_pc_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Export FF7 PC Saves"),bchoco_settings.value("export_pc").toString());
    bchoco_settings.setValue("export_pc",temp);
}
