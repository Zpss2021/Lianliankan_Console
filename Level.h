#pragma once
#ifndef _LEVEL_H
#define _LEVEL_H

#include <fstream>
#include <string>
#include <thread>
#include "Map.h"

using namespace std;

static const char* setFile = "./settings.dat";

struct Settings {
	unsigned difficulty;
	// more...
};

const char* diffToStr(unsigned diff);

class Level {
public:
	Level(unsigned);
	Level(unsigned, bool);
	unsigned getLevel();
	static Settings getSets();
	static void changeSets(Settings&);
	void setWindowSize();
	string setTitle();
	void newGame();
	friend class File;
	inline int getScore() {
		return int(map->second) + (level * 2 + 2) * (level * 2 + 2) - 10 * int(map->resort);
	}
private:
	Map* map;
	Settings set;
	unsigned level;
	bool unlimited;
};

static Level* level;
static Settings* sets;
static int score = 0;
extern int main();

#endif /*_LEVEL_H*/