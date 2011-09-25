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

extern FF7 ff7;
SaveIcon icons[15];

SlotSelect::SlotSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SlotSelect)
{
    ui->setupUi(this);
/*~~~~~~~~~~SLOT 1~~~~~~~~~~*/
    for(int s=0;s<15;s++)
    {
        if(ff7.SG_Region_String[s] == "")
        {
            switch(s)
            {
              case 0:   ui->s1_lbl_loc->setText(tr("Empty Slot"));  break;
              case 1:   ui->s2_lbl_loc->setText(tr("Empty Slot"));  break;
              case 2:   ui->s3_lbl_loc->setText(tr("Empty Slot"));  break;
              case 3:   ui->s4_lbl_loc->setText(tr("Empty Slot"));  break;
              case 4:   ui->s5_lbl_loc->setText(tr("Empty Slot"));  break;
              case 5:   ui->s6_lbl_loc->setText(tr("Empty Slot"));  break;
              case 6:   ui->s7_lbl_loc->setText(tr("Empty Slot"));  break;
              case 7:   ui->s8_lbl_loc->setText(tr("Empty Slot"));  break;
              case 8:   ui->s9_lbl_loc->setText(tr("Empty Slot"));  break;
              case 9:   ui->s10_lbl_loc->setText(tr("Empty Slot")); break;
              case 10:  ui->s11_lbl_loc->setText(tr("Empty Slot")); break;
              case 11:  ui->s12_lbl_loc->setText(tr("Empty Slot")); break;
              case 12:  ui->s13_lbl_loc->setText(tr("Empty Slot")); break;
              case 13:  ui->s14_lbl_loc->setText(tr("Empty Slot")); break;
              case 14:  ui->s15_lbl_loc->setText(tr("Empty Slot")); break;
            }
        }
        else if(ff7.SG_Region_String[s].contains("00867") ||ff7.SG_Region_String[s].contains("00869") ||
                ff7.SG_Region_String[s].contains("00900") ||ff7.SG_Region_String[s].contains("94163") ||
                ff7.SG_Region_String[s].contains("00700") ||ff7.SG_Region_String[s].contains("01057"))
        {//FF7 Slot
        //theme the box
            QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
            style.append(QString::number(ff7.slot[s].colors[0][0]));    style.append(",");
            style.append(QString::number(ff7.slot[s].colors[0][1]));    style.append(",");
            style.append(QString::number(ff7.slot[s].colors[0][2]));    style.append(", 255), stop:1 rgba(");
            style.append(QString::number(ff7.slot[s].colors[2][0]));    style.append(",");
            style.append(QString::number(ff7.slot[s].colors[2][1]));    style.append(",");
            style.append(QString::number(ff7.slot[s].colors[2][2]));    style.append(", 255));");

            switch(s)
            {
              case 0:	ui->s1_box->setStyleSheet(style);
                            ui->s1_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s1_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s1_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s1_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s1_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s1_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s1_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s1_lbl_loc->setText( ui->s1_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s1_lbl_name->setText( ui->s1_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 1:	ui->s2_box->setStyleSheet(style);
                            ui->s2_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s2_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s2_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s2_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s2_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s2_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s2_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s2_lbl_loc->setText( ui->s2_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s2_lbl_name->setText( ui->s2_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 2:	ui->s3_box->setStyleSheet(style);
                            ui->s3_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s3_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s3_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s3_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s3_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s3_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s3_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s3_lbl_loc->setText( ui->s3_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s3_lbl_name->setText( ui->s3_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 3:	ui->s4_box->setStyleSheet(style);
                            ui->s4_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s4_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s4_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s4_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s4_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s4_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s4_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s4_lbl_loc->setText( ui->s4_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s4_lbl_name->setText( ui->s4_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 4:	ui->s5_box->setStyleSheet(style);
                            ui->s5_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s5_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s5_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s5_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s5_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s5_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s5_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s5_lbl_loc->setText( ui->s5_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s5_lbl_name->setText( ui->s5_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 5:	ui->s6_box->setStyleSheet(style);
                            ui->s6_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s6_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s6_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s6_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s6_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s6_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s6_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s6_lbl_loc->setText( ui->s6_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s6_lbl_name->setText( ui->s6_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 6:	ui->s7_box->setStyleSheet(style);
                            ui->s7_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s7_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s7_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s7_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s7_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s7_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s7_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s7_lbl_loc->setText( ui->s7_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s7_lbl_name->setText( ui->s7_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 7:	ui->s8_box->setStyleSheet(style);
                            ui->s8_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s8_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s8_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s8_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s8_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s8_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s8_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s8_lbl_loc->setText( ui->s8_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s8_lbl_name->setText( ui->s8_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 8:	ui->s9_box->setStyleSheet(style);
                            ui->s9_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s9_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s9_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s9_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s9_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s9_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s9_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s9_lbl_loc->setText( ui->s9_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s9_lbl_name->setText( ui->s9_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 9:	ui->s10_box->setStyleSheet(style);
                            ui->s10_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s10_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s10_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s10_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s10_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s10_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s10_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s10_lbl_loc->setText( ui->s10_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s10_lbl_name->setText( ui->s10_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 10:	ui->s11_box->setStyleSheet(style);
                            ui->s11_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s11_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s11_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s11_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s11_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s11_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s11_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s11_lbl_loc->setText( ui->s11_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s11_lbl_name->setText( ui->s11_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 11:	ui->s12_box->setStyleSheet(style);
                            ui->s12_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s12_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s12_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s12_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s12_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s12_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s12_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s12_lbl_loc->setText( ui->s12_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s12_lbl_name->setText( ui->s12_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 12:	ui->s13_box->setStyleSheet(style);
                            ui->s13_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s13_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s13_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s13_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s13_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s13_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s13_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s13_lbl_loc->setText( ui->s13_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s13_lbl_name->setText( ui->s13_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 13:	ui->s14_box->setStyleSheet(style);
                            ui->s14_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s14_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s14_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s14_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s14_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s14_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s14_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s14_lbl_loc->setText( ui->s14_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s14_lbl_name->setText( ui->s14_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
              case 14:	ui->s15_box->setStyleSheet(style);
                            ui->s15_party1->setStyleSheet(avatar_style(ff7.slot[s].desc.party[0]));
                            ui->s15_party2->setStyleSheet(avatar_style(ff7.slot[s].desc.party[1]));
                            ui->s15_party3->setStyleSheet(avatar_style(ff7.slot[s].desc.party[2]));
                            ui->s15_lbl_lvl->setText(QString::number(ff7.slot[s].desc.level));
                            ui->s15_lbl_gil->setText(QString::number(ff7.slot[s].desc.gil));
                            ui->s15_lbl_hr->setText(QString::number(ff7.slot[s].desc.time/3600));
                            ui->s15_lbl_min->setText(QString::number(ff7.slot[s].desc.time/60 %60));
                            for (int loc=0; loc<32;loc++)
                            {
                                if (chPC[ff7.slot[s].desc.location[loc]]=='\0'){break;}
                                else{ui->s15_lbl_loc->setText( ui->s15_lbl_loc->text() + QString(chPC[ff7.slot[s].desc.location[loc]]));}
                            }
                            for (int n=0;n<16;n++)
                            {
                                if (chPC[ff7.slot[s].desc.name[n]]== '\0'){break;}
                                ui->s15_lbl_name->setText( ui->s15_lbl_name->text() + QString(chPC[ff7.slot[s].desc.name[n]]));
                            }
                            break;
            }
        }
        else//NOT FF7 Show Icon and Region String;
        {
            bool invalid =false;
            QByteArray data;
            for(int i=0;i<0x200;i++){data.append(ff7.hf[s].sl_header[i]);}

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

                default:
                    invalid = true;
            }

            if(!invalid)
            {
              switch(s)
              {
                case 0:
                  ui->s1_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s1_party2, SLOT(setPixmap(QPixmap)));
                  ui->s1_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 1:
                  ui->s2_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s2_party2, SLOT(setPixmap(QPixmap)));
                  ui->s2_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 2:
                  ui->s3_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s3_party2, SLOT(setPixmap(QPixmap)));
                  ui->s3_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 3:
                  ui->s4_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s4_party2, SLOT(setPixmap(QPixmap)));
                  ui->s4_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 4:
                  ui->s5_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s5_party2, SLOT(setPixmap(QPixmap)));
                  ui->s5_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 5:
                  ui->s6_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s6_party2, SLOT(setPixmap(QPixmap)));
                  ui->s6_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 6:
                  ui->s7_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s7_party2, SLOT(setPixmap(QPixmap)));
                  ui->s7_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 7:
                  ui->s8_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s8_party2, SLOT(setPixmap(QPixmap)));
                  ui->s8_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 8:
                  ui->s9_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s9_party2, SLOT(setPixmap(QPixmap)));
                  ui->s9_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 9:
                  ui->s10_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s10_party2, SLOT(setPixmap(QPixmap)));
                  ui->s10_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 10:
                  ui->s11_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s11_party2, SLOT(setPixmap(QPixmap)));
                  ui->s11_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 11:
                  ui->s12_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s12_party2, SLOT(setPixmap(QPixmap)));
                  ui->s12_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 12:
                  ui->s13_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s13_party2, SLOT(setPixmap(QPixmap)));
                  ui->s13_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 13:
                  ui->s14_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s14_party2, SLOT(setPixmap(QPixmap)));
                  ui->s14_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
                case 14:
                  ui->s15_party2->setPixmap(icons[s].icon());
                  connect(&icons[s], SIGNAL(nextIcon(QPixmap)), ui->s15_party2, SLOT(setPixmap(QPixmap)));
                  ui->s15_lbl_loc->setText(ff7.SG_Region_String[s].toAscii());
                  break;
              }
            }
        }
    }
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
