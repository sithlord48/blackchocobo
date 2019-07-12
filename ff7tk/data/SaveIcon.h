/****************************************************************************
 **
 ** Copyright (C) 2010 Arzel Jérôme <myst6re@gmail.com>
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#ifndef DEF_SAVEICON
#define DEF_SAVEICON

#include <QByteArray>
#include <QList>
#include <QPixmap>
#include <QTimer>

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
     * \return Icon Data
     */
    const QByteArray &save();

    /** \brief incase you wish to write the icon to a file
     * \return Icon As QByteArray
     * \sa save()
    */
    [[deprecated]] QByteArray sauver();

    /** \brief pixmap of your icon
     * \param chocobo_world_icon is this an icon for chocoboworld?
     * \return psx SaveIcon as A QPixmap
    */
    QPixmap icon(bool chocobo_world_icon = false);
signals:
    void nextIcon(QPixmap); /**< \brief Emit Signal: Time to update your QPixmap. connect to object your displaying on to tell it time for a new icon.*/
private slots:
    void nextFrame(); /**< \brief get get next icon if more then one frame */
private:
    QByteArray data; /**< \brief hold our icon data */
    quint8 nbFrames;/**< \brief number of frames */
    quint8 curFrame = 0; /**< \brief current Frame*/
    static QTimer timer; /**< \brief frame change timer.*/
};

#endif
