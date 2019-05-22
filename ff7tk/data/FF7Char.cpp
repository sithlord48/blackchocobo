/****************************************************************************/
//    copyright 2012 - 2018 Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//   FF7tk is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#include "FF7Char.h"

const FF7Char::Character& FF7Char::character(int who)
{
    if(who >= 0 && who <= 11) {
        return _charData.at(who);
    }
    return _emptyChar;
}

quint32 FF7Char::totalExpForLevel(int who, int level)
{
    level = std::clamp(level, 0, character(who)._charlvls.size() -1);
    return character(who)._charlvls.at(level);
}

quint32 FF7Char::tnlForLevel(int who, int level)
{
    level = std::clamp(level, 0, character(who)._charlvls.size() -1);
    return character(who)._chartnls.at(level);
}

QString FF7Char::defaultName(int who)
{
    who = std::clamp(who, 0, 10);
    return tr(_charData.at(who)._def_name.toLocal8Bit());
}

QStringList FF7Char::limits(int who)
{
    who = std::clamp(who, 0, 10);
    QStringList translated_list;
    for (const QString &limit : qAsConst(_charData.at(who)._limits)) {
        translated_list.append(tr(limit.toLocal8Bit()));
    }
    return translated_list;
}
int FF7Char::limitBitConvert(int bit)
{
    bit = std::clamp(bit, 0, 7);
    return _limitbitarray.at(bit);
}

int FF7Char::statGain(int who, int stat, int stat_amount, int current_lvl, int next_lvl)
{
    who = std::clamp(who, 0, 10);
    stat = std::clamp(stat, 0, 7);
    stat_amount = std::clamp(stat_amount, 0, 255);
    current_lvl = std::clamp(current_lvl, 0, 99);
    next_lvl = std::clamp(next_lvl, 0, 99);
    int gain = 0; //return this
    int diff = 0; //holds our dif
    int lvl_bracket = 0; //track what bracket in the gradent/base were looking at.
    //0:str; 1:vit; 2:mag; 3:spi; 4:dex; 5:luck; 6:hp; 7:mp
    int baseline_stat = 0; // holds our baseline_stat calculation.
    //first find out the level bracket
    if (stat_amount == 0) {
        stat_amount = 1;
    }
    if (next_lvl >= 2 && next_lvl <= 11) {
        lvl_bracket = 0;
    } else if (next_lvl >= 12 && next_lvl <= 21) {
        lvl_bracket = 1;
    } else if (next_lvl >= 22 && next_lvl <= 31) {
        lvl_bracket = 2;
    } else if (next_lvl >= 32 && next_lvl <= 41) {
        lvl_bracket = 3;
    } else if (next_lvl >= 42 && next_lvl <= 51) {
        lvl_bracket = 4;
    } else if (next_lvl >= 52 && next_lvl <= 61) {
        lvl_bracket = 5;
    } else if (next_lvl >= 62 && next_lvl <= 81) {
        lvl_bracket = 6;
    } else if (next_lvl >= 82 && next_lvl <= 99) {
        lvl_bracket = 7;
    }
    //calculate the baseline to use.
    if (stat < 5) {
        //calculating str,vit,mag,spi or dex
        int grade = stat_grade(who, stat);
        baseline_stat = stat_base(grade, lvl_bracket) + ((stat_gradent(grade, lvl_bracket) * next_lvl) / 100);
    } else if (stat == 5) {
        baseline_stat = luck_base(who, lvl_bracket) + ((luck_gradent(who, lvl_bracket)) / 100);   //
    } else if (stat == 6) {
        baseline_stat = hp_base(who, lvl_bracket) + (next_lvl - 1) * hp_gradent(who, lvl_bracket);
    } else if (stat == 7) {
        baseline_stat = mp_base(who, lvl_bracket) + ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10);
    }
    //now calc the diff, so we can send back a gain based on type
    if (stat < 6) {
        //str, vit,mag, spr,dex or luck all calculated the same
        //Vegeta_Ss4 lv down mod
        if (current_lvl < next_lvl) {
            diff = ((qrand() % 8) + 1) + (baseline_stat - stat_amount);   //is lv up
        } else {
            diff = ((qrand() % 8) + 1) - baseline_stat + stat_amount;   //lv down
        }
        if (diff < 4) {
            gain = 0;
        } else if (diff < 7) {
            gain = 1;
        } else if (diff < 10) {
            gain = 2;
        } else {
            gain = 3;
        }
    } else if (stat == 6) {
        // Base HP Gain
        //Vegeta_Ss4 lv down mod
        if (current_lvl < next_lvl) {
            diff = ((qrand() % 8) + 1) + (100 * baseline_stat / stat_amount) - 100;   //is lv up
        } else if (baseline_stat != 0) {
            diff = ((qrand() % 8) + 1) + (100 * stat_amount / baseline_stat) - 100;   //lv down
        }
        if (diff == 0) {
            gain = int(hp_gradent(who, lvl_bracket) * 0.40);
        } else if (diff == 1) {
            gain = int(hp_gradent(who, lvl_bracket) * .50);
        } else if (diff == 2) {
            gain = int(hp_gradent(who, lvl_bracket) * .50);
        } else if (diff == 3) {
            gain = int(hp_gradent(who, lvl_bracket) * .60);
        } else if (diff == 4) {
            gain = int(hp_gradent(who, lvl_bracket) * .70);
        } else if (diff == 5) {
            gain = int(hp_gradent(who, lvl_bracket) * .80);
        } else if (diff == 6) {
            gain = int(hp_gradent(who, lvl_bracket) * .90);
        } else if (diff == 7) {
            gain = int(hp_gradent(who, lvl_bracket) * 1.00);
        } else if (diff == 8) {
            gain = int(hp_gradent(who, lvl_bracket) * 1.10);
        } else if (diff == 9) {
            gain = int(hp_gradent(who, lvl_bracket) * 1.20);
        } else if (diff == 10) {
            gain = int(hp_gradent(who, lvl_bracket) * 1.30);
        } else if (diff >= 11) {
            gain = int(hp_gradent(who, lvl_bracket) * 1.50);
        }
    } else if (stat == 7) {
        // Base MP Gain
        //Vegeta_Ss4 lv down mod
        if (current_lvl < next_lvl) {
            diff = ((qrand() % 8) + 1) + (100 * baseline_stat / stat_amount) - 100;   //is lv up
        } else if (baseline_stat != 0) {
            diff = ((qrand() % 8) + 1) + (100 * stat_amount / baseline_stat) - 100;   //lv down
        }
        if (diff == 0) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * 0.20);
        } else if (diff == 1) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * .30);
        } else if (diff == 2) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * .30);
        } else if (diff == 3) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * .50);
        } else if (diff == 4) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * .70);
        } else if (diff == 5) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * .80);
        } else if (diff == 6) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * .90);
        } else if (diff == 7) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * 1.00);
        } else if (diff == 8) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * 1.10);
        } else if (diff == 9) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * 1.20);
        } else if (diff == 10) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * 1.40);
        } else if (diff >= 11) {
            gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * 1.60);
        }
    }
    return gain;
}
