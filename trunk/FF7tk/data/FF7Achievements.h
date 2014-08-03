/****************************************************************************/
//    copyright 2013 -2014  Chris Rizzitello <sithlord48@gmail.com>         //
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

#ifndef FF7ACHIEVEMENTS_H
#define FF7ACHIEVEMENTS_H
#include <QObject>
/*!
 * \class FF7Achievements
 * \todo need more icons for the achievements.
 * \brief Work with achievements.dat
 *
 * Open Edit and Save achievements.dat found with the 2012 Square and 2013 Steam Releases of Final Fantasy VII
*/

class FF7Achievements : public QObject
{
	Q_OBJECT
	public:
		/*! \brief Create a new FF7 Achievements
		*
		* Creates a new FF7Achievements object with data set to an 8byte file of 0x00
		*/
		explicit FF7Achievements(QObject *parent = 0);

		/*! \brief Attempt to Open a file.
		* Open a file and replace data with its contents.
		* \param fileName file you want to open
		* \return True is successful
		* \sa saveFile()
		*/
		bool openFile(QString fileName="");

		/*! \brief Attempt to save a file.
		 * Write data to a file
		 * \param fileName file you want to open
		 * \return TRUE if successful
		 * \sa openFile()
		*/
		bool saveFile(QString fileName="");

		/*!	\brief is Achievement @ bit unlocked?
		 *	 \param bit (28-63 are valid)
		 *	 \return TRUE for Achievement unlocked
		 *	\sa setAchievementUnlocked()
		*/
		bool achievmentUnlocked(int bit);

		/*! \brief set Achievement @ bit to unlocked
			\param bit (28-63 are valid)
			\param unlocked  True for Achievement Unlocked
			\sa achievmentUnlocked()
		*/
		void setAchievementUnlocked(int bit,bool unlocked);

		/*!	\brief Translate name for Achievement bit
			\param bit (28-63 are valid)
			\return Translated QString of Achievement Name.
		*/
		QString name(int bit);
	private:
		QByteArray Achievements; /**< Hold our Achievements.dat */
};
#endif // FF7ACHIEVEMENTS_H
