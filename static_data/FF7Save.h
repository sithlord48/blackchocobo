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
#ifndef DEF_FF7SAVE
#define DEF_FF7SAVE
#include "FF7Save_Const.h" //All consts placed here
#include "FF7Save_Types.h" //All Custom Types for this class here.
#include <QObject>
#include <cstdlib>

class FF7Save{

public:
  bool LoadFile(const QString &fileName);
  bool SaveFile(const QString &fileName);
  bool Export_PC(const QString &fileName);
  bool Export_PSX(const QString &fileName);
  bool Export_VMC(const QString &fileName);
  bool Export_DEX(const QString &fileName);
  bool Export_VGS(const QString &fileName);
  void clearslot(int s);
  void CopySlot(int s);
  void PasteSlot(int s);
  void New_Game(int s,QString fileName=""); //new game in slot s
  void New_Game_Plus(int s);
  quint16 itemId(int s,int item_num);
  quint8 itemQty(int s,int item_num);
  void setItemId(int s,int item_num,quint16 new_id);
  void setItemQty(int s,int item_num,quint8 new_qty);

  //publicly accessable core data(for now)
  FF7SLOT slot[15]; //core slot data.
  FF7HEADFOOT hf[15]; //slot header and footer.
  quint8 * file_headerp;              //pointer to file header
  quint8 * file_footerp;              //pointer to file footer

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
  //Set Needed Info Stuffs
  void setType(QString);//allows for slot change.
  QString region(int s);
  void setRegion(int s ,QString region);

  bool isEmpty(int s);//empty slot?
  bool isFF7(int s);//valid ff7 slot?
  bool isPAL(int s);//PAL SLOT?
  bool isNTSC(int s);//NTSC SLOT??

  void fix_pc_bytemask(int s);// update so last slot is shown selected on load (must be public to set to currently viewed slot).

private:
  //data members
  //FF7SLOT slot[15];
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
  qint16 itemDecode( quint16 itemraw );
  qint16 itemEncode( quint16 id, quint8 qty );
};

#endif //FF7Save
