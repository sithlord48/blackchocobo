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
	ui->line_default_save->setVisible(false);
	ui->btn_set_default_save->setVisible(false);
	ui->reset_default_save_location->setVisible(false);

	settings = config_data;
	set_path_lbls();
	load=true;
	ui->cbCharEditorAdvanced->setChecked(settings->value("charEditorAdvanced").toBool());
	ui->cbChocoboEditorAdvanced->setChecked(settings->value("chocoboEditorAdvanced").toBool());
	ui->cbLocationViewerAdvanced->setChecked(settings->value("locationViewerAdvanced").toBool());
	ui->cbTestDataEnabled->setChecked(settings->value("show_test").toBool());
	ui->cbGameProgressAdvanced->setChecked(settings->value("gameProgressAdvanced").toBool());
	ui->cbOptionsShowMapping->setChecked(settings->value("optionsShowMapping").toBool());
	ui->cb_skip_slot_mask->setChecked(settings->value("skip_slot_mask").toBool());
	ui->cbWorldMapAdvanced->setChecked(settings->value("worldMapAdvanced").toBool());
	ui->cb_override_def_save->setChecked(settings->value("override_default_save").toBool());
	ui->linePs3Key->setText(settings->value("ps3Key").toByteArray().toHex().toUpper());
	ui->linePs3Seed->setText(settings->value("ps3Seed").toByteArray().toHex().toUpper());
	load=false;
}

Options::~Options(){delete ui;}

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

void Options::closeEvent(QCloseEvent *){settings->setValue("OptionsGeometry",saveGeometry());}
void Options::moveEvent(QMoveEvent *){settings->setValue("OptionsGeometry",saveGeometry());}
void Options::resizeEvent(QResizeEvent *){settings->setValue("OptionsGeometry",saveGeometry());}

void Options::set_path_lbls()
{
	if (!settings->value("default_save_file").isNull()){ui->line_default_save->setText(settings->value("default_save_file").toString());}
	if (!settings->value("char_stat_folder").isNull()){ui->line_char_stat_folder->setText(settings->value("char_stat_folder").toString());}
	if (!settings->value("save_pc_path").isNull()){ui->line_save_pc->setText(settings->value("save_pc_path").toString());}
	if (!settings->value("save_emu_path").isNull()){ui->line_save_emu->setText(settings->value("save_emu_path").toString());}
	if (!settings->value("load_path").isNull()){ui->line_load_path->setText(settings->value("load_path").toString());}
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
	else{settings->setValue("char_stat_folder",QString(QDir::homePath()));}
	set_path_lbls();
	load=false;
}
/*~~~~~~~~~~~~~~~~~~RESET STUFF~~~~~~~~~~~~~~~~~~~*/
void Options::on_reset_default_save_location_clicked()
{
	ui->cb_override_def_save->setChecked(Qt::Unchecked);
	settings->remove("default_save_file");
	ui->line_default_save->clear();
}
void Options::on_cb_skip_slot_mask_toggled(bool checked){if(!load){settings->setValue("skip_slot_mask",checked);}}
void Options::on_cb_override_def_save_toggled(bool checked)
{
	if(!load){settings->setValue("override_default_save",checked);}
	if(checked)
	{
		ui->line_default_save->setVisible(true);
		ui->btn_set_default_save->setVisible(true);
		ui->reset_default_save_location->setVisible(true);
	}
	else
	{
		ui->line_default_save->setVisible(false);
		ui->btn_set_default_save->setVisible(false);
		ui->reset_default_save_location->setVisible(false);
	}
}

void Options::on_cbCharEditorAdvanced_toggled(bool checked){if(!load){settings->setValue("charEditorAdvanced",checked);}}
void Options::on_cbChocoboEditorAdvanced_toggled(bool checked){if(!load){settings->setValue("chocoboEditorAdvanced",checked);}}
void Options::on_cbGameProgressAdvanced_toggled(bool checked){if(!load){settings->setValue("gameProgressAdvanced",checked);}}
void Options::on_cbOptionsShowMapping_toggled(bool checked){if(!load){settings->setValue("optionsShowMapping",checked);}}
void Options::on_cbTestDataEnabled_toggled(bool checked){if(!load){settings->setValue("show_test",checked);}}
void Options::on_cbLocationViewerAdvanced_toggled(bool checked){if(!load){settings->setValue("locationViewerAdvanced",checked);}}
void Options::on_cbWorldMapAdvanced_toggled(bool checked){if(!load){settings->setValue("worldMapAdvanced",checked);}}

void Options::on_linePs3Key_editingFinished()
{if(!load){
		QByteArray temp = QByteArray::fromHex(ui->linePs3Key->text().toLocal8Bit());
		settings->setValue("ps3Key",temp);
}}

void Options::on_linePs3Seed_editingFinished()
{if(!load){
		QByteArray temp = QByteArray::fromHex(ui->linePs3Seed->text().toLocal8Bit());
		settings->setValue("ps3Seed",temp);
}}
