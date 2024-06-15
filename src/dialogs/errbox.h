//  SPDX-FileCopyrightText: 2010 - 2020 Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <FF7Save>
#include <SaveIcon>

class errbox : public QDialog
{
    Q_OBJECT

public:
    explicit errbox(QWidget *parent = nullptr, FF7Save *ff7data = nullptr, int slot = 0);
    bool isSingleSlot();
    void setSingleSlot(bool single);
protected:
    void keyPressEvent(QKeyEvent *e);
private slots:
    void setIcon(QPixmap);
    void btnPrevClicked();
    void btnExportClicked();
    void btnViewClicked();
    void btnNextClicked();
private:
    int s;
    bool singleSlot = false;
    FF7Save *ff7save = nullptr;
    SaveIcon *save_icon = nullptr;
    QPushButton *btnNext = nullptr;
    QPushButton *btnPrev = nullptr;
    QPushButton *btnView = nullptr;
    QPushButton *btnExport = nullptr;
    QLabel *lblRegionString = nullptr;
    QLabel *lblIcon = nullptr;
};
