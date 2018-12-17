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
    Q_INVOKABLE inline qint8 statSTR(int id){return Materias(id).str;}
    Q_INVOKABLE inline qint8 statVIT(int id){return Materias(id).vit;}
    Q_INVOKABLE inline qint8 statMAG(int id){return Materias(id).mag;}
    Q_INVOKABLE inline qint8 statSPI(int id){return Materias(id).spi;}
    Q_INVOKABLE inline qint8 statDEX(int id){return Materias(id).dex;}
    Q_INVOKABLE inline qint8 statLCK(int id){return Materias(id).lck;}
    Q_INVOKABLE inline qint8 statHP(int id){return Materias(id).hp;}
    Q_INVOKABLE inline qint8 statMP(int id){return Materias(id).mp;}
    Q_INVOKABLE inline qint8 levels(int id){return Materias(id).levels;}
    Q_INVOKABLE inline qint8 type(int id){return Materias(id).type;}
    Q_INVOKABLE inline quint32 ap2num(quint8 ap[3]){return quint32(ap[0] | (ap[1] << 8) | (ap[2] << 16));}
    Q_INVOKABLE inline const QString& imageAllResource() const {return _resourceAllMateria;}
    Q_INVOKABLE QString iconResource(int id);
    Q_INVOKABLE QString fullStarResource(int id);
    Q_INVOKABLE QString emptyStartResource(int id);
    //Image Functions
    inline QIcon icon(int id) {return QIcon(QPixmap(Materias(id).imageString));}
    inline QPixmap pixmap(int id) {return QPixmap(Materias(id).imageString);}
    inline QImage image(int id) {return QImage(Materias(id).imageString);}
    inline QImage imageEmptyStar(int id) {return QImage(Materias(id).emptyStarString);}
    inline QImage imageFullStar(int id) {return QImage(Materias(id).fullStarString);}
    inline QIcon iconAllMateria() const {return QIcon(QPixmap(":/materia/all"));}
    inline QImage imageAllMateria() const {return QImage(":/materia/all");}
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
    const FF7Materia::MATERIA& Materias(int id);
    inline static const auto _resourceAllMateria = QStringLiteral("/materia/all");
    inline static const auto _nameGroup = QStringLiteral("Materia_Names");
    inline static const auto _skillGroup = QStringLiteral("Materia_Skills");
    inline static const auto _statsGroup = QStringLiteral("Materia_Stats");
    inline static const auto _elementGroup  = QStringLiteral("Elements");
    inline static const auto _statusGroup  = QStringLiteral("Status");

    inline static const MATERIA _emptyMateria{
        QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("EMPTY"))
        , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
        , QStringLiteral("ID:0xFF"), QString(), QString(), QString()
        , 0XFF, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
    };
    inline static const QList<MATERIA> _materiaList{
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("MP Plus"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("MP Plus +10%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("MP Plus +20%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("MP Plus +30%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("MP Plus +40%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("MP Plus +50%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxMp:+% depending on level")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x00, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 20000, 30000, 50000}, 3, 5, QString(), {QString()}
        },
        {   QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("HP Plus"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("HP Plus +10%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("HP Plus +20%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("HP Plus +30%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("HP Plus +40%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("HP Plus +50%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:+% depending on level")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x01, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 20000, 30000, 50000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Speed Plus"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Speed Plus +10%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Speed Plus +20%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Speed Plus +30%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Speed Plus +40%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Speed Plus +50%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Dex:+% depending on level")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x02, 0, 0, 0, 0, 0, 0, 0, 0, {0, 15000, 30000, 60000, 100000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Magic Plus"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Magic Plus +10%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Magic Plus +20%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Magic Plus +30%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Magic Plus +40%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Magic Plus +50%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Mag:+% depending on level")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x03, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 20000, 30000, 50000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Luck Plus"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Luck Plus +10%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Luck Plus +20%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Luck Plus +30%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Luck Plus +40%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Luck Plus +50%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Lck:+% depending on level")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x04, 0, 0, 0, 0, 0, 0, 0, 0, {0, 15000, 30000, 60000, 100000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("EXP Plus"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Exp Plus +50%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Exp Plus +100%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Lck:+1")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x05, 0, 0, 0, 0, 0, +1, 0, 0, {0, 60000, 150000, 0, 0}, 3, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Gil Plus"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Gil Plus +50%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Gil Plus +100%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Lck:+1")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x06, 0, 0, 0, 0, 0, +1, 0, 0, {0, 80000, 150000, 0, 0}, 3, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Enemy Away"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Encounter Rate -50%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Encounter Rate -75%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Lck:+1")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x07, 0, 0, 0, 0, 0, +1, 0, 0, {0, 10000, 50000, 0, 0}, 3, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Enemy Lure"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Encounter Rate +50%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Encounter Rate +100%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Lck:-1")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x08, 0, 0, 0, 0, 0, -1, 0, 0, {0, 10000, 50000, 0, 0}, 3, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Chocobo Lure"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Chocobo Lure")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Chocobo Lure +50%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Chocobo Lure +100%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Chocobo Lure +200%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Lck:+1")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x09, 0, 0, 0, 0, 0, +1, 0, 0, {0, 3000, 10000, 30000, 0}, 3, 4, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Pre-emptive"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Pre-emptive +6%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Pre-emptive +12%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Pre-emptive +24%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Pre-emptive +36%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Pre-emptive +48%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Dex:+2")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x0A, 0, 0, 0, 0, +2, 0, 0, 0, {0, 8000, 20000, 40000, 80000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Long Range"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Long Range"))}
            , QString(), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x0B, 0, 0, 0, 0, 0, 0, 0, 0, {0, 80000, 0, 0, 0}, 3, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Mega All"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Mega-all x1")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Mega-all x2")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Mega-all x3")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Mega-all x4")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Mega-all x5"))}
            , QString(), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x0C, 0, 0, 0, 0, 0, 0, 0, 0, {0, 20000, 40000, 80000, 160000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Counter Attack"))
            ,{QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Counter Attack 20%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Counter Attack 40%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Counter Attack 60%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Counter Attack 80%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Counter Attack 100%"))}
            , QString(), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x0D, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 20000, 50000, 100000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Slash-All"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Slash-All")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Flash"))}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x0E, 0, 0, 0, 0, 0, 0, 0, 0, {0, 130000, 150000, 0, 0}, 5, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Double Cut"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("2x-Cut")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("4x-Cut"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Dex:+2")), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x0F, 0, 0, 0, 0, +2, 0, 0, 0, {0, 100000, 150000, 0, 0}, 5, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Cover"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Cover +20%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Cover +40%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Cover +60%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Cover +80%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Cover +100%"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Vit:+1")), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x10, 0, 0, 0, +1, 0, 0, 0, 0, {0, 2000, 10000, 25000, 40000}, 3, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Underwater"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Underwater"))}
            , QString(), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x11, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 3, 1, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("HP <-> MP"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("HP <-> MP"))}
            , QString(), QStringLiteral(":/materia/independent"), QStringLiteral(":/materia/independent_star_empty"), QStringLiteral(":/materia/independent_star_full")
            , 0x12, 0, 0, 0, 0, 0, 0, 0, 0, {0, 80000, 0, 0, 0}, 3, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("W-Magic"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("W-Magic"))}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x13, 0, 0, 0, 0, 0, 0, 0, 0, {0, 250000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("W-Summon"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("W-Summon"))}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x14, 0, 0, 0, 0, 0, 0, 0, 0, {0, 250000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("W-Item"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("W-Item"))}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x15, 0, 0, 0, 0, 0, 0, 0, 0, {0, 250000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("DON'T USE"))
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x16"), QString(), QString(), QString()
            , 0X16, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("All"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("All x1")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("All x2")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("All x3")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("All x4")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("All x5"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x17, 0, 0, 0, 0, 0, 0, 0, 0, {0, 1500, 6000, 18000, 35000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Counter"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Counter Rate 20%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Counter Rate 40%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Counter Rate 60%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Counter Rate 80%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Counter Rate 100%"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x18, 0, 0, 0, 0, 0, 0, 0, 0, {0, 20000, 40000, 60000, 100000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Magic Counter"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Magic Counter Rate 30%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Magic Counter Rate 40%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Magic Counter Rate 60%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Magic Counter Rate 80%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Magic Counter Rate 100%"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x19, 0, 0, 0, 0, 0, 0, 0, 0, {0, 20000, 40000, 80000, 300000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("MP Turbo"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("MP Turbo 10%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("MP Turbo 20%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("MP Turbo 30%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("MP Turbo 40%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("MP Turbo 50%"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1A, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 30000, 60000, 120000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("MP Absorb"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("MP Absorb"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1B, 0, 0, 0, 0, 0, 0, 0, 0, {0, 100000, 0, 0, 0}, 4, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("HP Absorb"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("HP Absorb"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1C, 0, 0, 0, 0, 0, 0, 0, 0, {0, 100000, 0, 0, 0}, 4, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Elemental"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Elemental 50%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Elemental 100%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Elemental 200%"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1D, 0, 0, 0, 0, 0, 0, 0, 0, {0, 10000, 40000, 80000, 0}, 4, 4, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Added Effect"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Added Effect"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1E, 0, 0, 0, 0, 0, 0, 0, 0, {0, 100000, 0, 0, 0}, 4, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Sneak Attack"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Sneak Attack 20%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Sneak Attack 35%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Sneak Attack 50%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Sneak Attack 65%")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Sneak Attack 80%"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x1F, 0, 0, 0, 0, 0, 0, 0, 0, {0, 20000, 60000, 100000, 150000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Final Attack"))
            ,  {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Final Attack x1")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Final Attack x2")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Final Attack x3")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Final Attack x4")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Final Attack x5"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x20, 0, 0, 0, 0, 0, 0, 0, 0, {0, 20000, 40000, 80000, 160000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Added Cut"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Added Cut"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x21, 0, 0, 0, 0, 0, 0, 0, 0, {0, 200000, 0, 0, 0}, 4, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Steal-As-Well"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Steal as well"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x22, 0, 0, 0, 0, 0, 0, 0, 0, {0, 200000, 0, 0, 0}, 4, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Quadra Magic"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Quadra Magic x1")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Quadra Magic x2")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Quadra Magic x3")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Quadra Magic x4")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Quadra Magic x5"))}
            , QString(), QStringLiteral(":/materia/support"), QStringLiteral(":/materia/support_star_empty"), QStringLiteral(":/materia/support_star_full")
            , 0x23, 0, 0, 0, 0, 0, 0, 0, 0, {0, 40000, 80000, 120000, 200000}, 4, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Steal"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Steal")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Mug"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Dex:+2")), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x24, 0, 0, 0, 0, +2, 0, 0, 0, {0, 40000, 50000, 0, 0}, 5, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Sense"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Sense"))}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x25, 0, 0, 0, 0, 0, 0, 0, 0, {0, 40000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("DON'T USE"))
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x26"), QString(), QString(), QString()
            , 0X26, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Throw"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Throw")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Coin"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Vit:+1")), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x27, 0, 0, 0, +1, 0, 0, 0, 0, {0, 45000, 60000, 0, 0}, 5, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Morph"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Morph"))}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x28, 0, 0, 0, 0, 0, 0, 0, 0, {0, 100000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Deathblow"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("DeathBlow"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("Lck:+1")), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x29, 0, 0, 0, 0, 0, +1, 0, 0, {0, 40000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Manipulate"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Manipulate"))}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x2A, 0, 0, 0, 0, 0, 0, 0, 0, {0, 40000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Mime"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Mime"))}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x2B, 0, 0, 0, 0, 0, 0, 0, 0, {0, 100000, 0, 0, 0}, 5, 2, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Enemy Skill"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Enemy Skill"))}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x2C, 0, 0, 0, 0, 0, 0, 0, 0, {16777215, 0, 0, 0, 0}, 5, 1, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("DON'T USE"))
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x2D"), QString(), QString(), QString()
            , 0X2D, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("DON'T USE"))
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x2E"), QString(), QString(), QString()
            , 0X2E, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("DON'T USE"))
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x2F"), QString(), QString(), QString()
            , 0X2F, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Master Command"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Master Command"))}
            , QString(), QStringLiteral(":/materia/command"), QStringLiteral(":/materia/command_star_empty"), QStringLiteral(":/materia/command_star_full")
            , 0x30, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 5, 1, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Fire"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Fire (4mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Fire2 (22mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Fire3 (52mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x31, -2, +2, -1, 0, 0, 0, +1, 0, {0, 2000, 18000, 35000, 0}, 1, 4, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Fire]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Ice"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ice (4mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ice2 (22mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ice3 (52mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x32, -2, +2, -1, 0, 0, 0, +1, 0, {0, 2000, 18000, 35000, 0}, 1, 4, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Ice]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Earth"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Quake (6mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Quake2 (28mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Quake3 (68mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x33, -2, +2, -1, 0, 0, 0, +1, 0, {0, 6000, 22000, 40000, 0}, 1, 4, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Earth]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Lightning"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bolt (4mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bolt2 (22mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bolt3 (52mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x34, -2, +2, -1, 0, 0, 0, +1, 0, {0, 2000, 18000, 35000, 0}, 1, 4, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Lightning]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Restore"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Cure (5mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Cure2 (24mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Regen (30mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Cure3 (64mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x35, -2, +2, -1, 0, 0, 0, +1, 0, {0, 2500, 17000, 25000, 40000}, 1, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Heal"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Poisona (3mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Esuna (15mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Resist (120mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x36, -2, +2, -1, 0, 0, 0, +1, 0, {0, 12000, 52000, 60000, 0}, 1, 4, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Revive"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Life (34mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Life2 (100mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x37, -5, +5, -2, -1, 0, 0, +2, +1, {0, 45000, 55000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Seal"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Sleepel (8mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Silence (24mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x38, -2, +2, -1, 0, 0, 0, +1, 0, {0, 10000, 20000, 0, 0}, 1, 3, QString(), {QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Sleep]")), QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Silence]"))}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Mystify"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Confu (18mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Berserk (28mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x39, -2, +2, -1, 0, 0, 0, +1, 0, {0, 12000, 25000, 0, 0}, 1, 3, QString(), {QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Confusion]")), QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Berserk]"))}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Transform"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Mini (10mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Toad (14mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x3A, -2, +2, -1, 0, 0, 0, +1, 0, {0, 8000, 24000, 0, 0}, 1, 3, QString(), {QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Mini]")), QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Frog]"))}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Exit"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Exit (16mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Remove (99mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x3B, -2, +2, -1, 0, 0, 0, +1, 0, {0, 10000, 30000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Poison"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bio (8mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bio2 (36mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bio3 (80mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x3C, -2, +2, -1, 0, 0, 0, +1, 0, {0, 5000, 20000, 38000, 0}, 1, 4, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Poison]")), {QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Poison]"))}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Gravity"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Demi (14mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Demi2 (33mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Demi3 (48mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Str:-1 Mag:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x3D, -2, +2, -1, 0, 0, 0, +1, 0, {0, 10000, 20000, 40000, 0}, 1, 4, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Gravity]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Barrier"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Barrier (16mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("M-Barrier (24mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Reflect (30mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Wall (58mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x3E, -5, +5, -2, -1, 0, 0, +2, +1, {0, 5000, 15000, 30000, 45000}, 1, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("DON'T USE"))
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x3F"), QString(), QString(), QString()
            , 0X3F, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Comet"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Comet (70mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Comet2 (110mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x40, -5, +5, -2, -1, 0, 0, +2, +1, {0, 12000, 60000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Time"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Haste (18mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Slow (20mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Stop (34mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x41, -5, +5, -2, -1, 0, 0, +2, +1, {0, 10000, 20000, 42000, 0}, 1, 4, QString(), {QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Slow]")), QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Stop]"))}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("DON'T USE"))
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x42"), QString(), QString(), QString()
            , 0X42, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("DON'T USE"))
            , {QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?"), QStringLiteral("?")}
            , QStringLiteral("ID:0x43"), QString(), QString(), QString()
            , 0X43, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 0, 0, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Destruct"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("DeBarrier (12mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("DeSpell (20mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Death (30mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-5% MaxMp:+5% Str:-2 Vit:-1 Mag:+2 Spi:+1")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x44, -5, +5, -2, -1, 0, 0, +2, +1, {0, 6000, 10000, 45000, 0}, 1, 4, QString(), {QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Death]"))}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Contain"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Freeze (82mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Break (86mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Tornado (90mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Flare (100mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x45, -10, +10, -4, -2, 0, 0, +4, +2, {0, 5000, 10000, 15000, 60000}, 1, 5, QString(), {QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Confusion]")), QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Petrify]")), QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Stop]"))}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Full Cure"))
            , {QString(), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Full Cure (99mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x46, -10, +10, -4, -2, 0, 0, +4, +2, {0, 3000, 100000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Shield"))
            , {QString(), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Shield (180mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x47, -10, +10, -4, -2, 0, 0, +4, +2, {0, 10000, 100000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Ultima"))
            , {QString(), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ultima (130mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-10% MaxMp:+10% Str:-4 Vit:-2 Mag:+4 Spi:+2")), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x48, -10, +10, -4, -2, 0, 0, +4, +2, {0, 5000, 100000, 0, 0}, 1, 3, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Master Magic"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Master Magic"))}
            , QString(), QStringLiteral(":/materia/magic"), QStringLiteral(":/materia/magic_star_empty"), QStringLiteral(":/materia/magic_star_full")
            , 0x49, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 1, 1, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Choco/Mog"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Choco/Mog x1 (14mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Choco/Mog x2 (14mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Choco/Mog x3 (14mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Choco/Mog x4 (14mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Choco/Mog x5 (14mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Mag:+1")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4A, -2, +2, 0, 0, 0, 0, +1, 0, {0, 2000, 14000, 25000, 35000}, 2, 5, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Wind]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Shiva"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Shiva x1 (32mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Shiva x2 (32mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Shiva x3 (32mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Shiva x4 (32mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Shiva x5 (32mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Mag:+1")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4B, -2, +2, 0, 0, 0, 0, +1, 0, {0, 4000, 15000, 30000, 50000}, 2, 5, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Ice]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Ifrit"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ifrit x1 (34mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ifrit x2 (34mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ifrit x3 (34mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ifrit x4 (34mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ifrit x5 (34mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Mag:+1")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4C, -2, +2, 0, 0, 0, 0, +1, 0, {0, 5000, 20000, 35000, 60000}, 2, 5, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Fire]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Ramuh"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ramuh x1 (40mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ramuh x2 (40mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ramuh x3 (40mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ramuh x4 (40mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Ramuh x5 (40mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Mag:+1")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4D, -2, +2, 0, 0, 0, 0, +1, 0, {0, 10000, 25000, 50000, 70000}, 2, 5, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Lightning]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Titan"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Titan x1 (46mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Titan x2 (46mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Titan x3 (46mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Titan x4 (46mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Titan x5 (46mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-2% MaxMp:+2% Mag:+1")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4E, -2, +2, 0, 0, 0, 0, +1, 0, {0, 15000, 30000, 60000, 80000}, 2, 5, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Earth]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Odin"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Odin x1 (80mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Odin x2 (80mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Odin x3 (80mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Odin x4 (80mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Odin x5 (80mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x4F, -5, +5, 0, 0, 0, 0, +1, +1, {0, 16000, 32000, 65000, 90000}, 2, 5, QString(), {QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Death]"))}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Leviathan"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Leviathan x1 (78mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Leviathan x2 (78mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Leviathan x3 (78mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Leviathan x4 (78mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Leviathan x5 (78mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x50, -5, +5, 0, 0, 0, 0, +1, +1, {0, 18000, 38000, 70000, 100000}, 2, 5, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Water]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Bahamut"))
            ,{QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bahamut x1 (100mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bahamut x2 (100mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bahamut x3 (100mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bahamut x4 (100mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bahamut x5 (100mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x51, -5, +5, 0, 0, 0, 0, +1, +1, {0, 20000, 50000, 80000, 120000}, 2, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Kujata"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Kujata x1 (110mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Kujata x2 (110mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Kujata x3 (110mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Kujata x4 (110mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Kujata x5 (110mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x52, -5, +5, 0, 0, 0, 0, +1, +1, {0, 22000, 60000, 90000, 140000}, 2, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Alexander"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Alexander x1 (120mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Alexander x2 (120mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Alexander x3 (120mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Alexander x4 (120mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Alexander x5 (120mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-5% MaxMp:+5% Mag:+1 Spi:+1")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x53, -5, +5, 0, 0, 0, 0, +1, +1, {0, 25000, 65000, 100000, 150000}, 2, 5, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Holy]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Phoenix"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Phoenix x1 (180mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Phoenix x2 (180mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Phoenix x3 (180mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Phoenix x4 (180mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Phoenix x5 (180mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-10% MaxMp:+10% Mag:+2 Spi:+2")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x54, -10, +10, 0, 0, 0, 0, +2, +2, {0, 28000, 70000, 120000, 180000}, 2, 5, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Fire]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Neo Bahamut"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Neo Bahamut x1 (140mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Neo Bahamut x2 (140mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Neo Bahamut x3 (140mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Neo Bahamut x4 (140mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Neo Bahamut x5 (140mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-10% MaxMp:+10% Mag:+2 Spi:+2")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x55, -10, +10, 0, 0, 0, 0, +2, +2, {0, 30000, 80000, 140000, 200000}, 2, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Hades"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Hades x1 (150mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Hades x2 (150mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Hades x3 (150mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Hades x4 (150mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Hades x5 (150mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-10% MaxMp:+15% Mag:+4 Spi:+4")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x56, -10, +15, 0, 0, 0, 0, +4, +4, {0, 35000, 120000, 150000, 250000}, 2, 5, QString(), {QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Sleep]")), QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Poison]")), QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Confusion]")), QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Silence]")), QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Frog]")), QT_TRANSLATE_NOOP(_statusGroup,  QStringLiteral("[Mini]"))}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Typhon"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Typhon x1 (160mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Typhon x2 (160mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Typhon x3 (160mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Typhon x4 (160mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Typhon x5 (160mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-10% MaxMp:+15% Mag:+4 Spi:+4")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x57, -10, +15, 0, 0, 0, 0, +4, +4, {0, 35000, 120000, 150000, 250000}, 2, 5, QT_TRANSLATE_NOOP(_elementGroup, QStringLiteral("[Wind]")), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Bahamut ZERO"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bahamut ZERO x1 (180mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bahamut ZERO x2 (180mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bahamut ZERO x3 (180mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bahamut ZERO x4 (180mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Bahamut ZERO x5 (180mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-10% MaxMp:+15% Mag:+4 Spi:+4")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            ,0x58, -10, +15, 0, 0, 0, 0, +4, +4, {0, 35000, 120000, 150000, 250000}, 2, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Knights of the Round"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("KOTR x1 (250mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("KOTR x2 (250mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("KOTR x3 (250mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("KOTR x4 (250mp)")), QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("KOTR x5 (250mp)"))}
            , QT_TRANSLATE_NOOP(_statsGroup, QStringLiteral("MaxHp:-10% MaxMp:+20% Mag:+8 Spi:+8")), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x59, -10, +20, 0, 0, 0, 0, +8, +8, {0, 50000, 200000, 300000, 500000}, 2, 5, QString(), {QString()}
        },
        {
            QT_TRANSLATE_NOOP(_nameGroup, QStringLiteral("Master Summon"))
            , {QT_TRANSLATE_NOOP(_skillGroup, QStringLiteral("Master Summon"))}
            , QString(), QStringLiteral(":/materia/summon"), QStringLiteral(":/materia/summon_star_empty"), QStringLiteral(":/materia/summon_star_full")
            , 0x5A, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0}, 2, 1, QString(), {QString()}
        }
    };
    inline static const QString _eskillGroup = QStringLiteral("E_skills");
    inline static const QStringList _enemySkills{
        QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Frog Song"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("L4 Suicide"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Magic Hammer"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("White Wind"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Big Guard"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Angel Whisper"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Dragon Force"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Death Force"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Flame Thrower"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Laser"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Matra Magic"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Bad Breath"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Beta"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Aqualung"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Trine"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Magic Breath"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("????"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Goblin Punch"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Chocobuckle"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("L5 Death"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Death Sentence"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Roulette"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Shadow Flare"))
        , QT_TRANSLATE_NOOP(_eskillGroup, QStringLiteral("Pandora's Box"))
    };
};
