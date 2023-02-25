#pragma once

#include <QWidget>
#include <Type_materia>

class QComboBox;
class QGroupBox;
class QPushButton;
class CharEditor;
struct FF7CHAR;
class PartyTab : public QWidget
{
    Q_OBJECT
public:
    explicit PartyTab(QWidget *parent = nullptr);

    /**
     * @brief Set the current party member setPartyMember
     * @param p1 - Id of member in slot 1
     * @param p2 - Id of member in slot 2
     * @param p3 - Id of member in slot 3
     */
    void setPartyMembers(int p1, int p2, int p3);
    void pressCharacterButton(int i);
    void pressBoostCharacter();

    // Methods to set the CharEditor up
    void setCharEditorSliderStyle(const QString &sliderStyleSheet);
    void setCharEditorToolBoxStyle(const QString &tabStyle);
    void setCharEditorEditableComboBoxes(bool editable);
    void setCharEditorShowPlaceholderMateria(bool shown);
    void setCharEditorAdvancedMode(bool adv);
    void setCharEditorAutoLevel(bool enabled);
    void setCharEditorAutoStatCalc(bool enabled);
    void setCharacter(const FF7CHAR &charData, const QString &processedName = QString());
    void setButtonImageToId(int buttonNumber = 0, int id = 0);
    void setButtonImagesToIds(const QList<int> &idList = {0, 1, 2, 3, 4, 5, 6, 7, 8});
signals:
    /**
     * @brief Emited when a party member is changed
     * @param partySlot - the Slot that was changed [ 0 - 2 ]
     * @param id - the id of the new Character in the slot
     */
    void partyChanged(int partySlot, int id);
    void loadCharacterInSlot(int charSlot);

    //Forwarded from charEditor
    void characterIdChanged(qint8);
    void characterLevelChanged(qint8);
    void characterStrChanged(quint8);
    void characterVitChanged(quint8);
    void characterMagChanged(quint8);
    void characterSpiChanged(quint8);
    void characterDexChanged(quint8);
    void characterLckChanged(quint8);
    void characterStrBonusChanged(quint8);
    void characterVitBonusChanged(quint8);
    void characterMagBonusChanged(quint8);
    void characterSpiBonusChanged(quint8);
    void characterDexBonusChanged(quint8);
    void characterLckBonusChanged(quint8);
    void characterLimitLevelChanged(qint8);
    void characterLimitBarChanged(quint8);
    void characterNameChanged(QString);
    void characterWeaponChanged(quint8);
    void characterArmorChanged(quint8);
    void characterAccessoryChanged(quint8);
    void characterCurHpChanged(quint16);
    void characterMaxHpChanged(quint16);
    void characterCurMpChanged(quint16);
    void characterMaxMpChanged(quint16);
    void characterKillsChanged(quint16);
    void characterRowChanged(quint8);
    void characterLevelProgressChanged(quint8);
    void characterSadnessfuryChanged(quint8);
    void characterLimitsChanged(quint16);
    void characterTimesused1Changed(quint16);
    void characterTimesused2Changed(quint16);
    void characterTimesused3Changed(quint16);
    void characterBaseHpChanged(quint16);
    void characterBaseMpChanged(quint16);
    void characterExpChanged(quint32);
    void characterMslotChanged(int);
    void characterMateriaChanged(materia);
    void characterExpNextChanged(quint32);

protected:
    void resizeEvent(QResizeEvent *ev);
    void changeEvent(QEvent *e);

private:
    void updateText();
    void boostCharacter();
    void setCurrentButton(int currentButton);
    QGroupBox * m_groupParty;
    QGroupBox * m_groupCharacters;
    QList<QComboBox *> m_comboParty;
    QList<QPushButton*> m_btnChars;
    QPushButton * m_btnBoostCharacter = nullptr;
    CharEditor * m_charEditor = nullptr;
    QString m_charStyle = QStringLiteral("QWidget{background-color: rgb(%1,%2,%3);}");
};
