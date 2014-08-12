/****************************************************************************/
//    copyright 2012 -2014  Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//   FF7tk is distributed in the hope that it will be useful,               //
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
/** \class FF7Save
 *	\todo add support for signing psv files.
 *	\todo add support for signing vmp files.
 *	\brief edit saves from Final Fantasy 7
 *
 *	FF7Save does it all for you open the file , edit then save. All of the file handling will be taken care of for you.
 *	the following are supported formats:
 *	|Flie	| Description |
 *	|-------|-------------|
 *	|*.ff7	|PC Format Save if with a metadata.xml file will attempt to sign it|
 *	|*.mcr	|Common Emulator format (Virtual Memory Card)|
 *	|*.mcd	|Common Emulator format (Virtual Memory Card)|
 *	|*.mci	|Common Emulator format (Virtual Memory Card)|
 *	|*.mc	|Common Emulator format (Virtual Memory Card)|
 *	|*.ddf	|Common Emulator format (Virtual Memory Card)|
 *	|*.ps	|Common Emulator format (Virtual Memory Card)|
 *	|*.psm	|Common Emulator format (Virtual Memory Card)|
 *	|*.bin	|Common Emulator format (Virtual Memory Card)|
 *	|*.vgs	|Memory Card from Virtual Game Station|
 *	|*.mem	|Memory Card from Virtual Game Station|
 *	|*.gme	|Dex drive format virtual memory card|
 *	|*.VM1	|Internal PSX Memory Card on PS3 (Virtual Memory Card)|
 *	|*.vmp	| VMC format used by the PSP/PsVita. Can not sign this type yet;reimport to console will fail|
 *	|*.psv	| Saves "Exported" by a PS3. can not sign this type yet;reimport to console will fail|
 *	|*FF7-S*| A Raw PSX memory card "file" extracted from a real or virtual memory card|
 */
class FF7Save: public QObject{
	Q_OBJECT
	public:
	//Enums
	enum WORLDVEHICLE {WVEHCILE_BUGGY=0/**< 0*/,WVEHCILE_TBRONCO/**< 2*/=2,WVEHCILE_HIGHWIND=4/**< 4*/};
	enum WORLDCHOCOBO {WCHOCO_WILD/**< 0*/,WCHOCO_YELLOW=2/**< 2*/,WCHOCO_GREEN=3/**< 3*/,WCHOCO_BLUE=4/**< 4*/,WCHOCO_BLACK=5/**< 5*/,WCHOCO_GOLD=6/**< 6*/};
	enum LOVER{LOVE_BARRET/**< 0*/,LOVE_TIFA/**< 1*/,LOVE_AERIS/**< 2*/,LOVE_YUFFIE/**< 3*/};
	enum MATERIACAVE{CAVE_MIME/**< 0*/,CAVE_HPMP/**< 1*/,CAVE_QUADMAGIC/**< 2*/,CAVE_KOTR/**< 3*/};
	enum SOUNDMODE{SOUND_MONO/**< 0*/,SOUND_STEREO/**< 1*/};
	enum CONTROLMODE {CONTROL_NORMAL/**< 0*/,CONTROL_CUSTOM/**< 1*/};
	enum CURSORMODE{CURSOR_INITIAL/**< 0*/, CURSOR_MEMORY/**< 1*/};
	enum ATBMODE{ATB_ACTIVE/**< 0*/,ATB_RECOMMENED,ATB_WAIT/**< 1*/};
	enum CAMERAMODE {CAMERA_AUTO/**< 0*/,CAMERA_FIXED/**< 1*/};
	enum MAGICORDER {MAGIC_RAI/**< 0*/,MAGIC_RIA/**< 1*/,MAGIC_AIR/**< 2*/,MAGIC_ARI/**< 3*/,MAGIC_IRA/**< 4*/,MAGIC_IAR/**< 5*/};
	/** \enum MENUITEMS
	 *	\brief Menu items for ff7.
	 */
	enum MENUITEMS {MENUITEM/**< 0*/,MENUMAGIC/**< 1*/,MENUMATERIA/**< 2*/,MENUEQUIPMENT/**< 3*/,MENUSTATUS/**< 4*/,MENUFORM/**< 5*/,MENULIMIT/**< 6*/,MENUCONFIG/**< 7*/,MENUPHS/**< 8*/,MENUSAVE/**< 9*/};
	/** \enum CONTROLACTION
	 *	\brief Possible Actions the user can input
	 */
	enum CONTROLACTION
	{
		ACTION_CAMERA/**< 0*/,ACTION_TARGET/**< 1*/,ACTION_PAGEUP/**< 2*/,ACTION_PAGEDOWN/**< 3*/,
		ACTION_MENU/**< 4*/,ACTION_OK/**< 5*/,ACTION_CANCEL/**< 6*/,ACTION_SWITCH/**< 7*/,
		ACTION_HELP/**< 8*/,ACTION_UNKNOWN1/**< 9*/,ACTION_UNKNOWN2/**< 10*/,
		ACTION_PAUSE/**< 11*/,ACTION_UP/**< 12*/,ACTION_RIGHT/**< 13*/,ACTION_DOWN/**< 14*/,ACTION_LEFT/**< 15*/
	};

	/** \enum PSXBUTTON
	 *	\brief Final Fantasy 7 Buttons for when on PSX
	 */
	enum PSXBUTTON
	{
		BTN_L2/**< 0*/,BTN_R2/**< 1*/,BTN_L1/**< 2*/,BTN_R1/**< 3*/,
		BTN_TRIANGLE/**< 4*/,BTN_CIRCLE/**< 5*/,BTN_X/**< 6*/,BTN_SQUARE/**< 7*/,
		BTN_SELECT/**< 8*/,BTN_UNKNOWN1/**< 9*/,BTN_UNKNOWN2/**< 10*/,BTN_START/**< 11*/,
		BTN_UP/**< 12*/,BTN_RIGHT/**< 13*/,BTN_DOWN/**< 14*/,BTN_LEFT/**< 15*/
	};
	/** \enum PSXBLOCKTYPE
	 *	\brief Used to set the type of block on a PSX memory card (image) when creating the index.
	 */
	enum PSXBLOCKTYPE {BLOCK_EMPTY= 0xA0, /**< 0xA0*/ BLOCK_MAIN=0x51, /**< 0x51*/ BLOCK_DELETED_MAIN=0xA1, /**< 0xA1*/ BLOCK_MIDLINK=0x52, /**< 0x52*/ BLOCK_DELETED_MIDLINK=0xA2, /**< 0xA2*/ BLOCK_ENDLINK=0x53, /**< 0x53*/ BLOCK_DELETED_ENDLINK=0xA3, /**< 0xA3*/};
	/*! \enum KEYITEMS
	 *	\brief ID's for each keyitem
	 */
	enum KEYITEMS
	{
		COTTONDRESS/**< 0*/,SATINDRESS/**< 1*/,SILKDRESS/**< 2*/,WIG/**< 3*/,DYEDWIG/**< 4*/,BLONDEWIG/**< 5*/,GLASSTIARA/**< 6*/,RUBYTIATA/**< 7*/,DIAMONDTIARA/**< 8*/,COLOGNE/**< 9*/,FLOWERCOLOGNE/**< 10*/,SEXYCOLOGNE/**< 11*/,MEMBERSCARD/**< 12*/,
		LINGERIE/**< 13*/,MYSTERYPANTIES/**< 14*/,BIKINIBRIEFS/**< 15*/,PHARMACYCOUPON/**< 16*/,DISINFECTANT/**< 17*/,DEODORANT/**< 18*/,DIGESTIVE/**< 19*/,HUGEMATERIA_CONDOR/**< 20*/,HUGEMATERIA_COREL/**< 21*/,HUGEMATERIA_UNDERWATER/**< 22*/,
		HUGEMATERIA_ROCKET/**< 23*/,KEYTOANCIENTS/**< 24*/,LETTERTOADAUGHTER/**< 25*/,LETTERTOAWIFE/**< 26*/,LUNARHARP/**< 27*/,BASEMENTKEY/**< 28*/,KEYTOSECTOR5/**< 29*/,KEYCARD60/**< 30*/,KEYCARD62/**< 31*/,KEYCARD65/**< 32*/,KEYCARD66/**< 33*/,
		KEYCARD68/**< 34*/,MIDGARPARTS1/**< 35*/,MIDGARPARTS2/**< 36*/,MIDGARPARTS3/**< 37*/,MIDGARPARTS4/**< 38*/,MIDGARPARTS5/**< 39*/,PHS/**< 40*/,GOLDTICKET/**< 41*/,KEYSTONE/**< 42*/,LEIATHANSCALES/**< 43*/,GLACIERMAP/**< 44*/,COUPON_A/**< 45*/,COUPON_B/**< 46*/,
		COUPON_C/**< 47*/,BLACKMATERIA/**< 48*/,MYTHRIL/**< 49*/,SNOWBOARD/**< 50*/
	};
	//Functions
	explicit FF7Save(); /**< \brief create a new FF7Save object */
	//File Members
	/**	\brief attempt to load fileName as ff7save
	 *	\param fileName file that will be loaded
	 *	\return True if Successful
	*/
	bool loadFile(const QString &fileName);

	/**	\brief attempt to save fileName as ff7save
	 *	\param fileName file that will be saved
	 *	\return True if Successful
	*/
	bool saveFile(const QString &fileName);

	 /** \brief attempt to export a file as ff7save. A convenance function to call the proper export function
	 *	\param fileName file that will be saved
	 *	\param newType Type of file to be saved	 "PC","PSX","MC","VGS","DEX" are valid
	 *	\param s Slot to export if exporting to a multi slot save type
	 *	\return True if Successful
	 *	\sa exportPC(),exportPSX(),exportVMC(),exportDEX(),exportVGS()
	*/
	bool exportFile(const QString &fileName,QString newType="",int s=0);

	/**	\brief attempt to save fileName as a PC ff7save
	 *	\param fileName file that will be saved
	 *	\return True if Successful
	*/
	bool exportPC(const QString &fileName);

	/**	\brief attempt to save fileName as a PC ff7save
	 *	\param s slot in loaded file to export as psx
	*	\param fileName file that will be saved
	 *	\return True if Successful
	*/
	bool exportPSX(int s,const QString &fileName);

	/**	\brief attempt to save fileName as a Virtual Memory Card (slots without a region string will not be exported)
	 *	\param fileName file that will be saved
	 *	\return True if Successful
	*/
	bool exportVMC(const QString &fileName);

	/**	\brief attempt to save fileName as a DEX Drive format memory card file
	 *	\param fileName file that will be saved
	 *	\return True if Successful
	*/
	bool exportDEX(const QString &fileName);

	/**	\brief attempt to save fileName as a Virtual Game Station format memory card file
	 *	\param fileName file that will be saved
	 *	\return True if Successful
	*/
	bool exportVGS(const QString &fileName);

	/**	\brief import from a file into a slot
	 *
	 *	 Will import a slot from a file(fileName) into slot (s). when importing from a multi slot save type slot # (fileSlot) in the file will be imported.
	 *	\param s slot to import into
	 *	\param fileName file that will be imported
	 *	\param fileSlot slot to import from fileName
	*/
	void importSlot(int s=0, QString fileName="",int fileSlot=0);

	/** \brief clear a slot
	 * \param s slot number (0-14)
	 */
	void clearSlot(int s);

	/** \brief copy a slot Sin to the buffer
	 * \param s slot number (0-14)
	 */
	void copySlot(int s);

	/** \brief paste from the buffer into a slot
	 * \param s slot number (0-14)
	 */
	void pasteSlot(int s);

	/** \brief creates a new game in a slot
	 * \param s slot number (0-14)
	 * \param fileName Raw PSX file to use instead of defalut data
	 */
	void newGame(int s,QString fileName=""); //new game in slot s (over load default w/ fileName must be RAW PSX)

	/** \brief creates a new game + in a slot
	 *
	 * When creating a new game+ two char files will be exported. one for cait sith and another for vincent. those characters have to be reset to correctly set a new game. You can reimport the char files when you aquire the character in your new game +
	 * \param s slot number (0-14)
	 * \param CharFileName base filename to use for saving char files vincent and
	 * \param fileName Raw PSX file to use instead of defalut data
	 */
	void newGamePlus(int s,QString CharFileName,QString fileName="");//new game + in slot s (over load default w/ fileName must be RAW PSX

	/** \brief export a character
	 * \param s slot number (0-14)
	 * \param char_num character slot (0-8)
	 * \param fileName file to write
	 * \return true is successful
	 */
	bool exportCharacter(int s,int char_num,QString fileName);// Write slot[s].char[char_num] to fileName

	/** \brief export a character
	 * \param s slot number (0-14)
	 * \param char_num character slot (0-8)
	 * \param new_char raw bytes for a character in ff7
	 * \return true is successful
	 */
	void importCharacter(int s,int char_num,QByteArray new_char);//import new_char to slot[s].char[char_num]

	typedef QVector< QString > SubContainer; /** <\typedef QVector<QString> SubContainer \brief used to hold more xml style string in metadata signing*/

	/** \brief parse the metadata for 2012 / 2013 release
	 *	\param fileName name of the file to output
	 *	\param OutPath to metadata
	 *	\param UserID squaresoft id number to when signing
	 *	\return True is Successful
	*/
	bool fixMetaData(QString fileName="",QString OutPath="",QString UserID="");

	QByteArray fileHeader(void);/**< \brief file Header as QByteArray*/

	/** \brief set the file header
	 *	\param data: replace exsisting data with these bytes
	 *	\return True is Successful
	*/
	bool setFileHeader(QByteArray data);

	QByteArray fileFooter(void);/**< \brief file Footer as QByteArray*/

	/** \brief set the file footer
	 *	\param data: replace exsisting data with these bytes
	 *	\return True is Successful
	*/
	bool setFileFooter(QByteArray data);

	QByteArray slotHeader(int s); /**< \brief Header for a slot as QByteArray \param s slot number (0-14)*/

	/** \brief set the slot header
	 *	\param s slot number (0-14)
	 *	\param data: replace exsisting data with these bytes
	 *	\return True is Successful
	*/
	bool setSlotHeader(int s,QByteArray data);

	QByteArray slotFooter(int s);/**< \brief Footer for a slot as QByteArray \param s slot number (0-14)*/

	/** \brief set the slot footer
	 *	\param s slot number (0-14)
	 *	\param data: replace exsisting data with these bytes
	 *	\return True is Successful
	*/
	bool setSlotFooter(int s,QByteArray data);

	QByteArray slotPsxRawData(int s);/**< \brief QByteArray of a psx save (multiblock saves are ok)\param s slot number (0-14); if a multi block set s should be the first block used*/

	/** \brief set the slots raw psx data
	 *
	 *	Most Useful when connected to a hexEditor, This function will set the slot(s) raw data as if writing to a psx card directly. even if more then one slot and correctly update the save index based on whats in the data.
	 *	\param s slot number (0-14)
	 *	\param data: replace exsisting data with these bytes
	 *	\return True is Successful
	*/
	bool setSlotPsxRawData(int s,QByteArray data);

	QByteArray slotFF7Data(int s); /**< \brief Return Raw data from the slot \param s slot number (0-14)*/

	/** \brief
	 *	\param s slot number (0-14)
	 *	\param data: replace exsisting data with these bytes
	 *	\overload setSlotFF7Data(int,FF7SLOT)
	 */
	bool setSlotFF7Data(int s, QByteArray data);
	bool setSlotFF7Data(int s, FF7SLOT data);

	QList<QByteArray> slotIcon(int s); /**< \brief return slots save icon. each new frame will be appended to the list.*/

	/** \brief return the chocobos in the pen outside of the chocobo farm
	 *	\param s slot number (0-14)
	 *	\return list of chocobo in then pen.
	*/
	QList<qint8> chocoboPens(int s);

	/** \brief return the chocobos in the pen outside of the chocobo farm
	 *	\param s slot number (0-14)
	 *	\param pen the slot in the pen to assign to (0-3)
	 *	\param value rating of the chocobo (0:Empty 1:Wonderful 2:Great 3:Good 4:Fair 5:Average 6:Poor 7:Bad 8:Terrible)
	*/
	void setChocoboPen(int s,int pen,qint8 value);

	/** \brief wins in fort condor mini game
	 *	\param s slot number (0-14)
	 *	\return number of wins at fort condor
	*/
	quint8 condorWins(int s);

	/** \brief set how many time you have won the fort condor mini game
	 *	\param s slot number (0-14)
	 *	\param wins number of wins in the fort condor mini game
	 *	\return number of wins at fort condor
	*/
	void setCondorWins(int s,quint8 wins);

	/** \brief losses in fort condor mini game
	 *	\param s slot number (0-14)
	 *	\return number of losses at fort condor
	*/
	quint8 condorLosses(int s);

	/** \brief set how many time you have lost the fort condor mini game
	 *	\param s slot number (0-14)
	 *	\param losses number of losses in the fort condor mini game
	*/
	void setCondorLosses(int s, quint8 losses);

	/** \return amount of gil you have donated to fort condor
	 *	\param s slot number (0-14)
	*/
	quint16 condorFunds(int s);

	/** \brief set how gil you have donated to  fort condor
	 *	\param s slot number (0-14)
	 *	\param value amount of gil donated
	*/
	void setCondorFunds(int s,quint16 value);
	//Field Location

	/**	\brief Id of the location save is located on
	 *	\param s slot number (0-14)
	 *	\return location id
	 */
	quint16 locationId(int s);

	/**	\brief set location id save is located on
	 *	\param s slot number (0-14)
	 *	\param locationID new locationID
	 */
	void setLocationId(int s, quint16 locationID);

	/** \brief map id save is on
	 * \param s slot number (0-14)
	 * \return map id
	*/
	quint16 mapId(int s);

	/**	\brief set map id save is located on
	 *	\param s slot number (0-14)
	 *	\param mapID new mapID
	 */
	void setMapId(int s, quint16 mapID);

	/** \brief x coordinate on field map
	 * \param s slot number (0-14)
	 * \return x coordinate
	*/
	qint16 locationX(int s);

	/** \brief set x coordinate on field map
	 * \param s slot number (0-14)
	 * \param x new x coordinate
	*/
	void setLocationX(int s, qint16 x);

	/** \brief y coordinate on field map
	 * \param s slot number (0-14)
	 * \return y coordinate
	*/
	qint16 locationY(int s);

	/** \brief set y coordinate on field map
	 * \param s slot number (0-14)
	 * \param y new y coordinate
	*/
	void setLocationY(int s, qint16 y);

	/** \brief triangle play is standing on. field map
	 * \param s slot number (0-14)
	 * \return triangle
	*/
	quint16 locationT(int s);

	/** \brief set t coordinate on field map
	 * \param s slot number (0-14)
	 * \param t new t coordinate
	*/
	void setLocationT(int s, quint16 t);

	/** \brief direction player is facing on field map
	 * \param s slot number (0-14)
	 * \return direction
	*/
	quint8 locationD (int s);

	/** \brief set direction player is facing on field map
	 * \param s slot number (0-14)
	 * \param d new direction
	*/
	void setLocationD(int s,quint8 d);

	/** \brief map the placeable save point is on
	 *	\param s slot number (0-14)
	 *	\return mapID of map containing the save point
	 */
	quint16 craterSavePointMapID(int s);

	/** \brief x coordinate of the placeable save point
	 *	\param s slot number (0-14)
	 *	\return x coordinate of the placeable save point
	*/
	qint16 craterSavePointX(int s);

	/** \brief y coordinate of the placeable save point
	 *	\param s slot number (0-14)
	 *	\return y coordinate of the placeable save point
	*/
	qint16 craterSavePointY(int s);

	/** \brief z coordinate of the placeable save point
	 *	\param s slot number (0-14)
	 *	\return z coordinate of the placeable save point
	*/
	qint16 craterSavePointZ(int s);

	/** \brief set the map that the placeable save point is on
	 *	\param s slot number (0-14)
	 *	\param value new mapID
	 */
	void setCraterSavePointMapID(int s,int value);

	/** \brief set x coordinate of the placeable save point
	 *	\param s slot number (0-14)
	 *	\param value new x coordinate
	*/
	void setCraterSavePointX(int s,int value);

	/** \brief set y coordinate of the placeable save point
	 *	\param s slot number (0-14)
	 *	\param value new y coordinate
	*/
	void setCraterSavePointY(int s,int value);

	/** \brief set z coordinate of the placeable save point
	 *	\param s slot number (0-14)
	 *	\param value new z coordinate
	*/
	void setCraterSavePointZ(int s,int value);

	//options
	/** \brief get controller mapping for a slot
	 *
	 *  The controller mapping while stored in the pc save is not used? and shouln't be edited
	 *	\param s slot number (0-14)
	 *	\return Mapping as raw bytes
	 */
	QByteArray controllerMapping(int s);

	/** \brief set the controller mapping for a slot
	 *
	 *  The controller mapping while stored in the pc save is not used? and shouln't be edited
	 *	\param s slot number (0-14)
	 *	\param map Mapping as raw bytes
	 */
	void setControllerMapping(int s,QByteArray map);

	/** \brief get button bound to an action for a slot
	 *
	 *  The controller mapping while stored in the pc save is not used? and shouln't be edited
	 *	\param s slot number (0-14)
	 *	\param action game action ( FF7Save::CONTROLACTION )
	 *	\return  FF7Save::PSXBUTTON that an action is mapped to
	 */
	quint8 controllerMapping(int s, int action);

	/** \brief bind a button to an action for a slot.
	 *
	 *  The controller mapping while stored in the pc save is not used? and shouln't be edited
	 *	\param s slot number (0-14)
	 *	\param action valid game action ( FF7Save::CONTROLACTION )
	 *	\param button a valid button ( FF7Save::PSXBUTTON )
	 */
	void setControllerMapping(int s, int action,int button);

	/** \brief In game options for a slot
	 *	\param s slot number (0-14)
	 *	\return game options in raw format
	 */
	quint16 options(int s);

	/** \brief Set in game options for a slot
	 *	\param s slot number (0-14)
	 *	\param opt game options in raw format
	 */
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
	int battleSpeed(int s);
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
	bool materiaCave(int s,MATERIACAVE cave);
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
	qint8 charLimitLevel(int s,int char_num);
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
	void setRegion(int s ,QString region);
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

	quint8 psx_block_type(int s);//mask of psx slot (used by index)
	void setPsx_block_type(int s,FF7Save::PSXBLOCKTYPE block_type);
	quint8 psx_block_next(int s);// if using more then one block return location of next block
	void setPsx_block_next(int s,int next);
	quint8 psx_block_size(int s);//how many blocks save uses.
	void setPsx_block_size(int s,int blockSize);
	void fix_pc_bytemask(int s);// update so last slot is shown selected on load (must be public to set to currently viewed slot).
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
	void fileChanged(bool);/**< \brief emits when internal data changes */
private:
	//methods
	//data members
	FF7SLOT slot[15]; //core slot data.
	FF7HEADFOOT hf[15]; //slot header and footer.
	quint8 * file_headerp;	//pointer to file header
	quint8 * file_footerp;							//pointer to file footer
	quint8 file_header_pc [0x0009];		// [0x0000] 0x06277371 this replace quint8 file_tag[9];
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
	void vmcRegionEval(int s);
	QVector< SubContainer > parseXML(QString fileName,QString metadataPath,QString UserID);
	QVector< SubContainer > createMetadata(QString fileName, QString UserID);
};
#endif //FF7Save
