#include "SlotSelect.h"

SlotSelect::SlotSelect(QWidget *parent,FF7Save *data):QDialog(parent)
{
    list_preview = new QScrollArea;
    this->setMinimumSize(600,460);
    this->setMaximumWidth(600);
    this->setWindowFlags(((this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));//remove close button

    QVBoxLayout *preview_layout = new QVBoxLayout;
    frm_preview = new QFrame;
    frm_preview->setLayout(preview_layout);
    frm_preview->setContentsMargins(0,0,0,0);
    preview_layout->setContentsMargins(0,0,0,0);
    preview_layout->setSpacing(3);
    frm_preview->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    for(int i=0;i<15;i++)
    {
        preview[i] = new SlotPreview;
        preview_layout->addWidget(preview[i]);

        if((data->type()!="PC") && ((data->psx_block_type(i)==0x52) || (data->psx_block_type(i) == 0x53)))
        {
            preview[i]->setMode(1);
            QByteArray icon_data;
            icon_data= data->slot_header(i) ;

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
            if(data->psx_block_type(i) == 0x52){Slottext =tr("       Mid-Linked Block Next Data Chunk @ Slot:%1").arg(QString::number(data->psx_block_next(i)+1));}
            else if(data->psx_block_type(i) == 0x53){Slottext =tr("      End Of Linked Blocks");}
            else{Slottext = tr("ERROR");}
            preview[i]->setLocation(Slottext);
        }
        else if(data->isFF7(i))
        {
            preview[i]->setMode(2);
            //show real Dialog background.
            QImage image(2, 2, QImage::Format_ARGB32);
            image.setPixel(0, 0, QColor(data->slot[i].colors[0][0],data->slot[i].colors[0][1],data->slot[i].colors[0][2]).rgb());
            image.setPixel(1, 0, QColor(data->slot[i].colors[1][0],data->slot[i].colors[1][1],data->slot[i].colors[1][2]).rgb());
            image.setPixel(0, 1, QColor(data->slot[i].colors[2][0],data->slot[i].colors[2][1],data->slot[i].colors[2][2]).rgb());
            image.setPixel(1, 1, QColor(data->slot[i].colors[3][0],data->slot[i].colors[3][1],data->slot[i].colors[3][2]).rgb());
            QImage gradient = image.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            preview[i]->setPixmap(QPixmap::fromImage(gradient));

            preview[i]->setParty(Chars.Pixmap(data->descParty(i,0)),Chars.Pixmap(data->descParty(i,1)),Chars.Pixmap(data->descParty(i,2)));
            preview[i]->setLocation(data->descLocation(i));
            preview[i]->setName(data->descName(i));
            preview[i]->setLevel(data->descLevel(i));
            preview[i]->setGil(data->descGil(i));
            preview[i]->setTime((data->descTime(i)/3600),(data->descTime(i)/60 %60));
        }
        else if(data->region(i).isEmpty() && data->psx_block_type(i) != 0x52 && data->psx_block_type(i) != 0x53)
        {
            preview[i]->setMode(0);
            preview[i]->setLocation(tr("-Empty-"));
        }
        else
        {// all other psx saves.
            preview[i]->setMode(1);
            QByteArray icon_data;
            icon_data= data->slot_header(i);

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
            if(data->psx_block_type(i)==0xA1){Slottext.append(tr("(Deleted)"));}
            Slottext.append(tr("\n\t Game Uses %1 Save Block").arg(QString::number(data->psx_block_size(i))));
            if(data->psx_block_next(i)!=0xFF){Slottext.append(tr("s; Next Data Chunk @ Slot:%1").arg(QString::number(data->psx_block_next(i)+1)));}
            preview[i]->setLocation(Slottext);
        }
        //more checks after this....
        //for any item
        preview[i]->set_Button_Label(QString((tr("Slot:%1"))).arg(QString::number(i+1)));
        if(QT_VERSION<0x050000)
        {//QT4 Style Connection
            connect(preview[i],SIGNAL(button_clicked(QString)),this,SLOT(button_clicked(QString)));
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
