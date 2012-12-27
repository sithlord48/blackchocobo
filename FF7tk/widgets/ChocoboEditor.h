/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
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
#ifndef CHOCOBOEDITOR_H
#define CHOCOBOEDITOR_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif

//Be sure to set paths correctly for below.
//ALSO CHECK ChocoboEditor.cpp for icons includes.
#include "../static_data/FF7Save_Types.h"

class ChocoboEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ChocoboEditor(QWidget *parent = 0);
    void SetChocobo(FF7CHOCOBO choco,QString Processed_Name="",bool cant_mate=false, quint16 stamina=0);
    quint16 sprint(void);
    quint16 mSprint(void);
    quint16 speed(void);
    quint16 mSpeed(void);
    quint16 stamina(void);
    quint8 accel(void);
    quint8 coop(void);
    quint8 intelligence(void);
    quint8 personality(void);
    quint8 pCount(void);
    quint8 wins(void);
    quint8 sex(void);
    quint8 type(void);
    QString name(void);
    bool cantMate(void);
signals:    
    void sprint_changed(quint16);
    void mSprint_changed(quint16);
    void speed_changed(quint16);
    void mSpeed_changed(quint16);
    void stamina_changed(quint16);
    void accel_changed(quint8);
    void coop_changed(quint8);
    void intelligence_changed(quint8);
    void personality_changed(quint8);
    void pCount_changed(quint8);
    void wins_changed(quint8);
    void sex_changed(quint8);
    void type_changed(quint8);
    void name_changed(QString);
    void cantMate_changed(bool);
public slots:
   void setSprint(int);
   void setMsprint(int);
   void setSpeed(int);
   void setMspeed(int);
   void setStamina(int);
   void setAccel(int);
   void setCoop(int);
   void setIntelligence(int);
   void setPersonality (int);
   void setPcount(int);
   void setWins(int);
   void setSex(int);
   void setType(int);
   void setName(QString);
   void setCantMate(bool);

private:
    void init_display(void);
    void init_connections(void);
    void disconnectAll(void);
    //Widgets
    QComboBox *combo_sex;
    QComboBox *combo_type;
    QCheckBox *cb_cantMate;
    QLineEdit *line_name;
    QSpinBox *sb_speed;
    QSpinBox *sb_mSpeed;
    QSpinBox *sb_sprint;
    QSpinBox *sb_mSprint;
    QSpinBox *sb_stamina;
    QSpinBox *sb_accel;
    QSpinBox *sb_wins;
    QSpinBox *sb_coop;
    QSpinBox *sb_pCount;
    QSpinBox *sb_intel;
    QSpinBox *sb_personality;

    QLabel *lbl_sex;
    QLabel *lbl_type;
    QLabel *lbl_name;
    QLabel *lbl_speed;
    QLabel *lbl_div_speed;
    QLabel *lbl_stamina;
    QLabel *lbl_sprint;
    QLabel *lbl_div_sprint;
    QLabel *lbl_accel;
    QLabel *lbl_wins;
    QLabel *lbl_coop;
    QLabel *lbl_pCount;
    QLabel *lbl_intel;
    QLabel *lbl_personality;

    //Data
    FF7CHOCOBO choco_data;
    QString choco_name;
    bool choco_cant_mate;
    quint16 choco_stamina;
};

#endif // CHOCOBOEDITOR_H
