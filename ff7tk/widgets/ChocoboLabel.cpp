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
#include "ChocoboLabel.h"
// Pull in Icons, Be Sure Paths Are Correct

bool ChocoboLabel::event(QEvent *ev)
{
    if (ev->type() == QEvent::MouseButtonPress && isEnabled) {
        emit(clicked());
        return true;
    } else if (ev->type() == QEvent::LanguageChange) {
        btnCopy->setToolTip(QString(tr("Copy")));
        btnPaste->setToolTip(QString(tr("Paste")));
        btnRemove->setToolTip(QString(tr("Remove")));
        setRank(m_wins);
        return true;
    } else {
        return false;
    }
}

ChocoboLabel::ChocoboLabel(const QString &titleText, bool occupied, QWidget *parent) :
    QWidget(parent)
    , lblType(new QLabel(this))
    , lblName(new QLabel(this))
    , lblRank(new QLabel(this))
    , lblSex(new QLabel(this))
{
    QSize iconSize = QSize(fontMetrics().height(), fontMetrics().height());
    lblType->setScaledContents(true);
    lblType->setFixedSize(fontMetrics().height() * 3, fontMetrics().height() * 3);

    chkOccupied = new QCheckBox(this);
    chkOccupied->setText(titleText);
    chkOccupied->setProperty("HoverStyled", QVariant(true));
    chkOccupied->setStyleSheet(QStringLiteral("QCheckBox::indicator{width: %1px; height: %1px;}").arg(QString::number(fontMetrics().height())));
    chkOccupied->setChecked(occupied);
    connect(chkOccupied, &QCheckBox::toggled, this, [this](bool checked) {
        emit occupiedToggled(checked);
        enable(checked);
    });

    btnCopy = new QPushButton(this);
    btnCopy->setFlat(true);
    btnCopy->setToolTip(QString(tr("Copy")));
    btnCopy->setProperty("HoverStyled", QVariant(true));
    btnCopy->setIcon(QIcon::fromTheme(QString("edit-copy"), QPixmap(":/common/edit-copy")));
    btnCopy->setIconSize(iconSize);
    btnCopy->setMaximumSize(iconSize);
    connect(btnCopy, &QPushButton::clicked, this, &ChocoboLabel::copy);

    btnPaste = new QPushButton(this);
    btnPaste->setFlat(true);
    btnPaste->setToolTip(QString(tr("Paste")));
    btnPaste->setProperty("HoverStyled", QVariant(true));
    btnPaste->setIcon(QIcon::fromTheme(QString("edit-paste"), QPixmap(":/common/edit-paste")));
    btnPaste->setIconSize(iconSize);
    btnPaste->setMaximumSize(iconSize);
    connect(btnPaste, &QPushButton::clicked, this, &ChocoboLabel::paste);

    btnRemove = new QPushButton(this);
    btnRemove->setFlat(true);
    btnRemove->setToolTip(QString(tr("Remove")));
    btnRemove->setProperty("HoverStyled", QVariant(true));
    btnRemove->setIcon(QIcon::fromTheme(QString("edit-clear"), QPixmap(":/common/edit-clear")));
    btnRemove->setIconSize(iconSize);
    btnRemove->setMaximumSize(iconSize);
    connect(btnRemove, &QPushButton::clicked, this, [this] {
        emit remove();
        clearLabel();
        chkOccupied->setChecked(false);
    });

    setFontSize(14);

    auto btnLayout = new QHBoxLayout;
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->addWidget(chkOccupied);
    btnLayout->addWidget(btnCopy);
    btnLayout->addWidget(btnPaste);
    btnLayout->addWidget(btnRemove);
    btnLayout->setSpacing(1);

    auto LeftTopLayout = new QHBoxLayout;
    LeftTopLayout->setContentsMargins(0, 0, 0, 0);
    LeftTopLayout->addWidget(lblName);
    LeftTopLayout->addWidget(lblSex);
    LeftTopLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
    LeftTopLayout->setSpacing(1);

    auto RightTopLayout = new QHBoxLayout;
    RightTopLayout->setContentsMargins(0, 0, 0, 0);
    RightTopLayout->addWidget(lblRank);
    RightTopLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
    RightTopLayout->setSpacing(1);

    auto rightSideLayout = new QVBoxLayout;
    rightSideLayout->setContentsMargins(0, 0, 0, 0);
    rightSideLayout->addLayout(LeftTopLayout);
    rightSideLayout->addLayout(RightTopLayout);

    auto innerFrameLayout = new QHBoxLayout;
    innerFrameLayout->addWidget(lblType);
    innerFrameLayout->addLayout(rightSideLayout);

    innerFrame = new QFrame;
    innerFrame->setLayout(innerFrameLayout);
    innerFrame->setProperty("HoverStyled", QVariant(true));

    auto outerFrameLayout = new QVBoxLayout;
    outerFrameLayout->setContentsMargins(3, 3, 3, 3);
    outerFrameLayout->addLayout(btnLayout);
    outerFrameLayout->addWidget(innerFrame);

    outerFrame = new QFrame;
    outerFrame->setLayout(outerFrameLayout);

    auto finalLayout = new QVBoxLayout;
    finalLayout->setContentsMargins(0, 0, 0, 0);
    finalLayout->addWidget(outerFrame);

    this->setLayout(finalLayout);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    enable(occupied);
}

void ChocoboLabel::setType(int type)
{
    switch (type) {
    case 0: lblType->setPixmap(QPixmap("://chocobo/yellow").scaled(lblType->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)); break;
    case 1: lblType->setPixmap(QPixmap("://chocobo/green").scaled(lblType->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)); break;
    case 2: lblType->setPixmap(QPixmap("://chocobo/blue").scaled(lblType->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)); break;
    case 3: lblType->setPixmap(QPixmap("://chocobo/black").scaled(lblType->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)); break;
    case 4: lblType->setPixmap(QPixmap("://chocobo/gold").scaled(lblType->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)); break;
    default: lblType->setPixmap(QPixmap()); break;
    }
}

void ChocoboLabel::setTitle(QString title)
{
    chkOccupied->setText(title);
}

void ChocoboLabel::setName(QString decodedName)
{
    lblName->setText(decodedName.mid(0, 6));/*only space for 6 chars*/
}

void ChocoboLabel::setSex(bool male)
{
    if (male) {
        lblSex->setText(QString::fromUtf8("♂"));
    } else {
        lblSex->setText(QString::fromUtf8("♀"));
    }
}

void ChocoboLabel::setSex(int sex)
{
    if (sex == 0) {
        lblSex->setText(QString::fromUtf8("♂"));
    } else if (sex == 1) {
        lblSex->setText(QString::fromUtf8("♀"));
    } else {
        lblSex->setText(QString());
    }
}

void ChocoboLabel::setRank(int wins)
{
    m_wins = wins;
    if (wins < 0) {
        lblRank->setText(QString());
    } else if (wins < 3) {
        lblRank->setText(tr("Rank:C"));
    } else if (wins < 6) {
        lblRank->setText(tr("Rank:B"));
    } else if (wins < 9) {
        lblRank->setText(tr("Rank:A"));
    } else {
        lblRank->setText(tr("Rank:S"));
    }
}

void ChocoboLabel::setOccupied(bool occupied)
{
    chkOccupied->blockSignals(true);
    chkOccupied->setChecked(occupied);
    chkOccupied->blockSignals(false);
    enable(occupied);
}

void ChocoboLabel::clearLabel()
{
    setType(-1);
    setRank(-1);
    setName(QString());
    setSex(-1);
}

void ChocoboLabel::setFontSize(int fontSize)
{
    QString fontStyle = QString("font-size:%1pt;background-color:rgba(0,0,0,0);").arg(fontSize);
    lblName->setStyleSheet(fontStyle);
    lblSex->setStyleSheet(fontStyle);
    lblRank->setStyleSheet(fontStyle);
    lblType->setStyleSheet(fontStyle);
}

void ChocoboLabel::enable(bool enabled)
{
    isEnabled = enabled;
    innerFrame->setEnabled(enabled);
    if (!enabled) {
        setSelected(false);
    }
}

void ChocoboLabel::setSelected(bool selected)
{
    if (selected) {
        outerFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken); innerFrame->setStyleSheet(SelectedBkStyle);
    } else {
        outerFrame->setFrameStyle(QFrame::NoFrame);
        QString Style = SelectedBkStyle;
        Style.append(Style.insert(Style.lastIndexOf("]") + 1, ":enabled:hover"));
        Style.prepend("QWidget[HoverStyled=\"true\"]{background-color:rgba(0,0,0,0);}");
        innerFrame->setStyleSheet(Style);
    }
}

bool ChocoboLabel::isOccupied(void)
{
    return chkOccupied->isChecked();
}

void ChocoboLabel::setHoverColorStyle(QString backgroundColor)
{
    SelectedBkStyle = backgroundColor;
    SelectedBkStyle.prepend("QWidget[HoverStyled=\"true\"]{background-color:");
    SelectedBkStyle.append("}");

    backgroundColor.prepend("QPushButton:enabled{background-color:rgba(0,0,0,0);border:0px solid;} QWidget[HoverStyled=\"true\"]:enabled:hover{background-color:");
    backgroundColor.append("}");
    this->setStyleSheet(backgroundColor);
}
