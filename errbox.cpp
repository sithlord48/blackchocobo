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
#include <QFileDialog>
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
    if (ff7data->format() == FF7SaveInfo::FORMAT::PC)
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

    QHBoxLayout *slotLayout = new QHBoxLayout;
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

    QVBoxLayout *finalLayout = new QVBoxLayout;
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
    QMap<QString, FF7SaveInfo::FORMAT> typeMap;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PSX)] = FF7SaveInfo::FORMAT::PSX;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PS3)] = FF7SaveInfo::FORMAT::PS3;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PGE)] = FF7SaveInfo::FORMAT::PGE;
    QString types = typeMap.keys().join(";;");
    QString fileName;
    QString selectedType = typeMap.key(ff7save->format());
    QString path = QDir::homePath();

    auto saveDialog = new QFileDialog(this, tr("Select A File to Save As"), path, types);
    saveDialog->setAttribute(Qt::WA_DeleteOnClose);
    saveDialog->selectNameFilter(selectedType);
    saveDialog->setFileMode(QFileDialog::AnyFile);
    saveDialog->setAcceptMode(QFileDialog::AcceptSave);

    QString nameTemplate = QStringLiteral("%1/%2");

    connect(saveDialog, &QFileDialog::filterSelected, this, [typeMap, saveDialog, nameTemplate, this](const QString &filter){
        QString name;
        if(filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PSX).join(" ")))
            name = ff7save->region(s);
        else if(filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PGE).join(" ")))
            name = ff7save->region(s).append(QStringLiteral(".mcs"));
        else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PS3).join(" ")))
            name = ff7save->region(s).mid(0, 12).append(QTextCodec::codecForName("Shift-JIS")->fromUnicode(ff7save->region(s).mid(12)).toHex().toUpper().append(QStringLiteral(".PSV")));
        saveDialog->selectFile(nameTemplate.arg(saveDialog->directory().path(), name));
    });

    connect(saveDialog, &QFileDialog::fileSelected, this, [saveDialog, &fileName, &selectedType](const QString &fileSelected){
        selectedType = saveDialog->selectedNameFilter();
        fileName = fileSelected;
    });

    saveDialog->exec();

    if (fileName.isEmpty())
        return;
    FF7SaveInfo::FORMAT newType = typeMap[selectedType];

    if (ff7save->exportFile(fileName, newType, s))
        QMessageBox::information(this, tr("Save Successfully"), tr("File Saved Successfully, Going Back To The Selection Dialog"));
    else
        QMessageBox::information(this, tr("Save Error"), tr("Error On File Save, Going Back To The Selection Dialog"));
    done(3);
}

void errbox::setSingleSlot(bool single)
{
    if (single) {
        btnNext->setEnabled(false);
        btnPrev->setEnabled(false);
        singleSlot = true;
    } else {
        btnNext->setEnabled(true);
        btnPrev->setEnabled(true);
        singleSlot = false;
    }
}

bool errbox::isSingleSlot()
{
    return singleSlot;
}

void errbox::setIcon(QPixmap pix)
{
    lblIcon->setPixmap(pix.scaled(lblIcon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
