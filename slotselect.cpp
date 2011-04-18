/****************************************************************************/
//    copyright 2010 Chris Rizzitello <sithlord48@gmail.com>                //
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
#include "globals.h"
#include "SaveIcon.h"
#include "QMessageBox"
extern FF7 ff7;
extern int s;
SaveIcon icons[15];

SlotSelect::SlotSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SlotSelect)
{
    ui->setupUi(this);
/*~~~~~~~~~~SLOT 1~~~~~~~~~~*/

    if(ff7.SG_Region_String[0] == ""){ui->s1_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[0].contains("00867") ||ff7.SG_Region_String[0].contains("00869") ||
            ff7.SG_Region_String[0].contains("00900") ||ff7.SG_Region_String[0].contains("94163") ||
            ff7.SG_Region_String[0].contains("00700") ||ff7.SG_Region_String[0].contains("01057"))
    {
    //theme the box
    QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
    style.append(QString::number(ff7.slot[0].colors[0][0]));
    style.append(",");
    style.append(QString::number(ff7.slot[0].colors[0][1]));
    style.append(",");
    style.append(QString::number(ff7.slot[0].colors[0][2]));
    style.append(", 255), stop:1 rgba(");
    style.append(QString::number(ff7.slot[0].colors[2][0]));
    style.append(",");
    style.append(QString::number(ff7.slot[0].colors[2][1]));
    style.append(",");
    style.append(QString::number(ff7.slot[0].colors[2][2]));
    style.append(", 255));");

    ui->s1_box->setStyleSheet(style);
    //set info
    ui->s1_lbl_lvl->setText(QString::number(ff7.slot[0].desc.level));
    ui->s1_lbl_gil->setText(QString::number(ff7.slot[0].desc.gil));
    ui->s1_lbl_hr->setText(QString::number(ff7.slot[0].desc.time/3600));
    ui->s1_lbl_min->setText(QString::number(ff7.slot[0].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[0].desc.location[loc]]=='\0'){break;}
        else{ui->s1_lbl_loc->setText( ui->s1_lbl_loc->text() + QString(chPC[ff7.slot[0].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[0].desc.name[n]]== '\0'){break;}
        ui->s1_lbl_name->setText( ui->s1_lbl_name->text() + QString(chPC[ff7.slot[0].desc.name[n]]));
    }
    switch (ff7.slot[0].desc.party[0]){
    case 0:
        ui->s1_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s1_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s1_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s1_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s1_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s1_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s1_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s1_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s1_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s1_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s1_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[0].desc.party[1]){
    case 0:
        ui->s1_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s1_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s1_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s1_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s1_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s1_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s1_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s1_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s1_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s1_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s1_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[0].desc.party[2])    {
    case 0:
        ui->s1_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s1_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s1_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s1_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s1_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s1_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s1_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s1_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s1_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s1_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s1_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
     }
    }

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[0].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[0].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[0].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[0].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s1_party2->setPixmap(icons[0].icon());
            connect(&icons[0], SIGNAL(nextIcon(QPixmap)), ui->s1_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s1_lbl_loc->setText(ff7.SG_Region_String[0].toAscii());
    }

/*~~~~~~~~~~SLOT 2~~~~~~~~~~*/

    if(ff7.SG_Region_String[1] == ""){ui->s2_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[1].contains("00867") ||ff7.SG_Region_String[1].contains("00869") ||
            ff7.SG_Region_String[1].contains("00900") ||ff7.SG_Region_String[1].contains("94163") ||
            ff7.SG_Region_String[1].contains("00700") ||ff7.SG_Region_String[1].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[1].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[1].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[1].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[1].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[1].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[1].colors[2][2]));
        style.append(", 255));");
        ui->s2_box->setStyleSheet(style);
        //set info
        ui->s2_lbl_lvl->setText(QString::number(ff7.slot[1].desc.level));
        ui->s2_lbl_gil->setText(QString::number(ff7.slot[1].desc.gil));
        ui->s2_lbl_hr->setText(QString::number(ff7.slot[1].desc.time/3600));
        ui->s2_lbl_min->setText(QString::number(ff7.slot[1].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[1].desc.location[loc]]=='\0'){break;}
        else{ui->s2_lbl_loc->setText( ui->s2_lbl_loc->text() + QString(chPC[ff7.slot[1].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[1].desc.name[n]]== '\0'){break;}
        ui->s2_lbl_name->setText( ui->s2_lbl_name->text() + QString(chPC[ff7.slot[1].desc.name[n]]));
    }
    switch (ff7.slot[1].desc.party[0]){
    case 0:
        ui->s2_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s2_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s2_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s2_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s2_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s2_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s2_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s2_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s2_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s2_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s2_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[1].desc.party[1]){
    case 0:
        ui->s2_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s2_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s2_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s2_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s2_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s2_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s2_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s2_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s2_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s2_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s2_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[1].desc.party[2]){
    case 0:
        ui->s2_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s2_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s2_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s2_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s2_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s2_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s2_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s2_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s2_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s2_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s2_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    }

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[1].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[1].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[1].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[1].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s2_party2->setPixmap(icons[1].icon());
            connect(&icons[1], SIGNAL(nextIcon(QPixmap)), ui->s2_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s2_lbl_loc->setText(ff7.SG_Region_String[1].toAscii());
    }

/*~~~~~~~~~~SLOT 3~~~~~~~~~~*/

    if(ff7.SG_Region_String[2] == ""){ui->s3_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[2].contains("00867") ||ff7.SG_Region_String[2].contains("00869") ||
            ff7.SG_Region_String[2].contains("00900") ||ff7.SG_Region_String[2].contains("94163") ||
            ff7.SG_Region_String[2].contains("00700") ||ff7.SG_Region_String[2].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[2].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[2].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[2].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[2].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[2].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[2].colors[2][2]));
        style.append(", 255));");
        ui->s3_box->setStyleSheet(style);
        //set info
        ui->s3_lbl_lvl->setText(QString::number(ff7.slot[2].desc.level));
        ui->s3_lbl_gil->setText(QString::number(ff7.slot[2].desc.gil));
        ui->s3_lbl_hr->setText(QString::number(ff7.slot[2].desc.time/3600));
        ui->s3_lbl_min->setText(QString::number(ff7.slot[2].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[2].desc.location[loc]]=='\0'){break;}
        else{ui->s3_lbl_loc->setText( ui->s3_lbl_loc->text() + QString(chPC[ff7.slot[2].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[2].desc.name[n]]== '\0'){break;}
        ui->s3_lbl_name->setText( ui->s3_lbl_name->text() + QString(chPC[ff7.slot[2].desc.name[n]]));
    }
    switch (ff7.slot[2].desc.party[0]){
    case 0:
        ui->s3_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s3_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s3_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s3_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s3_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s3_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s3_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s3_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s3_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s3_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s3_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[2].desc.party[1]){
    case 0:
        ui->s3_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s3_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s3_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s3_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s3_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s3_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s3_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s3_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s3_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s3_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s3_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[2].desc.party[2]){
    case 0:
        ui->s3_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s3_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s3_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s3_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s3_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s3_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s3_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s3_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s3_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s3_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s3_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[2].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[2].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[2].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[2].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s3_party2->setPixmap(icons[2].icon());
            connect(&icons[2], SIGNAL(nextIcon(QPixmap)), ui->s3_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s3_lbl_loc->setText(ff7.SG_Region_String[2].toAscii());
    }

/*~~~~~~~~~~SLOT 4~~~~~~~~~~*/

    if(ff7.SG_Region_String[3] == ""){ui->s4_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[3].contains("00867") ||ff7.SG_Region_String[3].contains("00869") ||
            ff7.SG_Region_String[3].contains("00900") ||ff7.SG_Region_String[3].contains("94163") ||
            ff7.SG_Region_String[3].contains("00700") ||ff7.SG_Region_String[3].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[3].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[3].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[3].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[3].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[3].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[3].colors[2][2]));
        style.append(", 255));");
        ui->s4_box->setStyleSheet(style);
        //set info
        ui->s4_lbl_lvl->setText(QString::number(ff7.slot[3].desc.level));
        ui->s4_lbl_gil->setText(QString::number(ff7.slot[3].desc.gil));
        ui->s4_lbl_hr->setText(QString::number(ff7.slot[3].desc.time/3600));
        ui->s4_lbl_min->setText(QString::number(ff7.slot[3].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[3].desc.location[loc]]=='\0'){break;}
        else{ui->s4_lbl_loc->setText( ui->s4_lbl_loc->text() + QString(chPC[ff7.slot[3].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[3].desc.name[n]]== '\0'){break;}
        ui->s4_lbl_name->setText( ui->s4_lbl_name->text() + QString(chPC[ff7.slot[3].desc.name[n]]));
    }
    switch (ff7.slot[3].desc.party[0]){
    case 0:
        ui->s4_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s4_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s4_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s4_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s4_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s4_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s4_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s4_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s4_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s4_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s4_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[3].desc.party[1]){
    case 0:
        ui->s4_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s4_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s4_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s4_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s4_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s4_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s4_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s4_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s4_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s4_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s4_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[3].desc.party[2]){
    case 0:
        ui->s4_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s4_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s4_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s4_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s4_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s4_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s4_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s4_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s4_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s4_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s4_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[3].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[3].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[3].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[3].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s4_party2->setPixmap(icons[3].icon());
            connect(&icons[3], SIGNAL(nextIcon(QPixmap)), ui->s4_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s4_lbl_loc->setText(ff7.SG_Region_String[3].toAscii());
    }

/*~~~~~~~~~~SLOT 5~~~~~~~~~~*/

    if(ff7.SG_Region_String[4] == ""){ui->s5_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[4].contains("00867") ||ff7.SG_Region_String[4].contains("00869") ||
            ff7.SG_Region_String[4].contains("00900") ||ff7.SG_Region_String[4].contains("94163") ||
            ff7.SG_Region_String[4].contains("00700") ||ff7.SG_Region_String[4].contains("01057"))
    {   //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[4].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[4].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[4].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[4].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[4].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[4].colors[2][2]));
        style.append(", 255));");
        ui->s5_box->setStyleSheet(style);
        //set info
        ui->s5_lbl_lvl->setText(QString::number(ff7.slot[4].desc.level));
        ui->s5_lbl_gil->setText(QString::number(ff7.slot[4].desc.gil));
        ui->s5_lbl_hr->setText(QString::number(ff7.slot[4].desc.time/3600));
        ui->s5_lbl_min->setText(QString::number(ff7.slot[4].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[4].desc.location[loc]]=='\0'){break;}
        else{ui->s5_lbl_loc->setText( ui->s5_lbl_loc->text() + QString(chPC[ff7.slot[4].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[4].desc.name[n]]== '\0'){break;}
        ui->s5_lbl_name->setText( ui->s5_lbl_name->text() + QString(chPC[ff7.slot[4].desc.name[n]]));
    }
    switch (ff7.slot[4].desc.party[0]){
    case 0:
        ui->s5_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s5_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s5_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s5_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s5_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s5_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s5_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s5_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s5_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s5_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s5_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[4].desc.party[1]){
    case 0:
        ui->s5_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s5_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s5_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s5_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s5_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s5_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s5_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s5_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s5_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s5_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s5_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[4].desc.party[2]){
    case 0:
        ui->s5_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s5_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s5_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s5_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s5_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s5_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s5_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s5_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s5_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s5_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s5_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[4].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[4].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[4].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[4].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s5_party2->setPixmap(icons[4].icon());
            connect(&icons[4], SIGNAL(nextIcon(QPixmap)), ui->s5_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s5_lbl_loc->setText(ff7.SG_Region_String[4].toAscii());
    }

/*~~~~~~~~~~SLOT 6~~~~~~~~~~*/

    if(ff7.SG_Region_String[5] == ""){ui->s6_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[5].contains("00867") ||ff7.SG_Region_String[5].contains("00869") ||
            ff7.SG_Region_String[5].contains("00900") ||ff7.SG_Region_String[5].contains("94163") ||
            ff7.SG_Region_String[5].contains("00700") ||ff7.SG_Region_String[5].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[5].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[5].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[5].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[5].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[5].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[5].colors[2][2]));
        style.append(", 255));");
        ui->s6_box->setStyleSheet(style);
        //set info
        ui->s6_lbl_lvl->setText(QString::number(ff7.slot[5].desc.level));
        ui->s6_lbl_gil->setText(QString::number(ff7.slot[5].desc.gil));
        ui->s6_lbl_hr->setText(QString::number(ff7.slot[5].desc.time/3600));
        ui->s6_lbl_min->setText(QString::number(ff7.slot[5].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[5].desc.location[loc]]=='\0'){break;}
        else{ui->s6_lbl_loc->setText( ui->s6_lbl_loc->text() + QString(chPC[ff7.slot[5].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[5].desc.name[n]]== '\0'){break;}
        ui->s6_lbl_name->setText( ui->s6_lbl_name->text() + QString(chPC[ff7.slot[5].desc.name[n]]));
    }
    switch (ff7.slot[5].desc.party[0]){
    case 0:
        ui->s6_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s6_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s6_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s6_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s6_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s6_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s6_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s6_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s6_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s6_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s6_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[5].desc.party[1]){
    case 0:
        ui->s6_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s6_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s6_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s6_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s6_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s6_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s6_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s6_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s6_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s6_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s6_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[5].desc.party[2]){
    case 0:
        ui->s6_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s6_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s6_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s6_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s6_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s6_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s6_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s6_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s6_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s6_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s6_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[5].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[5].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[5].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[5].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s6_party2->setPixmap(icons[5].icon());
            connect(&icons[5], SIGNAL(nextIcon(QPixmap)), ui->s6_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s6_lbl_loc->setText(ff7.SG_Region_String[5].toAscii());
    }
    /*~~~~~~~~~~SLOT 7~~~~~~~~~~*/

    if(ff7.SG_Region_String[6] == ""){ui->s7_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[6].contains("00867") ||ff7.SG_Region_String[6].contains("00869") ||
            ff7.SG_Region_String[6].contains("00900") ||ff7.SG_Region_String[6].contains("94163") ||
            ff7.SG_Region_String[6].contains("00700") ||ff7.SG_Region_String[6].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[6].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[6].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[6].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[6].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[6].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[6].colors[2][2]));
        style.append(", 255));");
        ui->s7_box->setStyleSheet(style);
        //set info
        ui->s7_lbl_lvl->setText(QString::number(ff7.slot[6].desc.level));
        ui->s7_lbl_gil->setText(QString::number(ff7.slot[6].desc.gil));
        ui->s7_lbl_hr->setText(QString::number(ff7.slot[6].desc.time/3600));
        ui->s7_lbl_min->setText(QString::number(ff7.slot[6].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[6].desc.location[loc]]=='\0'){break;}
        else{ui->s7_lbl_loc->setText( ui->s7_lbl_loc->text() + QString(chPC[ff7.slot[6].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[6].desc.name[n]]== '\0'){break;}
        ui->s7_lbl_name->setText( ui->s7_lbl_name->text() + QString(chPC[ff7.slot[6].desc.name[n]]));
    }
    switch (ff7.slot[6].desc.party[0]){
    case 0:
        ui->s7_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s7_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s7_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s7_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s7_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s7_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s7_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s7_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s7_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s7_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s7_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[6].desc.party[1]){
    case 0:
        ui->s7_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s7_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s7_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s7_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s7_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s7_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s7_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s7_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s7_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s7_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s7_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[6].desc.party[2]){
    case 0:
        ui->s7_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s7_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s7_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s7_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s7_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s7_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s7_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s7_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s7_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s7_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s7_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[6].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[6].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[6].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[6].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s7_party2->setPixmap(icons[6].icon());
            connect(&icons[6], SIGNAL(nextIcon(QPixmap)), ui->s7_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s7_lbl_loc->setText(ff7.SG_Region_String[6].toAscii());
    }

/*~~~~~~~~~~SLOT 8~~~~~~~~~~*/

    if(ff7.SG_Region_String[7] == ""){ui->s8_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[7].contains("00867") ||ff7.SG_Region_String[7].contains("00869") ||
            ff7.SG_Region_String[7].contains("00900") ||ff7.SG_Region_String[7].contains("94163") ||
            ff7.SG_Region_String[7].contains("00700") ||ff7.SG_Region_String[7].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[7].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[7].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[7].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[7].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[7].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[7].colors[2][2]));
        style.append(", 255));");
        ui->s8_box->setStyleSheet(style);
        //set info
        ui->s8_lbl_lvl->setText(QString::number(ff7.slot[7].desc.level));
        ui->s8_lbl_gil->setText(QString::number(ff7.slot[7].desc.gil));
        ui->s8_lbl_hr->setText(QString::number(ff7.slot[7].desc.time/3600));
        ui->s8_lbl_min->setText(QString::number(ff7.slot[7].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[7].desc.location[loc]]=='\0'){break;}
        else{ui->s8_lbl_loc->setText( ui->s8_lbl_loc->text() + QString(chPC[ff7.slot[7].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[7].desc.name[n]]== '\0'){break;}
        ui->s8_lbl_name->setText( ui->s8_lbl_name->text() + QString(chPC[ff7.slot[7].desc.name[n]]));
    }
    switch (ff7.slot[7].desc.party[0]){
    case 0:
        ui->s8_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s8_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s8_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s8_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s8_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s8_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s8_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s8_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s8_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s8_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s8_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[7].desc.party[1]){
    case 0:
        ui->s8_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s8_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s8_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s8_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s8_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s8_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s8_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s8_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s8_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s8_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s8_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[7].desc.party[2]){
    case 0:
         ui->s8_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
         break;
     case 1:
         ui->s8_party3->setPixmap(QPixmap(":/icon/barret_icon"));
         break;
     case 2:
         ui->s8_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
         break;
     case 3:
         ui->s8_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
         break;
     case 4:
         ui->s8_party3->setPixmap(QPixmap(":/icon/red_icon"));
         break;
     case 5:
         ui->s8_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
         break;
     case 6:
         ui->s8_party3->setPixmap(QPixmap(":/icon/cait_icon"));
         break;
     case 7:
         ui->s8_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
         break;
     case 8:
         ui->s8_party3->setPixmap(QPixmap(":/icon/cid_icon"));
         break;
     case 9:
         ui->s8_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
         break;
     case 10:
         ui->s8_party3->setPixmap(QPixmap(":/icon/sep_icon"));
         break;
     }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[7].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[7].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[7].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[7].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s8_party2->setPixmap(icons[7].icon());
            connect(&icons[7], SIGNAL(nextIcon(QPixmap)), ui->s8_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s8_lbl_loc->setText(ff7.SG_Region_String[7].toAscii());
    }

/*~~~~~~~~~~SLOT 9~~~~~~~~~~*/

    if(ff7.SG_Region_String[8] == ""){ui->s9_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[8].contains("00867") ||ff7.SG_Region_String[8].contains("00869") ||
            ff7.SG_Region_String[8].contains("00900") ||ff7.SG_Region_String[8].contains("94163") ||
            ff7.SG_Region_String[8].contains("00700") ||ff7.SG_Region_String[8].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[8].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[8].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[8].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[8].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[8].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[8].colors[2][2]));
        style.append(", 255));");
        ui->s9_box->setStyleSheet(style);
        //set info
        ui->s9_lbl_lvl->setText(QString::number(ff7.slot[8].desc.level));
        ui->s9_lbl_gil->setText(QString::number(ff7.slot[8].desc.gil));
        ui->s9_lbl_hr->setText(QString::number(ff7.slot[8].desc.time/3600));
        ui->s9_lbl_min->setText(QString::number(ff7.slot[8].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[8].desc.location[loc]]=='\0'){break;}
        else{ui->s9_lbl_loc->setText( ui->s9_lbl_loc->text() + QString(chPC[ff7.slot[8].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[8].desc.name[n]]== '\0'){break;}
        ui->s9_lbl_name->setText( ui->s9_lbl_name->text() + QString(chPC[ff7.slot[8].desc.name[n]]));
    }
    switch (ff7.slot[8].desc.party[0]){
    case 0:
        ui->s9_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s9_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s9_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s9_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s9_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s9_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s9_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s9_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s9_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s9_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s9_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[8].desc.party[1]){
    case 0:
        ui->s9_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s9_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s9_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s9_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s9_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s9_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s9_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s9_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s9_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s9_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s9_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[8].desc.party[2]){
    case 0:
        ui->s9_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s9_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s9_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s9_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s9_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s9_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s9_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s9_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s9_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s9_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s9_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[8].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[8].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[8].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[8].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s9_party2->setPixmap(icons[8].icon());
            connect(&icons[8], SIGNAL(nextIcon(QPixmap)), ui->s9_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s9_lbl_loc->setText(ff7.SG_Region_String[8].toAscii());
    }

/*~~~~~~~~~~SLOT 10~~~~~~~~~~*/

    if(ff7.SG_Region_String[9] == ""){ui->s10_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[9].contains("00867") ||ff7.SG_Region_String[9].contains("00869") ||
            ff7.SG_Region_String[9].contains("00900") ||ff7.SG_Region_String[9].contains("94163") ||
            ff7.SG_Region_String[9].contains("00700") ||ff7.SG_Region_String[9].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[9].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[9].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[9].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[9].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[9].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[9].colors[2][2]));
        style.append(", 255));");
        ui->s10_box->setStyleSheet(style);
        //set info
        ui->s10_lbl_lvl->setText(QString::number(ff7.slot[9].desc.level));
        ui->s10_lbl_gil->setText(QString::number(ff7.slot[9].desc.gil));
        ui->s10_lbl_hr->setText(QString::number(ff7.slot[9].desc.time/3600));
        ui->s10_lbl_min->setText(QString::number(ff7.slot[9].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[9].desc.location[loc]]=='\0'){break;}
        else{ui->s10_lbl_loc->setText( ui->s10_lbl_loc->text() + QString(chPC[ff7.slot[9].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[9].desc.name[n]]== '\0'){break;}
        ui->s10_lbl_name->setText( ui->s10_lbl_name->text() + QString(chPC[ff7.slot[9].desc.name[n]]));
    }
    switch (ff7.slot[9].desc.party[0]){
    case 0:
        ui->s10_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s10_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s10_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s10_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s10_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s10_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s10_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s10_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s10_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s10_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s10_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[9].desc.party[1]){
    case 0:
        ui->s10_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s10_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s10_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s10_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s10_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s10_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s10_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s10_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s10_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s10_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s10_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[9].desc.party[2]){
    case 0:
        ui->s10_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s10_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s10_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s10_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s10_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s10_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s10_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s10_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s10_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s10_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s10_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[9].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[9].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[9].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[9].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s10_party2->setPixmap(icons[9].icon());
            connect(&icons[9], SIGNAL(nextIcon(QPixmap)), ui->s10_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s10_lbl_loc->setText(ff7.SG_Region_String[9].toAscii());
    }

/*~~~~~~~~~~SLOT 11~~~~~~~~~~*/

    if(ff7.SG_Region_String[10] == ""){ui->s11_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[10].contains("00867") ||ff7.SG_Region_String[10].contains("00869") ||
            ff7.SG_Region_String[10].contains("00900") ||ff7.SG_Region_String[10].contains("94163") ||
            ff7.SG_Region_String[10].contains("00700") ||ff7.SG_Region_String[10].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[10].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[10].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[10].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[10].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[10].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[10].colors[2][2]));
        style.append(", 255));");
        ui->s11_box->setStyleSheet(style);
        //set info
        ui->s11_lbl_lvl->setText(QString::number(ff7.slot[10].desc.level));
        ui->s11_lbl_gil->setText(QString::number(ff7.slot[10].desc.gil));
        ui->s11_lbl_hr->setText(QString::number(ff7.slot[10].desc.time/3600));
        ui->s11_lbl_min->setText(QString::number(ff7.slot[10].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[10].desc.location[loc]]=='\0'){break;}
        else{ui->s11_lbl_loc->setText( ui->s11_lbl_loc->text() + QString(chPC[ff7.slot[10].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[10].desc.name[n]]== '\0'){break;}
        ui->s11_lbl_name->setText( ui->s11_lbl_name->text() + QString(chPC[ff7.slot[10].desc.name[n]]));
    }
    switch (ff7.slot[10].desc.party[0]){
    case 0:
        ui->s11_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s11_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s11_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s11_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s11_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s11_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s11_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s11_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s11_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s11_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s11_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[10].desc.party[1]){
    case 0:
        ui->s11_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s11_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s11_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s11_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s11_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s11_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s11_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s11_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s11_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s11_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s11_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[10].desc.party[2]){
    case 0:
        ui->s11_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s11_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s11_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s11_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s11_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s11_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s11_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s11_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s11_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s11_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s11_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[10].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[10].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[10].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[10].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s11_party2->setPixmap(icons[10].icon());
            connect(&icons[10], SIGNAL(nextIcon(QPixmap)), ui->s11_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s11_lbl_loc->setText(ff7.SG_Region_String[10].toAscii());
    }

/*~~~~~~~~~~SLOT 12~~~~~~~~~~*/

    if(ff7.SG_Region_String[11] == ""){ui->s12_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[11].contains("00867") ||ff7.SG_Region_String[11].contains("00869") ||
            ff7.SG_Region_String[11].contains("00900") ||ff7.SG_Region_String[11].contains("94163") ||
            ff7.SG_Region_String[11].contains("00700") ||ff7.SG_Region_String[11].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[11].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[11].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[11].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[11].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[11].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[11].colors[2][2]));
        style.append(", 255));");
        ui->s12_box->setStyleSheet(style);
        //set info
        ui->s12_lbl_lvl->setText(QString::number(ff7.slot[11].desc.level));
        ui->s12_lbl_gil->setText(QString::number(ff7.slot[11].desc.gil));
        ui->s12_lbl_hr->setText(QString::number(ff7.slot[11].desc.time/3600));
        ui->s12_lbl_min->setText(QString::number(ff7.slot[11].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[11].desc.location[loc]]=='\0'){break;}
        else{ui->s12_lbl_loc->setText( ui->s12_lbl_loc->text() + QString(chPC[ff7.slot[11].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[11].desc.name[n]]== '\0'){break;}
        ui->s12_lbl_name->setText( ui->s12_lbl_name->text() + QString(chPC[ff7.slot[11].desc.name[n]]));
    }
    switch (ff7.slot[11].desc.party[0]){
    case 0:
        ui->s12_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s12_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s12_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s12_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s12_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s12_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s12_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s12_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s12_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s12_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s12_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[11].desc.party[1]){
    case 0:
        ui->s12_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s12_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s12_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s12_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s12_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s12_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s12_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s12_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s12_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s12_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s12_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[11].desc.party[2]){
    case 0:
        ui->s12_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s12_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s12_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s12_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s12_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s12_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s12_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s12_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s12_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s12_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s12_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[11].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[11].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[11].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[11].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s12_party2->setPixmap(icons[11].icon());
            connect(&icons[11], SIGNAL(nextIcon(QPixmap)), ui->s12_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s12_lbl_loc->setText(ff7.SG_Region_String[11].toAscii());
    }

/*~~~~~~~~~~SLOT 13~~~~~~~~~~*/

    if(ff7.SG_Region_String[12] == ""){ui->s13_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[12].contains("00867") ||ff7.SG_Region_String[12].contains("00869") ||
            ff7.SG_Region_String[12].contains("00900") ||ff7.SG_Region_String[12].contains("94163") ||
            ff7.SG_Region_String[12].contains("00700") ||ff7.SG_Region_String[12].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[12].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[12].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[12].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[12].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[12].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[12].colors[2][2]));
        style.append(", 255));");
        ui->s13_box->setStyleSheet(style);
        //set info
        ui->s13_lbl_lvl->setText(QString::number(ff7.slot[12].desc.level));
        ui->s13_lbl_gil->setText(QString::number(ff7.slot[12].desc.gil));
        ui->s13_lbl_hr->setText(QString::number(ff7.slot[12].desc.time/3600));
        ui->s13_lbl_min->setText(QString::number(ff7.slot[12].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[12].desc.location[loc]]=='\0'){break;}
        else{ui->s13_lbl_loc->setText( ui->s13_lbl_loc->text() + QString(chPC[ff7.slot[12].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[12].desc.name[n]]== '\0'){break;}
        ui->s13_lbl_name->setText( ui->s13_lbl_name->text() + QString(chPC[ff7.slot[12].desc.name[n]]));
    }
    switch (ff7.slot[12].desc.party[0]){
    case 0:
        ui->s13_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s13_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s13_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s13_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s13_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s13_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s13_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s13_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s13_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s13_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s13_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[12].desc.party[1]){
    case 0:
        ui->s13_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s13_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s13_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s13_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s13_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s13_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s13_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s13_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s13_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s13_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s13_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[12].desc.party[2]){
    case 0:
         ui->s13_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
         break;
     case 1:
         ui->s13_party3->setPixmap(QPixmap(":/icon/barret_icon"));
         break;
     case 2:
         ui->s13_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
         break;
     case 3:
         ui->s13_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
         break;
     case 4:
         ui->s13_party3->setPixmap(QPixmap(":/icon/red_icon"));
         break;
     case 5:
         ui->s13_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
         break;
     case 6:
         ui->s13_party3->setPixmap(QPixmap(":/icon/cait_icon"));
         break;
     case 7:
         ui->s13_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
         break;
     case 8:
         ui->s13_party3->setPixmap(QPixmap(":/icon/cid_icon"));
         break;
     case 9:
         ui->s13_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
         break;
     case 10:
         ui->s13_party3->setPixmap(QPixmap(":/icon/sep_icon"));
         break;
     }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[12].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[12].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[12].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[12].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s13_party2->setPixmap(icons[12].icon());
            connect(&icons[12], SIGNAL(nextIcon(QPixmap)), ui->s13_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s13_lbl_loc->setText(ff7.SG_Region_String[12].toAscii());
    }

/*~~~~~~~~~~SLOT 14~~~~~~~~~~*/

    if(ff7.SG_Region_String[13] == ""){ui->s14_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[13].contains("00867") ||ff7.SG_Region_String[13].contains("00869") ||
            ff7.SG_Region_String[13].contains("00900") ||ff7.SG_Region_String[13].contains("94163") ||
            ff7.SG_Region_String[13].contains("00700") ||ff7.SG_Region_String[13].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[13].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[13].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[13].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[13].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[13].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[13].colors[2][2]));
        style.append(", 255));");
        ui->s14_box->setStyleSheet(style);
        //set info
        ui->s14_lbl_lvl->setText(QString::number(ff7.slot[13].desc.level));
        ui->s14_lbl_gil->setText(QString::number(ff7.slot[13].desc.gil));
        ui->s14_lbl_hr->setText(QString::number(ff7.slot[13].desc.time/3600));
        ui->s14_lbl_min->setText(QString::number(ff7.slot[13].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[13].desc.location[loc]]=='\0'){break;}
        else{ui->s14_lbl_loc->setText( ui->s14_lbl_loc->text() + QString(chPC[ff7.slot[13].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[13].desc.name[n]]== '\0'){break;}
        ui->s14_lbl_name->setText( ui->s14_lbl_name->text() + QString(chPC[ff7.slot[13].desc.name[n]]));
    }
    switch (ff7.slot[13].desc.party[0]){
    case 0:
        ui->s14_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s14_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s14_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s14_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s14_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s14_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s14_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s14_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s14_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s14_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s14_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[13].desc.party[1]){
    case 0:
        ui->s14_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s14_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s14_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s14_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s14_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s14_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s14_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s14_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s14_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s14_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s14_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[13].desc.party[2]){
    case 0:
        ui->s14_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s14_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s14_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s14_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s14_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s14_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s14_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s14_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s14_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s14_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s14_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;
        for(int i=0;i<0x200;i++){data.append(ff7.hf[13].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[13].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[13].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[13].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s14_party2->setPixmap(icons[13].icon());
            connect(&icons[13], SIGNAL(nextIcon(QPixmap)), ui->s14_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s14_lbl_loc->setText(ff7.SG_Region_String[13].toAscii());
    }

/*~~~~~~~~~~SLOT 15~~~~~~~~~~*/

    if(ff7.SG_Region_String[14] == ""){ui->s15_lbl_loc->setText("Empty Slot");}

    else if(ff7.SG_Region_String[14].contains("00867") ||ff7.SG_Region_String[14].contains("00869") ||
            ff7.SG_Region_String[14].contains("00900") ||ff7.SG_Region_String[14].contains("94163") ||
            ff7.SG_Region_String[14].contains("00700") ||ff7.SG_Region_String[14].contains("01057"))
    {
        //theme the box
        QString style = "background-color: qlineargradient(spread:pad, x1:0.489, y1:0.459955, x2:0.482, y2:0, stop:0 rgba(";
        style.append(QString::number(ff7.slot[14].colors[0][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[14].colors[0][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[14].colors[0][2]));
        style.append(", 255), stop:1 rgba(");
        style.append(QString::number(ff7.slot[14].colors[2][0]));
        style.append(",");
        style.append(QString::number(ff7.slot[14].colors[2][1]));
        style.append(",");
        style.append(QString::number(ff7.slot[14].colors[2][2]));
        style.append(", 255));");
        ui->s15_box->setStyleSheet(style);
        //set info
        ui->s15_lbl_lvl->setText(QString::number(ff7.slot[14].desc.level));
        ui->s15_lbl_gil->setText(QString::number(ff7.slot[14].desc.gil));
        ui->s15_lbl_hr->setText(QString::number(ff7.slot[14].desc.time/3600));
        ui->s15_lbl_min->setText(QString::number(ff7.slot[14].desc.time/60 %60));
    for (int loc=0; loc<32;loc++)
    {
        if (chPC[ff7.slot[14].desc.location[loc]]=='\0'){break;}
        else{ui->s15_lbl_loc->setText( ui->s15_lbl_loc->text() + QString(chPC[ff7.slot[14].desc.location[loc]]));}
    }
    for (int n=0;n<16;n++)
    {
        if (chPC[ff7.slot[14].desc.name[n]]== '\0'){break;}
        ui->s15_lbl_name->setText( ui->s15_lbl_name->text() + QString(chPC[ff7.slot[14].desc.name[n]]));
    }
    switch (ff7.slot[14].desc.party[0]){
    case 0:
        ui->s15_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s15_party1->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s15_party1->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s15_party1->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s15_party1->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s15_party1->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s15_party1->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s15_party1->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s15_party1->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s15_party1->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s15_party1->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[14].desc.party[1]){
    case 0:
        ui->s15_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s15_party2->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s15_party2->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s15_party2->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s15_party2->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s15_party2->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s15_party2->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s15_party2->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s15_party2->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s15_party2->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s15_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[14].desc.party[2]){
    case 0:
        ui->s15_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 1:
        ui->s15_party3->setPixmap(QPixmap(":/icon/barret_icon"));
        break;
    case 2:
        ui->s15_party3->setPixmap(QPixmap(":/icon/tifa_icon"));
        break;
    case 3:
        ui->s15_party3->setPixmap(QPixmap(":/icon/aeris_icon"));
        break;
    case 4:
        ui->s15_party3->setPixmap(QPixmap(":/icon/red_icon"));
        break;
    case 5:
        ui->s15_party3->setPixmap(QPixmap(":/icon/yuffie_icon"));
        break;
    case 6:
        ui->s15_party3->setPixmap(QPixmap(":/icon/cait_icon"));
        break;
    case 7:
        ui->s15_party3->setPixmap(QPixmap(":/icon/vincent_icon"));
        break;
    case 8:
        ui->s15_party3->setPixmap(QPixmap(":/icon/cid_icon"));
        break;
    case 9:
        ui->s15_party3->setPixmap(QPixmap(":/icon/y_cloud_icon"));
        break;
    case 10:
        ui->s15_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
}

    else//NOT FF7 Show Icon and Region String;
    {
        bool invalid =false;
        QByteArray data;

        for(int i=0;i<0x200;i++){data.append(ff7.hf[14].sl_header[i]);}

        switch((quint8)data.at(2))
        {
            case 0x11://1 frame
                icons[14].setAll(data.mid(96,160));
                break;

            case 0x12://2 frames
                icons[14].setAll(data.mid(96,288), 2);
                break;

            case 0x13://3 frames
                icons[14].setAll(data.mid(96,416), 3);
                break;

            default:
                invalid = true;
        }

        if(!invalid)
        {
            ui->s15_party2->setPixmap(icons[14].icon());
            connect(&icons[14], SIGNAL(nextIcon(QPixmap)), ui->s15_party2, SLOT(setPixmap(QPixmap)));
        }
        ui->s15_lbl_loc->setText(ff7.SG_Region_String[14].toAscii());
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
/*
void SlotSelect::on_btn_prev_clicked()
{
    if (ui->stackedWidget->currentIndex()== 0) {return;}
    else{ui->stackedWidget->setCurrentIndex((ui->stackedWidget->currentIndex()-1));}
}

void SlotSelect::on_btn_next_clicked()
{
    if (ui->stackedWidget->currentIndex()== 4) {return;}
    else{ui->stackedWidget->setCurrentIndex((ui->stackedWidget->currentIndex()+1));}
}
*/
void SlotSelect::on_btn_s1_clicked()
{
    s=0;SlotSelect::close();
}

void SlotSelect::on_btn_s2_clicked()
{
    s=1;SlotSelect::close();
}

void SlotSelect::on_btn_s3_clicked()
{
    s=2;SlotSelect::close();
}

void SlotSelect::on_btn_s4_clicked()
{
    s=3;SlotSelect::close();
}

void SlotSelect::on_btn_s5_clicked()
{
    s=4;SlotSelect::close();
}

void SlotSelect::on_btn_s6_clicked()
{
    s=5;SlotSelect::close();
}

void SlotSelect::on_btn_s7_clicked()
{
    s=6;SlotSelect::close();
}

void SlotSelect::on_btn_s8_clicked()
{
    s=7;SlotSelect::close();
}

void SlotSelect::on_btn_s9_clicked()
{
    s=8;SlotSelect::close();
}

void SlotSelect::on_btn_s10_clicked()
{
    s=9;SlotSelect::close();
}

void SlotSelect::on_btn_s11_clicked()
{
    s=10;SlotSelect::close();
}

void SlotSelect::on_btn_s12_clicked()
{
    s=11;SlotSelect::close();
}

void SlotSelect::on_btn_s13_clicked()
{
    s=12;SlotSelect::close();
}

void SlotSelect::on_btn_s14_clicked()
{
    s=13;SlotSelect::close();
}

void SlotSelect::on_btn_s15_clicked()
{
    s=14;SlotSelect::close();
}
