/****************************************************************************/
//    copyright 2010-2020 Chris Rizzitello <sithlord48@gmail.com>           //
//                                                                          //
//    This file is part of Black Chocobo.                                   //
//                                                                          //
//    Black Chocobo is free software: you can redistribute it and/or modify //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    Black Chocobo is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "errbox.h"
#include "ff7tk/data/FF7SaveInfo.h"
#include <QMessageBox>
#include <QKeyEvent>

errbox::errbox(QWidget *parent, FF7Save *ff7data, int slot)
    : QDialog(parent)
    , s(slot)
    , singleSlot(false)
    , ff7save(ff7data)
    , save_icon(new SaveIcon(ff7data->slotIcon(s)))
    , btnNext(new QPushButton(QIcon::fromTheme("go-next", QIcon(":/icon/next")), QString()))
    , btnPrev(new QPushButton(QIcon::fromTheme("go-previous", QIcon(":/icon/prev")), QString()))
    , btnView(new QPushButton(QIcon::fromTheme("window-close", QIcon(":/icon/quit")), tr("View Anyway")))
    , btnExport(new QPushButton(tr("E&xport Slot")))
    , lblRegionString(new QLabel)
    , lblIcon(new QLabel)
{
    if (FF7SaveInfo::instance()->internalPC(ff7data->format()))
        close();

    QSize iconSize = QSize(fontMetrics().height(), fontMetrics().height());
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setWindowFlags(((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowCloseButtonHint)); //remove close
    setWindowTitle(tr("Non Final Fantasy VII Slot"));

    connect(save_icon, &SaveIcon::nextIcon, this, &errbox::setIcon);

    lblRegionString->setAlignment(Qt::AlignTop);
    lblIcon->setMinimumSize(64, 64);
    lblIcon->setMaximumSize(128, 128);
    lblIcon->setPixmap(save_icon->icon().scaled(lblIcon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    btnPrev->setShortcut(QKeySequence::Back);
    btnPrev->setIconSize(iconSize);
    connect(btnPrev, &QPushButton::clicked, this, &errbox::btnPrevClicked);
    btnView->setShortcut(QKeySequence::Close);
    btnView->setIconSize(iconSize);
    connect(btnView, &QPushButton::clicked, this, &errbox::btnViewClicked);

    btnNext->setShortcut(QKeySequence::Forward);
    btnNext->setIconSize(iconSize);
    connect(btnNext, &QPushButton::clicked, this, &errbox::btnNextClicked);

    connect(btnExport, &QPushButton::clicked, this, &errbox::btnExportClicked);

    auto slotLayout = new QHBoxLayout;
    slotLayout->setContentsMargins(0, 0, 3, 0);
    slotLayout->setSpacing(0);
    slotLayout->addWidget(lblIcon);
    slotLayout->addWidget(lblRegionString);

    auto *navLayout = new QHBoxLayout;
    navLayout->setSpacing(3);
    navLayout->addWidget(btnPrev);
    navLayout->addWidget(btnView);
    navLayout->addWidget(btnNext);

    auto *btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(3);
    btnLayout->addWidget(btnExport);

    auto finalLayout = new QVBoxLayout;
    finalLayout->setContentsMargins(3, 3, 3, 3);
    finalLayout->setSpacing(3);
    finalLayout->addLayout(slotLayout);
    finalLayout->addLayout(navLayout);
    finalLayout->addLayout(btnLayout);
    setLayout(finalLayout);

    QString Slottext = QString(tr("Slot:%1\n").arg(QString::number(s + 1), 2, QChar('0')));
    if (ff7save->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK)
            || ff7save->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK)
            || ff7save->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK)
            || ff7save->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK)) {
        btnView->setEnabled(false);
        btnLayout->setEnabled(false);
        switch (ff7save->psx_block_type(s)) {
        case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK):   Slottext.append(tr("       Mid-Linked Block")); break;
        case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK):  Slottext.append(tr("    Mid-Linked Block (Deleted)")); break;
        case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK):  Slottext.append(tr("      End Of Linked Blocks")); break;
        case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK): Slottext.append(tr("      End Of Linked Blocks (Deleted)")); break;
        default: Slottext.append(tr("ERROR")); break;
        }
    }
    Slottext.append(ff7save->psxDesc(s));

    if (ff7save->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK)
            && ff7save->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK)
            && ff7save->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK)
            && ff7save->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK)) {
        Slottext.append(tr("\n Game Uses %n Save Block(s)", nullptr, ff7save->psx_block_size(s)));
    }

    if (ff7save->psx_block_next(s) != 0xFF)
        Slottext.append(tr("\n   Next Data Chunk @ Slot:%1").arg(QString::number(ff7save->psx_block_next(s) + 1)));

    lblRegionString->setText(Slottext);
    if (s == 0)
        btnPrev->setEnabled(false);
    if (s == 15)
        btnNext->setEnabled(false);
}

void errbox::keyPressEvent(QKeyEvent *e)
{
    //catch esc press and send it to view button
    if (e->key() != Qt::Key_Escape)
        QDialog::keyPressEvent(e);
    else
        btnView->click();
}

void errbox::btnViewClicked()
{
    done(0);
}

void errbox::btnPrevClicked()
{
    done(1);
}

void errbox::btnNextClicked()
{
    done(2);
}

void errbox::btnExportClicked()
{
    done(3);
}

void errbox::setSingleSlot(bool single)
{
    btnNext->setEnabled(!single);
    btnPrev->setEnabled(!single);
    singleSlot = !single;
}

bool errbox::isSingleSlot()
{
    return singleSlot;
}

void errbox::setIcon(QPixmap pix)
{
    lblIcon->setPixmap(pix.scaled(lblIcon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
