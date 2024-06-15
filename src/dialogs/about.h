//  SPDX-FileCopyrightText: 2010 - 2020 Chris Rizzitello <sithlord48@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QDialog>

namespace Ui
{
class About;
}

class About : public QDialog
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = nullptr);
    ~About();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::About *ui;
};
