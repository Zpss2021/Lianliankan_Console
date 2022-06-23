#include <iostream>
#include "Map.h"
#include "Menu.h"
#include "Level.h"
#include "Console.h"

using namespace std;

int main(void) {
	console.locale("zh-CN").font(L"新宋体", 28).color(black, white).cursor(1, false);
	options end; string tmp;
	while (true) {
		console.title(L"《连连看》控制台版");
		switch (mainMenu.exec(true, 1, "【WASD或方向键移动】")) {
		case 1:
			helpMenu.push_back("【游戏模式】 冒险模式");
			helpMenu.exec(false, "按【Enter】键开始游戏");
			helpMenu.pop_back();
			for (int lev = 1; lev < 5; lev++) {
				console.clear();
				level = new Level(lev);
				level->newGame();
				delete level;
			}
			break;
		case 2:
			helpMenu.push_back("【游戏模式】 无尽模式");
			helpMenu.exec(false, "按【Enter】键开始游戏");
			helpMenu.pop_back();
			console.clear();
			for (int lev = 1; lev < 255; lev++) {
				console.clear();
				level = new Level(lev, true);
				level->newGame();
				delete level;
			}
			break;
		case 3:
			break;
		case 4:
			helpMenu.push_back("               ——by Zpss");
			helpMenu.exec(false, "按【Enter】键返回主菜单");
			helpMenu.pop_back();
			break;
		case 5:
			setOpCps = new options(setOptions);
			*(setOpCps->begin()) += diffToStr(Level::getSets().difficulty);
			switch ((menu = new Menu(*setOpCps))->exec(true, 1)) {
			case 1:
				(sets = new Settings(Level::getSets()))
					->difficulty = diffMenu.exec(true, 1);
				Level::changeSets(*sets);
				delete sets;
			default:
				break;
			}
			delete menu;
			delete setOpCps;
			break;
		case 6:
			console.pause();
			exit(0);
		default:
			break;
		}
	}
	return -1;
}