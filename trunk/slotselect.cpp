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

#include "slotselect.h"
#include "ui_slotselect.h"
#include <globals.h>

SlotSelect::SlotSelect(QWidget *parent,FF7 *ff7data) :
    QDialog(parent),
    ui(new Ui::SlotSelect)
{
    ui->setupUi(this);
    ff7 = ff7data;
    bool not_pc = false;
    int index=0;
    this->setWindowFlags(((this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));//remove close button
/*~~~~~~~~~~SLOT 1~~~~~~~~~~*/
    for(int s=0;s<15;s++)
    {
        not_pc=false;
        if(ff7->SG_TYPE!="PC")
        {
            not_pc=true;
            index= 128+(128*s);
            if(ff7->SG_TYPE=="PSP"){index+=0x80;}
            else if(ff7->SG_TYPE=="VGS"){index+=0x40;}
            else if(ff7->SG_TYPE=="DEX"){index+=0xF40;}
        }
        if(not_pc && ((ff7->file_headerp[index]==0x52) || (ff7->file_headerp[index] ==0x53)))
        {// if not pc then we need to check if its a linked slot
            QByteArray data;
            for(int i=0;i<0x200;i++){data.append(ff7->hf[s].sl_header[i]);}

            switch((quint8)data.at(2))
            {
                case 0x11://1 frame
                    icons[s].setAll(data.mid(96,160));
                break;

                case 0x12://2 frames
                    icons[s].setAll(data.mid(96,288), 2);
                break;

                case 0x13://3 frames
                    icons[s].setAll(data.mid(96,416),3);
                break;

                default: //Black Box
                    QByteArray tmp;
                    tmp.fill(00,0x200);
                    icons[s].setAll(tmp);
                break;
            }
            QString Slottext;
            if(ff7->file_headerp[index] == 0x52){Slottext =tr("\n\n Mid-Linked Block Next Data Chunk @ Slot:%1").arg(QString::number(ff7->file_headerp[index+0x08]+1));}
            else if(ff7->file_headerp[index] == 0x53){Slottext =tr("\n\n End Of Linked Blocks");}
            else{return;}

            QHBoxLayout *hbox = new QHBoxLayout;
            QVBoxLayout *vbox = new QVBoxLayout;
            switch(s)
            {
            case 0:
                ui->s1_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s1_party1, SLOT(setPixmap(QPixmap)));
                ui->s1_box->layout()->~QLayout();
                ui->s1_frame_avatar->setHidden(1);
                ui->s1_lbl_name->~QFrame();
                ui->s1_frame_level->~QWidget();
                ui->s1_frame_time->~QWidget();
                hbox->addWidget(ui->s1_party1);
                hbox->addWidget(ui->s1_lbl_loc);
                vbox->addWidget(ui->btn_s1);
                vbox->addItem(hbox);
                ui->s1_box->setLayout(vbox);
                ui->s1_lbl_loc->setText(Slottext);
                ui->s1_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s1_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s1_party1->show();
            break;

            case 1:
                ui->s2_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s2_party1, SLOT(setPixmap(QPixmap)));
                ui->s2_box->layout()->~QLayout();
                ui->s2_frame_avatar->setHidden(1);
                ui->s2_lbl_name->~QFrame();
                ui->s2_frame_level->~QWidget();
                ui->s2_frame_time->~QWidget();
                hbox->addWidget(ui->s2_party1);
                hbox->addWidget(ui->s2_lbl_loc);
                vbox->addWidget(ui->btn_s2);
                vbox->addItem(hbox);
                ui->s2_box->setLayout(vbox);
                ui->s2_lbl_loc->setText(Slottext);
                ui->s2_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s2_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s2_party1->show();
            break;

            case 2:
                ui->s3_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s3_party1, SLOT(setPixmap(QPixmap)));
                ui->s3_box->layout()->~QLayout();
                ui->s3_frame_avatar->setHidden(1);
                ui->s3_lbl_name->~QFrame();
                ui->s3_frame_level->~QWidget();
                ui->s3_frame_time->~QWidget();
                hbox->addWidget(ui->s3_party1);
                hbox->addWidget(ui->s3_lbl_loc);
                vbox->addWidget(ui->btn_s3);
                vbox->addItem(hbox);
                ui->s3_box->setLayout(vbox);
                ui->s3_lbl_loc->setText(Slottext);
                ui->s3_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s3_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s3_party1->show();
            break;

            case 3:
                ui->s4_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s4_party1, SLOT(setPixmap(QPixmap)));
                ui->s4_box->layout()->~QLayout();
                ui->s4_frame_avatar->setHidden(1);
                ui->s4_lbl_name->~QFrame();
                ui->s4_frame_level->~QWidget();
                ui->s4_frame_time->~QWidget();
                hbox->addWidget(ui->s4_party1);
                hbox->addWidget(ui->s4_lbl_loc);
                vbox->addWidget(ui->btn_s4);
                vbox->addItem(hbox);
                ui->s4_box->setLayout(vbox);
                ui->s4_lbl_loc->setText(Slottext);
                ui->s4_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s4_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s4_party1->show();
            break;

            case 4:
                ui->s5_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s5_party1, SLOT(setPixmap(QPixmap)));
                ui->s5_box->layout()->~QLayout();
                ui->s5_frame_avatar->setHidden(1);
                ui->s5_lbl_name->~QFrame();
                ui->s5_frame_level->~QWidget();
                ui->s5_frame_time->~QWidget();
                hbox->addWidget(ui->s5_party1);
                hbox->addWidget(ui->s5_lbl_loc);
                vbox->addWidget(ui->btn_s5);
                vbox->addItem(hbox);
                ui->s5_box->setLayout(vbox);
                ui->s5_lbl_loc->setText(Slottext);
                ui->s5_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s5_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s5_party1->show();
            break;

            case 5:
                ui->s6_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s6_party1, SLOT(setPixmap(QPixmap)));
                ui->s6_box->layout()->~QLayout();
                ui->s6_frame_avatar->setHidden(1);
                ui->s6_lbl_name->~QFrame();
                ui->s6_frame_level->~QWidget();
                ui->s6_frame_time->~QWidget();
                hbox->addWidget(ui->s6_party1);
                hbox->addWidget(ui->s6_lbl_loc);
                vbox->addWidget(ui->btn_s6);
                vbox->addItem(hbox);
                ui->s6_box->setLayout(vbox);
                ui->s6_lbl_loc->setText(Slottext);
                ui->s6_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s6_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s6_party1->show();
            break;

            case 6:
                ui->s7_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s7_party1, SLOT(setPixmap(QPixmap)));
                ui->s7_box->layout()->~QLayout();
                ui->s7_frame_avatar->setHidden(1);
                ui->s7_lbl_name->~QFrame();
                ui->s7_frame_level->~QWidget();
                ui->s7_frame_time->~QWidget();
                hbox->addWidget(ui->s7_party1);
                hbox->addWidget(ui->s7_lbl_loc);
                vbox->addWidget(ui->btn_s7);
                vbox->addItem(hbox);
                ui->s7_box->setLayout(vbox);
                ui->s7_lbl_loc->setText(Slottext);
                ui->s7_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s7_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s7_party1->show();
            break;

            case 7:
                ui->s8_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s8_party1, SLOT(setPixmap(QPixmap)));
                ui->s8_box->layout()->~QLayout();
                ui->s8_frame_avatar->setHidden(1);
                ui->s8_lbl_name->~QFrame();
                ui->s8_frame_level->~QWidget();
                ui->s8_frame_time->~QWidget();
                hbox->addWidget(ui->s8_party1);
                hbox->addWidget(ui->s8_lbl_loc);
                vbox->addWidget(ui->btn_s8);
                vbox->addItem(hbox);
                ui->s8_box->setLayout(vbox);
                ui->s8_lbl_loc->setText(Slottext);
                ui->s8_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s8_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s8_party1->show();
            break;

            case 8:
                ui->s9_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s9_party1, SLOT(setPixmap(QPixmap)));
                ui->s9_box->layout()->~QLayout();
                ui->s9_frame_avatar->setHidden(1);
                ui->s9_lbl_name->~QFrame();
                ui->s9_frame_level->~QWidget();
                ui->s9_frame_time->~QWidget();
                hbox->addWidget(ui->s9_party1);
                hbox->addWidget(ui->s9_lbl_loc);
                vbox->addWidget(ui->btn_s9);
                vbox->addItem(hbox);
                ui->s9_box->setLayout(vbox);
                ui->s9_lbl_loc->setText(Slottext);
                ui->s9_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s9_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s9_party1->show();
            break;

            case 9:
                ui->s10_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s10_party1, SLOT(setPixmap(QPixmap)));
                ui->s10_box->layout()->~QLayout();
                ui->s10_frame_avatar->setHidden(1);
                ui->s10_lbl_name->~QFrame();
                ui->s10_frame_level->~QWidget();
                ui->s10_frame_time->~QWidget();
                hbox->addWidget(ui->s10_party1);
                hbox->addWidget(ui->s10_lbl_loc);
                vbox->addWidget(ui->btn_s10);
                vbox->addItem(hbox);
                ui->s10_box->setLayout(vbox);
                ui->s10_lbl_loc->setText(Slottext);
                ui->s10_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s10_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s10_party1->show();
            break;

            case 10:
                ui->s11_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s11_party1, SLOT(setPixmap(QPixmap)));
                ui->s11_box->layout()->~QLayout();
                ui->s11_frame_avatar->setHidden(1);
                ui->s11_lbl_name->~QFrame();
                ui->s11_frame_level->~QWidget();
                ui->s11_frame_time->~QWidget();
                hbox->addWidget(ui->s11_party1);
                hbox->addWidget(ui->s11_lbl_loc);
                vbox->addWidget(ui->btn_s11);
                vbox->addItem(hbox);
                ui->s11_box->setLayout(vbox);
                ui->s11_lbl_loc->setText(Slottext);
                ui->s11_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s11_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s11_party1->show();
            break;

            case 11:
                ui->s12_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s12_party1, SLOT(setPixmap(QPixmap)));
                ui->s12_box->layout()->~QLayout();
                ui->s12_frame_avatar->setHidden(1);
                ui->s12_lbl_name->~QFrame();
                ui->s12_frame_level->~QWidget();
                ui->s12_frame_time->~QWidget();
                hbox->addWidget(ui->s12_party1);
                hbox->addWidget(ui->s12_lbl_loc);
                vbox->addWidget(ui->btn_s12);
                vbox->addItem(hbox);
                ui->s12_box->setLayout(vbox);
                ui->s12_lbl_loc->setText(Slottext);
                ui->s12_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s12_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s12_party1->show();
            break;

            case 12:
                ui->s13_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s13_party1, SLOT(setPixmap(QPixmap)));
                ui->s13_box->layout()->~QLayout();
                ui->s13_frame_avatar->setHidden(1);
                ui->s13_lbl_name->~QFrame();
                ui->s13_frame_level->~QWidget();
                ui->s13_frame_time->~QWidget();
                hbox->addWidget(ui->s13_party1);
                hbox->addWidget(ui->s13_lbl_loc);
                vbox->addWidget(ui->btn_s13);
                vbox->addItem(hbox);
                ui->s13_box->setLayout(vbox);
                ui->s13_lbl_loc->setText(Slottext);
                ui->s13_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s13_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s13_party1->show();
            break;

            case 13:
                ui->s14_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s14_party1, SLOT(setPixmap(QPixmap)));
                ui->s14_box->layout()->~QLayout();
                ui->s14_frame_avatar->setHidden(1);
                ui->s14_lbl_name->~QFrame();
                ui->s14_frame_level->~QWidget();
                ui->s14_frame_time->~QWidget();
                hbox->addWidget(ui->s14_party1);
                hbox->addWidget(ui->s14_lbl_loc);
                vbox->addWidget(ui->btn_s14);
                vbox->addItem(hbox);
                ui->s14_box->setLayout(vbox);
                ui->s14_lbl_loc->setText(Slottext);
                ui->s14_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s14_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s14_party1->show();
            break;

            case 14:
                ui->s15_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s15_party1, SLOT(setPixmap(QPixmap)));
                ui->s15_box->layout()->~QLayout();
                ui->s15_frame_avatar->setHidden(1);
                ui->s15_lbl_name->~QFrame();
                ui->s15_frame_level->~QWidget();
                ui->s15_frame_time->~QWidget();
                hbox->addWidget(ui->s15_party1);
                hbox->addWidget(ui->s15_lbl_loc);
                vbox->addWidget(ui->btn_s15);
                vbox->addItem(hbox);
                ui->s15_box->setLayout(vbox);
                ui->s15_lbl_loc->setText(Slottext);
                ui->s15_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s15_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s15_party1->show();
            break;
            }
        }
        else if(ff7->SG_Region_String[s].isEmpty())//Empty Slot
        {//regular empty slot
            QString Slottext =tr("\nEmpty");
            QVBoxLayout *layout = new QVBoxLayout;
            switch(s)
            {

            case 0:
                ui->s1_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s1_lbl_name->~QFrame();
                ui->s1_frame_avatar->~QWidget();
                ui->s1_frame_level->~QWidget();
                ui->s1_frame_time->~QWidget();
                //set up new text and layout.
                ui->s1_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s1_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s1_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s1);    layout->addWidget(ui->s1_lbl_loc);
                ui->s1_box->setLayout(layout);
            break;

            case 1:
                ui->s2_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s2_lbl_name->~QFrame();
                ui->s2_frame_avatar->~QWidget();
                ui->s2_frame_level->~QWidget();
                ui->s2_frame_time->~QWidget();
                //set up new text and layout.
                ui->s2_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s2_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s2_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s2);    layout->addWidget(ui->s2_lbl_loc);
                ui->s2_box->setLayout(layout);
            break;

            case 2:
                ui->s3_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s3_lbl_name->~QFrame();
                ui->s3_frame_avatar->~QWidget();
                ui->s3_frame_level->~QWidget();
                ui->s3_frame_time->~QWidget();
                //set up new text and layout.
                ui->s3_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s3_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s3_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s3);    layout->addWidget(ui->s3_lbl_loc);
                ui->s3_box->setLayout(layout);
            break;

            case 3:
                ui->s4_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s4_lbl_name->~QFrame();
                ui->s4_frame_avatar->~QWidget();
                ui->s4_frame_level->~QWidget();
                ui->s4_frame_time->~QWidget();
                //set up new text and layout.
                ui->s4_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s4_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s4_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s4);    layout->addWidget(ui->s4_lbl_loc);
                ui->s4_box->setLayout(layout);
            break;

            case 4:
                ui->s5_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s5_lbl_name->~QFrame();
                ui->s5_frame_avatar->~QWidget();
                ui->s5_frame_level->~QWidget();
                ui->s5_frame_time->~QWidget();
                //set up new text and layout.
                ui->s5_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s5_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s5_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s5);    layout->addWidget(ui->s5_lbl_loc);
                ui->s5_box->setLayout(layout);
            break;

            case 5:
                ui->s6_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s6_lbl_name->~QFrame();
                ui->s6_frame_avatar->~QWidget();
                ui->s6_frame_level->~QWidget();
                ui->s6_frame_time->~QWidget();
                //set up new text and layout.
                ui->s6_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s6_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s6_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s6);    layout->addWidget(ui->s6_lbl_loc);
                ui->s6_box->setLayout(layout);
            break;

            case 6:
                ui->s7_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s7_lbl_name->~QFrame();
                ui->s7_frame_avatar->~QWidget();
                ui->s7_frame_level->~QWidget();
                ui->s7_frame_time->~QWidget();
                //set up new text and layout.
                ui->s7_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s7_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s7_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s7);    layout->addWidget(ui->s7_lbl_loc);
                ui->s7_box->setLayout(layout);
            break;

            case 7:
                ui->s8_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s8_lbl_name->~QFrame();
                ui->s8_frame_avatar->~QWidget();
                ui->s8_frame_level->~QWidget();
                ui->s8_frame_time->~QWidget();
                //set up new text and layout.
                ui->s8_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s8_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s8_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s8);    layout->addWidget(ui->s8_lbl_loc);
                ui->s8_box->setLayout(layout);
            break;

            case 8:
                ui->s9_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s9_lbl_name->~QFrame();
                ui->s9_frame_avatar->~QWidget();
                ui->s9_frame_level->~QWidget();
                ui->s9_frame_time->~QWidget();
                //set up new text and layout.
                ui->s9_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s9_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s9_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s9);    layout->addWidget(ui->s9_lbl_loc);
                ui->s9_box->setLayout(layout);
            break;

            case 9:
                ui->s10_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s10_lbl_name->~QFrame();
                ui->s10_frame_avatar->~QWidget();
                ui->s10_frame_level->~QWidget();
                ui->s10_frame_time->~QWidget();
                //set up new text and layout.
                ui->s10_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s10_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s10_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s10);    layout->addWidget(ui->s10_lbl_loc);
                ui->s10_box->setLayout(layout);
            break;

            case 10:
                ui->s11_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s11_lbl_name->~QFrame();
                ui->s11_frame_avatar->~QWidget();
                ui->s11_frame_level->~QWidget();
                ui->s11_frame_time->~QWidget();
                //set up new text and layout.
                ui->s11_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s11_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s11_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s11);    layout->addWidget(ui->s11_lbl_loc);
                ui->s11_box->setLayout(layout);
            break;

            case 11:
                ui->s12_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s12_lbl_name->~QFrame();
                ui->s12_frame_avatar->~QWidget();
                ui->s12_frame_level->~QWidget();
                ui->s12_frame_time->~QWidget();
                //set up new text and layout.
                ui->s12_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s12_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s12_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s12);    layout->addWidget(ui->s12_lbl_loc);
                ui->s12_box->setLayout(layout);
            break;

            case 12:
                ui->s13_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s13_lbl_name->~QFrame();
                ui->s13_frame_avatar->~QWidget();
                ui->s13_frame_level->~QWidget();
                ui->s13_frame_time->~QWidget();
                //set up new text and layout.
                ui->s13_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s13_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s13_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s13);    layout->addWidget(ui->s13_lbl_loc);
                ui->s13_box->setLayout(layout);
            break;

            case 13:
                ui->s14_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s14_lbl_name->~QFrame();
                ui->s14_frame_avatar->~QWidget();
                ui->s14_frame_level->~QWidget();
                ui->s14_frame_time->~QWidget();
                //set up new text and layout.
                ui->s14_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s14_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s14_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s14);    layout->addWidget(ui->s14_lbl_loc);
                ui->s14_box->setLayout(layout);
            break;

            case 14:
                ui->s15_box->layout()->~QLayout();
                //remove all the other stuff
                ui->s15_lbl_name->~QFrame();
                ui->s15_frame_avatar->~QWidget();
                ui->s15_frame_level->~QWidget();
                ui->s15_frame_time->~QWidget();
                //set up new text and layout.
                ui->s15_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s15_lbl_loc->setStyleSheet("color:rgb(255,255,0);");
                ui->s15_lbl_loc->setText(Slottext);;
                layout->addWidget(ui->btn_s15);    layout->addWidget(ui->s15_lbl_loc);
                ui->s15_box->setLayout(layout);
            break;
            }
        }
        else if(ff7->SG_Region_String[s].contains("00867") ||ff7->SG_Region_String[s].contains("00869") ||
                ff7->SG_Region_String[s].contains("00900") ||ff7->SG_Region_String[s].contains("94163") ||
                ff7->SG_Region_String[s].contains("00700") ||ff7->SG_Region_String[s].contains("01057") ||
                ff7->SG_Region_String[s].contains("00868"))
        {//FF7 Slot
            //theme the box
            QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
            style.append(QString::number(ff7->slot[s].colors[0][0]));    style.append(",");
            style.append(QString::number(ff7->slot[s].colors[0][1]));    style.append(",");
            style.append(QString::number(ff7->slot[s].colors[0][2]));    style.append(", 255), stop:1 rgba(");
            style.append(QString::number(ff7->slot[s].colors[2][0]));    style.append(",");
            style.append(QString::number(ff7->slot[s].colors[2][1]));    style.append(",");
            style.append(QString::number(ff7->slot[s].colors[2][2]));    style.append(", 255));");

            if( ff7->SG_Region_String[s].contains("00700") || ff7->SG_Region_String[s].contains("01057") ) {Text.init(1);}//Japanese
            else {Text.init(0);} // All others
            QByteArray location_text;
            QByteArray name_text;
            for (int loc=0; loc<32;loc++){location_text.append(ff7->slot[s].desc.location[loc]);}
            for (int n=0;n<16;n++){name_text.append(ff7->slot[s].desc.name[n]);}
            switch(s)
            {
            case 0:
                ui->s1_box->setStyleSheet(style);
                ui->s1_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s1_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s1_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s1_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s1_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s1_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s1_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s1_lbl_loc->setText(Text.toPC(location_text));
                ui->s1_lbl_name->setText(Text.toPC(name_text));
            break;

            case 1:
                ui->s2_box->setStyleSheet(style);
                ui->s2_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s2_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s2_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s2_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s2_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s2_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s2_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s2_lbl_loc->setText(Text.toPC(location_text));
                ui->s2_lbl_name->setText(Text.toPC(name_text));
            break;

            case 2:
                ui->s3_box->setStyleSheet(style);
                ui->s3_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s3_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s3_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s3_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s3_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s3_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s3_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s3_lbl_loc->setText(Text.toPC(location_text));
                ui->s3_lbl_name->setText(Text.toPC(name_text));
            break;

            case 3:
                ui->s4_box->setStyleSheet(style);
                ui->s4_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s4_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s4_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s4_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s4_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s4_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s4_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s4_lbl_loc->setText(Text.toPC(location_text));
                ui->s4_lbl_name->setText(Text.toPC(name_text));
            break;

            case 4:
                ui->s5_box->setStyleSheet(style);
                ui->s5_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s5_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s5_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s5_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s5_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s5_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s5_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s5_lbl_loc->setText(Text.toPC(location_text));
                ui->s5_lbl_name->setText(Text.toPC(name_text));
            break;

            case 5:
                ui->s6_box->setStyleSheet(style);
                ui->s6_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s6_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s6_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s6_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s6_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s6_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s6_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s6_lbl_loc->setText(Text.toPC(location_text));
                ui->s6_lbl_name->setText(Text.toPC(name_text));
            break;

            case 6:
                ui->s7_box->setStyleSheet(style);
                ui->s7_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s7_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s7_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s7_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s7_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s7_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s7_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s7_lbl_loc->setText(Text.toPC(location_text));
                ui->s7_lbl_name->setText(Text.toPC(name_text));
            break;

            case 7:
                ui->s8_box->setStyleSheet(style);
                ui->s8_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s8_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s8_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s8_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s8_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s8_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s8_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s8_lbl_loc->setText(Text.toPC(location_text));
                ui->s8_lbl_name->setText(Text.toPC(name_text));
            break;

            case 8:
                ui->s9_box->setStyleSheet(style);
                ui->s9_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s9_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s9_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s9_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s9_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s9_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s9_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s9_lbl_loc->setText(Text.toPC(location_text));
                ui->s9_lbl_name->setText(Text.toPC(name_text));
            break;
            case 9:
                ui->s10_box->setStyleSheet(style);
                ui->s10_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s10_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s10_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s10_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s10_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s10_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s10_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s10_lbl_loc->setText(Text.toPC(location_text));
                ui->s10_lbl_name->setText(Text.toPC(name_text));
            break;

            case 10:
                ui->s11_box->setStyleSheet(style);
                ui->s11_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s11_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s11_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s11_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s11_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s11_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s11_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s11_lbl_loc->setText(Text.toPC(location_text));
                ui->s11_lbl_name->setText(Text.toPC(name_text));
            break;

            case 11:
                ui->s12_box->setStyleSheet(style);
                ui->s12_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s12_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s12_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s12_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s12_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s12_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s12_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s12_lbl_loc->setText(Text.toPC(location_text));
                ui->s12_lbl_name->setText(Text.toPC(name_text));
            break;

            case 12:
                ui->s13_box->setStyleSheet(style);
                ui->s13_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s13_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s13_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s13_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s13_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s13_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s13_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s13_lbl_loc->setText(Text.toPC(location_text));
                ui->s13_lbl_name->setText(Text.toPC(name_text));
            break;

            case 13:
                ui->s14_box->setStyleSheet(style);
                ui->s14_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s14_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s14_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s14_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s14_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s14_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s14_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s14_lbl_loc->setText(Text.toPC(location_text));
                ui->s14_lbl_name->setText(Text.toPC(name_text));
            break;

            case 14:
                ui->s15_box->setStyleSheet(style);
                ui->s15_party1->setStyleSheet(avatar_style(ff7->slot[s].desc.party[0]));
                ui->s15_party2->setStyleSheet(avatar_style(ff7->slot[s].desc.party[1]));
                ui->s15_party3->setStyleSheet(avatar_style(ff7->slot[s].desc.party[2]));
                ui->s15_lbl_lvl->setText(QString::number(ff7->slot[s].desc.level));
                ui->s15_lbl_gil->setText(QString::number(ff7->slot[s].desc.gil));
                ui->s15_lbl_hr->setText(QString::number(ff7->slot[s].desc.time/3600));
                ui->s15_lbl_min->setText(QString::number(ff7->slot[s].desc.time/60 %60));
                ui->s15_lbl_loc->setText(Text.toPC(location_text));
                ui->s15_lbl_name->setText(Text.toPC(name_text));
            break;
            }
        }
        else//NOT FF7 Show Icon and Region String;
        {
            QByteArray data;
            for(int i=0;i<0x200;i++){data.append(ff7->hf[s].sl_header[i]);}
            switch((quint8)data.at(2))
            {
            case 0x11://1 frame
                icons[s].setAll(data.mid(96,160));
            break;

            case 0x12://2 frames
                icons[s].setAll(data.mid(96,288), 2);
            break;

            case 0x13://3 frames
                icons[s].setAll(data.mid(96,416), 3);
            break;

            default: //Black Box
                QByteArray tmp;
                tmp.fill(00,0x200);
                icons[s].setAll(tmp);
            break;
            }
            /*Make The Names Nice*/
            QByteArray desc;
            QTextCodec *codec = QTextCodec::codecForName(QByteArray("Shift-JIS"));
            desc = data.mid(4,64);

            int desc_end;
            if((desc_end = desc.indexOf('\x00')) != -1) {desc.truncate(desc_end);}

            QString Slottext ="\n\n" + codec->toUnicode(desc);
            if(ff7->file_headerp[index]==0xA1){Slottext.append(tr("(Deleted)"));}
            QByteArray temp;
            temp.resize(3);
            temp[0]=ff7->file_headerp[index+0x04];
            temp[1]=ff7->file_headerp[index+0x05];
            temp[2]=ff7->file_headerp[index+0x06];
            qint32 value = temp[0] | (temp[1] << 8) | (temp[2] <<16);
            Slottext.append(tr("\n Game Uses %1 Save Block").arg(QString::number(value/0x2000)));
            if(ff7->file_headerp[index+0x08]!=0xFF){Slottext.append(tr("s; Next Data Chunk @ Slot:%1").arg(QString::number(ff7->file_headerp[index+0x08]+1)));}

            QHBoxLayout *hbox = new QHBoxLayout;
            QVBoxLayout *vbox = new QVBoxLayout;

            switch(s)
            {
            case 0:
                ui->s1_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s1_party1, SLOT(setPixmap(QPixmap)));
                ui->s1_box->layout()->~QLayout();
                ui->s1_frame_avatar->setHidden(1);
                ui->s1_lbl_name->~QFrame();
                ui->s1_frame_level->~QWidget();
                ui->s1_frame_time->~QWidget();
                hbox->addWidget(ui->s1_party1);
                hbox->addWidget(ui->s1_lbl_loc);
                vbox->addWidget(ui->btn_s1);
                vbox->addItem(hbox);
                ui->s1_box->setLayout(vbox);
                ui->s1_lbl_loc->setText(Slottext);
                ui->s1_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s1_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s1_party1->show();
            break;

            case 1:
                ui->s2_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s2_party1, SLOT(setPixmap(QPixmap)));
                ui->s2_box->layout()->~QLayout();
                ui->s2_frame_avatar->setHidden(1);
                ui->s2_lbl_name->~QFrame();
                ui->s2_frame_level->~QWidget();
                ui->s2_frame_time->~QWidget();
                hbox->addWidget(ui->s2_party1);
                hbox->addWidget(ui->s2_lbl_loc);
                vbox->addWidget(ui->btn_s2);
                vbox->addItem(hbox);
                ui->s2_box->setLayout(vbox);
                ui->s2_lbl_loc->setText(Slottext);
                ui->s2_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s2_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s2_party1->show();
             break;

            case 2:
                ui->s3_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s3_party1, SLOT(setPixmap(QPixmap)));
                ui->s3_box->layout()->~QLayout();
                ui->s3_frame_avatar->setHidden(1);
                ui->s3_lbl_name->~QFrame();
                ui->s3_frame_level->~QWidget();
                ui->s3_frame_time->~QWidget();
                hbox->addWidget(ui->s3_party1);
                hbox->addWidget(ui->s3_lbl_loc);
                vbox->addWidget(ui->btn_s3);
                vbox->addItem(hbox);
                ui->s3_box->setLayout(vbox);
                ui->s3_lbl_loc->setText(Slottext);
                ui->s3_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s3_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s3_party1->show();
            break;

            case 3:
                ui->s4_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s4_party1, SLOT(setPixmap(QPixmap)));
                ui->s4_box->layout()->~QLayout();
                ui->s4_frame_avatar->setHidden(1);
                ui->s4_lbl_name->~QFrame();
                ui->s4_frame_level->~QWidget();
                ui->s4_frame_time->~QWidget();
                hbox->addWidget(ui->s4_party1);
                hbox->addWidget(ui->s4_lbl_loc);
                vbox->addWidget(ui->btn_s4);
                vbox->addItem(hbox);
                ui->s4_box->setLayout(vbox);
                ui->s4_lbl_loc->setText(Slottext);
                ui->s4_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s4_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s4_party1->show();
            break;

            case 4:
                ui->s5_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s5_party1, SLOT(setPixmap(QPixmap)));
                ui->s5_box->layout()->~QLayout();
                ui->s5_frame_avatar->setHidden(1);
                ui->s5_lbl_name->~QFrame();
                ui->s5_frame_level->~QWidget();
                ui->s5_frame_time->~QWidget();
                hbox->addWidget(ui->s5_party1);
                hbox->addWidget(ui->s5_lbl_loc);
                vbox->addWidget(ui->btn_s5);
                vbox->addItem(hbox);
                ui->s5_box->setLayout(vbox);
                ui->s5_lbl_loc->setText(Slottext);
                ui->s5_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s5_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s5_party1->show();
            break;

            case 5:
                ui->s6_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s6_party1, SLOT(setPixmap(QPixmap)));
                ui->s6_box->layout()->~QLayout();
                ui->s6_frame_avatar->setHidden(1);
                ui->s6_lbl_name->~QFrame();
                ui->s6_frame_level->~QWidget();
                ui->s6_frame_time->~QWidget();
                hbox->addWidget(ui->s6_party1);
                hbox->addWidget(ui->s6_lbl_loc);
                vbox->addWidget(ui->btn_s6);
                vbox->addItem(hbox);
                ui->s6_box->setLayout(vbox);
                ui->s6_lbl_loc->setText(Slottext);
                ui->s6_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s6_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s6_party1->show();
            break;

            case 6:
                ui->s7_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s7_party1, SLOT(setPixmap(QPixmap)));
                ui->s7_box->layout()->~QLayout();
                ui->s7_frame_avatar->setHidden(1);
                ui->s7_lbl_name->~QFrame();
                ui->s7_frame_level->~QWidget();
                ui->s7_frame_time->~QWidget();
                hbox->addWidget(ui->s7_party1);
                hbox->addWidget(ui->s7_lbl_loc);
                vbox->addWidget(ui->btn_s7);
                vbox->addItem(hbox);
                ui->s7_box->setLayout(vbox);
                ui->s7_lbl_loc->setText(Slottext);
                ui->s7_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s7_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s7_party1->show();
            break;

            case 7:
                ui->s8_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s8_party1, SLOT(setPixmap(QPixmap)));
                ui->s8_box->layout()->~QLayout();
                ui->s8_frame_avatar->setHidden(1);
                ui->s8_lbl_name->~QFrame();
                ui->s8_frame_level->~QWidget();
                ui->s8_frame_time->~QWidget();
                hbox->addWidget(ui->s8_party1);
                hbox->addWidget(ui->s8_lbl_loc);
                vbox->addWidget(ui->btn_s8);
                vbox->addItem(hbox);
                ui->s8_box->setLayout(vbox);
                ui->s8_lbl_loc->setText(Slottext);
                ui->s8_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s8_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s8_party1->show();
            break;

            case 8:
                ui->s9_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s9_party1, SLOT(setPixmap(QPixmap)));
                ui->s9_box->layout()->~QLayout();
                ui->s9_frame_avatar->setHidden(1);
                ui->s9_lbl_name->~QFrame();
                ui->s9_frame_level->~QWidget();
                ui->s9_frame_time->~QWidget();
                hbox->addWidget(ui->s9_party1);
                hbox->addWidget(ui->s9_lbl_loc);
                vbox->addWidget(ui->btn_s9);
                vbox->addItem(hbox);
                ui->s9_box->setLayout(vbox);
                ui->s9_lbl_loc->setText(Slottext);
                ui->s9_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s9_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s9_party1->show();
            break;

            case 9:
                ui->s10_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s10_party1, SLOT(setPixmap(QPixmap)));
                ui->s10_box->layout()->~QLayout();
                ui->s10_frame_avatar->setHidden(1);
                ui->s10_lbl_name->~QFrame();
                ui->s10_frame_level->~QWidget();
                ui->s10_frame_time->~QWidget();
                hbox->addWidget(ui->s10_party1);
                hbox->addWidget(ui->s10_lbl_loc);
                vbox->addWidget(ui->btn_s10);
                vbox->addItem(hbox);
                ui->s10_box->setLayout(vbox);
                ui->s10_lbl_loc->setText(Slottext);
                ui->s10_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s10_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s10_party1->show();
            break;

            case 10:
                ui->s11_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s11_party1, SLOT(setPixmap(QPixmap)));
                ui->s11_box->layout()->~QLayout();
                ui->s11_frame_avatar->setHidden(1);
                ui->s11_lbl_name->~QFrame();
                ui->s11_frame_level->~QWidget();
                ui->s11_frame_time->~QWidget();
                hbox->addWidget(ui->s11_party1);
                hbox->addWidget(ui->s11_lbl_loc);
                vbox->addWidget(ui->btn_s11);
                vbox->addItem(hbox);
                ui->s11_box->setLayout(vbox);
                ui->s11_lbl_loc->setText(Slottext);
                ui->s11_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s11_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s11_party1->show();
            break;

            case 11:
                ui->s12_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s12_party1, SLOT(setPixmap(QPixmap)));
                ui->s12_box->layout()->~QLayout();
                ui->s12_frame_avatar->setHidden(1);
                ui->s12_lbl_name->~QFrame();
                ui->s12_frame_level->~QWidget();
                ui->s12_frame_time->~QWidget();
                hbox->addWidget(ui->s12_party1);
                hbox->addWidget(ui->s12_lbl_loc);
                vbox->addWidget(ui->btn_s12);
                vbox->addItem(hbox);
                ui->s12_box->setLayout(vbox);
                ui->s12_lbl_loc->setText(Slottext);
                ui->s12_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s12_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s12_party1->show();
            break;

            case 12:
                ui->s13_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s13_party1, SLOT(setPixmap(QPixmap)));
                ui->s13_box->layout()->~QLayout();
                ui->s13_frame_avatar->setHidden(1);
                ui->s13_lbl_name->~QFrame();
                ui->s13_frame_level->~QWidget();
                ui->s13_frame_time->~QWidget();
                hbox->addWidget(ui->s13_party1);
                hbox->addWidget(ui->s13_lbl_loc);
                vbox->addWidget(ui->btn_s13);
                vbox->addItem(hbox);
                ui->s13_box->setLayout(vbox);
                ui->s13_lbl_loc->setText(Slottext);
                ui->s13_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s13_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s13_party1->show();
            break;

            case 13:
                ui->s14_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s14_party1, SLOT(setPixmap(QPixmap)));
                ui->s14_box->layout()->~QLayout();
                ui->s14_frame_avatar->setHidden(1);
                ui->s14_lbl_name->~QFrame();
                ui->s14_frame_level->~QWidget();
                ui->s14_frame_time->~QWidget();
                hbox->addWidget(ui->s14_party1);
                hbox->addWidget(ui->s14_lbl_loc);
                vbox->addWidget(ui->btn_s14);
                vbox->addItem(hbox);
                ui->s14_box->setLayout(vbox);
                ui->s14_lbl_loc->setText(Slottext);
                ui->s14_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s14_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s14_party1->show();
            break;

            case 14:
                ui->s15_party1->setPixmap(icons[s].icon());
                connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s15_party1, SLOT(setPixmap(QPixmap)));
                ui->s15_box->layout()->~QLayout();
                ui->s15_frame_avatar->setHidden(1);
                ui->s15_lbl_name->~QFrame();
                ui->s15_frame_level->~QWidget();
                ui->s15_frame_time->~QWidget();
                hbox->addWidget(ui->s15_party1);
                hbox->addWidget(ui->s15_lbl_loc);
                vbox->addWidget(ui->btn_s15);
                vbox->addItem(hbox);
                ui->s15_box->setLayout(vbox);
                ui->s15_lbl_loc->setText(Slottext);
                ui->s15_lbl_loc->setAlignment(Qt::AlignLeft);
                ui->s15_lbl_loc->setStyleSheet("font-size: 10pt;");
                ui->s15_party1->show();
            break;
            }
        }//end of else
    }//end of for Loop
}//end of new ui
SlotSelect::~SlotSelect()
{
    delete ui;
}

void SlotSelect::changeEvent(QEvent *e)
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
void SlotSelect::keyPressEvent(QKeyEvent *e)
{
    if(e->key()!=Qt::Key_Escape) QDialog::keyPressEvent(e);
}
void SlotSelect::on_btn_s1_clicked(){this->done(0);}
void SlotSelect::on_btn_s2_clicked(){this->done(1);}
void SlotSelect::on_btn_s3_clicked(){this->done(2);}
void SlotSelect::on_btn_s4_clicked(){this->done(3);}
void SlotSelect::on_btn_s5_clicked(){this->done(4);}
void SlotSelect::on_btn_s6_clicked(){this->done(5);}
void SlotSelect::on_btn_s7_clicked(){this->done(6);}
void SlotSelect::on_btn_s8_clicked(){this->done(7);}
void SlotSelect::on_btn_s9_clicked(){this->done(8);}
void SlotSelect::on_btn_s10_clicked(){this->done(9);}
void SlotSelect::on_btn_s11_clicked(){this->done(10);}
void SlotSelect::on_btn_s12_clicked(){this->done(11);}
void SlotSelect::on_btn_s13_clicked(){this->done(12);}
void SlotSelect::on_btn_s14_clicked(){this->done(13);}
void SlotSelect::on_btn_s15_clicked(){this->done(14);}
