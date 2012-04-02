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
#ifndef DEF_FF7SAVE
#define DEF_FF7SAVE
#include "FF7Save_Const.h" //All consts placed here
#include "FF7Save_Types.h" //All Custom Types for this class here.
#include "FF7Text.h"
#include <QObject>
#include <cstdlib>

class FF7Save{

public:
  //File Members
  bool LoadFile(const QString &fileName);
  bool SaveFile(const QString &fileName);
  bool Export_PC(const QString &fileName);
  bool Export_PSX(const QString &fileName);
  bool Export_VMC(const QString &fileName);
  bool Export_DEX(const QString &fileName);
  bool Export_VGS(const QString &fileName);
  void Import_PSX(int s,const QString &fileName);
  void Import_PSV(int s,const QString &fileName);
  void clearslot(int s);
  void CopySlot(int s);
  void PasteSlot(int s);
  void New_Game(int s,QString fileName=""); //new game in slot s (over load default w/ fileName must be RAW PSX)
  void New_Game_Plus(int s,QString CharFileName,QString fileName="");//new game + in slot s (over load default w/ fileName must be RAW PSX)

  bool exportChar(int s,int char_num,QString fileName);// Write slot[s].char[char_num] to fileName
  void importChar(int s,int char_num,QByteArray new_char);//import new_char to slot[s].char[char_num]
  //Set/Get Data Parts.
  quint16 itemId(int s,int item_num);
  quint8 itemQty(int s,int item_num);

  void setItem(int s,int item_num,quint16 new_id,quint8 new_qty);

  //materia get/set
  quint8 partyMateriaId(int s,int mat_num);
  qint32 partyMateriaAp(int s,int mat_num);
  quint8 charMateriaId(int s,int who,int mat_num);
  qint32 charMateriaAp(int s,int who,int mat_num);
  quint8 stolenMateriaId(int s,int mat_num);
  qint32 stolenMateriaAp(int s,int mat_num);
  void setPartyMateria(int s,int mat_num,quint8 id,qint32 ap);
  void setStolenMateria(int s, int mat_num,quint8 id,qint32 ap);
  void setCharMateria(int s,int who,int mat_num,quint8 id,qint32 ap);

  // String Functions.
  QString charName(int s,int char_num);//Return Char name
  void setCharName(int s,int char_num,QString new_name);//write char_num 's new_name to slot s
  QString chocoName(int s,int choco_num);//return choco_num's name.
  void setChocoName(int s,int choco_num,QString new_name);//write choco_num 's new_name to slot s
  QString location(int s);// return save location string
  void setLocation(int s, QString new_location);//set save location string to new_location
  QString descName(int s);//return the name in the description
  void setDescName(int s,QString new_name);// desc name = new_name
  QString descLocation(int s);//return the location string used in the description
  void setDescLocation(int s, QString new_desc_location);//write new desc location string called from setLocation

  //publicly accessable core data(for now)
  FF7SLOT slot[15]; //core slot data.

  // Return File Info
  int len_file(void);//Return File length.
  int len_file_header(void);//Return File Header length
  int len_file_footer(void);//Return File Footer length
  int len_core_save(void);//Return Slot length (data portion)
  int len_slot_header(void);//Return slot header length
  int len_slot_footer(void);//Return slot footer length
  int len_slot(void);//Return Slot length
  int number_slots(void);//Return number of slots in the file_footer_dex
  QString type(void);// Returns the file type loaded.
  bool isFF7(int s);//valid ff7 slot?
  bool isPAL(int s);//PAL SLOT?
  bool isNTSC(int s);//NTSC SLOT??
  bool isJPN(int s);//is a Japanese File
  QString region(int s);// region string of slot s
  //Set Needed Info Stuffs
  void setType(QString);//allows for slot change.
  void setRegion(int s ,QString region);
  QByteArray slot_header(int s); //return slot header.

  quint8 psx_block_type(int s);//mask of psx slot (used by index)
  quint8 psx_block_next(int s);// if using more then one block return location of next block
  quint8 psx_block_size(int s);//how many blocks save uses.
  void fix_pc_bytemask(int s);// update so last slot is shown selected on load (must be public to set to currently viewed slot).
  int stat_gain(int who,int stat, int stat_amount, int next_lvl); //The "level up" function must be called once per stat per level up.
private:
  //data members
  //FF7SLOT slot[15];
  FF7HEADFOOT hf[15]; //slot header and footer.
  quint8 * file_headerp;              //pointer to file header
  quint8 * file_footerp;              //pointer to file footer
  quint8 file_header_pc [0x0009];    // [0x0000] 0x06277371 this replace quint8 file_tag[9];
  quint8 file_header_psx[0x0000];	// [0x0000] 0x06277371 this replace quint8 file_tag[9];
  quint8 file_header_psv[0x0000];
  quint8 file_header_psp[0x2080];
  quint8 file_header_vgs[0x2040]; //header for vgs/mem ext format.
  quint8 file_header_dex[0x2F40]; //header for gme (dex-drive format)
  quint8 file_header_mc [0x2000];	// [0x0000] 0x06277371 this replace quint8 file_tag[9];
  quint8 file_footer_pc [0x0000];	// [0x0000] 0x06277371
  quint8 file_footer_psx[0x0000];	// [0x0000] 0x06277371
  quint8 file_footer_psv[0x0000];
  quint8 file_footer_vgs[0x0000];
  quint8 file_footer_dex[0x0000];
  quint8 file_footer_mc [0x0000];	// [0x0000] 0x06277371
  quint8 file_footer_psp[0x0000];

  FF7SLOT buffer_slot;// hold a buffer slot
  QString buffer_region; // hold the buffers region data.
  QString SG_Region_String[15];
  FF7TEXT Text;
  int SG_SIZE;
  int SG_HEADER;
  int SG_FOOTER;
  int SG_DATA_SIZE;
  int SG_SLOT_HEADER;
  int SG_SLOT_FOOTER;
  int SG_SLOT_SIZE;
  int SG_SLOT_NUMBER;
  QString SG_TYPE;
  //private functions
  void fix_sum(const QString &fileName);
  int ff7__checksum(void * qw );
  void fix_psv_header(void);
  void fix_psx_header(int s);
  void fix_vmc_header(void);
  quint16 itemDecode( quint16 itemraw );
  quint16 itemEncode( quint16 id, quint8 qty );
};

#endif //FF7Save
