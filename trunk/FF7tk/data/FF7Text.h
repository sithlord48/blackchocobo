/****************************************************************************/
//    copyright 2012-2014 Chris Rizzitello <sithlord48@gmail.com>           //
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
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#ifndef FF7TEXT_H
  #define FF7TEXT_H
#include <QObject>

/*! \class FF7TEXT
 * \brief Convert ff7text <-> pc string
 */
class FF7TEXT{
  //  Q_OBJECT
public:
	FF7TEXT();

	/*! \brief if TRUE toPC will return Japanese test  */
	void init(bool);

	/*! \brief convert ff7text to pc string
	 * 	\param text the raw ff7text to read
	 *  \return decoded ff7text
	 */
	QString toPC(QByteArray text);

	/*! \brief convert pc string to ff7text
	 * 	\param string the raw ff7text to read
	 *  \return decoded ff7text
	 */
	QByteArray toFF7(QString string);
private:
	QString eng; /**< character table for latin */
	QString jap; /**< character table #1 for japanese */
	QString jap_fa; /**< character table #2 for japanese */
	QString jap_fb; /**< character table #3 for japanese */
	QString jap_fc; /**< character table #4 for japanese */
	QString jap_fd; /**< character table #5 for japanese */
	QString jap_fe; /**< character table #6 for japanese */
	bool in_ja; /**< if true toPC will give us japanese characters*/
	QString character(quint8 ord, quint8 table); /** convert a single character*/
};
#endif //FF7TEXT_H
