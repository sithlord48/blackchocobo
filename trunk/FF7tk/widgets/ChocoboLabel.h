/****************************************************************************/
//    copyright 2013  Chris Rizzitello <sithlord48@gmail.com>               //
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
#ifndef CHOCOBOLABEL_H
#define CHOCOBOLABEL_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif

class ChocoboLabel : public QWidget
{
    Q_OBJECT
public:
    explicit ChocoboLabel(QWidget *parent = 0,QString titleText="",bool occupied=false);
    void setCheckBoxStyle(QString styleSheet);
signals:
    void clicked();
    void copy();
    void paste();
    void remove();
    void occupiedToggled(bool occupied);
public slots:
    void setSelected(bool selected);
    void setType(int type);
    void setName(QString decodedName);
    void setRank(int wins);
    void setSex(bool Male);
    void setSex(int sex);
    void setOccupied(bool occupied);
    void setTitle(QString title);
    void setFontSize(int fontSize);
    void clearLabel(void);
    bool isOccupied(void);
    void setHoverColorStyle(QString backgroundColor);
private slots:
    void chkOccupiedToggled(bool occupied);
    void copyPushed(void);
    void pastePushed(void);
    void removePushed(void);
private:
  bool event(QEvent *ev);
  void enable(bool);
  bool isEnabled;
  QPushButton *btnCopy;
  QPushButton *btnPaste;
  QPushButton *btnRemove;
  QCheckBox *chkOccupied;
  QLabel *lblType;
  QLabel *lblName;
  QLabel *lblRank;
  QLabel *lblSex;
  QFrame *innerFrame;
  QFrame *outerFrame;
  QString SelectedBkStyle;
};

#endif // ChocoboLABEL_H
