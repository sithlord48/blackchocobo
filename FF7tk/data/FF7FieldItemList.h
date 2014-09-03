/****************************************************************************/
//    copyright 2013 -2014  Chris Rizzitello <sithlord48@gmail.com>         //
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

//
#ifndef FF7FIELDITEMLIST_H
#define FF7FIELDITEMLIST_H

#include<QStringList>

/*! \brief data structure to hold field item  changes
 *\todo add more field items
*/
struct FieldItemList
{
	QList<quint16> Offset; /**< list of offsets to change */
	QList<quint8> Bit;	/**< list of bits to change (at offset of same index) */
	QStringList Maps;	/**< list of maps (filename) the item is shown on */
	QString Text;    /**< text to show. */
};

/*! \class FF7FieldItemList
 *  \brief Data Class to allow the tracking and changing of items being picked up on the field
 */
class FF7FieldItemList
{
public:
	FF7FieldItemList();
	/*! \brief offset list for an entry (offset[x] bit[x] are pairs needed to read/write correctly
	 *  \param index index in list
	 *   \return List of Offsets where that control the item being shown
	 */
	QList<quint16> offset(int index);

	/*! \brief bit list for an entry (one per offset)
	 *  \param index index in list
	 *  \return List of bits that control the item being shown
	 */
	QList<quint8> bit(int index);

	/*! \brief map list for an entry.
	 *  \param index index in list
	 *  \return List of maps that item is shown on
	 */
	QStringList maps(int index);

	/*! \brief item or desc of item
	 *  \param index index in list
	 *  \return text for item
	 */
	QString text(int index);

	/*! \brief total entries in FILIST
	 *  \return number of entries in FILIST
	 */
	int count();
};

static const FieldItemList FILIST[]=
{//don't forget to update count on entry
	{QList<quint16>()<<0x0BC8,QList<quint8>()<<0,QStringList()<<"mds7st1",QT_TRANSLATE_NOOP("FieldItems","Hi-Potion")},
	{QList<quint16>()<<0x0BC8,QList<quint8>()<<1,QStringList()<<"mds7st1",QT_TRANSLATE_NOOP("FieldItems","Echo Screen")},
	{QList<quint16>()<<0x0BC8,QList<quint8>()<<2,QStringList()<<"mds7st2",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0BC8,QList<quint8>()<<3,QStringList()<<"mds7st2",QT_TRANSLATE_NOOP("FieldItems","Ether")},
	{QList<quint16>()<<0x0BC8,QList<quint8>()<<4,QStringList()<<"mds7st1",QT_TRANSLATE_NOOP("FieldItems","Hi-Potion")},
	{QList<quint16>()<<0x0BC8,QList<quint8>()<<5,QStringList()<<"mds7st1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0BC8,QList<quint8>()<<6,QStringList()<<"mds7st1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0BC8,QList<quint8>()<<7,QStringList()<<"mds7st2",QT_TRANSLATE_NOOP("FieldItems","Hi-Potion")},

	{QList<quint16>()<<0x0BC9,QList<quint8>()<<0,QStringList()<<"hyou8_2",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0BC9,QList<quint8>()<<1,QStringList()<<"hyou5_1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0BC9,QList<quint8>()<<2,QStringList()<<"hyou5_3",QT_TRANSLATE_NOOP("FieldItems","Safety Bit")},
	{QList<quint16>()<<0x0BC9,QList<quint8>()<<3,QStringList()<<"hyou2",QT_TRANSLATE_NOOP("FieldItems","Mind Source")},
	{QList<quint16>()<<0x0BC9,QList<quint8>()<<4,QStringList()<<"mkt_w",QT_TRANSLATE_NOOP("FieldItems","Sneak Glove")},
	{QList<quint16>()<<0x0BC9,QList<quint8>()<<5,QStringList()<<"mkt_ia",QT_TRANSLATE_NOOP("FieldItems","Premium Heart")},

	{QList<quint16>()<<0x0BD4,QList<quint8>()<<0,QStringList()<<"md8_3",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0BD4,QList<quint8>()<<1,QStringList()<<"ealin_1",QT_TRANSLATE_NOOP("FieldItems","Phoenix Down")},
	{QList<quint16>()<<0x0BD4,QList<quint8>()<<2,QStringList()<<"eals_1",QT_TRANSLATE_NOOP("FieldItems","Ether")},
	{QList<quint16>()<<0x0BD4,QList<quint8>()<<3,QStringList()<<"eals_1",QT_TRANSLATE_NOOP("FieldItems","Cover")},
	{QList<quint16>()<<0x0BD4,QList<quint8>()<<4,QStringList()<<"farm",QT_TRANSLATE_NOOP("FieldItems","Choco/Mog")},
	{QList<quint16>()<<0x0BD4,QList<quint8>()<<5,QStringList()<<"mds6_22",QT_TRANSLATE_NOOP("FieldItems","Sense")},
	{QList<quint16>()<<0x0BD4,QList<quint8>()<<6,QStringList()<<"crcin_2",QT_TRANSLATE_NOOP("FieldItems","Ramuh")},
	{QList<quint16>()<<0x0BD4<<0x0BEA,QList<quint8>()<<7<<1,QStringList()<<"zz1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Mythril")}, // set KeyItem

	{QList<quint16>()<<0x0BD5,QList<quint8>()<<0,QStringList()<<"zz5",QT_TRANSLATE_NOOP("FieldItems","Mime")},
	{QList<quint16>()<<0x0BD5,QList<quint8>()<<1,QStringList()<<"zz6",QT_TRANSLATE_NOOP("FieldItems","HP <-> MP")},
	{QList<quint16>()<<0x0BD5,QList<quint8>()<<2,QStringList()<<"zz7",QT_TRANSLATE_NOOP("FieldItems","Quadra Magic")},
	{QList<quint16>()<<0x0BD5,QList<quint8>()<<3,QStringList()<<"zz8",QT_TRANSLATE_NOOP("FieldItems","Knights of the Round")},
	{QList<quint16>()<<0x0BD5,QList<quint8>()<<4,QStringList()<<"las3_1"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0BD5,QList<quint8>()<<5,QStringList()<<"las3_1",QT_TRANSLATE_NOOP("FieldItems","X-Potion")},
	{QList<quint16>()<<0x0BD5,QList<quint8>()<<6,QStringList()<<"las3_2"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Turbo Ether")},
	{QList<quint16>()<<0x0BD5,QList<quint8>()<<7,QStringList()<<"las3_2"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Vaccine")},

	{QList<quint16>()<<0x0BD6,QList<quint8>()<<0,QStringList()<<"las3_2",QT_TRANSLATE_NOOP("FieldItems","Magic Counter")},
	{QList<quint16>()<<0x0BD6,QList<quint8>()<<1,QStringList()<<"las3_3"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Speed Source")},
	{QList<quint16>()<<0x0BD6,QList<quint8>()<<2,QStringList()<<"las3_3",QT_TRANSLATE_NOOP("FieldItems","Turbo Ether")},
	{QList<quint16>()<<0x0BD6,QList<quint8>()<<3,QStringList()<<"las3_3",QT_TRANSLATE_NOOP("FieldItems","X-Potion")},
	{QList<quint16>()<<0x0BD6,QList<quint8>()<<4,QStringList()<<"las3_3"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Mega All")},
	{QList<quint16>()<<0x0BD6,QList<quint8>()<<5,QStringList()<<"las4_1",QT_TRANSLATE_NOOP("FieldItems","Luck Source")},
	{QList<quint16>()<<0x0BD6,QList<quint8>()<<6,QStringList()<<"las3_1"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Remedy")},
	{QList<quint16>()<<0x0BD6,QList<quint8>()<<7,QStringList()<<"zz1",QT_TRANSLATE_NOOP("FieldItems","Bolt Ring")},

	{QList<quint16>()<<0x0BD7,QList<quint8>()<<0,QStringList()<<"zz2",QT_TRANSLATE_NOOP("FieldItems","Gold Armlet")}, //reset Mythril pickup
	{QList<quint16>()<<0x0BD7,QList<quint8>()<<1,QStringList()<<"zz2",QT_TRANSLATE_NOOP("FieldItems","Great Gospel")}, //reset Mythril pickup
	{QList<quint16>()<<0x0BD7,QList<quint8>()<<2,QStringList()<<"jetin1",QT_TRANSLATE_NOOP("FieldItems","Umbrella")},
	{QList<quint16>()<<0x0BD7,QList<quint8>()<<3,QStringList()<<"jetin1",QT_TRANSLATE_NOOP("FieldItems","Flayer")},
	{QList<quint16>()<<0x0BD7,QList<quint8>()<<4,QStringList()<<"zz4",QT_TRANSLATE_NOOP("FieldItems","Chaos")},
	{QList<quint16>()<<0x0BD7,QList<quint8>()<<5,QStringList()<<"ghotin_2",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0BD7<<0x0BD7,QList<quint8>()<<6<<7,QStringList()<<"zz3",QT_TRANSLATE_NOOP("FieldItems","Enemy Skill")},// First Bit is Chocobo Has Droped Second is Pickup from field.

	{QList<quint16>()<<0x0BDC,QList<quint8>()<<0,QStringList()<<"colne_4",QT_TRANSLATE_NOOP("FieldItems","Ether")},
	{QList<quint16>()<<0x0BDC,QList<quint8>()<<1,QStringList()<<"colne_6",QT_TRANSLATE_NOOP("FieldItems","Hyper")},
	{QList<quint16>()<<0x0BDC,QList<quint8>()<<2,QStringList()<<"colne_3",QT_TRANSLATE_NOOP("FieldItems","Phoenix Down")},
	{QList<quint16>()<<0x0BDC,QList<quint8>()<<3,QStringList()<<"blinst_2",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0BDC,QList<quint8>()<<5,QStringList()<<"cosmin7",QString("%1 & %2").arg(QT_TRANSLATE_NOOP("FieldItems","Elixir"),QT_TRANSLATE_NOOP("FieldItems","Magic Source"))},
	{QList<quint16>()<<0x0BDC<<0x0BE8,QList<quint8>()<<6<<3,QStringList()<<"blin65_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Midgar parts")},
	{QList<quint16>()<<0x0BDC<<0x0BE8,QList<quint8>()<<7<<4,QStringList()<<"blin65_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Midgar parts")},

	{QList<quint16>()<<0x0BDD<<0x0BE8,QList<quint8>()<<0<<5,QStringList()<<"blin65_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Midgar parts")},
	{QList<quint16>()<<0x0BDD<<0x0BE8,QList<quint8>()<<1<<6,QStringList()<<"blin65_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Midgar parts")},
	{QList<quint16>()<<0x0BDD<<0x0BE8,QList<quint8>()<<2<<7,QStringList()<<"blin65_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Midgar parts")},
	{QList<quint16>()<<0x0BDD<<0x0BE8,QList<quint8>()<<3<<1,QStringList()<<"blin65_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Keycard 66")},
	{QList<quint16>()<<0x0BDD,QList<quint8>()<<4,QStringList()<<"shpin_2",QT_TRANSLATE_NOOP("FieldItems","All")},
	{QList<quint16>()<<0x0BDD,QList<quint8>()<<5,QStringList()<<"shpin_2",QT_TRANSLATE_NOOP("FieldItems","Ether")},
	{QList<quint16>()<<0x0BDD,QList<quint8>()<<6,QStringList()<<"shpin_3",QT_TRANSLATE_NOOP("FieldItems","Wind Slash")},
	{QList<quint16>()<<0x0BDD,QList<quint8>()<<7,QStringList()<<"gidun_4",QT_TRANSLATE_NOOP("FieldItems","Fairy Ring")},

	{QList<quint16>()<<0x0BDE,QList<quint8>()<<0,QStringList()<<"gidun_4",QT_TRANSLATE_NOOP("FieldItems","X-Potion")},
	{QList<quint16>()<<0x0BDE,QList<quint8>()<<1,QStringList()<<"gidun_1",QT_TRANSLATE_NOOP("FieldItems","Added Effect")},
	{QList<quint16>()<<0x0BDE,QList<quint8>()<<2,QStringList()<<"gidun_2",QT_TRANSLATE_NOOP("FieldItems","Black M-phone")},
	{QList<quint16>()<<0x0BDE,QList<quint8>()<<3,QStringList()<<"gidun_2",QT_TRANSLATE_NOOP("FieldItems","Ether")},
	{QList<quint16>()<<0x0BDE,QList<quint8>()<<4,QStringList()<<"cosmin6",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0BDE,QList<quint8>()<<5,QStringList()<<"hideway3",QT_TRANSLATE_NOOP("FieldItems","HP Absorb")},
	{QList<quint16>()<<0x0BDE,QList<quint8>()<<6,QStringList()<<"hideway1",QT_TRANSLATE_NOOP("FieldItems","Magic Shuriken")},
	{QList<quint16>()<<0x0BDE,QList<quint8>()<<7,QStringList()<<"hideway2",QT_TRANSLATE_NOOP("FieldItems","Hairpin")},

	{QList<quint16>()<<0x0BDF<<0xBE7,QList<quint8>()<<0<<7,QStringList()<<"blin61",QT_TRANSLATE_NOOP("FieldItems","Keycard 62")},
	{QList<quint16>()<<0x0BDF,QList<quint8>()<<1,QStringList()<<"uta_im",QT_TRANSLATE_NOOP("FieldItems","HP Absorb")},
	{QList<quint16>()<<0x0BDF,QList<quint8>()<<2,QStringList()<<"uttmpin4",QT_TRANSLATE_NOOP("FieldItems","Swift Bolt")},
	{QList<quint16>()<<0x0BDF,QList<quint8>()<<3,QStringList()<<"uttmpin4",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0BDF,QList<quint8>()<<4,QStringList()<<"blin2_i",QT_TRANSLATE_NOOP("FieldItems","Pile Banger")},
	{QList<quint16>()<<0x0BDF,QList<quint8>()<<5,QStringList()<<"blin2_i",QT_TRANSLATE_NOOP("FieldItems","Master Fist")},
	{QList<quint16>()<<0x0BDF,QList<quint8>()<<6,QStringList()<<"blinst_2",QT_TRANSLATE_NOOP("FieldItems","Behemoth Horn")},
	{QList<quint16>()<<0x0BDF,QList<quint8>()<<7,QStringList()<<"cosmin7",QT_TRANSLATE_NOOP("FieldItems","Full Cure")},

	{QList<quint16>()<<0x0C24<<0x0BE6,QList<quint8>()<<6<<5,QStringList()<<"ncorel3",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Huge Materia:Corel")},
	{QList<quint16>()<<0x0C24,QList<quint8>()<<7,QStringList()<<"ncorel2"<<"ncorel3",QT_TRANSLATE_NOOP("FieldItems","Ultima")},

	{QList<quint16>()<<0x0C26<<0x0C26<<0x0BEA,QList<quint8>()<<1<<5<<2,QStringList()<<"snmin1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Snowboard")},
	{QList<quint16>()<<0x0C26<<0x0BE9,QList<quint8>()<<6<<4,QStringList()<<"snmin2",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Glacier Map")},

	{QList<quint16>()<<0x0C2A,QList<quint8>()<<3,QStringList()<<"ujunon1"<<"prisila",QT_TRANSLATE_NOOP("FieldItems","Shiva")},

	{QList<quint16>()<<0x0C44<<0x0BE5,QList<quint8>()<<0<<1,QStringList()<<"mktpb",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Cologne")},//Mutually Exclucive
	{QList<quint16>()<<0x0C44<<0x0BE5,QList<quint8>()<<1<<2,QStringList()<<"mktpb",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Flower Cologne")},//Mutually Exclucive
	{QList<quint16>()<<0x0C44<<0x0BE5,QList<quint8>()<<2<<3,QStringList()<<"mktpb",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Sexy Cologne")},//Mutually Exclucive

	{QList<quint16>()<<0x0C44<<0x0BE6,QList<quint8>()<<6<<0,QStringList()<<"mkt_s2",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Pharmacy Coupon")},

	{QList<quint16>()<<0x0C44<<0x0BE4,QList<quint8>()<<7<<3,QStringList()<<"mkt_mens",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Wig")},//Mutually Exclucive
	{QList<quint16>()<<0x0C44<<0x0BE4,QList<quint8>()<<7<<4,QStringList()<<"mkt_mens",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Dyed Wig")},//Mutually Exclucive
	{QList<quint16>()<<0x0C44<<0x0BE4,QList<quint8>()<<7<<5,QStringList()<<"mkt_mens",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Blonde Wig")},//Mutually Exclucive

	{QList<quint16>()<<0x0C45<<0x0C45<<0x0BE4,QList<quint8>()<<3<<5<<0,QStringList()<<"mkt_s1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Cotton Dress")},//Mutually Exclucive
	{QList<quint16>()<<0x0C45<<0x0C45<<0x0BE4,QList<quint8>()<<3<<6<<1,QStringList()<<"mkt_s1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Satin Dress")},//Mutually Exclucive
	{QList<quint16>()<<0x0C45<<0x0C45<<0x0BE4,QList<quint8>()<<3<<7<<2,QStringList()<<"mkt_s1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Silk Dress")},//Mutually Exclucive

	{QList<quint16>()<<0x0C46<<0x0BE6,QList<quint8>()<<0<<1,QStringList()<<"mkt_s3",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Disinfectant")},//Mutually Exclucive
	{QList<quint16>()<<0x0C46<<0x0BE6,QList<quint8>()<<1<<2,QStringList()<<"mkt_s3",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Deodorant")},//Mutually Exclucive
	{QList<quint16>()<<0x0C46<<0x0BE6,QList<quint8>()<<2<<3,QStringList()<<"mkt_s3",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Digestive")},//Mutually Exclucive

	{QList<quint16>()<<0x0C46<<0x0BE4,QList<quint8>()<<6<<6,QStringList()<<"mkt_m",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Glass Tiara")}, //Mutally Exclucive
	{QList<quint16>()<<0x0C46<<0x0BE4,QList<quint8>()<<5<<7,QStringList()<<"mkt_m",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Ruby Tiara")},//Mutually Exclucive
	{QList<quint16>()<<0x0C46<<0x0BE5,QList<quint8>()<<4<<0,QStringList()<<"mkt_m",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Diamond Tiara")},//Mutually Exclucive

	{QList<quint16>()<<0x0C49<<0x0C49<<0x0C49,QList<quint8>()<<5<<6<<7,QStringList()<<"mkt_w",QT_TRANSLATE_NOOP("FieldItems","Batteries")},

	{QList<quint16>()<<0x0C54,QList<quint8>()<<5,QStringList()<<"convil_2",QT_TRANSLATE_NOOP("FieldItems","Peace Ring")},
	{QList<quint16>()<<0x0C54,QList<quint8>()<<6,QStringList()<<"convil_2",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},
	{QList<quint16>()<<0x0C54,QList<quint8>()<<7,QStringList()<<"convil_2",QT_TRANSLATE_NOOP("FieldItems","Super Ball")},

	{QList<quint16>()<<0x0C6B,QList<quint8>()<<4,QStringList()<<"hyou13_2",QT_TRANSLATE_NOOP("FieldItems","Alexander")},
	{QList<quint16>()<<0x0C6B,QList<quint8>()<<5,QStringList()<<"move_d",QT_TRANSLATE_NOOP("FieldItems","Added Cut")},
	{QList<quint16>()<<0x0C6B,QList<quint8>()<<6,QStringList()<<"hyou12",QT_TRANSLATE_NOOP("FieldItems","All")},

	{QList<quint16>()<<0x0C84<<0x0C84,QList<quint8>()<<0<<6,QStringList()<<"blin62_1",QT_TRANSLATE_NOOP("FieldItems","Can Advance")},

	{QList<quint16>()<<0x0C86<<0x0BE8,QList<quint8>()<<5<<2,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: KeyCard 68")},
	{QList<quint16>()<<0x0C8B<<0x0BE7,QList<quint8>()<<3<<3,QStringList()<<"bonevil",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Lunar Harp")},
	{QList<quint16>()<<0x0C8C<<0x0BE7,QList<quint8>()<<1<<4,QStringList()<<"sinin2_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Key To Basement")},
	/*Below share same bit you can only get one possible error in the field script*/
	{QList<quint16>()<<0x0CBD,QList<quint8>()<<1,QStringList()<<"nivl_3",QT_TRANSLATE_NOOP("FieldItems","Mind Plus")},
	{QList<quint16>()<<0x0CBD,QList<quint8>()<<1,QStringList()<<"nivinn_1",QT_TRANSLATE_NOOP("FieldItems","Luck Source")},

	{QList<quint16>()<<0x0CBD,QList<quint8>()<<2,QStringList()<<"niv_w",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0CBD,QList<quint8>()<<3,QStringList()<<"niv_ti1",QT_TRANSLATE_NOOP("FieldItems","Turbo Ether")},
	{QList<quint16>()<<0x0CBD,QList<quint8>()<<4,QStringList()<<"niv_ti2",QT_TRANSLATE_NOOP("FieldItems","Platinum Fist")},
	{QList<quint16>()<<0x0CBD,QList<quint8>()<<5,QStringList()<<"nvmin1_2",QT_TRANSLATE_NOOP("FieldItems","Luck Source")},

	{QList<quint16>()<<0x0CEC<<0x0BE9,QList<quint8>()<<7<<1,QStringList()<<"gldst"<<"games_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Gold Ticket")},
	{QList<quint16>()<<0x0CF1,QList<quint8>()<<0,QStringList()<<"games_1",QT_TRANSLATE_NOOP("FieldItems","Gil Plus")},
	{QList<quint16>()<<0x0CF1,QList<quint8>()<<1,QStringList()<<"games_1",QT_TRANSLATE_NOOP("FieldItems","Exp Plus")},
	{QList<quint16>()<<0x0CF2,QList<quint8>()<<6,QStringList()<<"coloss",QT_TRANSLATE_NOOP("FieldItems","Sprint Shoes")},
	{QList<quint16>()<<0x0CF3,QList<quint8>()<<5,QStringList()<<"coloin1",QT_TRANSLATE_NOOP("FieldItems","Omnislash")},
	{QList<quint16>()<<0x0CF3,QList<quint8>()<<6,QStringList()<<"coloin1",QT_TRANSLATE_NOOP("FieldItems","W-Summon")},


	{QList<quint16>()<<0x0D65,QList<quint8>()<<7,QStringList()<<"min51_2",QT_TRANSLATE_NOOP("FieldItems","Found hidden draw")},

	{QList<quint16>()<<0x0D44<<0x0D65,QList<quint8>()<<5<<7,QStringList()<<"min51_2",QT_TRANSLATE_NOOP("FieldItems","Stole boys 5 gil")},
	{QList<quint16>()<<0x0D44<<0x0D65,QList<quint8>()<<6<<7,QStringList()<<"min51_2",QT_TRANSLATE_NOOP("FieldItems","Turbo Ether")},

	{QList<quint16>()<<0x0D55,QList<quint8>()<<4,QStringList()<<"blin63_1",QT_TRANSLATE_NOOP("FieldItems","Initilized the Machine")},
	{QList<quint16>()<<0x0D55<<0x0BE9,QList<quint8>()<<1<<5,QStringList()<<"blin63_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: A Coupon")},
	{QList<quint16>()<<0x0D55<<0x0BE9,QList<quint8>()<<3<<6,QStringList()<<"blin63_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: B Coupon")},
	{QList<quint16>()<<0x0D55<<0x0BE9,QList<quint8>()<<2<<7,QStringList()<<"blin63_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: C Coupon")},
	//Can't Seam to varify these found in script never on field
	//{QList<quint16>()<<0x0D55,QList<quint8>()<<5,QStringList()<<"blin63_1",QT_TRANSLATE_NOOP("FieldItems","Hourglass")},
	//{QList<quint16>()<<0x0D55,QList<quint8>()<<6,QStringList()<<"blin63_1",QT_TRANSLATE_NOOP("FieldItems","All")},
	//Reward For Trading in the A B or C Coupon(s)
	{QList<quint16>()<<0x0D5D,QList<quint8>()<<5,QStringList()<<"blin63_1",QT_TRANSLATE_NOOP("FieldItems","Star Pendant")},
	{QList<quint16>()<<0x0D5D,QList<quint8>()<<6,QStringList()<<"blin63_1",QT_TRANSLATE_NOOP("FieldItems","All")},
	{QList<quint16>()<<0x0D5D,QList<quint8>()<<7,QStringList()<<"blin63_1",QT_TRANSLATE_NOOP("FieldItems","Four Slots")},

	//MainProgress >=1008 for the one below
	{QList<quint16>()<<0x0D55,QList<quint8>()<<7,QStringList()<<"blin63_1",QT_TRANSLATE_NOOP("FieldItems","Grow Lance")},

	{QList<quint16>()<<0x0D57<<0x0BE8,QList<quint8>()<<4<<0,QStringList()<<"blin62_1",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Keycard 65")},

	{QList<quint16>()<<0x0D60,QList<quint8>()<<1,QStringList()<<"blin62_1",QT_TRANSLATE_NOOP("FieldItems","Elemental")},

	{QList<quint16>()<<0x0D63,QList<quint8>()<<4,QStringList()<<"yufy1",QT_TRANSLATE_NOOP("FieldItems","MP Absorb")},

	{QList<quint16>()<<0x0D65,QList<quint8>()<<3,QStringList()<<"bugin1b",QT_TRANSLATE_NOOP("FieldItems","Bahamut Zero")},
	{QList<quint16>()<<0x0D65,QList<quint8>()<<4,QStringList()<<"gidun_4",QT_TRANSLATE_NOOP("FieldItems","Turbo Ether")},

	{QList<quint16>()<<0x0D66,QList<quint8>()<<0,QStringList()<<"min51_2",QT_TRANSLATE_NOOP("FieldItems","Turtle Paradise Flyer #1")},
	{QList<quint16>()<<0x0D66,QList<quint8>()<<1,QStringList()<<"blin1",QT_TRANSLATE_NOOP("FieldItems","Turtle Paradise Flyer #2")},
	{QList<quint16>()<<0x0D66,QList<quint8>()<<2,QStringList()<<"ghotin_1",QT_TRANSLATE_NOOP("FieldItems","Turtle Paradise Flyer #3")},
	{QList<quint16>()<<0x0D66,QList<quint8>()<<3,QStringList()<<"cosin1",QT_TRANSLATE_NOOP("FieldItems","Turtle Paradise Flyer #4")},
	{QList<quint16>()<<0x0D66,QList<quint8>()<<4,QStringList()<<"cosin3",QT_TRANSLATE_NOOP("FieldItems","Turtle Paradise Flyer #5")},
	{QList<quint16>()<<0x0D66,QList<quint8>()<<5,QStringList()<<"yufy2",QT_TRANSLATE_NOOP("FieldItems","Turtle Paradise Flyer #6")},
	{QList<quint16>()<<0x0D66,QList<quint8>()<<6,QStringList()<<"uutai1",QT_TRANSLATE_NOOP("FieldItems","Turtle Paradise Flyer #7")},
	{QList<quint16>()<<0x0D66,QList<quint8>()<<7,QStringList()<<"utapb",QT_TRANSLATE_NOOP("FieldItems","Rewarded for viewing all Turtle Paradise Flyers")},

 {QList<quint16>()<<0x0FA4,QList<quint8>()<<1,QStringList()<<"gaiin_4",QT_TRANSLATE_NOOP("FieldItems","Enhance Sword")},
	{QList<quint16>()<<0x0FA4,QList<quint8>()<<2,QStringList()<<"gaiin_5",QT_TRANSLATE_NOOP("FieldItems","Fire Armlet")},
	{QList<quint16>()<<0x0FA4,QList<quint8>()<<3,QStringList()<<"gaiin_3",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0FA4,QList<quint8>()<<4,QStringList()<<"gaiin_3",QT_TRANSLATE_NOOP("FieldItems","Speed Source")},
	{QList<quint16>()<<0x0FA4,QList<quint8>()<<5,QStringList()<<"gaiin_1",QT_TRANSLATE_NOOP("FieldItems","Javelin")},
	{QList<quint16>()<<0x0FA4,QList<quint8>()<<6,QStringList()<<"gaiin_5",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0FA4,QList<quint8>()<<7,QStringList()<<"gaiin_1",QT_TRANSLATE_NOOP("FieldItems","Ribbon")},

	{QList<quint16>()<<0x0FA5,QList<quint8>()<<0,QStringList()<<"ncoin1",QT_TRANSLATE_NOOP("FieldItems","Ether")},
	{QList<quint16>()<<0x0FA5,QList<quint8>()<<1,QStringList()<<"ncoin3",QT_TRANSLATE_NOOP("FieldItems","Catastrophe")},
	{QList<quint16>()<<0x0FA5,QList<quint8>()<<2,QStringList()<<"snmin2",QT_TRANSLATE_NOOP("FieldItems","Hero Drink")},
	{QList<quint16>()<<0x0FA5,QList<quint8>()<<3,QStringList()<<"snmin2",QT_TRANSLATE_NOOP("FieldItems","Vaccine")},
	{QList<quint16>()<<0x0FA5,QList<quint8>()<<4,QStringList()<<"sninn_2",QT_TRANSLATE_NOOP("FieldItems","X-Potion")},
	{QList<quint16>()<<0x0FA5,QList<quint8>()<<5,QStringList()<<"snmayor",QT_TRANSLATE_NOOP("FieldItems","Turbo Ether")},

	{QList<quint16>()<<0x0FA6,QList<quint8>()<<0,QStringList()<<"trnad_2",QT_TRANSLATE_NOOP("FieldItems","Neo Bahamut")},
	{QList<quint16>()<<0x0FA6,QList<quint8>()<<1,QStringList()<<"trnad_4",QT_TRANSLATE_NOOP("FieldItems","Poison Ring")},
	{QList<quint16>()<<0x0FA6,QList<quint8>()<<2,QStringList()<<"trnad_3",QT_TRANSLATE_NOOP("FieldItems","Hero Drink")},
	{QList<quint16>()<<0x0FA6,QList<quint8>()<<3,QStringList()<<"trnad_4",QT_TRANSLATE_NOOP("FieldItems","MP Turbo")},

	{QList<quint16>()<<0x0FC4,QList<quint8>()<<0,QStringList()<<"md1stin",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0FC4,QList<quint8>()<<1,QStringList()<<"md1stin",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0FC4,QList<quint8>()<<2,QStringList()<<"nmkin_3",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0FC4,QList<quint8>()<<3,QStringList()<<"nmkin_1",QT_TRANSLATE_NOOP("FieldItems","Phoenix Down")},
	{QList<quint16>()<<0x0FC4,QList<quint8>()<<4,QStringList()<<"blin67_1",QT_TRANSLATE_NOOP("FieldItems","Poison")},
	{QList<quint16>()<<0x0FC4,QList<quint8>()<<5,QStringList()<<"colne_b1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0FC4,QList<quint8>()<<7,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("FieldItems","Potion")},

	{QList<quint16>()<<0x0FC5,QList<quint8>()<<0,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0FC5,QList<quint8>()<<1,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0FC5,QList<quint8>()<<2,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0FC5,QList<quint8>()<<3,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("FieldItems","Bolt Armlet")},
	{QList<quint16>()<<0x0FC5,QList<quint8>()<<4,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("FieldItems","HypnoCrown")}, // add var[5][58] == 1 to this.
	{QList<quint16>()<<0x0FC5,QList<quint8>()<<5,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},
	{QList<quint16>()<<0x0FC5,QList<quint8>()<<6,QStringList()<<"smkin_1",QT_TRANSLATE_NOOP("FieldItems","Ether")},
	{QList<quint16>()<<0x0FC5,QList<quint8>()<<7,QStringList()<<"slfrst_2",QT_TRANSLATE_NOOP("FieldItems","Kujata")},

	{QList<quint16>()<<0x0FC6<<0x0FC6,QList<quint8>()<<0<<1,QStringList()<<"sininb42",QT_TRANSLATE_NOOP("FieldItems","Destruct")},
	{QList<quint16>()<<0x0FC6<<0x0FC6,QList<quint8>()<<2<<3,QStringList()<<"blin68_1"<<"blin68_2",QT_TRANSLATE_NOOP("FieldItems","Enemy Skill")},
	{QList<quint16>()<<0x0FC6<<0x0FC6,QList<quint8>()<<4<<5,QStringList()<<"sinin2_1",QT_TRANSLATE_NOOP("FieldItems","Odin")},
	{QList<quint16>()<<0x0FC6,QList<quint8>()<<6,QStringList()<<"nvdun1",QT_TRANSLATE_NOOP("FieldItems","Counter")},
	{QList<quint16>()<<0x0FC6,QList<quint8>()<<7,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("FieldItems","Magic Plus")},

	{QList<quint16>()<<0x0FC7,QList<quint8>()<<0,QStringList()<<"colne_b1",QT_TRANSLATE_NOOP("FieldItems","Steal")},
	{QList<quint16>()<<0x0FC7,QList<quint8>()<<1,QStringList()<<"sinin1_2",QT_TRANSLATE_NOOP("FieldItems","Twin Viper")},
	{QList<quint16>()<<0x0FC7,QList<quint8>()<<2,QStringList()<<"sinin1_2",QT_TRANSLATE_NOOP("FieldItems","Silver M-phone")},
	{QList<quint16>()<<0x0FC7,QList<quint8>()<<3,QStringList()<<"sinin2_1",QT_TRANSLATE_NOOP("FieldItems","Enemy Launcher")},
	{QList<quint16>()<<0x0FC7,QList<quint8>()<<4,QStringList()<<"sinin2_2",QT_TRANSLATE_NOOP("FieldItems","Magic Source")},
	{QList<quint16>()<<0x0FC7,QList<quint8>()<<5,QStringList()<<"bonevil",QT_TRANSLATE_NOOP("FieldItems","Buntline")},
	{QList<quint16>()<<0x0FC7,QList<quint8>()<<6,QStringList()<<"loslake1",QT_TRANSLATE_NOOP("FieldItems","Aurora Armlet")},
	{QList<quint16>()<<0x0FC7,QList<quint8>()<<7,QStringList()<<"sango3",QT_TRANSLATE_NOOP("FieldItems","Viper Halberd")},

	{QList<quint16>()<<0x0FC8,QList<quint8>()<<0,QStringList()<<"mtnvl2",QT_TRANSLATE_NOOP("FieldItems","Rune Blade")},
	{QList<quint16>()<<0x0FC8,QList<quint8>()<<1,QStringList()<<"mtnvl2",QT_TRANSLATE_NOOP("FieldItems","Plus Barrette")},
	{QList<quint16>()<<0x0FC8,QList<quint8>()<<2,QStringList()<<"nvdun1",QT_TRANSLATE_NOOP("FieldItems","Powersoul")},
	{QList<quint16>()<<0x0FC8,QList<quint8>()<<3,QStringList()<<"nvdun4",QT_TRANSLATE_NOOP("FieldItems","Sniper CR")},
	{QList<quint16>()<<0x0FC8,QList<quint8>()<<4,QStringList()<<"nvdun2",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0FC8,QList<quint8>()<<5,QStringList()<<"nvdun1",QT_TRANSLATE_NOOP("FieldItems","All")},
	{QList<quint16>()<<0x0FC8,QList<quint8>()<<6,QStringList()<<"nvdun3",QT_TRANSLATE_NOOP("FieldItems","Elemental")},

	{QList<quint16>()<<0x0FC9,QList<quint8>()<<0,QStringList()<<"sundun_2",QT_TRANSLATE_NOOP("FieldItems","Power Source")},
	{QList<quint16>()<<0x0FC9,QList<quint8>()<<1,QStringList()<<"sango1",QT_TRANSLATE_NOOP("FieldItems","Water Ring")},
	{QList<quint16>()<<0x0FC9,QList<quint8>()<<2,QStringList()<<"anfrst_2",QT_TRANSLATE_NOOP("FieldItems","Typhon")},
	{QList<quint16>()<<0x0FC9,QList<quint8>()<<3,QStringList()<<"anfrst_3",QT_TRANSLATE_NOOP("FieldItems","Supershot ST")},
	{QList<quint16>()<<0x0FC9,QList<quint8>()<<4,QStringList()<<"anfrst_1",QT_TRANSLATE_NOOP("FieldItems","Slash-All")},
	{QList<quint16>()<<0x0FC9,QList<quint8>()<<5,QStringList()<<"anfrst_1",QT_TRANSLATE_NOOP("FieldItems","Minerva Band")},
	{QList<quint16>()<<0x0FC9,QList<quint8>()<<6,QStringList()<<"anfrst_5",QT_TRANSLATE_NOOP("FieldItems","Apocalypse")},
	{QList<quint16>()<<0x0FC9,QList<quint8>()<<7,QStringList()<<"anfrst_5",QT_TRANSLATE_NOOP("FieldItems","Elixir")},

	{QList<quint16>()<<0x0FCA,QList<quint8>()<<0,QStringList()<<"anfrst_3",QT_TRANSLATE_NOOP("FieldItems","Spring Gun Clip")},
	{QList<quint16>()<<0x0FCA,QList<quint8>()<<1,QStringList()<<"bonevil",QT_TRANSLATE_NOOP("FieldItems","Mop")},
	{QList<quint16>()<<0x0FCA,QList<quint8>()<<2,QStringList()<<"bonevil",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},
	{QList<quint16>()<<0x0FCA<<0x0BE7,QList<quint8>()<<3<<5,QStringList()<<"blackbg1"<<"mds5_5"<<"bonevil",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Key To Sector 5")},

	{QList<quint16>()<<0x0FF4,QList<quint8>()<<0,QStringList()<<"sbwy4_6",QT_TRANSLATE_NOOP("FieldItems","Tent")},
	{QList<quint16>()<<0x0FF4,QList<quint8>()<<1,QStringList()<<"sbwy4_3",QT_TRANSLATE_NOOP("FieldItems","Potion")},
	{QList<quint16>()<<0x0FF4,QList<quint8>()<<2,QStringList()<<"sbwy4_1",QT_TRANSLATE_NOOP("Items","Ether")},
	{QList<quint16>()<<0x0FF4,QList<quint8>()<<3,QStringList()<<"psdun_3",QT_TRANSLATE_NOOP("FieldItems","Ether")},
	{QList<quint16>()<<0x0FF4,QList<quint8>()<<4,QStringList()<<"psdun_4",QT_TRANSLATE_NOOP("FieldItems","Hi-Potion")},
	{QList<quint16>()<<0x0FF4,QList<quint8>()<<5,QStringList()<<"psdun_4",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0FF4,QList<quint8>()<<6,QStringList()<<"psdun_3",QT_TRANSLATE_NOOP("FieldItems","Long Range")},
	{QList<quint16>()<<0x0FF4,QList<quint8>()<<7,QStringList()<<"gnmk",QT_TRANSLATE_NOOP("FieldItems","Titan")},

	{QList<quint16>()<<0x0FF5,QList<quint8>()<<0,QStringList()<<"elmin2_2",QT_TRANSLATE_NOOP("FieldItems","Ether")},
	{QList<quint16>()<<0x0FF5,QList<quint8>()<<1,QStringList()<<"losin1",QT_TRANSLATE_NOOP("FieldItems","Comet")},
	{QList<quint16>()<<0x0FF5,QList<quint8>()<<2,QStringList()<<"gonjun1",QT_TRANSLATE_NOOP("FieldItems","Deathblow")},
	{QList<quint16>()<<0x0FF5,QList<quint8>()<<3,QStringList()<<"q_4",QT_TRANSLATE_NOOP("FieldItems","Hades")},
	{QList<quint16>()<<0x0FF5,QList<quint8>()<<4,QStringList()<<"q_4",QT_TRANSLATE_NOOP("FieldItems","Outsider")},
	{QList<quint16>()<<0x0FF5,QList<quint8>()<<5,QStringList()<<"q_3",QT_TRANSLATE_NOOP("FieldItems","Escort Guard")},
	{QList<quint16>()<<0x0FF5,QList<quint8>()<<6,QStringList()<<"q_3",QT_TRANSLATE_NOOP("FieldItems","Conformer")},
	{QList<quint16>()<<0x0FF5,QList<quint8>()<<7,QStringList()<<"q_4",QT_TRANSLATE_NOOP("FieldItems","Spirit Lance")},

	{QList<quint16>()<<0x0FF6,QList<quint8>()<<0,QStringList()<<"q_1",QT_TRANSLATE_NOOP("FieldItems","Heaven's Cloud")},
	{QList<quint16>()<<0x0FF6,QList<quint8>()<<1,QStringList()<<"q_3",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},
	{QList<quint16>()<<0x0FF6,QList<quint8>()<<2,QStringList()<<"q_4",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},
	{QList<quint16>()<<0x0FF6,QList<quint8>()<<3,QStringList()<<"losinn",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0FF6,QList<quint8>()<<4,QStringList()<<"losin2",QT_TRANSLATE_NOOP("FieldItems","Guard Source")},
	{QList<quint16>()<<0x0FF6,QList<quint8>()<<5,QStringList()<<"losin3",QT_TRANSLATE_NOOP("FieldItems","Magic Source")},
	{QList<quint16>()<<0x0FF6,QList<quint8>()<<6,QStringList()<<"las1_2"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Elixir")}, //also needs to edit 11[142]:4 (field var) on las4_0
	{QList<quint16>()<<0x0FF6,QList<quint8>()<<7,QStringList()<<"las1_2"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Mystile")}, //also needs to edit 11[142]:1 (field var) on las4_0

	{QList<quint16>()<<0x0FF7,QList<quint8>()<<0,QStringList()<<"las1_2"<<"las1_3"<<"las0_4",QT_TRANSLATE_NOOP("FieldItems","Speed Source")}, //also needs to edit 11[142]:3 on las4_0
	{QList<quint16>()<<0x0FF7,QList<quint8>()<<1,QStringList()<<"las1_3",QT_TRANSLATE_NOOP("FieldItems","Tetra Elemental")},
	{QList<quint16>()<<0x0FF7,QList<quint8>()<<2,QStringList()<<"las1_3"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},// also needs to edit 11[142]:6 on las4_0
	{QList<quint16>()<<0x0FF7,QList<quint8>()<<3,QStringList()<<"las1_3"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Megalixir")}, // also needs to edit 11[142]:2 on las4_0
	{QList<quint16>()<<0x0FF7,QList<quint8>()<<4,QStringList()<<"las0_5",QT_TRANSLATE_NOOP("FieldItems","Power Source")},
	{QList<quint16>()<<0x0FF7,QList<quint8>()<<5,QStringList()<<"las0_5",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x0FF7,QList<quint8>()<<6,QStringList()<<"las0_4"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Guard Source")}, //also needs to edit 11[142]:0 (field var) on las4_0
	{QList<quint16>()<<0x0FF7,QList<quint8>()<<7,QStringList()<<"las0_5"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Mind Source")}, //also needs to edit 11[142]:2 (field var) on las4_0

	{QList<quint16>()<<0x0FF8,QList<quint8>()<<0,QStringList()<<"goson",QT_TRANSLATE_NOOP("FieldItems","White M-phone")},
	{QList<quint16>()<<0x0FF8,QList<quint8>()<<1,QStringList()<<"gninn",QT_TRANSLATE_NOOP("FieldItems","X-Potion")},
	{QList<quint16>()<<0x0FF8,QList<quint8>()<<2,QStringList()<<"rktsid",QT_TRANSLATE_NOOP("FieldItems","Drill Arm")},
	{QList<quint16>()<<0x0FF8,QList<quint8>()<<3,QStringList()<<"rktmin2",QT_TRANSLATE_NOOP("FieldItems","Power Source")},
	{QList<quint16>()<<0x0FF8,QList<quint8>()<<4,QStringList()<<"rckt",QT_TRANSLATE_NOOP("FieldItems","Yoshiyuki")},
	{QList<quint16>()<<0x0FF8,QList<quint8>()<<5,QStringList()<<"rckt2",QT_TRANSLATE_NOOP("FieldItems","Venus Gospel")},
	{QList<quint16>()<<0x0FF8,QList<quint8>()<<6,QStringList()<<"las0_4",QT_TRANSLATE_NOOP("FieldItems","Save Crystal")},
	{QList<quint16>()<<0x0FF8,QList<quint8>()<<7,QStringList()<<"elmtow",QT_TRANSLATE_NOOP("FieldItems","Peacemaker")},

	{QList<quint16>()<<0x0FF9,QList<quint8>()<<0,QStringList()<<"losinn",QT_TRANSLATE_NOOP("FieldItems","Enemy Skill")},
	{QList<quint16>()<<0x0FF9,QList<quint8>()<<1,QStringList()<<"elmin1_1",QT_TRANSLATE_NOOP("FieldItems","Ether")},
	{QList<quint16>()<<0x0FF9,QList<quint8>()<<2,QStringList()<<"las0_5",QT_TRANSLATE_NOOP("FieldItems","Magic Source")},
	{QList<quint16>()<<0x0FF9,QList<quint8>()<<3,QStringList()<<"elmin3_2",QT_TRANSLATE_NOOP("FieldItems","Guard Source")},
	{QList<quint16>()<<0x0FF9,QList<quint8>()<<4,QStringList()<<"elmin4_1",QT_TRANSLATE_NOOP("FieldItems","Ether")}, // shown if(5[9] ==0)
	{QList<quint16>()<<0x0FF9,QList<quint8>()<<5,QStringList()<<"rkt_w",QT_TRANSLATE_NOOP("FieldItems","Fourth Bracelet")}, // shown if gamemoment >999
	{QList<quint16>()<<0x0FF9,QList<quint8>()<<6,QStringList()<<"rkt_i",QT_TRANSLATE_NOOP("FieldItems","Guard Source")}, // shown if gamemoment >999
	{QList<quint16>()<<0x0FF9,QList<quint8>()<<7,QStringList()<<"elminn_2",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},

	{QList<quint16>()<<0x0FFA,QList<quint8>()<<0,QStringList()<<"las0_5",QT_TRANSLATE_NOOP("FieldItems","Guard Source")},
	{QList<quint16>()<<0x0FFA,QList<quint8>()<<1,QStringList()<<"q_3",QT_TRANSLATE_NOOP("FieldItems","Double Cut")},
	{QList<quint16>()<<0x0FFA,QList<quint8>()<<2,QStringList()<<"q_4",QT_TRANSLATE_NOOP("FieldItems","Highwind")},
	{QList<quint16>()<<0x0FFA,QList<quint8>()<<3,QStringList()<<"las0_5",QT_TRANSLATE_NOOP("FieldItems","HP Absorb")},
	{QList<quint16>()<<0x0FFA,QList<quint8>()<<4,QStringList()<<"psdun_2",QT_TRANSLATE_NOOP("FieldItems","Mind Source")},
	{QList<quint16>()<<0x0FFA,QList<quint8>()<<5,QStringList()<<"psdun_3",QT_TRANSLATE_NOOP("FieldItems","Tent")},

	{QList<quint16>()<<0x0FFB,QList<quint8>()<<0,QStringList()<<"elmin4_2",QT_TRANSLATE_NOOP("FieldItems","Show Underwater")},
	{QList<quint16>()<<0x0FFB,QList<quint8>()<<1,QStringList()<<"elmin4_2",QT_TRANSLATE_NOOP("FieldItems","Show Master Command")},
	{QList<quint16>()<<0x0FFB,QList<quint8>()<<2,QStringList()<<"elmin4_2",QT_TRANSLATE_NOOP("FieldItems","Show Master Magic")},
	{QList<quint16>()<<0x0FFB,QList<quint8>()<<3,QStringList()<<"elmin4_2",QT_TRANSLATE_NOOP("FieldItems","Show Master Summon")},
	{QList<quint16>()<<0x0FFB,QList<quint8>()<<4,QStringList()<<"elmin4_2",QT_TRANSLATE_NOOP("FieldItems","Show Gold Chocobo")},

	{QList<quint16>()<<0x1014,QList<quint8>()<<0,QStringList()<<"kuro_3",QT_TRANSLATE_NOOP("FieldItems","Morph")},
	{QList<quint16>()<<0x1014,QList<quint8>()<<1,QStringList()<<"kuro_1",QT_TRANSLATE_NOOP("FieldItems","Luck Plus")},
	{QList<quint16>()<<0x1014,QList<quint8>()<<2,QStringList()<<"kuro_1",QT_TRANSLATE_NOOP("FieldItems","Turbo Ether")},
	{QList<quint16>()<<0x1014,QList<quint8>()<<3,QStringList()<<"kuro_1",QT_TRANSLATE_NOOP("FieldItems","Mind Source")},
	//{QList<quint16>()<<0x1014,QList<quint8>()<<4,QStringList()<<"kuro_6",QT_TRANSLATE_NOOP("FieldItems","Battle #645")}, //if(3[230]:0) Map version
	//{QList<quint16>()<<0x1014,QList<quint8>()<<5,QStringList()<<"kuro_6",QT_TRANSLATE_NOOP("FieldItems","Battle #649")}, //if(3[230]:2) map is used for
	{QList<quint16>()<<0x1014,QList<quint8>()<<6,QStringList()<<"kuro_6",QT_TRANSLATE_NOOP("FieldItems","Princess Guard")},//if(3[230]:3) different rooms
	{QList<quint16>()<<0x1014,QList<quint8>()<<7,QStringList()<<"kuro_6",QT_TRANSLATE_NOOP("FieldItems","Trumpet Shell")}, //if(3[230]:5) 3[230] tracks the room

	{QList<quint16>()<<0x1015,QList<quint8>()<<0,QStringList()<<"kuro_6",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},   //if(3[230]:6)
	{QList<quint16>()<<0x1015,QList<quint8>()<<1,QStringList()<<"kuro_82",QT_TRANSLATE_NOOP("FieldItems","Bahamut")}, // if(Main Progress == 624)
	{QList<quint16>()<<0x1015,QList<quint8>()<<2,QStringList()<<"kuro_1",QT_TRANSLATE_NOOP("FieldItems","Trident")},
	{QList<quint16>()<<0x1015,QList<quint8>()<<3,QStringList()<<"kuro_1",QT_TRANSLATE_NOOP("FieldItems","Rocket Punch")},
	{QList<quint16>()<<0x1015,QList<quint8>()<<4,QStringList()<<"kuro_1",QT_TRANSLATE_NOOP("FieldItems","Ribbon")},
	{QList<quint16>()<<0x1015,QList<quint8>()<<5,QStringList()<<"kuro_2",QT_TRANSLATE_NOOP("FieldItems","Silver Rifle")},

	{QList<quint16>()<<0x1016,QList<quint8>()<<0,QStringList()<<"delmin12",QT_TRANSLATE_NOOP("FieldItems","Motor Drive")},
	{QList<quint16>()<<0x1016,QList<quint8>()<<1,QStringList()<<"delmin12",QT_TRANSLATE_NOOP("FieldItems","Fire Ring")},
	{QList<quint16>()<<0x1016,QList<quint8>()<<2,QStringList()<<"delmin12",QT_TRANSLATE_NOOP("FieldItems","Power Source")},
	{QList<quint16>()<<0x1016,QList<quint8>()<<3,QStringList()<<"delmin1",QT_TRANSLATE_NOOP("FieldItems","Purchased The House")},

	{QList<quint16>()<<0x1018,QList<quint8>()<<1,QStringList()<<"mtcrl_4",QT_TRANSLATE_NOOP("FieldItems","W Machine Gun")},
	{QList<quint16>()<<0x1018,QList<quint8>()<<2,QStringList()<<"mtcrl_4",QT_TRANSLATE_NOOP("FieldItems","Transform")},
	{QList<quint16>()<<0x1018,QList<quint8>()<<3,QStringList()<<"mtcrl_4",QT_TRANSLATE_NOOP("FieldItems","Turbo Ether")},

	{QList<quint16>()<<0x1019,QList<quint8>()<<0,QStringList()<<"mtcrl_7",QT_TRANSLATE_NOOP("FieldItems","Mind Source")},
	{QList<quint16>()<<0x1019,QList<quint8>()<<1,QStringList()<<"mtcrl_7",QT_TRANSLATE_NOOP("FieldItems","Power Source")},
	{QList<quint16>()<<0x1019,QList<quint8>()<<2,QStringList()<<"mtcrl_7",QT_TRANSLATE_NOOP("FieldItems","Tent")},

	{QList<quint16>()<<0x101A,QList<quint8>()<<0,QStringList()<<"junmin2",QT_TRANSLATE_NOOP("FieldItems","Mind Source")},
	{QList<quint16>()<<0x101A,QList<quint8>()<<1,QStringList()<<"junmin3",QT_TRANSLATE_NOOP("FieldItems","Power Source")},
	{QList<quint16>()<<0x101A,QList<quint8>()<<2,QStringList()<<"junmin3",QT_TRANSLATE_NOOP("FieldItems","Guard Source")},
	{QList<quint16>()<<0x101A,QList<quint8>()<<3,QStringList()<<"junmin2",QT_TRANSLATE_NOOP("FieldItems","Luck Source")},
	{QList<quint16>()<<0x101A,QList<quint8>()<<4,QStringList()<<"junmin2",QT_TRANSLATE_NOOP("FieldItems","1/35 soldier")},
	{QList<quint16>()<<0x101A,QList<quint8>()<<5,QStringList()<<"junmin4",QT_TRANSLATE_NOOP("FieldItems","Speed Source")},
	{QList<quint16>()<<0x101A,QList<quint8>()<<6,QStringList()<<"junmin5",QT_TRANSLATE_NOOP("FieldItems","1/35 soldier")},

	{QList<quint16>()<<0x1031<<0x0BE9,QList<quint8>()<<0<<3,QStringList()<<"semkin_7",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Leviathan Scales")},
	{QList<quint16>()<<0x1031,QList<quint8>()<<1,QStringList()<<"datiao_8",QT_TRANSLATE_NOOP("FieldItems","Steal-As-Well")},
	{QList<quint16>()<<0x1031,QList<quint8>()<<3,QStringList()<<"datiao_8",QT_TRANSLATE_NOOP("FieldItems","Dragoon Lance")},
	{QList<quint16>()<<0x1031,QList<quint8>()<<4,QStringList()<<"tunnel_4",QT_TRANSLATE_NOOP("FieldItems","W-Item")},
	{QList<quint16>()<<0x1031,QList<quint8>()<<5,QStringList()<<"md8_b1",QT_TRANSLATE_NOOP("FieldItems","Max Ray")},
	{QList<quint16>()<<0x1031,QList<quint8>()<<6,QStringList()<<"md8_b1",QT_TRANSLATE_NOOP("FieldItems","Aegis Armlet")},
	{QList<quint16>()<<0x1031,QList<quint8>()<<7,QStringList()<<"semkin_7",QT_TRANSLATE_NOOP("FieldItems","Scimitar")},

	{QList<quint16>()<<0x1032,QList<quint8>()<<0,QStringList()<<"semkin_6",QT_TRANSLATE_NOOP("FieldItems","Battle Trumpet")},
	{QList<quint16>()<<0x1032,QList<quint8>()<<1,QStringList()<<"tower5",QT_TRANSLATE_NOOP("FieldItems","Leviathan")},
	{QList<quint16>()<<0x1032,QList<quint8>()<<2,QStringList()<<"md8_b1",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},
	{QList<quint16>()<<0x1032,QList<quint8>()<<3,QStringList()<<"datiao_8",QT_TRANSLATE_NOOP("FieldItems","Oritsuru")},
	{QList<quint16>()<<0x1032,QList<quint8>()<<4,QStringList()<<"md8_b2",QT_TRANSLATE_NOOP("FieldItems","Starlight Phone")},
	{QList<quint16>()<<0x1032,QList<quint8>()<<5,QStringList()<<"md8_b2",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x1032,QList<quint8>()<<6,QStringList()<<"md8_b1",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x1032,QList<quint8>()<<7,QStringList()<<"tunnel_5",QT_TRANSLATE_NOOP("FieldItems","Magic Source")},

	{QList<quint16>()<<0x1035<<0x0BE6,QList<quint8>()<<3<<7,QStringList()<<"rcktin4",QT_TRANSLATE_NOOP("FieldItems","KeyItem: Huge Materia:Rocket")},

	{QList<quint16>()<<0x1036,QList<quint8>()<<0,QStringList()<<"tunnel_5",QT_TRANSLATE_NOOP("FieldItems","Mind Source")},
	{QList<quint16>()<<0x1036,QList<quint8>()<<1,QStringList()<<"tunnel_5",QT_TRANSLATE_NOOP("FieldItems","Power Source")},
	{QList<quint16>()<<0x1036,QList<quint8>()<<2,QStringList()<<"tunnel_5",QT_TRANSLATE_NOOP("FieldItems","Guard Source")},
	{QList<quint16>()<<0x1036,QList<quint8>()<<3,QStringList()<<"md8_32",QT_TRANSLATE_NOOP("FieldItems","Mystile")},
	{QList<quint16>()<<0x1036,QList<quint8>()<<4,QStringList()<<"canon_1",QT_TRANSLATE_NOOP("FieldItems","Missing Score")},
	{QList<quint16>()<<0x1036,QList<quint8>()<<5,QStringList()<<"md8_32",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x1036,QList<quint8>()<<6,QStringList()<<"las0_7",QT_TRANSLATE_NOOP("FieldItems","Megalixir")},
	{QList<quint16>()<<0x1036,QList<quint8>()<<7,QStringList()<<"las0_7",QT_TRANSLATE_NOOP("FieldItems","Power Source")},

	{QList<quint16>()<<0x1037,QList<quint8>()<<0,QStringList()<<"las0_7",QT_TRANSLATE_NOOP("FieldItems","Guard Source")},
	{QList<quint16>()<<0x1037,QList<quint8>()<<1,QStringList()<<"las2_2"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Magic Source")},
	{QList<quint16>()<<0x1037,QList<quint8>()<<2,QStringList()<<"las2_2"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Remedy")},
	{QList<quint16>()<<0x1037,QList<quint8>()<<3,QStringList()<<"las2_3"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Hero Drink")},
	{QList<quint16>()<<0x1037,QList<quint8>()<<4,QStringList()<<"las2_3",QT_TRANSLATE_NOOP("FieldItems","Vaccine")},
	{QList<quint16>()<<0x1037,QList<quint8>()<<5,QStringList()<<"las2_3"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Shield")},
	{QList<quint16>()<<0x1037,QList<quint8>()<<6,QStringList()<<"las0_4"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Counter")},
	{QList<quint16>()<<0x1037,QList<quint8>()<<7,QStringList()<<"las0_4"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","W-Magic")},

	{QList<quint16>()<<0x1038,QList<quint8>()<<0,QStringList()<<"las2_3"<<"las4_0",QT_TRANSLATE_NOOP("FieldItems","Imperial Guard")},
	{QList<quint16>()<<0x1038,QList<quint8>()<<1,QStringList()<<"las0_6",QT_TRANSLATE_NOOP("FieldItems","Mind Source")},
	{QList<quint16>()<<0x1038,QList<quint8>()<<2,QStringList()<<"las0_6",QT_TRANSLATE_NOOP("FieldItems","Hero Drink")},

	{QList<quint16>()<<0x1056,QList<quint8>()<<3,QStringList()<<"itmin2",QT_TRANSLATE_NOOP("FieldItems","Elixir")},
	{QList<quint16>()<<0x1057,QList<quint8>()<<0,QStringList()<<"itown1b",QT_TRANSLATE_NOOP("FieldItems","Contain")}
};
#endif // FF7FIELDITEMLIST_H
