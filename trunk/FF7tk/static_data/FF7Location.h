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
    {QT_TRANSLATE_NOOP("Locations","Sector 1 Station"),"1","117","1433","386","78"},
    {QT_TRANSLATE_NOOP("Locations","Sector 1"),"1","118","3568","30777","55"},
    {QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","119","65524","62793","0"},
    {QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","120","64800","1612","16"},
    {QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","121","30","40","7"},
    {QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","122","65331","235","90"},
    {QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","123","65362","1692","35"},
    {QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","124","37","1579","36"},
    {QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","125","65444","64360","1"},
    {QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","133","1270","60233","11"},
    {QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","134","61569","21109","19"},
    {QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","135","61423","18369","189"},
    {QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","137","65114","1111","6"},
    {QT_TRANSLATE_NOOP("Locations","Last Train From Midgar"),"1","138","6","42","20"},
    {QT_TRANSLATE_NOOP("Locations","Last Train From Midgar"),"1","139","2","537","28"},
    {QT_TRANSLATE_NOOP("Locations","Sector 7 Station"),"1","146","63066","2703","16"},
    {QT_TRANSLATE_NOOP("Locations","Sector 7 Slums"),"1","156","65185","636","231"},
    {QT_TRANSLATE_NOOP("Locations","Sector 7 Slums"),"1","151","1428","65374","109"},
    {QT_TRANSLATE_NOOP("Locations","7th Heaven"),"1","154","67","6","26"},
    {QT_TRANSLATE_NOOP("Locations","AVALANCHE Hideout"),"1","155","65346","65371","41"},
    {QT_TRANSLATE_NOOP("Locations","Sector 7 Item Store"),"1","152","21","65492","24"},
    {QT_TRANSLATE_NOOP("Locations","Sector 7 Weapon Shop"),"1","148","14","65532","5"},
    {QT_TRANSLATE_NOOP("Locations","Beginner's Hall"),"1","149","220","65371","71"},
    {QT_TRANSLATE_NOOP("Locations","Sector 7 Slums"),"1","150","65531","65352","12"},
    {QT_TRANSLATE_NOOP("Locations","Johnny's Home"),"1","153","65521","91","55"},
    {QT_TRANSLATE_NOOP("Locations","Inside Train "),"1","140","12","579","29"},
    {QT_TRANSLATE_NOOP("Locations","Inside Train "),"1","142","82","376","27"},
    {QT_TRANSLATE_NOOP("Locations","Inside Train "),"1","141","65476","478","31"},
    {QT_TRANSLATE_NOOP("Locations","Winding Tunnel"),"1","161","25","89","145"},
    {QT_TRANSLATE_NOOP("Locations","Winding Tunnel"),"1","162","1","555","11"},
    {QT_TRANSLATE_NOOP("Locations","4th Street Plate Int."),"1","164","65532","65123","4"},
    {QT_TRANSLATE_NOOP("Locations","Lower Sector 4 Plate"),"1","167","17","1","7"},
    {QT_TRANSLATE_NOOP("Locations","Lower Sector 4 Plate "),"1","168","65427","65419","65"},
    {QT_TRANSLATE_NOOP("Locations","4th Street Plate Int."),"1","165","0","65490","9"},
    {QT_TRANSLATE_NOOP("Locations","4th Street Plate Int."),"1","166","65382","575","21"},
    {QT_TRANSLATE_NOOP("Locations","Lower Sector 4 Plate"),"1","169","65422","468","11"},
    {QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","129","581","2137","157"},
    {QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","130","65360","1527","19"},
    {QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","131","34","1617","36"},
    {QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","132","65447","64575","0"},
    {QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","128","64035","2546","20"},
    {QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","126","65532","63661","7"},
    {QT_TRANSLATE_NOOP("Locations","church in the slums"),"1","183","65463","400","8"},
    {QT_TRANSLATE_NOOP("Locations","Inside the Church"),"1","184","65162","1130","129"},
    {QT_TRANSLATE_NOOP("Locations","Church Roof"),"1","186","65526","410","33"},
    {QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","171","65535","64904","12"},
    {QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","173","989","65501","4"},
    {QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","172","159","65402","59"},
    {QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","177","64951","166","101"},
    {QT_TRANSLATE_NOOP("Locations","Earthen Pipe"),"1","176","39","65259","57"},
    {QT_TRANSLATE_NOOP("Locations","Materia store"),"1","180","7","65449","21"},
    {QT_TRANSLATE_NOOP("Locations","Item Store"),"1","179","102","65527","28"},
    {QT_TRANSLATE_NOOP("Locations","House 1f."),"1","174","65510","24","32"},
    {QT_TRANSLATE_NOOP("Locations","House 2f."),"1","175","65486","76","7"},
    {QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","178","65514","32","10"},
    {QT_TRANSLATE_NOOP("Locations","Aerith's House"),"1","187","171","65329","138"},
    {QT_TRANSLATE_NOOP("Locations","Aerith's House"),"1","188","65453","65465","41"},
    {QT_TRANSLATE_NOOP("Locations","Aerith's House"),"1","190","63","305","25"},
    {QT_TRANSLATE_NOOP("Locations","Church"),"1","181","65527","65364","52"},
    {QT_TRANSLATE_NOOP("Locations","Sector 6"),"1","191","64282","65239","41"},
    {QT_TRANSLATE_NOOP("Locations","Sector 6 park"),"1","192","65272","65481","194"},
    {QT_TRANSLATE_NOOP("Locations","Sector 6"),"1","194","46","220","16"},
    {QT_TRANSLATE_NOOP("Locations","Wall Market"),"1","195","462","1080","58"},
    {QT_TRANSLATE_NOOP("Locations","Inn"),"1","199","65333","0","27"},
    {QT_TRANSLATE_NOOP("Locations","Item Store"),"1","198","65515","16","6"},
    {QT_TRANSLATE_NOOP("Locations","Pharmacy"),"1","203","30","65445","5"},
    {QT_TRANSLATE_NOOP("Locations","Diner"),"1","202","88","65388","23"},
    {QT_TRANSLATE_NOOP("Locations","Boutique"),"1","201","130","65511","41"},
    {QT_TRANSLATE_NOOP("Locations","Materia Store"),"1","200","174","65428","9"},
    {QT_TRANSLATE_NOOP("Locations","Wall Market"),"1","205","65412","63098","93"},
    {QT_TRANSLATE_NOOP("Locations","Men's Hall"),"1","197","65519","220","139"},
    {QT_TRANSLATE_NOOP("Locations","Bar"),"1","204","66","130","43"},
    {QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","196","71","65446","29"},
    {QT_TRANSLATE_NOOP("Locations","Wall Market"),"1","222","65467","544","4"},
    {QT_TRANSLATE_NOOP("Locations","Corneo Hall"),"1","206","53","341","35"},
    {QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","214","12","65429","24"},
    {QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","218","1","65499","11"},
    {QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","216","64","114","47"},
    {QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","220","65522","65255","36"},
    {QT_TRANSLATE_NOOP("Locations","Corneo Hall,1f."),"1","207","65363","65474","27"},
    {QT_TRANSLATE_NOOP("Locations","Torture Room"),"1","209","556","32","15"},
    {QT_TRANSLATE_NOOP("Locations","Corneo Hall,2f."),"1","210","65528","65272","84"},
    {QT_TRANSLATE_NOOP("Locations","Corneo Hall,2f."),"1","208","65449","65153","76"},
    {QT_TRANSLATE_NOOP("Locations","Corneo Hall,2f."),"1","211","145","308","43"},
    {QT_TRANSLATE_NOOP("Locations","Sewer"),"1","212","304","116","14"},
    {QT_TRANSLATE_NOOP("Locations","Sewer"),"1","213","66","65328","9"},
    {QT_TRANSLATE_NOOP("Locations","Train Graveyard"),"1","144","1981","62327","71"},
    {QT_TRANSLATE_NOOP("Locations","Train Graveyard"),"1","145","1403","1151","197"},
    {QT_TRANSLATE_NOOP("Locations","Plate Support"),"1","158","65332","64576","192"},
    {QT_TRANSLATE_NOOP("Locations","Plate Support"),"1","159","193","64530","100"},
    {QT_TRANSLATE_NOOP("Locations","Plate Support"),"1","160","262","65272","30"},
    {QT_TRANSLATE_NOOP("Locations","Sector 6 park"),"1","193","65485","65206","18"},
    {QT_TRANSLATE_NOOP("Locations","Plate Section"),"1","223","65527","909","111"},
    {QT_TRANSLATE_NOOP("Locations","Plate Section"),"1","224","50","1290","70"},
    {QT_TRANSLATE_NOOP("Locations","Sector 0"),"1","225","61105","52237","16"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg."),"1","227","512","63074","105"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg."),"1","228","4","64828","4"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. Stairs"),"1","229","65444","152","158"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. Stairs"),"1","230","65495","75","150"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. Stairs"),"1","231","65475","62","25"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 59f."),"1","238","65121","64992","85"},
    {QT_TRANSLATE_NOOP("Locations","Outside Elevator"),"1","233","46","65515","18"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 60f."),"1","240","65404","64601","12"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 60f."),"1","239","65397","64843","266"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 61f."),"1","241","733","65077","296"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 62f."),"1","242","611","65149","231"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 62f."),"1","243","120","65110","74"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 62f."),"1","244","65413","607","33"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 63f."),"1","245","905","64842","377"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 64f."),"1","247","64386","65253","245"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 65f."),"1","248","581","65074","131"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 65f."),"1","249","31","65168","86"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg.66f."),"1","250","567","65187","67"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg.66f."),"1","252","86","123","18"},
    /**********************************Below The List Is UnFinished   ***********************************/
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg 67F."),"1","256","65426","797","283"},
    {QT_TRANSLATE_NOOP("Locations","Shinra Bldg 69F."),"1","264","150","65102","226"},
    {QT_TRANSLATE_NOOP("Locations","Midgar Sector 8"),"1","732","265","65332","24"},
    {QT_TRANSLATE_NOOP("Locations","Midgar Sector 8"),"1","739","61439","18394","34"},
    {QT_TRANSLATE_NOOP("Locations","Sector 8, Underground"),"1","733","65264","1614","116"},
    {QT_TRANSLATE_NOOP("Locations","Train Graveyard"),"1","144","1981","62327","71"},
    {QT_TRANSLATE_NOOP("Locations","Tunnel"),"1","736","65453","65237","215"},
    {QT_TRANSLATE_NOOP("Locations","Kalm Inn"),"1","332","267","65429","15"},
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
    {QT_TRANSLATE_NOOP("Locations","Arena Lobby"),"1","500","6","62146","4"}
};
#endif //FF7LOCATION_H
