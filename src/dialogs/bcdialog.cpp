/****************************************************************************/
//    copyright 2020 Chris Rizzitello <sithlord48@gmail.com>                //
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
#include "bcdialog.h"

#include <QAction>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QTextCodec>

#include <AchievementEditor.h>
#include <FF7Save.h>

#include "../bcsettings.h"

QRect readGeometry()
{
    QByteArray geometry = BCSettings::value(SETTINGS::MAINGEOMETRY).toByteArray();
    if (geometry.size() < 4)
        return QRect();
    QDataStream stream(geometry);
    stream.setVersion(QDataStream::Qt_4_0);
    const quint32 magicNumber = 0x1D9D0CB;
    quint32 storedMagicNumber;
    stream >> storedMagicNumber;
    if (storedMagicNumber != magicNumber)
        return QRect();
    const quint16 currentMajorVersion = 3;
    quint16 majorVersion = 0;
    quint16 minorVersion = 0;
    stream >> majorVersion >> minorVersion;
    if (majorVersion > currentMajorVersion)
        return QRect();
    // (Allow all minor versions.)
    QRect restoredFrameGeometry;
    QRect restoredGeometry;
    QRect restoredNormalGeometry;
    qint32 restoredScreenNumber;
    quint8 maximized;
    quint8 fullScreen;
    qint32 restoredScreenWidth = 0;
    stream >> restoredFrameGeometry // Only used for sanity checks in version 0
           >> restoredNormalGeometry
           >> restoredScreenNumber
           >> maximized
           >> fullScreen
           >> restoredScreenWidth
           >> restoredGeometry;
    return restoredGeometry;
}

QString BCDialog::getOpenFileName(QWidget  *parent, const QString &title, const QString &path , const QString &nameFilters, const QString &initSelection)
{
    auto dialog = getFileDialog(parent, title, path, nameFilters, initSelection);

    if(dialog->exec() == QFileDialog::Accepted)
        return dialog->selectedFiles().at(0);
    return QString();
}

QString BCDialog::getExistingDirectory(QWidget *parent, const QString &title, const QString &path, const QString &initSelection)
{
    auto dialog = getFileDialog(parent, title, path, QString(), initSelection);
    dialog->setFileMode(QFileDialog::Directory);
    dialog->setFilter(QDir::Dirs);

    if(dialog->exec() == QFileDialog::Accepted)
        return dialog->selectedFiles().at(0);
    return QString();
}

QString BCDialog::getSaveFileName(QWidget  *parent, const QString &region, const QString &title, const QString &path , const QString &nameFilters, QString* chosenType, const QString &initSelection)
{
    auto dialog = getFileDialog(parent, title, path, nameFilters, initSelection);
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->setAcceptMode(QFileDialog::AcceptSave);

    if(nameFilters.contains(QStringLiteral(".char"))) {
        dialog->setDefaultSuffix(QStringLiteral(".char"));
    } else {
        QObject::connect(dialog, &QFileDialog::filterSelected, [dialog, region](const QString &filter) {
            QString name;
            if(filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PSX).join(" "))) {
                dialog->setDefaultSuffix(QString());
                name = region;
            } else if(filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PGE).join(" "))) {
                dialog->setDefaultSuffix(QStringLiteral(".mcs"));
                name = region;
            } else if(filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PDA).join(" "))) {
                dialog->setDefaultSuffix(QStringLiteral(".mcb"));
                name = region;
            } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PS3).join(" "))) {
                dialog->setDefaultSuffix(QStringLiteral(".PSV"));
                name = region.mid(0, 12).append(QTextCodec::codecForName("Shift-JIS")->fromUnicode(region.mid(12)).toHex().toUpper());
            } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PC).join(" "))) {
                dialog->setDefaultSuffix(QStringLiteral(".ff7"));
                name = QStringLiteral("save00");
            } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::SWITCH).join(" "))) {
                dialog->setDefaultSuffix(QString());
                name = QStringLiteral("ff7slot00");
            } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PSP).join(" "))) {
                dialog->setDefaultSuffix(QStringLiteral(".VMP"));
                name = QStringLiteral("SCEVMC0");
            } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::VMC).join(" "))) {
                dialog->setDefaultSuffix(QStringLiteral(".mcr"));
                name = QStringLiteral("vmcCard");
            } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::DEX).join(" "))) {
                dialog->setDefaultSuffix(QStringLiteral(".gme"));
                name = QStringLiteral("dexCard");
            } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::VGS).join(" "))) {
                dialog->setDefaultSuffix(QStringLiteral(".vgs"));
                name = QStringLiteral("vgsCard");
            }
            if(!dialog->defaultSuffix().isEmpty())
                name.append(QStringLiteral(".%1").arg(dialog->defaultSuffix()));
            dialog->selectFile(name);
        });
    }

    if(!chosenType->isEmpty())
        dialog->selectNameFilter(chosenType->mid(0));

    if(dialog->exec() == QFileDialog::Accepted) {
        if (!nameFilters.contains(QStringLiteral(".char")) && chosenType)
            chosenType->replace(chosenType->mid(0), dialog->selectedNameFilter());
        return dialog->selectedFiles().at(0);
    }
    return QString();
}

void BCDialog::editSideBarPaths(QWidget *parent)
{
    QDialog dialog(parent);
    dialog.setWindowTitle(QObject::tr("Edit Places"));
    dialog.setGeometry(parent->geometry());
    int fmw = dialog.fontMetrics().height();
    QSize iconSize = QSize(fmw, fmw);
    QListWidget listWidget;
    listWidget.setSelectionMode(QListWidget::SingleSelection);
    listWidget.setDragDropMode(QAbstractItemView::InternalMove);
    QStringList urls = BCSettings::value(SETTINGS::SIDEBARURLS).toStringList();
    for (const QString &string : qAsConst(urls))
        listWidget.addItem(string);
    QPushButton btnAdd(QIcon::fromTheme(QStringLiteral("list-add")), QString(), nullptr);
    btnAdd.setToolTip(QObject::tr("Add a place"));
    QObject::connect(&btnAdd, &QPushButton::clicked, &dialog, [parent, &listWidget]{
        QString fileName = getExistingDirectory(parent, QObject::tr("Select a path to add to places"));
        if (!fileName.isEmpty())
            listWidget.addItem(fileName);
    });
    QPushButton btnRemove(QIcon::fromTheme(QStringLiteral("list-remove")), QString(), nullptr);
    btnRemove.setToolTip(QObject::tr("Remove selected place"));
    QObject::connect(&btnRemove, &QPushButton::clicked, &dialog, [&listWidget] {
        if (!listWidget.selectedItems().isEmpty())
            delete listWidget.takeItem(listWidget.row(listWidget.selectedItems().first()));
    });
    QHBoxLayout btnLayout;
    btnLayout.addWidget(&btnAdd);
    btnLayout.addWidget(&btnRemove);
    btnLayout.addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Fixed));
    QDialogButtonBox btnBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel | QDialogButtonBox::Reset | QDialogButtonBox::RestoreDefaults);
    btnBox.button(QDialogButtonBox::RestoreDefaults)->setToolTip(QObject::tr("Restore default places"));
    btnBox.button(QDialogButtonBox::Reset)->setToolTip(QObject::tr("Reset values to stored settings"));
    btnBox.button(QDialogButtonBox::Save)->setToolTip(QObject::tr("Save Changes"));
    btnBox.button(QDialogButtonBox::Cancel)->setToolTip(QObject::tr("Close"));
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(&listWidget);
    mainLayout->addLayout(&btnLayout);
    mainLayout->addWidget(&btnBox);
    dialog.setLayout(mainLayout);
    const QList<QAbstractButton*> buttons = dialog.findChildren<QAbstractButton *>(QString(),Qt::FindChildrenRecursively);
    for (QAbstractButton *btn : buttons)
        btn->setIconSize(iconSize);

    QObject::connect(&btnBox, &QDialogButtonBox::clicked, &dialog, [&btnBox, &listWidget, &dialog](const QAbstractButton *button){
        if (button == btnBox.button(QDialogButtonBox::Save))
            dialog.accept();
        else if (button == btnBox.button(QDialogButtonBox::Cancel))
            dialog.reject();
        else if (button == btnBox.button(QDialogButtonBox::RestoreDefaults)) {
            listWidget.clear();
            listWidget.addItem(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
            if(!BCSettings::value(SETTINGS::LOADPATH).toString().isEmpty())
                listWidget.addItem(BCSettings::value(SETTINGS::LOADPATH).toString());
            if(!BCSettings::value(SETTINGS::PCSAVEPATH).toString().isEmpty())
                listWidget.addItem(BCSettings::value(SETTINGS::PCSAVEPATH).toString());
            if(!BCSettings::value(SETTINGS::EMUSAVEPATH).toString().isEmpty())
                listWidget.addItem(BCSettings::value(SETTINGS::EMUSAVEPATH).toString());
            if(!BCSettings::value(SETTINGS::STATFOLDER).toString().isEmpty())
                listWidget.addItem(BCSettings::value(SETTINGS::STATFOLDER).toString());
        } else if (button == btnBox.button(QDialogButtonBox::Reset)) {
            listWidget.clear();
            listWidget.addItems(BCSettings::value(SETTINGS::SIDEBARURLS).toStringList());
        }
    });

    if(dialog.exec() == QDialog::Accepted) {
        urls.clear();
        for ( int i =0; i < listWidget.count(); i++)
            urls.append(listWidget.item(i)->text());
        BCSettings::setValue(SETTINGS::SIDEBARURLS, urls);
    }
}


int BCDialog::fixTimeDialog(QWidget *parent, bool slotPAL)
{
    QMessageBox dialog(parent);
    dialog.setIconPixmap(QPixmap(":/icons/common/dialog-question"));
    dialog.setText(QObject::tr("Adjust the play time?"));
    dialog.setInformativeText(QObject::tr("Old region was %1hz\nNew region is %2hz").arg(slotPAL ? 50 : 60).arg(!slotPAL ? 50 : 60));
    dialog.setWindowTitle( slotPAL ? QObject::tr("PAL -> NTSC Conversion") : QObject::tr("NTSC -> PAL Conversion"));
    dialog.addButton(QMessageBox::Yes);
    dialog.addButton(QMessageBox::No);
    return dialog.exec();
}

void BCDialog::achievementDialog(QWidget *parent, const QString &fileName)
{
    QDialog dialog;
    dialog.setWindowTitle(QObject::tr("Achievement Editor"));
    dialog.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    const QRect mainRect = readGeometry();
    dialog.setFixedHeight(int (mainRect.height() * 0.90));
    auto achievementEditor = new AchievementEditor(&dialog);
    achievementEditor->openFile(fileName);
    achievementEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::StandardButton::Save | QDialogButtonBox::StandardButton::Cancel);
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(achievementEditor);
    layout->addWidget(buttonBox);
    dialog.setLayout(layout);
    buttonBox->button(QDialogButtonBox::StandardButton::Save)->setToolTip(QObject::tr("Close and save changes"));
    buttonBox->button(QDialogButtonBox::StandardButton::Cancel)->setToolTip(QObject::tr("Close and forget changes"));

    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::close);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, [achievementEditor, fileName, &dialog] {
        if (!achievementEditor->saveFile(fileName))
            QMessageBox::critical(&dialog, QObject::tr("Failed To Save File"), QString(QObject::tr("Failed To Write File\nFile:%1")).arg(fileName));
        dialog.close();
    });

    if(parent)
        dialog.move(mainRect.x() + (mainRect.width() - dialog.sizeHint().width()) / 2, mainRect.y() + (mainRect.height() - dialog.height())/2);
    dialog.exec();
}

QFileDialog* BCDialog::getFileDialog(QWidget *parent, const QString &title, const QString &path, const QString &nameFilters, const QString &initSelection)
{
    auto dialog = new QFileDialog(parent, title, path.isEmpty() ? QDir::homePath() : path, nameFilters);
    const QRect mainRect = readGeometry();
    int dialogWidth = int(mainRect.width() * 0.80);
    int dialogHeight = int (mainRect.height() * 0.80);

    QSize iconSize = QSize(dialog->fontMetrics().height(), dialog->fontMetrics().height());
    const QList<QAbstractButton*> buttons = dialog->findChildren<QAbstractButton*>(QString(), Qt::FindChildrenRecursively);
    for(QAbstractButton * btn: buttons)
        btn->setIconSize(iconSize);

    dialog->setGeometry(mainRect.x() + ((mainRect.width() - dialogWidth) / 2), mainRect.y() + ((mainRect.height() - dialogHeight) /2), dialogWidth, dialogHeight);
    dialog->setLabelText(QFileDialog::LookIn, QObject::tr("Places"));

    QList<QUrl> sideBarUrls;
    const QFileInfoList drives = QDir::drives();
    for (const QFileInfo &drive : drives)
        sideBarUrls.append(QUrl::fromLocalFile(drive.path()));
    const QStringList SideBarUrls = BCSettings::value(SETTINGS::SIDEBARURLS).toStringList();
    for(const QString &url : SideBarUrls)
        sideBarUrls.append(QUrl::fromLocalFile(url));
    dialog->setSidebarUrls(sideBarUrls);

    if (!initSelection.isEmpty())
        dialog->selectFile(initSelection);

    return dialog;
}
