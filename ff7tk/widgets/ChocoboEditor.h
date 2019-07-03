/****************************************************************************/
//    copyright 2012 - 2019  Chris Rizzitello <sithlord48@gmail.com>        //
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
#pragma once

#include <QtWidgets>
//Be sure to set paths correctly for below.
//ALSO CHECK ChocoboEditor.cpp for icons includes.
#include "../data/Type_FF7CHOCOBO.h"

class ChocoboEditor : public QWidget
{
    Q_OBJECT
protected:
    void resizeEvent(QResizeEvent *ev);
    void changeEvent(QEvent *e);
public:
    explicit ChocoboEditor(QWidget *parent = nullptr);
    void SetChocobo(FF7CHOCOBO choco,const QString &Processed_Name= nullptr, bool cant_mate=false, quint16 stamina=0,quint8 rating=0);
public slots:
   void updateText();
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
   void setName(const QString&);
   void setCantMate(bool);
   void setRating(int);
   void setAdvancedMode(bool);
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
	void ratingChanged(quint8);
private:
    void init_connections();
    void getRank(void);
    QSpinBox* makeSpinBox(int maxValue);
    //Widgets
    QFrame *advancedModeBox = nullptr;
    QLabel *lbl_rank = nullptr;
    QLabel *lbl_speed = nullptr;
    QLabel *lbl_sprint = nullptr;
    QLabel *lbl_accel = nullptr;
    QLabel *lbl_stamina = nullptr;
    QLabel *lbl_wins = nullptr;
    QLabel *lbl_coop = nullptr;
    QLabel *lbl_intel = nullptr;
    QLabel *lbl_pCount = nullptr;
    QLabel *lbl_personality = nullptr;
    QLabel *lbl_rating = nullptr;
    QLabel *lblSpeedWarning = nullptr;
    QComboBox *combo_sex = nullptr;
    QComboBox *combo_type = nullptr;
    QComboBox* combo_rating = nullptr;
    QCheckBox *cb_cantMate = nullptr;
    QLineEdit *line_name = nullptr;
    QSpinBox *sb_speed = nullptr;
    QSpinBox *sb_mSpeed = nullptr;
    QSpinBox *sb_sprint = nullptr;
    QSpinBox *sb_mSprint = nullptr;
    QSpinBox *sb_stamina = nullptr;
    QSpinBox *sb_accel = nullptr;
    QSpinBox *sb_wins = nullptr;
    QSpinBox *sb_coop = nullptr;
    QSpinBox *sb_pCount = nullptr;
    QSpinBox *sb_intel = nullptr;
    QSpinBox *sb_personality = nullptr;
    QGridLayout *Final = nullptr;
    //Data
    FF7CHOCOBO choco_data;
    QString choco_name;
    quint16 choco_stamina;
    bool choco_cant_mate;
	quint8 choco_rating;
};

