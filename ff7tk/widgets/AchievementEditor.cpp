/****************************************************************************/
//    copyright 2013 - 2019  Chris Rizzitello <sithlord48@gmail.com>        //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//   FF7tk is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "AchievementEditor.h"

AchievementEditor::AchievementEditor(QWidget *parent) :
	QWidget(parent)
{
    initDisplay();
    connect(achievementList, &QListWidget::clicked, this, &AchievementEditor::itemToggled);
}

void AchievementEditor::initDisplay()
{
    achievementList = new QListWidget;
    achievementList->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));
    achievementList->setStyleSheet(QStringLiteral("QListView::indicator{width: %1px; height:%1px} QListView::item{padding: 0px;}").arg(QString::number(fontMetrics().height())));
    auto layout = new QGridLayout;
    for(int i=63;i>27;--i) {
        QPixmap pix(QString(":/achievements/%1").arg(QString::number(i)));
        auto newItem = new QListWidgetItem(QIcon(pix), achievements.name(i), achievementList, 0);
        newItem->setCheckState(Qt::Unchecked);
	}
	layout->addWidget(achievementList);
    setLayout(layout);
}

bool AchievementEditor::openFile(const QString &fileName)
{
	bool open = achievements.openFile(fileName);
    for(int i=0;i<36;++i) {
        if (achievements.achievmentUnlocked(63-i)) {
            achievementList->item(i)->setCheckState(Qt::Checked);
        } else {
            achievementList->item(i)->setCheckState(Qt::Unchecked);
        }
	}
	return open;
}

void AchievementEditor::itemToggled(const QModelIndex &index)
{
    if(achievementList->item(index.row())->checkState() == Qt::Checked) {
        achievements.setAchievementUnlocked(63- index.row(), true);
    } else {
        achievements.setAchievementUnlocked(63- index.row(), false);
    }
}

bool AchievementEditor::saveFile(const QString &fileName)
{
	return achievements.saveFile(fileName);
}

