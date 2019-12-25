/****************************************************************************/
//    copyright 2012 - 2019  Chris Rizzitello <sithlord48@gmail.com>        //
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

class QQmlEngine;
class QJSEngine;

/*! \class FF7Location
 *  \brief Info about field locations.
 */
class FF7Location : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Get the FF7Location Instance.
     * @sa qmlSingletonRegister()
     */
    static FF7Location *instance();

    /**
     * @brief Register The FF7Location Singleton for QML
     */
    QObject *qmlSingletonRegister(QQmlEngine *engine, QJSEngine *scriptEngine);

    /*!
    * \brief get filename for location (flevel file)
    * \param index Number on the location list
    * \return filename of the location
    *  \sa fileName(int,int)
    */
    Q_INVOKABLE const QString &fileName(int index);

    /*! \brief get filename for location (flevel file)
    *  \param MapID Map Number location is on
    *  \param LocID Location Id for location
    *  \return filename of the location
    * \sa fileName(int)
    */
    Q_INVOKABLE const QString &fileName(int MapID, int LocID);

    /*! \brief locations String showing menu
     * \param index Number on the locations list
     * \return UnTranslated location string (as shown in menu/save preview)
     * \sa locationString(QString)
     */
    Q_INVOKABLE QString rawLocationString(int index);

    /*! \brief locations String showing menu
     * \param fileName fileName of location
     * \return UnTranslated location string (as shown in menu/save preview)
     * \sa locationString(int)
     */
    Q_INVOKABLE QString rawLocationString(const QString &fileName);

    /*! \brief locations String showing menu
     * \param index Number on the locations list
     * \return Translated location string (as shown in menu/save preview)
     * \sa locationString(QString)
     */
    Q_INVOKABLE QString locationString(int index);

    /*! \brief locations String showing menu
     * \param fileName fileName of location
     * \return Translated location string (as shown in menu/save preview)
     * \sa locationString(int)
     */
    Q_INVOKABLE QString locationString(const QString &fileName);

    /*! \brief get map id number
     *  \param index Number on the locations list
     *  \return MapID as QString
     *  \sa mapID(QString)
     */
    Q_INVOKABLE const QString &mapID(int index);

    /*! \brief get map id number
     *  \param fileName fileName of location
     *  \return MapID as QString
     *  \sa mapID(int)
     */
    Q_INVOKABLE const QString &mapID(const QString &fileName);

    /*! \brief get location id number
     *  \param index Number on the locations list
     *  \return location id as QString
     *  \sa locationID(QString)
     */
    Q_INVOKABLE const QString &locationID(int index);

    /*! \brief get location id number
     *  \param fileName fileName of location
     *  \return locationID as QString
     *  \sa locationID(int)
     */
    Q_INVOKABLE const QString &locationID(const QString &fileName);

    /*! \brief x coord of save or valid placment
     *  \param index Number on the locations list
     *  \return x as QString
     *  \sa x(QString)
     */
    Q_INVOKABLE const QString &x(int index);

    /*! \brief x coord of save or valid placment
     *  \param fileName fileName of location
     *  \return x as QString
     *  \sa x(int)
     */
    Q_INVOKABLE const QString &x(const QString &fileName);

    /*! \brief y coord of save or valid placment
     *  \param index Number on the locations list
     *  \return y as QString
     *  \sa y(QString)
     */
    Q_INVOKABLE const QString &y(int index);

    /*! \brief y coord of save or valid placment
     *  \param fileName fileName of location
     *  \return y as QString
     *  \sa y(int)
     */
    Q_INVOKABLE const QString &y(const QString &fileName);

    /*! \brief triangle of save or valid placment
     *  \param index Number on the locations list
     *  \return triangle as QString
     *  \sa t(QString)
     */
    Q_INVOKABLE const QString &t(int index);

    /*! \brief triangle of save or valid placment
    *  \param fileName fileName of location
    *  \return t as QString
    *  \sa t(int)
    */
    Q_INVOKABLE const QString &t(const QString &fileName);

    /*! \brief direction your facing
     *  \param index Number on the locations list
     *  \return d as QString
     *  \sa d(QString)
     */
    Q_INVOKABLE const QString &d(int index);

    /*! \brief direction your facing
    *  \param fileName fileName of location
    *  \return d as QString
    *  \sa d(int)
    */
    Q_INVOKABLE const QString &d(const QString &fileName);

    /*! \brief how many items on the location list do we have
     *  \return length of Locations
     */
    Q_INVOKABLE int size() const;
private:
    FF7Location *operator = (FF7Location &other) = delete;
    FF7Location(const FF7Location &other) = delete;
    explicit FF7Location(QObject *parent = nullptr);
    ~FF7Location();
    struct FF7LocationPrivate;
    FF7LocationPrivate *dPtr;

    /*! \struct LOCATION
     *  \brief type for holding location data
     */
    struct LOCATION {
        QString filename;
        QString location;
        QString map_id;
        QString loc_id;
        QString x;
        QString y;
        QString t;
        QString d;
    };
    /*!
     * \brief location return
     * \param index
     * \return Locations [index] or emptyLocation
     */
    const FF7Location::LOCATION &location(int index);

    struct FF7LocationPrivate {
        inline static const LOCATION _emptyLocation {QString(), QString(), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")};

        /*!
     * \var _duplicateLocations List of reused locations with different names
     */

        inline static const QList<LOCATION> _duplicateLocations{
            /****************Dupilcate Field Strings Don't Display************/
            {QStringLiteral("elminn_2"), QT_TR_NOOP("Cloud's Past"), QStringLiteral("1"), QStringLiteral("332"), QStringLiteral("164"), QStringLiteral("125"), QStringLiteral("8"), QStringLiteral("32")}
            , {QStringLiteral("delmin1"), QT_TR_NOOP("Cloud's Villa"), QStringLiteral("1"), QStringLiteral("446"), QStringLiteral("-40"), QStringLiteral("-43"), QStringLiteral("10"), QStringLiteral("32")}
        };

        /*!
     * \var _locations List of all locations
     */
        inline static const QList<LOCATION> _locations {
            /************************Every Location In The Game With Stock Translation******************/
            {QStringLiteral("testfight"), QT_TR_NOOP("Test Fight"), QStringLiteral("2"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("32")}
            /****************World Map Strings *************/
            , {QStringLiteral("WM0"), QT_TR_NOOP("Midgar Area"), QStringLiteral("3"), QStringLiteral("1"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM1"), QT_TR_NOOP("Midgar Area"), QStringLiteral("3"), QStringLiteral("2"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM2"), QT_TR_NOOP("Grasslands Area"), QStringLiteral("3"), QStringLiteral("3"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM3"), QT_TR_NOOP("Grasslands Area"), QStringLiteral("3"), QStringLiteral("4"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM4"), QT_TR_NOOP("Junon Area"), QStringLiteral("3"), QStringLiteral("5"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM5"), QT_TR_NOOP("Junon Area"), QStringLiteral("3"), QStringLiteral("6"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM6"), QT_TR_NOOP("Junon Area"), QStringLiteral("3"), QStringLiteral("7"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM7"), QT_TR_NOOP("Woodlands Area"), QStringLiteral("3"), QStringLiteral("8"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM8"), QT_TR_NOOP("Junon Area"), QStringLiteral("3"), QStringLiteral("9"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM9"), QT_TR_NOOP("Gongaga Area"), QStringLiteral("3"), QStringLiteral("10"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM10"), QT_TR_NOOP("Mideel Area"), QStringLiteral("3"), QStringLiteral("11"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM11"), QT_TR_NOOP("Mideel Area"), QStringLiteral("3"), QStringLiteral("12"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM12"), QT_TR_NOOP("Corel Area"), QStringLiteral("3"), QStringLiteral("13"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM13"), QT_TR_NOOP("Corel Area"), QStringLiteral("3"), QStringLiteral("14"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM14"), QT_TR_NOOP("Gold Saucer Area"), QStringLiteral("3"), QStringLiteral("15"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM15"), QT_TR_NOOP("Midgar Area"), QStringLiteral("3"), QStringLiteral("16"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM16"), QT_TR_NOOP("Gongaga Area"), QStringLiteral("3"), QStringLiteral("17"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM17"), QT_TR_NOOP("Cosmo Area"), QStringLiteral("3"), QStringLiteral("18"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM18"), QT_TR_NOOP("Nibel Area"), QStringLiteral("3"), QStringLiteral("19"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM19"), QT_TR_NOOP("Rocket Launch Pad Area"), QStringLiteral("3"), QStringLiteral("20"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM20"), QT_TR_NOOP("Nibel Area"), QStringLiteral("3"), QStringLiteral("21"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM21"), QT_TR_NOOP("North Corel Area"), QStringLiteral("3"), QStringLiteral("22"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM22"), QT_TR_NOOP("Wutai Area"), QStringLiteral("3"), QStringLiteral("23"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM23"), QT_TR_NOOP("Wutai Area"), QStringLiteral("3"), QStringLiteral("24"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM24"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("25"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM25"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("26"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM26"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("27"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM27"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("28"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM28"), QT_TR_NOOP("Round Island"), QStringLiteral("3"), QStringLiteral("29"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM29"), QT_TR_NOOP("Last Underwater Location"), QStringLiteral("3"), QStringLiteral("30"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM30"), QT_TR_NOOP("Underwater (Gelnika)"), QStringLiteral("3"), QStringLiteral("31"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM31"), QT_TR_NOOP("Last Worldmap Location"), QStringLiteral("3"), QStringLiteral("32"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM32"), QT_TR_NOOP("Last Worldmap Location"), QStringLiteral("3"), QStringLiteral("33"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM33"), QT_TR_NOOP("Last Worldmap Location"), QStringLiteral("3"), QStringLiteral("34"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM34"), QT_TR_NOOP("Last Worldmap Location"), QStringLiteral("3"), QStringLiteral("35"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM35"), QT_TR_NOOP("Start of Juion Ship Sequence"), QStringLiteral("3"), QStringLiteral("36"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM36"), QT_TR_NOOP("Almost at Costa del Sol"), QStringLiteral("3"), QStringLiteral("37"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM37"), QT_TR_NOOP("Junion -> Costa Del Sol"), QStringLiteral("3"), QStringLiteral("38"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM38"), QT_TR_NOOP("Costa del Sol -> Junion"), QStringLiteral("3"), QStringLiteral("39"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM39"), QT_TR_NOOP("Midgar Area"), QStringLiteral("3"), QStringLiteral("40"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM40"), QT_TR_NOOP("Junion Area (Highwind)"), QStringLiteral("3"), QStringLiteral("41"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM41"), QT_TR_NOOP("Junion Area (Underwater)"), QStringLiteral("3"), QStringLiteral("42"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM42"), QT_TR_NOOP("Nibel Area"), QStringLiteral("3"), QStringLiteral("43"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM43"), QT_TR_NOOP("Nibel Area"), QStringLiteral("3"), QStringLiteral("44"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM44"), QT_TR_NOOP("Last Worldmap Location"), QStringLiteral("3"), QStringLiteral("45"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM45"), QT_TR_NOOP("Nibel Area"), QStringLiteral("3"), QStringLiteral("46"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM46"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("47"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM47"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("48"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM48"), QT_TR_NOOP("Rocket Launch Pad Area"), QStringLiteral("3"), QStringLiteral("49"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM49"), QT_TR_NOOP("Last Worldmap Location"), QStringLiteral("3"), QStringLiteral("50"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM50"), QT_TR_NOOP("Midgar Area"), QStringLiteral("3"), QStringLiteral("51"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM51"), QT_TR_NOOP("Last Worldmap Location"), QStringLiteral("3"), QStringLiteral("52"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM52"), QT_TR_NOOP("Last Worldmap Location"), QStringLiteral("3"), QStringLiteral("53"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM53"), QT_TR_NOOP("Midgar Area"), QStringLiteral("3"), QStringLiteral("54"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM54"), QT_TR_NOOP("Cosmo Area"), QStringLiteral("3"), QStringLiteral("55"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM55"), QT_TR_NOOP("Last Underwater Location"), QStringLiteral("3"), QStringLiteral("56"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM56"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("57"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM57"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("58"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM58"), QT_TR_NOOP("Crater Area"), QStringLiteral("3"), QStringLiteral("59"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM59"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("60"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM60"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("61"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM61"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("62"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM62"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("63"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("WM63"), QT_TR_NOOP("Icicle Area"), QStringLiteral("3"), QStringLiteral("64"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            /************************Field Map Locations ******************/
            , {QStringLiteral("startmap"), QT_TR_NOOP("Debug Room [ja]"), QStringLiteral("1"), QStringLiteral("65"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("32")}
            , {QStringLiteral("fship_1"), QT_TR_NOOP("Highwind"), QStringLiteral("1"), QStringLiteral("66"), QStringLiteral("125"), QStringLiteral("64275"), QStringLiteral("27"), QStringLiteral("32")}
            , {QStringLiteral("fship_12"), QT_TR_NOOP("deck"), QStringLiteral("1"), QStringLiteral("67"), QStringLiteral("-149"), QStringLiteral("-1026"), QStringLiteral("23"), QStringLiteral("192")}
            , {QStringLiteral("fship_2"), QString(), QStringLiteral("1"), QStringLiteral("68"), QStringLiteral("-256"), QStringLiteral("-3635"), QStringLiteral("33"), QStringLiteral("32")}
            , {QStringLiteral("fship_22"), QString(), QStringLiteral("1"), QStringLiteral("69"), QStringLiteral("-256"), QStringLiteral("-3635"), QStringLiteral("33"), QStringLiteral("32")}

            , {QStringLiteral("fship_23"), QT_TR_NOOP("Highwind"), QStringLiteral("1"), QStringLiteral("70"), QStringLiteral("-256"), QStringLiteral("-3635"), QStringLiteral("33"), QStringLiteral("32")}
            , {QStringLiteral("fship_24"), QT_TR_NOOP("Bridge"), QStringLiteral("1"), QStringLiteral("71"), QStringLiteral("-44"), QStringLiteral("-2487"), QStringLiteral("101"), QStringLiteral("128")}
            , {QStringLiteral("fship_25"), QT_TR_NOOP("Highwind"), QStringLiteral("1"), QStringLiteral("72"), QStringLiteral("-3"), QStringLiteral("-2587"), QStringLiteral("99"), QStringLiteral("0")}
            , {QStringLiteral("fship_3"), QT_TR_NOOP("Highwind"), QStringLiteral("1"), QStringLiteral("73"), QStringLiteral("-168"), QStringLiteral("-247"), QStringLiteral("0"), QStringLiteral("192")}
            , {QStringLiteral("fship_4"), QT_TR_NOOP("Highwind"), QStringLiteral("1"), QStringLiteral("74"), QStringLiteral("213"), QStringLiteral("-324"), QStringLiteral("65"), QStringLiteral("0")}
            , {QStringLiteral("fship_42"), QT_TR_NOOP("Inside airship"), QStringLiteral("1"), QStringLiteral("75"), QStringLiteral("-652"), QStringLiteral("-540"), QStringLiteral("36"), QStringLiteral("0")}
            , {QStringLiteral("fship_5"), QT_TR_NOOP("Highwind"), QStringLiteral("1"), QStringLiteral("76"), QStringLiteral("-67"), QStringLiteral("-123"), QStringLiteral("11"), QStringLiteral("96")}
            , {QStringLiteral("hill"), QString(), QStringLiteral("1"), QStringLiteral("77"), QStringLiteral("43"), QStringLiteral("-285"), QStringLiteral("277"), QStringLiteral("96")}
            , {QStringLiteral("zz1"), QT_TR_NOOP("Old man's house"), QStringLiteral("1"), QStringLiteral("78"), QStringLiteral("-7"), QStringLiteral("157"), QStringLiteral("5"), QStringLiteral("128")}
            , {QStringLiteral("zz2"), QT_TR_NOOP("Weapon seller"), QStringLiteral("1"), QStringLiteral("79"), QStringLiteral("-70"), QStringLiteral("-124"), QStringLiteral("28"), QStringLiteral("128")}

            , {QStringLiteral("zz3"), QT_TR_NOOP("Chocobo Sage's house"), QStringLiteral("1"), QStringLiteral("80"), QStringLiteral("116"), QStringLiteral("-189"), QStringLiteral("2"), QStringLiteral("160")}
            , {QStringLiteral("zz4"), QT_TR_NOOP("???"), QStringLiteral("1"), QStringLiteral("81"), QStringLiteral("35"), QStringLiteral("-1306"), QStringLiteral("7"), QStringLiteral("128")}
            , {QStringLiteral("zz5"), QT_TR_NOOP("Materia Cave"), QStringLiteral("1"), QStringLiteral("82"), QStringLiteral("-625"), QStringLiteral("-1644"), QStringLiteral("8"), QStringLiteral("128")}
            , {QStringLiteral("zz6"), QT_TR_NOOP("Materia Cave"), QStringLiteral("1"), QStringLiteral("83"), QStringLiteral("-453"), QStringLiteral("-1334"), QStringLiteral("134"), QStringLiteral("128")}
            , {QStringLiteral("zz7"), QT_TR_NOOP("Materia Cave"), QStringLiteral("1"), QStringLiteral("84"), QStringLiteral("-610"), QStringLiteral("-1649"), QStringLiteral("16"), QStringLiteral("128")}
            , {QStringLiteral("zz8"), QT_TR_NOOP("Materia Cave"), QStringLiteral("1"), QStringLiteral("85"), QStringLiteral("-630"), QStringLiteral("-1585"), QStringLiteral("16"), QStringLiteral("128")}

            , {QStringLiteral("q_1"), QT_TR_NOOP("Hallway"), QStringLiteral("1"), QStringLiteral("88"), QStringLiteral("-395"), QStringLiteral("34"), QStringLiteral("13"), QStringLiteral("32")}
            , {QStringLiteral("q_2"), QT_TR_NOOP("Hallway"), QStringLiteral("1"), QStringLiteral("89"), QStringLiteral("89"), QStringLiteral("-73"), QStringLiteral("1"), QStringLiteral("128")}

            , {QStringLiteral("q_3"), QT_TR_NOOP("Research Room"), QStringLiteral("1"), QStringLiteral("90"), QStringLiteral("-239"), QStringLiteral("-392"), QStringLiteral("41"), QStringLiteral("128")}
            , {QStringLiteral("q_4"), QT_TR_NOOP("Cargo Room"), QStringLiteral("1"), QStringLiteral("91"), QStringLiteral("-856"), QStringLiteral("-707"), QStringLiteral("23"), QStringLiteral("128")}
            , {QStringLiteral("blackbg2"), QT_TR_NOOP("Debug Room [en]"), QStringLiteral("1"), QStringLiteral("94"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("32")}

            , {QStringLiteral("whitebg3"), QT_TR_NOOP("Mt. Nibel"), QStringLiteral("1"), QStringLiteral("115"), QStringLiteral("-61"), QStringLiteral("-726"), QStringLiteral("16"), QStringLiteral("0")}
            , {QStringLiteral("md1stin"), QT_TR_NOOP("Platform"), QStringLiteral("1"), QStringLiteral("116"), QStringLiteral("3655"), QStringLiteral("27432"), QStringLiteral("25"), QStringLiteral("96")}
            , {QStringLiteral("md1_1"), QT_TR_NOOP("Sector 1 Station"), QStringLiteral("1"), QStringLiteral("117"), QStringLiteral("1433"), QStringLiteral("386"), QStringLiteral("78"), QStringLiteral("32")}
            , {QStringLiteral("md1_2"), QT_TR_NOOP("Sector 1"), QStringLiteral("1"), QStringLiteral("118"), QStringLiteral("3568"), QStringLiteral("30777"), QStringLiteral("55"), QStringLiteral("32")}
            , {QStringLiteral("nrthmk"), QT_TR_NOOP("No.1 Reactor"), QStringLiteral("1"), QStringLiteral("119"), QStringLiteral("-12"), QStringLiteral("-2743"), QStringLiteral("0"), QStringLiteral("32")}

            , {QStringLiteral("nmkin_1"), QT_TR_NOOP("No.1 Reactor"), QStringLiteral("1"), QStringLiteral("120"), QStringLiteral("-736"), QStringLiteral("1612"), QStringLiteral("16"), QStringLiteral("32")}
            , {QStringLiteral("elevtr1"), QT_TR_NOOP("No.1 Reactor"), QStringLiteral("1"), QStringLiteral("121"), QStringLiteral("30"), QStringLiteral("40"), QStringLiteral("7"), QStringLiteral("32")}
            , {QStringLiteral("nmkin_2"), QT_TR_NOOP("No.1 Reactor"), QStringLiteral("1"), QStringLiteral("122"), QStringLiteral("-205"), QStringLiteral("235"), QStringLiteral("90"), QStringLiteral("32")}
            , {QStringLiteral("nmkin_3"), QT_TR_NOOP("No.1 Reactor"), QStringLiteral("1"), QStringLiteral("123"), QStringLiteral("-174"), QStringLiteral("1692"), QStringLiteral("35"), QStringLiteral("32")}
            , {QStringLiteral("nmkin_4"), QT_TR_NOOP("No.1 Reactor"), QStringLiteral("1"), QStringLiteral("124"), QStringLiteral("37"), QStringLiteral("1579"), QStringLiteral("36"), QStringLiteral("32")}
            , {QStringLiteral("nmkin_5"), QT_TR_NOOP("No.1 Reactor"), QStringLiteral("1"), QStringLiteral("125"), QStringLiteral("-85"), QStringLiteral("-1177"), QStringLiteral("1"), QStringLiteral("32")}
            , {QStringLiteral("southmk1"), QT_TR_NOOP("No.5 Reactor"), QStringLiteral("1"), QStringLiteral("126"), QStringLiteral("-4"), QStringLiteral("-1875"), QStringLiteral("7"), QStringLiteral("32")}
            , {QStringLiteral("smkin_1"), QT_TR_NOOP("No.5 Reactor"), QStringLiteral("1"), QStringLiteral("128"), QStringLiteral("-1501"), QStringLiteral("2546"), QStringLiteral("20"), QStringLiteral("32")}
            , {QStringLiteral("smkin_2"), QT_TR_NOOP("No.5 Reactor"), QStringLiteral("1"), QStringLiteral("129"), QStringLiteral("581"), QStringLiteral("2137"), QStringLiteral("157"), QStringLiteral("32")}

            , {QStringLiteral("smkin_3"), QT_TR_NOOP("No.5 Reactor"), QStringLiteral("1"), QStringLiteral("130"), QStringLiteral("-176"), QStringLiteral("1527"), QStringLiteral("19"), QStringLiteral("32")}
            , {QStringLiteral("smkin_4"), QT_TR_NOOP("No.5 Reactor"), QStringLiteral("1"), QStringLiteral("131"), QStringLiteral("34"), QStringLiteral("1617"), QStringLiteral("36"), QStringLiteral("32")}
            , {QStringLiteral("smkin_5"), QT_TR_NOOP("No.5 Reactor"), QStringLiteral("1"), QStringLiteral("132"), QStringLiteral("-89"), QStringLiteral("-961"), QStringLiteral("0"), QStringLiteral("32")}
            , {QStringLiteral("md8_1"), QT_TR_NOOP("Sector 8"), QStringLiteral("1"), QStringLiteral("133"), QStringLiteral("1270"), QStringLiteral("-5303"), QStringLiteral("11"), QStringLiteral("32")}
            , {QStringLiteral("md8_2"), QT_TR_NOOP("Sector 8"), QStringLiteral("1"), QStringLiteral("134"), QStringLiteral("-3967"), QStringLiteral("21109"), QStringLiteral("19"), QStringLiteral("32")}
            , {QStringLiteral("md8_3"), QT_TR_NOOP("Sector 8"), QStringLiteral("1"), QStringLiteral("135"), QStringLiteral("-4113"), QStringLiteral("18369"), QStringLiteral("189"), QStringLiteral("32")}
            , {QStringLiteral("md8brdg"), QT_TR_NOOP("Sector 8"), QStringLiteral("1"), QStringLiteral("137"), QStringLiteral("-422"), QStringLiteral("1111"), QStringLiteral("6"), QStringLiteral("32")}
            , {QStringLiteral("cargoin"), QT_TR_NOOP("Last Train From Midgar"), QStringLiteral("1"), QStringLiteral("138"), QStringLiteral("6"), QStringLiteral("42"), QStringLiteral("20"), QStringLiteral("32")}
            , {QStringLiteral("tin_1"), QT_TR_NOOP("Last Train From Midgar"), QStringLiteral("1"), QStringLiteral("139"), QStringLiteral("2"), QStringLiteral("537"), QStringLiteral("28"), QStringLiteral("32")}

            , {QStringLiteral("tin_2"), QT_TR_NOOP("Inside Train"), QStringLiteral("1"), QStringLiteral("140"), QStringLiteral("12"), QStringLiteral("579"), QStringLiteral("29"), QStringLiteral("32")}
            , {QStringLiteral("tin_3"), QT_TR_NOOP("Inside Train"), QStringLiteral("1"), QStringLiteral("141"), QStringLiteral("-60"), QStringLiteral("478"), QStringLiteral("31"), QStringLiteral("32")}
            , {QStringLiteral("tin_4"), QT_TR_NOOP("Inside Train"), QStringLiteral("1"), QStringLiteral("142"), QStringLiteral("82"), QStringLiteral("376"), QStringLiteral("27"), QStringLiteral("32")}
            , {QStringLiteral("mds7st1"), QT_TR_NOOP("Train Graveyard"), QStringLiteral("1"), QStringLiteral("144"), QStringLiteral("1981"), QStringLiteral("-3209"), QStringLiteral("71"), QStringLiteral("32")}
            , {QStringLiteral("mds7st2"), QT_TR_NOOP("Train Graveyard"), QStringLiteral("1"), QStringLiteral("145"), QStringLiteral("1403"), QStringLiteral("1151"), QStringLiteral("197"), QStringLiteral("32")}
            , {QStringLiteral("mds7st3"), QT_TR_NOOP("Sector 7 Station"), QStringLiteral("1"), QStringLiteral("146"), QStringLiteral("-2738"), QStringLiteral("3017"), QStringLiteral("9"), QStringLiteral("32")}
            , {QStringLiteral("mds7_w1"), QT_TR_NOOP("Sector 7 Weapon Shop"), QStringLiteral("1"), QStringLiteral("148"), QStringLiteral("14"), QStringLiteral("-4"), QStringLiteral("5"), QStringLiteral("32")}
            , {QStringLiteral("mds7_w2"), QT_TR_NOOP("Beginner's Hall"), QStringLiteral("1"), QStringLiteral("149"), QStringLiteral("-235"), QStringLiteral("9"), QStringLiteral("30"), QStringLiteral("32")}

            , {QStringLiteral("mds7_w3"), QT_TR_NOOP("Sector 7 Slums"), QStringLiteral("1"), QStringLiteral("150"), QStringLiteral("-5"), QStringLiteral("-184"), QStringLiteral("12"), QStringLiteral("32")}
            , {QStringLiteral("mds7"), QT_TR_NOOP("Sector 7 Slums"), QStringLiteral("1"), QStringLiteral("151"), QStringLiteral("1428"), QStringLiteral("-162"), QStringLiteral("109"), QStringLiteral("32")}
            , {QStringLiteral("mds7_im"), QT_TR_NOOP("Sector 7 Item Store"), QStringLiteral("1"), QStringLiteral("152"), QStringLiteral("172"), QStringLiteral("-5"), QStringLiteral("21"), QStringLiteral("32")}
            , {QStringLiteral("min71"), QT_TR_NOOP("Johnny's Home"), QStringLiteral("1"), QStringLiteral("153"), QStringLiteral("-15"), QStringLiteral("91"), QStringLiteral("55"), QStringLiteral("32")}
            , {QStringLiteral("mds7pb_1"), QT_TR_NOOP("7th Heaven"), QStringLiteral("1"), QStringLiteral("154"), QStringLiteral("67"), QStringLiteral("6"), QStringLiteral("26"), QStringLiteral("32")}
            , {QStringLiteral("mds7pb_2"), QT_TR_NOOP("AVALANCHE Hideout"), QStringLiteral("1"), QStringLiteral("155"), QStringLiteral("36"), QStringLiteral("69"), QStringLiteral("42"), QStringLiteral("32")}
            , {QStringLiteral("mds7plr1"), QT_TR_NOOP("Sector 7 Slums"), QStringLiteral("1"), QStringLiteral("156"), QStringLiteral("-351"), QStringLiteral("636"), QStringLiteral("231"), QStringLiteral("32")}
            , {QStringLiteral("pillar_1"), QT_TR_NOOP("Plate Support"), QStringLiteral("1"), QStringLiteral("158"), QStringLiteral("-204"), QStringLiteral("-960"), QStringLiteral("192"), QStringLiteral("32")}
            , {QStringLiteral("pillar_2"), QT_TR_NOOP("Plate Support"), QStringLiteral("1"), QStringLiteral("159"), QStringLiteral("193"), QStringLiteral("-1006"), QStringLiteral("100"), QStringLiteral("32")}

            , {QStringLiteral("pillar_3"), QT_TR_NOOP("Plate Support"), QStringLiteral("1"), QStringLiteral("160"), QStringLiteral("-461"), QStringLiteral("-274"), QStringLiteral("31"), QStringLiteral("32")}
            , {QStringLiteral("tunnel_1"), QT_TR_NOOP("Winding Tunnel"), QStringLiteral("1"), QStringLiteral("161"), QStringLiteral("25"), QStringLiteral("89"), QStringLiteral("145"), QStringLiteral("32")}
            , {QStringLiteral("tunnel_2"), QT_TR_NOOP("Winding Tunnel"), QStringLiteral("1"), QStringLiteral("162"), QStringLiteral("1"), QStringLiteral("555"), QStringLiteral("11"), QStringLiteral("32")}
            , {QStringLiteral("sbwy4_1"), QT_TR_NOOP("4th Street Plate Int."), QStringLiteral("1"), QStringLiteral("164"), QStringLiteral("6"), QStringLiteral("-728"), QStringLiteral("3"), QStringLiteral("128")}
            , {QStringLiteral("sbwy4_2"), QT_TR_NOOP("4th Street Plate Int."), QStringLiteral("1"), QStringLiteral("165"), QStringLiteral("0"), QStringLiteral("-46"), QStringLiteral("9"), QStringLiteral("32")}
            , {QStringLiteral("sbwy4_3"), QT_TR_NOOP("4th Street Plate Int."), QStringLiteral("1"), QStringLiteral("166"), QStringLiteral("-139"), QStringLiteral("574"), QStringLiteral("21"), QStringLiteral("32")}
            , {QStringLiteral("sbwy4_4"), QT_TR_NOOP("Lower Sector 4 Plate"), QStringLiteral("1"), QStringLiteral("167"), QStringLiteral("17"), QStringLiteral("1"), QStringLiteral("7"), QStringLiteral("32")}
            , {QStringLiteral("sbwy4_5"), QT_TR_NOOP("Lower Sector 4 Plate"), QStringLiteral("1"), QStringLiteral("168"), QStringLiteral("-88"), QStringLiteral("-72"), QStringLiteral("65"), QStringLiteral("32")}
            , {QStringLiteral("sbwy4_6"), QT_TR_NOOP("Lower Sector 4 Plate"), QStringLiteral("1"), QStringLiteral("169"), QStringLiteral("-114"), QStringLiteral("468"), QStringLiteral("11"), QStringLiteral("32")}

            , {QStringLiteral("mds5_5"), QT_TR_NOOP("Slum Outskirts"), QStringLiteral("1"), QStringLiteral("170"), QStringLiteral("867"), QStringLiteral("-2622"), QStringLiteral("15"), QStringLiteral("32")}
            , {QStringLiteral("mds5_4"), QT_TR_NOOP("Sector 5 Slum"), QStringLiteral("1"), QStringLiteral("171"), QStringLiteral("-28"), QStringLiteral("-587"), QStringLiteral("12"), QStringLiteral("68")}
            , {QStringLiteral("mds5_3"), QT_TR_NOOP("Sector 5 Slum"), QStringLiteral("1"), QStringLiteral("172"), QStringLiteral("159"), QStringLiteral("-134"), QStringLiteral("59"), QStringLiteral("32")}
            , {QStringLiteral("mds5_2"), QT_TR_NOOP("Sector 5 Slum"), QStringLiteral("1"), QStringLiteral("173"), QStringLiteral("-543"), QStringLiteral("158"), QStringLiteral("79"), QStringLiteral("128")}
            , {QStringLiteral("min51_1"), QT_TR_NOOP("House 1f."), QStringLiteral("1"), QStringLiteral("174"), QStringLiteral("-26"), QStringLiteral("24"), QStringLiteral("32"), QStringLiteral("32")}
            , {QStringLiteral("min51_2"), QT_TR_NOOP("House 2f."), QStringLiteral("1"), QStringLiteral("175"), QStringLiteral("-50"), QStringLiteral("76"), QStringLiteral("7"), QStringLiteral("32")}
            , {QStringLiteral("mds5_dk"), QT_TR_NOOP("Earthen Pipe"), QStringLiteral("1"), QStringLiteral("176"), QStringLiteral("39"), QStringLiteral("-277"), QStringLiteral("57"), QStringLiteral("32")}
            , {QStringLiteral("mds5_1"), QT_TR_NOOP("Sector 5 Slum"), QStringLiteral("1"), QStringLiteral("177"), QStringLiteral("-585"), QStringLiteral("166"), QStringLiteral("101"), QStringLiteral("32")}
            , {QStringLiteral("mds5_w"), QT_TR_NOOP("Weapon Store"), QStringLiteral("1"), QStringLiteral("178"), QStringLiteral("-22"), QStringLiteral("32"), QStringLiteral("10"), QStringLiteral("32")}
            , {QStringLiteral("mds5_i"), QT_TR_NOOP("Item Store"), QStringLiteral("1"), QStringLiteral("179"), QStringLiteral("102"), QStringLiteral("-9"), QStringLiteral("28"), QStringLiteral("32")}

            , {QStringLiteral("mds5_m"), QT_TR_NOOP("Materia store"), QStringLiteral("1"), QStringLiteral("180"), QStringLiteral("7"), QStringLiteral("-87"), QStringLiteral("21"), QStringLiteral("32")}
            , {QStringLiteral("church"), QT_TR_NOOP("Church"), QStringLiteral("1"), QStringLiteral("181"), QStringLiteral("-9"), QStringLiteral("-172"), QStringLiteral("52"), QStringLiteral("32")}
            , {QStringLiteral("chrin_1b"), QT_TR_NOOP("church in the slums"), QStringLiteral("1"), QStringLiteral("183"), QStringLiteral("-73"), QStringLiteral("400"), QStringLiteral("8"), QStringLiteral("32")}
            , {QStringLiteral("chrin_2"), QT_TR_NOOP("Inside the Church"), QStringLiteral("1"), QStringLiteral("184"), QStringLiteral("-374"), QStringLiteral("1130"), QStringLiteral("129"), QStringLiteral("32")}
            , {QStringLiteral("chrin_3b"), QT_TR_NOOP("Church Roof"), QStringLiteral("1"), QStringLiteral("186"), QStringLiteral("-10"), QStringLiteral("410"), QStringLiteral("33"), QStringLiteral("32")}
            , {QStringLiteral("eals_1"), QT_TR_NOOP("Aerith's House"), QStringLiteral("1"), QStringLiteral("187"), QStringLiteral("171"), QStringLiteral("-207"), QStringLiteral("138"), QStringLiteral("32")}
            , {QStringLiteral("ealin_1"), QT_TR_NOOP("Aerith's House"), QStringLiteral("1"), QStringLiteral("188"), QStringLiteral("-83"), QStringLiteral("-71"), QStringLiteral("41"), QStringLiteral("32")}

            , {QStringLiteral("ealin_2"), QT_TR_NOOP("Aerith's House"), QStringLiteral("1"), QStringLiteral("190"), QStringLiteral("63"), QStringLiteral("305"), QStringLiteral("25"), QStringLiteral("32")}
            , {QStringLiteral("mds6_1"), QT_TR_NOOP("Sector 6"), QStringLiteral("1"), QStringLiteral("191"), QStringLiteral("-1254"), QStringLiteral("-297"), QStringLiteral("41"), QStringLiteral("32")}
            , {QStringLiteral("mds6_2"), QT_TR_NOOP("Sector 6 park"), QStringLiteral("1"), QStringLiteral("192"), QStringLiteral("-264"), QStringLiteral("-55"), QStringLiteral("194"), QStringLiteral("32")}
            , {QStringLiteral("mds6_22"), QT_TR_NOOP("Sector 6 park"), QStringLiteral("1"), QStringLiteral("193"), QStringLiteral("-51"), QStringLiteral("-330"), QStringLiteral("18"), QStringLiteral("32")}
            , {QStringLiteral("mds6_3"), QT_TR_NOOP("Sector 6"), QStringLiteral("1"), QStringLiteral("194"), QStringLiteral("46"), QStringLiteral("220"), QStringLiteral("16"), QStringLiteral("32")}
            , {QStringLiteral("mrkt2"), QT_TR_NOOP("Wall Market"), QStringLiteral("1"), QStringLiteral("195"), QStringLiteral("462"), QStringLiteral("1080"), QStringLiteral("58"), QStringLiteral("32")}
            , {QStringLiteral("mkt_w"), QT_TR_NOOP("Weapon Store"), QStringLiteral("1"), QStringLiteral("196"), QStringLiteral("71"), QStringLiteral("-90"), QStringLiteral("29"), QStringLiteral("32")}
            , {QStringLiteral("mkt_mens"), QT_TR_NOOP("Men's Hall"), QStringLiteral("1"), QStringLiteral("197"), QStringLiteral("-17"), QStringLiteral("220"), QStringLiteral("139"), QStringLiteral("32")}
            , {QStringLiteral("mkt_ia"), QT_TR_NOOP("Item Store"), QStringLiteral("1"), QStringLiteral("198"), QStringLiteral("-21"), QStringLiteral("16"), QStringLiteral("6"), QStringLiteral("32")}
            , {QStringLiteral("mktinn"), QT_TR_NOOP("Inn"), QStringLiteral("1"), QStringLiteral("199"), QStringLiteral("-203"), QStringLiteral("0"), QStringLiteral("27"), QStringLiteral("32")}

            , {QStringLiteral("mkt_m"), QT_TR_NOOP("Materia Store"), QStringLiteral("1"), QStringLiteral("200"), QStringLiteral("174"), QStringLiteral("-108"), QStringLiteral("9"), QStringLiteral("32")}
            , {QStringLiteral("mkt_s1"), QT_TR_NOOP("Boutique"), QStringLiteral("1"), QStringLiteral("201"), QStringLiteral("130"), QStringLiteral("-25"), QStringLiteral("41"), QStringLiteral("32")}
            , {QStringLiteral("mkt_s2"), QT_TR_NOOP("Diner"), QStringLiteral("1"), QStringLiteral("202"), QStringLiteral("88"), QStringLiteral("-148"), QStringLiteral("23"), QStringLiteral("32")}
            , {QStringLiteral("mkt_s3"), QT_TR_NOOP("Pharmacy"), QStringLiteral("1"), QStringLiteral("203"), QStringLiteral("30"), QStringLiteral("-91"), QStringLiteral("5"), QStringLiteral("32")}
            , {QStringLiteral("mktpb"), QT_TR_NOOP("Bar"), QStringLiteral("1"), QStringLiteral("204"), QStringLiteral("66"), QStringLiteral("130"), QStringLiteral("43"), QStringLiteral("32")}
            , {QStringLiteral("mrkt1"), QT_TR_NOOP("Wall Market"), QStringLiteral("1"), QStringLiteral("205"), QStringLiteral("-124"), QStringLiteral("-2438"), QStringLiteral("93"), QStringLiteral("32")}
            , {QStringLiteral("colne_1"), QT_TR_NOOP("Corneo Hall"), QStringLiteral("1"), QStringLiteral("206"), QStringLiteral("53"), QStringLiteral("341"), QStringLiteral("35"), QStringLiteral("32")}
            , {QStringLiteral("colne_2"), QT_TR_NOOP("Corneo Hall,1f."), QStringLiteral("1"), QStringLiteral("207"), QStringLiteral("-169"), QStringLiteral("-54"), QStringLiteral("27"), QStringLiteral("32")}
            , {QStringLiteral("colne_3"), QT_TR_NOOP("Corneo Hall,2f."), QStringLiteral("1"), QStringLiteral("208"), QStringLiteral("-87"), QStringLiteral("-383"), QStringLiteral("76"), QStringLiteral("32")}
            , {QStringLiteral("colne_4"), QT_TR_NOOP("Torture Room"), QStringLiteral("1"), QStringLiteral("209"), QStringLiteral("556"), QStringLiteral("32"), QStringLiteral("15"), QStringLiteral("32")}

            , {QStringLiteral("colne_5"), QT_TR_NOOP("Corneo Hall,2f."), QStringLiteral("1"), QStringLiteral("210"), QStringLiteral("-8"), QStringLiteral("-264"), QStringLiteral("84"), QStringLiteral("32")}
            , {QStringLiteral("colne_6"), QT_TR_NOOP("Corneo Hall,2f."), QStringLiteral("1"), QStringLiteral("211"), QStringLiteral("145"), QStringLiteral("308"), QStringLiteral("43"), QStringLiteral("32")}
            , {QStringLiteral("colne_b1"), QT_TR_NOOP("Sewer"), QStringLiteral("1"), QStringLiteral("212"), QStringLiteral("304"), QStringLiteral("116"), QStringLiteral("14"), QStringLiteral("32")}
            , {QStringLiteral("colne_b3"), QT_TR_NOOP("Sewer"), QStringLiteral("1"), QStringLiteral("213"), QStringLiteral("66"), QStringLiteral("-208"), QStringLiteral("9"), QStringLiteral("32")}
            , {QStringLiteral("mrkt3"), QT_TR_NOOP("Honey Bee Inn"), QStringLiteral("1"), QStringLiteral("214"), QStringLiteral("12"), QStringLiteral("-107"), QStringLiteral("24"), QStringLiteral("32")}
            , {QStringLiteral("onna_2"), QT_TR_NOOP("Honey Bee Inn"), QStringLiteral("1"), QStringLiteral("216"), QStringLiteral("64"), QStringLiteral("114"), QStringLiteral("47"), QStringLiteral("32")}
            , {QStringLiteral("onna_4"), QT_TR_NOOP("Honey Bee Inn"), QStringLiteral("1"), QStringLiteral("218"), QStringLiteral("1"), QStringLiteral("-37"), QStringLiteral("11"), QStringLiteral("32")}

            , {QStringLiteral("onna_52"), QT_TR_NOOP("Honey Bee Inn"), QStringLiteral("1"), QStringLiteral("220"), QStringLiteral("-14"), QStringLiteral("-281"), QStringLiteral("36"), QStringLiteral("32")}
            , {QStringLiteral("mrkt4"), QT_TR_NOOP("Wall Market"), QStringLiteral("1"), QStringLiteral("222"), QStringLiteral("-69"), QStringLiteral("544"), QStringLiteral("4"), QStringLiteral("32")}
            , {QStringLiteral("wcrimb_1"), QT_TR_NOOP("Plate Section"), QStringLiteral("1"), QStringLiteral("223"), QStringLiteral("-9"), QStringLiteral("909"), QStringLiteral("111"), QStringLiteral("32")}
            , {QStringLiteral("wcrimb_2"), QT_TR_NOOP("Plate Section"), QStringLiteral("1"), QStringLiteral("224"), QStringLiteral("50"), QStringLiteral("1290"), QStringLiteral("70"), QStringLiteral("32")}
            , {QStringLiteral("md0"), QT_TR_NOOP("Sector 0"), QStringLiteral("1"), QStringLiteral("225"), QStringLiteral("-4431"), QStringLiteral("-13299"), QStringLiteral("16"), QStringLiteral("32")}
            , {QStringLiteral("roadend"), QT_TR_NOOP("Outside Plates"), QStringLiteral("1"), QStringLiteral("226"), QStringLiteral("-1312"), QStringLiteral("6"), QStringLiteral("44"), QStringLiteral("32")}
            , {QStringLiteral("sinbil_1"), QT_TR_NOOP("Shinra Bldg."), QStringLiteral("1"), QStringLiteral("227"), QStringLiteral("514"), QStringLiteral("-2458"), QStringLiteral("105"), QStringLiteral("32")}
            , {QStringLiteral("sinbil_2"), QT_TR_NOOP("Shinra Bldg."), QStringLiteral("1"), QStringLiteral("228"), QStringLiteral("4"), QStringLiteral("-708"), QStringLiteral("4"), QStringLiteral("32")}
            , {QStringLiteral("blinst_1"), QT_TR_NOOP("Shinra Bldg. Stairs"), QStringLiteral("1"), QStringLiteral("229"), QStringLiteral("-92"), QStringLiteral("152"), QStringLiteral("158"), QStringLiteral("32")}

            , {QStringLiteral("blinst_2"), QT_TR_NOOP("Shinra Bldg. Stairs"), QStringLiteral("1"), QStringLiteral("230"), QStringLiteral("-41"), QStringLiteral("75"), QStringLiteral("150"), QStringLiteral("32")}
            , {QStringLiteral("blinst_3"), QT_TR_NOOP("Shinra Bldg. Stairs"), QStringLiteral("1"), QStringLiteral("231"), QStringLiteral("-61"), QStringLiteral("62"), QStringLiteral("25"), QStringLiteral("32")}
            , {QStringLiteral("blinele"), QT_TR_NOOP("Elevator"), QStringLiteral("1"), QStringLiteral("232"), QStringLiteral("-6"), QStringLiteral("16"), QStringLiteral("7"), QStringLiteral("128")}
            , {QStringLiteral("eleout"), QT_TR_NOOP("Outside Elevator"), QStringLiteral("1"), QStringLiteral("233"), QStringLiteral("46"), QStringLiteral("-21"), QStringLiteral("18"), QStringLiteral("32")}
            , {QStringLiteral("blin1"), QT_TR_NOOP("Shinra Bldg. 1f. lobby"), QStringLiteral("1"), QStringLiteral("234"), QStringLiteral("849"), QStringLiteral("-110"), QStringLiteral("108"), QStringLiteral("32")}
            , {QStringLiteral("blin2"), QT_TR_NOOP("Shinra Bldg. 2f. Lobby"), QStringLiteral("1"), QStringLiteral("235"), QStringLiteral("-916"), QStringLiteral("-60"), QStringLiteral("46"), QStringLiteral("32")}
            , {QStringLiteral("blin2_i"), QT_TR_NOOP("Shinra Bldg. 2f. Shop"), QStringLiteral("1"), QStringLiteral("236"), QStringLiteral("112"), QStringLiteral("-531"), QStringLiteral("59"), QStringLiteral("32")}
            , {QStringLiteral("blin3_1"), QT_TR_NOOP("Shinra Bldg. 3f. Lobby"), QStringLiteral("1"), QStringLiteral("237"), QStringLiteral("-1429"), QStringLiteral("32"), QStringLiteral("61"), QStringLiteral("32")}
            , {QStringLiteral("blin59"), QT_TR_NOOP("Shinra Bldg. 59f."), QStringLiteral("1"), QStringLiteral("238"), QStringLiteral("-415"), QStringLiteral("-544"), QStringLiteral("85"), QStringLiteral("32")}
            , {QStringLiteral("blin60_1"), QT_TR_NOOP("Shinra Bldg. 60f."), QStringLiteral("1"), QStringLiteral("239"), QStringLiteral("-139"), QStringLiteral("-693"), QStringLiteral("266"), QStringLiteral("32")}

            , {QStringLiteral("blin60_2"), QT_TR_NOOP("Shinra Bldg. 60f."), QStringLiteral("1"), QStringLiteral("240"), QStringLiteral("-132"), QStringLiteral("-935"), QStringLiteral("12"), QStringLiteral("104")}
            , {QStringLiteral("blin61"), QT_TR_NOOP("Shinra Bldg. 61f."), QStringLiteral("1"), QStringLiteral("241"), QStringLiteral("733"), QStringLiteral("-459"), QStringLiteral("296"), QStringLiteral("32")}
            , {QStringLiteral("blin62_1"), QT_TR_NOOP("Shinra Bldg. 62f."), QStringLiteral("1"), QStringLiteral("242"), QStringLiteral("611"), QStringLiteral("-387"), QStringLiteral("231"), QStringLiteral("32")}
            , {QStringLiteral("blin62_2"), QT_TR_NOOP("Shinra Bldg. 62f."), QStringLiteral("1"), QStringLiteral("243"), QStringLiteral("120"), QStringLiteral("-426"), QStringLiteral("74"), QStringLiteral("32")}
            , {QStringLiteral("blin62_3"), QT_TR_NOOP("Shinra Bldg. 62f."), QStringLiteral("1"), QStringLiteral("244"), QStringLiteral("-123"), QStringLiteral("607"), QStringLiteral("33"), QStringLiteral("32")}
            , {QStringLiteral("blin63_1"), QT_TR_NOOP("Shinra Bldg. 63f."), QStringLiteral("1"), QStringLiteral("245"), QStringLiteral("905"), QStringLiteral("-694"), QStringLiteral("377"), QStringLiteral("32")}
            , {QStringLiteral("blin64"), QT_TR_NOOP("Shinra Bldg. 64f."), QStringLiteral("1"), QStringLiteral("247"), QStringLiteral("-1150"), QStringLiteral("-283"), QStringLiteral("245"), QStringLiteral("32")}
            , {QStringLiteral("blin65_1"), QT_TR_NOOP("Shinra Bldg. 65f."), QStringLiteral("1"), QStringLiteral("248"), QStringLiteral("581"), QStringLiteral("-462"), QStringLiteral("131"), QStringLiteral("32")}
            , {QStringLiteral("blin65_2"), QT_TR_NOOP("Shinra Bldg. 65f."), QStringLiteral("1"), QStringLiteral("249"), QStringLiteral("31"), QStringLiteral("-368"), QStringLiteral("86"), QStringLiteral("32")}

            , {QStringLiteral("blin66_1"), QT_TR_NOOP("Shinra Bldg.66f."), QStringLiteral("1"), QStringLiteral("250"), QStringLiteral("567"), QStringLiteral("-349"), QStringLiteral("67"), QStringLiteral("32")}
            , {QStringLiteral("blin66_3"), QT_TR_NOOP("Shinra Bldg.66f."), QStringLiteral("1"), QStringLiteral("252"), QStringLiteral("86"), QStringLiteral("123"), QStringLiteral("18"), QStringLiteral("32")}
            , {QStringLiteral("blin66_4"), QT_TR_NOOP("Shinra Bldg.66f."), QStringLiteral("1"), QStringLiteral("253"), QStringLiteral("452"), QStringLiteral("-78"), QStringLiteral("4"), QStringLiteral("32")}
            , {QStringLiteral("blin67_1"), QT_TR_NOOP("Shinra Bldg.67f."), QStringLiteral("1"), QStringLiteral("256"), QStringLiteral("-110"), QStringLiteral("797"), QStringLiteral("283"), QStringLiteral("32")}
            , {QStringLiteral("blin671b"), QT_TR_NOOP("Shinra Bldg.67f."), QStringLiteral("1"), QStringLiteral("257"), QStringLiteral("-92"), QStringLiteral("732"), QStringLiteral("283"), QStringLiteral("32")}
            , {QStringLiteral("blin67_2"), QT_TR_NOOP("Shinra Bldg.67f."), QStringLiteral("1"), QStringLiteral("258"), QStringLiteral("778"), QStringLiteral("703"), QStringLiteral("7"), QStringLiteral("32")}
            , {QStringLiteral("blin67_3"), QT_TR_NOOP("Shinra Bldg.67f."), QStringLiteral("1"), QStringLiteral("259"), QStringLiteral("-790"), QStringLiteral("-306"), QStringLiteral("242"), QStringLiteral("32")}

            , {QStringLiteral("blin673b"), QT_TR_NOOP("Shinra Bldg.67f."), QStringLiteral("1"), QStringLiteral("260"), QStringLiteral("-741"), QStringLiteral("-377"), QStringLiteral("238"), QStringLiteral("32")}
            , {QStringLiteral("blin68_1"), QT_TR_NOOP("Shinra Bldg.68f."), QStringLiteral("1"), QStringLiteral("262"), QStringLiteral("-571"), QStringLiteral("440"), QStringLiteral("109"), QStringLiteral("32")}
            , {QStringLiteral("blin68_2"), QT_TR_NOOP("Shinra Bldg.68f."), QStringLiteral("1"), QStringLiteral("263"), QStringLiteral("-994"), QStringLiteral("-45"), QStringLiteral("55"), QStringLiteral("104")}
            , {QStringLiteral("blin69_1"), QT_TR_NOOP("Shinra Bldg. 69f."), QStringLiteral("1"), QStringLiteral("264"), QStringLiteral("150"), QStringLiteral("-434"), QStringLiteral("226"), QStringLiteral("32")}
            , {QStringLiteral("blin70_3"), QT_TR_NOOP("Shinra Bldg. 70f."), QStringLiteral("1"), QStringLiteral("268"), QStringLiteral("134"), QStringLiteral("1617"), QStringLiteral("16"), QStringLiteral("32")}

            , {QStringLiteral("niv_w"), QT_TR_NOOP("Nibelheim Item Store"), QStringLiteral("1"), QStringLiteral("270"), QStringLiteral("380"), QStringLiteral("-365"), QStringLiteral("9"), QStringLiteral("32")}
            , {QStringLiteral("nvmin1_1"), QT_TR_NOOP("Nibelheim House"), QStringLiteral("1"), QStringLiteral("271"), QStringLiteral("121"), QStringLiteral("92"), QStringLiteral("62"), QStringLiteral("32")}
            , {QStringLiteral("nvmin1_2"), QT_TR_NOOP("Nibelheim House"), QStringLiteral("1"), QStringLiteral("272"), QStringLiteral("-64"), QStringLiteral("27"), QStringLiteral("14"), QStringLiteral("104")}
            , {QStringLiteral("nivinn_1"), QT_TR_NOOP("Nibelheim Inn"), QStringLiteral("1"), QStringLiteral("273"), QStringLiteral("22"), QStringLiteral("-413"), QStringLiteral("34"), QStringLiteral("32")}
            , {QStringLiteral("nivinn_2"), QT_TR_NOOP("Nibelheim Inn"), QStringLiteral("1"), QStringLiteral("274"), QStringLiteral("126"), QStringLiteral("158"), QStringLiteral("14"), QStringLiteral("32")}
            , {QStringLiteral("niv_cl"), QT_TR_NOOP("Cloud's House"), QStringLiteral("1"), QStringLiteral("276"), QStringLiteral("-238"), QStringLiteral("48"), QStringLiteral("9"), QStringLiteral("32")}

            , {QStringLiteral("nivgate"), QString(), QStringLiteral("1"), QStringLiteral("279"), QStringLiteral("12"), QStringLiteral("-1274"), QStringLiteral("0"), QStringLiteral("120")}

            , {QStringLiteral("nivgate2"), QString(), QStringLiteral("1"), QStringLiteral("280"), QStringLiteral("-2"), QStringLiteral("-1345"), QStringLiteral("0"), QStringLiteral("120")}

            , {QStringLiteral("nivl"), QT_TR_NOOP("Nibelheim"), QStringLiteral("1"), QStringLiteral("282"), QStringLiteral("591"), QStringLiteral("-73"), QStringLiteral("35"), QStringLiteral("32")}
            , {QStringLiteral("nivl_3"), QT_TR_NOOP("Nibelheim"), QStringLiteral("1"), QStringLiteral("284"), QStringLiteral("161"), QStringLiteral("-480"), QStringLiteral("7"), QStringLiteral("28")}
            , {QStringLiteral("niv_ti1"), QT_TR_NOOP("Tifa's House"), QStringLiteral("1"), QStringLiteral("286"), QStringLiteral("-214"), QStringLiteral("23"), QStringLiteral("24"), QStringLiteral("32")}
            , {QStringLiteral("niv_ti2"), QT_TR_NOOP("Tifa's House"), QStringLiteral("1"), QStringLiteral("287"), QStringLiteral("134"), QStringLiteral("-255"), QStringLiteral("46"), QStringLiteral("32")}

            , {QStringLiteral("nivl_b1"), QT_TR_NOOP("Nibelheim"), QStringLiteral("1"), QStringLiteral("290"), QStringLiteral("-130"), QStringLiteral("1144"), QStringLiteral("66"), QStringLiteral("32")}
            , {QStringLiteral("nivl_b12"), QT_TR_NOOP("Nibelheim"), QStringLiteral("1"), QStringLiteral("291"), QStringLiteral("-0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("nivl_b22"), QT_TR_NOOP("Nibelheim"), QStringLiteral("1"), QStringLiteral("293"), QStringLiteral("302"), QStringLiteral("-43"), QStringLiteral("19"), QStringLiteral("117")}

            , {QStringLiteral("nivl_e3"), QT_TR_NOOP("Nibelheim"), QStringLiteral("1"), QStringLiteral("296"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0")}
            , {QStringLiteral("sinin1_1"), QT_TR_NOOP("Mansion, 1f."), QStringLiteral("1"), QStringLiteral("297"), QStringLiteral("0"), QStringLiteral("255"), QStringLiteral("109"), QStringLiteral("32")}
            , {QStringLiteral("sinin1_2"), QT_TR_NOOP("Mansion, 1f."), QStringLiteral("1"), QStringLiteral("298"), QStringLiteral("-873"), QStringLiteral("507"), QStringLiteral("92"), QStringLiteral("32")}
            , {QStringLiteral("sinin2_1"), QT_TR_NOOP("Mansion, 2f."), QStringLiteral("1"), QStringLiteral("299"), QStringLiteral("-646"), QStringLiteral("749"), QStringLiteral("157"), QStringLiteral("32")}

            , {QStringLiteral("sinin2_2"), QT_TR_NOOP("Mansion, 2f."), QStringLiteral("1"), QStringLiteral("300"), QStringLiteral("525"), QStringLiteral("788"), QStringLiteral("150"), QStringLiteral("32")}
            , {QStringLiteral("sinin3"), QT_TR_NOOP("Mansion, Hidden Steps"), QStringLiteral("1"), QStringLiteral("301"), QStringLiteral("-123"), QStringLiteral("130"), QStringLiteral("174"), QStringLiteral("32")}
            , {QStringLiteral("sininb1"), QT_TR_NOOP("Mansion, Basement"), QStringLiteral("1"), QStringLiteral("302"), QStringLiteral("-104"), QStringLiteral("-253"), QStringLiteral("24"), QStringLiteral("32")}
            , {QStringLiteral("sininb2"), QT_TR_NOOP("Mansion, Basement"), QStringLiteral("1"), QStringLiteral("303"), QStringLiteral("-198"), QStringLiteral("-709"), QStringLiteral("17"), QStringLiteral("32")}
            , {QStringLiteral("sininb31"), QT_TR_NOOP("Mansion, Basement"), QStringLiteral("1"), QStringLiteral("304"), QStringLiteral("-141"), QStringLiteral("-125"), QStringLiteral("140"), QStringLiteral("32")}
            , {QStringLiteral("sininb32"), QT_TR_NOOP("Mansion, Basement"), QStringLiteral("1"), QStringLiteral("305"), QStringLiteral("-262"), QStringLiteral("-212"), QStringLiteral("46"), QStringLiteral("64")}
            , {QStringLiteral("sininb41"), QT_TR_NOOP("Mansion, Basement"), QStringLiteral("1"), QStringLiteral("307"), QStringLiteral("307"), QStringLiteral("501"), QStringLiteral("13"), QStringLiteral("32")}
            , {QStringLiteral("sininb51"), QT_TR_NOOP("Mansion, Basement"), QStringLiteral("1"), QStringLiteral("309"), QStringLiteral("80"), QStringLiteral("970"), QStringLiteral("94"), QStringLiteral("32")}

            , {QStringLiteral("mtnvl2"), QT_TR_NOOP("Mt. Nibel"), QStringLiteral("1"), QStringLiteral("311"), QStringLiteral("4623"), QStringLiteral("-2060"), QStringLiteral("193"), QStringLiteral("32")}
            , {QStringLiteral("mtnvl3"), QT_TR_NOOP("Mt. Nibel"), QStringLiteral("1"), QStringLiteral("312"), QStringLiteral("4073"), QStringLiteral("-1662"), QStringLiteral("29"), QStringLiteral("32")}
            , {QStringLiteral("mtnvl4"), QT_TR_NOOP("Mt. Nibel"), QStringLiteral("1"), QStringLiteral("313"), QStringLiteral("2907"), QStringLiteral("-392"), QStringLiteral("83"), QStringLiteral("32")}
            , {QStringLiteral("mtnvl6"), QT_TR_NOOP("Nibel Reactor"), QStringLiteral("1"), QStringLiteral("315"), QStringLiteral("-683"), QStringLiteral("-794"), QStringLiteral("16"), QStringLiteral("32")}
            , {QStringLiteral("nvdun1"), QT_TR_NOOP("Mt. Nibel"), QStringLiteral("1"), QStringLiteral("317"), QStringLiteral("667"), QStringLiteral("-501"), QStringLiteral("261"), QStringLiteral("32")}
            , {QStringLiteral("nvdun2"), QT_TR_NOOP("Mt. Nibel Cave"), QStringLiteral("1"), QStringLiteral("318"), QStringLiteral("237"), QStringLiteral("-320"), QStringLiteral("16"), QStringLiteral("32")}
            , {QStringLiteral("nvdun3"), QT_TR_NOOP("Mt. Nibel Cave"), QStringLiteral("1"), QStringLiteral("319"), QStringLiteral("-251"), QStringLiteral("942"), QStringLiteral("158"), QStringLiteral("0")}

            , {QStringLiteral("nvdun4"), QT_TR_NOOP("Mt. Nibel Cave"), QStringLiteral("1"), QStringLiteral("321"), QStringLiteral("446"), QStringLiteral("-271"), QStringLiteral("1"), QStringLiteral("0")}
            , {QStringLiteral("nvmkin1"), QT_TR_NOOP("Nibel Reactor(Int.)"), QStringLiteral("1"), QStringLiteral("322"), QStringLiteral("-9"), QStringLiteral("362"), QStringLiteral("23"), QStringLiteral("32")}
            , {QStringLiteral("nvmkin21"), QT_TR_NOOP("Nibel Reactor(Int.)"), QStringLiteral("1"), QStringLiteral("323"), QStringLiteral("3"), QStringLiteral("-114"), QStringLiteral("11"), QStringLiteral("32")}
            , {QStringLiteral("elm_wa"), QT_TR_NOOP("Weapon Store"), QStringLiteral("1"), QStringLiteral("328"), QStringLiteral("38"), QStringLiteral("114"), QStringLiteral("15"), QStringLiteral("32")}
            , {QStringLiteral("elm_i"), QT_TR_NOOP("Item Store"), QStringLiteral("1"), QStringLiteral("329"), QStringLiteral("40"), QStringLiteral("58"), QStringLiteral("4"), QStringLiteral("32")}

            , {QStringLiteral("elmpb"), QT_TR_NOOP("Bar"), QStringLiteral("1"), QStringLiteral("330"), QStringLiteral("-131"), QStringLiteral("-50"), QStringLiteral("13"), QStringLiteral("32")}
            , {QStringLiteral("elminn_1"), QT_TR_NOOP("Inn: 1f"), QStringLiteral("1"), QStringLiteral("331"), QStringLiteral("141"), QStringLiteral("-239"), QStringLiteral("14"), QStringLiteral("32")}
            , {QStringLiteral("elminn_2"), QT_TR_NOOP("Inn: 2f"), QStringLiteral("1"), QStringLiteral("332"), QStringLiteral("164"), QStringLiteral("125"), QStringLiteral("8"), QStringLiteral("32")}
            , {QStringLiteral("elmin1_1"), QT_TR_NOOP("House: 1f"), QStringLiteral("1"), QStringLiteral("333"), QStringLiteral("190"), QStringLiteral("-197"), QStringLiteral("34"), QStringLiteral("32")}
            , {QStringLiteral("elmin1_2"), QT_TR_NOOP("House: 2f"), QStringLiteral("1"), QStringLiteral("334"), QStringLiteral("332"), QStringLiteral("-58"), QStringLiteral("11"), QStringLiteral("32")}
            , {QStringLiteral("elm"), QT_TR_NOOP("Kalm"), QStringLiteral("1"), QStringLiteral("335"), QStringLiteral("-293"), QStringLiteral("-389"), QStringLiteral("112"), QStringLiteral("32")}
            , {QStringLiteral("elmin2_1"), QT_TR_NOOP("House: 1f"), QStringLiteral("1"), QStringLiteral("336"), QStringLiteral("-85"), QStringLiteral("-21"), QStringLiteral("14"), QStringLiteral("32")}
            , {QStringLiteral("elmin2_2"), QT_TR_NOOP("House: 2f"), QStringLiteral("1"), QStringLiteral("337"), QStringLiteral("114"), QStringLiteral("70"), QStringLiteral("14"), QStringLiteral("32")}
            , {QStringLiteral("elmin3_1"), QT_TR_NOOP("House: 1f"), QStringLiteral("1"), QStringLiteral("338"), QStringLiteral("174"), QStringLiteral("-217"), QStringLiteral("26"), QStringLiteral("32")}
            , {QStringLiteral("elmin3_2"), QT_TR_NOOP("House: 2f"), QStringLiteral("1"), QStringLiteral("339"), QStringLiteral("334"), QStringLiteral("-151"), QStringLiteral("34"), QStringLiteral("32")}

            , {QStringLiteral("elmtow"), QT_TR_NOOP("Rear Tower (Pagoda)"), QStringLiteral("1"), QStringLiteral("340"), QStringLiteral("61"), QStringLiteral("-55"), QStringLiteral("8"), QStringLiteral("32")}
            , {QStringLiteral("elmin4_1"), QT_TR_NOOP("House: 1f"), QStringLiteral("1"), QStringLiteral("341"), QStringLiteral("33"), QStringLiteral("108"), QStringLiteral("27"), QStringLiteral("32")}
            , {QStringLiteral("elmin4_2"), QT_TR_NOOP("House: 2f"), QStringLiteral("1"), QStringLiteral("342"), QStringLiteral("73"), QStringLiteral("310"), QStringLiteral("26"), QStringLiteral("32")}
            , {QStringLiteral("farm"), QT_TR_NOOP("Chocobo farm"), QStringLiteral("1"), QStringLiteral("343"), QStringLiteral("-207"), QStringLiteral("-126"), QStringLiteral("13"), QStringLiteral("32")}
            , {QStringLiteral("frmin"), QT_TR_NOOP("Chocobo farm"), QStringLiteral("1"), QStringLiteral("344"), QStringLiteral("65"), QStringLiteral("-58"), QStringLiteral("62"), QStringLiteral("32")}
            , {QStringLiteral("frcyo"), QT_TR_NOOP("Chocobo Ranch"), QStringLiteral("1"), QStringLiteral("345"), QStringLiteral("-134"), QStringLiteral("-150"), QStringLiteral("73"), QStringLiteral("32")}
            , {QStringLiteral("sichi"), QT_TR_NOOP("Marshes"), QStringLiteral("1"), QStringLiteral("348"), QStringLiteral("74"), QStringLiteral("-32"), QStringLiteral("40"), QStringLiteral("32")}
            , {QStringLiteral("psdun_1"), QT_TR_NOOP("Mythril Mine"), QStringLiteral("1"), QStringLiteral("349"), QStringLiteral("693"), QStringLiteral("56"), QStringLiteral("19"), QStringLiteral("32")}

            , {QStringLiteral("psdun_2"), QT_TR_NOOP("Mythril Mine"), QStringLiteral("1"), QStringLiteral("350"), QStringLiteral("146"), QStringLiteral("367"), QStringLiteral("90"), QStringLiteral("32")}
            , {QStringLiteral("psdun_3"), QT_TR_NOOP("Mythril Mine"), QStringLiteral("1"), QStringLiteral("351"), QStringLiteral("-203"), QStringLiteral("-304"), QStringLiteral("313"), QStringLiteral("32")}
            , {QStringLiteral("psdun_4"), QT_TR_NOOP("Mythril Mine"), QStringLiteral("1"), QStringLiteral("352"), QStringLiteral("-8"), QStringLiteral("-295"), QStringLiteral("12"), QStringLiteral("32")}
            , {QStringLiteral("condor1"), QT_TR_NOOP("Base of Fort Condor"), QStringLiteral("1"), QStringLiteral("353"), QStringLiteral("11"), QStringLiteral("-545"), QStringLiteral("9"), QStringLiteral("32")}
            , {QStringLiteral("condor2"), QT_TR_NOOP("Entrance to Fort Condor"), QStringLiteral("1"), QStringLiteral("354"), QStringLiteral("9"), QStringLiteral("44"), QStringLiteral("9"), QStringLiteral("32")}
            , {QStringLiteral("convil_1"), QT_TR_NOOP("Fort Condor"), QStringLiteral("1"), QStringLiteral("355"), QStringLiteral("1118"), QStringLiteral("391"), QStringLiteral("12"), QStringLiteral("32")}
            , {QStringLiteral("convil_2"), QT_TR_NOOP("Watch Room"), QStringLiteral("1"), QStringLiteral("356"), QStringLiteral("-52"), QStringLiteral("-13"), QStringLiteral("10"), QStringLiteral("32")}
            , {QStringLiteral("convil_4"), QT_TR_NOOP("top of the mountian"), QStringLiteral("1"), QStringLiteral("358"), QStringLiteral("662"), QStringLiteral("-545"), QStringLiteral("21"), QStringLiteral("96")}

            , {QStringLiteral("junonr1"), QT_TR_NOOP("Upper Junon"), QStringLiteral("1"), QStringLiteral("360"), QStringLiteral("1377"), QStringLiteral("-783"), QStringLiteral("106"), QStringLiteral("32")}
            , {QStringLiteral("junonr2"), QT_TR_NOOP("Upper Junon"), QStringLiteral("1"), QStringLiteral("361"), QStringLiteral("5934"), QStringLiteral("-4665"), QStringLiteral("47"), QStringLiteral("32")}
            , {QStringLiteral("jun_wa"), QT_TR_NOOP("Weapon Store"), QStringLiteral("1"), QStringLiteral("364"), QStringLiteral("245"), QStringLiteral("-314"), QStringLiteral("15"), QStringLiteral("32")}
            , {QStringLiteral("jun_i1"), QT_TR_NOOP("Item Store"), QStringLiteral("1"), QStringLiteral("365"), QStringLiteral("-3"), QStringLiteral("-84"), QStringLiteral("2"), QStringLiteral("32")}
            , {QStringLiteral("jun_m"), QT_TR_NOOP("Materia Store"), QStringLiteral("1"), QStringLiteral("366"), QStringLiteral("32"), QStringLiteral("-85"), QStringLiteral("6"), QStringLiteral("32")}
            , {QStringLiteral("junmin1"), QT_TR_NOOP("Barracks"), QStringLiteral("1"), QStringLiteral("367"), QStringLiteral("88"), QStringLiteral("-149"), QStringLiteral("6"), QStringLiteral("32")}
            , {QStringLiteral("junmin2"), QT_TR_NOOP("Barracks"), QStringLiteral("1"), QStringLiteral("368"), QStringLiteral("266"), QStringLiteral("-97"), QStringLiteral("11"), QStringLiteral("32")}
            , {QStringLiteral("junmin3"), QT_TR_NOOP("Barracks"), QStringLiteral("1"), QStringLiteral("369"), QStringLiteral("302"), QStringLiteral("-53"), QStringLiteral("49"), QStringLiteral("32")}

            , {QStringLiteral("junonl1"), QT_TR_NOOP("Lower Junon"), QStringLiteral("1"), QStringLiteral("370"), QStringLiteral("-1680"), QStringLiteral("-910"), QStringLiteral("131"), QStringLiteral("32")}
            , {QStringLiteral("junonl2"), QT_TR_NOOP("Lower Junon"), QStringLiteral("1"), QStringLiteral("371"), QStringLiteral("2454"), QStringLiteral("-863"), QStringLiteral("97"), QStringLiteral("32")}
            , {QStringLiteral("junonl3"), QT_TR_NOOP("Weapon Store"), QStringLiteral("1"), QStringLiteral("373"), QStringLiteral("10"), QStringLiteral("-52"), QStringLiteral("29"), QStringLiteral("32")}
            , {QStringLiteral("jun_a"), QT_TR_NOOP("Item Store"), QStringLiteral("1"), QStringLiteral("374"), QStringLiteral("-2"), QStringLiteral("-186"), QStringLiteral("23"), QStringLiteral("32")}
            , {QStringLiteral("jun_i2"), QT_TR_NOOP("Materia Store"), QStringLiteral("1"), QStringLiteral("375"), QStringLiteral("10"), QStringLiteral("-348"), QStringLiteral("46"), QStringLiteral("32")}
            , {QStringLiteral("juninn"), QT_TR_NOOP("Junon Inn"), QStringLiteral("1"), QStringLiteral("376"), QStringLiteral("45"), QStringLiteral("197"), QStringLiteral("21"), QStringLiteral("32")}
            , {QStringLiteral("junpb_1"), QT_TR_NOOP("Shinra Member's Bar"), QStringLiteral("1"), QStringLiteral("377"), QStringLiteral("82"), QStringLiteral("-241"), QStringLiteral("18"), QStringLiteral("32")}
            , {QStringLiteral("junpb_2"), QT_TR_NOOP("Respectable Inn"), QStringLiteral("1"), QStringLiteral("378"), QStringLiteral("-135"), QStringLiteral("107"), QStringLiteral("34"), QStringLiteral("32")}
            , {QStringLiteral("junpb_3"), QT_TR_NOOP("Bar"), QStringLiteral("1"), QStringLiteral("379"), QStringLiteral("17"), QStringLiteral("-156"), QStringLiteral("39"), QStringLiteral("32")}

            , {QStringLiteral("junmin4"), QT_TR_NOOP("Barracks"), QStringLiteral("1"), QStringLiteral("380"), QStringLiteral("182"), QStringLiteral("-170"), QStringLiteral("2"), QStringLiteral("32")}
            , {QStringLiteral("junmin5"), QT_TR_NOOP("Barracks"), QStringLiteral("1"), QStringLiteral("381"), QStringLiteral("74"), QStringLiteral("-101"), QStringLiteral("41"), QStringLiteral("32")}
            , {QStringLiteral("jundoc1a"), QT_TR_NOOP("Junon Dock"), QStringLiteral("1"), QStringLiteral("382"), QStringLiteral("-85"), QStringLiteral("1237"), QStringLiteral("10"), QStringLiteral("32")}
            , {QStringLiteral("jundoc1b"), QT_TR_NOOP("Junon Dock"), QStringLiteral("1"), QStringLiteral("383"), QStringLiteral("-503"), QStringLiteral("712"), QStringLiteral("18"), QStringLiteral("108")}
            , {QStringLiteral("junair"), QT_TR_NOOP("Airport"), QStringLiteral("1"), QStringLiteral("384"), QStringLiteral("13770"), QStringLiteral("14517"), QStringLiteral("108"), QStringLiteral("32")}
            , {QStringLiteral("junair2"), QT_TR_NOOP("Airport"), QStringLiteral("1"), QStringLiteral("385"), QStringLiteral("-4077"), QStringLiteral("-1403"), QStringLiteral("93"), QStringLiteral("32")}
            , {QStringLiteral("junin1"), QT_TR_NOOP("Junon Airport Path"), QStringLiteral("1"), QStringLiteral("386"), QStringLiteral("-634"), QStringLiteral("-333"), QStringLiteral("31"), QStringLiteral("32")}
            , {QStringLiteral("junin1a"), QT_TR_NOOP("Locker Room"), QStringLiteral("1"), QStringLiteral("387"), QStringLiteral("-1554"), QStringLiteral("-786"), QStringLiteral("22"), QStringLiteral("32")}
            , {QStringLiteral("junele1"), QT_TR_NOOP("Elevator"), QStringLiteral("1"), QStringLiteral("388"), QStringLiteral("-439"), QStringLiteral("-527"), QStringLiteral("2"), QStringLiteral("64")}
            , {QStringLiteral("junin2"), QT_TR_NOOP("Path 2"), QStringLiteral("1"), QStringLiteral("389"), QStringLiteral("-48"), QStringLiteral("74"), QStringLiteral("3"), QStringLiteral("0")}

            , {QStringLiteral("junin3"), QT_TR_NOOP("Junon Path"), QStringLiteral("1"), QStringLiteral("390"), QStringLiteral("-1365"), QStringLiteral("3390"), QStringLiteral("27"), QStringLiteral("32")}
            , {QStringLiteral("junele2"), QT_TR_NOOP("Elevator"), QStringLiteral("1"), QStringLiteral("391"), QStringLiteral("-295"), QStringLiteral("13"), QStringLiteral("1"), QStringLiteral("64")}
            , {QStringLiteral("junin4"), QT_TR_NOOP("Junon Path"), QStringLiteral("1"), QStringLiteral("392"), QStringLiteral("-1469"), QStringLiteral("1107"), QStringLiteral("39"), QStringLiteral("64")}
            , {QStringLiteral("junin5"), QT_TR_NOOP("Junon Path"), QStringLiteral("1"), QStringLiteral("393"), QStringLiteral("351"), QStringLiteral("958"), QStringLiteral("24"), QStringLiteral("32")}
            , {QStringLiteral("junin6"), QT_TR_NOOP("Junon Path"), QStringLiteral("1"), QStringLiteral("394"), QStringLiteral("2184"), QStringLiteral("-589"), QStringLiteral("24"), QStringLiteral("32")}
            , {QStringLiteral("junin7"), QT_TR_NOOP("Elevator"), QStringLiteral("1"), QStringLiteral("395"), QStringLiteral("-289"), QStringLiteral("-10"), QStringLiteral("3"), QStringLiteral("0")}
            , {QStringLiteral("junbin1"), QT_TR_NOOP("Junon Branch, 1f."), QStringLiteral("1"), QStringLiteral("396"), QStringLiteral("333"), QStringLiteral("-165"), QStringLiteral("133"), QStringLiteral("0")}
            , {QStringLiteral("junbin12"), QT_TR_NOOP("Junon Office F2"), QStringLiteral("1"), QStringLiteral("397"), QStringLiteral("-364"), QStringLiteral("-303"), QStringLiteral("8"), QStringLiteral("32")}
            , {QStringLiteral("junbin21"), QT_TR_NOOP("Office"), QStringLiteral("1"), QStringLiteral("398"), QStringLiteral("601"), QStringLiteral("-758"), QStringLiteral("125"), QStringLiteral("0")}

            , {QStringLiteral("junbin3"), QT_TR_NOOP("Dr.'s Office"), QStringLiteral("1"), QStringLiteral("400"), QStringLiteral("674"), QStringLiteral("-1408"), QStringLiteral("52"), QStringLiteral("128")}
            , {QStringLiteral("junbin4"), QT_TR_NOOP("Press Room"), QStringLiteral("1"), QStringLiteral("401"), QStringLiteral("-18"), QStringLiteral("0"), QStringLiteral("103"), QStringLiteral("0")}
            , {QStringLiteral("junbin5"), QT_TR_NOOP("Gas Room"), QStringLiteral("1"), QStringLiteral("402"), QStringLiteral("-57"), QStringLiteral("-137"), QStringLiteral("58"), QStringLiteral("32")}
            , {QStringLiteral("jumsbd1"), QT_TR_NOOP("Submarine Dock"), QStringLiteral("1"), QStringLiteral("404"), QStringLiteral("463"), QStringLiteral("-1211"), QStringLiteral("81"), QStringLiteral("192")}
            , {QStringLiteral("subin_1a"), QT_TR_NOOP("Submarine Bridge"), QStringLiteral("1"), QStringLiteral("405"), QStringLiteral("-91"), QStringLiteral("-173"), QStringLiteral("0"), QStringLiteral("128")}
            , {QStringLiteral("subin_1b"), QT_TR_NOOP("Submarine Bridge"), QStringLiteral("1"), QStringLiteral("406"), QStringLiteral("2"), QStringLiteral("125"), QStringLiteral("13"), QStringLiteral("128")}
            , {QStringLiteral("subin_2a"), QT_TR_NOOP("Inside Submarine"), QStringLiteral("1"), QStringLiteral("407"), QStringLiteral("27"), QStringLiteral("97"), QStringLiteral("10"), QStringLiteral("128")}
            , {QStringLiteral("subin_2b"), QT_TR_NOOP("Inside Submarine"), QStringLiteral("1"), QStringLiteral("408"), QStringLiteral("-52"), QStringLiteral("433"), QStringLiteral("7"), QStringLiteral("128")}
            , {QStringLiteral("subin_3"), QT_TR_NOOP("Inside Submarine"), QStringLiteral("1"), QStringLiteral("409"), QStringLiteral("-85"), QStringLiteral("-307"), QStringLiteral("42"), QStringLiteral("128")}

            , {QStringLiteral("junone2"), QT_TR_NOOP("Aljunon"), QStringLiteral("1"), QStringLiteral("411"), QStringLiteral("13911"), QStringLiteral("-2494"), QStringLiteral("15"), QStringLiteral("251")}
            , {QStringLiteral("junone4"), QT_TR_NOOP("Canon"), QStringLiteral("1"), QStringLiteral("413"), QStringLiteral("180"), QStringLiteral("-15763"), QStringLiteral("8"), QStringLiteral("0")}
            , {QStringLiteral("junone5"), QT_TR_NOOP("Junon branch,(ext.)"), QStringLiteral("1"), QStringLiteral("414"), QStringLiteral("441"), QStringLiteral("2966"), QStringLiteral("1"), QStringLiteral("128")}
            , {QStringLiteral("junone6"), QT_TR_NOOP("Canon"), QStringLiteral("1"), QStringLiteral("415"), QStringLiteral("353"), QStringLiteral("-7477"), QStringLiteral("114"), QStringLiteral("0")}
            , {QStringLiteral("junone7"), QT_TR_NOOP("Canon"), QStringLiteral("1"), QStringLiteral("416"), QStringLiteral("-54"), QStringLiteral("839"), QStringLiteral("4"), QStringLiteral("0")}
            , {QStringLiteral("spgate"), QT_TR_NOOP("Underwater Reactor"), QStringLiteral("1"), QStringLiteral("417"), QStringLiteral("10"), QStringLiteral("270"), QStringLiteral("10"), QStringLiteral("128")}
            , {QStringLiteral("spipe_1"), QT_TR_NOOP("Underwater Reactor"), QStringLiteral("1"), QStringLiteral("418"), QStringLiteral("6"), QStringLiteral("-1362"), QStringLiteral("19"), QStringLiteral("128")}
            , {QStringLiteral("spipe_2"), QT_TR_NOOP("Underwater Reactor"), QStringLiteral("1"), QStringLiteral("419"), QStringLiteral("-1"), QStringLiteral("-1146"), QStringLiteral("4"), QStringLiteral("128")}

            , {QStringLiteral("semkin_1"), QT_TR_NOOP("Underwater Reactor"), QStringLiteral("1"), QStringLiteral("420"), QStringLiteral("127"), QStringLiteral("8"), QStringLiteral("6"), QStringLiteral("192")}
            , {QStringLiteral("semkin_2"), QT_TR_NOOP("Underwater Reactor"), QStringLiteral("1"), QStringLiteral("421"), QStringLiteral("4909"), QStringLiteral("-1856"), QStringLiteral("23"), QStringLiteral("192")}
            , {QStringLiteral("semkin_8"), QT_TR_NOOP("Underwater Reactor"), QStringLiteral("1"), QStringLiteral("422"), QStringLiteral("34"), QStringLiteral("426"), QStringLiteral("14"), QStringLiteral("32")}
            , {QStringLiteral("semkin_3"), QT_TR_NOOP("Underwater Reactor"), QStringLiteral("1"), QStringLiteral("423"), QStringLiteral("-866"), QStringLiteral("2380"), QStringLiteral("0"), QStringLiteral("192")}
            , {QStringLiteral("semkin_4"), QT_TR_NOOP("Underwater Reactor"), QStringLiteral("1"), QStringLiteral("424"), QStringLiteral("7"), QStringLiteral("-420"), QStringLiteral("8"), QStringLiteral("128")}
            , {QStringLiteral("semkin_5"), QT_TR_NOOP("Underwater Reactor"), QStringLiteral("1"), QStringLiteral("425"), QStringLiteral("-1513"), QStringLiteral("-1173"), QStringLiteral("1"), QStringLiteral("64")}
            , {QStringLiteral("semkin_6"), QT_TR_NOOP("Underwater Reactor"), QStringLiteral("1"), QStringLiteral("426"), QStringLiteral("-1526"), QStringLiteral("-1161"), QStringLiteral("1"), QStringLiteral("64")}
            , {QStringLiteral("semkin_7"), QT_TR_NOOP("Underwater Reactor"), QStringLiteral("1"), QStringLiteral("427"), QStringLiteral("2231"), QStringLiteral("-1015"), QStringLiteral("9"), QStringLiteral("128")}
            , {QStringLiteral("ujunon1"), QT_TR_NOOP("Under Junon"), QStringLiteral("1"), QStringLiteral("428"), QStringLiteral("565"), QStringLiteral("680"), QStringLiteral("29"), QStringLiteral("32")}
            , {QStringLiteral("ujunon3"), QT_TR_NOOP("Dolphin Offing"), QStringLiteral("1"), QStringLiteral("429"), QStringLiteral("-656"), QStringLiteral("1735"), QStringLiteral("138"), QStringLiteral("32")}

            , {QStringLiteral("prisila"), QT_TR_NOOP("Priscilla's House"), QStringLiteral("1"), QStringLiteral("431"), QStringLiteral("35"), QStringLiteral("-100"), QStringLiteral("60"), QStringLiteral("32")}
            , {QStringLiteral("ujun_w"), QT_TR_NOOP("Weapon Store"), QStringLiteral("1"), QStringLiteral("432"), QStringLiteral("263"), QStringLiteral("200"), QStringLiteral("3"), QStringLiteral("32")}
            , {QStringLiteral("jumin"), QT_TR_NOOP("Under Junon"), QStringLiteral("1"), QStringLiteral("433"), QStringLiteral("-236"), QStringLiteral("-205"), QStringLiteral("4"), QStringLiteral("32")}
            , {QStringLiteral("ujunon5"), QString(), QStringLiteral("1"), QStringLiteral("435"), QStringLiteral("-300"), QStringLiteral("1871"), QStringLiteral("25"), QStringLiteral("149")}

            , {QStringLiteral("ship_1"), QT_TR_NOOP("Cargo Ship"), QStringLiteral("1"), QStringLiteral("436"), QStringLiteral("-106"), QStringLiteral("-1168"), QStringLiteral("46"), QStringLiteral("32")}
            , {QStringLiteral("ship_2"), QT_TR_NOOP("Cargo Ship"), QStringLiteral("1"), QStringLiteral("437"), QStringLiteral("357"), QStringLiteral("-524"), QStringLiteral("32"), QStringLiteral("32")}
            , {QStringLiteral("shpin_2"), QT_TR_NOOP("Cargo Ship"), QStringLiteral("1"), QStringLiteral("439"), QStringLiteral("32"), QStringLiteral("-245"), QStringLiteral("63"), QStringLiteral("32")}

            , {QStringLiteral("shpin_3"), QT_TR_NOOP("Cargo Ship"), QStringLiteral("1"), QStringLiteral("440"), QStringLiteral("2"), QStringLiteral("-501"), QStringLiteral("43"), QStringLiteral("32")}
            , {QStringLiteral("del1"), QT_TR_NOOP("Costa del Sol Harbor"), QStringLiteral("1"), QStringLiteral("441"), QStringLiteral("194"), QStringLiteral("352"), QStringLiteral("137"), QStringLiteral("32")}
            , {QStringLiteral("del2"), QT_TR_NOOP("Costa del Sol"), QStringLiteral("1"), QStringLiteral("443"), QStringLiteral("-1162"), QStringLiteral("83"), QStringLiteral("129"), QStringLiteral("32")}
            , {QStringLiteral("delinn"), QT_TR_NOOP("Costa del Sol Inn"), QStringLiteral("1"), QStringLiteral("444"), QStringLiteral("-156"), QStringLiteral("-591"), QStringLiteral("52"), QStringLiteral("32")}
            , {QStringLiteral("delpb"), QT_TR_NOOP("Bar"), QStringLiteral("1"), QStringLiteral("445"), QStringLiteral("120"), QStringLiteral("198"), QStringLiteral("11"), QStringLiteral("32")}
            , {QStringLiteral("delmin1"), QT_TR_NOOP("House for Sale"), QStringLiteral("1"), QStringLiteral("446"), QStringLiteral("-40"), QStringLiteral("-43"), QStringLiteral("10"), QStringLiteral("32")}
            , {QStringLiteral("delmin12"), QT_TR_NOOP("Cellar"), QStringLiteral("1"), QStringLiteral("447"), QStringLiteral("-5"), QStringLiteral("-48"), QStringLiteral("48"), QStringLiteral("32")}
            , {QStringLiteral("del3"), QT_TR_NOOP("Costa del Sol"), QStringLiteral("1"), QStringLiteral("449"), QStringLiteral("-65"), QStringLiteral("229"), QStringLiteral("118"), QStringLiteral("192")}

            , {QStringLiteral("ncorel"), QT_TR_NOOP("North Corel"), QStringLiteral("1"), QStringLiteral("450"), QStringLiteral("590"), QStringLiteral("-458"), QStringLiteral("64"), QStringLiteral("32")}
            , {QStringLiteral("ncorel2"), QT_TR_NOOP("North Corel"), QStringLiteral("1"), QStringLiteral("451"), QStringLiteral("627"), QStringLiteral("-397"), QStringLiteral("49"), QStringLiteral("32")}
            , {QStringLiteral("ncorel3"), QT_TR_NOOP("North Corel"), QStringLiteral("1"), QStringLiteral("452"), QStringLiteral("490"), QStringLiteral("-383"), QStringLiteral("54"), QStringLiteral("32")}
            , {QStringLiteral("ncoin1"), QT_TR_NOOP("North Corel"), QStringLiteral("1"), QStringLiteral("453"), QStringLiteral("-33"), QStringLiteral("-158"), QStringLiteral("2"), QStringLiteral("32")}
            , {QStringLiteral("ncoin2"), QT_TR_NOOP("North Corel"), QStringLiteral("1"), QStringLiteral("454"), QStringLiteral("7"), QStringLiteral("-239"), QStringLiteral("17"), QStringLiteral("32")}
            , {QStringLiteral("ncoin3"), QT_TR_NOOP("North Corel"), QStringLiteral("1"), QStringLiteral("455"), QStringLiteral("232"), QStringLiteral("1"), QStringLiteral("16"), QStringLiteral("32")}
            , {QStringLiteral("ncoinn"), QT_TR_NOOP("North Corel Inn"), QStringLiteral("1"), QStringLiteral("456"), QStringLiteral("190"), QStringLiteral("-261"), QStringLiteral("36"), QStringLiteral("32")}
            , {QStringLiteral("ropest"), QT_TR_NOOP("Ropeway Station"), QStringLiteral("1"), QStringLiteral("457"), QStringLiteral("504"), QStringLiteral("-208 "), QStringLiteral("39"), QStringLiteral("32")}
            , {QStringLiteral("mtcrl_0"), QT_TR_NOOP("Mt. Corel"), QStringLiteral("1"), QStringLiteral("458"), QStringLiteral("9"), QStringLiteral("-258"), QStringLiteral("103"), QStringLiteral("32")}
            , {QStringLiteral("mtcrl_1"), QT_TR_NOOP("Mt. Corel"), QStringLiteral("1"), QStringLiteral("459"), QStringLiteral("-94"), QStringLiteral("733"), QStringLiteral("88"), QStringLiteral("32")}

            , {QStringLiteral("mtcrl_2"), QT_TR_NOOP("Corel Reactor"), QStringLiteral("1"), QStringLiteral("460"), QStringLiteral("1538"), QStringLiteral("1674"), QStringLiteral("36"), QStringLiteral("32")}
            , {QStringLiteral("mtcrl_3"), QT_TR_NOOP("Mt. Corel"), QStringLiteral("1"), QStringLiteral("461"), QStringLiteral("534"), QStringLiteral("9"), QStringLiteral("182"), QStringLiteral("32")}
            , {QStringLiteral("mtcrl_4"), QT_TR_NOOP("Mt. Corel"), QStringLiteral("1"), QStringLiteral("462"), QStringLiteral("-2038"), QStringLiteral("-5"), QStringLiteral("220"), QStringLiteral("32")}
            , {QStringLiteral("mtcrl_6"), QT_TR_NOOP("Mt. Corel"), QStringLiteral("1"), QStringLiteral("464"), QStringLiteral("-2083"), QStringLiteral("957"), QStringLiteral("206"), QStringLiteral("32")}
            , {QStringLiteral("mtcrl_7"), QT_TR_NOOP("Mt. Corel"), QStringLiteral("1"), QStringLiteral("465"), QStringLiteral("-4"), QStringLiteral("176"), QStringLiteral("15"), QStringLiteral("32")}
            , {QStringLiteral("mtcrl_9"), QT_TR_NOOP("Mt. Corel"), QStringLiteral("1"), QStringLiteral("467"), QStringLiteral("9"), QStringLiteral("3575"), QStringLiteral("106"), QStringLiteral("32")}

            , {QStringLiteral("jail1"), QT_TR_NOOP("Corel Prison"), QStringLiteral("1"), QStringLiteral("471"), QStringLiteral("-348"), QStringLiteral("2345"), QStringLiteral("239"), QStringLiteral("32")}
            , {QStringLiteral("jailin1"), QT_TR_NOOP("Basement"), QStringLiteral("1"), QStringLiteral("472"), QStringLiteral("56"), QStringLiteral("56"), QStringLiteral("11"), QStringLiteral("32")}
            , {QStringLiteral("jail2"), QT_TR_NOOP("Corel Prison"), QStringLiteral("1"), QStringLiteral("473"), QStringLiteral("876"), QStringLiteral("1471"), QStringLiteral("74"), QStringLiteral("32")}
            , {QStringLiteral("jailpb"), QT_TR_NOOP("Prison Pub"), QStringLiteral("1"), QStringLiteral("474"), QStringLiteral("132"), QStringLiteral("-326"), QStringLiteral("67"), QStringLiteral("32")}
            , {QStringLiteral("jailin2"), QT_TR_NOOP("Mayor's Old House"), QStringLiteral("1"), QStringLiteral("475"), QStringLiteral("-21"), QStringLiteral("-69"), QStringLiteral("10"), QStringLiteral("32")}
            , {QStringLiteral("jailin4"), QT_TR_NOOP("Container"), QStringLiteral("1"), QStringLiteral("477"), QStringLiteral("-29"), QStringLiteral("-219"), QStringLiteral("1"), QStringLiteral("32")}
            , {QStringLiteral("jail3"), QT_TR_NOOP("Corel Prison"), QStringLiteral("1"), QStringLiteral("478"), QStringLiteral("-404"), QStringLiteral("223"), QStringLiteral("39"), QStringLiteral("32")}
            , {QStringLiteral("jail4"), QT_TR_NOOP("Corel Prison"), QStringLiteral("1"), QStringLiteral("479"), QStringLiteral("129"), QStringLiteral("308"), QStringLiteral("104"), QStringLiteral("32")}

            , {QStringLiteral("desert1"), QT_TR_NOOP("Corel Prison"), QStringLiteral("1"), QStringLiteral("481"), QStringLiteral("3198"), QStringLiteral("-382"), QStringLiteral("307"), QStringLiteral("32")}
            , {QStringLiteral("desert2"), QT_TR_NOOP("Corel Desert"), QStringLiteral("1"), QStringLiteral("482"), QStringLiteral("3111"), QStringLiteral("-698"), QStringLiteral("251"), QStringLiteral("32")}
            , {QStringLiteral("astage_a"), QT_TR_NOOP("Event square"), QStringLiteral("1"), QStringLiteral("484"), QStringLiteral("2070"), QStringLiteral("-3086"), QStringLiteral("28"), QStringLiteral("32")}
            , {QStringLiteral("jet"), QT_TR_NOOP("Speed square"), QStringLiteral("1"), QStringLiteral("486"), QStringLiteral("-63"), QStringLiteral("-1130"), QStringLiteral("32"), QStringLiteral("32")}
            , {QStringLiteral("jetin1"), QT_TR_NOOP("Platform"), QStringLiteral("1"), QStringLiteral("487"), QStringLiteral("747"), QStringLiteral("2"), QStringLiteral("12"), QStringLiteral("32")}
            , {QStringLiteral("bigwheel"), QT_TR_NOOP("Round Square"), QStringLiteral("1"), QStringLiteral("488"), QStringLiteral("222"), QStringLiteral("-33"), QStringLiteral("6"), QStringLiteral("32")}

            , {QStringLiteral("ghotel"), QT_TR_NOOP("Ghost Hotel"), QStringLiteral("1"), QStringLiteral("491"), QStringLiteral("43"), QStringLiteral("583"), QStringLiteral("53"), QStringLiteral("32")}
            , {QStringLiteral("ghotin_1"), QT_TR_NOOP("Hotel Lobby"), QStringLiteral("1"), QStringLiteral("492"), QStringLiteral("-445"), QStringLiteral("-11"), QStringLiteral("96"), QStringLiteral("32")}
            , {QStringLiteral("ghotin_2"), QT_TR_NOOP("Hotel"), QStringLiteral("1"), QStringLiteral("494"), QStringLiteral("273"), QStringLiteral("-216"), QStringLiteral("8"), QStringLiteral("32")}
            , {QStringLiteral("ghotin_3"), QT_TR_NOOP("Hotel Shop"), QStringLiteral("1"), QStringLiteral("495"), QStringLiteral("250"), QStringLiteral("-173"), QStringLiteral("13"), QStringLiteral("32")}
            , {QStringLiteral("gldst"), QT_TR_NOOP("Ropeway Station"), QStringLiteral("1"), QStringLiteral("496"), QStringLiteral("-769"), QStringLiteral("95"), QStringLiteral("26"), QStringLiteral("32")}
            , {QStringLiteral("gldgate"), QT_TR_NOOP("Terminal Floor"), QStringLiteral("1"), QStringLiteral("497"), QStringLiteral("26"), QStringLiteral("71"), QStringLiteral("13"), QStringLiteral("32")}
            , {QStringLiteral("coloss"), QT_TR_NOOP("Battle Square"), QStringLiteral("1"), QStringLiteral("499"), QStringLiteral("3"), QStringLiteral("-2322"), QStringLiteral("7"), QStringLiteral("32")}

            , {QStringLiteral("coloin1"), QT_TR_NOOP("Arena Lobby"), QStringLiteral("1"), QStringLiteral("500"), QStringLiteral("6"), QStringLiteral("-3278"), QStringLiteral("5"), QStringLiteral("128")}
            , {QStringLiteral("clsin2_2"), QT_TR_NOOP("Dio's Museum"), QStringLiteral("1"), QStringLiteral("503"), QStringLiteral("1547"), QStringLiteral("-2819"), QStringLiteral("9"), QStringLiteral("32")}
            , {QStringLiteral("games"), QT_TR_NOOP("Wonder Square"), QStringLiteral("1"), QStringLiteral("505"), QStringLiteral("231"), QStringLiteral("-527"), QStringLiteral("67"), QStringLiteral("216")}
            , {QStringLiteral("games_1"), QT_TR_NOOP("Building 1f."), QStringLiteral("1"), QStringLiteral("506"), QStringLiteral("29"), QStringLiteral("1643"), QStringLiteral("65"), QStringLiteral("32")}
            , {QStringLiteral("games_2"), QT_TR_NOOP("Building 2f."), QStringLiteral("1"), QStringLiteral("507"), QStringLiteral("12"), QStringLiteral("357"), QStringLiteral("23"), QStringLiteral("32")}
            , {QStringLiteral("chorace"), QT_TR_NOOP("Chocobo Square"), QStringLiteral("1"), QStringLiteral("509"), QStringLiteral("-73"), QStringLiteral("-2444"), QStringLiteral("118"), QStringLiteral("32")}

            , {QStringLiteral("crcin_1"), QT_TR_NOOP("Ticket Office"), QStringLiteral("1"), QStringLiteral("511"), QStringLiteral("-257"), QStringLiteral("-468"), QStringLiteral("18"), QStringLiteral("32")}
            , {QStringLiteral("crcin_2"), QT_TR_NOOP("Jungle"), QStringLiteral("1"), QStringLiteral("514"), QStringLiteral("-73"), QStringLiteral("-103"), QStringLiteral("64"), QStringLiteral("32")}
            , {QStringLiteral("gonjun2"), QT_TR_NOOP("Jungle"), QStringLiteral("1"), QStringLiteral("515"), QStringLiteral("-1"), QStringLiteral("-190"), QStringLiteral("0"), QStringLiteral("32")}
            , {QStringLiteral("gnmkf"), QT_TR_NOOP("Meltdown Reactor"), QStringLiteral("1"), QStringLiteral("516"), QStringLiteral("200"), QStringLiteral("-7054"), QStringLiteral("83"), QStringLiteral("32")}
            , {QStringLiteral("gnmk"), QT_TR_NOOP("Meltdown Reactor"), QStringLiteral("1"), QStringLiteral("517"), QStringLiteral("-16"), QStringLiteral("-767"), QStringLiteral("32"), QStringLiteral("104")}
            , {QStringLiteral("gongaga"), QT_TR_NOOP("Gongaga Village"), QStringLiteral("1"), QStringLiteral("518"), QStringLiteral("51"), QStringLiteral("-365"), QStringLiteral("96"), QStringLiteral("104")}
            , {QStringLiteral("gon_wa1"), QT_TR_NOOP("Weapons Store"), QStringLiteral("1"), QStringLiteral("519"), QStringLiteral("55"), QStringLiteral("-38"), QStringLiteral("2"), QStringLiteral("160")}

            , {QStringLiteral("gon_i"), QT_TR_NOOP("Item Store"), QStringLiteral("1"), QStringLiteral("521"), QStringLiteral("71"), QStringLiteral("-76"), QStringLiteral("7"), QStringLiteral("152")}
            , {QStringLiteral("gninn"), QT_TR_NOOP("Inn"), QStringLiteral("1"), QStringLiteral("522"), QStringLiteral("-26"), QStringLiteral("-203"), QStringLiteral("13"), QStringLiteral("104")}
            , {QStringLiteral("gomin"), QT_TR_NOOP("Zack's Home"), QStringLiteral("1"), QStringLiteral("523"), QStringLiteral("--109"), QStringLiteral("132"), QStringLiteral("45"), QStringLiteral("232")}
            , {QStringLiteral("goson"), QT_TR_NOOP("Mayor's Home"), QStringLiteral("1"), QStringLiteral("524"), QStringLiteral("-117"), QStringLiteral("-208"), QStringLiteral("94"), QStringLiteral("32")}
            , {QStringLiteral("cos_btm"), QT_TR_NOOP("Cosmo Canyon"), QStringLiteral("1"), QStringLiteral("525"), QStringLiteral("-962"), QStringLiteral("-1740"), QStringLiteral("128"), QStringLiteral("32")}
            , {QStringLiteral("con_btm2"), QT_TR_NOOP("Cosmo Candle"), QStringLiteral("1"), QStringLiteral("526"), QStringLiteral("-350"), QStringLiteral("-1422"), QStringLiteral("98"), QStringLiteral("235")}
            , {QStringLiteral("cosin1"), QT_TR_NOOP("Cosmo Canyon"), QStringLiteral("1"), QStringLiteral("529"), QStringLiteral("128"), QStringLiteral("-321"), QStringLiteral("79"), QStringLiteral("32")}

            , {QStringLiteral("cosin1_1"), QT_TR_NOOP("Elder's Room"), QStringLiteral("1"), QStringLiteral("530"), QStringLiteral("99"), QStringLiteral("-140"), QStringLiteral("7"), QStringLiteral("32")}
            , {QStringLiteral("cosin2"), QT_TR_NOOP("Gate of Naught"), QStringLiteral("1"), QStringLiteral("531"), QStringLiteral("8"), QStringLiteral("-88"), QStringLiteral("71"), QStringLiteral("32")}
            , {QStringLiteral("cosin3"), QT_TR_NOOP("Pub \"Starlet\" "), QStringLiteral("1"), QStringLiteral("532"), QStringLiteral("403"), QStringLiteral("-43"), QStringLiteral("22"), QStringLiteral("32")}
            , {QStringLiteral("cosin5"), QT_TR_NOOP("Sealed Cave"), QStringLiteral("1"), QStringLiteral("534"), QStringLiteral("-145"), QStringLiteral("624"), QStringLiteral("47"), QStringLiteral("32")}
            , {QStringLiteral("cosmin2"), QT_TR_NOOP("Materia Shop"), QStringLiteral("1"), QStringLiteral("535"), QStringLiteral("-33"), QStringLiteral("108"), QStringLiteral("11"), QStringLiteral("32")}
            , {QStringLiteral("cosmin3"), QT_TR_NOOP("Cosmo Canyon"), QStringLiteral("1"), QStringLiteral("536"), QStringLiteral("137"), QStringLiteral("58"), QStringLiteral("16"), QStringLiteral("32")}
            , {QStringLiteral("cosmin6"), QT_TR_NOOP("Shildra Inn"), QStringLiteral("1"), QStringLiteral("538"), QStringLiteral("40"), QStringLiteral("-244"), QStringLiteral("22"), QStringLiteral("32")}
            , {QStringLiteral("cosmin7"), QT_TR_NOOP("Item Store"), QStringLiteral("1"), QStringLiteral("539"), QStringLiteral("108"), QStringLiteral("-59"), QStringLiteral("32"), QStringLiteral("32")}

            , {QStringLiteral("cos_top"), QT_TR_NOOP("Observatory"), QStringLiteral("1"), QStringLiteral("540"), QStringLiteral("-81"), QStringLiteral("-453"), QStringLiteral("31"), QStringLiteral("104")}
            , {QStringLiteral("bugin1a"), QT_TR_NOOP("Observatory"), QStringLiteral("1"), QStringLiteral("541"), QStringLiteral("-147"), QStringLiteral("42"), QStringLiteral("32"), QStringLiteral("32")}
            , {QStringLiteral("bugin1b"), QT_TR_NOOP("Observatory"), QStringLiteral("1"), QStringLiteral("542"), QStringLiteral("-1821"), QStringLiteral("1835"), QStringLiteral("-1792"), QStringLiteral("99")}
            , {QStringLiteral("bugin2"), QT_TR_NOOP("Bugen Research Center"), QStringLiteral("1"), QStringLiteral("544"), QStringLiteral("-107"), QStringLiteral("-137"), QStringLiteral("9"), QStringLiteral("32")}
            , {QStringLiteral("gidun_1"), QT_TR_NOOP("Cave of the Gi"), QStringLiteral("1"), QStringLiteral("546"), QStringLiteral("-1070"), QStringLiteral("515"), QStringLiteral("198"), QStringLiteral("32")}
            , {QStringLiteral("gidun_2"), QT_TR_NOOP("Cave of the Gi"), QStringLiteral("1"), QStringLiteral("547"), QStringLiteral("333"), QStringLiteral("-1127"), QStringLiteral("144"), QStringLiteral("32")}
            , {QStringLiteral("gidun_4"), QT_TR_NOOP("Cave of the Gi"), QStringLiteral("1"), QStringLiteral("548"), QStringLiteral("335"), QStringLiteral("-1521"), QStringLiteral("17"), QStringLiteral("32")}
            , {QStringLiteral("gidun_3"), QT_TR_NOOP("Cave of the Gi"), QStringLiteral("1"), QStringLiteral("549"), QStringLiteral("-44"), QStringLiteral("-959"), QStringLiteral("19"), QStringLiteral("104")}

            , {QStringLiteral("rckt3"), QT_TR_NOOP("House"), QStringLiteral("1"), QStringLiteral("552"), QStringLiteral("-282"), QStringLiteral("521"), QStringLiteral("95"), QStringLiteral("156")}
            , {QStringLiteral("rkt_w"), QT_TR_NOOP("Weapons Store"), QStringLiteral("1"), QStringLiteral("553"), QStringLiteral("282"), QStringLiteral("187"), QStringLiteral("27"), QStringLiteral("32")}
            , {QStringLiteral("rkt_i"), QT_TR_NOOP("Item Store"), QStringLiteral("1"), QStringLiteral("554"), QStringLiteral("182"), QStringLiteral("143"), QStringLiteral("39"), QStringLiteral("32")}
            , {QStringLiteral("rktinn1"), QT_TR_NOOP("Shanghai Inn"), QStringLiteral("1"), QStringLiteral("555"), QStringLiteral("-172"), QStringLiteral("268"), QStringLiteral("48"), QStringLiteral("32")}
            , {QStringLiteral("rktinn2"), QT_TR_NOOP("Shanghai Inn"), QStringLiteral("1"), QStringLiteral("556"), QStringLiteral("-101"), QStringLiteral("330"), QStringLiteral("40"), QStringLiteral("32")}
            , {QStringLiteral("rckt"), QT_TR_NOOP("Rocket Town"), QStringLiteral("1"), QStringLiteral("557"), QStringLiteral("-3"), QStringLiteral("-721"), QStringLiteral("2"), QStringLiteral("104")}
            , {QStringLiteral("rktsid"), QT_TR_NOOP("House"), QStringLiteral("1"), QStringLiteral("558"), QStringLiteral("-133"), QStringLiteral("141"), QStringLiteral("96"), QStringLiteral("32")}
            , {QStringLiteral("rktmin1"), QT_TR_NOOP("House"), QStringLiteral("1"), QStringLiteral("559"), QStringLiteral("-69"), QStringLiteral("329"), QStringLiteral("25"), QStringLiteral("32")}

            , {QStringLiteral("rktmin2"), QT_TR_NOOP("House"), QStringLiteral("1"), QStringLiteral("560"), QStringLiteral("-228"), QStringLiteral("299"), QStringLiteral("49"), QStringLiteral("32")}
            , {QStringLiteral("rcktbas1"), QT_TR_NOOP("Rocket Launching Pad"), QStringLiteral("1"), QStringLiteral("561"), QStringLiteral("-1607"), QStringLiteral("3688"), QStringLiteral("120"), QStringLiteral("32")}
            , {QStringLiteral("rcktbas2"), QT_TR_NOOP("Rocket Launching Pad"), QStringLiteral("1"), QStringLiteral("562"), QStringLiteral("-1007"), QStringLiteral("4947"), QStringLiteral("89"), QStringLiteral("32")}
            , {QStringLiteral("rcktin1"), QT_TR_NOOP("Duct"), QStringLiteral("1"), QStringLiteral("563"), QStringLiteral("12"), QStringLiteral("88"), QStringLiteral("6"), QStringLiteral("128")}
            , {QStringLiteral("rcktin2"), QT_TR_NOOP("Ship Hallway"), QStringLiteral("1"), QStringLiteral("564"), QStringLiteral("-31"), QStringLiteral("60"), QStringLiteral("15"), QStringLiteral("32")}
            , {QStringLiteral("rcktin3"), QT_TR_NOOP("Ship Hallway"), QStringLiteral("1"), QStringLiteral("565"), QStringLiteral("12"), QStringLiteral("-37"), QStringLiteral("6"), QStringLiteral("0")}
            , {QStringLiteral("rcktin4"), QT_TR_NOOP("Materia Room"), QStringLiteral("1"), QStringLiteral("566"), QStringLiteral("1"), QStringLiteral("-311"), QStringLiteral("9"), QStringLiteral("128")}
            , {QStringLiteral("rcktin5"), QT_TR_NOOP("Cockpit"), QStringLiteral("1"), QStringLiteral("567"), QStringLiteral("4"), QStringLiteral("-32"), QStringLiteral("7"), QStringLiteral("128")}
            , {QStringLiteral("rcktin6"), QT_TR_NOOP("Engine Room"), QStringLiteral("1"), QStringLiteral("568"), QStringLiteral("0"), QStringLiteral("437"), QStringLiteral("9"), QStringLiteral("0")}
            , {QStringLiteral("rcktin7"), QT_TR_NOOP("Escape Pod"), QStringLiteral("1"), QStringLiteral("569"), QStringLiteral("-51"), QStringLiteral("263"), QStringLiteral("19"), QStringLiteral("32")}

            , {QStringLiteral("rcktin8"), QT_TR_NOOP("Duct"), QStringLiteral("1"), QStringLiteral("570"), QStringLiteral("5"), QStringLiteral("99"), QStringLiteral("11"), QStringLiteral("0")}
            , {QStringLiteral("yougan"), QT_TR_NOOP("Wilderness"), QStringLiteral("1"), QStringLiteral("572"), QStringLiteral("-7"), QStringLiteral("73"), QStringLiteral("3"), QStringLiteral("32")}
            , {QStringLiteral("yougan2"), QT_TR_NOOP("Plains"), QStringLiteral("1"), QStringLiteral("573"), QStringLiteral("-72"), QStringLiteral("28"), QStringLiteral("265"), QStringLiteral("32")}
            , {QStringLiteral("uta_wa"), QT_TR_NOOP("Wutai"), QStringLiteral("1"), QStringLiteral("575"), QStringLiteral("-4"), QStringLiteral("-13"), QStringLiteral("2"), QStringLiteral("32")}
            , {QStringLiteral("uta_im"), QT_TR_NOOP("Item Store"), QStringLiteral("1"), QStringLiteral("576"), QStringLiteral("19"), QStringLiteral("-20"), QStringLiteral("11"), QStringLiteral("32")}
            , {QStringLiteral("utmin1"), QT_TR_NOOP("Wutai, Cat's House"), QStringLiteral("1"), QStringLiteral("577"), QStringLiteral("0"), QStringLiteral("-72"), QStringLiteral("29"), QStringLiteral("32")}
            , {QStringLiteral("utmin2"), QT_TR_NOOP("Wutai, Old Man's House"), QStringLiteral("1"), QStringLiteral("578"), QStringLiteral("55"), QStringLiteral("-111"), QStringLiteral("46"), QStringLiteral("32")}
            , {QStringLiteral("uutai1"), QT_TR_NOOP("Wutai"), QStringLiteral("1"), QStringLiteral("579"), QStringLiteral("-575"), QStringLiteral("1101"), QStringLiteral("34"), QStringLiteral("32")}

            , {QStringLiteral("utapb"), QT_TR_NOOP("Bar [Turtle Paradise]"), QStringLiteral("1"), QStringLiteral("580"), QStringLiteral("-119"), QStringLiteral("-191"), QStringLiteral("10"), QStringLiteral("32")}
            , {QStringLiteral("yufy1"), QT_TR_NOOP("Yuffie's House"), QStringLiteral("1"), QStringLiteral("581"), QStringLiteral("28"), QStringLiteral("-75"), QStringLiteral("25"), QStringLiteral("32")}
            , {QStringLiteral("yufy2"), QT_TR_NOOP("Yuffie's House"), QStringLiteral("1"), QStringLiteral("582"), QStringLiteral("81"), QStringLiteral("-590"), QStringLiteral("66"), QStringLiteral("32")}
            , {QStringLiteral("hideway1"), QT_TR_NOOP("Hidden Passage"), QStringLiteral("1"), QStringLiteral("583"), QStringLiteral("31"), QStringLiteral("-82"), QStringLiteral("1"), QStringLiteral("32")}
            , {QStringLiteral("hideway2"), QT_TR_NOOP("Hidden Passage"), QStringLiteral("1"), QStringLiteral("584"), QStringLiteral("8"), QStringLiteral("-268"), QStringLiteral("0"), QStringLiteral("32")}
            , {QStringLiteral("hideway3"), QT_TR_NOOP("Hidden Passage"), QStringLiteral("1"), QStringLiteral("585"), QStringLiteral("-4"), QStringLiteral("-172"), QStringLiteral("1"), QStringLiteral("104")}
            , {QStringLiteral("tower5"), QT_TR_NOOP("Wutai, Godo's Pagoda"), QStringLiteral("1"), QStringLiteral("586"), QStringLiteral("5"), QStringLiteral("-290"), QStringLiteral("3"), QStringLiteral("104")}
            , {QStringLiteral("uutai2"), QT_TR_NOOP("Wutai, Pagoda"), QStringLiteral("1"), QStringLiteral("587"), QStringLiteral("-84"), QStringLiteral("-5145"), QStringLiteral("10"), QStringLiteral("32")}
            , {QStringLiteral("uttmpin1"), QT_TR_NOOP("Wutai, Main Mtn."), QStringLiteral("1"), QStringLiteral("588"), QStringLiteral("89"), QStringLiteral("-309"), QStringLiteral("88"), QStringLiteral("32")}
            , {QStringLiteral("uttmpin2"), QT_TR_NOOP("Wutai, Main Mtn."), QStringLiteral("1"), QStringLiteral("589"), QStringLiteral("-4905"), QStringLiteral("-373"), QStringLiteral("54"), QStringLiteral("32")}

            , {QStringLiteral("uttmpin3"), QT_TR_NOOP("Wutai, Main Mtn."), QStringLiteral("1"), QStringLiteral("590"), QStringLiteral("11"), QStringLiteral("-95"), QStringLiteral("10"), QStringLiteral("32")}
            , {QStringLiteral("uttmpin4"), QT_TR_NOOP("Hidden Room"), QStringLiteral("1"), QStringLiteral("591"), QStringLiteral("2"), QStringLiteral("-162"), QStringLiteral("16"), QStringLiteral("32")}
            , {QStringLiteral("datiao_1"), QT_TR_NOOP("Wutai, Da-chao Statue"), QStringLiteral("1"), QStringLiteral("592"), QStringLiteral("589"), QStringLiteral("-855"), QStringLiteral("11"), QStringLiteral("32")}
            , {QStringLiteral("datiao_3"), QT_TR_NOOP("Wutai, Da-chao Statue"), QStringLiteral("1"), QStringLiteral("593"), QStringLiteral("192"), QStringLiteral("-28"), QStringLiteral("22"), QStringLiteral("32")}
            , {QStringLiteral("datiao_2"), QT_TR_NOOP("Wutai, Da-chao Statue"), QStringLiteral("1"), QStringLiteral("594"), QStringLiteral("-943"), QStringLiteral("-209"), QStringLiteral("0"), QStringLiteral("32")}
            , {QStringLiteral("datiao_4"), QT_TR_NOOP("Wutai, Da-chao Statue"), QStringLiteral("1"), QStringLiteral("595"), QStringLiteral("619"), QStringLiteral("-45"), QStringLiteral("28"), QStringLiteral("32")}
            , {QStringLiteral("datiao_5"), QT_TR_NOOP("Wutai, Da-chao Statue"), QStringLiteral("1"), QStringLiteral("596"), QStringLiteral("-553"), QStringLiteral("-14"), QStringLiteral("7"), QStringLiteral("32")}
            , {QStringLiteral("datiao_6"), QT_TR_NOOP("Wutai, Da-chao Statue"), QStringLiteral("1"), QStringLiteral("597"), QStringLiteral("-317"), QStringLiteral("-238"), QStringLiteral("116"), QStringLiteral("32")}
            , {QStringLiteral("datiao_7"), QT_TR_NOOP("Wutai, Da-chao Statue"), QStringLiteral("1"), QStringLiteral("598"), QStringLiteral("-362"), QStringLiteral("361"), QStringLiteral("2"), QStringLiteral("32")}
            , {QStringLiteral("datiao_8"), QT_TR_NOOP("Wutai, Da-chao Statue"), QStringLiteral("1"), QStringLiteral("599"), QStringLiteral("-181"), QStringLiteral("-391"), QStringLiteral("16"), QStringLiteral("32")}

            , {QStringLiteral("jtempl"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("600"), QStringLiteral("509"), QStringLiteral("-1300"), QStringLiteral("2"), QStringLiteral("32")}
            , {QStringLiteral("jtmpin1"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("602"), QStringLiteral("-15"), QStringLiteral("-209"), QStringLiteral("32"), QStringLiteral("32")}
            , {QStringLiteral("kuro_1"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("604"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("0"), QStringLiteral("32")}
            , {QStringLiteral("kuro_2"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("605"), QStringLiteral("-59"), QStringLiteral("39"), QStringLiteral("30"), QStringLiteral("32")}
            , {QStringLiteral("kuro_3"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("606"), QStringLiteral("-75"), QStringLiteral("1430"), QStringLiteral("61"), QStringLiteral("32")}
            , {QStringLiteral("kuro_5"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("608"), QStringLiteral("-126"), QStringLiteral("-494"), QStringLiteral("6"), QStringLiteral("32")}
            , {QStringLiteral("kuro_6"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("609"), QStringLiteral("-3"), QStringLiteral("-191"), QStringLiteral("2"), QStringLiteral("32")}

            , {QStringLiteral("kuro_7"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("610"), QStringLiteral("-345"), QStringLiteral("314"), QStringLiteral("127"), QStringLiteral("32")}
            , {QStringLiteral("kuro_8"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("611"), QStringLiteral("-474"), QStringLiteral("86"), QStringLiteral("9"), QStringLiteral("32")}
            , {QStringLiteral("kuro_10"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("614"), QStringLiteral("-4"), QStringLiteral("608"), QStringLiteral("2"), QStringLiteral("32")}
            , {QStringLiteral("kuro_11"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("615"), QStringLiteral("4"), QStringLiteral("844"), QStringLiteral("12"), QStringLiteral("32")}
            , {QStringLiteral("kuro_12"), QT_TR_NOOP("Temple of the Ancients"), QStringLiteral("1"), QStringLiteral("616"), QStringLiteral("4"), QStringLiteral("-219"), QStringLiteral("30"), QStringLiteral("32")}
            , {QStringLiteral("bonevil"), QT_TR_NOOP("Bone Village"), QStringLiteral("1"), QStringLiteral("617"), QStringLiteral("-159"), QStringLiteral("-170"), QStringLiteral("65"), QStringLiteral("32")}
            , {QStringLiteral("slfrst_1"), QT_TR_NOOP("Sleeping Forest"), QStringLiteral("1"), QStringLiteral("618"), QStringLiteral("2"), QStringLiteral("-126"), QStringLiteral("8"), QStringLiteral("32")}
            , {QStringLiteral("slfrst_2"), QT_TR_NOOP("Sleeping Forest"), QStringLiteral("1"), QStringLiteral("619"), QStringLiteral("-3"), QStringLiteral("-331"), QStringLiteral("18"), QStringLiteral("32")}
            , {QStringLiteral("anfrst_1"), QT_TR_NOOP("Ancient Forest"), QStringLiteral("1"), QStringLiteral("620"), QStringLiteral("-1755"), QStringLiteral("-586"), QStringLiteral("56"), QStringLiteral("64")}
            , {QStringLiteral("anfrst_2"), QT_TR_NOOP("Ancient Forest"), QStringLiteral("1"), QStringLiteral("621"), QStringLiteral("-544"), QStringLiteral("-122"), QStringLiteral("61"), QStringLiteral("64")}
            , {QStringLiteral("anfrst_3"), QT_TR_NOOP("Ancient Forest"), QStringLiteral("1"), QStringLiteral("622"), QStringLiteral("-1943"), QStringLiteral("-748"), QStringLiteral("104"), QStringLiteral("64")}
            , {QStringLiteral("anfrst_4"), QT_TR_NOOP("Ancient Forest"), QStringLiteral("1"), QStringLiteral("623"), QStringLiteral("102"), QStringLiteral("-856"), QStringLiteral("31"), QStringLiteral("64")}
            , {QStringLiteral("anfrst_5"), QT_TR_NOOP("Ancient Forest"), QStringLiteral("1"), QStringLiteral("624"), QStringLiteral("118"), QStringLiteral("1045"), QStringLiteral("2"), QStringLiteral("64")}

            , {QStringLiteral("sango1"), QT_TR_NOOP("Corel Valley"), QStringLiteral("1"), QStringLiteral("625"), QStringLiteral("-112"), QStringLiteral("-345"), QStringLiteral("76"), QStringLiteral("32")}
            , {QStringLiteral("sango2"), QT_TR_NOOP("Corel Valley"), QStringLiteral("1"), QStringLiteral("626"), QStringLiteral("-1916"), QStringLiteral("-11320"), QStringLiteral("14"), QStringLiteral("32")}
            , {QStringLiteral("sango3"), QT_TR_NOOP("Forgotten City"), QStringLiteral("1"), QStringLiteral("627"), QStringLiteral("-65"), QStringLiteral("431"), QStringLiteral("135"), QStringLiteral("84")}
            , {QStringLiteral("sandun_1"), QT_TR_NOOP("Corel Valley Cave"), QStringLiteral("1"), QStringLiteral("628"), QStringLiteral("635"), QStringLiteral("-599"), QStringLiteral("164"), QStringLiteral("192")}
            , {QStringLiteral("sandun_2"), QT_TR_NOOP("Corel Valley Cave"), QStringLiteral("1"), QStringLiteral("629"), QStringLiteral("29"), QStringLiteral("-1053"), QStringLiteral("29"), QStringLiteral("128")}

            , {QStringLiteral("lost1"), QT_TR_NOOP("Forgotten Capital"), QStringLiteral("1"), QStringLiteral("630"), QStringLiteral("-1595"), QStringLiteral("1142"), QStringLiteral("10"), QStringLiteral("32")}
            , {QStringLiteral("losin1"), QT_TR_NOOP("Forgotten City"), QStringLiteral("1"), QStringLiteral("631"), QStringLiteral("216"), QStringLiteral("-184"), QStringLiteral("29"), QStringLiteral("32")}
            , {QStringLiteral("losin2"), QT_TR_NOOP("Forgotten Capital"), QStringLiteral("1"), QStringLiteral("632"), QStringLiteral("192"), QStringLiteral("-90"), QStringLiteral("14"), QStringLiteral("32")}
            , {QStringLiteral("losin3"), QT_TR_NOOP("Forgotten Capital"), QStringLiteral("1"), QStringLiteral("633"), QStringLiteral("-134"), QStringLiteral("-135"), QStringLiteral("40"), QStringLiteral("32")}
            , {QStringLiteral("lost2"), QT_TR_NOOP("Forgotten Capital"), QStringLiteral("1"), QStringLiteral("634"), QStringLiteral("-1587"), QStringLiteral("4484"), QStringLiteral("7"), QStringLiteral("32")}
            , {QStringLiteral("lost3"), QT_TR_NOOP("Forgotten Capital"), QStringLiteral("1"), QStringLiteral("635"), QStringLiteral("-5466"), QStringLiteral("7108"), QStringLiteral("12"), QStringLiteral("32")}
            , {QStringLiteral("losinn"), QT_TR_NOOP("Forgotten Capital"), QStringLiteral("1"), QStringLiteral("636"), QStringLiteral("427"), QStringLiteral("-157"), QStringLiteral("5"), QStringLiteral("32")}
            , {QStringLiteral("loslake1"), QT_TR_NOOP("Forgotten City"), QStringLiteral("1"), QStringLiteral("637"), QStringLiteral("-509"), QStringLiteral("443"), QStringLiteral("116"), QStringLiteral("32")}
            , {QStringLiteral("loslake2"), QT_TR_NOOP("Forgotten City"), QStringLiteral("1"), QStringLiteral("638"), QStringLiteral("-552"), QStringLiteral("-1321"), QStringLiteral("8"), QStringLiteral("32")}

            , {QStringLiteral("blue_1"), QT_TR_NOOP("Forgotten City"), QStringLiteral("1"), QStringLiteral("640"), QStringLiteral("-9922"), QStringLiteral("5910"), QStringLiteral("2"), QStringLiteral("32")}
            , {QStringLiteral("blue_2"), QT_TR_NOOP("Forgotten City"), QStringLiteral("1"), QStringLiteral("641"), QStringLiteral("311"), QStringLiteral("-990"), QStringLiteral("40"), QStringLiteral("32")}
            , {QStringLiteral("white1"), QString(), QStringLiteral("1"), QStringLiteral("642"), QStringLiteral("-342"), QStringLiteral("-760"), QStringLiteral("13"), QStringLiteral("112")}
            , {QStringLiteral("white2"), QString(), QStringLiteral("1"), QStringLiteral("643"), QStringLiteral("-241"), QStringLiteral("-517"), QStringLiteral("25"), QStringLiteral("112")}
            , {QStringLiteral("hekiga"), QString(), QStringLiteral("1"), QStringLiteral("644"), QStringLiteral("-146"), QStringLiteral("-321"), QStringLiteral("1"), QStringLiteral("112")}
            , {QStringLiteral("whitein"), QT_TR_NOOP("Forgotten City"), QStringLiteral("1"), QStringLiteral("645"), QStringLiteral("671"), QStringLiteral("-1199"), QStringLiteral("13"), QStringLiteral("32")}
            , {QStringLiteral("ancnt1"), QT_TR_NOOP("Forgotten City"), QStringLiteral("1"), QStringLiteral("646"), QStringLiteral("641"), QStringLiteral("793"), QStringLiteral("243"), QStringLiteral("32")}
            , {QStringLiteral("ancnt2"), QT_TR_NOOP("Water Altar"), QStringLiteral("1"), QStringLiteral("647"), QStringLiteral("443"), QStringLiteral("-891"), QStringLiteral("5"), QStringLiteral("32")}

            , {QStringLiteral("snw_w"), QT_TR_NOOP("Weapon Store"), QStringLiteral("1"), QStringLiteral("650"), QStringLiteral("-11"), QStringLiteral("33"), QStringLiteral("7"), QStringLiteral("128")}
            , {QStringLiteral("sninn_1"), QT_TR_NOOP("Icicle Inn"), QStringLiteral("1"), QStringLiteral("651"), QStringLiteral("44"), QStringLiteral("164"), QStringLiteral("37"), QStringLiteral("128")}
            , {QStringLiteral("sninn_2"), QT_TR_NOOP("Icicle Inn"), QStringLiteral("1"), QStringLiteral("652"), QStringLiteral("95"), QStringLiteral("229"), QStringLiteral("25"), QStringLiteral("192")}
            , {QStringLiteral("sninn_b1"), QT_TR_NOOP("Icicle Inn Bar"), QStringLiteral("1"), QStringLiteral("653"), QStringLiteral("68"), QStringLiteral("328"), QStringLiteral("79"), QStringLiteral("64")}
            , {QStringLiteral("snow"), QT_TR_NOOP("Icicle Inn"), QStringLiteral("1"), QStringLiteral("654"), QStringLiteral("-146"), QStringLiteral("-904"), QStringLiteral("96"), QStringLiteral("128")}
            , {QStringLiteral("snmin1"), QT_TR_NOOP("Icicle Inn"), QStringLiteral("1"), QStringLiteral("655"), QStringLiteral("13"), QStringLiteral("84"), QStringLiteral("26"), QStringLiteral("128")}
            , {QStringLiteral("snmin2"), QT_TR_NOOP("Icicle Inn"), QStringLiteral("1"), QStringLiteral("656"), QStringLiteral("-481"), QStringLiteral("-421"), QStringLiteral("61"), QStringLiteral("128")}
            , {QStringLiteral("snmayor"), QT_TR_NOOP("Gast's House"), QStringLiteral("1"), QStringLiteral("657"), QStringLiteral("-221"), QStringLiteral("926"), QStringLiteral("60"), QStringLiteral("64")}
            , {QStringLiteral("hyou1"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("658"), QStringLiteral("-12"), QStringLiteral("765"), QStringLiteral("69"), QStringLiteral("128")}
            , {QStringLiteral("hyou2"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("659"), QStringLiteral("-877"), QStringLiteral("566"), QStringLiteral("8"), QStringLiteral("64")}

            , {QStringLiteral("hyou3"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("660"), QStringLiteral("-316"), QStringLiteral("1809"), QStringLiteral("28"), QStringLiteral("64")}
            , {QStringLiteral("icedun_1"), QT_TR_NOOP("Frostbite Cave"), QStringLiteral("1"), QStringLiteral("661"), QStringLiteral("-66"), QStringLiteral("-721"), QStringLiteral("66"), QStringLiteral("64")}
            , {QStringLiteral("icedun_2"), QT_TR_NOOP("Frostbite Cave"), QStringLiteral("1"), QStringLiteral("662"), QStringLiteral("-523"), QStringLiteral("-121"), QStringLiteral("1"), QStringLiteral("192")}
            , {QStringLiteral("hyou4"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("663"), QStringLiteral("-76"), QStringLiteral("-477"), QStringLiteral("30"), QStringLiteral("128")}
            , {QStringLiteral("hyou5_1"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("664"), QStringLiteral("697"), QStringLiteral("1965"), QStringLiteral("104"), QStringLiteral("192")}
            , {QStringLiteral("hyou5_2"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("665"), QStringLiteral("183"), QStringLiteral("-802"), QStringLiteral("96"), QStringLiteral("128")}
            , {QStringLiteral("hyou5_3"), QT_TR_NOOP("Cave"), QStringLiteral("1"), QStringLiteral("666"), QStringLiteral("-62"), QStringLiteral("121"), QStringLiteral("87"), QStringLiteral("192")}
            , {QStringLiteral("hyou5_4"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("667"), QStringLiteral("158"), QStringLiteral("329"), QStringLiteral("4"), QStringLiteral("128")}
            , {QStringLiteral("hyou6"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("668"), QStringLiteral("-591"), QStringLiteral("-79"), QStringLiteral("188"), QStringLiteral("64")}
            , {QStringLiteral("hyoumap"), QT_TR_NOOP("Great Glacier Map"), QStringLiteral("1"), QStringLiteral("669"), QStringLiteral("0"), QStringLiteral("-0"), QStringLiteral("0"), QStringLiteral("0")}

            , {QStringLiteral("move_s"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("670"), QStringLiteral("996"), QStringLiteral("-49"), QStringLiteral("59"), QStringLiteral("192")}
            , {QStringLiteral("move_i"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("671"), QStringLiteral("1152"), QStringLiteral("-5446"), QStringLiteral("210"), QStringLiteral("192")}
            , {QStringLiteral("move_f"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("672"), QStringLiteral("1148"), QStringLiteral("63"), QStringLiteral("61"), QStringLiteral("192")}
            , {QStringLiteral("move_r"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("673"), QStringLiteral("-1224"), QStringLiteral("-162"), QStringLiteral("14"), QStringLiteral("64")}
            , {QStringLiteral("move_u"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("674"), QStringLiteral("-443"), QStringLiteral("-906"), QStringLiteral("140"), QStringLiteral("112")}
            , {QStringLiteral("move_d"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("675"), QStringLiteral("752"), QStringLiteral("-371"), QStringLiteral("92"), QStringLiteral("160")}
            , {QStringLiteral("hyou7"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("676"), QStringLiteral("238"), QStringLiteral("-308"), QStringLiteral("410"), QStringLiteral("132")}
            , {QStringLiteral("hyou8_1"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("677"), QStringLiteral("-242"), QStringLiteral("2345"), QStringLiteral("112"), QStringLiteral("128")}
            , {QStringLiteral("hyou8_2"), QT_TR_NOOP("Cave"), QStringLiteral("1"), QStringLiteral("678"), QStringLiteral("-16"), QStringLiteral("422"), QStringLiteral("14"), QStringLiteral("192")}
            , {QStringLiteral("hyou9"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("679"), QStringLiteral("1421"), QStringLiteral("4048"), QStringLiteral("10"), QStringLiteral("0")}

            , {QStringLiteral("hyou10"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("680"), QStringLiteral("373"), QStringLiteral("-426"), QStringLiteral("259"), QStringLiteral("120")}
            , {QStringLiteral("hyou11"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("681"), QStringLiteral("-719"), QStringLiteral("-14"), QStringLiteral("96"), QStringLiteral("76")}
            , {QStringLiteral("hyou12"), QT_TR_NOOP("Cave"), QStringLiteral("1"), QStringLiteral("682"), QStringLiteral("256"), QStringLiteral("742"), QStringLiteral("0"), QStringLiteral("184")}
            , {QStringLiteral("hyou13_1"), QT_TR_NOOP("Great Glacier"), QStringLiteral("1"), QStringLiteral("683"), QStringLiteral("-805"), QStringLiteral("2884"), QStringLiteral("27"), QStringLiteral("0")}
            , {QStringLiteral("hyou13_2"), QT_TR_NOOP("Cave"), QStringLiteral("1"), QStringLiteral("684"), QStringLiteral("-53"), QStringLiteral("423"), QStringLiteral("40"), QStringLiteral("64")}
            , {QStringLiteral("gaiafoot"), QT_TR_NOOP("Base of Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("686"), QStringLiteral("80"), QStringLiteral("-364"), QStringLiteral("24"), QStringLiteral("192")}
            , {QStringLiteral("holu_1"), QT_TR_NOOP("Base of Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("687"), QStringLiteral("165"), QStringLiteral("51"), QStringLiteral("5"), QStringLiteral("32")}
            , {QStringLiteral("holu_2"), QT_TR_NOOP("Base of Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("688"), QStringLiteral("159"), QStringLiteral("-62"), QStringLiteral("10"), QStringLiteral("128")}
            , {QStringLiteral("gaia_1"), QT_TR_NOOP("Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("689"), QStringLiteral("-203"), QStringLiteral("-814"), QStringLiteral("1"), QStringLiteral("128")}

            , {QStringLiteral("gaiin_1"), QT_TR_NOOP("Inside of Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("690"), QStringLiteral("-664"), QStringLiteral("-864"), QStringLiteral("151"), QStringLiteral("128")}
            , {QStringLiteral("gaiin_2"), QT_TR_NOOP("Inside of Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("691"), QStringLiteral("11"), QStringLiteral("-535"), QStringLiteral("160"), QStringLiteral("128")}
            , {QStringLiteral("gaia_2"), QT_TR_NOOP("Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("692"), QStringLiteral("-477"), QStringLiteral("-132"), QStringLiteral("19"), QStringLiteral("128")}
            , {QStringLiteral("gaiin_3"), QT_TR_NOOP("Inside of Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("693"), QStringLiteral("-109"), QStringLiteral("1123"), QStringLiteral("65"), QStringLiteral("32")}
            , {QStringLiteral("gaia_31"), QT_TR_NOOP("Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("694"), QStringLiteral("-631"), QStringLiteral("1107"), QStringLiteral("27"), QStringLiteral("128")}
            , {QStringLiteral("gaia_32"), QT_TR_NOOP("Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("695"), QStringLiteral("-990"), QStringLiteral("-28017"), QStringLiteral("31"), QStringLiteral("64")}
            , {QStringLiteral("gaiin_4"), QT_TR_NOOP("Inside of Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("696"), QStringLiteral("255"), QStringLiteral("-4160"), QStringLiteral("3"), QStringLiteral("128")}
            , {QStringLiteral("gaiin_5"), QT_TR_NOOP("Inside of Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("697"), QStringLiteral("664"), QStringLiteral("1099"), QStringLiteral("38"), QStringLiteral("192")}
            , {QStringLiteral("gaiin_6"), QT_TR_NOOP("Inside of Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("698"), QStringLiteral("-11"), QStringLiteral("2455"), QStringLiteral("8"), QStringLiteral("0")}
            , {QStringLiteral("gainn_7"), QT_TR_NOOP("Inside of Gaea's Cliff"), QStringLiteral("1"), QStringLiteral("699"), QStringLiteral("-116"), QStringLiteral("265"), QStringLiteral("17"), QStringLiteral("32")}

            , {QStringLiteral("crater_1"), QT_TR_NOOP("Crater"), QStringLiteral("1"), QStringLiteral("700"), QStringLiteral("910"), QStringLiteral("-321"), QStringLiteral("54"), QStringLiteral("192")}
            , {QStringLiteral("crater_2"), QT_TR_NOOP("Crater"), QStringLiteral("1"), QStringLiteral("701"), QStringLiteral("650"), QStringLiteral("79"), QStringLiteral("65"), QStringLiteral("192")}
            , {QStringLiteral("trnad_1"), QT_TR_NOOP("Whirlwind Maze"), QStringLiteral("1"), QStringLiteral("702"), QStringLiteral("-72"), QStringLiteral("43"), QStringLiteral("32"), QStringLiteral("128")}
            , {QStringLiteral("trnad_2"), QT_TR_NOOP("Whirlwind Maze"), QStringLiteral("1"), QStringLiteral("703"), QStringLiteral("-358"), QStringLiteral("-1056"), QStringLiteral("44"), QStringLiteral("32")}
            , {QStringLiteral("trnad_3"), QT_TR_NOOP("Whirlwind Maze"), QStringLiteral("1"), QStringLiteral("704"), QStringLiteral("619"), QStringLiteral("-3548"), QStringLiteral("3"), QStringLiteral("176")}
            , {QStringLiteral("trnad_4"), QT_TR_NOOP("Whirlwind Maze"), QStringLiteral("1"), QStringLiteral("705"), QStringLiteral("94"), QStringLiteral("1168"), QStringLiteral("173"), QStringLiteral("32")}
            , {QStringLiteral("woa_1"), QT_TR_NOOP("Whirlwind Maze"), QStringLiteral("1"), QStringLiteral("709"), QStringLiteral("121"), QStringLiteral("-536"), QStringLiteral("3"), QStringLiteral("128")}

            , {QStringLiteral("woa_2"), QT_TR_NOOP("Whirlwind Maze"), QStringLiteral("1"), QStringLiteral("710"), QStringLiteral("123"), QStringLiteral("-503"), QStringLiteral("41"), QStringLiteral("128")}
            , {QStringLiteral("woa_3"), QT_TR_NOOP("Whirlwind Maze"), QStringLiteral("1"), QStringLiteral("711"), QStringLiteral("170"), QStringLiteral("-339"), QStringLiteral("68"), QStringLiteral("128")}
            , {QStringLiteral("itown1a"), QT_TR_NOOP("Mideel"), QStringLiteral("1"), QStringLiteral("712"), QStringLiteral("-64"), QStringLiteral("-2225"), QStringLiteral("63"), QStringLiteral("128")}
            , {QStringLiteral("itown1b"), QT_TR_NOOP("Mideel"), QStringLiteral("1"), QStringLiteral("714"), QStringLiteral("-67"), QStringLiteral("-885"), QStringLiteral("123"), QStringLiteral("0")}
            , {QStringLiteral("itown_w"), QT_TR_NOOP("Mideel,Weapon Store"), QStringLiteral("1"), QStringLiteral("717"), QStringLiteral("36"), QStringLiteral("-236"), QStringLiteral("32"), QStringLiteral("128")}
            , {QStringLiteral("itown_i"), QT_TR_NOOP("Mideel,Item Store"), QStringLiteral("1"), QStringLiteral("718"), QStringLiteral("-90"), QStringLiteral("-159"), QStringLiteral("3"), QStringLiteral("128")}
            , {QStringLiteral("itown_m"), QT_TR_NOOP("Mideel,Materia Store"), QStringLiteral("1"), QStringLiteral("719"), QStringLiteral("34"), QStringLiteral("-211"), QStringLiteral("3"), QStringLiteral("128")}

            , {QStringLiteral("ithos"), QT_TR_NOOP("Mideel,Clinic"), QStringLiteral("1"), QStringLiteral("720"), QStringLiteral("151"), QStringLiteral("-156"), QStringLiteral("19"), QStringLiteral("32")}
            , {QStringLiteral("itmin1"), QT_TR_NOOP("Mideel,House1"), QStringLiteral("1"), QStringLiteral("721"), QStringLiteral("-158"), QStringLiteral("-183"), QStringLiteral("17"), QStringLiteral("96")}
            , {QStringLiteral("itmin2"), QT_TR_NOOP("Mideel,House2"), QStringLiteral("1"), QStringLiteral("722"), QStringLiteral("-53"), QStringLiteral("-110"), QStringLiteral("19"), QStringLiteral("96")}
            , {QStringLiteral("zmind1"), QString(), QStringLiteral("1"), QStringLiteral("725"), QStringLiteral("170"), QStringLiteral("-9200"), QStringLiteral("92"), QStringLiteral("96")}
            , {QStringLiteral("zmind2"), QString(), QStringLiteral("1"), QStringLiteral("726"), QStringLiteral("3826"), QStringLiteral("-3110"), QStringLiteral("22"), QStringLiteral("96")}
            , {QStringLiteral("zmind3"), QString(), QStringLiteral("1"), QStringLiteral("727"), QStringLiteral("-4725"), QStringLiteral("-344"), QStringLiteral("85"), QStringLiteral("96")}
            , {QStringLiteral("zcoal_2"), QT_TR_NOOP("Coal Train"), QStringLiteral("1"), QStringLiteral("729"), QStringLiteral("789"), QStringLiteral("200"), QStringLiteral("0"), QStringLiteral("0")}

            , {QStringLiteral("md8_5"), QT_TR_NOOP("8th Street"), QStringLiteral("1"), QStringLiteral("731"), QStringLiteral("-274"), QStringLiteral("-93"), QStringLiteral("40"), QStringLiteral("0")}
            , {QStringLiteral("md8_6"), QT_TR_NOOP("Midgar, Sector 8"), QStringLiteral("1"), QStringLiteral("732"), QStringLiteral("265"), QStringLiteral("-204"), QStringLiteral("24"), QStringLiteral("32")}
            , {QStringLiteral("md8_b1"), QT_TR_NOOP("Sector 8, Underground"), QStringLiteral("1"), QStringLiteral("733"), QStringLiteral("-272"), QStringLiteral("1614"), QStringLiteral("116"), QStringLiteral("32")}
            , {QStringLiteral("md8_b2"), QT_TR_NOOP("Sector 8, Underground"), QStringLiteral("1"), QStringLiteral("734"), QStringLiteral("-2860"), QStringLiteral("-371"), QStringLiteral("126"), QStringLiteral("192")}
            , {QStringLiteral("sbwy4_22"), QT_TR_NOOP("Sector 8, Underground"), QStringLiteral("1"), QStringLiteral("735"), QStringLiteral("0"), QStringLiteral("-57"), QStringLiteral("9"), QStringLiteral("128")}
            , {QStringLiteral("tunnel_4"), QT_TR_NOOP("Winding Tunnel"), QStringLiteral("1"), QStringLiteral("736"), QStringLiteral("-83"), QStringLiteral("-229"), QStringLiteral("215"), QStringLiteral("32")}
            , {QStringLiteral("tunnel_5"), QT_TR_NOOP("Winding Tunnel"), QStringLiteral("1"), QStringLiteral("737"), QStringLiteral("42"), QStringLiteral("1369"), QStringLiteral("41"), QStringLiteral("0")}
            , {QStringLiteral("md8brdg2"), QT_TR_NOOP("Midgar, Sector 8"), QStringLiteral("1"), QStringLiteral("738"), QStringLiteral("-526"), QStringLiteral("-995"), QStringLiteral("92"), QStringLiteral("128")}
            , {QStringLiteral("md8_32"), QT_TR_NOOP("Midgar, Sector 8"), QStringLiteral("1"), QStringLiteral("739"), QStringLiteral("-4097"), QStringLiteral("18394"), QStringLiteral("34"), QStringLiteral("32")}

            , {QStringLiteral("canon_1"), QT_TR_NOOP("Mako Cannon"), QStringLiteral("1"), QStringLiteral("740"), QStringLiteral("877"), QStringLiteral("-2016"), QStringLiteral("31"), QStringLiteral("192")}
            , {QStringLiteral("canon_2"), QT_TR_NOOP("Mako Cannon"), QStringLiteral("1"), QStringLiteral("741"), QStringLiteral("0"), QStringLiteral("-601"), QStringLiteral("80"), QStringLiteral("160")}
            , {QStringLiteral("las0_1"), QT_TR_NOOP("Highwind, on deck"), QStringLiteral("1"), QStringLiteral("744"), QStringLiteral("-33"), QStringLiteral("-1419"), QStringLiteral("277"), QStringLiteral("100")}
            , {QStringLiteral("las0_2"), QT_TR_NOOP("Northern Cave Crater"), QStringLiteral("1"), QStringLiteral("745"), QStringLiteral("-496"), QStringLiteral("-959"), QStringLiteral("51"), QStringLiteral("168")}
            , {QStringLiteral("las0_3"), QT_TR_NOOP("Northern Cave"), QStringLiteral("1"), QStringLiteral("746"), QStringLiteral("681"), QStringLiteral("1212"), QStringLiteral("115"), QStringLiteral("0")}
            , {QStringLiteral("las0_4"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("747"), QStringLiteral("-33"), QStringLiteral("1030"), QStringLiteral("190"), QStringLiteral("212")}
            , {QStringLiteral("las0_5"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("748"), QStringLiteral("-47"), QStringLiteral("-64"), QStringLiteral("24"), QStringLiteral("32")}
            , {QStringLiteral("las0_6"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("749"), QStringLiteral("-192"), QStringLiteral("16"), QStringLiteral("35"), QStringLiteral("32")}

            , {QStringLiteral("las0_7"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("750"), QStringLiteral("-711"), QStringLiteral("315"), QStringLiteral("190"), QStringLiteral("64")}
            , {QStringLiteral("las0_8"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("751"), QStringLiteral("-1953"), QStringLiteral("-422"), QStringLiteral("31"), QStringLiteral("32")}
            , {QStringLiteral("las1_1"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("752"), QStringLiteral("-419"), QStringLiteral("-75"), QStringLiteral("40"), QStringLiteral("16")}
            , {QStringLiteral("las1_2"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("753"), QStringLiteral("54"), QStringLiteral("-165"), QStringLiteral("9"), QStringLiteral("72")}
            , {QStringLiteral("las1_3"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("754"), QStringLiteral("664"), QStringLiteral("800"), QStringLiteral("72"), QStringLiteral("112")}
            , {QStringLiteral("las1_4"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("755"), QStringLiteral("314"), QStringLiteral("5"), QStringLiteral("0"), QStringLiteral("112")}
            , {QStringLiteral("las2_1"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("756"), QStringLiteral("646"), QStringLiteral("48"), QStringLiteral("86"), QStringLiteral("192")}
            , {QStringLiteral("las2_2"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("757"), QStringLiteral("123"), QStringLiteral("-732"), QStringLiteral("124"), QStringLiteral("192")}
            , {QStringLiteral("las2_3"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("758"), QStringLiteral("120"), QStringLiteral("-650"), QStringLiteral("17"), QStringLiteral("144")}
            , {QStringLiteral("las2_4"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("759"), QStringLiteral("1187"), QStringLiteral("162"), QStringLiteral("12"), QStringLiteral("212")}

            , {QStringLiteral("las3_1"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("760"), QStringLiteral("523"), QStringLiteral("-702"), QStringLiteral("51"), QStringLiteral("16")}
            , {QStringLiteral("las3_2"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("761"), QStringLiteral("467"), QStringLiteral("-459"), QStringLiteral("308"), QStringLiteral("16")}
            , {QStringLiteral("las3_3"), QT_TR_NOOP("Inside Northern Cave"), QStringLiteral("1"), QStringLiteral("762"), QStringLiteral("447"), QStringLiteral("-243"), QStringLiteral("28"), QStringLiteral("64")}
            , {QStringLiteral("las4_0"), QT_TR_NOOP("Bottom of Northern Cave"), QStringLiteral("1"), QStringLiteral("763"), QStringLiteral("102"), QStringLiteral("-856"), QStringLiteral("31"), QStringLiteral("32")}
            , {QStringLiteral("las4_1"), QT_TR_NOOP("Bottom of Northern Cave"), QStringLiteral("1"), QStringLiteral("764"), QStringLiteral("208"), QStringLiteral("-481"), QStringLiteral("103"), QStringLiteral("128")}
            , {QStringLiteral("las4_2"), QT_TR_NOOP("Inside the Planet"), QStringLiteral("1"), QStringLiteral("765"), QStringLiteral("-69"), QStringLiteral("562"), QStringLiteral("96"), QStringLiteral("64")}
            , {QStringLiteral("las4_3"), QT_TR_NOOP("Inside the Planet"), QStringLiteral("1"), QStringLiteral("766"), QStringLiteral("-808"), QStringLiteral("-56"), QStringLiteral("81"), QStringLiteral("96")}
            , {QStringLiteral("las4_4"), QString(), QStringLiteral("1"), QStringLiteral("767"), QStringLiteral("406"), QStringLiteral("944"), QStringLiteral("43"), QStringLiteral("96")}
            , {QStringLiteral("lastmap"), QT_TR_NOOP("????"), QStringLiteral("1"), QStringLiteral("768"), QStringLiteral("61"), QStringLiteral("-386"), QStringLiteral("179"), QStringLiteral("116")}

            , {QStringLiteral("hill2"), QString(), QStringLiteral("1"), QStringLiteral("771"), QStringLiteral("-50"), QStringLiteral("-24"), QStringLiteral("284"), QStringLiteral("56")}
            , {QStringLiteral("las4_42"), QString(), QStringLiteral("1"), QStringLiteral("777"), QStringLiteral("406"), QStringLiteral("945"), QStringLiteral("43"), QStringLiteral("96")}
            , {QStringLiteral("tunnel_6"), QT_TR_NOOP("Winding Tunnel"), QStringLiteral("1"), QStringLiteral("778"), QStringLiteral("166"), QStringLiteral("-376"), QStringLiteral("106"), QStringLiteral("128")}
        };
    };
};
