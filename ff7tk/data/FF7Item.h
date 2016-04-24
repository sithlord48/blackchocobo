/****************************************************************************/
//    copyright 2012 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
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

#ifndef FF7ITEM_H
	#define FF7ITEM_H
#include <QObject>
#include <QIcon>

/*! \struct ITEM
 *  \brief datatype  for one item "kernel" style
 */
struct ITEM {
		QString name;/**< name of item */
		QString desc;/**< description of item */
		qint8 type; /**< item type 0-unknown 1-item 2-armor 3-accessory 4-cloudWeapon 5-barretWeapon 6-tifaWeapon 7-redWeapon 8-aerithWeapon 9-cidWeapon 10-yuffieWeapon 11-caitWeapon 12-vincentWeapon */
		QString imageString; /**< image locations for item */
		qint8 mgrowth; /**< multiplier for ap */
		qint8 mslots; /**< number of materia slots in item */
		qint8 linked; /**< number of materia links in item */
		qint8 hp; /**< hp changes when item is equipped */
		qint8 mp; /**< mp changes when item is equipped */
		qint8 str; /**< str changes when item is equipped */
		qint8 vit; /**< vit changes when item is equipped */
		qint8 dex; /**< dex changes when item is equipped */
		qint8 lck; /**< luck changes when item is equipped */
		qint8 mag; /**< magic changes when item is equipped */
		qint8 spi; /**< spirt changes when item is equipped */

		/* all Elements in FF7
		   -3: Absorb
		   -2: Nullify
		   -1: Halve
			0: No Effect
		   +1: Damage
		*/
		qint8 e_restoration; /**< restoration elemental effect type */
		qint8 e_fire; /**< fire elemental effect type */
		qint8 e_cold; /**< cold elemental effect type */
		qint8 e_lightning; /**< lightning elemental effect type */
		qint8 e_earth; /**< earth elemental effect type */
		qint8 e_wind; /**< wind elemental effect type */
		qint8 e_water; /**< water elemental effect type */
		qint8 e_gravity; /**< gravity elemental effect type */
		qint8 e_holy; /**< holy elemental effect type */
		qint8 e_poison; /**< poison elemental effect type */
		qint8 e_cut; /**< cut elemental effect type */
		qint8 e_shoot; /**< shoot elemental effect type */
		qint8 e_punch; /**< punch elemental effect type */
		qint8 e_hit; /**< hit elemental effect type */

		/* all Status Effects in FF7
		   -2: Protect
		   -1: Remove
			0: No Effect
		   +1: Infilict
		   +2: Auto SelfCast
		*/
		qint8 s_death; /**< Death status effect type */
		qint8 s_slow_numb; /**< Slow numb status effect type */
		qint8 s_d_sentence;/**< Death sentence status effect type */
		qint8 s_paralysis;/**< Paralysis status effect type */
		qint8 s_petrify;/**< Petrify status effect type */
		qint8 s_silence;/**< Silence status effect type */
		qint8 s_sleep;/**< Sleep status effect type */
		qint8 s_confusion;/**< Confusion status effect type */
		qint8 s_berserk;/**< Berserk status effect type */
		qint8 s_frog;/**< Frog status effect type */
		qint8 s_mini;/**< Mini status effect type */
		qint8 s_poison;/**< Poison status effect type */
		qint8 s_fury;/**< Fury status effect type */
		qint8 s_sadness;/**< Sadness status effect type */
		qint8 s_darkness;/**< Darkness status effect type */
		qint8 s_haste;/**< Haste status effect type */
		qint8 s_slow;/**< Slow status effect type */
		qint8 s_stop;/**< Stop status effect type */
		qint8 s_barrier;/**< Barrier status effect type */
		qint8 s_m_barrier;/**< Magic Barrier status effect type */
		qint8 s_reflect;/**< Reflect status effect type */
		qint8 s_sheild;/**< Sheild status effect type */
		qint8 s_regen;/**< Regen status effect type */
		qint8 s_resist;/**< Resist status effect type */
};
/*! \class FF7Item
 * \brief Class containg all kinds of info about items in FF7
 */
class FF7Item
{
	public:
	/** \enum ItemType
	 *  \brief Item types in Final Fantasy 7
	 */
	enum ItemType
	{
		Unknown/**< 0*/,Item/**< 1*/,Armor/**< 2*/,Accessory/**< 3*/,WeaponCloud/**< 4*/,
		WeaponBarret/**< 5*/,WeaponTifa/**< 6*/,WeaponRed/**< 7*/,WeaponAerith/**< 8*/,WeaponCid/**< 9*/,
		WeaponYuffie/**< 10*/,WeaponCait/**< 11*/,WeaponVincent/**< 12*/};

	/*!	\enum ItemEffect
	 *	\brief Possible Elemental Effects and Status Effects for items
	 */
	enum ItemEffect
	{
		Absorb = -3,/**< \brief Absorb Element (value:-3)*/
		Nullify =-2,/**< \brief Nullify Element (value:-2)*/
		Protect =-2,/**< \brief Protect from Status (value:-2)*/
		Halve =-1,/**< \brief Halve Element (value:-1)*/
		Remove=-1,/**< \brief Remove Status (value:-1)*/
		NoEffect=0x00,/**<  \brief Does not affect Element or Status (value:0)*/
		Damage=0x01,/**<  \brief Inflict Element1 Dammage (value:1)*/
		Infilict=0x01, /**< \brief Inflict Status On Another (value:1) */
		SelfCast=0x02  /**< \brief Inflict Status On Self (value:2) */
	};
	/*! \enum ItemId
	 *  \brief Item Name to ID
	 */
	enum ItemId
	{
		Potion=0x00,/**< 0x00 */HiPotion=0x01,/**< 0x01 */XPotion=0x02,/**< 0x02 */Ether=0x03,/**< 0x03 */TurboEther=0x04,/**< 0x04 */Elixir=0x05,/**< 0x05 */Megalixir=0x06,/**< 0x06 */PhoenixDown=0x07,/**< 0x07 */Antidote=0x08,/**< 0x08 */Soft=0x09,/**< 0x09 */MaidensKiss=0x0A,/**< 0x0A */Cornucopia=0x0B,/**< 0x0B */Echoscreen=0x0C,/**< 0x0C */Hyper=0x0D,/**< 0x0D */Tranquilizer=0x0E,/**< 0x0E */Remedy=0x0F,/**< 0x0F */
		SmokeBomb=0x10,/**< 0x10 */SpeedDrink=0x11,/**< 0x11 */HeroDrink=0x12,/**< 0x12 */Vaccine=0x13,/**< 0x13 */Grenade=0x14,/**< 0x14 */Shrapnel=0x15,/**< 0x15 */RightArm=0x16,/**< 0x16 */Hourglass=0x17,/**< 0x17 */KissOfDeath=0x18,/**< 0x18 */SpiderWeb=0x19,/**< 0x19 */DreamPowder=0x1A,/**< 0x1A */MuteMask=0x1B,/**< 0x1B */WarGong=0x1C,/**< 0x1C */Locoweed=0x1D,/**< 0x1D */FireFang=0x1E,/**< 0x1E */FireVeil=0x1F,/**< 0x1F */
		AntarcticWind=0x20,/**< 0x20 */IceCrystal=0x21,/**< 0x21 */BoltPlume=0x22,/**< 0x22 */SwiftBolt=0x23,/**< 0x23 */EarthDrum=0x24,/**< 0x24 */EarthMallet=0x25,/**< 0x25 */DeadlyWaste=0x26,/**< 0x26 */MTentacles=0x27,/**< 0x27 */Stardust=0x28,/**< 0x28 */VampireFang=0x29,/**< 0x29 */GhostHand=0x2A,/**< 0x2A */VagyriskClaw=0x2B,/**< 0x2B */LightCurtain=0x2C,/**< 0x2C */LunarCurtain=0x2D,/**< 0x2D */Mirror=0x2E,/**< 0x2E */HolyTorch=0x2F,/**< 0x2F */
		BirdWing=0x30,/**< 0x30 */DragonScales=0x31,/**< 0x31 */Impaler=0x32,/**< 0x32 */Shrivel=0x33,/**< 0x33 */Eyedrop=0x34,/**< 0x34 */Molotov=0x35,/**< 0x35 */SMine=0x36,/**< 0x36 */EightInchCannon=0x37,/**< 0x37 */Graviball=0x38,/**< 0x38 */TSBomb=0x39,/**< 0x39 */Ink=0x3A,/**< 0x3A */Dazers=0x3B,/**< 0x3B */DragonFang=0x3C,/**< 0x3C */Cauldron=0x3D,/**< 0x3D */SylkisGreens=0x3E,/**< 0x3E */ReaganGreens=0x3F,/**< 0x3F */
		MimettGreens=0x40,/**< 0x40 */CurielGreens=0x41,/**< 0x41 */PahsanGreens=0x42,/**< 0x42 */TantalGreens=0x43,/**< 0x43 */KrakkaGreens=0x44,/**< 0x44 */GysahlGreens=0x45,/**< 0x45 */Tent=0x46,/**< 0x46 */PowerSource=0x47,/**< 0x47 */GuardSource=0x48,/**< 0x48 */MagicSource=0x49,/**< 0x49 */MindSource=0x4A,/**< 0x4A */SpeedSource=0x4B,/**< 0x4B */LuckSource=0x4C,/**< 0x4C */ZeioNut=0x4D,/**< 0x4D */CarobNut=0x4E,/**< 0x4E */PorovNut=0x4F,/**< 0x4F */
		PramNut=0x50,/**< 0x50 */LasanNut=0x51,/**< 0x51 */SaharaNut=0x52,/**< 0x52 */LuchileNut=0x53,/**< 0x53 */PepioNut=0x54,/**< 0x54 */Battery=0x55,/**< 0x55 */Tissue=0x56,/**< 0x56 */Omnislash=0x57,/**< 0x57 */Catastrophe=0x58,/**< 0x58 */FinalHeaven=0x59,/**< 0x59 */GreatGospel=0x5A,/**< 0x5A */CosmoMemory=0x5B,/**< 0x5B */AllCreation=0x5C,/**< 0x5C */Chaos=0x5D,/**< 0x5D */Highwind=0x5E,/**< 0x5E */_135thSoldier=0x5F,/**< 0x5F */
		SuperSweeper=0x60,/**< 0x60 */MasamuneBlade=0x61,/**< 0x61 */SaveCrystal=0x62,/**< 0x62 */CombatDiary=0x63,/**< 0x63 */Autograph=0x64,/**< 0x64 */Gambler=0x65,/**< 0x65 */DesertRose=0x66,/**< 0x66 */EarthHarp=0x67,/**< 0x68 */GuideBook=0x68,/**< 0x68 */
		BusterSword=0x80,/**< 0x80 */MythrilSaber=0x81,/**< 0x81 */Hardedge=0x82,/**< 0x82 */BytterflyEdge=0x83,/**< 0x83 */EnhanceSword=0x84,/**< 0x84 */Organics=0x85,/**< 0x85 */CrystalSword=0x86,/**< 0x86 */ForceStealer=0x87,/**< 0x87 */RuneBlade=0x88,/**< 0x88 */Murasame=0x89,/**< 0x89 */NailBat=0x8A,/**< 0x8A */Yoshiyuki=0x8B,/**< 0x8B */Apocalypse=0x8C,/**< 0x8C */HeavensCloud=0x8D,/**< 0x8D */Ragnarok=0x8E,/**< 0x8E */UltimaWeapon=0x8F,/**< 0x8F */
		LeatherGlove=0x90,/**< 0x90 */MetalKnuckle=0x91,/**< 0x91 */MythrilClaw=0x92,/**< 0x92 */GrandGlove=0x93,/**< 0x93 */TigerFang=0x94,/**< 0x94 */DiamondKnuckle=0x95,/**< 0x95 */DragonClaw=0x96,/**< 0x96 */CrystalGlove=0x97,/**< 0x97 */MotorDrive=0x98,/**< 0x98 */PlatinumFist=0x99,/**< 0x99 */KaiserKnuckle=0x9A,/**< 0x9A */WorkGlove=0x9B,/**< 0x9B */Powersoul=0x9C,/**< 0x9C */MasterFist=0x9D,/**< 0x9D */GodsHand=0x9E,/**< 0x9E */PremiumHeart=0x9F,/**< 0x9F */
		GatlingGun=0xA0,/**< 0xA0 */AssaultGun=0xA1,/**< 0xA1 */CannonBall=0xA2,/**< 0xA2 */AtomicScissors=0xA3,/**< 0xA3 */HeavyVulcan=0xA4,/**< 0xA4 */Chainsaw=0xA5,/**< 0xA5 */Microlaser=0xA6,/**< 0xA6 */AMCannon=0xA7,/**< 0xA7 */WMachineGun=0xA8,/**< 0xA8 */DrillArm=0xA9,/**< 0xA9 */SolidBazooka=0xAA,/**< 0xAA */RocketPunch=0xAB,/**< 0xAB */EnemyLauncher=0xAC,/**< 0xAC */PileBanger=0xAD,/**< 0xAD */MaxRay=0xAE,/**< 0xAE */MissingScore=0xAF,/**< 0xAF */
		MythrilClip=0xB0,/**< 0xB0 */DiamondPin=0xB1,/**< 0xB1 */SilverBarrette=0xB2,/**< 0xB2 */GoldBarrette=0xB3,/**< 0xB3 */AdamanClip=0xB4,/**< 0xB4 */CrystalComb=0xB5,/**< 0xB5 */MagicComb=0xB6,/**< 0xB6 */PlusBarrette=0xB7,/**< 0xB7 */Centclip=0xB8,/**< 0xBB */Hairpin=0xB9,/**< 0xB9 */SeraphComb=0xBA,/**< 0xBA */BehemothHorn=0xBB,/**< 0xBB */SpringGunClip=0xBC,/**< 0x BC*/LimitedMoon=0xBD,/**< 0xBD */
		GuardStick=0xBE,/**< 0xBE */MythrilRod=0xBF,/**< 0xBF */FullMetalStaff=0xC0,/**< 0xC0 */StrikingStaff=0xC1,/**< 0xC1 */PrismStaff=0xC2,/**< 0xC2 */AuroraRod=0xC3,/**< 0xC. */WizardStaff=0xC4,/**< 0xC4 */WizerStaff=0xC5,/**< 0xC5 */FairyTale=0xC6,/**< 0xC6 */Umbrella=0xC7,/**< 0xC7 */PrincessGuard=0xC8,/**< 0xC8 */
		Spear=0xC9,/**< 0xC9 */SlashLance=0xCA,/**< 0xCA */Trident=0xCB,/**< 0xCB */MastAx=0xCC,/**< 0xCC */Partisan=0xCD,/**< 0xCD */ViperHalberd=0xCE,/**< 0xCE */Javelin=0xCF,/**< 0xCF */GrowLance=0xD0,/**< 0xD0 */Mop=0xD1,/**< 0xD1 */DragoonLance=0xD2,/**< 0xD2 */Scimitar=0xD3,/**< 0xD3 */Flayer=0xD4,/**< 0xD4 */SpiritLance=0xD5,/**< 0xD5 */VenusGospel=0xD6,/**< 0xD6 */
		FourPointShuriken=0xD7,/**< 0xD7 */Boomerang=0xD8,/**< 0xD8 */Pinwheel=0xD9,/**< 0xD9 */RazorRing=0xDA,/**< 0xDA */Hawkeye=0xDB,/**< 0xDB */CrystalCross=0xDC,/**< 0xDC */WindSlash=0xDD,/**< 0xDD */TwinViper=0xDE,/**< 0xDE */SpiralShuriken=0xDF,/**< 0xDF */Superball=0xE0,/**< 0xE0 */MagicShuriken=0xE1,/**< 0xE1 */RisingSun=0xE2,/**< 0xE2 */Oritsuru=0xE3,/**< 0xE3 */Conformer=0xE4,/**< 0xE4 */
		YellowMphone=0xE5,/**< 0xE5 */GreenMphone=0xE6,/**< 0xE6 */BlueMphone=0xE7,/**< 0xE7 */RedMphone=0xE8,/**< 0xE8 */CrystalMphone=0xE9,/**< 0xE9 */WhiteMphone=0xEA,/**< 0xEA */BlackMphone=0xEB,/**< 0xEB */SilverMphone=0xEC,/**< 0xEC */TrumpetShell=0xED,/**< 0xED */GoldMphone=0xEE,/**< 0xEE */BattleTrumpet=0xEF,/**< 0xEF */StarlightPhone=0xF0,/**< 0xF0 */HpShout=0xF1,/**< 0xF1 */
		Quicksilver=0xF2,/**< 0xF2 */Shotgun=0xF3,/**< 0xF3 */Shortbarrel=0xF4,/**< 0xF4 */Lariat=0xF5,/**< 0xF5 */Winchester=0xF6,/**< 0xF6 */Peacemaker=0xF7,/**< 0xF7 */Buntline=0xF8,/**< 0xF8 */LongBarrelR=0xF9,/**< 0xF9 */SilverRifle=0xFA,/**< 0xFA */SniperCR=0xFB,/**< 0xFB */SupershotST=0xFC,/**< 0xFC */Outsider=0xFD,/**< 0xFD */DeathPenalty=0xFE,/**< 0xFE */Masamune=0xFF,/**< 0xFF */
		BronzeBangle=0x100,/**< 0x100 */IronBangle=0x101,/**< 0x101 */TitanBangle=0x102,/**< 0x102 */MythrilArmlet=0x103,/**< 0x103 */CarbonBangle=0x104,/**< 0x104 */SilverArmlet=0x105,/**< 0x105 */GoldArmlet=0x106,/**< 0x106 */DiamondBangle=0x107,/**< 0x107 */CrystalBangle=0x108,/**< 0x108 */PlatinumBangle=0x109,/**< 0x109 */RuneArmlet=0x10A,/**< 0x10A */Edincoat=0x10B,/**< 0x10B */WizardBracelet=0x10C,/**< 0x10C */AdamanBangle=0x10D,/**< 0x10D */GigasArmlet=0x10E,/**< 0x10F */ImperialGuard=0x10F,/**< 0x10F */
		AegisArmlet=0x110,/**< 0x110 */FourthBracelet=0x111,/**< 0x111 */WarriorBangle=0x112,/**< 0x112 */ShinraBeta=0x113,/**< 0x113 */ShinraAlpha=0x114,/**< 0x114 */FourSlots=0x115,/**< 0x115 */FireArmlet=0x116,/**< 0x116 */AuroraArmlet=0x117,/**< 0x117 */BoltArmlet=0x118,/**< 0x118 */DragonArmlet=0x119,/**< 0x119 */MinervaBand=0x11A,/**< 0x11A */EscortGuard=0x11B,/**< 0x11B */Mystile=0x11C,/**< 0x11C */Ziedrich=0x11D,/**< 0x11D */PreciousWatch=0x11E,/**< 0x11E */Chocobracelet=0x11F,/**< 0x11F */
		PowerWrist=0x120,/**< 0x120 */ProtectVest=0x121,/**< 0x121 */Earring=0x122,/**< 0x122 */Talisman=0x123,/**< 0x123 */ChocoFeather=0x124,/**< 0x124 */Amulet=0x125,/**< 0x125 */ChampionBelt=0x126,/**< 0x126 */PoisonRing=0x127,/**< 0x127 */ToughRing=0x128,/**< 0x128 */Circlet=0x129,/**< 0x129 */ StarPendant=0x12A,/**< 0x12A */SilverGlasses=0x12B,/**< 0x12B */Headband=0x12C,/**< 0x12C */FairyRing=0x12D,/**< 0x12D */JemRing=0x12E,/**< 0x12E */WhiteCape=0x12F,/**< 0x12F */
		SprintShoes=0x130,/**< 0x130 */PeaceRing=0x131,/**< 0x131 */Ribbon=0x132,/**< 0x132 */FireRing=0x133,/**< 0x133 */IceRing=0x134,/**< 0x134 */BoltRing=0x135,/**< 0x135 */TetraElemental=0x136,/**< 0x136 */SafetyBit=0x137,/**< 0x137 */FuryRing=0x138,/**< 0x138 */CurseRing=0x139,/**< 0x139 */ProtectRing=0x13A,/**< 0x13A */CatsBell=0x13B,/**< 0x13B */ReflectRing=0x13C,/**< 0x13C */WaterRing=0x13D,/**< 0x13D */SneakGlove=0x13E,/**< 0x13E */HypnoCrown=0x13F,/**< 0x13F */
		EmptyItem=0x1FF,/**< 0x1FF */EmptyItemData=0xFFFF/**< 0xFFFF */
	};
	/*!	\brief Decode rawitem to quint16
	*	\param itemraw raw 2byte item from ff7 Save
	*	\return quint16 holding an item
	*/
	quint16 itemDecode(quint16 itemraw);

	/*!	\brief Encode quint16 in to a rawitem
	*	\param id item id to be stored
	*	\param qty how many of item
	*	\return quint16 holding an item
	*/
	quint16 itemEncode(quint16 id,quint8 qty);

	/*!	\brief get item id from item
	*	\param item item you want to find the id of. rawitems will be decoded.
	*	\return items ID
	*	\sa itemQty()
	*/
	quint16 itemId(quint16 item);

	/*!	\brief get item id from item
	*	\param item item you want to find the qty of. rawitems will be decoded.
	*	\return items Qty
	*	\sa itemId()
	*/
	quint8 itemQty(quint16 item);

	/*!	\brief get an items name
	*	\param id valid FF7Item::ItemId
	*	\return translated item Name
	*/
	QString name(int id);

	/*!	\brief get an items description
	*	\param id valid FF7Item::ItemId
	*	\return translated item description
	*/
	QString desc(int id);

	/*!	\brief get an items type
	*	\param id valid FF7Item::ItemId
	*	\return Items type
	*	\sa ItemType
	*/
	qint8 type(int id);

	/*!	\brief get an items picture as qicon
	*	\param id valid FF7Item::ItemId
	*	\return Items icon in qicon form
	*	\sa image()
	*/
	QIcon icon(int id);

	/*!	\brief get an items picture as qimage
	*	\param id valid FF7Item::ItemId
	*	\return Items icon in qimage form
	*	\sa icon()
	*/
	QImage image(int id);

	/*!	\brief total number of materia slots in item
	*	\param id valid FF7Item::ItemId
	*	\return number of materia slots in an item
	*	\sa linkedSlots() ,ItemId
	*/
	qint8 materiaSlots(int id);

	/*!	\brief total number  materia links in item
	*	\param id valid FF7Item::ItemId
	*	\return number of materia links in an item
	*	\sa materiaSlots()
	*/
	qint8 linkedSlots(int id);

	/*!	\brief ap multiplier for an item
	*	\param id valid FF7Item::ItemId
	*	\return ap muliplier for given item
	*/
	qint8 materiaGrowthRate(int id);

	/*!	\brief change to HP when equipped
	*	\param id valid FF7Item::ItemId
	*	\return amount HP is changed when item is equipped
	*/
	qint8 statHP(int id);


	/*!	\brief change to MP when equipped
	*	\param id valid FF7Item::ItemId
	*	\return amount MP is changed when item is equipped
	*/
	qint8 statMP(int id);

	/*!	\brief change to strength when equipped
	*	\param id valid FF7Item::ItemId
	*	\return amount strength is changed when item is equipped
	*/
	qint8 statSTR(int id);

	/*!	\brief change to vitality when equipped
	*	\param id valid FF7Item::ItemId
	*	\return amount vitality is changed when item is equipped
	*/
	qint8 statVIT(int id);

	/*!	\brief change to dexterity when equipped
	*	\param id valid FF7Item::ItemId
	*	\return amount dexterity is changed when item is equipped
	*/
	qint8 statDEX(int id);

	/*!	\brief change to luck when equipped
	*	\param id valid FF7Item::ItemId
	*	\return amount luck is changed when item is equipped
	*/
	qint8 statLCK(int id);

	/*!	\brief change to magic when equipped
	*	\param id valid FF7Item::ItemId
	*	\return amount magic is changed when item is equipped
	*/
	qint8 statMAG(int id);

	/*!	\brief change to spirit when equipped
	*	\param id valid FF7Item::ItemId
	*	\return amount spirit is changed when item is equipped
	*/
	qint8 statSPI(int id);

	//Elemental Functions
	/*!	\brief restoration elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Restoration
	*	\sa ItemType
	*/
	qint8 elementRestoration(int id);

	/*!	\brief fire elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Fire
	*	\sa ItemEffect
	*/
	qint8 elementFire(int id);


	/*!	\brief cold elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Cold
	*	\sa ItemEffect
	*/
	qint8 elementCold(int id);

	/*!	\brief lightning elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Lightning
	*	\sa ItemEffect
	*/
	qint8 elementLightning(int id);

	/*!	\brief earth elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Earth
	*	\sa ItemEffect
	*/
	qint8 elementEarth(int id);

	/*!	\brief wind elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Wind
	*	\sa ItemEffect
	*/
	qint8 elementWind(int id);

	/*!	\brief water elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Water
	*	\sa ItemEffect
	*/
	qint8 elementWater(int id);

	/*!	\brief gravity elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Gravity
	*	\sa ItemEffect
	*/
	qint8 elementGravity(int id);

	/*!	\brief ho;y elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Holy
	*	\sa ItemEffect
	*/
	qint8 elementHoly(int id);

	/*!	\brief poison elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Poison
	*	\sa ItemEffect
	*/
	qint8 elementPoison(int id);

	/*!	\brief cut elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Cut
	*	\sa ItemEffect
	*/
	qint8 elementCut(int id);

	/*!	\brief shoot elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Shoot
	*	\sa ItemEffect
	*/
	qint8 elementShoot(int id);

	/*!	\brief punch elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Punch
	*	\sa ItemEffect
	*/
	qint8 elementPunch(int id);

	/*!	\brief hit elemental effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Element Hit
	*	\sa ItemEffect
	*/
	qint8 elementHit(int id);

	//Status Functions
	/*!	\brief death status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Death
	*	\sa ItemEffect
	*/
	qint8 statusDeath(int id);

	/*!	\brief slow numb status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Slow Numb
	*	\sa ItemEffect
	*/
	qint8 statusSlowNumb(int id);

	/*!	\brief death sentence status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Death Sentence
	*	\sa ItemEffect
	*/
	qint8 statusDeathSentence(int id);

	/*!	\brief paralysis status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Paralysis
	*	\sa ItemEffect
	*/
	qint8 statusParalysis(int id);

	/*!	\brief petrify status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Petrify
	*	\sa ItemEffect
	*/
	qint8 statusPetrify(int id);

	/*!	\brief silence status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Silence
	*	\sa ItemEffect
	*/
	qint8 statusSilence(int id);

	/*!	\brief sleep status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Sleep
	*	\sa ItemEffect
	*/
	qint8 statusSleep(int id);

	/*!	\brief confusion status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Confusion
	*	\sa ItemEffect
	*/
	qint8 statusConfusion(int id);

	/*!	\brief berserk status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Berserk
	*	\sa ItemEffect
	*/
	qint8 statusBerserk(int id);

	/*!	\brief frog status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Frog
	*	\sa ItemEffect
	*/
	qint8 statusFrog(int id);

	/*!	\brief mini status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Mini
	*	\sa ItemEffect
	*/
	qint8 statusMini(int id);

	/*!	\brief poison status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Poison
	*	\sa ItemEffect
	*/
	qint8 statusPoison(int id);

	/*!	\brief fury status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Fury
	*	\sa ItemEffect
	*/
	qint8 statusFury(int id);

	/*!	\brief sadness status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Sadness
	*	\sa ItemEffect
	*/
	qint8 statusSadness(int id);

	/*!	\brief darkness status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Darkness
	*	\sa ItemEffect
	*/
	qint8 statusDarkness(int id);

	/*!	\brief haste status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Haste
	*	\sa ItemEffect
	*/
	qint8 statusHaste(int id);

	/*!	\brief slow status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Slow
	*	\sa ItemEffect
	*/
	qint8 statusSlow(int id);

	/*!	\brief stop status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Stop
	*	\sa ItemEffect
	*/
	qint8 statusStop(int id);

	/*!	\brief barrier status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Barrier
	*	\sa ItemEffect
	*/
	qint8 statusBarrier(int id);

	/*!	\brief magic barrier status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Magic Barrier
	*	\sa ItemEffect
	*/
	qint8 statusMagicBarrier(int id);

	/*!	\brief reflect status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Reflect
	*	\sa ItemEffect
	*/
	qint8 statusReflect(int id);

	/*!	\brief shield status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Shield
	*	\sa ItemEffect
	*/
	qint8 statusShield(int id);

	/*!	\brief regen status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Regen
	*	\sa ItemEffect
	*/
	qint8 statusRegen(int id);

	/*!	\brief resist status effect of an item
	*	\param id valid FF7Item::ItemId
	*	\return Type of Effect for Status Resist
	*	\sa ItemEffect
	*/
	qint8 statusResist(int id);


	/*!	\brief Image of a no growth materia slot
	*	\return QImage of a no growth materia slot
	*	\sa imageMateriaSlot(), styleMateriaSlotNoGrowth()
	*/
	QImage imageMateriaSlotNoGrowth(void);

	/*!	\brief Image of a normal materia slot
	*	\return QImage of a normal materia slot
	*	\sa imageMateriaNoGrowthSlot(), styleMateriaSlot()
	*/
	QImage imageMateriaSlot(void);

	/*!	\brief Image of a materia link
	*	\return QImage of a materia link
	*	\sa styleMateriaLink()
	*/
	QImage imageMateriaLink(void);

	/*!	\brief QStyle of a no growth materia slot for use on a QPushButton
	*	\return QStyle of a no growth materia slot
	*	\sa styleMateriaSlot(), imageMateriaSlotNoGrowth()
	*/
	QString styleMateriaSlotNoGrowth(void);

	/*!	\brief QStyle of a normal materia slot for use on a QPushButton
	*	\return QStyle of a normal materia slot
	*	\sa styleMateriaSlotNoGrowth(), imageMateriaSlot()
	*/
	QString styleMateriaSlot(void);

	/*!	\brief QStyle of a materia link for use on a QLabel
	*	\return QStyle of a materia link
	*	\sa imageMateriaLink()
	*/
	QString styleMateriaLink(void);
};

/*! \var Items
 *  \brief Itemdata for all items in Final Fantasy 7
 */
static ITEM Items[]=
{
	{QT_TRANSLATE_NOOP("Items","Potion"),QT_TRANSLATE_NOOP("Item_desc","Restores 100 HP"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Hi-Potion"),QT_TRANSLATE_NOOP("Item_desc","Restores 500 HP"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","X-Potion"),QT_TRANSLATE_NOOP("Item_desc","Restores all lost HP"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Ether"),QT_TRANSLATE_NOOP("Item_desc","Restores 100 MP"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Turbo Ether"),QT_TRANSLATE_NOOP("Item_desc","Restores all lost MP"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Elixir"),QT_TRANSLATE_NOOP("Item_desc","Fully Restores HP/MP"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Megalixir"),QT_TRANSLATE_NOOP("Item_desc","Fully Restores all Members HP/MP"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Phoenix Down"),QT_TRANSLATE_NOOP("Item_desc","Restores life"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Antidote"),QT_TRANSLATE_NOOP("Item_desc","Cures [Poison]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Soft"),QT_TRANSLATE_NOOP("Item_desc","Cures [Petrify]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Maiden's Kiss"),QT_TRANSLATE_NOOP("Item_desc","Cures [Frog]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Cornucopia"),QT_TRANSLATE_NOOP("Item_desc","Cures [Mini]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Echo Screen"),QT_TRANSLATE_NOOP("Item_desc","Cures [Silence]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Hyper"),QT_TRANSLATE_NOOP("Item_desc","Cures [Sadness]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,-1,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Tranquilizer"),QT_TRANSLATE_NOOP("Item_desc","Cures [Fury]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,+1,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Remedy"),QT_TRANSLATE_NOOP("Item_desc","Cures abnormal status"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Smoke Bomb"),QT_TRANSLATE_NOOP("Item_desc","Can escape from opponents during battle"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Speed Drink"),QT_TRANSLATE_NOOP("Item_desc","Casts [Haste] on one ally"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Hero Drink"),QT_TRANSLATE_NOOP("Item_desc","Raises ability once during battle"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Vaccine"),QT_TRANSLATE_NOOP("Item_desc","Protects against transformations"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{QT_TRANSLATE_NOOP("Items","Grenade"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Shrapnel"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Right arm"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Hourglass"),QT_TRANSLATE_NOOP("Item_desc","Stops all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Kiss of Death"),QT_TRANSLATE_NOOP("Item_desc","Uses [Death] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Spider Web"),QT_TRANSLATE_NOOP("Item_desc","Slows all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Dream Powder"),QT_TRANSLATE_NOOP("Item_desc","Uses [Sleepel] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Mute Mask"),QT_TRANSLATE_NOOP("Item_desc","Uses [Silence] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","War Gong"),QT_TRANSLATE_NOOP("Item_desc","Uses [Berserk] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Loco weed"),QT_TRANSLATE_NOOP("Item_desc","Uses [Confu] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Fire Fang"),QT_TRANSLATE_NOOP("Item_desc","Uses [Fire2] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Fire Veil"),QT_TRANSLATE_NOOP("Item_desc","Uses [Fire3] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Antarctic Wind"),QT_TRANSLATE_NOOP("Item_desc","Uses [Ice2] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Ice Crystal"),QT_TRANSLATE_NOOP("Item_desc","Uses [Ice3] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Bolt Plume"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bolt2] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Swift Bolt"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bolt3] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Earth Drum"),QT_TRANSLATE_NOOP("Item_desc","Uses [Quake2] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Earth Mallet"),QT_TRANSLATE_NOOP("Item_desc","Uses [Quake3] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Deadly Waste"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bio2] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","M-Tentacles"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bio3] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Stardust"),QT_TRANSLATE_NOOP("Item_desc","Uses [Comet2] on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Vampire Fang"),QT_TRANSLATE_NOOP("Item_desc","Drains HP out of one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Ghost Hand"),QT_TRANSLATE_NOOP("Item_desc","Drains MP out of one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Vagyrisk Claw"),QT_TRANSLATE_NOOP("Item_desc","Petrifies one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Light Curtain"),QT_TRANSLATE_NOOP("Item_desc","Creates [Barrier] around all allies"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Lunar Curtain"),QT_TRANSLATE_NOOP("Item_desc","Creates [MBarrier] around all allies"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Mirror"),QT_TRANSLATE_NOOP("Item_desc","Uses [Reflect] on all allies"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Holy Torch"),QT_TRANSLATE_NOOP("Item_desc","Uses [DeSpell] on all allies"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,0},
	{QT_TRANSLATE_NOOP("Items","Bird Wing"),QT_TRANSLATE_NOOP("Item_desc","Uses whirlwind on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Dragon Scales"),QT_TRANSLATE_NOOP("Item_desc","Water damage on all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Impaler"),QT_TRANSLATE_NOOP("Item_desc","Changes one opponent to a frog"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Shrivel"),QT_TRANSLATE_NOOP("Item_desc","Uses [Mini] on one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Eye drop"),QT_TRANSLATE_NOOP("Item_desc","Cures [Darkness]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Molotov"),QT_TRANSLATE_NOOP("Item_desc","Fire damage on one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","S-mine"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage on one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","8-inch Cannon"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Graviball"),QT_TRANSLATE_NOOP("Item_desc","Uses [Demi] against one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","T/S Bomb"),QT_TRANSLATE_NOOP("Item_desc","Uses [Demi2] against one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Ink"),QT_TRANSLATE_NOOP("Item_desc","Uses [Darkness] against one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Dazers"),QT_TRANSLATE_NOOP("Item_desc","Paralyzes one opponent"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Dragon Fang"),QT_TRANSLATE_NOOP("Item_desc","Lightning damage against all opponents"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Cauldron"),QT_TRANSLATE_NOOP("Item_desc","Uses [Poison/Confu/Sleepel/Silence/Small/Frog]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,+1,+1,0,+1,+1,+1,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Sylkis Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Reagan Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Mimett Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Curiel Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Pahsana Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Tantal Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Krakka Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Gysahl Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Tent"),QT_TRANSLATE_NOOP("Item_desc","Restores ally's max HP/MP. Use at Save Point."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Power Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Strength]"),1,QString(":/items/item"),
	 0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Guard Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Vitality]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Magic Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Magic Power]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Mind Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Spirit]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Speed Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Dexterity]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Luck Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Luck]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Zeio Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Carob Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Porov Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Pram Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Lasan Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Saraha Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Luchile Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Pepio Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Battery"),QT_TRANSLATE_NOOP("Item_desc","Looks like it can start some sort of machine"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Tissue"),QT_TRANSLATE_NOOP("Item_desc","This one's a little tough..."),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Omnislash"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Omnislash]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Catastrophe"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Catastrophe]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Final Heaven"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Final Heaven]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Great Gospel"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Great Gospel]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Cosmo Memory"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Cosmo Memory]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","All Creation"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [All Creation]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Chaos"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Chaos]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Highwind"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Highwind]"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","1/35 soldier"),QT_TRANSLATE_NOOP("Item_desc","Shinra armored 'attack' soldiers: 12 in the Set!"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Super Sweeper"),QT_TRANSLATE_NOOP("Item_desc","A new machine to protect the reactor!"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Masamune Blade"),QT_TRANSLATE_NOOP("Item_desc","A prefect copy of Sephiroth's sword!"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Save Crystal"),QT_TRANSLATE_NOOP("Item_desc","Use This to create a SAVE Point in the 'North Cave'"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Combat Diary"),QT_TRANSLATE_NOOP("Item_desc","A record of Master Dio's fiercest battles"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Autograph"),QT_TRANSLATE_NOOP("Item_desc","Dio's autograph"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Gambler"),QT_TRANSLATE_NOOP("Item_desc","Second part of Dio's diary: The Gold Saucer years"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Desert Rose"),QT_TRANSLATE_NOOP("Item_desc","Blooms once every 1000 years"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Earth Harp"),QT_TRANSLATE_NOOP("Item_desc","Calms the hearts of all who hear it"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","Guide Book"),QT_TRANSLATE_NOOP("Item_desc","Map of another world. It Slumbers with sunken ships"),1,QString(":/items/item"),
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  //nothing 106-127
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //cloud weapons 128 -143
   {QT_TRANSLATE_NOOP("Items","Buster Sword"),QT_TRANSLATE_NOOP("Item_desc","Initial equiping"),4,QString(":/items/sword"),
	1,2,1,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Saber"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	1,3,1,0,0,0,0,0,0,+4,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Hardedge"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	1,4,1,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Butterfly Edge"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	1,4,2,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Enhance Sword"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	1,8,4,0,0,0,0,0,0,+16,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Organics"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	1,6,2,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Sword"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	1,6,3,0,0,0,0,0,0,+19,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Force Stealer"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	2,3,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rune Blade"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	2,4,0,0,0,0,0,0,0,+9,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Murasame"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	1,5,2,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Nail Bat"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Yoshiyuki"),QT_TRANSLATE_NOOP("Item_desc","Sword is used when an ally is down"),4,QString(":/items/sword"),
	0,2,0,0,0,0,0,0,0,+9,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Apocalypse"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	3,3,0,0,0,0,0,0,0,+43,+16,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Heaven's Cloud"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	1,6,0,0,0,0,0,0,0,+31,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ragnarok"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	1,6,3,0,0,0,0,0,0,+43,+35,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ultima Weapon"),QT_TRANSLATE_NOOP("Item_desc",""),4,QString(":/items/sword"),
	0,8,4,0,0,0,0,0,0,+51,+24,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   ///tifa's weapons 144-159/tifa's weapons 144-159
   {QT_TRANSLATE_NOOP("Items","Leather Glove"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Metal Knuckle"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	1,2,1,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Claw"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	1,3,1,0,0,0,0,0,0,+3,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Grand Glove"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	1,4,1,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Tiger Fang"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	1,4,2,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Diamond Knuckle"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	1,5,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Dragon Claw"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	1,6,2,0,0,0,0,0,0,+13,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Glove"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	1,6,3,0,0,0,0,0,0,+16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Motor Drive"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	2,3,0,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Platinum Fist"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	2,4,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Kaiser Knuckle"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	1,8,1,0,0,0,0,0,0,+13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Work Glove"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Powersoul"),QT_TRANSLATE_NOOP("Item_desc","Power up when [Near death]"),6,QString(":/items/glove"),
	2,4,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Master Fist"),QT_TRANSLATE_NOOP("Item_desc","Power up when condition changes"),6,QString(":/items/glove"),
	1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","God's Hand"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	1,4,2,0,0,0,0,0,0,+34,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Premium Heart"),QT_TRANSLATE_NOOP("Item_desc",""),6,QString(":/items/glove"),
	0,8,4,0,0,0,0,0,0,+32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //barret's weapons 160-175
   {QT_TRANSLATE_NOOP("Items","Gatling Gun"),QT_TRANSLATE_NOOP("Item_desc","Initial equip. Long Range Weapon"),5,QString(":/items/gunarm"),
	1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Assault Gun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QString(":/items/gunarm"),
	1,2,1,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Cannon Ball"),QT_TRANSLATE_NOOP("Item_desc",""),5,QString(":/items/gunarm"),
	1,3,1,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Atomic Scissors"),QT_TRANSLATE_NOOP("Item_desc",""),5,QString(":/items/gunarm"),
	1,4,1,0,0,0,0,0,0,+4,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Heavy Vulcan"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QString(":/items/gunarm"),
	1,4,2,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Chainsaw"),QT_TRANSLATE_NOOP("Item_desc",""),5,QString(":/items/gunarm"),
	1,5,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Microlaser"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QString(":/items/gunarm"),
	1,6,2,0,0,0,0,0,0,+13,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","A M Cannon"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QString(":/items/gunarm"),
	1,6,3,0,0,0,0,0,0,+16,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","W Machine Gun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QString(":/items/gunarm"),
	2,3,0,0,0,0,0,0,0,+3,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Drill Arm"),QT_TRANSLATE_NOOP("Item_desc",""),5,QString(":/items/gunarm"),
	2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Solid Bazooka"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QString(":/items/gunarm"),
	1,8,4,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rocket Punch"),QT_TRANSLATE_NOOP("Item_desc",""),5,QString(":/items/gunarm"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Enemy Launcher"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QString(":/items/gunarm"),
	1,5,1,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Pile Banger"),QT_TRANSLATE_NOOP("Item_desc",""),5,QString(":/items/gunarm"),
	0,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Max Ray"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QString(":/items/gunarm"),
	1,6,3,0,0,0,0,0,0,+30,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Missing Score"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QString(":/items/gunarm"),
	0,8,4,0,0,0,0,0,0,+49,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //red's weapons 176-189
   {QT_TRANSLATE_NOOP("Items","Mythril Clip"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	1,3,1,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Diamond Pin"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	1,4,1,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Barrette"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	1,4,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gold Barrette"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	1,5,2,0,0,0,0,0,0,+13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Adaman Clip"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	1,6,2,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Comb"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	1,6,3,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Magic Comb"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	2,3,0,0,0,0,0,0,0,+4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Plus Barrette"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	2,4,0,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Centclip"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	1,8,0,0,0,0,0,0,0,+22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Hairpin"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),7,QString(":/items/clip"),
	0,0,0,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Seraph Comb"),QT_TRANSLATE_NOOP("Item_desc","Memento of father"),7,QString(":/items/clip"),
	1,4,0,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Behemoth Horn"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	1,6,0,0,0,0,+35,0,0,+26,+18,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Spring Gun Clip"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	1,6,3,0,0,0,0,0,0,+55,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Limited Moon"),QT_TRANSLATE_NOOP("Item_desc",""),7,QString(":/items/clip"),
	0,8,4,0,0,0,0,0,0,+31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //aeris weapons 190-200
   {QT_TRANSLATE_NOOP("Items","Guard Stick"),QT_TRANSLATE_NOOP("Item_desc",""),8,QString(":/items/staff"),
	1,1,0,0,0,0,+1,0,0,+2,+4,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Rod"),QT_TRANSLATE_NOOP("Item_desc",""),8,QString(":/items/staff"),
	1,2,1,0,0,0,0,0,0,+3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Full Metal Staff"),QT_TRANSLATE_NOOP("Item_desc",""),8,QString(":/items/staff"),
	1,3,1,0,0,0,0,0,0,+4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Striking Staff"),QT_TRANSLATE_NOOP("Item_desc",""),8,QString(":/items/staff"),
	1,4,1,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Prism Staff"),QT_TRANSLATE_NOOP("Item_desc",""),8,QString(":/items/staff"),
	1,4,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Aurora Rod"),QT_TRANSLATE_NOOP("Item_desc",""),8,QString(":/items/staff"),
	1,5,2,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wizard Staff"),QT_TRANSLATE_NOOP("Item_desc",""),8,QString(":/items/staff"),
	2,3,0,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wizer Staff"),QT_TRANSLATE_NOOP("Item_desc",""),8,QString(":/items/staff"),
	2,4,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fairy Tale"),QT_TRANSLATE_NOOP("Item_desc",""),8,QString(":/items/staff"),
	1,7,0,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Umbrella"),QT_TRANSLATE_NOOP("Item_desc",""),8,QString(":/items/staff"),
	0,0,0,0,0,0,+20,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Princess Guard"),QT_TRANSLATE_NOOP("Item_desc","Raises Power when you need to protect others nearby"),8,QString(":/items/staff"),
	1,7,3,0,0,0,+12,0,0,+22,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //cid weapons 201-214
   {QT_TRANSLATE_NOOP("Items","Spear"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	1,4,2,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Slash Lance"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	1,5,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Trident"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	1,6,0,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mast Ax"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	1,6,2,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Partisan"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	1,6,3,0,0,0,0,0,0,+17,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Viper Halberd"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	2,4,0,0,0,0,0,0,0,+13,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Javelin"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	2,5,2,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Grow Lance"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	1,6,3,0,0,0,0,0,0,+31,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mop"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	0,0,0,0,0,0,0,0,0,+3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Dragoon Lance"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	1,8,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Scimitar"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	3,2,1,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Flayer"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	1,6,0,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Spirit Lance"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	1,4,2,0,0,0,0,0,0,+43,+20,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Venus Gospel"),QT_TRANSLATE_NOOP("Item_desc",""),9,QString(":/items/spear"),
	0,8,4,0,0,0,0,0,0,+42,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //yuffie weapons 215-228
   {QT_TRANSLATE_NOOP("Items","4-point Shuriken"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	1,3,1,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Boomerang"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	1,4,1,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Pinwheel"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	1,4,2,0,0,0,0,0,0,+9,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Razor Ring"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	1,5,2,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Hawkeye"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	1,6,2,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Cross"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	1,6,3,0,0,0,0,0,0,+18,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wind Slash"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	2,3,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Twin Viper"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	2,4,0,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Spiral Shuriken"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	1,8,1,0,0,0,0,0,0,+18,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Superball"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	0,0,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Magic Shuriken"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	1,3,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rising Sun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	2,4,2,0,0,0,0,0,0,+16,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Oritsuru"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	1,8,2,0,0,0,0,0,0,+38,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Conformer"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QString(":/items/star"),
	0,8,4,0,0,0,0,0,0,+42,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //cait sith weapons 229-241
   {QT_TRANSLATE_NOOP("Items","Yellow M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	1,4,1,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Green M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	1,4,2,0,0,0,0,0,0,+9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Blue M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	1,5,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Red M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	1,6,2,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	1,6,3,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","White M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	2,3,0,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Black M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	2,4,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	1,8,0,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Trumpet Shell"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	0,0,0,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gold M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	1,8,4,0,0,0,0,0,0,+28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Battle Trumpet"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	0,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Starlight Phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	1,8,4,0,0,0,+30,0,0,+31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","HP Shout"),QT_TRANSLATE_NOOP("Item_desc",""),11,QString(":/items/mphone"),
	0,8,4,0,0,0,0,0,0,+44,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //vincent weapons... 242-254
   {QT_TRANSLATE_NOOP("Items","Quicksilver"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	1,4,1,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shotgun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	1,4,2,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shortbarrel"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	1,5,2,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Lariat"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	1,6,2,0,0,0,0,0,0,+16,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Winchester"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	1,6,3,0,0,0,0,0,0,+18,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Peacemaker"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	2,3,1,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Buntline"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	2,4,2,0,0,0,0,0,0,+18,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Long Barrel R"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	1,8,4,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Rifle"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Sniper CR"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	1,4,2,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Supershot ST"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	0,6,3,0,0,0,0,0,0,+52,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Outsider"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	1,8,2,0,0,0,0,0,0,+48,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Death Penalty"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QString(":/items/gun"),
	0,8,4,0,0,0,0,0,0,+34,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //sepi weapon =255
   {QT_TRANSLATE_NOOP("Items","Masamune"),QT_TRANSLATE_NOOP("Item_desc",""),0,QString(""),0,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //armor  256-287
   {QT_TRANSLATE_NOOP("Items","Bronze Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Iron Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Titan Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Carbon Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gold Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Diamond Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Platinum Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rune Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Edincoat"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,7,0,0,0,0,0,0,0,+5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wizard Bracelet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,8,4,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Adaman Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gigas Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	0,5,2,0,0,+30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Imperial Guard"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Aegis Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fourth Bracelet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,5,2,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Warrior Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	0,4,2,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shinra Beta"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shinra Alpha"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Four Slots"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fire Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains [Fire] attacks"),2,QString(":/items/armor"),
	1,4,2,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Aurora Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains [Cold] attacks"),2,QString(":/items/armor"),
	1,4,2,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Bolt Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains [Lightning] attacks"),2,QString(":/items/armor"),
	1,4,2,0,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Dragon Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains 1/2 [Fire/Cold/Lightning] attack"),2,QString(":/items/armor"),
	1,6,3,0,0,0,0,0,0,0,0,0,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Minerva Band"),QT_TRANSLATE_NOOP("Item_desc","Women's Armlet nullifies [Fire/Cold/Gravity/Holy]"),2,QString(":/items/armor"),
	1,6,3,0,0,0,0,0,0,0,0,0,-2,-2,0,0,0,0,-2,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Escort Guard"),QT_TRANSLATE_NOOP("Item_desc","Man's Armlet nullifies [Lightning/Earth/Water/Poison]"),2,QString(":/items/armor"),
	1,6,3,0,0,0,0,0,0,0,0,0,0,0,-2,-2,0,-2,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mystile"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ziedrich"),QT_TRANSLATE_NOOP("Item_desc","Decreases all elemental attacks by 1/2"),2,QString(":/items/armor"),
	0,0,0,0,0,+20,0,0,0,+20,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Precious Watch"),QT_TRANSLATE_NOOP("Item_desc","A gorgeous watch"),2,QString(":/items/armor"),
	1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Chocobracelet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QString(":/items/armor"),
	1,4,0,0,0,0,0,+30,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //accessorys 288-319
   {QT_TRANSLATE_NOOP("Items","Power Wrist"),QT_TRANSLATE_NOOP("Item_desc","Strength +10"),3,QString(":/items/accessory"),
	0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Protect Vest"),QT_TRANSLATE_NOOP("Item_desc","Vitality +10"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Earring"),QT_TRANSLATE_NOOP("Item_desc","Magic +10"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Talisman"),QT_TRANSLATE_NOOP("Item_desc","Spirit +10"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Choco Feather"),QT_TRANSLATE_NOOP("Item_desc","Dexterity +10"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Amulet"),QT_TRANSLATE_NOOP("Item_desc","Luck +10"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Champion Belt"),QT_TRANSLATE_NOOP("Item_desc","Power & Vitality +30"),3,QString(":/items/accessory"),
	0,0,0,0,0,+30,+30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Poison Ring"),QT_TRANSLATE_NOOP("Item_desc","Drains [Poison] attacks, protects against [Poison]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Tough Ring"),QT_TRANSLATE_NOOP("Item_desc","Vitality & Spirit +50"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,+50,0,0,0,+50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Circlet"),QT_TRANSLATE_NOOP("Item_desc","Magic & Spirit +30"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,+30,+30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Star Pendant"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Poison]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Glasses"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Darkness]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Headband"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Sleep]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fairy Ring"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Poison/Darkness]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,-2,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Jem Ring"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Paralyze/Petrify/Slow-numb]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,-2,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","White Cape"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Frog/Small]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Sprint Shoes"),QT_TRANSLATE_NOOP("Item_desc","Automatically put you in [Haste]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Peace Ring"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Berserk/Fury/Sadness]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,0,0,0,-2,-2,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ribbon"),QT_TRANSLATE_NOOP("Item_desc","Protects against all abnormal status"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fire Ring"),QT_TRANSLATE_NOOP("Item_desc","Nullifies [Fire] attacks"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ice Ring"),QT_TRANSLATE_NOOP("Item_desc","Nullifies [Cold] attacks"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Bolt Ring"),QT_TRANSLATE_NOOP("Item_desc","Nullifies [Lightning] attacks"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Tetra Elemental"),QT_TRANSLATE_NOOP("Item_desc","Drains [Fire/Cold/Lightning/Earth] attacks"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,-3,-3,-3,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Safety Bit"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Sudden Death/Petrify/Slow-numb]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,-2,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fury Ring"),QT_TRANSLATE_NOOP("Item_desc","Automatically puts you in [Berserk]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Curse Ring"),QT_TRANSLATE_NOOP("Item_desc","It increases each status but..."),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Protect Ring"),QT_TRANSLATE_NOOP("Item_desc","Automatically sets up [Barrier/MBarrier]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,+2,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Cat's Bell"),QT_TRANSLATE_NOOP("Item_desc","Restores HP as you walk"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Reflect Ring"),QT_TRANSLATE_NOOP("Item_desc","Automatically sets up [Reflect]"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Water Ring"),QT_TRANSLATE_NOOP("Item_desc","Drains Water attacks"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Sneak Glove"),QT_TRANSLATE_NOOP("Item_desc","Increases Stealing rate"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","HypnoCrown"),QT_TRANSLATE_NOOP("Item_desc","Increases Manipulation rate"),3,QString(":/items/accessory"),
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
#endif //FF7Item
