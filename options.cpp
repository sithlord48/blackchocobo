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

//QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"blackchocobo","settings",0);

Options::Options(QWidget *parent,QSettings *config_data) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    load=false;
    settings = config_data;
    ui->combo_font->setFont(QApplication::font().family());
    set_path_lbls();
    ui->slide_c1_r->setValue(settings->value("color1_r").toInt());
    ui->slide_c1_g->setValue(settings->value("color1_g").toInt());
    ui->slide_c1_b->setValue(settings->value("color1_b").toInt());
    ui->slide_c2_r->setValue(settings->value("color2_r").toInt());
    ui->slide_c2_g->setValue(settings->value("color2_g").toInt());
    ui->slide_c2_b->setValue(settings->value("color2_b").toInt());
    ui->slide_c3_r->setValue(settings->value("color3_r").toInt());
    ui->slide_c3_g->setValue(settings->value("color3_g").toInt());
    ui->slide_c3_b->setValue(settings->value("color3_b").toInt());
    ui->combo_font_size->setCurrentIndex(QApplication::font().pointSize()-8);
    if(settings->value("show_test").toBool()){ui->cb_skip_slot_mask->setVisible(true);}
    else{ui->cb_skip_slot_mask->setVisible(false);}
    load=true;
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
void Options::set_preview()
{
    QString style="background-color: qlineargradient(spread:repeat, x1:1, y1:1, x2:0, y2:0, stop:0.0625 rgba(";
    style.append(QString::number(ui->slide_c1_r->value()));    style.append(",");
    style.append(QString::number(ui->slide_c1_g->value()));    style.append(",");
    style.append(QString::number(ui->slide_c1_b->value()));    style.append(", 255), stop:0.215909 rgba(");
    style.append(QString::number(ui->slide_c2_r->value()));    style.append(",");
    style.append(QString::number(ui->slide_c2_g->value()));    style.append(",");
    style.append(QString::number(ui->slide_c2_b->value()));    style.append(", 255), stop:0.818182 rgba(");
    style.append(QString::number(ui->slide_c3_r->value()));    style.append(",");
    style.append(QString::number(ui->slide_c3_g->value()));    style.append(",");
    style.append(QString::number(ui->slide_c3_b->value()));    style.append(", 255));");
    ui->lbl_preview->setStyleSheet(style);
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

void Options::on_line_save_pc_editingFinished()
{
    if(!ui->line_save_pc->text().isNull()){settings->setValue("save_pc",ui->line_save_pc->text());}
    //set_path_lbls();
}
void Options::on_btn_set_save_pc_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save FF7 PC Saves"),settings->value("save_pc_path").toString());
    if(!temp.isNull()){settings->setValue("save_pc_path",temp);}
    set_path_lbls();
}


void Options::on_line_save_emu_editingFinished()
{
    if(!ui->line_save_emu->text().isNull()){settings->setValue("save_emu",ui->line_save_emu->text());}
    //set_path_lbls();
}
void Options::on_btn_set_save_emu_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Save mcd/mcr saves"),settings->value("save_emu_path").toString());
    if(!temp.isNull()){settings->setValue("save_emu_path",temp);}
    set_path_lbls();
}

void Options::on_line_load_path_editingFinished()
{
    if(!ui->line_load_path->text().isNull()){settings->setValue("load_path",ui->line_load_path->text());}
    //set_path_lbls();
}
void Options::on_btn_set_load_path_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Load FF7 PC Saves From"),settings->value("load_path").toString());
    if(!temp.isNull()){settings->setValue("load_path",temp);}
    set_path_lbls();
}


void Options::on_line_export_pc_editingFinished()
{
    if(!ui->line_export_pc->text().isNull()){settings->setValue("export_pc",ui->line_export_pc->text());}
    //set_path_lbls();
}
void Options::on_btn_set_export_pc_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Directory To Export FF7 PC Saves"),settings->value("export_pc").toString());
    if(!temp.isNull()){settings->setValue("export_pc",temp);}
    set_path_lbls();
}

void Options::on_line_default_save_editingFinished()
{
    if(!ui->line_default_save->text().isNull()){settings->setValue("default_save_file",ui->line_default_save->text());}
    //set_path_lbls();
}
void Options::on_btn_set_default_save_clicked()
{
    QString temp = QFileDialog::getOpenFileName(this,tr("Select A Default Save Game (Must Be Raw PSX)"),settings->value("default_save_file").toString());
    if(!temp.isNull()){settings->setValue("default_save_file",temp);}
    set_path_lbls();
}

void Options::on_line_char_stat_folder_editingFinished()
{
    if(!ui->line_char_stat_folder->text().isNull()){settings->setValue("char_stat_folder",ui->line_char_stat_folder->text());}
}
void Options::on_btn_set_char_stat_folder_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select A Location To Save Character Stat Files"),settings->value("char_stat_folder").toString());
    if(!temp.isNull()){settings->setValue("char_stat_folder",temp);}
    set_path_lbls();
}
/*~~~~~~~~~~~~~~~~~~~~Font Stuff~~~~~~~~~~~~~~~~~~~~~~*/

void Options::on_combo_font_currentIndexChanged(QString family)
{
    settings->setValue("font-family",family);
    QApplication::setFont(QFont(family,int(QApplication::font().pointSize()),-1,false));
}

void Options::on_combo_font_size_currentIndexChanged(int index)
{
    settings->setValue("font-size",index+8);
    QApplication::setFont(QFont(ui->combo_font->currentText(),index+8,-1,false));
}
/*~~~~~~~~~~~~~~~~~~Color sliders~~~~~~~~~~~~~~~~~~*/
void Options::on_slide_c1_r_valueChanged(int value)
{
    QString g_style = "QSlider#slide_c1_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c1_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_c1_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c1_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_c1_b->value()));   g_style.append(",255));}");

    QString b_style =  "QSlider#slide_c1_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c1_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c1_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c1_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c1_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_c1_g->setStyleSheet(g_style);
    ui->slide_c1_b->setStyleSheet(b_style);
    settings->setValue("color1_r",value);
    set_preview();
}
void Options::on_slide_c1_g_valueChanged(int value)
{
    QString r_style = "QSlider#slide_c1_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_b->value()));   r_style.append(",255));}");

    QString b_style =  "QSlider#slide_c1_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c1_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c1_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c1_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c1_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_c1_r->setStyleSheet(r_style);
    ui->slide_c1_b->setStyleSheet(b_style);
    settings->setValue("color1_g",value);
    set_preview();
}
void Options::on_slide_c1_b_valueChanged(int value)
{
    QString r_style = "QSlider#slide_c1_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c1_b->value()));   r_style.append(",255));}");

    QString g_style = "QSlider#slide_c1_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c1_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_c1_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c1_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_c1_b->value()));   g_style.append(",255));}");

    ui->slide_c1_r->setStyleSheet(r_style);
    ui->slide_c1_g->setStyleSheet(g_style);
    settings->setValue("color1_b",value);
    set_preview();
}

void Options::on_slide_c2_r_valueChanged(int value)
{
    QString g_style = "QSlider#slide_c2_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c2_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_c2_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c2_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_c2_b->value()));   g_style.append(",255));}");

    QString b_style =  "QSlider#slide_c2_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c2_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c2_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c2_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c2_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_c2_g->setStyleSheet(g_style);
    ui->slide_c2_b->setStyleSheet(b_style);
    settings->setValue("color2_r",value);
    set_preview();
}
void Options::on_slide_c2_g_valueChanged(int value)
{
    QString r_style = "QSlider#slide_c2_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_b->value()));   r_style.append(",255));}");

    QString b_style =  "QSlider#slide_c2_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c2_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c2_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c2_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c2_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_c2_r->setStyleSheet(r_style);
    ui->slide_c2_b->setStyleSheet(b_style);
    settings->setValue("color2_g",value);
    set_preview();
}
void Options::on_slide_c2_b_valueChanged(int value)
{
    QString r_style = "QSlider#slide_c2_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c2_b->value()));   r_style.append(",255));}");

    QString g_style = "QSlider#slide_c2_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c2_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_c2_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c2_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_c2_b->value()));   g_style.append(",255));}");

    ui->slide_c2_r->setStyleSheet(r_style);
    ui->slide_c2_g->setStyleSheet(g_style);
    settings->setValue("color2_b",value);
    set_preview();
}

void Options::on_slide_c3_r_valueChanged(int value)
{
    QString g_style = "QSlider#slide_c3_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c3_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_c3_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c3_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_c3_b->value()));   g_style.append(",255));}");

    QString b_style =  "QSlider#slide_c3_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c3_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c3_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c3_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c3_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_c3_g->setStyleSheet(g_style);
    ui->slide_c3_b->setStyleSheet(b_style);
    settings->setValue("color3_r",value);
    set_preview();
}
void Options::on_slide_c3_g_valueChanged(int value)
{

    QString r_style = "QSlider#slide_c3_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_b->value()));   r_style.append(",255));}");

    QString b_style =  "QSlider#slide_c3_b::groove{background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    b_style.append(QString::number(ui->slide_c3_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c3_g->value()));   b_style.append(",");
    b_style.append(QString::number(0));                         b_style.append(", 255), stop:1 rgba(");
    b_style.append(QString::number(ui->slide_c3_r->value()));   b_style.append(",");
    b_style.append(QString::number(ui->slide_c3_g->value()));   b_style.append(",");
    b_style.append(QString::number(255));                       b_style.append(",255));}");

    ui->slide_c3_r->setStyleSheet(r_style);
    ui->slide_c3_b->setStyleSheet(b_style);
    settings->setValue("color3_g",value);
    set_preview();
}
void Options::on_slide_c3_b_valueChanged(int value)
{
    QString r_style = "QSlider#slide_c3_r::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    r_style.append(QString::number(0));                         r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_b->value()));   r_style.append(", 255), stop:1 rgba(");
    r_style.append(QString::number(255));                       r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_g->value()));   r_style.append(",");
    r_style.append(QString::number(ui->slide_c3_b->value()));   r_style.append(",255));}");

    QString g_style = "QSlider#slide_c3_g::groove{height: 12px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(";
    g_style.append(QString::number(ui->slide_c3_r->value()));   g_style.append(",");
    g_style.append(QString::number(0));                         g_style.append(",");
    g_style.append(QString::number(ui->slide_c3_b->value()));   g_style.append(", 255), stop:1 rgba(");
    g_style.append(QString::number(ui->slide_c3_r->value()));   g_style.append(",");
    g_style.append(QString::number(255));                       g_style.append(",");
    g_style.append(QString::number(ui->slide_c3_b->value()));   g_style.append(",255));}");

    ui->slide_c3_r->setStyleSheet(r_style);
    ui->slide_c3_g->setStyleSheet(g_style);
    settings->setValue("color3_b",value);
    set_preview();
}

/*~~~~~~~~~~~~~~~~~~RESET STUFF~~~~~~~~~~~~~~~~~~~*/
void Options::on_reset_default_save_location_clicked()
{
    settings->setValue("default_save_file",QString(QCoreApplication::applicationDirPath()) + "/"+ "save0");
    set_path_lbls();
}

void Options::on_reset_char_stat_folder_clicked()
{
    settings->setValue("char_stat_folder",QString(QDir::homePath()));
    set_path_lbls();
}

void Options::on_reset_font_clicked()
{
    //QApplication::setFont(QFont("ubuntu",9,-1,false)); QApplication::font().setFamily("ubuntu");
    ui->combo_font->setCurrentFont(QFont("ubuntu",9,-1,false));
    ui->combo_font_size->setCurrentIndex(0);
    settings->remove("font-family"); settings->remove("font-size");
}

void Options::on_cb_skip_slot_mask_toggled(bool checked){if(!load){settings->setValue("skip_slot_mask",checked);}}
/*~~~~~~~~~~~~~~~~CLOSE BUTTON~~~~~~~~~~~~~~~~~~*/
void Options::on_pushButton_clicked(){this->close();}
