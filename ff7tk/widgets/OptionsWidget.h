/****************************************************************************/
//    copyright 2013 - 2019 Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk.                                           //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QtWidgets>
#include "DialogPreview.h"

/** \class OptionsWidget
 *  \brief A Single widget to allow you to set all the options for the game
 *   will save emit a signal when any option changes.
 **/
class OptionsWidget : public QScrollArea
{
    Q_OBJECT
protected:
    void resizeEvent(QResizeEvent *);
    void changeEvent(QEvent *e);
public:
    explicit OptionsWidget(QWidget *parent = nullptr);
    void setInput(int controlAction, int newButton);/**< \brief change action  to a PSXBUTTON \param controlAction Action to change See::FF7Save::CONTROLACTION\param newButton Button must be valid FF7Save::PSXBUTTON */
public slots:
    void setSliderStyle(QString styleSheet);/**< \brief set style for the sliders on this widget \param styleSheet valid styleSheet for QSlider */
    void setScrollAreaStyleSheet(QString styleSheet); /**< \brief set style for the center widget \param styleSheet valid styleSheet for QWidget */
    void setDialogColors(QColor ul, QColor ur, QColor ll, QColor lr); /**< \brief set colors for dialog/menu background preview \param ul Upper Left Color \param ur Upper Right Color \param ll Lower Left Color \param lr Lower Right Color */
    void setAtbMode(int mode); /**< \brief Set Atb Mode \param mode must be valid FF7Save::ATBMODE */
    void setSoundMode(int mode); /**< \brief Set Sound Mode \param mode must be valid FF7Save::SOUNDMODE */
    void setMagicOrder(int order); /**< \brief Set Magic Order \param order  must be valid FF7Save::MAGICORDER */
    void setCursor(int mode); /**< \brief Set Cursor Mode \param mode must be valid FF7Save::CURSORMODE */
    void setCamera(int mode); /**< \brief Set Camera Mode \param mode must be valid FF7Save::CAMERAMODE */
    void setControllerMode(int mode); /**< \brief Set Controller Mode \param mode must be valid FF7Save::CONTROLMODE */
    void setBattleTargets(bool shown); /**< \brief Set Battle Targets Visible \param shown are Target labels shown durring battle */
    void setBattleHelp(bool shown); /**< \brief Set Battle Help Visible \param shown is Help shown durring battle */
    void setFieldHelp(bool shown);  /**< \brief Set Field Help Visible \param shown is Field shown durring battle */
    void setBattleSpeed(int speed); /**< \brief Set Battle Speed \param speed speed for Battles */
    void setBattleMessageSpeed(int speed); /**< \brief Set Battle Message Speed \param speed speed for Battle Messages */
    void setFieldMessageSpeed(int speed); /**< \brief Set Field Message Speed \param speed speed for Field Messages */
    void setControllerMappingVisible(bool visible); /**< \brief Set if the controller mapping area is visible \param visible mapping shown  */
signals:
    void dialogColorULChanged(QColor color); /**< \brief Emit Signal: Upper Left Color Has Changed */
    void dialogColorURChanged(QColor color); /**< \brief Emit Signal: Upper Right Color Has Changed */
    void dialogColorLLChanged(QColor color); /**< \brief Emit Signal: Lower Left Color Has Changed */
    void dialogColorLRChanged(QColor color); /**< \brief Emit Signal: Lower Right Color Has Changed */
    void atbChanged(int mode); /**< \brief Emit Signal: ATB Mode Changed */
    void soundChanged(int mode); /**< \brief Emit Signal: Sound Mode Changed */
    void magicOrderChanged(int order); /**< \brief Emit Signal: Magic Order Changed */
    void cursorChanged(int mode); /**< \brief Emit Signal: Cursor Mode Changed */
    void cameraChanged(int mode); /**< \brief Emit Signal: Camera Mode Changed */
    void controllerModeChanged(int mode); /**< \brief Emit Signal: Controller Mode Changed */
    void battleTargetsChanged(bool shown); /**< \brief Emit Signal: Battle Target Mode Changed */
    void battleHelpChanged(bool shown); /**< \brief Emit Signal: Battle Help Mode Changed */
    void fieldHelpChanged(bool shown); /**< \brief Emit Signal: Field Help Mode Changed */
    void battleSpeedChanged(int speed); /**< \brief Emit Signal: Battle Speed Changed */
    void battleMessageSpeedChanged(int speed); /**< \brief Emit Signal: Battle Message Speed Changed */
    void fieldMessageSpeedChanged(int speed); /**< \brief Emit Signal: Field Message Speed Changed */
    void inputChanged(int controlAction, int newButton);/**< \brief Emit Signal: Mapping for FF7Save::CONTROLACTION has Changed to new FF7Save::PSXBUTTON */

private:
    void updateText();
    QGridLayout *makeControllerLayout();
    DialogPreview *dialogPreview = nullptr;
    QGroupBox *dialogBox = nullptr;
    QWidget *centerWidget = nullptr;
    QComboBox *comboAtb = nullptr;
    QComboBox *comboSound = nullptr;
    QComboBox *comboMagicOrder = nullptr;
    QComboBox *comboCursor = nullptr;
    QComboBox *comboCamera = nullptr;
    QComboBox *comboControllerMode = nullptr;
    QCheckBox *cbBattleTargets = nullptr;
    QCheckBox *cbBattleHelp = nullptr;
    QCheckBox *cbFieldHelp = nullptr;
    QSlider *slideBattleSpeed = nullptr;
    QSlider *slideBattleMessageSpeed = nullptr;
    QSlider *slideFieldMessageSpeed = nullptr;
    QGroupBox *controllerMappingBox = nullptr;
    QLabel *labelAtb = nullptr;
    QLabel *labelSound = nullptr;
    QLabel *labelMagic = nullptr;
    QLabel *labelCursor = nullptr;
    QLabel *labelCamera = nullptr;
    QLabel *labelControllerMode = nullptr;
    QLabel *lblBattleSpeedMax = nullptr;
    QLabel *lblBattleSpeedMin = nullptr;
    QLabel *lblBattleMessageSpeedMax = nullptr;
    QLabel *lblBattleMessageSpeedMin = nullptr;
    QLabel *lblFieldMessageSpeedMax = nullptr;
    QLabel *lblFieldMessageSpeedMin = nullptr;
    QLabel *lblBattleSpeed = nullptr;
    QLabel *lblBattleMessageSpeed = nullptr;
    QLabel *lblFieldMessageSpeed = nullptr;
    QList<QLabel *> lblInputs;

    inline static const QStringList _inputNames {
        QT_TR_NOOP("Up")
        , QT_TR_NOOP("Right")
        , QT_TR_NOOP("Down")
        , QT_TR_NOOP("Left")
        , QT_TR_NOOP("Menu")
        , QT_TR_NOOP("Ok")
        , QT_TR_NOOP("Cancel")
        , QT_TR_NOOP("Switch")
        , QT_TR_NOOP("Camera")
        , QT_TR_NOOP("Target")
        , QT_TR_NOOP("PgUp")
        , QT_TR_NOOP("PgDn")
        , QT_TR_NOOP("Help")
        , QT_TR_NOOP("Pause")
        , QT_TR_NOOP("9")
        , QT_TR_NOOP("10")
    };

    inline static const QStringList _actionNames {
        QT_TR_NOOP("Camera")
        , QT_TR_NOOP("Target")
        , QT_TR_NOOP("PgUp")
        , QT_TR_NOOP("PgDn")
        , QT_TR_NOOP("Menu")
        , QT_TR_NOOP("Ok")
        , QT_TR_NOOP("Cancel")
        , QT_TR_NOOP("Switch")
        , QT_TR_NOOP("Help")
        , QT_TR_NOOP("9")
        , QT_TR_NOOP("10")
        , QT_TR_NOOP("Pause")
        , QT_TR_NOOP("Up")
        , QT_TR_NOOP("Right")
        , QT_TR_NOOP("Down")
        , QT_TR_NOOP("Left")
    };

    inline static const QStringList _atbList {
        QT_TR_NOOP("Active")
        , QT_TR_NOOP("Recommended")
        , QT_TR_NOOP("Wait")
    };

    inline static const QStringList _soundList {
        QT_TR_NOOP("Mono")
        , QT_TR_NOOP("Stereo")
    };

    inline static const QStringList _magicOrderList {
        QT_TR_NOOP("Restore,Attack,Indirect")
        , QT_TR_NOOP("Restore,Indirect,Attack")
        , QT_TR_NOOP("Attack,Indirect,Restore")
        , QT_TR_NOOP("Attack,Restore,Indirect")
        , QT_TR_NOOP("Indirect,Restore,Attack")
        , QT_TR_NOOP("Indirect,Attack,Restore")
    };

    inline static const QStringList _cursorCameraList {
        QT_TR_NOOP("Initial")
        , QT_TR_NOOP("Memory")
    };

    inline static const QStringList _controllerModeList {
        QT_TR_NOOP("Normal")
        , QT_TR_NOOP("Custom")
    };

    inline static const QString _fast =  QT_TR_NOOP("Fast");
    inline static const QString _slow =  QT_TR_NOOP("Slow");

};
#endif // OPTIONSWIDGET_H
