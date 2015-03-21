/****************************************************************************/
//    copyright 2013 Chris Rizzitello <sithlord48@gmail.com>           //
//                                                                          //
//    This file is part of FF7tk.                                   //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	#include <QtWidgets>
#else
	#include <QtGui>
#endif
#include "DialogPreview.h"
/*~~~~~~~~~Icons~~~~~~~~~~~~~~~*/
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
	explicit OptionsWidget(QWidget *parent = 0);
public slots:
	void setSliderStyle(QString styleSheet);/**< \brief set style for the sliders on this widget \param style valid styleSheet for QSlider */
	void setScrollAreaStyleSheet(QString styleSheet); /**< \brief set style for the center widget \param style valid styleSheet for QWidget */
	void setDialogColors(QColor ul,QColor ur,QColor ll,QColor lr); /**< \brief set colors for dialog/menu background preview \param ul Upper Left Color \param ur Upper Right Color \param ll Lower Left Color \param lr Lower Right Color */
	void setAtb(int mode); /**< \brief Set Atb Mode \param mode Button must be valid FF7Save::ATBMODE */
	void setSoundMode(int mode); /**< \brief Set Sound Mode \param mode Button must be valid FF7Save::SOUNDMODE */
	void setMagicOrder(int order); /**< \brief Set Magic Order \param mode Button must be valid FF7Save::MAGICORDER */
	void setCursor(int mode); /**< \brief Set Cursor Mode \param mode Button must be valid FF7Save::CURSORMODE */
	void setCamera(int mode); /**< \brief Set Camera Mode \param mode Button must be valid FF7Save::CAMERAMODE */
	void setControllerMode(int mode); /**< \brief Set Controller Mode \param mode Button must be valid FF7Save::CONTROLMODE */
	void setBattleTargets(bool shown); /**< \brief Set Battle Targets Visible \param shown are Target labels shown durring battle */
	void setBattleHelp(bool shown); /**< \brief Set Battle Help Visible \param shown is Help shown durring battle */
	void setFieldHelp(bool shown);  /**< \brief Set Field Help Visible \param shown is Field shown durring battle */
	void setBattleSpeed(int speed); /**< \brief Set Battle Speed \param speed speed for Battles */
	void setBattleMessageSpeed(int speed); /**< \brief Set Battle Message Speed \param speed speed for Battle Messages */
	void setFieldMessageSpeed(int speed); /**< \brief Set Field Message Speed \param speed speed for Field Messages */
	void setBtnUp(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnRight(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnDown(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnLeft(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnMenu(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnOk(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnCancel(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnSwitch(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnCamera(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnTarget(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnPgUp(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnPgDn(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnHelp(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtnPause(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtn9(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setBtn10(int btnNumber); /**< \brief Set Action Up to a PSXBUTTON \param btnNumber Button must be valid FF7Save::PSXBUTTON */
	void setControllerMappingVisible(bool visible); /**< \brief Set if the controller mapping area is visible \param visible mapping shown  */
signals:
	void dialogColorULChanged(QColor); /**< \brief Emit Signal: Upper Left Color Has Changed */
	void dialogColorURChanged(QColor); /**< \brief Emit Signal: Upper Right Color Has Changed */
	void dialogColorLLChanged(QColor); /**< \brief Emit Signal: Lower Left Color Has Changed */
	void dialogColorLRChanged(QColor); /**< \brief Emit Signal: Lower Right Color Has Changed */
	void AtbChanged(int); /**< \brief Emit Signal: ATB Mode Changed */
	void SoundChanged(int); /**< \brief Emit Signal: Sound Mode Changed */
	void MagicOrderChanged(int); /**< \brief Emit Signal: Magic Order Changed */
	void CursorChanged(int); /**< \brief Emit Signal: Cursor Mode Changed */
	void CameraChanged(int); /**< \brief Emit Signal: Camera Mode Changed */
	void ControllerModeChanged(int); /**< \brief Emit Signal: Controller Mode Changed */
	void BattleTargetsChanged(bool); /**< \brief Emit Signal: Battle Target Mode Changed */
	void BattleHelpChanged(bool); /**< \brief Emit Signal: Battle Help Mode Changed */
	void FieldHelpChanged(bool); /**< \brief Emit Signal: Field Help Mode Changed */
	void BattleSpeedChanged(int); /**< \brief Emit Signal: Battle Speed Changed */
	void BattleMessageSpeedChanged(int); /**< \brief Emit Signal: Battle Message Speed Changed */
	void FieldMessageSpeedChanged(int); /**< \brief Emit Signal: Field Message Speed Changed */
	void BtnUpChanged(int); /**< \brief Emit Signal: Button for Up has Changed see FF7Save::PSXBUTTON for values */
	void BtnDownChanged(int); /**< \brief Emit Signal: Button for Down has Changed see FF7Save::PSXBUTTON for values */
	void BtnLeftChanged(int); /**< \brief Emit Signal: Button for Left has Changed see FF7Save::PSXBUTTON for values */
	void BtnRightChanged(int); /**< \brief Emit Signal: Button for Right has Changed see FF7Save::PSXBUTTON for values */
	void BtnMenuChanged(int); /**< \brief Emit Signal: Button for Menu has Changed see FF7Save::PSXBUTTON for values */
	void BtnOkChanged(int); /**< \brief Emit Signal: Button for Ok has Changed see FF7Save::PSXBUTTON for values */
	void BtnCancelChanged(int); /**< \brief Emit Signal: Button for Cancel has Changed see FF7Save::PSXBUTTON for values */
	void BtnSwitchChanged(int); /**< \brief Emit Signal: Button for Switch has Changed see FF7Save::PSXBUTTON for values */
	void BtnCameraChanged(int); /**< \brief Emit Signal: Button for Camera has Changed see FF7Save::PSXBUTTON for values */
	void BtnTargetChanged(int); /**< \brief Emit Signal: Button for Target has Changed see FF7Save::PSXBUTTON for values */
	void BtnPgUpChanged(int); /**< \brief Emit Signal: Button for Up Page Up Changed see FF7Save::PSXBUTTON for values */
	void BtnPgDnChanged(int); /**< \brief Emit Signal: Button for Up Page Down Changed see FF7Save::PSXBUTTON for values */
	void BtnHelpChanged(int); /**< \brief Emit Signal: Button for Up Help Changed see FF7Save::PSXBUTTON for values */
	void BtnPauseChanged(int); /**< \brief Emit Signal: Button for Pause has Changed see FF7Save::PSXBUTTON for values */
	void Btn9Changed(int); /**< \brief Emit Signal: Button '09' has Changed see FF7Save::PSXBUTTON for values */
	void Btn10Changed(int); /**< \brief Emit Signal: Button '10' has Changed see FF7Save::PSXBUTTON for values */

private slots:
	void ulColorChange(QColor);
	void urColorChange(QColor);
	void llColorChange(QColor);
	void lrColorChange(QColor);
	void atbChanged(int);
	void soundChanged(int);
	void magicOrderChanged(int);
	void cursorChanged(int);
	void cameraChanged(int);
	void controllerModeChanged(int);
	void battleTargetsChanged(bool);
	void battleHelpChanged(bool);
	void fieldHelpChanged(bool);
	void battleSpeedChanged(int);
	void battleMessageSpeedChanged(int);
	void fieldMessageSpeedChanged(int);
	void btnUpChanged(int);
	void btnRightChanged(int);
	void btnDownChanged(int);
	void btnLeftChanged(int);
	void btnMenuChanged(int);
	void btnOkChanged(int);
	void btnCancelChanged(int);
	void btnSwitchChanged(int);
	void btnCameraChanged(int);
	void btnTargetChanged(int);
	void btnPgUpChanged(int);
	void btnPgDnChanged(int);
	void btnHelpChanged(int);
	void btnPauseChanged(int);
	void btn9Changed(int);
	void btn10Changed(int);

private:
	void init_Display();
	void init_Connections();
	DialogPreview* dialogPreview;
	QGroupBox *dialogBox;
	QVBoxLayout *centerLayout;
	QWidget *centerWidget;
	QComboBox * comboAtb;
	QComboBox *comboSound;
	QComboBox *comboMagicOrder;
	QComboBox *comboCursor;
	QComboBox *comboCamera;
	QComboBox *comboControllerMode;
	QCheckBox * cbBattleTargets;
	QCheckBox * cbBattleHelp;
	QCheckBox * cbFieldHelp;
	QSlider* slideBattleSpeed;
	QSlider* slideBattleMessageSpeed;
	QSlider* slideFieldMessageSpeed;
	QComboBox *comboBtnUp;
	QComboBox *comboBtnDown;
	QComboBox *comboBtnLeft;
	QComboBox *comboBtnRight;
	QComboBox *comboBtnMenu;
	QComboBox *comboBtnOk;
	QComboBox *comboBtnCancel;
	QComboBox *comboBtnSwitch;
	QComboBox *comboBtnCamera;
	QComboBox *comboBtnTarget;
	QComboBox *comboBtnPgUp;
	QComboBox *comboBtnPgDn;
	QComboBox *comboBtnHelp;
	QComboBox *comboBtnPause;
	QComboBox *comboBtn9;
	QComboBox *comboBtn10;
	QGroupBox *controllerMappingBox;
};
#endif // OPTIONSWIDGET_H
