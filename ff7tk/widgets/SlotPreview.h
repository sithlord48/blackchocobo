/****************************************************************************/
//    copyright 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>         //
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

#include <QLabel>

class QHBoxLayout;
class QPushButton;
class QVBoxLayout;
class SaveIcon;

/** \class SlotPreview
 *  \brief Preview a Single Slot on a Psx memory card or FF7 Save file.
 *
 * Currently will display the "description" of FF7 Save or a preview of what psx save is in that slot. More games could be added by extending the modes
 */
class SlotPreview : public QLabel
{
    Q_OBJECT
public:
    /** \enum MODE */
    enum MODE {MODE_EMPTY,/**< \brief Empty Slot*/ MODE_PSXGAME, /**< \brief PSX Game or linked block */ MODE_FF7SAVE /**< \brief FF7 Save in slot*/ };
    SlotPreview(int index = 0, qreal Scale = 1, QWidget *parent = nullptr);
    int index(void);
    void setParty(QPixmap p1, QPixmap p2, QPixmap p3);
    void setParty(QString p1_style, QString p2_style, QString p3_style);
    void setName(QString);
    void setLevel(int);
    void setLocation(QString);
    void setGil(int);
    void setTime(int hour, int min);
    void setPsxIcon(QByteArray icon_data, quint8 frames = 1);
    void setPsxIcon(QList<QByteArray> icon_data);
    void setMode(int mode);

signals:
    void clicked(int); /**< \brief Signal: User Clicked on preview . \return index number */
    void btn_remove_clicked(int); /**< \brief Signal: User Clicked on remove . \return index number */
    void btn_copy_clicked(int); /**< \brief Signal: User Clicked on copy . \return index number */
    void btn_paste_clicked(int); /**< \brief Signal: User Clicked on paste . \return index number */

protected:
    void mousePressEvent(QMouseEvent *ev);

private:
    void init_display(void);
    void set_ff7_save(void);
    void set_empty(void);
    void set_psx_game(void);
    QLabel *party1 = nullptr;
    QLabel *party2 = nullptr;
    QLabel *party3 = nullptr;
    QLabel *name = nullptr;
    QLabel *lbl_Slot = nullptr;
    QLabel *lbl_time = nullptr;
    QLabel *lbl_level = nullptr;
    QLabel *location = nullptr;
    QLabel *lbl_gil = nullptr;
    QPushButton *btn_copy = nullptr;
    QPushButton *btn_paste = nullptr;
    QPushButton *btn_remove = nullptr;
    SaveIcon *icon = nullptr;
    QHBoxLayout *btnLayout = nullptr;
    QVBoxLayout *Final = nullptr;
    QVBoxLayout *top_layout = nullptr;
    qreal scale;
    int m_index;
    static inline QString _previewStyle = QStringLiteral(R"(SlotPreview{border: .5ex solid;}\nQPushButton{border: 1px solid})");
    static inline QString _genericStyle = QStringLiteral(R"(font: 75 16pt "Verdana"; color: white)");
    static inline QString _ff7SlotStyle = QStringLiteral(R"(background-color:rgba(0,0,0,0);font: 75 16pt "Verdana";color:white)");
    static inline QString _emptyTextStyle = QStringLiteral(R"(font: 75 20pt "Verdana"; color:yellow;)");
};
