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
    set_path_lbls();
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

void Options::set_path_lbls()
{
    if (!bchoco_settings.value("default_save_file").isNull()){ui->lbl_defalut_save->setText(bchoco_settings.value("default_save_file").toString());}
    if (!bchoco_settings.value("char_stat_folder").isNull()){ui->lbl_char_stat_folder->setText(bchoco_settings.value("char_stat_folder").toString());}
    if (!bchoco_settings.value("save_pc_path").isNull()){ui->lbl_save_pc->setText(bchoco_settings.value("save_pc_path").toString());}
    if (!bchoco_settings.value("save_emu_path").isNull()){ui->lbl_save_emu->setText(bchoco_settings.value("save_emu_path").toString());}
    if (!bchoco_settings.value("load_path").isNull()){ui->lbl_load_path->setText(bchoco_settings.value("load_path").toString());}
    if (!bchoco_settings.value("export_pc").isNull()){ui->lbl_export_pc->setText(bchoco_settings.value("export_pc").toString());}
}

void Options::on_btn_set_save_pc_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save FF7 PC Saves"),bchoco_settings.value("save_pc_path").toString());
    if(!temp.isNull()){bchoco_settings.setValue("save_pc_path",temp);}
    set_path_lbls();
}
void Options::on_btn_set_save_emu_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save mcd/mcr saves"),bchoco_settings.value("save_emu_path").toString());
    if(!temp.isNull()){bchoco_settings.setValue("save_emu_path",temp);}
    set_path_lbls();
}

void Options::on_btn_set_load_pc_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Load FF7 PC Saves From"),bchoco_settings.value("load_path").toString());
    if(!temp.isNull()){bchoco_settings.setValue("load_path",temp);}
    set_path_lbls();
}
void Options::on_btn_set_export_pc_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Export FF7 PC Saves"),bchoco_settings.value("export_pc").toString());
    if(!temp.isNull()){bchoco_settings.setValue("export_pc",temp);}
    set_path_lbls();
}

void Options::on_btn_set_default_save_clicked()
{
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A Default Save Game (Must Be Raw PSX)"),bchoco_settings.value("default_save_file").toString());
    if(!temp.isNull()){bchoco_settings.setValue("default_save_file",temp);}
    set_path_lbls();
}
void Options::on_btn_set_char_stat_folder_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Location To Save Character Stat Files"),bchoco_settings.value("char_stat_folder").toString());
    if(!temp.isNull()){bchoco_settings.setValue("char_stat_folder",temp);}
    set_path_lbls();
}
/*~~~~~~~~~~~~~~~~CLOSE BUTTON~~~~~~~~~~~~~~~~~~*/
void Options::on_pushButton_clicked()
{
    this->close();
}
