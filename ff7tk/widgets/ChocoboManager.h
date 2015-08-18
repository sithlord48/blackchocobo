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
#ifndef CHOCOBOMANAGER_H
#define CHOCOBOMANAGER_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif
//import friends from ff7tk
#include "../widgets/ChocoboEditor.h"
#include "../widgets/ChocoboLabel.h"
class ChocoboManager : public QWidget
{
    Q_OBJECT
public:
	explicit ChocoboManager(qreal Scale=1,QWidget *parent=0);
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
    void cantMateChanged(int,bool);
    void penChanged(int,int);
public slots:
    void setAdvancedMode(bool advanced);
    void setData(FF7CHOCOBO choco[6],QString name[6],quint16 stamina[6],bool cMate[6],qint8 owned,qint8 occupied,qint8 mask,qint8 chocoPens[4]);
    void setData(QList<FF7CHOCOBO> chocos,QList<QString> names,QList<quint16> staminas,QList<bool> cMate,qint8 owned,qint8 occupied,qint8 mask,QList<qint8> chocoPens);
    void setChocobo(int s,FF7CHOCOBO chocoData,QString chocoName,quint16 chocoStamina,bool chocoCmate);
    void setChocoboPen(int pen, int value);
    void setOwned(int owned);
    void setOccupied(int occupied,int mask);
    void setHoverStyle(QString backgroundColor);
    void setHoverStyle();
private slots:
    void sbOwnedChanged(int);
    void copy();
    void paste();
    void remove();
    void clicked();
    void ChocoboChanged(int s);
    void occupiedToggled(bool occupied);
    void NameChange(QString);
    void SexChange(quint8);
    void TypeChange(quint8);
    void SprintChanged(quint16);
    void MsprintChanged(quint16);
    void SpeedChanged(quint16);
    void MspeedChanged(quint16);
    void StaminaChanged(quint16);
    void AccelChanged(quint8);
    void CoopChanged(quint8);
    void IntelligenceChanged(quint8);
    void PersonalityChanged(quint8);
    void PcountChanged(quint8);
    void WinsChanged(quint8);
    void CantMateChanged(bool);
    void ChocoPenIndexChanged(int);
private:
    bool isEmpty(FF7CHOCOBO choco);
    void initDisplay(void);
    void initConnections(void);
    void initData(void);
    void rmChocobo(int s);
    void labelUpdate(int label);

    QLabel *lblStablesOwned;
    QSpinBox *sbStablesOwned;
    QLabel *lblStablesOccupied;
    QLCDNumber *lcdStablesOccupied;
    ChocoboLabel *chocoboLabel[6];
    ChocoboEditor *chocoboEditor;
    qint8 stablesOwned;
    qint8 stablesOccupied;
    qint8 stableMask;
    int selectedStable;
    //one extra of each for a buffer.
    FF7CHOCOBO chocoboData[7];
    QString chocoboName[7];
    bool cantMate[7];
    quint16 chocoboStamina[7];
    QComboBox *comboChocoPen[4];
	qreal scale;
};
#endif // CHOCOBOMANAGER_H
