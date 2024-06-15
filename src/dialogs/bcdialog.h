//  SPDX-FileCopyrightText: 2022 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QDir>

class QString;
class QWidget;
class QSettings;
class FF7Save;
class QFileDialog;
class BCDialog
{
public:
    static QString getOpenFileName(QWidget  *parent = nullptr, const QString &title = QString(), const QString &path = QDir::homePath(), const QString &nameFilters = QString(), const QString &initSelection = QString());
    static QString getExistingDirectory(QWidget  *parent = nullptr, const QString &title = QString(), const QString &path = QDir::homePath(), const QString &initSelection = QString());
    static QString getSaveFileName(QWidget  *parent = nullptr, const QString &region = QString(), const QString &title = QString(), const QString &path = QDir::homePath(), const QString &nameFilters = QString(), QString *chosenType = nullptr, const QString &initSelection = QString());
    static void editSideBarPaths(QWidget *parent= nullptr);
    static int fixTimeDialog(QWidget* parent, bool slotPAL = false);
    static void achievementDialog(QWidget *parent = nullptr, const QString &fileName = QString());
private:
    static QFileDialog* getFileDialog(QWidget *parent = nullptr, const QString &title = QString(), const QString &path = QDir::homePath(), const QString &nameFilters = QString(), const QString &initSelection = QString());
};
