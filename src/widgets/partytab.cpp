#include "partytab.h"

#include <FF7Char>
#include <CharEditor>

#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QResizeEvent>

void PartyTab::changeEvent(QEvent *e)
{
    if (e->type() != QEvent::LanguageChange) {
        QWidget::changeEvent(e);
    }
    updateText();
}
void PartyTab::resizeEvent(QResizeEvent *ev)
{
    if (ev->size() == ev->oldSize())
        return;
    for (auto button: std::as_const(m_btnChars)) {
        if(button != m_btnChars.at(0))
            button->resize(m_btnChars.at(0)->size());
        button->setIconSize(QSize(button->size().width() - 4 , button->size().height()- 6));
    }
}

PartyTab::PartyTab(QWidget *parent)
    : QWidget(parent)
    , m_groupParty(new QGroupBox(this))
    , m_groupCharacters(new QGroupBox(this))
    , m_charEditor(new CharEditor(this))
{
    m_groupParty->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_groupParty->setContentsMargins(0,0,0,0);
    m_groupCharacters->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    for(int i=0; i<9;i++) {
        auto button = new QPushButton(this);
        button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        button->setMinimumSize(118,132);
        button->setIconSize(QSize(112, 128));
        button->setIcon(FF7Char::pixmap(i));
        connect(button, &QPushButton::clicked, this, [this, i] {
            Q_EMIT requestCharacterSlotLoad(i);
            setCurrentButton(i);
        });
        m_btnChars.append(button);
    }

    updateText();
    auto partyLayout = new QHBoxLayout;
    for (auto combo : std::as_const(m_comboParty))
        partyLayout->addWidget(combo);
    m_groupParty->setLayout(partyLayout);

    auto buttonGrid = new QGridLayout;
    for (int i = 0; i < 9; i++)
        buttonGrid->addWidget(m_btnChars.at(i), i/3,  i % 3);
    m_groupCharacters->setLayout(buttonGrid);
    m_groupCharacters->setSizeIncrement(50, 50);

    auto leftLayout = new QVBoxLayout;
    leftLayout->addWidget(m_groupParty);
    leftLayout->addWidget(m_groupCharacters);
    leftLayout->addWidget(m_btnBoostCharacter);
    leftLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Fixed, QSizePolicy::Expanding));

    auto mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addWidget(m_charEditor, 2);
    setLayout(mainLayout);
    setMinimumSize(mainLayout->sizeHint());

    connect(m_charEditor, &CharEditor::idChanged, this, [=](qint8 id) {
        if(id == FF7Char::Sephiroth || id == FF7Char::YoungCloud)
            m_btnBoostCharacter->setVisible(false);
        else
            m_btnBoostCharacter->setVisible(true);
    });
}

void PartyTab::setPartyMembers(int p1, int p2, int p3)
{
    if ( (p1 < 0) || (p1 > 11))
        p1 = 12;
    if ((p2 < 0) || (p2 > 11))
        p2 = 12;
    if ((p3 < 0) || (p3 > 11))
        p3 = 12;
    blockSignals(true);
    m_comboParty.at(0)->setCurrentIndex(p1);
    m_comboParty.at(1)->setCurrentIndex(p2);
    m_comboParty.at(2)->setCurrentIndex(p3);
    blockSignals(false);
}

void PartyTab::setCharacter(const FF7CHAR &charData, const QString &processedName)
{
    m_charEditor->setChar(charData, processedName);
    if(charData.id == FF7Char::Sephiroth || charData.id == FF7Char::YoungCloud)
        m_btnBoostCharacter->setVisible(false);
    else
        m_btnBoostCharacter->setVisible(true);
}

void PartyTab::setButtonImageToId(int buttonNumber, int id)
{
    buttonNumber = std::clamp(buttonNumber, 0 , 8);
    m_btnChars.at(buttonNumber)->setIcon(FF7Char::pixmap(id));
}

void PartyTab::setButtonImagesToIds(const QList<int> &idList)
{
    for(int i = 0;i<9;i++)
        setButtonImageToId(i, idList.at(i));
}

void PartyTab::pressCharacterButton(int i)
{
    Q_EMIT m_btnChars.at(i)->clicked();
}

void PartyTab::updateText()
{
    m_groupParty->setTitle(tr("Party Members"));
    m_groupCharacters->setTitle(tr("Click on a Char To Edit  ===>"));
    if (m_comboParty.isEmpty()) {
        for (int i = 0 ; i < 3 ; i ++ ) {
            auto combo = new QComboBox(this);
            combo->setIconSize(QSize(24,32));
            combo->setMaxVisibleItems(13);
            connect(combo, &QComboBox::currentIndexChanged, this, [this, i](int index) {
                Q_EMIT partyChanged( i , index);
            });
            for (int l = 0; l <= FF7Char::totalCharacters(); l++)
                combo->addItem(FF7Char::icon(l), FF7Char::defaultName(l));
            combo->addItem(tr("-Empty-"));
            m_comboParty.append(combo);
        }
    } else {
        for(int i=0; i< 3; i++) {
            for (int l = 0; l <= FF7Char::totalCharacters(); l++)
                m_comboParty.at(i)->setItemText(l, FF7Char::defaultName(l));
            m_comboParty.at(i)->setItemText(12 ,tr("-Empty-"));
        }
    }
    if(!m_btnBoostCharacter) {
        m_btnBoostCharacter = new QPushButton();
        connect(m_btnBoostCharacter, &QPushButton::clicked, this, &PartyTab::boostCharacter);
    }
    m_btnBoostCharacter->setText(tr("Selected Character Max Stats/Weapons/Materia"));
}

void PartyTab::boostCharacter()
{
    if (m_charEditor->id() == FF7Char::YoungCloud || m_charEditor->id() == FF7Char::Sephiroth || m_charEditor->name().isNull())
        return;   //no char selected, sephiroth and young cloud.

    if (m_charEditor->id() == FF7Char::Chocobo) {
        m_charEditor->MaxStats();
        return;
    }

    int result = QMessageBox::question(this, tr("Black Chocobo"), tr("Do You Want To Also Replace %1's Equipment and Materia?").arg(m_charEditor->name()), QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
    switch (result) {
    case QMessageBox::StandardButton::Yes : m_charEditor->MaxEquip(); m_charEditor->MaxStats(); break;
    case QMessageBox::StandardButton::No: m_charEditor->MaxStats(); break;
    }
}

void PartyTab::setCurrentButton(int currentButton)
{
    QColor color;
    for(int i=0; i< 9; i++) {
        if(currentButton == i)
            color = palette().highlight().color();
        else
            color = palette().button().color();
        m_btnChars.at(i)->setStyleSheet(m_charStyle.arg(QString::number(color.red()), QString::number(color.green()), QString::number(color.blue())));
    }
}
