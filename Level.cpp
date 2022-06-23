#include "Level.h"

const char* diffToStr(unsigned diff) {
	switch (diff) {
	case 1:
		return "���򵥡�";
	case 2:	
		return "����ͨ��";
	case 3:	
		return "�����ѡ�";
	default:
		return	"\0";
	}
}

Level::Level(unsigned Level)
	: level(Level), unlimited(false) {
	set = getSets();
	map = new Map(Level);
}

Level::Level(unsigned Level, bool Unlimited)
	: level(Level), unlimited(Unlimited) {
	set = getSets();
	map = new Map(Level);
}

unsigned Level::getLevel() {
	return level;
}

Settings Level::getSets() {
	ifstream fin(setFile);
	Settings setsIn = { 1 };
	fin >> setsIn.difficulty;
	return setsIn;
}

void Level::changeSets(Settings& nset) {
	ofstream fout(setFile);
	fout << nset.difficulty;
}

void Level::setWindowSize() {
	console.size(short(12 + level * 4), short(2 * level + 4));
}

string Level::setTitle() {
	string title = diffToStr(set.difficulty);
	title += "�� ";
	title += to_string(level);
	title += " ��";

	wchar_t* wt = new wchar_t[title.size()];
	swprintf(wt, title.size(), L"%S", title.c_str());

	console.title(wt);
	return title;
}

void Level::newGame() {
	if (unlimited) {
		setWindowSize();
		setTitle();
		console.clear();
		map->init(set.difficulty);
		map->sort();
		map->print(COORD{ 0, 0 });
		map->getCursor();
	}
	else {
		setWindowSize();
		thread tTimer(&Map::timer, map, setTitle());
		if (unlimited) setTitle();
		thread tGame(&Map::getCursor, map);
		console.clear();
		map->init(set.difficulty);
		map->sort();
		map->print(COORD{ 0, 0 });
		tGame.detach();
		if (!unlimited)
			tTimer.join();
	}
	
	if (map->second <= 0) {
		options end;
		menu = new Menu(end);
		menu->push_back("**��Ϸ������**");
		menu->show(false, true, 0);
		Sleep(750);
		string tmp = "ͨ���ؿ�: ";
		tmp += to_string(level - 1);
		menu->push_back(tmp);
		menu->show(false, true, 0);
		Sleep(500);
		tmp = "���Ŵ���: ";
		tmp += to_string(this->map->resort);
		menu->push_back(tmp);
		menu->show(false, true, 0);
		Sleep(500);
		tmp = "�ܷ�: ";
		tmp += to_string(int(score + (int(level) * 2 + 2) * (int(level) * 2 + 2) + map->emptyed - 10 * int(map->resort)));
		menu->push_back(tmp);
		menu->exec(false, "����Enter�����������˵�");
		delete menu;
		score = 0;
		main();
	}
	if (map->done)
		score += getScore();
	if (unlimited && map->second <= 0) {
		options end;
		menu = new Menu(end);
		menu->push_back("**��Ϸ������**");
		menu->show(false, true, 0);
		Sleep(750);
		string tmp = "ͨ���ؿ�: ";
		tmp += to_string(level - 1);
		menu->push_back(tmp);
		menu->show(false, true, 0);
		Sleep(500);
		tmp = "���Ŵ���: ";
		tmp += to_string(this->map->resort);
		menu->push_back(tmp);
		menu->exec(false, "����Enter�����������˵�");
		delete menu;
		score = 0;
		main();
	}
	else if (level == 4) {
		options end;
		menu = new Menu(end);
		menu->push_back("**��Ϸ������**");
		menu->show(false, true, 0);
		Sleep(750);
		string tmp = "ͨ���ؿ�: ";
		tmp += to_string(level);
		menu->push_back(tmp);
		menu->show(false, true, 0);
		Sleep(500);
		tmp = "���Ŵ���: ";
		tmp += to_string(this->map->resort);
		menu->push_back(tmp);
		menu->show(false, true, 0);
		Sleep(500);
		tmp = "�ܷ�: ";
		tmp += to_string(score);
		menu->push_back(tmp);
		menu->exec(false, "����Enter�����������˵�");
		delete menu;
		score = 0;
		main();
	}
}