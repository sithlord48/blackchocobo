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
extern FF7 ff7;
extern int s;
SlotSelect::SlotSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SlotSelect)
{
    ui->setupUi(this);
    //fill up slot preview data, manually can't loop .......

    //slot 1
    ui->s1_lcd_lvl->display(ff7.slot[0].desc.level);
    ui->s1_lcd_gil->display(double(ff7.slot[0].desc.gil));

    ui->s1_lcd_hr->display(int(ff7.slot[0].desc.time/3600));
    ui->s1_lcd_min->display(int(ff7.slot[0].desc.time/60 %60));
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
        ui->s1_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
        ui->s1_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 10:
        ui->s1_party2->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }
    switch (ff7.slot[0].desc.party[2]){
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
        ui->s1_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 10:
        ui->s1_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }

    //slot 2
    ui->s2_lcd_lvl->display(ff7.slot[1].desc.level);
    ui->s2_lcd_gil->display(double(ff7.slot[1].desc.gil));

    ui->s2_lcd_hr->display(int(ff7.slot[1].desc.time/3600));
    ui->s2_lcd_min->display(int(ff7.slot[1].desc.time/60 %60));
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
               ui->s2_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
               ui->s2_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
               ui->s2_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
               break;
           case 10:
               ui->s2_party3->setPixmap(QPixmap(":/icon/sep_icon"));
               break;
           }

    //slot 3
    ui->s3_lcd_lvl->display(ff7.slot[2].desc.level);
    ui->s3_lcd_gil->display(double(ff7.slot[2].desc.gil));

    ui->s3_lcd_hr->display(int(ff7.slot[2].desc.time/3600));
    ui->s3_lcd_min->display(int(ff7.slot[2].desc.time/60 %60));
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
                       ui->s3_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                       ui->s3_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                       ui->s3_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
                       break;
                   case 10:
                       ui->s3_party3->setPixmap(QPixmap(":/icon/sep_icon"));
                       break;
                   }

    //slot 4
    ui->s4_lcd_lvl->display(ff7.slot[3].desc.level);
    ui->s4_lcd_gil->display(double(ff7.slot[3].desc.gil));

    ui->s4_lcd_hr->display(int(ff7.slot[3].desc.time/3600));
    ui->s4_lcd_min->display(int(ff7.slot[3].desc.time/60 %60));
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
                               ui->s4_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                               ui->s4_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                               ui->s4_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
                               break;
                           case 10:
                               ui->s4_party3->setPixmap(QPixmap(":/icon/sep_icon"));
                               break;
                           }

    //slot 5
    ui->s5_lcd_lvl->display(ff7.slot[4].desc.level);
    ui->s5_lcd_gil->display(double(ff7.slot[4].desc.gil));

    ui->s5_lcd_hr->display(int(ff7.slot[4].desc.time/3600));
    ui->s5_lcd_min->display(int(ff7.slot[4].desc.time/60 %60));
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
                                       ui->s5_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                                       ui->s5_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                                       ui->s5_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
                                       break;
                                   case 10:
                                       ui->s5_party3->setPixmap(QPixmap(":/icon/sep_icon"));
                                       break;
                                   }
    //slot 6
    ui->s6_lcd_lvl->display(ff7.slot[5].desc.level);
    ui->s6_lcd_gil->display(double(ff7.slot[5].desc.gil));

    ui->s6_lcd_hr->display(int(ff7.slot[5].desc.time/3600));
    ui->s6_lcd_min->display(int(ff7.slot[5].desc.time/60 %60));
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
        ui->s6_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
        ui->s6_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
        ui->s6_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
        break;
    case 10:
        ui->s6_party3->setPixmap(QPixmap(":/icon/sep_icon"));
        break;
    }

    //slot 7
    ui->s7_lcd_lvl->display(ff7.slot[6].desc.level);
    ui->s7_lcd_gil->display(double(ff7.slot[6].desc.gil));

    ui->s7_lcd_hr->display(int(ff7.slot[6].desc.time/3600));
    ui->s7_lcd_min->display(int(ff7.slot[6].desc.time/60 %60));
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
               ui->s7_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
               ui->s7_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
               ui->s7_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
               break;
           case 10:
               ui->s7_party3->setPixmap(QPixmap(":/icon/sep_icon"));
               break;
           }

    //slot 8
    ui->s8_lcd_lvl->display(ff7.slot[7].desc.level);
    ui->s8_lcd_gil->display(double(ff7.slot[7].desc.gil));

    ui->s8_lcd_hr->display(int(ff7.slot[7].desc.time/3600));
    ui->s8_lcd_min->display(int(ff7.slot[7].desc.time/60 %60));
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
                       ui->s8_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                       ui->s8_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                       ui->s8_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
                       break;
                   case 10:
                       ui->s8_party3->setPixmap(QPixmap(":/icon/sep_icon"));
                       break;
                   }

    //slot 9
    ui->s9_lcd_lvl->display(ff7.slot[8].desc.level);
    ui->s9_lcd_gil->display(double(ff7.slot[8].desc.gil));

    ui->s9_lcd_hr->display(int(ff7.slot[8].desc.time/3600));
    ui->s9_lcd_min->display(int(ff7.slot[8].desc.time/60 %60));
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
                               ui->s9_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                               ui->s9_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                               ui->s9_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
                               break;
                           case 10:
                               ui->s9_party3->setPixmap(QPixmap(":/icon/sep_icon"));
                               break;
                           }

    //slot 10
    ui->s10_lcd_lvl->display(ff7.slot[9].desc.level);
    ui->s10_lcd_gil->display(double(ff7.slot[9].desc.gil));

    ui->s10_lcd_hr->display(int(ff7.slot[9].desc.time/3600));
    ui->s10_lcd_min->display(int(ff7.slot[9].desc.time/60 %60));
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
                                       ui->s10_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                                       ui->s10_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                                       ui->s10_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
                                       break;
                                   case 10:
                                       ui->s10_party3->setPixmap(QPixmap(":/icon/sep_icon"));
                                       break;
                                   }
    //slot 10
       ui->s11_lcd_lvl->display(ff7.slot[10].desc.level);
       ui->s11_lcd_gil->display(double(ff7.slot[10].desc.gil));

       ui->s11_lcd_hr->display(int(ff7.slot[10].desc.time/3600));
       ui->s11_lcd_min->display(int(ff7.slot[10].desc.time/60 %60));
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
           ui->s11_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
           ui->s11_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
           ui->s11_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
           break;
       case 10:
           ui->s11_party3->setPixmap(QPixmap(":/icon/sep_icon"));
           break;
       }

       //slot 11
       ui->s12_lcd_lvl->display(ff7.slot[11].desc.level);
       ui->s12_lcd_gil->display(double(ff7.slot[11].desc.gil));

       ui->s12_lcd_hr->display(int(ff7.slot[11].desc.time/3600));
       ui->s12_lcd_min->display(int(ff7.slot[11].desc.time/60 %60));
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
                  ui->s12_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                  ui->s12_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                  ui->s12_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
                  break;
              case 10:
                  ui->s12_party3->setPixmap(QPixmap(":/icon/sep_icon"));
                  break;
              }

       //slot 12
       ui->s13_lcd_lvl->display(ff7.slot[12].desc.level);
       ui->s13_lcd_gil->display(double(ff7.slot[12].desc.gil));

       ui->s13_lcd_hr->display(int(ff7.slot[12].desc.time/3600));
       ui->s13_lcd_min->display(int(ff7.slot[12].desc.time/60 %60));
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
                          ui->s13_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                          ui->s13_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                          ui->s13_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
                          break;
                      case 10:
                          ui->s13_party3->setPixmap(QPixmap(":/icon/sep_icon"));
                          break;
                      }

       //slot 4
       ui->s14_lcd_lvl->display(ff7.slot[13].desc.level);
       ui->s14_lcd_gil->display(double(ff7.slot[13].desc.gil));

       ui->s14_lcd_hr->display(int(ff7.slot[13].desc.time/3600));
       ui->s14_lcd_min->display(int(ff7.slot[13].desc.time/60 %60));
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
                                  ui->s14_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                                  ui->s14_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                                  ui->s14_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
                                  break;
                              case 10:
                                  ui->s14_party3->setPixmap(QPixmap(":/icon/sep_icon"));
                                  break;
                              }

       //slot 5
       ui->s15_lcd_lvl->display(ff7.slot[14].desc.level);
       ui->s15_lcd_gil->display(double(ff7.slot[14].desc.gil));

       ui->s15_lcd_hr->display(int(ff7.slot[14].desc.time/3600));
       ui->s15_lcd_min->display(int(ff7.slot[14].desc.time/60 %60));
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
                                          ui->s15_party1->setPixmap(QPixmap(":/icon/cloud_icon"));
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
                                          ui->s15_party2->setPixmap(QPixmap(":/icon/cloud_icon"));
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
             ui->s15_party3->setPixmap(QPixmap(":/icon/cloud_icon"));
             break;
        case 10:
            ui->s15_party3->setPixmap(QPixmap(":/icon/sep_icon"));
            break;
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


void SlotSelect::on_btn_s1_clicked()
{
    s=0;
    SlotSelect::close();
}

void SlotSelect::on_btn_s2_clicked()
{
    s=1;
    SlotSelect::close();
}

void SlotSelect::on_btn_s3_clicked()
{
    s=2;
    SlotSelect::close();
}

void SlotSelect::on_btn_s4_clicked()
{
    s=3;
    SlotSelect::close();
}

void SlotSelect::on_btn_s5_clicked()
{
    s=4;
    SlotSelect::close();
}

void SlotSelect::on_btn_s6_clicked()
{
    s=5;
    SlotSelect::close();
}

void SlotSelect::on_btn_s7_clicked()
{
    s=6;
    SlotSelect::close();
}

void SlotSelect::on_btn_s8_clicked()
{
    s=7;
    SlotSelect::close();
}

void SlotSelect::on_btn_s9_clicked()
{
    s=8;
    SlotSelect::close();
}

void SlotSelect::on_btn_s10_clicked()
{
    s=9;
    SlotSelect::close();
}

void SlotSelect::on_btn_s11_clicked()
{
    s=10;
    SlotSelect::close();
}

void SlotSelect::on_btn_s12_clicked()
{
    s=11;
    SlotSelect::close();
}

void SlotSelect::on_btn_s13_clicked()
{
    s=12;
    SlotSelect::close();
}

void SlotSelect::on_btn_s14_clicked()
{
    s=13;
    SlotSelect::close();
}

void SlotSelect::on_btn_s15_clicked()
{
    s=14;
    SlotSelect::close();
}

