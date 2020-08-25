/****************************************************************************/
//    copyright 2013 - 2020  Chris Rizzitello <sithlord48@gmail.com>        //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#pragma once

#include<QObject>

class QStringList;

struct FieldItem {
    QList<quint16> Offset; /**< list of offsets to change */
    QList<quint8> Bit;  /**< list of bits to change (at offset of same index) */
    QStringList Maps;   /**< list of maps (filename) the item is shown on */
    QString Text;    /**< text to show. */
};

/*! \class FF7FieldItemList
*\todo add more field items
 *  \brief Data Class to allow the tracking and changing of items being picked up on the field
 */
class FF7FieldItemList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int size READ size CONSTANT)
public:
    /*! \brief data structure to hold field item  changes
    */

    FF7FieldItemList() = default;
    ~FF7FieldItemList() = default;
    /*! \brief offset list for an entry (offset[x] bit[x] are pairs needed to read/write correctly
     *  \param index index in list
     *   \return List of Offsets where that control the item being shown
     */
    Q_INVOKABLE const QList<quint16> &offset(int index);
    /*! \brief bit list for an entry (one per offset)
     *  \param index index in list
     *  \return List of bits that control the item being shown
     */
    Q_INVOKABLE const QList<quint8> &bit(int index);

    /*! \brief map list for an entry.
     *  \param index index in list
     *  \return List of maps that item is shown on
     */
    Q_INVOKABLE const QStringList &maps(int index);

    /*! \brief item or desc of item
     *  \param index index in list
     *  \return text for item
     */
    Q_INVOKABLE QString text(int index);

    /*! \brief total entries in FILIST
     *  \return number of entries in FILIST
     */
    inline int size() const
    {
        return _fieldItemList.size();
    }

    /*!
     * \brief Reference to a fieldItem
     * \param index of item
     * \return info for one field item
     */
    const QList<FieldItem> &fieldItemList() const;

private:

    inline static const QList<FieldItem> _fieldItemList {
        {{quint16(0x0BC8)}, {quint8(0)}, {QStringLiteral("mds7st1")}, QT_TR_NOOP("Hi-Potion")}
        , {{quint16(0x0BC8)}, {quint8(1)}, {QStringLiteral("mds7st1")}, QT_TR_NOOP("Echo Screen")}
        , {{quint16(0x0BC8)}, {quint8(2)}, {QStringLiteral("mds7st2")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0BC8)}, {quint8(3)}, {QStringLiteral("mds7st2")}, QT_TR_NOOP("Ether")}
        , {{quint16(0x0BC8)}, {quint8(4)}, {QStringLiteral("mds7st1")}, QT_TR_NOOP("Hi-Potion")}
        , {{quint16(0x0BC8)}, {quint8(5)}, {QStringLiteral("mds7st1")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0BC8)}, {quint8(6)}, {QStringLiteral("mds7st1")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0BC8)}, {quint8(7)}, {QStringLiteral("mds7st2")}, QT_TR_NOOP("Hi-Potion")}

        , {{quint16(0x0BC9)}, {quint8(0)}, {QStringLiteral("hyou8_2")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0BC9)}, {quint8(1)}, {QStringLiteral("hyou5_1")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0BC9)}, {quint8(2)}, {QStringLiteral("hyou5_3")}, QT_TR_NOOP("Safety Bit")}
        , {{quint16(0x0BC9)}, {quint8(3)}, {QStringLiteral("hyou2")}, QT_TR_NOOP("Mind Source")}
        , {{quint16(0x0BC9)}, {quint8(4)}, {QStringLiteral("mkt_w")}, QT_TR_NOOP("Sneak Glove")}
        , {{quint16(0x0BC9)}, {quint8(5)}, {QStringLiteral("mkt_ia")}, QT_TR_NOOP("Premium Heart")}

        , {{quint16(0x0BD4)}, {quint8(0)}, {QStringLiteral("md8_3")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0BD4)}, {quint8(1)}, {QStringLiteral("ealin_1")}, QT_TR_NOOP("Phoenix Down")}
        , {{quint16(0x0BD4)}, {quint8(2)}, {QStringLiteral("eals_1")}, QT_TR_NOOP("Ether")}
        , {{quint16(0x0BD4)}, {quint8(3)}, {QStringLiteral("eals_1")}, QT_TR_NOOP("Cover")}
        , {{quint16(0x0BD4)}, {quint8(4)}, {QStringLiteral("farm")}, QT_TR_NOOP("Choco/Mog")}
        , {{quint16(0x0BD4)}, {quint8(5)}, {QStringLiteral("mds6_22")}, QT_TR_NOOP("Sense")}
        , {{quint16(0x0BD4)}, {quint8(6)}, {QStringLiteral("crcin_2")}, QT_TR_NOOP("Ramuh")}
        , {{quint16(0x0BD4), quint16(0x0BEA)}, {quint8(7), quint8(1)}, {QStringLiteral("zz1")}, QT_TR_NOOP("KeyItem: Mythril")} // set KeyItem

        , {{quint16(0x0BD5)}, {quint8(0)}, {QStringLiteral("zz5")}, QT_TR_NOOP("Mime")}
        , {{quint16(0x0BD5)}, {quint8(1)}, {QStringLiteral("zz6")}, QT_TR_NOOP("HP <-> MP")}
        , {{quint16(0x0BD5)}, {quint8(2)}, {QStringLiteral("zz7")}, QT_TR_NOOP("Quadra Magic")}
        , {{quint16(0x0BD5)}, {quint8(3)}, {QStringLiteral("zz8")}, QT_TR_NOOP("Knights of the Round")}
        , {{quint16(0x0BD5)}, {quint8(4)}, {QStringLiteral("las3_1"), QStringLiteral("las4_0")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0BD5)}, {quint8(5)}, {QStringLiteral("las3_1")}, QT_TR_NOOP("X-Potion")}
        , {{quint16(0x0BD5)}, {quint8(6)}, {QStringLiteral("las3_2"), QStringLiteral("las4_0")}, QT_TR_NOOP("Turbo Ether")}
        , {{quint16(0x0BD5)}, {quint8(7)}, {QStringLiteral("las3_2"), QStringLiteral("las4_0")}, QT_TR_NOOP("Vaccine")}

        , {{quint16(0x0BD6)}, {quint8(0)}, {QStringLiteral("las3_2")}, QT_TR_NOOP("Magic Counter")}
        , {{quint16(0x0BD6)}, {quint8(1)}, {QStringLiteral("las3_3"), QStringLiteral("las4_0")}, QT_TR_NOOP("Speed Source")}
        , {{quint16(0x0BD6)}, {quint8(2)}, {QStringLiteral("las3_3")}, QT_TR_NOOP("Turbo Ether")}
        , {{quint16(0x0BD6)}, {quint8(3)}, {QStringLiteral("las3_3")}, QT_TR_NOOP("X-Potion")}
        , {{quint16(0x0BD6)}, {quint8(4)}, {QStringLiteral("las3_3"), QStringLiteral("las4_0")}, QT_TR_NOOP("Mega All")}
        , {{quint16(0x0BD6)}, {quint8(5)}, {QStringLiteral("las4_1")}, QT_TR_NOOP("Luck Source")}
        , {{quint16(0x0BD6)}, {quint8(6)}, {QStringLiteral("las3_1"), QStringLiteral("las4_0")}, QT_TR_NOOP("Remedy")}
        , {{quint16(0x0BD6)}, {quint8(7)}, {QStringLiteral("zz1")}, QT_TR_NOOP("Bolt Ring")}

        , {{quint16(0x0BD7)}, {quint8(0)}, {QStringLiteral("zz2")}, QT_TR_NOOP("Gold Armlet")} //reset Mythril pickup
        , {{quint16(0x0BD7)}, {quint8(1)}, {QStringLiteral("zz2")}, QT_TR_NOOP("Great Gospel")} //reset Mythril pickup
        , {{quint16(0x0BD7)}, {quint8(2)}, {QStringLiteral("jetin1")}, QT_TR_NOOP("Umbrella")}
        , {{quint16(0x0BD7)}, {quint8(3)}, {QStringLiteral("jetin1")}, QT_TR_NOOP("Flayer")}
        , {{quint16(0x0BD7)}, {quint8(4)}, {QStringLiteral("zz4")}, QT_TR_NOOP("Chaos")}
        , {{quint16(0x0BD7)}, {quint8(5)}, {QStringLiteral("ghotin_2")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0BD7), quint16(0x0BD7)}, {quint8(6), quint8(7)}, {QStringLiteral("zz3")}, QT_TR_NOOP("Enemy Skill")}// First Bit is Chocobo Has Dropped Second is Pickup from field.

        , {{quint16(0x0BDC)}, {quint8(0)}, {QStringLiteral("colne_4")}, QT_TR_NOOP("Ether")}
        , {{quint16(0x0BDC)}, {quint8(1)}, {QStringLiteral("colne_6")}, QT_TR_NOOP("Hyper")}
        , {{quint16(0x0BDC)}, {quint8(2)}, {QStringLiteral("colne_3")}, QT_TR_NOOP("Phoenix Down")}
        , {{quint16(0x0BDC)}, {quint8(3)}, {QStringLiteral("blinst_2")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0BDC)}, {quint8(5)}, {QStringLiteral("cosmin7")}, QStringLiteral("%1 & %2").arg(QT_TR_NOOP("Elixir"), QT_TR_NOOP("Magic Source"))}
        , {{quint16(0x0BDC), quint16(0x0BE8)}, {quint8(6), quint8(3)}, {QStringLiteral("blin65_1")}, QT_TR_NOOP("KeyItem: Midgar parts")}
        , {{quint16(0x0BDC), quint16(0x0BE8)}, {quint8(7), quint8(4)}, {QStringLiteral("blin65_1")}, QT_TR_NOOP("KeyItem: Midgar parts")}

        , {{quint16(0x0BDD), quint16(0x0BE8)}, {quint8(0), quint8(5)}, {QStringLiteral("blin65_1")}, QT_TR_NOOP("KeyItem: Midgar parts")}
        , {{quint16(0x0BDD), quint16(0x0BE8)}, {quint8(1), quint8(6)}, {QStringLiteral("blin65_1")}, QT_TR_NOOP("KeyItem: Midgar parts")}
        , {{quint16(0x0BDD), quint16(0x0BE8)}, {quint8(2), quint8(7)}, {QStringLiteral("blin65_1")}, QT_TR_NOOP("KeyItem: Midgar parts")}
        , {{quint16(0x0BDD), quint16(0x0BE8)}, {quint8(3), quint8(1)}, {QStringLiteral("blin65_1")}, QT_TR_NOOP("KeyItem: Keycard 66")}
        , {{quint16(0x0BDD)}, {quint8(4)}, {QStringLiteral("shpin_2")}, QT_TR_NOOP("All")}
        , {{quint16(0x0BDD)}, {quint8(5)}, {QStringLiteral("shpin_2")}, QT_TR_NOOP("Ether")}
        , {{quint16(0x0BDD)}, {quint8(6)}, {QStringLiteral("shpin_3")}, QT_TR_NOOP("Wind Slash")}
        , {{quint16(0x0BDD)}, {quint8(7)}, {QStringLiteral("gidun_4")}, QT_TR_NOOP("Fairy Ring")}

        , {{quint16(0x0BDE)}, {quint8(0)}, {QStringLiteral("gidun_4")}, QT_TR_NOOP("X-Potion")}
        , {{quint16(0x0BDE)}, {quint8(1)}, {QStringLiteral("gidun_1")}, QT_TR_NOOP("Added Effect")}
        , {{quint16(0x0BDE)}, {quint8(2)}, {QStringLiteral("gidun_2")}, QT_TR_NOOP("Black M-phone")}
        , {{quint16(0x0BDE)}, {quint8(3)}, {QStringLiteral("gidun_2")}, QT_TR_NOOP("Ether")}
        , {{quint16(0x0BDE)}, {quint8(4)}, {QStringLiteral("cosmin6")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0BDE)}, {quint8(5)}, {QStringLiteral("hideway3")}, QT_TR_NOOP("HP Absorb")}
        , {{quint16(0x0BDE)}, {quint8(6)}, {QStringLiteral("hideway1")}, QT_TR_NOOP("Magic Shuriken")}
        , {{quint16(0x0BDE)}, {quint8(7)}, {QStringLiteral("hideway2")}, QT_TR_NOOP("Hairpin")}

        , {{quint16(0x0BDF), quint16(0xBE7)}, {quint8(0), quint8(7)}, {QStringLiteral("blin61")}, QT_TR_NOOP("KeyItem: Keycard 62")}
        , {{quint16(0x0BDF)}, {quint8(1)}, {QStringLiteral("uta_im")}, QT_TR_NOOP("HP Absorb")}
        , {{quint16(0x0BDF)}, {quint8(2)}, {QStringLiteral("uttmpin4")}, QT_TR_NOOP("Swift Bolt")}
        , {{quint16(0x0BDF)}, {quint8(3)}, {QStringLiteral("uttmpin4")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0BDF)}, {quint8(4)}, {QStringLiteral("blin2_i")}, QT_TR_NOOP("Pile Banger")}
        , {{quint16(0x0BDF)}, {quint8(5)}, {QStringLiteral("blin2_i")}, QT_TR_NOOP("Master Fist")}
        , {{quint16(0x0BDF)}, {quint8(6)}, {QStringLiteral("blinst_2")}, QT_TR_NOOP("Behemoth Horn")}
        , {{quint16(0x0BDF)}, {quint8(7)}, {QStringLiteral("cosmin7")}, QT_TR_NOOP("Full Cure")}

        , {{quint16(0x0BE5)}, {quint8(4)}, {QStringLiteral("mrkt2")}, QT_TR_NOOP("KeyItem: Member's Card")}

        , {{quint16(0x0BE6)}, {quint8(4)}, {QStringLiteral("convil_1")}, QT_TR_NOOP("KeyItem: Huge Materia: Fort Condor")}
        , {{quint16(0x0BE6)}, {quint8(6)}, {QStringLiteral("subin_1a"), QStringLiteral("subin_1b")}, QT_TR_NOOP("KeyItem: Huge Materia: UnderWater")}

        , {{quint16(0x0BE7)}, {quint8(0)}, {QStringLiteral("subin_1a"), QStringLiteral("subin_1b")}, QT_TR_NOOP("KeyItem: Key to Ancients")}

        , {{quint16(0x0BE9)}, {quint8(0)}, {QStringLiteral("elminn_1")}, QT_TR_NOOP("KeyItem: PHS")}
        , {{quint16(0x0BE9)}, {quint8(2)}, {QStringLiteral("clsin2_2")}, QT_TR_NOOP("KeyItem: Keystone")}
        , {{quint16(0x0BEA)}, {quint8(0)}, {QStringLiteral("trnad_1")}, QT_TR_NOOP("KeyItem: Black Materia")}


        , {{quint16(0x0C24), quint16(0x0BE6)}, {quint8(6), quint8(5)}, {QStringLiteral("ncorel3")}, QT_TR_NOOP("KeyItem: Huge Materia: Corel")}
        , {{quint16(0x0C24)}, {quint8(7)}, {QStringLiteral("ncorel2"), QStringLiteral("ncorel3")}, QT_TR_NOOP("Ultima")}

        , {{quint16(0x0C26), quint16(0x0C26), quint16(0x0BEA)}, {quint8(1), quint8(5), quint8(2)}, {QStringLiteral("snmin1")}, QT_TR_NOOP("KeyItem: Snowboard")}
        , {{quint16(0x0C26), quint16(0x0BE9)}, {quint8(6), quint8(4)}, {QStringLiteral("snmin2")}, QT_TR_NOOP("KeyItem: Glacier Map")}

        , {{quint16(0x0C2A)}, {quint8(3)}, {QStringLiteral("ujunon1"), QStringLiteral("prisila")}, QT_TR_NOOP("Shiva")}

        , {{quint16(0x0C44), quint16(0x0BE5)}, {quint8(0), quint8(1)}, {QStringLiteral("mktpb")}, QT_TR_NOOP("KeyItem: Cologne")}//Mutually Exclusive
        , {{quint16(0x0C44), quint16(0x0BE5)}, {quint8(1), quint8( 2)}, {QStringLiteral("mktpb")}, QT_TR_NOOP("KeyItem: Flower Cologne")}//Mutually Exclusive
        , {{quint16(0x0C44), quint16(0x0BE5)}, {quint8(2), quint8(3)}, {QStringLiteral("mktpb")}, QT_TR_NOOP("KeyItem: Sexy Cologne")}//Mutually Exclusive

        , {{quint16(0x0C44), quint16(0x0BE6)}, {quint8(6), quint8(0)}, {QStringLiteral("mkt_s2")}, QT_TR_NOOP("KeyItem: Pharmacy Coupon")}
        , {{quint16(0x0C44), quint16(0x0BE4)}, {quint8(7), quint8(3)}, {QStringLiteral("mkt_mens")}, QT_TR_NOOP("KeyItem: Wig")}//Mutually Exclusive
        , {{quint16(0x0C44), quint16(0x0BE4)}, {quint8(7), quint8(4)}, {QStringLiteral("mkt_mens")}, QT_TR_NOOP("KeyItem: Dyed Wig")}//Mutually Exclusive
        , {{quint16(0x0C44), quint16(0x0BE4)}, {quint8(7), quint8(5)}, {QStringLiteral("mkt_mens")}, QT_TR_NOOP("KeyItem: Blonde Wig")}//Mutually Exclusive

        , {{quint16(0x0C45), quint16(0x0C45), quint16(0x0BE4)}, {quint8(3), quint8(5), quint8(0)}, {QStringLiteral("mkt_s1")}, QT_TR_NOOP("KeyItem: Cotton Dress")}//Mutually Exclusive
        , {{quint16(0x0C45), quint16(0x0C45), quint16(0x0BE4)}, {quint8(3), quint8(6), quint8(1)}, {QStringLiteral("mkt_s1")}, QT_TR_NOOP("KeyItem: Satin Dress")}//Mutually Exclusive
        , {{quint16(0x0C45), quint16(0x0C45), quint16(0x0BE4)}, {quint8(3), quint8(7), quint8(2)}, {QStringLiteral("mkt_s1")}, QT_TR_NOOP("KeyItem: Silk Dress")}//Mutually Exclusive

        , {{quint16(0x0C46), quint16(0x0BE6)}, {quint8(0), quint8(1)}, {QStringLiteral("mkt_s3")}, QT_TR_NOOP("KeyItem: Disinfectant")}//Mutually Exclusive
        , {{quint16(0x0C46), quint16(0x0BE6)}, {quint8(1), quint8(2)}, {QStringLiteral("mkt_s3")}, QT_TR_NOOP("KeyItem: Deodorant")}//Mutually Exclusive
        , {{quint16(0x0C46), quint16(0x0BE6)}, {quint8(2), quint8(3)}, {QStringLiteral("mkt_s3")}, QT_TR_NOOP("KeyItem: Digestive")}//Mutually Exclusive

        , {{quint16(0x0C46), quint16(0x0BE4)}, {quint8(6), quint8(6)}, {QStringLiteral("mkt_m")}, QT_TR_NOOP("KeyItem: Glass Tiara")} //Mutally Exclusive
        , {{quint16(0x0C46), quint16(0x0BE4)}, {quint8(5), quint8(7)}, {QStringLiteral("mkt_m")}, QT_TR_NOOP("KeyItem: Ruby Tiara")}//Mutually Exclusive
        , {{quint16(0x0C46), quint16(0x0BE5)}, {quint8(4), quint8(0)}, {QStringLiteral("mkt_m")}, QT_TR_NOOP("KeyItem: Diamond Tiara")}//Mutually Exclusive

        , {{quint16(0x0C49), quint16(0x0C49), quint16(0x0C49)}, {quint8(5), quint8(6), quint8(7)}, {QStringLiteral("mkt_w")}, QT_TR_NOOP("Batteries")}

        , {{quint16(0x0C4C), quint16(0x0F05)}, {quint8(5), quint8(1)}, {QStringLiteral("convil_4"), QStringLiteral("bonevil")}, QT_TR_NOOP("Phoenix")}

        , {{quint16(0x0C55)}, {quint8(4)}, {QStringLiteral("convil_2")}, QT_TR_NOOP("Magic Comb")}
        , {{quint16(0x0C55)}, {quint8(5)}, {QStringLiteral("convil_2")}, QT_TR_NOOP("Peace Ring")}
        , {{quint16(0x0C55)}, {quint8(6)}, {QStringLiteral("convil_2")}, QT_TR_NOOP("Megalixir")}
        , {{quint16(0x0C55)}, {quint8(7)}, {QStringLiteral("convil_2")}, QT_TR_NOOP("Super Ball")}

        , {{quint16(0x0C6B)}, {quint8(4)}, {QStringLiteral("hyou13_2")}, QT_TR_NOOP("Alexander")}
        , {{quint16(0x0C6B)}, {quint8(5)}, {QStringLiteral("move_d")}, QT_TR_NOOP("Added Cut")}
        , {{quint16(0x0C6B)}, {quint8(6)}, {QStringLiteral("hyou12")}, QT_TR_NOOP("All")}

        , {{quint16(0x0C84), quint16(0x0C84)}, {quint8(0), quint8(6)}, {QStringLiteral("blin62_1")}, QT_TR_NOOP("Can Advance")}

        , {{quint16(0x0C86), quint16(0x0BE8)}, {quint8(5), quint8(2)}, {QStringLiteral("blin68_1")}, QT_TR_NOOP("KeyItem: KeyCard 68")}
        , {{quint16(0x0C8B), quint16(0x0BE7)}, {quint8(3), quint8(3)}, {QStringLiteral("bonevil")}, QT_TR_NOOP("KeyItem: Lunar Harp")}
        , {{quint16(0x0C8C), quint16(0x0BE7)}, {quint8(1), quint8(4)}, {QStringLiteral("sinin2_1")}, QT_TR_NOOP("KeyItem: Key To Basement")}
        //Below share same bit you can only get one possible error in the field script
        , {{quint16(0x0CBD)}, {quint8(1)}, {QStringLiteral("nivl_3")}, QT_TR_NOOP("Mind Plus")}
        , {{quint16(0x0CBD)}, {quint8(1)}, {QStringLiteral("nivinn_1")}, QT_TR_NOOP("Luck Source")}

        , {{quint16(0x0CBD)}, {quint8(2)}, {QStringLiteral("niv_w")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0CBD)}, {quint8(3)}, {QStringLiteral("niv_ti1")}, QT_TR_NOOP("Turbo Ether")}
        , {{quint16(0x0CBD)}, {quint8(4)}, {QStringLiteral("niv_ti2")}, QT_TR_NOOP("Platinum Fist")}
        , {{quint16(0x0CBD)}, {quint8(5)}, {QStringLiteral("nvmin1_2")}, QT_TR_NOOP("Luck Source")}

        , {{quint16(0x0CEC), quint16(0x0BE9)}, {quint8(7), quint8(1)}, {QStringLiteral("gldst"), QStringLiteral("games_1")}, QT_TR_NOOP("KeyItem: Gold Ticket")}
        , {{quint16(0x0CF1)}, {quint8(0)}, {QStringLiteral("games_1")}, QT_TR_NOOP("Gil Plus")}
        , {{quint16(0x0CF1)}, {quint8(1)}, {QStringLiteral("games_1")}, QT_TR_NOOP("Exp Plus")}
        , {{quint16(0x0CF2)}, {quint8(6)}, {QStringLiteral("coloss")}, QT_TR_NOOP("Sprint Shoes")}
        , {{quint16(0x0CF3)}, {quint8(5)}, {QStringLiteral("coloin1")}, QT_TR_NOOP("Omnislash")}
        , {{quint16(0x0CF3)}, {quint8(6)}, {QStringLiteral("coloin1")}, QT_TR_NOOP("W-Summon")}

        , {{quint16(0x0D65)}, {quint8(7)}, {QStringLiteral("min51_2")}, QT_TR_NOOP("Found hidden draw")}

        , {{quint16(0x0D44), quint16(0x0D65)}, {quint8(5), quint8(7)}, {QStringLiteral("min51_2")}, QT_TR_NOOP("Stole boys 5 gil")}
        , {{quint16(0x0D44), quint16(0x0D65)}, {quint8(6), quint8(7)}, {QStringLiteral("min51_2")}, QT_TR_NOOP("Turbo Ether")}

        , {{quint16(0x0D4C), quint16(0x0BE7)}, {quint8(1), quint8(6)}, {QStringLiteral("blin59")}, QT_TR_NOOP("KeyItem: Keycard 60")}

        , {{quint16(0x0D55)}, {quint8(4)}, {QStringLiteral("blin63_1")}, QT_TR_NOOP("Initialized the Machine")}
        , {{quint16(0x0D55), quint16(0x0BE9)}, {quint8(1), quint8(5)}, {QStringLiteral("blin63_1")}, QT_TR_NOOP("KeyItem: A Coupon")}
        , {{quint16(0x0D55), quint16(0x0BE9)}, {quint8(3), quint8(6)}, {QStringLiteral("blin63_1")}, QT_TR_NOOP("KeyItem: B Coupon")}
        , {{quint16(0x0D55), quint16(0x0BE9)}, {quint8(2), quint8(7)}, {QStringLiteral("blin63_1")}, QT_TR_NOOP("KeyItem: C Coupon")}
        //Can't Seam to varify these found in script never on field
        //, {{quint16(0x0D55)}, {quint8(5)}, {QStringLiteral("blin63_1")}, QT_TR_NOOP("Hourglass")}
        //, {{quint16(0x0D55)}, {quint8(6)}, {QStringLiteral("blin63_1")}, QT_TR_NOOP("All")}
        //Reward For Trading in the A B or C Coupon(s)
        , {{quint16(0x0D5D)}, {quint8(5)}, {QStringLiteral("blin63_1")}, QT_TR_NOOP("Star Pendant")}
        , {{quint16(0x0D5D)}, {quint8(6)}, {QStringLiteral("blin63_1")}, QT_TR_NOOP("All")}
        , {{quint16(0x0D5D)}, {quint8(7)}, {QStringLiteral("blin63_1")}, QT_TR_NOOP("Four Slots")}

        //MainProgress >=1008 for the one below
        , {{quint16(0x0D55)}, {quint8(7)}, {QStringLiteral("blin63_1")}, QT_TR_NOOP("Grow Lance")}

        , {{quint16(0x0D57), quint16(0x0BE8)}, {quint8(4), quint8(0)}, {QStringLiteral("blin62_1")}, QT_TR_NOOP("KeyItem: Keycard 65")}

        , {{quint16(0x0D60)}, {quint8(1)}, {QStringLiteral("blin62_1")}, QT_TR_NOOP("Elemental")}

        , {{quint16(0x0D63)}, {quint8(4)}, {QStringLiteral("yufy1")}, QT_TR_NOOP("MP Absorb")}

        , {{quint16(0x0D65), quint16(0x0F05)}, {quint8(3), quint8(0)}, {QStringLiteral("bugin1b"), QStringLiteral("bonevil")}, QT_TR_NOOP("Bahamut Zero")}
        , {{quint16(0x0D65)}, {quint8(4)}, {QStringLiteral("gidun_4")}, QT_TR_NOOP("Turbo Ether")}

        , {{quint16(0x0D66)}, {quint8(0)}, {QStringLiteral("min51_2")}, QT_TR_NOOP("Turtle Paradise Flyer #1")}
        , {{quint16(0x0D66)}, {quint8(1)}, {QStringLiteral("blin1")}, QT_TR_NOOP("Turtle Paradise Flyer #2")}
        , {{quint16(0x0D66)}, {quint8(2)}, {QStringLiteral("ghotin_1")}, QT_TR_NOOP("Turtle Paradise Flyer #3")}
        , {{quint16(0x0D66)}, {quint8(3)}, {QStringLiteral("cosin1")}, QT_TR_NOOP("Turtle Paradise Flyer #4")}
        , {{quint16(0x0D66)}, {quint8(4)}, {QStringLiteral("cosin3")}, QT_TR_NOOP("Turtle Paradise Flyer #5")}
        , {{quint16(0x0D66)}, {quint8(5)}, {QStringLiteral("yufy2")}, QT_TR_NOOP("Turtle Paradise Flyer #6")}
        , {{quint16(0x0D66)}, {quint8(6)}, {QStringLiteral("uutai1")}, QT_TR_NOOP("Turtle Paradise Flyer #7")}
        , {{quint16(0x0D66)}, {quint8(7)}, {QStringLiteral("utapb")}, QT_TR_NOOP("Rewarded for viewing all Turtle Paradise Flyers")}

        , {{quint16(0x0D7B)}, {quint8(3)}, {QStringLiteral("junpb_2")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0D7B)}, {quint8(4)}, {QStringLiteral("mds7_w2")}, QT_TR_NOOP("All")}
        , {{quint16(0x0D7B)}, {quint8(5)}, {QStringLiteral("mds7_w2")}, QT_TR_NOOP("Ether")}

        , {{quint16(0x0D81), quint16(0x0BE5)}, {quint8(0), quint8(7)}, {QStringLiteral("onna_52")}, QT_TR_NOOP("KeyItem: Bikini briefs")} //Mutually Exclusive
        , {{quint16(0x0D81), quint16(0x0D81), quint16(0x0BE5)}, {quint8(0), quint8(1), quint8(5)}, {QStringLiteral("onna_52")}, QT_TR_NOOP("KeyItem: Lingerie")}//Mutually Exclusive

        , {{quint16(0x0D90)}, {quint8(5)}, {QStringLiteral("junpb_2")}, QT_TR_NOOP("Enemy Skill")}

        , {{quint16(0x0D93)}, {quint8(3)}, {QStringLiteral("kuro_7")}, QT_TR_NOOP("Work Glove")}
        , {{quint16(0x0D93)}, {quint8(4)}, {QStringLiteral("kuro_5")}, QT_TR_NOOP("Nail Bat")}

        , {{quint16(0x0E2E)}, {quint8(5)}, {QStringLiteral("crcin_1")}, QT_TR_NOOP("Rewards From Ester")}

        , {{quint16(0x0E38)}, {quint8(3)}, {QStringLiteral("games_2")}, QT_TR_NOOP("Speed Source")}
        , {{quint16(0x0E38)}, {quint8(5)}, {QStringLiteral("games_2")}, QT_TR_NOOP("Ink")}
        , {{quint16(0x0E38)}, {quint8(6)}, {QStringLiteral("games_2")}, QT_TR_NOOP("T/S Bomb")}
        , {{quint16(0x0E38)}, {quint8(7)}, {QStringLiteral("games_2")}, QT_TR_NOOP("Dragon Fang")}

        , {{quint16(0x0E3D)}, {quint8(0)}, {QStringLiteral("games_2")}, QT_TR_NOOP("Dragon Scales")}
        , {{quint16(0x0E3D)}, {quint8(1)}, {QStringLiteral("games_2")}, QT_TR_NOOP("Cauldron")}
        , {{quint16(0x0E3D)}, {quint8(2)}, {QStringLiteral("farm")}, QT_TR_NOOP("Chocobo Lure")}

        , {{quint16(0x0EA5)}, {quint8(1)}, {QStringLiteral("niv_ti2")}, QT_TR_NOOP("Final Heaven (+other stuff?)")}
        //, {{quint16(0x0EA5)}, {quint8(2)}, {QStringLiteral("niv_ti2")}, QT_TR_NOOP("Played piano durring flashback")}
        , {{quint16(0x0EA5)}, {quint8(4)}, {QStringLiteral("niv_ti2")}, QT_TR_NOOP("Elemental(+other stuff?)")}

        , {{quint16(0x0FA4)}, {quint8(1)}, {QStringLiteral("gaiin_4")}, QT_TR_NOOP("Enhance Sword")}
        , {{quint16(0x0FA4)}, {quint8(2)}, {QStringLiteral("gaiin_5")}, QT_TR_NOOP("Fire Armlet")}
        , {{quint16(0x0FA4)}, {quint8(3)}, {QStringLiteral("gaiin_3")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0FA4)}, {quint8(4)}, {QStringLiteral("gaiin_3")}, QT_TR_NOOP("Speed Source")}
        , {{quint16(0x0FA4)}, {quint8(5)}, {QStringLiteral("gaiin_1")}, QT_TR_NOOP("Javelin")}
        , {{quint16(0x0FA4)}, {quint8(6)}, {QStringLiteral("gaiin_5")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0FA4)}, {quint8(7)}, {QStringLiteral("gaiin_1")}, QT_TR_NOOP("Ribbon")}

        , {{quint16(0x0FA5)}, {quint8(0)}, {QStringLiteral("ncoin1")}, QT_TR_NOOP("Ether")}
        , {{quint16(0x0FA5)}, {quint8(1)}, {QStringLiteral("ncoin3")}, QT_TR_NOOP("Catastrophe")}
        , {{quint16(0x0FA5)}, {quint8(2)}, {QStringLiteral("snmin2")}, QT_TR_NOOP("Hero Drink")}
        , {{quint16(0x0FA5)}, {quint8(3)}, {QStringLiteral("snmin2")}, QT_TR_NOOP("Vaccine")}
        , {{quint16(0x0FA5)}, {quint8(4)}, {QStringLiteral("sninn_2")}, QT_TR_NOOP("X-Potion")}
        , {{quint16(0x0FA5)}, {quint8(5)}, {QStringLiteral("snmayor")}, QT_TR_NOOP("Turbo Ether")}

        , {{quint16(0x0FA6)}, {quint8(0)}, {QStringLiteral("trnad_2")}, QT_TR_NOOP("Neo Bahamut")}
        , {{quint16(0x0FA6)}, {quint8(1)}, {QStringLiteral("trnad_4")}, QT_TR_NOOP("Poison Ring")}
        , {{quint16(0x0FA6)}, {quint8(2)}, {QStringLiteral("trnad_3")}, QT_TR_NOOP("Hero Drink")}
        , {{quint16(0x0FA6)}, {quint8(3)}, {QStringLiteral("trnad_4")}, QT_TR_NOOP("MP Turbo")}

        , {{quint16(0x0FC4)}, {quint8(0)}, {QStringLiteral("md1stin")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0FC4)}, {quint8(1)}, {QStringLiteral("md1stin")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0FC4)}, {quint8(2)}, {QStringLiteral("nmkin_3")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0FC4)}, {quint8(3)}, {QStringLiteral("nmkin_1")}, QT_TR_NOOP("Phoenix Down")}
        , {{quint16(0x0FC4)}, {quint8(4)}, {QStringLiteral("blin67_1")}, QT_TR_NOOP("Poison")}
        , {{quint16(0x0FC4)}, {quint8(5)}, {QStringLiteral("colne_b1")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0FC4)}, {quint8(7)}, {QStringLiteral("blin68_1")}, QT_TR_NOOP("Potion")}

        , {{quint16(0x0FC5)}, {quint8(0)}, {QStringLiteral("blin68_1")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0FC5)}, {quint8(1)}, {QStringLiteral("blin68_1")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0FC5)}, {quint8(2)}, {QStringLiteral("blin68_1")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0FC5)}, {quint8(3)}, {QStringLiteral("sandun_1")}, QT_TR_NOOP("Bolt Armlet")}
        , {{quint16(0x0FC5)}, {quint8(4)}, {QStringLiteral("sandun_1")}, QT_TR_NOOP("HypnoCrown")} // add var[5][58] == 1 to this.
        , {{quint16(0x0FC5)}, {quint8(5)}, {QStringLiteral("sandun_1")}, QT_TR_NOOP("Megalixir")}
        , {{quint16(0x0FC5)}, {quint8(6)}, {QStringLiteral("smkin_1")}, QT_TR_NOOP("Ether")}
        , {{quint16(0x0FC5)}, {quint8(7)}, {QStringLiteral("slfrst_2")}, QT_TR_NOOP("Kujata")}

        , {{quint16(0x0FC6), quint16(0x0FC6)}, {quint8(0), quint8(1)}, {QStringLiteral("sininb42")}, QT_TR_NOOP("Destruct")}
        , {{quint16(0x0FC6), quint16(0x0FC6)}, {quint8(2), quint8(3)}, {QStringLiteral("blin68_1"), QStringLiteral("blin68_2")}, QT_TR_NOOP("Enemy Skill")}
        , {{quint16(0x0FC6), quint16(0x0FC6)}, {quint8(4), quint8(5)}, {QStringLiteral("sinin2_1")}, QT_TR_NOOP("Odin")}
        , {{quint16(0x0FC6)}, {quint8(6)}, {QStringLiteral("nvdun1")}, QT_TR_NOOP("Counter")}
        , {{quint16(0x0FC6)}, {quint8(7)}, {QStringLiteral("sandun_1")}, QT_TR_NOOP("Magic Plus")}

        , {{quint16(0x0FC7)}, {quint8(0)}, {QStringLiteral("colne_b1")}, QT_TR_NOOP("Steal")}
        , {{quint16(0x0FC7)}, {quint8(1)}, {QStringLiteral("sinin1_2")}, QT_TR_NOOP("Twin Viper")}
        , {{quint16(0x0FC7)}, {quint8(2)}, {QStringLiteral("sinin1_2")}, QT_TR_NOOP("Silver M-phone")}
        , {{quint16(0x0FC7)}, {quint8(3)}, {QStringLiteral("sinin2_1")}, QT_TR_NOOP("Enemy Launcher")}
        , {{quint16(0x0FC7)}, {quint8(4)}, {QStringLiteral("sinin2_2")}, QT_TR_NOOP("Magic Source")}
        , {{quint16(0x0FC7)}, {quint8(5)}, {QStringLiteral("bonevil")}, QT_TR_NOOP("Buntline")}
        , {{quint16(0x0FC7)}, {quint8(6)}, {QStringLiteral("loslake1")}, QT_TR_NOOP("Aurora Armlet")}
        , {{quint16(0x0FC7)}, {quint8(7)}, {QStringLiteral("sango3")}, QT_TR_NOOP("Viper Halberd")}

        , {{quint16(0x0FC8)}, {quint8(0)}, {QStringLiteral("mtnvl2")}, QT_TR_NOOP("Rune Blade")}
        , {{quint16(0x0FC8)}, {quint8(1)}, {QStringLiteral("mtnvl2")}, QT_TR_NOOP("Plus Barrette")}
        , {{quint16(0x0FC8)}, {quint8(2)}, {QStringLiteral("nvdun1")}, QT_TR_NOOP("Powersoul")}
        , {{quint16(0x0FC8)}, {quint8(3)}, {QStringLiteral("nvdun4")}, QT_TR_NOOP("Sniper CR")}
        , {{quint16(0x0FC8)}, {quint8(4)}, {QStringLiteral("nvdun2")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0FC8)}, {quint8(5)}, {QStringLiteral("nvdun1")}, QT_TR_NOOP("All")}
        , {{quint16(0x0FC8)}, {quint8(6)}, {QStringLiteral("nvdun3")}, QT_TR_NOOP("Elemental")}

        , {{quint16(0x0FC9)}, {quint8(0)}, {QStringLiteral("sundun_2")}, QT_TR_NOOP("Power Source")}
        , {{quint16(0x0FC9)}, {quint8(1)}, {QStringLiteral("sango1")}, QT_TR_NOOP("Water Ring")}
        , {{quint16(0x0FC9)}, {quint8(2)}, {QStringLiteral("anfrst_2")}, QT_TR_NOOP("Typhon")}
        , {{quint16(0x0FC9)}, {quint8(3)}, {QStringLiteral("anfrst_3")}, QT_TR_NOOP("Supershot ST")}
        , {{quint16(0x0FC9)}, {quint8(4)}, {QStringLiteral("anfrst_1")}, QT_TR_NOOP("Slash-All")}
        , {{quint16(0x0FC9)}, {quint8(5)}, {QStringLiteral("anfrst_1")}, QT_TR_NOOP("Minerva Band")}
        , {{quint16(0x0FC9)}, {quint8(6)}, {QStringLiteral("anfrst_5")}, QT_TR_NOOP("Apocalypse")}
        , {{quint16(0x0FC9)}, {quint8(7)}, {QStringLiteral("anfrst_5")}, QT_TR_NOOP("Elixir")}

        , {{quint16(0x0FCA)}, {quint8(0)}, {QStringLiteral("anfrst_3")}, QT_TR_NOOP("Spring Gun Clip")}
        , {{quint16(0x0FCA)}, {quint8(1)}, {QStringLiteral("bonevil")}, QT_TR_NOOP("Mop")}
        , {{quint16(0x0FCA)}, {quint8(2)}, {QStringLiteral("bonevil")}, QT_TR_NOOP("Megalixir")}
        , {{quint16(0x0FCA), quint16(0x0BE7)}, {quint8(3), quint8(5)}, {QStringLiteral("mds5_5"), QStringLiteral("bonevil")}, QT_TR_NOOP("KeyItem: Key To Sector 5")}

        , {{quint16(0x0FF4)}, {quint8(0)}, {QStringLiteral("sbwy4_6")}, QT_TR_NOOP("Tent")}
        , {{quint16(0x0FF4)}, {quint8(1)}, {QStringLiteral("sbwy4_3")}, QT_TR_NOOP("Potion")}
        , {{quint16(0x0FF4)}, {quint8(2)}, {QStringLiteral("sbwy4_1")}, QT_TR_NOOP("Ether")}
        , {{quint16(0x0FF4)}, {quint8(3)}, {QStringLiteral("psdun_3")}, QT_TR_NOOP("Ether")}
        , {{quint16(0x0FF4)}, {quint8(4)}, {QStringLiteral("psdun_4")}, QT_TR_NOOP("Hi-Potion")}
        , {{quint16(0x0FF4)}, {quint8(5)}, {QStringLiteral("psdun_4")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0FF4)}, {quint8(6)}, {QStringLiteral("psdun_3")}, QT_TR_NOOP("Long Range")}
        , {{quint16(0x0FF4)}, {quint8(7)}, {QStringLiteral("gnmk")}, QT_TR_NOOP("Titan")}

        , {{quint16(0x0FF5)}, {quint8(0)}, {QStringLiteral("elmin2_2")}, QT_TR_NOOP("Ether")}
        , {{quint16(0x0FF5)}, {quint8(1)}, {QStringLiteral("losin1")}, QT_TR_NOOP("Comet")}
        , {{quint16(0x0FF5)}, {quint8(2)}, {QStringLiteral("gonjun1")}, QT_TR_NOOP("Deathblow")}
        , {{quint16(0x0FF5)}, {quint8(3)}, {QStringLiteral("q_4")}, QT_TR_NOOP("Hades")}
        , {{quint16(0x0FF5)}, {quint8(4)}, {QStringLiteral("q_4")}, QT_TR_NOOP("Outsider")}
        , {{quint16(0x0FF5)}, {quint8(5)}, {QStringLiteral("q_3")}, QT_TR_NOOP("Escort Guard")}
        , {{quint16(0x0FF5)}, {quint8(6)}, {QStringLiteral("q_3")}, QT_TR_NOOP("Conformer")}
        , {{quint16(0x0FF5)}, {quint8(7)}, {QStringLiteral("q_4")}, QT_TR_NOOP("Spirit Lance")}

        , {{quint16(0x0FF6)}, {quint8(0)}, {QStringLiteral("q_1")}, QT_TR_NOOP("Heaven's Cloud")}
        , {{quint16(0x0FF6)}, {quint8(1)}, {QStringLiteral("q_3")}, QT_TR_NOOP("Megalixir")}
        , {{quint16(0x0FF6)}, {quint8(2)}, {QStringLiteral("q_4")}, QT_TR_NOOP("Megalixir")}
        , {{quint16(0x0FF6)}, {quint8(3)}, {QStringLiteral("losinn")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0FF6)}, {quint8(4)}, {QStringLiteral("losin2")}, QT_TR_NOOP("Guard Source")}
        , {{quint16(0x0FF6)}, {quint8(5)}, {QStringLiteral("losin3")}, QT_TR_NOOP("Magic Source")}
        , {{quint16(0x0FF6)}, {quint8(6)}, {QStringLiteral("las1_2"), QStringLiteral("las4_0")}, QT_TR_NOOP("Elixir")} //also needs to edit 11[142]:4 (field var) on las4_0
        , {{quint16(0x0FF6)}, {quint8(7)}, {QStringLiteral("las1_2"), QStringLiteral("las4_0")}, QT_TR_NOOP("Mystile")} //also needs to edit 11[142]:1 (field var) on las4_0

        , {{quint16(0x0FF7)}, {quint8(0)}, {QStringLiteral("las1_2"), QStringLiteral("las1_3"), QStringLiteral("las0_4")}, QT_TR_NOOP("Speed Source")} //also needs to edit 11[142]:3 on las4_0
        , {{quint16(0x0FF7)}, {quint8(1)}, {QStringLiteral("las1_3")}, QT_TR_NOOP("Tetra Elemental")}
        , {{quint16(0x0FF7)}, {quint8(2)}, {QStringLiteral("las1_3"), QStringLiteral("las4_0")}, QT_TR_NOOP("Megalixir")}// also needs to edit 11[142]:6 on las4_0
        , {{quint16(0x0FF7)}, {quint8(3)}, {QStringLiteral("las1_3"), QStringLiteral("las4_0")}, QT_TR_NOOP("Megalixir")} // also needs to edit 11[142]:2 on las4_0
        , {{quint16(0x0FF7)}, {quint8(4)}, {QStringLiteral("las0_5")}, QT_TR_NOOP("Power Source")}
        , {{quint16(0x0FF7)}, {quint8(5)}, {QStringLiteral("las0_5")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x0FF7)}, {quint8(6)}, {QStringLiteral("las0_4"), QStringLiteral("las4_0")}, QT_TR_NOOP("Guard Source")} //also needs to edit 11[142]:0 (field var) on las4_0
        , {{quint16(0x0FF7)}, {quint8(7)}, {QStringLiteral("las0_5"), QStringLiteral("las4_0")}, QT_TR_NOOP("Mind Source")} //also needs to edit 11[142]:2 (field var) on las4_0

        , {{quint16(0x0FF8)}, {quint8(0)}, {QStringLiteral("goson")}, QT_TR_NOOP("White M-phone")}
        , {{quint16(0x0FF8)}, {quint8(1)}, {QStringLiteral("gninn")}, QT_TR_NOOP("X-Potion")}
        , {{quint16(0x0FF8)}, {quint8(2)}, {QStringLiteral("rktsid")}, QT_TR_NOOP("Drill Arm")}
        , {{quint16(0x0FF8)}, {quint8(3)}, {QStringLiteral("rktmin2")}, QT_TR_NOOP("Power Source")}
        , {{quint16(0x0FF8)}, {quint8(4)}, {QStringLiteral("rckt")}, QT_TR_NOOP("Yoshiyuki")}
        , {{quint16(0x0FF8)}, {quint8(5)}, {QStringLiteral("rckt2")}, QT_TR_NOOP("Venus Gospel")}
        , {{quint16(0x0FF8)}, {quint8(6)}, {QStringLiteral("las0_4")}, QT_TR_NOOP("Save Crystal")}
        , {{quint16(0x0FF8)}, {quint8(7)}, {QStringLiteral("elmtow")}, QT_TR_NOOP("Peacemaker")}

        , {{quint16(0x0FF9)}, {quint8(0)}, {QStringLiteral("losinn")}, QT_TR_NOOP("Enemy Skill")}
        , {{quint16(0x0FF9)}, {quint8(1)}, {QStringLiteral("elmin1_1")}, QT_TR_NOOP("Ether")}
        , {{quint16(0x0FF9)}, {quint8(2)}, {QStringLiteral("las0_5")}, QT_TR_NOOP("Magic Source")}
        , {{quint16(0x0FF9)}, {quint8(3)}, {QStringLiteral("elmin3_2")}, QT_TR_NOOP("Guard Source")}
        , {{quint16(0x0FF9)}, {quint8(4)}, {QStringLiteral("elmin4_1")}, QT_TR_NOOP("Ether")} // shown if(5[9] ==0)
        , {{quint16(0x0FF9)}, {quint8(5)}, {QStringLiteral("rkt_w")}, QT_TR_NOOP("Fourth Bracelet")} // shown if gamemoment >999
        , {{quint16(0x0FF9)}, {quint8(6)}, {QStringLiteral("rkt_i")}, QT_TR_NOOP("Guard Source")} // shown if gamemoment >999
        , {{quint16(0x0FF9)}, {quint8(7)}, {QStringLiteral("elminn_2")}, QT_TR_NOOP("Megalixir")}

        , {{quint16(0x0FFA)}, {quint8(0)}, {QStringLiteral("las0_5")}, QT_TR_NOOP("Guard Source")}
        , {{quint16(0x0FFA)}, {quint8(1)}, {QStringLiteral("q_3")}, QT_TR_NOOP("Double Cut")}
        , {{quint16(0x0FFA)}, {quint8(2)}, {QStringLiteral("q_4")}, QT_TR_NOOP("Highwind")}
        , {{quint16(0x0FFA)}, {quint8(3)}, {QStringLiteral("las0_5")}, QT_TR_NOOP("HP Absorb")}
        , {{quint16(0x0FFA)}, {quint8(4)}, {QStringLiteral("psdun_2")}, QT_TR_NOOP("Mind Source")}
        , {{quint16(0x0FFA)}, {quint8(5)}, {QStringLiteral("psdun_3")}, QT_TR_NOOP("Tent")}

        , {{quint16(0x0FFB)}, {quint8(0)}, {QStringLiteral("elmin4_2")}, QT_TR_NOOP("Show Underwater")}
        , {{quint16(0x0FFB)}, {quint8(1)}, {QStringLiteral("elmin4_2")}, QT_TR_NOOP("Show Master Command")}
        , {{quint16(0x0FFB)}, {quint8(2)}, {QStringLiteral("elmin4_2")}, QT_TR_NOOP("Show Master Magic")}
        , {{quint16(0x0FFB)}, {quint8(3)}, {QStringLiteral("elmin4_2")}, QT_TR_NOOP("Show Master Summon")}
        , {{quint16(0x0FFB)}, {quint8(4)}, {QStringLiteral("elmin4_2")}, QT_TR_NOOP("Show Gold Chocobo")}

        , {{quint16(0x1014)}, {quint8(0)}, {QStringLiteral("kuro_3")}, QT_TR_NOOP("Morph")}
        , {{quint16(0x1014)}, {quint8(1)}, {QStringLiteral("kuro_1")}, QT_TR_NOOP("Luck Plus")}
        , {{quint16(0x1014)}, {quint8(2)}, {QStringLiteral("kuro_1")}, QT_TR_NOOP("Turbo Ether")}
        , {{quint16(0x1014)}, {quint8(3)}, {QStringLiteral("kuro_1")}, QT_TR_NOOP("Mind Source")}
        //, {{quint16(0x1014)}, {quint8(4)}, {QStringLiteral("kuro_6")}, QT_TR_NOOP("Battle #645")} //if(3[230]:0) Map version
        //, {{quint16(0x1014)}, {quint8(5)}, {QStringLiteral("kuro_6")}, QT_TR_NOOP("Battle #649")} //if(3[230]:2) map is used for
        , {{quint16(0x1014)}, {quint8(6)}, {QStringLiteral("kuro_6")}, QT_TR_NOOP("Princess Guard")}//if(3[230]:3) different rooms
        , {{quint16(0x1014)}, {quint8(7)}, {QStringLiteral("kuro_6")}, QT_TR_NOOP("Trumpet Shell")} //if(3[230]:5) 3[230] tracks the room

        , {{quint16(0x1015)}, {quint8(0)}, {QStringLiteral("kuro_6")}, QT_TR_NOOP("Megalixir")}   //if(3[230]:6)
        , {{quint16(0x1015)}, {quint8(1)}, {QStringLiteral("kuro_82")}, QT_TR_NOOP("Bahamut")} // if(Main Progress == 624)
        , {{quint16(0x1015)}, {quint8(2)}, {QStringLiteral("kuro_1")}, QT_TR_NOOP("Trident")}
        , {{quint16(0x1015)}, {quint8(3)}, {QStringLiteral("kuro_1")}, QT_TR_NOOP("Rocket Punch")}
        , {{quint16(0x1015)}, {quint8(4)}, {QStringLiteral("kuro_1")}, QT_TR_NOOP("Ribbon")}
        , {{quint16(0x1015)}, {quint8(6)}, {QStringLiteral("kuro_2")}, QT_TR_NOOP("Silver Rifle")}

        , {{quint16(0x1016)}, {quint8(0)}, {QStringLiteral("delmin12")}, QT_TR_NOOP("Motor Drive")}
        , {{quint16(0x1016)}, {quint8(1)}, {QStringLiteral("delmin12")}, QT_TR_NOOP("Fire Ring")}
        , {{quint16(0x1016)}, {quint8(2)}, {QStringLiteral("delmin12")}, QT_TR_NOOP("Power Source")}
        , {{quint16(0x1016)}, {quint8(3)}, {QStringLiteral("delmin1")}, QT_TR_NOOP("Purchased The House")}

        , {{quint16(0x1018)}, {quint8(1)}, {QStringLiteral("mtcrl_4")}, QT_TR_NOOP("W Machine Gun")}
        , {{quint16(0x1018)}, {quint8(2)}, {QStringLiteral("mtcrl_4")}, QT_TR_NOOP("Transform")}
        , {{quint16(0x1018)}, {quint8(3)}, {QStringLiteral("mtcrl_4")}, QT_TR_NOOP("Turbo Ether")}

        , {{quint16(0x1019)}, {quint8(0)}, {QStringLiteral("mtcrl_7")}, QT_TR_NOOP("Mind Source")}
        , {{quint16(0x1019)}, {quint8(1)}, {QStringLiteral("mtcrl_7")}, QT_TR_NOOP("Power Source")}
        , {{quint16(0x1019)}, {quint8(2)}, {QStringLiteral("mtcrl_7")}, QT_TR_NOOP("Tent")}

        , {{quint16(0x101A)}, {quint8(0)}, {QStringLiteral("junmin2")}, QT_TR_NOOP("Mind Source")}
        , {{quint16(0x101A)}, {quint8(1)}, {QStringLiteral("junmin3")}, QT_TR_NOOP("Power Source")}
        , {{quint16(0x101A)}, {quint8(2)}, {QStringLiteral("junmin3")}, QT_TR_NOOP("Guard Source")}
        , {{quint16(0x101A)}, {quint8(3)}, {QStringLiteral("junmin2")}, QT_TR_NOOP("Luck Source")}
        , {{quint16(0x101A)}, {quint8(4)}, {QStringLiteral("junmin2")}, QT_TR_NOOP("1/35 soldier")}
        , {{quint16(0x101A)}, {quint8(5)}, {QStringLiteral("junmin4")}, QT_TR_NOOP("Speed Source")}
        , {{quint16(0x101A)}, {quint8(6)}, {QStringLiteral("junmin5")}, QT_TR_NOOP("1/35 soldier")}

        , {{quint16(0x1031), quint16(0x0BE9)}, {quint8(0), quint8(3)}, {QStringLiteral("semkin_7")}, QT_TR_NOOP("KeyItem: Leviathan Scales")}
        , {{quint16(0x1031)}, {quint8(1)}, {QStringLiteral("datiao_8")}, QT_TR_NOOP("Steal-As-Well")}
        , {{quint16(0x1031)}, {quint8(3)}, {QStringLiteral("datiao_8")}, QT_TR_NOOP("Dragoon Lance")}
        , {{quint16(0x1031), quint16(0x0F05)}, {quint8(4), quint8(2)}, {QStringLiteral("tunnel_4"), QStringLiteral("bonevil")}, QT_TR_NOOP("W-Item")}
        , {{quint16(0x1031)}, {quint8(5)}, {QStringLiteral("md8_b1")}, QT_TR_NOOP("Max Ray")}
        , {{quint16(0x1031)}, {quint8(6)}, {QStringLiteral("md8_b1")}, QT_TR_NOOP("Aegis Armlet")}
        , {{quint16(0x1031)}, {quint8(7)}, {QStringLiteral("semkin_7")}, QT_TR_NOOP("Scimitar")}

        , {{quint16(0x1032)}, {quint8(0)}, {QStringLiteral("semkin_6")}, QT_TR_NOOP("Battle Trumpet")}
        , {{quint16(0x1032)}, {quint8(1)}, {QStringLiteral("tower5")}, QT_TR_NOOP("Leviathan")}
        , {{quint16(0x1032)}, {quint8(2)}, {QStringLiteral("md8_b1")}, QT_TR_NOOP("Megalixir")}
        , {{quint16(0x1032)}, {quint8(3)}, {QStringLiteral("datiao_8")}, QT_TR_NOOP("Oritsuru")}
        , {{quint16(0x1032)}, {quint8(4)}, {QStringLiteral("md8_b2")}, QT_TR_NOOP("Starlight Phone")}
        , {{quint16(0x1032)}, {quint8(5)}, {QStringLiteral("md8_b2")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x1032)}, {quint8(6)}, {QStringLiteral("md8_b1")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x1032)}, {quint8(7)}, {QStringLiteral("tunnel_5")}, QT_TR_NOOP("Magic Source")}

        , {{quint16(0x1035), quint16(0x0BE6)}, {quint8(3), quint8(7)}, {QStringLiteral("rcktin4")}, QT_TR_NOOP("KeyItem: Huge Materia: Rocket")}

        , {{quint16(0x1036)}, {quint8(0)}, {QStringLiteral("tunnel_5")}, QT_TR_NOOP("Mind Source")}
        , {{quint16(0x1036)}, {quint8(1)}, {QStringLiteral("tunnel_5")}, QT_TR_NOOP("Power Source")}
        , {{quint16(0x1036)}, {quint8(2)}, {QStringLiteral("tunnel_5")}, QT_TR_NOOP("Guard Source")}
        , {{quint16(0x1036)}, {quint8(3)}, {QStringLiteral("md8_32")}, QT_TR_NOOP("Mystile")}
        , {{quint16(0x1036)}, {quint8(4)}, {QStringLiteral("canon_1")}, QT_TR_NOOP("Missing Score")}
        , {{quint16(0x1036)}, {quint8(5)}, {QStringLiteral("md8_32")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x1036)}, {quint8(6)}, {QStringLiteral("las0_7")}, QT_TR_NOOP("Megalixir")}
        , {{quint16(0x1036)}, {quint8(7)}, {QStringLiteral("las0_7")}, QT_TR_NOOP("Power Source")}

        , {{quint16(0x1037)}, {quint8(0)}, {QStringLiteral("las0_7")}, QT_TR_NOOP("Guard Source")}
        , {{quint16(0x1037)}, {quint8(1)}, {QStringLiteral("las2_2"), QStringLiteral("las4_0")}, QT_TR_NOOP("Magic Source")}
        , {{quint16(0x1037)}, {quint8(2)}, {QStringLiteral("las2_2"), QStringLiteral("las4_0")}, QT_TR_NOOP("Remedy")}
        , {{quint16(0x1037)}, {quint8(3)}, {QStringLiteral("las2_3"), QStringLiteral("las4_0")}, QT_TR_NOOP("Hero Drink")}
        , {{quint16(0x1037)}, {quint8(4)}, {QStringLiteral("las2_3")}, QT_TR_NOOP("Vaccine")}
        , {{quint16(0x1037)}, {quint8(5)}, {QStringLiteral("las2_3"), QStringLiteral("las4_0")}, QT_TR_NOOP("Shield")}
        , {{quint16(0x1037)}, {quint8(6)}, {QStringLiteral("las0_4"), QStringLiteral("las4_0")}, QT_TR_NOOP("Counter")}
        , {{quint16(0x1037)}, {quint8(7)}, {QStringLiteral("las0_4"), QStringLiteral("las4_0")}, QT_TR_NOOP("W-Magic")}

        , {{quint16(0x1038)}, {quint8(0)}, {QStringLiteral("las2_3"), QStringLiteral("las4_0")}, QT_TR_NOOP("Imperial Guard")}
        , {{quint16(0x1038)}, {quint8(1)}, {QStringLiteral("las0_6")}, QT_TR_NOOP("Mind Source")}
        , {{quint16(0x1038)}, {quint8(2)}, {QStringLiteral("las0_6")}, QT_TR_NOOP("Hero Drink")}

        , {{quint16(0x1056)}, {quint8(3)}, {QStringLiteral("itmin2")}, QT_TR_NOOP("Elixir")}
        , {{quint16(0x1057)}, {quint8(0)}, {QStringLiteral("itown1b")}, QT_TR_NOOP("Contain")}
    };
};
