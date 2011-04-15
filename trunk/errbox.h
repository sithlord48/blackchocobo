#ifndef ERRBOX_H
#define ERRBOX_H

#include <QDialog>

namespace Ui {
    class errbox;
}

class errbox : public QDialog
{
    Q_OBJECT

public:
    explicit errbox(QWidget *parent = 0);
    ~errbox();

private slots:
    void on_btn_prev_clicked();

    void on_btn_export_clicked();

    void on_btn_view_clicked();

    void on_btn_next_clicked();

private:
    Ui::errbox *ui;
};

#endif // ERRBOX_H
