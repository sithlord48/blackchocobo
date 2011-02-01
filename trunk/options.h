#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

namespace Ui {
    class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    ~Options();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Options *ui;

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
};

#endif // OPTIONS_H
