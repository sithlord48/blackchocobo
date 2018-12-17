/****************************************************************************/
//    copyright 2012 - 2018  Chris Rizzitello <sithlord48@gmail.com>        //
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

#pragma once
#include <QObject>
#include <QIcon>

/*! \class FF7Item
 * \brief Information about items in FF7
 */
class FF7Item: public QObject
{
    Q_OBJECT
public:
    /** \enum ItemType
     *  \brief Item types in Final Fantasy 7
     */
    enum ItemType {
        Unknown/**< 0*/
        , Item/**< 1*/
        , Armor/**< 2*/
        , Accessory/**< 3*/
        , WeaponCloud/**< 4*/
        , WeaponBarret/**< 5*/
        , WeaponTifa/**< 6*/
        , WeaponRed/**< 7*/
        , WeaponAerith/**< 8*/
        , WeaponCid/**< 9*/
        , WeaponYuffie/**< 10*/
        , WeaponCait/**< 11*/
        , WeaponVincent /**< 12*/
    };
    Q_ENUM(ItemType)
    /*! \enum ItemEffect
     *  \brief Possible Elemental Effects and Status Effects for items
     */
    enum ItemEffect {
        Absorb = -3/**< \brief Absorb Element (value:-3)*/
        , Nullify = -2 /**< \brief Nullify Element (value:-2)*/
        , Protect = -2 /**< \brief Protect from Status (value:-2)*/
        , Halve = -1 /**< \brief Halve Element (value:-1)*/
        , Remove = -1 /**< \brief Remove Status (value:-1)*/
        , NoEffect = 0x00 /**<  \brief Does not affect Element or Status (value:0)*/
        , Damage = 1 /**<  \brief Inflict Element1 Dammage (value:1)*/
        , Infilict = 1 /**< \brief Inflict Status On Another (value:1) */
        , SelfCast = 2 /**< \brief Inflict Status On Self (value:2) */
    };
    Q_ENUM(ItemEffect)
    /*! \enum ItemId
     *  \brief Item Name to ID
     */
    enum ItemId {
        Potion = 0x00/**< 0x00 */, HiPotion = 0x01/**< 0x01 */, XPotion = 0x02/**< 0x02 */, Ether = 0x03/**< 0x03 */, TurboEther = 0x04/**< 0x04 */, Elixir = 0x05/**< 0x05 */, Megalixir = 0x06/**< 0x06 */, PhoenixDown = 0x07/**< 0x07 */, Antidote = 0x08/**< 0x08 */, Soft = 0x09/**< 0x09 */, MaidensKiss = 0x0A/**< 0x0A */, Cornucopia = 0x0B/**< 0x0B */, Echoscreen = 0x0C/**< 0x0C */, Hyper = 0x0D/**< 0x0D */, Tranquilizer = 0x0E/**< 0x0E */, Remedy = 0x0F /**< 0x0F */
        , SmokeBomb = 0x10/**< 0x10 */, SpeedDrink = 0x11/**< 0x11 */, HeroDrink = 0x12/**< 0x12 */, Vaccine = 0x13/**< 0x13 */, Grenade = 0x14/**< 0x14 */, Shrapnel = 0x15/**< 0x15 */, RightArm = 0x16/**< 0x16 */, Hourglass = 0x17/**< 0x17 */, KissOfDeath = 0x18/**< 0x18 */, SpiderWeb = 0x19/**< 0x19 */, DreamPowder = 0x1A/**< 0x1A */, MuteMask = 0x1B/**< 0x1B */, WarGong = 0x1C/**< 0x1C */, Locoweed = 0x1D/**< 0x1D */, FireFang = 0x1E/**< 0x1E */, FireVeil = 0x1F /**< 0x1F */
        , AntarcticWind = 0x20/**< 0x20 */, IceCrystal = 0x21/**< 0x21 */, BoltPlume = 0x22/**< 0x22 */, SwiftBolt = 0x23/**< 0x23 */, EarthDrum = 0x24/**< 0x24 */, EarthMallet = 0x25/**< 0x25 */, DeadlyWaste = 0x26/**< 0x26 */, MTentacles = 0x27/**< 0x27 */, Stardust = 0x28/**< 0x28 */, VampireFang = 0x29/**< 0x29 */, GhostHand = 0x2A/**< 0x2A */, VagyriskClaw = 0x2B/**< 0x2B */, LightCurtain = 0x2C/**< 0x2C */, LunarCurtain = 0x2D/**< 0x2D */, Mirror = 0x2E/**< 0x2E */, HolyTorch = 0x2F /**< 0x2F */
        , BirdWing = 0x30/**< 0x30 */, DragonScales = 0x31/**< 0x31 */, Impaler = 0x32/**< 0x32 */, Shrivel = 0x33/**< 0x33 */, Eyedrop = 0x34/**< 0x34 */, Molotov = 0x35/**< 0x35 */, SMine = 0x36/**< 0x36 */, EightInchCannon = 0x37/**< 0x37 */, Graviball = 0x38/**< 0x38 */, TSBomb = 0x39/**< 0x39 */, Ink = 0x3A/**< 0x3A */, Dazers = 0x3B/**< 0x3B */, DragonFang = 0x3C/**< 0x3C */, Cauldron = 0x3D/**< 0x3D */, SylkisGreens = 0x3E/**< 0x3E */, ReaganGreens = 0x3F /**< 0x3F */
        , MimettGreens = 0x40/**< 0x40 */, CurielGreens = 0x41/**< 0x41 */, PahsanGreens = 0x42/**< 0x42 */, TantalGreens = 0x43/**< 0x43 */, KrakkaGreens = 0x44/**< 0x44 */, GysahlGreens = 0x45/**< 0x45 */, Tent = 0x46/**< 0x46 */, PowerSource = 0x47/**< 0x47 */, GuardSource = 0x48/**< 0x48 */, MagicSource = 0x49/**< 0x49 */, MindSource = 0x4A/**< 0x4A */, SpeedSource = 0x4B/**< 0x4B */, LuckSource = 0x4C/**< 0x4C */, ZeioNut = 0x4D/**< 0x4D */, CarobNut = 0x4E/**< 0x4E */, PorovNut = 0x4F /**< 0x4F */
        , PramNut = 0x50/**< 0x50 */, LasanNut = 0x51/**< 0x51 */, SaharaNut = 0x52/**< 0x52 */, LuchileNut = 0x53/**< 0x53 */, PepioNut = 0x54/**< 0x54 */, Battery = 0x55/**< 0x55 */, Tissue = 0x56/**< 0x56 */, Omnislash = 0x57/**< 0x57 */, Catastrophe = 0x58/**< 0x58 */, FinalHeaven = 0x59/**< 0x59 */, GreatGospel = 0x5A/**< 0x5A */, CosmoMemory = 0x5B/**< 0x5B */, AllCreation = 0x5C/**< 0x5C */, Chaos = 0x5D/**< 0x5D */, Highwind = 0x5E/**< 0x5E */, _135thSoldier = 0x5F /**< 0x5F */
        , SuperSweeper = 0x60/**< 0x60 */, MasamuneBlade = 0x61/**< 0x61 */, SaveCrystal = 0x62/**< 0x62 */, CombatDiary = 0x63/**< 0x63 */, Autograph = 0x64/**< 0x64 */, Gambler = 0x65/**< 0x65 */, DesertRose = 0x66/**< 0x66 */, EarthHarp = 0x67/**< 0x68 */, GuideBook = 0x68 /**< 0x68 */
        , BusterSword = 0x80/**< 0x80 */, MythrilSaber = 0x81/**< 0x81 */, Hardedge = 0x82/**< 0x82 */, BytterflyEdge = 0x83/**< 0x83 */, EnhanceSword = 0x84/**< 0x84 */, Organics = 0x85/**< 0x85 */, CrystalSword = 0x86/**< 0x86 */, ForceStealer = 0x87/**< 0x87 */, RuneBlade = 0x88/**< 0x88 */, Murasame = 0x89/**< 0x89 */, NailBat = 0x8A/**< 0x8A */, Yoshiyuki = 0x8B/**< 0x8B */, Apocalypse = 0x8C/**< 0x8C */, HeavensCloud = 0x8D/**< 0x8D */, Ragnarok = 0x8E/**< 0x8E */, UltimaWeapon = 0x8F /**< 0x8F */
        , LeatherGlove = 0x90/**< 0x90 */, MetalKnuckle = 0x91/**< 0x91 */, MythrilClaw = 0x92/**< 0x92 */, GrandGlove = 0x93/**< 0x93 */, TigerFang = 0x94/**< 0x94 */, DiamondKnuckle = 0x95/**< 0x95 */, DragonClaw = 0x96/**< 0x96 */, CrystalGlove = 0x97/**< 0x97 */, MotorDrive = 0x98/**< 0x98 */, PlatinumFist = 0x99/**< 0x99 */, KaiserKnuckle = 0x9A/**< 0x9A */, WorkGlove = 0x9B/**< 0x9B */, Powersoul = 0x9C/**< 0x9C */, MasterFist = 0x9D/**< 0x9D */, GodsHand = 0x9E/**< 0x9E */, PremiumHeart = 0x9F /**< 0x9F */
        , GatlingGun = 0xA0/**< 0xA0 */, AssaultGun = 0xA1/**< 0xA1 */, CannonBall = 0xA2/**< 0xA2 */, AtomicScissors = 0xA3/**< 0xA3 */, HeavyVulcan = 0xA4/**< 0xA4 */, Chainsaw = 0xA5/**< 0xA5 */, Microlaser = 0xA6/**< 0xA6 */, AMCannon = 0xA7/**< 0xA7 */, WMachineGun = 0xA8/**< 0xA8 */, DrillArm = 0xA9/**< 0xA9 */, SolidBazooka = 0xAA/**< 0xAA */, RocketPunch = 0xAB/**< 0xAB */, EnemyLauncher = 0xAC/**< 0xAC */, PileBanger = 0xAD/**< 0xAD */, MaxRay = 0xAE/**< 0xAE */, MissingScore = 0xAF /**< 0xAF */
        , MythrilClip = 0xB0/**< 0xB0 */, DiamondPin = 0xB1/**< 0xB1 */, SilverBarrette = 0xB2/**< 0xB2 */, GoldBarrette = 0xB3/**< 0xB3 */, AdamanClip = 0xB4/**< 0xB4 */, CrystalComb = 0xB5/**< 0xB5 */, MagicComb = 0xB6/**< 0xB6 */, PlusBarrette = 0xB7/**< 0xB7 */, Centclip = 0xB8/**< 0xBB */, Hairpin = 0xB9/**< 0xB9 */, SeraphComb = 0xBA/**< 0xBA */, BehemothHorn = 0xBB/**< 0xBB */, SpringGunClip = 0xBC/**< 0x BC*/, LimitedMoon = 0xBD /**< 0xBD */
        , GuardStick = 0xBE/**< 0xBE */, MythrilRod = 0xBF/**< 0xBF */, FullMetalStaff = 0xC0/**< 0xC0 */, StrikingStaff = 0xC1/**< 0xC1 */, PrismStaff = 0xC2/**< 0xC2 */, AuroraRod = 0xC3/**< 0xC. */, WizardStaff = 0xC4/**< 0xC4 */, WizerStaff = 0xC5/**< 0xC5 */, FairyTale = 0xC6/**< 0xC6 */, Umbrella = 0xC7/**< 0xC7 */, PrincessGuard = 0xC8 /**< 0xC8 */
        , Spear = 0xC9/**< 0xC9 */, SlashLance = 0xCA/**< 0xCA */, Trident = 0xCB/**< 0xCB */, MastAx = 0xCC/**< 0xCC */, Partisan = 0xCD/**< 0xCD */, ViperHalberd = 0xCE/**< 0xCE */, Javelin = 0xCF/**< 0xCF */, GrowLance = 0xD0/**< 0xD0 */, Mop = 0xD1/**< 0xD1 */, DragoonLance = 0xD2/**< 0xD2 */, Scimitar = 0xD3/**< 0xD3 */, Flayer = 0xD4/**< 0xD4 */, SpiritLance = 0xD5/**< 0xD5 */, VenusGospel = 0xD6 /**< 0xD6 */
        , FourPointShuriken = 0xD7/**< 0xD7 */, Boomerang = 0xD8/**< 0xD8 */, Pinwheel = 0xD9/**< 0xD9 */, RazorRing = 0xDA/**< 0xDA */, Hawkeye = 0xDB/**< 0xDB */, CrystalCross = 0xDC/**< 0xDC */, WindSlash = 0xDD/**< 0xDD */, TwinViper = 0xDE/**< 0xDE */, SpiralShuriken = 0xDF/**< 0xDF */, Superball = 0xE0/**< 0xE0 */, MagicShuriken = 0xE1/**< 0xE1 */, RisingSun = 0xE2/**< 0xE2 */, Oritsuru = 0xE3/**< 0xE3 */, Conformer = 0xE4 /**< 0xE4 */
        , YellowMphone = 0xE5/**< 0xE5 */, GreenMphone = 0xE6/**< 0xE6 */, BlueMphone = 0xE7/**< 0xE7 */, RedMphone = 0xE8/**< 0xE8 */, CrystalMphone = 0xE9/**< 0xE9 */, WhiteMphone = 0xEA/**< 0xEA */, BlackMphone = 0xEB/**< 0xEB */, SilverMphone = 0xEC/**< 0xEC */, TrumpetShell = 0xED/**< 0xED */, GoldMphone = 0xEE/**< 0xEE */, BattleTrumpet = 0xEF/**< 0xEF */, StarlightPhone = 0xF0/**< 0xF0 */, HpShout = 0xF1 /**< 0xF1 */
        , Quicksilver = 0xF2/**< 0xF2 */, Shotgun = 0xF3/**< 0xF3 */, Shortbarrel = 0xF4/**< 0xF4 */, Lariat = 0xF5/**< 0xF5 */, Winchester = 0xF6/**< 0xF6 */, Peacemaker = 0xF7/**< 0xF7 */, Buntline = 0xF8/**< 0xF8 */, LongBarrelR = 0xF9/**< 0xF9 */, SilverRifle = 0xFA/**< 0xFA */, SniperCR = 0xFB/**< 0xFB */, SupershotST = 0xFC/**< 0xFC */, Outsider = 0xFD/**< 0xFD */, DeathPenalty = 0xFE/**< 0xFE */, Masamune = 0xFF /**< 0xFF */
        , BronzeBangle = 0x100/**< 0x100 */, IronBangle = 0x101/**< 0x101 */, TitanBangle = 0x102/**< 0x102 */, MythrilArmlet = 0x103/**< 0x103 */, CarbonBangle = 0x104/**< 0x104 */, SilverArmlet = 0x105/**< 0x105 */, GoldArmlet = 0x106/**< 0x106 */, DiamondBangle = 0x107/**< 0x107 */, CrystalBangle = 0x108/**< 0x108 */, PlatinumBangle = 0x109/**< 0x109 */, RuneArmlet = 0x10A/**< 0x10A */, Edincoat = 0x10B/**< 0x10B */, WizardBracelet = 0x10C/**< 0x10C */, AdamanBangle = 0x10D/**< 0x10D */, GigasArmlet = 0x10E, /**< 0x10F */ ImperialGuard = 0x10F /**< 0x10F */
        , AegisArmlet = 0x110/**< 0x110 */, FourthBracelet = 0x111/**< 0x111 */, WarriorBangle = 0x112/**< 0x112 */, ShinraBeta = 0x113/**< 0x113 */, ShinraAlpha = 0x114/**< 0x114 */, FourSlots = 0x115/**< 0x115 */, FireArmlet = 0x116/**< 0x116 */, AuroraArmlet = 0x117/**< 0x117 */, BoltArmlet = 0x118/**< 0x118 */, DragonArmlet = 0x119/**< 0x119 */, MinervaBand = 0x11A/**< 0x11A */, EscortGuard = 0x11B/**< 0x11B */, Mystile = 0x11C/**< 0x11C */, Ziedrich = 0x11D/**< 0x11D */, PreciousWatch = 0x11E/**< 0x11E */, Chocobracelet = 0x11F /**< 0x11F */
        , PowerWrist = 0x120/**< 0x120 */, ProtectVest = 0x121/**< 0x121 */, Earring = 0x122/**< 0x122 */, Talisman = 0x123/**< 0x123 */, ChocoFeather = 0x124/**< 0x124 */, Amulet = 0x125/**< 0x125 */, ChampionBelt = 0x126/**< 0x126 */, PoisonRing = 0x127/**< 0x127 */, ToughRing = 0x128/**< 0x128 */, Circlet = 0x129/**< 0x129 */,  StarPendant = 0x12A/**< 0x12A */, SilverGlasses = 0x12B/**< 0x12B */, Headband = 0x12C/**< 0x12C */, FairyRing = 0x12D/**< 0x12D */, JemRing = 0x12E/**< 0x12E */, WhiteCape = 0x12F /**< 0x12F */
        , SprintShoes = 0x130/**< 0x130 */, PeaceRing = 0x131/**< 0x131 */, Ribbon = 0x132/**< 0x132 */, FireRing = 0x133/**< 0x133 */, IceRing = 0x134/**< 0x134 */, BoltRing = 0x135/**< 0x135 */, TetraElemental = 0x136/**< 0x136 */, SafetyBit = 0x137/**< 0x137 */, FuryRing = 0x138/**< 0x138 */, CurseRing = 0x139/**< 0x139 */, ProtectRing = 0x13A/**< 0x13A */, CatsBell = 0x13B/**< 0x13B */, ReflectRing = 0x13C/**< 0x13C */, WaterRing = 0x13D/**< 0x13D */, SneakGlove = 0x13E/**< 0x13E */, HypnoCrown = 0x13F /**< 0x13F */
        , EmptyItem = 0x1FF/**< 0x1FF */, EmptyItemData = 0xFFFF /**< 0xFFFF */
    };
    Q_ENUM(ItemId)

    /*! \brief Decode rawitem to quint16
    *   \param itemraw raw 2byte item from ff7 Save
    *   \return quint16 holding an item
    */
    Q_INVOKABLE quint16 itemDecode(quint16 itemraw);

    /*! \brief Encode quint16 in to a rawitem
    *   \param id item id to be stored
    *   \param qty how many of item
    *   \return quint16 holding an item
    */
    Q_INVOKABLE quint16 itemEncode(quint16 id, quint8 qty);

    /*! \brief get item id from item
    *   \param item item you want to find the id of. rawitems will be decoded.
    *   \return items ID
    *   \sa itemQty()
    */
    Q_INVOKABLE quint16 itemId(quint16 item);

    /*! \brief get item id from item
    *   \param item item you want to find the qty of. rawitems will be decoded.
    *   \return items Qty
    *   \sa itemId()
    */
    Q_INVOKABLE quint8 itemQty(quint16 item);

    /*! \brief get an items name
    *   \param id valid FF7Item::ItemId
    *   \return translated item Name
    */
    Q_INVOKABLE QString name(int id);

    /*! \brief get an items description
    *   \param id valid FF7Item::ItemId
    *   \return translated item description
    */
    Q_INVOKABLE QString desc(int id);

    /*! \brief get an items picture as qstring
    *   \param id valid FF7Item::ItemId
    *   \return Items icon in qstring form
    *   \sa image()
    */
    Q_INVOKABLE QString iconResource(int id);


    /*! \brief get an items type
    *   \param id valid FF7Item::ItemId
    *   \return Items type
    *   \sa ItemType
    */
    Q_INVOKABLE inline int type(int id){return item(id).type;}

    /*! \brief get an items picture as qicon
    *   \param id valid FF7Item::ItemId
    *   \return Items icon in qicon form
    *   \sa image()
    */
    inline QIcon icon(int id){return QIcon(QPixmap::fromImage(image(id)));}

    /*! \brief get materia no growth slot picture as qstring
    *   \return Image resource in qstring form
    *   \sa materiaSlotResource(), materiaLinkResource()
    */
    Q_INVOKABLE inline QString materiaSlotNoGrowthResource(){return _resourceSlotNoGrowth;}

    /*! \brief get materia slot picture as qstring
    *   \return Image resource in qstring form
    *   \sa materiaSlotNoGrowthResource(), materiaLinkResource()
    */
    Q_INVOKABLE inline QString materiaSlotResource(){return _resourceSlot;}

    /*! \brief get materia no growth slot picture as qstring
    *   \return Image resource in qstring form
    *   \sa materiaSlotResource(), materiaSlotNoGrowthResource()
    */
    Q_INVOKABLE inline QString materiaLinkResource(){return _resourceLink;}

    /*! \brief get an items picture as qimage
    *   \param id valid FF7Item::ItemId
    *   \return Items icon in qimage form
    *   \sa icon()
    */
    inline QImage image(int id){return QImage(item(id).imageString);}

    /*! \brief total number of materia slots in item
    *   \param id valid FF7Item::ItemId
    *   \return number of materia slots in an item
    *   \sa linkedSlots() ,ItemId
    */
    Q_INVOKABLE inline int materiaSlots(int id){return item(id).mslots;}

    /*! \brief total number  materia links in item
    *   \param id valid FF7Item::ItemId
    *   \return number of materia links in an item
    *   \sa materiaSlots()
    */
    Q_INVOKABLE inline int linkedSlots(int id){return item(id).linked;}

    /*! \brief ap multiplier for an item
    *   \param id valid FF7Item::ItemId
    *   \return ap muliplier for given item
    */
    Q_INVOKABLE inline int materiaGrowthRate(int id){return item(id).mgrowth;}

    /*! \brief change to HP when equipped
    *   \param id valid FF7Item::ItemId
    *   \return amount HP is changed when item is equipped
    */
    Q_INVOKABLE inline int statHP(int id){return item(id).hp;}

    /*! \brief change to MP when equipped
    *   \param id valid FF7Item::ItemId
    *   \return amount MP is changed when item is equipped
    */
    Q_INVOKABLE inline int statMP(int id){return item(id).mp;}

    /*! \brief change to strength when equipped
    *   \param id valid FF7Item::ItemId
    *   \return amount strength is changed when item is equipped
    */
    Q_INVOKABLE inline int statSTR(int id){return item(id).str;}

    /*! \brief change to vitality when equipped
    *   \param id valid FF7Item::ItemId
    *   \return amount vitality is changed when item is equipped
    */
    Q_INVOKABLE inline int statVIT(int id){return item(id).vit;}

    /*! \brief change to dexterity when equipped
    *   \param id valid FF7Item::ItemId
    *   \return amount dexterity is changed when item is equipped
    */
    Q_INVOKABLE inline int statDEX(int id){return item(id).dex;}

    /*! \brief change to luck when equipped
    *   \param id valid FF7Item::ItemId
    *   \return amount luck is changed when item is equipped
    */
    Q_INVOKABLE inline int statLCK(int id){return item(id).lck;}

    /*! \brief change to magic when equipped
    *   \param id valid FF7Item::ItemId
    *   \return amount magic is changed when item is equipped
    */
    Q_INVOKABLE inline int statMAG(int id){return item(id).mag;}

    /*! \brief change to spirit when equipped
    *   \param id valid FF7Item::ItemId
    *   \return amount spirit is changed when item is equipped
    */
    Q_INVOKABLE inline int statSPI(int id){return item(id).spi;}

    //Elemental Functions
    /*! \brief get a list of the items elemental properties
    *   \param id valid FF7Item::ItemId
    *   \return QList of elemental effects of the item in TYPE:ELEMENT format (ABSORB:WIND)
    */
    Q_INVOKABLE QStringList elementalEffects(int id);

    /*! \brief restoration elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Restoration
    *   \sa ItemType
    */
    Q_INVOKABLE inline int elementRestoration(int id){return item(id).e_restoration;}

    /*! \brief fire elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Fire
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementFire(int id){return item(id).e_fire;}

    /*! \brief cold elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Cold
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementCold(int id){return item(id).e_cold;}

    /*! \brief lightning elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Lightning
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementLightning(int id){return item(id).e_lightning;}

    /*! \brief earth elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Earth
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementEarth(int id){return item(id).e_earth;}

    /*! \brief wind elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Wind
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementWind(int id){return item(id).e_wind;}

    /*! \brief water elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Water
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementWater(int id){return item(id).e_water;}

    /*! \brief gravity elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Gravity
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementGravity(int id){return item(id).e_gravity;}

    /*! \brief ho;y elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Holy
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementHoly(int id){return item(id).e_holy;}

    /*! \brief poison elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Poison
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementPoison(int id){return item(id).e_poison;}

    /*! \brief cut elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Cut
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementCut(int id){return item(id).e_cut;}

    /*! \brief shoot elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Shoot
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementShoot(int id){return item(id).e_shoot;}

    /*! \brief punch elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Punch
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementPunch(int id){return item(id).e_punch;}

    /*! \brief hit elemental effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Element Hit
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int elementHit(int id){return item(id).e_hit;}

    //Status Functions

    /*! \brief get a list of the items status properties
    *   \param id valid FF7Item::ItemId
    *   \return QList of status effects of the item in TYPE:STATUS format (PROTECT:POISION)
    */
    Q_INVOKABLE QStringList statusEffects(int id);

    /*! \brief death status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Death
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusDeath(int id){return item(id).s_death;}

    /*! \brief slow numb status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Slow Numb
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusSlowNumb(int id){return item(id).s_slow_numb;}

    /*! \brief death sentence status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Death Sentence
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusDeathSentence(int id){return item(id).s_d_sentence;}

    /*! \brief paralysis status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Paralysis
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusParalysis(int id){return item(id).s_paralysis;}

    /*! \brief petrify status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Petrify
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusPetrify(int id){return item(id).s_petrify;}

    /*! \brief silence status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Silence
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusSilence(int id){return item(id).s_silence;}

    /*! \brief sleep status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Sleep
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusSleep(int id){return item(id).s_sleep;}

    /*! \brief confusion status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Confusion
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusConfusion(int id){return item(id).s_confusion;}

    /*! \brief berserk status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Berserk
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusBerserk(int id){return item(id).s_berserk;}

    /*! \brief frog status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Frog
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusFrog(int id){return item(id).s_frog;}

    /*! \brief mini status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Mini
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusMini(int id){return item(id).s_mini;}

    /*! \brief poison status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Poison
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusPoison(int id){return item(id).s_poison;}

    /*! \brief fury status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Fury
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusFury(int id){return item(id).s_fury;}

    /*! \brief sadness status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Sadness
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusSadness(int id){return item(id).s_sadness;}

    /*! \brief darkness status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Darkness
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusDarkness(int id){return item(id).s_darkness;}

    /*! \brief haste status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Haste
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusHaste(int id){return item(id).s_haste;}

    /*! \brief slow status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Slow
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusSlow(int id){return item(id).s_slow;}

    /*! \brief stop status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Stop
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusStop(int id){return item(id).s_stop;}

    /*! \brief barrier status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Barrier
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusBarrier(int id){return item(id).s_barrier;}

    /*! \brief magic barrier status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Magic Barrier
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusMagicBarrier(int id){return item(id).s_m_barrier;}

    /*! \brief reflect status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Reflect
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusReflect(int id){return item(id).s_reflect;}

    /*! \brief shield status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Shield
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusShield(int id){return item(id).s_sheild;}

    /*! \brief regen status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Regen
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusRegen(int id){return item(id).s_regen;}

    /*! \brief resist status effect of an item
    *   \param id valid FF7Item::ItemId
    *   \return Type of Effect for Status Resist
    *   \sa ItemEffect
    */
    Q_INVOKABLE inline int statusResist(int id){return item(id).s_resist;}

    /*! \brief Return number if items in _items
     */
    Q_INVOKABLE inline int size() const {return _items.size();}

    /*! \brief Image of a no growth materia slot
    *   \return QImage of a no growth materia slot
    *   \sa imageMateriaSlot(), styleMateriaSlotNoGrowth()
    */
    inline QImage imageMateriaSlotNoGrowth() {return QImage(materiaSlotNoGrowthResource());}

    /*! \brief Image of a normal materia slot
    *   \return QImage of a normal materia slot
    *   \sa imageMateriaNoGrowthSlot(), styleMateriaSlot()
    */
    inline QImage imageMateriaSlot(){return QImage(materiaSlotResource());}

    /*! \brief Image of a materia link
    *   \return QImage of a materia link
    *   \sa styleMateriaLink()
    */
    inline QImage imageMateriaLink(){return QImage(materiaLinkResource());}

    /*! \brief QStyle of a no growth materia slot for use on a QPushButton
    *   \return QStyle of a no growth materia slot
    *   \sa styleMateriaSlot(), imageMateriaSlotNoGrowth()
    */
    inline const QString& styleMateriaSlotNoGrowth(){return _styleSlotNoGrowth;}

    /*! \brief QStyle of a normal materia slot for use on a QPushButton
    *   \return QStyle of a normal materia slot
    *   \sa styleMateriaSlotNoGrowth(), imageMateriaSlot()
    */
    inline const QString& styleMateriaSlot(){return _styleSlot;}

    /*! \brief QStyle of a materia link for use on a QLabel
    *   \return QStyle of a materia link
    *   \sa imageMateriaLink()
    */
    inline const QString& styleMateriaLink(){return _styleLink;}
private:
    inline static const auto _resourceSlotNoGrowth = QStringLiteral("items/m_no_grow_slot");
    inline static const auto _resourceSlot = QStringLiteral("items/m_grow_slot");
    inline static const auto _resourceLink = QStringLiteral("items/m_link");
    inline static const auto _groupNames = QStringLiteral("Items");
    inline static const auto _groupDesc = QStringLiteral("Item_desc");
    inline static const auto _styleSlotNoGrowth = QStringLiteral("QPushButton:enabled{border: 0px;border-radius:16px;background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.814, fx:0.5, fy:0.5, stop:0 rgba(0, 1, 0, 255), stop:0.079096 rgba(77, 77, 77, 255), stop:0.152542 rgba(11, 28, 19, 255), stop:0.429379 rgba(37, 37, 37, 255), stop:0.514124 rgba(200, 195, 194, 255), stop:0.576271 rgba(153, 152, 152, 255), stop:0.655367 rgba(185, 181, 179, 255), stop:0.677966 rgba(37, 37, 37, 0));}QPushButton:hover{}");
    inline static const auto _styleSlot = QStringLiteral("QPushButton:enabled{border: 0px;border-radius:16px;background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.814, fx:0.5, fy:0.5, stop:0 rgba(0, 1, 0, 255), stop:0.429379 rgba(37, 37, 37, 255), stop:0.514124 rgba(200, 195, 194, 255), stop:0.576271 rgba(153, 152, 152, 255), stop:0.655367 rgba(185, 181, 179, 255), stop:0.677966 rgba(37, 37, 37, 0));}QPushButton:hover{}");
    inline static const auto _styleLink = QStringLiteral("QLabel:enabled{background-color: qlineargradient(spread:reflect, x1:0.5, y1:0.5, x2:0.5, y2:0, stop:0.0225989 rgba(37, 37, 37, 255), stop:0.231638 rgba(153, 152, 152, 255), stop:0.389831 rgba(200, 195, 194, 255), stop:0.502825 rgba(138, 137, 137, 255), stop:0.621469 rgba(200, 195, 194, 255), stop:0.768362 rgba(138, 137, 137, 255), stop:0.932584 rgba(37, 37, 37, 0));}");

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
    /*!
     * \brief Internal Wrapper to return Items
     * \param id: item to get Or empty data if invalid.
     * \return item data.
     */
    const FF7Item::ITEM& item(int id);
    inline static const ITEM _emptyitem{
        QString(), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    /*! \var _items
     *  \brief Itemdata for all items in Final Fantasy 7
     */
    inline static const QList<ITEM> _items{
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Potion")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Restores 100 HP")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Hi-Potion")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Restores 500 HP")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("X-Potion")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Restores all lost HP")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Ether")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Restores 100 MP")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Turbo Ether")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Restores all lost MP")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Elixir")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Fully Restores HP/MP")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Megalixir")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Fully Restores all Members HP/MP")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Phoenix Down")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Restores life")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Antidote")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Cures [Poison]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Soft")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Cures [Petrify]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Maiden's Kiss")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Cures [Frog]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Cornucopia")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Cures [Mini]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Echo Screen")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Cures [Silence]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Hyper")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Cures [Sadness]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Tranquilizer")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Cures [Fury]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Remedy")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Cures abnormal status")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Smoke Bomb")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Can escape from opponents during battle")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Speed Drink")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Casts [Haste] on one ally")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Hero Drink")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Raises ability once during battle")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Vaccine")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Protects against transformations")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Grenade")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Explosive damage against one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Shrapnel")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Explosive damage against all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Right arm")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Explosive damage against all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Hourglass")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Stops all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Kiss of Death")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Death] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Spider Web")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Slows all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Dream Powder")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Sleepel] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mute Mask")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Silence] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("War Gong")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Berserk] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Loco weed")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Confu] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Fire Fang")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Fire2] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Fire Veil")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Fire3] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Antarctic Wind")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Ice2] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Ice Crystal")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Ice3] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Bolt Plume")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Bolt2] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Swift Bolt")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Bolt3] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Earth Drum")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Quake2] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Earth Mallet")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Quake3] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Deadly Waste")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Bio2] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("M-Tentacles")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Bio3] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Stardust")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Comet2] on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Vampire Fang")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Drains HP out of one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Ghost Hand")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Drains MP out of one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Vagyrisk Claw")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Petrifies one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Light Curtain")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Creates [Barrier] around all allies")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Lunar Curtain")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Creates [MBarrier] around all allies")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mirror")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Reflect] on all allies")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Holy Torch")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [DeSpell] on all allies")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Bird Wing")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses whirlwind on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Dragon Scales")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Water damage on all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Impaler")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Changes one opponent to a frog")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Shrivel")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Mini] on one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Eye drop")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Cures [Darkness]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Molotov")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Fire damage on one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("S-mine")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Explosive damage on one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("8-inch Cannon")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Explosive damage against one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Graviball")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Demi] against one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("T/S Bomb")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Demi2] against one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Ink")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Darkness] against one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Dazers")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Paralyzes one opponent")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Dragon Fang")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Lightning damage against all opponents")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Cauldron")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Uses [Poison/Confu/Sleepel/Silence/Small/Frog]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, +1, +1, 0, +1, +1, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Sylkis Greens")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want a chocobo...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Reagan Greens")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want a chocobo...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mimett Greens")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want a chocobo...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Curiel Greens")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want a chocobo...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Pahsana Greens")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want a chocobo...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Tantal Greens")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want a chocobo...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Krakka Greens")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want a chocobo...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Gysahl Greens")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want a chocobo...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Tent")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Restores ally's max HP/MP. Use at Save Point.")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Power Source")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Raises [Strength]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Guard Source")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Raises [Vitality]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Magic Source")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Raises [Magic Power]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mind Source")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Raises [Spirit]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Speed Source")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Raises [Dexterity]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Luck Source")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Raises [Luck]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Zeio Nut")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want to breed Chocobos...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Carob Nut")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want to breed Chocobos...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Porov Nut")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want to breed Chocobos...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Pram Nut")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want to breed Chocobos...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Lasan Nut")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want to breed Chocobos...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Saraha Nut")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want to breed Chocobos...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Luchile Nut")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want to breed Chocobos...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Pepio Nut")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("When you want to breed Chocobos...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Battery")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Looks like it can start some sort of machine")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Tissue")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("This one's a little tough...")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Omnislash")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Learn Limit Skill [Omnislash]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Catastrophe")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Learn Limit Skill [Catastrophe]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Final Heaven")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Learn Limit Skill [Final Heaven]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Great Gospel")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Learn Limit Skill [Great Gospel]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Cosmo Memory")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Learn Limit Skill [Cosmo Memory]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("All Creation")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Learn Limit Skill [All Creation]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Chaos")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Learn Limit Skill [Chaos]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Highwind")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Learn Limit Skill [Highwind]")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("1/35 soldier")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Shinra armored 'attack' soldiers: 12 in the Set!")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Super Sweeper")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("A new machine to protect the reactor!")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Masamune Blade")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("A prefect copy of Sephiroth's sword!")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Save Crystal")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Use This to create a SAVE Point in the 'North Cave'")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Combat Diary")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("A record of Master Dio's fiercest battles")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Autograph")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Dio's autograph")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Gambler")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Second part of Dio's diary: The Gold Saucer years")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Desert Rose")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Blooms once every 1000 years")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Earth Harp")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Calms the hearts of all who hear it")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Guide Book")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Map of another world. It Slumbers with sunken ships")), 1, QStringLiteral(":/items/item"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //nothing 106-127
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("DON'T USE")), QString(), 0, QString(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        //cloud weapons 128 -143
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Buster Sword")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Initial equiping")), 4, QStringLiteral(":/items/sword"),
            1, 2, 1, 0, 0, 0, 0, 0, 0, +2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mythril Saber")), QString(), 4, QStringLiteral(":/items/sword"),
            1, 3, 1, 0, 0, 0, 0, 0, 0, +4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Hardedge")), QString(), 4, QStringLiteral(":/items/sword"),
            1, 4, 1, 0, 0, 0, 0, 0, 0, +6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Butterfly Edge")), QString(), 4, QStringLiteral(":/items/sword"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Enhance Sword")), QString(), 4, QStringLiteral(":/items/sword"),
            1, 8, 4, 0, 0, 0, 0, 0, 0, +16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Organics")), QString(), 4, QStringLiteral(":/items/sword"),
            1, 6, 2, 0, 0, 0, 0, 0, 0, +15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Crystal Sword")), QString(), 4, QStringLiteral(":/items/sword"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Force Stealer")), QString(), 4, QStringLiteral(":/items/sword"),
            2, 3, 0, 0, 0, 0, 0, 0, 0, +7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Rune Blade")), QString(), 4, QStringLiteral(":/items/sword"),
            2, 4, 0, 0, 0, 0, 0, 0, 0, +9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Murasame")), QString(), 4, QStringLiteral(":/items/sword"),
            1, 5, 2, 0, 0, 0, 0, 0, 0, +12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Nail Bat")), QString(), 4, QStringLiteral(":/items/sword"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Yoshiyuki")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Sword is used when an ally is down")), 4, QStringLiteral(":/items/sword"),
            0, 2, 0, 0, 0, 0, 0, 0, 0, +9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Apocalypse")), QString(), 4, QStringLiteral(":/items/sword"),
            3, 3, 0, 0, 0, 0, 0, 0, 0, +43, +16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Heaven's Cloud")), QString(), 4, QStringLiteral(":/items/sword"),
            1, 6, 0, 0, 0, 0, 0, 0, 0, +31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Ragnarok")), QString(), 4, QStringLiteral(":/items/sword"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +43, +35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Ultima Weapon")), QString(), 4, QStringLiteral(":/items/sword"),
            0, 8, 4, 0, 0, 0, 0, 0, 0, +51, +24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //tifa's weapons 144-159/tifa's weapons 144-159
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Leather Glove")), QString(), 6, QStringLiteral(":/items/glove"),
            1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Metal Knuckle")), QString(), 6, QStringLiteral(":/items/glove"),
            1, 2, 1, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mythril Claw")), QString(), 6, QStringLiteral(":/items/glove"),
            1, 3, 1, 0, 0, 0, 0, 0, 0, +3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Grand Glove")), QString(), 6, QStringLiteral(":/items/glove"),
            1, 4, 1, 0, 0, 0, 0, 0, 0, +6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Tiger Fang")), QString(), 6, QStringLiteral(":/items/glove"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Diamond Knuckle")), QString(), 6, QStringLiteral(":/items/glove"),
            1, 5, 2, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Dragon Claw")), QString(), 6, QStringLiteral(":/items/glove"),
            1, 6, 2, 0, 0, 0, 0, 0, 0, +13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Crystal Glove")), QString(), 6, QStringLiteral(":/items/glove"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Motor Drive")), QString(), 6, QStringLiteral(":/items/glove"),
            2, 3, 0, 0, 0, 0, 0, 0, 0, +6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Platinum Fist")), QString(), 6, QStringLiteral(":/items/glove"),
            2, 4, 0, 0, 0, 0, 0, 0, 0, +7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Kaiser Knuckle")), QString(), 6, QStringLiteral(":/items/glove"),
            1, 8, 1, 0, 0, 0, 0, 0, 0, +13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Work Glove")), QString(), 6, QStringLiteral(":/items/glove"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Powersoul")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Power up when [Near death]")), 6, QStringLiteral(":/items/glove"),
            2, 4, 0, 0, 0, 0, 0, 0, 0, +7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Master Fist")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Power up when condition changes")), 6, QStringLiteral(":/items/glove"),
            1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("God's Hand")), QString(), 6, QStringLiteral(":/items/glove"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Premium Heart")), QString(), 6, QStringLiteral(":/items/glove"),
            0, 8, 4, 0, 0, 0, 0, 0, 0, +32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //barret's weapons 160-175
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Gatling Gun")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Initial equip. Long Range Weapon")), 5, QStringLiteral(":/items/gunarm"),
            1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Assault Gun")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 5, QStringLiteral(":/items/gunarm"),
            1, 2, 1, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Cannon Ball")), QString(), 5, QStringLiteral(":/items/gunarm"),
            1, 3, 1, 0, 0, 0, 0, 0, 0, +2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Atomic Scissors")), QString(), 5, QStringLiteral(":/items/gunarm"),
            1, 4, 1, 0, 0, 0, 0, 0, 0, +4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Heavy Vulcan")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 5, QStringLiteral(":/items/gunarm"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Chainsaw")), QString(), 5, QStringLiteral(":/items/gunarm"),
            1, 5, 2, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Microlaser")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 5, QStringLiteral(":/items/gunarm"),
            1, 6, 2, 0, 0, 0, 0, 0, 0, +13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("A M Cannon")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 5, QStringLiteral(":/items/gunarm"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("W Machine Gun")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 5, QStringLiteral(":/items/gunarm"),
            2, 3, 0, 0, 0, 0, 0, 0, 0, +3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Drill Arm")), QString(), 5, QStringLiteral(":/items/gunarm"),
            2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Solid Bazooka")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 5, QStringLiteral(":/items/gunarm"),
            1, 8, 4, 0, 0, 0, 0, 0, 0, +15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Rocket Punch")), QString(), 5, QStringLiteral(":/items/gunarm"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Enemy Launcher")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 5, QStringLiteral(":/items/gunarm"),
            1, 5, 1, 0, 0, 0, 0, 0, 0, +7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Pile Banger")), QString(), 5, QStringLiteral(":/items/gunarm"),
            0, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Max Ray")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 5, QStringLiteral(":/items/gunarm"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Missing Score")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 5, QStringLiteral(":/items/gunarm"),
            0, 8, 4, 0, 0, 0, 0, 0, 0, +49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //red's weapons 176-189
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mythril Clip")), QString(), 7, QStringLiteral(":/items/clip"),
            1, 3, 1, 0, 0, 0, 0, 0, 0, +6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Diamond Pin")), QString(), 7, QStringLiteral(":/items/clip"),
            1, 4, 1, 0, 0, 0, 0, 0, 0, +8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Silver Barrette")), QString(), 7, QStringLiteral(":/items/clip"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Gold Barrette")), QString(), 7, QStringLiteral(":/items/clip"),
            1, 5, 2, 0, 0, 0, 0, 0, 0, +13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Adaman Clip")), QString(), 7, QStringLiteral(":/items/clip"),
            1, 6, 2, 0, 0, 0, 0, 0, 0, +15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Crystal Comb")), QString(), 7, QStringLiteral(":/items/clip"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Magic Comb")), QString(), 7, QStringLiteral(":/items/clip"),
            2, 3, 0, 0, 0, 0, 0, 0, 0, +4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Plus Barrette")), QString(), 7, QStringLiteral(":/items/clip"),
            2, 4, 0, 0, 0, 0, 0, 0, 0, +12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Centclip")), QString(), 7, QStringLiteral(":/items/clip"),
            1, 8, 0, 0, 0, 0, 0, 0, 0, +22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Hairpin")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 7, QStringLiteral(":/items/clip"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, +15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Seraph Comb")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Memento of father")), 7, QStringLiteral(":/items/clip"),
            1, 4, 0, 0, 0, 0, 0, 0, 0, +14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Behemoth Horn")), QString(), 7, QStringLiteral(":/items/clip"),
            1, 6, 0, 0, 0, 0, +35, 0, 0, +26, +18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Spring Gun Clip")), QString(), 7, QStringLiteral(":/items/clip"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Limited Moon")), QString(), 7, QStringLiteral(":/items/clip"),
            0, 8, 4, 0, 0, 0, 0, 0, 0, +31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //aeris weapons 190-200
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Guard Stick")), QString(), 8, QStringLiteral(":/items/staff"),
            1, 1, 0, 0, 0, 0, +1, 0, 0, +2, +4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mythril Rod")), QString(), 8, QStringLiteral(":/items/staff"),
            1, 2, 1, 0, 0, 0, 0, 0, 0, +3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Full Metal Staff")), QString(), 8, QStringLiteral(":/items/staff"),
            1, 3, 1, 0, 0, 0, 0, 0, 0, +4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Striking Staff")), QString(), 8, QStringLiteral(":/items/staff"),
            1, 4, 1, 0, 0, 0, 0, 0, 0, +7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Prism Staff")), QString(), 8, QStringLiteral(":/items/staff"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Aurora Rod")), QString(), 8, QStringLiteral(":/items/staff"),
            1, 5, 2, 0, 0, 0, 0, 0, 0, +14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Wizard Staff")), QString(), 8, QStringLiteral(":/items/staff"),
            2, 3, 0, 0, 0, 0, 0, 0, 0, +6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Wizer Staff")), QString(), 8, QStringLiteral(":/items/staff"),
            2, 4, 0, 0, 0, 0, 0, 0, 0, +7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Fairy Tale")), QString(), 8, QStringLiteral(":/items/staff"),
            1, 7, 0, 0, 0, 0, 0, 0, 0, +8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Umbrella")), QString(), 8, QStringLiteral(":/items/staff"),
            0, 0, 0, 0, 0, 0, +20, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Princess Guard")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Raises Power when you need to protect others nearby")), 8, QStringLiteral(":/items/staff"),
            1, 7, 3, 0, 0, 0, +12, 0, 0, +22, +20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //cid weapons 201-214
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Spear")), QString(), 9, QStringLiteral(":/items/spear"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Slash Lance")), QString(), 9, QStringLiteral(":/items/spear"),
            1, 5, 2, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Trident")), QString(), 9, QStringLiteral(":/items/spear"),
            1, 6, 0, 0, 0, 0, 0, 0, 0, +12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mast Ax")), QString(), 9, QStringLiteral(":/items/spear"),
            1, 6, 2, 0, 0, 0, 0, 0, 0, +15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Partisan")), QString(), 9, QStringLiteral(":/items/spear"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Viper Halberd")), QString(), 9, QStringLiteral(":/items/spear"),
            2, 4, 0, 0, 0, 0, 0, 0, 0, +13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Javelin")), QString(), 9, QStringLiteral(":/items/spear"),
            2, 5, 2, 0, 0, 0, 0, 0, 0, +12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Grow Lance")), QString(), 9, QStringLiteral(":/items/spear"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mop")), QString(), 9, QStringLiteral(":/items/spear"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, +3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Dragoon Lance")), QString(), 9, QStringLiteral(":/items/spear"),
            1, 8, 0, 0, 0, 0, 0, 0, 0, +7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Scimitar")), QString(), 9, QStringLiteral(":/items/spear"),
            3, 2, 1, 0, 0, 0, 0, 0, 0, +20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Flayer")), QString(), 9, QStringLiteral(":/items/spear"),
            1, 6, 0, 0, 0, 0, 0, 0, 0, +20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Spirit Lance")), QString(), 9, QStringLiteral(":/items/spear"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +43, +20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Venus Gospel")), QString(), 9, QStringLiteral(":/items/spear"),
            0, 8, 4, 0, 0, 0, 0, 0, 0, +42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //yuffie weapons 215-228
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("4-point Shuriken")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            1, 3, 1, 0, 0, 0, 0, 0, 0, +6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Boomerang")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            1, 4, 1, 0, 0, 0, 0, 0, 0, +7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Pinwheel")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Razor Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            1, 5, 2, 0, 0, 0, 0, 0, 0, +12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Hawkeye")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            1, 6, 2, 0, 0, 0, 0, 0, 0, +14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Crystal Cross")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Wind Slash")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            2, 3, 0, 0, 0, 0, 0, 0, 0, +7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Twin Viper")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            2, 4, 0, 0, 0, 0, 0, 0, 0, +8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Spiral Shuriken")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            1, 8, 1, 0, 0, 0, 0, 0, 0, +18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Superball")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Magic Shuriken")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            1, 3, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Rising Sun")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            2, 4, 2, 0, 0, 0, 0, 0, 0, +16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Oritsuru")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            1, 8, 2, 0, 0, 0, 0, 0, 0, +38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Conformer")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 10, QStringLiteral(":/items/star"),
            0, 8, 4, 0, 0, 0, 0, 0, 0, +42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //cait sith weapons 229-241
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Yellow M-phone")), QString(), 11, QStringLiteral(":/items/mphone"),
            1, 4, 1, 0, 0, 0, 0, 0, 0, +8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Green M-phone")), QString(), 11, QStringLiteral(":/items/mphone"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Blue M-phone")), QString(), 11, QStringLiteral(":/items/mphone"),
            1, 5, 2, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Red M-phone")), QString(), 11, QStringLiteral(":/items/mphone"),
            1, 6, 2, 0, 0, 0, 0, 0, 0, +15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Crystal M-phone")), QString(), 11, QStringLiteral(":/items/mphone"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("White M-phone")), QString(), 11, QStringLiteral(":/items/mphone"),
            2, 3, 0, 0, 0, 0, 0, 0, 0, +8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Black M-phone")), QString(), 11, QStringLiteral(":/items/mphone"),
            2, 4, 0, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Silver M-phone")), QString(), 11, QStringLiteral(":/items/mphone"),
            1, 8, 0, 0, 0, 0, 0, 0, 0, +14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Trumpet Shell")), QString(), 11, QStringLiteral(":/items/mphone"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, +2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Gold M-phone")), QString(), 11, QStringLiteral(":/items/mphone"),
            1, 8, 4, 0, 0, 0, 0, 0, 0, +28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Battle Trumpet")), QString(), 11, QStringLiteral(":/items/mphone"),
            0, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Starlight Phone")), QString(), 11, QStringLiteral(":/items/mphone"),
            1, 8, 4, 0, 0, 0, +30, 0, 0, +31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("HP Shout")), QString(), 11, QStringLiteral(":/items/mphone"),
            0, 8, 4, 0, 0, 0, 0, 0, 0, +44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //vincent weapons... 242-254
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Quicksilver")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            1, 4, 1, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Shotgun")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Shortbarrel")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            1, 5, 2, 0, 0, 0, 0, 0, 0, +14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Lariat")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            1, 6, 2, 0, 0, 0, 0, 0, 0, +16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Winchester")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, +18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Peacemaker")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            2, 3, 1, 0, 0, 0, 0, 0, 0, +8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Buntline")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            2, 4, 2, 0, 0, 0, 0, 0, 0, +18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Long Barrel R")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            1, 8, 4, 0, 0, 0, 0, 0, 0, +14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Silver Rifle")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Sniper CR")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, +7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Supershot ST")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            0, 6, 3, 0, 0, 0, 0, 0, 0, +52, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Outsider")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            1, 8, 2, 0, 0, 0, 0, 0, 0, +48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Death Penalty")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Long Range Weapon")), 12, QStringLiteral(":/items/gun"),
            0, 8, 4, 0, 0, 0, 0, 0, 0, +34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //sepi weapon =255
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Masamune")), QString(), 0, QStringLiteral(":/items/item"),
            0, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //armor  256-287
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Bronze Bangle")), QString(), 2, QStringLiteral(":/items/armor"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Iron Bangle")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Titan Bangle")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mythril Armlet")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Carbon Bangle")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Silver Armlet")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Gold Armlet")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Diamond Bangle")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Crystal Bangle")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Platinum Bangle")), QString(), 2, QStringLiteral(":/items/armor"),
            2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Rune Armlet")), QString(), 2, QStringLiteral(":/items/armor"),
            2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Edincoat")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 7, 0, 0, 0, 0, 0, 0, 0, +5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Wizard Bracelet")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 8, 4, 0, 0, 0, 0, 0, 0, +20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Adaman Bangle")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Gigas Armlet")), QString(), 2, QStringLiteral(":/items/armor"),
            0, 5, 2, 0, 0, +30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Imperial Guard")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Aegis Armlet")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Fourth Bracelet")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 5, 2, 0, 0, 0, 0, 0, 0, +20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Warrior Bangle")), QString(), 2, QStringLiteral(":/items/armor"),
            0, 4, 2, 0, 0, +20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Shinra Beta")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Shinra Alpha")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Four Slots")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Fire Armlet")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Drains [Fire] attacks")), 2, QStringLiteral(":/items/armor"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Aurora Armlet")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Drains [Cold] attacks")), 2, QStringLiteral(":/items/armor"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Bolt Armlet")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Drains [Lightning] attacks")), 2, QStringLiteral(":/items/armor"),
            1, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Dragon Armlet")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Drains 1/2 [Fire/Cold/Lightning] attack")), 2, QStringLiteral(":/items/armor"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Minerva Band")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Women's Armlet nullifies [Fire/Cold/Gravity/Holy]")), 2, QStringLiteral(":/items/armor"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, 0, 0, 0, 0, -2, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Escort Guard")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Man's Armlet nullifies [Lightning/Earth/Water/Poison]")), 2, QStringLiteral(":/items/armor"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, 0, -2, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Mystile")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Ziedrich")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Decreases all elemental attacks by 1/2")), 2, QStringLiteral(":/items/armor"),
            0, 0, 0, 0, 0, +20, 0, 0, 0, +20, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Precious Watch")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("A gorgeous watch")), 2, QStringLiteral(":/items/armor"),
            1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Chocobracelet")), QString(), 2, QStringLiteral(":/items/armor"),
            1, 4, 0, 0, 0, 0, 0, +30, +20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        //accessorys 288-319
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Power Wrist")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Strength +10")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Protect Vest")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Vitality +10")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Earring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Magic +10")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Talisman")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Spirit +10")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Choco Feather")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Dexterity +10")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Amulet")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Luck +10")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, +10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Champion Belt")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Power & Vitality +30")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, +30, +30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Poison Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Drains [Poison] attacks, protects against [Poison]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Tough Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Vitality & Spirit +50")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, +50, 0, 0, 0, +50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Circlet")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Magic & Spirit +30")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, +30, +30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Star Pendant")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Protects against [Poison]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Silver Glasses")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Protects against [Darkness]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Headband")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Protects against [Sleep]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Fairy Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Protects against [Poison/Darkness]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Jem Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Protects against [Paralyze/Petrify/Slow-numb]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, -2, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("White Cape")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Protects against [Frog/Small]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Sprint Shoes")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Automatically put you in [Haste]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +2, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Peace Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Protects against [Berserk/Fury/Sadness]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, 0, 0, 0, -2, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Ribbon")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Protects against all abnormal status")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Fire Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Nullifies [Fire] attacks")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Ice Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Nullifies [Cold] attacks")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Bolt Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Nullifies [Lightning] attacks")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Tetra Elemental")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Drains [Fire/Cold/Lightning/Earth] attacks")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Safety Bit")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Protects against [Sudden Death/Petrify/Slow-numb]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Fury Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Automatically puts you in [Berserk]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Curse Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("It increases each status but...")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Protect Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Automatically sets up [Barrier/MBarrier]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +2, +2, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Cat's Bell")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Restores HP as you walk")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Reflect Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Automatically sets up [Reflect]")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, +2, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Water Ring")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Drains Water attacks")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("Sneak Glove")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Increases Stealing rate")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            QT_TRANSLATE_NOOP(_groupNames, QStringLiteral("HypnoCrown")), QT_TRANSLATE_NOOP(_groupDesc, QStringLiteral("Increases Manipulation rate")), 3, QStringLiteral(":/items/accessory"),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        }
    };
};
