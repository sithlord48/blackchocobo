/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#include "FF7Save.h"
#include <QObject>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QCryptographicHash>
// This Class should contain NO Gui Parts
bool FF7Save::loadFile(const QString &fileName)
{
    // Return true if File Loaded and false if file not loaded.
    if(fileName.isEmpty()){return false;}// bail on empty string.
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){return false;}
    int file_size = file.size();
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~Set File Type Vars ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    //decide the file type
    if((file_size == FF7_PC_SAVE_GAME_SIZE)&& (file.peek(PC_SAVE_GAME_FILE_ID.length()))==PC_SAVE_GAME_FILE_ID){setType("PC");}
    else if((file_size == FF7_PSX_SAVE_GAME_SIZE)&& (file.peek(PSX_SAVE_GAME_FILE_ID.length()))==PSX_SAVE_GAME_FILE_ID){setType("PSX");}
    else if((file_size == FF7_MC_SAVE_GAME_SIZE)&& (file.peek(MC_SAVE_GAME_FILE_ID.length()))==MC_SAVE_GAME_FILE_ID){setType("MC");}
    else if((file_size == FF7_PSV_SAVE_GAME_SIZE)&& (file.peek(PSV_SAVE_GAME_FILE_ID.length()))==PSV_SAVE_GAME_FILE_ID){setType("PSV");}
    else if((file_size ==FF7_PSP_SAVE_GAME_SIZE)&& (file.peek(PSP_SAVE_GAME_FILE_ID.length()))==PSP_SAVE_GAME_FILE_ID){setType("PSP");}
    else if((file_size ==FF7_VGS_SAVE_GAME_SIZE)&& (file.peek(VGS_SAVE_GAME_FILE_ID.length()))==VGS_SAVE_GAME_FILE_ID){setType("VGS");}
    else if((file_size ==FF7_DEX_SAVE_GAME_SIZE)&& (file.peek(DEX_SAVE_GAME_FILE_ID.length()))==DEX_SAVE_GAME_FILE_ID){setType("DEX");}
    else{return false;}
    /*~~~~~~~~~~Start Load~~~~~~~~~~*/
    setFileHeader(file.read(SG_HEADER));
    for (int i=0;i<SG_SLOT_NUMBER;i++)
    {
        setSlotHeader(i,file.read(SG_SLOT_HEADER));
        setSlotFF7Data(i,file.read(SG_DATA_SIZE));
        setSlotFooter(i,file.read(SG_SLOT_FOOTER));
    }
    setFileFooter(file.read(SG_FOOTER));
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
           (fileName.contains("00868")))
        {
            QString string;
            string = fileName.mid(fileName.lastIndexOf("/")+1,fileName.lastIndexOf(".")-1-fileName.lastIndexOf("/"));
            SG_Region_String[0]= string.mid(string.lastIndexOf("BA")-1,string.lastIndexOf("FF7-S")+8);
        }
        else {SG_Region_String[0].clear();}
        for(int i=1;i<14;i++){clearSlot(i);}
    }

    else if (SG_TYPE =="PSV")
    {
        file.seek(0x64);
        SG_Region_String[0] = QString(file.read(19));
        for(int i=1;i<14;i++){clearSlot(i);}
    }

    else if (SG_TYPE == "MC" || SG_TYPE =="PSP" || SG_TYPE == "VGS" ||SG_TYPE=="DEX")
    {
        QByteArray mc_header;
        int offset = 0;//raw psx card types
        if(SG_TYPE =="PSP"){offset = 0x80;}
        if(SG_TYPE =="VGS"){offset = 0x40;}
        if(SG_TYPE =="DEX"){offset = 0xF40;}
        file.seek(offset);
        mc_header = file.read(SG_HEADER);
        int index=0;
        for(int i=0; i<15;i++)
        {
            index = (128*i) +138;
            setRegion(i,QString(mc_header.mid(index,19)));
        }

    }
    else{return false;}
    file.close();
    filename=fileName;
    setFileModified(false,0);
    return true;
}
QByteArray FF7Save::fileHeader(void)
{
    QByteArray temp;
    temp.setRawData(reinterpret_cast<char *>(file_headerp),SG_HEADER);
    return temp;
}

bool FF7Save::setFileHeader(QByteArray data)
{
    if(data.size() != SG_HEADER){return false;}
    else
    {
        memcpy(file_headerp,data,SG_HEADER);
        return true;
    }

}

QByteArray FF7Save::slotHeader(int s)
{
    QByteArray temp;
    temp.setRawData(reinterpret_cast<char *>(&hf[s].sl_header),0x0200);
    return temp;
}
bool FF7Save::setSlotHeader(int s, QByteArray data)
{
    if(s<0 || s>14){return false;}
    if(data.size()!=SG_SLOT_HEADER){return false;}
    memcpy(&hf[s].sl_header,data,SG_SLOT_HEADER);
    return true;
}

QByteArray FF7Save::fileFooter(void)
{
    QByteArray temp;
    temp.setRawData(reinterpret_cast<char *>(file_footerp),SG_FOOTER);
    return temp;
}

bool FF7Save::setFileFooter(QByteArray data)
{
    if(data.size() != SG_FOOTER){return false;}
    else
    {
        memcpy(file_footerp,data,SG_FOOTER);
        return true;
    }
}
QByteArray FF7Save::slotFooter(int s)
{
    QByteArray temp;
    temp.setRawData(reinterpret_cast<char *>(&hf[s].sl_footer),0xD0C);
    return temp;
}
bool FF7Save::setSlotFooter(int s, QByteArray data)
{
    if(s<0 || s>14){return false;}
    if(data.size()!=SG_SLOT_FOOTER){return false;}
    memcpy(&hf[s].sl_footer,data,SG_SLOT_FOOTER);
    return true;
}
QByteArray FF7Save::slotPsxRawData(int s)
{
    if(filename.isEmpty()){return QByteArray("\x00");}
    else
    {
        QByteArray temp;
        int blocks = psx_block_size(s);
        for(int i=0; i<blocks;i++)
        {
            temp.append(slotHeader(s));
            temp.append(slotFF7Data(s));
            temp.append(slotFooter(s));
            s= psx_block_next(s);
        }
            return temp;
    }
}
bool FF7Save::setSlotPsxRawData(int s, QByteArray data)
{
    if(s<0 || s>14){return false;}
    int blocks = data.length()/0x2000;

    for(int i=0; i< blocks ; i++)
    {//done once for each block
        int offset = (i*0x2000);
        int next = psx_block_next(s);
        setSlotHeader(s,data.mid(offset,0x0200));
        offset +=0x0200;
        setSlotFF7Data(s,data.mid(offset,0x10F4));
        offset +=0x10F4;
        setSlotFooter(s,data.mid(offset,0xD0C));
        s=next;
    }
    return true;
}
bool FF7Save::saveFile(const QString &fileName)
{
    if(fileName.isEmpty()){return false;}
    //fix our headers before saving
    if(type() =="PC"){/*PC Header Should be Fixed By Host*/}
    else if(type() == "PSX"){fix_psx_header(0);}
    else if(type() =="PSV"){fix_psv_header();}
    else{fix_vmc_header();}
    // write the file
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite)){return false;}
    file.write(fileHeader(),SG_HEADER);
    for(int si=0;si<SG_SLOT_NUMBER;si++)
    {
        file.write(slotHeader(si),SG_SLOT_HEADER);
        file.write(slotFF7Data(si),SG_DATA_SIZE);
        file.write(slotFooter(si),SG_SLOT_FOOTER);
    }
    file.write(fileFooter(),SG_FOOTER);
    file.close();
    fix_sum(fileName);
    filename=fileName;
    if(type()==("PC")){fixMetaData();}
    setFileModified(false,0);
    return true;
}
bool FF7Save::exportPC(const QString &fileName)
{
    if(fileName.isEmpty()){return false;}
    QString prev_type = SG_TYPE;
    if(SG_TYPE !="PC")
    {
      for(int i=0;i<15;i++){if(isFF7(i)){setControlMode(i,CONTROL_NORMAL);}}
      setType("PC");
      // Add File Header
      for(int i=0;i<9;i++){file_header_pc[i]= PC_SAVE_GAME_FILE_HEADER[i];}
      fix_pc_bytemask(0);//set first slot to 0
    }
    for(int i=0;i<15;i++)//clean up saves and fix time for Pal Saves.
    {
      if (isNTSC(i)){/*NTSC FF7 DATA.*/}
      else if(isPAL(i))
      {//PAL FF7 DATA , FIX PLAY TIME THEN SAVE
        slot[i].time = (slot[i].time*1.2);
        slot[i].desc.time = slot[i].time;
      }
      else{clearSlot(i);}
    }
    if(saveFile(fileName))
    {
        setType(prev_type);
        setFileModified(false,0);
        return true;
    }
    else
    {
        setType(prev_type);
        return false;
    }
}
bool FF7Save::exportPSX(int s,const QString &fileName)
{
    if(fileName.isEmpty()){return false;}
    int blocks=1;
    QString prev_type = SG_TYPE;
    if(SG_TYPE != "PSX")
    {
       if(isFF7(s)){setControlMode(s,CONTROL_NORMAL);}
       blocks = psx_block_size(s);
       setType("PSX");
    }
    if(isFF7(s))
    {
        if(fileName.endsWith("S01")){for(int i=0;i<256;i++)	  {hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S01[i];}}
        else if(fileName.endsWith("S02")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S02[i];}}
        else if(fileName.endsWith("S03")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S03[i];}}
        else if(fileName.endsWith("S04")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S04[i];}}
        else if(fileName.endsWith("S05")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S05[i];}}
        else if(fileName.endsWith("S06")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S06[i];}}
        else if(fileName.endsWith("S07")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S07[i];}}
        else if(fileName.endsWith("S08")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S08[i];}}
        else if(fileName.endsWith("S09")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S09[i];}}
        else if(fileName.endsWith("S10")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S10[i];}}
        else if(fileName.endsWith("S11")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S11[i];}}
        else if(fileName.endsWith("S12")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S12[i];}}
        else if(fileName.endsWith("S13")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S13[i];}}
        else if(fileName.endsWith("S14")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S14[i];}}
        else if(fileName.endsWith("S15")){for(int i=0;i<256;i++){hf[s].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S15[i];}}
        else{/*user ERROR*/}
        for(int i=0; i<SG_SLOT_FOOTER;i++){hf[s].sl_footer[i] =0x00;} //CLEAN FOOTER
        fix_psx_header(s);//only fix time for FF7 Slots.
    }
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite)){return false;}
    file.write(fileHeader(),SG_HEADER);
    for(int i=0;i<blocks;i++)
    {
        int next = psx_block_next(s);
        file.write(slotHeader(s),SG_SLOT_HEADER);
        file.write(slotFF7Data(s),SG_DATA_SIZE);
        file.write(slotFooter(s),SG_SLOT_FOOTER);
        s=next;
    }
    file.write(fileFooter(),SG_FOOTER);
    file.close();
    fix_sum(fileName);
    setType(prev_type);
    return true;
}

bool FF7Save::exportVMC(const QString &fileName)
{
  if(fileName.isEmpty()){return false;}
  QString prev_type = SG_TYPE;
  if(SG_TYPE != "MC")
  {
    for(int i=0;i<15;i++){if(isFF7(i)){setControlMode(i,CONTROL_NORMAL);}}
    setType("MC");
  }
  fix_vmc_header();
  if(saveFile(fileName))
  {
      setType(prev_type);
      return true;
  }
  else
  {
      setType(prev_type);
      return false;
  }
}
bool FF7Save::exportVGS(const QString &fileName)
{
  if(fileName.isEmpty()){return false;}
  QString prev_type = SG_TYPE;
  if(SG_TYPE != "VGS")
  {
     for(int i=0;i<15;i++){if(isFF7(i)){setControlMode(i,CONTROL_NORMAL);}}
    setType("VGS");//fill the Header With The Needed Default
    file_header_vgs[0] =0x56;
    file_header_vgs[1] =0x67;
    file_header_vgs[2] =0x73;
    file_header_vgs[3] =0x4D;
    file_header_vgs[4] =0x01;
    file_header_vgs[8] =0x01;
    file_header_vgs[12] =0x01;
  }
  fix_vmc_header();
  if(saveFile(fileName))
  {
      setType(prev_type);
      return true;
  }
  else
  {
      setType(prev_type);
      return false;
  }
}
bool FF7Save::exportDEX(const QString &fileName)
{
  if(fileName.isEmpty()){return false;}
  QString prev_type = SG_TYPE;
  if(SG_TYPE != "DEX")
  {
      for(int i=0;i<15;i++){if(isFF7(i)){setControlMode(i,CONTROL_NORMAL);}}
      setType("DEX");
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
  if(saveFile(fileName))
  {
      setType(prev_type);
      return true;
  }
  else
  {
      setType(prev_type);
      return false;
  }
}
void FF7Save::importPSX(int s,const QString &fileName)
{
    if(fileName.isEmpty()){return;}
    else
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly)){return;}
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        if((file.size() ==FF7_PSX_SAVE_GAME_SIZE) && ff7file.startsWith(PSX_SAVE_GAME_FILE_ID))
        {
            QByteArray temp; // create a temp to be used when needed
            int index = 0x200;
            temp = ff7file.mid(index,0x10f4);
            memcpy(&slot[s],temp,0x10f4);
            if((fileName.contains("00867")) || (fileName.contains("00869")) || (fileName.contains("00900")) ||
              (fileName.contains("94163")) || (fileName.contains("00700")) || (fileName.contains("01057")) || (fileName.contains("00868")))
            {
                QString string;
                string = fileName.mid(fileName.lastIndexOf("/")+1,fileName.lastIndexOf(".")-1-fileName.lastIndexOf("/"));
                setRegion(s,string.mid(string.lastIndexOf("BA")-1,string.lastIndexOf("FF7-S")+8));
            }
            else {setRegion(s,"");}
            setFileModified(true,s);
         }
         else{return;}
     }
}
void FF7Save::importPSV(int s,const QString &fileName)
{
    if(fileName.isEmpty()){return;}
    else
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly)){return;}
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        QByteArray temp; // create a temp to be used when needed
        if((file.size() ==FF7_PSV_SAVE_GAME_SIZE) && ff7file.startsWith(PSV_SAVE_GAME_FILE_ID))
        {
            int index = 0x284;
            temp = ff7file.mid(index,0x10f4);
            memcpy(&slot[s],temp,0x10f4);
            setRegion(s,QString(ff7file.mid(0x64,19)));
            setFileModified(true,s);
        }//Parse slot data....
        else{return;}
    }
}
void FF7Save::clearSlot(int rmslot)
{
    if(isSlotEmpty(rmslot)){return;}
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
        setFileModified(true,rmslot);
    }
}
bool FF7Save::exportCharacter(int s,int char_num,QString fileName)
{
        QFile file(fileName);
        if(!file.open(QIODevice::ReadWrite)){return false;}
        file.write(rawCharacterData(s,char_num),132);
        file.close();
        return true;
}
void FF7Save::importCharacter(int s,int char_num,QByteArray new_char){memcpy(&slot[s].chars[char_num],new_char.data(),132);setFileModified(true,s);}

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
quint16 FF7Save::itemDecode( quint16 itemraw )
{
    quint16 item;
    #ifdef Q_BYTE_ORDER
        #if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
            item = itemraw;
        #elif Q_BYTE_ORDER == Q_BIG_ENDIAN
            item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);
        #else
        int one = 1;
        if (*(char *)&one){
            /******************************************************************************************/
            /* Little-Endian (Do Nothing, No Change)                                                  */
            /* ITEMRAW:                                                                               */
            /* Itemraw Format: QQQQQQQXXXXXXXXX                                                       */
            /* ITEM:                                                                                  */
            /* Item Format: QQQQQQQXXXXXXXXX                                                          */
            /******************************************************************************************/
            item = itemraw;
        } else {
            /***********************************--*****************************************************/
            /* Big-Endian (Do things, Format Change)                                                  */
            /* ITEMRAW:                                                                               */
            /* Itemraw Format: XXXXXXXXQQQQQQQX                                                       */
            /* ITEM:                                                                                  */
            /* Left Shift&Mask itemraw 8bits:  QQQQQQQX00000000 & 1111111100000000 = QQQQQQQX00000000 */
            /* Right Shift&Mask itemraw 8bits: 00000000XXXXXXXX & 0000000011111111 = 00000000XXXXXXXX */
            /* Then OR them:                   QQQQQQQX00000000 | 00000000XXXXXXXX = QQQQQQQXXXXXXXXX */
            /* Item Format: QQQQQQQXXXXXXXXX                                                          */
            /******************************************************************************************/
            item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);
        }
        #endif
    #else
        int one = 1;
        if (*(char *)&one){
            item = itemraw;
        } else {
            item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);
        }
    #endif

    return item;
}
quint16 FF7Save::itemEncode( quint16 id, quint8 qty )
{
    quint16 item,itemraw;
    #ifdef Q_BYTE_ORDER
        #if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
            item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
            itemraw = item;
        #elif Q_BYTE_ORDER == Q_BIG_ENDIAN
            item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
            itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
        #else
            int one = 1;
            if (*(char *)&one) {
                /******************************************************************************************/
                /* Little-Endian                                                                          */
                /* ITEM:                                                                                  */
                /* Item Format: QQQQQQQXXXXXXXXX                                                          */
                /* Left Shift&Mask qty 9bits: QQQQQQQ000000000 & 1111111000000000 = QQQQQQQ000000000      */
                /* Right Mask id 9bits:              XXXXXXXXX & 0000000111111111 = 0000000XXXXXXXXX      */
                /* Then OR them:              QQQQQQQ000000000 | 0000000XXXXXXXXX = QQQQQQQXXXXXXXXX      */
                /* ITEMRAW:                                                                               */
                /* Itemraw Format: QQQQQQQXXXXXXXXX                                                       */
                /******************************************************************************************/
                item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
                itemraw = item;
            } else {
                /******************************************************************************************/
                /* Big-Endian                                                                             */
                /* ITEM:                                                                                  */
                /* Left Shift&Mask qty 9bits:   QQQQQQQ000000000 & 1111111000000000 = QQQQQQQ000000000    */
                /* Right Mask id 9bits:         0000000XXXXXXXXX & 0000000111111111 = 0000000XXXXXXXXX    */
                /* Then OR them:                QQQQQQQ000000000 | 0000000XXXXXXXXX = QQQQQQQXXXXXXXXX    */
                /* Item Format: QQQQQQQXXXXXXXXX                                                          */
                /* ITEMRAW:                                                                               */
                /* Left Shift&Mask item 8bits:  QQQQQQQX00000000 & 1111111100000000 = QQQQQQQX00000000    */
                /* Right Shift&Mask item 8bits: 00000000XXXXXXXX & 0000000011111111 = 00000000XXXXXXXX    */
                /* Then OR them:                QQQQQQQX00000000 | 00000000XXXXXXXX = QQQQQQQXXXXXXXXX    */
                /* Itemraw Format: XXXXXXXXQQQQQQQX                                                       */
                /******************************************************************************************/
                item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
                itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
            }
        #endif
    #else
        int one = 1;
        if (*(char *)&one)
        {
            item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
            itemraw = item;
        }
        else
        {
            item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
            itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
        }
    #endif

    return itemraw;
}
void FF7Save::setItem(int s,int item_num,quint16 rawitem)
{
    if(region(s).contains("SLPS-00700")){if(itemQty(rawitem)>99){if(itemId(rawitem) != 0x1FF){rawitem = itemEncode(itemId(rawitem),99);}}}
    //Item Qty over 99 on SLPS-00700 Causes an Error Durring Battle and break all items.
    //Above Is to Check for and fix, since im sure no one wants to lose all their items.
    slot[s].items[item_num]=rawitem;
    setFileModified(true,s);
}
void FF7Save::setItem(int s,int item_num,quint16 new_id,quint8 new_qty)
{
    if(region(s).contains("SLPS-00700")){if(new_qty>99){if(new_id != 0x1FF){new_qty = 99;}}}
    //Item Qty over 99 on SLPS-00700 Causes an Error Durring Battle and break all items.
    //Above Is to Check for and fix, since im sure no one wants to lose all their items.
    slot[s].items[item_num]= itemEncode(new_id,new_qty);
    setFileModified(true,s);
}

quint16 FF7Save::item(int s,int item_num){return slot[s].items[item_num];}
QList<quint16> FF7Save::items(int s)
{
    QList<quint16> item_list;
    for (int i=0;i<320;i++){item_list.append(slot[s].items[i]);}
    return item_list;
}

void FF7Save::setItems(int s,QList<quint16> items)
{
    if(region(s).contains("SLPS-00700"))
    {
        for(int i=0;i<320;i++)
        {
            if(itemQty(items.at(i)) >99) {slot[s].items[i]= itemEncode(itemId(items.at(i)),99);}
            else{slot[s].items[i]= items.at(i);}
        }
    }
    else{for(int i=0;i<320;i++){slot[s].items[i]= items.at(i);}}
    setFileModified(true,s);
}

quint16 FF7Save::itemId(quint16 rawitem){return quint16((itemDecode(rawitem)) & 0x1FF);}
quint16 FF7Save::itemId(int s,int item_num){return quint16((itemDecode(slot[s].items[item_num])) & 0x1FF);}
quint8 FF7Save::itemQty(int s,int item_num){return quint8(((itemDecode(slot[s].items[item_num]))& 0xFE00) >>9);}
quint8 FF7Save::itemQty(quint16 rawitem){return quint8(((itemDecode(rawitem))& 0xFE00) >>9);}

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
        if(isFF7(i)){mask |= (1<<i);}
    }
    newheader[5]=mask;
    mask=0;// reset for the next byte
    //calc 0x06 of the header (slot 9-15 empty?)
    for(int i=8;i<15;i++)
    {
        if(isFF7(i)){mask |= (1<<(i-8));}
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
void FF7Save::fix_psv_header(void)
{
 /*do signing stuff*/
 fix_psx_header(0);//adjust time.
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
        if(isFF7(i))
        {
           QByteArray temp;
           temp.resize(10);
           temp[0]=0x51;temp[1]=0x00;temp[2]=0x00;temp[3]=0x00;temp[4]=0x00;
           temp[5]=0x20;temp[6]=0x00;temp[7]=0x00;temp[8]=0xFF;temp[9]=0xFF;
           mc_header_2.append(temp);
           mc_header_2.append(region(i));
           temp.resize(98);
           for(int f=0;f<98;f++){temp[f]=0x00;}
           mc_header_2.append(temp);
           xor_byte = 0x00;
           for(int x=0;x<127;x++){xor_byte^=mc_header_2[x+index];}
           mc_header_2.append(xor_byte);

           if(region(i).endsWith("FF7-S01"))
           {for(int P=0;P<512;P++)
               {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S01[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }

           if(region(i).endsWith("FF7-S02"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S02[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S03"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S03[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S04"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S04[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S05"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S05[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S06"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S06[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           if(region(i).endsWith("FF7-S07"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S07[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S08"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S08[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S09"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S09[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S10"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S10[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S11"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S11[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S12"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S12[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           if(region(i).endsWith("FF7-S13"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S13[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S14"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S14[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           if(region(i).endsWith("FF7-S15"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S15[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           fix_psx_header(i);//fix header in current psx slot
        } // write string if found
        else
        {
            if(psx_block_type(i)==0x52 || psx_block_type(i)==0x53)
            {
                if(SG_TYPE =="MC"){for(int j=0;j<128;j++){mc_header_2.append(file_header_mc[index+j]);}}
                if(SG_TYPE =="PSP"){for(int j=0;j<128;j++){mc_header_2.append(file_header_psp[index+j]);}}
                if(SG_TYPE =="VGS"){for(int j=0;j<128;j++){mc_header_2.append(file_header_vgs[index+j]);}}
                if(SG_TYPE =="DEX"){for(int j=0;j<128;j++){mc_header_2.append(file_header_dex[index+j]);}}
            }
            else if((region(i).isEmpty() || region(i).isNull()))
            {
                //QString empty_header = ;
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

QString FF7Save::region(int s){return SG_Region_String[s];}

void FF7Save::setRegion(int s ,QString new_region)
{
    if( (new_region =="USA") || (new_region == "NTSC-U") || (new_region =="1") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BASCUS-94163FF7-S01"; break;
            case 1: SG_Region_String[s] = "BASCUS-94163FF7-S02"; break;
            case 2: SG_Region_String[s] = "BASCUS-94163FF7-S03"; break;
            case 3: SG_Region_String[s] = "BASCUS-94163FF7-S04"; break;
            case 4: SG_Region_String[s] = "BASCUS-94163FF7-S05"; break;
            case 5: SG_Region_String[s] = "BASCUS-94163FF7-S06"; break;
            case 6: SG_Region_String[s] = "BASCUS-94163FF7-S07"; break;
            case 7: SG_Region_String[s] = "BASCUS-94163FF7-S08"; break;
            case 8: SG_Region_String[s] = "BASCUS-94163FF7-S09"; break;
            case 9: SG_Region_String[s] = "BASCUS-94163FF7-S10"; break;
            case 10: SG_Region_String[s] = "BASCUS-94163FF7-S11"; break;
            case 11: SG_Region_String[s] = "BASCUS-94163FF7-S12"; break;
            case 12: SG_Region_String[s] = "BASCUS-94163FF7-S13"; break;
            case 13: SG_Region_String[s] = "BASCUS-94163FF7-S14"; break;
            case 14: SG_Region_String[s] = "BASCUS-94163FF7-S15"; break;
        }
    }
    else if( (new_region =="UK") || (new_region =="PAL-E") || (new_region =="2") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BESCES-00867FF7-S01"; break;
            case 1: SG_Region_String[s] = "BESCES-00867FF7-S02"; break;
            case 2: SG_Region_String[s] = "BESCES-00867FF7-S03"; break;
            case 3: SG_Region_String[s] = "BESCES-00867FF7-S04"; break;
            case 4: SG_Region_String[s] = "BESCES-00867FF7-S05"; break;
            case 5: SG_Region_String[s] = "BESCES-00867FF7-S06"; break;
            case 6: SG_Region_String[s] = "BESCES-00867FF7-S07"; break;
            case 7: SG_Region_String[s] = "BESCES-00867FF7-S08"; break;
            case 8: SG_Region_String[s] = "BESCES-00867FF7-S09"; break;
            case 9: SG_Region_String[s] = "BESCES-00867FF7-S10"; break;
            case 10:SG_Region_String[s] = "BESCES-00867FF7-S11"; break;
            case 11:SG_Region_String[s] = "BESCES-00867FF7-S12"; break;
            case 12:SG_Region_String[s] = "BESCES-00867FF7-S13"; break;
            case 13:SG_Region_String[s] = "BESCES-00867FF7-S14"; break;
            case 14:SG_Region_String[s] = "BESCES-00867FF7-S15"; break;
        }
    }
    else if( (new_region =="French") || (new_region =="PAL-FR") || (new_region =="3") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BESCES-00868FF7-S01"; break;
            case 1: SG_Region_String[s] = "BESCES-00868FF7-S02"; break;
            case 2: SG_Region_String[s] = "BESCES-00868FF7-S03"; break;
            case 3: SG_Region_String[s] = "BESCES-00868FF7-S04"; break;
            case 4: SG_Region_String[s] = "BESCES-00868FF7-S05"; break;
            case 5: SG_Region_String[s] = "BESCES-00868FF7-S06"; break;
            case 6: SG_Region_String[s] = "BESCES-00868FF7-S07"; break;
            case 7: SG_Region_String[s] = "BESCES-00868FF7-S08"; break;
            case 8: SG_Region_String[s] = "BESCES-00868FF7-S09"; break;
            case 9: SG_Region_String[s] = "BESCES-00868FF7-S10"; break;
            case 10:SG_Region_String[s] = "BESCES-00868FF7-S11"; break;
            case 11:SG_Region_String[s] = "BESCES-00868FF7-S12"; break;
            case 12:SG_Region_String[s] = "BESCES-00868FF7-S13"; break;
            case 13:SG_Region_String[s] = "BESCES-00868FF7-S14"; break;
            case 14:SG_Region_String[s] = "BESCES-00868FF7-S15"; break;
        }
    }
    else if( (new_region =="German") || (new_region =="PAL-DE") || (new_region =="4") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BESCES-00869FF7-S01"; break;
            case 1: SG_Region_String[s] = "BESCES-00869FF7-S02"; break;
            case 2: SG_Region_String[s] = "BESCES-00869FF7-S03"; break;
            case 3: SG_Region_String[s] = "BESCES-00869FF7-S04"; break;
            case 4: SG_Region_String[s] = "BESCES-00869FF7-S05"; break;
            case 5: SG_Region_String[s] = "BESCES-00869FF7-S06"; break;
            case 6: SG_Region_String[s] = "BESCES-00869FF7-S07"; break;
            case 7: SG_Region_String[s] = "BESCES-00869FF7-S08"; break;
            case 8: SG_Region_String[s] = "BESCES-00869FF7-S09"; break;
            case 9: SG_Region_String[s] = "BESCES-00869FF7-S10"; break;
            case 10:SG_Region_String[s] = "BESCES-00869FF7-S11"; break;
            case 11:SG_Region_String[s] = "BESCES-00869FF7-S12"; break;
            case 12:SG_Region_String[s] = "BESCES-00869FF7-S13"; break;
            case 13:SG_Region_String[s] = "BESCES-00869FF7-S14"; break;
            case 14:SG_Region_String[s] = "BESCES-00869FF7-S15"; break;
        }
    }
    else if( (new_region =="Spanish")||(new_region =="PAL-ES")||(new_region == "5") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BESCES-00900FF7-S01"; break;
            case 1: SG_Region_String[s] = "BESCES-00900FF7-S02"; break;
            case 2: SG_Region_String[s] = "BESCES-00900FF7-S03"; break;
            case 3: SG_Region_String[s] = "BESCES-00900FF7-S04"; break;
            case 4: SG_Region_String[s] = "BESCES-00900FF7-S05"; break;
            case 5: SG_Region_String[s] = "BESCES-00900FF7-S06"; break;
            case 6: SG_Region_String[s] = "BESCES-00900FF7-S07"; break;
            case 7: SG_Region_String[s] = "BESCES-00900FF7-S08"; break;
            case 8: SG_Region_String[s] = "BESCES-00900FF7-S09"; break;
            case 9: SG_Region_String[s] = "BESCES-00900FF7-S10"; break;
            case 10:SG_Region_String[s] = "BESCES-00900FF7-S11"; break;
            case 11:SG_Region_String[s] = "BESCES-00900FF7-S12"; break;
            case 12:SG_Region_String[s] = "BESCES-00900FF7-S13"; break;
            case 13:SG_Region_String[s] = "BESCES-00900FF7-S14"; break;
            case 14:SG_Region_String[s] = "BESCES-00900FF7-S15"; break;
        }
    }
    else if( (new_region =="Japanese")||(new_region =="NTSC-J")||(new_region =="6") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BISLPS-00700FF7-S01"; break;
            case 1: SG_Region_String[s] = "BISLPS-00700FF7-S02"; break;
            case 2: SG_Region_String[s] = "BISLPS-00700FF7-S03"; break;
            case 3: SG_Region_String[s] = "BISLPS-00700FF7-S04"; break;
            case 4: SG_Region_String[s] = "BISLPS-00700FF7-S05"; break;
            case 5: SG_Region_String[s] = "BISLPS-00700FF7-S06"; break;
            case 6: SG_Region_String[s] = "BISLPS-00700FF7-S07"; break;
            case 7: SG_Region_String[s] = "BISLPS-00700FF7-S08"; break;
            case 8: SG_Region_String[s] = "BISLPS-00700FF7-S09"; break;
            case 9: SG_Region_String[s] = "BISLPS-00700FF7-S10"; break;
            case 10:SG_Region_String[s] = "BISLPS-00700FF7-S11"; break;
            case 11:SG_Region_String[s] = "BISLPS-00700FF7-S12"; break;
            case 12:SG_Region_String[s] = "BISLPS-00700FF7-S13"; break;
            case 13:SG_Region_String[s] = "BISLPS-00700FF7-S14"; break;
            case 14:SG_Region_String[s] = "BISLPS-00700FF7-S15"; break;
        }
    }
    else if( (new_region =="International")||(new_region =="NTSC-JI")||(new_region =="7") )
    {
        switch(s)
        {
            case 0:SG_Region_String[s] = "BISLPS-01057FF7-S01"; break;
            case 1:SG_Region_String[s] = "BISLPS-01057FF7-S02"; break;
            case 2:SG_Region_String[s] = "BISLPS-01057FF7-S03"; break;
            case 3:SG_Region_String[s] = "BISLPS-01057FF7-S04"; break;
            case 4:SG_Region_String[s] = "BISLPS-01057FF7-S05"; break;
            case 5:SG_Region_String[s] = "BISLPS-01057FF7-S06"; break;
            case 6:SG_Region_String[s] = "BISLPS-01057FF7-S07"; break;
            case 7:SG_Region_String[s] = "BISLPS-01057FF7-S08"; break;
            case 8:SG_Region_String[s] = "BISLPS-01057FF7-S09"; break;
            case 9:SG_Region_String[s] = "BISLPS-01057FF7-S10"; break;
            case 10:SG_Region_String[s] = "BISLPS-01057FF7-S11"; break;
            case 11:SG_Region_String[s] = "BISLPS-01057FF7-S12"; break;
            case 12:SG_Region_String[s] = "BISLPS-01057FF7-S13"; break;
            case 13:SG_Region_String[s] = "BISLPS-01057FF7-S14"; break;
            case 14:SG_Region_String[s] = "BISLPS-01057FF7-S15"; break;
        }
    }
    else{SG_Region_String[s]=new_region;}
    setFileModified(true,s);
}
void FF7Save::copySlot(int s){buffer_slot=slot[s]; buffer_region = SG_Region_String[s];}
void FF7Save::pasteSlot(int s)
{
    slot[s]=buffer_slot;
    //memcpy(&slot[s],&buffer_slot,0x10f4);
    SG_Region_String[s]= buffer_region;
    SG_Region_String[s].chop(2);
    switch(s)
    {
        case 0: SG_Region_String[s].append("01"); break;
        case 1: SG_Region_String[s].append("02"); break;
        case 2: SG_Region_String[s].append("03"); break;
        case 3: SG_Region_String[s].append("04"); break;
        case 4: SG_Region_String[s].append("05"); break;
        case 5: SG_Region_String[s].append("06"); break;
        case 6: SG_Region_String[s].append("07"); break;
        case 7: SG_Region_String[s].append("08"); break;
        case 8: SG_Region_String[s].append("09"); break;
        case 9: SG_Region_String[s].append("10"); break;
        case 10:SG_Region_String[s].append("11"); break;
        case 11:SG_Region_String[s].append("12"); break;
        case 12:SG_Region_String[s].append("13"); break;
        case 13:SG_Region_String[s].append("14"); break;
        case 14:SG_Region_String[s].append("15"); break;
    }
    if( (SG_TYPE =="MC") || (SG_TYPE =="PSP") || (SG_TYPE =="VGS") || (SG_TYPE =="DEX") ){fix_vmc_header();}

    setFileModified(true,s);
}

quint8 FF7Save::psx_block_type(int s)
{
    if(type()!="PC")
    {
        int index=128+(128*s);
        if (type() =="PSP"){index+=0x80;}
        else if (type() =="VGS"){index+=0x40;}
        else if (type() =="DEX"){index+=0xF40;}
        else {}
        return file_headerp[index];
    }
    else{return 0x00;}
}
void FF7Save::setPsx_block_type(int s,FF7Save::PSXBLOCKTYPE block_type)
{
    if(type()!="PC")
    {
        int index=128+(128*s);
        if (type() =="PSP"){index+=0x80;}
        else if (type() =="VGS"){index+=0x40;}
        else if (type() =="DEX"){index+=0xF40;}
        else {}
        file_headerp[index]= block_type;
    }
    else{return;}
}
void FF7Save::setPsx_block_next(int s,int next)
{
    if(type()=="PC"){return;}
    if(next <0 || next >14){return;}
    if(s <0 || s >14){return;}
    if(next==s){return;}

    int index=128+(128*s);
    if (type() =="PSP"){index+=0x80;}
    else if (type() =="VGS"){index+=0x40;}
    else if (type() =="DEX"){index+=0xF40;}
    else {}
    file_headerp[index+0x08]= next;
}

quint8 FF7Save::psx_block_next(int s)
{
    if(type()!="PC")
    {
        int index=128+(128*s);
        if (type() =="PSP"){index+=0x80;}
        else if (type() =="VGS"){index+=0x40;}
        else if (type() =="DEX"){index+=0xF40;}
        else {}
        return file_headerp[index+0x08];
    }
    else{return 0x00;}
}

void FF7Save::setPsx_block_size(int s,int blockSize)
{
    if(type()=="PC"){return;}
    if(s <0 || s >14){return;}
    if(blockSize>15){return;}

    int index=128+(128*s);
    if (type() =="PSP"){index+=0x80;}
    else if (type() =="VGS"){index+=0x40;}
    else if (type() =="DEX"){index+=0xF40;}

    qint32 filesize= blockSize *0x2000;
    file_headerp[index+0x04] = (filesize & 0xff);
    file_headerp[index+0x05] = (filesize & 0xff00) >> 8;
    file_headerp[index+0x06] = (filesize & 0xff0000) >> 16;
}
quint8 FF7Save::psx_block_size(int s)
{
    if(type() !="PC")
    {
        int index=128+(128*s);
        if (type() =="PSP"){index+=0x80;}
        else if (type() =="VGS"){index+=0x40;}
        else if (type() =="DEX"){index+=0xF40;}
        else {}
        qint32 value = file_headerp[index+0x04] | (file_headerp[index+0x05] << 8) | (file_headerp[index+0x06] <<16);
        return value/0x2000;
     }
    else{return 0; }
}
bool FF7Save::isFileModified(void){return fileChanged;}
bool FF7Save::isSlotModified(int s){return slotChanged[s];}
bool FF7Save::isSlotEmpty(int s)
{
    if(ff7__checksum(&slot[s])==0x4D1D){return true;}
    else{return false;}
}
bool FF7Save::isFF7(int s)
{
    if(region(s).contains("00867") || region(s).contains("00869") ||
       region(s).contains("00900") || region(s).contains("94163") ||
       region(s).contains("00700") || region(s).contains("01057") ||
       region(s).contains("00868"))
       {return true;}
    else{return false;}
}

bool FF7Save::isPAL(int s)
{
    if(region(s).contains("00867") || region(s).contains("00869") ||
       region(s).contains("00900") || region(s).contains("00868"))
       {return true;}
    else{return false;}
}

bool FF7Save::isNTSC(int s)
{
    if(region(s).contains("00700") || region(s).contains("94163") || region(s).contains("01057"))
       {return true;}
    else{return false;}
}
bool FF7Save::isJPN(int s)
{
    if(region(s).contains("00700") || region(s).contains("01057")){return true;}
    else{return false;}
}
int FF7Save::lenFile(void){return SG_SIZE;}
int FF7Save::lenFileHeader(void){return SG_HEADER;}//Return File Header length
int FF7Save::lenFileFooter(void){return SG_FOOTER;}//Return File Footer length
int FF7Save::lenCoreSave(void){return SG_DATA_SIZE;}//Return Slot length (data portion)
int FF7Save::lenSlotHeader(void){return SG_SLOT_HEADER;}//Return slot header length
int FF7Save::lenSlotFooter(void){return SG_SLOT_FOOTER;}//Return slot footer length
int FF7Save::lenSlot(void){return SG_SLOT_SIZE;}//Return Slot length
int FF7Save::numberOfSlots(void){return SG_SLOT_NUMBER;}//Return number of slots in the file_footer_dex
QString FF7Save::type(void){return SG_TYPE;}// Returns the file type loaded.

void FF7Save::setType(QString type)
{//set up all type stuffs...
    if(type == "PC")
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
    else if(type =="PSX")
    {
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
    else if(type=="MC")
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
    else if(type=="PSV")
    {
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
    else if(type=="PSP")
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
    else if(type=="VGS")
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
    else if(type=="DEX")
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
}
void FF7Save::newGame(int s,QString fileName)
{
    if(fileName.isEmpty() || fileName.isNull())
    {
        memcpy(&slot[s],&default_save,0x10F4);
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly)){return;}
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        QByteArray temp; // create a temp to be used when needed
        int index = 0x200;
        temp = ff7file.mid(index,0x10f4);
        memcpy(&slot[s],temp,0x10f4);
    }
    if(isJPN(s))
    {
        for(int c=0;c<9;c++){setCharName(s,c,"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff");}// clear all names.
        Text.init(1);
        setCharName(s,0,QString::fromUtf8("元ソルジャー"));
        setCharName(s,1,QString::fromUtf8("バレット"));
        setCharName(s,2,QString::fromUtf8("ティファ"));
        setCharName(s,3,QString::fromUtf8("エアリス"));
        setCharName(s,4,QString::fromUtf8("レッド⑬"));
        setCharName(s,5,QString::fromUtf8("ユフィ"));
        setCharName(s,6,QString::fromUtf8(""));
        setCharName(s,7,QString::fromUtf8("セフィロス"));
        setCharName(s,8,QString::fromUtf8("シド"));
    }
    else if(region(s).isEmpty()){setRegion(s,"BASCUS-94163FF7-S01");Text.init(0);}
    setFileModified(true,s);
}

void FF7Save::newGamePlus(int s,QString CharFileName,QString fileName)
{
    if(fileName.isEmpty() || fileName.isNull())
    {
        memcpy(&buffer_slot,&default_save,0x10F4);
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly)){return;}
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        QByteArray temp; // create a temp to be used when needed
        int index = 0x200;
        temp = ff7file.mid(index,0x10f4);
        memcpy(&buffer_slot,temp,0x10f4);
    }
    buffer_region = region(s);
    memcpy(&buffer_slot.desc,&slot[s].desc,0x44); // keep a old preview
    memcpy(&buffer_slot.colors,&slot[s].colors,12); // keep old colors.

    for(int i=0;i<9;i++) // keep all old character info.
    {
        if((i==6)||(i==7))// except we have to export cait sith and vincent.the game needs y.cloud/seppie,for the flash back.
        {
            QString outFile;
            if(i==6) //export cait sith. cait sith's stats are only generated when he joins the party.
            {
                    outFile.append(CharFileName);
                    outFile.append("-cait_sith");
                    if(type() != "PSX" || type() != "PSV")
                    {
                        outFile.append("-");
                        QString str;
                        str.setNum(s,10)+1;
                        outFile.append(str);
                    }
                }
            else if(i==7)// export vincent. vincent's stats are only generated when he joins the party.
                {
                    outFile.append(CharFileName);
                    outFile.append("-vincent");
                    if(type() != "PSX" || type() != "PSV")
                    {
                        outFile.append("-");
                        QString str;
                        str.setNum(s,10)+1;
                        outFile.append(str);
                    }
                }
            outFile.append(".char");
            exportCharacter(s,i,outFile);

        }
        else{memcpy(&buffer_slot.chars[i],&slot[s].chars[i],0x84);} // normal character
    }
    memcpy(&buffer_slot.items,&slot[s].items,640);// copy items
    memcpy(&buffer_slot.materias,&slot[s].materias,800); // copy materia
    buffer_slot.gil = slot[s].gil; // copy gil
    buffer_slot.battles = slot[s].battles; // copy battle count
    buffer_slot.runs = slot[s].runs; // copy run count
    buffer_slot.gp = slot[s].gp; // copy gp
    //copy chocobo info.
    buffer_slot.stables = slot[s].stables;
    buffer_slot.stablesoccupied = slot[s].stablesoccupied;
    buffer_slot.chocobomask = slot[s].chocobomask;
    for(int i=0;i<4;i++){buffer_slot.chocobos[i]=slot[s].chocobos[i];}
    memcpy(&buffer_slot.chocobonames,slot[s].chocobonames,36);
    memcpy(&buffer_slot.chocostaminas,slot[s].chocostaminas,12);
    for(int i=0;i<2;i++){buffer_slot.choco56[i]=slot[s].choco56[i];}
    // copy options
    buffer_slot.battlespeed =slot[s].battlespeed;
    buffer_slot.battlemspeed =slot[s].battlemspeed;
    buffer_slot.options=slot[s].options;
    memcpy(&buffer_slot.controller_map,slot[s].controller_map,16);
    buffer_slot.fieldmspeed = slot[s].fieldmspeed;
    //~~ buffer now ready to be copied~
    slot[s]=buffer_slot;
    setLocation(s,QT_TRANSLATE_NOOP("FF7Save","New Game +"));
    setFileModified(true,s);
}
quint8 FF7Save::disc(int s){return slot[s].disc;}
void FF7Save::setDisc(int s, int disc)
{
    if(disc<1 || disc>3){return;}
    else{slot[s].disc=disc;}
}
QByteArray FF7Save::slot_header(int s)
{
    QByteArray icon;
    if (type() != "PC") //we could have an icon. for all formats except for pc
    {
        for(int i=0;i<0x200;i++){icon.append(hf[s].sl_header[i]);}
    }
    else{icon.fill(0x00,0x200);}//fill with nothing if pc
    return icon;
}
QString FF7Save::charName(int s,int char_num)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int n=0;n<12;n++){text.append(slot[s].chars[char_num].name[n]);}
    return Text.toPC(text);
}
void FF7Save::setCharName(int s,int char_num,QString new_name)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    for (int i=0;i<12;i++){slot[s].chars[char_num].name[i] =0xFF;}
    QByteArray temp = Text.toFF7(new_name);
    memcpy(slot[s].chars[char_num].name,temp,temp.length());
    setFileModified(true,s);
}

QString FF7Save::descName(int s)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int n=0;n<16;n++){text.append(slot[s].desc.name[n]);}
    return Text.toPC(text);
}
void FF7Save::setDescName(int s,QString new_name)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    for (int i=0;i<16;i++){slot[s].desc.name[i] =0xFF;}
    QByteArray temp = Text.toFF7(new_name);
    memcpy(slot[s].desc.name,temp,temp.length());
    setFileModified(true,s);
}

QString FF7Save::descLocation(int s)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int n=0;n<24;n++){text.append(slot[s].desc.location[n]);}
    return Text.toPC(text);
}

void FF7Save::setDescLocation(int s, QString new_desc_location)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int i=0;i<32;i++){slot[s].desc.location[i] =0xFF;}
    QByteArray temp = Text.toFF7(new_desc_location);
    memcpy(slot[s].desc.location,temp,temp.length());
    setFileModified(true,s);
}

quint8 FF7Save::descLevel(int s){return slot[s].desc.level;}
quint8 FF7Save::descParty(int s,int char_num)
{
    return slot[s].desc.party[char_num];
}
quint16 FF7Save::descCurHP(int s){return slot[s].desc.curHP;}
quint16 FF7Save::descMaxHP(int s){return slot[s].desc.maxHP;}
quint16 FF7Save::descCurMP(int s){return slot[s].desc.curMP;}
quint16 FF7Save::descMaxMP(int s){return slot[s].desc.maxMP;}
quint32 FF7Save::descGil(int s){return slot[s].desc.gil;}
void FF7Save::setDescLevel(int s,int new_level){slot[s].desc.level=new_level;setFileModified(true,s);}

void FF7Save::setDescParty(int s,int char_num,quint8 new_id){slot[s].desc.party[char_num]=new_id;setFileModified(true,s);}
void FF7Save::setDescCurHP(int s,quint16 new_curHP){slot[s].desc.curHP=new_curHP;setFileModified(true,s);}
void FF7Save::setDescMaxHP(int s,quint16 new_maxHP){slot[s].desc.maxHP=new_maxHP;setFileModified(true,s);}
void FF7Save::setDescCurMP(int s,quint16 new_curMP){slot[s].desc.curMP=new_curMP;setFileModified(true,s);}
void FF7Save::setDescMaxMP(int s,quint16 new_maxMP){slot[s].desc.maxMP=new_maxMP;setFileModified(true,s);}
void FF7Save::setDescGil(int s,quint32 new_gil){slot[s].desc.gil=new_gil;setFileModified(true,s);}

quint32 FF7Save::descTime(int s){return slot[s].desc.time;}
void FF7Save::setDescTime(int s,quint32 new_time){slot[s].desc.time=new_time;setFileModified(true,s);}

quint32 FF7Save::time(int s) {return slot[s].time;}

void FF7Save::setTime(int s,quint32 new_time)
{
    slot[s].time=new_time;
    setDescTime(s,new_time);//set Desc also.
    setFileModified(true,s);
}

QString FF7Save::location(int s)
{

    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int n=0;n<24;n++){text.append(slot[s].location[n]);}
    return Text.toPC(text);
}
void FF7Save::setLocation(int s, QString new_location)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int i=0;i<24;i++){slot[s].location[i] =0xFF;}
    QByteArray temp = Text.toFF7(new_location);
    memcpy(slot[s].location,temp,temp.length());
    //and the description.
    setDescLocation(s,new_location);
    setFileModified(true,s);
}
quint8 FF7Save::love(int s,bool battle, FF7Save::LOVER who)
{
    if(battle)
    {
        switch(who)
        {
            case FF7Save::LOVE_BARRET: return slot[s].b_love.barret; break;
            case FF7Save::LOVE_TIFA: return slot[s].b_love.tifa; break;
            case FF7Save::LOVE_AERIS: return slot[s].b_love.aeris; break;
            case FF7Save::LOVE_YUFFIE: return slot[s].b_love.yuffie; break;
            default:  return 0; break;
        }
    }
    else
    {
        switch(who)
        {
            case FF7Save::LOVE_BARRET: return slot[s].love.barret; break;
            case FF7Save::LOVE_TIFA: return slot[s].love.tifa; break;
            case FF7Save::LOVE_AERIS: return slot[s].love.aeris; break;
            case FF7Save::LOVE_YUFFIE: return slot[s].love.yuffie; break;
            default:  return 0; break;
        }
    }
}
void FF7Save::setLove(int s,bool battle, FF7Save::LOVER who ,quint8 love)
{
    if(battle)
    {
        switch(who)
        {
            case FF7Save::LOVE_BARRET: slot[s].b_love.barret = love; break;
            case FF7Save::LOVE_TIFA: slot[s].b_love.tifa=love; break;
            case FF7Save::LOVE_AERIS:  slot[s].b_love.aeris=love; break;
            case FF7Save::LOVE_YUFFIE:  slot[s].b_love.yuffie=love; break;
            default: break;
        }
    }
    else
    {
        switch(who)
        {
            case FF7Save::LOVE_BARRET: slot[s].love.barret = love; break;
            case FF7Save::LOVE_TIFA: slot[s].love.tifa=love; break;
            case FF7Save::LOVE_AERIS:  slot[s].love.aeris=love; break;
            case FF7Save::LOVE_YUFFIE:  slot[s].love.yuffie=love; break;
            default: break;
        }
    }
}
bool  FF7Save::materiaCave(int s, FF7Save::MATERIACAVE cave)
{
    switch(cave)
    {
        case FF7Save::CAVE_MIME: return (slot[s].materiacaves &(1<<0)); break;
        case FF7Save::CAVE_HPMP: return (slot[s].materiacaves &(1<<1)); break;
        case FF7Save::CAVE_QUADMAGIC: return (slot[s].materiacaves & (1<<2)); break;
        case FF7Save::CAVE_KOTR: return (slot[s].materiacaves & (1<<3)); break;
        default: return false;
    }
}
void FF7Save::setMateriaCave(int s, FF7Save::MATERIACAVE cave, bool isEmpty)
{
    switch(cave)
    {
        case FF7Save::CAVE_MIME:
            if(isEmpty){slot[s].materiacaves |= (1<<0);}
            else{slot[s].materiacaves &= ~(1<<0);}
            setFileModified(true,s);
            break;

        case FF7Save::CAVE_HPMP:
            if(isEmpty){slot[s].materiacaves |= (1<<1);}
            else{slot[s].materiacaves &= ~(1<<1);}
            setFileModified(true,s);
            break;

        case FF7Save::CAVE_QUADMAGIC:
            if(isEmpty){slot[s].materiacaves |= (1<<2);}
            else{slot[s].materiacaves &= ~(1<<2);}
            setFileModified(true,s);
            break;

        case FF7Save::CAVE_KOTR:
            if(isEmpty){slot[s].materiacaves |= (1<<3);}
            else{slot[s].materiacaves &= ~(1<<3);}
            setFileModified(true,s);
            break;

        default: break;
    }
}
quint16 FF7Save::speedScore(int s, int rank)
{
    switch(rank)
    {
        case 1: return slot[s].coster_1; break;
        case 2: return slot[s].coster_2; break;
        case 3: return slot[s].coster_3; break;
        default:  return 0; break;
     }
}
void FF7Save::setSpeedScore(int s, int rank,quint16 score)
{
    switch(rank)
    {
        case 1: slot[s].coster_1=score; break;
        case 2: slot[s].coster_2=score; break;
        case 3: slot[s].coster_3=score; break;
        default: break;
     }
}

QString FF7Save::chocoName(int s,int choco_num)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int n=0;n<6;n++){text.append(slot[s].chocobonames[choco_num][n]);}
    return Text.toPC(text);
}
void FF7Save::setChocoName(int s,int choco_num,QString new_name)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray temp = Text.toFF7(new_name);
    for (int i=0;i<6;i++){slot[s].chocobonames[choco_num][i] =0xFF;}
    memcpy(slot[s].chocobonames[choco_num],temp,temp.length());
    setFileModified(true,s);
}
void FF7Save::setPartyMateria(int s, int mat_num, quint8 id,qint32 ap)
{//if invalid set to 0xFF
    if( (id<91) && ((ap>=0)&&(ap<=16777215)))
    {//Valid Id and Ap provided.
        slot[s].materias[mat_num].id = id;
        int a = (ap & 0xff);
        int b = (ap & 0xff00) >> 8;
        int c = (ap & 0xff0000) >> 16;
        slot[s].materias[mat_num].ap[0]=a;
        slot[s].materias[mat_num].ap[1]=b;
        slot[s].materias[mat_num].ap[2]=c;
    }
    else
    {//invalid ID set Empty
        slot[s].materias[mat_num].id =0xFF;
        slot[s].materias[mat_num].ap[0]=0xFF;
        slot[s].materias[mat_num].ap[1]=0xFF;
        slot[s].materias[mat_num].ap[2]=0xFF;
    }
    setFileModified(true,s);
}
quint8 FF7Save::partyMateriaId(int s,int mat_num){return slot[s].materias[mat_num].id;}
qint32 FF7Save::partyMateriaAp(int s,int mat_num)
{
    qint32 ap_temp = slot[s].materias[mat_num].ap[0] |(slot[s].materias[mat_num].ap[1] << 8) | slot[s].materias[mat_num].ap[2]<<16;
    return ap_temp;
}
void FF7Save::setStolenMateria(int s, int mat_num, quint8 id,qint32 ap)
{
    if( (id<91) && ((ap>=0)&&(ap<=16777215)))
    {//Valid Id and Ap provided.
        slot[s].stolen[mat_num].id = id;
        int a = (ap & 0xff);
        int b = (ap & 0xff00) >> 8;
        int c = (ap & 0xff0000) >> 16;
        slot[s].stolen[mat_num].ap[0]=a;
        slot[s].stolen[mat_num].ap[1]=b;
        slot[s].stolen[mat_num].ap[2]=c;
    }
    else
    {//invalid ID set Empty
        slot[s].stolen[mat_num].id =0xFF;
        slot[s].stolen[mat_num].ap[0]=0xFF;
        slot[s].stolen[mat_num].ap[1]=0xFF;
        slot[s].stolen[mat_num].ap[2]=0xFF;
    }
    setFileModified(true,s);
}
quint8 FF7Save::stolenMateriaId(int s,int mat_num){return slot[s].stolen[mat_num].id;}

qint32 FF7Save::stolenMateriaAp(int s,int mat_num)
{
    qint32 ap_temp = slot[s].stolen[mat_num].ap[0] |(slot[s].stolen[mat_num].ap[1] << 8) | slot[s].stolen[mat_num].ap[2]<<16;
    return ap_temp;
}
QColor FF7Save::dialogColorUL(int s){return QColor(slot[s].colors[0][0],slot[s].colors[0][1],slot[s].colors[0][2]);}
QColor FF7Save::dialogColorUR(int s){return QColor(slot[s].colors[1][0],slot[s].colors[1][1],slot[s].colors[1][2]);}
QColor FF7Save::dialogColorLL(int s){return QColor(slot[s].colors[2][0],slot[s].colors[2][1],slot[s].colors[2][2]);}
QColor FF7Save::dialogColorLR(int s){return QColor(slot[s].colors[3][0],slot[s].colors[3][1],slot[s].colors[3][2]);}

void FF7Save::setDialogColorUL(int s, QColor color)
{
    slot[s].colors[0][0]=color.red();
    slot[s].colors[0][1]=color.green();
    slot[s].colors[0][2]= color.blue();
    setFileModified(true,s);
}
void FF7Save::setDialogColorUR(int s, QColor color)
{
    slot[s].colors[1][0]=color.red();
    slot[s].colors[1][1]=color.green();
    slot[s].colors[1][2]= color.blue();
    setFileModified(true,s);
}
void FF7Save::setDialogColorLL(int s, QColor color)
{
    slot[s].colors[2][0]=color.red();
    slot[s].colors[2][1]=color.green();
    slot[s].colors[2][2]= color.blue();
    setFileModified(true,s);
}
void FF7Save::setDialogColorLR(int s, QColor color)
{
    slot[s].colors[3][0]=color.red();
    slot[s].colors[3][1]=color.green();
    slot[s].colors[3][2]= color.blue();
    setFileModified(true,s);
}
void FF7Save::setCharacter(int s,int char_num,FF7CHAR new_char){slot[s].chars[char_num] = new_char;}

FF7CHAR FF7Save::character(int s,int char_num){return slot[s].chars[char_num];}

QByteArray FF7Save::rawCharacterData(int s, int char_num)
{
    QByteArray temp;
    temp.setRawData(reinterpret_cast <char *>(&slot[s].chars[char_num]),132);
    return temp;
}
quint8 FF7Save::charID(int s,int char_num){return slot[s].chars[char_num].id;}
quint8 FF7Save::charLevel(int s,int char_num){return slot[s].chars[char_num].level;}
quint8 FF7Save::charStr(int s,int char_num){return slot[s].chars[char_num].strength;}
quint8 FF7Save::charVit(int s,int char_num){return slot[s].chars[char_num].vitality;}
quint8 FF7Save::charMag(int s,int char_num){return slot[s].chars[char_num].magic;}
quint8 FF7Save::charSpi(int s,int char_num){return slot[s].chars[char_num].spirit;}
quint8 FF7Save::charDex(int s,int char_num){return slot[s].chars[char_num].dexterity;}
quint8 FF7Save::charLck(int s,int char_num){return slot[s].chars[char_num].luck;}
quint8 FF7Save::charStrBonus(int s,int char_num){return slot[s].chars[char_num].strength_bonus;}
quint8 FF7Save::charVitBonus(int s,int char_num){return slot[s].chars[char_num].vitality_bonus;}
quint8 FF7Save::charMagBonus(int s,int char_num){return slot[s].chars[char_num].magic_bonus;}
quint8 FF7Save::charSpiBonus(int s,int char_num){return slot[s].chars[char_num].spirit_bonus;}
quint8 FF7Save::charDexBonus(int s,int char_num){return slot[s].chars[char_num].dexterity_bonus;}
quint8 FF7Save::charLckBonus(int s,int char_num){return slot[s].chars[char_num].luck_bonus;}
qint8 FF7Save::charLimitLevel(int s,int char_num){return slot[s].chars[char_num].limitlevel;}
quint8 FF7Save::charLimitBar(int s,int char_num){return slot[s].chars[char_num].limitbar;}
quint8 FF7Save::charWeapon(int s,int char_num){return slot[s].chars[char_num].weapon;}
quint8 FF7Save::charArmor(int s,int char_num){return slot[s].chars[char_num].armor;}
quint8 FF7Save::charAccessory(int s,int char_num){return slot[s].chars[char_num].accessory;}
quint8 FF7Save::charFlag(int s,int char_num,int flag_num){return slot[s].chars[char_num].flags[flag_num];}
quint16 FF7Save::charLimits(int s,int char_num){return slot[s].chars[char_num].limits;}
quint16 FF7Save::charKills(int s,int char_num){return slot[s].chars[char_num].kills;}

quint16 FF7Save::charTimesLimitUsed(int s,int char_num,int level)
{
    switch(level)
    {
        case 1:return slot[s].chars[char_num].timesused1;break;
        case 2:return slot[s].chars[char_num].timesused2;break;
        case 3:return slot[s].chars[char_num].timesused3;break;
        default:return 0;
    }
}

quint16 FF7Save::charCurrentHp(int s,int char_num){return slot[s].chars[char_num].curHP;}
quint16 FF7Save::charBaseHp(int s,int char_num){return slot[s].chars[char_num].baseHP;}
quint16 FF7Save::charCurrentMp(int s,int char_num){return slot[s].chars[char_num].curMP;}
quint16 FF7Save::charBaseMp(int s,int char_num){return slot[s].chars[char_num].baseMP;}
quint8 FF7Save::charUnknown(int s,int char_num,int unknown_num){return slot[s].chars[char_num].z_4[unknown_num];}
quint16 FF7Save::charMaxHp(int s,int char_num){return slot[s].chars[char_num].maxHP;}
quint16 FF7Save::charMaxMp(int s,int char_num){return slot[s].chars[char_num].maxMP;}
quint32 FF7Save::charCurrentExp(int s,int char_num){return slot[s].chars[char_num].exp;}
quint32 FF7Save::charNextExp(int s,int char_num){return slot[s].chars[char_num].expNext;}

void  FF7Save::setCharID(int s,int char_num,qint8 new_id){slot[s].chars[char_num].id=new_id;setFileModified(true,s);}
void  FF7Save::setCharLevel(int s,int char_num,qint8 new_level){slot[s].chars[char_num].level=new_level;setFileModified(true,s);}
void  FF7Save::setCharStr(int s,int char_num,quint8 str){slot[s].chars[char_num].strength=str;setFileModified(true,s);}
void  FF7Save::setCharVit(int s,int char_num,quint8 vit){slot[s].chars[char_num].vitality=vit;setFileModified(true,s);}
void  FF7Save::setCharMag(int s,int char_num,quint8 mag){slot[s].chars[char_num].magic=mag;setFileModified(true,s);}
void  FF7Save::setCharSpi(int s,int char_num,quint8 spi){slot[s].chars[char_num].spirit=spi;setFileModified(true,s);}
void  FF7Save::setCharDex(int s,int char_num,quint8 dex){slot[s].chars[char_num].dexterity=dex;setFileModified(true,s);}
void  FF7Save::setCharLck(int s,int char_num,quint8 lck){slot[s].chars[char_num].luck=lck;setFileModified(true,s);}
void  FF7Save::setCharStrBonus(int s,int char_num,quint8 strbonus){slot[s].chars[char_num].strength_bonus=strbonus;setFileModified(true,s);}
void  FF7Save::setCharVitBonus(int s,int char_num,quint8 vitbonus){slot[s].chars[char_num].vitality_bonus=vitbonus;setFileModified(true,s);}
void  FF7Save::setCharMagBonus(int s,int char_num,quint8 magbonus){slot[s].chars[char_num].magic_bonus=magbonus;setFileModified(true,s);}
void  FF7Save::setCharSpiBonus(int s,int char_num,quint8 spibonus){slot[s].chars[char_num].spirit_bonus=spibonus;setFileModified(true,s);}
void  FF7Save::setCharDexBonus(int s,int char_num,quint8 dexbonus){slot[s].chars[char_num].dexterity_bonus=dexbonus;setFileModified(true,s);}
void  FF7Save::setCharLckBonus(int s,int char_num,quint8 lckbonus){slot[s].chars[char_num].luck_bonus=lckbonus;setFileModified(true,s);}
void  FF7Save::setCharLimitLevel(int s,int char_num,qint8 limitlevel){slot[s].chars[char_num].limitlevel=limitlevel;setFileModified(true,s);}
void  FF7Save::setCharLimitBar(int s,int char_num,quint8 limitbar){slot[s].chars[char_num].limitbar=limitbar;setFileModified(true,s);}
void  FF7Save::setCharWeapon(int s,int char_num,quint8 weapon){slot[s].chars[char_num].weapon=weapon;setFileModified(true,s);}
void  FF7Save::setCharArmor(int s,int char_num,quint8 armor){slot[s].chars[char_num].armor=armor;setFileModified(true,s);}
void  FF7Save::setCharAccessory(int s,int char_num,quint8 accessory){slot[s].chars[char_num].accessory=accessory;setFileModified(true,s);}
void  FF7Save::setCharFlag(int s,int char_num,int flag_num,quint8 flag_value){slot[s].chars[char_num].flags[flag_num]=flag_value;setFileModified(true,s);}
void  FF7Save::setCharLimits(int s,int char_num,quint16 new_limits){slot[s].chars[char_num].limits=new_limits;setFileModified(true,s);}
void  FF7Save::setCharKills(int s,int char_num,quint16 new_level){slot[s].chars[char_num].kills=new_level;setFileModified(true,s);}
void  FF7Save::setCharTimeLimitUsed(int s,int char_num,int level,quint16 timesused)
{
    switch(level)
    {
        case 1:slot[s].chars[char_num].timesused1=timesused;setFileModified(true,s);break;
        case 2:slot[s].chars[char_num].timesused2=timesused;setFileModified(true,s);break;
        case 3:slot[s].chars[char_num].timesused3=timesused;setFileModified(true,s);break;
    }
}
void  FF7Save::setCharCurrentHp(int s,int char_num,quint16 curHp){slot[s].chars[char_num].curHP=curHp;setFileModified(true,s);}
void  FF7Save::setCharBaseHp(int s,int char_num,quint16 baseHp){slot[s].chars[char_num].baseHP=baseHp;setFileModified(true,s);}
void  FF7Save::setCharCurrentMp(int s,int char_num,quint16 curMp){slot[s].chars[char_num].curMP=curMp;setFileModified(true,s);}
void  FF7Save::setCharBaseMp(int s,int char_num,quint16 baseMp){slot[s].chars[char_num].baseMP=baseMp;setFileModified(true,s);}
void  FF7Save::setCharUnknown(int s,int char_num,int unknown_num,quint8 value){slot[s].chars[char_num].z_4[unknown_num]=value;setFileModified(true,s);}
void  FF7Save::setCharMaxHp(int s,int char_num,quint16 maxHp){slot[s].chars[char_num].maxHP=maxHp;setFileModified(true,s);}
void  FF7Save::setCharMaxMp(int s,int char_num,quint16 maxMp){slot[s].chars[char_num].maxMP=maxMp;setFileModified(true,s);}
void  FF7Save::setCharCurrentExp(int s,int char_num,quint32 exp){slot[s].chars[char_num].exp=exp;setFileModified(true,s);}
void  FF7Save::setCharNextExp(int s,int char_num,quint32 next){slot[s].chars[char_num].expNext=next;setFileModified(true,s);}

void FF7Save::setCharMateria(int s,int who,int mat_num,quint8 id,qint32 ap)
{
    if( (id<91) && ((ap>=0)&&(ap<=16777215)))
    {//Valid Id and Ap provided.
        slot[s].chars[who].materias[mat_num].id = id;
        int a = (ap & 0xff);
        int b = (ap & 0xff00) >> 8;
        int c = (ap & 0xff0000) >> 16;
        slot[s].chars[who].materias[mat_num].ap[0]=a;
        slot[s].chars[who].materias[mat_num].ap[1]=b;
        slot[s].chars[who].materias[mat_num].ap[2]=c;
    }
    else
    {//invalid ID set Empty
        slot[s].chars[who].materias[mat_num].id =0xFF;
        slot[s].chars[who].materias[mat_num].ap[0]=0xFF;
        slot[s].chars[who].materias[mat_num].ap[1]=0xFF;
        slot[s].chars[who].materias[mat_num].ap[2]=0xFF;
    }
    setFileModified(true,s);
}
void FF7Save::setCharMateria(int s, int who, int mat_num, materia mat){slot[s].chars[who].materias[mat_num] = mat;setFileModified(true,s);}
quint8 FF7Save::charMateriaId(int s,int who,int mat_num){return slot[s].chars[who].materias[mat_num].id;}
qint32 FF7Save::charMateriaAp(int s,int who,int mat_num)
{
    qint32 ap_temp = slot[s].chars[who].materias[mat_num].ap[0] |(slot[s].chars[who].materias[mat_num].ap[1] << 8) | slot[s].chars[who].materias[mat_num].ap[2]<<16;
    return ap_temp;
}
FF7CHOCOBO FF7Save::chocobo(int s, int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot];}
    else if (chocoSlot ==4){return slot[s].choco56[0];}
    else if (chocoSlot ==5){return slot[s].choco56[1];}
    else
    {
        FF7CHOCOBO bob;
        QByteArray temp;
        temp.fill(0,16);
        memcpy(&bob,temp,16);
        return bob;
   }
}

quint16 FF7Save::chocoStamina(int s,int chocoSlot){return slot[s].chocostaminas[chocoSlot];}
quint16 FF7Save::chocoSpeed(int s,int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].speed;}
    else if (chocoSlot ==4){return slot[s].choco56[0].speed;}
    else if (chocoSlot ==5){return slot[s].choco56[1].speed;}
    else {return 0;}
}
quint16 FF7Save::chocoMaxSpeed(int s,int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].maxspeed;}
    else if (chocoSlot ==4){return slot[s].choco56[0].maxspeed;}
    else if (chocoSlot ==5){return slot[s].choco56[1].maxspeed;}
    else {return 0;}
}
quint16 FF7Save::chocoSprintSpeed(int s,int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].sprintspd;}
    else if (chocoSlot ==4){return slot[s].choco56[0].sprintspd;}
    else if (chocoSlot ==5){return slot[s].choco56[1].sprintspd;}
    else {return 0;}
}
quint16 FF7Save::chocoMaxSprintSpeed(int s,int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].maxsprintspd;}
    else if (chocoSlot ==4){return slot[s].choco56[0].maxsprintspd;}
    else if (chocoSlot ==5){return slot[s].choco56[1].maxsprintspd;}
    else {return 0;}
}
quint8 FF7Save::chocoSex(int s, int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].sex;}
    else if (chocoSlot ==4){return slot[s].choco56[0].sex;}
    else if (chocoSlot ==5){return slot[s].choco56[1].sex;}
    else {return 0;}
}
quint8 FF7Save::chocoType(int s, int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].type;}
    else if (chocoSlot ==4){return slot[s].choco56[0].type;}
    else if (chocoSlot ==5){return slot[s].choco56[1].type;}
    else {return 0;}
}
quint8 FF7Save::chocoCoop(int s, int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].coop;}
    else if (chocoSlot ==4){return slot[s].choco56[0].coop;}
    else if (chocoSlot ==5){return slot[s].choco56[1].coop;}
    else {return 0;}
}
quint8 FF7Save::chocoAccel(int s, int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].accel;}
    else if (chocoSlot ==4){return slot[s].choco56[0].accel;}
    else if (chocoSlot ==5){return slot[s].choco56[1].accel;}
    else {return 0;}
}
quint8 FF7Save::chocoIntelligence(int s, int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].intelligence;}
    else if (chocoSlot ==4){return slot[s].choco56[0].intelligence;}
    else if (chocoSlot ==5){return slot[s].choco56[1].intelligence;}
    else {return 0;}
}
quint8 FF7Save::chocoRaceswon(int s, int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].raceswon;}
    else if (chocoSlot ==4){return slot[s].choco56[0].raceswon;}
    else if (chocoSlot ==5){return slot[s].choco56[1].raceswon;}
    else {return 0;}
}
quint8 FF7Save::chocoPCount(int s, int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].pcount;}
    else if (chocoSlot ==4){return slot[s].choco56[0].pcount;}
    else if (chocoSlot ==5){return slot[s].choco56[1].pcount;}
    else {return 0;}
}
quint8 FF7Save::chocoPersonality(int s, int chocoSlot)
{
    if(chocoSlot >-1 && chocoSlot <4){return slot[s].chocobos[chocoSlot].personality;}
    else if (chocoSlot ==4){return slot[s].choco56[0].personality;}
    else if (chocoSlot ==5){return slot[s].choco56[1].personality;}
    else {return 0;}
}
bool FF7Save::chocoCantMate(int s, int chocoSlot){return slot[s].chocomated& (1<<chocoSlot);}

void FF7Save::setChocoStamina(int s,int chocoSlot,quint16 stamina){slot[s].chocostaminas[chocoSlot] = stamina;setFileModified(true,s);}
void FF7Save::setChocoSpeed(int s,int chocoSlot,quint16 speed)
{
    if(chocoSlot >-1 && chocoSlot <4){slot[s].chocobos[chocoSlot].speed = speed;setFileModified(true,s);}
    else if (chocoSlot ==4){slot[s].choco56[0].speed = speed;setFileModified(true,s);}
    else if (chocoSlot ==5){slot[s].choco56[1].speed = speed;setFileModified(true,s);}
}
void FF7Save::setChocoMaxSpeed(int s,int chocoSlot,quint16 maxspeed)
{
    if(chocoSlot >-1 && chocoSlot <4){slot[s].chocobos[chocoSlot].maxspeed = maxspeed;setFileModified(true,s);}
    else if (chocoSlot ==4){slot[s].choco56[0].maxspeed = maxspeed;setFileModified(true,s);}
    else if (chocoSlot ==5){slot[s].choco56[1].maxspeed = maxspeed;setFileModified(true,s);}
}
void FF7Save::setChocoSprintSpeed(int s,int chocoSlot,quint16 sprintSpeed)
{
    if(chocoSlot >-1 && chocoSlot <4){slot[s].chocobos[chocoSlot].sprintspd = sprintSpeed;setFileModified(true,s);}
    else if (chocoSlot ==4){slot[s].choco56[0].sprintspd = sprintSpeed;setFileModified(true,s);}
    else if (chocoSlot ==5){slot[s].choco56[1].sprintspd = sprintSpeed;setFileModified(true,s);}
}
void FF7Save::setChocoMaxSprintSpeed(int s,int chocoSlot,quint16 maxsprintSpeed)
{
    if(chocoSlot >-1 && chocoSlot <4){slot[s].chocobos[chocoSlot].maxsprintspd = maxsprintSpeed;setFileModified(true,s);}
    else if (chocoSlot ==4){slot[s].choco56[0].maxsprintspd = maxsprintSpeed;setFileModified(true,s);}
    else if (chocoSlot ==5){slot[s].choco56[1].maxsprintspd = maxsprintSpeed;setFileModified(true,s);}
}
void FF7Save::setChocoSex(int s, int chocoSlot,quint8 value)
{
    if(chocoSlot >-1 && chocoSlot <4){ slot[s].chocobos[chocoSlot].sex = value;setFileModified(true,s);}
    else if (chocoSlot ==4){ slot[s].choco56[0].sex = value;setFileModified(true,s);}
    else if (chocoSlot ==5){ slot[s].choco56[1].sex = value;setFileModified(true,s);}
}
void FF7Save::setChocoType(int s, int chocoSlot,quint8 value)
{
    if(chocoSlot >-1 && chocoSlot <4){ slot[s].chocobos[chocoSlot].type = value;setFileModified(true,s);}
    else if (chocoSlot ==4){ slot[s].choco56[0].type = value;setFileModified(true,s);}
    else if (chocoSlot ==5){ slot[s].choco56[1].type = value;setFileModified(true,s);}
}
void FF7Save::setChocoCoop(int s, int chocoSlot,quint8 value)
{
    if(chocoSlot >-1 && chocoSlot <4){ slot[s].chocobos[chocoSlot].coop = value;setFileModified(true,s);}
    else if (chocoSlot ==4){ slot[s].choco56[0].coop = value;setFileModified(true,s);}
    else if (chocoSlot ==5){ slot[s].choco56[1].coop = value;setFileModified(true,s);}
}
void FF7Save::setChocoAccel(int s, int chocoSlot,quint8 value)
{
    if(chocoSlot >-1 && chocoSlot <4){ slot[s].chocobos[chocoSlot].accel = value;setFileModified(true,s);}
    else if (chocoSlot ==4){ slot[s].choco56[0].accel = value;setFileModified(true,s);}
    else if (chocoSlot ==5){ slot[s].choco56[1].accel = value;setFileModified(true,s);}
}
void FF7Save::setChocoIntelligence(int s, int chocoSlot,quint8 value)
{
    if(chocoSlot >-1 && chocoSlot <4){ slot[s].chocobos[chocoSlot].intelligence = value;setFileModified(true,s);}
    else if (chocoSlot ==4){ slot[s].choco56[0].intelligence = value;setFileModified(true,s);}
    else if (chocoSlot ==5){ slot[s].choco56[1].intelligence = value;setFileModified(true,s);}
}
void FF7Save::setChocoRaceswon(int s, int chocoSlot,quint8 value)
{
    if(chocoSlot >-1 && chocoSlot <4){ slot[s].chocobos[chocoSlot].raceswon = value;setFileModified(true,s);}
    else if (chocoSlot ==4){ slot[s].choco56[0].raceswon = value;setFileModified(true,s);}
    else if (chocoSlot ==5){ slot[s].choco56[1].raceswon = value;setFileModified(true,s);}
}
void FF7Save::setChocoPCount(int s, int chocoSlot,quint8 value)
{
    if(chocoSlot >-1 && chocoSlot <4){ slot[s].chocobos[chocoSlot].pcount = value;setFileModified(true,s);}
    else if (chocoSlot ==4){ slot[s].choco56[0].pcount = value;setFileModified(true,s);}
    else if (chocoSlot ==5){ slot[s].choco56[1].pcount = value;setFileModified(true,s);}
}
void FF7Save::setChocoPersonality(int s, int chocoSlot,quint8 value)
{
    if(chocoSlot >-1 && chocoSlot <4){ slot[s].chocobos[chocoSlot].personality = value;setFileModified(true,s);}
    else if (chocoSlot ==4){ slot[s].choco56[0].personality = value;setFileModified(true,s);}
    else if (chocoSlot ==5){ slot[s].choco56[1].personality = value;setFileModified(true,s);}
}
void FF7Save::setChocoCantMate(int s,int chocoSlot,bool cantMate)
{
    if(cantMate){slot[s].chocomated |= (1 << chocoSlot);}
    else{slot[s].chocomated &=~(1<< chocoSlot);}
    setFileModified(true,s);
}
quint32 FF7Save::gil(int s){return slot[s].gil;}
void FF7Save::setGil(int s,int gil)
{
    if(gil<0){gil =0;}
    slot[s].gil = gil;
    setDescGil(s,gil);//Update Desc
    setFileModified(true,s);
}
quint16 FF7Save::gp (int s){return slot[s].gp;}
void FF7Save::setGp(int s,int gp)
{
    if(gp <0){gp = 0;}
    if(gp >65535){gp = 65535;}
    slot[s].gp = gp;
    setFileModified(true,s);
}
quint16 FF7Save::battles (int s){return slot[s].battles;}
void FF7Save::setBattles(int s,int battles)
{
    if(battles <0){battles = 0;}
    if(battles >65535){battles = 65535;}
    slot[s].battles = battles;
    setFileModified(true,s);
}
quint16 FF7Save::runs (int s){return slot[s].runs;}
void FF7Save::setRuns(int s,int runs)
{
    if(runs <0){runs = 0;}
    if(runs >65535){runs = 65535;}
    slot[s].runs = runs;
    setFileModified(true,s);
}
quint8 FF7Save::party(int s,int pos){return slot[s].party[pos];}
void FF7Save::setParty(int s,int pos, int new_id)
{
    if(pos >=0 && pos <4)
    {
        if(new_id >=0 && new_id<12){slot[s].party[pos] = new_id;}
        else{slot[s].party[pos] =0xFF;}
        setFileModified(true,s);
    }
}
qint8 FF7Save::chocoboPen(int s, int pos){return slot[s].pennedchocos[pos];}
void FF7Save::setChocoboPen(int s, int pos, int type)
{
    if(pos<5)
    {
        if(type >=0 && type <9){slot[s].pennedchocos[pos]=type;}
        else{slot[s].pennedchocos[pos]=0;}
        setFileModified(true,s);
    }
}
quint32 FF7Save::snowboardTime(int s, int course)
{
    quint32 time=0;
    switch(course)
    {
    case 0:
        time = ((slot[s].SnowBegFastTime[1]) | (slot[s].SnowBegFastTime[2]<< 8) | (slot[s].SnowBegFastTime[3] <<16));
        break;

    case 1:
        time = ((slot[s].SnowExpFastTime[1]) | (slot[s].SnowExpFastTime[2]<< 8) | (slot[s].SnowExpFastTime[3] <<16));
       break;

    case 2:
        time = ((slot[s].SnowCrazyFastTime[1]) | (slot[s].SnowCrazyFastTime[2]<< 8) | (slot[s].SnowCrazyFastTime[3] <<16));
       break;

       default: break;
     }
    return time;
}

void FF7Save::setSnowboardTime(int s, int course,quint32 value)
{
    int a = (value & 0xff);
    int b = (value & 0xff00) >> 8;
    int c = (value & 0xff0000) >> 16;
    switch(course)
    {
    case 0:
        slot[s].SnowBegFastTime[1]=a;
        slot[s].SnowBegFastTime[2]=b;
        slot[s].SnowBegFastTime[3]=c;
        setFileModified(true,s);
        break;
    case 1:
        slot[s].SnowExpFastTime[1]=a;
        slot[s].SnowExpFastTime[2]=b;
        slot[s].SnowExpFastTime[3]=c;
        setFileModified(true,s);
        break;
    case 2:
        slot[s].SnowCrazyFastTime[1]=a;
        slot[s].SnowCrazyFastTime[2]=b;
        slot[s].SnowCrazyFastTime[3]=c;
        setFileModified(true,s);
        break;
        default: break;
     }
}

quint8 FF7Save::snowboardScore(int s, int course)
{
    switch(course)
    {
        case 0: return slot[s].SnowBegScore; break;
        case 1: return slot[s].SnowExpScore; break;
        case 2: return slot[s].SnowCrazyScore; break;
        default: return 0; break;
     }
}

void FF7Save::setSnowboardScore(int s, int course,quint8 score)
{
    switch(course)
    {
        case 0:  slot[s].SnowBegScore=score; setFileModified(true,s);break;
        case 1:  slot[s].SnowExpScore=score; setFileModified(true,s);break;
        case 2:  slot[s].SnowCrazyScore=score; setFileModified(true,s);break;
        default: break;
     }

}
quint16 FF7Save::bikeHighScore(int s){return slot[s].BikeHighScore;}
void FF7Save::setBikeHighScore(int s,quint16 score){slot[s].BikeHighScore = score;setFileModified(true,s);}
quint16 FF7Save::battlePoints(int s){return (slot[s].z_20[4] | (slot[s].z_20[5] << 8));}
void FF7Save::setBattlePoints(int s,quint16 bp)
{
    int a = bp &0xFF;
    int b = (bp &0xFF00) >>8;
    slot[s].z_20[4]=a;
    slot[s].z_20[5]=b;
    setFileModified(true,s);
}

QString FF7Save::md5sum(QString fileName, QString UserID)
{
    QByteArray ff7file;
    QFile  file(fileName);
    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly)){ff7file = file.readAll();}
    }
    if(UserID!="")
    {
        ff7file.append(UserID.toLatin1());//append the user's ID
    }
    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(ff7file);
    return md5.result().toHex().toLower();
}
void FF7Save::setFileModified(bool changed,int s)
{
    fileChanged=changed;
    if(changed){slotChanged[s]=true;}
    else{for(int i=0;i<15;i++){slotChanged[i]=false;}}
}
QVector< SubContainer > FF7Save::parseXML(QString fileName, QString metadataPath, QString UserID)
{
    //typedef QVector< QString > SubContainer;
    QVector< SubContainer > vector( 10, SubContainer( 16 ) );
    QString Md5 = md5sum(fileName,UserID);
    QString timestamp = filetimestamp(fileName);
    QString number = fileblock(fileName);                           //Get file block number
    if(number == "-1"){/*return 0;*/}                               //Fail if not a number
    else {number = QString::number(number.toInt()+1);}

    QFile* file2 = new QFile(metadataPath);                         //Open metadata.xml
    if (!file2->open(QIODevice::ReadOnly)){/*return 0;*/}           //If open fail, show an error message.
    QDomDocument doc("metadata");
    bool setdoc = doc.setContent(file2);
    file2->close();
    if (!setdoc){/*return 0;*/}
    QDomElement docElem = doc.documentElement();                    //Get the root element
    if(docElem.tagName() != "gamestatus"){/*return 0;*/}            //Check file format
    QDomNodeList nodeList = docElem.elementsByTagName("savefiles"); //Get savefiles node
    for(int ii = 0;ii < nodeList.count(); ii++)                     //Check each node one by one.
    {
        QDomElement el = nodeList.at(ii).toElement();               //Get the current one as QDomElement
        QDomNode pEntries = el.firstChild();                        //Get all data for the element, by looping through all child elements
        int iii = 0;
        while(!pEntries.isNull())
        {
            QDomElement peData = pEntries.toElement();
            vector[ii][iii] = peData.text();
            if(el.attribute("block") == number)
            {
                if(iii==15){vector[ii][iii] = Md5;}
                else if(isSlotModified(iii)){vector[ii][iii] = timestamp;}  //We check the slot mod tracker to make the time update on all modified slots
                else if(region(iii).isEmpty()){vector[ii][iii] = "";}       //Clear timestamp for empty slot
                else if(vector[ii][iii] == ""){vector[ii][iii] = timestamp;}//Write the stamp (if no stamp is present and the slot isn't empty)
            }
            pEntries = pEntries.nextSibling();
            iii++;
        }
    }
    return vector;
}

QVector< SubContainer > FF7Save::createMetadata(QString fileName, QString UserID)
{
    QVector< SubContainer > vector( 10, SubContainer( 16 ) );
    QString Md5 = md5sum(fileName,UserID);
    QString timestamp = filetimestamp(fileName);
    QString number = fileblock(fileName);//Get file block number
    if(number == "-1"){return vector;}
    //Do foreach block
    for(int i=0;i<10; i++)
    {//if i is the current number then do each slot and md5
        if(i == number.toInt()){ for(int j=0; j<16; j++)
        {
            if(j==15){vector[i][j] = Md5;}
            else if(isSlotModified(j)){vector[i][j] = timestamp;} //We check the slot mod tracker to make the time update on all modified slots
            else if(region(j).isEmpty()){vector[i][j] = "";}      //Clear timestamp for empty slot
            else if(vector[i][j] == ""){vector[i][j] = timestamp;}//Write the stamp (if no stamp is present and the slot isn't empty)
        }}
    }
    return vector;
}
bool FF7Save::fixMetaData(QString fileName,QString OutPath,QString UserID)
{
    QString UserId;//user id is not global for now
    if(fileName==QString("")){fileName=filename;}
    QString Path =fileName;
    Path.chop(Path.length()-Path.lastIndexOf("/"));
    QString metadataPath = Path;
    metadataPath.append("/metadata.xml");

    QFile Metadata(metadataPath);
    if(!Metadata.exists() && OutPath == ""){return 0;}

    //is a New PC saveFile then
    QVector< SubContainer > vector( 10, SubContainer( 16 ) );
    if(Metadata.exists())
    {//get our user id
        Path.remove(0,Path.lastIndexOf("_")+1);
        Path.chop(Path.length()-Path.lastIndexOf("/"));
        UserId = Path;
        vector = parseXML(fileName, metadataPath, UserID);
    }
    else
    {
        UserId = UserID;
        vector = createMetadata(fileName, UserID);
    }

    QFile file3(metadataPath);
    if (!file3.open(QIODevice::ReadWrite)){return 0;}
    QTextStream out (&file3);
    file3.seek(0);//Set pointer to the Beggining
    out << QString ("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    out << QString("<gamestatus>\n");
    //Do foreach block
    for(int i=0;i<10; i++)
    {
        out << (QString("  <savefiles block=\"%1\">\n").arg(QString::number(i+1)));
        //Do foreach slot
        for(int j=0; j<15; j++)
        {
            out << (QString("    <timestamp slot=\"%1\">%2</timestamp>\n").arg(QString::number(j+1),vector[i][j]));
        }
        out << (QString("    <signature>%1</signature>\n").arg(vector[i][15]));
        out << QString("  </savefiles>\n");
    }
    out << QString("</gamestatus>\n");
    file3.resize(file3.pos());
    file3.close();
    return 1;
}
QString FF7Save::fileName(void){return filename;}
QString FF7Save::fileblock(QString fileName)
{
        QString number = fileName;
        number.remove(0,number.lastIndexOf("/")+5);//5=(/save)
        number.chop(4);
        bool isNumber = false;
        number = QString::number(number.toInt(&isNumber));
        if(isNumber){return number;}
        else{return "-1";}//fail if not a number.
}
QString FF7Save::filetimestamp(QString fileName)
{
    QFile tempFile(fileName);
    if(tempFile.exists()){QFileInfo file(fileName); return QString::number(file.lastModified().toMSecsSinceEpoch());}
    else {return "";}
}
QByteArray FF7Save::slotFF7Data(int s)
{
    if(s<0 || s>14){return QByteArray(0x00);}
    QByteArray temp;
    temp.setRawData(reinterpret_cast<char *>(&slot[s]),0x10F4);
    return temp;
}
bool FF7Save::setSlotFF7Data(int s,QByteArray data)
{
    if(s<0 || s>14){return false;}
    if(data.size()!=0x10F4){return false;}
    memcpy(&slot[s],data,0x10F4);
    return true;
}

bool FF7Save::setSlotFF7Data(int s,FF7SLOT data)
{
    if(s<0 || s>14){return false;}
    slot[s] = data;
    setFileModified(true,s);
    return true;
}

bool FF7Save::turtleParadiseFlyerSeen(int s, int flyer)
{
    if(s<0 || s>14){return false;}
    else if(flyer <0 || flyer >7){return false;}
    else{return ((slot[s].turtleflyers) &(1<<flyer));}
}
quint8 FF7Save::turtleParadiseFlyersSeen(int s)
{
    if(s<0 || s> 14){return 0;}
    else{return slot[s].turtleflyers;}
}

void FF7Save::setTurtleParadiseFlyerSeen(int s, int flyer,bool seen)
{
    if(s<0 || s>14){return;}
    else if(flyer <0 || flyer >7){return;}
    else
    {
        if(seen){slot[s].turtleflyers |= (1<<flyer);}
        else{slot[s].turtleflyers &= ~(1<<flyer);}
        setFileModified(true,s);
    }
}
void FF7Save::setTurtleParadiseFlyersSeen(int s,quint8 flyersSeen)
{
    if(s<0 || s>14){return;}
    else
    {
        slot[s].turtleflyers = flyersSeen;
        setFileModified(true,s);
    }
}
bool FF7Save::itemMask1(int s, int bit)
{//the Bit Number to offset.
    if(bit <0 || bit> 7){return false;}
    else{return ((slot[s].itemsmask_1)& (1<<bit) );}
}
void FF7Save::setItemMask1(int s, int bit, bool pickedUp)
{
    if(s<0 || s>14){return;}
    else if(bit<0 || bit >7){return;}
    else
    {
        if(pickedUp){slot[s].itemsmask_1 |= (1<<bit);}
        else
        {
            slot[s].itemsmask_1 &= ~(1<<bit);
            setFileModified(true,s);
        }
    }
}
QByteArray FF7Save::keyItems(int s)
{
    if(s<0 || s>14){return QByteArray("\x00");}
    else
    {
        QByteArray temp;
        temp.setRawData(reinterpret_cast<char *>(&slot[s].keyitems),sizeof(slot[s].keyitems));
        return temp;
     }
}
bool FF7Save::keyItem(int s, int keyItem)
{
    if(s<0 || s>14){return false;}
    else if(keyItem <0 || keyItem>51){return false;}
    else{return ((slot[s].keyitems[keyItem/8]) & (1<< (keyItem%8)));}
}
void FF7Save::setKeyItem(int s, int keyItem, bool pickedUp)
{
    if(s<0 || s>14){return ;}
    else if(keyItem <0 || keyItem>51){return;}
    else
    {
        if(pickedUp){slot[s].keyitems[keyItem/8] |= (1<< (keyItem%8));}
        else{slot[s].keyitems[keyItem/8] &= ~(1<< (keyItem%8));}
        setFileModified(true,s);
    }

}
bool FF7Save::setKeyItems(int s,QByteArray data)
{
    if(data.size() != sizeof(slot[s].keyitems)) {return false;}
    else
    {
        memcpy(&slot[s].keyitems,data,sizeof(slot[s].keyitems));
        setFileModified(true,s);
        return true;
    }
}
QByteArray FF7Save::unknown(int s,int z)
{
    if(s<0 || s>14){return QByteArray(0x00);}
    QByteArray temp;
    switch(z)
    {
        case 0: temp.setRawData(0x00,1); break;
        case 1: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_1),sizeof(slot[s].z_1)); break;
        case 2: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_2),sizeof(slot[s].z_2)); break;
        case 3: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_3),sizeof(slot[s].z_3)); break;
        case 4: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_4),sizeof(slot[s].z_4)); break;
        case 5: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_5),sizeof(slot[s].z_5)); break;
        case 6: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_6),sizeof(slot[s].z_6)); break;
        case 7: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_7),sizeof(slot[s].z_7)); break;
        case 8: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_8),sizeof(slot[s].z_8)); break;
        case 9: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_9),sizeof(slot[s].z_9)); break;
        case 10: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_10),sizeof(slot[s].z_10)); break;
        case 11: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_11),sizeof(slot[s].z_11)); break;
        case 12: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_12),sizeof(slot[s].z_12)); break;
        case 13: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_13),sizeof(slot[s].z_13)); break;
        case 14: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_14),sizeof(slot[s].z_14)); break;
        case 15: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_15),sizeof(slot[s].z_15)); break;
        case 16: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_16),sizeof(slot[s].z_16)); break;
        case 17: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_17),sizeof(slot[s].z_17)); break;
        case 18: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_18),sizeof(slot[s].z_18)); break;
        case 19: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_19),sizeof(slot[s].z_19)); break;
        case 20: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_20),sizeof(slot[s].z_20)); break;
        case 21: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_21),sizeof(slot[s].z_21)); break;
        case 22: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_22),sizeof(slot[s].z_22)); break;
        case 23: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_23),sizeof(slot[s].z_23)); break;
        case 24: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_24),sizeof(slot[s].z_24)); break;
        case 25: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_25),sizeof(slot[s].z_25)); break;
        case 26: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_26),sizeof(slot[s].z_26)); break;
        case 27: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_27),sizeof(slot[s].z_27)); break;
        case 28: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_28),sizeof(slot[s].z_28)); break;
        case 29: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_29),sizeof(slot[s].z_29)); break;
        case 30: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_30),sizeof(slot[s].z_30)); break;
        case 31: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_31),sizeof(slot[s].z_31)); break;
        case 32: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_32),sizeof(slot[s].z_32)); break;
        case 33: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_33),sizeof(slot[s].z_33)); break;
        case 34: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_34),sizeof(slot[s].z_34)); break;
        case 35: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_35),sizeof(slot[s].z_35)); break;
        case 36: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_36),sizeof(slot[s].z_36)); break;
        case 37: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_37),sizeof(slot[s].z_37)); break;
        case 38: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_38),sizeof(slot[s].z_38)); break;
        case 39: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_39),sizeof(slot[s].z_39)); break;
        case 40: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_40),sizeof(slot[s].z_40)); break;
        default: temp.setRawData(0x00,1); break;
    }
    return temp;
}

bool FF7Save::setUnknown(int s,int z,QByteArray data)
{
    if(s<0 || s>14){return false;}
    bool result;
    switch(z)
    {
        case 0: result=false; break;
        case 1:
                    if(data.size() != sizeof(slot[s].z_1)) {result=false; break;}
                    else{memcpy(&slot[s].z_1,data,sizeof(slot[s].z_1)); result=true;break;}
        case 2:
                    if(data.size() != sizeof(slot[s].z_2)) {result=false; break;}
                    else{memcpy(&slot[s].z_2,data,sizeof(slot[s].z_2)); result=true;break;}
        case 3:
                    if(data.size() != sizeof(slot[s].z_3)) {result=false; break;}
                    else{memcpy(&slot[s].z_3,data,sizeof(slot[s].z_3)); result=true;break;}
        case 4:
                    if(data.size() != sizeof(slot[s].z_4)) {result=false; break;}
                    else{memcpy(&slot[s].z_4,data,sizeof(slot[s].z_4)); result=true;break;}
        case 5:
                    if(data.size() != sizeof(slot[s].z_5)) {result=false; break;}
                    else{memcpy(&slot[s].z_5,data,sizeof(slot[s].z_5)); result=true;break;}
        case 6:
                    if(data.size() != sizeof(slot[s].z_6)) {result=false; break;}
                    else{memcpy(&slot[s].z_6,data,sizeof(slot[s].z_6)); result=true;break;}
        case 7:
                    if(data.size() != sizeof(slot[s].z_7)) {result=false; break;}
                    else{memcpy(&slot[s].z_7,data,sizeof(slot[s].z_7)); result=true;break;}
        case 8:
                    if(data.size() != sizeof(slot[s].z_8)) {result=false; break;}
                    else{memcpy(&slot[s].z_8,data,sizeof(slot[s].z_8)); result=true;break;}
        case 9:
                    if(data.size() != sizeof(slot[s].z_9)) {result=false; break;}
                    else{memcpy(&slot[s].z_9,data,sizeof(slot[s].z_9)); result=true;break;}
        case 10:
                    if(data.size() != sizeof(slot[s].z_10)) {result=false; break;}
                    else{memcpy(&slot[s].z_10,data,sizeof(slot[s].z_10)); result=true;break;}
        case 11:
                    if(data.size() != sizeof(slot[s].z_11)) {result=false; break;}
                    else{memcpy(&slot[s].z_11,data,sizeof(slot[s].z_11)); result=true;break;}
        case 12:
                    if(data.size() != sizeof(slot[s].z_12)) {result=false; break;}
                    else{memcpy(&slot[s].z_12,data,sizeof(slot[s].z_12)); result=true;break;}
        case 13:
                    if(data.size() != sizeof(slot[s].z_13)) {result=false; break;}
                    else{memcpy(&slot[s].z_13,data,sizeof(slot[s].z_13)); result=true;break;}
        case 14:
                    if(data.size() != sizeof(slot[s].z_14)) {result=false; break;}
                    else{memcpy(&slot[s].z_14,data,sizeof(slot[s].z_14)); result=true;break;}
        case 15:
                    if(data.size() != sizeof(slot[s].z_15)) {result=false; break;}
                    else{memcpy(&slot[s].z_15,data,sizeof(slot[s].z_15)); result=true;break;}
        case 16:
                    if(data.size() != sizeof(slot[s].z_16)) {result=false; break;}
                    else{memcpy(&slot[s].z_16,data,sizeof(slot[s].z_16)); result=true;break;}
        case 17:
                    if(data.size() != sizeof(slot[s].z_17)) {result=false; break;}
                    else{memcpy(&slot[s].z_17,data,sizeof(slot[s].z_17)); result=true;break;}
        case 18:
                    if(data.size() != sizeof(slot[s].z_18)) {result=false; break;}
                    else{memcpy(&slot[s].z_18,data,sizeof(slot[s].z_18)); result=true;break;}
        case 19:
                    if(data.size() != sizeof(slot[s].z_19)) {result=false; break;}
                    else{memcpy(&slot[s].z_19,data,sizeof(slot[s].z_19)); result=true;break;}
        case 20:
                    if(data.size() != sizeof(slot[s].z_20)) {result=false; break;}
                    else{memcpy(&slot[s].z_20,data,sizeof(slot[s].z_20)); result=true;break;}
        case 21:
                    if(data.size() != sizeof(slot[s].z_21)) {result=false; break;}
                    else{memcpy(&slot[s].z_21,data,sizeof(slot[s].z_21)); result=true;break;}
        case 22:
                    if(data.size() != sizeof(slot[s].z_22)) {result=false; break;}
                    else{memcpy(&slot[s].z_22,data,sizeof(slot[s].z_22)); result=true;break;}
        case 23:
                    if(data.size() != sizeof(slot[s].z_23)) {result=false; break;}
                    else{memcpy(&slot[s].z_23,data,sizeof(slot[s].z_23)); result=true;break;}
        case 24:
                    if(data.size() != sizeof(slot[s].z_24)) {result=false; break;}
                    else{memcpy(&slot[s].z_24,data,sizeof(slot[s].z_24)); result=true;break;}
        case 25:
                    if(data.size() != sizeof(slot[s].z_25)) {result=false; break;}
                    else{memcpy(&slot[s].z_25,data,sizeof(slot[s].z_25)); result=true;break;}
        case 26:
                    if(data.size() != sizeof(slot[s].z_26)) {result=false; break;}
                    else{memcpy(&slot[s].z_26,data,sizeof(slot[s].z_26)); result=true;break;}
        case 27:
                    if(data.size() != sizeof(slot[s].z_27)) {result=false; break;}
                    else{memcpy(&slot[s].z_27,data,sizeof(slot[s].z_27)); result=true;break;}
        case 28:
                    if(data.size() != sizeof(slot[s].z_28)) {result=false; break;}
                    else{memcpy(&slot[s].z_28,data,sizeof(slot[s].z_28)); result=true;break;}
        case 29:
                    if(data.size() != sizeof(slot[s].z_29)) {result=false; break;}
                    else{memcpy(&slot[s].z_29,data,sizeof(slot[s].z_29)); result=true;break;}
        case 30:
                    if(data.size() != sizeof(slot[s].z_30)) {result=false; break;}
                    else{memcpy(&slot[s].z_30,data,sizeof(slot[s].z_30)); result=true;break;}
        case 31:
                    if(data.size() != sizeof(slot[s].z_31)) {result=false; break;}
                    else{memcpy(&slot[s].z_31,data,sizeof(slot[s].z_31)); result=true;break;}
        case 32:
                    if(data.size() != sizeof(slot[s].z_32)) {result=false; break;}
                    else{memcpy(&slot[s].z_32,data,sizeof(slot[s].z_32)); result=true;break;}
        case 33:
                    if(data.size() != sizeof(slot[s].z_33)) {result=false; break;}
                    else{memcpy(&slot[s].z_33,data,sizeof(slot[s].z_33)); result=true;break;}
        case 34:
                    if(data.size() != sizeof(slot[s].z_34)) {result=false; break;}
                    else{memcpy(&slot[s].z_34,data,sizeof(slot[s].z_34)); result=true;break;}
        case 35:
                    if(data.size() != sizeof(slot[s].z_35)) {result=false; break;}
                    else{memcpy(&slot[s].z_35,data,sizeof(slot[s].z_35)); result=true;break;}
        case 36:
                    if(data.size() != sizeof(slot[s].z_36)) {result=false; break;}
                    else{memcpy(&slot[s].z_36,data,sizeof(slot[s].z_36)); result=true;break;}
        case 37:
                    if(data.size() != sizeof(slot[s].z_37)) {result=false; break;}
                    else{memcpy(&slot[s].z_37,data,sizeof(slot[s].z_37)); result=true;break;}
        case 38:
                    if(data.size() != sizeof(slot[s].z_38)) {result=false; break;}
                    else{memcpy(&slot[s].z_38,data,sizeof(slot[s].z_38)); result=true;break;}
        case 39:
                    if(data.size() != sizeof(slot[s].z_39)) {result=false; break;}
                    else{memcpy(&slot[s].z_39,data,sizeof(slot[s].z_39)); result=true;break;}
        case 40:
                    if(data.size() != sizeof(slot[s].z_40)) {result=false; break;}
                    else{memcpy(&slot[s].z_40,data,sizeof(slot[s].z_40)); result=true;break;}
        default: result=false; break;
    }
    return result;
}
bool FF7Save::soundMode(int s){return (slot[s].options & (1<<0));}

void FF7Save::setSoundMode(int s,int mode)
{
    if(mode !=soundMode(s))
    {
        switch(mode)
        {
            case SOUND_MONO: slot[s].options &= ~(1<<0); break;
            case SOUND_STEREO: slot[s].options |= (1<<0);   break;
            default: slot[s].options &= ~(1<<0) ; break;
        }
        setFileModified(true,s);
     }
}
void FF7Save::setSoundMode(int s,bool mode)
{
    if(!(mode && soundMode(s)))
    {
        if(mode){slot[s].options |= (1<<0);}
        else{slot[s].options &=~(1<<0);}
        setFileModified(true,s);
    }
}

bool FF7Save::controlMode(int s){return (slot[s].options& (1<<2));}
void FF7Save::setControlMode(int s, int mode)
{
    if(mode !=controlMode(s))
    {
        switch(mode)
        {
            case CONTROL_NORMAL: slot[s].options &= ~(1<<2); break;
            case CONTROL_CUSTOM: slot[s].options |= (1<<2);   break;
            default: slot[s].options &= ~(1<<2) ; break;
        }
        setFileModified(true,s);
     }
}

void FF7Save::setControlMode(int s, bool mode)
{
    if(!(mode && controlMode(s)))
    {
        if(mode){slot[s].options |= (1<<2);}
        else{slot[s].options &=~(1<<2);}
        setFileModified(true,s);
    }
}
bool FF7Save::cursorMode(int s){return (slot[s].options&(1<<4));}

void FF7Save::setCursorMode(int s, int mode)
{
    if(!(mode && cursorMode(s)))
    {
        switch(mode)
        {
            case CURSOR_INITIAL: slot[s].options &= ~(1<<4); break;
            case CURSOR_MEMORY: slot[s].options |= (1<<4);   break;
            default: slot[s].options &= ~(1<<2) ; break;
        }
        setFileModified(true,s);
     }
}
void FF7Save::setCursorMode(int s,  bool mode)
{
    if(mode != cursorMode(s))
    {
        if(mode){slot[s].options |= (1<<4);}
        else{slot[s].options &=~(1<<4);}
        setFileModified(true,s);
    }
}
int FF7Save::atbMode(int s)
{
    if( (slot[s].options &(1<<6))){return 1;}
    else if((slot[s].options &(1<<7))){return 2;}
    else{return 0;}
}

void FF7Save::setAtbMode(int s, int mode)
{
    if(mode != atbMode(s))
    {
        switch(mode)
        {
            case ATB_ACTIVE: slot[s].options &=~(1<<6); slot[s].options&=~(1<<7); break;
            case ATB_RECOMMENED:  slot[s].options |= (1<<6); slot[s].options&= ~(1<<7); break;
            case ATB_WAIT: slot[s].options &= ~(1<<6); slot[s].options |= (1<<7); break;
            default:slot[s].options &=~(1<<6); slot[s].options&= ~(1<<7); break;
        };
        setFileModified(true,s);
    }
}
bool FF7Save::cameraMode(int s){return (slot[s].options&(1<<8));}

void FF7Save::setCameraMode(int s, int mode)
{
    if(mode != cameraMode(s))
    {
        switch(mode)
        {
            case CAMERA_AUTO: slot[s].options &= ~(1<<8); break;
            case CAMERA_FIXED: slot[s].options |= (1<<8); break;
         }
        setFileModified(true,s);
    }
}
void FF7Save::setCameraMode(int s, bool mode)
{
    if(!(mode && cameraMode(s)))
    {
        if(mode){slot[s].options |= (1<<8);}
        else{slot[s].options &=~(1<<8);}
        setFileModified(true,s);
    }
}
int FF7Save::magicOrder(int s)
{
        if ( (slot[s].options&(1<<10)) && (slot[s].options&(1<<11))){return 3;}
        if ((slot[s].options&(1<<10)) && (slot[s].options&(1<<12))){return 5;}
        else if(slot[s].options&(1<<10)){return 1;}
        else if((slot[s].options&(1<<11))){return 2;}
        else if((slot[s].options&(1<<12))){return 4;}
        else{return 0;}
}

void FF7Save::setMagicOrder(int s, int order)
{
    if(order != magicOrder(s))
    switch(order)
    {
        case MAGIC_RAI: slot[s].options &=~(1<<10); slot[s].options &=~(1<<11); slot[s].options &= ~(1<<12); break;
        case MAGIC_RIA: slot[s].options |=(1<<10); slot[s].options &=~(1<<11); slot[s].options &= ~(1<<12); break;
        case MAGIC_AIR: slot[s].options &=~(1<<10); slot[s].options |=(1<<11); slot[s].options &= ~(1<<12); break;
        case MAGIC_ARI: slot[s].options |=(1<<10); slot[s].options |=(1<<11); slot[s].options &= ~(1<<12); break;
        case MAGIC_IRA: slot[s].options &=~(1<<10); slot[s].options &=~(1<<11); slot[s].options |= (1<<12); break;
        case MAGIC_IAR: slot[s].options |=(1<<10); slot[s].options &=~(1<<11); slot[s].options |= (1<<12); break;
        default: slot[s].options &=~(1<<10); slot[s].options &=~(1<<11); slot[s].options &= ~(1<<12); break;
        setFileModified(true,s);
    }
}

bool FF7Save::battleHelp(int s){return ((slot[s].options)&(1<<14));}

void FF7Save::setBattleHelp(int s, bool shown)
{
    if(!(shown && battleHelp(s)))
    {
        if(shown){slot[s].options |=(1<<14);}
        else{slot[s].options &= ~(1<<14);}
        setFileModified(true,s);
    }
}

int FF7Save::battleSpeed(int s){return slot[s].battlespeed;}
void FF7Save::setBattleSpeed(int s, int speed)
{
    if(speed != slot[s].battlespeed)
    {
        if(speed<0 || speed>255){speed=0;}
        else{slot[s].battlespeed=speed;}
        setFileModified(true,s);
    }
}

int FF7Save::messageSpeed(int s){return slot[s].fieldmspeed;}
void FF7Save::setMessageSpeed(int s, int speed)
{
    if(speed != slot[s].fieldmspeed)
    {
        if(speed<0 || speed>255){speed=0;}
        else{slot[s].fieldmspeed=speed;}
        setFileModified(true,s);
    }
}

int FF7Save::battleMessageSpeed(int s){return slot[s].battlemspeed;}
void FF7Save::setBattleMessageSpeed(int s, int speed)
{
    if(speed != slot[s].battlemspeed)
    {
        if(speed<0 || speed>255){speed=0;}
        else{slot[s].battlemspeed=speed;}
        setFileModified(true,s);
    }
}
bool FF7Save::fieldHelp(int s){return ((slot[s].field_help)&(1<<0));}
void FF7Save::setFieldHelp(int s, bool shown)
{
    if(!(shown && fieldHelp(s)))
    {
        if(shown){slot[s].field_help |= (1<<0);}
        else{slot[s].field_help &= ~(1<<0);}
        setFileModified(true,s);
    }
}
bool FF7Save::battleTargets(int s){return ((slot[s].tut_sub)&(1<<6));}
void FF7Save::setBattleTargets(int s, bool shown)
{
    if(!(shown &&battleTargets(s)))
    {
        if(shown){slot[s].tut_sub |= (1<<6);}
        else{slot[s].tut_sub &= ~(1<<6);}
        setFileModified(true,s);
    }
}

quint16 FF7Save::options(int s){return  slot[s].options;}
void FF7Save::setOptions(int s, int opt)
{
    if(opt != options(s))
    {
        slot[s].options= opt;
        setFileModified(true,s);
    }
}
QByteArray FF7Save::controllerMapping(int s)
{
    QByteArray temp;
    for(int i=0;i<16;i++){temp.append(slot[s].controller_map[i]);}
    return temp;
}
quint8 FF7Save::controllerMapping(int s, int action){return slot[s].controller_map[action];}

void FF7Save::setControllerMapping(int s,QByteArray map)
{
    if(map.length()>16){map.chop(16);}
    if(map != controllerMapping(s))
    {
        memcpy(&slot[s].controller_map,map,16);
        setFileModified(true,s);
    }
}
void FF7Save::setControllerMapping(int s, int action,  int button)
{
    if(button<0 || button >15){return;}
    else
    {
        if(slot[s].controller_map[action] != button)
        {
            slot[s].controller_map[action]= button;
            setFileModified(true,s);
        }
    }
}
bool FF7Save::phsVisible(int s, int who)
{
    if(s<0 || s>14){return false;}
    if(who<0 || who>8){return false;}
    else{return ((slot[s].phsvisible) & (1<<who));}
}
void FF7Save::setPhsVisible(int s, int who, bool checked)
{
    if(s<0 || s>14){return;}
    else if(who<0 || who >8){return;}
    else
    {
        if(checked){ slot[s].phsvisible |= (1<<who);}
        else {slot[s].phsvisible &= ~(1<<who);}
        setFileModified(true,s);
    }
}
void FF7Save::setPhsVisible(int s, quint16 phs_visible)
{
    if(s<0 || s>14){return;}
    if(phs_visible!=slot[s].phsvisible)
    {
        slot[s].phsvisible=phs_visible;
        setFileModified(true,s);
    }
}
quint16 FF7Save::phsVisible(int s)
{
    if(s<0 || s>14){return 0;}
    else{return slot[s].phsvisible;}
}

bool FF7Save::phsAllowed(int s, int who)
{
    if(s<0 || s>14){return false;}
    if(who<0 || who>8){return false;}
    else{return ((slot[s].phsallowed) & (1<<who));}
}
quint16 FF7Save::phsAllowed(int s)
{
    if(s<0 || s>14){return 0;}
    else{return slot[s].phsallowed;}
}

void FF7Save::setPhsAllowed(int s, int who, bool checked)
{
    if(s<0 || s>14){return;}
    else if(who<0 || who >8){return;}
    else
    {
        if(checked){ slot[s].phsallowed |= (1<<who);}
        else {slot[s].phsallowed &= ~(1<<who);}
        setFileModified(true,s);
    }
}
void FF7Save::setPhsAllowed(int s, quint16 phs_visible)
{
    if(s<0 || s>14){return;}
    if(phs_visible!=slot[s].phsallowed)
    {
        slot[s].phsallowed=phs_visible;
        setFileModified(true,s);
    }
}
bool FF7Save::menuVisible(int s, int index)
{
    if(s<0 || s>14){return false;}
    if(index<0 || index>9){return false;}
    else{return ((slot[s].menu_visible) & (1<<index));}
}
void FF7Save::setMenuVisible(int s, int index, bool checked)
{
    if(s<0 || s>14){return;}
    else if(index<0 || index >9){return;}
    else
    {
        if(checked){ slot[s].menu_visible |= (1<<index);}
        else {slot[s].menu_visible &= ~(1<<index);}
        setFileModified(true,s);
    }
}
void FF7Save::setMenuVisible(int s, quint16 menu_visible)
{
    if(s<0 || s>14){return;}
    if(menu_visible!=slot[s].menu_visible)
    {
        slot[s].menu_visible=menu_visible;
        setFileModified(true,s);
    }
}
quint16 FF7Save::menuVisible(int s)
{
    if(s<0 || s>14){return 0;}
    else{return slot[s].menu_visible;}
}

bool FF7Save::menuLocked(int s, int index)
{
    if(s<0 || s>14){return false;}
    if(index<0 || index>9){return false;}
    else{return ((slot[s].menu_locked) & (1<<index));}
}
void FF7Save::setMenuLocked(int s, int index, bool checked)
{
    if(s<0 || s>14){return;}
    else if(index<0 || index >9){return;}
    else
    {
        if(checked){ slot[s].menu_locked |= (1<<index);}
        else {slot[s].menu_locked &= ~(1<<index);}
        setFileModified(true,s);
    }
}
void FF7Save::setMenuLocked(int s, quint16 menu_locked)
{
    if(s<0 || s>14){return;}
    if(menu_locked!=slot[s].menu_locked)
    {
        slot[s].menu_locked=menu_locked;
        setFileModified(true,s);
    }
}
quint16 FF7Save::menuLocked(int s)
{
    if(s<0 || s>14){return 0;}
    else{return slot[s].menu_locked;}
}
quint16 FF7Save::locationId(int s)
{
    if(s<0 || s>14){return 0;}
    else{return slot[s].locationid;}
}

void FF7Save::setLocationId(int s, quint16 locationID)
{
    if(s<0 || s>14){return;}
    else if (locationID == locationId(s)){return;}
    else
    {
        slot[s].locationid = locationID;
        setFileModified(true,s);
    }
}
quint16 FF7Save::mapId(int s)
{
    if(s<0 || s>14){return 0;}
    else{return slot[s].mapid;}
}

void FF7Save::setMapId(int s, quint16 mapID)
{
    if(s<0 || s>14){return;}
    else if (mapID == mapId(s)){return;}
    else
    {
        slot[s].mapid = mapID;
        setFileModified(true,s);;
    }
}
qint16 FF7Save::locationX(int s)
{
    if(s<0 || s>14){return 0;}
    else{return slot[s].coord.x;}
}

void FF7Save::setLocationX(int s, qint16 x)
{
    if(s<0 || s>14){return;}
    else if (x == locationX(s)){return;}
    else
    {
        slot[s].coord.x = x;
        setFileModified(true,s);
    }
}
qint16 FF7Save::locationY(int s)
{
    if(s<0 || s>14){return 0;}
    else{return slot[s].coord.y;}
}

void FF7Save::setLocationY(int s, qint16 y)
{
    if(s<0 || s>14){return;}
    else if (y == locationY(s)){return;}
    else
    {
        slot[s].coord.y = y;
        setFileModified(true,s);
    }
}
quint16 FF7Save::locationT(int s)
{
    if(s<0 || s>14){return 0;}
    else{return slot[s].coord.t;}
}

void FF7Save::setLocationT(int s, quint16 t)
{
    if(s<0 || s>14){return;}
    else if (t == locationT(s)){return;}
    else
    {
        slot[s].coord.t = t;
        setFileModified(true,s);
    }
}
quint8 FF7Save::locationD(int s)
{
    if(s<0 || s>14){return 0;}
    else{return slot[s].coord.d;}
}

void FF7Save::setLocationD(int s, quint8 d)
{
    if(s<0 || s>14){return;}
    else if (d == locationD(s)){return;}
    else
    {
        slot[s].coord.d = d;
        setFileModified(true,s);
    }
}

// Z_38[12] Item Flags.
bool FF7Save::gaiin_1Ribbon(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[12])&(1<<7));}
}
void FF7Save::setGaiin_1Ribbon(int s,bool PickedUp)
{
    if(!(PickedUp && gaiin_1Ribbon(s)))
    {
        if(PickedUp){slot[s].z_38[12] |= (1<<7);}
        else{slot[s].z_38[12] &= ~(1<<7);}
        setFileModified(true,s);
    }
}
bool FF7Save::gaiin_5Elixir(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[12])&(1<<6));}
}
void FF7Save::setGaiin_5Elixir(int s, bool PickedUp)
{
    if(!(PickedUp && gaiin_5Elixir(s)))
    {
        if(PickedUp){slot[s].z_38[12] |= (1<<6);}
        else{slot[s].z_38[12] &= ~(1<<6);}
        setFileModified(true,s);
    }
}
bool FF7Save::gaiin_1Javelin(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[12])&(1<<5));}
}
void FF7Save::setGaiin_1Javelin(int s, bool PickedUp)
{
    if(!(PickedUp && gaiin_1Javelin(s)))
    {
        if(PickedUp){slot[s].z_38[12] |= (1<<5);}
        else{slot[s].z_38[12] &= ~(1<<5);}
        setFileModified(true,s);
    }
}

bool FF7Save::gaiin_3SpeedSource(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[12])&(1<<4));}
}
void FF7Save::setGaiin_3SpeedSource(int s, bool PickedUp)
{
    if(!(PickedUp && gaiin_3SpeedSource(s)))
    {
        if(PickedUp){slot[s].z_38[12] |= (1<<4);}
        else{slot[s].z_38[12] &= ~(1<<4);}
        setFileModified(true,s);
    }
}

bool FF7Save::gaiin_3Elixir(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[12])&(1<<3));}
}
void FF7Save::setGaiin_3Elixir(int s, bool PickedUp)
{
    if(!(PickedUp && gaiin_3Elixir(s)))
    {
        if(PickedUp){slot[s].z_38[12] |= (1<<3);}
        else{slot[s].z_38[12] &= ~(1<<3);}
        setFileModified(true,s);
    }
}

bool FF7Save::gaiin_5FireArmlet(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[12])&(1<<2));}
}
void FF7Save::setGaiin_5FireArmlet(int s, bool PickedUp)
{
    if(!(PickedUp && gaiin_5FireArmlet(s)))
    {
        if(PickedUp){slot[s].z_38[12] |= (1<<2);}
        else{slot[s].z_38[12] &= ~(1<<2);}
        setFileModified(true,s);
    }
}
bool FF7Save::gaiin_4EnhanceSword(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[12])&(1<<1));}
}
void FF7Save::setGaiin_4EnhanceSword(int s, bool PickedUp)
{
    if(!(PickedUp && gaiin_4EnhanceSword(s)))
    {
        if(PickedUp){slot[s].z_38[12] |= (1<<1);}
        else{slot[s].z_38[12] &= ~(1<<1);}
        setFileModified(true,s);
    }
}

//z_38[13] Item Flags
bool FF7Save::snmayorTurboEther(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[13])&(1<<5));}
}
void FF7Save::setSnmayorTurboEther(int s,bool PickedUp)
{
    if(!(PickedUp && snmayorTurboEther(s)))
    {
        if(PickedUp){slot[s].z_38[13] |= (1<<5);}
        else{slot[s].z_38[13] &= ~(1<<5);}
        setFileModified(true,s);
    }
}

bool FF7Save::sninn2XPotion(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[13])&(1<<4));}
}
void FF7Save::setSninn2XPotion(int s,bool PickedUp)
{
    if(!(PickedUp && sninn2XPotion(s)))
    {
        if(PickedUp){slot[s].z_38[13] |= (1<<4);}
        else{slot[s].z_38[13] &= ~(1<<4);}
        setFileModified(true,s);
    }
}

bool FF7Save::snmin2Vaccine(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[13])&(1<<3));}
}
void FF7Save::setSnmin2Vaccine(int s,bool PickedUp)
{
    if(!(PickedUp && snmin2Vaccine(s)))
    {
        if(PickedUp){slot[s].z_38[13] |= (1<<3);}
        else{slot[s].z_38[13] &= ~(1<<3);}
        setFileModified(true,s);
    }
}

bool FF7Save::snmin2HeroDrink(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[13])&(1<<2));}
}
void FF7Save::setSnmin2HeroDrink(int s,bool PickedUp)
{
    if(!(PickedUp && snmin2HeroDrink(s)))
    {
        if(PickedUp){slot[s].z_38[13] |= (1<<2);}
        else{slot[s].z_38[13] &= ~(1<<2);}
        setFileModified(true,s);
    }
}

bool FF7Save::ncoin3Catastrophe(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[13])&(1<<1));}
}
void FF7Save::setNcoin3Catastrophe(int s,bool PickedUp)
{
    if(!(PickedUp && ncoin3Catastrophe(s)))
    {
        if(PickedUp){slot[s].z_38[13] |= (1<<1);}
        else{slot[s].z_38[13] &= ~(1<<1);}
        setFileModified(true,s);
    }
}

bool FF7Save::ncoin1Ether(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[13])&(1<<0));}
}
void FF7Save::setNcoin1Ether(int s,bool PickedUp)
{
    if(!(PickedUp && ncoin1Ether(s)))
    {
        if(PickedUp){slot[s].z_38[13] |= (1<<0);}
        else{slot[s].z_38[13] &= ~(1<<0);}
        setFileModified(true,s);
    }
}
//z_38[14] Item Flags
bool FF7Save::trnad_4MpTurbo(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[14])&(1<<3));}
}
void FF7Save::setTrnad_4MpTurbo(int s,bool PickedUp)
{
    if(!(PickedUp && trnad_4MpTurbo(s)))
    {
        if(PickedUp){slot[s].z_38[14] |= (1<<3);}
        else{slot[s].z_38[14] &= ~(1<<3);}
        setFileModified(true,s);
    }
}
bool FF7Save::trnad_3KaiserKnuckle(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[14])&(1<<2));}
}
void FF7Save::setTrnad_3KaiserKnuckle(int s,bool PickedUp)
{
    if(!(PickedUp && trnad_3KaiserKnuckle(s)))
    {
        if(PickedUp){slot[s].z_38[14] |= (1<<2);}
        else{slot[s].z_38[14] &= ~(1<<2);}
        setFileModified(true,s);
    }
}

bool FF7Save::trnad_4PoisonRing(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[14])&(1<<1));}
}
void FF7Save::setTrnad_4PoisonRing(int s,bool PickedUp)
{
    if(!(PickedUp && trnad_4PoisonRing(s)))
    {
        if(PickedUp){slot[s].z_38[14] |= (1<<2);}
        else{slot[s].z_38[14] &= ~(1<<2);}
        setFileModified(true,s);
    }
}

bool FF7Save::trnad_2NeoBahmut(int s)
{
    if(s<0 || s>14){return false;}
    else{return ((slot[s].z_38[14])&(1<<0));}
}
void FF7Save::setTrnad_2NeoBahmut(int s,bool PickedUp)
{
    if(!(PickedUp && trnad_2NeoBahmut(s)))
    {
        if(PickedUp){slot[s].z_38[14] |= (1<<0);}
        else{slot[s].z_38[14] &= ~(1<<0);}
        setFileModified(true,s);
    }
}
quint16 FF7Save::condorFunds(int s)
{
    if(s<0 || s>14){return 0;}
    else
    {
        quint16 a = (slot[s].z_16[52] | (slot[s].z_16[53] <<8));
        return a;
    }
}
void FF7Save::setCondorFunds(int s,quint16 value)
{
    if(value==condorFunds(s)){return;}
    else
    {
        slot[s].z_16[52] = (value & 0xff);
        slot[s].z_16[53]= (value & 0xff00) >> 8;
    }
}
quint8 FF7Save::condorWins(int s)
{
    if(s<0 || s>14){return 0;}
    else{return  quint8(slot[s].z_16[39]);}
}
void FF7Save::setCondorWins(int s,quint8 wins)
{
    if(wins ==condorWins(s)){return;}
    else{slot[s].z_16[39] = wins;}
}
quint8 FF7Save::condorLoses(int s)
{
    if(s<0 || s>14){return 0;}
    else{return  quint8(slot[s].z_16[38]);}
}
void FF7Save::setCondorLoses(int s, quint8 loses)
{
    if(loses ==condorLoses(s)){return;}
    else{slot[s].z_16[38] = loses;}
}
