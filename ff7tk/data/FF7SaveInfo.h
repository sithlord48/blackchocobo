/****************************************************************************/
//    copyright 2019  Chris Rizzitello <sithlord48@gmail.com>         //
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
#include <QQmlEngine>

class FF7SaveInfo : public QObject
{
    Q_OBJECT
public:
    /**
     * \enum FORMAT
     * \brief Supported Data Types
     */
    enum class FORMAT {
        UNKNOWN = -1, //!< UNKNOWN FORMAT
        PSX = 0,  //!< PSX Save Data
        PC,       //!< PC Save Format
        VMC,      //!< Virtual Memory Card
        PSP,      //!< PSP Save Format
        PS3,      //!< PS3 Save Format
        DEX,      //!< Dex Format
        VGS,      //!< VGS Format
    };
    Q_ENUM(FORMAT)

    /** \enum PSXBLOCKTYPE
     *  \brief Used to set the type of block on a PSX memory card (image) when creating the index.
     */
    enum class PSXBLOCKTYPE : char {
        BLOCK_EMPTY = '\xA0', /**< 0xA0*/
        BLOCK_INUSE = '\x51', /**< 0x51*/
        BLOCK_DELETED = '\xA1', /**< 0xA1*/
        BLOCK_MIDLINK = '\x52', /**< 0x52*/
        BLOCK_DELETED_MIDLINK = '\xA2', /**< 0xA2*/
        BLOCK_ENDLINK = '\x53', /**< 0x53*/
        BLOCK_DELETED_ENDLINK = '\xA3', /**< 0xA3*/
    };
    Q_ENUM(PSXBLOCKTYPE)

    /**
     * @brief Get the FF7SaveInfo Instance.
     * @sa qmlSingletonRegister()
     */
    static FF7SaveInfo *instance();

    /**
     * @brief Register The FF7SaveInfo Singleton for QML
     */
    QObject *qmlSingletonRegister(QQmlEngine *engine, QJSEngine *scriptEngine);

    /**
     * @brief The Size of a Final Fantasy VII Save file
     * @param format : The Save Format you wish to know about
     * @return size of Filetype
     */
    Q_INVOKABLE int fileSize(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Size of the format's file header
     * @param format : The Save Format you wish to know about
     * @return size of File Header
     */
    Q_INVOKABLE int fileHeaderSize(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Size of the format's slot header
     * @param format : The Save Format you wish to know about
     * @return size of slotHeader
     */
    Q_INVOKABLE int slotHeaderSize(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Size of the format's slot footer
     * @param format : The Save Format you wish to know about
     * @return size of slotFooter
     */
    Q_INVOKABLE int slotFooterSize(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Number of save slots in format
     * @param format : The Save Format you wish to know about
     * @return number of save slots in format.
     */
    Q_INVOKABLE int slotCount(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Magic Numbers for Final Fantasy VII Save Files
     * @param format : The Save Format
     * @return Magic Numbers for this file type
     */
    Q_INVOKABLE QByteArray fileIdentifier(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Standard File Header for Format
     * @param format
     * @return A Default File header
     */
    Q_INVOKABLE QByteArray fileHeader(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Standard Slot Header for Format
     * @param format
     * @param slot: the slot value to use (PSX ICON)
     * @return A Default File header
     */
    Q_INVOKABLE QByteArray slotHeader(FF7SaveInfo::FORMAT format, int slot = 0) const;

    /**
     * @brief Standard Slot Footer for Format
     * @param format
     * @return A Default File header
     */
    Q_INVOKABLE QByteArray slotFooter(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Standard Slot Footer for Format
     * @param format
     * @return A Default File header
     */
    Q_INVOKABLE QString typeString(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Size of an FF7Save
     * @return
     */
    Q_INVOKABLE int slotSize() const;

private:
    FF7SaveInfo *operator = (FF7SaveInfo &other) = delete;
    FF7SaveInfo(const FF7SaveInfo &other) = delete;
    explicit FF7SaveInfo(QObject *parent = nullptr);
    ~FF7SaveInfo();
    struct FF7SaveInfoPrivate;
    FF7SaveInfoPrivate *d;
};
