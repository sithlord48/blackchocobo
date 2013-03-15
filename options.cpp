/****************************************************************************/
//    copyright 2010-2012 Chris Rizzitello <sithlord48@gmail.com>           //
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

#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent,QSettings *config_data) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    load=false;
    //Disable the defaut_save line and selector button unless override is checked
    ui->line_default_save->setEnabled(false);
    ui->btn_set_default_save->setEnabled(false);
    settings = config_data;
    set_path_lbls();
    load=true;

    if(settings->value("font-size").isNull()){settings->setValue("font-size",QApplication::font().pointSize());}
    if(settings->value("font-family").isNull()){settings->setValue("font-family",QApplication::font().family());}

    ui->combo_font->setFont(settings->value("font-family").toString());
    ui->combo_font_size->setCurrentIndex(settings->value("font-size").toInt()-8);

    if(settings->value("show_test").toBool()){ui->cb_skip_slot_mask->setVisible(true);}
    else{ui->cb_skip_slot_mask->setVisible(false);}
    if(settings->value("override_default_save").toBool()){ui->cb_override_def_save->setChecked(Qt::Checked);}
    else{ui->cb_override_def_save->setChecked(Qt::Unchecked);}
    if(settings->value("skip_slot_mask").toBool()){ui->cb_skip_slot_mask->setChecked(Qt::Checked);}
    else{ui->cb_skip_slot_mask->setChecked(Qt::Unchecked);}
    load=false;
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
    if (!settings->value("default_save_file").isNull()){ui->line_default_save->setText(settings->value("default_save_file").toString());}
    if (!settings->value("char_stat_folder").isNull()){ui->line_char_stat_folder->setText(settings->value("char_stat_folder").toString());}
    if (!settings->value("save_pc_path").isNull()){ui->line_save_pc->setText(settings->value("save_pc_path").toString());}
    if (!settings->value("save_emu_path").isNull()){ui->line_save_emu->setText(settings->value("save_emu_path").toString());}
    if (!settings->value("load_path").isNull()){ui->line_load_path->setText(settings->value("load_path").toString());}
    if (!settings->value("export_pc").isNull()){ui->line_export_pc->setText(settings->value("export_pc").toString());}
}

void Options::on_line_save_pc_editingFinished(){settings->setValue("save_pc",ui->line_save_pc->text());}
void Options::on_btn_set_save_pc_clicked()
{
    load=true;
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save FF7 PC Saves"),settings->value("save_pc_path").toString());
    if(!temp.isNull()){settings->setValue("save_pc_path",temp);}
    set_path_lbls();
    load=false;
}


void Options::on_line_save_emu_editingFinished(){settings->setValue("save_emu",ui->line_save_emu->text());}
void Options::on_btn_set_save_emu_clicked()
{
    load=true;
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save mcd/mcr saves"),settings->value("save_emu_path").toString());
    if(!temp.isNull()){settings->setValue("save_emu_path",temp);}
    set_path_lbls();
    load=false;
}

void Options::on_line_load_path_editingFinished(){settings->setValue("load_path",ui->line_load_path->text());}
void Options::on_btn_set_load_path_clicked()
{
    load=true;
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Load FF7 PC Saves From"),settings->value("load_path").toString());
    if(!temp.isNull()){settings->setValue("load_path",temp);}
    set_path_lbls();
    load=false;
}


void Options::on_line_export_pc_editingFinished(){settings->setValue("export_pc",ui->line_export_pc->text());}
void Options::on_btn_set_export_pc_clicked()
{
    load=true;
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Export FF7 PC Saves"),settings->value("export_pc").toString());
    if(!temp.isNull()){settings->setValue("export_pc",temp);}
    set_path_lbls();
    load=false;
}

void Options::on_line_default_save_editingFinished(){settings->setValue("default_save_file",ui->line_default_save->text());}
void Options::on_btn_set_default_save_clicked()
{
    load=true;
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A Default Save Game (Must Be Raw PSX)"),settings->value("default_save_file").toString());
    if(!temp.isNull()){settings->setValue("default_save_file",temp);}
    set_path_lbls();
    load=false;
}

void Options::on_line_char_stat_folder_editingFinished(){settings->setValue("char_stat_folder",ui->line_char_stat_folder->text());}

void Options::on_btn_set_char_stat_folder_clicked()
{
    load=true;
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Location To Save Character Stat Files"),settings->value("char_stat_folder").toString());
    if(!temp.isNull()){settings->setValue("char_stat_folder",temp);}
    set_path_lbls();
    load=false;
}
/*~~~~~~~~~~~~~~~~~~~~Font Stuff~~~~~~~~~~~~~~~~~~~~~~*/

void Options::on_combo_font_currentIndexChanged(QString family)
{if(!load){
    settings->setValue("font-family",family);
    QApplication::setFont(QFont(family,settings->value("font-size").toInt(),-1,false));
}}

void Options::on_combo_font_size_currentIndexChanged(int index)
{
    if(!load)
    {
        index+=8;//adjust so index 0 = starting font size.
        settings->setValue("font-size",index);
        QApplication::setFont(QFont(settings->value("font-family").toString(),index,-1,false));
    }
    else{ui->combo_font_size->setCurrentIndex(settings->value("font-size").toInt()-8);}
}
/*~~~~~~~~~~~~~~~~~~RESET STUFF~~~~~~~~~~~~~~~~~~~*/
void Options::on_reset_default_save_location_clicked()
{
    ui->cb_override_def_save->setChecked(Qt::Unchecked);
    settings->remove("default_save_file");
    ui->line_default_save->clear();
}

void Options::on_reset_char_stat_folder_clicked()
{
    settings->setValue("char_stat_folder",QString(QDir::homePath()));
    set_path_lbls();
}

void Options::on_reset_font_clicked()
{
    ui->combo_font->setCurrentFont(QFont("ubuntu",9,-1,false));
    ui->combo_font_size->setCurrentIndex(1);
    settings->remove("font-family"); settings->remove("font-size");
}

void Options::on_cb_skip_slot_mask_toggled(bool checked){if(!load){settings->setValue("skip_slot_mask",checked);}}
void Options::on_cb_override_def_save_toggled(bool checked)
{
    if(!load){settings->setValue("override_default_save",checked);}
    if(checked)
    {
        ui->line_default_save->setEnabled(true);
        ui->btn_set_default_save->setEnabled(true);
    }
    else
    {
        ui->line_default_save->setEnabled(false);
        ui->btn_set_default_save->setEnabled(false);
    }
}
/*~~~~~~~~~~~~~~~~CLOSE BUTTON~~~~~~~~~~~~~~~~~~*/
void Options::on_pushButton_clicked(){this->close();}
