#pragma once
#ifndef _LEVEL_H
#define _LEVEL_H

#include <fstream>
#include <string>
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
	unsigned getLevel();
	static Settings getSets();
	static void changeSets(Settings&);
	void setWindowSize();
	void setTitle();
	void newGame();
private:
	Map* map;
	Settings set;
	unsigned level;
};

static Level* level;
static Settings* sets;

#endif /*_LEVEL_H*/