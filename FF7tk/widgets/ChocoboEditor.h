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
#include "../static_data/Type_FF7CHOCOBO.h"

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
    void sprintChanged(quint16);
    void mSprintChanged(quint16);
    void speedChanged(quint16);
    void mSpeedChanged(quint16);
    void staminaChanged(quint16);
    void accelChanged(quint8);
    void coopChanged(quint8);
    void intelligenceChanged(quint8);
    void personalityChanged(quint8);
    void pCountChanged(quint8);
    void winsChanged(quint8);
    void sexChanged(quint8);
    void typeChanged(quint8);
    void nameChanged(QString);
    void cantMateChanged(bool);
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
   void setAdvancedMode(bool);
private slots:
   void SprintChanged(int);
   void MsprintChanged(int);
   void SpeedChanged(int);
   void MspeedChanged(int);
   void StaminaChanged(int);
   void AccelChanged(int);
   void CoopChanged(int);
   void IntelligenceChanged(int);
   void PersonalityChanged(int);
   void PcountChanged(int);
   void WinsChanged(int);
   void SexChanged(int);
   void TypeChanged(int);
   void NameChanged(QString);
   void CantMateChanged(bool);
private:
    void init_display(void);
    void init_connections(void);
    void disconnectAll(void);
    void getRank(void);
    //Widgets
    QFrame *advancedModeBox;
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
    QLabel *lbl_rankLabel;
    QLabel *lbl_rank;
    QLabel *lblSpeedWarning;
    //Data
    FF7CHOCOBO choco_data;
    QString choco_name;
    bool choco_cant_mate;
    quint16 choco_stamina;
};

#endif // CHOCOBOEDITOR_H
