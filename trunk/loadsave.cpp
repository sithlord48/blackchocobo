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

#include <QFileDialog> // for file dialogs
#include <QDataStream> // for data manip
//#include <QProcess>   // for calling ext processes (like checksum)
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"   // contains checksumming functions.
#include "slotselect.h"

#include "loadsave.h"
extern FF7 ff7;
extern int s;

FF7SLOT bufferslot;

void MainWindow::on_actionOpen_Save_File_activated()
{

    QString fileName = QFileDialog::getOpenFileName(this,
                                        tr("Open Final Fantasy 7 Save"),(""),
            tr("Known FF7 Save Types (*.ff7 BAS* *.mcr *.mcd *.psv);;PC FF7 SaveGame (*.ff7);;PSX FF7 SaveGame (*-S*);;MC SaveGame (*.mcr *.mcd);;PSV SaveGame (*.psv)"));

    if (!fileName.isEmpty())
        loadFileFull(fileName);

}

void MainWindow::on_actionSave_File_activated()
{
    // check for the type of save loaded and set the output type so we don't save the wrong type, all conversion opperations should be done via an Export function.
if(ff7.savetype==1)
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Final Fantasy 7 PC SaveGame"), "",
                tr("FF7 PC SaveGame(*.ff7)"));
    if (!fileName.isEmpty())
        saveFileFull(fileName);
}
else if(ff7.savetype==2)
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Final Fantasy 7 PSX SaveGame"), "",
                tr("FF7 PSX SaveGame(*)"));
    if (!fileName.isEmpty())
        saveFileFull(fileName);
}
else if(ff7.savetype==3)
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Final Fantasy 7 MC SaveGame"), "",
                tr("FF7 MC SaveGame(*.mcr),(*.mcd)"));
    if (!fileName.isEmpty())
        saveFileFull(fileName);
}
else {QMessageBox::warning(this, tr("Black Chocobo"),tr("Cannot save This Type of File"));}

}
/* The New Open File Function (Vegeta_Ss4) v0.8.3 */
void MainWindow::loadFileFull(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly )) {
            QMessageBox::warning(this, tr("Black Chocobo"),
                           tr("Cannot read file %1:\n%2.")
                            .arg(fileName)
                 .arg(file.errorString()));
    return;
    }
    QByteArray ff7file;
ff7file = file.readAll(); //put all data in temp raw file
QByteArray temp; // create a temp to be used when needed
// parse the save data... starting from the top...

//START SET FORMAT CONST & VARS

    int file_size = file.size();

    if(file_size == FF7_PC_SAVE_GAME_SIZE)
    {
       ff7.SG_SIZE          = FF7_PC_SAVE_GAME_SIZE;
       ff7.SG_HEADER        = FF7_PC_SAVE_GAME_HEADER;
       ff7.SG_FOOTER        = FF7_PC_SAVE_GAME_FOOTER;
       ff7.SG_DATA_SIZE     = FF7_PC_SAVE_GAME_DATA_SIZE;
       ff7.SG_SLOT_HEADER   = FF7_PC_SAVE_GAME_SLOT_HEADER;
       ff7.SG_SLOT_FOOTER   = FF7_PC_SAVE_GAME_SLOT_FOOTER;
       ff7.SG_SLOT_SIZE     = FF7_PC_SAVE_GAME_SLOT_SIZE;
       ff7.SG_SLOT_NUMBER   = FF7_PC_SAVE_GAME_SLOT_NUMBER;
       ff7.SG_TYPE          = "PC";
       ff7.file_headerp     = ff7.file_header_pc;           //pointer to pc file header
       ff7.file_footerp     = ff7.file_footer_pc;           //pointer to pc file footer
       //ff7.hf->headerp      = ff7.hf->header_pc;            //pointer to pc slot header
       //ff7.hf->footerp      = ff7.hf->footer_pc;            //pointer to pc slot footer
       ff7.savetype         = 1;
    }
    else if(file_size == FF7_PSX_SAVE_GAME_SIZE)
    {
       ff7.SG_SIZE          = FF7_PSX_SAVE_GAME_SIZE;
       ff7.SG_HEADER        = FF7_PSX_SAVE_GAME_HEADER;
       ff7.SG_FOOTER        = FF7_PSX_SAVE_GAME_FOOTER;
       ff7.SG_DATA_SIZE     = FF7_PSX_SAVE_GAME_DATA_SIZE;
       ff7.SG_SLOT_HEADER   = FF7_PSX_SAVE_GAME_SLOT_HEADER;
       ff7.SG_SLOT_FOOTER   = FF7_PSX_SAVE_GAME_SLOT_FOOTER;
       ff7.SG_SLOT_SIZE     = FF7_PSX_SAVE_GAME_SLOT_SIZE;
       ff7.SG_SLOT_NUMBER   = FF7_PSX_SAVE_GAME_SLOT_NUMBER;
       ff7.SG_TYPE          = "PSX";
       ff7.file_headerp     = ff7.file_header_psx;          //pointer to psx file header
       ff7.file_footerp     = ff7.file_footer_psx;          //pointer to psx file footer
       //ff7.hf->headerp      = ff7.hf->header_psx;           //pointer to psx slot header
       //ff7.hf->footerp      = ff7.hf->footer_psx;           //pointer to psx slot footer
       ff7.savetype         = 2;
    }
    else if(file_size == FF7_MC_SAVE_GAME_SIZE)
    {
       ff7.SG_SIZE          = FF7_MC_SAVE_GAME_SIZE;
       ff7.SG_HEADER        = FF7_MC_SAVE_GAME_HEADER;
       ff7.SG_FOOTER        = FF7_MC_SAVE_GAME_FOOTER;
       ff7.SG_DATA_SIZE     = FF7_MC_SAVE_GAME_DATA_SIZE;
       ff7.SG_SLOT_HEADER   = FF7_MC_SAVE_GAME_SLOT_HEADER;
       ff7.SG_SLOT_FOOTER   = FF7_MC_SAVE_GAME_SLOT_FOOTER;
       ff7.SG_SLOT_SIZE     = FF7_MC_SAVE_GAME_SLOT_SIZE;
       ff7.SG_SLOT_NUMBER   = FF7_MC_SAVE_GAME_SLOT_NUMBER;
       ff7.SG_TYPE          = "MC";
       ff7.file_headerp     = ff7.file_header_mc;           //pointer to mc file header
       ff7.file_footerp     = ff7.file_footer_mc;           //pointer to mc file footer
       //ff7.hf->headerp      = ff7.hf->header_mc;            //pointer to mc slot header
       //ff7.hf->footerp      = ff7.hf->footer_mc;            //pointer to mc slot footer
       ff7.savetype         = 3;
    }
    else if(file_size == FF7_PSV_SAVE_GAME_SIZE)
    {
       ff7.SG_SIZE          = FF7_PSV_SAVE_GAME_SIZE;
       ff7.SG_HEADER        = FF7_PSV_SAVE_GAME_HEADER;
       ff7.SG_FOOTER        = FF7_PSV_SAVE_GAME_FOOTER;
       ff7.SG_DATA_SIZE     = FF7_PSV_SAVE_GAME_DATA_SIZE;
       ff7.SG_SLOT_HEADER   = FF7_PSV_SAVE_GAME_SLOT_HEADER;
       ff7.SG_SLOT_FOOTER   = FF7_PSV_SAVE_GAME_SLOT_FOOTER;
       ff7.SG_SLOT_SIZE     = FF7_PSV_SAVE_GAME_SLOT_SIZE;
       ff7.SG_SLOT_NUMBER   = FF7_PSV_SAVE_GAME_SLOT_NUMBER;
       ff7.SG_TYPE          = "PSV";
       ff7.file_headerp     = ff7.file_header_psv;          //pointer to psx file header
       ff7.file_footerp     = ff7.file_footer_psv;          //pointer to psx file footer
       ff7.savetype         = 4;
    }
    else {
       //ff7.SG_TYPE          = "UNKNOWN";
       //ff7.savetype         = 0;
        QMessageBox::warning(this, tr("Unknown File"),
                       tr("File: %1 \nisn't a FF7 SaveGame.")
                        .arg(fileName));

       return;
    }

//END SET FORMAT CONST & VARS


    memcpy(ff7.file_headerp,ff7file.mid(0x0000,ff7.SG_HEADER),ff7.SG_HEADER);// collect header (0x09) bytes (PC), (0x00) bytes (PSX), (0x2000) bytes (MC)


for (int i=0;i<ff7.SG_SLOT_NUMBER;i++){ // MAIN FILL LOOP

    int index = (ff7.SG_SLOT_SIZE*i) + ff7.SG_HEADER + ff7.SG_SLOT_HEADER;

    memcpy(ff7.hf[i].sl_header,ff7file.mid((ff7.SG_SLOT_SIZE*i) + (ff7.SG_HEADER + 0x0000),ff7.SG_SLOT_HEADER),ff7.SG_SLOT_HEADER);// collect slot header (0x00) bytes (PC), (0x0200) bytes (PSX), (0x0200) bytes (MC)

    temp = ff7file.mid((index+0x0000),2); // collect checksum [first 2 bytes of save slot]
    memcpy(&ff7.slot[i].checksum,temp,2);

    temp = ff7file.mid((index+0x0002),2);//collect z_1 2 unknow bits if checksum !4bytes
    memcpy(&ff7.slot[i].z_1,temp,2);

    temp = ff7file.mid((index+0x0004),1);
    memcpy(&ff7.slot[i].desc.level,temp,1); // collect description level

    for (int p=0; p<3;p++){ff7.slot[i].desc.party[p] = ff7file.at((index+0x0005) + p);} //collect description party members [character's portrait]
    for (int n=0;n<16;n++){ff7.slot[i].desc.name[n]  = ff7file.at((index+0x0008) + n);}//collect description name chPC[] [character's name]

    temp = ff7file.mid((index+0x0018),2); // collect cur hp
    memcpy(&ff7.slot[i].desc.curHP,temp,2);

    temp = ff7file.mid((index+0x001A),2);// collect max hp
    memcpy(&ff7.slot[i].desc.maxHP,temp,2);

    temp = ff7file.mid((index+0x001C),2);// collect cur mp
    memcpy(&ff7.slot[i].desc.curMP,temp,2);

    temp = ff7file.mid((index+0x001E),2);// collect max mp
    memcpy(&ff7.slot[i].desc.maxMP,temp,2);

    temp =ff7file.mid((index+0x0020),4); // collect description gil amount
    memcpy(&ff7.slot[i].desc.gil,temp,4);

    temp =ff7file.mid((index+0x0024),4); //collect description time (in seconds)
    memcpy(&ff7.slot[i].desc.time, temp,4);

    for (int loc=0; loc<32;loc++){ff7.slot[i].desc.location[loc] = ff7file.at((ff7.SG_SLOT_SIZE * i)+(ff7.SG_HEADER+ff7.SG_SLOT_HEADER + 0x0028 + loc));}//collect descrition location ChPC[];

    for(int c=0;c<4;c++){//collect color data...
        for (int cc=0;cc<3;cc++){
        temp =ff7file.mid((index+0x0048)+(3*c)+cc,1);
        memcpy(&ff7.slot[i].colors[c][cc],temp,1);
            }}

                QByteArray temp2;
       for(int who=0;who<9;who++){//PARSE CHAR DATA
        temp2 = ff7file.mid((index+0x0054)+(char_len*who),132);
        temp=temp2.mid(0x00 ,1);
        memcpy(&ff7.slot[i].chars[who].id, temp,1);

        temp=temp2.mid(0x01 ,1);
        memcpy(&ff7.slot[i].chars[who].level, temp,1);

        temp=temp2.mid(0x02 ,1);
        memcpy(&ff7.slot[i].chars[who].strength, temp,1);

        temp=temp2.mid(0x03 ,1);
        memcpy(&ff7.slot[i].chars[who].vitality, temp,1);

        temp=temp2.mid(0x04 ,1);
        memcpy(&ff7.slot[i].chars[who].magic, temp,1);

        temp=temp2.mid(0x05 ,1);
        memcpy(&ff7.slot[i].chars[who].spirit, temp,1);

        temp=temp2.mid(0x06 ,1);
        memcpy(&ff7.slot[i].chars[who].dexterity, temp,1);

        temp=temp2.mid(0x07 ,1);
        memcpy(&ff7.slot[i].chars[who].luck, temp,1);

        temp=temp2.mid(0x08,1);
        memcpy(&ff7.slot[i].chars[who].strength_bonus,temp,1);

        temp=temp2.mid(0x09,1);
        memcpy(&ff7.slot[i].chars[who].vitality_bonus,temp,1);

        temp=temp2.mid(0x0A,1);
        memcpy(&ff7.slot[i].chars[who].magic_bonus,temp,1);

        temp=temp2.mid(0x0B,1);
        memcpy(&ff7.slot[i].chars[who].spirit_bonus,temp,1);

        temp=temp2.mid(0x0C,1);
        memcpy(&ff7.slot[i].chars[who].dexterity_bonus,temp,1);

        temp=temp2.mid(0x0D,1);
        memcpy(&ff7.slot[i].chars[who].luck_bonus,temp,1);

        temp=temp2.mid(0x0E,1);
        memcpy(&ff7.slot[i].chars[who].limitlevel,temp,1);

        temp=temp2.mid(0x0F,1);
        memcpy(&ff7.slot[i].chars[who].limitbar,temp,1);

        temp=temp2.mid(0x10,12);
        for (int n=0;n<12;n++){ff7.slot[i].chars[who].name[n] = temp.at(n);}

        temp=temp2.mid(0x1C,1);
        memcpy(&ff7.slot[i].chars[who].weapon,temp,1);

        temp=temp2.mid(0x1D,1);
        memcpy(&ff7.slot[i].chars[who].armor,temp,1);

        temp=temp2.mid(0x1E,1);
        memcpy(&ff7.slot[i].chars[who].accessory,temp,1);

        temp=temp2.mid(0x1F,3);
        for (int f=0;f<3;f++){ff7.slot[i].chars[who].flags[f] = temp.at(f);}

        temp=temp2.mid(0x22,2);
        memcpy(&ff7.slot[i].chars[who].limits,temp,2);

        temp=temp2.mid(0x24,2);
        memcpy(&ff7.slot[i].chars[who].kills,temp,2);

        temp=temp2.mid(0x26,2);
        memcpy(&ff7.slot[i].chars[who].timesused1,temp,2);

        temp=temp2.mid(0x28,2);
        memcpy(&ff7.slot[i].chars[who].timesused2,temp,2);

        temp=temp2.mid(0x2A,2);
        memcpy(&ff7.slot[i].chars[who].timesused3,temp,2);

        temp=temp2.mid(0x2C,2);
        memcpy(&ff7.slot[i].chars[who].curHP,temp,2);

        temp=temp2.mid(0x2E,2);
        memcpy(&ff7.slot[i].chars[who].baseHP,temp,2);

        temp=temp2.mid(0x30,2);
        memcpy(&ff7.slot[i].chars[who].curMP,temp,2);

        temp=temp2.mid(0x32,2);
        memcpy(&ff7.slot[i].chars[who].baseMP,temp,2);

        temp=temp2.mid(0x34,4);
        for(int z4=0;z4<4;z4++){ff7.slot[i].chars[who].z_4[z4]=temp.at(z4);}

        temp=temp2.mid(0x38,2);
        memcpy(&ff7.slot[i].chars[who].maxHP,temp,2);

        temp=temp2.mid(0x3A,2);
        memcpy(&ff7.slot[i].chars[who].maxMP,temp,2);

        temp=temp2.mid(0x3C,4);
        memcpy(&ff7.slot[i].chars[who].exp,temp,4);

        for (int mat=0;mat<16;mat++){
          temp=temp2.mid(0x40 + 4*mat,1);
          memcpy(&ff7.slot[i].chars[who].materias[mat].id,temp,1);
          temp=temp2.mid(0x40+4*mat +1,3);
          for(int m=0;m<3;m++){ff7.slot[i].chars[who].materias[mat].ap[m]=temp.at(m);}
          }
       temp=temp2.mid(0x80,4);
       memcpy(&ff7.slot[i].chars[who].expNext,temp,4);
       }//END CHAR LOOPING
       for (int p=0;p<3;p++)
       {
           temp=ff7file.mid((index+0x04F8) +p,1);//Party member in slots 1,2,3
           memcpy(&ff7.slot[i].party[p],temp,1);
       }
    temp=ff7file.mid((index+0x04FB),1);
    memcpy(&ff7.slot[i].z_2,temp,1); //0xFF


    for(int itm=0;itm<320;itm++) //Party item stock
    {
        temp=ff7file.mid((index+0x04FC) + (2*itm),1);
        memcpy(&ff7.slot[i].items[itm].id,temp,1);
        temp=ff7file.mid((index+0x04FC) + (2*itm)+1,1);
        memcpy(&ff7.slot[i].items[itm].qty,temp,1);
    }

    for (int met=0;met<200;met++) //Party materia stock
    {
        temp=ff7file.mid((index+0x077C) +(4*met),1);
        memcpy(&ff7.slot[i].materias[met].id,temp,1);
        temp=ff7file.mid((index+0x077C) +(4*met)+1,3);
        for (int ma=0;ma<3;ma++){ff7.slot[i].materias[met].ap[ma]=temp.at(ma);}
    }
    for (int met=0;met<48;met++) //Materia stolen by Yuffie
    {
        temp=ff7file.mid((index+0x0A9C) +(4*met),1);
        memcpy(&ff7.slot[i].stolen[met].id,temp,1);
        temp=ff7file.mid((index+0x0A9C) +(4*met)+1,3);
        for (int ma=0;ma<3;ma++){ff7.slot[i].stolen[met].ap[ma]=temp.at(ma);}
    }
   temp=ff7file.mid((index+0x0B5C),32); //32 Bytes Unknown

   for(int z=0;z<32;z++)//32 Bytes Unknown
   {
   ff7.slot[i].z_3[z] = temp.at(z);
   }
   temp=ff7file.mid((index+0x0B7C),4); // Collect Gil
   memcpy(&ff7.slot[i].gil,temp,4);

   temp=ff7file.mid((index+0x0B80),4); //Total played time
   memcpy(&ff7.slot[i].time,temp,4);

   temp=ff7file.mid((index+0x0B84),16);
   for (int z=0;z<16;z++)
   {
   ff7.slot[i].z_4[z] =temp.at(z);
   }

   temp=ff7file.mid((index+0x0B94),2);// Current map
   memcpy(&ff7.slot[i].mapid,temp,2);
   temp=ff7file.mid((index+0x0B96),2);
   memcpy(&ff7.slot[i].locationid,temp,2);// Current location

   temp=ff7file.mid((index+0x0B98),2);// Unknown
   for(int z=0;z<2;z++)
   {
       ff7.slot[i].z_5[z]=temp.at(z);
   }

   temp=ff7file.mid((index+0x0B9A),2);//x location world map
   memcpy(&ff7.slot[i].coord.x,temp,2);
   temp=ff7file.mid((index+0x0B9C),2);//y location world map
   memcpy(&ff7.slot[i].coord.y,temp,2);
   temp=ff7file.mid((index+0x0B9E),2);//z location world map
   memcpy(&ff7.slot[i].coord.z,temp,2);

   temp=ff7file.mid((index+0x0BA0),4);//Unknown related to map location and coords
   for(int z=0;z<4;z++){ff7.slot[i].z_6[z]=temp.at(z);}

   temp=ff7file.mid((index+0x0BA4),2);// man progress var
   memcpy (&ff7.slot[i].mprogress,temp,2);

   temp=ff7file.mid((index+0xBA6),1);
   memcpy(&ff7.slot[i].unknown1,temp,1);

   temp=ff7file.mid((index+0x0BA7)+0x00,1);
   memcpy(&ff7.slot[i].love.aeris,temp,1);
   temp=ff7file.mid((index+0x0BA7)+0x01,1);
   memcpy(&ff7.slot[i].love.tifa,temp,1);
   temp=ff7file.mid((index+0x0BA7)+0x02,1);
   memcpy(&ff7.slot[i].love.yuffie,temp,1);
   temp=ff7file.mid((index+0x0BA7)+0x03,1);
   memcpy(&ff7.slot[i].love.barret,temp,1);

   temp=ff7file.mid((index+0x0BAB),17);//Unknown
   for(int z=0;z<17;z++){ff7.slot[i].z_7[z]=temp.at(z);}
   temp=ff7file.mid((index+0x0BBC),2);//Number of battles fought
   memcpy(&ff7.slot[i].battles,temp,2);
   temp=ff7file.mid((index+0x0BBE),2);//Number of escapes
   memcpy(&ff7.slot[i].runs,temp,2);
   temp=ff7file.mid((index+0x0BC0),36);
   for(int t=0;t<36;t++){ff7.slot[i].temp[t] = temp.at(t);}
   temp=ff7file.mid((index+0x0BE4),8); //Key items
   for(int k=0;k<8;k++){ff7.slot[i].keyitems[k] = temp.at(k);}
   temp=ff7file.mid((index+0x0BEC),13);
   for(int z=0;z<13;z++){ff7.slot[i].z_8[z] =temp.at(z);}
   temp=ff7file.mid((index+0x0BF9),4);//Field Chocobo rating
   for (int c=0;c<4;c++){ff7.slot[i].pennedchocos[c]=temp.at(c);}
   // START NEW DATA

   temp=ff7file.mid((index+0x0BFD),136);
   for (int z=0;z<136;z++){ff7.slot[i].z_9[z]= temp.at(z);}

   temp= ff7file.mid ((index+0x0C85),1);
   memcpy(&ff7.slot[i].bm_progress1,temp,1);

   temp= ff7file.mid ((index+0x0C86),1);
   memcpy(&ff7.slot[i].bm_progress2,temp,1);

   temp= ff7file.mid((index+0x0C87),95);
   for (int z=0;z<95;z++){ff7.slot[i].unknown2[z] = temp.at(z);}

   temp= ff7file.mid ((index+0x0CE6),1);
   memcpy(&ff7.slot[i].bm_progress3,temp,1);

   temp=ff7file.mid((index+0x0CE7),7);
   for (int z=0;z<7;z++){ff7.slot[i].unknown3[z] = temp.at(z);}


   // END NEW DATA
   temp=ff7file.mid((index+0x0CEE),2); // Collect GP
   memcpy(&ff7.slot[i].gp,temp,2);
   temp=ff7file.mid((index+0x0CF0),12);
   for (int z=0;z<12;z++){ff7.slot[i].z_10[z]=temp.at(z);}
   temp=ff7file.mid((index+0x0CFC),1);
   memcpy(&ff7.slot[i].stables,temp,1);
   temp=ff7file.mid((index+0x0CFD),1);//Bug Fixed! Before was z_11 (Vegeta_Ss4) v0.8.3
   memcpy(&ff7.slot[i].stablesoccupied,temp,1);
   temp=ff7file.mid((index+0x0CFE),1);//Bug Fixed! Before was stablesoccupied (Vegeta_Ss4) v0.8.3
   memcpy(&ff7.slot[i].z_11,temp,1);
   temp=ff7file.mid((index+0x0CFF),1);// chocobomask.
   memcpy(&ff7.slot[i].chocobomask,temp,1);
   temp=ff7file.mid((index+0x0D00),1);
   memcpy(&ff7.slot[i].chocoborn,temp,1);
   temp=ff7file.mid((index+0x0D01),101);
   for(int z=0;z<101;z++){ff7.slot[i].z_12[z]=temp.at(z);}
   temp=ff7file.mid((index+0x0D66),1);
   memcpy(&ff7.slot[i].turtleflyers,temp,1);
   temp=ff7file.mid((index+0x0D67),93);
   for(int z=0;z<93;z++){ff7.slot[i].temp2[z] = temp.at(z);}

   for (int c=0;c<4;c++)// collect chocobo slots 1-4
   {
    temp2 = ff7file.mid((index+0x0DC4)+(c*16),16);
    temp = temp2.mid (0x0,2);
    memcpy(&ff7.slot[i].chocobos[c].sprintspd,temp,2);
    temp = temp2.mid (0x2,2);
    memcpy(&ff7.slot[i].chocobos[c].maxsprintspd,temp,2);
    temp = temp2.mid (0x4,2);
    memcpy(&ff7.slot[i].chocobos[c].speed,temp,2);
    temp = temp2.mid (0x6,2);
    memcpy(&ff7.slot[i].chocobos[c].maxspeed,temp,2);
    temp = temp2.mid (0x8,1);
    memcpy(&ff7.slot[i].chocobos[c].accel,temp,1);
    temp = temp2.mid (0x9,1);
    memcpy(&ff7.slot[i].chocobos[c].coop,temp,1);
    temp = temp2.mid (0xA,1);
    memcpy(&ff7.slot[i].chocobos[c].intelligence,temp,1);
    temp = temp2.mid (0xB,1);
    memcpy(&ff7.slot[i].chocobos[c].personality,temp,1);
    temp = temp2.mid (0xC,1);
    memcpy(&ff7.slot[i].chocobos[c].pcount,temp,1);
    temp = temp2.mid (0xD,1);
    memcpy(&ff7.slot[i].chocobos[c].raceswon,temp,1);
    temp = temp2.mid (0xE,1);
    memcpy(&ff7.slot[i].chocobos[c].sex,temp,1);
    temp = temp2.mid (0xF,1);
    memcpy(&ff7.slot[i].chocobos[c].type,temp,1);
   }

   temp = ff7file.mid((index+0x0E04),160);
   for (int z=0;z<160;z++){ff7.slot[i].z_13[z]=temp.at(z);}

   temp = ff7file.mid((index+0x0EA4),1);
   memcpy(&ff7.slot[i].disc,temp,1);

   temp = ff7file.mid((index+0x0EA5),31);
   for (int z=0;z<31;z++){ff7.slot[i].z_14[z]=temp.at(z);}


   for (int c=0;c<6;c++) //get chocobonames
   {
       temp=ff7file.mid((index+0x0EC4)+(c*6),6);
       for (int o=0;o<6;o++){
           ff7.slot[i].chocobonames[c][o]= temp.at(o);
       }
   }


   // grab all the stamina values too
  temp = ff7file.mid((index+0x0EE8),2);
  memcpy(&ff7.slot[i].chocostaminas[0],temp,2);
  temp = ff7file.mid((index+0x0EEA),2);
  memcpy(&ff7.slot[i].chocostaminas[1],temp,2);
  temp = ff7file.mid((index+0x0EEC),2);
  memcpy(&ff7.slot[i].chocostaminas[2],temp,2);
  temp = ff7file.mid((index+0x0EEE),2);
  memcpy(&ff7.slot[i].chocostaminas[3],temp,2);
  temp = ff7file.mid((index+0x0EF0),2);
  memcpy(&ff7.slot[i].chocostaminas[4],temp,2);
  temp = ff7file.mid((index+0x0EF2),2);
  memcpy(&ff7.slot[i].chocostaminas[5],temp,2);


   temp = ff7file.mid ((index+0x0EF4),400);
   for(int z=0;z<400;z++){
       ff7.slot[i].z_17[z]=temp.at(z);

   }


   for (int c=4;c<6;c++)// collect chocobo slots 5-6
   {
    temp2 = ff7file.mid((index+0x1084)+((c-4)*16),16);
    temp = temp2.mid (0x0,2);
    memcpy(&ff7.slot[i].chocobos[c].sprintspd,temp,2);
    temp = temp2.mid (0x2,2);
    memcpy(&ff7.slot[i].chocobos[c].maxsprintspd,temp,2);
    temp = temp2.mid (0x4,2);
    memcpy(&ff7.slot[i].chocobos[c].speed,temp,2);
    temp = temp2.mid (0x6,2);
    memcpy(&ff7.slot[i].chocobos[c].maxspeed,temp,2);
    temp = temp2.mid (0x8,1);
    memcpy(&ff7.slot[i].chocobos[c].accel,temp,1);
    temp = temp2.mid (0x9,1);
    memcpy(&ff7.slot[i].chocobos[c].coop,temp,1);
    temp = temp2.mid (0xA,1);
    memcpy(&ff7.slot[i].chocobos[c].intelligence,temp,1);
    temp = temp2.mid (0xB,1);
    memcpy(&ff7.slot[i].chocobos[c].personality,temp,1);
    temp = temp2.mid (0xC,1);
    memcpy(&ff7.slot[i].chocobos[c].pcount,temp,1);
    temp = temp2.mid (0xD,1);
    memcpy(&ff7.slot[i].chocobos[c].raceswon,temp,1);
    temp = temp2.mid (0xE,1);
    memcpy(&ff7.slot[i].chocobos[c].sex,temp,1);
    temp = temp2.mid (0xF,1);
    memcpy(&ff7.slot[i].chocobos[c].type,temp,1);
   }


   temp = ff7file.mid((index+0x10A4),2);
   memcpy(&ff7.slot[i].phsmask,temp,2);
   temp = ff7file.mid((index+0x10A6),2);
   memcpy(&ff7.slot[i].unlockedchars,temp,2);
   temp = ff7file.mid((index+0x10A8),48);
   for(int z=0;z<48;z++){ff7.slot[i].z_18[z] = temp.at(z);}
   temp =ff7file.mid((index+0x10D8),1);
   memcpy(&ff7.slot[i].battlespeed,temp,1);
   temp =ff7file.mid((index+0x10D9),1);
   memcpy(&ff7.slot[i].battlemspeed,temp,1);
   temp=ff7file.mid((index+0x10DA),1);
   memcpy(&ff7.slot[i].options1,temp,1);
   temp=ff7file.mid((index+0x10DB),1);
   memcpy(&ff7.slot[i].options2,temp,1);
   temp = ff7file.mid((index+0x10DC),16);
   for(int z=0;z<16;z++){ff7.slot[i].z_19[z] = temp.at(z);}
   temp =ff7file.mid((index+0x10EC),1);
   memcpy(&ff7.slot[i].fieldmspeed,temp,1);
   temp = ff7file.mid((index+0x10ED),7);
   for(int z=0;z<7;z++){ff7.slot[i].z_20[z] = temp.at(z);}


/*
   temp = ff7file.mid((ff7.SG_SLOT_SIZE*i)+ (ff7.SG_HEADER+ff7.SG_SLOT_HEADER+ff7.SG_DATA_SIZE),ff7.SG_SLOT_FOOTER);// added collect footer 0x12F4 len(0x0D0C) bytes (PSX)
   memcpy(&ff7.hf[i].footerp,temp,ff7.SG_SLOT_FOOTER);
*/

   //for(int z=0;z<ff7.SG_SLOT_FOOTER;z++){ff7.slot[i].footerp[z] = temp.at(z);}

/*
   temp = ff7file.mid((ff7.SG_SLOT_SIZE*i)+ (ff7.SG_HEADER+ff7.SG_SLOT_HEADER+ff7.SG_DATA_SIZE),ff7.SG_SLOT_FOOTER);// added collect footer 0x12F4 len(0x0D0C) bytes (PSX)
   for(int z=0;z<ff7.SG_SLOT_FOOTER;z++){ff7.slot[i].footerp[z] = temp.at(z);}
*/

   memcpy(ff7.hf[i].sl_footer,ff7file.mid((ff7.SG_SLOT_SIZE*i)+ (ff7.SG_HEADER+ff7.SG_SLOT_HEADER+ff7.SG_DATA_SIZE),ff7.SG_SLOT_FOOTER),ff7.SG_SLOT_FOOTER);// collect slot footer (0x00) bytes (PC), (0x0D0C) bytes (PSX), (0x0D0C) bytes (MC)


}//Parse slot data....

//for(int z=0;z<ff7.SG_FOOTER;z++){ff7.file_footerp[z] = temp.at(z);}//colect file footer UNUSED!!
if (ff7.savetype == 1 || ff7.savetype == 3)
{
          SlotSelect slotselect;
          slotselect.exec();
}
else
{
    s=0;
    for(int i=1;i<14;i++){clearslot(i);}
}

guirefresh();
}

void MainWindow::on_actionFrom_PSX_Slot_activated()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select Final Fantasy 7 PSX Save"),(""),tr("PSX FF7 SaveGame (*-S*)"));

    if (!fileName.isEmpty()){
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))
    {
            QMessageBox::warning(this, tr("Black Chocobo"),
                           tr("Cannot read file %1:\n%2.")
                            .arg(fileName)
                 .arg(file.errorString()));
    return;
}
QByteArray ff7file;
ff7file = file.readAll(); //put all data in temp raw file
QByteArray temp; // create a temp to be used when needed
// parse the save data... starting from the top...



int index = 0x200;


temp = ff7file.mid((index+0x0000),2); // collect checksum [first 2 bytes of save slot]
memcpy(&ff7.slot[s].checksum,temp,2);

temp = ff7file.mid((index+0x0002),2);//collect z_1 2 unknow bits if checksum !4bytes
memcpy(&ff7.slot[s].z_1,temp,2);

temp = ff7file.mid((index+0x0004),1);
memcpy(&ff7.slot[s].desc.level,temp,1); // collect description level

for (int p=0; p<3;p++){ff7.slot[s].desc.party[p] = ff7file.at(index +0x0005 +p);} //collect description party members [character's portrait]
for (int n=0;n<16;n++){ff7.slot[s].desc.name[n]  = ff7file.at(index +0x0008 +n);}//collect description name chPC[] [character's name]

temp = ff7file.mid((index+0x0018),2); // collect cur hp
memcpy(&ff7.slot[s].desc.curHP,temp,2);

temp = ff7file.mid((index+0x001A),2);// collect max hp
memcpy(&ff7.slot[s].desc.maxHP,temp,2);

temp = ff7file.mid((index+0x001C),2);// collect cur mp
memcpy(&ff7.slot[s].desc.curMP,temp,2);

temp = ff7file.mid((index+0x001E),2);// collect max mp
memcpy(&ff7.slot[s].desc.maxMP,temp,2);

temp =ff7file.mid((index+0x0020),4); // collect description gil amount
memcpy(&ff7.slot[s].desc.gil,temp,4);

temp =ff7file.mid((index+0x0024),4); //collect description time (in seconds)
memcpy(&ff7.slot[s].desc.time, temp,4);

for (int loc=0; loc<32;loc++){ff7.slot[s].desc.location[loc] = ff7file.at(index + 0x0028 + loc);}//collect descrition location ChPC[];

for(int c=0;c<4;c++){//collect color data...
    for (int cc=0;cc<3;cc++){
    temp =ff7file.mid((index+0x0048)+(3*c)+cc,1);
    memcpy(&ff7.slot[s].colors[c][cc],temp,1);
        }}

            QByteArray temp2;
   for(int who=0;who<9;who++){//PARSE CHAR DATA
    temp2 = ff7file.mid((index+0x0054)+(char_len*who),132);
    temp=temp2.mid(0x00 ,1);
    memcpy(&ff7.slot[s].chars[who].id, temp,1);

    temp=temp2.mid(0x01 ,1);
    memcpy(&ff7.slot[s].chars[who].level, temp,1);

    temp=temp2.mid(0x02 ,1);
    memcpy(&ff7.slot[s].chars[who].strength, temp,1);

    temp=temp2.mid(0x03 ,1);
    memcpy(&ff7.slot[s].chars[who].vitality, temp,1);

    temp=temp2.mid(0x04 ,1);
    memcpy(&ff7.slot[s].chars[who].magic, temp,1);

    temp=temp2.mid(0x05 ,1);
    memcpy(&ff7.slot[s].chars[who].spirit, temp,1);

    temp=temp2.mid(0x06 ,1);
    memcpy(&ff7.slot[s].chars[who].dexterity, temp,1);

    temp=temp2.mid(0x07 ,1);
    memcpy(&ff7.slot[s].chars[who].luck, temp,1);

    temp=temp2.mid(0x08,1);
    memcpy(&ff7.slot[s].chars[who].strength_bonus,temp,1);

    temp=temp2.mid(0x09,1);
    memcpy(&ff7.slot[s].chars[who].vitality_bonus,temp,1);

    temp=temp2.mid(0x0A,1);
    memcpy(&ff7.slot[s].chars[who].magic_bonus,temp,1);

    temp=temp2.mid(0x0B,1);
    memcpy(&ff7.slot[s].chars[who].spirit_bonus,temp,1);

    temp=temp2.mid(0x0C,1);
    memcpy(&ff7.slot[s].chars[who].dexterity_bonus,temp,1);

    temp=temp2.mid(0x0D,1);
    memcpy(&ff7.slot[s].chars[who].luck_bonus,temp,1);

    temp=temp2.mid(0x0E,1);
    memcpy(&ff7.slot[s].chars[who].limitlevel,temp,1);

    temp=temp2.mid(0x0F,1);
    memcpy(&ff7.slot[s].chars[who].limitbar,temp,1);

    temp=temp2.mid(0x10,12);
    for (int n=0;n<12;n++){ff7.slot[s].chars[who].name[n] = temp.at(n);}

    temp=temp2.mid(0x1C,1);
    memcpy(&ff7.slot[s].chars[who].weapon,temp,1);

    temp=temp2.mid(0x1D,1);
    memcpy(&ff7.slot[s].chars[who].armor,temp,1);

    temp=temp2.mid(0x1E,1);
    memcpy(&ff7.slot[s].chars[who].accessory,temp,1);

    temp=temp2.mid(0x1F,3);
    for (int f=0;f<3;f++){ff7.slot[s].chars[who].flags[f] = temp.at(f);}

    temp=temp2.mid(0x22,2);
    memcpy(&ff7.slot[s].chars[who].limits,temp,2);

    temp=temp2.mid(0x24,2);
    memcpy(&ff7.slot[s].chars[who].kills,temp,2);

    temp=temp2.mid(0x26,2);
    memcpy(&ff7.slot[s].chars[who].timesused1,temp,2);

    temp=temp2.mid(0x28,2);
    memcpy(&ff7.slot[s].chars[who].timesused2,temp,2);

    temp=temp2.mid(0x2A,2);
    memcpy(&ff7.slot[s].chars[who].timesused3,temp,2);

    temp=temp2.mid(0x2C,2);
    memcpy(&ff7.slot[s].chars[who].curHP,temp,2);

    temp=temp2.mid(0x2E,2);
    memcpy(&ff7.slot[s].chars[who].baseHP,temp,2);

    temp=temp2.mid(0x30,2);
    memcpy(&ff7.slot[s].chars[who].curMP,temp,2);

    temp=temp2.mid(0x32,2);
    memcpy(&ff7.slot[s].chars[who].baseMP,temp,2);

    temp=temp2.mid(0x34,4);
    for(int z4=0;z4<4;z4++){ff7.slot[s].chars[who].z_4[z4]=temp.at(z4);}

    temp=temp2.mid(0x38,2);
    memcpy(&ff7.slot[s].chars[who].maxHP,temp,2);

    temp=temp2.mid(0x3A,2);
    memcpy(&ff7.slot[s].chars[who].maxMP,temp,2);

    temp=temp2.mid(0x3C,4);
    memcpy(&ff7.slot[s].chars[who].exp,temp,4);

    for (int mat=0;mat<16;mat++){
      temp=temp2.mid(0x40 + 4*mat,1);
      memcpy(&ff7.slot[s].chars[who].materias[mat].id,temp,1);
      temp=temp2.mid(0x40+4*mat +1,3);
      for(int m=0;m<3;m++){ff7.slot[s].chars[who].materias[mat].ap[m]=temp.at(m);}
      }
   temp=temp2.mid(0x80,4);
   memcpy(&ff7.slot[s].chars[who].expNext,temp,4);
   }//END CHAR LOOPING
   for (int p=0;p<3;p++)
   {
       temp=ff7file.mid((index+0x04F8) +p,1);//Party member in slots 1,2,3
       memcpy(&ff7.slot[s].party[p],temp,1);
   }
temp=ff7file.mid((index+0x04FB),1);
memcpy(&ff7.slot[s].z_2,temp,1); //0xFF


for(int itm=0;itm<320;itm++) //Party item stock
{
    temp=ff7file.mid((index+0x04FC) + (2*itm),1);
    memcpy(&ff7.slot[s].items[itm].id,temp,1);
    temp=ff7file.mid((index+0x04FC) + (2*itm)+1,1);
    memcpy(&ff7.slot[s].items[itm].qty,temp,1);
}

for (int met=0;met<200;met++) //Party materia stock
{
    temp=ff7file.mid((index+0x077C) +(4*met),1);
    memcpy(&ff7.slot[s].materias[met].id,temp,1);
    temp=ff7file.mid((index+0x077C) +(4*met)+1,3);
    for (int ma=0;ma<3;ma++){ff7.slot[s].materias[met].ap[ma]=temp.at(ma);}
}
for (int met=0;met<48;met++) //Materia stolen by Yuffie
{
    temp=ff7file.mid((index+0x0A9C) +(4*met),1);
    memcpy(&ff7.slot[s].stolen[met].id,temp,1);
    temp=ff7file.mid((index+0x0A9C) +(4*met)+1,3);
    for (int ma=0;ma<3;ma++){ff7.slot[s].stolen[met].ap[ma]=temp.at(ma);}
}
temp=ff7file.mid((index+0x0B5C),32); //32 Bytes Unknown

for(int z=0;z<32;z++)//32 Bytes Unknown
{
ff7.slot[s].z_3[z] = temp.at(z);
}
temp=ff7file.mid((index+0x0B7C),4); // Collect Gil
memcpy(&ff7.slot[s].gil,temp,4);

temp=ff7file.mid((index+0x0B80),4); //Total played time
memcpy(&ff7.slot[s].time,temp,4);

temp=ff7file.mid((index+0x0B84),16);
for (int z=0;z<16;z++)
{
ff7.slot[s].z_4[z] =temp.at(z);
}

temp=ff7file.mid((index+0x0B94),2);// Current map
memcpy(&ff7.slot[s].mapid,temp,2);
temp=ff7file.mid((index+0x0B96),2);
memcpy(&ff7.slot[s].locationid,temp,2);// Current location

temp=ff7file.mid((index+0x0B98),2);// Unknown
for(int z=0;z<2;z++)
{
   ff7.slot[s].z_5[z]=temp.at(z);
}

temp=ff7file.mid((index+0x0B9A),2);//x location world map
memcpy(&ff7.slot[s].coord.x,temp,2);
temp=ff7file.mid((index+0x0B9C),2);//y location world map
memcpy(&ff7.slot[s].coord.y,temp,2);
temp=ff7file.mid((index+0x0B9E),2);//z location world map
memcpy(&ff7.slot[s].coord.z,temp,2);

temp=ff7file.mid((index+0x0BA0),4);//Unknown related to map location and coords
for(int z=0;z<4;z++){ff7.slot[s].z_6[z]=temp.at(z);}

temp=ff7file.mid((index+0x0BA4),2);// man progress var
memcpy (&ff7.slot[s].mprogress,temp,2);

temp=ff7file.mid((index+0xBA6),1);
memcpy(&ff7.slot[s].unknown1,temp,1);


temp=ff7file.mid((index+0x0BA7)+0x00,1);
memcpy(&ff7.slot[s].love.aeris,temp,1);
temp=ff7file.mid((index+0x0BA7)+0x01,1);
memcpy(&ff7.slot[s].love.tifa,temp,1);
temp=ff7file.mid((index+0x0BA7)+0x02,1);
memcpy(&ff7.slot[s].love.yuffie,temp,1);
temp=ff7file.mid((index+0x0BA7)+0x03,1);
memcpy(&ff7.slot[s].love.barret,temp,1);

temp=ff7file.mid((index+0x0BAB),17);//Unknown
for(int z=0;z<17;z++){ff7.slot[s].z_7[z]=temp.at(z);}
temp=ff7file.mid((index+0x0BBC),2);//Number of battles fought
memcpy(&ff7.slot[s].battles,temp,2);
temp=ff7file.mid((index+0x0BBE),2);//Number of escapes
memcpy(&ff7.slot[s].runs,temp,2);
temp=ff7file.mid((index+0x0BC0),36);
for(int t=0;t<36;t++){ff7.slot[s].temp[t] = temp.at(t);}
temp=ff7file.mid((index+0x0BE4),8); //Key items
for(int k=0;k<8;k++){ff7.slot[s].keyitems[k] = temp.at(k);}
temp=ff7file.mid((index+0x0BEC),13);
for(int z=0;z<13;z++){ff7.slot[s].z_8[z] =temp.at(z);}
temp=ff7file.mid((index+0x0BF9),4);//Field Chocobo rating
for (int c=0;c<4;c++){ff7.slot[s].pennedchocos[c]=temp.at(c);}

temp=ff7file.mid((index+0x0BFD),136);
for (int z=0;z<128;z++){ff7.slot[s].z_9[z]= temp.at(z);}

temp= ff7file.mid ((index+0x0C85),1);
memcpy(&ff7.slot[s].bm_progress1,temp,1);

temp= ff7file.mid ((index+0x0C86),1);
memcpy(&ff7.slot[s].bm_progress2,temp,1);

temp= ff7file.mid((index+0x0C87),95);
for (int z=0;z<95;z++){ff7.slot[s].unknown2[z] = temp.at(z);}

temp= ff7file.mid ((index+0x0CE6),1);
memcpy(&ff7.slot[s].bm_progress3,temp,1);

temp=ff7file.mid((index+0x0CE7),7);
for (int z=0;z<7;z++){ff7.slot[s].unknown3[z] = temp.at(z);}


temp=ff7file.mid((index+0x0CEE),2); // Collect GP
memcpy(&ff7.slot[s].gp,temp,2);
temp=ff7file.mid((index+0x0CF0),12);
for (int z=0;z<12;z++){ff7.slot[s].z_10[z]=temp.at(z);}
temp=ff7file.mid((index+0x0CFC),1);
memcpy(&ff7.slot[s].stables,temp,1);
temp=ff7file.mid((index+0x0CFD),1);//Bug Fixed! Before was z_11 (Vegeta_Ss4) v0.8.3
memcpy(&ff7.slot[s].stablesoccupied,temp,1);
temp=ff7file.mid((index+0x0CFE),1);//Bug Fixed! Before was stablesoccupied (Vegeta_Ss4) v0.8.3
memcpy(&ff7.slot[s].z_11,temp,1);
temp=ff7file.mid((index+0x0CFF),1);// chocobomask.
memcpy(&ff7.slot[s].chocobomask,temp,1);
temp=ff7file.mid((index+0x0D00),1);
memcpy(&ff7.slot[s].chocoborn,temp,1);
temp=ff7file.mid((index+0x0D01),101);
for(int z=0;z<101;z++){ff7.slot[s].z_12[z]=temp.at(z);}
temp=ff7file.mid((index+0x0D66),1);
memcpy(&ff7.slot[s].turtleflyers,temp,1);
temp=ff7file.mid((index+0x0D67),93);
for(int z=0;z<93;z++){ff7.slot[s].temp2[z] = temp.at(z);}

for (int c=0;c<4;c++)// collect chocobo slots 1-4
{
temp2 = ff7file.mid((index+0x0DC4)+(c*16),16);
temp = temp2.mid (0x0,2);
memcpy(&ff7.slot[s].chocobos[c].sprintspd,temp,2);
temp = temp2.mid (0x2,2);
memcpy(&ff7.slot[s].chocobos[c].maxsprintspd,temp,2);
temp = temp2.mid (0x4,2);
memcpy(&ff7.slot[s].chocobos[c].speed,temp,2);
temp = temp2.mid (0x6,2);
memcpy(&ff7.slot[s].chocobos[c].maxspeed,temp,2);
temp = temp2.mid (0x8,1);
memcpy(&ff7.slot[s].chocobos[c].accel,temp,1);
temp = temp2.mid (0x9,1);
memcpy(&ff7.slot[s].chocobos[c].coop,temp,1);
temp = temp2.mid (0xA,1);
memcpy(&ff7.slot[s].chocobos[c].intelligence,temp,1);
temp = temp2.mid (0xB,1);
memcpy(&ff7.slot[s].chocobos[c].personality,temp,1);
temp = temp2.mid (0xC,1);
memcpy(&ff7.slot[s].chocobos[c].pcount,temp,1);
temp = temp2.mid (0xD,1);
memcpy(&ff7.slot[s].chocobos[c].raceswon,temp,1);
temp = temp2.mid (0xE,1);
memcpy(&ff7.slot[s].chocobos[c].sex,temp,1);
temp = temp2.mid (0xF,1);
memcpy(&ff7.slot[s].chocobos[c].type,temp,1);
}

temp = ff7file.mid((index+0x0E04),160);
for (int z=0;z<160;z++){ff7.slot[s].z_13[z]=temp.at(z);}

temp = ff7file.mid((index+0x0EA4),1);
memcpy(&ff7.slot[s].disc,temp,1);

temp = ff7file.mid((index+0x0EA5),31);
for (int z=0;z<31;z++){ff7.slot[s].z_14[z]=temp.at(z);}


for (int c=0;c<6;c++) //get chocobonames
{
   temp=ff7file.mid((index+0x0EC4)+(c*6),6);
   for (int o=0;o<6;o++){
       ff7.slot[s].chocobonames[c][o]= temp.at(o);
   }
}


// grab all the stamina values too
temp = ff7file.mid((index+0x0EE8),2);
memcpy(&ff7.slot[s].chocostaminas[0],temp,2);
temp = ff7file.mid((index+0x0EEA),2);
memcpy(&ff7.slot[s].chocostaminas[1],temp,2);
temp = ff7file.mid((index+0x0EEC),2);
memcpy(&ff7.slot[s].chocostaminas[2],temp,2);
temp = ff7file.mid((index+0x0EEE),2);
memcpy(&ff7.slot[s].chocostaminas[3],temp,2);
temp = ff7file.mid((index+0x0EF0),2);
memcpy(&ff7.slot[s].chocostaminas[4],temp,2);
temp = ff7file.mid((index+0x0EF2),2);
memcpy(&ff7.slot[s].chocostaminas[5],temp,2);


temp = ff7file.mid ((index+0x0EF4),400);
for(int z=0;z<400;z++){
   ff7.slot[s].z_17[z]=temp.at(z);

}


for (int c=4;c<6;c++)// collect chocobo slots 5-6
{
temp2 = ff7file.mid((index+0x1084)+((c-4)*16),16);
temp = temp2.mid (0x0,2);
memcpy(&ff7.slot[s].chocobos[c].sprintspd,temp,2);
temp = temp2.mid (0x2,2);
memcpy(&ff7.slot[s].chocobos[c].maxsprintspd,temp,2);
temp = temp2.mid (0x4,2);
memcpy(&ff7.slot[s].chocobos[c].speed,temp,2);
temp = temp2.mid (0x6,2);
memcpy(&ff7.slot[s].chocobos[c].maxspeed,temp,2);
temp = temp2.mid (0x8,1);
memcpy(&ff7.slot[s].chocobos[c].accel,temp,1);
temp = temp2.mid (0x9,1);
memcpy(&ff7.slot[s].chocobos[c].coop,temp,1);
temp = temp2.mid (0xA,1);
memcpy(&ff7.slot[s].chocobos[c].intelligence,temp,1);
temp = temp2.mid (0xB,1);
memcpy(&ff7.slot[s].chocobos[c].personality,temp,1);
temp = temp2.mid (0xC,1);
memcpy(&ff7.slot[s].chocobos[c].pcount,temp,1);
temp = temp2.mid (0xD,1);
memcpy(&ff7.slot[s].chocobos[c].raceswon,temp,1);
temp = temp2.mid (0xE,1);
memcpy(&ff7.slot[s].chocobos[c].sex,temp,1);
temp = temp2.mid (0xF,1);
memcpy(&ff7.slot[s].chocobos[c].type,temp,1);
}


temp = ff7file.mid((index+0x10A4),2);
memcpy(&ff7.slot[s].phsmask,temp,2);
temp = ff7file.mid((index+0x10A6),2);
memcpy(&ff7.slot[s].unlockedchars,temp,2);
temp = ff7file.mid((index+0x10A8),48);
for(int z=0;z<48;z++){ff7.slot[s].z_18[z] = temp.at(z);}
temp =ff7file.mid((index+0x10D8),1);
memcpy(&ff7.slot[s].battlespeed,temp,1);
temp =ff7file.mid((index+0x10D9),1);
memcpy(&ff7.slot[s].battlemspeed,temp,1);
temp=ff7file.mid((index+0x10DA),1);
memcpy(&ff7.slot[s].options1,temp,1);
temp=ff7file.mid((index+0x10DB),1);
memcpy(&ff7.slot[s].options2,temp,1);
temp = ff7file.mid((index+0x10DC),16);
for(int z=0;z<16;z++){ff7.slot[s].z_19[z] = temp.at(z);}
temp =ff7file.mid((index+0x10EC),1);
memcpy(&ff7.slot[s].fieldmspeed,temp,1);
temp = ff7file.mid((index+0x10ED),7);
for(int z=0;z<7;z++){ff7.slot[s].z_20[z] = temp.at(z);}


}//Parse slot data....
guirefresh();
}

void MainWindow::on_actionFrom_PSV_Slot_activated()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select Final Fantasy 7 PSV Save"),(""),tr("PSX FF7 SaveGame (*.psv)"));

    if (!fileName.isEmpty()){
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))
    {
            QMessageBox::warning(this, tr("Black Chocobo"),
                           tr("Cannot read file %1:\n%2.")
                            .arg(fileName)
                 .arg(file.errorString()));
    return;
}
QByteArray ff7file;
ff7file = file.readAll(); //put all data in temp raw file
QByteArray temp; // create a temp to be used when needed
// parse the save data... starting from the top...



int index = 0x284;


temp = ff7file.mid((index+0x0000),2); // collect checksum [first 2 bytes of save slot]
memcpy(&ff7.slot[s].checksum,temp,2);

temp = ff7file.mid((index+0x0002),2);//collect z_1 2 unknow bits if checksum !4bytes
memcpy(&ff7.slot[s].z_1,temp,2);

temp = ff7file.mid((index+0x0004),1);
memcpy(&ff7.slot[s].desc.level,temp,1); // collect description level

for (int p=0; p<3;p++){ff7.slot[s].desc.party[p] = ff7file.at(index +0x0005 +p);} //collect description party members [character's portrait]
for (int n=0;n<16;n++){ff7.slot[s].desc.name[n]  = ff7file.at(index +0x0008 +n);}//collect description name chPC[] [character's name]

temp = ff7file.mid((index+0x0018),2); // collect cur hp
memcpy(&ff7.slot[s].desc.curHP,temp,2);

temp = ff7file.mid((index+0x001A),2);// collect max hp
memcpy(&ff7.slot[s].desc.maxHP,temp,2);

temp = ff7file.mid((index+0x001C),2);// collect cur mp
memcpy(&ff7.slot[s].desc.curMP,temp,2);

temp = ff7file.mid((index+0x001E),2);// collect max mp
memcpy(&ff7.slot[s].desc.maxMP,temp,2);

temp =ff7file.mid((index+0x0020),4); // collect description gil amount
memcpy(&ff7.slot[s].desc.gil,temp,4);

temp =ff7file.mid((index+0x0024),4); //collect description time (in seconds)
memcpy(&ff7.slot[s].desc.time, temp,4);

for (int loc=0; loc<32;loc++){ff7.slot[s].desc.location[loc] = ff7file.at(index + 0x0028 + loc);}//collect descrition location ChPC[];

for(int c=0;c<4;c++){//collect color data...
    for (int cc=0;cc<3;cc++){
    temp =ff7file.mid((index+0x0048)+(3*c)+cc,1);
    memcpy(&ff7.slot[s].colors[c][cc],temp,1);
        }}

            QByteArray temp2;
   for(int who=0;who<9;who++){//PARSE CHAR DATA
    temp2 = ff7file.mid((index+0x0054)+(char_len*who),132);
    temp=temp2.mid(0x00 ,1);
    memcpy(&ff7.slot[s].chars[who].id, temp,1);

    temp=temp2.mid(0x01 ,1);
    memcpy(&ff7.slot[s].chars[who].level, temp,1);

    temp=temp2.mid(0x02 ,1);
    memcpy(&ff7.slot[s].chars[who].strength, temp,1);

    temp=temp2.mid(0x03 ,1);
    memcpy(&ff7.slot[s].chars[who].vitality, temp,1);

    temp=temp2.mid(0x04 ,1);
    memcpy(&ff7.slot[s].chars[who].magic, temp,1);

    temp=temp2.mid(0x05 ,1);
    memcpy(&ff7.slot[s].chars[who].spirit, temp,1);

    temp=temp2.mid(0x06 ,1);
    memcpy(&ff7.slot[s].chars[who].dexterity, temp,1);

    temp=temp2.mid(0x07 ,1);
    memcpy(&ff7.slot[s].chars[who].luck, temp,1);

    temp=temp2.mid(0x08,1);
    memcpy(&ff7.slot[s].chars[who].strength_bonus,temp,1);

    temp=temp2.mid(0x09,1);
    memcpy(&ff7.slot[s].chars[who].vitality_bonus,temp,1);

    temp=temp2.mid(0x0A,1);
    memcpy(&ff7.slot[s].chars[who].magic_bonus,temp,1);

    temp=temp2.mid(0x0B,1);
    memcpy(&ff7.slot[s].chars[who].spirit_bonus,temp,1);

    temp=temp2.mid(0x0C,1);
    memcpy(&ff7.slot[s].chars[who].dexterity_bonus,temp,1);

    temp=temp2.mid(0x0D,1);
    memcpy(&ff7.slot[s].chars[who].luck_bonus,temp,1);

    temp=temp2.mid(0x0E,1);
    memcpy(&ff7.slot[s].chars[who].limitlevel,temp,1);

    temp=temp2.mid(0x0F,1);
    memcpy(&ff7.slot[s].chars[who].limitbar,temp,1);

    temp=temp2.mid(0x10,12);
    for (int n=0;n<12;n++){ff7.slot[s].chars[who].name[n] = temp.at(n);}

    temp=temp2.mid(0x1C,1);
    memcpy(&ff7.slot[s].chars[who].weapon,temp,1);

    temp=temp2.mid(0x1D,1);
    memcpy(&ff7.slot[s].chars[who].armor,temp,1);

    temp=temp2.mid(0x1E,1);
    memcpy(&ff7.slot[s].chars[who].accessory,temp,1);

    temp=temp2.mid(0x1F,3);
    for (int f=0;f<3;f++){ff7.slot[s].chars[who].flags[f] = temp.at(f);}

    temp=temp2.mid(0x22,2);
    memcpy(&ff7.slot[s].chars[who].limits,temp,2);

    temp=temp2.mid(0x24,2);
    memcpy(&ff7.slot[s].chars[who].kills,temp,2);

    temp=temp2.mid(0x26,2);
    memcpy(&ff7.slot[s].chars[who].timesused1,temp,2);

    temp=temp2.mid(0x28,2);
    memcpy(&ff7.slot[s].chars[who].timesused2,temp,2);

    temp=temp2.mid(0x2A,2);
    memcpy(&ff7.slot[s].chars[who].timesused3,temp,2);

    temp=temp2.mid(0x2C,2);
    memcpy(&ff7.slot[s].chars[who].curHP,temp,2);

    temp=temp2.mid(0x2E,2);
    memcpy(&ff7.slot[s].chars[who].baseHP,temp,2);

    temp=temp2.mid(0x30,2);
    memcpy(&ff7.slot[s].chars[who].curMP,temp,2);

    temp=temp2.mid(0x32,2);
    memcpy(&ff7.slot[s].chars[who].baseMP,temp,2);

    temp=temp2.mid(0x34,4);
    for(int z4=0;z4<4;z4++){ff7.slot[s].chars[who].z_4[z4]=temp.at(z4);}

    temp=temp2.mid(0x38,2);
    memcpy(&ff7.slot[s].chars[who].maxHP,temp,2);

    temp=temp2.mid(0x3A,2);
    memcpy(&ff7.slot[s].chars[who].maxMP,temp,2);

    temp=temp2.mid(0x3C,4);
    memcpy(&ff7.slot[s].chars[who].exp,temp,4);

    for (int mat=0;mat<16;mat++){
      temp=temp2.mid(0x40 + 4*mat,1);
      memcpy(&ff7.slot[s].chars[who].materias[mat].id,temp,1);
      temp=temp2.mid(0x40+4*mat +1,3);
      for(int m=0;m<3;m++){ff7.slot[s].chars[who].materias[mat].ap[m]=temp.at(m);}
      }
   temp=temp2.mid(0x80,4);
   memcpy(&ff7.slot[s].chars[who].expNext,temp,4);
   }//END CHAR LOOPING
   for (int p=0;p<3;p++)
   {
       temp=ff7file.mid((index+0x04F8) +p,1);//Party member in slots 1,2,3
       memcpy(&ff7.slot[s].party[p],temp,1);
   }
temp=ff7file.mid((index+0x04FB),1);
memcpy(&ff7.slot[s].z_2,temp,1); //0xFF


for(int itm=0;itm<320;itm++) //Party item stock
{
    temp=ff7file.mid((index+0x04FC) + (2*itm),1);
    memcpy(&ff7.slot[s].items[itm].id,temp,1);
    temp=ff7file.mid((index+0x04FC) + (2*itm)+1,1);
    memcpy(&ff7.slot[s].items[itm].qty,temp,1);
}

for (int met=0;met<200;met++) //Party materia stock
{
    temp=ff7file.mid((index+0x077C) +(4*met),1);
    memcpy(&ff7.slot[s].materias[met].id,temp,1);
    temp=ff7file.mid((index+0x077C) +(4*met)+1,3);
    for (int ma=0;ma<3;ma++){ff7.slot[s].materias[met].ap[ma]=temp.at(ma);}
}
for (int met=0;met<48;met++) //Materia stolen by Yuffie
{
    temp=ff7file.mid((index+0x0A9C) +(4*met),1);
    memcpy(&ff7.slot[s].stolen[met].id,temp,1);
    temp=ff7file.mid((index+0x0A9C) +(4*met)+1,3);
    for (int ma=0;ma<3;ma++){ff7.slot[s].stolen[met].ap[ma]=temp.at(ma);}
}
temp=ff7file.mid((index+0x0B5C),32); //32 Bytes Unknown

for(int z=0;z<32;z++)//32 Bytes Unknown
{
ff7.slot[s].z_3[z] = temp.at(z);
}
temp=ff7file.mid((index+0x0B7C),4); // Collect Gil
memcpy(&ff7.slot[s].gil,temp,4);

temp=ff7file.mid((index+0x0B80),4); //Total played time
memcpy(&ff7.slot[s].time,temp,4);

temp=ff7file.mid((index+0x0B84),16);
for (int z=0;z<16;z++)
{
ff7.slot[s].z_4[z] =temp.at(z);
}

temp=ff7file.mid((index+0x0B94),2);// Current map
memcpy(&ff7.slot[s].mapid,temp,2);
temp=ff7file.mid((index+0x0B96),2);
memcpy(&ff7.slot[s].locationid,temp,2);// Current location

temp=ff7file.mid((index+0x0B98),2);// Unknown
for(int z=0;z<2;z++)
{
   ff7.slot[s].z_5[z]=temp.at(z);
}

temp=ff7file.mid((index+0x0B9A),2);//x location world map
memcpy(&ff7.slot[s].coord.x,temp,2);
temp=ff7file.mid((index+0x0B9C),2);//y location world map
memcpy(&ff7.slot[s].coord.y,temp,2);
temp=ff7file.mid((index+0x0B9E),2);//z location world map
memcpy(&ff7.slot[s].coord.z,temp,2);

temp=ff7file.mid((index+0x0BA0),4);//Unknown related to map location and coords
for(int z=0;z<4;z++){ff7.slot[s].z_6[z]=temp.at(z);}

temp=ff7file.mid((index+0x0BA4),2);// man progress var
memcpy (&ff7.slot[s].mprogress,temp,2);

temp=ff7file.mid((index+0xBA6),1);
memcpy(&ff7.slot[s].unknown1,temp,1);


temp=ff7file.mid((index+0x0BA7)+0x00,1);
memcpy(&ff7.slot[s].love.aeris,temp,1);
temp=ff7file.mid((index+0x0BA7)+0x01,1);
memcpy(&ff7.slot[s].love.tifa,temp,1);
temp=ff7file.mid((index+0x0BA7)+0x02,1);
memcpy(&ff7.slot[s].love.yuffie,temp,1);
temp=ff7file.mid((index+0x0BA7)+0x03,1);
memcpy(&ff7.slot[s].love.barret,temp,1);

temp=ff7file.mid((index+0x0BAB),17);//Unknown
for(int z=0;z<17;z++){ff7.slot[s].z_7[z]=temp.at(z);}
temp=ff7file.mid((index+0x0BBC),2);//Number of battles fought
memcpy(&ff7.slot[s].battles,temp,2);
temp=ff7file.mid((index+0x0BBE),2);//Number of escapes
memcpy(&ff7.slot[s].runs,temp,2);
temp=ff7file.mid((index+0x0BC0),36);
for(int t=0;t<36;t++){ff7.slot[s].temp[t] = temp.at(t);}
temp=ff7file.mid((index+0x0BE4),8); //Key items
for(int k=0;k<8;k++){ff7.slot[s].keyitems[k] = temp.at(k);}
temp=ff7file.mid((index+0x0BEC),13);
for(int z=0;z<13;z++){ff7.slot[s].z_8[z] =temp.at(z);}
temp=ff7file.mid((index+0x0BF9),4);//Field Chocobo rating
for (int c=0;c<4;c++){ff7.slot[s].pennedchocos[c]=temp.at(c);}

temp=ff7file.mid((index+0x0BFD),136);
for (int z=0;z<128;z++){ff7.slot[s].z_9[z]= temp.at(z);}

temp= ff7file.mid ((index+0x0C85),1);
memcpy(&ff7.slot[s].bm_progress1,temp,1);

temp= ff7file.mid ((index+0x0C86),1);
memcpy(&ff7.slot[s].bm_progress2,temp,1);

temp= ff7file.mid((index+0x0C87),95);
for (int z=0;z<95;z++){ff7.slot[s].unknown2[z] = temp.at(z);}

temp= ff7file.mid ((index+0x0CE6),1);
memcpy(&ff7.slot[s].bm_progress3,temp,1);

temp=ff7file.mid((index+0x0CE7),7);
for (int z=0;z<7;z++){ff7.slot[s].unknown3[z] = temp.at(z);}

temp=ff7file.mid((index+0x0CEE),2); // Collect GP
memcpy(&ff7.slot[s].gp,temp,2);
temp=ff7file.mid((index+0x0CF0),12);
for (int z=0;z<12;z++){ff7.slot[s].z_10[z]=temp.at(z);}
temp=ff7file.mid((index+0x0CFC),1);
memcpy(&ff7.slot[s].stables,temp,1);
temp=ff7file.mid((index+0x0CFD),1);//Bug Fixed! Before was z_11 (Vegeta_Ss4) v0.8.3
memcpy(&ff7.slot[s].stablesoccupied,temp,1);
temp=ff7file.mid((index+0x0CFE),1);//Bug Fixed! Before was stablesoccupied (Vegeta_Ss4) v0.8.3
memcpy(&ff7.slot[s].z_11,temp,1);
temp=ff7file.mid((index+0x0CFF),1);// chocobomask.
memcpy(&ff7.slot[s].chocobomask,temp,1);
temp=ff7file.mid((index+0x0D00),1);
memcpy(&ff7.slot[s].chocoborn,temp,1);
temp=ff7file.mid((index+0x0D01),101);
for(int z=0;z<101;z++){ff7.slot[s].z_12[z]=temp.at(z);}
temp=ff7file.mid((index+0x0D66),1);
memcpy(&ff7.slot[s].turtleflyers,temp,1);
temp=ff7file.mid((index+0x0D67),93);
for(int z=0;z<93;z++){ff7.slot[s].temp2[z] = temp.at(z);}

for (int c=0;c<4;c++)// collect chocobo slots 1-4
{
temp2 = ff7file.mid((index+0x0DC4)+(c*16),16);
temp = temp2.mid (0x0,2);
memcpy(&ff7.slot[s].chocobos[c].sprintspd,temp,2);
temp = temp2.mid (0x2,2);
memcpy(&ff7.slot[s].chocobos[c].maxsprintspd,temp,2);
temp = temp2.mid (0x4,2);
memcpy(&ff7.slot[s].chocobos[c].speed,temp,2);
temp = temp2.mid (0x6,2);
memcpy(&ff7.slot[s].chocobos[c].maxspeed,temp,2);
temp = temp2.mid (0x8,1);
memcpy(&ff7.slot[s].chocobos[c].accel,temp,1);
temp = temp2.mid (0x9,1);
memcpy(&ff7.slot[s].chocobos[c].coop,temp,1);
temp = temp2.mid (0xA,1);
memcpy(&ff7.slot[s].chocobos[c].intelligence,temp,1);
temp = temp2.mid (0xB,1);
memcpy(&ff7.slot[s].chocobos[c].personality,temp,1);
temp = temp2.mid (0xC,1);
memcpy(&ff7.slot[s].chocobos[c].pcount,temp,1);
temp = temp2.mid (0xD,1);
memcpy(&ff7.slot[s].chocobos[c].raceswon,temp,1);
temp = temp2.mid (0xE,1);
memcpy(&ff7.slot[s].chocobos[c].sex,temp,1);
temp = temp2.mid (0xF,1);
memcpy(&ff7.slot[s].chocobos[c].type,temp,1);
}

temp = ff7file.mid((index+0x0E04),160);
for (int z=0;z<160;z++){ff7.slot[s].z_13[z]=temp.at(z);}

temp = ff7file.mid((index+0x0EA4),1);
memcpy(&ff7.slot[s].disc,temp,1);

temp = ff7file.mid((index+0x0EA5),31);
for (int z=0;z<31;z++){ff7.slot[s].z_14[z]=temp.at(z);}


for (int c=0;c<6;c++) //get chocobonames
{
   temp=ff7file.mid((index+0x0EC4)+(c*6),6);
   for (int o=0;o<6;o++){
       ff7.slot[s].chocobonames[c][o]= temp.at(o);
   }
}


// grab all the stamina values too
temp = ff7file.mid((index+0x0EE8),2);
memcpy(&ff7.slot[s].chocostaminas[0],temp,2);
temp = ff7file.mid((index+0x0EEA),2);
memcpy(&ff7.slot[s].chocostaminas[1],temp,2);
temp = ff7file.mid((index+0x0EEC),2);
memcpy(&ff7.slot[s].chocostaminas[2],temp,2);
temp = ff7file.mid((index+0x0EEE),2);
memcpy(&ff7.slot[s].chocostaminas[3],temp,2);
temp = ff7file.mid((index+0x0EF0),2);
memcpy(&ff7.slot[s].chocostaminas[4],temp,2);
temp = ff7file.mid((index+0x0EF2),2);
memcpy(&ff7.slot[s].chocostaminas[5],temp,2);


temp = ff7file.mid ((index+0x0EF4),400);
for(int z=0;z<400;z++){
   ff7.slot[s].z_17[z]=temp.at(z);

}


for (int c=4;c<6;c++)// collect chocobo slots 5-6
{
temp2 = ff7file.mid((index+0x1084)+((c-4)*16),16);
temp = temp2.mid (0x0,2);
memcpy(&ff7.slot[s].chocobos[c].sprintspd,temp,2);
temp = temp2.mid (0x2,2);
memcpy(&ff7.slot[s].chocobos[c].maxsprintspd,temp,2);
temp = temp2.mid (0x4,2);
memcpy(&ff7.slot[s].chocobos[c].speed,temp,2);
temp = temp2.mid (0x6,2);
memcpy(&ff7.slot[s].chocobos[c].maxspeed,temp,2);
temp = temp2.mid (0x8,1);
memcpy(&ff7.slot[s].chocobos[c].accel,temp,1);
temp = temp2.mid (0x9,1);
memcpy(&ff7.slot[s].chocobos[c].coop,temp,1);
temp = temp2.mid (0xA,1);
memcpy(&ff7.slot[s].chocobos[c].intelligence,temp,1);
temp = temp2.mid (0xB,1);
memcpy(&ff7.slot[s].chocobos[c].personality,temp,1);
temp = temp2.mid (0xC,1);
memcpy(&ff7.slot[s].chocobos[c].pcount,temp,1);
temp = temp2.mid (0xD,1);
memcpy(&ff7.slot[s].chocobos[c].raceswon,temp,1);
temp = temp2.mid (0xE,1);
memcpy(&ff7.slot[s].chocobos[c].sex,temp,1);
temp = temp2.mid (0xF,1);
memcpy(&ff7.slot[s].chocobos[c].type,temp,1);
}


temp = ff7file.mid((index+0x10A4),2);
memcpy(&ff7.slot[s].phsmask,temp,2);
temp = ff7file.mid((index+0x10A6),2);
memcpy(&ff7.slot[s].unlockedchars,temp,2);
temp = ff7file.mid((index+0x10A8),48);
for(int z=0;z<48;z++){ff7.slot[s].z_18[z] = temp.at(z);}
temp =ff7file.mid((index+0x10D8),1);
memcpy(&ff7.slot[s].battlespeed,temp,1);
temp =ff7file.mid((index+0x10D9),1);
memcpy(&ff7.slot[s].battlemspeed,temp,1);
temp=ff7file.mid((index+0x10DA),1);
memcpy(&ff7.slot[s].options1,temp,1);
temp=ff7file.mid((index+0x10DB),1);
memcpy(&ff7.slot[s].options2,temp,1);
temp = ff7file.mid((index+0x10DC),16);
for(int z=0;z<16;z++){ff7.slot[s].z_19[z] = temp.at(z);}
temp =ff7file.mid((index+0x10EC),1);
memcpy(&ff7.slot[s].fieldmspeed,temp,1);
temp = ff7file.mid((index+0x10ED),7);
for(int z=0;z<7;z++){ff7.slot[s].z_20[z] = temp.at(z);}


}//Parse slot data....
guirefresh();
}

void MainWindow::on_actionCopy_Slot_activated()
{

    bufferslot.checksum = ff7.slot[s].checksum;
    bufferslot.z_1 = ff7.slot[s].z_1;

    bufferslot.desc.level =ff7.slot[s].desc.level;

    for (int p=0; p<3;p++){bufferslot.desc.party[p]=ff7.slot[s].desc.party[p];}
    for (int n=0;n<16;n++){bufferslot.desc.name[n]=ff7.slot[s].desc.name[n];}


    bufferslot.desc.curHP = ff7.slot[s].desc.curHP;
    bufferslot.desc.maxHP = ff7.slot[s].desc.maxHP;
    bufferslot.desc.curMP = ff7.slot[s].desc.curMP;
    bufferslot.desc.maxMP = ff7.slot[s].desc.maxMP;


    bufferslot.desc.gil = ff7.slot[s].desc.gil;
    bufferslot.desc.time = ff7.slot[s].desc.time;

    for (int loc=0; loc<32;loc++){bufferslot.desc.location[loc] = ff7.slot[s].desc.location[loc];}

    for(int c=0;c<4;c++){//collect color data...
        for (int cc=0;cc<3;cc++){

        bufferslot.colors[c][cc] = ff7.slot[s].colors[c][cc];
            }}


       for(int who=0;who<9;who++){//PARSE CHAR DATA


        bufferslot.chars[who].id = ff7.slot[s].chars[who].id;
        bufferslot.chars[who].level = ff7.slot[s].chars[who].level;
        bufferslot.chars[who].strength = ff7.slot[s].chars[who].strength;
        bufferslot.chars[who].vitality = ff7.slot[s].chars[who].vitality;
        bufferslot.chars[who].magic = ff7.slot[s].chars[who].magic;
        bufferslot.chars[who].spirit = ff7.slot[s].chars[who].spirit;
        bufferslot.chars[who].dexterity = ff7.slot[s].chars[who].dexterity;
        bufferslot.chars[who].luck = ff7.slot[s].chars[who].luck;
        bufferslot.chars[who].strength_bonus = ff7.slot[s].chars[who].strength_bonus;
        bufferslot.chars[who].vitality_bonus = ff7.slot[s].chars[who].vitality_bonus;
        bufferslot.chars[who].magic_bonus = ff7.slot[s].chars[who].magic_bonus;
        bufferslot.chars[who].spirit_bonus = ff7.slot[s].chars[who].spirit_bonus;
        bufferslot.chars[who].dexterity_bonus = ff7.slot[s].chars[who].dexterity_bonus;
        bufferslot.chars[who].luck_bonus = ff7.slot[s].chars[who].luck_bonus;
        bufferslot.chars[who].limitlevel = ff7.slot[s].chars[who].limitlevel;
        bufferslot.chars[who].limitbar = ff7.slot[s].chars[who].limitbar;


        for (int n=0;n<12;n++){bufferslot.chars[who].name[n] = ff7.slot[s].chars[who].name[n];}


        bufferslot.chars[who].weapon = ff7.slot[s].chars[who].weapon;
        bufferslot.chars[who].armor = ff7.slot[s].chars[who].armor;
        bufferslot.chars[who].accessory = ff7.slot[s].chars[who].accessory;


        for (int f=0;f<3;f++){bufferslot.chars[who].flags[f] = ff7.slot[s].chars[who].flags[f];}


        bufferslot.chars[who].limits = ff7.slot[s].chars[who].limits;
        bufferslot.chars[who].kills = ff7.slot[s].chars[who].kills;
        bufferslot.chars[who].timesused1 = ff7.slot[s].chars[who].timesused1;
        bufferslot.chars[who].timesused2 = ff7.slot[s].chars[who].timesused2;
        bufferslot.chars[who].timesused3 = ff7.slot[s].chars[who].timesused3;
        bufferslot.chars[who].curHP = ff7.slot[s].chars[who].curHP;
        bufferslot.chars[who].baseHP = ff7.slot[s].chars[who].baseHP;
        bufferslot.chars[who].curMP = ff7.slot[s].chars[who].curMP;

        bufferslot.chars[who].baseMP = ff7.slot[s].chars[who].baseMP;


        for(int z4=0;z4<4;z4++){bufferslot.chars[who].z_4[z4] = ff7.slot[s].chars[who].z_4[z4];}

        bufferslot.chars[who].maxHP =ff7.slot[s].chars[who].maxHP;
        bufferslot.chars[who].maxMP =ff7.slot[s].chars[who].maxMP;


        bufferslot.chars[who].exp = ff7.slot[s].chars[who].exp;

        for (int mat=0;mat<16;mat++){

          bufferslot.chars[who].materias[mat].id = ff7.slot[s].chars[who].materias[mat].id;
          for(int m=0;m<3;m++){bufferslot.chars[who].materias[mat].ap[m] = ff7.slot[s].chars[who].materias[mat].ap[m];}
          }
       bufferslot.chars[who].expNext = ff7.slot[s].chars[who].expNext;
       }//END CHAR LOOPING
       for (int p=0;p<3;p++)
       {

          bufferslot.party[p] =ff7.slot[s].party[p];
       }

    bufferslot.z_2 = ff7.slot[s].z_2; //0xFF


    for(int itm=0;itm<320;itm++) //Party item stock
    {

        bufferslot.items[itm].id = ff7.slot[s].items[itm].id;

        bufferslot.items[itm].qty = ff7.slot[s].items[itm].qty;
    }

    for (int met=0;met<200;met++) //Party materia stock
    {

        bufferslot.materias[met].id =ff7.slot[s].materias[met].id;

        for (int ma=0;ma<3;ma++){bufferslot.materias[met].ap[ma] = ff7.slot[s].materias[met].ap[ma];}
    }
    for (int met=0;met<48;met++) //Materia stolen by Yuffie
    {

        bufferslot.stolen[met].id = ff7.slot[s].stolen[met].id;

        for (int ma=0;ma<3;ma++){bufferslot.stolen[met].ap[ma] = ff7.slot[s].stolen[met].ap[ma];}
    }

    for(int z=0;z<32;z++)//32 Bytes Unknown
    {
    bufferslot.z_3[z] = ff7.slot[s].z_3[z];
    }


    bufferslot.gil = ff7.slot[s].gil;
    bufferslot.time = ff7.slot[s].time;

    for (int z=0;z<16;z++)
    {
    bufferslot.z_4[z] = ff7.slot[s].z_4[z];
    }


    bufferslot.mapid = ff7.slot[s].mapid;
    bufferslot.locationid = ff7.slot[s].locationid;// Current location

;// Unknown
    for(int z=0;z<2;z++)
    {
       bufferslot.z_5[z] = ff7.slot[s].z_5[z];
    }

    bufferslot.coord.x = ff7.slot[s].coord.x;
    bufferslot.coord.y = ff7.slot[s].coord.y;
    bufferslot.coord.z = ff7.slot[s].coord.z;

    for(int z=0;z<4;z++){bufferslot.z_6[z] = ff7.slot[s].z_6[z];}
    bufferslot.mprogress= ff7.slot[s].mprogress;
    bufferslot.unknown1 = ff7.slot[s].unknown1;

    bufferslot.love.aeris = ff7.slot[s].love.aeris;
    bufferslot.love.tifa = ff7.slot[s].love.tifa;
    bufferslot.love.yuffie = ff7.slot[s].love.yuffie;
    bufferslot.love.barret = ff7.slot[s].love.barret;

    for(int z=0;z<17;z++){bufferslot.z_7[z] = ff7.slot[s].z_7[z];}


    bufferslot.battles=ff7.slot[s].battles;
    bufferslot.runs=ff7.slot[s].runs;

    for(int t=0;t<36;t++){bufferslot.temp[t] = ff7.slot[s].temp[t];}

    for(int k=0;k<8;k++){bufferslot.keyitems[k] = ff7.slot[s].keyitems[k];}

    for(int z=0;z<13;z++){bufferslot.z_8[z] = ff7.slot[s].z_8[z];}

    for (int c=0;c<4;c++){bufferslot.pennedchocos[c] = ff7.slot[s].pennedchocos[c];}

    for (int z=0;z<136;z++){bufferslot.z_9[z]=ff7.slot[s].z_9[z];}
    bufferslot.bm_progress1 = ff7.slot[s].bm_progress1;
    bufferslot.bm_progress2 = ff7.slot[s].bm_progress2;
    for (int z=0;z<95;z++){bufferslot.unknown2[z]= ff7.slot[s].unknown2[z];}
    bufferslot.bm_progress3 = ff7.slot[s].bm_progress3;
    for (int z=0;z<7;z++){bufferslot.unknown3[z] = ff7.slot[s].unknown3[z];}

    bufferslot.gp = ff7.slot[s].gp;

    for (int z=0;z<12;z++){bufferslot.z_10[z] =ff7.slot[s].z_10[z];}

    bufferslot.stables = ff7.slot[s].stables;
    bufferslot.stablesoccupied = ff7.slot[s].stablesoccupied;
    bufferslot.z_11=ff7.slot[s].z_11;
    bufferslot.chocobomask = ff7.slot[s].chocobomask;
    bufferslot.chocoborn = ff7.slot[s].chocoborn;

    for(int z=0;z<101;z++){ff7.slot[s].z_12[z]=0x00;}

    bufferslot.turtleflyers = ff7.slot[s].turtleflyers;

    for(int z=0;z<93;z++){bufferslot.temp2[z] = ff7.slot[s].temp2[z];}

    for (int c=0;c<6;c++)// collect chocobo slots 1-4
    {

    bufferslot.chocobos[c].sprintspd =ff7.slot[s].chocobos[c].sprintspd;
    bufferslot.chocobos[c].maxsprintspd =ff7.slot[s].chocobos[c].maxsprintspd;
    bufferslot.chocobos[c].speed =ff7.slot[s].chocobos[c].speed;
    bufferslot.chocobos[c].maxspeed =ff7.slot[s].chocobos[c].maxspeed;

    bufferslot.chocobos[c].accel =ff7.slot[s].chocobos[c].accel;
    bufferslot.chocobos[c].coop =ff7.slot[s].chocobos[c].coop;
    bufferslot.chocobos[c].intelligence =ff7.slot[s].chocobos[c].intelligence;
    bufferslot.chocobos[c].personality =ff7.slot[s].chocobos[c].personality;
    bufferslot.chocobos[c].pcount =ff7.slot[s].chocobos[c].pcount;
    bufferslot.chocobos[c].raceswon =ff7.slot[s].chocobos[c].raceswon;
    bufferslot.chocobos[c].sex =ff7.slot[s].chocobos[c].sex;
    bufferslot.chocobos[c].type =ff7.slot[s].chocobos[c].type;
    }


    for (int z=0;z<160;z++){bufferslot.z_13[z]= ff7.slot[s].z_13[z];}


    bufferslot.disc = ff7.slot[s].disc;


    for (int z=0;z<31;z++){bufferslot.z_14[z] = ff7.slot[s].z_14[z];}


    for (int c=0;c<6;c++) //get chocobonames
    {

       for (int o=0;o<6;o++)
       {
          bufferslot.chocobonames[c][o] = ff7.slot[s].chocobonames[c][o];
       }
    }

    bufferslot.chocostaminas[0] = ff7.slot[s].chocostaminas[0];
    bufferslot.chocostaminas[1]= ff7.slot[s].chocostaminas[1];
    bufferslot.chocostaminas[2]= ff7.slot[s].chocostaminas[2];
    bufferslot.chocostaminas[3]= ff7.slot[s].chocostaminas[3];
    bufferslot.chocostaminas[4]= ff7.slot[s].chocostaminas[4];
    bufferslot.chocostaminas[5]= ff7.slot[s].chocostaminas[5];

    for(int z=0;z<400;z++){bufferslot.z_17[z] = ff7.slot[s].z_17[z];}




    bufferslot.phsmask=ff7.slot[s].phsmask;
    bufferslot.unlockedchars=ff7.slot[s].unlockedchars;

    for(int z=0;z<48;z++){bufferslot.z_18[z]= ff7.slot[s].z_18[z];}

    bufferslot.battlespeed =ff7.slot[s].battlespeed;
    bufferslot.battlemspeed=ff7.slot[s].battlemspeed;
    bufferslot.options1=ff7.slot[s].options1;
    bufferslot.options2=ff7.slot[s].options2;

    for(int z=0;z<16;z++){bufferslot.z_19[z] = ff7.slot[s].z_19[z];}
    bufferslot.fieldmspeed = ff7.slot[s].fieldmspeed;

    for(int z=0;z<7;z++){bufferslot.z_20[z] = ff7.slot[s].z_20[z];}
}

void MainWindow::clearslot(int rmslot)
{
    QByteArray temp;

    temp = 0x00; // set temp to 1 byte, and clear all 1 byte vars.
    memcpy(&ff7.slot[rmslot].desc.level,temp,1);
    memcpy(&ff7.slot[rmslot].z_2,temp,1); //0xFF
    memcpy(&ff7.slot[rmslot].unknown1,temp,1);
    memcpy(&ff7.slot[rmslot].love.aeris,temp,1);
    memcpy(&ff7.slot[rmslot].love.tifa,temp,1);
    memcpy(&ff7.slot[rmslot].love.yuffie,temp,1);
    memcpy(&ff7.slot[rmslot].love.barret,temp,1);
    memcpy(&ff7.slot[rmslot].bm_progress1,temp,1);
    memcpy(&ff7.slot[rmslot].bm_progress2,temp,1);
    memcpy(&ff7.slot[rmslot].bm_progress3,temp,1);
    memcpy(&ff7.slot[rmslot].stables,temp,1);
    memcpy(&ff7.slot[rmslot].stablesoccupied,temp,1);
    memcpy(&ff7.slot[rmslot].z_11,temp,1);
    memcpy(&ff7.slot[rmslot].chocobomask,temp,1);
    memcpy(&ff7.slot[rmslot].chocoborn,temp,1);
    memcpy(&ff7.slot[rmslot].turtleflyers,temp,1);
    memcpy(&ff7.slot[rmslot].disc,temp,1);
    memcpy(&ff7.slot[rmslot].battlespeed,temp,1);
    memcpy(&ff7.slot[rmslot].battlemspeed,temp,1);
    memcpy(&ff7.slot[rmslot].options1,temp,1);
    memcpy(&ff7.slot[rmslot].options2,temp,1);
    memcpy(&ff7.slot[rmslot].fieldmspeed,temp,1);

    temp = 0x0000; //set temp to 2byte and clear all 2 byte vars.
    memcpy(&ff7.slot[rmslot].mprogress,temp,2); // clear main progress.
    memcpy(&ff7.slot[rmslot].checksum,temp,2);
    memcpy(&ff7.slot[rmslot].z_1,temp,2);
    memcpy(&ff7.slot[rmslot].desc.curHP,temp,2);
    memcpy(&ff7.slot[rmslot].desc.maxHP,temp,2);
    memcpy(&ff7.slot[rmslot].desc.curMP,temp,2);
    memcpy(&ff7.slot[rmslot].desc.maxMP,temp,2);
    memcpy(&ff7.slot[rmslot].mapid,temp,2);
    memcpy(&ff7.slot[rmslot].locationid,temp,2);
    memcpy(&ff7.slot[rmslot].coord.x,temp,2);
    memcpy(&ff7.slot[rmslot].coord.y,temp,2);
    memcpy(&ff7.slot[rmslot].coord.z,temp,2);
    memcpy(&ff7.slot[rmslot].battles,temp,2);
    memcpy(&ff7.slot[rmslot].runs,temp,2);
    memcpy(&ff7.slot[rmslot].gp,temp,2);
    memcpy(&ff7.slot[rmslot].phsmask,temp,2);
    memcpy(&ff7.slot[rmslot].unlockedchars,temp,2);

    temp = 0x00000000; //set temp to 4 byte clear all 4 byte vars.
    memcpy(&ff7.slot[rmslot].desc.gil,temp,4);
    memcpy(&ff7.slot[rmslot].desc.time, temp,4);
    memcpy(&ff7.slot[rmslot].gil,temp,4);
    memcpy(&ff7.slot[rmslot].time,temp,4);

    // clear arrays
    for(int c=0;c<6;c++){ff7.slot[rmslot].chocostaminas[c]=0x0000;}
    for(int p=0; p<3;p++){ff7.slot[rmslot].desc.party[p]=0x00;}
    for(int n=0;n<16;n++){ff7.slot[rmslot].desc.name[n]=0x00;}
    for(int loc=0; loc<32;loc++){ff7.slot[rmslot].desc.location[loc] = 0x00;}
    for(int c=0;c<4;c++){for (int cc=0;cc<3;cc++){ff7.slot[rmslot].colors[c][cc]=0x00;}}
    for(int z=0;z<32;z++){ff7.slot[rmslot].z_3[z] = 0x00;}
    for(int z=0;z<16;z++){ff7.slot[rmslot].z_4[z] =0x00;}
    for(int z=0;z<2;z++){ff7.slot[rmslot].z_5[z]=0x00;}
    for(int z=0;z<4;z++){ff7.slot[rmslot].z_6[z]=0x00;}
    for(int z=0;z<17;z++){ff7.slot[rmslot].z_7[z]=0x00;}
    for(int t=0;t<36;t++){ff7.slot[rmslot].temp[t] = 0x00;}
    for(int k=0;k<8;k++){ff7.slot[rmslot].keyitems[k] = 0x00;}
    for(int z=0;z<13;z++){ff7.slot[rmslot].z_8[z] =0x00;}
    for(int c=0;c<4;c++){ff7.slot[rmslot].pennedchocos[c]=0x00;}
    for(int z=0;z<136;z++){ff7.slot[rmslot].z_9[z]= 0x00;}
    for(int z=0;z<95;z++){ff7.slot[rmslot].unknown2[z]= 0x00;}
    for(int z=0;z<7;z++){ff7.slot[rmslot].unknown3[z]= 0x00;}
    for(int z=0;z<12;z++){ff7.slot[rmslot].z_10[z]=0x00;}
    for(int z=0;z<101;z++){ff7.slot[rmslot].z_12[z]=0x00;}
    for(int z=0;z<93;z++){ff7.slot[rmslot].temp2[z] = 0x00;}
    for(int z=0;z<160;z++){ff7.slot[rmslot].z_13[z]=0x00;}
    for(int z=0;z<31;z++){ff7.slot[rmslot].z_14[z]=0x00;}
    for(int c=0;c<6;c++){for (int o=0;o<6;o++){ff7.slot[rmslot].chocobonames[c][o]= 0x00;}}
    for(int z=0;z<400;z++){ff7.slot[rmslot].z_17[z]=0x00;}
    for(int z=0;z<48;z++){ff7.slot[rmslot].z_18[z] = 0x00;}
    for(int z=0;z<16;z++){ff7.slot[rmslot].z_19[z] = 0x00;}
    for(int z=0;z<7;z++){ff7.slot[rmslot].z_20[z] = 0x00;}
    for(int p=0;p<3;p++){ff7.slot[rmslot].party[p]=0x00;}

    //clear structs.
    for(int who=0;who<9;who++){//Clear Chars
    temp = 0x00;
        memcpy(&ff7.slot[rmslot].chars[who].id, temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].level, temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].strength, temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].vitality, temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].magic, temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].spirit, temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].dexterity, temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].luck, temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].strength_bonus,temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].vitality_bonus,temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].magic_bonus,temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].spirit_bonus,temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].dexterity_bonus,temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].luck_bonus,temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].limitlevel,temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].limitbar,temp,1);


        for (int n=0;n<12;n++){ff7.slot[rmslot].chars[who].name[n] = 0x00;}


        memcpy(&ff7.slot[rmslot].chars[who].weapon,temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].armor,temp,1);
        memcpy(&ff7.slot[rmslot].chars[who].accessory,temp,1);


        for (int f=0;f<3;f++){ff7.slot[rmslot].chars[who].flags[f] = 0x00;}

        temp=0x0000;
        memcpy(&ff7.slot[rmslot].chars[who].limits,temp,2);
        memcpy(&ff7.slot[rmslot].chars[who].kills,temp,2);
        memcpy(&ff7.slot[rmslot].chars[who].timesused1,temp,2);
        memcpy(&ff7.slot[rmslot].chars[who].timesused2,temp,2);
        memcpy(&ff7.slot[rmslot].chars[who].timesused3,temp,2);
        memcpy(&ff7.slot[rmslot].chars[who].curHP,temp,2);
        memcpy(&ff7.slot[rmslot].chars[who].baseHP,temp,2);
        memcpy(&ff7.slot[rmslot].chars[who].curMP,temp,2);
        memcpy(&ff7.slot[rmslot].chars[who].baseMP,temp,2);


        for(int z4=0;z4<4;z4++){ff7.slot[rmslot].chars[who].z_4[z4]=0x00;}

        memcpy(&ff7.slot[rmslot].chars[who].maxHP,temp,2);
        memcpy(&ff7.slot[rmslot].chars[who].maxMP,temp,2);

        temp=0x00000000;
        memcpy(&ff7.slot[rmslot].chars[who].exp,temp,4);

        for (int mat=0;mat<16;mat++){
          temp=0x00;
          memcpy(&ff7.slot[rmslot].chars[who].materias[mat].id,temp,1);
          for(int m=0;m<3;m++){ff7.slot[rmslot].chars[who].materias[mat].ap[m]=0x00;}
          }
       memcpy(&ff7.slot[rmslot].chars[who].expNext,temp,4);}
    for(int itm=0;itm<320;itm++) //Party item stock
    {
        ff7.slot[rmslot].items[itm].id =0x00;
        ff7.slot[rmslot].items[itm].qty=0x00;
    }
    for(int met=0;met<200;met++) //Party materia stock
    {
        temp=0x00;
        memcpy(&ff7.slot[rmslot].materias[met].id,temp,1);
        temp=0x000000;
        for (int ma=0;ma<3;ma++){ff7.slot[rmslot].materias[met].ap[ma]=temp.at(ma);}
    }
    for(int met=0;met<48;met++) //Materia stolen by Yuffie
    {
        temp=0x00;
        memcpy(&ff7.slot[rmslot].stolen[met].id,temp,1);
        temp=0x000000;
        for (int ma=0;ma<3;ma++){ff7.slot[rmslot].stolen[met].ap[ma]=temp.at(ma);}
    }
    for(int c=0;c<6;c++)// clear chocobo slots
    {
    temp=0x0000;
    memcpy(&ff7.slot[rmslot].chocobos[c].sprintspd,temp,2);
    memcpy(&ff7.slot[rmslot].chocobos[c].maxsprintspd,temp,2);
    memcpy(&ff7.slot[rmslot].chocobos[c].speed,temp,2);
    memcpy(&ff7.slot[rmslot].chocobos[c].maxspeed,temp,2);
    temp=0x00;
    memcpy(&ff7.slot[rmslot].chocobos[c].accel,temp,1);
    memcpy(&ff7.slot[rmslot].chocobos[c].coop,temp,1);
    memcpy(&ff7.slot[rmslot].chocobos[c].intelligence,temp,1);
    memcpy(&ff7.slot[rmslot].chocobos[c].personality,temp,1);
    memcpy(&ff7.slot[rmslot].chocobos[c].pcount,temp,1);
    memcpy(&ff7.slot[rmslot].chocobos[c].raceswon,temp,1);
    memcpy(&ff7.slot[rmslot].chocobos[c].sex,temp,1);
    memcpy(&ff7.slot[rmslot].chocobos[c].type,temp,1);
    }

}

void MainWindow::on_actionPaste_Slot_activated()
{

    ff7.slot[s].checksum = bufferslot.checksum;
    ff7.slot[s].z_1 = bufferslot.z_1;

    ff7.slot[s].desc.level =bufferslot.desc.level;

    for (int p=0; p<3;p++){ff7.slot[s].desc.party[p]=bufferslot.desc.party[p];}
    for (int n=0;n<16;n++){ff7.slot[s].desc.name[n]=bufferslot.desc.name[n];}


    ff7.slot[s].desc.curHP = bufferslot.desc.curHP;
    ff7.slot[s].desc.maxHP = bufferslot.desc.maxHP;
    ff7.slot[s].desc.curMP = bufferslot.desc.curMP;
    ff7.slot[s].desc.maxMP = bufferslot.desc.maxMP;


    ff7.slot[s].desc.gil = bufferslot.desc.gil;
    ff7.slot[s].desc.time = bufferslot.desc.time;

    for (int loc=0; loc<32;loc++){ff7.slot[s].desc.location[loc] = bufferslot.desc.location[loc];}

    for(int c=0;c<4;c++){//collect color data...
        for (int cc=0;cc<3;cc++){

        ff7.slot[s].colors[c][cc] = bufferslot.colors[c][cc];
            }}


       for(int who=0;who<9;who++){//PARSE CHAR DATA


        ff7.slot[s].chars[who].id = bufferslot.chars[who].id;
        ff7.slot[s].chars[who].level = bufferslot.chars[who].level;
        ff7.slot[s].chars[who].strength = bufferslot.chars[who].strength;
        ff7.slot[s].chars[who].vitality = bufferslot.chars[who].vitality;
        ff7.slot[s].chars[who].magic = bufferslot.chars[who].magic;
        ff7.slot[s].chars[who].spirit = bufferslot.chars[who].spirit;
        ff7.slot[s].chars[who].dexterity = bufferslot.chars[who].dexterity;
        ff7.slot[s].chars[who].luck = bufferslot.chars[who].luck;
        ff7.slot[s].chars[who].strength_bonus = bufferslot.chars[who].strength_bonus;
        ff7.slot[s].chars[who].vitality_bonus = bufferslot.chars[who].vitality_bonus;
        ff7.slot[s].chars[who].magic_bonus = bufferslot.chars[who].magic_bonus;
        ff7.slot[s].chars[who].spirit_bonus = bufferslot.chars[who].spirit_bonus;
        ff7.slot[s].chars[who].dexterity_bonus = bufferslot.chars[who].dexterity_bonus;
        ff7.slot[s].chars[who].luck_bonus = bufferslot.chars[who].luck_bonus;
        ff7.slot[s].chars[who].limitlevel = bufferslot.chars[who].limitlevel;
        ff7.slot[s].chars[who].limitbar = bufferslot.chars[who].limitbar;


        for (int n=0;n<12;n++){ff7.slot[s].chars[who].name[n] = bufferslot.chars[who].name[n];}


        ff7.slot[s].chars[who].weapon = bufferslot.chars[who].weapon;
        ff7.slot[s].chars[who].armor = bufferslot.chars[who].armor;
        ff7.slot[s].chars[who].accessory = bufferslot.chars[who].accessory;


        for (int f=0;f<3;f++){ff7.slot[s].chars[who].flags[f] = bufferslot.chars[who].flags[f];}


        ff7.slot[s].chars[who].limits = bufferslot.chars[who].limits;
        ff7.slot[s].chars[who].kills = bufferslot.chars[who].kills;
        ff7.slot[s].chars[who].timesused1 = bufferslot.chars[who].timesused1;
        ff7.slot[s].chars[who].timesused2 = bufferslot.chars[who].timesused2;
        ff7.slot[s].chars[who].timesused3 = bufferslot.chars[who].timesused3;
        ff7.slot[s].chars[who].curHP = bufferslot.chars[who].curHP;
        ff7.slot[s].chars[who].baseHP = bufferslot.chars[who].baseHP;
        ff7.slot[s].chars[who].curMP = bufferslot.chars[who].curMP;
        ff7.slot[s].chars[who].baseMP = bufferslot.chars[who].baseMP;


        for(int z4=0;z4<4;z4++){ff7.slot[s].chars[who].z_4[z4] = bufferslot.chars[who].z_4[z4];}

        ff7.slot[s].chars[who].maxHP =bufferslot.chars[who].maxHP;
        ff7.slot[s].chars[who].maxMP =bufferslot.chars[who].maxMP;


        ff7.slot[s].chars[who].exp = bufferslot.chars[who].exp;

        for (int mat=0;mat<16;mat++){

          ff7.slot[s].chars[who].materias[mat].id = bufferslot.chars[who].materias[mat].id;
          for(int m=0;m<3;m++){ff7.slot[s].chars[who].materias[mat].ap[m] = bufferslot.chars[who].materias[mat].ap[m];}
          }
       ff7.slot[s].chars[who].expNext = bufferslot.chars[who].expNext;
       }//END CHAR LOOPING
       for (int p=0;p<3;p++)
       {

          ff7.slot[s].party[p] =bufferslot.party[p];
       }

    ff7.slot[s].z_2 = bufferslot.z_2; //0xFF


    for(int itm=0;itm<320;itm++) //Party item stock
    {

        ff7.slot[s].items[itm].id = bufferslot.items[itm].id;

        ff7.slot[s].items[itm].qty = bufferslot.items[itm].qty;
    }

    for (int met=0;met<200;met++) //Party materia stock
    {

        ff7.slot[s].materias[met].id =bufferslot.materias[met].id;

        for (int ma=0;ma<3;ma++){ff7.slot[s].materias[met].ap[ma] = bufferslot.materias[met].ap[ma];}
    }
    for (int met=0;met<48;met++) //Materia stolen by Yuffie
    {

        ff7.slot[s].stolen[met].id = bufferslot.stolen[met].id;

        for (int ma=0;ma<3;ma++){ff7.slot[s].stolen[met].ap[ma] = bufferslot.stolen[met].ap[ma];}
    }

    for(int z=0;z<32;z++)//32 Bytes Unknown
    {
    ff7.slot[s].z_3[z] = bufferslot.z_3[z];
    }


    ff7.slot[s].gil = bufferslot.gil;
    ff7.slot[s].time = bufferslot.time;

    for (int z=0;z<16;z++)
    {
    ff7.slot[s].z_4[z] = bufferslot.z_4[z];
    }


    ff7.slot[s].mapid = bufferslot.mapid;
    ff7.slot[s].locationid = bufferslot.locationid;// Current location

;// Unknown
    for(int z=0;z<2;z++)
    {
       ff7.slot[s].z_5[z] = bufferslot.z_5[z];
    }

    ff7.slot[s].coord.x = bufferslot.coord.x;
    ff7.slot[s].coord.y = bufferslot.coord.y;
    ff7.slot[s].coord.z = bufferslot.coord.z;

    for(int z=0;z<4;z++){ff7.slot[s].z_6[z] = bufferslot.z_6[z];}
    ff7.slot[s].mprogress = bufferslot.mprogress;
    ff7.slot[s].unknown1 = bufferslot.unknown1;

    ff7.slot[s].love.aeris = bufferslot.love.aeris;
    ff7.slot[s].love.tifa = bufferslot.love.tifa;
    ff7.slot[s].love.yuffie = bufferslot.love.yuffie;
    ff7.slot[s].love.barret = bufferslot.love.barret;

    for(int z=0;z<17;z++){ff7.slot[s].z_7[z] = bufferslot.z_7[z];}


    ff7.slot[s].battles=bufferslot.battles;
    ff7.slot[s].runs=bufferslot.runs;

    for(int t=0;t<36;t++){ff7.slot[s].temp[t] = bufferslot.temp[t];}

    for(int k=0;k<8;k++){ff7.slot[s].keyitems[k] = bufferslot.keyitems[k];}

    for(int z=0;z<13;z++){ff7.slot[s].z_8[z] = bufferslot.z_8[z];}

    for (int c=0;c<4;c++){ff7.slot[s].pennedchocos[c] = bufferslot.pennedchocos[c];}

    for (int z=0;z<136;z++){ff7.slot[s].z_9[z]=bufferslot.z_9[z];}
    ff7.slot[s].bm_progress1 = bufferslot.bm_progress1;
    ff7.slot[s].bm_progress2 = bufferslot.bm_progress2;
    for (int z=0;z<95;z++){ff7.slot[s].unknown2[z]=bufferslot.unknown2[z];}
    ff7.slot[s].bm_progress3 = bufferslot.bm_progress3;
    for (int z=0;z<7;z++){ff7.slot[s].unknown3[z]=bufferslot.unknown3[z];}

    ff7.slot[s].gp = bufferslot.gp;
    for (int z=0;z<12;z++){ff7.slot[s].z_10[z] =bufferslot.z_10[z];}

    ff7.slot[s].stables = bufferslot.stables;
    ff7.slot[s].stablesoccupied = bufferslot.stablesoccupied;
    ff7.slot[s].z_11=bufferslot.z_11;
    ff7.slot[s].chocobomask = bufferslot.chocobomask;
    ff7.slot[s].chocoborn = bufferslot.chocoborn;

    for(int z=0;z<101;z++){bufferslot.z_12[z]=0x00;}

    ff7.slot[s].turtleflyers = bufferslot.turtleflyers;

    for(int z=0;z<93;z++){ff7.slot[s].temp2[z] = bufferslot.temp2[z];}

    for (int c=0;c<6;c++)// collect chocobo slots 1-4
    {

    ff7.slot[s].chocobos[c].sprintspd =bufferslot.chocobos[c].sprintspd;
    ff7.slot[s].chocobos[c].maxsprintspd =bufferslot.chocobos[c].maxsprintspd;
    ff7.slot[s].chocobos[c].speed =bufferslot.chocobos[c].speed;
    ff7.slot[s].chocobos[c].maxspeed =bufferslot.chocobos[c].maxspeed;

    ff7.slot[s].chocobos[c].accel =bufferslot.chocobos[c].accel;
    ff7.slot[s].chocobos[c].coop =bufferslot.chocobos[c].coop;
    ff7.slot[s].chocobos[c].intelligence =bufferslot.chocobos[c].intelligence;
    ff7.slot[s].chocobos[c].personality =bufferslot.chocobos[c].personality;
    ff7.slot[s].chocobos[c].pcount =bufferslot.chocobos[c].pcount;
    ff7.slot[s].chocobos[c].raceswon =bufferslot.chocobos[c].raceswon;
    ff7.slot[s].chocobos[c].sex =bufferslot.chocobos[c].sex;
    ff7.slot[s].chocobos[c].type =bufferslot.chocobos[c].type;
    }


    for (int z=0;z<160;z++){ff7.slot[s].z_13[z]= bufferslot.z_13[z];}


    ff7.slot[s].disc = bufferslot.disc;


    for (int z=0;z<31;z++){ff7.slot[s].z_14[z] = bufferslot.z_14[z];}


    for (int c=0;c<6;c++) //get chocobonames
    {

       for (int o=0;o<6;o++){
           ff7.slot[s].chocobonames[c][o] = bufferslot.chocobonames[c][o];
       }
    }




    ff7.slot[s].chocostaminas[0] = bufferslot.chocostaminas[0];
    ff7.slot[s].chocostaminas[1]= bufferslot.chocostaminas[1];
    ff7.slot[s].chocostaminas[2]= bufferslot.chocostaminas[2];
    ff7.slot[s].chocostaminas[3]= bufferslot.chocostaminas[3];
    ff7.slot[s].chocostaminas[4]= bufferslot.chocostaminas[4];
    ff7.slot[s].chocostaminas[5]= bufferslot.chocostaminas[5];

    for(int z=0;z<400;z++){ff7.slot[s].z_17[z] = bufferslot.z_17[z];}




    ff7.slot[s].phsmask=bufferslot.phsmask;
    ff7.slot[s].unlockedchars=bufferslot.unlockedchars;

    for(int z=0;z<48;z++){ff7.slot[s].z_18[z]= bufferslot.z_18[z];}

    ff7.slot[s].battlespeed =bufferslot.battlespeed;
    ff7.slot[s].battlemspeed=bufferslot.battlemspeed;
    ff7.slot[s].options1=bufferslot.options1;
    ff7.slot[s].options2=bufferslot.options2;

    for(int z=0;z<16;z++){ff7.slot[s].z_19[z] = bufferslot.z_19[z];}
    ff7.slot[s].fieldmspeed = bufferslot.fieldmspeed;

    for(int z=0;z<7;z++){ff7.slot[s].z_20[z] = bufferslot.z_20[z];}
guirefresh();
}

/* The New Save File Function (Vegeta_Ss4) v0.8.3 */
void MainWindow::saveFileFull(const QString &fileName){
QFile file(fileName);
    if (!file.open(QFile::ReadWrite )) {
        QMessageBox::warning(this, tr("Black Chocobo"),tr("Cannot write file %1:\n%2.")
                 .arg(fileName)
                 .arg(file.errorString()));
        return;

    }


    //if file size is diferent, proper resize it.
    if(ff7.SG_SIZE != file.size())
    {
        file.resize(ff7.SG_SIZE);
    }

QDataStream out (&file);
out.setByteOrder(QDataStream::LittleEndian);

for(int i=0;i<ff7.SG_HEADER;i++){out << ff7.file_headerp[i];}//write file header


for(int si=0;si<ff7.SG_SLOT_NUMBER;si++)

//int si=0; // used for testing new values.
{//write 15 slots
   //  out << ff7_checksum(&ff7.slot[si].desc); // call to dizugo's checksum function (global.cpp)
  // out << Checksum((char *)&ff7.slot[si].desc); // call to quimm's checksum function (global.cpp)
    // out << Checksum((char *)&ff7.slot[si].desc); // call to quimm's checksum function (global.cpp)

    //temp = ff7file.mid((ff7.SG_SLOT_SIZE*i) + (ff7.SG_HEADER + 0x0000),ff7.SG_SLOT_HEADER);// added collect slot header len(0x0200) bytes (PSX)
    //for(int z=0;z<ff7.SG_SLOT_HEADER;z++){ff7.slot->headerp[z] = temp.at(z);}


    //out << ff7.slot[si].headerp;
    for(int z=0;z<ff7.SG_SLOT_HEADER;z++){out << ff7.hf[si].sl_header[z];}//write slot header
    /*FILE *pfile; // file needs to be written with one or two lines.. aali demands it :P and it should save trouble in the future.
    pfile = fopen(fileName.toAscii(),"w");
 fwrite(&ff7.slot[si],1,0x10F4,pfile);*/

    out << ff7.slot[si].checksum;
    out << ff7.slot[si].z_1;
    out << ff7.slot[si].desc.level;
    for (int p=0;p<3;p++){out << ff7.slot[si].desc.party[p];}
    for (int n=0;n<16;n++){out << qint8(ff7.slot[si].desc.name[n]);}
    out << ff7.slot[si].desc.curHP;
    out << ff7.slot[si].desc.maxHP;
    out << ff7.slot[si].desc.curMP;
    out << ff7.slot[si].desc.maxMP;
    out << ff7.slot[si].desc.gil;
    out << ff7.slot[si].desc.time;
    for (int loc=0; loc<32;loc++){out << ff7.slot[si].desc.location[loc];}
    for(int c=0;c<4;c++){for (int cc=0;cc<3;cc++){out << ff7.slot[si].colors[c][cc];}}
    for (int i=0;i<9;i++){//OUTPUT CHAR RECORDS!
        out << ff7.slot[si].chars[i].id;
        out << ff7.slot[si].chars[i].level;
        out << ff7.slot[si].chars[i].strength;
        out << ff7.slot[si].chars[i].vitality;
        out << ff7.slot[si].chars[i].magic;
        out << ff7.slot[si].chars[i].spirit;
        out << ff7.slot[si].chars[i].dexterity;
        out << ff7.slot[si].chars[i].luck;
        out << ff7.slot[si].chars[i].strength_bonus;
        out << ff7.slot[si].chars[i].vitality_bonus;
        out << ff7.slot[si].chars[i].magic_bonus;
        out << ff7.slot[si].chars[i].spirit_bonus;
        out << ff7.slot[si].chars[i].dexterity_bonus;
        out << ff7.slot[si].chars[i].luck_bonus;
        out << ff7.slot[si].chars[i].limitlevel;
        out << ff7.slot[si].chars[i].limitbar;
        for(int n=0;n<12;n++){out << ff7.slot[si].chars[i].name[n];}
        out << ff7.slot[si].chars[i].weapon;
        out << ff7.slot[si].chars[i].armor;
        out << ff7.slot[si].chars[i].accessory;
        for(int f=0;f<3;f++){out << ff7.slot[si].chars[i].flags[f];}
        out << ff7.slot[si].chars[i].limits;
        out << ff7.slot[si].chars[i].kills;
        out << ff7.slot[si].chars[i].timesused1;
        out << ff7.slot[si].chars[i].timesused2;
        out << ff7.slot[si].chars[i].timesused3;
        out << ff7.slot[si].chars[i].curHP;
        out << ff7.slot[si].chars[i].baseHP;
        out << ff7.slot[si].chars[i].curMP;
        out << ff7.slot[si].chars[i].baseMP;
        for (int z=0;z<4;z++){out << ff7.slot[si].chars[i].z_4[z];}
        out << ff7.slot[si].chars[i].maxHP;
        out << ff7.slot[si].chars[i].maxMP;
        out << ff7.slot[si].chars[i].exp;
        for (int m=0;m<16;m++){out << ff7.slot[si].chars[i].materias[m].id;
        for (int ma=0;ma<3;ma++){out << ff7.slot[si].chars[i].materias[m].ap[ma];}}
        out << ff7.slot[si].chars[i].expNext;
    }//end char loop
    for (int p=0;p<3;p++){out<< ff7.slot[si].party[p];}
    out<< ff7.slot[si].z_2;
    for (int itm=0;itm<320;itm ++)
    {
        out<< ff7.slot[si].items[itm].id;
        out<< ff7.slot[si].items[itm].qty;
    }
    for(int mat=0;mat<200;mat++)
    {
        out << ff7.slot[si].materias[mat].id;
        for(int ma=0;ma<3;ma++){out << ff7.slot[si].materias[mat].ap[ma];}
    }
    for(int mat=0;mat<48;mat++)
    {
        out << ff7.slot[si].stolen[mat].id;
        for(int ma=0;ma<3;ma++){out << ff7.slot[si].stolen[mat].ap[ma];}
    }
    for(int z=0;z<32;z++){out<< ff7.slot[si].z_3[z];}
    out << ff7.slot[si].gil;
    out<< ff7.slot[si].time;
    for (int z=0;z<16;z++){out<< ff7.slot[si].z_4[z];}
    out << ff7.slot[si].mapid;
    out << ff7.slot[si].locationid;
    for (int z=0;z<2;z++){out << ff7.slot[si].z_5[z];}
    out<< ff7.slot[si].coord.x;
    out<<ff7.slot[si].coord.y;
    out<<ff7.slot[si].coord.z;
    for(int z=0;z<4;z++){out<<ff7.slot[si].z_6[z];}
    out<< ff7.slot[si].mprogress;
    out<<ff7.slot[si].unknown1;
    out<< ff7.slot[si].love.aeris;
    out<< ff7.slot[si].love.tifa;
    out<< ff7.slot[si].love.yuffie;
    out<< ff7.slot[si].love.barret;
    for (int z=0;z<17;z++){out << ff7.slot[si].z_7[z];}
    out << ff7.slot[si].battles;
    out << ff7.slot[si].runs;
    for(int t=0;t<36;t++){out << ff7.slot[si].temp[t];}
    for(int k=0;k<8;k++){out << ff7.slot[si].keyitems[k];}
    for(int z=0;z<13;z++){out << ff7.slot[si].z_8[z];}
    for (int c=0;c<4;c++){out << ff7.slot[si].pennedchocos[c];}
    //start new data
    for (int z=0;z<136;z++){out << ff7.slot[si].z_9[z];}
    out<<ff7.slot[si].bm_progress1;
    out<<ff7.slot[si].bm_progress2;
    for (int z=0;z<95;z++){out<<ff7.slot[si].unknown2[z];}
    out<<ff7.slot[si].bm_progress3;
    for (int z=0;z<7;z++){out<<ff7.slot[si].unknown3[z];}
    //end new data
    out << ff7.slot[si].gp;
    for (int z=0;z<12;z++){out << ff7.slot[si].z_10[z];}
    out << ff7.slot[si].stables;
    out << ff7.slot[si].stablesoccupied;//Bug Fixed! Before was z_11 (Vegeta_Ss4) v0.8.3
    out << ff7.slot[si].z_11;//Bug Fixed! Before was stablesoccupied (Vegeta_Ss4) v0.8.3
    out << ff7.slot[si].chocobomask;
    out << ff7.slot[si].chocoborn;
    for(int z=0;z<101;z++){out << ff7.slot[si].z_12[z];}
    out << ff7.slot[si].turtleflyers;
    for (int z=0;z<93;z++){out <<ff7.slot[si].temp2[z];}
    for(int c=0;c<4;c++)
    {
        out << ff7.slot[si].chocobos[c].sprintspd;//fixed before speed
        out << ff7.slot[si].chocobos[c].maxsprintspd;
        out << ff7.slot[si].chocobos[c].speed;
        out << ff7.slot[si].chocobos[c].maxspeed;
        out << ff7.slot[si].chocobos[c].accel;
        out << ff7.slot[si].chocobos[c].coop;
        out << ff7.slot[si].chocobos[c].intelligence;
        out << ff7.slot[si].chocobos[c].personality;
        out << ff7.slot[si].chocobos[c].pcount;
        out << ff7.slot[si].chocobos[c].raceswon;
        out << ff7.slot[si].chocobos[c].sex;
        out << ff7.slot[si].chocobos[c].type;

    }
    for(int z=0;z<160;z++){out<<ff7.slot[si].z_13[z];}                                  //0x0E04 z_13
    out << ff7.slot[si].disc;                                                           //0x0EA4 Current Disk
    for(int z=0;z<31;z++){out << ff7.slot[si].z_14[z];}                                 //0x0EA5 z_14
    for(int c=0;c<6;c++){for(int o=0;o<6;o++){out << ff7.slot[si].chocobonames[c][o];}} //0x0EC4 save chocobonames
    for(int c=0;c<6;c++){out << ff7.slot[si].chocostaminas[c];}                         //0x0EE8 save all the stamina values too
    for(int z=0;z<400;z++){out << ff7.slot[si].z_17[z];}                                //0x0EF4 z_17
    for(int c=4;c<6;c++)                                                                //0x1084 ADDED CHOCO 5-6
    {
        out << ff7.slot[si].chocobos[c].sprintspd;
        out << ff7.slot[si].chocobos[c].maxsprintspd;
        out << ff7.slot[si].chocobos[c].speed;
        out << ff7.slot[si].chocobos[c].maxspeed;
        out << ff7.slot[si].chocobos[c].accel;
        out << ff7.slot[si].chocobos[c].coop;
        out << ff7.slot[si].chocobos[c].intelligence;
        out << ff7.slot[si].chocobos[c].personality;
        out << ff7.slot[si].chocobos[c].pcount;
        out << ff7.slot[si].chocobos[c].raceswon;
        out << ff7.slot[si].chocobos[c].sex;
        out << ff7.slot[si].chocobos[c].type;

    }
    out << ff7.slot[si].phsmask;                                                        //0x10A4
    out << ff7.slot[si].unlockedchars;                                                  //0x10A6
    for(int z=0;z<48;z++){out << ff7.slot[si].z_18[z];}                                 //0x10A8
    out <<ff7.slot[si].battlespeed;
    out <<ff7.slot[si].battlemspeed;
    out <<ff7.slot[si].options1;
    out <<ff7.slot[si].options2;
    for(int z=0;z<16;z++){out <<ff7.slot[si].z_19[z];}
    out <<ff7.slot[si].fieldmspeed;
    for(int z=0;z<7;z++){out<<ff7.slot[si].z_20[z];}

    for(int z=0;z<ff7.SG_SLOT_FOOTER;z++){out << ff7.hf[si].sl_footer[z];}              //write slot footer
//*/  //used to cut out all of write. for C style writing
}// END OF SLOTS

// START CHECKSUM VEGETA
//FILE * file2;
void * memory;
long file_size;

file.seek(0);//Set pointer to the Beggining

QByteArray ff7savefile;

ff7savefile = file.readAll(); //put all data in temp raw file
file_size = file.size();//Get File Size
memory = (void*) malloc(ff7.SG_SIZE);//Memory Allocation

if (!memory) {
return;
}

file.seek(0);
memcpy(memory,ff7savefile.mid(0x00000,ff7.SG_SIZE),ff7.SG_SIZE);

//Do checksum foreach slot
    for(int i=0, checksum=0; i<ff7.SG_SLOT_NUMBER; i++)
    {

        char * data_pointer = ((char*)memory + ff7.SG_HEADER + ff7.SG_SLOT_SIZE*i + ff7.SG_SLOT_HEADER + 0x04);
        checksum = ff7__checksum(data_pointer); //2 Bytes checksum (a 16-bit Byte checksum)

        if(checksum != 0x4D1D) //if is a blank slot don't write checksum!
        {

            int index = ff7.SG_HEADER + ff7.SG_SLOT_SIZE*i + ff7.SG_SLOT_HEADER;

            file.seek(index);

            out << checksum;
        }

    }


file.close();
free(memory);
// END CHECKSUM VEGETA
}

void MainWindow::on_actionExport_PC_Save_activated()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Final Fantasy 7 SaveGame"), "",
                tr("FF7 SaveGame(*.ff7)")); // Only Allow PC save Since we are going to force its creation.
        if (!fileName.isEmpty())
    {
            QFile file(fileName);
                if (!file.open(QFile::ReadWrite )) {
                    QMessageBox::warning(this, tr("Black Chocobo"),tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
                    return;

                }
                ff7.SG_SIZE          = FF7_PC_SAVE_GAME_SIZE;
                ff7.SG_HEADER        = FF7_PC_SAVE_GAME_HEADER;
                ff7.SG_FOOTER        = FF7_PC_SAVE_GAME_FOOTER;
                ff7.SG_DATA_SIZE     = FF7_PC_SAVE_GAME_DATA_SIZE;
                ff7.SG_SLOT_HEADER   = FF7_PC_SAVE_GAME_SLOT_HEADER;
                ff7.SG_SLOT_FOOTER   = FF7_PC_SAVE_GAME_SLOT_FOOTER;
                ff7.SG_SLOT_SIZE     = FF7_PC_SAVE_GAME_SLOT_SIZE;
                ff7.SG_SLOT_NUMBER   = FF7_PC_SAVE_GAME_SLOT_NUMBER;
                ff7.SG_TYPE          = "PC";
                ff7.file_headerp     = ff7.file_header_pc;           //pointer to pc file header
                ff7.file_footerp     = ff7.file_footer_pc;           //pointer to pc file footer
            ui->combo_control->setCurrentIndex(0); // set controls to default so we don't break the controller maping!
            QDataStream out (&file);
            out.setByteOrder(QDataStream::LittleEndian);

            for(int i=0;i<9;i++){out << PC_SAVE_GAME_FILE_HEADER[i];}//write A PC file header


            for(int si=0;si<15;si++)
            //int si=0; // used for testing new values.
            {//write 15 slots its a pc save...

                out << ff7.slot[si].checksum;
                out << ff7.slot[si].z_1;
                out << ff7.slot[si].desc.level;
                for (int p=0;p<3;p++){out << ff7.slot[si].desc.party[p];}
                for (int n=0;n<16;n++){out << qint8(ff7.slot[si].desc.name[n]);}
                out << ff7.slot[si].desc.curHP;
                out << ff7.slot[si].desc.maxHP;
                out << ff7.slot[si].desc.curMP;
                out << ff7.slot[si].desc.maxMP;
                out << ff7.slot[si].desc.gil;
                out << ff7.slot[si].desc.time;
                for (int loc=0; loc<32;loc++){out << ff7.slot[si].desc.location[loc];}
                for(int c=0;c<4;c++){for (int cc=0;cc<3;cc++){out << ff7.slot[si].colors[c][cc];}}
                for (int i=0;i<9;i++){//OUTPUT CHAR RECORDS!
                    out << ff7.slot[si].chars[i].id;
                    out << ff7.slot[si].chars[i].level;
                    out << ff7.slot[si].chars[i].strength;
                    out << ff7.slot[si].chars[i].vitality;
                    out << ff7.slot[si].chars[i].magic;
                    out << ff7.slot[si].chars[i].spirit;
                    out << ff7.slot[si].chars[i].dexterity;
                    out << ff7.slot[si].chars[i].luck;
                    out << ff7.slot[si].chars[i].strength_bonus;
                    out << ff7.slot[si].chars[i].vitality_bonus;
                    out << ff7.slot[si].chars[i].magic_bonus;
                    out << ff7.slot[si].chars[i].spirit_bonus;
                    out << ff7.slot[si].chars[i].dexterity_bonus;
                    out << ff7.slot[si].chars[i].luck_bonus;
                    out << ff7.slot[si].chars[i].limitlevel;
                    out << ff7.slot[si].chars[i].limitbar;
                    for(int n=0;n<12;n++){out << ff7.slot[si].chars[i].name[n];}
                    out << ff7.slot[si].chars[i].weapon;
                    out << ff7.slot[si].chars[i].armor;
                    out << ff7.slot[si].chars[i].accessory;
                    for(int f=0;f<3;f++){out << ff7.slot[si].chars[i].flags[f];}
                    out << ff7.slot[si].chars[i].limits;
                    out << ff7.slot[si].chars[i].kills;
                    out << ff7.slot[si].chars[i].timesused1;
                    out << ff7.slot[si].chars[i].timesused2;
                    out << ff7.slot[si].chars[i].timesused3;
                    out << ff7.slot[si].chars[i].curHP;
                    out << ff7.slot[si].chars[i].baseHP;
                    out << ff7.slot[si].chars[i].curMP;
                    out << ff7.slot[si].chars[i].baseMP;
                    for (int z=0;z<4;z++){out << ff7.slot[si].chars[i].z_4[z];}
                    out << ff7.slot[si].chars[i].maxHP;
                    out << ff7.slot[si].chars[i].maxMP;
                    out << ff7.slot[si].chars[i].exp;
                    for (int m=0;m<16;m++){out << ff7.slot[si].chars[i].materias[m].id;
                    for (int ma=0;ma<3;ma++){out << ff7.slot[si].chars[i].materias[m].ap[ma];}}
                    out << ff7.slot[si].chars[i].expNext;
                }//end char loop
                for (int p=0;p<3;p++){out<< ff7.slot[si].party[p];}
                out<< ff7.slot[si].z_2;
                for (int itm=0;itm<320;itm ++)
                {
                    out<< ff7.slot[si].items[itm].id;
                    out<< ff7.slot[si].items[itm].qty;
                }
                for(int mat=0;mat<200;mat++)
                {
                    out << ff7.slot[si].materias[mat].id;
                    for(int ma=0;ma<3;ma++){out << ff7.slot[si].materias[mat].ap[ma];}
                }
                for(int mat=0;mat<48;mat++)
                {
                    out << ff7.slot[si].stolen[mat].id;
                    for(int ma=0;ma<3;ma++){out << ff7.slot[si].stolen[mat].ap[ma];}
                }
                for(int z=0;z<32;z++){out<< ff7.slot[si].z_3[z];}
                out << ff7.slot[si].gil;
                out<< ff7.slot[si].time;
                for (int z=0;z<16;z++){out<< ff7.slot[si].z_4[z];}
                out << ff7.slot[si].mapid;
                out << ff7.slot[si].locationid;
                for (int z=0;z<2;z++){out << ff7.slot[si].z_5[z];}
                out<< ff7.slot[si].coord.x;
                out<<ff7.slot[si].coord.y;
                out<<ff7.slot[si].coord.z;
                for(int z=0;z<4;z++){out<<ff7.slot[si].z_6[z];}
                out<< ff7.slot[si].mprogress;
                out<<ff7.slot[si].unknown1;
                out<< ff7.slot[si].love.aeris;
                out<< ff7.slot[si].love.tifa;
                out<< ff7.slot[si].love.yuffie;
                out<< ff7.slot[si].love.barret;
                for (int z=0;z<17;z++){out << ff7.slot[si].z_7[z];}
                out << ff7.slot[si].battles;
                out << ff7.slot[si].runs;
                for(int t=0;t<36;t++){out << ff7.slot[si].temp[t];}
                for(int k=0;k<8;k++){out << ff7.slot[si].keyitems[k];}
                for(int z=0;z<13;z++){out << ff7.slot[si].z_8[z];}
                for (int c=0;c<4;c++){out << ff7.slot[si].pennedchocos[c];}
                for (int z=0;z<136;z++){out << ff7.slot[si].z_9[z];}
                out<<ff7.slot[si].bm_progress1;
                out<<ff7.slot[si].bm_progress2;
                for (int z=0;z<95;z++){out<<ff7.slot[si].unknown2[z];}
                out<<ff7.slot[si].bm_progress3;
                for (int z=0;z<7;z++){out<<ff7.slot[si].unknown3[z];}
                out << ff7.slot[si].gp;
                for (int z=0;z<12;z++){out << ff7.slot[si].z_10[z];}
                out << ff7.slot[si].stables;
                out << ff7.slot[si].stablesoccupied;//Bug Fixed! Before was z_11 (Vegeta_Ss4) v0.8.3
                out << ff7.slot[si].z_11;//Bug Fixed! Before was stablesoccupied (Vegeta_Ss4) v0.8.3
                out << ff7.slot[si].chocobomask;
                out << ff7.slot[si].chocoborn;
                for(int z=0;z<101;z++){out << ff7.slot[si].z_12[z];}
                out << ff7.slot[si].turtleflyers;
                for (int z=0;z<93;z++){out <<ff7.slot[si].temp2[z];}
                for(int c=0;c<4;c++)
                {
                    out << ff7.slot[si].chocobos[c].sprintspd;//fixed before speed
                    out << ff7.slot[si].chocobos[c].maxsprintspd;
                    out << ff7.slot[si].chocobos[c].speed;
                    out << ff7.slot[si].chocobos[c].maxspeed;
                    out << ff7.slot[si].chocobos[c].accel;
                    out << ff7.slot[si].chocobos[c].coop;
                    out << ff7.slot[si].chocobos[c].intelligence;
                    out << ff7.slot[si].chocobos[c].personality;
                    out << ff7.slot[si].chocobos[c].pcount;
                    out << ff7.slot[si].chocobos[c].raceswon;
                    out << ff7.slot[si].chocobos[c].sex;
                    out << ff7.slot[si].chocobos[c].type;

                }
                for(int z=0;z<160;z++){out<<ff7.slot[si].z_13[z];}                                  //0x0E04 z_13
                out << ff7.slot[si].disc;                                                           //0x0EA4 Current Disk
                for(int z=0;z<31;z++){out << ff7.slot[si].z_14[z];}                                 //0x0EA5 z_14
                for(int c=0;c<6;c++){for(int o=0;o<6;o++){out << ff7.slot[si].chocobonames[c][o];}} //0x0EC4 save chocobonames
                for(int c=0;c<6;c++){out << ff7.slot[si].chocostaminas[c];}                         //0x0EE8 save all the stamina values too
                for(int z=0;z<400;z++){out << ff7.slot[si].z_17[z];}                                //0x0EF4 z_17
                for(int c=4;c<6;c++)                                                                //0x1084 ADDED CHOCO 5-6
                {
                    out << ff7.slot[si].chocobos[c].sprintspd;
                    out << ff7.slot[si].chocobos[c].maxsprintspd;
                    out << ff7.slot[si].chocobos[c].speed;
                    out << ff7.slot[si].chocobos[c].maxspeed;
                    out << ff7.slot[si].chocobos[c].accel;
                    out << ff7.slot[si].chocobos[c].coop;
                    out << ff7.slot[si].chocobos[c].intelligence;
                    out << ff7.slot[si].chocobos[c].personality;
                    out << ff7.slot[si].chocobos[c].pcount;
                    out << ff7.slot[si].chocobos[c].raceswon;
                    out << ff7.slot[si].chocobos[c].sex;
                    out << ff7.slot[si].chocobos[c].type;

                }
                out << ff7.slot[si].phsmask;                                                        //0x10A4
                out << ff7.slot[si].unlockedchars;                                                  //0x10A6
                for(int z=0;z<48;z++){out << ff7.slot[si].z_18[z];}                                 //0x10A8
                out <<ff7.slot[si].battlespeed;
                out <<ff7.slot[si].battlemspeed;
                out <<ff7.slot[si].options1;
                out <<ff7.slot[si].options2;
                for(int z=0;z<16;z++){out <<ff7.slot[si].z_19[z];}
                out <<ff7.slot[si].fieldmspeed;
                for(int z=0;z<7;z++){out<<ff7.slot[si].z_20[z];}
            }// END OF SLOTS

            // START CHECKSUM VEGETA
            //FILE * file2;
            void * memory;
            long file_size;

            file.seek(0);//Set pointer to the Beggining

            QByteArray ff7savefile;

            ff7savefile = file.readAll(); //put all data in temp raw file
            file_size = file.size();//Get File Size
            memory = (void*) malloc(ff7.SG_SIZE);//Memory Allocation

            if (!memory) {
            return;
            }

            file.seek(0);
            memcpy(memory,ff7savefile.mid(0x00000,ff7.SG_SIZE),ff7.SG_SIZE);

            //Do checksum foreach slot
                for(int i=0, checksum=0; i<ff7.SG_SLOT_NUMBER; i++)
                {

                    char * data_pointer = ((char*)memory + ff7.SG_HEADER + ff7.SG_SLOT_SIZE*i + ff7.SG_SLOT_HEADER + 0x04);
                    checksum = ff7__checksum(data_pointer); //2 Bytes checksum (a 16-bit Byte checksum)

                    if(checksum != 0x4D1D) //if is a blank slot don't write checksum!
                    {

                        int index = ff7.SG_HEADER + ff7.SG_SLOT_SIZE*i + ff7.SG_SLOT_HEADER;

                        file.seek(index);

                        out << checksum;
                    }

                }


            file.close();
            free(memory);
            // END CHECKSUM VEGETA
        }
    }

void MainWindow::on_actionExport_PSX_activated()
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Final Fantasy 7 SaveGame"), "BASCUS-94163FF7-",
                tr("BASCUS-94163FF7-S01(*-S01);;BASCUS-94163FF7-S02(*-S02);;BASCUS-94163FF7-S03(*-S03);;BASCUS-94163FF7-S04(*-S04);;BASCUS-94163FF7-S05(*-S05);;BASCUS-94163FF7-S06(*-S06);;BASCUS-94163FF7-S07(*-S07);;BASCUS-94163FF7-S08(*-S08);;BASCUS-94163FF7-S09(*-S09);;BASCUS-94163FF7-S10(*-S10);;BASCUS-94163FF7-S11(*-S11);;BASCUS-94163FF7-S12(*-S12);;BASCUS-94163FF7-S13(*-S13);;BASCUS-94163FF7-S14(*-S14);;BASCUS-94163FF7-S15(*-S15)")); // Only Allow PSX save slots Since we are going to force its creation.
        if (!fileName.isEmpty())
    {
            QFile file(fileName);
                if (!file.open(QFile::ReadWrite )) {
                    QMessageBox::warning(this, tr("Black Chocobo"),tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
                    return;

                }
                ff7.SG_SIZE          = FF7_PSX_SAVE_GAME_SIZE;
                ff7.SG_HEADER        = FF7_PSX_SAVE_GAME_HEADER;
                ff7.SG_FOOTER        = FF7_PSX_SAVE_GAME_FOOTER;
                ff7.SG_DATA_SIZE     = FF7_PSX_SAVE_GAME_DATA_SIZE;
                ff7.SG_SLOT_HEADER   = FF7_PSX_SAVE_GAME_SLOT_HEADER;
                ff7.SG_SLOT_FOOTER   = FF7_PSX_SAVE_GAME_SLOT_FOOTER;
                ff7.SG_SLOT_SIZE     = FF7_PSX_SAVE_GAME_SLOT_SIZE;
                ff7.SG_SLOT_NUMBER   = FF7_PSX_SAVE_GAME_SLOT_NUMBER;
                ff7.SG_TYPE          = "PSX";
                ff7.file_headerp     = ff7.file_header_psx;           //pointer to pc file header
                ff7.file_footerp     = ff7.file_footer_psx;           //pointer to pc file footer
            ui->combo_control->setCurrentIndex(0);

            QDataStream out (&file);
            out.setByteOrder(QDataStream::LittleEndian);

            //Check to see what slot header we are gonna write out.

                 if(file.fileName().endsWith("S01")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S01[i];}}
            else if(file.fileName().endsWith("S02")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S02[i];}}
            else if(file.fileName().endsWith("S03")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S03[i];}}
            else if(file.fileName().endsWith("S04")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S04[i];}}
            else if(file.fileName().endsWith("S05")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S05[i];}}
            else if(file.fileName().endsWith("S06")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S06[i];}}
            else if(file.fileName().endsWith("S07")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S07[i];}}
            else if(file.fileName().endsWith("S08")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S08[i];}}
            else if(file.fileName().endsWith("S09")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S09[i];}}
            else if(file.fileName().endsWith("S10")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S10[i];}}
            else if(file.fileName().endsWith("S11")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S11[i];}}
            else if(file.fileName().endsWith("S12")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S12[i];}}
            else if(file.fileName().endsWith("S13")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S13[i];}}
            else if(file.fileName().endsWith("S14")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S14[i];}}
            else if(file.fileName().endsWith("S15")){for(int i=0;i<0x200;i++) {out << PSX_SAVE_GAME_FILE_HEADER_S15[i];}}
            else{QMessageBox::information(this,"Bad Psx Save Name", "Can't Decide On What Header to Write, Please Add the sufix SXX (where x= 01-15, with leading 0 if < 10) US Header for that slot number will be written to the save"   );}

            int si = s; // set the slot to be output to the current slot selected.
                out << ff7.slot[si].checksum;
                out << ff7.slot[si].z_1;
                out << ff7.slot[si].desc.level;
                for (int p=0;p<3;p++){out << ff7.slot[si].desc.party[p];}
                for (int n=0;n<16;n++){out << qint8(ff7.slot[si].desc.name[n]);}
                out << ff7.slot[si].desc.curHP;
                out << ff7.slot[si].desc.maxHP;
                out << ff7.slot[si].desc.curMP;
                out << ff7.slot[si].desc.maxMP;
                out << ff7.slot[si].desc.gil;
                out << ff7.slot[si].desc.time;
                for (int loc=0; loc<32;loc++){out << ff7.slot[si].desc.location[loc];}
                for(int c=0;c<4;c++){for (int cc=0;cc<3;cc++){out << ff7.slot[si].colors[c][cc];}}
                for (int i=0;i<9;i++){//OUTPUT CHAR RECORDS!
                    out << ff7.slot[si].chars[i].id;
                    out << ff7.slot[si].chars[i].level;
                    out << ff7.slot[si].chars[i].strength;
                    out << ff7.slot[si].chars[i].vitality;
                    out << ff7.slot[si].chars[i].magic;
                    out << ff7.slot[si].chars[i].spirit;
                    out << ff7.slot[si].chars[i].dexterity;
                    out << ff7.slot[si].chars[i].luck;
                    out << ff7.slot[si].chars[i].strength_bonus;
                    out << ff7.slot[si].chars[i].vitality_bonus;
                    out << ff7.slot[si].chars[i].magic_bonus;
                    out << ff7.slot[si].chars[i].spirit_bonus;
                    out << ff7.slot[si].chars[i].dexterity_bonus;
                    out << ff7.slot[si].chars[i].luck_bonus;
                    out << ff7.slot[si].chars[i].limitlevel;
                    out << ff7.slot[si].chars[i].limitbar;
                    for(int n=0;n<12;n++){out << ff7.slot[si].chars[i].name[n];}
                    out << ff7.slot[si].chars[i].weapon;
                    out << ff7.slot[si].chars[i].armor;
                    out << ff7.slot[si].chars[i].accessory;
                    for(int f=0;f<3;f++){out << ff7.slot[si].chars[i].flags[f];}
                    out << ff7.slot[si].chars[i].limits;
                    out << ff7.slot[si].chars[i].kills;
                    out << ff7.slot[si].chars[i].timesused1;
                    out << ff7.slot[si].chars[i].timesused2;
                    out << ff7.slot[si].chars[i].timesused3;
                    out << ff7.slot[si].chars[i].curHP;
                    out << ff7.slot[si].chars[i].baseHP;
                    out << ff7.slot[si].chars[i].curMP;
                    out << ff7.slot[si].chars[i].baseMP;
                    for (int z=0;z<4;z++){out << ff7.slot[si].chars[i].z_4[z];}
                    out << ff7.slot[si].chars[i].maxHP;
                    out << ff7.slot[si].chars[i].maxMP;
                    out << ff7.slot[si].chars[i].exp;
                    for (int m=0;m<16;m++){out << ff7.slot[si].chars[i].materias[m].id;
                    for (int ma=0;ma<3;ma++){out << ff7.slot[si].chars[i].materias[m].ap[ma];}}
                    out << ff7.slot[si].chars[i].expNext;
                }//end char loop
                for (int p=0;p<3;p++){out<< ff7.slot[si].party[p];}
                out<< ff7.slot[si].z_2;
                for (int itm=0;itm<320;itm ++)
                {
                    out<< ff7.slot[si].items[itm].id;
                    out<< ff7.slot[si].items[itm].qty;
                }
                for(int mat=0;mat<200;mat++)
                {
                    out << ff7.slot[si].materias[mat].id;
                    for(int ma=0;ma<3;ma++){out << ff7.slot[si].materias[mat].ap[ma];}
                }
                for(int mat=0;mat<48;mat++)
                {
                    out << ff7.slot[si].stolen[mat].id;
                    for(int ma=0;ma<3;ma++){out << ff7.slot[si].stolen[mat].ap[ma];}
                }
                for(int z=0;z<32;z++){out<< ff7.slot[si].z_3[z];}
                out << ff7.slot[si].gil;
                out<< ff7.slot[si].time;
                for (int z=0;z<16;z++){out<< ff7.slot[si].z_4[z];}
                out << ff7.slot[si].mapid;
                out << ff7.slot[si].locationid;
                for (int z=0;z<2;z++){out << ff7.slot[si].z_5[z];}
                out<< ff7.slot[si].coord.x;
                out<<ff7.slot[si].coord.y;
                out<<ff7.slot[si].coord.z;
                for(int z=0;z<4;z++){out<<ff7.slot[si].z_6[z];}
                out<< ff7.slot[si].mprogress;
                out<<ff7.slot[si].unknown1;
                out<< ff7.slot[si].love.aeris;
                out<< ff7.slot[si].love.tifa;
                out<< ff7.slot[si].love.yuffie;
                out<< ff7.slot[si].love.barret;
                for (int z=0;z<17;z++){out << ff7.slot[si].z_7[z];}
                out << ff7.slot[si].battles;
                out << ff7.slot[si].runs;
                for(int t=0;t<36;t++){out << ff7.slot[si].temp[t];}
                for(int k=0;k<8;k++){out << ff7.slot[si].keyitems[k];}
                for(int z=0;z<13;z++){out << ff7.slot[si].z_8[z];}
                for (int c=0;c<4;c++){out << ff7.slot[si].pennedchocos[c];}
                for (int z=0;z<136;z++){out << ff7.slot[si].z_9[z];}
                out<<ff7.slot[si].bm_progress1;
                out<<ff7.slot[si].bm_progress2;
                for (int z=0;z<95;z++){out<<ff7.slot[si].unknown2[z];}
                out<<ff7.slot[si].bm_progress3;
                for (int z=0;z<7;z++){out<<ff7.slot[si].unknown3[z];}
                out << ff7.slot[si].gp;
                for (int z=0;z<12;z++){out << ff7.slot[si].z_10[z];}
                out << ff7.slot[si].stables;
                out << ff7.slot[si].stablesoccupied;//Bug Fixed! Before was z_11 (Vegeta_Ss4) v0.8.3
                out << ff7.slot[si].z_11;//Bug Fixed! Before was stablesoccupied (Vegeta_Ss4) v0.8.3
                out << ff7.slot[si].chocobomask;
                out << ff7.slot[si].chocoborn;
                for(int z=0;z<101;z++){out << ff7.slot[si].z_12[z];}
                out << ff7.slot[si].turtleflyers;
                for (int z=0;z<93;z++){out <<ff7.slot[si].temp2[z];}
                for(int c=0;c<4;c++)
                {
                    out << ff7.slot[si].chocobos[c].sprintspd;//fixed before speed
                    out << ff7.slot[si].chocobos[c].maxsprintspd;
                    out << ff7.slot[si].chocobos[c].speed;
                    out << ff7.slot[si].chocobos[c].maxspeed;
                    out << ff7.slot[si].chocobos[c].accel;
                    out << ff7.slot[si].chocobos[c].coop;
                    out << ff7.slot[si].chocobos[c].intelligence;
                    out << ff7.slot[si].chocobos[c].personality;
                    out << ff7.slot[si].chocobos[c].pcount;
                    out << ff7.slot[si].chocobos[c].raceswon;
                    out << ff7.slot[si].chocobos[c].sex;
                    out << ff7.slot[si].chocobos[c].type;

                }
                for(int z=0;z<160;z++){out<<ff7.slot[si].z_13[z];}                                  //0x0E04 z_13
                out << ff7.slot[si].disc;                                                           //0x0EA4 Current Disk
                for(int z=0;z<31;z++){out << ff7.slot[si].z_14[z];}                                 //0x0EA5 z_14
                for(int c=0;c<6;c++){for(int o=0;o<6;o++){out << ff7.slot[si].chocobonames[c][o];}} //0x0EC4 save chocobonames
                for(int c=0;c<6;c++){out << ff7.slot[si].chocostaminas[c];}                         //0x0EE8 save all the stamina values too
                for(int z=0;z<400;z++){out << ff7.slot[si].z_17[z];}                                //0x0EF4 z_17
                for(int c=4;c<6;c++)                                                                //0x1084 ADDED CHOCO 5-6
                {
                    out << ff7.slot[si].chocobos[c].sprintspd;
                    out << ff7.slot[si].chocobos[c].maxsprintspd;
                    out << ff7.slot[si].chocobos[c].speed;
                    out << ff7.slot[si].chocobos[c].maxspeed;
                    out << ff7.slot[si].chocobos[c].accel;
                    out << ff7.slot[si].chocobos[c].coop;
                    out << ff7.slot[si].chocobos[c].intelligence;
                    out << ff7.slot[si].chocobos[c].personality;
                    out << ff7.slot[si].chocobos[c].pcount;
                    out << ff7.slot[si].chocobos[c].raceswon;
                    out << ff7.slot[si].chocobos[c].sex;
                    out << ff7.slot[si].chocobos[c].type;

                }
                out << ff7.slot[si].phsmask;                                                        //0x10A4
                out << ff7.slot[si].unlockedchars;                                                  //0x10A6
                for(int z=0;z<48;z++){out << ff7.slot[si].z_18[z];}                                 //0x10A8
                out <<ff7.slot[si].battlespeed;
                out <<ff7.slot[si].battlemspeed;
                out <<ff7.slot[si].options1;
                out <<ff7.slot[si].options2;
                for(int z=0;z<16;z++){out <<ff7.slot[si].z_19[z];}
                out <<ff7.slot[si].fieldmspeed;
                for(int z=0;z<7;z++){out<<ff7.slot[si].z_20[z];}
            // END OF SLOT
                for (int z=0;z<835;z++){out << 0x00;}
            // START CHECKSUM VEGETA
            //FILE * file2;
            void * memory;
            long file_size;

            file.seek(0);//Set pointer to the Beggining

            QByteArray ff7savefile;

            ff7savefile = file.readAll(); //put all data in temp raw file
            file_size = file.size();//Get File Size
            memory = (void*) malloc(ff7.SG_SIZE);//Memory Allocation

            if (!memory) {
            return;
            }

            file.seek(0);
            memcpy(memory,ff7savefile.mid(0x00000,ff7.SG_SIZE),ff7.SG_SIZE);

            //Do checksum foreach slot
                for(int i=0, checksum=0; i<ff7.SG_SLOT_NUMBER; i++)
                {

                    char * data_pointer = ((char*)memory + ff7.SG_HEADER + ff7.SG_SLOT_SIZE*i + ff7.SG_SLOT_HEADER + 0x04);
                    checksum = ff7__checksum(data_pointer); //2 Bytes checksum (a 16-bit Byte checksum)

                    if(checksum != 0x4D1D) //if is a blank slot don't write checksum!
                    {

                        int index = ff7.SG_HEADER + ff7.SG_SLOT_SIZE*i + ff7.SG_SLOT_HEADER;

                        file.seek(index);

                        out << checksum;
                    }

                }


            file.close();
            free(memory);
            // END CHECKSUM VEGETA
        }
}
