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
#include <QStringList>

/*! \class FF7Char
*   \brief Data and Enums for Characters in Final Fantasy 7
*/

class FF7Char : public QObject
{
    Q_OBJECT
public:
    enum FF7CharId {
        Cloud/**<0*/
        , Barret/**<1*/
        , Tifa/**<2*/
        , Aerith/**<3*/
        , Red/**<4*/
        , Yuffie/**<5*/
        , CaitSith/**<6*/
        , Vincent/**<7*/
        , Cid/**<8*/
        , YoungCloud/**<9*/
        , Sephiroth/**<10*/
        , Empty = 0xFF/**<0xFF*/
    };
    Q_ENUM(FF7CharId)

    enum FF7CharStatus {
        Sadness = 0x10 /**<0x10*/
        , Fury = 0x20   /**<0x20*/
        , BackRow = 0xFE/**<0xFE*/
        , FrontRow = 0xFF /**<0xFF*/
    };
    Q_ENUM(FF7CharStatus)

    enum CharSpecial {
        EmptyArmor = 0xFF /**<0xFF*/
        , EmptyAccessory = 0xFF /**<0xFF*/
    };
    Q_ENUM(CharSpecial)

    FF7Char() = default;
    ~FF7Char() = default;
    /*! \brief get id value for Character
     * \param who persons id  (they are almost always the same in stock game)
     * \return Chars[who].id
     */
    Q_INVOKABLE inline quint8 id(int who)
    {
        return character(who)._id;
    }
    /*! \brief number of weapons for a Character
     * \param who Characters id number
     * \return Number of Weapons for the given character
     */
    Q_INVOKABLE inline int numberOfWeapons(int who)
    {
        return character(who)._num_weapons;
    }

    /*! \brief find what item id is the first weapon for a Character
     * \param who Characters id number
     * \return Item Id of characters first weapon
     */
    Q_INVOKABLE inline int weaponStartingId(int who)
    {
        return character(who)._starting_weapon_id;
    }

    /*! \brief find what weapon number is the first weapon for a Character
     * \param who Characters id number
     * \return Weapon number of characters first weapon
     */
    Q_INVOKABLE inline int weaponOffset(int who)
    {
        return character(who)._weapon_offset;
    }

    /*! \brief default name for a character
     * \param who Characters id number
     * \return Translated default name for character
     */
    Q_INVOKABLE QString defaultName(int who);

    /*! \brief Menu icon for a character
     * \param who Characters id number
     * \return QImage of a characters menu icon
     * \sa icon(),pixmap()
     */
    inline QImage image(int who)
    {
        return QImage(character(who)._avatarString);
    }

    /*! \brief Menu icon for a character
     * \param who Characters id number
     * \return QIcon of a characters menu icon
     * \sa image(),pixmap()
     */
    inline QIcon icon(int who)
    {
        return QIcon(pixmap(who));
    }

    /*! \brief Menu icon for a character
     * \param who Characters id number
     * \return QPixmap of a characters menu icon
     * \sa icon(),image()
     */
    inline QPixmap pixmap(int who)
    {
        return QPixmap(character(who)._avatarString);
    }

    /*! \brief Limit list for a character
     * \param who Characters id number
     * \return QStringList of Translated names for each limit break
     */
    Q_INVOKABLE QStringList limits(int who);

    /*! \brief Exp needed to reach a level
     * \param who Characters id number
     * \param level Level you want to reach
     * \return Total amount of Exp needed to reach level (ex. to reach level 99 you need 20000000 xp)
     */
    Q_INVOKABLE quint32 totalExpForLevel(int who, int level);

    /*! \brief experance needed to level up
     * \param who Characters id number
     * \param level Level you are trying to reach
     * \return Exp needed to reach the next level. (i.e from 9 to 10 you need 50 exp)
     */
    Q_INVOKABLE quint32 tnlForLevel(int who, int level);

    /*! \brief how much to increase stat on level up
     * \param who Characters id number
     * \param stat Stat you want to gain a point in (stat: 0 str, 1 vit, 2 mag, 3 spi, 4 dex, 5 luck,6 hp,7mp)
     * \param stat_amount current value for that stat
     * \param current_lvl characters current level
     * \param next_lvl level the character is becoming
     * \return how many points to be put in stat.
     */
    Q_INVOKABLE int statGain(int who, int stat, int stat_amount, int current_lvl, int next_lvl);

    /*! \brief convert bit to limit offset
     * \param bit to convert
     * \return limit offset to change
     */
    Q_INVOKABLE int limitBitConvert(int bit);
private:
    /*! \brief characters grade in a stat
    * \param who Characters id number
    * \param stat Stat you want to get grade for (stat: 0 str, 1 vit, 2 mag, 3 spi, 4 dex, 5 luck,6 hp,7mp)
    * \return characters grade in a stat
    */
    inline int stat_grade(int who, int stat)
    {
        return character(who)._stat_grade.at(stat);
    }

    /*! \brief characters base mp for set of levels
    * \param who Characters id number
    * \param lvl_bracket bracket the level falls in (0: lvl 0-9 . 1: 10-19. etc..)
    * \return characters base mp for that bracket
    */
    inline int mp_base(int who, int lvl_bracket)
    {
        return character(who)._mp_base.at(lvl_bracket);
    }

    /*! \brief characters mp gradent for set of levels
    * \param who Characters id number
    * \param lvl_bracket bracket the level falls in (0: lvl 0-9 . 1: 10-19. etc..)
    * \return characters mp gradent for bracket
    */
    inline int mp_gradent(int who, int lvl_bracket)
    {
        return character(who)._mp_gradent.at(lvl_bracket);
    }

    /*! \brief characters base hp for set of levels
    * \param who Characters id number
    * \param lvl_bracket bracket the level falls in (0: lvl 0-9 . 1: 10-19. etc..)
    * \return characters base hp for that bracket
    */
    inline int hp_base(int who, int lvl_bracket)
    {
        return character(who)._hp_base.at(lvl_bracket);
    }

    /*! \brief characters mp gradent for set of levels
    * \param who Characters id number
    * \param lvl_bracket bracket the level falls in (0: lvl 0-9 . 1: 10-19. etc..)
    * \return characters mp gradent for bracket
    */
    inline int hp_gradent(int who, int lvl_bracket)
    {
        return character(who)._hp_gradent.at(lvl_bracket);
    }

    /*! \brief characters base luck for set of levels
    * \param who Characters id number
    * \param lvl_bracket bracket the level falls in (0: lvl 0-9 . 1: 10-19. etc..)
    * \return characters base luck for that bracket
    */
    inline int luck_base(int who, int lvl_bracket)
    {
        return character(who)._luck_base.at(lvl_bracket);
    }

    /*! \brief characters luck gradent for set of levels
    * \param who Characters id number
    * \param lvl_bracket bracket the level falls in (0: lvl 0-9 . 1: 10-19. etc..)
    * \return characters luck gradent for bracket
    */
    inline int luck_gradent(int who, int lvl_bracket)
    {
        return character(who)._luck_gradent.at(lvl_bracket);
    }

    /*! \brief base stat for rank in a set of levels
    * \param rank Rank character is at start (grade)
    * \param lvl_bracket bracket the level falls in (0: lvl 0-9 . 1: 10-19. etc..)
    * \return base stat for that bracket
    */
    inline int stat_base(int rank, int lvl_bracket)
    {
        return _stat_base.at(rank).at(lvl_bracket);
    }

    /*! \brief characters mp gradent for set of levels
    * \param rank Rank character is at start (grade)
    * \param lvl_bracket bracket the level falls in (0: lvl 0-9 . 1: 10-19. etc..)
    * \return stat gradent for bracket
    */
    inline int stat_gradent(int rank, int lvl_bracket)
    {
        return _stat_gradent.at(rank).at(lvl_bracket);
    }

    /*! \struct Character
     *  \brief Holds all data for a single Character
     *  \sa _charData
     */
    struct Character {
        quint8 _id; /**< CharacterID */
        int _starting_weapon_id; /**< first item id for characters weapon*/
        int _num_weapons; /**< how many weapons the character has*/
        int _weapon_offset;/**< weapon offset of characters first weapon */
        QString _def_name; /**< default name for character*/
        QString _avatarString;/**< path it image resource*/
        QStringList _limits; /**< list of limit names */
        QList<quint32> _charlvls;/**< holds exp needed for lvls */
        QList<quint32> _chartnls;/**< starting exp needed to next level for each level*/
        QList<int> _stat_grade;/**< how the character grades in each basic stat*/
        QList<int> _mp_base;/**< grade in mp gain for each level bracket*/
        QList<int> _mp_gradent;/**< gradent for mp gain for each level bracket*/
        QList<int> _hp_base;/**< grade in hp gain for each level bracket*/
        QList<int> _hp_gradent;/**< gradent for hp gain for each level bracket*/
        QList<int> _luck_base;/**< luck base for each level bracket*/
        QList<int> _luck_gradent;/**< gradent for luck for each level bracket*/
    };

    /*!
     * \brief Internal Wrapper to return characters
     * \param who whos data to get Or empty data if invalid.
     * \return character data.
     */
    const FF7Char::Character& character(int who);
    inline static const Character _emptyChar {
        quint8(0), 0, 0, 0, QString(), QString(),
        {QString(), QString(), QString(), QString(), QString(), QString(), QString()},
        {quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0)},
        {quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0), quint32(0)},
        {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}
    };
    /*! \static _charData
     * Holds data for each character in Final Fantasy 7
     * \sa Character
     */
    inline static const QList<Character> _charData {
        {
            quint8(0), 128, 16, 0, QT_TR_NOOP("Cloud"), QStringLiteral(":/characters/cloud"),
            {QT_TR_NOOP("Braver"), QT_TR_NOOP("Cross-Slash"), QT_TR_NOOP("Blade Beam"), QT_TR_NOOP("Climhazzard"), QT_TR_NOOP("Meteorain"), QT_TR_NOOP("Finishing Touch"), QT_TR_NOOP("Omnislash")},
            {quint32(0), quint32(6), quint32(33), quint32(94), quint32(202), quint32(372), quint32(616), quint32(949), quint32(1384), quint32(1934), quint32(2614), quint32(3588), quint32(4610), quint32(5809), quint32(7200), quint32(8797), quint32(10614), quint32(12665), quint32(14965), quint32(17528), quint32(20368), quint32(24161), quint32(27694), quint32(31555), quint32(35759), quint32(40321), quint32(45255), quint32(50576), quint32(56299), quint32(62438), quint32(69008), quint32(77066), quint32(84643), quint32(92701), quint32(101255), quint32(110320), quint32(119910), quint32(130040), quint32(140725), quint32(151980), quint32(163820), quint32(176259), quint32(189312), quint32(202994), quint32(217320), quint32(232305), quint32(247963), quint32(264309), quint32(281358), quint32(299125), quint32(317625), quint32(336872), quint32(356881), quint32(377667), quint32(399245), quint32(421630), quint32(444836), quint32(468878), quint32(493771), quint32(519530), quint32(546170), quint32(581467), quint32(610297), quint32(640064), quint32(670784), quint32(702471), quint32(735141), quint32(768808), quint32(803488), quint32(839195), quint32(875945), quint32(913752), quint32(952632), quint32(992599), quint32(1033669), quint32(1075856), quint32(1119176), quint32(1163643), quint32(1209273), quint32(1256080), quint32(1304080), quint32(1389359), quint32(1441133), quint32(1494178), quint32(1548509), quint32(1604141), quint32(1661090), quint32(1719371), quint32(1778999), quint32(1839990), quint32(1902360), quint32(1966123), quint32(2031295), quint32(2097892), quint32(2165929), quint32(2235421), quint32(2306384), quint32(2378833), quint32(2452783)},
            {quint32(0), quint32(6), quint32(27), quint32(61), quint32(108), quint32(170), quint32(244), quint32(333), quint32(435), quint32(550), quint32(680), quint32(974), quint32(1022), quint32(1199), quint32(1391), quint32(1597), quint32(1817), quint32(2051), quint32(2300), quint32(2563), quint32(2840), quint32(3793), quint32(3533), quint32(3861), quint32(4204), quint32(4562), quint32(4934), quint32(5321), quint32(5723), quint32(6139), quint32(6570), quint32(8058), quint32(7577), quint32(8058), quint32(8554), quint32(9065), quint32(9590), quint32(10130), quint32(10685), quint32(11255), quint32(11840), quint32(12439), quint32(13053), quint32(13682), quint32(14326), quint32(14985), quint32(15658), quint32(16346), quint32(17049), quint32(17767), quint32(18500), quint32(19247), quint32(20009), quint32(20786), quint32(21578), quint32(22385), quint32(23206), quint32(24042), quint32(24893), quint32(25759), quint32(26640), quint32(35297), quint32(28830), quint32(29767), quint32(30720), quint32(31687), quint32(32670), quint32(33667), quint32(34680), quint32(35707), quint32(36750), quint32(37807), quint32(38880), quint32(39967), quint32(41070), quint32(42187), quint32(43320), quint32(44467), quint32(45630), quint32(46807), quint32(48000), quint32(85279), quint32(51774), quint32(53045), quint32(54331), quint32(55632), quint32(56949), quint32(58281), quint32(59628), quint32(60991), quint32(62370), quint32(63763), quint32(65172), quint32(66597), quint32(68037), quint32(69492), quint32(70963), quint32(72449), quint32(73950)},
            {1, 6, 3, 4, 26}, {12, 0, -26, -58, -102, -102, -4, 180}, {64, 78, 90, 101, 112, 112, 96, 73}, {200, -40, -640, -1440, -2280, -3080, -2040, -200}, {19, 42, 72, 100, 121, 137, 120, 98}, {15, 16, 16, 17, 17, 17, 18, 19}, {20, 10, 10, 8, 8, 8, 7, 6}
        },

        {
            quint8(1), 160, 16, 32, QT_TR_NOOP("Barret"), QStringLiteral(":/characters/barret"),
            {QT_TR_NOOP("Big Shot"), QT_TR_NOOP("Mindblow"), QT_TR_NOOP("Grenade Bomb"), QT_TR_NOOP("Hammerblow"), QT_TR_NOOP("Satellite Beam"), QT_TR_NOOP("Angermax"), QT_TR_NOOP("Catastrophe")},
            {quint32(0), quint32(7), quint32(35), quint32(98), quint32(210), quint32(385), quint32(637), quint32(980), quint32(1428), quint32(1995), quint32(2695), quint32(3689), quint32(4740), quint32(5973), quint32(7403), quint32(9045), quint32(10913), quint32(13022), quint32(15387), quint32(18022), quint32(20942), quint32(24827), quint32(28457), quint32(32424), quint32(36744), quint32(41431), quint32(46501), quint32(51968), quint32(57848), quint32(64155), quint32(70905), quint32(79149), quint32(86931), quint32(95207), quint32(103992), quint32(113302), quint32(123151), quint32(133555), quint32(144529), quint32(156088), quint32(168248), quint32(183403), quint32(196985), quint32(211222), quint32(226129), quint32(241721), quint32(258014), quint32(275023), quint32(292763), quint32(311250), quint32(330500), quint32(350527), quint32(371347), quint32(392976), quint32(415429), quint32(438721), quint32(462868), quint32(487885), quint32(513787), quint32(540590), quint32(568310), quint32(596961), quint32(626559), quint32(657120), quint32(688659), quint32(721191), quint32(754732), quint32(789297), quint32(824901), quint32(861560), quint32(899290), quint32(938105), quint32(978021), quint32(1019054), quint32(1061219), quint32(1104531), quint32(1149006), quint32(1194659), quint32(1241505), quint32(1289560), quint32(1338840), quint32(1389359), quint32(1441133), quint32(1494178), quint32(1548509), quint32(1604141), quint32(1661090), quint32(1719371), quint32(1778999), quint32(1839990), quint32(1902360), quint32(1966123), quint32(2031295), quint32(2097892), quint32(2165929), quint32(2235421), quint32(2306384), quint32(2378833), quint32(2452783)},
            {quint32(0), quint32(7), quint32(28), quint32(63), quint32(112), quint32(175), quint32(252), quint32(343), quint32(448), quint32(567), quint32(700), quint32(994), quint32(1051), quint32(1233), quint32(1430), quint32(1642), quint32(1868), quint32(2109), quint32(2365), quint32(2635), quint32(2920), quint32(3885), quint32(3630), quint32(3967), quint32(4320), quint32(4687), quint32(5070), quint32(5467), quint32(5880), quint32(6307), quint32(6750), quint32(8244), quint32(7782), quint32(8276), quint32(8785), quint32(9310), quint32(9849), quint32(10404), quint32(10974), quint32(11559), quint32(12160), quint32(15155), quint32(13582), quint32(14237), quint32(14907), quint32(15592), quint32(16293), quint32(17009), quint32(17740), quint32(18487), quint32(19250), quint32(20027), quint32(20820), quint32(21629), quint32(22453), quint32(23292), quint32(24147), quint32(25017), quint32(25902), quint32(26803), quint32(27720), quint32(28651), quint32(29598), quint32(30561), quint32(31539), quint32(32532), quint32(33541), quint32(34565), quint32(35604), quint32(36659), quint32(37730), quint32(38815), quint32(39916), quint32(41033), quint32(42165), quint32(43312), quint32(44475), quint32(45653), quint32(46846), quint32(48055), quint32(49280), quint32(50519), quint32(51774), quint32(53045), quint32(54331), quint32(55632), quint32(56949), quint32(58281), quint32(59628), quint32(60991), quint32(62370), quint32(63763), quint32(65172), quint32(66597), quint32(68037), quint32(69492), quint32(70963), quint32(72449), quint32(73950)},
            {5, 2, 18, 14, 29}, {10, 0, -20, -60, -108, -96, 0, 170}, {57, 67, 77, 90, 102, 100, 84, 63}, {200, 0, -760, -1840, -2840, -2840, -1160, 600}, {22, 45, 82, 118, 143, 143, 115, 95}, {14, 15, 15, 15, 16, 17, 18, 20}, {15, 8, 8, 7, 6, 5, 4, 3}
        },
        {
            quint8(2), 144, 16, 16, QT_TR_NOOP("Tifa"), QStringLiteral(":/characters/tifa"),
            {QT_TR_NOOP("Beat Rush"), QT_TR_NOOP("Somersault"), QT_TR_NOOP("Waterkick"), QT_TR_NOOP("Meteodrive"), QT_TR_NOOP("Dolphin Blow"), QT_TR_NOOP("Meteor Strike"), QT_TR_NOOP("Final Heaven")},
            {quint32(0), quint32(6), quint32(33), quint32(94), quint32(202), quint32(372), quint32(616), quint32(949), quint32(1384), quint32(1934), quint32(2614), quint32(3588), quint32(4610), quint32(5809), quint32(7200), quint32(8797), quint32(10614), quint32(12665), quint32(14965), quint32(17528), quint32(20368), quint32(24161), quint32(27694), quint32(31555), quint32(35759), quint32(40321), quint32(45255), quint32(50576), quint32(56299), quint32(62438), quint32(69008), quint32(77066), quint32(84643), quint32(92701), quint32(101255), quint32(110320), quint32(119910), quint32(130040), quint32(140725), quint32(151980), quint32(163820), quint32(178647), quint32(191877), quint32(205744), quint32(220264), quint32(235451), quint32(251321), quint32(267888), quint32(285168), quint32(303175), quint32(321925), quint32(341432), quint32(361712), quint32(382779), quint32(404649), quint32(427336), quint32(450856), quint32(475223), quint32(500453), quint32(526560), quint32(553560), quint32(581467), quint32(610297), quint32(640064), quint32(670784), quint32(702471), quint32(735141), quint32(768808), quint32(803488), quint32(839195), quint32(875945), quint32(913752), quint32(952632), quint32(992599), quint32(1033669), quint32(1075856), quint32(1119176), quint32(1163643), quint32(1209273), quint32(1256080), quint32(1304080), quint32(1371319), quint32(1422421), quint32(1474777), quint32(1528402), quint32(1583312), quint32(1639521), quint32(1697045), quint32(1755899), quint32(1816098), quint32(1877658), quint32(1940593), quint32(2004919), quint32(2070651), quint32(2137804), quint32(2206394), quint32(2276435), quint32(2347943), quint32(2420933)},
            {quint32(0), quint32(6), quint32(27), quint32(61), quint32(108), quint32(170), quint32(244), quint32(333), quint32(435), quint32(550), quint32(680), quint32(974), quint32(1022), quint32(1199), quint32(1391), quint32(1597), quint32(1817), quint32(2051), quint32(2300), quint32(2563), quint32(2840), quint32(3793), quint32(3533), quint32(3861), quint32(4204), quint32(4562), quint32(4934), quint32(5321), quint32(5723), quint32(6139), quint32(6570), quint32(8058), quint32(7577), quint32(8058), quint32(8554), quint32(9065), quint32(9590), quint32(10130), quint32(10685), quint32(11255), quint32(11840), quint32(14827), quint32(13230), quint32(13867), quint32(14520), quint32(15187), quint32(15870), quint32(16567), quint32(17280), quint32(18007), quint32(18750), quint32(19507), quint32(20280), quint32(21067), quint32(21870), quint32(22687), quint32(23520), quint32(24367), quint32(25230), quint32(26107), quint32(27000), quint32(27907), quint32(28830), quint32(29767), quint32(30720), quint32(31687), quint32(32670), quint32(33667), quint32(34680), quint32(35707), quint32(36750), quint32(37807), quint32(38880), quint32(39967), quint32(41070), quint32(42187), quint32(43320), quint32(44467), quint32(45630), quint32(46807), quint32(48000), quint32(67239), quint32(51102), quint32(52356), quint32(53625), quint32(54910), quint32(56209), quint32(57524), quint32(58854), quint32(60199), quint32(61560), quint32(62935), quint32(64326), quint32(65732), quint32(67153), quint32(68590), quint32(70041), quint32(71508), quint32(72990)},
            {6, 18, 16, 9, 25}, {10, 0, -28, -58, -98, -98, -26, 136}, {60, 70, 84, 94, 104, 104, 92, 72}, {200, 0, -520, -1520, -2520, -3000, -2160, -80}, {19, 38, 64, 96, 121, 131, 117, 92}, {14, 15, 15, 16, 17, 17, 17, 20}, {20, 10, 10, 9, 9, 10, 10, 6}
        },

        {
            quint8(3), 190, 11, 62, QT_TR_NOOP("Aerith"), QStringLiteral(":/characters/aerith"),
            {QT_TR_NOOP("Healing Wind"), QT_TR_NOOP("Seal Evil"), QT_TR_NOOP("Breath of the Earth"), QT_TR_NOOP("Fury Brand"), QT_TR_NOOP("Planet Protector"), QT_TR_NOOP("Pulse of Life"), QT_TR_NOOP("Great Gospel")},
            {quint32(0), quint32(6), quint32(32), quint32(92), quint32(199), quint32(366), quint32(607), quint32(935), quint32(1363), quint32(1905), quint32(2575), quint32(3542), quint32(4550), quint32(5733), quint32(7105), quint32(8680), quint32(10472), quint32(12495), quint32(14763), quint32(17290), quint32(20090), quint32(23831), quint32(27315), quint32(31123), quint32(35270), quint32(39770), quint32(44637), quint32(49885), quint32(55529), quint32(61584), quint32(68064), quint32(77066), quint32(84643), quint32(92701), quint32(101255), quint32(110320), quint32(119910), quint32(130040), quint32(140725), quint32(151980), quint32(163820), quint32(176259), quint32(189312), quint32(202994), quint32(217320), quint32(232305), quint32(247963), quint32(264309), quint32(281358), quint32(299125), quint32(317625), quint32(341432), quint32(361712), quint32(382779), quint32(404649), quint32(427336), quint32(450856), quint32(475223), quint32(500453), quint32(526560), quint32(553560), quint32(589211), quint32(618425), quint32(648589), quint32(679718), quint32(711828), quint32(744933), quint32(779049), quint32(814191), quint32(850374), quint32(887614), quint32(925925), quint32(965323), quint32(1005823), quint32(1047440), quint32(1090190), quint32(1134087), quint32(1179147), quint32(1225385), quint32(1272816), quint32(1321456), quint32(1407407), quint32(1459854), quint32(1513588), quint32(1568624), quint32(1624979), quint32(1682667), quint32(1741705), quint32(1802108), quint32(1863891), quint32(1927071), quint32(1991662), quint32(2057681), quint32(2125143), quint32(2194063), quint32(2264458), quint32(2336342), quint32(2409732), quint32(2484643)},
            {quint32(0), quint32(6), quint32(26), quint32(60), quint32(107), quint32(167), quint32(241), quint32(328), quint32(428), quint32(542), quint32(670), quint32(967), quint32(1008), quint32(1183), quint32(1372), quint32(1575), quint32(1792), quint32(2023), quint32(2268), quint32(2527), quint32(2800), quint32(3741), quint32(3484), quint32(3808), quint32(4147), quint32(4500), quint32(4867), quint32(5248), quint32(5644), quint32(6055), quint32(6480), quint32(9002), quint32(7577), quint32(8058), quint32(8554), quint32(9065), quint32(9590), quint32(10130), quint32(10685), quint32(11255), quint32(11840), quint32(12439), quint32(13053), quint32(13682), quint32(14326), quint32(14985), quint32(15658), quint32(16346), quint32(17049), quint32(17767), quint32(18500), quint32(23807), quint32(20280), quint32(21067), quint32(21870), quint32(22687), quint32(23520), quint32(24367), quint32(25230), quint32(26107), quint32(27000), quint32(35651), quint32(29214), quint32(30164), quint32(31129), quint32(32110), quint32(33105), quint32(34116), quint32(35142), quint32(36183), quint32(37240), quint32(38311), quint32(39398), quint32(40500), quint32(41617), quint32(42750), quint32(43897), quint32(45060), quint32(46238), quint32(47431), quint32(48640), quint32(85951), quint32(52447), quint32(53734), quint32(55036), quint32(56355), quint32(57688), quint32(59038), quint32(60403), quint32(61783), quint32(63180), quint32(64591), quint32(66019), quint32(67462), quint32(68920), quint32(70395), quint32(71884), quint32(73390), quint32(74911)},
            {23, 20, 0, 1, 28}, {16, 0, -30, -68, -116, -96, -6, 188}, {70, 84, 99, 112, 124, 120, 105, 82}, {160, 0, -560, -1400, -2240, -2880, -2080, -400}, {17, 36, 65, 93, 114, 126, 113, 93}, {14, 15, 15, 16, 16, 18, 17, 17}, {18, 8, 8, 8, 8, 5, 7, 7}
        },

        {
            quint8(4), 176, 14, 48, QT_TR_NOOP("Red XIII"), QStringLiteral(":/characters/red"),
            {QT_TR_NOOP("Sled Fang"), QT_TR_NOOP("Lunatic High"), QT_TR_NOOP("Blood Fang"), QT_TR_NOOP("Stardust Ray"), QT_TR_NOOP("Howling Moon"), QT_TR_NOOP("Earth Rave"), QT_TR_NOOP("Cosmo Memory")},
            {quint32(0), quint32(6), quint32(33), quint32(94), quint32(202), quint32(372), quint32(616), quint32(949), quint32(1384), quint32(1934), quint32(2614), quint32(3588), quint32(4610), quint32(5809), quint32(7200), quint32(8797), quint32(10614), quint32(12665), quint32(14965), quint32(17528), quint32(20368), quint32(24493), quint32(28074), quint32(31988), quint32(36250), quint32(40875), quint32(45877), quint32(51271), quint32(57072), quint32(63295), quint32(69955), quint32(78112), quint32(85792), quint32(93959), quint32(102629), quint32(111816), quint32(121536), quint32(131803), quint32(142633), quint32(154040), quint32(166040), quint32(178647), quint32(191877), quint32(205744), quint32(220264), quint32(235451), quint32(251321), quint32(267888), quint32(285168), quint32(303175), quint32(321925), quint32(341432), quint32(361712), quint32(382779), quint32(404649), quint32(427336), quint32(450856), quint32(475223), quint32(500453), quint32(526560), quint32(553560), quint32(589211), quint32(618425), quint32(648589), quint32(679718), quint32(711828), quint32(744933), quint32(779049), quint32(814191), quint32(850374), quint32(887614), quint32(925925), quint32(965323), quint32(1005823), quint32(1047440), quint32(1090190), quint32(1134087), quint32(1179147), quint32(1225385), quint32(1272816), quint32(1321456), quint32(1371319), quint32(1422421), quint32(1474777), quint32(1528402), quint32(1583312), quint32(1639521), quint32(1697045), quint32(1755899), quint32(1816098), quint32(1877658), quint32(1940593), quint32(2004919), quint32(2070651), quint32(2137804), quint32(2206394), quint32(2276435), quint32(2347943), quint32(2420933)},
            {quint32(0), quint32(6), quint32(27), quint32(61), quint32(108), quint32(170), quint32(244), quint32(333), quint32(435), quint32(550), quint32(680), quint32(974), quint32(1022), quint32(1199), quint32(1391), quint32(1597), quint32(1817), quint32(2051), quint32(2300), quint32(2563), quint32(2840), quint32(4125), quint32(3581), quint32(3914), quint32(4262), quint32(4625), quint32(5002), quint32(5394), quint32(5801), quint32(6223), quint32(6660), quint32(8157), quint32(7680), quint32(8167), quint32(8670), quint32(9187), quint32(9720), quint32(10267), quint32(10830), quint32(11407), quint32(12000), quint32(12607), quint32(13230), quint32(13867), quint32(14520), quint32(15187), quint32(15870), quint32(16567), quint32(17280), quint32(18007), quint32(18750), quint32(19507), quint32(20280), quint32(21067), quint32(21870), quint32(22687), quint32(23520), quint32(24367), quint32(25230), quint32(26107), quint32(27000), quint32(35651), quint32(29214), quint32(30164), quint32(31129), quint32(32110), quint32(33105), quint32(34116), quint32(35142), quint32(36183), quint32(37240), quint32(38311), quint32(39398), quint32(40500), quint32(41617), quint32(42750), quint32(43897), quint32(45060), quint32(46238), quint32(47431), quint32(48640), quint32(49863), quint32(51102), quint32(52356), quint32(53625), quint32(54910), quint32(56209), quint32(57524), quint32(58854), quint32(60199), quint32(61560), quint32(62935), quint32(64326), quint32(65732), quint32(67153), quint32(68590), quint32(70041), quint32(71508), quint32(72990)},
            {12, 11, 13, 9, 23}, {12, -6, -28, -60, -104, -126, -16, 210}, {58, 75, 86, 97, 108, 112, 94, 66}, {200, -40, -640, -1560, -2360, -2760, -1840, -80}, {21, 45, 75, 105, 126, 134, 119, 97}, {14, 15, 15, 16, 16, 18, 17, 17}, {18, 8, 8, 8, 8, 5, 7, 7}
        },

        {
            quint8(5), 215, 14, 87, QT_TR_NOOP("Yuffie"), QStringLiteral(":/characters/yuffie"),
            {QT_TR_NOOP("Greased Lightning"), QT_TR_NOOP("Clear Tranquil"), QT_TR_NOOP("Landscaper"), QT_TR_NOOP("Bloodfest"), QT_TR_NOOP("Gauntlet"), QT_TR_NOOP("Doom of the Living"), QT_TR_NOOP("All Creation")},
            {quint32(0), quint32(6), quint32(33), quint32(95), quint32(205), quint32(377), quint32(625), quint32(963), quint32(1404), quint32(1962), quint32(2652), quint32(3639), quint32(4675), quint32(5891), quint32(7302), quint32(8922), quint32(10765), quint32(12845), quint32(15177), quint32(17776), quint32(20656), quint32(24827), quint32(28457), quint32(32424), quint32(36744), quint32(41431), quint32(46501), quint32(51968), quint32(57848), quint32(64155), quint32(70905), quint32(78112), quint32(85792), quint32(93959), quint32(102629), quint32(111816), quint32(121536), quint32(131803), quint32(142633), quint32(154040), quint32(166040), quint32(181023), quint32(194429), quint32(208481), quint32(223194), quint32(238584), quint32(254665), quint32(271453), quint32(288963), quint32(307210), quint32(326210), quint32(345977), quint32(366527), quint32(387875), quint32(410036), quint32(433026), quint32(456859), quint32(481551), quint32(507117), quint32(533572), quint32(560932), quint32(596961), quint32(626559), quint32(657120), quint32(688659), quint32(721191), quint32(754732), quint32(789297), quint32(824901), quint32(861560), quint32(899290), quint32(938105), quint32(978021), quint32(1019054), quint32(1061219), quint32(1104531), quint32(1149006), quint32(1194659), quint32(1241505), quint32(1289560), quint32(1338840), quint32(1389359), quint32(1441133), quint32(1494178), quint32(1548509), quint32(1604141), quint32(1661090), quint32(1719371), quint32(1778999), quint32(1839990), quint32(1902360), quint32(1966123), quint32(2031295), quint32(2097892), quint32(2165929), quint32(2235421), quint32(2306384), quint32(2378833), quint32(2452783)},
            {quint32(0), quint32(6), quint32(27), quint32(62), quint32(110), quint32(172), quint32(248), quint32(338), quint32(441), quint32(558), quint32(690), quint32(987), quint32(1036), quint32(1216), quint32(1411), quint32(1620), quint32(1843), quint32(2080), quint32(2332), quint32(2599), quint32(2880), quint32(4171), quint32(3630), quint32(3967), quint32(4320), quint32(4687), quint32(5070), quint32(5467), quint32(5880), quint32(6307), quint32(6750), quint32(7207), quint32(7680), quint32(8167), quint32(8670), quint32(9187), quint32(9720), quint32(10267), quint32(10830), quint32(11407), quint32(12000), quint32(14983), quint32(13406), quint32(14052), quint32(14713), quint32(15390), quint32(16081), quint32(16788), quint32(17510), quint32(18247), quint32(19000), quint32(19767), quint32(20550), quint32(21348), quint32(22161), quint32(22990), quint32(23833), quint32(24692), quint32(25566), quint32(26455), quint32(27360), quint32(36029), quint32(29598), quint32(30561), quint32(31539), quint32(32532), quint32(33541), quint32(34565), quint32(35604), quint32(36659), quint32(37730), quint32(38815), quint32(39916), quint32(41033), quint32(42165), quint32(43312), quint32(44475), quint32(45653), quint32(46846), quint32(48055), quint32(49280), quint32(50519), quint32(51774), quint32(53045), quint32(54331), quint32(55632), quint32(56949), quint32(58281), quint32(59628), quint32(60991), quint32(62370), quint32(63763), quint32(65172), quint32(66597), quint32(68037), quint32(69492), quint32(70963), quint32(72449), quint32(73950)},
            {16, 19, 11, 10, 24}, {10, -2, -20, -58, -110, -130, 20, 126}, {58, 72, 80, 93, 106, 110, 85, 72}, {200, 0, -560, -1320, -2160, -2960, -2560, -520}, {18, 37, 64, 89, 111, 127, 120, 96}, {16, 17, 17, 17, 18, 18, 18, 19}, {20, 10, 10, 10, 8, 10, 10, 9}
        },

        {
            quint8(6), 229, 13, 101, QT_TR_NOOP("Cait Sith"), QStringLiteral(":/characters/cait"),
            {QT_TR_NOOP("Dice"), QString(), QT_TR_NOOP("Slots"), QString(), QString(), QString(), QString()},
            {quint32(0), quint32(6), quint32(33), quint32(95), quint32(205), quint32(377), quint32(625), quint32(963), quint32(1404), quint32(1962), quint32(2652), quint32(3639), quint32(4675), quint32(5891), quint32(7302), quint32(8922), quint32(10765), quint32(12845), quint32(15177), quint32(17776), quint32(20656), quint32(24827), quint32(28457), quint32(32424), quint32(36744), quint32(41431), quint32(46501), quint32(51968), quint32(57848), quint32(64155), quint32(70905), quint32(78112), quint32(85792), quint32(93959), quint32(102629), quint32(111816), quint32(121536), quint32(131803), quint32(142633), quint32(154040), quint32(166040), quint32(178647), quint32(191877), quint32(205744), quint32(220264), quint32(235451), quint32(251321), quint32(267888), quint32(285168), quint32(303175), quint32(321925), quint32(345977), quint32(366527), quint32(387875), quint32(410036), quint32(433026), quint32(456859), quint32(481551), quint32(507117), quint32(533572), quint32(560932), quint32(589211), quint32(618425), quint32(648589), quint32(679718), quint32(711828), quint32(744933), quint32(779049), quint32(814191), quint32(850374), quint32(887614), quint32(925925), quint32(965323), quint32(1005823), quint32(1047440), quint32(1090190), quint32(1134087), quint32(1179147), quint32(1225385), quint32(1272816), quint32(1321456), quint32(1371319), quint32(1422421), quint32(1474777), quint32(1528402), quint32(1583312), quint32(1639521), quint32(1697045), quint32(1755899), quint32(1816098), quint32(1877658), quint32(1940593), quint32(2004919), quint32(2070651), quint32(2137804), quint32(2206394), quint32(2276435), quint32(2347943), quint32(2420933)},
            {quint32(0), quint32(6), quint32(27), quint32(62), quint32(110), quint32(172), quint32(248), quint32(338), quint32(441), quint32(558), quint32(690), quint32(987), quint32(1036), quint32(1216), quint32(1411), quint32(1620), quint32(1843), quint32(2080), quint32(2332), quint32(2599), quint32(2880), quint32(4171), quint32(3630), quint32(3967), quint32(4320), quint32(4687), quint32(5070), quint32(5467), quint32(5880), quint32(6307), quint32(6750), quint32(7207), quint32(7680), quint32(8167), quint32(8670), quint32(9187), quint32(9720), quint32(10267), quint32(10830), quint32(11407), quint32(12000), quint32(12607), quint32(13230), quint32(13867), quint32(14520), quint32(15187), quint32(15870), quint32(16567), quint32(17280), quint32(18007), quint32(18750), quint32(24052), quint32(20550), quint32(21348), quint32(22161), quint32(22990), quint32(23833), quint32(24692), quint32(25566), quint32(26455), quint32(27360), quint32(28279), quint32(29214), quint32(30164), quint32(31129), quint32(32110), quint32(33105), quint32(34116), quint32(35142), quint32(36183), quint32(37240), quint32(38311), quint32(39398), quint32(40500), quint32(41617), quint32(42750), quint32(43897), quint32(45060), quint32(46238), quint32(47431), quint32(48640), quint32(49863), quint32(51102), quint32(52356), quint32(53625), quint32(54910), quint32(56209), quint32(57524), quint32(58854), quint32(60199), quint32(61560), quint32(62935), quint32(64326), quint32(65732), quint32(67153), quint32(68590), quint32(70041), quint32(71508), quint32(72990)},
            {19, 22, 6, 4, 28}, {2, -2, -20, -60, -104, -104, -20, 178}, {60, 75, 83, 97, 108, 108, 94, 70}, {200, -80, -640, -1640, -2760, -2600, -240, 2000}, {24, 51, 80, 111, 141, 138, 99, 72}, {14, 15, 15, 16, 17, 17, 17, 20}, {20, 10, 10, 9, 9, 10, 10, 6}
        },

        {
            quint8(7), 242, 13, 114, QT_TR_NOOP("Vincent"), QStringLiteral(":/characters/vincent"),
            {QT_TR_NOOP("Galian Beast"), QString(), QT_TR_NOOP("Death Gigas"), QString(), QT_TR_NOOP("Hellmasker"), QString(), QT_TR_NOOP("Chaos")},
            {quint32(0), quint32(7), quint32(35), quint32(98), quint32(210), quint32(385), quint32(637), quint32(980), quint32(1428), quint32(1995), quint32(2695), quint32(3639), quint32(4675), quint32(5891), quint32(7302), quint32(8922), quint32(10765), quint32(12845), quint32(15177), quint32(17776), quint32(20656), quint32(24827), quint32(28457), quint32(32424), quint32(36744), quint32(41431), quint32(46501), quint32(51968), quint32(57848), quint32(64155), quint32(70905), quint32(79149), quint32(86931), quint32(95207), quint32(103992), quint32(113302), quint32(123151), quint32(133555), quint32(144529), quint32(156088), quint32(168248), quint32(181023), quint32(194429), quint32(208481), quint32(223194), quint32(238584), quint32(254665), quint32(271453), quint32(288963), quint32(307210), quint32(326210), quint32(345977), quint32(366527), quint32(387875), quint32(410036), quint32(433026), quint32(456859), quint32(481551), quint32(507117), quint32(533572), quint32(560932), quint32(589211), quint32(618425), quint32(648589), quint32(679718), quint32(711828), quint32(744933), quint32(779049), quint32(814191), quint32(850374), quint32(887614), quint32(925925), quint32(965323), quint32(1005823), quint32(1047440), quint32(1090190), quint32(1134087), quint32(1179147), quint32(1225385), quint32(1272816), quint32(1321456), quint32(1371319), quint32(1422421), quint32(1474777), quint32(1528402), quint32(1583312), quint32(1639521), quint32(1697045), quint32(1755899), quint32(1816098), quint32(1877658), quint32(1940593), quint32(2004919), quint32(2070651), quint32(2137804), quint32(2206394), quint32(2276435), quint32(2347943), quint32(2420933)},
            {quint32(0), quint32(7), quint32(28), quint32(63), quint32(112), quint32(175), quint32(252), quint32(343), quint32(448), quint32(567), quint32(700), quint32(944), quint32(1036), quint32(1216), quint32(1411), quint32(1620), quint32(1843), quint32(2080), quint32(2332), quint32(2599), quint32(2880), quint32(4171), quint32(3630), quint32(3967), quint32(4320), quint32(4687), quint32(5070), quint32(5467), quint32(5880), quint32(6307), quint32(6750), quint32(8244), quint32(7782), quint32(8276), quint32(8785), quint32(9310), quint32(9849), quint32(10404), quint32(10974), quint32(11559), quint32(12160), quint32(12775), quint32(13406), quint32(14052), quint32(14713), quint32(15390), quint32(16081), quint32(16788), quint32(17510), quint32(18247), quint32(19000), quint32(19767), quint32(20550), quint32(21348), quint32(22161), quint32(22990), quint32(23833), quint32(24692), quint32(25566), quint32(26455), quint32(27360), quint32(28279), quint32(29214), quint32(30164), quint32(31129), quint32(32110), quint32(33105), quint32(34116), quint32(35142), quint32(36183), quint32(37240), quint32(38311), quint32(39398), quint32(40500), quint32(41617), quint32(42750), quint32(43897), quint32(45060), quint32(46238), quint32(47431), quint32(48640), quint32(49863), quint32(51102), quint32(52356), quint32(53625), quint32(54910), quint32(56209), quint32(57524), quint32(58854), quint32(60199), quint32(61560), quint32(62935), quint32(64326), quint32(65732), quint32(67153), quint32(68590), quint32(70041), quint32(71508), quint32(72990)},
            {21, 22, 6, 4, 28}, {12, -6, -26, -44, -60, -86, 38, 74}, {63, 80, 90, 96, 100, 105, 97, 84}, {160, -80, -600, -1160, -2120, -2800, -2640, -400}, {18, 41, 67, 86, 110, 123, 120, 92}, {14, 15, 15, 16, 17, 17, 17, 20}, {20, 10, 10, 9, 9, 10, 10, 6}
        },

        {
            quint8(8), 201, 14, 73, QT_TR_NOOP("Cid"), QStringLiteral(":/characters/cid"),
            {QT_TR_NOOP("Boost Jump"), QT_TR_NOOP("Dynamite"), QT_TR_NOOP("Hyper Jump"), QT_TR_NOOP("Dragon"), QT_TR_NOOP("Dragon Dive"), QT_TR_NOOP("Big Brawl"), QT_TR_NOOP("Highwind")},
            {quint32(0), quint32(6), quint32(33), quint32(95), quint32(205), quint32(377), quint32(625), quint32(963), quint32(1404), quint32(1962), quint32(2652), quint32(3639), quint32(4675), quint32(5891), quint32(7302), quint32(8922), quint32(10765), quint32(12845), quint32(15177), quint32(17776), quint32(20656), quint32(24827), quint32(28457), quint32(32424), quint32(36744), quint32(41431), quint32(46501), quint32(51968), quint32(57848), quint32(64155), quint32(70905), quint32(78112), quint32(85792), quint32(93959), quint32(102629), quint32(111816), quint32(121536), quint32(131803), quint32(142633), quint32(154040), quint32(166040), quint32(181023), quint32(194429), quint32(208481), quint32(223194), quint32(238584), quint32(254665), quint32(271453), quint32(288963), quint32(307210), quint32(326210), quint32(345977), quint32(366527), quint32(387875), quint32(410036), quint32(433026), quint32(456859), quint32(481551), quint32(507117), quint32(533572), quint32(560932), quint32(596961), quint32(626559), quint32(657120), quint32(688659), quint32(721191), quint32(754732), quint32(789297), quint32(824901), quint32(861560), quint32(899290), quint32(938105), quint32(978021), quint32(1019054), quint32(1061219), quint32(1104531), quint32(1149006), quint32(1194659), quint32(1241505), quint32(1289560), quint32(1338840), quint32(1389359), quint32(1441133), quint32(1494178), quint32(1548509), quint32(1604141), quint32(1661090), quint32(1719371), quint32(1778999), quint32(1839990), quint32(1902360), quint32(1966123), quint32(2031295), quint32(2097892), quint32(2165929), quint32(2235421), quint32(2306384), quint32(2378833), quint32(2452783)},
            {quint32(0), quint32(6), quint32(27), quint32(62), quint32(110), quint32(172), quint32(248), quint32(338), quint32(441), quint32(558), quint32(690), quint32(987), quint32(1036), quint32(1216), quint32(1411), quint32(1620), quint32(1843), quint32(2080), quint32(2332), quint32(2599), quint32(2880), quint32(4171), quint32(3630), quint32(3967), quint32(4320), quint32(4687), quint32(5070), quint32(5467), quint32(5880), quint32(6307), quint32(6750), quint32(7207), quint32(7680), quint32(8167), quint32(8670), quint32(9187), quint32(9720), quint32(10267), quint32(10830), quint32(11407), quint32(12000), quint32(14983), quint32(13406), quint32(14052), quint32(14713), quint32(15390), quint32(16081), quint32(16788), quint32(17510), quint32(18247), quint32(19000), quint32(19767), quint32(20550), quint32(21348), quint32(22161), quint32(22990), quint32(23833), quint32(24692), quint32(25566), quint32(26455), quint32(27360), quint32(36029), quint32(29598), quint32(30561), quint32(31539), quint32(32532), quint32(33541), quint32(34565), quint32(35604), quint32(36659), quint32(37730), quint32(38815), quint32(39916), quint32(41033), quint32(42165), quint32(43312), quint32(44475), quint32(45653), quint32(46846), quint32(48055), quint32(49280), quint32(50519), quint32(51774), quint32(53045), quint32(54331), quint32(55632), quint32(56949), quint32(58281), quint32(59628), quint32(60991), quint32(62370), quint32(63763), quint32(65172), quint32(66597), quint32(68037), quint32(69492), quint32(70963), quint32(72449), quint32(73950)},
            {11, 7, 17, 15, 27}, {10, -12, -26, -38, -66, -116, 69, 140}, {54, 75, 83, 87, 94, 104, 89, 69}, {200, -40, -640, -1640, -2360, -2560, -1720, -0}, {23, 44, 73, 107, 125, 129, 115, 93}, {14, 15, 15, 15, 16, 17, 18, 20}, {15, 8, 8, 7, 6, 5, 4, 3}
        },

        {
            quint8(9), 128, 16, 0, QT_TR_NOOP("Y.Cloud"), QStringLiteral(":/characters/y_cloud"),
            {QT_TR_NOOP("Braver"), QT_TR_NOOP("Cross-Slash"), QT_TR_NOOP("Blade Beam"), QT_TR_NOOP("Climhazzard"), QT_TR_NOOP("Meteorain"), QT_TR_NOOP("Finishing Touch"), QT_TR_NOOP("Omnislash")},
            {quint32(0), quint32(13), quint32(65), quint32(182), quint32(390), quint32(715), quint32(1183), quint32(1820), quint32(2652), quint32(3705), quint32(5005), quint32(7084), quint32(9100), quint32(11466), quint32(14210), quint32(17360), quint32(20944), quint32(24990), quint32(29526), quint32(34580), quint32(40180), quint32(46354), quint32(53130), quint32(60536), quint32(68600), quint32(77350), quint32(86814), quint32(97020), quint32(107996), quint32(119770), quint32(132370), quint32(114576), quint32(125840), quint32(137819), quint32(150535), quint32(164010), quint32(178266), quint32(193325), quint32(209209), quint32(225940), quint32(243540), quint32(214389), quint32(230265), quint32(246906), quint32(264330), quint32(282555), quint32(301599), quint32(321480), quint32(342216), quint32(363825), quint32(386325), quint32(318682), quint32(337610), quint32(357273), quint32(377685), quint32(398860), quint32(420812), quint32(443555), quint32(467103), quint32(491470), quint32(516670), quint32(372124), quint32(390575), quint32(409626), quint32(429286), quint32(449566), quint32(470474), quint32(492021), quint32(514216), quint32(537068), quint32(560588), quint32(584784), quint32(609667), quint32(635246), quint32(661530), quint32(688530), quint32(716254), quint32(744713), quint32(773916), quint32(803872), quint32(834592), quint32(487154), quint32(505308), quint32(523908), quint32(542959), quint32(562466), quint32(582435), quint32(602871), quint32(623779), quint32(645165), quint32(667035), quint32(689393), quint32(712245), quint32(735597), quint32(759454), quint32(783821), quint32(808704), quint32(834108), quint32(860038)},
            {quint32(0), quint32(13), quint32(52), quint32(117), quint32(208), quint32(325), quint32(468), quint32(637), quint32(832), quint32(1053), quint32(1300), quint32(2079), quint32(2016), quint32(2366), quint32(2744), quint32(3150), quint32(3584), quint32(4046), quint32(4536), quint32(5054), quint32(5600), quint32(6174), quint32(6776), quint32(7406), quint32(8064), quint32(8750), quint32(9464), quint32(10206), quint32(10976), quint32(11774), quint32(12600), quint32(-17794), quint32(11264), quint32(11979), quint32(12716), quint32(13475), quint32(14256), quint32(15059), quint32(15884), quint32(16731), quint32(17600), quint32(-29151), quint32(15876), quint32(16641), quint32(17424), quint32(18225), quint32(19044), quint32(19881), quint32(20736), quint32(21609), quint32(22500), quint32(-67643), quint32(18928), quint32(19663), quint32(20412), quint32(21175), quint32(21952), quint32(22743), quint32(23548), quint32(24367), quint32(25200), quint32(-144546), quint32(18451), quint32(19051), quint32(19660), quint32(20280), quint32(20908), quint32(21547), quint32(22195), quint32(22852), quint32(23520), quint32(24196), quint32(24883), quint32(25579), quint32(26284), quint32(27000), quint32(27724), quint32(28459), quint32(29203), quint32(29956), quint32(30720), quint32(-347438), quint32(18154), quint32(18600), quint32(19051), quint32(19507), quint32(19969), quint32(20436), quint32(20908), quint32(21386), quint32(21870), quint32(22358), quint32(22852), quint32(23352), quint32(23857), quint32(24367), quint32(24883), quint32(25404), quint32(25930)},
            {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}
        },

        {
            quint8(10), 255, 1, 0, QT_TR_NOOP("Sephiroth"), QString(":/characters/sep"),
            {QString(), QString(), QString(), QString(), QString(), QString(), QString()},
            {quint32(0), quint32(6), quint32(33), quint32(94), quint32(202), quint32(372), quint32(616), quint32(949), quint32(1384), quint32(1934), quint32(2614), quint32(3588), quint32(4610), quint32(5809), quint32(7200), quint32(8797), quint32(10614), quint32(12665), quint32(14965), quint32(17528), quint32(20368), quint32(24161), quint32(27694), quint32(31555), quint32(35759), quint32(40321), quint32(45255), quint32(50576), quint32(56299), quint32(62438), quint32(69008), quint32(77066), quint32(84643), quint32(92701), quint32(101255), quint32(110320), quint32(119910), quint32(130040), quint32(140725), quint32(151980), quint32(163820), quint32(176259), quint32(189312), quint32(202994), quint32(217320), quint32(232305), quint32(247963), quint32(264309), quint32(281358), quint32(299125), quint32(317625), quint32(336872), quint32(356881), quint32(377667), quint32(399245), quint32(421630), quint32(444836), quint32(468878), quint32(493771), quint32(519530), quint32(546170), quint32(581467), quint32(610297), quint32(640064), quint32(670784), quint32(702471), quint32(735141), quint32(768808), quint32(803488), quint32(839195), quint32(875945), quint32(913752), quint32(952632), quint32(992599), quint32(1033669), quint32(1075856), quint32(1119176), quint32(1163643), quint32(1209273), quint32(1256080), quint32(1304080), quint32(1389359), quint32(1441133), quint32(1494178), quint32(1548509), quint32(1604141), quint32(1661090), quint32(1719371), quint32(1778999), quint32(1839990), quint32(1902360), quint32(1966123), quint32(2031295), quint32(2097892), quint32(2165929), quint32(2235421), quint32(2306384), quint32(2378833), quint32(2452783)},
            {quint32(0), quint32(6), quint32(27), quint32(61), quint32(108), quint32(170), quint32(244), quint32(333), quint32(435), quint32(550), quint32(680), quint32(974), quint32(1022), quint32(1199), quint32(1391), quint32(1597), quint32(1817), quint32(2051), quint32(2300), quint32(2563), quint32(2840), quint32(3793), quint32(3533), quint32(3861), quint32(4204), quint32(4562), quint32(4934), quint32(5321), quint32(5723), quint32(6139), quint32(6570), quint32(8058), quint32(7577), quint32(8058), quint32(8554), quint32(9065), quint32(9590), quint32(10130), quint32(10685), quint32(11255), quint32(11840), quint32(12439), quint32(13053), quint32(13682), quint32(14326), quint32(14985), quint32(15658), quint32(16346), quint32(17049), quint32(17767), quint32(18500), quint32(19247), quint32(20009), quint32(20786), quint32(21578), quint32(22385), quint32(23206), quint32(24042), quint32(24893), quint32(25759), quint32(26640), quint32(35297), quint32(28830), quint32(29767), quint32(30720), quint32(31687), quint32(32670), quint32(33667), quint32(34680), quint32(35707), quint32(36750), quint32(37807), quint32(38880), quint32(39967), quint32(41070), quint32(42187), quint32(43320), quint32(44467), quint32(45630), quint32(46807), quint32(48000), quint32(85279), quint32(51774), quint32(53045), quint32(54331), quint32(55632), quint32(56949), quint32(58281), quint32(59628), quint32(60991), quint32(62370), quint32(63763), quint32(65172), quint32(66597), quint32(68037), quint32(69492), quint32(70963), quint32(72449), quint32(73950)},
            {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}
        }
    };
    inline static const QVector<QList<int>> _stat_base{
        {12, 9, 9, 21, 44, 50, 57, 73},
        {13, 12, 11, 11, 17, 43, 53, 80},
        {12, 10, 11, 21, 32, 42, 56, 73},
        {12, 13, 11, 15, 33, 40, 51, 69},
        {10, 9, 8, 8, 30, 33, 40, 61},
        {12, 12, 14, 14, 23, 49, 55, 62},
        {10, 8, 5, 17, 17, 30, 50, 61},
        {11, 10, 11, 16, 27, 33, 37, 58},
        {12, 9, 10, 11, 29, 34, 49, 58},
        {9, 8, 8, 8, 26, 29, 42, 48},
        {9, 9, 7, 8, 11, 26, 48, 53},
        {11, 10, 12, 17, 21, 49, 48},
        {9, 9, 6, 8, 29, 51, 57, 62},
        {10, 9, 7, 16, 22, 43, 45, 54},
        {8, 9, 11, 13, 16, 18, 40, 60},
        {9, 9, 11, 15, 23, 32, 48, 62},
        {10, 9, 10, 16, 22, 28, 49, 55},
        {10, 10, 10, 13, 21, 39, 45, 57},
        {10, 10, 9, 11, 21, 35, 51, 57},
        {9, 8, 9, 17, 32, 37, 42, 47},
        {10, 9, 8, 11, 29, 39, 47, 53},
        {8, 7, 4, 20, 31, 36, 37, 46},
        {9, 9, 10, 15, 21, 28, 35, 53},
        {9, 9, 8, 14, 18, 25, 44, 50},
        {8, 9, 12, 13, 22, 29, 38, 55},
        {7, 7, 1, 8, 13, 20, 42, 46},
        {6, 7, 6, 6, 10, 19, 36, 37},
        {6, 9, 8, 6, 7, 13, 31, 37},
        {5, 6, 7, 7, 9, 18, 38, 38},
        {5, 6, 4, 9, 14, 20, 24, 30}
    };

    inline static const QVector<QList<int>> _stat_gradent{
        {130, 160, 160, 120, 70, 60, 50, 30},
        {120, 130, 133, 135, 120, 72, 55, 21},
        {130, 140, 140, 110, 90, 70, 48, 27},
        {130, 140, 140, 110, 90, 79, 53, 32},
        {120, 128, 130, 130, 77, 72, 61, 35},
        {120, 125, 117, 118, 93, 52, 44, 35},
        {110, 130, 145, 110, 100, 95, 44, 31},
        {120, 135, 130, 110, 85, 70, 60, 35},
        {100, 130, 125, 120, 77, 67, 43, 31},
        {110, 120, 122, 123, 80, 75, 55, 44},
        {100, 115, 124, 118, 107, 78, 42, 36},
        {110, 120, 115, 102, 91, 37, 40, 40},
        {100, 122, 140, 135, 83, 40, 30, 25},
        {110, 122, 130, 98, 83, 45, 44, 33},
        {110, 105, 104, 102, 93, 87, 51, 25},
        {115, 127, 121, 108, 86, 68, 41, 24},
        {114, 118, 114, 95, 82, 71, 37, 30},
        {112, 115, 111, 103, 83, 48, 39, 25},
        {100, 108, 115, 108, 83, 55, 31, 24},
        {100, 111, 112, 87, 53, 45, 39, 34},
        {100, 108, 114, 106, 63, 45, 33, 26},
        {100, 110, 127, 77, 50, 41, 40, 31},
        {100, 102, 101, 88, 70, 57, 45, 24},
        {100, 100, 107, 85, 77, 60, 30, 24},
        {95, 90, 88, 85, 62, 52, 39, 18},
        {80, 85, 115, 92, 78, 64, 27, 21},
        {72, 69, 76, 77, 68, 50, 22, 21},
        {70, 53, 63, 70, 69, 58, 28, 20},
        {70, 70, 70, 71, 67, 48, 16, 16},
        {65, 63, 76, 61, 49, 36, 28, 20}
    };

    inline static const QList<int> _limitbitarray{0, 1, 3, 4, 6, 7, 9}; /**< Order of bytes used to flag limit breaks as learned*/
};
