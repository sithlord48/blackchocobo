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

#include <FF7Save.h>

#include "bcsettings.h"

QRect readGeometry()
{
    QByteArray geometry = BCSettings::instance()->value(SETTINGS::MAINGEOMETRY).toByteArray();
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
    const QRect mainRect = readGeometry();
    QFileDialog dialog(parent, title, path.isEmpty() ? QDir::homePath() : path, nameFilters);
    int dialogWidth = int(mainRect.width() * 0.80);
    int dialogHeight = int (mainRect.height() * 0.80);
    int fmw = dialog.fontMetrics().height();
    QSize iconSize = QSize(fmw, fmw);
    const QList<QAbstractButton*> buttons = dialog.findChildren<QAbstractButton*>(QString(), Qt::FindChildrenRecursively);
    for(QAbstractButton * btn: buttons)
        btn->setIconSize(iconSize);
    dialog.setGeometry(mainRect.x() + ((mainRect.width() - dialogWidth) / 2), mainRect.y() + ((mainRect.height() - dialogHeight) /2), dialogWidth, dialogHeight);
    dialog.setLabelText(QFileDialog::LookIn, QObject::tr("Places"));
    QString fileName = initSelection;
    if (!fileName.isEmpty())
        dialog.selectFile(fileName);
    QList<QUrl> sideBarUrls;
    const QStringList SideBarUrls = BCSettings::instance()->value(SETTINGS::SIDEBARURLS).toStringList();
    for(const QString &url : SideBarUrls)
        sideBarUrls.append(QUrl::fromLocalFile(url));
    dialog.setSidebarUrls(sideBarUrls);

    if(dialog.exec() == QFileDialog::Accepted)
        return dialog.selectedFiles().at(0);
    return QString();
}

QString BCDialog::getExistingDirectory(QWidget *parent, const QString &title, const QString &path, const QString &initSelection)
{
    QRect mainRect = readGeometry();
    int dialogWidth = int(mainRect.width() * 0.80);
    int dialogHeight = int (mainRect.height() * 0.80);
    QFileDialog dialog(parent, title, path.isEmpty() ? QDir::homePath() : path, initSelection);
    int fmw = dialog.fontMetrics().height();
    QSize iconSize = QSize(fmw, fmw);
    QList<QAbstractButton*> buttons = dialog.findChildren<QAbstractButton*>(QString(), Qt::FindChildrenRecursively);
    for(QAbstractButton * btn: buttons)
        btn->setIconSize(iconSize);
    dialog.setGeometry(mainRect.x() + ((mainRect.width() - dialogWidth) / 2), mainRect.y() + ((mainRect.height() - dialogHeight) /2), dialogWidth, dialogHeight);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setFilter(QDir::Dirs);
    QString fileName = initSelection;
    if (!fileName.isEmpty())
        dialog.selectFile(fileName);
    dialog.setLabelText(QFileDialog::LookIn, QObject::tr("Places"));
    QList<QUrl> sideBarUrls;
    const QStringList URLS = BCSettings::instance()->value(SETTINGS::SIDEBARURLS).toStringList();
    for(const QString &url : URLS)
        sideBarUrls.append(QUrl::fromLocalFile(url));
    dialog.setSidebarUrls(sideBarUrls);

    if(dialog.exec() == QFileDialog::Accepted)
        return dialog.selectedFiles().at(0);
    return QString();
}

QString BCDialog::getSaveFileName(QWidget  *parent, const QString &region, const QString &title, const QString &path , const QString &nameFilters, QString* chosenType, const QString &initSelection)
{
    QRect mainRect = readGeometry();
    int dialogWidth = int(mainRect.width() * 0.80);
    int dialogHeight = int (mainRect.height() * 0.80);
    QFileDialog dialog(parent, title, path.isEmpty() ? QDir::homePath() : path, nameFilters);
    dialog.setGeometry(mainRect.x() + ((mainRect.width() - dialogWidth) / 2), mainRect.y() + ((mainRect.height() - dialogHeight) /2), dialogWidth, dialogHeight);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setLabelText(QFileDialog::LookIn, QObject::tr("Places"));
    QString fileName = initSelection;
    if (!fileName.isEmpty())
        dialog.selectFile(fileName);
    QList<QUrl> sideBarUrls;
    const QStringList URLS = BCSettings::instance()->value(SETTINGS::SIDEBARURLS).toStringList();
    for(const QString &url : URLS)
        sideBarUrls.append(QUrl::fromLocalFile(url));
    dialog.setSidebarUrls(sideBarUrls);

    if(chosenType)
        dialog.selectNameFilter(chosenType->mid(0));
    if(nameFilters.contains(QStringLiteral(".char")))
        dialog.setDefaultSuffix(QStringLiteral(".char"));

    QObject::connect(&dialog, &QFileDialog::filterSelected, [&dialog, region](const QString &filter){
        QString name;
        if(filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PSX).join(" "))) {
            dialog.setDefaultSuffix(QString());
            name = region;
        } else if(filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PGE).join(" "))) {
            dialog.setDefaultSuffix(QStringLiteral(".mcs"));
            name = region;
        } else if(filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PDA).join(" "))) {
            dialog.setDefaultSuffix(QStringLiteral(".mcb"));
            name = region;
        } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PS3).join(" "))) {
            dialog.setDefaultSuffix(QStringLiteral(".PSV"));
            name = region.mid(0, 12).append(QTextCodec::codecForName("Shift-JIS")->fromUnicode(region.mid(12)).toHex().toUpper());
        } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PC).join(" "))) {
            dialog.setDefaultSuffix(QStringLiteral(".ff7"));
            name = QStringLiteral("save00");
        } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::SWITCH).join(" "))) {
            dialog.setDefaultSuffix(QString());
            name = QStringLiteral("ff7slot00");
        } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::PSP).join(" "))) {
            dialog.setDefaultSuffix(QStringLiteral(".VMP"));
            name = QStringLiteral("SCEVMC0");
        } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::VMC).join(" "))) {
            dialog.setDefaultSuffix(QStringLiteral(".mcr"));
            name = QStringLiteral("vmcCard");
        } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::DEX).join(" "))) {
            dialog.setDefaultSuffix(QStringLiteral(".gme"));
            name = QStringLiteral("dexCard");
        } else if (filter.contains(FF7SaveInfo::instance()->typeExtension(FF7SaveInfo::FORMAT::VGS).join(" "))) {
            dialog.setDefaultSuffix(QStringLiteral(".vgs"));
            name = QStringLiteral("vgsCard");
        }
        QString ext = dialog.defaultSuffix().isEmpty() ? QString() : QStringLiteral(".%1").arg(dialog.defaultSuffix());
        dialog.selectFile(QStringLiteral("%1%2").arg(name, ext));
    });

    if(dialog.exec() == QFileDialog::Accepted) {
        if (!nameFilters.contains(QStringLiteral(".char")))
            chosenType->replace(chosenType->mid(0), dialog.selectedNameFilter());
        return dialog.selectedFiles().at(0);
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
    QStringList urls = BCSettings::instance()->value(SETTINGS::SIDEBARURLS).toStringList();
    for (const QString &string : qAsConst(urls))
        listWidget.addItem(string);
    QPushButton btnAdd(QIcon::fromTheme(QStringLiteral("list-add"), QIcon(QStringLiteral(":/icon/list-add"))), QString(), nullptr);
    btnAdd.setToolTip(QObject::tr("Add a place"));
    QObject::connect(&btnAdd, &QPushButton::clicked, [parent, &listWidget]{
        QString fileName = getExistingDirectory(parent, QObject::tr("Select a path to add to places"));
        if (!fileName.isEmpty())
            listWidget.addItem(fileName);
    });
    QPushButton btnRemove(QIcon::fromTheme(QStringLiteral("list-remove"), QIcon(QStringLiteral(":/icon/list-remove"))), QString(), nullptr);
    btnRemove.setToolTip(QObject::tr("Remove selected place"));
    QObject::connect(&btnRemove, &QPushButton::clicked, [&listWidget] {
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

    QObject::connect(&btnBox, &QDialogButtonBox::clicked, [&btnBox, &listWidget, &dialog](QAbstractButton *button){
        if (button == btnBox.button(QDialogButtonBox::Save))
            dialog.accept();
        else if (button == btnBox.button(QDialogButtonBox::Cancel))
            dialog.reject();
        else if (button == btnBox.button(QDialogButtonBox::RestoreDefaults)) {
            listWidget.clear();
            listWidget.addItem(QDir::rootPath());
            listWidget.addItem(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
            if(!BCSettings::instance()->value(SETTINGS::LOADPATH).toString().isEmpty())
                listWidget.addItem(BCSettings::instance()->value(SETTINGS::LOADPATH).toString());
            if(!BCSettings::instance()->value(SETTINGS::PCSAVEPATH).toString().isEmpty())
                listWidget.addItem(BCSettings::instance()->value(SETTINGS::PCSAVEPATH).toString());
            if(!BCSettings::instance()->value(SETTINGS::EMUSAVEPATH).toString().isEmpty())
                listWidget.addItem(BCSettings::instance()->value(SETTINGS::EMUSAVEPATH).toString());
            if(!BCSettings::instance()->value(SETTINGS::STATFOLDER).toString().isEmpty())
                listWidget.addItem(BCSettings::instance()->value(SETTINGS::STATFOLDER).toString());
        } else if (button == btnBox.button(QDialogButtonBox::Reset)) {
            listWidget.clear();
            listWidget.addItems(BCSettings::instance()->value(SETTINGS::SIDEBARURLS).toStringList());
        }
    });

    if(dialog.exec() == QDialog::Accepted) {
        urls.clear();
        for ( int i =0; i < listWidget.count(); i++)
            urls.append(listWidget.item(i)->text());
        BCSettings::instance()->setValue(SETTINGS::SIDEBARURLS, urls);
    }
}


int BCDialog::fixTimeDialog(QWidget *parent, bool slotPAL)
{
    QMessageBox dialog(parent);
    dialog.setIconPixmap(QPixmap(":/icon/fix_time"));
    dialog.setText(QObject::tr("Adjust the play time?"));
    dialog.setInformativeText(QObject::tr("Old region was %1hz\nNew region is %2hz").arg(slotPAL ? 50 : 60).arg(!slotPAL ? 50 : 60));
    dialog.setWindowTitle( slotPAL ? QObject::tr("PAL -> NTSC Conversion") : QObject::tr("NTSC -> PAL Conversion"));
    dialog.addButton(QMessageBox::Yes);
    dialog.addButton(QMessageBox::No);
    return dialog.exec();
}
