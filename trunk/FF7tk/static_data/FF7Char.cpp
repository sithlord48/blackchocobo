#include "FF7Char.h"
#include <QCoreApplication>

FF7Char::FF7Char(){}
quint8 FF7Char::id(int who){return Chars[who]._id;}
int FF7Char::weapon_starting_id(int who){return Chars[who]._starting_weapon_id;}
int FF7Char::weapon_offset(int who){return Chars[who]._weapon_offset;}
int FF7Char::num_weapons(int who){return Chars[who]._num_weapons;}

QImage FF7Char::Image(int who)
{
  if((who<0x0B))
  {
    return Chars[who]._avatar;
  }
  else
  {
    return QImage();
  }
}
QPixmap FF7Char::Pixmap(int who)
{
  if(who<0x0B)
  {
    return QPixmap::fromImage(Chars[who]._avatar);
  }
  else
  {
      return QPixmap::fromImage(QImage(""));
  }
}
QIcon FF7Char::Icon(int who){return QIcon(Pixmap(who));}
quint32 FF7Char::Total_Exp_For_Level(int who,int level){return Chars[who]._charlvls[level];}
quint32 FF7Char::Tnl_For_Level(int who,int level){return Chars[who]._chartnls[level];}
quint8 FF7Char::stat_grade(int who,int stat){return Chars[who]._stat_grade[stat];}
int FF7Char::mp_base(int who,int lvl_bracket){return Chars[who]._mp_base[lvl_bracket];}
quint8 FF7Char::mp_gradent (int who, int lvl_bracket){return Chars[who]._mp_gradent[lvl_bracket];}
int FF7Char::hp_base(int who,int lvl_bracket){return Chars[who]._hp_base[lvl_bracket];}
quint8 FF7Char::hp_gradent (int who, int lvl_bracket){return Chars[who]._hp_gradent[lvl_bracket];}
int FF7Char::luck_base(int who,int lvl_bracket){return Chars[who]._luck_base[lvl_bracket];}
quint8 FF7Char::luck_gradent (int who, int lvl_bracket){return Chars[who]._luck_gradent[lvl_bracket];}
quint8 FF7Char::stat_base (int rank,int lvl_bracket){return _stat_base[rank][lvl_bracket];}
quint8 FF7Char::stat_gradent (int rank,int lvl_bracket){return _stat_gradent[rank][lvl_bracket];}

QString FF7Char::defaultName(int who){return qApp->translate("Char_Names",Chars[who]._def_name.toAscii());}

QStringList FF7Char::limits(int who)
{
    QStringList translated_list;
    for(int j=0;j<Chars[who]._limits.count();j++)
    {
        translated_list.append(qApp->translate("Char_Limits", Chars[who]._limits.at(j).toAscii()));
    }
    return translated_list;
}

int FF7Char::stat_gain(int who,int stat, int stat_amount, int current_lvl, int next_lvl)
{
  int gain=0;//return this
  int diff=0; //holds our dif
  int lvl_bracket=0; //track what bracket in the gradent/base were looking at.
  //0:str; 1:vit; 2:mag; 3:spi; 4:dex; 5:luck; 6:hp; 7:mp
  int grade=0;// whats our grade in the stat only used for str/vit/mag/spi/dex
  int baseline_stat=0; // holds our baseline_stat calculation.
  //first find out the level bracket
  if(stat_amount==0){stat_amount = 1;}
  if(next_lvl>=2 && next_lvl<=11){lvl_bracket=0;}
  else if(next_lvl>=12 && next_lvl<=21){lvl_bracket=1;}
  else if(next_lvl>=22 && next_lvl<=31){lvl_bracket=2;}
  else if(next_lvl>=32 && next_lvl<=41){lvl_bracket=3;}
  else if(next_lvl>=42 && next_lvl<=51){lvl_bracket=4;}
  else if(next_lvl>=52 && next_lvl<=61){lvl_bracket=5;}
  else if(next_lvl>=62 && next_lvl<=81){lvl_bracket=6;}
  else if(next_lvl>=82 && next_lvl<=99){lvl_bracket=7;}
  //calculate the baseline to use.
  if(stat<5)
  {//calculating str,vit,mag,spi or dex
    grade = stat_grade(who,stat);
    baseline_stat = stat_base(grade,lvl_bracket)+((stat_gradent(grade,lvl_bracket)*next_lvl)/100);
  }
  else if(stat==5){baseline_stat = luck_base(who,lvl_bracket)+((luck_gradent(who,lvl_bracket))/100);}//
  else if(stat==6){baseline_stat = hp_base(who,lvl_bracket) + (next_lvl -1) * hp_gradent(who,lvl_bracket);}
  else if(stat==7){baseline_stat = mp_base(who,lvl_bracket) + ((next_lvl -1) * mp_gradent(who,lvl_bracket)/10);}
  //now calc the diff, so we can send back a gain based on type
  if(stat<6)
  {//str, vit,mag, spr,dex or luck all calculated the same
    //Vegeta_Ss4 lv down mod
    if(current_lvl < next_lvl) {diff = ((qrand() %8)+1) + (baseline_stat - stat_amount);}//is lv up
    else {diff = ((qrand() %8)+1) - baseline_stat + stat_amount;}//lv down
    if(diff<4){gain=0;}
    else if(diff<7){gain=1;}
    else if(diff<10){gain=2;}
    else {gain=3;}
  }
  else if(stat==6)
  {// Base HP Gain
      //Vegeta_Ss4 lv down mod
      if(current_lvl < next_lvl){diff = ((qrand()%8)+1) + (100* baseline_stat/stat_amount)-100;}//is lv up
      else {diff = ((qrand()%8)+1) + (100* stat_amount/baseline_stat)-100;}//lv down
      if(diff==0){gain = hp_gradent(who,lvl_bracket)*0.40;}
      else if (diff==1){gain = hp_gradent(who,lvl_bracket)*.50;}
      else if (diff==2){gain = hp_gradent(who,lvl_bracket)*.50;}
      else if (diff==3){gain = hp_gradent(who,lvl_bracket)*.60;}
      else if (diff==4){gain = hp_gradent(who,lvl_bracket)*.70;}
      else if (diff==5){gain = hp_gradent(who,lvl_bracket)*.80;}
      else if (diff==6){gain = hp_gradent(who,lvl_bracket)*.90;}
      else if (diff==7){gain = hp_gradent(who,lvl_bracket)*1.00;}
      else if (diff==8){gain = hp_gradent(who,lvl_bracket)*1.10;}
      else if (diff==9){gain = hp_gradent(who,lvl_bracket)*1.20;}
      else if (diff==10){gain = hp_gradent(who,lvl_bracket)*1.30;}
      else if (diff>=11){gain = hp_gradent(who,lvl_bracket)*1.50;}
  }
  else if(stat==7)
  {// Base MP Gain
      //Vegeta_Ss4 lv down mod
      if(current_lvl < next_lvl) {diff = ((qrand()%8)+1) + (100* baseline_stat/stat_amount)-100;}//is lv up
      else {diff = ((qrand()%8)+1) + (100* stat_amount/baseline_stat)-100;}//lv down

      if(diff ==0){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*0.20;}
      else if (diff==1){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*.30;}
      else if (diff==2){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*.30;}
      else if (diff==3){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*.50;}
      else if (diff==4){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*.70;}
      else if (diff==5){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*.80;}
      else if (diff==6){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*.90;}
      else if (diff==7){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*1.00;}
      else if (diff==8){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*1.10;}
      else if (diff==9){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*1.20;}
      else if (diff==10){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*1.40;}
      else if (diff>=11){gain = ((next_lvl*mp_gradent(who,lvl_bracket)/10)-((next_lvl-1)*mp_gradent(who,lvl_bracket)/10))*1.60;}
  }
  return gain;
}
