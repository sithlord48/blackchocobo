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
#ifndef FF7ITEM_H
    #define FF7ITEM_H
#include <QObject>
#include <QImage>
#include <QIcon>

#include "icons/Item_Icons/accessory.xpm"
#include "icons/Item_Icons/armor.xpm"
#include "icons/Item_Icons/clip.xpm"
#include "icons/Item_Icons/glove.xpm"
#include "icons/Item_Icons/gun.xpm"
#include "icons/Item_Icons/gunarm.xpm"
#include "icons/Item_Icons/item.xpm"
#include "icons/Item_Icons/mphone.xpm"
#include "icons/Item_Icons/spear.xpm"
#include "icons/Item_Icons/staff.xpm"
#include "icons/Item_Icons/star.xpm"
#include "icons/Item_Icons/sword.xpm"

struct ITEM {
        QString name;
        QString desc;
        qint8 type; //0-unknown 1-item 2-armor 3-accessory 4-cloud 5-barret 6-tifa 7-red 8-aerith 9-cid 10-yuffie 11-cait 12-vincent
        QImage image;
        qint8 mgrowth;
        qint8 mslots;
        qint8 linked;
        qint8 hp;
        qint8 mp;
        qint8 str;
        qint8 vit;
        qint8 dex;
        qint8 lck;
        qint8 mag;
        qint8 spi;

        /* all Elements in FF7
           -3: Absorb
           -2: Nullify
           -1: Halve
            0: No Effect
           +1: damage
         */
        qint8 e_restoration;
        qint8 e_fire;
        qint8 e_cold;
        qint8 e_lightning;
        qint8 e_earth;
        qint8 e_wind;
        qint8 e_water;
        qint8 e_gravity;
        qint8 e_holy;
        qint8 e_poison;
        qint8 e_cut;
        qint8 e_shoot;
        qint8 e_punch;
        qint8 e_hit;

        /* all Status Effects in FF7
           -2: Protect
           -1: Remove
            0: No Effect
           +1: Infilict
           +2: Auto SelfCast
        */
        qint8 s_death;
        qint8 s_slow_numb;
        qint8 s_d_sentence;
        qint8 s_paralysis;
        qint8 s_petrify;
        qint8 s_silence;
        qint8 s_sleep;
        qint8 s_confusion;
        qint8 s_berserk;
        qint8 s_frog;
        qint8 s_mini;
        qint8 s_poison;
        qint8 s_fury;
        qint8 s_sadness;
        qint8 s_darkness;
        qint8 s_haste;
        qint8 s_slow;
        qint8 s_stop;
        qint8 s_barrier;
        qint8 s_m_barrier;
        qint8 s_reflect;
        qint8 s_sheild;
        qint8 s_regen;
        qint8 s_resist;
};
class FF7Item
{
  public:
    enum ItemType
    {
        Unknown,Item,Armor,Accessory,WeaponCloud,
        WeaponBarret,WeaponTifa,WeaponRed,WeaponAerith,WeaponCid,
        WeaponYuffie,WeaponCait,WeaponVincent};
    enum ItemElementalEffect
    {
        Absorb = -3,
        Nullify =-2,
        Halve =-1,
        NoEffect=0x00,
        Damage=0x01
    };
    enum ItemStatusEffect
    {
        Protect =-2,
        Remove=-1,
         //NoEffect=0, // declared above
        Infilict=0x01,
        SelfCast=0x02
    };
    enum ItemNames
    {
        Potion=0x00,HiPotion=0x01,XPotion=0x02,Ether=0x03,TurboEther=0x04,Elixir=0x05,Megalixir=0x06,PhoenixDown=0x07,Antidote=0x08,Soft=0x09,MaidensKiss=0x0A,Cornucopia=0x0B,Echoscreen=0x0C,Hyper=0x0D,Tranquilizer=0x0E,Remedy=0x0F,
        SmokeBomb=0x10,SpeedDrink=0x11,HeroDrink=0x12,Vaccine=0x13,Grenade=0x14,Shrapnel=0x15,RightArm=0x16,Hourglass=0x17,KissOfDeath=0x18,SpiderWeb=0x19,DreamPowder=0x1A,MuteMask=0x1B,WarGong=0x1C,Locoweed=0x1D,FireFang=0x1E,FireVeil=0x1F,
        AntarcticWind=0x20,IceCrystal=0x21,BoltPlume=0x22,SwiftBolt=0x23,EarthDrum=0x24,EarthMallet=0x25,DeadlyWaste=0x26,MTentacles=0x27,Stardust=0x28,VampireFang=0x29,GhostHand=0x2A,VagyriskClaw=0x2B,LightCurtain=0x2C,LunarCurtain=0x2D,Mirror=0x2E,HolyTorch=0x2F,
        BirdWing=0x30,DragonScales=0x31,Impaler=0x32,Shrivel=0x33,Eyedrop=0x34,Molotov=0x35,SMine=0x36,EightInchCannon=0x37,Graviball=0x38,TSBomb=0x39,Ink=0x3A,Dazers=0x3B,DragonFang=0x3C,Cauldron=0x3D,SylkisGreens=0x3E,ReaganGreens=0x3F,
        MimettGreens=0x40,CurielGreens=0x41,PahsanGreens=0x42,TantalGreens=0x43,KrakkaGreens=0x44,GysahlGreens=0x45,Tent=0x46,PowerSource=0x47,GuardSource=0x48,MagicSource=0x49,MindSource=0x4A,SpeedSource=0x4B,LuckSource=0x4C,ZeioNut=0x4D,CarobNut=0x4E,PorovNut=0x4F,
        PramNut=0x50,LasanNut=0x51,SaharaNut=0x52,LuchileNut=0x53,PepioNut=0x54,Battery=0x55,Tissue=0x56,Omnislash=0x57,Catastrophe=0x58,FinalHeaven=0x59,GreatGospel=0x5A,CosmoMemory=0x5B,AllCreation=0x5C,Chaos=0x5D,Highwind=0x5E,_135thSoldier=0x5F,
        SuperSweeper=0x60,MasamuneBlade=0x61,SaveCrystal=0x62,CombatDiary=0x63,Autograph=0x64,Gambler=0x65,DesertRose=0x66,EarthHarp=0x67,GuideBook=0x68,
        BusterSword=0x80,MythrilSaber=0x81,Hardedge=0x82,BytterflyEdge=0x83,EnhanceSword=0x84,Organics=0x85,CrystalSword=0x86,ForceStealer=0x87,RuneBlade=0x88,Murasame=0x89,NailBat=0x8A,Yoshiyuki=0x8B,Apocalypse=0x8C,HeavensCloud=0x8D,Ragnarok=0x8E,UltimaWeapon=0x8F,
        LeatherGlove=0x90,MetalKnuckle=0x91,MythrilClaw=0x92,GrandGlove=0x93,TigerFang=0x94,DiamondKnuckle=0x95,DragonClaw=0x96,CrystalGlove=0x97,MotorDrive=0x98,PlatinumFist=0x99,KaiserKnuckle=0x9A,WorkGlove=0x9B,Powersoul=0x9C,MasterFist=0x9D,GodsHand=0x9E,PremiumHeart=0x9F,
        GatlingGun=0xA0,AssaultGun=0xA1,CannonBall=0xA2,AtomicScissors=0xA3,HeavyVulcan=0xA4,Chainsaw=0xA5,Microlaser=0xA6,AMCannon=0xA7,WMachineGun=0xA8,DrillArm=0xA9,SolidBazooka=0xAA,RocketPunch=0xAB,EnemyLauncher=0xAC,PileBanger=0xAD,MaxRay=0xAE,MissingScore=0xAF,
        MythrilClip=0xB0,DiamondPin=0xB1,SilverBarette=0xB2,GoldBarette=0xB3,AdamanClip=0xB4,CrystalComb=0xB5,MagicComb=0xB6,PlusBarette=0xB7,Centclip=0xB8,Hairpin=0xB9,SeraphComb=0xBA,BehemothHorn=0xBB,SpringGunClip=0xBC,LimitedMoon=0xBD,
        GuardStick=0xBE,MythrilRod=0xBF,FullMetalStaff=0xC0,StrikingStaff=0xC1,PrismStaff=0xC2,AuroraRod=0xC3,WizardStaff=0xC4,WizerStaff=0xC5,FairyTale=0xC6,Umbrella=0xC7,PrincessGuard=0xC8,
        Spear=0xC9,SlashLance=0xCA,Trident=0xCB,MastAx=0xCC,Partisan=0xCD,ViperHalberd=0xCE,Javelin=0xCF,GrowLance=0xD0,Mop=0xD1,DragoonLance=0xD2,Scimitar=0xD3,Flayer=0xD4,SpiritLance=0xD5,VenusGospel=0xD6,
        FourPointShuriken=0xD7,Boomerang=0xD8,Pinwheel=0xD9,RazorRing=0xDA,Hawkeye=0xDB,CrystalCross=0xDC,WindSlash=0xDD,TwinViper=0xDE,SpiralShuriken=0xDF,Superball=0xE0,MagicShuriken=0xE1,RisingSun=0xE2,Oritsuru=0xE3,Conformer=0xE4,
        YellowMphone=0xE5,GreenMphone=0xE6,BlueMphone=0xE7,RedMphone=0xE8,CrystalMphone=0xE9,WhiteMphone=0xEA,BlackMphone=0xEB,SilverMphone=0xEC,TrumpetShell=0xED,GoldMphone=0xEE,BattleTrumpet=0xEF,StarlightPhone=0xF0,HpShout=0xF1,
        Quicksilver=0xF2,Shotgun=0xF3,Shortbarrel=0xF4,Lariat=0xF5,Winchester=0xF6,Peacemaker=0xF7,Buntline=0xF8,LongBarrelR=0xF9,SilverRifle=0xFA,SniperCR=0xFB,SupershotST=0xFC,Outsider=0xFD,DeathPenalty=0xFE,Masamune=0xFF,
        BronzeBangle=0x100,IronBangle=0x101,TitanBangle=0x102,MythrilArmlet=0x103,CarbonBangle=0x104,SilverArmlet=0x105,GoldArmlet=0x106,DiamondBangle=0x107,CrystalBangle=0x108,PlatinumBangle=0x109,RuneArmlet=0x10A,Edincoat=0x10B,WizardBracelet=0x10C,AdamanBangle=0x10D,GigasArmlet=0x10E,ImperialGuard=0x10F,
        AegisArmlet=0x110,FourthBracelet=0x111,WarriorBangle=0x112,ShinraBeta=0x113,ShinraAlpha=0x114,FourSlots=0x115,FireArmlet=0x116,AuroraArmlet=0x117,BoltArmlet=0x118,DragonArmlet=0x119,MinervaBand=0x11A,EscortGuard=0x11B,Mystile=0x11C,Ziedrich=0x11D,PreciousWatch=0x11E,Chocobracelet=0x11F,
        PowerWrist=0x120,ProtectVest=0x121,Earring=0x122,Talisman=0x123,ChocoFeather=0x124,Amulet=0x125,ChampionBelt=0x126,PoisonRing=0x127,ToughRing=0x128,Circlet=0x129, StarPendant=0x12A,SilverGlasses=0x12B,Headband=0x12C,FairyRing=0x12D,JemRing=0x12E,WhiteCape=0x12F,
        SprintShoes=0x130,PeaceRing=0x131,Ribbon=0x132,FireRing=0x133,IceRing=0x134,BoltRing=0x135,TetraElemental=0x136,SafetyBit=0x137,FuryRing=0x138,CurseRing=0x139,ProtectRing=0x13A,CatsBell=0x13B,ReflectRing=0x13C,WaterRing=0x13D,SneakGlove=0x13E,HypnoCrown=0x13F,
        EmptyItem=0x1FF,EmptyItemData=0xFFFF
    };
    quint16 itemDecode(quint16 itemraw);
    quint16 itemEncode(quint16 id,quint8 qty);
    quint16 itemId(quint16 item);
    quint8 itemQty(quint16 item);
    QString name(int);
    QString desc(int);
    qint8 type(int);
    //Image Functions
    QIcon icon(int);
    QImage image(int);
    QImage imageMateriaSlotNoGrowth(void);
    QImage imageMateriaSlot(void);
    QImage imageMateriaLink(void);
    //StyleSheet Equilvents (ONLY QButtons)
    QString styleMateriaSlotNoGrowth(void);
    QString styleMateriaSlot(void);
    //Style Sheet Only For QLabel
    QString styleMateriaLink(void);

    qint8 materiaSlots(int);
    qint8 linkedSlots(int);
    qint8 statHP(int);
    qint8 statMP(int);
    qint8 statSTR(int);
    qint8 statVIT(int);
    qint8 statDEX(int);
    qint8 statLCK(int);
    qint8 statMAG(int);
    qint8 statSPI(int);
    //don't forget to add nessessary items for growth rate and status/elements.
    qint8 materiaGrowthRate(int);
    //Elemental Functions
    qint8 elementRestoration(int);
    qint8 elementFire(int);
    qint8 elementCold(int);
    qint8 elementLightning(int);
    qint8 elementEarth(int);
    qint8 elementWind(int);
    qint8 elementWater(int);
    qint8 elementGravity(int);
    qint8 elementHoly(int);
    qint8 elementPoison(int);
    qint8 elementCut(int);
    qint8 elementShoot(int);
    qint8 elementPunch(int);
    qint8 elementHit(int);
    //Status Functions
    qint8 statusDeath(int);
    qint8 statusSlowNumb(int);
    qint8 statusDeathSentence(int);
    qint8 statusParalysis(int);
    qint8 statusPetrify(int);
    qint8 statusSilence(int);
    qint8 statusSleep(int);
    qint8 statusConfusion(int);
    qint8 statusBerserk(int);
    qint8 statusFrog(int);
    qint8 statusMini(int);
    qint8 statusPoison(int);
    qint8 statusFury(int);
    qint8 statusSadness(int);
    qint8 statusDarkness(int);
    qint8 statusHaste(int);
    qint8 statusSlow(int);
    qint8 statusStop(int);
    qint8 statusBarrier(int);
    qint8 statusMagicBarrier(int);
    qint8 statusReflect(int);
    qint8 statusShield(int);
    qint8 statusRegen(int);
    qint8 statusResist(int);
};
static ITEM Items[]=
{
    {QT_TRANSLATE_NOOP("Items","Potion"),QT_TRANSLATE_NOOP("Item_desc","Restores 100 HP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Hi-Potion"),QT_TRANSLATE_NOOP("Item_desc","Restores 500 HP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","X-Potion"),QT_TRANSLATE_NOOP("Item_desc","Restores all lost HP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Ether"),QT_TRANSLATE_NOOP("Item_desc","Restores 100 MP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Turbo Ether"),QT_TRANSLATE_NOOP("Item_desc","Restores all lost MP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Elixir"),QT_TRANSLATE_NOOP("Item_desc","Fully Restores HP/MP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Megalixir"),QT_TRANSLATE_NOOP("Item_desc","Fully Restores all Members HP/MP"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Phoenix Down"),QT_TRANSLATE_NOOP("Item_desc","Restores life"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Antidote"),QT_TRANSLATE_NOOP("Item_desc","Cures [Poison]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Soft"),QT_TRANSLATE_NOOP("Item_desc","Cures [Petrify]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Maiden's Kiss"),QT_TRANSLATE_NOOP("Item_desc","Cures [Frog]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Cornucopia"),QT_TRANSLATE_NOOP("Item_desc","Cures [Mini]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Echo Screen"),QT_TRANSLATE_NOOP("Item_desc","Cures [Silence]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Hyper"),QT_TRANSLATE_NOOP("Item_desc","Cures [Sadness]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,-1,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Tranquilizer"),QT_TRANSLATE_NOOP("Item_desc","Cures [Fury]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,+1,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Remedy"),QT_TRANSLATE_NOOP("Item_desc","Cures abnormal status"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Smoke Bomb"),QT_TRANSLATE_NOOP("Item_desc","Can escape from opponents during battle"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Speed Drink"),QT_TRANSLATE_NOOP("Item_desc","Casts [Haste] on one ally"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Hero Drink"),QT_TRANSLATE_NOOP("Item_desc","Raises ability once during battle"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Vaccine"),QT_TRANSLATE_NOOP("Item_desc","Protects against transformations"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {QT_TRANSLATE_NOOP("Items","Grenade"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Shrapnel"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Right arm"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Hourglass"),QT_TRANSLATE_NOOP("Item_desc","Stops all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Kiss of Death"),QT_TRANSLATE_NOOP("Item_desc","Uses [Death] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Spider Web"),QT_TRANSLATE_NOOP("Item_desc","Slows all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Dream Powder"),QT_TRANSLATE_NOOP("Item_desc","Uses [Sleepel] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Mute Mask"),QT_TRANSLATE_NOOP("Item_desc","Uses [Silence] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","War Gong"),QT_TRANSLATE_NOOP("Item_desc","Uses [Berserk] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Loco weed"),QT_TRANSLATE_NOOP("Item_desc","Uses [Confu] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Fire Fang"),QT_TRANSLATE_NOOP("Item_desc","Uses [Fire2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Fire Veil"),QT_TRANSLATE_NOOP("Item_desc","Uses [Fire3] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Antarctic Wind"),QT_TRANSLATE_NOOP("Item_desc","Uses [Ice2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Ice Crystal"),QT_TRANSLATE_NOOP("Item_desc","Uses [Ice3] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Bolt Plume"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bolt2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Swift Bolt"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bolt3] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Earth Drum"),QT_TRANSLATE_NOOP("Item_desc","Uses [Quake2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Earth Mallet"),QT_TRANSLATE_NOOP("Item_desc","Uses [Quake3] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Deadly Waste"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bio2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","M-Tentacles"),QT_TRANSLATE_NOOP("Item_desc","Uses [Bio3] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Stardust"),QT_TRANSLATE_NOOP("Item_desc","Uses [Comet2] on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Vampire Fang"),QT_TRANSLATE_NOOP("Item_desc","Drains HP out of one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Ghost Hand"),QT_TRANSLATE_NOOP("Item_desc","Drains MP out of one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Vagyrisk Claw"),QT_TRANSLATE_NOOP("Item_desc","Petrifies one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Light Curtain"),QT_TRANSLATE_NOOP("Item_desc","Creates [Barrier] around all allies"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Lunar Curtain"),QT_TRANSLATE_NOOP("Item_desc","Creates [MBarrier] around all allies"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Mirror"),QT_TRANSLATE_NOOP("Item_desc","Uses [Reflect] on all allies"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Holy Torch"),QT_TRANSLATE_NOOP("Item_desc","Uses [DeSpell] on all allies"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,0},
    {QT_TRANSLATE_NOOP("Items","Bird Wing"),QT_TRANSLATE_NOOP("Item_desc","Uses whirlwind on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Dragon Scales"),QT_TRANSLATE_NOOP("Item_desc","Water damage on all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Impaler"),QT_TRANSLATE_NOOP("Item_desc","Changes one opponent to a frog"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Shrivel"),QT_TRANSLATE_NOOP("Item_desc","Uses [Mini] on one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Eye drop"),QT_TRANSLATE_NOOP("Item_desc","Cures [Darkness]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Molotov"),QT_TRANSLATE_NOOP("Item_desc","Fire damage on one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","S-mine"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage on one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","8-inch Cannon"),QT_TRANSLATE_NOOP("Item_desc","Explosive damage against one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Graviball"),QT_TRANSLATE_NOOP("Item_desc","Uses [Demi] against one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","T/S Bomb"),QT_TRANSLATE_NOOP("Item_desc","Uses [Demi2] against one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Ink"),QT_TRANSLATE_NOOP("Item_desc","Uses [Darkness] against one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Dazers"),QT_TRANSLATE_NOOP("Item_desc","Paralyzes one opponent"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Dragon Fang"),QT_TRANSLATE_NOOP("Item_desc","Lightning damage against all opponents"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Cauldron"),QT_TRANSLATE_NOOP("Item_desc","Uses [Poison/Confu/Sleepel/Silence/Small/Frog]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,+1,+1,0,+1,+1,+1,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Sylkis Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Reagan Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Mimett Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Curiel Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Pahsana Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Tantal Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Krakka Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Gysahl Greens"),QT_TRANSLATE_NOOP("Item_desc","When you want a chocobo..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Tent"),QT_TRANSLATE_NOOP("Item_desc","Restores ally's max HP/MP. Use at Save Point."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Power Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Strength]"),1,QImage(item_xpm),
     0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Guard Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Vitality]"),1,QImage(item_xpm),
     0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Magic Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Magic Power]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Mind Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Spirit]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Speed Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Dexterity]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Luck Source"),QT_TRANSLATE_NOOP("Item_desc","Raises [Luck]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Zeio Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Carob Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Porov Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Pram Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Lasan Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Saraha Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Luchile Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Pepio Nut"),QT_TRANSLATE_NOOP("Item_desc","When you want to breed Chocobos..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Battery"),QT_TRANSLATE_NOOP("Item_desc","Looks like it can start some sort of machine"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Tissue"),QT_TRANSLATE_NOOP("Item_desc","This one's a little tough..."),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Omnislash"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Omnislash]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Catastrophe"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Catastrophe]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Final Heaven"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Final Heaven]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Great Gospel"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Great Gospel]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Cosmo Memory"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Cosmo Memory]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","All Creation"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [All Creation]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Chaos"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Chaos]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Highwind"),QT_TRANSLATE_NOOP("Item_desc","Learn Limit Skill [Highwind]"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","1/35 soldier"),QT_TRANSLATE_NOOP("Item_desc","Shinra armored 'attack' soldiers: 12 in the Set!"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Super Sweeper"),QT_TRANSLATE_NOOP("Item_desc","A new machine to protect the reactor!"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Masamune Blade"),QT_TRANSLATE_NOOP("Item_desc","A prefect copy of Sephiroth's sword!"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Save Crystal"),QT_TRANSLATE_NOOP("Item_desc","Use This to create a SAVE Point in the 'North Cave'"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Combat Diary"),QT_TRANSLATE_NOOP("Item_desc","A record of Master Dio's fiercest battles"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Autograph"),QT_TRANSLATE_NOOP("Item_desc","Dio's autograph"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Gambler"),QT_TRANSLATE_NOOP("Item_desc","Second part of Dio's diary: The Gold Saucer years"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Desert Rose"),QT_TRANSLATE_NOOP("Item_desc","Blooms once every 1000 years"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Earth Harp"),QT_TRANSLATE_NOOP("Item_desc","Calms the hearts of all who hear it"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","Guide Book"),QT_TRANSLATE_NOOP("Item_desc","Map of another world. It Slumbers with sunken ships"),1,QImage(item_xpm),
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  //nothing 106-127
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //cloud weapons 128 -143
   {QT_TRANSLATE_NOOP("Items","Buster Sword"),QT_TRANSLATE_NOOP("Item_desc","Initial equiping"),4,QImage(sword_xpm),
    1,2,1,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Saber"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    1,3,1,0,0,0,0,0,0,+4,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Hardedge"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    1,4,1,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Butterfly Edge"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    1,4,2,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Enhance Sword"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    1,8,4,0,0,0,0,0,0,+16,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Organics"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    1,6,2,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Sword"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    1,6,3,0,0,0,0,0,0,+19,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Force Stealer"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    2,3,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rune Blade"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    2,4,0,0,0,0,0,0,0,+9,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Murasame"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    1,5,2,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Nail Bat"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Yoshiyuki"),QT_TRANSLATE_NOOP("Item_desc","Sword is used when an ally is down"),4,QImage(sword_xpm),
    0,2,0,0,0,0,0,0,0,+9,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Apocalypse"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    3,3,0,0,0,0,0,0,0,+43,+16,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Heaven's Cloud"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    1,6,0,0,0,0,0,0,0,+31,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ragnarok"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    1,6,3,0,0,0,0,0,0,+43,+35,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ultima Weapon"),QT_TRANSLATE_NOOP("Item_desc",""),4,QImage(sword_xpm),
    0,8,4,0,0,0,0,0,0,+51,+24,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   ///tifa's weapons 144-159/tifa's weapons 144-159
   {QT_TRANSLATE_NOOP("Items","Leather Glove"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Metal Knuckle"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    1,2,1,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Claw"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    1,3,1,0,0,0,0,0,0,+3,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Grand Glove"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    1,4,1,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Tiger Fang"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    1,4,2,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Diamond Knuckle"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    1,5,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Dragon Claw"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    1,6,2,0,0,0,0,0,0,+13,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Glove"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    1,6,3,0,0,0,0,0,0,+16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Motor Drive"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    2,3,0,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Platinum Fist"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    2,4,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Kaiser Knuckle"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    1,8,1,0,0,0,0,0,0,+13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Work Glove"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Powersoul"),QT_TRANSLATE_NOOP("Item_desc","Power up when [Near death]"),6,QImage(glove_xpm),
    2,4,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Master Fist"),QT_TRANSLATE_NOOP("Item_desc","Power up when condition changes"),6,QImage(glove_xpm),
    1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","God's Hand"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    1,4,2,0,0,0,0,0,0,+34,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Premium Heart"),QT_TRANSLATE_NOOP("Item_desc",""),6,QImage(glove_xpm),
    0,8,4,0,0,0,0,0,0,+32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //barret's weapons 160-175
   {QT_TRANSLATE_NOOP("Items","Gatling Gun"),QT_TRANSLATE_NOOP("Item_desc","Initial equip. Long Range Weapon"),5,QImage(gunarm_xpm),
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Assault Gun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QImage(gunarm_xpm),
    1,2,1,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Cannon Ball"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(gunarm_xpm),
    1,3,1,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Atomic Scissors"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(gunarm_xpm),
    1,4,1,0,0,0,0,0,0,+4,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Heavy Vulcan"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QImage(gunarm_xpm),
    1,4,2,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Chainsaw"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(gunarm_xpm),
    1,5,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Microlaser"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QImage(gunarm_xpm),
    1,6,2,0,0,0,0,0,0,+13,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","A M Cannon"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QImage(gunarm_xpm),
    1,6,3,0,0,0,0,0,0,+16,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","W Machine Gun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QImage(gunarm_xpm),
    2,3,0,0,0,0,0,0,0,+3,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Drill Arm"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(gunarm_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Solid Bazooka"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QImage(gunarm_xpm),
    1,8,4,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rocket Punch"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(gunarm_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Enemy Launcher"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QImage(gunarm_xpm),
    1,5,1,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Pile Banger"),QT_TRANSLATE_NOOP("Item_desc",""),5,QImage(gunarm_xpm),
    0,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Max Ray"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QImage(gunarm_xpm),
    1,6,3,0,0,0,0,0,0,+30,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Missing Score"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),5,QImage(gunarm_xpm),
    0,8,4,0,0,0,0,0,0,+49,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //red's weapons 176-189
   {QT_TRANSLATE_NOOP("Items","Mythril Clip"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    1,3,1,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Diamond Pin"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    1,4,1,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Barette"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    1,4,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gold Barette"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    1,5,2,0,0,0,0,0,0,+13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Adaman Clip"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    1,6,2,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Comb"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    1,6,3,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Magic Comb"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    2,3,0,0,0,0,0,0,0,+4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Plus Barrette"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    2,4,0,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Centclip"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    1,8,0,0,0,0,0,0,0,+22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Hairpin"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),7,QImage(clip_xpm),
    0,0,0,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Seraph Comb"),QT_TRANSLATE_NOOP("Item_desc","Memento of father"),7,QImage(clip_xpm),
    1,4,0,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Behemoth Horn"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    1,6,0,0,0,0,+35,0,0,+26,+18,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Spring Gun Clip"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    1,6,3,0,0,0,0,0,0,+55,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Limited Moon"),QT_TRANSLATE_NOOP("Item_desc",""),7,QImage(clip_xpm),
    0,8,4,0,0,0,0,0,0,+31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //aeris weapons 190-200
   {QT_TRANSLATE_NOOP("Items","Guard Stick"),QT_TRANSLATE_NOOP("Item_desc",""),8,QImage(staff_xpm),
    1,1,0,0,0,0,+1,0,0,+2,+4,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Rod"),QT_TRANSLATE_NOOP("Item_desc",""),8,QImage(staff_xpm),
    1,2,1,0,0,0,0,0,0,+3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Full Metal Staff"),QT_TRANSLATE_NOOP("Item_desc",""),8,QImage(staff_xpm),
    1,3,1,0,0,0,0,0,0,+4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Striking Staff"),QT_TRANSLATE_NOOP("Item_desc",""),8,QImage(staff_xpm),
    1,4,1,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Prism Staff"),QT_TRANSLATE_NOOP("Item_desc",""),8,QImage(staff_xpm),
    1,4,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Aurora Rod"),QT_TRANSLATE_NOOP("Item_desc",""),8,QImage(staff_xpm),
    1,5,2,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wizard Staff"),QT_TRANSLATE_NOOP("Item_desc",""),8,QImage(staff_xpm),
    2,3,0,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wizer Staff"),QT_TRANSLATE_NOOP("Item_desc",""),8,QImage(staff_xpm),
    2,4,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fairy Tale"),QT_TRANSLATE_NOOP("Item_desc",""),8,QImage(staff_xpm),
    1,7,0,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Umbrella"),QT_TRANSLATE_NOOP("Item_desc",""),8,QImage(staff_xpm),
    0,0,0,0,0,0,+20,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Princess Guard"),QT_TRANSLATE_NOOP("Item_desc","Raises Power when you need to protect others nearby"),8,QImage(staff_xpm),
    1,7,3,0,0,0,+12,0,0,+22,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //cid weapons 201-214
   {QT_TRANSLATE_NOOP("Items","Spear"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    1,4,2,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Slash Lance"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    1,5,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Trident"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    1,6,0,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mast Ax"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    1,6,2,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Partisan"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    1,6,3,0,0,0,0,0,0,+17,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Viper Halberd"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    2,4,0,0,0,0,0,0,0,+13,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Javelin"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    2,5,2,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Grow Lance"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    1,6,3,0,0,0,0,0,0,+31,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mop"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    0,0,0,0,0,0,0,0,0,+3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Dragoon Lance"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    1,8,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Scimitar"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    3,2,1,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Flayer"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    1,6,0,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Spirit Lance"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    1,4,2,0,0,0,0,0,0,+43,+20,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Venus Gospel"),QT_TRANSLATE_NOOP("Item_desc",""),9,QImage(spear_xpm),
    0,8,4,0,0,0,0,0,0,+42,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //yuffie weapons 215-228
   {QT_TRANSLATE_NOOP("Items","4-point Shuriken"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    1,3,1,0,0,0,0,0,0,+6,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Boomerang"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    1,4,1,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Pinwheel"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    1,4,2,0,0,0,0,0,0,+9,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Razor Ring"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    1,5,2,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Hawkeye"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    1,6,2,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Cross"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    1,6,3,0,0,0,0,0,0,+18,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wind Slash"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    2,3,0,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Twin Viper"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    2,4,0,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Spiral Shuriken"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    1,8,1,0,0,0,0,0,0,+18,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Superball"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    0,0,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Magic Shuriken"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    1,3,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rising Sun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    2,4,2,0,0,0,0,0,0,+16,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Oritsuru"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    1,8,2,0,0,0,0,0,0,+38,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Conformer"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),10,QImage(star_xpm),
    0,8,4,0,0,0,0,0,0,+42,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //cait sith weapons 229-241
   {QT_TRANSLATE_NOOP("Items","Yellow M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    1,4,1,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Green M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    1,4,2,0,0,0,0,0,0,+9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Blue M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    1,5,2,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Red M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    1,6,2,0,0,0,0,0,0,+15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    1,6,3,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","White M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    2,3,0,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Black M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    2,4,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    1,8,0,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Trumpet Shell"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    0,0,0,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gold M-phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    1,8,4,0,0,0,0,0,0,+28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Battle Trumpet"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    0,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Starlight Phone"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    1,8,4,0,0,0,+30,0,0,+31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","HP Shout"),QT_TRANSLATE_NOOP("Item_desc",""),11,QImage(mphone_xpm),
    0,8,4,0,0,0,0,0,0,+44,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //vincent weapons... 242-254
   {QT_TRANSLATE_NOOP("Items","Quicksilver"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    1,4,1,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shotgun"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    1,4,2,0,0,0,0,0,0,+12,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shortbarrel"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    1,5,2,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Lariat"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    1,6,2,0,0,0,0,0,0,+16,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Winchester"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    1,6,3,0,0,0,0,0,0,+18,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Peacemaker"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    2,3,1,0,0,0,0,0,0,+8,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Buntline"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    2,4,2,0,0,0,0,0,0,+18,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Long Barrel R"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    1,8,4,0,0,0,0,0,0,+14,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Rifle"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Sniper CR"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    1,4,2,0,0,0,0,0,0,+7,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Supershot ST"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    0,6,3,0,0,0,0,0,0,+52,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Outsider"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    1,8,2,0,0,0,0,0,0,+48,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Death Penalty"),QT_TRANSLATE_NOOP("Item_desc","Long Range Weapon"),12,QImage(gun_xpm),
    0,8,4,0,0,0,0,0,0,+34,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //sepi weapon =255
   {QT_TRANSLATE_NOOP("Items","Masamune"),QT_TRANSLATE_NOOP("Item_desc",""),0,QImage(),0,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //armor  256-287
   {QT_TRANSLATE_NOOP("Items","Bronze Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Iron Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Titan Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mythril Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Carbon Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gold Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Diamond Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Crystal Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Platinum Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Rune Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Edincoat"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,7,0,0,0,0,0,0,0,+5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Wizard Bracelet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,8,4,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Adaman Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Gigas Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    0,5,2,0,0,+30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Imperial Guard"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Aegis Armlet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fourth Bracelet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,5,2,0,0,0,0,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Warrior Bangle"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    0,4,2,0,0,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shinra Beta"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Shinra Alpha"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Four Slots"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fire Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains [Fire] attacks"),2,QImage(armor_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Aurora Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains [Cold] attacks"),2,QImage(armor_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Bolt Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains [Lightning] attacks"),2,QImage(armor_xpm),
    1,4,2,0,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Dragon Armlet"),QT_TRANSLATE_NOOP("Item_desc","Drains 1/2 [Fire/Cold/Lightning] attack"),2,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Minerva Band"),QT_TRANSLATE_NOOP("Item_desc","Women's Armlet nullifies [Fire/Cold/Gravity/Holy]"),2,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,-2,-2,0,0,0,0,-2,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Escort Guard"),QT_TRANSLATE_NOOP("Item_desc","Man's Armlet nullifies [Lightning/Earth/Water/Poison]"),2,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,-2,-2,0,-2,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Mystile"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ziedrich"),QT_TRANSLATE_NOOP("Item_desc","Decreases all elemental attacks by 1/2"),2,QImage(armor_xpm),
    0,0,0,0,0,+20,0,0,0,+20,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Precious Watch"),QT_TRANSLATE_NOOP("Item_desc","A gorgeous watch"),2,QImage(armor_xpm),
    1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Chocobracelet"),QT_TRANSLATE_NOOP("Item_desc",""),2,QImage(armor_xpm),
    1,4,0,0,0,0,0,+30,+20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   //accessorys 288-319
   {QT_TRANSLATE_NOOP("Items","Power Wrist"),QT_TRANSLATE_NOOP("Item_desc","Strength +10"),3,QImage(accessory_xpm),
    0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Protect Vest"),QT_TRANSLATE_NOOP("Item_desc","Vitality +10"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Earring"),QT_TRANSLATE_NOOP("Item_desc","Magic +10"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Talisman"),QT_TRANSLATE_NOOP("Item_desc","Spirit +10"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Choco Feather"),QT_TRANSLATE_NOOP("Item_desc","Dexterity +10"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Amulet"),QT_TRANSLATE_NOOP("Item_desc","Luck +10"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,+10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Champion Belt"),QT_TRANSLATE_NOOP("Item_desc","Power & Vitality +30"),3,QImage(accessory_xpm),
    0,0,0,0,0,+30,+30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Poison Ring"),QT_TRANSLATE_NOOP("Item_desc","Drains [Poison] attacks, protects against [Poison]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Tough Ring"),QT_TRANSLATE_NOOP("Item_desc","Vitality & Spirit +50"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,+50,0,0,0,+50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Circlet"),QT_TRANSLATE_NOOP("Item_desc","Magic & Spirit +30"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,+30,+30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Star Pendant"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Poison]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Silver Glasses"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Darkness]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Headband"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Sleep]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fairy Ring"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Poison/Darkness]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,-2,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Jem Ring"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Paralyze/Petrify/Slow-numb]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,-2,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","White Cape"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Frog/Small]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Sprint Shoes"),QT_TRANSLATE_NOOP("Item_desc","Automatically put you in [Haste]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Peace Ring"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Berserk/Fury/Sadness]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,0,0,0,-2,-2,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ribbon"),QT_TRANSLATE_NOOP("Item_desc","Protects against all abnormal status"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fire Ring"),QT_TRANSLATE_NOOP("Item_desc","Nullifies [Fire] attacks"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Ice Ring"),QT_TRANSLATE_NOOP("Item_desc","Nullifies [Cold] attacks"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Bolt Ring"),QT_TRANSLATE_NOOP("Item_desc","Nullifies [Lightning] attacks"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Tetra Elemental"),QT_TRANSLATE_NOOP("Item_desc","Drains [Fire/Cold/Lightning/Earth] attacks"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,-3,-3,-3,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Safety Bit"),QT_TRANSLATE_NOOP("Item_desc","Protects against [Sudden Death/Petrify/Slow-numb]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-2,-2,-2,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Fury Ring"),QT_TRANSLATE_NOOP("Item_desc","Automatically puts you in [Berserk]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Curse Ring"),QT_TRANSLATE_NOOP("Item_desc","It increases each status but..."),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Protect Ring"),QT_TRANSLATE_NOOP("Item_desc","Automatically sets up [Barrier/MBarrier]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,+2,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Cat's Bell"),QT_TRANSLATE_NOOP("Item_desc","Restores HP as you walk"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Reflect Ring"),QT_TRANSLATE_NOOP("Item_desc","Automatically sets up [Reflect]"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,+2,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Water Ring"),QT_TRANSLATE_NOOP("Item_desc","Drains Water attacks"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","Sneak Glove"),QT_TRANSLATE_NOOP("Item_desc","Increases Stealing rate"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {QT_TRANSLATE_NOOP("Items","HypnoCrown"),QT_TRANSLATE_NOOP("Item_desc","Increases Manipulation rate"),3,QImage(accessory_xpm),
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
#endif //FF7Item
