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
#include "AchievementEditor.h"

AchievementEditor::AchievementEditor(QWidget *parent) :
    QWidget(parent)
{
    initDisplay();
    initConnect();
}
void AchievementEditor::initConnect(void)
{
    connect(achievementList,SIGNAL(clicked(QModelIndex)),this,SLOT(itemToggled(QModelIndex)));
}
void AchievementEditor::initDisconnect(void)
{
    disconnect(achievementList,SIGNAL(clicked(QModelIndex)),this,SLOT(itemToggled(QModelIndex)));
}
void AchievementEditor::initDisplay(void)
{
    achievementList = new QListWidget;
    achievementList->setIconSize(QSize(24,24));

    QGridLayout * layout = new QGridLayout;
    for(int i=63;i>27;--i)
    {
        QPixmap pix(QString(":/achievements/%1").arg(QString::number(i)));
        QListWidgetItem *newItem =new QListWidgetItem(QIcon(pix),achievements.name(i),0,0);
        newItem->setCheckState(Qt::Unchecked);
        achievementList->addItem(newItem);
    }
    layout->addWidget(achievementList);
    this->setLayout(layout);

}
bool AchievementEditor::openFile(QString fileName)
{
    bool open = achievements.openFile(fileName);
    initDisconnect();
    for(int i=0;i<36;++i)
    {
        if(achievements.achievmentUnlocked(63-i)){achievementList->item(i)->setCheckState(Qt::Checked);}
        else{achievementList->item(i)->setCheckState(Qt::Unchecked);}
    }
    initConnect();
    return open;
}
void AchievementEditor::itemToggled(QModelIndex index)
{
    if(achievementList->item(index.row())->checkState() ==Qt::Checked)
    {
        achievements.setAchievementUnlocked(63- index.row(),true);
    }
    else{achievements.setAchievementUnlocked(63- index.row(),false);}
}
bool AchievementEditor::saveFile(QString fileName)
{
    return achievements.saveFile(fileName);
}
