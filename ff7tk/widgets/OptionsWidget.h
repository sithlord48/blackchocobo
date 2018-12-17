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
 *	\brief A Single widget to allow you to set all the options for the game
 *   will save emit a signal when any option changes.
 **/
class OptionsWidget : public QScrollArea
{
	Q_OBJECT
protected:
	void resizeEvent(QResizeEvent *);
public:
    explicit OptionsWidget(QWidget *parent = nullptr);
    void setInput(int controlAction, int newButton);/**< \brief change action  to a PSXBUTTON \param controlAction Action to change See::FF7Save::CONTROLACTION\param newButton Button must be valid FF7Save::PSXBUTTON */
public slots:
	void setSliderStyle(QString styleSheet);/**< \brief set style for the sliders on this widget \param styleSheet valid styleSheet for QSlider */
	void setScrollAreaStyleSheet(QString styleSheet); /**< \brief set style for the center widget \param styleSheet valid styleSheet for QWidget */
	void setDialogColors(QColor ul,QColor ur,QColor ll,QColor lr); /**< \brief set colors for dialog/menu background preview \param ul Upper Left Color \param ur Upper Right Color \param ll Lower Left Color \param lr Lower Right Color */
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

    inline static const QStringList _inputNames {
        QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Up"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Right"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Down"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Left"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Menu"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Ok"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Cancel"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Switch"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Camera"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Target"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("PgUp"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("PgDn"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Help"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Pause"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("9"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("10"))
    };

    inline static const QStringList _actionNames {
        QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Camera"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Target"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("PgUp"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("PgDn"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Menu"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Ok"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Cancel"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Switch"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Help"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("9"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("10"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Pause"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Up"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Right"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Down"))
        , QT_TRANSLATE_NOOP(QStringLiteral("FF7Input"), QStringLiteral("Left"))
    };
};
#endif // OPTIONSWIDGET_H
