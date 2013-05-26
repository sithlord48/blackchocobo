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
#include "ChocoboManager.h"

ChocoboManager::ChocoboManager(QWidget *parent) :
    QWidget(parent)
{
    initDisplay();
    initData();
    initConnections();
}
void ChocoboManager::initDisplay(void)
{

    lblStablesOwned = new QLabel(QString(tr("Stables Owned")));
    sbStablesOwned = new QSpinBox;
    sbStablesOwned->setMaximum(6);
    sbStablesOwned->setWrapping(true);
    sbStablesOwned->setMaximumHeight(24);

    lblStablesOccupied = new QLabel(QString(tr("Stables Occupied")));
    lcdStablesOccupied = new QLCDNumber;
    lcdStablesOccupied->setSegmentStyle(QLCDNumber::Flat);
    lcdStablesOccupied->setMaximumHeight(24);
    lcdStablesOccupied->setDigitCount(1);
    lcdStablesOccupied->setMaximumWidth(24);

    QHBoxLayout *ownedLayout = new QHBoxLayout();
    ownedLayout->setContentsMargins(0,0,0,0);
    ownedLayout->addWidget(lblStablesOwned);
    ownedLayout->addWidget(sbStablesOwned);

    QHBoxLayout *occupiedLayout = new QHBoxLayout();
    occupiedLayout->setContentsMargins(0,0,0,0);
    occupiedLayout->addWidget(lblStablesOccupied);
    occupiedLayout->addWidget(lcdStablesOccupied);


    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(0,0,0,0);
    QSpacerItem *topSpacer1 = new QSpacerItem(20,0,QSizePolicy::Preferred,QSizePolicy::Preferred);
    topLayout->addSpacerItem(topSpacer1);
    topLayout->addLayout(ownedLayout);
    topLayout->addLayout(occupiedLayout);
    QSpacerItem *topSpacer2 = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred);
    topLayout->addSpacerItem(topSpacer2);

    QGridLayout *stableGridLayout =new QGridLayout();
    stableGridLayout->setContentsMargins(0,0,0,0);
    for(int i=0;i<6;i++)
    {
        chocoboLabel[i] = new ChocoboLabel(this,QString(tr("Stable:%1")).arg(QString::number(i+1)));
        chocoboLabel[i]->setObjectName(QString::number(i));
        stableGridLayout->addWidget(chocoboLabel[i],(i/2),(i%2),1,1,Qt::AlignCenter);
        chocoboLabel[i]->setEnabled(false);
        chocoboLabel[i]->setSelected(false);
    }
    chocoboEditor = new ChocoboEditor;
    stableGridLayout->addWidget(chocoboEditor,0,3,2,2);
    chocoboEditor->setHidden(true);

    QGroupBox *penBox = new QGroupBox(tr("Fenced Chocobos"));
    QGridLayout *comboGrid = new QGridLayout;
    comboGrid->setContentsMargins(0,0,0,0);
    penBox->setLayout(comboGrid);

    QStringList typeList;
    typeList.append(tr("Empty"));
    typeList.append(tr("Wonderful"));
    typeList.append(tr("Great"));
    typeList.append(tr("Good"));
    typeList.append(tr("Fair"));
    typeList.append(tr("Average"));
    typeList.append(tr("Poor"));
    typeList.append(tr("Bad"));
    typeList.append(tr("Terrible"));

    for(int i=0;i<4;i++)
    {
        comboChocoPen[i]= new QComboBox;
        comboChocoPen[i]->addItems(typeList);
        comboChocoPen[i]->setObjectName(QString::number(i));
        comboGrid->addWidget(comboChocoPen[i],i/2,i%2,1,1);
    }
    QVBoxLayout *finalLayout = new QVBoxLayout();

    stableGridLayout->addWidget(penBox,2,3,1,2);
    finalLayout->addLayout(topLayout);
    finalLayout->addLayout(stableGridLayout);
    this->setLayout(finalLayout);
}
void ChocoboManager::initConnections()
{
    for(int i=0;i<6;i++)
    {
        connect(chocoboLabel[i],SIGNAL(copy()),this,SLOT(copy()));
        connect(chocoboLabel[i],SIGNAL(paste()),this,SLOT(paste()));
        connect(chocoboLabel[i],SIGNAL(remove()),this,SLOT(remove()));
        connect(chocoboLabel[i],SIGNAL(occupiedToggled(bool)),this,SLOT(occupiedToggled(bool)));
        connect(chocoboLabel[i],SIGNAL(clicked()),this,SLOT(clicked()));
    }
    for(int i=0;i<4;i++){connect(comboChocoPen[i],SIGNAL(currentIndexChanged(int)),this,SLOT(ChocoPenIndexChanged(int)));}
    connect(sbStablesOwned,SIGNAL(valueChanged(int)),this,SLOT(sbOwnedChanged(int)));
    connect(this,SIGNAL(setMode(bool)),chocoboEditor,SLOT(setAdvancedMode(bool)));
    connect(chocoboEditor,SIGNAL(nameChanged(QString)),this,SLOT(NameChange(QString)));
    connect(chocoboEditor,SIGNAL(sexChanged(quint8)),this,SLOT(SexChange(quint8)));
    connect(chocoboEditor,SIGNAL(typeChanged(quint8)),this,SLOT(TypeChange(quint8)));
    connect(chocoboEditor,SIGNAL(sprintChanged(quint16)),this,SLOT(SprintChanged(quint16)));
    connect(chocoboEditor,SIGNAL(mSprintChanged(quint16)),this,SLOT(MsprintChanged(quint16)));
    connect(chocoboEditor,SIGNAL(speedChanged(quint16)),this,SLOT(SpeedChanged(quint16)));
    connect(chocoboEditor,SIGNAL(mSpeedChanged(quint16)),this,SLOT(MspeedChanged(quint16)));
    connect(chocoboEditor,SIGNAL(staminaChanged(quint16)),this,SLOT(StaminaChanged(quint16)));
    connect(chocoboEditor,SIGNAL(accelChanged(quint8)),this,SLOT(AccelChanged(quint8)));
    connect(chocoboEditor,SIGNAL(coopChanged(quint8)),this,SLOT(CoopChanged(quint8)));
    connect(chocoboEditor,SIGNAL(intelligenceChanged(quint8)),this,SLOT(IntelligenceChanged(quint8)));
    connect(chocoboEditor,SIGNAL(personalityChanged(quint8)),this,SLOT(PersonalityChanged(quint8)));
    connect(chocoboEditor,SIGNAL(pCountChanged(quint8)),this,SLOT(PcountChanged(quint8)));
    connect(chocoboEditor,SIGNAL(winsChanged(quint8)),this,SLOT(WinsChanged(quint8)));
    connect(chocoboEditor,SIGNAL(cantMateChanged(bool)),this,SLOT(CantMateChanged(bool)));

}
void ChocoboManager::initData(void)
{
    stablesOwned=0;
    stablesOccupied=0;
    selectedStable=-1;
    for(int i=0;i<7;i++){rmChocobo(i);}
}

void ChocoboManager::sbOwnedChanged(int value)
{
    if(value==stablesOwned){return;}
    else if(value<0 || value>6){return;}
    else
    {
        for(int i=0;i<6;i++){chocoboLabel[i]->setEnabled(false);}
        for(int i=0;i<value;i++){chocoboLabel[i]->setEnabled(true);}

        stablesOwned = value;
        emit(ownedChanged(value));      

        for(int i=value;i<6;i++)
        {
            if(chocoboLabel[i]->isOccupied())
            {
                chocoboLabel[i]->setOccupied(false);setOccupied(stablesOccupied-1,stableMask &=~(1<<i));
                emit(occupiedChanged(stablesOccupied));
                emit(stableMaskChanged(stableMask));
                if(i==selectedStable){selectedStable=-1;chocoboEditor->setHidden(true);}
            }
        }
    }
}
void ChocoboManager::copy(void)
{
    int s=sender()->objectName().toInt();
    chocoboData[6]=chocoboData[s];
    chocoboName[6]=chocoboName[s];
    cantMate[6]=cantMate[s];
    chocoboStamina[6]=chocoboStamina[s];
}
void ChocoboManager::paste(void)
{
    int s=sender()->objectName().toInt();
    setChocobo(s,chocoboData[6],chocoboName[6],chocoboStamina[6],cantMate[6]);
    //emit the changes
    ChocoboChanged(s);
    chocoboLabel[s]->setOccupied(true);
    setOccupied(stablesOccupied+1,stableMask |=(1<<s));
    emit(occupiedChanged(stablesOccupied));
    emit(stableMaskChanged(stableMask));

}

void ChocoboManager::remove(void)
{
    int s=sender()->objectName().toInt();
    rmChocobo(s);
}
void ChocoboManager::rmChocobo(int s)
{
    chocoboName[s]=QString("\xff\xff\xff\xff\xff\xff");
    chocoboStamina[s]=0;
    cantMate[s]=false;
    chocoboData[s].accel=0;
    chocoboData[s].coop=0;
    chocoboData[s].intelligence=0;
    chocoboData[s].maxspeed=0;
    chocoboData[s].maxsprintspd=0;
    chocoboData[s].pcount=0;
    chocoboData[s].personality=0;
    chocoboData[s].raceswon=0;
    chocoboData[s].sex=0;
    chocoboData[s].speed=0;
    chocoboData[s].sprintspd=0;
    chocoboData[s].type=0;
    //emit the changes
    ChocoboChanged(s);
    if (selectedStable==s){chocoboLabel[s]->setSelected(false);selectedStable=-1;chocoboEditor->setHidden(true);}
}
void ChocoboManager::labelUpdate(int label)
{
    if(!(chocoboName[label].startsWith(QString("\xff")))){chocoboLabel[label]->setName(chocoboName[label]);}
    chocoboLabel[label]->setSex(chocoboData[label].sex);
    chocoboLabel[label]->setRank(chocoboData[label].raceswon);
    chocoboLabel[label]->setType(chocoboData[label].type);
    chocoboLabel[label]->setOccupied(stableMask & (1<<label));

}
void ChocoboManager::occupiedToggled(bool occupied)
{
    int s=sender()->objectName().toInt();
    if(occupied)
    {
        stableMask |= (1<<s);
        lcdStablesOccupied->display(lcdStablesOccupied->value()+1);
        labelUpdate(s);
    }
    else
    {
        stableMask &= ~(1<<s);
        lcdStablesOccupied->display(lcdStablesOccupied->value()-1);
        chocoboLabel[s]->clearLabel();
        if (selectedStable==s){chocoboLabel[s]->setSelected(false);selectedStable=-1;chocoboEditor->setHidden(true);}
    }
    stablesOccupied=lcdStablesOccupied->value();
    emit(occupiedChanged(stablesOccupied));
    emit(stableMaskChanged(stableMask));
}
void ChocoboManager::setAdvancedMode(bool advanced){chocoboEditor->setAdvancedMode(advanced);}

void ChocoboManager::clicked()
{
    if(selectedStable ==-1){chocoboEditor->setHidden(false);}

    selectedStable = sender()->objectName().toInt();
    chocoboEditor->SetChocobo(chocoboData[selectedStable],chocoboName[selectedStable],cantMate[selectedStable],chocoboStamina[selectedStable]);

    for(int i=0;i<6;i++)
    {
        chocoboLabel[i]->setSelected(false);
        if(i==selectedStable){chocoboLabel[i]->setSelected(true);}
    }
}
void ChocoboManager::NameChange(QString name)
{
    if(name != chocoboName[selectedStable])
    {
        chocoboName[selectedStable]=name;
        labelUpdate(selectedStable);
        emit nameChanged(selectedStable,name);
    }
}
void ChocoboManager::SexChange(quint8 sex)
{
    if(sex!=chocoboData[selectedStable].sex)
    {
        chocoboData[selectedStable].sex=sex;
        labelUpdate(selectedStable);
        emit sexChanged(selectedStable,sex); 
    }
}
void ChocoboManager::TypeChange(quint8 type)
{
    if(type!=chocoboData[selectedStable].type)
    {
        chocoboData[selectedStable].type=type;
        labelUpdate(selectedStable);
        emit typeChanged(selectedStable,type);
    }
}
void ChocoboManager::SprintChanged(quint16 sprint)
{
    if(sprint !=chocoboData[selectedStable].sprintspd)
    {
        chocoboData[selectedStable].sprintspd=sprint;
        emit(sprintChanged(selectedStable,sprint));
    }
}
void ChocoboManager::MsprintChanged(quint16 Msprint)
{
    if(Msprint !=chocoboData[selectedStable].maxsprintspd)
    {
        chocoboData[selectedStable].maxsprintspd=Msprint;
        emit(mSprintChanged(selectedStable,Msprint));
    }
}
void ChocoboManager::SpeedChanged(quint16 speed)
{
    if(speed !=chocoboData[selectedStable].speed)
    {
        chocoboData[selectedStable].speed=speed;
        emit(speedChanged(selectedStable,speed));
    }
}
void ChocoboManager::MspeedChanged(quint16 Mspeed)
{
    if(Mspeed !=chocoboData[selectedStable].maxspeed)
    {
        chocoboData[selectedStable].maxspeed=Mspeed;
        emit(mSpeedChanged(selectedStable,Mspeed));
    }
}
void ChocoboManager::StaminaChanged(quint16 stamina)
{
    if(stamina != chocoboStamina[selectedStable])
    {
        chocoboStamina[selectedStable]=stamina;
        emit(staminaChanged(selectedStable,stamina));
    }
}
void ChocoboManager::AccelChanged(quint8 accel)
{
    if(accel !=chocoboData[selectedStable].accel)
    {
        chocoboData[selectedStable].accel=accel;
        emit(accelChanged(selectedStable,accel));
    }
}

void ChocoboManager::CoopChanged(quint8 coop)
{
    if(coop !=chocoboData[selectedStable].coop)
    {
        chocoboData[selectedStable].coop=coop;
        emit(coopChanged(selectedStable,coop));
    }
}
void ChocoboManager::IntelligenceChanged(quint8 intelligence)
{
    if(intelligence !=chocoboData[selectedStable].intelligence)
    {
        chocoboData[selectedStable].intelligence=intelligence;
        emit(intelligenceChanged(selectedStable,intelligence));
    }
}
void ChocoboManager::PersonalityChanged(quint8 personality)
{
    if(personality !=chocoboData[selectedStable].personality)
    {
        chocoboData[selectedStable].personality=personality;
        emit(personalityChanged(selectedStable,personality));
    }
}
void ChocoboManager::PcountChanged(quint8 pCount)
{
    if(pCount !=chocoboData[selectedStable].pcount)
    {
        chocoboData[selectedStable].pcount=pCount;
        emit(pCountChanged(selectedStable,pCount));
    }
}
void ChocoboManager::WinsChanged(quint8 wins)
{
    if(wins !=chocoboData[selectedStable].raceswon)
    {
        chocoboData[selectedStable].raceswon=wins;
        labelUpdate(selectedStable);
        emit(winsChanged(selectedStable,wins));
    }
}
void ChocoboManager::CantMateChanged(bool cantmate)
{
    if(cantmate !=cantMate[selectedStable])
    {
        cantMate[selectedStable]=cantmate;
        emit(cantMateChanged(selectedStable,cantmate));
    }
}
void ChocoboManager::setData(FF7CHOCOBO chocos[6],QString names[6],quint16 staminas[6],bool cMate[6],qint8 owned,qint8 occupied,qint8 mask,qint8 chocoPens[4])
{
    for(int i=0;i<6;i++)
    {
        setChocobo(i,chocos[i],names[i],staminas[i],cMate[i]);
        if(!chocoboLabel[i]->isOccupied()){chocoboLabel[i]->clearLabel();}
        chocoboLabel[i]->setSelected(false);
    }
    setOwned(owned);
    setOccupied(occupied,mask);
    selectedStable=-1;//reset
    chocoboEditor->setHidden(true);
    for(int i=0;i<4;i++){setChocoboPen(i,chocoPens[i]);}
}
void ChocoboManager::setData(QList<FF7CHOCOBO> chocos,QList<QString> names,QList<quint16> staminas,QList<bool> cMate,qint8 owned,qint8 occupied,qint8 mask,QList<qint8> chocoPens)
{
    setOwned(owned);
    setOccupied(occupied,mask);
    selectedStable=-1;//reset

    chocoboEditor->setHidden(true);

    for(int i=0;i<6;i++)
    {
        setChocobo(i,chocos.at(i),names.at(i),staminas.at(i),cMate.at(i));
        if(!chocoboLabel[i]->isOccupied()){chocoboLabel[i]->clearLabel();}
        chocoboLabel[i]->setSelected(false);
    }
    for(int i=0;i<4;i++){setChocoboPen(i,chocoPens[i]);}
}
void ChocoboManager::setChocobo(int s,FF7CHOCOBO chocoData,QString chocoName,quint16 chocoStamina,bool chocoCmate)
{
    chocoboLabel[s]->clearLabel();
    chocoboData[s]= chocoData;
    chocoboName[s]= chocoName;
    chocoboStamina[s]=chocoStamina;
    cantMate[s] = chocoCmate;
    if(chocoboLabel[s]->isOccupied()){labelUpdate(s);}
    else{chocoboLabel[s]->clearLabel();}
}
void ChocoboManager::setChocoboPen(int pen, int value)
{
    if(pen<0 || pen>4 || value<0 || value>8){return;}
    else{comboChocoPen[pen]->setCurrentIndex(value);}
}
void ChocoboManager::setOwned(int owned)
{
    if(owned<0 || owned>6){return;}
    else
    {
        stablesOwned=owned;
        sbStablesOwned->blockSignals(true);
        sbStablesOwned->setValue(owned);
        for(int i=0;i<6;i++){chocoboLabel[i]->setEnabled(false);}
        for(int i=0;i<owned;i++){chocoboLabel[i]->setEnabled(true);}
        sbStablesOwned->blockSignals(false);
    }
}
void ChocoboManager::setOccupied(int occupied,int mask)
{
    if(occupied<0 || occupied>6){return;}
    else
    {
        stablesOccupied = occupied;
        stableMask=mask;


        for(int i=0;i<6;i++)
        {
            chocoboLabel[i]->blockSignals(true);
            if((mask&(1<<i)))
            {
                chocoboLabel[i]->setOccupied(true);
                labelUpdate(i);
            }
            else
            {
                chocoboLabel[i]->setOccupied(false);
                chocoboLabel[i]->clearLabel();
            }
            chocoboLabel[i]->blockSignals(false);

        }
        lcdStablesOccupied->blockSignals(true);
        lcdStablesOccupied->display(occupied);
        lcdStablesOccupied->blockSignals(false);
    }
}
void ChocoboManager::ChocoboChanged(int s)
{
    emit(nameChanged(s,chocoboName[s]));
    emit(staminaChanged(s,chocoboStamina[s]));
    emit(cantMateChanged(s,cantMate[s]));
    emit(sexChanged(s,chocoboData[s].sex));
    emit(typeChanged(s,chocoboData[s].type));
    emit(sprintChanged(s,chocoboData[s].sprintspd));
    emit(mSprintChanged(s,chocoboData[s].maxsprintspd));
    emit(speedChanged(s,chocoboData[s].speed));
    emit(mSpeedChanged(s,chocoboData[s].maxspeed));
    emit(accelChanged(s,chocoboData[s].accel));
    emit(coopChanged(s,chocoboData[s].coop));
    emit(intelligenceChanged(s,chocoboData[s].intelligence));
    emit(personalityChanged(s,chocoboData[s].personality));
    emit(pCountChanged(s,chocoboData[s].pcount));
    emit(winsChanged(s,chocoboData[s].raceswon));
}
bool ChocoboManager::isEmpty(FF7CHOCOBO choco)
{
    int score =0;
    if(choco.accel!=0){score++;}
    if(choco.coop!=0){score++;}
    if(choco.intelligence!=0){score++;}
    if(choco.maxspeed!=0){score++;}
    if(choco.maxsprintspd!=0){score++;}
    if(choco.pcount!=0){score++;}
    if(choco.personality!=0){score++;}
    if(choco.raceswon!=0){score++;}
    if(choco.sex!=0){score++;}
    if(choco.speed!=0){score++;}
    if(choco.sprintspd!=0){score++;}
    if(choco.type!=0){score++;}
    if(score>5){return false;}
    else{return true;}
}
void ChocoboManager::setHoverStyle(QString backgroundColor)
{
    for(int i=0;i<6;i++){chocoboLabel[i]->setHoverColorStyle(backgroundColor);}
}
void ChocoboManager::ChocoPenIndexChanged(int index)
{
    int s =sender()->objectName().toInt();
    emit(penChanged(s,index));
}
