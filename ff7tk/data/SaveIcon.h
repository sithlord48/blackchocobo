/****************************************************************************/
//    copyright 2010 Arzel Jérôme <myst6re@gmail.com>                       //
//              2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>         //
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
#include <QPixmap>

/** \class SaveIcon
 *  \brief PSX icon data as a QPixmap
 */
class SaveIcon : public QObject
{
    Q_OBJECT
public:
    /** \brief create a new Save icon*/
    SaveIcon();

    /**
     * \brief create a new Save icon with data
     * \param data psx saveicon data
     * \param nbFrames number of frames icon has (1-3)
     * */
    SaveIcon(const QByteArray &data, quint8 nbFrames = 1);

    /**
     * \brief create a new Save icon with data
     * \param data psx saveicon one frame pre list item
    */
    SaveIcon(const QList<QByteArray> &data);

    /**
     * \brief fill SaveIcon with data
     * \param data psx saveicon data
     * \param nbFrames number of frames in icon (1-3)
    */
    void setAll(const QByteArray &data, quint8 nbFrames = 1);

    /** \brief fill SaveIcon with data
     * \param data psx saveicon one frame pre list item.
     */
    void setAll(const QList<QByteArray> &data);

    /*!
     * \brief Save the icon.
     * \return Icon Data as QByteArray
     */
    const QByteArray &save();

    /** \brief pixmap of your icon
     * \param chocobo_world_icon is this an icon for chocoboworld?
     * \return psx SaveIcon as A QPixmap
    */
    QPixmap icon(bool chocobo_world_icon = false);
signals:
    void nextIcon(QPixmap); /**< \brief Emit Signal: Time to update your QPixmap. connect to object your displaying on to tell it time for a new icon.*/
private:

    /** \brief Helper function for chocobo World Icons.
     * \return chocobo World Icon as A QPixmap
    */
    QPixmap chocoWorldIcon();

    /** \brief Helper function for psx SaveIcons
     * \return psx SaveIcon as A QPixmap
    */
    void nextFrame(); /**< \brief get get next icon if more then one frame */
    QPixmap psxIcon();
    QByteArray m_data; /**< \brief hold our icon data */
    quint8 m_nbFrames;/**< \brief number of frames */
    quint8 m_curFrame = 0; /**< \brief current Frame*/
    static QTimer m_timer; /**< \brief frame change timer.*/
};
