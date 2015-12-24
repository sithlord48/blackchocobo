/****************************************************************************/
//    copyright 2012 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
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

#include "FF7Text.h"
/*~~~~~~~~TEXT CLASS~~~~~~~~~*/
FF7TEXT::FF7TEXT()
{
	eng   =QString::fromUtf8(" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ÄÁÇÉÑÖÜáàâäãåçéèêëíìîïñóòôöõúùûü⌘°¢£ÙÛ¶ß®©™´¨≠ÆØ∞±≤≥¥µ∂ΣΠπ⌡ªºΩæø¿¡¬√ƒ≈∆«»… ÀÃÕŒœ–—“”‘’÷◊ÿŸ⁄¤‹›ﬁﬂ■▪‚„‰ÂÊËÁÈíîïìÓÔ ÒÙÛ             \t                               ");
	jap   =QString::fromUtf8("バばビびブぶベべボぼガがギぎグぐゲげゴごザざジじズずゼぜゾぞダだヂぢヅづデでドどヴパぱピぴプぷペぺポぽ０１２３４５６７８９、。　ハはヒひフふヘへホほカかキきクくケけコこサさシしスすセせソそタたチちツつテてトとウうアあイいエえオおナなニにヌぬネねノのマまミみムむメめモもラらリりルるレれロろヤやユゆヨよワわンんヲをッっャゃュゅョょァぁィぃゥぅェぇォぉ！？『』．＋ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ・＊ー～⋯％／：＆【】♥→αβ「」（）－＝¶¶¶⑬\n\n¶                      ");
	jap_fa=QString::fromUtf8("必殺技地獄火炎裁雷大怒斬鉄剣槍海衝聖審判転生改暗黒釜天崩壊零式自爆使放射臭息死宣告凶破晄撃画龍晴点睛超究武神覇癒風邪気封印吹烙星守護命鼓動福音掌打水面蹴乱闘合体疾迅明鏡止抜山蓋世血祭鎧袖一触者滅森羅万象装備器攻魔法召喚獣呼出持相手物確率弱投付与変化片方行決定分直前真似覚列後位置防御発回連続敵全即効果尾毒消金針乙女興奮剤鎮静能薬英雄榴弾右腕砂時計糸戦惑草牙南極冷結晶電鳥角有害質爪光月反巨目砲重力球空双野菜実兵単毛茶色髪¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶");
	jap_fb=QString::fromUtf8("安香花会員蜂蜜館下着入先不子供屋商品景交換階模型部離場所仲間無制限殿様秘氷河図何材料雪上進事古代種鍵娘紙町住奥眠楽最初村雨釘陸吉揮叢雲軍異常通威父蛇矛青偃刀戟十字裏車円輪卍折鶴倶戴螺貝突銀玉正宗具甲烈属性吸収半減土高級状態縁闇睡石徐々的指混呪開始歩復盗小治理同速遅逃去視複味沈黙還倍数瀕取返人今差誰当拡散飛以外暴避振身中旋津波育機械擲炉新両本君洞内作警特殊板強穴隊族亡霊鎖足刃頭怪奇虫跳侍左首潜長親衛塔宝条像忍謎般見報充填完了銃元経験値終獲得名悲蛙操成費背切替割¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶");
	jap_fc=QString::fromUtf8("由閉記憶選番街底忘都過艇路運搬船墓心港末宿西道艦家乗竜巻迷宮絶壁支社久件想秒予多落受組余系標起迫日勝形引現解除磁互口廃棄汚染液活令副隠主斉登温泉百段熱走急降奪響嵐移危戻遠吠軟骨言葉震叫噴舞狩粉失敗眼激盤逆鱗踏喰盾叩食凍退木吐線魅押潰曲翼教皇太陽界案挑援赤往殴意東北参知聞来仕別集信用思毎悪枯考然張好伍早各独配腐話帰永救感故売浮市加流約宇礼束母男年待宙立残俺少精士私険関倒休我許郷助要問係旧固荒稼良議導夢追説声任柱満未顔旅¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶");
	jap_fd=QString::fromUtf8("友伝夜探対調民読占頼若学識業歳争苦織困答準恐認客務居他再幸役縮情豊夫近窟責建求迎貸期工算湿難保帯届凝笑向可遊襲申次国素題普密望官泣創術演輝買途浴老幼利門格原管牧炭彼房驚禁注整衆語証深層査渡号科欲店括坑酬緊研権書暇兄派造広川賛駅絡在党岸服捜姉敷胸刑谷痛岩至勢畑姿統略抹展示修酸製歓接障災室索扉傷録優基讐勇司境璧医怖狙協犯資設雇根億脱富躍純写病依到練順園総念維検朽圧補公働因朝浪祝恋郎勉春功耳恵緑美辺昇悩泊低酒影競二矢瞬希志¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶");
	jap_fe=QString::fromUtf8("孫継団給抗違提断島栄油就僕存企比浸非応細承編排努締談趣埋営文夏個益損額区寒簡遣例肉博幻量昔臓負討悔膨飲妄越憎増枚皆愚療庫涙照冗壇坂訳抱薄義騒奴丈捕被概招劣較析繁殖耐論貴称千歴史募容噂壱胞鳴表雑職妹氏踊停罪甘健焼払侵頃愛便田舎孤晩清際領評課勤謝才偉誤価欠寄忙従五送周頑労植施販台度嫌諸習緒誘仮借輩席戒弟珍酔試騎霜鉱裕票券専祖惰偶怠罰熟牲燃犠快劇拠厄抵適程繰腹橋白処匹杯暑坊週秀看軽幕和平王姫庭観航横帳丘亭財律布規謀積刻陥類¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶");
	init(0);
}

void FF7TEXT::init(bool ja)
{//are we using latin or japanese chars?
	if(ja){in_ja = 1;}
	else{in_ja=0;}
}

// the PC function is modified from Makou Reactor (thanks Myst6re)
QString FF7TEXT::toPC(QByteArray text)
{
	int txt;
	if((txt = text.indexOf('\xFF')) != -1){text.truncate(txt);}
	QString String;
	quint8 index;

	for(quint16 i=0 ; i<text.size() ; ++i)
	{
		index = (quint8)text.at(i);
		if(index == 0xFF)	break;
		if(in_ja)
		{
			switch(index) {
			case 0xFA:
				++i;
				String += jap_fa[(quint8)text.at(i)];
				break;
			case 0xFB:
				++i;
				String += jap_fb[(quint8)text.at(i)];
				break;
			case 0xFC:
				++i;
				String += jap_fc[(quint8)text.at(i)];
				break;
			 case 0xFD:
				++i;
				String += jap_fd[(quint8)text.at(i)];
				break;
			 case 0xFE:
				++i;
				if((quint8)text.at(i) == 0xE2)	i+=4;
				String += jap_fe[(quint8)text.at(i)];
				break;
			 default:
				String.append(jap.at(index));
			 break;
			 }
		 }
		 else
		 {
			switch(index) {
			case 0xFA:case 0xFB:case 0xFC:case 0xFD:
				++i;
				String += "¶";
				break;
			case 0xFE:
				++i;
				if((quint8)text.at(i) == 0xE2)	i+=4;
				String += "¶";
				break;
			default:
				String.append(eng.at(index));
				break;
			}
		}
	}
	return String;
}
//This Convertor is Modified From Hyne (thanks Myst6re)
QByteArray FF7TEXT::toFF7(QString string)
{
	QByteArray ff7str;
	QChar comp;
	int stringSize = string.size(), i, table;

	for(int c=0 ; c<stringSize ; ++c)
	{
		comp = string.at(c);
		for(i=0 ; i<=0xff ; ++i)
		{
			if(QString::compare(comp, character(i,0))==0)
			{
				ff7str.append((char)i);
				goto end;
			}
		}
		if(in_ja)
		{
			for(table=1 ; table<7 ; ++table)
			{
				for(i=0 ; i<=0xff ; ++i)
				{
					if(QString::compare(comp, character(i, table))==0)
					{
					   switch(table)
						{
							case 1:break;
							case 2:ff7str.append('\xFA');   break;
							case 3:ff7str.append('\xFB');   break;
							case 4:ff7str.append('\xFC');   break;
							case 5:ff7str.append('\xFD');   break;
							case 6:ff7str.append('\xFE');   break;
						}
						ff7str.append((char)i);
						goto end;
					}
				}
			}
		}
		end:;
	}
	return ff7str;
}

QString FF7TEXT::character(quint8 ord, quint8 table)
{
	switch(table) {
	case 1:return jap.at(ord);
	case 2:return jap_fa.at(ord);
	case 3:return jap_fb.at(ord);
	case 4:return jap_fc.at(ord);
	case 5:return jap_fd.at(ord);
	case 6:return jap_fe.at(ord);
	default:return eng.at(ord);
	}
}
