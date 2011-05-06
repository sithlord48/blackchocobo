/****************************************************************************/
//    copyright 2010 Chris Rizzitello <sithlord48@gmail.com>                //
//                                                                          //
//    This file is part of Black Chocobo.                                   //
//                                                                          //
//    Black Chocobo is free software: you can redistribute it and/or modify //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    Black Chocobo is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#ifndef GLOBALS_H
#define GLOBALS_H
    #ifndef FF7SAVE_H
        #include "FF7SAVE.h"
    #endif

int ff7__checksum(void * qw );

void preptext (void);
void fix_pc_bytemask(void);

class ff7names
{
public:
QString ItemNames(int);
QString MateriaNames(int);
QString MateriaStats(int);
QString MateriaSkills(int,int);
};

static ITEM Items[]=
 {//ITEMS 0-105,
  {QObject::tr("Potion"),                ":/icon/item",0,0},
          {QObject::tr("Hi-Potion"),             ":/icon/item",0,0},
          {QObject::tr("X-Potion"),              ":/icon/item",0,0},
          {QObject::tr("Ether"),                 ":/icon/item",0,0},
          {QObject::tr("Turbo Ether"),           ":/icon/item",0,0},
          {QObject::tr("Elixir"),                ":/icon/item",0,0},
          {QObject::tr("Megalixir"),             ":/icon/item",0,0},
          {QObject::tr("Phoenix Down"),          ":/icon/item",0,0},
          {QObject::tr("Antidote"),              ":/icon/item",0,0},
          {QObject::tr("Soft"),                  ":/icon/item",0,0},
          {QObject::tr("Maiden's Kiss"),         ":/icon/item",0,0},
          {QObject::tr("Cornucopia"),            ":/icon/item",0,0},
          {QObject::tr("Echo screen"),           ":/icon/item",0,0},
          {QObject::tr("Hyper"),                 ":/icon/item",0,0},
          {QObject::tr("Tranquilizer"),          ":/icon/item",0,0},
          {QObject::tr("Remedy"),                ":/icon/item",0,0},
          {QObject::tr("Smoke Bomb"),            ":/icon/item",0,0},
          {QObject::tr("Speed Drink"),           ":/icon/item",0,0},
          {QObject::tr("Hero Drink"),            ":/icon/item",0,0},
          {QObject::tr("Vaccine"),               ":/icon/item",0,0},
          {QObject::tr("Grenade"),               ":/icon/item",0,0},
          {QObject::tr("Shrapnel"),              ":/icon/item",0,0},
          {QObject::tr("Right Arm"),             ":/icon/item",0,0},
          {QObject::tr("Hourglass"),             ":/icon/item",0,0},
          {QObject::tr("Kiss of Death"),         ":/icon/item",0,0},
          {QObject::tr("Spider Web"),            ":/icon/item",0,0},
          {QObject::tr("Dream Powder"),          ":/icon/item",0,0},
          {QObject::tr("Mute Mask"),             ":/icon/item",0,0},
          {QObject::tr("War Gong"),              ":/icon/item",0,0},
          {QObject::tr("Loco weed"),             ":/icon/item",0,0},
          {QObject::tr("Fire Fang"),             ":/icon/item",0,0},
          {QObject::tr("Fire Veil"),             ":/icon/item",0,0},
          {QObject::tr("Antarctic Wind"),        ":/icon/item",0,0},
          {QObject::tr("Ice Crystal"),           ":/icon/item",0,0},
          {QObject::tr("Bolt Plume"),            ":/icon/item",0,0},
          {QObject::tr("Swift Bolt"),            ":/icon/item",0,0},
          {QObject::tr("Earth Drum"),            ":/icon/item",0,0},
          {QObject::tr("Earth Mallet"),          ":/icon/item",0,0},
          {QObject::tr("Deadly Waste"),          ":/icon/item",0,0},
          {QObject::tr("M-Tentacles"),           ":/icon/item",0,0},
          {QObject::tr("Stardust"),              ":/icon/item",0,0},
          {QObject::tr("Vampire Fang"),          ":/icon/item",0,0},
          {QObject::tr("Ghost Hand"),            ":/icon/item",0,0},
          {QObject::tr("Vagyrisk Claw"),         ":/icon/item",0,0},
          {QObject::tr("Light Curtain"),         ":/icon/item",0,0},
          {QObject::tr("Lunar Curtain"),         ":/icon/item",0,0},
          {QObject::tr("Mirror"),                ":/icon/item",0,0},
          {QObject::tr("Holy Torch"),            ":/icon/item",0,0},
          {QObject::tr("Bird Wing"),             ":/icon/item",0,0},
          {QObject::tr("Dragon Scales"),         ":/icon/item",0,0},
          {QObject::tr("Impaler"),               ":/icon/item",0,0},
          {QObject::tr("Shrivel"),               ":/icon/item",0,0},
          {QObject::tr("Eye drop"),              ":/icon/item",0,0},
          {QObject::tr("Molotov"),               ":/icon/item",0,0},
          {QObject::tr("S-mine"),                ":/icon/item",0,0},
          {QObject::tr("8 Inch Cannon"),         ":/icon/item",0,0},
          {QObject::tr("Graviball"),             ":/icon/item",0,0},
          {QObject::tr("T/S Bomb"),              ":/icon/item",0,0},
          {QObject::tr("Ink"),                   ":/icon/item",0,0},
          {QObject::tr("Dazers"),                ":/icon/item",0,0},
          {QObject::tr("Dragon Fang"),           ":/icon/item",0,0},
          {QObject::tr("Cauldron"),              ":/icon/item",0,0},
          {QObject::tr("Sylkis Greens"),         ":/icon/item",0,0},
          {QObject::tr("Reagan Greens"),         ":/icon/item",0,0},
          {QObject::tr("Mimett Greens"),         ":/icon/item",0,0},
          {QObject::tr("Curiel Greens"),         ":/icon/item",0,0},
          {QObject::tr("Pahsana Greens"),        ":/icon/item",0,0},
          {QObject::tr("Tantal Greens"),         ":/icon/item",0,0},
          {QObject::tr("Krakka Greens"),         ":/icon/item",0,0},
          {QObject::tr("Gysahl Greens"),         ":/icon/item",0,0},
          {QObject::tr("Tent"),                  ":/icon/item",0,0},
          {QObject::tr("Power Source"),          ":/icon/item",0,0},
          {QObject::tr("Guard Source"),          ":/icon/item",0,0},
          {QObject::tr("Magic Source"),          ":/icon/item",0,0},
          {QObject::tr("Mind Source"),           ":/icon/item",0,0},
          {QObject::tr("Speed Source"),          ":/icon/item",0,0},
          {QObject::tr("Luck Source"),           ":/icon/item",0,0},
          {QObject::tr("Zeio Nut"),              ":/icon/item",0,0},
          {QObject::tr("Carob Nut"),             ":/icon/item",0,0},
          {QObject::tr("Porov Nut"),             ":/icon/item",0,0},
          {QObject::tr("Pram Nut"),              ":/icon/item",0,0},
          {QObject::tr("Lasan Nut"),             ":/icon/item",0,0},
          {QObject::tr("Sahara Nut"),            ":/icon/item",0,0},
          {QObject::tr("Luchile Nut"),           ":/icon/item",0,0},
          {QObject::tr("Pepio Nut"),             ":/icon/item",0,0},
          {QObject::tr("Battery"),               ":/icon/item",0,0},
          {QObject::tr("Tissue"),                ":/icon/item",0,0},
          {QObject::tr("Omnislash"),             ":/icon/item",0,0},
          {QObject::tr("Catastrophe"),           ":/icon/item",0,0},
          {QObject::tr("Final Heaven"),          ":/icon/item",0,0},
          {QObject::tr("Great Gospel"),          ":/icon/item",0,0},
          {QObject::tr("Cosmo Memory"),          ":/icon/item",0,0},
          {QObject::tr("All Creation"),          ":/icon/item",0,0},
          {QObject::tr("Chaos"),                 ":/icon/item",0,0},
          {QObject::tr("Highwind"),              ":/icon/item",0,0},
          {QObject::tr("1/35 Soldier"),          ":/icon/item",0,0},
          {QObject::tr("Super Sweeper"),         ":/icon/item",0,0},
          {QObject::tr("Masamune Blade"),        ":/icon/item",0,0},
          {QObject::tr("Save Crystal"),          ":/icon/item",0,0},
          {QObject::tr("Combat Diary"),          ":/icon/item",0,0},
          {QObject::tr("Autograph"),             ":/icon/item",0,0},
          {QObject::tr("Gambler"),               ":/icon/item",0,0},
          {QObject::tr("Desert Rose"),           ":/icon/item",0,0},
          {QObject::tr("Earth Harp"),            ":/icon/item",0,0},
          {QObject::tr("Guide Book"),            ":/icon/item",0,0},
  //nothing 106-127
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
          {QObject::tr("DON'T USE"),'\0',0,0},
  //cloud weapons 128 -143
          {QObject::tr("Buster Sword"),      ":/icon/cloud_weapon",2,1},
          {QObject::tr("Mythril Saber"),  	":/icon/cloud_weapon",3,1},
          {QObject::tr("Hardedge"),		":/icon/cloud_weapon",4,1},
          {QObject::tr("Butterfly Edge"), 	":/icon/cloud_weapon",4,2},
          {QObject::tr("Enhance Sword"),     ":/icon/cloud_weapon",8,4},
          {QObject::tr("Organics"),		":/icon/cloud_weapon",6,2},
          {QObject::tr("Crystal Sword"),     ":/icon/cloud_weapon",6,3},
          {QObject::tr("Force Stealer"),     ":/icon/cloud_weapon",3,0},
          {QObject::tr("Rune Blade"),      	":/icon/cloud_weapon",4,0},
          {QObject::tr("Murasame"),		":/icon/cloud_weapon",5,2},
          {QObject::tr("Nail Bat"),		":/icon/cloud_weapon",0,0},
          {QObject::tr("Yoshiyuki"),		":/icon/cloud_weapon",2,0},
          {QObject::tr("Apocalypse"),	":/icon/cloud_weapon",3,0},
          {QObject::tr("Heaven's Cloud"),   	":/icon/cloud_weapon",6,0},
          {QObject::tr("Ragnarok"),		":/icon/cloud_weapon",6,3},
          {QObject::tr("Ultima Weapon"),     ":/icon/cloud_weapon",8,4},
  //tifa's weapons 144-159
          {QObject::tr("Leather Glove"),     ":/icon/tifa_weapon",1,0},
          {QObject::tr("Metal Knuckle"),          ":/icon/tifa_weapon",2,1},
          {QObject::tr("Mythril Claw"),           ":/icon/tifa_weapon",3,1},
          {QObject::tr("Grand Glove"),		":/icon/tifa_weapon",4,1},
          {QObject::tr("Tiger Fang"),		":/icon/tifa_weapon",4,2},
          {QObject::tr("Diamond Knuckle"),	":/icon/tifa_weapon",5,2},
          {QObject::tr("Dragon Claw"),		":/icon/tifa_weapon",6,2},
          {QObject::tr("Crystal Glove"),          ":/icon/tifa_weapon",6,3},
          {QObject::tr("Motor Drive"),		":/icon/tifa_weapon",3,0},
          {QObject::tr("Platinum Fist"),          ":/icon/tifa_weapon",4,0},
          {QObject::tr("Kaiser Knuckle"),     	":/icon/tifa_weapon",8,1},
          {QObject::tr("Work Glove"),		":/icon/tifa_weapon",0,0},
          {QObject::tr("Powersoul"),		":/icon/tifa_weapon",4,0},
          {QObject::tr("Master Fist"),		":/icon/tifa_weapon",6,0},
          {QObject::tr("God's Hand"),		":/icon/tifa_weapon",4,2},
          {QObject::tr("Premium Heart"),          ":/icon/tifa_weapon",8,4},
  // barret's weapons 160-175
          {QObject::tr("Gatling Gun"),		":/icon/barret_weapon",1,0},
          {QObject::tr("Assault Gun"),		":/icon/barret_weapon",2,1},
          {QObject::tr("Cannon Ball"),		":/icon/barret_weapon",3,1},
          {QObject::tr("Atomic Scissors"),	":/icon/barret_weapon",4,2},
          {QObject::tr("Heavy Vulcan"),           ":/icon/barret_weapon",4,2},
          {QObject::tr("Chainsaw"),		":/icon/barret_weapon",5,2},
          {QObject::tr("Microlaser"),		":/icon/barret_weapon",6,2},
          {QObject::tr("A-M Cannon"),		":/icon/barret_weapon",6,3},
          {QObject::tr("W Machine Gun"),          ":/icon/barret_weapon",3,0},
          {QObject::tr("Drill Arm"),		":/icon/barret_weapon",4,0},
          {QObject::tr("Solid Bazooka"),          ":/icon/barret_weapon",8,4},
          {QObject::tr("Rocket Punch"),           ":/icon/barret_weapon",0,0},
          {QObject::tr("Enemy Launcher"),         ":/icon/barret_weapon",5,1},
          {QObject::tr("Pile Banger"),		":/icon/barret_weapon",6,3},
          {QObject::tr("Max Ray"),		":/icon/barret_weapon",6,3},
          {QObject::tr("Missing Score"),          ":/icon/barret_weapon",8,4},
  //red's weapons 176-189
          {QObject::tr("Mythril Clip"),           ":/icon/red_weapon",3,1},
          {QObject::tr("Diamond Pin"),		":/icon/red_weapon",4,1},
          {QObject::tr("Silver Barette"), 	":/icon/red_weapon",4,2},
          {QObject::tr("Gold Barette"),           ":/icon/red_weapon",5,2},
          {QObject::tr("Adaman Clip"),		":/icon/red_weapon",6,2},
          {QObject::tr("Crystal Comb"),           ":/icon/red_weapon",6,3},
          {QObject::tr("Magic Comb"),		":/icon/red_weapon",3,0},
          {QObject::tr("Plus Barette"),           ":/icon/red_weapon",4,0},
          {QObject::tr("Centclip"),		":/icon/red_weapon",8,0},
          {QObject::tr("Hairpin"),		":/icon/red_weapon",0,0},
          {QObject::tr("Seraph Comb"),		":/icon/red_weapon",4,0},
          {QObject::tr("Behemoth Horn"),          ":/icon/red_weapon",6,0},
          {QObject::tr("Spring Gun Clip"),	":/icon/red_weapon",6,3},
          {QObject::tr("Limited Moon"),           ":/icon/red_weapon",8,4},
  //aeris weapons 190-200
          {QObject::tr("Guard Stick"),		":/icon/aeris_weapon",2,1},
          {QObject::tr("Mythril Rod"),		":/icon/aeris_weapon",3,1},
          {QObject::tr("Full Metal Staff"),	":/icon/aeris_weapon",3,1},
          {QObject::tr("Striking Staff"),         ":/icon/aeris_weapon",4,1},
          {QObject::tr("Prism Staff"),		":/icon/aeris_weapon",4,2},
          {QObject::tr("Aurora Rod"),		":/icon/aeris_weapon",5,2},
          {QObject::tr("Wizard Staff"),           ":/icon/aeris_weapon",3,0},
          {QObject::tr("Wizer Staff"),		":/icon/aeris_weapon",4,0},
          {QObject::tr("Fairy Tale"),		":/icon/aeris_weapon",7,0},
          {QObject::tr("Umbrella"),		":/icon/aeris_weapon",0,0},
          {QObject::tr("Princess Guard"),         ":/icon/aeris_weapon",7,3},
  //cid weapons 201-214
          {QObject::tr("Spear"),                  ":/icon/cid_weapon",1,0},
          {QObject::tr("Slash Lance"),		":/icon/cid_weapon",5,2},
          {QObject::tr("Trident"),		":/icon/cid_weapon",6,0},
          {QObject::tr("Mast Ax"),		":/icon/cid_weapon",6,2},
          {QObject::tr("Partisan"),		":/icon/cid_weapon",6,3},
          {QObject::tr("Viper Halberd"),          ":/icon/cid_weapon",4,0},
          {QObject::tr("Javelin"),		":/icon/cid_weapon",5,2},
          {QObject::tr("Grow Lance"),		":/icon/cid_weapon",6,3},
          {QObject::tr("Mop"),			":/icon/cid_weapon",0,0},
          {QObject::tr("Dragoon Lance"),          ":/icon/cid_weapon",8,0},
          {QObject::tr("Scimitar"),		":/icon/cid_weapon",2,1},
          {QObject::tr("Flayer"),                 ":/icon/cid_weapon",6,0},
          {QObject::tr("Spirit Lance"),           ":/icon/cid_weapon",4,2},
          {QObject::tr("Venus Gospel"),           ":/icon/cid_weapon",8,4},
  //yuffie weapons 215-228
          {QObject::tr("4-point Shuriken"),	":/icon/yuffie_weapon",3,1},
          {QObject::tr("Boomerang"),		":/icon/yuffie_weapon",4,1},
          {QObject::tr("Pinwheel"),		":/icon/yuffie_weapon",4,2},
          {QObject::tr("Razor Ring"),		":/icon/yuffie_weapon",5,2},
          {QObject::tr("Hawkeye"),		":/icon/yuffie_weapon",6,2},
          {QObject::tr("Crystal Cross"),          ":/icon/yuffie_weapon",6,3},
          {QObject::tr("Wind Slash"),		":/icon/yuffie_weapon",3,0},
          {QObject::tr("Twin Viper"),		":/icon/yuffie_weapon",4,0},
          {QObject::tr("Spiral Shuriken"),	":/icon/yuffie_weapon",8,1},
          {QObject::tr("Superball"),		":/icon/yuffie_weapon",0,0},
          {QObject::tr("Magic Shuriken"),         ":/icon/yuffie_weapon",3,0},
          {QObject::tr("Rising Sun"),		":/icon/yuffie_weapon",4,2},
          {QObject::tr("Oritsuru"),		":/icon/yuffie_weapon",8,2},
          {QObject::tr("Conformer"),		":/icon/yuffie_weapon",8,4},
  //cait sith weapons 229-241
          {QObject::tr("Yellow M-phone"),         ":/icon/cait_weapon",4,2},
          {QObject::tr("Green M-phone"),          ":/icon/cait_weapon",4,2},
          {QObject::tr("Blue M-phone"),           ":/icon/cait_weapon",5,2},
          {QObject::tr("Red M-phone"),		":/icon/cait_weapon",6,2},
          {QObject::tr("Crystal M-phone"),	":/icon/cait_weapon",6,3},
          {QObject::tr("White M-phone"),          ":/icon/cait_weapon",3,0},
          {QObject::tr("Black M-phone"),          ":/icon/cait_weapon",4,0},
          {QObject::tr("Silver M-phone"),         ":/icon/cait_weapon",8,0},
          {QObject::tr("Trumpet Shell"),          ":/icon/cait_weapon",0,0},
          {QObject::tr("Gold M-phone"),           ":/icon/cait_weapon",8,4},
          {QObject::tr("Battle Trumpet"),         ":/icon/cait_weapon",6,3},
          {QObject::tr("Starlight Phone"),	":/icon/cait_weapon",8,4},
          {QObject::tr("HP Shout"),		":/icon/cait_weapon",8,4},
  //vincent weapons... 242-254
          {QObject::tr("Quicksilver"),		":/icon/vincent_weapon",4,1},
          {QObject::tr("Shotgun"),		":/icon/vincent_weapon",4,1},
          {QObject::tr("Shortbarrel"),		":/icon/vincent_weapon",5,2},
          {QObject::tr("Lariat"),               ":/icon/vincent_weapon",6,2},
          {QObject::tr("Winchester"),		":/icon/vincent_weapon",6,3},
          {QObject::tr("Peacemaker"),		":/icon/vincent_weapon",3,1},
          {QObject::tr("Buntline"),		":/icon/vincent_weapon",4,2},
          {QObject::tr("Long Barrel R"),        ":/icon/vincent_weapon",8,4},
          {QObject::tr("Silver Rifle"),         ":/icon/vincent_weapon",0,0},
          {QObject::tr("Sniper CR"),		":/icon/vincent_weapon",4,2},
          {QObject::tr("Supershot ST"),         ":/icon/vincent_weapon",6,3},
          {QObject::tr("Outsider"),		":/icon/vincent_weapon",8,2},
          {QObject::tr("Death Penalty"),        ":/icon/vincent_weapon",8,4},
  //sepi weapon =255
          {QObject::tr("Masamune"),		":/icon/item",0,0},
  //armor  256-287
          {QObject::tr("Bronze Bangle"),  	":/icon/armor",0,0},
          {QObject::tr("Iron Bangle"),		":/icon/armor",1,0},
          {QObject::tr("Titan Bangle"),           ":/icon/armor",2,0},
          {QObject::tr("Mythril Armlet"),         ":/icon/armor",2,1},
          {QObject::tr("Carbon Bangle"),          ":/icon/armor",3,1},
          {QObject::tr("Silver Armlet"),          ":/icon/armor",4,1},
          {QObject::tr("Gold Armlet"),		":/icon/armor",4,2},
          {QObject::tr("Diamond Bangle"),         ":/icon/armor",5,2},
          {QObject::tr("Crystal Bangle"),         ":/icon/armor",6,3},
          {QObject::tr("Platinum Bangle"),	":/icon/armor",2,0},
          {QObject::tr("Rune Armlet"),		":/icon/armor",4,0},
          {QObject::tr("Edincoat"),		":/icon/armor",7,0},
          {QObject::tr("Wizard Bracelet"),	":/icon/armor",8,4},
          {QObject::tr("Adaman Bangle"),          ":/icon/armor",2,1},
          {QObject::tr("Gigas Armlet"),           ":/icon/armor",5,2},
          {QObject::tr("Imperial Guard"),         ":/icon/armor",6,3},
          {QObject::tr("Aegis Armlet"),           ":/icon/armor",4,2},
          {QObject::tr("Fourth Bracelet"),	":/icon/armor",5,2},
          {QObject::tr("Warrior Bangle"),         ":/icon/armor",4,2},
          {QObject::tr("Shinra Beta"),		":/icon/armor",4,1},
          {QObject::tr("Shinra Alpha"),           ":/icon/armor",6,3},
          {QObject::tr("Four Slots"),		":/icon/armor",4,0},
          {QObject::tr("Fire Armlet"),		":/icon/armor",4,2},
          {QObject::tr("Aurora Armlet"),          ":/icon/armor",4,2},
          {QObject::tr("Bolt Armlet"),		":/icon/armor",4,2},
          {QObject::tr("Dragon Armlet"),          ":/icon/armor",6,3},
          {QObject::tr("Minerva Band"),           ":/icon/armor",6,3},
          {QObject::tr("Escort Guard"),           ":/icon/armor",6,3},
          {QObject::tr("Mystile"),		":/icon/armor",6,3},
          {QObject::tr("Ziedrich"),		":/icon/armor",0,0},
          {QObject::tr("Precious Watch"),         ":/icon/armor",8,0},
          {QObject::tr("Chocobracelet"),          ":/icon/armor",4,0},
  //accessorys 288-319
          {QObject::tr("Power Wrist"),            ":/icon/accessory",0,0},
          {QObject::tr("Protect Vest"),           ":/icon/accessory",0,0},
          {QObject::tr("Earring"),		":/icon/accessory",0,0},
          {QObject::tr("Talisman"),		":/icon/accessory",0,0},
          {QObject::tr("Choco Feather"),          ":/icon/accessory",0,0},
          {QObject::tr("Amulet"),                 ":/icon/accessory",0,0},
          {QObject::tr("Champion Belt"),          ":/icon/accessory",0,0},
          {QObject::tr("Poison Ring"),		":/icon/accessory",0,0},
          {QObject::tr("Tough Ring"),		":/icon/accessory",0,0},
          {QObject::tr("Circlet"),		":/icon/accessory",0,0},
          {QObject::tr("Star Pendant"),           ":/icon/accessory",0,0},
          {QObject::tr("Silver Glasses"),         ":/icon/accessory",0,0},
          {QObject::tr("Headband"),		":/icon/accessory",0,0},
          {QObject::tr("Fairy Ring"),		":/icon/accessory",0,0},
          {QObject::tr("Jem Ring"),		":/icon/accessory",0,0},
          {QObject::tr("White Cape"),		":/icon/accessory",0,0},
          {QObject::tr("Sprint Shoes"),           ":/icon/accessory",0,0},
          {QObject::tr("Peace Ring"),		":/icon/accessory",0,0},
          {QObject::tr("Ribbon"),                 ":/icon/accessory",0,0},
          {QObject::tr("Fire Ring"),		":/icon/accessory",0,0},
          {QObject::tr("Ice Ring"),		":/icon/accessory",0,0},
          {QObject::tr("Bolt Ring"),		":/icon/accessory",0,0},
          {QObject::tr("Tetra Elemental"),	":/icon/accessory",0,0},
          {QObject::tr("Safety Bit"),		":/icon/accessory",0,0},
          {QObject::tr("Fury Ring"),		":/icon/accessory",0,0},
          {QObject::tr("Curse Ring"),		":/icon/accessory",0,0},
          {QObject::tr("Protect Ring"),           ":/icon/accessory",0,0},
          {QObject::tr("Cat's Bell"),		":/icon/accessory",0,0},
          {QObject::tr("Reflect Ring"),           ":/icon/accessory",0,0},
          {QObject::tr("Water Ring"),		":/icon/accessory",0,0},
          {QObject::tr("Sneak Glove"),		":/icon/accessory",0,0},
          {QObject::tr("HypnoCrown"),		":/icon/accessory",0,0}
};

static MATERIA Materias[]=
{                                                            //ID   hp,mp,str,vit,dex,lck,mag,spi
    {QObject::tr("MP Plus"),		":/icon/independent", 0x00,/*{0,0,0,0,0,0,0,0}*/        QObject::tr("MP:+% depending on level")
   ,{QObject::tr("MP Plus +10%"),QObject::tr("MP Plus +20%"),QObject::tr("MP Plus +30%"),QObject::tr("MP Plus +40%"),QObject::tr("MP Plus +50%")},{10000,20000,30000,50000},3,5},

    {QObject::tr("HP Plus"),		":/icon/independent", 0x01,/*{0,0,0,0,0,0,0,0}*/        QObject::tr("HP:+% depending on level")
   ,{QObject::tr("HP Plus +10%"),QObject::tr("HP Plus +20%"),QObject::tr("HP Plus +30%"),QObject::tr("HP Plus +40%"),QObject::tr("HP Plus +50%")},{10000,20000,30000,50000},3,5},

    {QObject::tr("Speed Plus"),         ":/icon/independent", 0x02,/*{0,0,0,0,0,0,0,0}*/        QObject::tr("Dex:+% depending on level")
   ,{QObject::tr("Speed Plus +10%"),QObject::tr("Speed Plus +20%"),QObject::tr("Speed Plus +30%"),QObject::tr("Speed Plus +40%"),QObject::tr("Speed Plus +50%")},{15000,30000,60000,100000},3,5},

    {QObject::tr("Magic Plus"),         ":/icon/independent", 0x03,/*{0,0,0,0,0,0,0,0}*/        QObject::tr("Mag:+% depending on level")
   ,{QObject::tr("Magic Plus +10%"),QObject::tr("Magic Plus +20%"),QObject::tr("Magic Plus +30%"),QObject::tr("Magic Plus +40%"),QObject::tr("Magic Plus +50%")},{10000,20000,30000,50000},3,5},

    {QObject::tr("Luck Plus"),          ":/icon/independent", 0x04,/*{0,0,0,0,0,0,0,0}*/        QObject::tr("Lck:+% depending on level")
   ,{QObject::tr("Luck Plus +10%"),QObject::tr("Luck Plus +20%"),QObject::tr("Luck Plus +30%"),QObject::tr("Luck Plus +40%"),QObject::tr("Luck Plus +50%")},{15000,30000,60000,100000},3,5},

    {QObject::tr("EXP Plus"),		":/icon/independent", 0x05,/*{0,0,0,0,0,+1,0,0}*/       QObject::tr("Lck:+1")
   ,{QObject::tr("Exp Plus +50%"),QObject::tr("Exp Plus +100%"),QObject::tr("Mastered"),"",""},{60000,150000,0,0},3,3},

    {QObject::tr("Gil Plus"),		":/icon/independent", 0x06,/*{0,0,0,0,0,+1,0,0}*/       QObject::tr("Lck:+1")
   ,{QObject::tr("Gil Plus +50%"),QObject::tr("Gil Plus +100%"),QObject::tr("Mastered"),"",""},{80000,150000,0,0},3,3},

    {QObject::tr("Enemy Away"),         ":/icon/independent", 0x07,/*{0,0,0,0,0,+1,0,0}*/       QObject::tr("Lck:+1")
   ,{QObject::tr("Encounter Rate -50%"),QObject::tr("Encounter Rate -75%"),QObject::tr("Mastered"),"",""},{10000,50000,0,0},3,3},

    {QObject::tr("Enemy Lure"),         ":/icon/independent", 0x08,/*{0,0,0,0,0,-1,0,0}*/       QObject::tr("Lck:-1")
   ,{QObject::tr("Encounter Rate +50%"),QObject::tr("Encounter Rate +100%"),QObject::tr("Mastered"),"",""},{10000,50000,0,0},3,3},

    {QObject::tr("Chocobo Lure"),	":/icon/independent", 0x09,/*{0,0,0,0,0,+1,0,0}*/       QObject::tr("Lck:+1")
   ,{QObject::tr("Chocobo Lure"),QObject::tr("Chocobo Lure +50%"),QObject::tr("Chocobo Lure +100%"),QObject::tr("Chocobo Lure +200%"),QObject::tr("Mastered")},{3000,10000,30000,0},3,4},

   {QObject::tr("Pre-emptive"),        ":/icon/independent", 0x0A,/*{0,0,0,0,+2,0,0,0}*/       QObject::tr("Dex:+2")
  ,{QObject::tr("Pre-emptive +6%"),QObject::tr("Pre-emptive +12%"),QObject::tr("Pre-emptive +24%"),QObject::tr("Pre-emptive +36%"),QObject::tr("Pre-emptive +48%")},{8000,20000,40000,80000},3,5},

    {QObject::tr("Long Range"),         ":/icon/independent", 0x0B,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Long Range"),QObject::tr("Mastered"),"","",""},{80000,0,0,0},3,2},

    {QObject::tr("Mega All"),		":/icon/independent", 0x0C,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Mega-all x1"),QObject::tr("Mega-all x2"),QObject::tr("Mega-all x3"),QObject::tr("Mega-all x4"),QObject::tr("Mega-all x5")},{20000,40000,80000,160000},3,5},

    {QObject::tr("Counter Attack"),     ":/icon/independent", 0x0D,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Counter Attack 20%"),QObject::tr("Counter Attack 40%"),QObject::tr("Counter Attack 60%"),QObject::tr("Counter Attack 80%"),QObject::tr("Counter Attack 100%")},{10000,20000,50000,100000},3,5},

    {QObject::tr("Slash-All"),          ":/icon/command",     0x0E,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Slash-All"),QObject::tr("Flash"),QObject::tr("Mastered"),"",""},{130000,150000,0,0},5,3},

    {QObject::tr("Double Cut"),         ":/icon/command",     0x0F,/*{0,0,0,0,+2,0,0,0}*/       QObject::tr("Dex:+2")
   ,{QObject::tr("2x-Cut"),QObject::tr("4x-Cut"),QObject::tr("Mastered"),"",""},{100000,150000,0,0},5,3},

    {QObject::tr("Cover"),		":/icon/independent", 0x10,/*{0,0,0,+1,0,0,0,0}*/       QObject::tr("Vit:+1")
   ,{QObject::tr("Cover +20%"),QObject::tr("Cover +40%"),QObject::tr("Cover +60%"),QObject::tr("Cover +80%"),QObject::tr("Cover +100%")},{2000,10000,25000,40000},3,5},

    {QObject::tr("Underwater"),         ":/icon/independent", 0x11,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Underwater"),"","","",""},{0,0,0,0},3,1},

    {QObject::tr("HP <-> MP"),          ":/icon/independent", 0x12,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("HP <-> MP"),QObject::tr("Mastered"),"","",""},{80000,0,0,0},3,2},

    {QObject::tr("W-Magic"),		":/icon/command",     0x13,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("W-Magic"),QObject::tr("Mastered"),"","",""},{250000,0,0,0},5,2},

    {QObject::tr("W-Summon"),		":/icon/command",     0x14,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("W-Summon"),QObject::tr("Mastered"),"","",""},{250000,0,0,0},5,2},

    {QObject::tr("W-Item"),		":/icon/command",     0x15,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("W-Item"),QObject::tr("Mastered"),"","",""},{250000,0,0,0},5,2},

    {"DON'T USE",                       "",                   0X16,/*{0,0,0,0,0,0,0,0}*/        "ID:0x16"
   ,{"?","?","?","?","?"},{0,0,0,0},0,0},

    {QObject::tr("All"),                ":/icon/support",     0x17,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("All x1"),QObject::tr("All x2"),QObject::tr("All x3"),QObject::tr("All x4"),QObject::tr("All x5")},{1500,6000,18000,35000},4,5},

    {QObject::tr("Counter"),		":/icon/support",     0x18,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Counter Rate %20"),QObject::tr("Counter Rate %40"),QObject::tr("Counter Rate %60"),QObject::tr("Counter Rate %80"),QObject::tr("Counter Rate %100")},{20000,40000,60000,100000},4,5},

    {QObject::tr("Magic Counter"),	":/icon/support",     0x19,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Magic Counter Rate %30"),QObject::tr("Magic Counter Rate %40"),QObject::tr("Magic Counter Rate %60"),QObject::tr("Magic Counter Rate %80"),QObject::tr("Magic Counter Rate %100")},{20000,40000,80000,300000},4,5},

    {QObject::tr("MP Turbo"),		":/icon/support",     0x1A,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("MP Turbo 10%"),QObject::tr("Mp Turbo 20%"),QObject::tr("Mp Turbo 30%"),QObject::tr("Mp Turbo 40%"),QObject::tr("Mp Turbo 50%")},{10000,30000,60000,120000},4,5},

    {QObject::tr("MP Absorb"),          ":/icon/support",     0x1B,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("MP Absorb"),QObject::tr("Mastered"),"","",""},{100000,0,0,0},4,2},

    {QObject::tr("HP Absorb"),          ":/icon/support",     0x1C,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("HP Absorb"),QObject::tr("Mastered"),"","",""},{100000,0,0,0},4,2},

    {QObject::tr("Elemental"),          ":/icon/support",     0x1D,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Elemental 50%"),QObject::tr("Elemental 100%"),QObject::tr("Elemental 200%"),QObject::tr("Mastered"),""},{10000,40000,80000,0},4,4},

    {QObject::tr("Added Effect"),	":/icon/support",     0x1E,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Added Effect"),QObject::tr("Mastered"),"","",""},{100000,0,0,0},4,2},

    {QObject::tr("Sneak Attack"),	":/icon/support",     0x1F,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Sneak Attack 20%"),QObject::tr("Sneak Attack 35%"),QObject::tr("Sneak Attack 50%"),QObject::tr("Sneak Attack 65%"),QObject::tr("Sneak Attack 80%")},{20000,60000,100000,150000},4,5},

    {QObject::tr("Final Attack"),	":/icon/support",     0x20,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Final Attack x1"),QObject::tr("Final Attack x2"),QObject::tr("Final Attack x3"),QObject::tr("Final Attack x4"),QObject::tr("Final Attack x5")},{20000,40000,80000,160000},4,5},

    {QObject::tr("Added Cut"),          ":/icon/support",     0x21,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Added Cut"),QObject::tr("Mastered"),"","",""},{200000,0,0,0},4,2},

    {QObject::tr("Steal-As-Well"),	":/icon/support",     0x22,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Steal-As-Well"),QObject::tr("Mastered"),"","",""},{200000,0,0,0},4,2},

    {QObject::tr("Quadra Magic"),	":/icon/support",     0x23,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Quadra Magic x1"),QObject::tr("Quadra Magic x2"),QObject::tr("Quadra Magic x3"),QObject::tr("Quadra Magic x4"),QObject::tr("Quadra Magic x5")},{40000,80000,120000,200000},4,5},

    {QObject::tr("Steal"),		":/icon/command",     0x24,/*{0,0,0,0,+2,0,0,0}*/       QObject::tr("Dex:+2")
   ,{QObject::tr("Steal"),QObject::tr("Mug"),QObject::tr("Mastered"),"",""},{40000,50000,0,0},5,3},

    {QObject::tr("Sense"),		":/icon/command",     0x25,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Sence"),QObject::tr("Mastered"),"","",""},{40000,0,0,0},5,2},

    {"DON'T USE",                       "" ,                  0X26,/*{0,0,0,0,0,0,0,0}*/        "ID:0x26"
   ,{"?","?","?","?","?"},{0,0,0,0},0,0},

    {QObject::tr("Throw"),		":/icon/command",     0x27,/*{0,0,0,+1,0,0,0,0}*/       QObject::tr("Vit:+1")
   ,{QObject::tr("Throw"),QObject::tr("Coin"),QObject::tr("Mastered"),"",""},{45000,60000,0,0},5,3},

    {QObject::tr("Morph"),		":/icon/command",     0x28,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Morph"),QObject::tr("Mastered"),"","",""},{100000,0,0,0},5,2},

    {QObject::tr("DeathBlow"),  	":/icon/command",     0x29,/*{0,0,0,0,0,+1,0,0}*/       QObject::tr("Lck:+1")
   ,{QObject::tr("DeathBlow"),QObject::tr("Mastered"),"","",""},{40000,0,0,0},5,2},

    {QObject::tr("Manipulate"),         ":/icon/command",     0x2A,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Manipulate"),QObject::tr("Mastered"),"","",""},{40000,0,0,0},5,2},

    {QObject::tr("Mime"),		":/icon/command",     0x2B,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Mime"),QObject::tr("Mastered"),"","",""},{100000,0,0,0},5,2},

    {QObject::tr("Enemy Skill"),        ":/icon/command",     0x2C,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Enemy Skill"),"","","",""},{0,0,0,0},5,1},

    {"DON'T USE",                       "",                   0X2D,/*{0,0,0,0,0,0,0,0}*/        "ID:0x2D"
   ,{"?","?","?","?","?"},{0,0,0,0},0,0},

    {"DON'T USE",                       "",                   0X2E,/*{0,0,0,0,0,0,0,0}*/        "ID:0x2E"
   ,{"?","?","?","?","?"},{0,0,0,0},0,0},

    {"DON'T USE",                       "",                   0X2F,/*{0,0,0,0,0,0,0,0}*/        "ID:0x2F"
   ,{"?","?","?","?","?"},{0,0,0,0},0,0},

    {QObject::tr("Master Command"),     ":/icon/command",     0x30,/*{0,0,0,0,0,0,0,0}*/        ""
   ,{QObject::tr("Master Command"),"","","",""},{0,0,0,0},5,1},

    {QObject::tr("Fire"),		":/icon/magic",       0x31,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Fire (4mp)"),QObject::tr("Fire2 (22mp)"),QObject::tr("Fire3 (52mp)"),QObject::tr("Mastered"),""},{2000,18000,35000,0},1,4},

    {QObject::tr("Ice"),                ":/icon/magic",       0x32,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Ice (4mp)"),QObject::tr("Ice2 (22mp)"),QObject::tr("Ice3 (52mp)"),QObject::tr("Mastered"),""},{2000,18000,35000,0},1,4},

    {QObject::tr("Earth"),		":/icon/magic",       0x33,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Quake (6mp)"),QObject::tr("Quake2 (28mp)"),QObject::tr("Quake3 (68mp)"),QObject::tr("Mastered"),""},{6000,22000,40000,0},1,4},

    {QObject::tr("Lightning"),          ":/icon/magic",       0x34,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Bolt (4mp)"),QObject::tr("Bolt2 (22mp)"),QObject::tr("Bolt3(52mp)"),QObject::tr("Mastered"),""},{2000,18000,35000,0},1,4},

    {QObject::tr("Restore"),		":/icon/magic",       0x35,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Cure (5mp)"),QObject::tr("Cure2 (24mp)"),QObject::tr("Regen(30mp)"),QObject::tr("Cure3 (64mp)"),QObject::tr("Mastered")},{2500,17000,25000,40000},1,5},

    {QObject::tr("Heal"),		":/icon/magic",       0x36,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Poisona (3mp)"),QObject::tr("Esuna (15mp)"),QObject::tr("Resist (120mp)"),QObject::tr("Mastered"),""},{12000,52000,60000,0},1,4},

    {QObject::tr("Revive"),		":/icon/magic",       0x37,/*{-5,+5,-2,-1,0,0,+2,+1}*/  QObject::tr("HP:-5% MP:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1")
   ,{QObject::tr("Life (34mp)"),QObject::tr("Life2 (100mp)"),QObject::tr("Mastered"),"",""},{45000,55000,0,0},1,3},

    {QObject::tr("Seal"),		":/icon/magic",       0x38,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Sleepel (8mp)"),QObject::tr("Silence (24mp)"),QObject::tr("Mastered"),"",""},{10000,20000,0,0},1,3},

    {QObject::tr("Mystify"),		":/icon/magic",       0x39,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Confuse (18mp)"),QObject::tr("Berserk (24mp)"),QObject::tr("Mastered"),"",""},{12000,25000,0,0},1,3},

    {QObject::tr("Transform"),          ":/icon/magic",       0x3A,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Mini (10mp)"),QObject::tr("Toad (14mp)"),QObject::tr("Mastered"),"",""},{8000,24000,0,0},1,3},

    {QObject::tr("Exit"),		":/icon/magic",       0x3B,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Exit (16mp)"),QObject::tr("Remove (99mp)"),QObject::tr("Mastered"),"",""},{10000,30000,0,0},1,3},

    {QObject::tr("Poison"),		":/icon/magic",       0x3C,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Bio (8mp)"),QObject::tr("Bio2 (36mp)"),QObject::tr("Bio3 (80mp)"),QObject::tr("Mastered"),""},{5000,20000,38000,0},1,4},

    {QObject::tr("Demi"),		":/icon/magic",       0x3D,/*{-2,+2,-1,0,0,0,+1,0}*/    QObject::tr("HP:-2% MP:+2% Str:-1 Mag:+1")
   ,{QObject::tr("Demi (14mp)"),QObject::tr("Demi2 (33mp)"),QObject::tr("Demi3 (48mp)"),QObject::tr("Mastered"),""},{10000,20000,40000,0},1,4},

    {QObject::tr("Barrier"),		":/icon/magic",       0x3E,/*{-5,+5,-2,-1,0,0,+2,+1}*/  QObject::tr("HP:-5% MP:+5% Str:-2 Vit -1 Mag:+2 Spi:+1")
   ,{QObject::tr("Barrier (16mp)"),QObject::tr("Magic Barrier (24mp)"),QObject::tr("Reflect (30mp)"),QObject::tr("Wall (58mp)"),QObject::tr("Mastered")},{5000,15000,30000,45000},1,5},

    {"DON'T USE",                       "",                   0X3F,/*{0,0,0,0,0,0,0,0}*/"ID:0x3F",{"?","?","?","?","?"},{0,0,0,0},0,0},

    {QObject::tr("Comet"),              ":/icon/magic",       0x40,/*{-5,+5,-2,-1,0,0,+2,+1}*/  QObject::tr("HP:-5% MP:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1")
   ,{QObject::tr("Comet (70mp)"),QObject::tr("Comet2 (110mp)"),QObject::tr("Mastered"),"",""},{12000,60000,0,0},1,3},

    {QObject::tr("Time"),		":/icon/magic",       0x41,/*{-5,+5,-2,-1,0,0,+2,+1}*/  QObject::tr("HP:-5% MP:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1")
   ,{QObject::tr("Haste (18mp)"),QObject::tr("Slow (20mp)"),QObject::tr("Stop (34mp)"),QObject::tr("Mastered"),""},{10000,20000,42000,0},1,4},

    {"DON'T USE",                       "",                   0X42,/*{0,0,0,0,0,0,0,0}*/"ID:0x42"
   ,{"?","?","?","?","?"},{0,0,0,0},0,0},

    {"DON'T USE",                       "",                   0X43,/*{0,0,0,0,0,0,0,0}*/"ID:0x43"
   ,{"?","?","?","?","?"},{0,0,0,0},0,0},

    {QObject::tr("Destruct"),		":/icon/magic",       0x44,/*{-5,+5,-2,-1,0,0,+2,+1}*/  QObject::tr("HP:-5% MP:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1")
   ,{QObject::tr("DeBarrier (12mp)"),QObject::tr("DeSpell (20mp)"),QObject::tr("Death (30mp)"),QObject::tr("Mastered"),""},{6000,10000,45000,0},1,4},

    {QObject::tr("Contain"),		":/icon/magic",       0x45,/*{-10,+10,-4,-2,0,0,+4,+2}*/    QObject::tr("HP:-10% MP:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2")
   ,{QObject::tr("Freeze (82mp)"),QObject::tr("Break (86mp)"),QObject::tr("Tornado (90mp)"),QObject::tr("Flare(100mp)"),QObject::tr("Mastered")},{5000,10000,15000,60000},1,5},

    {QObject::tr("FullCure"),		":/icon/magic",       0x46,/*{-10,+10,-4,-2,0,0,+4,+2}*/    QObject::tr("HP:-10% MP:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2")
   ,{"",QObject::tr("Full Cure (99mp)"),QObject::tr("Mastered"),"",""},{3000,100000,0,0},1,3},

    {QObject::tr("Shield"),		":/icon/magic",       0x47,/*{-10,+10,-4,-2,0,0,+4,+2}*/    QObject::tr("HP:-10% MP:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2")
   ,{"",QObject::tr("Shield (180mp)"),QObject::tr("Mastered"),"",""},{10000,100000,0,0},1,3},

    {QObject::tr("Ultima"),             ":/icon/magic",       0x48,/*{-10,+10,-4,-2,0,0,+4,+2}*/    QObject::tr("HP:-10% MP:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2")
   ,{"",QObject::tr("Ultima (130mp)"),QObject::tr("Mastered"),"",""},{5000,100000,0,0},1,3},

    {QObject::tr("Master Magic"),	":/icon/magic",       0x49,/*{0,0,0,0,0,0,0,0}*/            ""
   ,{QObject::tr("Master Magic"),"","","",""},{0,0,0,0},1,1},

    {QObject::tr("Choco/Mog"),  	":/icon/summon",      0x4A,/*{-2,+2,0,0,0,0,+1,0}*/         QObject::tr("HP:-2% MP:+2% Mag:+1")
   ,{QObject::tr("Summon Choco/Mog x1 (14mp)"),QObject::tr("Summon Choco/Mog x2 (14mp)"),QObject::tr("Summon Choco/Mog x3 (14mp)"),QObject::tr("Summon Choco/Mog x4 (14mp)"),QObject::tr("Summon Choco/Mog x5 (14mp)")},{2000,14000,25000,35000},2,5},

    {QObject::tr("Shiva"),		":/icon/summon",      0x4B,/*{-2,+2,0,0,0,0,+1,0}*/         QObject::tr("HP:-2% MP:+2% Mag:+1")
   ,{QObject::tr("Summon Shiva x1 (34mp)"),QObject::tr("Summon Shiva x2 (34mp)"),QObject::tr("Summon Shiva x3 (34mp)"),QObject::tr("Summon Shiva x4 (34mp)"),QObject::tr("Summon Shiva x5 (34mp)")},{4000,15000,30000,50000},2,5},

    {QObject::tr("Ifrit"),		":/icon/summon",      0x4C,/*{-2,+2,0,0,0,0,+1,0}*/         QObject::tr("HP:-2% MP:+2% Mag:+1")
   ,{QObject::tr("Summon Ifrit x1 (34mp)"),QObject::tr("Summon Ifrit x2 (34mp)"),QObject::tr("Summon Ifrit x3 (34mp)"),QObject::tr("Summon Ifrit x4 (34mp)"),QObject::tr("Summon Ifrit x5 (34mp)")},{5000,20000,35000,60000},2,5},

    {QObject::tr("Ramuh"),		":/icon/summon",      0x4D,/*{-2,+2,0,0,0,0,+1,0}*/         QObject::tr("HP:-2% MP:+2% Mag:+1")
   ,{QObject::tr("Summon Ramuh x1 (40mp)"),QObject::tr("Summon Ramuh x2 (40mp)"),QObject::tr("Summon Ramuh x3 (40mp)"),QObject::tr("Summon Ramuh x4 (40mp)"),QObject::tr("Summon Ramuh x5 (40mp)")},{10000,25000,50000,70000},2,5},

    {QObject::tr("Titan"),		":/icon/summon",      0x4E,/*{-2,+2,0,0,0,0,+1,0}*/         QObject::tr("HP:-2% MP:+2% Mag:+1")
   ,{QObject::tr("Summon Titan x1 (46mp)"),QObject::tr("Summon Titan x2 (46mp)"),QObject::tr("Summon Titan x3 (46mp)"),QObject::tr("Summon Titan x4 (46mp)"),QObject::tr("Summon Titan x5 (46mp)")},{15000,30000,60000,80000},2,5},

    {QObject::tr("Odin"),		":/icon/summon",      0x4F,/*{-5,+5,0,0,0,0,+1,+1}*/        QObject::tr("HP:-5% MP:+5% Mag:+1 Spi:+1")
   ,{QObject::tr("Summon Odin x1 (80mp)"),QObject::tr("Summon Odin x2 (80mp)"),QObject::tr("Summon Odin x3 (80mp)"),QObject::tr("Summon Odin x4 (80mp)"),QObject::tr("Summon Odin x5 (80mp)")},{16000,32000,65000,90000},2,5},

    {QObject::tr("Leviathan"),  	":/icon/summon",      0x50,/*{-5,+5,0,0,0,0,+1,+1}*/        QObject::tr("HP:-5% MP:+5% Mag:+1 Spi:+1")
   ,{QObject::tr("Summon Leviathan x1 (78mp)"),QObject::tr("Summon Leviathan x2 (78mp)"),QObject::tr("Summon Leviathan x3 (78mp)"),QObject::tr("Summon Leviathan x4 (78mp)"),QObject::tr("Summon Leviathan x5 (78mp)")},{18000,38000,70000,100000},2,5},

    {QObject::tr("Bahamut"),		":/icon/summon",      0x51,/*{-5,+5,0,0,0,0,+1,+1}*/        QObject::tr("HP:-5% MP:+5% Mag:+1 Spi:+1")
   ,{QObject::tr("Summon Bahamut x1 (100mp)"),QObject::tr("Summon Bahamut x2 (100mp)"),QObject::tr("Summon Bahamut x3 (100mp)"),QObject::tr("Summon Bahamut x4 (100mp)"),QObject::tr("Summon Bahamut x5 (100mp)")},{20000,50000,80000,120000},2,5},

    {QObject::tr("Kujata"),		":/icon/summon",      0x52,/*{-5,+5,0,0,0,0,+1,+1}*/        QObject::tr("HP:-5% MP:+5% Mag:+1 Spi:+1")
   ,{QObject::tr("Summon Kujata x1 (110mp)"),QObject::tr("Summon Kujata x2 (110mp)"),QObject::tr("Summon Kujata x3 (110mp)"),QObject::tr("Summon Kujata x4 (110mp)"),QObject::tr("Summon Kujata x5 (110mp)")},{22000,60000,90000,140000},2,5},

    {QObject::tr("Alexander"),  	":/icon/summon",      0x53,/*{-5,+5,0,0,0,0,+1,+1}*/        QObject::tr("HP:-5% MP:+5% Mag:+1 Spi:+1")
   ,{QObject::tr("Summon Alexander x1 (120mp)"),QObject::tr("Summon Alexander x2 (120mp)"),QObject::tr("Summon Alexander x3 (120mp)"),QObject::tr("Summon Alexander x4 (120mp)"),QObject::tr("Summon Alexander x5 (120mp)")},{25000,65000,100000,150000},2,5},

    {QObject::tr("Phoenix"),		":/icon/summon",      0x54,/*{-10,+10,0,0,0,0,+2,+2}*/      QObject::tr("HP:-10% MP:+10% Mag:+2 Spi:+2")
   ,{QObject::tr("Summon Phoenix x1 (180mp)"),QObject::tr("Summon Phoenix x2 (180mp)"),QObject::tr("Summon Phoenix x3 (180mp)"),QObject::tr("Summon Phoenix x4 (180mp)"),QObject::tr("Summon Phoenix x5 (180mp)")},{28000,70000,120000,180000},2,5},

    {QObject::tr("Neo Bahamut"),        ":/icon/summon",      0x55,/*{-10,+10,0,0,0,0,+2,+2}*/      QObject::tr("HP:-10% MP:+10% Mag:+2 Spi:+2")
   ,{QObject::tr("Summon Neo Bahamut x1 (140mp)"),QObject::tr("Summon Neo Bahamut x2 (140mp)"),QObject::tr("Summon Neo Bahamut x3 (140mp)"),QObject::tr("Summon Neo Bahamut x4 (140mp)"),QObject::tr("Summon Neo Bahamut x5 (140mp)")},{30000,80000,140000,200000},2,5},

    {QObject::tr("Hades"),		":/icon/summon",      0x56,/*{-10,+15,0,0,0,0,+4,+4}*/     QObject::tr("HP:-10% MP:+15% Mag:+4 Spi:+4")
   ,{QObject::tr("Summon Hades x1 (150mp)"),QObject::tr("Summon Hades x2 (150mp)"),QObject::tr("Summon Hades x3 (150mp)"),QObject::tr("Summon Hades x4 (150mp)"),QObject::tr("Summon Hades x5 (150mp)")},{35000,120000,150000,250000},2,5},

    {QObject::tr("Typhoon"),		":/icon/summon",      0x57,/*{-10,+15,0,0,0,0,+4,+4}*/      QObject::tr("HP:-10% MP:+15% Mag:+4 Spi:+4")
   ,{QObject::tr("Summon Typhoon x1 (160mp)"),QObject::tr("Summon Typhoon x2 (160mp)"),QObject::tr("Summon Typhoon x3 (160mp)"),QObject::tr("Summon Typhoon x4 (160mp)"),QObject::tr("Summon Typhoon x5 (160mp)")},{35000,120000,150000,250000},2,5},

    {QObject::tr("Bahamut ZERO"),	":/icon/summon",      0x58,/*{-10,+15,0,0,0,0,+4,+4}*/      QObject::tr("HP:-10% MP:+15% Mag:+4 Spi:+4")
   ,{QObject::tr("Summon Bahamut ZERO x1 (180mp)"),QObject::tr("Summon Bahamut ZERO x2 (180mp)"),QObject::tr("Summon Bahamut ZERO x3 (180mp)"),QObject::tr("Summon Bahamut ZERO x4 (180mp)"),QObject::tr("Summon Bahamut ZERO x5 (180mp)")},{35000,120000,150000,250000},2,5},

    {QObject::tr("Knights of Round"),   ":/icon/summon",      0x59,/*{-10,+20,0,0,0,0,+8,+8}*/      QObject::tr("HP:-10% MP:+20% Mag:+8 Spi:+8")
   ,{QObject::tr("Summon KOTR x1 (250mp)"),QObject::tr("Summon KOTR x2 (250mp)"),QObject::tr("Summon KOTR x3 (250mp)"),QObject::tr("Summon KOTR x4 (250mp)"),QObject::tr("Summon KOTR x5 (250mp)")},{50000,200000,300000,500000},2,5},

    {QObject::tr("Master Summon"),	":/icon/summon",      0x5A,/*{0,0,0,0,0,0,0,0}*/            ""
   ,{QObject::tr("Master Summon"),"","","",""},{0,0,0,0},2,1}

};
static char chPC[256] = {
        ' ',	// 00: Space
        '!',
        '"',
        '#',
        '$',
        '%',
        '&',
        '\'',	// 07: "'" (apostrophe)
        '(',
        ')',
        '*',
        '+',
        ',',
        '-',
        '.',
        '/',
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        ':',
        ';',
        '<',
        '=',
        '>',
        '?',
        '@',
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
        'G',
        'H',
        'I',
        'J',
        'K',
        'L',
        'M',
        'N',
        'O',
        'P',
        'Q',
        'R',
        'S',
        'T',
        'U',
        'V',
        'W',
        'X',
        'Y',
        'Z',
        '[',
        '\\',
(char)	']',
        '^',
        '_',
        '`',
        'a',
        'b',
        'c',
        'd',
        'e',
        'f',
        'g',
        'h',
        'i',
        'j',
        'k',
        'l',
        'm',
        'n',
        'o',
        'p',
        'q',
        'r',
        's',
        't',
        'u',
        'v',
        'w',
        'x',
        'y',
        'z',
        '{',
        '|',
        '}',
        '~',
        ' ',
        'Ä',
        'Á',
        'Ç',
        'É',
        'Ñ',
        'Ö',
        'Ü',
        'á',
        'à',
        'â',
        'ä',
        'ã',
        'å',
        'ç',
        'é',
        'è',
        'ê',
        'ë',
        'í',
        'ì',
        'î',
        'ï',
        'ñ',
        'ó',
        'ò',
        'ô',
        'ö',
        'õ',
        'ú',
        'ù',
        'û',
        'ü',
        ' ',
        '°',
        '¢',
        '£',
        'Ú',
        'Û',
        '¶',
        'ß',
        '®',
        '©',
        '™',
        '´',
        '¨',
        ' ',	// non-equality
        'Æ',
        'Ø',
        ' ',	// infinity
        '±',
        ' ',	// <=
        ' ',	// >=
        '¥',
        'µ',
        ' ',	// a-like symbol
        ' ',	// sum
        ' ',	// capital pi
        ' ',	// pi
        ' ',	// J-like symbol
        ' ',	// a-underline
        ' ',	// o-underline
        ' ',	// capital omega
        'æ',
        'ø',
        '¿',
        '¡',
        '¬',
        ' ',	// check mark
        'ƒ',
        ' ',	// approximate to
        ' ',	// capital delta
        '«',
        '»',
        '…',	// '...' character
        ' ',
        'À',
        'Ã',
        'Õ',
        'Œ',
        'œ',
        '–',
        '—',
        '“',
        '”',
        '‘',
        '’',
        '÷',
        ' ',	// romboid
        'ÿ',
        '/',
        '¤',
        '‹',
        '›',
        ' ',	// fi-like
        ' ',	// fl-like
        '•',	// filled square
        '·',
        '‚',
        '„',
        '‰',
        'Å',
        'Ê',
        ' ',	// A-dash
        'Ë',
        'È',
        'Í',
        'Î',
        'Ï',
        'Ì',
        'Ó',
        'Ô',
        ' ',	// apple
        'Ò',
        'Ú',
        'Û',
        ' ',	// wide U
        ' ',	// low vertical dash
        ' ',	// D5: Cyan (following FE)
        ' ',
        ' ',	// D7: Purple (following FE)
        ' ',
        ' ',	// D9: White (following FE)
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',	// E0
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',	// E7: Line feed (?)
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',	// F0
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',	// FE: Change text color
        '\0'	// FF: End of string (NULL)
};
#endif // GLOBALS_H


