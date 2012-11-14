#ifndef SLOTSELECT_H
#define SLOTSELECT_H

#include <QDialog>
#include <QScrollArea>
#include <QLayout>
#include <QFrame>
#include "../static_data/FF7Save.h"
#include "../static_data/FF7Char.h"
#include "SlotPreview.h"

class SlotSelect : public QDialog
{
    Q_OBJECT
public:
    explicit SlotSelect(QWidget *parent = 0,FF7Save *data=0);

private slots:
    void button_clicked(QString);
    void remove_slot(QString);
private:
    void ReIntSlot(int button_number,int mode);
    QFrame *frm_preview;
    QVBoxLayout *preview_layout;
    QScrollArea *list_preview;
    SlotPreview *preview[15];
    //Private Data
    FF7Save *ff7;
    FF7Char Chars;
};

#endif // SLOTSELECT_H
