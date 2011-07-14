/****************************************************************************/
//    copyright 2010, 2011 Chris Rizzitello <sithlord48@gmail.com>          //
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

QSettings bchoco_settings(QSettings::NativeFormat,QSettings::UserScope,"blackchocobo","settings",0);

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    ui->lcd_font_size->setHidden(1);
    ui->lcd_font_size->display(int(QApplication::font().pointSize()));
    ui->combo_font->setFont(QApplication::font().family());
    set_path_lbls();
    ui->slide_c1_r->setValue(bchoco_settings.value("color1_r").toInt());
    ui->slide_c1_g->setValue(bchoco_settings.value("color1_g").toInt());
    ui->slide_c1_b->setValue(bchoco_settings.value("color1_b").toInt());
    ui->slide_c2_r->setValue(bchoco_settings.value("color2_r").toInt());
    ui->slide_c2_g->setValue(bchoco_settings.value("color2_g").toInt());
    ui->slide_c2_b->setValue(bchoco_settings.value("color2_b").toInt());
    ui->slide_c3_r->setValue(bchoco_settings.value("color3_r").toInt());
    ui->slide_c3_g->setValue(bchoco_settings.value("color3_g").toInt());
    ui->slide_c3_b->setValue(bchoco_settings.value("color3_b").toInt());
    switch(int(ui->lcd_font_size->value()))
    {
    case 9: ui->btn_9pt->setChecked(Qt::Checked); break;
    case 10: ui->btn_10pt->setChecked(Qt::Checked); break;
    case 11: ui->btn_11pt->setChecked(Qt::Checked); break;
    case 12: ui->btn_12pt->setChecked(Qt::Checked); break;
    case 13: ui->btn_13pt->setChecked(Qt::Checked); break;
    case 14: ui->btn_14pt->setChecked(Qt::Checked); break;
    default: ui->btn_9pt->setChecked(Qt::Checked); break;
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
        break;
    default:
        break;
    }
}
void Options::set_preview()
{
    QString style="background-color: qlineargradient(spread:repeat, x1:1, y1:1, x2:0, y2:0, stop:0.0625 rgba(";
    style.append(QString::number(ui->slide_c1_r->value()));
    style.append(",");
    style.append(QString::number(ui->slide_c1_g->value()));
    style.append(",");
    style.append(QString::number(ui->slide_c1_b->value()));
    style.append(", 255), stop:0.215909 rgba(");
    style.append(QString::number(ui->slide_c2_r->value()));
    style.append(",");
    style.append(QString::number(ui->slide_c2_g->value()));
    style.append(",");
    style.append(QString::number(ui->slide_c2_b->value()));
    style.append(", 255), stop:0.818182 rgba(");
    style.append(QString::number(ui->slide_c3_r->value()));
    style.append(",");
    style.append(QString::number(ui->slide_c3_g->value()));
    style.append(",");
    style.append(QString::number(ui->slide_c3_b->value()));
    style.append(", 255));");
    ui->lbl_preview->setStyleSheet(style);
}
void Options::set_path_lbls()
{
    if (!bchoco_settings.value("default_save_file").isNull()){ui->line_default_save->setText(bchoco_settings.value("default_save_file").toString());}
    if (!bchoco_settings.value("char_stat_folder").isNull()){ui->line_char_stat_folder->setText(bchoco_settings.value("char_stat_folder").toString());}
    if (!bchoco_settings.value("save_pc_path").isNull()){ui->line_save_pc->setText(bchoco_settings.value("save_pc_path").toString());}
    if (!bchoco_settings.value("save_emu_path").isNull()){ui->line_save_emu->setText(bchoco_settings.value("save_emu_path").toString());}
    if (!bchoco_settings.value("load_path").isNull()){ui->line_load_path->setText(bchoco_settings.value("load_path").toString());}
    if (!bchoco_settings.value("export_pc").isNull()){ui->line_export_pc->setText(bchoco_settings.value("export_pc").toString());}
}

void Options::on_line_save_pc_editingFinished()
{
    if(!ui->line_save_pc->text().isNull()){bchoco_settings.setValue("save_pc",ui->line_save_pc->text());}
    //set_path_lbls();
}
void Options::on_btn_set_save_pc_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save FF7 PC Saves"),bchoco_settings.value("save_pc_path").toString());
    if(!temp.isNull()){bchoco_settings.setValue("save_pc_path",temp);}
    set_path_lbls();
}


void Options::on_line_save_emu_editingFinished()
{
    if(!ui->line_save_emu->text().isNull()){bchoco_settings.setValue("save_emu",ui->line_save_emu->text());}
    //set_path_lbls();
}
void Options::on_btn_set_save_emu_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save mcd/mcr saves"),bchoco_settings.value("save_emu_path").toString());
    if(!temp.isNull()){bchoco_settings.setValue("save_emu_path",temp);}
    set_path_lbls();
}

void Options::on_line_load_path_editingFinished()
{
    if(!ui->line_load_path->text().isNull()){bchoco_settings.setValue("load_path",ui->line_load_path->text());}
    //set_path_lbls();
}
void Options::on_btn_set_load_path_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Load FF7 PC Saves From"),bchoco_settings.value("load_path").toString());
    if(!temp.isNull()){bchoco_settings.setValue("load_path",temp);}
    set_path_lbls();
}


void Options::on_line_export_pc_editingFinished()
{
    if(!ui->line_export_pc->text().isNull()){bchoco_settings.setValue("export_pc",ui->line_export_pc->text());}
    //set_path_lbls();
}
void Options::on_btn_set_export_pc_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Export FF7 PC Saves"),bchoco_settings.value("export_pc").toString());
    if(!temp.isNull()){bchoco_settings.setValue("export_pc",temp);}
    set_path_lbls();
}

void Options::on_line_default_save_editingFinished()
{
    if(!ui->line_default_save->text().isNull()){bchoco_settings.setValue("default_save_file",ui->line_default_save->text());}
    //set_path_lbls();
}
void Options::on_btn_set_default_save_clicked()
{
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A Default Save Game (Must Be Raw PSX)"),bchoco_settings.value("default_save_file").toString());
    if(!temp.isNull()){bchoco_settings.setValue("default_save_file",temp);}
    set_path_lbls();
}

void Options::on_line_char_stat_folder_editingFinished()
{
    if(!ui->line_char_stat_folder->text().isNull()){bchoco_settings.setValue("char_stat_folder",ui->line_char_stat_folder->text());}
}
void Options::on_btn_set_char_stat_folder_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Location To Save Character Stat Files"),bchoco_settings.value("char_stat_folder").toString());
    if(!temp.isNull()){bchoco_settings.setValue("char_stat_folder",temp);}
    set_path_lbls();
}
/*~~~~~~~~~~~~~~~~~~~~Font Stuff~~~~~~~~~~~~~~~~~~~~~~*/

void Options::on_combo_font_currentIndexChanged(QString family)
{
    bchoco_settings.setValue("font-family",family);
    QApplication::setFont(QFont(family,int(ui->lcd_font_size->value()),-1,false));
}
void Options::on_btn_9pt_clicked(bool checked)
{if(checked){
    bchoco_settings.setValue("font-size",9);
    ui->lcd_font_size->display(9);
    QApplication::setFont(QFont(ui->combo_font->currentText(),9,-1,false));
}}
void Options::on_btn_10pt_clicked(bool checked)
{if(checked){
    bchoco_settings.setValue("font-size",10);
    ui->lcd_font_size->display(10);
    QApplication::setFont(QFont(ui->combo_font->currentText(),10,-1,false));
}}
void Options::on_btn_11pt_clicked(bool checked)
{if(checked){
    bchoco_settings.setValue("font-size",11);
    ui->lcd_font_size->display(11);
    QApplication::setFont(QFont(ui->combo_font->currentText(),11,-1,false));
}}
void Options::on_btn_12pt_clicked(bool checked)
{if(checked){
    bchoco_settings.setValue("font-size",12);
    ui->lcd_font_size->display(12);
    QApplication::setFont(QFont(ui->combo_font->currentText(),12,-1,false));
}}
void Options::on_btn_13pt_clicked(bool checked)
{if(checked){
    bchoco_settings.setValue("font-size",13);
    ui->lcd_font_size->display(13);
    QApplication::setFont(QFont(ui->combo_font->currentText(),13,-1,false));
}}
void Options::on_btn_14pt_clicked(bool checked)
{if(checked){
    bchoco_settings.setValue("font-size",14);
    ui->lcd_font_size->display(14);
    QApplication::setFont(QFont(ui->combo_font->currentText(),14,-1,false));
}}
/*~~~~~~~~~~~~~~~~~~Color sliders~~~~~~~~~~~~~~~~~~*/
void Options::on_slide_c1_r_valueChanged(int value)
{
    QString g_style = "QSlider#slide_c1_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c1_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c1_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c1_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c1_b->value()));
    g_style.append(",255));}");

    QString b_style =  "QSlider#slide_c1_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c1_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c1_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c1_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c1_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_c1_g->setStyleSheet(g_style);
    ui->slide_c1_b->setStyleSheet(b_style);
    bchoco_settings.setValue("color1_r",value);
    set_preview();
}
void Options::on_slide_c1_g_valueChanged(int value)
{
    QString r_style = "QSlider#slide_c1_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_b->value()));
    r_style.append(",255));}");

    QString b_style =  "QSlider#slide_c1_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c1_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c1_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c1_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c1_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_c1_r->setStyleSheet(r_style);
    ui->slide_c1_b->setStyleSheet(b_style);
    bchoco_settings.setValue("color1_g",value);
    set_preview();
}
void Options::on_slide_c1_b_valueChanged(int value)
{
    QString r_style = "QSlider#slide_c1_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_b->value()));
    r_style.append(",255));}");

    QString g_style = "QSlider#slide_c1_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c1_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c1_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c1_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c1_b->value()));
    g_style.append(",255));}");

    ui->slide_c1_r->setStyleSheet(r_style);
    ui->slide_c1_g->setStyleSheet(g_style);
    bchoco_settings.setValue("color1_b",value);
    set_preview();
}

void Options::on_slide_c2_r_valueChanged(int value)
{
    QString g_style = "QSlider#slide_c2_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c2_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c2_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c2_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c2_b->value()));
    g_style.append(",255));}");

    QString b_style =  "QSlider#slide_c2_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c2_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c2_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c2_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c2_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_c2_g->setStyleSheet(g_style);
    ui->slide_c2_b->setStyleSheet(b_style);
    bchoco_settings.setValue("color2_r",value);
    set_preview();
}
void Options::on_slide_c2_g_valueChanged(int value)
{
    QString r_style = "QSlider#slide_c2_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_b->value()));
    r_style.append(",255));}");

    QString b_style =  "QSlider#slide_c2_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c2_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c2_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c2_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c2_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_c2_r->setStyleSheet(r_style);
    ui->slide_c2_b->setStyleSheet(b_style);
    bchoco_settings.setValue("color2_g",value);
    set_preview();
}
void Options::on_slide_c2_b_valueChanged(int value)
{
    QString r_style = "QSlider#slide_c2_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_b->value()));
    r_style.append(",255));}");

    QString g_style = "QSlider#slide_c2_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c2_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c2_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c2_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c2_b->value()));
    g_style.append(",255));}");

    ui->slide_c2_r->setStyleSheet(r_style);
    ui->slide_c2_g->setStyleSheet(g_style);
    bchoco_settings.setValue("color2_b",value);
    set_preview();
}

void Options::on_slide_c3_r_valueChanged(int value)
{
    QString g_style = "QSlider#slide_c3_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c3_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c3_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c3_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c3_b->value()));
    g_style.append(",255));}");

    QString b_style =  "QSlider#slide_c3_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c3_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c3_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c3_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c3_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_c3_g->setStyleSheet(g_style);
    ui->slide_c3_b->setStyleSheet(b_style);
    bchoco_settings.setValue("color3_r",value);
    set_preview();
}
void Options::on_slide_c3_g_valueChanged(int value)
{

    QString r_style = "QSlider#slide_c3_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_b->value()));
    r_style.append(",255));}");

    QString b_style =  "QSlider#slide_c3_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c3_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c3_g->value()));
    b_style.append(",");
    b_style.append(QString::number(0));
    b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c3_r->value()));
    b_style.append(",");
    b_style.append(QString::number(ui->slide_c3_g->value()));
    b_style.append(",");
    b_style.append(QString::number(255));
    b_style.append(",255));}");

    ui->slide_c3_r->setStyleSheet(r_style);
    ui->slide_c3_b->setStyleSheet(b_style);
    bchoco_settings.setValue("color3_g",value);
    set_preview();
}
void Options::on_slide_c3_b_valueChanged(int value)
{
    QString r_style = "QSlider#slide_c3_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_b->value()));
    r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_g->value()));
    r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_b->value()));
    r_style.append(",255));}");

    QString g_style = "QSlider#slide_c3_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c3_r->value()));
    g_style.append(",");
    g_style.append(QString::number(0));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c3_b->value()));
    g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c3_r->value()));
    g_style.append(",");
    g_style.append(QString::number(255));
    g_style.append(",");
    g_style.append(QString::number(ui->slide_c3_b->value()));
    g_style.append(",255));}");

    ui->slide_c3_r->setStyleSheet(r_style);
    ui->slide_c3_g->setStyleSheet(g_style);
    bchoco_settings.setValue("color3_b",value);
    set_preview();
}

/*~~~~~~~~~~~~~~~~~~RESET STUFF~~~~~~~~~~~~~~~~~~~*/
void Options::on_reset_default_save_location_clicked()
{
 bchoco_settings.setValue("default_save_file",QString(QCoreApplication::applicationDirPath()) + "/"+ "save0");
 set_path_lbls();
}

void Options::on_reset_char_stat_folder_clicked()
{
 bchoco_settings.setValue("char_stat_folder",QString(QDir::homePath()));
 set_path_lbls();
}

void Options::on_reset_font_clicked()
{
    QApplication::setFont(QFont("ubuntu",9,-1,false)); QApplication::font().setFamily("ubuntu");
    ui->combo_font->setCurrentFont(QFont("ubuntu",9,-1,false));
    ui->btn_9pt->click();
    bchoco_settings.remove("font-family"); bchoco_settings.remove("font-size");
}

/*~~~~~~~~~~~~~~~~CLOSE BUTTON~~~~~~~~~~~~~~~~~~*/
void Options::on_pushButton_clicked(){this->close();}
