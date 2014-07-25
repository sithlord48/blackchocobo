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
//QtI Includes
#include <QObject>
#include<QColor>
#include <cstdlib>
#include <QFileInfo>
#include <QDateTime>
#include <QVector>
#include <QtXml/QDomDocument>
//FF7tk Includes
#include "FF7Save_Const.h" //All consts placed here
#include "FF7Save_Types.h" //All Custom Types for this class here.
#include "FF7Text.h"

class FF7Save: public QObject{
    Q_OBJECT
public:
  explicit FF7Save();
  //Enums
  enum WORLDVEHICLE {WVEHCILE_BUGGY=0,WVEHCILE_TBRONCO=2,WVEHCILE_HIGHWIND=4};
  enum WORLDCHOCOBO {WCHOCO_WILD,WCHOCO_YELLOW=2,WCHOCO_GREEN=3,WCHOCO_BLUE=4,WCHOCO_BLACK=5,WCHOCO_GOLD=6};
  enum LOVER{LOVE_BARRET,LOVE_TIFA,LOVE_AERIS,LOVE_YUFFIE};
  enum MATERIACAVE{CAVE_MIME,CAVE_HPMP,CAVE_QUADMAGIC,CAVE_KOTR};
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
      ACTION_PAUSE,ACTION_UP,ACTION_RIGHT,ACTION_DOWN,ACTION_LEFT
  };
  enum PSXBUTTONS
  {
      BTN_L2,BTN_R2,BTN_L1,BTN_R1,
      BTN_TRIANGLE,BTN_CIRCLE,BTN_X,BTN_SQUARE,
      BTN_SELECT,BTN_UNKNOWN1,BTN_UNKNOWN2,BTN_START,
      BTN_UP,BTN_RIGHT,BTN_DOWN,BTN_LEFT
  };
  enum PSXBLOCKTYPE {BLOCK_EMPTY= 0xA0, BLOCK_MAIN=0x51,BLOCK_DELETED_MAIN=0xA1,BLOCK_MIDLINK=0x52,BLOCK_DELETED_MIDLINK=0xA2,BLOCK_ENDLINK=0x53,BLOCK_DELETED_ENDLINK=0xA3};
  enum KEYITEMS
  {
      COTTONDRESS,SATINDRESS,SILKDRESS,WIG,DYEDWIG,BLONDEWIG,GLASSTIARA,RUBYTIATA,DIAMONDTIARA,COLOGNE,FLOWERCOLOGNE,SEXYCOLOGNE,MEMBERSCARD,
      LINGERIE,MYSTERYPANTIES,BIKINIBRIEFS,PHARMACYCOUPON,DISINFECTANT,DEODORANT,DIGESTIVE,HUGEMATERIA_CONDOR,HUGEMATERIA_COREL,HUGEMATERIA_UNDERWATER,
      HUGEMATERIA_ROCKET,KEYTOANCIENTS,LETTERTOADAUGHTER,LETTERTOAWIFE,LUNARHARP,BASEMENTKEY,KEYTOSECTOR5,KEYCARD60,KEYCARD62,KEYCARD65,KEYCARD66,
      KEYCARD68,MIDGARPARTS1,MIDGARPARTS2,MIDGARPARTS3,MIDGARPARTS4,MIDGARPARTS5,PHS,GOLDTICKET,KEYSTONE,LEIATHANSCALES,GLACIERMAP,COUPON_A,COUPON_B,
      COUPON_C,BLACKMATERIA,MYTHRIL,SNOWBOARD
  };
  //Functions
  QList<qint8> chocoboPens(int s);
  void setChocoboPen(int s,int pen,qint8 value);
  quint8 condorWins(int s);
  void setCondorWins(int s,quint8 wins);
  quint8 condorLoses(int s);
  void setCondorLoses(int s, quint8 loses);
  quint16 condorFunds(int s);
  void setCondorFunds(int s,quint16 value);
  //Field Location
  quint16 locationId(int s);
  void setLocationId(int s, quint16 locationID);
  quint16 mapId(int s);
  void setMapId(int s, quint16 mapID);
  qint16 locationX(int s);
  void setLocationX(int s, qint16 x);
  qint16 locationY(int s);
  void setLocationY(int s, qint16 y);
  quint16 locationT(int s);
  void setLocationT(int s, quint16 t);
  quint8 locationD (int s);
  void setLocationD(int s,quint8 d);

  quint16 craterSavePointMapID(int s);
  qint16 craterSavePointX(int s);
  qint16 craterSavePointY(int s);
  qint16 craterSavePointZ(int s);
  void setCraterSavePointMapID(int s,int value);
  void setCraterSavePointX(int s,int value);
  void setCraterSavePointY(int s,int value);
  void setCraterSavePointZ(int s,int value);
  //options
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
  int battleMessageSpeed(int s);
  void setBattleMessageSpeed(int s, int speed);
  int messageSpeed(int s);
  void setMessageSpeed(int s, int speed);
  bool fieldHelp(int s);
  void setFieldHelp(int s, bool shown);
  bool battleTargets(int s);
  void setBattleTargets(int s, bool shown);
  //Phs/Menu
  bool phsVisible(int s, int who);
  void setPhsVisible(int s, int who , bool checked);
  quint16 phsVisible(int s);
  void setPhsVisible(int s, quint16 phs_visible);
  bool phsAllowed(int s,int who);
  quint16 phsAllowed(int s);
  void setPhsAllowed(int s, int who , bool checked);
  void setPhsAllowed(int s, quint16 phs_visible);
  bool menuVisible(int s, int index);
  void setMenuVisible(int s, int index , bool checked);
  quint16 menuVisible(int s);
  void setMenuVisible(int s, quint16 menu_visible);
  bool menuLocked(int s, int index);
  void setMenuLocked(int s, int index , bool checked);
  quint16 menuLocked(int s);
  void setMenuLocked(int s, quint16 menu_visible);
  //File Members
  bool loadFile(const QString &fileName);
  bool saveFile(const QString &fileName);
  bool exportFile(const QString &fileName,QString newType="",int s=0);
  bool exportPC(const QString &fileName);
  bool exportPSX(int s,const QString &fileName);
  bool exportVMC(const QString &fileName);
  bool exportDEX(const QString &fileName);
  bool exportVGS(const QString &fileName);
  void importFromFileToSlot(int s=0, QString fileName="",int fileSlot=0);
  void importPSX(int s,const QString &fileName);
  void importPSV(int s,const QString &fileName);
  void clearSlot(int s);
  void copySlot(int s);
  void pasteSlot(int s);
  void newGame(int s,QString fileName=""); //new game in slot s (over load default w/ fileName must be RAW PSX)
  void newGamePlus(int s,QString CharFileName,QString fileName="");//new game + in slot s (over load default w/ fileName must be RAW PSX
  bool exportCharacter(int s,int char_num,QString fileName);// Write slot[s].char[char_num] to fileName
  void importCharacter(int s,int char_num,QByteArray new_char);//import new_char to slot[s].char[char_num]
  typedef QVector< QString > SubContainer;
  QVector< SubContainer >  parseXML(QString fileName,QString metadataPath,QString UserID);
  QVector< SubContainer >  createMetadata(QString fileName, QString UserID);
  bool fixMetaData(QString fileName="",QString OutPath="",QString UserID="");
  QByteArray fileHeader(void);
  bool setFileHeader(QByteArray data);
  QByteArray fileFooter(void);
  bool setFileFooter(QByteArray data);
  QByteArray slotHeader(int s);
  bool setSlotHeader(int s,QByteArray data);
  QByteArray slotFooter(int s);
  bool setSlotFooter(int s,QByteArray data);
  QByteArray slotPsxRawData(int s);
  bool setSlotPsxRawData(int s,QByteArray data);
  //item info
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
  void setMateriaCave(int s, MATERIACAVE cave, bool isEmpty);
  quint8 partyMateriaId(int s,int mat_num);
  qint32 partyMateriaAp(int s,int mat_num);
  quint8 stolenMateriaId(int s,int mat_num);
  qint32 stolenMateriaAp(int s,int mat_num);
  void setPartyMateria(int s,int mat_num,quint8 id,qint32 ap);
  void setStolenMateria(int s, int mat_num,quint8 id,qint32 ap);
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
  QColor dialogColorUL(int s);
  QColor dialogColorUR(int s);
  QColor dialogColorLL(int s);
  QColor dialogColorLR(int s);
  void setDialogColorUL(int s,QColor color);
  void setDialogColorUR(int s,QColor color);
  void setDialogColorLL(int s,QColor color);
  void setDialogColorLR(int s,QColor color);
  // String Functions.
  QString chocoName(int s,int choco_num);//return choco_num's name.
  void setChocoName(int s,int choco_num,QString new_name);//write choco_num 's new_name to slot s
  QString location(int s);// return save location string
  void setLocation(int s, QString new_location);//set save location string to new_location
  quint32 gil(int s);
  void setGil(int s,int gil);
  quint16 gp (int s);
  void setGp(int s,int gp);
  quint16 battles (int s);
  void setBattles(int s,int battles);
  quint16 runs (int s);
  void setRuns(int s,int runs);
  quint8 party(int s,int pos);
  void setParty(int s,int pos, int new_id);
  qint8 chocoboPen(int s, int pos);
  void setChocoboPen(int s, int pos, int type);
  bool seenPandorasBox(int s);
  void setSeenPandorasBox(int s,bool seen);
  //Mini Game Stuff
  quint8 love(int s,bool battle, LOVER who);
  void setLove(int s,bool battle, LOVER who ,quint8 love);
  quint16 speedScore(int s, int rank);
  void setSpeedScore(int s,int rank,quint16 score);
  quint16 bikeHighScore(int s);
  void setBikeHighScore(int s,quint16 score);
  quint32 snowboardTime(int s,int course);
  void setSnowboardTime(int s,int course,quint32 time);
  quint8 snowboardScore(int s,int course);
  void setSnowboardScore(int s,int course,quint8 score);
  quint32 countdownTimer(int s);
  void setCountdownTimer(int s,quint32 time);
  //Char Releated Functions
  FF7CHAR character(int s,int char_num); //Return Full Char
  QByteArray rawCharacterData(int s, int char_num);
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
  void setCharacter(int s,int char_num,FF7CHAR new_char);
  void setCharID(int s,int char_num,qint8 new_id);
  void setCharLevel(int s,int char_num,qint8 new_level);
  void setCharStr(int s,int char_num,quint8 str);
  void setCharVit(int s,int char_num,quint8 vit);
  void setCharMag(int s,int char_num,quint8 mag);
  void setCharSpi(int s,int char_num,quint8 spi);
  void setCharDex(int s,int char_num,quint8 dex);
  void setCharLck(int s,int char_num,quint8 lck);
  void setCharStrBonus(int s,int char_num,quint8 strbonus);
  void setCharVitBonus(int s,int char_num,quint8 vitbonus);
  void setCharMagBonus(int s,int char_num,quint8 magbonus);
  void setCharSpiBonus(int s,int char_num,quint8 spibonus);
  void setCharDexBonus(int s,int char_num,quint8 dexbonus);
  void setCharLckBonus(int s,int char_num,quint8 lckbonus);
  void setCharLimitLevel(int s,int char_num,qint8 limitlevel);
  void setCharLimitBar(int s,int char_num,quint8 limitbar);
  void setCharName(int s,int char_num,QString new_name);//write char_num 's new_name to slot s
  void setCharWeapon(int s,int char_num,quint8 weapon);
  void setCharArmor(int s,int char_num,quint8 armor);
  void setCharAccessory(int s,int char_num,quint8 accessory);
  void setCharFlag(int s,int char_num,int flag_num,quint8 flag_value);
  void setCharLimits(int s,int char_num,quint16 new_limits);
  void setCharKills(int s,int char_num,quint16 kills);
  void setCharTimeLimitUsed(int s,int char_num,int level,quint16 timesused);
  void setCharCurrentHp(int s,int char_num,quint16 curHp);
  void setCharBaseHp(int s,int char_num,quint16 baseHp);
  void setCharCurrentMp(int s,int char_num,quint16 curMp);
  void setCharBaseMp(int s,int char_num,quint16 baseMp);
  void setCharUnknown(int s,int char_num,int unknown_num,quint8 value);
  void setCharMaxHp(int s,int char_num,quint16 maxHp);
  void setCharMaxMp(int s,int char_num,quint16 maxMp);
  void setCharCurrentExp(int s,int char_num,quint32 exp);
  void setCharNextExp(int s,int char_num,quint32 next);
  void setCharMateria(int s,int who,int mat_num,quint8 id,qint32 ap);
  void setCharMateria(int s,int who,int mat_num,materia mat);
  //chocobo Stuff.
  QList<FF7CHOCOBO> chocobos(int s);
  QList<quint16> chocobosStaminas(int s);
  QList<QString> chocobosNames(int s);
  QList<bool> chocoboCantMates(int s);
  qint8 stablesOwned(int s);
  qint8 stablesOccupied(int s);
  qint8 stableMask(int s);
  void setStablesOwned(int s,qint8 value);
  void setStablesOccupied(int s,qint8 value);
  void setStableMask(int s,qint8 value);
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
  int lenFile(void);//Return File length.
  int lenFileHeader(void);//Return File Header length
  int lenFileFooter(void);//Return File Footer length
  int lenCoreSave(void);//Return Slot length (data portion)
  int lenSlotHeader(void);//Return slot header length
  int lenSlotFooter(void);//Return slot footer length
  int lenSlot(void);//Return Slot length
  int numberOfSlots(void);//Return number of slots in the file_footer_dex
  QString fileName(void);//return loaded filename
  QString type(void);// Returns the file type loaded.
  void setFileModified(bool,int s);//file changed toggle, with slot called
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
  //more data members
  QByteArray unknown(int s,int z);
  bool setUnknown(int s,int z,QByteArray data);
  quint16 steps(int s);
  void setSteps(int s,int steps);
  quint8 chruchProgress(int s);
  void setChurchProgress(int s,int progress);
  quint8 donProgress(int s);
  void setDonProgress(int s,int progress);
  quint16 battlePoints(int s);
  void setBattlePoints(int s,quint16);
  quint32 time(int s);
  void setTime(int s,quint32 new_time);
  void setDisc(int s,int disc);
  quint8 disc(int s);
  quint16 mainProgress(int s);
  void setMainProgress(int s,int mProgress);
  QByteArray keyItems(int s);
  bool setKeyItems(int s,QByteArray data);
  bool keyItem(int s, int keyItem);
  void setKeyItem(int s, int keyItem,bool pickedUp);
  bool itemMask1(int s, int bit);
  void setItemMask1(int s, int bit, bool pickedUp);
  bool bmProgress1(int s, int bit);
  void setBmProgress1(int s, int bit, bool isTrue);
  void setBmProgress1(int s, int value);
  bool bmProgress2(int s, int bit);
  void setBmProgress2(int s, int bit, bool isTrue);
  void setBmProgress2(int s, int value);
  bool bmProgress3(int s, int bit);
  void setBmProgress3(int s, int bit, bool isTrue);
  void setBmProgress3(int s, int value);
  bool midgarTrainFlags(int s, int bit);
  void setMidgarTrainFlags(int s, int bit, bool isTrue);
  void setMidgarTrainFlags(int s, int value);
  bool turtleParadiseFlyerSeen(int s, int flyer);
  quint8 turtleParadiseFlyersSeen(int s);
  void setTurtleParadiseFlyerSeen(int s, int flyer,bool seen);
  void setTurtleParadiseFlyersSeen(int s,quint8 flyersSeen);
  bool startBombingMission(int s);
  void setStartBombingMission(int s,bool isTrue);
  quint32 uWeaponHp(int s);
  void setUWeaponHp(int s,int hp);
  bool killedEmeraldWeapon(int s);
  void setKilledEmeraldWeapon(int s,bool isTrue);
  bool killedRubyWeapon(int s);
  void setKilledRubyWeapon(int s,bool isTrue);
  quint8 tutSave(int s);
  void setTutSave(int s, int value);
  bool canFightNinjaInForest(int s);
  void setCanFightNinjaInForest(int s,bool isTrue);
  quint8 tutSub(int s);
  bool tutSub(int s, int bit);
  void setTutSub(int s, int bit, bool isTrue);
  void setTutSub(int s, int value);
  bool yuffieAquired(int s);
  quint8 regYuffie(int s);
  void setYuffieAquired(int s,bool isTrue);
  void setRegYuffie(int s , int value);
  bool vincentAquired(int s);
  quint8 regVincent(int s);
  void setVincentAquired(int s,bool isTrue);
  void setRegVincent(int s , int value);
  bool worldChocobo(int s, int bit);
  void setWorldChocobo(int s, int bit, bool isTrue);
  bool worldVehicle(int s, int bit);
  void setWorldVehicle(int s, int bit, bool isTrue);
  //World Coords
  quint32 worldCoordsLeader(int s, bool firstChunk);
  int worldCoordsLeaderX(int s);
  int worldCoordsLeaderID(int s);
  int worldCoordsLeaderAngle(int s);
  int worldCoordsLeaderY(int s);
  int worldCoordsLeaderZ(int s);
  void setWorldCoordsLeader(int s,bool firstChunk,int value);
  void setWorldCoordsLeaderX(int s,int value);
  void setWorldCoordsLeaderID(int s,int value);
  void setWorldCoordsLeaderAngle(int s,int value);
  void setWorldCoordsLeaderY(int s,int value);
  void setWorldCoordsLeaderZ(int s,int value);
  quint32 worldCoordsTc(int s, bool firstChunk);
  int worldCoordsTcX(int s);
  int worldCoordsTcID(int s);
  int worldCoordsTcAngle(int s);
  int worldCoordsTcY(int s);
  int worldCoordsTcZ(int s);
  void setWorldCoordsTc(int s,bool firstChunk,int value);
  void setWorldCoordsTcX(int s,int value);
  void setWorldCoordsTcID(int s,int value);
  void setWorldCoordsTcAngle(int s,int value);
  void setWorldCoordsTcY(int s,int value);
  void setWorldCoordsTcZ(int s,int value);
  quint32 worldCoordsBh(int s, bool firstChunk);
  int worldCoordsBhX(int s);
  int worldCoordsBhID(int s);
  int worldCoordsBhAngle(int s);
  int worldCoordsBhY(int s);
  int worldCoordsBhZ(int s);
  void setWorldCoordsBh(int s,bool firstChunk,int value);
  void setWorldCoordsBhX(int s,int value);
  void setWorldCoordsBhID(int s,int value);
  void setWorldCoordsBhAngle(int s,int value);
  void setWorldCoordsBhY(int s,int value);
  void setWorldCoordsBhZ(int s,int value);
  quint32 worldCoordsSub(int s, bool firstChunk);
  int worldCoordsSubX(int s);
  int worldCoordsSubID(int s);
  int worldCoordsSubAngle(int s);
  int worldCoordsSubY(int s);
  int worldCoordsSubZ(int s);
  void setWorldCoordsSub(int s,bool firstChunk,int value);
  void setWorldCoordsSubX(int s,int value);
  void setWorldCoordsSubID(int s,int value);
  void setWorldCoordsSubAngle(int s,int value);
  void setWorldCoordsSubY(int s,int value);
  void setWorldCoordsSubZ(int s,int value);
  quint32 worldCoordsWchoco(int s, bool firstChunk);
  int worldCoordsWchocoX(int s);
  int worldCoordsWchocoID(int s);
  int worldCoordsWchocoAngle(int s);
  int worldCoordsWchocoY(int s);
  int worldCoordsWchocoZ(int s);
  void setWorldCoordsWchoco(int s,bool firstChunk,int value);
  void setWorldCoordsWchocoX(int s,int value);
  void setWorldCoordsWchocoID(int s,int value);
  void setWorldCoordsWchocoAngle(int s,int value);
  void setWorldCoordsWchocoY(int s,int value);
  void setWorldCoordsWchocoZ(int s,int value);
  quint32 worldCoordsDurw(int s, bool firstChunk);
  int worldCoordsDurwX(int s);
  int worldCoordsDurwID(int s);
  int worldCoordsDurwAngle(int s);
  int worldCoordsDurwY(int s);
  int worldCoordsDurwZ(int s);
  void setWorldCoordsDurw(int s,bool firstChunk,int value);
  void setWorldCoordsDurwX(int s,int value);
  void setWorldCoordsDurwID(int s,int value);
  void setWorldCoordsDurwAngle(int s,int value);
  void setWorldCoordsDurwY(int s,int value);
  void setWorldCoordsDurwZ(int s,int value);
  void setSaveNumber(int s,int saveNum);
signals:
  void fileChanged(bool);
private:
  //methods
  void vmcRegionEval(int s);
  //data members
  FF7SLOT slot[15]; //core slot data.
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
  bool fileHasChanged;
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
  void checksumSlots();
  quint16 ff7Checksum(int s);
  void fix_psv_header(void);
  void fix_psx_header(int s);
  void fix_vmc_header(void);
  quint16 itemDecode( quint16 itemraw );
  quint16 itemEncode( quint16 id, quint8 qty );
};
#endif //FF7Save
