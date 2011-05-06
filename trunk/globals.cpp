/****************************************************************************/
//    copyright 2010, 2011 Chris Rizzitello <sithlord48@gmail.com>          //
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
#include "globals.h"

FF7 ff7;
int s;

int ff7__checksum( void* qw )
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

void fix_pc_bytemask(void)
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
    if(ff7.SG_Region_String[i].contains("00867") || ff7.SG_Region_String[i].contains("00869") ||
       ff7.SG_Region_String[i].contains("00900") || ff7.SG_Region_String[i].contains("94163") ||
       ff7.SG_Region_String[i].contains("00700") || ff7.SG_Region_String[i].contains("01057"))
    {
    mask |= (1<<i);
    }
}

newheader[5]=mask;
mask=0;// reset for the next byte
//calc 0x06 of the header (slot 9-15 empty?)
for(int i=8;i<15;i++)
{
    if(ff7.SG_Region_String[i].contains("00867") || ff7.SG_Region_String[i].contains("00869") ||
       ff7.SG_Region_String[i].contains("00900") || ff7.SG_Region_String[i].contains("94163") ||
       ff7.SG_Region_String[i].contains("00700") || ff7.SG_Region_String[i].contains("01057"))
    {
    mask |= (1<<(i-8));
    }
}
newheader[6]=mask;
memcpy(ff7.file_headerp,newheader,9);
}

static const char *itemNames[]=
{
    QT_TR_NOOP("Potion"),QT_TR_NOOP("Hi-Potion"),QT_TR_NOOP("X-Potion"),QT_TR_NOOP("Ether"),QT_TR_NOOP("Turbo Ether"),
    QT_TR_NOOP("Elixir"),QT_TR_NOOP("Megalixir"),QT_TR_NOOP("Phoenix Down"),QT_TR_NOOP("Antidote"),QT_TR_NOOP("Soft"),
    QT_TR_NOOP("Maiden's Kiss"),QT_TR_NOOP("Cornucopia"),QT_TR_NOOP("Echo screen"),QT_TR_NOOP("Hyper"),QT_TR_NOOP("Tranquilizer"),
    QT_TR_NOOP("Remedy"),QT_TR_NOOP("Smoke Bomb"),QT_TR_NOOP("Speed Drink"),QT_TR_NOOP("Hero Drink"),QT_TR_NOOP("Vaccine"),
    QT_TR_NOOP("Grenade"),QT_TR_NOOP("Shrapnel"),QT_TR_NOOP("Right Arm"),QT_TR_NOOP("Hourglass"),QT_TR_NOOP("Kiss of Death"),
    QT_TR_NOOP("Spider Web"),QT_TR_NOOP("Dream Powder"),QT_TR_NOOP("Mute Mask"),QT_TR_NOOP("War Gong"),QT_TR_NOOP("Loco weed"),
    QT_TR_NOOP("Fire Fang"),QT_TR_NOOP("Fire Veil"),QT_TR_NOOP("Antarctic Wind"),QT_TR_NOOP("Ice Crystal"),QT_TR_NOOP("Bolt Plume"),
    QT_TR_NOOP("Swift Bolt"),
                 QT_TR_NOOP("Earth Drum"),
                 QT_TR_NOOP("Earth Mallet"),
                 QT_TR_NOOP("Deadly Waste"),
                 QT_TR_NOOP("M-Tentacles"),
                 QT_TR_NOOP("Stardust"),
                 QT_TR_NOOP("Vampire Fang"),
                 QT_TR_NOOP("Ghost Hand"),
                 QT_TR_NOOP("Vagyrisk Claw"),
                 QT_TR_NOOP("Light Curtain"),
                 QT_TR_NOOP("Lunar Curtain"),
                 QT_TR_NOOP("Mirror"),
                 QT_TR_NOOP("Holy Torch"),
                 QT_TR_NOOP("Bird Wing"),
                 QT_TR_NOOP("Dragon Scales"),
                 QT_TR_NOOP("Impaler"),
                 QT_TR_NOOP("Shrivel"),
                 QT_TR_NOOP("Eye drop"),
                 QT_TR_NOOP("Molotov"),
                 QT_TR_NOOP("S-mine"),
                 QT_TR_NOOP("8 Inch Cannon"),
                 QT_TR_NOOP("Graviball"),
                 QT_TR_NOOP("T/S Bomb"),
                 QT_TR_NOOP("Ink"),
                 QT_TR_NOOP("Dazers"),
                 QT_TR_NOOP("Dragon Fang"),
                 QT_TR_NOOP("Cauldron"),
                 QT_TR_NOOP("Sylkis Greens"),
                 QT_TR_NOOP("Reagan Greens"),
                 QT_TR_NOOP("Mimett Greens"),
                 QT_TR_NOOP("Curiel Greens"),
                 QT_TR_NOOP("Pahsana Greens"),
                 QT_TR_NOOP("Tantal Greens"),
                 QT_TR_NOOP("Krakka Greens"),
                 QT_TR_NOOP("Gysahl Greens"),
                 QT_TR_NOOP("Tent"),
                 QT_TR_NOOP("Power Source"),
                 QT_TR_NOOP("Guard Source"),
                 QT_TR_NOOP("Magic Source"),
                 QT_TR_NOOP("Mind Source"),
                 QT_TR_NOOP("Speed Source"),
                 QT_TR_NOOP("Luck Source"),
                 QT_TR_NOOP("Zeio Nut"),
                 QT_TR_NOOP("Carob Nut"),
                 QT_TR_NOOP("Porov Nut"),
                 QT_TR_NOOP("Pram Nut"),
                 QT_TR_NOOP("Lasan Nut"),
                 QT_TR_NOOP("Sahara Nut"),
                 QT_TR_NOOP("Luchile Nut"),
                 QT_TR_NOOP("Pepio Nut"),
                 QT_TR_NOOP("Battery"),
                 QT_TR_NOOP("Tissue"),
                 QT_TR_NOOP("Omnislash"),
                 QT_TR_NOOP("Catastrophe"),
                 QT_TR_NOOP("Final Heaven"),
                 QT_TR_NOOP("Great Gospel"),
                 QT_TR_NOOP("Cosmo Memory"),
                 QT_TR_NOOP("All Creation"),
                 QT_TR_NOOP("Chaos"),
                 QT_TR_NOOP("Highwind"),
                 QT_TR_NOOP("1/35 Soldier"),
                 QT_TR_NOOP("Super Sweeper"),
                 QT_TR_NOOP("Masamune Blade"),
                 QT_TR_NOOP("Save Crystal"),
                 QT_TR_NOOP("Combat Diary"),
                 QT_TR_NOOP("Autograph"),
                 QT_TR_NOOP("Gambler"),
                 QT_TR_NOOP("Desert Rose"),
                 QT_TR_NOOP("Earth Harp"),
                 QT_TR_NOOP("Guide Book"),
              //nothing 106-127
                 "DON'T USE","DON'T USE","DON'T USE","DON'T USE",
                 "DON'T USE","DON'T USE","DON'T USE","DON'T USE","DON'T USE","DON'T USE",
                 "DON'T USE","DON'T USE","DON'T USE","DON'T USE","DON'T USE","DON'T USE",
                 "DON'T USE","DON'T USE","DON'T USE","DON'T USE","DON'T USE","DON'T USE","DON'T USE",
              //cloud weapons 128 -143
                 QT_TR_NOOP("Buster Sword"),
                 QT_TR_NOOP("Mythril Saber"),
                 QT_TR_NOOP("Hardedge"),
                 QT_TR_NOOP("Butterfly Edge"),
                 QT_TR_NOOP("Enhance Sword"),
                 QT_TR_NOOP("Organics"),
                 QT_TR_NOOP("Crystal Sword"),
                 QT_TR_NOOP("Force Stealer"),
                 QT_TR_NOOP("Rune Blade"),
                 QT_TR_NOOP("Murasame"),
                 QT_TR_NOOP("Nail Bat"),
                 QT_TR_NOOP("Yoshiyuki"),
                 QT_TR_NOOP("Apocalypse"),
                 QT_TR_NOOP("Heaven's Cloud"),
                 QT_TR_NOOP("Ragnarok"),
                 QT_TR_NOOP("Ultima Weapon"),
              //tifa's weapons 144-159
                 QT_TR_NOOP("Leather Glove"),
                 QT_TR_NOOP("Metal Knuckle"),
                 QT_TR_NOOP("Mythril Claw"),
                 QT_TR_NOOP("Grand Glove"),
                 QT_TR_NOOP("Tiger Fang"),
                 QT_TR_NOOP("Diamond Knuckle"),
                 QT_TR_NOOP("Dragon Claw"),
                 QT_TR_NOOP("Crystal Glove"),
                 QT_TR_NOOP("Motor Drive"),
                 QT_TR_NOOP("Platinum Fist"),
                 QT_TR_NOOP("Kaiser Knuckle"),
                 QT_TR_NOOP("Work Glove"),
                 QT_TR_NOOP("Powersoul"),
                 QT_TR_NOOP("Master Fist"),
                 QT_TR_NOOP("God's Hand"),
                 QT_TR_NOOP("Premium Heart"),
              // barret's weapons 160-175
                 QT_TR_NOOP("Gatling Gun"),
                 QT_TR_NOOP("Assault Gun"),
                 QT_TR_NOOP("Cannon Ball"),
                 QT_TR_NOOP("Atomic Scissors"),
                 QT_TR_NOOP("Heavy Vulcan"),
                 QT_TR_NOOP("Chainsaw"),
                 QT_TR_NOOP("Microlaser"),
                 QT_TR_NOOP("A-M Cannon"),
                 QT_TR_NOOP("W Machine Gun"),
                 QT_TR_NOOP("Drill Arm"),
                 QT_TR_NOOP("Solid Bazooka"),
                 QT_TR_NOOP("Rocket Punch"),
                 QT_TR_NOOP("Enemy Launcher"),
                 QT_TR_NOOP("Pile Banger"),
                 QT_TR_NOOP("Max Ray"),
                 QT_TR_NOOP("Missing Score"),
              //red's weapons 176-189
                 QT_TR_NOOP("Mythril Clip"),
                 QT_TR_NOOP("Diamond Pin"),
                 QT_TR_NOOP("Silver Barette"),
                 QT_TR_NOOP("Gold Barette"),
                 QT_TR_NOOP("Adaman Clip"),
                 QT_TR_NOOP("Crystal Comb"),
                 QT_TR_NOOP("Magic Comb"),
                 QT_TR_NOOP("Plus Barette"),
                 QT_TR_NOOP("Centclip"),
                 QT_TR_NOOP("Hairpin"),
                 QT_TR_NOOP("Seraph Comb"),
                 QT_TR_NOOP("Behemoth Horn"),
                 QT_TR_NOOP("Spring Gun Clip"),
                 QT_TR_NOOP("Limited Moon"),
              //aeris weapons 190-200
                 QT_TR_NOOP("Guard Stick"),
                 QT_TR_NOOP("Mythril Rod"),
                 QT_TR_NOOP("Full Metal Staff"),
                 QT_TR_NOOP("Striking Staff"),
                 QT_TR_NOOP("Prism Staff"),
                 QT_TR_NOOP("Aurora Rod"),
                 QT_TR_NOOP("Wizard Staff"),
                 QT_TR_NOOP("Wizer Staff"),
                 QT_TR_NOOP("Fairy Tale"),
                 QT_TR_NOOP("Umbrella"),
                 QT_TR_NOOP("Princess Guard"),
              //cid weapons 201-214
                 QT_TR_NOOP("Spear"),
                 QT_TR_NOOP("Slash Lance"),
                 QT_TR_NOOP("Trident"),
                 QT_TR_NOOP("Mast Ax"),
                 QT_TR_NOOP("Partisan"),
                 QT_TR_NOOP("Viper Halberd"),
                 QT_TR_NOOP("Javelin"),
                 QT_TR_NOOP("Grow Lance"),
                 QT_TR_NOOP("Mop"),
                 QT_TR_NOOP("Dragoon Lance"),
                 QT_TR_NOOP("Scimitar"),
                 QT_TR_NOOP("Flayer"),
                 QT_TR_NOOP("Spirit Lance"),
                 QT_TR_NOOP("Venus Gospel"),
              //yuffie weapons 215-228
                 QT_TR_NOOP("4-point Shuriken"),
                 QT_TR_NOOP("Boomerang"),
                 QT_TR_NOOP("Pinwheel"),
                 QT_TR_NOOP("Razor Ring"),
                 QT_TR_NOOP("Hawkeye"),
                 QT_TR_NOOP("Crystal Cross"),
                 QT_TR_NOOP("Wind Slash"),
                 QT_TR_NOOP("Twin Viper"),
                 QT_TR_NOOP("Spiral Shuriken"),
                 QT_TR_NOOP("Superball"),
                 QT_TR_NOOP("Magic Shuriken"),
                 QT_TR_NOOP("Rising Sun"),
                 QT_TR_NOOP("Oritsuru"),
                 QT_TR_NOOP("Conformer"),
              //cait sith weapons 229-241
                 QT_TR_NOOP("Yellow M-phone"),
                 QT_TR_NOOP("Green M-phone"),
                 QT_TR_NOOP("Blue M-phone"),
                 QT_TR_NOOP("Red M-phone"),
                 QT_TR_NOOP("Crystal M-phone"),
                 QT_TR_NOOP("White M-phone"),
                 QT_TR_NOOP("Black M-phone"),
                 QT_TR_NOOP("Silver M-phone"),
                 QT_TR_NOOP("Trumpet Shell"),
                 QT_TR_NOOP("Gold M-phone"),
                 QT_TR_NOOP("Battle Trumpet"),
                 QT_TR_NOOP("Starlight Phone"),
                 QT_TR_NOOP("HP Shout"),
              //vincent weapons... 242-254
                 QT_TR_NOOP("Quicksilver"),
                 QT_TR_NOOP("Shotgun"),
                 QT_TR_NOOP("Shortbarrel"),
                 QT_TR_NOOP("Lariat"),
                 QT_TR_NOOP("Winchester"),
                 QT_TR_NOOP("Peacemaker"),
                 QT_TR_NOOP("Buntline"),
                 QT_TR_NOOP("Long Barrel R"),
                 QT_TR_NOOP("Silver Rifle"),
                 QT_TR_NOOP("Sniper CR"),
                 QT_TR_NOOP("Supershot ST"),
                 QT_TR_NOOP("Outsider"),
                 QT_TR_NOOP("Death Penalty"),
              //sepi weapon =255
                 QT_TR_NOOP("Masamune"),
              //armor  256-287
                 QT_TR_NOOP("Bronze Bangle"),
                 QT_TR_NOOP("Iron Bangle"),
                 QT_TR_NOOP("Titan Bangle"),
                 QT_TR_NOOP("Mythril Armlet"),
                 QT_TR_NOOP("Carbon Bangle"),
                 QT_TR_NOOP("Silver Armlet"),
                 QT_TR_NOOP("Gold Armlet"),
                 QT_TR_NOOP("Diamond Bangle"),
                 QT_TR_NOOP("Crystal Bangle"),
                 QT_TR_NOOP("Platinum Bangle"),
                 QT_TR_NOOP("Rune Armlet"),
                 QT_TR_NOOP("Edincoat"),
                 QT_TR_NOOP("Wizard Bracelet"),
                 QT_TR_NOOP("Adaman Bangle"),
                 QT_TR_NOOP("Gigas Armlet"),
                 QT_TR_NOOP("Imperial Guard"),
                 QT_TR_NOOP("Aegis Armlet"),
                 QT_TR_NOOP("Fourth Bracelet"),
                 QT_TR_NOOP("Warrior Bangle"),
                 QT_TR_NOOP("Shinra Beta"),
                 QT_TR_NOOP("Shinra Alpha"),
                 QT_TR_NOOP("Four Slots"),
                 QT_TR_NOOP("Fire Armlet"),
                 QT_TR_NOOP("Aurora Armlet"),
                 QT_TR_NOOP("Bolt Armlet"),
                 QT_TR_NOOP("Dragon Armlet"),
                 QT_TR_NOOP("Minerva Band"),
                 QT_TR_NOOP("Escort Guard"),
                 QT_TR_NOOP("Mystile"),
                 QT_TR_NOOP("Ziedrich"),
                 QT_TR_NOOP("Precious Watch"),
                 QT_TR_NOOP("Chocobracelet"),
              //accessorys 288-319
                 QT_TR_NOOP("Power Wrist"),
                 QT_TR_NOOP("Protect Vest"),
                 QT_TR_NOOP("Earring"),
                 QT_TR_NOOP("Talisman"),
                 QT_TR_NOOP("Choco Feather"),
                 QT_TR_NOOP("Amulet"),
                 QT_TR_NOOP("Champion Belt"),
                 QT_TR_NOOP("Poison Ring"),
                 QT_TR_NOOP("Tough Ring"),
                 QT_TR_NOOP("Circlet"),
                 QT_TR_NOOP("Star Pendant"),
                 QT_TR_NOOP("Silver Glasses"),
                 QT_TR_NOOP("Headband"),
                 QT_TR_NOOP("Fairy Ring"),
                 QT_TR_NOOP("Jem Ring"),
                 QT_TR_NOOP("White Cape"),
                 QT_TR_NOOP("Sprint Shoes"),
                 QT_TR_NOOP("Peace Ring"),
                 QT_TR_NOOP("Ribbon"),
                 QT_TR_NOOP("Fire Ring"),
                 QT_TR_NOOP("Ice Ring"),
                 QT_TR_NOOP("Bolt Ring"),
                 QT_TR_NOOP("Tetra Elemental"),
                 QT_TR_NOOP("Safety Bit"),
                 QT_TR_NOOP("Fury Ring"),
                 QT_TR_NOOP("Curse Ring"),
                 QT_TR_NOOP("Protect Ring"),
                 QT_TR_NOOP("Cat's Bell"),
                 QT_TR_NOOP("Reflect Ring"),
                 QT_TR_NOOP("Water Ring"),
                 QT_TR_NOOP("Sneak Glove"),
                 QT_TR_NOOP("HypnoCrown")
};
static const char *materiaNames[]=
{
    QT_TR_NOOP("MP Plus"),QT_TR_NOOP("HP Plus"),QT_TR_NOOP("Speed Plus"),QT_TR_NOOP("Magic Plus"),QT_TR_NOOP("Luck Plus"),QT_TR_NOOP("EXP Plus"),
    QT_TR_NOOP("Gil Plus"),QT_TR_NOOP("Enemy Away"),QT_TR_NOOP("Enemy Lure"),QT_TR_NOOP("Chocobo Lure"),QT_TR_NOOP("Pre-emptive"),QT_TR_NOOP("Long Range"),
    QT_TR_NOOP("Mega All"),QT_TR_NOOP("Counter Attack"),QT_TR_NOOP("Slash-All"),QT_TR_NOOP("Double Cut"),QT_TR_NOOP("Cover"),QT_TR_NOOP("Underwater"),
    QT_TR_NOOP("HP <-> MP"),QT_TR_NOOP("W-Magic"),QT_TR_NOOP("W-Summon"),QT_TR_NOOP("W-Item"),"DON'T USE",QT_TR_NOOP("All"),QT_TR_NOOP("Counter"),
    QT_TR_NOOP("Magic Counter"),QT_TR_NOOP("MP Turbo"),QT_TR_NOOP("MP Absorb"),QT_TR_NOOP("HP Absorb"),QT_TR_NOOP("Elemental"),QT_TR_NOOP("Added Effect"),
    QT_TR_NOOP("Sneak Attack"),QT_TR_NOOP("Final Attack"),QT_TR_NOOP("Added Cut"),QT_TR_NOOP("Steal-As-Well"),QT_TR_NOOP("Quadra Magic"),QT_TR_NOOP("Steal"),
    QT_TR_NOOP("Sense"),"DON'T USE",QT_TR_NOOP("Throw"),QT_TR_NOOP("Morph"),QT_TR_NOOP("DeathBlow"),QT_TR_NOOP("Manipulate"),QT_TR_NOOP("Mime"),
    QT_TR_NOOP("Enemy Skill"),"DON'T USE","DON'T USE","DON'T USE",QT_TR_NOOP("Master Command"),QT_TR_NOOP("Fire"),QT_TR_NOOP("Ice"),QT_TR_NOOP("Earth"),
    QT_TR_NOOP("Lightning"),QT_TR_NOOP("Restore"),QT_TR_NOOP("Heal"),QT_TR_NOOP("Revive"),QT_TR_NOOP("Seal"),QT_TR_NOOP("Mystify"),
    QT_TR_NOOP("Transform"),QT_TR_NOOP("Exit"),QT_TR_NOOP("Poison"),QT_TR_NOOP("Demi"),QT_TR_NOOP("Barrier"),"DON'T USE",QT_TR_NOOP("Comet"),
    QT_TR_NOOP("Time"),"DON'T USE","DON'T USE",QT_TR_NOOP("Destruct"),QT_TR_NOOP("Contain"),QT_TR_NOOP("FullCure"),QT_TR_NOOP("Shield"),QT_TR_NOOP("Ultima"),
    QT_TR_NOOP("Master Magic"),QT_TR_NOOP("Choco/Mog"),QT_TR_NOOP("Shiva"),QT_TR_NOOP("Ifrit"),QT_TR_NOOP("Ramuh"),QT_TR_NOOP("Titan"),
    QT_TR_NOOP("Odin"),QT_TR_NOOP("Leviathan"),QT_TR_NOOP("Bahamut"),QT_TR_NOOP("Kujata"),QT_TR_NOOP("Alexander"),QT_TR_NOOP("Phoenix"),
    QT_TR_NOOP("Neo Bahamut"),QT_TR_NOOP("Hades"),QT_TR_NOOP("Typhoon"),QT_TR_NOOP("Bahamut ZERO"),QT_TR_NOOP("Knights of Round"),QT_TR_NOOP("Master Summon")
};
static const char *materiaStats[]=
{
    QT_TR_NOOP("MP:+% depending on level"),QT_TR_NOOP("HP:+% depending on level"),QT_TR_NOOP("Dex:+% depending on level"),QT_TR_NOOP("Mag:+% depending on level"),
    QT_TR_NOOP("Lck:+% depending on level"),QT_TR_NOOP("Lck:+1"),QT_TR_NOOP("Lck:+1"),QT_TR_NOOP("Lck:+1"),QT_TR_NOOP("Lck:-1"),QT_TR_NOOP("Lck:+1"),QT_TR_NOOP("Dex:+2")
    ,"","","","",QT_TR_NOOP("Dex:+2"),QT_TR_NOOP("Vit:+1"),"","","","","","ID:0x16","","","","","","","","","","","","","",QT_TR_NOOP("Dex:+2"),"","ID:0x26",QT_TR_NOOP("Vit:+1"),
    "",QT_TR_NOOP("Lck:+1"),"","","","ID:0x2D","ID:0x2E","ID:0x2F","",QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),
    QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),
    QT_TR_NOOP("HP:-5% MP:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"),QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),
    QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),QT_TR_NOOP("HP:-2% MP:+2% Str:-1 Mag:+1"),QT_TR_NOOP("HP:-5% MP:+5% Str:-2 Vit -1 Mag:+2 Spi:+1"),
    "ID:0x3F",QT_TR_NOOP("HP:-5% MP:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"),QT_TR_NOOP("HP:-5% MP:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"),"ID:0x42","ID:0x43",
    QT_TR_NOOP("HP:-5% MP:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"),QT_TR_NOOP("HP:-10% MP:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"),QT_TR_NOOP("HP:-10% MP:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"),
    QT_TR_NOOP("HP:-10% MP:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"),QT_TR_NOOP("HP:-10% MP:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"),"",QT_TR_NOOP("HP:-2% MP:+2% Mag:+1"),
    QT_TR_NOOP("HP:-2% MP:+2% Mag:+1"),QT_TR_NOOP("HP:-2% MP:+2% Mag:+1"),QT_TR_NOOP("HP:-2% MP:+2% Mag:+1"),QT_TR_NOOP("HP:-2% MP:+2% Mag:+1"),QT_TR_NOOP("HP:-5% MP:+5% Mag:+1 Spi:+1"),
    QT_TR_NOOP("HP:-5% MP:+5% Mag:+1 Spi:+1"),QT_TR_NOOP("HP:-5% MP:+5% Mag:+1 Spi:+1"),QT_TR_NOOP("HP:-5% MP:+5% Mag:+1 Spi:+1"),QT_TR_NOOP("HP:-5% MP:+5% Mag:+1 Spi:+1"),
    QT_TR_NOOP("HP:-10% MP:+10% Mag:+2 Spi:+2"),QT_TR_NOOP("HP:-10% MP:+10% Mag:+2 Spi:+2"),QT_TR_NOOP("HP:-10% MP:+15% Mag:+4 Spi:+4"),QT_TR_NOOP("HP:-10% MP:+15% Mag:+4 Spi:+4"),
    QT_TR_NOOP("HP:-10% MP:+15% Mag:+4 Spi:+4"),QT_TR_NOOP("HP:-10% MP:+20% Mag:+8 Spi:+8"),""
};
static const char *materiaSkills[91][5]=
{
    {QT_TR_NOOP("MP Plus +10%"),QT_TR_NOOP("MP Plus +20%"),QT_TR_NOOP("MP Plus +30%"),QT_TR_NOOP("MP Plus +40%"),QT_TR_NOOP("MP Plus +50%")},
    {QT_TR_NOOP("HP Plus +10%"),QT_TR_NOOP("HP Plus +20%"),QT_TR_NOOP("HP Plus +30%"),QT_TR_NOOP("HP Plus +40%"),QT_TR_NOOP("HP Plus +50%")},
    {QT_TR_NOOP("Speed Plus +10%"),QT_TR_NOOP("Speed Plus +20%"),QT_TR_NOOP("Speed Plus +30%"),QT_TR_NOOP("Speed Plus +40%"),QT_TR_NOOP("Speed Plus +50%")},
    {QT_TR_NOOP("Magic Plus +10%"),QT_TR_NOOP("Magic Plus +20%"),QT_TR_NOOP("Magic Plus +30%"),QT_TR_NOOP("Magic Plus +40%"),QT_TR_NOOP("Magic Plus +50%")},
    {QT_TR_NOOP("Luck Plus +10%"),QT_TR_NOOP("Luck Plus +20%"),QT_TR_NOOP("Luck Plus +30%"),QT_TR_NOOP("Luck Plus +40%"),QT_TR_NOOP("Luck Plus +50%")},
    {QT_TR_NOOP("Exp Plus +50%"),QT_TR_NOOP("Exp Plus +100%"),QT_TR_NOOP("Mastered"),"",""},{QT_TR_NOOP("Gil Plus +50%"),QT_TR_NOOP("Gil Plus +100%"),QT_TR_NOOP("Mastered"),"",""},
    {QT_TR_NOOP("Encounter Rate -50%"),QT_TR_NOOP("Encounter Rate -75%"),QT_TR_NOOP("Mastered"),"",""},{QT_TR_NOOP("Encounter Rate +50%"),QT_TR_NOOP("Encounter Rate +100%"),QT_TR_NOOP("Mastered"),"",""},
    {QT_TR_NOOP("Chocobo Lure"),QT_TR_NOOP("Chocobo Lure +50%"),QT_TR_NOOP("Chocobo Lure +100%"),QT_TR_NOOP("Chocobo Lure +200%"),QT_TR_NOOP("Mastered")},
    {QT_TR_NOOP("Pre-emptive +6%"),QT_TR_NOOP("Pre-emptive +12%"),QT_TR_NOOP("Pre-emptive +24%"),QT_TR_NOOP("Pre-emptive +36%"),QT_TR_NOOP("Pre-emptive +48%")},
    {QT_TR_NOOP("Long Range"),QT_TR_NOOP("Mastered"),"","",""},{QT_TR_NOOP("Mega-all x1"),QT_TR_NOOP("Mega-all x2"),QT_TR_NOOP("Mega-all x3"),QT_TR_NOOP("Mega-all x4"),QT_TR_NOOP("Mega-all x5")},
    {QT_TR_NOOP("Counter Attack 20%"),QT_TR_NOOP("Counter Attack 40%"),QT_TR_NOOP("Counter Attack 60%"),QT_TR_NOOP("Counter Attack 80%"),QT_TR_NOOP("Counter Attack 100%")},
    {QT_TR_NOOP("Slash-All"),QT_TR_NOOP("Flash"),QT_TR_NOOP("Mastered"),"",""},{QT_TR_NOOP("2x-Cut"),QT_TR_NOOP("4x-Cut"),QT_TR_NOOP("Mastered"),"",""},
    {QT_TR_NOOP("Cover +20%"),QT_TR_NOOP("Cover +40%"),QT_TR_NOOP("Cover +60%"),QT_TR_NOOP("Cover +80%"),QT_TR_NOOP("Cover +100%")},{QT_TR_NOOP("Underwater"),"","","",""},
    {QT_TR_NOOP("HP <-> MP"),QT_TR_NOOP("Mastered"),"","",""},{QT_TR_NOOP("W-Magic"),QT_TR_NOOP("Mastered"),"","",""},{QT_TR_NOOP("W-Summon"),QT_TR_NOOP("Mastered"),"","",""},
    {QT_TR_NOOP("W-Item"),QT_TR_NOOP("Mastered"),"","",""},{"?","?","?","?","?"},{QT_TR_NOOP("All x1"),QT_TR_NOOP("All x2"),QT_TR_NOOP("All x3"),QT_TR_NOOP("All x4"),QT_TR_NOOP("All x5")},
    {QT_TR_NOOP("Counter Rate %20"),QT_TR_NOOP("Counter Rate %40"),QT_TR_NOOP("Counter Rate %60"),QT_TR_NOOP("Counter Rate %80"),QT_TR_NOOP("Counter Rate %100")},
    {QT_TR_NOOP("Magic Counter Rate %30"),QT_TR_NOOP("Magic Counter Rate %40"),QT_TR_NOOP("Magic Counter Rate %60"),QT_TR_NOOP("Magic Counter Rate %80"),QT_TR_NOOP("Magic Counter Rate %100")},
    {QT_TR_NOOP("MP Turbo 10%"),QT_TR_NOOP("Mp Turbo 20%"),QT_TR_NOOP("Mp Turbo 30%"),QT_TR_NOOP("Mp Turbo 40%"),QT_TR_NOOP("Mp Turbo 50%")},{QT_TR_NOOP("MP Absorb"),QT_TR_NOOP("Mastered"),"","",""},
    {QT_TR_NOOP("HP Absorb"),QT_TR_NOOP("Mastered"),"","",""},{QT_TR_NOOP("Elemental 50%"),QT_TR_NOOP("Elemental 100%"),QT_TR_NOOP("Elemental 200%"),QT_TR_NOOP("Mastered"),""},
    {QT_TR_NOOP("Added Effect"),QT_TR_NOOP("Mastered"),"","",""},{QT_TR_NOOP("Sneak Attack 20%"),QT_TR_NOOP("Sneak Attack 35%"),QT_TR_NOOP("Sneak Attack 50%"),QT_TR_NOOP("Sneak Attack 65%"),QT_TR_NOOP("Sneak Attack 80%")},
    {QT_TR_NOOP("Final Attack x1"),QT_TR_NOOP("Final Attack x2"),QT_TR_NOOP("Final Attack x3"),QT_TR_NOOP("Final Attack x4"),QT_TR_NOOP("Final Attack x5")},{QT_TR_NOOP("Added Cut"),QT_TR_NOOP("Mastered"),"","",""},
    {QT_TR_NOOP("Steal-As-Well"),QT_TR_NOOP("Mastered"),"","",""},{QT_TR_NOOP("Quadra Magic x1"),QT_TR_NOOP("Quadra Magic x2"),QT_TR_NOOP("Quadra Magic x3"),QT_TR_NOOP("Quadra Magic x4"),QT_TR_NOOP("Quadra Magic x5")},
    {QT_TR_NOOP("Steal"),QT_TR_NOOP("Mug"),QT_TR_NOOP("Mastered"),"",""},{QT_TR_NOOP("Sence"),QT_TR_NOOP("Mastered"),"","",""},{"?","?","?","?","?"},{QT_TR_NOOP("Throw"),QT_TR_NOOP("Coin"),QT_TR_NOOP("Mastered"),"",""},
    {QT_TR_NOOP("Morph"),QT_TR_NOOP("Mastered"),"","",""},{QT_TR_NOOP("DeathBlow"),QT_TR_NOOP("Mastered"),"","",""},{QT_TR_NOOP("Manipulate"),QT_TR_NOOP("Mastered"),"","",""},{QT_TR_NOOP("Mime"),QT_TR_NOOP("Mastered"),"","",""},
    {QT_TR_NOOP("Enemy Skill"),"","","",""},{"?","?","?","?","?"},{"?","?","?","?","?"},{"?","?","?","?","?"},{QT_TR_NOOP("Master Command"),"","","",""},{QT_TR_NOOP("Fire (4mp)"),QT_TR_NOOP("Fire2 (22mp)"),QT_TR_NOOP("Fire3 (52mp)"),QT_TR_NOOP("Mastered"),""},
    {QT_TR_NOOP("Ice (4mp)"),QT_TR_NOOP("Ice2 (22mp)"),QT_TR_NOOP("Ice3 (52mp)"),QT_TR_NOOP("Mastered"),""},{QT_TR_NOOP("Quake (6mp)"),QT_TR_NOOP("Quake2 (28mp)"),QT_TR_NOOP("Quake3 (68mp)"),QT_TR_NOOP("Mastered"),""},{QT_TR_NOOP("Bolt (4mp)"),QT_TR_NOOP("Bolt2 (22mp)"),QT_TR_NOOP("Bolt3(52mp)"),QT_TR_NOOP("Mastered"),""},{QT_TR_NOOP("Cure (5mp)"),QT_TR_NOOP("Cure2 (24mp)"),QT_TR_NOOP("Regen(30mp)"),QT_TR_NOOP("Cure3 (64mp)"),QT_TR_NOOP("Mastered")},{QT_TR_NOOP("Poisona (3mp)"),QT_TR_NOOP("Esuna (15mp)"),QT_TR_NOOP("Resist (120mp)"),QT_TR_NOOP("Mastered"),""},{QT_TR_NOOP("Life (34mp)"),QT_TR_NOOP("Life2 (100mp)"),QT_TR_NOOP("Mastered"),"",""},{QT_TR_NOOP("Sleepel (8mp)"),QT_TR_NOOP("Silence (24mp)"),QT_TR_NOOP("Mastered"),"",""},{QT_TR_NOOP("Confuse (18mp)"),QT_TR_NOOP("Berserk (24mp)"),QT_TR_NOOP("Mastered"),"",""},{QT_TR_NOOP("Mini (10mp)"),QT_TR_NOOP("Toad (14mp)"),QT_TR_NOOP("Mastered"),"",""},
    {QT_TR_NOOP("Exit (16mp)"),QT_TR_NOOP("Remove (99mp)"),QT_TR_NOOP("Mastered"),"",""},{QT_TR_NOOP("Bio (8mp)"),QT_TR_NOOP("Bio2 (36mp)"),QT_TR_NOOP("Bio3 (80mp)"),QT_TR_NOOP("Mastered"),""},
    {QT_TR_NOOP("Demi (14mp)"),QT_TR_NOOP("Demi2 (33mp)"),QT_TR_NOOP("Demi3 (48mp)"),QT_TR_NOOP("Mastered"),""},{QT_TR_NOOP("Barrier (16mp)"),QT_TR_NOOP("Magic Barrier (24mp)"),QT_TR_NOOP("Reflect (30mp)"),QT_TR_NOOP("Wall (58mp)"),QT_TR_NOOP("Mastered")},
    {"?","?","?","?","?"},{QT_TR_NOOP("Comet (70mp)"),QT_TR_NOOP("Comet2 (110mp)"),QT_TR_NOOP("Mastered"),"",""},{QT_TR_NOOP("Haste (18mp)"),QT_TR_NOOP("Slow (20mp)"),QT_TR_NOOP("Stop (34mp)"),QT_TR_NOOP("Mastered"),""},{"?","?","?","?","?"},{"?","?","?","?","?"},{QT_TR_NOOP("DeBarrier (12mp)"),QT_TR_NOOP("DeSpell (20mp)"),QT_TR_NOOP("Death (30mp)"),QT_TR_NOOP("Mastered"),""},{QT_TR_NOOP("Freeze (82mp)"),QT_TR_NOOP("Break (86mp)"),QT_TR_NOOP("Tornado (90mp)"),QT_TR_NOOP("Flare(100mp)"),QT_TR_NOOP("Mastered")},{"",QT_TR_NOOP("Full Cure (99mp)"),QT_TR_NOOP("Mastered"),"",""},{"",QT_TR_NOOP("Shield (180mp)"),QT_TR_NOOP("Mastered"),"",""},{"",QT_TR_NOOP("Ultima (130mp)"),QT_TR_NOOP("Mastered"),"",""},{QT_TR_NOOP("Master Magic"),"","","",""},
    {QT_TR_NOOP("Summon Choco/Mog x1 (14mp)"),QT_TR_NOOP("Summon Choco/Mog x2 (14mp)"),QT_TR_NOOP("Summon Choco/Mog x3 (14mp)"),QT_TR_NOOP("Summon Choco/Mog x4 (14mp)"),QT_TR_NOOP("Summon Choco/Mog x5 (14mp)")},{QT_TR_NOOP("Summon Shiva x1 (34mp)"),QT_TR_NOOP("Summon Shiva x2 (34mp)"),QT_TR_NOOP("Summon Shiva x3 (34mp)"),QT_TR_NOOP("Summon Shiva x4 (34mp)"),QT_TR_NOOP("Summon Shiva x5 (34mp)")},{QT_TR_NOOP("Summon Ifrit x1 (34mp)"),QT_TR_NOOP("Summon Ifrit x2 (34mp)"),QT_TR_NOOP("Summon Ifrit x3 (34mp)"),QT_TR_NOOP("Summon Ifrit x4 (34mp)"),QT_TR_NOOP("Summon Ifrit x5 (34mp)")},{QT_TR_NOOP("Summon Ramuh x1 (40mp)"),QT_TR_NOOP("Summon Ramuh x2 (40mp)"),QT_TR_NOOP("Summon Ramuh x3 (40mp)"),QT_TR_NOOP("Summon Ramuh x4 (40mp)"),QT_TR_NOOP("Summon Ramuh x5 (40mp)")},
    {QT_TR_NOOP("Summon Titan x1 (46mp)"),QT_TR_NOOP("Summon Titan x2 (46mp)"),QT_TR_NOOP("Summon Titan x3 (46mp)"),QT_TR_NOOP("Summon Titan x4 (46mp)"),QT_TR_NOOP("Summon Titan x5 (46mp)")},{QT_TR_NOOP("Summon Odin x1 (80mp)"),QT_TR_NOOP("Summon Odin x2 (80mp)"),QT_TR_NOOP("Summon Odin x3 (80mp)"),QT_TR_NOOP("Summon Odin x4 (80mp)"),QT_TR_NOOP("Summon Odin x5 (80mp)")},
    {QT_TR_NOOP("Summon Leviathan x1 (78mp)"),QT_TR_NOOP("Summon Leviathan x2 (78mp)"),QT_TR_NOOP("Summon Leviathan x3 (78mp)"),QT_TR_NOOP("Summon Leviathan x4 (78mp)"),QT_TR_NOOP("Summon Leviathan x5 (78mp)")},
    {QT_TR_NOOP("Summon Bahamut x1 (100mp)"),QT_TR_NOOP("Summon Bahamut x2 (100mp)"),QT_TR_NOOP("Summon Bahamut x3 (100mp)"),QT_TR_NOOP("Summon Bahamut x4 (100mp)"),QT_TR_NOOP("Summon Bahamut x5 (100mp)")},
    {QT_TR_NOOP("Summon Kujata x1 (110mp)"),QT_TR_NOOP("Summon Kujata x2 (110mp)"),QT_TR_NOOP("Summon Kujata x3 (110mp)"),QT_TR_NOOP("Summon Kujata x4 (110mp)"),QT_TR_NOOP("Summon Kujata x5 (110mp)")},
    {QT_TR_NOOP("Summon Alexander x1 (120mp)"),QT_TR_NOOP("Summon Alexander x2 (120mp)"),QT_TR_NOOP("Summon Alexander x3 (120mp)"),QT_TR_NOOP("Summon Alexander x4 (120mp)"),QT_TR_NOOP("Summon Alexander x5 (120mp)")},
    {QT_TR_NOOP("Summon Phoenix x1 (180mp)"),QT_TR_NOOP("Summon Phoenix x2 (180mp)"),QT_TR_NOOP("Summon Phoenix x3 (180mp)"),QT_TR_NOOP("Summon Phoenix x4 (180mp)"),QT_TR_NOOP("Summon Phoenix x5 (180mp)")},
    {QT_TR_NOOP("Summon Neo Bahamut x1 (140mp)"),QT_TR_NOOP("Summon Neo Bahamut x2 (140mp)"),QT_TR_NOOP("Summon Neo Bahamut x3 (140mp)"),QT_TR_NOOP("Summon Neo Bahamut x4 (140mp)"),QT_TR_NOOP("Summon Neo Bahamut x5 (140mp)")},
    {QT_TR_NOOP("Summon Hades x1 (150mp)"),QT_TR_NOOP("Summon Hades x2 (150mp)"),QT_TR_NOOP("Summon Hades x3 (150mp)"),QT_TR_NOOP("Summon Hades x4 (150mp)"),QT_TR_NOOP("Summon Hades x5 (150mp)")},
    {QT_TR_NOOP("Summon Typhoon x1 (160mp)"),QT_TR_NOOP("Summon Typhoon x2 (160mp)"),QT_TR_NOOP("Summon Typhoon x3 (160mp)"),QT_TR_NOOP("Summon Typhoon x4 (160mp)"),QT_TR_NOOP("Summon Typhoon x5 (160mp)")},
    {QT_TR_NOOP("Summon Bahamut ZERO x1 (180mp)"),QT_TR_NOOP("Summon Bahamut ZERO x2 (180mp)"),QT_TR_NOOP("Summon Bahamut ZERO x3 (180mp)"),QT_TR_NOOP("Summon Bahamut ZERO x4 (180mp)"),QT_TR_NOOP("Summon Bahamut ZERO x5 (180mp)")},
    {QT_TR_NOOP("Summon KOTR x1 (250mp)"),QT_TR_NOOP("Summon KOTR x2 (250mp)"),QT_TR_NOOP("Summon KOTR x3 (250mp)"),QT_TR_NOOP("Summon KOTR x4 (250mp)"),QT_TR_NOOP("Summon KOTR x5 (250mp)")},{QT_TR_NOOP("Master Summon"),"","","",""}
};
QString ff7names::ItemNames(int i){return QObject::tr(itemNames[i]);}
QString ff7names::MateriaNames(int i){return QObject::tr(materiaNames[i]);}
QString ff7names::MateriaStats(int i){return QObject::tr(materiaStats[i]);}
QString ff7names::MateriaSkills(int i,int l){return QObject::tr(materiaSkills[i][l]);}
