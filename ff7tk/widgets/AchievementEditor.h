/****************************************************************************/
//    copyright 2013 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
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
#ifndef ACHIEVEMENTEDITOR_H
#define ACHIEVEMENTEDITOR_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	#include <QtWidgets>
#else
	#include <QtGui>
#endif

#include "../data/FF7Achievements.h"

/*!	\class AchievementEditor
 *	\brief A QWidget editor for achievements.dat file from 2012 and 2013 release of Final Fantasy 7.
 *
 *	This widget uses FF7Achievements to do everything for us we only need to tell it what file to open and what file to save.
 *	The list will contain icons for each achievement so be sure to include achievements.qrc in your projects resources
 *	The end user only ever needs to see a list the rest sholud be set to signals/slots in the host application
 */

class AchievementEditor : public QWidget
{
	Q_OBJECT
public:
	explicit AchievementEditor(qreal Scale=1,QWidget *parent=0); /**< \brief create a new AchievementEditor */
public slots:
	/*!	\brief open a file.
	 *	\param fileName an achievements.dat file that you want to open
	 *	\return TRUE if successful while attempting to open the file
	 *	\sa openFile()
	 */
	bool openFile(QString fileName="");

	/*!	\brief saves a file.
	 *	\param fileName an achievements.dat file that you want to save
	 *	\return TRUE if successful while attempting to write the file
	 *	\sa saveFile()
	 */
	bool saveFile(QString fileName="");
private slots:
	/*! \brief an item has been toggled
	 *  \param index QModeIndex from where the change occored
	 */
	void itemToggled(QModelIndex index);
private:
	void initDisplay(void); /**< \brief create this items widgets*/
	void initConnect(void); /**< \brief Connect objects */
	void initDisconnect(void); /**< \brief Disconnect object*/
	FF7Achievements achievements; /**< \brief data class for widget*/
	QListWidget *achievementList; /**< \brief QListWidget that will contain the list of achievements.*/
	qreal scale; /**< \brief Scale value for hidpi systems. */
};

#endif // ACHIEVEMENTEDITOR_H
