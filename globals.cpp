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
