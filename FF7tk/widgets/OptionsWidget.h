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

class OptionsWidget : public QWidget
{
    Q_OBJECT
protected:
    void resizeEvent(QResizeEvent *);
public:
    explicit OptionsWidget(QWidget *parent = 0);
    void setDialogColors(QColor ul,QColor ur,QColor ll,QColor lr);
    void setAtb(int mode);
    void setSoundMode(int mode);
    void setMagicOrder(int order);
    void setCursor(int mode);
    void setCamera(int mode);
    void setControllerMode(int mode);
    void setBattleTargets(bool shown);
    void setBattleHelp(bool shown);
    void setFieldHelp(bool shown);
    void setBattleSpeed(int speed);
    void setBattleMessageSpeed(int speed);
    void setFieldMessageSpeed(int speed);

    void setBtnUp(int btnNumber);
    void setBtnRight(int btnNumber);
    void setBtnDown(int btnNumber);
    void setBtnLeft(int btnNumber);
    void setBtnMenu(int btnNumber);
    void setBtnOk(int btnNumber);
    void setBtnCancel(int btnNumber);
    void setBtnSwitch(int btnNumber);
    void setBtnCamera(int btnNumber);
    void setBtnTarget(int btnNumber);
    void setBtnPgUp(int btnNumber);
    void setBtnPgDn(int btnNumber);
    void setBtnHelp(int btnNumber);
    void setBtnPause(int btnNumber);
    void setBtn9(int btnNumber);
    void setBtn10(int btnNumber);

    void setControllerMappingVisible(bool visible);


signals:
    void dialogColorULChanged(QColor);
    void dialogColorURChanged(QColor);
    void dialogColorLLChanged(QColor);
    void dialogColorLRChanged(QColor);
    void AtbChanged(int);
    void SoundChanged(int);
    void MagicOrderChanged(int);
    void CursorChanged(int);
    void CameraChanged(int);
    void ControllerModeChanged(int);
    void BattleTargetsChanged(bool);
    void BattleHelpChanged(bool);
    void FieldHelpChanged(bool);
    void BattleSpeedChanged(int);
    void BattleMessageSpeedChanged(int);
    void FieldMessageSpeedChanged(int);
    void BtnUpChanged(int);
    void BtnRightChanged(int);
    void BtnDownChanged(int);
    void BtnLeftChanged(int);
    void BtnMenuChanged(int);
    void BtnOkChanged(int);
    void BtnCancelChanged(int);
    void BtnSwitchChanged(int);
    void BtnCameraChanged(int);
    void BtnTargetChanged(int);
    void BtnPgUpChanged(int);
    void BtnPgDnChanged(int);
    void BtnHelpChanged(int);
    void BtnPauseChanged(int);
    void Btn9Changed(int);
    void Btn10Changed(int);
    
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

   QScrollArea *mainArea;
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
