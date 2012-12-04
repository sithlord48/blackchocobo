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
    QString filename;
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
    QString fileName(int);
    QString fileName(int MapID,int LocID);
    QString locationString(int);
    QString mapID(int);
    QString locationID(int);
    QString x(int);
    QString y(int);
    QString z(int);
    int len(void);
};
static LOCATION Locations[]=
{
    /************************Every Location In The Game With Stock Translation******************/

/*
    {"fship_1",QT_TRANSLATE_NOOP("Locations","Highwind"),"1","66","125","64275","27"},
    {"fship_12",QT_TRANSLATE_NOOP("Locations","deck"),"1","67","0","0","0"},
    {"fship_2",QT_TRANSLATE_NOOP("Locations",""),"1","68","0","0","0"},
    {"fship_22",QT_TRANSLATE_NOOP("Locations",""),"1","69","0","0","0"},
*/
    {"fship_25",QT_TRANSLATE_NOOP("Locations","Highwind"),"1","72","65533","62949","99"},
    {"zz2",QT_TRANSLATE_NOOP("Locations","Weapon seller"),"1","79","65359","65470","30"},
    {"q_1",QT_TRANSLATE_NOOP("Locations","Hallway"),"1","88","65141","34","13"},
    {"blackbg2",QT_TRANSLATE_NOOP("Locations","Debug Room [en]"),"1","94","0","0","0"},
    {"startmap",QT_TRANSLATE_NOOP("Locations","Debug Room [ja]"),"1","65","0","0","0"},

    {"md1stin",QT_TRANSLATE_NOOP("Locations","Platform"),"1","116","3655","27432","25"},
    {"md1_1",QT_TRANSLATE_NOOP("Locations","Sector 1 Station"),"1","117","1433","386","78"},
    {"md1_2",QT_TRANSLATE_NOOP("Locations","Sector 1"),"1","118","3568","30777","55"},
    {"nrthmk",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","119","65524","62793","0"},

    {"nrthmk_1",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","120","64800","1612","16"},
    {"elevtr1",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","121","30","40","7"},
    {"nmkin_2",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","122","65331","235","90"},
    {"nmkin_3",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","123","65362","1692","35"},
    {"nmkin_4",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","124","37","1579","36"},
    {"nmkin_5",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","125","65444","64360","1"},
    {"southmk1",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","126","65532","63661","7"},
    {"smkin_1",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","128","64035","2546","20"},
    {"smkin_2",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","129","581","2137","157"},

    {"smkin_3",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","130","65360","1527","19"},
    {"smkin_4",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","131","34","1617","36"},
    {"smkin_5",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","132","65447","64575","0"},
    {"md8_1",QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","133","1270","60233","11"},
    {"md8_2",QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","134","61569","21109","19"},
    {"md8_3",QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","135","61423","18369","189"},
    {"md8brdg",QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","137","65114","1111","6"},
    {"cargoin",QT_TRANSLATE_NOOP("Locations","Last Train From Midgar"),"1","138","6","42","20"},
    {"tin_1",QT_TRANSLATE_NOOP("Locations","Last Train From Midgar"),"1","139","2","537","28"},

    {"tin_2",QT_TRANSLATE_NOOP("Locations","Inside Train"),"1","140","12","579","29"},
    {"tin_3",QT_TRANSLATE_NOOP("Locations","Inside Train"),"1","141","65476","478","31"},
    {"tin_4",QT_TRANSLATE_NOOP("Locations","Inside Train"),"1","142","82","376","27"},
    {"mds7st1",QT_TRANSLATE_NOOP("Locations","Train Graveyard"),"1","144","1981","62327","71"},
    {"mds7st2",QT_TRANSLATE_NOOP("Locations","Train Graveyard"),"1","145","1403","1151","197"},
    {"mds7st3",QT_TRANSLATE_NOOP("Locations","Sector 7 Station"),"1","146","63066","2703","16"},
    {"mds7_w1",QT_TRANSLATE_NOOP("Locations","Sector 7 Weapon Shop"),"1","148","14","65532","5"},
    {"mds7_w2",QT_TRANSLATE_NOOP("Locations","Beginner's Hall"),"1","149","220","65371","71"},

    {"mds7_w3",QT_TRANSLATE_NOOP("Locations","Sector 7 Slums"),"1","150","65531","65352","12"},
    {"mds7",QT_TRANSLATE_NOOP("Locations","Sector 7 Slums"),"1","151","1428","65374","109"},
    {"mds7_im",QT_TRANSLATE_NOOP("Locations","Sector 7 Item Store"),"1","152","21","65492","24"},
    {"7min1",QT_TRANSLATE_NOOP("Locations","Johnny's Home"),"1","153","65521","91","55"},
    {"mds7pb_1",QT_TRANSLATE_NOOP("Locations","7th Heaven"),"1","154","67","6","26"},
    {"mds7pb_2",QT_TRANSLATE_NOOP("Locations","AVALANCHE Hideout"),"1","155","65346","65371","41"},
    {"mds7plr1",QT_TRANSLATE_NOOP("Locations","Sector 7 Slums"),"1","156","65185","636","231"},
    {"pillar_1",QT_TRANSLATE_NOOP("Locations","Plate Support"),"1","158","65332","64576","192"},
    {"pillar_2",QT_TRANSLATE_NOOP("Locations","Plate Support"),"1","159","193","64530","100"},

    {"pillar_3",QT_TRANSLATE_NOOP("Locations","Plate Support"),"1","160","262","65272","30"},
    {"tunnel_1",QT_TRANSLATE_NOOP("Locations","Winding Tunnel"),"1","161","25","89","145"},
    {"tunnel_2",QT_TRANSLATE_NOOP("Locations","Winding Tunnel"),"1","162","1","555","11"},
    {"4sbwy_1",QT_TRANSLATE_NOOP("Locations","4th Street Plate Int."),"1","164","65532","65123","4"},
    {"4sbwy_2",QT_TRANSLATE_NOOP("Locations","4th Street Plate Int."),"1","165","0","65490","9"},
    {"4sbwy_3",QT_TRANSLATE_NOOP("Locations","4th Street Plate Int."),"1","166","65382","575","21"},
    {"4sbwy_4",QT_TRANSLATE_NOOP("Locations","Lower Sector 4 Plate"),"1","167","17","1","7"},
    {"4sbwy_5",QT_TRANSLATE_NOOP("Locations","Lower Sector 4 Plate"),"1","168","65427","65419","65"},
    {"4sbwy_6",QT_TRANSLATE_NOOP("Locations","Lower Sector 4 Plate"),"1","169","65422","468","11"},

    {"mds5_5",QT_TRANSLATE_NOOP("Locations","Slum Outskirts"),"1","170","867","62914","15"},
    {"mds5_4",QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","171","65535","64904","12"},
    {"mds5_3",QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","172","159","65402","59"},
    {"mds5_2",QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","173","989","65501","4"},
    {"5min1_1",QT_TRANSLATE_NOOP("Locations","House 1f."),"1","174","65510","24","32"},
    {"5min1_2",QT_TRANSLATE_NOOP("Locations","House 2f."),"1","175","65486","76","7"},
    {"mds5_dk",QT_TRANSLATE_NOOP("Locations","Earthen Pipe"),"1","176","39","65259","57"},
    {"mds5_1",QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","177","64951","166","101"},
    {"mds5_w",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","178","65514","32","10"},
    {"mds5_i",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","179","102","65527","28"},

    {"mds5_m",QT_TRANSLATE_NOOP("Locations","Materia store"),"1","180","7","65449","21"},
    {"church",QT_TRANSLATE_NOOP("Locations","Church"),"1","181","65527","65364","52"},
    {"chrin_1b",QT_TRANSLATE_NOOP("Locations","church in the slums"),"1","183","65463","400","8"},
    {"chrin_2",QT_TRANSLATE_NOOP("Locations","Inside the Church"),"1","184","65162","1130","129"},
    {"chrin_3b",QT_TRANSLATE_NOOP("Locations","Church Roof"),"1","186","65526","410","33"},
    {"eals_1",QT_TRANSLATE_NOOP("Locations","Aerith's House"),"1","187","171","65329","138"},
    {"ealin_1",QT_TRANSLATE_NOOP("Locations","Aerith's House"),"1","188","65453","65465","41"},

    {"ealin_2",QT_TRANSLATE_NOOP("Locations","Aerith's House"),"1","190","63","305","25"},
    {"mds6_1",QT_TRANSLATE_NOOP("Locations","Sector 6"),"1","191","64282","65239","41"},
    {"mds6_2",QT_TRANSLATE_NOOP("Locations","Sector 6 park"),"1","192","65272","65481","194"},
    {"mds6_22",QT_TRANSLATE_NOOP("Locations","Sector 6 park"),"1","193","65485","65206","18"},
    {"mds6_3",QT_TRANSLATE_NOOP("Locations","Sector 6"),"1","194","46","220","16"},
    {"mrkt2",QT_TRANSLATE_NOOP("Locations","Wall Market"),"1","195","462","1080","58"},
    {"mkt_w",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","196","71","65446","29"},
    {"mkt_mens",QT_TRANSLATE_NOOP("Locations","Men's Hall"),"1","197","65519","220","139"},
    {"mkt_ia",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","198","65515","16","6"},
    {"mktinn",QT_TRANSLATE_NOOP("Locations","Inn"),"1","199","65333","0","27"},

    {"mkt_m",QT_TRANSLATE_NOOP("Locations","Materia Store"),"1","200","174","65428","9"},
    {"mkt_s1",QT_TRANSLATE_NOOP("Locations","Boutique"),"1","201","130","65511","41"},
    {"mkt_s2",QT_TRANSLATE_NOOP("Locations","Diner"),"1","202","88","65388","23"},
    {"mkt_s3",QT_TRANSLATE_NOOP("Locations","Pharmacy"),"1","203","30","65445","5"},
    {"mktpb",QT_TRANSLATE_NOOP("Locations","Bar"),"1","204","66","130","43"},
    {"mrkt1",QT_TRANSLATE_NOOP("Locations","Wall Market"),"1","205","65412","63098","93"},
    {"colne_1",QT_TRANSLATE_NOOP("Locations","Corneo Hall"),"1","206","53","341","35"},
    {"colne_2",QT_TRANSLATE_NOOP("Locations","Corneo Hall,1f."),"1","207","65363","65474","27"},
    {"colne_3",QT_TRANSLATE_NOOP("Locations","Corneo Hall,2f."),"1","208","65449","65153","76"},
    {"colne_4",QT_TRANSLATE_NOOP("Locations","Torture Room"),"1","209","556","32","15"},

    {"colne_5",QT_TRANSLATE_NOOP("Locations","Corneo Hall,2f."),"1","210","65528","65272","84"},
    {"colne_6",QT_TRANSLATE_NOOP("Locations","Corneo Hall,2f."),"1","211","145","308","43"},
    {"colne_b1",QT_TRANSLATE_NOOP("Locations","Sewer"),"1","212","304","116","14"},
    {"colne_b3",QT_TRANSLATE_NOOP("Locations","Sewer"),"1","213","66","65328","9"},
    {"mrkt3",QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","214","12","65429","24"},
    {"onna_2",QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","216","64","114","47"},
    {"onna_4",QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","218","1","65499","11"},

    {"onna_52",QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","220","65522","65255","36"},
    {"mrkt4",QT_TRANSLATE_NOOP("Locations","Wall Market"),"1","222","65467","544","4"},
    {"wcrimb_1",QT_TRANSLATE_NOOP("Locations","Plate Section"),"1","223","65527","909","111"},
    {"wcrimb_2",QT_TRANSLATE_NOOP("Locations","Plate Section"),"1","224","50","1290","70"},
    {"md0",QT_TRANSLATE_NOOP("Locations","Sector 0"),"1","225","61105","52237","16"},
    {"roadend",QT_TRANSLATE_NOOP("Locations","Outside Plates"),"1","226","65416","65529","224"},
    {"sinbil_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg."),"1","227","512","63074","105"},
    {"sinbil_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg."),"1","228","4","64828","4"},
    {"blinst_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. Stairs"),"1","229","65444","152","158"},

    {"blinst_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. Stairs"),"1","230","65495","75","150"},
    {"blinst_3",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. Stairs"),"1","231","65475","62","25"},
    {"blinele",QT_TRANSLATE_NOOP("Locations","Elevator"),"1","232","65530","16","7"},
    {"eleout",QT_TRANSLATE_NOOP("Locations","Outside Elevator"),"1","233","46","65515","18"},
    {"blin1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 1f. lobby"),"1","234","849","65426","108"},
    {"blin2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 2f. Lobby"),"1","235","64620","65476","46"},
    {"blin2_i",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 2f. Shop"),"1","236","112","65005","59"},
    {"blin3_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 3f. Lobby"),"1","237","64107","32","61"},
    {"blin59",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 59f."),"1","238","65121","64992","85"},
    {"blin60_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 60f."),"1","239","65397","64843","266"},

    {"blin60_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 60f."),"1","240","65404","64601","12"},
    {"blin61",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 61f."),"1","241","733","65077","296"},
    {"blin62_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 62f."),"1","242","611","65149","231"},
    {"blin62_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 62f."),"1","243","120","65110","74"},
    {"blin62_3",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 62f."),"1","244","65413","607","33"},
    {"blin63_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 63f."),"1","245","905","64842","377"},
    {"blin64",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 64f."),"1","247","64386","65253","245"},
    {"blin65_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 65f."),"1","248","581","65074","131"},
    {"blin65_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 65f."),"1","249","31","65168","86"},

    {"blin66_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.66f."),"1","250","567","65187","67"},
    {"blin66_3",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.66f."),"1","252","86","123","18"},
    {"blin66_4",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.66f."),"1","253","452","65458","4"},
    {"blin67_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.67f."),"1","256","65426","797","283"},
    {"blin671b",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.67f."),"1","257","65444","732","283"},
    {"blin67_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.67f."),"1","258","778","703","7"},
    {"blin67_3",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.67f."),"1","259","64746","65230","242"},

    {"blin673b",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.67f."),"1","260","64795","65159","238"},
    {"blin68_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.68f."),"1","262","64965","440","109"},
    {"blin68_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.68f."),"1","263","64542","65491","55"},
    {"blin69_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 69f."),"1","264","150","65102","226"},
    {"blin70_3",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 70f."),"1","268","134","1617","16"},

    {"niv_w",QT_TRANSLATE_NOOP("Locations","Nibelheim Item Store"),"1","270","380","65171","9"},
    {"nvmin1_1",QT_TRANSLATE_NOOP("Locations","Nibelheim House"),"1","271","121","92","62"},
    {"nvmin1_2",QT_TRANSLATE_NOOP("Locations","Nibelheim House"),"1","272","65472","27","14"},
    {"nivinn_1",QT_TRANSLATE_NOOP("Locations","Nibelheim Inn"),"1","273","65514","65123","34"},
    {"nivinn_2",QT_TRANSLATE_NOOP("Locations","Nibelheim Inn"),"1","274","126","158","14"},
    {"niv_cl",QT_TRANSLATE_NOOP("Locations","Cloud's House"),"1","276","65298","48","9"},

    {"nivl",QT_TRANSLATE_NOOP("Locations","Nibelheim"),"1","282","591","65463","35"},
    {"niv_ti1",QT_TRANSLATE_NOOP("Locations","Tifa's House"),"1","286","65322","23","24"},
    {"niv_ti2",QT_TRANSLATE_NOOP("Locations","Tifa's House"),"1","287","134","65281","46"},

    {"nivl_b1",QT_TRANSLATE_NOOP("Locations","Nibelheim"),"1","290","65406","1144","66"},
    {"sinin1_1",QT_TRANSLATE_NOOP("Locations","Mansion, 1f."),"1","297","0","255","109"},
    {"sinin1_2",QT_TRANSLATE_NOOP("Locations","Mansion, 1f."),"1","298","64663","507","92"},
    {"sinin2_1",QT_TRANSLATE_NOOP("Locations","Mansion, 2f."),"1","299","64890","749","157"},

    {"sinin2_2",QT_TRANSLATE_NOOP("Locations","Mansion, 2f."),"1","300","525","788","150"},
    {"sinin3",QT_TRANSLATE_NOOP("Locations","Mansion, Hidden Steps"),"1","301","65413","130","174"},
    {"sininb1",QT_TRANSLATE_NOOP("Locations","Mansion, Basement"),"1","302","65432","65283","24"},
    {"sininb2",QT_TRANSLATE_NOOP("Locations","Mansion, Basement"),"1","303","65338","64827","17"},
    {"sininb31",QT_TRANSLATE_NOOP("Locations","Mansion, Basement"),"1","304","65395","65411","140"},
    {"sininb41",QT_TRANSLATE_NOOP("Locations","Mansion, Basement"),"1","307","307","501","13"},
    {"sininb51",QT_TRANSLATE_NOOP("Locations","Mansion, Basement"),"1","309","80","970","94"},

    {"mtnvl2",QT_TRANSLATE_NOOP("Locations","Mt. Nibel"),"1","311","4623","63476","193"},
    {"mtnvl3",QT_TRANSLATE_NOOP("Locations","Mt. Nibel"),"1","312","4073","63874","29"},
    {"mtnvl4",QT_TRANSLATE_NOOP("Locations","Mt. Nibel"),"1","313","2907","65144","83"},
    {"mtnvl6",QT_TRANSLATE_NOOP("Locations","Nibel Reactor"),"1","315","64853","64742","16"},
    {"nvdun1",QT_TRANSLATE_NOOP("Locations","Mt. Nibel"),"1","317","667","65035","261"},
    {"nvdun2",QT_TRANSLATE_NOOP("Locations","Mt. Nibel Cave"),"1","318","237","65216","16"},

    {"nvmkin1",QT_TRANSLATE_NOOP("Locations","Nibel Reactor(Int.)"),"1","322","65527","362","23"},
    {"nvmkin21",QT_TRANSLATE_NOOP("Locations","Nibel Reactor(Int.)"),"1","323","3","65422","11"},
    {"elm_wa",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","328","38","114","15"},
    {"elm_i",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","329","40","58","4"},


    {"elmpb",QT_TRANSLATE_NOOP("Locations","Bar"),"1","330","65405","65486","13"},
    {"elminn_1",QT_TRANSLATE_NOOP("Locations","Inn: 1f"),"1","331","141","65297","14"},
    {"elminn_2",QT_TRANSLATE_NOOP("Locations","Inn: 2f"),"1","332","164","125","8"},
    {"elmin1_1",QT_TRANSLATE_NOOP("Locations","House: 1f"),"1","333","190","65339","34"},
    {"elmin1_2",QT_TRANSLATE_NOOP("Locations","House: 2f"),"1","334","332","65478","11"},
    {"elm",QT_TRANSLATE_NOOP("Locations","Kalm"),"1","335","65243","65147","112"},
    {"elmin2_1",QT_TRANSLATE_NOOP("Locations","House: 1f"),"1","336","65451","65515","14"},
    {"elmin2_2",QT_TRANSLATE_NOOP("Locations","House: 2f"),"1","337","114","70","14"},
    {"elmin3_1",QT_TRANSLATE_NOOP("Locations","House: 1f"),"1","338","174","65319","26"},
    {"elmin3_2",QT_TRANSLATE_NOOP("Locations","House: 2f"),"1","339","334","65385","34"},

    {"elmtow",QT_TRANSLATE_NOOP("Locations","Rear Tower (Pagoda)"),"1","340","61","65481","8"},
    {"elmmin4_1",QT_TRANSLATE_NOOP("Locations","House: 1f"),"1","341","33","108","27"},
    {"elmmin4_2",QT_TRANSLATE_NOOP("Locations","House: 2f"),"1","342","73","310","26"},
    {"farm",QT_TRANSLATE_NOOP("Locations","Chocobo farm"),"1","343","65329","65410","13"},
    {"frmin",QT_TRANSLATE_NOOP("Locations","Chocobo farm"),"1","344","65","65478","62"},
    {"frcyo",QT_TRANSLATE_NOOP("Locations","Chocobo Ranch"),"1","345","65402","65386","73"},
    {"sichi",QT_TRANSLATE_NOOP("Locations","Marshes"),"1","348","74","65504","40"},
    {"psdun_1",QT_TRANSLATE_NOOP("Locations","Mythril Mine"),"1","349","693","56","19"},

    {"psdun_2",QT_TRANSLATE_NOOP("Locations","Mythril Mine"),"1","350","146","367","90"},
    {"psdun_3",QT_TRANSLATE_NOOP("Locations","Mythril Mine"),"1","351","65333","65232","313"},
    {"psdun_4",QT_TRANSLATE_NOOP("Locations","Mythril Mine"),"1","352","65528","65241","12"},
    {"condor1",QT_TRANSLATE_NOOP("Locations","Base of Fort Condor"),"1","353","11","64991","9"},
    {"condor2",QT_TRANSLATE_NOOP("Locations","Entrance to Fort Condor"),"1","354","9","44","9"},
    {"convil_1",QT_TRANSLATE_NOOP("Locations","Fort Condor"),"1","355","1118","391","12"},
    {"convil_2",QT_TRANSLATE_NOOP("Locations","Watch Room"),"1","356","65484","65523","10"},

    {"junonr1",QT_TRANSLATE_NOOP("Locations","Upper Junon"),"1","360","1377","64753","106"},
    {"junonr2",QT_TRANSLATE_NOOP("Locations","Upper Junon"),"1","361","5934","60871","47"},
    {"jun_wa",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","364","245","65222","15"},
    {"jun_i1",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","365","65533","65452","2"},
    {"jun_m",QT_TRANSLATE_NOOP("Locations","Materia Store"),"1","366","32","65451","6"},
    {"junmin1",QT_TRANSLATE_NOOP("Locations","Barracks"),"1","367","88","65387","6"},
    {"junmin2",QT_TRANSLATE_NOOP("Locations","Barracks"),"1","368","266","65439","11"},
    {"junmin3",QT_TRANSLATE_NOOP("Locations","Barracks"),"1","369","302","65483","49"},

    {"junonl1",QT_TRANSLATE_NOOP("Locations","Lower Junon"),"1","370","63856","64626","131"},
    {"junonl2",QT_TRANSLATE_NOOP("Locations","Lower Junon"),"1","371","2454","64673","97"},
    {"junonl3",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","373","10","65484","29"},
    {"jun_a",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","374","65534","65350","23"},
    {"jun_i2",QT_TRANSLATE_NOOP("Locations","Materia Store"),"1","375","10","65188","46"},
    {"juninn",QT_TRANSLATE_NOOP("Locations","Junon Inn"),"1","376","45","197","21"},
    {"junpb_1",QT_TRANSLATE_NOOP("Locations","Shinra Member's Bar"),"1","377","82","65295","18"},
    {"junpb_3",QT_TRANSLATE_NOOP("Locations","Bar"),"1","379","17","65380","39"},

    {"junmin4",QT_TRANSLATE_NOOP("Locations","Barracks"),"1","380","182","65366","2"},
    {"junmin5",QT_TRANSLATE_NOOP("Locations","Barracks"),"1","381","74","65435","41"},
    {"jundoc1a",QT_TRANSLATE_NOOP("Locations","Junon Dock"),"1","382","65451","1237","10"},
    {"junair",QT_TRANSLATE_NOOP("Locations","Airport"),"1","384","13770","14517","108"},
    {"junair2",QT_TRANSLATE_NOOP("Locations","Airport"),"1","385","61459","64133","93"},
    {"junin1",QT_TRANSLATE_NOOP("Locations","Junon Airport Path"),"1","386","64902","65203","31"},
    {"junin1a",QT_TRANSLATE_NOOP("Locations","Locker Room"),"1","387","63982","64750","22"},

    {"junin3",QT_TRANSLATE_NOOP("Locations","Junon Path"),"1","390","64171","3390","27"},
    {"junin6",QT_TRANSLATE_NOOP("Locations","Junon Way"),"1","394","2184","64947","24"},
    {"junbin12",QT_TRANSLATE_NOOP("Locations","Junon Office F2"),"1","397","65162","65236","8"},

    {"subin_2b",QT_TRANSLATE_NOOP("Locations","Inside Submarine"),"1","408","65484","433","7"},

    {"semkin_8",QT_TRANSLATE_NOOP("Locations","Underwater Reactor"),"1","422","34","426","14"},
    {"ujunon1",QT_TRANSLATE_NOOP("Locations","Under Junon"),"1","428","565","680","29"},
    {"ujunon3",QT_TRANSLATE_NOOP("Locations","Dolphin Offing"),"1","429","64880","1735","138"},

    {"prisila",QT_TRANSLATE_NOOP("Locations","Priscilla's House"),"1","431","35","65436","60"},
    {"ujun_w",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","432","263","200","3"},
    {"jumin",QT_TRANSLATE_NOOP("Locations","Under Junon"),"1","433","65300","65331","4"},
    {"ship_1",QT_TRANSLATE_NOOP("Locations","Cargo Ship"),"1","436","65430","64368","46"},
    {"ship_2",QT_TRANSLATE_NOOP("Locations","Cargo Ship"),"1","437","357","65017","32"},
    {"shpin_2",QT_TRANSLATE_NOOP("Locations","Cargo Ship"),"1","439","32","65291","63"},

    {"shpin_3",QT_TRANSLATE_NOOP("Locations","Cargo Ship"),"1","440","2","65035","43"},
    {"del1",QT_TRANSLATE_NOOP("Locations","Costa del Sol Harbor"),"1","441","194","352","137"},
    {"del2",QT_TRANSLATE_NOOP("Locations","Costa del Sol"),"1","443","64374","83","129"},
    {"delinn",QT_TRANSLATE_NOOP("Locations","Costa del Sol Inn"),"1","444","65380","64945","52"},
    {"delpb",QT_TRANSLATE_NOOP("Locations","Bar"),"1","445","120","198","11"},
    {"delmin1",QT_TRANSLATE_NOOP("Locations","House for Sale"),"1","446","65496","65493","10"},
    {"delmin12",QT_TRANSLATE_NOOP("Locations","Cellar"),"1","447","65531","65488","48"},
    {"del3",QT_TRANSLATE_NOOP("Locations","Costa del Sol"),"1","449","65433","234","118"},

    {"ncorel",QT_TRANSLATE_NOOP("Locations","North Corel"),"1","450","590","65078","64"},
    {"ncoin1",QT_TRANSLATE_NOOP("Locations","North Corel"),"1","453","65503","65378","2"},
    {"ncoin2",QT_TRANSLATE_NOOP("Locations","North Corel"),"1","454","7","65297","17"},
    {"ncoin3",QT_TRANSLATE_NOOP("Locations","North Corel"),"1","455","232","1","16"},
    {"ncoinn",QT_TRANSLATE_NOOP("Locations","North Corel Inn"),"1","456","190","65275","36"},
    {"ropest",QT_TRANSLATE_NOOP("Locations","Ropeway Station"),"1","457","504","65328","39"},
    {"mtcrl_0",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","458","9","65278","103"},
    {"",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","459","65442","733","88"},

    {"mtcrl_2",QT_TRANSLATE_NOOP("Locations","Corel Reactor"),"1","460","1538","1674","36"},
    {"mtcrl_3",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","461","534","9","182"},
    {"mtcrl_4",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","462","63498","65531","220"},
    {"mtcrl_6",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","464","63453","957","206"},
    {"mtcrl_7",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","465","65532","176","15"},
    {"mtcrl_9",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","467","9","3575","106"},

    {"jail1",QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","471","65188","2345","239"},
    {"jailin1",QT_TRANSLATE_NOOP("Locations","Basement"),"1","472","56","56","11"},
    {"jail2",QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","473","876","1471","74"},
    {"jailpb",QT_TRANSLATE_NOOP("Locations","Prison Pub"),"1","474","132","65210","67"},
    {"jailin2",QT_TRANSLATE_NOOP("Locations","Mayor's Old House"),"1","475","65515","65467","10"},
    {"jailin4",QT_TRANSLATE_NOOP("Locations","Container"),"1","477","65507","65317","1"},
    {"jail3",QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","478","65132","223","39"},
    {"jail4",QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","479","129","308","104"},

    {"desert1",QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","481","3198","65154","307"},
    {"desert2",QT_TRANSLATE_NOOP("Locations","Corel Desert"),"1","482","3111","64838","251"},
    {"astage_a",QT_TRANSLATE_NOOP("Locations","Event square"),"1","484","2070","62450","28"},
    {"jet",QT_TRANSLATE_NOOP("Locations","Speed square"),"1","486","65473","64406","32"},
    {"jetin1",QT_TRANSLATE_NOOP("Locations","Platform"),"1","487","747","2","12"},
    {"bigwheel",QT_TRANSLATE_NOOP("Locations","Round Square"),"1","488","222","65503","6"},

    {"ghotel",QT_TRANSLATE_NOOP("Locations","Ghost Hotel"),"1","491","43","583","53"},
    {"ghotin_1",QT_TRANSLATE_NOOP("Locations","Hotel Lobby"),"1","492","65091","65525","96"},
    {"ghotin_2",QT_TRANSLATE_NOOP("Locations","Hotel"),"1","494","273","65320","8"},
    {"ghotin_3",QT_TRANSLATE_NOOP("Locations","Hotel Shop"),"1","495","250","65363","13"},
    {"gldst",QT_TRANSLATE_NOOP("Locations","Ropeway Station"),"1","496","64767","95","26"},
    {"gldgate",QT_TRANSLATE_NOOP("Locations","Terminal Floor"),"1","497","26","71","13"},
    {"coloss",QT_TRANSLATE_NOOP("Locations","Battle Square"),"1","499","3","63214","7"},


    {"coloin1",QT_TRANSLATE_NOOP("Locations","Arena Lobby"),"1","500","6","62258","5"},
    {"clsin2_2",QT_TRANSLATE_NOOP("Locations","Dio's Museum"),"1","503","1547","62729","9"},
    {"games",QT_TRANSLATE_NOOP("Locations","Wonder Square"),"1","505","149","64988","68"},
    {"games_1",QT_TRANSLATE_NOOP("Locations","Building 1f."),"1","506","29","1643","65"},
    {"games_2",QT_TRANSLATE_NOOP("Locations","Building 2f."),"1","507","12","357","23"},
    {"chorace",QT_TRANSLATE_NOOP("Locations","Chocobo Square"),"1","509","65463","63092","118"},

    {"crcin_1",QT_TRANSLATE_NOOP("Locations","Ticket Office"),"1","511","65279","65068","18"},
    {"crcin_2",QT_TRANSLATE_NOOP("Locations","Jungle"),"1","514","65463","65433","64"},
    {"gonjun2",QT_TRANSLATE_NOOP("Locations","Jungle"),"1","515","65535","65346","0"},
    {"gnmkf",QT_TRANSLATE_NOOP("Locations","Meltdown Reactor"),"1","516","200","58482","83"},
    {"gnmk",QT_TRANSLATE_NOOP("Locations","Meltdown Reactor"),"1","517","65520","64769","32"},
    {"gongaga",QT_TRANSLATE_NOOP("Locations","Gongaga Village"),"1","518","51","65171","96"},
    {"gon_wa1",QT_TRANSLATE_NOOP("Locations","Weapons Store"),"1","519","55","65498","2"},

    {"gon_i",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","521","76","65453","2"},
    {"gninn",QT_TRANSLATE_NOOP("Locations","Inn"),"1","522","65510","65333","13"},
    {"gomin",QT_TRANSLATE_NOOP("Locations","Zach's Home"),"1","523","65457","140","36"},
    {"goson",QT_TRANSLATE_NOOP("Locations","Mayor's Home"),"1","524","65419","65328","94"},
    {"cos_btm",QT_TRANSLATE_NOOP("Locations","Cosmo Canyon"),"1","525","64574","63796","128"},
    {"con_btm2",QT_TRANSLATE_NOOP("Locations","Cosmo Candle"),"1","526","65006","63732","48"},
    {"cosin1",QT_TRANSLATE_NOOP("Locations","Cosmo Canyon"),"1","529","128","65215","79"},

    {"cosin1_1",QT_TRANSLATE_NOOP("Locations","Elder's Room"),"1","530","99","65396","7"},
    {"cosin2",QT_TRANSLATE_NOOP("Locations","Gate of Naught"),"1","531","8","65448","71"},
    {"cosin3",QT_TRANSLATE_NOOP("Locations","Pub \"Starlet\" "),"1","532","403","65493","22"},
    {"cosin5",QT_TRANSLATE_NOOP("Locations","Sealed Cave"),"1","534","65391","624","47"},
    {"cosmin2",QT_TRANSLATE_NOOP("Locations","Materia Shop"),"1","535","65503","108","11"},
    {"cosmin3",QT_TRANSLATE_NOOP("Locations","Cosmo Canyon"),"1","536","137","58","16"},
    {"cosmin6",QT_TRANSLATE_NOOP("Locations","Shildra Inn"),"1","538","40","65292","22"},
    {"cosmin7",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","539","108","65477","32"},

    {"cos_top",QT_TRANSLATE_NOOP("Locations","Observatory"),"1","540","65455","65083","31"},
    {"bugin1a",QT_TRANSLATE_NOOP("Locations","Observatory"),"1","541","65389","42","32"},
    {"bugin2",QT_TRANSLATE_NOOP("Locations","Bugen Research Center"),"1","544","65429","65399","9"},
    {"gidun_1",QT_TRANSLATE_NOOP("Locations","Cave of the Gi"),"1","546","64466","515","198"},
    {"gidun_2",QT_TRANSLATE_NOOP("Locations","Cave of the Gi"),"1","547","333","64409","144"},
    {"gidun_4",QT_TRANSLATE_NOOP("Locations","Cave of the Gi"),"1","548","335","64015","17"},
    {"gidun_3",QT_TRANSLATE_NOOP("Locations","Cave of the Gi"),"1","549","65492","64577","19"},

    {"rckt3",QT_TRANSLATE_NOOP("Locations","House"),"1","552","65251","293","39"},
    {"rkt_w",QT_TRANSLATE_NOOP("Locations","Weapons Store"),"1","553","282","187","27"},
    {"rkt_i",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","554","182","143","39"},
    {"rktinn1",QT_TRANSLATE_NOOP("Locations","Shanghai Inn"),"1","555","65364","268","48"},
    {"rktinn2",QT_TRANSLATE_NOOP("Locations","Shanghai Inn"),"1","556","65435","330","40"},
    {"rckt",QT_TRANSLATE_NOOP("Locations","Rocket Town"),"1","557","65533","64815","2"},
    {"rktsid",QT_TRANSLATE_NOOP("Locations","House"),"1","558","65403","141","96"},
    {"rktmin1",QT_TRANSLATE_NOOP("Locations","House"),"1","559","65467","329","25"},

    {"rktmin2",QT_TRANSLATE_NOOP("Locations","House"),"1","560","65308","299","49"},
    {"rcktbas1",QT_TRANSLATE_NOOP("Locations","Rocket Launching Pad"),"1","561","63725","3688","120"},
    {"rcktbas2",QT_TRANSLATE_NOOP("Locations","Rocket Launching Pad"),"1","562","64529","4947","89"},
    {"rcktin2",QT_TRANSLATE_NOOP("Locations","Ship Hallway"),"1","564","65505","60","15"},

    {"yougan",QT_TRANSLATE_NOOP("Locations","Wilderness"),"1","572","65529","73","3"},
    {"yougan2",QT_TRANSLATE_NOOP("Locations","Plains"),"1","573","65461","28","265"},
    {"uta_wa",QT_TRANSLATE_NOOP("Locations","Wutai"),"1","575","65532","65523","2"},
    {"uta_im",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","576","19","65516","11"},
    {"utmin1",QT_TRANSLATE_NOOP("Locations","Wutai, Cat's House"),"1","577","0","65464","29"},
    {"utmin2",QT_TRANSLATE_NOOP("Locations","Wutai, Old Man's House"),"1","578","55","65425","46"},
    {"uutai1",QT_TRANSLATE_NOOP("Locations","Wutai"),"1","579","64961","1101","34"},

    {"utapb",QT_TRANSLATE_NOOP("Locations","Bar [Turtle Paradise]"),"1","580","65417","65345","10"},
    {"yufy1",QT_TRANSLATE_NOOP("Locations","Yuffie's House"),"1","581","28","65461","25"},
    {"yufy2",QT_TRANSLATE_NOOP("Locations","Yuffie's House"),"1","582","81","64946","66"},
    {"hideway1",QT_TRANSLATE_NOOP("Locations","Hidden Passage"),"1","583","31","65454","1"},
    {"hideway2",QT_TRANSLATE_NOOP("Locations","Hidden Passage"),"1","584","8","65268","0"},
    {"hideway3",QT_TRANSLATE_NOOP("Locations","Hidden Passage"),"1","585","65532","65364","1"},
    {"5tower",QT_TRANSLATE_NOOP("Locations","Wutai, Godo's Pagoda"),"1","586","5","65246","3"},
    {"uutai2",QT_TRANSLATE_NOOP("Locations","Wutai, Pagoda"),"1","587","65452","60391","10"},
    {"uttmpin1",QT_TRANSLATE_NOOP("Locations","Wutai, Main Mtn."),"1","588","89","65227","88"},
    {"uttmpin2",QT_TRANSLATE_NOOP("Locations","Wutai, Main Mtn."),"1","589","60631","65163","54"},

    {"uttmpin3",QT_TRANSLATE_NOOP("Locations","Wutai, Main Mtn."),"1","590","11","65441","10"},
    {"uttmpin4",QT_TRANSLATE_NOOP("Locations","Hidden Room"),"1","591","2","65374","16"},
    {"datiao_1",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","592","589","64681","11"},
    {"datiao_2",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","594","64593","65327","0"},
    {"datiao_3",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","593","192","65508","22"},
    {"datiao_4",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","595","619","65491","28"},
    {"datiao_5",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","596","64983","65522","7"},
    {"datiao_6",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","597","65219","65298","116"},
    {"datiao_7",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","598","65174","361","2"},
    {"datiao_8",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","599","65355","65145","16"},

    {"jtempl",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","600","509","64236","2"},
    {"jtmpin1",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","602","65521","65327","32"},
    {"kuro_1",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","604","0","0","0"},
    {"kuro_2",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","605","65477","39","30"},
    {"kuro_3",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","606","65461","1430","61"},
    {"kuro_6",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","609","65533","65345","2"},

    {"kuro_7",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","610","65191","314","127"},
    {"kuro_8",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","611","65062","86","9"},
    {"kuro_10",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","614","65532","608","2"},
    {"kuro_11",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","615","4","844","12"},
    {"kuro_12",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","616","4","65317","30"},
    {"bonevil",QT_TRANSLATE_NOOP("Locations","Bone Village"),"1","617","65377","65366","65"},
    {"slfrst_1",QT_TRANSLATE_NOOP("Locations","Sleeping Forest"),"1","618","2","65410","8"},
    {"slfrst_2",QT_TRANSLATE_NOOP("Locations","Sleeping Forest"),"1","619","65533","65205","18"},

    {"sango1",QT_TRANSLATE_NOOP("Locations","Correl Valley"),"1","625","65424","65191","76"},
    {"sango2",QT_TRANSLATE_NOOP("Locations","Correl Valley"),"1","626","63620","54216","14"},

    {"lost1",QT_TRANSLATE_NOOP("Locations","Forgotten Capital"),"1","630","63941","1142","10"},
    {"losin1",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","631","216","65352","29"},
    {"losin2",QT_TRANSLATE_NOOP("Locations","Forgotten Capital"),"1","632","192","65446","14"},
    {"losin3",QT_TRANSLATE_NOOP("Locations","Forgotten Captial"),"1","633","65402","65401","40"},
    {"lost2",QT_TRANSLATE_NOOP("Locations","Forgotten Capital"),"1","634","63949","4484","7"},
    {"lost3",QT_TRANSLATE_NOOP("Locations","Forgotten Capital"),"1","635","60070","7108","12"},
    {"losinn",QT_TRANSLATE_NOOP("Locations","Forgotten Capital"),"1","636","427","65379","5"},
    {"loslake1",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","637","65027","443","116"},
    {"loslake2",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","638","64984","64215","8"},

    {"blue_1",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","640","55614","5910","2"},
    {"blue_2",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","641","311","64546","40"},
    {"whitein",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","645","671","64337","13"},
    {"ancnt1",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","646","641","793","243"},
    {"ancnt2",QT_TRANSLATE_NOOP("Locations","Water Altar"),"1","647","443","64645","5"},

    /**********************************Below The List Is UnFinished   *********/
    {"gaiin_2",QT_TRANSLATE_NOOP("Locations","Gaeas Cliff"),"1","693","65384","1104","65"},
    {"gainn_7",QT_TRANSLATE_NOOP("Locations","Gaeas Cliff"),"1","699","65424","240","17"},
    {"holu_1",QT_TRANSLATE_NOOP("Locations","Gaeas Cliff Base"),"1","687","165","51","5"},
    {"trnad_2",QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","703","65170","64488","44"},
    {"trnad_4",QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","705","94","1168","173"},
    {"ithos",QT_TRANSLATE_NOOP("Locations","Mideel,Clinic"),"1","720","151","65380","19"},
    {"md8_6",QT_TRANSLATE_NOOP("Locations","Midgar Sector 8"),"1","732","265","65332","24"},
    {"md8_b1",QT_TRANSLATE_NOOP("Locations","Sector 8, Underground"),"1","733","65264","1614","116"},
    {"tunnel_4",QT_TRANSLATE_NOOP("Locations","Tunnel"),"1","736","65453","65237","215"},
    {"md8_32",QT_TRANSLATE_NOOP("Locations","Midgar Sector 8"),"1","739","61439","18394","34"},
    {"las0_6",QT_TRANSLATE_NOOP("Locations","North Crater"),"1","749","65344","16","35"},
    {"",QT_TRANSLATE_NOOP("Locations","Test Fight"),"2","0","0","0","0"},
    /****************Dupilcate Field Strings Don't Display************/
    {"",QT_TRANSLATE_NOOP("Locations","Cloud's Past"),"1","332","164","125","8"},
    {"",QT_TRANSLATE_NOOP("Locations","Cloud's Villa"),"1","446","65496","65493","10"},
    /****************World Map Places  Don't Display For Text Only***********/
    {"",QT_TRANSLATE_NOOP("Locations","Midgar Area"),"3","1","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Midgar Area"),"3","2","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Grasslands Area"),"3","3","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Grasslands Area"),"3","4","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Junon Area"),"3","5","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Junon Area"),"3","6","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Junon Area"),"3","7","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Corel Area"),"3","13","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Corel Area"),"3","14","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Gold Saucer Area"),"3","15","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Gold Saucer Area"),"3","16","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Gongaga Area"),"3","10","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Gongaga Area"),"3","17","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Cosmo Area"),"3","18","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Nibel Area"),"3","19","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Rocket Launch Pad Area"),"3","20","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Wutai Area"),"3","23","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Nibel Area"),"3","43","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Woodlands Area"),"3","172","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Icicle Area"),"3","25","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Icicle Area"),"3","57","0","0","0"},
    {"",QT_TRANSLATE_NOOP("Locations","Icicle Area"),"3","58","0","0","0"}
};
#endif //FF7LOCATION_H
