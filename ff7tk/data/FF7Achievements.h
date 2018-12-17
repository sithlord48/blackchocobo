/****************************************************************************/
//    copyright 2013 - 2018  Chris Rizzitello <sithlord48@gmail.com>        //
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
        FF7Achievements() = default;
        ~FF7Achievements() = default;
		/*! \brief Attempt to Open a file.
		* Open a file and replace data with its contents.
		* \param fileName file you want to open
		* \return True is successful
		* \sa saveFile()
		*/
        Q_INVOKABLE bool openFile(const QString &fileName);

		/*! \brief Attempt to save a file.
		 * Write data to a file
		 * \param fileName file you want to open
		 * \return TRUE if successful
		 * \sa openFile()
		*/
        Q_INVOKABLE bool saveFile(const QString &fileName);

		/*!	\brief is Achievement @ bit unlocked?
		 *	 \param bit (28-63 are valid)
		 *	 \return TRUE for Achievement unlocked
		 *	\sa setAchievementUnlocked()
		*/
        Q_INVOKABLE bool achievmentUnlocked(int bit);

		/*! \brief set Achievement @ bit to unlocked
			\param bit (28-63 are valid)
			\param unlocked  True for Achievement Unlocked
			\sa achievmentUnlocked()
		*/
        Q_INVOKABLE void setAchievementUnlocked(int bit,bool unlocked);

		/*!	\brief Translate name for Achievement bit
			\param bit (28-63 are valid)
			\return Translated QString of Achievement Name.
		*/
        Q_INVOKABLE QString name(int bit);
private:
    QByteArray _achievements = QByteArray(8, '\x00');/**< Hold our Achievements.dat */
    inline static const auto _group = QStringLiteral("Achievement_Names");
    inline static const QStringList _names{
        QT_TRANSLATE_NOOP(_group, QStringLiteral("Dice"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Sled Fang"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Greased Lightning"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Beat Rush"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Boost Jump"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Healing Wind"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Galian Beast"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Big Shot"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Braver"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("First Battle"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Gold Chocobo"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Battle Square"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Materia Overlord"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Yuffie"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Vincent"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Emerald Weapon"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Ruby Weapon"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Diamond Weapon"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Ultimate Weapon"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Bahamut Zero"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Slots"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Cosmo Memory"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("All Creation"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Final Heaven"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Highwind"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Great Gospel"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Chaos"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Catastrophe"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Omnislash"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Knights of the Round"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Top Level"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Master of Gil"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("Master Materia"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("End of Game"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("End of Part II"))
        , QT_TRANSLATE_NOOP(_group, QStringLiteral("End of Part I"))
    };
};
