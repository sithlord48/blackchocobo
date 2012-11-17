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
#include<QColor>
#include <cstdlib>
#include <QFileInfo>
#include <QDateTime>
#include <QVector>
#include <QtXml/QDomDocument>

class FF7Save{

public:
    enum  LOVER{LOVE_BARRET,LOVE_TIFA,LOVE_AERIS,LOVE_YUFFIE};
    enum MATERIACAVE{CAVE_MIME,CAVE_HPMP,CAVE_QUADMAGIC,CAVE_KOTR};
    //Options Enums
    enum SOUNDMODE{SOUND_MONO,SOUND_STEREO};
    enum CONTROLMODE {CONTROL_NORMAL,CONTROL_CUSTOM};
    enum CURSORMODE{CURSOR_INITIAL, CURSOR_MEMORY};
    enum ATBMODE{ATB_ACTIVE,ATB_RECOMMENED,ATB_WAIT};
    enum CAMERAMODE {CAMERA_AUTO,CAMERA_FIXED};
    enum MAGICORDER {MAGIC_RAI,MAGIC_RIA,MAGIC_AIR,MAGIC_ARI,MAGIC_IRA,MAGIC_IAR};
    enum CONTROLACTION
    {
        ACTION_CAMERA,ACTION_TARGET,ACTION_PAGEUP,ACTION_PAGEDOWN,
        ACTION_MENU,ACTION_OK,ACTION_CANCEL,ACTION_SWITCH,
        ACTION_HELP,ACTION_UNKNOWN1,ACTION_UNKNOWN2,
        ACTION_PAUSE,ACTION_UP,ACTION_DOWN,ACTION_LEFT,ACTION_RIGHT
    };
    enum PSXBUTTONS
    {
        BTN_L2,BTN_R2,BTN_L1,BTN_R1,
        BTN_TRIANGLE,BTN_CIRCLE,BTN_X,BTN_SQUARE,
        BTN_SELECT,BTN_UNKNOWN1,BTN_UNKNOWN2,BTN_START,
        BTN_UP,BTN_DOWN,BTN_LEFT,BTN_RIGHT
    };
    enum PSXBLOCKTYPE {BLOCK_EMPTY= 0xA0, BLOCK_MAIN=0x51,BLOCK_DELETED_MAIN=0xA1,BLOCK_MIDLINK=0x52,BLOCK_DELETED_MIDLINK=0xA2,BLOCK_ENDLINK=0x53,BLOCK_DELETED_ENDLINK=0xA3};
    QByteArray slotHeader(int s);
    QByteArray slotFooter(int s);
    QByteArray slotPsxRawData(int s);

    bool setSlotHeader(int s,QByteArray data);
    bool setSlotFooter(int s,QByteArray data);
    bool setSlotPsxRawData(int s,QByteArray data);

    QByteArray controllerMapping(int s);
    quint8 controllerMapping(int s, int action);

    void setControllerMapping(int s,QByteArray map);
    void setControllerMapping(int s, int action,  int button);

    quint16 options(int s);
    void setOptions(int s, int opt);
    bool soundMode(int s);
    void setSoundMode(int s, int mode);
    void setSoundMode(int s, bool mode);
    bool controlMode(int s);
    void setControlMode(int s, int mode);
    void setControlMode(int s, bool mode);
    bool cursorMode(int s);
    void setCursorMode(int s, int mode);
    void setCursorMode(int s, bool mode);
    int atbMode(int s);
    void setAtbMode(int s, int mode);
    bool cameraMode(int s);
    void setCameraMode(int s, int mode);
    void setCameraMode(int s, bool mode);
    int magicOrder(int s);
    void setMagicOrder(int s , int order);
    bool battleHelp(int s);
    void setBattleHelp(int s, bool shown);
    int  battleSpeed(int s);
    void setBattleSpeed(int s,int speed);
    int battleMSpeed(int s);
    void setBattleMSpeed(int s, int speed);
    int messageSpeed(int s);
    void setMessageSpeed(int s, int speed);
    bool fieldHelp(int s);
    void setfieldHelp(int s, bool shown);
    bool battleTargets(int s);
    void setBattleTargets(int s, bool shown);
  //File Members
  bool LoadFile(const QString &fileName);
  bool SaveFile(const QString &fileName);
  bool Export_PC(const QString &fileName);
  bool Export_PSX(int s,const QString &fileName);
  bool Export_VMC(const QString &fileName);
  bool Export_DEX(const QString &fileName);
  bool Export_VGS(const QString &fileName);
  void Import_PSX(int s,const QString &fileName);
  void Import_PSV(int s,const QString &fileName);
  void clearslot(int s);
  void CopySlot(int s);
  void PasteSlot(int s);
  void New_Game(int s,QString fileName=""); //new game in slot s (over load default w/ fileName must be RAW PSX)
  void New_Game_Plus(int s,QString CharFileName,QString fileName="");//new game + in slot s (over load default w/ fileName must be RAW PSX
  bool exportChar(int s,int char_num,QString fileName);// Write slot[s].char[char_num] to fileName
  void importChar(int s,int char_num,QByteArray new_char);//import new_char to slot[s].char[char_num]
  typedef QVector< QString > SubContainer;
  QVector< SubContainer >  parsexml(QString fileName,QString metadataPath,QString UserID);
  QVector< SubContainer >  CreateMetadata(QString fileName, QString UserID);
  //Set/Get Data Parts.
  bool FixMetaData(QString fileName="",QString OutPath="",QString UserID="");
  quint16 battlePoints(int s);
  void setBattlePoints(int s,quint16);
  quint16 item(int s,int item_num); //return raw ff7item
  QList<quint16> items(int s);// return all items
  quint16 itemId(int s,int item_num);
  quint16 itemId(quint16 rawitem);
  quint8 itemQty(int s,int item_num);
  quint8 itemQty(quint16 rawitem);

  void setItems(int s,QList<quint16> items);
  void setItem(int s,int item_num,quint16 rawitem);
  void setItem(int s,int item_num,quint16 new_id,quint8 new_qty);

  //materia get/set
  bool  materiaCave(int s,MATERIACAVE cave);
  void setMateriaCave(int s, MATERIACAVE cave, bool hasMateria);

  quint8 partyMateriaId(int s,int mat_num);
  qint32 partyMateriaAp(int s,int mat_num);
  quint8 stolenMateriaId(int s,int mat_num);
  qint32 stolenMateriaAp(int s,int mat_num);
  void setPartyMateria(int s,int mat_num,quint8 id,qint32 ap);
  void setStolenMateria(int s, int mat_num,quint8 id,qint32 ap);
  quint32 time(int s);
  void setTime(int s,quint32 new_time);
  void setDisc(int s,int disc);
  quint8 disc(int s);
  //Description Stuff.
  quint32 descTime(int s);
  void setDescTime(int s,quint32 new_time);
  QString descName(int s);//return the name in the description
  void setDescName(int s,QString new_name);// desc name = new_name
  QString descLocation(int s);//return the location string used in the description
  void setDescLocation(int s, QString new_desc_location);//write new desc location string called from setLocation
  quint8 descLevel(int s);
  void setDescLevel(int s,int new_level);
  quint8 descParty(int s,int char_num);
  void setDescParty(int s,int char_num,quint8 new_id);
  quint16 descCurHP(int s);
  void setDescCurHP(int s,quint16 new_curHP);
  quint16 descMaxHP(int s);
  void setDescMaxHP(int s,quint16 new_maxHP);
  quint16 descCurMP(int s);
  void setDescCurMP(int s,quint16 new_curMP);
  quint16 descMaxMP(int s);
  void setDescMaxMP(int s,quint16 new_maxMP);
  quint32 descGil(int s);
  void setDescGil(int s,quint32 new_gil);
  //Dialog Colors
  QColor Dialog_UL(int s);
  QColor Dialog_UR(int s);
  QColor Dialog_LL(int s);
  QColor Dialog_LR(int s);

  void setDialog_UL(int s,QColor color);
  void setDialog_UR(int s,QColor color);
  void setDialog_LL(int s,QColor color);
  void setDialog_LR(int s,QColor color);
  // String Functions.
  QString chocoName(int s,int choco_num);//return choco_num's name.
  void setChocoName(int s,int choco_num,QString new_name);//write choco_num 's new_name to slot s
  QString location(int s);// return save location string
  void setLocation(int s, QString new_location);//set save location string to new_location
  quint32 Gil(int s);
  void setGil(int s,int gil);
  quint16 Gp (int s);
  void setGp(int s,int gp);
  quint16 Battles (int s);
  void setBattles(int s,int battles);
  quint16 Runs (int s);
  void setRuns(int s,int runs);
  quint8 Party(int s,int pos);
  void setParty(int s,int pos, int new_id);
  qint8 ChocoPen(int s, int pos);
  void setChocoPen(int s, int pos, int type);

  //Mini Game Stuff
  quint8 love(int s,bool battle, LOVER who);
  void setLove(int s,bool battle, LOVER who ,quint8 love);
  quint16 speedScore(int s, int rank);
  void setSpeedScore(int s,int rank,quint16 score);
  quint16 BikeHighScore(int s);
  void setBikeHighScore(int s,quint16 score);
  quint32 snowboardTime(int s,int course);
  void setSnowboardTime(int s,int course,quint32 time);
  quint8 snowboardScore(int s,int course);
  void setSnowboardScore(int s,int course,quint8 score);
  //Char Releated Functions
  FF7CHAR Char(int s,int char_num); //Return Full Char
  quint8 charID(int s,int char_num);//Return Char ID
  quint8 charLevel(int s,int char_num);//Return Char Level
  quint8 charStr(int s,int char_num);
  quint8 charVit(int s,int char_num);
  quint8 charMag(int s,int char_num);
  quint8 charSpi(int s,int char_num);
  quint8 charDex(int s,int char_num);
  quint8 charLck(int s,int char_num);
  quint8 charStrBonus(int s,int char_num);
  quint8 charVitBonus(int s,int char_num);
  quint8 charMagBonus(int s,int char_num);
  quint8 charSpiBonus(int s,int char_num);
  quint8 charDexBonus(int s,int char_num);
  quint8 charLckBonus(int s,int char_num);
  qint8  charLimitLevel(int s,int char_num);
  quint8 charLimitBar(int s,int char_num);
  QString charName(int s,int char_num);//Return Char name
  quint8 charWeapon(int s,int char_num);
  quint8 charArmor(int s,int char_num);
  quint8 charAccessory(int s,int char_num);
  quint8 charFlag(int s,int char_num,int flag_num);
  quint16 charLimits(int s,int char_num);//Return Char ID
  quint16 charKills(int s,int char_num);//Return Char Level
  quint16 charTimesLimitUsed(int s,int char_num,int level);
  quint16 charCurrentHp(int s,int char_num);
  quint16 charBaseHp(int s,int char_num);
  quint16 charCurrentMp(int s,int char_num);
  quint16 charBaseMp(int s,int char_num);
  quint8 charUnknown(int s,int char_num,int unknown_num);
  quint16 charMaxHp(int s,int char_num);
  quint16 charMaxMp(int s,int char_num);
  quint32 charCurrentExp(int s,int char_num);
  quint32 charNextExp(int s,int char_num);
  quint8 charMateriaId(int s,int who,int mat_num);
  qint32 charMateriaAp(int s,int who,int mat_num);
  void setChar(int s,int char_num,FF7CHAR new_char);
  void  setCharID(int s,int char_num,qint8 new_id);
  void  setCharLevel(int s,int char_num,qint8 new_level);
  void  setCharStr(int s,int char_num,quint8 str);
  void  setCharVit(int s,int char_num,quint8 vit);
  void  setCharMag(int s,int char_num,quint8 mag);
  void  setCharSpi(int s,int char_num,quint8 spi);
  void  setCharDex(int s,int char_num,quint8 dex);
  void  setCharLck(int s,int char_num,quint8 lck);
  void  setCharStrBonus(int s,int char_num,quint8 strbonus);
  void  setCharVitBonus(int s,int char_num,quint8 vitbonus);
  void  setCharMagBonus(int s,int char_num,quint8 magbonus);
  void  setCharSpiBonus(int s,int char_num,quint8 spibonus);
  void  setCharDexBonus(int s,int char_num,quint8 dexbonus);
  void  setCharLckBonus(int s,int char_num,quint8 lckbonus);
  void  setCharLimitLevel(int s,int char_num,qint8 limitlevel);
  void  setCharLimitBar(int s,int char_num,quint8 limitbar);
  void setCharName(int s,int char_num,QString new_name);//write char_num 's new_name to slot s
  void  setCharWeapon(int s,int char_num,quint8 weapon);
  void  setCharArmor(int s,int char_num,quint8 armor);
  void  setCharAccessory(int s,int char_num,quint8 accessory);
  void  setCharFlag(int s,int char_num,int flag_num,quint8 flag_value);
  void  setCharLimits(int s,int char_num,quint16 new_limits);
  void  setCharKills(int s,int char_num,quint16 kills);
  void  setCharTimeLimitUsed(int s,int char_num,int level,quint16 timesused);
  void  setCharCurrentHp(int s,int char_num,quint16 curHp);
  void  setCharBaseHp(int s,int char_num,quint16 baseHp);
  void  setCharCurrentMp(int s,int char_num,quint16 curMp);
  void  setCharBaseMp(int s,int char_num,quint16 baseMp);
  void  setCharUnknown(int s,int char_num,int unknown_num,quint8 value);
  void  setCharMaxHp(int s,int char_num,quint16 maxHp);
  void  setCharMaxMp(int s,int char_num,quint16 maxMp);
  void  setCharCurrentExp(int s,int char_num,quint32 exp);
  void  setCharNextExp(int s,int char_num,quint32 next);
  void setCharMateria(int s,int who,int mat_num,quint8 id,qint32 ap);
  void setCharMateria(int s,int who,int mat_num,materia mat);
  //chocobo Stuff.
  FF7CHOCOBO chocobo(int s,int chocoSlot);
  quint16 chocoStamina(int s,int chocoSlot);
  quint16 chocoSpeed(int s,int chocoSlot);
  quint16 chocoMaxSpeed(int s,int chocoSlot);
  quint16 chocoSprintSpeed(int s,int chocoSlot);
  quint16 chocoMaxSprintSpeed(int s,int chocoSlot);
  quint8 chocoSex(int s, int chocoSlot);
  quint8 chocoType(int s, int chocoSlot);
  quint8 chocoCoop(int s, int chocoSlot);
  quint8 chocoAccel(int s, int chocoSlot);
  quint8 chocoIntelligence(int s, int chocoSlot);
  quint8 chocoRaceswon(int s, int chocoSlot);
  quint8 chocoPCount(int s, int chocoSlot);
  quint8 chocoPersonality(int s, int chocoSlot);
  bool chocoCantMate(int s, int chocoSlot);
  void setChocoStamina(int s,int chocoSlot,quint16 stamina);
  void setChocoSpeed(int s,int chocoSlot,quint16 speed);
  void setChocoMaxSpeed(int s,int chocoSlot,quint16 maxspeed);
  void setChocoSprintSpeed(int s,int chocoSlot,quint16 sprintSpeed);
  void setChocoMaxSprintSpeed(int s,int chocoSlot,quint16 maxsprintSpeed);
  void setChocoSex(int s, int chocoSlot,quint8 value);
  void setChocoType(int s, int chocoSlot,quint8 value);
  void setChocoCoop(int s, int chocoSlot,quint8 value);
  void setChocoAccel(int s, int chocoSlot,quint8 value);
  void setChocoIntelligence(int s, int chocoSlot,quint8 value);
  void setChocoRaceswon(int s, int chocoSlot,quint8 value);
  void setChocoPCount(int s, int chocoSlot,quint8 value);
  void setChocoPersonality(int s, int chocoSlot,quint8 value);
  void setChocoCantMate(int s,int chocoSlot,bool cantMate);
  // Return File Info

  int len_file(void);//Return File length.
  int len_file_header(void);//Return File Header length
  int len_file_footer(void);//Return File Footer length
  int len_core_save(void);//Return Slot length (data portion)
  int len_slot_header(void);//Return slot header length
  int len_slot_footer(void);//Return slot footer length
  int len_slot(void);//Return Slot length
  int number_slots(void);//Return number of slots in the file_footer_dex
  QString fileName(void);//return loaded filename
  QString type(void);// Returns the file type loaded.
  void FileModified(bool,int s);//file changed toggle, with slot called
  bool isFileModified(void);//has the file changed since load
  bool isSlotModified(int s);//has slot[s] changed since load.
  bool isSlotEmpty(int s);//is Slot s empty
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
  void setPsx_block_type(int s,FF7Save::PSXBLOCKTYPE block_type);
  quint8 psx_block_next(int s);// if using more then one block return location of next block
  void setPsx_block_next(int s,int next);
  quint8 psx_block_size(int s);//how many blocks save uses.
  void setPsx_block_size(int s,int blockSize);
  void fix_pc_bytemask(int s);// update so last slot is shown selected on load (must be public to set to currently viewed slot).

  QByteArray slotFF7Data(int s); //Return Raw data from the slot
  bool setSlotFF7Data(int s, QByteArray data);
  bool setSlotFF7Data(int s, FF7SLOT data);

  QByteArray UnknownVar(int s,int z);
  bool setUnknownVar(int s,int z,QByteArray data);

  //publicly accessable core data(for now)
  FF7SLOT slot[15]; //core slot data.
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
  QString filename;//opened file;
  FF7TEXT Text;
  bool fileChanged;
  bool slotChanged[15];
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
  QString md5sum(QString fileName,QString UserID);
  QString fileblock(QString fileName);
  QString filetimestamp(QString fileName);
  void fix_sum(const QString &fileName);
  int ff7__checksum(void * qw );
  void fix_psv_header(void);
  void fix_psx_header(int s);
  void fix_vmc_header(void);
  quint16 itemDecode( quint16 itemraw );
  quint16 itemEncode( quint16 id, quint8 qty );
};

#endif //FF7Save
