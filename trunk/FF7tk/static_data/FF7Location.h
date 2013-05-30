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
    QString t;
    QString d;
};

class FF7Location
{
public:
    QString fileName(int);
    QString fileName(int MapID,int LocID);
    QString locationString(int);
    QString locationString(QString fileName);
    QString mapID(int);
    QString mapID(QString fileName);
    QString locationID(int);
    QString locationID(QString fileName);
    QString x(int);
    QString x(QString fileName);
    QString y(int);
    QString y(QString fileName);
    QString t(int);
    QString t(QString fileName);
    QString d(int);
    QString d(QString fileName);
    int len(void);
};
static LOCATION Locations[]=
{
    /************************Every Location In The Game With Stock Translation******************/

    {"startmap",QT_TRANSLATE_NOOP("Locations","Debug Room [ja]"),"1","65","0","0","0","32"},
/*
    {"fship_1",QT_TRANSLATE_NOOP("Locations","Highwind"),"1","66","125","64275","27","32"},
    {"fship_12",QT_TRANSLATE_NOOP("Locations","deck"),"1","67","0","0","0","32"},
    {"fship_2",QT_TRANSLATE_NOOP("Locations",""),"1","68","0","0","0","32"},
    {"fship_22",QT_TRANSLATE_NOOP("Locations",""),"1","69","0","0","0","32"},
*/
    {"fship_25",QT_TRANSLATE_NOOP("Locations","Highwind"),"1","72","-3","-2587","99","0"},
    {"fship_3",QT_TRANSLATE_NOOP("Locations","Highwind"),"1","73","-168","-247","0","192"},
    {"fship_4",QT_TRANSLATE_NOOP("Locations","Highwind"),"1","74","213","-324","65","0"},
    {"fship_5",QT_TRANSLATE_NOOP("Locations","Highwind"),"1","76","-67","-123","11","96"},
    
    {"zz2",QT_TRANSLATE_NOOP("Locations","Weapon seller"),"1","79","-70","-124","28","128"},
    {"q_1",QT_TRANSLATE_NOOP("Locations","Hallway"),"1","88","-395","34","13","32"},
    {"blackbg2",QT_TRANSLATE_NOOP("Locations","Debug Room [en]"),"1","94","0","0","0","32"},

    {"md1stin",QT_TRANSLATE_NOOP("Locations","Platform"),"1","116","3655","27432","25","96"},
    {"md1_1",QT_TRANSLATE_NOOP("Locations","Sector 1 Station"),"1","117","1433","386","78","32"},
    {"md1_2",QT_TRANSLATE_NOOP("Locations","Sector 1"),"1","118","3568","30777","55","32"},
    {"nrthmk",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","119","-12","-2743","0","32"},

    {"nrthmk_1",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","120","-736","1612","16","32"},
    {"elevtr1",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","121","30","40","7","32"},
    {"nmkin_2",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","122","-205","235","90","32"},
    {"nmkin_3",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","123","-174","1692","35","32"},
    {"nmkin_4",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","124","37","1579","36","32"},
    {"nmkin_5",QT_TRANSLATE_NOOP("Locations","No.1 Reactor"),"1","125","-85","-1177","1","32"},
    {"southmk1",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","126","-4","-1875","7","32"},
    {"smkin_1",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","128","-1501","2546","20","32"},
    {"smkin_2",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","129","581","2137","157","32"},

    {"smkin_3",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","130","-176","1527","19","32"},
    {"smkin_4",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","131","34","1617","36","32"},
    {"smkin_5",QT_TRANSLATE_NOOP("Locations","No.5 Reactor"),"1","132","-89","-961","0","32"},
    {"md8_1",QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","133","1270","-5303","11","32"},
    {"md8_2",QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","134","-3967","21109","19","32"},
    {"md8_3",QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","135","-4113","18369","189","32"},
    {"md8brdg",QT_TRANSLATE_NOOP("Locations","Sector 8"),"1","137","-422","1111","6","32"},
    {"cargoin",QT_TRANSLATE_NOOP("Locations","Last Train From Midgar"),"1","138","6","42","20","32"},
    {"tin_1",QT_TRANSLATE_NOOP("Locations","Last Train From Midgar"),"1","139","2","537","28","32"},

    {"tin_2",QT_TRANSLATE_NOOP("Locations","Inside Train"),"1","140","12","579","29","32"},
    {"tin_3",QT_TRANSLATE_NOOP("Locations","Inside Train"),"1","141","-60","478","31","32"},
    {"tin_4",QT_TRANSLATE_NOOP("Locations","Inside Train"),"1","142","82","376","27","32"},
    {"mds7st1",QT_TRANSLATE_NOOP("Locations","Train Graveyard"),"1","144","1981","-3209","71","32"},
    {"mds7st2",QT_TRANSLATE_NOOP("Locations","Train Graveyard"),"1","145","1403","1151","197","32"},
    {"mds7st3",QT_TRANSLATE_NOOP("Locations","Sector 7 Station"),"1","146","-2738","3017","9","32"},
    {"mds7_w1",QT_TRANSLATE_NOOP("Locations","Sector 7 Weapon Shop"),"1","148","14","-4","5","32"},
    {"mds7_w2",QT_TRANSLATE_NOOP("Locations","Beginner's Hall"),"1","149","-235","9","30","32"},

    {"mds7_w3",QT_TRANSLATE_NOOP("Locations","Sector 7 Slums"),"1","150","-5","-184","12","32"},
    {"mds7",QT_TRANSLATE_NOOP("Locations","Sector 7 Slums"),"1","151","1428","-162","109","32"},
    {"mds7_im",QT_TRANSLATE_NOOP("Locations","Sector 7 Item Store"),"1","152","172","-5","21","32"},
    {"7min1",QT_TRANSLATE_NOOP("Locations","Johnny's Home"),"1","153","-15","91","55","32"},
    {"mds7pb_1",QT_TRANSLATE_NOOP("Locations","7th Heaven"),"1","154","67","6","26","32"},
    {"mds7pb_2",QT_TRANSLATE_NOOP("Locations","AVALANCHE Hideout"),"1","155","36","69","42","32"},
    {"mds7plr1",QT_TRANSLATE_NOOP("Locations","Sector 7 Slums"),"1","156","-351","636","231","32"},
    {"pillar_1",QT_TRANSLATE_NOOP("Locations","Plate Support"),"1","158","-204","-960","192","32"},
    {"pillar_2",QT_TRANSLATE_NOOP("Locations","Plate Support"),"1","159","193","-1006","100","32"},

    {"pillar_3",QT_TRANSLATE_NOOP("Locations","Plate Support"),"1","160","-461","-274","31","32"},
    {"tunnel_1",QT_TRANSLATE_NOOP("Locations","Winding Tunnel"),"1","161","25","89","145","32"},
    {"tunnel_2",QT_TRANSLATE_NOOP("Locations","Winding Tunnel"),"1","162","1","555","11","32"},
    {"4sbwy_1",QT_TRANSLATE_NOOP("Locations","4th Street Plate Int."),"1","164","-6","-340","4","32"},
    {"4sbwy_2",QT_TRANSLATE_NOOP("Locations","4th Street Plate Int."),"1","165","0","-46","9","32"},
    {"4sbwy_3",QT_TRANSLATE_NOOP("Locations","4th Street Plate Int."),"1","166","-139","574","21","32"},
    {"4sbwy_4",QT_TRANSLATE_NOOP("Locations","Lower Sector 4 Plate"),"1","167","17","1","7","32"},
    {"4sbwy_5",QT_TRANSLATE_NOOP("Locations","Lower Sector 4 Plate"),"1","168","-88","-72","65","32"},
    {"4sbwy_6",QT_TRANSLATE_NOOP("Locations","Lower Sector 4 Plate"),"1","169","-114","468","11","32"},

    {"mds5_5",QT_TRANSLATE_NOOP("Locations","Slum Outskirts"),"1","170","867","-2622","15","32"},
    {"mds5_4",QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","171","-28","-587","12","68"},
    {"mds5_3",QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","172","159","-134","59","32"},
    {"mds5_2",QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","173","-543","158","79","128"},
    {"5min1_1",QT_TRANSLATE_NOOP("Locations","House 1f."),"1","174","-26","24","32","32"},
    {"5min1_2",QT_TRANSLATE_NOOP("Locations","House 2f."),"1","175","-50","76","7","32"},
    {"mds5_dk",QT_TRANSLATE_NOOP("Locations","Earthen Pipe"),"1","176","39","-277","57","32"},
    {"mds5_1",QT_TRANSLATE_NOOP("Locations","Sector 5 Slum"),"1","177","-585","166","101","32"},
    {"mds5_w",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","178","-22","32","10","32"},
    {"mds5_i",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","179","102","-9","28","32"},

    {"mds5_m",QT_TRANSLATE_NOOP("Locations","Materia store"),"1","180","7","-87","21","32"},
    {"church",QT_TRANSLATE_NOOP("Locations","Church"),"1","181","-9","-172","52","32"},
    {"chrin_1b",QT_TRANSLATE_NOOP("Locations","church in the slums"),"1","183","-73","400","8","32"},
    {"chrin_2",QT_TRANSLATE_NOOP("Locations","Inside the Church"),"1","184","-374","1130","129","32"},
    {"chrin_3b",QT_TRANSLATE_NOOP("Locations","Church Roof"),"1","186","-10","410","33","32"},
    {"eals_1",QT_TRANSLATE_NOOP("Locations","Aerith's House"),"1","187","171","-207","138","32"},
    {"ealin_1",QT_TRANSLATE_NOOP("Locations","Aerith's House"),"1","188","-83","-71","41","32"},

    {"ealin_2",QT_TRANSLATE_NOOP("Locations","Aerith's House"),"1","190","63","305","25","32"},
    {"mds6_1",QT_TRANSLATE_NOOP("Locations","Sector 6"),"1","191","-1254","-297","41","32"},
    {"mds6_2",QT_TRANSLATE_NOOP("Locations","Sector 6 park"),"1","192","-264","-55","194","32"},
    {"mds6_22",QT_TRANSLATE_NOOP("Locations","Sector 6 park"),"1","193","-51","-330","18","32"},
    {"mds6_3",QT_TRANSLATE_NOOP("Locations","Sector 6"),"1","194","46","220","16","32"},
    {"mrkt2",QT_TRANSLATE_NOOP("Locations","Wall Market"),"1","195","462","1080","58","32"},
    {"mkt_w",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","196","71","-90","29","32"},
    {"mkt_mens",QT_TRANSLATE_NOOP("Locations","Men's Hall"),"1","197","-17","220","139","32"},
    {"mkt_ia",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","198","-21","16","6","32"},
    {"mktinn",QT_TRANSLATE_NOOP("Locations","Inn"),"1","199","-203","0","27","32"},

    {"mkt_m",QT_TRANSLATE_NOOP("Locations","Materia Store"),"1","200","174","-108","9","32"},
    {"mkt_s1",QT_TRANSLATE_NOOP("Locations","Boutique"),"1","201","130","-25","41","32"},
    {"mkt_s2",QT_TRANSLATE_NOOP("Locations","Diner"),"1","202","88","-148","23","32"},
    {"mkt_s3",QT_TRANSLATE_NOOP("Locations","Pharmacy"),"1","203","30","-91","5","32"},
    {"mktpb",QT_TRANSLATE_NOOP("Locations","Bar"),"1","204","66","130","43","32"},
    {"mrkt1",QT_TRANSLATE_NOOP("Locations","Wall Market"),"1","205","-124","-2438","93","32"},
    {"colne_1",QT_TRANSLATE_NOOP("Locations","Corneo Hall"),"1","206","53","341","35","32"},
    {"colne_2",QT_TRANSLATE_NOOP("Locations","Corneo Hall,1f."),"1","207","-169","-54","27","32"},
    {"colne_3",QT_TRANSLATE_NOOP("Locations","Corneo Hall,2f."),"1","208","-87","-383","76","32"},
    {"colne_4",QT_TRANSLATE_NOOP("Locations","Torture Room"),"1","209","556","32","15","32"},

    {"colne_5",QT_TRANSLATE_NOOP("Locations","Corneo Hall,2f."),"1","210","-8","-264","84","32"},
    {"colne_6",QT_TRANSLATE_NOOP("Locations","Corneo Hall,2f."),"1","211","145","308","43","32"},
    {"colne_b1",QT_TRANSLATE_NOOP("Locations","Sewer"),"1","212","304","116","14","32"},
    {"colne_b3",QT_TRANSLATE_NOOP("Locations","Sewer"),"1","213","66","-208","9","32"},
    {"mrkt3",QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","214","12","-107","24","32"},
    {"onna_2",QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","216","64","114","47","32"},
    {"onna_4",QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","218","1","-37","11","32"},

    {"onna_52",QT_TRANSLATE_NOOP("Locations","Honey Bee Inn"),"1","220","-14","-281","36","32"},
    {"mrkt4",QT_TRANSLATE_NOOP("Locations","Wall Market"),"1","222","-69","544","4","32"},
    {"wcrimb_1",QT_TRANSLATE_NOOP("Locations","Plate Section"),"1","223","-9","909","111","32"},
    {"wcrimb_2",QT_TRANSLATE_NOOP("Locations","Plate Section"),"1","224","50","1290","70","32"},
    {"md0",QT_TRANSLATE_NOOP("Locations","Sector 0"),"1","225","-4431","-13299","16","32"},
    {"roadend",QT_TRANSLATE_NOOP("Locations","Outside Plates"),"1","226","-1312","6","44","32"},
    {"sinbil_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg."),"1","227","514","-2458","105","32"},
    {"sinbil_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg."),"1","228","4","-708","4","32"},
    {"blinst_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. Stairs"),"1","229","-92","152","158","32"},

    {"blinst_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. Stairs"),"1","230","-41","75","150","32"},
    {"blinst_3",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. Stairs"),"1","231","-61","62","25","32"},
    {"blinele",QT_TRANSLATE_NOOP("Locations","Elevator"),"1","232","-6","16","7","128"},
    {"eleout",QT_TRANSLATE_NOOP("Locations","Outside Elevator"),"1","233","46","-21","18","32"},
    {"blin1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 1f. lobby"),"1","234","849","-110","108","32"},
    {"blin2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 2f. Lobby"),"1","235","-916","-60","46","32"},
    {"blin2_i",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 2f. Shop"),"1","236","112","-531","59","32"},
    {"blin3_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 3f. Lobby"),"1","237","-1429","32","61","32"},
    {"blin59",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 59f."),"1","238","-415","-544","85","32"},
    {"blin60_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 60f."),"1","239","-139","-693","266","32"},

    {"blin60_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 60f."),"1","240","-132","-935","12","104"},
    {"blin61",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 61f."),"1","241","733","-459","296","32"},
    {"blin62_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 62f."),"1","242","611","-387","231","32"},
    {"blin62_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 62f."),"1","243","120","-426","74","32"},
    {"blin62_3",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 62f."),"1","244","-123","607","33","32"},
    {"blin63_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 63f."),"1","245","905","-694","377","32"},
    {"blin64",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 64f."),"1","247","-1150","-283","245","32"},
    {"blin65_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 65f."),"1","248","581","-462","131","32"},
    {"blin65_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 65f."),"1","249","31","-368","86","32"},

    {"blin66_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.66f."),"1","250","567","-349","67","32"},
    {"blin66_3",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.66f."),"1","252","86","123","18","32"},
    {"blin66_4",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.66f."),"1","253","452","-78","4","32"},
    {"blin67_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.67f."),"1","256","-110","797","283","32"},
    {"blin671b",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.67f."),"1","257","-92","732","283","32"},
    {"blin67_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.67f."),"1","258","778","703","7","32"},
    {"blin67_3",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.67f."),"1","259","-790","-306","242","32"},

    {"blin673b",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.67f."),"1","260","-741","-377","238","32"},
    {"blin68_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.68f."),"1","262","-571","440","109","32"},
    {"blin68_2",QT_TRANSLATE_NOOP("Locations","Shinra Bldg.68f."),"1","263","-994","-45","55","104"},
    {"blin69_1",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 69f."),"1","264","150","-434","226","32"},
    {"blin70_3",QT_TRANSLATE_NOOP("Locations","Shinra Bldg. 70f."),"1","268","134","1617","16","32"},

    {"niv_w",QT_TRANSLATE_NOOP("Locations","Nibelheim Item Store"),"1","270","380","-365","9","32"},
    {"nvmin1_1",QT_TRANSLATE_NOOP("Locations","Nibelheim House"),"1","271","121","92","62","32"},
    {"nvmin1_2",QT_TRANSLATE_NOOP("Locations","Nibelheim House"),"1","272","-64","27","14","104"},
    {"nivinn_1",QT_TRANSLATE_NOOP("Locations","Nibelheim Inn"),"1","273","22","-413","34","32"},
    {"nivinn_2",QT_TRANSLATE_NOOP("Locations","Nibelheim Inn"),"1","274","126","158","14","32"},
    {"niv_cl",QT_TRANSLATE_NOOP("Locations","Cloud's House"),"1","276","-238","48","9","32"},
    
    {"nivgate",QT_TRANSLATE_NOOP("Locations",""),"1","279","12","-1274","0","120"},
    

    {"nivl",QT_TRANSLATE_NOOP("Locations","Nibelheim"),"1","282","591","-73","35","32"},
    {"nivl_3",QT_TRANSLATE_NOOP("Locations","Nibelheim"),"1","284","161","-480","7","28"},
    {"niv_ti1",QT_TRANSLATE_NOOP("Locations","Tifa's House"),"1","286","-214","23","24","32"},
    {"niv_ti2",QT_TRANSLATE_NOOP("Locations","Tifa's House"),"1","287","134","-255","46","32"},

    {"nivl_b1",QT_TRANSLATE_NOOP("Locations","Nibelheim"),"1","290","-130","1144","66","32"},
    
    {"nivl_b22",QT_TRANSLATE_NOOP("Locations","Nibelheim"),"1","293","302","-43","19","117"},
    
    {"nivl_e3",QT_TRANSLATE_NOOP("Locations","Nibelheim"),"1","296","0","0","0","0"}, 
    {"sinin1_1",QT_TRANSLATE_NOOP("Locations","Mansion, 1f."),"1","297","0","255","109","32"},
    {"sinin1_2",QT_TRANSLATE_NOOP("Locations","Mansion, 1f."),"1","298","-873","507","92","32"},
    {"sinin2_1",QT_TRANSLATE_NOOP("Locations","Mansion, 2f."),"1","299","-646","749","157","32"},

    {"sinin2_2",QT_TRANSLATE_NOOP("Locations","Mansion, 2f."),"1","300","525","788","150","32"},
    {"sinin3",QT_TRANSLATE_NOOP("Locations","Mansion, Hidden Steps"),"1","301","-123","130","174","32"},
    {"sininb1",QT_TRANSLATE_NOOP("Locations","Mansion, Basement"),"1","302","-104","-253","24","32"},
    {"sininb2",QT_TRANSLATE_NOOP("Locations","Mansion, Basement"),"1","303","-198","-709","17","32"},
    {"sininb31",QT_TRANSLATE_NOOP("Locations","Mansion, Basement"),"1","304","-141","-125","140","32"},
    {"sininb32",QT_TRANSLATE_NOOP("Locations","Mansion, Basement"),"1","305","-262","-212","46","64"},
    {"sininb41",QT_TRANSLATE_NOOP("Locations","Mansion, Basement"),"1","307","307","501","13","32"},
    {"sininb51",QT_TRANSLATE_NOOP("Locations","Mansion, Basement"),"1","309","80","970","94","32"},

    {"mtnvl2",QT_TRANSLATE_NOOP("Locations","Mt. Nibel"),"1","311","4623","-2060","193","32"},
    {"mtnvl3",QT_TRANSLATE_NOOP("Locations","Mt. Nibel"),"1","312","4073","-1662","29","32"},
    {"mtnvl4",QT_TRANSLATE_NOOP("Locations","Mt. Nibel"),"1","313","2907","-392","83","32"},
    {"mtnvl6",QT_TRANSLATE_NOOP("Locations","Nibel Reactor"),"1","315","-683","-794","16","32"},
    {"nvdun1",QT_TRANSLATE_NOOP("Locations","Mt. Nibel"),"1","317","667","-501","261","32"},
    {"nvdun2",QT_TRANSLATE_NOOP("Locations","Mt. Nibel Cave"),"1","318","237","-320","16","32"},

    {"nvmkin1",QT_TRANSLATE_NOOP("Locations","Nibel Reactor(Int.)"),"1","322","-9","362","23","32"},
    {"nvmkin21",QT_TRANSLATE_NOOP("Locations","Nibel Reactor(Int.)"),"1","323","3","-114","11","32"},
    {"elm_wa",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","328","38","114","15","32"},
    {"elm_i",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","329","40","58","4","32"},


    {"elmpb",QT_TRANSLATE_NOOP("Locations","Bar"),"1","330","-131","-50","13","32"},
    {"elminn_1",QT_TRANSLATE_NOOP("Locations","Inn: 1f"),"1","331","141","-239","14","32"},
    {"elminn_2",QT_TRANSLATE_NOOP("Locations","Inn: 2f"),"1","332","164","125","8","32"},
    {"elmin1_1",QT_TRANSLATE_NOOP("Locations","House: 1f"),"1","333","190","-197","34","32"},
    {"elmin1_2",QT_TRANSLATE_NOOP("Locations","House: 2f"),"1","334","332","-58","11","32"},
    {"elm",QT_TRANSLATE_NOOP("Locations","Kalm"),"1","335","-293","-389","112","32"},
    {"elmin2_1",QT_TRANSLATE_NOOP("Locations","House: 1f"),"1","336","-85","-21","14","32"},
    {"elmin2_2",QT_TRANSLATE_NOOP("Locations","House: 2f"),"1","337","114","70","14","32"},
    {"elmin3_1",QT_TRANSLATE_NOOP("Locations","House: 1f"),"1","338","174","-217","26","32"},
    {"elmin3_2",QT_TRANSLATE_NOOP("Locations","House: 2f"),"1","339","334","-151","34","32"},

    {"elmtow",QT_TRANSLATE_NOOP("Locations","Rear Tower (Pagoda)"),"1","340","61","-55","8","32"},
    {"elmmin4_1",QT_TRANSLATE_NOOP("Locations","House: 1f"),"1","341","33","108","27","32"},
    {"elmmin4_2",QT_TRANSLATE_NOOP("Locations","House: 2f"),"1","342","73","310","26","32"},
    {"farm",QT_TRANSLATE_NOOP("Locations","Chocobo farm"),"1","343","-207","-126","13","32"},
    {"frmin",QT_TRANSLATE_NOOP("Locations","Chocobo farm"),"1","344","65","-58","62","32"},
    {"frcyo",QT_TRANSLATE_NOOP("Locations","Chocobo Ranch"),"1","345","-134","-150","73","32"},
    {"sichi",QT_TRANSLATE_NOOP("Locations","Marshes"),"1","348","74","-32","40","32"},
    {"psdun_1",QT_TRANSLATE_NOOP("Locations","Mythril Mine"),"1","349","693","56","19","32"},

    {"psdun_2",QT_TRANSLATE_NOOP("Locations","Mythril Mine"),"1","350","146","367","90","32"},
    {"psdun_3",QT_TRANSLATE_NOOP("Locations","Mythril Mine"),"1","351","-203","-304","313","32"},
    {"psdun_4",QT_TRANSLATE_NOOP("Locations","Mythril Mine"),"1","352","-8","-295","12","32"},
    {"condor1",QT_TRANSLATE_NOOP("Locations","Base of Fort Condor"),"1","353","11","-545","9","32"},
    {"condor2",QT_TRANSLATE_NOOP("Locations","Entrance to Fort Condor"),"1","354","9","44","9","32"},
    {"convil_1",QT_TRANSLATE_NOOP("Locations","Fort Condor"),"1","355","1118","391","12","32"},
    {"convil_2",QT_TRANSLATE_NOOP("Locations","Watch Room"),"1","356","-52","-13","10","32"},

    {"junonr1",QT_TRANSLATE_NOOP("Locations","Upper Junon"),"1","360","1377","-783","106","32"},
    {"junonr2",QT_TRANSLATE_NOOP("Locations","Upper Junon"),"1","361","5934","-4665","47","32"},
    {"jun_wa",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","364","245","-314","15","32"},
    {"jun_i1",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","365","-3","-84","2","32"},
    {"jun_m",QT_TRANSLATE_NOOP("Locations","Materia Store"),"1","366","32","-85","6","32"},
    {"junmin1",QT_TRANSLATE_NOOP("Locations","Barracks"),"1","367","88","-149","6","32"},
    {"junmin2",QT_TRANSLATE_NOOP("Locations","Barracks"),"1","368","266","-97","11","32"},
    {"junmin3",QT_TRANSLATE_NOOP("Locations","Barracks"),"1","369","302","-53","49","32"},

    {"junonl1",QT_TRANSLATE_NOOP("Locations","Lower Junon"),"1","370","-1680","-910","131","32"},
    {"junonl2",QT_TRANSLATE_NOOP("Locations","Lower Junon"),"1","371","2454","-863","97","32"},
    {"junonl3",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","373","10","-52","29","32"},
    {"jun_a",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","374","-2","-186","23","32"},
    {"jun_i2",QT_TRANSLATE_NOOP("Locations","Materia Store"),"1","375","10","-348","46","32"},
    {"juninn",QT_TRANSLATE_NOOP("Locations","Junon Inn"),"1","376","45","197","21","32"},
    {"junpb_1",QT_TRANSLATE_NOOP("Locations","Shinra Member's Bar"),"1","377","82","-241","18","32"},
    {"junpb_3",QT_TRANSLATE_NOOP("Locations","Bar"),"1","379","17","-156","39","32"},

    {"junmin4",QT_TRANSLATE_NOOP("Locations","Barracks"),"1","380","182","-170","2","32"},
    {"junmin5",QT_TRANSLATE_NOOP("Locations","Barracks"),"1","381","74","-101","41","32"},
    {"jundoc1a",QT_TRANSLATE_NOOP("Locations","Junon Dock"),"1","382","-85","1237","10","32"},
    {"junair",QT_TRANSLATE_NOOP("Locations","Airport"),"1","384","13770","14517","108","32"},
    {"junair2",QT_TRANSLATE_NOOP("Locations","Airport"),"1","385","-4077","-1403","93","32"},
    {"junin1",QT_TRANSLATE_NOOP("Locations","Junon Airport Path"),"1","386","-634","-333","31","32"},
    {"junin1a",QT_TRANSLATE_NOOP("Locations","Locker Room"),"1","387","-1554","-786","22","32"},
    
    {"junin2",QT_TRANSLATE_NOOP("Locations","Path 2"),"1","389","-48","74","3","0"},
    

    {"junin3",QT_TRANSLATE_NOOP("Locations","Junon Path"),"1","390","-1365","3390","27","32"},
    {"junin6",QT_TRANSLATE_NOOP("Locations","Junon Way"),"1","394","2184","-589","24","32"},
    {"junbin1",QT_TRANSLATE_NOOP("Locations","Junon Branch, 1f."),"1","396","333","-165","133","0"},
    
    {"junbin12",QT_TRANSLATE_NOOP("Locations","Junon Office F2"),"1","397","-364","-303","8","32"},
    {"junbin21",QT_TRANSLATE_NOOP("Locations","Office"),"1","398","601","-758","125","0"},
    
    {"junbin3",QT_TRANSLATE_NOOP("Locations","Dr.'s Office"),"1","400","674","-1408","52","128"},
    {"junbin4",QT_TRANSLATE_NOOP("Locations","Press Room"),"1","401","-18","0","103","0"},
    {"junbin5",QT_TRANSLATE_NOOP("Locations","Gas Room"),"1","402","-57","-137","58","32"},
    
    {"subin_2b",QT_TRANSLATE_NOOP("Locations","Inside Submarine"),"1","408","-52","433","7","128"},

    {"junone2",QT_TRANSLATE_NOOP("Locations","Inside Submarine"),"1","411","13911","-2494","15","251"},
    {"junone4",QT_TRANSLATE_NOOP("Locations","Canon"),"1","413","180","-15763","8","0"},
    {"junone5",QT_TRANSLATE_NOOP("Locations","Junon branch,(ext.)"),"1","414","441","2966","1","128"},
    {"junone6",QT_TRANSLATE_NOOP("Locations","Canon"),"1","415","353","-7477","114","0"},
    {"junone7",QT_TRANSLATE_NOOP("Locations","Canon"),"1","416","-54","839","4","0"},
    
    
    {"semkin_8",QT_TRANSLATE_NOOP("Locations","Underwater Reactor"),"1","422","34","426","14","32"},
    {"ujunon1",QT_TRANSLATE_NOOP("Locations","Under Junon"),"1","428","565","680","29","32"},
    {"ujunon3",QT_TRANSLATE_NOOP("Locations","Dolphin Offing"),"1","429","-656","1735","138","32"},

    {"prisila",QT_TRANSLATE_NOOP("Locations","Priscilla's House"),"1","431","35","-100","60","32"},
    {"ujun_w",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","432","263","200","3","32"},
    {"jumin",QT_TRANSLATE_NOOP("Locations","Under Junon"),"1","433","-236","-205","4","32"},
    {"ship_1",QT_TRANSLATE_NOOP("Locations","Cargo Ship"),"1","436","-106","-1168","46","32"},
    {"ship_2",QT_TRANSLATE_NOOP("Locations","Cargo Ship"),"1","437","357","-524","32","32"},
    {"shpin_2",QT_TRANSLATE_NOOP("Locations","Cargo Ship"),"1","439","32","-245","63","32"},

    {"shpin_3",QT_TRANSLATE_NOOP("Locations","Cargo Ship"),"1","440","2","-501","43","32"},
    {"del1",QT_TRANSLATE_NOOP("Locations","Costa del Sol Harbor"),"1","441","194","352","137","32"},
    {"del2",QT_TRANSLATE_NOOP("Locations","Costa del Sol"),"1","443","-1162","83","129","32"},
    {"delinn",QT_TRANSLATE_NOOP("Locations","Costa del Sol Inn"),"1","444","-156","-591","52","32"},
    {"delpb",QT_TRANSLATE_NOOP("Locations","Bar"),"1","445","120","198","11","32"},
    {"delmin1",QT_TRANSLATE_NOOP("Locations","House for Sale"),"1","446","-40","-43","10","32"},
    {"delmin12",QT_TRANSLATE_NOOP("Locations","Cellar"),"1","447","-5","-48","48","32"},
    {"del3",QT_TRANSLATE_NOOP("Locations","Costa del Sol"),"1","449","-65","229","118","192"},

    {"ncorel",QT_TRANSLATE_NOOP("Locations","North Corel"),"1","450","590","-458","64","32"},
    {"ncoin1",QT_TRANSLATE_NOOP("Locations","North Corel"),"1","453","-33","-158","2","32"},
    {"ncoin2",QT_TRANSLATE_NOOP("Locations","North Corel"),"1","454","7","-239","17","32"},
    {"ncoin3",QT_TRANSLATE_NOOP("Locations","North Corel"),"1","455","232","1","16","32"},
    {"ncoinn",QT_TRANSLATE_NOOP("Locations","North Corel Inn"),"1","456","190","-261","36","32"},
    {"ropest",QT_TRANSLATE_NOOP("Locations","Ropeway Station"),"1","457","504","-208 ","39","32"},
    {"mtcrl_0",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","458","9","-258","103","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","459","-94","733","88","32"},

    {"mtcrl_2",QT_TRANSLATE_NOOP("Locations","Corel Reactor"),"1","460","1538","1674","36","32"},
    {"mtcrl_3",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","461","534","9","182","32"},
    {"mtcrl_4",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","462","-2038","-5","220","32"},
    {"mtcrl_6",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","464","-2083","957","206","32"},
    {"mtcrl_7",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","465","-4","176","15","32"},
    {"mtcrl_9",QT_TRANSLATE_NOOP("Locations","Mt. Corel"),"1","467","9","3575","106","32"},

    {"jail1",QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","471","-348","2345","239","32"},
    {"jailin1",QT_TRANSLATE_NOOP("Locations","Basement"),"1","472","56","56","11","32"},
    {"jail2",QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","473","876","1471","74","32"},
    {"jailpb",QT_TRANSLATE_NOOP("Locations","Prison Pub"),"1","474","132","-326","67","32"},
    {"jailin2",QT_TRANSLATE_NOOP("Locations","Mayor's Old House"),"1","475","-21","-69","10","32"},
    {"jailin4",QT_TRANSLATE_NOOP("Locations","Container"),"1","477","-29","-219","1","32"},
    {"jail3",QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","478","-404","223","39","32"},
    {"jail4",QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","479","129","308","104","32"},

    {"desert1",QT_TRANSLATE_NOOP("Locations","Corel Prison"),"1","481","3198","-382","307","32"},
    {"desert2",QT_TRANSLATE_NOOP("Locations","Corel Desert"),"1","482","3111","-698","251","32"},
    {"astage_a",QT_TRANSLATE_NOOP("Locations","Event square"),"1","484","2070","-3086","28","32"},
    {"jet",QT_TRANSLATE_NOOP("Locations","Speed square"),"1","486","-63","-1130","32","32"},
    {"jetin1",QT_TRANSLATE_NOOP("Locations","Platform"),"1","487","747","2","12","32"},
    {"bigwheel",QT_TRANSLATE_NOOP("Locations","Round Square"),"1","488","222","-33","6","32"},

    {"ghotel",QT_TRANSLATE_NOOP("Locations","Ghost Hotel"),"1","491","43","583","53","32"},
    {"ghotin_1",QT_TRANSLATE_NOOP("Locations","Hotel Lobby"),"1","492","-445","-11","96","32"},
    {"ghotin_2",QT_TRANSLATE_NOOP("Locations","Hotel"),"1","494","273","-216","8","32"},
    {"ghotin_3",QT_TRANSLATE_NOOP("Locations","Hotel Shop"),"1","495","250","-173","13","32"},
    {"gldst",QT_TRANSLATE_NOOP("Locations","Ropeway Station"),"1","496","-769","95","26","32"},
    {"gldgate",QT_TRANSLATE_NOOP("Locations","Terminal Floor"),"1","497","26","71","13","32"},
    {"coloss",QT_TRANSLATE_NOOP("Locations","Battle Square"),"1","499","3","-2322","7","32"},


    {"coloin1",QT_TRANSLATE_NOOP("Locations","Arena Lobby"),"1","500","6","-3278","5","128"},
    {"clsin2_2",QT_TRANSLATE_NOOP("Locations","Dio's Museum"),"1","503","1547","-2819","9","32"},
    {"games",QT_TRANSLATE_NOOP("Locations","Wonder Square"),"1","505","231","-527","67","216"},
    {"games_1",QT_TRANSLATE_NOOP("Locations","Building 1f."),"1","506","29","1643","65","32"},
    {"games_2",QT_TRANSLATE_NOOP("Locations","Building 2f."),"1","507","12","357","23","32"},
    {"chorace",QT_TRANSLATE_NOOP("Locations","Chocobo Square"),"1","509","-73","-2444","118","32"},

    {"crcin_1",QT_TRANSLATE_NOOP("Locations","Ticket Office"),"1","511","-257","-468","18","32"},
    {"crcin_2",QT_TRANSLATE_NOOP("Locations","Jungle"),"1","514","-73","-103","64","32"},
    {"gonjun2",QT_TRANSLATE_NOOP("Locations","Jungle"),"1","515","-1","-190","0","32"},
    {"gnmkf",QT_TRANSLATE_NOOP("Locations","Meltdown Reactor"),"1","516","200","-7054","83","32"},
    {"gnmk",QT_TRANSLATE_NOOP("Locations","Meltdown Reactor"),"1","517","-16","-767","32","104"},
    {"gongaga",QT_TRANSLATE_NOOP("Locations","Gongaga Village"),"1","518","51","-365","96","104"},
    {"gon_wa1",QT_TRANSLATE_NOOP("Locations","Weapons Store"),"1","519","55","-38","2","160"},

    {"gon_i",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","521","71","-76","7","152"},
    {"gninn",QT_TRANSLATE_NOOP("Locations","Inn"),"1","522","-26","-203","13","104"},
    {"gomin",QT_TRANSLATE_NOOP("Locations","Zack's Home"),"1","523","--109","132","45","232"},
    {"goson",QT_TRANSLATE_NOOP("Locations","Mayor's Home"),"1","524","-117","-208","94","32"},
    {"cos_btm",QT_TRANSLATE_NOOP("Locations","Cosmo Canyon"),"1","525","-962","-1740","128","32"},
    {"con_btm2",QT_TRANSLATE_NOOP("Locations","Cosmo Candle"),"1","526","-350","-1422","98","235"},
    {"cosin1",QT_TRANSLATE_NOOP("Locations","Cosmo Canyon"),"1","529","128","-321","79","32"},

    {"cosin1_1",QT_TRANSLATE_NOOP("Locations","Elder's Room"),"1","530","99","-140","7","32"},
    {"cosin2",QT_TRANSLATE_NOOP("Locations","Gate of Naught"),"1","531","8","-88","71","32"},
    {"cosin3",QT_TRANSLATE_NOOP("Locations","Pub \"Starlet\" "),"1","532","403","-43","22","32"},
    {"cosin5",QT_TRANSLATE_NOOP("Locations","Sealed Cave"),"1","534","-145","624","47","32"},
    {"cosmin2",QT_TRANSLATE_NOOP("Locations","Materia Shop"),"1","535","-33","108","11","32"},
    {"cosmin3",QT_TRANSLATE_NOOP("Locations","Cosmo Canyon"),"1","536","137","58","16","32"},
    {"cosmin6",QT_TRANSLATE_NOOP("Locations","Shildra Inn"),"1","538","40","-244","22","32"},
    {"cosmin7",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","539","108","-59","32","32"},

    {"cos_top",QT_TRANSLATE_NOOP("Locations","Observatory"),"1","540","-81","-453","31","104"},
    {"bugin1a",QT_TRANSLATE_NOOP("Locations","Observatory"),"1","541","-147","42","32","32"},
    {"bugin2",QT_TRANSLATE_NOOP("Locations","Bugen Research Center"),"1","544","-107","-137","9","32"},
    {"gidun_1",QT_TRANSLATE_NOOP("Locations","Cave of the Gi"),"1","546","-1070","515","198","32"},
    {"gidun_2",QT_TRANSLATE_NOOP("Locations","Cave of the Gi"),"1","547","333","-1127","144","32"},
    {"gidun_4",QT_TRANSLATE_NOOP("Locations","Cave of the Gi"),"1","548","335","-1521","17","32"},
    {"gidun_3",QT_TRANSLATE_NOOP("Locations","Cave of the Gi"),"1","549","-44","-959","19","104"},

    {"rckt3",QT_TRANSLATE_NOOP("Locations","House"),"1","552","-282","521","95","156"},
    {"rkt_w",QT_TRANSLATE_NOOP("Locations","Weapons Store"),"1","553","282","187","27","32"},
    {"rkt_i",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","554","182","143","39","32"},
    {"rktinn1",QT_TRANSLATE_NOOP("Locations","Shanghai Inn"),"1","555","-172","268","48","32"},
    {"rktinn2",QT_TRANSLATE_NOOP("Locations","Shanghai Inn"),"1","556","-101","330","40","32"},
    {"rckt",QT_TRANSLATE_NOOP("Locations","Rocket Town"),"1","557","-3","-721","2","104"},
    {"rktsid",QT_TRANSLATE_NOOP("Locations","House"),"1","558","-133","141","96","32"},
    {"rktmin1",QT_TRANSLATE_NOOP("Locations","House"),"1","559","-69","329","25","32"},

    {"rktmin2",QT_TRANSLATE_NOOP("Locations","House"),"1","560","-228","299","49","32"},
    {"rcktbas1",QT_TRANSLATE_NOOP("Locations","Rocket Launching Pad"),"1","561","-1607","3688","120","32"},
    {"rcktbas2",QT_TRANSLATE_NOOP("Locations","Rocket Launching Pad"),"1","562","-1007","4947","89","32"},
    {"rcktin2",QT_TRANSLATE_NOOP("Locations","Ship Hallway"),"1","564","-31","60","15","32"},

    {"yougan",QT_TRANSLATE_NOOP("Locations","Wilderness"),"1","572","-7","73","3","32"},
    {"yougan2",QT_TRANSLATE_NOOP("Locations","Plains"),"1","573","-72","28","265","32"},
    {"uta_wa",QT_TRANSLATE_NOOP("Locations","Wutai"),"1","575","-4","-13","2","32"},
    {"uta_im",QT_TRANSLATE_NOOP("Locations","Item Store"),"1","576","19","-20","11","32"},
    {"utmin1",QT_TRANSLATE_NOOP("Locations","Wutai, Cat's House"),"1","577","0","-72","29","32"},
    {"utmin2",QT_TRANSLATE_NOOP("Locations","Wutai, Old Man's House"),"1","578","55","-111","46","32"},
    {"uutai1",QT_TRANSLATE_NOOP("Locations","Wutai"),"1","579","-575","1101","34","32"},

    {"utapb",QT_TRANSLATE_NOOP("Locations","Bar [Turtle Paradise]"),"1","580","-119","-191","10","32"},
    {"yufy1",QT_TRANSLATE_NOOP("Locations","Yuffie's House"),"1","581","28","-75","25","32"},
    {"yufy2",QT_TRANSLATE_NOOP("Locations","Yuffie's House"),"1","582","81","-590","66","32"},
    {"hideway1",QT_TRANSLATE_NOOP("Locations","Hidden Passage"),"1","583","31","-82","1","32"},
    {"hideway2",QT_TRANSLATE_NOOP("Locations","Hidden Passage"),"1","584","8","-268","0","32"},
    {"hideway3",QT_TRANSLATE_NOOP("Locations","Hidden Passage"),"1","585","-4","-172","1","104"},
    {"5tower",QT_TRANSLATE_NOOP("Locations","Wutai, Godo's Pagoda"),"1","586","5","-290","3","104"},
    {"uutai2",QT_TRANSLATE_NOOP("Locations","Wutai, Pagoda"),"1","587","-84","-5145","10","32"},
    {"uttmpin1",QT_TRANSLATE_NOOP("Locations","Wutai, Main Mtn."),"1","588","89","-309","88","32"},
    {"uttmpin2",QT_TRANSLATE_NOOP("Locations","Wutai, Main Mtn."),"1","589","-4905","-373","54","32"},

    {"uttmpin3",QT_TRANSLATE_NOOP("Locations","Wutai, Main Mtn."),"1","590","11","-95","10","32"},
    {"uttmpin4",QT_TRANSLATE_NOOP("Locations","Hidden Room"),"1","591","2","-162","16","32"},
    {"datiao_1",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","592","589","-855","11","32"},
    {"datiao_3",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","593","192","-28","22","32"},
    {"datiao_2",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","594","-943","-209","0","32"},
    {"datiao_4",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","595","619","-45","28","32"},
    {"datiao_5",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","596","-553","-14","7","32"},
    {"datiao_6",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","597","-317","-238","116","32"},
    {"datiao_7",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","598","-362","361","2","32"},
    {"datiao_8",QT_TRANSLATE_NOOP("Locations","Wutai, Da-chao Statue"),"1","599","-181","-391","16","32"},

    {"jtempl",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","600","509","-1300","2","32"},
    {"jtmpin1",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","602","-15","-209","32","32"},
    {"kuro_1",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","604","0","0","0","32"},
    {"kuro_2",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","605","-59","39","30","32"},
    {"kuro_3",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","606","-75","1430","61","32"},
    {"kuro_6",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","609","-3","-191","2","32"},

    {"kuro_7",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","610","-345","314","127","32"},
    {"kuro_8",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","611","-474","86","9","32"},
    {"kuro_10",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","614","-4","608","2","32"},
    {"kuro_11",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","615","4","844","12","32"},
    {"kuro_12",QT_TRANSLATE_NOOP("Locations","Temple of the Ancients"),"1","616","4","-219","30","32"},
    {"bonevil",QT_TRANSLATE_NOOP("Locations","Bone Village"),"1","617","-159","-170","65","32"},
    {"slfrst_1",QT_TRANSLATE_NOOP("Locations","Sleeping Forest"),"1","618","2","-126","8","32"},
    {"slfrst_2",QT_TRANSLATE_NOOP("Locations","Sleeping Forest"),"1","619","-3","-331","18","32"},

    {"sango1",QT_TRANSLATE_NOOP("Locations","Correl Valley"),"1","625","-112","-345","76","32"},
    {"sango2",QT_TRANSLATE_NOOP("Locations","Correl Valley"),"1","626","-1916","-11320","14","32"},
    {"sango3",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","627","-65","431","135","84"},
    {"sandun_1",QT_TRANSLATE_NOOP("Locations","Correl Valley Cave"),"1","628","635","-599","164","192"},
    {"sandun_2",QT_TRANSLATE_NOOP("Locations","Correl Valley Cave"),"1","629","29","-1053","29","128"},


    {"lost1",QT_TRANSLATE_NOOP("Locations","Forgotten Capital"),"1","630","-1595","1142","10","32"},
    {"losin1",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","631","216","-184","29","32"},
    {"losin2",QT_TRANSLATE_NOOP("Locations","Forgotten Capital"),"1","632","192","-90","14","32"},
    {"losin3",QT_TRANSLATE_NOOP("Locations","Forgotten Captial"),"1","633","-134","-135","40","32"},
    {"lost2",QT_TRANSLATE_NOOP("Locations","Forgotten Capital"),"1","634","-1587","4484","7","32"},
    {"lost3",QT_TRANSLATE_NOOP("Locations","Forgotten Capital"),"1","635","-5466","7108","12","32"},
    {"losinn",QT_TRANSLATE_NOOP("Locations","Forgotten Capital"),"1","636","427","-157","5","32"},
    {"loslake1",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","637","-509","443","116","32"},
    {"loslake2",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","638","-552","-1321","8","32"},

    {"blue_1",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","640","-9922","5910","2","32"},
    {"blue_2",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","641","311","-990","40","32"},
    {"whitein",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","645","671","-1199","13","32"},
    {"ancnt1",QT_TRANSLATE_NOOP("Locations","Forgotten City"),"1","646","641","793","243","32"},
    {"ancnt2",QT_TRANSLATE_NOOP("Locations","Water Altar"),"1","647","443","-891","5","32"},

    {"snw_w",QT_TRANSLATE_NOOP("Locations","Weapon Store"),"1","650","-11","33","7","128"},
    {"sninn_1",QT_TRANSLATE_NOOP("Locations","Icicle Inn"),"1","651","44","164","37","128"},
    {"sninn_2",QT_TRANSLATE_NOOP("Locations","Icicle Inn"),"1","652","95","229","25","192"},
    {"sninn_b1",QT_TRANSLATE_NOOP("Locations","Icicle Inn Bar"),"1","653","68","328","79","64"},
    {"snow",QT_TRANSLATE_NOOP("Locations","Icicle Inn"),"1","654","-146","-904","96","128"},
    {"snmin1",QT_TRANSLATE_NOOP("Locations","Icicle Inn"),"1","655","13","84","26","128"},
    {"snmin2",QT_TRANSLATE_NOOP("Locations","Icicle Inn"),"1","656","-481","-421","61","128"},
    {"snmayor",QT_TRANSLATE_NOOP("Locations","Gast's House"),"1","657","-221","926","60","64"},
    {"hyou1",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","658","-12","765","69","128"},
    {"hyou2",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","659","-877","566","8","64"},

    {"hyou3",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","660","-316","1809","28","64"},
    {"icedun_1",QT_TRANSLATE_NOOP("Locations","Frostbite Cave"),"1","661","-66","-721","66","64"},
    {"icedun_2",QT_TRANSLATE_NOOP("Locations","Frostbite Cave"),"1","662","-523","-121","1","192"},
    {"hyou4",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","663","-76","-477","30","128"},
    {"hyou5_1",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","664","697","1965","104","192"},
    {"hyou5_2",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","665","183","-802","96","128"},
    {"hyou5_3",QT_TRANSLATE_NOOP("Locations","Cave"),"1","666","-62","121","87","192"},
    {"hyou5_4",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","667","158","329","4","128"},
    {"hyou6",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","668","-591","-79","188","64"},
    {"hyoumap",QT_TRANSLATE_NOOP("Locations","Great Glacier Map"),"1","669","0","-0","0","0"},

    {"move_s",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","670","996","-49","59","192"},
    {"move_i",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","671","1152","-5446","210","192"},
    {"move_f",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","672","1148","63","61","192"},
    {"move_r",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","673","-1224","-162","14","64"},
    {"move_u",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","674","-443","-906","140","112"},
    {"move_d",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","675","752","-371","92","160"},
    {"hyou7",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","676","238","-308","410","132"},
    {"hyou8_1",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","677","-242","2345","112","128"},
    {"hyou8_2",QT_TRANSLATE_NOOP("Locations","Cave"),"1","678","-16","422","14","192"},
    {"hyou9",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","679","1421","4048","10","0"},

    {"hyou10",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","680","373","-426","259","120"},
    {"hyou11",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","681","-719","-14","96","76"},
    {"hyou12",QT_TRANSLATE_NOOP("Locations","Cave"),"1","682","256","742","0","184"},
    {"hyou13_1",QT_TRANSLATE_NOOP("Locations","Great Glacier"),"1","683","-805","2884","27","0"},
    {"hyou13_2",QT_TRANSLATE_NOOP("Locations","Cave"),"1","684","-53","423","40","64"},
    {"gaiafoot",QT_TRANSLATE_NOOP("Locations","Base of Gaea's Cliff"),"1","687","165","51","5","32"},
    {"holu_1",QT_TRANSLATE_NOOP("Locations","Base of Gaea's Cliff"),"1","687","165","51","5","32"},
    {"holu_2",QT_TRANSLATE_NOOP("Locations","Base of Gaea's Cliff"),"1","688","159","-62","10","128"},
    {"gaia_1",QT_TRANSLATE_NOOP("Locations","Gaea's Cliff"),"1","689","-203","-814","1","128"},

    {"gaiin_1",QT_TRANSLATE_NOOP("Locations","Inside of Gaea's Cliff"),"1","690","-664","-864","151","128"},
    {"gaiin_2",QT_TRANSLATE_NOOP("Locations","Inside of Gaea's Cliff"),"1","691","11","-535","160","128"},
    {"gaia_2",QT_TRANSLATE_NOOP("Locations","Gaea's Cliff"),"1","692","-477","-132","19","128"},
    {"gaiin_3",QT_TRANSLATE_NOOP("Locations","Inside of Gaea's Cliff"),"1","693","-109","1123","65","32"},
    {"gaia_31",QT_TRANSLATE_NOOP("Locations","Gaea's Cliff"),"1","694","-631","1107","27","128"},
    {"gaia_32",QT_TRANSLATE_NOOP("Locations","Gaea's Cliff"),"1","695","-990","-28017","31","64"},
    {"gaiin_4",QT_TRANSLATE_NOOP("Locations","Inside of Gaea's Cliff"),"1","696","255","-4160","3","128"},
    {"gaiin_5",QT_TRANSLATE_NOOP("Locations","Inside of Gaea's Cliff"),"1","697","664","1099","38","192"},
    {"gaiin_6",QT_TRANSLATE_NOOP("Locations","Inside of Gaea's Cliff"),"1","698","-11","2455","8","0"},
    {"gainn_7",QT_TRANSLATE_NOOP("Locations","Inside of Gaea's Cliff"),"1","699","-116","265","17","32"},

    {"crater_1",QT_TRANSLATE_NOOP("Locations","Crater"),"1","700","910","-321","54","192"},
    {"crater_2",QT_TRANSLATE_NOOP("Locations","Crater"),"1","701","650","79","65","192"},
    {"trnad_1",QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","702","-72","43","32","128"},    
    {"trnad_2",QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","703","-358","-1056","44","32"},    
    {"trnad_3",QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","704","619","-3548","3","176"},    
    {"trnad_4",QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","705","94","1168","173","32"},
    
    {"woa_1",QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","709","121","-536","3","128"},
    
    {"woa_2",QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","710","123","-503","41","128"},
    {"woa_3",QT_TRANSLATE_NOOP("Locations","Whirlwind Maze"),"1","711","170","-339","68","128"},
    {"itown1a",QT_TRANSLATE_NOOP("Locations","Mideel"),"1","712","-64","-2225","63","128"},

    {"itown_w",QT_TRANSLATE_NOOP("Locations","Mideel,Weapon Store"),"1","717","36","-236","32","128"},
    {"itown_i",QT_TRANSLATE_NOOP("Locations","Mideel,Item Store"),"1","718","-90","-159","3","128"},
    {"itown_m",QT_TRANSLATE_NOOP("Locations","Mideel,Materia Store"),"1","719","34","-211","3","128"},

    
    {"ithos",QT_TRANSLATE_NOOP("Locations","Mideel,Clinic"),"1","720","151","-156","19","32"},
    {"itmin1",QT_TRANSLATE_NOOP("Locations","Mideel,House1"),"1","721","-158","-183","17","96"},
    
    {"zcoal_2",QT_TRANSLATE_NOOP("Locations","Coal Train"),"1","729","789","200","0","0"},
    
    /**********************************Below The List Is UnFinished   *********/
    {"md8_6",QT_TRANSLATE_NOOP("Locations","Midgar Sector 8"),"1","732","265","-204","24","32"},
    {"md8_b1",QT_TRANSLATE_NOOP("Locations","Sector 8, Underground"),"1","733","-272","1614","116","32"},
    {"tunnel_4",QT_TRANSLATE_NOOP("Locations","Tunnel"),"1","736","-83","-229","215","32"},
    {"md8_32",QT_TRANSLATE_NOOP("Locations","Midgar Sector 8"),"1","739","-4097","18394","34","32"},
    {"las0_6",QT_TRANSLATE_NOOP("Locations","North Crater"),"1","749","-192","16","35","32"},
    {"testfight",QT_TRANSLATE_NOOP("Locations","Test Fight"),"2","0","0","0","0","32"},
    /****************Dupilcate Field Strings Don't Display************/
    {"",QT_TRANSLATE_NOOP("Locations","Cloud's Past"),"1","332","164","125","8","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Cloud's Villa"),"1","446","-40","-43","10","32"},
    /****************World Map Places  Don't Display For Text Only***********/
    {"",QT_TRANSLATE_NOOP("Locations","Midgar Area"),"3","1","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Midgar Area"),"3","2","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Grasslands Area"),"3","3","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Grasslands Area"),"3","4","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Junon Area"),"3","5","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Junon Area"),"3","6","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Junon Area"),"3","7","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Corel Area"),"3","13","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Corel Area"),"3","14","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Gold Saucer Area"),"3","15","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Gold Saucer Area"),"3","16","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Gongaga Area"),"3","10","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Gongaga Area"),"3","17","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Cosmo Area"),"3","18","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Nibel Area"),"3","19","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Rocket Launch Pad Area"),"3","20","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Wutai Area"),"3","23","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Nibel Area"),"3","43","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Woodlands Area"),"3","172","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Icicle Area"),"3","25","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Icicle Area"),"3","57","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Icicle Area"),"3","58","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Icicle Area"),"3","26","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Icicle Area"),"3","27","0","0","0","32"},
    {"",QT_TRANSLATE_NOOP("Locations","Icicle Area"),"3","48","0","0","0","32"}

};
#endif //FF7LOCATION_H
