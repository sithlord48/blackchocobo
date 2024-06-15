//  SPDX-FileCopyrightText: 2024 Chris Rizzitello <sithlord48@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QWidget>

class ItemListView;

class QCheckBox;
class QCommandLinkButton;
class QDoubleSpinBox;
class QGroupBox;
class QLabel;
class QPushButton;
class QSpinBox;

class ItemTab : public QWidget
{
    Q_OBJECT
public:
    explicit ItemTab(QWidget *parent = nullptr);
    ItemListView* itemList() { return m_itemList; }
    void setGil(quint32 newGil);
    quint32 gil() const;
    void setGp(quint16 newGp);
    quint16 gp() const;
    void setBattles(quint16 newBattles);
    quint16 battles() const;
    void setRuns(quint16 newRuns);
    quint16 runs() const;
    bool mysteryPanties() const;
    void setMysteryPanties(bool pickedup);
    bool daughterLetter() const;
    void setDaughterLetter(bool pickedup);
    bool wifeLetter() const;
    void setWifeLetter(bool pickedup);
signals:
    void gilChanged(quint32 gil);
    void gpChanged(quint16 gp);
    void battlesChanged(quint16 battles);
    void runsChanged(quint16 runs);
    void addedAllItems();
    void clearedAllItems();
    void requestFlyerSearch();
    void requestKeyItemSearch();
    void mysteryPantiesChanged(bool pickedup);
    void daughterLetterChanged(bool pickedup);
    void wifeLetterChanged(bool pickedup);
protected:
    void changeEvent(QEvent *e);
private:
    void init_connections();
    void updateText();
    void allItems();
    void clearItems();
    QGroupBox* m_groupInventory = nullptr;
    QGroupBox* m_groupMoney = nullptr;
    QGroupBox* m_groupBattles = nullptr;
    QGroupBox* m_groupFlyers = nullptr;
    QGroupBox* m_groupKeyItems = nullptr;
    QGroupBox* m_groupUnusedKeyItems = nullptr;
    ItemListView* m_itemList = nullptr;
    QPushButton* m_btn_allItems = nullptr;
    QPushButton* m_btn_clearItems = nullptr;
    QDoubleSpinBox* m_sb_gil = nullptr;
    QLabel* m_lbl_gil = nullptr;
    QSpinBox* m_sb_gp = nullptr;
    QLabel* m_lbl_gp = nullptr;
    QSpinBox* m_sb_battles = nullptr;
    QLabel* m_lbl_battles = nullptr;
    QSpinBox* m_sb_runs = nullptr;
    QLabel* m_lbl_runs = nullptr;
    QCommandLinkButton* m_btn_findFlyers = nullptr;
    QCommandLinkButton* m_btn_keyItems = nullptr;
    QCheckBox* m_cb_mysterypanties = nullptr;
    QCheckBox* m_cb_daughterLetter = nullptr;
    QCheckBox* m_cb_wifeLetter = nullptr;
    quint32 m_gil;
    quint16 m_gp;
    quint16 m_battles;
    quint16 m_runs;
};
