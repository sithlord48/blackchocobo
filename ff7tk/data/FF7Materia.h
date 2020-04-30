/****************************************************************************/
//    copyright 2012 - 2020  Chris Rizzitello <sithlord48@gmail.com>        //
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

#include <QObject>

#include <QIcon>

class FF7Materia : public QObject
{
    Q_OBJECT
public:
    enum MateriaType {
        Unknown/**< 0*/
        , Magic/**< 1*/
        , Summon/**< 2*/
        , Independent/**< 3*/
        , Support/**< 4*/
        , Command/**< 5*/
    };
    Q_ENUM(MateriaType)

    enum MateriaNames {
        MpPlus = 0x00/**< 0x00*/, HpPlus = 0x01/**< 0x01*/, SpeedPlus = 0x02/**< 0x02*/, MagicPlus = 0x03/**< 0x03*/, LuckPlus = 0x04/**< 0x04*/, ExpPlus = 0x05/**< 0x05*/, GilPlus = 0x06/**< 0x06*/, EnemyAway = 0x07/**< 0x07*/, EnemyLure = 0x08/**< 0x08*/, ChocoboLure = 0x09/**< 0x09*/, PreEmptive = 0x0A/**< 0x0A*/, LongRange = 0x0B/**< 0x0B*/, MegaAll = 0x0C/**< 0x0C*/, CounterAttack = 0x0D/**< 0x0D*/, SlashAll = 0x0E/**< 0x0E*/, DoubleCut = 0x0F/**< 0x0F*/
        , Cover = 0x10/**< 0x10*/, Underwater = 0x11/**< 0x11*/, HPMP = 0x12/**< 0x12*/, WMagic = 0x13/**< 0x13*/, WSummon = 0x14/**< 0x14*/, WItem = 0x15/**< 0x15*/, All = 0x17/**< 0x17*/, Counter = 0x18/**< 0x18*/, MagicCounter = 0x19/**< 0x19*/, MpTurbo = 0x1A/**< 0x1A*/, MpAbsorb = 0x1B/**< 0x1B*/, HpAbsorb = 0x1C/**< 0x1C*/, Elemental = 0x1D/**< 0x1D*/, AddedEffect = 0x1E/**< 0x1E*/, SneakAttack = 0x1F/**< 0x1F*/
        , FinalAttack = 0x20/**< 0x20*/, AddedCut = 0x21/**< 0x21*/, StealAsWell = 0x22/**< 0x22*/, QuadraMagic = 0x23/**< 0x23*/, Steal = 0x24/**< 0x24*/, Sense = 0x25/**< 0x25*/, Throw = 0x27/**< 0x27*/, Morph = 0x28/**< 0x28*/, Deathblow = 0x29/**< 0x29*/, Manipulate = 0x2A/**< 0x2A*/, Mime = 0x2B/**< 0x2B*/, EnemySkill = 0x2C/**< 0x2C*/
        , MasterCommand = 0x30/**< 0x30*/, Fire = 0x31/**< 0x31*/, Ice = 0x32/**< 0x32*/, Earth = 0x33/**< 0x33*/, Lightning = 0x34/**< 0x34*/, Restore = 0x35/**< 0x35*/, Heal = 0x36/**< 0x36*/, Revive = 0x37/**< 0x37*/, Seal = 0x38/**< 0x38*/, Mystify = 0x39/**< 0x39*/, Transform = 0x3A/**< 0x3A*/, Exit = 0x3B/**< 0x3B*/, Poison = 0x3C/**< 0x3C*/, Demi = 0x3D/**< 0x3D*/, Barrier = 0x3E/**< 0x3E*/
        , Comet = 0x40/**< 0x40*/, Time = 0x41/**< 0x41*/, Destruct = 0x44/**< 0x44*/, Contain = 0x45/**< 0x45*/, FullCure = 0x46/**< 0x46*/, Shield = 0x47/**< 0x47*/, Ultima = 0x48/**< 0x48*/, MasterMagic = 0x49/**< 0x49*/, ChocoMog = 0x4A/**< 0x4A*/, Shiva = 0x4B/**< 0x4B*/, Ifrit = 0x4C/**< 0x4C*/, Ramuh = 0x4D/**< 0x4D*/, Titan = 0x4E/**< 0x4E*/, Odin = 0x4F/**< 0x4F*/
        , Leviathan = 0x50/**< 0x50*/, Bahamut = 0x51/**< 0x51*/, Kujata = 0x52/**< 0x52*/, Alexander = 0x53/**< 0x53*/, Phoenix = 0x54/**< 0x54*/, NeoBahamut = 0x55/**< 0x55*/, Hades = 0x56/**< 0x56*/, Typhoon = 0x57/**< 0x57*/, BahamutZERO = 0x58/**< 0x58*/, KOTR = 0x59/**< 0x59*/, MasterSummon = 0x5A/**< 0x5A*/
        , EmptyId = 0xFF/**< 0xFF*/
        , MaxMateriaAp = 0xFFFFFF /**< 0xFFFFFF*/
    };
    Q_ENUM(MateriaNames)

    FF7Materia() = default;
    ~FF7Materia() = default;
    Q_INVOKABLE QString name(int id);
    Q_INVOKABLE QString statString(int id);
    Q_INVOKABLE QString enemySkill(int id);
    Q_INVOKABLE QString element(int id);
    Q_INVOKABLE QStringList skills(int id);
    Q_INVOKABLE QStringList status(int id);
    Q_INVOKABLE qint32 ap(int id, int lvl);
    Q_INVOKABLE inline qint8 statSTR(int id)
    {
        return Materias(id).str;
    }
    Q_INVOKABLE inline qint8 statVIT(int id)
    {
        return Materias(id).vit;
    }
    Q_INVOKABLE inline qint8 statMAG(int id)
    {
        return Materias(id).mag;
    }
    Q_INVOKABLE inline qint8 statSPI(int id)
    {
        return Materias(id).spi;
    }
    Q_INVOKABLE inline qint8 statDEX(int id)
    {
        return Materias(id).dex;
    }
    Q_INVOKABLE inline qint8 statLCK(int id)
    {
        return Materias(id).lck;
    }
    Q_INVOKABLE inline qint8 statHP(int id)
    {
        return Materias(id).hp;
    }
    Q_INVOKABLE inline qint8 statMP(int id)
    {
        return Materias(id).mp;
    }
    Q_INVOKABLE inline qint8 levels(int id)
    {
        return Materias(id).levels;
    }
    Q_INVOKABLE inline qint8 type(int id)
    {
        return Materias(id).type;
    }
    Q_INVOKABLE inline qint32 ap2num(quint8 ap[3])
    {
        return qint32(ap[0] | (ap[1] << 8) | (ap[2] << 16));
    }
    Q_INVOKABLE inline const QString &imageAllResource() const
    {
        return _resourceAllMateria;
    }
    Q_INVOKABLE QString iconResource(int id);
    Q_INVOKABLE QString fullStarResource(int id);
    Q_INVOKABLE QString emptyStartResource(int id);
    //Image Functions
    inline QIcon icon(int id)
    {
        return QIcon(QPixmap(Materias(id).imageString));
    }
    inline QPixmap pixmap(int id)
    {
        return QPixmap(Materias(id).imageString);
    }
    inline QImage image(int id)
    {
        return QImage(Materias(id).imageString);
    }
    inline QImage imageEmptyStar(int id)
    {
        return QImage(Materias(id).emptyStarString);
    }
    inline QImage imageFullStar(int id)
    {
        return QImage(Materias(id).fullStarString);
    }
    inline QIcon iconAllMateria() const
    {
        return QIcon(QPixmap(":/materia/all"));
    }
    inline QImage imageAllMateria() const
    {
        return QImage(":/materia/all");
    }
private:
    /*! \struct MATERIA
     *  \brief MATERIA data storage
     */
    struct MATERIA {
        QString name;
        QStringList skills;
        QString stats;
        QString imageString;
        QString emptyStarString;
        QString fullStarString;
        quint8 id;
        qint8 hp;
        qint8 mp;
        qint8 str;
        qint8 vit;
        qint8 dex;
        qint8 lck;
        qint8 mag;
        qint8 spi;
        QList<qint32> ap; //ap needed for levels.
        qint8 type; //1-magic,2-summon,3-independent,4-support,5-command,0-unknown
        qint8 levels;
        QString elemental;
        QStringList status;
    };
    /*!
    * \brief Materia Wrapper function to get Materia data
    * \param id Materia ID (0x00 - 0x5A && 0xFF)
    * \return Materia data for given id
    * \sa Materias(int)
    */
    const FF7Materia::MATERIA &Materias(int id);
    inline static const auto _resourceAllMateria = QStringLiteral("/materia/all");

    inline static const MATERIA _emptyMateria{
        QT_TR_NOOP("EMPTY")
        , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
        , QStringLiteral("ID:0xFF"), QString(), QString(), QString()
        , 0XFF, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
    };
    inline static const QList<MATERIA> _materiaList{
        {
            QT_TR_NOOP("MP Plus")
            , {QT_TR_NOOP("MP Plus +10%"), QT_TR_NOOP("MP Plus +20%"), QT_TR_NOOP("MP Plus +30%"), QT_TR_NOOP("MP Plus +40%"), QT_TR_NOOP("MP Plus +50%")}
            , QT_TR_NOOP("MaxMp:+% depending on level"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x00, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 20000, 30000, 50000}, 3, 5, QString(), {QString()}
        },
        {   QT_TR_NOOP("HP Plus")
            , {QT_TR_NOOP("HP Plus +10%"), QT_TR_NOOP("HP Plus +20%"), QT_TR_NOOP("HP Plus +30%"), QT_TR_NOOP("HP Plus +40%"), QT_TR_NOOP("HP Plus +50%")}
            , QT_TR_NOOP("MaxHp:+% depending on level"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x01, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 20000, 30000, 50000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Speed Plus")
            , {QT_TR_NOOP("Speed Plus +10%"), QT_TR_NOOP("Speed Plus +20%"), QT_TR_NOOP("Speed Plus +30%"), QT_TR_NOOP("Speed Plus +40%"), QT_TR_NOOP("Speed Plus +50%")}
            , QT_TR_NOOP("Dex:+% depending on level"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x02, 0, 0, 0, 0, 0, 0, 0, 0, {0, 15000, 30000, 60000, 100000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Magic Plus")
            , {QT_TR_NOOP("Magic Plus +10%"), QT_TR_NOOP("Magic Plus +20%"), QT_TR_NOOP("Magic Plus +30%"), QT_TR_NOOP("Magic Plus +40%"), QT_TR_NOOP("Magic Plus +50%")}
            , QT_TR_NOOP("Mag:+% depending on level"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x03, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 20000, 30000, 50000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Luck Plus")
            , {QT_TR_NOOP("Luck Plus +10%"), QT_TR_NOOP("Luck Plus +20%"), QT_TR_NOOP("Luck Plus +30%"), QT_TR_NOOP("Luck Plus +40%"), QT_TR_NOOP("Luck Plus +50%")}
            , QT_TR_NOOP("Lck:+% depending on level"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x04, 0, 0, 0, 0, 0, 0, 0, 0, {0, 15000, 30000, 60000, 100000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("EXP Plus")
            , {QT_TR_NOOP("Exp Plus +50%"), QT_TR_NOOP("Exp Plus +100%")}
            , QT_TR_NOOP("Lck:+1"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x05, 0, 0, 0, 0, 0, +1, 0, 0, {0, 60000, 150000, 0, 0}, 3, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Gil Plus")
            , {QT_TR_NOOP("Gil Plus +50%"), QT_TR_NOOP("Gil Plus +100%")}
            , QT_TR_NOOP("Lck:+1"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x06, 0, 0, 0, 0, 0, +1, 0, 0, {0, 80000, 150000, 0, 0}, 3, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Enemy Away")
            , {QT_TR_NOOP("Encounter Rate -50%"), QT_TR_NOOP("Encounter Rate -75%")}
            , QT_TR_NOOP("Lck:+1"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x07, 0, 0, 0, 0, 0, +1, 0, 0, {0, 10000, 50000, 0, 0}, 3, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Enemy Lure")
            , {QT_TR_NOOP("Encounter Rate +50%"), QT_TR_NOOP("Encounter Rate +100%")}
            , QT_TR_NOOP("Lck:-1"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x08, 0, 0, 0, 0, 0, -1, 0, 0, {0, 10000, 50000, 0, 0}, 3, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Chocobo Lure")
            , {QT_TR_NOOP("Chocobo Lure"), QT_TR_NOOP("Chocobo Lure +50%"), QT_TR_NOOP("Chocobo Lure +100%"), QT_TR_NOOP("Chocobo Lure +200%")}
            , QT_TR_NOOP("Lck:+1"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x09, 0, 0, 0, 0, 0, +1, 0, 0, {0, 3000, 10000, 30000, 0}, 3, 4, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Pre-emptive")
            , {QT_TR_NOOP("Pre-emptive +6%"), QT_TR_NOOP("Pre-emptive +12%"), QT_TR_NOOP("Pre-emptive +24%"), QT_TR_NOOP("Pre-emptive +36%"), QT_TR_NOOP("Pre-emptive +48%")}
            , QT_TR_NOOP("Dex:+2"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x0A, 0, 0, 0, 0, +2, 0, 0, 0, {0, 8000, 20000, 40000, 80000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Long Range")
            , {QT_TR_NOOP("Long Range")}
            , QString(), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x0B, 0, 0, 0, 0, 0, 0, 0, 0, {0, 80000, 0, 0, 0}, 3, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Mega All")
            , {QT_TR_NOOP("Mega-all x1"), QT_TR_NOOP("Mega-all x2"), QT_TR_NOOP("Mega-all x3"), QT_TR_NOOP("Mega-all x4"), QT_TR_NOOP("Mega-all x5")}
            , QString(), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x0C, 0, 0, 0, 0, 0, 0, 0, 0, {0, 20000, 40000, 80000, 160000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Counter Attack")
            ,{QT_TR_NOOP("Counter Attack 20%"), QT_TR_NOOP("Counter Attack 40%"), QT_TR_NOOP("Counter Attack 60%"), QT_TR_NOOP("Counter Attack 80%"), QT_TR_NOOP("Counter Attack 100%")}
            , QString(), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x0D, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 20000, 50000, 100000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Slash-All")
            , {QT_TR_NOOP("Slash-All"), QT_TR_NOOP("Flash")}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x0E, 0, 0, 0, 0, 0, 0, 0, 0, {0, 130000, 150000, 0, 0}, 5, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Double Cut")
            , {QT_TR_NOOP("2x-Cut"), QT_TR_NOOP("4x-Cut")}
            , QT_TR_NOOP("Dex:+2"), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x0F, 0, 0, 0, 0, +2, 0, 0, 0, {0, 100000, 150000, 0, 0}, 5, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Cover")
            , {QT_TR_NOOP("Cover +20%"), QT_TR_NOOP("Cover +40%"), QT_TR_NOOP("Cover +60%"), QT_TR_NOOP("Cover +80%"), QT_TR_NOOP("Cover +100%")}
            , QT_TR_NOOP("Vit:+1"), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x10, 0, 0, 0, +1, 0, 0, 0, 0, {0, 2000, 10000, 25000, 40000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Underwater")
            , {QT_TR_NOOP("Underwater")}
            , QString(), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x11, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 3, 1, QString(), {QString()}
        },
        {
            QT_TR_NOOP("HP <-> MP")
            , {QT_TR_NOOP("HP <-> MP")}
            , QString(), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x12, 0, 0, 0, 0, 0, 0, 0, 0, {0, 80000, 0, 0, 0}, 3, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("W-Magic")
            , {QT_TR_NOOP("W-Magic")}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x13, 0, 0, 0, 0, 0, 0, 0, 0, {0, 250000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("W-Summon")
            , {QT_TR_NOOP("W-Summon")}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x14, 0, 0, 0, 0, 0, 0, 0, 0, {0, 250000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("W-Item")
            , {QT_TR_NOOP("W-Item")}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x15, 0, 0, 0, 0, 0, 0, 0, 0, {0, 250000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("DON'T USE")
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x16"), QString(), QString(), QString()
            , 0X16, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TR_NOOP("All")
            , {QT_TR_NOOP("All x1"), QT_TR_NOOP("All x2"), QT_TR_NOOP("All x3"), QT_TR_NOOP("All x4"), QT_TR_NOOP("All x5")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x17, 0, 0, 0, 0, 0, 0, 0, 0, {0, 1500, 6000, 18000, 35000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Counter")
            , {QT_TR_NOOP("Counter Rate 20%"), QT_TR_NOOP("Counter Rate 40%"), QT_TR_NOOP("Counter Rate 60%"), QT_TR_NOOP("Counter Rate 80%"), QT_TR_NOOP("Counter Rate 100%")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x18, 0, 0, 0, 0, 0, 0, 0, 0, {0, 20000, 40000, 60000, 100000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Magic Counter")
            , {QT_TR_NOOP("Magic Counter Rate 30%"), QT_TR_NOOP("Magic Counter Rate 40%"), QT_TR_NOOP("Magic Counter Rate 60%"), QT_TR_NOOP("Magic Counter Rate 80%"), QT_TR_NOOP("Magic Counter Rate 100%")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x19, 0, 0, 0, 0, 0, 0, 0, 0, {0, 20000, 40000, 80000, 300000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("MP Turbo")
            , {QT_TR_NOOP("MP Turbo 10%"), QT_TR_NOOP("MP Turbo 20%"), QT_TR_NOOP("MP Turbo 30%"), QT_TR_NOOP("MP Turbo 40%"), QT_TR_NOOP("MP Turbo 50%")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1A, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 30000, 60000, 120000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("MP Absorb")
            , {QT_TR_NOOP("MP Absorb")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1B, 0, 0, 0, 0, 0, 0, 0, 0, {0, 100000, 0, 0, 0}, 4, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("HP Absorb")
            , {QT_TR_NOOP("HP Absorb")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1C, 0, 0, 0, 0, 0, 0, 0, 0, {0, 100000, 0, 0, 0}, 4, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Elemental")
            , {QT_TR_NOOP("Elemental 50%"), QT_TR_NOOP("Elemental 100%"), QT_TR_NOOP("Elemental 200%")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1D, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 40000, 80000, 0}, 4, 4, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Added Effect")
            , {QT_TR_NOOP("Added Effect")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1E, 0, 0, 0, 0, 0, 0, 0, 0, {0, 100000, 0, 0, 0}, 4, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Sneak Attack")
            , {QT_TR_NOOP("Sneak Attack 20%"), QT_TR_NOOP("Sneak Attack 35%"), QT_TR_NOOP("Sneak Attack 50%"), QT_TR_NOOP("Sneak Attack 65%"), QT_TR_NOOP("Sneak Attack 80%")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1F, 0, 0, 0, 0, 0, 0, 0, 0, {0, 20000, 60000, 100000, 150000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Final Attack")
            ,  {QT_TR_NOOP("Final Attack x1"), QT_TR_NOOP("Final Attack x2"), QT_TR_NOOP("Final Attack x3"), QT_TR_NOOP("Final Attack x4"), QT_TR_NOOP("Final Attack x5")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x20, 0, 0, 0, 0, 0, 0, 0, 0, {0, 20000, 40000, 80000, 160000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Added Cut")
            , {QT_TR_NOOP("Added Cut")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x21, 0, 0, 0, 0, 0, 0, 0, 0, {0, 200000, 0, 0, 0}, 4, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Steal-As-Well")
            , {QT_TR_NOOP("Steal as well")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x22, 0, 0, 0, 0, 0, 0, 0, 0, {0, 200000, 0, 0, 0}, 4, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Quadra Magic")
            , {QT_TR_NOOP("Quadra Magic x1"), QT_TR_NOOP("Quadra Magic x2"), QT_TR_NOOP("Quadra Magic x3"), QT_TR_NOOP("Quadra Magic x4"), QT_TR_NOOP("Quadra Magic x5")}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x23, 0, 0, 0, 0, 0, 0, 0, 0, {0, 40000, 80000, 120000, 200000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Steal")
            , {QT_TR_NOOP("Steal"), QT_TR_NOOP("Mug")}
            , QT_TR_NOOP("Dex:+2"), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x24, 0, 0, 0, 0, +2, 0, 0, 0, {0, 40000, 50000, 0, 0}, 5, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Sense")
            , {QT_TR_NOOP("Sense")}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x25, 0, 0, 0, 0, 0, 0, 0, 0, {0, 40000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("DON'T USE")
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x26"), QString(), QString(), QString()
            , 0X26, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Throw")
            , {QT_TR_NOOP("Throw"), QT_TR_NOOP("Coin")}
            , QT_TR_NOOP("Vit:+1"), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x27, 0, 0, 0, +1, 0, 0, 0, 0, {0, 45000, 60000, 0, 0}, 5, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Morph")
            , {QT_TR_NOOP("Morph")}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x28, 0, 0, 0, 0, 0, 0, 0, 0, {0, 100000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Deathblow")
            , {QT_TR_NOOP("DeathBlow")}
            , QT_TR_NOOP("Lck:+1"), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x29, 0, 0, 0, 0, 0, +1, 0, 0, {0, 40000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Manipulate")
            , {QT_TR_NOOP("Manipulate")}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x2A, 0, 0, 0, 0, 0, 0, 0, 0, {0, 40000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Mime")
            , {QT_TR_NOOP("Mime")}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x2B, 0, 0, 0, 0, 0, 0, 0, 0, {0, 100000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Enemy Skill")
            , {QT_TR_NOOP("Enemy Skill")}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x2C, 0, 0, 0, 0, 0, 0, 0, 0, {16777215, 0, 0, 0, 0}, 5, 1, QString(), {QString()}
        },
        {
            QT_TR_NOOP("DON'T USE")
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x2D"), QString(), QString(), QString()
            , 0X2D, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TR_NOOP("DON'T USE")
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x2E"), QString(), QString(), QString()
            , 0X2E, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TR_NOOP("DON'T USE")
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x2F"), QString(), QString(), QString()
            , 0X2F, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Master Command")
            , {QT_TR_NOOP("Master Command")}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x30, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 5, 1, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Fire")
            , {QT_TR_NOOP("Fire (4mp)"), QT_TR_NOOP("Fire2 (22mp)"), QT_TR_NOOP("Fire3 (52mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x31, -2, +2, -1, 0, 0, 0, +1, 0, {0, 2000, 18000, 35000, 0}, 1, 4, QT_TR_NOOP("[Fire]"), {QString()}
        },
        {
            QT_TR_NOOP("Ice")
            , {QT_TR_NOOP("Ice (4mp)"), QT_TR_NOOP("Ice2 (22mp)"), QT_TR_NOOP("Ice3 (52mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x32, -2, +2, -1, 0, 0, 0, +1, 0, {0, 2000, 18000, 35000, 0}, 1, 4, QT_TR_NOOP("[Ice]"), {QString()}
        },
        {
            QT_TR_NOOP("Earth")
            , {QT_TR_NOOP("Quake (6mp)"), QT_TR_NOOP("Quake2 (28mp)"), QT_TR_NOOP("Quake3 (68mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x33, -2, +2, -1, 0, 0, 0, +1, 0, {0, 6000, 22000, 40000, 0}, 1, 4, QT_TR_NOOP("[Earth]"), {QString()}
        },
        {
            QT_TR_NOOP("Lightning")
            , {QT_TR_NOOP("Bolt (4mp)"), QT_TR_NOOP("Bolt2 (22mp)"), QT_TR_NOOP("Bolt3 (52mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x34, -2, +2, -1, 0, 0, 0, +1, 0, {0, 2000, 18000, 35000, 0}, 1, 4, QT_TR_NOOP("[Lightning]"), {QString()}
        },
        {
            QT_TR_NOOP("Restore")
            , {QT_TR_NOOP("Cure (5mp)"), QT_TR_NOOP("Cure2 (24mp)"), QT_TR_NOOP("Regen (30mp)"), QT_TR_NOOP("Cure3 (64mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x35, -2, +2, -1, 0, 0, 0, +1, 0, {0, 2500, 17000, 25000, 40000}, 1, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Heal")
            , {QT_TR_NOOP("Poisona (3mp)"), QT_TR_NOOP("Esuna (15mp)"), QT_TR_NOOP("Resist (120mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x36, -2, +2, -1, 0, 0, 0, +1, 0, {0, 12000, 52000, 60000, 0}, 1, 4, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Revive")
            , {QT_TR_NOOP("Life (34mp)"), QT_TR_NOOP("Life2 (100mp)")}
            , QT_TR_NOOP("MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x37, -5, +5, -2, -1, 0, 0, +2, +1, {0, 45000, 55000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Seal")
            , {QT_TR_NOOP("Sleepel (8mp)"), QT_TR_NOOP("Silence (24mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x38, -2, +2, -1, 0, 0, 0, +1, 0, {0, 10000, 20000, 0, 0}, 1, 3, QString(), {QT_TR_NOOP("[Sleep]"), QT_TR_NOOP("[Silence]")}
        },
        {
            QT_TR_NOOP("Mystify")
            , {QT_TR_NOOP("Confu (18mp)"), QT_TR_NOOP("Berserk (28mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x39, -2, +2, -1, 0, 0, 0, +1, 0, {0, 12000, 25000, 0, 0}, 1, 3, QString(), {QT_TR_NOOP("[Confusion]"), QT_TR_NOOP("[Berserk]")}
        },
        {
            QT_TR_NOOP("Transform")
            , {QT_TR_NOOP("Mini (10mp)"), QT_TR_NOOP("Toad (14mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x3A, -2, +2, -1, 0, 0, 0, +1, 0, {0, 8000, 24000, 0, 0}, 1, 3, QString(), {QT_TR_NOOP("[Mini]"), QT_TR_NOOP("[Frog]")}
        },
        {
            QT_TR_NOOP("Exit")
            , {QT_TR_NOOP("Exit (16mp)"), QT_TR_NOOP("Remove (99mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x3B, -2, +2, -1, 0, 0, 0, +1, 0, {0, 10000, 30000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Poison")
            , {QT_TR_NOOP("Bio (8mp)"), QT_TR_NOOP("Bio2 (36mp)"), QT_TR_NOOP("Bio3 (80mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x3C, -2, +2, -1, 0, 0, 0, +1, 0, {0, 5000, 20000, 38000, 0}, 1, 4, QT_TR_NOOP("[Poison]"), {QT_TR_NOOP("[Poison]")}
        },
        {
            QT_TR_NOOP("Gravity")
            , {QT_TR_NOOP("Demi (14mp)"), QT_TR_NOOP("Demi2 (33mp)"), QT_TR_NOOP("Demi3 (48mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x3D, -2, +2, -1, 0, 0, 0, +1, 0, {0, 10000, 20000, 40000, 0}, 1, 4, QT_TR_NOOP("[Gravity]"), {QString()}
        },
        {
            QT_TR_NOOP("Barrier")
            , {QT_TR_NOOP("Barrier (16mp)"), QT_TR_NOOP("M-Barrier (24mp)"), QT_TR_NOOP("Reflect (30mp)"), QT_TR_NOOP("Wall (58mp)")}
            , QT_TR_NOOP("MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x3E, -5, +5, -2, -1, 0, 0, +2, +1, {0, 5000, 15000, 30000, 45000}, 1, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("DON'T USE")
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x3F"), QString(), QString(), QString()
            , 0X3F, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Comet")
            , {QT_TR_NOOP("Comet (70mp)"), QT_TR_NOOP("Comet2 (110mp)")}
            , QT_TR_NOOP("MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x40, -5, +5, -2, -1, 0, 0, +2, +1, {0, 12000, 60000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Time")
            , {QT_TR_NOOP("Haste (18mp)"), QT_TR_NOOP("Slow (20mp)"), QT_TR_NOOP("Stop (34mp)")}
            , QT_TR_NOOP("MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x41, -5, +5, -2, -1, 0, 0, +2, +1, {0, 10000, 20000, 42000, 0}, 1, 4, QString(), {QT_TR_NOOP("[Slow]"), QT_TR_NOOP("[Stop]")}
        },
        {
            QT_TR_NOOP("DON'T USE")
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x42"), QString(), QString(), QString()
            , 0X42, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TR_NOOP("DON'T USE")
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x43"), QString(), QString(), QString()
            , 0X43, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Destruct")
            , {QT_TR_NOOP("DeBarrier (12mp)"), QT_TR_NOOP("DeSpell (20mp)"), QT_TR_NOOP("Death (30mp)")}
            , QT_TR_NOOP("MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x44, -5, +5, -2, -1, 0, 0, +2, +1, {0, 6000, 10000, 45000, 0}, 1, 4, QString(), {QT_TR_NOOP("[Death]")}
        },
        {
            QT_TR_NOOP("Contain")
            , {QT_TR_NOOP("Freeze (82mp)"), QT_TR_NOOP("Break (86mp)"), QT_TR_NOOP("Tornado (90mp)"), QT_TR_NOOP("Flare (100mp)")}
            , QT_TR_NOOP("MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x45, -10, +10, -4, -2, 0, 0, +4, +2, {0, 5000, 10000, 15000, 60000}, 1, 5, QString(), {QT_TR_NOOP("[Confusion]"), QT_TR_NOOP("[Petrify]"), QT_TR_NOOP("[Stop]")}
        },
        {
            QT_TR_NOOP("Full Cure")
            , {QString(), QT_TR_NOOP("Full Cure (99mp)")}
            , QT_TR_NOOP("MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x46, -10, +10, -4, -2, 0, 0, +4, +2, {0, 3000, 100000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Shield")
            , {QString(), QT_TR_NOOP("Shield (180mp)")}
            , QT_TR_NOOP("MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x47, -10, +10, -4, -2, 0, 0, +4, +2, {0, 10000, 100000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Ultima")
            , {QString(), QT_TR_NOOP("Ultima (130mp)")}
            , QT_TR_NOOP("MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2"), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x48, -10, +10, -4, -2, 0, 0, +4, +2, {0, 5000, 100000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Master Magic")
            , {QT_TR_NOOP("Master Magic")}
            , QString(), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x49, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 1, 1, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Choco/Mog")
            , {QT_TR_NOOP("Choco/Mog x1 (14mp)"), QT_TR_NOOP("Choco/Mog x2 (14mp)"), QT_TR_NOOP("Choco/Mog x3 (14mp)"), QT_TR_NOOP("Choco/Mog x4 (14mp)"), QT_TR_NOOP("Choco/Mog x5 (14mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Mag:+1"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4A, -2, +2, 0, 0, 0, 0, +1, 0, {0, 2000, 14000, 25000, 35000}, 2, 5, QT_TR_NOOP("[Wind]"), {QString()}
        },
        {
            QT_TR_NOOP("Shiva")
            , {QT_TR_NOOP("Shiva x1 (32mp)"), QT_TR_NOOP("Shiva x2 (32mp)"), QT_TR_NOOP("Shiva x3 (32mp)"), QT_TR_NOOP("Shiva x4 (32mp)"), QT_TR_NOOP("Shiva x5 (32mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Mag:+1"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4B, -2, +2, 0, 0, 0, 0, +1, 0, {0, 4000, 15000, 30000, 50000}, 2, 5, QT_TR_NOOP("[Ice]"), {QString()}
        },
        {
            QT_TR_NOOP("Ifrit")
            , {QT_TR_NOOP("Ifrit x1 (34mp)"), QT_TR_NOOP("Ifrit x2 (34mp)"), QT_TR_NOOP("Ifrit x3 (34mp)"), QT_TR_NOOP("Ifrit x4 (34mp)"), QT_TR_NOOP("Ifrit x5 (34mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Mag:+1"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4C, -2, +2, 0, 0, 0, 0, +1, 0, {0, 5000, 20000, 35000, 60000}, 2, 5, QT_TR_NOOP("[Fire]"), {QString()}
        },
        {
            QT_TR_NOOP("Ramuh")
            , {QT_TR_NOOP("Ramuh x1 (40mp)"), QT_TR_NOOP("Ramuh x2 (40mp)"), QT_TR_NOOP("Ramuh x3 (40mp)"), QT_TR_NOOP("Ramuh x4 (40mp)"), QT_TR_NOOP("Ramuh x5 (40mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Mag:+1"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4D, -2, +2, 0, 0, 0, 0, +1, 0, {0, 10000, 25000, 50000, 70000}, 2, 5, QT_TR_NOOP("[Lightning]"), {QString()}
        },
        {
            QT_TR_NOOP("Titan")
            , {QT_TR_NOOP("Titan x1 (46mp)"), QT_TR_NOOP("Titan x2 (46mp)"), QT_TR_NOOP("Titan x3 (46mp)"), QT_TR_NOOP("Titan x4 (46mp)"), QT_TR_NOOP("Titan x5 (46mp)")}
            , QT_TR_NOOP("MaxHp:-2% MaxMp:+2% Mag:+1"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4E, -2, +2, 0, 0, 0, 0, +1, 0, {0, 15000, 30000, 60000, 80000}, 2, 5, QT_TR_NOOP("[Earth]"), {QString()}
        },
        {
            QT_TR_NOOP("Odin")
            , {QT_TR_NOOP("Odin x1 (80mp)"), QT_TR_NOOP("Odin x2 (80mp)"), QT_TR_NOOP("Odin x3 (80mp)"), QT_TR_NOOP("Odin x4 (80mp)"), QT_TR_NOOP("Odin x5 (80mp)")}
            , QT_TR_NOOP("MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4F, -5, +5, 0, 0, 0, 0, +1, +1, {0, 16000, 32000, 65000, 90000}, 2, 5, QString(), {QT_TR_NOOP("[Death]")}
        },
        {
            QT_TR_NOOP("Leviathan")
            , {QT_TR_NOOP("Leviathan x1 (78mp)"), QT_TR_NOOP("Leviathan x2 (78mp)"), QT_TR_NOOP("Leviathan x3 (78mp)"), QT_TR_NOOP("Leviathan x4 (78mp)"), QT_TR_NOOP("Leviathan x5 (78mp)")}
            , QT_TR_NOOP("MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x50, -5, +5, 0, 0, 0, 0, +1, +1, {0, 18000, 38000, 70000, 100000}, 2, 5, QT_TR_NOOP("[Water]"), {QString()}
        },
        {
            QT_TR_NOOP("Bahamut")
            ,{QT_TR_NOOP("Bahamut x1 (100mp)"), QT_TR_NOOP("Bahamut x2 (100mp)"), QT_TR_NOOP("Bahamut x3 (100mp)"), QT_TR_NOOP("Bahamut x4 (100mp)"), QT_TR_NOOP("Bahamut x5 (100mp)")}
            , QT_TR_NOOP("MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x51, -5, +5, 0, 0, 0, 0, +1, +1, {0, 20000, 50000, 80000, 120000}, 2, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Kujata")
            , {QT_TR_NOOP("Kujata x1 (110mp)"), QT_TR_NOOP("Kujata x2 (110mp)"), QT_TR_NOOP("Kujata x3 (110mp)"), QT_TR_NOOP("Kujata x4 (110mp)"), QT_TR_NOOP("Kujata x5 (110mp)")}
            , QT_TR_NOOP("MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x52, -5, +5, 0, 0, 0, 0, +1, +1, {0, 22000, 60000, 90000, 140000}, 2, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Alexander")
            , {QT_TR_NOOP("Alexander x1 (120mp)"), QT_TR_NOOP("Alexander x2 (120mp)"), QT_TR_NOOP("Alexander x3 (120mp)"), QT_TR_NOOP("Alexander x4 (120mp)"), QT_TR_NOOP("Alexander x5 (120mp)")}
            , QT_TR_NOOP("MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x53, -5, +5, 0, 0, 0, 0, +1, +1, {0, 25000, 65000, 100000, 150000}, 2, 5, QT_TR_NOOP("[Holy]"), {QString()}
        },
        {
            QT_TR_NOOP("Phoenix")
            , {QT_TR_NOOP("Phoenix x1 (180mp)"), QT_TR_NOOP("Phoenix x2 (180mp)"), QT_TR_NOOP("Phoenix x3 (180mp)"), QT_TR_NOOP("Phoenix x4 (180mp)"), QT_TR_NOOP("Phoenix x5 (180mp)")}
            , QT_TR_NOOP("MaxHp:-10% MaxMp:+10% Mag:+2 Spi:+2"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x54, -10, +10, 0, 0, 0, 0, +2, +2, {0, 28000, 70000, 120000, 180000}, 2, 5, QT_TR_NOOP("[Fire]"), {QString()}
        },
        {
            QT_TR_NOOP("Neo Bahamut")
            , {QT_TR_NOOP("Neo Bahamut x1 (140mp)"), QT_TR_NOOP("Neo Bahamut x2 (140mp)"), QT_TR_NOOP("Neo Bahamut x3 (140mp)"), QT_TR_NOOP("Neo Bahamut x4 (140mp)"), QT_TR_NOOP("Neo Bahamut x5 (140mp)")}
            , QT_TR_NOOP("MaxHp:-10% MaxMp:+10% Mag:+2 Spi:+2"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x55, -10, +10, 0, 0, 0, 0, +2, +2, {0, 30000, 80000, 140000, 200000}, 2, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Hades")
            , {QT_TR_NOOP("Hades x1 (150mp)"), QT_TR_NOOP("Hades x2 (150mp)"), QT_TR_NOOP("Hades x3 (150mp)"), QT_TR_NOOP("Hades x4 (150mp)"), QT_TR_NOOP("Hades x5 (150mp)")}
            , QT_TR_NOOP("MaxHp:-10% MaxMp:+15% Mag:+4 Spi:+4"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x56, -10, +15, 0, 0, 0, 0, +4, +4, {0, 35000, 120000, 150000, 250000}, 2, 5, QString(), {QT_TR_NOOP("[Sleep]"), QT_TR_NOOP("[Poison]"), QT_TR_NOOP("[Confusion]"), QT_TR_NOOP("[Silence]"), QT_TR_NOOP("[Frog]"), QT_TR_NOOP("[Mini]")}
        },
        {
            QT_TR_NOOP("Typhon")
            , {QT_TR_NOOP("Typhon x1 (160mp)"), QT_TR_NOOP("Typhon x2 (160mp)"), QT_TR_NOOP("Typhon x3 (160mp)"), QT_TR_NOOP("Typhon x4 (160mp)"), QT_TR_NOOP("Typhon x5 (160mp)")}
            , QT_TR_NOOP("MaxHp:-10% MaxMp:+15% Mag:+4 Spi:+4"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x57, -10, +15, 0, 0, 0, 0, +4, +4, {0, 35000, 120000, 150000, 250000}, 2, 5, QT_TR_NOOP("[Wind]"), {QString()}
        },
        {
            QT_TR_NOOP("Bahamut ZERO")
            , {QT_TR_NOOP("Bahamut ZERO x1 (180mp)"), QT_TR_NOOP("Bahamut ZERO x2 (180mp)"), QT_TR_NOOP("Bahamut ZERO x3 (180mp)"), QT_TR_NOOP("Bahamut ZERO x4 (180mp)"), QT_TR_NOOP("Bahamut ZERO x5 (180mp)")}
            , QT_TR_NOOP("MaxHp:-10% MaxMp:+15% Mag:+4 Spi:+4"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            ,0x58, -10, +15, 0, 0, 0, 0, +4, +4, {0, 35000, 120000, 150000, 250000}, 2, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Knights of the Round")
            , {QT_TR_NOOP("KOTR x1 (250mp)"), QT_TR_NOOP("KOTR x2 (250mp)"), QT_TR_NOOP("KOTR x3 (250mp)"), QT_TR_NOOP("KOTR x4 (250mp)"), QT_TR_NOOP("KOTR x5 (250mp)")}
            , QT_TR_NOOP("MaxHp:-10% MaxMp:+20% Mag:+8 Spi:+8"), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x59, -10, +20, 0, 0, 0, 0, +8, +8, {0, 50000, 200000, 300000, 500000}, 2, 5, QString(), {QString()}
        },
        {
            QT_TR_NOOP("Master Summon")
            , {QT_TR_NOOP("Master Summon")}
            , QString(), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x5A, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 2, 1, QString(), {QString()}
        }
    };
    inline static const QStringList _enemySkills{
        QT_TR_NOOP("Frog Song")
        , QT_TR_NOOP("L4 Suicide")
        , QT_TR_NOOP("Magic Hammer")
        , QT_TR_NOOP("White Wind")
        , QT_TR_NOOP("Big Guard")
        , QT_TR_NOOP("Angel Whisper")
        , QT_TR_NOOP("Dragon Force")
        , QT_TR_NOOP("Death Force")
        , QT_TR_NOOP("Flame Thrower")
        , QT_TR_NOOP("Laser")
        , QT_TR_NOOP("Matra Magic")
        , QT_TR_NOOP("Bad Breath")
        , QT_TR_NOOP("Beta")
        , QT_TR_NOOP("Aqualung")
        , QT_TR_NOOP("Trine")
        , QT_TR_NOOP("Magic Breath")
        , QT_TR_NOOP("????")
        , QT_TR_NOOP("Goblin Punch")
        , QT_TR_NOOP("Chocobuckle")
        , QT_TR_NOOP("L5 Death")
        , QT_TR_NOOP("Death Sentence")
        , QT_TR_NOOP("Roulette")
        , QT_TR_NOOP("Shadow Flare")
        , QT_TR_NOOP("Pandora's Box")
    };
};
