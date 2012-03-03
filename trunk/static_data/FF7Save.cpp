/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
//                                                                          //
//    This file is part of <UnNamedToolKit>                                 //
//                                                                          //
//  <UnNamedToolKit> is free software: you can redistribute it and/or modify//
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
// <UnNamedToolKit> is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#include "FF7Save.h"
#include <QObject>
#include <QFile>
#include <QDataStream>
bool FF7Save::LoadFile(const QString &fileName)
  {
    // Return true if File Loaded and false if file not loaded.
    // This Class should contain NO Gui Parts 
    if(fileName.isEmpty()){return false;}// bail on empty string.
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){return false;}
    QByteArray ff7file;
    ff7file = file.readAll(); //put all data in temp raw file
    QByteArray temp; // create a temp to be used when needed
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~Set File Type Vars ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    int file_size = file.size();
    QString info_string = "%1(%2)\n%3 -- %4";
    info_string = info_string.arg(fileName,QString::number(file.size()),QString(ff7file.mid(0,2)),QString(PC_SAVE_GAME_FILE_ID));
    if((file_size == FF7_PC_SAVE_GAME_SIZE) && ff7file.startsWith(PC_SAVE_GAME_FILE_ID))
    {
       SG_SIZE          = FF7_PC_SAVE_GAME_SIZE;
       SG_HEADER        = FF7_PC_SAVE_GAME_HEADER;
       SG_FOOTER        = FF7_PC_SAVE_GAME_FOOTER;
       SG_DATA_SIZE     = FF7_PC_SAVE_GAME_DATA_SIZE;
       SG_SLOT_HEADER   = FF7_PC_SAVE_GAME_SLOT_HEADER;
       SG_SLOT_FOOTER   = FF7_PC_SAVE_GAME_SLOT_FOOTER;
       SG_SLOT_SIZE     = FF7_PC_SAVE_GAME_SLOT_SIZE;
       SG_SLOT_NUMBER   = FF7_PC_SAVE_GAME_SLOT_NUMBER;
       SG_TYPE          = "PC";
       file_headerp     = file_header_pc;           //pointer to pc file header
       file_footerp     = file_footer_pc;           //pointer to pc file footer
    }
    else if((file_size == FF7_PSX_SAVE_GAME_SIZE)&& ff7file.startsWith(PSX_SAVE_GAME_FILE_ID))
    {//This should catch just about any false positive named *-S*
       SG_SIZE          = FF7_PSX_SAVE_GAME_SIZE;
       SG_HEADER        = FF7_PSX_SAVE_GAME_HEADER;
       SG_FOOTER        = FF7_PSX_SAVE_GAME_FOOTER;
       SG_DATA_SIZE     = FF7_PSX_SAVE_GAME_DATA_SIZE;
       SG_SLOT_HEADER   = FF7_PSX_SAVE_GAME_SLOT_HEADER;
       SG_SLOT_FOOTER   = FF7_PSX_SAVE_GAME_SLOT_FOOTER;
       SG_SLOT_SIZE     = FF7_PSX_SAVE_GAME_SLOT_SIZE;
       SG_SLOT_NUMBER   = FF7_PSX_SAVE_GAME_SLOT_NUMBER;
       SG_TYPE          = "PSX";
       file_headerp     = file_header_psx;          //pointer to psx file header
       file_footerp     = file_footer_psx;          //pointer to psx file footer
    }
    else if((file_size == FF7_MC_SAVE_GAME_SIZE) && ff7file.startsWith(MC_SAVE_GAME_FILE_ID))
    {
       SG_SIZE          = FF7_MC_SAVE_GAME_SIZE;
       SG_HEADER        = FF7_MC_SAVE_GAME_HEADER;
       SG_FOOTER        = FF7_MC_SAVE_GAME_FOOTER;
       SG_DATA_SIZE     = FF7_MC_SAVE_GAME_DATA_SIZE;
       SG_SLOT_HEADER   = FF7_MC_SAVE_GAME_SLOT_HEADER;
       SG_SLOT_FOOTER   = FF7_MC_SAVE_GAME_SLOT_FOOTER;
       SG_SLOT_SIZE     = FF7_MC_SAVE_GAME_SLOT_SIZE;
       SG_SLOT_NUMBER   = FF7_MC_SAVE_GAME_SLOT_NUMBER;
       SG_TYPE          = "MC";
       file_headerp     = file_header_mc;           //pointer to mc file header
       file_footerp     = file_footer_mc;           //pointer to mc file footer
    }

    else if((file_size == FF7_PSV_SAVE_GAME_SIZE) && ff7file.startsWith(PSV_SAVE_GAME_FILE_ID))
    {//CAUTION: be sure we are loading the correct kind of psv, pSX uses the extension for it's state files.
       SG_SIZE          = FF7_PSV_SAVE_GAME_SIZE;
       SG_HEADER        = FF7_PSV_SAVE_GAME_HEADER;
       SG_FOOTER        = FF7_PSV_SAVE_GAME_FOOTER;
       SG_DATA_SIZE     = FF7_PSV_SAVE_GAME_DATA_SIZE;
       SG_SLOT_HEADER   = FF7_PSV_SAVE_GAME_SLOT_HEADER;
       SG_SLOT_FOOTER   = FF7_PSV_SAVE_GAME_SLOT_FOOTER;
       SG_SLOT_SIZE     = FF7_PSV_SAVE_GAME_SLOT_SIZE;
       SG_SLOT_NUMBER   = FF7_PSV_SAVE_GAME_SLOT_NUMBER;
       SG_TYPE          = "PSV";
       file_headerp     = file_header_psv;          //pointer to psv file header
       file_footerp     = file_footer_psv;          //pointer to psv file footer
    }
    else if((file_size ==FF7_PSP_SAVE_GAME_SIZE) && ff7file.startsWith(PSP_SAVE_GAME_FILE_ID))
    {
        SG_SIZE          = FF7_PSP_SAVE_GAME_SIZE;
        SG_HEADER        = FF7_PSP_SAVE_GAME_HEADER;
        SG_FOOTER        = FF7_PSP_SAVE_GAME_FOOTER;
        SG_DATA_SIZE     = FF7_PSP_SAVE_GAME_DATA_SIZE;
        SG_SLOT_HEADER   = FF7_PSP_SAVE_GAME_SLOT_HEADER;
        SG_SLOT_FOOTER   = FF7_PSP_SAVE_GAME_SLOT_FOOTER;
        SG_SLOT_SIZE     = FF7_PSP_SAVE_GAME_SLOT_SIZE;
        SG_SLOT_NUMBER   = FF7_PSP_SAVE_GAME_SLOT_NUMBER;
        SG_TYPE          = "PSP";
        file_headerp     = file_header_psp;          //pointer to psp file header
        file_footerp     = file_footer_psp;          //pointer to psp file footer
    }
    else if((file_size ==FF7_VGS_SAVE_GAME_SIZE) && ff7file.startsWith(VGS_SAVE_GAME_FILE_ID))
    {
        SG_SIZE          = FF7_VGS_SAVE_GAME_SIZE;
        SG_HEADER        = FF7_VGS_SAVE_GAME_HEADER;
        SG_FOOTER        = FF7_VGS_SAVE_GAME_FOOTER;
        SG_DATA_SIZE     = FF7_VGS_SAVE_GAME_DATA_SIZE;
        SG_SLOT_HEADER   = FF7_VGS_SAVE_GAME_SLOT_HEADER;
        SG_SLOT_FOOTER   = FF7_VGS_SAVE_GAME_SLOT_FOOTER;
        SG_SLOT_SIZE     = FF7_VGS_SAVE_GAME_SLOT_SIZE;
        SG_SLOT_NUMBER   = FF7_VGS_SAVE_GAME_SLOT_NUMBER;
        SG_TYPE          = "VGS";
        file_headerp     = file_header_vgs;          //pointer to vgs file header
        file_footerp     = file_footer_vgs;          //pointer to vgs file footer
    }
    else if((file_size ==FF7_DEX_SAVE_GAME_SIZE) && ff7file.startsWith(DEX_SAVE_GAME_FILE_ID))
    {
        SG_SIZE          = FF7_DEX_SAVE_GAME_SIZE;
        SG_HEADER        = FF7_DEX_SAVE_GAME_HEADER;
        SG_FOOTER        = FF7_DEX_SAVE_GAME_FOOTER;
        SG_DATA_SIZE     = FF7_DEX_SAVE_GAME_DATA_SIZE;
        SG_SLOT_HEADER   = FF7_DEX_SAVE_GAME_SLOT_HEADER;
        SG_SLOT_FOOTER   = FF7_DEX_SAVE_GAME_SLOT_FOOTER;
        SG_SLOT_SIZE     = FF7_DEX_SAVE_GAME_SLOT_SIZE;
        SG_SLOT_NUMBER   = FF7_DEX_SAVE_GAME_SLOT_NUMBER;
        SG_TYPE          = "DEX";
        file_headerp     = file_header_dex;          //pointer to dex file header
        file_footerp     = file_footer_dex;          //pointer to dex file footer
    }
    else{return false;}
    /*~~~~~~~~~~Start Load~~~~~~~~~~*/
    memcpy(file_headerp,ff7file.mid(0x0000,SG_HEADER),SG_HEADER);// collect header (0x09) bytes (PC), (0x00) bytes (PSX), (0x2000) bytes (MC)
    for (int i=0;i<SG_SLOT_NUMBER;i++)
    {
        int index = (SG_SLOT_SIZE*i) + SG_HEADER + SG_SLOT_HEADER;
        memcpy(hf[i].sl_header,ff7file.mid((SG_SLOT_SIZE*i) + (SG_HEADER + 0x0000),SG_SLOT_HEADER),SG_SLOT_HEADER);// collect slot header (0x00) bytes (PC), (0x0200) bytes (PSX), (0x0200) bytes (MC)
        temp = ff7file.mid(index,0x10f4);
        memcpy(&slot[i],temp,0x10f4);
        memcpy(hf[i].sl_footer,ff7file.mid((SG_SLOT_SIZE*i)+ (SG_HEADER+SG_SLOT_HEADER+SG_DATA_SIZE),SG_SLOT_FOOTER),SG_SLOT_FOOTER);// collect slot footer (0x00) bytes (PC), (0x0D0C) bytes (PSX), (0x0D0C) bytes (MC)
    }
    //memcpy(file_footerp,ff7file.mid(0x0000,SG_FOOTER),SG_FOOTER); LOAD FOOTER IF ITS THERE>! FIX INDEX.
    /*~~~~~~~End Load~~~~~~~~~~~~~~*/
    if (SG_TYPE == "PC")
    {
        if(slot[0].checksum != 0x0000 && slot[0].checksum != 0x4D1D){SG_Region_String[0]= "BASCUS-94163FF7-S01";} else {SG_Region_String[0].clear();}
        if(slot[1].checksum != 0x0000 && slot[1].checksum != 0x4D1D){SG_Region_String[1]= "BASCUS-94163FF7-S02";} else {SG_Region_String[1].clear();}
        if(slot[2].checksum != 0x0000 && slot[2].checksum != 0x4D1D){SG_Region_String[2]= "BASCUS-94163FF7-S03";} else {SG_Region_String[2].clear();}
        if(slot[3].checksum != 0x0000 && slot[3].checksum != 0x4D1D){SG_Region_String[3]= "BASCUS-94163FF7-S04";} else {SG_Region_String[3].clear();}
        if(slot[4].checksum != 0x0000 && slot[4].checksum != 0x4D1D){SG_Region_String[4]= "BASCUS-94163FF7-S05";} else {SG_Region_String[4].clear();}
        if(slot[5].checksum != 0x0000 && slot[5].checksum != 0x4D1D){SG_Region_String[5]= "BASCUS-94163FF7-S06";} else {SG_Region_String[5].clear();}
        if(slot[6].checksum != 0x0000 && slot[6].checksum != 0x4D1D){SG_Region_String[6]= "BASCUS-94163FF7-S07";} else {SG_Region_String[6].clear();}
        if(slot[7].checksum != 0x0000 && slot[7].checksum != 0x4D1D){SG_Region_String[7]= "BASCUS-94163FF7-S08";} else {SG_Region_String[7].clear();}
        if(slot[8].checksum != 0x0000 && slot[8].checksum != 0x4D1D){SG_Region_String[8]= "BASCUS-94163FF7-S09";} else {SG_Region_String[8].clear();}
        if(slot[9].checksum != 0x0000 && slot[9].checksum != 0x4D1D){SG_Region_String[9]= "BASCUS-94163FF7-S10";} else {SG_Region_String[9].clear();}
        if(slot[10].checksum != 0x0000 && slot[10].checksum != 0x4D1D){SG_Region_String[10]= "BASCUS-94163FF7-S11";} else {SG_Region_String[10].clear();}
        if(slot[11].checksum != 0x0000 && slot[11].checksum != 0x4D1D){SG_Region_String[11]= "BASCUS-94163FF7-S12";} else {SG_Region_String[11].clear();}
        if(slot[12].checksum != 0x0000 && slot[12].checksum != 0x4D1D){SG_Region_String[12]= "BASCUS-94163FF7-S13";} else {SG_Region_String[12].clear();}
        if(slot[13].checksum != 0x0000 && slot[13].checksum != 0x4D1D){SG_Region_String[13]= "BASCUS-94163FF7-S14";} else {SG_Region_String[13].clear();}
        if(slot[14].checksum != 0x0000 && slot[14].checksum != 0x4D1D){SG_Region_String[14]= "BASCUS-94163FF7-S15";} else {SG_Region_String[14].clear();}
    }

    else if (SG_TYPE == "PSX")
    {
        if((fileName.contains("00867")) || (fileName.contains("00869")) || (fileName.contains("00900")) ||
           (fileName.contains("94163")) || (fileName.contains("00700")) || (fileName.contains("01057")) ||
           (fileName.contains("00868")) )
        {
            QString string;
            string = fileName.mid(fileName.lastIndexOf("/")+1,fileName.lastIndexOf(".")-1-fileName.lastIndexOf("/"));
            SG_Region_String[0]= string.mid(string.lastIndexOf("BA")-1,string.lastIndexOf("FF7-S")+8);
        }
        else {SG_Region_String[0].clear();}
        for(int i=1;i<14;i++){clearslot(i);}
    }

    else if (SG_TYPE =="PSV")
    {
        SG_Region_String[0] = QString(ff7file.mid(0x64,19));
        for(int i=1;i<14;i++){clearslot(i);}
    }

    else if (SG_TYPE == "MC" || SG_TYPE =="PSP" || SG_TYPE == "VGS" ||SG_TYPE=="DEX")
    {
        QByteArray mc_header;
        int offset = 0;//raw psx card types
        if(SG_TYPE =="PSP"){offset = 0x80;}
        if(SG_TYPE =="VGS"){offset = 0x40;}
        if(SG_TYPE =="DEX"){offset = 0xF40;}
        mc_header = ff7file.mid(offset,SG_HEADER);
        int index=0;
        for(int i=0; i<15;i++)
        {
            index = (128*i) +138;
            SG_Region_String[i] = QString(mc_header.mid(index,19));
        }
    }
    else{return false;}
    filename = fileName;
    modified = false;
    return true;
  }

 bool FF7Save::SaveFile(const QString &fileName)
 {
    if(fileName.isEmpty()){return false;}
    FILE *pfile;
    pfile = fopen(fileName.toAscii(),"wb");
    if(pfile == NULL){return false;}
    fwrite(file_headerp,SG_HEADER,1,pfile);
    for(int si=0;si<SG_SLOT_NUMBER;si++)
    {
        fwrite(hf[si].sl_header,SG_SLOT_HEADER,1,pfile);
        fwrite(&slot[si],SG_DATA_SIZE,1,pfile);
        fwrite(hf[si].sl_footer,SG_SLOT_FOOTER,1,pfile);
    }
    fwrite(file_footerp,SG_FOOTER,1,pfile);
    fclose(pfile);
    fix_sum(fileName);
    modified = false;
    return true;
}
void FF7Save::fix_sum(const QString &fileName)
{
    void * memory;
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite )){return;}
    QDataStream out (&file);
    out.setByteOrder(QDataStream::LittleEndian);
    file.seek(0);//Set pointer to the Beggining
    QByteArray ff7savefile;
    ff7savefile = file.readAll(); //put all data in temp raw file
    memory = (void*) malloc(SG_SIZE);//Memory Allocation
    if (!memory){return;}
    file.seek(0);
    memcpy(memory,ff7savefile.mid(0x00000,SG_SIZE),SG_SIZE);
    //Do checksum foreach slot
    for(int i=0, checksum=0; i<SG_SLOT_NUMBER; i++)
    {
        char * data_pointer = ((char*)memory + SG_HEADER + SG_SLOT_SIZE*i + SG_SLOT_HEADER + 0x04);
        checksum = ff7__checksum(data_pointer); //2 Bytes checksum (a 16-bit Byte checksum)
        if(checksum != 0x4D1D) //if is a blank slot don't write checksum!
        {
            int index = SG_HEADER + SG_SLOT_SIZE*i + SG_SLOT_HEADER;
            file.seek(index);
            out << checksum;
        }
    }
    file.close();
    free(memory);
} 
int FF7Save::ff7__checksum( void* qw )
{
   int i = 0, t, d;
   long r = 0xFFFF, len = 4336;
   long pbit = 0x8000;
   char* b=(char*)qw;

   while( len-- ) {
      t = b[i++];
      r ^= t << 8;
      for(d=0;d<8;d++) {
         if( r & pbit )
            r = ( r << 1 ) ^ 0x1021;
         else
            r <<= 1;
      }
      r &= ( 1 << 16 ) - 1;
   }
   return (r^0xFFFF)&0xFFFF;
}
void FF7Save::clearslot(int rmslot)
{
    QByteArray temp;
    temp.fill(0x00,0x10f4);
    memcpy(hf[rmslot].sl_header,temp,SG_SLOT_HEADER);// clear the header..
    memcpy(&slot[rmslot],temp,0x10f4);
    memcpy(hf[rmslot].sl_footer,temp,SG_SLOT_FOOTER);// clear the footer..
    SG_Region_String[rmslot].clear();
    if(SG_TYPE =="MC" || SG_TYPE =="PSP" || SG_TYPE =="VGS" || SG_TYPE =="DEX")
    {//clean the mem card header if needed.
        int index = (128+(128*rmslot));
        if (SG_TYPE == "PSP"){index +=0x80;}
        else if (SG_TYPE == "VGS"){index +=0x40;}
        else if (SG_TYPE == "DEX"){index +=0xF40;}
        temp.resize(128);
        temp.fill(0x00);
        temp[0]=0xA0;
        temp[8]=0xFF;
        temp[9]=0xFF;
        temp[0x7F]=0xA0;
        memcpy(&file_headerp[index],temp,128);
    }
}
void FF7Save::fix_pc_bytemask(int s)
{
    quint8 mask=0;
    quint8 newheader[0x09] = {0x71,0x73,0x27,0x06,0x00,0x00,0x00,0x00,0x00};
    //calc 0x04 of the header (selected slot) no idea why they choose this way to do it but slot15 = 0xC2 , slot 14= 0xb2  and so on till slot2 = 0x01 and slot 01 0x00
    switch(s)
    {
        case 0: newheader[4]=0x00; break;
        case 1: newheader[4]=0x01; break;
        default:newheader[4]= (16 * (s-2))+2; break;
    };
    //calc 0x05 of the header (slots 1-8 empty?)
    for(int i=0;i<8;i++)
    {
        if(SG_Region_String[i].contains("00867") || SG_Region_String[i].contains("00869") ||
           SG_Region_String[i].contains("00900") || SG_Region_String[i].contains("94163") ||
           SG_Region_String[i].contains("00700") || SG_Region_String[i].contains("01057") ||
           SG_Region_String[i].contains("00868"))
        {
        mask |= (1<<i);
        }
    }
    newheader[5]=mask;
    mask=0;// reset for the next byte
    //calc 0x06 of the header (slot 9-15 empty?)
    for(int i=8;i<15;i++)
    {
        if(SG_Region_String[i].contains("00867") || SG_Region_String[i].contains("00869") ||
           SG_Region_String[i].contains("00900") || SG_Region_String[i].contains("94163") ||
           SG_Region_String[i].contains("00700") || SG_Region_String[i].contains("01057") ||
           SG_Region_String[i].contains("00868"))
        {
        mask |= (1<<(i-8));
        }
    }
    newheader[6]=mask;
    memcpy(file_headerp,newheader,9);
}
void FF7Save::fix_psx_header(int s)
{   //Time Has to be fixed in the header part of description string.
    if((slot[s].time/3600)>99){hf[s].sl_header[27]=0x58;hf[s].sl_header[29]=0x58;}
    else
    {
        hf[s].sl_header[27] = ((slot[s].time/3600)/10)+0x4F;
        hf[s].sl_header[29] = ((slot[s].time/3600)%10)+0x4F;
    }
    hf[s].sl_header[33] = ((slot[s].time/60%60)/10)+0x4F;
    hf[s].sl_header[35] = ((slot[s].time/60%60)%10)+0x4F;
}
void FF7Save::fix_vmc_header(void)
{//Set The Index Section Up.
    QByteArray mc_header_2;
    int index=2;

    if(SG_TYPE =="PSP"){for(int i=0; i<0x80; i++){mc_header_2.append(file_header_psp[i]);} index=0x82;}
    if(SG_TYPE =="VGS"){for(int i=0; i<0x40; i++){mc_header_2.append(file_header_vgs[i]);} index=0x42;}
    if(SG_TYPE =="DEX"){for(int i=0; i<0xF40; i++){mc_header_2.append(file_header_dex[i]);} index=0xF42;}
    quint8 xor_byte = 0x00;
    mc_header_2.append("MC");
    if(SG_TYPE =="MC"){for(int k=0; k<125;k++){mc_header_2.append(file_header_mc[k+index]);}}
    if(SG_TYPE =="PSP"){for(int k=0; k<125;k++){mc_header_2.append(file_header_psp[k+index]);}}
    if(SG_TYPE =="VGS"){for(int k=0; k<125;k++){mc_header_2.append(file_header_vgs[k+index]);}}
    if(SG_TYPE =="DEX"){for(int k=0; k<125;k++){mc_header_2.append(file_header_dex[k+index]);}}
    xor_byte= 0x00;
    if(SG_TYPE =="MC"){for(int x=0;x<127;x++){xor_byte^=mc_header_2[x];}}
    if(SG_TYPE =="PSP"){for(int x=128;x<256;x++){xor_byte^=mc_header_2[x];}}
    if(SG_TYPE =="VGS"){for(int x=64;x<192;x++){xor_byte^=mc_header_2[x];}}
    if(SG_TYPE =="DEX"){for(int x=0xF40;x<0x1000;x++){xor_byte^=mc_header_2[x];}}
    //write xor byte..
    mc_header_2.append(xor_byte);
    // thats a normal header
    for(int i=0;i<15;i++)
    {
        //calc xor byte..
        index= (128 +(128*i));
        if(SG_TYPE =="PSP"){index+=0x80;}
        if(SG_TYPE =="VGS"){index+=0x40;}
        if(SG_TYPE =="DEX"){index+=0xF40;}
        if(SG_Region_String[i].contains("00867") ||SG_Region_String[i].contains("00869") ||
           SG_Region_String[i].contains("00900") ||SG_Region_String[i].contains("94163") ||
           SG_Region_String[i].contains("00700") ||SG_Region_String[i].contains("01057") ||
           SG_Region_String[i].contains("00868"))
        {
           QByteArray temp;
           temp.resize(10);
           temp[0]=0x51;temp[1]=0x00;temp[2]=0x00;temp[3]=0x00;temp[4]=0x00;
           temp[5]=0x20;temp[6]=0x00;temp[7]=0x00;temp[8]=0xFF;temp[9]=0xFF;
           mc_header_2.append(temp);
           mc_header_2.append(SG_Region_String[i]);
           temp.resize(98);
           for(int f=0;f<98;f++){temp[f]=0x00;}
           mc_header_2.append(temp);
           xor_byte = 0x00;
           for(int x=0;x<127;x++){xor_byte^=mc_header_2[x+index];}
           mc_header_2.append(xor_byte);

           if(SG_Region_String[i].endsWith("FF7-S01"))
           {for(int P=0;P<512;P++)
               {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S01[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }

           if(SG_Region_String[i].endsWith("FF7-S02"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S02[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(SG_Region_String[i].endsWith("FF7-S03"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S03[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(SG_Region_String[i].endsWith("FF7-S04"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S04[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(SG_Region_String[i].endsWith("FF7-S05"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S05[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(SG_Region_String[i].endsWith("FF7-S06"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S06[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           if(SG_Region_String[i].endsWith("FF7-S07"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S07[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(SG_Region_String[i].endsWith("FF7-S08"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S08[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(SG_Region_String[i].endsWith("FF7-S09"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S09[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(SG_Region_String[i].endsWith("FF7-S10"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S10[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(SG_Region_String[i].endsWith("FF7-S11"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S11[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(SG_Region_String[i].endsWith("FF7-S12"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S12[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           if(SG_Region_String[i].endsWith("FF7-S13"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S13[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(SG_Region_String[i].endsWith("FF7-S14"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S14[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           if(SG_Region_String[i].endsWith("FF7-S15"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S15[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           fix_psx_header(i);//fix header in current psx slot
        } // write string if found
        else if(SG_Region_String[i].isEmpty() || SG_Region_String[i].isNull())
        {   //QString empty_header = ;
            mc_header_2.append("\xA0\x00\x00\x00\x00\x00\x00\x00\xFF\xFF",10);
            for (int j=0;j<117;j++){mc_header_2.append('\x00');}
            mc_header_2.append('\xA0');
        }
        else
        {//Write What Ever is in the Header (Non ff7 data)
            if(SG_TYPE =="MC"){for(int j=0;j<128;j++){mc_header_2.append(file_header_mc[index+j]);}}
            if(SG_TYPE =="PSP"){for(int j=0;j<128;j++){mc_header_2.append(file_header_psp[index+j]);}}
            if(SG_TYPE =="VGS"){for(int j=0;j<128;j++){mc_header_2.append(file_header_vgs[index+j]);}}
            if(SG_TYPE =="DEX"){for(int j=0;j<128;j++){mc_header_2.append(file_header_dex[index+j]);}}
        }
    }

    if(SG_TYPE =="MC")
    {
        index=2048;
        for(int i=0;i<6143;i++){mc_header_2.append(file_header_mc[index+i]);}// fill the remainder
        memcpy(file_header_mc,mc_header_2,0x2000);
    }
    if(SG_TYPE =="PSP")
    {
        index=2048+0x80;
        for(int i=0;i<6143;i++){mc_header_2.append(file_header_psp[index+i]);}// fill the remainder
        memcpy(file_header_psp,mc_header_2,0x2080);
        //PUT PSP CHECKSUMING HERE ..
    }
    if(SG_TYPE =="VGS")
    {
        index=2048+0x40;
        for(int i=0;i<6143;i++){mc_header_2.append(file_header_vgs[index+i]);}// fill the remainder
        memcpy(file_header_vgs,mc_header_2,0x2040);
    }
    if(SG_TYPE =="DEX")
    {
        index=2048+0xF40;
        for(int i=0;i<6143;i++){mc_header_2.append(file_header_dex[index+i]);}// fill the remainder
        memcpy(file_header_dex,mc_header_2,0x2F40);
    }
}  

bool FF7Save::Export_PC(const QString &fileName)
{
  if(fileName.isEmpty()){return false;}// catch if Cancel is pressed
  if(SG_TYPE !="PC")
  {
    /*RESET CONTROLLS LATER WHEN IMPLIMENTED!!!*/
    SG_SIZE          = FF7_PC_SAVE_GAME_SIZE;
    SG_HEADER        = FF7_PC_SAVE_GAME_HEADER;
    SG_FOOTER        = FF7_PC_SAVE_GAME_FOOTER;
    SG_DATA_SIZE     = FF7_PC_SAVE_GAME_DATA_SIZE;
    SG_SLOT_HEADER   = FF7_PC_SAVE_GAME_SLOT_HEADER;
    SG_SLOT_FOOTER   = FF7_PC_SAVE_GAME_SLOT_FOOTER;
    SG_SLOT_SIZE     = FF7_PC_SAVE_GAME_SLOT_SIZE;
    SG_SLOT_NUMBER   = FF7_PC_SAVE_GAME_SLOT_NUMBER;
    SG_TYPE          = "PC";
    file_headerp     = file_header_pc;           //pointer to pc file header
    file_footerp     = file_footer_pc;           //pointer to pc file footer
    // Add File Header
    for(int i=0;i<9;i++){file_header_pc[i]= PC_SAVE_GAME_FILE_HEADER[i];}
  }
  for(int si=0;si<15;si++)//clean up saves and fix time for Pal Saves.
  {
    if (SG_Region_String[si].contains("94163") ||  SG_Region_String[si].contains("00700") || SG_Region_String[si].contains("01057"))
    {//NTSC FF7 DATA.
      fix_pc_bytemask(si);
    }
  
    else if(SG_Region_String[si].contains("00867") || SG_Region_String[si].contains("00868") || 
	    SG_Region_String[si].contains("00869") || SG_Region_String[si].contains("00900"))
    {//PAL FF7 DATA , FIX PLAY TIME THEN SAVE
      slot[si].time = (slot[si].time*1.2);
      slot[si].desc.time = slot[si].time;
      fix_pc_bytemask(si);
    }
    
    else{clearslot(si);}
  }
    if(SaveFile(fileName)){return true;}
    else {return false;}
}

bool FF7Save::Export_PSX(const QString &fileName)
{
  if(fileName.isEmpty()){return false;}
  if(SG_TYPE != "PSX")
  {
    /* RESET CONTROLS LATER WHEN IMPLIMENTED!!!!!!*/
    SG_SIZE          = FF7_PSX_SAVE_GAME_SIZE;
    SG_HEADER        = FF7_PSX_SAVE_GAME_HEADER;
    SG_FOOTER        = FF7_PSX_SAVE_GAME_FOOTER;
    SG_DATA_SIZE     = FF7_PSX_SAVE_GAME_DATA_SIZE;
    SG_SLOT_HEADER   = FF7_PSX_SAVE_GAME_SLOT_HEADER;
    SG_SLOT_FOOTER   = FF7_PSX_SAVE_GAME_SLOT_FOOTER;
    SG_SLOT_SIZE     = FF7_PSX_SAVE_GAME_SLOT_SIZE;
    SG_SLOT_NUMBER   = FF7_PSX_SAVE_GAME_SLOT_NUMBER;
    SG_TYPE          = "PSX";
    file_headerp     = file_header_psx;           //pointer to psx file header
    file_footerp     = file_footer_psx;           //pointer to psx file footer
  }
  if(fileName.endsWith("S01")){for(int i=0;i<256;i++)	  {hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S01[i];}}
  else if(fileName.endsWith("S02")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S02[i];}}
  else if(fileName.endsWith("S03")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S03[i];}}
  else if(fileName.endsWith("S04")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S04[i];}}
  else if(fileName.endsWith("S05")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S05[i];}}
  else if(fileName.endsWith("S06")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S06[i];}}
  else if(fileName.endsWith("S07")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S07[i];}}
  else if(fileName.endsWith("S08")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S08[i];}}
  else if(fileName.endsWith("S09")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S09[i];}}
  else if(fileName.endsWith("S10")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S10[i];}}
  else if(fileName.endsWith("S11")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S11[i];}}
  else if(fileName.endsWith("S12")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S12[i];}}
  else if(fileName.endsWith("S13")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S13[i];}}
  else if(fileName.endsWith("S14")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S14[i];}}
  else if(fileName.endsWith("S15")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S15[i];}}
  else{return false;}
  for(int i=0; i<SG_SLOT_FOOTER;i++){hf[0].sl_footer[i] =0x00;} //CLEAN FOOTER
  fix_psx_header(0);
  if(SaveFile(fileName)){return true;}
  else{return false;}
}

bool FF7Save::Export_VMC(const QString &fileName)
{
  if(fileName.isEmpty()){return false;}
  if(SG_TYPE != "MC")
  {
    /* RESET CONTROLS LATER WHEN IMPLIMENTED!!!!!!*/
    SG_SIZE          = FF7_MC_SAVE_GAME_SIZE;
    SG_HEADER        = FF7_MC_SAVE_GAME_HEADER;
    SG_FOOTER        = FF7_MC_SAVE_GAME_FOOTER;
    SG_DATA_SIZE     = FF7_MC_SAVE_GAME_DATA_SIZE;
    SG_SLOT_HEADER   = FF7_MC_SAVE_GAME_SLOT_HEADER;
    SG_SLOT_FOOTER   = FF7_MC_SAVE_GAME_SLOT_FOOTER;
    SG_SLOT_SIZE     = FF7_MC_SAVE_GAME_SLOT_SIZE;
    SG_SLOT_NUMBER   = FF7_MC_SAVE_GAME_SLOT_NUMBER;
    SG_TYPE          = "MC";
    file_headerp     = file_header_mc;           //pointer to mc file header
    file_footerp     = file_footer_mc;           //pointer to mc file footer
  }
  fix_vmc_header();
  if(SaveFile(fileName)){return true;}
  else{return false;}
}

bool FF7Save::Export_VGS(const QString &fileName)
{
  if(fileName.isEmpty()){return false;}
  if(SG_TYPE != "VGS")
  {
    /* RESET CONTROLS LATER WHEN IMPLIMENTED!!!!!!*/
    SG_SIZE          = FF7_VGS_SAVE_GAME_SIZE;
    SG_HEADER        = FF7_VGS_SAVE_GAME_HEADER;
    SG_FOOTER        = FF7_VGS_SAVE_GAME_FOOTER;
    SG_DATA_SIZE     = FF7_VGS_SAVE_GAME_DATA_SIZE;
    SG_SLOT_HEADER   = FF7_VGS_SAVE_GAME_SLOT_HEADER;
    SG_SLOT_FOOTER   = FF7_VGS_SAVE_GAME_SLOT_FOOTER;
    SG_SLOT_SIZE     = FF7_VGS_SAVE_GAME_SLOT_SIZE;
    SG_SLOT_NUMBER   = FF7_VGS_SAVE_GAME_SLOT_NUMBER;
    SG_TYPE          = "VGS";
    file_headerp     = file_header_vgs;           //pointer to mc file header
    file_footerp     = file_footer_vgs;           //pointer to mc file footer
    //fill the Header With The Needed Default
    file_header_vgs[0] =0x56;
    file_header_vgs[1] =0x67;
    file_header_vgs[2] =0x73;
    file_header_vgs[3] =0x4D;
    file_header_vgs[4] =0x01;
    file_header_vgs[8] =0x01;
    file_header_vgs[12] =0x01;
  }
  fix_vmc_header();
  if(SaveFile(fileName)){return true;}
  else{return false;}
}

bool FF7Save::Export_DEX(const QString &fileName)
{
  if(fileName.isEmpty()){return false;}
  if(SG_TYPE != "DEX")
  {
    /* RESET CONTROLS LATER WHEN IMPLIMENTED!!!!!!*/
    SG_SIZE          = FF7_DEX_SAVE_GAME_SIZE;
    SG_HEADER        = FF7_DEX_SAVE_GAME_HEADER;
    SG_FOOTER        = FF7_DEX_SAVE_GAME_FOOTER;
    SG_DATA_SIZE     = FF7_DEX_SAVE_GAME_DATA_SIZE;
    SG_SLOT_HEADER   = FF7_DEX_SAVE_GAME_SLOT_HEADER;
    SG_SLOT_FOOTER   = FF7_DEX_SAVE_GAME_SLOT_FOOTER;
    SG_SLOT_SIZE     = FF7_DEX_SAVE_GAME_SLOT_SIZE;
    SG_SLOT_NUMBER   = FF7_DEX_SAVE_GAME_SLOT_NUMBER;
    SG_TYPE          = "DEX";
    file_headerp     = file_header_dex;           //pointer to mc file header
    file_footerp     = file_footer_dex;           //pointer to mc file footer
    //default header..
    file_header_dex[0]=0x31;
    file_header_dex[1]=0x32;
    file_header_dex[2]=0x33;
    file_header_dex[3]=0x2D;
    file_header_dex[4]=0x34;
    file_header_dex[5]=0x35;
    file_header_dex[6]=0x36;
    file_header_dex[7]=0x2D;
    file_header_dex[8]=0x53;
    file_header_dex[9]=0x54;
    file_header_dex[10]=0x44;
    file_header_dex[18]=0x01;
    file_header_dex[20]=0x01;
    file_header_dex[21]=0x4D;
    file_header_dex[22]=0x51;
    for(int i=0x17;i<0x25;i++){file_header_dex[i]=0xA0;}
    file_header_dex[38]=0xFF;
  }
  fix_vmc_header();
  if(SaveFile(fileName)){return true;}
  else{return false;}
}


int FF7Save::len_file(void){return SG_SIZE;}
int FF7Save::len_file_header(void){return SG_HEADER;}//Return File Header length
int FF7Save::len_file_footer(void){return SG_FOOTER;}//Return File Footer length
int FF7Save::len_core_save(void){return SG_DATA_SIZE;}//Return Slot length (data portion)
int FF7Save::len_slot_header(void){return SG_SLOT_HEADER;}//Return slot header length
int FF7Save::len_slot_footer(void){return SG_SLOT_FOOTER;}//Return slot footer length
int FF7Save::len_slot(void){return SG_SLOT_SIZE;}//Return Slot length
int FF7Save::number_slots(void){return SG_SLOT_NUMBER;}//Return number of slots in the file_footer_dex
QString FF7Save::type(void){return SG_TYPE;}// Returns the file type loaded.
void FF7Save::setType(QString type){SG_TYPE =type;}
