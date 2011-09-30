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

void fix_pc_bytemask(FF7 &ff7,int s)
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

void fix_psx_header(FF7 &ff7,int i)
{   //Time Has to be fixed in the header
    if((ff7.slot[i].time/3600)>99){ff7.hf[i].sl_header[27]=0x58;ff7.hf[i].sl_header[29]=0x58;}
    else
    {
        ff7.hf[i].sl_header[27] = ((ff7.slot[i].time/3600)/10)+0x4F;
        ff7.hf[i].sl_header[29] = ((ff7.slot[i].time/3600)%10)+0x4F;
    }
    ff7.hf[i].sl_header[33] = ((ff7.slot[i].time/60%60)/10)+0x4F;
    ff7.hf[i].sl_header[35] = ((ff7.slot[i].time/60%60)%10)+0x4F;
}

void fix_vmc_header(FF7 &ff7)
{//Set The Index Section Up.
    QByteArray mc_header_2;
    int index=2;

    if(ff7.savetype==5){for(int i=0; i<0x80; i++){mc_header_2.append(ff7.file_header_psp[i]);} index=0x82;}
    if(ff7.savetype==6){for(int i=0; i<0x40; i++){mc_header_2.append(ff7.file_header_vgs[i]);} index=0x42;}
    if(ff7.savetype==7){for(int i=0; i<0xF40; i++){mc_header_2.append(ff7.file_header_vgs[i]);} index=0xF42;}
    quint8 xor_byte = 0x00;
    mc_header_2.append("MC");
    if(ff7.savetype==3){for(int k=0; k<125;k++){mc_header_2.append(ff7.file_header_mc[k+index]);}}
    if(ff7.savetype==5){for(int k=0; k<125;k++){mc_header_2.append(ff7.file_header_psp[k+index]);}}
    if(ff7.savetype==6){for(int k=0; k<125;k++){mc_header_2.append(ff7.file_header_vgs[k+index]);}}
    if(ff7.savetype==7){for(int k=0; k<125;k++){mc_header_2.append(ff7.file_header_dex[k+index]);}}
    xor_byte= 0x00;
    if(ff7.savetype==3){for(int x=0;x<127;x++){xor_byte^=mc_header_2[x];}}
    if(ff7.savetype==5){for(int x=128;x<256;x++){xor_byte^=mc_header_2[x];}}
    if(ff7.savetype==6){for(int x=64;x<192;x++){xor_byte^=mc_header_2[x];}}
    if(ff7.savetype==7){for(int x=0xF40;x<0x1000;x++){xor_byte^=mc_header_2[x];}}
    //write xor byte..
    mc_header_2.append(xor_byte);
    // thats a normal header
    for(int i=0;i<15;i++)
    {
        //calc xor byte..
        index= (128 +(128*i));
        if(ff7.savetype==5){index+=0x80;}
        if(ff7.savetype==6){index+=0x40;}
        if(ff7.savetype==7){index+=0xF40;}
        if(ff7.SG_Region_String[i].contains("00867") ||ff7.SG_Region_String[i].contains("00869") ||
           ff7.SG_Region_String[i].contains("00900") ||ff7.SG_Region_String[i].contains("94163") ||
           ff7.SG_Region_String[i].contains("00700") ||ff7.SG_Region_String[i].contains("01057"))
        {
           QByteArray temp;
           temp.resize(10);
           temp[0]=0x51;temp[1]=0x00;temp[2]=0x00;temp[3]=0x00;temp[4]=0x00;
           temp[5]=0x20;temp[6]=0x00;temp[7]=0x00;temp[8]=0xFF;temp[9]=0xFF;
           mc_header_2.append(temp);
           mc_header_2.append(ff7.SG_Region_String[i]);
           temp.resize(98);
           for(int f=0;f<98;f++){temp[f]=0x00;}
           mc_header_2.append(temp);
           xor_byte = 0x00;
           for(int x=0;x<127;x++){xor_byte^=mc_header_2[x+index];}
           mc_header_2.append(xor_byte);

           if(ff7.SG_Region_String[i].endsWith("S01"))
           {
               for(int P=0;P<512;P++)
                {
                    if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S01[P];}
                    else{ff7.hf[i].sl_header[P]= 0x00;}
                }
           }
           if(ff7.SG_Region_String[i].endsWith("S02"))
           {
                for(int P=0;P<512;P++)
                {
                    if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S02[P];}
                    else{ff7.hf[i].sl_header[P]= 0x00;}
                }
           }
           if(ff7.SG_Region_String[i].endsWith("S03"))
           {
                for(int P=0;P<512;P++)
                {
                    if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S03[P];}
                    else{ff7.hf[i].sl_header[P]= 0x00;}
                }
           }
           if(ff7.SG_Region_String[i].endsWith("S04"))
           {
                for(int P=0;P<512;P++)
                {
                    if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S04[P];}
                    else{ff7.hf[i].sl_header[P]= 0x00;}
                }
           }
           if(ff7.SG_Region_String[i].endsWith("S05"))
           {
               for(int P=0;P<512;P++)
                {
                    if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S05[P];}
                    else{ff7.hf[i].sl_header[P]= 0x00;}
                }
           }
           if(ff7.SG_Region_String[i].endsWith("S06"))
           {
               for(int P=0;P<512;P++)
               {
                   if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S06[P];}
                   else{ff7.hf[i].sl_header[P]= 0x00;}
               }
           }
           if(ff7.SG_Region_String[i].endsWith("S07"))
           {
               for(int P=0;P<512;P++)
                {
                    if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S07[P];}
                    else{ff7.hf[i].sl_header[P]= 0x00;}
                }
           }
           if(ff7.SG_Region_String[i].endsWith("S08"))
           {
                for(int P=0;P<512;P++)
                {
                    if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S08[P];}
                    else{ff7.hf[i].sl_header[P]= 0x00;}
                }
           }
           if(ff7.SG_Region_String[i].endsWith("S09"))
           {
                for(int P=0;P<512;P++)
                {
                    if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S09[P];}
                    else{ff7.hf[i].sl_header[P]= 0x00;}
                }
           }
           if(ff7.SG_Region_String[i].endsWith("S10"))
           {
                for(int P=0;P<512;P++)
                {
                    if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S10[P];}
                    else{ff7.hf[i].sl_header[P]= 0x00;}
                }
           }
           if(ff7.SG_Region_String[i].endsWith("S11"))
           {
               for(int P=0;P<512;P++)
                {
                    if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S11[P];}
                    else{ff7.hf[i].sl_header[P]= 0x00;}
                }
           }
           if(ff7.SG_Region_String[i].endsWith("S12"))
           {
               for(int P=0;P<512;P++)
               {
                   if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S12[P];}
                   else{ff7.hf[i].sl_header[P]= 0x00;}
               }
           }
           if(ff7.SG_Region_String[i].endsWith("S13"))
           {
               for(int P=0;P<512;P++)
                {
                    if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S13[P];}
                    else{ff7.hf[i].sl_header[P]= 0x00;}
                }
           }
           if(ff7.SG_Region_String[i].endsWith("S14"))
           {
               for(int P=0;P<512;P++)
               {
                   if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S14[P];}
                   else{ff7.hf[i].sl_header[P]= 0x00;}
               }
           }
           if(ff7.SG_Region_String[i].endsWith("S15"))
           {
               for(int P=0;P<512;P++)
               {
                   if(P<256){ff7.hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S15[P];}
                   else{ff7.hf[i].sl_header[P]= 0x00;}
               }
           }
           fix_psx_header(ff7,i);//here ff7 is already a pointer to ff7 in mainwindow.
        } // write string if found
        else
        {//Write What Ever is in the Header (Non ff7 data)
            if(ff7.savetype==3){for(int j=0;j<128;j++){mc_header_2.append(ff7.file_header_mc[index+j]);}}
            if(ff7.savetype==5){for(int j=0;j<128;j++){mc_header_2.append(ff7.file_header_psp[index+j]);}}
            if(ff7.savetype==6){for(int j=0;j<128;j++){mc_header_2.append(ff7.file_header_vgs[index+j]);}}
            if(ff7.savetype==7){for(int j=0;j<128;j++){mc_header_2.append(ff7.file_header_dex[index+j]);}}
        }
    }

    if(ff7.savetype==3)
    {
        index=2048;
        for(int i=0;i<6143;i++){mc_header_2.append(ff7.file_header_mc[index+i]);}// fill the remainder
        memcpy(&ff7.file_header_mc,mc_header_2,0x2000);
    }
    if(ff7.savetype==5)
    {
        index=2048+0x80;
        for(int i=0;i<6143;i++){mc_header_2.append(ff7.file_header_psp[index+i]);}// fill the remainder
        memcpy(&ff7.file_header_psp,mc_header_2,0x2080);
        //PUT PSP CHECKSUMING HERE ..
    }
    if(ff7.savetype==6)
    {
        index=2048+0x40;
        for(int i=0;i<6143;i++){mc_header_2.append(ff7.file_header_vgs[index+i]);}// fill the remainder
        memcpy(&ff7.file_header_psp,mc_header_2,0x2040);
    }
    if(ff7.savetype==7)
    {
        index=2048+0xF40;
        for(int i=0;i<6143;i++){mc_header_2.append(ff7.file_header_dex[index+i]);}// fill the remainder
        memcpy(&ff7.file_header_psp,mc_header_2,0x2F40);
    }
}

QString avatar_style(int id)
{
    QString style;
    switch(id)
    {
      case 0:
        style="image: url(:/icon/cloud_icon)";
        break;
      case 1:
        style="image: url(:/icon/barret_icon)";
        break;
      case 2:
        style="image: url(:/icon/tifa_icon)";
        break;
      case 3:
        style="image: url(:/icon/aeris_icon)";
        break;
      case 4:
        style="image: url(:/icon/red_icon)";
        break;
      case 5:
        style="image: url(:/icon/yuffie_icon)";
        break;
      case 6:
        style="image: url(:/icon/cait_icon)";
        break;
      case 7:
        style="image: url(:/icon/vincent_icon)";
        break;
      case 8:
        style="image: url(:/icon/cid_icon)";
        break;
      case 9:
        style="image: url(:/icon/y_cloud_icon)";
        break;
      case 10:
        style="image: url(:/icon/sep_icon)";
        break;
      }
    return style;
}
/* STATIC STRINGS FOR TRANSLATION */
static const char *itemNames[]=
{   // 0-105 "normal" items
    QT_TRANSLATE_NOOP("Items","Potion"),QT_TRANSLATE_NOOP("Items","Hi-Potion"),QT_TRANSLATE_NOOP("Items","X-Potion"),QT_TRANSLATE_NOOP("Items","Ether"),QT_TRANSLATE_NOOP("Items","Turbo Ether"),QT_TRANSLATE_NOOP("Items","Elixir"),QT_TRANSLATE_NOOP("Items","Megalixir"),QT_TRANSLATE_NOOP("Items","Phoenix Down"),
    QT_TRANSLATE_NOOP("Items","Antidote"),QT_TRANSLATE_NOOP("Items","Soft"),QT_TRANSLATE_NOOP("Items","Maiden's Kiss"),QT_TRANSLATE_NOOP("Items","Cornucopia"),QT_TRANSLATE_NOOP("Items","Echo screen"),QT_TRANSLATE_NOOP("Items","Hyper"),QT_TRANSLATE_NOOP("Items","Tranquilizer"),QT_TRANSLATE_NOOP("Items","Remedy"),
    QT_TRANSLATE_NOOP("Items","Smoke Bomb"),QT_TRANSLATE_NOOP("Items","Speed Drink"),QT_TRANSLATE_NOOP("Items","Hero Drink"),QT_TRANSLATE_NOOP("Items","Vaccine"),QT_TRANSLATE_NOOP("Items","Grenade"),QT_TRANSLATE_NOOP("Items","Shrapnel"),QT_TRANSLATE_NOOP("Items","Right arm"),QT_TRANSLATE_NOOP("Items","Hourglass"),
    QT_TRANSLATE_NOOP("Items","Kiss of Death"),QT_TRANSLATE_NOOP("Items","Spider Web"),QT_TRANSLATE_NOOP("Items","Dream Powder"),QT_TRANSLATE_NOOP("Items","Mute Mask"),QT_TRANSLATE_NOOP("Items","War Gong"),QT_TRANSLATE_NOOP("Items","Loco weed"),QT_TRANSLATE_NOOP("Items","Fire Fang"),QT_TRANSLATE_NOOP("Items","Fire Veil"),
    QT_TRANSLATE_NOOP("Items","Antarctic Wind"),QT_TRANSLATE_NOOP("Items","Ice Crystal"),QT_TRANSLATE_NOOP("Items","Bolt Plume"),QT_TRANSLATE_NOOP("Items","Swift Bolt"),QT_TRANSLATE_NOOP("Items","Earth Drum"),QT_TRANSLATE_NOOP("Items","Earth Mallet"),QT_TRANSLATE_NOOP("Items","Deadly Waste"),QT_TRANSLATE_NOOP("Items","M-Tentacles"),
    QT_TRANSLATE_NOOP("Items","Stardust"),QT_TRANSLATE_NOOP("Items","Vampire Fang"),QT_TRANSLATE_NOOP("Items","Ghost Hand"),QT_TRANSLATE_NOOP("Items","Vagyrisk Claw"),QT_TRANSLATE_NOOP("Items","Light Curtain"),QT_TRANSLATE_NOOP("Items","Lunar Curtain"),QT_TRANSLATE_NOOP("Items","Mirror"),QT_TRANSLATE_NOOP("Items","Holy Torch"),
    QT_TRANSLATE_NOOP("Items","Bird Wing"),QT_TRANSLATE_NOOP("Items","Dragon Scales"),QT_TRANSLATE_NOOP("Items","Impaler"),QT_TRANSLATE_NOOP("Items","Shrivel"),QT_TRANSLATE_NOOP("Items","Eye drop"),QT_TRANSLATE_NOOP("Items","Molotov"),QT_TRANSLATE_NOOP("Items","S-mine"),QT_TRANSLATE_NOOP("Items","8-inch Cannon"),
    QT_TRANSLATE_NOOP("Items","Graviball"),QT_TRANSLATE_NOOP("Items","T/S Bomb"),QT_TRANSLATE_NOOP("Items","Ink"),QT_TRANSLATE_NOOP("Items","Dazers"),QT_TRANSLATE_NOOP("Items","Dragon Fang"),QT_TRANSLATE_NOOP("Items","Cauldron"),QT_TRANSLATE_NOOP("Items","Sylkis Greens"),QT_TRANSLATE_NOOP("Items","Reagan Greens"),
    QT_TRANSLATE_NOOP("Items","Mimett Greens"),QT_TRANSLATE_NOOP("Items","Curiel Greens"),QT_TRANSLATE_NOOP("Items","Pahsana Greens"),QT_TRANSLATE_NOOP("Items","Tantal Greens"),QT_TRANSLATE_NOOP("Items","Krakka Greens"),QT_TRANSLATE_NOOP("Items","Gysahl Greens"),QT_TRANSLATE_NOOP("Items","Tent"),QT_TRANSLATE_NOOP("Items","Power Source"),
    QT_TRANSLATE_NOOP("Items","Guard Source"),QT_TRANSLATE_NOOP("Items","Magic Source"),QT_TRANSLATE_NOOP("Items","Mind Source"),QT_TRANSLATE_NOOP("Items","Speed Source"),QT_TRANSLATE_NOOP("Items","Luck Source"),QT_TRANSLATE_NOOP("Items","Zeio Nut"),QT_TRANSLATE_NOOP("Items","Carob Nut"),QT_TRANSLATE_NOOP("Items","Porov Nut"),
    QT_TRANSLATE_NOOP("Items","Pram Nut"),QT_TRANSLATE_NOOP("Items","Lasan Nut"),QT_TRANSLATE_NOOP("Items","Saraha Nut"),QT_TRANSLATE_NOOP("Items","Luchile Nut"),QT_TRANSLATE_NOOP("Items","Pepio Nut"),QT_TRANSLATE_NOOP("Items","Battery"),QT_TRANSLATE_NOOP("Items","Tissue"),QT_TRANSLATE_NOOP("Items","Omnislash"),
    QT_TRANSLATE_NOOP("Items","Catastrophe"),QT_TRANSLATE_NOOP("Items","Final Heaven"),QT_TRANSLATE_NOOP("Items","Great Gospel"),QT_TRANSLATE_NOOP("Items","Cosmo Memory"),QT_TRANSLATE_NOOP("Items","All Creation"),QT_TRANSLATE_NOOP("Items","Chaos"),QT_TRANSLATE_NOOP("Items","Highwind"),QT_TRANSLATE_NOOP("Items","1/35 soldier"),
    QT_TRANSLATE_NOOP("Items","Super Sweeper"),QT_TRANSLATE_NOOP("Items","Masamune Blade"),QT_TRANSLATE_NOOP("Items","Save Crystal"),QT_TRANSLATE_NOOP("Items","Combat Diary"),QT_TRANSLATE_NOOP("Items","Autograph"),QT_TRANSLATE_NOOP("Items","Gambler"),QT_TRANSLATE_NOOP("Items","Desert Rose"),QT_TRANSLATE_NOOP("Items","Earth Harp"),
    QT_TRANSLATE_NOOP("Items","Guide Book"),
    //nothing 106-127
    QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),
    QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),
    QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),QT_TRANSLATE_NOOP("Items","DON'T USE"),
    //cloud weapons 128 -143
    QT_TRANSLATE_NOOP("Items","Buster Sword"),QT_TRANSLATE_NOOP("Items","Mythril Saber"),QT_TRANSLATE_NOOP("Items","Hardedge"),QT_TRANSLATE_NOOP("Items","Butterfly Edge"),QT_TRANSLATE_NOOP("Items","Enhance Sword"),QT_TRANSLATE_NOOP("Items","Organics"),QT_TRANSLATE_NOOP("Items","Crystal Sword"),QT_TRANSLATE_NOOP("Items","Force Stealer"),
    QT_TRANSLATE_NOOP("Items","Rune Blade"),QT_TRANSLATE_NOOP("Items","Murasame"),QT_TRANSLATE_NOOP("Items","Nail Bat"),QT_TRANSLATE_NOOP("Items","Yoshiyuki"),QT_TRANSLATE_NOOP("Items","Apocalypse"),QT_TRANSLATE_NOOP("Items","Heaven's Cloud"),QT_TRANSLATE_NOOP("Items","Ragnarok"),QT_TRANSLATE_NOOP("Items","Ultima Weapon"),
    //tifa's weapons 144-159
    QT_TRANSLATE_NOOP("Items","Leather Glove"),QT_TRANSLATE_NOOP("Items","Metal Knuckle"),QT_TRANSLATE_NOOP("Items","Mythril Claw"),QT_TRANSLATE_NOOP("Items","Grand Glove"),QT_TRANSLATE_NOOP("Items","Tiger Fang"),QT_TRANSLATE_NOOP("Items","Diamond Knuckle"),QT_TRANSLATE_NOOP("Items","Dragon Claw"),QT_TRANSLATE_NOOP("Items","Crystal Glove"),
    QT_TRANSLATE_NOOP("Items","Motor Drive"),QT_TRANSLATE_NOOP("Items","Platinum Fist"),QT_TRANSLATE_NOOP("Items","Kaiser Knuckle"),QT_TRANSLATE_NOOP("Items","Work Glove"),QT_TRANSLATE_NOOP("Items","Powersoul"),QT_TRANSLATE_NOOP("Items","Master Fist"),QT_TRANSLATE_NOOP("Items","God's Hand"),QT_TRANSLATE_NOOP("Items","Premium Heart"),
    // barret's weapons 160-175
    QT_TRANSLATE_NOOP("Items","Gatling Gun"),QT_TRANSLATE_NOOP("Items","Assault Gun"),QT_TRANSLATE_NOOP("Items","Cannon Ball"),QT_TRANSLATE_NOOP("Items","Atomic Scissors"),QT_TRANSLATE_NOOP("Items","Heavy Vulcan"),QT_TRANSLATE_NOOP("Items","Chainsaw"),QT_TRANSLATE_NOOP("Items","Microlaser"),QT_TRANSLATE_NOOP("Items","A▪M Cannon"),
    QT_TRANSLATE_NOOP("Items","W Machine Gun"),QT_TRANSLATE_NOOP("Items","Drill Arm"),QT_TRANSLATE_NOOP("Items","Solid Bazooka"),QT_TRANSLATE_NOOP("Items","Rocket Punch"),QT_TRANSLATE_NOOP("Items","Enemy Launcher"),QT_TRANSLATE_NOOP("Items","Pile Banger"),QT_TRANSLATE_NOOP("Items","Max Ray"),QT_TRANSLATE_NOOP("Items","Missing Score"),
    //red's weapons 176-189
    QT_TRANSLATE_NOOP("Items","Mythril Clip"),QT_TRANSLATE_NOOP("Items","Diamond Pin"),QT_TRANSLATE_NOOP("Items","Silver Barette"),QT_TRANSLATE_NOOP("Items","Gold Barette"),QT_TRANSLATE_NOOP("Items","Adaman Clip"),QT_TRANSLATE_NOOP("Items","Crystal Comb"),QT_TRANSLATE_NOOP("Items","Magic Comb"),QT_TRANSLATE_NOOP("Items","Plus Barrette"),
    QT_TRANSLATE_NOOP("Items","Centclip"),QT_TRANSLATE_NOOP("Items","Hairpin"),QT_TRANSLATE_NOOP("Items","Seraph Comb"),QT_TRANSLATE_NOOP("Items","Behemoth Horn"),QT_TRANSLATE_NOOP("Items","Spring Gun Clip"),QT_TRANSLATE_NOOP("Items","Limited Moon"),
    //aeris weapons 190-200
    QT_TRANSLATE_NOOP("Items","Guard Stick"),QT_TRANSLATE_NOOP("Items","Mythril Rod"),QT_TRANSLATE_NOOP("Items","Full Metal Staff"),QT_TRANSLATE_NOOP("Items","Striking Staff"),QT_TRANSLATE_NOOP("Items","Prism Staff"),QT_TRANSLATE_NOOP("Items","Aurora Rod"),QT_TRANSLATE_NOOP("Items","Wizard Staff"),QT_TRANSLATE_NOOP("Items","Wizer Staff"),
    QT_TRANSLATE_NOOP("Items","Fairy Tale"),QT_TRANSLATE_NOOP("Items","Umbrella"),QT_TRANSLATE_NOOP("Items","Princess Guard"),
    //cid weapons 201-214
    QT_TRANSLATE_NOOP("Items","Spear"),QT_TRANSLATE_NOOP("Items","Slash Lance"),QT_TRANSLATE_NOOP("Items","Trident"),QT_TRANSLATE_NOOP("Items","Mast Ax"),QT_TRANSLATE_NOOP("Items","Partisan"),QT_TRANSLATE_NOOP("Items","Viper Halberd"),QT_TRANSLATE_NOOP("Items","Javelin"),QT_TRANSLATE_NOOP("Items","Grow Lance"),QT_TRANSLATE_NOOP("Items","Mop"),
    QT_TRANSLATE_NOOP("Items","Dragoon Lance"),QT_TRANSLATE_NOOP("Items","Scimitar"),QT_TRANSLATE_NOOP("Items","Flayer"),QT_TRANSLATE_NOOP("Items","Spirit Lance"),QT_TRANSLATE_NOOP("Items","Venus Gospel"),
    //yuffie weapons 215-228
    QT_TRANSLATE_NOOP("Items","4-point Shuriken"),QT_TRANSLATE_NOOP("Items","Boomerang"),QT_TRANSLATE_NOOP("Items","Pinwheel"),QT_TRANSLATE_NOOP("Items","Razor Ring"),QT_TRANSLATE_NOOP("Items","Hawkeye"),QT_TRANSLATE_NOOP("Items","Crystal Cross"),QT_TRANSLATE_NOOP("Items","Wind Slash"),QT_TRANSLATE_NOOP("Items","Twin Viper"),
    QT_TRANSLATE_NOOP("Items","Spiral Shuriken"),QT_TRANSLATE_NOOP("Items","Superball"),QT_TRANSLATE_NOOP("Items","Magic Shuriken"),QT_TRANSLATE_NOOP("Items","Rising Sun"),QT_TRANSLATE_NOOP("Items","Oritsuru"),QT_TRANSLATE_NOOP("Items","Conformer"),
    //cait sith weapons 229-241
    QT_TRANSLATE_NOOP("Items","Yellow M-phone"),QT_TRANSLATE_NOOP("Items","Green M-phone"),QT_TRANSLATE_NOOP("Items","Blue M-phone"),QT_TRANSLATE_NOOP("Items","Red M-phone"),QT_TRANSLATE_NOOP("Items","Crystal M-phone"),QT_TRANSLATE_NOOP("Items","White M-phone"),QT_TRANSLATE_NOOP("Items","Black M-phone"),QT_TRANSLATE_NOOP("Items","Silver M-phone"),
    QT_TRANSLATE_NOOP("Items","Trumpet Shell"),QT_TRANSLATE_NOOP("Items","Gold M-phone"),QT_TRANSLATE_NOOP("Items","Battle Trumpet"),QT_TRANSLATE_NOOP("Items","Starlight Phone"),QT_TRANSLATE_NOOP("Items","HP Shout"),
    //vincent weapons... 242-254
    QT_TRANSLATE_NOOP("Items","Quicksilver"),QT_TRANSLATE_NOOP("Items","Shotgun"),QT_TRANSLATE_NOOP("Items","Shortbarrel"),QT_TRANSLATE_NOOP("Items","Lariat"),QT_TRANSLATE_NOOP("Items","Winchester"),QT_TRANSLATE_NOOP("Items","Peacemaker"),QT_TRANSLATE_NOOP("Items","Buntline"),QT_TRANSLATE_NOOP("Items","Long Barrel R"),
    QT_TRANSLATE_NOOP("Items","Silver Rifle"),QT_TRANSLATE_NOOP("Items","Sniper CR"),QT_TRANSLATE_NOOP("Items","Supershot ST"),QT_TRANSLATE_NOOP("Items","Outsider"),QT_TRANSLATE_NOOP("Items","Death Penalty"),
    //sepi weapon =255
    QT_TRANSLATE_NOOP("Items","Masamune"),
    //armor  256-287
    QT_TRANSLATE_NOOP("Items","Bronze Bangle"),QT_TRANSLATE_NOOP("Items","Iron Bangle"),QT_TRANSLATE_NOOP("Items","Titan Bangle"),QT_TRANSLATE_NOOP("Items","Mythril Armlet"),QT_TRANSLATE_NOOP("Items","Carbon Bangle"),QT_TRANSLATE_NOOP("Items","Silver Armlet"),QT_TRANSLATE_NOOP("Items","Gold Armlet"),QT_TRANSLATE_NOOP("Items","Diamond Bangle"),
    QT_TRANSLATE_NOOP("Items","Crystal Bangle"),QT_TRANSLATE_NOOP("Items","Platinum Bangle"),QT_TRANSLATE_NOOP("Items","Rune Armlet"),QT_TRANSLATE_NOOP("Items","Edincoat"),QT_TRANSLATE_NOOP("Items","Wizard Bracelet"),QT_TRANSLATE_NOOP("Items","Adaman Bangle"),QT_TRANSLATE_NOOP("Items","Gigas Armlet"),QT_TRANSLATE_NOOP("Items","Imperial Guard"),
    QT_TRANSLATE_NOOP("Items","Aegis Armlet"),QT_TRANSLATE_NOOP("Items","Fourth Bracelet"),QT_TRANSLATE_NOOP("Items","Warrior Bangle"),QT_TRANSLATE_NOOP("Items","Shinra Beta"),QT_TRANSLATE_NOOP("Items","Shinra Alpha"),QT_TRANSLATE_NOOP("Items","Four Slots"),QT_TRANSLATE_NOOP("Items","Fire Armlet"),QT_TRANSLATE_NOOP("Items","Aurora Armlet"),
    QT_TRANSLATE_NOOP("Items","Bolt Armlet"),QT_TRANSLATE_NOOP("Items","Dragon Armlet"),QT_TRANSLATE_NOOP("Items","Minerva Band"),QT_TRANSLATE_NOOP("Items","Escort Guard"),QT_TRANSLATE_NOOP("Items","Mystile"),QT_TRANSLATE_NOOP("Items","Ziedrich"),QT_TRANSLATE_NOOP("Items","Precious Watch"),QT_TRANSLATE_NOOP("Items","Chocobracelet"),
    //accessorys 288-319
    QT_TRANSLATE_NOOP("Items","Power Wrist"),QT_TRANSLATE_NOOP("Items","Protect Vest"),QT_TRANSLATE_NOOP("Items","Earring"),QT_TRANSLATE_NOOP("Items","Talisman"),QT_TRANSLATE_NOOP("Items","Choco Feather"),QT_TRANSLATE_NOOP("Items","Amulet"),QT_TRANSLATE_NOOP("Items","Champion Belt"),QT_TRANSLATE_NOOP("Items","Poison Ring"),
    QT_TRANSLATE_NOOP("Items","Tough Ring"),QT_TRANSLATE_NOOP("Items","Circlet"),QT_TRANSLATE_NOOP("Items","Star Pendant"),QT_TRANSLATE_NOOP("Items","Silver Glasses"),QT_TRANSLATE_NOOP("Items","Headband"),QT_TRANSLATE_NOOP("Items","Fairy Ring"),QT_TRANSLATE_NOOP("Items","Jem Ring"),QT_TRANSLATE_NOOP("Items","White Cape"),
    QT_TRANSLATE_NOOP("Items","Sprint Shoes"),QT_TRANSLATE_NOOP("Items","Peace Ring"),QT_TRANSLATE_NOOP("Items","Ribbon"),QT_TRANSLATE_NOOP("Items","Fire Ring"),QT_TRANSLATE_NOOP("Items","Ice Ring"),QT_TRANSLATE_NOOP("Items","Bolt Ring"),QT_TRANSLATE_NOOP("Items","Tetra Elemental"),QT_TRANSLATE_NOOP("Items","Safety Bit"),
    QT_TRANSLATE_NOOP("Items","Fury Ring"),QT_TRANSLATE_NOOP("Items","Curse Ring"),QT_TRANSLATE_NOOP("Items","Protect Ring"),QT_TRANSLATE_NOOP("Items","Cat's Bell"),QT_TRANSLATE_NOOP("Items","Reflect Ring"),QT_TRANSLATE_NOOP("Items","Water Ring"),QT_TRANSLATE_NOOP("Items","Sneak Glove"),QT_TRANSLATE_NOOP("Items","HypnoCrown")
};
static const char *materiaNames[]=
{
    QT_TRANSLATE_NOOP("Materia_Names","MP Plus"),QT_TRANSLATE_NOOP("Materia_Names","HP Plus"),QT_TRANSLATE_NOOP("Materia_Names","Speed Plus"),QT_TRANSLATE_NOOP("Materia_Names","Magic Plus"),QT_TRANSLATE_NOOP("Materia_Names","Luck Plus"),QT_TRANSLATE_NOOP("Materia_Names","EXP Plus"),QT_TRANSLATE_NOOP("Materia_Names","Gil Plus"),
    QT_TRANSLATE_NOOP("Materia_Names","Enemy Away"),QT_TRANSLATE_NOOP("Materia_Names","Enemy Lure"),QT_TRANSLATE_NOOP("Materia_Names","Chocobo Lure"),QT_TRANSLATE_NOOP("Materia_Names","Pre-emptive"),QT_TRANSLATE_NOOP("Materia_Names","Long Range"),    QT_TRANSLATE_NOOP("Materia_Names","Mega All"),QT_TRANSLATE_NOOP("Materia_Names","Counter Attack"),
    QT_TRANSLATE_NOOP("Materia_Names","Slash-All"),QT_TRANSLATE_NOOP("Materia_Names","Double Cut"),QT_TRANSLATE_NOOP("Materia_Names","Cover"),QT_TRANSLATE_NOOP("Materia_Names","Underwater"),QT_TRANSLATE_NOOP("Materia_Names","HP <-> MP"),QT_TRANSLATE_NOOP("Materia_Names","W-Magic"),QT_TRANSLATE_NOOP("Materia_Names","W-Summon"),
    QT_TRANSLATE_NOOP("Materia_Names","W-Item"),QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),QT_TRANSLATE_NOOP("Materia_Names","All"),QT_TRANSLATE_NOOP("Materia_Names","Counter"),QT_TRANSLATE_NOOP("Materia_Names","Magic Counter"),QT_TRANSLATE_NOOP("Materia_Names","MP Turbo"),QT_TRANSLATE_NOOP("Materia_Names","MP Absorb"),
    QT_TRANSLATE_NOOP("Materia_Names","HP Absorb"),QT_TRANSLATE_NOOP("Materia_Names","Elemental"),QT_TRANSLATE_NOOP("Materia_Names","Added Effect"),QT_TRANSLATE_NOOP("Materia_Names","Sneak Attack"),QT_TRANSLATE_NOOP("Materia_Names","Final Attack"),QT_TRANSLATE_NOOP("Materia_Names","Added Cut"),QT_TRANSLATE_NOOP("Materia_Names","Steal-As-Well"),
    QT_TRANSLATE_NOOP("Materia_Names","Quadra Magic"),QT_TRANSLATE_NOOP("Materia_Names","Steal"),QT_TRANSLATE_NOOP("Materia_Names","Sense"),QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),QT_TRANSLATE_NOOP("Materia_Names","Throw"),QT_TRANSLATE_NOOP("Materia_Names","Morph"),QT_TRANSLATE_NOOP("Materia_Names","Deathblow"),
    QT_TRANSLATE_NOOP("Materia_Names","Manipulate"),QT_TRANSLATE_NOOP("Materia_Names","Mime"),QT_TRANSLATE_NOOP("Materia_Names","Enemy Skill"),QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),QT_TRANSLATE_NOOP("Materia_Names","Master Command"),
    QT_TRANSLATE_NOOP("Materia_Names","Fire"),QT_TRANSLATE_NOOP("Materia_Names","Ice"),QT_TRANSLATE_NOOP("Materia_Names","Earth"),QT_TRANSLATE_NOOP("Materia_Names","Lightning"),QT_TRANSLATE_NOOP("Materia_Names","Restore"),QT_TRANSLATE_NOOP("Materia_Names","Heal"),QT_TRANSLATE_NOOP("Materia_Names","Revive"),QT_TRANSLATE_NOOP("Materia_Names","Seal"),
    QT_TRANSLATE_NOOP("Materia_Names","Mystify"),QT_TRANSLATE_NOOP("Materia_Names","Transform"),QT_TRANSLATE_NOOP("Materia_Names","Exit"),QT_TRANSLATE_NOOP("Materia_Names","Poison"),QT_TRANSLATE_NOOP("Materia_Names","Gravity"),QT_TRANSLATE_NOOP("Materia_Names","Barrier"),QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),
    QT_TRANSLATE_NOOP("Materia_Names","Comet"),QT_TRANSLATE_NOOP("Materia_Names","Time"),QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),QT_TRANSLATE_NOOP("Materia_Names","DON'T USE"),QT_TRANSLATE_NOOP("Materia_Names","Destruct"),QT_TRANSLATE_NOOP("Materia_Names","Contain"),QT_TRANSLATE_NOOP("Materia_Names","FullCure"),
    QT_TRANSLATE_NOOP("Materia_Names","Shield"),QT_TRANSLATE_NOOP("Materia_Names","Ultima"),QT_TRANSLATE_NOOP("Materia_Names","Master Magic"),QT_TRANSLATE_NOOP("Materia_Names","Choco/Mog"),QT_TRANSLATE_NOOP("Materia_Names","Shiva"),QT_TRANSLATE_NOOP("Materia_Names","Ifrit"),QT_TRANSLATE_NOOP("Materia_Names","Ramuh"),
    QT_TRANSLATE_NOOP("Materia_Names","Titan"),QT_TRANSLATE_NOOP("Materia_Names","Odin"),QT_TRANSLATE_NOOP("Materia_Names","Leviathan"),QT_TRANSLATE_NOOP("Materia_Names","Bahamut"),QT_TRANSLATE_NOOP("Materia_Names","Kujata"),QT_TRANSLATE_NOOP("Materia_Names","Alexander"),QT_TRANSLATE_NOOP("Materia_Names","Phoenix"),
    QT_TRANSLATE_NOOP("Materia_Names","Neo Bahamut"),QT_TRANSLATE_NOOP("Materia_Names","Hades"),QT_TRANSLATE_NOOP("Materia_Names","Typhon"),QT_TRANSLATE_NOOP("Materia_Names","Bahamut ZERO"),QT_TRANSLATE_NOOP("Materia_Names","Knights of Round"),QT_TRANSLATE_NOOP("Materia_Names","Master Summon")
};
static const char *materiaStats[]=
{
    QT_TRANSLATE_NOOP("Materia_Stats","MaxMp:+% depending on level"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:+% depending on level"),QT_TRANSLATE_NOOP("Materia_Stats","Dex:+% depending on level"),QT_TRANSLATE_NOOP("Materia_Stats","Mag:+% depending on level"),QT_TRANSLATE_NOOP("Materia_Stats","Lck:+% depending on level"),
    QT_TRANSLATE_NOOP("Materia_Stats","Lck:+1"),QT_TRANSLATE_NOOP("Materia_Stats","Lck:+1"),QT_TRANSLATE_NOOP("Materia_Stats","Lck:+1"),QT_TRANSLATE_NOOP("Materia_Stats","Lck:-1"),QT_TRANSLATE_NOOP("Materia_Stats","Lck:+1"),QT_TRANSLATE_NOOP("Materia_Stats","Dex:+2"),"","","","",QT_TRANSLATE_NOOP("Materia_Stats","Dex:+2"),
    QT_TRANSLATE_NOOP("Materia_Stats","Vit:+1"),"","","","","","ID:0x16","","","","","","","","","","","","","",QT_TRANSLATE_NOOP("Materia_Stats","Dex:+2"),"","ID:0x26",QT_TRANSLATE_NOOP("Materia_Stats","Vit:+1"),"",QT_TRANSLATE_NOOP("Materia_Stats","Lck:+1"),"","","","ID:0x2D","ID:0x2E","ID:0x2F","",
    QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),
    QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),
    QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"),"ID:0x3F",
    QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"),"ID:0x42","ID:0x43",QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"),
    QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"),"",QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Mag:+1"),
    QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-2% MaxMp:+2% Mag:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1"),
    QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-10% MaxMp:+10% Mag:+2 Spi:+2"),
    QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-10% MaxMp:+10% Mag:+2 Spi:+2"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-10% MaxMp:+15% Mag:+4 Spi:+4"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-10% MaxMp:+15% Mag:+4 Spi:+4"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-10% MaxMp:+15% Mag:+4 Spi:+4"),QT_TRANSLATE_NOOP("Materia_Stats","MaxHp:-10% MaxMp:+20% Mag:+8 Spi:+8"),""
};
static const char *materiaSkills[91][5]=
{
    {QT_TRANSLATE_NOOP("Materia_Skills","MP Plus +10%"),QT_TRANSLATE_NOOP("Materia_Skills","MP Plus +20%"),QT_TRANSLATE_NOOP("Materia_Skills","MP Plus +30%"),QT_TRANSLATE_NOOP("Materia_Skills","MP Plus +40%"),QT_TRANSLATE_NOOP("Materia_Skills","MP Plus +50%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","HP Plus +10%"),QT_TRANSLATE_NOOP("Materia_Skills","HP Plus +20%"),QT_TRANSLATE_NOOP("Materia_Skills","HP Plus +30%"),QT_TRANSLATE_NOOP("Materia_Skills","HP Plus +40%"),QT_TRANSLATE_NOOP("Materia_Skills","HP Plus +50%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Speed Plus +10%"),QT_TRANSLATE_NOOP("Materia_Skills","Speed Plus +20%"),QT_TRANSLATE_NOOP("Materia_Skills","Speed Plus +30%"),QT_TRANSLATE_NOOP("Materia_Skills","Speed Plus +40%"),QT_TRANSLATE_NOOP("Materia_Skills","Speed Plus +50%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Magic Plus +10%"),QT_TRANSLATE_NOOP("Materia_Skills","Magic Plus +20%"),QT_TRANSLATE_NOOP("Materia_Skills","Magic Plus +30%"),QT_TRANSLATE_NOOP("Materia_Skills","Magic Plus +40%"),QT_TRANSLATE_NOOP("Materia_Skills","Magic Plus +50%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Luck Plus +10%"),QT_TRANSLATE_NOOP("Materia_Skills","Luck Plus +20%"),QT_TRANSLATE_NOOP("Materia_Skills","Luck Plus +30%"),QT_TRANSLATE_NOOP("Materia_Skills","Luck Plus +40%"),QT_TRANSLATE_NOOP("Materia_Skills","Luck Plus +50%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Exp Plus +50%"),QT_TRANSLATE_NOOP("Materia_Skills","Exp Plus +100%"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},{QT_TRANSLATE_NOOP("Materia_Skills","Gil Plus +50%"),QT_TRANSLATE_NOOP("Materia_Skills","Gil Plus +100%"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Encounter Rate -50%"),QT_TRANSLATE_NOOP("Materia_Skills","Encounter Rate -75%"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},{QT_TRANSLATE_NOOP("Materia_Skills","Encounter Rate +50%"),QT_TRANSLATE_NOOP("Materia_Skills","Encounter Rate +100%"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Chocobo Lure"),QT_TRANSLATE_NOOP("Materia_Skills","Chocobo Lure +50%"),QT_TRANSLATE_NOOP("Materia_Skills","Chocobo Lure +100%"),QT_TRANSLATE_NOOP("Materia_Skills","Chocobo Lure +200%"),QT_TRANSLATE_NOOP("Materia_Skills","")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Pre-emptive +6%"),QT_TRANSLATE_NOOP("Materia_Skills","Pre-emptive +12%"),QT_TRANSLATE_NOOP("Materia_Skills","Pre-emptive +24%"),QT_TRANSLATE_NOOP("Materia_Skills","Pre-emptive +36%"),QT_TRANSLATE_NOOP("Materia_Skills","Pre-emptive +48%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Long Range"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Mega-all x1"),QT_TRANSLATE_NOOP("Materia_Skills","Mega-all x2"),QT_TRANSLATE_NOOP("Materia_Skills","Mega-all x3"),QT_TRANSLATE_NOOP("Materia_Skills","Mega-all x4"),QT_TRANSLATE_NOOP("Materia_Skills","Mega-all x5")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Counter Attack 20%"),QT_TRANSLATE_NOOP("Materia_Skills","Counter Attack 40%"),QT_TRANSLATE_NOOP("Materia_Skills","Counter Attack 60%"),QT_TRANSLATE_NOOP("Materia_Skills","Counter Attack 80%"),QT_TRANSLATE_NOOP("Materia_Skills","Counter Attack 100%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Slash-All"),QT_TRANSLATE_NOOP("Materia_Skills","Flash"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},{QT_TRANSLATE_NOOP("Materia_Skills","2x-Cut"),QT_TRANSLATE_NOOP("Materia_Skills","4x-Cut"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Cover +20%"),QT_TRANSLATE_NOOP("Materia_Skills","Cover +40%"),QT_TRANSLATE_NOOP("Materia_Skills","Cover +60%"),QT_TRANSLATE_NOOP("Materia_Skills","Cover +80%"),QT_TRANSLATE_NOOP("Materia_Skills","Cover +100%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Underwater"),"","","",""},{QT_TRANSLATE_NOOP("Materia_Skills","HP <-> MP"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},{QT_TRANSLATE_NOOP("Materia_Skills","W-Magic"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","W-Summon"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},{QT_TRANSLATE_NOOP("Materia_Skills","W-Item"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},{"?","?","?","?","?"},
    {QT_TRANSLATE_NOOP("Materia_Skills","All x1"),QT_TRANSLATE_NOOP("Materia_Skills","All x2"),QT_TRANSLATE_NOOP("Materia_Skills","All x3"),QT_TRANSLATE_NOOP("Materia_Skills","All x4"),QT_TRANSLATE_NOOP("Materia_Skills","All x5")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Counter Rate 20%"),QT_TRANSLATE_NOOP("Materia_Skills","Counter Rate 40%"),QT_TRANSLATE_NOOP("Materia_Skills","Counter Rate 60%"),QT_TRANSLATE_NOOP("Materia_Skills","Counter Rate 80%"),QT_TRANSLATE_NOOP("Materia_Skills","Counter Rate 100%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Magic Counter Rate 30%"),QT_TRANSLATE_NOOP("Materia_Skills","Magic Counter Rate 40%"),QT_TRANSLATE_NOOP("Materia_Skills","Magic Counter Rate 60%"),QT_TRANSLATE_NOOP("Materia_Skills","Magic Counter Rate 80%"),QT_TRANSLATE_NOOP("Materia_Skills","Magic Counter Rate 100%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","MP Turbo 10%"),QT_TRANSLATE_NOOP("Materia_Skills","Mp Turbo 20%"),QT_TRANSLATE_NOOP("Materia_Skills","Mp Turbo 30%"),QT_TRANSLATE_NOOP("Materia_Skills","Mp Turbo 40%"),QT_TRANSLATE_NOOP("Materia_Skills","Mp Turbo 50%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","MP Absorb"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},{QT_TRANSLATE_NOOP("Materia_Skills","HP Absorb"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Elemental 50%"),QT_TRANSLATE_NOOP("Materia_Skills","Elemental 100%"),QT_TRANSLATE_NOOP("Materia_Skills","Elemental 200%"),QT_TRANSLATE_NOOP("Materia_Skills",""),""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Added Effect"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Sneak Attack 20%"),QT_TRANSLATE_NOOP("Materia_Skills","Sneak Attack 35%"),QT_TRANSLATE_NOOP("Materia_Skills","Sneak Attack 50%"),QT_TRANSLATE_NOOP("Materia_Skills","Sneak Attack 65%"),QT_TRANSLATE_NOOP("Materia_Skills","Sneak Attack 80%")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Final Attack x1"),QT_TRANSLATE_NOOP("Materia_Skills","Final Attack x2"),QT_TRANSLATE_NOOP("Materia_Skills","Final Attack x3"),QT_TRANSLATE_NOOP("Materia_Skills","Final Attack x4"),QT_TRANSLATE_NOOP("Materia_Skills","Final Attack x5")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Added Cut"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},{QT_TRANSLATE_NOOP("Materia_Skills","Steal as well"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Quadra Magic x1"),QT_TRANSLATE_NOOP("Materia_Skills","Quadra Magic x2"),QT_TRANSLATE_NOOP("Materia_Skills","Quadra Magic x3"),QT_TRANSLATE_NOOP("Materia_Skills","Quadra Magic x4"),QT_TRANSLATE_NOOP("Materia_Skills","Quadra Magic x5")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Steal"),QT_TRANSLATE_NOOP("Materia_Skills","Mug"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},{QT_TRANSLATE_NOOP("Materia_Skills","Sense"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},{"?","?","?","?","?"},
    {QT_TRANSLATE_NOOP("Materia_Skills","Throw"),QT_TRANSLATE_NOOP("Materia_Skills","Coin"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},{QT_TRANSLATE_NOOP("Materia_Skills","Morph"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},{QT_TRANSLATE_NOOP("Materia_Skills","DeathBlow"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Manipulate"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},{QT_TRANSLATE_NOOP("Materia_Skills","Mime"),QT_TRANSLATE_NOOP("Materia_Skills",""),"","",""},{QT_TRANSLATE_NOOP("Materia_Skills","Enemy Skill"),"","","",""},{"?","?","?","?","?"},{"?","?","?","?","?"},{"?","?","?","?","?"},
    {QT_TRANSLATE_NOOP("Materia_Skills","Master Command"),"","","",""},{QT_TRANSLATE_NOOP("Materia_Skills","Fire (4mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Fire2 (22mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Fire3 (52mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Ice (4mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Ice2 (22mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Ice3 (52mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Quake (6mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Quake2 (28mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Quake3 (68mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Bolt (4mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Bolt2 (22mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Bolt3 (52mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Cure (5mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Cure2 (24mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Regen (30mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Cure3 (64mp)"),QT_TRANSLATE_NOOP("Materia_Skills","")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Poisona (3mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Esuna (15mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Resist (120mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Life (34mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Life2 (100mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},{QT_TRANSLATE_NOOP("Materia_Skills","Sleepel (8mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Silence (24mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Confu (18mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Berserk (28mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},{QT_TRANSLATE_NOOP("Materia_Skills","Mini (10mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Toad (14mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Exit (16mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Remove (99mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Bio (8mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Bio2 (36mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Bio3 (80mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Demi (14mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Demi2 (33mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Demi3 (48mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Barrier (16mp)"),QT_TRANSLATE_NOOP("Materia_Skills","M-Barrier (24mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Reflect (30mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Wall (58mp)"),QT_TRANSLATE_NOOP("Materia_Skills","")},{"?","?","?","?","?"},
    {QT_TRANSLATE_NOOP("Materia_Skills","Comet (70mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Comet2 (110mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Haste (18mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Slow (20mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Stop (34mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),""},{"?","?","?","?","?"},{"?","?","?","?","?"},
    {QT_TRANSLATE_NOOP("Materia_Skills","DeBarrier (12mp)"),QT_TRANSLATE_NOOP("Materia_Skills","DeSpell (20mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Death (30mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Freeze (82mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Break (86mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Tornado (90mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Flare (100mp)"),QT_TRANSLATE_NOOP("Materia_Skills","")},
    {"",QT_TRANSLATE_NOOP("Materia_Skills","Full Cure (99mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},{"",QT_TRANSLATE_NOOP("Materia_Skills","Shield (180mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},
    {"",QT_TRANSLATE_NOOP("Materia_Skills","Ultima (130mp)"),QT_TRANSLATE_NOOP("Materia_Skills",""),"",""},{QT_TRANSLATE_NOOP("Materia_Skills","Master Magic"),"","","",""},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Choco/Mog x1 (14mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Choco/Mog x2 (14mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Choco/Mog x3 (14mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Choco/Mog x4 (14mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Choco/Mog x5 (14mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Shiva x1 (32mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Shiva x2 (32mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Shiva x3 (32mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Shiva x4 (32mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Shiva x5 (32mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Ifrit x1 (34mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Ifrit x2 (34mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Ifrit x3 (34mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Ifrit x4 (34mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Ifrit x5 (34mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Ramuh x1 (40mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Ramuh x2 (40mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Ramuh x3 (40mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Ramuh x4 (40mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Ramuh x5 (40mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Titan x1 (46mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Titan x2 (46mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Titan x3 (46mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Titan x4 (46mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Titan x5 (46mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Odin x1 (80mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Odin x2 (80mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Odin x3 (80mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Odin x4 (80mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Odin x5 (80mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Leviathan x1 (78mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Leviathan x2 (78mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Leviathan x3 (78mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Leviathan x4 (78mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Leviathan x5 (78mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Bahamut x1 (100mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Bahamut x2 (100mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Bahamut x3 (100mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Bahamut x4 (100mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Bahamut x5 (100mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Kujata x1 (110mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Kujata x2 (110mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Kujata x3 (110mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Kujata x4 (110mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Kujata x5 (110mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Alexander x1 (120mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Alexander x2 (120mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Alexander x3 (120mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Alexander x4 (120mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Alexander x5 (120mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Phoenix x1 (180mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Phoenix x2 (180mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Phoenix x3 (180mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Phoenix x4 (180mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Phoenix x5 (180mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Neo Bahamut x1 (140mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Neo Bahamut x2 (140mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Neo Bahamut x3 (140mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Neo Bahamut x4 (140mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Neo Bahamut x5 (140mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Hades x1 (150mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Hades x2 (150mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Hades x3 (150mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Hades x4 (150mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Hades x5 (150mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Typhon x1 (160mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Typhon x2 (160mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Typhon x3 (160mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Typhon x4 (160mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Typhon x5 (160mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon Bahamut ZERO x1 (180mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Bahamut ZERO x2 (180mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Bahamut ZERO x3 (180mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Bahamut ZERO x4 (180mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon Bahamut ZERO x5 (180mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Summon KOTR x1 (250mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon KOTR x2 (250mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon KOTR x3 (250mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon KOTR x4 (250mp)"),QT_TRANSLATE_NOOP("Materia_Skills","Summon KOTR x5 (250mp)")},
    {QT_TRANSLATE_NOOP("Materia_Skills","Master Summon"),"","","",""}
};

QString ff7names::ItemNames(int i){return qApp->translate("Items",itemNames[i]);}
QString ff7names::MateriaNames(int i){return qApp->translate("Materia_Names",materiaNames[i]);}
QString ff7names::MateriaStats(int i){return qApp->translate("Materia_Stats",materiaStats[i]);}
QString ff7names::MateriaSkills(int i,int l){return qApp->translate("Materia_Skills",materiaSkills[i][l]);}

 static LOCATION Locations[]=
 {
     {QT_TRANSLATE_NOOP("Locations","Platform"),"1","116","3655","27432","25"},
     {QT_TRANSLATE_NOOP("Locations","Reactor No.1"),"1","124","37","1579","36"},
     {QT_TRANSLATE_NOOP("Locations","Reactor No. 5"),"1","128","64035","2546","20"},
     {QT_TRANSLATE_NOOP("Locations","Reactor No. 5"),"1","131","34","1617","36"},
     {QT_TRANSLATE_NOOP("Locations","Church in the slums"),"1","183","65463","400","8"},
     {QT_TRANSLATE_NOOP("Locations","Lower Sector 4 Plate"),"1","169","65422","468","11"},
     {QT_TRANSLATE_NOOP("Locations","Sector 5 - Slums"),"1","173","64997","135","78"},
     {QT_TRANSLATE_NOOP("Locations","Sector 7 - Slums"),"1","156","65185","636","231"},
     {QT_TRANSLATE_NOOP("Locations","Midgar Sector 8"),"1","732","265","65332","24"},
     {QT_TRANSLATE_NOOP("Locations","Midgar Sector 8"),"1","739","61439","18394","34"},
     {QT_TRANSLATE_NOOP("Locations","Sector 8, Underground"),"1","733","65264","1614","116"},
     {QT_TRANSLATE_NOOP("Locations","Train Graveyard"),"1","144","1981","62327","71"},
     {QT_TRANSLATE_NOOP("Locations","Tunnel"),"1","736","65453","65237","215"},
     {QT_TRANSLATE_NOOP("Locations","Kalm Inn"),"1","332","267","65429","15"},
     {QT_TRANSLATE_NOOP("Locations","Aerith's House"),"1","187","175","65330","138"},
     {QT_TRANSLATE_NOOP("Locations","Beginner's Hall"),"1","149","220","65371","71"},
     {QT_TRANSLATE_NOOP("Locations","Wall Market"),"1","195","462","1080","58"},
     {QT_TRANSLATE_NOOP("Locations","Shinra Bldg."),"1","227","512","63074","105"},
     {QT_TRANSLATE_NOOP("Locations","Shinra Bldg 64F."),"1","247","64386","65253","245"},
     {QT_TRANSLATE_NOOP("Locations","Shinra Bldg 67F."),"1","256","65426","797","283"},
     {QT_TRANSLATE_NOOP("Locations","Shinra Bldg 69F."),"1","264","150","65102","226"},
     {QT_TRANSLATE_NOOP("Locations","Junon Inn"),"1","376","45","197","21"},
     {QT_TRANSLATE_NOOP("Locations","Junon Office F2"),"1","397","65162","65236","8"},
     {QT_TRANSLATE_NOOP("Locations","Junon Way"),"1","394","2184","64947","24"},
     {QT_TRANSLATE_NOOP("Locations","Junon Airport Path"),"1","386","64902","65203","31"},
     {QT_TRANSLATE_NOOP("Locations","Gaeas Cliff"),"1","699","65424","240","17"},
     {QT_TRANSLATE_NOOP("Locations","Gaeas Cliff"),"1","693","65384","1104","65"},
     {QT_TRANSLATE_NOOP("Locations","Gaeas Cliff Base"),"1","687","165","51","5"},
     {QT_TRANSLATE_NOOP("Locations","Mt. Nibel"),"1","317","667","65035","261"},
     {QT_TRANSLATE_NOOP("Locations","North Crater"),"1","749","65344","16","35"},
     {QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","473","876","1471","74"},
     {QT_TRANSLATE_NOOP("Locations","Fort Condor"),"1","355","1118","391","12"},
     {QT_TRANSLATE_NOOP("Locations","Underwater Reactor"),"1","422","34","426","14"},
     {QT_TRANSLATE_NOOP("Locations","Inside Submarine"),"1","408","65484","433","7"},
     {QT_TRANSLATE_NOOP("Locations","Hallway"),"1","88","65141","34","13"},
     {QT_TRANSLATE_NOOP("Locations","Cosmo Canyon"),"1","529","128","65215","79"},
     {QT_TRANSLATE_NOOP("Locations","Boat"),"1","436","65430","64368","46"},
     {QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","462","63498","65531","220"},
     {QT_TRANSLATE_NOOP("Locations","Ropeway Station"),"1","496","64767","95","26"},
     {QT_TRANSLATE_NOOP("Locations","Forgotten Captial"),"1","633","65402","65401","40"},
     {QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","703","65170","64488","44"},
     {QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","705","94","1168","173"},
     {QT_TRANSLATE_NOOP("Locations","Wutai"),"1","579","64961","1101","34"},
     {QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","646","641","793","243"},
     {QT_TRANSLATE_NOOP("Locations","Chocobo Ranch"),"1","345","65535","64960","61"},
     {QT_TRANSLATE_NOOP("Locations","Highwind"),"1","72","65533","62949","99"},
     {QT_TRANSLATE_NOOP("Locations","Debug Room [en]"),"1","94","0","0","0"},
     {QT_TRANSLATE_NOOP("Locations","Debug Room [ja]"),"1","65","0","0","0"},
     {QT_TRANSLATE_NOOP("Locations","Test Fight"),"2","0","0","0","0"}
 };

QString locations::loc_name(int i){return qApp->translate("Locations",Locations[i].location.toAscii());}
QString locations::map_id(int i){return Locations[i].map_id;}
QString locations::loc_id(int i){return Locations[i].loc_id;}
QString locations::x(int i){return Locations[i].y;}
QString locations::y(int i){return Locations[i].x;}
QString locations::z(int i){return Locations[i].z;}

/*LEVEL CHART */
quint32 charlvls[11][99]=
{
    {0,6,33,94,202,372,616,949,1384,1934,2614,3588,4610,5809,7200,8797,10614,12665,14965,17528,20368,24161,27694,31555,35759,40321,45255,50576,56299,62438,69008,77066,84643,92701,101255,110320,119910,130040,140725,151980,163820,176259,189312,202994,217320,232305,247963,264309,281358,299125,317625,336872,356881,377667,399245,421630,444836,468878,493771,519530,546170,581467,610297,640064,670784,702471,735141,768808,803488,839195,875945,913752,952632,992599,1033669,1075856,1119176,1163643,1209273,1256080,1304080,1389359,1441133,1494178,1548509,1604141,1661090,1719371,1778999,1839990,1902360,1966123,2031295,2097892,2165929,2235421,2306384,2378833,2452783},
    {0,7,35,98,210,385,637,980,1428,1995,2695,3689,4740,5973,7403,9045,10913,13022,15387,18022,20942,24827,28457,32424,36744,41431,46501,51968,57848,64155,70905,79149,86931,95207,103992,113302,123151,133555,144529,156088,168248,183403,196985,211222,226129,241721,258014,275023,292763,311250,330500,350527,371347,392976,415429,438721,462868,487885,513787,540590,568310,596961,626559,657120,688659,721191,754732,789297,824901,861560,899290,938105,978021,1019054,1061219,1104531,1149006,1194659,1241505,1289560,1338840,1389359,1441133,1494178,1548509,1604141,1661090,1719371,1778999,1839990,1902360,1966123,2031295,2097892,2165929,2235421,2306384,2378833,2452783},
    {0,6,33,94,202,372,616,949,1384,1934,2614,3588,4610,5809,7200,8797,10614,12665,14965,17528,20368,24161,27694,31555,35759,40321,45255,50576,56299,62438,69008,77066,84643,92701,101255,110320,119910,130040,140725,151980,163820,178647,191877,205744,220264,235451,251321,267888,285168,303175,321925,341432,361712,382779,404649,427336,450856,475223,500453,526560,553560,581467,610297,640064,670784,702471,735141,768808,803488,839195,875945,913752,952632,992599,1033669,1075856,1119176,1163643,1209273,1256080,1304080,1371319,1422421,1474777,1528402,1583312,1639521,1697045,1755899,1816098,1877658,1940593,2004919,2070651,2137804,2206394,2276435,2347943,2420933},
    {0,6,32,92,199,366,607,935,1363,1905,2575,3542,4550,5733,7105,8680,10472,12495,14763,17290,20090,23831,27315,31123,35270,39770,44637,49885,55529,61584,68064,77066,84643,92701,101255,110320,119910,130040,140725,151980,163820,176259,189312,202994,217320,232305,247963,264309,281358,299125,317625,341432,361712,382779,404649,427336,450856,475223,500453,526560,553560,589211,618425,648589,679718,711828,744933,779049,814191,850374,887614,925925,965323,1005823,1047440,1090190,1134087,1179147,1225385,1272816,1321456,1407407,1459854,1513588,1568624,1624979,1682667,1741705,1802108,1863891,1927071,1991662,2057681,2125143,2194063,2264458,2336342,2409732,2484643},
    {0,6,33,94,202,372,616,949,1384,1934,2614,3588,4610,5809,7200,8797,10614,12665,14965,17528,20368,24493,28074,31988,36250,40875,45877,51271,57072,63295,69955,78112,85792,93959,102629,111816,121536,131803,142633,154040,166040,178647,191877,205744,220264,235451,251321,267888,285168,303175,321925,341432,361712,382779,404649,427336,450856,475223,500453,526560,553560,589211,618425,648589,679718,711828,744933,779049,814191,850374,887614,925925,965323,1005823,1047440,1090190,1134087,1179147,1225385,1272816,1321456,1371319,1422421,1474777,1528402,1583312,1639521,1697045,1755899,1816098,1877658,1940593,2004919,2070651,2137804,2206394,2276435,2347943,2420933},
    {0,6,33,95,205,377,625,963,1404,1962,2652,3639,4675,5891,7302,8922,10765,12845,15177,17776,20656,24827,28457,32424,36744,41431,46501,51968,57848,64155,70905,78112,85792,93959,102629,111816,121536,131803,142633,154040,166040,181023,194429,208481,223194,238584,254665,271453,288963,307210,326210,345977,366527,387875,410036,433026,456859,481551,507117,533572,560932,596961,626559,657120,688659,721191,754732,789297,824901,861560,899290,938105,978021,1019054,1061219,1104531,1149006,1194659,1241505,1289560,1338840,1389359,1441133,1494178,1548509,1604141,1661090,1719371,1778999,1839990,1902360,1966123,2031295,2097892,2165929,2235421,2306384,2378833,2452783},
    {0,6,33,95,205,377,625,963,1404,1962,2652,3639,4675,5891,7302,8922,10765,12845,15177,17776,20656,24827,28457,32424,36744,41431,46501,51968,57848,64155,70905,78112,85792,93959,102629,111816,121536,131803,142633,154040,166040,178647,191877,205744,220264,235451,251321,267888,285168,303175,321925,345977,366527,387875,410036,433026,456859,481551,507117,533572,560932,589211,618425,648589,679718,711828,744933,779049,814191,850374,887614,925925,965323,1005823,1047440,1090190,1134087,1179147,1225385,1272816,1321456,1371319,1422421,1474777,1528402,1583312,1639521,1697045,1755899,1816098,1877658,1940593,2004919,2070651,2137804,2206394,2276435,2347943,2420933},
    {0,7,35,98,210,385,637,980,1428,1995,2695,3639,4675,5891,7302,8922,10765,12845,15177,17776,20656,24827,28457,32424,36744,41431,46501,51968,57848,64155,70905,79149,86931,95207,103992,113302,123151,133555,144529,156088,168248,181023,194429,208481,223194,238584,254665,271453,288963,307210,326210,345977,366527,387875,410036,433026,456859,481551,507117,533572,560932,589211,618425,648589,679718,711828,744933,779049,814191,850374,887614,925925,965323,1005823,1047440,1090190,1134087,1179147,1225385,1272816,1321456,1371319,1422421,1474777,1528402,1583312,1639521,1697045,1755899,1816098,1877658,1940593,2004919,2070651,2137804,2206394,2276435,2347943,2420933},
    {0,6,33,95,205,377,625,963,1404,1962,2652,3639,4675,5891,7302,8922,10765,12845,15177,17776,20656,24827,28457,32424,36744,41431,46501,51968,57848,64155,70905,78112,85792,93959,102629,111816,121536,131803,142633,154040,166040,181023,194429,208481,223194,238584,254665,271453,288963,307210,326210,345977,366527,387875,410036,433026,456859,481551,507117,533572,560932,596961,626559,657120,688659,721191,754732,789297,824901,861560,899290,938105,978021,1019054,1061219,1104531,1149006,1194659,1241505,1289560,1338840,1389359,1441133,1494178,1548509,1604141,1661090,1719371,1778999,1839990,1902360,1966123,2031295,2097892,2165929,2235421,2306384,2378833,2452783},
    {0,13,65,182,390,715,1183,1820,2652,3705,5005,7084,9100,11466,14210,17360,20944,24990,29526,34580,40180,46354,53130,60536,68600,77350,86814,97020,107996,119770,132370,114576,125840,137819,150535,164010,178266,193325,209209,225940,243540,214389,230265,246906,264330,282555,301599,321480,342216,363825,386325,318682,337610,357273,377685,398860,420812,443555,467103,491470,516670,372124,390575,409626,429286,449566,470474,492021,514216,537068,560588,584784,609667,635246,661530,688530,716254,744713,773916,803872,834592,487154,505308,523908,542959,562466,582435,602871,623779,645165,667035,689393,712245,735597,759454,783821,808704,834108,860038},
    {0,6,33,94,202,372,616,949,1384,1934,2614,3588,4610,5809,7200,8797,10614,12665,14965,17528,20368,24161,27694,31555,35759,40321,45255,50576,56299,62438,69008,77066,84643,92701,101255,110320,119910,130040,140725,151980,163820,176259,189312,202994,217320,232305,247963,264309,281358,299125,317625,336872,356881,377667,399245,421630,444836,468878,493771,519530,546170,581467,610297,640064,670784,702471,735141,768808,803488,839195,875945,913752,952632,992599,1033669,1075856,1119176,1163643,1209273,1256080,1304080,1389359,1441133,1494178,1548509,1604141,1661090,1719371,1778999,1839990,1902360,1966123,2031295,2097892,2165929,2235421,2306384,2378833,2452783}
};
quint32 chartnls[11][99]=
{
    {0,6,27,61,108,170,244,333,435,550,680,974,1022,1199,1391,1597,1817,2051,2300,2563,2840,3793,3533,3861,4204,4562,4934,5321,5723,6139,6570,8058,7577,8058,8554,9065,9590,10130,10685,11255,11840,12439,13053,13682,14326,14985,15658,16346,17049,17767,18500,19247,20009,20786,21578,22385,23206,24042,24893,25759,26640,35297,28830,29767,30720,31687,32670,33667,34680,35707,36750,37807,38880,39967,41070,42187,43320,44467,45630,46807,48000,85279,51774,53045,54331,55632,56949,58281,59628,60991,62370,63763,65172,66597,68037,69492,70963,72449,73950},
    {0,7,28,63,112,175,252,343,448,567,700,994,1051,1233,1430,1642,1868,2109,2365,2635,2920,3885,3630,3967,4320,4687,5070,5467,5880,6307,6750,8244,7782,8276,8785,9310,9849,10404,10974,11559,12160,15155,13582,14237,14907,15592,16293,17009,17740,18487,19250,20027,20820,21629,22453,23292,24147,25017,25902,26803,27720,28651,29598,30561,31539,32532,33541,34565,35604,36659,37730,38815,39916,41033,42165,43312,44475,45653,46846,48055,49280,50519,51774,53045,54331,55632,56949,58281,59628,60991,62370,63763,65172,66597,68037,69492,70963,72449,73950},
    {0,6,27,61,108,170,244,333,435,550,680,974,1022,1199,1391,1597,1817,2051,2300,2563,2840,3793,3533,3861,4204,4562,4934,5321,5723,6139,6570,8058,7577,8058,8554,9065,9590,10130,10685,11255,11840,14827,13230,13867,14520,15187,15870,16567,17280,18007,18750,19507,20280,21067,21870,22687,23520,24367,25230,26107,27000,27907,28830,29767,30720,31687,32670,33667,34680,35707,36750,37807,38880,39967,41070,42187,43320,44467,45630,46807,48000,67239,51102,52356,53625,54910,56209,57524,58854,60199,61560,62935,64326,65732,67153,68590,70041,71508,72990},
    {0,6,26,60,107,167,241,328,428,542,670,967,1008,1183,1372,1575,1792,2023,2268,2527,2800,3741,3484,3808,4147,4500,4867,5248,5644,6055,6480,9002,7577,8058,8554,9065,9590,10130,10685,11255,11840,12439,13053,13682,14326,14985,15658,16346,17049,17767,18500,23807,20280,21067,21870,22687,23520,24367,25230,26107,27000,35651,29214,30164,31129,32110,33105,34116,35142,36183,37240,38311,39398,40500,41617,42750,43897,45060,46238,47431,48640,85951,52447,53734,55036,56355,57688,59038,60403,61783,63180,64591,66019,67462,68920,70395,71884,73390,74911},
    {0,6,27,61,108,170,244,333,435,550,680,974,1022,1199,1391,1597,1817,2051,2300,2563,2840,4125,3581,3914,4262,4625,5002,5394,5801,6223,6660,8157,7680,8167,8670,9187,9720,10267,10830,11407,12000,12607,13230,13867,14520,15187,15870,16567,17280,18007,18750,19507,20280,21067,21870,22687,23520,24367,25230,26107,27000,35651,29214,30164,31129,32110,33105,34116,35142,36183,37240,38311,39398,40500,41617,42750,43897,45060,46238,47431,48640,49863,51102,52356,53625,54910,56209,57524,58854,60199,61560,62935,64326,65732,67153,68590,70041,71508,72990},
    {0,6,27,62,110,172,248,338,441,558,690,987,1036,1216,1411,1620,1843,2080,2332,2599,2880,4171,3630,3967,4320,4687,5070,5467,5880,6307,6750,7207,7680,8167,8670,9187,9720,10267,10830,11407,12000,14983,13406,14052,14713,15390,16081,16788,17510,18247,19000,19767,20550,21348,22161,22990,23833,24692,25566,26455,27360,36029,29598,30561,31539,32532,33541,34565,35604,36659,37730,38815,39916,41033,42165,43312,44475,45653,46846,48055,49280,50519,51774,53045,54331,55632,56949,58281,59628,60991,62370,63763,65172,66597,68037,69492,70963,72449,73950},
    {0,6,27,62,110,172,248,338,441,558,690,987,1036,1216,1411,1620,1843,2080,2332,2599,2880,4171,3630,3967,4320,4687,5070,5467,5880,6307,6750,7207,7680,8167,8670,9187,9720,10267,10830,11407,12000,12607,13230,13867,14520,15187,15870,16567,17280,18007,18750,24052,20550,21348,22161,22990,23833,24692,25566,26455,27360,28279,29214,30164,31129,32110,33105,34116,35142,36183,37240,38311,39398,40500,41617,42750,43897,45060,46238,47431,48640,49863,51102,52356,53625,54910,56209,57524,58854,60199,61560,62935,64326,65732,67153,68590,70041,71508,72990},
    {0,7,28,63,112,175,252,343,448,567,700,944,1036,1216,1411,1620,1843,2080,2332,2599,2880,4171,3630,3967,4320,4687,5070,5467,5880,6307,6750,8244,7782,8276,8785,9310,9849,10404,10974,11559,12160,12775,13406,14052,14713,15390,16081,16788,17510,18247,19000,19767,20550,21348,22161,22990,23833,24692,25566,26455,27360,28279,29214,30164,31129,32110,33105,34116,35142,36183,37240,38311,39398,40500,41617,42750,43897,45060,46238,47431,48640,49863,51102,52356,53625,54910,56209,57524,58854,60199,61560,62935,64326,65732,67153,68590,70041,71508,72990},
    {0,6,27,62,110,172,248,338,441,558,690,987,1036,1216,1411,1620,1843,2080,2332,2599,2880,4171,3630,3967,4320,4687,5070,5467,5880,6307,6750,7207,7680,8167,8670,9187,9720,10267,10830,11407,12000,14983,13406,14052,14713,15390,16081,16788,17510,18247,19000,19767,20550,21348,22161,22990,23833,24692,25566,26455,27360,36029,29598,30561,31539,32532,33541,34565,35604,36659,37730,38815,39916,41033,42165,43312,44475,45653,46846,48055,49280,50519,51774,53045,54331,55632,56949,58281,59628,60991,62370,63763,65172,66597,68037,69492,70963,72449,73950},
    {0,13,52,117,208,325,468,637,832,1053,1300,2079,2016,2366,2744,3150,3584,4046,4536,5054,5600,6174,6776,7406,8064,8750,9464,10206,10976,11774,12600,-17794,11264,11979,12716,13475,14256,15059,15884,16731,17600,-29151,15876,16641,17424,18225,19044,19881,20736,21609,22500,-67643,18928,19663,20412,21175,21952,22743,23548,24367,25200,-144546,18451,19051,19660,20280,20908,21547,22195,22852,23520,24196,24883,25579,26284,27000,27724,28459,29203,29956,30720,-347438,18154,18600,19051,19507,19969,20436,20908,21386,21870,22358,22852,23352,23857,24367,24883,25404,25930},
    {0,6,27,61,108,170,244,333,435,550,680,974,1022,1199,1391,1597,1817,2051,2300,2563,2840,3793,3533,3861,4204,4562,4934,5321,5723,6139,6570,8058,7577,8058,8554,9065,9590,10130,10685,11255,11840,12439,13053,13682,14326,14985,15658,16346,17049,17767,18500,19247,20009,20786,21578,22385,23206,24042,24893,25759,26640,35297,28830,29767,30720,31687,32670,33667,34680,35707,36750,37807,38880,39967,41070,42187,43320,44467,45630,46807,48000,85279,51774,53045,54331,55632,56949,58281,59628,60991,62370,63763,65172,66597,68037,69492,70963,72449,73950}
};
