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
    for (auto button: qAsConst(m_btnChars)) {
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
        connect(button, &QPushButton::clicked, this, [this, i](){
            Q_EMIT loadCharacterInSlot(i);
            setCurrentButton(i);
        });
        m_btnChars.append(button);
    }

    updateText();
    auto partyLayout = new QHBoxLayout;
    for (auto combo : qAsConst(m_comboParty))
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

    connect(m_charEditor, &CharEditor::id_changed, this, &PartyTab::characterIdChanged);
    connect(m_charEditor, &CharEditor::level_changed, this, &PartyTab::characterLevelChanged);
    connect(m_charEditor, &CharEditor::str_changed, this, &PartyTab::characterStrChanged);
    connect(m_charEditor, &CharEditor::vit_changed, this, &PartyTab::characterVitChanged);
    connect(m_charEditor, &CharEditor::mag_changed, this, &PartyTab::characterMagChanged);
    connect(m_charEditor, &CharEditor::spi_changed, this, &PartyTab::characterSpiChanged);
    connect(m_charEditor, &CharEditor::dex_changed, this, &PartyTab::characterDexChanged);
    connect(m_charEditor, &CharEditor::lck_changed, this, &PartyTab::characterLckChanged);
    connect(m_charEditor, &CharEditor::strBonus_changed, this, &PartyTab::characterStrBonusChanged);
    connect(m_charEditor, &CharEditor::vitBonus_changed, this, &PartyTab::characterVitBonusChanged);
    connect(m_charEditor, &CharEditor::magBonus_changed, this, &PartyTab::characterMagBonusChanged);
    connect(m_charEditor, &CharEditor::spiBonus_changed, this, &PartyTab::characterSpiBonusChanged);
    connect(m_charEditor, &CharEditor::dexBonus_changed, this, &PartyTab::characterDexBonusChanged);
    connect(m_charEditor, &CharEditor::lckBonus_changed, this, &PartyTab::characterLckBonusChanged);
    connect(m_charEditor, &CharEditor::limitLevel_changed, this, &PartyTab::characterLimitLevelChanged);
    connect(m_charEditor, &CharEditor::limitBar_changed, this, &PartyTab::characterLimitBarChanged);
    connect(m_charEditor, &CharEditor::name_changed, this, &PartyTab::characterNameChanged);
    connect(m_charEditor, &CharEditor::weapon_changed, this, &PartyTab::characterWeaponChanged);
    connect(m_charEditor, &CharEditor::armor_changed, this, &PartyTab::characterArmorChanged);
    connect(m_charEditor, &CharEditor::accessory_changed, this, &PartyTab::characterAccessoryChanged);
    connect(m_charEditor, &CharEditor::curHp_changed, this, &PartyTab::characterCurHpChanged);
    connect(m_charEditor, &CharEditor::maxHp_changed, this, &PartyTab::characterMaxHpChanged);
    connect(m_charEditor, &CharEditor::curMp_changed, this, &PartyTab::characterCurMpChanged);
    connect(m_charEditor, &CharEditor::maxMp_changed, this, &PartyTab::characterMaxMpChanged);
    connect(m_charEditor, &CharEditor::kills_changed, this, &PartyTab::characterKillsChanged);
    connect(m_charEditor, &CharEditor::row_changed, this, &PartyTab::characterRowChanged);
    connect(m_charEditor, &CharEditor::levelProgress_changed, this, &PartyTab::characterLevelProgressChanged);
    connect(m_charEditor, &CharEditor::sadnessfury_changed, this, &PartyTab::characterSadnessfuryChanged);
    connect(m_charEditor, &CharEditor::limits_changed, this, &PartyTab::characterLimitsChanged);
    connect(m_charEditor, &CharEditor::timesused1_changed, this, &PartyTab::characterTimesused1Changed);
    connect(m_charEditor, &CharEditor::timesused2_changed, this, &PartyTab::characterTimesused2Changed);
    connect(m_charEditor, &CharEditor::timesused3_changed, this, &PartyTab::characterTimesused3Changed);
    connect(m_charEditor, &CharEditor::baseHp_changed, this, &PartyTab::characterBaseHpChanged);
    connect(m_charEditor, &CharEditor::baseMp_changed, this, &PartyTab::characterBaseMpChanged);
    connect(m_charEditor, &CharEditor::exp_changed, this, &PartyTab::characterExpChanged);
    connect(m_charEditor, &CharEditor::mslotChanged, this, &PartyTab::characterMslotChanged);
    connect(m_charEditor, &CharEditor::Materias_changed, this, &PartyTab::characterMateriaChanged);
    connect(m_charEditor, &CharEditor::expNext_changed, this, &PartyTab::characterExpNextChanged);

}

void PartyTab::setPartyMembers(int p1, int p2, int p3)
{
    if(p1 < 0 || p1 > 11)
        p1 = 12;
    if(p2 < 0 || p2 > 11)
        p2 = 12;
    if(p3 < 0 || p3 > 11)
        p3 = 12;
    blockSignals(true);
    m_comboParty.at(0)->setCurrentIndex(p1);
    m_comboParty.at(1)->setCurrentIndex(p2);
    m_comboParty.at(2)->setCurrentIndex(p3);
    blockSignals(false);
}

void PartyTab::pressBoostCharacter()
{
    Q_EMIT m_btnBoostCharacter->pressed();
}

void PartyTab::setCharEditorSliderStyle(const QString &sliderStyleSheet)
{
    m_charEditor->setSliderStyle(sliderStyleSheet);
}

void PartyTab::setCharEditorToolBoxStyle(const QString &tabStyle)
{
    m_charEditor->setToolBoxStyle(tabStyle);
}

void PartyTab::setCharEditorEditableComboBoxes(bool editable)
{
    m_charEditor->setEditableComboBoxes(editable);
}

void PartyTab::setCharEditorShowPlaceholderMateria(bool shown)
{
    m_charEditor->setShowPlaceholderMateria(shown);
}

void PartyTab::setCharEditorAdvancedMode(bool adv)
{
    m_charEditor->setAdvancedMode(adv);
}

void PartyTab::setCharEditorAutoLevel(bool enabled)
{
    m_charEditor->setAutoLevel(enabled);
}

void PartyTab::setCharEditorAutoStatCalc(bool enabled)
{
    m_charEditor->setAutoStatCalc(enabled);
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
