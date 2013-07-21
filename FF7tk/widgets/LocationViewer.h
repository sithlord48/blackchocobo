/****************************************************************************/
//    copyright 2013  Chris Rizzitello <sithlord48@gmail.com>               //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#ifndef LOCATIONVIEWER_H
#define LOCATIONVIEWER_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #include <QtWidgets>
#else
    #include <QtGui>
#endif
// Include FF7tk Items.
#include "../static_data/FF7Location.h"
class LocationViewer : public QWidget
{
    Q_OBJECT
public:
    explicit LocationViewer(QWidget *parent = 0);

signals:
    void locationChanged(QString);
    void xChanged(int x);
    void yChanged(int y);
    void tChanged(int t);
    void dChanged(int d);
    void mapIdChanged(int mapId);
    void locIdChanged(int locId);
    void locationStringChanged(QString);

public slots:
    void setSelected(QString);
    void setRegion(QString region);
    void setTranslationBaseFile(QString);
    void setX(int x);
    void setY(int y);
    void setT(int t);
    void setD(int d);
    void setMapId(int mapId);
    void setLocationId(int locId);
    void setLocationString(QString);
    void setHorizontalHeaderStyle(QString styleSheet);

private slots:
    void itemChanged(int currentRow,int currentColumn,int prevRow, int prevColumn);
    void sbMapIdChanged(int mapId);
    void sbLocIdChanged(int locId);
    void sbXChanged(int x);
    void sbYChanged(int y);
    void sbTChanged(int t);
    void sbDChanged(int d);
    void lineLocationNameChanged(QString);
    void setLocation(int mapId,int locId);
    void filterLocations(QString filter);
    void actionRegExpSearchToggled(bool checked);
    void actionCaseSensitiveToggled(bool checked);
    void btnSearchOptionsClicked(void);
protected:
    void resizeEvent(QResizeEvent *ev);
private:
    void init_display(void);
    void init_connections(void);
    void init_disconnect(void);
    QString translate(QString text);
    QTableWidget *locationTable;
    QLineEdit *lineTableFilter;
    QAction *actionRegExpSearch;
    QAction *actionCaseSensitive;
    QToolButton *btnSearchOptions;
    FF7Location *Locations;
    QLabel * lblLocationPreview;
    QLineEdit *lineLocationName;
    QSpinBox *sbMapID;
    QSpinBox *sbLocID;
    QSpinBox *sbX;
    QSpinBox *sbY;
    QSpinBox *sbT;
    QSpinBox *sbD;
    QString region;
    QString transBasePath;
    bool regExpSearch;
    bool caseSensitive;
};

#endif // LOCATIONVIEWER_H
