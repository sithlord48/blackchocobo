//  SPDX-FileCopyrightText: 2022 - 2024 Chris Rizzitello <sithlord48@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

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
    /**
     * @brief boostCharacter - Give the current chracter a boost to maximum level
     */
    void boostCharacter();

    CharEditor* characterEditor() { return m_charEditor; }
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

    /**
     * @brief requestCharacterSlotLoad This signal is emitted when the user clicks on a character's icon
     * The Character Editor will expect the host program to call to setChracter with the new chracter data for new character slot
     * @param charSlot The character slot that is requested
     */
    void requestCharacterSlotLoad(int charSlot);

protected:
    void resizeEvent(QResizeEvent *ev);
    void changeEvent(QEvent *e);

private:
    void updateText();
    void setCurrentButton(int currentButton);
    QGroupBox * m_groupParty;
    QGroupBox * m_groupCharacters;
    QList<QComboBox *> m_comboParty;
    QList<QPushButton*> m_btnChars;
    QPushButton * m_btnBoostCharacter = nullptr;
    CharEditor * m_charEditor = nullptr;
    QString m_charStyle = QStringLiteral("QWidget{background-color: rgb(%1,%2,%3);}");
};
