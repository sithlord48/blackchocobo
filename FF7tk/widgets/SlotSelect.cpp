#include "SlotSelect.h"

SlotSelect::SlotSelect(QWidget *parent,FF7Save *data):QDialog(parent)
{
    list_preview = new QScrollArea;
    this->setMinimumSize(600,460);
    this->setMaximumWidth(600);
    this->setWindowFlags(((this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));//remove close button

    preview_layout = new QVBoxLayout;
    frm_preview = new QFrame;
    frm_preview->setLayout(preview_layout);
    frm_preview->setContentsMargins(0,0,0,0);
    preview_layout->setContentsMargins(0,0,0,0);
    preview_layout->setSpacing(3);
    frm_preview->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    ff7 = data;
    for(int i=0;i<15;i++)
    {
        preview[i] = new SlotPreview;
        preview_layout->addWidget(preview[i]);

        if(((ff7->type()!="PC") && (((ff7->psx_block_type(i)==FF7Save::BLOCK_MIDLINK) || (ff7->psx_block_type(i) == FF7Save::BLOCK_ENDLINK)) || ((ff7->psx_block_type(i)==FF7Save::BLOCK_DELETED_MIDLINK) || (ff7->psx_block_type(i) == FF7Save::BLOCK_DELETED_ENDLINK)))))
        {
            preview[i]->setMode(1);
            QByteArray icon_data;
            icon_data= ff7->slot_header(i) ;

            switch((quint8)icon_data.at(2))
            {
                case 0x11: preview[i]->setPsxIcon(icon_data.mid(96,160));break;
                case 0x12: preview[i]->setPsxIcon(icon_data.mid(96,288),2);break;
                case 0x13: preview[i]->setPsxIcon(icon_data.mid(96,416),3);break;
                default: //Black Box
                    QByteArray tmp;
                    tmp.fill(00,0x200);
                    preview[i]->setPsxIcon(tmp,1);
                    break;
            }
            QString Slottext;
            switch (ff7->psx_block_type(i))
            {
                case FF7Save::BLOCK_MIDLINK:   Slottext =tr("       Mid-Linked Block, Next Data Chunk @ Slot:%1").arg(QString::number(ff7->psx_block_next(i)+1)); break;
                case  FF7Save::BLOCK_DELETED_MIDLINK:  Slottext =tr("    Mid-Linked Block (Deleted), Next Data Chunk @ Slot:%1").arg(QString::number(ff7->psx_block_next(i)+1)); break;
                case FF7Save::BLOCK_ENDLINK:  Slottext =tr("      End Of Linked Blocks"); break;
                case  FF7Save::BLOCK_DELETED_ENDLINK: Slottext =tr("      End Of Linked Blocks (Deleted)"); break;
                default: Slottext = tr("ERROR"); break;
            }
            preview[i]->setLocation(Slottext);
        }

        else if(ff7->isFF7(i))
        {
            preview[i]->setMode(2);
            //show real Dialog background.
            QImage image(2, 2, QImage::Format_ARGB32);
            image.setPixel(0, 0, QColor(ff7->slot[i].colors[0][0],ff7->slot[i].colors[0][1],ff7->slot[i].colors[0][2]).rgb());
            image.setPixel(1, 0, QColor(ff7->slot[i].colors[1][0],ff7->slot[i].colors[1][1],ff7->slot[i].colors[1][2]).rgb());
            image.setPixel(0, 1, QColor(ff7->slot[i].colors[2][0],ff7->slot[i].colors[2][1],ff7->slot[i].colors[2][2]).rgb());
            image.setPixel(1, 1, QColor(ff7->slot[i].colors[3][0],ff7->slot[i].colors[3][1],ff7->slot[i].colors[3][2]).rgb());
            QImage gradient = image.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            preview[i]->setPixmap(QPixmap::fromImage(gradient));

            preview[i]->setParty(Chars.Pixmap(ff7->descParty(i,0)),Chars.Pixmap(ff7->descParty(i,1)),Chars.Pixmap(ff7->descParty(i,2)));
            preview[i]->setLocation(ff7->descLocation(i));
            preview[i]->setName(ff7->descName(i));
            preview[i]->setLevel(ff7->descLevel(i));
            preview[i]->setGil(ff7->descGil(i));
            preview[i]->setTime((ff7->descTime(i)/3600),(ff7->descTime(i)/60 %60));
        }
        else if(ff7->region(i).isEmpty() || ff7->psx_block_type(i) ==FF7Save::BLOCK_EMPTY ) //&& ff7->psx_block_type(i) != FF7Save::BLOCK_MIDLINK && ff7->psx_block_type(i) != FF7Save::BLOCK_ENDLINK && ff7->psx_block_type(i) != FF7Save::BLOCK_DELETED_MIDLINK && ff7->psx_block_type(i)!=FF7Save::BLOCK_DELETED_ENDLINK)
        {
            preview[i]->setMode(0);
            preview[i]->setLocation(tr("-Empty-"));
        }
        else
        {// all other psx saves.
            preview[i]->setMode(1);
            QByteArray icon_data;
            icon_data= ff7->slot_header(i);

            switch((quint8)icon_data.at(2))
            {
                case 0x11: preview[i]->setPsxIcon(icon_data.mid(96,160)); break;
                case 0x12: preview[i]->setPsxIcon(icon_data.mid(96,288),2);break;
                case 0x13: preview[i]->setPsxIcon(icon_data.mid(96,416),3); break;
                default: //Black Box
                    QByteArray tmp;
                    tmp.fill(00,0x200);
                    preview[i]->setPsxIcon(tmp);
                    break;
            }
            QByteArray desc;
            QTextCodec *codec = QTextCodec::codecForName(QByteArray("Shift-JIS"));
            desc = icon_data.mid(4,64);
            int desc_end;
            if((desc_end = desc.indexOf('\x00')) != -1) {desc.truncate(desc_end);}

            QString Slottext=codec->toUnicode(desc);
            Slottext.prepend("      ");
            if((ff7->psx_block_type(i)==FF7Save::BLOCK_DELETED_MAIN)||(ff7->psx_block_type(i)==FF7Save::BLOCK_DELETED_MIDLINK) || (ff7->psx_block_type(i)==FF7Save::BLOCK_DELETED_ENDLINK)){Slottext.append(tr("(Deleted)"));}
            Slottext.append(tr("\n\t Game Uses %1 Save Block").arg(QString::number(ff7->psx_block_size(i))));
            if(ff7->psx_block_next(i)!=0xFF){Slottext.append(tr("s; Next Data Chunk @ Slot:%1").arg(QString::number(ff7->psx_block_next(i)+1)));}
            preview[i]->setLocation(Slottext);
        }
        //more checks after this....
        //for any item
        preview[i]->set_Button_Label(QString((tr("Slot:%1"))).arg(QString::number(i+1)));
        if(QT_VERSION<0x050000)
        {//QT4 Style Connection
            connect(preview[i],SIGNAL(btn_select_clicked(QString)),this,SLOT(button_clicked(QString)));
            connect(preview[i],SIGNAL(btn_remove_clicked(QString)),this,SLOT(remove_slot(QString)));
        }
        else
        {//QT5 Style Connection
        //    connect(preview[i]::button_clicked(QString),this::button_clicked(QString));
        }
    }
    list_preview->setWidget(frm_preview);
    list_preview->setContentsMargins(0,0,0,0);

    QVBoxLayout *dialog_layout = new QVBoxLayout;
    dialog_layout->setContentsMargins(0,0,0,0);
    dialog_layout->setSpacing(2);
    dialog_layout->addWidget(list_preview);
    this->setLayout(dialog_layout);
    this->setContentsMargins(0,0,0,0);
}
void SlotSelect::button_clicked(QString btn_text)
{
    if(btn_text == QString(tr("Slot:1"))){done(0);}
    else if(btn_text == QString(tr("Slot:2"))){done(1);}
    else if(btn_text == QString(tr("Slot:3"))){done(2);}
    else if(btn_text == QString(tr("Slot:4"))){done(3);}
    else if(btn_text == QString(tr("Slot:5"))){done(4);}
    else if(btn_text == QString(tr("Slot:6"))){done(5);}
    else if(btn_text == QString(tr("Slot:7"))){done(6);}
    else if(btn_text == QString(tr("Slot:8"))){done(7);}
    else if(btn_text == QString(tr("Slot:9"))){done(8);}
    else if(btn_text == QString(tr("Slot:10"))){done(9);}
    else if(btn_text == QString(tr("Slot:11"))){done(10);}
    else if(btn_text == QString(tr("Slot:12"))){done(11);}
    else if(btn_text == QString(tr("Slot:13"))){done(12);}
    else if(btn_text == QString(tr("Slot:14"))){done(13);}
    else if(btn_text == QString(tr("Slot:15"))){done(14);}
    else{this->done(0);}
}
void SlotSelect::remove_slot(QString btn_text)
{
    btn_text.remove(0,5);
    int s = btn_text.toInt()-1;
    if(ff7->type()!="PC")
    {
        if((ff7->psx_block_type(s)!=FF7Save::BLOCK_MAIN) && (ff7->psx_block_type(s) != FF7Save::BLOCK_DELETED_MAIN)){return;}//only can remove Main blocks (they will clean up their sub blocks).
        int size = ff7->psx_block_size(s);
        for (int i=0;  i<size; i++)
        {
            int t=ff7->psx_block_next(s);
            ff7->clearslot(s);
            ReIntSlot(s,0);
            preview[s]->setLocation(tr("-Empty-"));
            s=t;
        }
    }
    else
    {
        ff7->clearslot(s);
        ReIntSlot(s,0);
        preview[s]->setLocation(tr("-Empty-"));
    }
}
void SlotSelect::ReIntSlot(int button_number, int mode)
{
    preview[button_number]->~QWidget();
    preview[button_number]= new SlotPreview;
    preview[button_number]->setMode(mode);
    preview[button_number]->set_Button_Label(QString((tr("Slot:%1"))).arg(QString::number(button_number+1)));
    preview_layout->insertWidget(button_number,preview[button_number]);
    if(QT_VERSION<0x050000)
    {//QT4 Style Connection
        connect(preview[button_number],SIGNAL(btn_select_clicked(QString)),this,SLOT(button_clicked(QString)));}
    else
    {//QT5 Style Connection
    //    connect(preview[button_number]::button_clicked(QString),this::button_clicked(QString));
    }
}
