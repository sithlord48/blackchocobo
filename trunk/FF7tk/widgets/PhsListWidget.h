/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
//                                                                          //
//    This file is part of FF7tk                                            //
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
#ifndef PHSLISTWIDGET_H
#define PHSLISTWIDGET_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif
#include "DoubleCheckBox.h"

class PhsListWidget : public QWidget
{
    Q_OBJECT
public:
    enum BoxType {BOX_ALLOWED=1,BOX_VISIBLE=2};
    explicit PhsListWidget(QWidget *parent = 0);

signals:
    void box1_toggled(int row,bool checked);
    void box2_toggled(int row,bool checked);
public slots:
     void setChecked(int row,int box,bool checked);
private slots:
    void cb_cloud_one_toggled(bool checked);
    void cb_cloud_two_toggled(bool checked);
    void cb_barret_one_toggled(bool checked);
    void cb_barret_two_toggled(bool checked);
    void cb_tifa_one_toggled(bool checked);
    void cb_tifa_two_toggled(bool checked);
    void cb_aerith_one_toggled(bool checked);
    void cb_aerith_two_toggled(bool checked);
    void cb_red_one_toggled(bool checked);
    void cb_red_two_toggled(bool checked);
    void cb_yuffie_one_toggled(bool checked);
    void cb_yuffie_two_toggled(bool checked);
    void cb_cait_one_toggled(bool checked);
    void cb_cait_two_toggled(bool checked);
    void cb_vincent_one_toggled(bool checked);
    void cb_vincent_two_toggled(bool checked);
    void cb_cid_one_toggled(bool checked);
    void cb_cid_two_toggled(bool checked);

private:
    DoubleCheckBox *cb_cloud;
    DoubleCheckBox *cb_barret;
    DoubleCheckBox *cb_tifa;
    DoubleCheckBox *cb_aerith;
    DoubleCheckBox *cb_red;
    DoubleCheckBox *cb_yuffie;
    DoubleCheckBox *cb_cait;
    DoubleCheckBox *cb_vincent;
    DoubleCheckBox *cb_cid;
    QLabel *lbl_phs;
    void init_display();
    void connectAll();
    void disconnectAll();
};

#endif // PHSMENULIST_H
