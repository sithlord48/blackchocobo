#ifndef ITEMSELECTOR_H
#define ITEMSELECTOR_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QHBoxLayout>
//Include Data class
#include "../static_data/FF7Item.h"

class ItemSelector : public QWidget
{
    Q_OBJECT
public:
    explicit ItemSelector(QWidget *parent = 0);
    int id();// current id
signals:
    void item_changed(quint16);//return selected rawitem
public slots:
    void setCurrentItem(quint16 ff7item);
    void setCurrentItem(int id,int qty);
private slots:
    void setFilter(int type);
    void comboItem_changed(int index);
    void sb_qty_changed(int qty);
    void btn_remove_clicked();
private:
    void init_display();
    void init_connections();
    void init_data();
    int type_offset(int type);
    FF7Item Items;
    QComboBox *combo_type;
    QComboBox *combo_item;
    QSpinBox  *sb_qty;
    QPushButton *btn_remove;
    quint16 current_item;
};
#endif // ITEMSELECTOR_H
