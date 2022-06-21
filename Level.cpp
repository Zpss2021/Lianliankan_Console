#include "Level.h"

const char* diffToStr(unsigned diff) {
	switch (diff) {
	case 1:
		return "【简单】";
	case 2:	
		return "【普通】";
	case 3:	
		return "【困难】";
	default:
		return	"\0";
	}
}

Level::Level(unsigned Level)
	: level(Level) {
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

void Level::setTitle() {
	string title = diffToStr(set.difficulty);
	title += "第 ";
	title += to_string(level);
	title += " 关";
	wchar_t* wt = new wchar_t[title.size()];
	swprintf(wt, title.size(), L"%S", title.c_str());
	console.title(wt);
}

void Level::newGame() {
	setTitle();
	setWindowSize();
	console.clear();
	map->init(set.difficulty);
	map->sort();
	map->print();
	map->getCursor();

	console.pause();
}
