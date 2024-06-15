//  SPDX-FileCopyrightText: 2024 Chris Rizzitello <sithlord48@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#include "itemtab.h"
#include <QCheckBox>
#include <QEvent>
#include <ItemListView.h>
#include <QGroupBox>
#include <QCommandLinkButton>
#include <QPushButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <FF7ItemModel>

ItemTab::ItemTab(QWidget *parent)
    : QWidget(parent)
    , m_groupInventory(new QGroupBox(this))
    , m_groupMoney(new QGroupBox(this))
    , m_groupBattles(new QGroupBox(this))
    , m_groupFlyers(new QGroupBox(this))
    , m_groupKeyItems(new QGroupBox(this))
    , m_groupUnusedKeyItems(new QGroupBox(this))
    , m_itemList(new ItemListView(this))
    , m_btn_allItems(new QPushButton(this))
    , m_btn_clearItems(new QPushButton(this))
    , m_sb_gil(new QDoubleSpinBox(this))
    , m_lbl_gil(new QLabel(this))
    , m_sb_gp(new QSpinBox(this))
    , m_lbl_gp(new QLabel(this))
    , m_sb_battles(new QSpinBox(this))
    , m_lbl_battles(new QLabel(this))
    , m_sb_runs(new QSpinBox(this))
    , m_lbl_runs(new QLabel(this))
    , m_btn_findFlyers(new QCommandLinkButton(this))
    , m_btn_keyItems(new QCommandLinkButton(this))
    , m_cb_mysterypanties(new QCheckBox(this))
    , m_cb_daughterLetter(new QCheckBox(this))
    , m_cb_wifeLetter(new QCheckBox(this))
    , m_gil(0)
    , m_gp(0)
    , m_battles(0)
    , m_runs(0)
{
    auto inventoryLayout = new QVBoxLayout();
    inventoryLayout->addWidget(m_itemList);
    inventoryLayout->addWidget(m_btn_allItems);
    inventoryLayout->addWidget(m_btn_clearItems);
    m_groupInventory->setLayout(inventoryLayout);
    m_groupInventory->setContentsMargins(0,0,0,0);
    m_itemList->setFixedWidth(m_itemList->width() + 8);
    m_groupInventory->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    m_sb_gil->setMinimum(0);
    m_sb_gil->setMaximum(4294967295);
    m_sb_gil->setDecimals(0);
    m_sb_gil->setWrapping(true);
    m_sb_gil->setAccelerated(true);
    m_sb_gil->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_sb_gil->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    auto gilLayout = new QHBoxLayout();
    gilLayout->addWidget(m_lbl_gil);
    gilLayout->addWidget(m_sb_gil);

    m_sb_gp->setMinimum(0);
    m_sb_gp->setMaximum(10000);
    m_sb_gp->setWrapping(true);
    m_sb_gp->setAccelerated(true);
    m_sb_gp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_sb_gp->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    auto gpLayout = new QHBoxLayout();
    gpLayout->addWidget(m_lbl_gp);
    gpLayout->addWidget(m_sb_gp);

    auto moneyLayout = new QVBoxLayout();
    moneyLayout->addLayout(gilLayout);
    moneyLayout->addLayout(gpLayout);
    moneyLayout->setSpacing(3);

    m_groupMoney->setLayout(moneyLayout);
    m_groupMoney->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    m_sb_battles->setMinimum(0);
    m_sb_battles->setMaximum(65535);
    m_sb_battles->setWrapping(true);
    m_sb_battles->setAccelerated(true);
    m_sb_battles->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_sb_battles->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    auto battleLayout = new QHBoxLayout();
    battleLayout->addWidget(m_lbl_battles);
    battleLayout->addWidget(m_sb_battles);

    m_sb_runs->setMinimum(0);
    m_sb_runs->setMaximum(65535);
    m_sb_runs->setWrapping(true);
    m_sb_runs->setAccelerated(true);
    m_sb_runs->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_sb_runs->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    auto runsLayout = new QHBoxLayout();
    runsLayout->addWidget(m_lbl_runs);
    runsLayout->addWidget(m_sb_runs);

    auto battlesLayout = new QVBoxLayout();
    battlesLayout->addLayout(battleLayout);
    battlesLayout->addLayout(runsLayout);
    battlesLayout->setSpacing(3);

    m_groupBattles->setLayout(battlesLayout);
    m_groupBattles->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    m_btn_findFlyers->setIcon(QIcon::fromTheme("go-next"));

    auto flyersLayout = new QHBoxLayout();
    flyersLayout->addWidget(m_btn_findFlyers);

    m_groupFlyers->setLayout(flyersLayout);
    m_groupFlyers->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    m_btn_keyItems->setIcon(QIcon::fromTheme("go-next"));

    auto keyItemLayout = new QHBoxLayout();
    keyItemLayout->addWidget(m_btn_keyItems);

    m_groupKeyItems->setLayout(keyItemLayout);
    m_groupKeyItems->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    auto unusedKeyItemLayout = new QVBoxLayout();
    unusedKeyItemLayout->addWidget(m_cb_mysterypanties);
    unusedKeyItemLayout->addWidget(m_cb_daughterLetter);
    unusedKeyItemLayout->addWidget(m_cb_wifeLetter);

    m_groupUnusedKeyItems->setLayout(unusedKeyItemLayout);
    m_groupUnusedKeyItems->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    auto rightLayout = new QVBoxLayout();
    rightLayout->addWidget(m_groupMoney);
    rightLayout->addWidget(m_groupBattles);
    rightLayout->addWidget(m_groupFlyers);
    rightLayout->addWidget(m_groupKeyItems);
    rightLayout->addWidget(m_groupUnusedKeyItems);
    rightLayout->addSpacerItem(new QSpacerItem(1, 10, QSizePolicy::Preferred, QSizePolicy::Expanding));

    auto widgetLayout = new QHBoxLayout();
    widgetLayout->addWidget(m_groupInventory);
    widgetLayout->addLayout(rightLayout);
    setLayout(widgetLayout);

    updateText();
    init_connections();
//Work around Qt 6.6.1 regression where it won't adjust the columns until after the gui is completely created
#if QT_VERSION == QT_VERSION_CHECK(6, 6, 1)
    for(int i=0;i < 3; i++)
        m_itemList->setColumnWidth(i, m_itemList->sizeHintForColumn(i));
#endif
}

void ItemTab::setGil(quint32 newGil)
{
    if(m_gil == newGil)
        return;

    m_gil = newGil;
    m_sb_gil->setValue(m_gil);

    Q_EMIT gilChanged(m_gil);
}

quint32 ItemTab::gil() const
{
    return m_gil;
}

void ItemTab::setGp(quint16 newGp)
{
    if(m_gp == newGp)
        return;
    m_gp = newGp;
    m_sb_gp->setValue(m_gp);
    Q_EMIT gpChanged(m_gp);
}

quint16 ItemTab::gp() const
{
    return m_gp;
}

void ItemTab::setBattles(quint16 newBattles)
{
    if(m_battles == newBattles)
        return;
    m_battles = newBattles;
    m_sb_battles->setValue(m_battles);
    Q_EMIT battlesChanged(m_battles);
}

quint16 ItemTab::battles() const
{
    return m_battles;
}

void ItemTab::setRuns(quint16 newRuns)
{
    if(m_runs == newRuns)
        return;
    m_runs = newRuns;
    m_sb_runs->setValue(m_runs);
    Q_EMIT runsChanged(m_runs);
}

quint16 ItemTab::runs() const
{
    return m_runs;
}

bool ItemTab::mysteryPanties() const
{
    return m_cb_mysterypanties->isChecked();
}

void ItemTab::setMysteryPanties(bool pickedup)
{
    m_cb_mysterypanties->setChecked(pickedup);
    Q_EMIT mysteryPantiesChanged(pickedup);
}

bool ItemTab::daughterLetter() const
{
    return m_cb_daughterLetter->isChecked();
}

void ItemTab::setDaughterLetter(bool pickedup)
{
    m_cb_daughterLetter->setChecked(pickedup);
    Q_EMIT daughterLetterChanged(pickedup);
}

bool ItemTab::wifeLetter() const
{
    return m_cb_wifeLetter->isChecked();
}

void ItemTab::setWifeLetter(bool pickedup)
{
    m_cb_wifeLetter->setChecked(pickedup);
    Q_EMIT wifeLetterChanged(pickedup);
}

void ItemTab::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        updateText();
    else
        QWidget::changeEvent(e);
}

void ItemTab::init_connections()
{
    connect(m_btn_allItems, &QPushButton::clicked, this, &ItemTab::allItems);
    connect(m_btn_clearItems, &QPushButton::clicked, this, &ItemTab::clearItems);
    connect(m_sb_gil, &QDoubleSpinBox::valueChanged, this, &ItemTab::setGil);
    connect(m_sb_gp, &QSpinBox::valueChanged, this, &ItemTab::setGp);
    connect(m_sb_battles, &QSpinBox::valueChanged, this, &ItemTab::setBattles);
    connect(m_sb_runs, &QSpinBox::valueChanged, this, &ItemTab::setRuns);
    connect(m_btn_findFlyers, &QCommandLinkButton::clicked, this, &ItemTab::requestFlyerSearch);
    connect(m_btn_keyItems, &QCommandLinkButton::clicked, this, &ItemTab::requestKeyItemSearch);
    connect(m_cb_mysterypanties, &QCheckBox::toggled, this, &ItemTab::setMysteryPanties);
    connect(m_cb_daughterLetter, &QCheckBox::toggled, this, &ItemTab::setDaughterLetter);
    connect(m_cb_wifeLetter, &QCheckBox::toggled, this, &ItemTab::setWifeLetter);
}

void ItemTab::updateText()
{
    m_groupInventory->setTitle(tr("Inventory"));
    m_btn_allItems->setText(tr("Add Max of All Items"));
    m_btn_clearItems->setText(tr("Clear All Items"));

    m_groupMoney->setTitle(tr("Money"));
    m_lbl_gil->setText(tr("Gil"));
    m_lbl_gp->setText(tr("GP"));

    m_groupBattles->setTitle(tr("Battles"));
    m_lbl_battles->setText(tr("Battles"));
    m_lbl_runs->setText(tr("Escapes"));

    m_groupKeyItems->setTitle(tr("KeyItems"));
    m_btn_keyItems->setText(tr("Search For \"KeyItem\" using item search mode on the location tab"));

    m_groupFlyers->setTitle(tr("Turtle Paradise Flyers Collected"));
    m_btn_findFlyers->setText(tr("Search for \"Turtle Paradise\" using item search mode on the location tab"));

    m_groupUnusedKeyItems->setTitle(tr("Unused KeyItems"));
    m_cb_mysterypanties->setText(tr("Mystery panties"));
    m_cb_daughterLetter->setText(tr("Letter to a Daughter"));
    m_cb_wifeLetter->setText(tr("Letter to a Wife"));
}

void ItemTab::allItems()
{
    QList<quint16>items;
    QList<quint16>emptyList;
    for (int i = 0; i < 320; i++) {
        if (FF7Item::placeHolderIds().contains(i))
            emptyList.append(FF7Item::EmptyItemData);
        else
            items.append(FF7Item::itemEncode(quint16(i), m_itemList->maximumItemQty()));
    }
    items.append(emptyList);
    static_cast<FF7ItemModel*>(m_itemList->model())->setItems(items);
    Q_EMIT addedAllItems();

}

void ItemTab::clearItems()
{
    QList<quint16>items;
    for (int i = 0; i < 320; i++)
        items.append(0xFFFF);
    static_cast<FF7ItemModel*>(m_itemList->model())->setItems(items);
    Q_EMIT clearedAllItems();
}


