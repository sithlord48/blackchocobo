/****************************************************************************/
//    copyright 2013 - 2019 Chris Rizzitello <sithlord48@gmail.com>         //
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
//import friends from ff7tk
#include "../widgets/ChocoboEditor.h"
#include "../widgets/ChocoboLabel.h"
class ChocoboManager : public QWidget
{
    Q_OBJECT
public:
    explicit ChocoboManager(QWidget *parent = nullptr);
signals:
    void ownedChanged(qint8);
    void occupiedChanged(qint8);
    void stableMaskChanged(qint8);
    void setMode(bool advanced);
    void nameChanged(int,QString);
    void sexChanged(int,quint8);
    void typeChanged(int,quint8);
    void sprintChanged(int,quint16);
    void mSprintChanged(int,quint16);
    void speedChanged(int,quint16);
    void mSpeedChanged(int,quint16);
    void staminaChanged(int,quint16);
    void accelChanged(int,quint8);
    void coopChanged(int,quint8);
    void intelligenceChanged(int,quint8);
    void personalityChanged(int,quint8);
    void pCountChanged(int,quint8);
    void winsChanged(int,quint8);
	void ratingChanged(int,quint8);
    void cantMateChanged(int,bool);
    void penChanged(int,int);
public slots:
    inline void setAdvancedMode(bool advanced){chocoboEditor->setAdvancedMode(advanced);}
	void setData(FF7CHOCOBO choco[6],QString name[6],quint16 stamina[6],bool cMate[6],qint8 owned,qint8 occupied,qint8 mask,qint8 chocoPens[4],quint8 chocoRatings[6]);
	void setData(QList<FF7CHOCOBO> chocos,QList<QString> names,QList<quint16> staminas,QList<bool> cMate,qint8 owned,qint8 occupied,qint8 mask,QList<qint8> chocoPens,QList<quint8> chocoRatings);
	void setChocobo(int s,FF7CHOCOBO chocoData,QString chocoName,quint16 chocoStamina,bool chocoCmate,quint8 rating);
    void setChocoboPen(int pen, int value);
    void setOwned(int owned);
    void setOccupied(int occupied,int mask);
    void setHoverStyle(QString Color);
private slots:
    void ChocoboChanged(int s);
    void setStablesOwned(int value);
private:
    bool isEmpty(FF7CHOCOBO choco);
    void clearSelection();
    void disableChocoLabels();
    void enableChocoboLabels(int count);
    void rmChocobo(int s);
    void labelUpdate(int label);
    void connectEditor();
    QGridLayout* createChocoboPenGrid();
    QGridLayout* createChocoboLabelGrid();
    QSpinBox *sbStablesOwned = nullptr;
    QLCDNumber *lcdStablesOccupied = nullptr;
    ChocoboLabel *chocoboLabel[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    ChocoboEditor *chocoboEditor = nullptr;
    QGroupBox *penBox = nullptr;
    qint8 stablesOwned = 0;
    qint8 stablesOccupied = 0;
    qint8 stableMask;
    int selectedStable = -1;
    //one extra of each for a buffer.
    FF7CHOCOBO chocoboData[7];
    QString chocoboName[7];
    bool cantMate[7];
    quint16 chocoboStamina[7];
	quint8 chocoboRatings[7];
    QComboBox *comboChocoPen[4];
};
