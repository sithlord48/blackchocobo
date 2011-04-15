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

#include <QtGui>

class SaveIcon : public QObject
{
	Q_OBJECT
public:
	SaveIcon();
	SaveIcon(QByteArray data, quint8 nbFrames=1);
	//~SaveIcon();
	void setAll(QByteArray data, quint8 nbFrames=1);
	QByteArray sauver();
	QPixmap icon(bool chocobo_world_icon=false);
signals:
	void nextIcon(QPixmap);
private slots:
	void nextFrame();
private:
	QByteArray data;
	quint8 nbFrames, curFrame;
	static QTimer timer;
};

#endif
