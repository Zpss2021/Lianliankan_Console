#include "Menu.h"

options menus = {
	"冒险模式",
	"无尽模式",
	"排行榜",
	"帮助",
	"游戏设置",
	"退出游戏"
};

//options loads;

options ranks;
//	专门定义一个处理此内容的函数
// 1.xxx mmm分
//	2.yyy nnn分
//	3.zzz ddd分
//  。。。
//	4."返回主菜单"

options helps = {
	"【游戏规则】",
	"将相同的两图案配对消除",
	"【操作】",
	"WASD键控制光标，空格键选择，",
	"配对成功则选中的两图案消失",
	"【按键】",
	"按R重排，按Esc退出",
	"【高分技巧】",
	"用时越少，分数越高",
	"               ——by Zpss"
};

options setOptions = {
	"游戏难度：",
	//	"游戏音效",
	"返回主菜单"
};

options* setOpCps;

options diffs = {
	"简单： 6种图案",
	"普通： 9种图案",
	"困难：12种图案"
};

options pauses = {
	"音效：",
	"继续游戏",
	"存档",
	"不保存并退出"
};

Menu mainMenu(menus);
//Menu loadMenu(loads);
//Menu rankMenu(ranks);
Menu helpMenu(helps);
Menu diffMenu(diffs);
Menu pausMenu(pauses);