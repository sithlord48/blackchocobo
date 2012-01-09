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

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
namespace Ui {
    class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0,QSettings *config_data=0);
    ~Options();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Options *ui;
    bool load;
    QSettings *settings;
private slots:
    void on_line_char_stat_folder_editingFinished();
    void on_line_default_save_editingFinished();
    void on_line_export_pc_editingFinished();
    void on_line_load_path_editingFinished();
    void on_line_save_emu_editingFinished();
    void on_line_save_pc_editingFinished();
    void on_btn_set_char_stat_folder_clicked();
    void on_btn_set_default_save_clicked();
    void on_btn_set_export_pc_clicked();
    void on_btn_set_load_path_clicked();
    void on_btn_set_save_emu_clicked();
    void on_btn_set_save_pc_clicked();
    void on_pushButton_clicked();
    void set_path_lbls();
    void set_preview();
    void on_slide_c1_b_valueChanged(int value);
    void on_slide_c1_g_valueChanged(int value);
    void on_slide_c1_r_valueChanged(int value);
    void on_slide_c2_b_valueChanged(int value);
    void on_slide_c2_g_valueChanged(int value);
    void on_slide_c2_r_valueChanged(int value);
    void on_slide_c3_b_valueChanged(int value);
    void on_slide_c3_g_valueChanged(int value);
    void on_slide_c3_r_valueChanged(int value);
    void on_reset_default_save_location_clicked();
    void on_reset_char_stat_folder_clicked();
    void on_combo_font_currentIndexChanged(QString );
    void on_reset_font_clicked();
    void on_cb_skip_slot_mask_toggled(bool checked);
    void on_combo_font_size_currentIndexChanged(int index);
};

#endif // OPTIONS_H
