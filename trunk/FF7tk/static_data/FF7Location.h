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
#ifndef FF7LOCATION_H
    #define FF7LOCATION_H
#include <QObject> 
struct LOCATION {//Location Table Stuff
    QString location;
    QString map_id;
    QString loc_id;
    QString x;
    QString y;
    QString z;
};

class FF7Location
{
public:
    QString loc_name(int);
    QString map_id(int);
    QString loc_id(int);
    QString x(int);
    QString y(int);
    QString z(int);
    int len(void);
};
static LOCATION Locations[]=
{
    {QT_TRANSLATE_NOOP("Locations","Platform"),"1","116","3655","27432","25"},
    {QT_TRANSLATE_NOOP("Locations","Reactor No.1"),"1","124","37","1579","36"},
    {QT_TRANSLATE_NOOP("Locations","Reactor No. 5"),"1","128","64035","2546","20"},
    {QT_TRANSLATE_NOOP("Locations","Reactor No. 5"),"1","131","34","1617","36"},
    {QT_TRANSLATE_NOOP("Locations","Church in the slums"),"1","183","65463","400","8"},
    {QT_TRANSLATE_NOOP("Locations","Lower Sector 4 Plate"),"1","169","65422","468","11"},
    {QT_TRANSLATE_NOOP("Locations","Sector 5 - Slums"),"1","173","64997","135","78"},
    {QT_TRANSLATE_NOOP("Locations","Sector 7 - Slums"),"1","156","65185","636","231"},
    {QT_TRANSLATE_NOOP("Locations","7th Heaven"),"1","154","67","6","26"},
    {QT_TRANSLATE_NOOP("Locations","AVALANCHE Hideout"),"1","155","65346","65371","41"},
    {QT_TRANSLATE_NOOP("Locations","Midgar Sector 8"),"1","732","265","65332","24"},
    {QT_TRANSLATE_NOOP("Locations","Midgar Sector 8"),"1","739","61439","18394","34"},
    {QT_TRANSLATE_NOOP("Locations","Sector 8, Underground"),"1","733","65264","1614","116"},
    {QT_TRANSLATE_NOOP("Locations","Train Graveyard"),"1","144","1981","62327","71"},
    {QT_TRANSLATE_NOOP("Locations","Tunnel"),"1","736","65453","65237","215"},
    {QT_TRANSLATE_NOOP("Locations","Kalm Inn"),"1","332","267","65429","15"},
    {QT_TRANSLATE_NOOP("Locations","Aerith's House"),"1","187","175","65330","138"},
    {QT_TRANSLATE_NOOP("Locations","Beginner's Hall"),"1","149","220","65371","71"},
    {QT_TRANSLATE_NOOP("Locations","Wall Market"),"1","195","462","1080","58"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg."),"1","227","512","63074","105"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg 64F."),"1","247","64386","65253","245"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg 67F."),"1","256","65426","797","283"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg 69F."),"1","264","150","65102","226"},
    {QT_TRANSLATE_NOOP("Locations","Junon Inn"),"1","376","45","197","21"},
    {QT_TRANSLATE_NOOP("Locations","Junon Office F2"),"1","397","65162","65236","8"},
    {QT_TRANSLATE_NOOP("Locations","Junon Way"),"1","394","2184","64947","24"},
    {QT_TRANSLATE_NOOP("Locations","Junon Airport Path"),"1","386","64902","65203","31"},
    {QT_TRANSLATE_NOOP("Locations","Gaeas Cliff"),"1","699","65424","240","17"},
    {QT_TRANSLATE_NOOP("Locations","Gaeas Cliff"),"1","693","65384","1104","65"},
    {QT_TRANSLATE_NOOP("Locations","Gaeas Cliff Base"),"1","687","165","51","5"},
    {QT_TRANSLATE_NOOP("Locations","Mt. Nibel"),"1","317","667","65035","261"},
    {QT_TRANSLATE_NOOP("Locations","North Crater"),"1","749","65344","16","35"},
    {QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","473","876","1471","74"},
    {QT_TRANSLATE_NOOP("Locations","Fort Condor"),"1","355","1118","391","12"},
    {QT_TRANSLATE_NOOP("Locations","Underwater Reactor"),"1","422","34","426","14"},
    {QT_TRANSLATE_NOOP("Locations","Inside Submarine"),"1","408","65484","433","7"},
    {QT_TRANSLATE_NOOP("Locations","Hallway"),"1","88","65141","34","13"},
    {QT_TRANSLATE_NOOP("Locations","Cosmo Canyon"),"1","529","128","65215","79"},
    {QT_TRANSLATE_NOOP("Locations","Boat"),"1","436","65430","64368","46"},
    {QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","462","63498","65531","220"},
    {QT_TRANSLATE_NOOP("Locations","Ropeway Station"),"1","496","64767","95","26"},
    {QT_TRANSLATE_NOOP("Locations","Forgotten Captial"),"1","633","65402","65401","40"},
    {QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","703","65170","64488","44"},
    {QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","705","94","1168","173"},
    {QT_TRANSLATE_NOOP("Locations","Wutai"),"1","579","64961","1101","34"},
    {QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","646","641","793","243"},
    {QT_TRANSLATE_NOOP("Locations","Chocobo Ranch"),"1","345","65535","64960","61"},
    {QT_TRANSLATE_NOOP("Locations","Highwind"),"1","72","65533","62949","99"},
    {QT_TRANSLATE_NOOP("Locations","Debug Room [en]"),"1","94","0","0","0"},
    {QT_TRANSLATE_NOOP("Locations","Debug Room [ja]"),"1","65","0","0","0"},
    {QT_TRANSLATE_NOOP("Locations","Test Fight"),"2","0","0","0","0"},
    {QT_TRANSLATE_NOOP("Locations","Mideel,Clinic"),"1","720","151","65380","19"},
    {QT_TRANSLATE_NOOP("Locations","Sector 6"),"1","194","12","302","15"},
    {QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","214","12","65429","24"},
    {QT_TRANSLATE_NOOP("Locations","Corneo Hall"),"1","206","53","341","35"},
    {QT_TRANSLATE_NOOP("Locations","Arena Lobby"),"1","500","6","62146","4"}
};
#endif //FF7LOCATION_H
